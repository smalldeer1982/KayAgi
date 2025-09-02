---
title: "Football"
layout: "post"
diff: 入门
pid: CF43A
tag: ['模拟', '字符串']
---

# Football

## 题目描述

One day Vasya decided to have a look at the results of Berland 1910 Football Championship’s finals. Unfortunately he didn't find the overall score of the match; however, he got hold of a profound description of the match's process. On the whole there are $ n $ lines in that description each of which described one goal. Every goal was marked with the name of the team that had scored it. Help Vasya, learn the name of the team that won the finals. It is guaranteed that the match did not end in a tie.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ) — the number of lines in the description. Then follow $ n $ lines — for each goal the names of the teams that scored it. The names are non-empty lines consisting of uppercase Latin letters whose lengths do not exceed 10 symbols. It is guaranteed that the match did not end in a tie and the description contains no more than two different teams.

## 输出格式

Print the name of the winning team. We remind you that in football the team that scores more goals is considered the winner.

## 样例 #1

### 输入

```
1
ABC

```

### 输出

```
ABC

```

## 样例 #2

### 输入

```
5
A
ABA
ABA
A
A

```

### 输出

```
A

```

