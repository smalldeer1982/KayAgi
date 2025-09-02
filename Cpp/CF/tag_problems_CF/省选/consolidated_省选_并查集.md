---
title: "Network Safety"
layout: "post"
diff: 省选/NOI-
pid: CF1039C
tag: ['并查集', '枚举', '概率论']
---

# Network Safety

## 题目描述

题意：

给你一个有$n$点个和$m$条边的图，第$i$个点的权值为$c_i$。

定义图为安全的条件对于所有的边都保证$c_l≠c_r$

请你求出对于任意的$x$，集合$s$中所有点的点权$xor\quad x$后图仍然安全，这样的$x$和$s$的组合的数量。

答案对于$1e9+7$取模

保证一开始给出的图是安全的。

## 输入格式

第一行一共三个整数$n(n<=500000),m(m<=min(\frac{n*(n-1)}{2},500000)),k(k<=60)$

第二行一共$n$个整数$c_i(c_i<=2^k-1)$

接下来的$m$行每行两个整数$l,r$，表示$l$和$r$之间有边

## 输出格式

一共一个整数，表示答案

## 样例 #1

### 输入

```
4 4 2
0 1 0 1
1 2
2 3
3 4
4 1

```

### 输出

```
50

```

## 样例 #2

### 输入

```
4 5 3
7 1 7 2
1 2
2 3
3 4
4 1
2 4

```

### 输出

```
96

```



---

---
title: "Clearing Up"
layout: "post"
diff: 省选/NOI-
pid: CF141E
tag: ['并查集', '生成树']
---

# Clearing Up

## 题目描述

After Santa Claus and his assistant Elf delivered all the presents and made all the wishes come true, they returned to the North Pole and found out that it is all covered with snow. Both of them were quite tired and they decided only to remove the snow from the roads connecting huts. The North Pole has $ n $ huts connected with $ m $ roads. One can go along the roads in both directions.

The Elf offered to split: Santa Claus will clear up the wide roads and the Elf will tread out the narrow roads. For each road they decided who will clear it: Santa Claus or the Elf. To minimize the efforts they decided to clear the road so as to fulfill both those conditions:

- between any two huts should exist exactly one simple path along the cleared roads;
- Santa Claus and the Elf should clear the same number of roads.

At this point Santa Claus and his assistant Elf wondered which roads should they clear up?

## 输入格式

The first input line contains two positive integers $ n $ and $ m $ ( $ 1<=n<=10^{3} $ , $ 1<=m<=10^{5} $ ) — the number of huts and the number of roads. Then follow $ m $ lines, each of them contains a road description: the numbers of huts it connects — $ x $ and $ y $ ( $ 1<=x,y<=n $ ) and the person responsible for clearing out this road ("S" — for the Elf or "M" for Santa Claus). It is possible to go on each road in both directions. Note that there can be more than one road between two huts and a road can begin and end in the same hut.

## 输出格式

Print "-1" without the quotes if it is impossible to choose the roads that will be cleared by the given rule. Otherwise print in the first line how many roads should be cleared and in the second line print the numbers of those roads (the roads are numbered from $ 1 $ in the order of occurrence in the input). It is allowed to print the numbers of the roads in any order. Each number should be printed exactly once. As you print the numbers, separate them with spaces.

## 说明/提示

A path is called simple if all huts on it are pairwise different.

## 样例 #1

### 输入

```
1 2
1 1 S
1 1 M

```

### 输出

```
0


```

## 样例 #2

### 输入

```
3 3
1 2 S
1 3 M
2 3 S

```

### 输出

```
2
2 1 

```

## 样例 #3

### 输入

```
5 6
1 1 S
1 2 M
1 3 S
1 4 M
1 5 M
2 2 S

```

### 输出

```
-1

```



---

---
title: "Edges in MST"
layout: "post"
diff: 省选/NOI-
pid: CF160D
tag: ['线段树', '并查集', '生成树', '连通块']
---

# Edges in MST

## 题目描述

You are given a connected weighted undirected graph without any loops and multiple edges.

Let us remind you that a graph's spanning tree is defined as an acyclic connected subgraph of the given graph that includes all of the graph's vertexes. The weight of a tree is defined as the sum of weights of the edges that the given tree contains. The minimum spanning tree (MST) of a graph is defined as the graph's spanning tree having the minimum possible weight. For any connected graph obviously exists the minimum spanning tree, but in the general case, a graph's minimum spanning tree is not unique.

