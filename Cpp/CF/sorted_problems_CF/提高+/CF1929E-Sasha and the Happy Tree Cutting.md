---
title: "Sasha and the Happy Tree Cutting"
layout: "post"
diff: 提高+/省选-
pid: CF1929E
tag: []
---

# Sasha and the Happy Tree Cutting

## 题目描述

Sasha was given a tree $ ^{\dagger} $ with $ n $ vertices as a prize for winning yet another competition. However, upon returning home after celebrating his victory, he noticed that some parts of the tree were missing. Sasha remembers that he colored some of the edges of this tree. He is certain that for any of the $ k $ pairs of vertices $ (a_1, b_1), \ldots, (a_k, b_k) $ , he colored at least one edge on the simple path $ ^{\ddagger} $ between vertices $ a_i $ and $ b_i $ .

Sasha does not remember how many edges he exactly colored, so he asks you to tell him the minimum number of edges he could have colored to satisfy the above condition.

 $ ^{\dagger} $ A tree is an undirected connected graph without cycles.

 $ ^{\ddagger} $ A simple path is a path that passes through each vertex at most once.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 10^5 $ ) — the number of vertices in the tree.

The next $ (n - 1) $ lines describe the edges of the tree. The $ i $ -th line contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \ne v_i $ ) — the numbers of the vertices connected by the $ i $ -th edge.

The next line contains a single integer $ k $ ( $ 1 \leq k \leq 20 $ ) — the number of pairs of vertices between which Sasha colored at least one edge on a simple path.

The next $ k $ lines describe pairs. The $ j $ -th line contains two integers $ a_j $ and $ b_j $ ( $ 1 \leq a_j, b_j \leq n, a_j \neq b_j $ ) — the vertices in the $ j $ -th pair.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ . It is guaranteed that the sum of $ 2^k $ over all test cases does not exceed $ 2^{20} $ .

## 输出格式

For each test case, output a single integer — the minimum number of edges Sasha could have colored.

## 说明/提示

In the first test case, Sasha could have colored only one edge $ (1, 2) $ . Then, there would be at least one colored edge on the simple path between vertices $ 1 $ and $ 3 $ , and vertices $ 4 $ and $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929E/a12ac27221d04aa56e014cbf2e8421ab5e15a544.png)In the second test case, Sasha could have colored the edges $ (1, 6) $ and $ (1, 3) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929E/6df2f20069f97a0b34db8fc6f8d67fe5a3f5659b.png)

## 样例 #1

### 输入

```
3
4
1 2
2 3
2 4
2
1 3
4 1
6
1 2
3 1
6 1
5 2
4 2
3
3 1
3 6
2 6
5
1 2
2 3
3 4
4 5
4
1 2
2 3
3 4
4 5
```

### 输出

```
1
2
4
```

