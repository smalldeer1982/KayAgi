---
title: "Copil Copac Draws Trees"
layout: "post"
diff: 普及/提高-
pid: CF1830A
tag: []
---

# Copil Copac Draws Trees

## 题目描述

Copil Copac is given a list of $ n-1 $ edges describing a tree of $ n $ vertices. He decides to draw it using the following algorithm:

- Step $ 0 $ : Draws the first vertex (vertex $ 1 $ ). Go to step $ 1 $ .
- Step $ 1 $ : For every edge in the input, in order: if the edge connects an already drawn vertex $ u $ to an undrawn vertex $ v $ , he will draw the undrawn vertex $ v $ and the edge. After checking every edge, go to step $ 2 $ .
- Step $ 2 $ : If all the vertices are drawn, terminate the algorithm. Else, go to step $ 1 $ .

The number of readings is defined as the number of times Copil Copac performs step $ 1 $ .

Find the number of readings needed by Copil Copac to draw the tree.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices of the tree.

The following $ n - 1 $ lines of each test case contain two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $ ) — indicating that $ (u_i,v_i) $ is the $ i $ -th edge in the list. It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the number of readings Copil Copac needs to draw the tree.

## 说明/提示

In the first test case:

After the first reading, the tree will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/96592d8d6a7376d06a499045a206685f9a68df31.png)After the second reading:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/7b7bd2d2b1a9ad0d44021bb292052bd1a2395dfd.png)Therefore, Copil Copac needs $ 2 $ readings to draw the tree.

## 样例 #1

### 输入

```
2
6
4 5
1 3
1 2
3 4
1 6
7
5 6
2 4
2 7
1 3
1 2
4 5
```

### 输出

```
2
3
```

