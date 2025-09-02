# [AGC012D] Colorful Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc012/tasks/agc012_d

すぬけくんは $ N $ 個の色が塗られたボールを一列に並べました。 左から $ i $ 番目のボールは色 $ c_i $ で塗られていて、その重さは $ w_i $ です。

すぬけくんは以下の $ 2 $ 種類の操作を任意の順序で何回でも繰り返してボールの配置を変更することができます。

- 操作 $ 1 $：色が同じであるような $ 2 $ つのボールを選ぶ。$ 2 $ つのボールの重さの和が $ X $ 以下なら、$ 2 $ つのボールの位置を入れ替える。
- 操作 $ 2 $：色が異なるような $ 2 $ つのボールを選ぶ。$ 2 $ つのボールの重さの和が $ Y $ 以下なら、$ 2 $ つのボールの位置を入れ替える。

最終的なボールの色の並びとしてありうるような数列の数を modulo $ 10^9\ +\ 7 $ で求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 2\ ×\ 10^5 $
- $ 1\ ≦\ X,\ Y\ ≦\ 10^9 $
- $ 1\ ≦\ c_i\ ≦\ N $
- $ 1\ ≦\ w_i\ ≦\ 10^9 $
- $ X,Y,c_i,\ w_i $ はいずれも整数

### Sample Explanation 1

\- 操作 $ 2 $ により左から $ 1 $ 番目のボールの位置と左から $ 3 $ 番目のボールの位置を入れ替えることで、$ (2,4,3,4) $ という色の並びを作ることが可能です。 - 操作 $ 1 $ により左から $ 2 $ 番目のボールの位置と左から $ 4 $ 番目のボールの位置を入れ替えることも可能ですが、色の並びは変化しません。

## 样例 #1

### 输入

```
4 7 3
3 2
4 3
2 1
4 4```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1 1
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
21 77 68
16 73
16 99
19 66
2 87
2 16
7 17
10 36
10 68
2 38
10 74
13 55
21 21
3 7
12 41
13 88
18 6
2 12
13 87
1 9
2 27
13 15```

### 输出

```
129729600```

# 题解

## 作者：Kinandra (赞：13)

标签: `Luogu` 都咩有标签我怎么编的出.

#### Part 1

我们发现如果球$a$可以和球$b$交换且球$a$可以和球$c$, 我们可以通过一系列只涉及$a,b,c$的交换任意决定它们的相对顺序. 经过数学归纳法得, 我们发现**相对顺序可以改变的性质**是**可传递的**, 于是可以的到一个十分显然的 $\mathcal O(n^2)$ 的做法:

枚举两个球, 如果满足交换条件就连一条边, 则一个联通块内的所有点可以随意决定相对顺序. 那么我们该如何计算答案呢, 容易发现不同连通块的方案数是独立(分步)的, 所以我们对每个联通快分别求答案然后相乘即可. 易知一个联通快的方案数为$\frac{(\sum_i s_i)!}{\prod s_i!}$, 其中 $s_i$ 表示第 $i$ 中颜色的点数.

#### Par2

上述做法还不够优秀, 考虑优化.

发现一个联通块内有许多边是无用的(断开后不影响联通性), 考虑优化这个部分.

发现对于同色相连的边, 只用连重量最小的球和其他球之间的边.

对于异色相连的边, 只用连 **最小重量**最小的颜色重量最小的球 与 其它颜色的重量最小的球 之间的边 和 **最小重量**最小的颜色重量非最小的球 与 **最小重量**次小颜色的重量最小的球之间 的边就好了(有点绕口, 加油! *<|:-) ).

另外, 根据 `Part1` 可知: 一个联通块内至少有两种颜色对答案才有贡献, 也即如果一种颜色无法与 **最小重量**最小的颜色 连边, 那么对答案一定没有贡献, 也即只有一个联通块对答案有贡献. 所以图就不用建了, 代码实现非常简单.

复杂度$\mathcal O(n)$.

(由于很简单变量名瞎取).

```cpp
#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int read();
vector<int> c[200005];
int w[200005];

int fsp(int bs, int p) {
	int rt = 1;
	while (p) {
		if (p & 1) rt = 1ll * rt * bs % mod;
		bs = 1ll * bs * bs % mod, p >>= 1;
	}
	return rt;
}

int fac[200005], caf[200005];
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = 1ll * i * fac[i - 1] % mod;
	caf[n] = fsp(fac[n], mod - 2);
	for (int i = n; i >= 1; --i) caf[i - 1] = 1ll * i * caf[i] % mod;
}

