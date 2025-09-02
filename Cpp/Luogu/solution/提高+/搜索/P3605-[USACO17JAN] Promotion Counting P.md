# [USACO17JAN] Promotion Counting P

## 题目描述

奶牛们又一次试图创建一家创业公司，还是没有从过去的经验中吸取教训——牛是可怕的管理者！

为了方便，把奶牛从 $1\sim n$ 编号，把公司组织成一棵树，1 号奶牛作为总裁（这棵树的根节点）。除了总裁以外的每头奶牛都有一个单独的上司（它在树上的 “双亲结点”）。  

所有的第 $i$ 头牛都有一个不同的能力指数 $p_i$，描述了她对其工作的擅长程度。如果奶牛 $i$ 是奶牛 $j$ 的祖先节点，那么我们我们把奶牛 $j$ 叫做 $i$ 的下属。

不幸地是，奶牛们发现经常发生一个上司比她的一些下属能力低的情况，在这种情况下，上司应当考虑晋升她的一些下属。你的任务是帮助奶牛弄清楚这是什么时候发生的。简而言之，对于公司的中的每一头奶牛 $i$，请计算其下属 $j$ 的数量满足 $p_j > p_i$。


## 说明/提示

 对于 $100\%$ 的数据，$1\le n \le 10^5$，$1 \le p_i \le 10^9$。

## 样例 #1

### 输入

```
5
804289384
846930887
681692778
714636916
957747794
1
1
2
3```

### 输出

```
2
0
1
0
0```

# 题解

## 作者：George1123 (赞：164)

