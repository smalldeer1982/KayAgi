---
title: "Game 23"
layout: "post"
diff: 普及/提高-
pid: CF1141A
tag: []
---

# Game 23

## 题目描述

Polycarp plays "Game 23". Initially he has a number $ n $ and his goal is to transform it to $ m $ . In one move, he can multiply $ n $ by $ 2 $ or multiply $ n $ by $ 3 $ . He can perform any number of moves.

Print the number of moves needed to transform $ n $ to $ m $ . Print -1 if it is impossible to do so.

It is easy to prove that any way to transform $ n $ to $ m $ contains the same number of moves (i.e. number of moves doesn't depend on the way of transformation).

## 输入格式

The only line of the input contains two integers $ n $ and $ m $ ( $ 1 \le n \le m \le 5\cdot10^8 $ ).

## 输出格式

Print the number of moves to transform $ n $ to $ m $ , or -1 if there is no solution.

## 说明/提示

In the first example, the possible sequence of moves is: $ 120 \rightarrow 240 \rightarrow 720 \rightarrow 1440 \rightarrow 4320 \rightarrow 12960 \rightarrow 25920 \rightarrow 51840. $ The are $ 7 $ steps in total.

In the second example, no moves are needed. Thus, the answer is $ 0 $ .

In the third example, it is impossible to transform $ 48 $ to $ 72 $ .

## 样例 #1

### 输入

```
120 51840

```

### 输出

```
7

```

## 样例 #2

### 输入

```
42 42

```

### 输出

```
0

```

## 样例 #3

### 输入

```
48 72

```

### 输出

```
-1

```

