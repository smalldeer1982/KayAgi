---
title: "Inversion Composition"
layout: "post"
diff: 省选/NOI-
pid: CF1951F
tag: []
---

# Inversion Composition

## 题目描述

[My Chemical Romance - Disenchanted](https://youtu.be/j_MlBCb9-m8)

ඞ



You are given a permutation $ p $ of size $ n $ , as well as a non-negative integer $ k $ . You need to construct a permutation $ q $ of size $ n $ such that $ \operatorname{inv}(q) + \operatorname{inv}(q \cdot p) = k {}^\dagger {}^\ddagger $ , or determine if it is impossible to do so.

 $ {}^\dagger $ For two permutations $ p $ and $ q $ of the same size $ n $ , the permutation $ w = q \cdot p $ is such that $ w_i = q_{p_i} $ for all $ 1 \le i \le n $ .

 $ {}^\ddagger $ For a permutation $ p $ of size $ n $ , the function $ \operatorname{inv}(p) $ returns the number of inversions of $ p $ , i.e. the number of pairs of indices $ 1 \le i < j \le n $ such that $ p_i > p_j $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 3 \cdot 10^5, 0 \le k \le n(n - 1) $ ) — the size of $ p $ and the target number of inversions.

The second line of each test case contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ , $ p_i $ 's are pairwise distinct) — the given permutation $ p $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print on one line "YES" if there exists a permutation $ q $ that satisfies the given condition, or "NO" if there is no such permutation.

If the answer is "YES", on the second line, print $ n $ integers $ q_1, q_2, \ldots, q_n $ that represent such a satisfactory permutation $ q $ . If there are multiple such $ q $ 's, print any of them.

## 说明/提示

In the first test case, we have $ q \cdot p = [2, 1, 3] $ , $ \operatorname{inv}(q) = 3 $ , and $ \operatorname{inv}(q \cdot p) = 1 $ .

In the fourth test case, we have $ q \cdot p = [9, 1, 8, 5, 7, 6, 4, 3, 2] $ , $ \operatorname{inv}(q) = 24 $ , and $ \operatorname{inv}(q \cdot p) = 27 $ .

## 样例 #1

### 输入

```
5
3 4
2 3 1
5 5
2 3 5 1 4
6 11
5 1 2 3 4 6
9 51
3 1 4 2 5 6 7 8 9
1 0
1
```

### 输出

```
YES
3 2 1
NO
NO
YES
1 5 9 8 7 6 4 3 2
YES
1
```

