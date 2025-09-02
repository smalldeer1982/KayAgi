---
title: "Find B"
layout: "post"
diff: 普及/提高-
pid: CF1923C
tag: ['前缀和', '构造']
---

# Find B

## 题目描述

An array $ a $ of length $ m $ is considered good if there exists an integer array $ b $ of length $ m $ such that the following conditions hold:

1. $ \sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i $ ;
2. $ a_i \neq b_i $ for every index $ i $ from $ 1 $ to $ m $ ;
3. $ b_i > 0 $ for every index $ i $ from $ 1 $ to $ m $ .

You are given an array $ c $ of length $ n $ . Each element of this array is greater than $ 0 $ .

You have to answer $ q $ queries. During the $ i $ -th query, you have to determine whether the subarray $ c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}} $ is good.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 3 \cdot 10^5 $ ) — the length of the array $ c $ and the number of queries.

The second line of each test case contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le 10^9 $ ).

Then $ q $ lines follow. The $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the borders of the $ i $ -th subarray.

Additional constraints on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ ; the sum of $ q $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each query, print YES if the subarray is good. Otherwise, print NO.

You can output each letter of the answer in any case (upper or lower). For example, the strings yEs, yes, Yes, and YES will all be recognized as positive responses.

## 样例 #1

### 输入

```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3
```

### 输出

```
YES
NO
YES
NO
```

