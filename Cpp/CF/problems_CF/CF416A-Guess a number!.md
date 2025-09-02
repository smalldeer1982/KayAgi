---
title: "Guess a number!"
layout: "post"
diff: 普及-
pid: CF416A
tag: []
---

# Guess a number!

## 题目描述

A TV show called "Guess a number!" is gathering popularity. The whole Berland, the old and the young, are watching the show.

The rules are simple. The host thinks of an integer $ y $ and the participants guess it by asking questions to the host. There are four types of acceptable questions:

- Is it true that $ y $ is strictly larger than number $ x $ ?
- Is it true that $ y $ is strictly smaller than number $ x $ ?
- Is it true that $ y $ is larger than or equal to number $ x $ ?
- Is it true that $ y $ is smaller than or equal to number $ x $ ?

On each question the host answers truthfully, "yes" or "no".

Given the sequence of questions and answers, find any integer value of $ y $ that meets the criteria of all answers. If there isn't such value, print "Impossible".

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=10000 $ ) — the number of questions (and answers). Next $ n $ lines each contain one question and one answer to it. The format of each line is like that: "sign x answer", where the sign is:

- ">" (for the first type queries),
- "<" (for the second type queries),
- ">=" (for the third type queries),
- "<=" (for the fourth type queries).

All values of $ x $ are integer and meet the inequation $ -10^{9}<=x<=10^{9} $ . The answer is an English letter "Y" (for "yes") or "N" (for "no").

Consequtive elements in lines are separated by a single space.

## 输出格式

Print any of such integers $ y $ , that the answers to all the queries are correct. The printed number $ y $ must meet the inequation $ -2·10^{9}<=y<=2·10^{9} $ . If there are many answers, print any of them. If such value doesn't exist, print word "Impossible" (without the quotes).

## 样例 #1

### 输入

```
4
&gt;= 1 Y
&lt; 3 N
&lt;= -3 N
&gt; 55 N

```

### 输出

```
17

```

## 样例 #2

### 输入

```
2
&gt; 100 Y
&lt; -100 Y

```

### 输出

```
Impossible

```

