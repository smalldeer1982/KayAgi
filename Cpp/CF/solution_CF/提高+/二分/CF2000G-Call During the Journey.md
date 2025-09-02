# Call During the Journey

## 题目描述

你所居住的城市由 $n$ 个交叉路口和连接几对交叉路口的 $m$ 条街道组成。您可以在每条街道上向任一方向前进。没有两条街道连接同一对交叉路口，也没有一条街道只连接一个交叉路口。您可以从任何一个交叉路口到达另一个交叉路口，但可能会经过其他一些交叉路口。

每分钟，你可以在路口 $u_i$ 登上一辆公交车，然后行驶 $l_{i1}$ 分钟到达路口 $v_i$ 。相反，您可以在 $l_{i1}$ 分钟内从路口 $v_i$ 到达路口 $u_i$ 。您只能在交叉路口上下车。只有当您正在某交叉路口时，才能在该交叉路口登上公共汽车。

您也可以沿着每条街道步行，这需要 $l_{i2} \gt l_{i1}$ 分钟。

您可以在十字路口停车。

您住在十字路口编号 $1$ 处。今天您在 $0$ 点起床，在路口编号 $n$ 处有一个重要活动安排，您必须在 $t_0$ 点之前到达。你还计划打一个电话，通话时间为 $t_1$ 至 $t_2$ 分钟（ $t_1 \lt t_2 \lt t_0$ ）。

通话期间，您不能乘坐公共汽车，但可以在任何街道上行走、停靠在站点处或待在家里。您可以在 $t_1$ 分钟下车，在 $t_2$ 分钟再次上车。

由于您希望获得充足的睡眠，您开始好奇您可以多晚离开家，以便有时间讲电话，同时还不会在活动中迟到？

## 样例 #1

### 输入

```
7
5 5
100 20 80
1 5 30 100
1 2 20 50
2 3 20 50
3 4 20 50
4 5 20 50
2 1
100 50 60
1 2 55 110
4 4
100 40 60
1 2 30 100
2 4 30 100
1 3 20 50
3 4 20 50
3 3
100 80 90
1 2 1 10
2 3 10 50
1 3 20 21
3 2
58 55 57
2 1 1 3
2 3 3 4
2 1
12 9 10
2 1 6 10
5 5
8 5 6
2 1 1 8
2 3 4 8
4 2 2 4
5 3 3 4
4 5 2 6```

### 输出

```
0
-1
60
80
53
3
2```

# 题解

## 作者：Super_Cube (赞：7)

# Solution

正向问题不太好做，考虑倒推得到答案。

设 $f_i$ 表示从 $i$ 开始到 $n$ 的最晚起步时间，初始化 $f_n=n$，答案为 $f_1$。从 $n$ 开始倒着往回遍历，对于 $u\to v$，若 $f_u-l_1\ge t_2$ 或 $f_u\le t_1$，那肯定坐公交车（因为保证了 $l_1<l_2$）；否则选择步行，或者站着干等直到 $t_1$ 时刻再坐公交。所以得到转移：$f_v\gets\max\limits_{u\to v}\begin{cases}f_u-l_1&f_u-l_1\ge l_2\lor f_u\le t_1\\\max(f_u-l_2,t_1-l_1)&\text{otherwise.}\end{cases}$

发现是类最短路转移的形式，就当最短路跑即可。

# Code
```cpp
#include<bits/stdc++.h>
#define $(x,i) std::get<i>(x)
std::vector<std::tuple<int,int,int> >v[100005];
int dis[100005];
bool vis[100005];
int T,n,m,t0,t1,t2;
int bfs(){
	std::priority_queue<std::pair<int,int> >q;
	memset(dis+1,192,n<<2);
	memset(vis+1,0,n);
	q.emplace(dis[n]=t0,n);
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;
		vis[x]=true;
		for(const auto&i:v[x]){
			static int val;
			if(dis[x]-$(i,1)>=t2||dis[x]<=t1)val=dis[x]-$(i,1);
			else val=std::max(dis[x]-$(i,2),t1-$(i,1));
			if(dis[$(i,0)]<val)
				q.emplace(dis[$(i,0)]=val,$(i,0));
		}
	}
	return std::max(dis[1],-1);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d%d",&n,&m,&t0,&t1,&t2);
		for(int i=1;i<=n;++i)v[i].clear();
		for(int x,y,z1,z2;m--;)
			scanf("%d%d%d%d",&x,&y,&z1,&z2),
			v[x].emplace_back(y,z1,z2),v[y].emplace_back(x,z1,z2);
		printf("%d\n",bfs());
	}
	return 0;
}
```

