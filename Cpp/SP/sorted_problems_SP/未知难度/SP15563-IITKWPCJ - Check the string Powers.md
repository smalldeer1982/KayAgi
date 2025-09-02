---
title: "IITKWPCJ - Check the string Powers"
layout: "post"
diff: 难度0
pid: SP15563
tag: []
---

# IITKWPCJ - Check the string Powers

## 题目描述

Feluda 非常喜欢字符串和数学。作为一名少年，他刚刚学习了幂的概念。由于对这个概念还不太熟悉，他不仅对数字的幂感兴趣，还想着给字符串也加上幂。他把 $A^n$（表示 $A$ 重复连接 $n$ 次）定义为 $A + A + \ldots + A$，即把字符串 $A$ 连续重复 $n$ 次。例如，“bhupkas”$^2$ 就是“bhupkasbhupkas”。

Feluda 想知道，是否能找到正整数 $n$ 和 $m$，使得对于给定的两个字符串 $A$ 和 $B$，有 $A^n = B^m$。对每个测试用例，他只需要回答“YES”或者“NO”，不需要给出具体的 $n$ 和 $m$。

## 输入格式

第一行包含一个整数 $T$，表示测试用例的数量（$T \leq 100$）。

接下来的每行包含两个字符串 $A$ 和 $B$。这些字符串都是非空的，最大长度为 $10^5$，并且仅由小写字母组成。

## 输出格式

对于每个测试用例，如果存在正整数 $n$ 和 $m$ 使得 $A^n = B^m$，则输出“YES”；否则输出“NO”。

## 说明/提示

- $1 \leq T \leq 100$
- $1 \leq |A|, |B| \leq 10^5$
- 字符串 $A$ 和 $B$ 仅包含小写字母。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
a a
ab ba
praveen praveen
```

### 输出

```
YES
NO
YES
```

