---
title: "Arranging Crystal Balls"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1740I
tag: []
---

# Arranging Crystal Balls

## 题目描述

In the world of Compfestnesia, Pak Chanek discovers a secret underground dungeon. Inside it, there is a treasure chest that is surrounded by $ n $ statues that are arranged in a circular manner. The statues are numbered from $ 0 $ to $ n-1 $ with statue $ i $ being to the left of statue $ i+1 $ and statue $ n-1 $ being to the left of statue $ 0 $ .

Pak Chanek observes that each statue is holding a crystal ball with an integer between $ 0 $ and $ m-1 $ inclusive. Let's say the integer in the crystal ball of statue $ i $ is $ a_i $ .

The dungeon provides instructions that every integer in the crystal balls must be $ 0 $ in order to open the treasure chest. To achieve that, Pak Chanek is given an integer $ k $ , and he can do zero or more operations. In a single operation, Pak Chanek does the following:

1. Choose exactly $ k $ consecutive statues. In other words, choose the statues $ p, (p+1) \bmod n, (p+2) \bmod n, (p+3) \bmod n, \ldots, (p+k-1) \bmod n $ for some chosen index $ p $ .
2. Do one of the following: 
  - For all chosen statues, change their values of $ a_i $ into $ (a_i+1) \bmod m $ .
  - For all chosen statues, change their values of $ a_i $ into $ (a_i-1) \bmod m $ .

Help Pak Chanek find the minimum possible number of operations to open the treasure chest.

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ k $ ( $ 2 \leq n,m \leq 10^6 $ , $ nm \leq 2 \cdot 10^6 $ , $ 1 \leq k < n $ ) — the number of statues, the bound of the integers in the crystal balls, and the number of statues that can be operated in a single operation.

The second line contains $ n $ integers $ a_0,a_1,\ldots,a_{n-1} $ ( $ 0 \leq a_i < m $ ) — the integers in the crystal balls.

## 输出格式

If it is possible to perform zero or more operations so that $ a_0=a_1=\ldots=a_{n-1}=0 $ , output the minimum number of operations required. Otherwise, output $ -1 $ .

## 说明/提示

In the first example, Pak Chanek can do the following operations:

1. Do the $ a_i := (a_i-1) \bmod m $ operation $ 3 $ times for statues $ 1 $ , $ 2 $ , and $ 3 $ . Now $ a=[8,7,1,2,0] $ .
2. Do the $ a_i := (a_i-1) \bmod m $ operation $ 1 $ time for statues $ 3 $ , $ 4 $ , and $ 0 $ . Now $ a=[7,7,1,1,8] $ .
3. Do the $ a_i := (a_i+1) \bmod m $ operation $ 2 $ times for statues $ 4 $ , $ 0 $ , and $ 1 $ . Now $ a=[0,0,1,1,1] $ .
4. Do the $ a_i := (a_i-1) \bmod m $ operation $ 1 $ time for statues $ 2 $ , $ 3 $ , and $ 4 $ . Now $ a=[0,0,0,0,0] $ .

## 样例 #1

### 输入

```
5 9 3
8 1 4 5 0
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 4 2
1 0 0 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 5 2
1 0 0 0 0
```

### 输出

```
10
```

