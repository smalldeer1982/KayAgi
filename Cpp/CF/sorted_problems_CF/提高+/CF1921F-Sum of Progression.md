---
title: "Sum of Progression"
layout: "post"
diff: 提高+/省选-
pid: CF1921F
tag: ['根号分治']
---

# Sum of Progression

## 题目描述

You are given an array $ a $ of $ n $ numbers. There are also $ q $ queries of the form $ s, d, k $ .

For each query $ q $ , find the sum of elements $ a_s + a_{s+d} \cdot 2 + \dots + a_{s + d \cdot (k - 1)} \cdot k $ . In other words, for each query, it is necessary to find the sum of $ k $ elements of the array with indices starting from the $ s $ -th, taking steps of size $ d $ , multiplying it by the serial number of the element in the resulting sequence.

## 输入格式

Each test consists of several testcases. The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases. Next lines contain descriptions of testcases.

The first line of each testcase contains two numbers $ n, q $ ( $ 1 \le n \le 10^5, 1 \le q \le 2 \cdot 10^5 $ ) — the number of elements in the array $ a $ and the number of queries.

The second line contains $ n $ integers $ a_1, ... a_n $ ( $ -10^8 \le a_1, ..., a_n \le 10^8 $ ) — elements of the array $ a $ .

The next $ q $ lines each contain three integers $ s $ , $ d $ , and $ k $ ( $ 1 \le s, d, k \le n $ , $ s + d\cdot (k - 1) \le n $ ).

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 10^5 $ , and that the sum of $ q $ over all testcases does not exceed $ 2 \cdot 10^5  $ .

## 输出格式

For each testcase, print $ q $ numbers in a separate line — the desired sums, separated with space.

## 样例 #1

### 输入

```
5
3 3
1 1 2
1 2 2
2 2 1
1 1 2
3 1
-100000000 -100000000 -100000000
1 1 3
5 3
1 2 3 4 5
1 2 3
2 3 2
1 1 5
3 1
100000000 100000000 100000000
1 1 3
7 7
34 87 5 42 -44 66 -32
2 2 2
4 3 1
1 3 2
6 2 1
5 2 2
2 5 2
6 1 2
```

### 输出

```
5 1 3 
-600000000 
22 12 55 
600000000 
171 42 118 66 -108 23 2
```

