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
title: "Military Problem"
layout: "post"
diff: 普及+/提高
pid: CF1006E
tag: ['深度优先搜索 DFS', '图论建模', '向量']
---

# Military Problem

## 题目描述

在这个问题中你需要帮助伯兰（？？我没找到有Berland这个国家）军队组织他们的指挥系统

伯兰军队中一共有n个军官。第一个官员是军队的指挥官，他并没有任何上级。其他的军官都有且只有一个直接的上级。如果一个军官a是军官b的上级，那么你也可以说军官b就是军官a的下属

如果满足下列条件，那么军官x就是军官y的下属（直接或非直接）：

1.y是x的直接上级 2.x的直接上级是y的下属

举个例子，下图的官员3的下属有:5,6,7,8,9

所以，在伯兰军队的结构中，除了指挥官，其他人都是指挥官的下属

形式上的，让我们把伯兰军队看成一棵拥有n个节点的树，树的节点u就代表了军官u。根（即一号节点）就相当于指挥官

伯兰战争部门命令你对q个查询给出答案。这q个查询会以（ui，ki）的形式给出，ui代表了某个军官，ki是正整数。你需要输出，编号为ui的军官下达命令后，第ki个得知此命令的军官编号是多少，如果传达人数不足ki个，输出-1。

要处理第i个查询，想象一下ui的命令如何我下达到ui的下属。这里使用了典型的DFS（深度优先搜索）算法。

假设现在的军官是a，他要下达一个命令。a军官选择一个军官b——还没有收到这个命令的直接下属（即在树上的一个孩子）。如果有许多这样的直接下属，那么A选择编号最小的那一个。A军官向B军官发出命令。之后，B使用完全相同的方式将命令扩展到它的子树。在B完成命令后，军官A再次选择下一个直接下属（使用相同的策略）。当军官A不能选择任何还没有接到命令的直接下属时，军官A下达命令完成。

让我们看一下下面这个例子（看下面的图）：

如果军官1下达了命令，军官们收到命令的顺序是：1,2,3,5,6,8,7,9,4

如果军官3下达了命令，军官们收到命令的顺序是：3,5,6,8,7,9

如果军官7下达了命令，军官们收到命令的顺序是：7,9

如果军官9下达了命令，军官们收到命令的顺序是：9

你应当分开处理这些查询。一个查询不会影响其他查询的结果。

## 输入格式

第一行包括两个整数n,q，表示有n个军官和q个查询（2≤n≤2×10^5,1≤q≤2×10^5）

第二行包括n-1个整数,p2、p3……pn，(1≤p<i )表示编号为i的军官直接上级为pi。编号为1的为指挥官并且他没有上级，不在输入数据中。

接下来的q行是q个查询每行包含两个整数(ui,ki)（1≤ui,ki≤n）ui表示开始下达命令的军官，ki表示要输出的军官编号是第几个得知命令的

## 输出格式

一共q行，每行包含一个整数表示第i个查询的答案：编号为ui的军官下达命令后，第ki个得知此命令的军官编号是多少，如果传达人数不足ki个，输出-1。

感谢@hicc0305 提供的翻译

## 样例 #1

### 输入

```
9 6
1 1 1 3 5 3 5 7
3 1
1 5
3 4
7 3
1 8
1 9

```

### 输出

```
3
6
8
-1
9
4

```



---

---
title: "Two Fairs"
layout: "post"
diff: 普及+/提高
pid: CF1276B
tag: ['搜索', '图论']
---

# Two Fairs

## 题目描述

There are $ n $ cities in Berland and some pairs of them are connected by two-way roads. It is guaranteed that you can pass from any city to any other, moving along the roads. Cities are numerated from $ 1 $ to $ n $ .

Two fairs are currently taking place in Berland — they are held in two different cities $ a $ and $ b $ ( $ 1 \le a, b \le n $ ; $ a \ne b $ ).

Find the number of pairs of cities $ x $ and $ y $ ( $ x \ne a, x \ne b, y \ne a, y \ne b $ ) such that if you go from $ x $ to $ y $ you will have to go through both fairs (the order of visits doesn't matter). Formally, you need to find the number of pairs of cities $ x,y $ such that any path from $ x $ to $ y $ goes through $ a $ and $ b $ (in any order).

Print the required number of pairs. The order of two cities in a pair does not matter, that is, the pairs $ (x,y) $ and $ (y,x) $ must be taken into account only once.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 4\cdot10^4 $ ) — the number of test cases in the input. Next, $ t $ test cases are specified.

The first line of each test case contains four integers $ n $ , $ m $ , $ a $ and $ b $ ( $ 4 \le n \le 2\cdot10^5 $ , $ n - 1 \le m \le 5\cdot10^5 $ , $ 1 \le a,b \le n $ , $ a \ne b $ ) — numbers of cities and roads in Berland and numbers of two cities where fairs are held, respectively.

The following $ m $ lines contain descriptions of roads between cities. Each of road description contains a pair of integers $ u_i, v_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \ne v_i $ ) — numbers of cities connected by the road.

Each road is bi-directional and connects two different cities. It is guaranteed that from any city you can pass to any other by roads. There can be more than one road between a pair of cities.

The sum of the values of $ n $ for all sets of input data in the test does not exceed $ 2\cdot10^5 $ . The sum of the values of $ m $ for all sets of input data in the test does not exceed $ 5\cdot10^5 $ .

## 输出格式

Print $ t $ integers — the answers to the given test cases in the order they are written in the input.

## 样例 #1

### 输入

```
3
7 7 3 5
1 2
2 3
3 4
4 5
5 6
6 7
7 5
4 5 2 3
1 2
2 3
3 4
4 1
4 2
4 3 2 1
1 2
2 3
4 1

```

### 输出

```
4
0
1

```



---

---
title: "Uncle Bogdan and Country Happiness"
layout: "post"
diff: 普及+/提高
pid: CF1388C
tag: ['图论']
---

# Uncle Bogdan and Country Happiness

## 题目描述

Uncle Bogdan is in captain Flint's crew for a long time and sometimes gets nostalgic for his homeland. Today he told you how his country introduced a happiness index.

There are $ n $ cities and $ n−1 $ undirected roads connecting pairs of cities. Citizens of any city can reach any other city traveling by these roads. Cities are numbered from $ 1 $ to $ n $ and the city $ 1 $ is a capital. In other words, the country has a tree structure.

There are $ m $ citizens living in the country. A $ p_i $ people live in the $ i $ -th city but all of them are working in the capital. At evening all citizens return to their home cities using the shortest paths.

Every person has its own mood: somebody leaves his workplace in good mood but somebody are already in bad mood. Moreover any person can ruin his mood on the way to the hometown. If person is in bad mood he won't improve it.

Happiness detectors are installed in each city to monitor the happiness of each person who visits the city. The detector in the $ i $ -th city calculates a happiness index $ h_i $ as the number of people in good mood minus the number of people in bad mood. Let's say for the simplicity that mood of a person doesn't change inside the city.

