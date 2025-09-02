---
title: "Levko and Sets"
layout: "post"
diff: 省选/NOI-
pid: CF360D
tag: []
---

# Levko and Sets

## 题目描述

Levko loves all sorts of sets very much.

Levko has two arrays of integers $ a_{1},a_{2},...\ ,a_{n} $ and $ b_{1},b_{2},...\ ,b_{m} $ and a prime number $ p $ . Today he generates $ n $ sets. Let's describe the generation process for the $ i $ -th set:

1. First it has a single number $ 1 $ .
2. Let's take any element $ c $ from this set. For all $ j $ ( $ 1<=j<=m $ ) if number $ (c·a_{i}^{b_{j}}) mod p $ doesn't occur in the set, then add it to the set.
3. Repeat step $ 2 $ as long as we can add at least one element to our set.

Levko wonders, how many numbers belong to at least one set. That is, he wants to know what size is the union of $ n $ generated sets.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ p $ ( $ 1<=n<=10^{4} $ , $ 1<=m<=10^{5} $ , $ 2<=p<=10^{9} $ ), $ p $ is prime.

The second line contains space-separated integers $ a_{1},a_{2},...\ ,a_{n} $ ( $ 1<=a_{i}<p $ ). The third line contains space-separated integers $ b_{1},b_{2},...\ ,b_{m} $ ( $ 1<=b_{i}<=10^{9} $ ).

## 输出格式

The single number — the size of the union of the sets.

## 样例 #1

### 输入

```
1 1 7
2
5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
1 2 7
2
2 4

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2 1 7
1 6
2

```

### 输出

```
1

```

## 样例 #4

### 输入

```
2 1 7
1 6
5

```

### 输出

```
2

```

