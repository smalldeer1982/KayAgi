# [JOISC 2023] Passport (Day1)

## 题目描述

护照是旅行家进入他国时使用的证件。

在一个星球上有 $N$ 个国家，从 $1$ 到 $N$ 编号。每个国家都签发一种护照。当旅行家获得由国家$i \ (1 \le i \le N)$ 签发的护照后，他能够进入国家 $L_i, L_{i + 1}, \dots, R_i$。**这里保证旅行家能够进入其签证的签发国。形式上地说, $L_i \le i \le R_i$ 必然成立。**

你有一个爱旅行的朋友。即使他奢望能环游世界，但他最初一种护照也没有。因此，他想通过一下重复以下两项行为来环游这 $N$ 个国家。

- 获得他当前所在国家签发的护照。
- 用他现有的护照进入某个国家。

知道他的计划后，你想知道这个计划的是否可行，和如果可行的话，他最少需要的护照数量。因为你并不清楚他现在身处何国，所以你预测了 $Q$ 个他可能正居住在那的国家 $X_1, X_2, \dots, X_Q$。

现在给定各国护照的信息 $L_i, R_i$ 和他可能居住的 $Q$ 个国家，您需要写一个程序，对于每一个可能居住的国家，判断他是否可能环游这 $N$ 个国家，如果可能的话，计算出他需要的最少护照种数。

## 说明/提示

**【样例解释 #1】**

假设你的朋友居住在国家 $X_1 = 1$，一种可行的方式如下，最后他获得了 $2$ 种护照：

1. 获得国家 $1$ 签发的护照。
2. 用国家 $1$ 签发的护照去国家 $2$ 旅行。
3. 获得国家 $2$ 签发的护照。
4. 用国家 $1$ 签发的护照去国家 $3$ 旅行。
5. 用国家 $2$ 签发的护照去国家 $4$ 旅行。

可以证明不存在使用护照种数更小的方案，故输出 $2$。

该样例满足所有子任务的限制。

**【样例解释 #2】**

假设你的朋友居住在国家 $X_1 = 3$。一种可行的方式如下，最后他获得了 $4$ 种护照：

1. 获得国家 $3$ 签发的护照。
2. 用国家 $3$ 签发的护照去国家 $2$ 旅行。
3. 获得国家 $2$ 签发的护照。
4. 用国家 $2$ 签发的护照去国家 $4$ 旅行。
5. 获得国家 $4$ 签发的护照。
6. 用国家 $4$ 签发的护照去国家 $5$ 旅行。
7. 获得国家 $5$ 签发的护照。
8. 用国家 $5$ 签发的护照去国家 $1$ 旅行。

可以证明不存在使用护照种数更小的方案，故输出 $4$。

该样例满足子任务 $2 \sim 5$ 的限制。

**【样例解释 #3】**

例如，如果你的朋友居住在 $X_3 = 3$，一种可行的方案书获得国家 $3$ 签发的护照，并用它来依次去国家 $1, 2, 4, 5$ 旅行。故第三行输出 $3$。

但如果你的朋友居住在国家 $X_5 = 5$，即使他获得了国家 $5$ 签发的护照，他也不可能进入任何其他国家，因此，他无法实现自己的旅行计划。故第五行输出 $-1$。

该样例满足子任务 $4 \sim 5$ 的限制。

**【样例解释 #4】**

该样例满足子任务 $4 \sim 5$ 的限制。

## 样例 #1

### 输入

```
4
1 3
2 4
2 3
4 4
1
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
1 5
2 4
2 3
3 5
1 5
1
3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
5
1 1
2 3
1 5
3 4
5 5
5
1
2
3
4
5
```

### 输出

```
-1
2
1
2
-1
```

## 样例 #4

### 输入

```
4
1 2
1 2
3 4
3 4
4
1
2
3
4
```

### 输出

```
-1
-1
-1
-1
```

# 题解

