---
title: "BIRD - Bird or not bird"
layout: "post"
diff: 难度0
pid: SP5463
tag: []
---

# BIRD - Bird or not bird

## 题目描述

你在森林中研究动物，并希望知道哪些动物是鸟。  
对于一只动物你会测量他的身高（height）和体重（weight）。  
有两个区间 $[h_l,h_r]$ 和 $[w_l,w_r]$。若一只动物的 height 在 $[h_l,h_r]$ 内且 weight 在 $[w_l,w_r]$ 内，那么这只动物一定是鸟，并且鸟的 height 一定在 $[h_l,h_r]$ 内，weight 一定在 $[w_l,w_r]$ 中，但是你并不知道这两个区间的具体数值。

现在你测量了 $n$ 只动物的 height 和 weight，并且知道它们是不是鸟。再给你 $m$ 只动物的 height 和 weight，请你回答它们是不是鸟，或者回答你不能确定它们是不是鸟。

接下来有 $n$ 行，第 $i$ 行有两个整数 $h_i,w_i$ 和一个字符串 $S_i$。$h_i,w_i$ 分别表示第 $i$ 只动物的 height 和 weight。$S_i$ 为 `BIRD` 或 `NOT BIRD`，表示第 $i$ 只动物是或不是鸟。  
接下来 $m$ 行，第 $j$ 行有两个整数 $qh_j,qw_j$，分别表示询问中第 $j$ 只动物的 height 和 weight。

## 输入格式

**本题有多组数据。**  
第一行输入一个数 $C$ 表示数据组数。

## 输出格式

对于第 $k$ 组数据，先输出一行 `Case #k:`。  
每条询问一行。
对于询问的第 $j$ 只鸟：若可以确定它是鸟，则输出 `BIRD`；若可以确定它不是鸟，则输出 `NOT BIRD`；若不能确定它是不是鸟，则输出 `UNKNOWN`。

## 说明/提示

对于 $100\%$ 的数据：  
$1 \le C \le 20$。  
$1 \le n,m \le 1 \times 10^3$。  
$1 \le h_i,w_i,qh_j,qw_j \le 1 \times 10^6$。其中 $1 \le i \le n,1 \le j \le m$。

## 样例 #1

### 输入

```
3
5
1000 1000 BIRD
2000 1000 BIRD
2000 2000 BIRD
1000 2000 BIRD
1500 2010 NOT BIRD
3
1500 1500
900 900
1400 2020
3
500 700 NOT BIRD
501 700 BIRD
502 700 NOT BIRD
2
501 600
502 501
1
100 100 NOT BIRD
3
107 93
86 70
110 115

```

### 输出

```
Case #1:
BIRD
UNKNOWN
NOT BIRD
Case #2:
UNKNOWN
NOT BIRD
Case #3:
UNKNOWN
UNKNOWN
UNKNOWN

```

