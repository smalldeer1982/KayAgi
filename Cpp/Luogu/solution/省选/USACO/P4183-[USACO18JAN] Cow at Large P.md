# [USACO18JAN] Cow at Large P

## 题目描述

Bessie 被逼到了绝境，躲进了一个偏远的农场。这个农场由 $N$ 个谷仓（$2 \leq N \leq 7 \cdot 10^4$）和 $N-1$ 条双向隧道组成，因此每对谷仓之间都有一条唯一的路径。每个只有一个隧道的谷仓都是一个出口。当早晨来临时，Bessie 会从某个谷仓出现，并试图到达一个出口。

但是，当 Bessie 从某个谷仓出现时，执法人员会立即定位到她的位置。一些农民会从各个出口谷仓出发，试图抓住 Bessie。农民和 Bessie 的移动速度相同（因此在每个时间步中，每个农民可以从一个谷仓移动到相邻的谷仓）。农民们始终知道 Bessie 的位置，而 Bessie 也始终知道农民们的位置。如果农民和 Bessie 在同一谷仓或同时穿过同一条隧道，农民就会抓住 Bessie。相反，如果 Bessie 在农民抓住她之前严格地到达一个出口谷仓，她就能逃脱。

Bessie 不确定她应该从哪个谷仓出现。对于每个谷仓，请帮助 Bessie 确定如果她从该谷仓出现，假设农民们最优地分布在出口谷仓中，抓住她所需的最少农民数量。

请注意，本题的时间限制略高于默认值：C/C++/Pascal 为 4 秒，Java/Python 为 8 秒。

## 样例 #1

### 输入

```
7
1 2
1 3
3 4
3 5
4 6
5 7```

### 输出

```
3
1
3
3
3
1
1```

# 题解

## 作者：lgswdn_SA (赞：45)

希望写的能比别的题解更加详细

## 分析

贝西需要跑到树的叶节点才行。我们不妨现设贝西的出发点为根。

我们要做的是“封锁点”，就是在站在一个点上阻止贝西通行。一旦准时站在点 $u$ 上，就等于封锁了整个子树内的点，因为贝西将无法进入这棵子树内部。目标是封锁所有叶节点。

我们称一个农民要站着封锁子树的点 $u$ 为封锁点（自己瞎扯的名字）。

所以我们现在要合理地安排封锁点。由贪心的想法可知，我们做到每个叶节点只被一个封锁点封锁。

### 封锁点的规则

