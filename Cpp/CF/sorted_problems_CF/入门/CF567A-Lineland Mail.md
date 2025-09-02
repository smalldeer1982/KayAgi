---
title: "Lineland Mail"
layout: "post"
diff: 入门
pid: CF567A
tag: []
---

# Lineland Mail

## 题目描述

All cities of Lineland are located on the $ Ox $ coordinate axis. Thus, each city is associated with its position $ x_{i} $ — a coordinate on the $ Ox $ axis. No two cities are located at a single point.

Lineland residents love to send letters to each other. A person may send a letter only if the recipient lives in another city (because if they live in the same city, then it is easier to drop in).

Strange but true, the cost of sending the letter is exactly equal to the distance between the sender's city and the recipient's city.

For each city calculate two values ​​ $ min_{i} $ and $ max_{i} $ , where $ min_{i} $ is the minimum cost of sending a letter from the $ i $ -th city to some other city, and $ max_{i} $ is the the maximum cost of sending a letter from the $ i $ -th city to some other city

## 输入格式

The first line of the input contains integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of cities in Lineland. The second line contains the sequence of $ n $ distinct integers $ x_{1},x_{2},...,x_{n} $ ( $ -10^{9}<=x_{i}<=10^{9} $ ), where $ x_{i} $ is the $ x $ -coordinate of the $ i $ -th city. All the $ x_{i} $ 's are distinct and follow in ascending order.

## 输出格式

Print $ n $ lines, the $ i $ -th line must contain two integers $ min_{i},max_{i} $ , separated by a space, where $ min_{i} $ is the minimum cost of sending a letter from the $ i $ -th city, and $ max_{i} $ is the maximum cost of sending a letter from the $ i $ -th city.

## 样例 #1

### 输入

```
4
-5 -2 2 7

```

### 输出

```
3 12
3 9
4 7
5 12

```

## 样例 #2

### 输入

```
2
-1 1

```

### 输出

```
2 2
2 2

```

