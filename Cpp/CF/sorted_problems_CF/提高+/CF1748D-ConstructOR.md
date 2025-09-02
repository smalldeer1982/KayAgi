---
title: "ConstructOR"
layout: "post"
diff: 提高+/省选-
pid: CF1748D
tag: ['贪心', '中国剩余定理 CRT', '位运算', '构造']
---

# ConstructOR

## 题目描述

You are given three integers $ a $ , $ b $ , and $ d $ . Your task is to find any integer $ x $ which satisfies all of the following conditions, or determine that no such integers exist:

- $ 0 \le x \lt 2^{60} $ ;
- $ a|x $ is divisible by $ d $ ;
- $ b|x $ is divisible by $ d $ .

Here, $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of one line, containing three integers $ a $ , $ b $ , and $ d $ ( $ 1 \le a,b,d \lt 2^{30} $ ).

## 输出格式

For each test case print one integer. If there exists an integer $ x $ which satisfies all of the conditions from the statement, print $ x $ . Otherwise, print $ -1 $ .

If there are multiple solutions, you may print any of them.

## 说明/提示

In the first test case, $ x=18 $ is one of the possible solutions, since $ 39|18=55 $ and $ 12|18=30 $ , both of which are multiples of $ d=5 $ .

In the second test case, $ x=14 $ is one of the possible solutions, since $ 8|14=6|14=14 $ , which is a multiple of $ d=14 $ .

In the third and fourth test cases, we can show that there are no solutions.

## 样例 #1

### 输入

```
8
12 39 5
6 8 14
100 200 200
3 4 6
2 2 2
18 27 3
420 666 69
987654321 123456789 999999999
```

### 输出

```
18
14
-1
-1
0
11
25599
184470016815529983
```

