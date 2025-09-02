# TTM - To the moon

## 题目描述

一个长度为 $N$ 的数组 $\{A\}$，$4$ 种操作 ：

- `C l r d`：区间 $[l,r]$ 中的数都加 $d$ ，同时当前的时间戳加 $1$。

- `Q l r`：查询当前时间戳区间 $[l,r]$ 中所有数的和 。

- `H l r t`：查询时间戳 $t$ 区间 $[l,r]$ 的和 。

- `B t`：将当前时间戳置为 $t$ 。

　　所有操作均合法 。

ps：刚开始时时间戳为 $0$

## 样例 #1

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4```

### 输出

```
4
55
9
15
```

## 样例 #2

### 输入

```
2 4
0 0
C 1 1 1
C 2 2 -1
Q 1 2
H 1 2 1```

### 输出

```
0
1```

# 题解

## 作者：_ctz (赞：22)

题意概括一下就是区间修改的可持久化线段树。

一般的可持久化线段树都是单点改的，这道题肯定不能一个一个改。想想普通线段树的区间修改，是找到最多 $logn$ 个节点并打上懒标记。这样我们当然可以也找到这 $logn$ 个节点并继承。但是标记一下传就会出问题：某两个版本的线段树共用的节点不能修改值。

于是用标记永久化。标记永久化既不需要下传标记，也不需要通过子节点更新自己。

具体来说：**对被修改区间覆盖的节点打上标记，其左右子节点继承上个版本的左右子节点**

放图来看：

![](https://cdn.luogu.com.cn/upload/pic/52158.png )

就会发现，查询时红色线段树有标记，查询时 $tag$ 会对答案产生影响， $tag$ 不下放就不会影响到两棵线段树的公共节点，就能保证不会互相影响了 $QwQ$ 。

时间复杂度：$O(nlogn)$
 
空间复杂度：每个区间最多被分成 $2logn$ 个节点，所以为 $O(nlogn)$

细节上注意好时间戳与版本之间的关系（尤其是 $B$ 操作）

上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 100005
#define inf 0x3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
template<typename T>
inline T read(){
	T x=0;
	int y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}//快读
int root[maxn<<1],wh[maxn];
//wh记录每个时间戳对应哪个版本
int a[maxn];
struct Chairman_Tree{
	long long dat[maxn<<6],tag[maxn<<6];
	int ls[maxn<<6],rs[maxn<<6],cnt;
#define ls(x) ls[x]
#define rs(x) rs[x]
	inline void update(int node){
		dat[node]=dat[ls(node)]+dat[rs(node)];
	}
	void build(int l,int r,int &node){
		node=++cnt;
		if(l==r){
			dat[node]=a[l];
			return;
		}
		int mid=l+r>>1;
		build(l,mid,ls(node));
		build(mid+1,r,rs(node));
		update(node);
	}//初始建树
	void add(int L,int R,int l,int r,int &ne,int ol,int d){
		ne=++cnt;
		dat[ne]=dat[ol]+1ll*(min(R,r)-max(L,l)+1)*d;
		tag[ne]=tag[ol];
		if(L<=l&&R>=r){
			tag[ne]+=(long long)d;
			ls[ne]=ls[ol],rs[ne]=rs[ol];//继承子节点
			return;
		}
		int mid=l+r>>1;
		if(L<=mid)add(L,R,l,mid,ls(ne),ls(ol),d);
		else ls(ne)=ls(ol);//不包含在这个区间内节点，直接继承过来
		if(R>mid)add(L,R,mid+1,r,rs(ne),rs(ol),d);
		else rs(ne)=rs(ol);
	}
	long long ask(int L,int R,int l,int r,int node){
		if(L<=l&&R>=r)return dat[node];
		int mid=l+r>>1;
		long long ans=0;
		if(L<=mid)ans=ask(L,R,l,mid,ls(node));
		if(R>mid)ans+=ask(L,R,mid+1,r,rs(node));
		return ans+1ll*(min(R,r)-max(L,l)+1)*tag[node];
	}
}ct;
int main(){
	int n=read(),m=read(),t=0,now=0;
    //now是当前的时间戳，t是当前的版本
	for(register int i=1;i<=n;++i)
		a[i]=read();
	ct.build(1,n,root[0]);
	while(m--){
		char s[2];
		scanf("%s",s);
		if(s[0]=='C'){
			wh[++now]=++t;
			int l=read(),r=read(),d=read();
			ct.add(l,r,1,n,root[t],root[t-1],d);
		}
		else if(s[0]=='Q'){
			int l=read(),r=read();
			printf("%lld\n",ct.ask(l,r,1,n,root[t]));
		}
		else if(s[0]=='H'){
			int l=read(),r=read(),k=read();
			printf("%lld\n",ct.ask(l,r,1,n,root[wh[k]]));
		}
		else now=read(),root[++t]=root[wh[now]];
	}	
    return 0;
}

```

标记永久化大法好！ $QwQ$


---

## 作者：AubRain (赞：19)

## 法一：

大概叫标记永久化？直接主席树上区间修改即可。

修改的时候正常修改，询问的时候如果当前区间完全重合就返回 $sum$ 值。

注意的地方：

1、因为多了一个 $add$ 标记，每次 $copy$ 的时候也要复制一遍，不能忘。

