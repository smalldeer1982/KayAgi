---
title: "George and Cards"
layout: "post"
diff: 提高+/省选-
pid: CF387E
tag: ['贪心', '线段树', '二分']
---

# George and Cards

## 题目描述

George is a cat, so he loves playing very much.

Vitaly put $ n $ cards in a row in front of George. Each card has one integer written on it. All cards had distinct numbers written on them. Let's number the cards from the left to the right with integers from $ 1 $ to $ n $ . Then the $ i $ -th card from the left contains number $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Vitaly wants the row to have exactly $ k $ cards left. He also wants the $ i $ -th card from left to have number $ b_{i} $ written on it. Vitaly gave a task to George, to get the required sequence of cards using the remove operation $ n-k $ times.

In one remove operation George can choose $ w $ ( $ 1<=w $ ; $ w $ is not greater than the current number of cards in the row) contiguous cards (contiguous subsegment of cards). Let's denote the numbers written on these card as $ x_{1},x_{2},...,x_{w} $ (from the left to the right). After that, George can remove the card $ x_{i} $ , such that $ x_{i}<=x_{j} $ for each $ j $ $ (1<=j<=w) $ . After the described operation George gets $ w $ pieces of sausage.

George wondered: what maximum number of pieces of sausage will he get in total if he reaches his goal and acts optimally well? Help George, find an answer to his question!

## 输入格式

The first line contains integers $ n $ and $ k $ ( $ 1<=k<=n<=10^{6} $ ) — the initial and the final number of cards.

The second line contains $ n $ distinct space-separated integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the initial row of cards.

The third line contains $ k $ space-separated integers $ b_{1},b_{2},...,b_{k} $ — the row of cards that you need to get. It is guaranteed that it's possible to obtain the given row by using the remove operation for $ n-k $ times.

## 输出格式

Print a single integer — the maximum number of pieces of sausage that George can get if he acts optimally well.

## 样例 #1

### 输入

```
3 2
2 1 3
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10

```

### 输出

```
30

```

