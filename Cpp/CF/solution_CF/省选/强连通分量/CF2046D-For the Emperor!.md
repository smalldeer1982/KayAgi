# For the Emperor!

## 题目描述

在古罗马，为了击败野蛮人，制定了一项计划，但要实施该计划，每个城市都必须得到通知。

罗马帝国的北部由 $n$ 个城市组成，这些城市通过 $m$ 条单向道路相连。起初，第 $i$ 个城市有 $a_i$ 名信使，每名信使可以沿着现有的道路自由地在城市间移动。一名信使可以携带一份计划副本，并在他访问的城市中传达信息，并且可以在他当前所在的城市为其他信使制作无限多的副本。

开始时，你需要制作一定数量的计划，并将它们交给选定的信使。你的目标是确保每座城市都被携带计划的信使访问过。找出最初需要制作的计划的最小数量，以确保信使能够将计划送到每一个城市，或者确定根本无法做到这一点。

## 样例 #1

### 输入

```
2
7 6
2 1 0 1 2 3 4
1 2
1 3
2 4
2 5
3 6
3 7
4 4
1 1 1 1
1 2
1 3
2 4
3 4```

### 输出

```
2
2```

# 题解

## 作者：Milmon (赞：16)

## Statement

有一张 $n$ 个点 $m$ 条边的**有向**图，第 $i$ 个点上有 $a_i$ 个人。

你可以选择一些结点发放一份计划，接下来每个人可以沿着边自由移动，如果一个人从一个收到过计划的点移动到一个没有收到计划的点，那么可以令其收到计划。

你需要让所有的点都收到计划，求最少需要在多少个结点发放计划，或者报告无解。

数据范围：数据组数 $T \leq 100$，$2 \leq n \leq 200$，$1 \leq m \leq 800$，$0 \leq a_i \leq n$。

## Solution

考虑建立费用流模型，核心思想是让最大流量总是 $\sum a_i$，而经过一个点的费用是 $-B$（$B$ 是一个极大的数），在一个点发放计划的费用是 $1$，这样求出最小费用之后，可以根据其除以 $B$ 的整数部分计算其最多能让多少个点收到计划，根据余数计算出该前提下最小发放计划的数量。

记源点为 $S$，汇点为 $T$。考虑按照下述方案连边：

- 为了限制从一个点 $u$ 出发的人的数量为 $a_u$，先建立一个约束点 $F_u$，连一条流量为 $a_u$ 的边 $S \to F_u$。
- 考虑为一个点 $u$ 建立一个入点 $P_u$ 和一个出点 $Q_u$，流过 $P_u \to Q_u$ 这条边就认为一个人走过的路径经过了点 $u$。要让第一次经过产生 $-B$ 的费用，之后不产生费用，只需要连两条流量分别为 $1$ 和 $+\infty$、费用分别为 $-B$ 和 $0$ 的边即可。
- 为了让一开始发放计划的点产生 $1$ 的费用，而当点被经过之后从该点出发不产生 $1$ 的费用，只需连边 $F_u \to P_u$，流量和费用均为 $1$，再连边 $F_u \to Q_u$，流量为 $+\infty$，费用为 $0$。如果 $F_u \to Q_u$ 被经过，那么 $P_u \to Q_u$ 的费用为 $-B$ 的边一定被经过，此时点 $u$ 已经被发放计划，所以不产生贡献。
- 对于原图的有向边 $u \to v$，需要连边 $Q_u \to P_v$。
- 最后当人结束移动时流向汇点，即连边 $Q_u \to T$。

如果原图存在环，那么需要先进行强联通分量缩点，$a$ 的值为 SCC 内所有点的 $a$ 的值的和。

按照上述方案连边，总点数是 $\Theta(n)$ 的，总边数是 $\Theta(n + m)$ 的，使用最小费用最大流解决可以接受。

## Solution (English)

Consider constructing a cost-flow model. The core idea is to ensure that the maximum flow is always $\sum a_i$, and the cost of passing through a point is $-B$ (where $B$ is a very large number). The cost of issuing a plan at a point is $1$. After calculating the minimum cost, its integer part divided by $B$ represents the maximum number of points that can receive the plan, while the remainder determines the minimum number of plans issued under this condition.

Let the source be $S$ and the sink be $T$. Edges are constructed as follows:

- To limit the number of people starting from a point $u$ to $a_u$, introduce a constraint point $F_u$ and connect an edge with capacity $a_u$ from $S \to F_u$.
- For a point $u$, create an entry node $P_u$ and an exit node $Q_u$. If a path passes through the edge $P_u \to Q_u$, it means that someone has traversed point $u$. To ensure that the first traversal incurs a cost of $-B$ while subsequent traversals incur no cost, simply add two edges with capacities $1$ and $+\infty$, and costs $-B$ and $0$, respectively.
- To ensure that issuing a plan at a point initially incurs a cost of $1$, and subsequent departures from the point incur no cost, connect edges $F_u \to P_u$ with both capacity and cost of $1$, and $F_u \to Q_u$ with capacity $+\infty$ and cost $0$. If the edge $F_u \to Q_u$ is used, then the edge $P_u \to Q_u$ with cost $-B$ must have been traversed, indicating that point $u$ has already been issued a plan and thus contributes no additional cost.
- For a directed edge $u \to v$ in the original graph, connect an edge $Q_u \to P_v$.
- Finally, to allow people to end their movement at the sink, connect edges $Q_u \to T$.

