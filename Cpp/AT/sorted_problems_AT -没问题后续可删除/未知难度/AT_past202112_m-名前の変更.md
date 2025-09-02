---
title: "名前の変更"
layout: "post"
diff: 难度0
pid: AT_past202112_m
tag: []
---

# 名前の変更

## 题目描述

对 $n$ 个字符串进行 $q$ 次操作。每次操作给出一个整数 $x$ 和一个字符串 $t$，表示将字符串按字典序升序排列后（若出现并列则按它们在原序列中的顺序排列），将第 $x$ 个字符串修改为 $t$。

请在所有操作完成后，输出原序列。

## 输入格式

第一行为两个整数 $n$ 和 $q$。

第二行为 $n$ 个字符串，表示序列 $s$。

最后 $q$ 行，每行输入一个整数 $x$ 和一个字符串 $t$。

## 输出格式

在所有操作完成后，输出序列，每个字符串一行，共 $n$ 行。

## 说明/提示

#### 数据规模与约定

对于全部测试点，数据保证：

- $1\le n,q\le 10^5$，$1\le x\le n$；
- 任意一个字符串的长度 $\in[1,5]$，且串中仅包含英文小写字母。

## 样例 #1

### 输入

```
3 3
taro jiro sabro
1 taro
2 jiro
3 taro
```

### 输出

```
jiro taro sabro
```

## 样例 #2

### 输入

```
10 10
yo gaaj uab y reah y dyg ix rwq p
10 tvbvr
8 ax
7 xr
9 vw
10 ky
10 wlxtw
2 guoux
10 wbct
9 zbuxx
5 gq
```

### 输出

```
tvbvr gaaj ax zbuxx reah gq guoux ix wbct p
```

