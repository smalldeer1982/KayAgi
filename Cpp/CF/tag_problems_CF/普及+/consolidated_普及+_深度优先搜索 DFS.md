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
title: "Minimum path"
layout: "post"
diff: 普及+/提高
pid: CF1031D
tag: ['广度优先搜索 BFS', '深度优先搜索 DFS']
---

# Minimum path

## 题目描述

给你一个n×n的全是小写字母的矩阵,你能改变k个字母



你要从左上角走到右下角,且每步只能移动到右边或下边的字母上。



对于每一条路径都会得到一个由你经过的所有字母组成的字符串。当然,他的长度是2×n-1.



在你最多改动k个字母的情况下,找到一个得到字符串字典序最小的路径.



一个字符串a如果字典序比字符串b小,那他们第一个不同的字符在a中小于b.

## 输入格式

第一行包括两个整数n和k(1≤n≤2000,0≤k≤n2),矩阵的大小和你最多能改变的字母数.



下面n行,每行n个小写字母.

## 输出格式

在你最多改动k个字母的情况下,得到的一个字符串字典序最小的路径.

## 样例 #1

### 输入

```
4 2
abcd
bcde
bcad
bcde

```

### 输出

```
aaabcde

```

## 样例 #2

### 输入

```
5 3
bwwwz
hrhdh
sepsp
sqfaf
ajbvw

```

### 输出

```
aaaepfafw

```

## 样例 #3

### 输入

```
7 6
ypnxnnp
pnxonpm
nxanpou
xnnpmud
nhtdudu
npmuduh
pmutsnz

```

### 输出

```
aaaaaaadudsnz

```



---

---
title: "Fools and Roads"
layout: "post"
diff: 普及+/提高
pid: CF191C
tag: ['深度优先搜索 DFS', '最近公共祖先 LCA', '差分']
---

# Fools and Roads

## 题目描述

有一颗 $n$  个节点的树，$k$  次旅行，问每一条边被走过的次数。

## 输入格式

第一行一个整数 $n$  （$2\leq n\leq 10^5$ ）。

接下来 $n-1$  行，每行两个正整数 $x,y$  （$1\leq x,y\leq n,x\neq y$ ），表示 $x$  与 $y$  之间有一条连边。

接下来一个整数 $k$  （$0\leq k\leq 10^5$ ）。

接下来 $k$  行，每行两个正整数 $x,y$  （$1\leq x,y\leq n$ ），表示有一个从 $x$  到 $y$  的旅行。

## 输出格式

一行空格分隔的 $n - 1$ 个整数，按输入顺序输出每一条边被走过的次数。

Translated by @larryzhong

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5
2
1 4
3 5

```

### 输出

```
2 1 1 1 

```

## 样例 #2

### 输入

```
5
3 4
4 5
1 4
2 4
3
2 3
1 3
3 5

```

### 输出

```
3 1 1 1 

