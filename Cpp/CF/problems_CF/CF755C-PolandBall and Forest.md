---
title: "PolandBall and Forest"
layout: "post"
diff: 普及/提高-
pid: CF755C
tag: []
---

# PolandBall and Forest

## 题目描述

PolandBall lives in a forest with his family. There are some trees in the forest. Trees are undirected acyclic graphs with $ k $ vertices and $ k-1 $ edges, where $ k $ is some integer. Note that one vertex is a valid tree.

There is exactly one relative living in each vertex of each tree, they have unique ids from $ 1 $ to $ n $ . For each Ball $ i $ we know the id of its most distant relative living on the same tree. If there are several such vertices, we only know the value of the one with smallest id among those.

How many trees are there in the forest?

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{4} $ ) — the number of Balls living in the forest.

The second line contains a sequence $ p_{1},p_{2},...,p_{n} $ of length $ n $ , where ( $ 1<=p_{i}<=n $ ) holds and $ p_{i} $ denotes the most distant from Ball $ i $ relative living on the same tree. If there are several most distant relatives living on the same tree, $ p_{i} $ is the id of one with the smallest id.

It's guaranteed that the sequence $ p $ corresponds to some valid forest.

Hacking: To hack someone, you should provide a correct forest as a test. The sequence $ p $ will be calculated according to the forest and given to the solution you try to hack as input. Use the following format:

In the first line, output the integer $ n $ ( $ 1<=n<=10^{4} $ ) — the number of Balls and the integer $ m $ ( $ 0<=m&lt;n $ ) — the total number of edges in the forest. Then $ m $ lines should follow. The $ i $ -th of them should contain two integers $ a_{i} $ and $ b_{i} $ and represent an edge between vertices in which relatives $ a_{i} $ and $ b_{i} $ live. For example, the first sample is written as follows:

`<br></br>5 3<br></br>1 2<br></br>3 4<br></br>4 5<br></br>`

## 输出格式

You should output the number of trees in the forest where PolandBall lives.

Interaction

From the technical side, this problem is interactive. However, it should not affect you (except hacking) since there is no interaction.

## 说明/提示

In the first sample testcase, possible forest is: 1-2 3-4-5.

There are $ 2 $ trees overall.

In the second sample testcase, the only possible graph is one vertex and no edges. Therefore, there is only one tree.

## 样例 #1

### 输入

```
5
2 1 5 3 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
1

```

### 输出

```
1
```

