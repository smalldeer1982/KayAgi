# [ABC302B] Find snuke

## 题目描述

给你一个 $H$ 行 $W$ 列的字符矩阵。请你在当中的行列或者 $45\degree$ 斜上的八个方向上寻找连续的五个字符 `s`，`n`，`u`，`k`，`e`，并依次输出它们的位置。保证有且仅有一组解。

## 样例 #1

### 输入

```
6 6
vgxgpu
amkxks
zhkbpp
hykink
esnuke
zplvfj```

### 输出

```
5 2
5 3
5 4
5 5
5 6```

## 样例 #2

### 输入

```
5 5
ezzzz
zkzzz
ezuzs
zzznz
zzzzs```

### 输出

```
5 5
4 4
3 3
2 2
1 1```

## 样例 #3

### 输入

```
10 10
kseeusenuk
usesenesnn
kskekeeses
nesnusnkkn
snenuuenke
kukknkeuss
neunnennue
sknuessuku
nksneekknk
neeeuknenk```

### 输出

```
9 3
8 3
7 3
6 3
5 3```