Your task is to determine the following for each edge of the given graph: whether it is either included in any MST, or included at least in one MST, or not included in any MST.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=10^{5} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF160D/1841eb9adb257200301ec3daad18abd00c456982.png)) — the number of the graph's vertexes and edges, correspondingly. Then follow $ m $ lines, each of them contains three integers — the description of the graph's edges as " $ a_{i} $ $ b_{i} $ $ w_{i} $ " ( $ 1<=a_{i},b_{i}<=n,1<=w_{i}<=10^{6},a_{i}≠b_{i} $ ), where $ a_{i} $ and $ b_{i} $ are the numbers of vertexes connected by the $ i $ -th edge, $ w_{i} $ is the edge's weight. It is guaranteed that the graph is connected and doesn't contain loops or multiple edges.

## 输出格式

Print $ m $ lines — the answers for all edges. If the $ i $ -th edge is included in any MST, print "any"; if the $ i $ -th edge is included at least in one MST, print "at least one"; if the $ i $ -th edge isn't included in any MST, print "none". Print the answers for the edges in the order in which the edges are specified in the input.

## 说明/提示

In the second sample the MST is unique for the given graph: it contains two first edges.

In the third sample any two edges form the MST for the given graph. That means that each edge is included at least in one MST.

## 样例 #1

### 输入

```
4 5
1 2 101
1 3 100
2 3 2
2 4 2
3 4 1

```

### 输出

```
none
any
at least one
at least one
any

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 2

```

### 输出

```
any
any
none

```

## 样例 #3

### 输入

```
3 3
1 2 1
2 3 1
1 3 1

```

### 输出

```
at least one
at least one
at least one

```



---

---
title: "Sanae and Giant Robot"
layout: "post"
diff: 省选/NOI-
pid: CF1687C
tag: ['并查集', '广度优先搜索 BFS']
---

# Sanae and Giant Robot

## 题目描述

> 果然是那个吗！因为其实用性而无法被实现的！只能出现于憧憬中的，二足步行巨大机器人！——东风谷早苗，《东方非想天则》

早苗制造了一台巨大的机器人——非想天则，但是这个机器人出了一些故障。更糟糕的是，早苗不知道如何将其停止运行，因而早苗只能在机器人运行的时候对其修复。

非想天则的状态可以用一个正整数数列 $n$ 来表示。非想天则现在处于状态 $a_1,a_2,\dots a_n$，而早苗希望将其变为 $b_1,b_2,\dots,b_n$。

作为一位优秀的女子高中生，早苗非常了解复制粘贴的艺术。她有 $m$ 个可供选择的区间，在每一次操作中，早苗可以把序列 $b$ 中的一个可选择的区间对应位置地复制粘贴到序列 $a$ 中，前提是要求序列 $a$ 的每个数字的总和不变。形式化地来讲，早苗可以选择一个区间 $[l,r]$，执行操作 $a_i \leftarrow b_i (l \leq i \leq r)$，当且仅当 $\sum \limits_{i=1}^n a_i$ 不变。

请你判断早苗能否通过若干次这样的操作，将非想天则的状态由序列 $a$ 转化为序列 $b$。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 2 \times 10^4)$，表示输入数据组数。   
对于每组数据，首先输入两个正整数 $n,m(2 \leq n \leq 2 \times 10^5,1 \leq m \leq 10^5)$，分别表示数列 $a,b$ 的长度和可以操作的区间个数。        
第二行输入 $n$ 个正整数 $a_i(1 \leq a_i \leq 10^9)$，表示非想天则的状态。     
第三行输入 $n$ 个正整数 $b_i(1 \leq b_i \leq 10^9)$，表示早苗希望非想天则变成的状态。      
接下来输入 $m$ 行，每行两个正整数 $l,r(1 \leq l < r \leq n)$，表示早苗可以进行操作的区间。     
数据保证，$\sum n,\sum m \leq 2 \times 10^5$。

## 输出格式

如果早苗可以将数列 $a$ 转化为数列 $b$，则输出 `YES`，否则输出 `NO`，不区分大小写。

## 样例 #1

### 输入

```
2
5 2
1 5 4 2 3
3 2 5 4 1
1 3
2 5
5 2
1 5 4 2 3
3 2 4 5 1
1 2
2 4
```

### 输出

```
YES
NO
```



---

---
title: "Smooth Sailing (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1920F2
tag: ['并查集', 'Kruskal 重构树']
---