[${\color{#aa66ee}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.com.cn/blog/Wendigo/)

[P3605 【\[USACO17JAN\]Promotion Counting晋升者计数】](https://www.luogu.com.cn/problem/P3605)

### 此题算法:树状数组+$dfs$

这仔细一想是道比较纯的树状数组题

~~你看了粉兔的题解后会发现那个$a[]$数组尤为鬼畜~~

![](https://s2.ax1x.com/2019/12/06/QYYvVA.jpg)

>(手画抨击粉兔)

**我这里有最容易理解的算法，走过路过不要错过**

首先将拿到的数组**离散化**(如下)

```cpp
for(int i=1;i<=n;i++)
	scanf("%d",p+i),b[i]=p[i];
sort(b+1,b+n+1); //unique什么的真的没啥用
for(int i=1;i<=n;i++)
	p[i]=lower_bound(b+1,b+n+1,p[i])-b;
```
加完**单向边**后$dfs$：

若令$ans[]$表示节点的最终答案，则有

>**$ans[x]=x$的下属中比$x$强的**

>**$~~~~~~~~~~~~=$树状数组中加了$x$下属后比$x$强的$-$原来就比$x$强的**

所以$dfs$可以写成这样：

```cpp
void dfs(int x){//x为节点，p[]为离散化后的数组
	//hx为值域树状数组
	ans[x]=-(hx.fsum(n)-hx.fsum(p[x]));//原来比x强的
	for(auto i:g[x]) dfs(i);     //加x的下属
	ans[x]+=(hx.fsum(n)-hx.fsum(p[x]));//后来比x强的
	hx.fix(p[x],1); //加x自己
}
```
![](https://s2.ax1x.com/2019/12/06/QYUCng.jpg)




## 以下是代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,p[N],b[N],ans[N];
vector<int> g[N];
struct hxtree{ //树状数组
	int v[N];
	int flow(int x){
		return x&-x;
	}
	void fix(int x,int y){
		for(;x<=n;x+=flow(x))
			v[x]+=y;
	}
	int fsum(int x){
		int ret=0;
		for(;x;x-=flow(x))
			ret+=v[x];
		return ret;
	}
}hx;
void dfs(int x){//x为节点，p[]为离散化后的数组
	//hx为值域树状数组
	ans[x]=-(hx.fsum(n)-hx.fsum(p[x]));//原来比x强的
	for(auto i:g[x]) dfs(i);     //加x的下属
	ans[x]+=(hx.fsum(n)-hx.fsum(p[x]));//后来比x强的
	hx.fix(p[x],1); //加x自己
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i),b[i]=p[i];
	sort(b+1,b+n+1); //对萌新很友好的两步离散化
	for(int i=1;i<=n;i++)
		p[i]=lower_bound(b+1,b+n+1,p[i])-b;
	// for(int i=1;i<=n;i++)
	// 	printf("%d%c",p[i]," \n"[i==n]);
	for(int i=2;i<=n;i++){
		int fa;
		scanf("%d",&fa);
		g[fa].push_back(i);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]); //1+1=2
	return 0;
}
```

这题就像身边的“萌新”向自己学习，

结果不久他们就分到了省选班，而自己越来越弱。

**写题解不易，喜欢就点个赞吧。**

谢谢大家! !








---

## 作者：小粉兔 (赞：87)

短码大师 #(滑稽)

先对权值离散化，然后对于每一个节点，我们需要统计它的子树中比它大的节点的个数。

所以为了方便统计，离散化可以大的在前。

然后建一棵权值树状数组，在递归子树之前先把答案减掉，递归完子树后再把新的答案加回来，这样结果就是正确的了。

```cpp
#include<cstdio>
#include<algorithm>
#define F(i,a,b) for(int i=a;i<=b;++i)
#define eF(i,u) for(int i=h[u];i;i=nxt[i])
int n,q;
int a[100001],O[100001],Ans[100001],b[100001];
inline void I(int x){for(;x<=n;++b[x],x+=x&-x);}
inline int Q(int x){int sum=0;for(;x;sum+=b[x],x-=x&-x);return sum;}
int h[100001],nxt[100001],to[100001],tot;
inline void ins(int x,int y){nxt[++tot]=h[x];to[tot]=y;h[x]=tot;}
inline bool cmp(int p1,int p2){return a[p1]>a[p2];}
void dfs(int u){
	Ans[u]=-Q(a[u]);
	eF(i,u) dfs(to[i]);
	Ans[u]+=Q(a[u]);
	I(a[u]);
}
int main(){
	scanf("%d",&n);
	F(i,1,n) scanf("%d",a+i), O[i]=i;
	std::sort(O+1,O+n+1,cmp);
	F(i,1,n) a[O[i]]=i;
	int x;
	F(i,2,n) scanf("%d",&x), ins(x,i);
	dfs(1);
	F(i,1,n) printf("%d\n",Ans[i]);
	return 0;
}
```

可能难理解，但是至少我的码很短 #(滑稽)

---

## 作者：AC_Panda (赞：25)

~~好像这么一个奇奇怪怪的写法还没有人写过并且表现还不错~~

# 题意：

求某节点子树内比该节点的点权大的点的个数

# 分析：

1.一根链的情况：树状数组求逆序数

序列逆序数定义：$i<j$ 且 $p_i>p_j$ 的点对个数

当 $j$ 确定时，统计比 $p_j$ 大的数的个数（离散化+树状数组）（顺序则可以保证 $i<j$）
	
2.一棵树的情况：

树上逆序数定义：$y$ 属于 $x$ 的子树（不包含 $x$ ) 且 $p_y>p_x$ 的点对个数

$dfs$ 序：每个节点在dfs深度优先遍历中的进出栈的时间序列。

重要性质：每个点的子树都能化为一段**连续**的区间

令 $\left\{{d_n}\right\}$ 为该树的 $dfs$ 序，$dfn_i$ 表示点 $i$ 在 $dfs$ 序中的位置，$siz_i$ 表示 $i$ 的子树（含 $i$ ）大小

当 $j$ 确定时：


只需统计$i\in\left[{dfn_j+1,dfn_j+siz_j-1}\right]$，且 $p_i>p_j$ 的点的个数

则只需将各点以点权为关键字从小到大排序，统计其子树区间内比其大的点的个数：

令 $num_i$ 表示排序后点权第 $i$ 小的点， $b_i$ 表示 $d_i$ 是否比当前的点权大（初始化为 $1$ ，每一轮统计完将其改为 $0$ ，因为有序所以能保证正确）

则有 $ans_{num_x}= \sum\limits_{i=dfn_{num_x}+1}^{dfn_{num_x}+siz_{num_x}-1}b_i $

# 实现：

只加父节点到子节点的单向边便于 $dfs$

$dfs$ 预处理 $\left\{dfn_n\right\}$ 和 $\left\{siz_n\right\}$

构造 $b$ 数组的树状数组 $S$，因其初始值均为 $1$，故可令 $S_i=lowbit(i)$

求出 $ans$ 数组

时间复杂度 $O(nlogn)$ ，~~常数小极了~~

# 代码
~~丑爆了~~
```
#include<bits/stdc++.h>
#define F(a,b) for(int i=a;i<=b;++i)
#define eF(u) for(int i=head[u],v=edge[i].to;i;i=edge[i].next,v=edge[i].to)
using namespace std;
int n,dfn[100001],p[100001],faz[100001],siz[100001],head[100001],xb,cnt,b[100001],c[100001],ans[100001];
int lowbit(int x)
{
	return x&(-x);
}
struct pyh
{
	int to,next;
}edge[200001];
struct pyhh
{
	int w,num;
}d[100001];//d[i].num即num[i]，此处为了排序……
void add(int st,int ed)
{
	edge[++xb].to=ed;
	edge[xb].next=head[st];
	head[st]=xb;
}
void dfs(int u)
{
	siz[u]=1;
	dfn[u]=++cnt;
	eF(u)
	{
		dfs(v);
		siz[u]+=siz[v];
	}
	return;
}
bool cmp(pyhh aa,pyhh bb)
{
	return aa.w<bb.w;
}
int query(int l,int r)
{
	if(l>r)return 0;
	l--;
	int sum=0;
	while(r>l)sum+=c[r],r-=lowbit(r);
	while(l>r)sum-=c[l],l-=lowbit(l);
	return sum;
}//树状数组查询优化
void update(int x)
{
	b[x]=0;
	while(x<=n)
	{
		c[x]--;
		x+=lowbit(x);
	}
}
int main()
{
	scanf("%d",&n);
	F(1,n)
	{
		scanf("%d",&d[i].w); 
		d[i].num=i;
		b[i]=1;
	}
	F(2,n)
	{
		scanf("%d",&faz[i]);
		add(faz[i],i);
	}
	dfs(1);
	sort(d+1,d+n+1,cmp);
	F(1,n)
	{
		c[i]=lowbit(i);
	}
	F(1,n)
	{
		ans[d[i].num]=query(dfn[d[i].num]+1,dfn[d[i].num]+siz[d[i].num]-1);
		update(dfn[d[i].num]);
	}
	F(1,n)cout<<ans[i]<<endl;
}
```



---

## 作者：wuzhaoxin (赞：17)

## 离散化+线段树合并（裸）


------------

### 线段树合并
#### 线段树合并，就是将已有的两棵线段树合并为一棵，相同位置的信息整合到一起，通常是权值线段树
#### 比较裸的，就是将一棵线段树的每一个位置取出来插入另一棵中
#### 但比较高效的线段树合并可以参照可并堆的合并方式

- 线段树合并的原理十分简单，具体步骤如下：
- 对于两颗树的节点u和v
- ①如果u为空，返回v
- ②如果v为空，返回u
- ③否则，新建节点t，整合u和v的信息，然后递归合并u和v的左右子树
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace segment_tree_merge {
	int lc[3000001] = {0}, rc[3000001] = {0}, tot = 0;
	int v[3000001] = {0}, l[3000001], r[3000001];
	int root[100001];
	void push_up(int p) {
		v[p] = v[lc[p]]+v[rc[p]];
	}
	void build(int &p, int le, int ri, int x) {
		p = ++ tot;
		l[p] = le;
		r[p] = ri;
		if(le == ri) {
			v[p]=1;
			return;
		}
		int mid = (le + ri) >> 1;
		if(x <= mid)build(lc[p], le, mid, x);
		else build(rc[p], mid + 1, ri, x);
		push_up(p);
	}
	void add(int p, int x) {
		if(l[p] == r[p]) {
			v[p] ++;
			return;
		}
		int mid = (l[p] + r[p]) >> 1;
		if(x <= mid)add(lc[p], x);
		else add(rc[p], x);
		push_up(p);
	}
	int merge(int x, int y) {
		if(!x)return y;
		if(!y)return x;
		if(l[x] == r[x])return v[x] += v[y],x;
		lc[x]=merge(lc[x], lc[y]);
		rc[x]=merge(rc[x], rc[y]);
		push_up(x);
		return x;
	}
	int query(int p, int le, int ri) {
		if(p == 0)return 0;
		if(l[p] == le && r[p] == ri)return v[p];
		int mid = (l[p] + r[p]) >> 1;
		if(le <= mid)
			if(ri > mid)return query(lc[p], le, mid) + query(rc[p], mid + 1, ri);
			else return query(lc[p], le, ri);
		return query(rc[p], le, ri);
	}
}
#define stm segment_tree_merge
int n;
int a[100001];
int hs[100001];
int fa[100001];
vector<int>ver[100001];
int ans[100001];
void dfs(int x) {
	for(int i = ver[x].size() - 1; i >= 0; i --) {
		dfs(ver[x][i]);
		stm::root[x] = stm::merge(stm::root[x], stm::root[ver[x][i]]);
	}
	ans[x]=stm::query(stm::root[x], a[x] + 1, n + 1);
}
int main() {
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i ++) {
		
		cin>>a[i];
		hs[i] = a[i];
	}
	sort(hs + 1, hs + n + 1);
	for(int i = 1; i <= n; i ++)
		a[i] = lower_bound(&hs[1], &hs[n + 1], a[i]) - hs,
		stm::build(stm::root[i], 1, n + 1, a[i]);
	for(int i = 2; i <= n; i ++) {
		cin>>fa[i];
		ver[fa[i]].push_back(i);
	}
	dfs(1);
	for(int i = 1; i <= n; i ++)
		cout<<ans[i] <<endl;
	return 0;
}
```
（tab被吃了）

---

## 作者：Victorique (赞：11)

主席树。。。

这题说白了就是一静态区间求比数k大的数的个数。

很容易考虑到主席树。

首先预处理，dfs把dfs序和每个点的size求出来。

直接上主席树求解即可。

不想离散化可以动态开点。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+7;
#define mid ((l+r)>>1)
int L[MAXN<<5],R[MAXN<<5],T[MAXN],st[MAXN<<5],n,m,cnt,at[MAXN];
int size[MAXN],dfn[MAXN],sz;
int a[MAXN],b[MAXN],t;
vector<int> edge[MAXN];
inline int update(int pre,int l,int r,int x,int k)
{
	int rt=++sz;
	L[rt]=L[pre];R[rt]=R[pre];st[rt]=st[pre]+1;
	if(l==r) return rt;
	if(x<=mid) L[rt]=update(L[pre],l,mid,x,k);
	else R[rt]=update(R[pre],mid+1,r,x,k);
	return rt;
}
inline int query(int u,int v,int l,int r,int dl,int dr)
{
	int sum=0;
	if(dl<=l&&r<=dr) return st[v]-st[u];
	if(dl<=mid) sum+=query(L[u],L[v],l,mid,dl,dr);
	if(dr>mid) sum+=query(R[u],R[v],mid+1,r,dl,dr);
	return sum;
}
inline void dfs(int u,int fa)
{
	size[u]=1;dfn[u]=++cnt;at[cnt]=u;
	for(int i=0;i<edge[u].size();i++){
		int v=edge[u][i];
		if(v!=fa) dfs(v,u);
		size[u]+=size[v];
	}
}
inline int read()
{
    int x=0,c=1;
    char ch=' ';
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    while(ch=='-')c*=-1,ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*c;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=b[i]=read();
	for(int i=2;i<=n;i++){edge[read()].push_back(i);}
	dfs(1,0);
	sort(b+1,b+n+1);
	t=unique(b+1,b+n+1)-b-1;
	
	for(int i=1;i<=n;i++){
		int x=at[i];
		int k=lower_bound(b+1,b+t+1,a[x])-b;
		T[i]=update(T[i-1],1,t,k,1);
	}
	for(int i=1;i<=n;i++){
		int k=lower_bound(b+1,b+t+1,a[i])-b;
		if(size[i]==1) puts("0");else printf("%d\n", query(T[dfn[i]],T[dfn[i]+size[i]-1],1,t,k+1,t));
	}
}
```

---

## 作者：sjkmost (赞：10)

题意就是给出一个点权不相同的树然后问你每个结点子树中权值大于它的节点个数。

我们可以先搞出一个DFS序来，然后就是静态区间rank查询了。

对于静态区间rank查询，我们可以先把所有的询问（结点）按权值排序，然后依次加入树状数组里面，每次加入之前查询[l,r]的区间和。

时间复杂度$O(nlogn)$。

```cpp
const int MAXN = 100000 + 5;

int hed[MAXN], nxt[MAXN << 1], tot[MAXN << 1], val[MAXN], fa[MAXN], L[MAXN], R[MAXN], bit[MAXN], ask[MAXN];
pair < int, int > point[MAXN];

inline void AddEdge(int x, int y) { //加边 
    static int cnt;
    ++ cnt;
    tot[cnt] = y;
    nxt[cnt] = hed[x];
    hed[x] = cnt;
}

void DFS(int u) {
    static int cnt;
    ++ cnt;
    L[u] = cnt;  //更新结点u在DFS序中的映射 
    point[cnt] = make_pair(val[u], u);  //权值与结点编号，方便排序后查找DFS序 
    int v;
    for (int k = hed[u]; k; k = nxt[k]) {  //DFS 
        v = tot[k];
        if (v != fa[u])
            DFS(v);
    }
    R[u] = cnt;  //DFS结束后的计数器值就是结点u子树在DFS序中的范围 
}

int n;

#define lowbit(x) (x) & -(x) 
inline void Modify(int i) {  //树状数组操作 
    for (; i <= n; i += lowbit(i))
        ++ bit[i]; 
}

inline int Query(int i) {
    int k = 0;
    for (; i; i -= lowbit(i))
        k += bit[i];
    return k;
}

inline bool Comp(const pair < int, int > &a, const pair < int, int > &b) {  //按权值从大到小排序 
    return a.first > b.first;
}

int main() {
    get, n;
    For(i, 1, n)
        get, val[i];
    int dx;
    For(i, 2, n) {
        get, dx;
        fa[i] = dx;
        AddEdge(dx, i);
        AddEdge(i, dx);
    }
    DFS(1);  //先DFS一遍找出DFS序 
    sort(point + 1, point + n + 1, Comp);  //排序 
    For(i, 1, n) {
        ask[point[i].second] = Query(R[point[i].second]) - Query(L[point[i].second] - 1);  //在当前结点之前插入树状数组的一定是比当前结点权值大的，直接查找即可 
        Modify(L[point[i].second]);
    }
    For(i, 1, n)
        put, ask[i], '\n';
    return 0;
}
```

---

## 作者：Drug__Lover (赞：9)

**树状数组+离散化**

**在树上求一下逆序对的个数**

**在求右儿子的逆序对的个数时由于是先添加的左儿子的个数**

**所以这时右儿子的个数会有左儿子的一部分**

**我们需要记录一个last**

**来记录右儿子的改变值**

**这样一减就是真正的右儿子的逆序对的个数了**


```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstdio>
#define maxn 100100
using namespace std;
struct node
{
    int next,to;
}e[maxn*2];
int cnt;
int head[maxn];
int n;
int c[maxn];
int fa[maxn];
int num[maxn];
int add(int u,int v)
{
    e[++cnt].next=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
int add_tree(int x,int k)
{
    for(int i=x;i<=n;i+=i&(-i)) c[i]+=k;
}
int query(int x)
{
    int sum=0;
    for(int i=x;i>0;i-=i&(-i)) sum+=c[i];
    return sum;
}
struct NOde
{
    int w,place;
}a[maxn];
int cmp1(NOde x,NOde y)
{
    return x.w<y.w;
}
int cmp2(NOde x,NOde y)
{
    return x.place<y.place;
}
int dfs(int now)
{
    add_tree(a[now].w,1);
    int last=query(n)-query(a[now].w);
    for(int i=head[now];i;i=e[i].next)
    {
        int to=e[i].to;
        if(fa[now]!=to)
        {
            dfs(to);
        }
    }
    num[now]+=query(n)-query(a[now].w)-last;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].w);
        a[i].place=i;
    }
    sort(a+1,a+1+n,cmp1);
    for(int i=1;i<=n;i++) a[i].w=i;
    sort(a+1,a+1+n,cmp2);
    for(int i=2;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        add(x,i);
        add(i,x);
        fa[i]=x;
    }
    dfs(1);
    for(int i=1;i<=n;i++) printf("%d\n",num[i]);
    return 0;
}
```

---

## 作者：ChrisK (赞：7)

~~怎么最近老写线段树合并~~

权值线段树加合并。

需要离散化。

查询就查当前节点的线段树。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int cnt,n,vl[maxn],fa[maxn],c[maxn],tot,rt[maxn],ans[maxn];
struct tree{
    int lc,rc,dt,tg;
}t[maxn*40];
vector<int> q[maxn];
inline void pushup(int p){
    t[p].dt=t[t[p].lc].dt+t[t[p].rc].dt;

}
inline int insert(int p,int l,int r,int wh){
    if(!p) p=++tot;
    if(l==r){
        t[p].dt++;t[p].tg=wh;return  p;
    }
    int mid=(l+r)>>1;
    if(wh<=mid) t[p].lc=insert(t[p].lc,l,mid,wh);
    else t[p].rc=insert(t[p].rc,mid+1,r,wh);
    pushup(p);
    return p;
}
inline int merge(int p,int q,int l,int r){
    if(!p) return q;
    if(!q) return p;
    if(l==r){
        t[p].dt+=t[q].dt;
        t[p].tg=t[q].tg;
    }
    int mid=(l+r)>>1;
    t[p].lc=merge(t[p].lc,t[q].lc,l,mid);
    t[p].rc=merge(t[p].rc,t[q].rc,mid+1,r);
    pushup(p);
    return p;
}
inline int ask(int p,int l,int r,int x,int y){
    if(x<=l && r<=y)
        return t[p].dt;
    int mid=(l+r)>>1;
    int res=0;
    if(x<=mid) res+=ask(t[p].lc,l,mid,x,y);
    if(y>mid) res+=ask(t[p].rc,mid+1,r,x,y);
    return res;
}
void dfs(int x){
    for(int i=0;i<q[x].size();i++){
        int to=q[x][i];
        if(to==fa[x]) continue;
        dfs(to);
        rt[x]=merge(rt[x],rt[to],1,cnt);
    }
    ans[x]=ask(rt[x],1,cnt,vl[x]+1,cnt);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&vl[i]),c[i]=vl[i];
    sort(c+1,c+1+n);
    cnt=unique(c+1,c+1+n)-c-1;
    for(int i=1;i<=n;i++){
        vl[i]=lower_bound(c+1,c+1+n,vl[i])-c;
        rt[i]=insert(rt[i],1,cnt,vl[i]);
    }
    for(int i=2;i<=n;i++){
        int xx;scanf("%d",&xx);fa[i]=xx;
        q[xx].push_back(i);
        q[i].push_back(xx);
    }
    dfs(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}

```


---

## 作者：Cry_For_theMoon (赞：5)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/P3605)

&emsp;&emsp;扶苏大佬写的我这种蒟蒻完全看不懂啊，题解只看到一篇思路类似的，但是我还是没有完全看懂。我就把我这个非常简明易懂的做法讲一下吧。

&emsp;&emsp;**如果一道树上的题太难，我们就把它搬到链上**。如果树退化成了一条链，我们发现这是一个求**逆序对**的过程，可以直接用树状数组。

&emsp;&emsp;现在考虑把这个求逆序对的过程搬到树上。如果我们能确定当我们求解点 $i$ 时，能知道点 $i$ 的所有子孙都在哪里就可以了。众所周知树的 DFS 有三种，**只有后序遍历保证在最后的DFS序中，一个节点的子孙都会在该节点的前面**。因为我们对子孙进行查询，而子孙又是一段**连续**的区间（怎么可能我一颗树还没搜完就去搜另外一颗树呢），很明显我们可以用树状数组维护。

&emsp;&emsp;但是！虽然所有子孙都在根节点之前，但**不是所有根节点之前的节点都是它的子孙**，比如说可能是节点的兄弟的子孙。但是我们知道了子孙是一段连续的序列且在 $pos_i-1$处结尾（$pos_i$ 是节点 $i$ 在后序的位置），我们设节点 $i$ 的子孙数量是 $size_i$，那么 $pos_i-size_i$ ~ $pos_i-1$ 都是节点 $i$ 的子孙。然后我们用树状数组询问这一段的和就可以了。这也是为什么那篇类似思路的题解需要统计子树大小的原因。

&emsp;&emsp;事实上还有一种解法。如果我们对节点和它的DFS序做了**一一映射**，即我们既可以通过节点本身得到它的DFS序位置，也可以根据DFS位置得到该处的节点。我们只要维护一个节点的**上一个兄弟**，因为后序遍历的过程肯定是先后序上一个兄弟那颗子树，然后立马遍历当前这颗的，而上一个兄弟的子树的根（即上一个兄弟）一定位于它的DFS序的最末端，即位于 $pos_i-size_i-1$ 处。又因为我们对节点和DFS序位置做了一一映射，我们就直接可以知道 $pos_i-size_i-1$ 的位置，然后把它 $+1$ 就是查询区间的左边界了。这样省去了统计子树大小的过程，但是多了统计兄弟和一一映射的过程（好像两种解法其实都需要一一映射）

&emsp;&emsp;讲得差不多了，献上 AC Code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN],b[MAXN],ord[MAXN];
int n;
struct Cow{
	int p,ord,num;
	bool operator<(Cow& c2)const{
		return p<c2.p;
	}
}cow[MAXN];
struct Edge{
	int u,v;
}edge[MAXN];
int first[MAXN],next[MAXN],tot;
int past[MAXN],size[MAXN],tot2,m[MAXN];
int ans[MAXN];
int tree[MAXN];
void addedge(int u,int v){
	tot++;
	edge[tot].u = u;edge[tot].v = v;
	next[tot] = first[u];
	first[u] = tot;
}
int dfs(int u){
	size[u] = 1;
	for(int j=first[u];j;j=next[j]){
		int v=edge[j].v;
		size[u] += dfs(v);
	}
	past[++tot2] = u;
	m[u] = tot2; //映射 
	return size[u];
}
inline int lowbit(int x){
	return x & (-x);
}
inline void update(int x,int value){
	while(x<=n){
		tree[x] += value;
		x+=lowbit(x);
	}
}
inline int query(int x){
	int sum = 0;
	while(x>=1){
		sum += tree[x];
		x-=lowbit(x);
	}
	return sum;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i] = a[i];
	} 
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++){
		//离散化
		ord[i] = lower_bound(b+1,b+1+n,a[i])-b; 
	}
	for(int i=1;i<=n;i++){
		cow[i] = (Cow){a[i],ord[i],i};
	}
	//建树
	for(int i=2;i<=n;i++){
		int fa;
		cin>>fa;
		addedge(fa,i);
	} 
	//后序 + 统计子树大小 
	dfs(1);
	sort(cow+1,cow+1+n);
	for(int i=n;i>=1;i--){
		int now = m[cow[i].num],s = size[cow[i].num]-1; //子树大小
		//查找后序上[now-s,now)这一段的个数
		ans[cow[i].num] = query(now)-query(now-s-1);
		//加入
		update(now,1); 
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
} 
```


---

## 作者：OIER_z (赞：4)

~~竟然一遍AC？！~~ 咳咳

首先翻译题面，这是要求某个节点子树中权值比自己大的节点个数...

那我们可以先转成dfs序，于是变成维护区间和。

但每次都要找比自己小的，怎么维护呢？

我们可以先从小到大排序，dfs序列初始全为1，每次把自己修改成0，然后求区间和sum/2即可

贴代码时刻~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100009
int head[N],tot,let[N],rit[N],sum[N<<4],b[N<<1],ans[N],cnt;
struct node{
	int to,nxt;
}h[N<<1];
struct edge{
	int p,num;
}a[N];
void add(int u,int v){h[++tot].to=v;h[tot].nxt=head[u];head[u]=tot;}
void dfs(int x,int fa)
{
	let[x]=++cnt;
	b[cnt]=1;
	for(int i=head[x];i!=-1;i=h[i].nxt)
	{
		int v=h[i].to;
		if(v==fa) continue;
		dfs(v,x);
	}
	rit[x]=++cnt;
	b[cnt]=1;
}
void build(int rt,int l,int r)
{
	if(l==r) 
	{
		sum[rt]=b[l];
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void modify(int rt,int l,int r,int p)
{
	if(l==r)
	{
		sum[rt]=0;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid) modify(rt<<1,l,mid,p);
	if(p>mid) modify(rt<<1|1,mid+1,r,p);
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
int query(int rt,int l,int r,int xl,int xr)
{
	if(xl<=l && r<=xr) return sum[rt];
	int mid=(l+r)>>1,res=0;
	if(xl<=mid) res+=query(rt<<1,l,mid,xl,xr);
	if(mid<xr) res+=query(rt<<1|1,mid+1,r,xl,xr);
	return res;
}
bool cmp(edge x,edge y){return x.p<y.p;}
int main()
{
	memset(head,-1,sizeof(head));
	int n,x;
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i].p),a[i].num=i;
	for(int i=2;i<=n;i++)
		scanf("%d",&x),add(i,x),add(x,i);
	dfs(1,0);
	build(1,1,n<<1);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		modify(1,1,n<<1,let[a[i].num]);
		modify(1,1,n<<1,rit[a[i].num]);
		ans[a[i].num]=query(1,1,n<<1,let[a[i].num],rit[a[i].num])/2;
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：hcrbd8 (赞：4)

一开始看到这道题，以为是一道很高级的题目，然后突然发现只是一道建立在树上的树状数组，于是想了一想勉强水过


------------

题目描述：在一个树上，求对于每一个节点来说，以它为根节点的子树中多少个节点点权大于它本身点权


------------

先考虑树退化成链的情况，则题目变为求解逆序对个数，因此果断做一个树状数组

然后考虑在树上的操作，我们用dfs序的顺序向树状数组中加点，由于dfs的性质，我们可以得出以下结论：

当我们在求点i的ans时，我们发现在dfs的过程中，dfs序第一次出现i与最后一次出现i之间的过程会把且仅把以i为根节点的子树中的每一点加入树状数组，而这个两次情况下的树状数组求和结果S1和S2的差，即为所求的ans

总结一下：将点权从大到小排序，以rank为底构建树状数组，然后正常地dfs，每到一个点，先取出S1，然后dfs下去，最后回来取出S2，最后做差求解


------------

最最后贴上自己愚蠢的代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100100
using namespace std;
int n,x,tot=0,rank[maxn],ans[maxn],Last[maxn],tree[maxn];
struct recCow{int ab,odr;} p[maxn];
struct recEdge{int pre,to;} E[maxn];
void addEdge(int U,int V){
    E[++tot].pre=Last[U];Last[U]=tot;
    E[tot].to=V;
}
void read(int &x){
    char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar());
    for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-48;
}//丑陋的读入优化
bool cmp(const recCow &A,const recCow &B){return A.ab>B.ab;}
int lowbit(int x){return x&(-x);}
int sum(int p){
    int result=0;
    for (int i=p;i;i-=lowbit(i)){result+=tree[i];}
    return result;
}
void modify(int p,int delta){
    for (int i=p;i<=n;i+=lowbit(i)){tree[i]+=delta;}
}//树状数组标准(?)操作
void dfs(int x){
    int old=sum(rank[x]);
    for (int ed=Last[x];ed;ed=E[ed].pre)dfs(E[ed].to);
    ans[x]=sum(rank[x])-old;
    modify(rank[x],1);
}//dfs遍历
int main(){
    read(n);
    memset(Last,0,sizeof(Last));
    memset(tree,0,sizeof(tree));
    for (int i=1;i<=n;i++){read(p[i].ab);p[i].odr=i;}
    for (int i=2;i<=n;i++){read(x);addEdge(x,i);}
    sort(p+1,p+n+1,cmp);
    for (int i=1;i<=n;i++){rank[p[i].odr]=i;}
    dfs(1);
    for (int i=1;i<=n;i++){printf("%d\n",ans[i]);}
    return 0;
}
```