2、$ask$ 的时候，$v$ 的初值是 $add[p]*(R-L+1)$ ，而不是 $add[p]*(r-l+1)$。即应该乘询问区间长度。

```cpp
#include<bits/stdc++.h>
#define N 100005
#define M N*100
#define mid ((l+r)>>1)
#define int long long 
using namespace std;

inline void rd(int &x){
	x=0;char ch=0;int w=0;
	while(!isdigit(ch)) ch=getchar(),w|=ch=='-';
	while( isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=w?-x:x;
}

char pd[5];
int n,m,cnt,t;
int rt[N],sum[M],ls[M],rs[M],add[M];

void change(int o,int &p,int L,int R,int d,int l=1,int r=n){
	sum[p=++cnt]=sum[o],ls[p]=ls[o],rs[p]=rs[o],add[p]=add[o];
	if(L<=l and r<=R) {add[p]+=d;return ;}
	if(L<=mid) change(ls[o],ls[p],L,R,d,l,mid);
	if(R >mid) change(rs[o],rs[p],L,R,d,mid+1,r);
	sum[p]=sum[ls[p]]+sum[rs[p]]+(mid-l+1)*add[ls[p]]+(r-mid)*add[rs[p]];
}
int ask(int p,int L,int R,int l=1,int r=n){
	if(L==l and r==R) return sum[p]+add[p]*(r-l+1); 
	int v=(R-L+1)*add[p];
	if(R<=mid) return v+ask(ls[p],L,R,l,mid);
	if(L> mid) return v+ask(rs[p],L,R,mid+1,r);
	return ask(ls[p],L,mid,l,mid)+ask(rs[p],mid+1,R,mid+1,r)+v;	
}
void build(int &p,int l=1,int r=n){
	p=++cnt; if(l==r) return rd(sum[p]);
	build(ls[p],l,mid);build(rs[p],mid+1,r);
	sum[p]=sum[ls[p]]+sum[rs[p]];
}
signed main(){
	rd(n);rd(m);build(rt[0]);
	while(m--){
		scanf("%s",pd);int l,r,x;
		if(pd[0]=='B') rd(t);
		if(pd[0]=='C') rd(l),rd(r),rd(x),t++,change(rt[t-1],rt[t],l,r,x);
		if(pd[0]=='Q') rd(l),rd(r),printf("%lld\n",ask(rt[t],l,r));
		if(pd[0]=='H') rd(l),rd(r),rd(x),printf("%lld\n",ask(rt[x],l,r));
	}	
}
```

## 法二:

比第一种更优的解法。

就像**“树状数组维护区间修改”**一样，维护一下差分数组，每次询问拆成两次前缀和相减。

具体来说，设 $d$ 是差分数组，刚开始值都为 $0$ 。只需要维护 $d_i$ 的前缀和以及 $d_i*i$ 的前缀和就可以知道每个前缀被增加的多少。再开一个原序列的前缀和数组就可以了。

这样每次就只需要在两颗主席树上分别修改两个位置的值，单点就该就行了。

无论是空间还是时间都比第一种解法的常数小，目前最优解前 $5$ 。

听起来很麻烦，实际上**代码短得可怜**

```cpp
#include<bits/stdc++.h>
#define N 100005
#define M N*50
#define mid ((l+r)>>1)
#define int long long 
using namespace std;

inline void rd(int &x){
	x=0;char ch=0;int w=0;
	while(!isdigit(ch)) ch=getchar(),w|=ch=='-';
	while( isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=w?-x:x;
}

char pd[5];
int n,m,cnt,t,s[N];
int rt[N],rt2[N],sum[M],ls[M],rs[M];

void ins(int o,int &p,int x,int d,int l=1,int r=n+1){
	sum[p=++cnt]=sum[o]+d,ls[p]=ls[o],rs[p]=rs[o];if(l==r) return ;
	x<=mid ? ins(ls[o],ls[p],x,d,l,mid) : ins(rs[o],rs[p],x,d,mid+1,r);
}
int ask(int p,int x,int l=1,int r=n+1){
	if(!p or l==r) return sum[p];
	return x<=mid ? ask(ls[p],x,l,mid) : ask(rs[p],x,mid+1,r)+sum[ls[p]];
}
int Ask(int rt1,int rt2,int x){
	return s[x]+(x+1)*ask(rt1,x)-ask(rt2,x);
}
signed main(){
	rd(n);rd(m);
	for(int i=1;i<=n;i++)
		rd(s[i]),s[i]+=s[i-1];
	while(m--){
		scanf("%s",pd);int l,r,x;
		if(pd[0]=='B') rd(t);
		if(pd[0]=='C') {
			rd(l),rd(r),rd(x),t++;rt[t]=rt[t-1];rt2[t]=rt2[t-1];
			ins(rt[t],rt[t],l,x),ins(rt[t],rt[t],r+1,-x);
			ins(rt2[t],rt2[t],l,x*l),ins(rt2[t],rt2[t],r+1,-x*(r+1));	
		}
		if(pd[0]=='Q') rd(l),rd(r),printf("%lld\n",Ask(rt[t],rt2[t],r)-Ask(rt[t],rt2[t],l-1));
		if(pd[0]=='H') rd(l),rd(r),rd(x),printf("%lld\n",Ask(rt[x],rt2[x],r)-Ask(rt[x],rt2[x],l-1));
	}	
}
```

