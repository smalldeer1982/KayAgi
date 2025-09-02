# Counting Is Fun (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ n $ . You can make hacks only if both versions of the problem are solved.

An array $ b $ of $ m $ non-negative integers is said to be good if all the elements of $ b $ can be made equal to $ 0 $ using the following operation some (possibly, zero) times:

- Select two distinct indices $ l $ and $ r $ ( $ 1 \leq l \color{red}{<} r \leq m $ ) and subtract $ 1 $ from all $ b_i $ such that $ l \leq i \leq r $ .

You are given two positive integers $ n $ , $ k $ and a prime number $ p $ .

Over all $ (k+1)^n $ arrays of length $ n $ such that $ 0 \leq a_i \leq k $ for all $ 1 \leq i \leq n $ , count the number of good arrays.

Since the number might be too large, you are only required to find it modulo $ p $ .

## 说明/提示

In the first test case, the $ 4 $ good arrays $ a $ are:

- $ [0,0,0] $ ;
- $ [0,1,1] $ ;
- $ [1,1,0] $ ;
- $ [1,1,1] $ .

## 样例 #1

### 输入

```
4
3 1 998244853
4 1 998244353
3 2 998244353
343 343 998244353```

### 输出

```
4
7
10
456615865```

# 题解

## 作者：strcmp (赞：13)

这是积木大赛，所以如果没有 $l < r$ 的限制我们一定有解。

但是有 $l < r$ 的限制，就要看它产生了什么限制。

