---
title: "Paint the Tree"
layout: "post"
diff: 普及+/提高
pid: CF1244D
tag: []
---

# Paint the Tree

## 题目描述

You are given a tree consisting of $ n $ vertices. A tree is an undirected connected acyclic graph.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1244D/0b019d9da08990633b2a6779b2699db8afb883d7.png)Example of a tree.You have to paint each vertex into one of three colors. For each vertex, you know the cost of painting it in every color.

You have to paint the vertices so that any path consisting of exactly three distinct vertices does not contain any vertices with equal colors. In other words, let's consider all triples $ (x, y, z) $ such that $ x \neq y, y \neq z, x \neq z $ , $ x $ is connected by an edge with $ y $ , and $ y $ is connected by an edge with $ z $ . The colours of $ x $ , $ y $ and $ z $ should be pairwise distinct. Let's call a painting which meets this condition good.

You have to calculate the minimum cost of a good painting and find one of the optimal paintings. If there is no good painting, report about it.

## 输入格式

The first line contains one integer $ n $ $ (3 \le n \le 100\,000) $ — the number of vertices.

The second line contains a sequence of integers $ c_{1, 1}, c_{1, 2}, \dots, c_{1, n} $ $ (1 \le c_{1, i} \le 10^{9}) $ , where $ c_{1, i} $ is the cost of painting the $ i $ -th vertex into the first color.

The third line contains a sequence of integers $ c_{2, 1}, c_{2, 2}, \dots, c_{2, n} $ $ (1 \le c_{2, i} \le 10^{9}) $ , where $ c_{2, i} $ is the cost of painting the $ i $ -th vertex into the second color.

The fourth line contains a sequence of integers $ c_{3, 1}, c_{3, 2}, \dots, c_{3, n} $ $ (1 \le c_{3, i} \le 10^{9}) $ , where $ c_{3, i} $ is the cost of painting the $ i $ -th vertex into the third color.

Then $ (n - 1) $ lines follow, each containing two integers $ u_j $ and $ v_j $ $ (1 \le u_j, v_j \le n, u_j \neq v_j) $ — the numbers of vertices connected by the $ j $ -th undirected edge. It is guaranteed that these edges denote a tree.

## 输出格式

If there is no good painting, print $ -1 $ .

Otherwise, print the minimum cost of a good painting in the first line. In the second line print $ n $ integers $ b_1, b_2, \dots, b_n $ $ (1 \le b_i \le 3) $ , where the $ i $ -th integer should denote the color of the $ i $ -th vertex. If there are multiple good paintings with minimum cost, print any of them.

## 说明/提示

All vertices should be painted in different colors in the first example. The optimal way to do it is to paint the first vertex into color $ 1 $ , the second vertex — into color $ 3 $ , and the third vertex — into color $ 2 $ . The cost of this painting is $ 3 + 2 + 1 = 6 $ .

## 样例 #1

### 输入

```
3
3 2 3
4 3 2
3 1 3
1 2
2 3

```

### 输出

```
6
1 3 2 

```

## 样例 #2

### 输入

```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 3

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 4

```

### 输出

```
9
1 3 2 1 3 

```