# Smooth Sailing (Hard Version)

## 题目描述

The only difference between the two versions of this problem is the constraint on $ q $ . You can make hacks only if both versions of the problem are solved.

Thomas is sailing around an island surrounded by the ocean. The ocean and island can be represented by a grid with $ n $ rows and $ m $ columns. The rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The position of a cell at row $ r $ and column $ c $ can be represented as $ (r, c) $ . Below is an example of a valid grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/516df36ca6ac022124866d4043411e04ed0cf48c.png) Example of a valid gridThere are three types of cells: island, ocean and underwater volcano. Cells representing the island are marked with a '\#', cells representing the ocean are marked with a '.', and cells representing an underwater volcano are marked with a 'v'. It is guaranteed that there is at least one island cell and at least one underwater volcano cell. It is also guaranteed that the set of all island cells forms a single connected component $ ^{\dagger} $ and the set of all ocean cells and underwater volcano cells forms a single connected component. Additionally, it is guaranteed that there are no island cells at the edge of the grid (that is, at row $ 1 $ , at row $ n $ , at column $ 1 $ , and at column $ m $ ).

Define a round trip starting from cell $ (x, y) $ as a path Thomas takes which satisfies the following conditions:

- The path starts and ends at $ (x, y) $ .
- If Thomas is at cell $ (i, j) $ , he can go to cells $ (i+1, j) $ , $ (i-1, j) $ , $ (i, j-1) $ , and $ (i, j+1) $ as long as the destination cell is an ocean cell or an underwater volcano cell and is still inside the grid. Note that it is allowed for Thomas to visit the same cell multiple times in the same round trip.
- The path must go around the island and fully encircle it. Some path $ p $ fully encircles the island if it is impossible to go from an island cell to a cell on the grid border by only traveling to adjacent on a side or diagonal cells without visiting a cell on path $ p $ . In the image below, the path starting from $ (2, 2) $ , going to $ (1, 3) $ , and going back to $ (2, 2) $ the other way does not fully encircle the island and is not considered a round trip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/587237f643ee9a450f570eb64a27b00d982a357b.png) Example of a path that does not fully encircle the islandThe safety of a round trip is the minimum Manhattan distance $ ^{\ddagger} $ from a cell on the round trip to an underwater volcano (note that the presence of island cells does not impact this distance).

You have $ q $ queries. A query can be represented as $ (x, y) $ and for every query, you want to find the maximum safety of a round trip starting from $ (x, y) $ . It is guaranteed that $ (x, y) $ is an ocean cell or an underwater volcano cell.

 $ ^{\dagger} $ A set of cells forms a single connected component if from any cell of this set it is possible to reach any other cell of this set by moving only through the cells of this set, each time going to a cell with a common side.

 $ ^{\ddagger} $ Manhattan distance between cells $ (r_1, c_1) $ and $ (r_2, c_2) $ is equal to $ |r_1 - r_2| + |c_1 - c_2| $ .

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 3 \leq n, m \leq 10^5 $ , $ 9 \leq n \cdot m \leq 3 \cdot 10^5 $ , $ 1 \leq q \leq 3 \cdot 10^5 $ ) — the number of rows and columns of the grid and the number of queries.

Each of the following $ n $ lines contains $ m $ characters describing the cells of the grid. The character '\#' denotes an island cell, '.' denotes an ocean cell, and 'v' denotes an underwater volcano cell.

It is guaranteed that there is at least one island cell and at least one underwater volcano cell. It is guaranteed that the set of all island cells forms a single connected component and the set of all ocean cells and underwater volcano cells forms a single connected component. Also, it is guaranteed that there are no island cells at the edge of the grid (that is, at the row $ 1 $ , at the row $ n $ , at the column $ 1 $ , and at the column $ m $ ).

The following $ q $ lines describe the queries. Each of these lines contains two integers $ x $ and $ y $ ( $ 1 \leq x \leq n $ , $ 1 \leq y \leq m $ ) denoting a round trip starting from $ (x, y) $ .

It is guaranteed that $ (x, y) $ is an ocean cell or an underwater volcano cell.

## 输出格式

For each query, output a single integer — the maximum safety of a round trip starting from the specified position.

## 说明/提示

For the first example, the image below shows an optimal round trip starting from $ (1, 1) $ . The round trip has a safety of $ 3 $ as the minimum Manhattan distance from a cell on the round trip to an underwater volcano is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/b0d58ba7a9650556e586a3235109c2b13f201dd2.png) Example of an optimal round tripFor the fourth example, remember that it is allowed for Thomas to visit the same cell multiple times in the same round trip. For example, doing so is necessary for the round trip starting from $ (7, 6) $ .

