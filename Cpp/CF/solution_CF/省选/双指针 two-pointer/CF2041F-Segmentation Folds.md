# Segmentation Folds

## 题目描述

Peter 喜欢折线段玩。有一条线段位于数轴上的区间 $[\ell, r]$。现如今正是折叠线段的好时机，Peter 决定小心翼翼地对这条线段进行折叠。每次操作中，他可以选择以下两种方式之一（在可能的情况下）：

1. 操作 $\tt{LTR}$：他从左向右折线段，使得左端点 $\ell$ 与某个点 $x$ 重合（$\ell < x \le r$），并且 $\ell + x$ 是质数。当他选择此操作时，总是选取最大的 $x$ 值。折叠后，线段所在的区间变为 $[\frac{1}{2}(\ell + x), r]$。
   
2. 操作 $\tt{RTL}$：他从右向左折线段，使得右端点 $r$ 与某个点 $x$ 重合（$\ell \le x < r$），并且 $r + x$ 是质数。当他选择此操作时，总是选取最小的 $x$ 值。折叠后，线段所在的区间变为 $[\ell, \frac{1}{2}(r + x)]$。

一个折叠序列是指这两种操作的组合。Peter 想要通过多次折叠，使线段的长度尽可能短，且无法再缩短。区间的长度自然定义为 $r - \ell$。考虑以下例子：假设我们折叠一段初始为 $[1, 30]$ 的线段。有三种折叠方式能使最终区间长度最短，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041F/be032bc113ac39f401b84d34f2c5f31947b110d1.png)

请你帮助 Peter 确定有多少种不同的折叠序列可以使线段达到最短长度。结果需要对 $998244353$ 取模。

注：一个大于 $1$ 的整数 $p$ 是质数，当且仅当不存在整数 $a, b > 1$ 使得 $p = ab$。

## 样例 #1

### 输入

```
3
1 30
16 18
142857 240135```

### 输出

```
3
1
63```

# 题解

## 作者：JiangZhixu (赞：2)

## 题目大意

本题开启多测，$T \leq 10$。

给定一个数对 $(l, r)$，满足 $1 \leq l < r \leq 10^{12}$，$r - l \leq 10^{5}$，其中 $l$ 和 $r$ 是整数，你需要每次对其进行以下操作之一：

- 将 $(l, r)$ 修改为 $(x, r)$，其中 $2x$ 是一个质数，且 $l < x \leq \frac{l + r}{2}$，$x$ 必须在条件范围内最大；
- 将 $(l, r)$ 修改为 $(l, y)$，其中 $2y$ 是一个质数，且 $\frac{l + r}{2} \leq y < r$，$y$ 必须在条件范围内最小。

在经过若干次操作后，该数对将无法进行任何操作，此时该数对 $(l', r')$ 的长度 $L = r' - l'$。

你需要找到最小的 $L_{min}$，并输出可以得到长度为 $L_{min}$ 的无法进行任何操作的数对的操作方法的个数（结果一样但过程不一样的操作算作不同的操作）。

## 解题思路

首先，我们为了便于处理，可以将 $l$ 和 $r$ 在输入过后立即乘以 $2$，这样可以使问题中不会出现 $\frac{1}{2}$。

接下来，我们就需要解决问题的关键——质数的处理。由于 $l$ 和 $r$ 的范围非常大，我们不能使用常规的筛法来处理质数，所以我们需要一个更加高效的预处理。

我们注意到 $r - l$ 的范围其实非常小，所以我们可以只对这一段区间做最朴素的筛法。

如果我们使用 $2 \sim \sqrt{2r}$ 中的数来筛 $2l \sim 2r$ 的话，算法的时间复杂度是无法接受的，因此我们还需要进一步优化。

考虑再加上一层筛法，可以先使用线性筛筛出 $2 \sim \sqrt{2r}$ 中的质数，然后再用这些质数来筛 $2l \sim 2r$ 中的质数。

这种算法的时间复杂度因涉及质数和调和级数，所以详细的时间复杂度分析可以参考相关资料和官方及其他题解，在此不再赘述。但是由于 $2 \sim \sqrt{2r}$ 中的质数并不多，且这个数较大时被筛到的数很少，因此可以得出这种方法的时间复杂度是极低的。

