---
title: "Lexicographically Maximum Subsequence"
layout: "post"
diff: 普及-
pid: CF196A
tag: []
---

# Lexicographically Maximum Subsequence

## 题目描述

你现在有一个只包含小写英文字母的字符串，要求求它的最大字典序子序列。

我们把一个非空字符串s[p_{1}p_{2}...\ p_{k}]=s_{p1}s_{p2}...\ s_{pk}(1<=p_{1}<p_{2}<...<p_{k}<=|s|)叫做字符串s=s1s2…s|s|的一个子序列。

如果|x|>|y|而且x1=y1,x2=y2…X|y|=Y|y|或者存在一个数字r (r<|x|,r<|y|)满足x1=y1,x2=y2…X|y|=Y|y|并且x_{r+1}>y_{r+1}，那么字符串x=x1x2…x|x|在字典序上比字符串y=y1y2…y|y|大。在行中的字符根据他们的ASCII码进行比较

## 输入格式

只有一行，包括一个非空的只含小写字母的字符串s，字符串长度不超过10^5

## 输出格式

输出只有一行，输出字符串s的 最大字典序子序列

## 说明/提示

让我们看一下样例并看一看待求的子序列长什么样子(用大写粗体字母标注）

样例1:a**B**a**BBA**

样例2:abb**C**b**CC**a**C**bb**CB**aa**BA**

## 样例 #1

### 输入

```
ababba

```

### 输出

```
bbba

```

## 样例 #2

### 输入

```
abbcbccacbbcbaaba

```

### 输出

```
cccccbba

```

