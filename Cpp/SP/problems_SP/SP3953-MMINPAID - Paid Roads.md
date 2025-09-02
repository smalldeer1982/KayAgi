---
title: "MMINPAID - Paid Roads"
layout: "post"
diff: 提高+/省选-
pid: SP3953
tag: []
---

# MMINPAID - Paid Roads

## 题目描述

A network of **m** roads connects **N** cities (numbered from 1 to **N**). There may be more than one road connecting one city with another. Some of the roads are paid. There are two ways to pay for travel on a paid road **i** from city **a $ _{i} $**  to city **b $ _{i} $** :

- in advance, in a city **c $ _{i} $**  (which may or may not be the same as **a $ _{i} $** );
- after the travel, in the city **b $ _{i} $** . The payment is **P $ _{i} $**  in the first case and **R $ _{i} $**  in the second case. Write a program to find a minimal-cost route from the city 1 to the city **N**.

## 输入格式

`The first line of the input contains the values of N and m. Each of the following m lines describes one road by specifying the values of ai, bi, ci, Pi, Ri (1 `

## 输出格式

```
The first and only line of the output must contain the minimal possible cost of a trip from the city 1 to the city N. If the trip is not possible for any reason, the line must contain the word 'impossible'.
```

## 样例 #1

### 输入

```
\n
4 5\n1 2 1 10 10\n2 3 1 30 50\n3 4 3 80 80\n2 1 2 10 10\n1 3 2 10 50
```

### 输出

```
\n
110
```

