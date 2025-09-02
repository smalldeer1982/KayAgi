# [NEERC 2017] Hack

## 题目描述

Heidi 正在分析一个特殊的设备。该设备以一个 $a$ 作为输入，并使用以下伪代码和存储在设备中的一些整数 $d$ 和 $n$ 计算 $a^d \bmod n$：

```
modPow(a, d, n) {
  r = 1;
  for (i = 0; i < 60; ++i) {
    if ((d & (1 << i)) != 0) {
      r = r * a % n;
    }
  a = a * a % n;
  }
}
```

注意，伪代码假设整数可以是任意大小，$<<$ 表示按位左移，$&$ 表示按位与，% 表示取模。

设备不会告诉 Heidi 计算结果。然而，Heidi 可以测量计算所需的时间。她知道只有模 $n$ 的乘法（上述伪代码中的第 5 行和第 7 行）需要可测量的时间，其他所有行可以假设为 0 纳秒。

此外，她知道将 $x$ 和 $y$ 模 $n$ 相乘需要 $(\text{bits}(x) + 1) \cdot (\text{bits}(y) + 1)$ 纳秒，其中 $\text{bits}(x)$ 是 $x$ 的二进制表示中不含前导零的位数，更正式地，$\text{bits}(x) = \lceil \log_2 (x + 1) \rceil$。

Heidi 知道整数 $n$，但不知道整数 $d$。她想通过将不同的整数 $a$ 作为输入提供给设备，并测量每个 $a$ 的计算时间来找到 $d$。

她知道 $n$ 和 $d$ 是通过以下方式选择的：首先，两个具有 30 位二进制表示的素数 $p$ 和 $q$（换句话说，在 $2^{29}$ 和 $2^{30} - 1$ 之间）被独立且均匀地随机选择。然后计算 $n = p \cdot q$。然后计算 $m = \varphi(n) = (p-1) \cdot (q-1)$。然后在 $1$ 到 $m - 1$ 之间均匀随机选择 $d$，使其与 $m$ 互质。

# 交互协议

首先，测试系统写入整数 $n$——设备使用的模数。注意，$n$ 和隐藏的数字 $d$ 保证是按照上述过程生成的。

你的解决方案应打印两种类型的请求：

- “? a” 告诉设备以 $a$ 作为输入。$a$ 必须是 $0$ 到 $n-1$ 之间的整数。测试系统会返回设备计算 `modPow(a , d , n)` 所需的时间（以纳秒为单位）。

- “! d” 告诉你的程序已确定的 $d$ 值。

不要忘记在每次请求后刷新输出！

你的解决方案必须发出恰好一个第二种类型的请求，该请求必须是最后一个请求，并且解决方案在发出该请求后必须正常终止。

你的解决方案最多可以发出 $30,000$ 个第一种类型的请求。

