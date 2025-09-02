# Fools and Roads

## 题目描述

有一颗 $n$  个节点的树，$k$  次旅行，问每一条边被走过的次数。

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5
2
1 4
3 5
```

### 输出

```
2 1 1 1 
```

## 样例 #2

### 输入

```
5
3 4
4 5
1 4
2 4
3
2 3
1 3
3 5
```

### 输出

```
3 1 1 1 
```

# 题解

## 作者：MY_Lee (赞：15)

#### 闲聊

> 关于树剖，他太难了，所以要用树上差分来解决。

---
#### 思路
这是一道树上差分的较模板题。在学习树上差分之前，我们先来说说差分的基本思想。

前置知识：

1. 链式前向星存树 or 图
1. 倍增求 LCA
1. 前缀和与差分

---
差分是什么呢？差分从某种意义上来讲，就是前缀和的逆运算。~~(如果你连前缀和都不知道，不用做这道题了)~~它主要应用范围时是以 $O(m)$ 的时间解决形如“$m$ 次将 $[l,r]$ 区间中的所有数加 $x$，最后输出整个序列”。

是不是很神奇？

我们从暴力讲起：对于每次修改，循环从 $l\rightarrow r$，然后把 $a_i$ 加上 $x$ 即可。

但是这样的算法是 $O(nm)$ 的，出题人随便卡卡你就 T 飞了。

那么我们要怎么改进呢？很简单。

---
给定一个 $a$ 序列，先定义一个“差分数组”(我也忘了叫啥了，这不重要) $d_i=a_i-a_{i-1}$，于是我们发现：$d$ 数组的前缀和不就是 $a$ 数组吗？！

这就是差分的核心思想了，差分差分，就是在 $d$ 数组中修改，最后求出 $a$ 数组的值即为答案。

那么问题就变成了——怎么快速修改 $d$ 数组呢？

---
根据前缀和的思想，我们可以这么做：
```
d[l]+=x;d[r+1]-=x;
```
什么意思呢？

我们根据“差分数组”的定义，$a_l\rightarrow a_r$ 全部加 $1$，则原来 $d_l=a_l-a_{l-1}$ 变成了 $a_l+1-a_{l-1}$ 即 $d_l$ 被加上了 $x$。

同理 $d_{r+1}$ 被减掉了 $x$，而 $d_{l+1}\rightarrow d_{r-1}$ 都加了 $1$,一减抵消了，所以不用更新。

综上，我们发现时间复杂度是常数级别的，非常快。

这就是差分的基本内容啦，注意做完所有修改后要前缀和还原 $a$ 数组才是答案哦。

---
接下来，我们要把差分搬到树上做。

怎么做呢？很简单，假设从 $l\rightarrow r$，经过的每个点权值增加 $x$。那么更新的时候，
```
d[l]+=x;d[r]+=x;d[lca(l,r)]-=x;d[f[lca(l,r)]]-=x;
```
其中 $\operatorname{lca}(l,r)$ 的意思是 $l,r$ 的最近公共祖先，用倍增求，这里不多讲了；$f_i$ 数组表示 $i$ 的父亲节点编号。这样我们就完成了**点**的树上差分.

但是这道题要我们求**边**的树上差分，上面那个公式不再适用了。怎么办呢？
```
d[l]+=x;d[y]+=x;d[lca(x,y)]-=2*x;
```
这是**边**的差分公式，以上三个公式必须记牢。注意做完之后还要一次 dfs 将他们前缀和(即 $d_u=d_u+d_v,v$ 是 $u$ 的儿子节点)

关于这道~~恶心~~奇妙的输出：要求按边的输入顺序，那么我们可以把每条边看作他的两个顶点中深度较大的那个点来输出。即保存一下输入的 $x_i,y_i$，输出时比较 $dep_{x_i}$ 和 $dep_{y_i}$ 的大小(其中 $dep_i$ 表示深度，从 $1$ 开始)，然后输出叫大点的 $d$ 值即可。

---
#### 代码
因为我不会跟简短的做法，于是我给出我的~~拖泥带水~~的辣鸡代码。

~~`limingye` 的同学：`limingye` 的码风丑死了！~~
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
struct Edge{
	int to;
	int nxt;
	int head;
};
Edge edge[200005];
int n,m,u,v,lg[100005],x[100005],y[100005],point,anc[100005][20],depth[100005],diff[100005];
inline void init_log(){
	lg[1]=1;
	for(register int i=2;i<=n;i++){
		if(1<<lg[i-1]==i){
			lg[i]=1;
		}
		lg[i]+=lg[i-1]; 
	}
}
inline void add_edge(int u,int v){
	point++;
	edge[point].to=v;
	edge[point].nxt=edge[u].head;
	edge[u].head=point;
}
inline void dfs_anc(int now,int father){
	anc[now][0]=father;
	depth[now]=depth[father]+1;
	for(register int i=1;i<=lg[depth[now]];i++){
		anc[now][i]=anc[anc[now][i-1]][i-1];
	}
	int tmp=edge[now].head;
	while(tmp>0){
		int son=edge[tmp].to;
		if(son==father){
			tmp=edge[tmp].nxt;
			continue;
		}
		dfs_anc(son,now);
		tmp=edge[tmp].nxt;
	}
}
inline int lca(int a,int b){
	if(depth[a]<depth[b]){
		swap(a,b);
	}
	while(depth[a]>depth[b]){
		a=anc[a][lg[depth[a]-depth[b]]-1];
	}
	if(a==b){
		return b;
	}
	for(register int i=lg[depth[a]]-1;i>=0;i--){
		if(anc[a][i]!=anc[b][i]){
			a=anc[a][i];
			b=anc[b][i];
		}
	}
	return anc[a][0];
}
inline void dfs_answer(int now,int father){
	int tmp=edge[now].head;
	while(tmp>0){
		int son=edge[tmp].to;
		if(son==father){
			tmp=edge[tmp].nxt;
			continue;
		}
		dfs_answer(son,now);
		diff[now]+=diff[son];
		tmp=edge[tmp].nxt;
	}
}
int main(){
	scanf("%d",&n);
	init_log();
	for(register int i=1;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);
		add_edge(x[i],y[i]);
		add_edge(y[i],x[i]);
	}
	dfs_anc(1,0);
	scanf("%d",&m);
	for(register int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		diff[u]++;
		diff[v]++;
		diff[lca(u,v)]-=2;
	}
	dfs_answer(1,0);
	for(register int i=1;i<n;i++){
		u=x[i],v=y[i];
		if(depth[u]>depth[v]){
			printf("%d ",diff[u]);
		}
		else{
			printf("%d ",diff[v]);
		}
	}
	printf("\n");
	return 0;
}
```
---
#### 番外

