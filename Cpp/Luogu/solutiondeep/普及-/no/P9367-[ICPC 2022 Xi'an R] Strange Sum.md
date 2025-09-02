# 题目信息

# [ICPC 2022 Xi'an R] Strange Sum

## 题目描述

Given a sequence $a_1, a_2, \ldots, a_n$.

You are going to select zero or more elements of $a$ so that: if you select $a_i$, then in any interval of length $i$ (formally, in $a[j, j + i - 1]$ for any $1 \le j \le n - i + 1$) you can select at most $2$ elements.

Calculate the maximal sum of the elements you select.

## 说明/提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem J.

**Author**: JohnVictor.

## 样例 #1

### 输入

```
4
1 4 3 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3
-10 -10 -10
```

### 输出

```
0```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
题目要求从序列中选择若干元素，满足特定条件，并使得所选元素的和最大。通过分析，可以发现最多只能选择两个元素，因此问题简化为选择序列中的最大值和次大值（如果它们非负）。所有题解都基于这一思路，通过排序或直接遍历来找到最大值和次大值，并计算它们的和。

### 所选题解

#### 1. 作者：cff_0102 (赞：4)
- **星级**: 4星
- **关键亮点**: 简洁明了，直接通过排序找到最大值和次大值，并考虑负数情况。
- **核心代码**:
  ```cpp
  sort(a,a+n);
  cout<<max(0,a[n-2])+max(0,a[n-1]);
  ```
  **核心思想**: 排序后取最后两个元素，确保它们非负。

#### 2. 作者：lailai0916 (赞：3)
- **星级**: 4星
- **关键亮点**: 通过遍历一次找到最大值和次大值，避免了排序的开销。
- **核心代码**:
  ```cpp
  if(t>max1) {
      max2=max1;
      max1=t;
  } else if(t>max2) {
      max2=t;
  }
  ```
  **核心思想**: 在一次遍历中更新最大值和次大值，最后输出它们的和。

#### 3. 作者：zhuweiqi (赞：3)
- **星级**: 4星
- **关键亮点**: 使用反证法证明最多只能选择两个元素，代码简洁高效。
- **核心代码**:
  ```cpp
  ans=max(ans,x+maxs);
  maxs=max(maxs,x);
  ```
  **核心思想**: 在遍历过程中动态更新最大值和当前最大值与当前元素的和。

### 最优关键思路或技巧
- **贪心策略**: 通过分析发现最多只能选择两个元素，因此问题简化为选择序列中的最大值和次大值。
- **优化技巧**: 通过一次遍历找到最大值和次大值，避免排序的开销。

### 可拓展之处
- 类似问题：在满足某些限制条件下选择元素，使得和最大。这类问题通常可以通过贪心策略或动态规划来解决。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：17.74秒