# [ARC161F] Everywhere is Sparser than Whole (Judge)

## 题目描述

我们将非空顶点集合的简单无向图的**密度**定义为 $ \displaystyle\frac{(\text{边数})}{(\text{顶点数})} $。

给定正整数 $ N,\ D $，以及一个有 $ N $ 个顶点、$ DN $ 条边的简单无向图 $ G $。$ G $ 的顶点编号为 $ 1 $ 到 $ N $，第 $ i $ 条边连接顶点 $ A_i $ 和顶点 $ B_i $。请判断 $ G $ 是否满足以下条件。

**条件：** 设 $ G $ 的顶点集合为 $ V $。对于 $ V $ 的任意非空**真**子集 $ X $，由 $ X $ 所诱导的 $ G $ 的子图的密度严格小于 $ D $。

诱导子图的定义如下：

对于图 $ G $ 的顶点子集 $ X $，由 $ X $ 所诱导的 $ G $ 的**子图**，是指“顶点集合为 $ X $，边集合为『$ G $ 中连接 $ X $ 内任意两点的所有边』的图”。注意，上述条件只考虑既不是空集也不是全集的顶点子集。

## 说明/提示

### 限制条件

- $ T\geq 1 $
- $ N\geq 1 $
- $ D\geq 1 $
- 所有测试用例中 $ DN $ 的总和不超过 $ 5\times 10^4 $。
- $ 1\leq A_i < B_i \leq N\ (1\leq i\leq DN) $
- $ (A_i, B_i) \neq (A_j, B_j)\ (1\leq i < j\leq DN) $

### 样例解释 1

- 第 1 个测试用例与[问题 D](./arc161_d)的输出样例 1 相同，满足条件。
- 对于第 2 个测试用例，顶点集合 $ \{1, 2, 3, 4\} $ 的非空真子集 $ \{1, 2, 3\} $ 所诱导的子图的边集合为 $ \{(1, 2), (1, 3), (2, 3)\} $，其密度为 $ \displaystyle\frac{3}{3}=1=D $。因此，该图不满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3 1
1 2
1 3
2 3
4 1
1 2
1 3
2 3
3 4```

### 输出

```
Yes
No```

# 题解

## 作者：Alex_Wei (赞：10)

### [[ARC161F] Everywhere is Sparser than Whole (Judge)](https://www.luogu.com.cn/problem/AT_arc161_f)

首先尝试描述导出子图，若一条边被选中，则其两个端点必须属于导出子图。这启发我们构建有向二分图 $G'$，原图每条边对应 $G'$ 的一个左部点，每个点对应 $G'$ 的一个右部点，每个左部点向对应边的两端对应的右部点连边，那么原图的导出子图一定是新图的闭合子图。

考虑 $E/V\geq D$ 的限制，将其写为 $E - VD\geq 0$，相当于：每选择一条边有 $1$ 的贡献，每选择一个点有 $D$ 的代价。若 $G'$ 的最大权闭合子图权值大于 $0$，说明原图存在密度大于 $D$ 的子图。

问题在于，我们不能直接判断原图是否存在密度恰等于 $D$ 的子图：原图和空图两个平凡导出子图均对应 $G'$ 上权值为 $0$ 的闭合子图，所以若 $G'$ 最大权闭合子图权值为 $0$，不能说明原图不符合条件。

考虑求最大权闭合子图的网络流算法：默认选择所有边，不选择所有点。源点向每个左部点连容量为 $1$ 的边，左部点向对应的两个右部点连容量为 $+\infty$ 的边，每个右部点向汇点连容量为 $D$ 的边，用割表示一组方案：左边的边被割掉表示不选择对应的边，右边的边被割掉表示选择对应的点，不存在 $S\to T$ 的通路表示不存在一条被选择的边，它的任意一端不在闭合子图内。

设 $M = ND$。

当流量小于 $M$ 时，说明最大权闭合子图权值大于 $0$，即存在 $E - VD > 0$ 的子图，原图不符合条件。

当流量等于 $M$ 时，左边所有边剩余容量为 $0$，右边所有边剩余容量为 $0$，从 $S$ 或 $T$ 开始在残量网络上 BFS 均只能得到平凡最小割。

尝试钦定第一条边选或者不选。

- 如果钦定选第一条边，相当于钦定不割掉这条边，即将 $S\to L_1$ 的容量设为无穷大。此时只要找到一组割掉左边任意一条边的最小割，就能说明原图不符合条件。我们断言：原图不符合条件当且仅当存在 $S$ 在残量网络上不可达的左部点 $L_i$。
  - 充分性：将 $S$ 在残量网络上可达的点集作为最小割的左部点集，其余作为右部点集，则 $S\to L_i$ 的边被割掉。
  - 必要性：考虑任意割掉 $S\to L_i$ 的最小割，这说明存在一种划分点集的方案，使得左部点集包含 $S$，右部点集包含 $L_i$，且中间所有边均不在残量网络上（最小割割边必然满流），这说明 $S$ 在残量网络上不可达 $L_i$。
- 如果钦定不选第一条边，相当于钦定割掉这条边，即将 $S\to L_1$ 的容量设为 $0$。可以证明新图的最小割（流量为 $M - 1$）对应原图包含割边 $S\to L_1$ 的最小割（流量为 $M$），因为存在一种方式使得 $S\to L_1$ 属于最小割的边集。换言之，新图最小割一定为 $M - 1$：新图 $S\to L_*$ 的总流量为 $M - 1$，且原图存在流量为 $M$ 的最小割。此时只要找到一组割掉右边任意一条边的最小割，就能说明原图不符合条件。类似地，原图不符合条件当且仅当存在右部点 $R_i$ 在残量网络上不可达 $T$。

当最小割流量小于 $M$ 时，不存在一个割使得全割左边或全割右边，所以不需要特殊判断最小割小于 $M$，即最大权闭合子图权值大于 $0$ 的情况，而直接使用最小割等于 $M$ 的算法即可。

时间复杂度 $\mathcal{O}(M ^ {1.5})$，其中 $M = ND$。[代码](https://atcoder.jp/contests/arc161/submissions/41837135)。

若不存在密度大于 $D$ 的子图，存在 $\mathcal{O}(M)$ 检查是否存在密度为 $D$ 的子图的算法（官方题解）：注意到可以根据网络流结果（存在完美匹配）给每个点分配恰好 $D$ 条以其为一端的边，且一条边恰被分配到一个点。给每条边定向，从被分配的点指向另外一个点，合法当且仅当原图强连通。证明略。

---

## 作者：honglan0301 (赞：6)

## 题目分析

感觉不保证时间复杂度一定正确。前置知识：最大密度子图直接转最小割的做法（[见此处“方法二”](https://blog.csdn.net/qq_45735851/article/details/113964394)）。以下默认我们了解它并知道其中的原理。

记最小割为 $f$。首先是否存在密度 $>D$ 的子图是很好判断的，只需把分数规划时的 $g$ 设为 $D$ 之后看 $|E'|-D|V'|$ 的最大值（$nm-f$）是否 $>0$ 即可。

于是下面只需讨论（不存在密度 $>D$ 的子图时）如何判断是否存在密度 $=D$ 的非全选的子图（其不能用相同方法直接做的原因是无法排除全选而使密度 $=D$ 的情况）。

我们考虑最小割做法的本质，发现其实是把 $|E'|$ 拆成了 $\sum deg_i$ 和 $E[v_1,v_2]$ 这两部分，而我们的要求其实等价于要让 $E[v_1,v_2]>0$，放到最小割中就是要让原图中存在被割掉的边。于是把原图中的边容量由 $1$ 改为 $1-eps$ 即可，证明如下：

1. 因为原先有 $\sum deg_i-E[v_1,v_2]=2D|V'|$ 的方案（全选，此时 $nm-f=0$），故若这样的方案中存在至少一种使得 $E[v_1,v_2]>0$，则新图中一定有 $nm-f'=E[v_1,v_2]\times eps>0$。

2. 因为 $eps$ 足够小，故不会使得 $\sum deg_i-E[v_1,v_2](1-eps)>2D|V'|$ 但 $\sum deg_i-E[v_1,v_2]<2D|V'|$ 的情况发生，即新图中最小割所对应的子图密度一定还 $=D$。

故存在满足条件的子图等价于 $nm-f'>0$，结束了。注意要特判不连通时答案为 $\text{No}$，因为多个连通块中至少有一个密度 $\geq D$。

## 代码

```cpp
/*
  author: PEKKA_l  
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define int __int128
#define ll long long
#define INF (10000000000000ll)

ll T,n,d,m,u,v;
int s,t,du[50005],vis[50005],cntd,head[50005],cnt,MX=1e22;

struct edge
{
	int son,val,next;
}edge[400005];
void adde(int x,int y,int z) {edge[++cnt]={y,z,head[x]}; head[x]=cnt;}

queue <int> Q;
int dep[50005],nowb[50005],maxflow;

/*
	网络流板子
*/

