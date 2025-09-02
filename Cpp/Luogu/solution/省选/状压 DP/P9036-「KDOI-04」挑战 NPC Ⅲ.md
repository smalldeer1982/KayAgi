# 「KDOI-04」挑战 NPC Ⅲ

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/zn5t5x28.png)

## 题目描述

小 S 有一个伟大的梦想：证明 $\text{P}=\text{NP}$。

有一天，他得知一般图最大独立集是 NPC 问题后，决定解决他。

当然小 S 太菜了，解决不了，于是求助于你：

> 给出一个含有 $n$ 个顶点，$m$ 条边的无向图 $G$，求 $G$ 中大小恰好为 $n-k$ 的独立集的数量。由于答案可能很大，请将其对 $998~244~353$ 取模。

小 S 不喜欢多测，因为他在 NOIp 中因为多测挂分，所以本题包含多组测试数据。

## 说明/提示

**【样例解释】**

对于第 $1,2$ 组测试数据，图是完全图，容易发现，完全图的最大独立集为 $1$，并且每一个顶点都单独构成一个独立集。因此第 $1$ 组测试数据的答案为 $0$，第 $2$ 组测试数据的答案为 $4$。

对于第 $3$ 组测试数据，该组数据中给出的无向图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/abt8ho3b.png)

其中，所有大小为 $3$ 的独立集为：

+ $\{2,4,8\}$；
+ $\{2,3,7\}$；
+ $\{3,4,6\}$；
+ $\{2,4,6\}$；
+ $\{1,4,6\}$；
+ $\{2,3,6\}$；
+ $\{1,4,5\}$；
+ $\{2,3,4\}$。

**【数据范围】**

**本题采用捆绑测试。**

