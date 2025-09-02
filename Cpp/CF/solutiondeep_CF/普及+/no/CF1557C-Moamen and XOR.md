# 题目信息

# Moamen and XOR

## 题目描述

Moamen and Ezzat are playing a game. They create an array $ a $ of $ n $ non-negative integers where every element is less than $ 2^k $ .

Moamen wins if $ a_1 \,\&\, a_2 \,\&\, a_3 \,\&\, \ldots \,\&\, a_n \ge a_1 \oplus a_2 \oplus a_3 \oplus \ldots \oplus a_n $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Please calculate the number of winning for Moamen arrays $ a $ .

As the result may be very large, print the value modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

In the first example, $ n = 3 $ , $ k = 1 $ . As a result, all the possible arrays are $ [0,0,0] $ , $ [0,0,1] $ , $ [0,1,0] $ , $ [1,0,0] $ , $ [1,1,0] $ , $ [0,1,1] $ , $ [1,0,1] $ , and $ [1,1,1] $ .

Moamen wins in only $ 5 $ of them: $ [0,0,0] $ , $ [1,1,0] $ , $ [0,1,1] $ , $ [1,0,1] $ , and $ [1,1,1] $ .

## 样例 #1

### 输入

```
3
3 1
2 1
4 0```

### 输出

```
5
2
1```

# AI分析结果

### 题目翻译
# Moamen 和异或运算

## 题目描述
Moamen 和 Ezzat 在玩一个游戏。他们创建一个包含 $n$ 个非负整数的数组 $a$，其中每个元素都小于 $2^k$。
如果 $a_1 \,\&\, a_2 \,\&\, a_3 \,\&\, \ldots \,\&\, a_n \ge a_1 \oplus a_2 \oplus a_3 \oplus \ldots \oplus a_n$，则 Moamen 获胜。
这里 $\&$ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)，$\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。
请计算 Moamen 获胜的数组 $a$ 的数量。
由于结果可能非常大，请将值对 $1\,000\,000\,007$（$10^9 + 7$）取模后输出。

## 说明/提示
在第一个示例中，$n = 3$，$k = 1$。因此，所有可能的数组为 $[0,0,0]$，$[0,0,1]$，$[0,1,0]$，$[1,0,0]$，$[1,1,0]$，$[0,1,1]$，$[1,0,1]$ 和 $[1,1,1]$。
Moamen 仅在其中 5 个数组中获胜：$[0,0,0]$，$[1,1,0]$，$[0,1,1]$，$[1,0,1]$ 和 $[1,1,1]$。

## 样例 #1
### 输入
```
3
3 1
2 1
4 0
```
### 输出
```
5
2
1
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是按二进制位分别考虑，通过组合数学的方法计算满足条件的数组个数。不同题解在具体实现和分类讨论的方式上有所差异，但都围绕 $n$ 的奇偶性展开。

在思路方面，大部分题解都将情况分为 $n$ 为奇数和偶数两种情况讨论，对于 $n$ 为奇数时，$\text{and}$ 结果大于 $\text{xor}$ 结果的情况不存在，主要考虑相等的情况；对于 $n$ 为偶数时，需要分别计算 $\text{and}$ 结果等于和大于 $\text{xor}$ 结果的情况。

算法要点上，各题解都用到了组合数的计算，部分题解还使用了快速幂来优化计算过程，以处理较大的指数。

解决的难点在于准确分析不同情况下每一位的取值组合，以及如何通过组合数和快速幂计算出满足条件的方案数，同时要注意取模操作以避免溢出。

### 所选题解
- **作者：SDqwq (赞：18)，4星**
    - **关键亮点**：思路清晰，对按位分析的过程和两种情况的讨论详细，代码实现规范，使用了快速幂和组合数的模板。
    - **个人心得**：赛时因为和 @[Leasier](https://www.luogu.com.cn/user/201007) 聊天导致没写完代码。
- **作者：zhiyangfan (赞：10)，4星**
    - **关键亮点**：通过表格清晰呈现不同情况下 $\text{and}$ 和 $\text{xor}$ 的结果，方便理解，对 $n$ 为偶数时使用补集转换的方法，思路巧妙。
    - **个人心得**：结束前 5 秒过了样例，没交上去。
- **作者：Leasier (赞：2)，4星**
    - **关键亮点**：使用动态规划的思想，通过定义状态 $dp_{i, j}$ 来表示从第 $0$ 位到第 $i$ 位构造原数组的方法数，转移方程明确。
    - **个人心得**：做了这道题才知道自己不会数数，甚至不配数数。

### 重点代码
#### SDqwq 的代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll fac[200005];
inline void init(ll n) {
    fac[0] = 1;
    for (ll i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % mod;
}
inline ll quick_pow(ll a, ll k, ll p) {
    ll res = 1;
    a %= p;
    while (k) {
        if (k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}
inline ll inv(ll x, ll p) {return quick_pow(x, p - 2, p);}
inline ll getC(ll n, ll m, ll p) {return fac[n] * inv(fac[n - m] * fac[m] % p, p) % p;}

int main() {
    init(2e5);
    int T;
    scanf("%d", &T);
    while (T--) {
        ll n, k, ans = 0, sum = 0;
        scanf("%lld %lld", &n, &k);
        for (ll i = 0; i < n; i += 2) sum = (sum + getC(n, i, mod)) % mod;
        if (n & 1) ans = (ans + quick_pow(sum + 1, k, mod)) % mod;
        else {
            for (ll i = 0; i < k; i++) ans = (ans + quick_pow(sum, i, mod) * quick_pow(quick_pow(2, n, mod), k - i - 1, mod) % mod) % mod;
            ans = (ans + quick_pow(sum, k, mod)) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```
