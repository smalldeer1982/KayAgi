---
title: "A-B-C Sort"
layout: "post"
diff: 普及/提高-
pid: CF1674D
tag: []
---

# A-B-C Sort

## 题目描述

You are given three arrays $ a $ , $ b $ and $ c $ . Initially, array $ a $ consists of $ n $ elements, arrays $ b $ and $ c $ are empty.

You are performing the following algorithm that consists of two steps:

- Step $ 1 $ : while $ a $ is not empty, you take the last element from $ a $ and move it in the middle of array $ b $ . If $ b $ currently has odd length, you can choose: place the element from $ a $ to the left or to the right of the middle element of $ b $ . As a result, $ a $ becomes empty and $ b $ consists of $ n $ elements.
- Step $ 2 $ : while $ b $ is not empty, you take the middle element from $ b $ and move it to the end of array $ c $ . If $ b $ currently has even length, you can choose which of two middle elements to take. As a result, $ b $ becomes empty and $ c $ now consists of $ n $ elements.

 Refer to the Note section for examples.Can you make array $ c $ sorted in non-decreasing order?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. Next $ t $ cases follow.

The first line of each test case contains the single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the array $ a $ itself.

It's guaranteed that the sum of $ n $ doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test, print YES (case-insensitive), if you can make array $ c $ sorted in non-decreasing order. Otherwise, print NO (case-insensitive).

## 说明/提示

In the first test case, we can do the following for $ a = [3, 1, 5, 3] $ :

Step $ 1 $ :

$ a $  $ [3, 1, 5, 3] $  $ \Rightarrow $  $ [3, 1, 5] $  $ \Rightarrow $  $ [3, 1] $  $ \Rightarrow $  $ [3] $  $ \Rightarrow $  $ [] $

$ b $  $ [] $ $ \Rightarrow $ $ [\underline{3}] $ $ \Rightarrow $ $ [3, \underline{5}] $ $ \Rightarrow $ $ [3, \underline{1}, 5] $ $ \Rightarrow $ $ [3, \underline{3}, 1, 5] $
 
Step $ 2 $ :

$ b $  $ [3, 3, \underline{1}, 5] $  $ \Rightarrow $  $ [3, \underline{3}, 5] $  $ \Rightarrow $  $ [\underline{3}, 5] $  $ \Rightarrow $  $ [\underline{5}] $  $ \Rightarrow $  $ [] $

$ c $  $ [] $ $ \Rightarrow $ $ [1] $ $ \Rightarrow $ $ [1, 3] $ $ \Rightarrow $ $ [1, 3, 3] $ $ \Rightarrow $ $ [1, 3, 3, 5] $

As a result, array $ c = [1, 3, 3, 5] $ and it's sorted.

## 样例 #1

### 输入

```
3
4
3 1 5 3
3
3 2 1
1
7331
```

### 输出

```
YES
NO
YES
```

