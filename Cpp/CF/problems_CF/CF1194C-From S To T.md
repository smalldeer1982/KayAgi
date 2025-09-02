---
title: "From S To T"
layout: "post"
diff: 普及/提高-
pid: CF1194C
tag: []
---

# From S To T

## 题目描述

你将会得到三个由小写拉丁字符组成的字符串 $s, t, p$

每一次操作中，你可以在 $p$ 中任意选出一个字符删去并插入在 $s$ 中的任意一个位置

例如当 $p$ 为 $\text{aba}$，$s$ 为 $\text{de}$，则以下操作都是合法的

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{ade}$

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{dae}$

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{dea}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{bde}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{dbe}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{deb}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{ade}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{dae}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{dea}$

你的任务是检验是否能经过若干次操作（可能零次），将 $s$ 变为 $t$

## 输入格式

多组数据

第一行包括一个正整数 $q(1\leq q \leq 100)$，描述了数据的组数

对于每一组数据，都会由三排组成

第一排为由小写拉丁字符组成的字符串 $s(1 \leq |s| \leq 100)$

第二排为由小写拉丁字符组成的字符串 $t(1 \leq |t| \leq 100)$

第三排为由小写拉丁字符组成的字符串 $p(1\leq |p| \leq 100)$

## 输出格式

如果能够对 $s$ 进行若干次操作使其变为 $t$，请输出 $\text{YES}$，否则输出 $\text{NO}$

## 样例 #1

### 输入

```
4
ab
acxb
cax
a
aaaa
aaabbcc
a
aaaa
aabbcc
ab
baaa
aaaaa

```

### 输出

```
YES
YES
NO
NO

```