---

## 作者：CyanSineSin (赞：13)

先总结下题目:

* 区间加法并创建新版本。

* 查询某版本区间和。

* 版本回溯。

如果不是区间加法，我们就可以直接用普通的主席树做了。

但有了区间加法，我们如果一个一个改，那么时间，空间都会乘 $n$ 。

如果下传懒标记，那么可能会影响到与之前版本共用的节点。如果下传懒标记时新建节点，可能又会 MLE 。

**那我们干脆就不下传了吧！**

### 标记永久化:

我们就把标记放在这里，懒标记表示下面的节点代表的区间中的每个数本来都要加上这个值，~~但是因为懒没有加。~~ 查询时要往下走就把这个节点的懒标记记上，到最后返回值的时候再把这些记录到的懒标记的和加上。

就像这张图：

![](https://i.loli.net/2020/01/21/wGM9q84zKilsF2r.png)

我们就一直把懒标记留在$1$和$5$两个点上，不用下传，查询的时候再加。

比如我们要查询$6$节点的值。

先从$1$节点开始，向右边走，顺便加上它的懒标记$3$。

到了$5$节点，又往左走，也要加上懒标记$5$。

最后到了$6$节点，得到它的现在值就是它的原值加上刚刚加上的懒标记的和。

---

区间查询的话，懒标记加上时要乘上区间元素个数。（见懒标记定义）

主席树的查询和修改其实本来就和线段树差不多，也就多了个新建节点和版本。

那么这道题的区间修改，查询也就和线段树类似:

$1$、如果当前区间与要求区间没有交集：就跳过。

$2$、如果有交集但没有被覆盖：就继续往下分：

如果是修改还要记得把这个节点的值修改掉，因为它代表的区间有一部分被修改了；

如果是查询就要记录下这个节点的懒标记。

$3$、否则就直接处理这个节点的值，修改时要修改懒标记，查询的话就要加上之前记录的懒标记之和乘上这个节点代表区间的元素个数。

一点小小的区别就是不下传懒标记，每次都新建节点，创建新版本。

新建节点时要全部复制下来，因为它代表的区间里的所有元素本来也要加上它懒标记的值的，但没有加，所以要继承过来，不然查询的时候查不到。

代码：（细节已注释）
```
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,tot,root[100010],a[100010],l,r,v,now=0;
char op;
struct node
{
	long long l,r,num,lazy;
}nodes[20000010];
void build(long long l,long long r,long long &x)//对于第0号版本的建树。 
{
	x=++tot;
	if(l^r)
	{
		long long mid=(l+r)>>1;
		build(l,mid,nodes[x].l);
		build(mid+1,r,nodes[x].r);
		nodes[x].num=nodes[nodes[x].l].num+nodes[nodes[x].r].num;
	}
	else	nodes[x].num=a[l];
}
void ins(long long l,long long r,long long pre,long long &now,long long fr,long long ba,long long val)
{
	if(l>ba||r<fr)	return;//没有交集，跳过。 
	nodes[++tot]=nodes[pre];//复制上一个版本中代表这个区间的节点值。 
	now=tot;
	if(l>=fr&&r<=ba)//完全覆盖，直接修改 
	{
		nodes[now].lazy+=val;
		//懒标记加上值，由于下面节点还应加上的值不一样，直接记录这个值，到下面乘了再加要方便些 
		nodes[now].num+=val*(r-l+1);
		//先修改当前节点的值，因为我们往下走的时候才会加上懒标记，如果不修改查询就查不到 
	}
	else
	{
		nodes[now].num+=val*max(0ll,min(r,ba)-max(l,fr)+1);
		//修改当前节点被修改的部分 
		long long mid=(l+r)>>1;
		ins(l,mid,nodes[pre].l,nodes[now].l,fr,ba,val);//
		ins(mid+1,r,nodes[pre].r,nodes[now].r,fr,ba,val);//继续分裂 
	}
}
long long find(long long l,long long r,long long x,long long fr,long long ba,long long la)
{
	if(l>ba||r<fr)	return 0;
	if(l>=fr&&r<=ba)	return nodes[x].num+la*(r-l+1);
	//原值+还应加上的总值；懒标记记录的是这个区间中每个元素还应加上的值，所以还要乘上元素个数
	else
	{
		long long mid=(l+r)>>1;
		return find(l,mid,nodes[x].l,fr,ba,la+nodes[x].lazy)+find(mid+1,r,nodes[x].r,fr,ba,la+nodes[x].lazy);//继续向下分裂 
	}
}
int main()
{
	scanf("%lld %lld",&n,&m);
	for(long long i=1;i<=n;++i)	scanf(" %lld",&a[i]);
	build(1,n,root[0]);
	for(long long i=1;i<=m;++i)
	{
		scanf(" %c %lld",&op,&l);
		if(op=='C')//区间修改 
		{
			scanf(" %lld %lld",&r,&v);
			++now;
			ins(1,n,root[now-1],root[now],l,r,v);
		}
		else if(op=='Q')//查询当前版本 
		{
			scanf(" %lld",&r);
			printf("%lld\n",find(1,n,root[now],l,r,0));
		}
		else if(op=='H')//查询历史版本 
		{
			scanf(" %lld %lld",&r,&v);
			printf("%lld\n",find(1,n,root[v],l,r,0));
		}
		else	now=l;//版本回溯 
	}
	return 0;
}
```

---

## 作者：良月澪二 (赞：6)

线段树进行单点修改时，由于每次修改最多改变$log(n)$个点，所以直接把这些点直接连到之前的树上，也就是主席树的思想

如果是区间修改呢?

对于线段树来说没什么压力

但是对于树套树主席树这一类空间开销很大的呢？如果你再对维护的东西每次都pushdown，那就是在打暴力，所以引进了**标记永久化**

算是主席树的可持久化思想

标记永久化常数小，空间小，主要就是在经过每个点时把需要修改的值对答案的贡献累计上，这样就不用每次pushdown了

1.修改操作时，若当前区间与修改区间有包含（看个人写法），更新add的值，最后还要维护区间和

2.询问操作时，把需要加的值累积起来，若当前区间和询问区间重合，返回区间和和一路上累计的add

## long long
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#define A 1000010
#define B 2010

using namespace std;
typedef long long ll;
#define int ll
struct node {
    int l, r, w, add;
}tree[A << 2];
int root[A << 2], w[A], n, m, a, b, c, cnt, now;
void build(int &k, int l, int r) {
    k = ++cnt;
    if (l == r) {
        tree[k].w = w[l];
        return;
    }
    int m = (l + r) >> 1;
    build(tree[k].l, l, m);
    build(tree[k].r, m + 1, r);
    tree[k].w = tree[tree[k].l].w + tree[tree[k].r].w;
}
void change(int &k, int kk, int l, int r, int x, int y) {
    tree[++cnt] = tree[kk];
    k = cnt;
    if (l <= x and y <= r) {
    	tree[k].add += c;
    	return;
    }
    int m = (x + y) >> 1;
    if (l <= m) change(tree[k].l, tree[kk].l, l, r, x, m);
    if (r > m) change(tree[k].r, tree[kk].r, l, r, m + 1, y);
    tree[k].w = tree[tree[k].l].w + tree[tree[k].r].w + (m - x + 1) * tree[tree[k].l].add + (y - m) * tree[tree[k].r].add;
}
ll ask(int k, int l, int r, int x, int y) {
    if (l == x and r == y) return tree[k].w + (y - x + 1) * tree[k].add;
    ll val = (r - l + 1) * tree[k].add;
    int m = (x + y) >> 1;
    if (r <= m) return val + ask(tree[k].l, l, r, x, m);
    if (l > m) return val + ask(tree[k].r, l, r, m + 1, y);
    return val + ask(tree[k].l, l, m, x, m) + ask(tree[k].r, m + 1, r, m + 1, y);
}
void operate1() {
    scanf("%lld%lld%lld", &a, &b, &c); now++;
    change(root[now], root[now - 1], a, b, 1, n);
}
void operate2() {
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", ask(root[now], a, b, 1, n));
}
void operate3() {
    scanf("%lld%lld%lld", &a, &b, &c);
    printf("%lld\n", ask(root[c], a, b, 1, n));
}

signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);
    build(root[0], 1, n);
    while (m--) {
        char opt[2];
        scanf("%s", opt);
        switch (opt[0]) {
            case 'C' : operate1(); break;
            case 'Q' : operate2(); break;
            case 'H' : operate3(); break;
            case 'B' : scanf("%lld", &now); break;
            default : break;
        }
    }
}
```

---

## 作者：qnqfff (赞：6)

思路：

建立一颗操作树，1和2操作就从当前时间戳向当前点连边，3操作就从 $t$ 向当前点连边，4操作相当于把时间戳改成 $t$ ，然后离线在操作树上做操作，这样就不需要可持久化了。

比如说这样一组操作：

```cpp
C l r v
Q l r
H l r 0
C l r v
C l r v
B 1
Q l r
C l r v
H l r 0

