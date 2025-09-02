---
title: "Matching Arrays"
layout: "post"
diff: 普及+/提高
pid: CF1896C
tag: ['贪心', '排序']
---

# Matching Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of size $ n $ . The beauty of the arrays $ a $ and $ b $ is the number of indices $ i $ such that $ a_i > b_i $ .

You are also given an integer $ x $ . Determine whether it is possible to rearrange the elements of $ b $ such that the beauty of the arrays becomes $ x $ . If it is possible, output one valid rearrangement of $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le n \le 2\cdot 10^5 $ , $ 0 \le x \le n $ ) — the size of arrays $ a $ and $ b $ and the desired beauty of the arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2n $ ) — the elements of array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 2n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output "NO" if it is not possible to rearrange $ b $ to make the beauty of the arrays equal to $ x $ .

Otherwise, output "YES". Then, on the next line, output $ n $ integers which represent the rearrangement of $ b $ .

If there are multiple solutions, you may output any of them.

You can output "YES" and "NO" in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In test cases 1 and 2, the beauty of the arrays has to be $ 0 $ since $ a_1 = 1 \le 2 = b_1 $ .

In test cases 3, 4, 5 and 6, the only possible beauty of the arrays is $ x = 1 $ and $ x = 2 $ . In particular, if $ b $ is rearranged to $ [2, 4, 1] $ , then $ a_3 = 3 > 1 = b_3 $ , so the beauty of the arrays is $ 1 $ . If $ b $ is kept in the same order as given the input, then $ a_2 = 4 > b_2 = 1 $ and $ a_3 = 3 > 2 = b_3 $ , so the beauty of the arrays is $ 2 $ .

## 样例 #1

### 输入

```
7
1 0
1
2
1 1
1
2
3 0
2 4 3
4 1 2
3 1
2 4 3
4 1 2
3 2
2 4 3
4 1 2
3 3
2 4 3
4 1 2
5 2
6 4 5 6 2
9 7 9 1 1
```

### 输出

```
YES
2
NO
NO
YES
2 4 1
YES
4 1 2
NO
YES
1 9 9 7 1
```

