# [ABC406F] Compare Tree Weights

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc406/tasks/abc406_f

给定一个有 $N$ 个顶点的树 $T$，顶点和边分别编号为顶点 $1$, 顶点 $2$, $\ldots$, 顶点 $N$ 和边 $1$, 边 $2$, $\ldots$, 边 $(N-1)$。

特别地，边 $i$ $(1 \leq i \leq N-1)$ 连接顶点 $U_i$ 和顶点 $V_i$。

此外，每个顶点都有一个权重，最初，所有顶点的权重都为 $1$。

给定 $Q$ 个查询，请按顺序处理它们。每个查询是以下两种类型之一：

- `1 x w`：将顶点 $x$ 的权重增加 $w$。
- `2 y`：如果删除边 $y$，$T$ 将分裂成两个子树（连通分量）。将每个子树中包含的顶点的权重总和作为该子树的权重时，输出两个子树权重的差。

关于第二种类型的查询，可以证明，从 $T$ 中选择任意一条边并删除它时，$T$ 总是会分裂成两个子树。

另外，请注意，第二种类型的查询实际上并没有删除边。

## 说明/提示

**「数据范围」**

- $2 \leq N \leq 3 \times 10^5$
- $1 \leq U_i, V_i \leq N$
- $1 \leq Q \leq 3 \times 10^5$
- $1 \leq x \leq N$
- $1 \leq w \leq 1000$
- $1 \leq y \leq N-1$
- 输入均为整数
- 给定的图是一棵树。
- 至少存在一个第二种类型的查询。

**「样例 1 解释」**

树 $T$ 的结构和顶点编号对应如下图左所示。最初，所有顶点的权重都为 $1$。

对于第 $1$ 个查询，考虑删除边 $1$。此时，树会分裂成包含顶点 $1$ 的子树和包含顶点 $2$ 的子树。包含顶点 $1$ 的子树的权重为 $2$，包含顶点 $2$ 的子树的权重为 $4$，因此输出它们的差 $2$。（下图右）

