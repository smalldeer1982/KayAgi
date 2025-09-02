---
title: "Alyona and a Square Jigsaw Puzzle"
layout: "post"
diff: 普及-
pid: CF2047A
tag: ['数学']
---

# Alyona and a Square Jigsaw Puzzle

## 题目描述

Alyona 组装了一个特殊的方形拼图。在 $n$ 天中，她的组装规则如下：

- 在第一天，她将中心拼图放在桌子的中心点。
- 在接下来的每一天，她在中心的周围顺时针摆一定数量的拼图，一层拼图全部摆满后才会开始摆新的一层。

下图展示了她前 $14$ 块拼图的摆放方法：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2047A/79d4bc6fb70315d8b0bc2f84e7e9b7aaaaa1456d.png)

不同颜色表示不同的层，第三层还未摆满。如果在某一天，Alyona 没有任何未摆满的拼图层，她就会很开心。给出 Alyona 每天摆放拼图的块数，求 Alyona 开心的天数。

## 输入格式

本题有多组数据。第一行，一个整数 $t$ ($1\le t\le 500$)，表示数据组数。

对于每组数据：

第一行，一个整数 $n$ ($1\le n\le 100$)，表示拼图的天数。

第二行，$n$ 个整数 $a_1,a_2,\cdots,a_n$ ($1\le a_i\le 100, a_1=1$)，表示 Alyona 第 $i$ 天拼的拼图块个数。

保证在每组数据中，最后一天结束后没有未摆满的层。

## 输出格式

对于每组数据，输出一行一个整数，表示 Alyona 开心的天数。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
5
1
1
2
1 8
5
1 3 2 1 2
7
1 2 1 10 2 7 2
14
1 10 10 100 1 1 10 1 10 2 10 2 10 1
```

### 输出

```
1
2
2
2
3
```

