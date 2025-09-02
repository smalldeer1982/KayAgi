---
title: "Technical Support"
layout: "post"
diff: 普及-
pid: CF1754A
tag: []
---

# Technical Support

## 题目描述

### 题面翻译

给定一个只包含大写字母 $\texttt{Q}$ 和 $\texttt{A}$ 的字符串，如果字符串里的每一个 $\texttt{Q}$ 都能与**在其之后**的 $\texttt{A}$ 一一对应地匹配，则输出字符串 $\texttt{Yes}$，否则输出字符串 $\texttt{No}$。注意，可以有 $\texttt{A}$ 没有被匹配，但每个 $\texttt{Q}$ 必须成功地匹配。

## 输入格式

输入一个只包含大写字母 $\texttt{Q}$ 和 $\texttt{A}$ 的字符串。

## 输出格式

输出字符串 $\texttt{Yes}$ 或 $\texttt{No}$。

## 样例 #1

### 输入

```
5
4
QQAA
4
QQAQ
3
QAA
1
Q
14
QAQQAQAAQQQAAA
```

### 输出

```
Yes
No
Yes
No
Yes
```