![](https://img.atcoder.jp/abc406/6f17e951940c2460b3ae5fe8e6bddc52.png)

对于第 $2$ 个查询，将顶点 $1$ 的权重增加 $3$。

对于第 $3$ 个查询，考虑删除边 $1$。包含顶点 $1$ 的子树的权重为 $5$，包含顶点 $2$ 的子树的权重为 $4$，因此输出它们的差 $1$。（下图左）

对于第 $4$ 个查询，将顶点 $4$ 的权重增加 $10$。

对于第 $5$ 个查询，考虑删除边 $5$。此时，树会分裂成包含顶点 $4$ 的子树和仅包含顶点 $6$ 的子树。包含顶点 $4$ 的子树的权重为 $18$，仅包含顶点 $6$ 的子树的权重为 $1$，因此输出它们的差 $17$。（下图右）

![](https://img.atcoder.jp/abc406/c5eacf2967bcc2b09866a0d8b83104c4.png)

因此，按顺序换行输出第二种类型查询的答案 $2, 1, 17$。

## 样例 #1

### 输入

```
6
1 2
1 3
2 4
4 5
4 6
5
2 1
1 1 3
2 1
1 4 10
2 5```

### 输出

```
2
1
17```

# 题解

## 作者：fkxr (赞：7)

## 题意
给你一棵树，有点权。有 $m$ 个操作，每个是增加一个点的点权或求一颗子树与其他节点点权和的差的绝对值。
## 思路
一颗子树外点权和相当于总点权减去这颗子树点权和。

问题就转换为增加一个点的点权或求一颗子树的点权和。

然后就和[这题](https://www.luogu.com.cn/problem/P7746)几乎一模一样（~~这么爱出原题~~）。

因为是查询子树和考虑 dfs 序，在同一个子树内的 dfs 序是连续的。

树上问题就被转换为了序列问题，每个操作是单点或和区间求和。

然后随便用一点数据结构维护就行了，像树状数组、线段树、分块（可能有点悬）。
## Code
```cpp
//Do not hack it
// @author       fkxr(luogu uid=995934)
#include <bits/stdc++.h>
#define endl cerr<<"------------------I Love Sqrt Decomposition------------------\n";
#define int long long
#define _4x _4x
#define BIT BIT
//#define ST ST
//#define dsu dsu
using namespace std;
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc getchar
#define pc putchar
#endif

#define ds(x) (x=='\r'||x=='\n'||x==' ')
#define MAX 20
namespace fastIO {
	template<typename T>inline void r(T& a) { a = 0; char ch = gc(); bool ok = 0; for (; ch < '0' || ch>'9';)ok ^= (ch == '-'), ch = gc(); for (; ch >= '0' && ch <= '9';)a = (a << 1) + (a << 3) + (ch ^ 48), ch = gc(); if (ok)a = -a; }
	template<typename T>inline void w(T a) { if (a == 0) { pc('0'); return; }static char ch[MAX]; int till = 0; if (a < 0) { pc('-'); for (; a;)ch[till++] = -(a % 10), a /= 10; } else for (; a;)ch[till++] = a % 10, a /= 10; for (; till;)pc(ch[--till] ^ 48); }
	struct Srr {
		inline Srr operator>>(int& a) { r(a); return{}; }
		inline Srr operator>>(char& ch) { ch = gc(); for (; ds(ch);)ch = gc(); return{}; }
		inline Srr operator>>(string& s) { s = ""; char ch = gc(); for (; ds(ch);)ch = gc(); for (; !(ds(ch) || ch == EOF);) { s.push_back(ch); ch = gc(); }return{}; }
		template<typename T>inline Srr operator<<(T& a) { r(a); return{}; }
		inline void is(int n, string& s) { s = ""; char ch = gc(); for (; ds(ch);)ch = gc(); for (; n--;) { s.push_back(ch); ch = gc(); } }
	}in;
	struct Sww {
		inline Sww operator<<(const int a) { w(a); return{}; }
		inline Sww operator<<(const char ch) { pc(ch); return{}; }
		inline Sww operator<<(const string s) { for (int i = 0; i < s.size(); i++)pc(s[i]); return{}; }
		template<typename T>inline Sww operator>>(const T a) { w(a); return{}; }
	}out;
}using fastIO::in; using fastIO::out;
#undef ds
#define eout cerr

namespace Maths {
	const bool __is_P[] = { 0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1 };
	inline bool IP1(const int a) { if (a <= 29)return __is_P[a]; if (a % 2 == 0 || a % 3 == 0 || a % 5 == 0)return 0; for (int i = 6;; i += 6) { if (((i + 1) * (i + 1)) > a)return 1; if (a % (i + 1) == 0)return 0; if (((i + 5) * (i + 5)) > a)return 1; if (a % (i + 5) == 0)return 0; } }
#define times(a,b,m) (c=(unsigned long long)a*b-(unsigned long long)((long double)a/m*b+0.5L)*m,c<m?c:m+c)
	inline int power(int a, int b, const int mod = -1) { unsigned long long c; int ans = 1; if (mod == -1) { for (; b;) { if (b & 1)ans *= a; b >>= 1; a *= a; }return ans; }for (; b;) { if (b & 1)ans = times(ans, a, mod); b >>= 1; a = times(a, a, mod); }return ans; }
	const int Suk[] = { 2,325,9375,28178,450775,9780504,1795265022 };
	inline bool chk(const int n, int a, int b, int x) { if (x >= n) return 1; unsigned long long c; int v = power(x, a, n); if (v == 1)return 1; int j = 1; while (j <= b) { if (v == n - 1)break; v = times(v, v, n); j++; }if (j > b)return 0; return 1; }
	inline bool IP(int n) { if (n < 3 || n % 2 == 0)return n == 2; if (n <= 1e6) { return IP1(n); } else { int a = n - 1, b = 0; while (a % 2 == 0)a >>= 1, b++; for (int k : Suk)if (!chk(n, a, b, k))return 0; return 1; } }
#undef times
} using Maths::power;
using Maths::IP;
namespace exs {
#ifdef _4x
	int dx[] = { 1,-1,0,0 }, dy[] = { 0,0,1,-1 };
#else
	int dx[] = { 1,0,-1,-1,1,1,0,-1 }, dy[] = { 1,1,1,0,0,-1,-1,-1 };
#endif
	template<typename T, typename T1, typename T2>inline bool rg(T l, T1 r, T2 x) { return l <= x && x <= r; }
	inline bool emc(const int& a, const int& b) { return a > b; }

#ifdef BIT//BIT------------ 1x
#define maxn 300005
	struct bit {
		int c0[maxn], c1[maxn], n;
		inline void Add(int* c, int p, int v) { for (; p <= n; p += p & -p)c[p] += v; }inline int Sum(int* c, int p) { int t = 0; for (; p; p -= p & -p)t += c[p]; return t; }
		inline int sum(int l, int r) { return Sum(c0, r) * r - Sum(c1, r) - Sum(c0, l - 1) * (l - 1) + Sum(c1, l - 1); }
		inline void add(int l, int r, int v) { Add(c0, l, v); Add(c0, r + 1, -v); Add(c1, l, (l - 1) * v); Add(c1, r + 1, -r * v); }
		inline void init(int* c, int len) { int last = 0; for (int i = 1; i <= len; i++) { last = c[i] - last; Add(c0, i, last); Add(c1, i, last * (i - 1)); last = c[i]; } }
	};
#undef maxn
#endif//BIT end

#ifdef ST//ST------------- 1x
#define maxn 100005
#define bq max
	struct st {
		int lg[maxn], f[18][maxn];
		inline void init(int* c, int len) { for (int i = 2; i <= len; i++)lg[i] = lg[i >> 1] + 1; for (int i = 1; i <= len; i++)f[0][i] = c[i]; for (int j = 1; (1 << j) <= len; j++) { for (int i = 1; i + (1 << j) - 1 <= len; i++)f[j][i] = bq(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]); } }
		inline int q(int l, int r) { int j = lg[r - l + 1]; return bq(f[j][l], f[j][r - (1 << j) + 1]); }
	};
#undef maxn
#undef bq
#endif//ST end

#ifdef dsu//dsu-------------- 0x
	struct dsu {
		vector<int> fa, size; dsu(int size_) :fa(size_), size(size_, 1) { iota(fa.begin(), fa.end(), 0); }
		inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
		inline void unite(int x, int y) { x = find(x), y = find(y); if (x == y)return; if (size[x] < size[y])swap(x, y); fa[y] = x; size[x] += size[y]; }
	};
#endif//dsu end
}using namespace exs;

int dfn[300005], dep[300005], a[300005], siz[300005],Dfn[300005];
int tot;
vector<int>e[300005];
void dfs(int x, int fa) {
	dep[x] = dep[fa] + 1;
	siz[x] = 1;
	dfn[x] = ++tot;
	Dfn[tot] = x;
	for (auto i : e[x]) {
		if (i == fa)continue;
		dfs(i, x);
		siz[x] += siz[i];
	}
}
bit t;
int X[300005], Y[300005];
void Main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; i++)a[i] = 1;
	for (int i = 1; i < n; i++) {
		int x, y;
		in >> x >> y;
		X[i] = x, Y[i] = y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1, 0);
	int q;
	in >> q;
	int sum = n;
	t.n = n;
	t.init(a, n);
	for (; q--;) {
		int opt;
		in >> opt;
		if (opt == 1) {
			int x, w;
			in >> x >> w;
			sum += w;
			t.add(dfn[x], dfn[x], w);
		}
		else {
			int x;
			in >> x;
			x = max(dfn[X[x]], dfn[Y[x]]);
			int k = t.sum(x, x + siz[Dfn[x]] - 1);
			int ans = sum - k - k;
			if (ans < 0)ans *= -1;
			out << ans << '\n';
		}
	}
}

signed main() {
	Main();
	return 0;
}
```
[场切记录](https://atcoder.jp/contests/abc406/submissions/65892985)

---

## 作者：AnotherDream (赞：6)

# [AT_abc406_f](https://www.luogu.com.cn/problem/AT_abc406_f) 题解
## 题意简述

维护一棵树，初始点权都是 $1$，使它支持以下两种操作：

- 将一个点的点权加上 $x$。
- **临时**删掉一条边，将这棵树分成两部分，求出两棵树点权和之差。

## 思路
可以看出其中一棵树的点权和是整棵树上一棵子树的点权和，根为被删除的边上深度更大的那个。  
另一棵的权值和就是整棵树点权和减去上面求出的权值和。

整棵树的点权和是很好维护的。

因为要子树查询，所以要用 DFS 序将子树的编号连续起来，用树状数组或线段树维护点权。

总复杂度 $O(Q\log N)$，可以接受。
## 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define debug cerr<<"The code runs successfully.\n";
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
#define lowbit(x) (x&-x)
const int N = 3e5 + 10;
int n,q,tr[N],siz[N],id[N],dep[N],tmp,sum;
//siz是子树大小 id是dfs序 dep是点的深度 sum是点权和
vector<int> g[N];
int U[N],V[N];//存边
//树状数组部分
inline void add(int x,int y) {
	for(;x<=n;x+=lowbit(x)) {
		tr[x]+=y;
	}
}
inline int ask(int x) {
	int ret=0;
	for(;x;x-=lowbit(x)) {
		ret+=tr[x];
	}
	return ret;
}
//dfs序
inline void dfs(int fa,int u) {
	id[u]=++tmp;
	dep[u]=dep[fa]+1;
	siz[u]=1;
	add(tmp,1);
	for(int v:g[u]) {
		if(v==fa) continue;
		dfs(u,v);
		siz[u]+=siz[v];
	}
}
signed main() {
	fst;
	cin>>n;
	sum=n;//初始点权为1，总权值和就是n
	for(int i=1;i<n;i++) {
		cin>>U[i]>>V[i];
		g[U[i]].push_back(V[i]);
		g[V[i]].push_back(U[i]);
	}
	dfs(0,1);
	for(int i=1;i<n;i++) {
		if(dep[U[i]]<dep[V[i]]) {
			swap(U[i],V[i]);//让深度更大的点排在前面
		}
	}
	cin>>q;
	while(q--) {
		int op;
		cin>>op;
		if(op==1) {
			int x,y;
			cin>>x>>y;
			add(id[x],y);
			sum+=y;
		}
		else {
			int x;
			cin>>x;
			int sum1=ask(id[U[x]]+siz[U[x]]-1)-ask(id[U[x]]-1);
			int sum2=sum-sum1;
			cout<<abs(sum1-sum2)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Inzaghi_Luo (赞：2)

这个题目第一个操作就是单点加，第二个操作可以只查询一边的子树，另外一边用总数减去刚才查询出来的子树。单点加，子树查询，随便用数据结构维护一下就好，我写的是树状数组。具体实现就是先 DFS 一次树，记录下来 DFS 序和每个子树的大小，然后每个子树对应的区间就知道了，这个时候就可以直接用树状数组做了。

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN = 300005;
int head[MAXN], CNT;
struct edge{
	int next, to;
}ed[MAXN << 1];
void add_edge(int u, int v){
	ed[++CNT] = (edge){head[u], v};
	head[u] = CNT;
}
int u[MAXN], v[MAXN];
int dep[MAXN], dfn[MAXN], sz[MAXN], num;
void dfs(int u, int fa){
	sz[u] = 1;
	dep[u] = dep[fa] + 1;
	dfn[u] = ++num;
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}
long long ft[MAXN];
int n;
int lowbit(int x){
	return x & (-x);
}
void change(int x, int y){
	for(int i = x;i <= n;i += lowbit(i)){
		ft[i] += y;
	}
}
long long query(int x){
	long long ans = 0;
	for(int i = x;i;i -= lowbit(i)){
		ans += ft[i];
	}
	return ans;
}
int main(){
	scanf("%d", &n);
	for(int i = 1;i < n;i++){
		scanf("%d%d", &u[i], &v[i]);
		add_edge(u[i], v[i]);
		add_edge(v[i], u[i]);
	}
	dfs(1, 0);
	for(int i = 1;i < n;i++){
		if(dep[u[i]] > dep[v[i]]) swap(u[i], v[i]); 
	}
	for(int i = 1;i <= n;i++) change(i, 1);
	int q;
	scanf("%d", &q);
	long long sum = n;
	for(int i = 1, op, x, y;i <= q;i++){
		scanf("%d%d", &op, &x);
		if(op == 1){
			scanf("%d", &y);
			change(dfn[x], y);
			sum += y;
		}
		else{
			y = v[x];
			long long s1 = query(dfn[y] + sz[y] - 1) - query(dfn[y] - 1);
			printf("%lld\n", max(sum - s1 - s1, s1 + s1 - sum));
		}
	}
	return 0;
}
```

---

## 作者：haokee (赞：2)

对于第二个操作，我们需要将树分成两棵子树，并计算它们权值和的差值。当移除一条边时，较深的那个节点所在的子树为第一棵子树，第二棵子树的权值和则是总权值和减去第一棵子树的权值和。因此本题需要实现单点修改和子树求和两种操作。

如果操作的是一个序列而非树，单点修改和区间求和可以简单地用树状数组实现。但在树上进行这些操作时，单点修改容易实现，子树求和则较为复杂。因此我们需要将子树求和转化为区间求和。

这里我们可以使用 DFS 序的概念。DFS 序是指对树进行深度优先遍历时访问节点的顺序。一个重要的性质是：任何子树中所有节点的 DFS 序都是连续的，因为 DFS 在访问完当前节点后会立即访问其所有子节点，然后再回溯。利用这一性质，我们可以：

1. 单点修改时，直接修改对应节点 DFS 序位置的值；
2. 子树查询时，查询的是从该节点 DFS 序开始、长度为子树大小的连续区间和。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const LL kMaxN = 3e5 + 5;

LL dfn[kMaxN], t[kMaxN], d[kMaxN], u[kMaxN], v[kMaxN], siz[kMaxN], n, q, cnt;
vector<LL> e[kMaxN];

// 标记 dfs 序，子树大小和节点深度
void dfs(LL x, LL f) {
  d[x] = d[f] + 1;
  dfn[x] = ++cnt;
  siz[x] = 1;
  for (LL i : e[x]) {
    if (i != f) {
      dfs(i, x);
      siz[x] += siz[i];
    }
  }
}

// 单点修改
void modify(LL x, LL y) {
  for (; x <= n; x += x & -x) {
    t[x] += y;
  }
}

// 区间查询
LL query(LL x) {
  LL ans = 0;
  for (; x; x -= x & -x) {
    ans += t[x];
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (LL i = 1; i < n; i++) {
    cin >> u[i] >> v[i];
    e[u[i]].push_back(v[i]);
    e[v[i]].push_back(u[i]);
  }
  dfs(1, 0);
  for (LL i = 1; i <= n; i++) {
    modify(i, 1);
  }
  cin >> q;
  for (LL o, x, w; q; q--) {
    cin >> o >> x;
    if (o == 1) {
      cin >> w;
      modify(dfn[x], w);
    } else {
      LL p = d[u[x]] > d[v[x]] ? u[x] : v[x];  // 取深度大的点
      LL subtree_sum = query(dfn[p] + siz[p] - 1) - query(dfn[p] - 1);  // 第一棵子树
      LL other_sum = query(n) - subtree_sum;  // 第二棵子树
      cout << abs(subtree_sum - other_sum) << '\n';
    }
  }
  return 0;
}
```

虽然树上动态操作常见的解决方案是重链剖分配合线段树，但这种方法代码冗长且实现复杂。使用 DFS 序配合树状数组不仅代码简洁，而且实现更为直观，是一种很好的替代方案。

---

## 作者：dingxiongyue (赞：2)

# 题解：AT_abc406_f [ABC406F] Compare Tree Weights

## 思路：

~~考场上直接把树剖代码贴上去了（）。~~

* 操作 $1$：直接线段树里单点修改 $dfn_x$。
* 操作 $2$：记所有点权和为 $sum$，询问的边连接点 $u,v$，则 $dfn$ 较小的为父亲，不妨设点 $u$ 为父亲，线段树查询以 $v$ 为根的子树点权和，记为 $val$，答案即为 $|sum - 2 \times val|$。


## 代码：

[AC记录](https://atcoder.jp/contests/abc406/submissions/65907755)

不要在意代码中的树剖部分。

```cpp
#include <iostream>
#include <cstring>
#define int long long
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
#define x first
#define y second
typedef std::pair<int, int> PII;
const int N = 3e5 + 10;
int n, m, rt, mod;
int u, v;
int op, x, w;
int tim;
int sum;
int a[N];
int e[N << 1], ne[N << 1], h[N << 1], idx;
int fa[N], sz[N], wc[N], dep[N];
int dfn[N], rdfn[N], top[N];
PII edge[N];
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

namespace Tree {
	int tr[N << 2];
	int tag[N << 2];
	void pushup(int u) {
		tr[u] = tr[lc(u)] + tr[rc(u)];
	}
	void pushdown(int u, int _l, int _r) {
		if (tag[u]) {
			int mid = _l + _r >> 1;
			tr[lc(u)] = tr[lc(u)] + (mid - _l + 1) * tag[u];
			tr[rc(u)] = tr[rc(u)] + (_r - mid) * tag[u];
			tag[lc(u)] = tag[lc(u)] + tag[u];
			tag[rc(u)] = tag[rc(u)] + tag[u];
			tag[u] = 0;
		}
	}
	void build(int u = 1, int _l = 1, int _r = n) {
		if (_l == _r) {
			tr[u] = a[rdfn[_l]];
			return;
		}
		int mid = _l + _r >> 1;
		build(lc(u), _l, mid), build(rc(u), mid + 1, _r);
		pushup(u);
	}
	void modify(int l, int r, int x, int u = 1, int _l = 1, int _r = n) {
		if (_l >= l && _r <= r) {
			tr[u] = tr[u] + (_r - _l + 1) * x;
			tag[u] = tag[u] + x;
			return;
		}
		int mid = _l + _r >> 1;
		pushdown(u, _l, _r);
		if (l <= mid) modify(l, r, x, lc(u), _l, mid);
		if (r > mid) modify(l, r, x, rc(u), mid + 1, _r);
		pushup(u);
	}
	int query(int l, int r, int u = 1, int _l = 1, int _r = n) {
		if (_l >= l && _r <= r) 
			return tr[u];
		int mid = _l + _r >> 1, sum = 0;
		pushdown(u, _l, _r);
		if (l <= mid) sum += query(l, r, lc(u), _l, mid);
		if (r > mid) sum += query(l, r, rc(u), mid + 1, _r);
		return sum;
	}
}

void dfs1(int u, int f) {
	fa[u] = f, sz[u] = 1, dep[u] = dep[f] + 1;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == f) continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if (sz[v] > sz[wc[u]]) 
			wc[u] = v;
	}
}

void dfs2(int u, int _top) {
	dfn[u] = ++tim;
	rdfn[tim] = u;
	top[u] = _top;
	if (wc[u]) {
		dfs2(wc[u], _top);
		for (int i = h[u]; ~i; i = ne[i]) {
			int v = e[i];
			if (v == fa[u] || v == wc[u]) continue;
			dfs2(v, v);
		}
	}
}

void modify(int x, int y, int z) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		Tree::modify(dfn[top[x]], dfn[x], z);
		x = fa[top[x]];
	}
	Tree::modify(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y]), z);
}

int query(int x, int y) {
	int sum = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		sum = (sum + Tree::query(dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	} 
	return (sum + Tree::query(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y])));
}

signed main() {
	memset(h, -1, sizeof h);
	n = read();
	rt = 1;
	sum = n;
	for (int i = 1; i <= n; i++) 
		a[i] = 1;
	for (int i = 1; i < n; i++) {
		u = read(), v = read();
		edge[i] = {u, v};
		add(u, v), add(v, u);
	}
	dfs1(rt, 0);
	dfs2(rt, 0);
	Tree::build();
	m = read();
	while (m--) {
		op = read(), x = read();
		if (op == 1) {
			w = read();
			sum += w;
			Tree::modify(dfn[x], dfn[x], w);
		} else {
			if (dfn[edge[x].x] > dfn[edge[x].y]) std::swap(edge[x].x, edge[x].y);
			write(abs(sum - 2 * Tree::query(dfn[edge[x].y], dfn[edge[x].y] + sz[edge[x].y] - 1)));
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：aaron0919 (赞：2)

# [AT_abc406_f の题解](https://www.luogu.com.cn/problem/AT_abc406_f)

## 题目大意

单点加，询问将树断开后两部分权的差。

至于查询的东西就是以深度较大的点为根的子树的权值之和与剩下部分的差的绝对值。

可直接用 dfs 序加树状数组过掉。

解释一下，因为 dfs 是扫完一颗子树再扫下一颗子树，只要记录了子树大小，就能知道这个子树所对应的区间。

## code

赛时懒，用树链剖分模板过掉的。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

const int N = 1e6 + 10;
const int INF = 1e18;

int n, m, root, MOD;
int a[N], b[N], t[N << 2], tg[N << 2];
int siz[N], fat[N], top[N], dep[N], son[N], id[N];
vector<int> e[N];

#define mid (l + r) / 2
#define ls (u << 1)
#define rs (ls | 1)

void pushup(int u)
{
    t[u] = (t[ls] + t[rs]) % MOD;
}

void pushdown(int u, int l, int r)
{
    if (tg[u])
    {
        (t[ls] += (mid - l + 1) * tg[u]) %= MOD;
        (t[rs] += (r - mid) * tg[u]) %= MOD;
        (tg[ls] += tg[u]) %= MOD;
        (tg[rs] += tg[u]) %= MOD;
        tg[u] = 0;
    }
}

void build(int u, int l, int r)
{
    if (l == r)
    {
        t[u] = b[l] % MOD;
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int ql, int qr, int x)
{
    if (qr < l || r < ql)
    {
        return;
    }
    if (ql <= l && r <= qr)
    {
        (tg[u] += x) %= MOD;
        (t[u] += x * (r - l + 1) % MOD) %= MOD;
        return;
    }
    pushdown(u, l, r);
    update(ls, l, mid, ql, qr, x), update(rs, mid + 1, r, ql, qr, x);
    pushup(u);
}

int query(int u, int l, int r, int ql, int qr)
{
    if (qr < l || r < ql)
    {
        return 0;
    }
    if (ql <= l && r <= qr)
    {
        return t[u];
    }
    pushdown(u, l, r);
    return (query(ls, l, mid, ql, qr) + query(rs, mid + 1, r, ql, qr)) % MOD;
}

void dfs1(int u, int fath)
{
    siz[u] = 1;
    fat[u] = fath;
    dep[u] = dep[fath] + 1;
    for (int &v : e[u])
    {
        if (v == fath)
        {
            continue;
        }
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
        {
            son[u] = v;
        }
    }
}

int _cnt;
void dfs2(int u, int tp)
{
    b[id[u] = ++_cnt] = a[u];
    top[u] = tp;
    if (son[u])
    {
        dfs2(son[u], tp);
    }
    for (int &v : e[u])
    {
        if (v == fat[u] || v == son[u])
        {
            continue;
        }
        dfs2(v, v);
    }
}

void addpath(int u, int v, int x)
{
    x %= MOD;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
        {
            swap(u, v);
        }
        update(1, 1, n, id[top[u]], id[u], x);
        u = fat[top[u]];
    }
    if (dep[u] > dep[v])
    {
        swap(u, v);
    }
    update(1, 1, n, id[u], id[v], x);
}

void addtree(int u, int x)
{
    update(1, 1, n, id[u], id[u] + siz[u] - 1, x % MOD);
}

int querypath(int u, int v)
{
    int ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
        {
            swap(u, v);
        }
        (ans += query(1, 1, n, id[top[u]], id[u])) %= MOD;
        u = fat[top[u]];
    }
    if (dep[u] > dep[v])
    {
        swap(u, v);
    }
    (ans += query(1, 1, n, id[u], id[v])) %= MOD;
    return ans;
}

int querytree(int u)
{
    return query(1, 1, n, id[u], id[u] + siz[u] - 1);
}
array<int, 2> edge[N];
int all;
signed main()
{
    cin.tie(0)->sync_with_stdio(false), cout.setf(ios::fixed), cout.precision(10);

    cin >> n;
    root = 1, MOD = 1e18;
    for (int i = 1; i <= n; ++i)
    {
        a[i] = 1;
        ++all;
    }
    for (int i = 1, u, v; i < n; ++i)
    {
        cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
        edge[i] = {u, v};
    }
    dfs1(root, 0);
    dfs2(root, root);
    build(1, 1, n);
    cin >> m;
    while (m--)
    {
        int op, x, y;
        cin >> op;
        if (op == 1)
        {
            cin >> x >> y;
            addpath(x, x, y);
            all += y;
        }
        else
        {
            cin >> x;
            if (dep[edge[x][0]] < dep[edge[x][1]])
            {
                y = edge[x][1];
            }
            else
            {
                y = edge[x][0];
            }
            cout << abs(querytree(y) * 2 - all) << '\n';
        }
    }
    return 0;
}
```

---

## 作者：Vae_L (赞：1)

纯送的。

赛时注意到树链剖分可以维护，但时间不多了没敢写，写了树状数组的做法，93 分钟过的。

第一个询问应该是随便做的，转成欧拉序后直接单点加即可。

对于欧拉序不了解的同学可自行百度，当然 dfs 序应该也是能做的。

第二个询问，注意到其中一个节点一定是另一个的父亲，这也就意味着一定有一个节点的子树是完整的，我们求出这一个子树的和，将总和减去这课子树就是剩下部分的和了。

~~我才不会说我被 B 卡了 80 分钟，被 D 卡了 4 个点，被 C 翻译创飞，但最后过了 A、B、E、F 的。~~

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,op,tr[1000005],a[1000005],m,l[1000005],r[1000005],tim,fa[1000005],q;
vector<int>vec[1000005];
struct node{
	int a,b;
}edge[1000005];
int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int k)
{
	while(x<=n)
	{
		tr[x]+=k;
		x+=lowbit(x);
	}
} 
int solve(int x)
{
	int ans=0;
	while(x)
	{
		ans+=tr[x];
		x-=lowbit(x);	
	} 
	return ans;
}
void dfs(int x,int fat)
{
	l[x]=(++tim);
	fa[x]=fat;
	for(auto it:vec[x])
	{
		if(it==fat) continue;
		dfs(it,x);
	}
	r[x]=tim;
}
signed main() 
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
    	int u,v;
		cin>>u>>v;
		vec[u].push_back(v);
		vec[v].push_back(u);
		edge[i]={u,v};;
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) add(l[i],1);
	cin>>q;
	while(q--)
	{
		int op,x,y,w;
		cin>>op;
		if(op==1)
		{
			cin>>x>>w;
			add(l[x],w);
		}
		else
		{
			cin>>y;	
			int u=edge[y].a;
			int v=edge[y].b;
			if(fa[v]==u) swap(u,v);
			int sum=solve(r[u])-solve(l[u]-1);
			int sum1=solve(n);
			cout<<abs(sum1-sum*2)<<"\n";
		}
	}
    return 0;
}

---

## 作者：NTT__int128 (赞：1)

把 $1$ 提做根节点，求出每个节点 $x$ 的 $dfn_x,siz_x$。

用线段树的区间 $[l,r]$ 维护 $dfn$ 在 $[l,r]$ 中的权值之和。

令 $S_t$ 为 $t$ 子树内的权值和，由 dfs 序的性质，$S_t$ 即为线段树的区间 $[dfn_t,dfn_t+siz_t-1]$ 的权值和。

对于每次修改，直接在线段树位置 $dfn_x$ 上加 $w$ 即可。

对于每次查询：

设边 $y$ 连接的两点中深度大的为 $x$，则答案为 $S_1-2S_x$，直接求即可。

代码：[https://atcoder.jp/contests/abc406/submissions/65882783](https://atcoder.jp/contests/abc406/submissions/65882783)

---

## 作者：Nahida_Official (赞：1)

原题链接 [Link](https://atcoder.jp/contests/abc406/tasks/abc406_f)

## 题意：
给定一棵初始点权全部为 1 的树，有两种操作：

- 修改点权
- 统计以 $y$ 为边相连的两棵子树的权值和的差值（绝对值）

## 分析：
看到这操作应该都知道怎么写了，如果再加上子树修改和路径统计就更典了。

正常写树链剖分和线段树，正常写子树统计，这道题唯一需要动脑子的就是你要在加边的时候统计每条边连的是哪两个节点，并且在进行第二个操作的时候判断哪个点的深度更大，因为节点深度更大的子树必然是下子树，你要用下子树的权值和（因为你没有办法统计上子树的权值和）来进行处理。

每次更新整个子树和 $sum$，就是统计以 1 为根节点的子树和，然后拿 $sum$ 减掉两倍的下子树和，加个绝对值就行了。

没想到 F 题这么板，打比赛被 C 题硬控了。

## Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define Sangonomiya signed
#define Kokomi main()
#define Love return
#define Nahida 0
#define Forever ;
#define IOS cin.tie(nullptr)->sync_with_stdio(false)
#define cin std::cin
#define cout std::cout
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
const int N=1e6;
int dfn[N],son[N],top[N],fa[N],siz[N],rnk[N],dep[N];
int val[N<<2],lzy[N<<2],len[N<<2];
int head[N],cnt,num;
int a[N];
int n,q;
int bian[N],bian2[N];
struct node{
    int next,v;
};
node G[N];
void add(int u,int v){
    G[++cnt].next=head[u];
    G[cnt].v=v;
    head[u]=cnt;
}
void dfs1(int x,int y){
    siz[x]=1;
    son[x]=0;
    fa[x]=y;
    dep[x]=dep[y]+1;
    for(int i=head[x];i;i=G[i].next){
        int v=G[i].v;
        if(v==y) continue;
        dfs1(v,x);
        siz[x]+=siz[v];
        if(siz[v]>siz[son[x]]) son[x]=v;
    }
}
void dfs2(int x,int y){
    top[x]=y;
    dfn[x]=++num;
    rnk[num]=x;
    if(son[x]) dfs2(son[x],y);
    for(int i=head[x];i;i=G[i].next){
        int v=G[i].v;
        if(v==son[x]||v==fa[x]) continue;
        dfs2(v,v);
    }
}
void pushup(int x){
    val[x]=val[lc]+val[rc];
}
void upd(int x,int y){
    lzy[x]+=y;
    val[x]+=len[x]*y;
}
void pushdown(int x){
    if(lzy[x]){
        upd(lc,lzy[x]);
        upd(rc,lzy[x]);
        lzy[x]=0;
    }
}
void build(int x,int l,int r){
    len[x]=r-l+1;
    lzy[x]=0;
    if(l==r){
        val[x]=a[rnk[l]];
        return ;
    }
    build(lc,l,mid);
    build(rc,mid+1,r);
    pushup(x);
}
void update(int x,int l,int r,int ul,int ur,int k){
    if(l>=ul && r<=ur){
        upd(x,k);
        return ;
    }
    pushdown(x);
    if(ul<=mid) update(lc,l,mid,ul,ur,k);
    if(ur>mid) update(rc,mid+1,r,ul,ur,k);
    pushup(x);
}
int query(int x,int l,int r,int ql,int qr){
    int res=0;
    if(l>=ql && r<=qr){
        return val[x];
    }
    pushdown(x);
    if(ql<=mid) res+=query(lc,l,mid,ql,qr);
    if(qr>mid) res+=query(rc,mid+1,r,ql,qr);
    return res;
}
int Tree_query(int x){
    int res=0;
	res=query(1,1,n,dfn[x],dfn[x]+siz[x]-1);
	return res;
}
Sangonomiya Kokomi{
	IOS;
    cin>>n;
    for(int i=1;i<=n;i++) a[i]=1;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        bian[i]=v;
        bian2[i]=u;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    cin>>q;
    while(q--){
        int op,x,y,w;
        cin>>op;
        if(op==1){
            cin>>x>>w;
            update(1,1,n,dfn[x],dfn[x],w);
        }else{
            cin>>y;
            int sum=Tree_query(1);
            if(dep[bian[y]]>=dep[bian2[y]]){
                cout<<std::abs((sum-Tree_query(bian[y]))-Tree_query(bian[y]))<<'\n';
            }else{
                cout<<std::abs((sum-Tree_query(bian2[y]))-Tree_query(bian2[y]))<<'\n';
            }
            
        }
    }
	Love Nahida Forever;
}
```
upd on 5.20:修改了文章中的错字。

---

## 作者：zbzbzzb (赞：1)

看到单点修改和查询子树，其显然可以将子树转为一个区间后使用线段树维护。

考虑使用 DFS 序，其在一个子树中是连续的，因此可以直接在修改时修改 DFS 序而不用在树上修改。

然后查询也是查询 DFS 序所在的区间，从而得到子树的权重和。

然后就是线段树的模板，不难写。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long u,v;
}e[300010];
vector<int>g[300010];
long long n,m,u,v,s,op,tmp,tr,ret,x,xx,yy,k,dep[300010],l[300010],r[300010],a[300010],sum[2000010];
void dfs(int u,int fa){//DFS序
	dep[u]=dep[fa]+1;
	tmp++;
    l[u]=tmp;
    for(int i=0;i<(int)g[u].size();i++){
    	int v=g[u][i];
    	if(v!=fa){
	        dfs(v,u);
	    }
	}r[u]=tmp;
}void pushup(long long rt){//线段树板子
	sum[rt]=sum[rt*2]+sum[rt*2+1];
}void build(long long rt,long long l,long long r){
	if(l==r){
		sum[rt]=1;
		return;
	}long long mid=(l+r)/2;
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
	pushup(rt);
}void updata(long long rt,long long l,long long r){
	if(x<l||x>r){
		return;
	}if(l>=x&&r<=x){
		sum[rt]+=k;
		return;
	}long long mid=(l+r)/2;
	updata(rt*2,l,mid);
	updata(rt*2+1,mid+1,r);
	pushup(rt);
}long long query(long long rt,long long l,long long r){
	if(yy<l||xx>r){
		return 0;
	}if(xx<=l&&yy>=r){
		return sum[rt];
	}long long mid=(l+r)/2;
	return (query(rt*2,l,mid)+query(rt*2+1,mid+1,r));
}int main(){
	scanf("%lld",&n);
	s=n;//最开始的总权值和显然为点数
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
		e[i]=(node){u,v};
	}dfs(1,1);
	build(1,1,n);
	scanf("%lld",&m);
	while(m --> 0){
		scanf("%lld",&op);
		if(op==1){
			scanf("%lld%lld",&x,&k);
			s+=k,x=l[x];//修改总和
			updata(1,1,n);
		}else if(op==2){
			scanf("%lld",&x);
			if(dep[e[x].u]>=dep[e[x].v]){
				tr=e[x].u;
			}else{
				tr=e[x].v;
			}xx=l[tr],yy=r[tr];//DFS序转为区间
			ret=s-2*query(1,1,n);
			if(ret<0){
				ret=-ret;
			}printf("%lld\n",ret);
		}
	}return 0;
}
```

---

## 作者：Yesod (赞：1)

因为 $ 2 $ 操作不会真的断开子树，所以发现 $ 2 $ 操作的断开边等价于求权值总和减去一棵子树权值和的两倍的绝对值。

然后题目就变成了单点加，子树查的树上问题，先用 dfs 序下树，再用树状数组维护即可。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5; 
long long n,m,l[N],r[N],opt,po,po1,tr[N],fa[N],siz[N],son[N],id[N],o,sum,op,op1;
vector<int>q[N];
void add(int i,int j)
{
	while(i<=n)
	{
		tr[i]+=j;
		i+=i&-i;
	}
}
long long cz(int i)
{
	long long ans=0;
	while(i)
	{
		ans+=tr[i];
		i-=i&-i;
	}
	return ans;
}
void dfs(int i)
{
	siz[i]=1;
	for(int j=0;j<q[i].size();++j)
	{
		if(q[i][j]==fa[i]) continue;
		fa[q[i][j]]=i;
		dfs(q[i][j]);
		siz[i]+=siz[q[i][j]];
		if(siz[son[i]]<siz[q[i][j]]) 
			son[i]=q[i][j]; 
	}
}
void dfs1(int i)
{
	++o;
	id[i]=o;
	if(!son[i]) return;
	dfs1(son[i]);
	for(int j=0;j<q[i].size();++j)
	{
		if(q[i][j]==fa[i]||q[i][j]==son[i]) continue;
		dfs1(q[i][j]);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;++i)
		cin>>l[i]>>r[i],q[l[i]].push_back(r[i]),q[r[i]].push_back(l[i]);
	cin>>m;
	dfs(1);
	dfs1(1);
	for(int i=1;i<=n;++i)
		add(i,1),sum+=1;
	for(int i=1;i<=m;++i)
	{
		cin>>opt;
		if(opt==1)
		{
			cin>>op>>op1;
			add(id[op],op1),sum+=op1;
		}
		else{
			cin>>op;
			if(fa[l[op]]==r[op])//看找的是哪一棵子树
				cout<<abs(sum-2*(cz(id[l[op]]+siz[l[op]]-1)-cz(id[l[op]]-1)))<<'\n';
			else
				cout<<abs(sum-2*(cz(id[r[op]]+siz[r[op]]-1)-cz(id[r[op]]-1)))<<'\n';
		}
	}
	return 0;
 }
```

---

## 作者：_Weslie_ (赞：1)

不是，我 $5$ 月 $16$ 日刚做过树上树状数组，$5$ 月 $17$ 日就来这么一道，实在巧的离谱了。

## Solution AT_abc406_f

### Idea

转化操作。

- 操作 $1$：单点加 $x$。
- 操作 $2$：子树求和。

接下来我们说说把操作 $2$ 转化为子树求和的可行性。

由于操作 $2$ 与边有关，所以我们要把边转化成点。这个点是边的两个端点中深度大的。

然后求两边权值差的绝对值。一边是子树和，另外一边是整棵树的和减掉子树和。整棵树的和简单，我们只需要处理子树和。

然后就非常简单了。把树转化成 dfs 序，对每个点 $u$ 记录子树 dfs 序最小值 $l$（这个 $l$ 显然是 $u$ 的 dfs 序）和最大值 $r$。然后用树状数组维护，就变成了单点修改，区间查询问题。

具体可以看 [P12385 题解](https://www.luogu.com.cn/article/vdcoxjrw)。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=300005;
struct node{
    int u,v,nxt;
}e[N<<1];
int head[N],cnt,n;
void addd(int u,int v){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int idx;
int l[N],r[N],dep[N],u[N],v[N];
ll sum[N];
void dfs(int now,int fa){
    dep[now]=dep[fa]+1;
    sum[now]=1;
    l[now]=++idx;
    for(int i=head[now],v;i;i=e[i].nxt){
        v=e[i].v;if(v==fa)continue;
        dfs(v,now);
        sum[now]+=sum[v];//sum[now];
    }
    r[now]=idx;
}
ll tr[N];
int lowbit(int x){
    return x&(-x);
}
void add(int now,int x){
    while(now<=n){
        tr[now]+=x;
        now+=lowbit(now);
    }
}
ll query(int now){
    ll res=0;
    while(now){
        res+=tr[now];
        now-=lowbit(now);
    }
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u[i],&v[i]);
        addd(u[i],v[i]);
        addd(v[i],u[i]);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        // printf("%d %d\n",l[i],r[i]);
        add(l[i],1);
    }
    int q;scanf("%d",&q);
    for(int opt,x,y;q;q--){
        scanf("%d%d",&opt,&x);
        if(opt==1){
            scanf("%d",&y);
            add(l[x],y);
        }
        else{
            int t=0;
            if(dep[u[x]]>dep[v[x]])t=u[x];
            else t=v[x];
            // printf("%d\n",t);
            ll qq=query(n),pp=query(r[t])-query(l[t]-1);
            printf("%lld\n",abs(pp-(qq-pp)));
        }
    }
}
```

---

## 作者：Ryanhao (赞：0)

赛时打了树剖，赛后发现是炮打蚊子。

其实只需要用到组成树剖的一个东西：dfs 序（当然还有树剖的思想）。

何为 dfs 序？

这东西是记录对树 dfs 时为每个节点打的“时间戳”。有个特性：**以某个节点为根的子树上所有节点的 dfs 序是连续的。** 记住这段话，马上要考。

好了，回到题目：求得 dfs 序，我们就可以把一棵树降维打击成一条链，就可以套各种东西啦。本题是求子树和，所以我们套树状数组或线段树。

对于题目中的询问，我们可以这样看：

令树的点权和为 $s$。把一条边“剪掉”后，$s$ 被分成两部分，一部分设为 $a$，另一部分为 $s-a$，答案就是 $|a-(s-a)|=|2a-s|$。

回到树上，不难发现，以深一点的点为根的子树的点权和加上剩下的点权和就是 $s$，有了前面的 dfs 序铺垫，我们可以方便的计算出以深一点的点为根的子树的点权和，考虑把它设为 $a$。接下来的操作就不难了，详见代码。

## ACCode

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;
const int maxn = 3e5+5;

vector<int> G[maxn]; int a[maxn];
int Es[maxn],Ee[maxn],d[maxn],siz[maxn];
int A[maxn],n,I[maxn],__cnt;

void init(int u, int vat) {
  I[u] = ++__cnt;
  d[u] = d[vat]+1;
  siz[u] = 1;
  for (int v : G[u]) {
    if (v == vat) continue;
    init(v,u);
    siz[u] += siz[v];
  }
}
void change(int x, int k) {
  for (int i = x; i <= n; i += lowbit(i)) {
    A[i] += k;
  }
}
int query(int l, int r) {
  int ans = 0;
  for (int i = r; i > 0; i -= lowbit(i)) ans += A[i]; 
  for (int i = l-1; i > 0; i -= lowbit(i)) ans -= A[i]; 
  return ans;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    change(i,1); // 记得每个点的点权初值为 1
  }
  for (int i = 1; i < n; i++) {
    cin >> Es[i] >> Ee[i];
    G[Es[i]].push_back(Ee[i]);
    G[Ee[i]].push_back(Es[i]);
  }
  init(1,0);
  int q; cin >> q;
  while(q--) {
    int op; cin >> op;
    if (op == 1) {
      int u,w; cin >> u >> w;
      change(I[u],w);
    } else {
      int x; cin >> x;
      int u = Es[x], v = Ee[x];
      if (d[u] < d[v]) swap(u,v); // 深一点的节点为 u，计算以 u 为根的子树点权和。
      cout << abs(2*query(I[u],I[u]+siz[u]-1)-query(1,n)) << endl;
      // I[u] 表示一个点的 dfs 序。
      // 以 u 为根的子树点权和就是 I[u]~I[u]+siz[u]-1 的区间和。
    }
  }
  return 0;
}
```

---

## 作者：__O_v_O__ (赞：0)

第一个操作太简单，重点考虑如何做第二个操作。

考察删去一条边后的两个连通块。它们有什么性质能够帮助我们统计呢？结合样例或者画几个图，我们发现：两个连通块中必然有一个是完整的子树，而另一个是整棵树减去这个子树。

这样就把问题转化为了单点加，子树询问和。我们在每个节点上维护它的子树和，单点加 $x$ 就是把 $x$ 到根的路径上全部增加。可以简单维护，这里我使用的是树链剖分。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lid id<<1
#define rid id<<1|1 
#define le(x) (tr[x].r-tr[x].l+1)
int n,m,a[300001],h[300001],en,cn;
int rk[300001],so[300001],si[300001];
int de[300001],to[300001],df[300001];
int fa[300001],al;
struct E{int to,nx;}e[600001];
struct A{
	int a,b;
}kk[600001];
struct s_t{
	int l,r,s,la;
}tr[1500001];
void ae(int fr,int to){
	e[++en]={to,h[fr]},h[fr]=en;
}
void pu(int id){
	tr[id].s=(tr[lid].s+tr[rid].s);
}
void pd(int id){
	if(!tr[id].la)return;
	tr[lid].la=(tr[lid].la+tr[id].la);
	tr[rid].la=(tr[rid].la+tr[id].la);
	tr[lid].s=(tr[lid].s+le(lid)*tr[id].la);
	tr[rid].s=(tr[rid].s+le(rid)*tr[id].la);
	tr[id].la=0;
}
void bd(int id,int l,int r){
	tr[id].l=l,tr[id].r=r;
	if(l==r){
		tr[id].s=a[rk[l]];
		return;
	}
	int mi=l+r>>1;
	bd(lid,l,mi),bd(rid,mi+1,r);
	pu(id);
}
void md(int id,int l,int r,int x){
	if(tr[id].l==l&&tr[id].r==r){
		tr[id].s=(tr[id].s+le(id)*x);
		tr[id].la=(tr[id].la+x);
		return;
	} 
	pd(id);
	int mi=tr[id].l+tr[id].r>>1;
	if(r<=mi)md(lid,l,r,x);
	else if(l>mi)md(rid,l,r,x);
	else md(lid,l,mi,x),md(rid,mi+1,r,x);
	pu(id);
}
int qr(int id,int x){
	if(tr[id].l==tr[id].r){
		return tr[id].s;
	}
	pd(id);
	int mi=tr[id].l+tr[id].r>>1;
	return qr(x<=mi?lid:rid,x);
}
void dfs1(int x,int f){
	so[x]=-1,si[x]=1;
	de[x]=de[f]+1;
	for(int i=h[x];i;i=e[i].nx){
		int v=e[i].to;
		if(v==f)continue;
		dfs1(v,x),si[x]+=si[v],fa[v]=x;
		if(so[x]==-1||si[so[x]]<si[v])so[x]=v;
	}
}
void dfs2(int x,int tp){
	to[x]=tp,df[x]=(++cn),rk[cn]=x;
	if(so[x]==-1)return;
	dfs2(so[x],tp);
	for(int i=h[x];i;i=e[i].nx){
		int v=e[i].to;
		if(v==fa[x]||v==so[x])continue;
		dfs2(v,v);
	}
}
void ad(int x,int y,int k){
	while(to[x]!=to[y]){
		if(de[to[x]]<de[to[y]])swap(x,y);
		md(1,df[to[x]],df[x],k);
		x=fa[to[x]];
	}
	if(de[x]>de[y])swap(x,y);
	md(1,df[x],df[y],k);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n,al=n;
	for(int i=1;i<n;i++){
		int x,y;cin>>x>>y;
		ae(x,y),ae(y,x);
		kk[i]={x,y};
	}
	cin>>m;
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;i++)a[i]=si[i];
	bd(1,1,n);
	while(m--){
		int op,x,y;cin>>op;
		if(op==1)cin>>x>>y,ad(1,x,y),al+=y;
		else{
			cin>>x;
			int a1=kk[x].a,a2=kk[x].b;
			if(de[a1]>de[a2])swap(a1,a2);
			int no=qr(1,df[a2]);
			cout<<abs((al-no)-no)<<'\n';
		}
	}
	return 0;
} 
```

---

