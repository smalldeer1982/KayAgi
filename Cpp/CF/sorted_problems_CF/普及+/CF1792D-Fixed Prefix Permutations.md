---
title: "Fixed Prefix Permutations"
layout: "post"
diff: 普及+/提高
pid: CF1792D
tag: []
---

# Fixed Prefix Permutations

## 题目描述

You are given $ n $ permutations $ a_1, a_2, \dots, a_n $ , each of length $ m $ . Recall that a permutation of length $ m $ is a sequence of $ m $ distinct integers from $ 1 $ to $ m $ .

Let the beauty of a permutation $ p_1, p_2, \dots, p_m $ be the largest $ k $ such that $ p_1 = 1, p_2 = 2, \dots, p_k = k $ . If $ p_1 \neq 1 $ , then the beauty is $ 0 $ .

The product of two permutations $ p \cdot q $ is a permutation $ r $ such that $ r_j = q_{p_j} $ .

For each $ i $ from $ 1 $ to $ n $ , print the largest beauty of a permutation $ a_i \cdot a_j $ over all $ j $ from $ 1 $ to $ n $ (possibly, $ i = j $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains two integers $ n $ and $ m $ ( $ 1 \le n \le 5 \cdot 10^4 $ ; $ 1 \le m \le 10 $ ) — the number of permutations and the length of each permutation.

The $ i $ -th of the next $ n $ lines contains a permutation $ a_i $ — $ m $ distinct integers from $ 1 $ to $ m $ .

The sum of $ n $ doesn't exceed $ 5 \cdot 10^4 $ over all testcases.

## 输出格式

For each testcase, print $ n $ integers. The $ i $ -th value should be equal to the largest beauty of a permutation $ a_i \cdot a_j $ over all $ j $ ( $ 1 \le j \le n $ ).

## 样例 #1

### 输入

```
3
3 4
2 4 1 3
1 2 4 3
2 1 3 4
2 2
1 2
2 1
8 10
3 4 9 6 10 2 7 8 1 5
3 9 1 8 5 7 4 10 2 6
3 10 1 7 5 9 6 4 2 8
1 2 3 4 8 6 10 7 9 5
1 2 3 4 10 6 8 5 7 9
9 6 1 2 10 4 7 8 3 5
7 9 3 2 5 6 4 8 1 10
9 4 3 7 5 6 1 10 8 2
```

### 输出

```
1 4 4 
2 2 
10 8 1 6 8 10 1 7
```

