---
title: "Stop Gaming (Easy Version)"
layout: "post"
diff: 难度0
pid: CF2059E1
tag: []
---

# Stop Gaming (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that in this version you only need to find the minimum number of operations. You can hack only if you solved all versions of this problem.

You are given $ n $ arrays, each of which has a length of $ m $ . Let the $ j $ -th element of the $ i $ -th array be denoted as $ a_{i, j} $ . It is guaranteed that all $ a_{i, j} $ are pairwise distinct. In one operation, you can do the following:

- Choose some integer $ i $ ( $ 1 \le i \le n $ ) and an integer $ x $ ( $ 1 \le x \le 2 \cdot n \cdot m $ ).
- For all integers $ k $ from $ i $ to $ n $ in increasing order, do the following: 
  1. Add the element $ x $ to the beginning of the $ k $ -th array.
  2. Assign $ x $ the value of the last element in the $ k $ -th array.
  3. Remove the last element from the $ k $ -th array.

In other words, you can insert an element at the beginning of any array, after which all elements in this and all following arrays are shifted by one to the right. The last element of the last array is removed.

You are also given a description of the arrays that need to be obtained after all operations. That is, after performing the operations, the $ j $ -th element of the $ i $ -th array should be equal to $ b_{i, j} $ . It is guaranteed that all $ b_{i, j} $ are pairwise distinct.

Determine the minimum number of operations that need to be performed to obtain the desired arrays.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 3 \cdot 10^5 $ ) — the number of arrays and the number of elements in each array.

The $ i $ -th of the following $ n $ lines contains $ m $ integers $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, m} $ ( $ 1 \le a_{i, j} \le 2 \cdot n \cdot m $ ) — the elements of the $ i $ -th original array. It is guaranteed that all $ a_{i, j} $ are pairwise distinct.

The $ i $ -th of the following $ n $ lines contains $ m $ integers $ b_{i, 1}, b_{i, 2}, \ldots, b_{i, m} $ ( $ 1 \le b_{i, j} \le 2 \cdot n \cdot m $ ) — the elements of the $ i $ -th final array. It is guaranteed that all $ b_{i, j} $ are pairwise distinct.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations that need to be performed.

## 说明/提示

In the first test case, the following sequence of $ 3 $ operations is suitable:

- Apply the operation to the first array with $ x = 1 $ . Then the element $ 1 $ will be added to the beginning of the first array, and the value of $ x $ will become $ 6 $ . The last element will be removed, and the first array will look like $ [1, 2] $ . Next, the element $ x $ is added to the beginning of the second array, and the value of $ x $ becomes $ 4 $ . The last element of the second array is removed, and both arrays look like $ [1, 2] $ and $ [6, 3] $ respectively after the first operation.
- Apply the operation to the second array with $ x = 8 $ . Then the first array remains unchanged, and both arrays will look like $ [1, 2] $ and $ [8, 6] $ respectively.
- Apply the operation to the second array with $ x = 7 $ , then both arrays will have the required appearance $ [1, 2] $ and $ [7, 8] $ respectively.

In the second test case, the desired array can only be achieved in $ 5 $ operations.

In the third test case, the following sequence of $ 3 $ operations is suitable:

- Apply the operation with $ x = 11 $ to the first array.
- Apply the operation with $ x = 12 $ to the second array.
- Apply the operation with $ x = 13 $ to the third array.

## 样例 #1

### 输入

```
4
2 2
2 6
3 4
1 2
7 8
1 5
5 4 1 2 3
5 4 3 2 1
3 3
1 2 3
4 5 6
7 8 9
11 1 2
12 3 4
13 5 6
4 4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
17 1 2 3
4 18 5 6
7 19 8 20
9 21 22 10
```

### 输出

```
3
5
3
6
```

