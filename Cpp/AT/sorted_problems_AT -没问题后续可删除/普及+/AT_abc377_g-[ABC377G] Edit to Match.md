---
title: "[ABC377G] Edit to Match"
layout: "post"
diff: 普及+/提高
pid: AT_abc377_g
tag: ['动态规划 DP', '字典树 Trie']
---

# [ABC377G] Edit to Match

## 题目描述

给你 $N$ 个字符串 $S_1,S_2,\ldots,S_N$ 。每个字符串都由小写英文字母组成。

对于每一个 $k=1,2,\ldots,N$，解决下列问题：

一开始将一个字符串 $T$ 赋为 $S_k$。

接下来，你可以在下列操作中二选一，并可以操作无限次。但每一次操作都会花费 $1$ 的代价。

- 当 $T$ 不为空时，删除 $T$ 的最后一个字符。
- 在 $T$ 后面加上一个任意的小写字母。

求使 $T$ 要么为空，要么与 $S_1,S_2,\ldots,S_{k-1}$ 中的一个匹配所需的最小代价。

## 输入格式

第一行一个正整数 $N$。

第 $2$ 至 $N+1$ 行，每行一个字符串 $S_i$。

## 输出格式

共 $N$ 行。第 $i$ 行输出当 $k=i$ 时的最小代价。

## 说明/提示

- $1\le N\le 2\times10^5$
- $\sum\limits_{i=1}^N|S_i|\le2\times10^5$

## 样例 #1

### 输入

```
3
snuke
snuki
snuuk
```

### 输出

```
5
2
4
```

## 样例 #2

### 输入

```
3
abc
arc
agc
```

### 输出

```
3
3
3
```

## 样例 #3

### 输入

```
8
at
atatat
attat
aatatatt
attattat
ttatta
tta
tt
```

### 输出

```
2
4
3
8
3
6
3
1
```