bool bfs2()
{
	for(int i=1;i<=n;i++) vis[i]=0; Q.push(1); vis[1]=1; cntd=1;
	while(!Q.empty())
	{
		int nr=Q.front(); Q.pop();
		for(int i=head[nr];i>0;i=edge[i].next)
		{
			if(!vis[edge[i].son]) {vis[edge[i].son]=1; cntd++; Q.push(edge[i].son);}
		}
	}
	return cntd==n;
}

signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>d; m=n*d; for(int i=1;i<=n;i++) du[i]=0,head[i]=0; 
		s=0,t=n+1; head[s]=head[t]=0; cnt=1;
		for(int i=1;i<=m;i++)
		{
			cin>>u>>v; du[u]++; du[v]++; adde(u,v,INF-1); adde(v,u,INF-1);
		}
		if(!bfs2()) {cout<<"No"<<endl; continue;}
		for(int i=1;i<=n;i++)
		{
			adde(s,i,INF*m); adde(i,s,0);
			adde(i,t,INF*(m+2*d-du[i])); adde(t,i,0);
		}
		dinic(); if(((__int128)n)*m*INF>maxflow) cout<<"No"<<endl; else cout<<"Yes"<<endl;
	}
}
```


---

## 作者：Purslane (赞：4)

# Solution

如果将条件弱化为 $|E'| \le D|V'|$，就是经典的[最大密度子图问题](https://blog.csdn.net/qq_45735851/article/details/113964394)。计算出 $|E'|-D|V'|$ 的最大值，判断它是否 $\le 0$。

遗憾的是，如果这个问题成立，那么它必然 $=0$（因为全图就能使它取等，空图也能让它取等）。我们需要知道，是否存在另一个子图满足其密度为 $D$。

这个问题显然就变为：最小割是否唯一。即，是否存在一组最小割，不是割掉源点相邻的所有边，或者割掉汇点相邻的所有边。

一条边 $(u,v)$ 是否能在最小割中其实有一个充要条件条件（这是我自己想出来的……应该是对的吧）：

1. 这条边满流。
2. 残量网络上不存在 $u \to v$ 的增广路。

在残量网络上缩点之后，性质 $2$ 显然等价于 $u$ 和 $v$ 不在同一个强联通分量内。而且发现，如果有一条边不在同一个强联通分量中，它就一定可以是最小割边。

首先判掉不连通的情况，根据抽屉原理，这时候一定有某个导出子图密度大于等于 $D$。这样只需要某一条中间的边能被割掉，就说明存在一个导出子图密度大于等于 $D$。$\rm tarjan$ 缩点即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e4+10,MAXM=MAXN*100;
int T,n,d,m,k,s,t,tot=1,deg[MAXN],fa[MAXN],dis[MAXN],hd[MAXN],cur[MAXN];
struct Edge {int to,nxt,f;}edge[MAXM];
int dfn[MAXN],low[MAXN],cs,dtot,in[MAXN],col[MAXN];
stack<int> st;
void tarjan(int u) {
	dfn[u]=low[u]=++dtot,in[u]=1,st.push(u);
	for(int i=hd[u];i;i=edge[i].nxt) {
		int v=edge[i].to,f=edge[i].f;
		if(!f) continue ;
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(in[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		++cs;
		while(1) {
			int v=st.top(); st.pop();
			in[v]=0,col[v]=cs;
			if(u==v) break ;
		}
	}
	return ;
}
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
void init(void) {
	tot=1,dtot=cs=0;
	ffor(i,0,n+1) deg[i]=hd[i]=cur[i]=dfn[i]=low[i]=in[i]=0;
	return ;
}
int check(void) {
	ffor(u,0,n+1) if(!dfn[u]) tarjan(u);
	ffor(u,1,n) for(int i=hd[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(v>n||v<1) continue ;
		if(i%2==0&&col[u]!=col[v]&&edge[i].f==0) return 0;
	}
	return 1;
}
void add_edge(int u,int v,int w) {
	edge[++tot]={v,hd[u],w},hd[u]=tot;
	edge[++tot]={u,hd[v],0},hd[v]=tot;
	return ;	
}
int bfs(void) {
	ffor(i,0,n+1) dis[i]=-1;
	queue<int> q;
	dis[s]=0,q.push(s);
	while(!q.empty()) {
		int u=q.front();
		q.pop(),cur[u]=hd[u];
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,f=edge[i].f;
			if(!f||dis[to]!=-1) continue ;
			dis[to]=dis[u]+1,q.push(to);
		}
	}
	return dis[t]!=-1;
}
int dinic(int u,int mx) {
	if(u==t) return mx;	
	int ans=0;
	for(int i=cur[u];i;i=edge[i].nxt,cur[u]=i) {
		int to=edge[i].to,f=edge[i].f;
		if(!f||dis[to]!=dis[u]+1) continue ;
		int tmp=dinic(to,min(mx,f));
		if(tmp) {
			edge[i].f-=tmp,edge[i^1].f+=tmp,ans+=tmp,mx-=tmp;
			if(!mx) break ;	
		}
		else dis[to]=-1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>d,init(),s=0,t=n+1,k=n+1;
		ffor(i,1,n) fa[i]=i;
		ffor(i,1,n*d) {
			int u,v;
			cin>>u>>v;
			add_edge(v,u,1),add_edge(u,v,1),deg[u]++,deg[v]++;
			fa[find(u)]=find(v);
		}
		int cnt=0;
		ffor(i,1,n) cnt+=(i==find(i));
		if(cnt!=1) {cout<<"No\n";continue ;}
		ffor(i,1,n) add_edge(s,i,2*d-deg[i]+1000000),add_edge(i,t,1000000);
		int ans=0,tmp=0;
		while(bfs()) while(tmp=dinic(s,10000000)) ans+=tmp;
		ans-=1000000*n;
		if(ans>0) cout<<"No\n";
		else if(check()) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：Little09 (赞：4)

来个官方题解做法。

首先假设如果判定的是密度 $>D$ 怎么做。考虑如果有一个导出子图的密度 $>D$，那么考虑这个导出子图的补集（同时取边的补集和点的补集）一定满足密度 $<D$，而这个补集其实就是先选一个非空点集 $S$，再选所有至少一个端点在 $S$ 的边。

考虑如果不存在这样的点集 $S$，也就是对于每个点集 $S$，对应的边集（至少一个端点在点集里的边）大小都满足 $\ge D\cdot |S|$。看起来很 Hall 定理，那我们构造一张二分图进行多重匹配。一条原图上的边就是一个左部点，连向的两个右部点是在原图上连接的点，此时的完美匹配应该是一个边集满足左部点每个被选 $1$ 次，右部点每个被选 $D$ 次。因此只需要源点向左部点连流量 $1$ 的边，右部点向汇点连流量 $D$ 的边跑网络流就行，复杂度是 $O((ND)^{1.5})$。

上面的过程也就是说，如果不存在完美匹配，那么一定存在密度 $>D$ 的点集。否则不存在 $>D$ 的点集，但是可能有密度 $=D$ 的点集。考虑根据刚才求出的完美匹配给图定向，使得每个点的出度恰好为 $D$。给出引理：

> 存在密度 $=D$ 的真导出子图当且仅当新定向的图不止一个强连通分量。

- 如果存在多个强连通分量，找到没有出边的强连通分量，此时这个强连通分量内部的所有边一定指向内部，所以它的密度恰好是 $D$。

- 如果存在一个真导出子图密度 $=D$，假设点集是 $S$，那么从 $S$ 出发的边一定指向内部。如果该导出子图不连通，选择一个连通的导出子图。此时一定形成了一个强连通分量，且没有出边，所以原图一定存在多个强连通分量。

因此先跑一遍 dinic 再跑一遍 tarjan 即可。复杂度是 $O((ND)^{1.5})$。

---

## 作者：Dovish (赞：2)

来一点不需要太多分析的无脑做法。

## 分析

首先，我们考虑描述一下题目的限制：如果一条边被选择了，那么相连的两个点一定会被选择。选择一条边的贡献为 $1$，选择一个点的代价为 $m$，要最大化贡献。

这个显然可以用最小割来做。

如果最终求出来的答案是正数，说明 $|E'|>m|V'|$。即密度不合法。

但是如果存在一个真非空子集的 $|E'|=m|V'|$ 怎么办？

网络流直接求出来的答案是空集或者全集，但是我们希望钦定一些边必须要割掉。

> 下文中「点」和「边」指的都是原图的点和边在网络流图上的对应的边。

考虑钦定一个「点」必须选，如果这个「点」是最终使得答案非法的构造出的子集中的一个点，那么那么新图上的最小割不会变且存在一条「边」是可行边。

每次随机找一个点，期望 $\frac nk$ 次能找到一个这样的点。其中 $k$ 是所有使得答案不合法的点集的并集的大小。

显然当 $k$ 很小的时候我们难以快速找到答案，这个时候考虑另外一个方面。

我们也可以随机钦定一条「边」必须不选，这样，我们每次就有 $\frac {n-k}{n}$ 的概率找到一个「边」使得其不是不合法构造出的子集中的一条边。此时如果存在一个「点」是最小割的可行边，则可以说明这样不合法的子集存在。

> 正确性证明：随机钦定一条「边」和一个「点」之后求出的答案的正确率为 $\frac{n-k}{n}\times \frac{k}{n}$。根据均值不等式，当 $k=n-k$ 时错误率最高，为 $\frac 14$，那么随机 $T$ 次的正确率就是 $1-(\frac 14)^T$。

把两个做法拼在一起即可，直接在残量网络上退流显然是更优的做法，但是直接重新建图跑一遍也能冲过去。

复杂度 $O(m(\sqrt m+T))$。其中 $T$ 是随机化次数，一般情况下取 $20$ 左右就差不多了。

[丑代码](https://atcoder.jp/contests/arc161/submissions/65314209)

---

## 作者：Nelofus (赞：2)

## 题解
以下所有**子图**都是**导出子图**

首先你要知道这个子图怎么整。

一个经典的刻画子图的方式是构造一个二分图，把边看成左部点，原来的点看成右部点，连边就从**原图中的边**对应的点连到**边的两个端点**对应的点。

### 密度 $>D$

整个图自己就是密度 $=D$ 的情况，判断等于不太好做，先判存在子图密度 $>D$ 的情况。如果存在这样的子图，那么记这个子图的边集是 $S_e$，点集是 $S_v$，就是 $\dfrac{|S_e|}{|S_{v}|}>D$，这看起来跟我们上面的刻画还是没有什么关系，因为上面直接流的情况是先选出一个点集 $S$ 再选出所有至少有一个端点在 $S$ 里的边的数量。

但是你考虑这个子图在原图上的补图，那就是去掉 $S_v$ 中的点，而剩下的边就是**至少有一个端点不在 $S_v$ 中**的边。如果有一个密度 $>D$ 的子图那么其补图密度一定 $<D$。而这个补图的形式很符合我们上面的刻画。

如果不存在一个密度 $>D$ 的子图，那么任意选出一个点集 $S$ 作为补图的点集，都一定至少有 $\ge D\cdot |S|$ 条边在补图里。这个显然是 Hall 定理，成立当且仅当在我们上面的二分图中跑左部点容量为 $1$，右部点容量为 $D$ 的二分图多重匹配时有完美匹配。

所以我们得出了判断是否存在密度 $>D$ 子图的方法，如果这个二分图有完美匹配，那么不存在密度 $>D$ 的子图，否则一定存在。

### 密度 $=D$

现在所有导出子图密度都 $\le D$，我们要判断是否存在一个 $=D$ 的**真子图**。那么你根据完美的结果对原图的边进行定向(一条边对其端点 $u$ 有流量则为 $u\longrightarrow v$，否则为 $v\longrightarrow u$)，这个定向的结果就是所有点的出度恰好为 $D$。给出结论：

> 一个图有密度 $=D$ 的子图当且仅当定向后强联通分量数量不唯一。

### 你说得对但是

这为啥是对的呢。

首先如果一个强联通分量是没有出边的，那么这个强联通分量一定密度为 $D$，因为所有点出度都为 $D$。

然后如果有一个真子图的密度是 $D$，那么假设它的点集是 $S$，所有与 $S$ 中的点有连接的边一定会指回 $S$ 当中。从而形成一个没有出边的强联通分量。

**注意，下面的内容因为我不熟悉，不保证正确，如有理解错的可以向我提出。**

完全不懂怎么想到这个构造咋办？

之所以会考虑这个构造，其实是因为 [官方题解](https://atcoder.jp/contests/arc161/editorial/6471) 里面提到的 [Dulmage–Mendelsohn decomposition](https://en.wikipedia.org/wiki/Dulmage%E2%80%93Mendelsohn_decomposition) 这个东西。

考虑我们找密度 $=D$ 的子图的实质，其实就是我们希望把原来的一整个完美匹配划分成若干个相互之间无关的匹配。

这个其实是和 Dulmage–Mendelsohn decomposition 的 fine decomposition 是一样的过程，都是把一个完美匹配进一步划分成若干个部分，考虑一下它是怎么做的：

1. 把图 $G$ 的所有匹配边变成一个点，放在图 $H$ 中。
2. 我们这样构造 $H$ 中的边：对于 $G$ 的每条非匹配边 $(x, y)$，从 $x$ 的匹配边连向 $y$ 的匹配边。
3. 对 $H$ 求强联通分量，每个强联通分量都是一组独立的完美匹配。

为什么这个对呢，考虑 $H$ 中的每一个简单环，其实都对应着 $G$ 中的一个 `非匹配边——匹配边——非匹配边……` 的交错环(alternating cycle)，只要把每条环中的匹配边换成全部换成下一条边，这仍然是完美匹配。

但是我们这个是容量为 $D$ 的，没法直接套上去，但是其实也差不多，还是用这种调整的想法。在边 $(u, v)$ 对应的点往 $u$ 匹配，边就是 $u\longrightarrow v$ 的，表示你要把这个匹配换给 $v$，那么 $v$ 就要换给下一个 $w$……如此一直到再有一个边把容量换给了 $u$，又重新构成一组完美匹配。

## 代码

```cpp
#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 5e4 + 10;
constexpr int inf = 0x3f3f3f3f;
class flow {
	public:
	static constexpr int N = 1e5 + 10;
	static constexpr int M = 3e5 + 10;

