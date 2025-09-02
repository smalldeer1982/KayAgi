---
title: "Teams Formation"
layout: "post"
diff: 提高+/省选-
pid: CF878B
tag: []
---

# Teams Formation

## 题目描述

This time the Berland Team Olympiad in Informatics is held in a remote city that can only be reached by one small bus. Bus has $ n $ passenger seats, seat $ i $ can be occupied only by a participant from the city $ a_{i} $ .

Today the bus has completed $ m $ trips, each time bringing $ n $ participants. The participants were then aligned in one line in the order they arrived, with people from the same bus standing in the order of their seats (i. e. if we write down the cities where the participants came from, we get the sequence $ a_{1},a_{2},...,a_{n} $ repeated $ m $ times).

After that some teams were formed, each consisting of $ k $ participants form the same city standing next to each other in the line. Once formed, teams left the line. The teams were formed until there were no $ k $ neighboring participants from the same city.

Help the organizers determine how many participants have left in the line after that process ended. We can prove that answer doesn't depend on the order in which teams were selected.

## 输入格式

The first line contains three integers $ n,k $ and $ m $ ( $ 1<=n<=10^{5} $ , $ 2<=k<=10^{9} $ , $ 1<=m<=10^{9} $ ).

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ), where $ a_{i} $ is the number of city, person from which must take seat $ i $ in the bus.

## 输出格式

Output the number of remaining participants in the line.

## 说明/提示

In the second example, the line consists of ten participants from the same city. Nine of them will form a team. At the end, only one participant will stay in the line.

## 样例 #1

### 输入

```
4 2 5
1 2 3 1

```

### 输出

```
12

```

## 样例 #2

### 输入

```
1 9 10
1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 2 10
1 2 1

```

### 输出

```
0

```

