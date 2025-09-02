# 题目信息

# Not Adding

## 题目描述

You have an array $ a_1, a_2, \dots, a_n $ consisting of $ n $ distinct integers. You are allowed to perform the following operation on it: 

- Choose two elements from the array $ a_i $ and $ a_j $ ( $ i \ne j $ ) such that $ \gcd(a_i, a_j) $ is not present in the array, and add $ \gcd(a_i, a_j) $ to the end of the array. Here $ \gcd(x, y) $ denotes [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Note that the array changes after each operation, and the subsequent operations are performed on the new array.

What is the maximum number of times you can perform the operation on the array?

## 说明/提示

In the first example, one of the ways to perform maximum number of operations on the array is:

- Pick $ i = 1, j= 5 $ and add $ \gcd(a_1, a_5) = \gcd(4, 30) = 2 $ to the array.
- Pick $ i = 2, j= 4 $ and add $ \gcd(a_2, a_4) = \gcd(20, 25) = 5 $ to the array.
- Pick $ i = 2, j= 5 $ and add $ \gcd(a_2, a_5) = \gcd(20, 30) = 10 $ to the array.

It can be proved that there is no way to perform more than $ 3 $ operations on the original array.

In the second example one can add $ 3 $ , then $ 1 $ , then $ 5 $ , and $ 2 $ .

## 样例 #1

### 输入

```
5
4 20 1 25 30```

### 输出

```
3```

## 样例 #2

### 输入

```
3
6 10 15```

### 输出

```
4```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由 $n$ 个不同整数组成的数组 $a_1, a_2, \dots, a_n$。你可以对数组执行以下操作：

- 选择数组中的两个元素 $a_i$ 和 $a_j$（$i \ne j$），使得 $\gcd(a_i, a_j)$ 不在当前数组中，然后将 $\gcd(a_i, a_j)$ 添加到数组的末尾。这里 $\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的最大公约数。

注意，每次操作后数组会发生变化，后续操作将在新数组上进行。

问：你最多可以执行多少次这样的操作？

#### 说明/提示

在第一个示例中，执行最大操作次数的一种方式如下：

- 选择 $i = 1, j= 5$，并将 $\gcd(a_1, a_5) = \gcd(4, 30) = 2$ 添加到数组中。
- 选择 $i = 2, j= 4$，并将 $\gcd(a_2, a_4) = \gcd(20, 25) = 5$ 添加到数组中。
- 选择 $i = 2, j= 5$，并将 $\gcd(a_2, a_5) = \gcd(20, 30) = 10$ 添加到数组中。

可以证明，在原始数组上无法执行超过 $3$ 次操作。

在第二个示例中，可以依次添加 $3$、$1$、$5$ 和 $2$。

#### 样例 #1

##### 输入

```
5
4 20 1 25 30
```

##### 输出

```
3
```

#### 样例 #2

##### 输入

```
3
6 10 15
```

##### 输出

```
4
```

### 题解分析与结论

#### 综合分析

本题的核心在于如何高效地计算数组中所有可能的 $\gcd$ 数量。由于值域较小（$1 \leq a_i \leq 10^6$），可以通过枚举每个可能的 $\gcd$ 值，并检查其是否可以通过数组中某些元素的 $\gcd$ 得到。具体来说，对于每个可能的 $\gcd$ 值 $x$，检查数组中所有 $x$ 的倍数的 $\gcd$ 是否为 $x$。如果是，则 $x$ 可以通过操作得到。

#### 最优关键思路

1. **枚举 $\gcd$ 值**：由于值域较小，可以枚举每个可能的 $\gcd$ 值 $x$，并检查其是否可以通过数组中某些元素的 $\gcd$ 得到。
2. **检查 $\gcd$ 条件**：对于每个 $x$，计算数组中所有 $x$ 的倍数的 $\gcd$，如果结果为 $x$，则 $x$ 可以通过操作得到。
3. **桶标记法**：使用桶标记法记录数组中每个值是否存在，方便快速查询。

#### 可拓展之处

类似的问题可以通过枚举可能的 $\gcd$ 值并结合桶标记法来解决。例如，在计算数组中所有子序列的 $\gcd$ 数量时，也可以采用类似的思路。

#### 推荐题目

1. [P2303 [SDOI2012] Longge的问题](https://www.luogu.com.cn/problem/P2303)
2. [P2568 GCD](https://www.luogu.com.cn/problem/P2568)
3. [P1447 [NOI2010] 能量采集](https://www.luogu.com.cn/problem/P1447)

### 精选题解

#### 题解1：作者：Tyyyyyy (赞：14)

**星级：5星**

**关键亮点**：
- 思路清晰，直接枚举每个可能的 $\gcd$ 值，并通过计算其所有倍数的 $\gcd$ 来判断是否可行。
- 代码简洁，使用了桶标记法和 `__gcd` 函数，效率高。

**核心代码**：
```cpp
for(int i=1;i<=1e6;i++)
{
    for(int j=1;1ll*i*j<=1e6;j++)
        f[i]=__gcd(f[i],f[i*j]);
    if(f[i]==i&&!isin[i])ans++;
}
```

#### 题解2：作者：Yizhixiaoyun (赞：9)

**星级：4星**

**关键亮点**：
- 使用桶记录每个值是否存在，并通过暴力枚举每个可能的 $\gcd$ 值的倍数来判断是否可行。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(register int i=1;i<=maxx;++i){
    if(a[i]!=0) continue;
    int tot=0;
    for(register int j=i;j<=maxx;j+=i){
        if(a[j]!=0) tot=__gcd(tot,j);
    }
    if(tot==i) ans++;
}
```

#### 题解3：作者：0xFF (赞：3)

**星级：4星**

**关键亮点**：
- 通过枚举每个可能的 $\gcd$ 值，并计算其所有倍数的 $\gcd$ 来判断是否可行。
- 代码简洁，使用了 `gcd` 函数，效率高。

**核心代码**：
```cpp
for(int i=1;i<=1e6;++i) {
    int p=0;
    for(int j=i;j<=1e6;j+=i) {
        if(f[j]) p=gcd(p,j);
    }
    if(p==i) ++ans;
}
```

### 总结

本题的核心在于枚举每个可能的 $\gcd$ 值，并通过计算其所有倍数的 $\gcd$ 来判断是否可行。通过桶标记法和 `__gcd` 函数，可以高效地解决该问题。类似的问题可以通过枚举可能的 $\gcd$ 值并结合桶标记法来解决。

---
处理用时：47.58秒