If the original graph contains cycles, first perform a strongly connected components (SCC) contraction. The value of $a$ for each SCC is the sum of the $a$ values of all points within the SCC.

Following the above scheme for edge construction, the total number of nodes is $\Theta(n)$, and the total number of edges is $\Theta(n + m)$. Solving this using minimum-cost maximum-flow is accepted.

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e5;

struct MinCostFlow{
    static const int N=602,M=2000;
    int n,cntEdge,head[N+1];
    struct Edge{
        int to,nxt,lim,cost;
    }edge[(M+1)*2];
    inline void addEdge(int u,int v,int lim,int cost){
        edge[++cntEdge]={v,head[u],lim,cost},head[u]=cntEdge;
        edge[++cntEdge]={u,head[v],0,-cost},head[v]=cntEdge;
    }
    inline void init(int _n){
        n=_n,cntEdge=1;
        memset(head,0,sizeof(int)*(n+1));
    }
    int dis[N+1],minn[N+1],pre[N+1],preEdge[N+1];
    bool inQueue[N+1];
    inline bool SPFA(int S,int T){
        memset(dis,0x7f,sizeof(int)*(n+1));
        memset(minn,0x7f,sizeof(int)*(n+1));
        memset(inQueue,false,sizeof(bool)*(n+1));
        queue<int> Q;
        Q.push(S),dis[S]=0,inQueue[S]=true,pre[T]=-1;
        while(!Q.empty()){
            int u=Q.front(); Q.pop();
            inQueue[u]=false;
            for(int i=head[u];i;i=edge[i].nxt){
                int v=edge[i].to;
                if(edge[i].lim&&dis[u]+edge[i].cost<dis[v]){
                    dis[v]=dis[u]+edge[i].cost;
                    pre[v]=u,preEdge[v]=i,minn[v]=min(minn[u],edge[i].lim);
                    if(!inQueue[v])Q.push(v),inQueue[v]=true;
                }
            }
        }
        return pre[T]!=-1;
    }
    inline pair<int,int> flow(int S,int T){
        int maxflow=0,mincost=0;
        while(SPFA(S,T)){
            maxflow+=minn[T],mincost+=minn[T]*dis[T];
            int u=T;
            while(u!=S){
                edge[preEdge[u]].lim-=minn[T];
                edge[preEdge[u]^1].lim+=minn[T];
                u=pre[u];
            }
        }
        return {maxflow,mincost};
    }
}G;

int n,m,a[201];
vector<int> E[201];

