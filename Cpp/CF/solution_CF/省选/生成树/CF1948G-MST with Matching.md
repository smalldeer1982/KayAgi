# MST with Matching

## 题目描述

给定一个 $n$ 个点的无向连通图，令 $i, j$ 之间的边权为 $w_{i, j}$，若无边则 $w_{i, j} = 0$。

再给定一个常数 $c$。

你需要找到这个图的一个生成树，使得这个生成树的权值最小。定义一个生成树的权值为以下两者的和：

- 生成树中所有边权的和；
- 生成树上**最大匹配**的大小乘 $c$。

一个无向图 $G = (V, E)$ 的匹配为：一个边集 $E$ 的子集 $E'$，满足对于任意一个点 $i \in V$，不存在两条与 $i$ 相连的边 $(i, a), (i, b)$，使得 $(i, a), (i, b) \in E'$。

## 说明/提示

对于 $100 \%$ 的数据，保证 $2 \leq n \leq 20, 1 \leq c \leq 10^6, 0 \leq w_{i, j} \leq 10^6$。

保证 $w_{i, j} = w_{j, i}, w_{i, i} = 0$。

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
4 10
0 1 8 0
1 0 1 0
8 1 0 2
0 0 2 0```

### 输出

```
21```

## 样例 #2

### 输入

```
4 5
0 1 8 0
1 0 1 0
8 1 0 2
0 0 2 0```

### 输出

```
14```

# 题解

## 作者：Register_int (赞：16)

首先有最大匹配等于最小点覆盖，所以我们直接枚举这个点覆盖，把这个点覆盖连着的边扔进去跑一遍最小生成树即可。这里我懒所以 kruskal，时间复杂度 $O(2^nn^2\log n)$。用 Prim 可以做到 $O(2^nn^2)$。

这复杂度还开 $n=20$，一个点 $\text{6\,s}$ 还搞 $81$ 个点，出题人素质低下。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 10;

int n, c, g[20][20], ans = 1e9;

struct node {
	int u, v, w;
	node(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
	bool operator < (const node &rhs) const { return w < rhs.w; }
} a[MAXN]; int tot, fa[20];

int find(int k) {
	return k == fa[k] ? k : fa[k] = find(fa[k]);
}

inline 
int kruskal() {
	sort(a, a + tot); int cnt = 0, res = 0;
	for (int i = 0; i < n; i++) fa[i] = i;
	for (int i = 0, u, v; i < tot; i++) {
		u = find(a[i].u), v = find(a[i].v);
		if (u == v) continue; fa[u] = v, cnt++, res += a[i].w;
	}
	return cnt == n - 1 ? res : 1e9;
}

int main() {
	scanf("%d%d", &n, &c);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) scanf("%d", &g[i][j]);
	}
	for (int s = 1; s < 1 << n; s++) {
		tot = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if ((s >> i & 1 || s >> j & 1) && g[i][j]) a[tot++] = { i, j, g[i][j] };
			}
		}
		ans = min(ans, kruskal() + c * __builtin_popcount(s));
	}
	printf("%d", ans);
}
```

---

## 作者：Purslane (赞：5)

注意到一棵树是一个二分图，二分图的最大匹配等于最小点覆盖。枚举点覆盖，求解所有可能的边的 $\rm MST$ 即可。复杂度 $O(n^22^n \alpha(n))$，可以通过本题。

个人认为第一步转化是相当巧妙的，帮助我们量化最大匹配这一组合量。

