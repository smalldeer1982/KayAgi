---
title: "Bipartite Array"
layout: "post"
diff: 省选/NOI-
pid: CF1620F
tag: []
---

# Bipartite Array

## 题目描述

You are given a permutation $ p $ consisting of $ n $ integers $ 1, 2, \dots, n $ (a permutation is an array where each element from $ 1 $ to $ n $ occurs exactly once).

Let's call an array $ a $ bipartite if the following undirected graph is bipartite:

- the graph consists of $ n $ vertices;
- two vertices $ i $ and $ j $ are connected by an edge if $ i < j $ and $ a_i > a_j $ .

Your task is to find a bipartite array of integers $ a $ of size $ n $ , such that $ a_i = p_i $ or $ a_i = -p_i $ , or report that no such array exists. If there are multiple answers, print any of them.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the size of the permutation.

The second line contains $ n $ integers $ p_1, p_2, \dots, p_n $ .

The sum of $ n $ over all test cases doesn't exceed $ 10^6 $ .

## 输出格式

For each test case, print the answer in the following format. If such an array $ a $ does not exist, print "NO" in a single line. Otherwise, print "YES" in the first line and $ n $ integers — array $ a $ in the second line.

## 样例 #1

### 输入

```
4
3
1 2 3
6
1 3 2 6 5 4
4
4 1 3 2
8
3 2 1 6 7 8 5 4
```

### 输出

```
YES
1 2 3
NO
YES
-4 -1 -3 -2
YES
-3 -2 1 6 7 -8 -5 -4
```

