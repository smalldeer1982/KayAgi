---
title: "Punctuation"
layout: "post"
diff: 普及/提高-
pid: CF147A
tag: []
---

# Punctuation

## 题目描述

有一个文本，包含小写字母、空格和标点（点、逗号、感叹号和问号），连续的字母组成的序列称为单词。

你的任务是修改这个文本，使它满足一下规则：

1. 相邻两个单词间最多只能有一个空格

2. 标点的前面没有空格，后面有一个空格

（保证两个标点间至少有一个单词，文本的开头、结尾都是字母）

## 输入格式

一行非空字符串，不大于10000个字符

## 输出格式

按照规则编辑好的字符串，末尾不能有多余的空格（可以有换行符）

## 样例 #1

### 输入

```
galileo galilei was an   italian physicist  ,mathematician,astronomer

```

### 输出

```
galileo galilei was an italian physicist, mathematician, astronomer

```

## 样例 #2

### 输入

```
galileo  was  born  in  pisa

```

### 输出

```
galileo was born in pisa

```

