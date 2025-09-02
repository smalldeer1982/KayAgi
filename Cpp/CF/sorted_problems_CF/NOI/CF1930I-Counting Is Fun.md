---
title: "Counting Is Fun"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1930I
tag: []
---

# Counting Is Fun

## 题目描述

You are given a binary $ ^\dagger $ pattern $ p $ of length $ n $ .

A binary string $ q $ of the same length $ n $ is called good if for every $ i $ ( $ 1 \leq i \leq n $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq n $ , and
- $ p_i $ is a mode $ ^\ddagger $ of the string $ q_lq_{l+1}\ldots q_r $ .

Count the number of good binary strings modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A binary string is a string that only consists of characters $ \mathtt{0} $ and $ \mathtt{1} $ .

 $ ^\ddagger $ Character $ c $ is a mode of string $ t $ of length $ m $ if the number of occurrences of $ c $ in $ t $ is at least $ \lceil \frac{m}{2} \rceil $ . For example, $ \mathtt{0} $ is a mode of $ \mathtt{010} $ , $ \mathtt{1} $ is not a mode of $ \mathtt{010} $ , and both $ \mathtt{0} $ and $ \mathtt{1} $ are modes of $ \mathtt{011010} $ .

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the binary string $ p $ .

The second line of input contains a binary string $ p $ of length $ n $ consisting of characters 0 and 1.

## 输出格式

Output the number of good strings modulo $ 998\,244\,353 $ .

## 说明/提示

In the second example, the good strings are

- $ \mathtt{010} $ ;
- $ \mathtt{011} $ ;
- $ \mathtt{101} $ ;
- $ \mathtt{110} $ ;
- $ \mathtt{111} $ .

## 样例 #1

### 输入

```
1
0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
111
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4
1011
```

### 输出

```
9
```

## 样例 #4

### 输入

```
6
110001
```

### 输出

```
36
```

## 样例 #5

### 输入

```
12
111010001111
```

### 输出

```
2441
```

