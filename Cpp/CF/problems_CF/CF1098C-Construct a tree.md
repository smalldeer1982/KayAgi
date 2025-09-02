---
title: "Construct a tree"
layout: "post"
diff: 省选/NOI-
pid: CF1098C
tag: []
---

# Construct a tree

## 题目描述

Misha walked through the snowy forest and he was so fascinated by the trees to decide to draw his own tree!

Misha would like to construct a rooted tree with $ n $ vertices, indexed from 1 to $ n $ , where the root has index 1. Every other vertex has a parent $ p_i $ , and $ i $ is called a child of vertex $ p_i $ . Vertex $ u $ belongs to the subtree of vertex $ v $ iff $ v $ is reachable from $ u $ while iterating over the parents ( $ u $ , $ p_{u} $ , $ p_{p_{u}} $ , ...). Clearly, $ v $ belongs to its own subtree, and the number of vertices in the subtree is called the size of the subtree. Misha is only interested in trees where every vertex belongs to the subtree of vertex $ 1 $ .

Below there is a tree with $ 6 $ vertices. The subtree of vertex $ 2 $ contains vertices $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ . Hence the size of its subtree is $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1098C/c0bc9c82cdcd20b087d88b1afdb2ab79756ebad2.png)The branching coefficient of the tree is defined as the maximum number of children in any vertex. For example, for the tree above the branching coefficient equals $ 2 $ . Your task is to construct a tree with $ n $ vertices such that the sum of the subtree sizes for all vertices equals $ s $ , and the branching coefficient is minimum possible.

## 输入格式

The only input line contains two integers $ n $ and $ s $ — the number of vertices in the tree and the desired sum of the subtree sizes ( $ 2 \le n \le 10^5 $ ; $ 1 \le s \le 10^{10} $ ).

## 输出格式

If the required tree does not exist, output «No». Otherwise output «Yes» on the first line, and in the next one output integers $ p_2 $ , $ p_3 $ , ..., $ p_n $ , where $ p_i $ denotes the parent of vertex $ i $ .

## 说明/提示

Below one can find one of the possible solutions for the first sample case. The sum of subtree sizes equals $ 3 + 1 + 1 = 5 $ , and the branching coefficient equals $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1098C/ee98c5c7cbd89b2c919d59781e8421d44b49e284.png)Below one can find one of the possible solutions for the third sample case. The sum of subtree sizes equals $ 6 + 3 + 2 + 1 + 2 + 1 = 15 $ , and the branching coefficient equals $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1098C/c9978c0d5d53b71095c0212966f1b4c387ec4ee6.png)

## 样例 #1

### 输入

```
3 5

```

### 输出

```
Yes
1 1 

```

## 样例 #2

### 输入

```
4 42

```

### 输出

```
No

```

## 样例 #3

### 输入

```
6 15

```

### 输出

```
Yes
1 2 3 1 5 

```

