---
title: "Tricky Sum"
layout: "post"
diff: 普及-
pid: CF598A
tag: ['数学', '枚举']
---

# Tricky Sum

## 题目描述

In this problem you are to calculate the sum of all integers from $ 1 $ to $ n $ , but you should take all powers of two with minus in the sum.

For example, for $ n=4 $ the sum is equal to $ -1-2+3-4=-4 $ , because $ 1 $ , $ 2 $ and $ 4 $ are $ 2^{0} $ , $ 2^{1} $ and $ 2^{2} $ respectively.

Calculate the answer for $ t $ values of $ n $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1<=t<=100 $ ) — the number of values of $ n $ to be processed.

Each of next $ t $ lines contains a single integer $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Print the requested sum for each of $ t $ integers $ n $ given in the input.

## 说明/提示

The answer for the first sample is explained in the statement.

## 样例 #1

### 输入

```
2
4
1000000000

```

### 输出

```
-4
499999998352516354

```

