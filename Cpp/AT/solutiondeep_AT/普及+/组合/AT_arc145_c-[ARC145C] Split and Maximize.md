# 题目信息

# [ARC145C] Split and Maximize

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc145/tasks/arc145_c

$ (1,2,\ldots,2N) $ の順列 $ P=(P_1,P_2,\ldots,P_{2N}) $ に対し、スコアを以下で定義します。

> $ P $ を順序を保ったまま二つの長さ $ N $ の（連続するとは限らない）部分列 $ A\ =\ (A_1,A_2,\ldots,A_N),B\ =\ (B_1,B_2,\ldots,B_N) $ に分割する。分割を行ったときに得られる $ \displaystyle\sum_{i=1}^{N}A_i\ B_i $ の最大値をスコアとする。

$ (1,2,\ldots,2N) $ の順列全てについてスコアを計算し、それらの最大値を $ M $ とします。 $ (1,2,\ldots,2N) $ の順列のうち、スコアが $ M $ であるものの個数を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- 入力は全て整数

### Sample Explanation 1

考えられる順列 $ 24 $ 通りの中で、スコアの最大値 $ M $ は $ 14 $ です。スコアが $ 14 $ となる順列は $ 16 $ 通りあります。 例えば、順列 $ (1,2,3,4) $ は $ A=(1,3),\ B=(2,4) $ と分割することで、$ \sum\ _{i=1}^{N}A_i\ B_i\ =\ 14 $ となります。

### Sample Explanation 2

$ 998244353 $ で割ったあまりを答えてください。

## 样例 #1

### 输入

```
2```

### 输出

```
16```

## 样例 #2

### 输入

```
10000```

### 输出

```
391163238```

# AI分析结果

### 题目翻译
对于排列 $P=(P_1,P_2,\ldots,P_{2N})$（其中 $P$ 是 $(1,2,\ldots,2N)$ 的一个排列），定义其得分如下：

将 $P$ 按顺序划分为两个长度为 $N$ 的（不一定连续的）子序列 $A = (A_1,A_2,\ldots,A_N)$ 和 $B = (B_1,B_2,\ldots,B_N)$。划分后，$\displaystyle\sum_{i = 1}^{N}A_iB_i$ 的最大值即为该排列的得分。

计算 $(1,2,\ldots,2N)$ 的所有排列的得分，并将其中的最大值记为 $M$。请计算 $(1,2,\ldots,2N)$ 的排列中得分等于 $M$ 的排列个数，将结果对 $998244353$ 取模后输出。

### 综合分析与结论
这些题解的核心思路都是先确定使 $\sum_{i = 1}^{N}A_iB_i$ 最大的配对方式，即相邻两个数配对（$|A_i - B_i| = 1$），然后通过计数原理来计算满足最大得分的排列个数。具体步骤包括：确定最优配对方式、分析排列的变化情况（如交换对子顺序、交换对子内元素），最后利用卡特兰数计算满足特定条件的排列个数。

### 所选题解
- **liangbowen（5星）**
    - **关键亮点**：思路清晰，先给出了一种有趣的“猜结论”思路，然后对最优配对方式进行了严格证明，最后详细阐述了计数的各个部分，逻辑连贯。
    - **个人心得**：无
- **hhhqx（4星）**
    - **关键亮点**：对题意和做法的解释较为详细，通过引入二元组序列 $C$ 来辅助理解，最后给出了完整的代码实现。
    - **个人心得**：蒟蒻第一次写卡特兰数的题解，如果有问题希望能被指正！
- **xukehg（4星）**
    - **关键亮点**：从数学原理出发，通过展开式子说明最优配对方式，然后将问题转化为合法括号匹配序列的个数问题，解释通俗易懂。
    - **个人心得**：隔壁 liangbowen 大佬的题解整体上有一些难以理解（可能是我太菜了），本篇题解更倾向与方便像我一样菜的人理解题解。

### 重点代码
#### liangbowen 核心思路
```plaintext
1. 证明 |A_i - B_i| = 1 最优。
2. 交换 (A_i,B_i) 与 (A_j,B_j) 方案数 n!。
3. 交换 A_i 与 B_i 方案数 2^n。
4. 满足条件的序列是卡特兰数，总答案为这些结果相乘。
```

#### hhhqx 核心代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const LL mod = 998244353;
const int MAXN = 4e5 + 3;

LL qpow(LL A, LL B){
    LL ret = 1;
    while(B > 0){
        if(B & 1) ret = ret * A % mod;
        A = A * A % mod, B >>= 1;
    }
    return ret;
}

LL fac[MAXN], ifac[MAXN];
int n, m;

LL C(int A, int B){ return fac[B] * ifac[A] % mod * ifac[B - A] % mod; }
LL Catalan(int A){ return (C(A, A + A) - C(A - 1, A + A) + mod) % mod; }

int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    fac[0] = ifac[0] = 1;
    for(int i = 1; i <= 4e5; i++) fac[i] = fac[i - 1] * i % mod, ifac[i] = qpow(fac[i], mod - 2);
    cin >> n;
    cout << qpow(2, n) * fac[n] % mod * Catalan(n) % mod;
    return 0;
}
```
**核心实现思想**：先预处理阶乘和阶乘的逆元，然后计算卡特兰数，最后根据计数原理计算最终答案。

#### xukehg 核心代码
```cpp
#include<bits/stdc++.h>
#define int long long
const int N = 5e6 + 5,mod = 998244353;
using namespace std;

int n,ans = 0;
int fac[N],ifac[N],f[N];
int qpow(int a,int b) {
    int cnt = 1;
    while (b) {
        if (b & 1) cnt = cnt % mod * a % mod;
        a = a % mod * a % mod;
        b >>= 1;
    }
    return cnt;
}
int C(int n,int m) {
    if (n < 0 || m < 0 || n - m < 0) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int inv(int x) {
    return qpow(x,mod - 2);
}
signed main() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[N] = qpow(fac[N],mod - 2);
    for (int i = N - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    cin >> n;
    cout << fac[n] * qpow(2,n) % mod * inv(n + 1) % mod* C(2 * n,n) % mod;
}
```
**核心实现思想**：预处理阶乘和阶乘的逆元，计算卡特兰数，根据计数原理计算最终答案。

### 最优关键思路或技巧
- **数学证明**：通过数学推导证明相邻两个数配对能使 $\sum_{i = 1}^{N}A_iB_i$ 最大。
- **问题转化**：将满足条件的排列问题转化为合法括号匹配序列问题，利用卡特兰数求解。
- **计数原理**：分析排列的不同变化情况，利用乘法原理计算最终的排列个数。

### 可拓展之处
同类型题目可能会涉及不同的配对规则或得分计算方式，但解题思路通常是先确定最优方案，然后通过计数原理和组合数学知识来计算满足条件的方案数。类似的算法套路包括利用卡特兰数解决具有特定顺序要求的组合问题，如栈的进出问题、二叉树的计数问题等。

### 洛谷相似题目
1. [P3200 有趣的数列](https://www.luogu.com.cn/problem/P3200)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1754 球迷购票问题](https://www.luogu.com.cn/problem/P1754)

---
处理用时：40.29秒