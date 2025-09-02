# 题目信息

# Hossam and Trainees

## 题目描述

Hossam has $ n $ trainees. He assigned a number $ a_i $ for the $ i $ -th trainee.

A pair of the $ i $ -th and $ j $ -th ( $ i \neq j $ ) trainees is called successful if there is an integer $ x $ ( $ x \geq 2 $ ), such that $ x $ divides $ a_i $ , and $ x $ divides $ a_j $ .

Hossam wants to know if there is a successful pair of trainees.

Hossam is very tired now, so he asks you for your help!

## 说明/提示

In the first example, the first trainee and the second trainee make up a successful pair:

 $ a_1 = 32, a_2 = 48 $ , you can choose $ x = 4 $ .

## 样例 #1

### 输入

```
2
3
32 48 7
3
14 5 9```

### 输出

```
YES
NO```

# AI分析结果

### 题目内容重写
# Hossam和学员

## 题目描述

Hossam有$n$个学员。他为第$i$个学员分配了一个数字$a_i$。

如果存在一个整数$x$（$x \geq 2$），使得$x$能整除$a_i$，且$x$能整除$a_j$，那么第$i$个和第$j$个（$i \neq j$）学员组成的对被称为成功的对。

Hossam想知道是否存在一个成功的学员对。

Hossam现在非常累，所以他请你帮忙！

## 说明/提示

在第一个样例中，第一个学员和第二个学员组成了一个成功的对：

$a_1 = 32, a_2 = 48$，你可以选择$x = 4$。

## 样例 #1

### 输入

```
2
3
32 48 7
3
14 5 9```

### 输出

```
YES
NO```

### 算法分类
质数

### 题解分析与结论
本题的核心在于判断数组中是否存在两个数有大于1的公约数。由于直接枚举所有数对的复杂度为$O(n^2)$，无法通过，因此需要优化。所有题解都采用了质因数分解的思路，通过分解每个数的质因数，并统计每个质因数的出现次数，来判断是否存在两个数共享同一个质因数。

### 题解评分与亮点
1. **Dream__Sky (4星)**  
   - 关键亮点：提出了分段处理的思路，将质因数分为小于等于$\sqrt{n}$和大于$\sqrt{n}$两种情况，分别用数组和`map`记录，优化了空间和时间复杂度。
   - 代码实现：通过预处理质数，分解质因数，并统计质因数的出现次数，最后判断是否有质因数出现超过一次。

2. **lraM41 (4星)**  
   - 关键亮点：代码结构清晰，使用了快读和快写优化输入输出，预处理质数后，分别处理小于$\sqrt{10^9}$和大于$\sqrt{10^9}$的质因数，逻辑严谨。
   - 代码实现：通过线性筛预处理质数，分解质因数并统计出现次数，最后判断是否有质因数出现超过一次。

3. **include_BM (4星)**  
   - 关键亮点：思路清晰，将质因数分为小于等于$\sqrt{V}$和大于$\sqrt{V}$两种情况，分别用数组和`map`记录，优化了空间和时间复杂度。
   - 代码实现：通过预处理质数，分解质因数并统计出现次数，最后判断是否有质因数出现超过一次。

### 最优关键思路
1. **质因数分解**：通过分解每个数的质因数，统计每个质因数的出现次数，判断是否有质因数出现超过一次。
2. **分段处理**：将质因数分为小于等于$\sqrt{n}$和大于$\sqrt{n}$两种情况，分别用数组和`map`记录，优化了空间和时间复杂度。

### 可拓展之处
1. **质因数分解的优化**：可以进一步优化质因数分解的算法，如使用Pollard-Rho算法进行大数分解。
2. **统计质因数的数据结构**：可以使用更高效的数据结构如`unordered_map`来统计质因数的出现次数。

### 推荐题目
1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)

### 个人心得
- **调试经历**：在处理质因数分解时，需要注意质因数的唯一性，避免重复统计。
- **踩坑教训**：在处理大质因数时，使用`map`记录可以避免数组空间不足的问题。
- **顿悟感想**：分段处理质因数的思路非常巧妙，能够有效降低时间和空间复杂度。

---
处理用时：32.94秒