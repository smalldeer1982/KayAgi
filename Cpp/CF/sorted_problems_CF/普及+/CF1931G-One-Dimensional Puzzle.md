---
title: "One-Dimensional Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF1931G
tag: ['组合数学', '分类讨论']
---

# One-Dimensional Puzzle

## 题目描述

You have a one-dimensional puzzle, all the elements of which need to be put in one row, connecting with each other. All the puzzle elements are completely white and distinguishable from each other only if they have different shapes.

Each element has straight borders at the top and bottom, and on the left and right it has connections, each of which can be a protrusion or a recess. You cannot rotate the elements.

You can see that there are exactly $ 4 $ types of elements. Two elements can be connected if the right connection of the left element is opposite to the left connection of the right element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png) All possible types of elements. The puzzle contains $ c_1, c_2, c_3, c_4 $ elements of each type. The puzzle is considered complete if you have managed to combine all elements into one long chain. You want to know how many ways this can be done.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of input test cases. The descriptions of the test cases follow.

The description of each test case contains $ 4 $ integers $ c_i $ ( $ 0 \le c_i \le 10^6 $ ) — the number of elements of each type, respectively.

It is guaranteed that the sum of $ c_i $ for all test cases does not exceed $ 4 \cdot 10^6 $ .

## 输出格式

For each test case, print one integer — the number of possible ways to solve the puzzle.

Two methods are considered different if there is $ i $ , such that the types of elements at the $ i $ position in these methods differ.

Since the answer can be very large, output it modulo $ 998244353 $ .

If it is impossible to solve the puzzle, print $ 0 $ .

## 样例 #1

### 输入

```
11
1 1 1 1
1 2 5 10
4 6 100 200
900000 900000 900000 900000
0 0 0 0
0 0 566 239
1 0 0 0
100 0 100 0
0 0 0 4
5 5 0 2
5 4 0 5
```

### 输出

```
4
66
0
794100779
1
0
1
0
1
36
126
```

