---
title: "GCD on a grid"
layout: "post"
diff: 普及+/提高
pid: CF1955G
tag: ['动态规划 DP', '搜索', '数论']
---

# GCD on a grid

## 题目描述

Not long ago, Egor learned about the Euclidean algorithm for finding the greatest common divisor of two numbers. The greatest common divisor of two numbers $ a $ and $ b $ is the largest number that divides both $ a $ and $ b $ without leaving a remainder. With this knowledge, Egor can solve a problem that he once couldn't.

Vasily has a grid with $ n $ rows and $ m $ columns, and the integer $ {a_i}_j $ is located at the intersection of the $ i $ -th row and the $ j $ -th column. Egor wants to go from the top left corner (at the intersection of the first row and the first column) to the bottom right corner (at the intersection of the last row and the last column) and find the greatest common divisor of all the numbers along the path. He is only allowed to move down and to the right. Egor has written down several paths and obtained different GCD values. He became interested in finding the maximum possible GCD.

Unfortunately, Egor is tired of calculating GCDs, so he asks for your help in finding the maximum GCD of the integers along the path from the top left corner to the bottom right corner of the grid.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le {10}^{4} $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 100 $ ) — the number of rows and columns of the grid.

Then, there are $ n $ lines, where the $ i $ -th line contains $ m $ integers $ (1 \le a_{i,j} \le {10}^{6} $ ) — the integers written in the $ i $ -th row and the $ j $ -th column of the grid.

It is guaranteed that the sum of $ n \cdot m $ does not exceed $ 2 \cdot {10}^{5} $ over all test cases.

## 输出格式

For each test case, output the maximum possible GCD along the path from the top left cell to the bottom right cell in a separate line.

## 样例 #1

### 输入

```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9
```

### 输出

```
10
3
1
```

