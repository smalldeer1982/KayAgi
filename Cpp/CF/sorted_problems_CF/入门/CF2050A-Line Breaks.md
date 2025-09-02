---
title: "Line Breaks"
layout: "post"
diff: 入门
pid: CF2050A
tag: ['模拟']
---

# Line Breaks

## 题目描述

Kostya has a text $ s $ consisting of $ n $ words made up of Latin alphabet letters. He also has two strips on which he must write the text. The first strip can hold $ m $ characters, while the second can hold as many as needed.

Kostya must choose a number $ x $ and write the first $ x $ words from $ s $ on the first strip, while all the remaining words are written on the second strip. To save space, the words are written without gaps, but each word must be entirely on one strip.

Since space on the second strip is very valuable, Kostya asks you to choose the maximum possible number $ x $ such that all words $ s_1, s_2, \dots, s_x $ fit on the first strip of length $ m $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 50 $ ; $ 1 \le m \le 500 $ ) — the number of words in the list and the maximum number of characters that can be on the first strip.

The next $ n $ lines contain one word $ s_i $ of lowercase Latin letters, where the length of $ s_i $ does not exceed $ 10 $ .

## 输出格式

For each test case, output the maximum number of words $ x $ such that the first $ x $ words have a total length of no more than $ m $ .

## 样例 #1

### 输入

```
5
3 1
a
b
c
2 9
alpha
beta
4 12
hello
world
and
codeforces
3 2
ab
c
d
3 2
abc
ab
a
```

### 输出

```
1
2
2
1
0
```