```



---

---
title: "Microcycle"
layout: "post"
diff: 普及+/提高
pid: CF1927F
tag: ['并查集', '深度优先搜索 DFS', '生成树']
---

# Microcycle

## 题目描述

Given an undirected weighted graph with $ n $ vertices and $ m $ edges. There is at most one edge between each pair of vertices in the graph, and the graph does not contain loops (edges from a vertex to itself). The graph is not necessarily connected.

A cycle in the graph is called simple if it doesn't pass through the same vertex twice and doesn't contain the same edge twice.

Find any simple cycle in this graph in which the weight of the lightest edge is minimal.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 3 \le n \le m \le \min(\frac{n\cdot(n - 1)}{2}, 2 \cdot 10^5) $ ) — the size of the graph and the number of edges.

The next $ m $ lines of the test case contain three integers $ u $ , $ v $ , and $ w $ ( $ 1 \le u, v \le n $ , $ u \ne v $ , $ 1 \le w \le 10^6 $ ) — vertices $ u $ and $ v $ are connected by an edge of weight $ w $ .

It is guaranteed that there is at most one edge between each pair of vertices. Note that under the given constraints, there is always at least one simple cycle in the graph.

It is guaranteed that the sum of the values of $ m $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a pair of numbers $ b $ and $ k $ , where:

- $ b $ — the minimum weight of the edge in the found cycle,
- $ k $ — the number of vertices in the found cycle.

On the next line, output $ k $ numbers from $ 1 $ to $ n $ — the vertices of the cycle in traversal order.

Note that the answer always exists, as under the given constraints, there is always at least one simple cycle in the graph.

## 样例 #1

### 输入

```
5
6 6
1 2 1
2 3 1
3 1 1
4 5 1
5 6 1
6 4 1
6 6
1 2 10
2 3 8
3 1 5
4 5 100
5 6 40
6 4 3
6 15
1 2 4
5 2 8
6 1 7
6 3 10
6 5 1
3 2 8
4 3 4
5 3 6
2 6 6
5 4 5
4 1 3
6 4 5
4 2 1
3 1 7
1 5 5
4 6
2 3 2
1 3 10
1 4 1
3 4 7
2 4 5
1 2 2
4 5
2 1 10
3 1 3
4 2 6
1 4 7
2 3 3
```

### 输出

```
1 3
1 2 3 
3 3
6 4 5 
1 5
4 2 1 6 3 
1 4
1 4 3 2 
3 3
2 3 1
```



---

---
title: "Maximize the Largest Component (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1985H1
tag: ['深度优先搜索 DFS']
---

# Maximize the Largest Component (Easy Version)

## 题目描述

Easy and hard versions are actually different problems, so read statements of both problems completely and carefully. The only difference between the two versions is the operation.

Alex has a grid with $ n $ rows and $ m $ columns consisting of '.' and '\#' characters. A set of '\#' cells forms a connected component if from any cell in this set, it is possible to reach any other cell in this set by only moving to another cell in the set that shares a common side. The size of a connected component is the number of cells in the set.

In one operation, Alex selects any row $ r $ ( $ 1 \le r \le n $ ) or any column $ c $ ( $ 1 \le c \le m $ ), then sets every cell in row $ r $ or column $ c $ to be '\#'. Help Alex find the maximum possible size of the largest connected component of '\#' cells that he can achieve after performing the operation at most once.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \cdot m \le 10^6 $ ) — the number of rows and columns of the grid.

The next $ n $ lines each contain $ m $ characters. Each character is either '.' or '\#'.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the maximum possible size of a connected component of '\#' cells that Alex can achieve.

## 说明/提示

In the second test case, it is optimal for Alex to set all cells in column $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 6 $ .

In the third test case, it is optimal for Alex to set all cells in row $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 9 $ .

In the fourth test case, it is optimal for Alex to set all cells in row $ 4 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 11 $ .

## 样例 #1

### 输入

```
6
1 1
.
4 2
..
#.
#.
.#
3 5
.#.#.
..#..
.#.#.
5 5
#...#
....#
#...#
.....
...##
6 6
.#..#.
#..#..
.#...#
#.#.#.
.#.##.
###..#
6 8
..#....#
.####.#.
###.#..#
.##.#.##
.#.##.##
#..##.#.
```

### 输出

```
1
6
9
11
15
30
```



---

---
title: "DFS Checker (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2002D1
tag: ['深度优先搜索 DFS']
---

# DFS Checker (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, the given tree is a perfect binary tree and the constraints on $ n $ and $ q $ are lower. You can make hacks only if both versions of the problem are solved.

You are given a perfect binary tree $ ^\dagger $ consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a permutation $ p_1, p_2, \ldots, p_n $ of $ [1,2,\ldots,n] $ .

You need to answer $ q $ queries. For each query, you are given two integers $ x $ , $ y $ ; you need to swap $ p_x $ and $ p_y $ and determine if $ p_1, p_2, \ldots, p_n $ is a valid DFS order $ ^\ddagger $ of the given tree.

Please note that the swaps are persistent through queries.

 $ ^\dagger $ A perfect binary tree is a tree with vertex $ 1 $ as its root, with size $ n=2^k-1 $ for a positive integer $ k $ , and where the parent of each vertex $ i $ ( $ 1<i\le n $ ) is $ \left\lfloor\frac{i}{2}\right\rfloor $ . Thus, all leaves of this tree are at a distance $ k - 1 $ from the root.

 $ ^\ddagger $ A DFS order is found by calling the following $ \texttt{dfs} $ function on the given tree.

```
<pre class="lstlisting">```
dfs_order = []<br></br><br></br>function dfs(v):<br></br>    append v to the back of dfs_order<br></br>    pick an arbitrary permutation s of children of v<br></br>    for child in s:<br></br>        dfs(child)<br></br>dfs(1)<br></br>
```
```

Note that the DFS order is not unique.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\le t\le10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ q $ ( $ 3\le n\le 65\,535 $ , $ 2\le q\le 5 \cdot 10^4 $ ) — the number of vertices in the tree and the number of queries. It is guaranteed that $ n=2^k-1 $ for a positive integer $ k $ .

The next line contains $ n-1 $ integers $ a_2,a_3,\ldots,a_n $ ( $ 1\le a_i<i $ ) — the parent of each vertex in the given tree. It is guaranteed that $ a_i=\left\lfloor\frac{i}{2}\right\rfloor $ .

The next line contains $ n $ integers $ p_1,p_2,\ldots,p_n $ ( $ 1\le p_i\le n $ , all $ p_i $ are distinct) — the initial permutation $ p $ .

The next $ q $ lines each contain two integers $ x $ , $ y $ ( $ 1\le x,y\le n,x\neq y $ ) — the positions of the elements to swap in the permutation.

It is guaranteed that the sum of all $ n $ does not exceed $ 65\,535 $ , and the sum of all $ q $ does not exceed $ 5 \cdot 10^4 $ .

## 输出格式

For each test case, print $ q $ lines corresponding to the $ q $ queries. For each query, output $ \texttt{YES} $ if there is a DFS order that exactly equals the current permutation, and output $ \texttt{NO} $ otherwise.

You can output $ \texttt{Yes} $ and $ \texttt{No} $ in any case (for example, strings $ \texttt{yEs} $ , $ \texttt{yes} $ , $ \texttt{Yes} $ and $ \texttt{YES} $ will be recognized as a positive response).

## 说明/提示

In the first test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,3,2],[1,2,3],[3,2,1] $ , respectively. The first two permutations are valid DFS orders; the third is not a DFS order.

In the second test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,2,5,4,3,6,7],[1,3,5,4,2,6,7],[1,3,7,4,2,6,5],[1,3,7,6,2,4,5] $ , respectively.

## 样例 #1

### 输入

```
2
3 3
1 1
1 2 3
2 3
3 2
1 3
7 4
1 1 2 2 3 3
1 2 3 4 5 6 7
3 5
2 5
3 7
4 6
```

### 输出

```
YES
YES
NO
YES
NO
NO
YES
```



---

---
title: "Mirror Maze"
layout: "post"
diff: 普及+/提高
pid: CF2045M
tag: ['模拟', '深度优先搜索 DFS']
---

# Mirror Maze

## 题目描述

# 镜子迷宫


给定一个有\(R\)行（从北到南编号为\(1\)到\(R\)）和\(C\)列（从西到东编号为\(1\)到\(C\)）的网格。这个网格中的每个方格大小相同。位于第\(r\)行和第\(c\)列的方格表示为\((r,c)\)。每个方格要么为空，要么在方格的一条对角线上有一面镜子。每面镜子由一条线段表示。如果镜子是从西南角到东北角斜着放置的，则为\(1\)型镜子；如果是另一条对角线方向，则为\(2\)型镜子。

这些镜子遵循反射定律，即反射角等于入射角。正式地说，对于\(1\)型镜子，如果一束光线从方格的北、南、西或东方向射入，那么它将分别被反射到方格的西、东、北和南方向。类似地，对于\(2\)型镜子，如果一束光线从方格的北、南、西或东方向射入，那么它将分别被反射到方格的东、西、南和北方向。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/5f7b63f0fb5656735a6c59d6b7204c8e210c6d4c.png)你想要在网格外放置一个激光发射器，使得激光束能击中所有的镜子。有\(2\cdot(R + C)\)个可能放置激光发射器的位置：

- 从网格北侧的第\(c\)列（\(1\leq c\leq C\)），向南发射激光束；
- 从网格南侧的第\(c\)列（\(1\leq c\leq C\)），向北发射激光束；
- 从网格东侧的第\(r\)行（\(1\leq r\leq R\)），向西发射激光束；
- 从网格西侧的第\(r\)行（\(1\leq r\leq R\)），向东发射激光束。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/29c68e47c3b155b917aa2d4237fa93819b498fc4.png)确定所有可能放置激光发射器的位置，使得激光束能击中所有的镜子。

## 输入格式

第一行包含两个整数\(R\)和\(C\)（\(1\leq R,C\leq200\)）。

接下来的\(R\)行，每行包含一个长度为\(C\)的字符串\(S_r\)。字符串\(S_r\)的第\(c\)个字符表示方格\((r,c)\)。每个字符可以是“.”（如果方格为空）、“/”（如果方格有\(1\)型镜子）或者“\”（如果方格有\(2\)型镜子）。网格中至少有一面镜子。

## 输出格式

输出一个整数，表示能使激光束击中所有镜子的激光发射器的可能放置位置的数量，记为\(k\)。

如果\(k>0\)，则输出\(k\)个用空格分隔的字符串，表示激光发射器的位置。每个字符串由一个字符和一个紧跟其后的整数组成，中间没有空格。这个字符表示网格的边，如果将激光发射器放在网格的北、南、东或西边，则字符分别为\(N\)、\(S\)、\(E\)或\(W\)。这个整数表示行/列编号。你可以按任意顺序输出这些字符串。

## 说明/提示

样例输入/输出 #1的解释

下面的图示展示了这个样例的一个解决方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/e36d02e4bf94a08c27da9c9fd00e9bc42d7a4647.png)样例输入/输出 #2的解释

下面的图示展示了这个样例的一个解决方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/35fe527ce8ee213e9ba2c6ba34c9f6c589c7585c.png)

## 样例 #1

### 输入

```
4 4
.//.
.\\.
.\/.
....
```

### 输出

```
2
N3 W2
```

## 样例 #2

### 输入

```
4 6
./..\.
.\...\
./../\
......
```

### 输出

```
2
E3 S2
```

## 样例 #3

### 输入

```
4 4
....
./\.
.\/.
....
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
title: "Writing a Song"
layout: "post"
diff: 普及+/提高
pid: CF54D
tag: ['深度优先搜索 DFS', 'KMP 算法']
---

