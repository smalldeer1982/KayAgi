---
title: "Single Wildcard Pattern Matching"
layout: "post"
diff: 普及/提高-
pid: CF1023A
tag: ['模拟', '字符串']
---

# Single Wildcard Pattern Matching

## 题目描述

给定两个小写英文单词 $s,t$，其中 $s$ 包含还不多于一个的 `*`。$s$ 的长度为 $n$，而 $t$ 的长度为 $m$。

$s$ 中的 `*` 可以被替换为任意小写字母串（可以是空串），但其他字母不能被更改或者调换顺序。如果将 `*` 替换为一个任意小写字母串之后，$s=t$，那么我们称 $s,t$ 是匹配的。

例如，字符串 $s=$ `lu*gu` 与 `luogu` `lugu` `luooooogu`都是匹配的，但与字符串 `lougu` `log` `lu^_^gu` `lu114514gu` 都是不匹配的。

如果给定的 $s,t$ 是匹配的，输出 `YES`，否则输出 `NO`。

## 输入格式

第一行输入两个整数 $n,m$，分别表示 $s$ 和 $t$ 的长度。

第二行输入字符串 $s$，保证 $s$ 中只含有小写字母和不多于一个的 `*`。

第三行输入字符串 $t$，保证 $t$ 中只含有小写字母。

## 输出格式

如果 $s$ 与 $t$ 是匹配的，那么输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le2\times10^5$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

## 样例 #1

### 输入

```
6 10
code*s
codeforces

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
6 5
vk*cup
vkcup

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
1 1
v
k

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
9 6
gfgf*gfgf
gfgfgf

```

### 输出

```
NO

```

