# オリンピックバス (Olympic Bus)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020ho/tasks/joi2020ho_d

JOI 国には $ N $ 個の都市があり，$ 1 $ から $ N $ までの番号が付いている．また，都市と都市を一方向に結ぶ $ M $ 本のバス路線があり，$ 1 $ から $ M $ までの番号が付いている．バス路線 $ i $ ($ 1\ \leqq\ i\ \leqq\ M $) は都市 $ U_i $ から都市 $ V_i $ へ向けて運行されており，運賃は $ C_i $ 円である．バス路線 $ i $ ($ 1\ \leqq\ i\ \leqq\ M $) では，都市 $ U_i $ 以外で乗ったり，都市 $ V_i $ 以外で降りることはできない．ある都市からある都市へ向けて運行されるバス路線が複数存在するかもしれない．

JOI 国では間もなくオリンピックが開催される．JOI 国の運輸大臣である $ K $ 理事長は，バス路線を高々 $ 1 $ つ選び，オリンピック期間中，運賃を変更せずにそのバス路線の運行方向を反転させることにした．つまり，バス路線 $ i $ ($ 1\ \leqq\ i\ \leqq\ M $) を選んだ場合，オリンピック期間中，そのバス路線は都市 $ U_i $ から都市 $ V_i $ へ向けて運行されるのではなく，都市 $ V_i $ から都市 $ U_i $ へ向けて運行されるようになる．ただし，バス路線 $ i $ の運行方向の反転には $ D_i $ 円かかり，これは K 理事長のポケットマネーにより賄われる．また，混乱を避けるため，オリンピック期間の途中でバス路線を反転させることはできない．

運輸大臣である K 理事長は，オリンピック期間中，都市 $ 1 $ と都市 $ N $ の間をバス路線を乗り継いで往復する予定である．運行方向を反転させるバス路線をうまく選ぶことで，往復の合計運賃と運行方向の反転の費用との和を最小化したい．

都市の個数と，バス路線の情報が与えられたとき，運行方向を反転させるバス路線をうまく選ぶことで，都市 $ 1 $ と都市 $ N $ の間の往復の合計運賃と，運行方向の反転の費用との和の最小値を求めるプログラムを作成せよ．ただし，どのようにバス路線を選んでも都市 $ 1 $ と都市 $ N $ の間を往復することができない場合は，代わりに $ −1 $ を出力せよ．

- - - - - -

## 说明/提示

### 制約

- $ 2\ \leqq\ N\ \leqq\ 200 $．
- $ 1\ \leqq\ M\ \leqq\ 50\,000 $．
- $ 1\ \leqq\ U_i\ \leqq\ N $ ($ 1\ \leqq\ i\ \leqq\ M $)．
- $ 1\ \leqq\ V_i\ \leqq\ N $ ($ 1\ \leqq\ i\ \leqq\ M $)．
- $ U_i\ \neq\ V_i $ ($ 1\ \leqq\ i\ \leqq\ M $)．
- $ 0\ \leqq\ C_i\ \leqq\ 1\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ M $)．
- $ 0\ \leqq\ D_i\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ M $)．

### 小課題

1. ($ 5 $ 点) $ M\ \leqq\ 1\,000 $．
2. ($ 11 $ 点) $ M $ は偶数，$ U_{2i\ −\ 1}\ =\ U_{2i} $，$ V_{2i\ −\ 1}\ =\ V_{2i} $，$ C_{2i\ −\ 1}\ =\ C_{2i} $ ($ 1\ \leqq\ i\ \leqq\ \frac{M}{2} $)．
3. ($ 21 $ 点) $ C_i\ =\ 0 $ ($ 1\ \leqq\ i\ \leqq\ M $)．
4. ($ 63 $ 点) 追加の制約はない．

- - - - - -

### Sample Explanation 1

バス路線 $ 2 $ の運行方向を費用 $ 1 $ で反転させると，都市 $ 1 $ から都市 $ 4 $ への移動にかかる運賃は最小で $ 6 $，都市 $ 4 $ から都市 $ 1 $ への移動にかかる運賃は最小で $ 3 $ となり，都市 $ 1 $ と都市 $ 4 $ の間の往復の合計運賃と，運行方向の反転の費用との和は $ 10 $ となる． 都市 $ 1 $ と都市 $ 4 $ の間の往復の合計運賃と，運行方向の反転の費用との和を $ 10 $ より小さくすることはできないので，$ 10 $ を出力する． - - - - - -

### Sample Explanation 2

この入出力例は小課題 $ 2 $ の制約を満たす． - - - - - -

### Sample Explanation 3

この入出力例は小課題 $ 3 $ の制約を満たす． - - - - - -

### Sample Explanation 4

バス路線の運行方向を反転させなくてもよい． - - - - - -

### Sample Explanation 5

