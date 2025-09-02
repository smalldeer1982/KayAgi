---
title: "RNUMBER - Random Number"
layout: "post"
diff: 难度0
pid: SP407
tag: []
---

# RNUMBER - Random Number

## 题目描述

有一个黑盒算法假设自然数序列 $u(1), u(2), \dots, u(N)$ 按非递减顺序排列，且满足 $N \le M$。对于每个 $p$（$1 \le p \le N$），序列元素满足 $p \le u(p) \le M$。

为了测试这个算法，我们发现生成随机序列 ${u(i)}$ 时遇到了一些问题。由于序列必须满足特定条件，普通的随机数据生成器无法生成整体符合要求的随机序列。

我们认为可以通过将所有可能的序列按某种顺序排列（比如字典序），然后为每个序列分配一个编号。当选择了随机编号后，就可以取出对应的序列。看似简单，只需编写一个程序按顺序生成这些序列即可。然而，即使 $M$ 和 $N$ 的值不大，当今的计算机也需要很长时间才能枚举所有的序列。实际上，我们可以不生成所有序列，而是根据给定编号直接创建所需的序列。同时，由于序列数量庞大，该编号会非常长，可能高达数百位十进制数，而我们只能够生成普通数字。因此，我们决定将随机数生成器产生的 [0,1] 连续区间中的实数，转换为一个长随机数。为此，我们将实数表示为二进制小数形式 $0.b(1)b(2)\dots$，其中每个 $b(i)$ 取值为 0 或 1，然后设定规则将这个实数对应到区间 [_A_, _B_] 中的某个整数。

## 输入格式

输入第一行为一个整数 $K \le 10$，表示有 $K$ 组数据。

每组数据包含两行：第一行为 $M$ 和 $N$，第二行为一个无前导或尾随空格的二进制实数 $0.b(1)b(2) \dots b(p)$。

## 输出格式

对于每组数据，输出相应的序列 $u(1), u(2), \dots, u(N)$。序列中的数字以空格隔开，并以换行符分行。每行最多可以包含20个数字。如果需要，数字前面可以填充空格以使其占据3个字符的位置。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
The first line of the input is an integer K &#8804; 10, followed by K datasets.
The first line of each dataset contains M and N. The second line
contains binary real
number 

(without leading, trailing and other spaces).
```

### 输出

```
For each dataset, write into the output data file the corresponding sequence
.
The
sequence numbers should be separated with spaces and end-of-line characters.
There should be up to 20 numbers in each line. If neccesary, the numbers will have leading blanks to occupy 3 characters.

Example


Input:

1
4 3
0.01101101011110010001101010001011010

Output:

  2   2   4
```

## 样例 #2

### 输入

```
1
4 3
0.01101101011110010001101010001011010
```

### 输出

```
None
```

