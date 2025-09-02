---
title: "GRIDFLIP - Flipping Slipping of grids"
layout: "post"
diff: 难度0
pid: SP13926
tag: []
---

# GRIDFLIP - Flipping Slipping of grids

## 题目描述

现有两个字符网格，字符范围仅限于 'a' 到 'z'。我们将这两个网格分别命名为 A 和 B。

## 输入格式

第一行输入一个整数 $n$，表示网格的维度大小（即网格为 $n \times n$）。

接下来的 $n$ 行（从第 2 行到第 $n+1$ 行），每行输入一个长度为 $n$ 的字符串，构成网格 A。

接着的 $n$ 行（从第 $n+2$ 行到第 $2n+1$ 行），每行输入一个长度为 $n$ 的字符串，构成网格 B。

### 约束条件

1. $5 \leq n \leq 1000$
2. 字符串仅由小写字母组成

## 输出格式

要求输出一行，包含三个整数（以空格分隔），分别表示 $i$、$j$ 和 $k$，使得结果为按字典序最大的解。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
ooscz
hkaea
nnzth
khdlf
rejtf
fldhk
htznn
aeakh
zcsoo
ftjer
```

### 输出

```
3 3 4
```

