---
title: "Small Permutation Problem (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1909F2
tag: ['动态规划 DP']
---

# Small Permutation Problem (Hard Version)

## 题目描述

[Andy Tunstall - MiniBoss](https://soundcloud.com/tunners/miniboss)

⠀



In the easy version, the $ a_i $ are in the range $ [0, n] $ ; in the hard version, the $ a_i $ are in the range $ [-1, n] $ and the definition of good permutation is slightly different. You can make hacks only if all versions of the problem are solved.

You are given an integer $ n $ and an array $ a_1, a_2, \dots, a_n $ of integers in the range $ [-1, n] $ .

A permutation $ p_1, p_2, \dots, p_n $ of $ [1, 2, \dots, n] $ is good if, for each $ i $ , the following condition is true:

- if $ a_i \neq -1 $ , the number of values $ \leq i $ in $ [p_1, p_2, \dots, p_i] $ is exactly $ a_i $ .

Count the good permutations of $ [1, 2, \dots, n] $ , modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -1 \le a_i \le n $ ), which describe the conditions for a good permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing the number of good permutations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, all the permutations of length $ 5 $ are good, so there are $ 120 $ good permutations.

In the second test case, the only good permutation is $ [1, 2, 3, 4, 5] $ .

In the third test case, there are $ 4 $ good permutations: $ [2, 1, 5, 6, 3, 4] $ , $ [2, 1, 5, 6, 4, 3] $ , $ [2, 1, 6, 5, 3, 4] $ , $ [2, 1, 6, 5, 4, 3] $ . For example, $ [2, 1, 5, 6, 3, 4] $ is good because:

- $ a_1 = 0 $ , and there are $ 0 $ values $ \leq 1 $ in $ [p_1] = [2] $ ;
- $ a_2 = 2 $ , and there are $ 2 $ values $ \leq 2 $ in $ [p_1, p_2] = [2, 1] $ ;
- $ a_3 = 2 $ , and there are $ 2 $ values $ \leq 3 $ in $ [p_1, p_2, p_3] = [2, 1, 5] $ ;
- $ a_4 = 2 $ , and there are $ 2 $ values $ \leq 4 $ in $ [p_1, p_2, p_3, p_4] = [2, 1, 5, 6] $ ;
- $ a_5 = -1 $ , so there are no restrictions on $ [p_1, p_2, p_3, p_4, p_5] $ ;
- $ a_6 = -1 $ , so there are no restrictions on $ [p_1, p_2, p_3, p_4, p_5, p_6] $ .

## 样例 #1

### 输入

```
10
5
-1 -1 -1 -1 -1
5
1 2 3 4 5
6
0 2 2 2 -1 -1
6
-1 -1 -1 -1 -1 5
6
-1 -1 3 2 -1 -1
15
0 0 -1 -1 -1 2 2 -1 -1 -1 -1 9 11 13 15
6
0 2 2 2 4 6
6
0 1 3 4 5 5
6
1 2 3 2 4 6
15
0 0 1 1 1 2 3 4 5 6 7 9 11 13 15
```

### 输出

```
120
1
4
0
0
494403526
4
0
0
532305727
```

