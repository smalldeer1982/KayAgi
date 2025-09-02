---
title: "Shifts and Swaps"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2118F
tag: []
---

# Shifts and Swaps

## 题目描述

You are given arrays $ a $ and $ b $ of length $ n $ and an integer $ m $ .

The arrays only contain integers from $ 1 $ to $ m $ , and both arrays contain all integers from $ 1 $ to $ m $ .

You may repeatedly perform either of the following operations on $ a $ :

- cyclic shift $ ^{\text{∗}} $ the array to the left
- swap two neighboring elements if their difference is at least $ 2 $ .

Is it possible to transform the first array into the second?

 $ ^{\text{∗}} $ A left cyclic shift of a zero-indexed array $ p $ of length $ n $ is an array $ q $ such that $ q_i = p_{(i + 1) \bmod n} $ for all $ 0 \le i < n $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le m \le n \le 5\cdot10^5 $ ) — the length of the arrays and the number of distinct elements in $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le m $ ) — denoting the array $ a $ .

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le m $ ) — denoting the array $ b $ .

It is guaranteed that both arrays contain all integers from $ 1 $ to $ m $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5\cdot10^5 $ .

## 输出格式

For each test case, output "YES" if it is possible to transform the first array into the second and "NO" otherwise. You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, you can transform array $ a $ into array $ b $ with the following steps:

- \[ $ 1 $ , $ 2 $ , $ 3 $ \] — shift to the left
- \[ $ 2 $ , $ 3 $ , $ 1 $ \] — swap indices $ 2 $ and $ 3 $
- \[ $ 2 $ , $ 1 $ , $ 3 $ \] — shift to the left
- \[ $ 1 $ , $ 3 $ , $ 2 $ \] — shift to the left
- \[ $ 3 $ , $ 2 $ , $ 1 $ \]

In the second test case, it can be proven that it is impossible to transform array $ a $ into array $ b $ with the given operations.

## 样例 #1

### 输入

```
8
3 3
1 2 3
3 2 1
4 3
1 1 2 3
1 2 2 3
4 4
1 3 2 4
2 3 4 1
6 3
1 1 2 1 2 3
2 1 1 2 3 1
5 4
2 3 4 1 1
3 2 1 1 4
9 7
2 4 6 7 3 1 5 4 6
6 7 3 5 6 4 2 4 1
9 8
8 3 5 6 5 4 1 7 2
7 5 3 5 8 4 6 2 1
8 6
2 1 5 4 6 3 5 4
6 1 5 2 4 5 3 4
```

### 输出

```
YES
NO
YES
NO
YES
YES
NO
NO
```