![image.png](https://i.loli.net/2020/03/24/n9IiDjz1s3kAoMu.png)

我们先看这张图。我们希望确定橙点能不能成为一个封锁点。封锁点要求能**成功准时**地封锁住贝西，所以一定需要存在一个出口，使得农夫能**在贝西抵达并穿过封锁点进入子树前到达封锁点**。

因为可以说准时到达封锁点是让贝西不进入子树内地叶节点的**唯一机会**。一旦比贝西晚到达，你就永远也追不上它了，它会长驱直入逃走。

所以我们必须制定这个规则。

![image.png](https://i.loli.net/2020/03/24/l7pCNsIQ8v3xqYn.png)

黄色小点是最接近封锁点的出口，紫色路径是农夫到达封锁点的路径，黑色路径是贝西试图到达封锁点然后长驱直入逃跑的路径。

显然，我们需要紫色路径长度$\le$黑色路径长度。

还有，为了保证是最优解，一旦父亲可以做封锁点，那么儿子就不用再做封锁点了。

![image.png](https://i.loli.net/2020/03/25/tiDeMZXbhK28naL.png)

我们假设橙点是一个封锁点。因为父亲已经封锁了整个子树，所以儿子就不用（橙点的两个子节点）就不用再作为封锁点浪费农民资源了。

于是，我们得到了一个点 $u$ 应不应该是封锁点的条件：  
$d_{u,root}\le d_{u,p_u}$ 且 $d_{fa_u,root}\le d_{u,p_{fa_u}}$

其中 $p_u$ 代表离 $u$ 最近的叶节点，$d$ 代表两点距离。

### 算法

对于每一个根节点（就是出发点）：  
先暴力 dfs 求出 $p_u$ 和 $fa_u$ 和 $d_{u,root}$ 和 $d_{u,p_u}$，然后判断是不是一个封锁点。如果是的，```ans++```。

## 优化
上述算法是 $O(n^2)$ 的，本质问题是每次要确定一个根。

但是，我们发现其实 $d, p$ 都是和根无关的，在无根情况下可以做出来。那么罪魁祸首就是 $fa$ 数组。所以我们要换一种统计确定封锁点的方式。

我们试图要去掉$fa$的影响。

试想，如果我们不计算 $fa$，$ans$ 会是什么？

下图中蓝色的点是封锁点，绿色三角代表了这棵树（看起来更像一个山……不管了）

![image.png](https://i.loli.net/2020/03/25/eyEYxkX7TGzg29o.png)

那么被淡蓝色覆盖到的部分都会被统计到。那么我们保持这些点都被统计的状态，需要改变这些点的权值，让**这些被覆盖到的点的权值之和=封锁点的数量**。

这个问题看上去很棘手啊。不过我们对其进行分子树考虑。

（我们先不考虑封锁点是根节点的情况）

![image.png](https://i.loli.net/2020/03/25/NW2gZweRkXO5AKu.png)

我们需要子树权值和是 $1$，而且权值只与自己有关。

再具体一点，肯定存在一些操作，使得一些点的权值和为 $0$ (否则没法做)。我们可以想到树上差分，因为两个节点权值 $+1$, LCA 权值 $-2$，构成了天然的抵消操作。

这样，我们只需要子树中的叶节点的权值为 $1$，其他节点的权值为 $1-$儿子数量，也就是 $2-$这个节点的度数。

所以，每个节点的权值是$2-$这个节点的度数（$deg_u$）。所以，对于每个根节点，我们要求 $\sum_{u|d_{root,u}\ge d{p_u,u}} 2-deg_u$

其中里面的东西除了 $d_{root,u} $都和 $root$ 无关，而 $d_{root,u}$ 是 $root,u$ 的路径长度，所以就是统计有多少点对 $(u,v)$ 满足 $\sum_{u|d_{v,u}\ge d{p_u,u}} 2-deg_u$。

其实，上面的东西，就是树形差分的一些基础的公式的东西。

上述可以用点分治实现，复杂度是 $O(nlogn)$

这种不等式点对的点权统计可以用这种点分治模板实现：[我的博客里面的模板题](https://www.luogu.com.cn/blog/forever-captain/dian-fen-zhi)

对于 ```cal``` 函数的实现：

(下面请你忘掉 $d$ 原来的含义，记住他的新的含义)

我们假设$d$为$u$在以 $r$ 为根的深度，于是题目的条件变成了 $d_v\ge -d_u + d_{p_u}$

先在 update 的时候更新数组 $ca_i=d_{p_v}$, $cb_i=-d_u+d_{p_u}$，然后用结构体顺便把 $这个节点的标号和权值给带上$

在 cal 中先排个序，然后从左到右遍历 $ca$，对于每个$ca$，满足条件的 $cb$ 是个前缀，于是动态维护前缀和就行了。

代码中用 $dp_u$ 代表 $d_{p_u}$

**重要的事情** dfz 函数的 find_root 里面和别的一些题解不一样，这些区别影响到了代码的运行速度。具体注意事项参考[这个讨论的第2，3页某金钩大佬的话，顺便%他](https://www.luogu.com.cn/discuss/show/207604?page=2)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=7*1e5;
struct edge{int to,nxt,w;}e[N*2]; int hd[N],tot;
void add(int u,int v,int w){e[++tot]=(edge){v,hd[u],w};hd[u]=tot;}
int n,ans[N];

int d[N],deg[N],p[N],dp[N],sz[N];
void dfs_down(int u,int fa){
	sz[u]=1;
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa){
			d[v]=d[u]+e[i].w,deg[v]++,deg[u]++;
			dfs_down(v,u); sz[u]+=sz[v];
			if(dp[v]+e[i].w<=dp[u]) p[u]=p[v],dp[u]=dp[v]+e[i].w;
		}
	if(deg[u]==1) p[u]=u,dp[u]=0;
}
void dfs_up(int u,int fa){
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa){
			if(dp[u]+e[i].w<=dp[v]) p[v]=p[u],dp[v]=dp[u]+e[i].w;
			dfs_up(v,u);
		}
}

int mx[N]; bool vst[N];
int find_root(int u,int fa,int cnt,int root){
	sz[u]=1,mx[u]=0;
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa&&!vst[v]){
			root=find_root(v,u,cnt,root);
			sz[u]+=sz[v]; mx[u]=max(mx[u],sz[v]);
		}
	mx[u]=max(mx[u],cnt-sz[u]); if(mx[u]<=mx[root]) root=u;
	return root;
}

struct as{int id,dis;}ca[N];
struct bs{int val,dis;}cb[N];
bool cmpa(const as&a,const as&b){return a.dis<b.dis;}
bool cmpb(const bs&a,const bs&b){return a.dis<b.dis;}
int cnt;

void update(int u,int fa){
	ca[++cnt]=(as){u,d[u]},cb[cnt]=(bs){2-deg[u],dp[u]-d[u]};
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa&&!vst[v]){
			d[v]=d[u]+e[i].w; 
			update(v,u);
		}
}

void cal(int u,int base,int sig,int ret=0){
	d[u]=base; cnt=0; update(u,0);
	sort(ca+1,ca+cnt+1,cmpa),sort(cb+1,cb+cnt+1,cmpb);
	int j=0,sum=0;
	for(int i=1;i<=cnt;i++){
		while(j<cnt&&cb[j+1].dis<=ca[i].dis) j++,sum+=cb[j].val;
		ans[ca[i].id]+=sig*sum;
	}
}

int dfz(int u,int wtcl){
	vst[u]=1;
	cal(u,0,1);
	for(int i=hd[u],v,tmp;i;i=e[i].nxt)
		if(!vst[(v=e[i].to)]){
			cal(v,e[i].w,-1);
			int root=find_root(v,u,tmp=(sz[v]>sz[u]?wtcl-sz[u]:sz[v]),0);
			dfz(root,tmp);
		}
} 

int main(){
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++)
		scanf("%d%d",&u,&v),add(u,v,1),add(v,u,1);
	memset(dp,0x3f,sizeof(dp)),memset(mx,0x3f,sizeof(mx));
	dfs_down(1,0); dfs_up(1,0);
	int root=find_root(1,0,n,0); dfz(root,n);
	for(int i=1;i<=n;i++) printf("%d\n",deg[i]==1?1:ans[i]);
	return 0;
}
```

---

## 作者：y2823774827y (赞：45)

~~感觉楼下写的有点不清楚，反正我看不懂，这么说dalao是不是有点不好~~

显然，$g_i$为$i$到最近叶子节点的距离，$d_i$为$i$的度数

假设我们要求的是$ans_u$，如果把$u$作为根，$dep_i≥g_i$则$i$这棵子树贡献为$1$就能拦截$u$，但为了保证唯一性，$dep_i≥g_i \&\& dep_{fa_{i}}<g_{fa_{i}}$

时间复杂度$O(n^2)$

点对贡献，考虑用点分治优化

对于一棵**子树**，$\sum\limits^m d_i=2m-1,\therefore 1=\sum\limits^m (2-d_i)$，根据子树贡献单调性，$ans_u=\sum\limits_{i=1}^n [dis(u,i)≥g_i](2-d_i)$

至此，该题转换成点分治模板题，时间复杂度$O(nlog^2n)$

乱七八糟的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int LL;
const LL maxn=1e5,inf=0x3f3f3f3f;
struct node{
    LL to,nxt;
}dis[maxn<<1];
LL n,root,num,up,N,mi,tim;
LL ans[maxn],head[maxn],d[maxn],g[maxn],tree[maxn],visit[maxn],size[maxn],V[maxn];
inline void Add(LL u,LL v){
    dis[++num]=(node){v,head[u]}, head[u]=num;
    ++d[v];
}
void Dfs1(LL u,LL f){
    if(d[u]==1) g[u]=0;
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(v==f) continue;
        Dfs1(v,u);
        g[u]=min(g[u],g[v]+1);
    }
}
void Dfs2(LL u,LL f){
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(v==f) continue;
        g[v]=min(g[v],g[u]+1);
        Dfs2(v,u);
    }
}

inline LL Lowbit(LL x){ return x&-x; }
inline LL Query(LL x){ LL ret(0); x+=up; for(;x;x-=Lowbit(x)) ret+=tree[x]; return ret; }
inline void Modify(LL x,LL val){ x+=up; for(;x<=100000;x+=Lowbit(x)) tree[x]+=val; }
void Dfs(LL u){
    LL mx(0); visit[u]=true; size[u]=1;
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        Dfs(v); size[u]+=size[v];
        mx=max(mx,size[v]);
    }mx=max(mx,N-size[u]);
    if(mi>mx) mi=mx,root=u;
    visit[u]=false;
}
void Get(LL u,LL dt){
    ans[u]+=Query(dt);
    visit[u]=true;
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        Get(v,dt+1);
    }visit[u]=false;
}
void Up(LL u,LL dt){
    Modify(g[u]-dt,2-d[u]);
    visit[u]=true;
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        Up(v,dt+1);
    }visit[u]=false;
}
void Clear(LL u,LL dt){
    Modify(g[u]-dt,-(2-d[u]));
    visit[u]=true;
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        Clear(v,dt+1);
    }visit[u]=false;
}
void Div(LL u){
    mi=inf, Dfs(u); 
    u=root;
    visit[u]=true;
    LL top(0);
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        V[++top]=v;
        Get(v,1);
        Up(v,1);
    }
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        Clear(v,1);
    }
    Modify(g[u],2-d[u]);
    for(LL i=top;i>=1;--i){
        LL v(V[i]);
        Get(v,1);
        Up(v,1);
    }ans[u]+=Query(0);
    Modify(g[u],-(2-d[u]));
    for(LL i=head[u];i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        Clear(v,1);
    }
    for(LL i=head[u],sum=N;i;i=dis[i].nxt){
        LL v(dis[i].to);
        if(visit[v]) continue;
        N=(size[v]>size[u]?sum-size[u]:size[v]);
        Div(v);
    }
}
int main(){
    cin>>n; up=n;
    for(LL i=1;i<n;++i){
        LL u,v; cin>>u>>v;
        Add(u,v), Add(v,u);
    }
    memset(g,inf,sizeof(g));
    Dfs1(1,0), Dfs2(1,0);
    N=n; Div(1);
    for(LL i=1;i<=n;++i) if(d[i]==1) cout<<1<<endl;else cout<<ans[i]<<endl;
    return 0;
}
```

---

## 作者：sainsist (赞：20)

第一次写博客，希望不会被骂QAQ

从暴力的角度来说，如果我们$O(n)$枚举根节点，有没有办法在$O(n)$的时间内找到答案呢？

此时如果用树形$dp$的想法，发现是可做的，因为可以推得以下的结论：

设$x$为根节点，$d[i]$为$i$节点到$x$的距离(即深度)，$g[i]$为$i$节点到最近的出入口(即叶子节点)的距离，$ans_{x}$为以$x$为根节点时的答案。

如果$d[i] \geq g[i]$，则我们可以确定，以$i$为子树，对于$x$为根时的答案贡献为$1$。如下图：

![](https://img2018.cnblogs.com/blog/1597439/201909/1597439-20190924164920962-209274545.png)


在对于以$i$为根的子树，会对$ans_{x}$产生$1$的贡献，可以理解为一个人从$i$为根的子树的任意叶子节点出发，可以比贝茜更先到达$i$

而这种解法只需要先$dfs$两次得到$g[i]$和$d[i]$，然后一次$dfs$得到答案，复杂度为$O(n^{2})$。

但是这种做法不够理想，我们还想更快的实现。

如果我们对树的性质较为熟悉，我们知道：

$1$.对于树的某棵子树，子树有m个节点，有：$\sum du[i]=2*m-1$

$2$.对于某棵树，树有n个节点，有：$\sum du[i]=2*n-2$

$PS$：$du[i]$为$i$节点的度。

将性质$1$变形为：$1=\sum (2-du[i])$

在本题中，贡献为1的子树有一个性质，即：$d[i] \geq g[i]\& \&d[fa[i]]<g[fa[i]]$。可以理解为他的父亲贡献为子节点个数，即上图中的$i$的父亲。

所以$ans_{x}$=贡献为1的子树数量之和。~~这不是废话吗......~~

所以根据性质$1$，有：$ans_{x}=\sum_{i=1}^{n}[d[i] \geq g[i]](2-du[i])$，稍微解释一下式子的来由：

因为子树的$\sum (2-du[i])=1$，而$1$刚好是一颗子树的贡献，所以满足$d[i] \geq g[i]$的点集，可以组成$ans_{x}$那么多棵贡献为1的子树。如下图：

![](https://img2018.cnblogs.com/blog/1597439/201909/1597439-20190924170131333-93886634.png)

所以满足$g[i] \geq d[i]$的点集为上图圈出来的点，而答案为贡献为1的子树数量：$3$。


------------

此时我们可以用点分治的想法，将：

$ans_{x}=\sum_{i=1}^{n}[d[i] \geq g[i]](2-du[i])$

求解问题变化成求解点对问题：

$ans_{x}=\sum_{i=1}^{n}[dis(x,i) \geq g[i]](2-du[i])$，$dis(x,i)$为$x$到$i$的距离。

所以设$w$为当前子树的重心，$p[i]$为$i$到重心的距离。
则$dis(x,i) \geq g[i]\rightarrow p[x]+p[i] \geq g[i]\rightarrow p[x] \geq g[i]-p[i]$

而在每次求出$p[i]$后，可以使用树状数组维护$g[i]-p[i]$，不过注意$g[i]-p[i]$会小于0，所以维护时向右移$n$的数量。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5e4;
const int inf = 2e9 + 10;
struct node {
	int s, e, w, next;
}edge[maxn];
int head[maxn], len;
void init() {
	memset(head, -1, sizeof(head));
	len = 0;
}
void add(int s, int e) {
	edge[len].s = s;
	edge[len].e = e;
	edge[len].next = head[s];
	head[s] = len++;
}
int root, lens, sum;
int d[maxn], du[maxn], o[maxn], vis[maxn], g[maxn], son[maxn], siz[maxn], ans[maxn];
int rt[maxn], n;
int lowbit(int x) {
	return x & -x;
}
void Add(int x, int val) {
	for (int i = x; i <= 2 * n; i += lowbit(i))
		rt[i] += val;
}
int query(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans += rt[i];
	return ans;
}
void getroot(int x, int fa) {
	siz[x] = 1, son[x] = 0;
	for (int i = head[x]; i != -1; i = edge[i].next) {
		int y = edge[i].e;
		if (y == fa || vis[y])continue;
		getroot(y, x);
		siz[x] += siz[y];
		son[x] = max(son[x], siz[y]);
	}
	son[x] = max(son[x], sum - siz[x]);
	if (son[x] < son[root])root = x;
}
void getd(int x, int fa) {
	o[++lens] = x;
	for (int i = head[x]; i != -1; i = edge[i].next) {
		int y = edge[i].e;
		if (y == fa || vis[y])continue;
		d[y] = d[x] + 1;
		getd(y, x);
	}
}
void cal(int x, int val, int add) {
	lens = 0, d[x] = val;
	getd(x, 0);
	for (int i = 1; i <= lens; i++)
		Add(g[o[i]] - d[o[i]] + n, 2 - du[o[i]]);
	for (int i = 1; i <= lens; i++)
		ans[o[i]] += add * query(d[o[i]] + n);
	for (int i = 1; i <= lens; i++)
		Add(g[o[i]] - d[o[i]] + n, du[o[i]] - 2);
}
void solve(int x) {
	cal(x, 0, 1);
	vis[x] = 1;
	for (int i = head[x]; i != -1; i = edge[i].next) {
		int y = edge[i].e;
		if (vis[y])continue;
		cal(y, 1, -1);
		sum = siz[y];
		root = 0;
		getroot(y, 0);
		solve(root);
	}
}
void dfs1(int x, int fa, int dep) {
	g[x] = inf;
	if (du[x] == 1)g[x] = 0;
	for (int i = head[x]; i != -1; i = edge[i].next) {
		int y = edge[i].e;
		if (y == fa)continue;
		dfs1(y, x, dep + 1);
		g[x] = min(g[x], g[y] + 1);
	}
}
void dfs2(int x, int fa) {
	for (int i = head[x]; i != -1; i = edge[i].next) {
		int y = edge[i].e;
		if (y == fa)continue;
		g[y] = min(g[y], g[x] + 1);
		dfs2(y, x);
	}
}
int main() {
	scanf("%d", &n);
	init();
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
		du[x]++, du[y]++;
	}
	dfs1(1, 0, 1);
	dfs2(1, 0);
	son[0] = n, root = 0, sum = n, getroot(1, 0);
	solve(root);
	for (int i = 1; i <= n; i++) {
		if (du[i] == 1)printf("1\n");
		else printf("%d\n", ans[i]);
	}
}
```


---

## 作者：muzqingt (赞：13)

### 题意分析

我们首先想到，枚举贝茜在 $x$ 点，枚举度数大于 $2$ 的点为 $y$。设 $x$ 的度数为 $a$，$y$ 的度数为 $b$。

我们首先发现每个 $x$ 点都有一个初始的贡献为 $a$ 条通往叶子的路径。

如果点 $y$ 到最近的叶子节点的距离大于到 $x$ 的点的距离（农夫不能在 $y$ 点追上贝茜），则 $y$ 点可以贡献额外的 $b-2$ 条路径。（$y$ 的度数减去进入 $y$、离开 $y$ 的初始贡献消耗的度数）。

我们考虑先预处理出每个 $y$ 点到最近的叶子节点的距离为 $mi_y$。

```
void bfs(int x){
    queue<pair<int,int> >q;
    q.push(make_pair(x,0));
    bool v[70010]={};
    while(!q.empty()){
        int y=q.front().first,z=q.front().second;
        q.pop();
        for(int i=hea[y];i;i=nex[i]){
            int t=to[i];
            if(v[t]!=1){
                v[t]=1;
                if(siz[t]==1){
                    mi[x]=z+1;
                    return;
                }
                q.push(make_pair(t,z+1));
            }
        }
    }
}
```

然后再从 $x$ 点搜索出所有的 $y$ 点计算出合法贡献。注意不能加上自己。

```
void dfs(int x,int nu,int fa){
    if(siz[x]>2){
        if(nu<mi[x]&&nu!=0) ans+=siz[x]-2;
        tot++;
    }
    if(tot>=num) return ; 
    for(int i=hea[x];i;i=nex[i]){
        int t=to[i];
        if(t!=fa){
            dfs(t,nu+1,x);
        }
    }
}
```
我们发现[这样](https://www.luogu.com.cn/record/121207651)会 TLE  $5$ 个点。

我们考虑优化，我们发现枚举的 $x$ 点数量太多。我们可以枚举 $y$ 点反推 $x$ 点。

像这样：
```
void bf(int x){
    queue<pair<int,int> >q;
    q.push(make_pair(x,0));
    bool v[70010]={};
    while(!q.empty()){
        int y=q.front().first,z=q.front().second;
        q.pop();
        if(y!=x)
        an[y]+=siz[x]-2;
        if(z+1<mi[x])
        for(int i=hea[y];i;i=nex[i]){
            int t=to[i];
            if(v[t]!=1){
                v[t]=1;
                q.push(make_pair(t,z+1));
            }
        }
    }
}
```
### 证明一下复杂度：

我们考虑最坏复杂度，此时树为一棵满二叉树。

![img](https://cdn.luogu.com.cn/upload/image_hosting/gj14jh1o.png)

我们设树总共有 $m$ 层。

第 $1$ 层不会遍历。

第 $2$ 层有 $2^{2-1}$ 个数，每个数会遍历 $2^{m-1}-1+1$ 次。

有什么规律呢？

我们把向上的部分转移位置，例如 $2$ 号节点是这样的：

![img](https://cdn.luogu.com.cn/upload/image_hosting/2glgdcq3.png)

如果有更多节点，图就变成了这样。

![img](https://cdn.luogu.com.cn/upload/image_hosting/e6fe1qnk.png)

对于第 $i$ 层遍历了 $2^{i-1}\times(2^{m-i}-1+2^{m-i-1})$ 次。

化简一下并去掉常数就是 $2^{m-1}\times2^{m-2}=3\times{2^{m-2}}$ 次。

由于是一个满二叉树，节点数 $n=2^m-1$，$m\approx{log(n)}$。

所以复杂度就是 $m\times{\tfrac{3}{4}\times{2^m}}\approx{O(n\log{n})}$。

由于常数较小，故比点分治快。


#### code
```
#include<iostream>
#include<queue>
#include<cstdio>
#include<utility>
using namespace std;
int n,siz[70010],mi[70010],num,ans,ma;
int tot,hea[70010],nex[200010],to[200010],an[70010];
void add(int x,int y){
    to[++tot]=y;
    nex[tot]=hea[x];
    hea[x]=tot;
}
void bfs(int x){
    queue<pair<int,int> >q;
    q.push(make_pair(x,0));
    bool v[70010]={};
    while(!q.empty()){
        int y=q.front().first,z=q.front().second;
        q.pop();
        for(int i=hea[y];i;i=nex[i]){
            int t=to[i];
            if(v[t]!=1){
                v[t]=1;
                if(siz[t]==1){
                    mi[x]=z+1;
                    return;
                }
                q.push(make_pair(t,z+1));
            }
        }
    }
}
void bf(int x){
    queue<pair<int,int> >q;
    q.push(make_pair(x,0));
    bool v[70010]={};
    while(!q.empty()){
        int y=q.front().first,z=q.front().second;
        q.pop();
        if(y!=x)
        an[y]+=siz[x]-2;
        if(z+1<mi[x])
        for(int i=hea[y];i;i=nex[i]){
            int t=to[i];
            if(v[t]!=1){
                v[t]=1;
                q.push(make_pair(t,z+1));
            }
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
        siz[x]++;
        siz[y]++;
    }
    for(int i=1;i<=n;i++){
        if(siz[i]>2){
            bfs(i);
            num++;
            ma=max(ma,mi[i]);
        }
    }
    for(int i=1;i<=n;i++){
        if(siz[i]>2){
            bf(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(siz[i]==1){
            printf("1\n");
        }
        else{
            ans=siz[i];
            tot=0;
            printf("%d\n",ans+an[i]);
        }
    }
    return 0;
}
```

---

## 作者：joe19025 (赞：13)

## Solution

### 结论

如果我们把现在Bessie的位置作为根，那么如果个一点到达最近的叶子节点小于它的深度，那么一个农夫就够，反之为所有子树所需农夫之和。

#### 证明

如果现在一点到达最近的叶子节点小于它的深度，那么我在最近叶子节点安排一个农夫，一定比Bessie先到这个点，可以直接堵住整个子树，所以一个人就够。

反之，如果所有农夫到达都比Bessie晚，那么需要每个子树都布控到，因为不知道Bessie会往哪走。所以是所有子树所需农夫之和。

### 性质

根据上述结论，我们尽量找到所有只需要一个农夫且不能再大的子树个数，然后这就是答案了。

我们可以发现，上述子树需要满足的性质如下：$dep[i]>g[i],dep[fa[i]]<g[i] $  （ $g[i]$ 为距离 $i$ 最近的叶子节点距离）。

可以发现，这样的节点在一个满足仅需一个农夫就能控制的连通块里只有一个。

### 构造

对于任意子树，都满足下面这个结论：

$\sum deg[i] = 2m-1$ ( $deg[i]$ 是点的度数 ，$m$ 为点的个数 )

变形可得：$\sum (2-deg[i])=1$ 所以可以得到对于一棵子树满足这样一个条件。

### 点分治

这个条件有什么用呢？我们要求的是满足只需一个农夫的点的连通块，这个连通块必定是一个子树，所以我们每一个连通子树只贡献1。这和上面的构造正好吻合，因为上面的构造也是让一个子树内只贡献一个。

但别忘了我们还有一个判断条件 $dis(u,i)>g[i]$ ，所以答案表达式为 $ans[u]=\sum_{1}^n [dis(u,i)>g[i]](2-deg[i])$ 。

### 复杂度： $O(nlog_{2}n)$

## Code

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define MAXN 70005 
#define int long long
using namespace std;

vector<int>G[MAXN];
int n,sum,root,siz[MAXN],son[MAXN];
bool vis[MAXN];

void getroot(int u,int fa)
{
    siz[u]=1;son[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa || vis[v])continue;
        getroot(v,u);
        siz[u]+=siz[v];
        son[u]=max(son[u],siz[v]);
    }
    son[u]=max(son[u],sum-siz[u]);
    if(son[u]<son[root])root=u;
}

int g[MAXN],dep[MAXN],du[MAXN];
void dfs1(int u,int father,int depth)
{
    dep[u]=depth;
    g[u]=2147483647;
    if(du[u]==1)g[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==father)continue;
        dfs1(v,u,depth+1);
        g[u]=min(g[u],g[v]+1);
    }
}

void dfs2(int u,int father)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==father)continue;
        g[v]=min(g[v],g[u]+1);
        dfs2(v,u);
    }
}

int d[MAXN];

void getdis(int u,int father,int cur)
{
    d[u]=cur;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==father || vis[v])continue;
        getdis(v,u,cur+1);
    }
}

struct node{
    int dg,deg;
    bool operator<(const node a)const
    {
        return dg<a.dg;
    }
}q[MAXN];

struct bond{
    int id,dis;
    bool operator<(const bond a)const
    {
        return dis<a.dis;
    }
}p[MAXN];

int ans[MAXN];

int tot=0;
void addin(int u,int father)
{
    p[++tot]=(bond){u,d[u]};
    q[tot]=(node){g[u]-d[u],2-du[u]};
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==father || vis[v])continue;
        addin(v,u);
    }
}

void calc(int u,int father,int type)
{
    tot=0;
    addin(u,father);
    sort(p+1,p+tot+1);
    sort(q+1,q+tot+1);
    int Sum=0,cursor=0;
    for(int i=1;i<=tot;i++)
    {
        while(cursor<tot && p[i].dis>=q[cursor+1].dg)
        {
            cursor++;
            Sum+=q[cursor].deg;
        }
        ans[p[i].id]+=type*Sum;
    }
}

void solve(int u)
{
    vis[u]=1;
    getdis(u,0,0);
    calc(u,0,1);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(vis[v])continue;
        calc(v,u,-1);
        sum=siz[v];
        root=0;
        getroot(v,u);
        solve(root);
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
        du[x]++;du[y]++;
    }
    dfs1(1,0,1);dfs2(1,0);
    root=0;sum=son[0]=n;getroot(1,0);
    solve(root);
    for(int i=1;i<=n;i++)
        if(du[i]==1)ans[i]=1;
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<endl;
    return 0;
}
```



---

## 作者：dsidsi (赞：10)

来讲一个非常奇怪的乱搞

首先把所有叶子节点丢进队列BFS。得到每个节点距离最近叶子节点的距离。

设奶牛在$a$点，然后考虑一个节点$b$被子树里的叶子保护(即奶牛一旦走到这个节点就会被捕捉)的条件是

$$dep_b-dep_u\le dep_u-dep_a$$

然后就可以写一个$O(n^2)$的贪心了，只要当前点能被子树的节点保护，则$++ans$。因为一棵子树肯定越早被保护越好。

显然是无法通过此题的。

可以发现，对于一条链，在链的顶端被保护和在链的底端保护的答案不变。所以只需要把一条链缩成一条边，然后贪心即可。

复杂度 $O($玄学$)$，实际运行速度目前$Rank1$。~~吊打点分治~~

```
#include <bits/stdc++.h>
using namespace std;

const int maxn = 70005;

int n, ans;

struct edge
{
    int to, next;
    int To, fa, w;
} e[maxn * 2];
int h[maxn], d[maxn], tot;

queue<int> q;
int f[maxn], eu, ev, ew;

inline int gi()
{
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    int sum = 0;
    while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
    return sum;
}

inline void add(int u, int v)
{
    e[++tot] = (edge) {v, h[u]}; h[u] = tot; ++d[v];
    e[++tot] = (edge) {u, h[v]}; h[v] = tot; ++d[u];
}

void bfs()
{
    for (int i = 1; i <= n; ++i)
        if (d[i] == 1) f[i] = 0, q.push(i);
        else f[i] = -1;
    int u;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
            if (f[v] == -1) {
                f[v] = f[u] + 1;
                q.push(v);
            }
    }
}

void dfs1(int u, int fa, int dep)
{
    if (fa && d[u] != 2) return eu = u, ev = fa, ew = dep, void();
    for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
        if (v != fa) {
            dfs1(v, u, dep + 1);
            e[i].To = eu; e[i].fa = ev; e[i].w = ew - dep;
        }
}

void dfs2(int u, int fa, int dep)
{
    if (f[u] <= dep) return ++ans, void();
    for (int i = h[u]; i; i = e[i].next)
        if (e[i].to != fa) dfs2(e[i].To, e[i].fa, dep + e[i].w);
}

int main()
{
    n = gi();
    for (int i = 1; i < n; ++i) add(gi(), gi());

    bfs();

    tot = 0;
    for (int i = 1; i <= n; ++i)
        if (d[i] != 2) dfs1(i, 0, 0);
    
    for (int i = 1; i <= n; ++i) {
        ans = 0; dfs2(i, 0, 0);
        printf("%d\n", ans);
    }
    
    return 0;
}

```

---

## 作者：Dzhao (赞：5)

令 $g_i$ 表示 $i$ 与最近的叶子节点之间的距离。考虑若奶牛在 $u$，无法走到子树 $i$ 内，当且仅当满足 $g_i\le dist(u, i)$。这些满足条件的 $i$ 点可以对 ${ans}_u$ 产生贡献。而由于要使答案最优，所以 $i$ 要尽可能能管到尽可能多的出口。也就是说，当 $i$ 的父亲没法管到 $i$ 的子树，但 $i$ 可以时，会对 ${ans}_u$ 产生 $1$ 的贡献。用式子表示就是： $g_i\le dist(u,i)$ 且 $g_{{fa}_i}>dist(u, {fa}_i)$ 。于是问题就转化为了，对于一个 $u$，求有多少个 $i$ 满足上述条件，求解的时间复杂度为 $\mathcal{O}(n^2)$。

考虑如何优化：

令 ${deg}_i$ 表示 $i$ 的度数，${siz}_i$ 表示以 $i$ 为根的子树的大小，我们发现 $\sum_{v\in sub(u)}{{deg}_v}=2\times {siz}_u-1$，可以推出 $1=\sum_{v\in sub(u)}(2-{deg}_v)$，而一个子树的贡献只有 $1$，所以可以将式子转化为 ${ans}_u=\sum_{i=1}^n [g_i\le dist(u, i)](2-{deg}_i)$，发现这是一个求有多少点对满足要求的问题，可以使用点分治。

考虑如何点分治：

对于每一个 $divide$ 到的根 $rt$，我们预处理出其子树内所有点到他的距离，问题就变成了我们要求有多少个 $i$ 满足 $g_i\le d_u+d_i$，即求有多少个 $i$ 满足 $d_u\ge g_i - d_i$，这个用一个树状数组维护一下就好了，对于两条链相交的情况，我们只要在求根的孩子时把多算的不合法的答案减去就好了，复杂度为 $\mathcal{O}(n\log^2n)$。

$\mathcal{View\ Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int N = 2e5 + 5;
int n, siz[N], rt, S, mx[N], ans[N], d[N], deg[N], cnt, g[N], o[N];
bool vis[N];
vector <int> e[N];
int c[N];
void add(int x, int z) {for(; x <= 2 * n; x += x & -x) c[x] += z;}
int ask(int x) {int res = 0; for(; x; x -= x & -x) res += c[x]; return res;}
void dfs1(int u, int fa) {
	for(auto v : e[u]) if(v != fa) {
		dfs1(v, u);
		g[u] = min(g[u], g[v] + 1);
	}
}
void dfs2(int u, int fa) {
	for(auto v : e[u]) if(v != fa) {
		g[v] = min(g[v], g[u] + 1);
		dfs2(v, u);
	}
}
void getroot(int u, int fa) {
	siz[u] = 1, mx[u] = 0;
	for(auto v : e[u]) if(!vis[v] && v != fa) {
		getroot(v, u);
		siz[u] += siz[v];
		mx[u] = max(mx[u], siz[v]);
	}
	mx[u] = max(mx[u], S - siz[u]);
	if(!rt || mx[u] < mx[rt]) rt = u;
}
void getdis(int u, int fa) {
	o[++cnt] = u;
	for(auto v : e[u]) if(v != fa && !vis[v]) 
		d[v] = d[u] + 1, getdis(v, u);
}
void solve(int u, int len1, int mul) {
	d[u] = len1; cnt = 0; getdis(u, 0);
	for(int i = 1; i <= cnt; i++) 
		add(g[o[i]] - d[o[i]] + n, 2 - deg[o[i]]);
	for(int i = 1; i <= cnt; i++) {
		add(g[o[i]] - d[o[i]] + n, deg[o[i]] - 2);
		ans[o[i]] += ask(d[o[i]] + n) * mul;
		add(g[o[i]] - d[o[i]] + n, 2 - deg[o[i]]);
	}
	for(int i = 1; i <= cnt; i++)
		add(g[o[i]] - d[o[i]] + n, deg[o[i]] - 2);
}
void divide(int u) {
	solve(u, 0, 1); vis[u] = 1; 
	for(auto v : e[u]) if(!vis[v]) {
		solve(v, 1, -1);
		S = siz[v], rt = 0;
		getroot(v, 0);
		divide(rt); 
	}
}

int main() {
	memset(g, 0x3f, sizeof(g));
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		e[x].pb(y), e[y].pb(x);
		deg[x]++, deg[y]++;
	}
	for(int i = 1; i <= n; i++)
		if(deg[i] == 1) g[i] = 0;
	dfs1(1, 0), dfs2(1, 0);
	S = n, rt = 0; getroot(1, 0); divide(rt);
	for(int i = 1; i <= n; i++)
		printf("%d\n", deg[i] == 1 ? 1 : ans[i]);
	return 0;
}
```

---

## 作者：乙津梦 (赞：4)

不知道为什么$lg$题解里清一色只会用
$\sum d=2m-1\rightarrow 1=2m-\sum d$容斥做法

设$\mathit{mnleaf_u}$表示距点$u$最近的叶子节点的距离

这个可以用脚$dfs$随便$O(n/nlogn)$做
对于一个根的情况就是统计

$\sum_{u}[\mathit{mnleaf_u}\le dep_u\ \&\&\ \mathit{mnleaf_{fa[u]}}\geq dep_u]$

对于所有点询问，考虑点分治

那么一个子树中$u$对另一个子树中的$v$的贡献就是
$[\mathit{mnleaf_u}\le dep_u+dep_v\ \&\&\ \mathit{mnleaf_{fa[u]}}\geq dep_u+dep_v]$

移一下项就是$u$区间加，$v$单点求值

于是点分即可

先把整个$dfs$然后枚举求值的子树减去这个子树自己的贡献然后随便算算即可

注意记得把当前分治中心的贡献加进去

就是往哪个子树求值就把中心的父亲设为哪个


### Code

```cpp

#include<bits/stdc++.h>
using namespace std;
#define cs const
#define pb push_back
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define bg begin
cs int RLEN=1<<20|1;
inline char gc(){
	static char ibuf[RLEN],*ib,*ob;
	(ib==ob)&&(ob=(ib=ibuf)+fread(ibuf,1,RLEN,stdin));
	return (ib==ob)?EOF:*ib++;
}
inline int read(){
	char ch=gc();
	int res=0;bool f=1;
	while(!isdigit(ch))f^=ch=='-',ch=gc();
	while(isdigit(ch))res=(res*10)+(ch^48),ch=gc();
	return f?res:-res;
}
template<typename tp>inline void chemx(tp &a,tp b){a=max(a,b);}
template<typename tp>inline void chemn(tp &a,tp b){a=min(a,b);}
cs int N=70005;
int n,mnleaf[N],isleaf[N];
vector<int> e[N];
void dfs(int u,int fa){mnleaf[u]=1e9;int fg=0;
	for(int &v:e[u])if(v!=fa){
		fg=1;dfs(v,u);
		chemn(mnleaf[u],mnleaf[v]+1);
	}
	if(!fg||(u==1&&e[u].size()==1))mnleaf[u]=0,isleaf[u]=1;
}
void dfs1(int u,int tp,int fa){
	chemn(mnleaf[u],tp);
	multiset<int>st;st.insert(mnleaf[u]);
	for(int &v:e[u])if(v!=fa){
		st.insert(mnleaf[v]+1);
	}
	for(int &v:e[u])if(v!=fa){
		st.erase(st.find(mnleaf[v]+1));
		int vl=mnleaf[v]+1;
		dfs1(v,min(tp,*st.bg())+1,u);
		st.insert(vl);
	}
}
namespace bit{
	int tr[2*N],stk[N*6],top;
	#define lb(x) (x&(-x))
	void write(){
		for(int i=1;i<=n+n;i++)cout<<tr[i]<<" ";puts("");
	}
	void upd(int p,int k){stk[++top]=p;
		for(;p<=n+n;p+=lb(p))tr[p]+=k;
	}
	void delet(int p){
		for(;p<=n+n;p+=lb(p))tr[p]=0;
	}
	void clear(){
		while(top)delet(stk[top--]);
	}
	void update(int l,int r,int k){
		if(l>r)return;l+=n,r+=n;
		upd(l,k),upd(r+1,-k);
	}
	int query(int p,int res=0){p+=n;
		for(;p>0;p-=lb(p))res+=tr[p];return res;
	}
	#undef lb
};
int maxn,mxsiz,rt;
int siz[N],vis[N],fa[N],dep[N],ans[N];
void getrt(int u,int fa){
	siz[u]=1;int son=0;
	for(int v:e[u])if(!vis[v]&&v!=fa){
		getrt(v,u),siz[u]+=siz[v];
		chemx(son,siz[v]);
	}chemx(son,maxn-siz[u]);
	if(son<mxsiz)mxsiz=son,rt=u;
}
vector<int>nd[N];
void dfs2(int u,int root){
	nd[root].pb(u),bit::update(mnleaf[u]-dep[u],mnleaf[fa[u]]-dep[u],1);
	for(int v:e[u])if(!vis[v]&&v!=fa[u])fa[v]=u,dep[v]=dep[u]+1,dfs2(v,root);
}
void delet(int u){
	for(int &v:nd[u])
	bit::update(mnleaf[v]-dep[v],mnleaf[fa[v]]-dep[v],-1);
}
void insert(int u){
	for(int &v:nd[u])
	bit::update(mnleaf[v]-dep[v],mnleaf[fa[v]]-dep[v],1);	
	nd[u].resize(0);
}
void getans(int u){
	ans[u]+=bit::query(dep[u]);
	for(int v:e[u])if(!vis[v]&&v!=fa[u])getans(v);
}
void solve(int u){
	vis[u]=1;
	for(cs int &v:e[u])if(!vis[v]){
		fa[v]=u,dep[v]=1,dfs2(v,v);
	}
	ans[u]+=bit::query(0);
	for(cs int &v:e[u])if(!vis[v]){
		delet(v);
		bit::update(mnleaf[u],mnleaf[v],1);
		getans(v);
		bit::update(mnleaf[u],mnleaf[v],-1);
		insert(v);
	}
	bit::clear();
	for(cs int &v:e[u])if(!vis[v]){
		maxn=siz[v],mxsiz=1e9,getrt(v,u);
		solve(rt);
	}
}
int main(){
	#ifdef Stargazer
	freopen("lx.in","r",stdin);
	#endif
	n=read();maxn=n;mxsiz=1e9;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}dfs(1,0);
	dfs1(1,1e9,0);
	getrt(1,0);
	solve(rt);
	for(int i=1;i<=n;i++)if(!isleaf[i])cout<<ans[i]<<'\n';else cout<<1<<'\n';
	return 0;
}
```



---

## 作者：foreverlasting (赞：4)

[题面](https://www.luogu.org/problemnew/show/P4183)

点分治。

首先有一个明显的结论：叶子节点到点$x$的距离如果小于根到点$x$的距离，那么点$x$的子树只用一个代价就可以保护了。所以首先维护出每个点$x$到叶子结点的最近距离$mndis[x]$。考虑如何换根更新答案。我们考虑总答案减去不合法的方法。总答案可以通过这条公式$\sum _ {v}Dg[v]=2(k-1)+1$——>$\sum _ {v}(2-Dg[v])=1$推出来是$2$。不合法的答案我们通过重心来统计。设点分治重心为$x$，考虑所有经过$x$的边是否合法。设$dis[u]$为$u$到$x$的距离，那么两个在子树中的点$u$和$v$不合法当且仅当$dis[u]+dis[v]<mndis[u]$——>$dis[v]<mndis[u]-dis[u]$，这可以用类似天天爱跑步那道题的思路，开个桶统计一下，维护一个后缀和就好。

code:
```
#pragma GCC optimize("Ofast,no-stack-protector")
//2018.9.27 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e5+10;
namespace MAIN{
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N<<1];
    int head[N],cnt;
    int du[N];
    inline void addedge(const res &u,const res &v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
        edge[++cnt]=E(head[v],u),head[v]=cnt;
        du[u]++,du[v]++;
    }
    int mndis[N];
    void dfs1(const res &x,const res &fax){
        mndis[x]=inf;
        if(du[x]==1)mndis[x]=0;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax)continue;
            dfs1(tox,x);
            mndis[x]=_min(mndis[tox]+1,mndis[x]);
        }
    }
    void dfs2(const res &x,const res &fax){
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax)continue;
            mndis[tox]=_min(mndis[tox],mndis[x]+1);
            dfs2(tox,x);
        }
    }
    int siz[N],w[N],rt,sum,vis[N];
    void getroot(const res &x,const res &fax){
        siz[x]=1,w[x]=0;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax||vis[tox])continue;
            getroot(tox,x);
            siz[x]+=siz[tox],w[x]=_max(w[x],siz[tox]);
        }
        w[x]=_max(w[x],sum-siz[x]);
        if(w[x]<w[rt])rt=x;
    }
    int n;
    int tot[N][2],len[2],ans[N],dis[N];
    void getdis(const res &x,const res &fax,const res &d){
        dis[x]=d;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax||vis[tox])continue;
            getdis(tox,x,d+1);
        }
    }
    void in_ex(const res &x,const res &fax,const res &S){
        res p=mndis[x]-dis[x];
        if(p>0)tot[p][S]+=2-du[x],len[S]=_max(len[S],p);
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax||vis[tox])continue;
            in_ex(tox,x,S);
        }
    }
    void calc(const res &x,const res &fax){
        ans[x]+=tot[dis[x]+1][0]-tot[dis[x]+1][1];
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax||vis[tox])continue;
            calc(tox,x);
        }
    }
    void solve(const res &x){
        vis[x]=1,getdis(x,0,0);
        len[0]=0,in_ex(x,0,0);
        for(res i=len[0]-1;i>=1;i--)tot[i][0]+=tot[i+1][0];
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(vis[tox])continue;
            len[1]=0,in_ex(tox,x,1);
            for(res j=len[1]-1;j>=1;j--)tot[j][1]+=tot[j+1][1];
            calc(tox,x);
            for(res j=len[1];j>=1;j--)tot[j][1]=0;
        }
        ans[x]+=tot[1][0];
        for(res i=len[0];i>=0;i--)tot[i][0]=0;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(vis[tox])continue;
            rt=0,sum=siz[tox],getroot(tox,0),solve(rt);
        }
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read();
        for(res i=1;i<n;i++){
            res u=read(),v=read();
            addedge(u,v);
        }
        dfs1(1,0),dfs2(1,0);
        rt=0,sum=w[0]=n,getroot(1,0);
        solve(rt);
        for(res i=1;i<=n;i++)
            if(du[i]==1)puts("1");
            else printf("%d\n",2-ans[i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：orz_z (赞：3)

题面自行看吧。。。

#### std

首先把当前奶牛的位置作为根。

令 $g_u$ 表示 $u$ 与最近的叶子的距离。

那么若奶牛在 $u$，无法走到 $i$ 的子树内，当且仅当 $\operatorname{dis}(u, i) \ge g_i$。

由于要使答案最优，即让 $i$ 管辖的节点尽可能多，若 $i$ 满足上面条件，$fa_i$ 也满足上面条件，那么优先选 $fa_i$。

那么上面条件可转化为：$\operatorname{dis}(u,i) \ge g_i$ 且 $\operatorname{dis}(u, fa_i) \le g_{fa_i}$。

于是，问题就转化为：对于一个 $u$，求有多少个 $i$ 满足上述条件，求解的时间复杂度为 $\mathcal{O}(n^2)$。

考虑优化。

令 $deg_i$ 表示 $i$ 的度数，$siz_i$ 表示 $i$ 的子树大小。

我们发现 $\sum\limits_{v\in sub(u)}deg_v=2 \times siz_u - 1$，即 $1 = \sum\limits_{v \in sub(u)}(2 - deg_v)$。

而一个子树的贡献只有 $1$，所以我们可以将式子转化为：$ans_u=\sum\limits_{i=1}^{n} [\operatorname{dis}(u,i)\ge g_i](2-deg_i)$，此时就已经自动选满足的且深度最小的了。

考虑再次优化：

对于这种无根树，我们可以想到用点分治，以当前分治中心为根，维护有多少个 $i$ 满足 $g_i \leq dep_u+dep_i$，即 $dep_u \geq g_i-dep_i$，树状数组维护一下即可，注意链重合的情况。

时间复杂度为 $\mathcal O(n \log^2 n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int _ = 2e5 + 10;

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + (c - '0'), c = getchar();
	return x * f;
}

int n;

int tot, head[_], to[_ << 1], nxt[_ << 1];

bool vis[_];

int g[_], siz[_], mx[_], deg[_], d[_], p[_], ans[_], rt, sum;

int cnt, o[_];

int c[_];

void update(int x, int val)
{
	for(; x <= 2 * n; x += x & -x)
		c[x] += val;
}

int query(int x)
{
	int res = 0;
	for(; x; x -= x & -x)
		res += c[x];
	return res;
}

void add(int u, int v)
{
	to[++tot] = v;
	nxt[tot] = head[u];
	head[u] = tot;
}

void dfs1(int u, int fa)
{
	siz[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa)
			continue;
		dfs1(v, u);
		g[u] = min(g[u], g[v] + 1);
	}
}

void dfs2(int u, int fa)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa)
			continue;
		g[v] = min(g[v], g[u] + 1);
		dfs2(v, u);
	}
}

