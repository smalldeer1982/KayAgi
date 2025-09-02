---
title: "Different Differences"
layout: "post"
diff: 普及-
pid: CF1772C
tag: []
---

# Different Differences

## 题目描述

An array $ a $ consisting of $ k $ integers is strictly increasing if $ a_1 < a_2 < \dots < a_k $ . For example, the arrays $ [1, 3, 5] $ , $ [1, 2, 3, 4] $ , $ [3, 5, 6] $ are strictly increasing; the arrays $ [2, 2] $ , $ [3, 7, 5] $ , $ [7, 4, 3] $ , $ [1, 2, 2, 3] $ are not.

For a strictly increasing array $ a $ of $ k $ elements, let's denote the characteristic as the number of different elements in the array $ [a_2 - a_1, a_3 - a_2, \dots, a_k - a_{k-1}] $ . For example, the characteristic of the array $ [1, 3, 4, 7, 8] $ is $ 3 $ since the array $ [2, 1, 3, 1] $ contains $ 3 $ different elements: $ 2 $ , $ 1 $ and $ 3 $ .

You are given two integers $ k $ and $ n $ ( $ k \le n $ ). Construct an increasing array of $ k $ integers from $ 1 $ to $ n $ with maximum possible characteristic.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 819 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ k $ and $ n $ ( $ 2 \le k \le n \le 40 $ ).

## 输出格式

For each test case, print $ k $ integers — the elements of the strictly increasing array $ a $ with the maximum possible characteristic. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
7
5 9
4 12
3 3
3 4
4 4
4 6
8 11
```

### 输出

```
1 3 4 7 8
2 4 7 12
1 2 3
1 3 4
1 2 3 4
2 4 5 6
1 2 3 5 6 7 8 11
```

