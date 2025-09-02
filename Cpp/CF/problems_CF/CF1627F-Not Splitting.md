---
title: "Not Splitting"
layout: "post"
diff: 省选/NOI-
pid: CF1627F
tag: []
---

# Not Splitting

## 题目描述

There is a $ k \times k $ grid, where $ k $ is even. The square in row $ r $ and column $ c $ is denoted by $ (r,c) $ . Two squares $ (r_1, c_1) $ and $ (r_2, c_2) $ are considered adjacent if $ \lvert r_1 - r_2 \rvert + \lvert c_1 - c_2 \rvert = 1 $ .

An array of adjacent pairs of squares is called strong if it is possible to cut the grid along grid lines into two connected, [congruent](https://en.wikipedia.org/wiki/Congruence_(geometry)) pieces so that each pair is part of the same piece. Two pieces are congruent if one can be matched with the other by translation, rotation, and reflection, or a combination of these.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627F/7a1cba5ad185443613d7aa270876dfc93648efec.png) The picture above represents the first test case. Arrows indicate pairs of squares, and the thick black line represents the cut. You are given an array $ a $ of $ n $ pairs of adjacent squares. Find the size of the largest strong subsequence of $ a $ . An array $ p $ is a subsequence of an array $ q $ if $ p $ can be obtained from $ q $ by deletion of several (possibly, zero or all) elements.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two space-separated integers $ n $ and $ k $ ( $ 1 \leq n \leq 10^5 $ ; $ 2 \leq k \leq 500 $ ,  $ k $ is even) — the length of $ a $ and the size of the grid, respectively.

Then $ n $ lines follow. The $ i $ -th of these lines contains four space-separated integers $ r_{i,1} $ , $ c_{i,1} $ , $ r_{i,2} $ , and $ c_{i,2} $ ( $ 1 \leq r_{i,1}, c_{i,1}, r_{i,2}, c_{i,2} \leq k $ ) — the $ i $ -th element of $ a $ , represented by the row and column of the first square $ (r_{i,1}, c_{i,1}) $ and the row and column of the second square $ (r_{i,2}, c_{i,2}) $ . These squares are adjacent.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , and the sum of $ k $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output a single integer — the size of the largest strong subsequence of $ a $ .

## 说明/提示

In the first test case, the array $ a $ is not good, but if we take the subsequence $ [a_1, a_2, a_3, a_4, a_5, a_6, a_8] $ , then the square can be split as shown in the statement.

In the second test case, we can take the subsequence consisting of the last four elements of $ a $ and cut the square with a horizontal line through its center.

## 样例 #1

### 输入

```
3
8 4
1 2 1 3
2 2 2 3
3 2 3 3
4 2 4 3
1 4 2 4
2 1 3 1
2 2 3 2
4 1 4 2
7 2
1 1 1 2
2 1 2 2
1 1 1 2
1 1 2 1
1 2 2 2
1 1 2 1
1 2 2 2
1 6
3 3 3 4
```

### 输出

```
7
4
1
```

