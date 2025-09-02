---
title: "Move Back at a Cost"
layout: "post"
diff: 普及+/提高
pid: CF2046B
tag: ['贪心']
---

# Move Back at a Cost

## 题目描述

You are given an array of integers $ a $ of length $ n $ . You can perform the following operation zero or more times:

- In one operation choose an index $ i $ ( $ 1 \le i \le n $ ), assign $ a_i := a_i + 1 $ , and then move $ a_i $ to the back of the array (to the rightmost position). For example, if $ a = [3, 5, 1, 9] $ , and you choose $ i = 2 $ , the array becomes $ [3, 1, 9, 6] $ .

Find the lexicographically smallest $ ^{\text{∗}} $ array you can get by performing these operations.

 $ ^{\text{∗}} $ An array $ c $ is lexicographically smaller than an array $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ; or
- in the first position where $ c $ and $ d $ differ, the array $ c $ has a smaller element than the corresponding element in $ d $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ), the length of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print the lexicographically smallest array you can get.

## 样例 #1

### 输入

```
3
3
2 1 3
5
1 2 2 1 4
6
1 2 3 6 5 4
```

### 输出

```
1 3 3 
1 1 3 3 5 
1 2 3 4 6 7
```

