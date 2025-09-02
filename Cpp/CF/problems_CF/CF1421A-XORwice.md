---
title: "XORwice"
layout: "post"
diff: 入门
pid: CF1421A
tag: []
---

# XORwice

## 题目描述

In order to celebrate Twice's 5th anniversary, Tzuyu and Sana decided to play a game.

Tzuyu gave Sana two integers $ a $ and $ b $ and a really important quest.

In order to complete the quest, Sana has to output the smallest possible value of ( $ a \oplus x $ ) + ( $ b \oplus x $ ) for any given $ x $ , where $ \oplus $ denotes the [bitwise XOR operation](http://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^{4} $ ). Description of the test cases follows.

The only line of each test case contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^{9} $ ).

## 输出格式

For each testcase, output the smallest possible value of the given expression.

## 说明/提示

For the first test case Sana can choose $ x=4 $ and the value will be ( $ 6 \oplus 4 $ ) + ( $ 12 \oplus 4 $ ) = $ 2 + 8 $ = $ 10 $ . It can be shown that this is the smallest possible value.

## 样例 #1

### 输入

```
6
6 12
4 9
59 832
28 14
4925 2912
1 1
```

### 输出

```
10
13
891
18
6237
0
```

