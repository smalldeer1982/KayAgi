---
title: "Tricky Alchemy"
layout: "post"
diff: 普及-
pid: CF912A
tag: ['模拟', '数学', '概率论']
---

# Tricky Alchemy

## 题目描述

During the winter holidays, the demand for Christmas balls is exceptionally high. Since it's already $ 2018 $ , the advances in alchemy allow easy and efficient ball creation by utilizing magic crystals.

Grisha needs to obtain some yellow, green and blue balls. It's known that to produce a yellow ball one needs two yellow crystals, green — one yellow and one blue, and for a blue ball, three blue crystals are enough.

Right now there are $ A $ yellow and $ B $ blue crystals in Grisha's disposal. Find out how many additional crystals he should acquire in order to produce the required number of balls.

## 输入格式

The first line features two integers $ A $ and $ B $ ( $ 0<=A,B<=10^{9} $ ), denoting the number of yellow and blue crystals respectively at Grisha's disposal.

The next line contains three integers $ x $ , $ y $ and $ z $ ( $ 0<=x,y,z<=10^{9} $ ) — the respective amounts of yellow, green and blue balls to be obtained.

## 输出格式

Print a single integer — the minimum number of crystals that Grisha should acquire in addition.

## 说明/提示

In the first sample case, Grisha needs five yellow and four blue crystals to create two yellow balls, one green ball, and one blue ball. To do that, Grisha needs to obtain two additional crystals: one yellow and one blue.

## 样例 #1

### 输入

```
4 3
2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 9
1 1 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
12345678 87654321
43043751 1000000000 53798715

```

### 输出

```
2147483648

```

