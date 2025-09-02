---
title: "Arthur and Table"
layout: "post"
diff: 普及+/提高
pid: CF557C
tag: []
---

# Arthur and Table

## 题目描述

Arthur has bought a beautiful big table into his new flat. When he came home, Arthur noticed that the new table is unstable.

In total the table Arthur bought has $ n $ legs, the length of the $ i $ -th leg is $ l_{i} $ .

Arthur decided to make the table stable and remove some legs. For each of them Arthur determined number $ d_{i} $ — the amount of energy that he spends to remove the $ i $ -th leg.

A table with $ k $ legs is assumed to be stable if there are more than half legs of the maximum length. For example, to make a table with $ 5 $ legs stable, you need to make sure it has at least three (out of these five) legs of the maximum length. Also, a table with one leg is always stable and a table with two legs is stable if and only if they have the same lengths.

Your task is to help Arthur and count the minimum number of energy units Arthur should spend on making the table stable.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the initial number of legs in the table Arthur bought.

The second line of the input contains a sequence of $ n $ integers $ l_{i} $ ( $ 1<=l_{i}<=10^{5} $ ), where $ l_{i} $ is equal to the length of the $ i $ -th leg of the table.

The third line of the input contains a sequence of $ n $ integers $ d_{i} $ ( $ 1<=d_{i}<=200 $ ), where $ d_{i} $ is the number of energy units that Arthur spends on removing the $ i $ -th leg off the table.

## 输出格式

Print a single integer — the minimum number of energy units that Arthur needs to spend in order to make the table stable.

## 样例 #1

### 输入

```
2
1 5
3 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
2 4 4
1 1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6
2 2 1 1 3 3
4 3 5 5 2 1

```

### 输出

```
8

```

