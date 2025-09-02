---
title: "We Need More Bosses"
layout: "post"
diff: 普及+/提高
pid: CF1000E
tag: ['图论建模', '强连通分量', '树的直径']
---

# We Need More Bosses

## 题目描述

**题目大意：**

给定一个 $n$ 个点 $m$ 条边的无向图，保证图连通。找到两个点$s,t$，使得$s$到$t$**必须**经过的边最多（一条边无论走哪条路线都经过ta，这条边就是必须经过的边），$2<=n<=3*10^5,1<=m<=3*10^5$

## 输入格式

第一行两个整数，$n,m$

以下m行，每行两个整数$x,y$，表示$xy$间有一条无向边相连

## 输出格式

一个整数，即最多的必须经过边数

感谢@守望 提供翻译

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 1
4 1
5 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
1 2
4 3
3 2

```

### 输出

```
3

```



---

---
title: "Apple Tree Traversing"
layout: "post"
diff: 普及+/提高
pid: CF2107D
tag: ['贪心', '树的直径']
---

# Apple Tree Traversing

## 题目描述

有一棵 $n$ 个点的苹果树，每个结点上有一棵苹果。你有一张白纸。

你将要在苹果树上穿梭，重复做以下事情直到苹果树上没有苹果：
- 选择一条路径 $(u,v)$，满足这条路径上所有点上都有苹果。
- 拿走这条路径上的所有苹果，设你这次拿了 $d$ 个苹果，在你的纸上依次写下三个数字 $d$，$u$ 和 $v$。

称结束后你的纸上的数字构成的数列为 $a$。输出可能的字典序最大的 $a$。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 1.5\times 10^5)$。\
接下来 $n-1$ 行，每行两个数字表示树上的一条边。

保证一个测试点中 $\sum n\le 1.5\times 10^5$。

## 输出格式

每组数据输出一行，为可能的字典序最大的 $a$。可以证明 $a$ 的长度 $\le 3\times n$。

## 说明/提示

在第一组数据中，我们进行以下操作：
- 选择路径 $(4,3)$，拿走结点 $1,3,4$ 上面的苹果，在纸上写下 $3,4,3$。
- 选择路径 $(2,2)$，拿走结点 $2$ 上面的苹果，在纸上写下 $1,2,2$。

最终形成了 $a=(3,4,3,1,2,2)$，可以证明这是字典序最大的合法结果。

By chenxi2009

## 样例 #1

### 输入

```
6
4
1 2
1 3
1 4
4
2 1
2 4
2 3
5
1 2
2 3
3 4
4 5
1
8
6 3
3 5
5 4
4 2
5 1
1 8
3 7
6
3 2
2 6
2 5
5 4
4 1
```

### 输出

```
3 4 3 1 2 2 
3 4 3 1 1 1 
5 5 1 
1 1 1 
5 8 7 2 4 2 1 6 6 
5 6 1 1 3 3
```



---

---
title: "穿越苹果树"
layout: "post"
diff: 普及+/提高
pid: CF2107D
tag: ['贪心', '树的直径']
---

# 穿越苹果树

## 题目描述

有一棵 $n$ 个点的苹果树，每个结点上有一棵苹果。你有一张白纸。

你将要在苹果树上穿梭，重复做以下事情直到苹果树上没有苹果：
- 选择一条路径 $(u,v)$，满足这条路径上所有点上都有苹果。
- 拿走这条路径上的所有苹果，设你这次拿了 $d$ 个苹果，在你的纸上依次写下三个数字 $d$，$u$ 和 $v$。

称结束后你的纸上的数字构成的数列为 $a$。输出可能的字典序最大的 $a$。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 1.5\times 10^5)$。\
接下来 $n-1$ 行，每行两个数字表示树上的一条边。

保证一个测试点中 $\sum n\le 1.5\times 10^5$。

## 输出格式

每组数据输出一行，为可能的字典序最大的 $a$。可以证明 $a$ 的长度 $\le 3\times n$。

## 说明/提示

在第一组数据中，我们进行以下操作：
- 选择路径 $(4,3)$，拿走结点 $1,3,4$ 上面的苹果，在纸上写下 $3,4,3$。
- 选择路径 $(2,2)$，拿走结点 $2$ 上面的苹果，在纸上写下 $1,2,2$。

最终形成了 $a=(3,4,3,1,2,2)$，可以证明这是字典序最大的合法结果。

By chenxi2009

## 样例 #1

### 输入

```
6
4
1 2
1 3
1 4
4
2 1
2 4
2 3
5
1 2
2 3
3 4
4 5
1
8
6 3
3 5
5 4
4 2
5 1
1 8
3 7
6
3 2
2 6
2 5
5 4
4 1
```

### 输出

```
3 4 3 1 2 2 
3 4 3 1 1 1 
5 5 1 
1 1 1 
5 8 7 2 4 2 1 6 6 
5 6 1 1 3 3
```



---

---
title: "Anton and Tree"
layout: "post"
diff: 普及+/提高
pid: CF734E
tag: ['并查集', '强连通分量', '树的直径']
---

# Anton and Tree

## 题目描述

Anton is growing a tree in his garden. In case you forgot, the tree is a connected acyclic undirected graph.

There are $ n $ vertices in the tree, each of them is painted black or white. Anton doesn't like multicolored trees, so he wants to change the tree such that all vertices have the same color (black or white).

To change the colors Anton can use only operations of one type. We denote it as $ paint(v) $ , where $ v $ is some vertex of the tree. This operation changes the color of all vertices $ u $ such that all vertices on the shortest path from $ v $ to $ u $ have the same color (including $ v $ and $ u $ ). For example, consider the tree

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/e17d4eda0dc67dbbca220a370e8bf45f5d1faeb0.png)and apply operation $ paint(3) $ to get the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/eabfeb953964c829d6d1820bd3bcad690b9ae826.png)Anton is interested in the minimum number of operation he needs to perform in order to make the colors of all vertices equal.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ color_{i} $ ( $ 0<=color_{i}<=1 $ ) — colors of the vertices. $ color_{i}=0 $ means that the $ i $ -th vertex is initially painted white, while $ color_{i}=1 $ means it's initially painted black.

Then follow $ n-1 $ line, each of them contains a pair of integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i} $ ) — indices of vertices connected by the corresponding edge. It's guaranteed that all pairs $ (u_{i},v_{i}) $ are distinct, i.e. there are no multiple edges.

## 输出格式

Print one integer — the minimum number of operations Anton has to apply in order to make all vertices of the tree black or all vertices of the tree white.

## 说明/提示

In the first sample, the tree is the same as on the picture. If we first apply operation $ paint(3) $ and then apply $ paint(6) $ , the tree will become completely black, so the answer is $ 2 $ .

In the second sample, the tree is already white, so there is no need to apply any operations and the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
0 0 0 1 1 0 1 0 0 1 1
1 2
1 3
2 4
2 5
5 6
5 7
3 8
3 9
3 10
9 11

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
0 0 0 0
1 2
2 3
3 4

```

### 输出

```
0

```



---

