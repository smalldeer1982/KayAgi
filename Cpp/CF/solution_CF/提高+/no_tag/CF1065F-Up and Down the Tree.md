# Up and Down the Tree

## 题目描述

你有一棵带有 $n$ 个结点的树，根是结点 $1$。有一个标记，最初在根结点处。你可以将标记移动到其他结点处。假设标记当前所在结点为 $v$，你可以做出以下两种操作：
1. 将标记移动到 $v$ 子树的任一叶子处。
2. 如果是结点 $v$ 为叶子，则将标记向根移动不超过 $k$ 次。换句话说，如果 $h_v$ 为结点 $v$ 的深度 (根的深度为 $0$），你可以将其移动到顶点 $to$（$to$ 为 $v$ 祖先）并且 $h_v-k\le h_{to}$。

根不是叶子（即使它的度数是 $1$）。计算最多能访问多少叶子。

## 样例 #1

### 输入

```
7 1
1 1 3 3 4 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 2
1 1 2 3 4 5 5
```

### 输出

```
2
```

# 题解

## 作者：Lynkcat (赞：13)

I hate dp.

所以我选择用纯图论的方法解决这道题。

研究下两个叶子 $x,y$ 之间的关系，容易发现：

设两点 $lca$ 为 $u$。

如果 $dep_y-dep_u \leq k$ 那么可以从叶子 $y$ 跳到 叶子 $x$ 。

如果 $dep_x-dep_u\leq k$ 那么可以从叶子 $x$ 跳到 叶子 $y$ 。

于是我们就得到了一个很 naive 的做法，把所有点与其子树内的叶子连一条有向边，每两个叶子之间能跳的连上边，容易发现有环，那就缩点之后跑最长路。

你会发现边数爆炸！！！

我们再来仔细分析一下这个图，它的冗余边是哪些。

首先，点 $x$ 能到的叶子必然等于它的儿子能到的叶子的并集，也就是说我们只需要将点 $x$ 连向其儿子即可。

其次观察叶子，我们发现可以将其独立考虑，将叶子与其小于等于 $k$ 级的组先都连上边，当然你可能又会发现并没有必要，我们只要将其连向它的 $k$ 级组先即可。

总边数 $O(n)$ 级别，随便过。

~~qnm的dp~~

当然你仔细分析下能发现它的本质和 dp 是一样的，缩点相当于把所有的 f(能回来) 一起算，每在 DAG 上往下走一步也就相当于走一个回不来的。虽然本质相同，但我认为两者思考的方向区别还是比较大的。


ps:令人惊讶的是 Luogu 上好像还没人写过这个写法，当然我没找到的话就是我sb/ll

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
#define N 1000005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int chu[N],n,K,sta[N],tp,f[N],bel[N],sum[N],ye[N],dis[N],ans,cnt,ru[N],dfn[N],low[N],vis[N],_dfn;
queue<int>q;
vector<int>G[N],E[N];
void ad(int x,int y)
{
	G[x].push_back(y);chu[x]++;
}
void ad1(int x,int y)
{
	E[x].push_back(y);ru[y]++;
}
void dfs(int k,int fa)
{
	sta[++tp]=k;
	f[k]=sta[max(1,tp-K)];
	for (auto u:G[k])
	{
		dfs(u,k);
	}
	tp--;
}
void Tarjan(int k)
{
	dfn[k]=++_dfn;
	low[k]=dfn[k];
	sta[++tp]=k;
	vis[k]=1;
	for (auto u:G[k])
	{
		if (!dfn[u])
		{
			Tarjan(u);
			low[k]=min(low[k],low[u]);
		} else
			if (vis[u]) low[k]=min(low[k],dfn[u]);
	}
	if (dfn[k]==low[k])
	{
		++cnt;
		while (sta[tp]!=k)
		{
			bel[sta[tp]]=cnt;
			vis[sta[tp]]=0;
			tp--;
		}
			bel[sta[tp]]=cnt;
			vis[sta[tp]]=0;
			tp--;
	}
}
		
signed main()
{
	n=read(),K=read();
	for (int i=1;i<n;i++) ad(read(),i+1);
	dfs(1,0);
	for (int i=2;i<=n;i++)
		if (!chu[i]) 
		{
			ye[i]=1;ad(i,f[i]);
		}
		
	for (int i=1;i<=n;i++) 
		if (!dfn[i]) 
			Tarjan(i);
	for (int i=1;i<=n;i++)
		for (auto u:G[i])
		{
			if (bel[u]!=bel[i]) ad1(bel[i],bel[u]);
		}
	for (int i=1;i<=n;i++)
		sum[bel[i]]+=ye[i];
	for (int i=1;i<=cnt;i++)
		if (!ru[i]) q.push(i),dis[i]=sum[i],ans=max(ans,dis[i]);
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		for (auto v:E[u])
		{
			dis[v]=max(dis[v],dis[u]+sum[v]);
			ans=max(ans,dis[v]);
			ru[v]--;
			if (!ru[v]) q.push(v);
		}
	}
	writeln(ans);
}
/*

*/
```

---

## 作者：intel_core (赞：8)

纯纯的诈骗题。。。

如果当前到了一个叶节点，要向上跳，肯定是往上跳满 $k$ 级。

一遍 $\text{dfs}$ 处理出当前节点子树内最浅的叶节点的深度 $low_u$。

如果跳进 $u$ 的子树内还能跳回 $u$ 的父亲的充要条件是 $low_u \le depth_{fa_u}+k$。

在跳的过程中，如果跳进一个子树还能跳出来，那么相当于没有影响遍历其他的叶节点。

我们记 $f_u$ 表示跳进 $u$ 子树内对答案的贡献值。

明显的，有 $f_u=\sum\limits_{v\in son_u, depth_u+k\ge low_v}f_v$，然后对所有满足 $v\in son_u , depth_u+k\ge low_v$ 的 $v$ 把 $f_v$ 置为 $0$。

置 $0$ 是为了表示跳进 $v$ 子树后还可以跳回 $u$。

最后的答案就是选一条从根到叶节点的一条路径，路径上节点 $f$ 值的和。

复杂度显然的 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e6+10;
int n,k,f[NR],depth[NR],low[NR];
vector<int>son[NR];
#define pb push_back

void dfs1(int id,int fath){
	depth[id]=depth[fath]+1;
	low[id]=(son[id].empty())?depth[id]:1e9;
	if(son[id].empty())f[id]=1;
	for(int x:son[id]){
		dfs1(x,id);
		low[id]=min(low[id],low[x]);
		if(low[x]<=k+depth[id])f[id]+=f[x],f[x]=0;
	}
}
int dfs2(int id){
	int maxn=0;
	for(int x:son[id])
		maxn=max(maxn,dfs2(x));
	return maxn+f[id];
}

int main(){
	cin>>n>>k;
	for(int i=2,x;i<=n;i++)
		scanf("%d",&x),son[x].pb(i);
	dfs1(1,0);
	cout<<dfs2(1)<<endl;
	return 0;
}
```

