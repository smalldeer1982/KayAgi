---
title: "Asterisk Substrings"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1276F
tag: []
---

# Asterisk Substrings

## 题目描述

给定一个字符集为小写字母的长度为 $n$ 的字符串 $s$，设 $t_i$ 表示将 $s$ 中的第 $i$ 个字符替换为特殊字符 $\text{*}$ 时得到的字符串，比如当 $s=\text{abc}$ 时，$t_1=\text{*bc}$，$t_2 = \text{a*c}$，$t_3 = \text{ab*}$。

求字符串集合 $\{s,t_1,t_2,t_3,...,t_n\}$ 中本质不同的子串个数（需要计算空串）。

注意 $\text{*}$ 仅表示一个字符，不表示其他含义（如通配符）。

## 输入格式

一行一个长度为 $n$（$1 \le n \le {10}^5$）的字符串 $s$。

## 输出格式

一行一个整数表示本质不同的子串个数。

## 样例 #1

### 输入

```
abc

```

### 输出

```
15

```

