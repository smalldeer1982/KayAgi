# Katya and Segments Sets

## 题目描述

给你n个集合，集合中的元素是线段，每个线段用左右端点$[l,r],l\le r$描述。每个集合可以包含任意个线段（包括0个），允许存在相同的线段

有m个询问，每个询问形如$a,b,x,y$，问对于编号在$[a,b]$之间的集合，是不是每一个都包含一个满足$x\le l\le r\le y$的线段，是则输出"yes"，否则输出"no"

## 说明/提示

第一个询问答案是no，因为第二个集合不包含一个在$[2,3]$之间的线段

对于第二个询问，第一个集合包含$[2,3]$，第二个集合包含$[2,4]$

对于第三个询问，第一个集合包含$[2,3]$，第二个集合包含$[2,4]$，第三个集合包含$[2,5]$

对于第四个询问，第二个集合不包含一个在$[3，6]$之间的线段

对于第五个询问，第二个集合包含$[2,4]$，第三个集合包含$[2,5]$，第四个集合包含$[7,9]$

## 样例 #1

### 输入

```
5 5 9
3 6 3
1 3 1
2 4 2
1 2 3
4 6 5
2 5 3
7 9 4
2 3 1
4 10 4
1 2 2 3
1 2 2 4
1 3 1 5
2 3 3 6
2 4 2 9
```

### 输出

```
no
yes
yes
no
yes
```

# 题解

## 作者：Wen_kr (赞：8)

主要思路：离散化+主席树

考虑将所有线段左端点离散化，主席树的第 $j$ 个根的叶子节点 $i$ 表示第 $i$ 个集合中左端点在离散化之后大于等于 $j$ 的线段中右端点的最小值。

这样说可能难以理解。我们考虑对于一个询问 $a,b,x,y$

我们考虑 $[a,b]$ 中的每个集合，它符合条件，当且仅当这个集合中存在一条线段，左端点大于 $x$，右端点小于 $y$，本质上就是维护左端点大于 $x$ 的线段中右端点的最小值。

我们定义一个集合 $a$ 在 $(x,y)$ 意义下的答案为这个集合中的左端点大于 $x$ 的线段右端点最小值，这个可以使用线段树 $O(log n)$ 更新。

接着我们查询 $[a,b]$ 区间每个集合的答案并取最大值，这个操作可以通过线段树实现。若最大值小于 $y$ ，答案为 $yes$，否则就是 $no$

那么我们只需要倒序插入线段，用主席树维护若干集合右端点最小值的最大值，询问时找 $x$ 在我们离散化集合中的 $lower\_bound$ 即可。

感觉这道题是黑题已经远远高估它了。

防止抄袭，从我做起，以下代码经过一些小修改，只提供思路，并不能 AC，请读者们自行思考 AC 代码。

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

int n,m,k;

struct Segx
{
	int l,r,ps;
	bool operator < (const Segx &a) const
	{
		return l < a.l;
	}
}Seg[300050];

const int MAXNODE = 1e7;

struct Prisident_Tree
{
	int val[MAXNODE],lc[MAXNODE],rc[MAXNODE],pcnt;
	void Push_Up(int rt)
	{
		val[rt] = max(val[lc[rt]],val[rc[rt]]);
	}
	int Build(int rt,int l,int r)
	{
		rt = ++ pcnt;
		if(l == r)
		{
			val[rt] = 1000000001;
			return rt;
		}
		int mid = (l + r) >> 1;
		lc[rt] = Build(0,l,mid);
		rc[rt] = Build(0,mid + 1,r);
		return rt;
        	Push_Up(rt);
	}
	void Update(int &rt,int rt0,int l,int r,int x,int valx)
	{
		if(!rt) rt = ++ pcnt;
		val[rt] = val[rt0];
		lc[rt] = lc[rt0]; rc[rt] = rc[rt0];
		if(l == r)
		{
			val[rt] = min(val[rt],valx);
			return ;
		}
		int mid = (l + r) >> 1;
		if(mid >= x) Update(lc[rt],lc[rt0],l,mid,x,valx);
		else Update(rc[rt],rc[rt0],mid + 1,r,x,valx);
                Push_Up(rt);
	}
	int Query(int rt,int l,int r,int ll,int rr)
	{
		if(ll <= l && r <= rr) return val[rt];
		int mid = (l + r) >> 1;
		if(mid >= rr) return Query(lc[rt],l,mid,ll,rr);
		if(mid < ll) return Query(rc[rt],mid + 1,r,ll,rr);
		return max(Query(lc[rt],l,mid,ll,rr),Query(rc[rt],mid + 1,r,ll,rr));
	}
}tree;

int lisan[300050];
int root[300050];

