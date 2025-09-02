---
title: "Fair Numbers"
layout: "post"
diff: 入门
pid: CF1411B
tag: []
---

# Fair Numbers

## 题目描述

We call a positive integer number fair if it is divisible by each of its nonzero digits. For example, $ 102 $ is fair (because it is divisible by $ 1 $ and $ 2 $ ), but $ 282 $ is not, because it isn't divisible by $ 8 $ . Given a positive integer $ n $ . Find the minimum integer $ x $ , such that $ n \leq x $ and $ x $ is fair.

## 输入格式

The first line contains number of test cases $ t $ ( $ 1 \leq t \leq 10^3 $ ). Each of the next $ t $ lines contains an integer $ n $ ( $ 1 \leq n \leq 10^{18} $ ).

## 输出格式

For each of $ t $ test cases print a single integer — the least fair number, which is not less than $ n $ .

## 说明/提示

Explanations for some test cases:

- In the first test case number $ 1 $ is fair itself.
- In the second test case number $ 288 $ is fair (it's divisible by both $ 2 $ and $ 8 $ ). None of the numbers from $ [282, 287] $ is fair, because, for example, none of them is divisible by $ 8 $ .

## 样例 #1

### 输入

```
4
1
282
1234567890
1000000000000000000
```

### 输出

```
1
288
1234568040
1000000000000000000
```

