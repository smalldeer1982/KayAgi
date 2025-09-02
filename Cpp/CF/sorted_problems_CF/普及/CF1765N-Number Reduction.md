---
title: "Number Reduction"
layout: "post"
diff: 普及/提高-
pid: CF1765N
tag: []
---

# Number Reduction

## 题目描述

You are given a positive integer $ x $ .

You can apply the following operation to the number: remove one occurrence of any digit in such a way that the resulting number does not contain any leading zeroes and is still a positive integer. For example, $ 10142 $ can be converted to $ 1142 $ , $ 1042 $ , $ 1012 $ or $ 1014 $ (note that $ 0142 $ is not a valid outcome); $ 10 $ can be converted to $ 1 $ (but not to $ 0 $ since it is not positive).

Your task is to find the minimum positive integer that you can obtain from $ x $ if you can apply the aforementioned operation exactly $ k $ times.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

The first line of each test case contains a single integer $ x $ ( $ 1 \le x < 10^{500000} $ ).

The second line contains a single integer $ k $ ( $ 0 \le k < |x| $ ), where $ |x| $ is the length of the number $ x $ .

The sum of $ |x| $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the minimum positive number that you can obtain from $ x $ if you can apply the operation exactly $ k $ times.

## 样例 #1

### 输入

```
5
10000
4
1337
0
987654321
6
66837494128
5
7808652
3
```

### 输出

```
1
1337
321
344128
7052
```

