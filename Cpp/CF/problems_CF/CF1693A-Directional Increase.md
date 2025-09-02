---
title: "Directional Increase"
layout: "post"
diff: 普及/提高-
pid: CF1693A
tag: []
---

# Directional Increase

## 题目描述

We have an array of length $ n $ . Initially, each element is equal to $ 0 $ and there is a pointer located on the first element.

We can do the following two kinds of operations any number of times (possibly zero) in any order:

1. If the pointer is not on the last element, increase the element the pointer is currently on by $ 1 $ . Then move it to the next element.
2. If the pointer is not on the first element, decrease the element the pointer is currently on by $ 1 $ . Then move it to the previous element.

But there is one additional rule. After we are done, the pointer has to be on the first element.

You are given an array $ a $ . Determine whether it's possible to obtain $ a $ after some operations or not.

## 输入格式

The first line contains a single integer $ t $ $ (1\le t\le 1000) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1\le n\le 2 \cdot 10^5) $ — the size of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — elements of the array.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print "Yes" (without quotes) if it's possible to obtain $ a $ after some operations, and "No" (without quotes) otherwise.

You can output "Yes" and "No" in any case (for example, strings "yEs", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first test case we can obtain the array after some operations, but the pointer won't be on the first element.

One way of obtaining the array in the second test case is shown below.

 $ \langle \underline{0}, 0, 0, 0\rangle \to \langle 1, \underline{0}, 0, 0 \rangle \to \langle \underline{1}, -1, 0, 0\rangle \to \langle 2, \underline{-1}, 0, 0\rangle \to \langle 2, 0, \underline{0}, 0\rangle \to \langle 2, \underline{0}, -1, 0\rangle \to \langle \underline{2}, -1, -1, 0\rangle $

## 样例 #1

### 输入

```
7
2
1 0
4
2 -1 -1 0
4
1 -4 3 0
4
1 -1 1 -1
5
1 2 3 4 -10
7
2 -1 1 -2 0 0 0
1
0
```

### 输出

```
No
Yes
No
No
Yes
Yes
Yes
```

