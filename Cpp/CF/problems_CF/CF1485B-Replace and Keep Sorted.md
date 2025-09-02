---
title: "Replace and Keep Sorted"
layout: "post"
diff: 普及-
pid: CF1485B
tag: []
---

# Replace and Keep Sorted

## 题目描述

Given a positive integer $ k $ , two arrays are called $ k $ -similar if:

- they are strictly increasing;
- they have the same length;
- all their elements are positive integers between $ 1 $ and $ k $ (inclusive);
- they differ in exactly one position.

You are given an integer $ k $ , a strictly increasing array $ a $ and $ q $ queries. For each query, you are given two integers $ l_i \leq r_i $ . Your task is to find how many arrays $ b $ exist, such that $ b $ is $ k $ -similar to array $ [a_{l_i},a_{l_i+1}\ldots,a_{r_i}] $ .

## 输入格式

The first line contains three integers $ n $ , $ q $ and $ k $ ( $ 1\leq n, q \leq 10^5 $ , $ n\leq k \leq 10^9 $ ) — the length of array $ a $ , the number of queries and number $ k $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots,a_n $ ( $ 1 \leq a_i \leq k $ ). This array is strictly increasing — $ a_1 < a_2 < \ldots < a_n $ .

Each of the following $ q $ lines contains two integers $ l_i $ , $ r_i $ ( $ 1 \leq l_i \leq r_i \leq n $ ).

## 输出格式

Print $ q $ lines. The $ i $ -th of them should contain the answer to the $ i $ -th query.

## 说明/提示

In the first example:

In the first query there are $ 4 $ arrays that are $ 5 $ -similar to $ [2,4] $ : $ [1,4],[3,4],[2,3],[2,5] $ .

In the second query there are $ 3 $ arrays that are $ 5 $ -similar to $ [4,5] $ : $ [1,5],[2,5],[3,5] $ .

## 样例 #1

### 输入

```
4 2 5
1 2 4 5
2 3
3 4
```

### 输出

```
4
3
```

## 样例 #2

### 输入

```
6 5 10
2 4 6 7 8 9
1 4
1 2
3 5
1 6
5 5
```

### 输出

```
8
9
7
6
9
```

