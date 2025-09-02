---
title: "Dislike of Threes"
layout: "post"
diff: 入门
pid: CF1560A
tag: ['模拟']
---

# Dislike of Threes

## 题目描述

Polycarp doesn't like integers that are divisible by $ 3 $ or end with the digit $ 3 $ in their decimal representation. Integers that meet both conditions are disliked by Polycarp, too.

Polycarp starts to write out the positive (greater than $ 0 $ ) integers which he likes: $ 1, 2, 4, 5, 7, 8, 10, 11, 14, 16, \dots $ . Output the $ k $ -th element of this sequence (the elements are numbered from $ 1 $ ).

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case consists of one line containing one integer $ k $ ( $ 1 \le k \le 1000 $ ).

## 输出格式

For each test case, output in a separate line one integer $ x $ — the $ k $ -th element of the sequence that was written out by Polycarp.

## 样例 #1

### 输入

```
10
1
2
3
4
5
6
7
8
9
1000
```

### 输出

```
1
2
4
5
7
8
10
11
14
1666
```