int main()
{
	int n,m,k,scnt = 0;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= k; ++ i)
	{
		scanf("%d%d%d",&Seg[i].l,&Seg[i].r,&Seg[i].ps);
		lisan[++ scnt] = Seg[i].l;
	}
	sort(lisan + 1,lisan + 1 + scnt); scnt = unique(lisan + 1,lisan + 1 + scnt) - lisan - 1;
	root[scnt + 1] = tree.Build(1,1,n);
	for(int i = 1;i <= k; ++ i) Seg[i].l = lower_bound(lisan + 1,lisan + 1 + scnt,Seg[i].l) - lisan;
	sort(Seg + 1,Seg + 1 + k);
	int cpos = k;
	for(int i = scnt;i >= 1; -- i)
	{
		bool fucked = 0;
		while(cpos >= 1 && Seg[cpos].l >= i)
		{
			tree.Update(root[i],fucked ? root[i] : root[i + 1],1,n,Seg[cpos].ps,Seg[cpos].r); cpos --;
			fucked = 1;
		}
		if(!fucked) root[i] = root[i + 1];
	}
	for(int i = 1;i <= m; ++ i)
	{
		int l,r,x,y; scanf("%d%d%d%d",&l,&r,&x,&y);
		x = lower_bound(lisan + 1,lisan + 1 + scnt,x) - lisan;
		int ans = tree.Query(root[x],1,n,l,r);
		if(ans <= y) printf("yes\n"); else printf("no\n");
	}
}
```

---

## 作者：封禁用户 (赞：7)

## 题目大意

给定 $k$ 条线段，每一条线段属于 $1\sim n$ 中的某一个集合。
$m$ 次询问，每次询问形如 $(a, b, x, y)$，即询问是否集合 $a\sim b$  中，都存在一条线段被线段 $[x, y]$ 覆盖。

$ k \le 3\times 10^5$ , $n, m \le 10^5$。

## 题目思路

对于这种题当然是先考虑暴力，再考虑用数据结构优化。

有两种思维方向:

- 一种是从线段为元素出发，查询 $[x, y]$ 内的线段是否能将 $[a, b]$ 这些集合囊括入内；
- 一种是从集合为元素出发，查询 $[a, b]$ 这个区间的集合是否都有线段在 $[x, y]$ 之间。

第二个一定会比第一个好做，不然题目给你 $[a, b]$ 这个区间是白给的吗。

考虑对于某一个集合，它包含某一条线段 $ [l, r]$ 在 $[x, y]$ 之间，相当于满足 $ r \le y$ 的线段中最大的 $l \ge x$ 。

相当于我们在满足 $r \le y$ 的前提下，求出 $[a, b]$ 集合中的线段最大的 $l$，将这些 $l$ 取最小值 $l_{min}$。如果 $l_{min} \ge x$，则有解，输出 `yes`；否则输出 `no`。

在满足 $r \le y$ 的前提下，我们可以用可持久化线段树来搞。按照 $r$ 从小到大的顺序，将 $l$ 依次加入线段树并维护历史版本。这样就可以取得任意的 $r \le y$ 情况下的线段树。就可以进行相应的询问。
## 代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100000;
const int MAXK = 300000;
const int INF = (1<<30);
struct Segment{
	int l, r, p;
	Segment(int _l=0, int _r=0, int _p=0):l(_l), r(_r), p(_p){}
}seg[MAXK + 5];
bool operator < (Segment a, Segment b) {
	return a.r < b.r;
}
struct SegmentTree{
	SegmentTree *ch[2]; int mn;
}tree[MAXK*20 + 5], *root[MAXK + 5], *NIL, *tcnt;
void init() {
	NIL = tcnt = &tree[0];
	NIL->ch[0] = NIL->ch[1] = NIL;
	NIL->mn = -INF;
}
void insert(SegmentTree *rt1, SegmentTree *&rt2, int pos, int key, int le, int ri) {
	rt2 = (++tcnt); *(rt2) = *(rt1);
	if( le == ri ) rt2->mn = max(rt2->mn, key);
	else {
		int mid = (le + ri) >> 1;
		if( pos <= mid )
			insert(rt1->ch[0], rt2->ch[0], pos, key, le, mid);
		else insert(rt1->ch[1], rt2->ch[1], pos, key, mid+1, ri);
		rt2->mn = min(rt2->ch[0]->mn, rt2->ch[1]->mn);
	}
}
int query(SegmentTree *rt, int le, int ri, int ql, int qr) {
	if( ql > ri || qr < le )
		return INF;
	else if( ql <= le && ri <= qr )
		return rt->mn;
	int mid = (le + ri) >> 1;
	return min(query(rt->ch[0], le, mid, ql, qr), query(rt->ch[1], mid+1, ri, ql, qr));
}
int main() {
	init(); int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i=1;i<=k;i++)
		scanf("%d%d%d", &seg[i].l, &seg[i].r, &seg[i].p);
	sort(seg+1, seg+k+1); root[0] = NIL;
	for(int i=1;i<=k;i++)
		insert(root[i-1], root[i], seg[i].p, seg[i].l, 1, n);
	for(int i=1;i<=m;i++) {
		int a, b, x, y;
		scanf("%d%d%d%d", &a, &b, &x, &y);
		int p = upper_bound(seg+1, seg+k+1, Segment(0, y, 0)) - seg - 1;
		int q = query(root[p], 1, n, a, b);
		if( q >= x ) puts(q >= x ? "yes" : "no");
		fflush(stdout);
	}
}
```


---

## 作者：Fading (赞：6)

主席树练手好题，所以为什么是黑的$qwq$

做主席树的题目，不要被模版给欺骗了，主席树本质是**可持久化**线段树，他不一定是权值线段树（废话！