	struct edge {
		int v;
		int cap, flow;
	} E[M << 1];

	std::basic_string<int> G[N];

	int idx;
	int dep[N];
	int now[N];

	inline bool bfs() {
		memset(dep, 0x3f, (t + 1) * sizeof(int));
		std::queue<int> q;
		q.push(s);
		now[s] = 0, dep[s] = 0;
		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (const int &i : G[u]) {
				edge &e = E[i];
				if (e.cap > e.flow && dep[e.v] == inf) {
					dep[e.v] = dep[u] + 1;
					q.push(e.v);
					now[e.v] = 0;
					if (e.v == t)
						return true;
				}
			}
		}
		return false;
	}


	int dfs(int u, int res) {
		if (u == t || !res)
			return res;
		int k = 0, flow = 0;
		for (int i = now[u]; i < G[u].size() && res; i++) {
			now[u] = i;
			auto &edg = E[G[u][i]];
			auto &rev = E[G[u][i] ^ 1];

			if (edg.cap > edg.flow && dep[edg.v] == dep[u] + 1) {
				k = dfs(edg.v, std::min(edg.cap - edg.flow, res));
				if (!k)
					dep[edg.v] = inf;
				edg.flow += k;
				rev.flow -= k;
				flow += k;
				res -= k;
			}
		}
		return flow;
	}
	int s, t;
	void connectS(int x, int cap) {
		add(s, x, cap);
	}
	void connectT(int x, int cap) {
		add(x, t, cap);
	}
	void clear() {
		for (int i = s; i <= t; i++)
			G[i].clear();
		idx = 0;
	}
	int dinitz() {
		int flow = 0;
		while (bfs()) {
			flow += dfs(s, inf);
		}
		return flow;
	}
	inline void add(int u, int v, int cap) {
		E[idx] = {v, cap, 0};
		G[u] += idx++;
		E[idx] = {u, 0, 0};
		G[v] += idx++;
	}
} FLOW;

