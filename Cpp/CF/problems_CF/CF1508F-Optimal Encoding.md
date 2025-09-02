---
title: "Optimal Encoding"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1508F
tag: []
---

# Optimal Encoding

## 题目描述

Touko's favorite sequence of numbers is a permutation $ a_1, a_2, \dots, a_n $ of $ 1, 2, \dots, n $ , and she wants some collection of permutations that are similar to her favorite permutation.

She has a collection of $ q $ intervals of the form $ [l_i, r_i] $ with $ 1 \le l_i \le r_i \le n $ . To create permutations that are similar to her favorite permutation, she coined the following definition:

- A permutation $ b_1, b_2, \dots, b_n $ allows an interval $ [l', r'] $ to holds its shape if for any pair of integers $ (x, y) $ such that $ l' \le x < y \le r' $ , we have $ b_x < b_y $ if and only if $ a_x < a_y $ .
- A permutation $ b_1, b_2, \dots, b_n $ is  $ k $ -similar if $ b $ allows all intervals $ [l_i, r_i] $ for all $ 1 \le i \le k $ to hold their shapes.

Yuu wants to figure out all $ k $ -similar permutations for Touko, but it turns out this is a very hard task; instead, Yuu will encode the set of all $ k $ -similar permutations with directed acylic graphs (DAG). Yuu also coined the following definitions for herself:

- A permutation $ b_1, b_2, \dots, b_n $ satisfies a DAG $ G' $ if for all edge $ u \to v $ in $ G' $ , we must have $ b_u < b_v $ .
- A  $ k $ -encoding is a DAG $ G_k $ on the set of vertices $ 1, 2, \dots, n $ such that a permutation $ b_1, b_2, \dots, b_n $ satisfies $ G_k $ if and only if $ b $ is $ k $ -similar.

Since Yuu is free today, she wants to figure out the minimum number of edges among all $ k $ -encodings for each $ k $ from $ 1 $ to $ q $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 25\,000 $ , $ 1 \le q \le 100\,000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ which form a permutation of $ 1, 2, \dots, n $ .

The $ i $ -th of the following $ q $ lines contains two integers $ l_i $ and $ r_i $ . ( $ 1 \le l_i \le r_i \le n $ ).

## 输出格式

Print $ q $ lines. The $ k $ -th of them should contain a single integer — The minimum number of edges among all $ k $ -encodings.

## 说明/提示

For the first test case:

- All $ 1 $ -similar permutations must allow the interval $ [1, 3] $ to hold its shape. Therefore, the set of all $ 1 $ -similar permutations is $ \{[3, 4, 2, 1], [3, 4, 1, 2], [2, 4, 1, 3], [2, 3, 1, 4]\} $ . The optimal encoding of these permutations is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1508F/85de89b00f0437164d2c51ab0a45d57494c6671b.png)
- All $ 2 $ -similar permutations must allow the intervals $ [1, 3] $ and $ [2, 4] $ to hold their shapes. Therefore, the set of all $ 2 $ -similar permutations is $ \{[3, 4, 1, 2], [2, 4, 1, 3]\} $ . The optimal encoding of these permutations is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1508F/9812f99e6109928593fe56033ff4c0fee9e53ec0.png)
- All $ 3 $ -similar permutations must allow the intervals $ [1, 3] $ , $ [2, 4] $ , and $ [1, 4] $ to hold their shapes. Therefore, the set of all $ 3 $ -similar permutations only includes $ [2, 4, 1, 3] $ . The optimal encoding of this permutation is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1508F/3afffad12ee48608f1c3c75965871674387d3ef4.png)

## 样例 #1

### 输入

```
4 3
2 4 1 3
1 3
2 4
1 4
```

### 输出

```
2
4
3
```

## 样例 #2

### 输入

```
8 4
3 7 4 8 1 5 2 6
3 6
1 6
3 8
1 8
```

### 输出

```
3
5
9
7
```

## 样例 #3

### 输入

```
10 10
10 5 1 2 7 3 9 4 6 8
2 2
4 5
6 8
4 10
4 4
2 7
2 2
7 8
3 7
2 10
```

### 输出

```
0
1
3
6
6
9
9
9
9
8
```