Happiness detector is still in development, so there is a probability of a mistake in judging a person's happiness. One late evening, when all citizens successfully returned home, the government asked uncle Bogdan (the best programmer of the country) to check the correctness of the collected happiness indexes.

Uncle Bogdan successfully solved the problem. Can you do the same?

More formally, You need to check: "Is it possible that, after all people return home, for each city $ i $ the happiness index will be equal exactly to $ h_i $ ".

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le       10000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 10^5 $ ; $ 0 \le m \le 10^9 $ ) — the number of cities and citizens.

The second line of each test case contains $ n $ integers $ p_1, p_2, \ldots, p_{n} $ ( $ 0 \le p_i \le m $ ; $ p_1 + p_2       + \ldots + p_{n} = m $ ), where $ p_i $ is the number of people living in the $ i $ -th city.

The third line contains $ n $ integers $ h_1, h_2, \ldots,       h_{n} $ ( $ -10^9 \le h_i \le 10^9 $ ), where $ h_i $ is the calculated happiness index of the $ i $ -th city.

Next $ n − 1 $ lines contain description of the roads, one per line. Each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \neq y_i $ ), where $ x_i $ and $ y_i $ are cities connected by the $ i $ -th road.

It's guaranteed that the sum of $ n $ from all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print YES, if the collected data is correct, or NO — otherwise. You can print characters in YES or NO in any case.

## 说明/提示

Let's look at the first test case of the first sample:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/001794ade043a3f0f7ed603305eb551246689207.png)At first, all citizens are in the capital. Let's describe one of possible scenarios:

- a person from city $ 1 $ : he lives in the capital and is in good mood;
- a person from city $ 4 $ : he visited cities $ 1 $ and $ 4 $ , his mood was ruined between cities $ 1 $ and $ 4 $ ;
- a person from city $ 3 $ : he visited cities $ 1 $ and $ 3 $ in good mood;
- a person from city $ 6 $ : he visited cities $ 1 $ , $ 3 $ and $ 6 $ , his mood was ruined between cities $ 1 $ and $ 3 $ ;

 In total, - $ h_1 = 4 - 0 =         4 $ ,
- $ h_2 = 0 $ ,
- $ h_3 = 1 - 1 = 0 $ ,
- $ h_4 = 0 - 1 = -1 $ ,
- $ h_5 = 0 $ ,
- $ h_6 = 0 - 1 = -1 $ ,
- $ h_7 = 0 $ .

The second case of the first test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/a9264c4828a85c9989a95ed8604e23cfb9f3dcda.png)All people have already started in bad mood in the capital — this is the only possible scenario.

The first case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/b8bbd8cbfa8f12355a17c596fd18bc65433a619c.png)The second case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/5c48a1551b8fe0dc0edc02bc5782fb0068b84587.png)It can be proven that there is no way to achieve given happiness indexes in both cases of the second test.

## 样例 #1

### 输入

```
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5
```

### 输出

```
YES
YES
```

## 样例 #2

### 输入

```
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3
```

### 输出

```
NO
NO
```



---

---
title: "Counting Shortcuts"
layout: "post"
diff: 普及+/提高
pid: CF1650G
tag: ['动态规划 DP', '图论']
---

# Counting Shortcuts

## 题目描述

Given an undirected connected graph with $ n $ vertices and $ m $ edges. The graph contains no loops (edges from a vertex to itself) and multiple edges (i.e. no more than one edge between each pair of vertices). The vertices of the graph are numbered from $ 1 $ to $ n $ .

Find the number of paths from a vertex $ s $ to $ t $ whose length differs from the shortest path from $ s $ to $ t $ by no more than $ 1 $ . It is necessary to consider all suitable paths, even if they pass through the same vertex or edge more than once (i.e. they are not simple).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)Graph consisting of $ 6 $ of vertices and $ 8 $ of edgesFor example, let $ n = 6 $ , $ m = 8 $ , $ s = 6 $ and $ t = 1 $ , and let the graph look like the figure above. Then the length of the shortest path from $ s $ to $ t $ is $ 1 $ . Consider all paths whose length is at most $ 1 + 1 = 2 $ .

- $ 6 \rightarrow 1 $ . The length of the path is $ 1 $ .
- $ 6 \rightarrow 4 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 2 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 5 \rightarrow 1 $ . Path length is $ 2 $ .

There is a total of $ 4 $ of matching paths.

## 输入格式

The first line of test contains the number $ t $ ( $ 1 \le t \le 10^4 $ ) —the number of test cases in the test.

Before each test case, there is a blank line.

The first line of test case contains two numbers $ n, m $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 2 \cdot 10^5 $ ) —the number of vertices and edges in the graph.

The second line contains two numbers $ s $ and $ t $ ( $ 1 \le s, t \le n $ , $ s \neq t $ ) —the numbers of the start and end vertices of the path.

The following $ m $ lines contain descriptions of edges: the $ i $ th line contains two integers $ u_i $ , $ v_i $ ( $ 1 \le u_i,v_i \le n $ ) — the numbers of vertices that connect the $ i $ th edge. It is guaranteed that the graph is connected and does not contain loops and multiple edges.

It is guaranteed that the sum of values $ n $ on all test cases of input data does not exceed $ 2 \cdot 10^5 $ . Similarly, it is guaranteed that the sum of values $ m $ on all test cases of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the number of paths from $ s $ to $ t $ such that their length differs from the length of the shortest path by no more than $ 1 $ .

