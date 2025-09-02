# Interesting Problem (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的唯一区别在于 $n$ 的限制。只有当你同时解决了两个版本的问题时，才能进行 Hack。

给定一个长度为 $n$ 的整数数组 $a$。

每次操作，你需要执行以下两步：

1. 选择一个下标 $i$，满足 $1 \le i < |a|$ 且 $a_i = i$。
2. 从数组中移除 $a_i$ 和 $a_{i+1}$，并将剩余部分拼接起来。

请你求出最多可以执行上述操作多少次。

## 说明/提示

在第一个测试用例中，一种可能的最优操作序列为 $[1, 5, \color{red}{3}, \color{red}{2}, 4] \rightarrow [\color{red}{1}, \color{red}{5}, 4] \rightarrow [4]$。

在第三个测试用例中，一种可能的最优操作序列为 $[1, \color{red}{2}, \color{red}{3}] \rightarrow [1]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
5
1 5 3 2 4
8
2 1 3 4 5 6 7 8
3
1 2 3
4
1 2 4 4
5
4 4 1 3 5
1
1```

### 输出

```
2
3
1
2
0
0```

# 题解

## 作者：lalaouye (赞：5)

前两个月被这题薄纱了，最后特判了几个数据通过，现在来补。

先看简单版本，注意到后面的删除不会影响到前面的，而如果前面删除了 $x$ 次，那么对于后面的任意一点 $i$，只要是满足 $i-2x\le a_i\le i$ 这个条件就可以删除。

结合数据范围容易想到设 $f_{l,r,x}$ 表示对于 $[l,r]$ 这个区间内，前面删除了 $x$ 次，能删除最多的次数。

这个 dp 有两个转移，一个是 $f_{l,r,x}\leftarrow f_{l+1,r-1,x}$，它的前提是在 $[l+1,r-1]$ 的区间中能够删完且 $l$ 这个位置可以删，一个是 $f_{l,r,x}\leftarrow f_{l,k,x}+f_{k+1,r,x+f_{l,k,x}}$，然后对于前缀取最大值即可。

这样子可以做到 $\mathcal{O}(n^4)$，可以通过简单版本。

考虑优化。发现这样子的区间 dp 直接优化是优化不了的，考虑优化状态。观察它的转移，发现本质上第一个转移是考虑能不能将区间 $[l,r]$ 中的数删完，而第二个转移则是合并能删完与不能删的区间。这启发我们改变状态，设 $f_{l,r}$ 表示在区间 $[l,r]$ 前面至少要删多少数才能使得该区间删完所有数，转移是与刚刚那个 dp 转移类似的，而这个 dp 只需要 $\mathcal{O}(n^3)$ 完成，最后使用一个 $g_i$ 表示对于一个前缀 $[1,i]$ 最多删多少数，利用 $f$ 简单转移即可。

总时间复杂度 $\mathcal{O}(n^3)$，可以通过困难版本。

 代码：

````
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define id(x, y) n * (x - 1) + y
#define ls p << 1
#define rs ls | 1
using namespace std;
constexpr int N = 800 + 5, M = (1ll << 31) - 1, P = 998244353;
constexpr double PI = acos (-1.0);
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + ch - 48;
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
int f[N][N], g[N];
int n;
int a[N];
signed main () {
  for (int T = rd (); T; -- T) {
    n = rd ();
    rep (i, 1, n) a[i] = rd ();
    rep (i, 1, n) rep (j, 1, n) f[i][j] = 1e9, g[i] = 0;
    rep (i, 1, n - 1) {
      if (a[i] <= i && (i - a[i]) % 2 == 0) f[i][i + 1] = (i - a[i]) / 2;
    }
    rep (len, 3, n) {
      rep (l, 1, n - len + 1) {
        int r = l + len - 1;
        if (a[l] <= l && (l - a[l]) % 2 == 0) {
          int must = (l - a[l]) / 2;
          if (f[l + 1][r - 1] <= must) f[l][r] = must;
        } 
        rep (k, l, r - 1) {
          if (((k - l + 1) & 1) || ((r - k) & 1)) continue;
          f[l][r] = min (f[l][r], max (f[l][k], f[k + 1][r] - (k - l + 1) / 2));
        }
      }
    }
    rep (i, 1, n) {
      g[i] = g[i - 1];
      rep (j, 1, i - 1) {
        if (f[j][i] <= g[j - 1]) g[i] = max (g[i], g[j - 1] + (i - j + 1) / 2);
      }
    }
    printf ("%d\n", g[n]);
  }
}
````

---