```

它的操作树长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/mr4a72u7.png?x-oss-process=image/resize,m_lfit,h_1000,w_2000)

就可以直接在上面 $dfs$ ，每次搜到一个点就做这个点的操作，如果是修改操作回溯的时候还要把当前节点的修改操作撤销掉。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define lson now<<1
#define rson now<<1|1
using namespace std;
int read(){
	char ch=getchar();int s=0,f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f*s;
}
int n,m,pos[1000010],ans[1000010];struct node{int l,r,sum,tag;}t[4000010];struct query{char opt;int l,r,v;}q[1000010];vector<int>e[1000010];
void build(int now,int l,int r){
	t[now].l=l;t[now].r=r;if(l==r){t[now].sum=read();return ;}
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);t[now].sum=t[lson].sum+t[rson].sum;
}
void pushdown(int now){
	if(!t[now].tag) return ;
	t[lson].tag+=t[now].tag;t[rson].tag+=t[now].tag;
	t[lson].sum+=t[now].tag*(t[lson].r-t[lson].l+1);t[rson].sum+=t[now].tag*(t[rson].r-t[rson].l+1);
	t[now].tag=0;
}
void modify(int now,int l,int r,int v){
	if(l<=t[now].l&&t[now].r<=r){t[now].sum+=v*(t[now].r-t[now].l+1);t[now].tag+=v;return ;}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(l<=mid) modify(lson,l,r,v);if(mid<r) modify(rson,l,r,v);t[now].sum=t[lson].sum+t[rson].sum;
}
int query(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r) return t[now].sum;
	pushdown(now);int mid=(t[now].l+t[now].r)>>1,ans=0;if(l<=mid) ans+=query(lson,l,r);if(mid<r) ans+=query(rson,l,r);return ans;
}
void dfs(int u){
	if(q[u].opt=='C') modify(1,q[u].l,q[u].r,q[u].v);else if(q[u].opt=='Q'||q[u].opt=='H') ans[u]=query(1,q[u].l,q[u].r);
	for(auto v:e[u]) dfs(v);if(q[u].opt=='C') modify(1,q[u].l,q[u].r,-q[u].v);
}
signed main(){
	n=read();m=read();build(1,1,n);int t=0,lst=0;for(int i=1;i<=m;i++){
		cin>>q[i].opt;if(q[i].opt=='C') q[i].l=read(),q[i].r=read(),q[i].v=read(),e[lst].push_back(i),pos[++t]=lst=i;
		else if(q[i].opt=='Q') q[i].l=read(),q[i].r=read(),e[lst].push_back(i);
		else if(q[i].opt=='H') q[i].l=read(),q[i].r=read(),e[pos[read()]].push_back(i);
		else t=read(),lst=pos[t];
	}dfs(0);for(int i=1;i<=m;i++) if(q[i].opt=='Q'||q[i].opt=='H') cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：3)

此题其实就是可持久化线段树的区间修改。

可以用标记永久化。

但我不想用。

我用一种只用可持久化线段树的单点自增与区间求和来完成。

我们可以先想一下不可持久化该怎么只用这两个操作来完成。

也就是[线段树 1](https://www.luogu.com.cn/problem/P3372)。

再来看一下那两个操作。

那不就是树状数组吗？

众所周知，可以建两个树状数组，维护一个前缀和就可以顺利的解决线段树 1 的所有操作。

不清楚这种方法的，可以看[这篇](https://www.luogu.com.cn/blog/Start-Dash/P3372)题解。

然后就是写两个可持久化线段树，维护一个前缀和。

然后记录每个时间戳对应的两个根。

在两棵树上查询就好啦。

代码可能有一点长，但总体还是很清晰的啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m;
struct node{
	node *l,*r;
	int val;
}*root[2][signed(1e6)+10];
int tot[2];
node *null;
void _init(){
	tot[0]=tot[1]=0;
	null=new node;
	null->l=null->r=null;
	null->val=0;
}
node *build(int l,int r){
	if(l==r){
		node *p=new node;
		p->l=p->r=null;
		p->val=0;
		return p;
	}
	int mid=l+r>>1;
	node *p=new node;
	p->l=build(l,mid),p->r=build(mid+1,r);
	p->val=p->l->val+p->r->val;
	return p; 
}
void creat(){
	_init();
	root[0][tot[0]]=build(0,n);
	root[1][tot[1]]=build(0,n);
}
inline node *update(int x,int k,node *p,int l=0,int r=n){
	if(l==r && r==x){
		node *q=new node;
		q->l=q->r=null;
		q->val=p->val+k;
		return q;
	}
	node *q=new node;
	q->l=p->l,q->r=p->r;
	int mid=l+r>>1;
	if(x>=l && x<=mid) q->l=update(x,k,q->l,l,mid);
	if(x>mid && x<=r) q->r=update(x,k,q->r,mid+1,r); 
	q->val=q->l->val+q->r->val;
	return q;
}
inline int ask(int x,int y,node *p,int l=0,int r=n){
	if(l>=x && y>=r) return p->val;
	int mid=l+r>>1;
	int tot=0;
	if(x<=mid) tot+=ask(x,y,p->l,l,mid);
	if(y>mid) tot+=ask(x,y,p->r,mid+1,r);
	return tot;
}
int a[signed(1e6)+10],tim,s[signed(1e6)+10];
int w[signed(1e6)+10];
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) a[i]=read(),s[i]=s[i-1]+a[i];
	creat();
	while(m--){
		char ch;
		cin>>ch;
		if(ch=='C'){
			int l=read(),r=read(),k=read();
			root[0][++tot[0]]=update(l,k,root[0][w[tim]]);
			root[0][tot[0]+1]=update(r+1,-k,root[0][tot[0]]),tot[0]++;
			root[1][++tot[1]]=update(l,l*k,root[1][w[tim]]);
			root[1][tot[1]+1]=update(r+1,-(r+1)*k,root[1][tot[1]]),tot[1]++;
			w[++tim]=tot[0];
		}
		if(ch=='Q'){
			int l=read(),r=read();
			int ans=s[r]+(r+1)*ask(0,r,root[0][w[tim]])-ask(0,r,root[1][w[tim]]);
			ans-=(s[l-1]+l*ask(0,l-1,root[0][w[tim]])-ask(0,l-1,root[1][w[tim]]));
			cout<<ans<<"\n";
		}
		if(ch=='H'){
			int l=read(),r=read(),t=read();
			int ans=s[r]+(r+1)*ask(0,r,root[0][w[t]])-ask(0,r,root[1][w[t]]);
			ans-=(s[l-1]+l*ask(0,l-1,root[0][w[t]])-ask(0,l-1,root[1][w[t]]));
			cout<<ans<<"\n";
		}
		if(ch=='B'){
			tim=read();
			root[0][++tot[0]]=root[0][w[tim]],root[1][++tot[1]]=root[1][w[tim]];
		}
	}
	return 0;
} 
```
这种方法时间复杂度与空间复杂度都较高。