Since this number may be too large, output it modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2
```

### 输出

```
2
4
1
11
```



---

---
title: "Skipping"
layout: "post"
diff: 普及+/提高
pid: CF2023B
tag: ['动态规划 DP', '图论', '线段树', '最短路']
---

# Skipping

## 题目描述

现在已经是3024年了，出题的想法早就枯竭。现今的OI以一种修改后的个人参赛形式进行。比赛有$n$道题，编号从$1$到$n$，一道题有一个分数$a_i$和一个参数$b_i$。最开始，评测系统会把第$1$道题丢给选手。当一个选手拿到第$i$道题，他有两个选择：

- 提交，获得$a_i$分
- 跳过，但他再不能去交这道题了。

接下来，评测系统会把编号最大的符合下述条件的题目$j$丢给选手：

- 如果选手提交了$i$题，那么$j<i$
- 如果选手选择跳过，那么$j\leq b_i$

系统不能给选手一道之前给过的题目。如果系统找不到这样的题，那么比赛结束。特别的，如果选手提交第一题，比赛结束。

请你帮助小p拿到最高的可能得分。

## 输入格式

此题**多测**，第一行一个整数$t(1\leq t\leq 10^5$，为测试数据组数。每组数据如下：

第一行一个整数$n(1\leq n\leq 4\cdot10^5)$，表示题目数量

第二行一行$n$个整数$a_1,a_2……a_n(1\leq a_i\leq 10^9)$表示题目分数。

第三行一行$n$个整数$b_1,b_2……b_n(1\leq b_i\leq n)$表示题目参数。

保证所有测试数据的$\sum n$不超过$4\cdot 10^5$。

## 输出格式

每行输出一个整数，为小p最大的可能得分。

## 样例 #1

### 输入

```
4
2
15 16
2 1
5
10 10 100 100 1000
3 4 1 1 1
3
100 49 50
3 2 2
4
100 200 300 1000
2 3 4 1
```

### 输出

```
16
200
100
1000
```



---

---
title: "Cool Graph"
layout: "post"
diff: 普及+/提高
pid: CF2029D
tag: ['图论', '构造']
---

# Cool Graph

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges.

You can perform the following operation at most $ 2\cdot \max(n,m) $ times:

- Choose three distinct vertices $ a $ , $ b $ , and $ c $ , then for each of the edges $ (a,b) $ , $ (b,c) $ , and $ (c,a) $ , do the following: 
  - If the edge does not exist, add it. On the contrary, if it exists, remove it.

A graph is called cool if and only if one of the following holds:

- The graph has no edges, or
- The graph is a tree.

You have to make the graph cool by performing the above operations. Note that you can use at most $ 2\cdot \max(n,m) $ operations.

It can be shown that there always exists at least one solution.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 3\le n\le 10^5 $ , $ 0\le m\le \min\left(\frac{n(n-1)}{2},2\cdot 10^5\right) $ ) — the number of vertices and the number of edges.

Then $ m $ lines follow, the $ i $ -th line contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i,v_i\le n $ ) — the two nodes that the $ i $ -th edge connects.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , and the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ .

It is guaranteed that there are no self-loops or multiple-edges in the given graph.

## 输出格式

For each test case, in the first line output an integer $ k $ ( $ 0\le k\le 2\cdot \max(n, m) $ ) — the number of operations.

Then output $ k $ lines, the $ i $ -th line containing three distinct integers $ a $ , $ b $ , and $ c $ ( $ 1\le a,b,c\le n $ ) — the three integers you choose in the $ i $ -th operation.

If there are multiple solutions, you can output any of them.

## 说明/提示

In the first test case, the graph is already cool because there are no edges.

In the second test case, after performing the only operation, the graph becomes a tree, so it is cool.

In the third test case, the graph is already cool because it is a tree.

In the fourth test case, after performing the only operation, the graph has no edges, so it is cool.

In the fifth test case:

 OperationGraph before the operationGraph after the operation $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/b0f7ac35f24bdd1ef25527e8445c75c07c81b1cd.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/967d0caf549d17edc01f85e8fd3b92d4a29c78a4.png) $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/8fc9b337d57d63328a0f768cb6979898a6acb589.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/e76a67a3a1dfd30fecae063029760f2fec760cd4.png) $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/cd4bbe994192de9db9336eff41b4aa05bb7c27af.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/278495e89dce856c8d1c4a31851cd95fdb2f1cd3.png)Note that after the first operation, the graph has already become cool, and there are two extra operations. As the graph is still cool after the two extra operations, this is a valid answer.

## 样例 #1

### 输入

```
5
3 0
3 1
1 2
3 2
1 2
2 3
3 3
1 2
2 3
3 1
6 6
1 2
1 6
4 5
3 4
4 6
3 6
```

### 输出

```
0
1
1 2 3
0
1
1 2 3
3
1 3 6
2 4 5
3 4 6
```



---

---
title: "Genokraken"
layout: "post"
diff: 普及+/提高
pid: CF2032D
tag: ['图论', '构造']
---

# Genokraken

## 题目描述

This is an interactive problem.

Upon clearing the Waterside Area, Gretel has found a monster named Genokraken, and she's keeping it contained for her scientific studies.

The monster's nerve system can be structured as a tree $ ^{\dagger} $ of $ n $ nodes (really, everything should stop resembling trees all the time $ \ldots $ ), numbered from $ 0 $ to $ n-1 $ , with node $ 0 $ as the root.

Gretel's objective is to learn the exact structure of the monster's nerve system — more specifically, she wants to know the values $ p_1, p_2, \ldots, p_{n-1} $ of the tree, where $ p_i $ ( $ 0 \le p_i < i $ ) is the direct parent node of node $ i $ ( $ 1 \le i \le n - 1 $ ).

She doesn't know exactly how the nodes are placed, but she knows a few convenient facts:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths $ ^{\ddagger} $ . Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- The nodes are indexed in a way that if $ 1 \le x \le y \le n - 1 $ , then $ p_x \le p_y $ .
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)The tree in this picture does not satisfy the condition, because if we remove node $ 0 $ , then node $ 2 $ (which was initially adjacent to the node $ 0 $ ) will not be the end of the path $ 4-2-5 $ .The tree in this picture does not satisfy the condition, because $ p_3 \le p_4 $ must hold.The tree in this picture does not satisfy the condition, because node $ 1 $ has only one adjacent node.Gretel can make queries to the containment cell:

- "? a b" ( $ 1 \le a, b < n $ , $ a \ne b $ ) — the cell will check if the simple path between nodes $ a $ and $ b $ contains the node $ 0 $ .

However, to avoid unexpected consequences by overstimulating the creature, Gretel wants to query at most $ 2n - 6 $ times. Though Gretel is gifted, she can't do everything all at once, so can you give her a helping hand?

 $ ^{\dagger} $ A tree is a connected graph where every pair of distinct nodes has exactly one simple path connecting them.

 $ ^{\ddagger} $ A path is a tree whose vertices can be listed in the order $ v_1, v_2, \ldots, v_k $ such that the edges are $ (v_i, v_{i+1}) $ ( $ 1 \le i < k $ ).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^4 $ ) — the number of nodes in Genokraken's nerve system.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, interaction starts by reading the integer $ n $ .

Then you can make queries of the following type:

- "? a b" (without quotes) ( $ 1 \le a, b < n $ , $ a \ne b $ ).

After the query, read an integer $ r $ — the answer to your query. You are allowed to use at most $ 2n - 6 $ queries of this type.

- If the simple path between nodes $ a $ and $ b $ does not contain node $ 0 $ , you will get $ r = 0 $ .
- If the simple path between nodes $ a $ and $ b $ contains node $ 0 $ , you will get $ r = 1 $ .
- In case you make more than $ 2n-6 $ queries or make an invalid query, you will get $ r = -1 $ . You will need to terminate after this to get the "Wrong answer" verdict. Otherwise, you can get an arbitrary verdict because your solution will continue to read from a closed stream.

When you find out the structure, output a line in the format "! $ p_1 \space p_2 \ldots p_{n-1} $ " (without quotes), where $ p_i $ ( $ 0 \le p_i < i $ ) denotes the index of the direct parent of node $ i $ . This query is not counted towards the $ 2n - 6 $ queries limit.

After solving one test case, the program should immediately move on to the next one. After solving all test cases, the program should be terminated immediately.

After printing any query do not forget to output an end of line and flush the output buffer. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

The interactor is non-adaptive. The tree does not change during the interaction.

Hacks

For hack, use the following format:

The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^4 $ ) — the number of nodes in Genokraken's nerve system.

The second line of each test case contains $ n-1 $ integers $ p_1, p_2, \ldots, p_{n-1} $ ( $ 0 \le p_1 \le p_2 \le \ldots \le p_{n-1} \le n - 2 $ , $ 0 \le p_i < i $ ) — the direct parents of node $ 1 $ , $ 2 $ , ..., $ n-1 $ in the system, respectively.

In each test case, the values $ p_1, p_2, \ldots, p_{n-1} $ must ensure the following in the tree:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths. Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

The sum of $ n $ over all test cases must not exceed $ 10^4 $ .

## 说明/提示

In the first test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .

In the second test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .
- The answer to "? 2 4" is $ 0 $ . This means that the simple path between nodes $ 2 $ and $ 4 $ doesn't contain node $ 0 $ .

In the third test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

## 样例 #1

### 输入

```
3
4

