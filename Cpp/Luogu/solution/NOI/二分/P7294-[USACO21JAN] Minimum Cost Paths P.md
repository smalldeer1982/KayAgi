# [USACO21JAN] Minimum Cost Paths P

## 题目描述

Farmer John 的牧草地可以看作是一个$N×M$（$2≤N≤10^9, 2≤M≤2⋅10^5$）的正方形方格组成的二维方阵（想象一个巨大的棋盘）。对于 $x∈[1,N],y∈[1,M]$，从上往下第 $x$ 行、从左往右第 $y$ 列的方格记为 $(x,y)$。此外，对于每一个 $y∈[1,M]$，第 $y$ 列拥有一个代价 $c_y$（$1≤c_y≤10^9$）。

Bessie 从方格 $(1,1)$ 出发。如果她现在位于方格 $(x,y)$，则她可以执行以下操作之一：

-  如果 $y<M$，Bessie 可以以 $x^2$ 的代价移动到下一列（$y$ 增加一）。
- 如果 $x<N$，Bessie 可以以 $c_y$ 的代价移动到下一行（$x$ 增加一）。 

给定 $Q$（$1≤Q≤2⋅10^5$）个独立的询问，每个询问给定 $(x_i,y_i)$（$x_i∈[1,N],y_i∈[1,M]$），计算 Bessie 从 $(1,1)$ 移动到 $(x_i,y_i)$ 的最小总代价。

## 说明/提示

#### 样例 1 解释

输出以方阵形式表示如下：

```
    1  2  3  4
  *--*--*--*--*
1 | 0| 1| 2| 3|
  *--*--*--*--*
2 | 1| 5| 9|13|
  *--*--*--*--*
3 | 2|11|20|29|
  *--*--*--*--*
4 | 3|19|35|49|
  *--*--*--*--*
5 | 4|29|54|69|
  *--*--*--*--*
```

#### 测试点性质：

 - 测试点 1-3 满足 $N,M≤2000$。
 - 测试点 4-8 满足 $c_2>c_3>⋯>c_M$。
 - 测试点 9-15 满足 $N≤2⋅10^5$。
 - 测试点 16-20 没有额外限制。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
5 4
1 100 100 20
20
1 1
2 1
3 1
4 1
5 1
1 2
2 2
3 2
4 2
5 2
1 3
2 3
3 3
4 3
5 3
1 4
2 4
3 4
4 4
5 4```

### 输出

```
0
1
2
3
4
1
5
11
19
29
2
9
20
35
54
3
13
29
49
69```

# 题解

## 作者：CXY07 (赞：23)

## 保序回归入门题

> 题目链接：[P7294 [USACO21JAN] Minimum Cost Paths P](https://www.luogu.com.cn/problem/P7294)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/65/)**

题意：

> 现有 $n\times m$ 的一个矩形，第 $i$ 列有一个代价 $c_i$。如果现在你在 $(x,y)$，可以花费 $x^2$ 的代价到 $(x,y+1)$，或 $c_y$ 的代价到 $(x+1,y)$。

> 现有 $q$ 次询问，每次给定 $(x_i,y_i)$，求从 $(1,1)$ 到 $(x_i,y_i)$ 的最小代价。

> $2\le n\le 10^9,2\le m,q\le 10^5$。

本题解提供两种做法，第一种是 $\text{B}\red{\text{enq}}$ 给出的正解，还有一种是更为无脑的保序回归。~~由于作者很懒所以只写了第二种的代码~~

~~听神仙zzm说本质是一样的 代码还差不多~~

### Solution 1

> 本部分参照 $\text{B}\red{\text{enq}}$  在 $\text{USACO}$ 发布的官方题解。

令从 $(1,1)$ 到 $(x,y)$ 的最小代价为 $\text{ans}_y(x)$，那么能够发现，对于一个固定的 $y$，其函数值随着 $x$ 单调增且 $\text{ans}_{y}(x)-\text{ans}_{y}(x-1)\le \text{ans}_{y}(x+1)-\text{ans}_{y}(x)$。可以这样解释：

考虑从 $\text{ans}_y(x)$ 转移到 $\text{ans}_{y+1}(x)$ 的时候：

1. 先令 $\text{ans}_{y+1}(x)=\text{ans}_y(x)+x^2$。

2. 接着令 $\text{ans}_{y+1}(x)=\min(\text{ans}_{y+1}(x),\text{ans}_{y+1}(x-1)+c_y)$。

对于操作 $2$，相当于拿一条斜率为 $c_y$ 的直线去切函数图像，然后把过高的部分砍下来。同时，看到 $1$ 中 $\text{ans}_{y+1}(x)$ 上加了 $x^2$ 就可以大概发现 $\text{ans}_{y}(x)-\text{ans}_{y}(x-1)\le \text{ans}_{y}(x+1)-\text{ans}_{y}(x)$ 的规律。

那么现在可以使用一个栈来维护这样一个类似凸壳的东西，每次在栈里二分找到被直线给砍掉的位置，然后加入一个新点。至于每次的 $1$ 操作，也就是 $+x^2$，可以记录一个时间戳，然后和当前时间戳作差。

~~是的代码咕了~~

### Solution 2

> 本部分来自 [$\text{zxyhymzg}$](https://www.luogu.com.cn/user/89645#main) 考场想法。

~~萌新刚学保序回归 有锅请轻喷~~

令 $s_i$ 为我们在第 $i$ 行处走到 $(i,s_i)$，其中 $s_0=1$。那么显然有 $s_{i-1}\le s_i$，因为只能向右或者向下走。

计算一下代价，对于从 $(1,1)$ 到 $(x,y)$，$\forall s_i\le x$，代价为：

$$\sum_{i=1}^{y-1} s_i^2+(s_i-s_{i-1})\times c_i$$

后面的部分交换和式，把一项变成只和 $s_i$ 相关：

$$x\times c_y-c_1+\sum_{i=1}^{y-1} s_i^2+(c_i-c_{i+1})\times s_i$$

和式外面是常数，那么只要最小化和式内部。发现是二次函数，先写成顶点式：

$$(s_i-\dfrac{c_{i+1}-c_i}{2})^2-\dfrac{(c_{i+1}-c_i)^2}{4}$$

后面的也是常数，不管。变成最小化：

$$\sum_{i=1}^{y-1} (s_i-\dfrac{c_{i+1}-c_i}{2})^2$$

$\dfrac{c_{i+1}-c_i}{2}$ 是常数，那么就变成了经典的保序回归中的特殊的 $L_2$ 问题，在 $\text{IOI2018}$ 国家候选队论文集中有写到。

需要注意的是，现在对于一个固定的 $y$，发现其 $s_i$ 是固定的。而我们要求 $1\le s_i\le x$，实际上可能会不满足。可以发现将 $s_i$ 向 $[1,x]$ 取整，同时浮点数四舍五入即可。

那么同样的，在保序回归该特殊情况的贪心求解中，我们需要维护一个单调栈，因此对于向 $[1,x]$ 取整的操作可以在单调栈上二分，取整后一段区间的贡献是可以 $\mathcal{O}(1)$ 计算的。

至此即可解决本题，时间复杂度 $\mathcal{O}(n\log n)$，实际上好像效率海星？

$\text{Code:}$

```cpp
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define FILE
#define int long long
#define debug(x) cout << #x << " = " << x << endl
#define file(FILENAME) freopen(FILENAME".in", "r", stdin), freopen(FILENAME".out", "w", stdout)
#define LINE() cout << "LINE = " << __LINE__ << endl
#define LL long long
#define ull unsigned long long
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fst first
#define scd second
#define inv(x) qpow((x),mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define vec vector

