---
title: "Two Permutations (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1882E2
tag: []
---

# Two Permutations (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the two versions is that you have to minimize the number of operations in this version. You can make hacks only if both versions of the problem are solved.

You have two permutations $ ^{\dagger} $ $ p_{1}, p_{2}, \ldots, p_{n} $ (of integers $ 1 $ to $ n $ ) and $ q_{1}, q_{2}, \ldots, q_{m} $ (of integers $ 1 $ to $ m $ ). Initially $ p_{i}=a_{i} $ for $ i=1, 2, \ldots, n $ , and $ q_{j} = b_{j} $ for $ j = 1, 2, \ldots, m $ . You can apply the following operation on the permutations several (possibly, zero) times.

In one operation, $ p $ and $ q $ will change according to the following three steps:

- You choose integers $ i $ , $ j $ which satisfy $ 1 \le i \le n $ and $ 1 \le j \le m $ .
- Permutation $ p $ is partitioned into three parts using $ p_i $ as a pivot: the left part is formed by elements $ p_1, p_2, \ldots, p_{i-1} $ (this part may be empty), the middle part is the single element $ p_i $ , and the right part is $ p_{i+1}, p_{i+2}, \ldots, p_n $ (this part may be empty). To proceed, swap the left and the right parts of this partition. Formally, after this step, $ p $ will become $ p_{i+1}, p_{i+2}, \ldots, p_{n}, p_{i}, p_{1}, p_{2}, \ldots, p_{i-1} $ . The elements of the newly formed $ p $ will be reindexed starting from $ 1 $ .
- Perform the same transformation on $ q $ with index $ j $ . Formally, after this step, $ q $ will become $ q_{j+1}, q_{j+2}, \ldots, q_{m}, q_{j}, q_{1}, q_{2}, \ldots, q_{j-1} $ . The elements of the newly formed $ q $ will be reindexed starting from $ 1 $ .

Your goal is to simultaneously make $ p_{i}=i $ for $ i=1, 2, \ldots, n $ , and $ q_{j} = j $ for $ j = 1, 2, \ldots, m $ .

Find any way to achieve the goal using the minimum number of operations possible, or say that none exists. Please note that you have to minimize the number of operations.

 $ ^{\dagger} $ A permutation of length $ k $ is an array consisting of $ k $ distinct integers from $ 1 $ to $ k $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ k=3 $ but there is $ 4 $ in the array).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2500 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ).

The third line contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le m $ ).

It is guaranteed that $ a $ and $ b $ are permutations.

## 输出格式

If there is no solution, print a single integer $ -1 $ .

Otherwise, print an integer $ k $ — the number of operations to perform, followed by $ k $ lines, each containing two integers $ i $ and $ j $ ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ) — the integers chosen for the operation.

If there are multiple solutions, print any of them.

Please note that you have to minimize the number of operations.

## 说明/提示

In the first test case, we can achieve the goal within $ 2 $ operations:

1. In the first operation, choose $ i = 3 $ , $ j = 4 $ . After this, $ p $ becomes $ [3, 2, 1] $ and $ q $ becomes $ [3, 4, 5, 2, 1] $ .
2. In the second operation, choose $ i = 2 $ , $ j = 4 $ . After this, $ p $ becomes $ [1, 2, 3] $ and $ q $ becomes $ [1, 2, 3, 4, 5] $ .

In the third test case, it is impossible to achieve the goal.

## 样例 #1

### 输入

```
3 5
2 1 3
5 2 1 4 3
```

### 输出

```
2
3 4
2 4
```

## 样例 #2

### 输入

```
4 4
3 4 2 1
2 4 1 3
```

### 输出

```
3
3 3
1 4
4 2
```

## 样例 #3

### 输入

```
2 2
1 2
2 1
```

### 输出

```
-1
```

