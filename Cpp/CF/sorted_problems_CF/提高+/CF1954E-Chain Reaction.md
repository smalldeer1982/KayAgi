---
title: "Chain Reaction"
layout: "post"
diff: 提高+/省选-
pid: CF1954E
tag: ['贪心']
---

# Chain Reaction

## 题目描述

There are $ n $ monsters standing in a row. The $ i $ -th monster has $ a_i $ health points.

Every second, you can choose one alive monster and launch a chain lightning at it. The lightning deals $ k $ damage to it, and also spreads to the left (towards decreasing $ i $ ) and to the right (towards increasing $ i $ ) to alive monsters, dealing $ k $ damage to each. When the lightning reaches a dead monster or the beginning/end of the row, it stops. A monster is considered alive if its health points are strictly greater than $ 0 $ .

For example, consider the following scenario: there are three monsters with health equal to $ [5, 2, 7] $ , and $ k = 3 $ . You can kill them all in $ 4 $ seconds:

- launch a chain lightning at the $ 3 $ -rd monster, then their health values are $ [2, -1, 4] $ ;
- launch a chain lightning at the $ 1 $ -st monster, then their health values are $ [-1, -1, 4] $ ;
- launch a chain lightning at the $ 3 $ -rd monster, then their health values are $ [-1, -1, 1] $ ;
- launch a chain lightning at the $ 3 $ -th monster, then their health values are $ [-1, -1, -2] $ .

For each $ k $ from $ 1 $ to $ \max(a_1, a_2, \dots, a_n) $ , calculate the minimum number of seconds it takes to kill all the monsters.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of monsters.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the health points of the $ i $ -th monster.

## 输出格式

For each $ k $ from $ 1 $ to $ \max(a_1, a_2, \dots, a_n) $ , output the minimum number of seconds it takes to kill all the monsters.

## 样例 #1

### 输入

```
3
5 2 7
```

### 输出

```
10 6 4 3 2 2 1
```

## 样例 #2

### 输入

```
4
7 7 7 7
```

### 输出

```
7 4 3 2 2 2 1
```

## 样例 #3

### 输入

```
10
1 9 7 6 2 4 7 8 1 3
```

### 输出

```
17 9 5 4 3 3 3 2 1
```

