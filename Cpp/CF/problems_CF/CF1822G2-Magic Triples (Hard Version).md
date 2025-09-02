---
title: "Magic Triples (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1822G2
tag: []
---

# Magic Triples (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version, $ a_i \le 10^9 $ .

For a given sequence of $ n $ integers $ a $ , a triple $ (i, j, k) $ is called magic if:

- $ 1 \le i, j, k \le n $ .
- $ i $ , $ j $ , $ k $ are pairwise distinct.
- there exists a positive integer $ b $ such that $ a_i \cdot b = a_j $ and $ a_j \cdot b = a_k $ .

Kolya received a sequence of integers $ a $ as a gift and now wants to count the number of magic triples for it. Help him with this task!

Note that there are no constraints on the order of integers $ i $ , $ j $ and $ k $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of the test case contains a single integer $ n $ ( $ 3 \le n \le 2 \cdot 10^5 $ ) — the length of the sequence.

The second line of the test contains $ n $ integers $ a_1, a_2, a_3, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the sequence $ a $ .

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of magic triples for the sequence $ a $ .

## 说明/提示

In the first example, there are $ 6 $ magic triples for the sequence $ a $ — $ (2, 3, 5) $ , $ (2, 5, 3) $ , $ (3, 2, 5) $ , $ (3, 5, 2) $ , $ (5, 2, 3) $ , $ (5, 3, 2) $ .

In the second example, there is a single magic triple for the sequence $ a $ — $ (2, 1, 3) $ .

## 样例 #1

### 输入

```
7
5
1 7 7 2 7
3
6 2 18
9
1 2 3 4 5 6 7 8 9
4
1000 993 986 179
7
1 10 100 1000 10000 100000 1000000
8
1 1 2 2 4 4 8 8
9
1 1 1 2 2 2 4 4 4
```

### 输出

```
6
1
3
0
9
16
45
```

