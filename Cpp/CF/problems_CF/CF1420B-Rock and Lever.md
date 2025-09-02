---
title: "Rock and Lever"
layout: "post"
diff: 普及/提高-
pid: CF1420B
tag: []
---

# Rock and Lever

## 题目描述

"You must lift the dam. With a lever. I will give it to you.You must block the canal. With a rock. I will not give the rock to you."





Danik urgently needs rock and lever! Obviously, the easiest way to get these things is to ask Hermit Lizard for them.

Hermit Lizard agreed to give Danik the lever. But to get a stone, Danik needs to solve the following task.

You are given a positive integer $ n $ , and an array $ a $ of positive integers. The task is to calculate the number of such pairs $ (i,j) $ that $ i<j $ and $ a_i $ $ \& $ $ a_j \ge a_i \oplus a_j $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Danik has solved this task. But can you solve it?

## 输入格式

Each test contains multiple test cases.

The first line contains one positive integer $ t $ ( $ 1 \le t \le 10 $ ) denoting the number of test cases. Description of the test cases follows.

The first line of each test case contains one positive integer $ n $ ( $ 1 \le n \le 10^5 $ ) — length of the array.

The second line contains $ n $ positive integers $ a_i $ ( $ 1 \le a_i \le 10^9 $ ) — elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For every test case print one non-negative integer — the answer to the problem.

## 说明/提示

In the first test case there is only one pair: $ (4,7) $ : for it $ 4 $ $ \& $ $ 7 = 4 $ , and $ 4 \oplus 7 = 3 $ .

In the second test case all pairs are good.

In the third test case there are two pairs: $ (6,5) $ and $ (2,3) $ .

In the fourth test case there are no good pairs.

## 样例 #1

### 输入

```
5
5
1 4 3 7 10
3
1 1 1
4
6 2 5 3
2
2 4
1
1
```

### 输出

```
1
3
2
0
0
```

