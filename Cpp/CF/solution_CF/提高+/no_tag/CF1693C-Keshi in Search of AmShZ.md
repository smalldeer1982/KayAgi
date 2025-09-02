# Keshi in Search of AmShZ

## 题目描述

AmShZ has traveled to Italy from Iran for the Thom Yorke concert. There are $ n $ cities in Italy indexed from $ 1 $ to $ n $ and $ m $ directed roads indexed from $ 1 $ to $ m $ . Initially, Keshi is located in the city $ 1 $ and wants to go to AmShZ's house in the city $ n $ . Since Keshi doesn't know the map of Italy, AmShZ helps him to see each other as soon as possible.

In the beginning of each day, AmShZ can send one of the following two messages to Keshi:

- AmShZ sends the index of one road to Keshi as a blocked road. Then Keshi will understand that he should never use that road and he will remain in his current city for the day.
- AmShZ tells Keshi to move. Then, Keshi will randomly choose one of the cities reachable from his current city and move there. (city $ B $ is reachable from city $ A $ if there's an out-going road from city $ A $ to city $ B $ which hasn't become blocked yet). If there are no such cities, Keshi will remain in his current city.Note that AmShZ always knows Keshi's current location.

AmShZ and Keshi want to find the smallest possible integer $ d $ for which they can make sure that they will see each other after at most $ d $ days. Help them find $ d $ .

## 说明/提示

In the first sample, it's enough for AmShZ to send the second type of message.

In the second sample, on the first day, AmShZ blocks the first road. So the only reachable city from city $ 1 $ will be city $ 4 $ . Hence on the second day, AmShZ can tell Keshi to move and Keshi will arrive at AmShZ's house.

It's also possible for AmShZ to tell Keshi to move for two days.

## 样例 #1

### 输入

```
2 1
1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
4 4
1 2
1 4
2 4
1 4```

### 输出

```
2```

## 样例 #3

### 输入

```
5 7
1 2
2 3
3 5
1 4
4 3
4 5
3 1```

### 输出

```
4```

# 题解

## 作者：小木虫 (赞：9)

###  Preface  
非常经典的类 Dijkstra 算法，同样类型的题目还有 [AHOI2014/JSOI2014]骑士游戏，[SDOI2010]大陆争霸。  
### Problem  
给你一张 $n$ 个点的有向连通图，你可以从点 1 开始沿着一条路径行走，沿着一条边行走花费 1 的时间，在某个点上时你可以花费 1 的时间断掉一条相邻的边，若沿着边行走的行动是完全随机的，即随机选择一条相邻边行走，问到达 $n$ 点的最大时间的最小值。

### Solution  
如果你做过我说的那两道题，那么这道题在思维上应该对您来说十分简单。    

具体来说，由于一个点到 $n$ 点的最小代价由其后继决定，我们倒着考虑，设 $f_u$ 为从 $u$ 到 $n$ 的最小代价，那么：  
$$f_u=\min_{v\in nxt_u}(f_v+\sum_{p\in nxt_u}[f_p>f_v]+1)$$  

发现该转移方程是正权的，同时这是一个带环图，考虑 Dijkstra trick 优化这个 dp，即每一次我们取出一个 $f$ 最小的点进行考虑，而那个求和符号后面的东西可以在一个一个转移的时候一个一个减，本质就是度数（因为我们先取 $f$ 小的），没有做到的转移一定是无意义的。  




