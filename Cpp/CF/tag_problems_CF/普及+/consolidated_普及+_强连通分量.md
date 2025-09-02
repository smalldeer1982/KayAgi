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
title: "Checkposts"
layout: "post"
diff: 普及+/提高
pid: CF427C
tag: ['图论', '图论建模', '强连通分量']
---

# Checkposts

## 题目描述

你的城市有 $n$ 个路口。路口之间有一条单程道路。作为城市的市长，你必须确保所有路口的安全。

为了确保安全，你必须建造一些警察检查站。一个检查站只能建在一个路口。 如果有一个检查站在 $i$ 路口，保护 $j$ 的条件是：$i==j$ 或者警察巡逻车可以从 $i$ 走到 $j$，并且能回到 $i$。

建造检查站要花一些钱。 由于城市的某些地区比其他地区更昂贵，在某些路口修建检查站可能比其他路口花费更多的钱。

你需要找到使所有路口安全的最低花费，以及花费与最低价格相等的方案数。

如果其中任何一个路口包含其中一个检查点而不包含在另一个路口中，则两种方式是不同的。

方案数模 $10^9+7$。

## 输入格式

第一行输入一个整数 $n$ 表示路口数。

第二行输入 $n$ 个整数 $a_{i}$ 表示每个路口建检查站的花费。

第三行输入一个整数 $m$ 表示有向道路的数量。

接下来 $m$ 行，每行两个整数 $x,y$，表示一条从 $x$ 到 $y$ 的有向道路。

## 输出格式

一行用空格分割的两个数，分别表示最小花费和方案数

## 说明/提示

$1 \leq n \leq 10^5,0 \leq m \leq 3 \times 10^5,0 \leq a_{i} \leq 10^9$。

$1<=u_{i},v_{i}<=n,u≠v$。

**最小花费不需要取模，方案数需要取模。**

## 样例 #1

### 输入

```
3
1 2 3
3
1 2
2 3
3 2

```

### 输出

```
3 1

```

## 样例 #2

### 输入

```
5
2 8 0 6 0
6
1 4
1 3
2 4
3 4
4 5
5 1

```

### 输出

```
8 2

```

## 样例 #3

### 输入

```
10
1 3 2 2 1 3 1 4 10 10
12
1 2
2 3
3 1
3 4
4 5
5 6
5 7
6 4
7 3
8 9
9 10
10 9

```

### 输出

```
15 6

```

## 样例 #4

### 输入

```
2
7 91
2
1 2
2 1

```

### 输出

```
7 1

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

