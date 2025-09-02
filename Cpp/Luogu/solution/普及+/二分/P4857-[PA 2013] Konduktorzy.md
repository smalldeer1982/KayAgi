# [PA 2013] Konduktorzy

## 题目描述

一辆无限长的列车，有 $k$ 个检票员。每个检票员一次检验 $a_i$ 个车厢，初始时所有检票员在 $0$ 号车厢。

列车长每次命令最靠左的编号最小的检票员向右走 $a_i$ 步，一共发出 $n$ 个命令，输出每个售票员走的最后一步是列车长的第几次命令。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 2\times 10^{13}$，$1\le k\le 10^5$，$k\le n$，$1\le a_i\le 10^5$。

## 样例 #1

### 输入

```
10 3
3 5 6
```

### 输出

```
10 9 7```

# 题解

## 作者：jiangly (赞：12)

首先二分求出每个人结束的时间 $end_i$。

我们只需要求出每个人最后一次检票开始之后有多少次检票。即有多少个 $end_j-k\cdot a_j$ 大于等于 $end_i-a_i$，如果 $j\le i$ 则不能取等。

因为 $a_i$ 互不相同，且 $\max\{end_i\}-\min\{end_i-a_i\}\le 2C$ ($C=\max\{a_i\}$)，因此有用的数的个数只有 $O(C\log k)$。

我们记录每个数的出现次数，求后缀和求能得到所有 $\ge end_i-a_i$ 的数的个数。再减去 $i$ 之前出现的等于 $end_i-a_i$ 的数的个数即可。

时间复杂度 $O(k\log nC+C\log k)$。

```cpp
#include <bits/stdc++.h>

constexpr int N = 1e5;

int64_t n;
int k;
int a[N];

int64_t pos[N];

int cnt[2 * N], ans[N];

int64_t count(int64_t m) {
    int64_t s = 0;
    for (int i = 0; i < k; ++i)
        s = std::min<int64_t>(s + (m + a[i] - 1) / a[i], 1e18);
    return s;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cin >> n >> k;
    for (int i = 0; i < k; ++i)
        std::cin >> a[i];
    
    int64_t l = 0, r = 2e18;
    while (l < r) {
        int64_t m = (l + r + 1) / 2;
        if (count(m) <= n) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    
    int res = n - count(l);
    for (int i = 0; i < k; ++i) {
        pos[i] = (l + a[i] - 1) / a[i] * a[i];
        if (pos[i] == l && res > 0) {
            --res;
            pos[i] += a[i];
        }
    }
    
    int64_t mn = 2e18, mx = 0;
    for (int i = 0; i < k; ++i) {
        mx = std::max(mx, pos[i]);
        mn = std::min(mn, pos[i] - a[i]);
    }
    
    for (int i = 0; i < k; ++i) {
        for (int64_t j = pos[i] - a[i]; j >= mn; j -= a[i])
            ++cnt[j - mn];
        ans[i] = -cnt[pos[i] - a[i] - mn];
    }
    
    for (int i = mx - mn - 2; i >= 0; --i)
        cnt[i] += cnt[i + 1];
    for (int i = 0; i < k; ++i) {
        ans[i] += cnt[pos[i] - a[i] - mn];
        std::cout << n - ans[i] << " \n"[i == k - 1];
    }
    
    return 0;
}
```

---

## 作者：huanyue (赞：8)

如果你是看到**能够继续检票**无法理解,所以戳进了题解,

这个根本没用,实际就是向前走.可以回去再思考一下



读完题,不看数据范围,~~你一定会认为这是憨憨的优先队列模拟~~

当你地看到$n \leq 2*10^{13}$,嗯,有意思.

~~仔细思索后,你点击了 查看题解 看到了这段文字~~



如果$n \leq 10^5$,用优先队列是轻松跑过的,

但仔细想一下,对于在最后一段之前的模拟,都是没有必要的

$k\leq 10^5$ 那么用$O(n log n)$是可以接受的,

那么假设所有检票员都走到了位置$X$,有

$step=\sum^{k}_{i=1}\lfloor x/a_i\rfloor$

如果$step<n$说明所有检票员都尽量走到$X$,并且还有没用完指令

我们可以**二分**满足$step\leq n$的最大$X$,

再将$X$适当前推,计算出一个所有人在的位置.

再计算出走到这个位置所花的步数,与$n$相减.

剩下的交给堆模拟

```cpp
/*
 * @Author: Huanyue 
 * @Date: 2020-02-15 10:48:32 
 * @Last Modified by: Huanyue
 * @Last Modified time: 2020-02-15 10:51:16
 */
#include <iostream>
#include <cstdio>
#define MAXN 100005
#define LL long long int
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
using namespace std;

int n, num[MAXN];
LL m, l, r, mid, temp, ans[MAXN];

inline bool check(LL mid)
{
    LL t = m;
    for (int i = 1; i <= n; ++i)
    {
        t -= mid / num[i];
        if (t < 0)
            return 0;
    }
    return 1;
}

int mv[MAXN + MAXN];
LL cnt[MAXN];
inline void pushup(int &p)
{
    int &r = mv[p];
    r = p;
    if (cnt[mv[p << 1]] < cnt[r] || cnt[mv[p << 1]] == cnt[r] && mv[p << 1] < r)
        r = mv[p << 1];
    if (cnt[mv[p << 1 | 1]] < cnt[r] || cnt[mv[p << 1 | 1]] == cnt[r] && mv[p << 1 | 1] < r)
        r = mv[p << 1 | 1];
}

void update(int u, LL d)
{
    if (d < cnt[u])
        return;
    cnt[u] = d;
    for (; u; u >>= 1)
        pushup(u);
}

char w;
inline void GET(int &t)
{
    do
        w = getchar();
    while (w < '0' || w > '9');
    do
    {
        t = t * 10 + w - '0';
        w = getchar();
    } while (w >= '0' && w <= '9');
}

int main()
{
    cnt[0] = 9223372036854775807ll;
    scanf("%lld", &m), GET(n);
    for (int i = 1; i <= n; ++i)
        GET(num[i]), l = max(l, num[i]);
    r = l * m, ++l;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (check(mid))
            temp = mid, l = mid + 1;
        else
            r = mid - 1;
    }

    LL t = temp;
    for (int i = 1; i <= n && t; ++i)
        t = min(t, max((temp / num[i] - 1) * num[i], 0));
    LL used = 0;
    int tmp;
    for (int i = 1; i <= n; ++i)
    {
        used += t / num[i];
        update(i, t / num[i] * num[i]);
    }
    while (used < m)
    {
        tmp = mv[1];
        ans[tmp] = ++used;
        update(tmp, cnt[tmp] + num[tmp]);
    }
    for (int i = 1; i < n; ++i)
        printf("%lld ", ans[i]);
    printf("%lld\n", ans[n]);
    return 0;
}
```







---

