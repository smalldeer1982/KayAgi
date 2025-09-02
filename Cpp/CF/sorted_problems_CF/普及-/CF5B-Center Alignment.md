---
title: "Center Alignment"
layout: "post"
diff: 普及-
pid: CF5B
tag: ['字符串']
---

# Center Alignment

## 题目描述

几乎每一个文本编辑器都有文字居中对齐的功能，因此Berland的著名文本编辑器Textpad的开发者们希望在产品的第四次更新中加入此功能。

您的任务是尽快编写一个文本居中对齐的原型程序，祝您好运!

## 输入格式

输入包含一行或者多行文本，每行均由拉丁字母、数字和/或空格组成，每一行都不会以空格开始或者结束，保证至少有一行长度大于等于1。每行的长度和总行数都不会超过1000。

## 输出格式

将文本居中对齐，用星号'\*'框起整个文本。

如果无法实现完美的居中对齐，请将这一行文本向左或者向右微调(您应该在第一次遇到此类情况时将该行文本向左微调，下一次向右，在下一次向左...依此类推)。

## 样例 #1

### 输入

```
This  is

Codeforces
Beta
Round
5

```

### 输出

```
************
* This  is *
*          *
*Codeforces*
*   Beta   *
*  Round   *
*     5    *
************

```

## 样例 #2

### 输入

```
welcome to the
Codeforces
Beta
Round 5

and
good luck

```

### 输出

```
****************
*welcome to the*
*  Codeforces  *
*     Beta     *
*   Round 5    *
*              *
*      and     *
*  good luck   *
****************

```

