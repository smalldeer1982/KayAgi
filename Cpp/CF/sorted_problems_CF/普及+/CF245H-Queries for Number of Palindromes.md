---
title: "Queries for Number of Palindromes"
layout: "post"
diff: 普及+/提高
pid: CF245H
tag: ['字符串', '动态规划 DP', '区间 DP', '前缀和']
---

# Queries for Number of Palindromes

## 题目描述

给你一个字符串s由小写字母组成，有q组询问，每组询问给你两个数，l和r，问在字符串区间l到r的字串中，包含多少回文串。

## 输入格式

第1行，给出s，s的长度小于5000
第2行给出q(1<=q<=10^6)
第2至2+q行 给出每组询问的l和r

## 输出格式

输出每组询问所问的数量。

## 样例 #1

### 输入

```
caaaba
5
1 1
1 4
2 3
4 6
4 5

```

### 输出

```
1
7
3
4
2

```

