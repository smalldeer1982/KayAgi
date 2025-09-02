---
title: "ModularPowerEquation!!"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_tenka1_2017_f
tag: []
---

# ModularPowerEquation!!

## 题目描述

输入$Q$ $(1\leq Q\leq 100)$组$A,M$ $(0\leq A_i\leq 10^9, 1\leq M_i\leq 10^9(1\leq i\leq Q))$，求任意一个$K$ $(1\leq K\leq 2\times 10^{18})$，使得$A^K\equiv K\ (mod\ M)$

## 输入格式

$ Q $ 

$ A_1 $   $ M_1 $ 

$\dots $

$ A_Q $   $ M_Q $

## 输出格式

第$i$行输出第$i$组的$K$值，若没有合法的$K$,则输出```-1```

## 样例 #1

### 输入

```
4
2 4
3 8
9 6
10 7
```

### 输出

```
4
11
9
2
```

## 样例 #2

### 输入

```
3
177 168
2028 88772
123456789 987654321
```

### 输出

```
7953
234831584
471523108231963269
```

