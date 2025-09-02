---
title: "Tyndex.Brome"
layout: "post"
diff: 普及/提高-
pid: CF62B
tag: []
---

# Tyndex.Brome

## 题目描述

每个测试字符串$S$都有一个**独立**的$ans$。

对于测试字符串$S$的每个字母$S_{i}$，可以找到标准字符串$C$中字母$S_{i}$的离$i$的最近位置$j$。将位置的绝对差$\left|i-j \right|$加到$ans$中。也就是说对于每个$i$，取位置$j$，使得 $S_i = C_j$ 且$\left|i-j \right|$最小。

如果标准字符串中不存在字母$C_i$，则将测试字符串$S$的长度添加到$ans$。

## 输入格式

第$1$行包含两个整数$n$和$k$$\left( n,k\leq 10^5 \right)$。$n$是测试字符串的数目，$k$是标准字符串的长度。

第$2$行是长度为$k$且字符均为小写字母的标准字符串。

第$3$至$n+3$行每行输入一个测试字符串。保证所有字符串的总长度不超过$2\times10^5$。

## 输出格式

$n$行，每行输出一个数字代表$ans$。

## 样例 #1

### 输入

```
2 10
codeforces
codeforces
codehorses

```

### 输出

```
0
12

```

## 样例 #2

### 输入

```
9 9
vkontakte
vcontacte
vkontrakte
vkollapse
vkrokodile
vtopke
vkapuste
vpechke
vk
vcodeforcese

```

### 输出

```
18
14
36
47
14
29
30
0
84

```

