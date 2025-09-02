---
title: "Mike and code of a permutation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF798E
tag: []
---

# Mike and code of a permutation

## 题目描述

Mike has discovered a new way to encode permutations. If he has a permutation $ P=[p_{1},p_{2},...,p_{n}] $ , he will encode it in the following way:

Denote by $ A=[a_{1},a_{2},...,a_{n}] $ a sequence of length $ n $ which will represent the code of the permutation. For each $ i $ from $ 1 $ to $ n $ sequentially, he will choose the smallest unmarked $ j $ ( $ 1<=j<=n $ ) such that $ p_{i}&lt;p_{j} $ and will assign to $ a_{i} $ the number $ j $ (in other words he performs $ a_{i}=j $ ) and will mark $ j $ . If there is no such $ j $ , he'll assign to $ a_{i} $ the number $ -1 $ (he performs $ a_{i}=-1 $ ).

Mike forgot his original permutation but he remembers its code. Your task is simple: find any permutation such that its code is the same as the code of Mike's original permutation.

You may assume that there will always be at least one valid permutation.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=500000 $ ) — length of permutation.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ or $ a_{i}=-1 $ ) — the code of Mike's permutation.

You may assume that all positive values from $ A $ are different.

## 输出格式

In first and only line print $ n $ numbers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — a permutation $ P $ which has the same code as the given one. Note that numbers in permutation are distinct.

## 说明/提示

For the permutation from the first example:

 $ i=1 $ , the smallest $ j $ is $ 2 $ because $ p_{2}=6&gt;p_{1}=2 $ .

 $ i=2 $ , there is no $ j $ because $ p_{2}=6 $ is the greatest element in the permutation.

 $ i=3 $ , the smallest $ j $ is $ 1 $ because $ p_{1}=2&gt;p_{3}=1 $ .

 $ i=4 $ , the smallest $ j $ is $ 5 $ ( $ 2 $ was already marked) because $ p_{5}=5&gt;p_{4}=4 $ .

 $ i=5 $ , there is no $ j $ because $ 2 $ is already marked.

 $ i=6 $ , the smallest $ j $ is $ 4 $ because $ p_{4}=4&gt;p_{6}=3 $ .

## 样例 #1

### 输入

```
6
2 -1 1 5 -1 4

```

### 输出

```
2 6 1 4 5 3

```

## 样例 #2

### 输入

```
8
2 -1 4 -1 6 -1 8 -1

```

### 输出

```
1 8 2 7 3 6 4 5

```