code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,u,v,deg[N],vis[N],dis[N];
struct node{
	int u,dis;
	bool operator <(const node &a)const{
		return dis>a.dis;
	}
};
priority_queue <node> Q;
vector <int> edge[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>u>>v,edge[v].push_back(u),deg[u]++;
	fill(dis,dis+1+n,1e9);
	Q.push((node){n,0});dis[n]=0;
	while(!Q.empty()){
		int u=Q.top().u,w=Q.top().dis;
		Q.pop();if(vis[u])continue;vis[u]=1,dis[u]=w;
		for(int i=0;i<edge[u].size();i++){
			int v=edge[u][i];int w=deg[v]--;
			if(vis[v])continue;
			Q.push((node){v,dis[u]+w});
		}
	}cout<<dis[1];
	return 0;
}
```


---

## 作者：周子衡 (赞：7)

显然 AmShz 可以先把该封的道路都封了，再指挥 Keshi 行动。剩下的图中，$1$ 不能走到任何一个环。总代价为封的道路数量 + 剩下的图中 $1$ 至 $n$ 的最长路。

直接做也许有些困难。我们先人为添加一条性质：保证原图是有向无环图。可以发现，似乎没有什么直接的贪心做法。考虑 DP。我们设 $d_i$ 表示从 $i$ 到 $n$ 的最小代价。假设我们知道了 $i$ 的所有后继的 $d$ 值 $d_1,...,d_k$，将它们降序排序。那么封路一定是封 $d$ 值较大的若干条道路。枚举封多少条路，可以得到 $d_i=\min_{1\leq x \leq k}\{d_{x}+x\}$。在反图上按拓扑序 DP 即可。

回到原题。可能有环怎么办呢？我们可以考虑借用 Dijsktra 算法的思想。初始时，我们令 $d_n=0$，其余点的 $d$ 值都为正无穷。对于每个还没有确定 $d$ 值的点 $u$，我们定义它的**当前值** $c_u$ 为：假设 $u$ 的所有出边中，还没确定 $d$ 值的点的 $d$ 值都为正无穷，$d_u$ 的值。可以发现，所有 $c_u$ 中最小的那个一定等于最后的 $d_u$。我们用一个小根堆维护所有的 $c$，每次取出 $c$ 最小的那个，将它的 $d$ 值确定下来，然后扫描所有指向它的点，更新这些点的 $c$ 值。可以发现，这样每次从堆里取出来的 $c$ 一定是递增的，那么每次用新确定的 $d$ 去更新 $c$ 的时候，实际上只有包含了所有已确定点的方案是需要额外考虑的，因而单次更新可以做到 $O(1)$。总时间复杂度 $O(m\log n)$。实现可以类比 Dijsktra 算法的实现。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

const int INF=1e9;

typedef pair<int,int> PAIR;

priority_queue<PAIR> pq;
int out[300000];vector<int> ed[300000];bool vis[300000];
int dis[300000];

int main()
{
	int n=0,m=0;scanf("%d%d",&n,&m);
	for(int i=1,x=0,y=0;i<=m;i++)
	{
		scanf("%d%d",&x,&y);out[x]++;ed[y].push_back(x);
	}
	for(int i=1;i<n;i++)dis[i]=INF;
	pq.push(make_pair(0,n));
	while(!pq.empty())
	{
		int u=pq.top().second;pq.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=0;i<ed[u].size();i++)
		{
			int v=ed[u][i];
			out[v]--;int x=dis[u]+out[v]+1;
			if(dis[v]>x){dis[v]=x;pq.push(make_pair(-dis[v],v));}
		}
	}
	printf("%d",dis[1]);
}
```

**后记**

非常喜欢这题。也许这种改造熟知算法的题比较符合我的审美？QaQ

以及感觉这场后面几个题也都不错。~~虽然好像很码，呜呜呜。~~

---

## 作者：I_am_Accepted (赞：7)

~~蓝题过分了嗷~~

### Preface

首先我们发现这是一种最短路变式，而且题面中的「随机走一条」可以等效为「走最差的一条」。

我们首先温习一下 **Dijkstra** 算法的过程：找到**还没有确定的距离终点最短的点**确定下来，然后扩展。

我们发现这样点是按**距离终点的距离升序**确定下来的。

由于**边权非负**，可得 Dij 的正确性。

由于本题的边权（封路 + 走路）也非负，所以可以用 Dij 的思路。

### Analysis

我们先考察一个点 $x$。假设我们知道了 $x$ 每条出边到达的点的最小距离（封路 + 走路），设为 $c_1\le c_2\le \dots\le c_k$，我们可以求出 $x$ 的最小距离
$$
\min_{i=1}^k(c_i+k-i)
$$
原理是我们贪心封住最小距离最大的那些路。

由于刚才说到点是按距离终点的距离升序确定下来的，所以每次从每一个点扩展到 $x$，这些点按顺序一定是 $c_1,c_2,\dots,c_k$ 对应的点。

所以，我们在 Dij 的同时，记录这个点是被第几次扩展的（即还有多少出度），然后正常 Dij 即可。

### Code

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug cerr<<"Line#"<<__LINE__<<endl
#define ll long long
const ll mod=1;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int long long
#define N 200010
const int inf=1e9;
struct node{
	int id,dis;
	friend bool operator<(node x,node y){
		return x.dis>y.dis;
	}
};
int dis[N],deg[N],n,m;
priority_queue<node> q;
vector<int> e[N];
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	For(i,1,n) dis[i]=inf;
	dis[n]=0;
	int x,y;
	For(i,1,m){
		cin>>x>>y;
		e[y].pb(x);
		deg[x]++;
	}
	q.push({n,dis[n]});
	while(!q.empty()){
		x=q.top().id;
		y=q.top().dis;
		q.pop();
		if(dis[x]!=y) continue;
		for(int i:e[x]){
			if(dis[x]+deg[i]<dis[i]){
				dis[i]=dis[x]+deg[i];
				q.push({i,dis[i]});
			}
			deg[i]--;
		}
	}
	cout<<dis[1]<<endl;
