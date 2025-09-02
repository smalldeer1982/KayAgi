---
title: "MADHULK - Mad Hulk"
layout: "post"
diff: 难度0
pid: SP12251
tag: []
---

# MADHULK - Mad Hulk

## 题目描述

Evil Doctor D has captured Hulk and put him into an underground tunnel system. The tunnel system is closed but sadly Hulk is not aware of this fact. 

Tunnel structure is of the form of an asterisk. There are many tunnels coming out of single center point. Hulk is left unconscious at the outer end of tunnel. Once Hulk gets up he just wants to get out of this underground system. Since its completely dark down there, Hulk adopts the following strategy : He runs to get to the center and once he gets there he randomly enters another tunnel other than the one he came from. He will run to outer end of this tunnel, come back to center and again choose a random tunnel other than presently exited one (may as well be the first chosen one). 

Note: The starting point of Hulk is at the end of the tunnel whose length is mentioned first in the array

You have to find out the the expected length of Hulk's path in which he would have visited the ends of all tunnels at least once.

## 输入格式

First line contains integer n giving number of test cases. 

n test cases follow. 

For each test case contains k followed k space separated integers representing the lengths of the k tunnels.

## 输出格式

One line per test case containing one number E which is the expected length of Hulk's path.

## 说明/提示

2 <= k <= 50

Each integer a[i] : 1 <= a[i] <= 10^5

## 样例 #1

### 输入

```
2
2 40 40
3 50 50 50
```

### 输出

```
80.0
300.0
```