啊我也不知道有什么好写的，祝大家 [CF 上分愉快！](https://moon-snow.blog.luogu.org/)

---

## 作者：_H1kar1 (赞：8)

去看题解大佬打的看不懂...只好自己努力（~~连蒙带抄~~）写了好久终于过了

竟然没人发树剖？（~~害我调半天~~）结合我自己看不懂题解的经验，我尽量写清楚些，顺便介绍几个调错的小技巧hhh

#### 树链剖分的思想？

树剖，简单来说就是将一棵树分成**由轻边连成都重链**，从而使得问题大大简化

我们假设每一个节点重量是1，那么对于任意一个节点，他的子树中更重的那个，我们称之为**重孩子**，其他都称之为**轻孩子**。我们知道，每一个节点都会有一个重孩子，那么这一串重孩子链我们称之为**重链**，反之呢，连接轻孩子的边称之为**轻边**

自己随便找些树来画一画，~~易证~~每一棵树都可以分为若干条重链，重链与重链间由轻边链接

#### 首先是每个数组的含义
```cpp
int sz[N],hs[N],f[N],tp[N],dep[N];
```
* sz是以每个节点为根的子树的重量
* hs是每个节点的重孩子
* f是每个节点的父亲
* tp是每个节点所处的重链的顶
* dep是每个节点在树中的深度

#### 这里是树剖的dfs：
```cpp
int sz[N],hs[N],f[N],tp[N],dep[N];
void dfs1(int x,int fa){
	dep[x]=dep[fa]+1;
	sz[x]=1;
	f[x]=fa;
	hs[x]=0;
	for(int i=head[x];i;i=nxt[i]){
		int y=G[i];
		if(y==fa)	continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[hs[x]])
			hs[x]=y;
	}
}

void dfs2(int x,int t){
	tp[x]=t;
	if(hs[x])
		dfs2(hs[x],t);
	for(int i=head[x];i;i=nxt[i]){
		int y=G[i];
		if(y==f[x] || y==hs[x])	continue;
		dfs2(y,y);
	}
}

```
#### 用树剖求LCA的思想是：

* 对于两个点，如果不处于同一条重链，就像上跳出当前重链直到处于同一条，那么此时他们必定一个高一个低

```cpp
inline int LCA(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]>=dep[tp[y]])
			x=f[tp[x]];
		else	y=f[tp[y]];
        //特别注意，必须跳出重链，也就是跳到顶的父亲上
	}
	return dep[x]>dep[y]?y:x;
}
```

#### 这道题已经有大佬曰过，差分做法是
```cpp
++s[x],++s[y],s[LCA(x,y)]-=2;
```

那么我们在一个dfs中将这个影响施加到整个路径上
```cpp
int s[N],ans[N],id[N];
void dfs3(int x){
	for(int i=head[x];i;i=nxt[i]){
		int y=G[i];
		if(y==f[x])	continue;
		dfs3(y);
		s[x]+=s[y];
	}
	ans[id[x]]=s[x];
}
```

感觉这个做法还不错，最慢也不过300ms


#### 这里是源码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;

const int N=210000,M=N<<1;//请注意2倍... 

struct node{
	int x,y;
	node(int x=0,int y=0):x(x),y(y){}
};
node edge[N];//单项不开二倍 
int G[M],head[N],nxt[M],e_cnt=0;
inline void add(int x,int y){
	//前向星 
	G[++e_cnt]=y;
	nxt[e_cnt]=head[x];head[x]=e_cnt;
}

int sz[N],hs[N],f[N],tp[N],dep[N];
//我猜你们记不住数组的含义，往前翻翻吧 
void dfs1(int x,int fa){
	dep[x]=dep[fa]+1;
	sz[x]=1;
	f[x]=fa;
	hs[x]=0;
	for(int i=head[x];i;i=nxt[i]){
		int y=G[i];
		if(y==fa)	continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[hs[x]])
			hs[x]=y;
	}
}