const int MAXN = 2e5 + 10;
const int INF = 2e9;
const double PI = acos(-1);
const double eps = 1e-6;
//const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

struct Query {
	int x, y, id;
	Query(int _x = 0, int _y = 0, int _id = 0) : x(_x), y(_y), id(_id) {}
	bool operator < (const Query &b) const {return y < b.y;}
} q[MAXN];

int n, m, qs, top;
int c[MAXN], sum[MAXN], stk[MAXN];
//为了尽量避免浮点数计算，sum数组中先不将c_{i+1}-c_i除2
int Ans[MAXN], num[MAXN], val[MAXN];

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {a = a * 10 + (c ^ 48); c = getchar();}
	a *= f;
	return 1;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) {return read(x) && read(y...);}

double aver(int l, int r) {
	return 1. * (sum[r] - sum[l - 1]) / (2. * (r - l + 1));
}

int calc(int l, int r, int x) {
	if(l > r) return 0;
	return x * x * (r - l + 1) - x * (sum[r] - sum[l - 1]);
}

void Insert(int x) {
	while(top && aver(stk[top - 1] + 1, stk[top]) + eps > aver(stk[top] + 1, x)) top--;
	stk[++top] = x;
	num[top] = (int)round(aver(stk[top - 1] + 1, stk[top]));
	val[top] = val[top - 1] + calc(stk[top - 1] + 1, stk[top], num[top]);
}

signed main () {
#ifdef FILE
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	read(n), read(m);
	for(int i = 1; i <= m; ++i) read(c[i]);
	for(int i = 1; i <= m; ++i) sum[i] = sum[i - 1] + c[i + 1] - c[i];
	read(qs);
	for(int i = 1, x, y; i <= qs; ++i) {
		read(x), read(y);
		q[i] = Query(x, y, i);
	}
	sort(q + 1, q + qs + 1);
	int nowy = 0;
	for(int p = 1; p <= qs; ++p) {
		if(q[p].y == 1) {
			Ans[q[p].id] = (q[p].x - 1) * c[1];
			continue;
		}
		while(nowy + 1 < q[p].y) {
			nowy++;
			Insert(nowy);
		}
		Ans[q[p].id] = val[top] + q[p].x * c[q[p].y] - c[1];
		int L = 0, R = top, mid;
		while(L < R) {
			mid = (L + R + 1) >> 1;
			if(num[mid] > q[p].x) R = mid - 1;
			else L = mid;
		}
		Ans[q[p].id] += calc(stk[L] + 1, nowy, q[p].x) - (val[top] - val[L]);
		L = 1, R = top + 1;
		while(L < R) {
			mid = (L + R) >> 1;
			if(num[mid] <= 0) L = mid + 1;
			else R = mid;
		}
		Ans[q[p].id] += calc(1, stk[L - 1], 1) - val[L - 1];
	}
	for(int i = 1; i <= qs; ++i)
		printf("%lld\n", Ans[i]);
	return 0;
}

