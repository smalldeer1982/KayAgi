---
title: "Matches Are Not a Child's Play "
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1137F
tag: []
---

# Matches Are Not a Child's Play 

## 题目描述

我们定义一棵树的删除序列为：每一次将树中编号最小的叶子删掉，将该节点编号加入到当前序列的最末端，最后只剩下一个节点时将该节点的编号加入到结尾。

![](https://cdn.luogu.org/upload/vjudge_pic/CF1137F/bc0d9649c17373120f77a2c7a539e99bc4a36a66.png)

例如对于上图中的树，它的删除序列为：2 4 3 1 5

现在给出一棵$n$个节点的树，有$m$次操作：

`up v`：将$v$号节点的编号变为当前所有节点编号的$\max + 1$

`when v`：查询$v$在当前树的删除序列中是第几号元素

`compare u v`：查询$u$和$v$在当前树的删除序列中谁更靠前

## 输入格式

第一行两个正整数$n,q(1 \leq n , q \leq 200000)$表示树的点数和操作数

接下来$n-1$行每行$2$个正整数$u,v(1 \leq u,v \leq n)$表示树上的一条边

接下来$q$行每行描述一个操作

## 输出格式

每一个询问输出一行

对于`when v`询问，输出一个正整数表示$v$是当前删除序列的哪一个元素

对于`compare u v`询问，如果$u$在删除序列中更靠前则输出$u$，否则输出$v$

## 样例 #1

### 输入

```
5 7
1 5
1 2
1 3
4 3
when 1
when 2
when 3
when 4
when 5
compare 2 3
compare 3 4

```

### 输出

```
4
1
3
2
5
2
4

```

## 样例 #2

### 输入

```
5 5
1 5
1 2
1 3
4 3
up 1
compare 2 4
compare 4 3
compare 3 1
compare 1 5

```

### 输出

```
2
4
3
5

```

