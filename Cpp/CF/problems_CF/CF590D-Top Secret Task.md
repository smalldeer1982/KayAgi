---
title: "Top Secret Task"
layout: "post"
diff: 提高+/省选-
pid: CF590D
tag: []
---

# Top Secret Task

## 题目描述

A top-secret military base under the command of Colonel Zuev is expecting an inspection from the Ministry of Defence. According to the charter, each top-secret military base must include a top-secret troop that should... well, we cannot tell you exactly what it should do, it is a top secret troop at the end. The problem is that Zuev's base is missing this top-secret troop for some reasons.

The colonel decided to deal with the problem immediately and ordered to line up in a single line all $ n $ soldiers of the base entrusted to him. Zuev knows that the loquacity of the $ i $ -th soldier from the left is equal to $ q_{i} $ . Zuev wants to form the top-secret troop using $ k $ leftmost soldiers in the line, thus he wants their total loquacity to be as small as possible (as the troop should remain top-secret). To achieve this, he is going to choose a pair of consecutive soldiers and swap them. He intends to do so no more than $ s $ times. Note that any soldier can be a participant of such swaps for any number of times. The problem turned out to be unusual, and colonel Zuev asked you to help.

Determine, what is the minimum total loquacity of the first $ k $ soldiers in the line, that can be achieved by performing no more than $ s $ swaps of two consecutive soldiers.

## 输入格式

The first line of the input contains three positive integers $ n $ , $ k $ , $ s $ ( $ 1<=k<=n<=150 $ , $ 1<=s<=10^{9} $ ) — the number of soldiers in the line, the size of the top-secret troop to be formed and the maximum possible number of swap operations of the consecutive pair of soldiers, respectively.

The second line of the input contains $ n $ integer $ q_{i} $ ( $ 1<=q_{i}<=1000000 $ ) — the values of loquacity of soldiers in order they follow in line from left to right.

## 输出格式

Print a single integer — the minimum possible total loquacity of the top-secret troop.

## 说明/提示

In the first sample Colonel has to swap second and third soldiers, he doesn't really need the remaining swap. The resulting soldiers order is: ( $ 2 $ , $ 1 $ , $ 4 $ ). Minimum possible summary loquacity of the secret troop is $ 3 $ . In the second sample Colonel will perform swaps in the following order:

1. (10, 1, 6 — 2, 5)
2. (10, 1, 2, 6 — 5)

The resulting soldiers order is (10, 1, 2, 5, 6).

Minimum possible summary loquacity is equal to $ 18 $ .

## 样例 #1

### 输入

```
3 2 2
2 4 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 4 2
10 1 6 2 5

```

### 输出

```
18

```

## 样例 #3

### 输入

```
5 2 3
3 1 4 2 5

```

### 输出

```
3

```