void dfs2(int x,int t){
	tp[x]=t;
	if(hs[x])
		dfs2(hs[x],t);
	for(int i=head[x];i;i=nxt[i]){
		int y=G[i];
		if(y==f[x] || y==hs[x])	continue;
		dfs2(y,y);
	}
}

inline int LCA(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]>=dep[tp[y]])
			x=f[tp[x]];
		else	y=f[tp[y]];
	}
	return dep[x]>dep[y]?y:x;
}

int s[N],ans[N],id[N];
void dfs3(int x){
	for(int i=head[x];i;i=nxt[i]){
		int y=G[i];
		if(y==f[x])	continue;
		dfs3(y);
		s[x]+=s[y];
	}
	ans[id[x]]=s[x];
}

int main(){
	ios::sync_with_stdio(0);
	//关闭同步 
	int n,k;//n个点和k次问询 
	cin>>n;
	for(int i=1;i<n;++i){
		int x,y;
		cin>>x>>y;
		edge[i]=node(x,y);
		add(x,y);	add(y,x);
	}
	
	dfs1(1,0); 
	dfs2(1,1); 
	//这个题要按照边的顺序输出，很烦
	//我们将边的权值施加到深度较大的那个点上 
	for(int i=1;i<n;++i)
		if(dep[edge[i].x]>dep[edge[i].y])
			id[edge[i].x]=i;
		else
			id[edge[i].y]=i;
			
	cin>>k;
	for(int i=1;i<=k;++i){
		int x,y;
		cin>>x>>y;
		++s[x],++s[y],s[LCA(x,y)]-=2;
		//cout<<"lca="<<LCA(x,y)<<endl;
		//这里是个debug的好地方，对于本题来说差分难度不大，而lca直接是模板
		//在这里检查lca结果可以迅速确定出错位置 
	}
	
	dfs3(1);//处理权值，差分
	for(int i=1;i<n;++i)
		//输答案跑路 
		cout<<ans[i]<<' '; 
	
	return 0;
}

```


---

## 作者：stepsys (赞：6)

题意 : 给你一棵树，然后给你m对点，将每对点之间的最短路径上每条边权值+1，求操作完成后每条边的权值

solution:树上差分（其实如果你是数据结构大师的话也可以用树链剖分做）

树上差分的板子是这样的：
设差分数组p,对于路径s->t，p[s]++,p[t]++,p[lca(s,t)]--,p[fa[lca[(s,t)]]]--;

然后一个点的子树内差分数组值之和即为*该点*被覆盖的次数
然而这题要求我们处理边

那么我们有两种方法

一种是对于一条边，新建一个点代表这条边，由该点向边的两个端点连边

暴力但很无脑

另一种是用一条边的两个端点中深度较大的端点代表这条边

但此时原来的差分操作会出锅，要改为p[s]++,p[t]++,p[lca(s,t)]-=2（自己理解）

贴代码（第一种方法，欧拉序ST表求LCA）

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define N 400050
using namespace std;
vector<int> G[N];
int n,m;
int dfn[N],pos[N],lg[N],dep[N];
int id[N],ans[N];
int st[35][N],cnt=0,plu[N],fa[N];
void aux(int x,int ff) {
	dfn[++cnt]=x,pos[x]=cnt,fa[x]=ff;
	for(int i=0; i<G[x].size(); i++) {
		int to=G[x][i];
		if(to==ff)continue;
		dep[to]=dep[x]+1;
		aux(to,x);
		dfn[++cnt]=x;
		}
	}
int mn(int a,int b) {
	return (dep[a]<dep[b])?a:b;
	}
void build() {
	lg[0]=-1;
	for(int i=1; i<=N-10; i++)lg[i]=lg[i>>1]+1;
	for(int i=1; i<=cnt; i++)st[0][i]=dfn[i];
	for(int i=1; i<=lg[cnt]; i++)
		for(int r=1; r+(1<<i)<=cnt; r++)
			st[i][r]=mn(st[i-1][r],st[i-1][r+(1<<(i-1))]);
	}
int lca(int a,int b) {
	int x=pos[a],y=pos[b];
	if(x>y)swap(x,y);
	int p=lg[y-x+1];
	return mn(st[p][x],st[p][y-(1<<p)+1]);
	}
void add_edge(int a,int b) {
	G[a].push_back(b),G[b].push_back(a);
	}
void all_last(int x,int ff) {
	for(int i=0; i<G[x].size(); i++) {
		int to=G[x][i];
		if(to==ff)continue;
		all_last(to,x);
		plu[x]+=plu[to];
		}
	if(id[x])ans[id[x]]=plu[x];
	}
int main() {
	scanf("%d",&n);
	for(int i=1; i<n; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		add_edge(a,i+n);
		add_edge(i+n,b);
		id[i+n]=i;
		}
	aux(1,0);
	build();
	scanf("%d",&m);
	for(int i=1; i<=m; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		int poi=lca(a,b);
		plu[fa[poi]]--;
		plu[poi]--;
		plu[a]++,plu[b]++;
		}
	all_last(1,0);
	for(int i=1; i<n; i++)printf("%d ",ans[i]);
	}

```