int dfn[201],low[201],cntdfn;
int cntscc,scc[201],siz[201];
bool vis[201];
stack<int> sta;
void tarjan(int u){
    dfn[u]=low[u]=++cntdfn,vis[u]=true,sta.push(u);
    for(int v :E[u]){
        if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
        else if(vis[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        scc[u]=++cntscc,siz[cntscc]=0;
        int v;
        do v=sta.top(),sta.pop(),siz[cntscc]+=a[v],scc[v]=cntscc,vis[v]=false;
        while(v!=u);
    }
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)E[i].clear(),dfn[i]=low[i]=vis[i]=0;
        cntdfn=cntscc=0;
        for(int i=1;i<=n;i++)scanf("%d",a+i);
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
        }
        for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
        G.init(cntscc*3+2);
        auto id=[&](int t,int u){
            return t*cntscc+u;
        };
        int S=id(3,1),T=id(3,2);
        for(int i=1;i<=cntscc;i++){
            if(siz[i]){
                G.addEdge(S,id(0,i),siz[i],0);
                G.addEdge(id(0,i),id(1,i),1,1);
                G.addEdge(id(0,i),id(2,i),inf,0);
            }
            G.addEdge(id(1,i),id(2,i),1,-inf);
            G.addEdge(id(1,i),id(2,i),inf,0);
            G.addEdge(id(2,i),T,inf,0);
        }
        for(int u=1;u<=n;u++)
            for(int v :E[u])if(scc[u]!=scc[v])
                G.addEdge(id(2,scc[u]),id(1,scc[v]),inf,0);
        int cost=-G.flow(S,T).second;
        int used=(inf-cost%inf)%inf,covered=(cost+used)/inf;
        printf("%d\n",covered==cntscc?used:-1);
    }
    return 0;
}
```

---

## 作者：Albert_van (赞：9)

[题](https://www.luogu.com.cn/problem/CF2046D) [题](https://mirror.codeforces.com/contest/2046/problem/D)。一道赛时通过人数仅 50 的网络流。搬运官解，顺便复习一下上下界费用流。

最终情况是所有点上的所有人都被激活。所以先不考虑最小化，直接手动激活所有人，判断是否能覆盖全图（判 $-1$）。上下界网络流是一个强力工具，碰到此类限制“每个点至少被一个人经过”，无需考虑链剖分之类科技，直接把 $u$ 拆成 $u_{in}$ 和 $u_{out}$，在其间设置流量下界即可。如此建模（以下流量下界默认 $0$，上界默认 $\inf$）：

- $S\to u_{in}$，上界 $a_u$；
- $u_{in}\to u_{out}$，下界 $1$；
- $u_{out}\to T$；
- 对原图边 $(u,v)$，连 $u_{out}\to v_{in}$。

有源汇上下界可行流。核心思想在于绕过了形如“一个人经过点 $u$ 会分裂成 $a_u$ 个人”的思维陷阱。回到原题，最小化手动激活的点数，考虑什么样的点 $u$ 需要手动激活：没有人从外部走来并经过点 $u$，即 $u_{in}$ 没有流量输入。那么直接想法就是，手动以 $1$ 的费用向 $u_{in}$ 输入 $1$ 点流量。在上面建模的基础上修改（所有边费用默认 $0$）：

- $\color{red}{S\to u_{in}}$（删除）$S\to u_0$，上界 $a_u$；
- $u_0\to u_{in}$，上界 $1$，费用 $1$；
- $u_0\to u_{out}$。

![](https://s3.bmp.ovh/imgs/2024/12/05/45dcdd63587b31fa.png)

这是形如“有多个，但只有一个应该付费”的常用建模。跑有源汇上下界最小费用可行流。然后你喜提 WA Pretest#2，发现一个 $a_1=a_2=0$ 的二元环就能够将你 hack 掉。

这是因为，有源汇上下界最小费用**可行**流的要求是，在连边 $T\to S$ 后转为无源汇问题并构造一组**循环流**，也就是说，在连边 $T\to S$ 之前，**并不要求**图中流量全部从 $S$ 流出并汇集到 $T$。如果连边 $T\to S$ 后存在不包含 $(T,S)$ 这条边的环（即构建的图本身有环），求得的一组流就可能不满足要求。

于是我们希望原图是 DAG。发现原图的强连通分量可以缩点，新点的 $a$ 就是原图的 $\sum a$。做完了，注意数组点数开够。

```cpp
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

const int N=231;

bool G[N][N],ist[N];

int a[N],b[N],dfn[N],low[N],stk[N],bel[N],dfscnt,tp,kcnt,n;

void tar(int now){
	dfn[now]=low[now]=++dfscnt;
	stk[++tp]=now;ist[now]=1;
	for(int v=1;v<=n;++v) if(G[now][v]){
		if(!dfn[v]) tar(v),low[now]=min(low[now],low[v]);
		else if(ist[v]) low[now]=min(low[now],dfn[v]);
	}
	if(dfn[now]==low[now]){
		++kcnt;do ist[stk[tp]]=0,bel[stk[tp]]=kcnt,b[kcnt]+=a[stk[tp]];while(stk[tp--]!=now);
	}
}

namespace Dnc{
	const int N=::N<<2;
	int inv(int x){return x&1?x+1:x-1;}
	struct ed{
		int v,w,c,nxt;
	}e[114514];int head[N],ecnt;
	void cnct(int u,int v,int w,int c){
		e[++ecnt]=(ed){v,w,c,head[u]};head[u]=ecnt;
	}
	void lnk(int u,int v,int w,int c){cnct(u,v,w,c);cnct(v,u,0,-c);}
	queue<int> q;
	int d[N],s,t;bool inq[N];
	bool spfa(){
		memset(d,63,sizeof(d));
		d[s]=0;q.push(s);inq[s]=1;
		while(!q.empty()){
			int now=q.front();q.pop();inq[now]=0;
			for(int i=head[now];i;i=e[i].nxt) if(e[i].w&&d[now]+e[i].c<d[e[i].v]){
				d[e[i].v]=d[now]+e[i].c;if(!inq[e[i].v]) q.push(e[i].v),inq[e[i].v]=1;
			}
		}
		return d[t]!=0x3f3f3f3f;
	}
	int cur[N],flw,cst;bool vis[N];
	int flow(int now,int f){
		if(now==t) return flw+=f,f;
		vis[now]=1;int r=f;
		for(int i=cur[now];i&&r;i=e[i].nxt){
			cur[now]=i;if(e[i].w&&d[e[i].v]==d[now]+e[i].c&&!vis[e[i].v]){
				int nf=flow(e[i].v,min(r,e[i].w));
				e[i].w-=nf;e[inv(i)].w+=nf;r-=nf;cst+=nf*e[i].c;
			}
		}
		return vis[now]=0,f-r;
	}
	void dinic(){while(spfa()) memcpy(cur,head,sizeof(cur)),flow(s,N);}
	void clr(){
		memset(head,0,sizeof(head));ecnt=flw=cst=0;
	}
}using Dnc::lnk;

int x[1024],y[1024];

