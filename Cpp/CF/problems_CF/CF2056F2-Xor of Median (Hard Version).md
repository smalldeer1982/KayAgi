---
title: "Xor of Median (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2056F2
tag: []
---

# Xor of Median (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, the constraints on $ t $ , $ k $ , and $ m $ are higher. You can hack only if you solved all versions of this problem.

A sequence $ a $ of $ n $ integers is called good if the following condition holds:

- Let $ \text{cnt}_x $ be the number of occurrences of $ x $ in sequence $ a $ . For all pairs $ 0 \le i < j < m $ , at least one of the following has to be true: $ \text{cnt}_i = 0 $ , $ \text{cnt}_j = 0 $ , or $ \text{cnt}_i \le \text{cnt}_j $ . In other words, if both $ i $ and $ j $ are present in sequence $ a $ , then the number of occurrences of $ i $ in $ a $ is less than or equal to the number of occurrences of $ j $ in $ a $ .

You are given integers $ n $ and $ m $ . Calculate the value of the bitwise XOR of the median $ ^{\text{∗}} $ of all good sequences $ a $ of length $ n $ with $ 0\le a_i < m $ .

Note that the value of $ n $ can be very large, so you are given its binary representation instead.

 $ ^{\text{∗}} $ The median of a sequence $ a $ of length $ n $ is defined as the $ \left\lfloor\frac{n + 1}{2}\right\rfloor $ -th smallest value in the sequence.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ k $ and $ m $ ( $ 1 \le k \le 2 \cdot 10^5 $ , $ 1 \le m \le 10^9 $ ) — the number of bits in $ n $ and the upper bound on the elements in sequence $ a $ .

The second line of each test case contains a binary string of length $ k $ — the binary representation of $ n $ with no leading zeros.

It is guaranteed that the sum of $ k $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer representing the bitwise XOR of the median of all good sequences $ a $ of length $ n $ where $ 0\le a_i < m $ .

## 说明/提示

In the first example, $ n = 10_2 = 2 $ and $ m = 3 $ . All possible sequences with elements less than $ m $ are: $ [0, 0] $ , $ [0, 1] $ , $ [0, 2] $ , $ [1, 0] $ , $ [1, 1] $ , $ [1, 2] $ , $ [2, 0] $ , $ [2, 1] $ , $ [2, 2] $ . All of them are good, so the answer is: $ 0 \oplus 0 \oplus 0 \oplus 0 \oplus 1 \oplus 1 \oplus 0 \oplus 1 \oplus 2 = 3 $ .

In the second example, $ n = 11_2 = 3 $ and $ m = 3 $ . Some good sequences are $ [2, 2, 2] $ , $ [1, 0, 1] $ , and $ [2, 0, 1] $ . However, a sequence $ [2, 0, 0] $ is not good, because $ \text{cnt}_0 = 2 $ , $ \text{cnt}_2 = 1 $ . Therefore, if we set $ i = 0 $ and $ j = 2 $ , $ i < j $ holds, but $ \text{cnt}_i \le \text{cnt}_j $ does not.

## 样例 #1

### 输入

```
6
2 3
10
2 3
11
5 1
11101
7 9
1101011
17 34
11001010001010010
1 1000000000
1
```

### 输出

```
3
2
0
8
32
0
```

