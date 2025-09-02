---
title: "Selling Numbers"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF778E
tag: []
---

# Selling Numbers

## 题目描述

Boris really likes numbers and even owns a small shop selling interesting numbers. He has $ n $ decimal numbers $ B_{i} $ . Cost of the number in his shop is equal to the sum of costs of its digits. You are given the values $ c_{d} $ , where $ c_{d} $ is the cost of the digit $ d $ . Of course, Boris is interested in that numbers he owns have the maximum cost possible.

Recently Boris got hold of the magical artifact $ A $ , which can allow him to increase the cost of his collection. Artifact is a string, consisting of digits and '?' symbols. To use the artifact, Boris must replace all '?' with digits to get a decimal number without leading zeros (it is also not allowed to get number 0). After that, the resulting number is added to all numbers $ B_{i} $ in Boris' collection. He uses the artifact exactly once.

What is the maximum cost of the collection Boris can achieve after using the artifact?

## 输入格式

First line contains artifact $ A $ , consisting of digits '0'–'9' and '?' symbols ( $ 1<=|A|<=1000 $ ). Next line contains $ n $ — the amount of numbers in Boris' collection ( $ 1<=n<=1000 $ ). Next $ n $ lines contain integers $ B_{i} $ ( $ 1<=B_{i}&lt;10^{1000} $ ). $ A $ doesn't start with '0'.

Last line contains ten integers — costs of digits $ c_{0},c_{1},...,c_{9} $ ( $ 0<=c_{i}<=1000 $ ).

## 输出格式

Output one integer — the maximum possible cost of the collection after using the artifact.

## 说明/提示

In the second sample input, the optimal way is to compose the number 453. After adding this number, Boris will have numbers 2656, 5682, 729 and 6696. The total cost of all digits in them is equal to $ 18+15+11+18=62 $ .

## 样例 #1

### 输入

```
42
3
89
1
958
0 0 1 1 2 2 3 3 4 4

```

### 输出

```
4

```

## 样例 #2

### 输入

```
?5?
4
2203
5229
276
6243
2 1 6 1 1 2 5 2 2 3

```

### 输出

```
62

```

