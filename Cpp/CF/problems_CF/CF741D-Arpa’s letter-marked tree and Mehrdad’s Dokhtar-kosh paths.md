---
title: "Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths"
layout: "post"
diff: 省选/NOI-
pid: CF741D
tag: ['树上启发式合并']
---

# Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths

## 题目描述

Just in case somebody missed it: we have wonderful girls in Arpa’s land.

Arpa has a rooted tree (connected acyclic graph) consisting of $ n $ vertices. The vertices are numbered $ 1 $ through $ n $ , the vertex $ 1 $ is the root. There is a letter written on each edge of this tree. Mehrdad is a fan of Dokhtar-kosh things. He call a string Dokhtar-kosh, if we can shuffle the characters in string such that it becomes palindrome.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF741D/ae6eaea25c446dd1a9c02c7621129601f3a81ec1.png)He asks Arpa, for each vertex $ v $ , what is the length of the longest simple path in subtree of $ v $ that form a Dokhtar-kosh string.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the number of vertices in the tree.

 $ (n-1) $ lines follow, the $ i $ -th of them contain an integer $ p_{i+1} $ and a letter $ c_{i+1} $ ( $ 1<=p_{i+1}<=i $ , $ c_{i+1} $ is lowercase English letter, between a and v, inclusively), that mean that there is an edge between nodes $ p_{i+1} $ and $ i+1 $ and there is a letter $ c_{i+1} $ written on this edge.

## 输出格式

Print $ n $ integers. The $ i $ -th of them should be the length of the longest simple path in subtree of the $ i $ -th vertex that form a Dokhtar-kosh string.

## 样例 #1

### 输入

```
4
1 s
2 a
3 s

```

### 输出

```
3 1 1 0 
```

## 样例 #2

### 输入

```
5
1 a
2 h
1 a
4 h

```

### 输出

```
4 1 0 1 0 
```

