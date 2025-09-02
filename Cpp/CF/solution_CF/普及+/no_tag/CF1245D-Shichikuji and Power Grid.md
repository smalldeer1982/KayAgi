# Shichikuji and Power Grid

## 题目描述

Shichikuji is the new resident deity of the South Black Snail Temple. Her first job is as follows:

There are $ n $ new cities located in Prefecture X. Cities are numbered from $ 1 $ to $ n $ . City $ i $ is located $ x_i $ km North of the shrine and $ y_i $ km East of the shrine. It is possible that $ (x_i, y_i) = (x_j, y_j) $ even when $ i \ne j $ .

Shichikuji must provide electricity to each city either by building a power station in that city, or by making a connection between that city and another one that already has electricity. So the City has electricity if it has a power station in it or it is connected to a City which has electricity by a direct connection or via a chain of connections.

- Building a power station in City $ i $ will cost $ c_i $ yen;
- Making a connection between City $ i $ and City $ j $ will cost $ k_i + k_j $ yen per km of wire used for the connection. However, wires can only go the cardinal directions (North, South, East, West). Wires can cross each other. Each wire must have both of its endpoints in some cities. If City $ i $ and City $ j $ are connected by a wire, the wire will go through any shortest path from City $ i $ to City $ j $ . Thus, the length of the wire if City $ i $ and City $ j $ are connected is $ |x_i - x_j| + |y_i - y_j| $ km.

Shichikuji wants to do this job spending as little money as possible, since according to her, there isn't really anything else in the world other than money. However, she died when she was only in fifth grade so she is not smart enough for this. And thus, the new resident deity asks for your help.

And so, you have to provide Shichikuji with the following information: minimum amount of yen needed to provide electricity to all cities, the cities in which power stations will be built, and the connections to be made.

If there are multiple ways to choose the cities and the connections to obtain the construction of minimum price, then print any of them.

## 说明/提示

For the answers given in the samples, refer to the following diagrams (cities with power stations are colored green, other cities are colored blue, and wires are colored red):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1245D/251d50cda099f4e4be2994b6b01574cc32a17cd3.png)

For the first example, the cost of building power stations in all cities is $ 3 + 2 + 3 = 8 $ . It can be shown that no configuration costs less than 8 yen.

For the second example, the cost of building a power station in City 2 is 2. The cost of connecting City 1 and City 2 is $ 2 \cdot (3 + 2) = 10 $ . The cost of connecting City 2 and City 3 is $ 3 \cdot (2 + 3) = 15 $ . Thus the total cost is $ 2 + 10 + 15 = 27 $ . It can be shown that no configuration costs less than 27 yen.

## 样例 #1

### 输入

```
3
2 3
1 1
3 2
3 2 3
3 2 3
```

### 输出

```
8
3
1 2 3 
0
```

## 样例 #2

### 输入

```
3
2 1
1 2
3 3
23 2 23
3 2 3
```

### 输出

```
27
1
2 
2
1 2
2 3
```

# 题解

## 作者：yi_fan0305 (赞：9)

这张图有点权，有边权，那我们考虑把点权化为边权，即建一个虚点，向所有点连边，边权为每个点的点权，要求是最小代价，根据题目，可以想到最小生成树，由于 $n \le 2000$，而且是稠密图，我们考虑用 prim 算法。

最后统计答案时，我记录了每条边的起始点和终点，在判断起始点是否为虚点来判断这个点是否建发电站。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;
typedef pair<ll, pair<int, int> > plii;

const int N = 2010;

int n, cnt, cot;
ll tot;
ll x[N], y[N];
ll c[N], k[N], dis[N];
bool vis[N], ok[N];
vector<pil> son[N];
priority_queue<plii, vector<plii>, greater<plii> > q; // pair 套 pair

struct edge {
	int u, v;
	ll w;
} ans[N]; // 记录答案

