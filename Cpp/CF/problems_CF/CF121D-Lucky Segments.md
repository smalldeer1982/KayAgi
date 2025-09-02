---
title: "Lucky Segments"
layout: "post"
diff: 提高+/省选-
pid: CF121D
tag: []
---

# Lucky Segments

## 题目描述

Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya has $ n $ number segments $ [l_{1}; r_{1}] $ , $ [l_{2}; r_{2}] $ , ..., $ [l_{n}; r_{n}] $ . During one move Petya can take any segment (let it be segment number $ i $ ) and replace it with segment $ [l_{i}+1; r_{i}+1] $ or $ [l_{i}-1; r_{i}-1] $ . In other words, during one move Petya can shift any segment to the left or to the right by a unit distance. Petya calls a number full if it belongs to each segment. That is, number $ x $ is full if for any $ i $ $ (1<=i<=n) $ the condition $ l_{i}<=x<=r_{i} $ is fulfilled.

Petya makes no more than $ k $ moves. After that he counts the quantity of full lucky numbers. Find the maximal quantity that he can get.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{5} $ , $ 1<=k<=10^{18}) $ — the number of segments and the maximum number of moves. Next $ n $ lines contain pairs of integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i}<=r_{i}<=10^{18}) $ .

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the %I64d specificator.

## 输出格式

Print on the single line the single number — the answer to the problem.

## 说明/提示

In the first sample Petya shifts the second segment by two units to the left (it turns into $ [4; 7] $ ), after that number $ 4 $ becomes full.

In the second sample Petya shifts the first segment by two units to the right (it turns into $ [42; 47] $ ), and shifts the second segment by three units to the left (it turns into $ [44; 71] $ ), after that numbers $ 44 $ and $ 47 $ become full.

## 样例 #1

### 输入

```
4 7
1 4
6 9
4 7
3 5

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 7
40 45
47 74

```

### 输出

```
2

```

