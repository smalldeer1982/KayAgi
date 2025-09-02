---
title: "More Cowbell"
layout: "post"
diff: 普及/提高-
pid: CF604B
tag: []
---

# More Cowbell

## 题目描述

Kevin Sun wants to move his precious collection of $ n $ cowbells from Naperthrill to Exeter, where there is actually grass instead of corn. Before moving, he must pack his cowbells into $ k $ boxes of a fixed size. In order to keep his collection safe during transportation, he won't place more than two cowbells into a single box. Since Kevin wishes to minimize expenses, he is curious about the smallest size box he can use to pack his entire collection.

Kevin is a meticulous cowbell collector and knows that the size of his $ i $ -th ( $ 1<=i<=n $ ) cowbell is an integer $ s_{i} $ . In fact, he keeps his cowbells sorted by size, so $ s_{i-1}<=s_{i} $ for any $ i&gt;1 $ . Also an expert packer, Kevin can fit one or two cowbells into a box of size $ s $ if and only if the sum of their sizes does not exceed $ s $ . Given this information, help Kevin determine the smallest $ s $ for which it is possible to put all of his cowbells into $ k $ boxes of size $ s $ .

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=2·k<=100000 $ ), denoting the number of cowbells and the number of boxes, respectively.

The next line contains $ n $ space-separated integers $ s_{1},s_{2},...,s_{n} $ ( $ 1<=s_{1}<=s_{2}<=...<=s_{n}<=1000000 $ ), the sizes of Kevin's cowbells. It is guaranteed that the sizes $ s_{i} $ are given in non-decreasing order.

## 输出格式

Print a single integer, the smallest $ s $ for which it is possible for Kevin to put all of his cowbells into $ k $ boxes of size $ s $ .

## 说明/提示

In the first sample, Kevin must pack his two cowbells into the same box.

In the second sample, Kevin can pack together the following sets of cowbells: $ {2,3} $ , $ {5} $ and $ {9} $ .

In the third sample, the optimal solution is $ {3,5} $ and $ {7} $ .

## 样例 #1

### 输入

```
2 1
2 5

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4 3
2 3 5 9

```

### 输出

```
9

```

## 样例 #3

### 输入

```
3 2
3 5 7

```

### 输出

```
8

```

