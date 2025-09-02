---
title: "AGS - Aritho-geometric Series (AGS)"
layout: "post"
diff: 难度0
pid: SP10966
tag: []
---

# AGS - Aritho-geometric Series (AGS)

## 题目描述

在数学中，等差数列和等比数列是两种常见的数列。

等差数列（AP）的特点是任意相邻两个数之间的差是固定的。例如，数列 1, 3, 5, 7, 9... 中，相邻两个数的差为 2。

等比数列（GP）的特点是任意相邻两个数之间的比值是固定的。例如，数列 1, 2, 4, 8, 16... 中，相邻两个数的比值为 2。

接下来，如果有一个数列满足这样的生成规则：将 $a(n)$ 乘以 $r$ 得到 $a(n+1)$，再加上 $d$ 得到 $a(n+2)$，会怎样？

例如：假设 $d=1$, $r=2$，并且 $a(1) = 1$，这个数列就是 1, 2, 4, 5, 10, 11, 22, 23, 46, 47, 94, 95, 190...

首先将 $d$ 加到 $a(1)$ 上，然后将 $a(2)$ 乘以 $r$，以此类推...

你的任务是，在已知 $a$、$d$ 和 $r$ 的情况下，计算出数列的第 $n$ 项 $a(n)$。

由于这些数可能会非常大，你需要输出结果对给定的 $mod$ 取模的值。$mod$ 将在每个测试用例中提供。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量。

每个测试用例包含两行数据：

第一行是三个整数 $a$、$d$ 和 $r$，分别表示数列的首项、差值和比率。

第二行是两个整数 $n$ 和 $mod$，分别表示你需要计算的第 $n$ 项，以及要求输出结果进行取模的值。

## 输出格式

对于每个测试用例，单独输出一行“a(n) % mod”。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2\n1 1 2\n13 7\n2 2 2\n10 8\n\n&nbsp;
```

### 输出

```
\n\n1\n6 \n\n\nDescription - for the first test case the series is 1,2,4,5,10,11,22,23,46,47,94,95,190..\n13th term is 190 and 190%7 = 1\n\nNote - the value of a , d , r , n &amp; mod will be less than 10^8 and more than 0.\nfor every series 2nd term will be a+d and third term will be (a+d)*r .. and so on ..
```