---

## 作者：water_tomato (赞：7)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1065f-up-and-down-the-tree-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1065F)。

给出一颗树，走到叶子节点后可以回到它的第 $k$ 祖先，求最多可以访问多少叶子节点。

## 解析

定义 $f_{i}$ 为从 $i$ 节点开始走，最后走回到 $i$ 节点的贡献，$g_i$ 为从 $i$ 节点开始走，最后不用回到 $i$ 节点的最大贡献。

先预处理出从每个点开始走可以回到的最高点，对于叶子节点，初始先将其贡献打到其第 $k$ 个祖先上，这部分代码如下：

```cpp
inline void dfs(int u,int F){
	fa[u][0]=F;dep[u]=dep[F]+1;
	for(int i=1;i<=20;i++){
		fa[u][i]=fa[fa[u][i-1]][i-1];
	}
	bool fl=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;//因为连边的时候仅仅从父亲向儿子连边了，所以这里未判返祖边。
		dfs(v,u);fl=0;
		if(!jp[u]||dep[jp[v]]<dep[jp[u]]) jp[u]=jp[v];//继承儿子可以跳到的最高点
	}
	if(fl){
		int x=u;
		for(int i=0;i<=20;i++){
			if(k&(1<<i)) x=fa[x][i];
		}//往上跳能跳到的最高点
		jp[u]=x;siz[x]++;//siz 即为贡献
	}
}
```

然后考虑对于一个点 $u$，对于其任意一个儿子 $v$，如果走到儿子能跳回到 $u$ 或 $u$ 的祖先，直接将 $f_u$ 加上 $f_v$ 即可。

接下来考虑转移 $g_u$，发现 $g_u$ 显然可以直接加上 $f_u$，然后其相当于要往某一个儿子走，最终不走回来。考虑每一个儿子的剩余价值，对于能跳回到 $u$ 或 $u$ 的祖先的儿子，其剩余价值为 $g_v-f_v$，对于其他儿子，其剩余价值就为 $g_v$，从所有儿子的剩余价值中取一个最大值加上即可。这部分代码如下：

