# 题目信息

# Palindrome Basis

## 题目描述

You are given a positive integer $ n $ . Let's call some positive integer $ a $ without leading zeroes palindromic if it remains the same after reversing the order of its digits. Find the number of distinct ways to express $ n $ as a sum of positive palindromic integers. Two ways are considered different if the frequency of at least one palindromic integer is different in them. For example, $ 5=4+1 $ and $ 5=3+1+1 $ are considered different but $ 5=3+1+1 $ and $ 5=1+3+1 $ are considered the same.

Formally, you need to find the number of distinct multisets of positive palindromic integers the sum of which is equal to $ n $ .

Since the answer can be quite large, print it modulo $ 10^9+7 $ .

## 说明/提示

For the first testcase, there are $ 7 $ ways to partition $ 5 $ as a sum of positive palindromic integers:

- $ 5=1+1+1+1+1 $
- $ 5=1+1+1+2 $
- $ 5=1+2+2 $
- $ 5=1+1+3 $
- $ 5=2+3 $
- $ 5=1+4 $
- $ 5=5 $

For the second testcase, there are total $ 77 $ ways to partition $ 12 $ as a sum of positive integers but among them, the partitions $ 12=2+10 $ , $ 12=1+1+10 $ and $ 12=12 $ are not valid partitions of $ 12 $ as a sum of positive palindromic integers because $ 10 $ and $ 12 $ are not palindromic. So, there are $ 74 $ ways to partition $ 12 $ as a sum of positive palindromic integers.

## 样例 #1

### 输入

```
2
5
12```

### 输出

```
7
74```

# AI分析结果

### 题目内容重写

**题目描述：**

给定一个正整数 $n$。我们称一个没有前导零的正整数 $a$ 为回文数，如果它的数字顺序反转后仍然与原数相同。求将 $n$ 表示为正回文数之和的不同方式的数量。如果两种方式中至少有一个回文数的频率不同，则认为它们是不同的。例如，$5=4+1$ 和 $5=3+1+1$ 被认为是不同的，但 $5=3+1+1$ 和 $5=1+3+1$ 被认为是相同的。

形式化地，你需要找到满足和等于 $n$ 的正回文数的不同多重集的数量。

由于答案可能很大，请输出其对 $10^9+7$ 取模的结果。

**说明/提示：**

对于第一个测试用例，有 $7$ 种方式将 $5$ 表示为正回文数之和：

- $5=1+1+1+1+1$
- $5=1+1+1+2$
- $5=1+2+2$
- $5=1+1+3$
- $5=2+3$
- $5=1+4$
- $5=5$

对于第二个测试用例，总共有 $77$ 种方式将 $12$ 表示为正数之和，但其中 $12=2+10$、$12=1+1+10$ 和 $12=12$ 不是有效的表示方式，因为 $10$ 和 $12$ 不是回文数。因此，有 $74$ 种方式将 $12$ 表示为正回文数之和。

**样例 #1**

### 输入

```
2
5
12
```

### 输出

```
7
74
```

### 算法分类

动态规划

### 题解分析与结论

该问题的核心是将 $n$ 表示为回文数之和的方案数，且每个回文数可以重复使用。这类似于完全背包问题，其中回文数相当于物品，$n$ 相当于背包容量。因此，动态规划是解决该问题的合适方法。

### 精选题解

#### 题解1：JCLinux (赞：10)

**星级：5星**

**关键亮点：**
- 详细解释了动态规划的思路，特别是完全背包的应用。
- 提供了回文数的预处理方法，并解释了如何通过完全背包求解方案数。
- 代码清晰，注释详细，易于理解。

**核心代码：**
```cpp
void init()
{
    dp[0] = 1;
    for(int i = 1; i <= 40004; i++) if(ish(i)) hw.push_back(i);
    for(auto x : hw)
        for(int i = x; i <= 40004; i++)
            dp[i] = (dp[i] + dp[i - x]) % mod;
}
```
**实现思想：**
- 首先预处理出所有回文数，然后使用完全背包的方法计算每个 $n$ 的方案数。

#### 题解2：wwwidk1234 (赞：2)

**星级：4星**

**关键亮点：**
- 提供了回文数打表的方法，并解释了完全背包的状态转移方程。
- 代码简洁，易于理解。

**核心代码：**
```cpp
f[0]=1;
for(int i=0;i<HWS;i++)
    for(int j=hw[i];j<=MAXN;j++)
        f[j]=(f[j]+f[j-hw[i]])%mod;
```
**实现思想：**
- 通过打表预处理回文数，然后使用完全背包的方法计算每个 $n$ 的方案数。

#### 题解3：NFGase (赞：1)

**星级：4星**

**关键亮点：**
- 代码简洁，贴近完全背包的板子，易于理解。
- 提供了回文数的判断方法，并解释了完全背包的应用。

**核心代码：**
```cpp
dp[0] = 1;
for(int i = 0; i < vec.size(); i++)
    for(int j = vec[i]; j <= 40000; j++)
        dp[j] = (dp[j] + dp[j - vec[i]]) % mod;
```
**实现思想：**
- 通过预处理回文数，然后使用完全背包的方法计算每个 $n$ 的方案数。

### 最优关键思路或技巧

1. **回文数预处理**：通过遍历 $1$ 到 $40000$ 的所有数，判断是否为回文数，并将其存储起来。
2. **完全背包**：将回文数视为物品，$n$ 视为背包容量，使用完全背包的方法计算方案数。
3. **动态规划优化**：通过预处理和滚动数组优化，减少时间和空间复杂度。

### 可拓展之处

类似的问题可以扩展到其他类型的数（如质数、平方数等）的拆分问题，或者扩展到多维背包问题。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)

### 个人心得

- **调试经历**：在预处理回文数时，需要注意边界条件，如 $1$ 和 $40000$ 是否包含在内。
- **踩坑教训**：在动态规划转移时，要注意取模运算，避免溢出。
- **顿悟感想**：完全背包问题在计数类问题中的应用非常广泛，理解其本质可以解决许多类似问题。

---
处理用时：41.57秒