我们的主席树维护的是：以集合为下标，每一个集合内所有线段的$r$的最小值。

对于非叶子结点，还要维护他儿子权值的最大值。

我们先按照所有线段的$l$从大到小排序，这样子可以消除$l$的影响。

然后按照$l$从大到小的顺序将$r$插入

设$root[i]$为第$i$次插入后这棵主席树的根

每一次询问就等价于询问$l\geq x$时对应的主席树区间$(a,b)$的最大值是否$\leq y$就好啦！

那怎么求$l\geq x$时对应的主席树的根节点呢？

二分就好啦!

代码如下:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
int n,m,cnt,k;
struct node{
    int l,r,sum=1999999999;
}g[maxn*20];
inline int read(){
    register int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
    while (ch<='9'&&ch>='0') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct value{
    int x,y,id;
}x[maxn];
bool cmp(value v1,value v2){
    return v1.x>v2.x;
}
int root[maxn];
void update(int num,int wht,int &rt,int l,int r){
    g[++cnt]=g[rt];
    if (l==r){g[cnt].sum=min(g[rt].sum,wht);rt=cnt;return;}
    rt=cnt;int mid=l+r>>1;
    if (num<=mid) update(num,wht,g[rt].l,l,mid);
    else update(num,wht,g[rt].r,mid+1,r);
    g[rt].sum=max(g[g[rt].l].sum,g[g[rt].r].sum);
}
int query(int rt,int l,int r,int lb,int rb){
    if (lb>=l&&rb<=r) return g[rt].sum;
    if (lb>r||l>rb) return -1999999999;
    int mid=lb+rb>>1;
    return max(query(g[rt].l,l,r,lb,mid),query(g[rt].r,l,r,mid+1,rb));
}
int main(){
    cnt=1;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        x[i].x=read(),x[i].y=read(),x[i].id=read();
    }
    sort(x+1,x+1+k,cmp);
    for (int i=1;i<=k;i++){
        //cout<<"wht:"<<x[i].x<<" "<<x[i].y<<" "<<x[i].id<<endl;
        root[i]=root[i-1];
        update(x[i].id,x[i].y,root[i],1,n);
    }
    while (m--){
        int A=read(),B=read(),X=read(),Y=read();
        int lb=1,asn=-1,rb=k;
        while (lb<=rb){
            int mid=lb+rb>>1;
            if (x[mid].x>=X){
                lb=mid+1;asn=mid;
            }else{
                rb=mid-1;
            }
        }
        int ans=query(root[asn],A,B,1,n);
        //cout<<"pos:"<<asn<<" "<<ans<<endl;
        if (ans<=Y) printf("yes\n"); else printf("no\n");
        fflush(stdout);
    }
    return 0;
}