接下来，我们可以使用搜索算法来解决这个问题。考虑使用宽度优先搜索来搜索所有可能的操作序列，可以使用二分算法来快速找到适合的质数。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int l, r, n, minn = LLONG_MAX, cnt = 0;
    cin >> l >> r;
    l <<= 1; // 乘 2 便于处理 1 / 2
    r <<= 1;
    n = sqrt(r);
    vector<int> ps, v;
    vector<bool> p(n + 1), h(r - l + 1, 1);
    // 筛 2 ~ 根号 2r  +  筛 2l ~ 2r
    for (int i = 2; i <= n; i++) {
        if (!p[i]) {
            for (int j = max(ceil(l * 1.0 / i), 2.0) * i; j <= r; j += i)
                h[j - l] = 0; // 筛 2l ~ 2r
            v.push_back(i);
        }
        for (int j : v) {
            if (i * j > n)
                break;
            p[i * j] = 1;
            if (i % j == 0)
                break;
        }
    }
    // 将哈希转化为数组
    for (int i = l; i <= r; i++)
        if (h[i - l])
            ps.push_back(i);
    queue<pair<int, int>> q;
    q.push({l, r});
    vector<pair<int, int>> ans;
    // BFS
    while (!q.empty()) {
        bool ok = 1;
        vector<int>::iterator it;
        // RTL
        it = lower_bound(
            ps.begin(), ps.end(),
            ceil((q.front().first + q.front().second) / 2.0));
        if (it != ps.end() && *it < q.front().second) {
            ok = 0;
            q.push({q.front().first, *it});
        }
        // LTR
        it = upper_bound(ps.begin(), ps.end(),
                         (q.front().first + q.front().second) / 2);
        if (it != ps.begin() && *(--it) > q.front().first) {
            ok = 0;
            q.push({*it, q.front().second});
        }
        // 不能再进行操作
        if (ok) {
            ans.push_back({q.front().first, q.front().second});
            minn = min(minn, q.front().second - q.front().first);
        }
        q.pop();
    }
    // 统计答案
    for (pair<int, int> i : ans)
        if (i.second - i.first == minn)
            cnt++;
    cout << cnt << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

## F. Segmentation Folds

给定 $[l,r]$，你需要选择以下操作任一执行：

- 选择一个最大的 $x(l\lt x\leq r)$ 满足 $l+x$ 是质数，$[l,r]\to [\frac{1}{2}(l+x),r]$。

- 选择一个最小的 $x(l\leq x\lt r)$ 满足 $r+x$ 是质数，$[l,r]\to [l,\frac{1}{2}(r+x)]$。

如果这个区间 $[l,r]$ 无法操作，则称这个区间为一个结束状态。否则继续递归。

问所有结束状态中，长度最小的有多少个。答案对 $998244353$ 取模。

多测，$1\leq t\leq 10$。

$1\leq l\lt r\leq 10^{12}$，$r-l\leq 10^5$。

---

为了规避浮点问题，我们把所有区间的 $l,r$ 都乘上 $2$。

我们首先要把 $[2l,2r]$ 之间的素数都筛出来。我们先预处理到 $\sqrt{2r}$ 的所有质数，然后把这些质数在 $[2l,2r]$ 内的倍数筛出来。具体参见 [P1835 素数密度](https://www.luogu.com.cn/problem/P1835)。

然后大力搜索即可。

搜索的时候可以通过二分找到第一个和最后一个合法的 $x$。但是这样复杂度多带一个 $\log$。我们把二分的内容拎出去，在预处理完质数之后，枚举所有的情况找到上一个下一个质数。

搜索的结束状态一定是两个相邻的质数。只有 $\mathcal O(\frac{n}{\log n})$ 个。而每个状态只有 $\mathcal O(\log n)$ 个前驱状态，所以直接搜索甚至不带记忆化的复杂度是 $\mathcal O(n)$ 的。

总复杂度瓶颈在筛质数的 $\mathcal O(n\log \log n)$。

代码写的有点丑了，丑在了：

>我们把二分的内容拎出去，在预处理完质数之后，枚举所有的情况找到上一个下一个质数。

这一部分。写的是二分，如果写双指针最后复杂度就是 $\mathcal O(n\log \log n)$。这份代码是 $\mathcal O(n\log n)$ 的。 

<https://codeforces.com/contest/2041/submission/294604119>

---

