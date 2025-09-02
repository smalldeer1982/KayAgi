---
title: "CODWRECK4 - Alien Language"
layout: "post"
diff: 难度0
pid: SP32940
tag: []
---

# CODWRECK4 - Alien Language

## 题目描述

给你 $n$ 个单词和 $m$ 个句子，句子没有空格，是由若干单词直接拼接而成的。

现在你需要将句子拆分成组成它的单词。

## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行，每行一个字符串，表示一个单词。

第 $n+2$ 行一个正整数 $m$。

接下来 $m$ 行，每行一个字符串，表示一个句子。

## 输出格式

输出共 $m$ 行，每行若干个用空格隔开的字符串，表示被拆分后的句子。

## 说明/提示

$1\le n\le 10^5,1\le m\le 10^3$。 

单词的长度不超过 $20$，句子的长度不超过 $40$。

本题输入输出量较大，请使用较快的输入输出方法。

如果句子有多种拆分方法，输出拆分后长度最小的一种。（长度包括空格）

Translated by \_Ponder_

## 样例 #1

### 输入

```
6
coding
code
wreck
dechef
co
chef
2
codingwreck
codechef\n
```

### 输出

```
coding wreck
co dechef
```

