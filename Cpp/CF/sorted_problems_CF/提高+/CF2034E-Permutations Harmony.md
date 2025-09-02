---
title: "Permutations Harmony"
layout: "post"
diff: 提高+/省选-
pid: CF2034E
tag: ['贪心', '分类讨论']
---

# Permutations Harmony

## 题目描述

Rayan wants to present a gift to Reyhaneh to win her heart. However, Reyhaneh is particular and will only accept a k-harmonic set of permutations.

We define a k-harmonic set of permutations as a set of $ k $ pairwise distinct permutations $ p_1, p_2, \ldots, p_k $ of size $ n $ such that for every pair of indices $ i $ and $ j $ (where $ 1 \leq i, j \leq n $ ), the following condition holds:

 $ $$$ p_1[i] + p_2[i] + \ldots + p_k[i] = p_1[j] + p_2[j] + \ldots + p_k[j]  $ $ </p><p>Your task is to help Rayan by either providing a valid <span class="tex-font-style-it">k-harmonic set of permutations</span> for given values of  $ n $  and  $ k $  or by determining that such a set does not exist.</p><p>We call a sequence of length  $ n $  a permutation if it contains every integer from  $ 1 $  to  $ n$$$ exactly once.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ), the number of test cases.

Each test case consists of two integers $ n $ and $ k $ ( $ 1 \leq n, k \leq 10^5 $ ). The sum of $ n \cdot k $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, if a k-harmonic set of permutations exists, print YES on the first line. Then, print $ k $ lines, each containing a distinct permutation of the integers from $ 1 $ to $ n $ .

If no such set exists, print NO on the first line.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", and "Yes" will be recognized as a positive response).

If multiple answers are possible, you can output any of them.

## 说明/提示

In example 1, we have $ p_1 = [1, 2, 3] $ , $ p_2 = [2, 3, 1] $ , and $ p_3 = [3, 1, 2] $ . It's easy to see that $ p_1[1] + p_2[1] + p_3[1] = p_1[2] + p_2[2] + p_3[2] = p_1[3] + p_2[3] + p_3[3] = 6 $ .

In example 2, we have $ p_1 = [1, 2, 3, 4] $ and $ p_2 = [4, 3, 2, 1] $ . It's easy to see that $ p_1[1] + p_2[1] = p_1[2] + p_2[2] = p_1[3] + p_2[3] = p_1[4] + p_2[4] = 5 $ .

In example 3, as there are five distinct elements in $ p_1 $ , it's obvious that the answer is "No".

## 样例 #1

### 输入

```
4
3 3
4 2
5 1
3 2
```

### 输出

```
YES
1 2 3
2 3 1
3 1 2
YES
1 2 3 4
4 3 2 1
NO
YES
1 2 3
3 2 1
```