![](https://cdn.luogu.com.cn/upload/image_hosting/jamyjmlq.png)

对，就是这种类似 CF Logo 的图形。

翻译成人话就是：存在 $i$ 满足 $a_i > a_{i - 1} + a_{i + 1}$，则必定无解。

![](https://cdn.luogu.com.cn/upload/image_hosting/6umv861x.png)

首先无解是一定的，这种情况下 $a_i$ 最多减 $a_{i - 1} + a_{i + 1}$ 次，然后 $a_{i - 1}$ 和 $a_{i + 1}$ 变成 $0$，就消不了了。

那不存在这种情况就合法了吗？这也是容易理解的。

根据积木大赛的结论，我们考虑包含 $a_{i - 1}$ 的所有区间 $[?,\,i - 1]$，我们显然不关心 $?$ 是什么。然后考虑将这个区间多覆盖到 $i$。进而还剩下 $a_{i}' = a_{i} - a_{i - 1}$。如果 $a_{i + 1} - a_i' \ge 0$ 显然能消完 $a_i$（把包含 $a_{i + 1}$ 的区间左端点扩到 $a_i$ 就好了）。对所有 $a_i$ 从外到内这样讨论可知必然有解。

---

好，现在就是计数所有满足 $a_{i} \ge a_{i - 1} - a_{i - 2}$  的序列方案数了。

此时有一个 naive 的做法就是设个 $f_{i,\,x,\,y}$ 代表前 $i$ 个位置 $i$ 位置是 $x$ 而 $i - 1$ 位置是 $y$ 的方案数。朴素实现 $\Theta(nk^3)$，后缀和优化一下 $\Theta(nk^2)$。后者能过 Easy Version。

但还是不够切这道题。

从转移方程上找东西显然是无用功，只能继续发掘性质。比如——考虑容斥。

发现一个重要性质：不合法的位置不会相邻。

很简单，因为你随便考虑某两个相邻的不合法位置，假设分别是 $a_{i - 1}$ 和 $a_i$。

则 $a_{i - 1} > a_{i - 2} + a_{i},\,a_{i} > a_{i - 1} + a_{i + 1} \Rightarrow a_{i} > a_{i} + a_{i - 2} + a_{i + 1} \Rightarrow a_{i - 2} + a_{i + 1} < 0$。显然矛盾。

![](https://cdn.luogu.com.cn/upload/image_hosting/7qc1n5iu.png)

不合法位置不相邻，给我们优化复杂度以极大方便。

一个明显的好处就是我们可以直接从 $i - 2$ 位置转移过来。进而不用考虑 $i - 3$ 选取了什么。

设 $f_{i,\,j}$ 代表考虑到第 $i$ 个数，末尾是 $j$ 的合法序列数。

则有：

$$
f_{i,\,j} \leftarrow \sum f_{i - 1} - \sum_{x = 0}^{k - j - 1} f_{i - 2,\,x} \times (k - j - x)
$$

因为 $i$ 不合法所以我们不用考虑 $i - 1$ 不合法的可能。后面一项相当于计数 $i$ 位置之前都合法，而 $i$ 位置不合法的序列并容斥。

前面一坨直接记录和，后面一坨倒序枚举 $j$ 前缀和记录 $k - j - x$  的增量即可。

时间复杂度 $\Theta(nk)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ld = double;
typedef long long int ll;
using pdi = pair<ld, int>;
using vec = vector<int>;
constexpr int maxn = 3e3 + 10; 
int T, n, k, mod, f[maxn][maxn], g[maxn][maxn];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &k, &mod);
		rep(i, 0, n + 1) rep(j, 0, k) f[i][j] = g[i][j] = 0;
		f[0][0] = 1; rep(i, 0, k) f[1][i] = g[0][i] = 1, g[1][i] = i + 1;
		rep(i, 2, n + 1) {
			int s = 0;
			per(j, k, 0) f[i][j] = ((ll)g[i - 1][k] - (s = (s + g[i - 2][k - j - 1]) % mod) + mod) % mod;
			rep(j, 0, k) g[i][j] = ((j ? g[i][j - 1] : 0) + f[i][j]) % mod;
		}
		printf("%d\n", f[n + 1][0]);
	}
	return 0;
}
```

  同类题（lca 长训营入营测试赛，侵删）：给定长度为 $n$ 的非负整数序列 $w$。定义一个长度为 $n$ 的序列 $a$ 的权值是 $\prod\limits_{i = 1}^{n - 2} w_{\max \{ a_i,\,a_{i + 1},\,a_{i + 2}\}}$，求所有值域在 $[0,\,n]$ 长度为 $n$ 的非负整数序列的权值和。对 $998244353$ 取模，$n \le 4 \times 10^3$。

---

## 作者：Alex_Wei (赞：5)

### [D1. Counting Is Fun (Easy Version)](https://www.luogu.com.cn/problem/CF1943D1)

考虑合法序列的充要条件，这个是经典结论：设 $a_0 = a_{n + 1} = 0$，考虑所有 $a_i > \max(a_{i - 1}, a_{i + 1})$ 的位置 $i$，如果 $a_i > a_{i - 1} + a_{i + 1}$ 则不合法，因为一个区间要么包含 $[i - 1, i]$，要么包含 $[i, i + 1]$。否则容易构造出让这三个位置同时变为 $0$ 的操作。基于这些操作，容易构造出让整个序列清零的操作：

- 如果 $a_i$ 极大且 $a_{i + 2}$ 极大，则 $i + 1$ 会被覆盖 $2a_{i + 1}$ 次。将 $[l, i + 1]$ 和 $[i + 1, r]$ 两次操作合并成 $[l, r]$ 一次操作即可。
- 否则 $a_i$ 极大且 $a_{i + k}$ 极大，满足 $k \geq 3$，则 $a_{i + 1\sim i + k - 1}$ 形成非严格单谷序列，将覆盖 $i + 1$（同时以 $i + 1$ 为右端点）的操作的右端点向右拉，将覆盖 $i + k - 1$ 的操作的左端点向左拉即可。

于是序列合法的充要条件为 $\forall 1\leq i \leq n$，$a_i \leq a_{i - 1} + a_{i + 1}$。设 $f_{i, x, y}$ 表示 $a_{i - 1} = x$ 且 $a_i = y$ 的方案数，则 $f_{i, x, y}$ 贡献至 $f_{i + 1, y, z}$，满足 $y \leq x + z$ 且 $0\leq z\leq k$，即 $\max(0, y - x)\leq z \leq k$。

使用前缀和优化，时间复杂度 $\mathcal{O}(n ^ 3)$。[代码](https://codeforces.com/contest/1943/submission/251749532)。

---

## 作者：Rain_chr (赞：3)

### 题意

我们认为一个序列是好的当且仅当能通过区间减一变成全零序列，其中区间减一不能退化成单点减一。

对所有长度为 $n$，值域在 $[1,m]$ 的好序列计数。

### D1 做法

时间复杂度：$O(n^3)$

对于这种题，我们先可以转化好序列的充要条件。

区间减一，很容易想到差分序列。那么我们对原序列求差分序列，问题就转化为在选择点不相邻的情况下单点减一并单点加一，让 $[1,n+1]$ 全部变成零。

单点减一并单点加一很容易就想到是匹配问题——差分数组总用前面的正数匹配后面的负数，这样就可以了。

我们设 $dif$ 为原序列的差分序列，那么能匹配完当且仅当  $\displaystyle \sum^{i-2}_{j=1} dif_j \ge -dif_i$，这样的话当前这一位能够匹配前面剩下的。

但是我们发现这样很蠢，因为差分数组的前缀和就是原数组，所以上式等价于 $a_{i-2} \ge -a_i+a_{i-1}$，即 $a_{i-2}+a_i \ge a_{i-1}$。

所以，只要原数列对于 $1\le i \le n$ 的下标都满足上述条件，原数列就是合法的。

所以我们设 $dp[i][j][k]$ 表示当前有 $i$ 位，原数列倒数第一位为 $j$，倒数第二位为 $k$，用前缀和优化转移即可。

### D2 做法

时间复杂度：$O(n^2)$

赛时我的思路止步于此，最终也因此下大分。

由于状态数已经不能接受了，我们考虑优化状态。具体的，我们通过容斥将性质弱化。

我们设 $f(i)$ 表示钦定有 $i$ 个位置是不合法的，根据容斥答案显然为 $\displaystyle \sum^{n}_{i=0} (-1)^i f(i)$ 。

可以发现，如果我们要使 $a_{i-2}+a_i \ge a_{i-1}$ 不合法，在已知 $a_{i-2}$ 的情况下，$a_{i-1}$ 是可以直接算的。

**提示**：为什么要用容斥弱化条件，是因为如果我们不容斥，直接算 $a_{i-1}$，我们并不知道 $a_{i-1}$ 造成的贡献是什么。只有容斥，我们才能只考虑当前位。

所以我们可以设 $dp[i][j][k]$ 表示前 $i$ 位，最后一个数为 $j$，当前钦定有 $k$ 个不合法的位置。

再次发现这样很蠢，因为系数仅与钦定的不合法位置个数的奇偶性相关，所以我们就可以优化成 $dp[i][j][0/1]$ 表示其奇偶性。

那么我们现在转移就要分类讨论了：

1. 当前位不钦定产生贡献 
	
那么前一位选啥都可以（因为不钦定），所以直接继承上一位选所有数的答案。

2. 当前位钦定产生贡献

$dp[i][j][k]=\displaystyle \sum^{m}_{l=1} dp[i-2][l][1-k] \times (m-l-j)$

同样可以前缀和优化，具体的，维护 $\displaystyle \sum^{m}_{l=1} dp[i-2][l][1-k] \times (m-l)$ 与 $\displaystyle \sum^{m}_{l=1} dp[i-2][l][1-k]$，分类讨论即可。

### 总结

本题考查了转化条件的能力，对于充要条件进行容斥计数。并且压状态的方式十分巧妙，是一道有思维的计数题。

---

## 作者：caoshurui (赞：2)

### 提示 1

不妨思考一下什么情况下 $b$ 才是好的。可以尽量从贪心的角度来考虑。

### 提示 2

显然如果一个 $b$ 是**坏的**，则必定必须使用一个长度为 $1$ 的区间来消成零。所以现在的目标就是尽可能得不出现长度为 $1$ 的区间。假设当前有 $x$ 个长度为 $1$ 的区间。如果 $b_i < b_{i + 1}$，则 $x$ 变为 $b_{i + 1} - b_i$，否则如果 $x < b_{i + 1}$，则一定会留下来一些长度为 $1$ 的区间，则一定不合法。

整理一下就得到了满足 $\forall 1 \le i \le n, b_{i} \le b_{i - 1} + b_{i + 1}$ 的 $b$ 一定是合法的。

### 提示 3

已经基本上出来啦。数据范围只有 $400$，直接 DP 就行了。

### 提示 4

直接放代码参考吧。


```cpp

