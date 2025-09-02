---
title: "MSTS - Count Minimum Spanning Trees"
layout: "post"
diff: 省选/NOI-
pid: SP2670
tag: []
---

# MSTS - Count Minimum Spanning Trees

## 题目描述

你的任务是一个简单地问题：数出一个无向图中最小生成树的数量（最小生成数定义详见[维基百科](https://en.wikipedia.org/wiki/Minimum_spanning_tree)）。

## 输入格式

第一行给出两个数N（1$\leq$N$\leq$100），M（1$\leq$M$\leq$1000）。图中节点标号为1至N。
接下来M行，每行包括三个正整数a$_i$，b$_i$，c$_i$，表示有一条长度为c$_i$的无向边连接a$_i$和b$_i$。（1$\leq$ a$_i$ $\neq$b$_i$ $\leq$N，1  $\leq$c$_i$$\leq$1,000,000,000）。保证图是联通的且没有重边

## 输出格式

输出一行答案，对31011取模

## 样例 #1

### 输入

```
4 6
1 2 1
1 3 1
1 4 1
2 3 2
2 4 1
3 4 1
```

### 输出

```
8
```

