---
title: "ふたつのアンテナ (Two Antennas)"
layout: "post"
diff: 省选/NOI-
pid: AT_joisc2019_d
tag: ['线段树', '扫描线']
---

# ふたつのアンテナ (Two Antennas)

## 题目描述

有 $n$ 个天线，每个天线用 $a_i,l_i,r_i$ 描述。定义两个天线 $i,j$ 可以联络当且仅当 $|i-j|\in [l_i,r_i]\cap [l_j,r_j]$。

$q$ 次询问一个区间内可以联络的天线 $i,j$ 中 $|a_i-a_j|$ 最大是多少，不存在输出 $-1$。

$1\le n,q\le 2\times 10^5$，$1\le a_i\le 10^9$。

## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行，第 $i$ 行三个正整数 $a_i,l_i,r_i$，描述一个天线。

接下来一行一个正整数 $q$。

接下来 $q$ 行，每行两个正整数 $l,r$，表示询问区间。

## 输出格式

输出 $q$ 行，每行一个整数，表示答案。

by @Kellyfrog

