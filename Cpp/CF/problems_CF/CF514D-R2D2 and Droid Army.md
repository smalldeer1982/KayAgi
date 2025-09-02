---
title: "R2D2 and Droid Army"
layout: "post"
diff: 普及+/提高
pid: CF514D
tag: []
---

# R2D2 and Droid Army

## 题目描述

An army of $ n $ droids is lined up in one row. Each droid is described by $ m $ integers $ a_{1},a_{2},...,a_{m} $ , where $ a_{i} $ is the number of details of the $ i $ -th type in this droid's mechanism. R2-D2 wants to destroy the sequence of consecutive droids of maximum length. He has $ m $ weapons, the $ i $ -th weapon can affect all the droids in the army by destroying one detail of the $ i $ -th type (if the droid doesn't have details of this type, nothing happens to it).

A droid is considered to be destroyed when all of its details are destroyed. R2-D2 can make at most $ k $ shots. How many shots from the weapon of what type should R2-D2 make to destroy the sequence of consecutive droids of maximum length?

## 输入格式

The first line contains three integers $ n,m,k $ ( $ 1<=n<=10^{5} $ , $ 1<=m<=5 $ , $ 0<=k<=10^{9} $ ) — the number of droids, the number of detail types and the number of available shots, respectively.

Next $ n $ lines follow describing the droids. Each line contains $ m $ integers $ a_{1},a_{2},...,a_{m} $ ( $ 0<=a_{i}<=10^{8} $ ), where $ a_{i} $ is the number of details of the $ i $ -th type for the respective robot.

## 输出格式

Print $ m $ space-separated integers, where the $ i $ -th number is the number of shots from the weapon of the $ i $ -th type that the robot should make to destroy the subsequence of consecutive droids of the maximum length.

If there are multiple optimal solutions, print any of them.

It is not necessary to make exactly $ k $ shots, the number of shots can be less.

## 说明/提示

In the first test the second, third and fourth droids will be destroyed.

In the second test the first and second droids will be destroyed.

## 样例 #1

### 输入

```
5 2 4
4 0
1 2
2 1
0 2
1 3

```

### 输出

```
2 2

```

## 样例 #2

### 输入

```
3 2 4
1 2
1 3
2 2

```

### 输出

```
1 3

```

