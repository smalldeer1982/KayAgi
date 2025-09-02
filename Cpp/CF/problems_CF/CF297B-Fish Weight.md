---
title: "Fish Weight"
layout: "post"
diff: 普及/提高-
pid: CF297B
tag: []
---

# Fish Weight

## 题目描述

It is known that there are $ k $ fish species in the polar ocean, numbered from $ 1 $ to $ k $ . They are sorted by non-decreasing order of their weight, which is a positive number. Let the weight of the $ i $ -th type of fish be $ w_{i} $ , then $ 0&lt;w_{1}<=w_{2}<=...<=w_{k} $ holds.

Polar bears Alice and Bob each have caught some fish, and they are guessing who has the larger sum of weight of the fish he/she's caught. Given the type of the fish they've caught, determine whether it is possible that the fish caught by Alice has a strictly larger total weight than Bob's. In other words, does there exist a sequence of weights $ w_{i} $ (not necessary integers), such that the fish caught by Alice has a strictly larger total weight?

## 输入格式

The first line contains three integers $ n,m,k $ $ (1<=n,m<=10^{5},1<=k<=10^{9}) $ — the number of fish caught by Alice and Bob respectively, and the number of fish species.

The second line contains $ n $ integers each from 1 to $ k $ , the list of fish type caught by Alice. The third line contains $ m $ integers each from 1 to $ k $ , the list of fish type caught by Bob.

Note that one may have caught more than one fish for a same species.

## 输出格式

Output "YES" (without quotes) if it is possible, and "NO" (without quotes) otherwise.

## 说明/提示

In the first sample, if $ w_{1}=1,w_{2}=2,w_{3}=2.5 $ , then Alice has a total of $ 2+2+2=6 $ weight units, while Bob only has $ 1+1+2.5=4.5 $ .

In the second sample, the fish that Alice caught is a subset of Bob's. Therefore, the total weight of Bob’s fish is always not less than the total weight of Alice’s fish.

## 样例 #1

### 输入

```
3 3 3
2 2 2
1 1 3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4 7 9
5 2 7 3
3 5 2 7 3 8 7

```

### 输出

```
NO

```

