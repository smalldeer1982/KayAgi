---
title: "[ABC268D] Unique Username"
layout: "post"
diff: 普及+/提高
pid: AT_abc268_d
tag: []
---

# [ABC268D] Unique Username

## 题目描述

高桥君有取名选择困难症，于是他找到你，希望帮他取一个用户名。

具体取名规则是：把给定的 $N$ 个字符串 $S_1，S_2,\ldots,S_N$ 以任意顺序排列，并在每两个字符串中间加 $\ge1$ 个下划线，要求不能与后面给定的 $M$ 个字符串 $T_1，T_2,\ldots,T_M$ 中的任意一个相同。

其中，你给出的字符串的长度 $X$ 应该满足 $3\le X \le 16$ 。如果无法满足条件，输出 $-1$。

## 输入格式

第一行两个整数，分别为 $N$ 和 $M$ ；

后 $N$ 行每行一个字符串 $S_i$ ；

后 $M$ 行每行一个字符串 $T_i$ 。

## 输出格式

一个满足题意的字符串 $X$ 。如果没有满足的，输出一个数 $-1$ 。

## 样例 #1

### 输入

```
1 1
chokudai
chokudai
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2 2
choku
dai
chokudai
choku_dai
```

### 输出

```
dai_choku
```

## 样例 #3

### 输入

```
2 2
chokudai
atcoder
chokudai_atcoder
atcoder_chokudai
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
4 4
ab
cd
ef
gh
hoge
fuga
____
_ab_cd_ef_gh_
```

### 输出

```
ab__ef___cd_gh
```