你的解决方案将在 $30$ 个测试用例上运行，每次运行处理一个 $(n , d)$ 对。对于每个测试用例，数字 $n$ 和 $d$ 是固定的，并且是使用上述过程生成的。下面的例子不是以这种方式生成的，因此不会用于测试你的解决方案；它仅用于说明输入/输出格式并为计算时间的合理性检查提供一个 sanity check。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
15
980
293```

### 输出

```
? 3
? 8
! 5```

# 题解

## 作者：ZnPdCo (赞：1)

由于运行时间是 $\text{bits}+1$ 相乘，所以我们定义 $\text{len}(x)=\text{bits}(x)+1$，运行时间就是 $\text{len}$ 相乘了。

考虑如何算 $d$？首先，考虑能不能算出 $d$ 的 popcount。设 $d$ 的 popcount 为 $s$，那么一共会进行 $s$ 次「他乘」（`r = r * a`），进行 $60$ 次「自乘」（`a = a * a`）。我们假设将 $a$ 赋值为一个随机数，那么过程中 $a$ 和 $r$ 也都可以被看作是一个随机数。假设随机数的 $\text{len}$ 期望为 $l$，那么「将 $a$ 设为一个随机数运行一次」期望耗费的时间就是 $60l^2+(s-1)l^2+2l$，这里不是 $sl^2$ 而是 $(s-1)l^2+2l$ 的原因是，$r$ 初始为 $1$，不能看作一个随机数，所以 $\text{len}$ 为 $2$。只有「他乘」过一次后才能够看作一个随机数。

那么枚举所有 $s$，选择和真实运行时间差最小的那个作为 $q$ 的 popcount 即可。

热身完毕，上面的过程可写可不写，主要是用在最后剪枝的，不过不写也能过。

类比上面的过程，我们希望能够得到一个更加充分的信息来计算 $q$ 的每一位。

假设我们询问的是随机数 $a$，那么我们运行过程中对运行时间的贡献分为「他乘」和「自乘」。「自乘」会运行恰好 $60$ 次，当 $a$ 固定的时候「自乘」的代价是确定的，所以我们可以减去。现在只剩下了「他乘」的时间贡献，这个可以计算出 $d$。考虑在 $i=t$ 时进行一次「他乘」，会将 $r$ 和 $a^{2^t}$ 相乘，同时也说明 $d$ 的第 $t$ 位为 $1$。其中 $r$ 我们依旧看作是一个随机数，期望长度为 $l$。但是 $a^{2^t}$ 在这里我们就不看做是随机数了，因为我们明确知道它的值，如果它的值比 $\dfrac{n}{16}$ 还要小，我们称它在第 $t$ 位是极小的，那么它对计算时间的贡献也会小一点，大概率会小于平均值。这个信息很有用。

我们枚举大量的随机数 $a$，将运行时间减去可以计算的「自乘」时间，得到有用的「他乘」时间，同时计算出 $a$ 在哪些位是极小的。

将全部的「他乘」时间计算出平均值，如果单次枚举的 $a$ 的「他乘」时间小于平均值，那大概率说明在它的极小位，有一些 $d$ 在这些位为 $1$。

计算出每一位在它作为极小位时，单次询问「他乘」的时间小于平均值的概率。那么概率越高，说明 $d$ 越有可能在这一位是 $1$。

但是这应该还是过不了，需要加一些优化：因为对于一次询问，如果它的极小位非常多，那很大概率是其它位使得这一位的时间小于平均值，所以我们计算加权概率，一个询问的权值是它极小位数量的倒数。

最后直接从概率大到小 dfs，如果前面计算了 popcount 就用 popcount 剪枝，没有就算了，跑出一个答案就 check 一下，如果合法就输出，没有就继续 dfs，大概 500 次左右就能跑出一个正确答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace {
using ld = long double;
using ll = long long;
mt19937_64 rnd(5201314);
int cnt, l, num, coef[30000];
ll mod, lim, X[30000], ans[30000], Y[30000];
ld expect_len;
vector<int> small[60];
vector<pair<ld, int>> bit;

ll len(ll x) { return x ? __lg(x) + 2 : 1; }

void dfs(int x, ll y) {
    if (y >= mod) return;
    if (__builtin_popcountll(y) > l) return;
    if (x >= 60) {
        if (__builtin_popcountll(y) != l) return;
        for (int i = 0; i < 10; i++) {
            ll r = 1, a = X[i], ti = 0;
            for (int j = 0; j < 60; j++) {
                if (y & (1ll << j)) ti += len(r) * len(a), r = (__int128)r * a % mod;
                ti += len(a) * len(a), a = (__int128)a * a % mod;
            }
            if (ti != ans[i]) return;
        }
        printf("! %lld\n", y);
        fflush(stdout);
        exit(0);
    }
    dfs(x + 1, y | (1ll << bit[x].second));
    dfs(x + 1, y);
}

void entry() {
    scanf("%lld", &mod);

    lim = mod / 64;

    // 获取随机数的期望长度
    expect_len = 2;
    for (ll x = 2; x < mod; x <<= 1) expect_len += 1.0 * (mod - x) / mod;

    // 获取 d 的 popcnt
    vector<pair<ll, int>> popcnt;
    for (int j = 0; j < 60; j++) popcnt.emplace_back(0, j);
    for (int i = 0; i < 1000; i++) {
        ll x = rnd() % mod;
        printf("? %lld\n", x);
        fflush(stdout);
        ll ti;
        scanf("%lld", &ti);
        cnt++;
        for (int j = 1; j < 60; j++) {
            popcnt[j].first += abs(ti - expect_len * expect_len * 60 - expect_len * expect_len * (j - 1) - expect_len * 2);
        }
    }
    sort(popcnt.begin(), popcnt.end());
    l = popcnt[1].second;

    // 随机 x 计算出他乘期望
    for (int i = 0; cnt < 30000; i++) {
        X[i] = rnd() % mod;
        ll x = X[i];
        printf("? %lld\n", x);
        fflush(stdout);
        cnt++;
        scanf("%lld", &ans[i]);
        ll sum = 0;
        for (int j = 0; j < 60; j++) {
            if (x < lim) small[j].push_back(i), coef[i]++;
            sum += 1ll * len(x) * len(x);
            x = (__int128)x * x % mod;
        }
        Y[i] = ans[i] - sum;
        if (coef[i] == 0) i--;
        num = i;
    }

    // 他乘期望
    ld sum = 0;
    for (int i = 0; i < num; i++) sum += Y[i];
    sum /= num;

    // 计算每一位的概率
    for (int j = 0; j < 60; j++) {
        ld num = 0, den = 0;
        for (int i : small[j]) {
            den += 1.0l / coef[i];
            if (Y[i] < sum) num += 1.0l / coef[i];
        }
        bit.emplace_back(num / den, j);
    }

    sort(bit.begin(), bit.end(), greater<pair<ld, int>>());

    dfs(0, 0);
}
}
int main() { entry(); }
```

---

