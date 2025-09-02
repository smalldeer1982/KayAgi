---
title: "Fox and Number Game"
layout: "post"
diff: 入门
pid: CF389A
tag: []
---

# Fox and Number Game

## 题目描述

Fox Ciel is playing a game with numbers now.

Ciel has $ n $ positive integers: $ x_{1} $ , $ x_{2} $ , ..., $ x_{n} $ . She can do the following operation as many times as needed: select two different indexes $ i $ and $ j $ such that $ x_{i} $ > $ x_{j} $ hold, and then apply assignment $ x_{i} $ = $ x_{i} $ - $ x_{j} $ . The goal is to make the sum of all numbers as small as possible.

Please help Ciel to find this minimal sum.

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=100 $ ). Then the second line contains $ n $ integers: $ x_{1} $ , $ x_{2} $ , ..., $ x_{n} $ ( $ 1<=x_{i}<=100 $ ).

## 输出格式

Output a single integer — the required minimal sum.

## 说明/提示

In the first example the optimal way is to do the assignment: $ x_{2} $ = $ x_{2} $ - $ x_{1} $ .

In the second example the optimal sequence of operations is: $ x_{3} $ = $ x_{3} $ - $ x_{2} $ , $ x_{2} $ = $ x_{2} $ - $ x_{1} $ .

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
2 4 6

```

### 输出

```
6

```

## 样例 #3

### 输入

```
2
12 18

```

### 输出

```
12

```

## 样例 #4

### 输入

```
5
45 12 27 30 18

```

### 输出

```
15

```

