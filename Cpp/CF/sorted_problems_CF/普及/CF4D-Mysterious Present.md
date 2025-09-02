---
title: "Mysterious Present"
layout: "post"
diff: 普及/提高-
pid: CF4D
tag: ['动态规划 DP', '搜索', '递归']
---

# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 输入格式

The first line contains integers $ n $ , $ w $ , $ h $ ( $ 1<=n<=5000 $ , $ 1<=w,h<=10^{6} $ ) — amount of envelopes Peter has, the card width and height respectively. Then there follow $ n $ lines, each of them contains two integer numbers $ w_{i} $ and $ h_{i} $ — width and height of the $ i $ -th envelope ( $ 1<=w_{i},h_{i}<=10^{6} $ ).

## 输出格式

In the first line print the maximum chain size. In the second line print the numbers of the envelopes (separated by space), forming the required chain, starting with the number of the smallest envelope. Remember, please, that the card should fit into the smallest envelope. If the chain of maximum size is not unique, print any of the answers.

If the card does not fit into any of the envelopes, print number $ 0 $ in the single line.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2

```

### 输出

```
1
1 

```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8

```

### 输出

```
3
1 3 2 

```