---

## 作者：zhengrunzhe (赞：3)

提供一篇平衡树启发式合并

~~虽然看上去很慢但实测423ms吸氧209ms~~

一开始每个点都是一颗独立的Splay

dfs下去，回溯时从叶节点开始，在儿子中找一个棵最大的Splay(其根记作wson)，把其他儿子的Splay并到wson中的里面来，然后再把自己并进去，用数组pos[x]表示编号为x的点的重儿子在Splay中节点指针，再把pos[当前点]设置为pos[wson](类似路径压缩)，查询比自己权值大的有多少个

```cpp
#include<cstdio>
#include<utility>
#include<algorithm>
using std::fill;
using std::pair;
using std::make_pair;
template<class type>inline const void read(type &in)
{
    in=0;char ch=getchar();short fh=1;
    while (ch<48||ch>57)fh=ch=='-'?-1:fh,ch=getchar();
    while (ch>47&&ch<58)in=(in<<3)+(in<<1)+ch-48,ch=getchar();
    in*=fh;
}
const int N=1e5+10;
class Splay
{
	private:
		struct tree
		{
			int size,val;
			tree *fa,*son[2];
			inline const bool identity()
			{
				return fa->son[1]==this;
			}
			inline const void pushup()
			{
				size=son[0]->size+1+son[1]->size;
			}
		}*null,memory_pool[N],*recycle[N],*tail;
		int top;
	public:
		tree *pos[N];
	protected:
		inline const void init()
		{
			top=0;
			tail=memory_pool;
			null=tail++;
			null->size=null->val=0;
			null->fa=null->son[0]=null->son[1]=null;
			fill(pos+1,pos+N,null);
		}
		inline tree *spawn(int key)
		{
			tree *p=top?recycle[--top]:tail++;
			p->size=1;
			p->val=key;
			p->fa=p->son[0]=p->son[1]=null;
			return p;
		}
		inline const void connect(tree *p,tree *fa,bool which)
		{
			if (p!=null)p->fa=fa;
			if (fa!=null)fa->son[which]=p,fa->pushup();
		}
		inline const void rotate(tree *p)
		{
			tree *fa=p->fa;
			bool id=p->identity();
			connect(p,fa->fa,fa->identity());
			connect(p->son[id^1],fa,id);
			connect(fa,p,id^1);
		}
		inline const void splay(tree *&root,tree *p)
		{
			for (tree *fa;(fa=p->fa)!=null;rotate(p))
				if (fa->fa!=null)
					rotate(p->identity()^fa->identity()?p:fa);
			root=p;
		}
		inline const void find(tree *root,int key)
		{
			tree *now=root;
			while (now->son[now->val<key]!=null&&now->val!=key)
				now=now->son[now->val<key];
			splay(root,now);
		}
	public:
		inline Splay(){init();}
		inline const void insert(tree *&root,int key)
		{
			if (root==null)return (void)(root=spawn(key));
			tree *now=root,*fa;bool which;
			while (1)
				if (fa=now,which=fa->val<key,(now=fa->son[which])==null)
					return now=spawn(key),connect(now,fa,which),splay(root,now);
		}
		inline const void merge(tree *a,tree *&b) //把a合并到b里
		{
			if (a==null)return;
			merge(a->son[0],b);
			merge(a->son[1],b);
			recycle[top++]=a;
		insert(b,a->val);
		}
		inline const int query(tree *p,int key)
		{
			find(p,key); //把p中权值为key的节点提到根
			return p->son[1]->size; //在p中比key大的数的个数即此时的根节点的右子树大小
		}
}S;
pair<int,int>e[N];
int head[N],cnt;
inline const void connect(int u,int v)
{
	e[++cnt]=make_pair(v,head[u]);
	head[u]=cnt;
}
int n,w[N],ans[N];
inline const void dfs(int p)
{
	int wson=0,weight=0;
	for (int son,i=head[p];i;i=e[i].second)
		if (dfs(son=e[i].first),S.pos[son]->size>weight) //找最大的儿子
			weight=S.pos[wson=son]->size;
	for (int son,i=head[p];i;i=e[i].second)
		if ((son=e[i].first)!=wson) //wson自己就不用合并了
			S.merge(S.pos[son],S.pos[wson]);
	S.insert(S.pos[p],w[p]); //初始化节点，
	if (!wson)return; //叶节点就直接返回了
	S.merge(S.pos[p],S.pos[wson]);
	ans[p]=S.query(S.pos[p],w[p]);
	S.pos[p]=S.pos[wson];
}
int main()
{
	read(n);
	for (int i=1;i<=n;i++)read(w[i]);
	for (int fa,i=2;i<=n;i++)
		read(fa),connect(fa,i);
	dfs(1);
	for (int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Great_Influence (赞：3)

首先可以明确问题要求每个点子树中比它权值大的点有多少个。dfs一下就可以转换成区间问题。

然后关于求区间比某个值大的点个数，可以选择分块，块内排序，就可以做到根号求值。时间复杂度$O(n\sqrt n\log_2\sqrt n)$。（数据才1e5可以放心水过）

代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x)
{
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&(k^'-'))k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file()
{
	#ifndef ONLINE_JUDGE
		freopen("test.in","r",stdin);
		freopen("test.out","w",stdout);
	#endif
}
const int MAXN=1e5+7;
static int n,w[MAXN],fa[MAXN],e,head[MAXN];
static struct edge
{
	int v,nxt;
}p[MAXN];
inline void add(int u,int v){p[++e].v=v;p[e].nxt=head[u];head[u]=e;}
static int dfn[MAXN],ri[MAXN],sz[MAXN];
void dfs(int u)
{
	ri[dfn[u]=++e]=u;sz[u]=1;
	for(register int v=head[u];v;v=p[v].nxt)if(fa[u]^p[v].v)
		dfs(p[v].v),sz[u]+=sz[p[v].v];
}
static int blo,c[1001][1001],a[MAXN];
#define bel(x) ((x-1)/blo+1)
void init()
{
	read(n);blo=sqrt(n)+1;
	Rep(i,1,n)read(w[i]);
	Rep(i,2,n)read(fa[i]),add(fa[i],i);
	e=0;dfs(1);
	Rep(i,1,n)c[bel(i)][i-(bel(i)-1)*blo]=a[i]=w[ri[i]];
	Rep(i,1,n/blo+1)
		sort(c[i]+1,c[i]+1+(i==n/blo+1?n-blo*(bel(n)-1):blo));
}
inline int query(int l,int r,int bs)
{
	if(l>r)return 0;
	static int ans;ans=0;
	if(bel(l)==bel(r))
	{
		Rep(i,l,r)ans+=bs<a[i];
		return ans;
	}
	for(;l%blo!=1;++l)ans+=bs<a[l];
	if(bel(l)==bel(r))
	{
		Rep(i,l,r)ans+=bs<a[i];
		return ans;
	}
	for(;r%blo;--r)ans+=bs<a[r];
	Rep(i,bel(l),bel(r))
		ans+=blo-(upper_bound(c[i]+1,c[i]+blo+1,bs)-c[i])+1;
	return ans;
}
void solve()
{
	Rep(i,1,n)
		printf("%d\n",query(dfn[i]+1,dfn[i]+sz[i]-1,w[i]));
}
int main()
{
	file();
	init();
	solve();
	return 0;
}
```

