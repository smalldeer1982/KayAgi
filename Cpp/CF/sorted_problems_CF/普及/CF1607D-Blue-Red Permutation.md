---
title: "Blue-Red Permutation"
layout: "post"
diff: 普及/提高-
pid: CF1607D
tag: []
---

# Blue-Red Permutation

## 题目描述

有 $n$ 个数，每个数是红色或蓝色。你可以进行无限次操作（也可以 $0$ 次），每次操作你可以：

1. 把一个蓝色的数 $-1$ 。
2. 把一个红色的数 $+1$ 。

问是否能将这 $n$ 个数变成 $1$ 到 $n$ 的排列，是就输出 `YES` ，否则 `NO` 。

## 输入格式

一共 $T$ 组数据，每组数据输入三行。

第一行，一个整数 $n$ ，表示有 $n$ 个数。

第二行，$n$ 个整数，第 $i$ 个数的值为 $a_i$ 。

第三行，一个长为 $n$ 的只包含 `R` 和 `B` （分别表示红色和蓝色）的字符串 $s$ ，第 $i$ 个数的颜色为 $s_i$ 。

## 输出格式

共 $T$ 行，输出 `YES` 或 `NO` 。

## 说明/提示

$1 \le T \le 10^4$ ，$1 \le n \le 2 \times 10^5$ ， $-10^9 \le a_i \le 10^9$ ，$\sum n \le 2 \times 10^5$ 。

## 样例 #1

### 输入

```
8
4
1 2 5 2
BRBR
2
1 1
BB
5
3 1 4 2 5
RBRRB
5
3 1 3 1 3
RBRRB
5
5 1 5 1 5
RBRRB
4
2 2 2 2
BRBR
2
1 -2
BR
4
-2 -1 4 0
RRRR
```

### 输出

```
YES
NO
YES
YES
NO
YES
YES
YES
```

