---
title: "Replace the Numbers"
layout: "post"
diff: 普及+/提高
pid: CF1620E
tag: []
---

# Replace the Numbers

## 题目描述

You have an array of integers (initially empty).

You have to perform $ q $ queries. Each query is of one of two types:

- " $ 1 $ $ x $ " — add the element $ x $ to the end of the array;
- " $ 2 $ $ x $ $ y $ " — replace all occurrences of $ x $ in the array with $ y $ .

Find the resulting array after performing all the queries.

## 输入格式

The first line contains a single integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ) — the number of queries.

Next $ q $ lines contain queries (one per line). Each query is of one of two types:

- " $ 1 $ $ x $ " ( $ 1 \le x \le 5 \cdot 10^5 $ );
- " $ 2 $ $ x $ $ y $ " ( $ 1 \le x, y \le 5 \cdot 10^5 $ ).

It's guaranteed that there is at least one query of the first type.

## 输出格式

In a single line, print $ k $ integers — the resulting array after performing all the queries, where $ k $ is the number of queries of the first type.

## 说明/提示

In the first example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [3] $ $ \rightarrow $ $ [3, 1] $ $ \rightarrow $ $ [3, 2] $ $ \rightarrow $ $ [3, 2, 2] $ $ \rightarrow $ $ [3, 2, 2, 1] $ $ \rightarrow $ $ [3, 2, 2, 1, 2] $ $ \rightarrow $ $ [3, 2, 2, 3, 2] $ .

In the second example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 2] $ $ \rightarrow $ $ [1, 2, 1] $ $ \rightarrow $ $ [1, 2, 1] $ .

In the third example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 4] $ $ \rightarrow $ $ [1, 4, 2] $ $ \rightarrow $ $ [1, 4, 4] $ $ \rightarrow $ $ [1, 3, 3] $ $ \rightarrow $ $ [1, 3, 3, 2] $ $ \rightarrow $ $ [1, 3, 3, 7] $ .

## 样例 #1

### 输入

```
7
1 3
1 1
2 1 2
1 2
1 1
1 2
2 1 3
```

### 输出

```
3 2 2 3 2
```

## 样例 #2

### 输入

```
4
1 1
1 2
1 1
2 2 2
```

### 输出

```
1 2 1
```

## 样例 #3

### 输入

```
8
2 1 4
1 1
1 4
1 2
2 2 4
2 4 3
1 2
2 2 7
```

### 输出

```
1 3 3 7
```