int main()
{
	int Ts;scanf("%d",&Ts);while(Ts--){
		int m;scanf("%d%d",&n,&m);
		int S=3*n+1,T=S+1,s=T+1,t=s+1;lnk(T,S,N,0);
		for(int i=1;i<=n;++i) scanf("%d",a+i);
		for(int i=1;i<=m;++i) scanf("%d%d",x+i,y+i),G[x[i]][y[i]]=1;
		for(int i=1;i<=n;++i) if(!dfn[i]) tar(i);
		for(int u=1;u<=kcnt;++u){
			lnk(S,u,b[u],0);lnk(u,u+n,1,1);lnk(u,u+2*n,N,0);lnk(u+2*n,T,N,0);
			lnk(u+n,u+2*n,N,0);lnk(s,u+2*n,1,0);lnk(u+n,t,1,0);
		}
		for(int i=1;i<=m;++i) if(bel[x[i]]!=bel[y[i]]) lnk(bel[x[i]]+2*n,bel[y[i]]+n,N,0);
		Dnc::s=s;Dnc::t=t;Dnc::dinic();
		printf("%d\n",Dnc::flw==kcnt?Dnc::cst:-1);
		Dnc::clr();memset(G,0,sizeof(G));memset(b,0,sizeof(b));memset(dfn,0,sizeof(dfn));dfscnt=kcnt=0;
	}
}
```

---

## 作者：Nelofus (赞：4)

凭啥 3k1 来着。

首先显然要缩点成一个 DAG，每个点的 $a$ 是 SCC 里所有的 $a$ 之和，然后考虑网络流。

一条一条限制看，首先点 $u$ 能派出的信使个数 $\operatorname{out}(u)$ 与到达点 $u$ 的信使个数 $\operatorname{in}(u)$ 必然有：

$$
\operatorname{out}(u)\le \operatorname{in}(u)+a_u
$$

然后每个点都必须要有至少一个信使经过，那么就把点 $u$ 拆成 $u_{\text{in}}$ 和 $u_{\text{out}}$，连一条 $u_{\text{in}}$ 到 $u_{\text{out}}$ 的下界为 $1$，上界为 $+\infin$ 的边。

考虑什么时候要单独给 $u$ 一份计划，当且仅当入流量为 $0$，也就是说，没法满足 $u_{\text{in}}$ 到 $u_{\text{out}}$ 的下界。开一个新点 $u_{\text{mid}}$，向 $u_\text{in}$ 连一个上界为 $1$，费用为 $1$ 的边，向 $u_{\text{out}}$ 连一条上界为 $+\infin$ 的边。

结合第一条限制，$s$ 再向 $u_\text{mid}$ 连一条上界为 $a_u$ 的边，因为信使可以在任何一个站点停下，所以再从 $u_{\text{out}}$ 向 $t$ 连一条上界为 $+\infin$ 的边。

然后直接最小费用上下界可行流。

---

## 作者：mqmhaaaa1 (赞：3)

不错的流流题，这篇题解采用**费用流**做法。

# 分析

大概可以想到每个点可以出 $a_i$ 的流量，每次代价为 $1$，要求经过每个点一次，问最小代价。

可能一看题面会想到上下界，毕竟要经过每个点至少一次。但因为上下界是一个十分不好理解的流流（至少对我而言是这样的），因此我想到可以利用费用流的性质来**骗**流量，流量经过每一个点，有点像 [p4542](https://www.luogu.com.cn/problem/P4542) 的费用流做法。

因为此方法下网络流图不能有负环，所以我们先所点，把原图缩成一个 DAG 后再来做，这样的话，缩好后一个点内只需要一个信使到便可以全部经过（强联通分量），这个点的 $a_i$ 自然变成所有被缩成此点的点的 $a_i$ 之和。

我们考虑如何尽量让流量经过点。不难想到我们在跑最小费用流时，流量肯定会按费用最小的路径走。因此，我们可以令点尽量在最小费用的路径上，在不知几轮增广后便所有的点都会被经过一次，或者说原本无解。

具体而言，我们将点 $u$ 拆成 $ui,uo$ 分别表示入点，出点。连 $ui \to uo$ 流量为 $1$，费用为 $-inf$（$inf$ 是很大的数）。这样设计的话，增广时每条没被经过的这种 $ui \to uo$ 的边如果可以的话一定会优先在增广路上，因为费用特别小。在增广不知几轮后所有这种边便都会被经过，代表所有的点都被经过一次了。

除此之外，还要连 $ui \to uo$ 流量 $inf$ 费用 $0$，因为一个点可以经过多遍，但只需要经过一次，多次经过**没有额外贡献**，所以之前的边流量为 $1$。

想信了解流流套路的都知道对原图中的每条边如何处理，这里不赘述。

接下来才是难想的部分（也就是为什么它有 3100），**如何处理信使**。

首先肯定能想到源点 $s$ 向每个 $ui$ 连流量为对应 $a_i$ 的边，费用为 $1$，表示出动一名拿了计划副本的信使，然后连 $uo \to t$（$t$ 是汇点）流量为 $inf$，表示在经过一个点后这个信使可以选择完成任务。那接下来如何处理**到一个点，那个点的信使便都可以免费出来呢**。

确实很难想，可以这么理解：

当我们经过一个点 $u$，便是经过了 $ui \to uo$ 的边，说明经过这边后所有该点信使便 free（此处表免费）了。说明，只要**到了一个点的 $uo$，便算经过该点**。

那我们可以为每个点 $u$ 再新建一个点 $ux$，连 $s \to ux$ 流量为对应 $a_i$，用来限制流量。把 $s \to ui$ 改为 $ux \to ui$，再新建边 $ux \to uo$ 流量 $inf$ 费用 $0$，表示到 $uo$ 后这个点的信使就可以随便用。

为什么对？我们考虑这样几种情况。

1. 当真的有流量老老实实经过 $ui \to uo$，那没问题。

2. 当没有有流量流过 $ui \to uo$，因为原图已经缩成了 DAG，所以不会出现由 $uo$ 流出的流量绕一圈回来的情况，只会经过这条链到底的点，那必定有一个 $-inf$ 的费用没有被加上，到时候我们在总费用加上 点数 $ \times inf$ 的费用后会有 $-inf$ 与 $inf$ 无法完全抵消，便会多一大截费用，这时候直接判无解。

这样处理便可完美的通过此题，复杂度为 $O(dinic(3n,5n+m))$（大概 $O(n^3m)$），可过。

还有些细节

1. 答案至多是点数，超过直接判无解（很好理解）

2. 事实上跑到增广路上没有没经过的原图中的点（即本次增广费用 $ \ge 0$）就可以退出了，说明所有点已经经过了（所以才不是最小费用最大流）

码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define i8 __int128
void write(ll x) {static ll sta[35];ll top = 0;do {sta[top++] = x % 10, x /= 10;} while (x);while (top) putchar(sta[--top] + 48);}
ll read() {ll x = 0, w = 1;char ch = 0;while (ch < '0' || ch > '9') {  if (ch == '-') w = -1;ch = getchar();}while (ch >= '0' && ch <= '9') {x = x * 10 + (ch - '0'); ch = getchar(); }return x * w; }
const ll N=1000,M=1e6+10,inf=0x7f7f7f7f;
ll to[M<<1],nxt[M<<1],w[M<<1],c[M<<1],bh[N],tot=1;
ll head[N],dis[N];
bool vis[N];
inline void add(ll u,ll v,ll flow,ll cost){
	to[++tot]=v;
	nxt[tot]=bh[u];
	w[tot]=flow;
	c[tot]=cost;
	bh[u]=tot;
//	cout<<u<<' '<<v<<' '<<flow<<'\n';
	to[++tot]=u;
	nxt[tot]=bh[v];
	w[tot]=0;
	c[tot]=-cost;
	bh[v]=tot;
}
ll s,t;
inline bool spaf(){
	for(ll i=0;i<=t;i++){
		vis[i]=0;head[i]=bh[i];
		dis[i]=inf;
	}
	queue<ll>q;
	vis[s]=1;dis[s]=0;
	q.push(s);
	while(q.size()){
		ll u=q.front();q.pop();
		vis[u]=0;
		for(ll i=bh[u];i;i=nxt[i]){
			ll v=to[i];
			if(w[i]&&dis[u]+c[i]<dis[v]){
				dis[v]=dis[u]+c[i];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
//	cout<<dis[t]<<'\n';
	return dis[t]!=inf&&dis[t]<0;//事实上这里dis[t]<0也不用判，和后面的ans<(num-1)*inf等效 
}
ll ans,mxf;
ll dic(ll u,ll flow){
	vis[u]=1;
//	cout<<u<<' '<<flow<<'\n';
	if(u==t){
		mxf+=flow;
		return flow;
	}
	ll zy=0;
	for(ll i=head[u];i&&flow;i=nxt[i]){
		ll v=to[i];head[u]=i;
		if(w[i]&&(!vis[v]||v==t)&&dis[v]==dis[u]+c[i]){
			ll jb=dic(v,min(w[i],flow));
			w[i]-=jb;w[i^1]+=jb;
			zy+=jb;flow-=jb;
			ans+=jb*c[i];
			if(!flow)break;
		}
	}
	vis[u]=0;
	return zy;
}//优质dinic 
ll n,m,a[N];
ll to1[M],nxt1[M],bh1[N],tot1=1;
void add1(ll u,ll v){
	to1[++tot1]=v;
	nxt1[tot1]=bh1[u];
	bh1[u]=tot1;
} 
ll dfn[N],cnt=0,fa[N],low[N];
ll sum[N],num=0;
ll stc[N],top=0;
void tarjan(ll u){
	dfn[u]=low[u]=++cnt;
	stc[++top]=u;vis[u]=1;
	for(ll i=bh1[u];i;i=nxt1[i]){
		ll v=to1[i];
		if(!dfn[v]){
			tarjan(v);low[u]=min(low[u],low[v]);
		}else if(vis[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		ll v=stc[top];
		num++;
		while(v!=u){
			fa[v]=num;
			vis[v]=0;
			sum[num]+=a[v];
			v=stc[--top];
		}
		vis[u]=0;fa[u]=num;
		sum[num]+=a[u];--top;
	}
}
void work(){
	for(ll i=0;i<=n*3+10;i++){
		bh[i]=bh1[i]=fa[i]=sum[i]=dfn[i]=stc[i]=low[i]=0;
	}//清空 
	tot1=tot=1;
	mxf=ans=num=0;
	n=read(),m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=m;i++){
		ll u=read(),v=read();
		add1(u,v);
	}
	for(ll i=1;i<=n;i++){
		if(!dfn[i])tarjan(i);
	}//记得跑tarjan 
	s=0,t=num*3+1;//这里开始点数就等于tarjan缩完的点数了 
	for(ll i=1;i<=num;i++){
		ll ui=i,uo=i+num,ux=i+2*num;
		add(s,ux,sum[i],0);
		add(ui,uo,1,-inf),add(ui,uo,inf,0);
		add(ux,ui,1,1),add(ux,uo,inf,0);
		add(uo,t,inf,0);
	}
	for(ll u=1;u<=n;u++){
		for(ll i=bh1[u];i;i=nxt1[i]){
			ll v=to1[i];
			if(fa[u]!=fa[v]){
				add(fa[u]+num,fa[v],inf,0);
			}
		}
	}
	while(spaf()){
		vis[t]=1;
		while(vis[t]){
			memset(vis,0,sizeof vis);
			dic(s,inf);
		}
		if(ans<=-inf*(num-1))break;//相当于是真实费用（除去-inf) +num*inf后>=0 
	}
	ans+=num*inf;
	if(ans<=num)write(ans),puts("");
	else puts("-1");//无解 
	
}
int main(){
	ll T=read();
	while(T--)work();
} 
```