```cpp
inline void dfs2(int u){
	f[u]=siz[u];//初始打上的贡献先加上来
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs2(v);
		if(dep[jp[v]]<=dep[u]) f[u]+=f[v];//能走回来的
	}
	g[u]=f[u];
	int maxx=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(dep[jp[v]]<=dep[u]) maxx=max(maxx,g[v]-f[v]);
		else maxx=max(maxx,g[v]);//找出剩余价值最高的那个
	}
	g[u]+=maxx;
}
```

时间复杂度为 $O(n\log k)$，有趣且不难。

核心代码已给出，连边后依次进行两个 dfs 再输出 $g_1$ 即可。

---

## 作者：Sshenyyyu (赞：6)

巨水的一道树形DP题（但由于未知原因被刷黑了，~~所以我也评了黑题~~）

设siz[i]表示由哪些叶子节点出发可以到达i，显然
$$siz[i]=\sum_{j=child[i]}siz[j](low[j]-dep[i]<=k)$$
其中low[j]表示离j最近的叶子节点深度，dep[i]表示i的深度

这也很好理解，j中所有能到j的叶子都可以以low[j]为跳板跳到i上啦

但这样可能重复计算，所以我们可以把满足要求的j的siz值全清零就行了

最后，我们从根出发，找一条siz和最大的到叶子节点的路径就是答案啦！！

~~是不是很水？~~
```cpp
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
const int M=998244353,INF=1<<30,N=1000005;
int n,m,i,j,u,v,head[N],Next[N],adj[N],k,vis[N],dfn[N],low[N],dep[N],siz[N];
void Push(int u,int v)
{
	Next[++k]=head[u];
	head[u]=k;
	adj[k]=v;
}
void dfs2(int i,int d)
{
	dep[i]=d;
	int j;
	low[i]=1<<30;
	if(vis[i]==0)
		low[i]=d;
	for(j=head[i];j!=0;j=Next[j])
	{
		dfs2(adj[j],d+1);
		low[i]=min(low[i],low[adj[j]]);
	}
}
void dfs3(int i)
{
	int j;
	if(vis[i]==0)
		siz[i]=1;
	for(j=head[i];j!=0;j=Next[j])
	{
		dfs3(adj[j]);
		if(low[adj[j]]-dep[i]<=m)
		{
			siz[i]+=siz[adj[j]];
			siz[adj[j]]=0;
		}
	}
}
int dfs(int i)
{
	int j,s=0;
	for(j=head[i];j!=0;j=Next[j])
		s=max(s,dfs(adj[j]));
	return s+siz[i];
}
int main(){
	scanf("%d %d",&n,&m);
	for(i=2;i<=n;i++)
	{
		scanf("%d",&u);
		Push(u,i);
		vis[u]=1;
	}
	dfs2(1,0);
	dfs3(1);
	printf("%d",dfs(1));
}

```

---

## 作者：傅思维666 (赞：1)


## 题解：

~~2019.10.28模拟赛T3骗分场~~

一开始发现暴力打起来很麻烦，正解不会。那么想到骗分。很显然，它求最多的可达叶子节点个数，那么会有**很大的可能**答案是所有叶子节点的个数。当然，这是过不了样例的。但是实测证明直觉很正确，骗到了60分（逃）

正解是树形DP。

在我个人的理解中，树形DP其实就是把一个节点的信息向上回溯统计得到答案的一类DP题。

那么我们分析一下思路：很显然，根据贪心原则，我们在从1号点选择往下走的时候，当然是挑选可达叶子节点最多的一棵子树来走。就是要看这个叶子节点往上跳能到达的节点中，相连叶子节点最多的点。

显然，统计的量就是$size[i]$表示$i$节点的可达叶子节点的数量。

为了维护这个东西，我们继续统计两个量：第一个就是离某点最近的叶子节点的深度，定义为$near[i]$，并且统计所有节点的正常深度$deep[i]$。

那么，根据题意有：
$$
size[i]=\sum_{to\in children[i]}(near[j]-deep[i]\le k)
$$