void get_rt(int u, int fa)
{
	siz[u] = 1, mx[u] = 0;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(vis[v] || v == fa)
			continue;
		get_rt(v, u);
		siz[u] += siz[v];
		mx[u] = max(mx[u], siz[v]);
	}
	mx[u] = max(mx[u], sum - siz[u]);
	if(mx[u] < mx[rt])
		rt = u;
}


void get_dis(int u, int fa)
{
	o[++cnt] = u;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || vis[v])
			continue;
		d[v] = d[u] + 1;
		get_dis(v, u);
	}
}

void calc(int u, int len, int mul)
{
	d[u] = len, cnt = 0;
	get_dis(u, 0);
	for(int i = 1; i <= cnt; ++i)
		update(g[o[i]] - d[o[i]] + n, 2 - deg[o[i]]);
	for(int i = 1; i <= cnt; ++i)
	{
		update(g[o[i]] - d[o[i]] + n, -(2 - deg[o[i]]));
		ans[o[i]] += query(d[o[i]] + n) * mul;
		update(g[o[i]] - d[o[i]] + n, 2 - deg[o[i]]);
	}
	for(int i = 1; i <= cnt; ++i)
		update(g[o[i]] - d[o[i]] + n, -(2 - deg[o[i]]));
}

void dfz(int u)
{
	vis[u] = 1;
	calc(u, 0, 1);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(vis[v])
			continue;
		calc(v, 1, -1);
		rt = 0, sum = siz[v];
		get_rt(v, u), dfz(rt);
	}
}

