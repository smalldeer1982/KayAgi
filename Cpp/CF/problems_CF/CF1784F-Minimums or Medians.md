---
title: "Minimums or Medians"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1784F
tag: []
---

# Minimums or Medians

## 题目描述

Vika has a set of all consecutive positive integers from $ 1 $ to $ 2n $ , inclusive.

Exactly $ k $ times Vika will choose and perform one of the following two actions:

- take two smallest integers from her current set and remove them;
- take two median integers from her current set and remove them.

Recall that medians are the integers located exactly in the middle of the set if you write down its elements in increasing order. Note that Vika's set always has an even size, thus the pair of median integers is uniquely defined. For example, two median integers of the set $ \{1, 5, 6, 10, 15, 16, 18, 23\} $ are $ 10 $ and $ 15 $ .

How many different sets can Vika obtain in the end, after $ k $ actions? Print this number modulo $ 998\,244\,353 $ . Two sets are considered different if some integer belongs to one of them but not to the other.

## 输入格式

The only line contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 10^6 $ ).

## 输出格式

Print a single integer — the number of sets Vika can obtain in the end, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, Vika's initial set is $ \{1, 2, 3, 4, 5, 6\} $ . She can remove the minimums from it to obtain $ \{3, 4, 5, 6\} $ , or she can remove the medians from it to obtain $ \{1, 2, 5, 6\} $ .

In the second example, Vika can obtain $ \{1, 6\} $ , $ \{3, 6\} $ , or $ \{5, 6\} $ . For instance, Vika can obtain $ \{3, 6\} $ if she removes two smallest integers first ( $ \{1, 2, 3, 4, 5, 6\} \rightarrow \{3, 4, 5, 6\} $ ), and then she removes two median integers ( $ \{3, 4, 5, 6\} \rightarrow \{3, 6\} $ ).

In the third example, regardless of Vika's choices, she'll end up with an empty set.

## 样例 #1

### 输入

```
3 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
```

### 输出

```
1
```

## 样例 #4

### 输入

```
7 4
```

### 输出

```
11
```

## 样例 #5

### 输入

```
23 8
```

### 输出

```
88
```

## 样例 #6

### 输入

```
100 77
```

### 输出

```
825430474
```

