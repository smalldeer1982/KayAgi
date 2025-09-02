---
title: "Dreamoon and Strings"
layout: "post"
diff: 提高+/省选-
pid: CF476E
tag: []
---

# Dreamoon and Strings

## 题目描述

Dreamoon 有一个字符串 $s$ 和一个模式串 $p$，他会先从 $s$ 中删除恰好 $x$ 个字符来产生一个新的字符串 $s'$。然后他会计算 $occ(s',p)$，即从 $s'$ 中能找到的等于 $p$ 的不相交的子串数量的最大值。他想让 $occ(s',p)$ 的值尽可能大。

更形式地说，让我们用 $ans(x)$ 表示所有可以从 $s$ 中删去恰好 $x$ 个字符得到的 $s'$ 中 $occ(s',p)$ 的最大值。Dreamoon 想要知道对于所有的 $x$ $(0 \leq x \leq |s|)$，$ans(x)$ 的值。

## 输入格式

第一、二行分别输入一个字符串：$s$，$p$。$(1 \leq |s| \leq 2000,1 \leq |p| \leq 500)$，两串只包含小写英文字母。

## 输出格式

一行，$(|s|+1)$ 个数，分别代表 $ans(0),ans(1),\dots,ans(|s|)$。

## 样例 #1

### 输入

```
aaaaa
aa

```

### 输出

```
2 2 1 1 0 0

```

## 样例 #2

### 输入

```
axbaxxb
ab

```

### 输出

```
0 1 1 2 1 1 0 0

```

