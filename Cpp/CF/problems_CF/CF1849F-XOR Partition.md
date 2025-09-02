---
title: "XOR Partition"
layout: "post"
diff: 省选/NOI-
pid: CF1849F
tag: []
---

# XOR Partition

## 题目描述

For a set of integers $ S $ , let's define its cost as the minimum value of $ x \oplus y $ among all pairs of different integers from the set (here, $ \oplus $ denotes bitwise XOR). If there are less than two elements in the set, its cost is equal to $ 2^{30} $ .

You are given a set of integers $ \{a_1, a_2, \dots, a_n\} $ . You have to partition it into two sets $ S_1 $ and $ S_2 $ in such a way that every element of the given set belongs to exactly one of these two sets. The value of the partition is the minimum among the costs of $ S_1 $ and $ S_2 $ .

Find the partition with the maximum possible value.

## 输入格式

The first line contains $ n $ ( $ 2 \le n \le 200000 $ ) — the number of elements in the set.

The second line contains $ n $ distinct integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 0 \le a_i < 2^{30} $ ) — the elements of the set.

## 输出格式

Print a string $ n $ characters 0 and/or 1 describing the partition as follows: the $ i $ -th character should be 0 if the element $ a_i $ belongs to $ S_1 $ , otherwise, that character should be 1.

If there are multiple optimal answers, print any of them.

## 样例 #1

### 输入

```
5
42 13 1337 37 152
```

### 输出

```
10001
```

## 样例 #2

### 输入

```
4
1 2 3 4
```

### 输出

```
1100
```

## 样例 #3

### 输入

```
2
1 2
```

### 输出

```
10
```

## 样例 #4

### 输入

```
8
7 6 5 4 3 2 1 0
```

### 输出

```
10010110
```

