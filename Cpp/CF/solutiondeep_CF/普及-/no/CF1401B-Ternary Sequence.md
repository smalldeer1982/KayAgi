# 题目信息

# Ternary Sequence

## 题目描述

You are given two sequences $ a_1, a_2, \dots, a_n $ and $ b_1, b_2, \dots, b_n $ . Each element of both sequences is either $ 0 $ , $ 1 $ or $ 2 $ . The number of elements $ 0 $ , $ 1 $ , $ 2 $ in the sequence $ a $ is $ x_1 $ , $ y_1 $ , $ z_1 $ respectively, and the number of elements $ 0 $ , $ 1 $ , $ 2 $ in the sequence $ b $ is $ x_2 $ , $ y_2 $ , $ z_2 $ respectively.

You can rearrange the elements in both sequences $ a $ and $ b $ however you like. After that, let's define a sequence $ c $ as follows:

 $ c_i = \begin{cases} a_i b_i & \mbox{if }a_i > b_i \\ 0       & \mbox{if }a_i = b_i \\ -a_i b_i & \mbox{if }a_i < b_i \end{cases} $

You'd like to make $ \sum_{i=1}^n c_i $ (the sum of all elements of the sequence $ c $ ) as large as possible. What is the maximum possible sum?

## 说明/提示

In the first sample, one of the optimal solutions is:

 $ a = \{2, 0, 1, 1, 0, 2, 1\} $

 $ b = \{1, 0, 1, 0, 2, 1, 0\} $

 $ c = \{2, 0, 0, 0, 0, 2, 0\} $

In the second sample, one of the optimal solutions is:

 $ a = \{0, 2, 0, 0, 0\} $

 $ b = \{1, 1, 0, 1, 0\} $

 $ c = \{0, 2, 0, 0, 0\} $

In the third sample, the only possible solution is:

 $ a = \{2\} $

 $ b = \{2\} $

 $ c = \{0\} $

## 样例 #1

### 输入

```
3
2 3 2
3 3 1
4 0 1
2 3 0
0 0 1
0 0 1```

### 输出

```
4
2
0```

# AI分析结果

### 题目内容
# 三元序列

## 题目描述
给定两个序列 $a_1, a_2, \dots, a_n$ 和 $b_1, b_2, \dots, b_n$ 。两个序列中的每个元素均为 $0$、$1$ 或 $2$ 。序列 $a$ 中元素 $0$、$1$、$2$ 的数量分别为 $x_1$、$y_1$、$z_1$ ，序列 $b$ 中元素 $0$、$1$、$2$ 的数量分别为 $x_2$、$y_2$、$z_2$ 。

你可以随意重新排列序列 $a$ 和 $b$ 中的元素。之后，定义序列 $c$ 如下：
\[ c_i = 
\begin{cases} 
a_i b_i & \text{若 }a_i > b_i \\
0 & \text{若 }a_i = b_i \\
-a_i b_i & \text{若 }a_i < b_i 
\end{cases}
\]

你希望使 $\sum_{i=1}^n c_i$ （序列 $c$ 的所有元素之和）尽可能大。这个最大和是多少？

## 说明/提示
在第一个样例中，一种最优解为：
\[ a = \{2, 0, 1, 1, 0, 2, 1\} \]
\[ b = \{1, 0, 1, 0, 2, 1, 0\} \]
\[ c = \{2, 0, 0, 0, 0, 2, 0\} \]

在第二个样例中，一种最优解为：
\[ a = \{0, 2, 0, 0, 0\} \]
\[ b = \{1, 1, 0, 1, 0\} \]
\[ c = \{0, 2, 0, 0, 0\} \]

在第三个样例中，唯一可能的解为：
\[ a = \{2\} \]
\[ b = \{2\} \]
\[ c = \{0\} \]

## 样例 #1
### 输入
```
3
2 3 2
3 3 1
4 0 1
2 3 0
0 0 1
0 0 1
```

### 输出
```
4
2
0
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解均采用贪心思想，核心思路是让能产生正贡献的组合尽可能多，产生负贡献的组合尽可能少。通过分析 $c_i$ 的计算规则可知，$a_i = 2$ 且 $b_i = 1$ 时，$c_i = 2$ 产生正贡献；$a_i = 1$ 且 $b_i = 2$ 时，$c_i = - 2$ 产生负贡献；其他情况 $c_i = 0$ 无贡献。所以要点在于优先用 $a$ 中的 $2$ 与 $b$ 中的 $1$ 配对，然后用 $a$ 中的 $0$ 和 $2$ 去抵消 $b$ 中的 $2$，最后计算剩余部分。各题解的思路和实现方式基本一致，主要区别在于代码的简洁性和可读性。

### 通用建议与扩展思路
对于此类贪心问题，关键在于通过对题目条件的分析，找出能使目标值最优的组合方式。可以多练习类似的贪心题目，如涉及资源分配、任务调度等场景的问题，加深对贪心策略的理解和运用。在实现代码时，要注意逻辑的清晰性和变量命名的规范性，以提高代码的可读性和可维护性。

### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
3. [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937) 

---
处理用时：28.75秒