这题想懂了确实没 3100，可流流题不都这样吗。（还有推荐把 [p4542](https://www.luogu.com.cn/problem/P4542)
切了，和这题处理经过每个点有点像）

---

## 作者：dspt (赞：3)

这题自己想挺难吧，赛时只过了 20 个人，建议评黑。以下做法和图来自官方题解。

先**缩点**，同一个 SCC 内的 $a_u$ 求和，建出的 DAG 与原图是等价的。显然在 DAG 上思考更加方便。不难看出需要网络流。

## 判断无解

通过**最大流**判断是否有解。

我们发现这题的难点在于难以刻画“信使经过了每个点”这个限制。最简单的想法是把每个点拆点成 $u_{\text{in}}$ 和 $u_{\text{out}}$ 两个点，连边 $u_{\text{in}}\xrightarrow{\infin}u_{\text{out}}$。限制就变成了这条边的流量 $\geqslant 1$。

先不管复制这个事情，每个点有 $a_i$ 限制最直接的建模就是 $S\xrightarrow{a_u}u_{\text{in}}$。原图上的边 $u\to v$ 建成 $v_{\text{out}}\xrightarrow{\infin}u_{\text{in}}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ykoa12n4.png)

就像这样，这个限制容易将我们导向上下界网络流，但是我们后面还要引入费用流，所以考虑把下界的限制消掉。

