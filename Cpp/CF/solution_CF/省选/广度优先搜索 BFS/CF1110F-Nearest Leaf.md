# Nearest Leaf

## 题目描述

我们将树（一个无环连通无向图）的欧拉遍历定义如下：考虑一种深度优先搜索算法，遍历树的顶点，并按访问顺序依次编号（每个顶点只在第一次访问时编号）。该函数从编号为 $1$ 的顶点开始，然后递归地从所有与当前顶点通过一条边相连且尚未访问过的顶点出发，按编号递增的顺序进行。形式化地，你可以用如下伪代码描述该函数：

```
next_id = 1
id = 长度为 n 的数组，初始值均为 -1
visited = 长度为 n 的数组，初始值均为 false

function dfs(v):
    visited[v] = true
    id[v] = next_id
    next_id += 1
    for to in 按编号递增顺序的 v 的邻居:
        if not visited[to]:
            dfs(to)
```

给定一棵带权树，其顶点已按照上述算法用 $1$ 到 $n$ 的整数编号。

叶子节点是指仅与一个其他顶点相连的顶点。在给定的树中，编号为 $1$ 的顶点不是叶子节点。树中两个顶点之间的距离定义为它们之间简单路径上所有边的权值之和。

你需要回答 $q$ 个如下形式的询问：给定整数 $v$、$l$ 和 $r$，求从顶点 $v$ 到编号在 $l$ 到 $r$（包含端点）之间的某个叶子节点的最短距离。

## 说明/提示

在第一个样例中，树的结构如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1110F/0f1b498aea8daedc270520f6cae94d5c4aa241fe.png)

对于第一个询问，顶点 $1$ 最近的叶子节点是顶点 $4$，距离为 $3$。对于第二个询问，顶点 $5$ 最近的叶子节点是顶点 $5$，距离为 $0$。对于第三个询问，顶点 $4$ 最近的叶子节点是顶点 $4$，但它不在询问区间 $[1, 2]$ 内。区间 $[1, 2]$ 内唯一的叶子节点是顶点 $2$，从顶点 $4$ 到顶点 $2$ 的距离为 $13$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3
1 10
1 1
3 2
3 3
1 1 5
5 4 5
4 1 2
```

### 输出

```
3
0
13
```

## 样例 #2

### 输入

```
5 3
1 1000000000
2 1000000000
1 1000000000
1 1000000000
3 4 5
2 1 5
2 4 5
```

### 输出

```
3000000000
1000000000
2000000000
```

## 样例 #3

### 输入

```
11 8
1 7
2 1
1 20
1 2
5 6
6 2
6 3
5 1
9 10
9 11
5 1 11
1 1 4
9 4 8
6 1 4
9 7 11
9 10 11
8 1 11
11 4 5
```

### 输出

```
8
8
9
16
9
10
0
34
```

# 题解

## 作者：Grussg (赞：12)

# $Introducer$

其实评黑着实有一点点过分了 ~~（第一道黑题）~~

代码实现算不上难，思维还是有难度滴

学校讲题做了Markdown顺便就当题解发了

# $Description$

给你一棵带权有根树，它的根为1。且保证对于每个点$i$，它的父亲$Father_i<i$,且$Father_i  \rightarrow i$的权值为$w_i$。

同时，这棵树有一个性质：如果我们$DFS$这一棵树，对于每个点都递增访问其子节点，每访问一个节点就记录其编号，那么得到的编号刚好为$1$到$n$.

现在有$q$次询问，每次给出$v_i,l_i,r_i$,求从$v_i$出发到$[l_i,r_i]$中的一个叶子结点的的最短距离（保证$[l_i,r_i]$之中有一个叶子结点）。

数据范围：

$3 \leq n \leq5\times10^5,1 \leq q \leq 5\times10^5\;\;$

$1\leq Father_i<i ,1\leq w_i \leq10^9$

# $Solution$

#### 从特殊性质入手思考

$Special\;1$

对于一个节点，它的子节点均比它大。

$Special\;2$

一棵树，$DFS$的时候，每个点递增访问其子节点，得到编号刚好为$1$到$n$的序列


$Thinking~ Special ~1 ~and~ Special ~2$

这些特殊点又意味着什么呢。

既然对于一个点，子节点都比它要大，同时的它又是递增有序的，所以说，对于一个点$i$它的子树的节点的编号，是一个$[Min_{son} , Max_{son}]$的连续的序列。

#### 有了这个特殊性质之后，我们继续思考如何处理这棵特殊的树。


我们先特殊化处理一个例子。设一非叶子结点$u$，有其一儿子$v$，特别的设一条边$(u,v)$权值为$w$。我们每当往下跑这一条边的时候（即当前结点$now$由$u \to v$）那我们当前结点到所有叶子结点的距离会有什么变化？

显然有两种情况

$Case ~1$

不在$v$的子树里的叶子结点到$now$的距离会$+w$。

$Case ~2$

在$v$的子树里的叶子结点到$now$的距离会$-w$。


那么我们每当跑一条边的时候只要把所有不在子树里的叶子结点$+w$，然后把子树里的叶子结点$-w$就好了，然后取所有的最小值。同样的，子树是$[Min_{son} , Max_{son}]$的区间，所以说区间修改+查询，显而易见线段树可维护。

#### 算法流程就处来了

$Step~1$ $DFS$一遍，找到每个节点其子树的编号最大值，并且处理每个节点到根的距离。

$Step~2$ 把所有节点加入线段树，把叶子节点赋成其到根的距离，为了让非叶子节点不影响处理，全都赋成$INF$。

$Step~3$ $DFS$第二遍，每跑一条边用线段树区间修改，跑到一个节点的时候线段树查询最小值。

## $Tips$

$First$.把$1$到$n$的区间$+w$然后再把$[Min_{son} , Max_{son}]-2\times w$更加不容易出锅。

$Second$.第二遍往下$DFS$的时候记得回溯。

 $Third$.$INF$要开的足够大。

# $Code$

```cpp
#include<bits/stdc++.h>
#define mid (l+r)/2
#define ri register int 
#define ll long long 
using namespace std;
const ll INF=LLONG_MAX/2;
const ll maxG=500005;
ll n,m;
ll tot;
ll ql[maxG],qr[maxG],siz[maxG],head[maxG],dis[maxG],ans[maxG],laz[maxG<<2],tr[maxG<<2];
vector<ll> q[maxG];
struct node{
	ll u,v,w,nxt;
}e[maxG];
 
