---
title: "Industrial Nim"
layout: "post"
diff: 普及/提高-
pid: CF15C
tag: []
---

# Industrial Nim

## 题目描述

There are $ n $ stone quarries in Petrograd.

Each quarry owns $ m_{i} $ dumpers ( $ 1<=i<=n $ ). It is known that the first dumper of the $ i $ -th quarry has $ x_{i} $ stones in it, the second dumper has $ x_{i}+1 $ stones in it, the third has $ x_{i}+2 $ , and the $ m_{i} $ -th dumper (the last for the $ i $ -th quarry) has $ x_{i}+m_{i}-1 $ stones in it.

Two oligarchs play a well-known game Nim. Players take turns removing stones from dumpers. On each turn, a player can select any dumper and remove any non-zero amount of stones from it. The player who cannot take a stone loses.

Your task is to find out which oligarch will win, provided that both of them play optimally. The oligarchs asked you not to reveal their names. So, let's call the one who takes the first stone «tolik» and the other one «bolik».

## 输入格式

The first line of the input contains one integer number $ n $ ( $ 1<=n<=10^{5} $ ) — the amount of quarries. Then there follow $ n $ lines, each of them contains two space-separated integers $ x_{i} $ and $ m_{i} $ ( $ 1<=x_{i},m_{i}<=10^{16} $ ) — the amount of stones in the first dumper of the $ i $ -th quarry and the number of dumpers at the $ i $ -th quarry.

## 输出格式

Output «tolik» if the oligarch who takes a stone first wins, and «bolik» otherwise.

## 样例 #1

### 输入

```
2
2 1
3 2

```

### 输出

```
tolik

```

## 样例 #2

### 输入

```
4
1 1
1 1
1 1
1 1

```

### 输出

```
bolik

```