那么我们只需要深搜处理出这几个数组，然后从底到上进行搜索求解更新即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e6+10;
const int INF=1e9;
int n,k;
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1];
int deep[maxn],size[maxn],low[maxn];
bool v[maxn];
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dfs1(int x,int d)
{
    deep[x]=d;
    low[x]=INF;
    if(!v[x])
        low[x]=d;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        dfs1(y,d+1);
        low[x]=min(low[x],low[y]);
    }
}
void dfs2(int x)
{
    if(!v[x])
        size[x]=1;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        dfs2(y);
        if(low[y]-deep[x]<=k)
        {
            size[x]+=size[y];
            size[y]=0;
        }
    }
}
int getsum(int x)
{
    int ret=0;
    for(int i=head[x];i;i=nxt[i])
        ret=max(ret,getsum(to[i]));
    return ret+=size[x];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=2;i<=n;i++)
    {
        int a;
        scanf("%d",&a);
        add(a,i);
        v[a]=1;
    }
    dfs1(1,0);
    dfs2(1);
    printf("%d",getsum(1));
    return 0;
}
```



---

## 作者：Hoks (赞：0)

## 前言
吐槽下这场为什么 DE 是紫的 F 是蓝的，原来是诈骗题。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
设计 $f_u$ 表示 $u$ 这个子树的最大答案。

那么转移就是 $f_u=\sum\limits_{v\in S} f_v$，其中 $S$ 定义为 $u$ 的儿子中满足能跳到 $u$ 所有点的集合。

接着就是怎么求这些满足的点了。

对于一个点 $v$，他能跳到的最上面的点，就是先走到一个最浅的叶子，再往上跳 $k$ 步。

先处理出这个东西，扫一遍儿子转移 dp 即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=0x3f3f3f3f3f3f3f3f;
int n,k,f[N],t[N],dep[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    // #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs(int u,int fa)
{
    dep[u]=dep[fa]+1;t[u]=(e[u].empty())?dep[u]:INF;f[u]=e[u].empty();
    for(auto x:e[u])
    {
        dfs(x,u);t[u]=min(t[u],t[x]);
        if(t[x]<=k+dep[u]) f[u]+=f[x],f[x]=0;
    }
}
inline int solve(int u){int mx=0;for(auto x:e[u]) mx=max(mx,solve(x));return mx+f[u];}
signed main()
{
    n=read(),k=read();for(int i=2;i<=n;i++) e[read()].emplace_back(i);
    dfs(1,0);print(solve(1));genshin:;flush();return 0;
}
```

---

## 作者：cheng2010 (赞：0)

# Up and Down the Tree
## 思路
dp。

设 $near_i$ 为以 $i$ 为根的子树中的叶子节点中离 $i$ 最近的叶子节点的距离。

设 $f_i$ 为以 $i$ 为根的答案。

发现可以通过 $f_{son_i}$ 转移到 $f_i$。具体的，如果 $i$ 的儿子的 $near$ 可以到 $i$，那么其他的便可以以 $near$ 为跳板到 $i$。
即：$ f_x= \displaystyle\ \sum_{v=son_x} f_v \times [near_v-dep_x \le k ] $。

- 注意
直接这样算会算重，所以对于每一个有贡献的 $f_v$ 要清零。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
const int INF=2147483647;
int n,k;
struct EDGE
{
	int frm,to;
}edge[N];
int cnt,head[N];
int f[N];
int near[N];
int dep[N];
inline void add(int x,int y)
{
	edge[++cnt].to=y;
	edge[cnt].frm=head[x];
	head[x]=cnt;
}
inline void dfs1(int x)
{
	int s=0;
	near[x]=INF;
	for(int i=head[x];i;i=edge[i].frm)
	{
		s++;
		int v=edge[i].to;
		dep[v]=dep[x]+1;
		dfs1(v);
		near[x]=min(near[x],near[v]);
	}
	if(!s)
	{
		near[x]=dep[x];
	}
}
inline void dfs2(int x)
{
	int s=0;
	for(int i=head[x];i;i=edge[i].frm)
	{
		s++;
		int v=edge[i].to;
		dfs2(v);
		bool b=(near[v]-dep[x]<=k);
		f[x]+=f[v]*b;
		f[v]*=(!b);
	}
	if(!s)
	{
		f[x]=1;
	}
}
inline int get(int x)
{
	int res=0;
	for(int i=head[x];i;i=edge[i].frm)
	{
		int v=edge[i].to;
		res=max(res,get(v));
	}
	return res+f[x];
}
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add(x,i);
	}
	dep[1]=1;
	dfs1(1);
	dfs2(1);
	printf("%d\n",get(1));
}
```

---