1

5

1

0

9
```

### 输出

```
? 2 3

! 0 0 1

? 2 3

? 2 4

! 0 0 1 2

! 0 0 0 1 3 5 6 7
```



---

---
title: "Another Exercise on Graphs (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2057E1
tag: ['图论', '最短路']
---

# Another Exercise on Graphs (Easy Version)

## 题目描述

这是该问题的简单版本。不同版本间的区别在于此版本对 $m$ 有额外约束。只有在你解决了该问题的所有版本后，才能进行 hack。

最近，"T-generation" 的导师需要筹备一场训练赛。他们发现缺少一道题目，且整场比赛中没有图论相关的问题，于是设计了如下题目。

给定一个包含 $n$ 个顶点和 $m$ 条边的连通带权无向图，图中无自环和重边。

处理 $q$ 次形如 $(a, b, k)$ 的查询：在从顶点 $a$ 到顶点 $b$ 的所有路径中，找出路径上边权的第 $k$ 小最大值$^{\dagger}$。

导师们认为这个问题非常有趣，但存在一个问题：他们不知道如何解决它。请帮助他们解决这个问题，因为距离比赛开始仅剩几小时。

$^{\dagger}$ 设 $w_1 \ge w_2 \ge \ldots \ge w_{h}$ 为某条路径中所有边权按非递增顺序排列后的结果。该路径边权的第 $k$ 大值即为 $w_{k}$。


## 输入格式

每个测试包含多个测试用例。第一行输入一个整数 $t$（$1 \le t \le 100$）表示测试用例数量。每个测试用例的描述如下：

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $q$（$2 \le n \le 400$，$n - 1 \le m \le \operatorname{min}(\mathbf{400}, \frac{n \cdot (n - 1)}{2})$，$1 \le q \le 3 \cdot 10^5$）分别表示顶点数、边数和查询数。

接下来每个测试用例的 $m$ 行中，每行包含三个整数 $v$、$u$ 和 $w$（$1 \le v, u \le n$，$1 \le w \le 10^9$）表示一条边的两个端点及其权重。保证图中无自环和重边。

接下来每个测试用例的 $q$ 行中，每行包含三个整数 $a$、$b$ 和 $k$（$1 \le a, b \le n$，$k \ge 1$）表示一次查询。保证从顶点 $a$ 到顶点 $b$ 的任何路径至少包含 $k$ 条边。

保证所有测试用例的 $n$ 之和不超过 $400$。

保证所有测试用例的 $m$ 之和不超过 $400$。

保证所有测试用例的 $q$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出所有查询的答案。

## 说明/提示

在第一个测试用例中，第一次查询的最优路径之一是 $1 \rightarrow 3 \rightarrow 4$，该路径边权的第 $2$ 大值为 $1$。第二次查询的最优路径之一是 $2 \rightarrow 4 \rightarrow 3$，边权的第 $1$ 大值为 $2$。

在第二个测试用例中，第一次查询的最优路径之一是 $1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 6$，该路径边权的第 $3$ 大值为 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4 4 2
1 2 2
2 4 2
1 3 4
3 4 1
1 4 2
2 3 1
6 7 3
1 2 10
2 3 3
3 4 9
4 5 2
5 6 1
2 4 10
4 6 10
1 6 3
1 6 2
2 4 1
11 17 10
1 4 5
1 3 19
1 2 10
3 2 13
4 5 1
4 6 11
3 5 9
3 6 18
2 7 17
5 8 15
5 10 8
6 9 4
7 10 20
7 8 16
8 11 3
9 11 6
10 11 14
3 11 1
3 11 3
1 11 1
1 11 4
1 11 3
8 2 2
10 4 1
3 9 2
3 9 1
6 7 3
```

### 输出

```
1 2
2 9 9
11 3 11 1 3 10 8 4 11 4
```



---

---
title: "Object Identification"
layout: "post"
diff: 普及+/提高
pid: CF2066A
tag: ['图论']
---

# Object Identification

## 题目描述

这是一道交互题。

给定一个由 $1$ 到 $n$ 的整数构成的数组 $x_1, \ldots, x_n$。评测方还拥有一个固定但隐藏的数组 $y_1, \ldots, y_n$，其元素也是 $1$ 到 $n$ 的整数。数组 $y$ 的元素对你未知。此外，已知对于所有 $i$，$x_i \neq y_i$，且所有有序对 $(x_i, y_i)$ 互不相同。

评测方秘密选择了以下两个对象之一，你需要判断具体是哪一个：

- 对象 A：一个包含 $n$ 个顶点（编号为 $1$ 到 $n$）的有向图，包含 $n$ 条形如 $x_i \to y_i$ 的边。
- 对象 B：坐标系上的 $n$ 个点，其中第 $i$ 个点的坐标为 $(x_i, y_i)$。

为了猜测评测方选择的对象，你可以进行查询。每次查询需指定两个数字 $i, j$（$1 \leq i, j \leq n, i \neq j$）。作为回应，你将得到一个数值：

- 若评测方选择对象 A，则返回顶点 $i$ 到顶点 $j$ 的最短路径长度（以边数为单位），若无路径则返回 $0$。
- 若评测方选择对象 B，则返回点 $i$ 与点 $j$ 的曼哈顿距离，即 $|x_i - x_j| + |y_i - y_j|$。

你最多可以进行 $2$ 次查询来确定评测方选择的对象。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 1000$）。随后为各测试用例的描述。

## 输出格式

交互开始时，首先读取 $n$（$3 \leq n \leq 2 \cdot 10^5$）——每个测试用例中数组 $x$ 和 $y$ 的长度。

接下来读取 $n$ 个整数：$x_1, x_2, \ldots, x_n$（$1 \leq x_i \leq n$）——数组 $x$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

每个测试用例的数组 $y_1, y_2, \ldots, y_n$ 是固定的。即交互器不具有自适应性。

保证对于所有 $1 \leq i \leq n$，有 $x_i \neq y_i$，且所有有序对 $(x_i, y_i)$ 互不相同。

要进行查询，请输出 "? $i$ $j$"（不含引号，$1 \le i, j \le n, i \neq j$）。随后需读取查询的响应值（非负整数）。

给出答案时，若隐藏对象为 A 则输出 "! A"，若为 B 则输出 "! B"（不含引号）。注意输出答案不计入 $2$ 次查询次数。

