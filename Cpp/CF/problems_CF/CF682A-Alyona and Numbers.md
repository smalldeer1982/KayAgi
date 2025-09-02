---
title: "Alyona and Numbers"
layout: "post"
diff: 普及-
pid: CF682A
tag: []
---

# Alyona and Numbers

## 题目描述

After finishing eating her bun, Alyona came up with two integers $ n $ and $ m $ . She decided to write down two columns of integers — the first column containing integers from $ 1 $ to $ n $ and the second containing integers from $ 1 $ to $ m $ . Now the girl wants to count how many pairs of integers she can choose, one from the first column and the other from the second column, such that their sum is divisible by $ 5 $ .

Formally, Alyona wants to count the number of pairs of integers $ (x,y) $ such that $ 1<=x<=n $ , $ 1<=y<=m $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF682A/bb850c8c10ee7a9c00e5b1ff3da7605a7415f98c.png) equals $ 0 $ .

As usual, Alyona has some troubles and asks you to help.

## 输入格式

The only line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=1000000 $ ).

## 输出格式

Print the only integer — the number of pairs of integers $ (x,y) $ such that $ 1<=x<=n $ , $ 1<=y<=m $ and $ (x+y) $ is divisible by $ 5 $ .

## 说明/提示

Following pairs are suitable in the first sample case:

- for $ x=1 $ fits $ y $ equal to $ 4 $ or $ 9 $ ;
- for $ x=2 $ fits $ y $ equal to $ 3 $ or $ 8 $ ;
- for $ x=3 $ fits $ y $ equal to $ 2 $ , $ 7 $ or $ 12 $ ;
- for $ x=4 $ fits $ y $ equal to $ 1 $ , $ 6 $ or $ 11 $ ;
- for $ x=5 $ fits $ y $ equal to $ 5 $ or $ 10 $ ;
- for $ x=6 $ fits $ y $ equal to $ 4 $ or $ 9 $ .

Only the pair $ (1,4) $ is suitable in the third sample case.

## 样例 #1

### 输入

```
6 12

```

### 输出

```
14

```

## 样例 #2

### 输入

```
11 14

```

### 输出

```
31

```

## 样例 #3

### 输入

```
1 5

```

### 输出

```
1

```

## 样例 #4

### 输入

```
3 8

```

### 输出

```
5

```

## 样例 #5

### 输入

```
5 7

```

### 输出

```
7

```

## 样例 #6

### 输入

```
21 21

```

### 输出

```
88

```

