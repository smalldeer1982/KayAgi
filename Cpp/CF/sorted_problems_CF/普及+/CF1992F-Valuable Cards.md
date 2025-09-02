---
title: "Valuable Cards"
layout: "post"
diff: 普及+/提高
pid: CF1992F
tag: ['贪心', '数论']
---

# Valuable Cards

## 题目描述

In his favorite cafe Kmes once again wanted to try the herring under a fur coat. Previously, it would not have been difficult for him to do this, but the cafe recently introduced a new purchasing policy.

Now, in order to make a purchase, Kmes needs to solve the following problem: $ n $ cards with prices for different positions are laid out in front of him, on the $ i $ -th card there is an integer $ a_i $ , among these prices there is no whole positive integer $ x $ .

Kmes is asked to divide these cards into the minimum number of bad segments (so that each card belongs to exactly one segment). A segment is considered bad if it is impossible to select a subset of cards with a product equal to $ x $ . All segments, in which Kmes will divide the cards, must be bad.

Formally, the segment $ (l, r) $ is bad if there are no indices $ i_1 < i_2 < \ldots < i_k $ such that $ l \le i_1, i_k \le r $ , and $ a_{i_1} \cdot a_{i_2} \ldots \cdot a_{i_k} = x $ .

Help Kmes determine the minimum number of bad segments in order to enjoy his favorite dish.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

The first line of each set of input data gives you $ 2 $ integers $ n $ and $ x $ ( $ 1 \le n \le 10^5, 2 \le x \le 10^5 $ ) — the number of cards and the integer, respectively.

The second line of each set of input data contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 2 \cdot 10^5, a_i \neq x $ ) — the prices on the cards.

It is guaranteed that the sum of $ n $ over all sets of test data does not exceed $ 10^5 $ .

## 输出格式

For each set of input data, output the minimum number of bad segments.

## 样例 #1

### 输入

```
8
6 4
2 3 6 2 1 2
9 100000
50000 25000 12500 6250 3125 2 4 8 16
5 2
1 1 1 1 1
8 6
4 3 4 3 4 3 4 3
7 12
6 11 1 3 11 10 2
10 5
2 4 4 2 4 4 4 3 1 1
7 8
4 6 5 1 2 4 1
8 27
3 9 17 26 2 20 9 3
```

### 输出

```
3
2
1
1
2
1
3
3
```

