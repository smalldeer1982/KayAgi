# [BalticOI 2017] Plus Minus

## 题目背景

物理学家马修正在研究硅基矩形微芯片的量子电动力学。

## 题目描述

这一块芯片的大小为 $n \times m$ ，可以分成 $n \times m$ 个电子。  
我们都知道电子的状态只有正电 `+` 和负电 `-`。  
所以，每一个电子都只有一个状态，`+` 或者 `-`。  
马修不知道每个电子的状态，但他可以进行 $k$ 次测量。  
第 $i$ 次测量他可以得到 $(y_i,x_i)$ 这个电子的状态 $s_i$。  
（$s_i$ 是 `+` 或者 `-`）  
马修还知道，在任意一个 $2\times2$ 的大小的电子块中，拥有 `+` 的电子和拥有 `-` 的电子数量相等。  
然后他找到了您，想让您给出有多少种电子排列的形式满足测量的结果和上述要求。  
答案对 $10^9+7$ 取模。

## 说明/提示

#### 样例说明

对于样例 $1$，有以下 $2$ 种情况：
```
+-+-
+-+-
```
和
```
+-+-
-+-+
```

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（12 pts）：$n,m \le 5$。
- Subtask 2（42 pts）：$n,m \le 1000$。
- Subtask 3（46 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,m \le 10^9$，$0 \le k \le 10^5$，$1 \le y_i \le n$，$1 \le x_i \le m$。

#### 说明