每次输出查询后，请勿忘记换行并刷新输出缓冲区$^{\text{∗}}$，否则将导致超时错误。若在任何交互步骤中读取到 $-1$，必须立即终止程序。这意味着你的程序将因无效查询或其他错误而获得错误答案判定。未能及时终止可能导致不确定的评测结果，因为程序会尝试从已关闭的流中读取数据。注意若查询合法，响应值永远不会为 $-1$。

Hacks 说明

第一行必须包含整数 $t$（$1 \le t \le 1000$）——测试用例数。

每个测试用例的第一行必须包含整数 $n$（$3 \le n \le 2 \cdot 10^5$）——隐藏数组的长度。

第二行必须包含 $n$ 个整数——$x_1, x_2, \ldots, x_n$（$1 \le x_i \le n$）。

第三行必须包含 $n$ 个整数——$y_1, y_2, \ldots, y_n$（$1 \le y_i \le n$）。

必须确保对于所有 $1 \le i \le n$，有 $x_i \neq y_i$，且所有有序对 $(x_i, y_i)$ 互不相同。

第四行必须包含一个字符 A 或 B，表示要隐藏的对象类型。

所有测试用例的 $n$ 之和不得超过 $2 \cdot 10^5$。

$^{\text{∗}}$ 刷新缓冲区方法：

- C++：使用 `fflush(stdout)` 或 `cout.flush()`；
- Python：使用 `sys.stdout.flush()`；
- 其他语言请参考相关文档。

## 说明/提示

第一个测试用例中，$x = [2,2,3]$，$y = [1,3,1]$，隐藏对象为 A。

第二个测试用例中，$x = [5,1,4,2,3]$，$y = [3,3,2,4,1]$，隐藏对象为 B。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3
2 2 3

1

0

5
5 1 4 2 3

4

4
```

### 输出

```
? 2 3

? 1 2

! A

? 1 5

? 5 1

! B
```



---

---
title: "Baggage Claim"
layout: "post"
diff: 普及+/提高
pid: CF2097B
tag: ['图论', '并查集']
---

# Baggage Claim

## 题目描述

每个机场都有一个行李提取区，Balbesovo 机场也不例外。某天，Sheremetyevo 机场的一位管理员提出了一个不同寻常的想法：将传统的行李传送带形状从旋转盘改为更复杂的形式。

假设行李提取区被表示为一个 $n \times m$ 的矩形网格。管理员提议传送带的路径应穿过单元格 $p_1, p_2, \ldots, p_{2k+1}$，其中 $p_i = (x_i, y_i)$。

对于每个单元格 $p_i$ 和下一个单元格 $p_{i+1}$（其中 $1 \leq i \leq 2k$），这两个单元格必须共享一条公共边。此外，路径必须是简单的，即对于任意两个不同的索引 $i \neq j$，单元格 $p_i$ 和 $p_j$ 不能重合。

不幸的是，路径计划被意外洒出的咖啡弄脏了，只保留了路径中奇数索引的单元格：$p_1, p_3, p_5, \ldots, p_{2k+1}$。你的任务是给定这些 $k+1$ 个单元格，计算恢复原始完整路径 $p_1, p_2, \ldots, p_{2k+1}$ 的可能方式的数量。

由于答案可能非常大，请输出其对 $10^9+7$ 取模的结果。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 3 \cdot 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $k$（$1 \le n, m \le 1000$，$n \cdot m \ge 3$，$1 \le k \le \left\lfloor \frac12 (n m - 1) \right\rfloor$）—— 网格的尺寸和定义路径长度的参数。

接下来是 $k+1$ 行，第 $i$ 行包含两个整数 $x_{2i-1}$ 和 $y_{2i-1}$（$1 \le x_{2i-1} \le n$，$1 \le y_{2i-1} \le m$）—— 路径上单元格 $p_{2i-1}$ 的坐标。

保证所有 $(x_{2i-1}, y_{2i-1})$ 对都是不同的。

保证所有测试用例的 $n \cdot m$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出一个整数——恢复原始完整路径的方式数量对 $10^9+7$ 取模的结果。

## 说明/提示

在第一个测试用例中，有两种可能的路径：

- $(1,1) \to (2,1) \to (2, 2) \to (2, 3) \to (2, 4)$
- $(1,1) \to (1,2) \to (2, 2) \to (2, 3) \to (2, 4)$

在第二个测试用例中，没有合适的路径，因为单元格 $(1,1)$ 和 $(1,4)$ 没有共同的相邻单元格。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 4 2
1 1
2 2
2 4
1 4 1
1 1
1 4
5 5 11
2 5
3 4
4 5
5 4
4 3
5 2
4 1
3 2
2 1
1 2
2 3
1 4
3 4 4
1 2
2 1
3 2
2 3
3 4
3 3 2
2 2
1 1
1 3
```

### 输出

```
2
0
2
5
1
```



---

---
title: "D/D/D"
layout: "post"
diff: 普及+/提高
pid: CF2109D
tag: ['图论', '最短路']
---

# D/D/D

## 题目描述

当然，这道以字母 D 开头的题目是由 Declan Akaba 赞助的。

给定一个简单、连通的无向图，包含 $n$ 个顶点和 $m$ 条边。图中没有自环或重边。同时给定一个包含 $\ell$ 个元素的多重集 $A$：
$$ A = \{A_1, A_2, \ldots, A_\ell\} $$

从顶点 $1$ 出发，你可以执行以下操作任意次数（只要多重集 $A$ 不为空）：
- 从多重集 $A$ 中选择一个元素 $k$ 并移除它（必须移除 $k$ 的一个实例）。
- 遍历恰好包含 $k$ 条边的任意路径$^{\text{∗}}$，到达某个顶点（可以是起始顶点本身）。

对于每个 $i$（$1 \le i \le n$），判断是否存在一个操作序列，使得从顶点 $1$ 出发，使用原始多重集 $A$，最终能到达顶点 $i$。

注意：对每个顶点 $i$ 的检查是独立的——每次都需要从顶点 $1$ 重新开始，并使用原始多重集 $A$。

$^{\text{∗}}$ 长度为 $k$ 的路径是指一个顶点序列 $v_0, v_1, \ldots, v_{k-1}, v_k$，其中每对相邻顶点 $(v_i, v_{i+1})$ 都由图中的一条边连接。序列中允许包含重复的顶点。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例描述。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $\ell$（$2 \leq n \leq 2 \cdot 10^5$，$n-1 \leq m \leq 4 \cdot 10^5$，$1 \leq \ell \leq 2 \cdot 10^5$）——分别表示顶点数、边数和多重集的大小。

第二行包含 $\ell$ 个整数 $A_1, A_2, \ldots, A_{\ell}$（$1 \leq A_i \leq 10^4$）——多重集的元素。

接下来的 $m$ 行，每行包含两个整数 $u$ 和 $v$（$1 \le u < v \le n$）——表示图中的一条边。

保证边构成一个简单、连通的无向图，没有自环或重边。

保证所有测试用例的 $n$ 之和、$m$ 之和以及 $\ell$ 之和分别不超过 $2 \cdot 10^5$、$4 \cdot 10^5$ 和 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出一个长度为 $n$ 的二进制字符串，其中第 $i$ 个字符为 $\mathtt{1}$ 表示存在到达顶点 $i$ 的操作序列，否则为 $\mathtt{0}$。


