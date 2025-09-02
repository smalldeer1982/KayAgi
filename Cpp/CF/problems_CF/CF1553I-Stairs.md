---
title: "Stairs"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1553I
tag: []
---

# Stairs

## 题目描述

For a permutation $ p $ of numbers $ 1 $ through $ n $ , we define a stair array $ a $ as follows: $ a_i $ is length of the longest segment of permutation which contains position $ i $ and is made of consecutive values in sorted order: $ [x, x+1, \ldots, y-1, y] $ or $ [y, y-1, \ldots, x+1, x] $ for some $ x \leq y $ . For example, for permutation $ p = [4, 1, 2, 3, 7, 6, 5] $ we have $ a = [1, 3, 3, 3, 3, 3, 3] $ .

You are given the stair array $ a $ . Your task is to calculate the number of permutations which have stair array equal to $ a $ . Since the number can be big, compute it modulo $ 998\,244\,353 $ . Note that this number can be equal to zero.

## 输入格式

The first line of input contains integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of a stair array $ a $ .

The second line of input contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ).

## 输出格式

Print the number of permutations which have stair array equal to $ a $ . Since the number can be big, compute it modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
6
3 3 3 1 1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7
4 4 4 4 3 3 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
1
1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
8
2 2 2 2 2 2 1 1
```

### 输出

```
370
```

## 样例 #5

### 输入

```
4
3 2 3 1
```

### 输出

```
0
```