---

## 作者：liugh_ (赞：1)

## [Call During the Journey](https://codeforces.com/contest/2000/problem/G)

> $n$ 个点 $m$ 条边的无向图，有主边权和副边权，在时间区间 $(t_1,t_2)$ 内不能走主边权，$t_0$ 时刻前要从点 $1$ 到点 $n$，求最大出发时刻。
>
> $n,m\le 10^5$，$t_0\le 10^9$。

倒着想，在 $[t_2,t_0]$ 内我们可以通过主边权从 $n$ 走到一些点，在 $(t_1,t_2)$ 内又能通过副边权走到一些点，然而后者是不好确定的，因此不易直接得出到 $1$ 的最短路。

有关时间的限制，一般可以拆点或分层，此题时间值域大且不能离散化，于是考虑建分层图。先预处理出从 $1$ 和 $n$ 出发的最短路 $f,g$。考虑分两层，主层和副层上原图中的边分别应用主边权和副边权，我们想在 $t_1$ 前跳到副层，在 $t_2$ 后跳回主层，那么可以在主层上对于满足 $f(x)\le t_1-s$ 的 $x$ 连边 $1\xrightarrow{f(x)} x$，对于满足 $g(x)\le t_0-t_2$ 的 $x$ 连边 $x\xrightarrow{g(x)} n$，每个点在主层和副层中的映射连权为 $0$ 的双向边。这样建图实现了**让算法选择最优解以避免对跳转时间的讨论**。结合刚才的结论，二分答案 $s$，那么合法当且仅当分层图上 $1$ 到 $n$ 的最短路不大于 $t_0-s$。时间复杂度 $O(n\log^2 n)$。

```cpp
auto dij=[&](auto&G,auto&dis,int s){vector<int>(n*2+5,inf).swap(dis);vector<bool> vis(n*2+5);priority_queue<pii> q;for(dis[s]=0,q.push({0,s});q.size();){int u=q.top().se;q.pop();if(vis[u])continue;vis[u]=1;for(auto [v,w]:G[u])if(dis[u]+w<dis[v])dis[v]=dis[u]+w,q.push({-dis[v],v});}};
int n,m,t0,t1,t2;cin>>n>>m>>t0>>t1>>t2;vector<vector<pii>> G(n+5);vector<array<int,3>> E(m+5);
for(int i=1;i<=m;i++){int u,v,w1,w2;cin>>u>>v>>w1>>w2;G[u].pb({v,w1}),G[v].pb({u,w1}),E[i]={u,v,w2};}
vector<int> dis1,dis2;dij(G,dis1,1),dij(G,dis2,n);
auto chk=[&](int mid){
	vector<vector<pii>> tG(n*2+5);
	for(int i=1;i<=n;i++){
		if(dis1[i]<=t1-mid)
			tG[1].pb({i,dis1[i]});
		if(dis2[i]<=t0-t2)
			tG[i].pb({n,dis2[i]});
		tG[i].pb({i+n,0}),tG[i+n].pb({i,0});
	}
	for(int i=1;i<=m;i++){
		auto [u,v,w2]=E[i];
		tG[u+n].pb({v+n,w2}),tG[v+n].pb({u+n,w2});
	}
	vector<int> dis;dij(tG,dis,1);
	return dis[n]<=t0-mid;
};int l=0,r=t0,res=-1;while(l<=r)if(int mid=(l+r)>>1;chk(mid))res=mid,l=mid+1;else r=mid-1;cout<<res<<'\n';
```

---

## 作者：BrotherCall (赞：1)

## 题意

$n$ 个点 $m$ 条边的无向图，每条路开车要 $l_{i1}$ 分钟，走路要 $l_{i2}(l_{i2} > l_{i1})$ 分钟。给定 $t_1,t_2,t_3$，你从 $1$ 号点出发，要求在 $t_2\sim t_3$ 时段不开车的情况下，在 $t_1$ 时刻前到达点 $n$，问最迟什么时候出发。

## 分析

由于对于任意两点，开车一定比走路快，所以在没有不开车限制的情况下，必定选择全程开车。

现在有了不开车的限制，那么必定是存在一个连续的不开车区间 $[t_2',t_3']$ 覆盖 $[t_2,t_3]$，在 $t_2'$ 之前全程开车，在 $t_3'$ 之后也全程开车。

若出发的时间为 $t_0$，开车到点 $d_1$，步行到点 $d_2$，然后开车到点 $n$。

