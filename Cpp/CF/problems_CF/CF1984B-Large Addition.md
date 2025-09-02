---
title: "Large Addition"
layout: "post"
diff: 普及-
pid: CF1984B
tag: ['数学']
---

# Large Addition

## 题目描述

A digit is large if it is between $ 5 $ and $ 9 $ , inclusive. A positive integer is large if all of its digits are large.

You are given an integer $ x $ . Can it be the sum of two large positive integers with the same number of digits?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The only line of each test case contains a single integer $ x $ ( $ 10 \leq x \leq 10^{18} $ ).

## 输出格式

For each test case, output $ \texttt{YES} $ if $ x $ satisfies the condition, and $ \texttt{NO} $ otherwise.

You can output $ \texttt{YES} $ and $ \texttt{NO} $ in any case (for example, strings $ \texttt{yES} $ , $ \texttt{yes} $ , and $ \texttt{Yes} $ will be recognized as a positive response).

## 说明/提示

In the first test case, we can have $ 658 + 679 = 1337 $ .

In the second test case, it can be shown that no numbers of equal length and only consisting of large digits can add to $ 200 $ .

In the third test case, we can have $ 696\,969 + 696\,969 = 1\,393\,938 $ .

In the fourth test case, we can have $ 777 + 657 = 1434 $ .

## 样例 #1

### 输入

```
11
1337
200
1393938
1434
98765432123456789
11111111111111111
420
1984
10
69
119
```

### 输出

```
YES
NO
YES
YES
NO
YES
NO
YES
YES
NO
NO
```