---

## 作者：Nero_Claudius (赞：3)

这道题开10倍左右一直MLE+RE，然后尝试着开了20倍就A了。。。窒息

------------

对于这道题目，我们考虑使用线段树合并来做。

所谓线段树合并，就是把结构相同的线段树上的节点的信息合在一起，合并的方式比较类似左偏树什么的。

------------

我们对于每个节点用权值线段树查询大于它的子节点数量，然后把当前节点并到它的父亲上面去。

对于此类型的题目我们通常使用动态开点的线段树（不然炸的没边）。

时间复杂度应该是$O(nlogn)$。

------------

AC代码如下：

`455ms 32824kb`

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace StandardIO {

	template<typename T> inline void read (T &x) {
		x=0;T f=1;char c=getchar();
		for(; c<'0'||c>'9'; c=getchar()) if(c=='-') f=-1;
		for(; c>='0'&&c<='9'; c=getchar()) x=x*10+c-'0';
		x*=f;
	}
	template<typename T>inline void write (T x) {
		if (x<0) putchar('-'),x*=-1;
		if (x>=10) write(x/10);
		putchar(x%10+'0');
	}

}

using namespace StandardIO;

namespace Solve {
	
	const int N=100100;
	
	int n;
	int cnt;
	struct node {
		int id,v;
		inline bool operator < (const node &x) const {
			return v<x.v;
		}
	}p[N];
	vector<int>graph[N];
	int tree_node;
	int val[N],tree[(int)(N*20)],ls[(int)(N*20)],rs[(int)(N*20)],root[N],ans[N];
	
