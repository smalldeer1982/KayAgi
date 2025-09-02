---
title: "Colorings and Dominoes"
layout: "post"
diff: 普及+/提高
pid: CF1511E
tag: []
---

# Colorings and Dominoes

## 题目描述

You have a large rectangular board which is divided into $ n \times m $ cells (the board has $ n $ rows and $ m $ columns). Each cell is either white or black.

You paint each white cell either red or blue. Obviously, the number of different ways to paint them is $ 2^w $ , where $ w $ is the number of white cells.

After painting the white cells of the board, you want to place the maximum number of dominoes on it, according to the following rules:

- each domino covers two adjacent cells;
- each cell is covered by at most one domino;
- if a domino is placed horizontally (it covers two adjacent cells in one of the rows), it should cover only red cells;
- if a domino is placed vertically (it covers two adjacent cells in one of the columns), it should cover only blue cells.

Let the value of the board be the maximum number of dominoes you can place. Calculate the sum of values of the board over all $ 2^w $ possible ways to paint it. Since it can be huge, print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 3 \cdot 10^5 $ ; $ nm \le 3 \cdot 10^5 $ ) — the number of rows and columns, respectively.

Then $ n $ lines follow, each line contains a string of $ m $ characters. The $ j $ -th character in the $ i $ -th string is \* if the $ j $ -th cell in the $ i $ -th row is black; otherwise, that character is o.

## 输出格式

Print one integer — the sum of values of the board over all $ 2^w $ possible ways to paint it, taken modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
3 4
**oo
oo*o
**oo
```

### 输出

```
144
```

## 样例 #2

### 输入

```
3 4
**oo
oo**
**oo
```

### 输出

```
48
```

## 样例 #3

### 输入

```
2 2
oo
o*
```

### 输出

```
4
```

## 样例 #4

### 输入

```
1 4
oooo
```

### 输出

```
9
```

