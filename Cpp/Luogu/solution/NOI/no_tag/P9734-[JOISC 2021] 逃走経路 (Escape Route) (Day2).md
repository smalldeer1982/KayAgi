# [JOISC 2021] 逃走経路 (Escape Route) (Day2)

## 题目背景

本题**不是**交互题，请注意提交方式。

[英文题面](https://www2.ioi-jp.org/camp/2021/2021-sp-tasks/day2/escape_route-en.pdf)。

## 题目描述

IOI 王国使用 Byou（秒）作为时间单位，将一天划分成 $S$ Byou，分别称为时刻 $0,1,\dotsc,S-1$。

IOI 王国中有 $N$ 个城市和 $M$ 条双向道路，均从 $0$ 开始标号。保证任两个城市之间均连通。第 $i$ 条道路连接城市 $A_i$ 和 $B_i$，需要恰好 $L_i$ Byou 通过。每天的时刻 $C_i$ 后，第 $i$ 条道路将开始进行检查，直到当天结束。

JOI 组织是一个活跃在 IOI 王国中的秘密团体。出于其保密性，成员不能在道路上受到检查。如果其成员想要通过道路 $i$，最晚要在时刻 $C_i-L_i$ 到达这条路的一端。道路的检查不会影响两端的城市。

现在有 $Q$ 名 JOI 组织的成员，从 $0$ 开始标号。第 $j$ 名成员在某天的时刻 $T_j$，要从城市 $U_j$ 出发去城市 $V_j$。成员可以在任意城市内停留任意长的时间。注意这名成员可能会在路上花费一天以上。

请计算每名成员花费的最短时间，精确到 Byou.

## 说明/提示

对于 $100\%$ 的数据，保证：

- $2 \leq N \leq 90$。
- $N-1 \leq M \leq \dfrac{N(N-1)}{2}$。
- $2 \leq S \leq 10^{15}$。
- $1 \leq Q \leq 3 \times 10^6$。
- $0 \leq A_i,B_i \leq N-1$。
- $A_i \neq B_i$。
- $\forall i,j \in [0,M-1]$，若 $i \neq j$，则有 $(A_i,B_i) \neq (A_j,B_j),(A_i,B_i) \neq (B_j,A_j)$。
- $1 \leq L_i \leq C_i < S$。
- 从任意城市出发走过一些边后，可以到达任意其他城市。
- $0\leq U_j,V_j \leq N-1$。
- $U_j \neq V_j$。
- $0 \leq T_j < S$。

有 $5 \%$ 的分数，满足 $N \leq 40,Q \leq 1000$。

另有 $20 \%$ 的分数，满足 $N \leq 40,U_j=0$

另有 $10 \%$ 的分数，满足 $N \leq 40$。

另有 $35 \%$ 的分数，满足 $N \leq 60$。

**建议使用较快的 IO 方式。**

## 样例 #1

### 输入

```
4 5 20 6
0 1 3 19
0 2 2 8
1 2 4 15
1 3 5 14
2 3 1 18
0 3 5
0 3 7
0 3 9
2 0 6
3 1 10
1 2 15```

### 输出

```
3
8
14
2
5
7```

## 样例 #2

### 输入

```
6 10 100 9
5 3 4 29
1 0 6 26
0 4 2 7
0 5 18 18
2 0 79 82
3 4 35 46
1 2 15 57
2 4 3 6
4 1 21 83
3 2 47 53
0 2 63
0 4 70
0 4 98
0 5 25
0 5 19
0 4 96
0 5 2
0 3 62
0 3 83```

### 输出

```
42
32
4
93
99
6
102
60
39```

## 样例 #3

### 输入

```
8 12 1000000000000000 13
2 0 4451698272827 120985696255786
6 5 78520421713825 342652131468508
2 1 185377268405175 382583457603811
0 4 54350742205838 133614919589507
7 0 68486247989149 651590905094148
0 6 85177550834829 299184420663240
5 2 442329739732459 926608308293721
3 7 78020232822359 913548478810253
1 3 267796317244889 687571310475622
5 4 90590208828121 910324397566584
5 7 8414633059584 17796117322043
4 6 45682367792138 204548471584556
7 2 44779065000162
3 5 79376234836942
4 7 305556687070759
4 3 927935834343174
5 1 663284649258985
2 5 967584209777344
5 2 963749709374595
7 4 484562389171308
1 5 446160773830045
6 4 801452311055604
3 1 744524289545354
0 6 467418420721777
5 6 371181379240653```

### 输出

```
72937946261976
929038398222642
702857945988825
272921388674172
580895059624855
181808439529442
117602869946965
569788353034530
1181546234307589
244230056736534
513790925121797
617759130113052
674500988551485```

# 题解

## 作者：寻逍遥2006 (赞：6)

简要题意：一天有 $S$ 个时刻。有 $Q$ 个人，其中第 $i$ 个人要从 $T_i$ 时刻开始从 $U_i$ 走到 $V_i$。对于每条边 $(A_i,B_i)$ 经过它需要 $L_i$ 的时间，它会在第 $C_i$ 个时刻关闭，这也就意味着只有在**每天的前 $C_i-L_i$ 个时刻**才能够走上这条路。问每个人至少需要多长的时间能够到达目的地。

首先答案必然有一个上界 $S\times n-T_i$，也就是把第一天等完，然后一天走一条边。

我们考虑一个人可能走的两种情况：

1. 在一天之内完成了整个路程。
2. 用至少两天完成了整个路程。

### 第二种情况

对于第二种情况，我们可以将其分解成三段：第一天，中间的若干天（可能没有），最后一天。我们逐个来考虑。

#### 第一天

考虑路径 $U\to V$。我们可以倒过来看：初始权值为 $S$，从 $V$ 点走到 $U$ 点，经过了第 $i$ 条边，权值会变成 $\min(S,C_i)-L_i$，我们要最大化最后的权值。

这个过程类似最短路可以使用 Dijkstra 实现，以每一个点为起点跑一遍，时间复杂度 $O(nm\log m)$。由于这个图是稠密图，所以 Dijkstra 单次可以做到 $O(n^3)$。

#### 最后一天

考虑路径 $U\to V$。这个和正常的最短路是类似的，但是只有转移权值 $\le C_i-L_i$ 才能沿着第 $i$ 条边转移。

这个也可以使用 Dijkstra 实现，以每一个点为起点跑一遍，时间复杂度 $O(nm\log m)$ 或者 $O(n^3)$。

#### 中间的若干天

每一天都可以看作是一条和“最后一天”相同的路径，利用最后一天对应的数组来生成一张图：如果可以从 $U$ 到达 $V$，则我们加入一条 $U\to V$ 的权值为 $S$ 的边。

然后在这张图上跑 Floyd 即可，时间复杂度 $O(n^3)$。

考虑如何计算对于答案的贡献，一个很暴力的想法是枚举第一天的终点 $U'$ 和最后一天的起点 $V'$，判断第一天 $U\to U'$ 的合法性，然后把三段的贡献加到一起。但是这样单次的复杂度为 $O(n^2)$ 无法接受。

我们考虑到 $V'$ 的枚举是只与 $U'$ 和 $V_i$ 有关的，与 $U_i$ 和 $T_i$ 无关。所以我们预处理对于每一个 $U'$ 和 $V_i$ 的 $V'$ 的枚举，这样在求解的过程中只需要枚举 $U'$ 即可。单次求解时间复杂度为 $O(n)$。

### 第一种情况

我们考虑一条从 $T=0$ 时刻开始的，合法的从 $U$ 到 $V$ 的路径，每次必然是能走就走，我们逐渐的增大 $T$，直到某一个时刻 $T=T'+1$ 时，有一条路是不可经过的了。也就是至多在 $T'$ 时刻出发，才能够走这一条路径。我们考虑限制住这条路径的是编号为 $x$ 的边，则从 $T'$ 时刻出发，必然会在 $C_x-L_x$ 时刻到达 $A_x$ 或 $B_x$，再在 $C_x$ 时刻到达这条边的另一端。

我们考虑枚举这条边 $x$，则可以将所有这样的路径拆成两部分（假设从 $A_x$ 进入这条边，从 $B_x$ 离开这条边，反过来也是类似的）：第一部分是从 $U\to A_x$，在 $C_x-L_x$ 时刻到达 $A_x$，这个可以和第二种情况中的“第一天”类似的方式处理；第二部分是 $B_x\to V$，从 $C_x$ 时刻出发，这个可以和第二种情况中的“最后一天”类似的方式处理。

对于某一对 $U,V$，假设我们得到至多在 $T_1$ 时刻从 $U$ 出发，可以在 $T_2$ 时刻到达 $V$，则如果要走 $U\to V$，且可以在 $\le T_1$ 的时刻出发，就可以以 $T_2-T_1$ 的代价走到。

对于每一对 $U,V$，都可以得到这样的 $O(m)$ 条路径，将其按照 $T_1$ 排序，去掉所有被其他路径偏序了的路径，就可以通过一次二分来得到每一次询问能否在第一天之内到达，同时可以得到它需要消耗的最短时间。

考虑时间复杂度：对于枚举每一条边跑一次 Dijkstra，时间复杂度为 $O(mn^2)$；对于每一个 $U\to V$ 点对处理那 $O(m)$ 条路经，时间复杂度 $O(n^2m\log m)$；每一次求解答案需要一次二分，时间复杂度 $O(Q\log m)$。

总体时间复杂度为 $O(n^2m\log m+Q(n+\log m))$ 可以通过。

```cpp
#include "escape_route.h"
#include <bits/stdc++.h>

using namespace std;

template<typename T>bool get_max(T &a,T b){if(a<b) return a=b,true;return false;}
template<typename T>bool get_min(T &a,T b){if(a>b) return a=b,true;return false;}

vector<long long> ans;
vector<pair<int,int> >ed[100];
vector<pair<long long,long long> >mind[100][100],tmp;
priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > G;
priority_queue<pair<long long,int> >G_;
long long dis[100][100],tr[100][100];

long long sid[100][100];

long long dis1[100],dis2[100];

int f[100][100];
bool vis[100];

vector<long long> calculate_necessary_time(
	int N, int M, long long S, int Q, vector<int> A, vector<int> B,
    vector<long long> L, vector<long long> C, vector<int> U,
    vector<int> V, vector<long long> T)
{
	ans.resize(Q);
	for(int i=0;i<M;i++)
		ed[A[i]].push_back(make_pair(B[i],i)),
		ed[B[i]].push_back(make_pair(A[i],i));
	
	//solve go in days

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++) dis[i][j]=S*N,vis[j]=false;
		dis[i][i]=0;G.push(make_pair(0ll,i));
		while(!G.empty())
		{
			int v=G.top().second;G.pop();
			if(vis[v]) continue;
			vis[v]=true;
			for(pair<int,int> g:ed[v])
				if(dis[i][v]+L[g.second]<=C[g.second]&&dis[i][g.first]>dis[i][v]+L[g.second])
					G.push(make_pair(dis[i][g.first]=dis[i][v]+L[g.second],g.first));
		}
		for(int j=0;j<N;j++)
			f[i][j]=(dis[i][j]<S?1:N+1);
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++) sid[i][j]=-1,vis[j]=false;
		sid[i][i]=S;G_.push(make_pair(S,i));
		while(!G_.empty())
		{
			int v=G_.top().second;G_.pop();
			if(vis[v]) continue;
			vis[v]=true;
			for(pair<int,int> g:ed[v])
				if(get_max(sid[i][g.first],min(sid[i][v],C[g.second])-L[g.second]))
					G_.push(make_pair(sid[i][g.first],g.first));
		}
	}

	for(int i=0;i<N;i++)
		f[i][i]=0;

	for(int k=0;k<N;k++)
	for(int i=0;i<N;i++)
	for(int j=0;j<N;j++)
		f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for(int i=0;i<N;i++)
	for(int j=0;j<N;j++)
	{
		tr[i][j]=f[i][j]*S;
		for(int k=0;k<N;k++)
			tr[i][j]=min(tr[i][j],f[i][k]*S+dis[k][j]);
	}

	//solve go in one day

	for(int i=0;i<M;i++)
	{
		//A[i]->B[i]
		memset(dis1,0xcf,sizeof(dis1));
		memset(dis2,0x3f,sizeof(dis2));
		dis1[A[i]]=C[i]-L[i],dis2[B[i]]=C[i];
		memset(vis,0,sizeof(vis));
		for(int j=0,mx;j<N;j++)
		{
			mx=-1;
			for(int k=0;k<N;k++)
				if(!vis[k]&&(mx==-1||dis1[mx]<dis1[k]))
					mx=k;
			vis[mx]=true;
			for(pair<int,int> g:ed[mx])
				if(dis1[mx]<=C[g.second]&&dis1[g.first]<dis1[mx]-L[g.second])
					dis1[g.first]=dis1[mx]-L[g.second];
		}
		memset(vis,0,sizeof(vis));
		for(int j=0,mn;j<N;j++)
		{
			mn=-1;
			for(int k=0;k<N;k++)
				if(!vis[k]&&(mn==-1||dis2[mn]>dis2[k]))
					mn=k;
			vis[mn]=true;
			for(pair<int,int> g:ed[mn])
				if(dis2[mn]<=C[g.second]-L[g.second]&&dis2[g.first]>dis2[mn]+L[g.second])
					dis2[g.first]=dis2[mn]+L[g.second];
		}
		for(int x=0;x<N;x++)
		for(int y=0;y<N;y++)
			if(dis1[x]>=0&&dis2[y]<=S)
				mind[x][y].push_back(make_pair(dis1[x],dis2[y]-dis1[x]));
		
		//B[i]->A[i]
		memset(dis1,0xcf,sizeof(dis1));
		memset(dis2,0x3f,sizeof(dis2));
		dis1[B[i]]=C[i]-L[i],dis2[A[i]]=C[i];
		memset(vis,0,sizeof(vis));
		for(int j=0,mx;j<N;j++)
		{
			mx=-1;
			for(int k=0;k<N;k++)
				if(!vis[k]&&(mx==-1||dis1[mx]<dis1[k]))
					mx=k;
			vis[mx]=true;
			for(pair<int,int> g:ed[mx])
				if(dis1[mx]<=C[g.second]&&dis1[g.first]<dis1[mx]-L[g.second])
					dis1[g.first]=dis1[mx]-L[g.second];
		}
		memset(vis,0,sizeof(vis));
		for(int j=0,mn;j<N;j++)
		{
			mn=-1;
			for(int k=0;k<N;k++)
				if(!vis[k]&&(mn==-1||dis2[mn]>dis2[k]))
					mn=k;
			vis[mn]=true;
			for(pair<int,int> g:ed[mn])
				if(dis2[mn]<=C[g.second]-L[g.second]&&dis2[g.first]>dis2[mn]+L[g.second])
					dis2[g.first]=dis2[mn]+L[g.second];
		}
		for(int x=0;x<N;x++)
		for(int y=0;y<N;y++)
			if(dis1[x]>=0&&dis2[y]<=S)
				mind[x][y].push_back(make_pair(dis1[x],dis2[y]-dis1[x]));
	}

	for(int x=0;x<N;x++)
	for(int y=0;y<N;y++)
	if(mind[x][y].size())
	{
		sort(mind[x][y].begin(),mind[x][y].end(),[&](pair<long long,long long> A,pair<long long,long long> B)
		{if(A.first!=B.first) return A.first<B.first;else return A.second>B.second;});
		vector<pair<long long,long long> >().swap(tmp);
		for(pair<long long,long long> &g:mind[x][y])
		{
			while(!tmp.empty()&&tmp.rbegin()->second>g.second) tmp.pop_back();
			tmp.push_back(g);
		}
		swap(tmp,mind[x][y]);
	}

	vector<pair<long long,long long> >::iterator it;

	for(int i=0;i<Q;i++)
	{
		if((it=lower_bound(mind[U[i]][V[i]].begin(),mind[U[i]][V[i]].end(),make_pair(T[i],0ll)))!=mind[U[i]][V[i]].end())
			ans[i]=it->second;
		else ans[i]=(N+1)*S;
        
		if(T[i]<=sid[V[i]][U[i]])
			get_min(ans[i],S-sid[V[i]][U[i]]);
		
		for(int j=0;j<N;j++)
			if(T[i]<=sid[j][U[i]])
				get_min(ans[i],S-T[i]+tr[j][V[i]]);
	}
	return ans;
}
```

注：需要写标准输入输出，而不是 JOISC 的交互。

---

## 作者：云浅知处 (赞：4)

首先，我们有 $O(q(n^2+m))$ 的算法，即每次询问跑一遍 dijkstra，同时记录到每个点的最短路以及这个最短路对应的时刻。可以证明只要这样就能得到最优解。

把路径分成两类：在一天内完成的，和至少有一次等待到下一天的。

对于在一天内完成的路径，我们考虑找到其中限制最严（也就是经过这条边的时间最接近他的限制时间）的一条边 $(u,v,L,C)$，假设我们是从 $s$ 走到 $t$，起始时间为 $A$，如果走到点 $u$ 的时候时刻为 $B\le C-L$，那么我们知道这条边的 $C-L-B$ 是所有边里面最小的一个。

我们把起始时刻加上 $C-L-B$，可以发现路径仍然合法。于是有如下的算法：枚举每条边 $(u,v,L,C)$，计算 $dis_x$ 表示想要从 $x$ 走到 $u$，满足：

- 整个过程必须在一天内完成。
- 到达 $u$ 时，当前时刻 $\le C-L$。

这种情况下所需的最小时间。这可以通过一遍 dijkstra 在 $O(n^2+m)$ 的时间内算出，同时也可以算出 $tim_x$ 表示如果要求能走这个最短路，$x$ 的起始时间最晚是多少。再通过一遍 dijkstra 算出 $to_y$ 表示从 $v$ 到 $y$，起始时间为 $C$，所需的最少时间（这个过程同样必须在一天内完成）。

算出这些之后，我们就可以计算 $(u,v,L,C)$ 这条边对所有点对 $(x,y)$ 的贡献，即对于起始时间 $A\le tim_x$，都有一种 $dis_x+to_y+L$ 的方案。

现在考虑跨越多天的路径，注意到如果在某个城市 $u$ 进行等待，一定是等待到第二天的 $0$ 时刻，然后在 $L$ 时刻出现在某条边 $(u,v,L,C)$ 的终点 $v$。

于是类似地，我们枚举路径上第一条进行等待的边 $(u,v,L,C)$，同理算出 $tim,dis,to$（只不过此时从 $v$ 开始走的时候，我们允许它跨越多天完成），更新答案即可。

最后再对每个点对 $x,y$，我们把贡献到 $(x,y)$ 上面的若干条路径按照 $tim$ 排序，然后预处理后缀 min，即可在 $O(\log n)$ 的时间内回答一组询问。这里可能要对 $O(n^2)$ 个长度为 $O(m)$ 的数组排序，但注意到对于一个 $x$，所有 $y$ 的分段点总共只有 $O(m)$ 个，于是只需要进行 $n$ 次排序。

综上，总复杂度 $O((n^2+m)m+nm\log m+q\log n)$。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline char gc(){
	static char buf[100000],*p1=buf,*p2=buf; 
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++; 
}
inline ll read(){
	ll x=0,f=1;char c=gc();
	for(;(c<'0'||c>'9');c=gc()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=gc())x=x*10+(c&15);
	return x*f;
}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=105;
const int M=10005;
vector<pair<int,pair<ll,ll> > >G[N];
int n,m,q;ll S;

const ll INF=1e18;
ll dis[N],tim[N];bool vis[N];
void dij1(int s,ll st){
	for(int i=0;i<=n;i++)dis[i]=INF,tim[i]=0,vis[i]=0;
	dis[s]=0,tim[s]=st;
	for(int _=1;_<=n;_++){
		int u=0;
		for(int i=1;i<=n;i++)if((!vis[i])&&dis[i]<dis[u])u=i;
		vis[u]=1;
		for(auto [v,A]:G[u]){
			ll cost=A.fi,lim=A.se;
			if(tim[u]+cost<=lim){
				if(dis[v]>dis[u]+cost)dis[v]=dis[u]+cost,tim[v]=tim[u]+cost;
			}
			else{
				if(dis[v]>dis[u]+S-tim[u]+cost)dis[v]=dis[u]+S-tim[u]+cost,tim[v]=cost;
			}
		}
	}
}
void dij2(int s,ll st){
	for(int i=0;i<=n;i++)dis[i]=INF,tim[i]=0,vis[i]=0;
	dis[s]=0,tim[s]=st;
	for(int _=1;_<=n;_++){
		int u=0;
		for(int i=1;i<=n;i++)if((!vis[i])&&dis[i]<dis[u])u=i;
		if(dis[u]>=INF)return ;
		vis[u]=1;
		for(auto [v,A]:G[u]){
			ll cost=A.fi,lim=A.se;
			if(tim[u]<cost)continue;
			ll cc=tim[u]-(min(tim[u],lim)-cost);
			if(dis[v]>dis[u]+cc)dis[v]=dis[u]+cc,tim[v]=min(tim[u],lim)-cost;
		}
	}
}
void dij3(int s,ll st){
	for(int i=0;i<=n;i++)dis[i]=INF,tim[i]=0,vis[i]=0;
	dis[s]=0,tim[s]=st;
	for(int _=1;_<=n;_++){
		int u=0;
		for(int i=1;i<=n;i++)if((!vis[i])&&dis[i]<dis[u])u=i;
		if(dis[u]>=INF)return ;
		vis[u]=1;
		for(auto [v,A]:G[u]){
			ll cost=A.fi,lim=A.se;
			if(tim[u]+cost>lim)continue;
			if(dis[v]>dis[u]+cost)dis[v]=dis[u]+cost,tim[v]=tim[u]+cost;
		}
	}
}

vector<pair<ll,ll> >vals[N][N];
int st[M],ed[M];ll lim[M],len[M];

const int Q=3e6+5;
struct qry{int x,y;ll t;}qr[Q];
ll ans[Q];

vector<pair<ll,int> >vec[N];
vector<ll>tos[750005];
int ncnt=0;

signed main(void){

	n=read(),m=read(),S=read(),q=read();
	
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1;ll L=read(),C=read();
		G[u].emplace_back(mk(v,mk(L,C)));
		G[v].emplace_back(mk(u,mk(L,C)));
		st[i]=u,ed[i]=v,lim[i]=C,len[i]=L;
	}
	
	for(int i=1;i<=q;i++)qr[i].x=read()+1,qr[i].y=read()+1,qr[i].t=read(),ans[i]=INF;
	
	for(int i=m+1;i<=m+m;i++)st[i]=ed[i-m],ed[i]=st[i-m],lim[i]=lim[i-m],len[i]=len[i-m];m*=2;
	
	for(int i=1;i<=m;i++){
		int u=st[i],v=ed[i];
		vector<ll>to(n+1);
		dij1(v,len[i]);
		for(int j=1;j<=n;j++)to[j]=dis[j];
		dij2(u,S-1);
		for(int j=1;j<=n;j++)if(dis[j]<INF){
			vector<ll>curt(n+1);
			for(int k=1;k<=n;k++)curt[k]=dis[j]+to[k]+len[i]+1+tim[j];
			tos[++ncnt]=curt,vec[j].emplace_back(mk(tim[j],ncnt));
		}
	}
	
	for(int i=1;i<=n;i++){
		sort(vec[i].begin(),vec[i].end());
		for(auto [tim,id]:vec[i]){
			for(int j=1;j<=n;j++)vals[i][j].emplace_back(mk(tim,tos[id][j]));
			vector<ll>().swap(tos[id]);
		}
		vector<pair<ll,int> >().swap(vec[i]);
	}
	
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		ll mn=INF;
		vector<pair<ll,ll> >cur;
		for(int k=vals[i][j].size()-1;k>=0;k--){
			if(vals[i][j][k].se<mn)cur.emplace_back(vals[i][j][k]),mn=vals[i][j][k].se;
		}
		reverse(cur.begin(),cur.end());vals[i][j]=cur;
	}
	
	for(int i=1;i<=q;i++){
		auto [u,v,st]=qr[i];
		int p=lower_bound(vals[u][v].begin(),vals[u][v].end(),mk(st,-1ll))-vals[u][v].begin();
		if(p<vals[u][v].size())cmin(ans[i],vals[u][v][p].se-st);
	}
	
	ncnt=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)vector<pair<ll,ll> >().swap(vals[i][j]);
	
	for(int i=1;i<=m;i++){
		int u=st[i],v=ed[i];
		vector<ll>to(n+1);
		dij3(v,lim[i]);
		for(int j=1;j<=n;j++)to[j]=dis[j];
		dij2(u,lim[i]-len[i]);
		for(int j=1;j<=n;j++)if(dis[j]<INF){
			vector<ll>curt(n+1);
			for(int k=1;k<=n;k++)curt[k]=dis[j]+to[k]+len[i];
			tos[++ncnt]=curt,vec[j].emplace_back(mk(tim[j],ncnt));
		}
	}
	
	for(int i=1;i<=n;i++){
		sort(vec[i].begin(),vec[i].end());
		for(auto [tim,id]:vec[i]){
			for(int j=1;j<=n;j++)vals[i][j].emplace_back(mk(tim,tos[id][j]));
			vector<ll>().swap(tos[id]);
		}
		vector<pair<ll,int> >().swap(vec[i]);
	}
	
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		ll mn=INF;
		if(!vals[i][j].empty()){
			vector<pair<ll,ll> >cur;
			for(int k=vals[i][j].size()-1;k>=0;k--){
				if(vals[i][j][k].se<mn)cur.emplace_back(vals[i][j][k]),mn=vals[i][j][k].se;
			}
			reverse(cur.begin(),cur.end());vals[i][j]=cur;
		}
	}
	
	for(int i=1;i<=q;i++){
		auto [u,v,st]=qr[i];
		int p=lower_bound(vals[u][v].begin(),vals[u][v].end(),mk(st,-1ll))-vals[u][v].begin();
		if(p<vals[u][v].size())cmin(ans[i],vals[u][v][p].se);
		cout<<ans[i]<<'\n';
	}

	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：3)

