---
title: "Presents in Bankopolis"
layout: "post"
diff: 普及+/提高
pid: CF793D
tag: []
---

# Presents in Bankopolis

## 题目描述

Bankopolis is an incredible city in which all the $ n $ crossroads are located on a straight line and numbered from $ 1 $ to $ n $ along it. On each crossroad there is a bank office.

The crossroads are connected with $ m $ oriented bicycle lanes (the $ i $ -th lane goes from crossroad $ u_{i} $ to crossroad $ v_{i} $ ), the difficulty of each of the lanes is known.

Oleg the bank client wants to gift happiness and joy to the bank employees. He wants to visit exactly $ k $ offices, in each of them he wants to gift presents to the employees.

The problem is that Oleg don't want to see the reaction on his gifts, so he can't use a bicycle lane which passes near the office in which he has already presented his gifts (formally, the $ i $ -th lane passes near the office on the $ x $ -th crossroad if and only if $ min(u_{i},v_{i})&lt;x&lt;max(u_{i},v_{i}))) $ . Of course, in each of the offices Oleg can present gifts exactly once. Oleg is going to use exactly $ k-1 $ bicycle lane to move between offices. Oleg can start his path from any office and finish it in any office.

Oleg wants to choose such a path among possible ones that the total difficulty of the lanes he will use is minimum possible. Find this minimum possible total difficulty.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n,k<=80 $ ) — the number of crossroads (and offices) and the number of offices Oleg wants to visit.

The second line contains single integer $ m $ ( $ 0<=m<=2000 $ ) — the number of bicycle lanes in Bankopolis.

The next $ m $ lines contain information about the lanes.

The $ i $ -th of these lines contains three integers $ u_{i} $ , $ v_{i} $ and $ c_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ 1<=c_{i}<=1000 $ ), denoting the crossroads connected by the $ i $ -th road and its difficulty.

## 输出格式

In the only line print the minimum possible total difficulty of the lanes in a valid path, or -1 if there are no valid paths.

## 说明/提示

In the first example Oleg visiting banks by path $ 1→6→2→4 $ .

Path $ 1→6→2→7 $ with smaller difficulity is incorrect because crossroad $ 2→7 $ passes near already visited office on the crossroad $ 6 $ .

In the second example Oleg can visit banks by path $ 4→1→3 $ .

## 样例 #1

### 输入

```
7 4
4
1 6 2
6 2 2
2 4 2
2 7 1

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 3
4
2 1 2
1 3 2
3 4 2
4 1 1

```

### 输出

```
3

```

