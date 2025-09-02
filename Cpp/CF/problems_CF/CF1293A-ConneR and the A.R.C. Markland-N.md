---
title: "ConneR and the A.R.C. Markland-N"
layout: "post"
diff: 入门
pid: CF1293A
tag: []
---

# ConneR and the A.R.C. Markland-N

## 题目描述

网易云：[削除 - Imprinting](https://music.163.com/#/song?id=30148626)

A.R.C. Markland-N有n层。ConneR（真名Colin Neumann）的办公室在第s层。

现在已知除了其中k层以外，每层上都有一个餐厅。请问ConneR的办公室到最近的餐厅有几层的距离？

## 输入格式

多组数据，第一行一个$t$ ( $1\le t\le1000$ )表示数据组数。

每组数据的第一行包含三个正整数，$n$ ( $2\le n\le 10^9$ )，$s$ ( $1\le s\le n$ )和$k$ ( $1\le k\le min(n-1,1000)$ )，分别表示A.R.C. Markland-N的层数，ConneR在哪一层，没有餐厅的楼层的数量。  
每组数据的第二行包含k个不同的正整数 $a_1,a_2\dots a_k$ ( $1 \le a_i \le n$ )，表示这些层没有餐厅。

## 输出格式

共 $t$ 行，每行一个自然数，表示对于每组输入的答案。

## 样例 #1

### 输入

```
5
5 2 3
1 2 3
4 3 3
4 1 2
10 2 6
1 2 3 4 5 7
2 1 1
2
100 76 8
76 75 36 67 41 74 10 77
```

### 输出

```
2
0
4
0
2
```

