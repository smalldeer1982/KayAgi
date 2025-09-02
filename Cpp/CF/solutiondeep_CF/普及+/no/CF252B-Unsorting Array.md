# 题目信息

# Unsorting Array

## 题目描述

Little Petya likes arrays of integers a lot. Recently his mother has presented him one such array consisting of $ n $ elements. Petya is now wondering whether he can swap any two distinct integers in the array so that the array got unsorted. Please note that Petya can not swap equal integers even if they are in distinct positions in the array. Also note that Petya must swap some two integers even if the original array meets all requirements.

Array $ a $ (the array elements are indexed from 1) consisting of $ n $ elements is called sorted if it meets at least one of the following two conditions:

1. $ a_{1}<=a_{2}<=...<=a_{n} $ ;
2. $ a_{1}>=a_{2}>=...>=a_{n} $ .

Help Petya find the two required positions to swap or else say that they do not exist.

## 说明/提示

In the first two samples the required pairs obviously don't exist.

In the third sample you can swap the first two elements. After that the array will look like this: 2 1 3 4. This array is unsorted.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
1 2 3 4
```

### 输出

```
1 2
```

## 样例 #4

### 输入

```
3
1 1 1
```

### 输出

```
-1
```

# AI分析结果

### 题目重写
# 打乱数组

## 题目描述
小佩佳非常喜欢整数数组。最近，他妈妈送给他一个由 $n$ 个元素组成的这样的数组。佩佳现在想知道，他是否可以交换数组中任意两个不同的整数，使数组变得无序。请注意，佩佳不能交换相等的整数，即使它们在数组中的位置不同。还要注意，即使原始数组满足所有要求，佩佳也必须交换两个整数。

由 $n$ 个元素组成的数组 $a$（数组元素从 1 开始索引）如果满足以下两个条件中的至少一个，则称为已排序：
1. $a_{1} \leq a_{2} \leq \cdots \leq a_{n}$；
2. $a_{1} \geq a_{2} \geq \cdots \geq a_{n}$。

帮助佩佳找到需要交换的两个位置，否则说明它们不存在。

## 说明/提示
在前两个样例中，显然不存在所需的数对。
在第三个样例中，你可以交换前两个元素。之后数组将变为：2 1 3 4。这个数组是无序的。

## 样例 #1
### 输入
```
1
1
```
### 输出
```
-1
```

## 样例 #2
### 输入
```
2
1 2
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
4
1 2 3 4
```
### 输出
```
1 2
```

## 样例 #4
### 输入
```
3
1 1 1
```
### 输出
```
-1
```

### 算法分类
枚举

### 综合分析与结论
所有题解思路基本一致，均先对 $n\leq2$ 以及数组元素全相同（即排序后数组与原数组相同）的情况进行特判，确定无解直接输出 -1。之后通过双重循环枚举所有可交换的不同元素对，每次交换后判断数组是否既非升序也非降序，若是则输出交换位置并结束程序，否则还原继续枚举，若所有情况都不满足则输出 -1。虽然暴力枚举时间复杂度为 $O(n^3)$（包含排序的 $O(nlogn)$ 以及双重循环枚举 $O(n^2)$），但实际运行时，由于满足条件的情况出现概率较高，往往远跑不满该复杂度就能得出结果。

### 通用建议与扩展思路
对于此类判断数组是否可通过特定操作变为无序的问题，通常先分析特殊情况进行特判，减少不必要的计算。在暴力枚举时，要注意边界条件以及状态的还原。扩展思路方面，可以考虑增加限制条件，如交换次数限制等，或者改变判断无序的条件，拓展为更复杂的序列判断问题。

### 相似知识点洛谷题目
1. [P1116 车厢重组](https://www.luogu.com.cn/problem/P1116)：通过交换相邻车厢，求最少交换次数使车厢编号有序，涉及排序与交换操作。
2. [P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)：在给定数组中通过各种方式找到第 k 小的数，可使用排序相关知识。
3. [P1059 [NOIP2006 普及组] 明明的随机数](https://www.luogu.com.cn/problem/P1059)：对输入的随机数去重并排序输出，考查排序与去重操作。

### 个人心得摘录与总结
lin_er的题解中分析了看似 $O(n^3)$ 的暴力能通过大数据范围的原因，总结出数组中数的种类不同时，制造无序数组的概率情况，有助于理解暴力算法在本题中的可行性。 

---
处理用时：32.45秒