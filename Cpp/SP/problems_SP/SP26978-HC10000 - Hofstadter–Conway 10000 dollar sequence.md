---
title: "HC10000 - Hofstadter–Conway 10000 dollar sequence"
layout: "post"
diff: 难度0
pid: SP26978
tag: []
---

# HC10000 - Hofstadter–Conway 10000 dollar sequence

## 题目描述

Hofstadter–Conway $10,000 sequence is a famous sequence, which is defined as $$ a_1 = a_2 = 1,\,   a_{n} = a_{a_{n-1}} + a_{n-a_{n-1}}\, (n \ge 3). $$

Your task is to find a summatory function $ S(n) := \sum\limits_{i=1}^n a_i $ and compute $ S(n) $ **modulo** $ 10^9 $ .

## 输入格式

The first line contains $ T $ ( $ 1 \le T \le 10000 $ ), the number of test cases.

Each of the next $ T $ lines contains a positive integer $ n $ ( $ 1 \le n \le 10^{18} $ ).

## 输出格式

For each test case, print $ S(n) $ **modulo** $ 10^9 $ .

## 样例 #1

### 输入

```
10
1
2
3
4
5
10
100
1000
1000000
1000000000
```

### 输出

```
1
2
4
6
9
32
2818
269446
334706485
137951847
```

