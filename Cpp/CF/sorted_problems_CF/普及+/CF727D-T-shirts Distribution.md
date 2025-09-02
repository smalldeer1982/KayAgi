---
title: "T-shirts Distribution"
layout: "post"
diff: 普及+/提高
pid: CF727D
tag: []
---

# T-shirts Distribution

## 题目描述

The organizers of a programming contest have decided to present t-shirts to participants. There are six different t-shirts sizes in this problem: S, M, L, XL, XXL, XXXL (sizes are listed in increasing order). The t-shirts are already prepared. For each size from S to XXXL you are given the number of t-shirts of this size.

During the registration, the organizers asked each of the $ n $ participants about the t-shirt size he wants. If a participant hesitated between two sizes, he could specify two neighboring sizes — this means that any of these two sizes suits him.

Write a program that will determine whether it is possible to present a t-shirt to each participant of the competition, or not. Of course, each participant should get a t-shirt of proper size:

- the size he wanted, if he specified one size;
- any of the two neibouring sizes, if he specified two sizes.

If it is possible, the program should find any valid distribution of the t-shirts.

## 输入格式

The first line of the input contains six non-negative integers — the number of t-shirts of each size. The numbers are given for the sizes S, M, L, XL, XXL, XXXL, respectively. The total number of t-shirts doesn't exceed $ 100000 $ .

The second line contains positive integer $ n $ ( $ 1<=n<=100000 $ ) — the number of participants.

The following $ n $ lines contain the sizes specified by the participants, one line per participant. The $ i $ -th line contains information provided by the $ i $ -th participant: single size or two sizes separated by comma (without any spaces). If there are two sizes, the sizes are written in increasing order. It is guaranteed that two sizes separated by comma are neighboring.

## 输出格式

If it is not possible to present a t-shirt to each participant, print «NO» (without quotes).

Otherwise, print $ n+1 $ lines. In the first line print «YES» (without quotes). In the following $ n $ lines print the t-shirt sizes the orginizers should give to participants, one per line. The order of the participants should be the same as in the input.

If there are multiple solutions, print any of them.

## 样例 #1

### 输入

```
0 1 0 1 1 0
3
XL
S,M
XL,XXL

```

### 输出

```
YES
XL
M
XXL

```

## 样例 #2

### 输入

```
1 1 2 0 1 1
5
S
M
S,M
XXL,XXXL
XL,XXL

```

### 输出

```
NO

```