return 0;}
```

---

## 作者：创世游戏科技 (赞：3)

# Keshi in Search of AmShZ

## 题目大意

给定一张有 $n$ 个点和 $m$ 条边的有向图，对于一个时刻，你有两种操作（时刻知道自己的位置）。

1. 断掉一条边，停留在原地。
2. 走随机一条出边。

求保证从 $1$ 到 $n$ 的最小时间。

## 思路解析

从 $1$ 到 $n$ 比较困难，我们考虑在反图上进行操作。

设 $F_i$ 表示从 $i$ 到 $n$ 的最小时间。

如果在 DAG 上做这个问题，我们对一个点连向的点的 $F_i $ 进行排序。假设目前在 $u$ 点，我们要走到 $v$，为了保证一定走到，我们需要把比 $v$ 更劣，即 到满足 $f_v > f_i $ 点的边全部封锁。所需要的代价是
 $\sum_{k \in nxt_i}[f_k > f_j] $ ，然后我们再花费 $ 1 $ 的代价走到 $v$ 即可。


$$F_i = \min_{j \in nxt_i} \{ F_j + \sum_{k \in nxt_i}[f_k > f_j] + 1\}$$

可以用排序实现，复杂度 $O(n\log n)$

然而这道题不一定是 DAG ，所以可能出现环导致反复转移。

如此我们考虑一个转移有价值，当且仅当它作为**未被访问的出边指向的点中最小的一个**进行转移。

考虑使用类 Dijkstra 算法。此时我们对于 $nxt_u$ ，我们需要转移到 $u$。那么正好满足 $f_{nxt_u} $从小到大转移，每次需要封锁的点都变得更少。因为每次必定选择最小的进行转移，转移出的答案一定是更优的。而当出边全部用完之后，这些点就失去了价值。

改造出来
$$F_i = \min_{j \in nxt_i} \{ F_j + outdeg_i + 1\}$$

## 代码实现


```
#include <bits/stdc++.h>
#define prr pair<int,int>
#define int long long
using namespace std;
const int MAXN=3e5+10;
int n,m,in[MAXN],dis[MAXN];
vector<int>G[MAXN];
bool vis[MAXN];
queue<int>q;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        G[v].push_back(u);in[u]++;
    }
    priority_queue<prr,vector<prr>,greater<prr> >q;
    memset(dis,0x3f,sizeof dis);
    q.push({0,n});
    dis[n]=0;
    while(!q.empty()){
        int u=q.top().second;q.pop();
        if(vis[u])continue;
        vis[u]=true;
        
        for(auto j:G[u]){
            
            if(dis[j]>dis[u]+in[j]){
                dis[j]=dis[u]+in[j];
                q.push({dis[j],j});
            }
            in[j]--;
        }
    }
    cout<<dis[1];
    return 0;
}
```

---

## 作者：小超手123 (赞：1)

显然每次断边断当前点相邻的边不会更劣。

题外话：先全部断边再走是错误的。

在 DAG 上是好做的，考虑倒着 dp，记 $f_{u}$ 表示 $u$ 到 $n$ 的最大时间的最小值。转移显然为：
$$
f_{u} = \min_{u \to v} (f_{v}+1+\sum_{u \to z} [f_{z}>f_{v}])
$$
$S$ 集合表示已经确定 $f$ 的点，$T$ 集合表示还未确定 $f$ 的点。最开始 $S$ 为空，$f_{n}=0$。每次把 $T$ 里 $f$ 最小的点 $x$ 加入 $S$ 里（因为此时 $x$ 到 $n$ 的最短路一定不会经过 $T$）。然后建反边进行扩展。

不难发现在反边扩展 $f_{u}$ 被 $f_{v}$ 更新时，$f_{v}$ 一定是从小到大的。这个结论是正确的，当且仅当对于一个松弛 $u \to v_{1}$，在 $T$ 的点 $u$ 肯定无法找到点 $v_{2} \in T$，满足 $f_{v_{2}}<f_{v_{1}}$。 否则说明 $f_{E}\le f_{x}+w_{v_{2} \to A}+w_{A \to B} + w_{B \to C} + \dots+w_{E \to x}<f_{v_{1}}$，其中 $A,B,C,D,E \in T, x \in S$。与 $dis_{v_{1}}$ 在 $T$ 中最小矛盾。

具体实现可以记个 $deg_{u}$，这样 $\sum_{u \to z} [f_{z}>f_{v}]$ 这部分贡献就好算了。

最后一个问题，每次从 $T$ 中取出 $f$ 最小的 $f$ 一定是正确的吗？是的，证明和上面那个结论的证明类似。

---

## 作者：Cure_Wing (赞：1)

[CF1693C Keshi in Search of AmShZ](https://www.luogu.com.cn/problem/CF1693C)

### 思路

考虑这张图确定了下来，那么 Keshi 一定会走最长路。也就是说，他一定会选择可以出发的路径中能到达最长路的那条边。这启发我们倒着搜，建出原图的反图。

我们将反图上的边看作状态之间的转移，于是设 $f_i$ 表示点 $i$ 到点 $n$ 的最长时间。如果选择了一条出边 $i\to u$，那么必要条件是经过 $u$ 是一条最长路，可以看作是连向更长路的边被删除了。状态转移方程为 $f_i=\min\limits_{u\in to_i}\{f_u+1+\sum\limits_{k\in to_i}[f_k>f_u]\}$，边界条件显然 $f_n=0$。

但是如果这样转移的话，复杂度是起飞的。容易发现瓶颈在于每一次都要找出一个点所能转移到的点。那么我们想，能不能在反图上跑时就把状态转移出去呢？此时有一个新的问题出现了，我们直接倒着转移的话，无法确定有多少个 $f_k>f_u$。此时套路性地钦定转移顺序，让 $f_u$ 最小的最先转移，然后按从小到大的顺序依次转移，这样 $\sum\limits_{k\in to_i}[f_k>f_u]$ 就满足了单调性，可以开一个数组维护这个值。

那么如何满足让最小的最先转移呢？我们贪心维护最小的 $f_i$，每次优先转移值最小的 $f_i$ 去更新能到达它的点就可以了。

对于最小的 $f_i$ 的维护，可以用优先队列，时间复杂度 $O((n+m)\log m)$。而观察到 $f_i$ 关于转移顺序单调递增，答案又一定不超过 $m$，于是可以用桶来维护，时间复杂度优化为 $O(n+m)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using std::cin;using std::cout;
constexpr int N=200005;
int n,m,u,v,f[N],c[N];
std::vector<int>edge[N],l[N];
bool vis[N];
signed main(){
 	freopen("c.in","r",stdin);
 	freopen("c.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		cin>>u>>v;
		edge[v].push_back(u);//建反图
		++c[u];//统计转移时的删边的代价
	}
	for(int i=1;i<=n;++i) f[i]=N;
	l[0].push_back(n);
	for(int i=0;i<=m;++i)//用桶维护
		for(int j:l[i]){
			if(vis[j]) continue;
			vis[j]=1;f[j]=i;//贪心选取最小的 f[i]
			for(int k:edge[j]){//f[j]+1+c[k]-1=f[j]+c[k]
				l[f[j]+c[k]].push_back(k);//把新的 f[i] 插入桶
				--c[k];//小的 f[u] 显然不会对大的做贡献，于是减一
			}
		}
	cout<<f[1];
	return 0;
}
```

