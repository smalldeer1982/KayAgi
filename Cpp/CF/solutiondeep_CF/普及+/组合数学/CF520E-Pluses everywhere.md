# 题目信息

# Pluses everywhere

## 题目描述

Vasya is sitting on an extremely boring math class. To have fun, he took a piece of paper and wrote out $ n $ numbers on a single line. After that, Vasya began to write out different ways to put pluses ("+") in the line between certain digits in the line so that the result was a correct arithmetic expression; formally, no two pluses in such a partition can stand together (between any two adjacent pluses there must be at least one digit), and no plus can stand at the beginning or the end of a line. For example, in the string 100500, ways 100500 (add no pluses), 1+00+500 or 10050+0 are correct, and ways 100++500, +1+0+0+5+0+0 or 100500+ are incorrect.

The lesson was long, and Vasya has written all the correct ways to place exactly $ k $ pluses in a string of digits. At this point, he got caught having fun by a teacher and he was given the task to calculate the sum of all the resulting arithmetic expressions by the end of the lesson (when calculating the value of an expression the leading zeros should be ignored). As the answer can be large, Vasya is allowed to get only its remainder modulo $ 10^{9}+7 $ . Help him!

## 说明/提示

In the first sample the result equals $ (1+08)+(10+8)=27 $ .

In the second sample the result equals $ 1+0+8=9 $ .

## 样例 #1

### 输入

```
3 1
108
```

### 输出

```
27```

## 样例 #2

### 输入

```
3 2
108
```

### 输出

```
9```

# AI分析结果

### 题目中文重写
# 处处是加号

## 题目描述
瓦西亚正在上一节极其无聊的数学课。为了找点乐子，他拿了一张纸，在一行上写下了 $n$ 个数字。之后，瓦西亚开始写出在这一行数字的某些数位之间添加加号（“+”）的不同方式，使得结果是一个正确的算术表达式；形式上，在这样的划分中，任意两个加号不能相邻（任意两个相邻的加号之间必须至少有一个数字），并且加号不能位于一行的开头或结尾。例如，在字符串 100500 中，方式 100500（不添加加号）、1+00+500 或 10050+0 是正确的，而方式 100++500、+1+0+0+5+0+0 或 100500+ 是不正确的。

这节课很长，瓦西亚已经写出了在一串数字中恰好放置 $k$ 个加号的所有正确方式。这时，他在找乐子的时候被老师发现了，老师要求他在这节课结束前计算所有得到的算术表达式的和（在计算表达式的值时，应忽略前导零）。由于答案可能很大，允许瓦西亚只取其对 $10^{9}+7$ 取模的结果。帮帮他！

## 说明/提示
在第一个样例中，结果等于 $(1+08)+(10+8)=27$。

在第二个样例中，结果等于 $1+0+8=9$。

## 样例 #1
### 输入
```
3 1
108
```
### 输出
```
27
```

## 样例 #2
### 输入
```
3 2
108
```
### 输出
```
9
```

### 综合分析与结论
这些题解的核心思路都是通过单独计算每个数位的贡献来求解所有可能表达式的和。具体做法是根据离该数位最近且在其之后的加号位置分情况讨论，结合组合数计算该数位在不同情况下的贡献，最后累加得到总和。

算法要点包括：
1. 预处理组合数及其逆元，方便后续计算。
2. 利用前缀和优化内层求和计算，将时间复杂度从 $O(n^2)$ 降低到 $O(n)$。
3. 考虑最后一个数位后面不能放加号的特殊情况，进行单独处理。

解决的难点在于：
1. 准确分析每个数位在不同加号位置下的贡献情况。
2. 处理最后一个数位的特殊情况，避免遗漏或重复计算。
3. 对复杂的求和公式进行化简和优化，以满足时间复杂度要求。

### 所选题解
- **作者：Heartlessly（5星）**
    - 关键亮点：思路清晰，详细推导了每个数位的贡献公式，并通过前缀和预处理优化了计算过程，代码可读性高。
    - 核心代码：
```cpp
for (int cur = 1, i = 1; i <= n - m; ++i, cur = 1ll * cur * 10 % MOD)
    ans = (ans + 1ll * cur * (1ll * pre[n - i] * c(n - 1 - i, m - 1) % MOD + 
    1ll * a[n - i + 1] * c(n - i, m) % MOD) % MOD) % MOD;
```
核心实现思想：枚举 $i$，计算所有 $i$ 位数产生的贡献，利用前缀和 `pre` 计算能产生 $10^j$ 贡献的数字总和，结合组合数计算每个数位的贡献并累加。

- **作者：QwQcOrZ（4星）**
    - 关键亮点：通过分析每个数位在不同位置出现的贡献，发现出现次数与数位位置无关，将数组处理成前缀和形式，枚举 $j$ 计算贡献，同时对最后一位的特殊情况进行了特判。
    - 核心代码：
```cpp
for (ll i = 0; i < n; i++)
{
    ans = (ans + a[n - i - 1] * base[i] % p * C(k - 1, n - i - 2) % p) % p;
    ans = (ans + (a[n - i] - a[n - i - 1] + p) % p * base[i] % p * C(k, n - i - 1) % p) % p; 
} 
```
核心实现思想：枚举 $j$，分别计算普通情况和最后一位特殊情况的贡献并累加。

- **作者：_Passerby_（4星）**
    - 关键亮点：详细推导了每个数位的贡献公式，并通过化简和拆分，将总答案拆分为两个式子的和，最后合并最外层循环，利用前缀和优化内层求和，降低了时间复杂度。
    - 核心代码：
```cpp
Ans = \sum_{j = 1}^{n-k}10^{j - 1}\times((C_{n-j-1}^{k-1}\times\sum_{i = 1}^{n - j}a_i)+a_{n-j+1}\times C_{n-j}^k)
```
核心实现思想：通过化简公式，将最外层循环合并，利用前缀和优化内层求和，计算总答案。

### 最优关键思路或技巧
1. **单独计算贡献**：通过单独计算每个数位的贡献，将问题简化，避免了枚举所有可能的表达式。
2. **前缀和优化**：利用前缀和预处理能产生 $10^j$ 贡献的数字总和，将内层求和的时间复杂度从 $O(n)$ 降低到 $O(1)$。
3. **组合数计算**：预处理组合数及其逆元，方便在计算贡献时快速计算组合数的值。
4. **公式化简**：对复杂的求和公式进行化简和拆分，将总答案拆分为多个简单式子的和，便于计算和优化。

### 可拓展之处
同类型题或类似算法套路包括：
1. 其他在数字间插入运算符的计数问题，如插入减号、乘号等，可采用类似的单独计算贡献的方法。
2. 组合数相关的计数问题，可通过预处理组合数及其逆元来优化计算。
3. 涉及前缀和优化的问题，可通过将数组处理成前缀和形式来降低时间复杂度。

### 推荐洛谷题目
1. [P1869 愚蠢的组合数](https://www.luogu.com.cn/problem/P1869)：考察组合数的计算和取模。
2. [P2671 求和](https://www.luogu.com.cn/problem/P2671)：涉及前缀和的应用。
3. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)：需要运用组合数学和快速幂的知识。

### 个人心得摘录与总结
- **作者：QwQcOrZ**：“祭我在考场上AC了此题”，表达了作者在考场上成功解决此题的喜悦和成就感。
- **作者：Arcturus1350**：“ps:可能组合数一不小心打错了，请发现的大佬提出，谢谢”，提醒自己和他人在编写代码时要注意细节，避免出现错误。

---
处理用时：37.68秒