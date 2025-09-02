---
title: "Grouping Increases"
layout: "post"
diff: 普及/提高-
pid: CF1919C
tag: ['贪心']
---

# Grouping Increases

## 题目描述

You are given an array $ a $ of size $ n $ . You will do the following process to calculate your penalty:

1. Split array $ a $ into two (possibly empty) subsequences $ ^\dagger $ $ s $ and $ t $ such that every element of $ a $ is either in $ s $ or $ t^\ddagger $ .
2. For an array $ b $ of size $ m $ , define the penalty $ p(b) $ of an array $ b $ as the number of indices $ i $ between $ 1 $ and $ m - 1 $ where $ b_i < b_{i + 1} $ .
3. The total penalty you will receive is $ p(s) + p(t) $ .

If you perform the above process optimally, find the minimum possible penalty you will receive.

 $ ^\dagger $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by the deletion of several (possibly, zero or all) elements.

 $ ^\ddagger $ Some valid ways to split array $ a=[3,1,4,1,5] $ into $ (s,t) $ are $ ([3,4,1,5],[1]) $ , $ ([1,1],[3,4,5]) $ and $ ([\,],[3,1,4,1,5]) $ while some invalid ways to split $ a $ are $ ([3,4,5],[1]) $ , $ ([3,1,4,1],[1,5]) $ and $ ([1,3,4],[5,1]) $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 2\cdot 10^5 $ ) — the size of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer representing the minimum possible penalty you will receive.

## 说明/提示

In the first test case, a possible way to split $ a $ is $ s=[2,4,5] $ and $ t=[1,3] $ . The penalty is $ p(s)+p(t)=2 + 1 =3 $ .

In the second test case, a possible way to split $ a $ is $ s=[8,3,1] $ and $ t=[2,1,7,4,3] $ . The penalty is $ p(s)+p(t)=0 + 1 =1 $ .

In the third test case, a possible way to split $ a $ is $ s=[\,] $ and $ t=[3,3,3,3,3] $ . The penalty is $ p(s)+p(t)=0 + 0 =0 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
8
8 2 3 1 1 7 4 3
5
3 3 3 3 3
1
1
2
2 1
```

### 输出

```
3
1
0
0
0
```

