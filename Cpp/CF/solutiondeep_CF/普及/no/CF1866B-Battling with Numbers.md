# 题目信息

# Battling with Numbers

## 题目描述

On the trip to campus during the mid semester exam period, Chaneka thinks of two positive integers $ X $ and $ Y $ . Since the two integers can be very big, both are represented using their prime factorisations, such that:

- $ X=A_1^{B_1}\times A_2^{B_2}\times\ldots\times A_N^{B_N} $ (each $ A_i $ is prime, each $ B_i $ is positive, and $ A_1<A_2<\ldots<A_N $ )
- $ Y=C_1^{D_1}\times C_2^{D_2}\times\ldots\times C_M^{D_M} $ (each $ C_j $ is prime, each $ D_j $ is positive, and $ C_1<C_2<\ldots<C_M $ )

Chaneka ponders about these two integers for too long throughout the trip, so Chaneka's friend commands her "Gece, deh!" (move fast) in order to not be late for the exam.

Because of that command, Chaneka comes up with a problem, how many pairs of positive integers $ p $ and $ q $ such that $ \text{LCM}(p, q) = X $ and $ \text{GCD}(p, q) = Y $ . Since the answer can be very big, output the answer modulo $ 998\,244\,353 $ .

Notes:

- $ \text{LCM}(p, q) $ is the smallest positive integer that is simultaneously divisible by $ p $ and $ q $ .
- $ \text{GCD}(p, q) $ is the biggest positive integer that simultaneously divides $ p $ and $ q $ .

## 说明/提示

In the first example, the integers are as follows:

- $ X=2^2\times3^1\times5^1\times7^2=2940 $
- $ Y=3^1\times7^1=21 $

The following are all possible pairs of $ p $ and $ q $ :

- $ p=21 $ , $ q=2940 $
- $ p=84 $ , $ q=735 $
- $ p=105 $ , $ q=588 $
- $ p=147 $ , $ q=420 $
- $ p=420 $ , $ q=147 $
- $ p=588 $ , $ q=105 $
- $ p=735 $ , $ q=84 $
- $ p=2940 $ , $ q=21 $

In the third example, the integers are as follows:

- $ X=2^1\times5^1=10 $
- $ Y=2^1\times3^1=6 $

There is no pair $ p $ and $ q $ that simultaneously satisfies $ \text{LCM}(p,q)=10 $ and $ \text{GCD}(p,q)=6 $ .

## 样例 #1

### 输入

```
4
2 3 5 7
2 1 1 2
2
3 7
1 1```

### 输出

```
8```

## 样例 #2

### 输入

```
2
1299721 1999993
100000 265
2
1299721 1999993
100000 265```

### 输出

```
1```

## 样例 #3

### 输入

```
2
2 5
1 1
2
2 3
1 1```

### 输出

```
0```

# AI分析结果

### 题目内容重写
# 数字之战

## 题目描述

在期中考试期间前往校园的路上，Chaneka想到了两个正整数 $X$ 和 $Y$。由于这两个整数可能非常大，它们都以质因数分解的形式表示，如下所示：

- $X=A_1^{B_1}\times A_2^{B_2}\times\ldots\times A_N^{B_N}$（每个 $A_i$ 是质数，每个 $B_i$ 是正整数，且 $A_1<A_2<\ldots<A_N$）
- $Y=C_1^{D_1}\times C_2^{D_2}\times\ldots\times C_M^{D_M}$（每个 $C_j$ 是质数，每个 $D_j$ 是正整数，且 $C_1<C_2<\ldots<C_M$）

Chaneka在旅途中思考这两个整数太久，因此她的朋友命令她“Gece, deh！”（快点），以免考试迟到。

由于这个命令，Chaneka提出了一个问题：有多少对正整数 $p$ 和 $q$ 满足 $\text{LCM}(p, q) = X$ 且 $\text{GCD}(p, q) = Y$。由于答案可能非常大，输出答案模 $998\,244\,353$。

注释：

