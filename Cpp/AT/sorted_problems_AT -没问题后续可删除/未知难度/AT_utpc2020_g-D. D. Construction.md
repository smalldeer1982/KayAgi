---
title: "D. D. Construction"
layout: "post"
diff: 难度0
pid: AT_utpc2020_g
tag: []
---

# D. D. Construction

## 题目描述

给出整数 $N$ 和 $N \times N$ 矩阵 $A$。请输出满足以下条件的整数 $M$ 和 $M$ 个 $N \times N$ 矩阵 $B_1,...B_M $。$1≤M≤1000$

-  对于任意 $1≤i≤M$，$B_i$都是绝对值为 $40$ 以下的整数
-  对于任意 $1≤i≤M$，$det（Bi）$=$det（A）$
- $\sum_{i=1}^MB_i=diag(M A_{11},M A_{22},...,M A_{NN})$

在输入条件下，可以证明满足上述限制的输出是可能的。

[$det$的定义](https://ja.wikipedia.org/wiki/%E8%A1%8C%E5%88%97%E5%BC%8F)

[$diag$的定义](https://ja.wikipedia.org/wiki/%E5%AF%BE%E8%A7%92%E8%A1%8C%E5%88%97)

## 输入格式

第一行 $N$。

接下来 $N$行，每行 $N$ 个整数。

## 输出格式

在第 $1$ 行输出矩阵的个数 $M$。在接下来的$N\times M$行中，对于满足 $1≤i≤M，1≤j≤N$的 $i，j$ ，在$（i-1）\times N+j $行以空白间隔输出 $B_i$的第 $j$行。
### 制约
- 输出保证为整数
- $2≤N≤8$
- $|A_{ij}|≤40$

## 样例 #1

### 输入

```
3
1 0 0
0 1 0
0 0 1
```

### 输出

```
3
-2 -1 2
0 1 1
1 0 -2
0 0 -1
-1 2 -2
0 1 1
5 1 -1
1 0 1
-1 -1 4
```

