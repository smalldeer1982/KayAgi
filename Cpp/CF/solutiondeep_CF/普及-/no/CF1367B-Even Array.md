# 题目信息

# Even Array

## 题目描述

You are given an array $ a[0 \ldots n-1] $ of length $ n $ which consists of non-negative integers. Note that array indices start from zero.

An array is called good if the parity of each index matches the parity of the element at that index. More formally, an array is good if for all $ i $ ( $ 0 \le i \le n - 1 $ ) the equality $ i \bmod 2 = a[i] \bmod 2 $ holds, where $ x \bmod 2 $ is the remainder of dividing $ x $ by 2.

For example, the arrays \[ $ 0, 5, 2, 1 $ \] and \[ $ 0, 17, 0, 3 $ \] are good, and the array \[ $ 2, 4, 6, 7 $ \] is bad, because for $ i=1 $ , the parities of $ i $ and $ a[i] $ are different: $ i \bmod 2 = 1 \bmod 2 = 1 $ , but $ a[i] \bmod 2 = 4 \bmod 2 = 0 $ .

In one move, you can take any two elements of the array and swap them (these elements are not necessarily adjacent).

Find the minimum number of moves in which you can make the array $ a $ good, or say that this is not possible.

## 说明/提示

In the first test case, in the first move, you can swap the elements with indices $ 0 $ and $ 1 $ , and in the second move, you can swap the elements with indices $ 2 $ and $ 3 $ .

In the second test case, in the first move, you need to swap the elements with indices $ 0 $ and $ 1 $ .

In the third test case, you cannot make the array good.

## 样例 #1

### 输入

```
4
4
3 2 7 6
3
3 2 6
1
7
7
4 9 2 1 18 3 0```

### 输出

```
2
1
-1
0```

# AI分析结果

### 题目内容
# 偶数数组

## 题目描述
给定一个长度为 $n$ 的数组 $a[0 \ldots n - 1]$，数组元素为非负整数。注意数组索引从0开始。

如果每个索引的奇偶性与该索引位置上元素的奇偶性相匹配，则称该数组为 “好数组”。更正式地说，如果对于所有 $i$（$0 \le i \le n - 1$），等式 $i \bmod 2 = a[i] \bmod 2$ 成立，则该数组是好数组，其中 $x \bmod 2$ 是 $x$ 除以2的余数。

例如，数组 \[ $0, 5, 2, 1$ \] 和 \[ $0, 17, 0, 3$ \] 是好数组，而数组 \[ $2, 4, 6, 7$ \] 是坏数组，因为对于 $i = 1$，$i$ 和 $a[i]$ 的奇偶性不同：$i \bmod 2 = 1 \bmod 2 = 1$，但 $a[i] \bmod 2 = 4 \bmod 2 = 0$。

在一次移动中，你可以选取数组中的任意两个元素并交换它们（这两个元素不一定相邻）。

求使数组 $a$ 变为好数组所需的最小移动次数，如果不可能，则输出 -1。

## 说明/提示
在第一个测试用例中，在第一次移动中，你可以交换索引为 $0$ 和 $1$ 的元素，在第二次移动中，你可以交换索引为 $2$ 和 $3$ 的元素。

在第二个测试用例中，在第一次移动中，你需要交换索引为 $0$ 和 $1$ 的元素。

在第三个测试用例中，你无法使数组变为好数组。

## 样例 #1
### 输入
```
4
4
3 2 7 6
3
3 2 6
1
7
7
4 9 2 1 18 3 0
```
### 输出
```
2
1
-1
0
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路本质相同，均是通过统计数组中位置与对应元素奇偶性不匹配的情况。具体为分别统计奇数索引位置上元素为偶数的数量（设为 $a$），以及偶数索引位置上元素为奇数的数量（设为 $b$）。若 $a = b$，则说明可以通过交换使数组变好，最小交换次数即为 $a$（或 $b$）；若 $a \neq b$，则无法使数组变好，输出 -1。各题解主要差异在于代码实现细节，如输入方式、变量命名等。

### 通用建议与扩展思路
对于此类题目，关键在于理解题目中对数组的限定条件，通过合理统计关键信息来判断能否达成目标以及计算最小操作次数。扩展思路上，可以考虑增加条件限制，如限制交换只能在相邻元素间进行，或者改变数组元素与索引的匹配规则等。同时，在代码实现上，可以进一步优化输入输出的效率，例如使用更高效的输入函数。

### 洛谷相似题目
1. P1909 [NOIP2016 普及组] 买铅笔：通过计算不同包装铅笔购买方案的花费，选择最小花费，考察数学计算与方案选择。
2. P1085 [NOIP2004 普及组] 不高兴的津津：根据时间安排计算满足条件的时间，涉及数学运算和逻辑判断。
3. P1046 [NOIP2005 普及组] 陶陶摘苹果：根据身高和苹果高度计算能摘到的苹果数量，属于简单的数学应用。 

---
处理用时：33.98秒