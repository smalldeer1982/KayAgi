---
title: "Alice's Adventures in Permuting"
layout: "post"
diff: 普及/提高-
pid: CF2028B
tag: ['数学', '分类讨论']
---

# Alice's Adventures in Permuting

## 题目描述

Alice mixed up the words transmutation and permutation! She has an array $ a $ specified via three integers $ n $ , $ b $ , $ c $ : the array $ a $ has length $ n $ and is given via $ a_i = b\cdot (i - 1) + c $ for $ 1\le i\le n $ . For example, if $ n=3 $ , $ b=2 $ , and $ c=1 $ , then $ a=[2 \cdot 0 + 1, 2 \cdot 1 + 1, 2 \cdot 2 + 1] = [1, 3, 5] $ .

Now, Alice really enjoys permutations of $ [0, \ldots, n-1] $ $ ^{\text{∗}} $ and would like to transform $ a $ into a permutation. In one operation, Alice replaces the maximum element of $ a $ with the $ \operatorname{MEX} $ $ ^{\text{†}} $ of $ a $ . If there are multiple maximum elements in $ a $ , Alice chooses the leftmost one to replace.

Can you help Alice figure out how many operations she has to do for $ a $ to become a permutation for the first time? If it is impossible, you should report it.

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 0 $ to $ n-1 $ in arbitrary order. Please note, this is slightly different from the usual definition of a permutation. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,2,3] $ is also not a permutation ( $ n=3 $ but there is $ 3 $ in the array).

 $ ^{\text{†}} $ The $ \operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array. For example, the $ \operatorname{MEX} $ of $ [0, 3, 1, 3] $ is $ 2 $ and the $ \operatorname{MEX} $ of $ [5] $ is $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The only line of each test case contains three integers $ n $ , $ b $ , $ c $ ( $ 1\le n\le 10^{18} $ ; $ 0\le b $ , $ c\le 10^{18} $ ) — the parameters of the array.

## 输出格式

For each test case, if the array can never become a permutation, output $ -1 $ . Otherwise, output the minimum number of operations for the array to become a permutation.

## 说明/提示

In the first test case, the array is already $ [0, 1, \ldots, 9] $ , so no operations are required.

In the third test case, the starting array is $ [1, 3, 5, \ldots, 199] $ . After the first operation, the $ 199 $ gets transformed into a $ 0 $ . In the second operation, the $ 197 $ gets transformed into a $ 2 $ . If we continue this, it will take exactly $ 50 $ operations to get the array $ [0, 1, 2, 3, \ldots, 99] $ .

In the fourth test case, two operations are needed: $ [1,1,1] \to [0,1,1] \to [0,2,1] $ .

In the fifth test case, the process is $ [0,0,0] \to [1,0,0] \to [2,0,0] \to [1,0,0] \to [2,0,0] $ . This process repeats forever, so the array is never a permutation and the answer is $ -1 $ .

## 样例 #1

### 输入

```
7
10 1 0
1 2 3
100 2 1
3 0 1
3 0 0
1000000000000000000 0 0
1000000000000000000 1000000000000000000 1000000000000000000
```

### 输出

```
0
1
50
2
-1
-1
1000000000000000000
```