void prim(int s) {
	q.push({0, {s, 0}});
	for (int i = 0; i <= n; ++ i) {
		dis[i] = 1e18;
	}
	dis[s] = 0;
	while (! q.empty()) {
		plii it = q.top();
		q.pop();
		int u = it.second.first;
		if (vis[u])	continue;
		++ cnt;
		tot += dis[u];
		vis[u] = 1;
		ans[cnt] = edge{it.second.second, it.second.first, dis[u]};
		// 记录答案
		if (it.second.second == 0) { // 由此来判断这个点是否建发电站
			ok[u] = 1;
			++ cot;
		}
		if (cnt >= n + 1)	return ;
		for (auto it : son[u]) {
			int v = it.first;
			ll w = it.second;
			if (dis[v] > w) {
				dis[v] = w;
				q.push({dis[v], {v, u}});
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld%lld", &x[i], &y[i]);
	}
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld", &c[i]);
		son[0].push_back({i, c[i]});
	}
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld", &k[i]);
		for (int j = 1; j < i; ++ j) {
			ll dis = abs(x[i] - x[j]) + abs(y[i] - y[j]);
			dis = dis * (k[i] + k[j]);
			son[i].push_back({j, dis});
			son[j].push_back({i, dis});
		}
	}
	prim(0);
	printf("%lld\n%d\n", tot, cot - 1);
	// 由于统计 cot 时把 0（虚点） 也统计上了,所以要减一
	for (int i = 1; i <= n; ++ i) {
		if (ok[i]) {
			printf("%d ", i);
		}
	}
	putchar('\n');
	int res = 0;
	for (int i = 1; i <= cnt; ++ i) {
		if (ans[i].u != 0 && ans[i].v != 0) { // 与虚点的连边不能统计上
			++ res;
		}
	}
	printf("%d\n", res);
	for (int i = 1; i <= cnt; ++ i) {
		if (ans[i].u != 0 && ans[i].v != 0) {
			printf("%d %d\n", ans[i].u, ans[i].v);
		}
	}
	return 0;
}
```

---

## 作者：wheneveright (赞：9)

# 题解 CF1245D

## 思路分析及算法分析

这道题的想法其他 dalao 也都讲了，就是**套一个虚拟节点再向上建边**的想法。

考虑到这道题每两个节点之间都会有边。

Kruscal 的复杂度就到了 $O(K \times \log_2 K) = O(N^2 \times \log_2 N^2)$。

而 prim 的复杂度还是稳定的 $O(N^2)$。

prim 要优化一个 $log_2 N^2$ 时间，所以选择用 **prim** 解决这道题。

## 代码及讲解

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;

struct reader {
	template <typename Type>
	reader & operator >> (register Type & ret) {
		register int f = 1; ret = 0; register char ch = getchar ();
		for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f=-f;
		for (; isdigit (ch); ch = getchar ()) ret = (ret << 1) + (ret << 3) + (ch - '0');
		ret *= f; return *this;
	}
} fin;

int N, bd; // bd指的是直接建立一个电源的节点个数
long long K[maxn];
long long X[maxn];
long long Y[maxn]; // 这些如题
long long las[maxn]; // 计入上一次更新这个点是哪个点，如果选上那就代表 las[i] 与 i 之间有边
long long res; // 最后的答案
long long dis[maxn]; // 当前树到各个非树节点的最小值
bool vis[maxn]; // 记录当前是否有被加入树中

int main () {
	fin >> N;
	for (register int i = 1; i <= N; i++) fin >> X[i] >> Y[i];
	for (register int i = 1; i <= N; i++) fin >> dis[i];
	for (register int i = 1; i <= N; i++) fin >> K[i], las[i] = 0;
	//读入数据的同时讲上一次更新的设为0号节点，然后将 dis 设为直接建立电力站的代价，也就是普通prim将所有点设置为初始的0号点的权值
	for (register int t = 1; t <= N; t++) {
		register int minn = 2147483640, id;
		for (register int i = 1; i <= N; i++)
		if (!vis[i] && dis[i] < minn) minn = dis[i], id = i;
		vis[id] = true; res += minn; if (las[id] == 0) bd++;
		for (register int i = 1; i <= N; i++)
		if (!vis[i] && dis[i] > (K[i] + K[id]) * (abs (X[id] - X[i]) + abs (Y[id] - Y[i])))
		dis[i] = (K[i] + K[id]) * (abs (X[id] - X[i]) + abs (Y[id] - Y[i])), las[i] = id;
		//更新点的同时建立记录此次是哪个点更新，这里上文有说
	}
	printf ("%lld\n%d\n", res, bd);
	for (register int i = 1; i <= N; i++)
	if (las[i] == 0) printf ("%d ", i);
	printf ("\n%d\n", N - bd);
	//如果直接设立电力站的代价是 bd 的话，那么剩下 N-bd 个点肯定都是连边的，一个点一条边
	for (register int i = 1; i <= N; i++)
	if (las[i] != 0) printf ("%lld %d\n", las[i], i);
	return 0;
}
```
最后，将这句老生常谈的话再拿出来：**十年OI一场空，不开longlong见祖宗**