[Submission](https://codeforces.com/contest/1948/submission/251924614)

---

## 作者：I_am_Accepted (赞：4)

## 做法一

在二分图中最大匹配 $=$ 最小点覆盖，树是二分图。

枚举最小点覆盖的点集，两端均不在点集里的边不合法。合法的边跑 MST 即可。

## 做法二

在二分图中最大匹配 $+$ 最大独立集 $=n$。

状压 DP，从一个被选入独立集的点开始，每次挂上一个下图这样的菊花（黑点作为独立集，下图黑点个数可以为零）：

![](https://cdn.luogu.com.cn/upload/image_hosting/g7n6g7vn.png)

这样一定是独立集，而且每种非空独立集的状态均能被转移到，所以包含最大独立集的状态。

两种做法复杂度均可做到 $O(2^nn^2)$。

---

## 作者：rui_er (赞：3)

非常精彩的转化！

显然，树是二分图。由 König 定理，我们知道：二分图最小点覆盖等于最大匹配。因此枚举点覆盖 $S$，则一条边 $(u,v)$ 可以被选择，当且仅当 $u\in S\lor v\in S$，在所有可以选择的边上跑最小生成树即可。

我采用的是 Kruskal 算法，时间复杂度为 $O(2^nn^2\log n)$，可能略有卡常，可以使用 Prim 算法做到 $O(2^nn^2)$。

```cpp
// Problem: MST with Matching
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1948G
// Memory Limit: 500 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 20, inf = 0x1f1f1f1f;

int n, c, a[N][N], ans = +inf;
vector<tuple<int, int, int>> G;

struct Dsu {
    int fa[N];
    void init(int x) {rep(i, 0, x - 1) fa[i] = i;}
    int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if(x == y) return false;
        fa[x] = y;
        return true;
    }
}dsu;

int kruskal() {
    sort(G.begin(), G.end(), [](auto x, auto y) {
        return get<2>(x) < get<2>(y);
    });
    dsu.init(n);
    int rem = n, mst = 0;
    for(auto [u, v, w] : G) {
        if(dsu.merge(u, v)) {
            --rem;
            mst += w;
        }
    }
    return rem == 1 ? mst : +inf;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> c;
    rep(i, 0, n - 1) rep(j, 0, n - 1) cin >> a[i][j];
    rep(S, 1, (1 << n) - 1) {
        G.clear();
        rep(i, 0, n - 1) {
            rep(j, i + 1, n - 1) {
                if(((S >> i) & 1) || ((S >> j) & 1)) {
                    if(a[i][j]) {
                        G.emplace_back(i, j, a[i][j]);
                    }
                }
            }
        }
        chkmin(ans, kruskal() + c * __builtin_popcount(S));
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：zzzYheng (赞：1)

### CF1948G MST with Matching

#### 题意：

给定一张 $n$ 个点的图和一个常数 $c$。定义一个生成树的权值为边权和加上，最大匹配与 $c$ 的乘积。

求权值最小的生成树的权值。

数据范围：$n\le 20$。

#### 思路：

直接用最小斯坦纳树摁做可以做到 $\Theta(3^{n}\cdot \operatorname{poly}(n))$。

更好的办法是考虑将最大匹配对偶成最小点覆盖，此时最值方向同向，取最小点覆盖等价于任选一个点覆盖。

那么先钦定一个点覆盖，这等价于 ban 一些边，然后直接求出最小生成树即可，时间复杂度 $\Theta(2^nn^2)$。

---

## 作者：Union_Find (赞：1)

看到题目中有生成树上**最大匹配的大小**，其实就是**最小点覆盖**。因为这题 $n \le 20$，我们可以直接暴力枚举选择哪些点去覆盖。然后直接最小生成树，是 $O(2^nn^2 \log n)$ 的，有点卡常，可以在一开始输入边的时候先排序，就变成了 $O(n^2\log n + 2^nn^2)$ 的了，十分容易的通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll int
#define il inline
#define N 20
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), c = rd(), w[N][N], ans = 1e9, cnt, fa[N], id[N][N], t[N * N];
il ll find(ll x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
struct E{
	ll w, u, v;
}e[N * N];
il bool cmp(E a, E b){return a.w < b.w;}
il ll ww(ll s){ll ans = 0;for (int i = 0; i < n; i++) if (s & (1 << i)) ans++;return ans;}
il ll kls(ll s){
	for (int i = 0; i < n; i++) fa[i] = i;
	ll ans = 0, tot = 0;
	for (int i = 1; i <= cnt; i++){
		if (!t[i]) continue;
		ll fu = find(e[i].u), fv = find(e[i].v);
		if (fu != fv) fa[fu] = fv, ans += e[i].w, tot++;
	}return tot == n - 1 ? ans : 1e9;
}
int main(){
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++){
		w[i][j] = rd();
		if (i > j && w[i][j]) e[++cnt] = E{w[i][j], i, j};
	}sort (e + 1, e + cnt + 1, cmp);
	for (int i = 1; i <= cnt; i++) id[e[i].u][e[i].v] = id[e[i].v][e[i].u] = i;
	for (int s = 0; s < (1 << n); s++){
		for (int i = 1; i <= cnt; i++) t[i] = 0;
		for (int i = 0; i < n; i++) for (int j = 0; j < i; j++){
			if (((s & (1 << i)) || (s & (1 << j))) && w[i][j]) t[id[i][j]] = 1;
		}
		ans = min(ans, ww(s) * c + kls(s));
	}
	printf ("%d\n", ans);
	return 0;
}

```

---

## 作者：zifanwang (赞：1)

题目要求一个最小值加上一个最大值的最小值，不好直接做，考虑转化。

发现树是二分图，而由柯尼希定理可知二分图的最大匹配等于其最小点覆盖。这样就把求 $\min(\min_{\text{生成树}}+\max_{匹配})$ 转化为了 $\min(\min_{生成树}+\min_{覆盖})$。

直接 $\mathcal O(2^n)$ 枚举最小点覆盖中的点，每次做一遍最小生成树即可。时间复杂度 $\mathcal O(2^nn^2)$。

[code](https://codeforces.com/contest/1948/submission/252739519)

---

## 作者：yizhiming (赞：1)

数据范围翻译错了，应该是 $n\leq 20$ 才对，害得我想了好久。

## 题目大意

给定一个 $n$ 个点的无向连通图，读入 $w_{i,j}$ 表示 $i$ 和 $j$ 之间的边权，特别的，若为 $0$ 则视作无边。

读入常数 $c$，求这个图的权值最小的生成树，权值定义为边的和，加上最大匹配数乘 $c$。

$1\leq n\leq 20,1\leq c\leq10^6,0\leq w_{i,j}\leq10^6$。

## 题目解析

首先我们假设只保留生成树上的边，那么原图可以视作二分图，那么就有经典结论，最大匹配 $=$ 最小点覆盖，所以将最大匹配转换成最小点覆盖去做这个问题。

最小点覆盖是什么呢，是保证每条边都至少有一个端点被选的情况下，最小的被选点集的大小，注意到 $n\leq 20$，所以 $2^n$ 枚举被选点集，在钦点集的情况下做最小生成树，相当于将原图上有至少一个端点被选的边拎出来，单独做最小生成树。

所以枚举点集后，用 Prim 或者 Kruskal 即可，复杂度 $O(2^n n^2)$。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 2e6+5;
const int M = 22;
int inf = 2e18;
int w[M][M],n,c;
bool vis[N],flg[N];
int val[N];
int che(int x){
	int sum = 0;
	for(int i=1;i<=n;i++){
		vis[i] = (x>>(i-1))&1;
		sum+=vis[i];
		val[i] = inf;flg[i] = 0;
	}
	flg[1] = 1;
	int res = sum*c;
	for(int i=1;i<=n;i++){
		if(!w[1][i]){
			continue;
		}
		if(vis[1]||vis[i]){
			val[i] = min(val[i],w[1][i]);
		}
	}
	val[0] = inf;
	for(int i=1;i<n;i++){
		int u = 0;
		for(int j=1;j<=n;j++){
			if(flg[j]){
				continue;
			}
			if(val[j]<val[u]){
				u = j;
			}
		}
		if(!u){
			return inf;
		}
		res+=val[u];
		flg[u] = 1;
		for(int j=1;j<=n;j++){
			if(flg[j]||!w[u][j]){
				continue;
			}
			if(vis[j]||vis[u]){
				val[j] = min(val[j],w[u][j]);
			}
		}
	}
	return res;
}
signed main(){
	n = read();c = read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			w[i][j] = read();
		}
	}
	int up = (1<<n)-1;
	int ans = inf;
	for(int i=1;i<=up;i++){
		ans = min(ans,che(i));
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：唐一文 (赞：1)

感觉这题有点太草率了。。

最大匹配不好算，有结论：

在二分图中，最大匹配 $=$ 点数减去最大独立集。（树也是二分图）

那么枚举独立集，如果一条边的两个端点至少有一个不在独立集里，这条边就能选。对这些边求 MST，再加上最大匹配的代价就行了，所有独立集计算出来的答案取 $\min$ 即可。注意要判断这棵生成树是否让整张图联通。

由于是稠密图，用 prim 复杂度 $O(n^22^n)$。

笔者比较唐，用了 kruskal 导致直接做的话复杂度 $O(n^22^n\log n)$ 过不去。所以按集合大小从大到小做，维护每个集合的 MST 边集，一个集合从它的超集扩展过来做到 $O(n2^n\log n)$。[code](https://codeforces.com/contest/1948/submission/251925204)

---

## 作者：xiezheyuan (赞：0)

## 简要题意

以邻接矩阵形式给出一个 $n$ 个点的无向带权简单图和一个常数 $c$。

定义这个图的一个生成树的权值，为其边权和加上最大匹配数的 $c$ 倍。输出权值最小值。

$2\leq n\leq 20$。

## 思路

首先看到最大匹配，大概率要往二分图最大匹配去想，无良出题人应该是不会考带花树之类的东西吧。

然后你迅速发现树是一个二分图（因为我可以按照深度的奇偶性染色），于是可以应用二分图最大匹配的性质。

同时很容易发现 $n\leq 20$ 这个约束条件，应该是暗示我们使用指数级算法枚举一个量，边权和相对容易维护（最小生成树即可），但最大匹配难以维护，可以考虑枚举这个量。

但是最大匹配与边有关，而边有 $O(n^2)$ 条不适合枚举，不妨**利用 König 定理，转为最大独立集**。

最大独立集是点集，因此可以 $O(2^n)$ 枚举点集，然后排除端点均在独立集的边跑最小生成树算法来更新答案，由于求的是最小值，所以不用刻意限制最大，只需要枚举独立集即可。

使用 Kruskal 算法在稠密图下表现不佳（至少难以通过本题），改为 Prim 算法即可通过。

时间复杂度 $O(2^nn^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

using i64 = long long;
const int N = 25;
int n, c, a[N][N], b[N][N], dis[N];
bool vis[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cin >> a[i][j];
    }
    i64 ans = LLONG_MAX;
    dis[0] = INT_MAX; vis[1] = 1;
    for(int S=0;S<(1<<n);S++){
        int cnt = 0;
        i64 sum = 0; bool flag = 1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) b[i][j] = (((S >> (i - 1)) & 1) && ((S >> (j - 1)) & 1)) ? 0 : a[i][j];
        }
        fill(vis + 2, vis + n + 1, 0);
        fill(dis + 2, dis + n + 1, INT_MAX);
        for(int i=1;i<=n;i++){
            if(b[1][i]) dis[i] = b[1][i];
        }
        for(int i=1;i<n;i++){
            int x = 0;
            for(int j=1;j<=n;j++){
                if(!vis[j] && dis[j] < dis[x]) x = j;
            }
            if(!x){ flag = 0; break; }
            vis[x] = 1, sum += dis[x];
            for(int j=1;j<=n;j++){
                if(!vis[j] && b[x][j]) dis[j] = min(dis[j], b[x][j]);
            }
        }
        if(flag) ans = min(ans, sum + 1ll * c * (n - __builtin_popcount(S)));
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：strapplE (赞：0)

为啥题解都是转最小点覆盖啊……感觉这步十分套路且不直观，说一个常人思维能想出的做法。

事情是这样的。它要你得到那个最大边独立集，即选尽量多的边出来，额外贡献是边数乘 $c$。那我们考虑一种特殊情形：如果所有点都在一个选中的边中，此时的生成树最小是多少？

不难想到，如果我们把每条选中的边对应的两个点捆在一起，则直接求出“缩点”后的 MST 即可。而求 MST 有个蠢办法：考虑一个一直删叶子的过程，把它倒过来，其实就相当于一个连通块每次多加一条边，多出一个点。这个做状压 dp 是很容易的。比如设 $f_S$ 表示目前状态是 $S$ 时的答案，则可以转移到 $f_{S+u+v}$，贡献是 $w_{u,v}+c+\min\limits_{i\in S,j\in \{u,v\}}w_{i,j}$，这个复杂度可以做到 $O(2^nn^2)$ 的。

回到原题，不难发现也可以考虑成这样：把 $\{1,2,\dots,n\}$ 拆成若干个大小至少为 $2$ 的集合，每个集合都选出里面的一个 MST，再在大层跑个 MST，额外贡献是 $c$ 乘上分成的集合个数。暴力 $dp$ 需要枚举子集，复杂度是 $O(3^n)$。

怎么优化呢？其实可以通过这个选出的集合的特殊形态考虑。注意到，如果这个连通块有一条长度 $\geq 3$ 的路径，则可以选出两条独立的边，而不是一条，一定不优。因此这里面的直径必须 $\leq 2$，说白了，这棵树就必须要是菊花。

不过要刚好跑到菊花的顶点还是不容易，如果缩点后的那一条连边对应的不是顶点怎么办？不过仔细想想可以发现，那条边连向的点可以归到已有的一个集合中，因此最后新连出的这条一定可以连到一个菊花顶点。

那么这样就容易 dp 了。注意到可以分步转移，每次只加上菊花的一朵花瓣，枚举量是不大的。具体地，设 $f_S$ 表示大集合加到了 $S$ 的答案，$g_{S,x}$ 表示目前停留在一个菊花，其中顶点编号是 $x$ 是的最优解。转移三种：

- $f\rightarrow g$，也即新建一个菊花，此时只有一个点不能形成集合，需要再来一个点。
- $g\rightarrow g$，加一个花瓣。
- $g\rightarrow f$，此时在第二种转移的时候同步进行，也就是说完成了一朵菊花，可以进行再往后的转移了。

此时每个枚举都只需要一个 $1\sim n$ 的位置，因此综复杂度就是状态数乘上单次转移数，即 $O(2^nn^2)$。十分好想又好写！

```cpp
#include<bits/stdc++.h>
using namespace std;
int w[25][25],vist[25],aa[25];
int f[1<<20],g[1<<20][25];
int main(){
	int n,c;
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			scanf("%d",&w[i][j]);
		}
	}
	memset(f,63,sizeof(f));
	memset(g,63,sizeof(g));
	f[0]=0;
	for(int i=0;i<(1<<n);++i){
		int t=0;
		for(int j=1;j<=n;++j){
			vist[j]=(i>>(j-1)&1);
			if(vist[j])aa[++t]=j;
		}
		for(int j=1;j<=n;++j)if(!vist[j]){
			int mx=1e9;
			for(int k=1;k<=t;++k)if(w[j][aa[k]])mx=min(mx,w[j][aa[k]]);
			if(mx<1e8||i==0){
				int ii=i|(1<<(j-1));
				g[ii][j]=min(g[ii][j],f[i]+(mx<1e8?mx:0)+c);
			}
		}else{
			for(int k=1;k<=n;++k)if(!vist[k]&&w[j][k]){
				int ii=i|(1<<(k-1));
				g[ii][j]=min(g[ii][j],g[i][j]+w[j][k]);
				f[ii]=min(f[ii],g[i][j]+w[j][k]);
			}
		}
	}
	printf("%d\n",f[(1<<n)-1]);
	return 0;
}
```

---

## 作者：Kevin_Lsy (赞：0)

# 思路转化
这道题乍一看没有什么思路，考虑拆分答案两部分贡献:

- 贡献 1 : 最小化生成树中所有边权的和，求最小生成树即可，关键在于贡献 2 中最优边集的选择，对于一个确定的边集，贡献1是确定的。
- 贡献 2 : 很妙的转化，有性质: 一棵树一定是一个二分图。最大匹配的大小不好处理，但二分图最大匹配=最小点覆盖，可以把这一贡献转化到只与点相关，这样就可以枚举点覆盖的点集了。对于每个在点集中的点，将其连出的所有边加入求最小生成树的候选边集中，就可以求对应的贡献 1 了。
# 实现
点覆盖的点集用子集枚举，时间复杂度 $O(2^n)$ , 枚举的每种情况求对应的最小生成树更新答案,(此处我的实现为 $\text{Kruskal}$ ), 时间复杂度 $O(n^2\log n) .$\
总时间复杂度 $O(2^nn^2\log n)$ , 可以通过本题(码风微丑)
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=21,M=1e3+7,inf=1e9;
int n,c;
int w[N][N],ans=inf,tot,fa[N],cnt,ret,u,v,siz[N];
struct edge{
	int u,v,w;
	bool operator<(const edge &x){
		return w<x.w;
	}
}e[M];
int find(int x){
	if(fa[x]^x)return fa[x]=find(fa[x]);
	return x;
}
inline int kru(){
	sort(e+1,e+tot+1);
	cnt=ret=0;
	for(register int i=0;i<n;++i){
		fa[i]=i,siz[i]=1;
	}
	for(register int i=1;i<=tot;++i){
		u=find(e[i].u),v=find(e[i].v);
		if(u^v){
			if(siz[u]<siz[v])u^=v^=u^=v;
			siz[u]+=siz[v],fa[v]=u;
			cnt++,ret+=e[i].w;
		}
	}
	return (cnt==n-1?ret:inf);
}
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
int main(){
	n=read(),c=read();
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			w[i][j]=read();
		}
	}
	for(int k=0;k<(1<<n);++k){
		tot=0;
		for(int i=0;i<n;++i){
			for(int j=0;j<i;++j){
				if((k>>i&1||k>>j&1)&&w[i][j]){
					e[++tot]={i,j,w[i][j]};
				}
			}
		}
		ans=min(ans,kru()+c*__builtin_popcount(k));
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://luogu.com.cn/problem/CF1948G)

给你一张图，定义其生成树的权值为其（最小生成树的权值和）加上（最大匹配 $\times c$）。求最小生成树的权值。

$n \le 20,c \le 10^6,w \le 10^6$。

---

首先，~~显然~~树是一个二分图，那么它的最大匹配就是最小覆盖。

因此，我们只需要枚举一下最小覆盖的点集，在连接这些点的边上跑一遍 $\text{Prim}$ 就好了。时间复杂度 $O(2^n \cdot n^2 \log n)$。

这个复杂度比较卡常，但是我们可以把排序放在外面做，可以省一个 $\log$，就不卡常了（$1499\text{ms}$）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 25;

struct edge{ int u, v, w; } e[N * N];
bool cmp( edge x, edge y ){ return x.w < y.w; }
vector<int> E[N];
bool xuan[N * N];
int cnt, n, ans, c;

struct bcj{
	int fa[N];
	void csh( int n ){ for( int i = 1; i <= n; ++i ) fa[i] = i; }
	int find( int x ){ return fa[x] == x ? x : fa[x] = find( fa[x] ); }
	void add( int a, int b ){ fa[find( a )] = find( b ); }
} b1;

int mst( int dianji ){
	memset( xuan, 0, sizeof xuan );
	int ans = 0;
	b1.csh( n );
	for( int i = 0; i < n; ++i ){
		if( dianji & ( 1 << i ) ){
			for( auto j : E[i + 1] ){
				xuan[j] = 1;
			}
		}
	}
	for( int i = 1; i <= cnt; ++i ){
		if( xuan[i] ){
			if( b1.find( e[i].u ) != b1.find( e[i].v ) ){
				ans += e[i].w;
				b1.add( e[i].u, e[i].v );
			}
		}
	}
	for( int i = 1; i < n; ++i ) if( b1.find( i ) != b1.find( i + 1 ) ) return -1;
	return ans;
}

int popc( int i ){
	int ans = 0;
	while( i ){
		if( i & 1 ) ++ans;
		i >>= 1;
	}
	return ans;
}

int main(){
	scanf( "%d%d", &n, &c );
	for( int i = 1; i <= n; ++i ){
		for( int j = 1; j <= n; ++j ){
			int w;
			scanf( "%d", &w );
			if( i >= j ) continue;
			if( w ) e[++cnt] = { i, j, w };
		}
	}
	sort( e + 1, e + cnt + 1, cmp );
	for( int i = 1; i <= cnt; ++i ){
		E[e[i].u].push_back( i ), E[e[i].v].push_back( i );
	}
	ans = 0x7fffffff;
	for( int i = 1; i < ( 1 << n ); ++i ){
		int _ans = mst( i );
		if( _ans == -1 ) continue;
		_ans += popc( i ) * c;
		ans = min( ans, _ans );
	}
	printf( "%d\n", ans );
	return 0;
}
```

---

用一些奇特的卡常卡进了最优解前三。[record](https://www.luogu.com.cn/record/158366929) [code](https://www.luogu.com.cn/paste/mcen4mjy)

---

## 作者：daniEl_lElE (赞：0)

首先最小化一个东西与另一个东西最大值的和看着就别扭，考虑将**最大匹配**对偶变成**最小点覆盖**。

于是，题目可以转化为最小化生成树中所有边权的和与生成树**某个**点覆盖的大小乘 $c$ 的和。

考虑一个遍历这棵树的方式。每次可以新加入一个属于点覆盖的点，并将其周围不在点覆盖中的点加入。显然这样可以遍历这棵树并确定某些点属于点覆盖。

考虑 $dp_{S,i}$ 表示目前考虑了 $S$ 中的点，目前钦定的被选中入点覆盖的点为 $i$。

每次新加一个点，如果他不在点覆盖中，就加入他并与 $i$ 连边。同时也可以选择一个新的点，将其与 $S$ 中某个点连边并选为点覆盖中的一个。

总复杂度 $O(n^22^n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
int g[25][25];
int dp[25][1048576],f[25][1048576];
signed main(){
	int n,c; cin>>n>>c;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>g[i][j];
			if(g[i][j]==0) g[i][j]=1e9;
		}
		for(int j=0;j<(1<<n);j++){
			f[i][j]=1e9;
			for(int k=1;k<=n;k++) if((j>>(k-1))&1) f[i][j]=min(f[i][j],g[i][k]);
		}
	}
	memset(dp,1,sizeof(dp));
	for(int i=1;i<=n;i++) dp[i][1<<(i-1)]=c;
	for(int j=0;j<(1<<n);j++){
		for(int i=1;i<=n;i++){
			if((j>>(i-1))&1){
				for(int k=1;k<=n;k++){
					if(!((j>>(k-1))&1)){
						dp[i][j|(1<<(k-1))]=min(dp[i][j|(1<<(k-1))],dp[i][j]+g[i][k]);
						dp[k][j|(1<<(k-1))]=min(dp[k][j|(1<<(k-1))],dp[i][j]+c+f[k][j]);
					}
				}
			}
		}
	}
	int minv=1e9;
	for(int i=1;i<=n;i++) minv=min(minv,dp[i][(1<<n)-1]);
	cout<<minv;
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

转化还是挺好的。

考虑树的最大匹配是什么，往二分图方面考虑，**二分图最大匹配 $=$ 最小点覆盖**。

那我们枚举最小点覆盖集合再跑 MST 即可。

注意此时生成的 MST 只需保证枚举的点覆盖集合是合法点覆盖集合即可。相当于钦定若干条边不选。

用 Prim 实现，复杂度 $O(2^n n^2)$。

还有一个做法，是把**二分图最大匹配转化为点数减去最大独立集**。然后枚举独立集，是类似的。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1948/submission/255160316)

---