```

---

## 作者：a2956331800 (赞：3)

UPDATA：注意主席树的root数组等于**插入次数**而不是集合个数；以及之前看错题，这个题问的是“是不是每一个集合都存在一个线段在给定区间内”，而不是“存在一个...”（~~昨天还说题意相当明确来着~~），题目翻译上也写错了（所以没过审？）然后也改掉了不知道能不能过。

昨天打CF这个题写了半天发现是假算法，然后就看了官方题解（贼难懂）发现好妙，把这题的翻译和题解一起写了

题意~~相当明确~~就不多说了

先把线段按**左端点**排序，左端点相同的顺序无所谓

#### 考虑怎么回答一个询问：先找到左端点$\ge a$的位置，然后考虑从它开始右面（数组排过序了）所有右端点$\le b$的线段中有没有编号在$a$、$b$之间的

直接做肯定TLE

对每个集合定义一个$W$，表示这个集合中左端点$\ge a$的线段中，右端点的**最小值**

## 线段树！！！

$a$、$b$之间这个条件用**线段树**就可以解决了（线段树**对集合**维护$W$的最大值）注意这个是关键，答案按集合维护

------------

怎么维护$W$啊（$a$是改变的,$W$也会跟着变）

不知道**强制在线**和$10^5$有没有让你想到什么

## 可持久化线段树！！！

回想一下开始那个排过序的数组，现在倒序把其中的线段插入（计入答案），这样更新的时候就是左端点**随插入顺序向左移**

### 怎么回答询问呢

先在二分找到哪些线段左端点$\ge a$，然后在可持久化线段树上找到最靠左的（符合条件的）线段对应的版本（就是第$n-id+1$个版本，$id$是线段的编号），由于是按左端点倒序插入，这个版本一定包含了所有左端点$\ge a$的线段，然后查一下$[a,b]$之间的最小值看看是不是$\le b$就行了

注意如果没有一个在$a$左边的话，直接no（要不可能查到第0（视写法不同可能是01）个版本去然后RE）

---

## 作者：yizhiming (赞：2)

本来懒得写题解的，但突然发现自己是第 $441$ 个提交，第 $144$ 个通过，闲得无聊纪念一下(

## 题面描述

给你 $n$ 个集合，每个集合中右若干从 $l_i$ 到 $r_i$ 的线段，线段总数为 $k$，共 $m$ 次查询，每次查询第 $a$ 到第 $b$ 个集合中的是否满足所有集合都有至少一条线段完全处于 $[l,r]$ 区间。

$1\leq n,m\leq 10^5,1\leq k\leq 3\times 10^5,1\leq l,r\leq 10^9,1\leq a,b \leq n$

## 题目分析

我们发现查询操作相当于查询一个二维区间，是可持久化的基本操作，现在的问题就在于，我们该选择哪一部分作为下标，哪一部分作为可持久化的版本标号，哪一部分用作权值。

我们先来考虑每个线段能做什么，我们假设当前集合有两个线段，左端点相等，右端点分别为 $r_1,r_2$，且 $r_1<r_2$，那么我们就会发现，$r_2$ 的贡献完全可以忽视掉，原因也很简单，如果当前区间 $[l,r]$ 能够包含 $[l,r_2]$，那么也一定能包含 $[l,r_1]$，但反过来却不一定。

所以我们可以用右端点作为线段树节点的权值，对于叶子结点，我们记录对应线段右端点的最小值，对于其他节点，我们维护其左右儿子权值的最大值，只要当前的区间的权值超过当前查询的 $r$，那么就没有合法方案。反之合法。

既然我们已经用右端点作为权值了，所以为了让下标是区间，所以只能让 $a,b$ 作为线段树的下标了，也符合上述的求值方法，相当于我们每次查询 $[a,b]$ 区间右端点的最大值。

最后我们考虑如何用 $l$ 维护历史版本标号，我们想我们需要知道什么，现在我们已经知道了在不考虑左端点是否合法的情况下，如何判断当前区间是否合法。所以我们现在是需要想办法保证当前区间的左端点全部合法。

那么也就是说要满足 $l_i\geq l$，所以我们就能想到 $rt_l$ 这棵线段树维护所有左端点 $\geq l$ 的线段，我们考虑将左端点离散化，然后从大到小排序，每次用最大的更新线段树，就直接以上一个版本为蓝本更新即可。

由于我们离散化了左端点，所以查询的时候，要二分找到最小的满足条件的左端点，从这个左端点开始查询，而且注意如果没找到符合条件的，说明一定无解。

## Code

注意由于我们是动态开点，所以权值取最大值的时候不会考虑到空节点，但实际上只要当前区间有一个空叶子节点，那么就一定无解，要特判掉这种情况，所以要另外维护一个 $cnt_i$ 表示当前线段树节点有多少个叶子节点，只有当叶子节点满的时候才可能有解。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 3e5+5;
int lsh[N],lx[N],rx[N],p[N];
int rt[N];
struct aa{
	int lx,rx,p;
	bool operator<(const aa&x)const{
		return lx>x.lx;
	}
}line[N];
int tot;
struct bb{
	int lc,rc,val,cnt;
}node[N*40];
int inf = 2e9;
void pushup(int u){
	node[u].val = max(node[node[u].lc].val,node[node[u].rc].val);
	node[u].cnt = node[node[u].lc].cnt+node[node[u].rc].cnt;
	if(!node[u].lc&&!node[u].rc){
		node[u].val = inf;
	}
}
void ins(int &u,int v,int l,int r,int pla,int x){
	u = ++tot;
	node[u] = node[v];
	if(l==r){
		if(node[u].val==0){
			node[u].val=x;
		}else{
			node[u].val = min(x,node[u].val);
		}
		node[u].cnt = 1;
		return;
	}
	int mid = (l+r)/2;
	if(pla<=mid){
		ins(node[u].lc,node[v].lc,l,mid,pla,x);
	}else{
		ins(node[u].rc,node[v].rc,mid+1,r,pla,x);
	}
	pushup(u);
}
int n,m,k,cnt;
int zhi[N];
int ask(int val){
	int l=1,r=cnt;
	int ans=0;
	while(l<=r){
		int mid = (l+r)/2;
		if(val<=zhi[mid]){
			ans = mid;
			l = mid+1;
		}else{
			r = mid-1;
		}
	}
	return ans;
}

int query(int u,int l,int r,int ll,int rr){
	if(!u){
		return inf;
	}
	if(l==ll&&r==rr){
		if(node[u].cnt!=r-l+1){
			return inf;
		}
		return node[u].val;
	}
	int mid = (l+r)/2;
	if(rr<=mid){
		return query(node[u].lc,l,mid,ll,rr);
	}else if(ll>mid){
		return query(node[u].rc,mid+1,r,ll,rr);
	}else{
		return max(query(node[u].lc,l,mid,ll,mid),query(node[u].rc,mid+1,r,mid+1,rr));
	}
}
int main(){
	n = read();m = read();k = read();
	for(int i=1;i<=k;i++){
		line[i].lx = read();line[i].rx = read();line[i].p = read();
//		lx[i] = read();rx[i] = read();p[i] = read();
		lsh[i] = line[i].lx;
	}
	sort(lsh+1,lsh+1+k);
	int z = unique(lsh+1,lsh+1+k)-lsh-1;
	for(int i=1;i<=k;i++){
		line[i].lx = lower_bound(lsh+1,lsh+1+z,line[i].lx)-lsh;
	}
	sort(line+1,line+1+k);
	for(int i=1;i<=k;i++){
		if(line[i].lx!=line[i-1].lx){
			cnt++;
			rt[cnt] = rt[cnt-1];
			zhi[cnt] = lsh[line[i].lx];
		}
		ins(rt[cnt],rt[cnt],1,n,line[i].p,line[i].rx);
	}
	int a,b,x,y;
	for(int i=1;i<=m;i++){
		a = read();b = read();x = read();y = read();
		int id = ask(x);
		if(id==0){
			cout<<"no"<<"\n";
		}else{
			bool flg = (query(rt[id],1,n,a,b)<=y);
			if(flg){
				cout<<"yes"<<"\n";
			}else{
				cout<<"no"<<"\n";
			}
		}
		cout.flush();
	}
	return 0;
}
```

