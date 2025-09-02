---
title: "Fighting the Heat"
layout: "post"
diff: 难度0
pid: UVA1142
tag: []
---

# Fighting the Heat

## 题目描述

你有一个 $n$ 行 $m$ 列的网格，每个单元格都有一个字母。你还有一个单词列表。你的目标是在网格上高亮显示所有横向、纵向或斜向，正向或反向出现的单词，并从上到下、从左到右输出未高亮的字符组成的单词。

## 输入格式

**本题有多组数据**。

第一行两个整数 $n$ 和 $m$ （$0<n,m\le40$）。

第二行一个整数 $k$（$0 < k \le 200$），表示列表中单词的数量。

接下来 $k$ 行，每行一个字符串表示一个单词。单词的字母不超过 $22$ 个。

接下来 $n$ 行，每行 $m$ 个大写字母，表示网格。

## 输出格式

对于每组数据，输出一行得到的单词。

## 说明/提示

### 输入

```
6 6
7
ALLY
BARE
BARED
FINES
HIND
LORD
WONG
BBARED
ACALHF
RWOEII
EROSNN
DARNDE
ALLYGS
```

### 输出

```
CAESAR
```