## 说明/提示

**第一个测试用例解释：**
- 顶点 $1$ 无需任何操作即可到达。
- 顶点 $2$ 可通过选择 $A$ 中的元素 $3$ 到达，例如路径 $[1 \rightarrow 2 \rightarrow 1 \rightarrow 2]$。
- 顶点 $3$ 可通过选择 $A$ 中的元素 $2$ 并走路径 $[1 \rightarrow 2 \rightarrow 3]$ 到达。
- 顶点 $4$ 可通过选择 $A$ 中的元素 $3$ 并走路径 $[1 \rightarrow 2 \rightarrow 3 \rightarrow 4]$ 到达。
- 顶点 $5$ 无法通过任何有效操作序列到达。
- 顶点 $6$ 可通过以下方式到达：
  1. 选择 $A$ 中的元素 $2$ 并走路径 $[1 \rightarrow 2 \rightarrow 3]$；
  2. 选择 $A$ 中的元素 $3$ 并走路径 $[3 \rightarrow 4 \rightarrow 5 \rightarrow 6]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
6 5 2
2 3
1 2
2 3
3 4
4 5
5 6
5 5 1
5
1 2
2 3
3 4
4 5
3 5
5 4 3
100 200 300
1 2
1 3
1 4
2 5
```

### 输出

```
111101
11111
10001
```



---

---
title: "Fewer Batteries"
layout: "post"
diff: 普及+/提高
pid: CF2110D
tag: ['动态规划 DP', '图论', '二分']
---

# Fewer Batteries

## 题目描述

在 2077 年机器人统治世界后，它们决定进行以下比赛。

有 $n$ 个检查点，第 $i$ 个检查点包含 $b_i$ 块电池。机器人最初从第 $1$ 个检查点出发，不带任何电池，必须到达第 $n$ 个检查点。

检查点之间共有 $m$ 条单向通道。第 $i$ 条通道允许从点 $s_i$ 移动到点 $t_i$（$s_i < t_i$），但不能反向移动。此外，只有当机器人拥有至少 $w_i$ 块充满电的电池时，才能使用第 $i$ 条通道；否则它会在途中耗尽电量。

当机器人到达点 $v$ 时，可以额外获取 $0$ 到 $b_v$（含）之间的任意数量电池。而且，它会携带之前收集的所有电池，并在每个检查点为所有已收集的电池充电。

求机器人旅程结束时能够拥有的最少电池数量，如果无法从第一个检查点到达最后一个检查点，则报告不可能。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例描述。

每个测试用例的第一行包含两个整数 $n, m$（$2 \leq n \leq 2 \cdot 10^5$，$0 \leq m \leq 3 \cdot 10^5$）——分别表示检查点数量和通道数量。

第二行包含 $n$ 个数字 $b_i$（$0 \leq b_i \leq 10^9$）——第 $i$ 个检查点的电池数量。

接下来的 $m$ 行每行包含三个整数 $s_i, t_i, w_i$（$1 \leq s_i < t_i \leq n$，$1 \leq w_i \leq 10^9$）——通道的起点、终点和通过所需的最低电池数量。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。
保证所有测试用例的 $m$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出旅程结束时能够拥有的最少电池数量，如果无法到达点 $n$，则输出 $-1$。


## 说明/提示

在第一个测试用例中，需要在起点获取 $1$ 块电池，然后移动到点 $2$，再移动到点 $3$。

在第二个测试用例中，需要在起点获取 $2$ 块电池，移动到点 $2$ 再获取 $2$ 块电池，移动到点 $4$，最后移动到点 $5$。

在第三个测试用例中，没有从点 $1$ 到点 $n$ 的路径。

在第四个测试用例中，需要在起点获取 $1$ 块电池，移动到点 $2$ 再获取 $9$ 块电池，移动到点 $3$，最后移动到点 $4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
2 0 0
1 2 1
2 3 1
1 3 2
5 6
2 2 5 0 1
1 2 2
1 3 1
1 4 3
3 5 5
2 4 4
4 5 3
2 0
1 1
4 4
3 10 0 0
1 2 1
1 3 3
2 3 10
3 4 5
```

### 输出

```
1
4
-1
10
```



---

---
title: "Reachability and Tree"
layout: "post"
diff: 普及+/提高
pid: CF2112D
tag: ['图论', '构造']
---

# Reachability and Tree

## 题目描述

考虑一个有向图，我们称有序数对 $(u,v)$ 是好的当且仅当 $u\ne v$ 且图中存在一条 $u$ 到 $v$ 的路径。

给你一棵 $n$ 个结点的树，问有没有一种把这棵树的所有 $n-1$ 条边确定方向的方案，使得形成的有向图中恰有 $n$ 个好的数对。如果存在，给出任意一种方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2112D/5e96780aa4a833603401ce38c95583d3dff310ba.png)

对于第一组数据，这是一种可能的定向方案。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 10^4)$，表示数据组数。

对于每组数据，第一行输入一个正整数 $n(2\le n\le 2\times 10^5)$。

接下来 $n-1$ 行，每行输入两个整 $u_i,v_i(1\le u_i,v_i\le n,n_i\ne v_i)$，表示树上的一条边。

保证每组数据输入的图均构成一棵无向树。保证单个测试点内 $n$ 的和不超过 $2\times 10^5$。

## 输出格式

对于每组数据，如果不存在定向方案使得形成的有向图中恰有 $n$ 个好的数对，输出一行 `NO`（大小写不敏感）。

否则，输出一行 `YES`（大小写不敏感），接下来输出 $n-1$ 行，每行两个正整数 $u_i,v_i$，表示你给出的方案形成的有向图中一条结点 $u_i$ 指向结点 $v_i$ 的边。边的输出顺序不限。如果有多种解，输出任意一种均可。

## 说明/提示

**样例解释**

对于第一组数据，一种可能的定向方案如上图所示。在此方案中五个好的数对为 $(3,5),(3,1),(3,2),(1,2),(4,2)$。

对于第二组数据，一种可能的定向方案如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2112D/a9d7677ec7ba1046004aa29fc6e4a4dca863d6eb.png)

在此方案中五个好的数对为 $(2,1),(3,1),(4,1),(5,4),(5,1)$。

对于第三组数据，只有两个有序数对，无论这条唯一的边指向哪个方向，都只有一个数对会是好的。

## 样例 #1

### 输入

```
4
5
1 2
2 4
1 3
3 5
5
1 2
1 3
1 4
4 5
2
2 1
4
3 1
1 2
2 4
```

### 输出

```
YES
1 2
3 1
3 5
4 2
YES
2 1
3 1
4 1
5 4
NO
YES
1 3
2 1
2 4
```



---

---
title: "Omg Graph"
layout: "post"
diff: 普及+/提高
pid: CF2117G
tag: ['图论', '并查集', '最短路']
---

# Omg Graph

## 题目描述

给定一个带权无向连通图，定义一条长度为 $k$ 路径的费用如下：