**翻译自 [BOI 2017 D2](https://boi.cses.fi/files/boi2017_day2.pdf) T3 Plus Minus。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。

## 样例 #1

### 输入

```
2 4 4
+ 1 1
- 1 2
+ 1 3
- 1 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3 3
- 2 1
+ 2 3
+ 3 3```

### 输出

```
0```

# 题解

## 作者：Tweetuzki (赞：9)

> 一个 $n \times m$ 的 $01$ 矩阵，其中 $k$ 个位置的值给定。这个矩阵满足性质：对于每个 $2 \times 2$ 的小子矩阵中 $0$ 与 $1$ 的个数相同。求满足条件的矩阵数量，对 $10 ^ 9 + 7$ 取模。
> 
> $n, m \le 10 ^ 9$，$k \le 10 ^ 5$。

一个显然的事实是：确认了第一行和第一列，就能推得所有矩阵。考虑如何确定第一行和第一列。

结论：一个矩阵是一个合法的矩阵，当且仅当其满足，要么第一行是 $010101\ldots$ 或 $101010\ldots$ 这样 $01$ 交错的；要么第一列是这样 $01$ 交错的。

证明可以画图，考虑一个这样的矩阵，使得其第一行和第一列都不是 $01$ 相间的。那么可以找出一个位置 $i$，满足第 $i$ 行的第一个数和第 $i + 1$ 行的第一个数相同（即第一列上连续的两个相同的数），为了方便，都假定为 $1$。我们考虑这两行的情况：

$$
\begin{matrix}
1 \quad 0 \quad 1 \quad \cdots \quad 0 \quad 1 \quad 1 \quad 0 \quad 1 \quad \cdots \quad 1 \quad 0 \quad 0 \quad 1 \quad \cdots \\
1 \quad 0 \quad 1 \quad \cdots \quad 0 \quad {\color{red} 1} \quad 1 \quad 0 \quad 1 \quad \cdots \quad 1 \quad {\color{blue} 0} \quad 0 \quad 1 \quad \cdots
\end{matrix}
$$

（由于 Latex 渲染问题，该公式建议在博客内查看）

注意到红色 $1$ 的位置，在这个位置为了满足以它作为右下角的矩阵而值为 $1$，但这就导致了以它为左下角的矩阵出现了三个 $1$，成为了一个不合法的矩阵。这正是因为行上也有相邻的两个 $1$，有两个相邻的 $0$ 也是这种情况（蓝色部分）。这是不可避免的，故而这样的矩阵都是不合法的。而如果不出现这种情况，则一定可以构造出合法方案。故而结论证毕。

同时这个结论可以推导出一些东西：对于一个第一行都是 $01$ 相间的矩阵，它的每一行都是 $01$ 相间的；对于一个第一列都是 $01$ 相间的矩阵，它的每一列都是 $01$ 相间的。

接下来考虑如何计数。根据容斥原理，我们用 **行都是 01 相间的矩阵** $+$ **列都是 01 相间的矩阵** $-$ **行列都是 01 相间的矩阵**（即类似棋盘的黑白染色矩阵）。

行都是 $01$ 相间和列都是 $01$ 相间做法类似，这里只介绍行的方式，列做法同理。

- 对于行上没有已确定的 $k$ 个位置，这一行的情况可以任取 $0101\ldots$ 或 $1010\ldots$ 的一种，乘法原理对答案乘 $2$。
- 对于行上已经有确定的位置时，用奇偶性检测它们能否构成 $01$ 相间的一行。如果可以，对答案乘 $1$；如果不行，答案为 $0$。

行列都是 $01$ 相间的矩阵直接检查是否能够构成一个棋盘状的东西，同样判一下奇偶性。注意特判一下 $k = 0$ 的情况。

这题这样就做完了，时间复杂度 $\mathcal{O}(k \log k + \log (n + m))$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>

const int MaxN = 100000;
const int Mod = 1000000007;

inline int add(int x, int y) { return (x += y) >= Mod ? x - Mod : x; }
inline int sub(int x, int y) { return (x -= y) < 0 ? x + Mod : x; }
inline int mul(int x, int y) { return 1LL * x * y % Mod; }
inline int pw(int x, int y) { int z = 1; for (; y; y >>= 1, x = mul(x, x)) if (y & 1) z = mul(z, x); return z; }
inline int inv(int x) { return pw(x, Mod - 2); }
inline int sep(int x, int y) { return mul(x, inv(y)); }
inline void inc(int &x, int y = 1) { x = add(x, y); }
inline void dec(int &x, int y = 1) { x = sub(x, y); }

struct data_t {
  int x, y, d;
  data_t(int _x = 0, int _y = 0, int _d = 0) { x = _x, y = _y, d = _d; }
};

int W, H, N;
data_t A[MaxN + 5];

inline int getSit() {
  char c;
  do c = getchar();
  while (c != '+' && c != '-');
  return (c == '+') ? 1 : 0;
}

void init() {
  scanf("%d %d %d", &W, &H, &N);
  for (int i = 1; i <= N; ++i) {
    A[i].d = getSit();
    scanf("%d %d", &A[i].x, &A[i].y);
  }
}

inline bool cmpx(const data_t &a, const data_t &b) {
  if (a.x != b.x) return a.x < b.x;
  else return a.y < b.y;
}

inline bool cmpy(const data_t &a, const data_t &b) {
  if (a.y != b.y) return a.y < b.y;
  else return a.x < b.x;
}

inline int calc1() {
  std::sort(A + 1, A + 1 + N, cmpx);
  int res = 0, prex = 0;
  for (int l = 1, r = 0; l <= N; l = r + 1) {
    while (r < N && A[r + 1].x == A[l].x) r++;
    for (int i = l; i <= r; ++i) {
      int x1 = (A[i].y ^ A[l].y) & 1, x2 = (A[i].d ^ A[l].d);
      if (x1 != x2) return 0; 
    }
    res += A[l].x - prex - 1;
    prex = A[l].x;
  }
  res += W - prex;
  return pw(2, res);
}

inline int calc2() {
  std::sort(A + 1, A + 1 + N, cmpy);
  int res = 0, prey = 0;
  for (int l = 1, r = 0; l <= N; l = r + 1) {
    while (r < N && A[r + 1].y == A[l].y) r++;
    for (int i = l; i <= r; ++i) {
      int x1 = (A[i].x ^ A[l].x) & 1, x2 = (A[i].d ^ A[l].d);
      if (x1 != x2) return 0; 
    }
    res += A[l].y - prey - 1;
    prey = A[l].y;
  }
  res += H - prey;
  return pw(2, res);
}

inline int calc3() {
  for (int i = 1; i <= N; ++i) {
    int x1 = (A[1].x ^ A[1].y ^ A[i].x ^ A[i].y) & 1, x2 = (A[1].d ^ A[i].d);
    if (x1 != x2) return 0;
  }
  return 1;
}

void solve() {
  int ans = 0;
  inc(ans, calc1());
  inc(ans, calc2());
  dec(ans, calc3());
  if (N == 0) dec(ans);
  printf("%d\n", ans);
}

int main() {
  init();
  solve();
  return 0;
}
```

---

