---
title: "Devu and Flowers"
layout: "post"
diff: 省选/NOI-
pid: CF451E
tag: ['状态合并', '进制', '容斥原理']
---

# Devu and Flowers

## 题目描述

Devu wants to decorate his garden with flowers. He has purchased $ n $ boxes, where the $ i $ -th box contains $ f_{i} $ flowers. All flowers in a single box are of the same color (hence they are indistinguishable). Also, no two boxes have flowers of the same color.

Now Devu wants to select exactly $ s $ flowers from the boxes to decorate his garden. Devu would like to know, in how many different ways can he select the flowers from each box? Since this number may be very large, he asks you to find the number modulo $ (10^{9}+7) $ .

Devu considers two ways different if there is at least one box from which different number of flowers are selected in these two ways.

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ s $ ( $ 1<=n<=20 $ , $ 0<=s<=10^{14} $ ).

The second line contains $ n $ space-separated integers $ f_{1},f_{2},...\ f_{n} $ ( $ 0<=f_{i}<=10^{12} $ ).

## 输出格式

Output a single integer — the number of ways in which Devu can select the flowers modulo $ (10^{9}+7) $ .

## 说明/提示

Sample 1. There are two ways of selecting $ 3 $ flowers: $ {1,2} $ and $ {0,3} $ .

Sample 2. There is only one way of selecting $ 4 $ flowers: $ {2,2} $ .

Sample 3. There are three ways of selecting $ 5 $ flowers: $ {1,2,2} $ , $ {0,3,2} $ , and $ {1,3,1} $ .

## 样例 #1

### 输入

```
2 3
1 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 4
2 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 5
1 3 2

```

### 输出

```
3

```