## 样例 #1

### 输入

```
9 9 3
.........
.........
....###..
...v#....
..###....
...##...v
...##....
.........
v........
1 1
9 1
5 7
```

### 输出

```
3
0
3
```

## 样例 #2

### 输入

```
3 3 5
..v
.#.
...
1 2
1 3
2 3
2 1
3 2
```

### 输出

```
0
0
0
0
0
```

## 样例 #3

### 输入

```
14 13 5
.............
.............
.............
...vvvvvvv...
...v.....v...
...v.###.v...
...v.#.#.v...
...v..v..v...
...v..v..v...
....v...v....
.....vvv.....
.............
.............
.............
1 1
7 7
5 6
4 10
13 6
```

### 输出

```
3
0
1
0
2
```

## 样例 #4

### 输入

```
10 11 4
...........
..#######..
..#..#..#..
..#.....#..
..#..v..#..
..#.###.#..
..#.#.#.#..
..#...#.#..
..#####.#..
...........
7 6
3 7
6 8
1 1
```

### 输出

```
1
2
3
4
```



---

---
title: "Nene and the Passing Game"
layout: "post"
diff: 省选/NOI-
pid: CF1956F
tag: ['图论', '并查集']
---

# Nene and the Passing Game

## 题目描述

Nene is training her team as a basketball coach. Nene's team consists of $ n $ players, numbered from $ 1 $ to $ n $ . The $ i $ -th player has an arm interval $ [l_i,r_i] $ . Two players $ i $ and $ j $ ( $ i \neq j $ ) can pass the ball to each other if and only if $ |i-j|\in[l_i+l_j,r_i+r_j] $ (here, $ |x| $ denotes the absolute value of $ x $ ).

Nene wants to test the cooperation ability of these players. In order to do this, she will hold several rounds of assessment.

- In each round, Nene will select a sequence of players $ p_1,p_2,\ldots,p_m $ such that players $ p_i $ and $ p_{i+1} $ can pass the ball to each other for all $ 1 \le i < m $ . The length of the sequence $ m $ can be chosen by Nene. Each player can appear in the sequence $ p_1,p_2,\ldots,p_m $ multiple times or not appear in it at all.
- Then, Nene will throw a ball to player $ p_1 $ , player $ p_1 $ will pass the ball to player $ p_2 $ and so on... Player $ p_m $ will throw a ball away from the basketball court so it can no longer be used.

As a coach, Nene wants each of $ n $ players to appear in at least one round of assessment. Since Nene has to go on a date after school, Nene wants you to calculate the minimum number of rounds of assessment needed to complete the task.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 2\cdot 10^5 $ ). The description of test cases follows.

The first line contains a single integer $ n $ ( $ 1 \le n \le 2\cdot 10^6 $ ) — the number of players.

The $ i $ -th of the next $ n $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1\leq l_i\leq r_i\leq n $ ) — the arm interval of the $ i $ -th player.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^6 $ .

## 输出格式

For each test case, output one integer — the minimum number of rounds of assessment Nene needs to complete her work.

## 说明/提示

In the first two test cases, Nene can host two rounds of assessment: one with $ p=[1] $ and one with $ p=[2] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

