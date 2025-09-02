---
title: "Maximum of Maximums of Minimums"
layout: "post"
diff: 普及-
pid: CF870B
tag: []
---

# Maximum of Maximums of Minimums

## 题目描述

You are given an array $ a_{1},a_{2},...,a_{n} $ consisting of $ n $ integers, and an integer $ k $ . You have to split the array into exactly $ k $ non-empty subsegments. You'll then compute the minimum integer on each subsegment, and take the maximum integer over the $ k $ obtained minimums. What is the maximum possible integer you can get?

Definitions of subsegment and array splitting are given in notes.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=10^{5} $ ) — the size of the array $ a $ and the number of subsegments you have to split the array to.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ).

## 输出格式

Print single integer — the maximum possible integer you can get if you split the array into $ k $ non-empty subsegments and take maximum of minimums on the subsegments.

## 说明/提示

A subsegment $ [l,r] $ ( $ l<=r $ ) of array $ a $ is the sequence $ a_{l},a_{l+1},...,a_{r} $ .

Splitting of array $ a $ of $ n $ elements into $ k $ subsegments $ [l_{1},r_{1}] $ , $ [l_{2},r_{2}] $ , ..., $ [l_{k},r_{k}] $ ( $ l_{1}=1 $ , $ r_{k}=n $ , $ l_{i}=r_{i-1}+1 $ for all $ i>1 $ ) is $ k $ sequences $ (a_{l1},...,a_{r1}),...,(a_{lk},...,a_{rk}) $ .

In the first example you should split the array into subsegments $ [1,4] $ and $ [5,5] $ that results in sequences $ (1,2,3,4) $ and $ (5) $ . The minimums are $ min(1,2,3,4)=1 $ and $ min(5)=5 $ . The resulting maximum is $ max(1,5)=5 $ . It is obvious that you can't reach greater result.

In the second example the only option you have is to split the array into one subsegment $ [1,5] $ , that results in one sequence $ (-4,-5,-3,-2,-1) $ . The only minimum is $ min(-4,-5,-3,-2,-1)=-5 $ . The resulting maximum is $ -5 $ .

## 样例 #1

### 输入

```
5 2
1 2 3 4 5

```

### 输出

```
5

```

## 样例 #2

### 输入

```
5 1
-4 -5 -3 -2 -1

```

### 输出

```
-5

```

