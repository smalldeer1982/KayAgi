# [CERC 2021] Lines in a grid

## 题目描述

假设我们有一个 $n \times n$ 的整数网格，例如 $\{(i, j)\}_{i=0, j=0}^{n-1, n-1}$。令 $l_n$ 表示与网格上至少两个点相交的不同直线的数量。

对于 $n = 3$，恰好有 $20$ 条这样的直线，如下图所示。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/hs3oswsp.png)
:::

请计算所有给定 $n$ 的 $l_n$。

## 说明/提示

### 输入范围

- $1 \leq Q \leq 1000$
- $1 \leq n_i \leq 10^7$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
0
20
6```