signed main()
{
	memset(g, 0x3f, sizeof g);
	n = read();
	int a, b;
	for(int i = 1; i < n; ++i)
	{
		a = read(), b = read();
		add(a, b), add(b, a);
		deg[a]++, deg[b]++;
	}
	for(int i = 1; i <= n; ++i)
		if(deg[i] == 1) g[i] = 0;
	dfs1(1, 0), dfs2(1, 0);
	rt = 0, sum = n, mx[0] = 2e9;
	get_rt(1, 0), dfz(rt);
	for(int i = 1; i <= n; ++i)
		printf("%d\n", deg[i] == 1 ? 1 : ans[i]);
	return 0;
}
```



---

## 作者：DrBit (赞：2)

[题面](https://www.luogu.com.cn/problem/P4183)

首先可以发现如果一个农夫想抓到 Bessie 那么只能去“相遇”而不能去“追及”，一个农夫应该尽可能往上走以“占领”更大的子树及更多的叶子节点。

假设当前 Bessie 所在的节点为 $u$，同时我们将 $u$ 看做树的根节点。

设 $p_i$ 表示 $i$ 号点到最近的叶子节点的距离，$dep_i$表示 $i$ 号点的深度，$fa_i$ 表示 $i$ 号点的父亲节点。

那么很显然，满足 $dep_x \ge p_x$ 且 $dep_{fa_x} \le p_{fa_x}$ 的点都需要且仅需要在子树中设置一个农夫。（$fa_x$ 的那个条件是为了去重）

有多少个这样的点就是答案。

复杂度 $O(N^2)$。

看见不等关系很容易想到点分治，但如果 $u$ 不是根的话 $dep_i$ 和 $fa_i$ 的维护都极为困难。

发现引入 $fa_i$ 是为了去重，那有没有方法运用容斥的方法去重？

设 $dis_{a,b}$ 为从 $a$ 到 $b$ 的路径长度，那么一个点被“封锁”的条件为 $dis{x,i} \ge p_i$，如果一个点 $i$ 满足这个条件，那么它子树中的所有点也都满足这个条件。（此处子树的概念是以 $u$ 为根）。

而对于一棵有 $M$ 个点的子树，设 $deg_i$ 表示 $i$ 号点的度数，那么有 $\sum deg_i =2M-1 \to \sum 2-deg_i =1 $

如果我们把每个点的权值都设为 $2-deg_i$，那么这样就解决了去重的问题。

对于一个点 $u$，我们要求所有满足 $dis_{u,i} \ge p_i$ 的权值和。

如果当前的根是 $x$ ，那么限制条件变为 $dep_u+dep_i \ge p_i \to dep_u \ge p_i - dep_i$。

点分治即可。

复杂度 $O(N \log N)$。

tips:求解 $p_i$ 时要注意距离 $i$ 号点最近的叶子节点并不一定在以 $1$ 为根意义下的子树中，所以初始求 $p_i$ 时要同时计算来自父亲和来自儿子的贡献。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 1e5 + 50;
const int INF = 0x3f3f3f3f;
int p[MAXN], dep[MAXN], ans[MAXN], deg[MAXN], siz[MAXN], mx[MAXN], tag[MAXN];
struct edge
{
    int nxt, to;
} e[MAXN * 2];
int head[MAXN], edgetot;
int N, tot, rt, cnt1, cnt2;
struct nodea
{
    int id, key;
    bool operator<(const nodea &tmp) const
    {
        return key < tmp.key;
    }
    nodea(){}
    nodea(int a, int b)
    {
        id = a;
        key = b;
    }
} ta[MAXN];
struct nodeb
{
    int key, val;
    bool operator<(const nodeb &tmp) const
    {
        return key < tmp.key;
    }
    nodeb(){}
    nodeb(int a, int b)
    {
        key = a;
        val = b;
    }
} tb[MAXN];
void add(int x, int y)
{
    e[++edgetot].to = y;
    e[edgetot].nxt = head[x];
    head[x] = edgetot;
}
void getp1(int x, int f) 
{
    if (deg[x] == 1)
        p[x] = 0;
    else
        p[x] = INF;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == f)
            continue;
        getp1(v, x);
        p[x] = min(p[x], p[v] + 1);
    }
}
void getp2(int x, int f)
{
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == f)
            continue;
        p[v] = min(p[v], p[x] + 1);
        getp2(v, x);
    }
}
void findrt(int x, int f)
{
    siz[x] = 1;
    dep[x] = dep[f] + 1;
    mx[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == f || tag[v])
            continue;
        findrt(v, x);
        siz[x] += siz[v];
        mx[x] = max(mx[x], siz[v]);
    }
    mx[x] = max(mx[x], tot - siz[x]);
    if (mx[x] < mx[rt] || !rt)
        rt = x;
}
void dfs(int x, int f)
{
    dep[x] = dep[f] + 1;
    ta[++cnt1] = nodea(x, dep[x]);
    tb[++cnt2] = nodeb(p[x] - dep[x], 2 - deg[x]);
    siz[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == f || tag[v])
            continue;
        dfs(v, x);
        siz[x] += siz[v];
    }
}
void calc(int x, int base, int typ)
{
    cnt1 = cnt2 = 0;
    dep[0] += base;
    dfs(x, 0);
    dep[0] -= base;
    sort(ta + 1, ta + cnt1 + 1);
    sort(tb + 1, tb + cnt2 + 1);
    int sum = 0;
    int j = 0;
    for (int i = 1; i <= cnt1; ++i)
    {
        while (tb[j + 1].key <= ta[i].key && j < cnt1)
        {
            j++;
            sum += tb[j].val;
        }
        ans[ta[i].id] += typ * sum;
    }
}
void solve(int x)
{
    calc(x, 0, 1);
    tag[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (tag[v])
            continue;
        calc(v, 1, -1);
        tot = siz[v];
        rt = 0;
        findrt(v, 0);
        // cout << x << ":" << v << " " << rt << endl;
        solve(rt);
    }
}
int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N - 1; ++i)
    {
        int u, v;
        scanf("%d%d",&u,&v);
        add(u, v);
        add(v, u);
        deg[u]++;
        deg[v]++;
    }
    dep[0] = -1;
    tot = N;
    getp1(1, 0);
    getp2(1, 0);
    findrt(1, 0);
    solve(rt);
    for (int i = 1; i <= N; ++i)
        printf("%d\n", deg[i] == 1 ? 1 : ans[i]);
    return 0;
}
```


