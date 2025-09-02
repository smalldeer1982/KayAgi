---
title: "[ARC031B] 埋め立て"
layout: "post"
diff: 普及/提高-
pid: AT_arc031_2
tag: []
---

# [ARC031B] 埋め立て

## 题目描述

很久很久以前，某地曾有一个岛国。这个岛国由一些岛屿组成。现在，这个岛国决定填海造陆，但还没有决定填海造陆的位置。政府希望填海造陆工程能够将所有岛屿连接起来，成为一个岛屿。

给出 $10$ 格 $×10$ 格的该国地图，请判断：能否仅将一格海洋变成陆地，使该国所有岛屿连接成一个岛屿。另外，地图中表示陆地的格子上下左右互相连接的区域称为一个岛屿。

## 输入格式

输入按以下形式：
$$ A_{1,1} \space A_{1,2} \space \dots \space A_{1,10} $$
$$ A_{2,1} \space A_{2,2} \space \dots \space A_{2,10} $$
$$ : $$
$$ A_{10,1} \space A_{10,2} \space \dots \space A_{10,10} $$ 

- 岛国的地图一定为 $10$ 行。
- 每行一定由 $10$ 个字符组成，每个字符为 'o'（表示陆地）或 'x'（表示海洋）
- 保证至少有一格为陆地。
- 保证至少有一格为海洋。

## 输出格式

如果能将 $1$ 个格子的海洋变成陆地使得整个岛国只含一个岛屿，则输出'YES'，否则输出'NO'。输出结尾请换行。
（如果本来就只有一个岛，也输出'YES'）

## 样例1解释
将红色方框处的格子变成陆地，就能将两个岛屿合并为一个。
![](https://arc031.contest.atcoder.jp/img/arc/031/2-1.png)

## 样例 #1

### 输入

```
xxxxxxxxxx
xoooooooxx
xxoooooxxx
xxxoooxxxx
xxxxoxxxxx
xxxxxxxxxx
xxxxoxxxxx
xxxoooxxxx
xxoooooxxx
xxxxxxxxxx
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
xxxxxxxxxx
xoooooooxx
xxoooooxxx
xxxoooxxxx
xxxxxxxxxx
xxxxxxxxxx
xxxxxxxxxx
xxxoooxxxx
xxoooooxxx
xxxxxxxxxx
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
ooooxooooo
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
xxxxoxxxxx
```

### 输出

```
YES
```

