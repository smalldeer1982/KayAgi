---
title: "Another Sorting Problem"
layout: "post"
diff: 入门
pid: CF1575A
tag: []
---

# Another Sorting Problem

## 题目描述

Andi and Budi were given an assignment to tidy up their bookshelf of $ n $ books. Each book is represented by the book title — a string $ s_i $ numbered from $ 1 $ to $ n $ , each with length $ m $ . Andi really wants to sort the book lexicographically ascending, while Budi wants to sort it lexicographically descending.

Settling their fight, they decided to combine their idea and sort it asc-desc-endingly, where the odd-indexed characters will be compared ascendingly, and the even-indexed characters will be compared descendingly.

A string $ a $ occurs before a string $ b $ in asc-desc-ending order if and only if in the first position where $ a $ and $ b $ differ, the following holds:

- if it is an odd position, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ ;
- if it is an even position, the string $ a $ has a letter that appears later in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n \cdot m \leq 10^6 $ ).

The $ i $ -th of the next $ n $ lines contains a string $ s_i $ consisting of $ m $ uppercase Latin letters — the book title. The strings are pairwise distinct.

## 输出格式

Output $ n $ integers — the indices of the strings after they are sorted asc-desc-endingly.

## 说明/提示

The following illustrates the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575A/4fc97fb21b092b67b618bea3a13d2dd3dee136ca.png)

## 样例 #1

### 输入

```
5 2
AA
AB
BB
BA
AZ
```

### 输出

```
5 2 1 3 4
```

