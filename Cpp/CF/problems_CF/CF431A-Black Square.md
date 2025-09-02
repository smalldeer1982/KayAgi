---
title: "Black Square"
layout: "post"
diff: 入门
pid: CF431A
tag: []
---

# Black Square

## 题目描述

Quite recently, a very smart student named Jury decided that lectures are boring, so he downloaded a game called "Black Square" on his super cool touchscreen phone.

In this game, the phone's screen is divided into four vertical strips. Each second, a black square appears on some of the strips. According to the rules of the game, Jury must use this second to touch the corresponding strip to make the square go away. As Jury is both smart and lazy, he counted that he wastes exactly $ a_{i} $ calories on touching the $ i $ -th strip.

You've got a string $ s $ , describing the process of the game and numbers $ a_{1},a_{2},a_{3},a_{4} $ . Calculate how many calories Jury needs to destroy all the squares?

## 输入格式

The first line contains four space-separated integers $ a_{1} $ , $ a_{2} $ , $ a_{3} $ , $ a_{4} $ ( $ 0<=a_{1},a_{2},a_{3},a_{4}<=10^{4} $ ).

The second line contains string $ s $ ( $ 1<=|s|<=10^{5} $ ), where the $ і $ -th character of the string equals "1", if on the $ i $ -th second of the game the square appears on the first strip, "2", if it appears on the second strip, "3", if it appears on the third strip, "4", if it appears on the fourth strip.

## 输出格式

Print a single integer — the total number of calories that Jury wastes.

## 样例 #1

### 输入

```
1 2 3 4
123214

```

### 输出

```
13

```

## 样例 #2

### 输入

```
1 5 3 2
11221

```

### 输出

```
13

```

