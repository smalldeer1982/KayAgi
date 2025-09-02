---
title: "Unequal Adjacent Elements"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1762G
tag: []
---

# Unequal Adjacent Elements

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers.

Find any permutation $ p $ of $ [1,2,\dots,n] $ such that:

- $ p_{i-2} < p_i $ for all $ i $ , where $ 3 \leq i \leq n $ , and
- $ a_{p_{i-1}} \neq a_{p_i} $ for all $ i $ , where $ 2 \leq i \leq n $ .

Or report that no such permutation exists.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 3 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ space-separated integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \leq a_i \leq n $ ) — representing the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output "NO" if no such permutation exists, otherwise output "YES" in the first line and print the permutation $ p $ in the next line.

In case there are multiple permutations, print any one of them.

You can output "YES" and "NO" in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive response).

## 说明/提示

In the first test case, $ p=[1,2,3] $ is the only permutation of $ [1,2,3] $ that satisfy the given constraints.

In the second test case, $ [1,3,2,4] $ , $ [2,1,4,3] $ and some other permutations are also acceptable.

In the third test case, it can be proved that there does not exist any permutation of $ [1,2,3] $ satisfying the given constraints.

## 样例 #1

### 输入

```
4
3
1 2 1
4
1 2 3 4
3
1 1 1
7
1 2 1 1 3 1 4
```

### 输出

```
YES
1 2 3
YES
3 1 4 2
NO
YES
1 2 3 5 4 7 6
```