	void build (int l,int r,int v,int &root) {
		if (!root) root=++tree_node;
		tree[root]++;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (v<=mid) build(l,mid,v,ls[root]);
		else build(mid+1,r,v,rs[root]);
	}
	int query (int l,int r,int v,int root) {
		if (!root) return 0;
		if (v<=l) return tree[root];
		int mid=(l+r)>>1;
		if (v<=mid) return query(l,mid,v,ls[root])+query(mid+1,r,v,rs[root]);
		return query(mid+1,r,v,rs[root]);
	}
	int merge (int x,int y) {
		if (!x||!y) return x+y;
		int root=++tree_node;
		tree[root]=tree[x]+tree[y];
		ls[root]=merge(ls[x],ls[y]);
		rs[root]=merge(rs[x],rs[y]);
		return root;
	}
	void dfs (int now) {
		for (register int i=0; i<graph[now].size(); ++i) {
			int to=graph[now][i];
			dfs(to);
			root[now]=merge(root[now],root[to]);
		}
		ans[now]=query(1,cnt,val[now]+1,root[now]);
		build(1,cnt,val[now],root[now]);
	}
	
	inline void solve () {
		read(n);
		for (register int i=1; i<=n; ++i) {
			read(p[i].v),p[i].id=i;
		}
		sort(p+1,p+n+1);
		for (register int i=1; i<=n; ++i) {
			if (p[i].v!=p[i-1].v) val[p[i].id]=++cnt;
			else val[p[i].id]=cnt;
		}
		for (register int i=2; i<=n; ++i) {
			int x;read(x);
			graph[x].push_back(i);
		}
		dfs(1);
		for (register int i=1; i<=n; ++i) {
			write(ans[i]),putchar('\n');
		}
	}
}

using namespace Solve;

int main () {
	solve();
}
```

---

## 作者：COUPDETAT (赞：2)

#### [树上逆序对](https://www.luogu.org/problem/P3605 "树上逆序对")
这道题呢 和逆序对非常相似 只需要处理出每条链上的逆序对数即可
#### 处理时需要注意的问题：
![file](http://101.200.56.58/wp-content/uploads/2019/10/image-1571974924910.png)
处理右子树时一定会将左子树的信息重复统计
这时候需要记录一个last值 一个小小的容斥思想即可

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int c[100100],data[100100],N,n,ans=0,maxi=0,head[100100],num[100100],lst[1001000];
int lowbit(int i) {return i&(-i);}	
struct zz{int i,data;}d[500010];
struct node{int to,nex;}e[1001000];
void add(int x,int y){e[++N].to=y;e[N].nex=head[x];head[x]=N;}
void insert(int i,int ci){for(;i<=n;i+=lowbit(i)) c[i]+=ci;}
int query(int i){int sum=0;for(;i>0;i-=lowbit(i))sum+=c[i];return sum;}
bool cmp(zz a,zz b){if(a.data==b.data)return a.i<b.i; return a.data<b.data;}
int dfs(int now)
{
    insert(d[now].data,1);
    int rongchi=query(n)-query(d[now].data);
    for(int i=head[now];i;i=e[i].nex){
    	int to=e[i].to;dfs(to);
    }
    num[now]+=query(n)-query(d[now].data)-rongchi;
}
bool cmp1(zz a,zz b){return a.data<b.data;};
bool cmp2(zz a,zz b){return a.i<b.i;};
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) d[i].i=i,cin>>d[i].data;
	sort(d+1,d+n+1,cmp1);
	for(int i=1;i<=n;i++) d[i].data=i;
	sort(d+1,d+n+1,cmp2);
	for(int i=2;i<=n;i++){int x,y=i;cin>>x;add(x,y);}
	dfs(1);	for(int i=1;i<=n;i++) cout<<num[i]<<endl;
	return 0;
} 
```

---

## 作者：VenusM1nT (赞：2)

树状数组。

首先我们知道，树有一种非常优美的性质，也就是说，一颗子树的 $\texttt{Dfs}$ 序是连续的，这意味着什么呢？也就是说，我们在对子树进行操作的时候，可以用 $\texttt{Dfs}$ 序把它从一棵树转换成一个序列，然后我们可以直接在序列上操作。

