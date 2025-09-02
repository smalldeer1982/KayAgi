---
title: "Darth Vader and Tree"
layout: "post"
diff: 提高+/省选-
pid: CF514E
tag: ['动态规划 DP', '动态规划优化', '矩阵加速']
---

# Darth Vader and Tree

## 题目描述

When Darth Vader gets bored, he sits down on the sofa, closes his eyes and thinks of an infinite rooted tree where each node has exactly $ n $ sons, at that for each node, the distance between it an its $ i $ -th left child equals to $ d_{i} $ . The Sith Lord loves counting the number of nodes in the tree that are at a distance at most $ x $ from the root. The distance is the sum of the lengths of edges on the path between nodes.

But he has got used to this activity and even grew bored of it. 'Why does he do that, then?' — you may ask. It's just that he feels superior knowing that only he can solve this problem.

Do you want to challenge Darth Vader himself? Count the required number of nodes. As the answer can be rather large, find it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two space-separated integers $ n $ and $ x $ ( $ 1<=n<=10^{5},0<=x<=10^{9} $ ) — the number of children of each node and the distance from the root within the range of which you need to count the nodes.

The next line contains $ n $ space-separated integers $ d_{i} $ ( $ 1<=d_{i}<=100 $ ) — the length of the edge that connects each node with its $ i $ -th child.

## 输出格式

Print a single number — the number of vertexes in the tree at distance from the root equal to at most $ x $ .

## 说明/提示

Pictures to the sample (the yellow color marks the nodes the distance to which is at most three)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514E/dfa75ce6cc0df1087a16e02cadbd273a08641d03.png)

## 样例 #1

### 输入

```
3 3
1 2 3

```

### 输出

```
8

```

