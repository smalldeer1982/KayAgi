# [JOI 2018 Final] 月票购买 / Commuter Pass

## 题目描述

JOI 君住在一个有 $N$ 个车站的城市。车站编号为 $1$ 至$N$。编号为 $1$ 至 $M$ 的有 $M$ 条铁路。铁路 $i$（$1 \leq i \leq M$）双向连接 $A_i$ 站和 $B_i$ 站，票价为 $C_i$ 日元。  
JOI 君住在 $S$ 站附近，去 $T$ 站附近的 IOI 高中。他打算买一张连接这两个站的通勤票。当他购买通勤票时，他需要选择一条成本最低的 $S$ 站和 $T$ 站之间的路线。使用此通勤票，他可以沿任何方向乘坐所选路线中包含的任何铁路，而无需额外费用。  
JOI 君经常去 $U$ 站和 $V$ 站附近的书店。因此，他想买一张通勤票，这样从 $U$ 站到 $V$ 站的费用可以降到最低。  
当他从 $U$ 站移动到 $V$ 站时，他首先选择了一条从 $U$ 站到 $V$ 站的路线，那么他需要支付的车费是：  
- $0$ 日元：如果铁路 $i$ 包含在他购买的通勤票时选择的路线中，或者，  
- $C_i$ 日元：如果铁路 $i$ 不包含在他购买通勤票时选择的路线中。  

上述票价的总和就是从 $U$ 站到 $V$ 站的成本。  
他想知道如果他在购买通勤票时选择合适的路线，从 $U$ 站到 $V$ 站的最低成本。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，  
$2 \leq N \leq 10^5$，$1 \leq M \leq 2×10^5$，$1 \leq S \leq N$，$1 \leq T \leq N$，$1 \leq U \leq N$，$1 \leq V \leq N$，$S {=}\mathllap{/\,} T$，$U {=}\mathllap{/\,} V$，$ S{=}\mathllap{/\,} U$ 或 $T {=}\mathllap{/\,} V$，$1 \leq A_i \leq B_i \leq N$（$1 \leq i \leq M$）。对于每 $1 \leq i < j \leq M$，$A_i {=}\mathllap{/\,} A_j$ 或 $B_i {=}\mathllap{/\,} B_j$，$1 \leq C_i \leq 10^9$（$1 \leq i \leq M$）。JOI 君可以从任何车站移动到任何其他车站乘坐铁路。  
- Subtask $1$（$16$ points）：$S=U$。  
- Subtask $2$（$15$ points）：从 $S$ 站到 $T$ 站有一条成本最低的唯一路线。  
- Subtask $3$（$24$ points）：$N \leq 300$。  
- Subtask $4$（$45$ points）：没有额外的限制。  
#### 样例说明  
**对于样例 $1$**：JOI 君在购买通勤票时只能选择一条路线：$1$ 号站 → $2$ 号站 →$3$ 号站 → $5$ 号站 → $6$ 号站。为了尽量减少从 $1$ 号站到 $4$ 号站的成本 ，他选择以下路线：$1$ 站 → $2$ 站 → $3$ 站 → $5$ 站 → $4$ 站。选择这条路线时，他需要支付的车费为。  
- $2$ 日元用于车站 $4$ 和车站 $5$ 的铁路 $5$，以及，  
- $0$ 日元：其他铁路。  
  
