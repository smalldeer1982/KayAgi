---
title: "ADACROP - Ada and Harvest"
layout: "post"
diff: 难度0
pid: SP32745
tag: []
---

# ADACROP - Ada and Harvest

## 题目描述

## 【问题描述】
给定一个长度为 $N$ 的序列 $A_{0_n-1}$，有 $Q$ 次操作，每次将 $A_{pos}$ 的值赋为 $val$ ,再询问序列 $A$ 在 $[0,pos)$ 中有多少数的值等于 $val$。

## 输入格式

第一行包含两个整数 $N$，$Q$，分别表示序列长度和操作次数

接下来一行包含 $N$ 个整数，分别表示 $A_i$ 的值。**（下标从0开始）**。

接下来 $Q$ 行，每行包含2个整数,分别表示 $pos_i$，$val_i$

## 输出格式

对于每次操作,每行输出一个整数 $x_i$ 表示修改后 $A$ 中 $[0,pos_i)$ 值等于 $val_i$ 的个数

## 说明/提示

### 【数据规模与约定】
$1\leq N,Q\leq 2*10^5$。

$1\leq pos_i\leq N$。

$0\leq A_i,val_i\leq 10^9$。

