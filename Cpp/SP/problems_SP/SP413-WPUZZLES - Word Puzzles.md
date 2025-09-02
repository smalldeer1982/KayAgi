---
title: "WPUZZLES - Word Puzzles"
layout: "post"
diff: 省选/NOI-
pid: SP413
tag: []
---

# WPUZZLES - Word Puzzles

## 题目描述

--------

给出一个由大写字母组成的L*C的图案，给出W个询问，每个询问给出一个字符串，输出该字符串在图案中出现的位置（保证询问的字符串都可以在图案中找到，若有多个解，输出其中一个解即可）

![](https://cdn.luogu.com.cn/upload/image_hosting/qh4uvvgh.png)

------------

## 输入格式

给出T组数据，对于每组数据：
第1行包含3个整数，L，C，W（0<L，C,W<=1000)，分别为行数、列数和询问数量.

第2～L+1行，每行C个字符给出图案

第L+2～L+W+1行，每行一个任意长度的字符，表示要求你在图案中找出该字符串

## 输出格式

对于每组数据，输出W行，每行2个数字及一个字符，分别表示该询问的字符串在图案中出现的位置（第一个字母的坐标，从0开始）及该字符串的方向，向上为记A，字母沿方向顺时针递增，共有8种方向。
##### 在每组数据之间输出一个换行

## 样例 #1

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