容易算出 $f_{i,j}$ 表示从 $i$ 城市、时刻 $0$ 出发到达 $j$ 的最小时间。

然后就是考虑如何对一个询问，快速计算出 $g_i$ 表示同一天到达 $i$ 的最小时间（或者不可能）。这样子我们就能枚举是否要经过多天，以及第一天的中转站来计算答案了。

如何快速计算 $g$ 呢？首先每个询问都扫一遍所有边显然不行。我们考虑离线询问。把所有起点相同的询问归为一类，按照时间**从大到小**排序。维护每个点的同一天最小时间 $g$。

那么注意到随着出发时间的减少 $g$ 也会慢慢减小。那么每条边会在某个时刻减少到可用。也就是，**只有至多 $m$ 个询问，其新增了可用边**。

如果一个询问新增了可用边。我们直接重构 $g$ 即可。这部分复杂度是 $O(nm^2)$ 的，可以接受。否则我们没有新增边，直接对 $g$ 减少早出发的时间即可。

复杂度是 $O(n(m^2+q))$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
const int MAXN=95,MR=3e6+5;
const ll inf=1e18;
ll n,m,s,q,ans[MR],d[MAXN][MAXN],R[MAXN][MAXN],T[MAXN][MAXN];
ll cur[MAXN],ti[MAXN];
inline void chkmin(ll &x,ll y){if(x>y)x=y;}
inline void chkmax(ll &x,ll y){if(x<y)x=y;}
vector<array<ll,3> > vec[MAXN];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	// freopen("Otomachi_Una.in","r",stdin);
	// freopen("Otomachi_Una.out","w",stdout);
	cin>>n>>m>>s>>q;
	memset(R,-1,sizeof(R));
	while(m--){
		ll u,v,c,l;cin>>u>>v>>l>>c;u++,v++;
		R[u][v]=R[v][u]=c-l;T[u][v]=T[v][u]=l;
	}
	memset(d,0x3f,sizeof(d));
	for(int i=1;i<=n;i++){
		d[i][i]=0;
		for(int t=1;t<=n;t++) for(int u=1;u<=n;u++) 
		for(int v=1;v<=n;v++) if(R[u][v]>=0){
			chkmin(d[i][v],d[i][u]+(d[i][u]%s<=R[u][v]?T[u][v]:
				s-d[i][u]%s+T[u][v]));
		}
	}
	for(int i=1;i<=q;i++){
		ll u,v,t;cin>>u>>v>>t;u++,v++;
		vec[u].push_back({t,v,i});
	}
	for(int i=1;i<=n;i++){
		// cerr<<"Solve "<<i<<'\n';
		sort(vec[i].begin(),vec[i].end());
		reverse(vec[i].begin(),vec[i].end());
		memset(cur,0x3f,sizeof(cur));cur[i]=s;
		memset(ti,0x3f,sizeof(ti));
		ll t=s;
		for(auto o:vec[i]){
			priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> q;
			for(int j=1;j<=n;j++) if(cur[j]<inf){
				cur[j]-=(t-o[0]);
				if(cur[j]<=ti[j]) q.push(MP(cur[j],j));
			}t=o[0];
			while(!q.empty()){
				auto it=q.top();q.pop();
				ll u=it.second,t=it.first;
				if(cur[u]!=t) continue;
				ti[u]=-inf;
				for(int v=1;v<=n;v++) if(R[u][v]>=0){
					if(cur[u]<=R[u][v]){
						if(cur[u]+T[u][v]<cur[v]){
							cur[v]=cur[u]+T[u][v];
							q.push(MP(cur[v],v));
						}
					}else chkmax(ti[u],R[u][v]);
				}
			}
			if(cur[o[1]]<inf) ans[o[2]]=cur[o[1]]-o[0];
			else{
				ans[o[2]]=inf;
				for(int i=1;i<=n;i++) if(cur[i]<inf)
					chkmin(ans[o[2]],s-o[0]+d[i][o[1]]);
			}
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：是青白呀 (赞：1)

你发现点数和边数是完全支持我们对 $n$ 个起点都跑一次最短路的。问题在于时间太多，$|S|$ 达到 $10^{15}$，没办法对每个时间都跑一次。但是显然地，并不是每个时间都有意义，许多时间实际上是等效的。下面分两条路考虑：

首先是路程在一天内结束的方案。我们找到全过程中，到达 $v$ 的时间距离终止时间最近的一条边 $(u,v,l,c)$，假设我们于 $t$ 时刻出发，实际是 $x$ 时刻到的 $v$，则出发时刻从 $t\sim t+c-x$ 都是等效的。于是我们枚举每一条限制边，从 $u$ 出发跑 dij，算出 $dis_x$ 表示从 $x$ 出发、途中不被其它边的终止时间限制，到达 $u$ 的最短时间。进而，可以算出从每个点的最小出发时间。然后再维护 $to_x$ 表示当天于 $c$ 时刻从 $v$ 出发，**当天**到其它点的最小时间。则对于每个满足出发时间限制的询问，都存在一组耗时为 $dis_x+to_y+l$ 的解。我们可以对于每个点对 $(u,v)$ 维护求到的所有 $2m$ 种方案，将它们按照出发时间限制排序并对总时长做后缀 $\min$，每个询问二分即可。

对于路程跨天的方案，你发现一旦过了一天后，第二天早上的出发时间一定是 $0$ 时刻，这样，可能情况大大减少。我们直接枚举第二天早上的出发点 $u$，仍然跑 dij 求出 $frm_x$ 表示从 $x$ 在一天之内于 $s$ 时刻前到达 $u$ 的最小时间、$stt_y$ 表示从 $u$ 于 $0$ 时刻出发，经过任意天到 $y$ 的最短时间。对每个询问，同样枚举第二天的出发点即可。

由于给出的可能是完全图，dij 的过程可以直接用 $O(n^2+m)$ 的暴力算法实现，相较于 $O(m\log m)$ 的优先队列做法更优。故总复杂度为 $O((n+m)(n^2+m)+n^2m\log m+q\log m+qn)$，不难通过。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=95,M=105,inf=(ll)1e18+7,mo=1e9+7;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m,s,q;
struct edge{
    int to,len,lim;
};
vector<edge>e[N];
int dis[N],to[N];
int frm[N][N],stt[N][N];
vector<pii>ans[N][N];
void getans(int endt,int l){
    rep(x,1,n){
        rep(y,1,n){
            if(x==y)continue;
            if(dis[x]==inf||to[y]==inf)continue;
            ans[x][y].push_back(mp(endt-dis[x],dis[x]+l+to[y]));
        }
    }
}
bool vis[N];
void dij1(int x,int t,int op){
    rep(i,1,n)
        dis[i]=inf,vis[i]=0;
    dis[x]=0;
    int nwp=x,cntp=0;
    while(cntp<n){
        vis[nwp]=1,cntp++;
        for(auto p:e[nwp]){
            int j=p.to,l=p.len,c=p.lim;
            if(vis[j])continue;
            if(t-dis[nwp]-l<0)continue;
            if(t-dis[nwp]>c&&!op)continue;
            if(t-dis[nwp]>c)dis[j]=min(dis[j],t-c+l);
            else dis[j]=min(dis[j],dis[nwp]+l);
        }
        rep(i,1,n){
            if(vis[i])continue;
            if(dis[i]==inf)continue;
            if(vis[nwp]||dis[nwp]>dis[i])nwp=i;
        }
        if(vis[nwp])break;
    }
}
void dij2(int x,int t,int op){
    rep(i,1,n)
        to[i]=inf,vis[i]=0;
    to[x]=0;
    int nwp=x,cntp=0;
    while(cntp<n){
        vis[nwp]=1,cntp++;
        int nwt=(t+to[nwp])%s;
        for(auto p:e[nwp]){
            int j=p.to,l=p.len,c=p.lim;
            if(vis[j])continue;
            if(l+nwt<=c)to[j]=min(to[j],to[nwp]+l);
            else if(op)to[j]=min(to[j],to[nwp]+s-nwt+l);
        }
        rep(i,1,n){
            if(vis[i])continue;
            if(to[i]==inf)continue;
            if(vis[nwp]||to[nwp]>to[i])nwp=i;
        }
        if(vis[nwp])break;
    }
}
signed main(){
    read(n),read(m),read(s),read(q);
    rep(i,1,m){
        int x,y,l,c;
        read(x),read(y),read(l),read(c);
        x++,y++;
        e[x].push_back((edge){y,l,c}),e[y].push_back((edge){x,l,c});
    }
    rep(i,1,n){
        for(auto p:e[i]){
            int j=p.to,l=p.len,c=p.lim;
            dij1(i,c-l,0),dij2(j,c,0);
            getans(c-l,l);
        }
        dij1(i,s,1),dij2(i,0,1);
        rep(j,1,n)
            frm[i][j]=dis[j],stt[i][j]=to[j];
    }
    rep(i,1,n){
        rep(j,1,n){
            if(i==j)continue;
            sort(ans[i][j].begin(),ans[i][j].end());
            repp(l,(int)ans[i][j].size()-2,0)
                ans[i][j][l].sec=min(ans[i][j][l].sec,ans[i][j][l+1].sec);
        }
    }
    while(q--){
        int x,y,t;
        read(x),read(y),read(t);
        x++,y++;
        int res=inf;
        if(ans[x][y].size()){
            res=min(res,ans[x][y][0].sec+s-t);
            int targ=lower_bound(ans[x][y].begin(),ans[x][y].end(),mp(t,0ll))-ans[x][y].begin();
            if(targ<(int)ans[x][y].size())res=min(res,ans[x][y][targ].sec);
        }
        rep(i,1,n){
            if(frm[i][x]==inf||stt[i][y]==inf)continue;
            res=min(res,s-t+(s-frm[i][x]<t?s:0)+stt[i][y]);
        }
        printf("%lld\n",res);
    }
    return 0;
}
```

---

## 作者：honglan0301 (赞：0)

## 题目分析

记 $f_{i,j}(x)$ 表示在时刻 $x$ 从 $i$ 出发去 $j$ 的最早到达时间，$g_{i,j}(x)$ 表示在时刻 $x$ 从 $i$ 出发去 $j$ 最少花费的时间。那么观察结论：

1. 当 $f_{i,j}(x)$ 与 $x$ 不在同一天时，$f_{i,j}(x)$ 是至多 $n$ 段的分段函数，因为这仅与出发那天能到达的城市集合有关。

2. 否则，$g_{i,j}(x)$ 是至多 $m$ 段的分段函数，因为其仅与当天能够使用的边集有关。

于是我们只需要对两种情况分别处理：

1. 首先对每个有序对 $(i,j)$ 预处理出想在一天内从 $i$ 到 $j$ 的最晚出发时间 $t_{i,j}$，这可以通过建反图跑最短路实现（钦定在一天的末尾到达 $j$ 不影响结果）。

	然后再处理在一天起始时出发的全源最短路。对每个询问把两部分拼起来即可（答案就是 $S-T_j+\min\{dis(i,v_j)\mid t_{u_j,i}\ge T_j\}$）。
    
2. 考虑将每条边 $(A_i,B_i)$ 消失的时间 $C_i$ 作为关键时刻，以每个关键时刻作为出发时间跑出正反图上以 $B_i$ 为起点的最短路，然后拼起来分段取最小值就好。 

	感性理解它挺对的，因为 $g_{i,j}$ 的每个端点都代表着一次路径的改变，而路径发生改变当且仅当该路径上的一条边恰好在通过时消失，于是枚举每条“恰好要消失”的边应当具有正确性。
    
从每个步骤看，时间复杂度大概不超过 $O(nm\log m+n^3+qn+m^2\log m+n^2m+q\log m)$，应当足够通过本题。

不过我是口胡选手，没有写代码，如果有锅请指出。

---

