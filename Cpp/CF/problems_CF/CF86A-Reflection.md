---
title: "Reflection"
layout: "post"
diff: 普及/提高-
pid: CF86A
tag: ['数学']
---

# Reflection

## 题目描述

For each positive integer $ n $ consider the integer $ ψ(n) $ which is obtained from $ n $ by replacing every digit $ a $ in the decimal notation of $ n $ with the digit $ (9-a) $ . We say that $ ψ(n) $ is the reflection of $ n $ . For example, reflection of $ 192 $ equals $ 807 $ . Note that leading zeros (if any) should be omitted. So reflection of $ 9 $ equals $ 0 $ , reflection of $ 91 $ equals $ 8 $ .

Let us call the weight of the number the product of the number and its reflection. Thus, the weight of the number $ 10 $ is equal to $ 10·89=890 $ .

Your task is to find the maximum weight of the numbers in the given range $ [l,r] $ (boundaries are included).

## 输入格式

Input contains two space-separated integers $ l $ and $ r $ ( $ 1<=l<=r<=10^{9} $ ) — bounds of the range.

## 输出格式

Output should contain single integer number: maximum value of the product $ n·ψ(n) $ , where $ l<=n<=r $ .

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preferred to use cout (also you may use %I64d).

## 说明/提示

In the third sample weight of $ 8 $ equals $ 8·1=8 $ , weight of $ 9 $ equals $ 9·0=0 $ , weight of $ 10 $ equals $ 890 $ .

Thus, maximum value of the product is equal to $ 890 $ .

## 样例 #1

### 输入

```
3 7

```

### 输出

```
20
```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
8
```

## 样例 #3

### 输入

```
8 10

```

### 输出

```
890
```