**对于样例 $2$**：JOI 君从 $3$ 号站移动到 $6$ 号站时，不使用通勤票。  
#### 题目说明：  
来源于 The 17th Japanese Olympiad in Informatics (JOI 2017/2018) Final Round 的 [T4：Commuter Pass](https://www.ioi-jp.org/joi/2017/2018-ho/2018-ho-t4-en.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。  
#### Hack 说明  
[@gaojunqing](https://www.luogu.com.cn/user/536005) 于 2021 年 11 月 6 日向供题人提供一组 hack 数据，经过多次检验后于 2021 年 11 月 7 日加入到本题测试数据中。  
出于对该 JOI 原题的尊重与体验考虑，一律所加入的 hack 数据均不做分值改变，即满分依然为 100 分，新增 hack 数据单独放置在 Subtask #5 ，且分数为 0 分。即如通过原所有测试数据而未通过 hack 数据，将获得 100 分但不能 AC，当且仅当通过全部测试数据方可 AC。

## 样例 #1

### 输入

```
6 6
1 6
1 4
1 2 1
2 3 1
3 5 1
2 4 3
4 5 2
5 6 1```

### 输出

```
2```

## 样例 #2

### 输入

```
6 5
1 2
3 6
1 2 1000000000 
2 3 1000000000
3 4 1000000000
4 5 1000000000
5 6 1000000000```

### 输出

```
3000000000```

## 样例 #3

### 输入

```
8 8
5 7
6 8
1 2 2
2 3 3
3 4 4
1 4 1
1 5 5
2 6 6
3 7 7
4 8 8```

### 输出

```
15```

## 样例 #4

### 输入

```
5 5
1 5
2 3
1 2 1
2 3 10
2 4 10
3 5 10
4 5 10```

### 输出

```
0```

## 样例 #5

### 输入

```
10 15
6 8
7 9
2 7 12
8 10 17
1 3 1
3 8 14
5 7 15
2 3 7
1 10 14
3 6 12
1 5 10
8 9 1
2 9 7
1 4 1  
1 8 1
2 4 7
5 6 16```

### 输出

```
19```

# 题解

## 作者：VainSylphid (赞：8)

## 思路

首先我们考虑，选定了一条 $S$ 到 $T$ 的最短路后， $U$ 到 $V$ 的最短路是什么样的。它有可能不经过 $S$ 到 $T$ 的最短路，也有可能经过。

不难发现，如果 $U$ 到 $V$ 的最短路经过 $S$ 到 $T$ 的最短路，那么一定是一条形如 $U\rightarrow A\rightarrow B\rightarrow V$ 的路径，其中有且仅有 $A\rightarrow B$ 在 $S$ 到 $T$ 的最短路上。

证明很简单，假如有一条形如 $U\rightarrow A\rightarrow B\rightarrow C\rightarrow D\rightarrow V$ 的路径，其中 $A\rightarrow B$、$C\rightarrow D$ 在 $S$ 到 $T$ 的最短路上，$B\rightarrow C$ 不在在 $S$ 到 $T$ 的最短路上，由于原图边权都是正的，将 $B\rightarrow C$ 的路径替换为 $S$ 到 $T$ 的最短路上 $B\rightarrow C$ 的路径一定更优。

换言之，我们可以 $O(n^2)$ 枚举一条 $P\rightarrow Q$ 的路径，如果它位于 $S$ 到 $T$ 的最短路上，即 $dis_{S\rightarrow P}+dis_{P\rightarrow Q}+dis_{Q\rightarrow T}=dis_{S\rightarrow T}$，那么就用 $dis_{U\rightarrow P}+dis_{Q\rightarrow V}$ 和 $dis_{U\rightarrow Q}+dis_{P\rightarrow V}$ 更新最短路。有两种方案的原因是最短路有可能是在 $S$ 到 $T$ 的最短路上反方向行走的。

考虑优化。显然所有在某一条最短路径上的边构成了一个 DAG，那么我们就可以跑一遍 dp 求出 DAG 上能到达节点 $D$ 的所有节点中，到 $U$ 的最小距离 $low_D$，然后用 $low_D+dis_{D\rightarrow V}$ 更新答案即可。还是由于$U$ 到 $V$ 的最短路可能 $S$ 到 $T$ 的最短路上反方向行走的，需要对反图也跑一次。

代码流程如下：

* 跑四次 dijkstra 计算 $S$、$T$、$U$、$V$ 到每一个点的最短路，先用原图中 $U$ 到 $V$ 的最短路。
* 找出在 $S$ 到 $T$ 的最短路上的边，分别用原来的边和反边建一张 DAG。
* 在正图和反图上分别跑一次按拓扑序的 dp 计算 $U$ 到每个最短路上节点的最小距离，然后更新答案。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3fLL
using namespace std;
ll n,m,s,t,u,v,x[200005],y[200005],z[200005],c1[100005],c2[100005],c3[100005],c4[100005],ans;
struct graph{
    struct edge{
	    ll v,w,nxt;
    }e[400005];
    ll h[100005],pos,dis[100005],vis[100005],du[100005],mind[100005],f[100005];
    void add(ll u,ll v,ll w)
    {
	    e[++pos] = {v,w,h[u]},h[u] = pos,du[v]++,f[u] = f[v] = 1;
    }
    struct node{
    	ll w,d;
    	bool operator <(const node &b) const
    	{
    		return d > b.d;
    	}
    };
    void dijkstra(ll s)
    {
    	priority_queue<node> q;
    	memset(dis,0x3f,sizeof dis),memset(vis,0,sizeof vis),q.push({s,0}),dis[s] = 0;
    	while(q.size())
    	{
    		node tmp = q.top();
    		q.pop(),vis[tmp.w] = 1;
	    	for(int i = h[tmp.w];i;i = e[i].nxt)
    			if(!vis[e[i].v] && dis[e[i].v] > tmp.d + e[i].w)
    			    q.push({e[i].v,tmp.d + e[i].w}),dis[e[i].v] = tmp.d + e[i].w;
    	}
    }
    void solve()
    {
    	queue<ll> q;
    	for(ll i = 1;i <= n;i++)
    	{
    	    mind[i] = c3[i];
    	    if(!du[i])
    	        q.push(i);
		}
    	while(q.size())
    	{
    		ll tmp = q.front();q.pop();
    		ans = min(ans,mind[tmp] + c4[tmp]);
    		for(ll i = h[tmp];i;i = e[i].nxt)
    		{
    		    du[e[i].v]--,mind[e[i].v] = min(mind[e[i].v],mind[tmp]);
    		    if(du[e[i].v] == 0)
    		        q.push(e[i].v);
			}
		}
	}
}g1,g2,g3;
int main()
{
	scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&s,&t,&u,&v);
	for(ll i = 1;i <= m;i++)
	    scanf("%lld%lld%lld",&x[i],&y[i],&z[i]),g1.add(x[i],y[i],z[i]),g1.add(y[i],x[i],z[i]);
	g1.dijkstra(s);
	for(ll i = 1;i <= n;i++)
	    c1[i] = g1.dis[i];
	g1.dijkstra(t);
	for(ll i = 1;i <= n;i++)
	    c2[i] = g1.dis[i];
	g1.dijkstra(u);
	for(ll i = 1;i <= n;i++)
	    c3[i] = g1.dis[i];
	g1.dijkstra(v);
	for(ll i = 1;i <= n;i++)
	    c4[i] = g1.dis[i];
	ans = c3[v];
	for(ll i = 1;i <= m;i++)
	{
	    if(c1[x[i]] + z[i] + c2[y[i]] == c1[t])
	        g2.add(x[i],y[i],0),g3.add(y[i],x[i],0);
	    else if(c1[y[i]] + z[i] + c2[x[i]] == c1[t])
	        g2.add(y[i],x[i],0),g3.add(x[i],y[i],0);
	}
	g2.solve(),g3.solve();
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：__stick (赞：8)

## 题意
给出一张无向图，问将 $s$ 到 $ t$ 某条最短路上所有边权值置为 $0$ 后 $u\to v$ 的最短路。
## 思路

先跑出来 $s,t,u,v$ 各自的单源最短路，然后朴素的想法是先判断不经过最短路的情况，这种直接跑即可。

然后枚举 $s\to t$ 最短路上的两个点，求出 $u,v$ 到他们距离之和。

这样复杂度明显是 $O(n^2)$ 的，我们考虑优化，先只枚举最短路径上一个的点，设为 $x$ ，然后问题就是另外一个点的选取。

不难发现我们对 $s$ 为源点的单源最短路建出来最短路树，再加上不在树上但是可以位于最短路上的边，就形成了一个只有一个源点 $s$ 的 DAG ，则在这个 DAG 上能到达 $x$ 的点都是合法的。满足存在一条最短路径同时经过这两个点。

而对于 $t$  为源点的最短路径同理。

注意到并不需要显示建出来这个 DAG，直接在跑最短路的时候顺便 dp 即可得到答案。

## code

```cpp
const int MAXN=2e5+10;
vector<pii>e[MAXN];

int n;
void dijk(int s,ll dis[])
{
    memset(dis,0x3f,8*MAXN);
    dis[s]=0;
    priority_queue<pll>q;
    q.emplace(0,s);
    vector<bool>vis(n+1);
    while(!q.empty())
    {
        int u=q.top().second;q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(auto&[v,w]:e[u])if(cmin(dis[v],dis[u]+w))q.emplace(-dis[v],v);
    }
}
void dijk2(int s,ll dis[],ll mmin[])
{
    memset(dis,0x3f,8*MAXN);
    dis[s]=0;
    priority_queue<pll>q;
    q.emplace(0,s);
    vector<ll>val(mmin,mmin+n+1);
    vector<bool>vis(n+1);
    while(!q.empty())
    {
        int u=q.top().second;q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(auto&[v,w]:e[u])
        {
            if(cmin(dis[v],dis[u]+w))mmin[v]=val[v],q.emplace(-dis[v],v);
            if(dis[v]==dis[u]+w)cmin(mmin[v],mmin[u]);
        }
        
    }
}
ll d1[MAXN],d2[MAXN];
int fa1[MAXN],fa2[MAXN];
ll d3[MAXN],d4[MAXN];
ll mmin1[MAXN],mmin2[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int m;cin>>n>>m;
    int s,t,x,y;
    cin>>s>>t>>x>>y;
    for(int i=1,u,v,w;i<=m;i++)cin>>u>>v>>w,e[u].emplace_back(v,w),e[v].emplace_back(u,w);
    dijk(x,d3),dijk(y,d4);
    for(int i=1;i<=n;i++)mmin1[i]=mmin2[i]=d4[i];
    dijk2(s,d1,mmin1),dijk2(t,d2,mmin2);
    ll len=d1[t];
    ll ans=d3[y];
    for(int i=1;i<=n;i++)if(d1[i]+d2[i]==len)
    {
        cmin(ans,mmin1[i]+d3[i]);
        cmin(ans,mmin2[i]+d3[i]);
    }
    cout<<ans;
	return 0;
} 

```


---

## 作者：7KByte (赞：8)

比较套路的题目。

首先我们需要求出 $S\to T$ 的最短路可行边。

我们分别以 $S/T$ 为起点，跑最短路得到 $dist_1,dist_2$ ，如果两端 $dist$ 之和加上边的长度为最短路，则当前边出现在一条最短路中。

现在从 $U\to V$ ，免费的一定是一条连续的路径。

而这条免费的路径要么是顺着最短路径图走一段，要么是逆着最短路径图走一段，而不能同时有顺向或逆向走。

简单想了一个贪心，大概是先求出 $U/V$ 到最短路径图的最近点 $P,Q$，再从 $P/Q$ 为起点出发顺向或逆向找到最近公共可达点，分别以 $P,Q$ 为起点正图反图都跑一遍最短路。

码了 $10$ 分钟感觉太麻烦了，不如直接分层图。第 $1$ 层和第 $4$ 层分别表示还未开始免费路径，已经结束免费路径。第 $2$ 层表示免费路径顺着走，这一层就是最短路图，第 $3$ 层表示免费路径逆着走，就是最短路图的反图。

最后再跑一遍最短路即可，一共跑三遍最短路，时间复杂度 $\mathcal{O}((N+M)\log (N+M))$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 400005
#define int long long 
using namespace std;
int n,m,d[N],c[N],mk[N],h[N],tot,s,t,u,v;
struct edge{int to,nxt,val;}e[N];
void add(int x,int y,int z){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;}
typedef pair<int,int> Pr;
priority_queue<pair<int,int>>q;
vector<Pr>a[N];
void ins(int x,int y,int z){a[x].push_back(make_pair(y,z));}
void dij(){
	memset(d,0x3f,sizeof(d));
	d[s]=0;q.push(make_pair(0,s));
	while(!q.empty()){
		int x=q.top().second;q.pop();mk[x]=1;
		for(int i=h[x];i;i=e[i].nxt)if(d[x]+e[i].val<d[e[i].to])
			d[e[i].to]=d[x]+e[i].val,q.push(make_pair(-d[e[i].to],e[i].to));
		while(!q.empty()&&mk[q.top().second])q.pop();
	}
	memset(c,0x3f,sizeof(c));
	memset(mk,0,sizeof(mk));
	c[t]=0;q.push(make_pair(0,t));
	while(!q.empty()){
		int x=q.top().second;q.pop();mk[x]=1;
		for(int i=h[x];i;i=e[i].nxt)if(c[x]+e[i].val<c[e[i].to])
			c[e[i].to]=c[x]+e[i].val,q.push(make_pair(-c[e[i].to],e[i].to));
		while(!q.empty()&&mk[q.top().second])q.pop();
	}
	rep(x,1,n)
		for(int i=h[x];i;i=e[i].nxt)
			if(d[x]+e[i].val+c[e[i].to]==d[t]){
				ins(x+n,e[i].to+n,0),ins(e[i].to+n+n,x+n+n,0);
			}
}
void solve(){
	memset(d,0x3f,sizeof(d));
	memset(mk,0,sizeof(mk));
	d[u]=0;q.push(make_pair(0,u));
	while(!q.empty()){
		int x=q.top().second;q.pop();mk[x]=1;
		for(auto w:a[x]){
			int y = w.first,z = w.second;
			if(d[x] + z < d[y])d[y] = d[x] + z,q.push(make_pair(-d[y],y));
		}
		while(!q.empty()&&mk[q.top().second])q.pop();
	}
	printf("%lld\n",d[v+n+n+n]);
}
signed main(){
	scanf("%lld%lld",&n,&m);
	scanf("%lld%lld%lld%lld",&s,&t,&u,&v);
	rep(i,1,m){
		int x,y,z;scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);add(y,x,z);
		ins(x,y,z);ins(y,x,z);
		ins(x+n+n+n,y+n+n+n,z);ins(y+n+n+n,x+n+n+n,z);
	}
	rep(i,1,n)ins(i,i+n,0),ins(i,i+n+n,0),ins(i+n,i+n+n+n,0),ins(i+n+n,i+n+n+n,0);
	dij();solve();
	return 0;
}
```

---

## 作者：dyc2022 (赞：4)

JOI 的一道好题。
***
### 题意简述

给定一个无向带权图，和节点 $S,T,U,V$。你可以将 $S \rightarrow T$ 的一条最短路上的所有边权修改为 $0$，然后最小化 $U \rightarrow V$ 的最短路长度。

### Solution

首先，我们可以处理出所有可能出现在 $S$ 到 $T$ 的最短路的边（以下简称 **可能边**）。一条边 $(U_i,V_i,W_i)$ 可能出现在最短路中，当且仅当 $\text{dis}_{S,U_i} + W_i + \text{dis}_{V_i,T} = \text{dis}_{S,T}$，这一点显然。

我们可以把每一条可能边按照最短路经过它的方向定向。有一个显然的结论，那就是由可能边组成的图是一张 DAG。因为在一个正边权图中，一条最短路是不可能出现环的。

那么我们可以把这个问题转化为一个 DAG 上 dp 问题。我们可以预处理出 $U$ 和 $V$ 到每一个节点的最短路。然后我们在 DAG 上通过 dp 求出每一个节点 $i$ 所能到达的节点 $k_i$，使 $\text{dis}_{k_i,V}$ 最小。那么最后的答案就是 $\min \text{dis}_{U,i}+ \text{dis}_{k_i,V}$。

### AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 100006
using namespace std;
vector<pair<int,int> > G[N];
int n,m,s1,t1,s2,t2;
int u[N<<2],v[N<<2],w[N<<2],dis[4][N],vis[N],ans[N],in[N];
struct Node{int u,d;};
bool operator >(Node x,Node y){return x.d>y.d;}
priority_queue<Node,vector<Node>,greater<Node> > q;
void dij(int s,int *D)
{
    for(int i=1;i<=n;i++)vis[i]=0,D[i]=1e15;
    D[s]=0;
    q.push({s,0});
    while(!q.empty())
    {
        Node now=q.top();q.pop();
        int u=now.u;
        if(vis[u])continue;
        vis[u]=1;
        for(auto v:G[u])
        {
            if(vis[v.first])continue;
            if(D[u]+v.second<D[v.first])
            {
                D[v.first]=D[u]+v.second;
                q.push({v.first,D[v.first]});
            }
        }
    }
    //for(int i=1;i<=n;i++)cout<<D[i]<<' ';puts("");
}
void topo(int s)
{
    queue<int> q2;
    q2.push(s);
    //cout<<s<<':'<<ans[s]<<endl;
    while(!q2.empty())
    {
        int now=q2.front();q2.pop();
        for(auto v:G[now])
        {
            //cout<<"topu: "<<now<<' '<<v.first<<endl;
            in[v.first]--;
            ans[v.first]=min(ans[v.first],ans[now]);
            if(!in[v.first])q2.push(v.first);
        }
    }
}
int solve()
{
    for(int i=1;i<=(m<<1);i++)ans[i]=1e15;
    for(int i=1;i<=n;i++)G[i].clear(),in[i]=0;
    for(int i=1;i<=(m<<1);i++)G[u[i]].push_back({v[i],w[i]});
    dij(s1,dis[0]),dij(t1,dis[1]),dij(s2,dis[2]),dij(t2,dis[3]);
    for(int i=1;i<=n;i++)G[i].clear();
    set<int> points;
    for(int i=1;i<=(m<<1);i++)
    {
        if(dis[0][u[i]]+w[i]+dis[1][v[i]]==dis[0][t1])
        {
            G[v[i]].push_back({u[i],w[i]});
            in[u[i]]++;
            points.insert(u[i]),points.insert(v[i]);
        }
    }
    for(auto it=points.begin();it!=points.end();it++)
        ans[*it]=dis[3][*it];
    for(auto it=points.begin();it!=points.end();it++)
        if(!in[*it])topo(*it);
    //for(int i=1;i<=n;i++)cout<<ans[i]<<' ';cout<<endl;
    int minn=1e15;
    for(auto it=points.begin();it!=points.end();it++)minn=min(minn,dis[2][*it]+ans[*it]);
    //cout<<"["<<minn<<"]\n";
    return min(minn,dis[2][t2]);
}
main()
{
    scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&s1,&t1,&s2,&t2);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
        u[i+m]=v[i],v[i+m]=u[i],w[i+m]=w[i];
    }
    int ans=solve();
    swap(s1,t1);
    ans=min(ans,solve());
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：船酱魔王 (赞：2)

# P7669 [JOI2018] Commuter Pass 题解

## 题意回顾

$ n $ 点 $ m $ 边无向图，你可以选择一条 $ s $ 到 $ t $ 的最短路将路径上边权覆盖为 $ 0 $，以最小化 $ u $ 到 $ v $ 在新图上的最短距离并输出这个距离。

$ 2 \le n \le 10^5 $，$ 1 \le m \le 2 \times 10^5 $。

## 分析

可以构造分层图，层间边连全 $ 1 $ 边，层内不连边，把最短路径数卡得很大，因此枚举每条最短路是行不通的。

考虑我们的 $ u $ 到 $ v $ 的路径与 $ s $ 到 $ t $ 的最短路的公共部分，这两条路径第一次和最后一次相交的点之间的代价最小全为 $ 0 $（因为可以走 $ s $ 到 $ t $ 最短路上的边），因此枚举 $ s,t $ 最短路上的两点 $ x,y $，求出 $ u $ 到 $ x $，$ x $ 到 $ v $ 的距离和的最小值即可，$ O(n^3) $ 做法可以拿到 $ 24 $ 分的好成绩。

我们发现，$ x $ 到 $ y $ 之间的边是最短路的一部分，我们可以通过判断 $ s $ 到 $ x $，$ t $ 到 $ y $，$ x,y $ 之间边的长度来判断 $ x,y $ 之间的边是否在某条 $ 0 $ 权最短路上。

但这样可能会同时算多条最短路，怎么办？考虑证明一个结论：如果沿着最短路边走的话，只能一直正（从 $ s $ 到 $ t $）走或一直反走，具有最优性和正确性。

如果一直按照一个方向走的话，那么显然我们走的就是最短路的一部分，有正确性；因为我们只会上最短路 $ 1 $ 次，如果换方向的话，显然会走重一条边多次，故考虑拆点设计状态，拆为没上过 $ 0 $ 权边、在 $ 0 $ 权边上且正走或反走（两种不同的状态）、已经下 $ 0 $ 权边四种状态，建图跑最短路即可。

可以封装最短路寻找过程。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long
using namespace std;
const int N = 1e5 + 5;
const long long inf = (ll)1e18 + 5;
int n, m;
int s, t, u, v;
struct node {
    int pt;
    ll lt;
};
node make(int pt, ll lt) {
    node res;
    res.pt = pt, res.lt = lt;
    return res;
}
bool operator<(node p1, node p2) {
    if(p1.lt != p2.lt) return p1.lt > p2.lt;
    return p1.pt > p2.pt;
}
vector<node> g[N];
priority_queue<node> que;
vector<node> f[N * 4];
ll dis[N * 4], ds[N], dt[N];
int vis[N * 4];
void dijkstra(int nn, int ss, vector<node> gf[]) {
    for(int i = 1; i <= nn; i++) dis[i] = inf, vis[i] = 0;
    dis[ss] = 0;
    while(!que.empty()) que.pop();
    que.push(make(ss, 0));
    while(!que.empty()) {
        node now = que.top();
        que.pop();
        int ux, vx, wx;
        ux = now.pt;
        if(vis[ux] == 1) continue;
        vis[ux] = 1;
        for(int i = 0; i < gf[ux].size(); i++) {
            vx = gf[ux][i].pt;
            wx = gf[ux][i].lt;
            if(dis[ux] + wx < dis[vx]) {
                dis[vx] = dis[ux] + wx;
                que.push(make(vx, dis[vx]));
            }
        }
    }
}
int id(int x, int typ) {//1-unused,2-back,3-front,4-used
    return (x - 1) * 4 + typ;
}
void link(int x, int y, int z) {
    f[x].push_back(make(y, z));
}
int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &s, &t, &u, &v);
    int x, y, z;
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        g[x].push_back(make(y, z)), g[y].push_back(make(x, z));
    }
    dijkstra(n, s, g);
    for(int i = 1; i <= n; i++) ds[i] = dis[i];
    dijkstra(n, t, g);
    for(int i = 1; i <= n; i++) dt[i] = dis[i];
    for(int i = 1; i <= n; i++) {
        link(id(i, 1), id(i, 2), 0);
        link(id(i, 1), id(i, 3), 0);
        link(id(i, 2), id(i, 4), 0);
        link(id(i, 3), id(i, 4), 0);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < g[i].size(); j++) {
            x = i, y = g[i][j].pt, z = g[i][j].lt;
            link(id(x, 1), id(y, 1), z);
            link(id(x, 4), id(y, 4), z);
            if(ds[x] + z + dt[y] == ds[t]) link(id(x, 3), id(y, 3), 0);
            if(dt[x] + z + ds[y] == ds[t]) link(id(x, 2), id(y, 2), 0);
        }
    }
    dijkstra(n * 4, id(u, 1), f);
    printf("%lld\n", dis[id(v, 4)]);
    return 0;
}
```

---

## 作者：PCCP (赞：2)

## 赛时思路

赛时第一眼看到这题无感，但是我的同学跟我说这题和我做过的一题很像，努力想了很久，发现是和[P2149 [SDOI2009] Elaxia的路线](https://www.luogu.com.cn/problem/P2149)这题很像，当时我还发了个讨论所以印象深刻，其实这两个只有一点区别吧，核心思想都是把求最短路当成 DP 来考虑。

很简单的想法是先跑一遍最短路，然后枚举每一条最短路，把路径上每一条边的边权修改为 $ 0 $，最后求一遍最短路，因为我根本没想暴力，所以我盲猜时间复杂度是 $ O(n^2\log_2{n}) $。

每次修改一次时间复杂度太大了，直接一次性把所有最短路构成的最短路修改一遍，只要最短路不会重就可以了，这个思路非常简单。问题在于怎么实现。

------------

引理：在无负权边的无向图求单源最短路，所有可能的最短路方案构成的一定是 DAG。

![](https://cdn.luogu.com.cn/upload/image_hosting/ztbav02b.png)

这里的方向简单的来说是指每一个点的最短路是从哪些点所转移过来的，这个转移是有方向的，从离起点近的一端指向离终点近的一端。（堆优化最短路算法实质属于贪心，贪心属于广义上的动态规划，贪心只是每次转移可以找到最优或更优解）

为什么呢？因为存在环的话就说明有负边权了。

------------

以下把这个 DAG 在原无向图的对应边的集合成为最短路子图，单条最短路的方向抽象成所有最短路方案的方向。

因为没有环，所以单条最短路是有方向的，你可以发现只要你求 $ U $ 与 $ V $ 间的最短路时走了一条和 $ S $ 与 $ T $ 间的最短路子图方向相同的边，又走了一条方向相反的边就说明你走了两条不同的 $ S $ 与 $ T $ 间的最短路方案。

那这看起来就很简单了，把求最短路当成 DP 给每个点加一维表示从相对于 $ S $ 与 $ T $ 间的最短路方向的正/反向或最短路子图外的边转移来的，再分类讨论转移即可。我赛时没有继续想，因为留给我实现的时间并不多了，于是写假只得了 20 分。

## 正解接下来的内容

不仅如此，还需要注意的是，我们求出来的 $ U $ 与 $ V $ 间的最短路还有可能会在走过和进入 $ S $ 与 $ T $ 间的最短路子图时的方向不同的边后，再走过一条方向相同的边；或者离开最短路子图又回到最短路子图，相当于可以选几个不同的方案赋边权为 $ 0 $，那这也是要 DP 实现的。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/v69nflc5.png)

所以你还需要判断他到底有没有走完当前选择的最短路方案，那我们就要给他加一维状态，表示有没有走完当前最短路方案。

很容易推知我们最后求出来的 $ U $ 与 $ V $ 间的最短路如果包含一个 $ S $ 与 $ T $ 间的最短路方案，那这个 $ S $ 与 $ T $ 间的最短路方案在 $ U $ 与 $ V $ 间的最短路路径上一定是连续的一段，因为 $ S $ 与 $ T $ 间的最短路边权都变成 $ 0 $ 了，那走这个 $ S $ 与 $ T $ 间的最短路方案一定是最优的。

但是这样状态数太多了，读者实现的不够好就会 TLE。于是压缩状态。

设 DP 数组为 $ f_{i,j} $，$ j\in[0,3] $，$ j=0 $ 表示转移到当前点是还没选择方案，$ j=1 $ 表示转移到当前点是和选择的方案**方向相同**，$ j=2 $ 表示转移到当前点是和选择的方案**方向不同**，$ j=3 $ 表示转移到当前点是走完了当前选择方案可优化的所有边。

具体如何分类讨论进行转移，非常简单，读者可自行推出式子。不会请看代码注释。

时间复杂度：$ O(m\log_2{m}) $

## 代码

有两份，第一份是最优代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
using namespace std;
#define int long long
typedef pair<long long,int> PLI;
typedef pair<int,int> PII;
typedef pair<PII,int> PPI;
typedef pair<long long,PII> PLP;
const int N=2e5+10;
const int M=4e5+10;
int n,m,S,T,U,V;
int he[N],ne[M<<1],to[M<<1],tot=1;
long long w[M<<1];
bool vis[M<<1];
void addedge(int x,int y,long long z){
	to[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
	w[tot]=z;
}
set<int> pre[N];
long long dist[N];
bool st[N];
void dij(int x){
	priority_queue<PLI,vector<PLI>,greater<PLI> > q;
	for(int i=1;i<=n;i++){
		dist[i]=1e18;
	}
	q.push(PII(0,x));
	dist[x]=0;
	while(!q.empty()){
		PLI t=q.top();
		q.pop();
		if(st[t.second]){
			continue;
		}
		st[t.second]=true;
		for(int i=he[t.second];i;i=ne[i]){
			int v=to[i];
			if(st[v]){
				continue;
			}
			if(dist[v]>t.first+w[i]){
				dist[v]=t.first+w[i];
				pre[v].clear();
				pre[v].insert(t.second);
				q.push(PII(dist[v],v));
			}
			else if (dist[v]==t.first+w[i]){
				pre[v].insert(t.second);
			}
		}
	}
}
void bfs1(int s,int t){
	for(int i=1;i<=n;i++){
		st[i]=false;
	}
	queue<int> q;
	q.push(t);
	while(q.size()){
		int tem=q.front();
		q.pop();
		if(st[tem]||tem==s){
			continue;
		}
		st[tem]=true;
		for(int i=he[tem];i;i=ne[i]){
			int v=to[i];
			if(pre[tem].count(v)){
				vis[i]=true;
				if(!st[v]){
					q.push(v);
				}
			}
		}
	}
}
long long f[N][4],ans=1e18;
//第二维：0-没走过最短路，1-正在走正向，2-正在走反向，3-走完了 
bool yet[N][4];
void dp(int s){
	priority_queue<PLP,vector<PLP>,greater<PLP> > q;
	for(int i=1;i<=n;i++){
		for(int j=0;j<4;j++){
			f[i][j]=1e18;
		}
	}
	for(int i=0;i<4;i++){
		q.push(PLP(0,PII(i,s)));
		f[s][i]=0;
	}
	while(!q.empty()){
		PLP t=q.top();
		q.pop();
		long long d=t.first;
		int x=t.second.second,j=t.second.first;
		if(yet[x][j]){
			continue;
		}
		yet[x][j]=true;
		for(int i=he[x];i;i=ne[i]){
			int v=to[i],dir;
			if(vis[i]||vis[i^1]){
				dir=vis[i]==0?1:2;
			}
			else{
				dir=0;
			}
			if(j==0){//未走
				if(f[v][0]>d+w[i]){//不入 
					f[v][0]=d+w[i];
					q.push(PLP(f[v][0],PII(0,v)));
				}
				if(dir){//入 
					if(f[v][dir]>d){
						f[v][dir]=d;
						q.push(PLP(f[v][dir],PII(dir,v)));
					}
				}
			}
			else if(j==3){//已经走完，必原长 
				if(f[v][3]>d+w[i]){
					f[v][3]=d+w[i];
					q.push(PLP(f[v][3],PII(3,v)));
				}
			}
			else{
				if(j!=dir){//必出最短路 
					if(f[v][3]>d+w[i]){
						f[v][3]=d+w[i];
						q.push(PLP(f[v][3],PII(3,v)));
					}
				}
				else{
					if(f[v][j]>d){//不出 
						f[v][j]=d;
						q.push(PLP(f[v][j],PII(j,v)));
					}
				}
			}
		}
	}
}
main(){
        scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&S,&T,&U,&V);
	int x,y;
	long long z;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		addedge(x,y,z);
		addedge(y,x,z);
	}
	addedge(n+1,U,0);
	addedge(U,n+1,0);
	dij(S);
	bfs1(S,T);
	dp(n+1);
	for(int i=0;i<4;i++){
		ans=min(f[V][i],ans);
	}
	printf("%lld",ans);
}
```

第二份是二维代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
#define int long long
using namespace std;
typedef pair<long long,int> PLI;
typedef pair<int,int> PII;
typedef pair<PII,int> PPI;
typedef pair<long long,PPI> PLP;
const int N=1e5+10;
const int M=2e5+10;
const long long INF=0x3f3f3f3f3f3f3f3f;
int n,m,S,T,U,V;
struct graph{
	int he[N],ne[M<<1],to[M<<1],w[M<<1],tot;
	bool vis[M<<1];
	void addedge(int x,int y,int z){
		to[++tot]=y;
		ne[tot]=he[x];
		he[x]=tot;
		w[tot]=z;
	}
}g1,g2;
set<int> pre[N];
long long dist[N];
bool st[N];
void dij(int x){
	priority_queue<PLI,vector<PLI>,greater<PLI> > q;
	for(int i=1;i<=n;i++){
		dist[i]=1e18;
	}
	q.push(PII(0,x));
	dist[x]=0;
	while(!q.empty()){
		PLI t=q.top();
		q.pop();
		if(st[t.second]){
			continue;
		}
		st[t.second]=true;
		for(int i=g1.he[t.second];i;i=g1.ne[i]){
			int v=g1.to[i];
			if(st[v]){
				continue;
			}
			if(dist[v]>t.first+g1.w[i]){
				dist[v]=t.first+g1.w[i];
				pre[v].clear();
				pre[v].insert(t.second);
				q.push(PII(dist[v],v));
			}
			else if (dist[v]==t.first+g1.w[i]){
				pre[v].insert(t.second);
			}
		}
	}
}
void bfs1(int s,int t){
	for(int i=1;i<=n;i++){
		st[i]=false;
	}
	queue<int> q;
	q.push(t);
	while(q.size()){
		int tem=q.front();
		q.pop();
		if(st[tem]||tem==s){
			continue;
		}
		st[tem]=true;
		for(int i=g1.he[tem];i;i=g1.ne[i]){
			int v=g1.to[i];
			if(pre[tem].count(v)){
				g2.vis[i]=true;
				g2.w[i]=g2.w[i^1]=0;
				if(!st[v]){
					q.push(v);
				}
			}
		}
	}
}
long long f[N][3][3],ans=1e18;//i节点从0/1/2方向来的，0-顺着最短路走过，1-逆着最短路走过,2-不知道 
//第二维：0-没走过最短路，1-正在走，2-走完了 
bool yet[N][3][3];
void dp(int s){
	priority_queue<PLP,vector<PLP>,greater<PLP> > q;
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				f[i][j][k]=1e18;
			}
		}
	}
	q.push(PLP(0,PPI(PII(2,0),s)));
	f[s][2][0]=0;
	while(!q.empty()){
		PLP t=q.top();
		long long d=t.first;
		int x=t.second.second,j=t.second.first.first,k=t.second.first.second;
		q.pop();
		if(yet[x][j][k]){
			continue;
		}
		yet[x][j][k]=true;
		for(int i=g2.he[t.second.second];i;i=g2.ne[i]){
			int v=g2.to[i],dir;
			if(g2.vis[i]||g2.vis[i^1]){
				dir=g2.vis[i];
			}
			else{
				dir=2;
			}
//			cout<<x<<","<<j<<","<<k<<" -> "<<v<<","<<dir<<endl;
			if(!k){
				if(dir==2){
					if(f[v][dir][0]>d+g1.w[i]){
						f[v][dir][0]=d+g1.w[i];
						q.push(PLP(f[v][dir][0],PPI(PII(dir,0),v)));
					}
				}
				else{
					if(f[v][dir][1]>d+g2.w[i]){//进入最短路 
						f[v][dir][1]=d+g2.w[i];
						q.push(PLP(f[v][dir][1],PPI(PII(dir,1),v)));
					}
					if(f[v][dir][0]>d+g1.w[i]){//不进最短路 
						f[v][dir][0]=d+g1.w[i];
						q.push(PLP(f[v][dir][0],PPI(PII(dir,0),v)));
					}
				}
			}
			else{
				if(k&1){
					if(dir==j){
						if(f[v][dir][1]>d+g2.w[i]){
							f[v][dir][1]=d+g2.w[i];
							q.push(PLP(f[v][dir][1],PPI(PII(dir,1),v)));
						}
					}
					else{
						if(f[v][dir][2]>d+g1.w[i]){
							f[v][dir][2]=d+g1.w[i];
							q.push(PLP(f[v][dir][2],PPI(PII(dir,2),v)));
						}
					}
				}
				else{
					if(f[v][dir][2]>d+g1.w[i]){
						f[v][dir][2]=d+g1.w[i];
						q.push(PLP(f[v][dir][2],PPI(PII(dir,2),v)));
					}
				}
			}
		}
	}
}
main(){
	scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&S,&T,&U,&V);
	int x,y,z;
	g1.tot=g2.tot=1;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		g1.addedge(x,y,z);
		g1.addedge(y,x,z);
		g2.addedge(x,y,z);
		g2.addedge(y,x,z);
	}
	dij(S);
	bfs1(S,T);
	dp(U);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			ans=min(f[V][i][j],ans);
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

# P7669 [JOI 2018 Final] 月票购买 / Commuter Pass

## 题意

给定一张 $n$ 个点 $m$ 条边的无向连通正权图，再给出四个点 $S,T,U,V$，请仅选择一条从 $S$ 到 $T$ 的最短路，并将路径上每条边的边权改为 $0$，最后求出所有选择方案中，修改之后从 $U$ 到 $V$ 的最短路长度的最小值。

## 题解

知识点：最短路，动态规划。

比较平凡的题目。

先分别处理出 $U,V,S$ 的单源最短路数组 $dst,ded,ds$，并赋值答案上界为 $dst_V$，考虑的是 $U$ （可能）不经过 $S$ 到 $T$ 的最短路到达 $V$ 的情况。

接着考虑如果经过 $S$ 到 $T$ 最短路时的情况，设 $i,j$ 均为 $S$ 到 $T$ 的**同一条**最短路上的点，则答案为 $\displaystyle \min_{i,j\in path_{S,T}} (dst_i+ded_j)$。

取出 $S$ 到 $T$ 其中的一条最短路 $path_{S,T}$ 考虑，设 $dp_i$ 为从 $S$ 出发处理到点 $i$ 时从 $U$ 到 $V$ 且过点 $i$ 的最短路，则有 $\displaystyle dp_i=\min(dst_i+\min_{j\in path_{S,i}} ded_j,ded_i+\min_{j\in path_{S,i}} dst_j)$，答案为 $\displaystyle \min_{i\in path_{S,T}} dp_i$。

考虑限制，$i,j$ 只能在 $S$ 到 $T$ 的同一条最短路上，不过暴力枚举每一条最短路显然是错误的，通过简单构造可以将复杂度卡到指数级。

所以要考虑把所有可能的最短路一起处理掉。

具体地，建一个新的无权图 $G$，初始时都是孤点，对于原图上满足 $ds_u+w=ds_v$ 的边 $(u,v,w)$ 在 $G$ 上连一条从 $v$ 指向 $u$ 的有向边，由于边权是正权，可以发现新图一定是一个 DAG，且汇点为 $S$，源点为 $T$。

还是设 $dp_i$ 为从 $S$ 出发走到 $i$ 时从 $U$ 到 $V$ 且过点 $i$ 的最短路，$dps_i$ 为 $i$ 之前的点中 $dst$ 的最小值，$dpe_i$ 为 $i$ 之前的点中 $ded$ 的最小值，有如下转移：

$$\displaystyle dp_i=\min_{u\in (u,i)} (dps_u+ded_i,dpe_u+dst_i)$$

$$\displaystyle dps_i=\min(dst_i,\min_{u\in (u,i)}dps_u)$$

$$\displaystyle dpe_i=\min(ded_i,\min_{u\in (u,i)}dpe_u)$$

答案即为 $\displaystyle \max_{i\in G} dp_i$，转移可以用拓扑排序或者记忆化搜索实现。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define int long long
#define N 202507

int n,m,ss,tt,st,ed,ans=2e18;
int dst[N],ded[N],ds[N];
int dps[N],dpe[N];

struct edge{
    int t,w;
};

vector<edge>e[N];
bitset<N>f;

inline void dijkstra(int s,int *dis){
    rep(i,1,n){
        dis[i]=1e18;
        f[i]=0;
    }
    dis[s]=0;

    priority_queue<pr,vector<pr>,greater<pr>>q;

    q.push({dis[s],s});

    while(!q.empty()){
        pr u=q.top();
        q.pop();

        if(f[u.se]){
            continue;
        }
        f[u.se]=1;

        for(edge x:e[u.se]){
            if(dis[u.se]+x.w<dis[x.t]){
                dis[x.t]=dis[u.se]+x.w;
                q.push({dis[x.t],x.t});
            }
        }
    }
}

inline void sol(int k){
    if(f[k]){
        return;
    }
    f[k]=1;

    dps[k]=dst[k];
    dpe[k]=ded[k];

    for(edge x:e[k]){
        if(ds[x.t]+x.w!=ds[k]){
            continue;
        }

        sol(x.t);

        ans=min({ans,dps[x.t]+ded[k],dpe[x.t]+dst[k]});

        dps[k]=min(dps[k],dps[x.t]);
        dpe[k]=min(dpe[k],dpe[x.t]);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;

    cin>>ss>>tt>>st>>ed;

    rep(i,1,m){
        int u,v,w;
        cin>>u>>v>>w;

        e[u].pb({v,w});
        e[v].pb({u,w});
    }

    dijkstra(st,dst);
    dijkstra(ed,ded);
    ans=dst[ed];

    dijkstra(ss,ds);

    rep(i,1,n){
        dps[i]=2e18;
        dpe[i]=2e18;
        f[i]=0;
    }

    sol(tt);

    cout<<ans;

    return 0;
}
```

---

## 作者：dAniel_lele (赞：1)

[双倍经验](https://www.luogu.com.cn/problem/AT_joi2018ho_d)。

不难发现买完通勤票后，从 $U$ 到 $V$ 的最短路有两种情况：

* $U$ 到 $V$ 原图最短路。
* $U$ 到 $S$ 到 $T$ 最短路上某点，$S$ 到 $T$ 最短路上某点到 $V$。

预处理出 $U$ 和 $V$ 到每个点的最短路，然后对 $S$ 到 $T$ 进行双关键字最短路。

考虑除了记录 $S$ 到了哪里以外还要记录是否选了某个点到 $U$，是否选了某个点到 $V$，第二关键字记录目前已选的最小值。

总复杂度 $O((n+m)\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,S,T,U,V;
vector<pair<int,int>> vc[100005]; 
int dis1[100005],dis2[100005];
int vis[100005];
int dis[100005],dp[100005][4];
signed main(){
	cin>>n>>m>>S>>T>>U>>V;
	for(int i=1;i<=m;i++){
		int u,v,w; cin>>u>>v>>w;
		vc[u].push_back(make_pair(v,w));
		vc[v].push_back(make_pair(u,w));
	}
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
	memset(dis1,1,sizeof(dis1));
	memset(vis,0,sizeof(vis));
	dis1[U]=0; q.push(make_pair(0,U));
	while(!q.empty()){
		int f=q.top().second; q.pop();
		if(vis[f]) continue; vis[f]=1;
		for(auto v:vc[f]){
			if(dis1[f]+v.second<dis1[v.first]){
				dis1[v.first]=dis1[f]+v.second;
				q.push(make_pair(dis1[v.first],v.first));
			}
		}
	}
	memset(dis2,1,sizeof(dis2));
	memset(vis,0,sizeof(vis));
	dis2[V]=0; q.push(make_pair(0,V));
	while(!q.empty()){
		int f=q.top().second; q.pop();
		if(vis[f]) continue; vis[f]=1;
		for(auto v:vc[f]){
			if(dis2[f]+v.second<dis2[v.first]){
				dis2[v.first]=dis2[f]+v.second;
				q.push(make_pair(dis2[v.first],v.first));
			}
		}
	}
	memset(dp,1,sizeof(dp));
	memset(dis,1,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dp[S][0]=0,dis[S]=0; q.push(make_pair(0,S));
	while(!q.empty()){
		int f=q.top().second; q.pop();
		if(vis[f]) continue; vis[f]=1;
		dp[f][1]=min(dp[f][1],dp[f][0]+dis1[f]);
		dp[f][2]=min(dp[f][2],dp[f][0]+dis2[f]);
		dp[f][3]=min(dp[f][3],min(dp[f][1]+dis2[f],dp[f][2]+dis1[f]));
		for(auto v:vc[f]){
			if(dis[f]+v.second<dis[v.first]){
				dis[v.first]=dis[f]+v.second;
				dp[v.first][0]=dp[f][0];
				dp[v.first][1]=dp[f][1];
				dp[v.first][2]=dp[f][2];
				dp[v.first][3]=dp[f][3];
				q.push(make_pair(dis[v.first],v.first));
			}
			else if(dis[f]+v.second==dis[v.first]){
				dp[v.first][0]=min(dp[v.first][0],dp[f][0]);
				dp[v.first][1]=min(dp[v.first][1],dp[f][1]);
				dp[v.first][2]=min(dp[v.first][2],dp[f][2]);
				dp[v.first][3]=min(dp[v.first][3],dp[f][3]);
			}
		}
	}
	cout<<min(dp[T][3],dis1[V]);
	return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18973479)


简单图论题，感觉应该是一眼了，这种板子为啥紫啊。

因为 $S,T$ 必须选一条最短路径边权变 $0$，所以可以先跑一遍从 $S$ 开始的最短路，然后再在反图跑一遍从 $T$ 开始的最短路，即可求出所有 $S\to T$ 可能经过的边，也就是满足 $dis_{S\to i}+w_{i,j}+dis_{j\to T}$ 的边 $(i,j)$。这些边组成的**任意一条 $S\to T$ 的路径即为 $S\to T$ 的最短路**，且**组成的图是个 DAG**，因为有环一定不是最短路。

在求出 $S\to T$ 的拓扑图 $G$ 后，不难发现我们**最多只会走一次**这张拓扑图，因为如果走进去之后，走出来再走进去会导致边权为 $0$ 的边没有用上，一定不优。所以套路地把路径分为三段：$U\to G,G,G\to V$。第一和第三种都是容易的，考虑如何做第二种。

进一步观察性质，发现进入拓扑图后我们**只可能沿着拓扑图的路径，或沿着拓扑图反图的路径行走**。理由很简单，如果逆向走了一条边，此时从 $S$ 到 $T$ **只取一条最短路**的条件无法被满足，至少要取两条。所以我们对这张图正向和反向跑一个拓扑排序，然后枚举路径的交界处，更新答案即可。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pi=pair<int,int>;
using pl=pair<ll,ll>;
const int N=100005,M=2000005;
const ll inf=0x3f3f3f3f3f3f3f3f;
ll n,m,s,t,ss,tt,odis[N],sdis[N],tdis[N],dp1[N],dp2[N],rd1[N],rd2[N],ans=inf,todis[N];
int h[N],idx=1;
struct Edge{
	int v,ne;
	ll w;
}e[M];
void add(int u,int v,ll w)
{
	e[++idx]={v,h[u],w};
	h[u]=idx;
}
void dijkstra(int spos,ll *dis)
{
	priority_queue<pl,vector<pl>,greater<pl> >q;
	bitset<N>vis;
	dis[spos]=0;
	q.push({0,spos});
	while(!q.empty())
	{
		int u=q.top().se;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].ne)
		{
			int v=e[i].v;ll w=e[i].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				q.push({dis[v],v});
			}
		}
	}
}
vector<int>g1[N],g2[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(odis,0x3f,sizeof(odis));
	memset(todis,0x3f,sizeof(todis));
	memset(sdis,0x3f,sizeof(sdis));
	memset(tdis,0x3f,sizeof(tdis));
	cin>>n>>m;
	cin>>s>>t>>ss>>tt;
	for(int i=1;i<=m;i++)
	{
		ll u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dijkstra(s,odis);
	dijkstra(t,todis);
	for(int i=2;i<=idx;i++)
	{
		int u=e[i^1].v,v=e[i].v;ll w=e[i].w;
		if(odis[t]==odis[u]+w+todis[v])
		{
			g1[u].push_back(v);
			rd1[v]++;
			g2[v].push_back(u);
			rd2[u]++;
		}
		else if(odis[t]==odis[v]+w+todis[u])
		{
			g1[v].push_back(u);
			rd1[u]++;
			g2[u].push_back(v);
			rd2[v]++;
		}
	}
	dijkstra(ss,sdis);
	dijkstra(tt,tdis);
	memset(dp1,0x3f,sizeof(dp1));
	memset(dp2,0x3f,sizeof(dp2));
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(rd1[i]==0)
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		dp1[u]=min(dp1[u],sdis[u]);
		for(auto v:g1[u])
		{
			rd1[v]--;
			if(rd1[v]==0)q.push(v);
			dp1[v]=min(dp1[v],dp1[u]);
		}
	}
	for(int i=1;i<=n;i++)
		if(rd2[i]==0)
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		dp2[u]=min(dp2[u],sdis[u]);
		for(auto v:g2[u])
		{
			rd2[v]--;
			if(rd2[v]==0)q.push(v);
			dp2[v]=min(dp2[v],dp2[u]);
		}
	}	
	ans=min(ans,sdis[tt]);
	for(int i=1;i<=n;i++)
		ans=min(ans,min(dp1[i],dp2[i])+tdis[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：xukehg (赞：0)

这有紫？

考虑刻画选定了 $S$ 到 $T$ 的最短路后，$U$ 到 $V$ 的最短路是什么样的。注意到如果新的最短路包含了这条最短路上的非首尾的两个点 $a$ 和 $b$，不如直接从 $a$ 走到 $b$ 再走出去。因此最终 $U$ 到 $V$ 的最短路如果发生改变必然是走到选定的路径上的某个点，在路径上走一段距离，然后直接走到 $V$。

接下来形式化描述答案：即 $dist_{u,0/1/2/3}$ 分别表示从 $S$，$T$，$U$，$V$ 为起点的最短路，答案便是 $\min(dist_{V,2},\min(dist_{u,2} + dist_{v,3}))$，其中 $u$ 和 $v$ 满足存在一条最短路同时经过 $u$ 和 $v$。

考虑取出所有的最短路，如果从 $S$ 开始 `dfs` 并定向，剩下的图一定是一个 `dag`。在 `dag` 及其反图上跑拓扑 `dp` 即可。~~某人拿 dfs 写了，究竟在干什么呢？~~

[代码](https://loj.ac/s/2376992)。

---

## 作者：Priestess_SLG (赞：0)

题意：给定一张无向图 $G$，现在给定四个点 $S$，$T$，$u$，$v$，你需要任意选取 $S\to T$ 的一条最短路，并使得将其上所有边边权均赋为 $0$ 后 $u\to v$ 最短路长度最短。

题解：

首先考虑下面的引理：

$\textbf{Lemma}$ 图中 $S\to T$，$u\to v$ 可以构造两条最短路满足下列两种情况中至少一组：

+ 两条图上的路径没有重边。
+ 两条图上的路径有且只有一段相同的边。

$\textbf{Proof}$ 若上述两条图上的路径有两段或以上的重合部分，则任意两段相邻的重合部分，必然有一段路径不重合。考虑找出这一段路径在另一条最短路上所对应的路径，则此时若这条新的路径边权之和大于或等于原来最短路，则换为原来的最短路一定不会更劣；若小于原来的最短路，则原来的最短路就可以被替换为现在的路径，不符合最短路的定义。因此得证。

以及下面的另一个引理：

$\textbf{Lemma}$ 令 $\text{DS}$ 数组表示 $S$ 点为原点的最短路长度，$\text{DT}$ 数组表示 $T$ 点为原点的最短路长度，则对于每一条 $u\leftrightarrow v$，长度为 $w$ 的一条无向边，若满足 $\text{DS}_u+\text{DT}_v+w=\text{DS}_{T}$，或者 $\text{DT}_u+\text{DS}_v+w=\text{DS}_{v}$，则该边可能成为 $S\to T$ 的最短路，否则一定不可能。

$\textbf{Proof}$ 若 $\text{DS}_u+\text{DT}_v+w=\text{DS}_{T}$，则等式的前半部分可以分离为：

+ 从 $S$ 沿最短路走到 $u$。
+ 从 $u$ 走到 $v$，边权为 $w$。
+ 从 $v$ 沿最短路走到 $T$。

而后半部分的 $\text{DS}_T$ 则表示 $S$ 直接走到 $T$ 的最短路。若这两个相等，则表示 $S\to u\to v\to T$ 这一条路径也为最短路，因此 $u\to v$ 这条边在最短路上。反过来同理。

若 $\text{DS}_u+\text{DT}_v+w>\text{DS}_T$，则根据类似于上面的分析可以发现，$u\to v$ 这条边在当前的选取路径下不在最短路上。而因为另外两个部分已经为最短的长度，没有其他的路径继续压缩上述的长度，因此她一定不在最短路上。因此证毕。

又有第三个引理：

$\textbf{Lemma}$ 若将所有可能在最短路上的边按照 $S\to T$ 最短路上的顺序建边，则新图为一张 $\text{DAG}$。

$\textbf{Proof}$ 若图不为 $\text{DAG}$ 则必然存在环。原图中不存在负权边，也就更不可能存在负环。没有负环就不会在新图中存在环，而有向无环图即为 $\text{DAG}$，因此得证。

因此建出新图 $G_1$ 和新图的反图 $G_2$，在 $G_1$ 中跑 $S$ 点的最短路，$G_2$ 中跑 $T$ 点的最短路。然后考虑枚举两条最短路重合的一段路径 $x\to y$，满足 $G_1$ 中 $x$ 可以到达 $y$，并且使得 $\text{DU}_x+\text{DV}_y$ 的值最小。此时考虑在 $\text{DAG}$ 上 $\text{dp}$，对于每一个点 $x$ 找出在 $G_1$ 中其能走到的 $y$ 中 $\text{DV}_y$ 的最小值。这个问题就是平凡的了。

于是这个题我们就做完啦！！！！！不愧是一道好题！！！

---

## 作者：喵仔牛奶 (赞：0)

# Solution

我们有结论：答案路径上免费的边是连续的。

证明比较显然，如果不连续就可以得出 $S\to T$ 或 $U\to V$ 的更优路径。

比较暴力的做法就是枚举免费路径的起点和终点（我们记为 $x,y$），若 $dis_{S,x}+dis_{y,T}+dis_{x,y}=dis_{S,T}$，用 $dis_{U,x}+dis_{y,V}$ 更新答案。

我们要判断 $(x,y)$ 这条路径是否在最短路上，自然想到建最短路 DAG，$(x,y)$ 在最短路上的充要条件就是 $(x,y)$ 在最短路 DAG 上存在。

DAG 的可达性是很好的偏序关系。我们枚举 $x$，令 $mn_x$ 是所有可达的 $y$ 中最小的 $dis_{y,V}$，拓扑排序转移即可。答案就是 $\min\{dis_{U,x}+mn_x\}$。

当然，路径正反不定，还要令 $mn=\min dis_{U,y}$ 跑一遍，再和 $\min\{dis_{x,V}+mn_x\}$ 取最小值。

时间复杂度 $\mathcal{O}(\text{shortestpath}(n,m))$（就是你选的最短路算法的复杂度，比如我写个 Dijkstra 就是 $\mathcal{O}(m\log n)$）。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	LL n, m, s, t, p, q, u, v, w, sd[N], td[N], pd[N], qd[N], dg[N], mn1[N], mn2[N];
	vector<pii> G[N]; vector<int> E[N];
	void dijk(int s, LL* d) {
		priority_queue<pii, vector<pii>, greater<pii>> q;
		REP(i, 1, n) d[i] = 1e18;
		d[s] = 0, q.emplace(d[s], s);
		while (q.size()) {
			auto [dis, u] = q.top(); q.pop();
			if (dis != d[u]) continue;
			for (auto [v, w] : G[u])
				if (d[v] > d[u] + w) d[v] = d[u] + w, q.emplace(d[v], v);
		}
	}
	void chkmin(LL& x, LL y) { x = min(x, y); }
	int main() {
		cin >> n >> m >> s >> t >> p >> q;
		REP(i, 1, m) cin >> u >> v >> w, G[u].pb(v, w), G[v].pb(u, w);
		dijk(s, sd), dijk(t, td), dijk(p, pd), dijk(q, qd);
		REP(u, 1, n) {
			mn1[u] = pd[u], mn2[u] = qd[u];
			for (auto [v, w] : G[u])
				if (sd[u] + td[v] + w == sd[t]) E[u].pb(v), dg[v] ++;
		}
		queue<int> q; LL rs = 1e18;
		REP(i, 1, n) if (!dg[i]) q.push(i);
		while (q.size()) {
			int u = q.front(); q.pop();
			chkmin(rs, mn1[u] + qd[u]), chkmin(rs, mn2[u] + pd[u]);
			for (int v : E[u]) {
				chkmin(mn1[v], mn1[u]), chkmin(mn2[v], mn2[u]);
				if (!-- dg[v]) q.push(v);
			}
		}
		cout << rs << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：xs_siqi (赞：0)

模拟赛 T2。但是除了我以外的所有人都想出来了。哎。

但是不可否认这题积累了很多最短路的新的二级结论，还是很有收获的，希望下次可以用起来。

我们可以选择一段免费路径，但它一定是一段 $S$ 到 $T$ 的最短路。据此，不难想到我们可以直接把最短路树建出来。

其实也算不上建出来，只是把最短路树的边稍微标记一下，给下次用。如何标记最短路路径？说实话做这题之前我都不知道这个二级结论，稍微介绍一下：

我们分别从 $S$ 和 $T$ 跑一遍最短路，然后枚举每一条边。令这条边的左端点为 $x$，右端点为 $y$，假如 $S$ 到 $x$ 的最短路加上 $T$ 到 $y$ 的最短路加上这条边的边权，恰好等于 $S$ 到 $T$ 的最短路，那么这条边一定是最短路树上的一条边。

然后我们正图反图跑一下最短路就可以求完了。

接下来我们无非就是要解决 $U$ 到 $V$ 被覆盖后最短路的问题。暴力的做法肯定是枚举这每一条最短路树上的每一种可能，但是这样复杂度大概就到了指数级别，太垃圾了。

考虑挖掘一些性质。比如我们发现有这样一个性质：被 $S$ 到 $T$ 覆盖的路径一定是连续的，不可能断开。考虑反证法，证明如下：

从简单的情况入手，比如说，我们要从 $U$ 到 $V$，中间有两条路径被覆盖，这两条路径之间有一条断开的不免费的路径，就让这个路径两个端点为 $x,y$ 好了。既然我们知道，$S$ 到 $T$ 是一条最短路，且 $S$ 到 $x$ 与 $y$ 到 $T$ 都是一部分，那么不可能存在一条路径比 $x$ 到 $y$ 的最短路更优（不严格小于），因此 $x$ 到 $y$ 也一定是最短路树上的一部分，也就是可以免费的。路径多的情况同理。

我们有了这个性质之后就非常好做了，分层图和图上 dp 二选一随便搞。我写了图上 dp，我是消愁，因为这题图上 dp 的码量还是比较大的。而且常数优势也没有那么明显。

可能这个状态难设，那我还是讲一下怎么图上 dp 吧。我们设 $f_{i,0}$ 表示目前没有走到免费路径的最短路，$f_{i,1}$ 表示目前走到一段顺的路径上的最短路，$f_{i,2}$ 表示目前走到一段逆的路径上的最短路，$f_{i,3}$ 表示已经走完免费路径后的最短路。这里区分“顺的路径”和“逆的路径”是因为 $U$ 到 $V$ 可能是被 $T$ 到 $S$ 的路径覆盖。但是顺的路径和逆的路径不可以同时覆盖。

然后自己枚举一下所有情况大力转移即可。都来做紫题相信你自己也能推出方程的。

算了还是讲一下吧。就比如说如果你是目前的状态是 $0$，并且前面那条路径是免费路径，那显然是能免费转移到状态 $1$ 或者状态 $2$ 的。然后因为有可能一条免费的路径都不走反而更优，所以 $0$ 也可以走收费的然后到状态 $3$。$0$ 能转移到它自己，因为可以先沉淀一下，晚点再走更优的免费路径。

假如你目前的状态是 $1$，如果前面是免费路径，那肯定会出现一个选择就是我继续走下去，下一步状态还是 $1$，如果前面不是免费路径，说明已经走完免费的了，那就直接转移到 $3$。目前状态是 $2$ 也是同理的。

假如你目前的状态是 $3$，免费路径已经走过一段了，再走肯定不优。所以你肯定只能走收费路径，然后转移到自己。

哦，还有一个事情要讲：如何分别标记顺的路径和逆的路径？

我们可以仿照 tarjan 求边双时不能走回头路的方法，把初始的邻接表的值改为 $1$，然后直接用异或标记就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=8e5+5;
int n,m,S,T,U,V,fir[maxn],to[maxn*2],nxt[maxn*2],w[maxn*2],tot=1,dis[3][maxn],f[4][maxn];
void add(int x,int y,int z){
	to[++tot]=y,nxt[tot]=fir[x],w[tot]=z,fir[x]=tot;
}
struct edge{
	int x,id;
	friend bool operator < (edge x,edge y){
		return x.x>y.x;
	}
};
struct edge2{
	int id,x,tag;
	friend bool operator < (edge2 x,edge2 y){
		return x.x>y.x;
	}
};
bool vis[maxn],red[2][maxn],vis2[4][maxn];
priority_queue<edge> q;
priority_queue<edge2> q2;
void dij(int id,int s){
	for(int i=1;i<=n;i++)
		dis[id][i]=(i==s?0:1e18);
	memset(vis,0,sizeof vis);
	q.push((edge){0,s});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=fir[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[id][v]>dis[id][u]+w[i]){
				dis[id][v]=dis[id][u]+w[i];
				q.push((edge){dis[id][v],v});
			}
		}
	}
}
void calc(int s){
	for(int l=0;l<=3;l++)
		for(int i=1;i<=n;i++)
			f[l][i]=1e18;
	f[3][s]=f[0][s]=0;
	memset(vis2,0,sizeof vis2);
	q2.push((edge2){s,0,0});
	while(!q2.empty()){
		int u=q2.top().id,tag=q2.top().tag;
		q2.pop();
		if(vis2[tag][u])continue;
		vis2[tag][u]=1;
		for(int i=fir[u];i;i=nxt[i]){
			int v=to[i];
			if(tag==0){
				if(f[0][v]>f[0][u]+w[i])
					f[0][v]=f[0][u]+w[i],q2.push((edge2){v,f[0][v],0});
				if(f[3][v]>f[0][u]+w[i])
					f[3][v]=f[0][u]+w[i],q2.push((edge2){v,f[3][v],0});
				if(red[0][i]&&f[1][v]>f[0][u])
					f[1][v]=f[0][u],q2.push((edge2){v,f[1][v],1});
				if(red[1][i]&&f[2][v]>f[0][u])
					f[2][v]=f[0][u],q2.push((edge2){v,f[2][v],2});
			}
			if(tag==1){
				if(red[0][i]&&f[1][u]<f[1][v])
					f[1][v]=f[1][u],q2.push((edge2){v,f[1][v],1});
				if(f[1][u]+w[i]<f[3][v])
					f[3][v]=f[1][u]+w[i],q2.push((edge2){v,f[3][v],3});
			}
			if(tag==2){
				if(red[1][i]&&f[2][u]<f[2][v])
					f[2][v]=f[2][u],q2.push((edge2){v,f[2][v],2});
				if(f[2][u]+w[i]<f[3][v])
					f[3][v]=f[2][u]+w[i],q2.push((edge2){v,f[3][v],3});
			}
			if(tag==3){
				if(f[3][v]>f[3][u]+w[i])
					f[3][v]=f[3][u]+w[i],q2.push((edge2){v,f[3][v],3});
			}
		}
	}
}
signed main(){
//	freopen("01-10.in","r",stdin); 
	scanf("%lld%lld",&n,&m);
	scanf("%lld%lld%lld%lld",&S,&T,&U,&V);
	for(int x,y,z,i=1;i<=m;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	dij(0,S),dij(1,T);
	for(int u=1;u<=n;u++){
		for(int i=fir[u];i;i=nxt[i]){
			if(dis[0][u]+w[i]+dis[1][to[i]]==dis[0][T]){
				red[0][i]=1,red[1][i^1]=1;
//				cout<<"0:"<<u<<" "<<to[i]<<endl;
//				cout<<"1:"<<to[i]<<" "<<u<<endl;
			}
		}
	}
	calc(U);
	printf("%lld\n",min(min(f[0][V],f[1][V]),min(f[2][V],f[3][V])));
	return 0;
}


```


---

