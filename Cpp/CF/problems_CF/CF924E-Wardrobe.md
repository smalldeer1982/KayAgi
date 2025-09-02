---
title: "Wardrobe"
layout: "post"
diff: 省选/NOI-
pid: CF924E
tag: []
---

# Wardrobe

## 题目描述

Olya wants to buy a custom wardrobe. It should have $ n $ boxes with heights $ a_{1},a_{2},...,a_{n} $ , stacked one on another in some order. In other words, we can represent each box as a vertical segment of length $ a_{i} $ , and all these segments should form a single segment from $ 0 $ to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924E/5093cd7c115b544583c5d55ccc379a13fe72e866.png) without any overlaps.

Some of the boxes are important (in this case $ b_{i}=1 $ ), others are not (then $ b_{i}=0 $ ). Olya defines the convenience of the wardrobe as the number of important boxes such that their bottom edge is located between the heights $ l $ and $ r $ , inclusive.

You are given information about heights of the boxes and their importance. Compute the maximum possible convenience of the wardrobe if you can reorder the boxes arbitrarily.

## 输入格式

The first line contains three integers $ n $ , $ l $ and $ r $ ( $ 1<=n<=10000 $ , $ 0<=l<=r<=10000 $ ) — the number of boxes, the lowest and the highest heights for a bottom edge of an important box to be counted in convenience.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10000 $ ) — the heights of the boxes. It is guaranteed that the sum of height of all boxes (i. e. the height of the wardrobe) does not exceed $ 10000 $ : Olya is not very tall and will not be able to reach any higher.

The second line contains $ n $ integers $ b_{1},b_{2},...,b_{n} $ ( $ 0<=b_{i}<=1 $ ), where $ b_{i} $ equals $ 1 $ if the $ i $ -th box is important, and $ 0 $ otherwise.

## 输出格式

Print a single integer — the maximum possible convenience of the wardrobe.

## 说明/提示

In the first example you can, for example, first put an unimportant box of height $ 2 $ , then put an important boxes of sizes $ 1 $ , $ 3 $ and $ 2 $ , in this order, and then the remaining unimportant boxes. The convenience is equal to $ 2 $ , because the bottom edges of important boxes of sizes $ 3 $ and $ 2 $ fall into the range $ [3,6] $ .

In the second example you have to put the short box under the tall box.

## 样例 #1

### 输入

```
5 3 6
3 2 5 1 2
1 1 0 1 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 2 5
3 6
1 1

```

### 输出

```
1

```