In the third test case, Nene can host two rounds of assessment: one with $ p=[1,3] $ and one with $ p=[2] $ . Player $ 1 $ can pass the ball to player $ 3 $ as $ |3-1|=2 \in [1+1,3+3] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
5
2
1 1
1 1
2
1 1
2 2
3
1 3
1 3
1 3
5
1 1
2 2
1 5
2 2
1 1
6
1 2
5 5
2 3
2 3
2 2
1 2
```

### 输出

```
2
2
2
1
3
```



---

---
title: "Modulo 3"
layout: "post"
diff: 省选/NOI-
pid: CF2104G
tag: ['并查集', '数论', '线段树分治']
---

# Modulo 3

## 题目描述

给定基环内向森林，每个点有且仅有一条出边 $g_i$，可能有自环。

所有点的初始颜色均为 $1$，你可以执行如下操作**任意次**（可以为零次）：

- 选择一个顶点 $u \in [1,n]$，再选择一种颜色 $c \in [1,k]$，将 $u$ 能到达的所有点（包括 $u$ 本身）染成颜色 $c$。

你需要求出，最终能形成的不同的图的数量，**答案对 $3$ 取模**。

两个图不同，当且仅当存在一个编号为 $i$ 的节点，它的颜色在两图中不同。

现在有 $q$ 次修改操作，每次给定 $x,y,k$：

- 将 $g_x$ 修改为 $y$。
- 对于本次输入的 $k$，输出答案，对 $3$ 取模。

对 $g_x$ 的修改操作是永久的，对后面有影响。但是在每次询问答案时，所有顶点的初始颜色都是 $1$。

## 输入格式

第一行包含两个整数 $n$ 和 $q$。

第二行包含 $n$ 个整数 $g_1, g_2, \dots, g_n$。

接下来是 $q$ 行，第 $i$ 行包含三个整数 $x_i$ 、 $y_i$ 和 $k_i$ （$1 \le k_i \le 10^9$ ）。

## 输出格式

共 $q$ 行，每行一个在 $[0,3)$ 的整数。

## 说明/提示

$1 \le n, q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
4 5
2 3 1 4
4 3 1
2 1 2
3 4 3
4 1 5
2 4 4
```

### 输出

```
1
2
0
2
1
```

## 样例 #2

### 输入

```
8 10
7 4 6 8 7 7 1 4
1 7 5
2 3 3
8 6 1
3 1 3
7 2 5
5 2 4
2 7 4
4 6 5
5 2 3
4 5 1
```

### 输出

```
1
0
1
0
2
1
1
2
0
1
```



---

---
title: "Alien DNA"
layout: "post"
diff: 省选/NOI-
pid: CF217E
tag: ['字符串', '并查集', '递归']
---

# Alien DNA

## 题目描述

Professor Bajtocy is conducting experiments on alien DNA. He has discovered that it is subject to repetitive mutations — each mutation happens in the same way: some continuous subsequence of the alien DNA becomes active, copies itself, the copy gets mangled and inserts itself right after the original subsequence. The mangled copy of the activated continuous subsequence is formed by first joining all the elements at the even positions in that subsequence, and then joining all the elements at the odd ones at the end. That is, if the activated subsequence consists of 11 elements and represented as $ s_{1}s_{2}...\ s_{11} $ , its mangled copy is $ s_{2}s_{4}s_{6}s_{8}s_{10}s_{1}s_{3}s_{5}s_{7}s_{9}s_{11} $ .

For example, if the original sequence was "ACTGG" and the mutation happened on the segment $ [2,4] $ (that is the activated subsequence is "CTG"), the mutated DNA is: "ACTGTCGG". The mangled copy of the activated subsequence is marked with bold font.

Professor Bajtocy has written down the original DNA sequence and the mutations that sequentially happened to it, and he now asks you to recover the first $ k $ elements of the DNA sequence after all the mutations.

## 输入格式

The first line of input contains the original DNA sequence, consisting only of letters "A", "C", "T" and "G" and not exceeding $ 3·10^{6} $ in length.

The second line contains a single integer $ k $ ( $ 1<=k<=3·10^{6} $ ).

The third line contains a single integer $ n $ ( $ 0<=n<=5000 $ ) — the number of mutations. The next $ n $ lines describe the mutations in chronological order — each mutation is described by two numbers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=10^{9} $ ), meaning that the continuous subsequence $ [l_{i},r_{i}] $ has become active and cloned itself, joining itself with the mangled copy.

It is guaranteed that the input data is correct, that is, no mutation acts on non-existing elements of the DNA sequence, and the resulting DNA sequence has at least $ k $ elements.

Assume that the DNA elements are indexed starting from 1 and that the notation $ [l,r] $ meaning the continuous subsequence of DNA sequence that consists of $ r-l+1 $ elements starting at the $ l $ -th DNA sequence element and ending at the $ r $ -th DNA sequence element.

## 输出格式

Output a single line, containing the first $ k $ letters of the mutated DNA sequence.

## 说明/提示

In the second example, after the first mutation the sequence is "ACCAGTACGT". After the second mutation it's "ACCAGTACCGACATCGT".

## 样例 #1

### 输入

```
GAGA
4
0

```

### 输出

```
GAGA

```

## 样例 #2

### 输入

```
ACGTACGT
16
2
1 2
2 8

```

### 输出

```
ACCAGTACCGACATCG

```



---

---
title: "Dividing Kingdom II"
layout: "post"
diff: 省选/NOI-
pid: CF687D
tag: ['贪心', '并查集']
---

