---
title: "Marvolo Gaunt's Ring"
layout: "post"
diff: 普及/提高-
pid: CF855B
tag: []
---

# Marvolo Gaunt's Ring

## 题目描述

Professor Dumbledore is helping Harry destroy the Horcruxes. He went to Gaunt Shack as he suspected a Horcrux to be present there. He saw Marvolo Gaunt's Ring and identified it as a Horcrux. Although he destroyed it, he is still affected by its curse. Professor Snape is helping Dumbledore remove the curse. For this, he wants to give Dumbledore exactly $ x $ drops of the potion he made.

Value of $ x $ is calculated as maximum of $ p·a_{i}+q·a_{j}+r·a_{k} $ for given $ p,q,r $ and array $ a_{1},a_{2},...\ a_{n} $ such that $ 1<=i<=j<=k<=n $ . Help Snape find the value of $ x $ . Do note that the value of $ x $ may be negative.

## 输入格式

First line of input contains $ 4 $ integers $ n,p,q,r $ ( $ -10^{9}<=p,q,r<=10^{9},1<=n<=10^{5} $ ).

Next line of input contains $ n $ space separated integers $ a_{1},a_{2},...\ a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ).

## 输出格式

Output a single integer the maximum value of $ p·a_{i}+q·a_{j}+r·a_{k} $ that can be obtained provided $ 1<=i<=j<=k<=n $ .

## 说明/提示

In the first sample case, we can take $ i=j=k=5 $ , thus making the answer as $ 1·5+2·5+3·5=30 $ .

In second sample case, selecting $ i=j=1 $ and $ k=5 $ gives the answer $ 12 $ .

## 样例 #1

### 输入

```
5 1 2 3
1 2 3 4 5

```

### 输出

```
30

```

## 样例 #2

### 输入

```
5 1 2 -3
-1 -2 -3 -4 -5

```

### 输出

```
12

```