---

## 作者：luan341502 (赞：8)

与其他题解不同的做法。

首先我们按照题目要求，在 $n$ 个点之间建好图。

回忆 kruskal 算法的过程，我们先将边从小到大排列，假设每个点是一个孤立的子集，若一条边连接 $u$ 和 $v$，而所有边权小于这条边的边无法使这两个点连通，那么这条边就在最小生成树上。

本题与裸的最小生成树的不同之处就在与每个点有一个可以选择的权值。很容易想到，对于一个连通块，我们仅选择权值最小的那个点建造发电站是最优的。

因此考虑和 kruskal 相同的过程，我们先在每个点上都建一个发电站，将边从小到大排列后依次枚举，若将两个连通块连上，取权值最小点建造发电站比在两个连通块上分别建造连通块更优，则我们在这两点间连接电缆。

考虑什么情况下在两点间连接电缆更优。设边 $(u,v)$ 的权值为 $w_i$，$u$ 点所在连通块上权值最小值（唯一的建造发电站的点上取到）为 $c'_u$，同理得知 $v$ 点对应的 $c'_v$，此时 $u$ 和 $v$ 还不连通。如果不在 $u$ 和 $v$ 间连接电缆，对答案的贡献显然为 $c'_u+c'_v+\sum w$（这里 $\sum w$ 指的是两个连通块已连接边的权值之和）；如果连接，对答案的贡献就是 $\min (c'_u,c'_v)+\sum w+w_i$。

比较二者大小，当 $c'_u+c'_v+\sum w\ge \min (c'_u,c'_v)+\sum w+w_i$ 时，化简得 $\max (c'_u,c'_v) \ge w_i$，此时在两点间连接电缆更优。反之不连接更优。

考虑代码实现，我们需要做一次正常的 kruskal，即因为图的最小生成树是不变的，我们要考虑的是在哪些点上建造发电站和选取哪些边连接电缆，不可能选取原来不在最小生成树上的边连接，原因根据最优性显然。所以我们另外开一个并查集记录当前连接电缆情况，在两点之间不用电缆连接更优时，我们也需要在最小生成树对应的并查集上合并两点所在集合，代表已经考虑过是否连接电缆，此时的 $w_i$ 已经比 $\max (c'_u,c'_v)$ 要大，往后枚举时 $w_j\ge w_i$，所以在两点所在的连通块上不可能连接电缆，所以无需考虑连接两个连通块的其他边。