## 作者：Zpair (赞：2)

注意到可达的点一定构成一段区间，所以问题等价于同时走到 $1,n$ 的最小花费。

先建反图预处理出 $1$ 和 $n$ 到每个点的距离，记为 $dis1$ 和 $dis2$，这个线段树优化建图然后bfs一遍就行。

考虑钦定最后答案的护照获得顺序，对于当前的可达区间 $[l,r]$，我们要求在取 $[l,r]$ 之外的点后再也不能取 $[l,r]$ 中的点，容易发现这并不影响答案。

对于当前的 $[l,r]$，我们最多会在其中取两个点，否则一定会有点的区间被完全包含。

当取两个点 $x,y$ 时，不妨令 $L_x \le l,R_y \ge r$。则一定存在一组最优解满足 $x$ 走到 $1$，$y$ 走到 $n$。因为如果是从 $x$ 走到 $n$，则当前的 $y$ 可以放在以后选取，这样一定不劣，于是此时答案为 $\min(dis1_x+dis2_y+2)$。

进一步的，我们不需要枚举选取的两个点 $x,y$，上面的式子等价于当前区间到 $1,n$ 的距离和。

当取一个点 $x$ 时，不妨令：$L_x \le l$，另一边的情况类似。

我们断定，将当前可达区间改为 $[L_x,R_x]$ 不影响答案。

当 $R_x \ge r$ 时显然成立。 

当 $R_x < r$ 时，被错误标记为不可达的区间为 $[R_x+1,r]$，根据我们的钦定顺序，这段区间不会影响后面的选取。

当 $r=n$ 时，当前区间的答案可以被取两个点统计到，否则后续的选取一定会有一段覆盖到 $n$ 的区间，则 $[R_x+1,r]$ 的区间被标记为不可达也不会影响答案。

于是可以发现上面的可达区间只有每个点的对应区间，设：$f_p$ 表示从 $[L_p,R_p]$ 开始同时到 $1,n$ 的最小花费，则有：$f_p=\min(dis1_p+dis2_p,\min_{p \rightarrow t}(f_t+1))$。

按照最短路的更新方式 bfs 一遍即可。

