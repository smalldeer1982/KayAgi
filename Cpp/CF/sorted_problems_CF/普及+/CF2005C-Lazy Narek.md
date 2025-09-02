---
title: "Lazy Narek"
layout: "post"
diff: 普及+/提高
pid: CF2005C
tag: ['动态规划 DP']
---

# Lazy Narek

## 题目描述

$\text{Alice}$ 有 $n$ 个字符串，每个字符串长度为 $m$。

$\text{Alice}$ 会选择 $n$ 个字符串的一个子集，可以为空，将子集中的字符串首尾按原本的相对顺序拼接，然后她会在拼接的字符串中依次查找字符 "n","a","r","e","k"。当这五个字符全被找到后，$\text{Alice}$ 会将自己的分数 $+5$ 然后继续从当前位置向后查找。

之后 $\text{Bob}$ 会扫描整个字符串并查找，如果 $\text{Alice}$ 的查找中有未被访问的 "n","a","r","e" 或 "k"，$\text{Bob}$ 会将自己的分数 $+1$。

请你帮 $\text{Alice}$ 和 $\text{Bob}$ 求出 $\max\{score_{Alice} - score_{Bob}\}$。

## 输入格式

多组测试数据，第一行一个正整数 $T(1 \leq T \leq 10^5)$，表示数据组数。

接下来每个测试数据的第一行两个正整数 $n,m(1 \leq n,m \leq 10^3)$，表示字符串的数量以及每个字符串的长度。

接下来 $n$ 行，每行一个长度为 $m$ 的字符串，意义如题意所述，仅包含小写字母。

$\sum{n \cdot m} \leq 10^6$

## 输出格式

对于每个测试数据，输出一个整数：$score_{Alice} - score_{Bob}$ 的最大值

## 样例 #1

### 输入

```
4
5 2
nn
aa
rr
ee
kk
1 5
narek
1 4
nare
5 7
nrrarek
nrnekan
uuuuuuu
ppppppp
nkarekz
```

### 输出

```
0
5
0
7
```

