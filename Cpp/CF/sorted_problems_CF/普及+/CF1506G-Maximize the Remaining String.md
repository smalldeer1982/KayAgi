---
title: "Maximize the Remaining String"
layout: "post"
diff: 普及+/提高
pid: CF1506G
tag: ['贪心', '单调队列']
---

# Maximize the Remaining String

## 题目描述

给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 输入格式

多测
第一行一个正整数 $T$（$1\le T\le 10^4$）表示数据组数。  
接下来 $T$ 行，每行一个由小写字母组成的字符串 $s$（$\sum|s|\le 2\times 10^5$）。

## 输出格式

输出 $T$ 行  
对于每组输入的 $s$，输出一行一个字符串表示满足要求且字典序最大的 $t$。

## 样例 #1

### 输入

```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz
```

### 输出

```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz
```

