# 题目信息

# Differential Sorting

## 题目描述

You are given an array $ a $ of $ n $ elements.

Your can perform the following operation no more than $ n $ times: Select three indices $ x,y,z $ $ (1 \leq x < y < z \leq n) $ and replace $ a_x $ with $ a_y - a_z $ . After the operation, $ |a_x| $ need to be less than $ 10^{18} $ .

Your goal is to make the resulting array non-decreasing. If there are multiple solutions, you can output any. If it is impossible to achieve, you should report it as well.

## 说明/提示

In the first example, the array becomes

 $ [-6,-4,2,-1,2] $ after the first operation,

 $ [-6,-4,-3,-1,2] $ after the second operation.

In the second example, it is impossible to make the array sorted after any sequence of operations.

In the third example, the array is already sorted, so we don't need to perform any operations.

## 样例 #1

### 输入

```
3
5
5 -4 2 -1 2
3
4 3 2
3
-3 -2 -1```

### 输出

```
2
1 2 3
3 4 5
-1
0```

# AI分析结果

### 题目内容
# 差分排序

## 题目描述
给定一个包含 $n$ 个元素的数组 $a$。

你可以执行以下操作不超过 $n$ 次：选择三个索引 $x,y,z$（$1 \leq x < y < z \leq n$），并将 $a_x$ 替换为 $a_y - a_z$。操作后，$|a_x|$ 需要小于 $10^{18}$。

你的目标是使得到的数组为非递减顺序。如果有多个解决方案，你可以输出任何一个。如果无法实现，也应报告。

## 说明/提示
在第一个示例中，数组在第一次操作后变为 $[-6,-4,2,-1,2]$，在第二次操作后变为 $[-6,-4,-3,-1,2]$。

在第二个示例中，无论经过任何操作序列，都无法使数组排序。

在第三个示例中，数组已经是排序的，所以我们不需要执行任何操作。

## 样例 #1
### 输入
```
3
5
5 -4 2 -1 2
3
4 3 2
3
-3 -2 -1
```
### 输出
```
2
1 2 3
3 4 5
-1
0
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断数组是否已经非降序或者是否无解，再处理一般情况。
1. **思路**：多数题解先检查数组是否已非降序，若不是，重点分析 $a_{n - 1}$ 与 $a_n$ 的关系来判断无解情况，如 $a_{n - 1} > a_n$ 或 $a_n < 0$ 且数组非升序时无解；对于有解情况，常采用将前 $n - 2$ 个元素通过操作变为 $a_{n - 1} - a_n$ 的方式。
2. **算法要点**：通过遍历数组判断是否非降序，利用 $a_{n - 1}$ 与 $a_n$ 的比较结果决定输出无解或进行后续操作，确定操作次数及具体操作。
3. **解决难点**：难点在于找出无解的条件以及设计一种通用的操作方案使数组变为非降序。各题解通过对数组最后两个元素关系及整体单调性的分析来解决无解判断问题，利用固定的操作模式解决使数组非降序的问题。

由于所有题解均未达到4星，以下给出通用建议与扩展思路：
 - **通用建议**：题解整体思路较清晰，但部分题解代码注释较少，可读性欠佳。在代码实现时，可增加注释以更好地解释关键步骤，如判断无解条件和具体操作的意义。同时，部分题解可适当优化代码结构，使其更加简洁明了。
 - **扩展思路**：此类构造题可进一步拓展思维，思考不同操作规则下如何使数组满足特定顺序，或改变数组条件（如元素取值范围、数组长度限制等）后对解法的影响。还可考虑将该问题拓展到多维数组或其他数据结构上，研究相应的解决策略。

### 相似知识点洛谷题目
 - [P1163 银行贷款](https://www.luogu.com.cn/problem/P1163)：涉及数学计算与方案构造，与本题类似需根据给定条件构造出满足要求的方案。
 - [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要结合质数判断和回文数构造等知识，与本题一样要在一定规则下构造出符合条件的数，锻炼构造思维。
 - [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分答案和构造检查函数来解决问题，与本题在构造满足特定条件的方案上有相似之处，可加深对构造类问题的理解。 

---
处理用时：26.27秒