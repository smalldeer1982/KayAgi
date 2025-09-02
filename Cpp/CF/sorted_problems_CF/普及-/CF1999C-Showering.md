---
title: "Showering"
layout: "post"
diff: 普及-
pid: CF1999C
tag: ['模拟']
---

# Showering

## 题目描述

作为一名中学生，jmsyang0808需要每天洗澡，但悲剧的是，因为Ta还要登~~臭名昭著的~~洛谷，AK CF赛，面基等等做一些琐碎的事导致Ta没有空。因为Ta太忙了，所以Ta请你写个程序来解决这个问题。

Ta有 $m$ 单位的时间，而Ta需要用 $s$ 单位的时间来洗澡。Ta有 $n$ 件事要做，第 $i$ 件事的开始与结束时间分别为 $l_i$ 和 $r_i$ ，期间Ta无法洗澡。没有两项任务重叠。

现在jmsyang0808问你，Ta有时间洗澡吗？如果能，输出 `YES` ，否则只能输出 `NO` 了QAQ~。

## 输入格式

_本题包含多组测试数据。_ 

第一行包含一个整数 $T(1\leq T\leq 10^4)$ 表示测试用例的数量。

每个测试用例的第一行包含三个整数 $n,s,m(1\leq n\leq 2\cdot 10^5,1\leq s,m\leq 10^9)$ 。

然后是 $n$ 行，其中第 $i$ 行包含两个整数 $l_i$ 和 $r_i$ $(0\leq l_i<r_i\leq m)$ 。

保证对于所有 $i>1$ ， $l_i>r_{i-1}$ 。

## 输出格式

对于每个输入用例，输出一行 `YES` 或 `NO` 。

## 说明/提示

下面是对于用例一的解释。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1999C/f37c16ccee56dc0e812638d809cb1411cb80cf1b.png)

Translated By @jmsyang0808.

## 样例 #1

### 输入

```
4
3 3 10
3 5
6 8
9 10
3 3 10
1 2
3 5
6 7
3 3 10
1 2
3 5
6 8
3 4 10
1 2
6 7
8 9
```

### 输出

```
YES
YES
NO
YES
```