回到这道题，我们可以把树按照权值进行离散化，然后从大到小给每个点的子节点查询、打标记（相当于对一段区间进行操作），就可以过了。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1]; 
int n,id[MAXN],ans[MAXN],dfn[MAXN],siz[MAXN],idx;
struct Node
{
    int val,id;
    friend bool operator < (const Node &x,const Node &y)
    {
        return x.val>y.val;
    }
}a[MAXN];
struct TreeArray
{
    int c[MAXN];
    inl int lowbit(reg int x)
    {
        return x&-x;
    }
    inl void Modify(reg int x,reg int val)
    {
        for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }
    inl int Query(reg int x)
    {
        reg int res=0;
        for(;x;x-=lowbit(x)) res+=c[x];
        return res; 
    }
}T;
template <typename T> void Read(T &x)
{
    x=0;
    int fu=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
    x*=fu;
}
inl void AddEdge(reg int u,reg int v)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
}
void Dfs(reg int u,reg int faz)
{
    siz[u]=1;
    dfn[u]=++idx;
    for(reg int i=fst[u];i;i=nxt[i])
    {
        reg int v=to[i];
        if(v==faz) continue;
        Dfs(v,u);
        siz[u]+=siz[v];
    }
}
int main()
{
    Read(n);
    for(reg int i=1;i<=n;i++)
    {
        Read(a[i].val);
        a[i].id=i;
    }
    sort(a+1,a+n+1);
    for(reg int i=2;i<=n;i++)
    {
        reg int x;
        Read(x);
        AddEdge(x,i);
        AddEdge(i,x);
    }
    Dfs(1,0);
    for(reg int i=1;i<=n;i++)
    {
        ans[a[i].id]=T.Query(dfn[a[i].id]+siz[a[i].id]-1)-T.Query(dfn[a[i].id]-1);
        T.Modify(dfn[a[i].id],1);
    }
    for(reg int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：iodwad (赞：2)

线段树动态开点 + 线段树合并 模板题。

对于每一个树上的结点，维护一个值域线段树，这个值域线段树就是所有儿子的线段树合并起来的。

因为一个节点的线段树在被父亲合并了之后就不会再被合并了，所以合并完可以直接删除。

1A，感动。。。

注意要离散化。

指针吼啊！！

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

const int MAXN = 100000;

int n, tot;
int ans[MAXN | 1], a[MAXN | 1], hash[MAXN | 1];
std::vector < int > e[MAXN | 1];

struct Segtree {
	int sumv;
	Segtree *ch[2];
	Segtree(Segtree *ch0 = NULL, Segtree *ch1 = NULL, int val = 0) : sumv(val) {
		ch[0] = ch0;
		ch[1] = ch1;
	}
} *root[MAXN | 1];

inline int read() {
	register int x = 0;
	register char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x;
}

// 动态开点
void insert(Segtree *&o, int w, int l = 1, int r = tot) {
	if(o == NULL) o = new Segtree;
	++(o -> sumv);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(w <= mid) insert(o -> ch[0], w, l, mid);
	else insert(o -> ch[1], w, mid + 1, r);
}

int query(Segtree *o, int ql, int qr, int l = 1, int r = tot) {
	if(o == NULL) return 0;
	if(ql <= l && r <= qr) return o -> sumv;
	int mid = (l + r) >> 1, res = 0;
	if(ql <= mid) res = query(o -> ch[0], ql, qr, l, mid);
	if(mid < qr) res += query(o -> ch[1], ql, qr, mid + 1, r);
	return res;
}

Segtree *merge(Segtree *x, Segtree *y, int l = 1, int r = tot) {
	if(x == NULL) return y;
	if(y == NULL) return x;
	if(l == r) return new Segtree(NULL, NULL, x -> sumv + y -> sumv);
	int mid = (l + r) >> 1;
	Segtree *res = new Segtree(merge(x -> ch[0], y -> ch[0], l, mid), merge(x -> ch[1], y -> ch[1], mid + 1, r), x -> sumv + y -> sumv);
    // 这里就是直接删除的部分
	delete x;
	delete y;
	return res;
}

void dfs(int x) {
	for(std::vector < int >::iterator it = e[x].begin(); it != e[x].end(); ++it) {
		int to = *it;
		dfs(to);
		root[x] = merge(root[x], root[to]);
	}
	ans[x] = query(root[x], a[x] + 1, tot);
	insert(root[x], a[x]);
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = hash[i] = read();
	for(int i = 2; i <= n; ++i) e[read()].push_back(i);
	std::sort(hash + 1, hash + 1 + n);
	tot = std::unique(hash + 1, hash + 1 + n) - hash - 1;
	for(int i = 1; i <= n; ++i) a[i] = std::lower_bound(hash + 1, hash + 1 + tot, a[i]) - hash;
	dfs(1);
	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}
```



---

## 作者：金闪闪数据球 (赞：2)

有毒！！一开始离散化错了WA到怀疑人生。

本题可以看成树上逆序对，逆序对我们用树状数组求，权值太大了先离散化一下，对于树上的节点u，先遍历其子树，把子孙节点的权值累加进树状数组，最后查询有几个节点比u小，再维护siz【u】u及其子树的大小，就可以计算有几个节点比u大了。

不过有一个问题，我们是按树的后续遍历计算答案的。也就是说在计算u之前，u的兄弟节点有可能也会被插入树状数组中，如何排除这些多余的答案？

递归的时候查一次，回溯的时候查一次，两者相减，就知道真正比u小的节点是哪一些了。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define N 100010
using namespace std;
struct node{
  int v,nxt;
}e[N];
struct no{
  int name,p;
}f[N];
int head[N],num,n;
int val[N],siz[N],s[N],ans[N];
bool cmp(const no &a,const no &b){return a.p<b.p;}
bool cmp2(const no &a,const no &b){return a.name<b.name;}
void add(int u,int v){
  e[num].v=v;
  e[num].nxt=head[u];
  head[u]=num++;
}
int lowbit(int k){return k&(-k);}
void add(int x){
  while(x<=n){
    s[x]++;
    x+=lowbit(x);
  }
}
int sum(int x){
  int ans=0;
  while(x>0){
    ans+=s[x];
    x-=lowbit(x);
  }
  return ans;
}
void dfs(int u){
  siz[u]=1;
  int pre=sum(f[u].p);
  for(int i=head[u];i!=-1;i=e[i].nxt){
    int v=e[i].v;
    dfs(v);
    siz[u]+=siz[v];
  }
  ans[u]=siz[u]-1-(sum(f[u].p)-pre);
  add(f[u].p);
}
int main(){
  freopen("hh.in","r",stdin);
  freopen("hh.out","w",stdout);
  memset(head,-1,sizeof(head));
  int a,b;
  cin>>n;
  for(int i=1;i<=n;i++)scanf("%d",&f[i].p),f[i].name=i;
  sort(f+1,f+1+n,cmp);
  for(int i=1;i<=n;i++)f[i].p=i;
  sort(f+1,f+1+n,cmp2);
  for(int i=2;i<=n;i++){
    scanf("%d",&a);
    add(a,i);
  }
  dfs(1);
  for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
  return 0;
}

```

---

## 作者：zyh2015 (赞：2)

来自我的博客：<http://blog.csdn.net/yihan\_z/article/details/70144167>


题目大意：给出一棵有根树，每个点有一个权值，问对于每一个点的子树中比这个点大的点的个数。


首先权值很大需要离散化。

对于每一个点建一个权值线段树。遍历每一棵子树，然后将子树的线段树合并到自己的线段树上，在查询之后将自己插入。时间复杂度O(nlogn)


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
using namespace std;
struct Node {
    Node *ch[2];
    int l,r,sum;
    Node(int _l,int _r):l(_l),r(_r) {
        sum=0;
        ch[0]=ch[1]=NULL;
    }
    Node() {}
    void maintain() {
        sum=0;
        if(ch[0]) sum+=ch[0]->sum;
        if(ch[1]) sum+=ch[1]->sum;
        return ;
    }
    void* operator new (size_t) {
        static Node *mempool,*C;
        if(mempool==C) mempool=(C=new Node[1<<20])+(1<<20);
        return C++;
    }
}*root[N];
struct Edge {
    int to,nxt;
    Edge() {}
    Edge(int _to,int _nxt):to(_to),nxt(_nxt) {}
}e[N];
int n,m,tot=-1,fir[N],a[N],b[N],ans[N];
void Add_Edge(int x,int y) {
    e[++tot]=Edge(y,fir[x]), fir[x]=tot;
    return ;
}
void Merge(Node*& x,Node*& y) {
    if(!y) return ;
    if(!x) {
        x=y;
        return ;
    }
    x->sum+=y->sum;
    Merge(x->ch[0],y->ch[0]), Merge(x->ch[1],y->ch[1]);
    return ;
}
void Insert(Node*& o,int v,int L,int R) {
    if(!o) o=new Node(L,R);
    if(o->l==o->r) {
        o->sum++;
        return ;
    }
    int mid=L+R>>1;
    if(v<=mid) Insert(o->ch[0],v,L,mid);
    else Insert(o->ch[1],v,mid+1,R);
    o->maintain();
    return ;
}
int Query(Node* o,int v) {
    if(!o) return 0;
    if(v==o->r) return o->sum;
    int mid=o->l+o->r>>1;
    if(v<=mid) return Query(o->ch[0],v);
    return (o->ch[0] ? o->ch[0]->sum : 0)+Query(o->ch[1],v);
}
void dfs(int x) {
    for(int i=fir[x];~i;i=e[i].nxt) {
        dfs(e[i].to);
        Merge(root[x],root[e[i].to]);
    }
    ans[x]=Query(root[x],n-a[x]);
    Insert(root[x],n-a[x]+1,1,n);
    return ;
}
int main() {
    memset(fir,-1,sizeof fir);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i), b[i]=a[i];
    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+m,a[i])-b;
    for(int i=2;i<=n;i++) {
        int x;
        scanf("%d",&x);
        Add_Edge(x,i);
    }
    dfs(1);
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}

```

---

## 作者：ivyjiao (赞：2)

大家好，我是只会打暴力的 ivyjiao，我觉得权值树状数组太麻烦了，所以我拿暴力 AC 了这道题。什么线段树、离散化我觉得都没必要。

这题最开始也是等了很长时间没思路，苦于没法记录子树中的每个节点的值，又因为这题的 $p_i$ 并不单调，所以树形 dp 是行不通了。

那么考虑把不在子树内的节点手动排除，具体的，我们遍历到每个节点时，先把这个节点的答案减掉现在已被记录的节点的值，搜完子树后得到新的已被记录的节点的值，新记录的值肯定都是这个节点的子树内的，再把新的答案加回来，就是正确的答案了。最后再把当前节点的值记录一下即可，这里我用的是 vector，加减答案时用 lower/upper_bound 就行。

然后就愉快的 AC 了，而且代码非常简短。

时间复杂度 $O(n\log n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3u7kjklf.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int n,q,a[N],fa[N],ans[N];
vector<int>b,G[N];
void dfs(int u){
	ans[u]-=b.size()-(upper_bound(b.begin(),b.end(),a[u])-b.begin());
	for(int i=0;i<G[u].size();i++) dfs(G[u][i]);
	ans[u]+=b.size()-(upper_bound(b.begin(),b.end(),a[u])-b.begin());
	b.insert(lower_bound(b.begin(),b.end(),a[u]),a[u]);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
        cin>>fa[i];
        G[fa[i]].push_back(i);
    }
	dfs(1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
}
```