那么本题就被划分为了“开车 $\to$ 步行 $\to$ 开车”三个阶段。

由于是要求出发时间的最大值，我们知道这个答案是可以二分的。但这是个未知量，不好分析。

而该图是一个无向图，所以考虑从终点入手，把问题转化为：从终点出发，经历“开车 $\to$ 步行 $\to$ 开车”，且满足不开车的区间覆盖 $[t_2,t_3]$，最早什么时刻到起点。


初始化一个所有边权均为开车的图为 $G_1$，一个所有边权均为走路的图为 $G_2$，$i$ 到 $j$ 的最短路为 $dis_{i,j}$。

由于在 $t_1$ 时刻前需要到达终点，所以对于从点 $n$ 开始的开车阶段，需要满足 $dis_{n,i}\in G_1 \le t_1 - t_3$。

找到所有满足该条件的点，对于其中的每个点 $x$，都在 $G_2$ 中连一条 $n \to x$ 和一条 $x \to n$ 的边，边权为 $dis_{n,i}\in G_1$，代表从 $n$ 出发能开车的时候尽量开车。

对于新的 $G_2$ 再跑一个最短路，于是花的最少的时间 $t_{min}$ 即为 $\min(\max(t_1-t_2,dis_{n,i}\in G_2) + dis_{1,i} \in G_1)$。

又需要考虑到 $1$ 点这段不开车的情况。

所以答案即为 $\max(t_1 - t_{min} , t_1 - dis_{n,1}\in G_2)$。

时间复杂度即 $\text{Dijkstra}$ 的 $O(m\log m)$。

