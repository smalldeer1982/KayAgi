---
title: "Castle Defense"
layout: "post"
diff: 普及+/提高
pid: CF954G
tag: []
---

# Castle Defense

## 题目描述

Today you are going to lead a group of elven archers to defend the castle that is attacked by an army of angry orcs. Three sides of the castle are protected by impassable mountains and the remaining side is occupied by a long wall that is split into $ n $ sections. At this moment there are exactly $ a_{i} $ archers located at the $ i $ -th section of this wall. You know that archer who stands at section $ i $ can shoot orcs that attack section located at distance not exceeding $ r $ , that is all such sections $ j $ that $ |i-j|<=r $ . In particular, $ r=0 $ means that archers are only capable of shooting at orcs who attack section $ i $ .

Denote as defense level of section $ i $ the total number of archers who can shoot at the orcs attacking this section. Reliability of the defense plan is the minimum value of defense level of individual wall section.

There is a little time left till the attack so you can't redistribute archers that are already located at the wall. However, there is a reserve of $ k $ archers that you can distribute among wall sections in arbitrary way. You would like to achieve maximum possible reliability of the defence plan.

## 输入格式

The first line of the input contains three integers $ n $ , $ r $ and $ k $ ( $ 1<=n<=500000 $ , $ 0<=r<=n $ , $ 0<=k<=10^{18} $ ) — the number of sections of the wall, the maximum distance to other section archers can still shoot and the number of archers yet to be distributed along the wall. The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ) — the current number of archers at each section.

## 输出格式

Print one integer — the maximum possible value of defense plan reliability, i.e. the maximum possible value of minimum defense level if we distribute $ k $ additional archers optimally.

## 样例 #1

### 输入

```
5 0 6
5 4 3 4 9

```

### 输出

```
5

```

## 样例 #2

### 输入

```
4 2 0
1 2 3 4

```

### 输出

```
6

```

## 样例 #3

### 输入

```
5 1 1
2 1 2 1 2

```

### 输出

```
3

```

