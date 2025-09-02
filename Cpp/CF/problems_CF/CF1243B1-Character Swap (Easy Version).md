---
title: "Character Swap (Easy Version)"
layout: "post"
diff: 普及-
pid: CF1243B1
tag: []
---

# Character Swap (Easy Version)

## 题目描述

### 题意简述

给定两个长为 $n$ 的字符串 $s,t$。

您需要进行一次交换：找到一组 $i,j$ 满足 $1\leq i,j \leq n$，交换 $s_i$ 和 $t_j$。

问是否可以通过这次交换使得 $s=t$。

注意：您不能不进行交换。

## 输入格式

第一行一个正整数 $k(1\leq k \leq 10)$，表示数据的组数。

对于每组数据，第一行一个正整数 $n(2\leq n \leq 10^4)$。

接下来一行一个字符串 $s$。

接下来一行一个字符串 $t$。

## 输出格式

对于每组数据，如果可以通过一次交换使得 $s=t$，输出 `Yes`，否则输出 `No`。

您可以输出 `Yes` 和 `No` 的任意大小写形式。当答案为 `Yes` 时，输出 `yes`，`YES`，`YEs`，`yeS` 等答案都会被判为正确。

翻译贡献者 U108949

## 样例 #1

### 输入

```
4
5
souse
houhe
3
cat
dog
2
aa
az
3
abc
bca

```

### 输出

```
Yes
No
No
No

```