int main() { 
	int n = read(), X = read(), Y = read();
	init(n);
	for (int i = 1, tc, tw; i <= n; ++i) {
		tc = read(), tw = read();
		if (!c[tc].size()) w[tc] = tw;
		c[tc].push_back(tw), w[tc] = min(tw, w[tc]);
	}
	int mc1 = 0, mc2 = 0;
	for (int i = 1; i <= n; ++i) 
		if (c[i].size() && (!mc1 || w[i] < w[mc1])) mc1 = i;
	for (int i = 1; i <= n; ++i) 
		if (c[i].size() && i != mc1 && (!mc2 || w[i] < w[mc2])) mc2 = i;
	if (!mc2 || w[mc1] + w[mc2] > Y) return puts("1"), 0;
	int res1 = 0, res2 = 1;
	for (int i = 1, cnt; i <= n; ++i) {
		if (!c[i].size() || w[i] + w[mc1] > Y) continue;
		cnt = 0;
		for (vector<int>::iterator j = c[i].begin(); j != c[i].end(); ++j) {
			cnt += ((*j) + w[mc1 - i ? mc1 : mc2] <= Y || (*j) + w[i] <= X);
		}
		res1 += cnt, res2 = 1ll * caf[cnt] * res2 % mod;
	}
	printf("%d\n", 1ll * fac[res1] * res2 % mod);
	return 0; 
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```

---

## 作者：tuliwei (赞：9)

先看看两个推论：
* ~~显而易见的~~推论1：  
如果一种颜色中最小的与其他颜色中最小的无法交换，  
那么这种颜色中所有球都不能与别的颜色的球交换，  
而同种颜色的球交换对颜色序列没有影响，  
那么这种颜色对答案没有贡献(~~废话~~

* ~~显而易见的~~推论2：  
如果一个球与同颜色球中最小的球无法交换，  
并且这个球与其他颜色中最小的球无法交换，  
那么这个球动不了(~~废话~~

所以说我们就可以把以上两种情况去除了  

接下来我们发现。。好像每个球都可以到任意位置了？？  
那这不组合数学直接算就好了吗？？

### 代码：
```cpp
#include <bits/stdc++.h>
//#define inf 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define inv(x) Power(x, mod - 2)
#define fi first
#define se second
#define N 200005

using namespace std;
typedef pair<int,int> Pair;
typedef long long ll;

const long double Pi = 3.14159265358979323846l;
const int mod = 1e9 + 7;
inline int add(int x, int y) { return (x += y) - (x >= mod ? mod : 0); }
inline void inc(int &x, int y) { (x += y) -= (x >= mod ? mod : 0); }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
inline int Power(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res = mul(res, x);
		x = mul(x, x), y >>= 1;
	} return res;
}

template <class T> inline T	input() {
	T x; char ch; while (!isdigit(ch = getchar()));
	for (x = ch ^ 48; isdigit(ch = getchar()); x = x * 10 + (ch ^ 48));
	return x;
}

template <class T> inline void chkmin(T &x, T &y) { x = x < y ? x : y; }
template <class T> inline void chkmax(T &x, T &y) { x = x > y ? x : y; }

