---
title: "Kleofáš and the n-thlon"
layout: "post"
diff: 省选/NOI-
pid: CF601C
tag: []
---

# Kleofáš and the n-thlon

## 题目描述

Kleofáš is participating in an $ n $ -thlon - a tournament consisting of $ n $ different competitions in $ n $ different disciplines (numbered $ 1 $ through $ n $ ). There are $ m $ participants in the $ n $ -thlon and each of them participates in all competitions.

In each of these $ n $ competitions, the participants are given ranks from $ 1 $ to $ m $ in such a way that no two participants are given the same rank - in other words, the ranks in each competition form a permutation of numbers from $ 1 $ to $ m $ . The score of a participant in a competition is equal to his/her rank in it.

The overall score of each participant is computed as the sum of that participant's scores in all competitions.

The overall rank of each participant is equal to $ 1+k $ , where $ k $ is the number of participants with strictly smaller overall score.

The $ n $ -thlon is over now, but the results haven't been published yet. Kleofáš still remembers his ranks in each particular competition; however, he doesn't remember anything about how well the other participants did. Therefore, Kleofáš would like to know his expected overall rank.

All competitors are equally good at each discipline, so all rankings (permutations of ranks of everyone except Kleofáš) in each competition are equiprobable.

## 输入格式

The first line of the input contains two space-separated integers $ n $ ( $ 1<=n<=100 $ ) and $ m $ ( $ 1<=m<=1000 $ ) — the number of competitions and the number of participants respectively.

Then, $ n $ lines follow. The $ i $ -th of them contains one integer $ x_{i} $ ( $ 1<=x_{i}<=m $ ) — the rank of Kleofáš in the $ i $ -th competition.

## 输出格式

Output a single real number – the expected overall rank of Kleofáš. Your answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-9} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601C/d8d110e69d298146d951837cc2710d1c4cc74a7d.png).

## 说明/提示

In the first sample, Kleofáš has overall score $ 6 $ . Nobody else can have overall score less than $ 6 $ (but it's possible for one other person to have overall score $ 6 $ as well), so his overall rank must be $ 1 $ .

## 样例 #1

### 输入

```
4 10
2
1
2
1

```

### 输出

```
1.0000000000000000

```

## 样例 #2

### 输入

```
5 5
1
2
3
4
5

```

### 输出

```
2.7500000000000000

```

## 样例 #3

### 输入

```
3 6
2
4
2

```

### 输出

```
1.6799999999999999

```