- 设路径经过边的权值为 $w_1,w_2,\dots,w_k$。
- 路径的费用定义为 $(\min_{i=1}^k w_i) + (\max_{i=1}^k w_i)$，也就是最大的边权加上最小的边权。

请求出所有从结点 $1$ 到结点 $n$ 的路径中最小的费用。注意路径未必是简单路径。

## 输入格式

输入数据包含多个测试用例。输入数据的第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的个数。

对于每个测试用例：

- 第一行包含两个整数 $n$ 和 $m$（$2 \le n \le 2 \cdot 10^5$，$n-1 \le m \le \min\left(2 \cdot 10^5, \frac{n(n-1)}{2}\right)$）。
- 接下来的 $m$ 行中每行包含三个整数 $u$，$v$ 和 $w$（$1 \le u, v \le n$，$1 \le w \le 10^9$），表示一条从结点 $u$ 连接到结点 $v$，权值为 $w$ 的无向边。输入数据保证这些边组成一个连通图，且图中不含自环或重边。

输入数据保证所有测试用例的 $n$ 和 $m$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数，代表从结点 $1$ 到结点 $n$ 的最小费用。

## 说明/提示

对于第二个测试用例，最优路径之一是 $1 \rightarrow 2 \rightarrow 1 \rightarrow 3$。经过的边权分别为 $5,5,13$，因此费用为 $\min(5,5,13)+\max(5,5,13)=18$。可以证明不存在费用更低的路径。

## 样例 #1

### 输入

```
4
3 2
1 2 1
2 3 1
3 2
1 3 13
1 2 5
8 9
1 2 6
2 3 5
3 8 6
1 4 7
4 5 4
5 8 7
1 6 5
6 7 5
7 8 5
3 3
1 3 9
1 2 8
2 3 3
```

### 输出

```
2
18
10
11
```



---

---
title: "Flawed Flow"
layout: "post"
diff: 普及+/提高
pid: CF269C
tag: ['图论']
---

# Flawed Flow

## 题目描述

Emuskald considers himself a master of flow algorithms. Now he has completed his most ingenious program yet — it calculates the maximum flow in an undirected graph. The graph consists of $ n $ vertices and $ m $ edges. Vertices are numbered from 1 to $ n $ . Vertices $ 1 $ and $ n $ being the source and the sink respectively.

However, his max-flow algorithm seems to have a little flaw — it only finds the flow volume for each edge, but not its direction. Help him find for each edge the direction of the flow through this edges. Note, that the resulting flow should be correct maximum flow.

More formally. You are given an undirected graph. For each it's undirected edge ( $ a_{i} $ , $ b_{i} $ ) you are given the flow volume $ c_{i} $ . You should direct all edges in such way that the following conditions hold:

1. for each vertex $ v $ $ (1&lt;v&lt;n) $ , sum of $ c_{i} $ of incoming edges is equal to the sum of $ c_{i} $ of outcoming edges;
2. vertex with number $ 1 $ has no incoming edges;
3. the obtained directed graph does not have cycles.

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ n-1<=m<=2·10^{5} $ ), the number of vertices and edges in the graph. The following $ m $ lines contain three space-separated integers $ a_{i} $ , $ b_{i} $ and $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ , $ 1<=c_{i}<=10^{4} $ ), which means that there is an undirected edge from $ a_{i} $ to $ b_{i} $ with flow volume $ c_{i} $ .

It is guaranteed that there are no two edges connecting the same vertices; the given graph is connected; a solution always exists.

## 输出格式

Output $ m $ lines, each containing one integer $ d_{i} $ , which should be 0 if the direction of the $ i $ -th edge is $ a_{i}→b_{i} $ (the flow goes from vertex $ a_{i} $ to vertex $ b_{i} $ ) and should be 1 otherwise. The edges are numbered from 1 to $ m $ in the order they are given in the input.

If there are several solutions you can print any of them.

## 说明/提示

In the first test case, 10 flow units pass through path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/112cc3d7bc5d5ae260d516a02ced6ab796839bee.png), and 5 flow units pass directly from source to sink: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/851f40f264708d94590f3171217fe3d9e053dcee.png).

## 样例 #1

### 输入

```
3 3
3 2 10
1 2 10
3 1 5

```

### 输出

```
1
0
1

```

## 样例 #2

### 输入

```
4 5
1 2 10
1 3 10
2 3 5
4 2 15
3 4 5

```

### 输出

```
0
0
1
1
0

```



---

---
title: "Balance"
layout: "post"
diff: 普及+/提高
pid: CF317C
tag: ['图论']
---

# Balance

## 题目描述

A system of $ n $ vessels with water is given. Several pairs of vessels are connected by tubes with transfusion mechanisms. One may transfer an integer amount of liters of water between two vessels connected by such tube (tube works in both directions). There might be multiple tubes between two vessels. Total number of tubes equals $ e $ . Volume of each vessel equals $ v $ liters. Of course, the amount of the water in any vessel cannot exceed $ v $ liters in the process of transfusions.

Given the initial amounts $ a_{i} $ of water in the vessels and the desired amounts $ b_{i} $ find a sequence of transfusions that deals with the task. Total number of transfusions must not exceed $ 2·n^{2} $ .

## 输入格式

First line of the input contains integers $ n $ , $ v $ , $ e $ ( $ 1<=n<=300 $ , $ 1<=v<=10^{9} $ , $ 0<=e<=50000 $ ).

Next two lines contain $ n $ integers each: initial $ a_{i} $ and the desired amounts $ b_{i} $ of water in corresponding vessels ( $ 0<=a_{i},b_{i}<=v $ ).

Next $ e $ lines describe one tube each in the format $ x $ $ y $ ( $ 1<=x,y<=n,x≠y $ ) for a tube between vessels number $ x $ and $ y $ . There might be multiple tubes between two vessels. You may assume that vessels are numbered from 1 to $ n $ in some way.

## 输出格式

Print "NO" (without quotes), if such sequence of transfusions does not exist.

Otherwise print any suitable sequence in the following format. On the first line print the total number of transfusions $ k $ ( $ k $ should not exceed $ 2·n^{2} $ ). In the following $ k $ lines print transfusions in the format $ x $ $ y $ $ d $ (transfusion of $ d $ liters from the vessel number $ x $ to the vessel number $ y $ , $ x $ and $ y $ must be distinct). For all transfusions $ d $ must be a non-negative integer.

## 样例 #1

### 输入

```
2 10 1
1 9
5 5
1 2

```

### 输出

```
1
2 1 4

```

## 样例 #2

### 输入

```
2 10 0
5 2
4 2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
2 10 0
4 2
4 2

```

### 输出

```
0

```



---

---
title: "Inna and Dima"
layout: "post"
diff: 普及+/提高
pid: CF374C
tag: ['图论', '深度优先搜索 DFS']
---

# Inna and Dima

## 题目描述

Inna and Dima bought a table of size $ n×m $ in the shop. Each cell of the table contains a single letter: "D", "I", "M", "A".

Inna loves Dima, so she wants to go through his name as many times as possible as she moves through the table. For that, Inna acts as follows:

