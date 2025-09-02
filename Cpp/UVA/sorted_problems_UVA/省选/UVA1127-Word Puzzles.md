---
title: "Word Puzzles"
layout: "post"
diff: 省选/NOI-
pid: UVA1127
tag: []
---

# Word Puzzles

## 题目描述

给定一个 $n\times m$ 的字符矩阵和 $k$ 个模式串，请找出每个模式串在矩阵中出现的位置和方向。具体地，我们认为矩阵的左上角为原点 $(0,0)$，行和列从 $0$ 开始编号；共有 $8$ 种可能的方向，从正北开始顺时针依次编号为 `A` ~ `H`（点 $a$ 在点 $b$ 的正北当且仅当它们在同一列上且 $a$ 所在行号小于 $b$ 所在行号，其余方向以此类推）。对于每个模式串，你只需要输出该串的首个字符在矩阵中的位置，以及该串的方向。

Statement fixed by @liugh_


每组数据之后应输出一行空行。

## 输入格式

**输入一共 $t$ 组数据。**

第一行一个整数 $t$，表示数据的组数。

对于每组数据，第一行三个整数 $n,m,k$，表示矩阵的行数，矩阵的列数，模式串的个数。

接下来 $n$ 行，每行 $m$ 个字符，表示给定的字符矩阵。

接下来 $k$ 行，第 $i$ 行一个字符串 $s_i$，表示给定的模式串。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1\le n,m,k\le 1000$。
- $1\le|s_i|\le 1000$，其中 $|s_i|$ 表示第 $i$ 个模式串的长度。
- 给定的字符矩阵和 $s_i$ 中只包含大写英文字母。

## 样例 #1

### 输入

```
2
3 3 2
ABC
DEF
GHI
AEI
FED
2 4 4
ABCD
EFGH
GH
EB
ABC
BF
```

### 输出

```
0 0 D
1 2 G

1 2 C
1 0 B
0 0 C
0 1 E
```

## 样例 #2

### 输入

```
1
20 20 10
QWSPILAATIRAGRAMYKEI
AGTRCLQAXLPOIJLFVBUQ
TQTKAZXVMRWALEMAPKCW
LIEACNKAZXKPOTPIZCEO
FGKLSTCBTROPICALBLBC
JEWHJEEWSMLPOEKORORA
LUPQWRNJOAAGJKMUSJAE
KRQEIOLOAOQPRTVILCBZ
QOPUCAJSPPOUTMTSLPSF
LPOUYTRFGMMLKIUISXSW
WAHCPOIYTGAKLMNAHBVA
EIAKHPLBGSMCLOGNGJML
LDTIKENVCSWQAZUAOEAL
HOPLPGEJKMNUTIIORMNC
LOIUFTGSQACAXMOPBEIO
QOASDHOPEPNBUYUYOBXB
IONIAELOJHSWASMOUTRK
HPOIYTJPLNAQWDRIBITG
LPOINUYMRTEMPTMLMNBO
PAFCOPLHAVAIANALBPFS
MARGARITA
ALEMA
BARBECUE
TROPICAL
SUPREMA
LOUISIANA
CHEESEHAM
EUROPA
HAVAIANA
CAMPONESA
```

### 输出

```
0 15 G
2 11 C
7 18 A
4 8 C
16 13 B
4 15 E
10 3 D
5 1 E
19 7 C
11 11 H
```

