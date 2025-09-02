---
title: "Vlad and the Nice Paths (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1811G2
tag: []
---

# Vlad and the Nice Paths (hard version)

## 题目描述

This is hard version of the problem, it differs from the easy one only by constraints on $ n $ and $ k $ .

Vlad found a row of $ n $ tiles and the integer $ k $ . The tiles are indexed from left to right and the $ i $ -th tile has the color $ c_i $ . After a little thought, he decided what to do with it.

You can start from any tile and jump to any number of tiles right, forming the path $ p $ . Let's call the path $ p $ of length $ m $ nice if:

- $ p $ can be divided into blocks of length exactly $ k $ , that is, $ m $ is divisible by $ k $ ;
- $ c_{p_1} = c_{p_2} = \ldots = c_{p_k} $ ;
- $ c_{p_{k+1}} = c_{p_{k+2}} = \ldots = c_{p_{2k}} $ ;
- $ \ldots $
- $ c_{p_{m-k+1}} = c_{p_{m-k+2}} = \ldots = c_{p_{m}} $ ;

Your task is to find the number of nice paths of maximum length. Since this number may be too large, print it modulo $ 10^9 + 7 $ .

## 输入格式

The first line of each test contains the integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 5000 $ ) — the number of tiles in a row and the length of the block.

The second line of each test case contains $ n $ integers $ c_1, c_2, c_3, \dots, c_n $ ( $ 1 \le c_i \le n $ ) — tile colors.

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 25 \cdot 10^6 $ .

## 输出格式

Print $ t $ numbers, each of which is the answer to the corresponding test case — the number of nice paths of maximum length modulo $ 10^9 + 7 $ .

## 说明/提示

In the first sample, it is impossible to make a nice path with a length greater than $ 0 $ .

In the second sample, we are interested in the following paths:

- $ 1 \rightarrow 3 \rightarrow 4 \rightarrow 5 $
- $ 2 \rightarrow 4 \rightarrow 5 \rightarrow 7 $
- $ 1 \rightarrow 3 \rightarrow 5 \rightarrow 7 $
- $ 1 \rightarrow 3 \rightarrow 4 \rightarrow 7 $

In the third example, any path of length $ 8 $ is nice.

## 样例 #1

### 输入

```
5
5 2
1 2 3 4 5
7 2
1 3 1 3 3 1 3
11 4
1 1 1 1 1 1 1 1 1 1 1
5 2
1 1 2 2 2
5 1
1 2 3 4 5
```

### 输出

```
1
4
165
3
1
```

