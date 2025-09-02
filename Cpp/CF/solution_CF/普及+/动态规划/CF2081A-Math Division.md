# Math Division

## 题目描述

Ecrade 有一个整数 $x$。他将以长度为 $n$ 的二进制数的形式向你展示这个数。

存在两种操作：
1. 将 $x$ 替换为 $\left\lfloor \frac{x}{2}\right\rfloor$，其中 $\left\lfloor \frac{x}{2}\right\rfloor$ 是小于等于 $\frac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \frac{x}{2}\right\rceil$，其中 $\left\lceil \frac{x}{2}\right\rceil$ 是大于等于 $\frac{x}{2}$ 的最小整数。

Ecrade 将执行若干次操作直到 $x$ 变为 $1$。每次操作时，他会独立地以 $\frac{1}{2}$ 的概率选择执行第一种操作或第二种操作。

Ecrade 想知道他将执行的操作次数的期望值（模 $10^9 + 7$）。由于问题有一定难度，请你帮助他！

## 说明/提示

为简化描述，我们将第一种操作称为 $\text{OPER 1}$，第二种操作称为 $\text{OPER 2}$。

第一个测试用例中，$x=6$，存在六种可能的操作序列：
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。

因此，操作次数的期望为 $2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} + 2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} = \dfrac{5}{2} \equiv 500\,000\,006 \pmod{10^9 + 7}$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3
110
3
100
10
1101001011```

### 输出

```
500000006
2
193359386```

# 题解

## 作者：WanderOvO (赞：1)

# 【期望DP】CF2081A Math Division

## 题意

Ecrade 有一个整数 $x$。他将以长度为 $n$ 的二进制数的形式向你展示这个数。

存在两种操作：

1. 将 $x$ 替换为 $\left\lfloor \frac{x}{2}\right\rfloor$，其中 $\left\lfloor \frac{x}{2}\right\rfloor$ 是小于等于 $\frac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \frac{x}{2}\right\rceil$，其中 $\left\lceil \frac{x}{2}\right\rceil$ 是大于等于 $\frac{x}{2}$ 的最小整数。

Ecrade 将执行若干次操作直到 $x$ 变为 $1$。每次操作时，他会独立地以 $\frac{1}{2}$ 的概率选择执行第一种操作或第二种操作。问期望操作多少次才能变成 $1$，答案需要模 $10^9 + 7$。

## 思路

按照期望 DP 的常用做法，容易想到考虑目前只剩下 $x$ 的高 $i$ 位需要处理时，还需要操作多少次才能变成 $1$。

但是目前 $x$ 的高 $i$ 位不一定是原字符串中的前 $i$ 位了，因为前面可能有进位。不过通过手玩一些数据可以发现，$x$ 的高 $i$ 位在受到低位向上取整进位影响的情况下只会恰好比原来的串 $+1$。

举个例子，对于串 $101011$，在考虑只剩前 $3$ 位的情况下还需要多少次才能变成 $1$ 时，前 $3$ 位只可能是 $101$ 或者 $101 + 1 = 110$。

我们设：
- $dp[i][0]$ 表示目前还需要处理 $x$ 的高 $i$ 位，且 $x$ 的高 $i$ 位目前**没有受到低位进位的影响**时，还期望需要多少次操作变成 $1$。
- $dp[i][1]$ 表示目前还需要处理 $x$ 的高 $i$ 位，且 $x$ 的高 $i$ 位**受到了低位向上取整进位的影响**，变成了原串高 $i$ 位的值 $+1$，还期望需要多少次操作变成 $1$。

初始化显然有 $dp[1][0] = 0, dp[1][1] = 1$。

下面考虑转移方程：

- 如果第 $i$ 位原串中为 $0$，则有：
  - $dp[i][0] = dp[i - 1][0] + 1$，因为 $dp[i][0]$ 状态下这时候末位是 $0$，不管向上还是向下取整都不会导致进位。
  - $dp[i][1] = \frac{1}{2}\times(dp[i - 1][0] + dp[i - 1][1]) + 1$，因为在 $dp[i][1]$ 状态下末位为 $1$，向下取整则转移到 $dp[i - 1][0]$，向上取整则转移到 $dp[i - 1][1]$。
- 如果第 $i$ 位原串中为 $1$，则有：
  - $dp[i][0] = \frac{1}{2}\times(dp[i - 1][0] + dp[i - 1][1]) + 1$，因为这个时候末位是 $1$ 了，所以向下取整则转移到 $dp[i - 1][0]$，向上取整则转移到 $dp[i - 1][1]$。
  - $dp[i][1] = dp[i - 1][1] + 1$，因为原串中末位已经是 $1$ 了，所以在 $dp[i][1]$ 状态下相当于又加了 $1$，直接进位了，所以只会转移到 $dp[i - 1][1]$。

最后的答案就是 $dp[n][0]$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

typedef long long LL;

int n;
string s;
LL dp[N][2];

LL qpow(LL a, LL b, LL MOD) {
    LL res = 1, base = a;
    while (b) {
        if (b & 1) {
            res = res * base % MOD;
        }
        base = base * base % MOD;
        b >>= 1;
    }
    return res % MOD;
}

void solve() {
    cin >> n >> s;
    s = " " + s;
    int mod = 1e9 + 7;
    dp[1][0] = 0;
    dp[1][1] = 1;
    LL inv2 = qpow(2, mod - 2, mod);
    for (int i = 2; i <= n; i++) {
        if (s[i] == '0') {
            dp[i][0] = (dp[i - 1][0] + 1) % mod;
            dp[i][1] = ((dp[i - 1][0] + dp[i - 1][1]) * inv2 % mod + 1) % mod;
        } else {
            dp[i][0] = ((dp[i - 1][0] + dp[i - 1][1]) * inv2 % mod + 1) % mod;
            dp[i][1] = (dp[i - 1][1] + 1) % mod;
        }
    }
    cout << dp[n][0] << "\n";
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

根据 CF2082B 的结论，操作次数只能是 $n-1$ 或 $n$，因为最高位最多产生 $1$ 的进位。

那么我们只用看最后一位是否进位即可。

我们设 $f_i$ 为在 $i$ 位进位的概率，初始有 $f_0=0$。

很显然，有转移方程：

$$f_i=\begin{cases}\frac12\times f_{i-1}&x_i=0 \\ \frac12\times (1-f_{i-1})+f_{i-1}&x_i=1\end{cases}$$

最后答案为 $n-1+f_{n-1}$。

---

