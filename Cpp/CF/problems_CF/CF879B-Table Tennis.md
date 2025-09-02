---
title: "Table Tennis"
layout: "post"
diff: 普及/提高-
pid: CF879B
tag: []
---

# Table Tennis

## 题目描述

 $ n $ people are standing in a line to play table tennis. At first, the first two players in the line play a game. Then the loser goes to the end of the line, and the winner plays with the next person from the line, and so on. They play until someone wins $ k $ games in a row. This player becomes the winner.

For each of the participants, you know the power to play table tennis, and for all players these values are different. In a game the player with greater power always wins. Determine who will be the winner.

## 输入格式

The first line contains two integers: $ n $ and $ k $ ( $ 2<=n<=500 $ , $ 2<=k<=10^{12} $ ) — the number of people and the number of wins.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ) — powers of the player. It's guaranteed that this line contains a valid permutation, i.e. all $ a_{i} $ are distinct.

## 输出格式

Output a single integer — power of the winner.

## 说明/提示

Games in the second sample:

 $ 3 $ plays with $ 1 $ . $ 3 $ wins. $ 1 $ goes to the end of the line.

 $ 3 $ plays with $ 2 $ . $ 3 $ wins. He wins twice in a row. He becomes the winner.

## 样例 #1

### 输入

```
2 2
1 2

```

### 输出

```
2 
```

## 样例 #2

### 输入

```
4 2
3 1 2 4

```

### 输出

```
3 
```

## 样例 #3

### 输入

```
6 2
6 5 3 1 2 4

```

### 输出

```
6 
```

## 样例 #4

### 输入

```
2 10000000000
2 1

```

### 输出

```
2

```

