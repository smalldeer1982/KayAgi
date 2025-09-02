---
title: ""a" String Problem"
layout: "post"
diff: 普及+/提高
pid: CF1984D
tag: ['数论', '哈希 hashing']
---

# "a" String Problem

## 题目描述

You are given a string $ s $ consisting of lowercase Latin characters. Count the number of nonempty strings $ t \neq $ " $ \texttt{a} $ " such that it is possible to partition $ ^{\dagger} $ $ s $ into some substrings satisfying the following conditions:

- each substring either equals $ t $ or " $ \texttt{a} $ ", and
- at least one substring equals $ t $ .

 $ ^{\dagger} $ A partition of a string $ s $ is an ordered sequence of some $ k $ strings $ t_1, t_2, \ldots, t_k $ (called substrings) such that $ t_1 + t_2 + \ldots + t_k = s $ , where $ + $ represents the concatenation operation.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The only line of each test case contains a string $ s $ consisting of lowercase Latin characters ( $ 2 \leq |s| \leq 2 \cdot 10^5 $ ).

The sum of $ |s| $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of nonempty strings $ t \neq $ " $ \texttt{a} $ " that satisfy all constraints.

## 说明/提示

In the first test case, $ t $ can be " $ \texttt{aa} $ ", " $ \texttt{aaa} $ ", " $ \texttt{aaaa} $ ", or the full string.

In the second test case, $ t $ can be " $ \texttt{b} $ ", " $ \texttt{bab} $ ", " $ \texttt{ba} $ ", or the full string.

In the third test case, the only such $ t $ is the full string.

## 样例 #1

### 输入

```
8
aaaaa
baba
cabacb
aaabaaa
bitset
ab
abbaaaabbb
yearnineteeneightyfour
```

### 输出

```
4
4
1
16
1
2
3
1
```

