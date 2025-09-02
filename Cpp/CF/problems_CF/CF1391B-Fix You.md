---
title: "Fix You"
layout: "post"
diff: 普及-
pid: CF1391B
tag: []
---

# Fix You

## 题目描述

给你一个 $n \times m$ 的矩阵，每一格上有个一标记不是 $R$ 就是 $D$，如果为 $R$ 表示这一格的物品会被送到这一格紧邻的右边的那一格，如果为 $D$ 表示这一格的物品会被送到这一格紧邻的下边的那一格。问你最少修改（$R$ 变 $D$ 或者 $D$ 变 $R$）多少次使得不管哪一个里的物品最后都能到达 $(n,m)$。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)

## 输入格式

多组测试。

第一行一个 $t \ (1 \leq t \leq 10)$，表示数据组数。

每一组数据第一行为 $n,m \ (1 \leq n,m \leq 100)$ 表示矩阵有 $n$ 行 $m$ 列。

接下来有 $n$ 行每行 $m$ 个字符为 $R$ 或 $D$（无空格分隔）。

## 输出格式

对于每组数据输出一行表示最少修改多少次。

## 样例 #1

### 输入

```
4
3 3
RRD
DDR
RRC
1 4
DDDC
6 9
RDDDDDRRR
RRDDRRDDD
RRDRDRRDR
DDDDRDDRR
DRRDRDDDR
DDRDRRDDC
1 1
C
```

### 输出

```
1
3
9
0
```