双倍经验：[[USACO21DEC] Tickets P](https://www.luogu.com.cn/problem/P7984)。

---

## 作者：Elma_ (赞：1)

关键的性质是，由于每次拓展的是包含 $i$ 的一个区间，因此任意时刻，能到达的点集都是一个区间。因此能够到达所有国家，等价于能够到达 $1$ 和 $n$ 这两个国家。

不过这好像也没有想象中那么好做，不妨再考虑一个弱化：如果只要求能到达 $1$ 怎么做。这很容易，建反图从 $1$ 开始做 01-BFS，连边用线段树优化一下就行了。只要求能到达 $n$ 也是类似的。

我们发现，要求某个点能够同时到达 $1$ 和 $n$，分别考虑它到 $1$ 和 $n$ 的最短路径，这两条路径会有一些重合的部分，把这部分缩起来就是答案了。具体来说，是先走一段共同的部分到达某个中继点 $x$，然后从 $x$ 开始分道扬镳去 $1$ 和 $n$。于是做法就呼之欲出了：先对每个点求出若以这个点为中继点，但不要求之后的路径没有重合，后续部分的最小代价。然后再跑一次 01-BFS 更新掉路径重合的那部分即可。

总时间复杂度 $\mathcal{O}(n \log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> pi;
constexpr int N = 2e5 + 5;
int n, q, L[N], R[N];
vector <pi> e[N << 2]; int id[N << 2], tot, a[N << 2], b[N << 2], d[N << 2];
#define m ((l + r) >> 1)
void build(int x, int l, int r) {
	id[x] = ++tot;
	if (l == r) return e[l].emplace_back(id[x], 0), void();
	build(x << 1, l, m), build(x << 1 | 1, m + 1, r);
	e[id[x << 1]].emplace_back(id[x], 0);
	e[id[x << 1 | 1]].emplace_back(id[x], 0);
}
void add(int x, int l, int r, int ql, int qr, int v) {
	if (ql <= l && qr >= r) return e[id[x]].emplace_back(n + v, 0), void();
	if (ql <= m) add(x << 1, l, m, ql, qr, v);
	if (qr > m) add(x << 1 | 1, m + 1, r, ql, qr, v);
}
#undef m 
signed main() {
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	tot = 2 * n;
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		cin >> L[i] >> R[i];
		add(1, 1, n, L[i], R[i], i), e[n + i].emplace_back(i, 1);
	}
	for (int i = 1; i <= tot; i++) a[i] = 1e9;
	a[1] = 0;
	deque <int> que;
	que.push_front(1);
	while (!que.empty()) {
		int u = que.front(); que.pop_front();
		for (auto [v, w] : e[u]) {
			if (a[v] > a[u] + w) {
				a[v] = a[u] + w;
				if (w == 0) que.push_front(v);
				if (w == 1) que.push_back(v);
			}
		}
	}
	for (int i = 1; i <= tot; i++) b[i] = 1e9;
	b[n] = 0;
	que.push_front(n);
	while (!que.empty()) {
		int u = que.front(); que.pop_front();
		for (auto [v, w] : e[u]) {
			if (b[v] > b[u] + w) {
				b[v] = b[u] + w;
				if (w == 0) que.push_front(v);
				if (w == 1) que.push_back(v);
			}
		}
	}
	for (int i = 1; i <= tot; i++) d[i] = 1e9;
	for (int i = 1; i <= n; i++) d[i] = a[i] + b[i] - (1 < i && i < n);
	int seq[N];
	for (int i = 1; i <= n; i++) seq[i] = i;
	sort(seq + 1, seq + n + 1, [&](int i, int j) {
		return d[i] < d[j];
	});
	for (int i = 1; i <= n; i++) que.push_back(seq[i]);
	while (!que.empty()) {
		int u = que.front(); que.pop_front();
		for (auto [v, w] : e[u]) {
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				if (w == 0) que.push_front(v);
				if (w == 1) que.push_back(v);
			}
		}
	}
	cin >> q;
	while (q--) {
		int x; cin >> x;
		if (d[x] > n) cout << "-1\n";
		else cout << d[x] << "\n";
	}
   	return 0;
}
```

---

## 作者：lfxxx (赞：0)

注意到任何时候解锁的点（可以前往的国家）构成了一个区间。

所以要求能抵达所有点等价于能抵达点 $1$ 与点 $n$。

假若只要求抵达点 $1$ 的答案，显然不会走重复的点，于是 $i$ 向 $[l_i,r_i]$ 连边后变为一个最短路问题。

要求抵达点 $1$ 与点 $n$ 的话，不难想到路径一定是先走共同的一段再分叉然后分别走向点 $1$ 与点 $n$，分叉之后的路径不交，因为如果有交则可以延后分叉点减小代价。

考虑建立反图，求解每个点到点 $1$ 与点 $n$ 的最短路，然后再枚举分叉点，一个点作为分叉点时从这个点往后的路径代价就是这个点到点 $1$ 与到点 $n$ 的距离之和，求解每个点真正的答案考虑将每个点作为分叉点的代价作为这个点的权值，在反图上再跑一遍多源最短路即可。

时间复杂度 $O(n \log^2 n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 2e5+114;
int id[maxn];
vector< pair<int,int> > E[maxn<<2];
void build(int cur,int lt,int rt){
	if(lt==rt){
		id[lt]=cur;
		return ;
	}
	int mid=(lt+rt)>>1;
	build(cur<<1,lt,mid);
	build(cur<<1|1,mid+1,rt);
	E[cur<<1].push_back(make_pair(cur,0));
	E[cur<<1|1].push_back(make_pair(cur,0));	
}
int dis[maxn<<2],sum[maxn<<2],vis[maxn<<2];
void link(int cur,int lt,int rt,int l,int r,int c){
	if(rt<l||r<lt) return ;
	if(l<=lt&&rt<=r){
		E[cur].push_back(make_pair(c,1));
		return ;
	}
	int mid=(lt+rt)>>1;
	link(cur<<1,lt,mid,l,r,c);
	link(cur<<1|1,mid+1,rt,l,r,c);
}
const int inf = 1e8;
int n;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		link(1,1,n,l,r,id[i]);
	}
	for(int i=0;i<(maxn<<2);i++) dis[i]=inf;
	dis[id[1]]=0;
	deque<int> q;
	q.push_front(id[1]);
	while(q.size()>0){
		int u=q.front();
		q.pop_front();
		if(vis[u]==1) continue;
		vis[u]=1;
		for(pair<int,int> nxt:E[u]){
			int v=nxt.first,w=nxt.second;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(w==0) q.push_front(v);
				else q.push_back(v);
			}
		}
	}
	dis[id[1]]=1;
	for(int i=1;i<=n;i++) sum[id[i]]=dis[id[i]];
	for(int i=0;i<(maxn<<2);i++) dis[i]=inf;
	memset(vis,0,sizeof(vis));
	dis[id[n]]=0;
	q.push_front(id[n]);
	while(q.size()>0){
		int u=q.front();
		q.pop_front();
		if(vis[u]==1) continue;
		vis[u]=1;
		for(pair<int,int> nxt:E[u]){
			int v=nxt.first,w=nxt.second;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(w==0) q.push_front(v);
				else q.push_back(v);
			}
		}
	}
	dis[id[n]]=1;
	for(int i=1;i<=n;i++){
		sum[id[i]]=min(inf,sum[id[i]]+dis[id[i]]-1);
	}
	for(int i=0;i<(maxn<<2);i++) dis[i]=inf;
	for(int i=1;i<=n;i++) dis[id[i]]=sum[id[i]];
	memset(vis,0,sizeof(vis));
	priority_queue< pair<int,int> > Q;
	for(int i=1;i<=n;i++) Q.push(make_pair(-dis[id[i]],id[i]));
	while(Q.size()>0){
		int u=Q.top().second;
		Q.pop();
		if(vis[u]==1) continue;
		vis[u]=1;
		for(pair<int,int> nxt:E[u]){
			int v=nxt.first,w=nxt.second;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				Q.push(make_pair(-dis[v],v));
			}
		}
	}
	int m;
	cin>>m;
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		cout<<(dis[id[x]]<inf?dis[id[x]]:-1)<<'\n';
	}
	return 0;
}
```

