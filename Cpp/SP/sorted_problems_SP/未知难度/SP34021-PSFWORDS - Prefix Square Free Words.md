---
title: "PSFWORDS - Prefix Square Free Words"
layout: "post"
diff: 难度0
pid: SP34021
tag: []
---

# PSFWORDS - Prefix Square Free Words

## 题目描述

定义square string为两个相同的字符串相拼接，比如aa和abab。而abba就不是一个square string。

定义prefix-square free string是一个所有前缀均不是square string的字符串。例如abcacb就是一个prefix-square free strings，但是abcabc就不是。

给出字母表中包含的字母个数m,求由字母表中字母组成的非空长度小于等于n的prefix-square free strings的个数。

答案会很大，结果需要对2的32次方取余。

## 输入格式

有多组数据，第一行输入T,代表数据的组数。

之后的T行每行有两个整数，代表n和m。

## 输出格式

对于每一组数据，输出一个整数。

## 说明/提示

1≤T≤100

1≤n≤100,1≤m≤10^9

## 样例 #1

### 输入

```
2
3 2
4 6
```

### 输出

```
8
1266
```

