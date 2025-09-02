---
title: "Cyclic Cipher"
layout: "post"
diff: 省选/NOI-
pid: CF722F
tag: []
---

# Cyclic Cipher

## 题目描述

You are given $ n $ sequences. Each sequence consists of positive integers, not exceeding $ m $ . All integers in one sequence are distinct, but the same integer may appear in multiple sequences. The length of the $ i $ -th sequence is $ k_{i} $ .

Each second integers in each of the sequences are shifted by one to the left, i.e. integers at positions $ i&gt;1 $ go to positions $ i-1 $ , while the first integers becomes the last.

Each second we take the first integer of each sequence and write it down to a new array. Then, for each value $ x $ from $ 1 $ to $ m $ we compute the longest segment of the array consisting of element $ x $ only.

The above operation is performed for $ 10^{100} $ seconds. For each integer from $ 1 $ to $ m $ find out the longest segment found at this time.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=100000 $ ) — the number of sequences and the maximum integer that can appear in the sequences.

Then follow $ n $ lines providing the sequences. Each of them starts with an integer $ k_{i} $ ( $ 1<=k_{i}<=40 $ ) — the number of integers in the sequence, proceeded by $ k_{i} $ positive integers — elements of the sequence. It's guaranteed that all integers in each sequence are pairwise distinct and do not exceed $ m $ .

The total length of all sequences doesn't exceed $ 200000 $ .

## 输出格式

Print $ m $ integers, the $ i $ -th of them should be equal to the length of the longest segment of the array with all its values equal to $ i $ during the first $ 10^{100} $ seconds.

## 样例 #1

### 输入

```
3 4
3 3 4 1
4 1 3 4 2
3 3 1 4

```

### 输出

```
2
1
3
2

```

## 样例 #2

### 输入

```
5 5
2 3 1
4 5 1 3 2
4 2 1 3 5
1 3
2 5 3

```

### 输出

```
3
1
4
0
1

```

## 样例 #3

### 输入

```
4 6
3 4 5 3
2 6 3
2 3 6
3 3 6 5

```

### 输出

```
0
0
2
1
1
2

```

