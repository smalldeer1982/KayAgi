---
title: "Hamming Distance"
layout: "post"
diff: 省选/NOI-
pid: CF193C
tag: []
---

# Hamming Distance

## 题目描述

定义函数 $h(s,t)$ 为：
- 两个长度相等的字符串 $s,t$ 中满足 $s_i \neq t_i$ 的 $i$ 的个数。

现在给出六个数 $a,b,c,d,e,f$，要你构造出**四个长度相等的仅由字符 $\texttt{ab}$ 构成的字符串** $s_1,s_2,s_3,s_4$，满足：
- $h(s_1,s_2)=a$，$h(s_1,s_3)=b$，$h(s_1,s_4)=c$，$h(s_2,s_3)=d$，$h(s_2,s_4)=e$，$h(s_3,s_4)=f$。
- 它们长度尽可能小。

构造出一个合法的方案，无解输出 $-1$。

数据范围 $0 \leq a,b,c,d,e,f \leq 10^5$，$\max\{a,b,c,d,e,f\}>0$。

## 输入格式

第一行三个整数 $a, b, c$；

第二行两个整数 $d, e$；

第三行一个整数 $f$。

## 输出格式

第一行，一个整数表示字符串长度 $len$。

接下来四行，每行一个长度为 $len$ 的字符串 $s_i$

本题包含 SPJ，所以不用担心多解的问题

## 样例 #1

### 输入

```
4 4 4
4 4
4

```

### 输出

```
6
aaaabb
aabbaa
bbaaaa
bbbbbb

```

