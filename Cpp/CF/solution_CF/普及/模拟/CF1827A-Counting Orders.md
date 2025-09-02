# Counting Orders

## 题目描述

You are given two arrays $ a $ and $ b $ each consisting of $ n $ integers. All elements of $ a $ are pairwise distinct.

Find the number of ways to reorder $ a $ such that $ a_i > b_i $ for all $ 1 \le i \le n $ , modulo $ 10^9 + 7 $ .

Two ways of reordering are considered different if the resulting arrays are different.

## 样例 #1

### 输入

```
5
6
9 6 8 4 5 2
4 1 5 6 3 1
3
4 3 2
3 4 9
1
2
1
3
2 3 4
1 3 3
12
2 3 7 10 23 28 29 50 69 135 420 1000
1 1 2 3 5 8 13 21 34 55 89 144```

### 输出

```
32
0
1
0
13824```