并且有点难理解。

可能遇见这种问题首选不是这种方法。

---

## 作者：Sangber (赞：2)

### 题目描述
给定一段长度为 $N$ 的序列 $a$ 以及 $M$ 次操作，操作有以下几种：
+ `C l r d` ：将区间 $[l,r]$ 中的数都加上 $d$
+ `Q l r` ：查询当前时间戳区间 $[l,r]$ 中所有数的和
+ `H l r t` ：查询时间戳为 $t$ 时，区间 $[l,r]$ 中所有数的和
+ `B t` ：将当前时间戳重置为 $t$

对于每一次询问操作，输出一行对应的答案。  
时间戳初始值为 $0$  
数据范围：  
$1\leq N,M\leq 10^5$  
然后要开 `long long`

----
### 基本思路
主席树的一道比较模板的题。。。  
原谅我不想讲细节（其实代码里面写的还可以）  
关于标记永久化的一些实现细节，我是参考的《信息学奥赛一本通 $\cdot$ 提高篇》

----
### 细节注意事项
+ `long long`一定要开
+ 细节不要写挂，数据结构题还是有**点**难调的
+ 应该不会有人像我一样搞错输入顺序吧。。。

----
### 参考代码
```cpp
/*--------------------------------
  Author: The Ace Bee
  Blog: www.cnblogs.com/zsbzsb
  This code is made by The Ace Bee
--------------------------------*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#define rg register
using namespace std;
template < typename T > inline void read(T& s) {
	s = 0; int f = 0; char c = getchar();
	while (!isdigit(c)) f |= (c == '-'), c = getchar();
	while (isdigit(c)) s = s * 10 + (c ^ 48), c = getchar();
	s = f ? -s : s;
}

typedef long long LL;
const int _ = 100010;

int n, m, a[_];
int tot, rt[_], lc[_ << 5], rc[_ << 5];
LL sum[_ << 5], add[_ << 5];

inline void build(int& p, int l = 1, int r = n) {
	p = ++tot;
	if (l == r) return read(sum[p]);
	int mid = (l + r) >> 1;
	build(lc[p], l, mid), build(rc[p], mid + 1, r);
	sum[p] = sum[lc[p]] + sum[rc[p]];
}

inline void update(int& p, int q, int ql, int qr, int v, int l = 1, int r = n) {
	lc[p = ++tot] = lc[q], rc[p] = rc[q], add[p] = add[q], sum[p] = sum[q];
	if (ql <= l && r <= qr) { add[p] += v; return; }
	int mid = (l + r) >> 1;
	if (ql <= mid) update(lc[p], lc[q], ql, qr, v, l, mid);
	if (qr > mid) update(rc[p], rc[q], ql, qr, v, mid + 1, r);
	sum[p] += 1ll * v * (min(qr, r) - max(ql, l) + 1);
}

inline LL query(int p, int ql, int qr, int l = 1, int r = n) {
	if (ql <= l && r <= qr) return sum[p] + 1ll * add[p] * (r - l + 1);
	int mid = (l + r) >> 1; LL res = 0;
	if (ql <= mid) res += query(lc[p], ql, qr, l, mid);
	if (qr > mid) res += query(rc[p], ql, qr, mid + 1, r);
	return res + 1ll * add[p] * (min(qr, r) - max(ql, l) + 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
#endif
	read(n), read(m), build(rt[0]);
	int tim = 0;
	for (rg int i = 1; i <= m; ++i) {
		char s[5]; scanf("%s", s);
		if (s[0] == 'B') read(tim), tot = rt[tim + 1] - 1;
		else if (s[0] == 'C') { int ql, qr, v;
			read(ql), read(qr), read(v), ++tim;
			update(rt[tim], rt[tim - 1], ql, qr, v);
		} else if (s[0] == 'Q') { int ql, qr;
			read(ql), read(qr);
			printf("%lld\n", query(rt[tim], ql, qr));
		} else if (s[0] == 'H') { int t, ql, qr;
			read(ql), read(qr), read(t);
			printf("%lld\n", query(rt[t], ql, qr));
		}
	}
	return 0;
}

```