怎么感觉又写的好长啊。。。

---

## 作者：Flandres (赞：1)

主席树好题。

要询问的是 $[a,b]$ 的集合中是否每一个集合都包含一个 $[l,r]$ 的线段。

用扫描线的思想，考虑将所有的线段先存下来，按右端点排序，消除右端点的影响。

然后我们发现，因为已经排序，判断右端点的位置关系是容易的。如果我们还知道 $[a,b]$ 集合中右端点 $\le r$ 所有线段的左端点的最小值 $\ge l$，那么就可以判定是合法的。其实就是维护一个前缀最小值，这个可以用可持久化线段树轻松解决。

注意在线段树的叶子结点上维护的是左端点的最大值，因为一个集合只需要有一条线段满足要求就可以。

还需要注意主席树的空间大约是 $O(n\log n)$ 级别的。~~管那么多，能开多大就开多大就好。~~

详见代码：

```cpp
#include<bits/stdc++.h>
int n,m,k;
struct segment{
	int l,r,p;segment()=default;
	segment(int l,int r,int p):l(l),r(r),p(p){}
	bool operator<(const segment &rhs)const{return r<rhs.r;}
}s[300005];
int root[300005];
struct HjtTree{
	struct node{int ls,rs,mn;}T[6000005];int tot=0;
	inline void pushup(int o){T[o].mn=std::min(T[T[o].ls].mn,T[T[o].rs].mn);}
	void modify(int &o,int pre,int l,int r,int x,int v){
		o=++tot;T[o]=T[pre];
		if(l==r)return T[o].mn=std::max(T[o].mn,v),void();int mid=l+r>>1;
		x<=mid?modify(T[o].ls,T[pre].ls,l,mid,x,v):modify(T[o].rs,T[pre].rs,mid+1,r,x,v);
		pushup(o);
	}
	int query(int o,int l,int r,int ql,int qr){
		if(ql>r||qr<l)return INT_MAX;
		if(ql<=l&&r<=qr)return T[o].mn;int mid=l+r>>1;
		return std::min(query(T[o].ls,l,mid,ql,qr),query(T[o].rs,mid+1,r,ql,qr));
	}
}t;
int main(){
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cin>>n>>m>>k;for(int i=1;i<=k;++i)std::cin>>s[i].l>>s[i].r>>s[i].p;
	std::sort(s+1,s+1+k);
	for(int i=1;i<=k;++i)t.modify(root[i],root[i-1],1,n,s[i].p,s[i].l);
	for(int i=1,a,b,x,y;i<=m;++i){
		std::cin>>a>>b>>x>>y;
		int pos=std::upper_bound(s+1,s+1+k,(segment){0,y,0})-s-1;
		t.query(root[pos],1,n,a,b)>=x?std::cout<<"yes":std::cout<<"no";
		std::cout<<std::endl;
	}
	return 0;
}
```







---

## 作者：Islauso (赞：1)

## 题目大意

给定 $k$ 条线段，分成 $n$ 组，每组标号 $1,2,3,\dots,n$，每次询问标号为 $a,a+1,a+2,\dots,b$ 的集合中，是否都有至少一条线段满足 $x\le l\le r\le y$，强制在线。

## 思路

~~居然还能用交互来强制在线。~~

看到这道题第一时间想到的是主席树，因为这道题在区间里询问一个区间问题。一开始，我想到的是按照线段所属集合从小到大排序后依次塞到主席树里面，但这样貌似只能解决询问集合里有多少条线段满足条件，并不能判断是否每个集合都包含一条满足要求的线段。

所以我们考虑转化问题。

思考如果只有一个集合怎么办，显然可以这样：先对于所有右端点小于等于 $i$ 的线段，求出它们最大的那个左端点 $l$，记为 $w_i$，对于每一次询问，如果满足 $x\le w_y$，则说明有至少一条满足要求的线段，如果 $x>w_y$，那么就没有。

证明一下这个方法的正确性，首先由于 $w_y$ 表示的是右端点小于等于 $y$ 的线段中最大的左端点，所以这些线段的右端点 $r$ 很明显都是满足 $r\le y$ 的。如果在这些线段中存在一条满足要求的线段，也就是说存在一个 $l$ 大于等于 $x$，那么 $w_y$ 显然一定是大于等于 $l$ 的，而如果不存在一条满足要求的线段，也就是说所有 $l$ 都小于 $x$，那么 $w_y$ 也就一定是小于 $x$ 的了。

接下来，我们考虑如何将这个方法推广到多个集合。

