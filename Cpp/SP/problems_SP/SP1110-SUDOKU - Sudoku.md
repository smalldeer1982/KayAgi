---
title: "SUDOKU - Sudoku"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP1110
tag: []
---

# SUDOKU - Sudoku

## 题目描述

## 题目大意

一个数独的网格是由$16*16$个小格组成的, 这些小格又被分为$4*4=16$个小组,
一些小格填入了从$A$至$P$(字母表前$16$个)的字母，不过一般填成数字。

游戏目的是将所有小格填满，而使每行，每列和每个$4*4$小组中不重复的包含这$16$个字母。

给出的初始状态满足以上要求且满足唯一解。

## 输入格式

第一行包含一个整数$K$($K<=10$),表示有$K$组数据.

每一组数据会有$16$字符一行,共$16$行字符串,其中以'-'表示空格.

每两组数据间由空行相隔.

## 输出格式

对每组数据输出一个$16*16$的表格，要求按照原输入顺序和格式输出.

每两组数据间由空行相隔.

## 样例 #1

### 输入

```
1
--A----C-----O-I 
-J--A-B-P-CGF-H-
--D--F-I-E----P-
-G-EL-H----M-J--
----E----C--G---
-I--K-GA-B---E-J 
D-GP--J-F----A--
-E---C-B--DP--O-
E--F-M--D--L-K-A 
-C--------O-I-L-
H-P-C--F-A--B---
---G-OD---J----H 
K---J----H-A-P-L 
--B--P--E--K--A-
-H--B--K--FI-C--
--F---C--D--H-N-
```

### 输出

```
FPAHMJECNLBDKOGI 
OJMIANBDPKCGFLHE 
LNDKGFOIJEAHMBPC 
BGCELKHPOFIMAJDN 
MFHBELPOACKJGNID 
CILNKDGAHBMOPEFJ 
DOGPIHJMFNLECAKB 
JEKAFCNBGIDPLHOM 
EBOFPMIJDGHLNKCA 
NCJDHBAEKMOFIGLP 
HMPLCGKFIAENBDJO 
AKIGNODLBPJCEFMH 
KDEMJIFNCHGAOPBL 
GLBCDPMHEONKJIAF 
PHNOBALKMJFIDCEG 
IAFJOECGLDPBHMNK
```

