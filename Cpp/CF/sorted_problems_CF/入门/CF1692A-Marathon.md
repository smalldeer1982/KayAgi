---
title: "Marathon"
layout: "post"
diff: 入门
pid: CF1692A
tag: []
---

# Marathon

## 题目描述

You are given four distinct integers $ a $ , $ b $ , $ c $ , $ d $ .

Timur and three other people are running a marathon. The value $ a $ is the distance that Timur has run and $ b $ , $ c $ , $ d $ correspond to the distances the other three participants ran.

Output the number of participants in front of Timur.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The description of each test case consists of four distinct integers $ a $ , $ b $ , $ c $ , $ d $ ( $ 0 \leq a, b, c, d \leq 10^4 $ ).

## 输出格式

For each test case, output a single integer — the number of participants in front of Timur.

## 说明/提示

For the first test case, there are $ 2 $ people in front of Timur, specifically the participants who ran distances of $ 3 $ and $ 4 $ . The other participant is not in front of Timur because he ran a shorter distance than Timur.

For the second test case, no one is in front of Timur, since he ran a distance of $ 10000 $ while all others ran a distance of $ 0 $ , $ 1 $ , and $ 2 $ respectively.

For the third test case, only the second person is in front of Timur, who ran a total distance of $ 600 $ while Timur ran a distance of $ 500 $ .

## 样例 #1

### 输入

```
4
2 3 4 1
10000 0 1 2
500 600 400 300
0 9999 10000 9998
```

### 输出

```
2
0
1
3
```

