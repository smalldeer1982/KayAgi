# ナップザック

## 题目描述

# AT683 背包
有$N$个物品，第i个重$w_i$，价值是$v_i$，颜色是$c_i$。背包可以容纳总重量小于$W$，颜色总数小于$C$的物品。问拿到的物品价值总和最大是多少？

## 说明/提示

- $1\le N\le100$
- $1\le W\le10000$
- $1\le C\le50$
- $1\le w_i,v_i\le10000$
- $1\le c_i\le50$  

**样例数据**  
输入：
```
4 5 2
1 10 1
1 20 2
1 30 3
10 100 4
```
输出：
```
50
```
选择第二、三个物品

---
输入：
```
10 20 2
4 5 6
3 3 9
5 2 9
4 1 6
6 8 3
3 7 6
2 4 9
4 7 3
6 5 6
3 2 9
```
输出：
```
27
```

# 题解

## 作者：jijidawang (赞：4)

唯一的一篇题解写的比较迷惑。

令 $dp_{i,j,k}$ 表示选 $1\dots i$ 中的颜色，选了 $j$ 种颜色，质量和为 $k$ 的答案，那么在 $1\dots i$ 加入 $i+1$ 肯定颜色种类数多 1，于是就可以简便处理颜色种类数了。转移类似 01 背包：
$$dp_{i,j,k}=\max\left\{\max_{(w,v,c),\,c=i}\{dp_{i-1,j-1,k-w}+v\},\,dp_{i-1,j,k}\right\}$$

时间复杂度 $\Theta(n+wc^2)$。

[Submission](https://atcoder.jp/contests/tdpc/submissions/41476563)。

---

## 作者：fa_555 (赞：1)

under 题解 [AT683](https://www.luogu.com.cn/problem/AT683)

同步发布于[个人博客](https://fa555.github.io/2020/某At的dp场/#H-ナップザック)

### problem

有 $U \ (1 \le U \le 100)$ 个物品，第 $i$ 个的质量、价值、颜色分别为 $w_i, v_i, c_i \ (1 \le w_i, v_i \le 10000, 1 \le c_i \le 50)$。有一个背包，能容纳总质量为 $W \ (1 \le W \le 10000)$，颜色种类数为 $C \ (1 \le C \le 50)$ 的物品。求能容纳的物品的最大总价值。

### solution

设 $f_{i, j}$ 表示使用不超过 $i$ 种颜色，总质量为 $j$ 时的最大价值。

需要枚举颜色个数和所有颜色，以每个颜色为整体进行转移。

转移时直接套用 01 背包转移方程 $F_i = max{\{F_{i - w_j} + v_j\}}$ 即可。其中 $F$ 代表 $f$ 的第一维。

初始状态 $f_{i, j} = - \infty, f_{0, 0} = 0$。

答案即为 $\max{\{f_{C, i}\}}$。总复杂度 $O(UCW)$，不过常数很小。

### code

``` cpp
using namespace std;

struct Node {
  int w, v;
};

int t[10003], f[53][10003];
vector<Node> z[53];

int main() {
  int N, W, C;

  cin >> N >> W >> C;
  for (int i = 1, w, v, c; i <= N; ++i) {
    cin >> w >> v >> c;
    z[c].push_back({w, v});
  }

  memset(f, 0xc0, sizeof f);
  f[0][0] = 0;
  for (int c = 1; c <= 50; ++c)
    if (z[c].size()) {
      for (int i = C; i; --i) {
        memcpy(t, f[i - 1], sizeof(int) * (W + 1));
        for (Node x : z[c])
          for (int j = W; j >= x.w; --j)
            t[j] = max(t[j], t[j - x.w] + x.v);
        for (int j = 0; j <= W; ++j)
          f[i][j] = max(f[i][j], t[j]);
      }
    }
  cout << *max_element(f[C], f[C] + W + 1) << '\n';
  return 0;
}

```

---

## 作者：NightDiver (赞：0)

定义：$A_c$ 表示颜色为 $c$ 的物品集合，$g \otimes S$ 表示背包 $g$ 中插入集合 $S$ 中的所有物品后的新背包。

刚开始想的是对于每种颜色，求出各自背包，然后进行 $lim_c$ 次 $O({lim_w}^2)$ 的合并。

显然 T 了，考虑漏了什么：本来操作 $g \otimes S$ 是 $O(|g| \cdot |s|)$ 的，当物品个数小于背包大小时，这种合并方式更加合理。

那么就好办了，设 $f_{c,k}$ 表示考虑前 $c$ 种颜色，使用 $k$ 种颜色时的背包（下文中，前一维滚动掉，但是这样 $k$ 需要倒序枚举）。

枚举使用 $c$ 颜色去更新整个 $f$，则 $f_k \otimes A_c \to f_{k+1}$。

因为物品总数为 $n$，所以这么做是 $O(nm\cdot lim_c)$ 的。

[代码在这里](https://www.cnblogs.com/TongKa/p/18568889)

---

