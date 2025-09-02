# 题目信息

# Hungry Sequence

## 题目描述

Iahub and Iahubina went to a date at a luxury restaurant. Everything went fine until paying for the food. Instead of money, the waiter wants Iahub to write a Hungry sequence consisting of $ n $ integers.

A sequence $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ , consisting of $ n $ integers, is Hungry if and only if:

- Its elements are in increasing order. That is an inequality $ a_{i}&lt;a_{j} $ holds for any two indices $ i,j $ $ (i&lt;j) $ .
- For any two indices $ i $ and $ j $ $ (i&lt;j) $ , $ a_{j} $ must not be divisible by $ a_{i} $ .

Iahub is in trouble, so he asks you for help. Find a Hungry sequence with $ n $ elements.

## 样例 #1

### 输入

```
3
```

### 输出

```
2 9 15
```

## 样例 #2

### 输入

```
5
```

### 输出

```
11 14 20 27 31
```

# AI分析结果



# Hungry Sequence

## 题目描述

Iahub 和 Iahubina 去了一家豪华餐厅约会。一切都很顺利，直到支付餐费时出现意外。服务员不要钱，而是要求 Iahub 写出一个包含 $n$ 个整数的"饥饿序列"。

一个由 $n$ 个整数组成的序列 $a_1, a_2, ..., a_n$ 被称为饥饿序列，当且仅当满足以下条件：
- 元素严格递增，即对任意 $i < j$ 都有 $a_i < a_j$
- 对任意 $i < j$，$a_j$ 不能被 $a_i$ 整除

请帮助 Iahub 构造这样的饥饿序列。

## 样例 #1

### 输入
```
3
```

### 输出
```
2 9 15
```

## 样例 #2

### 输入
```
5
```

### 输出
```
11 14 20 27 31
```

**算法分类**：构造

---

### 综合分析与结论
本题要求构造严格递增且任意元素不互为倍数的序列。核心思路是利用连续数的性质或质数的互质性，最优解法为构造 $[n, 2n-1]$ 的连续整数区间。

---

### 高星题解推荐

#### 1. yydfj（★★★★★）
**关键亮点**：  
- 发现区间 $[n, 2n-1]$ 的数学性质：任意两个数不构成倍数关系  
- 时间复杂度 $O(n)$，实现极简  
**代码核心**：
```cpp
for(int i=n;i<=2*n-1;i++) printf("%d ",i);
```

#### 2. Diphosphonate（★★★★☆）
**关键亮点**：  
- 给出严谨数学证明：$a_j - a_i < n$ 保证不构成倍数  
- 代码简洁，逻辑清晰  
**代码核心**：
```cpp
for(int i=n;i<=2*n-1;i++) cout<<i<<" ";
```

#### 3. shengheng（★★★★☆）
**关键亮点**：  
- 明确点出构造思路的数学依据  
- 强调题目允许多种答案的特性  
**代码核心**：
```cpp
for(int i=n;i<=2*n-1;i++) cout<<i<<' ';
```

---

### 最优关键思路
构造 $n$ 到 $2n-1$ 的连续整数序列：  
1. **数学性质**：对于任意 $a_i$ 和 $a_j$（$i < j$），有 $a_j < 2a_i$，而区间内最小可能的倍数是 $2a_i$，超出区间范围  
2. **复杂度最优**：直接输出 $n$ 个数，无需预处理或复杂计算  

---

### 拓展应用
类似构造问题可考虑：  
1. 利用相邻数互质性质（如构造递增互质序列）  
2. 利用特殊区间范围避免特定数论关系  

---

### 推荐习题
1. [CF12B - Correct Solution?](https://www.luogu.com.cn/problem/CF12B)（构造与数值特性）  
2. [P1300 街名标注](https://www.luogu.com.cn/problem/P1300)（构造特定排列）  
3. [P1216 数字游戏](https://www.luogu.com.cn/problem/P1216)（构造满足数论条件的序列）  

---

### 题解心得摘录
- yydfj：_"随机找出一个整数 $n$ 作为起点... 证出上述答案"_  
- shengheng：_"题目告诉你有多种答案输出其一... 不必拘泥于样例"_  
- Diphosphonate：_通过差值 $j-i < n$ 证明不构成倍数关系_

---
处理用时：68.25秒