---

## 作者：hongzy (赞：2)

这题先上来写一个主席树，像线段树那样打区间加标记，但是马上就发现不能`pushdown`。

因为：主席树是有共用子结点的，直接把标记传递下去会影响答案的正确性，如果新建一大堆结点那复杂度就大到飞起~~还不如暴力跑得快~~。所以需要使用**标记永久化**。

标记永久化就是每个结点维护一个`add`标记，表示这个区间每个数加上了$x$。每个结点维护的区间和`s`，通过子结点的`s`之和加上左右儿子的的`add`标记乘以区间长度来维护。这就是说，一个结点对应的区间被整体加上一个值，从根到这个结点的路径上所有结点的`s`都会被更新，而对它子树内的结点的影响等到询问的时候再考虑。

细节见代码，询问的时候用如下方式写会比较简单，不需要判区间交的长度。

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int n, m, a[N];
int T[N], id, L[N << 6], R[N << 6];
ll s[N << 6], add[N << 6];

void build(int &rt, int l, int r) {
	rt = ++ id;
	if(l < r) {
		int mid = (l + r) >> 1;
		build(L[rt], l, mid);
		build(R[rt], mid + 1, r);
		s[rt] = s[L[rt]] + s[R[rt]];
	} else s[rt] = a[l];
}

