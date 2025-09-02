---
title: "Hossam and Friends"
layout: "post"
diff: 普及/提高-
pid: CF1771B
tag: []
---

# Hossam and Friends

## 题目描述

Hossam makes a big party, and he will invite his friends to the party.

He has $ n $ friends numbered from $ 1 $ to $ n $ . They will be arranged in a queue as follows: $ 1, 2, 3, \ldots, n $ .

Hossam has a list of $ m $ pairs of his friends that don't know each other. Any pair not present in this list are friends.

A subsegment of the queue starting from the friend $ a $ and ending at the friend $ b $ is $ [a, a + 1, a + 2, \ldots, b] $ . A subsegment of the queue is called good when all pairs of that segment are friends.

Hossam wants to know how many pairs $ (a, b) $ there are ( $ 1 \le a \le b \le n $ ), such that the subsegment starting from the friend $ a $ and ending at the friend $ b $ is good.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ), the number of test cases. Description of the test cases follows.

The first line of each test case contains two integer numbers $ n $ and $ m $ ( $ 2 \le n \le 10^5 $ , $ 0 \le m \le 10^5 $ ) representing the number of friends and the number of pairs, respectively.

The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i\le n $ , $ x_i \neq y_i $ ) representing a pair of Hossam's friends that don't know each other.

Note that pairs can be repeated.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , and the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print an integer — the number of good subsegments.

## 说明/提示

In the first example, the answer is $ 4 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[1, 2\]

In the second example, the answer is $ 5 $ .

The good subsegments are:

\[1\]

\[2\]

\[3\]

\[4\]

\[3, 4\]

## 样例 #1

### 输入

```
2
3 2
1 3
2 3
4 2
1 2
2 3
```

### 输出

```
4
5
```