# Writing a Song

## 题目描述

**题目大意**

求一个字符串s，满足该串长度为n，只出现字母表中前k个字母，并且在指定位置必须出现指定字符串p

## 输入格式

第一行 n，k。(n为所需字符串的长度 n<=100，k为相应的字母大小 2<=k<=26)

第二行 p。（一个长度小于n，只包含字母表中前k个字母的字符串）

第三行 01串。（在第i个位置的数字1表示p的出现应该从s的第i个位置开始，而0表示从这里开始没有出现。）

## 输出格式

输出任意一个符合题意的字符串s

若无，输出“No solution”

## 样例 #1

### 输入

```
5 2
aba
101

```

### 输出

```
ababa
```

## 样例 #2

### 输入

```
5 2
a
10001

```

### 输出

```
abbba
```

## 样例 #3

### 输入

```
6 2
abba
101

```

### 输出

```
No solution
```



---

---
title: "Kay and Snowflake"
layout: "post"
diff: 普及+/提高
pid: CF685B
tag: ['枚举', '深度优先搜索 DFS', '位运算']
---

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 2<=n<=300000 $ , $ 1<=q<=300000 $ ) — the size of the initial tree and the number of queries respectively.

The second line contains $ n-1 $ integer $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the indices of the parents of the nodes from $ 2 $ to $ n $ . Node $ 1 $ is a root of the tree. It's guaranteed that $ p_{i} $ define a correct tree.

