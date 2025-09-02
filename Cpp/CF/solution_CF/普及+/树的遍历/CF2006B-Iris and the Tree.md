# Iris and the Tree

## 题目描述

Given a rooted tree with the root at vertex $ 1 $ . For any vertex $ i $ ( $ 1 < i \leq n $ ) in the tree, there is an edge connecting vertices $ i $ and $ p_i $ ( $ 1 \leq p_i < i $ ), with a weight equal to $ t_i $ .

Iris does not know the values of $ t_i $ , but she knows that $ \displaystyle\sum_{i=2}^n t_i = w $ and each of the $ t_i $ is a non-negative integer.

The vertices of the tree are numbered in a special way: the numbers of the vertices in each subtree are consecutive integers. In other words, the vertices of the tree are numbered in the order of a depth-first search.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/ed42d3ad002b849b19e2cab01dc8c80b05d343e1.png) The tree in this picture satisfies the condition. For example, in the subtree of vertex $ 2 $ , the vertex numbers are $ 2, 3, 4, 5 $ , which are consecutive integers.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/fbbdad2f1a4867f5d12408bb700e0a02f6731145.png) The tree in this picture does not satisfy the condition, as in the subtree of vertex $ 2 $ , the vertex numbers $ 2 $ and $ 4 $ are not consecutive integers.We define $ \operatorname{dist}(u, v) $ as the length of the simple path between vertices $ u $ and $ v $ in the tree.

Next, there will be $ n - 1 $ events:

- Iris is given integers $ x $ and $ y $ , indicating that $ t_x = y $ .

After each event, Iris wants to know the maximum possible value of $ \operatorname{dist}(i, i \bmod n + 1) $ independently for each $ i $ ( $ 1\le i\le n $ ). She only needs to know the sum of these $ n $ values. Please help Iris quickly get the answers.

Note that when calculating the maximum possible values of $ \operatorname{dist}(i, i \bmod n + 1) $ and $ \operatorname{dist}(j, j \bmod n + 1) $ for $ i \ne j $ , the unknown edge weights may be different.

## 说明/提示

In the first test case, $ \operatorname{dist}(1, 2) = \operatorname{dist}(2, 1) = t_2 = w = 10^{12} $ , so $ \operatorname{dist}(1, 2) + \operatorname{dist}(2, 1) = 2 \cdot 10^{12} $ .

In the second test case, the tree after Iris found out all $ t_x $ is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006B/cb4bc8b1d32fd5015d0673154cd358fe4ee772d9.png) $ \operatorname{dist}(1, 2) = t_2 $ , $ \operatorname{dist}(2, 3) = t_2 + t_3 $ , $ \operatorname{dist}(3, 4) = t_3 + t_4 $ , $ \operatorname{dist}(4, 1) = t_4 $ . After the first event, she found out that $ t_2 = 2 $ , so $ \operatorname{dist}(1, 2) = 2 $ . At the same time:

- $ \operatorname{dist}(2, 3) $ is maximized if $ t_3 = 7 $ , $ t_4 = 0 $ . Then $ \operatorname{dist}(2, 3) = 9 $ .
- $ \operatorname{dist}(3, 4) $ and $ \operatorname{dist}(4, 1) $ are maximized if $ t_3 = 0 $ , $ t_4 = 7 $ . Then $ \operatorname{dist}(3, 4) = \operatorname{dist}(4, 1) = 7 $ .

Thus, the answer is $ 2 + 9 + 7 + 7 = 25 $ .

After the second event, she found out that $ t_4 = 4 $ , then $ t_3 = w - t_2 - t_4 = 4 $ . $ \operatorname{dist}(1, 2) = 2 $ , $ \operatorname{dist}(2, 3) = 2 + 3 = 5 $ , $ \operatorname{dist}(3, 4) = 3 + 4 = 7 $ , $ \operatorname{dist}(4, 1) = 4 $ . Thus, the answer is $ 2 + 5 + 7 + 4 = 18 $ .

## 样例 #1

### 输入

```
4
2 1000000000000
1
2 1000000000000
4 9
1 1 1
2 2
4 4
3 3
6 100
1 2 3 2 1
6 17
3 32
2 4
4 26
5 21
10 511
1 2 2 4 2 1 1 8 8
3 2
6 16
10 256
9 128
2 1
5 8
8 64
4 4
7 32```

### 输出

```
2000000000000
25 18 18
449 302 247 200 200
4585 4473 2681 1567 1454 1322 1094 1022 1022```

# 题解

## 作者：Missa (赞：4)

节点编号为 dfs 序，考虑 dfs 时每条边只会被访问两次，$\sum dis(i, i \bmod n+1)$ 也会恰好访问每条边两次。这说明我们直接维护每个 $dis(i, i \bmod n + 1)$ 经过哪些边，在边权修改时暴力修改这些 $dis$ 的一些信息，就能快速得出答案。

