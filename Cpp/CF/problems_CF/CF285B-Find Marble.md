---
title: "Find Marble"
layout: "post"
diff: 普及/提高-
pid: CF285B
tag: []
---

# Find Marble

## 题目描述

Petya and Vasya are playing a game. Petya's got $ n $ non-transparent glasses, standing in a row. The glasses' positions are indexed with integers from $ 1 $ to $ n $ from left to right. Note that the positions are indexed but the glasses are not.

First Petya puts a marble under the glass in position $ s $ . Then he performs some (possibly zero) shuffling operations. One shuffling operation means moving the glass from the first position to position $ p_{1} $ , the glass from the second position to position $ p_{2} $ and so on. That is, a glass goes from position $ i $ to position $ p_{i} $ . Consider all glasses are moving simultaneously during one shuffling operation. When the glasses are shuffled, the marble doesn't travel from one glass to another: it moves together with the glass it was initially been put in.

After all shuffling operations Petya shows Vasya that the ball has moved to position $ t $ . Vasya's task is to say what minimum number of shuffling operations Petya has performed or determine that Petya has made a mistake and the marble could not have got from position $ s $ to position $ t $ .

## 输入格式

The first line contains three integers: $ n,s,t\ (1<=n<=10^{5}; 1<=s,t<=n) $ — the number of glasses, the ball's initial and final position. The second line contains $ n $ space-separated integers: $ p_{1},p_{2},...,p_{n}\ (1<=p_{i}<=n) $ — the shuffling operation parameters. It is guaranteed that all $ p_{i} $ 's are distinct.

Note that $ s $ can equal $ t $ .

## 输出格式

If the marble can move from position $ s $ to position $ t $ , then print on a single line a non-negative integer — the minimum number of shuffling operations, needed to get the marble to position $ t $ . If it is impossible, print number -1.

## 样例 #1

### 输入

```
4 2 1
2 3 4 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 3 3
4 1 3 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4 3 4
1 2 3 4

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
3 1 3
2 1 3

```

### 输出

```
-1

```

