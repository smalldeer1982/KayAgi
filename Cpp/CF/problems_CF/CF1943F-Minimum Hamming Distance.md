---
title: "Minimum Hamming Distance"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1943F
tag: []
---

# Minimum Hamming Distance

## 题目描述

You are given a binary string $ ^\dagger $ $ s $ of length $ n $ .

A binary string $ p $ of the same length $ n $ is called good if for every $ i $ ( $ 1 \leq i \leq n $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq n $
- $ s_i $ is a mode $ ^\ddagger $ of the string $ p_lp_{l+1}\ldots p_r $

You are given another binary string $ t $ of length $ n $ . Find the minimum Hamming distance $ ^\S $ between $ t $ and any good string $ g $ .

 $ ^\dagger $ A binary string is a string that only consists of characters $ \mathtt{0} $ and $ \mathtt{1} $ .

 $ ^\ddagger $ Character $ c $ is a mode of string $ p $ of length $ m $ if the number of occurrences of $ c $ in $ p $ is at least $ \lceil \frac{m}{2} \rceil $ . For example, $ \mathtt{0} $ is a mode of $ \mathtt{010} $ , $ \mathtt{1} $ is not a mode of $ \mathtt{010} $ , and both $ \mathtt{0} $ and $ \mathtt{1} $ are modes of $ \mathtt{011010} $ .

 $ ^\S $ The Hamming distance of strings $ a $ and $ b $ of length $ m $ is the number of indices $ i $ such that $ 1 \leq i \leq m $ and $ a_i \neq b_i $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^4 $ ) — the length of the binary string $ s $ .

The second line of each test case contains a binary string $ s $ of length $ n $ consisting of characters 0 and 1.

The third line of each test case contains a binary string $ t $ of length $ n $ consisting of characters 0 and 1.

It is guaranteed that the sum of $ n $  over all test cases does not exceed $ 10^6 $ , with the additional assurance that the sum of $ n^2 $  over all test cases does not exceed $ 10^8 $

## 输出格式

For each test case, print the minimum Hamming distance between $ t $ and any good string $ g $ .

## 说明/提示

In the first test case, $ g=\mathtt{000} $ is a good string which has Hamming distance $ 0 $ from $ t $ .

In the second test case, $ g=\mathtt{0011} $ is a good string which has Hamming distance $ 2 $ from $ t $ . It can be proven that there are no good strings with Hamming distance less than $ 2 $ from $ t $ .

In the third test case, $ g=\mathtt{001100} $ is a good string which has Hamming distance $ 1 $ from $ t $ .

## 样例 #1

### 输入

```
3
3
000
000
4
0000
1111
6
111111
000100
```

### 输出

```
0
2
1
```