---

## 作者：C3H5ClO (赞：2)

思路其他几位大佬都说了，我讲一讲点分治的具体实现和几个细节，方便大家调试。

设$h[x]$为点$x$到最近叶节点距离，首先有$ans[x]=\sum\limits_{i=1}^n[dis(x,i)\ge h[i]](2-deg[i])$

设当前分治中心为$rt$，$dep[x]$为点$x$到$rt$距离，则$dis(x,i)\ge h[i]\Leftrightarrow dep[x]+dep[i]\ge h[i]\Leftrightarrow h[i]-dep[i]\le dep[x]$

因此加入贡献时将每个$x$的$2-deg[x]$加入到$h[i]-dep[i]$位置，用树状数组统计$\le dep[x]$的和

这里给出较为清晰的两种实现方法。

实现方法1
>1.找根

>2.将每个子树节点的贡献加入树状数组

>3.加分治中心的答案

>4.将分治中心贡献加入树状数组

>5.对于分治中心的每棵子树，将其所有节点的贡献从树状数组删除，在给这棵子树的节点加答案，然后将其所有节点的贡献加入树状数组

>6.将当前分治块所有节点贡献从树状数组删除

>7.分治

实现方法2
>1.找根

>2.将当前分治块所有节点贡献加入树状数组

>3.给当前分治块所有节点加答案

