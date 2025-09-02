---
title: "Bishwock"
layout: "post"
diff: 普及/提高-
pid: CF991D
tag: ['模拟', '贪心']
---

# Bishwock

## 题目描述

Bishwock is a chess figure that consists of three squares resembling an "L-bar". This figure can be rotated by 90, 180 and 270 degrees so it can have four possible states:

```
XX   XX   .X   X.
X.   .X   XX   XX
```

Bishwocks don't attack any squares and can even occupy on the adjacent squares as long as they don't occupy the same square.

Vasya has a board with $ 2\times n $ squares onto which he wants to put some bishwocks. To his dismay, several squares on this board are already occupied by pawns and Vasya can't put bishwocks there. However, pawns also don't attack bishwocks and they can occupy adjacent squares peacefully.

Knowing the positions of pawns on the board, help Vasya to determine the maximum amount of bishwocks he can put onto the board so that they wouldn't occupy the same squares and wouldn't occupy squares with pawns.

## 输入格式

The input contains two nonempty strings that describe Vasya's board. Those strings contain only symbols "0" (zero) that denote the empty squares and symbols "X" (uppercase English letter) that denote the squares occupied by pawns. Strings are nonempty and are of the same length that does not exceed $ 100 $ .

## 输出格式

Output a single integer — the maximum amount of bishwocks that can be placed onto the given board.

## 样例 #1

### 输入

```
00
00

```

### 输出

```
1
```

## 样例 #2

### 输入

```
00X00X0XXX0
0XXX0X00X00

```

### 输出

```
4
```

## 样例 #3

### 输入

```
0X0X0
0X0X0

```

### 输出

```
0
```

## 样例 #4

### 输入

```
0XXX0
00000

```

### 输出

```
2
```