---

## 作者：lyreqwq (赞：0)

考虑 $X = 1$ 怎么做：设 $p_0 = n$，每次找最左的能到达 $p_{i - 1}$ 的点 $p_i$，直到 $p_i = 1$。

这启发我们从 $n$ 开始向左扩展，计算从每个点出发到 $n$ 的距离。从 $1$ 开始向右扩展同理。

具体地，对于 $x \in [L_i, R_i]$，可以用 $dis_x + 1$ 来更新 $dis_i$，同时建出 bfs 树。

现在我们有两棵 bfs 树，它们之间可能会有影响。

假设我们要先从 $X$ 到达 $n$，经过从 $X$ 到 $n$ 的反祖链上的点。简单推一下可以发现，在中途选一个不在反祖链上的点，一定不会优于先走到 $n$ 再选不在反祖链上的点。另一侧也同理。

于是只需要分别考虑先走到 $n$ 和先走到 $1$ 的两种情况。先走到其中一个端点，然后查询前缀 / 后缀向另一侧走的 $dis$ 最小值。

若 bfs 树有多种形态，要选择能向另一侧扩展的最远的。把 $dis$ 记成 pair 即可解决这个问题。

实现上，不需要树套树 / 序列分块，直接线段树优化建反图，然后 01bfs 就行了。