[提交记录](https://codeforces.com/contest/2000/submission/281825026)。

---

另外二分起点时刻，用类似的方法也可以做，复杂度 $O(m\log m \log t_1)$。

[提交记录](https://codeforces.com/contest/2000/submission/281804875)。

---

## 作者：abensyl (赞：1)

原题链接：[CF2000G Call During the Journey](https://www.luogu.com.cn/problem/CF2000G)。

与其他题解不同，考虑不进行二分的做法，时间复杂度少一个 log。

## 思路

求从 $1$ 号节点可以准时到达 $n$ 号节点的最晚出发时间，等价于反着求从 $n$ 号节点出发，最早到达 $1$ 号节点的时间。

根据题意，我们将时间划分为三个阶段：$[0,t_1]$、$[t_1,t_2]$、$[t_2,t_0]$。

在第一和第三个阶段中，我们可以随意的坐公共汽车，但是在第二个阶段中，我们只能走路。

既然是求最短路问题，考虑对于三个阶段分别跑三次 dijkstra。

先跑第三阶段：以 $n$ 号节点为源点，限定时间必须小于等于 $t_0-t_2$，乘坐公交车。

然后跑第二阶段：不限定时间，建立在刚才最短路的基础上，可以随意穿梭，但是只能走路，不能乘车。

最后跑第三阶段：限定出发时间必须大于 $t_0-t_1$，乘坐公交车。

三次最短路之后可以求得以 $n$ 号节点为原点的 $1$ 号节点的最短路长度，记作 $d$。

如果 $d>t_0$，很显然无解，输出 `-1`，否则输出 $t_0-d$。

时间复杂度为 $O(n\log n)$。

[代码 + 我的 AC 记录](https://codeforces.com/contest/2000/submission/281829163)。

---

## 作者：aeiouaoeiu (赞：1)

预处理 $1,n$ 为起点的最短路 $d_0,d_1$。

答案存在单调性，考虑二分。检查 $x$ 时，处理出在 $t_1-x$ 时刻内能从 $1$ 走到的点，将这些点 $i$ 到 $1$ 的距离设为 $d_{1,i}+x$，只使用步行道跑一遍最短路，记为 $d_2$。依次检查点 $i$ 是否满足 $\max(t_2,d_{2,i})+d_{1,i}\le t_0$ 即可。

时间复杂度 $\mathcal{O}(\sum m\log m\log t_0)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair
#define pob pop_back
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=100007,ee=1e18;
struct Edge{ll to,w,tag,nxt;}edge[maxn<<2];
ll n,m,h[maxn],ent,dis[3][maxn],vis[maxn],t0,t1,t2,res;
vector<ll> tmp;
priority_queue<pair<ll,ll> > q;
void addedge(ll u,ll v,ll w,ll tag){edge[++ent]=Edge{v,w,tag,h[u]},h[u]=ent;}
void dij(vector<ll> &st,ll *d,bool flg){
	if(!flg)for(int i=1;i<=n;i++) d[i]=ee;
	for(int i=1;i<=n;i++) vis[i]=0;
	if(!flg)for(auto u:st) d[u]=0;
	for(auto u:st) q.push(mp(d[u],u));
	for(ll u,v,w;!q.empty();){
		u=q.top().second,q.pop();
		if(vis[u]||(flg&&d[u]>t2)||d[u]>t0) continue; vis[u]=1;
		for(ll i=h[u];i;i=edge[i].nxt){
			v=edge[i].to,w=edge[i].w;
			if(flg&&edge[i].tag) continue;
			if(d[v]>d[u]+w) d[v]=d[u]+w,q.push(mp(-d[v],v));
		}
	}
}
bool check(ll x){
	tmp.clear();
	for(int i=1;i<=n;i++) dis[2][i]=ee;
	for(int i=1;i<=n;i++)if(dis[0][i]<=max(t1-x,0ll)) dis[2][i]=x+dis[0][i],tmp.pb(i);
	//cout<<x<<": "; for(auto u:tmp) cout<<u<<" "; cout<<"\n";
	dij(tmp,dis[2],1);
	//for(int i=1;i<=n;i++) cout<<dis[2][i]<<" "; cout<<"\n";
	for(int i=1;i<=n;i++)if(max(dis[2][i],t2)+dis[1][i]<=t0) return 1;
	return 0;
}
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	ll T=1;
	cin>>T;
	for(;T--;){
		for(int i=1;i<=n;i++) h[i]=0; ent=0; tmp.clear();
		cin>>n>>m>>t0>>t1>>t2; res=-1;
		for(int i=1,u,v,w1,w2;i<=m;i++){
			cin>>u>>v>>w1>>w2;
			addedge(u,v,w1,1),addedge(v,u,w1,1);
			addedge(u,v,w2,0),addedge(v,u,w2,0);
		}
		tmp.pb(1),dij(tmp,dis[0],0),tmp.pob(),tmp.pb(n),dij(tmp,dis[1],0);
		for(ll l=0,r=t0,mid;l<=r;){
			mid=(l+r)>>1;
			if(check(mid)) l=mid+1,res=mid;
			else r=mid-1;
		}
		cout<<res<<"\n";
	}
	return 0;
}
```

---

## 作者：Ke_scholar (赞：0)

# [Call During the Journey](https://codeforces.com/contest/2000/problem/G)

## 思路

考虑要找最晚出发的时间，这点我们可以通过二分解决。

然后考虑 Dijkstra，如果当前的时间点采用骑车的话，其花费的时间段和打电话的时间如果有交集，那我们只有两种选择，走路 或者 在原地打完电话之后骑车；若无交集，那就正常骑车即可。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

struct DIJ {
    using i64 = long long;
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<vector<array<i64, 3>>> G;

    int n;
    DIJ() {}
    DIJ(int n_): n(n_) {
        G.resize(n + 1);
    }

    void add(int u, int v, int l1, int l2) {
        G[u].push_back({v, l1, l2});
    }

    void dijkstra(int s, i64 tx, i64 t1, i64 t2) {
        dis.assign(n + 1, 1e18);
        priority_queue<PII> Q;
        dis[s] = tx;
        Q.push({ -dis[s], s});
        while (!Q.empty()) {
            auto [t, u] = Q.top();
            Q.pop();

            t = -t;
            if (dis[u] < t) continue;

            for (auto [v, l1, l2] : G[u]) {
                auto now = t + l2;
                if (max(t, t1) < min(t + l1, t2)) {
                    now = min(now, t2 + l1);
                } else {
                    now = min(now, t + l1);
                }
                if (dis[v] > now) {
                    dis[v] = now;
                    Q.push({ -dis[v], v});
                }
            }
        }
    }
};

void solve() {

    int n, m, t[3] {};
    cin >> n >> m >> t[0] >> t[1] >> t[2];

    DIJ dij(n);
    for (int i = 0; i < m; i ++) {
        int u, v, l1, l2;
        cin >> u >> v >> l1 >> l2;
        dij.add(u, v, l1, l2);
        dij.add(v, u, l1, l2);
    }

    i64 l = 0, r = t[0], ans = -1;
    while (l <= r) {
        i64 mid = l + r >> 1;
        dij.dijkstra(1, mid, t[1], t[2]);
        if (dij.dis[n] <= t[0]) l = mid + 1, ans = mid;
        else r = mid - 1;
    }

    cout << ans << '\n';

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
```

---