Each of the following $ q $ lines contain a single integer $ v_{i} $ ( $ 1<=v_{i}<=n $ ) — the index of the node, that define the subtree, for which we want to find a centroid.

## 输出格式

For each query print the index of a centroid of the corresponding subtree. If there are many suitable nodes, print any of them. It's guaranteed, that each subtree has at least one centroid.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5

```

### 输出

```
3
2
3
6

```



---

---
title: "Lizards and Basements 2"
layout: "post"
diff: 普及+/提高
pid: CF6D
tag: ['枚举', '深度优先搜索 DFS', '剪枝']
---

# Lizards and Basements 2

## 题目描述

有一队人，第 $i$ 个人的血量为 $h_{i}$，你可以用火球点某个人，会对当前的人造成 $a$ 点伤害，对旁边的人造成 $b$ 点伤害。

火球不能打 $1$ 号和 $n$ 号，求最少多少发火球烧死所有人。血量为负数才算死。

## 输入格式

第一行输入三个整数 $n$, $a$, $b$；

第二行输入 $n$ 个 $h_{i}$，表示每个人的血量。

## 输出格式

第一行输出 $ t $，表示需要使用的火球总数。

第二行输出 $ t $ 个数，分别表示第 $i$ 个火球打在了哪个人身上。

## 样例 #1

### 输入

```
3 2 1
2 2 2

```

### 输出

```
3
2 2 2 
```

## 样例 #2

### 输入

```
4 3 1
1 4 1 1

```

### 输出

```
4
2 2 3 3 
```



---

