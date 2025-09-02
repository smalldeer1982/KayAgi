---
title: "CODE1 - Secret Code"
layout: "post"
diff: 难度0
pid: SP36
tag: []
---

# CODE1 - Secret Code

## 题目描述

很久以前有一个叫做 Sarcophagus 的东西，它被一个神秘数字编码锁住了。你若想要打开它就必须把他输入在它的顶部，如果你输入错误了，整个 Sarcophagus 都会被烧毁。由 $100$ 个整数组成的密码储藏在 Alexandrian 图书馆，但不幸的是，这个图书馆已经完全被烧毁了。

但是有一名神秘的考古学家在 $18$ 世纪获得了密码的复印版本， 他怕有坏人去打开 Sarcophagus，便以一种复杂的数字将其加密，他获取了一个绝对值比所有密码数字都大的 $B$。然后将密码 $a_n,a_{n-1},a_{n-2}\dots a_1,a_0$ 编译为了数字$X$，$X$ 由以下规则算出：

$$X = a_0+a_1B+a_2B^2+\dots+a_nB^n$$

你的目的是通过已给的 $X,B$ 算出 $a_n,a_{n-1},a_{n-2}\dots a_1,a_0$。

## 输入格式

第一行包含 $T$ 个测试数据。

接下来的 $T$ 行每行包含 $4$ 个整数$X_r,X_i,B_r,B_i$

这些数字表明 $X,B$ 的数值：

$\begin{cases}X = X_r+i\times X_i\\B = B_r+i \times B_i\end{cases}$

其中 $|B|>1$。

## 输出格式

每个输入的测试样例对应一行输出，包含 $a_n,a_{n-1},a_{n-2}\dots a_1,a_0$。

这些输出数据应该满足：



如果输入的样例不成立的话，输出`The code cannot be decrypted.`。如果有更多可能则全部输出并用逗号分隔。

## 输入输出样例 
### 输入
```
4
-935 2475 -11 -15
1 0 -3 -2
93 16 3 2
191 -192 11 -12

```
### 输出
```
8,11,18
1
The code cannot be decrypted.
16,15
```

$0\le a_i<B$ 且 $0<=i<=n$，$i\in \mathbb{Z}$

$X = a_0+a_1B+a_2B^2+\dots+a_nB^n$

如果$n>0$，则$a_n\neq 0$

$n\le 100$，$T\le 10^5$

$|Xr|,|Xi|\le 10^6$，$|Br|,|Bi|\le 16$

## 样例 #1

### 输入

```
4
-935 2475 -11 -15
1 0 -3 -2
93 16 3 2
191 -192 11 -12
```

### 输出

```
8,11,18
1
The code cannot be decrypted.
16,15
```