struct {
	inline operator int () { return input<int>(); }
	inline operator long long () { return input<long long>(); }
	template <class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

int n, x, y;
int c[N], w[N];
int col_min[N], cnt[N], mina, minb, tot;
int fac[N], ifac[N];
bool pd_col[N];

void init() {
	ifac[0] = fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = mul(fac[i - 1], i);
	ifac[N - 1] = inv(fac[N - 1]);
	for (int i = N - 2; i; --i) ifac[i] = mul(ifac[i + 1], i + 1);
}

int C(int x, int y) {
	if (x < y || y < 0) return 0;
	return mul(fac[x], mul(ifac[y], ifac[x - y]));
}

int main() {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	freopen("debug", "w", stderr);

	init();
	read(n, x, y);
	memset(col_min, 0x3f, sizeof col_min);
	mina = minb = inf;

	for (int i = 1; i <= n; ++i) {
		read(c[i], w[i]);
		chkmin(col_min[c[i]], w[i]);
	}
	for (int c = 1; c <= n; ++c) {
		if (col_min[c] < mina) minb = mina, mina = col_min[c];
		else if (col_min[c] < minb) minb = col_min[c];
	}

	if (mina + minb > y) return puts("1"), 0;
	for (int c = 1; c <= n; ++c)
		if (col_min[c] + mina > y)
			pd_col[c] = true;

	for (int i = 1; i <= n; ++i) {
		if (pd_col[c[i]]) continue;
		if (col_min[c[i]] + w[i] <= x) ++cnt[c[i]], ++tot;
		else if ((col_min[c[i]] == mina ? minb : mina) + w[i] <= y) ++cnt[c[i]], ++tot;
	}

	int ans = 1;
	for (int c = 1; c <= n; ++c)
		ans = mul(ans, C(tot, cnt[c])), tot -= cnt[c];
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：zhiyangfan (赞：8)

### 题目
有一个长为 $n$ 的数组，第 $i$ 个元素是一个二元组 $(c_i,w_i)$，分别表示颜色和权值。共有以下两种操作可以执行：
1. 选择两个元素 $i,j$ 满足 $c_i=c_j,w_i+w_j\le x$，并把它们交换。
2. 选择两个元素 $i,j$ 满足 $c_i\ne c_j,w_i+w_j\le y$，并把它们交换。

其中 $x,y$ 为给定常数。求一共能产生多少种不同的最终序列，答案对 $10^9+7$ 取模。($1\le n\le 2\times10^5,1\le x,y,w_i\le10^9,1\le c_i\le n$)

### 题解
注意到这个「可交换」的性质是可以传递的，即如果 $A,B$ 可以交换，$B,C$ 可以交换，那么 $A,C$ 也可以交换。（手玩一下就知道惹）那「可交换」其实就可以抽象为图上的边了，如果我们把所有「可交换」关系都用边表示出来，那么最终答案即为得到的无向图中所有连通块里可重集排列数之积。（因为一个连通块里面可以任意交换）但这样的话，边的数量就达到了 $\mathcal{O}(n^2)$ 级别，显然无法接受。如果我们画几组小数据，可以发现这么多条边其实有很多都是重复的，所以我们考虑删去一些边使得图上的连通性不变。

首先考虑操作1，这个是在 $c_i$ 相同的元素中进行的，我们设 $x_i$ 表示第 $i$ 种颜色中权值最小的，设 $y_i,z_i$ 表示 $i$ 种颜色中任意的其他两个元素。则如果 $y_i+z_i\le x$，即它们两个之间能连边，则一定有 $y_i+x_i\le x,z_i+x_i\le x$，即它们两个都可以和 $x_i$ 连边。所以如果我们去掉 $(y_i,z_i)$ 这条边对连通性是没有影响的。所以对于每种颜色，我们只需要考虑其中所有元素和 $x_i$ 的连边即可，连出的边数仅为 $\mathcal{O}(n)$ 级别。

再来考虑操作2，这个是在 $c_i$ 不同的元素中进行的。依然延续上述思路，不失一般性，我们假设有：
- 颜色从 $1$ 到 $c$ 编号。
- $\forall 1\le i\le c$，我们设 $a_i$ 表示第 $i$ 种颜色中权值最小的。
- $a_1\le a_2\le\cdot\cdot\cdot\le a_c$。

则对于任意两个颜色不同的元素 $s,t$，如果有 $w_s+w_y\le y$，则有：
- 如果 $c_s\ne 1,c_t\ne 1$，则存在边 $(s,a_1),(t,a_1)$，可以删去 $(s,t)$。
- 如果 $c_s\ne 2,c_t\ne 2$，则存在边 $(s,a_2),(t,a_2)$，可以删去 $(s,t)$。
- 如果 $c_s=1,c_t=2$，则存在边 $(s,a_2),(a_1,t)$，因为 $w_s+w_y\le y$，所以一定有边 $(a_1,a_2)$，可以删去 $(s,t)$。

注意这里还涉及到了次小值，是考虑到颜色可能和最小值相同无法连边的情况。这样只需要考虑所有元素和 $a_1,a_2$ 的连边即可，连出的边数仅为 $\mathcal{O}(n)$ 级别。

这样我们就成功在连通性不变的前提下减少边数到了 $\mathcal{O}(n)$ 可以通过本题。时间复杂度 $\mathcal{O}(n)$，注意一点小细节。
```cpp
//写丑了，并查集就够了的
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
const int N = 2e6 + 10, mod = 1e9 + 7, inf = 1e9; 
std::vector<std::pair<int, int> > vec[N]; int size[N], col[N], ww[N], d[N], tp;
struct edge{ int v, next; }E[N << 1]; int p[N], vis[N], fac[N], st[N], top, cnt;
inline void init() { memset(p, -1, sizeof (p)); cnt = 0; }
inline void insert(int u, int v) { E[cnt].v = v; E[cnt].next = p[u]; p[u] = cnt++; }
inline void addedge(int u, int v) { if (u == v) return ; insert(u, v); insert(v, u); }
void dfs(int u)
{
    vis[u] = 1; ++size[tp]; st[++top] = u;
    for (int i = p[u], v; i + 1; i = E[i].next)
    {
        v = E[i].v; if (vis[v]) continue; 
        dfs(v);
    }
}
inline int ksm(int a, int b)
{
    int ret = 1;
    while (b)
    {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod; b >>= 1;
    }
    return ret;
}
int main()
{
    init(); int n, x, y, ans = 1; scanf("%d%d%d", &n, &x, &y);
    fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    for (int i = 1; i <= n; ++i) d[i] = 1;
    for (int i = 1, c, w; i <= n; ++i) 
    {
        scanf("%d%d", &c, &w); ww[i] = w; col[i] = c;
        vec[c].emplace_back(w, i);
    }      
    for (int i = 1; i <= n; ++i)
    {
        std::sort(vec[i].begin(), vec[i].end());
        for (auto v : vec[i])
            if (v.first + vec[i][0].first <= x) addedge(v.second, vec[i][0].second); 
    }
    std::pair<int, int> a(inf, 0), b(inf, 0);
    for (int i = 1; i <= n; ++i)
    {   
        if (vec[i].empty()) continue;
        if (vec[i][0].first < a.first) b = a, a = vec[i][0];
        else if (vec[i][0].first < b.first) b = vec[i][0];
    }
    for (int i = 1; i <= n; ++i)
    {
        if (col[i] == col[a.second])
            { if (b.second && ww[i] + b.first <= y) addedge(b.second, i); }
        else if (ww[i] + a.first <= y) addedge(a.second, i);
    }
    std::vector<int> vec(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) 
        {
            ++tp; top = 0; dfs(i);
            for (int j = 1; j <= top; ++j)
                ++vec[col[st[j]]], d[tp] = 1ll * d[tp] * vec[col[st[j]]] % mod;
            for (int j = 1; j <= top; ++j) vec[col[st[j]]] = 0; 
        }
    for (int i = 1; i <= tp; ++i) 
        ans = 1ll * ans * fac[size[i]] % mod * ksm(d[i], mod - 2) % mod;
    printf("%d\n", ans); return 0; 
}
```

---

## 作者：Arghariza (赞：8)

sweet tea.

手玩一下发现「交换」的性质是具有传递性的，所以考虑一个 $O(n^2)$ 做法：

枚举每个点对，如果满足交换条件，则连双向边。显然一个连通块内的点可以互相交换，而不同连通块之间互相独立。答案就是 $\prod\limits_{i=1}^m\dbinom{size_i}{s_{i,1}\ s_{i,2}\ ...\ s_{i,n}}$。 $s_{i,j}$ 表示连通块 $i$ 内颜色为 $j$ 的点的数量。本质上就是个可重排列。

很可惜，这是 AGC D，暴力过不了。

充分发扬人类智慧，我们发现这个图点数很小，但是边数很大。最后求解答案的复杂度是 $O(n+m)$ 的。我们又发现连出去的许多边是没有必要的，因为对于一个连通块，我们尽可能地只保留一个生成树，或者边数尽量少的结构，于是我们考虑如何减少重复的边。

第一种操作，每种颜色 $c$ 分开考虑。对于颜色 $c$ 的所有点，拎出一个 $w$ 值最小的 $w_{\min}$。考虑同样是颜色 $c$ 的 $(i,j)$ 满足 $w_i+w_j\le x$，那么显然有 $w_i+w_{\min}\le x$ 并且 $w_j+w_{\min}\le x$，也就是说 $i$ 到 $j$ 的边是没有必要的。于是我们可以每个点向其**同样颜色 $w$ 值最小**的点连边，边数 $O(n)$。

第二种操作，我们将所有颜色 $\text{col}$ 按照 $a_{\text{col}}=\min\limits_{c_i=\text{col}}w_i$ 从小到大排序。同上，我们考虑满足 $c_i\neq c_j,w_i+w_j\le y$ 的 $(i,j)$，但是为了避免 $i,j$ 中有颜色和 $a_\text{col}$ 最小值颜色 $c_{\min}$ 相同，我们还需要拎出来一个次小值颜色 $c_{\min_2}$ 来讨论（以下写点对颜色 $c$ 连边，实际上是对**颜色 $c$ 中权值最小的点**连边）：

- 若 $c_i\ne c_{\min},c_j\neq c_{\min}$，则不连 $(i,j)$，将 $i,j$ 都连向 $c_{\min}$ 连边即可。
- 若 $c_i\neq c_{\min_2},c_j\neq c_{\min_2}$，也可以不连 $(i,j)$，将 $i,j$ 均连向 $c_{\min_2}$ 即可。
- 否则 $c_i$ 和 $c_j$ 中必定有一个 $c_{\min}$ 和一个 $c_{\min_2}$，不妨假设 $c_i=c_{\min},c_j=c_{\min_2}$，由于 $w_i+w_j\le y$，所以有 $a_{\min}+a_{\min_2}\le y$，两个最小值连边。再连 $(c_{\min},j)$ 和 $(c_{\min_2},i)$ 即可。

所以我们每个点，只需要考虑向最小值和次小值连边即可。边数 $O(n)$。

统计答案的话一个连通块显然不能求出连通块所有颜色个数后再计算答案，可以预处理阶乘 $f_i$ 和阶乘的逆元 $g_i$，到达 $c_u$ 时考虑 $\text{ans}$ 的变化量，然后就随便做了。


[评测记录。](https://atcoder.jp/contests/agc012/submissions/38930104)

---

## 作者：pufanyi (赞：2)

我们考虑什么时候连个球能进行交换。

显然如果有三个球$a,b,c$，如果$a$与$b$能交换，$b$与$c$能交换，那$a$与$c$一定能通过$b$的“媒介”交换（$a$先于$b$交换，$b$与$c$交换，$a$与$b$交换）。

于是我们可以把$a,b,c$缩在同一个连通块里。

由于不同颜色与相同颜色交换条件是不一样的，我们先考虑相同颜色。

显然只需要用最小值做“媒介”即可。

然后我们考虑跨颜色交换。我们发现只需要用全局最小值做“媒介”，也就是说对于某个点，先通过该颜色最小值换到全局最小值，再通过全局最小值换到其他点。如果与全局最小值颜色相同，那我们就只能用次小值做媒介。

这样我们只需要记录某种颜色的最小值、全局最小值、全局次小值即可。

然后我们不难发现含有不同颜色的连通块只有一个，那就是全局最小值所在的连通块。

而只有一种颜色的连通块对答案没有影响。

于是我们只考虑最小值所在的连通块。首先我们找到全局最小值、全局次小值与每种颜色的最小值。如果他们都不能交换，那显然是凉了（答案为$1$）。我们对每种颜色数出能与该种颜色最小值交换的点数，然后用每种连通块的最小值与全局最小值（全局次小值）比较，求出这个联通块。我们发现就是求这个联通块排列方案数，其实就是可重集合排列。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 1000005;
const int inf = 0x3f3f3f3f;
const int mod = 1000000007;

int n, A, B;
int fac[maxn], inv[maxn];
int c[maxn], w[maxn], minci[maxn];
int Gs[maxn];

inline int pow(int a, int b)
{
	int ans = 1;
	for(; b; b >>= 1, a = (LL) a * a % mod)
		if(b & 1)
			ans = (LL) ans * a % mod;
	return ans;
}

inline int C(int n, int m)
{
	if(!n)
		return 1;
	if(m < n)
		return 0;
	return (LL) fac[m] * (LL) inv[m - n] % mod * (LL) inv[n] % mod;
}

int main()
{
	scanf("%d%d%d", &n, &A, &B);
	memset(minci, 0x3f, sizeof(minci));
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d", &c[i], &w[i]);
		minci[c[i]] = min(minci[c[i]], w[i]);
	}
	int minn = 0, minnn = 0;
	for(int i = 1; i <= n; ++i)
	{
		if(minci[i] < minci[minn])
		{
			minnn = minn;
			minn = i;
		}
		else if(minci[i] < minci[minnn])
			minnn = i;
	}
	int gss = 0;
	for(int i = 1; i <= n; ++i)
	{
		if(w[i] + minci[c[i]] <= A)
			w[i] = minci[c[i]];
		if(c[i] == minn && minci[minnn] + w[i] <= B)
		{
			Gs[c[i]]++;
			gss++;
		}
		if(c[i] != minn && minci[minn] + w[i] <= B)
		{
			Gs[c[i]]++;
			gss++;
		}
	}
	int ans = 1;
	fac[0] = 1;
	for(int i = 1; i <= n; ++i)
		fac[i] = (LL) i * fac[i - 1] % mod;
	inv[n] = pow(fac[n], mod - 2);
	for(int i = n - 1; ~i; --i)
		inv[i] = (LL) inv[i + 1] * (i + 1) % mod;
	for(int i = 1; i <= n; ++i)
	{
		if(Gs[i])
		{
			ans = (LL) ans * (LL) C(Gs[i], gss) % mod;
			gss -= Gs[i];
		}
	}
	printf("%d\n", ans);
	return 0;
}
```



---

