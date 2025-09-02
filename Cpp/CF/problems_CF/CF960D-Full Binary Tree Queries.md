---
title: "Full Binary Tree Queries"
layout: "post"
diff: 省选/NOI-
pid: CF960D
tag: []
---

# Full Binary Tree Queries

## 题目描述

You have a full binary tree having infinite levels.

Each node has an initial value. If a node has value $ x $ , then its left child has value $ 2·x $ and its right child has value $ 2·x+1 $ .

The value of the root is $ 1 $ .

You need to answer $ Q $ queries.

There are $ 3 $ types of queries:

1. Cyclically shift the values of all nodes on the same level as node with value $ X $ by $ K $ units. (The values/nodes of any other level are not affected).
2. Cyclically shift the nodes on the same level as node with value $ X $ by $ K $ units. (The subtrees of these nodes will move along with them).
3. Print the value of every node encountered on the simple path from the node with value $ X $ to the root.

Positive $ K $ implies right cyclic shift and negative $ K $ implies left cyclic shift.

It is guaranteed that atleast one type $ 3 $ query is present.

## 输入格式

The first line contains a single integer $ Q $ ( $ 1<=Q<=10^{5} $ ).

Then $ Q $ queries follow, one per line:

- Queries of type $ 1 $ and $ 2 $ have the following format: $ T $ $ X $ $ K $ ( $ 1<=T<=2 $ ; $ 1<=X<=10^{18} $ ; $ 0<=|K|<=10^{18} $ ), where $ T $ is type of the query.
- Queries of type $ 3 $ have the following format: $ 3 $ $ X $ ( $ 1<=X<=10^{18} $ ).

## 输出格式

For each query of type $ 3 $ , print the values of all nodes encountered in descending order.

## 说明/提示

Following are the images of the first $ 4 $ levels of the tree in the first test case:

Original:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960D/3753965d34e08b83256fa92db7096f66de1db941.png) After query 1 2 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960D/d6350f6795afab08bec95128db23af58d71e24a4.png) After query 2 4 -1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960D/1c7af7fd089110021fd920d50be3656fe800bbdb.png)

## 样例 #1

### 输入

```
5
3 12
1 2 1
3 12
2 4 -1
3 8

```

### 输出

```
12 6 3 1 
12 6 2 1 
8 4 2 1 

```

## 样例 #2

### 输入

```
5
3 14
1 5 -3
3 14
1 3 1
3 14

```

### 输出

```
14 7 3 1 
14 6 3 1 
14 6 2 1 

```

