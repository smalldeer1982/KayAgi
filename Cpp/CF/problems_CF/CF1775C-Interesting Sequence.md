---
title: "Interesting Sequence"
layout: "post"
diff: 普及+/提高
pid: CF1775C
tag: []
---

# Interesting Sequence

## 题目描述

Petya and his friend, robot Petya++, like to solve exciting math problems.

One day Petya++ came up with the numbers $ n $ and $ x $ and wrote the following equality on the board: $ $$$n\ \&\ (n+1)\ \&\ \dots\ \&\ m = x, $ $  where  $ \\&amp; $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#AND">bitwise AND operation</a>. Then he suggested his friend Petya find such a minimal  $ m $  ( $ m \\ge n$$$) that the equality on the board holds.

Unfortunately, Petya couldn't solve this problem in his head and decided to ask for computer help. He quickly wrote a program and found the answer.

Can you solve this difficult problem?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775C/3708862555546ebb5c352c2d2207eacbd490398b.png)

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 2000 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ , $ x $ ( $ 0\le n, x \le 10^{18} $ ).

## 输出格式

For every test case, output the smallest possible value of $ m $ such that equality holds.

If the equality does not hold for any $ m $ , print $ -1 $ instead.

We can show that if the required $ m $ exists, it does not exceed $ 5 \cdot 10^{18} $ .

## 说明/提示

In the first example, $ 10\ \&\ 11 = 10 $ , but $ 10\ \&\ 11\ \&\ 12 = 8 $ , so the answer is $ 12 $ .

In the second example, $ 10 = 10 $ , so the answer is $ 10 $ .

In the third example, we can see that the required $ m $ does not exist, so we have to print $ -1 $ .

## 样例 #1

### 输入

```
5
10 8
10 10
10 42
20 16
1000000000000000000 0
```

### 输出

```
12
10
-1
24
1152921504606846976
```

