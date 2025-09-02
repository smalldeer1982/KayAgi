# Variables and Operations

## 题目描述

There are $ n $ variables; let's denote the value of the $ i $ -th variable as $ a_i $ .

There are also $ m $ operations which will be applied to these variables; the $ i $ -th operation is described by three integers $ x_i, y_i, z_i $ . When the $ i $ -th operation is applied, the variable $ x_i $ gets assigned the following value: $ \min(a_{x_i}, a_{y_i} + z_i) $ .

Every operation will be applied exactly once, but their order is not fixed; they can be applied in any order.

Let's call a sequence of initial variable values $ a_1, a_2, \dots, a_n $ stable, if no matter in which order we apply operations, the resulting values will be the same. If the resulting value of the $ i $ -th variable depends on the order of operations, then the sequence of initial variable values is called $ i $ -unstable.

You have to process $ q $ queries. In each query, you will be given initial values $ a_1, a_2, \dots, a_n $ and an integer $ k $ ; before applying the operations, you can at most $ k $ times choose a variable and decrease it by $ 1 $ . For every variable $ i $ , you have to independently determine if it is possible to transform the given values into an $ i $ -unstable sequence.

## 说明/提示

Consider the first example. If the initial variable values are $ [20, 0, 15, 5] $ , the resulting values will be $ [6, 0, 5, 5] $ with any order of operations. Decreasing the variables $ 10 $ times is not enough. However, if we can apply no more than $ 30 $ changes, we can decrease the $ 1 $ -st variable by $ 2 $ , and the $ 4 $ -th variable by $ 25 $ , we get initial values equal to $ [18, 0, 15, -20] $ , and this sequence is $ 2 $ -unstable and $ 3 $ -unstable:

- if you apply the operations in the order they are given, you will get $ [-12, 0, 5, -20] $ ;
- however, if you apply the operations in order $ [3, 2, 4, 1, 5] $ , you will get $ [-12, -2, 5, -20] $ ;
- and if you apply the operations in order $ [3, 4, 5, 1, 2] $ , you will get $ [-12, -2, 3, -20] $ .

## 样例 #1

### 输入

```
4 5
2 1 10
3 2 5
1 4 8
1 2 6
3 1 17
3
0
20 0 15 5
10
20 0 15 5
30
20 0 15 5```

### 输出

```
0000
0000
0110```

## 样例 #2

### 输入

```
3 5
1 2 100
1 2 10
1 3 5
1 2 100
3 2 5
1
1000000000
0 0 0```

### 输出

```
000```

## 样例 #3

### 输入

```
3 4
2 3 5
1 2 0
3 1 4
1 3 4
10
5
7 5 3
2
5 7 0
1
1 1 1
5
3 0 1
0
5 3 5
5
6 0 4
5
1 5 6
1
7 7 2
1
1 6 6
4
7 7 2```

### 输出

```
000
000
000
001
000
001
001
000
000
000```

# 题解

## 作者：sunkuangzheng (赞：2)

刚注册的 cf 小号倒开过这个题立刻被封了，我们人类写代码还要避开 AI 的码风吗，？

首先考虑 $k=0$ 的做法，我们只关心每个 $i$ 位置能取到的最大值和最小值。最大值是显然的，显然是把终边在位置 $i$ 的边先操作，剩下的没影响，即 $\min(a_j + w_{j,i})$。

考虑最小值怎么求，注意到 $w_{i,j} \ge 0$，因此 $a_i$ 最小的点不可能被更新。只需要类最短路地按 $a_i$ 从小到大依次执行操作，更新到的 $i$ 一定都是最小的。每次询问跑最短路不现实，但是注意到边权是不变的，可以预处理全源最短路，每次询问 $i$ 的最小值即为 $\min(a_j + dis_{j,i})$。于是可以在 $\mathcal O(n^3+n^2q)$ 复杂度内计算答案。

然后考虑 $k>0$ 的情况，很容易证明操作只会用在一个元素上；最大值和最小值都是取 $\min$，减小正值后 $\min$ 不增，因此直接暴力枚举减的是哪个就好了。

[Skipped Submission.](https://codeforces.com/contest/2112/submission/325738844)

---

## 作者：StayAlone (赞：1)

先不考虑修改。对于原题中的 $(x_i,y_i,z_i)$，连 $y_i\to x_i$，长度为 $z_i$ 的边，跑全源最短路。那么 $i$ 点能获得的最小值就是 $\min\{dis_{u, i}+a_u\}$。原因是若 $u$ 到 $i$ 的路径上发生了取 $\min$ 的操作，那么操作的这个点 $v$ 肯定有 $a_v<dis_{u, v}+a_u$，用 $v$ 点更新更优。

同样可以想到，$i$ 点能获得的最大值，就是 $\min\limits_{(i, u, w)\in E}\{a_u+w\}$，即用邻域的点更新。这是一个显然的上界，而且一定存在方案取到。

故一个点 $i$ 不稳定，当且仅当最大值不等于最小值。容易想到操作时肯定要让最小值尽量小，所以只会对一个点操作。

设 $w_{u, v}$ 表示 $u\to v$ 的重边中，最短的边长。

先预处理最短路，对于每次查询，对于每个点 $i$，若它的邻域中存在一个点 $u$，满足 $dis_{u, v}<w_{u, v}$，那么不必操作就是不稳定的。

否则，枚举操作的点 $j$（不在邻域）。此时最大值不受影响，最小值可取 $\min\{dis_{j, i}+a_j-k\}$。对所有 $j$ 求出最小值后判断即可。

代码略有区别，基于上述思路，如果想清楚可以省去分类讨论。由 $\mathcal O(m)=\mathcal O(n^2)$，时间复杂度 $\mathcal O(n^3+qn^2)$。

[AC record](https://codeforces.com/contest/2112/submission/325852005)

```cpp
int n, m, a[510], vis[510], dis[510][510];
vector <pii> lnk[510];
 
int main() {
    read(n, m);
    rep1(i, 1, n) rep1(j, 1, n) if (i ^ j) dis[i][j] = inf;
    rep1(i, 1, m) {
        int x, y, w; read(x, y, w);
        lnk[x].eb(y, w); gmin(dis[y][x], w);
    }
    rep1(i, 1, n) vis[i] = inf;
    rep1(k, 1, n) rep1(i, 1, n) rep1(j, 1, n) gmin(dis[i][j], dis[i][k] + dis[k][j]);
    for (int Q = read(), k; Q--; ) {
        read(k); rer(i, 1, n, a);
        rep1(i, 1, n) {
            int dmx = a[i], dis2 = inf;
            for (auto [v, w] : lnk[i]) gmin(vis[v], w), gmin(dmx, w + a[v]);
            rep1(j, 1, n) if (i ^ j && dis[j][i] < vis[j]) gmin(dis2, a[j] + dis[j][i] - k);
            ptc('0' + (dmx > dis2));
            for (auto [v, w] : lnk[i]) vis[v] = inf;
        } puts("");
    }
    return 0;
}
```

---

