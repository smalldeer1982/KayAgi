---
title: "Bully Sort"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1830E
tag: []
---

# Bully Sort

## 题目描述

On a permutation $ p $ of length $ n $ , we define a bully swap as follows:

- Let $ i $ be the index of the largest element $ p_i $ such that $ p_i \neq i $ .
- Let $ j $ be the index of the smallest element $ p_j $ such that $ i < j $ .
- Swap $ p_i $ and $ p_j $ .

We define $ f(p) $ as the number of bully swaps we need to perform until $ p $ becomes sorted. Note that if $ p $ is the identity permutation, $ f(p)=0 $ .

You are given $ n $ and a permutation $ p $ of length $ n $ . You need to process the following $ q $ updates.

In each update, you are given two integers $ x $ and $ y $ . You will swap $ p_x $ and $ p_y $ and then find the value of $ f(p) $ .

Note that the updates are persistent. Changes made to the permutation $ p $ will apply when processing future updates.

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 2 \le n \le 5 \cdot 10^5 $ , $ 1 \le q \le 5 \cdot 10^4 $ ) — the length of the permutation and the number of updates.

The second line of input contains $ n $ integer $ p_1,p_2,\ldots,p_n $ ( $ 1 \leq p_i \leq n $ ) — the permutation $ p $ . All elements of $ p $ are distinct.

The $ i $ -th of the next $ q $ lines of input contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i < y_i \le n $ ) — describing the $ i $ -th update.

## 输出格式

After each update, output $ f(p) $ .

## 说明/提示

After the first update, we have $ f(p)=5 $ . The $ 5 $ bully swaps are illustrated below.

- $ [\mathbf{1}, 2, \mathbf{8}, 5, 3, 4, 7, 6] $ ,
- $ [1, 2, \mathbf{3}, 5, \mathbf{8}, 4, 7, 6] $ ,
- $ [1, 2, 3, 5, \mathbf{4}, \mathbf{8}, 7, 6] $ ,
- $ [1, 2, 3, 5, 4, \mathbf{6}, 7, \mathbf{8}] $ ,
- $ [1, 2, 3, \mathbf{4}, \mathbf{5}, 6, 7, 8] $ .

## 样例 #1

### 输入

```
8 5
6 2 1 5 3 4 7 8
1 8
2 3
4 7
7 8
3 6
```

### 输出

```
5
6
9
8
7
```

