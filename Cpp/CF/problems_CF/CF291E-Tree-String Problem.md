---
title: "Tree-String Problem"
layout: "post"
diff: 提高+/省选-
pid: CF291E
tag: []
---

# Tree-String Problem

## 题目描述

A rooted tree is a non-directed connected graph without any cycles with a distinguished vertex, which is called the tree root. Consider the vertices of a rooted tree, that consists of $ n $ vertices, numbered from 1 to $ n $ . In this problem the tree root is the vertex number 1.

Let's represent the length of the shortest by the number of edges path in the tree between vertices $ v $ and $ u $ as $ d(v,u) $ .

A parent of vertex $ v $ in the rooted tree with the root in vertex $ r $ $ (v≠r) $ is vertex $ p_{v} $ , such that $ d(r,p_{v})+1=d(r,v) $ and  $ d(p_{v},v)=1 $ . For example, on the picture the parent of vertex $ v=5 $ is vertex $ p_{5}=2 $ .

One day Polycarpus came across a rooted tree, consisting of $ n $ vertices. The tree wasn't exactly ordinary: it had strings written on its edges. Polycarpus positioned the tree on the plane so as to make all edges lead from top to bottom if you go from the vertex parent to the vertex (see the picture). For any edge that lead from vertex $ p_{v} $ to vertex $ v $ $ (1&lt;v<=n) $ , he knows string $ s_{v} $ that is written on it. All strings are written on the edges from top to bottom. For example, on the picture $ s_{7} $ ="ba". The characters in the strings are numbered starting from 0.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF291E/5987d6fa331503653665dfdb5083832d68b0b965.png)An example of Polycarpus's tree (corresponds to the example from the statement)Polycarpus defines the position in this tree as a specific letter on a specific string. The position is written as a pair of integers $ (v,x) $ that means that the position is the $ x $ -th letter of the string $ s_{v} $ ( $ 1&lt;v<=n $ , $ 0<=x&lt;|s_{v}| $ ), where $ |s_{v}| $ is the length of string $ s_{v} $ . For example, the highlighted letters are positions ( $ 2,1 $ ) and ( $ 3,1 $ ).

Let's consider the pair of positions $ (v,x) $ and $ (u,y) $ in Polycarpus' tree, such that the way from the first position to the second goes down on each step. We will consider that the pair of such positions defines string $ z $ . String $ z $ consists of all letters on the way from $ (v,x) $ to $ (u,y) $ , written in the order of this path. For example, in the picture the highlighted positions define string "bacaba".

Polycarpus has a string $ t $ , he wants to know the number of pairs of positions that define string $ t $ . Note that the way from the first position to the second in the pair must go down everywhere. Help him with this challenging tree-string problem!

## 输入格式

The first line contains integer $ n $ $ (2<=n<=10^{5}) $ — the number of vertices of Polycarpus's tree. Next $ n-1 $ lines contain the tree edges. The $ i $ -th of them contains number $ p_{i+1} $ and string $ s_{i+1} $ $ (1<=p_{i+1}<=n; p_{i+1}≠(i+1)) $ . String $ s_{i+1} $ is non-empty and consists of lowercase English letters. The last line contains string $ t $ . String $ t $ consists of lowercase English letters, its length is at least 2.

It is guaranteed that the input contains at most $ 3·10^{5} $ English letters.

## 输出格式

Print a single integer — the required number.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first test case string "aba" is determined by the pairs of positions: (2, 0) and (5, 0); (5, 2) and (6, 1); (5, 2) and (3, 1); (4, 0) and (4, 2); (4, 4) and (4, 6); (3, 3) and (3, 5).

Note that the string is not defined by the pair of positions (7, 1) and (5, 0), as the way between them doesn't always go down.

## 样例 #1

### 输入

```
7
1 ab
5 bacaba
1 abacaba
2 aca
5 ba
2 ba
aba

```

### 输出

```
6

```

## 样例 #2

### 输入

```
7
1 ab
5 bacaba
1 abacaba
2 aca
5 ba
2 ba
bacaba

```

### 输出

```
4

```

