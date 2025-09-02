---
title: "Kevin and Bipartite Graph"
layout: "post"
diff: 普及+/提高
pid: CF2048E
tag: ['二分图', '构造']
---

# Kevin and Bipartite Graph

## 题目描述

武器工厂需要一种海报设计模式，并向 Kevin 求助。

海报设计模式是一个二分图，左半部分有 $2n$ 个顶点，右半部分有 $m$ 个顶点。左半部分的每个顶点与右半部分的每个顶点之间都有一条边，总共形成 $2nm$ 条边。

Kevin 必须用范围在 $[1, n]$ 内的正整数为每条边着色。如果二分图中没有单色环（所有边颜色相同的简单环），则该海报设计模式是良好的。

Kevin 需要你的帮助来构造一个良好的二分图，或者在不可能的情况下通知他。

**单色环**：指所有边颜色都相同的简单环。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \leq t \leq 100$）。

每个测试用例的唯一一行包含两个整数 $n$ 和 $m$（$1 \leq n, m \leq 10^3$），表示二分图左半部分有 $2n$ 个顶点，右半部分有 $m$ 个顶点。

保证所有测试用例的 $n$ 之和以及 $m$ 之和都不超过 $10^3$。

## 输出格式

对于每个测试用例，如果没有解决方案，则输出 No。

否则，首先输出 Yes，然后输出 $2n$ 行，每行包含 $m$ 个正整数。第 $i$ 行的第 $j$ 个整数表示左半部分第 $i$ 个顶点和右半部分第 $j$ 个顶点之间的边的颜色。

如果有多个答案，可以输出其中任何一个。

你可以以任何大小写形式输出每个字母（例如，字符串 yEs、yes、Yes 和 YES 都将被识别为肯定回答）。

## 说明/提示

对于第一个测试用例，图形如下所示：

对于第二个测试用例，可以证明没有有效的解决方案。

## 样例 #1

### 输入

```
3
2 2
3 7
5 4
```

### 输出

```
YES
1 2
2 1
2 2
2 1
NO
YES
1 1 1 1
1 2 2 2
1 2 3 3
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
```



---

---
title: "Mahmoud and Ehab and the bipartiteness"
layout: "post"
diff: 普及+/提高
pid: CF862B
tag: ['二分图']
---

# Mahmoud and Ehab and the bipartiteness

## 题目描述

Mahmoud and Ehab continue their adventures! As everybody in the evil land knows, Dr. Evil likes bipartite graphs, especially trees.

A tree is a connected acyclic graph. A bipartite graph is a graph, whose vertices can be partitioned into $ 2 $ sets in such a way, that for each edge $ (u,v) $ that belongs to the graph, $ u $ and $ v $ belong to different sets. You can find more formal definitions of a tree and a bipartite graph in the notes section below.

Dr. Evil gave Mahmoud and Ehab a tree consisting of $ n $ nodes and asked them to add edges to it in such a way, that the graph is still bipartite. Besides, after adding these edges the graph should be simple (doesn't contain loops or multiple edges). What is the maximum number of edges they can add?

A loop is an edge, which connects a node with itself. Graph doesn't contain multiple edges when for each pair of nodes there is no more than one edge between them. A cycle and a loop aren't the same .

## 输入格式

The first line of input contains an integer $ n $ — the number of nodes in the tree ( $ 1<=n<=10^{5} $ ).

The next $ n-1 $ lines contain integers $ u $ and $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ) — the description of the edges of the tree.

It's guaranteed that the given graph is a tree.

## 输出格式

Output one integer — the maximum number of edges that Mahmoud and Ehab can add to the tree while fulfilling the conditions.

## 说明/提示

Tree definition: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>

Bipartite graph definition: [https://en.wikipedia.org/wiki/Bipartite\_graph](https://en.wikipedia.org/wiki/Bipartite_graph)

In the first test case the only edge that can be added in such a way, that graph won't contain loops or multiple edges is $ (2,3) $ , but adding this edge will make the graph non-bipartite so the answer is 0.

In the second test case Mahmoud and Ehab can add edges $ (1,4) $ and $ (2,5) $ .

## 样例 #1

### 输入

```
3
1 2
1 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5

```

### 输出

```
2

```



---

