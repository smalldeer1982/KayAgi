---
title: "Casting Spells"
layout: "post"
diff: 省选/NOI-
pid: UVA1470
tag: []
---

# Casting Spells

## 题目描述

给你若干个字符串，你要在这些字符串中分别找出最长的、形如$ww^*ww^*$的子串（$w^*$的意义是将字符串$w$反着写之后得到的字符串）。

比如说，字符串$abrahellehhelleh$中，题意所求的最长的子串就是$hellehhelleh$（其中，$w="hel"$）。

## 输入格式

输入由多组数据组成。第一行是一个正整数$T$，表示数据的组数。

接下来$T$行，每一行都有一个字符串$S$。

## 输出格式

共$T$行，第$i$行表示第$i$个字符串中题意所求的最长的子串的长度。

## 输入输出样例

### 输入样例:
```
2
abrahellehhelleh
rachelhellabracadabra
```

### 输出样例：
```
12
0
```

## 说明/提示

$1 \leqslant T \leqslant 40 $	
$1 \leqslant |S| \leqslant 3 \times 10^5$	
$S$中只包含大小写英文字母。

