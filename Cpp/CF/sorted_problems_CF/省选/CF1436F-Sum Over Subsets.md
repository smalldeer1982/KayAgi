---
title: "Sum Over Subsets"
layout: "post"
diff: 省选/NOI-
pid: CF1436F
tag: []
---

# Sum Over Subsets

## 题目描述

You are given a multiset $ S $ . Over all pairs of subsets $ A $ and $ B $ , such that:

- $ B \subset A $ ;
- $ |B| = |A| - 1 $ ;
- greatest common divisor of all elements in $ A $ is equal to one;

find the sum of $ \sum_{x \in A}{x} \cdot \sum_{x \in B}{x} $ , modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains one integer $ m $ ( $ 1 \le m \le 10^5 $ ): the number of different values in the multiset $ S $ .

Each of the next $ m $ lines contains two integers $ a_i $ , $ freq_i $ ( $ 1 \le a_i \le 10^5, 1 \le freq_i \le 10^9 $ ). Element $ a_i $ appears in the multiset $ S $ $ freq_i $ times. All $ a_i $ are different.

## 输出格式

Print the required sum, modulo $ 998\,244\,353 $ .

## 说明/提示

A multiset is a set where elements are allowed to coincide. $ |X| $ is the cardinality of a set $ X $ , the number of elements in it.

 $ A \subset B $ : Set $ A $ is a subset of a set $ B $ .

In the first example $ B=\{1\}, A=\{1,2\} $ and $ B=\{2\}, A=\{1, 2\} $ have a product equal to $ 1\cdot3 + 2\cdot3=9 $ . Other pairs of $ A $ and $ B $ don't satisfy the given constraints.

## 样例 #1

### 输入

```
2
1 1
2 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4
1 1
2 1
3 1
6 1
```

### 输出

```
1207
```

## 样例 #3

### 输入

```
1
1 5
```

### 输出

```
560
```