注意若 pair 的第一维相同，更新第二维时只能 push_back。因为后面可能有一个更优的值把 push_front 的复杂度卡爆。

```cpp
# include <bits/stdc++.h>

using namespace std;

namespace lyre {
  constexpr int nmax = 200'100;
  constexpr int inf = INT_MAX / 4;
  using pair = std::pair<int, int>;
  int n, q, index;
  int X[nmax], ans[nmax];
  struct interval {
    int l, r;
    constexpr interval() : l(inf), r(-inf) {}
    constexpr interval(int l, int r) : l(l), r(r) {}
  } v[2 * nmax];
  vector<pair> G[2 * nmax];
  pair f[2][2 * nmax];
  pair g[2][2 * nmax];
  bool vis[2 * nmax];
  int suff[nmax], preg[nmax];
  namespace seg {
    int tr[4 * nmax];
    void build(int u, int l, int r) {
      if (l == r) {
        tr[u] = l;
        return;
      }
      tr[u] = ++index;
      auto mid = (l + r) / 2;
      build(u << 1, l, mid);
      build(u << 1 | 1, mid + 1, r);
      G[tr[u << 1]].emplace_back(tr[u], 0);
      G[tr[u << 1 | 1]].emplace_back(tr[u], 0);
    }
    void ins(int u, int l, int r, int x, int y, int v) {
      if (l == x && r == y) {
        G[tr[u]].emplace_back(v, 1);
        return;
      }
      auto mid = (l + r) / 2;
      if (y <= mid) {
        ins(u << 1, l, mid, x, y, v);
      } else if (x > mid) {
        ins(u << 1 | 1, mid + 1, r, x, y, v);
      } else {
        ins(u << 1, l, mid, x, mid, v);
        ins(u << 1 | 1, mid + 1, r, mid + 1, y, v);
      }
    }
  }
  int solveR(pair (&g)[2 * nmax], int x) {
    if (g[x].second >= inf) return inf;
    return suff[g[x].second] + g[x].first;
  }
  int solveL(pair (&f)[2 * nmax], int x) {
    if (f[x].second <= 0) return inf;
    return preg[f[x].second] + f[x].first;
  }
  void calcL(pair (&f)[2 * nmax], pair s) {
    fill(f + 1, f + index + 1, pair(inf, 0));
    deque<int> q;
    f[1] = s;
    q.push_back(1), vis[1] = true;
    while (!q.empty()) {
      auto x = q.front();
      q.pop_front(), vis[x] = false;
      for (auto [y, w] : G[x]) {
        if (f[y].first > f[x].first + w) {
          f[y].first = f[x].first + w;
          f[y].second = max(f[x].second, v[y].r);
          if (!vis[y] && w) q.push_back(y), vis[y] = true;
          else if (!vis[y]) q.push_front(y), vis[y] = true;
        } else if (f[y].first == f[x].first + w) {
          if (f[y].second < max(f[x].second, v[y].r)) {
            f[y].second = max(f[x].second, v[y].r);
            if (!vis[y]) q.push_back(y), vis[y] = true;
          }
        }
      }
    }
  }
  void calcR(pair (&g)[2 * nmax], pair s) {
    fill(g + 1, g + index + 1, pair(inf, inf));
    deque<int> q;
    g[n] = s;
    q.push_back(n), vis[n] = true;
    while (!q.empty()) {
      auto x = q.front();
      q.pop_front(), vis[x] = false;
      for (auto [y, w] : G[x]) {
        if (g[y].first > g[x].first + w) {
          g[y].first = g[x].first + w;
          g[y].second = min(g[x].second, v[y].l);
          if (!vis[y] && w) q.push_back(y), vis[y] = true;
          else if (!vis[y]) q.push_front(y), vis[y] = true;
        } else if (g[y].first == g[x].first + w) {
          if (g[y].second > min(g[x].second, v[y].l)) {
            g[y].second = min(g[x].second, v[y].l);
            if (!vis[y]) q.push_back(y), vis[y] = true;
          }
        }
      }
    } 
  }
  void check(int x, int y) {
    suff[n] = f[x][n].first;
    for (int i = n - 1; i >= 1; --i)
      suff[i] = min(suff[i + 1], f[x][i].first);
    preg[1] = g[y][1].first;
    for (int i = 2; i <= n; ++i)
      preg[i] = min(preg[i - 1], g[y][i].first);
    for (int i = 1; i <= q; ++i) {
      ans[i] = min(ans[i], solveL(f[x], X[i]));
      ans[i] = min(ans[i], solveR(g[y], X[i]));
    }
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n, index = n;
    seg::build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
      cin >> v[i].l >> v[i].r;
      seg::ins(1, 1, n, v[i].l, v[i].r, i);
    }
    cin >> q;
    for (int i = 1; i <= q; ++i)
      cin >> X[i];
    fill(ans + 1, ans + n + 1, inf);
    calcL(f[0], pair(0, 0)), calcL(f[1], pair(1, v[1].r));
    calcR(g[0], pair(0, inf)), calcR(g[1], pair(1, v[n].l));
    check(0, 0), check(0, 1), check(1, 0), check(1, 1);
    for (int i = 1; i <= q; ++i)
      cout << (ans[i] < inf ? ans[i] : -1) << '\n';
  }
}

int main() { lyre::main(); }
```