1. initially, Inna chooses some cell of the table where letter "D" is written;
2. then Inna can move to some side-adjacent table cell that contains letter "I"; then from this cell she can go to one of the side-adjacent table cells that contains the written letter "M"; then she can go to a side-adjacent cell that contains letter "A". Then Inna assumes that she has gone through her sweetheart's name;
3. Inna's next move can be going to one of the side-adjacent table cells that contains letter "D" and then walk on through name DIMA in the similar manner. Inna never skips a letter. So, from the letter "D" she always goes to the letter "I", from the letter "I" she always goes the to letter "M", from the letter "M" she always goes to the letter "A", and from the letter "A" she always goes to the letter "D".

Depending on the choice of the initial table cell, Inna can go through name DIMA either an infinite number of times or some positive finite number of times or she can't go through his name once. Help Inna find out what maximum number of times she can go through name DIMA.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ $ (1<=n,m<=10^{3}) $ .

Then follow $ n $ lines that describe Inna and Dima's table. Each line contains $ m $ characters. Each character is one of the following four characters: "D", "I", "M", "A".

Note that it is not guaranteed that the table contains at least one letter "D".

## 输出格式

If Inna cannot go through name DIMA once, print on a single line "Poor Dima!" without the quotes. If there is the infinite number of names DIMA Inna can go through, print "Poor Inna!" without the quotes. Otherwise print a single integer — the maximum number of times Inna can go through name DIMA.

## 说明/提示

Notes to the samples:

In the first test sample, Inna cannot go through name DIMA a single time.

In the second test sample, Inna can go through the infinite number of words DIMA. For that, she should move in the clockwise direction starting from the lower right corner.

In the third test sample the best strategy is to start from the cell in the upper left corner of the table. Starting from this cell, Inna can go through name DIMA four times.

## 样例 #1

### 输入

```
1 2
DI

```

### 输出

```
Poor Dima!

```

## 样例 #2

### 输入

```
2 2
MA
ID

```

### 输出

```
Poor Inna!

```

## 样例 #3

### 输入

```
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID

```

### 输出

```
4

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
title: "The Child and Toy"
layout: "post"
diff: 普及+/提高
pid: CF437C
tag: ['图论', '贪心']
---

# The Child and Toy

## 题目描述

On Children's Day, the child got a toy from Delayyy as a present. However, the child is so naughty that he can't wait to destroy the toy.

The toy consists of $ n $ parts and $ m $ ropes. Each rope links two parts, but every pair of parts is linked by at most one rope. To split the toy, the child must remove all its parts. The child can remove a single part at a time, and each remove consume an energy. Let's define an energy value of part $ i $ as $ v_{i} $ . The child spend $ v_{f1}+v_{f2}+...+v_{fk} $ energy for removing part $ i $ where $ f_{1},f_{2},...,f_{k} $ are the parts that are directly connected to the $ i $ -th and haven't been removed.

Help the child to find out, what is the minimum total energy he should spend to remove all $ n $ parts.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=1000 $ ; $ 0<=m<=2000 $ ). The second line contains $ n $ integers: $ v_{1},v_{2},...,v_{n} $ ( $ 0<=v_{i}<=10^{5} $ ). Then followed $ m $ lines, each line contains two integers $ x_{i} $ and $ y_{i} $ , representing a rope from part $ x_{i} $ to part $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n; x_{i}≠y_{i} $ ).

Consider all the parts are numbered from $ 1 $ to $ n $ .

## 输出格式

Output the minimum total energy the child should spend to remove all $ n $ parts of the toy.

## 说明/提示

One of the optimal sequence of actions in the first sample is:

- First, remove part $ 3 $ , cost of the action is $ 20 $ .
- Then, remove part $ 2 $ , cost of the action is $ 10 $ .
- Next, remove part $ 4 $ , cost of the action is $ 10 $ .
- At last, remove part $ 1 $ , cost of the action is $ 0 $ .

So the total energy the child paid is $ 20+10+10+0=40 $ , which is the minimum.

In the second sample, the child will spend $ 400 $ no matter in what order he will remove the parts.

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 4
1 2
2 3

```

### 输出

```
40

```

## 样例 #2

### 输入

```
4 4
100 100 100 100
1 2
2 3
2 4
3 4

```

### 输出

```
400

```

## 样例 #3

### 输入

```
7 10
40 10 20 10 20 80 40
1 5
4 7
4 5
5 2
5 7
6 4
1 6
1 3
4 3
1 4

```

### 输出

```
160

```



---

---
title: "Pashmak and Graph"
layout: "post"
diff: 普及+/提高
pid: CF459E
tag: ['动态规划 DP', '图论']
---

# Pashmak and Graph

## 题目描述

Pashmak's homework is a problem about graphs. Although he always tries to do his homework completely, he can't solve this problem. As you know, he's really weak at graph theory; so try to help him in solving the problem.

You are given a weighted directed graph with $ n $ vertices and $ m $ edges. You need to find a path (perhaps, non-simple) with maximum number of edges, such that the weights of the edges increase along the path. In other words, each edge of the path must have strictly greater weight than the previous edge in the path.

Help Pashmak, print the number of edges in the required path.

## 输入格式

The first line contains two integers $ n $ , $ m $ $ (2<=n<=3·10^{5}; 1<=m<=min(n·(n-1),3·10^{5})) $ . Then, $ m $ lines follows. The $ i $ -th line contains three space separated integers: $ u_{i} $ , $ v_{i} $ , $ w_{i} $ $ (1<=u_{i},v_{i}<=n; 1<=w_{i}<=10^{5}) $ which indicates that there's a directed edge with weight $ w_{i} $ from vertex $ u_{i} $ to vertex $ v_{i} $ .

It's guaranteed that the graph doesn't contain self-loops and multiple edges.

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first sample the maximum trail can be any of this trails: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/46950f7ebb1a8fb1042610e7d90ce693216dd148.png).

In the second sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/0a8ef1a8d44f73ed1581f13e754f7328cc98bdea.png).

In the third sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/077a752077571978dd842d2ca5ed7e4dcecd7b85.png).

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 2
3 1 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4

```

### 输出

```
6

```



---

---
title: "Fox And Names"
layout: "post"
diff: 普及+/提高
pid: CF510C
tag: ['字符串', '图论建模', '拓扑排序']
---

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ): number of names.

Each of the following $ n $ lines contain one string $ name_{i} $ ( $ 1<=|name_{i}|<=100 $ ), the $ i $ -th name. Each name contains only lowercase Latin letters. All names are different.

## 输出格式

If there exists such order of letters that the given names are sorted lexicographically, output any such order as a permutation of characters 'a'–'z' (i. e. first output the first letter of the modified alphabet, then the second, and so on).

Otherwise output a single word "Impossible" (without quotes).

## 样例 #1

### 输入

```
3
rivest
shamir
adleman

```

### 输出

```
bcdefghijklmnopqrsatuvwxyz

```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever

```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz

```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck

```

### 输出

```
acbdefhijklmnogpqrstuvwxyz

```



---

