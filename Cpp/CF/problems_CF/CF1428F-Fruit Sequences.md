---
title: "Fruit Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF1428F
tag: []
---

# Fruit Sequences

## 题目描述

Zookeeper is buying a carton of fruit to feed his pet wabbit. The fruits are a sequence of apples and oranges, which is represented by a binary string $ s_1s_2\ldots s_n $ of length $ n $ . $ 1 $ represents an apple and $ 0 $ represents an orange.

Since wabbit is allergic to eating oranges, Zookeeper would like to find the longest contiguous sequence of apples. Let $ f(l,r) $ be the longest contiguous sequence of apples in the substring $ s_{l}s_{l+1}\ldots s_{r} $ .

Help Zookeeper find $ \sum_{l=1}^{n} \sum_{r=l}^{n} f(l,r) $ , or the sum of $ f $ across all substrings.

## 输入格式

The first line contains a single integer $ n $ $ (1 \leq n \leq 5 \cdot 10^5) $ .

 The next line contains a binary string $ s $ of length $ n $ $ (s_i \in \{0,1\}) $

## 输出格式

Print a single integer: $ \sum_{l=1}^{n} \sum_{r=l}^{n} f(l,r) $ .

## 说明/提示

In the first test, there are ten substrings. The list of them (we let $ [l,r] $ be the substring $ s_l s_{l+1} \ldots s_r $ ):

- $ [1,1] $ : 0
- $ [1,2] $ : 01
- $ [1,3] $ : 011
- $ [1,4] $ : 0110
- $ [2,2] $ : 1
- $ [2,3] $ : 11
- $ [2,4] $ : 110
- $ [3,3] $ : 1
- $ [3,4] $ : 10
- $ [4,4] $ : 0

The lengths of the longest contiguous sequence of ones in each of these ten substrings are $ 0,1,2,2,1,2,2,1,1,0 $ respectively. Hence, the answer is $ 0+1+2+2+1+2+2+1+1+0 = 12 $ .

## 样例 #1

### 输入

```
4
0110
```

### 输出

```
12
```

## 样例 #2

### 输入

```
7
1101001
```

### 输出

```
30
```

## 样例 #3

### 输入

```
12
011100011100
```

### 输出

```
156
```

