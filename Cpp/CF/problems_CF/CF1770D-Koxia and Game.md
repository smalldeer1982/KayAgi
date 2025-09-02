---
title: "Koxia and Game"
layout: "post"
diff: 提高+/省选-
pid: CF1770D
tag: []
---

# Koxia and Game

## 题目描述

Koxia and Mahiru are playing a game with three arrays $ a $ , $ b $ , and $ c $ of length $ n $ . Each element of $ a $ , $ b $ and $ c $ is an integer between $ 1 $ and $ n $ inclusive.

The game consists of $ n $ rounds. In the $ i $ -th round, they perform the following moves:

- Let $ S $ be the multiset $ \{a_i, b_i, c_i\} $ .
- Koxia removes one element from the multiset $ S $ by her choice.
- Mahiru chooses one integer from the two remaining in the multiset $ S $ .

Let $ d_i $ be the integer Mahiru chose in the $ i $ -th round. If $ d $ is a permutation $ ^\dagger $ , Koxia wins. Otherwise, Mahiru wins.

Currently, only the arrays $ a $ and $ b $ have been chosen. As an avid supporter of Koxia, you want to choose an array $ c $ such that Koxia will win. Count the number of such $ c $ , modulo $ 998\,244\,353 $ .

Note that Koxia and Mahiru both play optimally.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq {10}^5 $ ) — the size of the arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ).

The third line of each test case contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \leq b_i \leq n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ {10}^5 $ .

## 输出格式

Output a single integer — the number of $ c $ makes Koxia win, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, there are $ 6 $ possible arrays $ c $ that make Koxia win — $ [1, 2, 3] $ , $ [1, 3, 2] $ , $ [2, 2, 3] $ , $ [2, 3, 2] $ , $ [3, 2, 3] $ , $ [3, 3, 2] $ .

In the second test case, it can be proved that no array $ c $ makes Koxia win.

## 样例 #1

### 输入

```
2
3
1 2 2
1 3 3
5
3 3 1 3 4
4 5 2 5 5
```

### 输出

```
6
0
```