可以看出，上面提到的这个方法有点像前缀和，这启发我们用主席树来维护这一过程，具体来说，用主席树第 $i$ 个根的第 $j$ 个儿子表示集合 $j$ 中所有右端点小于等于 $i$ 的线段中左端点的最大值（也就是上面的 $w_i$），这样，对于每一次询问 $a,b,x,y$，我们只需要看第 $y$ 棵线段树的 $[a,b]$ 这个区间里的值是否全都大于等于 $x$ 就行了，但我们总不能把这些叶子节点全都遍历一次吧，所以我们可以维护这些 $w_y$ 的最小值，如果这个最小值都是大于等于 $x$ 的，那一定所有集合里都包含一条满足要求的线段，如果这个最小值小于 $x$，就说明至少存在一个集合，不存在一条满足要求的线段。

对了，由于右端点不一定是连续的，所以我们建树时可以用下标来代替，在询问时二分一下，找到对应的根就行了。

还有一点，如果在查询时访问到了一个不存在的节点，而它对应的区间又包含了一部分（或全部）要查询的区间，则说明被它包含的这部分区间里不存在一条右端点小于等于 $y$ 的线段，直接返回一个极小值就行了，在 pushup 的时候，如果一个节点只有左儿子或是只有右儿子，那也直接赋成一个极小值就行了，这样如果它被要查询的区间完全包含，返回的值才正确（道理同上）。

具体的还是看代码吧，我语文有点差，可能表述不太清楚。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10, inf = 0x3f3f3f3f;
struct Segment
{
	int l;
	int r;
	int p;
	bool operator < (Segment const & x) const
	{
		return r == x.r ? (l == x.l ? p < x.p : l < x.l) : r < x.r;
	}
};
struct SegTree
{
	int ls;
	int rs;
	int dat;
};
SegTree tree[N*30];
Segment q[N];
int n, m, k, tot, c[N], rt[N];
inline void push_up(int i)
{
	if(tree[i].ls && tree[i].rs)//这里要注意，只有同时有左右儿子时才取它们的较小值，否则都直接赋成 0
		tree[i].dat = min(tree[tree[i].ls].dat, tree[tree[i].rs].dat);
	else
		tree[i].dat = 0;
}
void update(int &i, int p, int l, int r, int x, int k)
{
	i = ++tot;
	tree[i] = tree[p];
	if(l == r)
	{
		tree[i].dat = max(tree[i].dat, k);
		return;
	}
	int mid = (l+r)>>1;
	if(x <= mid)
		update(tree[i].ls, tree[p].ls, l, mid, x, k);
	else
		update(tree[i].rs, tree[p].rs, mid+1, r, x, k);
	push_up(i);
}
int query(int i, int l, int r, int x, int y)
{
	if(!i)//上面讲过了，直接返回一个极小值
		return 0;
	if(x <= l && y >= r)
		return tree[i].dat;
	int mid = (l+r)>>1, ans = inf;
	if(x <= mid)
		ans = min(ans, query(tree[i].ls, l, mid, x, y));
	if(mid+1 <= y)
		ans = min(ans, query(tree[i].rs, mid+1, r, x, y));
	return ans;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= k; i++)
	{
		scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].p);
		c[i] = q[i].r;
	}
	sort(c+1, c+1+k);
	sort(q+1, q+1+k);
	for(int i = 1; i <= k; i++)
		update(rt[i], rt[i-1], 1, n, q[i].p, q[i].l);
	while(m--)
	{
		int a, b, x, y;
		scanf("%d%d%d%d", &a, &b, &x, &y);
		y = upper_bound(c+1, c+1+k, y)-c-1;
		if(y == 0)
			printf("no\n");
		else
			if(query(rt[y], 1, n, a, b) < x)
				printf("no\n");
			else
				printf("yes\n");
		fflush(stdout);
	}
	return 0;
}
```

关于`y = upper_bound(c+1, c+1+k, y)-c-1;`这一句，我看到有的大佬是手写的二分，这样子少了一个排序，常数会小一点（~~然而因为我懒所以就没写~~）。

## 反思

思维还不够开阔，没有想到转化问题，虽然都想到主席树上去了，但就是搞不出来，对这种数据结构的理解还不够深入，应当再多加练习才行。

---

## 作者：LCuter (赞：1)

## CF1080F 题解

##### $\text{Description}$

给定 $n$ 个集合，每个集合里有若干条线段，共有 $k$ 条，$m$ 次询问，每次给定 $a,b,x,y$，询问编号在 $[a,b]$ 内的集合是否都有一条线段在 $[x,y]$ 内。

$1\le n,m\le 10^5,1\le k\le 3\times 10^5$

##### $\text{Solution}$

首先分析，若有某个集合内有一条线段在 $[x,y]$ 内，则要求其中所有满足 $l\in[x,y]$ 的线段中，$r$ 的最小值 $\in[x,y]$。实际上，由于 $r\ge l$ 一定成立，所以为了方便（询问一个前缀通常比询问一个区间来的简单），我们将 $l\in[x,y]$ 这一条件改成 $l\in [x,+\infty]$，这里的 $+\infty$ 在实现中可以看作是最大的 $l$。

因此，对于两条线段 $[l_x,r_x],[l_y,r_y]$，若 $l_x=l_y$，则我们只需考虑 $r$ 小的那一条线段。

回到问题本身，这种多维度限制的题目一般可以用排序来去除某一个维度的影响，注意到我们将询问中对 $l$ 的限制变成了一个后缀/前缀，我们将所有线段按 $l$ 降序排列，则询问中对 $l$ 的限制是一个前缀。

既然是询问一个前缀，这启发我们使用主席树。对于某一个前缀来说，其意义是所有满足 $l$ 大于等于某一个值的线段的集合。由于询问中对集合编号的限制是一个区间，我们在建树时不妨以集合编号为下标，那么此时某一个叶子节点存的就应当是其对应的集合中最小的 $r$。由于询问中要求区间内的**所有**集合都要满足条件，故该主席树中任意一个非叶子节点的权值是其儿子权值的最大值。

那么每次询问时，先二分找到需要的前缀（大于等于 $x$ 的最小的 $l$），然后在其上询问 $[a,b]$ 的最大值，若小于等于 $y$，则返回 $\texttt {yes}$，否则返回 $\texttt{no}$。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	REG char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int N=100005,K=300005,INF=0x7f7f7f7f;

int n,m,k;

struct Seg{int l,r,num;}seg[K];
inline bool cmp(Seg x,Seg y){return x.l>y.l;}
int srt[K];
inline bool cmp1(int x,int y){return x>y;}

int Rt[K],tot;
struct Tree{int ls,rs,val;}t[N*100];

void Build(int& now,int l,int r){
	t[now=++tot].val=INF;
	if(l==r) return;
	REG int mid=(l+r)>>1;
	Build(t[now].ls,l,mid),Build(t[now].rs,mid+1,r);
}

void Insert(int pre,int& now,int l,int r,int pos,int S){
	t[now=++tot]=t[pre];
	if(l==r) return (void)(t[now].val=min(t[now].val,S));
	REG int mid=(l+r)>>1;
	if(mid>=pos) Insert(t[pre].ls,t[now].ls,l,mid,pos,S);
	else Insert(t[pre].rs,t[now].rs,mid+1,r,pos,S);
	t[now].val=max(t[t[now].ls].val,t[t[now].rs].val);
}

int Ask(int now,int l,int r,int x,int y){
	if(!now) return INF;
	if(l>=x&&r<=y) return t[now].val;
	REG int Ans=0,mid=(l+r)>>1;
	if(mid>=x) Ans=max(Ans,Ask(t[now].ls,l,mid,x,y));
	if(mid<y) Ans=max(Ans,Ask(t[now].rs,mid+1,r,x,y));
	return Ans;
}

inline void Work(){
	read(n),read(m),read(k);
	for(REG int i=1;i<=k;++i) read(seg[i].l),read(seg[i].r),read(seg[i].num),srt[i]=seg[i].l;
	sort(seg+1,seg+k+1,cmp),sort(srt+1,srt+k+1,cmp1);
	Build(Rt[0],1,n);
	for(REG int i=1;i<=k;++i) Insert(Rt[i-1],Rt[i],1,n,seg[i].num,seg[i].r);
	while(m--){
    	int a,b,x,y;
    	read(a),read(b),read(x),read(y);
    	int l=1,r=k,mid,ans=0;
    	while(l<=r){
        	mid=(l+r)>>1;
        	if(srt[mid]>=x) ans=mid,l=mid+1;
        	else r=mid-1;
        }
    	int M=Ask(Rt[ans],1,n,a,b);
    	if(M<=y) puts("yes");
    	else puts("no");
    	fflush(stdout);
    }
}

int main(){Work();}
```