![数据范围](https://cdn.luogu.com.cn/upload/image_hosting/p3jwdqp3.png)

对于 $100\%$ 的数据，保证 $1\leq n\leq10^5$，$0\le m\le 10^5$，$0\leq k\leq \min(n-1,18)$，$1\leq T\leq 10^{4}$，$\sum n,\sum m\leq10^6$。

并且对于每个测试点保证：

设 $K=\max k$，即该测试点中所有 $k$ 的最大值，

+ 若 $K\ge 17$，则 $T=1$；
+ 若 $K\ge 15$，则 $T\le 3$；
+ 若 $K\ge 10$，则 $T\le 5$；
+ 若 $K\ge 5$，则 $T\le 300$。


## 样例 #1

### 输入

```
3
4 6 1
1 2
1 3
1 4
2 3
2 4
3 4
4 6 3
1 2
1 3
1 4
2 3
2 4
3 4
8 13 5
1 2
7 8
1 3 
2 5
3 8
6 8
4 7
5 6
5 7
5 8
6 7
1 8
3 5```

### 输出

```
0
4
8```

# 题解

## 作者：Alex_Wei (赞：18)

$n - k$ 的最大独立集唯一对应 $k$ 的点覆盖集。

忽略重边。

对于度数大于 $k$ 的点，若其没有被选择，则与其相连的所有点均被选择，与大小为 $k$ 矛盾。因此，度数大于 $k$ 的点一定被选择。

进一步地，因为接下来每次选择时，覆盖的边数均不超过 $k$，所以当未被覆盖的边数大于 $k ^ 2$ 时，无解。

因为 $k$ 很小，考虑爆搜。

$\mathcal{O}(k ^ 2)$ 找到任意一条未被覆盖的边，选择覆盖其左端点或右端点，至多进行 $k$ 次这样的操作。若当前所有边均被覆盖，设点覆盖集大小为 $c$，则答案加上 $\binom {n - c} {k - c}$。

看似很简单，但是这样会算重：在 $\binom {n - c} {k - c}$ 种方案中，选到我们关注的某条边的另一个端点时，可能与在该分支选择该端点的方案重复。

为避免这种情况，我们需要在找到一条边时，同时确定其两端是否在最终点覆盖集中，也就是除了被选进点覆盖集，一个点还有可能被钦定不可以选进覆盖集。

因为一条边的两端不可能同时不在点覆盖集中，所以只有以下情况：

- 两端均在点覆盖集，大小加 $2$；
- 一端在点覆盖集，另一端不在，两种情况大小均加 $1$。

复杂度递推式为 $\mathcal{T}(k) = 2\mathcal{T}(k - 1) + \mathcal{T}(k - 2)$，但是跑不满（找到一条边的某端钦定不在点覆盖集中时，另一端必须在点覆盖集中）。

时间复杂度 $\mathcal{O}(\mathcal{T}(k) k ^ 2 + m\log m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int mod = 998244353;
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}
int fc[N], ifc[N];
int bin(int n, int m) {return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;}
int n, m, k, ans;
int u[N], v[N], ban[N];
set<int> e[N];
vector<int> buc;
void dfs(int rest, int cur) {
  if(cur > k) return;
  int e = -1;
  for(auto it : buc)
    if(ban[u[it]] != 1 && ban[v[it]] != 1) {
      e = it;
      break;
    }
  if(e == -1) {
    ans = (ans + bin(rest, k - cur)) % mod;
    return;
  }
  int &x = ban[u[e]], &y = ban[v[e]];
  if(x == 2 && y == 2) return;
  if(x == 2 && y == 0) y = 1, dfs(rest - 1, cur + 1), y = 0;
  if(x == 0 && y == 2) x = 1, dfs(rest - 1, cur + 1), x = 0;
  if(x == 0 && y == 0) {
    x = 1, y = 1, dfs(rest - 2, cur + 2);
    x = 1, y = 2, dfs(rest - 2, cur + 1);
    x = 2, y = 1, dfs(rest - 2, cur + 1);
    x = y = 0;
  }
}
int solve() {
  cin >> n >> m >> k, ans = 0;
  for(int i = 1; i <= n; i++) e[i].clear(), ban[i] = 0;
  for(int i = 1; i <= m; i++) {
    cin >> u[i] >> v[i];
    if(e[u[i]].find(v[i]) != e[u[i]].end()) i--, m--;
    e[u[i]].insert(v[i]);
    e[v[i]].insert(u[i]);
  }
  int cnt = 0;
  for(int i = 1; i <= n && cnt <= k; i++)
    if(e[i].size() > k - cnt) {
      ban[i] = 1, cnt++;
      for(int it : e[i]) e[it].erase(i);
    }
  if(cnt > k) return 0;
  buc.clear();
  for(int i = 1; i <= m; i++)
    if(ban[u[i]] != 1 && ban[v[i]] != 1)
      buc.push_back(i);
  if(buc.size() > k * (k - cnt)) return 0;
  dfs(n - cnt, cnt);
  return ans;
}
int main() {
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for(int i = fc[0] = 1; i < N; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[N - 1] = ksm(fc[N - 1], mod - 2);
  for(int i = N - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  int T;
  cin >> T;
  while(T--) cout << solve() << "\n";
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

每次选度数不为 $0$ 的点或其周围所有点可以做到 $\mathcal{T}(k) = 2 ^ k$。

---

## 作者：_Diu_ (赞：8)

bxzxx。

月赛快结束的时候听同学说这题很难不会，就去看了看，口炮说我会了没人信。~~难道我的信誉这么差吗~~，所以赛后写了下。

感觉是道小清新题，挺有意思的，写一篇题解。

看到 $k$ 很小而要求是选 $n-k$ 的独立集，容易想到等价于选大小为 $k$ 的点覆盖。

$k$ 的数据范围大概支持一个近似 $O(2^kk)$ 的做法，容易向状压的方向思考，但发现不好设状态，因此先不考虑。可以考虑暴搜。

暴搜复杂度 $O(\binom nk)$ 显然不能接受，因此需要剪枝优化复杂度。最理想的情况是能搜到 $O(2^k)$ 种不同的状态，然后每一种需要一个较小的复杂度转移。

我们可以选出 $k$ 个特殊点，依次枚举，容易发现一个很好的性质，对于一个点，如果我们不选他，就要把他的所有连边都给选上。如果每次枚举的特殊点的出边都 $\ge1$，那么每次不管选还是不选 $k$ 都至少减 $1$，所以最多枚举 $k$ 层。

进一步发现选的 $k$ 个点不一定要是固定的。因为决定选择一个点 $k$ 之后，它的所有连边都失效了，所以可以考虑动态地选点。每次选择当前情况下度数最大的点，要么把他扣掉要么把他的连边都扣掉。

可以先把度数 $>k$ 的点选了，这些点是必选的。这样剩下的过程可以搜索，用 `set` 维护度数最大的点，每次删点最多只会有 $O(k)$ 个点的度数收到影响（度数大的都删完了）。这样复杂度是 $O(2^kk\log n)$。如果到所有剩下的点的度数都为 $0$，此时剩下的点可以乱选，组合数直接计算。注意计算的时候要把前面强制没选的点给删掉。

常数较小，实现比较简单，总体来说作为月赛 D 可能较简单，idea 个人感觉比较新颖~~至少我没见过~~。感谢 KDOI 出题组的高质量题目，再次 bxzxx。

注意搜完回溯的时候把点加回来避免影响之后的搜索，注意顺序，因为删点操作只支持按顺序撤销；还要注意判掉重边，因为上面做法都和度数有关。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,K=20,p=998244353;
int T,n,m,k,d[N],vis[N],id[N];
int C[N][K];
vector<int> g[N];
bool cmp(int a,int b){return d[a]<d[b];}
set<pair<int,int> > s;
int ans;
void erase(int x){
	s.erase(make_pair(-d[x],x));
	vis[x]=1;
	for(int y:g[x])if(!vis[y]){
		s.erase(make_pair(-d[y],y));
		--d[y];
		s.insert(make_pair(-d[y],y));
	}
}
void insert(int x){
	s.insert(make_pair(-d[x],x));
	vis[x]=0;
	for(int y:g[x])if(!vis[y]){
		s.erase(make_pair(-d[y],y));
		++d[y];
		s.insert(make_pair(-d[y],y));
	}
}
void dfs(int x,int num){
	if(s.empty()||s.begin()->first==0){
		ans=(ans+C[num][x])%p;
		return;
	}
	if(!x)return;
	int t=s.begin()->second;
	erase(t),dfs(x-1,num-1),insert(t);
	if(d[t]>x||x==num)return;
	int st[K],tp=0;
	for(int y:g[t])if(!vis[y])erase(y),st[++tp]=y;
	dfs(x-tp,num-tp-1);
	for(int i=tp;i>=1;i--)insert(st[i]);
}
map<int,int> mp[N];
signed main(){
	scanf("%d",&T);
	C[0][0]=1;
	for(int i=1;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=min(i,K-1);j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	}
	for(;T--;){
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=n;i++){
			d[i]=vis[i]=0,id[i]=i;
			g[i].clear(),mp[i].clear();
		}
		for(int u,v;m--;){
			scanf("%d%d",&u,&v);
			if(u>v)swap(u,v);
			if(mp[u][v])continue;
			mp[u][v]=1;
			g[u].push_back(v),g[v].push_back(u);
			d[u]++,d[v]++;
		}
		stable_sort(id+1,id+n+1,cmp);
		int nn=n;
		while(k>=0&&d[id[n]]>k){
			for(int x:g[id[n]])if(!vis[x])d[x]--;
			vis[id[n]]=1;
			--n,--k;
		}
		if(k<0){puts("0");continue;}
		s.clear();
		for(int i=1;i<=nn;i++)if(!vis[i])s.insert(make_pair(-d[i],i));
		ans=0;
		dfs(k,n);
		printf("No Copy:%d\n",ans);
	}
}
```

---

## 作者：Jorisy (赞：3)

注意到 $k$ 很小，考虑转化题意。

不难发现独立集 $A$ 的补集 $B$ 恰好是图 $G$ 的一个点覆盖，即 $B$ 内所有点与其相连的边构成集合大小恰好为 $m$。因此 $A$ 和 $B$ 构成一个一一对应，故原问题可以转化为大小恰好为 $k$ 的点覆盖计数。

这也太 NPC 了，我们似乎只能爆搜了！！

所以我们先考虑一些优化来减小搜索规模。

首先，对于一个度数 $>k$ 的节点，我们必然是会选择的，否则为了覆盖与它相连的边，我们必须把这些边另外的 $>k$ 的点都选中，这就和恰好选 $k$ 个矛盾了。

其次，进一步地，我们这样剩下来所要覆盖的边的条数不超过 $k^2$，如果超过了，自然就无解。

这样的话，我们就剩下了 $O(k^2)$ 条边。

然后我们开始爆搜！！！

记 $a_i$ 表示节点 $i$ 被选的状态：
- $0$ 表示未确定。
- $1$ 表示一定被选入点覆盖集。
- $2$ 表示一定不被选入点覆盖集。

记 $\text{dfs}(x,r)$ 表示已经选择了 $x$ 个点加入点覆盖集，还剩下 $r$ 个点没有被确定。

那么，首先找到一条没有被覆盖的边 $(u,v)$。
- 若所有边当前已经被恰好覆盖了，那么只要让剩下还没选的随便选即可，即答案加上 $\binom{r}{k-x}$。
- 若 $a_u=a_v=2$，那么这是不合法的，直接跳出。
- 若 $a_u=0,a_v=2$，那么令 $a_u=1$，进入 $\text{dfs}(x+1,r-1)$。
- 若 $a_u=2,a_v=0$，那么令 $a_v=1$，进入 $\text{dfs}(x+1,r-1)$。
- 若 $a_u=a_v=0$，那么依次地：
  - 令 $a_u=a_v=1$，进入 $\text{dfs}(x+2,r-2)$。
  - 令 $a_u=1,a_v=2$，进入 $\text{dfs}(x+1,r-2)$。
  - 令 $a_u=2,a_v=1$，进入 $\text{dfs}(x+1,r-2)$。

最后注意处理重边的情况。

时间复杂度大约为 $O(2^kk^2)$。

---

## 作者：船酱魔王 (赞：3)

# P9036 「KDOI-04」挑战 NPC Ⅲ 题解

## 题意回顾

求出 $ n $ 点 $ m $ 边的无向图的大小为 $ n-k $ 的最大独立集的个数。

多测，$ T $ 组数据。

$ 1 \le n \le 10^5 $，$ 0 \le m \le 10^5 $，$ 0 \le k \le \min\{n-1,18\} $，$ 1 \le T \le 10^4 $，$ \sum n, \sum m \le 10^6 $。

数据范围不会同时取到上界，若一个测试点内最大的 $ k $ 的到达一定数值后，该测试点的 $ T $ 会有很严的限制（具体见原题面）。

## 分析

因为需要计算每个点的度数，先用 `set` 处理掉重边。

一般图最大独立集问题没有多项式时间做法，突破口在于 $ k $ 很小。

我们可以考虑不选哪些点，每条边都必须至少有一个端点被是不选的点，即选出 $ k $ 个点覆盖所有边，即找到大小为 $ k $ 的点覆盖集。

如果一个点的度数大于 $ k $，则这个点必须被选入点覆盖集，因为如果不选入的话为了覆盖这个点的所有连边，需要超过 $ k $ 个点选入点覆盖集，与大小为 $ k $ 矛盾。

实现时，我们每次找到一个度数大于 $ k $ 的点选入点覆盖集，将所有连边删除（因为已经覆盖），将 $ k $ 减少 $ 1 $，重复以上过程直到 $ k<0 $（即无解）或不存在度数大于 $ k $ 的点。

本代码中使用了线段树找最大值，但是因为只用找 $ k $ 次最大值且 $ k $ 很小其实没必要。

若未被覆盖边数大于 $ k^2 $，则无解，因为每个点度数不超过 $ k $，$ k $ 次选点最多覆盖 $ k^2 $ 条边（实际上不加这个特判也可过）。

此时我们剩下很多孤点，不超过 $ k^2 $ 条边，考虑设计爆搜枚举。每次覆盖一条未被覆盖的边，选择选入两个端点还是选入一个端点，**注意未被选入点覆盖集的点的状态需要设计为不可被选而不是未被选，否则会算重。**

如果所有边已经被覆盖，即剩下的全是孤点，可以直接组合数解决，需要用杨辉三角预处理组合数。

因为每次至少选入 $ 1 $ 个点以实现覆盖，所以最多搜 $ k $ 层，复杂度有保证。

一种写假的方式是将已经覆盖的边未确定是否选入的端点继续搜索，可以通过构造很多个互不相连的的菊花图来卡掉，会把时间复杂度卡到 $ O(2^{k^2}) $ 量级。应该没有这种极限数据所以如果想过的话可以把搜边的顺序随机打乱（实测可过）。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
const int mod = 998244353;
const int N = 1e5 + 5;
const int K = 19;
int T;
int n, m, k;
vector<int> g[N];
int deg[N];
struct node {
	int id;
	int val;
} d[N * 4], zero;
node operator+(node p1, node p2) {
	node res = zero;
	if(p1.val < p2.val) {
		res.id = p2.id, res.val = p2.val;
	} else {
		res.id = p1.id, res.val = p1.val;
	}
	return res;
}
void build(int s, int t, int p) {
	if(s == t) {
		d[p].id = s, d[p].val = deg[s];
		return;
	}
	int mid = (s + t) >> 1;
	build(s, mid, p * 2);
	build(mid + 1, t, p * 2 + 1);
	d[p] = d[p * 2] + d[p * 2 + 1];
}
void update(int x, int v, int s, int t, int p) {
	if(s == t) {
		d[p].val = v;
		return;
	}
	int mid = (s + t) >> 1;
	if(x <= mid) update(x, v, s, mid, p * 2);
	else update(x, v, mid + 1, t, p * 2 + 1);
	d[p] = d[p * 2] + d[p * 2 + 1];
}
int valid[N];
struct Edge {
	int u;
	int v;
	Edge(int uu, int vv) {
		u = uu;
		v = vv;
	}
};
bool operator<(Edge p1, Edge p2) {
	if(p1.u != p2.u) return p1.u < p2.u;
	return p1.v < p2.v;
}
vector<Edge> eg;
int c[N][K];
int ind;
int ans = 0;
int sta[N];
void solve(int csn) {
	if(csn > k) return;
	int id = -1;
	for(int i = 0; i < eg.size(); i++) {
		if(sta[eg[i].u] == 2 && sta[eg[i].v] == 2) return;
		if(sta[eg[i].u] != 1 && sta[eg[i].v] != 1) {
			id = i;
			break;
		}
	}
	if(id == -1) {
		ans += c[ind][k - csn];
		ans %= mod;
		return;
	}
	int u, v;
	u = eg[id].u, v = eg[id].v;
	int tu, tv;
	tu = sta[u], tv = sta[v];
	if(tu == 2 && tv == 2) return;
	for(int su = 1; su <= 2; su++) {
		for(int sv = 1; sv <= 2; sv++) {
			if(su == 2 && sv == 2) continue;
			if(tu != 0 && su != tu) continue;
			if(tv != 0 && sv != tv) continue;
			sta[u] = su, sta[v] = sv;
			ind -= (int)(tu == 0) + (int)(tv == 0);
			solve(csn + (int)(tu == 0 && su == 1) + (int)(tv == 0 && sv == 1));
			ind += (int)(tu == 0) + (int)(tv == 0);
		}
	}
	sta[u] = tu, sta[v] = tv;
}
set<Edge> se;
int main() {
	scanf("%d", &T);
	c[0][0] = 1;
	for(int i = 1; i <= 100000; i++) {
		c[i][0] = 1;
		for(int j = 1; j <= min(i, 18); j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
	for(int ti = 1; ti <= T; ti++) {
		scanf("%d%d%d", &n, &m, &k);
		int u, v;
		for(int i = 1; i <= n; i++) {
			g[i].clear();
			deg[i] = 0;
			valid[i] = 1;
		}
		se.clear();
		ans = 0;
		eg.clear();
		for(int i = 1; i <= m; i++) {
			scanf("%d%d", &u, &v);
			if(u > v) swap(u, v);
			if(se.find(Edge(u, v)) != se.end()) continue;
			se.insert(Edge(u, v));
			g[u].push_back(v);
			g[v].push_back(u);
			deg[u]++;
			deg[v]++;
		}
		build(1, n, 1);
		while(k >= 0) {
			u = d[1].id;
			if(deg[u] <= k) break;
			valid[u] = 0;
			update(u, 0, 1, n, 1);
			deg[u] = 0;
			k--;
			for(int i = 0; i < g[u].size(); i++) {
				v = g[u][i];
				deg[v]--;
				update(v, deg[v], 1, n, 1);
			}
		}
		if(k < 0) {
			printf("0\n");
			continue;
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < g[i].size(); j++) {
				v = g[i][j];
				if((valid[i] == 1) && (valid[v] == 1) && i < v) {
					eg.push_back(Edge(i, v));
				}
			}
		}
		if(eg.size() > k * k) {
			printf("0\n");
			continue;
		}
		ind = 0;
		for(int i = 1; i <= n; i++) {
			if(valid[i] == 1) ind++;
		}
		solve(0);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意

对于一个 $n$ 个点，$m$ 条边的图，求这个图中大小为 $n-k$ 的独立集数量。

大小为 $n-k$ 的独立集，简单来讲就是选 $k$ 个点，使得所有边都至少有一个顶点被选。

### 题目分析

这道题一看 $n,m$ 都很大，但是 $k$ 才 $18$，所以肯定要在 $k$ 上面下手。

对于纯暴力，暴力枚举选哪 $k$ 个点的话是 $\mathcal O(n ^k)$ 的。

然后考虑有哪些点事必须选的，首先如果一个点没被选，要使他所有连边都被选，则至少需要将这些边的另一个顶点选上。由此可得如果一个点的度大于 $k$，则这个点必须选否则选 $k$ 个点后一定不能覆盖完这个点连出的边。

如果将这些点都选去后，则剩下的点度数都不大于 $k$，然后我们再来考虑，如果选任意一点，至多只能覆盖 $k$ 条边，于是我们就可以得出选 $k$ 个点后，至多覆盖 $k^2$ 调边，即现在剩下的边数一定不大于 $k ^ 2$ 条，否则一定覆盖不全。

对于一个只有 $k^2$ 条边的图，就已经很小了，于是我们就可以考虑暴力一点的算法了，就是暴力枚举每条边的被覆盖状态。假设一条边的两顶点是 $u,v$，且这条边未被覆盖，那么可能的状态只有：选 $u,v$；选 $u$；选 $v$。三种。最后枚举完会有一些点我们可选可不选，也有可能剩一些选点名额，我们排列组合计算答案即可。

于是我们就可以设计出一个 $3 ^ {k^2}$ 的算法，并且由于这 $k^2$ 条边最开始都是没被覆盖的，所以每枚举完一条边 $k$ 都会减小，所以跑不满，大概只能跑到 $3 ^ k$ 的级别，可过。

### 坑点

1. 最开始的图可能有重边，所以在计算每个点的度数的时候要先判重。

2. 枚举边的状态是，我们所记录的状态应是：选 $u,v$；选 $u$ 且以后不能选 $v$；选 $v$ 且以后不能选 $u$。

（因为如果开始枚举的是选 $u$，后面又把 $v$ 选上了，这种情况跟选 $u,v$ 的情况会算重）

3. [（本人卡了 5 天交了 18 发的错误）](https://www.luogu.com.cn/discuss/800673)，我们枚举完最后计算答案的事后需要知道哪些点可选可不选，这时如果我们再遍历一遍所有点的状态的话时间复杂度就是 $\mathcal O(3 ^k \times n)$，凭空多出 $10^6$ 会导致最后两个 subtask 直接 T 掉。所以我们边枚举边维护可选可不选的点的数量即可。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

const int N = 1e5 + 5, K = 25, MOD = 998244353;
int T, n, m, k, du[N], ans, c[N][K];
int flag[N];	//0-待定,1-留,2-选 
set <int> e[N];		//set建边，自动去重，还可以直接删边
vector <pair <int, int> > v;

void change(int x, int goal)
{
	flag[x] = goal;
	if(goal == 2)
	{
		du[x] = 0, k--;
		for(set<int>::iterator it = e[x].begin();it != e[x].end();it++)
			if(flag[*it] == 0 && du[*it])
				du[*it]--, e[*it].erase(x);
	}
	return ;
}	//覆盖点 x，状态为 goal

inline void dfs(int x, int kk, int sum)
{
	if(kk < 0)
		return ;
	while(x < v.size() && (flag[v[x].first] == 2 || flag[v[x].second] == 2))
		x++;
	if(x == v.size())
	{
		(ans += c[sum][kk]) %= MOD;
		//printf("%d %d\n", tmp, ans);
		return ;
	}
	if(flag[v[x].first] == 0)
	{
		if(flag[v[x].second] == 1)
		{
			flag[v[x].first] = 2;
			dfs(x + 1, kk - 1, sum - 1);
			flag[v[x].first] = 0;
		}
		else if(flag[v[x].second] == 0)
		{
			flag[v[x].first] = 2, flag[v[x].second] = 2;
			dfs(x + 1, kk - 2, sum - 2);
			flag[v[x].first] = 1, flag[v[x].second] = 2;
			dfs(x + 1, kk - 1, sum - 2);
			flag[v[x].first] = 2, flag[v[x].second] = 1;
			dfs(x + 1, kk - 1, sum - 2);
			flag[v[x].first] = 0, flag[v[x].second] = 0;
		}
	}
	if(flag[v[x].first] == 1)
	{
		if(flag[v[x].second] == 0)
		{
			flag[v[x].second] = 2;
			dfs(x + 1, kk - 1, sum - 1);
			flag[v[x].second] = 0;
		}
	}
	return ;
}

inline void solve()
{
	v.clear(), ans = 0;
	scanf("%d %d %d", &n, &m, &k);
	for(register int i = 0;i <= n;i++)	du[i] = flag[i] = 0, e[i].clear();
	for(register int i = 1, u, v;i <= m;i++)
	{
		scanf("%d %d", &u, &v);
		e[u].insert(v);
		e[v].insert(u);
	}
	for(register int i = 1;i <= n;i++)	du[i] = e[i].size();
	while(k >= 0)
	{
		int mx = 0;
		for(register int i = 1;i <= n;i++)	if(du[i] > du[mx])	mx = i;
		if(du[mx] <= k)	break;
		change(mx, 2);
		//printf("%d\n", k);
	}
	if(k < 0)
	{
		puts("0");
		return ;
	}
	for(register int i = 1;i <= n;i++)
	{
		for(set<int>::iterator it = e[i].begin();it != e[i].end();it++)
		{
			if(*it <= i || flag[i] == 2 || flag[*it] == 2)
				continue;
			v.push_back(make_pair(i, *it));
			if(v.size() > k * k)
			{
				puts("0");
				return ;
			}
		}
	}
	//printf("edge:%d\n", v.size());
	int tmp = 0;
	for(register int i = 1;i <= n;i++)
		if(flag[i] == 0)	tmp++;
	dfs(0, k, tmp);
	//for(int i = 1;i <= 15;i++)	printf("%d\n", sum[i]);
	printf("%d\n", ans);
	return ;
}

signed main()
{
	for(register int i = 0;i <= 100000;i++)	c[i][0] = 1;
	for(register int i = 1;i <= 100000;i++)
		for(register int j = 1;j <= min(i, 18);j++) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
	//提前预处理排列组合优化常数
	scanf("%d", &T);
	while(T--)	solve();
	return 0;
}
```

---

## 作者：JohnVictor (赞：2)

考虑爆搜。

首先用一个类似拓扑排序的过程删去所有度数大于 $k$ 的点，把 $k$ 减去这个数字。如果还有就继续做。这一部分复杂度 $O(mk)$。

现在考虑所有点度数不超过 $k$，那么就只有最多 $k(k+1)$ 个度数非零的点，否则答案一定为 $0$。

现在，我们证明一个足够优化了的爆搜是能通过本题的。

具体地，设 $f(S,k)$ 表示对于一个只保留 $S$ 中的点的诱导子图求出所有 $k'=0,1,\cdots,k$ 对应的答案形成的一个多项式。如果 $S$ 不联通，那么只用将不同连通块对应的多项式卷积。特别地，最开始的 $0$ 度点也可以先算出贡献并卷积。

现在考虑度数最大的点 $u$，设它的度数为 $t$。那么显然 $f(S,k)=f(S\setminus \{u\},k-1)x+f(S\setminus N(u),k-t)x^t$，因为两项分别表示枚举 $u$ 选或者不选。

我们注意到 $t \le 2$ 的情况一定是森林，可以简单 $\text{dp}$ 解决，反之 $t \ge 3$。这样我们已经可以分析出状态数为 $O(\lambda ^k)$ 其中 $\lambda $ 为 $x^3-x^2-1$ 的根。稍作分析能得到远远好于此的界，不过这里不再展开。

这里是一份实现的极其粗糙的代码，这一部分的最坏复杂度为 $(\frac{1+\sqrt{5}}{2})^k \text{poly}(k)$，可以通过 $k=24$ 的数据。如果想要写的更好可以把所有上述优化都加上，并且把每个状态的复杂度优化到线性。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
const int p=998244353,N=100005;
typedef long long ll;
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

int n,m,k,deg[N],vis[N],rev[N],M;vector<int>e[N];int f[400][400],c[N][20],pw2[N];
int dfs(vector<int>all,int k){
	if(k<0)return 0;
	if(all.empty()){
		if(k==0)return 1;return 0;
	}
	int sz=all.size();
	vector<int>deg;deg.resize(M+1);int flg=0,pl=0;
	for(auto u:all)for(auto v:all)if(f[u][v])++deg[u];
	for(auto u:all)if(deg[u]>flg)flg=deg[u],pl=u;
	if(!flg)return c[sz][k];
	if(flg==1){
		int tt=0;if(sz<2*tt)return 0;
		int ans=0;
		rep(i,0,min(k-tt,tt))ans=(ans+(1ll*pw2[tt-i]*c[tt][i]%p)*c[sz-2*tt][k-tt-i])%p;
		return ans;
	}
	vector<int>f1,f2;f1.clear();f2.clear();
	for(auto v:all){
		if(v!=pl)f1.pb(v);
		if(v!=pl&&f[pl][v]==0)f2.pb(v);
	}
	return (dfs(f1,k-1)+dfs(f2,k-deg[pl]))%p;
}
void solve(){
	cin>>n>>m>>k;rep(i,1,n)deg[i]=vis[i]=rev[i]=0,e[i].clear();int kk=k;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;assert(u!=v);if(u!=v)e[u].pb(v),e[v].pb(u);
	}
	rep(i,1,n)sort(e[i].begin(),e[i].end());
	rep(i,1,n){
		auto last=unique(e[i].begin(),e[i].end());e[i].erase(last,e[i].end());
	} 
	rep(i,1,n)deg[i]=e[i].size();
	vector<int>slv;rep(i,1,n)if(deg[i]>k)slv.pb(i);
	for(auto u:slv)if(deg[u]>k){
		for(auto v:e[u])if(!vis[v])--deg[u],--deg[v];--k;vis[u]=1;
	}
	int cnt=0;
	vector<int>all;
	rep(i,1,n)if(!vis[i]){
		if(deg[i]>0)all.pb(i);else cnt++;
	}
	int sz=all.size();if(sz>kk*(kk+1)){
		printf("0\n");return;
	}
	rep(i,0,sz)rep(j,0,sz)f[i][j]=0;M=sz;
	rep(i,0,sz-1)rev[all[i]]=i+1;
	rep(i,0,sz-1)for(auto v:e[all[i]])if(!vis[v])f[i+1][rev[v]]=1;
	all.clear();rep(i,0,sz-1)all.pb(i+1);
	int ans=0;//printf("k=%d cnt=%d\n",k,cnt);
	rep(i,0,k)ans=(ans+1ll*c[cnt][i]*dfs(all,k-i))%p;
	printf("%d\n",ans);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	pw2[0]=1;rep(i,1,1e5)pw2[i]=2*pw2[i-1]%p;
	rep(i,0,1e5)c[i][0]=1;
	rep(i,1,1e5)rep(j,1,18)c[i][j]=(c[i-1][j]+c[i-1][j-1])%p;
	int _;cin>>_;while(_--)solve();
	return 0;
}
```

---

## 作者：zhouyuhang (赞：1)

将大小为 $n-k$ 的独立集转化为选出恰好 $k$ 个点，覆盖所有的边。考察所有度数大于 $k$ 的点，都有其必然被选（否则需要选出所有邻点，与恰 $k$ 个的要求矛盾）。

从原图中删去这些点可以得到一个新图。注意到点集所覆盖的边数不大于所有点度数之和的一半，因此有新图边与非孤立点的数量均为 $O(k^2)$。

在这样一个大小较小的图上，我们可以考虑搜索出每个点的选与不选。加入以下剪枝：

- 将点按照度数从大到小排序。
- 若当前剩余未被覆盖边数大于随后相应数量点的度数和，返回。
- 若已经覆盖所有边，则剩余的选法数量是一个组合数。

复杂度不会算，但是可以过。

记录：https://www.luogu.com.cn/record/101471135

---

## 作者：lyhqwq (赞：0)

# Solution

喵喵题。

注意到 $n-k$ 很大而 $k$ 很小，我们就可以把找独立集转化为找大小为 $k$ 的覆盖。

对于入度 $>k$ 的节点，它一定包含在覆盖里，否则与它相连的每一个节点都会被包含，与覆盖的大小为 $k$ 矛盾。

我们用一个类似拓扑的方式，把一定要选的点找出来，已经被覆盖的边删除。

剩下的边我们考虑暴捜。对于一条没有被覆盖的边，我们钦定他的两个端点是否被选择，如果所有的边都被覆盖，那么剩下的点就可以随意选择，用组合数计算答案。

这样看似是 $O(2^m)$ 的，但是我们剩余的节点的度数都 $\leq k$ ，即每选择一个节点，我们最多会覆盖 $k$ 条边。而我们最多再选择 $k$ 个结点，所以当剩余的边数 $>k^2$ 时答案为 $0$。

时间复杂度不会分析，为 $O(\text{能过})$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
const int Mod=998244353;
int _;
int n,m,k,ans;
int vis[N];
int fac[N],inv[N];
set<int> s[N];
vector<pair<int,int> > e;
int qpow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=a*a%Mod) if(b&1) ans=ans*a%Mod;
    return ans;
}
int C(int n,int m){
    if(n<m) return 0;
    return fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
void dfs(int rst,int now){
    if(now>k) return;
    int id=-1;
    for(int i=0;i<e.size();i++){
        if(vis[e[i].first]!=1&&vis[e[i].second]!=1){
            id=i;
            break;
        }
    }
    if(id==-1){
        ans=(ans+C(rst,k-now))%Mod;
        return;
    }
    int u=e[id].first,v=e[id].second;
    if(vis[u]==2&&vis[v]==2) return;
    if(vis[u]==2&&vis[v]==0) vis[v]=1,dfs(rst-1,now+1),vis[v]=0;
    if(vis[u]==0&&vis[v]==2) vis[u]=1,dfs(rst-1,now+1),vis[u]=0;
    if(vis[u]==0&&vis[v]==0){
        vis[u]=1,vis[v]=2,dfs(rst-2,now+1);
        vis[u]=2,vis[v]=1,dfs(rst-2,now+1);
        vis[u]=1,vis[v]=1,dfs(rst-2,now+2);
        vis[u]=vis[v]=0;
    }
}
signed main(){
    //freopen("P9036_110.in","r",stdin);
    //freopen("114.out","w",stdout);
    scanf("%lld",&_);
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    for(int i=0;i<N;i++) inv[i]=qpow(fac[i],Mod-2);
    while(_--){
        scanf("%lld%lld%lld",&n,&m,&k);
        ans=0;
        for(int i=1;i<=n;i++) vis[i]=0,s[i].clear();
        e.clear();
        for(int i=1,u,v;i<=m;i++){
            scanf("%lld%lld",&u,&v);
            s[u].insert(v);
            s[v].insert(u);
        }
        int cnt=0;
        while(cnt<=k){
            int p=0;
            for(int i=1;i<=n;i++) if(s[i].size()>s[p].size()) p=i;
            if(s[p].size()<=k-cnt) break;
            vis[p]=1,++cnt;
            for(auto i:s[p]) s[i].erase(p);
            s[p].clear();
        }
        if(cnt>k){puts("0");continue;}
        for(int i=1;i<=n;i++){
            for(auto j:s[i]){
                if(j<=i) continue;
                e.push_back(make_pair(i,j));
            }
        }
        if(e.size()>k*(k-cnt)){puts("0");continue;}
        dfs(n-cnt,cnt);
        printf("%lld\n",ans);
    }
    return 0;
}

```

---