时间复杂度为 $O(n^2\log n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,xi[2005],yi[2005],c[2005],k[2005];
struct edge{
	int u,v;
	long long w;
}e[4000005];
int fa[2005],link[2005];
int tot=0;
bool s[2005];
long long ans=0;
vector<pair<int,int> > v_edge;
bool cmp(edge x,edge y){return x.w<y.w;}
int find(int k){return (fa[k]==k)?k:fa[k]=find(fa[k]);}
int find_link(int k){return (link[k]==k)?k:link[k]=find(link[k]);}
void print(){
	cout<<ans<<"\n";
	int res=0;
	vector<int> v_res;
	for(int i=1;i<=n;i++) s[find_link(i)]=true;
	for(int i=1;i<=n;i++)
		if(s[i]) v_res.push_back(i),res++;
	cout<<res<<"\n";
	for(int i=0;i<res;i++) cout<<v_res[i]<<" ";
	cout<<"\n";
	cout<<n-res<<"\n";
	for(int i=0;i<n-res;i++) cout<<v_edge[i].first<<" "<<v_edge[i].second<<"\n";
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>xi[i]>>yi[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) cin>>k[i];
	for(int i=1;i<=n;i++){
		fa[i]=link[i]=i,ans+=1ll*c[i];
		for(int j=1;j<=n;j++)
			e[++tot].u=i,e[tot].v=j,e[tot].w=1ll*(k[i]+k[j])*(abs(xi[i]-xi[j])+abs(yi[i]-yi[j]));
	}
	sort(e+1,e+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		if(find(e[i].u)==find(e[i].v)) continue;
		int fu=find_link(e[i].u),fv=find_link(e[i].v);
		if(c[fu]<c[fv]) swap(fu,fv);
		if(c[fu]>=e[i].w){
			ans+=e[i].w-c[fu],link[fu]=fv;
			v_edge.push_back(make_pair(e[i].u,e[i].v));
		}
		fa[fu]=fv;
	}
	print();
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	/*int tt;cin>>tt;while(tt--)*/solve();
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：4)

考场上当Dijkstra写了(捂脸)  
我们假定有一个结点,是~~万恶~~电力之源。所有建造电站可以等效为与电力之源~~签订协议~~连接。  
于是所有操作变成了连边操作,那么直接当最小生成树套prim板子即可。  
```cpp
#include <cstdio>
#define ll long long

using namespace std;

const ll INF = 1e17 + 10;
const int N = 2345;

ll xi[N], yi[N], w[N], dis[N], vis[N], tlen;
int u[N], v[N], po[N], pre[N], etot, ptot, n;
inline ll min(ll x, ll y) { return x < y ? x : y; } 
inline ll fabs(ll x) { return x < 0 ? -x : x; }
inline ll getdis(int x, int y) { return (fabs(xi[x] - xi[y]) +  fabs(yi[x] - yi[y])) * (w[x] + w[y]); }
inline void addans(int x, int y) { u[etot] = x; v[etot++] = y; }
inline void addpo(int x) { po[ptot++] = x; }
inline void prim() {
	int cur = 0; dis[0] = INF;
	for(int i = 1; i <= n; ++i) if(dis[cur] > dis[i]) cur = i;
	tlen += dis[cur]; vis[cur] = 1;
	addpo(cur);
	for(int i = 1; i <= n; ++i) if(!vis[i]) {
		ll w = getdis(cur, i);
		if(w < dis[i]) dis[i] = w, pre[i] = cur;
	}
	for(int i = 1; i < n; ++i) {
		cur = 0;
		for(int i = 1; i <= n; ++i) if(!vis[i] && dis[i] < dis[cur]) cur = i;
		tlen += dis[cur];
		if(pre[cur]) addans(pre[cur], cur);
		else addpo(cur);
		vis[cur] = 1;
		for(int i = 1; i <= n; ++i) if(!vis[i]) {
			ll w = getdis(cur, i);
			if(w < dis[i]) dis[i] = w, pre[i] = cur;
		}
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%lld %lld", xi + i, yi + i);
	for(int i = 1; i <= n; ++i) scanf("%lld", dis + i);
	for(int i = 1; i <= n; ++i) scanf("%lld", w + i);
	prim();
	printf("%lld\n%d\n", tlen, ptot);
	for(int i = 0; i < ptot; ++i) printf("%d ", po[i]);
	printf("\n");
	printf("%d\n", etot);
	for(int i = 0; i < etot; ++i)
		printf("%d %d\n", u[i], v[i]);
	return 0;
}
```

---

