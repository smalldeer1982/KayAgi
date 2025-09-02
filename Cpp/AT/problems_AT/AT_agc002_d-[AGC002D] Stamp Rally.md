---
title: "[AGC002D] Stamp Rally"
layout: "post"
diff: 省选/NOI-
pid: AT_agc002_d
tag: ['并查集', '栈', '整体二分']
---

# [AGC002D] Stamp Rally

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc002/tasks/agc002_d



## 输入格式

第一行两个正整数，代表 $N$ 和 $M$。

接下来 $M$ 行，第 $i$ 行有两个正整数 $a_i,b_i$，代表 $a_i$ 和 $b_i$ 之间有一条无向边。

接下来一行有一个正整数，代表 $Q$。

接下来 $Q$ 行，第 $i$ 行有三个整数 $x_i,y_i,z_i$，表示一种询问。

## 输出格式

对于每个询问，输出一行一个整数表示答案。

## 样例 #1

### 输入

```
5 6
2 3
4 5
1 2
1 3
1 4
1 5
6
2 4 3
2 4 4
2 4 5
1 3 3
1 3 4
1 3 5

```

### 输出

```
1
2
3
1
5
5

```