void update(int &rt, int pre, int l, int r, int ql, int qr, int x) {
	if(l > qr || r < ql) return ;
	rt = ++ id; L[rt] = L[pre]; R[rt] = R[pre];
	s[rt] = s[pre]; add[rt] = add[pre];
	if(ql <= l && r <= qr) { add[rt] += x; return ; }
	int mid = (l + r) >> 1;
	update(L[rt], L[pre], l, mid, ql, qr, x);
	update(R[rt], R[pre], mid + 1, r, ql, qr, x);
	s[rt] = s[L[rt]] + s[R[rt]] + (mid - l + 1) * add[L[rt]] + (r - mid) * add[R[rt]];
}

ll query(int rt, int l, int r, int ql, int qr) {
	if(ql == l && qr == r) return add[rt] * (r - l + 1) + s[rt];
	ll val = add[rt] * (qr - ql + 1);
	int mid = (l + r) >> 1;
	if(qr <= mid) return val + query(L[rt], l, mid, ql, qr);
	if(ql > mid) return val + query(R[rt], mid + 1, r, ql, qr);
	return val + query(L[rt], l, mid, ql, mid) + query(R[rt], mid + 1, r, mid + 1, qr);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", a + i);
	static char op[5];
	int tnow = 0; build(T[0], 1, n);
	for(int l, r, d, i = 1; i <= m; i ++) {
		scanf("%s", op);
		if(* op == 'C') {
			scanf("%d%d%d", &l, &r, &d);
			update(T[tnow + 1], T[tnow], 1, n, l, r, d);
			tnow ++;
		}
		if(* op == 'Q') {
			scanf("%d%d", &l, &r);
			printf("%lld\n", query(T[tnow], 1, n, l, r));
		}
		if(* op == 'H') {
			scanf("%d%d%d", &l, &r, &d);
			printf("%lld\n", query(T[d], 1, n, l, r));
		}
		if(* op == 'B') {
			scanf("%d", &tnow);
		}
	}
	return 0;
}
```

---

## 作者：bztMinamoto (赞：2)

先打个广告：[blog](https://www.cnblogs.com/bztMinamoto/p/9408649.html)

辛辛苦苦调了半天终于到rank1了（✿✿ヽ(°▽°)ノ✿）~~（虽然只是抄着题解并卡了卡常）~~

原来……主席树真的能做可持久化的啊……花了一个下午才搞明白……

先考虑一下，如果直接每一次修改的话，一共要修改$r-l+1$次，空间复杂度绝对爆炸

然后考虑一下线段树的打懒标记，可不可以套到主席树上来？

我们发现可以这么做，于是每一次修改区间时，如果区间相等，直接打上标记，等到查询的时候，再把标记给加上去。如果不相等，直接让区间和加上要修改的总和就是

ps：B操作更改时间的时候可以直接把$cnt$改成$rt[t+1]-1$，这样的话可以回收空间

upd:感谢@Vivian_IMproved提供的Hack数据，然后发现自己的代码忘记特判$B$操作之后时间戳不变的情况了，现在的代码应该没问题了qwq
```
//minamoto
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=100005,M=N*30;
int n,m,cnt,rt[N];
int L[M],R[M];ll sum[M],add[M];
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){
    #define num ch-'0'
    char ch;bool flag=0;ll res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
void build(int &now,int l,int r){
    add[now=++cnt]=0;
    if(l==r) return (void)(sum[now]=read());
    int mid=(l+r)>>1;
    build(L[now],l,mid);
    build(R[now],mid+1,r);
    sum[now]=sum[L[now]]+sum[R[now]];
}
void update(int last,int &now,int l,int r,int ql,int qr,int x){
    now=++cnt;
    L[now]=L[last],R[now]=R[last],add[now]=add[last],sum[now]=sum[last];
    sum[now]+=1ll*x*(qr-ql+1);
    if(ql==l&&qr==r) return (void)(add[now]+=x);
    int mid=(l+r)>>1;
    if(qr<=mid) update(L[last],L[now],l,mid,ql,qr,x);
    else if(ql>mid) update(R[last],R[now],mid+1,r,ql,qr,x);
    else return (void)(update(L[last],L[now],l,mid,ql,mid,x),update(R[last],R[now],mid+1,r,mid+1,qr,x));
}
ll query(int now,int l,int r,int ql,int qr){
    if(l==ql&&r==qr) return sum[now];
    int mid=(l+r)>>1;
    ll res=1ll*add[now]*(qr-ql+1);
    if(qr<=mid) res+=query(L[now],l,mid,ql,qr);
    else if(ql>mid) res+=query(R[now],mid+1,r,ql,qr);
    else res+=query(L[now],l,mid,ql,mid)+query(R[now],mid+1,r,mid+1,qr);
    return res;
}
int main(){
//    freopen("testdata.in","r",stdin);
    n=read(),m=read();
    cnt=-1;
    build(rt[0],1,n);
    int now=0,x;
    while(m--){
        char ch;int l,r,x;
        while(!isupper(ch=getc()));
        switch(ch){
            case 'C':{
                l=read(),r=read(),x=read();
                ++now;
                update(rt[now-1],rt[now],1,n,l,r,x);
                break;
            }
            case 'Q':{
                l=read(),r=read();
                printf("%lld\n",query(rt[now],1,n,l,r));
                break;
            }
            case 'H':{
                l=read(),r=read(),x=read();
                printf("%lld\n",query(rt[x],1,n,l,r));
                break;
            }
            case 'B':{
                x=read();
                if(x!=now)now=x,cnt=rt[now+1]-1;
                break;
            }
        }
    }
    return 0;
}
```

---

## 作者：DAMDAM (赞：1)

想到的不是可持久化线段树与标记永久化，而是可持久化平衡树。

所以想用这个做法，首先你得会平衡树、可持久化平衡树、文艺平衡树与可持久化文艺平衡树，最好再练几道题。

做法与[模板题](https://www.luogu.com.cn/problem/P5055)一样的，不过把翻转标记换成了加法标记。

区间加法怎么打标记呢？

非常显然的有

```cpp
void TagAdd(Vertex *p, const ll &c) {
    p && (p->add += c, p->sum += c * p->siz, p->val += c);
}
```

即我们把该节点本身的值加上 $c$，该节点的标记加上 $c$，区间和加上 $c\times siz$。

那么之后只是裸的维护可持久化平衡树了。

建树用了 $\Theta(n)$ 写法。

维护当前时间戳，可以用一个表示时间的变量来表示。

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;
struct Vertex {
    ll val = 0, sum = 0, add = 0;
    int siz = 0, cnt = 0;
    unsigned rank = 0;
    Vertex *son[2] = {};
    Vertex(const ll &__val = 0) { val = sum = __val, son[add = 0] = son[siz = cnt = 1] = nullptr; }
    Vertex* Copy() { return this ? &(*(new Vertex) = *this) : nullptr; }
} *rt[maxn];

int siz(Vertex *p) { return p ? p->siz : 0; }

ll sum(Vertex *p) { return p ? p->sum : 0; }

void Pushup(Vertex *p) { p && (p->siz = siz(*p->son) + siz(p->son[1]) + p->cnt, p->sum = sum(*p->son) + sum(p->son[1]) + p->val); }

void Maintain(Vertex *&p) { p && (p = p->Copy()); }

void TagAdd(Vertex *p, const ll &c) {
    p && (p->add += c, p->sum += c * p->siz, p->val += c);
}

void Pushdown(Vertex *p) {
    if (p && p->add) {
        Maintain(*p->son), Maintain(p->son[1]);
        p->add && (TagAdd(*p->son, p->add), TagAdd(p->son[1], p->add), p->add = 0);
    }
}

void SplitRank(const int &k, Vertex *&u, Vertex *&v, Vertex *p) {
    if (!p) return void(u = v = nullptr);
    Pushdown(p);
    if (k <= siz(*p->son)) v = p->Copy(), SplitRank(k, u, v->son[0], p->son[0]), Pushup(v);
    else u = p->Copy(), SplitRank(k - siz(*p->son) - p->cnt, u->son[1], v, p->son[1]), Pushup(u);
}

void Merge(Vertex *u, Vertex *v, Vertex *&p) {
    if (!u || !v) return void(p = u ? u : v);
    Pushdown(u), Pushdown(v);
    if (u->rank >= v->rank) p = v, Merge(u, p->son[0], p->son[0]);
    else p = u, Merge(p->son[1], v, p->son[1]);
    Pushup(p);
}

int n;
ll a[maxn];
void Build(const int &s = 1, const int &t = n, Vertex *&v = *rt, Vertex *u = nullptr) {
    if (s > t) return;
    int mid = s + ((t - s) >> 1);
    v = new Vertex{a[mid]}, v->rank = u ? u->rank + 1 : 0;
    if (s == t) return;
    Build(s, mid - 1, v->son[0], v), Build(mid + 1, t, v->son[1], v);
    Pushup(v);
}

void Add(const int &l, const int &r, const ll &x, Vertex *u, Vertex *&v) {
    Vertex *a = nullptr, *b = nullptr, *c = nullptr;
    SplitRank(l - 1, a, c, u), SplitRank(r - l + 1, b, c, c);
    TagAdd(b, x);
    Merge(b, c, c), Merge(a, c, v);
}

ll Get(const int &l, const int &r, Vertex *u) {
    Vertex *a = nullptr, *b = nullptr, *c = nullptr;
    SplitRank(l - 1, a, c, u), SplitRank(r - l + 1, b, c, c);
    ll reply = b->sum;
    return Merge(b, c, c), Merge(a, c, u), reply;
}

int m, now;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    Build();
    char c;
    for (int l, r, x; m; --m) {
        scanf(" %c%d", &c, &l);
        if (c == 'B') now = l;
        else {
            scanf("%d", &r);
            if (c == 'Q') printf("%lld", Get(l, r, rt[now])), putchar(10);
            else {
                scanf("%d", &x);
                if (c == 'H') printf("%lld", Get(l, r, rt[x])), putchar(10);
                else Add(l, r, x, rt[now], rt[now + 1]), ++now;
            }
        }
    }
    return 0;
}
```

---

