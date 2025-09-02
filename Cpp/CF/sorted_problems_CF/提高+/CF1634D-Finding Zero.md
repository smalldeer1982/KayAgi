---
title: "Finding Zero"
layout: "post"
diff: 提高+/省选-
pid: CF1634D
tag: ['数学']
---

# Finding Zero

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1634D/74895b22455b2b459cd8609f4caa3df7273f47e6.png)This is an interactive problem.

We picked an array of whole numbers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) and concealed exactly one zero in it! Your goal is to find the location of this zero, that is, to find $ i $ such that $ a_i = 0 $ .

You are allowed to make several queries to guess the answer. For each query, you can think up three distinct indices $ i, j, k $ , and we will tell you the value of $ \max(a_i, a_j, a_k) - \min(a_i, a_j, a_k) $ . In other words, we will tell you the difference between the maximum and the minimum number among $ a_i $ , $ a_j $ and $ a_k $ .

You are allowed to make no more than $ 2 \cdot n - 2 $ queries, and after that you have two tries to guess where the zero is. That is, you have to tell us two numbers $ i $ and $ j $ and you win if $ a_i = 0 $ or $ a_j = 0 $ .

Can you guess where we hid the zero?

Note that the array in each test case is fixed beforehand and will not change during the game. In other words, the interactor is not adaptive.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). Description of the test cases follows.

The first and only line of each test case contains an integer $ n $ ( $ 4 \le n \le 1000 $ ) — the length of the array that we picked.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3000 $ .

## 输出格式

For each test case, the interaction starts with reading $ n $ .

To make a query, print "? $ i $ $ j $ $ k $ " (without quotes, $ 1 \le i, j, k \le n $ , indices must be distinct). Then you should read our response from standard input, that is, $ \max(a_i, a_j, a_k) - \min(a_i, a_j, a_k) $ .

If the response is $ -1 $ , it means your program has made an invalid query or has run out of tries. Your program must terminate immediately after reading $ -1 $ , and you will get a verdict Wrong answer. Otherwise you may get any verdict, because the program will continue reading from the closed stream. Note that if the query is correct, the answer will never be $ -1 $ because $ \max(a_i, a_j, a_k) - \min(a_i, a_j, a_k) \geq 0 $ .

To give the final answer, print "! $ i $ $ j $ " (without the quotes). Printing the same number twice (that is, $ i = j $ ) is allowed. Note that giving this answer is not counted towards the limit of $ 2 \cdot n - 2 $ queries. After that, your program must continue to solve the remaining test cases, or exit if all test cases have been solved.

After printing a query, don't forget to output line feed and flush the output buffer. Otherwise you will get the verdict Idleness limit exceeded. To flush the buffer, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- Read documentation for other languages.

Hacks

The first line must contain an integer $ t $ ( $ 1 \le t \le 500 $ ) — the count of test cases.

The first line of each test case must contain an integer $ n $ ( $ 4 \le n \le 1000 $ ) — the length of the hidden array.

The second line of each test case must contain $ n $ integers separated by spaces — $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ). There must also be exactly one zero in this array.

The sum of $ n $ over all test cases must not exceed $ 3000 $ .

## 说明/提示

Array from sample: $ [1, 2, 0, 3] $ .

## 样例 #1

### 输入

```
1

4

2

3

3

2
```

### 输出

```
? 1 2 3

? 2 3 4

? 3 4 1

? 4 1 2

! 2 3
```

