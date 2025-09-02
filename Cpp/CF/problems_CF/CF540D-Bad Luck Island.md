---
title: "Bad Luck Island"
layout: "post"
diff: 普及+/提高
pid: CF540D
tag: []
---

# Bad Luck Island

## 题目描述

The Bad Luck Island is inhabited by three kinds of species: $ r $ rocks, $ s $ scissors and $ p $ papers. At some moments of time two random individuals meet (all pairs of individuals can meet equiprobably), and if they belong to different species, then one individual kills the other one: a rock kills scissors, scissors kill paper, and paper kills a rock. Your task is to determine for each species what is the probability that this species will be the only one to inhabit this island after a long enough period of time.

## 输入格式

The single line contains three integers $ r $ , $ s $ and $ p $ ( $ 1<=r,s,p<=100 $ ) — the original number of individuals in the species of rock, scissors and paper, respectively.

## 输出格式

Print three space-separated real numbers: the probabilities, at which the rocks, the scissors and the paper will be the only surviving species, respectively. The answer will be considered correct if the relative or absolute error of each number doesn't exceed $ 10^{-9} $ .

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
0.333333333333 0.333333333333 0.333333333333

```

## 样例 #2

### 输入

```
2 1 2

```

### 输出

```
0.150000000000 0.300000000000 0.550000000000

```

## 样例 #3

### 输入

```
1 1 3

```

### 输出

```
0.057142857143 0.657142857143 0.285714285714

```

