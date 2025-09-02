---
title: "Odd Subarrays"
layout: "post"
diff: 普及-
pid: CF1686B
tag: []
---

# Odd Subarrays

## 题目描述

For an array $ [b_1, b_2, \ldots, b_m] $ define its number of inversions as the number of pairs $ (i, j) $ of integers such that $ 1 \le i < j \le m $ and $ b_i>b_j $ . Let's call array $ b $ odd if its number of inversions is odd.

For example, array $ [4, 2, 7] $ is odd, as its number of inversions is $ 1 $ , while array $ [2, 1, 4, 3] $ isn't, as its number of inversions is $ 2 $ .

You are given a permutation $ [p_1, p_2, \ldots, p_n] $ of integers from $ 1 $ to $ n $ (each of them appears exactly once in the permutation). You want to split it into several consecutive subarrays (maybe just one), so that the number of the odd subarrays among them is as large as possible.

What largest number of these subarrays may be odd?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the permutation.

The second line of each test case contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ , all $ p_i $ are distinct) — the elements of the permutation.

The sum of $ n $ over all test cases doesn't exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case output a single integer — the largest possible number of odd subarrays that you can get after splitting the permutation into several consecutive subarrays.

## 说明/提示

In the first and third test cases, no matter how we split our permutation, there won't be any odd subarrays.

In the second test case, we can split our permutation into subarrays $ [4, 3], [2, 1] $ , both of which are odd since their numbers of inversions are $ 1 $ .

In the fourth test case, we can split our permutation into a single subarray $ [2, 1] $ , which is odd.

In the fifth test case, we can split our permutation into subarrays $ [4, 5], [6, 1, 2, 3] $ . The first subarray has $ 0 $ inversions, and the second has $ 3 $ , so it is odd.

## 样例 #1

### 输入

```
5
3
1 2 3
4
4 3 2 1
2
1 2
2
2 1
6
4 5 6 1 2 3
```

### 输出

```
0
2
0
1
1
```