考虑建两个虚点 $S',T'$，如果这条边的流量 $\geqslant 1$，那么可以断言流入 $u_{\text{in}}$ 的流量 $\geqslant 1$，流出 $u_{\text{out}}$ 的流量 $\geqslant 1$。那么我们额外连上 $S'\xrightarrow1u_{\text{in}},u_{\text{out}}\xrightarrow1T'$。

现在我们有两个源点和两个汇点。注意到原先的流量的意义是“信使”。但是这样跑最大流是没有意义的，我们不需要“信使”最多。那么这个流就可以搞成**循环流**的形式，即 $T\xrightarrow{\infin}S$。真正有意义的是 $S'\to T'$ 的流，流量是**经过的点的数量**。

![](https://cdn.luogu.com.cn/upload/image_hosting/uvlxvbr6.png)

在这个图上跑最大流，如果流量为 $n$，那么就有解，否则无解。

## 计算答案

通过**最小费用最大流**计算答案。

引入费用，上图中所有边的费用为零。我们发现费用只有一个来源：某个满足 $a_u\geqslant 1$ 的点 $u$，可以花一的代价在 $u_{\text{in}}$ 处获得 $a_u$ 的流量。费用流好像没有这种花一的代价获得很多流量的这种建模。但是注意到 $u_{\text{in}}$ 和 $u_{\text{out}}$ 的唯一区别在于 $u_{\text{in}}\to T'$ 的这条边，而这条边的流量为一。意思就是说 $u_{\text{in}}$ 只有流量 $\geqslant 1$ 和无流量两种状态。流量 $\geqslant 1$ 的话必然会有恰好为一的流量流到 $T'$。

所以再对点 $u$ 建一个虚点 $u_\text{cnt}$，$u_\text{cnt}\to u_{\text{in}}$ 连一条费用为一的边，$u_{\text{cnt}}\to u_{\text{out}}$ 连一条费用为零的边，$S\to u_{\text{cnt}}$ 连一条容量为 $a_u$，费用为零的边。

![ ](https://cdn.luogu.com.cn/upload/image_hosting/sv37dsaz.png)	

​	这个建模还是比较抽象的，我们来看看实际上流是怎样的：

+ 选了点 $u$，分这样两条流，$u_\text{out}$ 的流量 $\geqslant a_u$，$u_{\text{in}}\to T'$ 的边流满了，说明这个点被经过了。 

  ![](https://cdn.luogu.com.cn/upload/image_hosting/vnr5vop2.png)

+ 没选点 $u$，可以发现流入 $u_{\text{in}}$ 的流量 $\geqslant 1$，$u_{\text{out}}$ 的流量 $\geqslant a_u+1$，$u_{\text{in}}\to T’$ 的边流满了，说明这个点被经过了。 

  ![](https://cdn.luogu.com.cn/upload/image_hosting/qgc4s32t.png)

---

这张图点数为 $3n+4$，边数为 $2(8n+m)$，跑任何费用流算法都可以通过。[代码](https://codeforces.com/contest/2046/submission/295505563)。

---

## 作者：Graygoo (赞：3)

vp 赛后两分钟过题。

  先解决一些简单的部分。比如跑个 $\text{tarjan}$ 就成了 DAG 上的问题。

  我不是天赋哥，所以遇到这种一眼流肯定不能硬想，得尝试调用一下记忆库。

  你在做过的流套路里进行一个检索，显然发现最接近的是 DAG 最小链覆盖。

  当然这里显然还是可重的。众所周知原问题的可重版本有两种做法，一个是传递凹包，一个是 $n+i$ 向 $i$ 连 $\inf$ 边。前面那个过于的 low，所以我们选择后一种方法。

  显然源点连向每个点的流量是多少是重要的。考虑原问题相当于所有点的 $a_i$ 都为 $0$ 的情况，此时这个流量为 $1$，所以我们可以猜测，该问题中流量为 $a_i + 1$。

  再考虑到一个简单事实，就是最后匹配的“链头”不能被其它点贡献，因此我们允许每个点有一个流量花费一点费用从出点走到自己的入点。
  
  现在我们可以进行一个简单的思维模拟。你从 $i$ 点出发，有一个流量和自己匹配，其余所有流量都走到了新点 $j$，其中一个流量和 $j$ 匹配，剩下来一个通过反边走到这个点的出点。此时 $j$ 的出点拥有的流量为 $a_i - 1 + a_j + 1 = a_i + a_j$，这个数字和我们想要的组合意义是一致的。因此这个过程可以不断进行下去，同时将链上经过的所有点都加入匹配。

  这样的话跑一下最小费用最大流即可，是否有解即为最大流是否为 scc 个数。

  你交一下，发现 WA 了。考虑到 $a_i = 0$ 的点不可能当链头，所以 $a_i = 0$ 的点不能向自己的入点连边。修改一下即可通过。

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/CF2046D)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的有向图，第 $i$ 个点上有 $a_i$ 个机器人，你可以激活若干个点，一个点被激活，上面的机器人就可以沿着图上的边走到其他节点并激活这些点，求激活全部点最少要手动激活多少个点。
>
> 数据范围：$n\le 200,m\le 800$。

**思路分析**

首先强联通分量肯定可以缩点，转成 DAG 问题。

这种图上最优代价的问题肯定考虑网络流，最大流很显然无法描述本题模型，因此需要费用流。

首先我们要把每个点拆成 $(l_i,r_i)$ 两份并且钦定 $l_i\to r_i$ 必须经过。

对于 DAG 上的边，直接连 $r_u\to l_v$，我们需要判断的是每个点是否需要手动激活，以及如何在这个点上创造 $a_i$ 个机器人。

那么再建虚拟点 $x_i$，$x_i\to l_i$ 连容量为 $1$ 费用为 $1$ 的边表示手动激活，然后连 $x_i\to r_i$ 容量为 $\infty$ 的边，$s\to x_i$ 连容量为 $a_i$ 的边即可手动控制容量。

钦定 $l_i\to r_i$ 必须经过可以直接跑最小费用可行流，但一种好写的方法是把这条边的权值赋成 $-K$，其中 $K$ 是充分大的数，这样就能实现双关键字比较费用。

时间复杂度 $\mathcal O(n^3m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace F {
const int MAXV=605,MAXE=1e4+5,inf=1e9;
struct Edge { int v,e,f,w; } G[MAXE];
int S,T,ec=1,hd[MAXV],dis[MAXV],pre[MAXV];
bool inq[MAXV];
void init() { ec=1,memset(hd,0,sizeof(hd)); }
void adde(int u,int v,int f,int w) { G[++ec]={v,hd[u],f,w},hd[u]=ec; }
void link(int u,int v,int f,int w) { adde(u,v,f,w),adde(v,u,0,-w); }
bool SPFA() {
	memset(dis,0x3f,sizeof(dis));
	memset(pre,0,sizeof(pre));
	memset(inq,false,sizeof(inq));
	queue <int> Q; Q.push(S),inq[S]=true,dis[S]=0;
	while(Q.size()) {
		int u=Q.front(); Q.pop(),inq[u]=false;
		for(int i=hd[u],v;i;i=G[i].e) if(G[i].f&&dis[v=G[i].v]>dis[u]+G[i].w) {
			dis[v]=dis[u]+G[i].w,pre[v]=i;
			if(!inq[v]) Q.push(v),inq[v]=true;
		}
	}
	return pre[T];
}
array<int,2> ssp() {
	int f=0,c=0;
	while(SPFA()) {
		int g=inf;
		for(int u=T;u!=S;u=G[pre[u]^1].v) g=min(g,G[pre[u]].f);
		f+=g,c+=g*dis[T];
		for(int u=T;u!=S;u=G[pre[u]^1].v) G[pre[u]].f-=g,G[pre[u]^1].f+=g;
	}
	return {f,c};
}
}
const int MAXN=205,inf=1e9;
int n,m,low[MAXN],dfn[MAXN],dcnt,stk[MAXN],tp,bl[MAXN],scnt;
bool ins[MAXN];
int a[MAXN],su[MAXN];
vector <int> G[MAXN];
void tarjan(int u) {
	low[u]=dfn[u]=++dcnt,stk[++tp]=u,ins[u]=true;
	for(int v:G[u]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		++scnt;
		while(ins[u]) bl[stk[tp]]=scnt,ins[stk[tp--]]=false;
	}
}
const int V=1000;
void solve() {
	scanf("%d%d",&n,&m),F::init();
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1,u,v;i<=m;++i) cin>>u>>v,G[u].push_back(v);
	for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;++i) {
		su[bl[i]]+=a[i];
	}
	int s=F::S=3*scnt+1,t=F::T=3*scnt+2;
	auto L=[&](int x) { return x+scnt; };
	auto R=[&](int x) { return x+2*scnt; };
	for(int i=1;i<=scnt;++i) {
		if(su[i]) {
			F::link(s,i,su[i],0);
			F::link(i,L(i),1,1);
			F::link(i,R(i),inf,0);
		}
		F::link(L(i),R(i),1,-V);
		F::link(L(i),R(i),inf,0);
		F::link(R(i),t,inf,0);
	}
	for(int u=1;u<=n;++u) for(int v:G[u]) if(bl[u]^bl[v]) F::link(R(bl[u]),L(bl[v]),inf,0);
	int z=F::ssp()[1]+V*scnt;
	printf("%d\n",z<=scnt?z:-1);
	for(int i=1;i<=n;++i) a[i]=su[i]=stk[i]=bl[i]=low[i]=dfn[i]=ins[i]=0,G[i].clear();
	scnt=dcnt=tp=0;
}
signed main() {
	int _; scanf("%d",&_);
	while(_--) solve();
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

>有 $n$ 个仓库，每个仓库中有 $a_i$ 个机器人。你可以在最开始激活若干个仓库，这会使得其中的所有机器人被激活。被激活的机器人可以沿有向边移动，去激活沿途的仓库。问最初最少激活多少个仓库才能让所有仓库都被激活。

如果一个强连通分量内有一个仓库被激活了，则这等同于强连通分量的所有仓库都被激活了。于是可以缩点。强连通分量的点权为其中各个仓库的点权之和。

**将题目转写为最大化每个点被其它仓库经过的获益和**。记一个仓库 $i$ 是被其它仓库激活的获益为 $b_i$。具体地，如果 $a_i=0$，那么 $i$ 就必须被经过，所以可以考虑令 $b_i = +\infty$。否则，$i$ 就可以不用被手动激活了，代价 $-1$，所以令 $b_i = 1$。本贡献可以拆成当 $i$ 第一次被经过时，收益为 $b_i$，否则收益为 $0$。

于是就可以建图了：把每个点 $i$ 拆成入点 $\text{in}_i$ 以及出点 $\text{out}_i$，连接这几类边：

$(S,\text{out}_i,a_i,0)$：只能有 $a_i$ 个路径以 $i$ 为端点。

$(T,\text{out}_i,+\infty,0)$：结束路径。

$(\text{out}_u,\text{in}_v,+\infty,0)$：经过有向边。

$(\text{in}_i,\text{out}_i,1,b_i)$：首次有 $b_i$ 的获益。

$(\text{in}_i,\text{out}_i,+\infty,0)$ ：其余情况经过 $i$ 点没有获益。

求最大费用可行流即可。无解当且仅当存在一个 $i$ 满足 $b_i = +\infty$，有 $(\text{in}_i,\text{out}_i,1,b_i)$ 无流量。拿 $\sum b_i$ 减去最大费用即可。

由于流量至多有 $n$，每次寻找的复杂度为 $O(nm)$，所以最坏时间复杂度为 $O(n^2m)$。

---

