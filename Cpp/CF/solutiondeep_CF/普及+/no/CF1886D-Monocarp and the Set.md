# 题目信息

# Monocarp and the Set

## 题目描述

Monocarp has $ n $ numbers $ 1, 2, \dots, n $ and a set (initially empty). He adds his numbers to this set $ n $ times in some order. During each step, he adds a new number (which has not been present in the set before). In other words, the sequence of added numbers is a permutation of length $ n $ .

Every time Monocarp adds an element into the set except for the first time, he writes out a character:

- if the element Monocarp is trying to insert becomes the maximum element in the set, Monocarp writes out the character &gt;;
- if the element Monocarp is trying to insert becomes the minimum element in the set, Monocarp writes out the character &lt;;
- if none of the above, Monocarp writes out the character ?.

You are given a string $ s $ of $ n-1 $ characters, which represents the characters written out by Monocarp (in the order he wrote them out). You have to process $ m $ queries to the string. Each query has the following format:

- $ i $ $ c $ — replace $ s_i $ with the character $ c $ .

Both before processing the queries and after each query, you have to calculate the number of different ways to order the integers $ 1, 2, 3, \dots, n $ such that, if Monocarp inserts the integers into the set in that order, he gets the string $ s $ . Since the answers might be large, print them modulo $ 998244353 $ .

## 说明/提示

In the first example, there are three possible orderings before all queries:

- $ 3, 1, 2, 5, 4, 6 $ ;
- $ 4, 1, 2, 5, 3, 6 $ ;
- $ 4, 1, 3, 5, 2, 6 $ .

After the last query, there is only one possible ordering:

- $ 3, 5, 4, 6, 2, 1 $ .

## 样例 #1

### 输入

```
6 4
<?>?>
1 ?
4 <
5 <
1 >
```

### 输出

```
3
0
0
0
1```

## 样例 #2

### 输入

```
2 2
>
1 ?
1 <
```

### 输出

```
1
0
1```

# AI分析结果

### 题目内容重写

Monocarp有$n$个数字$1, 2, \dots, n$和一个初始为空的集合。他按照某种顺序将这$n$个数字依次加入集合中。每次加入一个新数字（即之前未加入过的数字），换句话说，加入的数字序列是一个长度为$n$的排列。

每次加入一个元素时（除了第一次），Monocarp会写下一个字符：

- 如果加入的元素成为集合中的最大值，Monocarp写下字符`>`；
- 如果加入的元素成为集合中的最小值，Monocarp写下字符`<`；
- 如果以上两种情况都不满足，Monocarp写下字符`?`。

给定一个长度为$n-1$的字符串$s$，表示Monocarp写下的字符序列（按顺序）。你需要处理$m$个查询，每个查询的格式如下：

- $i$ $c$ — 将$s_i$替换为字符$c$。

在处理所有查询之前以及每个查询之后，你需要计算有多少种不同的方式将数字$1, 2, \dots, n$排列，使得Monocarp按照这个顺序加入数字时，得到的字符串是$s$。由于答案可能很大，输出时对$998244353$取模。

### 算法分类
数学、组合数学

### 题解分析与结论

#### 题解思路对比
1. **uid_310801**：从前往后处理字符，每次根据字符类型（`>`、`<`、`?`）更新答案。对于`?`，答案乘上当前插入的数减1。使用逆元处理修改操作。
2. **SunnyYuan**：将问题转化为倒序删除数字，每次删除时根据字符类型更新答案。对于`?`，答案乘上当前集合大小减2。使用逆元处理修改操作。
3. **TernaryTree**：动态维护前缀答案，根据字符类型更新答案。对于`?`，答案乘上当前插入的数减1。使用逆元处理修改操作。

#### 关键思路总结
- **倒序思维**：将插入问题转化为删除问题，简化了问题分析。
- **逆元处理**：通过预处理逆元，快速处理修改操作，避免了重复计算。
- **特判处理**：对于第一个字符为`?`的情况，直接输出0，避免不必要的计算。

#### 推荐题解
1. **SunnyYuan**（4星）
   - **亮点**：倒序思维清晰，逆元处理高效，代码简洁。
   - **代码核心**：
     ```cpp
     for (int i = 3; i <= n; i++)
         if (s[i] == '?')
             ans = 1ll * ans * (i - 2) % mod;
     ```
   - **个人心得**：将问题转化为删除操作，简化了问题分析。

2. **TernaryTree**（4星）
   - **亮点**：动态维护前缀答案，思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     for (int i = 2; i <= n - 1; i++) if (s[i] == '?') ans = ans * (i - 1) % p;
     ```
   - **个人心得**：动态维护前缀答案，避免了重复计算。

3. **uid_310801**（4星）
   - **亮点**：从前往后处理字符，思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     for (int i = 3; i <= n; i++) if (s[i] == '?') (ans *= (i - 2)) %= mod;
     ```
   - **个人心得**：从前往后处理字符，思路清晰。

### 关键代码实现
```cpp
// SunnyYuan的核心代码
for (int i = 3; i <= n; i++)
    if (s[i] == '?')
        ans = 1ll * ans * (i - 2) % mod;
```

### 拓展思路
- **类似题目**：可以考虑其他涉及排列组合和动态维护答案的题目，如洛谷P1494、P1495、P1496。

### 推荐题目
1. [P1494 小Z的袜子](https://www.luogu.com.cn/problem/P1494)
2. [P1495 曹冲养猪](https://www.luogu.com.cn/problem/P1495)
3. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)

---
处理用时：34.22秒