---

## 作者：AubRain (赞：1)

好题啊好题！

刚开始的想法是对于每个集合中的每个 $l$ 维护一个最小的 $r$ 值，然后某个区间是否合法就可以看做 $\ge x$ 的最小值是否 $\le y$。

这样的话外层区间就要树套树了，显然不行。

正解：先把所有线段按照 $l$ 从小到大排序。每次询问 $x$ 的时候，只考虑左端点$\ge x$ 的所有线段。这可以二分找到。然后就是看后缀的所有线段中，$[a,b]$ 集合的右端点最小值的区间最大值是否 $\le y$ 即可。这可以主席树实现。

还有第一次做强制在线的交互题，只要加上一句话就行了，别的都一样。

还有，数组赋值的时候不要手懒。

```cpp
int mx[M]={INF};
```
虽然只有 $mx[0]$ 的值为 $INF$ ，其它都是 0，不过还是会赋值一遍的。这会使输出大小特别大，因为这个CE了好几次。


代码：
```cpp
#include <bits/stdc++.h>
#define N 300005
#define M N*20
#define mid ((l+r)>>1)
using namespace std;

inline void rd(int &X){
    X=0;int w=0;char ch=0;
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while( isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    X=w?-X:X;
}

int n,m,k,cnt;
struct nd{int l,r,p;}a[N];
int B[N],rt[N],ls[M],rs[M],mx[M],mn[M];

bool cmp(nd a,nd b){
	return a.l<b.l;
}
void ins(int o,int &p,int x,int d,int l=1,int r=n){
	mn[p=++cnt]=min(mn[o],d);ls[p]=ls[o],rs[p]=rs[o];if(l==r) return mx[p]=mn[p],void();
	x<=mid ? ins(ls[o],ls[p],x,d,l,mid) : ins(rs[o],rs[p],x,d,mid+1,r); mx[p]=max(mx[ls[p]],mx[rs[p]]);
}
int ask(int p,int L,int R,int l=1,int r=n){
	if(!p or (L<=l and r<=R)) return mx[p]; int v=0;
	if(L<=mid) v=max(v,ask(ls[p],L,R,l,mid));
	if(R >mid) v=max(v,ask(rs[p],L,R,mid+1,r));
	return v;
}
signed main(){
	mx[0]=mn[0]=2e9;
	rd(n);rd(m);rd(k);
	for(int i=1;i<=k;i++)
		rd(a[i].l),rd(a[i].r),rd(a[i].p);
	sort(a+1,a+1+k,cmp);	
	for(int i=k;i;i--)
		ins(rt[i+1],rt[i],a[i].p,a[i].r),B[i]=a[i].l;
	while(m--){
		int a,b,x,y;rd(a);rd(b);rd(x);rd(y);
		int now=lower_bound(B+1,B+1+k,x)-B;
		ask(rt[now],a,b)<=y ? puts("yes") : puts("no");
		fflush(stdout);
	}
}
```

