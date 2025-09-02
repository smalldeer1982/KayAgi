---
title: "Adjacent Digit Sums"
layout: "post"
diff: 难度0
pid: CF2067A
tag: []
---

# Adjacent Digit Sums

## 题目描述

You are given two numbers $ x, y $ . You need to determine if there exists an integer $ n $ such that $ S(n) = x $ , $ S(n + 1) = y $ .

Here, $ S(a) $ denotes the sum of the digits of the number $ a $ in the decimal numeral system.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ x, y $ ( $ 1 \le x \le 1000, 1 \le y \le 1000 $ ).

## 输出格式

For each test case, print "NO" if a suitable $ n $ does not exist. Otherwise, output "YES".

You can output each letter in any case (for example, "YES", "Yes", "yes", "yEs", "yEs" will be recognized as a positive answer).

## 说明/提示

In the first test case, for example, $ n = 100 $ works. $ S(100) = 1 $ , $ S(101) = 2 $ .

In the second test case, it can be shown that $ S(n) \neq S(n+1) $ for all $ n $ ; therefore, the answer is No.

In the fourth test case, $ n = 10^{111}-1 $ works, which is a number consisting of $ 111 $ digits of $ 9 $ .

## 样例 #1

### 输入

```
7
1 2
77 77
997 999
999 1
1000 1
1 11
18 1
```

### 输出

```
Yes
No
No
Yes
No
No
Yes
```