---

## 作者：极寒神冰 (赞：5)

树上差分模版题，这题每次都是固定增加1.

需要注意的是差分的时候两个点的公共祖先会被这两个点都加一次要，所以要-2.

（如果实在不能理解可以画张图看一下，鉴于本人画图能力为-INF就不画了QAQ）

```
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
struct edge
{
	int to,nxt,id;
};
edge e[N];
int E;
int dep[N],cnt[N],ans[N],head[N];
int dp[N][22];
int n,k,u,v;
inline void init_st()
{
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dp[j][i]=dp[dp[j][i-1]][i-1];//预处理倍增数组
		}
	}
}
inline void init_e()
{
	E=0;
	memset(head,-1,sizeof(head));//初始化
}
inline void add(int u,int v,int id)
{
	e[++E].nxt=head[u];
	e[E].to=v;
	e[E].id=id;
	head[u]=E;
}
inline void dfs(int u,int fa)
{
	dp[u][0]=fa;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dep[v]=dep[u]+1;//先dfs遍历一遍建树
		dfs(v,u);
	}
}
inline int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	int del=dep[x]-dep[y];
	for(int i=0;i<=20;i++)
	{
		if(del&(1<<i)) x=dp[x][i];
	}
	if(x==y) return x;
	for(int i=20;i>=0;i--)
	{
		if(dp[x][i]!=dp[y][i])
		{
			x=dp[x][i];
			y=dp[y][i];
		}
	}
	return dp[x][0];//倍增求公共祖先
}
inline void solve(int u,int fa)
{
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		solve(v,u);
		cnt[u]+=cnt[v];
		ans[e[i].id]=cnt[v];//求出每一个点的值
	}
}
int main()
{
	init_e();
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v,i);add(v,u,i);
	}
	dfs(1,0);
	init_st();
	k=read();
	for(int i=1;i<=k;i++)
	{
		int x=read(),y=read();
		cnt[x]++,cnt[y]++;
		cnt[lca(x,y)]-=2;//差分
	}
	solve(1,0);
	for(int i=1;i<n;i++)
	{
		cout<<ans[i]<<" ";
	}
}
```


---

## 作者：shame_djj (赞：4)

细节写挂，交了两遍，写篇题解，提醒自己~~

~~主要是立下了这遍 AC 我就写题解的 flag~~

