---
title: "Red and Blue"
layout: "post"
diff: 普及-
pid: CF1469B
tag: []
---

# Red and Blue

## 题目描述

Monocarp had a sequence $ a $ consisting of $ n + m $ integers $ a_1, a_2, \dots, a_{n + m} $ . He painted the elements into two colors, red and blue; $ n $ elements were painted red, all other $ m $ elements were painted blue.

After painting the elements, he has written two sequences $ r_1, r_2, \dots, r_n $ and $ b_1, b_2, \dots, b_m $ . The sequence $ r $ consisted of all red elements of $ a $ in the order they appeared in $ a $ ; similarly, the sequence $ b $ consisted of all blue elements of $ a $ in the order they appeared in $ a $ as well.

Unfortunately, the original sequence was lost, and Monocarp only has the sequences $ r $ and $ b $ . He wants to restore the original sequence. In case there are multiple ways to restore it, he wants to choose a way to restore that maximizes the value of

 $ $$$f(a) = \max(0, a_1, (a_1 + a_2), (a_1 + a_2 + a_3), \dots, (a_1 + a_2 + a_3 + \dots + a_{n + m})) $ $ </p><p>Help Monocarp to calculate the maximum possible value of  $ f(a)$$$.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Then the test cases follow. Each test case consists of four lines.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 100 $ ).

The second line contains $ n $ integers $ r_1, r_2, \dots, r_n $ ( $ -100 \le r_i \le 100 $ ).

The third line contains one integer $ m $ ( $ 1 \le m \le 100 $ ).

The fourth line contains $ m $ integers $ b_1, b_2, \dots, b_m $ ( $ -100 \le b_i \le 100 $ ).

## 输出格式

For each test case, print one integer — the maximum possible value of $ f(a) $ .

## 说明/提示

In the explanations for the sample test cases, red elements are marked as bold.

In the first test case, one of the possible sequences $ a $ is $ [\mathbf{6}, 2, \mathbf{-5}, 3, \mathbf{7}, \mathbf{-3}, -4] $ .

In the second test case, one of the possible sequences $ a $ is $ [10, \mathbf{1}, -3, \mathbf{1}, 2, 2] $ .

In the third test case, one of the possible sequences $ a $ is $ [\mathbf{-1}, -1, -2, -3, \mathbf{-2}, -4, -5, \mathbf{-3}, \mathbf{-4}, \mathbf{-5}] $ .

In the fourth test case, one of the possible sequences $ a $ is $ [0, \mathbf{0}] $ .

## 样例 #1

### 输入

```
4
4
6 -5 7 -3
3
2 3 -4
2
1 1
4
10 -3 2 2
5
-1 -2 -3 -4 -5
5
-1 -2 -3 -4 -5
1
0
1
0
```

### 输出

```
13
13
0
0
```

