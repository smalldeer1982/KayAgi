---
title: "Dima and Bacteria"
layout: "post"
diff: 普及+/提高
pid: CF400D
tag: []
---

# Dima and Bacteria

## 题目描述

Dima took up the biology of bacteria, as a result of his experiments, he invented $ k $ types of bacteria. Overall, there are $ n $ bacteria at his laboratory right now, and the number of bacteria of type $ i $ equals $ c_{i} $ . For convenience, we will assume that all the bacteria are numbered from $ 1 $ to $ n $ . The bacteria of type $ c_{i} $ are numbered from ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400D/982a571b1865821e9e229719b32d90deaece954a.png) to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400D/cadef4f1e0deb44673d0bf224d83a90828e59d96.png).

With the help of special equipment Dima can move energy from some bacteria into some other one. Of course, the use of such equipment is not free. Dima knows $ m $ ways to move energy from some bacteria to another one. The way with number $ i $ can be described with integers $ u_{i} $ , $ v_{i} $ and $ x_{i} $ mean that this way allows moving energy from bacteria with number $ u_{i} $ to bacteria with number $ v_{i} $ or vice versa for $ x_{i} $ dollars.

Dima's Chef (Inna) calls the type-distribution correct if there is a way (may be non-direct) to move energy from any bacteria of the particular type to any other bacteria of the same type (between any two bacteria of the same type) for zero cost.

As for correct type-distribution the cost of moving the energy depends only on the types of bacteria help Inna to determine is the type-distribution correct? If it is, print the matrix $ d $ with size $ k×k $ . Cell $ d[i][j] $ of this matrix must be equal to the minimal possible cost of energy-moving from bacteria with type $ i $ to bacteria with type $ j $ .

## 输入格式

The first line contains three integers $ n,m,k $ $ (1<=n<=10^{5}; 0<=m<=10^{5}; 1<=k<=500) $ . The next line contains $ k $ integers $ c_{1},c_{2},...,c_{k} $ $ (1<=c_{i}<=n) $ . Each of the next $ m $ lines contains three integers $ u_{i},v_{i},x_{i} $ $ (1<=u_{i},v_{i}<=10^{5}; 0<=x_{i}<=10^{4}) $ . It is guaranteed that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400D/31b6f8aa1e4750c940bc1c186a5143544e1a885a.png).

## 输出格式

If Dima's type-distribution is correct, print string «Yes», and then $ k $ lines: in the $ i $ -th line print integers $ d[i][1],d[i][2],...,d[i][k] $ $ (d[i][i]=0) $ . If there is no way to move energy from bacteria $ i $ to bacteria $ j $ appropriate $ d[i][j] $ must equal to -1. If the type-distribution isn't correct print «No».

## 样例 #1

### 输入

```
4 4 2
1 3
2 3 0
3 4 0
2 4 1
2 1 2

```

### 输出

```
Yes
0 2
2 0

```

## 样例 #2

### 输入

```
3 1 2
2 1
1 2 0

```

### 输出

```
Yes
0 -1
-1 0

```

## 样例 #3

### 输入

```
3 2 2
2 1
1 2 0
2 3 1

```

### 输出

```
Yes
0 1
1 0

```

## 样例 #4

### 输入

```
3 0 2
1 2

```

### 输出

```
No

```

