---
title: "ACM ICPC"
layout: "post"
diff: 普及-
pid: CF886A
tag: ['模拟', '枚举']
---

# ACM ICPC

## 题目描述

In a small but very proud high school it was decided to win ACM ICPC. This goal requires to compose as many teams of three as possible, but since there were only $ 6 $ students who wished to participate, the decision was to build exactly two teams.

After practice competition, participant number $ i $ got a score of $ a_{i} $ . Team score is defined as sum of scores of its participants. High school management is interested if it's possible to build two teams with equal scores. Your task is to answer that question.

## 输入格式

The single line contains six integers $ a_{1},...,a_{6} $ ( $ 0<=a_{i}<=1000 $ ) — scores of the participants

## 输出格式

Print "YES" (quotes for clarity), if it is possible to build teams with equal score, and "NO" otherwise.

You can print each character either upper- or lowercase ("YeS" and "yes" are valid when the answer is "YES").

## 说明/提示

In the first sample, first team can be composed of $ 1 $ st, $ 2 $ nd and $ 6 $ th participant, second — of $ 3 $ rd, $ 4 $ th and $ 5 $ th: team scores are $ 1+3+1=2+1+2=5 $ .

In the second sample, score of participant number $ 6 $ is too high: his team score will be definitely greater.

## 样例 #1

### 输入

```
1 3 2 1 2 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1 1 1 1 1 99

```

### 输出

```
NO

```

