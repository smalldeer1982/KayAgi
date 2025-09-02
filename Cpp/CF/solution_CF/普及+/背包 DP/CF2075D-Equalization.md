# Equalization

## 题目描述

给定两个非负整数 $x$ 和 $y$。

你可以执行以下操作任意次数（包括零次）：选择一个正整数 $k$，并将 $x$ 或 $y$ 除以 $2^k$（向下取整）。此操作的代价为 $2^k$。但存在额外约束：每个 $k$ 值最多只能选择一次。

你的任务是计算使 $x$ 和 $y$ 相等所需的最小可能代价。

## 说明/提示

第一个示例中，可以按如下步骤操作：选择 $k=1$ 并将 $y$ 除以 $2$。之后，$x$ 和 $y$ 均等于 $0$。

第二个示例中，可以按如下步骤操作：选择 $k=2$ 并将 $x$ 除以 $4$；选择 $k=1$ 并将 $y$ 除以 $2$。之后，$x$ 和 $y$ 均等于 $1$。

第三个示例中，两数已经相等，无需操作。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
0 1
6 2
3 3
13 37
4238659325782394 12983091057341925```

### 输出

```
2
6
0
26
32764```

# 题解

## 作者：MrPython (赞：4)

无敌 brute force。注意到 $\log_2 10^{17}$ 约为 $56$，$1+2+3+4+5+6+7+8+9+10=55,11+12+13+14+15=65$，大胆猜测仅需要 $15$ 以内的数就够了。使用复杂度为 $O(3^n)$ 的子集枚举算法枚举所有分配的方案，足以填满整个数组。对于每次询问枚举要右移多少位，取个 min 就好了。

```cpp
#include <array>
#include <bit>
#include <iostream>
#include <limits>
#include <utility>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
const auto f = []() {
  array<array<ui, 64>, 64> d;
  for (auto& i : d)
    for (auto& j : i) j = numeric_limits<ui>::max();
  for (ui i = 0; i < (1u << 16); ++i)
    for (ui j = i; j; j = i & (j - 1)) {
      ui x = 0, y = 0;
      for (ui k = 0; k < 16; ++k)
        if ((i >> k) & 1) ((j >> k) & 1 ? x : y) += k + 1;
      if (x < 64 && y < 64) d[x][y] = d[y][x] = min(d[x][y], i);
    }
  return d;
}();
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    uli x, y;
    fin >> x >> y;
    if (x == y) {
      fout << "0\n";
      continue;
    }
    if (x < y) swap(x, y);
    ui ans = numeric_limits<ui>::max();
    for (ui i = 0; i < 58; ++i)
      for (ui j = 0; j < 58; ++j)
        if ((x >> i) == (y >> j)) { ans = min(ans, f[i][j]); }
    fout << ans * 2 << '\n';
  }
  return 0;
}
```

---

## 作者：cflsfzh (赞：2)

一道很显然的 dp 题，我们很容易想到设 dp 方程为:

$f_{i,j}$ 表示 $x$ 总共左移 $i$ 位，$y$ 总共左移 $j$ 位所需的最小代价。

显然有 dp 转移方程：
$$
\left\{
\begin{aligned}
f_{\min(N-1,i+k),j}=\min(f_{\min(N-1,i+k),j},f_{i,j}+2^k)\\
f_{i,\min(N-1,j+k)}=\min(f_{i,\min(N-1,j+k)},f_{i,j}+2^k)
\end{aligned}
\right.
$$
其中的 $N-1$ 指二进制下的最大位数，我取的是 $60$，$k$ 指的就是题面中的 $k$。这个 dp 显然是可以预处理出来的，至于统计答案，对于一个询问 $\left\{x,y\right\}$，我们只需要枚举 $i$ 和 $j$，表示 $x$ 左移 $i$ 位，$y$ 左移 $j$ 位，只需判断 $x$ 剩下的是否与 $y$ 剩下的相等即可，若相等，计算贡献 $f_{i,j}$ 即可。

请注意，我的代码与上述的变量名有所出入，请理解上述方程后再借鉴代码。

[AC code。](https://codeforces.com/contest/2075/submission/311198045)

---

## 作者：_Kamisato_Ayaka_ (赞：0)

## Statement

给定 $x,y$，每次选择 $k$，令 $x \leftarrow \lfloor\frac{x}{2^k}\rfloor$ 或者 $ y \leftarrow \lfloor\frac{y}{2^k}\rfloor$，每个 $k$ 有且仅能选一次，每次代价 $2^k$，求使得 $x=y$ 的最小代价。

## Solution

除以 $2^k$ 等效于二进制下右移 $k$ 位，从这一点入手。

分别记 $x,y$ 在二进制下有 $n,m$ 位，假设 $x_{n} \sim x_{n-i+1}$ 和 $y_{m} \sim y_{m-i+1}$ 相等，我们就可以把 $x$ 右移 $n-i$ 位，$y$ 右移 $m-i$ 位使它们相等。

考虑动态规划，记 $dp_{i,j}$ 表示 $x$ 右移 $i$ 位，$y$ 右移 $j$ 位的最小代价。

这是一个背包问题，将其看做有两个背包和一堆物品，每个物品只选一次恰好装满两个背包的代价，所以 $01$ 背包预处理。

在将 $x,y$ 转成二进制之后从高到低位考虑，枚举 dp 值取最小，如果说最后 $x=y=0$，显然右移位数大于 $n,m$，枚举大于 $n,m$ 的答案，一个数为另一个的前缀的情况也要考虑。

## Code
[Submission](https://codeforces.com/contest/2075/submission/311186612)

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1MTXuYyEJE)

[参考代码](https://codeforces.com/contest/2075/submission/311144335)

---