# Dividing Kingdom II

## 题目描述

Long time ago, there was a great kingdom and it was being ruled by The Great Arya and Pari The Great. These two had some problems about the numbers they like, so they decided to divide the great kingdom between themselves.

The great kingdom consisted of $ n $ cities numbered from $ 1 $ to $ n $ and $ m $ bidirectional roads between these cities, numbered from $ 1 $ to $ m $ . The $ i $ -th road had length equal to $ w_{i} $ . The Great Arya and Pari The Great were discussing about destructing some prefix (all road with numbers less than some $ x $ ) and suffix (all roads with numbers greater than some $ x $ ) of the roads so there will remain only the roads with numbers $ l,l+1,...,r-1 $ and $ r $ .

After that they will divide the great kingdom into two pieces (with each city belonging to exactly one piece) such that the hardness of the division is minimized. The hardness of a division is the maximum length of a road such that its both endpoints are in the same piece of the kingdom. In case there is no such road, the hardness of the division is considered to be equal to $ -1 $ .

Historians found the map of the great kingdom, and they have $ q $ guesses about the $ l $ and $ r $ chosen by those great rulers. Given these data, for each guess $ l_{i} $ and $ r_{i} $ print the minimum possible hardness of the division of the kingdom.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n,q<=1000 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687D/4c89fcb1064dcf8d1c87b4349a7b3c1469f276b5.png)) — the number of cities and roads in the great kingdom, and the number of guesses, respectively.

The $ i $ -th line of the following $ m $ lines contains three integers $ u_{i} $ , $ v_{i} $ and $ w_{i} $ ( $ 1<=u_{i},v_{i}<=n,0<=w_{i}<=10^{9} $ ), denoting the road number $ i $ connects cities $ u_{i} $ and $ v_{i} $ and its length is equal $ w_{i} $ . It's guaranteed that no road connects the city to itself and no pair of cities is connected by more than one road.

Each of the next $ q $ lines contains a pair of integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=m $ ) — a guess from the historians about the remaining roads in the kingdom.

## 输出格式

For each guess print the minimum possible hardness of the division in described scenario.

## 样例 #1

### 输入

```
5 6 5
5 4 86
5 1 0
1 3 38
2 1 33
2 4 28
2 3 40
3 5
2 6
1 3
2 3
1 6

```

### 输出

```
-1
33
-1
-1
33

```



---

---
title: "Royal Questions"
layout: "post"
diff: 省选/NOI-
pid: CF875F
tag: ['贪心', '并查集', '二分图']
---

# Royal Questions

## 题目描述

In a medieval kingdom, the economic crisis is raging. Milk drops fall, Economic indicators are deteriorating every day, money from the treasury disappear. To remedy the situation, King Charles Sunnyface decided make his $ n $ sons-princes marry the brides with as big dowry as possible.

In search of candidates, the king asked neighboring kingdoms, and after a while several delegations arrived with $ m $ unmarried princesses. Receiving guests, Karl learned that the dowry of the $ i $ th princess is $ w_{i} $ of golden coins.

Although the action takes place in the Middle Ages, progressive ideas are widespread in society, according to which no one can force a princess to marry a prince whom she does not like. Therefore, each princess has an opportunity to choose two princes, for each of which she is ready to become a wife. The princes were less fortunate, they will obey the will of their father in the matter of choosing a bride.

Knowing the value of the dowry and the preferences of each princess, Charles wants to play weddings in such a way that the total dowry of the brides of all his sons would be as great as possible. At the same time to marry all the princes or princesses is not necessary. Each prince can marry no more than one princess, and vice versa, each princess can marry no more than one prince.

Help the king to organize the marriage of his sons in the most profitable way for the treasury.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 2<=n<=200000 $ , $ 1<=m<=200000 $ ) — number of princes and princesses respectively.

Each of following $ m $ lines contains three integers $ a_{i} $ , $ b_{i} $ , $ w_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ , $ 1<=w_{i}<=10000 $ ) — number of princes, which $ i $ -th princess is ready to marry and the value of her dowry.

## 输出格式

Print the only integer — the maximum number of gold coins that a king can get by playing the right weddings.

## 样例 #1

### 输入

```
2 3
1 2 5
1 2 1
2 1 10

```

### 输出

```
15
```

## 样例 #2

### 输入

```
3 2
1 2 10
3 2 20

```

### 输出

```
30
```



---

