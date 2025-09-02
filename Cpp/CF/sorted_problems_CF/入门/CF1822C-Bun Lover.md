---
title: "Bun Lover"
layout: "post"
diff: 入门
pid: CF1822C
tag: []
---

# Bun Lover

## 题目描述

Tema loves cinnabon rolls — buns with cinnabon and chocolate in the shape of a "snail".

Cinnabon rolls come in different sizes and are square when viewed from above. The most delicious part of a roll is the chocolate, which is poured in a thin layer over the cinnabon roll in the form of a spiral and around the bun, as in the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1822C/ffc1c1654f069b6dc40f3daa75316ce608e668a4.png) Cinnabon rolls of sizes 4, 5, 6

For a cinnabon roll of size $ n $ , the length of the outer side of the square is $ n $ , and the length of the shortest vertical chocolate segment in the central part is one.

Formally, the bun consists of two dough spirals separated by chocolate. A cinnabon roll of size $ n + 1 $ is obtained from a cinnabon roll of size $ n $ by wrapping each of the dough spirals around the cinnabon roll for another layer.

It is important that a cinnabon roll of size $ n $ is defined in a unique way.

Tema is interested in how much chocolate is in his cinnabon roll of size $ n $ . Since Tema has long stopped buying small cinnabon rolls, it is guaranteed that $ n \ge 4 $ .

Answer this non-obvious question by calculating the total length of the chocolate layer.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

The following $ t $ lines describe the test cases.

Each test case is described by a single integer $ n $ ( $ 4 \le n \le 10^9 $ ) — the size of the cinnabon roll.

## 输出格式

Output $ t $ integers. The $ i $ -th of them should be equal to the total length of the chocolate layer in the $ i $ -th test case.

## 样例 #1

### 输入

```
4
4
5
6
179179179
```

### 输出

```
26
37
50
32105178545472401
```