struct edge {
	int u, v;
} E[N];

int n, d;
int edg[N];
std::basic_string<int> G[N];
int low[N];
int dfn[N];
int SCCnu, SCC[N];
int stk[N], tt, instk[N], dfc;

void dfs(int u) {
	dfn[u] = low[u] = ++dfc;
	instk[u] = true;
	stk[++tt] = u;

	for (const int &v : G[u]) {
		if (!dfn[v]) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		} else if (instk[v]) {
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		SCCnu++;
		int tp;
		do {
			tp = stk[tt--];
			SCC[tp] = SCCnu;
			instk[tp] = false;
		} while (tp != u);
	}
}

void tarjan_clear() {
	SCCnu = dfc = 0;
	memset(instk, 0, (n + 2) * sizeof(int));
	memset(dfn, 0, (n + 2) * sizeof(int));
	tt = 0;
}

void tarjan() {
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			dfs(i);
}

void solve() {
	std::cin >> n >> d;
	int m = n * d;

	for (int i = 1; i <= n; i++)
		G[i].clear();
	for (int i = 1; i <= m; i++)
		std::cin >> E[i].u >> E[i].v;

	FLOW.s = 0, FLOW.t = m + n + 1;
	FLOW.clear();

	for (int i = 1; i <= m; i++) {
		FLOW.connectS(i, 1);
		FLOW.add(i, E[i].u + m, 1);
		edg[i] = FLOW.idx - 2;
		FLOW.add(i, E[i].v + m, 1);
	}
	for (int i = 1; i <= n; i++)
		FLOW.connectT(i + m, d);

	// 左边点权和
	int ans = FLOW.dinitz();
	if (ans != m) {
		std::cout << "No\n";
		return ;
	}
	for (int i = 1; i <= m; i++) {
		if (FLOW.E[edg[i]].flow == 1)
			std::swap(E[i].u, E[i].v);
	}
	for (int i = 1; i <= m; i++) {
		G[E[i].u] += E[i].v;
	}
	tarjan_clear();
	tarjan();
	if (SCCnu > 1) {
		std::cout << "No\n";
	} else {
		std::cout << "Yes\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：XZhuRen (赞：1)

由于导出子图的定义，考虑选了某条边就必选对应点，选了对应点就必选某条边，套路地构造一个最大权闭合子图模型，位二分图，左部为边，右部为点，一条边连接对应的两点。

考虑找不合法情况，先找 $>D$ 的，这个可以直接判断。

则转化式子 $\large{\frac{E}{V}>D}$ 为 $\large{E-VD>0}$ 即要求最大权闭合子图权值 $>0$。

若最大权闭合子图权值 $>0$，则一定不合法。

接下来判断是否有子图满足以下条件。

根据 [P4126 [AHOI2009] 最小割](https://www.luogu.com.cn/problem/P4126) 的知识，我们发现一条边必割等价于它两端分属 $S,T$ 的连通分量中。

直接应用这个模型是不行的，容易发现本图没有直接必割边。

观察发现，本图存在真子图满足 $E=VD$ 当且仅当根据割掉的点，拆分成几个不交的闭合子图。

则我们重新考虑视每一个左部点为一个 $S$，同样是经过中间部分，则对于 $S$ 的集合，要达成割必然要把连接象征点的右部点与 $T$ 割掉，也就是说**左部点和右部点同属一个强连通分量**。

如果不同属一个强连通分量，视左部点为 $S$ 的集合，使一些边断流，一定存在不割完右部点的方案。

所以最后判断是否存在三个强连通分量即可（$S,T$ 及中间的点各一个）。

Code：

```cpp
struct edge{
	int u,v,nxt;
	ll1 c;
}g[M];
int head[N],tote=1;
void ae(int u,int v,ll1 c){
	g[++tote]=(edge){u,v,head[u],c};
	head[u]=tote;
}
void Ae(int u,int v,ll1 c){ae(u,v,c),ae(v,u,0);}
int S,T,totn=0;
namespace flows{
	ll1 d[N];
	int thead[N];
	int que[N],hd,tl;
	bool bfs(){
		for(int i=0;i<=totn;i++)thead[i]=head[i],d[i]=0;
		d[S]=1;que[hd=tl=1]=S;
		int u;
		while(hd<=tl){
			u=que[hd++];
			for(int e=head[u],v;e;e=g[e].nxt){
				v=g[e].v;if(d[v]||!g[e].c)continue;
				d[v]=d[u]+1;que[++tl]=v;
			}
		}
		return d[T];
	}
	ll1 dfs(int u,ll1 F){
		if(!F||u==T)return F;
		ll1 rf=0,tmp;
		for(int e=thead[u],v;F&&e;thead[u]=e=g[e].nxt){
			v=g[e].v;if(d[v]!=d[u]+1||!g[e].c)continue;
			tmp=dfs(v,min(F,g[e].c));
			F-=tmp;rf+=tmp;
			g[e].c-=tmp,g[1^e].c+=tmp;
		}
		return rf;
	}
	ll1 dinic(){
		ll1 res=0;
		while(bfs())res+=dfs(S,inf);
		return res;
	}
}
int n,D,m;
int dfn[N],low[N];
int tdfn=0;
bool vis[N];
int stk[N],top=0;
int col[N];
int totcols=0;
//E-DV>0
int el,er;
#define V(x) (x+m)
#define E(x) (x)
void init(){
	scanf("%d%d",&n,&D);
	m=n*D;
	totn=n+m;tote=1;
	S=++totn,T=++totn;
	for(int i=1;i<=totn;i++)head[i]=0;
	for(int i=1;i<=totn;i++){
		vis[i]=0;stk[i]=col[i]=0;
		dfn[i]=low[i]=0;
	}
	top=0;tdfn=0;totcols=0;
	//直接判断割完割的这些是不是都是必需边
	el=tote+1;
	for(int i=1;i<=n;i++){
		Ae(V(i),T,D);
	}
	er=tote;
	int u,v;
	for(int i=1;i<=m;i++){
		Ae(S,E(i),1);
		scanf("%d%d",&u,&v);
		Ae(E(i),V(u),inf);
		Ae(E(i),V(v),inf);//最大权闭合子图模型
	}
}
void Tarjan(int u){
	dfn[u]=low[u]=++tdfn;
	vis[u]=1;
	stk[++top]=u;
	for(int e=head[u],v;e;e=g[e].nxt){
		if(!g[e].c)continue;
		v=g[e].v;
		if(!vis[v]){
			Tarjan(v);low[u]=min(low[u],low[v]);
		}else if(!col[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		col[u]=++totcols;
		while(stk[top]!=u)
			col[stk[top--]]=totcols;
		top--;
	}
}
void work(){
	ll1 res=flows::dinic();
	if(m-res>0){
		printf("No\n");
		return;
	}
	for(int i=1;i<=totn;i++){
		if(!vis[i])Tarjan(i);
	}
	bool flag=bool(totcols==3);
	if(flag)
	printf("Yes\n");
	else printf("No\n");
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		init();
		work();
	}
	return 0;
}

```

---

## 作者：Leasier (赞：1)

显然可以转化为判断是否存在真子图密度 $\geq D$。

有一个简单的想法：$\frac{|E|}{|V|} \geq D$ 等价于 $|E| - D|V| \geq 0$。

显然在 $|E|$ 固定时，$|V|$ 越小左式越大。贪心地，$E$ 固定时我们只会选择 $E$ 中涉及到的点。

“选 A 就必须选 B”让我们想到**最大权闭合子图**，可得如下网络流建图：

- 连边 $S \to^1 i$，表示一条边的权值为 $1$。
- 连边 $i \to^1 A_i', B_i'$，表示选一条边就必须选其两个端点。
- 连边 $i' \to^D T$，表示一个点的权值为 $-D$。

跑一遍网络流，则左式的最大值为 $ND - \operatorname{maxflow}$。

**但事实上这里 $\operatorname{maxflow} \leq ND$，因为 $G$ 本身就满足其密度 $= D$。上面的做法并没有排除 $G$ 本身。**

因而这里我们实际上只能在 $\operatorname{maxflow} < ND$ 时断言存在真子图密度 $> D$。

接下来考虑判断是否存在真子图密度 $= D$。考虑观察跑完网络流后的残量网络：

- $S \to^1 i, i' \to^D T$ 都被流满了。
- 对于每条边 $i$，其中一个端点 $u_i$ 满足 $u_i' \to^1 i$ 未满流，另一个端点 $v_i$ 满足 $i \to^1 v_i'$ 未满流。

不妨给每条边的情况换一个更加直观的描述方式：

- 给定一种每条边定向的方案，使得每个点出度为 $D$。

设定向后新图为 $G'$。

当 $D = 1$，$G'$ 必为**一个环**。否则，删去任意一个树上的叶子后，边数和点数均减小 $1$，此时密度仍为 $1$，不满足条件。

当 $D > 1$ 时，我们猜想 $G'$ 必然可以由**一堆环拼起来**，也就是说它是一个 SCC。

事实上这是正确的。证明：

- 充分性：对于一个 SCC，其每条边的两个端点仍在该 SCC 中，则 $G'$ 的密度为 $D$。
- 必要性：如果 $G'$ 不是一个 SCC，取 $G'$ 的一个子图 $G''$ 满足其为 SCC，则 $G''$ 的密度为 $D$，不满足条件。

于是我们只需要判断 $G'$ 是否恰有一个 SCC 即可。

实现时，ISAP 跑网络流、Tarjan 求 SCC 个数即可。时间复杂度为 $O(\sum dn \sqrt{dn})$。

代码：
```cpp
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

typedef struct {
	int nxt;
	int end;
	int dis;
} Edge;

int cnt;
int head[100007], dis[100007], dis_cnt[100007], cur_edge[100007], dfn[100007], low[100007];
bool vis1[100007], vis2[100007];
Edge edge[400007];
stack<int> s;
queue<int> q;

inline void init1(int n){
	cnt = 1;
	for (register int i = 0; i <= n; i++){
		head[i] = 0;
	}
}

inline void init2(int n){
	for (register int i = 0; i <= n; i++){
		dis[i] = 0x7fffffff;
		dis_cnt[i] = 0;
		cur_edge[i] = head[i];
	}
}

inline void init3(int n){
	for (register int i = 0; i <= n; i++){
		vis1[i] = false;
	}
}

inline void add_edge(int start, int end, int dis){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
}

inline void bfs(int start){
	dis[start] = 0;
	q.push(start);
	while (!q.empty()){
		int cur = q.front(), dis_i = dis[cur] + 1;
		q.pop();
		dis_cnt[dis[cur]]++;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (dis[x] == 0x7fffffff){
				dis[x] = dis_i;
				q.push(x);
			}
		}
	}
}

int dfs(int u, int flow, int start, int end, int n){
	if (u == end) return flow;
	int ans = 0;
	for (register int i = cur_edge[u]; i != 0; i = edge[i].nxt){
		cur_edge[u] = i;
		if (edge[i].dis != 0){
			int x = edge[i].end;
			if (dis[u] == dis[x] + 1){
				int t = dfs(x, min(flow - ans, edge[i].dis), start, end, n);
				edge[i].dis -= t;
				edge[i ^ 1].dis += t;
				ans += t;
				if (ans == flow || dis[start] == n) return ans;
			}
		}
	}
	cur_edge[u] = head[u];
	if (--dis_cnt[dis[u]] == 0) dis[start] = n;
	dis_cnt[++dis[u]]++;
	return ans;
}

inline int isap(int start, int end, int n){
	int ans = 0;
	bfs(end);
	while (dis[start] < n) ans += dfs(start, 0x7fffffff, start, end, n);
	return ans;
}

void tarjan(int u, int &id, int &scc_cnt){
	dfn[u] = low[u] = ++id;
	vis1[u] = vis2[u] = true;
	s.push(u);
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		if (edge[i].dis != 0){
			int x = edge[i].end;
			if (!vis1[x]){
				tarjan(x, id, scc_cnt);
				low[u] = min(low[u], low[x]);
			} else if (vis2[x]){
				low[u] = min(low[u], dfn[x]);
			}
		}
	}
	if (dfn[u] == low[u]){
		int cur;
		scc_cnt++;
		do {
			cur = s.top();
			vis2[cur] = false;
			s.pop();
		} while (cur != u);
	}
}

int main(){
	int t;
	cin >> t;
	for (register int i = 1; i <= t; i++){
		int n, d, m, end;
		cin >> n >> d;
		m = n * d;
		end = n + m + 1;
		init1(end);
		for (register int j = 1; j <= m; j++){
			int a, b, a_, b_;
			cin >> a >> b;
			a_ = a + m;
			b_ = b + m;
			add_edge(0, j, 1);
			add_edge(j, 0, 0);
			add_edge(j, a_, 1);
			add_edge(a_, j, 0);
			add_edge(j, b_, 1);
			add_edge(b_, j, 0);
		}
		for (register int j = 1; j <= n; j++){
			int j_ = j + m;
			add_edge(j_, end, d);
			add_edge(end, j_, 0);
		}
		init2(end);
		if (isap(0, end, end + 1) < m){
			cout << "No" << endl;
			continue;
		}
		int id = 0, scc_cnt = 0;
		init3(end);
		for (register int j = 0; j <= end; j++){
			if (!vis1[j]) tarjan(j, id, scc_cnt);
		}
		if (scc_cnt == 3){
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	return 0;
}
```

---

## 作者：Tony2 (赞：1)

题目要求判定一张图是否有一个严格子图的密度大于等于 $d$，可以考虑先判定是否有大于的情况。

这是一个经典问题，列出式子 $\dfrac e v>d$，得到 $e>vd$，我们需要判定 $e-vd$ 是否大于零。

这个式子可以看作每一条边有 $1$ 的贡献，每一个点有 $d$ 的代价，选了一条边必须要选连接的两个点，这是一个最大权闭合子图问题。图除了 $S$ 和 $T$ 共有两层，靠近 $S$ 的是边，靠近 $T$ 的是点。三类边为 $(S,e,1),(e,v,\inf),(v,T,d)$。

跑一次最大流看看是不是满流。如果不是那就直接输出 `No`，否则继续判断是否有严格非空子图的密度恰好为 $d$。

一个密度恰好等于 $d$ 的联通子图对应到最小割模型中会形成一个子图，若联通子图大小为 $x$，则最小割模型子图将包含 $x$ 个 $v$ 和 $dx$ 个 $e$，并且 $e$ 连向的两个 $v$ 都在子图内。这将构成一个强连通块，原因是找不到割边。一个非空的大小小于 $n(d+1)$ 的强连通块将对应着一个密度恰好等于 $d$ 的非空联通子图。

为了方便写代码，可以直接判定强连通块的个数，因为出度为 $0$ 的强连通块一定能满足我们的要求。

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 1e5 + 5, M = 1e6 + 5, inf = 1e9;
int T, n, d;
int s, t, etot, val[M];
int de[N], cur[N];
int dfsnum, dfn[N], low[N], top, sta[N], colnum, col[N];
vector<pair<int, int>> e1[N];
queue<int> q;
void addedge(int u, int v, int w){
	e1[u].emplace_back(v, ++etot);
	val[etot] = w;
	e1[v].emplace_back(u, ++etot);
	val[etot] = 0;
}
bool bfs(){
	for (int i = 1; i <= n * (d + 1) + 2; i++){
		de[i] = -1;
		cur[i] = 0;
	}
	q.push(s);
	de[s] = 0;
	while (!q.empty()){
		int u = q.front();
		q.pop();
		for (pair<int, int> p : e1[u]){
			int v = p.first, id = p.second;
			if (val[id] && de[v] == -1){
				de[v] = de[u] + 1;
				q.push(v);
			}
		}
	}
	return de[t] != -1;
}
int dfs(int u, int in){
	if (u == t) return in;
	int out = 0;
	for (int &i = cur[u]; i < (int)e1[u].size(); i++){
		int v = e1[u][i].first, id = e1[u][i].second;
		if (val[id] && de[v] == de[u] + 1){
			int res = dfs(v, min(val[id], in));
			in -= res;
			out += res;
			val[id] -= res;
			val[id & 1 ? id + 1 : id - 1] += res;
			if (!in) break;
		}
	}
	if (!out) de[u] = -1;
	return out;
}
void tarjan(int u){
	dfn[u] = low[u] = ++dfsnum;
	sta[++top] = u;
	for (pair<int, int> p : e1[u]){
		int v = p.first, id = p.second;
		if (!val[id]) continue;
		if (!dfn[v]){
			tarjan(v);
			low[u] = min(low[v], low[u]);
		}else if (!col[v]) low[u] = min(dfn[v], low[u]);
	}
	if (dfn[u] == low[u]){
		colnum++;
		do{
			col[sta[top]] = colnum;
		}while (sta[top--] != u);
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out2.txt", "w", stdout);
	cin >> T;
	while (T--){
		etot = 0;
		cin >> n >> d;
		s = n * (d + 1) + 1, t = s + 1;
		for (int i = 1; i <= t; i++)
			e1[i].clear();
		for (int i = 1; i <= n * d; i++){
			int u, v;
			cin >> u >> v;
			addedge(s, i + n, 1);
			addedge(i + n, u, inf);
			addedge(i + n, v, inf);
		}
		for (int i = 1; i <= n; i++)
			addedge(i, t, d);
		int flow = 0;
		while (bfs())
			flow += dfs(s, inf);
		if (flow < n * d){
			cout << "No" << endl;
			continue;
		}
		dfsnum = colnum = top = 0;
		for (int i = 1; i <= n * (d + 1) + 2; i++)
			dfn[i] = col[i] = 0;
		tarjan(s);
		for (int i = 1; i <= n * (d + 1) + 2; i++)
			if (!dfn[i])
				tarjan(i);
		cout << (colnum - 2 == 1 ? "Yes" : "No") << endl;
	}
	return 0;
}
```

后记：所以为什么要把 F 放在 E 后面？

---

## 作者：xxxxxzy (赞：0)

学习笔记，加深了我对网络流的理解，honglan0301 的做法。

题目给的是一个密度的形式。

回顾最大密度子图的做法：

二分 $k$，存在密度为 $k$ 的子图即存在子图满足 $\dfrac{|E|}{|V|} \ge k$。

移项，得到 $|E|-k|V|\ge 0$。

考虑把 $|E|$ 拆开，拆成了 $\dfrac{1}{2}(\sum\limits_{u \in V} \text{deg}_u - c(V))$，这里 $\text{deg}$ 表示顶点的度数，$c$ 表示一个割。

反过来，求 $k|V|-|E|$ 的最小值。此时，选中一个点 $u$ 会提供 $k-\dfrac{1}{2}\text{deg}_u$ 的贡献。同时 $\times 2$，变成 $2k - \text{deg}_u$。

考虑用网络流解决，具体来说，从源点 $s$ 往 $i$ 连一条权值 $0$ 的边，原图的边权值为 $1$，从 $i$ 往汇点连一条权值为 $2k-\text{deg}_u$ 的边。

这样会出现一个问题，边权 $2k - \text{deg}_u$ 可能为负数，于是把边权加上 $m$。

即，我们得到的最终方案是，从源点 $s$ 往 $i$ 连一条权值 $m$ 的边，原图的边权值为 $1$，从 $i$ 往汇点连一条权值为 $m+2k-\text{deg}_u$ 的边。

首先如果存在密度 $>D$ 的子图，那么一定不满足条件，这一个限制可以用上面的方案判断。

+ 为什么不能直接判断是否存在 $\ge D$ 的子图？

因为全图的密度 $=D$，用上面的方案判断会把整个图的答案包括进去。

相当于，我们要对上面的算法略微改造，我们要对上面的式子进行限制，具体来说，限制 $c(V) > 0$，即一定有割边。

考虑把原图上的边权从 $1$ 变为 $1-eps$。

对于原来 $\sum\limits_{u \in V'}(2D-\text{deg}_u) + c(V')=0$ 并且 $V' \ne V$ 的方案，这样的调整会让 $c(V')$ 变小，让最大流变小，从而让最小割变大，让答案 $> 0$。

因为 $eps$ 足够小，所以把 $1$ 调整为 $1-eps$ 并不会让原来合法的情况变得不合法。

这样跑出来 $\ge 0$ 的就一定有 $\ge D$ 的子图了。

这样就可以解决这个问题了，时间复杂度不会算，反正能过。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int __int128
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = ll; using i64 = ll; using i128 = __int128_t;
using namespace std;
const i32 N = 5e5 + 5;
const int inf = 1e20, INF = 1e35;
int num, s, t;
namespace Dinic {
  int cnt = 1, vis[N], now[N], dis[N];
  vector <int> G[N];
  int E[N << 1], V[N << 1]; 
  void adds(int x, int y, int z) { ++cnt, G[x].pb(cnt); E[cnt] = y, V[cnt] = z; }
  inline bool bfs() {
    rep (i, 1, num) dis[i] = INF;
    queue <int> q;
    dis[s] = 0;
    q.push(s);
    now[s] = 0;
    while (q.size()) {
      int x = q.front(); q.pop();
      rep (j, 0, (int)G[x].size() - 1) {
        int y = E[G[x][j]], z = V[G[x][j]];
        if (!z || dis[y] != INF) continue;
        dis[y] = dis[x] + 1; now[y] = 0; q.push(y);
        if (y == t) return 1;
      }
    }
    return 0;
  }
  inline int dfs(int x, int flow) {
    if (x == t) return flow;
      int sum = 0;
      rep (j, now[x], G[x].size() - 1) {
        now[x] = j;
        int e = G[x][j];
        int y = E[e], z = V[e];
        if (z > 0 && dis[y] == dis[x] + 1) {
        int res = dfs(y, min(flow - sum, z));
        V[e] -= res, V[e ^ 1] += res, sum += res;
        if (res == flow) return res;
      }
    }
    return sum;
  }
  inline void clear(int n) {
    rep (i, 1, n) G[i].clear();
    cnt = 1;
  }
  inline int dinic() {
    int ans = 0;
    while (bfs()) ans += dfs(s, INF);
    return ans;
  }
  inline void add(int u, int v, int w) {
    assert(w >= 0);
    adds(u, v, w); adds(v, u, 0);
  }	
}
using Dinic::clear;
using Dinic::add;
using Dinic::dinic;
using Dinic::adds;
i32 n, u, v, d, cnt, deg[N], vis[N];
vec G[N];
fv dfs(i32 u) {
  vis[u] = 1, cnt++;
  for (i32 v : G[u]) if (!vis[v]) dfs(v);
}
fv sol() {
  cin >> n >> d;
  i32 m = n * d; num = n; s = ++num, t = ++num; 
  rep (i, 1, n) vis[i] = 0, G[i].clear(); cnt = 0;
  rep (i, 1, m) cin >> u >> v, G[u].pb(v), G[v].pb(u), adds(u, v, inf - 1), adds(v, u, inf - 1);
  rep (u, 1, n) deg[u] = G[u].size();
  dfs(1);
  if (cnt != n) return (void)(clear(num), cout << "No\n");
  rep (i, 1, n) add(s, i, inf * m), add(i, t, inf * (m + 2 * d - deg[i]));
  int k = dinic();
  if ((__int128)n * m * inf > k) cout << "No\n";
  else cout << "Yes\n";
  clear(num);
}
signed main() {
  i32 T = 1;
  cin >> T;
  while (T--) sol();
}
```

---

