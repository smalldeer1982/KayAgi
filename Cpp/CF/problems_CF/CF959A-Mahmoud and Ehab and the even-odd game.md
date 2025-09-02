---
title: "Mahmoud and Ehab and the even-odd game"
layout: "post"
diff: 普及-
pid: CF959A
tag: []
---

# Mahmoud and Ehab and the even-odd game

## 题目描述

Mahmoud和Ehab正在玩一款叫做“奇偶”的游戏。Ehab选择了一个他最喜欢的整数n然后他们开始玩这个游戏（从Mahmoud开始）在每个人的回合中，他必须选择一个数a，然后从n中减去它。

条件：

     1<=a<=n.
     如果轮到Mahmoud，a必须是偶数。
     但如果轮到Ehab，a必须是奇数。
     
如果当前的玩家不能选择任何满足条件的数字，他就会输。请输出谁获胜了。

## 输入格式

只输入一个n（n1<=n<=10^9),n为游戏开始的数字。

## 输出格式

如果Mahmoud获胜了，就输出"Mahmoud"(没有引号)。
否则输出"Ehab"(没有引号）。

## 说明/提示

在样例1中，Mahmoud不能选择任何一个整数，因为没有一个正偶数小于（等于）1。所以Ehab获胜了。

在样例2中，Mahmoud应当选择a为2。从n中减去2。轮到Ehab的回合了，此时n=0。因为没有小于（等于）0的正奇数，所以Mahmoud获胜了。

## 样例 #1

### 输入

```
1

```

### 输出

```
Ehab
```

## 样例 #2

### 输入

```
2

```

### 输出

```
Mahmoud
```

