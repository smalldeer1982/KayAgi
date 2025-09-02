---
title: "RPLN - Negative Score"
layout: "post"
diff: 难度0
pid: SP11772
tag: []
---

# RPLN - Negative Score

## 题目描述

### 题目翻译

Orianna 是一名出色的游泳运动员，她这个月要去参加游泳比赛，然而她对比赛结果非常担心，所以需要你的帮助。

比赛后每个评委都会打分，这些分数是最终的，意味着在比赛中不会改变。

Orianna 正在接受多个打分，她非常担心自己的结果，所以她想知道从第 $A$ 个分数到第 $B$ 个分数中的最差分数是多少。

## 输入格式

第一行是一个整数 $T$ ，代表 $T$ 组数据，接下来每组数据以 $N$ 和 $Q$ 开头，然后是 $N$ 个整数，表示 Orianna 获得的分数。之后，有 $Q$ 个问题，每个问题由两个整数 $A$ 和 $B$ 组成。

## 输出格式

首先，你要输出字符串 "Scenario #i:" 和一个空行，然后输出每个问题的结果。请注意，Orianna 只对从第 $A$ 个分数到第 $B$ 个分数中的**最差**分数感兴趣。

## 说明/提示

$ 1 \leqslant T \leqslant 100 $

小数据 $30\%$

$ 1 \leqslant N \leqslant 1,000 $

$ 1 \leqslant Q \leqslant 1,000 $

$ -10^9 \leqslant N_{i} \leqslant 10^9 $

$1 \leqslant A \leqslant B \leqslant N$

大数据 $70\%$

$ 1 \leqslant N \leqslant 100,000 $

$ 1 \leqslant Q \leqslant 100,000 $

$ -10^9 \leqslant N_{i} \leqslant 10^9 $

$1 \leqslant A \leqslant B \leqslant N$

## 样例 #1

### 输入

```
2
5 3
1 2 3 4 5
1 5
1 3
2 4
5 3
1 -2 -4 3 -5
1 5
1 3
2 4
```

### 输出

```
Scenario #1:
1
1
2
Scenario #2:
-5
-4
-4
```

