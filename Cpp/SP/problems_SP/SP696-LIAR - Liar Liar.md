---
title: "LIAR - Liar Liar"
layout: "post"
diff: 难度0
pid: SP696
tag: []
---

# LIAR - Liar Liar

## 题目描述

Millman 教授讨厌我们，但更糟的是，他认为我们都是骗子。我们并不关心他是否是真心的，但（比他更专业的）我们打算计算班级里最多、最少有多少说谎的人数。（这样下次他批评我们时，我们就有底气了！）

首先，我们对班级上每个人进行了一次调查。每位学生的回答是各位学生是否说谎。这些回答以一个矩阵 $a[i][j]$ 的形式告诉你，其中 $a[i][j]$ 表示第 $i$ 个学生认为第 $j$ 个学生是否为说谎的人。"L" 代表说谎者，"T" 代表说真话的人。

我们对“说谎者”和“说真话的人”的定义如下：

说真话的人 ("T")：这位同学所有的回答都是正确的；

说谎者 ("L")：这位同学的回答有一个或一个以上的错误。

## 输入格式

$T$ - 输入数据组数；

对于每组数据：

$N$ - 全班学生的总数；

$N*N$的矩阵 - 即上文提到的矩阵a。

## 输出格式

对于第 $i$ 组数据，输出一行格式为 "Class Room#i contains atleast A and atmost B liars" 的字符串，其中 $A$ 表示班级里最少有 $A$ 个说谎者，$B$ 表示班级里最多有 $B$ 个说谎者。

如果有某个班级是矛盾的，则输出 "Class Room#i is paradoxical"。

## 说明/提示

$ T \leq 50 $，$ N \leq 70 $

## 样例 #1

### 输入

```
4
2
LL
TT
3
TTT
TTT
TTT
4
TLLL
LTLL
LLTL
LLLT
5
TLTLT
TTTTT
LLTLL
LLLLL
TLTLT
```

### 输出

```
Class Room#1 is paradoxical\n
Class Room#2 contains atleast 0 and atmost 3 liars
Class Room#3 contains atleast 3 and atmost 4 liars
Class Room#4 contains atleast 4 and atmost 4 liars
```

