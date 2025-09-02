---
title: "Mister B and PR Shifts"
layout: "post"
diff: 普及+/提高
pid: CF819B
tag: []
---

# Mister B and PR Shifts

## 题目描述

Some time ago Mister B detected a strange signal from the space, which he started to study.

After some transformation the signal turned out to be a permutation $ p $ of length $ n $ or its cyclic shift. For the further investigation Mister B need some basis, that's why he decided to choose cyclic shift of this permutation which has the minimum possible deviation.

Let's define the deviation of a permutation $ p $ as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF819B/47275887a8ad3386063ea864423569d3d609b7f9.png).

Find a cyclic shift of permutation $ p $ with minimum possible deviation. If there are multiple solutions, print any of them.

Let's denote id $ k $ ( $ 0<=k&lt;n $ ) of a cyclic shift of permutation $ p $ as the number of right shifts needed to reach this shift, for example:

- $ k=0 $ : shift $ p_{1},p_{2},...\ p_{n} $ ,
- $ k=1 $ : shift $ p_{n},p_{1},...\ p_{n-1} $ ,
- ...,
- $ k=n-1 $ : shift $ p_{2},p_{3},...\ p_{n},p_{1} $ .

## 输入格式

First line contains single integer $ n $ ( $ 2<=n<=10^{6} $ ) — the length of the permutation.

The second line contains $ n $ space-separated integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the elements of the permutation. It is guaranteed that all elements are distinct.

## 输出格式

Print two integers: the minimum deviation of cyclic shifts of permutation $ p $ and the id of such shift. If there are multiple solutions, print any of them.

## 说明/提示

In the first sample test the given permutation $ p $ is the identity permutation, that's why its deviation equals to $ 0 $ , the shift id equals to $ 0 $ as well.

In the second sample test the deviation of $ p $ equals to $ 4 $ , the deviation of the $ 1 $ -st cyclic shift $ (1,2,3) $ equals to $ 0 $ , the deviation of the $ 2 $ -nd cyclic shift $ (3,1,2) $ equals to $ 4 $ , the optimal is the $ 1 $ -st cyclic shift.

In the third sample test the deviation of $ p $ equals to $ 4 $ , the deviation of the $ 1 $ -st cyclic shift $ (1,3,2) $ equals to $ 2 $ , the deviation of the $ 2 $ -nd cyclic shift $ (2,1,3) $ also equals to $ 2 $ , so the optimal are both $ 1 $ -st and $ 2 $ -nd cyclic shifts.

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
0 0

```

## 样例 #2

### 输入

```
3
2 3 1

```

### 输出

```
0 1

```

## 样例 #3

### 输入

```
3
3 2 1

```

### 输出

```
2 1

```

