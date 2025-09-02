---
title: "Christmas Spruce"
layout: "post"
diff: 普及-
pid: CF913B
tag: []
---

# Christmas Spruce

## 题目描述

Consider a rooted tree. A rooted tree has one special vertex called the root. All edges are directed from the root. Vertex $ u $ is called a child of vertex $ v $ and vertex $ v $ is called a parent of vertex $ u $ if there exists a directed edge from $ v $ to $ u $ . A vertex is called a leaf if it doesn't have children and has a parent.

Let's call a rooted tree a spruce if its every non-leaf vertex has at least $ 3 $ leaf children. You are given a rooted tree, check whether it's a spruce.

The definition of a rooted tree can be found [here](https://goo.gl/1dqvzz).

## 输入格式

The first line contains one integer $ n $ — the number of vertices in the tree ( $ 3<=n<=1000 $ ). Each of the next $ n-1 $ lines contains one integer $ p_{i} $ ( $ 1<=i<=n-1 $ ) — the index of the parent of the $ i+1 $ -th vertex ( $ 1<=p_{i}<=i $ ).

Vertex $ 1 $ is the root. It's guaranteed that the root has at least $ 2 $ children.

## 输出格式

Print "Yes" if the tree is a spruce and "No" otherwise.

## 说明/提示

The first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/3d87b6a6cda0ba6f4ad05908fb42ae8248c8369b.png)

The second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/bd0b03933e2dbb274b2b58b0c7a13d930c39c80b.png)

It is not a spruce, because the non-leaf vertex $ 1 $ has only $ 2 $ leaf children.

The third example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913B/a9d72240b2a5e338c43541d320aabfb5ee526dff.png)

## 样例 #1

### 输入

```
4
1
1
1

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
7
1
1
1
2
2
2

```

### 输出

```
No

```

## 样例 #3

### 输入

```
8
1
1
1
1
3
3
3

```

### 输出

```
Yes

```