---

## 作者：_maze (赞：0)

> 在第 $i$ 个点买一张票，就能在 $[L_i,R_i]$ 中任意行走，求从每个点出发，最少买几张票能走遍 $[1,n]$？

tag：最短路，线段树优化建图。

题目的问题是求最少代价，于是我们发现题目很像一个最短路模型：$i$ 向一个虚点 $u_i$ 连边权为 $1$ 的边，$u_i$ 向 $[L_i,R_i]$ 连代价为 $0$ 的边。连边看起来很多，但是由于连边连向的是一个区间，我们只需要线段树优化建图即可。

考虑最终的答案是什么：由于连边是连向一个区间，所以对于点 $i$，所有买的票的并，也就是我们能走到的点，构成了一个大区间。所以走遍 $[1,i]$ 的充要条件是走到 $1$。因为 $1$ 为该区间左端点。同理走遍 $[i,n]$ 的充要条件是走到 $n$，因为 $n$ 为该区间右端点。所以我们建反图并从 $1$ 与 $n$ 分别跑最短路，每一个点的答案应该是到 $1$ 的最短路加上到 $n$ 的最短路。

然后我们发现这个不对，因为到 $1$ 的最短路和到 $n$ 的最短路会有重复的路径，这一段路径只会被计算一次。例如，从点 $i$ 出发只需要买一张 $i$ 的票就可以了。

我们如果设初始 $dis_1+dis_n$ 为初始答案 $ans_u$，那么我们发现对于任意的 $(u,v,w)$，$ans_v \le ans_u + w$。于是我们考虑再次使用最短路，只不过这一次往优先队列中加入所有点作为源点进行松弛。

>如果对算法进行思考，我们会发现只需要将所有票的虚点作为源点即可。原因如下：
>1. 对于线段树上的点，它们只负责联通原始图中有边的点，从其出发的边权值都为 $0$，因此不用松弛。
>2. 对于原有点，我们建的反图中必定有票的虚点连向原有点的边，因此只要不是无解情况，原有点必定会被松弛到。