---

## 作者：xujunlang2011 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1693C)

## 思路
假设从 $u$ 出发，可到达的点数量为 $k$，到 $n$ 的最小距离为 $dis_u$，

那么从 $u$ 走到 $n$ 的最小代价，代价是：

$$dis_u=\min\limits_{v=1}^k(dis_v+1+\sum\limits_{x=1}^k[dis_v<dis_x])$$

这样就可以跑最短路了。

因为这题没有负边权，所以可以跑 Dijkstra。

又因为 Dijkstra 可以用堆优化，所以我们可以开一个数组来存每个点的入度，每次查到这个点时，将入度减 $1$。

最后就可以正常跑 Dijkstra 了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, M = 2e5 + 5, intm = 2147483647;
int n, m, s, x, y, z, cnt, dis[N], vis[N], hc[N];
bool f[N];
priority_queue <pair<int, int>> q;
struct node
{
    int u, v, h;
}a[M];
void add(int p, int q)
{
    a[++cnt].u = p;
    a[cnt].v = q;
    a[cnt].h = hc[p];
    hc[p] = cnt;
}
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
	{
		dis[i] = intm;
	}
	dis[n] = 0;
	for (int i = 1;i <= m;i++)
	{
		cin >> x >> y;
		add(y, x);
		vis[x]++;
	}
    q.push({-dis[n], n});
	while (q.size())
	{
		int s = q.top().second;
        q.pop();
	    if (f[s])
	    {
	        continue;
	    }
        for (int j = hc[s];j != 0;j = a[j].h)
        {
            int v = a[j].v;
            if (dis[v] > vis[v] + dis[s])
            {
                dis[v] = vis[v] + dis[s];
                if (!f[v])
                {
                    q.push({-dis[v], v});
                }
            }
            vis[v]--;
		}
		f[s] = 1;
	}
    cout << dis[1];
	return 0;
} 
```
本篇题解思路参考了[这篇题解](https://www.luogu.com.cn/blog/xiaomuchong/solution-cf1693c)。

---

## 作者：VitrelosTia (赞：0)

非常深刻的题，把不会 Dijkstra 的我击败了。记后继点集为 $to_v$，出度为 $d_v$。

首先考虑 dp，由于终态是确定的，考虑设 $f_v$ 表示 $v$ 到 $n$ 的最小时间（为什么用 $v$？），我们先考虑在 dag 上的情况，将 $u\in to_v$ 的 $f_u$ 排序，我们肯定考虑去掉更大的边，那么有转移 $f_v = \displaystyle \min_{k=0}^{d_v}(f_k+(d_v-k)+1)$，这里的 $f_u$ 是排过序的，含义为我留下 $f_u$ 前 $k$ 小的。稍作思考，我们可以改写成更直观的形式 $f_v = \displaystyle \min_{u\in to_v}(f_u+d_v-rnk_u+1)$，$rnk$ 就是上面按 $f_u$ 排序的排名。

然后考虑一个有环的图，我们先建反图。我们考虑 Dijkstra 算法，因为你这个 $d_v-rnk_u+1$ 是正的并且是可以在 Dijkstra 的过程中直接求出的，所以我们把它当作边权就行了。

所以为什么用 $v$ 呢，因为 Dijkstra 的时候 $u$ 是已经知道最短路的，所以要用 $u$ 去更新 $v$。

```cpp
const int N = 2e5 + 5;
int n, m, d[N], f[N]; vector <int> g[N];
struct Node { 
    int u, d;
    bool operator < (const Node &x) const { return d > x.d; }
}; priority_queue <Node> q; int dis[N]; bool vis[N];

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[v].push_back(u); d[u]++;
    } memset(dis, 0x3f, sizeof dis); q.push({n, dis[n] = 0});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue; vis[u] = true;
        for (int v : g[u]) {
            if (dis[v] > dis[u] + d[v]) q.push({v, dis[v] = dis[u] + d[v]});
            d[v]--;
        }
    } cout << dis[1];
    return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

