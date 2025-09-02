---
title: "Double Sort II"
layout: "post"
diff: 省选/NOI-
pid: CF1783F
tag: ['网络流', '二分图']
---

# Double Sort II

## 题目描述

You are given two permutations $ a $ and $ b $ , both of size $ n $ . A permutation of size $ n $ is an array of $ n $ elements, where each integer from $ 1 $ to $ n $ appears exactly once. The elements in each permutation are indexed from $ 1 $ to $ n $ .

You can perform the following operation any number of times:

- choose an integer $ i $ from $ 1 $ to $ n $ ;
- let $ x $ be the integer such that $ a_x = i $ . Swap $ a_i $ with $ a_x $ ;
- let $ y $ be the integer such that $ b_y = i $ . Swap $ b_i $ with $ b_y $ .

Your goal is to make both permutations sorted in ascending order (i. e. the conditions $ a_1 < a_2 < \dots < a_n $ and $ b_1 < b_2 < \dots < b_n $ must be satisfied) using minimum number of operations. Note that both permutations must be sorted after you perform the sequence of operations you have chosen.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 3000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ; all $ a_i $ are distinct).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ; all $ b_i $ are distinct).

## 输出格式

First, print one integer $ k $ ( $ 0 \le k \le 2n $ ) — the minimum number of operations required to sort both permutations. Note that it can be shown that $ 2n $ operations are always enough.

Then, print $ k $ integers $ op_1, op_2, \dots, op_k $ ( $ 1 \le op_j \le n $ ), where $ op_j $ is the value of $ i $ you choose during the $ j $ -th operation.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
5
1 3 2 4 5
2 1 3 4 5
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
2
1 2
1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
1 3 4 2
4 3 2 1
```

### 输出

```
2
3 4
```

