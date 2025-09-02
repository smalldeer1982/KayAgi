# [ARC037D] Chaotic Polygons

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc037/tasks/arc037_d

非負整数 $ L $ に対し、レベル $ L $ のシェルピンスキーのガスケットとは次のような図形である。

- レベル $ 0 $ のシェルピンスキーのガスケットとは、 $ 1 $ 個の正三角形である。
- レベル $ i $ ($ i $ $ ≧ $ $ 1 $) のシェルピンスキーのガスケットは、レベル $ i-1 $ のシェルピンスキーのガスケットに含まれる $ 3i-1 $ 個の正三角形それぞれに対して以下の操作を行って得られる図形である。  
   (操作) 正三角形の各辺の中点を結び、中心に小さな正三角形を作る。この正三角形を図形から取り除く（この結果、もとの正三角形は $ 3 $ つの小さな正三角形に分割される）。

以下にレベル $ 0,1,2,3,4 $ のシェルピンスキーのガスケットを図示する。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc037_d/5a357333ea00f1b1c9530fab93f43b77e64ac598.png)

正整数 $ L $ が与えられる。レベル $ L $ のシェルピンスキーのガスケットに含まれる $ 3L $ 個の正三角形のすべての辺を考える。これらの線分から形成される単純多角形 (自己交差しない多角形) の個数を $ 1,000,000,007 $ で割った余りを求めよ。相似な多角形であっても位置が異なるものは区別する。

以下に数えるべき多角形とそうでないものの例を示す。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc037_d/0cddd04506e34a3ef17fb2428dacca22017f1d6d.png)

## 说明/提示

### Sample Explanation 1

以下の $ 11 $ 個の単純多角形が存在する。 !\[\](http://arc037.contest.atcoder.jp/img/arc/037/ljlefijfewkjfwefk/D\_sample1.png)

## 样例 #1

### 输入

```
1```

### 输出

```
11```

## 样例 #2

### 输入

```
2```

### 输出

```
1033```

## 样例 #3

### 输入

```
3```

### 输出

```
30304092```

## 样例 #4

### 输入

```
123```

### 输出

```
853343829```

# 题解

## 作者：xyf007 (赞：4)

设第 $i$ 个的答案是 $\mathit{ans}_i$，如果一个回路不是在一个 $(i-1)$ 层三角形的内部，那么必然同时经过了这三个小三角形。于是记 $h_i$ 表示从第 $i$ 层三角形一个顶点进入，另一个顶点离开的方案数，则 $\mathit{ans}_i=3\mathit{ans}_{i-1}+h_{i-1}^3$。问题转化成计算 $h_i$。  
以左下角进入，右下角离开为例。如果不经过上面那个小三角形，方案数是 $h_{i-1}^2$；否则，方案数就是经过左下角、上方、右下角三个三角形方案数的乘积。但是有一个问题：底边中点只能经过一次。因此还要设 $f_i$ 和 $g_i$ 分别表示从一个顶点进入，一个顶点离开，经过/不经过剩下那个顶点的方案数，计算的时候减去两边都经过底边中点的方案数。即
$$ \begin{aligned}f_i&=f_{i-1}(h_{i-1}^2-f_{i-1}^2)\\g_i&=h_{i-1}^2+g_{i-1}(h_{i-1}^2-f_{i-1}^2)\\h_i&=f_i+g_i\end{aligned} $$
时间复杂度 $O(n)$。

代码中省去了计算 $g$ 的过程，`g[i]` 就是 $h_i$。
```cpp
#include <atcoder/modint>
#include <iostream>
using mint = atcoder::modint1000000007;
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
int n;
mint f[100001], g[100001], ans[100001];
int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  std::cin >> n;
  f[0] = 1, g[0] = 2, ans[0] = 1;
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] * (g[i - 1] * g[i - 1] - f[i - 1] * f[i - 1]);
    g[i] = g[i - 1] * g[i - 1] +
           g[i - 1] * (g[i - 1] * g[i - 1] - f[i - 1] * f[i - 1]);
    ans[i] = ans[i - 1] * mint::raw(3) + g[i - 1] * g[i - 1] * g[i - 1];
  }
  std::cout << ans[n].val() << '\n';
  return 0;
}
```

---

