---
title: "Vasya and Robot"
layout: "post"
diff: 普及/提高-
pid: CF354A
tag: []
---

# Vasya and Robot

## 题目描述

Vasya has $ n $ items lying in a line. The items are consecutively numbered by numbers from $ 1 $ to $ n $ in such a way that the leftmost item has number $ 1 $ , the rightmost item has number $ n $ . Each item has a weight, the $ i $ -th item weights $ w_{i} $ kilograms.

Vasya needs to collect all these items, however he won't do it by himself. He uses his brand new robot. The robot has two different arms — the left one and the right one. The robot can consecutively perform the following actions:

1. Take the leftmost item with the left hand and spend $ w_{i}·l $ energy units ( $ w_{i} $ is a weight of the leftmost item, $ l $ is some parameter). If the previous action was the same (left-hand), then the robot spends extra $ Q_{l} $ energy units;
2. Take the rightmost item with the right hand and spend $ w_{j}·r $ energy units ( $ w_{j} $ is a weight of the rightmost item, $ r $ is some parameter). If the previous action was the same (right-hand), then the robot spends extra $ Q_{r} $ energy units;

Naturally, Vasya wants to program the robot in a way that the robot spends as little energy as possible. He asked you to solve this problem. Your task is to find the minimum number of energy units robot spends to collect all items.

## 输入格式

The first line contains five integers $ n,l,r,Q_{l},Q_{r} $ $ (1<=n<=10^{5};1<=l,r<=100;1<=Q_{l},Q_{r}<=10^{4}) $ .

The second line contains $ n $ integers $ w_{1},w_{2},...,w_{n} $ $ (1<=w_{i}<=100) $ .

## 输出格式

In the single line print a single number — the answer to the problem.

## 说明/提示

Consider the first sample. As $ l=r $ , we can take an item in turns: first from the left side, then from the right one and last item from the left. In total the robot spends $ 4·42+4·99+4·3=576 $ energy units.

The second sample. The optimal solution is to take one item from the right, then one item from the left and two items from the right. In total the robot spends $ (2·4)+(7·1)+(2·3)+(2·2+9)=34 $ energy units.

## 样例 #1

### 输入

```
3 4 4 19 1
42 3 99

```

### 输出

```
576

```

## 样例 #2

### 输入

```
4 7 2 3 9
1 2 3 4

```

### 输出

```
34

```

