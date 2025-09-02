---
title: "Levko and Permutation"
layout: "post"
diff: 普及/提高-
pid: CF361B
tag: []
---

# Levko and Permutation

## 题目描述

Levko loves permutations very much. A permutation of length $ n $ is a sequence of distinct positive integers, each is at most $ n $ .

Let’s assume that value $ gcd(a,b) $ shows the greatest common divisor of numbers $ a $ and $ b $ . Levko assumes that element $ p_{i} $ of permutation $ p_{1},p_{2},...\ ,p_{n} $ is good if $ gcd(i,p_{i})&gt;1 $ . Levko considers a permutation beautiful, if it has exactly $ k $ good elements. Unfortunately, he doesn’t know any beautiful permutation. Your task is to help him to find at least one of them.

## 输入格式

The single line contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{5} $ , $ 0<=k<=n $ ).

## 输出格式

In a single line print either any beautiful permutation or -1, if such permutation doesn’t exist.

If there are multiple suitable permutations, you are allowed to print any of them.

## 说明/提示

In the first sample elements $ 4 $ and $ 3 $ are good because $ gcd(2,4)=2&gt;1 $ and $ gcd(3,3)=3&gt;1 $ . Elements $ 2 $ and $ 1 $ are not good because $ gcd(1,2)=1 $ and $ gcd(4,1)=1 $ . As there are exactly 2 good elements, the permutation is beautiful.

The second sample has no beautiful permutations.

## 样例 #1

### 输入

```
4 2

```

### 输出

```
2 4 3 1
```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
-1

```

