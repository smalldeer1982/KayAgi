---
title: "GCPC11D - Magic Star"
layout: "post"
diff: 普及+/提高
pid: SP9120
tag: []
---

# GCPC11D - Magic Star

## 题目描述

A magic star consists of all the numbers from _1_ to _12_ arranged in the shape of a hexagram:

![example image](https://cdn.luogu.com.cn/upload/vjudge_pic/SP9120/3d20330b2ff74f8126e5b3ea9c38989226dcbc5a.png)

The magic comes from the fact that in each line of _4_ numbers, the sum of the numbers is _26_. In the example given above, the six lines consist of the following numbers:

- _1 + 4 + 10 + 11_
- _11 + 5 + 3 + 7_
- _7 + 6 + 12 + 1_
- _2 + 10 + 5 + 9_
- _9 + 3 + 6 + 8_
- _8 + 12 + 4 + 2_

There are several possible ways to arrange the numbers to get a magic star. Given a partially labelled star, your task is to extend the solution such that a magic star is formed.

## 输入格式

The input consists of a visualization of the star; the unlabelled fields of the star will be represented by an 'x' character, and labelled fields will contain a letter between 'A' and 'L', where the _i_-th letter in the alphabet represents number _i_. The character '.' is used to align the fields of the star in the shape of a hexagram. You may assume that each input will use the same alignment of the fields as the one in the sample input.

## 输出格式

Print the lexicographically smallest extension of the given partial solution which is a magic star (lexicographically smallest means that the concatenation of the rows should result in a string which is lexicographically smaller than other potential solutions). You may assume that there is always a solution for the given input.

## 样例 #1

### 输入

```
....x....
.A.I.D.x.
..x...x..
.x.x.x.x.
....x....
```

### 输出

```
....F....
.A.I.D.L.
..H...E..
.C.J.B.K.
....G....
```