- $\text{LCM}(p, q)$ 是同时能被 $p$ 和 $q$ 整除的最小正整数。
- $\text{GCD}(p, q)$ 是同时能整除 $p$ 和 $q$ 的最大正整数。

## 说明/提示

在第一个例子中，整数如下：

- $X=2^2\times3^1\times5^1\times7^2=2940$
- $Y=3^1\times7^1=21$

以下是所有可能的 $p$ 和 $q$ 对：

- $p=21$，$q=2940$
- $p=84$，$q=735$
- $p=105$，$q=588$
- $p=147$，$q=420$
- $p=420$，$q=147$
- $p=588$，$q=105$
- $p=735$，$q=84$
- $p=2940$，$q=21$

在第三个例子中，整数如下：

- $X=2^1\times5^1=10$
- $Y=2^1\times3^1=6$

没有满足 $\text{LCM}(p,q)=10$ 且 $\text{GCD}(p,q)=6$ 的 $p$ 和 $q$ 对。

## 样例 #1

### 输入

```
4
2 3 5 7
2 1 1 2
2
3 7
1 1```

### 输出

```
8```

## 样例 #2

### 输入

```
2
1299721 1999993
100000 265
2
1299721 1999993
100000 265```

### 输出

```
1```

## 样例 #3

### 输入

```
2
2 5
1 1
2
2 3
1 1```

### 输出

```
0```

### 算法分类
数学

### 题解分析与结论
题目要求计算满足 $\text{LCM}(p, q) = X$ 且 $\text{GCD}(p, q) = Y$ 的正整数对 $(p, q)$ 的数量。核心思路是利用 $\text{LCM}$ 和 $\text{GCD}$ 的性质，将问题转化为对 $X$ 和 $Y$ 的质因数分解的处理。

各题解的思路基本一致，主要步骤如下：
1. 检查 $X$ 是否是 $Y$ 的倍数，如果不是则直接输出 $0$。
2. 对于每个质因数，根据其在 $X$ 和 $Y$ 中的指数关系，决定是否可以将该质因数的指数分配给 $p$ 或 $q$。
3. 如果某个质因数在 $X$ 中的指数大于在 $Y$ 中的指数，则有两种分配方式（全给 $p$ 或全给 $q$），否则只有一种方式。
4. 最终答案是将所有质因数的分配方式相乘，结果模 $998\,244\,353$。

### 高星题解
#### 题解1：作者：One_JuRuo (4星)
**关键亮点**：
- 思路清晰，代码简洁。
- 使用 `map` 存储质因数及其指数，便于处理。

**核心代码**：
```cpp
for(auto i:p2)
{
    if(p1[i.first]<i.second) printf("0"),exit(0);
    if(p1[i.first]-i.second) ans=ans*2%mod;
    p1[i.first]=0;
}
for(auto i:p1)
{
    if(i.second) ans=ans*2%mod;
}
```

#### 题解2：作者：Falling_Sakura (4星)
**关键亮点**：
- 详细解释了 $\text{LCM}$ 和 $\text{GCD}$ 的性质。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(auto &i : s)
{
    if(s1[i] < s2[i])
    {
        cout << 0 << endl;
        return 0;
    }
    else if(s1[i] == s2[i]) continue;
    else ans = ans * 2 % MOD;
}
```

#### 题解3：作者：Czy_Lemon (4星)
**关键亮点**：
- 详细分析了质因数的分配方式。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
for(int i=1;i<=n;i++)
    if(pf[a[i]]>qf[a[i]])
        ans=ans*2%mod;
```

### 最优关键思路
1. **质因数分解**：利用质因数分解的性质，将问题转化为对每个质因数的指数处理。
2. **分配方式**：对于每个质因数，根据其在 $X$ 和 $Y$ 中的指数关系，决定分配方式。
3. **模运算**：最终结果需要对 $998\,244\,353$ 取模，避免大数问题。

### 可拓展之处
类似的问题可以扩展到多个数的 $\text{LCM}$ 和 $\text{GCD}$ 计算，或者结合其他数论知识进行更复杂的处理。

### 推荐题目
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)
3. [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)

---
处理用时：40.87秒