/*
Solution:

forall 1 <= i <= n, a[i] <= a[i + 1] + a[i - 1]

f[i][j][k] 表示第 i 位为 j 第 i - 1 位为 k 的方案数

f[i][j][k] = f[i - 1][l][j], max(0, j - k) <= l <= k

*/

#include <algorithm>
#include <iostream>
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define lop(i, x, y) for (int i = x; i >= y; i--)
#define int long long

using namespace std;

using pii = pair<int, int>;
using ll = long long;

const int MAXN = 505;

int T, ans;
int n, k, mod;

int f[2][MAXN][MAXN], sum[2][MAXN][MAXN];
bool now;

void solve() {
  cin >> n >> k >> mod, ans = 0;

  now = 0;
  rep(i, 0, k) rep(j, 0, k) f[0][i][j] = f[1][i][j] = 0,
                            sum[0][i][j] = sum[1][i][j] = 0;

  rep(i, 0, k) {
    f[0][0][i] = 1;
    rep(j, 0, k) sum[0][i][j] = 1;
  }

  rep(i, 2, n) {
    now ^= 1;
    rep(x, 0, k) {
      rep(y, 0, k) {
        int t = max(0ll, x - y);
        if (t <= k) {
          f[now][x][y] = (sum[now ^ 1][x][k] - (t ? sum[now ^ 1][x][t - 1] : 0) + mod) % mod;
        } else {
          f[now][x][y] = 0;
        }
        sum[now][y][x] = (f[now][x][y] + (x ? sum[now][y][x - 1] : 0)) % mod;
      }
    }
  }

  rep(i, 0, k) rep(j, 0, i) ans = (ans + f[now][i][j]) % mod;

  cout << ans << '\n';
}

