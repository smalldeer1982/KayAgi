---
title: "Optimizer"
layout: "post"
diff: 普及+/提高
pid: CF306B
tag: []
---

# Optimizer

## 题目描述

A process RAM is a sequence of bytes that are indexed from 1 to $ n $ . Polycarpus's program contains such instructions as "memset", that is, the operations of filling memory cells on a segment with some value. The details are: the code only contains $ m $ instructions that look like "set13 a\_i l\_i". Instruction $ i $ fills a continuous memory segment of length $ l_{i} $ , starting from cell number $ a_{i} $ , (that it cells with numbers $ a_{i},a_{i}+1,...,a_{i+li}-1 $ ) with values 13.

In Polycarpus's code, the optimizer's task is to remove the maximum number of instructions from his code in such a way that the remaining instructions set value 13 in all the memory bytes that got this value from the code before the optimization. Also, the value 13 should be set only in the memory bytes that got this value from the code before the optimization. Your task is to implement the optimizer for such program.

## 输入格式

The first line contains integers $ n $ and $ m $ ( $ 1<=n<=2·10^{6},1<=m<=2·10^{5} $ ) — the number of bytes (memory cells) and the number of instructions in Polycarpus's code. Then $ m $ lines follow, each line contains a pair of integers $ a_{i} $ , $ l_{i} $ ( $ 1<=a_{i}<=n,1<=l_{i}<=n-a_{i}+1 $ ).

## 输出格式

Print in the first line the sought maximum number of instructions that can be removed from the code. In the second line print the numbers of the instructions. The instructions are numbered from 1 to $ m $ in the order they appeared in the input. If there are multiple solutions, print any of them.

## 样例 #1

### 输入

```
10 4
3 3
3 1
4 1
9 2

```

### 输出

```
2
2 3 
```

## 样例 #2

### 输入

```
1 1
1 1

```

### 输出

```
0

```

