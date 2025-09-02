# Showstopper

## 题目描述

You are given two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

In one operation, you can choose any integer $ i $ from $ 1 $ to $ n $ and swap the numbers $ a_i $ and $ b_i $ .

Determine whether, after using any (possibly zero) number of operations, the following two conditions can be satisfied simultaneously:

- $ a_n = \max(a_1, a_2, \ldots, a_n) $ ,
- $ b_n = \max(b_1, b_2, \ldots, b_n) $ .

Here $ \max(c_1, c_2, \ldots, c_k) $ denotes the maximum number among $ c_1, c_2, \ldots, c_k $ . For example, $ \max(3, 5, 4) = 5 $ , $ \max(1, 7, 7) = 7 $ , $ \max(6, 2) = 6 $ .

## 说明/提示

In the first test case, you can swap the numbers $ a_3 $ and $ b_3 $ , after which the array $ a $ becomes equal to $ [7, 9, 9] $ , and the array $ b $ becomes equal to $ [7, 6, 7] $ , and both conditions are met.

In the second test case, it can be proved that it is impossible to satisfy both conditions.

In the third test case, you can swap the numbers $ a_1 $ and $ b_1 $ , after which the array $ a $ becomes equal to $ [99, 99] $ , and the array $ b $ becomes equal to $ [100, 100] $ , and both conditions are satisfied.

In fifth test case, you can swap $ a_7 $ and $ b_7 $ , $ a_8 $ and $ b_8 $ , $ a_9 $ and $ b_9 $ , after which the array $ a $ becomes equal to $ [1, 2, 3, 4, 5, 6, 6, 6, 6] $ , and the array $ b $ becomes equal to $ [9, 9, 9, 9, 9, 9, 7, 8, 9] $ , and both conditions are satisfied.

## 样例 #1

### 输入

```
7
3
7 9 7
7 6 9
4
10 10 15 15
10 16 15 15
2
100 99
99 100
1
1
1
9
1 2 3 4 5 6 7 8 9
9 9 9 9 9 9 6 6 6
7
1 1 2 2 1 1 2
1 2 1 2 1 2 1
2
30 4
5 30```

### 输出

```
Yes
No
Yes
Yes
Yes
No
No```