**核心实现思想**：先预处理阶乘，然后根据 $n$ 的奇偶性分类讨论，计算满足条件的方案数，使用快速幂和组合数进行计算，并对结果取模。

#### zhyangfan 的代码
```cpp
#include <cstdio>
const int mod = 1e9 + 7, N = 2e5 + 10; int fac[N], ifac[N];
inline int ksm(int a, int b)
{
    int ret = 1;
    while (b)
    {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return ret;
}
inline int C(int a, int b) { return 1ll * fac[a] * ifac[b] % mod * ifac[a - b] % mod;  }
int main()
{
    int T; scanf("%d", &T); fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[N - 1] = ksm(fac[N - 1], mod - 2);
    for (int i = N - 2; i >= 1; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
    while (T--)
    {
        int n, k; scanf("%d%d", &n, &k);
        if (n & 1)
        {
            int tmp = 1;
            for (int i = 1; i <= (n + 1) / 2; i++)
                tmp = (tmp + C(n, 2 * i - 1)) % mod;
            printf("%d\n", ksm(tmp, k));
        }
        else
        {
            int tmp = 0, t1 = 0, t2 = 0;
            for (int i = 2; i <= n; i += 2) t1 = (t1 + C(n, i)) % mod;
            for (int i = 1; i <= n; i += 2) t2 = (t2 + C(n, i)) % mod;
            for (int i = 1; i <= k; i++)
                tmp = (tmp + 1ll * t2 * ksm(t1, k - i) % mod * ksm(ksm(2, i - 1), n) % mod) % mod;
            printf("%d\n", (ksm(ksm(2, k), n) - tmp + mod) % mod);
        }
    }
    return 0;
}
```
**核心实现思想**：预处理阶乘和逆元，根据 $n$ 的奇偶性分类讨论，$n$ 为奇数时直接计算每一位的方案数并快速幂求解，$n$ 为偶数时使用补集转换，计算 $\text{and}$ 小于 $\text{xor}$ 的方案数，用总方案数减去该值得到结果。

#### Leasier 的代码
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 2e5 + 7, M = 1 + 7, mod = 1e9 + 7;
ll fac[N], inv_fac[N], dp[N][M];

inline ll quick_pow(ll x, ll p, ll mod){
    ll ans = 1;
    while (p){
        if (p & 1) ans = ans * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ans;
}

inline void init(){
    fac[0] = 1;
    for (int i = 1; i < N; i++){
        fac[i] = fac[i - 1] * i % mod;
    }
    inv_fac[N - 1] = quick_pow(fac[N - 1], mod - 2, mod);
    for (int i = N - 2; i >= 0; i--){
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
    }
}

inline ll comb(ll n, ll m, ll mod){
    if (m == 0) return 1;
    if (m > n) return 0;
    return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int main(){
    int t;
    scanf("%d", &t);
    init();
    for (int i = 1; i <= t; i++){
        int n, k;
        scanf("%d %d", &n, &k);
        if (k == 0){
            printf("1\n");
            continue;
        }
        ll x = 0, ans;
        for (int j = 0; j < n; j += 2){
            x = (x + comb(n, j, mod)) % mod;
        }
        if (n % 2 == 0){
            ll y = quick_pow(2, n, mod);
            dp[0][0] = x;
            dp[0][1] = 1;
            for (int j = 1; j < k; j++){
                dp[j][0] = dp[j - 1][0] * x % mod;
                dp[j][1] = (dp[j - 1][1] * y % mod + dp[j - 1][0]) % mod;
            }
        } else {
            dp[0][0] = x + 1;
            dp[0][1] = 0;
            for (int j = 1; j < k; j++){
                dp[j][0] = dp[j - 1][0] * (x + 1) % mod;
                dp[j][1] = 0;
            }
        }
        printf("%lld\n", (dp[k - 1][0] + dp[k - 1][1]) % mod);
    }
    return 0;
}
```
**核心实现思想**：预处理阶乘和逆元，定义动态规划状态 $dp_{i, j}$ 表示从第 $0$ 位到第 $i$ 位构造原数组的方法数，根据 $n$ 的奇偶性和 $j$ 的取值进行状态转移，最终答案为 $dp_{k - 1, 0} + dp_{k - 1, 1}$。

### 最优关键思路或技巧
- **按位分析**：将问题按二进制位分别考虑，简化问题复杂度。
- **分类讨论**：根据 $n$ 的奇偶性进行分类讨论，使问题更加清晰。
- **组合数和快速幂**：使用组合数计算每一位的方案数，使用快速幂优化指数运算，提高计算效率。

### 可拓展之处
同类型题可能会改变运算规则或条件，例如改变比较的运算符，或者增加更多的数组元素限制等。类似算法套路可以应用在其他涉及二进制运算和组合计数的问题中，如计算满足特定条件的二进制序列个数等。

### 推荐题目
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)
- [P1869 愚蠢的组合数](https://www.luogu.com.cn/problem/P1869)
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)

---
处理用时：133.70秒