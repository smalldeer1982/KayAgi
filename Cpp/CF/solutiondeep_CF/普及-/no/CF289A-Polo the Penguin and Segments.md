# 题目信息

# Polo the Penguin and Segments

## 题目描述

Little penguin Polo adores integer segments, that is, pairs of integers $ [l; r] $ $ (l<=r) $ .

He has a set that consists of $ n $ integer segments: $ [l_{1}; r_{1}],[l_{2}; r_{2}],...,[l_{n}; r_{n}] $ . We know that no two segments of this set intersect. In one move Polo can either widen any segment of the set 1 unit to the left or 1 unit to the right, that is transform $ [l; r] $ to either segment $ [l-1; r] $ , or to segment $ [l; r+1] $ .

The value of a set of segments that consists of $ n $ segments $ [l_{1}; r_{1}],[l_{2}; r_{2}],...,[l_{n}; r_{n}] $ is the number of integers $ x $ , such that there is integer $ j $ , for which the following inequality holds, $ l_{j}<=x<=r_{j} $ .

Find the minimum number of moves needed to make the value of the set of Polo's segments divisible by $ k $ .

## 样例 #1

### 输入

```
2 3
1 2
3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 7
1 2
3 3
4 7
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 企鹅波罗与线段

## 题目描述
小企鹅波罗喜欢整数线段，即整数对 $[l; r]$ （$l \leq r$）。
它有一个由 $n$ 个整数线段组成的集合：$[l_1; r_1], [l_2; r_2],..., [l_n; r_n]$ 。我们知道这个集合中的任意两个线段都不相交。在一次移动中，波罗可以将集合中的任意一个线段向左或向右扩展1个单位，即将 $[l; r]$ 转换为线段 $[l - 1; r]$ ，或者转换为线段 $[l; r + 1]$ 。
由 $n$ 个线段 $[l_1; r_1], [l_2; r_2],..., [l_n; r_n]$ 组成的线段集合的值，是指存在整数 $j$ ，使得不等式 $l_j \leq x \leq r_j$ 成立的整数 $x$ 的数量。
求使波罗的线段集合的值能被 $k$ 整除所需的最少移动次数。

## 样例 #1
### 输入
```
2 3
1 2
3 4
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3 7
1 2
3 3
4 7
```
### 输出
```
0
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先计算所有区间包含整数数量之和，由于每次操作使该和加1，所以求该和与大于等于它且能被k整除的最小数的差值，就是最少操作次数。具体实现上，多数题解直接累加各区间长度 `r - l + 1` 得到总和，再通过取余等运算得到结果。部分题解提到了暴力寻找大于总和且能被k整除的数，但都指出可以通过 `k - sum % k` 这种更简便的方式计算，最后再对k取余以防总和本身是k的倍数。整体来说，各题解思路相近，主要差异在于代码风格和细节处理。

### 通用建议与扩展思路
对于此类题目，核心在于理解每次操作对总和的影响，进而通过数学运算简化求解过程。可以拓展到其他类似的区间操作并求特定结果的题目，例如改变操作对区间和的影响方式，或者改变最终需要满足的条件（如被多个数整除等）。

### 洛谷相似题目推荐
- P1008 [三连击](https://www.luogu.com.cn/problem/P1008)：通过枚举和数学运算解决问题，锻炼对数字关系的处理能力。
- P1147 连续自然数和：需要运用数学推理和枚举来找出满足条件的连续自然数序列，与本题分析数字关系的思路类似。
- P1440 求m区间内的最小值：涉及区间相关操作，可锻炼对区间数据处理的能力，与本题区间相关的背景有相似之处。 

---
处理用时：31.17秒