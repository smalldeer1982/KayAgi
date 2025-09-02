---
title: "Little Elephant and Array"
layout: "post"
diff: 普及+/提高
pid: CF220B
tag: []
---

# Little Elephant and Array

## 题目描述

小象喜欢和数组玩。现在有一个数组  $a$，含有  $n$ 个正整数，记第  $i$ 个数为  $a_i$。

现在有  $m$ 个询问，每个询问包含两个正整数  $l_j$ 和  $r_j \;(1\leqslant l_j\leqslant r_j\leqslant n)$，小象想知道在  $A_{l_j}$ 到  $A_{r_j}$ 之中有多少个数  $x$，其出现次数也为  $x$。

## 输入格式

第一行  $n$ 和  $m$， $n$ 表示数组大小， $m$ 表示询问个数；

第二行共  $n$ 个数，第  $i$ 个数为  $a_i$ 的值；

接下来  $m$ 行，每行两个数  $l_j$ 和  $r_j$，意义如题面。

## 输出格式

共  $m$ 行，每行一个数，表示每一次询问的答案。

## 样例 #1

### 输入

```
7 2
3 1 2 2 3 3 7
1 7
3 4

```

### 输出

```
3
1

```

