---
title: "Linguistics"
layout: "post"
diff: 提高+/省选-
pid: CF1685B
tag: ['贪心']
---

# Linguistics

## 题目描述

Alina 发现了一种只由 $\text{A, B, AB, BA}$ 四种单词组成的语言，这种语言不含有空格，书写句子时只需要将单词直接连接起来即可。

她很好奇是否可以用 $a$ 个 $\text{A}$，$b$ 个 $\text{B}$，$c$ 个 $\text{AB}$，$d$ 个 $\text{BA}$ 拼接形成句子 $s$。

换句话说，是否可以用 $a+b+c+d$ 个单词以某种顺序拼接出句子 $s$，这 $a+b+c+d$ 个单词都得被用到，他们的顺序可以由你决定。

## 输入格式

第一行是一个数字 $t$，表示数据的组数。每一组的格式如下：

每组的第一行是四个数字 $a, b, c, d$（$0\leq a,b,c,d\leq2\cdot10^5$），它们分别代表本组单词 $\text{A, B, AB, BA}$ 需要使用的次数。
每组的第二行是一个字符串 $s$（$|s|\leq 2\cdot 10^5$），并且保证 $s$ 的总长和 $a$ 个 $\text{A}$，$b$ 个 $\text{B}$，$c$ 个 $\text{AB}$，$d$ 个 $\text{BA}$ 拼接形成的长度相同（$|s|=a+b+2c+2d$）。其中 $|s|$ 表示字符串 $s$ 的长度。

所有 $s$ 的总长度之和不会超过 $2\cdot 10^5$。

## 输出格式

对于每组数据，如果该组数据的 $s$ 可以被 $a$ 个 $\text{A}$，$b$ 个 $\text{B}$，$c$ 个 $\text{AB}$，$d$ 个 $\text{BA}$ 不限顺序地拼接形成，那么输出一个字符串 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
8
1 0 0 0
B
0 0 1 0
AB
1 1 0 1
ABAB
1 0 1 1
ABAAB
1 1 2 2
BAABBABBAA
1 1 2 3
ABABABBAABAB
2 3 5 4
AABAABBABAAABABBABBBABB
1 3 3 10
BBABABABABBBABABABABABABAABABA
```

### 输出

```
NO
YES
YES
YES
YES
YES
NO
YES
```

