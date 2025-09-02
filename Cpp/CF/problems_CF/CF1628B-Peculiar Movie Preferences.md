---
title: "Peculiar Movie Preferences"
layout: "post"
diff: 普及+/提高
pid: CF1628B
tag: []
---

# Peculiar Movie Preferences

## 题目描述

给定一个含有$n$个字符串的序列，序列中的每个字符串长度均不超过$3$，判断能否从中选出一个非零子段（可以不连续），使得子段中的字符串按照在序列中的顺序首尾相连构成一个回文串。如果能，输出"YES"，否则输出"NO"。

## 输入格式

第一行一个整数$t$（$1 \leq t \leq 100$），表示测试样例的数量

每一组测试样例的第一行一个整数$n$（所有的$n$之和小于等于$10^5$），表示序列中字符串的总数

接下来的$n$行，每行一个非空且长度小于等于3的字符串，只包含小写字母

## 输出格式

对于每一组测试样例，如果可以构成回文串，则输出"YES"，否则输出"NO"

## 样例 #1

### 输入

```
6
5
zx
ab
cc
zx
ba
2
ab
bad
4
co
def
orc
es
3
a
b
c
3
ab
cd
cba
2
ab
ab
```

### 输出

```
YES
NO
NO
YES
YES
NO
```

