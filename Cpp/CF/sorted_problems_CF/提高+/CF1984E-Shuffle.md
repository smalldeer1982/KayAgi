---
title: "Shuffle"
layout: "post"
diff: 提高+/省选-
pid: CF1984E
tag: ['树形 DP']
---

# Shuffle

## 题目描述

Two hungry red pandas, Oscar and Lura, have a tree $ T $ with $ n $ nodes. They are willing to perform the following shuffle procedure on the whole tree $ T $ exactly once. With this shuffle procedure, they will create a new tree out of the nodes of the old tree.

1. Choose any node $ V $ from the original tree $ T $ . Create a new tree $ T_2 $ , with $ V $ as the root.
2. Remove $ V $ from $ T $ , such that the original tree is split into one or more subtrees (or zero subtrees, if $ V $ is the only node in $ T $ ).
3. Shuffle each subtree with the same procedure (again choosing any node as the root), then connect all shuffled subtrees' roots back to $ V $ to finish constructing $ T_2 $ .

After this, Oscar and Lura are left with a new tree $ T_2 $ . They can only eat leaves and are very hungry, so please find the maximum number of leaves over all trees that can be created in exactly one shuffle.

Note that leaves are all nodes with degree $ 1 $ . Thus, the root may be considered as a leaf if it has only one child.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of every test case contains a single integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the number of nodes within the original tree $ T $ .

The next $ n - 1 $ lines each contain two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n $ ) — an edge within the original tree $ T $ . The given edges form a tree.

The sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum number of leaves achievable with exactly one shuffle procedure on the whole tree.

## 说明/提示

In the first test case, it can be shown that the maximum number of leaves is $ 4 $ . To accomplish this, we can start our shuffle with selecting node $ 3 $ as the new root.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/0496f1e53b8faef700719d0f92212c9f9e0075c9.png)  Next, we are left only with one subtree, in which we can select node $ 2 $ to be the new root of that subtree.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/a280b18a5bea58b0f12cdd08ee4e52dbe699c78a.png)  This will force all $ 3 $ remaining nodes to be leaves, and once we connect them back to our new root, the shuffled subtree looks like this:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/7cf63ffdc63a80cf27ff8fce3a8da6cd1e9078f0.png)  We connect the shuffled subtree back to our new root of our new tree. Our final tree has four leaves (including the root), and looks like this:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984E/4a077e6e7f7254d7c89391723da6791d33896856.png)In our second test case, we have a line of five nodes. It can be shown that the maximum number of leaves after one shuffle is $ 3 $ . We can start off with node $ 2 $ , which forces node $ 1 $ to become a leaf. Then, if we select node $ 4 $ on the right side, we will also have nodes $ 3 $ and $ 5 $ as leaves.

The third test case is a star graph with six nodes. The number of leaves cannot increase, thus our answer will be $ 5 $ (if we start the shuffling with the original root node).

## 样例 #1

### 输入

```
4
5
1 2
1 3
2 4
2 5
5
1 2
2 3
3 4
4 5
6
1 2
1 3
1 4
1 5
1 6
10
9 3
8 1
10 6
8 5
7 8
4 6
1 3
10 1
2 7
```

### 输出

```
4
3
5
6
```

