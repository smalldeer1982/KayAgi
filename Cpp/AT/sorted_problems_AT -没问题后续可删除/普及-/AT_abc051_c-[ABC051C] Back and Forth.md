---
title: "[ABC051C] Back and Forth"
layout: "post"
diff: 普及-
pid: AT_abc051_c
tag: []
---

# [ABC051C] Back and Forth

## 题目描述

在平面直角坐标系中，有点 $A（sx,sy）$ 和 点 $B（tx,ty）$ 保证 $sx<tx$，$sy<ty$ 并且 $sx,sy,tx,ty$ 都为整数。

在 $A$ 点有一只海豚，它每次可以向上下左右其中一个方向移动一个单位长度。这只海豚想从 $A$ 点到 $B$ 点再回到 $A$ 点再到 $B$ 点再回到 $A$ 点。

要求：除了 $A,B$ 点以外，所有格点都不能走第二遍。海豚不能斜着走。

输出一个字符串 `S` 表示海豚的最短路径，
`S` 中只包括 $U,R,D,L$。
- $U$：向上走一个单位长度。 
- $R$：向右走一个单位长度。 
- $D$：向下走一个单位长度。 
- $L$：向左走一个单位长度。

## 输入格式

一行，$sx,sy,tx,ty$。

## 输出格式

一行，字符串 `S`。

如果有多个最短路径，输出其中任意一个。

Translate by @sqh_let_it_be

## 样例 #1

### 输入

```
0 0 1 2
```

### 输出

```
UURDDLLUUURRDRDDDLLU
```

## 样例 #2

### 输入

```
-2 -2 1 1
```

### 输出

```
UURRURRDDDLLDLLULUUURRURRDDDLLDL
```