```

---

## 作者：KaguyaH (赞：12)

> 一张 $n \cdot m$ 的棋盘，点编号为 $([1, n], [1, m])$，起点位于 $(1, 1)$。
>
> 一步可以从 $(x, y)$ 走到 $(x, y+ 1)$，代价 $x^2$；可以从 $(x, y)$ 走到 $(x + 1, y)$，代价 $c_y$。
>
> $q$ 组询问，每次询问 $(1, 1) \rightsquigarrow (x_i, y_i)$ 所需最小代价。询问互相独立。
>
> $2 \le n \le 10^9$，$2 \le m \le 2 \times 10^5$，$1 \le c_i \le 10^9$，$1 \le q \le 2 \times 10^5$，$x_i \in [1, n]$，$y_i \in [1, m]$。各数据均为整数。

记 $f_y(x)$ 为 $(1, 1) \rightsquigarrow (x, y)$ 的代价。有 $f_1(x) = (x - 1)c_1$。显然 $f_1$ 单调增。

令 $g_y(x) = f_y(x) - f_y(x - 1)$。显然 $g_1$ 为常函数。

> 考虑由 $f_1$ 转移到 $f_2$ 的过程。
>
> 0. 令 $f_2(x) \leftarrow f_1(x) + x^2$（称这一操作为横更新）。
>
>    注意到，$x^2 - (x - 1)^2$ 是单调增的，故横更新后的 $f_2, g_2$ 单调增。
>
> 1. $x$ 由 $2$ 扫描至 $n$，令 $f_2(x) \leftarrow \min\{ f_2(x), f_2(x - 1) + c_2 \}$（称这一操作为纵更新）。
>
>    注意到，纵更新只会更新 $g_2 > c_y$ 的部分，也即 $f_2$ 的一个后缀，故纵更新后 $f_2, g_2$ 单调不降。

类似地，归纳可得，$\forall 1 \le y \le m$，$f_y, g_y$ 单调不降。

注意到横更新比较优美，而纵更新至多更新 $m$ 组。故考虑询问离线（按 $y$ 排序），并依次处理 $f_{1 \dots m}$。

记 $p_y(x)$ 为 $f_{1 \dots y}(x)$ 最后一次被纵更新时的位置。$p_y$ 可以分为 $O(m)$ 段，各段内值相同。

根据定义，$f_y(x) = f_{p(y, x)}(x) + (y - p_y(x))x^2$。

又有若 $\forall l \le x \le r, p_y(x) = p_y(l)$ 则 $\forall l \lt x \le r, g_{p(y, l)}(x) = g_{p(y, l)}(r)$。即：若 $[l, r]$ 中 $p_y$ 相等，则 $f_{p(y)}$ 在 $[l, r]$ 中成等差数列或一次函数（因为此时 $[l, r]$ 被更新，而被更新后初始状态应如此）。

于是可以类似维护凸壳地，维护各段 $p_y, f_{p(y)}$，转移与查询均可二分。

时间复杂度 $O(m \log nm + q \log m)$，空间复杂度 $O(m + q)$。

```cpp
namespace Main::Main {
  static constexpr const lu M(2e5), Q(2e5);
  class function {
    lu k; llu b;
  public:
    constexpr function(const lu k = lu(), const llu b = llu()): k(k), b(b) {}
    inline void err() const { fprintf(stderr, "k = %lu b = %llu\n", k, b); }
    inline constexpr llu operator()(const lu x) { return 1ull * k * x + b; }
  };
  struct query {
    lu x, y; lu id; llu ans;
    inline void in(const lu id) { io >> x >> y, this->id = id; }
    friend inline constexpr bool operator<(const query& a, const query& b)
    { return a.id < b.id; }
    static inline constexpr bool comp(const query& a, const query& b)
    { return a.y < b.y; }
  };
  struct func {
    function f; lu x, y;
    constexpr func(const function& f, const lu x, const lu y): f(f), x(x), y(y) {}
    // [x, infty) [y, infty)
    inline void err() const { f.err(), fprintf(stderr, "x = %lu y = %lu\n", x, y); }
    inline constexpr operator lu() { return x; }
    inline constexpr llu operator()(const lu _x, const lu _y)
    { return f(_x - x) + 1ull * (_y - y) * _x * _x; }
  };
  static lu n, m; static lu c[M + 1]; static lu q; static query r[Q];
  static vector<func> ans;
  static inline void insert(const lu y) {
    // fprintf(stderr, "insert %lu\n", y);
    ld l(-1), r(ans.size());
    while (r - l > 1) {
      const lu t((l + r) / 2), x(t + 1 == ans.size() ? n : ans[t + 1].x - 1);
      (
        (
          x == ans[t].x ?
            x == 1 || ans[t](x, y) - ans[t - 1](x - 1, y) < c[y] :
            ans[t](x, y) - ans[t](x - 1, y) < c[y]
        ) ? l : r
      ) = t;
    }
    // fprintf(stderr, "insert l = %ld, r = %ld\n", l, r);
    if ((lu)r == ans.size()) return;
    if ((r + 1ul == ans.size() ? n : ans[r + 1].x - 1) == ans[r].x) {
      const lu t(ans[r].x); ans.erase(ans.begin() + r, ans.end());
      ans.emplace_back(function(c[y], ans.back()(t - 1, y) + c[y]), t, y);
      return;
    } 
    lu p(max(ans[r].x - 1, 1ul)), q(r + 1ul == ans.size() ? n : ans[r + 1].x - 1);
    while (q - p > 1)
      (ans[r]((p + q) / 2, y) - ans[r]((p + q) / 2 - 1, y) < c[y] ? p : q) = (p + q) / 2;
    const func t(
      function(c[y], (q == ans[r].x ? ans[r - 1](q - 1, y) : ans[r](q - 1, y)) + c[y]),
      q, y
    );
    ans.erase(ans.begin() + r + (q != ans[r].x), ans.end()), ans.push_back(t);
  }
  static inline llu query(const lu x, const lu y)
  { return (*(upper_bound(ans.begin(), ans.end(), x) - 1))(x, y); }
  static inline void main() {
    io >> n >> m; for (lu i(1); i <= m; ++i) get(c[i]);
    get(q); for (lu i{}; i < q; ++i) r[i].in(i); sort(r, r + q, query::comp);
    ans.emplace_back(function(c[1], 0), 1, 1);
    for (lu i(1), j{}; ; ) {
      // for (const func& f: ans) f.err();
      while (j < q and r[j].y == i) r[j].ans = query(r[j].x, r[j].y), ++j;
      ; if (i == m) break; insert(++i);
    }
    sort(r, r + q); for (lu i{}; i < q; ++i) put(r[i].ans, '\n');
  }
}
```

---

## 作者：Hadtsti (赞：7)

~~今天模拟赛 T3 出了这道题，结果剩下时间太短正解没想完~~

### 题意简述

给出一个 $n\times m(1\le n\le 10^9,1\le m\le 2\times10^5)$ 的棋盘。设 $(i,j)$ 为第 $i$ 行第 $j$ 列的格子。从 $(1,1)$ 开始走，从 $(i,j)(1\le i<n,1\le j\le m)$ 走到 $(i+1,j)$ 代价为 $c_j$；从 $(i,j)(1\le i\le n,1\le j<m)$ 走到 $(i,j+1)$ 代价为 $i^2$。

再来 $q(1\le q\le 2\times 10^5)$ 次询问，每次给出坐标 $(x,y)$，求从 $(1,1)$ 走到 $(x,y)$ 的最小代价。

### 题目分析

由于是模拟赛题，我就按赛场上的思路写，因此从部分分开始。

- $n,m\le 2000$ 

简单的 DP，不用多说。预处理 $O(nm)$，询问 $O(1)$。

- $c_2>c_3>\cdots>c_m$

考虑一下这个性质的作用。其实就是说，在 $j\ge2$ 时应该先横着走到 $j=y$，再竖着走到 $i=x$。证明也很简单：如果在 $j\ge 2$ 时，存在有一步是从 $(i,j)$ 先走到 $(i+1,j)$ 再走到 $(i+1,j+1)$，则此时的代价是 $c_j+(i+1)^2>c_{j+1}+i^2$，即先走到 $(i,j+1)$ 再走到 $(i+1,j+1)$ 是更优的。所以通过调整，我们得到总的路径也是先横着走再竖着走。

那么就好处理了。我们只需要依据 $j=1$ 时是从哪一行开始横着走的就能算出最小代价。如果是从第 $i$ 行开始，则代价为 $(i-1)c_1+(y-1)i^2+(x-i)c_y$。为了求最优的 $i$，我们把它表示成以 $i$ 为主元的形式：$(y-1)i^2+(c_1-c_y)i+(xc_y-c_1)$。当 $y>1$ 时这是一个开口向上的二次函数，所以我们可以根据它的对称轴 $\displaystyle i=\frac{c_y-c_1}{2(y-1)}$ 找到最优的 $i$（将对称轴四舍五入之后对 $1$ 取 $\max$ 再对 $x$ 取 $\min$ 即可）；否则 $y=1$ 时，由上文的 DP 可知代价为 $(x-1)c_1$。时间复杂度 $O(m+q)$。

- $n\le 2\times 10^5$、$n\le 10^9$

其实受到上一部分的启发剩下的两个范围都可以做了。

注意到上一部分中的最优的 $i$ 取值实际上只和 $j=1$ 与 $j=y$ 有关（当然忽略范围问题导致的取 $\min/\max$ 问题），所以考虑把询问按 $y$ 分类离线处理。我们由刚刚的分析可得，每次路径出现“横走——竖走”的情况时（即 $(i,j)\rightarrow(i,j+\Delta j)\rightarrow(i+\Delta i,j+\Delta j)$ 时），应该尽可能使得开始向右走的 $i$ 接近 $\displaystyle\frac{c_{j+\Delta j}-c_j}{2\Delta j}$。为了 $i$ 最优且是递增的，我们可以采用单调栈维护。具体地，假设我们竖着走的列决策分别为 $j_1,j_2,\cdots,j_k$，我们就需要保证 $\displaystyle\forall 1\le l\le k-2,\frac{c_{j_{l+1}}-c_{j_l}}{2(j_{l+1}-j_l)}<\frac{c_{j_{l+2}}-c_{j_{l+1}}}{2(j_{l+2}-j_{l+1})}$。这只需要在每次插入需要查询的 $j=y$ 之前，不断检查栈顶和次栈顶决策是否满足最优的 $i$ 小于当前决策和栈顶决策算得的最优的 $i$ 即可，不满足就弹掉，最后 $j=y$ 入栈。至于计算每个具体 $(x,y)$ 的答案，只需要在维护栈的同时维护决策算得代价的前缀和，每次二分找到 $x$ 在哪两个决策算得的最优 $i$ 之间并记录对应答案即可。

时间复杂度 $O(q\log n+m)$，可以通过本题。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,a[200010],c[200010],stk[200010],top,ID;//stk[]:栈，top:栈顶，a[]:决策计算出的最优 i 位置，方便二分 
long long sum[200010],ans[200010];//sum[]:代价前缀和，ans[]:询问答案 
vector<pair<int,int> >Q[200010];
int P(int i,int j)
{
	return min(n,max(int(0.5*(double)(c[j]-c[i])/(j-i)+0.5),1));
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&c[i]);
	scanf("%d",&q);
	for(int x,y,i=1;i<=q;i++)
		scanf("%d%d",&x,&y),Q[y].push_back({x,i});//把询问按 y 分类，离线下来 
	for(auto i:Q[1])
		ans[i.second]=1ll*c[1]*(i.first-1);//特判 y=1 
	top=stk[1]=a[1]=1;//最初决策是 y=1 
	for(int i=2;i<=m;i++)
	{
		while(top>1&&a[top]>=P(stk[top],i))
			top--;//弹掉不合法的决策 
		int x=P(stk[top],i);
		sum[top+1]=sum[top]+1ll*(x-a[top])*c[stk[top]]+1ll*(i-stk[top])*x*x;//维护代价的前缀和 
		stk[++top]=i,a[top]=x; 
		for(auto t:Q[i])
		{
			ID=upper_bound(a+1,a+top+1,t.first)-a-1;//二分找到对应决策位置 
			ans[t.second]=sum[ID]+1ll*(t.first-a[ID])*c[stk[ID]]+1ll*(i-stk[ID])*t.first*t.first;//保存答案 
		}
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：Acoipp (赞：3)

给一种比较无脑的解法。

首先交换题目中 $x,y$ 的顺序，然后设 $f_{i,j}$ 表示走到 $(i,j)$ 这个点的最小代价。

转移有：

$$
f_{i,j} = \min(f_{i-1,j}+j^2,f_{i,j-1}+c_i)
$$

考虑经典套路，对 $f_{i,*}$ 作差分得到 $g_{i,j}=f_{i,j}-f_{i,j-1}$，即有等式 $\sum_{j=1}^k g_{i,j}=f_{i,k}$。

注意到 $f_{*,1}$ 和 $g_{*,1}$ 是常量，所以以下讨论中均不考虑这两项。

考虑一行一行地转移，首先 $f_{i,j}$ 继承 $f_{i-1,j}+j^2$，此时，$g_{i,j}=g_{i-1,j}+2j-1$。

然后对所有 $j$ 依次执行 $f_{i,j} = \min(f_{i,j},f_{i,j-1}+c_i)$，对应到 $g$ 上的操作就是如果 $g_{i,j} \ge c_i$，设 $x = g_{i,j}-c_i$，那么 $g_{i,j} \gets g_{i,j}-x$，$g_{i,j+1} \gets g_{i,j+1}+x$。

观察此过程，我们发现，$g_{i,j}$ 随着 $j$ 的增长而递增，证明可以使用归纳法，因此，我们有了下面的文字描述：

> 首先令 $g_{i,j}=g_{i-1,j}+2j-1$。
>
> 然后找到第一个大于等于 $c_i$ 的 $g_{i,j}$，令 $g_{i,j} \gets c_i（\Delta \gets g_{i,j}-c_i）$，然后 $g_{i,j+1} \gets \Delta+g_{i,j+1}$，以此类推。
>
> 最后 $g$ 的形态是前面若干个小于等于 $c_i$ 的值，后面全部变成 $c_i$。

于是，我们再次对 $g$ 做一次差分得到 $h$ 数组，那么对于 $h$ 来说，操作变成了：

> 首先令 $h_{i,j}=h_{i-1,j}+2$。
>
> 然后找到第一个 $j$ 满足 $\sum_{k=1}^j h_{i,k} \ge c_i$，令 $h_{i,j} = c_i-\sum_{k=1}^{j-1} h_{i,k}$，剩下的 $h_{i,p} \gets 0(p>j)$。

第一步可以使用区间加操作，第二步可以线段树上二分，最后一步是单点修改。

为了方便起见，线段树的每个节点可以维护两个值 $c0,c1$ 表示这里一共有 $c0$ 个值为 $c1$ 的 $h$，这样的话我们就可以不用动态开点了，常数也特别小。

最后查询离线下来，对 $h$ 求一个二阶前缀和就可以了。

时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
struct noede{ll x,y,id;}p[N];
bool cmp(noede a,noede b){return a.x<b.x;}
struct node{ll sum,sum1,cnt,tag;}tr[N<<2];
ll n,m,q,i,j,a[N],ans[N],root,top,f1;
inline void pushup(ll p,ll s,ll t){
	tr[p].cnt = tr[2*p].cnt+tr[2*p+1].cnt;
	tr[p].sum = tr[2*p].sum+tr[2*p+1].sum;
	tr[p].sum1 = tr[2*p+1].sum1+tr[2*p].sum1+tr[2*p].sum*tr[2*p+1].cnt;
}
inline void pushtag(ll p,ll c){tr[p].tag+=c,tr[p].sum+=tr[p].cnt*c,tr[p].sum1+=(1+tr[p].cnt)*tr[p].cnt/2*c;}
inline void pushdown(ll p){pushtag(2*p,tr[p].tag),pushtag(2*p+1,tr[p].tag),tr[p].tag=0;}
inline void add(ll x,ll c1,ll c2,ll s,ll t,ll p){
	if(s==t){
		tr[p].cnt=c1,tr[p].sum=c1*c2,tr[p].sum1=(1+c1)*c1/2*c2;
		return ;
	}
	if(tr[p].tag) pushdown(p);
	if(x<=(s+t)/2) add(x,c1,c2,s,(s+t)/2,2*p);
	else add(x,c1,c2,(s+t)/2+1,t,2*p+1);
	pushup(p,s,t);
}
inline pair<ll,ll> query(ll cnt,ll s,ll t,ll p){
	if(!cnt) return make_pair(0,0);
	if(s==t) return make_pair(cnt*(tr[p].sum/tr[p].cnt),(1+cnt)*cnt/2*(tr[p].sum/tr[p].cnt));
	if(tr[p].tag) pushdown(p);
	if(tr[2*p].cnt<cnt){
		pair<ll,ll> ans = query(cnt-tr[2*p].cnt,(s+t)/2+1,t,2*p+1); 
		ans.first += tr[2*p].sum,ans.second += tr[2*p].sum*(cnt-tr[2*p].cnt)+tr[2*p].sum1;
		return ans;
	}
	else return query(cnt,s,(s+t)/2,2*p);
}
inline pair<ll,ll> querys(ll x,ll s,ll t,ll p){
	if(s==t) return make_pair(tr[p].cnt,tr[p].sum/tr[p].cnt);
	if(tr[p].tag) pushdown(p);
	if(x<=(s+t)/2) return querys(x,s,(s+t)/2,2*p);
	else return querys(x,(s+t)/2+1,t,2*p+1);
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=m;i++) scanf("%lld",&a[i]);
	scanf("%lld",&q);
	for(i=1;i<=q;i++) scanf("%lld%lld",&p[i].x,&p[i].y),swap(p[i].x,p[i].y),p[i].id=i;
	sort(p+1,p+q+1,cmp);
	top=1,add(1,1,a[1],1,2e5,1);
	for(i=1,j=1;i<=m;i++){
		top++,add(top,1e9,0,1,2e5,1);
		for(;j<=q&&p[j].x==i;j++) ans[p[j].id]=f1*p[j].y+query(p[j].y-1,1,2e5,1).second;
		if(i!=m){
			f1++,pushtag(1,2);
			if(f1+querys(1,1,2e5,1).second>=a[i+1]){
				while(top) add(top,0,0,1,2e5,1),top--;
				top=1,add(1,1,a[i+1]-f1,1,2e5,1);
			}
			else{
				pair<ll,ll> las;
				while(f1+tr[1].sum>=a[i+1]&&top>=1){
					las = querys(top,1,2e5,1),add(top,0,0,1,2e5,1);
					top--;
				}
				ll delta = (a[i+1]-tr[1].sum-f1),num = (las.second==0?0:delta/las.second),rest = delta-num*las.second;
				if(num) top++,add(top,num,las.second,1,2e5,1);
				if(rest) top++,add(top,1,rest,1,2e5,1);
			}
		}
	}
	for(i=1;i<=q;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# P7294 题解



## 题目大意

> 在一个 $n\times m$ 的网格图上，$(x,y)\to(x+1,y)$ 代价为 $c_y$，$(x,y)\to (x+1,y)$ 代价为 $x^2$。
>
> $q$ 次询问 $(1,1)\to(x,y)$ 的最短路。
>
> 数据范围保证：$n\le 10^9,m,q\le 2\times 10^5$。



## 思路分析

注意到第二档部分分非常有趣，考虑从这一档部分分入手，可以发现最优路径一定只会在第 $1$ 和第 $y$ 列往下走，否则把这一段向下走的替换到第 $y$ 列一定不劣，因此只需要最开始在第 $1$ 列走到了哪一行。

假设整条路径为 $(1,1)\to(p,1)\to(p,y)\to(x,y)$，那么相应的代价应该是 $(p-1)\times c_1+(y-1)\times p^2+(x-p)\times c_y$。

容易发现这个代价是关于 $p$ 的二次函数 $f(p)=(y-1)\times p^2+(c_1-c_y)\times p+xc_y-c_1$，最小值在 $p=\dfrac{c_y-c_1}{2(y-1)}$  处取得，由于 $p$ 是整值，因此四舍五入到 $\left\lfloor\dfrac{c_y-c_1}{2(y-1)}\right\rceil$ 处（$\left\lfloor x\right\rceil$ 表示 $x$ 四舍五入到最近整数的结果）。

同理，根据上面一部分的启发，我们发现，对于任意两列 $y_1,y_2$ 我们应该在第 $\left\lfloor\dfrac{c_{y_1}-c_{y_2}}{y_1-y_2}\right\rceil$ 行转移，简记为 $P(y_1,y_2)$。

那么我们可以猜想，（忽略 $x$ 的限制）任何一组 $1\to y$ 的最优解一定是经过若干个 $y_1,y_2,\dots y_k$ ，其中从任意 $y_i\to y_{i+1}$ 均选择路径 $P(y_i,y_{i+1})$，因此可以考虑对 $y$ 离线，用单调栈维护当前转移路径上所有的 $y_i$，压入新的 $y$ 的时候按 $P(y_{i-1},y_i)\ge P(y_i,y)$ 更新整个单调栈即可，这一步的贪心策略的正确性可以用调整法证明。

接下来考虑横向这一维的限制，首先我们发现 $P(y_1,y_2)$ 首先要调整到 $[1,n]$ 之间，在计算的时候取一下 $\min$ 和 $\max$ 即可，而对于每次询问的 $x$ 限制，我们可以在单调栈上二分找到最后一段 $P(y_{i-1},y_i)\le x$ 的转移，而剩下的一定要尽可能靠近二次函数对称轴，即贴近 $x$ 更优，因此在维护单调栈的时候顺便维护到每个 $y_i$ 的距离。

时间复杂度 $\mathcal O(q\log m)$。



### 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll __int128
using namespace std;
const int MAXN=2e5+1;
int c[MAXN];
struct Query {
	int x,y,id;
	Query(int _x=0,int _y=0,int _id=0) { x=_x,y=_y,id=_id; }
};
vector <Query> que[MAXN];
ll ans[MAXN];
int stk[MAXN];
ll sum[MAXN];
int n,m,Q;
inline int transP(int a,int b) {
	if(a>b) swap(a,b);
	int k=round((double)(c[b]-c[a])/(double)(2*(b-a)));
	k=max(k,1ll),k=min(k,n);
	return k;
}
inline void write(ll x) {
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
signed main() {
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;++i) scanf("%lld",&c[i]);
	scanf("%lld",&Q);
	for(int i=1;i<=Q;++i) {
		int x,y;
		scanf("%lld%lld",&x,&y);
		que[y].push_back(Query(x,y,i));
	}
	for(auto q:que[1]) ans[q.id]=c[1]*(q.x-1);
	int top=1; stk[top]=1,sum[top]=0;
	for(int i=2;i<=m;++i) {
		while(top>1&&transP(stk[top-1],stk[top])>=transP(stk[top],i)) --top;
		int a=transP(stk[top],i);
		if(top==1) sum[top+1]=sum[top]+(ll)(a-1)*(ll)c[stk[top]]+(ll)(i-stk[top])*(ll)a*(ll)a;
		else {
			int a0=transP(stk[top-1],stk[top]);
			sum[top+1]=sum[top]+(ll)(a-a0)*(ll)c[stk[top]]+(ll)(i-stk[top])*(ll)a*(ll)a;
		}
		stk[++top]=i;
		for(auto q:que[i]) {
			int L=2,R=top,res=1;
			while(L<=R) {
				int mid=(L+R)>>1;
				if(transP(stk[mid-1],stk[mid])<=q.x) L=mid+1,res=mid;
				else R=mid-1;
			}
			int a=(res==1)?1:transP(stk[res-1],stk[res]);
			ans[q.id]=sum[res]+(ll)(i-stk[res])*(ll)q.x*(ll)q.x+(ll)(q.x-a)*(ll)c[stk[res]];
		}
	}
	for(int i=1;i<=Q;++i) write(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：Jeefy (赞：2)

所以说它本身是一个保序回归经典问题，但是我用另一种方法将它做了出来。

首先看到朴素的 DP：

$$
\begin{aligned}
f_{i, j} = \min(f_{i - 1, j} + C_j, f_{i, j - 1} + i^2)
\end{aligned}
$$

考虑到 $j$ 这一维很小，考虑是否能够对其做一个扫描线。

那么首先修正转移的顺序，对于列 $j$，我们先统一令 $f_{i, j} = f_{i, j - 1} + i^2$，也就是先从上一个版本转移过来。

再考虑列内转移 $f_{i, j} = \min(f_{i, j}, f_{i - 1, j} + C_j)$。

发现如果可以转移，当且仅当 $f_{i, j} > f_{i - 1, j} + C_j$，稍微移项，写成 $f_{i, j} - f_{i - 1, j} > C_j$ 的形式，发现这是差分的形式，考虑将转移变成差分然后维护。

令 $g_{i, j} = f_{i, j} - f_{i - 1, j}$，那么可知 $f_{i, j} = f_{i, 1} + \sum_{2 \le k \le i} g_{k, j}$，如果我们可以在扫描线时维护这个差分，那么求答案就变成了一个简单的前缀和问题。

考虑转移如何转移，我们对于列 $g_i$ 统一执行 $g_{i, j} \leftarrow g_{i, j - 1} + i^2 - (i - 1)^2 = g_{i, j - 1} + 2i - 1$，发现相当于全局加一个一次函数。

然后对于列内的转移，相当于对于全局取 $\min C_i$，由于我们需要求前缀和，所以这个问题是不可做的，但是我们可以通过性质绕开它。

考虑我们可以归纳证明 $g_i$ 是一个不降的函数，那么对于全局取 $\min C_i$ 就可以变为对于一个后缀赋值的问题。

在 $i = 1$ 时，有 $g_{1, j} = C_1$，在进行第一步转移时，我们加上的是一个单增函数（并且没有负数），那么转移后的 $g_{1, j}$ 仍然是一个不降函数，并且显然的全局取 $\min C_2$ 后仍然不增。

![](https://gitlab.com//jeefies/image-repo/uploads/17508a57675a3dc9ffd34c0a12a739ff/202312191015680.png)

类似的，我们可以证明对于任意 $i$ 转移后仍然是一个不降的函数，那么我们就可以将全局取 $\min C_i$ 变为区间赋值问题。

那么我们就将问题转化为如下对于一个序列上的问题：

- 全局加一次函数
- 找到第一个 $> C_i$ 的位置，并对找到的后缀赋值
- 查询前缀和

这可以利用动态开点线段树用 $O(m \log n)$ 的时空代价完成，于是我们就搞定了这道题。

代码链接：[云剪切板](https://www.luogu.com.cn/paste/52wc1znb)

---

## 作者：AbioAg (赞：2)

模拟赛题，赛时正解没调出来，人麻了。

考虑原先形式，再观察 $n$ 的范围，发现横着走的情况如果每步都算贡献很麻烦，而对于每一行，$x$ 为定值，因此如果不换行，可以 $O(1)$ 求出，而换行的话，发现可以方便的维护一个增量,设目标点为 $(X,Y)$，当前点为 $(x,y)$，则如果当前要换行，代价为 $\Delta x=(2x+1)(Y-y)$，而初始只需要令答案为 $Y-1$ 即可，而不难发现我们要换行 $n-1$ 次，且每次 $y$ 单调不降。

则题意转化为：
选出 $n-1$ 个每行的下降点  $(i,y_i)$ 满足最小化 $\sum c_{y_i}+(2i+1)(Y-y_i)$。

再变换一下形式如下：
构造一个长度为 $n-1$，值域为 $Y$ 的单调不降序列 $a$，最小化 $c_{a_i}+(2i-1)\times (Y-a_i)$。

注意到带 $Y$ 的部分为常量，提取出来，所以就是最小化 $c_{a_i}-(2i-1)a_i$，我们发现如果把 $-(2i-1)$ 看做一个斜率 $k$，由于 $a_i$ 值域为 $m$，则能够构建一个关于 $a_i$ 的凸包，每个点为 $(t,c_t)$，由于 $k=-(2i-1)$ 是单调递减的，我们发现用 $k$ 去切凸包，得到的 $a_i$ 恰好是单调不降的！

我们发现这是具有决策单调性的，保留在凸包上的点都能够支配一段连续的横坐标。

这样我们就只需要单调栈维护每个点能支配的区域，并计算出代价的前缀和，同时记录此点的最优决策点 $a_i$。

对于询问，我们实际限制的是 $a_i$ 的值域最大为 $Y$，只要二分到第一个比 $Y$ 小的最优决策点 $p$，取其前缀和，剩余部分代价则一定均取 $a_i=p$ 最优，代价可以 $O(1)$ 计算。

复杂度 $O(m+q\log m)$。

---

## 作者：Gauss0320 (赞：2)

# Description

给你一张 $n\times m$ 的网格图，从 $(1,1)$ 出发，有如下两种移动方式：

1. 从 $(x,y)$ 移动到 $(x,y+1)$，代价为 $x^2$。

2. 从 $(x,y)$ 移动到 $(x+1,y)$，代价为 $c_y$。

现在给出 $q$ 组询问 $(x,y)$，求从 $(1,1)$ 走到 $(x,y)$ 的最小代价。

# Constraint

见原题

# Solution

首先感谢 [@CXY07](https://www.luogu.com.cn/user/53489)，他教会了我这道题的解法。

设在第 $i$ 列我们从 $(s_{i-1},i)$ 移动到了 $(s_i,i)$（$s_0=0$），那么总代价为
$$\sum_{i=1}^{y-1}[s_i^2+(s_i-s_{i-1})c_i]+(x-s_{y-1})c_y$$

作一些变形可得
$$
\begin{aligned}
\sum_{i=1}^{y-1}[s_i^2+(s_i-s_{i-1})c_i]+(x-s_{y-1})c_y&=\sum_{i=1}^{y-1}\left[s_i^2+s_i(c_i-c_{i+1})\right]+(xc_y-c_1)\\
&=\sum_{i=1}^{y-1}\left(s_i-\frac{c_{i+1}-c_i}{2}\right)^2-\sum_{i=1}^{y-1}\frac{(c_i-c_{i+1})^2}{4}+(xc_y-c_1)
\end{aligned}
$$
忽略常数项，我们发现要做的仅仅是
$$\begin{aligned}&\operatorname{minimize }\sum_{i=1}^{y-1}\left(s_i-\frac{c_{i+1}-c_i}{2}\right)^2\\&\operatorname{s.t. }s_i\le s_{i+1},1\le s_i\le x,s_i\in \mathbb N_{+}\end{aligned}$$
这是经典的保序回归问题，翻阅 2018 年的国家预选队论文即可知道做法。

并且注意到 $\dfrac{c_{i+1}-c_i}{2}$ 这种差分形式的前缀和非常好维护。

---

## 作者：Mirasycle (赞：1)

很显然的整体 dp 的形式。

我们设 $dp_{i,j}$ 表示考虑了前 $i$ 列，走到第 $j$ 行的代价。

$$dp_{i,j}=\min(dp_{i-1,j}+j^2,dp_{i,j-1}+c_i)$$

因为贡献函数 $j^2$ 是下凸函数，可以猜测，固定 $i$，$dp_{i,j}$ 是一个下凸函数。也就是 $dp_{i,j}$ 的差分数组单调不减。

每次从 $i-1\to i$，对于 $dp_{i}$ 先是直接继承 $dp_{i-1}$，然后对于每个位置打上一个 $j^2$ 的标记。

现在考虑列内的转移。上面说了 $dp_{i,j}$ 的差分数组单调递增，而行内观察形式其实就是差分数组对于 $c_i$ 进行一个 chkmin。由于差分数组单调，于是我们直接二分找到变化点进行修改即可。

由于第二维是 $O(n)$ 的，我们不能直接维护。考虑使用单调栈维护转折点。转折点之间都是一条一次函数。

直接的思路是维护一个差分数组，这样子非常方便更新。但是由于不是问 $(1,1)\to (n,m)$ 的代价，而是中间有 $q$ 个询问，我们不可能每次询问都累加一次差分数组吧。

于是考虑维护 $f_i(x)=(i-j)\times x^2+c_j\times x-b$ 的形式。这个 $(i-j)\times x^2$ 就是上面说的一个 $+x^2$ 的 tag，其中 $j$ 表示上次该点被 chkmin $c_j$ 更新的时间点 $j$。由于上次是被 $c_j$ 更新，所以就是形式就是 $val_p+c_j\times (x-p)$，其中 $p$ 表示前面一个断点，拆开就是 $c_j\times x+b$。综上所述，我们只需要在单调栈中对于每个断点维护一个三元组 $(x,j,b)$ 即可。

每次修改由于我们不是直接维护的差分数组，所以可以直接用 $f_i(x)-f_i(x-1)$ 得到差分值。对于后缀推平，我们可以直接从后缀开始不断 check 并且 `pop`，由于每列只会进队列 $O(1)$ 个的点，所有点也只会被删一次，所以复杂度均摊是正确的。`pop` 到满足题意之后要二分寻找一下，然后插入新的端点。

每次询问就是离线处理，二分找到询问点在栈中哪两个端点之中，然后求值。

时间复杂度 $O((m+q)\log n)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
ll V(int x){ return 1ll*x*x; } int c[maxn];
struct node{
	int x,tim; ll deta;
	bool operator < (const node &rhs) const { return mp(x,tim)<mp(rhs.x,rhs.tim);}
	ll get(int x,int t){ return V(x)*(t-tim)+1ll*x*c[tim]+deta; }
}st[maxn]; int top=0;
int n,m,Q; vector<pair<int,int> > q[maxn]; ll ans[maxn];
int find(int x){  return upper_bound(st+1,st+1+top,(node){x+1,0,0})-st-1; }
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>c[i];
	cin>>Q;
	for(int i=1;i<=Q;i++){
		int x,y; cin>>x>>y;
		if(n==1) cout<<y<<"\n";
		q[y].pb(x,i);
	}
	if(n==1) return 0;
	for(int i=1;i<=m;i++){
		if(i==1) st[++top]=(node){1,1,-c[1]};
		else{
			while(top){
				int x=st[top].x;
				ll v1=st[top].get(x,i);
				ll v2=st[top].get(x+1,i);
				if(v1+c[i]<v2){ top--; continue; }
				if(st[top].get(n-1,i)+c[i]>=st[top].get(n,i)) break;
				int l=x+1,r=n-1;
				while(l<r){
					int mid=(l+r)>>1;
					if(st[top].get(mid,i)+c[i]<st[top].get(mid+1,i)) r=mid;
					else l=mid+1;
				}
				v1=st[top].get(l,i);
				st[++top]=(node){l,i,v1-1ll*l*c[i]};
				break;
			}
			if(!top) st[++top]=(node){1,i,i-1-c[i]};
		}
		for(auto z:q[i]) ans[z.se]=st[find(z.fi)].get(z.fi,i);
	}
	for(int i=1;i<=Q;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：Anonymely (赞：1)

很套路的题。

首先有朴素的 $n^2$ dp。

对于一列同时考虑，一列变化时会加上一个二次函数，而还有 $f_{j}=\min(f_j,f_{j-1}+c_{j-1})$，本质是将斜率大于 $c$ 的点全部推到 $c$ 这条直线上，归纳可得 $dp$ 下凸。

暴力一点是直接平衡树维护，但是不太好做加二次函数的操作。考虑每次推斜线一定是推一段后缀，于是用一个单调栈维护转折点即可。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, T y) {x = min(x, y);}

const int N = 2e5 + 5;
int n, m, q;
int c[N];
ll ans[N];
vector < pair <int, int> > ask[N];
struct Node {
    ll k, x, t, b;
    Node () {}
    Node (ll _k, ll _x, ll _t, ll _b) {k = _k, x = _x, t = _t, b = _b;}
} stk[N];
int top;

ll cal(int x, int now) {
    int p = lower_bound(stk + 1, stk + top + 1, x, [&](Node u, int v) {return u.x <= v;}) - stk - 1;
    return stk[p].b + (now - stk[p].t) * x * x + (x - stk[p].x) * stk[p].k;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> c[i];
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        ask[y].push_back({x, i});
    }
    stk[++top] = Node(c[1], 1, 1, 0);
    for (int i = 1; i <= m; i++) {
        if (i != 1) {
            int l = 2, r = 1e9, ans = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (cal(mid, i) - cal(mid - 1, i) >= c[i]) ans = mid, r = mid - 1;
                else l = mid + 1;
            } 
            if (ans != -1) {
                while (top && stk[top].x >= ans) top--;
                ll v = cal(ans - 1, i) + c[i];
                stk[++top] = Node(c[i], ans, i, v);
            }
        }
        for (auto [x, id] : ask[i]) ans[id] = cal(x, i);
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    QwQ01AwA;
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

在一个 $n\times m$ 的网格上，位于 $(i,j)$ 格子上时，有两种走法：

- 花费 $c_j$ 的代价走到 $(i+1,j)$。

- 花费 $i^2$ 的代价走到 $(i,j+1)$。

多次询问从 $(1,1)$ 到 $(x_i,y_i)$ 的最小代价。

## 题目分析

我们尝试把这两种贡献合并到一个式子里。对于每一行，都是从一个纵坐标进入，然后向右走一段，然后再从一个纵坐标进入下一行。

我们设每一行 $i$ 进入下一行 $i+1$ 时的纵坐标设为 $p_i$，则显然 $p_i$ 单调不降，且 $p_x$ 视作 $y$ 但并不进入下一行，则代价相当于：

$\sum\limits_{1\le i\le x}(p_i-p_{i-1})i^2+\sum\limits_{1\le i<x}c_{p_i},p_0=1$。

把式子拆开来，合并 $p_i$ 的系数（这时候就可以惊奇的发现 $i^2$ 这个二次系数被消成了一次），代价可以转化为：

$x^2y-1+\sum\limits_{1\le i<x}(c_{p_i}-p_i(2i+1))$。

这样后面只用处理后面这一坨的最小值了，但这时候还有着 $p_i\ge p_{i-1}$ 的限制。而眼尖的同学已经发现 $-p_i(2i+1)+c_{p_i}$ 是关于 $i$ 的 $m$ 个一次函数 $f(x)=-2p_ix+c_{p_i}-p_i$。这个函数随着 $p_i$ 的增大，斜率也会增大，然后把图像画出来（呃呃呃这个凑合看吧）：

![](https://cdn.luogu.com.cn/upload/image_hosting/lveb7dxq.png)

彩色的部分表示这些函数的最小值，这构成斜率递增的段，所以 $x$ 增长时，$f(x)$ 的最小值对应的函数的斜率不减，所以对应的 $p_i$ 自然不减，所以我们只要对这个彩色的函数求个前缀和就行了。

这下黑题就变成黄题了，我们直接按照 $y$ 扫描线，用单调栈维护这个彩色函数的段以及前缀和，然后二分查找一下 $x$ 对应的是哪一段就可以了。

总复杂度 $O(q\log m+m)$，瓶颈在于二分。

```cpp
// ubsan: undefined
// accoders
#include<bits/stdc++.h>
#define ll long long
#define int ll 
#define L xd[x].l
#define R xd[x].r
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for (int i = h[x], y = to[i]; i; i = nxt[i], y = to[i])
#define E(x) for (auto y : p[x])
#define Pi pair<int, int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=1e18;
using namespace std;
int n,m,c[N],q;
struct node{
	int k,b;
}a[N];
inline int getmet(int i,int j){
	if(i==0)return 1;
	return ceil((double)(a[j].b-a[i].b)/(double)(a[i].k-a[j].k));

} //计算交点 
inline int sum(int x,int l,int r){
	return (r-l+1)*(l+r)/2*a[x].k+(r-l+1)*a[x].b;
} //计算 [l,r]交Z 在函数的区间和 
inline int get(int x,int id){
	return a[id].k*x+a[id].b;
}
struct nod{
	int x,y,id;
}qr[N];
inline bool cmp(nod a,nod b){
	return a.y<b.y;
}
int s[N],tp,p[N],out[N];
inline int find(int x){
	int l=1,r=tp,ans=1;
	while(l<=r)if(getmet(s[mid-1],s[mid])<=x)ans=mid,l=mid+1;
	else r=mid-1;
	return ans;
}
signed main(){		
	n=read(),m=read();
	repm(i)c[i]=read(),a[i].k=-2*i,a[i].b=c[i]-i;
	q=read();
	rep(i,1,q)qr[i].x=read(),qr[i].y=read(),qr[i].id=i;
	sort(qr+1,qr+q+1,cmp);
	int l=1;
	repm(i){
		while(tp){
			int pos=getmet(s[tp-1],s[tp]);
			if(get(pos,i)<=get(pos,s[tp]))tp--;
			else break;
		}
		s[++tp]=i;
		if(tp>1)p[tp-1]=p[tp-2]+sum(s[tp-1],getmet(s[tp-2],s[tp-1]),getmet(s[tp-1],s[tp])-1);
		while(l<=q&&qr[l].y==i){
			out[qr[l].id]=qr[l].x*qr[l].x*qr[l].y-1;
			if(qr[l].x>1){
				int ps=find(qr[l].x-1);
				out[qr[l].id]+=p[ps-1]+sum(s[ps],getmet(s[ps-1],s[ps]),qr[l].x-1);
			}
			l++;
		}
	}
	rep(i,1,q)pf(out[i]),putchar('\n');
	return 0;
}
```



---

## 作者：Leasier (赞：1)

考虑逐行拆贡献，设我们在第 $i$ 行走到了 $x_i$ 再往下走，则花费为：

- $\displaystyle\sum_{i = 1}^x (i^2(p_i - p_{i - 1}) + [i < x] c_{p_i})$，其中 $p_0 = 1, p_x = y$，且 $p_i$ 单调不降。

考虑把贡献分给每个 $p_i$，可得：

- $yx^2 + \displaystyle\sum_{i = 1}^{x - 1} (c_{p_i} - p_i(2i + 1)) - 1$。

考虑把贡献当成一次函数 $f_i(x) = c_i - i(2x + 1)$，则当 $i$ 增大时，斜率单调递增，则只要我们每次选择一个 $p_i$ 使得 $f_{p_i}(i)$ 最小，就可以满足 $p_i$ 单调不降的限制。

考虑把 $f_i(x)$ 的图像画在坐标系中，则我们每次的选择构成了一个**下凸壳**。

考虑把 $y$ 离线下来，从 $1$ 到 $n$ 用单调栈维护当前凸壳，处理当前 $y$ 的所有询问时在凸壳上二分即可。时间复杂度为 $O(n + q \log n)$。

注意需要把所有在 $x \geq 1$ 时都不可能比当前 $f_y(x)$ 优的项从单调栈里扔掉。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;

int top = 0;
int c[200007], stk[200007], r[200007];
ll sum[200007], ans[200007];
vector<pair<int, int> > v[200007];

inline double intersection(int x, int y){
	return (1.0 * (c[x] - c[y]) / (x - y) - 1) / 2.0;
}

inline ll calc(int x, int l, int r){
	return (ll)c[x] * (r - l + 1) - (ll)x * (r - l + 1) * (r + l + 1);
}

inline void update(int x){
	sum[x] = sum[x - 1] + calc(stk[x], r[x - 1] + 1, r[x]);
}

int main(){
	int n, m, q;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++){
		scanf("%d", &c[i]);
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		v[y].push_back(make_pair(i, x));
	}
	for (int i = 1; i <= m; i++){
		int size = v[i].size();
		while (top > 1 && intersection(i, stk[top]) <= intersection(stk[top], stk[top - 1])) top--;
		while (top > 0 && intersection(i, stk[top]) < 1.0) top--;
		if (top > 0){
			r[top] = intersection(i, stk[top]);
			update(top);
		}
		top++;
		stk[top] = i;
		r[top] = 1e9;
		update(top);
		for (int j = 0; j < size; j++){
			int x = v[i][j].second, pos = lower_bound(r + 1, r + top + 1, x - 1) - r - 1;
			ans[v[i][j].first] = (ll)i * x * x + (sum[pos] + calc(stk[pos + 1], r[pos] + 1, x - 1)) - 1;
		}
	}
	for (int i = 1; i <= q; i++){
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

有一个显然易见的 $O(N^2)$ DP:

$$dp_{i,j} = \min(dp_{i-1,j}+c_j,dp_{i,j-1}+i^2)$$

**我们见到平方状态的 DP，可以像如 CSP-S2024 T3 一样直接使用数据结构维护整个 $dp_{i,*}$。即移动第一维，整体维护第二维**。

由于 $n \le 10^9$，移动第一维是不现实的，而且 $a_i \leftarrow a_i+c_i$ 与 $a_i \leftarrow \min(a_i,a_{i-1}+j^2)$ 也看起来不好维护，只能暴力。

移动第二维则是 $a_i \leftarrow a_i+i^2$ 与 $a_i \leftarrow \min(a_i,a_{i-1}+c)$ 之类的状物了。起码只需要进行 $O(m)$ 次操作了。但是这看起来还是不好维护啊。

**平方与 $\min$ 之类的东西结合出现的时候，我们就可以想一下维护的东西是不是凸的。**

我们下文记 $dp_{i,j}$ 为 $a_i$。很幸运，它是下凸的，即 $a_{i+1}-a_i \ge a_i-a_{i-1}$。

接下来所说的差分数组与二阶差分数组都从 $2$ 开始标号。

证明：首先其最开始的差分数组为 $\{c_1,c_1,c_1,\dots\}$，是凸的。

其次，$a_i \leftarrow a_i+i^2$ 带来的结果是 $b_i \leftarrow b_i+2i-1$，显然 $i$ 的增加量小于 $i+1$ 的增加量，还是凸的。

$a_i \leftarrow \min(a_i,a_{i-1}+c)$ 的本质就是找到第一个差分数组中 $>c$ 的，给其及其后全部推平成 $c$，还是凸的。

现在问题就是全局加 $3,5,7,9,\dots$，以及后缀推平与求前缀和。

发现还是不好做，考虑维护二阶差分数组。具体地，我们定义 $h_i$，满足 $a_i-a_{i-1} = \sum \limits_{j=2}^i h_j+t$（$t$ 表示当前进行过几轮更新）

此时修改就变成了全局 $+2$，以及查询第一个前缀和大于 $c$ 的位置，将其修改为 $c-\sum \limits_{j=2}^{i-1}h_j-t$，并将后面全部置为 $0$。查询就是求一段前缀的二阶前缀和。

全局 $+2$ 可以打标记维护。发现修改操作最多会新添 $O(1)$ 个值域连续段，于是直接维护值域连续段即可。你可以通过维护值域连续段的前缀和与二阶前缀和来维护操作。

时间复杂度 $O((m+q) \log m)$。

---

## 作者：Purslane (赞：0)

# Solution

设 $dp_{x,y}$ 表示，从 $(1,1)$ 走到 $(x,y)$ 的代价。

则有：

$$
dp_{x,y} = \min\{dp_{x,y-1}+x^2,dp_{x-1,y}+c_y\}
$$

动态改变 $y$，维护 $dp_{*,y}$ 的变化。

首先，默认走第一条，也就是**默认全局加下标的平方**。

使用数学归纳法容易发现，$dp_{*,y}$ 始终是凸的。所以你加上下标的平方之后还是凸的。

这时候引入第二种操作。发现只需要找到差分数组第一个 $\ge c_y$ 的位置，将他之后的位置赋值为 $c_y$。

直观的想法是使用线段树维护这个过程。但是考虑值域很大，要动态开点，会爆空间。

注意每次都是给一段后缀赋值，所以我们可以将差分数组拆成若干段，每一段的值都是 $c_y + (t-y)(2x+1)$ 型，其中 $t$ 是我们当前考虑到的列的标号。

直接维护所有端点即可，只需要一个栈，在上面二分、求和即可。

我比较懒，为了避免细节直接先二分再弹栈，所以是 $O(n\log^2 n)$ 的。。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,q,c[MAXN],tot,id[MAXN],t[MAXN],val[MAXN],pre[MAXN],ans[MAXN];
int sum(int l,int r) {return (r+1)*(r+1)-l*l;}
int calc(int pos,int qt) {
	if(pos==0) return 0;
	int qid=upper_bound(t+1,t+tot+1,pos)-t-1;
	return qt*sum(1,pos)+pre[qid-1]+c[id[qid]]*(pos-t[qid]+1)-id[qid]*sum(t[qid],pos);
}
int Calc(int pos,int qt) {
	int qid=upper_bound(t+1,t+tot+1,pos)-t-1;
	return c[id[qid]]+(qt-id[qid])*(2*pos+1);
}
vector<pair<int,int>> qr[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) cin>>c[i];
	cin>>q;
	ffor(i,1,q) {int x,y;cin>>x>>y,qr[y].push_back({x,i});}
	t[++tot]=1,id[tot]=1;
	for(auto pr:qr[1]) ans[pr.second]=calc(pr.first-1,1);
	ffor(i,2,m) {
		if(c[id[tot]]+(i-id[tot])*(2*n-1)>c[i]) {
			int ans=-1,l=1,r=n-1;
			while(l<=r) {
				int mid=(l+r)>>1;
				if(Calc(mid,i)>c[i]) ans=mid,r=mid-1;
				else l=mid+1;
			}
			while(tot&&t[tot]>=ans) tot--;
			if(tot==0) ++tot,t[tot]=1,id[tot]=i,pre[tot]=0;
			else pre[tot]=pre[tot-1]+c[id[tot]]*(ans-t[tot])-id[tot]*sum(t[tot],ans-1),++tot,t[tot]=ans,id[tot]=i,pre[tot]=0;
		}
		for(auto pr:qr[i]) ans[pr.second]=calc(pr.first-1,i)+i-1;
	}
	ffor(i,1,q) cout<<ans[i]<<'\n';
	return 0;
}
```

---