>4.将当前分治块所有节点贡献从树状数组删除

>5.对于当前分治中心的每棵子树，将其所有节点贡献加入树状数组，再给这些节点减去多余的答案（因为在第2步中加了同一子树的节点构成路径的情况），再将其贡献从树状数组删除

>6.分治

几个细节：
>1.虽然树状数组在中间过程可能爆int，但由于最终答案$\in[1,n]$，即使中途从正的加爆成负的，也一定会再把它减成正的，因此long long并不需要（当然开了有备无患！）

>2.树状数组要处理下标为负数，要么全部加上$n$，要么像下文我的代码中那么处理

>3.树形DP求$h[x]$时注意一开始随便定的树根就是叶子的情况，这里要加个特判

>4.叶子节点答案必为1

希望这些能帮助大家调试！我就因为这些奇怪的东西耗了两个多小时。。

接下来上代码，我这里用的是我讲的实现方法1。
```
#include<cstdio>
#include<algorithm>
using namespace std;
#define ri register int
const int INF=987654321;
int n,x,y,rt,tsiz,hei[100005],siz[100005],f[100005],c[100005],ans[100005];
int head[100005],to[200005],nxt[200005],ecnt,deg[200005];
bool vis[100005];
inline void add(int x,int y)
{
	ecnt++;
	to[ecnt]=y;
	nxt[ecnt]=head[x];
	head[x]=ecnt;
	deg[y]++;
}
inline void ddxg(int x,int y)
{
	if(x<=0)c[0]+=y;
	else for(ri i=x;i<n;i+=i&-i)c[i]+=y;
}
inline int qjcx(int x)
{
	int res=c[0];
	for(ri i=x;i;i-=i&-i)res+=c[i];
	return res;
}
void gethei1(int x,int fa)
{
	if(deg[x]==1&&x>1)return;
	if(deg[x]>1)hei[x]=INF;
	for(int i=head[x];i;i=nxt[i])
		if(to[i]!=fa)
		{
			gethei1(to[i],x);
			hei[x]=min(hei[x],hei[to[i]]+1);
		}
}
void gethei2(int x,int fa)
{
	for(int i=head[x];i;i=nxt[i])
		if(to[i]!=fa&&deg[to[i]]!=1)
		{
			hei[to[i]]=min(hei[to[i]],hei[x]+1);
			gethei2(to[i],x);
		}
}
void getrt(int x,int fa)
{
	siz[x]=1; f[x]=0;
	for(int i=head[x];i;i=nxt[i])
		if(!vis[to[i]]&&to[i]!=fa)
		{
			getrt(to[i],x);
			siz[x]+=siz[to[i]];
			f[x]=max(f[x],siz[to[i]]);
		}
	f[x]=max(f[x],tsiz-siz[x]);
	if(f[x]<f[rt])rt=x;
}
void addcon(int x,int fa,int dep)
{
	ddxg(hei[x]-dep,2-deg[x]);
	for(int i=head[x];i;i=nxt[i])
		if(to[i]!=fa&&!vis[to[i]])addcon(to[i],x,dep+1);
}
void addans(int x,int fa,int dep)
{
	ans[x]+=qjcx(dep);
	for(int i=head[x];i;i=nxt[i])
		if(to[i]!=fa&&!vis[to[i]])addans(to[i],x,dep+1);
}
void delcon(int x,int fa,int dep)
{
	ddxg(hei[x]-dep,deg[x]-2);
	for(int i=head[x];i;i=nxt[i])
		if(to[i]!=fa&&!vis[to[i]])delcon(to[i],x,dep+1);
}
void dfz(int x)
{
	rt=0;
	getrt(x,x);
	vis[rt]=1;
	for(int i=head[rt];i;i=nxt[i])
		if(!vis[to[i]])addcon(to[i],to[i],1);
	ans[rt]+=qjcx(0);
	ddxg(hei[rt],2-deg[rt]);
	for(int i=head[rt];i;i=nxt[i])
		if(!vis[to[i]])
		{
			delcon(to[i],to[i],1);
			addans(to[i],to[i],1);
			addcon(to[i],to[i],1);
		}
	delcon(rt,rt,0);
	for(int i=head[rt];i;i=nxt[i])
		if(!vis[to[i]])
		{
			tsiz=siz[to[i]]>siz[rt]?siz[x]-siz[rt]:siz[to[i]];
			dfz(to[i]);
		}
}
int main()
{
	scanf("%d",&n);
	for(ri i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	gethei1(1,1);
	gethei2(1,1);
	f[0]=INF;
	tsiz=n;
	dfz(1);
	for(ri i=1;i<=n;i++)
	{
		if(deg[i]==1)printf("1\n");
		else printf("%lld\n",ans[i]);
	}
}

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目分析】**

先考虑 $\mathcal{O}(n^2)$ 怎么做。

设 $f_u$ 表示距离点 $u$ 最近的叶子节点的距离，$dis_u$ 为当前的根节点到点 $u$ 的距离。显而易见的，如果农夫要从叶子节点出发抓到 Bessie，那这个农夫一定要比 Bessie 先到达某个子树的根节点，否则农夫永远追不上 Bessie。我们称这样的子树根节点为关键点。显然，关键点子树内一定可以只放一个农夫。

贪心地考虑，如果一个关键点地父亲也是关键点，那么这个子树没有控制的必要，我们可以少放一些农夫。即，我们要选择的关键点一定满足 $f_u \le d_u$ 且 $f_v > d_v$，其中 $v$ 是 $u$ 的父亲。于是我们每次钦定一个点为根， dfs 扫几遍即可。时间复杂度 $\mathcal O(n^2)$。

---
我们发现 $f_u$ 是节点的本质属性，与根节点无关。据此考虑优化。设 $d_u$ 为节点 $u$ 的度数，显然一个子树内 $\sum d_u = 2m-1$，其中 $m$ 是子树大小（不是 $2m-2$ 因为子树的根还会连接原树）。我们将上面的式子移项，得到 $\sum(2 - d_u)= 1$，这是一个关键结论。

现在我们求满足条件的点的数量，就转化为了求这些子树内 $2 - d$ 的和。记点 $u$ 的点权为 $2 - d_u$。我们用点分治来求答案，在树状数组里以 $f_i - dis_i$ 为下标，$2-d_i$ 为值，这样可以在遍历时快速查找小于等于 $dis_i$ 的点权和。记得减去算重的答案，使用容斥的思想。时间复杂度 $\mathcal {O}(n \log^2 n)$，一只 $\log$ 是点分治，另一只是树状数组。

---

代码实现上，`dfs1` 和 `dfs2` 是点分治所用的统计子树大小和树的重心，`dfs3` 遍历子树求距离，`dfs4` 是点分治的过程。`dpfs` 函数用来求 $f$ 数组。

记得插入树状数组时，给下标加上 $n$ 防止出现负数。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 7e4+5;
struct edge{int to,nxt;}e[maxn*2];vector <int> acc;
int t[maxn*4],n,cnt,head[maxn],u,v,d[maxn],frt,son[maxn],f[maxn],vis[maxn],dis[maxn],siz[maxn],ms[maxn],mx,rt,ans[maxn];
void update(int x,int p){for(;x <= 2*n;x += x & -x) t[x] += p;}
int sum(int x){int res = 0;for(;x;x -= x & -x) res += t[x];return res;}
void add(int u,int v){e[++cnt].to = v,e[cnt].nxt = head[u],head[u] = cnt;}
void dfs1(int u,int fa){
    ms[u] = 0,siz[u] = 1;
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;
        dfs1(v,u),siz[u] += siz[v];if(siz[v] > ms[u]) ms[u] = siz[v];
    }
}
void dfs2(int rn,int u,int fa){
    ms[u] = max(ms[u],siz[rn] - siz[u]);
    if(ms[u] < mx) mx = ms[u],rt = u;
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;
        dfs2(rn,v,u);
    }
}
void dfs3(int u,int fa){
    acc.push_back(u);
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;
        dis[v] = dis[u] + 1,dfs3(v,u);
    }
}
void calc(int u,int _dis,int k){
    acc.clear(),dis[u] = _dis,dfs3(u,0);
    for(int i : acc) update(-dis[i] + f[i] + n,d[i]);
    for(int i : acc) update(-dis[i] + f[i] + n,-d[i]),ans[i] += sum(dis[i] + n) * k,update(-dis[i] + f[i] + n,d[i]);
    for(int i : acc) update(-dis[i] + f[i] + n,-d[i]);
}
void dfs4(int u){
    mx = 1e9;dfs1(u,0),dfs2(u,u,0),calc(rt,0,1),vis[rt] = 1;
    for(int i = head[rt];i;i = e[i].nxt){
        int v = e[i].to;if(vis[v]) continue;
        calc(v,1,-1);dfs4(v);
    }
}
void dpfs1(int u,int fa){
    if(d[u] == 1) return f[u] = 0,void();
    f[u] = 1e9;
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;dpfs1(v,u);
        f[u] = min(f[u],f[v] + 1);
    }
}
void dpfs2(int u,int fa){
    if(d[u] == 1) return ;
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;
        f[v] = min(f[v],f[u] + 1);dpfs2(v,u);
    }
}
int main(){
    cin >> n;
    for(int i = 1;i < n;i ++) cin >> u >> v,add(u,v),add(v,u),d[u] ++,d[v] ++;
    for(int i = 1;i <= n;i ++) d[i] = 2 - d[i];
    for(int i = 1;i <= n;i ++) if(d[i] != 1){frt = i;break;} //找到一个非叶子节点出发
    dpfs1(frt,0),dpfs2(frt,0),dfs4(frt);
    for(int i = 1;i <= n;i ++) cout << ans[i] << "\n";
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：1)

带有小 trick 的点分治。

建议先做完 [弱化版](https://www.luogu.com.cn/problem/P4186) 再看。

假如奶牛在 $u$，那么所需的最少农夫数为 $\sum\limits_{v\in son(u)}[dis(u,v)\ge g_v][dis(u,fa_v)<g_{fa_v}]$。

其中 $dis(u,v)$ 为 $u,v$ 在树上的距离，$g_u$ 为 $u$ 到离它最近的出入口的距离（BFS 预处理），$fa_u$ 为 $u$ 的父亲。

复杂度 $O(n^2)$。

由于 $dis(u,fa_v)<g_{fa_v}$ 限制的存在，不好优化。

但通过人类智慧我们发现，对于 $u$ 这棵子树，$\sum\limits_{v\in son(u)}in_v=2n-1$。其中 $in_u$ 为 $u$ 的度数，$n$ 为子树大小，$v$ 可以为 $u$。

将式子变换一下得：$1=\sum\limits_{v\in son(u)}(2-in_v)$。

这样原式就可以去掉后面的限制，变为 $\sum\limits_{v\in son(u)}[dis(u,v)\le g_v](2-in_v)$。

接下来点分治的操作和 [这道题](https://www.luogu.com.cn/problem/P4178) 很像，可以看一眼。

具体来说，对于分治重心 $rt$ 中的两个点 $u,v$，当前仅当 $g_u\le d_u+d_v$ 时，$v$ 会对 $u$ 产生贡献。其中 $d_u$ 为 $dis(u,rt)$。这其实就是个点对问题。

所以我们可以以 $g_u-d_u$ 为下标建一棵树状数组，每次访问前缀和即可。由于下标可能为负，所以需要整体平移一下。

复杂度 $O(n\log^2 n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=7e4+5;
int n,g[N],vis[N],f[N],siz[N],d[N],c[N*2],in[N],tot,ans[N],t[N],cnt,rt;
queue<int>q;
vector<int>adj[N];
int lbt(int x){return x&(-x);}
void update(int i,int k){for(;i<=2*n;i+=lbt(i))c[i]+=k;}
int getsum(int i){int res=0;for(;i;i-=lbt(i))res+=c[i];return res;}
void dfs(int u,int lst){
  siz[u]=1;f[u]=0;
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];if(v==lst||vis[v])continue;
    dfs(v,u);siz[u]+=siz[v];f[u]=max(f[u],siz[v]);
  }
  f[u]=max(f[u],tot-siz[u]);
  if(f[u]<f[rt])rt=u;
}
void getdis(int u,int lst){
  t[++cnt]=u;
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];if(v==lst||vis[v])continue;
    d[v]=d[u]+1;getdis(v,u);
  }
}
void getans(int u,int len,int op){
  d[u]=len;cnt=0;getdis(u,0);
  for(int i=1;i<=cnt;++i)update(g[t[i]]-d[t[i]]+n,2-in[t[i]]);
  for(int i=1;i<=cnt;++i){
    update(g[t[i]]-d[t[i]]+n,in[t[i]]-2);
    ans[t[i]]+=op*getsum(d[t[i]]+n);
    update(g[t[i]]-d[t[i]]+n,2-in[t[i]]);
  }
  for(int i=1;i<=cnt;++i)update(g[t[i]]-d[t[i]]+n,in[t[i]]-2);
}
void solve(int u){
  getans(u,0,1);vis[u]=1;
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];if(vis[v])continue;
    getans(v,1,-1);
    rt=0;tot=siz[v];dfs(v,u);solve(rt);
  }
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;
  for(int i=1;i<n;++i){
    int u,v;cin>>u>>v;
    adj[u].push_back(v);adj[v].push_back(u);++in[u];++in[v];
  }
  for(int i=1;i<=n;++i)if(in[i]==1)q.push(i),vis[i]=1;
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int i=0;i<adj[u].size();++i){
      int v=adj[u][i];if(vis[v])continue;
      vis[v]=1;g[v]=g[u]+1;q.push(v);
    }
  }
  for(int i=1;i<=n;++i)vis[i]=0;
  f[0]=1e9;tot=n;dfs(1,0);solve(rt);
  for(int i=1;i<=n;++i)cout<<ans[i]<<endl;
  return 0;
}

```


---