考虑倒着 dp。设 $f_i$ 表示从 $i$ 到 $n$ 最优策略下最多走多少步。考虑到若要保证从 $i$ 点走到 $j$ 点，那么需要先把所有比走到 $j$ 点更差的边全部断掉，才能保证从 $i$ 走到 $j$ 一定为最差情况。那么 dp 就是：初始条件为 $f_n=0$，转移对于每一个 $i\in[1,n)$，都有 $f_i=\min\limits_{\text{There is an edge from }i\text{ to }j}(f_j+c_{i,j}+1)$，其中 $c_{i,j}$ 表示从 $i$ 点走到 $j$ 点最少要断多少条 $i$ 点的出边。

$c_{i,j}$ 是容易计算的，显然有：

$$c_{i,j}=\sum\limits_{\text{There is an edge from }i\text{ to }k}[f_j<f_k]$$

于是可以直接暴力转移，时间复杂度为 $O(nm)$。考虑一个很厉害的优化：考虑到 $c_{i,j}+1>0$，因此图中不存在负权边和负权环，考虑用 dijkstra 维护，每一次从堆顶端取出当前 $f$ 权值最小的结点。此时可以证明 $c_{i,j}$ 的值一定单调不递增，且每一次递减的值不会超过 $1$，而且还可以发现初始 $c_{i,j}$ 的值其实就是 $\deg(i)$。因此可以直接简单的在 dijkstra 的过程中暴力维护，时间复杂度为 $O(m\log m)$，可以通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200100;
vector<int> adj[N];
int deg[N], dis[N];
struct Node {
    int dis, u;
    bool operator<(const Node &r) const {
        return dis > r.dis;
    }
};
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        adj[b].emplace_back(a);
        ++deg[a];
    }
    priority_queue<Node> q;
    memset(dis, 0x3f, sizeof dis);
    q.push({dis[n] = 0, n});
    while (q.size()) {
        auto [Dis, u] = q.top();
        q.pop();
        if (dis[u] >= Dis) {
            for (auto &v : adj[u])
                if (dis[v] > dis[u] + deg[v]) q.push({dis[v] = dis[u] + deg[v]--, v});
                else --deg[v];
        }
    }
    cout << dis[1] << '\n';
    return 0;
}
```

---

