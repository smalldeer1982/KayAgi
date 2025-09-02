---
title: "Good Arrays"
layout: "post"
diff: 普及-
pid: CF1856B
tag: []
---

# Good Arrays

## 题目描述

You are given an array of positive integers $ a $ of length $ n $ .

Let's call an array of positive integers $ b $ of length $ n $ good if:

1. $ a_i \neq b_i $ for all $ i $ from $ 1 $ to $ n $ ,
2. $ a_1 + a_2 +\ldots + a_n = b_1 + b_2 + \ldots + b_n $ .

Does a good array exist?

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10 ^ 9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "YES" (without quotes) if there exists a good array, and "NO" (without quotes) otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs","yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, a possible good array is $ [3, 3, 3] $ . Some examples of not good arrays are:

- $ [8, 0, 1] $ — the array does not consist of only positive integers,
- $ [5, 2, 4] $ — the array does not have the same sum as the given array,
- $ [5, 2, 2] $ — the third element is equal to the third element of the given array.

In the second test case, $ [1, 1] $ is the only array of positive integers of length $ 2 $ that has the sum of it's elements equal to $ 2 $ . Since $ [1, 1] $ is not a good array, the answer is "NO".

## 样例 #1

### 输入

```
6
3
6 1 2
2
1 1
4
3 1 2 4
1
17
5
1 2 1 1 1
3
618343152 819343431 1000000000
```

### 输出

```
YES
NO
YES
NO
NO
YES
```