この入力例では，都市 $ 4 $ から都市 $ 3 $ へと運行されるバス路線が $ 2 $ 本存在する．

## 样例 #1

### 输入

```
4 5
1 2 4 4
1 3 2 1
4 3 1 2
4 1 6 1
2 4 2 5```

### 输出

```
10```

## 样例 #2

### 输入

```
4 10
1 2 4 4
1 2 4 4
1 3 2 1
1 3 2 1
4 3 1 2
4 3 1 2
4 1 6 1
4 1 6 1
2 4 2 5
2 4 2 5```

### 输出

```
10```

## 样例 #3

### 输入

```
4 4
1 2 0 4
1 3 0 1
4 3 0 2
4 1 0 1```

### 输出

```
2```

## 样例 #4

### 输入

```
4 5
1 2 4 4
1 3 2 4
4 3 1 5
4 1 6 1
2 4 2 5```

### 输出

```
12```

## 样例 #5

### 输入

```
4 5
2 1 4 4
1 3 2 1
4 3 1 2
4 3 6 1
2 4 2 5```

### 输出

```
-1```

# 题解

## 作者：Mirage_Insane (赞：2)

将最短路去掉堆优化，枚举反转边就可以得到一个 $O(m \times n^2)$ 的做法，过不去。

容易发现只有当反转边在原图上处于最短路上时才需要重跑一遍最短路，否则直接用原图的最短路就可以了。而最短路最多也就经过 $n$ 条边，时间复杂度降为 $O(n ^ 3)$。~~这种不像是一种优化的优化是怎样。~~

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
int n, m, now[205][205], id[205][205], u[50005], v[50005], w[50005], d[50005];
void change(int x) {
	for(int i = 1; i <= 200; i++) {
		for(int j = 1; j <= 200; j++) now[i][j] = 1e18;
	}
	for(int i = 1; i <= m; i++) {
		if(i == x) swap(u[i], v[i]);
		if(now[u[i]][v[i]] > w[i]) {
			now[u[i]][v[i]] = w[i];
			id[u[i]][v[i]] = i;
		}
		if(i == x) swap(u[i], v[i]);
	}
	for(int i = 1; i <= n; i++) now[i][i] = 0;
}
int dp[205], pre[205];
bool vis[205];
int Dijkstra(int S, int T) {
	for(int i = 0; i <= n; i++) dp[i] = 1e18, vis[i] = 0, pre[i] = 0;
    dp[S] = 0;
    for(int i = 1; i <= n; i++) {
        int Min = 1e18, id = 0;
        for(int j = 1; j <= n; j++) {
        	if(!vis[j] && Min > dp[j]) {
        		Min = dp[j];
        		id = j;
			}
		}
		vis[id] = 1;
        for(int to = 1; to <= n; to++) {
        	if(dp[to] > dp[id] + now[id][to]) {
        		dp[to] = dp[id] + now[id][to];
        		pre[to] = id;
			}
		}
    }
    return dp[T];
}
bool book[50005];
void dfs(int x) {
	if(pre[x] == 0) return;
	book[id[pre[x]][x]] = 1;
	dfs(pre[x]);
}
int dis[205][205];
signed main() {
	SF("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++) SF("%lld%lld%lld%lld", &u[i], &v[i], &w[i], &d[i]);
	change(0);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) dis[i][j] = now[i][j];
	}
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		}
	}
	int ans = 0;
	ans += Dijkstra(1, n), dfs(n);
	ans += Dijkstra(n, 1), dfs(1);
	for(int i = 1; i <= m; i++) {
		if(book[i]) {
			change(i);
			int sum = 0;
			sum += Dijkstra(1, n);
			sum += Dijkstra(n, 1);
			ans = min(ans, sum + d[i]);
		}
		else {
			int sum = 0;
			sum += min(dis[1][v[i]] + w[i] + dis[u[i]][n], dis[1][n]);
			sum += min(dis[n][v[i]] + w[i] + dis[u[i]][1], dis[n][1]);
			ans = min(ans, sum + d[i]);
		}
	}
	PF("%lld", ans >= 1e18 ? -1ll : ans);
	return 0;
}
```

---

## 作者：modfisher (赞：2)

## 思路
直接枚举翻转的边是不现实的。即使使用 $O(n^2)$ 的 Dijkstra，其复杂度也达到了 $O(n^2m)$，完全过不去。

那么，是否存在一种方法，可以规避枚举边数过大的局限性呢？

考虑一条边，如果它既不在 $1$ 到 $n$ 的最短路径上，也不在 $n$ 到 $1$ 的最短路径上，那么将其反转后，计算它可能产生的新答案是简单的。

所以，不妨建立 $4$ 棵树：原图上以 $1$ 为根的最短路径树、原图上以 $n$ 为根的最短路径树、反图上以 $1$ 为根的最短路径树、反图上以 $n$ 为根的最短路径树。如果某条边 $(u,v)$ 不在这四棵树上，那么反转它必定不会影响所有最短路径的存在性。但是，可能存在一条新的经过 $(v,u)$ 的路径，使 $1$ 到 $n$ 的最短路变短。所以，只需要计算一下即可。

对于在这四棵树上的边，不超过 $4n$ 条，直接暴力跑 Dijkstra 即可。

复杂度 $O(n^3)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 205, maxm = 5e4 + 5;

int n, m;
vector<pair<int, ll> > G[2][maxn];
ll g[maxn][maxn], g2[maxn][maxn], dis[2][2][maxn], dis2[2][maxn];
int vis[maxn], pre[2][2][maxn];
map<pair<int, int>, int> mp;
int us[maxm], vs[maxm];
ll w1[maxm], ds[maxm];

void dijkstra(int st, int id){
	int p = 1;
	if(st == 1) p = 0;
	for(int i = 0; i <= n; i ++) dis[id][p][i] = (ll)1e18, vis[i] = 0;
	dis[id][p][st] = 0;
	for(int t = 1; t <= n; t ++){
		int x = 0;
		for(int j = 1; j <= n; j ++) if(!vis[j] && dis[id][p][j] < dis[id][p][x]) x = j;
		vis[x] = 1;
		for(int i = 0; i < G[id][x].size(); i ++){
			int j = G[id][x][i].first;
			if(dis[id][p][x] + G[id][x][i].second < dis[id][p][j]){
				dis[id][p][j] = dis[id][p][x] + G[id][x][i].second;
				pre[id][p][j] = x;
			}
		}
	}
}
void dijkstra2(int st){
	int id = st == n;
	for(int i = 0; i <= n; i ++) dis2[id][i] = (ll)1e18, vis[i] = 0;
	dis2[id][st] = 0;
	for(int t = 1; t <= n; t ++){
		int x = 0;
		for(int j = 1; j <= n; j ++) if(!vis[j] && dis2[id][j] < dis2[id][x]) x = j;
		vis[x] = 1;
		for(int j = 1; j <= n; j ++){
			if(dis2[id][x] + g2[x][j] < dis2[id][j]) dis2[id][j] = dis2[id][x] + g2[x][j];
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++) for(int j = 1; j <= n; j ++) if(i != j) g[i][j] = (ll)1e18;
	for(int i = 1; i <= m; i ++){
		int u, v;
		ll w, d;
		scanf("%d %d %d %d", &u, &v, &w, &d);
		us[i] = u, vs[i] = v, w1[i] = w, ds[i] = d;
		G[0][u].push_back(make_pair(v, w)), G[1][v].push_back(make_pair(u, w));
		g[u][v] = min(g[u][v], w);
	}
	dijkstra(1, 0), dijkstra(n, 0), dijkstra(1, 1), dijkstra(n, 1);
	for(int i = 1; i <= n; i ++){
		mp[make_pair(pre[0][0][i], i)] = 1;
		mp[make_pair(pre[0][1][i], i)] = 1;
		mp[make_pair(i, pre[1][0][i])] = 1;
		mp[make_pair(i, pre[1][1][i])] = 1;
		for(int j = 1; j <= n; j ++) g2[i][j] = g[i][j];
	}
	ll ans = dis[0][0][n] + dis[0][1][1];
	for(int i = 1; i <= m; i ++){
		if(!mp[make_pair(us[i], vs[i])]){
			ans = min(ans, ds[i] + min(dis[0][0][n], dis[0][0][vs[i]] + w1[i] + dis[1][1][us[i]]) + min(dis[0][1][1], dis[0][1][vs[i]] + w1[i] + dis[1][0][us[i]]));
		}else{
			g2[vs[i]][us[i]] = min(g2[vs[i]][us[i]], w1[i]);
			if(g2[us[i]][vs[i]] == w1[i]){
				bool fl = true;
				g2[us[i]][vs[i]] = (ll)1e18;
				for(int j = 0; j < G[0][us[i]].size(); j ++){
					if(G[0][us[i]][j].first == vs[i] && G[0][us[i]][j].second == w1[i]){
						if(fl){
							fl = false;
							continue;
						}else g2[us[i]][vs[i]] = min(g2[us[i]][vs[i]], G[0][us[i]][j].second);
					}
				}
			}
			dijkstra2(1), dijkstra2(n);
			ans = min(ans, ds[i] + dis2[0][n] + dis2[1][1]);
			g2[us[i]][vs[i]] = g[us[i]][vs[i]], g2[vs[i]][us[i]] = g[vs[i]][us[i]];
		}
	}
	printf("%lld\n", ans >= (ll)1e18 ? -1 : ans);
	return 0;
}
```