---

## 作者：凄魉 (赞：1)

给你$n$个集合，集合中的元素是线段，每个线段用左右端点$[l,r],l\le r$描述。每个集合可以包含任意个线段（包括0个），允许存在相同的线段

有$m$个询问，每个询问形如$a,b,x,y$，问对于编号在$[a,b]$之间的集合，是不是每一个都包含一个满足$x\le l\le r\le y$的线段，是则输出"yes"，否则输出"no"。强制在线。

这个题一开始yy了很多种做法，后来想出了一个很simple的用主席树求$[a,b]$集合中有多少被包含在$[x,y]$中的线段，但是并不能判断出是否每个集合都有没有。然后后面又演变成求二维平面内矩形范围的不同的数的个数，就弃了。

问题转化很重要，对于一个集合我们要判断是否存在，可以用这样一种方法：查询左端点$\ge l$的那些线段的右端点最小值是否$\le r$。这种思路很容易扩展，我们记一个值为$V_{i,l}$表示第$i$个集合里左端点$\ge l$的线段的右端点的最小值。那么对于一个询问$a,b,x,y$，我们要判断$[a,b]$中每个集合的$V_{i,l}$是否都小于$y$,等价于求$max\{V_{i,x}\}\le r,i\in [a,b]$。如果区间最大值都满足，那么每一个集合也都满足。所以我们只需要维护一个区间最大值就能支持查询了。

所以我们就能维护一颗线段树，支持查询在当前左端点值$l$下，集合区间$V_i$的最大值。离线的话就将线段按照左端点从大到小排序，在线段树上单点修改。

在线可持久化一下嘛。

有一个小细节的点被坑了。每次查询需要二分出一个查询的线段树根的位置。但假如给出的线段集合根本没有左端点大于当前询问点的时候，可能会出现点小问题。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
#define N 331200
#define INF 0x3f3f3f3f
int Rt[N],ls[N*33],rs[N*33],maxm[N*33],a[N],cc;
struct Seg{
	int l,r,S;
	bool operator < (const Seg &B) const {return l==B.l?r>B.r:l>B.l;}
}seg[N];
void update(int &i,int l,int r,int F,int pos,int k)
{
	i=++cc;ls[i]=ls[F];rs[i]=rs[F];maxm[i]=maxm[F];
	if (l==r) {maxm[i]=min(maxm[i],k);return;}
	int mid=(l+r)>>1;
	if (pos<=mid) update(ls[i],l,mid,ls[F],pos,k);
	else update(rs[i],mid+1,r,rs[F],pos,k);
	maxm[i]=max(maxm[ls[i]],maxm[rs[i]]);
}
int query(int i,int l,int r,int L,int R)
{
	if (!i) return INF;
	if (L<=l&&r<=R) return maxm[i];
	int mid=(l+r)>>1;
	if (L>mid) return query(rs[i],mid+1,r,L,R);
	else if (R<=mid) return query(ls[i],l,mid,L,R);
	else return max(query(ls[i],l,mid,L,mid),query(rs[i],mid+1,r,mid+1,R));
}
int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	maxm[0]=INF;a[0]=INF;
	int n=read(),Q=read(),k=read(),l,r,mid,L,R,now=0,x,y,pos;
	for (int i=1;i<=k;++i) seg[i]=(Seg){read(),read(),read()};
	sort(seg+1,seg+1+k);
	for (int i=1;i<=k;++i)
	{
		if (i==1||seg[i].l^seg[i-1].l) Rt[now+1]=Rt[now],++now,a[now]=seg[i].l;
		update(Rt[now],1,n,Rt[now],seg[i].S,seg[i].r);
	}
	while(Q--)
	{
		L=read();R=read();x=read();y=read();
		l=0;r=now;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if (a[mid]>=x) pos=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%s\n",query(Rt[pos],1,n,L,R)<=y?"yes":"no");
		fflush(stdout);
	}
	return 0;
}
```


---

