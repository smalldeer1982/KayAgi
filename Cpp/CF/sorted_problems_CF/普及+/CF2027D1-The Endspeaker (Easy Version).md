---
title: "The Endspeaker (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2027D1
tag: ['动态规划 DP', '二分']
---

# The Endspeaker (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is that you only need to output the minimum total cost of operations in this version. You must solve both versions to be able to hack.

You're given an array $ a $ of length $ n $ , and an array $ b $ of length $ m $ ( $ b_i > b_{i+1} $ for all $ 1 \le i < m $ ). Initially, the value of $ k $ is $ 1 $ . Your aim is to make the array $ a $ empty by performing one of these two operations repeatedly:

- Type $ 1 $ — If the value of $ k $ is less than $ m $ and the array $ a $ is not empty, you can increase the value of $ k $ by $ 1 $ . This does not incur any cost.
- Type $ 2 $ — You remove a non-empty prefix of array $ a $ , such that its sum does not exceed $ b_k $ . This incurs a cost of $ m - k $ .

You need to minimize the total cost of the operations to make array $ a $ empty. If it's impossible to do this through any sequence of operations, output $ -1 $ . Otherwise, output the minimum total cost of the operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 3 \cdot 10^5 $ , $ \boldsymbol{1 \le n \cdot m \le 3 \cdot 10^5} $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The third line of each test case contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le 10^9 $ ).

It is also guaranteed that $ b_i > b_{i+1} $ for all $ 1 \le i < m $ .

It is guaranteed that the sum of $ \boldsymbol{n \cdot m} $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, if it's possible to make $ a $ empty, then output the minimum total cost of the operations.

If there is no possible sequence of operations which makes $ a $ empty, then output a single integer $ -1 $ .

## 说明/提示

In the first test case, one optimal sequence of operations which yields a total cost of $ 1 $ is as follows:

- Perform an operation of type $ 2 $ . Choose the prefix to be $ [9] $ . This incurs a cost of $ 1 $ .
- Perform an operation of type $ 1 $ . The value of $ k $ is now $ 2 $ . This incurs no cost.
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3, 4] $ . This incurs a cost of $ 0 $ .
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3] $ . This incurs a cost of $ 0 $ .
- The array $ a $ is now empty, and the total cost of all operations is $ 1 $ .

In the second test case, it's impossible to remove any prefix of the array since $ a_1 > b_1 $ , so array $ a $ cannot be made empty by any sequence of operations.

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1
```

### 输出

```
1
-1
2
10
4
```

