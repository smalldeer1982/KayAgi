# 题目信息

# IQ Test

## 题目描述

Petya is preparing for IQ test and he has noticed that there many problems like: you are given a sequence, find the next number. Now Petya can solve only problems with arithmetic or geometric progressions.

Arithmetic progression is a sequence $ a_{1} $ , $ a_{1}+d $ , $ a_{1}+2d $ , $ ... $ , $ a_{1}+(n-1)d $ , where $ a_{1} $ and $ d $ are any numbers.

Geometric progression is a sequence $ b_{1} $ , $ b_{2}=b_{1}q $ , $ ... $ , $ b_{n}=b_{n-1}q $ , where $ b_{1}≠0 $ , $ q≠0 $ , $ q≠1 $ .

Help Petya and write a program to determine if the given sequence is arithmetic or geometric. Also it should found the next number. If the sequence is neither arithmetic nor geometric, print 42 (he thinks it is impossible to find better answer). You should also print 42 if the next element of progression is not integer. So answer is always integer.

## 说明/提示

This problem contains very weak pretests!

## 样例 #1

### 输入

```
836 624 412 200
```

### 输出

```
-12
```

## 样例 #2

### 输入

```
1 334 667 1000
```

### 输出

```
1333
```

# AI分析结果

### 题目内容
# IQ测试

## 题目描述
Petya正在准备智商测试，他注意到有很多这样的问题：给定一个数列，找出下一个数字。现在Petya只能解决涉及等差数列或等比数列的问题。

等差数列是一个数列 $a_{1}$，$a_{1}+d$，$a_{1}+2d$，...，$a_{1}+(n - 1)d$，其中 $a_{1}$ 和 $d$ 可以是任意数字。

等比数列是一个数列 $b_{1}$，$b_{2}=b_{1}q$，...，$b_{n}=b_{n - 1}q$，其中 $b_{1}≠0$，$q≠0$，$q≠1$。

帮助Petya编写一个程序，判断给定的数列是等差数列还是等比数列，并找出下一个数字。如果该数列既不是等差数列也不是等比数列，则输出42（他认为找不到更好的答案）。如果数列下一个元素不是整数，也应输出42。所以答案始终是整数。

## 说明/提示
此问题的预测试数据非常弱！

## 样例 #1
### 输入
```
836 624 412 200
```
### 输出
```
-12
```

## 样例 #2
### 输入
```
1 334 667 1000
```
### 输出
```
1333
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先读入四个数，然后分别判断该数列是否为等差数列或等比数列，进而求出下一项的值。判断等差数列时，依据相邻两项差值是否相等；判断等比数列时，为避免浮点数精度问题，通过交叉相乘变形后的等式（如 $a * c == b * b$）来判断，并且要检查等比数列下一项是否为整数。难点在于处理数据的特殊情况，如全零数列、等比数列下一项非整数的情况，以及避免等比数列判断时的精度问题。所有题解思路和代码实现都较为基础和直接，没有特别突出的优化，整体质量均未达到4星。

### 通用建议与扩展思路
 - **通用建议**：在处理这类数学判断问题时，要仔细考虑各种边界情况和特殊输入，像本题中的全零数列、等比数列下一项非整数等情况。代码实现上，注意简洁性和可读性，变量命名尽量清晰。
 - **扩展思路**：对于类似判断数列规律的题目，可以拓展到更复杂的数列类型，如斐波那契数列及其变体、高阶等差数列等。同时，可以增加输入数据的规模和复杂性，例如输入更多项的数列，或者数列中的数为小数、分数等情况，这就需要更精细地处理数据类型和精度问题。

### 洛谷相似题目推荐
 - [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：涉及到最长不上升子序列和最长上升子序列的求解，与本题一样需要分析数列规律。
 - [P1089 津津的储蓄计划](https://www.luogu.com.cn/problem/P1089)：通过对每月收支数据的分析处理，得出最终结果，和本题对数列数据的分析处理类似。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：需要根据给定条件分析等式的组成规律，与本题判断数列规律属于同一类思考方式。 

---
处理用时：31.19秒