---

upd on 2024/11/2：

听说 vector 被卡了？为什么？？？

查了一下，原来 vector 的 $\text{insert}$ 和 $\text{erase}$ 是 $O(n)$ 的，只不过做了很多优化。

但是 [rope](https://oi-wiki.org/ds/block-list/) 的 $\text{insert}$ 和 $\text{erase}$ 都是严格 $O(\sqrt n)$ 的！本题 $1\leq n\leq 10^5$，$O(\sqrt n)$ 完全可过，时间复杂度 $O(n\sqrt n)$。

注意，rope 和 vector 的 $\text{insert}$ 和 $\text{erase}$ 的写法稍有不同，详见代码。

代码：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
const int N=1e5+1;
int n,q,a[N],fa[N],ans[N];
rope<int>b,G[N];
void dfs(int u){
	ans[u]-=b.size()-(upper_bound(b.begin(),b.end(),a[u])-b.begin());
	for(int i=0;i<G[u].size();i++) dfs(G[u][i]);
	ans[u]+=b.size()-(upper_bound(b.begin(),b.end(),a[u])-b.begin());
	b.insert(lower_bound(b.begin(),b.end(),a[u])-b.begin(),a[u]);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
        cin>>fa[i];
        G[fa[i]].push_back(i);
    }
	dfs(1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
}
```

---

## 作者：神仙酱 (赞：1)

~~其实我只想出来一半，还有一半是我五块牌的同学教我的~~
## 思路分析
### 从弱化问题开始
先来讨论一个弱化问题：下属能力大于上司能力的个数总共有多少？也就是要计数“顺序对”的个数，这显然是树状数组的强项。为了在树上做树状数组，需要通过 DFS 将树“压缩”成序列（见下图， 圈内数字为节点编号，绿色数字为离散化后牛的能力值）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ya20ll1r.png)

通过图中遍历顺序，获得其欧拉序为 1 2 4 4 2 3 5 5 3 1。根据欧拉序，在初次进入某个结点时，将对应结点的**权值**放入树状数组，在第二次离开某个结点时，将对应结点的**权值**从树状数组中删去即可。我已用粗体标出，需要明确，我们的树状数组维护的是权值，而权值范围太大，因此还需要离散化。

来模拟一下这个过程（以下序号代表欧拉序的编号，`ans` 代表“顺序对”的个数）：

1. `insert(3, 1)`，`ans += query(3)`，此刻 `ans == 0`，树状数组里值为 1 的有：3。
2. `insert(4, 1)`，`ans += query(4)`，此刻 `ans == 1`，树状数组里值为 1 的有：3 4。
3. `insert(2, 1)`，`ans += query(2)`，此刻 `ans == 1`，树状数组里值为 1 的有：2 3 4。
4. `insert(2, -1)`，删去 2，不更新答案。
5. `insert(4, -1)`，删去 4，不更新答案。
6. `insert(1, 1)`，`ans += query(1)`，此刻 `ans == 1`，树状数组里值为 1 的有：1 3。
7. `insert(5, 1)`，`ans += query(5)`，此刻 `ans == 3`，树状数组里值为 1 的有：1 3 5。
8. 后续都在删除结点，不更新答案。

如此一来，我们就统计出了所有的“顺序对”数。

### 解决原问题
本题棘手的地方就在于此，当我们在某个结点找到“顺序对”的时候，我们其实应该去更新其某些祖先节点的答案。然而顺着慢慢爬上去一个一个更新肯定会超时，因此只能另寻它径。

做法是：第一次进入结点时，记录下当前权值位置 $x$ 下，树状数组的值 $v_1$，然后使树状数组 $ [1, x) $ 的区间内加一。第二次离开 $x$ 对应结点时，再记录下树状数组的值 $v_2$，那么该点的答案就是 $v_2 - v_1$。

这个方法可行的原因是，如果有 $k$ 个子结点比当前结点的权值大，那么必然会使这个位置的值增加 $k$，所以答案就是两次经过该节点树状数组在该点的差。

## 实现细节
如果想知道怎么快速对树状数组维护区间进行区间修改，请参见，[【模板】树状数组2](https://www.luogu.com.cn/problem/P3368)。如果还不熟悉树状数组求逆序对或进行离散化，请参见[逆序对](https://www.luogu.com.cn/problem/P1908)。
## AC代码
```c++
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#define val first
#define id second
using namespace std;
const int N = 1e5 + 10;
int rk[N], n, ans[N];
int tr[N << 1], dfsq[N << 1], dfn, ht[N];
int e[N], h[N], nxt[N], idx = 1;
pair<int, int> a[N];
void add(int a, int b) {
    e[idx] = b, nxt[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    dfsq[++dfn] = u;
    for (int i = h[u]; i; i = nxt[i])
        dfs(e[i]);
    dfsq[++dfn] = u;
}

void insert(int x, int v) {
    for (; x <= n; x += x & -x)
        tr[x] += v;
}

int query(int x) {
    int ans = 0;
    for (; x; x -= (x & -x))
        ans += tr[x];
    return ans;
}

inline int read() {
    int x{}, flag = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            flag = -1;
    for (; isdigit(ch); ch = getchar())
        x = x * 10 + (ch ^ 48);
    return x * flag;
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i].val = read(), a[i].id = i;
    // 离散化
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        rk[a[i].id] = i;
    // 建树
    for (int i = 2; i <= n; ++i)
        add(read(), i);
    // 获得欧拉序
    dfs(1);
    // 欧拉序的个数是 2 * n
    n <<= 1;
    memset(ans, -1, sizeof ans);
    for (int i = 1; i <= n; ++i) {
        if (~ans[dfsq[i]]) {
            ans[dfsq[i]] = query(rk[dfsq[i]]) - ans[dfsq[i]];
        }
        else {
            ans[dfsq[i]] = query(rk[dfsq[i]]);
            if (rk[dfsq[i]] > 1) {
                insert(1, 1);
                insert(rk[dfsq[i]], -1);
            }
        }
    }

    for (int i = 1; i <= (n >> 1); ++i)
        cout << ans[i] << "\n";
}
```

---

## 作者：垣根帝督 (赞：1)

### 本蒟蒻的第一篇~~紫题~~题解 , 各位dalao勿喷



首先看到这道题,我的第一反应就是 , 这道题也忒简单了吧 , 直接每次枚举一头牛,然后找它的下属有几个比它大的就行了吧

### 但是
## 但是
# 但是

### 请看数据范围

### (1≤N≤100,000)

这显然是不行的

那么应该怎么办呢?


我们再来思考一下 : 看到树 我们想到了什么 ? 树状数组 ? \

答对了 其实这题可以用树状数组来优化\

那么该怎么来优化呢?

直接用树状数组统计子树中有几个比他大的就行了,不过这里我们需要借助入度和出度来实现

详见代码:

```cpp
for (int i=1;i<=n;i++){
	int num=a[i].id;//a[i].id是排序前的i,具体的看代码吧
	ans[num]=get(T_ou[num])-get(T_in[num]);//这里是在计算答案,使用了树状数组
	add_x(T_in[num],1);//后续处理
}

```

这样把答案保存到ans数组中,最后输出就行了

丑陋的Code:


```cpp
#include<cstdio>
#include<algorithm>
#define maxn 100005
using namespace std;
struct data{
	int w,id;
	bool operator <(const data b)const{return b.w<w;}//结构体里重载运算符,将a数组按照w从大到小排
}a[maxn];
int n,cnt,T_in[maxn],T_ou[maxn],f[maxn],ans[maxn],lnk[maxn],son[maxn],nxt[maxn];
inline int read(){//快读
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
void add_e(int x , int y){son[++cnt]=y,nxt[cnt]=lnk[x],lnk[x]=cnt;}//建边的过程
void add_x(int x,int date){//典型的树状数组
	for(int i=x;i<=n;i+=i&-i) f[i]+=date;
}
int get(int x){
	int now=0;
	for(int i=x;i;i-=i&-i) now+=f[i];
	return now;
}
void DFS(int x){//借助于DFS算出后面要用到的T_in和T_out,表示入度和出度
	T_in[x]=++cnt;
	for(int j=lnk[x];j;j=nxt[j])
	  if (!T_in[son[j]]) DFS(son[j]);
	T_ou[x]=cnt;
}
int main(){
	freopen("promote.in","r",stdin);
	freopen("promote.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) a[i].w=read(),a[i].id=i;//读入数据
	sort(a+1,a+1+n);//排一趟
	for(int i=2;i<=n;i++) add_e(read(),i);//建边
	cnt=0;DFS(1);
	for (int i=1;i<=n;i++){//计算
		int num=a[i].id;
		ans[num]=get(T_ou[num])-get(T_in[num]);
		add_x(T_in[num],1);
	}
	for (int i=1;i<=n;i++) printf("%d\n",ans[i]);//输出
	return 0;
}
```

望管理大大通过QWQ !


---

## 作者：Bring (赞：1)

# 来一发不用离散化的玩法
题目中要求的是关于任何一个点i，i的子树中p值>p(i)的节点个数

一种做法就是将权值离散化，然后以离散化后权值的size（即n）构造树状数组，使用dfs计算自己的子树对答案的贡献（具体的可以看其他题解）

**那么另一种做法呢？**

## ~~当然就是暴力数啦~~

~~当然暴力数要超时的~~

考虑这样一种做法：

以一种方式排列这n个点，使得对于这棵树的每一棵子树，这个序列存在一条连续字段，他们包含的点相同。

如果这个可以实现，那么题目就从求i的子树中p值>p(i)的节点个数变成了求该序列中包含i的某区间中p值>p(i)的元素个数了。

对于这种问题，只要将所有点按权值排序，树状数组求区间和，做完一个点更新就可以了。

**那么这个神奇的序列是什么呢**

相信大家都已经想到了，就是……

## dfs序

本题解采用先序遍历，后序遍历做法类似

用l[i],r[i]表示以i为根的子树在先序遍历的区间

那么l[i]就是i的序列位置，r[i]就是i的最右叶节点的序列位置，即i回溯时的计数器值

细节详见代码(127ms/8.69MB)
```cpp
//This program is written by Bring.
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<vector>
using namespace std;
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
inline int read(){
    register int x;register char c(getchar());register bool k;
    while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
    if(c^'-')k=1,x=c&15;else k=x=0;
    while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
    return k?x:-x;
}
void wr(register int a){
    if(a<0)Pc('-'),a=-a;
    if(a<=9)Pc(a|'0');
    else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(register int i(a);i<(b);++i)
#define Frn1(i,a,b) for(register int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(register int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (100010)
#define I (c[i].i)
int n,l[N],r[N],idx,t[N],ans[N];
struct T{int p,i;}c[N];
vector<int>e[N];
void dfs(int x){l[x]=++idx;for(int i:e[x])dfs(i);r[x]=idx;}
inline void add(int x){while(x<=n)++t[x],x+=x&-x;}
inline int sm(int x){int r(0);while(x)r+=t[x],x^=x&-x;return r;}
inline int qry(int x,int y){return sm(y)-sm(x-1);}
signed main(){
    Rd(n);
    Frn1(i,1,n)c[i]={read(),i};
    Frn1(i,2,n)e[read()].push_back(i);
    dfs(1),sort(c+1,c+n+1,[](T a,T b){return a.p<b.p;});
    Frn1(i,1,n)ans[I]=r[I]-l[I]-qry(l[I],r[I]),add(l[I]);
    Frn1(i,1,n)wr(ans[i]),Pe;
    exit(0);
}
```

---

## 作者：teafrogsf (赞：1)

题解里这么多BIT的啊......其实我是因为找线段树合并裸题才来的orz~~那么为了增加代码长度就写一个线段树合并吧~~  
建好**动态开点线段树**（原题解有误，故修正），每次dfs后就合并父子线段树，然后再查询权值线段树上大于它的。这样的复杂度仍然是$O(n\log n)$。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<tr1/unordered_map>
#define neko 100010
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~(i)))
#define travel(i,u,v) for(register int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)
typedef int arr[neko];
arr in,out,dfn,head,ans;
int L[neko*20],R[neko*20],Sum[neko*20],rt[neko*20];
int t,cnt,n;
std::tr1::unordered_map<int,int>mp;
struct OK
{int val,id;}a[neko];
bool cmp(OK x,OK y)
{return x.val<y.val;}
bool cmp2(OK x,OK y)
{return x.id<y.id;}
struct node
{
	int v,nex;
}e[neko<<1];
void add(int x,int y)
{
	e[++t].v=y;
	e[t].nex=head[x];
	head[x]=t;
}
namespace Pst_Tree
{
	#define mid ((l+r)>>1)
	#define lson L[root],l,mid
	#define rson R[root],mid+1,r
	void pushup(int root)
	{Sum[root]=Sum[L[root]]+Sum[R[root]];}
	void update(int &root,int l,int r,int x)
	{
		if(!root)root=++cnt;
		if(l==r){++Sum[root];return;}
		if(x<=mid)update(lson,x);
		else update(rson,x);
		pushup(root);
	}
	int query(int root,int l,int r,int tagl,int tagr)
	{
		if(l>=tagl&&r<=tagr)return Sum[root];
		int tmp=0;
		if(tagl<=mid)tmp+=query(lson,tagl,tagr);
		if(tagr>mid)tmp+=query(rson,tagl,tagr);
		return tmp;
	}
	int merge(int x,int y)
	{
		if((!x)||(!y))return x+y;
		L[x]=merge(L[x],L[y]);
		R[x]=merge(R[x],R[y]);
		pushup(x);
		return x;
	}
}
using namespace Pst_Tree;
void dfs(int u,int fa)
{
	travel(i,u,v)if(v!=fa)dfs(v,u),rt[u]=merge(rt[u],rt[v]);
	ans[u]=query(rt[u],1,n,mp[a[u].val]+1,n);
}
int main()
{
	using namespace std;
	int x;
	scanf("%d",&n);
	f(i,1,n)scanf("%d",&a[i].val),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	f(i,1,n)if(!mp[a[i].val])mp[a[i].val]=i;
	sort(a+1,a+n+1,cmp2);
	f(i,2,n)scanf("%d",&x),add(x,i),add(i,x);
	f(i,1,n)update(rt[i],1,n,mp[a[i].val]);
	dfs(1,0);
	f(i,1,n)printf("%d\n",ans[i]);
}
```


---

## 作者：曹老师 (赞：1)

**知识点：BIT DFS**

这么大的数据 直接**离散化处理**

我这里求ans数组的时候用了~~我也不知道叫什么的~~思想

**满足条件的=总的-不满足条件的** 就这么简单

query和update函数是处理BIT的 (模板类型

DFS完 就可以出答案咯

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=100005;
struct node{
	int num,q;
};
node f[L];
int n,c[L],ans[L],siz[L],bit[L];
vector<int>tree[L];
bool cmp(const node &a,const node &b)
{
	return a.q<b.q;
}
int query(int x)
{
	int t=0;
	while(x)
	{
		t+=bit[x];
		x-=lowbit(x);
	}
	return t;
}
void update(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
		bit[i]+=v;
}
int dfs(int u)
{
	siz[u]=1;
	int pre=query(c[u]);
	for(int i=0;i<tree[u].size();i++)
	{
		dfs(tree[u][i]);
		siz[u]+=siz[tree[u][i]];		
	}
	ans[u]=siz[u]-1-(query(c[u])-pre);
	update(c[u],1);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&f[i].q);
		f[i].num=i;
	}
	sort(f+1,f+n+1,cmp);
	for(int i=1;i<=n;i++)
		c[f[i].num]=i;//离散化 
	for(int i=2;i<=n;i++)
	{
		int m;
		scanf("%d",&m);
		tree[m].push_back(i);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：henry_y (赞：0)

[$my\ blog$](https://www.cnblogs.com/henry-1202/)

想了几种做法...

主席树$O(nlogn)$，线段树合并$O(nlogn)$，分块$O(n\sqrt{n}log(\sqrt{n}))$，然而都懒得写...

然后就写了一个莫队+BIT。$O(nsqrt{n}logn)$。离散化一下就行了...

就是把dfs序爬下来，顺便记录一下siz，那么一个节点的子树在dfs上就
是$[dfn_x,dfn_x+siz_x-1]$，那就用莫队维护一下，每次移动指针对应的在bit里面操作就好了...

然而在树上直接BIT求逆序对真的没看题解之前不会写（把之前答案删了处理完子树再加上去，这个真的没想到）。

选择这个主要是因为好写..基本不用调，也就70行左右。一发过掉了。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N], dfn[N], c[N], siz[N];
int cnt, head[N], ans[N];
struct edge {
	int to, nxt;
}e[N<<1];

void ins(int u, int v) {
	e[++cnt] = (edge) {v, head[u]};
	head[u] = cnt;
}

int tim = 0;
void dfs(int u, int fa) {
	siz[u] = 1; dfn[u] = ++tim;
	for(int i = head[u]; i; i = e[i].nxt) {
		if(e[i].to == fa) continue;
		int v = e[i].to;
		dfs(v, u);
		siz[u] += siz[v];
	}
}

struct task {
	int l, r, id, v;
}q[N];

int block;
bool cmp(task a, task b) {
	return a.l / block == b.l / block ? a.r < b.r : a.l / block < b.l / block;
}

namespace BIT {
	#define lowbit(x) (x&(-x))
	void add(int x, int v) {
		for(int i = x; i <= n; i += lowbit(i)) c[i] += v;
	}
	int query(int x) { 
		int ans = 0;
		for(int i = x; i; i -= lowbit(i)) ans += c[i];
		return ans;
	}
} using namespace BIT;

int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
	for(int i = 2; i <= n; ++i) {
		int v; cin >> v;
		ins(i, v), ins(v, i);
	}
	dfs(1, 0); 
	for(int i = 1; i <= n; ++i) 
		q[i] = (task) {dfn[i], dfn[i]+siz[i]-1, i, a[i]};
	for(int i = 1; i <= n; ++i) b[dfn[i]] = a[i];
	block = sqrt(n);
	sort(q+1,q+n+1,cmp);
	int l = q[1].l, r = q[1].l - 1;
	for(int i = 1; i <= n; ++i) {
		int ql = q[i].l, qr = q[i].r;
		while(ql < l) add(b[--l], 1);
		while(ql > l) add(b[l++], -1);
		while(r < qr) add(b[++r], 1);
		while(r > qr) add(b[r--], -1);
		ans[q[i].id] = query(n) - query(q[i].v);
	}
	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
} 
```

---

