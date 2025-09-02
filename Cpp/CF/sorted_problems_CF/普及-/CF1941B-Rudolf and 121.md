---
title: "Rudolf and 121"
layout: "post"
diff: 普及-
pid: CF1941B
tag: ['贪心']
---

# Rudolf and 121

## 题目描述

Rudolf has an array $ a $ of $ n $ integers, the elements are numbered from $ 1 $ to $ n $ .

In one operation, he can choose an index $ i $ ( $ 2 \le i \le n - 1 $ ) and assign:

- $ a_{i - 1} = a_{i - 1} - 1 $
- $ a_i = a_i - 2 $
- $ a_{i + 1} = a_{i + 1} - 1 $

Rudolf can apply this operation any number of times. Any index $ i $ can be used zero or more times.

Can he make all the elements of the array equal to zero using this operation?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

The first line of each case contains a single integer $ n $ ( $ 3 \le n \le 2 \cdot 10^5 $ ) — the number of elements in the array.

The second line of each case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_j \le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of the values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if it is possible to make all the elements of the array zero using the described operations. Otherwise, output "NO".

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the first example, the original array is $ [1, 3, 5, 5, 2] $ , to make all its elements zero, Rudolf can act as follows:

- apply the operation at $ i=4 $ and get the array $ [1, 3, 4, 3, 1] $ ;
- apply the operation at $ i=3 $ and get the array $ [1, 2, 2, 2, 1] $ ;
- apply the operation at $ i=2 $ and get the array $ [0, 0, 1, 2, 1] $ ;
- apply the operation at $ i=4 $ and get the array $ [0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7
5
1 3 5 5 2
5
2 4 4 5 1
5
0 1 3 3 1
6
5 6 0 2 3 0
4
1 2 7 2
3
7 1 0
4
1 1 1 1
```

### 输出

```
YES
NO
YES
NO
NO
NO
NO
```

