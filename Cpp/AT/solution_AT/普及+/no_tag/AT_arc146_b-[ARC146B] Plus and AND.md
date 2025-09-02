# [ARC146B] Plus and AND

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc146/tasks/arc146_b

長さ $ N $ の非負整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。あなたは以下の操作を $ M $ 回以下行うことができます。($ 1 $ 回も行わなくてもよいです。)

- $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ を選び、$ A_i $ を $ 1 $ 増やす。

その後、$ A $ の中から $ K $ 要素を選びます。

選んだ $ K $ 要素のビット単位 $ \mathrm{AND} $ の最大値を求めてください。

  ビット単位 $ \mathrm{AND} $ 演算とは  整数 $ A,\ B $ のビット単位 $ \mathrm{AND} $、$ A\ \mathrm{AND}\ B $ は以下のように定義されます。

- $ A\ \mathrm{AND}\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち両方が $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \mathrm{AND}\ 5\ =\ 1 $ となります (二進表記すると: $ 011\ \mathrm{AND}\ 101\ =\ 001 $)。  
 一般に $ k $ 個の整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{AND} $ は $ (\dots\ ((p_1\ \mathrm{AND}\ p_2)\ \mathrm{AND}\ p_3)\ \mathrm{AND}\ \dots\ \mathrm{AND}\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots\ p_k $ の順番によらないことが証明できます。 ​

## 说明/提示

### 制約

- $ 1\ \le\ K\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 0\ \le\ M\ <\ 2^{30} $
- $ 0\ \le\ A_i\ <\ 2^{30} $
- 入力は全て整数である。

### Sample Explanation 1

以下のような手順を踏むことで 選んだ $ 2 $ 要素の $ \mathrm{AND} $ として $ 10 $ を達成できます。 - $ A_3 $ を選ぶ操作を $ 6 $ 回行う。$ A_3\ =\ 10 $ となる。 - $ A_4 $ を選ぶ操作を $ 2 $ 回行う。$ A_4\ =\ 10 $ となる。 - $ A_3,A_4 $ を選ぶ。$ 2 $ 要素の $ \mathrm{AND} $ は $ 10 $ である。 選んだ $ 2 $ 要素の $ \mathrm{AND} $ を $ 11 $ 以上にすることはできないので、解は $ 10 $ です。

## 样例 #1

### 输入

```
4 8 2
1 2 4 8```

### 输出

```
10```

## 样例 #2

### 输入

```
5 345 3
111 192 421 390 229```

### 输出

```
461```

# 题解

## 作者：Phartial (赞：5)

由于有式子 $2^n>\sum_{i=0}^{n-1}2^i$，所以考虑按位贪心。

假设当前正在考虑第 $i$ 位，那么把第 $j$ 个数的第 $i$ 位变成 $1$ 的代价为 $\max(0,2^i-j\bmod 2^{i+1})$。把所有数的代价算出来，取前 $k$ 小的代价，如果加起来不大于 $m$，那么把答案的第 $i$ 位设为 $1$ 肯定最优。把前 $k$ 小的数的贡献加到对应的数上，然后删掉所有第 $i$ 位为 $0$ 的数（因为这些数是不能被选择的），继续判断下一位即可。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int k, n, m, a[kN], b[kN], d[kN], ans, _a[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 31; i >= 0 && n >= k; --i) {
    for (int j = 1; j <= n; ++j) {
      d[j] = j;
      b[j] = max(0LL, (1LL << i) - (a[j] & ((1LL << i + 1) - 1)));  // 计算代价
    }
    sort(d + 1, d + n + 1, [](int i, int j) { return b[i] < b[j]; });
    LL s = 0;
    for (int j = 1; j <= k; ++j) {  // 选代价前 k 小的数
      s += b[d[j]];
    }
    if (s <= m) {                     // 如果可行
      m -= s, ans |= 1 << i;          // 将答案的这一位设为 1
      for (int j = 1; j <= k; ++j) {  // 修改对应的数
        a[d[j]] += b[d[j]];
      }
      int _n = 0;
      for (int j = 1; j <= n; ++j) {  // 删掉不能选的数
        if (a[j] >> i & 1) {
          _a[++_n] = a[j];
        }
      }
      copy_n(_a + 1, n = _n, a + 1);
    }
  }
  cout << ans;
  return 0;
}
```

---

