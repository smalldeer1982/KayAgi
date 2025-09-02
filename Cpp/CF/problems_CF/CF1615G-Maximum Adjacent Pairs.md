---
title: "Maximum Adjacent Pairs"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1615G
tag: []
---

# Maximum Adjacent Pairs

## 题目描述

You are given an array $ a $ consisting of $ n $ non-negative integers.

You have to replace each $ 0 $ in $ a $ with an integer from $ 1 $ to $ n $ (different elements equal to $ 0 $ can be replaced by different integers).

The value of the array you obtain is the number of integers $ k $ from $ 1 $ to $ n $ such that the following condition holds: there exist a pair of adjacent elements equal to $ k $ (i. e. there exists some $ i \in [1, n - 1] $ such that $ a_i = a_{i + 1} = k $ ). If there are multiple such pairs for some integer $ k $ , this integer is counted in the value only once.

Your task is to obtain the array with the maximum possible value.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 3 \cdot 10^5 $ ) — the number of elements in the array.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le \min(n, 600) $ ) — the elements of the array.

## 输出格式

Print $ n $ integers not less than $ 1 $ and not greater than $ n $ — the array with the maximum possible value you can obtain.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4
1 1 0 2
```

### 输出

```
1 1 2 2
```

## 样例 #2

### 输入

```
5
0 0 0 0 0
```

### 输出

```
3 1 1 3 3
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1 2 3 4 5
```

## 样例 #4

### 输入

```
6
1 0 0 0 0 1
```

### 输出

```
1 2 3 3 1 1
```

## 样例 #5

### 输入

```
3
3 0 2
```

### 输出

```
3 2 2
```

## 样例 #6

### 输入

```
5
1 0 2 0 1
```

### 输出

```
1 2 2 1 1
```

## 样例 #7

### 输入

```
7
1 0 2 3 1 0 2
```

### 输出

```
1 2 2 3 1 1 2
```

