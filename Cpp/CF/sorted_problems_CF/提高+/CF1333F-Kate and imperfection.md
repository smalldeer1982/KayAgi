---
title: "Kate and imperfection"
layout: "post"
diff: 提高+/省选-
pid: CF1333F
tag: []
---

# Kate and imperfection

## 题目描述

Kate has a set $ S $ of $ n $ integers $ \{1, \dots, n\}  $ .

She thinks that imperfection of a subset $ M \subseteq S $ is equal to the maximum of $ gcd(a, b) $ over all pairs $ (a, b) $ such that both $ a $ and $ b $ are in $ M $ and $ a \neq b $ .

Kate is a very neat girl and for each $ k \in \{2, \dots, n\} $ she wants to find a subset that has the smallest imperfection among all subsets in $ S $ of size $ k $ . There can be more than one subset with the smallest imperfection and the same size, but you don't need to worry about it. Kate wants to find all the subsets herself, but she needs your help to find the smallest possible imperfection for each size $ k $ , will name it $ I_k $ .

Please, help Kate to find $ I_2 $ , $ I_3 $ , ..., $ I_n $ .

## 输入格式

The first and only line in the input consists of only one integer $ n $ ( $ 2\le n \le 5 \cdot 10^5 $ ) — the size of the given set $ S $ .

## 输出格式

Output contains only one line that includes $ n - 1 $ integers: $ I_2 $ , $ I_3 $ , ..., $ I_n $ .

## 说明/提示

First sample: answer is 1, because $ gcd(1, 2) = 1 $ .

Second sample: there are subsets of $ S $ with sizes $ 2, 3 $ with imperfection equal to 1. For example, $ \{2,3\} $ and $ \{1, 2, 3\} $ .

## 样例 #1

### 输入

```
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
1 1
```