---

## 作者：wwwwwza (赞：1)

[一模一样的题](https://www.luogu.com.cn/problem/P6880)。

我们考虑一个最简单的 $O(m\times n^2)$ 的暴力，最短路用 $O(n^2)$ 的 Dijkstra 来求。

但是在每一次翻转路径中，可以发现有些时候求最短路是没有用的，换句话说，如果翻转的路径不是最短路上的路径，其答案是不会发生变化的。

所以，在枚举翻转的路径时，如果该路径时最短路上的路径，则 $O(n)$ 求整个最短路；若不是，则判断过这个翻转的路径会不会比最短路更优。

时间复杂度 $O(n^3)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e2+5;
const int M=5e4+5;
const int inf=1e12;
int n,m,x[M],y[M],c[M],d[M],dis[N][N],swp=0,ans=0,a=0,b=0,to[N];
bool vis[N],line[2][M];
struct node{
	int v,w,d,id,opt;
};
bool cmp(node p,node q){
	return p.w<q.w;
}
vector<node>g[N];
void dij(int s,int flag,int *dist){
	for(int i=1;i<=n;i++){
		dist[i]=inf;
		vis[i]=0;
	}
	dist[s]=0;
	for(int i=1;i<=n;i++){
		int u=0,minn=inf;
		for(int j=1;j<=n;j++){
			if(!vis[j]&&minn>dist[j]){
				minn=dist[j];
				u=j;
			}
		}
		vis[u]=1;
		for(int j=0;j<g[u].size();j++){
			int v=g[u][j].v,w=g[u][j].w,id=g[u][j].id,opt=g[u][j].opt;
			int pos=(swp==id?1:0);
			if(opt==pos&&!vis[v]&&dist[v]>dist[u]+w){
				dist[v]=dist[u]+w;
				to[v]=id;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(i==s)continue;
		if(flag==0)line[flag][to[i]]=1;
		if(flag==1)line[flag][to[i]]=1;
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld%lld",&x[i],&y[i],&c[i],&d[i]);
		g[x[i]].push_back({y[i],c[i],d[i],i,0});
		g[y[i]].push_back({x[i],c[i],d[i],i,1});
	}
	for(int i=1;i<=n;i++)sort(g[i].begin(),g[i].end(),cmp);
	for(int i=1;i<=n;i++)dij(i,(i==1?0:(i==n?1:2)),dis[i]);
	a=dis[1][n],b=dis[n][1];
	ans=a+b;
	for(int i=1;i<=m;i++){
		int res=d[i];
		swp=i;
		if(line[0][i])dij(1,2,dis[0]),res+=dis[0][n];
		else res+=min(a,dis[1][y[i]]+c[i]+dis[x[i]][n]);
		if(line[1][i])dij(n,2,dis[0]),res+=dis[0][1];
		else res+=min(b,dis[n][y[i]]+c[i]+dis[x[i]][1]);
		ans=min(ans,res);
	}
	if(ans>=inf)printf("-1");
	else printf("%lld",ans);
	return 0;
}

```

---

## 作者：Unnamed114514 (赞：0)

因为是稠密图，所以应该用 $O(n^2)$ 的 dij。

记录 $4$ 个东西：

- $dis_{1,i}$ 表示 $1$ 到 $i$ 在原图上的最短路。

- $dis_{2,i}$ 表示 $1$ 到 $i$ 在反图上的最段路。

- $dis_{3,i}$ 表示 $n$ 到 $i$ 在原图上的最短路。

- $dis_{4,i}$ 表示 $n$ 到 $i$ 在反图上的最段路。

首先，一条边不反转的情况就是 $dis_{1,n}+dis_{3,1}$。

如果反转了一条边 $(u,v,w,c)$，看看它会发生什么变化：

如果要发生变化的话，那么必须是一条 $1\to v\to u\to n$ 的路径，此时的答案就是 $dis_{1,v}+w+dis_{4,u}$。同理得到 $n\to 1$ 的答案是 $dis_{3,v}+w+dis_{2,u}$，当然还要分别和 $dis_{1,n},dis_{3,1}$ 取 $\min$。

所以最终答案就是：

$$\min\{dis_{1,n},dis_{1,v}+w+dis_{4,u}\}+\min\{dis_{3,1},dis_{3,v}+w+dis_{2,u}\}+c$$

但是没有这么简单，我们把一条边取反之后，$dis_1,dis_2,dis_3,dis_4$ 可能会变化。

但是发现变化的边都在原图和反图分别以 $1$ 和 $n$ 为根的最段路树上。也就是说，只有 $n$ 条边会影响 $dis_1,dis_2,dis_3,dis_4$。对于这些边，暴力算即可，剩下的边直接带入式子，时间复杂度 $O(n^3)$，可以通过。

---