```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 5;

int n;
struct node {
  int u, w;
  bool operator <(const node &b) const {
    return b.w < w;
  }
};
vector<pair<int, int>> e[N << 2];
int dis[N << 2], mx[N << 2], vis[N << 2], mxn;
const int INF = 1919810;
void dij(int s) {
  for (int i = 1; i <= mxn; ++i) dis[i] = INF;
  for (int i = 1; i <= mxn; ++i) vis[i] = 0;
  priority_queue<node> q;q.push({s, 0});
  while (!q.empty()) {
    auto t = q.top();q.pop();
    int u = t.u, val = t.w;
    if (vis[u] == 1) continue;
    vis[u] = 1, dis[u] = val;
    int v, w;
    for (auto p : e[u]) {
      tie(v, w) = p;
      q.push({v, val + w});
    }
  }
  for (int i = 1; i <= mxn; ++i) {
    if (dis[i] < INF) mx[i] = mx[i] + dis[i];
    else mx[i] = INF;
  }
}
void reans() {
  priority_queue<node> q;
  for (int i = n + 1; i <= 2 * n; ++i) if (mx[i] < INF) q.push({i, mx[i]});
  for (int i = 1; i <= mxn; ++i) vis[i] = 0;
  while (!q.empty()) {
    auto t = q.top();q.pop();
    int u = t.u, val = t.w;
    if (vis[u] == 1) continue;
    vis[u] = 1, mx[u] = val;
    int v, w;
    for (auto p : e[u]) {
      tie(v, w) = p;
      q.push({v, val + w});
    }
  }
}

void add(int u, int v, int w) {
  e[v].push_back(make_pair(u, w));
}
#define ls(u) (u<<1)
#define rs(u) ((u<<1)|1)
#define mid ((l+r)>>1)
void build(int u, int l, int r) {
  if (l == r) {
    mxn = max(mxn, u + (2 * n));
    return add(u + (2 * n), l, 0);
  }
  add(u + (2 * n), ls(u) + (2 * n), 0);
  add(u + (2 * n), rs(u) + (2 * n), 0);
  build(ls(u), l, mid);
  build(rs(u), mid + 1, r);
}
void modify(int u, int l, int r, int fl, int fr, int p) {
  if (fl <= l && r <= fr) return add(p, u + (2 * n), 0);
  if (mid >= fl) modify(ls(u), l, mid, fl, fr, p);
  if (mid < fr) modify(rs(u), mid + 1, r, fl, fr, p);
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  build(1, 1, n);
  for (int i = 1, l, r; i <= n; ++i) {
    cin >> l >> r;
    add(i, i + n, 1);
    modify(1, 1, n, l, r, i + n);
  }
  dij(1);
  dij(n);
  reans();
  int q;cin >> q;
  for (int i = 1, x; i <= q; ++i) {
    cin >> x;
    if (mx[x] < INF) cout << mx[x] << endl;
    else cout << -1 << endl;    
  } 

  return 0;
}
```


---

## 作者：Raisetsu41 (赞：0)

直观感受往往能带来较强的性质，注意到每一次的操作是将包含当前点的一个集合扩大，于是出发点能够到达的位置都是连续的，改写所求问题，求到达所有点改为，到达 $1$ 和 $n$ 两个点。  
发现这个不能拆开做，原因显而易见，继续直观感受，最优方案长成啥样呢，首先走到达到某个区间 $[l, r]$ 之前这两条路都是相同的，之后分开求解。  
更好地转化一下，从 $1, n$ 出发往中间走到某个区间 $[l, r]$ 合到了一起。  
所以现在的解法为，首先分别从 $1, n$ 出发做最短路，求到达某个相同的点时的步数，分别记为 $dis_{1}(i), dis_{n}(i)$，现在对于 $i$ 的答案上界为 $dis_{1}(i) + dis_{n}(i)$，问题在于怎么把前面部分的相同路径减去。  
或许这个东西就叫三角形不等式。  
注意到一件事情对于 $(u, v)$，总会有 $dis_v \le dis_u + 1$，所以如果发现了 $dis_v > dis_u + 1$，那就重新松弛，具体过程再用一次 `0/1 bfs` 实现。  

[submission](https://loj.ac/s/1899312)

---

