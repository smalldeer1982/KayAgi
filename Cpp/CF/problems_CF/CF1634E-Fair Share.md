---
title: "Fair Share"
layout: "post"
diff: 省选/NOI-
pid: CF1634E
tag: ['二分图']
---

# Fair Share

## 题目描述

Even a cat has things it can do that AI cannot.

— Fei-Fei Li



You are given $ m $ arrays of positive integers. Each array is of even length.

You need to split all these integers into two equal multisets $ L $ and $ R $ , that is, each element of each array should go into one of two multisets (but not both). Additionally, for each of the $ m $ arrays, exactly half of its elements should go into $ L $ , and the rest should go into $ R $ .

Give an example of such a division or determine that no such division exists.

## 输入格式

The first line contains an integer $ m $ ( $ 1 \le m \le 10 ^ 5 $ ) — the number of arrays.

The next $ 2 \cdot m $ lines contain descriptions of the arrays.

For each array, the first line contains an even integer $ n $ ( $ 2 \le n \le 2 \cdot 10 ^ 5 $ ) — the length of the array. The second line consists of $ n $ space-separated integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10 ^ 9 $ ) — array elements.

It is guaranteed that the sum of $ n $ over all arrays does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

If the answer exists, print "YES", and then print $ m $ lines.

On each line, for each element, print the letter "L" or "R" (capitalized, without spaces), depending on which multiset the element should go into.

If there is no answer, print "NO" on the only line.

## 说明/提示

In the first array, we add the first element to $ R $ and the second to $ L $ . Now $ L = \{2\} $ , and $ R = \{1\} $ .

In the second array, we add the first and third elements to $ L $ and the rest to $ R $ . Now $ L = \{1, 2, 3\} $ and $ R = \{1, 2, 3\} $ .

In the third array, we add elements 2, 3, and 6 to $ L $ , and others — to $ R $ . As a result, $ L = R = \{1, 1, 2, 2, 3, 3\} $ .

## 样例 #1

### 输入

```
3
2
1 2
4
1 2 3 3
6
1 1 2 2 3 3
```

### 输出

```
YES
RL
LRLR
RLLRRL
```

