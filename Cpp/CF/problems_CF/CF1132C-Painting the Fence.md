---
title: "Painting the Fence"
layout: "post"
diff: 提高+/省选-
pid: CF1132C
tag: []
---

# Painting the Fence

## 题目描述

You have a long fence which consists of $ n $ sections. Unfortunately, it is not painted, so you decided to hire $ q $ painters to paint it. $ i $ -th painter will paint all sections $ x $ such that $ l_i \le x \le r_i $ .

Unfortunately, you are on a tight budget, so you may hire only $ q - 2 $ painters. Obviously, only painters you hire will do their work.

You want to maximize the number of painted sections if you choose $ q - 2 $ painters optimally. A section is considered painted if at least one painter paints it.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 3 \le n, q \le 5000 $ ) — the number of sections and the number of painters availible for hire, respectively.

Then $ q $ lines follow, each describing one of the painters: $ i $ -th line contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ).

## 输出格式

Print one integer — maximum number of painted sections if you hire $ q - 2 $ painters.

## 样例 #1

### 输入

```
7 5
1 4
4 5
5 6
6 7
3 5

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4 3
1 1
2 2
3 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4 4
1 1
2 2
2 3
3 4

```

### 输出

```
3

```

