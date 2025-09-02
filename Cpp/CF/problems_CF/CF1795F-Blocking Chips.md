---
title: "Blocking Chips"
layout: "post"
diff: 省选/NOI-
pid: CF1795F
tag: []
---

# Blocking Chips

## 题目描述

You are given a tree, consisting of $ n $ vertices. There are $ k $ chips, placed in vertices $ a_1, a_2, \dots, a_k $ . All $ a_i $ are distinct. Vertices $ a_1, a_2, \dots, a_k $ are colored black initially. The remaining vertices are white.

You are going to play a game where you perform some moves (possibly, zero). On the $ i $ -th move ( $ 1 $ -indexed) you are going to move the $ ((i - 1) \bmod k + 1) $ -st chip from its current vertex to an adjacent white vertex and color that vertex black. So, if $ k=3 $ , you move chip $ 1 $ on move $ 1 $ , chip $ 2 $ on move $ 2 $ , chip $ 3 $ on move $ 3 $ , chip $ 1 $ on move $ 4 $ , chip $ 2 $ on move $ 5 $ and so on. If there is no adjacent white vertex, then the game ends.

What's the maximum number of moves you can perform?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices of the tree.

Each of the next $ n - 1 $ lines contains two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ) — the descriptions of the edges. The given edges form a tree.

The next line contains a single integer $ k $ ( $ 1 \le k \le n $ ) — the number of chips.

The next line contains $ k $ integers $ a_1, a_2, \dots, a_k $ ( $ 1 \le a_i \le n $ ) — the vertices with the chips. All $ a_i $ are distinct.

The sum of $ n $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the maximum number of moves you can perform.

## 样例 #1

### 输入

```
5
5
1 2
2 3
3 4
4 5
1
3
5
1 2
2 3
3 4
4 5
2
1 2
5
1 2
2 3
3 4
4 5
2
2 1
6
1 2
1 3
2 4
2 5
3 6
3
1 4 6
1
1
1
```

### 输出

```
2
0
1
2
0
```

