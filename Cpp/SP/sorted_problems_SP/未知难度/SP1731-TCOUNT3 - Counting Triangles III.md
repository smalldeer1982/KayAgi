---
title: "TCOUNT3 - Counting Triangles III"
layout: "post"
diff: 难度0
pid: SP1731
tag: []
---

# TCOUNT3 - Counting Triangles III

## 题目描述

我们将题目 [TRICOUNT](https://www.luogu.com.cn/problem/SP1724) 中的边长为 $n$ 的正三角形称为 $n$ 阶三角形。将 $12$ 个 $n$ 阶三角形通过如下方式摆放可以得到一个 $n$ 阶六芒星。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1731/2a826fdc032b197c797b57e0a580c733b43c8526.png)

求一个 $n$ 阶六芒星包含的正三角形个数。

## 输入格式

先输入一个数 $T$。

后面 $T$ 行，每行一个正整数 $i$。

## 输出格式

一共 $T$ 行，每行输出 $i$ 阶六芒星中包含的正三角形个数，答案不超过 $\rm unsigned\ long\ long$ 范围。

## 说明/提示

样例中要求 $1$ 阶六芒星中正三角形个数。容易数出 $1$ 阶六芒星中有 $12$ 个 $1$ 阶三角形，$6$ 个 $2$ 阶三角形和 $2$ 个 $3$ 阶三角形。

## 样例 #1

### 输入

```
1
1
```

### 输出

```
20
```

