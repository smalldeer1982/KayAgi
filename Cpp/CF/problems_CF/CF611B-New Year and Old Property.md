---
title: "New Year and Old Property"
layout: "post"
diff: 普及/提高-
pid: CF611B
tag: ['位运算']
---

# New Year and Old Property

## 题目描述

The year 2015 is almost over.

Limak is a little polar bear. He has recently learnt about the binary system. He noticed that the passing year has exactly one zero in its representation in the binary system — $ 2015_{10}=11111011111_{2} $ . Note that he doesn't care about the number of zeros in the decimal representation.

Limak chose some interval of years. He is going to count all years from this interval that have exactly one zero in the binary representation. Can you do it faster?

Assume that all positive integers are always written without leading zeros.

## 输入格式

The only line of the input contains two integers $ a $ and $ b $ ( $ 1<=a<=b<=10^{18} $ ) — the first year and the last year in Limak's interval respectively.

## 输出格式

Print one integer – the number of years Limak will count in his chosen interval.

## 说明/提示

In the first sample Limak's interval contains numbers $ 5_{10}=101_{2} $ , $ 6_{10}=110_{2} $ , $ 7_{10}=111_{2} $ , $ 8_{10}=1000_{2} $ , $ 9_{10}=1001_{2} $ and $ 10_{10}=1010_{2} $ . Two of them ( $ 101_{2} $ and $ 110_{2} $ ) have the described property.

## 样例 #1

### 输入

```
5 10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2015 2015

```

### 输出

```
1

```

## 样例 #3

### 输入

```
100 105

```

### 输出

```
0

```

## 样例 #4

### 输入

```
72057594000000000 72057595000000000

```

### 输出

```
26

```