那么我们需要对一条路径找到一些信息，只与剩余的 $w$ 和经过的所有边有关，可以快速维护这条路径的长度的上限。注意到，如果这条路径上还有边没有确定，那么把 $w$ 全部放到未确定的边上最优；否则这条路径的长度已经确定了。那么需要维护尚未确定值的边数和已经确定值的边的长度和。

那么答案的组成部分是，确定的路径的长度，没有完全确定的路径的确定部分的长度。对于每条没有完全确定的路径，会额外贡献一个 $w$。直接维护就行了。

```cpp
#include <bits/stdc++.h>

using LL = long long;

void solve() {
  int n; LL w; scanf("%d %lld", &n, &w);
  std::vector<std::vector<int>> ocr(n); // 维护 p[i] 在哪些 dis(i, (i + 1) mod n) 中出现
  std::vector<std::vector<int>> e(n);
  std::vector<int> cur, st(n), cnt(n);
  std::vector<LL> sum(n);
  for (int i = 1, p; i < n; i++) {
    scanf("%d", &p), --p;
    e[p].push_back(i);
  }
  std::function<void(int)> dfs = [&](int u) {
    for (auto x : cur) ocr[x].push_back(u), ++cnt[u];
    cur.clear();
    for (auto v : e[u]) {
      cur.push_back(v), dfs(v), cur.push_back(v);
    }
  };
  dfs(0);
  for (auto x : cur) ocr[x].push_back(0), ++cnt[0];
  LL ans = 0, tmp = 0, tot = n, s = 0;
  // ans 维护确定路径的长度和
  // tmp 维护未确定路径的确定部分的长度和，tot 维护未确定路径的数量
  for (int i = 1; i < n; i++) {
    int x; LL y; scanf("%d %lld", &x, &y), --x;
    w -= y;
    for (auto u : ocr[x]) {
      tmp -= sum[u], sum[u] += y;
      if (!--cnt[u]) {
        ans += sum[u], --tot;
      } else {
        tmp += sum[u];
      }
    }
    printf("%lld ", ans + tot * w + tmp);
  }
  printf("\n");
}

int main() {
  int T; scanf("%d", &T); while (T--) {
    solve();
  }
}
```

---

## 作者：IvanZhang2009 (赞：3)

首先本题的普通做法可以去看别的题解（概括一下，由于 dfs 序的性质，每条边最多经过两次，暴力更新每条路径的情况即可）。这篇题解主要讲解加强版做法：

- 不保证 dfs 序，且要求的 $n$ 条路径改成给定的 $m$ 条路径。
- 强制在线。

普通做法中，一条路径的贡献是：如果没被完全覆盖，则贡献是 $w$ 减去路径外的已知边权和；否则边权和就确定了。我们考虑知道一个边权 $y$ 的影响：求出目前还没被覆盖的且经过这条边的路径数量，对于这些路径，贡献都是 $-y$。注意此时我们把“将要在这一次被覆盖”的也算入其中，于是所有经过这条边的路径就都是了。再找出所有“在这次加边之后被覆盖”的路径数量，贡献是所有已知边权和减 $w$。于是关键的就是求出上面两个的数量。

对于第一点，只要求每条边的被覆盖次数，这个在一开始就可以 lca+ 树上差分解决，相当于已经在线了。对于第二点，在线看上去比较困难，先考虑离线下来之后怎么做。我们考虑求出每条路径最早在什么时候被覆盖。给每条边按照加入顺序赋权（第 $i$ 条加入的边赋权 $i$），然后容易发现这个最早时间就是路径最大值。倍增求解。于是“在某次加边后被覆盖”的路径数量就求出来了。时间复杂度 $O(n\log n)$。

现在要做的问题可以转化成：加入一条边后，给经过这条边的路径长度减一，求有几个路径长度变成了 $0$。其实这和转化后的 [NOI D1T3](https://www.luogu.com.cn/problem/P10787) 几乎一模一样啊！我们设 $f(i,j)$ 表示点 $i$ 到它的 $2^j$ 级祖先的这条路径上有几条边**没被覆盖**。可以发现一条路径可以分解成大约 $\log$ 个 $f(i,j)$ 之和。记 $p(i,j)$ 表示 $i$ 的 $j$ 级祖先，于是可以把 $f(i,j)$ 拆成 $f(i,j-1)+f(p(i,j-1),j-1)$。我们考虑建图，把 $(i,j-1)$ 和 $(p(i,j-1),j-1)$ 都向 $(i,j)$ 连边。考虑一个类似线段树懒标记的做法：我们只要求出所有权值变成 $0$ 的路径，于是不妨在 $f(i,j)$ 变成 $0$ 之后再更新所有它指向的点，如果更新之后也变成了 $0$ 就递归更新下去。同理，如果一个 $(i,j)$ 出现在某条路径上，且某次更新后 $f(i,j)$ 变成了 $0$，就检查这条路径的情况。每个点只会更新一次，于是做到了 $O(n\log n)$ 在线查询。

代码咕了，感觉有点难写。

---

