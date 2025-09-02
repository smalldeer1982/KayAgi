---
title: "Alphabetical Strings"
layout: "post"
diff: 入门
pid: CF1547B
tag: []
---

# Alphabetical Strings

## 题目描述

若一个长度为 $n$ 的字符串 $s$ 是用以下方法构造的，我们称 $s$ 合法。

- $s$ 初始为空；

- 对 $s$ 进行 $n$ 操作，第 $i$ 次操作可以将字典序中排名第 $i$ 的字符插入到 $s$ 的最前面或最后面。

题目给定 $t$ 个字符串，请你分别判断它们是否合法。

## 输入格式

第一行包含一个整数 $t$。

接下来的 $t$ 行，每行各有一个长度在 $1$ 到 $26$ 之间字符串 $s$。

## 输出格式

对于每个字符串输出 `YES` 或 `NO`（你也可以输出 `yEs`，`yes` 之类的东西qwq），中间用一个换行隔开。

## 样例 #1

### 输入

```
11
a
ba
ab
bac
ihfcbadeg
z
aa
ca
acb
xyz
ddcba
```

### 输出

```
YES
YES
YES
YES
YES
NO
NO
NO
NO
NO
NO
```

