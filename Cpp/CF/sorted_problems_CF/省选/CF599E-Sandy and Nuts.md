---
title: "Sandy and Nuts"
layout: "post"
diff: 省选/NOI-
pid: CF599E
tag: ['动态规划 DP', '枚举', '最近公共祖先 LCA']
---

# Sandy and Nuts

## 题目描述

Rooted tree is a connected graph without any simple cycles with one vertex selected as a root. In this problem the vertex number $ 1 $ will always serve as a root.

Lowest common ancestor of two vertices $ u $ and $ v $ is the farthest from the root vertex that lies on both the path from $ u $ to the root and on path from $ v $ to the root. We will denote it as $ LCA(u,v) $ .

Sandy had a rooted tree consisting of $ n $ vertices that she used to store her nuts. Unfortunately, the underwater storm broke her tree and she doesn't remember all it's edges. She only managed to restore $ m $ edges of the initial tree and $ q $ triples $ a_{i} $ , $ b_{i} $ and $ c_{i} $ , for which she supposes $ LCA(a_{i},b_{i})=c_{i} $ .

Help Sandy count the number of trees of size $ n $ with vertex $ 1 $ as a root, that match all the information she remembered. If she made a mess and there are no such trees then print $ 0 $ . Two rooted trees are considered to be distinct if there exists an edge that occur in one of them and doesn't occur in the other one.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n<=13,0<=m<n,0<=q<=100 $ ) — the number of vertices, the number of edges and $ LCA $ triples remembered by Sandy respectively.

Each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i} $ ) — the numbers of vertices connected by the $ i $ -th edge. It's guaranteed that this set of edges is a subset of edges of some tree.

The last $ q $ lines contain the triplets of numbers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i},c_{i}<=n) $ . Each of these triples define $ LCA(a_{i},b_{i})=c_{i} $ . It's not guaranteed that there exists a tree that satisfy all the given $ LCA $ conditions.

## 输出格式

Print a single integer — the number of trees of size $ n $ that satisfy all the conditions.

## 说明/提示

In the second sample correct answer looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/3a06f49f1bab15c25fa9029dff674e9bd2958cf5.png)In the third sample there are two possible trees:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/5bc65707292dd568a0ac7a018a2f94f9303bf3c4.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/bacea40f00b7ff26956d9e8aa34e3c4499c85dc6.png)In the fourth sample the answer is $ 0 $ because the information about $ LCA $ is inconsistent.

## 样例 #1

### 输入

```
4 0 0

```

### 输出

```
16

```

## 样例 #2

### 输入

```
4 0 1
3 4 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1 0
1 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
3 0 2
2 3 2
2 3 1

```

### 输出

```
0

```

## 样例 #5

### 输入

```
4 1 2
1 2
2 2 2
3 4 2

```

### 输出

```
1

```