原题连接[【Fools and Roads】](https://www.luogu.org/problem/CF191C)

题意

		给出一棵树，给出 m 对点，

		每对点之间的路径全部加一，最后输出每条边的值

这一看就是~~树上差分~~树剖啊

思路

		树剖，将边对应到深度大的点，差分维护区间加

没有太多要说的，主要就是细节

我踩的坑

		1、差点写了数据结构来维护区间加，高级数据结构病，本题差分就好了

		2、关于从边到点的数组映射，用混了，实际上就是打错了一个变量，调了十几分钟

没了，另外推荐一道和本题很像的题，思路一模一样，而且那道题是维护点权，更好实现

[【[USACO15DEC]最大流Max Flow】](https://www.luogu.org/problem/P3128)

然后是本题的代码，跑了 3.96 s

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

inline int read() {
    char c = getchar(); int x = 0, f = 1;
    for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
    for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

int ver[maxn << 1], nxt[maxn << 1], rk[maxn << 1], head[maxn], rk_[maxn], tot;
int dep[maxn], fa[maxn], son[maxn], size[maxn], maxson;
int id[maxn], top[maxn], cnt_;
int n, m, u, v;

void add (int u, int v, int i) {
    ver[++ tot] = v, nxt[tot] = head[u], head[u] = tot;
    rk[tot] = i;
}

struct djj_lxy_aa {
    int a[maxn];

    void change (int l, int r, int x) {
        a[l] += x, a[r + 1] -= x;
    }

    void finish () {
        for (register int i = 1; i <= n; i ++)
            a[i] = a[i - 1] + a[i];
    }
} t;

void dfs1 (int x, int f, int deep) {
    dep[x] = deep, fa[x] = f;
    size[x] = 1, maxson = -1;
    for (register int i = head[x]; i; i = nxt[i]) {
        if (ver[i] == f) continue ;
        rk_[rk[i]] = ver[i];
        dfs1 (ver[i], x, deep + 1);
        size[x] += size[ver[i]];
        if (size[ver[i]] > maxson)
            maxson = size[ver[i]], son[x] = ver[i];
    }
}

void dfs2 (int x, int topf) {
    top[x] = topf, id[x] = ++ cnt_;
    if (!son[x]) return ;
    dfs2 (son[x], topf);
    for (register int i = head[x]; i; i = nxt[i]) {
        if (ver[i] == son[x] || ver[i] == fa[x])
            continue ;
        dfs2 (ver[i], ver[i]);
    }
}

void solve (int u, int v) {
    for (; top[u] != top[v]; ) {
        if (dep[top[u]] < dep[top[v]])
            swap (u, v);
        if (u == top[u]) {
            t.change (id[u], id[u], 1);
            u = fa[u];
        }
        else {
            t.change (id[top[u]] + 1, id[u], 1);
            u = top[u];
        }
    }
    if (dep[u] > dep[v]) swap (u, v);
    t.change (id[u] + 1, id[v], 1);
}

void djj () {
    n = read();
    for (register int i = 1; i < n; i ++)
        u = read(), v = read(), add (u, v, i), add (v, u, i);
    dfs1 (1, 1, 1), dfs2 (1, 1);
}

void lxy () {
    for (m = read(); m; m --) {
        u = read(), v = read();
        solve (u, v);
    }
    t.finish ();
    for (register int i = 1; i < n; i ++)
        printf ("%d ", t.a[id[rk_[i]]]);
}

void djj_lxy () {
    djj (), lxy ();
}

int main () {
    djj_lxy ();
}
//个人习惯，把样例粘到代码下面，然后就不用返回原来界面了
/*
5
1 2
1 3
2 4
2 5
2
1 4
3 5

2 1 1 1
*/

/*
5
3 4
4 5
1 4
2 4
3
2 3
1 3
3 5

3 1 1 1
*/

```

常规题，大家一定要注意细节

最好是能一遍 AC, 毕竟考场上只能交一遍

距离新 Noip 还有一个多月时间，祝大家 rp ++

也希望自己能更努力一些，加油！

---

## 作者：ModestCoder_ (赞：4)

我记得有一道题目叫做“最大流”（可不是网络流）

那道题目是询问每个点经过了几次；这道题目是每条边经过了几次

同样是裸的树上差分，但是边和点的差分是不一样的

边是```++power[u],++power[v],power[lca]-=2```

点是```++power[u],++power[v],--power[lca],--power[fa[lca]]```

这道题还要一个**以点代边**的操作

是不是特别水啊

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
struct Edge{
	int to, next;
}edge[maxn << 1];
struct Line{
	int x, y;
}line[maxn];
int num, head[maxn], d[maxn], fa[maxn][25], power[maxn], n, m, ans[maxn], id[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
} 

void addedge(int x, int y){ edge[++num] = (Edge){ y, head[x] }; head[x] = num; }

void dfs(int u, int pre){
	d[u] = d[pre] + 1, fa[u][0] = pre;
	for (int i = 0; fa[u][i]; ++i) fa[u][i + 1] = fa[fa[u][i]][i];
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v != pre) dfs(v, u);
	}
}

int Lca(int u, int v){
	if (d[u] > d[v]) swap(u, v);
	for (int i = 20; i >= 0; --i) if (d[u] <= d[v] - (1 << i)) v = fa[v][i];
	if (u == v) return u;
	for (int i = 20; i >= 0; --i) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

void dfs(int u){
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v != fa[u][0]) dfs(v), power[u] += power[v];
	}
	ans[id[u]] = power[u];
}

int main(){
	n = read();
	for (int i = 1; i < n; ++i){
		line[i].x = read(), line[i].y = read();
		addedge(line[i].x, line[i].y); addedge(line[i].y, line[i].x);
	}
	dfs(1, 0);
	for (int i = 1; i < n; ++i)
		if (d[line[i].x] > d[line[i].y]) id[line[i].x] = i; else id[line[i].y] = i;
	m = read();
	while (m--){
		int x = read(), y = read(), lca = Lca(x, y);
		++power[x], ++power[y], power[lca] -= 2;
	}
	dfs(1);
	for (int i = 1; i < n; ++i) printf("%d ", ans[i]);
	return 0;
}
```


---

## 作者：Fuko_Ibuki (赞：2)

这个题其实是一个经典树上差分题.我们维护一个差分数组f.  
对于一组$u,v$不相等的询问,我们考虑找到$u,v$的最近公共祖先$p$,把$f[u]++,f[v]++$,然后把$f[p]-=2$.如果在线求出它们的最近公共祖先,这题的思路会好想一些.  
最后一遍dfs,把差分数组重新加起来,就得到了答案.  
不要忘记加边的时候加入边的编号就可以了.  
代码实现用了**tarjan**求最近公共祖先,求最近公共祖先的步骤和差分混在了一起,所以看起来比较迷.
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;//first是边指向的点,second是边的序号
const int boss=1e5;
typedef int fuko[boss|10];
vector<pii> lj[boss|10];
vector<int> fo[boss|10];
fuko fa,ans,f,vis;int n,k;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
//结合tarjan求lca的代码应该能读懂这个dfs.
void dfs(int x)
{
fa[x]=x,vis[x]=1;
for (int i:fo[x]) f[x]++,vis[i]?f[find(i)]-=2:0;
for (pii i:lj[x]) if (!vis[i.first]) 
  {
  dfs(i.first);
  f[x]+=ans[i.second]=f[i.first];
  //ans[i.second]最后一次更新的结果就是答案了,因为此时询问到的节点(i.first)深度最小.
  fa[find(i.first)]=x;
  }
}

int main()
{
int i,u,v,k;
scanf("%d",&n);
for (i=1;i<n;i++) 
  {
  scanf("%d%d",&u,&v);
  lj[u].push_back(pii(v,i));
  lj[v].push_back(pii(u,i));
  }
scanf("%d",&k);
for (i=1;i<=k;i++) 
  {
  scanf("%d%d",&u,&v);
  if (u!=v) //差分不用考虑u=v的情况
    {
    fo[u].push_back(v);
	fo[v].push_back(u); 
	}
  }dfs(1);
for (i=1;i<n;i++) printf("%d ",ans[i]);
}
```

---

## 作者：qianfujia (赞：2)

## 这里提供一种新思路
**树上差分**

>Node[LCA] -= 2;

>Node[u] ++;

>Node[v] ++;

**求子树和**

>Node[u] += Node[v] (v is u's son)

**求树上前缀和**

>F[u] = F[u's Father] + Node[u];

**询问**

>F[son] - F[father]

**时间复杂度**

>3遍DFS，LCA

>$O(k\ log_2n\ +\ n)$

**代码**

```cpp
#include<bits/stdc++.h>
#define N 100010
#define LogN 20
using namespace std;

struct EDGE{
	int u, v;
	int Next;
}G[N << 1];

int tot = 0;
int Head[N];

inline void AddEdge(int u, int v)
{
	++ tot;
	G[tot].u = u;
	G[tot].v = v;
	G[tot].Next = Head[u];
	Head[u] = tot;
}

int n;
int BZ[N][LogN];
int Dep[N];

inline void DFS(int u)
{
	Dep[u] = Dep[BZ[u][0]] + 1;
	for(int i = Head[u]; i; i = G[i].Next)
	{
		int v = G[i].v;
		if(v == BZ[u][0])
			continue;
		BZ[v][0] = u;
		DFS(v);
	}
}

inline void Cal()
{
	for(int i = 1; i < LogN; ++ i)
		for(int j = 1; j <= n; ++ j)
			BZ[j][i] = BZ[BZ[j][i - 1]][i - 1];
}

inline int Get_LCA(int u, int v)
{
	if(Dep[u] < Dep[v])
		swap(u, v);
	for(int i = LogN - 1; i >= 0; -- i)
		if(Dep[BZ[u][i]] >= Dep[v])
			u = BZ[u][i];
	if(u == v)
		return u;
	for(int i = LogN - 1; i >= 0; -- i)
		if(BZ[u][i] != BZ[v][i])
		{
			u = BZ[u][i];
			v = BZ[v][i];
		}
	return BZ[u][0];
}

int A[N];
int B[N];

int Node[N];

inline void DFS2(int u)
{
	for(int i = Head[u]; i; i = G[i].Next)
	{
		int v = G[i].v;
		if(v == BZ[u][0])
			continue;
		DFS2(v);
		Node[u] += Node[v];
	}
}

int F[N];

inline void DFS3(int u, int val)
{
	F[u] = Node[u] + val;
	for(int i = Head[u]; i; i = G[i].Next)
	{
		int v = G[i].v;
		if(v == BZ[u][0])
			continue;
		DFS3(v, F[u]);
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++ i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		A[i] = u;
		B[i] = v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	DFS(1);
	Cal();
	int k;
	scanf("%d", &k);
	for(int i = 1; i <= k; ++ i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int LCA = Get_LCA(u, v);
		++ Node[u];
		++ Node[v];
		Node[LCA] -= 2;
	}
	
	DFS2(1);
	DFS3(1, 0);
	
	for(int i = 1; i < n; ++ i)
	{
		int u = A[i];
		int v = B[i];
		if(Dep[u] < Dep[v])
			swap(u, v);
		printf("%d ", F[u] - F[v]);
	}
	return 0;
} 
```

---

## 作者：影踪派武僧 (赞：1)

树上差分半裸题

常规思路是进行三次DFS，然后常规运算即可

这里提供两次dfs的思路（**wyz tql orz**）

我们以样例2为例
![](https://i.loli.net/2019/02/21/5c6e936f5a219.png)

我们考虑任意一条路径，令其起点为u终点为v，每走一次当前路径则v的访问次数必定+1，于是我们可以使每一个点表示连接其上的一条边的访问次数，所以我们令节点v的访问次数+1;

与此同时，过程中的路径也同样会被访问，且这里是双向边，于是与此同时的我们也令节点u的访问次数+1;当然访问当前子树下根节点中包含的两个点并不会访问，而我们在增加u和v的访问时同时也错误地增加了其公共父节点的访问量，于是我们令lca(u,v)的访问量-2即可。

例如上图中我们从节点5走到节点3，我们令节点3与节点5的访问次数+1，同时使节点4的访问次数-2。

如下：

```cpp
while(k--){
    int u=read(),v=read();
    diff[u]++,diff[v]++,diff[lca(u,v)]-=2;
}
```

最后输出答案时只需要判断每条边两端点的深度大小即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 100005
using namespace std;
inline char get(){
    static char buf[30000],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,30000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    register char c=get();register int f=1,_=0;
    while(c>'9' || c<'0')f=(c=='-')?-1:1,c=get();
    while(c<='9' && c>='0')_=(_<<3)+(_<<1)+(c^48),c=get();
    return _*f;
}
struct edge{
    int u,v,w,next;
    int num=0;
}E[maxn<<1];
int n,k;
int p[maxn],eid;
int d[maxn], parent[maxn][20];
int diff[maxn];
inline void init(){
    for(register int i=0;i<maxn;i++)p[i]=d[i]=-1;
    eid=0;
}
inline void insert(int u,int v){
    E[eid].u=u;
    E[eid].v=v;
    E[eid].next=p[u];
    p[u]=eid++;
}
inline void insert2(int u,int v){
    insert(u,v);
    insert(v,u);
}
void dfs(int u){
    for (register int i=p[u];~i;i=E[i].next) {
        if (d[E[i].v]==-1){
            d[E[i].v]=d[u]+1;
            parent[E[i].v][0]=u;
            dfs(E[i].v);
        }
    }
}
int lca(int x, int y) {
    int i,j;
    if(d[x]<d[y])swap(x,y);
    for(i=0;(1<<i)<=d[x];i++);
    i--;
    for(register int j=i;j>=0;j--){
        if (d[x]-(1<<j)>=d[y])x=parent[x][j];
    }
    if(x==y)return x;
    for(register int j=i;j>=0;j--){
        if(parent[x][j]!=parent[y][j]) {
            x=parent[x][j];
            y=parent[y][j];
    	}
    }
    return parent[x][0];
}
int dd[maxn];
void dfs_(int u,int fa,int flag){
	dd[u]=flag;
    for(register int i=p[u];~i;i=E[i].next){
        int v=E[i].v;
        if(fa==v)continue;
        dfs_(v,u,flag+1);
        diff[u]+=diff[v];
    }
}
int u[maxn],v[maxn];
signed main(){
    //freopen("1.txt","r",stdin);
    init();
    n=read();
    for(register int i=2;i<=n;i++){
        u[i]=read(),v[i]=read();
        insert2(u[i],v[i]);
    }
    d[1]=0;
    dfs(1);
    for(register int level=1;(1<<level)<=n;level++){
        for(register int i=1;i<=n;i++){
            parent[i][level]=parent[parent[i][level-1]][level-1];
        }
    }
    k=read();
    while(k--){
        int casu=read(),casv=read();
        diff[casu]++,diff[casv]++,diff[lca(casu,casv)]-=2;
    }
    dfs_(1,-1,1);
    for(register int i=2;i<=n;i++){
    	if(dd[u[i]]>=dd[v[i]])cout<<diff[u[i]]<<" ";
    	else cout<<diff[v[i]]<<" ";
	}
    return 0;
}
```

---

## 作者：Aleph1022 (赞：1)

显然树上差分，那么配合 LCA。  
反正在下用了树剖，还有 BFS 赛高！

所以诸位大佬的 DFS 实现的操作都被我换成了用 **BFS 序**实现。  
做一次 BFS 并保留遍历的序列即可。

代码：
```cpp
#include <cstdio>
using namespace std;
const int N = 2e5;
int n,k;
int to[(N << 1) + 10],pre[(N << 1) + 10],first[N + 10];
int c[N + 10];
int dep[N + 10],fa[N + 10],sz[N + 10],son[N + 10],top[N + 10];
int q[N + 10],head,tail;
inline void add(int u,int v)
{
	static int tot = 0;
	to[++tot] = v;
	pre[tot] = first[u];
	first[u] = tot;
}
inline int getlca(int x,int y)
{
	while(top[x] ^ top[y])
		dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
	return dep[x] < dep[y] ? x : y;
}
int main()
{
	scanf("%d",&n);
	int x,y;
	for(register int i = 1;i < n;++i)
		scanf("%d%d",&x,&y),add(x,y),add(y,x);
	q[++tail] = dep[1] = 1;
	int p;
	while(head < tail)
	{
		p = q[++head];
		sz[p] = 1;
		for(register int i = first[p];i;i = pre[i])
			if(to[i] ^ fa[p])
			{
				q[++tail] = to[i];
				dep[to[i]] = dep[p] + 1;
				fa[to[i]] = p;
			}
	}
	for(register int i = n;i;--i)
	{
		sz[fa[q[i]]] += sz[q[i]];
		if(!son[fa[q[i]]] || sz[q[i]] > sz[son[fa[q[i]]]])
			son[fa[q[i]]] = q[i];
	}
	for(register int i = 1;i <= n;++i)
		top[q[i]] = son[fa[q[i]]] == q[i] ? top[fa[q[i]]] : q[i];
	scanf("%d",&k);
	while(k--)
	{
		scanf("%d%d",&x,&y);
		int lca = getlca(x,y);
		++c[x],++c[y],c[lca] -= 2;
	}
	for(register int i = n;i;--i)
		c[fa[q[i]]] += c[q[i]];
	for(register int i = 1;i < n;++i)
		printf("%d ",c[dep[to[i * 2]] > dep[to[i * 2 - 1]] ? to[i * 2] : to[i * 2 - 1]]);
}
```

---

## 作者：LJC00118 (赞：0)

直接求边走过的次数不好求，我们对树进行一次 dfs，考虑到每个点只有一个父亲，我们用点 $ u $ 表示从它父亲连到它的边，根节点不表示边

用一个树上差分维护每条边经过的次数即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 1e5 + 5;

map < pair <int, int>, int > wxw;
vector <int> adj[N];
int fa[N][20], d[N], s[N], id[N], ans[N];
int n, m;

void dfs1(int u, int father) {
    fa[u][0] = father;
    for(register int i = 1; i <= 18; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(register unsigned i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if(v != father) {
            d[v] = d[u] + 1;
            dfs1(v, u);
            id[v] = wxw[make_pair(u, v)];
        }
    }
}

int LCA(int u, int v) {
    if(d[u] < d[v]) swap(u, v);
    for(register int i = 18; i >= 0; i--)
        if(d[fa[u][i]] >= d[v])
            u = fa[u][i];
    // fprintf(stderr, "u = %d, v = %d\n", u, v);
    if(u == v) return u;
    for(register int i = 18; i >= 0; i--)
        if(fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

void dfs2(int u, int father) {
    for(register unsigned i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if(v != father) {
            dfs2(v, u);
            s[u] += s[v];
        }
    }
}

int main() {
    read(n);
    for(register int i = 1; i < n; i++) {
        int u, v;
        read(u); read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        wxw[make_pair(u, v)] = i;
        wxw[make_pair(v, u)] = i;
    }
    d[1] = 1;
    dfs1(1, 0);
    read(m);
    for(register int i = 1; i <= m; i++) {
        int u, v;
        read(u); read(v);
        ++s[u]; ++s[v]; s[LCA(u, v)] -= 2;
        // fprintf(stderr, "LCA(%d, %d) = %d\n", u, v, LCA(u, v));
    }
    dfs2(1, 0);
    for(register int i = 2; i <= n; i++) ans[id[i]] = s[i];
    for(register int i = 1; i < n; i++) print(ans[i], ' ');
    putchar('\n');
    return 0;
}
```

---

