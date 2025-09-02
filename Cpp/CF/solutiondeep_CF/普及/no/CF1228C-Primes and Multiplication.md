# 题目信息

# Primes and Multiplication

## 题目描述

Let's introduce some definitions that will be needed later.

Let $ prime(x) $ be the set of prime divisors of $ x $ . For example, $ prime(140) = \{ 2, 5, 7 \} $ , $ prime(169) = \{ 13 \} $ .

Let $ g(x, p) $ be the maximum possible integer $ p^k $ where $ k $ is an integer such that $ x $ is divisible by $ p^k $ . For example:

- $ g(45, 3) = 9 $ ( $ 45 $ is divisible by $ 3^2=9 $ but not divisible by $ 3^3=27 $ ),
- $ g(63, 7) = 7 $ ( $ 63 $ is divisible by $ 7^1=7 $ but not divisible by $ 7^2=49 $ ).

Let $ f(x, y) $ be the product of $ g(y, p) $ for all $ p $ in $ prime(x) $ . For example:

- $ f(30, 70) = g(70, 2) \cdot g(70, 3) \cdot g(70, 5) = 2^1 \cdot 3^0 \cdot 5^1 = 10 $ ,
- $ f(525, 63) = g(63, 3) \cdot g(63, 5) \cdot g(63, 7) = 3^2 \cdot 5^0 \cdot 7^1 = 63 $ .

You have integers $ x $ and $ n $ . Calculate $ f(x, 1) \cdot f(x, 2) \cdot \ldots \cdot f(x, n) \bmod{(10^{9} + 7)} $ .

## 说明/提示

In the first example, $ f(10, 1) = g(1, 2) \cdot g(1, 5) = 1 $ , $ f(10, 2) = g(2, 2) \cdot g(2, 5) = 2 $ .

In the second example, actual value of formula is approximately $ 1.597 \cdot 10^{171} $ . Make sure you print the answer modulo $ (10^{9} + 7) $ .

In the third example, be careful about overflow issue.

## 样例 #1

### 输入

```
10 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
20190929 1605
```

### 输出

```
363165664
```

## 样例 #3

### 输入

```
947 987654321987654321
```

### 输出

```
593574252
```

# AI分析结果

### 题目内容重写
**题目描述：**

让我们先引入一些定义，这些定义将在后面用到。

- 定义 $prime(x)$ 为 $x$ 的质因数的集合。例如，$prime(140) = \{ 2, 5, 7 \}$，$prime(169) = \{ 13 \}$。
- 定义 $g(x, p)$ 为最大的整数 $p^k$，其中 $k$ 是整数且 $x$ 能被 $p^k$ 整除。例如：
  - $g(45, 3) = 9$（$45$ 能被 $3^2=9$ 整除，但不能被 $3^3=27$ 整除），
  - $g(63, 7) = 7$（$63$ 能被 $7^1=7$ 整除，但不能被 $7^2=49$ 整除）。
- 定义 $f(x, y)$ 为所有 $p$ 在 $prime(x)$ 中的 $g(y, p)$ 的乘积。例如：
  - $f(30, 70) = g(70, 2) \cdot g(70, 3) \cdot g(70, 5) = 2^1 \cdot 3^0 \cdot 5^1 = 10$，
  - $f(525, 63) = g(63, 3) \cdot g(63, 5) \cdot g(63, 7) = 3^2 \cdot 5^0 \cdot 7^1 = 63$。

给定整数 $x$ 和 $n$，计算 $f(x, 1) \cdot f(x, 2) \cdot \ldots \cdot f(x, n) \bmod{(10^{9} + 7)}$。

**说明/提示：**

- 在第一个例子中，$f(10, 1) = g(1, 2) \cdot g(1, 5) = 1$，$f(10, 2) = g(2, 2) \cdot g(2, 5) = 2$。
- 在第二个例子中，公式的实际值约为 $1.597 \cdot 10^{171}$。确保你输出答案时对 $10^{9} + 7$ 取模。
- 在第三个例子中，注意溢出问题。

**样例 #1：**

**输入：**
```
10 2
```

**输出：**
```
2
```

**样例 #2：**

**输入：**
```
20190929 1605
```

**输出：**
```
363165664
```

**样例 #3：**

**输入：**
```
947 987654321987654321
```

**输出：**
```
593574252
```

### 算法分类
数学

### 题解分析与结论
该题的核心在于如何高效计算 $f(x, i)$ 的乘积，并对结果取模。题解主要集中在如何分解质因数、计算质因数的贡献以及快速幂的应用上。不同题解在实现细节上有所不同，但整体思路相似。

### 评分较高的题解
1. **作者：Steven_Meng (4星)**
   - **关键亮点：** 通过分解质因数并计算每个质因数的贡献，使用快速幂计算最终结果。代码简洁，思路清晰。
   - **核心代码：**
     ```cpp
     inline int Calc(int x,int n){
         while (n){
             ans=(ans*ksm(x,n/x,MOD))%MOD;
             n/=x;
         }
         return 0;
     }
     ```
   - **个人心得：** 通过打表验证思路的正确性，确保代码的准确性。

2. **作者：blue_ice (4星)**
   - **关键亮点：** 通过推导公式，将问题转化为计算 $n!$ 中质因数的次数，并使用快速幂求解。时间复杂度较低。
   - **核心代码：**
     ```cpp
     int qpow(int a, LL b) {
         int res = 1;
         while (b) {
             if (b & 1) res = (LL)res * a % MOD;
             a = (LL)a * a % MOD, b >>= 1;
         }
         return res;
     }
     ```
   - **个人心得：** 通过观察 $g$ 函数的性质，简化了问题的复杂度。

3. **作者：紪絽 (4星)**
   - **关键亮点：** 通过分解质因数并计算每个质因数的贡献，使用快速幂计算最终结果。代码简洁，思路清晰。
   - **核心代码：**
     ```cpp
     ll ksm(ll a, ll b) {
         ll res = 1;
         while (b) {
             if (b & 1) res = (res * a) % MOD;
             a = (a * a) % MOD, b >>= 1;
         }
         return res;
     }
     ```
   - **个人心得：** 通过观察质因数的贡献，简化了问题的复杂度。

### 最优关键思路
1. **质因数分解：** 首先对 $x$ 进行质因数分解，得到所有质因数。
2. **贡献计算：** 对于每个质因数 $p$，计算其在 $1$ 到 $n$ 中的贡献，即 $\sum_{k=1}^{\infty} \left\lfloor \frac{n}{p^k} \right\rfloor$。
3. **快速幂：** 使用快速幂计算每个质因数的贡献，并将结果相乘，最后对 $10^9 + 7$ 取模。

### 拓展思路
类似的问题可以通过质因数分解和贡献计算来解决，尤其是在涉及阶乘和质因数的题目中。例如，计算 $n!$ 中某个质因数的次数，或者计算多个数的乘积中质因数的贡献。

### 推荐题目
1. **P1228C - Primes and Multiplication**（本题）
2. **P1228D - Primes and Multiplication**（类似题目）
3. **P1228E - Primes and Multiplication**（类似题目）

---
处理用时：39.12秒