---
title: "Context Advertising"
layout: "post"
diff: 提高+/省选-
pid: CF309B
tag: []
---

# Context Advertising

## 题目描述

你有一个有 $n$ 个**单词**的文本，请按要求重新编辑此文本后输出。

以下为规定:

1. 一个单词中的每个字母都在一行上。
2. 单词之间以**若干**个空格分隔。
3. 最终的文本应当是原文本中的一个子段。也就是说，选择一个区间 $[i, j]$，然后让第 $i$ 个单词到第 $j$ 个单词都出现在最终文本上。
4. 最多有 $r$ 行，每行最多 $c$ 个**字符**。
5. 包含的单词数尽可能多。

## 输入格式

第一行包含三个整数 $n, r, c\ (1 \leq n, r, c \leq 10 ^ {6}$，$r\times c \leq 10 ^ 6)$。下一行为一个文本，包括 $n$ 个单词。单词仅包含小写英文字母，并且不能为空。所有单词中的字符总数不超过 $5 \times 10^{6}$。

## 输出格式

一行，符合要求的文本。如果有多个答案，请输出其中的任何一个。

请注意，横幅的某些行可以为空。允许不输出这些行。

## 样例 #1

### 输入

```
9 4 12
this is a sample text for croc final round

```

### 输出

```
this is a
sample text
for croc
final round

```

## 样例 #2

### 输入

```
9 1 9
this is a sample text for croc final round

```

### 输出

```
this is a

```

## 样例 #3

### 输入

```
6 2 3
croc a a a croc a

```

### 输出

```
a a
a

```

## 样例 #4

### 输入

```
2 2 5
first second

```

### 输出

```
first

```

