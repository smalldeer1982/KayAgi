---
title: "Squares and Cubes"
layout: "post"
diff: 入门
pid: CF1619B
tag: []
---

# Squares and Cubes

## 题目描述

Polycarp likes squares and cubes of positive integers. Here is the beginning of the sequence of numbers he likes: $ 1 $ , $ 4 $ , $ 8 $ , $ 9 $ , ....

For a given number $ n $ , count the number of integers from $ 1 $ to $ n $ that Polycarp likes. In other words, find the number of such $ x $ that $ x $ is a square of a positive integer number or a cube of a positive integer number (or both a square and a cube simultaneously).

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 20 $ ) — the number of test cases.

Then $ t $ lines contain the test cases, one per line. Each of the lines contains one integer $ n $ ( $ 1 \le n \le 10^9 $ ).

## 输出格式

For each test case, print the answer you are looking for — the number of integers from $ 1 $ to $ n $ that Polycarp likes.

## 样例 #1

### 输入

```
6
10
1
25
1000000000
999999999
500000000
```

### 输出

```
4
1
6
32591
32590
23125
```

