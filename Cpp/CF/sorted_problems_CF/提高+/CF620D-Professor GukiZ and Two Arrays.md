---
title: "Professor GukiZ and Two Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF620D
tag: []
---

# Professor GukiZ and Two Arrays

## 题目描述

Professor GukiZ has two arrays of integers, a and b. Professor wants to make the sum of the elements in the array a $ s_{a} $ as close as possible to the sum of the elements in the array b $ s_{b} $ . So he wants to minimize the value $ v=|s_{a}-s_{b}| $ .

In one operation professor can swap some element from the array a and some element from the array b. For example if the array a is $ [5,1,3,2,4] $ and the array b is $ [3,3,2] $ professor can swap the element $ 5 $ from the array a and the element $ 2 $ from the array b and get the new array a $ [2,1,3,2,4] $ and the new array b $ [3,3,5] $ .

Professor doesn't want to make more than two swaps. Find the minimal value $ v $ and some sequence of no more than two swaps that will lead to the such value $ v $ . Professor makes swaps one by one, each new swap he makes with the new arrays a and b.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2000 $ ) — the number of elements in the array a.

The second line contains $ n $ integers $ a_{i} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ) — the elements of the array a.

The third line contains integer $ m $ ( $ 1<=m<=2000 $ ) — the number of elements in the array b.

The fourth line contains $ m $ integers $ b_{j} $ ( $ -10^{9}<=b_{j}<=10^{9} $ ) — the elements of the array b.

## 输出格式

In the first line print the minimal value $ v=|s_{a}-s_{b}| $ that can be got with no more than two swaps.

The second line should contain the number of swaps $ k $ ( $ 0<=k<=2 $ ).

Each of the next $ k $ lines should contain two integers $ x_{p},y_{p} $ ( $ 1<=x_{p}<=n,1<=y_{p}<=m $ ) — the index of the element in the array a and the index of the element in the array b in the $ p $ -th swap.

If there are several optimal solutions print any of them. Print the swaps in order the professor did them.

## 样例 #1

### 输入

```
5
5 4 3 2 1
4
1 1 1 1

```

### 输出

```
1
2
1 1
4 2

```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1
15

```

### 输出

```
0
0

```

## 样例 #3

### 输入

```
5
1 2 3 4 5
4
1 2 3 4

```

### 输出

```
1
1
3 1

```

