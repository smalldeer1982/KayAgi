---
title: "电子人的基因 Cyborg Genes"
layout: "post"
diff: 提高+/省选-
pid: UVA10723
tag: []
---

# 电子人的基因 Cyborg Genes

## 题目描述

输入两个$A$~$Z$组成的字符串（长度均不超过$30$），找一个最短的串，使得输入的两个串均是它的子序列（不一定连续出现）。你的程序还应统计长度最短的串的个数。

$e.g.:ABAAXGF$和$AABXFGA$的最优解之一为$AABAAXGFGA$,一共有$9$个解。

## 输入格式

有多组数据。第一行一个整数$T$表示数据组数。接下来的$2T$行，每行一个字符串，含义如题所示。

## 输出格式

共$T$行。第$i$行格式为

``Case #i: x y``

其中$x$为最短串的长度，$y$为最优解的个数。

## 样例 #1

### 输入

```
3
ABAAXGF
AABXFGA
ABA
BXA
AABBA
BBABAA
```

### 输出

```
Case #1: 10 9
Case #2: 4 1
Case #3: 8 10
```

