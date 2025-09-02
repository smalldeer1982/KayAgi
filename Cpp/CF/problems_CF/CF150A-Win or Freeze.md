---
title: "Win or Freeze"
layout: "post"
diff: 普及/提高-
pid: CF150A
tag: []
---

# Win or Freeze

## 题目描述

You can't possibly imagine how cold our friends are this winter in Nvodsk! Two of them play the following game to warm up: initially a piece of paper has an integer $ q $ . During a move a player should write any integer number that is a non-trivial divisor of the last written number. Then he should run this number of circles around the hotel. Let us remind you that a number's divisor is called non-trivial if it is different from one and from the divided number itself.

The first person who can't make a move wins as he continues to lie in his warm bed under three blankets while the other one keeps running. Determine which player wins considering that both players play optimally. If the first player wins, print any winning first move.

## 输入格式

The first line contains the only integer $ q $ ( $ 1<=q<=10^{13} $ ).

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 输出格式

In the first line print the number of the winning player ( $ 1 $ or $ 2 $ ). If the first player wins then the second line should contain another integer — his first move (if the first player can't even make the first move, print $ 0 $ ). If there are multiple solutions, print any of them.

## 说明/提示

Number $ 6 $ has only two non-trivial divisors: $ 2 $ and $ 3 $ . It is impossible to make a move after the numbers $ 2 $ and $ 3 $ are written, so both of them are winning, thus, number $ 6 $ is the losing number. A player can make a move and write number $ 6 $ after number $ 30 $ ; $ 6 $ , as we know, is a losing number. Thus, this move will bring us the victory.

## 样例 #1

### 输入

```
6

```

### 输出

```
2

```

## 样例 #2

### 输入

```
30

```

### 输出

```
1
6

```

## 样例 #3

### 输入

```
1

```

### 输出

```
1
0

```