template <class T> inline void read(T&x){
	bool f;char ch=getchar();
	for(f=false;!isdigit(ch);ch=getchar())if(ch=='-')f=true;
	for(x=0;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
	x*=f==1?-1:1;
}

inline ll ls(ll u){return u<<1;}
inline ll rs(ll u){return u<<1|1;}
inline void pushup(ll u){tr[u]=min(tr[ls(u)],tr[rs(u)]);}

inline void lazy(ll num){
	if(laz[num]){
		laz[ls(num)]+=laz[num];
		laz[rs(num)]+=laz[num];
		tr[ls(num)]+=laz[num];
		tr[rs(num)]+=laz[num];
		laz[num]=0;
	}
}

inline void updata(ll l,ll r,ll x,ll y,ll num,ll k){
	if(l>=x&&r<=y) {
		tr[num]+=k;
		laz[num]+=k;
		return;
	}
	lazy(num);
	if(mid>=x) updata(l,mid,x,y,ls(num),k);
	if(mid<y)  updata(mid+1,r,x,y,rs(num),k);
	pushup(num);
}

inline ll getans(ll l,ll r,ll x,ll y,ll num){
	if(l>=x&&r<=y) return tr[num];
	ll ans=INF;
	lazy(num);
	if(mid>=x) ans=min(ans,getans(l,mid,x,y,ls(num)));
	if(mid<y)  ans=min(ans,getans(mid+1,r,x,y,rs(num)));
	return ans;
}


inline void add(ll u,ll v,ll w){
	e[++tot]=(node){u,v,w,head[u]};
	head[u]=tot;
}

inline void dfs1(ll u){
	siz[u]=u;
	for(ri i=head[u];i;i=e[i].nxt){
		ll v=e[i].v,w=e[i].w;
		dis[v]=dis[u]+w;
		dfs1(v);
		siz[u]=max(siz[u],siz[v]);
	}
}

inline void dfs2(ll u){
	ll len=q[u].size();
	for(ri i=0;i<len;i++) ans[q[u][i]]=getans(1,n,ql[q[u][i]],qr[q[u][i]],1);
	for(ri i=head[u];i;i=e[i].nxt){
		ll v=e[i].v,w=e[i].w;
		updata(1,n,1,n,1,w);updata(1,n,v,siz[v],1,-w-w);
		dfs2(v);
		updata(1,n,1,n,1,-w);updata(1,n,v,siz[v],1,w+w);
	}
} 

int main(){
  	read(n),read(m);
	for(ri x,y,i=2;i<=n;i++){
  		read(x),read(y);
  		add(x,i,y);
	}
	dfs1(1);
	for(ri i=1;i<=n;i++){
		if(siz[i]==i) updata(1,n,i,i,1,dis[i]);
		else updata(1,n,i,i,1,INF);
	}
	for(ri x,i=1;i<=m;i++){
		read(x),read(ql[i]),read(qr[i]);
		q[x].push_back(i); 
	}
	dfs2(1);
	for(ri i=1;i<=m;i++) scanf("%lld\n",ans[i]); 
	return 0;
}

```

# $Postscript$

鸣谢： @$Siyuan$（UID：49725）奆佬的题解在我学习中对我的帮助


希望我的题解能给大家带来一点启发

## $C_{S^P}~~2^0_19~~ R_P~ ~P^{L^US}~~ P_{L_US}$

顺带撒花


---

## 作者：Siyuan (赞：11)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-1110F-Nearest-Leaf/)

---

## Description

> 题目链接：[Codeforces 1110F](https://codeforces.com/contest/1110/problem/F)

给你一棵带权有根树，根节点为 $1$，且保证每个点的父亲 $p_i<i$，其中 $(p_i,i)$ 的边权为 $w_i$。这棵树有个性质：如果我们 $\text{DFS}$ 这棵树，对于每个点都递增枚举儿子节点，每访问到一个节点就记录其编号，那么得到的序列刚好为 $1$ 到 $n$。

现在有 $q$ 次询问，每次给出 $v_i,l_i,r_i$，求从 $v_i$ 出发到 $[l_i,r_i]$ 中的其中一个叶子节点的最短距离（保证 $[l_i,r_i]$ 中至少有一个叶子节点）。

数据范围：$3\le n\le 5\times 10^5$，$1\le q\le 5\times 10^5$，$1\le p_i<i$，$1\le w_i\le 10^9$

------

## Solution

考虑都没有修改操作，我们可以把询问**离线**下来。按照询问的节点分类。

我们首先观察一个性质：由于 $\text{DFS}$ 序就是 $1$ 到 $n$，那么意味着**每棵子树内**的编号都是**连续**的，记子树 $i$ 内点的**最大编号**为 $k_i$。

我们再考虑一个问题：如果从 $u$ 到达 $v$（我们记这条边为 $(u,v,w)$），其中 $v$ 的深度大于 $u$，那么到达每个叶子的路径长度会发生什么变化？

- 对于在 $v$ 子树内的叶子，到他们的距离**减少** $w$。
- 其余叶子节点，到他们的距离**增加** $w$。

根据之前的性质，我们发现 $v$ 子树内的节点编号连续，可以直接用**线段树修改**。具体的修改方法为：我们将线段树内 $[1,n]$ 的节点的值增加 $w$，将 $[v,k_v]$ 的节点的值减少 $2w$。

为了防止对线段树中**非叶子节点**的影响，我们应该要将他们的值初始化为 $\text{INF}$，使得无论如何修改都不会影响答案。

这样一来，我们可以得到一个简单的算法流程：

1. 将 $1$ 到所有叶子节点的距离放到线段树中，非叶子节点的距离定义为 $\text{INF}$。
2. 直接 $\text{DFS}$ 整棵树，将询问节点为**当前节点**的询问统计答案。
3. 枚举当前节点 $u$ 的儿子节点 $v$，在线段树上修改 $[v,k_v]$ 的值并递归求解 $v$ 的值；递归后记得**回溯**消去影响！

**时间复杂度**：$O((n+q)\log n)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#define lson p<<1
#define rson p<<1|1

const int N=5e5+5;
const long long INF=1LL<<60;
int n,m,tot,l[N],r[N],mx[N],lnk[N],ter[N],nxt[N],val[N];
long long seg[N<<2],tag[N<<2],dis[N],ans[N];
std::vector<int> q[N];

void pushup(int p) {
	seg[p]=std::min(seg[lson],seg[rson]);
}
void pushdown(int p) {
	if(!tag[p]) return;
	long long v=tag[p];
	seg[lson]+=v,tag[lson]+=v,seg[rson]+=v,tag[rson]+=v,tag[p]=0;
}
void modify(int x,int y,int p,int l,int r,long long v) {
	if(x<=l&&r<=y) {
		seg[p]+=v,tag[p]+=v;
		return;
	}
	pushdown(p);
	int mid=(l+r)>>1;
	if(x<=mid) modify(x,y,lson,l,mid,v);
	if(mid<y) modify(x,y,rson,mid+1,r,v);
	pushup(p);
}
long long query(int x,int y,int p,int l,int r) {
	if(x<=l&&r<=y) return seg[p];
	pushdown(p);
	int mid=(l+r)>>1;
	long long ans=INF;
	if(x<=mid) ans=std::min(ans,query(x,y,lson,l,mid));
	if(mid<y) ans=std::min(ans,query(x,y,rson,mid+1,r));
	return ans;
}
void add(int u,int v,int w) {
	ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot,val[tot]=w;
}
void dfs1(int u) {
	mx[u]=u;
	for(int i=lnk[u];i;i=nxt[i]) {
		int v=ter[i];
		dis[v]=dis[u]+val[i];
		dfs1(v);
		mx[u]=std::max(mx[u],mx[v]);
	}
}
void dfs2(int u) {
	for(int i:q[u]) ans[i]=query(l[i],r[i],1,1,n);
	for(int i=lnk[u];i;i=nxt[i]) {
		int v=ter[i],w=val[i];
		modify(1,n,1,1,n,w),modify(v,mx[v],1,1,n,-w-w);
		dfs2(v);
		modify(1,n,1,1,n,-w),modify(v,mx[v],1,1,n,w+w);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;++i) {
		int p,w;
		scanf("%d%d",&p,&w),add(p,i,w);
	}
	dfs1(1);
	for(int i=1;i<=n;++i) {
		modify(i,i,1,1,n,i==mx[i]?dis[i]:INF);
	}
	for(int i=1;i<=m;++i) {
		int v;
		scanf("%d%d%d",&v,&l[i],&r[i]),q[v].push_back(i);
	}
	dfs2(1);
	for(int i=1;i<=m;++i) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Liliangxi (赞：3)

# [CF1110F Nearest Leaf](https://www.luogu.com.cn/problem/CF1110F)

## 题意：

（题外话：这是本蒟蒻的第一篇题解，写的不好的地方请在评论区指出来）

给定一棵树，保证给定编号恰好为一个 dfs 序。保证 $1$ 号节点不是叶子。$m$ 次询问，每次给定 $x$，$l$，$r$，你需要求出 $\min\limits_{i\in [l,r],i \text{是叶子}}dis(x,i)$。

## solution

### step1

首先考虑一个弱化的问题：

如果**查询的始终是根节点**，那么只需求出每个点到根节点的距离，然后查询就变成了一个区间最小值问题。容易解决，先 dfs 求出每个节点到达根节点的距离，然后对于 dfn 序（本题中即 $1$ 到 $n$ 已经排好序），并使用线段树维护。

### step2

![tree](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1110F/0f1b498aea8daedc270520f6cae94d5c4aa241fe.png)

如图，若是**以 $1$ 连向的子节点为根节点**进行查询（**换根**的思想），**目前已经遍历到节点 $3$**：

在 **$3$ 的子树**中查询，先对于**所有节点**加上**从 $1$ 到 $3$ 的边权**（**相对节点 $1$ 来说，距离节点 $3$ 都更远了从 $1$ 到 $3$ 的边权**），再对 $3$ 的子树管辖的区间减去两倍从 $1$ 到 $3$ 的边权（**对于 $3$ 的子树来说，相对原根 $1$ 来说，离根节点进了从 $1$ 到 $3$ 的边权，再考虑原先加上过一次从 $1$ 到 $3$ 的边权，所以减去两倍**），这样就完成了换根操作，可以仔细推一下，应该容易理解。

同时使用**线段树**进行维护，同时别忘记回溯了，于是便可以完成这道题了！

## Code(码风清奇)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lll unsigned long long
#define dou double
#define S string
#define INF 214748364711451419
#define pi pair<ll,ll>
#define mkp make_pair
#define mii map<int,int> 
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;

struct node
{
    ll v,w;
};
struct segment
{
    int ls,rs;
    ll val,tag;
}t[2000011];
int n,m;
ll len[500011],dis[500011],pl[500011],pr[500011],ans[500011];
vector<node> a[500011];
vector<ll> dc[500011];


//----------线段树----------
void pushup(int pos)
{
    t[pos].val=min(t[pos*2].val,t[pos*2+1].val);
}
void maketag(int pos,ll v)
{
    t[pos].val+=v;
    t[pos].tag+=v;
}
void pushdown(int pos)
{
    if(t[pos].tag)
    {
        maketag(pos*2,t[pos].tag);
        maketag(pos*2+1,t[pos].tag);
        t[pos].tag=0;
    }
}
void build(int l,int r,int pos)
{
    t[pos].ls=l;
    t[pos].rs=r;
    if(l==r)
    {
        return ;
    }
    int mid=(l+r)>>1;
    build(l,mid,pos*2);
    build(mid+1,r,pos*2+1);
}
void update(int l,int r,ll v,int pos)
{
    if(l<=t[pos].ls&&t[pos].rs<=r)
    {
        t[pos].val+=v;
        t[pos].tag+=v;
        return ;
    }
    pushdown(pos);
    int mid=(t[pos].ls+t[pos].rs)>>1;
    if(l<=mid) update(l,r,v,pos*2);
    if(mid<r) update(l,r,v,pos*2+1);
    pushup(pos);
}
ll query(int l,int r,int pos)
{
    if(l<=t[pos].ls&&t[pos].rs<=r)
    {
        return t[pos].val;
    }
    pushdown(pos);
    int mid=(t[pos].ls+t[pos].rs)>>1;
    ll sum=INF;
    if(l<=mid) sum=min(sum,query(l,r,pos*2));
    if(mid<r) sum=min(sum,query(l,r,pos*2+1));
    return sum;
}
//----------结束----------
//----------搜索----------
void dfs1(int x)
{
    len[x]=x;                           //初始赋值为自己
    for(auto i:a[x])
    {
        dis[i.v]=dis[x]+i.w;            //每个点到树根（题目中为1）的距离
        dfs1(i.v);
        len[x]=max(len[x],len[i.v]);    //len[i]描述对于i节点其子孙的最大编号
    }
}
void dfs2(int x)
{
    for(auto i:dc[x])
    {
        ans[i]=query(pl[i],pr[i],1);        //对于当前点，若有以此点进行展开操作的，去线段树中查询区间最小值
    }
    for(auto i:a[x])                        //搜索树的下一层
    {
        update(1,n,i.w,1);                  //全体加上一次i.w
        update(i.v,len[i.v],-i.w-i.w,1);    //在当前节点子树的叶子节点的距离全部减去边权，在当前节点子树外的叶子节点的距离要加上边权
        dfs2(i.v);                          //下一层树搜索
        update(1,n,-i.w,1);                 //回溯
        update(i.v,len[i.v],i.w+i.w,1);
    }
}
//----------结束----------
int main()
{
    IOS;
    cin>>n>>m;
    for(int i=2;i<=n;i++)
    {
        ll x,y;
        cin>>x>>y;
        a[x].push_back((node){i,y});
    }
    build(1,n,1);                       //建树（虽然没有值填充，个人习惯是预处理出ls和rs）
    dfs1(1);                            //得出每个点到根的距离和其子孙节点的最大编号
    for(int i=1;i<=n;i++)
    {
        if(len[i]==i) update(i,i,dis[i],1);     //若是叶子节点，线段树赋值为其到根节点的距离
        else update(i,i,INF,1);                 //否则设置为无穷大
    }
    for(int i=1;i<=m;i++)                       //使用离线思想  
    {
        int opt;
        cin>>opt>>pl[i]>>pr[i];
        dc[opt].push_back(i);                   //对于节点opt，查询节点编号再l到r区间内的最近叶子节点
    }
    dfs2(1);                                //二次深搜
    for(int i=1;i<=m;i++)
    {
        cout<<ans[i]<<endl;                 //离线做法输出答案
    }
    return 0;
}
/*
求过求过
*/
```

---

## 作者：1saunoya (赞：3)

你今天要是能卡掉我 $n\log^2n$ 的点分树，我 当 场 就 把 这 个 电 脑 屏 幕 吃 下 去。

~~（cnm卡一个小时真累，又被卡空间又被卡时间，如果想抄代码不建议来抄我这个又臭又长空间又大跑的又慢的代码谢谢合作。）~~


建出来一个树高 $\log n$ 的点分树，然后在上面把叶子信息加上去。

然后把所有的部分扔到这个重心，重心的重心（

容易证明这样是最小的，最小的就不用去掉相同一段的贡献了。

然后每次枚举 $father$ 把那颗子树的信息并过来，也就是并起来两段路径。

- 另外一种做法。

我们把非叶子节点距离设为 $inf$，叶子节点正常搞，然后 dfs 一遍，可回退栈的思想，就做完了（考虑一个类换根dp的东西，u -> v 给所有的贡献是，v 子树中距离减少，非 v 子树中距离增加）于是就是线段树打tag，查询，打tag，查询……就完了。

```cpp
// powered by c++11
// by Isaunoya

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;
char buf[1 << 21], *p1 = buf, *p2 = buf;
char getc(){ return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++; }
void read(int&x) {
  char c = getc();
  for(x = 0; !isdigit(c); c = getc());
  while(isdigit(c)) x = x * 10 + (c ^ '0'), c = getc();
}
void put(long long x) { if(x > 9) put(x / 10); putchar(x % 10 + '0'); }
template <class T>  void cmax(T& x, const T& y) { if (x < y) x = y; }
template <class T>  void cmin(T& x, const T& y) { if (x > y) x = y; }
int n, m;
const int maxn = 5e5 + 1;
int rt[maxn];
struct SMT {
  long long val[maxn * 50];
  int ls[maxn * 50], rs[maxn * 50], cnt;
  SMT() { cnt = 0, memset(val, 0x3f, sizeof(val)); }
  void upd(int& p, int l, int r, int x, long long v) {
    if (!p) p = ++cnt;
    if (l == r) { cmin(val[p], v); return; }
    int mid = l + r >> 1;
    if (x <= mid)
      upd(ls[p], l, mid, x, v);
    else
      upd(rs[p], mid + 1, r, x, v);
    val[p] = min(val[ls[p]], val[rs[p]]);
  }

  long long qry(int p, int a, int b, int l, int r) {
    if (!p) return 1e18;
    if (a <= l && r <= b) return val[p];
    int mid = l + r >> 1;
    long long ans = 1e18;
    if (a <= mid) cmin(ans, qry(ls[p], a, b, l, mid));
    if (b > mid) cmin(ans, qry(rs[p], a, b, mid + 1, r));
    return ans;
  }
} smt;
struct edge { int v, nxt, w; } e[maxn << 1];
int cnt = 0, head[maxn];
void add(int u, int v, int w) {
  e[++cnt] = { v, head[u], w }, head[u] = cnt;
  e[++cnt] = { u, head[v], w }, head[v] = cnt;
}
struct Tree {
  int f[maxn][20], fa[maxn], dep[maxn];
  long long len[maxn];

  void dfs(int u) {
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (v ^ fa[u]) {
        fa[v] = u, len[v] = len[u] + e[i].w;
        dfs(v);
      }
    }
  }

  void solve() {
    dfs(1);
    for (int i = 1; i <= n; i++) f[i][0] = fa[i];
    for (int j = 1; j < 20; j++) {
      for (int i = 1; i <= n; i++) f[i][j] = f[f[i][j - 1]][j - 1];
    }
  }

  int lca(int x, int y) {
    if (dep[x] < dep[y]) x ^= y ^= x ^= y;
    for (int i = 19; ~i; i--)
      if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y) return x;
    for (int i = 19; ~i; i--)
      if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
  }

  long long dis(int x, int y) { return len[x] + len[y] - (len[lca(x, y)] << 1); }
} tr;

struct NewTree {
  int sz[maxn], mx[maxn], vis[maxn], fa[maxn];
  int rt, tot;

  NewTree() { mx[rt = 0] = 1e9; }

  void getrt(int u, int fa) {
    sz[u] = 1, mx[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (v ^ fa && !vis[v]) {
        getrt(v, u);
        sz[u] += sz[v], cmax(mx[u], sz[v]);
      }
    }
    cmax(mx[u], tot - sz[u]);
    if (mx[u] < mx[rt]) {
      rt = u;
    }
  }

  void solve(int u) {
    vis[u] = 1;
    const int now = tot;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (!vis[v]) {
        rt = 0, tot = (sz[v] > sz[u]) ? (now - sz[u]) : sz[v];
        getrt(v, u), fa[rt] = u, solve(rt);
      }
    }
  }

  void upd(int x, int val) {
    int now = x;
    while (x) {
      smt.upd(::rt[x], 1, n, val, tr.dis(now, x));
      x = fa[x];
    }
  }

  long long qry(int x, int l, int r) {
    int now = x;
    long long ans = 1e18;
    while (x) {
      cmin(ans, tr.dis(now, x) + smt.qry(::rt[x], l, r, 1, n));
      x = fa[x];
    }
    return ans;
  }
} nt;

signed main() {
  read(n), read(m);
  std::vector<int> deg(n + 1, 0);
  for (int i = 2; i <= n; i++) {
    int father, w;
    read(father), read(w);
    add(father, i, w);
    deg[father]++;
    deg[i]++;
  }
  tr.solve(), nt.tot = n, nt.getrt(1, 0), nt.solve(nt.rt);
  for (int i = 1; i <= n; i++) if(deg[i] == 1) { nt.upd(i, i); }
  while (m--) {
    int x, l, r;
    read(x), read(l), read(r);
    put(nt.qry(x, l, r)); putchar('\n');
  }
  return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

考虑把询问离线下来，把询问 $(x,l,r)$ 变成在 $x$ 上询问 $[l,r]$。

于是就可以分为两种情况讨论：在子树内和在子树外的叶子。

不难发现这个编号是一个 dfs 序，那么就是子树内的节点编号一定是连续的一段。

于是可以在 dfs 算答案的过程中，当前遍历进子节点就给子树内的 $-w$ 而给不在子树的 $+w$，区间加用线段树维护。这个是显然的。

复杂度 $O(n \log n)$。

---

## 作者：NoGoshPlease (赞：1)

提供一种在线单 $\log$ 做法。

询问显然可以转化为 $\min \limits _{i=l}^r dis_x+dis_i-2dis_{LCA(x,i)}$。

于是最暴力地，我们可以从 $x$ 上跳枚举 $LCA(x,i)$，用 ST 表维护区间 $dis$ 最小值即可。

如何优化呢？

既然题目保证节点编号与 dfs 序相同，那我们询问就会分成如图的几种情况。（以下默认所有叶子从左到右编号递增）

![](https://cdn.luogu.com.cn/upload/image_hosting/gosh8gog.png)

对于后面两种情况，我们先把 $x$ 跳到红点的位置，显然不会产生影响。

然后我们考虑树剖，考虑跳祖先的过程，我们希望能快速求出来这段祖先链的每个点作为 $LCA$ 时的答案。

我们维护一个数组 $lmin_x$ 表示以 $x$ 为 $LCA$ 时对于所有 $x$ 子树内在重链左边的叶子 $v$，$dis_v-2dis_x$ 的最小值。同理维护 $rmin_x$ 表示右边。

结合图理解一下，实际上跳链的过程中只需要用到 $lmin,rmin$ 数组中的值，那么我们按照树剖的 dfn 序列对这两个数组分别维护 ST 表维护区间最小值。

实际计算答案跳链的时候，遇到图中交点的情况或者重链更换，需要特殊处理一下。

时间复杂度 $O(n\log n)$。

具体细节参见代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
const long long inf=1e18;
int n,q;
int fa[N],w[N];
vector <int> g[N];
long long sum[N];
int dep[N],siz[N],son[N];
int dfn[N],dfncnt,seq[N],top[N];
void dfs1(int x,int f)
{
	sum[x]=sum[f]+w[x];
	dep[x]=dep[f]+1;
	siz[x]=1;
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(v==f) continue;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
}
void dfs2(int x,int f)
{
	dfn[x]=++dfncnt;
	seq[dfncnt]=x;
	top[x]=f;
	if(son[x]) dfs2(son[x],f);
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(v==fa[x]||v==son[x]) continue;
		dfs2(v,v);
	}
}
int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) return x;
	return y;
}
long long mi[N],lmi[N],rmi[N];
void dfs3(int x)
{
	mi[x]=inf;lmi[x]=rmi[x]=inf;
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		dfs3(v);
		mi[x]=min(mi[x],mi[v]);
		if(v<son[x]) lmi[x]=min(lmi[x],mi[v]);
		if(v>son[x]) rmi[x]=min(rmi[x],mi[v]);
	}
	if(g[x].size()==0) mi[x]=sum[x];
}
struct ST
{
	int Log2[N];
	long long st[N][20];
	void getst()
	{
		for(int i=2;i<=n;i++) Log2[i]=Log2[i/2]+1;
		for(int j=1;j<=Log2[n];j++)
			for(int i=1;i<=n;i++)
				st[i][j]=min(st[i][j-1],st[min(n,i+(1<<j-1))][j-1]);
	}
	long long find(int l,int r)
	{
		if(l>r) return inf;
		int k=Log2[r-l+1];
		return min(st[l][k],st[r-(1<<k)+1][k]);
	}
}st,stl,str;
long long calc(int x,int l,int r)
{
	long long d=sum[x];
	long long ans=inf;
	if(x<l) x=LCA(x,l);
	if(x>r) x=LCA(x,r);
	int xl=LCA(x,l),xr=LCA(x,r);
	bool chk=0;
//	printf("%d %d\n",xl,xr);
	while(xl||xr)
	{
//		printf("%d:%d %d:%lld(%d)\n",x,xl,xr,ans,chk);
		ans=min(ans,st.find(max(l,x),min(x+siz[x]-1,r))+d-sum[x]*2);
		if(xl==x) xl=0;
		if(xr==x) xr=0;
		if(chk==0){chk=(x!=top[x]),x=fa[x];continue;}
		int v=top[x];
		if(dep[v]<=dep[xl]) v=seq[dfn[xl]+1];
		if(dep[v]<=dep[xr]) v=seq[dfn[xr]+1];
		if(xl) ans=min(ans,d+stl.find(dfn[v],dfn[x]));
		if(xr) ans=min(ans,d+str.find(dfn[v],dfn[x]));
		x=fa[v];
		chk=0;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++) scanf("%d%d",&fa[i],&w[i]),g[fa[i]].push_back(i);
	for(int i=1;i<=n;i++) sort(g[i].begin(),g[i].end());
	dfs1(1,0);
	dfs2(1,1);
	dfs3(1);
	for(int i=1;i<=n;i++) st.st[i][0]=(g[i].size()==0?sum[i]:inf);
	for(int i=1;i<=n;i++) stl.st[i][0]=lmi[seq[i]]-sum[seq[i]]*2,str.st[i][0]=rmi[seq[i]]-sum[seq[i]]*2;
	st.getst();stl.getst();str.getst();
	for(int i=1;i<=q;i++)
	{
		int x,l,r;
		scanf("%d%d%d",&x,&l,&r);
		printf("%lld\n",calc(x,l,r));
	}
}
```

---

## 作者：xukuan (赞：1)

加黑的那句话：**如果我们 DFS 这棵树，对于每个点都递增枚举儿子节点，每访问到一个节点就记录其编号，那么得到的序列刚好为 1 到 n**

学过树剖的同学应该想到，树剖的方法就是对每个点进行重新编号，这样每个子树中的编号就是连续的。再用线段树维护区间，得到结果。

这题也可以用类似的方法。

同时对于从x到达y，记这条边为的长度为z，其中$dep_{y} > dep_{x}$，那么到达每个叶子的路径长度会发生什么变化？

如过节点是v的子节点，距离减少z，否则增加z

以下内容有参考[机房超级大佬丁思源的题解](http://old.orzsiyuan.com/articles/problem-Codeforces-1110F-Nearest-Leaf)

### 方法：
1. 将根节点到所有叶子节点的距离放到线段树中，非叶子节点的距离定义为INF
2. 直接DFS整棵树，将询问节点为当前节点的询问统计答案。
3. 枚举当前节点x的儿子节点y，在线段树上修改并递归求解y的值

特别注意INF要写$2^{60}$,像$2^{32}-1$之类的连样例都过不了

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll INF=1ll<<60;
ll n,m,Max[500010],d[500010],L[500010],R[500010],ans[500010];
ll ver[1000010],edge[1000010],Next[1000010],head[500010],tot;
vector<ll> q[500010];
struct SegmentTree{
	ll l,r,Min,lazy;
}tree[500010<<2];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

inline void addEdge(ll x,ll y,ll z){
	ver[++tot]=y;
	edge[tot]=z;
	Next[tot]=head[x];
	head[x]=tot;
}

void dfs1(ll x){
	Max[x]=x;
	for(ll i=head[x]; i; i=Next[i]){
		ll y=ver[i],z=edge[i];
		d[y]=d[x]+z;
		dfs1(y);
		Max[x]=max(Max[x],Max[y]);
	}
}

inline void pushup(ll p){
	tree[p].Min=min(tree[p<<1].Min,tree[p<<1|1].Min);
}

inline void pushdown(ll p){
	if(tree[p].lazy){
		tree[p<<1].Min+=tree[p].lazy;
		tree[p<<1].lazy+=tree[p].lazy;
		tree[p<<1|1].Min+=tree[p].lazy;
		tree[p<<1|1].lazy+=tree[p].lazy;
		tree[p].lazy=0;
	}
}

void build(ll p,ll l,ll r){
	tree[p].l=l; tree[p].r=r;
	if(l==r) return;
	ll mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}

void update(ll p,ll l,ll r,ll val){
	if(l<=tree[p].l&&tree[p].r<=r){
		tree[p].Min+=val;
		tree[p].lazy+=val;
		return;
	}
	pushdown(p);
	ll mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid) update(p<<1,l,r,val);
	if(r>mid) update(p<<1|1,l,r,val);
	pushup(p);
}

ll query(ll p,ll l,ll r){
	if(l<=tree[p].l&&tree[p].r<=r) return tree[p].Min;
	pushdown(p);
	ll mid=(tree[p].l+tree[p].r)>>1,ans=INF;
	if(l<=mid) ans=min(ans,query(p<<1,l,r));
	if(r>mid) ans=min(ans,query(p<<1|1,l,r));
	return ans;
}

void dfs2(ll x){
	for(ll i:q[x]) ans[i]=query(1,L[i],R[i]);
	for(ll i=head[x]; i; i=Next[i]){
		ll y=ver[i],z=edge[i];
		update(1,1,n,z); update(1,y,Max[y],-2*z);
		dfs2(y);
		update(1,1,n,-z); update(1,y,Max[y],2*z);
	}
}

int main(){
	n=read(); m=read();
	for(ll i=2; i<=n; i++){
		ll y=read(),z=read();
		addEdge(y,i,z);
	}
	dfs1(1);
	build(1,1,n);
	for(ll i=1; i<=n; i++) update(1,i,i,i==Max[i]?d[i]:INF);
	for(ll i=1; i<=m; i++){
		ll x=read(); L[i]=read(); R[i]=read();
		q[x].push_back(i);
	}
	dfs2(1);
	for(ll i=1; i<=m; i++){
		write(ans[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

这里给一个跟叶子结点的性质没啥关系的做法。

首先考虑求出它的 **欧拉序**，然后求出相邻两个点之间的位移（往下走是 $x$，往上走是 $-x$）。dfs 序在 $[l,r]$ 中就相当于它的欧拉序也在一段区间内。

对于询问 $(x,l,r)$，我们 **将 $1\to x$ 中所有边的边权变为原来的相反数后** 分类讨论：设最优的叶子为 $i$：

- $in_{i}<in_x$：我们把 $(in_i,in_x]$ 中的所有位移加起来，发现刚好等于 $i$ 到 $x$ 的距离。设 $sum_i$ 为位移的前缀和序列，答案就是 $sum_x-\min_{in_i\in [l,in_x)}sum_{in_i}$。
- $in_i>in_x$：还是一样，把 $(in_x,in_i]$ 中的所有位移加起来就是距离。跟上述情况类似，我们也只要求一个区间最小的 $sum$ 值即可。

反转边权可以通过 dfs 实现，每次遍历到一个儿子时，就将当前点与儿子的边权反转。

单点修改，区间查询前缀和最小值可以使用线段树维护。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6;
const ll inf=1e18;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,fa[Maxn+5],h[Maxn+5],L[Maxn+5],R[Maxn+5],cur;
int in[Maxn+5],out[Maxn+5],px[Maxn+5],dx[Maxn+5],chk[Maxn+5],s;
ll t[Maxn*4+5],tag[Maxn*4+5],val[Maxn+5],ans[Maxn+5];
vector<int> v[Maxn+5],q[Maxn+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

struct BIT
{
    ll t[Maxn+5];
    #define lowbit(x) (x&-x)
    inline void Add(int x,ll y) {while(x<=s) t[x]+=y,x+=lowbit(x);}
    inline ll Count(int x) {ll res=0; while(x) res+=t[x],x-=lowbit(x); return res;}
} T;

inline void dfs(int x,int k)
{
    in[x]=++s,dx[s]=x,val[s]=k,chk[x]=v[x].empty(),px[++cur]=s;
    for(auto y:v[x]) dfs(y,h[y]);
    out[x]=++s,dx[s]=-x,val[s]=-k;
}
inline void push_up(int p) {t[p]=min(t[ls(p)],t[rs(p)]);}
inline void mk(int p,ll k) {t[p]+=k,tag[p]+=k;}
inline void push_down(int p)
{if(tag[p]) mk(ls(p),tag[p]),mk(rs(p),tag[p]),tag[p]=0;}
inline void Build(int l,int r,int p)
{
    if(l==r) {t[p]=(dx[l]>0 && chk[dx[l]])?val[l]:inf; return;}
    int mid=(l+r)>>1; Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Modify(int nl,int nr,int l,int r,int p,ll k)
{
    if(l>r) return; if(l<=nl && nr<=r) {mk(p,k); return;}
    int mid=(nl+nr)>>1; push_down(p);
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    if(r>mid) Modify(mid+1,nr,l,r,rs(p),k);
    push_up(p);
}
inline ll Count(int nl,int nr,int l,int r,int p)
{
    if(l>r) return inf; if(l<=nl && nr<=r) return t[p];
    int mid=(nl+nr)>>1; ll res=inf; push_down(p);
    if(l<=mid) res=min(res,Count(nl,mid,l,r,ls(p)));
    if(r>mid) res=min(res,Count(mid+1,nr,l,r,rs(p)));
    return res;
}
inline void Modify(int x,ll k) {T.Add(x,k),Modify(1,s,x,s,1,k);}
inline void dfs(int x)
{
    for(auto id:q[x])
    {
        int l=L[id],r=R[id];
        ans[id]=min(ans[id],Count(1,s,px[l],min(px[r],in[x]-1),1)-T.Count(in[x]));
        ans[id]=min(ans[id],Count(1,s,max(in[x],px[l]),px[r],1)-T.Count(in[x]));
    }
    for(auto y:v[x])
    {
        Modify(in[y],-2ll*h[y]),Modify(out[y],2ll*h[y]),dfs(y);
        Modify(in[y],2ll*h[y]),Modify(out[y],-2ll*h[y]);
    }
}

int main()
{
    n=read(),m=read();
    For(i,2,n) v[fa[i]=read()].push_back(i),h[i]=read();
    dfs(1,0); For(i,1,s) T.Add(i,val[i]);
    For(i,1,s) val[i]+=val[i-1]; Build(1,s,1);
    For(i,1,m)
    {
        int x=read(),l=read(),r=read(); L[i]=l,R[i]=r;
        q[x].push_back(i),ans[i]=inf;
    }
    dfs(1); For(i,1,m) printf("%lld\n",ans[i]);
    return 0;
}
```



---

## 作者：hegm (赞：0)

很好的一道题目。

由于题目保证给定的是 dfs 序，自然而然的想到一个性质，一个节点的子树一定对应着一个子区间，我们不妨考虑先离线下拉，将每个询问对应到节点上，现在考虑在整棵树上进行移动会造成什么影响：

从 $i$ 到 $j$ 其中是 $j$ 的子树中的节点，的距离会减少 $w(i,j)$ 而其他的节点会增加 $w(i,j)$ ，同时这又是三个区间，所以可以使用线段树维护区间最小值，不是叶子的节点初始值设置为 inf 就好了。

### CODE

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (now<<1)
#define rs (now<<1|1)
#define N 500005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,cnt,vis[N],dis[N],mx[N],mn[N],ans[N];
struct qst
{
	int l,r,id;
};
vector<qst> v[N];
struct fig
{
	int to,next,w;
}k[N*4];int tot,head[N];
void adt(int from,int to,int w)
{
	k[++tot].to=to;
	k[tot].next=head[from];
	k[tot].w=w;
	head[from]=tot;
}
void dfs(int now)
{
	mx[now]=now;
	mn[now]=now;
	for(int i=head[now];i;i=k[i].next)
	{
		vis[now]=1;
		dis[k[i].to]=dis[now]+k[i].w;
		dfs(k[i].to);
		mx[now]=max(mx[now],mx[k[i].to]);
		mn[now]=min(mn[now],mn[k[i].to]);
	}
}
struct tree
{
	int w,lz;
}tr[N*4];
void up(int now)
{
	tr[now].w=min(tr[ls].w,tr[rs].w);
}
void build(int now,int l,int r)
{
	if(l==r)
	{
		if(vis[l])tr[now].w=1000000000000000000;
		else tr[now].w=dis[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	up(now);
}
void down(int now)
{
	if(tr[now].lz!=0)
	{
		tr[ls].w+=tr[now].lz;
		tr[rs].w+=tr[now].lz;
		tr[ls].lz+=tr[now].lz;
		tr[rs].lz+=tr[now].lz;
		tr[now].lz=0;
	}
}
void add(int now,int l,int r,int ql,int qr,int w)
{
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)
	{
		tr[now].w+=w;
		tr[now].lz+=w;
		return ;
	}
	int mid=(l+r)>>1;down(now);
	if(mid>=ql)add(ls,l,mid,ql,qr,w);
	if(mid<qr)add(rs,mid+1,r,ql,qr,w);
	up(now);
}
int que(int now,int l,int r,int ql,int qr)
{
	if(l>=ql&&r<=qr)
	{
		return tr[now].w;
	}
	int mid=(l+r)>>1,cnt=1000000000000000000;down(now);
	if(mid>=ql)cnt=min(cnt,que(ls,l,mid,ql,qr));
	if(mid<qr)cnt=min(cnt,que(rs,mid+1,r,ql,qr));
	return cnt;
}
void solve(int now)
{
	for(qst x:v[now])ans[x.id]=que(1,1,n,x.l,x.r);
	for(int i=head[now];i;i=k[i].next)
	{
		add(1,1,n,mn[k[i].to],mx[k[i].to],-k[i].w);
		add(1,1,n,1,mn[k[i].to]-1,k[i].w);
		add(1,1,n,mx[k[i].to]+1,n,k[i].w);
		solve(k[i].to);
		add(1,1,n,mn[k[i].to],mx[k[i].to],k[i].w);
		add(1,1,n,1,mn[k[i].to]-1,-k[i].w);
		add(1,1,n,mx[k[i].to]+1,n,-k[i].w);
	}
}
signed main()
{
	n=read();m=read();
	for(int i=2,x,w;i<=n;i++)
	{
		x=read();w=read();
		adt(x,i,w);
	}
	dfs(1);
	build(1,1,n);
	for(int i=1,x,l,r;i<=m;i++)
	{
		x=read();l=read();r=read();
		v[x].push_back(qst{l,r,i});
	}
	solve(1);
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：registerGen (赞：0)

在 [cnblogs](https://www.cnblogs.com/registergen/p/cf1110f_solution.html) 上查看。

## Solution

这个题的性质保证了对于任意的结点，它的子树的结点编号是连续的区间。

考虑离线，将整棵树 DFS 一遍，在这个过程中动态维护当前结点 $u$ 到所有叶子的距离。

于是问题来了：当我们从 $u$ DFS 到他的儿子 $v$ 时，到叶子的距离有什么变化呢？

答案是：以 $v$ 为根的子树距离 $-w$，其它结点距离 $+w$。由于这两个都是连续区间，所以可以使用线段树维护。

具体细节见代码。

## Code

语言标准：C++17。

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<tuple>

typedef long long ll;

const int N=5e5;
const ll inf=0x3f3f3f3f3f3f3f3f;

typedef long long ll;

struct Node{
	ll v,atag;
};

int n,m;
std::vector<std::pair<int,int>> G[N+10];
ll dis[N+10],a[N+10],ans[N+10];
int cnt,L[N+10],R[N+10],siz[N+10];
std::vector<std::tuple<int,int,int>> q[N+10];
Node t[N*4+10];

// L[u], R[u] 表示以 u 为根的子树中的结点编号的 min 和 max。
void DFS1(int u){
	L[u]=++cnt;
	siz[u]=1;
	for(auto [v,w]:G[u]){
		dis[v]=dis[u]+w;
		DFS1(v);
		siz[u]+=siz[v];
	}
	R[u]=L[u]+siz[u]-1;
}

// 区间加，区间最小值
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void pushUp(int i){
	t[i].v=std::min(t[ls(i)].v,t[rs(i)].v);
}

inline void pushA(int i,ll atag){
	t[i].v+=atag;t[i].atag+=atag;
}

inline void pushDown(int i){
	if(t[i].atag){
		pushA(ls(i),t[i].atag);
		pushA(rs(i),t[i].atag);
		t[i].atag=0;
	}
}

void build(int i,int l,int r){
	if(l==r)return t[i].v=a[l],void();
	int mid=(l+r)>>1;
	build(ls(i),l,mid);
	build(rs(i),mid+1,r);
	pushUp(i);
}

void modify(int i,int l,int r,int ql,int qr,int x){
	if(ql<=l&&r<=qr)return pushA(i,x),void();
	int mid=(l+r)>>1;
	pushDown(i);
	if(ql<=mid)modify(ls(i),l,mid,ql,qr,x);
	if(qr>mid) modify(rs(i),mid+1,r,ql,qr,x);
	pushUp(i);
}

ll query(int i,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return t[i].v;
	int mid=(l+r)>>1;
	pushDown(i);
	ll res=inf;
	if(ql<=mid)res=std::min(res,query(ls(i),l,mid,ql,qr));
	if(qr>mid) res=std::min(res,query(rs(i),mid+1,r,ql,qr));
	return res;
}

#undef ls
#undef rs

void DFS2(int u){
	// 处理所有在 u 结点上的询问
	for(auto [l,r,id]:q[u])
		ans[id]=query(1,1,n,l,r);
	for(auto [v,w]:G[u]){
		modify(1,1,n,1,n,w);
		modify(1,1,n,L[v],R[v],-2*w);
		DFS2(v);
		modify(1,1,n,1,n,-w);
		modify(1,1,n,L[v],R[v],2*w);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		int x,y;scanf("%d%d",&x,&y);
		G[x].push_back({i,y});
	}
	for(auto &x:G)std::sort(x.begin(),x.end());
	for(int i=1;i<=m;i++){
		int v,l,r;scanf("%d%d%d",&v,&l,&r);
		q[v].push_back({l,r,i});
	}
	DFS1(1);
	for(int i=1;i<=n;i++){
		if(siz[i]==1)a[i]=dis[i];
		else a[i]=inf; // 如果不是叶子结点，直接设为 inf，以忽略它们对答案的影响
	}
	build(1,1,n);
	DFS2(1);
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：0)

其实这题并不需要用啥特殊性质，直接无脑点分治即可，在全局开个线段树维护dfs序区间内深度最小的叶子，然后把所有询问离线下来存在每个点上，点分治的时候先dfs一遍连通块把每个叶子的deep记在线段树上，然后再dfs一遍爆扫每个点的询问去线段树上查就行了，注意因为求的是最短路所以并不需要考虑区间里的叶子和自己在同一棵子树内的情况因为那样一定不优，复杂度显然$O(n\log^2n)$，开了4s所以可过……

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define ls(_o) (_o<<1)
#define inf 0x3f3f3f3f3f3f3f3f
#define rs(_o) ((_o<<1)|1)
#define up(_o) minn[_o]=min(minn[ls(_o)],minn[rs(_o)])
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	void print(ll num){
		if(num>=10)print(num/10);putchar(num%10+'0');
	}
	typedef struct _b{
		int dest;int nxt;int len;
	}bian;
	bian memchi[1000001];
	int gn=1,heads[500001];
	inline void add(int s,int t,int l){
		memchi[gn].dest=t;
		memchi[gn].len=l;
		memchi[gn].nxt=heads[s];
		heads[s]=gn;gn++;
	}
	int tmp[500001],stk[500001],dfn[500001];
	ll minn[2000001];
	unsigned char leaf[500001];
	ll query(int rl,int rr,int l,int r,int tree){
		if(rl==l&&rr==r)return(minn[tree]);
		int mid=(l+r)>>1;
		if(rl>mid)return(query(rl,rr,mid+1,r,rs(tree)));
		if(rr<=mid)return(query(rl,rr,l,mid,ls(tree)));
		return(min(query(rl,mid,l,mid,ls(tree)),query(mid+1,rr,mid+1,r,rs(tree))));
	}
	int nd[500001];int n;
	inline void setpt(int pt,ll num){
		minn[nd[pt]]=num;
		for(register int i=nd[pt]>>1;i;i>>=1)up(i);
	}
	void build(int l,int r,int tree){
		minn[tree]=inf;
		if(l==r){
			nd[l]=tree;return;
		}
		int mid=(l+r)>>1;
		build(l,mid,ls(tree));
		build(mid+1,r,rs(tree));
	}
	int gdfn=1,sp=0;
	void dfs(int pt,int baba){
		dfn[pt]=gdfn;gdfn++;
		int ptr=0;
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			if(memchi[i].dest==baba)continue;
			tmp[ptr]=memchi[i].dest,ptr++;
		}if(!ptr){
			leaf[pt]=1;return;
		}
		sort(tmp,tmp+ptr);reverse(tmp,tmp+ptr);
		for(register int i=0;i<ptr;i++)stk[sp]=tmp[i],sp++;
		while(ptr){
			ptr--;sp--;dfs(stk[sp],pt);
		}
	}
	ll anss[500001];
	int vec[500001];
	unsigned char bv[500001];
	typedef struct _n{
		int nxt;int l;int r;
	}node;
	node nodes[500001];
	int tot=0,zx;
	void afs(int pt,int baba){
		tot++;
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			if(bv[memchi[i].dest]||memchi[i].dest==baba)continue;
			afs(memchi[i].dest,pt);
		}
	}
	int size[500001];
	void bfs(int pt,int baba){
		int mx=0;size[pt]=1;
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			if(bv[memchi[i].dest]||memchi[i].dest==baba)continue;
			bfs(memchi[i].dest,pt);
			size[pt]+=size[memchi[i].dest];
			mx=max(mx,size[memchi[i].dest]);
		}
		if(max(mx,tot-size[pt])<=tot/2)zx=pt;
	}
	ll deep[500001];
	void cfs(int pt,int baba){
		if(leaf[pt])setpt(dfn[pt],deep[pt]);
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			if(bv[memchi[i].dest]||memchi[i].dest==baba)continue;
			deep[memchi[i].dest]=deep[pt]+memchi[i].len;
			cfs(memchi[i].dest,pt);
		}
	}
	void efs(int pt,int baba){
		for(register int i=vec[pt];i;i=nodes[i].nxt){
			anss[i]=min(anss[i],deep[pt]+query(nodes[i].l,nodes[i].r,1,n,1));
		}
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			if(bv[memchi[i].dest]||memchi[i].dest==baba)continue;
			efs(memchi[i].dest,pt);
		}
	}
	void ffs(int pt,int baba){
		if(leaf[pt])setpt(dfn[pt],inf);
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			if(bv[memchi[i].dest]||memchi[i].dest==baba)continue;
			ffs(memchi[i].dest,pt);
		}
	}
	void digui(int pt){
		tot=0;
		afs(pt,0);
		bfs(pt,0);
		int me=zx;
		deep[me]=0;
		cfs(me,0);
		efs(me,0);
		ffs(me,0);
		bv[me]=1;
		for(register int i=heads[me];i;i=memchi[i].nxt){
			if(bv[memchi[i].dest])continue;
			digui(memchi[i].dest);
		}
	}
	void ywymain(){
		n=get();
		int q=get();
		for(register int i=2;i<=n;i++){
			int s=get(),l=get();
			add(s,i,l);add(i,s,l);
		}
		build(1,n,1);
		dfs(1,0);
		for(register int i=1;i<=q;i++){
			int v=get(),l=get(),r=get();
			nodes[i].l=l;
			nodes[i].r=r;
			nodes[i].nxt=vec[v];
			vec[v]=i;
		}
		memset(anss,0x3f,sizeof(anss));
		digui(1);
		for(register int i=1;i<=q;i++)print(anss[i]),putchar('\n');
	}
}
int main(){
	ywy::ywymain();return(0);
}
```

---

## 作者：Gypsophila (赞：0)

### Description 

给你一颗满足编号 = dfs 序的带边权的有根树。$m$ 次询问，每次给出 $v,l,r$ 求编号在 $[l,r]$ 中的叶子到 $v$ 节点的最短距离

$n,m \leq 5\times10^5,w \leq 10^9$ 


### Solution 

如果我们知道 $u$ 节点到所有叶子的最短路，如何求出他的某一个儿子 $v$ 到所有叶子的最短路呢？

不妨设 $(u,v)$ 的边权是 $w$ 。那么在 $v$ 这颗子树内的叶子到 $v$ 的距离较 $u$ 要减少 $w$ ； $v$ 这颗子树外的叶子到 $v$ 的距离较 $u$ 要增加 $w$ 。

又良心出题人给的树是满足那个性质的，所以子树内的编号是连续的。

所以最开始 dfs 一遍。求出每个点到根的距离。把询问离线，进行一次先序遍历。

每次进入到一颗子树，就用线段树把该子树内的叶子减少 w 外面的增加 w

当回溯的父亲的时候，就用线段树把该子树内的叶子增加 w 外面的减少 w

然后遍历到一个节点就把和他有关的询问全都用线段树里的信息处理掉就行了

### Code

[看代码戳这里](https://acfunction.github.io/2019/02/09/CF1110F/)

---

