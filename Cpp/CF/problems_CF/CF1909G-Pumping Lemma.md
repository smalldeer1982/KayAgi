---
title: "Pumping Lemma"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1909G
tag: ['字符串']
---

# Pumping Lemma

## 题目描述

有两个只含小写字母的字符串 $s$ 和 $t$，长度分别为 $n$ 和 $m$。

请计算满足下列要求的字符串三元组 $(x,y,z)$ 有几个：

- $s=x+y+z$ （$+$ 代表连接）；

- $t = x+\underbrace{ y+\dots+y }_{k \text{ 个}} + z$，其中 $k$ 为整数。

## 输入格式

第一行两个整数 $n,m(1 \le n < m \le 10^7)$。

第二行一个字符串 $s$。

第三行一个字符串 $t$。

## 输出格式

一行，一个整数表示答案。

## 样例 #1

### 输入

```
4 8
abcd
abcbcbcd
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 5
aaa
aaaaa
```

### 输出

```
5
```

## 样例 #3

### 输入

```
12 16
abbababacaab
abbababababacaab
```

### 输出

```
8
```

