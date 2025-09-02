---
title: "The Bases Are Loaded"
layout: "post"
diff: 难度0
pid: UVA355
tag: []
---

# The Bases Are Loaded

## 题目描述

Neptune_Disaster得到了一个$x$进制数字，她让Aiming_High把它转换为一个$y$进制数字。

Aiming_High一看：诶这不是大水题吗？于是他十分不屑地把这个数字交给了菜鸡zclg，让他完成这个任务。由于zclg太菜了，所以你需要帮助他。

## 输入格式

输入包含若干组数据。

对于每组数据，会给出$x,y$，即转换前的进制和转换后的进制。接下来给出一个长度不超过$10$的$x$进制数$z$，只含有'0'~'9','A'~'F'。

## 输出格式

对于每组数据，如果给出的$z$在$x$进制下不合法，输出$z $ is an illegal base $x$ number 并换行。

否则输出 $z$ base $x$ = $akahioi$ base $y$，其中$akakioi$为$z$转换为$y$进制后的数。

## 输入输出样例

### 输入样例 \#1

```
2 10 10101
5 3 126
15 11 A4C
```

### 输出样例 \#1
```
10101 base 2 = 21 base 10
126 is an illegal base 5 number
A4C base 15 = 1821 base 11
```

