---
title: "Carry Bit"
layout: "post"
diff: 提高+/省选-
pid: CF1761D
tag: []
---

# Carry Bit

## 题目描述

Let $ f(x,y) $ be the number of carries of $ x+y $ in binary (i. e. $ f(x,y)=g(x)+g(y)-g(x+y) $ , where $ g(x) $ is the number of ones in the binary representation of $ x $ ).

Given two integers $ n $ and $ k $ , find the number of ordered pairs $ (a,b) $ such that $ 0 \leq a,b < 2^n $ , and $ f(a,b) $ equals $ k $ . Note that for $ a\ne b $ , $ (a,b) $ and $ (b,a) $ are considered as two different pairs.

As this number may be large, output it modulo $ 10^9+7 $ .

## 输入格式

The only line of each test contains two integers $ n $ and $ k $ ( $ 0\leq k<n\leq 10^6 $ ).

## 输出格式

Output a single integer — the answer modulo $ 10^9+7 $ .

## 说明/提示

Here are some examples for understanding carries:

$$ \begin{aligned} &\begin{array}{r} 1_{\ \ }1_{\ \ }1\\ +\ _{1}1_{\ \ }0_{\ \ }0\\ \hline \ 1_{\ \ }0_{\ \ }1_{\ \ }1 \end{array} &\begin{array}{r} \ 1_{\ \ }0_{\ \ }1\\ +\ _{\ \ }0_{\ \ }0_{1}1\\ \hline \ 0_{\ \ }1_{\ \ }1_{\ \ }0 \end{array} & &\begin{array}{r} \ 1_{\ \ }0_{\ \ }1\\ +\ _{1}0_{1}1_{1}1\\ \hline \ 1_{\ \ }0_{\ \ }0_{\ \ }0 \end{array} \end{aligned}  $$ 

So  $ f(7,4)=1 $ ,  $ f(5,1)=1 $  and  $ f(5,3)=3 $ .

In the first test case, all the pairs meeting the constraints are  $ (1,1),(1,5),(2,2),(2,3),(3,2),(4,4),(4,5),(4,6),(4,7),(5,1),(5,4),(5,6),(6,4),(6,5),(7,4)$.

## 样例 #1

### 输入

```
3 1
```

### 输出

```
15
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
27
```

## 样例 #3

### 输入

```
998 244
```

### 输出

```
573035660
```