signed main() {
  // freopen("data", "r", stdin);
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--; solve());
  return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

显然先找“好数组”的充要条件。对原数组 $a$ 差分，设 $b_i = a_i - a_{i - 1}$。那么一次可以选择一对 $(i, j)$ 满足 $i \le j - 2$，然后给 $b_i$ 减 $1$，给 $b_j$ 加 $1$。

我们从左往右操作。注意到我们不能操作相邻的一对元素，所以若某个时刻 $b_i > 0$ 且 $b_{1 \sim i - 2}$ 都为 $0$ 就不合法。这就是充要条件。

充要条件可以表述成 $b_i + \sum\limits_{j = 1}^{i - 2} b_j \ge 0$，即 $a_i - a_{i - 1} + a_{i - 2} \ge 0$，注意 $a_0 = a_{n + 1} = 0$。

对于 $n \le 400$ 可以直接做一个 $O(n^3)$ dp，设 $f_{i, j, k}$ 为考虑了 $[1, i]$ 的前缀，$a_{i - 1} = j, a_i = k$ 的方案数。因为合法的 $a_{i - 2}$ 是一段后缀，所以预处理后缀和即可做到 $O(1)$ 转移。这样可以[通过 D1](https://codeforces.com/problemset/submission/1943/251749221)。

---

## 作者：云浅知处 (赞：2)

- [PYD1](https://www.luogu.com.cn/user/266732) 给我说的这个题，我在原神启动之前就会做了，很快啊！
- 话说官方题解为啥要容斥呢。下面是不用容斥的做法。

考虑合法的充要条件。求差分序列 $b_i=a_i-a_{i-1},1\le i\le n+1$，其中 $a_{n+1}=a_0=0$。

则每次可以选 $i+1<j$，让 $b_i\leftarrow b_i-1,b_j\leftarrow b_j+1$。

考虑 Hall 定理，发现限制最严的时候一定是取左部点是一个前缀。于是这等价于对任意 $i\ge 2$，有 $\sum_{j=1}^{i-2}[b_i>0]b_i\ge \sum_{j=1}^i[b_i<0](-b_i)$。

即 $\sum_{j=1}^ib_i-[b_i>0]b_{i}-[b_i>0]b_{i-1}\ge 0$。讨论一下：

- $b_i>0,b_{i-1}>0$：左边变成 $a_{i-2}$，一定 $\ge 0$。
- $b_i>0,b_{i-1}<0$：左边变成 $a_{i-1}$，一定 $\ge 0$。
- $b_i<0,b_{i-1}>0$：左边是 $a_i-b_{i-1}$。
- $b_i<0,b_{i-1}<0$：左边是 $a_i$，一定 $\ge 0$。

于是只需要

- 对任意的 $i\ge 2$，有 $a_i-b_{i-1}\ge 0$。这里 $i$ 可以取到 $n+1$。

为了方便我们改写为：

- 对任意 $1\le i\le n,a_{i-1}-a_i+a_{i+1}\ge 0$。其中 $a_0=a_{n+1}=0$。

此时有简单 $O(nk^2)$ DP：记录最后两个元素的值即可。已经足以通过 D1。

考虑优化。

~~感觉直接对这个自动机跑最小化就好了。~~

我们还是来脑动跑一下 DFA minimize 吧！

设 $f(i,j,k)$ 表示 $i$ 个元素，$a_i=j,a_{i-1}=k$。我们发现：

- $j\le k$ 的状态，DP 值全都一样。这是因为 $j$ 这个位置一定符合要求了，所以 $k$ 就不会影响合法性。
- $j\ge k$ 的状态，转移全都一样。这是因为 $k$ 这个位置一定符合要求了，所以 $j$ 不会影响合法性。

于是就做完啦。对于 $j\le k,j>k$ 我们分别记录单独 $j$ 和 $k$，转移时再乘上系数即可。

具体的系数和转移在代码的注释中写的很清楚。

<https://codeforces.com/contest/1943/submission/252190617>

---

## 作者：Conan15 (赞：1)

本文将原题中的 $k$ 记为 $m$。

考虑满足题目要求的序列有什么性质：当一个数特别大而两边特别小的时候是不满足条件的。\
准确的说，当 $a_i \gt a_{i-1} + a_{i+1}$ 是不满足的，这是显然的，因为 $a_i$ 这个数要么只能和左边一起 $-1$，要么只能和右边一起。如果左右都分配完它本身仍然 $\gt 0$，那么就无法消除了。\
设 $f_{i,j,k}$ 表示写了前 $i$ 个数，$a_{i-1}=j$，$a_i=k$ 的方案数。

这是好转移的，枚举下一次选 $l$ 即可。\
这边注意统计答案的时候要特判最后一个数也要满足条件，即 `ans += dp[n][i][j]` 需要满足条件 $0 \leq j \leq i$，我调试的时候在这里卡了一会儿。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 415;
int T, n, m, mod, dp[N][N][N];

void solve() {
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= m; k++) dp[i][j][k] = 0;
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int k = 0; k <= m; k++)     //i
            for (int j = 0; j <= m; j++) { //i-1
                if (!dp[i][j][k]) continue;
                //满足 0 <= l <= m，且 k <= j+l ----> k-j<=l
                for (int l = 0; l <= m; l++) {
                    if (k <= j + l) (dp[i + 1][k][l] += dp[i][j][k]) %= mod;
                }
            }
    long long ans = 0;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= i; j++) (ans += dp[n][i][j]) %= mod;
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
```

观察一下复杂度，枚举前 $i$ 个数和 $j,k,l$，复杂度是高贵的 $O(nk^3)$，显然无法通过本题。\
观察式子发现对于一个 $l$，满足条件的 $dp_{i,j,k}$ 是一段前缀的形式，那么把 $k \leq j+l$ 和 $0 \leq m$ 移项后组合起来就成了：$\max(0,k-j) \leq l \leq m$。\
记录 $sum_{p}$ 表示 $p=\max(0,k-j)$ 的所有 $dp_{i,j,k}$ 之和，然后再做一遍前缀和，转移的时候就不需要枚举 $j$ 了，时间复杂度降低至 $O(nk^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 415;
int T, n, m, mod, dp[N][N][N];
int sum[N];

void solve() {
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= m; k++) dp[i][j][k] = 0;
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int k = 0; k <= m; k++) {     //i
            for (int j = 0; j <= m; j++) sum[j] = 0;
            for (int j = 0; j <= m; j++) (sum[max(0, k - j)] += dp[i][j][k]) %= mod;
            for (int j = 1; j <= m; j++) (sum[j] += sum[j - 1]) %= mod;
            for (int l = 0; l <= m; l++) (dp[i + 1][k][l] += sum[l]) %= mod;
            
            // for (int j = 0; j <= m; j++) { //i-1
            //     if (!dp[i][j][k]) continue;
            //     //满足 0 <= l <= m，且 k <= j+l ----> k-j<=l
            //     for (int l = 0; l <= m; l++) {
            //         if (max(0, k - j) <= l) (dp[i + 1][k][l] += dp[i][j][k]) %= mod;
            //     }
            // }
            
        }
    long long ans = 0;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= i; j++) (ans += dp[n][i][j]) %= mod;
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

大家好这是 D1 直接暴力 DP 的朴素做法 。
### 题意
一个序列，如果可以通过若干次对一个长度**大于等于** $2$ 的子段 $-1$ 使得序列变为全 $0$，则认为它是好的。

给定长度 $n$，值域 $k$ 和模数 $P$，求出该条件下好序列的个数。
### 分析
这种**对存在某种性质的对象计数**的题目一般先考虑判定版本。

于是你考虑用一个比较优美的语言来描述好序列的判定，方便下面的计数。

你发现正着描述不好描述，于是你反着想。一个序列什么时候不是好的呢，显然如果有一个位置非常大，与其它数字差得很多，那其它数字就没办法带着它一起减下去了。由于你选择更长的区间只会耗费更多的数值，所以理论最优的策略是只用和它相邻的数字把它一起减掉，那么这个序列好的充要条件就是 $a_i\le a_{i-1}+a_{i+1}$。

于是结论猜完了。我们声称它非常对，然后可以开写了。

那么现在我们只要计数一个长度为 $n$，值域为 $k$，满足 $\forall i,a_i\le a_{i-1}+a_{i+1}$ 的序列就行了。这东西显然在 $n\le 400$ 的范围下随便 DP 就好了，考虑设 $dp_{i,x,y}$ 表示填到第 $i$ 位，第 $i$ 位为 $x$，第 $i-1$ 位为 $y$ 的方案数，枚举下一个数字，刷表法转移。然后复杂度爆了，再加个前缀和优化，$O(n^3)$ 就过了。具体实现参考一下代码。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=4e2+5;
int T;
int n,k,mod;
int ans;
int tmp[maxn];
int dp[maxn][maxn][maxn];
void add(int &x,int y){x+=y;if(x>=mod) x-=mod;}
signed main(){
	#ifndef ONLINE_JUDGE
		assert(freopen("data.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read(),k=read(),mod=read();
		for(int i=2;i<=n;i++) for(int x=0;x<=k;x++) for(int y=0;y<=k;y++) dp[i][x][y]=0; 
		for(int x=0;x<=k;x++) for(int y=x;y<=k;y++) dp[2][x][y]=1;
		for(int i=2;i<n;i++){
			for(int x=0;x<=k;x++){
				for(int t=0;t<=k;t++) tmp[t]=0;
				for(int y=0;y<=k;y++){
					if(!dp[i][y][x]) continue;
					add(tmp[max(x-y,0)],dp[i][y][x]);
				}
				for(int t=0;t<=k;t++){
					add(tmp[t],tmp[t-1]);
					if(tmp[t]) add(dp[i+1][x][t],tmp[t]);
				}
			}
		}
		ans=0;
		for(int x=0;x<=k;x++) for(int y=0;y<=x;y++) add(ans,dp[n][x][y]);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

题意：给定序列，每次选择长度 $>1$ 的区间减 $1$，若可以变为全 $0$ 序列，那么是好的，问存在多少长度为 $n$ 且元素 $\in[0,k]$ 的好序列。

### D1

如果一个操作修改了 $i$，那么它要么修改了 $i-1$，要么修改了 $i+1$。所以：一个序列是好的 $\Rightarrow a_i\leq a_{i-1}+a_{i+1}$。假如一个序列满足 $a_i\leq a_{i-1}+a_{i+1}$，那么每次操作序列之后都能让序列仍然满足上述条件。如果 $a_{i+2}=a_{i+1}+a_{i+3}$，那么操作 $[i,i+2]$，否则操作 $[i,i+1]$。若干次操作之后，序列必然全 $0$。所以：一个序列是好的 $\Leftrightarrow a_i\leq a_{i-1}+a_{i+1}$。

DP，设 $f_{i,x,y}$ 为 $a_{i-1}=x,a_i=y$ 的方案数，则 $a_{i+1}\geq y-x$，前缀和优化后 $\mathcal O(n^3)$。

### D2

设 $dp_{i,x}$ 表示长度为 $i$ 的以 $x$ 结尾的，且 $[1,i)$ 合法的不合法序列方案，设 $f_{i,x}$ 表示长度为 $i$ 的以 $x$ 结尾的合法序列方案。所以计算 $dp$ 时只需枚举 $a_{i-1}$，得到转移方程

$dp_{i,j}=\sum_{b=0}^kf_{i-2,b}\max(k-j-b,0)$

显然

$f_{i,j}=(\sum_{b=0}^kf_{i-1,b})-dp_{i,j}$

前缀和优化后 $\mathcal O(n^2)$。

---

## 作者：Unnamed114514 (赞：0)

考虑把区间 $-1$ 刻画在差分数组上，记 $c$ 为差分数组。

操作相当于 $c_l-1,c_{r+1}+1$。

也就是说，你 $i$ 这个位置要加的不能超过前面可以减去的。

即 $\sum\limits_{j=1}^{i-2} c_j\ge -c_i$。

根据差分数组的前缀和为原数组，知原式等价于 $a_{i-2}\ge a_{i-1}-a_i$，即 $a_i\ge a_{i-1}-a_{i-2}$。

因此令 $f_{i,j,k}$ 表示前 $i$ 个数，$a_{i-1}=j,a_i=k$ 的方案数。

发现每次 dp 更新后面的时候 $j$ 不变，$k$ 是一段连续的区间，直接上差分即可。

---

## 作者：Z_301 (赞：0)

为了方便假设 $\forall i\not\in[1,n],a_i=0$。

直接考虑好序列的充要条件。发现是 $\forall i,a_i\le a_{i-1}+a_{i+1}$。为什么？

- 必要性：不难发现，对于每个 $i$，如果一个操作区间 $[l,r]$ 包含了 $i$，那它也一定至少包含了 $i-1$ 或 $i+1$ 中的一个。换句话说，最后 $c_i$ 为 $i$ 被覆盖的次数（不难发现 $a_i=c_i$ ），则有 $c_i\le c_{i-1}+c_{i+1}$，即 $a_i\le a_{i-1}+a_{i+1}$。

- 充分性：考虑说明我们总能进行一次操作，使得序列仍然满足条件。记 $p$ 为所有 $a_i\not=0$ 的下标中最小的那个。考虑如下几种情况：

	- $a_{p+2}<a_{p+1}+a_{p+3}$。操作 $[p,p+1]$。
    
	- $a_{p+2}=a_{p+1}+a_{p+3}$。注意到此时满足 $a_{p+3}<a_{p+2}$（由于 $a_{p+1}>0$）和 $a_{p+1}<a_{p}+a_{p+2}$（由于 $a_p>0$ 和 $a_{p+1}\le a_{p+2}$），所以可以直接操作 $[p,p+2]$。

然后直接 DP 即可。具体的，记 $f_{i,j,k}$ 为，满足以下条件的好序列的方案数：

- 长度为 $i$。

- $a_{i-1}=j$。

- $a_{i}=k$。

转移直接枚举下一个数。复杂度 $O(n^4)$。

发现可以后缀和优化。复杂度 $O(n^3)$。

---

