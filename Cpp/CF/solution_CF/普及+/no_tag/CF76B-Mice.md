# Mice

## 题目描述

在平面上给出两条直线 $y = Y_0$ 和 $y = Y_1$。在 $y = Y_0$ 上有 $n$ 只老鼠，第 $i$ 只老鼠横坐标为 $x_{1, i}$，在 $y = Y_1$ 上有 $m$ 个奶酪，第 $i$ 个奶酪横坐标为 $x_{2, i}$。已知一只老鼠的捕食策略如下：

$1.$ 如果离这只老鼠最近的奶酪有且只有一个，那么这只老鼠会往这个奶酪移动。

$2.$ 如果有多个奶酪离老鼠距离最近，那么这只老鼠会选择向使所有老鼠中挨饿个数最少的奶酪移动。

每只老鼠的移动速度都是一样的，当某些老鼠到达某个奶酪并且当前奶酪还没有被吃掉时，他们会吃掉奶酪并且不再挨饿。如果某个老鼠在到达奶酪时奶酪已经被吃掉了，那么它不会再进行移动，此时我们认为它处于挨饿状态。

请输出最终处于挨饿状态的老鼠个数。

## 样例 #1

### 输入

```
3 2 0 2
0 1 3
2 5
```

### 输出

```
1
```

# 题解

## 作者：Lily_White (赞：3)

本文将用『人』来指代题目中的『老鼠』。

首先口胡出一种贪心算法：

> 贪心选左边的，如果左边被人占了，看能不能吃右边的，不能的话，只好跟左边的竞争了，看谁快。

那这么做为什么是对的呢？

我们注意到一个事实，**每个人的权值是一样的**， 换句话说，如果我们让一个人不吃但让一个没吃到的人去吃，那么 **答案不会变得更差** 。

显然，在某个人右边的人不可能和他去抢他左边的那一块，所以 **选择左边的会对后面的决策造成较小的影响。** 那么，我们就**只要考虑我们的决策和我们左边的人的决策就好了。**

知道这两个事实之后，我们逐一考虑几种操作：

如果左边被人占了，说明**对于我们左边的人，这是他的最优选择。** 这个时候，我们尝试去占右边的不会让答案更差。

如果右边的太远了，我们吃不到，那就只能吃左边的，这个时候左边的就没得吃了，但是**两人对总答案的贡献之和仍然是 1**。换句话说，答案并没变得更差。

否则，我们就去吃右边的。

时间复杂度是 $O(n+m)$.

参考代码：

```cpp
// Problem: B. Mice
// URL: https://codeforces.com/contest/76/problem/B
// Written by RavenclawOIer on 2020-10-30

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define repn(i, n) for (int i = 1; i <= (n); i++)
int n, m, ans;
const int N = 100010, INF = 0x3f3f3f3f;
int x[N], y[N], best[N];
int main() {
  scanf("%d%d%*d%*d", &n, &m);
  rep(i, n) scanf("%d", x + i);
  repn(i, m) scanf("%d", y + i);
  y[0] = -INF;
  y[m + 1] = INF;
  memset(best, INF, sizeof(best));
  rep(i, n) {
    int j = lower_bound(y, y + m + 2, x[i]) - y;
    int dis = min(x[i] - y[j - 1], y[j] - x[i]);
    if (y[j] - x[i] > dis ||
        (x[i] - y[j - 1] == dis && (best[j - 1] == dis || best[j - 1] == INF)))
      --j;
    if (best[j] == INF || best[j] == dis) ++ans;
    best[j] = min(best[j], dis);
  }
  printf("%d\n", n - ans);
  return 0;
}
```

本题也可以 DP。

---

## 作者：chenxia25 (赞：1)

这着实是一个简单题（？

注意到一个黑点显然对应 $1\sim 2$ 个红点。考虑处理出每个红点所对应的黑点集合，显然是区间。然后两个相邻的红点在它们各自的对应黑点集合的右端和左端可能共用一个黑点，我们考虑决策这个黑点到底归谁。显然只有相邻红点才可能互相影响，于是我们可以对红点序列 DP。

