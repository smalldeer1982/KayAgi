---
title: "Sakurako and Chefir"
layout: "post"
diff: 提高+/省选-
pid: CF2033G
tag: ['动态规划 DP', '倍增']
---

# Sakurako and Chefir

## 题目描述

Given a tree with $ n $ vertices rooted at vertex $ 1 $ . While walking through it with her cat Chefir, Sakurako got distracted, and Chefir ran away.

To help Sakurako, Kosuke recorded his $ q $ guesses. In the $ i $ -th guess, he assumes that Chefir got lost at vertex $ v_i $ and had $ k_i $ stamina.

Also, for each guess, Kosuke assumes that Chefir could move along the edges an arbitrary number of times:

- from vertex $ a $ to vertex $ b $ , if $ a $ is an ancestor $ ^{\text{∗}} $ of $ b $ , the stamina will not change;
- from vertex $ a $ to vertex $ b $ , if $ a $ is not an ancestor of $ b $ , then Chefir's stamina decreases by $ 1 $ .

If Chefir's stamina is $ 0 $ , he cannot make a move of the second type.

For each assumption, your task is to find the distance to the farthest vertex that Chefir could reach from vertex $ v_i $ , having $ k_i $ stamina.

 $ ^{\text{∗}} $ Vertex $ a $ is an ancestor of vertex $ b $ if the shortest path from $ b $ to the root passes through $ a $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described as follows:

- The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.
- The next $ n-1 $ lines contain the edges of the tree. It is guaranteed that the given edges form a tree.
- The next line consists of a single integer $ q $ $ (1\le q\le 2 \cdot 10^5) $ , which denotes the number of guesses made by Kosuke.
- The next $ q $ lines describe the guesses made by Kosuke, with two integers $ v_i $ , $ k_i $ $ (1\le v_i \le n, 0 \le k_i\le n) $ .

It is guaranteed that the sum of $ n $ and the sum of $ q $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case and for each guess, output the maximum distance to the farthest vertex that Chefir could reach from the starting point $ v_i $ having $ k_i $ stamina.

## 说明/提示

In the first example:

- In the first query, you can go from vertex $ 5 $ to vertex $ 3 $ (after which your stamina will decrease by $ 1 $ and become $ 0 $ ), and then you can go to vertex $ 4 $ ;
- In the second query, from vertex $ 3 $ with $ 1 $ stamina, you can only reach vertices $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ ;
- In the third query, from vertex $ 2 $ with $ 0 $ stamina, you can only reach vertices $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ ;

## 样例 #1

### 输入

```
3
5
1 2
2 3
3 4
3 5
3
5 1
3 1
2 0
9
8 1
1 7
1 4
7 3
4 9
3 2
1 5
3 6
7
6 0
2 3
6 2
8 2
2 4
9 2
6 3
6
2 1
2 5
2 4
5 6
4 3
3
3 1
1 3
6 5
```

### 输出

```
2 1 2 
0 5 2 4 5 5 5 
1 3 4
```

