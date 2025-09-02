# キャッシュ戦略

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2011/tasks/utpc2011_8



# 题解

## 作者：My_Youth (赞：3)

[题目链接](https://www.luogu.com.cn/problem/AT_utpc2011_8)

机翻多少有点生草，不如重新描述一遍。总共有 $m$ 个盒子，给定 $n$ 种 $k$ 个小球，依次放入盒子中，求最小的花费。花费定义为对于第 $i$ 个小球：

- 如果已经有盒子放有这种小球，则代价为 $0$。
- 如果没有盒子有这种小球，则花费 $w_{a_i}$ 的代价找一个盒子放下，如果选的这个盒子里有球，则拿出之前放的球。

首先连续插入同一种小球的情况是平凡的，所以可以在读入的时候把连续颜色段缩成一个。

记同一种小球当前插入时间为 $s$，下一次插入时间为 $t$，那么实际决策只有两种：

- 无论在 $[s,t)$ 的哪个时刻取出小球，对答案的贡献都是相同的，所以不妨钦定放入后立即取出，即 $s$ 放入，$s + 1$ 拿出，代价为 $w_{a_i}$。
- 一直放在盒子中直到下一次插入，这样下一次插入代价为 $0$。

首先我们假设每个小球都用第一种决策，然后再看怎样尽可能多的选决策二替代决策一。

考虑费用流。以下记当前位置为 $i$ ，对于在 $i$ 的这种小球，上一次出现的位置为 $pre_i$，源点为 $s$，汇点为 $t$。

- 对于第一种决策，我们连 $i \to i + 1$，费用为 $0$，流量为 $\text{INF}$ 即没有节省代价，放入 $i$ 的小球后在 $i + 1$ 接着拿出。
- 对于第二种决策，我们连 $pre_i + 1 \to i$ 表示上一次放入后不在 $pre_i + 1$ 拿出，而是一直放置到 $i$ 这个位置，费用为 $- w_{a_i}$ 表示能省下 $w_{a_i}$，流量自然为 $1$。
- 最后连 $s \to 1$，$k \to t$。限定 $s \to 1$ 的流量为 $m-1$。

为什么这样限定流量呢？考虑这里流量的含义是盒子被使用的状况。因为我们要保证始终有一个盒子可以让我们进行决策一的瞬间放入拿出，所以我们同一时刻最多只能有 $m - 1$ 个盒子存着之前的小球。

对于上面一串的建边，当然还有一张感性一些的图。

![7B36XFY_YGEJ5UZNWSF_V54.png](https://s2.loli.net/2023/03/16/K34Va5zgvSDGhjT.png)

黑色代表决策一，彩色代表可以选择的决策二，我们在一个时刻不能同时占用超过 $m-1$ 个盒子，使得不能操作决策一。

时间复杂度 $\mathcal O(K M (N + K))$，由于 $M$ 很小，上来就很限制流量，所以远远达不到这个上界。

这个题也算得上是上古题了，[官方题解](https://www.utpc.jp/2011/slides/cache.pdf)给的十分简略模糊，再加上 AtCoder 上这个题的评测还写的有点锅，所以有很多奇怪的问题。首先是最后输出答案必须要加一个换行，不然会判定收不到答案一直时间超限。还有就是要开 $\text{int}$，笔者~~因为代码丑陋~~不用 $\text{int}$ 也会超时。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	return s*w;
}

namespace LgxTpre
{
	static const int MAX=100010;
	static const int INF=2007070707;
	static const int mod=998244353;
	
	int m,n,k,x;
	int sum,con;
	int w[MAX],a[MAX],lst[MAX];
	
	struct edge
	{
		int nex,to,val,flow;
	}e[MAX<<1];
	int head[MAX],cnt=1;
	inline void add(int x,int y,int val,int flow)
	{
		e[++cnt].nex=head[x],head[x]=cnt,e[cnt].to=y,e[cnt].val=val,e[cnt].flow=flow;
		e[++cnt].nex=head[y],head[y]=cnt,e[cnt].to=x,e[cnt].val=-val,e[cnt].flow=0;
		return;
	}
	
	int s,t;
	int incf[MAX],dis[MAX],vis[MAX],pre[MAX]; 	
	int maxflow,mincost;
	queue<int> q;
	inline bool spfa()
	{
		for(int i=s;i<=t;++i) vis[i]=0,dis[i]=INF;
		q.push(s),vis[s]=1,dis[s]=0,incf[s]=INF;
		while(!q.empty())
		{
			int now=q.front(); q.pop();
			vis[now]=0;
			for(int i=head[now];i;i=e[i].nex)
			{
				int to=e[i].to;
				if(!e[i].flow) continue;
				if(dis[to]>dis[now]+e[i].val)
				{
					dis[to]=dis[now]+e[i].val;
					incf[to]=min(e[i].flow,incf[now]);
					pre[to]=i;
					if(!vis[to]) vis[to]=1,q.push(to);
				}
			}
		}
		return dis[t]!=INF;
	}
	inline void Augment()
	{
		while(spfa())
		{
			int now=t;
			maxflow+=incf[t];
			mincost+=incf[t]*dis[t];
			while(now!=s)
			{
				int i=pre[now];
				e[i].flow-=incf[t];
				e[i^1].flow+=incf[t];
				now=e[i^1].to;
			}
		}
		return;
	}

	inline void lmy_forever()
	{
		m=read(),n=read(),k=read();
		for(int i=1;i<=n;++i) w[i]=read();
		for(int i=1;i<=k;++i) {x=read(); if(a[con]!=x) a[++con]=x;}
		k=con,s=0,t=k+1;
		for(int i=1;i<=k;++i)
		{
			if(i!=k) add(i,i+1,0,INF);
			if(lst[a[i]]) add(lst[a[i]]+1,i,-w[a[i]],1);
			lst[a[i]]=i;
			sum+=w[a[i]];
		}
		add(s,1,0,m-1),add(k,t,0,INF);
		Augment();
		printf("%d\n",mincost+sum);
		return;
	}
}

signed main()
{
	LgxTpre::lmy_forever();
	return (0-0);
}
```

---

## 作者：Eraine (赞：1)

来源：utpc2011  
编号：AT_utpc2011_8  
tag：网络流建图  
难度：紫

似乎好久没写题解了呢。

本文重点放在讲解为何是连边 $x-1$。

这是一个最优化问题。在原序列扫描的时候，dp 状态非常之多，要同时维护 $m$ 个袋子的信息，所以不可行，随即考虑网络流。

对于两个相同且相邻的 $a_i$，可以看做是一个段，因为后面显然是直接继承前面的最优，代价为 $0$。这一步可以将序列强化成相邻两个元素不相等的情况。

显然结构是线性扫描。考虑如何建边。由于结构是线性扫描，只要考虑一个点从下一个点袋子信息的变化即可。不难想到由 $m=1$ 的情况依次推到 $m=M$ 的情况，所以求图上的费用流相当于求相对于 $m=1$ 的代价所能省下的钱。可以建出 $(i,i+1,M-1,0)$ 的边表示不为了下一个颜色而保留位置的情况。

问题在于为了下一个颜色而保留位置的情况。注意到从 $x\to x+1$ 的转移上这些袋子中恰好存在一个下一个接受的元素是 $x+1$。也就是必须 **强制** 钦定某个转移是到 $x+1$ 的。若边建成 $pre_{a_x}\to x$ 且总流量若为 $M$ 则不能保证必然存在一个 $p=x+1$，总流量若为 $M-1$ 则如某些状态 ```1 2 1 2 ``` 会漏算掉某一个贡献，这是由于第一个 ```1``` 必须强制流到第二个 ```1```，而在 $2\to 3$ 时此时剩余的一个袋子可以让 $2$ 保留到 $4$，但是原图中并不能从 $3$ 流向 $2$。建成 $pre_{a_x}\to x-1$ 则发现 $x-1\to x$ 的边恰好可以被没有计入真正流量的第 $1$ 条流流过。也就是，$x\to x+1$ 所有流的实际意义是有若干 $(\lt m)$ 个袋子是跨过 $i+1$ 为更后面同颜色元素省钱， 剩下的流有一条是 **恰好** 为 $i+1$ 保留的一个袋子，其他就是不需要留空间给后续元素的袋子。即连边 $(pre_{a_x},x-1,1,-w_{a_x})$。

[submission](https://atcoder.jp/contests/utpc2011/submissions/61989457)

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：Echoternity (赞：1)

https://atcoder.jp/contests/utpc2011/tasks/utpc2011_8

形式化题意：有 $m$ 个盒子和 $n$ 个小球，一共 $k$ 次操作 $a_i$，表示将第 $a_i$ 个小球放入盒子中，并产生 $w_{a_i}$ 的代价。如果盒子满了，就必须从某一个盒子中拿出另一个小球并放入 $a_i$，总之，必须保证操作 $i$ 执行结束后，盒子中至少存在 $1$ 个 $a_i$ 小球。

数据范围：$1\leq m\leq 10,1\leq n,k\leq 10^4,1\leq a_i\leq n$

---

~~不~~容易发现这是一道费用流。

正向思考是一个艰难的问题，所以我们假定所有的球都需要被替换（产生代价），然后通过负费用算出最多能省多少。

如果对于一个小球 $i$，我们要求其保留至下一次放入，就可以节省 $w_i$ 的代价，但是在 $[s,t)$ 操作内就会消耗一个盒子。这种方式我们在同一时间一共可以做 $m-1$ 这样的操作，也就是在同一个时间节省 $m-1$ 种代价。

考虑 $\mathrm{dp}$，但是具有后效性，反向 $\mathrm{dp}$ 肯定也不行。贪心就更不用想了。

以盒子数为流量，代价为费用建立费用流。

我们钦定每一次都会产生代价，也就是每一次都要放进去。但我们有 $m-1$ 次机会可以使当前操作不产生代价，但在同一时刻也只有 $m-1$ 次。而如果我们让某一次操作不产生代价，就会在 $[lst_i,i]$ 内占用一个盒子。其中 $lst_i$ 表示第 $i$ 个小球上一次放入的时间。

所以，对于每一次操作，我们有 $2$ 种选择：

1. 放入，并产生 $w_{a_i}$ 的代价；
2. 从上一次放入后就不移动，并让其延续到当前操作，不产生代价。

容易发现，第 $2$ 个选择实际上就是要求我们在 $(lst_i,i]$ 内不执行第 $1$ 个选择。

所以我们考虑按以下方式建图：

* 建立 $1\sim k$ 的操作结点，以及源汇点 $s,t$；
* 从 $s$ 到 $1$ 连边，流量 $m-1$，费用 $0$；
* 从 $k$ 到 $t$ 连边，流量 $\infty$，费用 $0$；
* 从 $i$ 到 $i+1$ 连边，流量 $\infty$，费用 $0$；
* 从 $lst_i+1$ 到 $i$ 连边，流量 $1$，费用 $-w_{a_i}$。

答案是 $\displaystyle\sum_{i=1}^{k}w_{a_i}+ret$，其中 $ret$ 表示最小费用。

因为对于每一个时刻，我们都至少要留出一个盒子给当前操作的小球，所以我们能够维护保持的小球至多有 $m-1$ 个，总流量为 $m-1$。而至于为什么是从 $lst_i+1$，如果这个小球在下一次放入前被拿出来了，那无论是在 $\forall i\in(lst_i,i)$ 被拿出对结果的影响是一样的，我们都必须要再次放入，所以我们钦定在 $(lst_i,i]$ 内不被拿出，就会产生 $-w_{a_i}$ 的代价。而在 $lst_i$ 时，我们是必须会执行第一个选择的。

附上[官方题解](https://www.utpc.jp/2011/slides/cache.pdf)。以及感谢与我一同探究的 [$\text{@LgxTpre}$](https://www.luogu.com.cn/user/66709)。

最后整几个注意事项：

* $\text{AT}$ 上古题，记得答案最后换行。
* 不建议开 `long long`，好像会超时，这个数据范围 `int` 是可以过的。
* 请注意，如果存在 $lst_i=i-1$ 的情况，就会使得图中出现一个负环，然后要么答案会变小，要么会死循环。所以我们在建图之前要进行一次去重处理，把所有 $lst_i=i-1$ 的情况剔除掉。

``` c++
// ----- Eternally question-----
// Problem: H - キャッシュ戦略
// Contest: AtCoder - UTPC 2011
// URL: https://atcoder.jp/contests/utpc2011/tasks/utpc2011_8
// Memory Limit: 292 MB
// Time Limit: 2000 ms
// Written by: Eternity
// Time: 2023-03-16 14:37:28
// ----- Endless solution-------

#include<bits/stdc++.h>
#define re register
const int MAXM=12,MAXN=1e4+10,MAXK=1e4+10,MAXV=1e4+10,MAXE=1e5+10;
const int INF=0x3f3f3f3f;
int M,N,K,S,T;
int Wgt[MAXN];
struct Net
{ int next,to,val,cost; }Edge[MAXE<<1];
int Head[MAXV],Cur[MAXV],Total=1;
inline void addEdge(int u,int v,int w,int c)
{
    Edge[++Total]=(Net){Head[u],v,w,c};Head[u]=Total;
    Edge[++Total]=(Net){Head[v],u,0,-c};Head[v]=Total;
}
int Dist[MAXV],ret;
bool Vis[MAXV];
inline bool Spfa(int s,int t)
{
	for(int i=S;i<=T;++i) Dist[i]=INF;
	for(int i=S;i<=T;++i) Cur[i]=Head[i];
    std::queue<int>Q;
    Q.push(s),Dist[s]=0,Vis[s]=1;
    while(!Q.empty())
    {
        int u=Q.front();Q.pop();
        Vis[u]=0;
        for(int e=Head[u];e;e=Edge[e].next)
        {
            int v=Edge[e].to;
            if(Edge[e].val&&Dist[v]>Dist[u]+Edge[e].cost)
            {
                Dist[v]=Dist[u]+Edge[e].cost;
            	if(!Vis[v]) Q.push(v),Vis[v]=1;
            }
        }
    }
    return Dist[t]!=INF;
}
int Dfs(int x,int inf)
{
    if(x==T) return inf;
    Vis[x]=1;
    int flow=0;
    for(int e=Cur[x],v;e&&flow<inf;e=Edge[e].next)
    {
        Cur[x]=e,v=Edge[e].to;
        if(!Vis[v]&&Edge[e].val&&Dist[v]==Dist[x]+Edge[e].cost)
        {
            int k=Dfs(v,std::min(Edge[e].val,inf-flow));
            if(k)
            {
                ret+=k*Edge[e].cost;
                Edge[e].val-=k,Edge[e^1].val+=k,flow+=k;
            }
        }
    }
    Vis[x]=0;
    return flow;
}
inline int SSP()
{
    int res=0,flow;
    while(Spfa(S,T)) while(flow=Dfs(S,INF)) res+=flow;
    return res;
}
int Sum,Lst[MAXN],Id[MAXN],Idx;
signed main()
{
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	scanf("%d%d%d",&M,&N,&K);S=0;
	for(int i=1;i<=N;++i) scanf("%d",&Wgt[i]);
	std::memset(Lst,-1,sizeof(Lst));
	for(int i=1,x;i<=K;++i)
	{
		scanf("%d",&x);
		if(Id[Idx]!=x) Id[++Idx]=x;
	}
	K=Idx,T=Idx+1;
	for(int i=1;i<=K;++i)
	{
		if(~Lst[Id[i]]) addEdge(Lst[Id[i]]+1,i,1,-Wgt[Id[i]]);
		Lst[Id[i]]=i,Sum+=Wgt[Id[i]];
	}
	addEdge(S,1,M-1,0);
	for(int i=1;i<=K;++i) addEdge(i,i+1,INF,0);
	SSP();
	printf("%d\n",Sum+ret);
	return 0;
}
/*

*/
```

---

