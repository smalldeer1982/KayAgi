# [ARC044C] ビーム

## 题目描述

### 题意简述

有一个 $H\times W$ 的网格，左下角为 $\left(1,1\right)$，右上角为 $\left(W,H\right)$。

这个网格很危险，会有 $Q$ 束光束飞来，光束用形如 $\left(T,D,X\right)$ 的三元组给出，$T$ 表示光束到来的时间，$D$ 表示方向（$0$ 为垂直，$1$ 为水平），$X$ 为坐标。例如 $\left(t,1,a\right)$ 表示第 $t$ 秒有一束光束会通过所有坐标为 $\left(i,a\right)\left(1\le i\le W\right)$ 的格子。

高桥君已知所有光束来袭的信息，他要让自己不会被光束击中。他可以自由选择初始位置，且结束位置没有限制，一秒可以移动任意次（每次可以横向或竖向移动一步），但不能走出网格。

请计算高桥君最少的移动次数。如果高桥君一定会碰到光束，则输出 $−1$。

## 说明/提示

$1\le W,H\le 10^5,0\le Q\le 10^5,1\le T_i\le 10^5,D_i\in\left\{0,1\right\}$，当 $D_i=0$ 时 $1\le X_i\le W$；当 $D_i=1$ 时 $1\le X_i\le H$，$\forall i\ne j,\left(T_i,D_i,X_i\right)\ne\left(T_j,D_j,X_j\right)$。

[Y204335](https://www.luogu.com.cn/user/360974)翻译

## 样例 #1

### 输入

```
3 2 8
1 0 2
3 0 2
4 1 2
2 1 2
4 0 3
2 0 3
1 1 1
2 0 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2 4 10
3 1 1
2 1 3
3 0 1
2 1 4
1 1 3
2 1 2
3 1 2
1 0 1
3 1 4
2 0 2```

### 输出

```
4```

## 样例 #3

### 输入

```
3 3 5
1 0 3
1 0 2
1 1 3
1 1 2
1 0 1```

### 输出

```
-1```

# 题解

## 作者：Y204335 (赞：1)

# \[ARC044C] ビーム

## 题目大意

有一个 $H\times W$ 的网格，有 $Q$ 束光束，高桥君可以从任意点开始任意移动，求他使自己不被击中的最少的移动次数，无解输出 $-1$。

## 题目分析

显然这是一个最优化问题，可以考虑贪心，尽可能不移动，将每秒的光束叠加在一起，直到没有一个地方安全时回退到上一秒，将其作为一段，再从零开始叠加，也就变成了从当前段的最优位置转移到下一个最优位置的问题，但这样处理很麻烦，而且时间复杂度太高（贪心正确性不清楚，如果正确当然应该也能做，只是太麻烦了）。

考虑其他方法，可以进行 dp，设 $dp_{i,j,k}$ 表示第 $i$ 秒末到 $\left(j,k\right)$ 的最少移动次数，从四周转移，转移方程可以很容易得到，但这样直接做复杂度为 $O\left(TWH\right)$（其中 $T$ 为总时间），根据具体实现复杂度可能更高。

考虑进行优化，由于要求的是最短的曼哈顿距离，**横向和竖向移动是无关的**，并且光束会通过一整行或列，可以**把行和列分别处理**，最后再加起来。以行为例，设 $dp_{i,j}$ 为第 $i$ 秒末在第 $j$ 行的最少移动次数，转移方程很容易，当当前行没有光束时移动次数不变，有光束时可以从左或右的没有光束的位置转移过来，当每个位置都有光束时无解输出 $-1$，在处理时需要进行排序，复杂度为 $O\left(T\left(W+H\right)\log\left(W+H\right)\right)$，仍然很高。

继续进行优化，不难发现每一次**只有有光束的行或列，dp 的值才会改变**，可以每次只处理有光束的行或列，重复利用已有的 dp 值。以行为例，设 $dp_i$ 为当前秒末在第 $i$ 行的最少移动次数，$f_i$ 为当前秒末到当前秒有光束的 $i$ 行的最少移动次数。对当前秒的垂直光束排序后，分别从左、右进行转移，总转移方程如下（设 $x$ 为 $i$ 左侧最靠近 $i$ 的无光束的行，$y$ 为 $i$ 右侧最靠近 $i$ 的无光束的行）。

$$f_i=\min\left\{dp_x+\left(i-x\right),dp_y+\left(y-i\right)\right\}$$

全部处理完成后再用 $f$ 更新 $dp$，最后答案取最小值即可。

时间复杂度为 $O\left(T+W+H+Q\log Q\right)$。

## 代码

注意代码中的 $f$ 数组也被存在 $dp$ 数组中了。

代码中的 $dp_{i,j,k}$ 中 $i$ 表示为是否是临时数组（为 $1$ 相当于上文的 $f$ 数组，为 $0$ 相当于上文的 $dp$ 数组），$j$ 表示行 / 列，$k$ 表示第 $k$ 行 / 列。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, inf = 0x3f3f3f3f;
int w, h, q, dp[2][2][N], ans, mmin, ti;
vector<int> x[N], y[N];
void sol(vector<int> a, int p)
{
    sort(a.begin(), a.end());
    for (int i = 0, lst = 0; i < (int)a.size(); i++) {
        if (a[i] == 1) {
            lst = -1;
            dp[1][p][a[i]] = inf;
            continue;
        }
        if (i == 0 || a[i - 1] != a[i] - 1) {
            dp[1][p][a[i]] = dp[0][p][a[i] - 1] + 1;
            lst = dp[1][p][a[i]];
        } else if (lst != -1) {
            dp[1][p][a[i]] = lst + 1;
            lst = dp[1][p][a[i]];
        } else {
            dp[1][p][a[i]] = inf;
        }
    }
    for (int i = a.size() - 1, lst = 0; i >= 0; i--) {
        if (a[i] == (p == 0 ? w : h)) {
            lst = -1;
            dp[1][p][a[i]] = min(dp[1][p][a[i]], inf);
            continue;
        }
        if (i == (int)a.size() - 1 || a[i + 1] != a[i] + 1) {
            dp[1][p][a[i]] = min(dp[1][p][a[i]], dp[0][p][a[i] + 1] + 1);
            lst = dp[1][p][a[i]];
        } else if (lst != -1) {
            dp[1][p][a[i]] = min(dp[1][p][a[i]], lst + 1);
            lst = dp[1][p][a[i]];
        } else {
            dp[1][p][a[i]] = min(dp[1][p][a[i]], inf);
        }
    }
    for (auto i : a) {
        dp[0][p][i] = dp[1][p][i];
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> w >> h >> q;
    for (int i = 1; i <= q; i++) {
        int t, d, p;
        cin >> t >> d >> p;
        ti = max(ti, t);
        if (d == 0)
            x[t].push_back(p);
        else
            y[t].push_back(p);
    }
    for (int i = 1; i <= ti; i++) {
        if ((int)x[i].size() == w || (int)y[i].size() == h) {
            cout << -1 << '\n';
            return 0;
        }
        sol(x[i], 0);
        sol(y[i], 1);
    }
    mmin = inf;
    for (int i = 1; i <= w; i++) {
        mmin = min(mmin, dp[0][0][i]);
    }
    ans += mmin;
    mmin = inf;
    for (int i = 1; i <= h; i++) {
        mmin = min(mmin, dp[0][1][i]);
    }
    ans += mmin;
    cout << ans << '\n';
    return 0;
}
```

---

