---
title: "Almost Triple Deletions"
layout: "post"
diff: 提高+/省选-
pid: CF1699D
tag: ['贪心', '区间 DP']
---

# Almost Triple Deletions

## 题目描述

You are given an integer $ n $ and an array $ a_1,a_2,\ldots,a_n $ .

In one operation, you can choose an index $ i $ ( $ 1 \le i \lt n $ ) for which $ a_i \neq a_{i+1} $ and delete both $ a_i $ and $ a_{i+1} $ from the array. After deleting $ a_i $ and $ a_{i+1} $ , the remaining parts of the array are concatenated.

For example, if $ a=[1,4,3,3,6,2] $ , then after performing an operation with $ i=2 $ , the resulting array will be $ [1,3,6,2] $ .

What is the maximum possible length of an array of equal elements obtainable from $ a $ by performing several (perhaps none) of the aforementioned operations?

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The following lines contain the descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) — the elements of array $ a $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10\,000 $ .

## 输出格式

For each testcase, print a single integer, the maximum possible length of an array of equal elements obtainable from $ a $ by performing a sequence of operations.

## 说明/提示

For the first testcase, an optimal sequence of operations would be: $ [1,2,3,2,1,3,3] \rightarrow [3,2,1,3,3] \rightarrow [3,3,3] $ .

For the second testcase, all elements in the array are already equal.

For the third testcase, the only possible sequence of operations is: $ [1,1,1,2,2,2] \rightarrow [1,1,2,2] \rightarrow [1,2] \rightarrow [] $ . Note that, according to the statement, the elements deleted at each step must be different.

For the fourth testcase, the optimal sequence of operations is: $ [1,1,2,2,3,3,1,1] \rightarrow [1,1,2,3,1,1] \rightarrow [1,1,1,1] $ .

For the fifth testcase, one possible reachable array of two equal elements is $ [4,4] $ .

## 样例 #1

### 输入

```
5
7
1 2 3 2 1 3 3
1
1
6
1 1 1 2 2 2
8
1 1 2 2 3 3 1 1
12
1 5 2 3 3 3 4 4 4 4 3 3
```

### 输出

```
3
1
0
4
2
```

