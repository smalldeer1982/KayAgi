---
title: "Penchick and Desert Rabbit"
layout: "post"
diff: 普及/提高-
pid: CF2031D
tag: ['动态规划 DP']
---

# Penchick and Desert Rabbit

## 题目描述

Dedicated to pushing himself to his limits, Penchick challenged himself to survive the midday sun in the Arabian Desert!

While trekking along a linear oasis, Penchick spots a desert rabbit preparing to jump along a line of palm trees. There are $ n $ trees, each with a height denoted by $ a_i $ .

The rabbit can jump from the $ i $ -th tree to the $ j $ -th tree if exactly one of the following conditions is true:

- $ j < i $ and $ a_j > a_i $ : the rabbit can jump backward to a taller tree.
- $ j > i $ and $ a_j < a_i $ : the rabbit can jump forward to a shorter tree.

For each $ i $ from $ 1 $ to $ n $ , determine the maximum height among all trees that the rabbit can reach if it starts from the $ i $ -th tree.

## 输入格式

The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^5 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ) — the number of trees.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the height of the trees.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers. The $ i $ -th integer should contain the maximum height among all trees that the rabbit can reach if it starts from the $ i $ -th tree.

## 说明/提示

In the first test case, the initial heights of trees are $ a = [2, 3, 1, 4] $ .

- If the rabbit starts from the first tree, it can jump to the third tree as $ 3 > 1 $ and $ 1 < 2 $ . Then, the rabbit can jump to the second tree as $ 2 < 3 $ and $ 3 > 1 $ . It can be proved that the rabbit cannot reach the fourth tree; hence, the maximum height of the tree that the rabbit can reach is $ a_2 = 3 $ .
- If the rabbit starts from the fourth tree, it does not need to jump anywhere as it is already at the highest tree.

In the second test case, the rabbit can jump to the first tree regardless of which tree it starts from.

In the fifth test case, if the rabbit starts from the fifth tree, it can jump to the fourth tree. Then the rabbit can jump to the seventh tree and finally reach the sixth tree. Therefore, the maximum height of the tree that the rabbit can reach is $ 8 $ .

## 样例 #1

### 输入

```
5
4
2 3 1 4
5
5 4 3 2 1
4
2 1 1 3
4
1 1 3 1
8
2 4 1 6 3 8 5 7
```

### 输出

```
3 3 3 4 
5 5 5 5 5 
2 2 2 3 
1 1 3 3 
8 8 8 8 8 8 8 8
```

