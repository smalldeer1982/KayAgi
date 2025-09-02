---
title: "Mex Master"
layout: "post"
diff: 普及-
pid: CF1806B
tag: []
---

# Mex Master

## 题目描述

You are given an array $ a $ of length $ n $ . The score of $ a $ is the MEX $ ^{\dagger} $ of $ [a_1+a_2,a_2+a_3,\ldots,a_{n-1}+a_n] $ . Find the minimum score of $ a $ if you are allowed to rearrange elements of $ a $ in any order. Note that you are not required to construct the array $ a $ that achieves the minimum score.

 $ ^{\dagger} $ The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2\le n\le 2\cdot10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 2\cdot 10^5 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum score of $ a $ after rearranging the elements of $ a $ in any order.

## 说明/提示

In the first test case, it is optimal to rearrange $ a $ as $ [0,0] $ , the score of this array is the MEX of $ [0+0]=[0] $ , which is $ 1 $ .

In the second test case, it is optimal to rearrange $ a $ as $ [0,1,0] $ , the score of this array is the MEX of $ [0+1,1+0]=[1,1] $ , which is $ 0 $ .

## 样例 #1

### 输入

```
3
2
0 0
3
0 0 1
8
1 0 0 0 2 0 3 0
```

### 输出

```
1
0
1
```

