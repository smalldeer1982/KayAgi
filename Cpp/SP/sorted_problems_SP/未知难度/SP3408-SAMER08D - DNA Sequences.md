---
title: "SAMER08D - DNA Sequences"
layout: "post"
diff: 难度0
pid: SP3408
tag: []
---

# SAMER08D - DNA Sequences

## 题目描述

Thomas 是一名研究 DNA 序列的计算机科学家，他的任务是计算给定字符串对的最长公共子序列。设有一个字母表 $\Sigma$，以及一个单词 $w = a_1 a_2 \ldots a_r$，其中每个字符 $a_i$ 属于 $\Sigma$。单词 $w$ 的子序列是形如 $x = a_{i1} a_{i2} \ldots a_{is}$ 的字符串，在原字符串中字符的顺序不变，且对应索引满足 $1 \leq i_1 < i_2 < \ldots < i_s \leq r$。如果对于所有的 $j = 1, 2, \ldots, s-1$，都有 $i_{j+1} = i_j + 1$，那么子序列 $x$ 就是一个段。例如，单词“ove”是“lovely”的一个段，而“loly”则是“lovely”的一个子序列，但不是一个段。

若一个单词同时是两个单词 $w_1$ 和 $w_2$ 的子序列，则称其为这两个单词的公共子序列。对于 $w_1$ 和 $w_2$，最长公共子序列是它们所有公共子序列中长度最大者。例如，考虑 $w_1 = \text{lovxxelyxxxxx}$ 和 $w_2 = \text{xxxxxxxlovely}$。如 $w_3 = \text{lovely}$ 和 $w_4 = \text{xxxxxxx}$，后者长度为 7，二者都是 $w_1$ 与 $w_2$ 的公共子序列。实际上，$w_4$ 是它们的最长公共子序列。注意，虽然长度为 0 的空字符串总是一个公共子序列，但它不是最长的。

对于 Thomas 来说，还有一个额外的要求：公共子序列必须由两个字符串中长度至少为 $K$ 的段组成。比如，如果 Thomas 决定 $K = 3$，那么他会认为“lovely”是“lovxxelyxxxxx”和“xxxxxxxlovely”的一个符合条件的公共子序列，而“xxxxxxx”虽然也是一个公共子序列且长度为 7，但不符合要求。你能帮助 Thomas 完成这个任务吗？

## 输入格式

输入包含多个测试用例。每个测试用例的第一行包含一个整数 $K$，表示公共段的最小长度，满足 $1 \leq K \leq l$。接着两行分别给出两个字符串 $w_1$ 和 $w_2$，每个字符串的长度 $l$ 满足 $1 \leq l \leq 10^5$。

## 输出格式

对于每个测试用例，输出一行，表示由这两个字符串中长度至少为 $K$ 的连续段组成的最长子序列的长度。如果没有这样的公共子序列存在，输出 0。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
lovxxelyxxxxx
xxxxxxxlovely
1
lovxxelyxxxxx
xxxxxxxlovely
3
lovxxxelxyxxxx
xxxlovelyxxxxxxx
4
lovxxxelyxxx
xxxxxxlovely
0
```

### 输出

```
6
7
10
0
```

