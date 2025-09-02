---
title: "Tree Requests"
layout: "post"
diff: 省选/NOI-
pid: CF570D
tag: ['树上启发式合并']
---

# Tree Requests

## 题目描述

Roman planted a tree consisting of $ n $ vertices. Each vertex contains a lowercase English letter. Vertex $ 1 $ is the root of the tree, each of the $ n-1 $ remaining vertices has a parent in the tree. Vertex is connected with its parent by an edge. The parent of vertex $ i $ is vertex $ p_{i} $ , the parent index is always less than the index of the vertex (i.e., $ p_{i}&lt;i $ ).

The depth of the vertex is the number of nodes on the path from the root to $ v $ along the edges. In particular, the depth of the root is equal to $ 1 $ .

We say that vertex $ u $ is in the subtree of vertex $ v $ , if we can get from $ u $ to $ v $ , moving from the vertex to the parent. In particular, vertex $ v $ is in its subtree.

Roma gives you $ m $ queries, the $ i $ -th of which consists of two numbers $ v_{i} $ , $ h_{i} $ . Let's consider the vertices in the subtree $ v_{i} $ located at depth $ h_{i} $ . Determine whether you can use the letters written at these vertices to make a string that is a palindrome. The letters that are written in the vertexes, can be rearranged in any order to make a palindrome, but all letters should be used.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n,m<=500000 $ ) — the number of nodes in the tree and queries, respectively.

The following line contains $ n-1 $ integers $ p_{2},p_{3},...,p_{n} $ — the parents of vertices from the second to the $ n $ -th ( $ 1<=p_{i}&lt;i $ ).

The next line contains $ n $ lowercase English letters, the $ i $ -th of these letters is written on vertex $ i $ .

Next $ m $ lines describe the queries, the $ i $ -th line contains two numbers $ v_{i} $ , $ h_{i} $ ( $ 1<=v_{i},h_{i}<=n $ ) — the vertex and the depth that appear in the $ i $ -th query.

## 输出格式

Print $ m $ lines. In the $ i $ -th line print "Yes" (without the quotes), if in the $ i $ -th query you can make a palindrome from the letters written on the vertices, otherwise print "No" (without the quotes).

## 说明/提示

String $ s $ is a palindrome if reads the same from left to right and from right to left. In particular, an empty string is a palindrome.

Clarification for the sample test.

In the first query there exists only a vertex 1 satisfying all the conditions, we can form a palindrome "z".

In the second query vertices 5 and 6 satisfy condititions, they contain letters "с" and "d" respectively. It is impossible to form a palindrome of them.

In the third query there exist no vertices at depth 1 and in subtree of 4. We may form an empty palindrome.

In the fourth query there exist no vertices in subtree of 6 at depth 1. We may form an empty palindrome.

In the fifth query there vertices 2, 3 and 4 satisfying all conditions above, they contain letters "a", "c" and "c". We may form a palindrome "cac".

## 样例 #1

### 输入

```
6 5
1 1 1 3 3
zacccd
1 1
3 3
4 1
6 1
1 2

```

### 输出

```
Yes
No
Yes
Yes
Yes

```