我们考虑 $dp_{i,0/1}$ 表示考虑到第 $i$ 个红点，如果它左端有共用的黑点，那么这个黑点属于 / 不属于它的情况下，最少的 unhappy 的黑点个数。然后随便转移即可线性。

然后还要预处理这些个集合，也就是要与处理出每个黑点两边最近的红点。这个可以二分查找（线性对数），甚至可以 two-pointers 做到线性，但是最好写的是直接关于值域前后缀跑一遍（值域是 1e7）。但是空间可能会被卡，考虑前后缀分开来计算，共用一个数组。

可能有其他更简单或更优秀的例如贪心的做法，但我不想管了。

但我当时写了快读，然而这题偏偏有负数，我只写了非负数版本的快读，导致挂的不剩多少了/ll

**_[code](https://www.luogu.com.cn/paste/e3wnn6s0)_**

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18365166)

# 思路

比较简单的贪心。

对于可以选择两个奶酪的老鼠，我们先将它们忽略掉。现在所有老鼠所吃的奶酪是唯一确定的。

考虑加上可以选择两个奶酪的老鼠如何选择。显然，如果它可以选择一个没有任何老鼠吃过的奶酪，它必然这样选择。

其次，如果它可以选择的奶酪被吃掉的时间 $t$ 与它到达奶酪的时间 $T$ 相同，则可以选择共享。

并且可以证明如果这个老鼠不满足上述所有情况，也不会对答案产生影响。

---

如下是简单的证明过程：

令这个在 $x$ 位置上的老鼠走到的奶酪位置分别为 $a,b$，则有 $x - a = b - x$。

由于老鼠两两之间位置不同，并且奶酪两两之间位置不同。因此对于同一块奶酪，最多只会有两只老鼠共享。假设这两个位置为 $p,q$，并且 $p \leq q$。

进行一个简单的分讨：

1. $a - p < x - a$，显然答案不变，因为前者比后者率先到达目的地。

2. $a - p > x - a$。因为 $x - a = b - x \wedge a - p = q - a$，因此 $q \in [x,b]$，但是此时离 $q$ 最近的点是 $b$，不可能出现此情况。

由此得证。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10,inf = 1e9 + 10;
int n,m,_,sum;
int x[N],xx[N];
int Min[N],cnt[N];

struct point{
    int l,r,dist;
};
vector<point> v;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

int main(){
    n = read(),m = read();
    _ = read(),_ = read();
    for (re int i = 1;i <= n;i++) x[i] = read();
    for (re int i = 1;i <= m;i++){
        xx[i] = read(); Min[i] = inf;
    }
    xx[0] = -inf; xx[m + 1] = inf;
    for (re int i = 1,j = 1;i <= n;i++){
        while (j < m && xx[j] < x[i]) j++;
        int a = abs(x[i] - xx[j - 1]),b = abs(x[i] - xx[j]);
        if (a < b){
            if (Min[j - 1] > a){
                Min[j - 1] = a; cnt[j - 1] = 1;
            }
            else if (Min[j - 1] == a) cnt[j - 1]++;
        }
        else if (a > b){
            if (Min[j] > b){
                Min[j] = b; cnt[j] = 1;
            }
            else if (Min[j] == b) cnt[j]++;
        }
        else v.push_back({j - 1,j,a});
    }
    for (point p:v){
        if (Min[p.l] == p.dist) cnt[p.l]++;
        else if (Min[p.r] == p.dist) cnt[p.r]++;
        else if (!cnt[p.l]){
            Min[p.l] = p.dist; cnt[p.l] = 1;
        }
        else if (!cnt[p.r]){
            Min[p.r] = p.dist; cnt[p.r] = 1;
        }
    }
    for (re int i = 1;i <= m;i++) sum += cnt[i];
    printf("%d",n - sum);
    return 0;
}
```

---

