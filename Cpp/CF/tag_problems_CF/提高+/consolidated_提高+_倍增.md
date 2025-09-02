---
title: "Minimal Segment Cover"
layout: "post"
diff: 提高+/省选-
pid: CF1175E
tag: ['倍增']
---

# Minimal Segment Cover

## 题目描述

You are given $ n $ intervals in form $ [l; r] $ on a number line.

You are also given $ m $ queries in form $ [x; y] $ . What is the minimal number of intervals you have to take so that every point (not necessarily integer) from $ x $ to $ y $ is covered by at least one of them?

If you can't choose intervals so that every point from $ x $ to $ y $ is covered, then print -1 for that query.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ) — the number of intervals and the number of queries, respectively.

Each of the next $ n $ lines contains two integer numbers $ l_i $ and $ r_i $ ( $ 0 \le l_i < r_i \le 5 \cdot 10^5 $ ) — the given intervals.

Each of the next $ m $ lines contains two integer numbers $ x_i $ and $ y_i $ ( $ 0 \le x_i < y_i \le 5 \cdot 10^5 $ ) — the queries.

## 输出格式

Print $ m $ integer numbers. The $ i $ -th number should be the answer to the $ i $ -th query: either the minimal number of intervals you have to take so that every point (not necessarily integer) from $ x_i $ to $ y_i $ is covered by at least one of them or -1 if you can't choose intervals so that every point from $ x_i $ to $ y_i $ is covered.

## 说明/提示

In the first example there are three queries:

1. query $ [1; 3] $ can be covered by interval $ [1; 3] $ ;
2. query $ [1; 4] $ can be covered by intervals $ [1; 3] $ and $ [2; 4] $ . There is no way to cover $ [1; 4] $ by a single interval;
3. query $ [3; 4] $ can be covered by interval $ [2; 4] $ . It doesn't matter that the other points are covered besides the given query.

In the second example there are four queries:

1. query $ [1; 2] $ can be covered by interval $ [1; 3] $ . Note that you can choose any of the two given intervals $ [1; 3] $ ;
2. query $ [1; 3] $ can be covered by interval $ [1; 3] $ ;
3. query $ [1; 4] $ can't be covered by any set of intervals;
4. query $ [1; 5] $ can't be covered by any set of intervals. Note that intervals $ [1; 3] $ and $ [4; 5] $ together don't cover $ [1; 5] $ because even non-integer points should be covered. Here $ 3.5 $ , for example, isn't covered.

## 样例 #1

### 输入

```
2 3
1 3
2 4
1 3
1 4
3 4

```

### 输出

```
1
2
1

```

## 样例 #2

### 输入

```
3 4
1 3
1 3
4 5
1 2
1 3
1 4
1 5

```

### 输出

```
1
1
-1
-1

```



---

---
title: "Yunli's Subarray Queries (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF2009G2
tag: ['线段树', '倍增']
---

# Yunli's Subarray Queries (hard version)

## 题目描述

这是问题的困难版本。在此版本中，保证所有查询的 $r\geq l+k-1$。

对于任意数组 $b$，Yunli 可以执行以下操作任意次数：

- 选择一个索引 $i$。设置 $b_i=x$，其中 $x$ 是她想要的任何整数（$x$ 不限于区间 $[1,n]$）。

将 $f(b)$ 表示为她需要执行的最小操作数，直到 $b$ 中存在长度至少为 $k$ 的连续子数组$^{\text{*}}$。

Yunli 收到一个大小为 $n$ 的数组 $a$，并询问 $q$ 次。在每次查询中，你需要计算 $\sum_{j=l+k-1}^{r}f([a_l,a_{l+1},\ldots,a_j])$。

$^{\text{*}}$ 如果存在一个长度为 $k$ 的连续子数组，从索引 $i$ 开始（$1\leq i\leq |b|-k+1$），那么对于所有 $i<j\leq i+k-1$，$b_j=b_{j-1}+1$。

## 输入格式

第一行包含 $t$（$1\leq t\leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含三个整数 $n$、$k$ 和 $q$（$1\leq k\leq n\leq 2\cdot 10^5$，$1\leq 2 \cdot 10^ 5$）——数组的长度、连续子数组的长度和查询次数。

下一行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$（$1\leq a_i\leq n$）。

以下 $q$ 行包含两个整数 $l$ 和 $r$（$1\leq l\leq r\leq n$，$r\geq l+k-1$）——查询的边界。

保证所有测试用例中 $n$ 的总和不超过 $2\cdot 10^5$，所有测试用例的 $q$ 总和不超过 $2\cdot 10^5$。

## 输出格式

对于每组测试数据上的每次查询，输出 $\sum_{j=l+k-1}^{r}f([a_l,a_{l+1},\ldots,a_j])$。

## 说明/提示

在第一组测试用例的第二次查询中，我们计算了以下函数值：

- $f([2,3,2,1,2])=3$，因为 Yunli 可以设置 $b_3=4$、$b_4=5$ 和 $b_5=6$，从而在 $3$ 次操作中形成一个大小为 $5$ 的连续子阵列。
- $f([2,3,2,1,2,3])=2$，因为我们可以设置 $b_3=0$ 和 $b_2=-1$，在 $2$ 次操作中中（从位置 $2$ 开始）形成一个大小为$5$的连续子阵列。

这个查询的答案是 $3+2=5$。

翻译 @Cure_Wing。

## 样例 #1

### 输入

```
3
7 5 3
1 2 3 2 1 2 3
1 7
2 7
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
1 5
5 4 2
4 5 1 2 3
1 4
1 5
```

### 输出

```
6
5
2
2
5
2
3
```



---

---
title: "Sakurako and Chefir"
layout: "post"
diff: 提高+/省选-
pid: CF2033G
tag: ['动态规划 DP', '倍增']
---

# Sakurako and Chefir

## 题目描述

Given a tree with $ n $ vertices rooted at vertex $ 1 $ . While walking through it with her cat Chefir, Sakurako got distracted, and Chefir ran away.

To help Sakurako, Kosuke recorded his $ q $ guesses. In the $ i $ -th guess, he assumes that Chefir got lost at vertex $ v_i $ and had $ k_i $ stamina.

Also, for each guess, Kosuke assumes that Chefir could move along the edges an arbitrary number of times:

- from vertex $ a $ to vertex $ b $ , if $ a $ is an ancestor $ ^{\text{∗}} $ of $ b $ , the stamina will not change;
- from vertex $ a $ to vertex $ b $ , if $ a $ is not an ancestor of $ b $ , then Chefir's stamina decreases by $ 1 $ .

If Chefir's stamina is $ 0 $ , he cannot make a move of the second type.

For each assumption, your task is to find the distance to the farthest vertex that Chefir could reach from vertex $ v_i $ , having $ k_i $ stamina.

 $ ^{\text{∗}} $ Vertex $ a $ is an ancestor of vertex $ b $ if the shortest path from $ b $ to the root passes through $ a $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described as follows:

- The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.
- The next $ n-1 $ lines contain the edges of the tree. It is guaranteed that the given edges form a tree.
- The next line consists of a single integer $ q $ $ (1\le q\le 2 \cdot 10^5) $ , which denotes the number of guesses made by Kosuke.
- The next $ q $ lines describe the guesses made by Kosuke, with two integers $ v_i $ , $ k_i $ $ (1\le v_i \le n, 0 \le k_i\le n) $ .

It is guaranteed that the sum of $ n $ and the sum of $ q $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case and for each guess, output the maximum distance to the farthest vertex that Chefir could reach from the starting point $ v_i $ having $ k_i $ stamina.

## 说明/提示

In the first example:

- In the first query, you can go from vertex $ 5 $ to vertex $ 3 $ (after which your stamina will decrease by $ 1 $ and become $ 0 $ ), and then you can go to vertex $ 4 $ ;
- In the second query, from vertex $ 3 $ with $ 1 $ stamina, you can only reach vertices $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ ;
- In the third query, from vertex $ 2 $ with $ 0 $ stamina, you can only reach vertices $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ ;

## 样例 #1

### 输入

```
3
5
1 2
2 3
3 4
3 5
3
5 1
3 1
2 0
9
8 1
1 7
1 4
7 3
4 9
3 2
1 5
3 6
7
6 0
2 3
6 2
8 2
2 4
9 2
6 3
6
2 1
2 5
2 4
5 6
4 3
3
3 1
1 3
6 5
```

### 输出

```
2 1 2 
0 5 2 4 5 5 5 
1 3 4
```



---

---
title: "Maze 2D"
layout: "post"
diff: 提高+/省选-
pid: CF413E
tag: ['线段树', '倍增']
---

# Maze 2D

## 题目描述

The last product of the R2 company in the 2D games' field is a new revolutionary algorithm of searching for the shortest path in a $ 2×n $ maze.

Imagine a maze that looks like a $ 2×n $ rectangle, divided into unit squares. Each unit square is either an empty cell or an obstacle. In one unit of time, a person can move from an empty cell of the maze to any side-adjacent empty cell. The shortest path problem is formulated as follows. Given two free maze cells, you need to determine the minimum time required to go from one cell to the other.

Unfortunately, the developed algorithm works well for only one request for finding the shortest path, in practice such requests occur quite often. You, as the chief R2 programmer, are commissioned to optimize the algorithm to find the shortest path. Write a program that will effectively respond to multiple requests to find the shortest path in a $ 2×n $ maze.

## 输入格式

The first line contains two integers, $ n $ and $ m $ $ (1<=n<=2·10^{5}; 1<=m<=2·10^{5}) $ — the width of the maze and the number of queries, correspondingly. Next two lines contain the maze. Each line contains $ n $ characters, each character equals either '.' (empty cell), or 'X' (obstacle).

Each of the next $ m $ lines contains two integers $ v_{i} $ and $ u_{i} $ $ (1<=v_{i},u_{i}<=2n) $ — the description of the $ i $ -th request. Numbers $ v_{i} $ , $ u_{i} $ mean that you need to print the value of the shortest path from the cell of the maze number $ v_{i} $ to the cell number $ u_{i} $ . We assume that the cells of the first line of the maze are numbered from $ 1 $ to $ n $ , from left to right, and the cells of the second line are numbered from $ n+1 $ to $ 2n $ from left to right. It is guaranteed that both given cells are empty.

## 输出格式

Print $ m $ lines. In the $ i $ -th line print the answer to the $ i $ -th request — either the size of the shortest path or -1, if we can't reach the second cell from the first one.

## 样例 #1

### 输入

```
4 7
.X..
...X
5 1
1 3
7 7
1 4
6 1
4 7
5 7

```

### 输出

```
1
4
0
5
2
2
2

```

## 样例 #2

### 输入

```
10 3
X...X..X..
..X...X..X
11 7
7 18
18 10

```

### 输出

```
9
-1
3

```



---

---
title: "A and B and Lecture Rooms"
layout: "post"
diff: 提高+/省选-
pid: CF519E
tag: ['倍增', '最近公共祖先 LCA']
---

# A and B and Lecture Rooms

## 题目描述

A和B在准备参加编程比赛。

A和B学习的大学的房间由走廊连接。大学一共有$n$ 个房间，由$n-1$ 条走廊连接，房间的编号是从$1$ 到$n$ 的数字编号。

A和B在大学的某些房间里进行比赛。在每场比赛之后，他们会一起在一个房间里讨论问题。A和B希望这个讨论问题的房间到分别他们两个人比赛房间的距离相等。两个房间之间的距离指他们之间最短路的边数。

因为A和B每天都在不一样的房间里比赛，所以他们请求你告诉他们在接下来比赛的$m$ 天里可以用来讨论问题的房间有多少个？

## 输入格式

第一行包括整数$n$ ，其中$(1<=n<=10^5)$ ，表示房间数量。

接下来的$n-1$ 行描述所有的走廊。这$n-1$ 行中的第$i$ 行包括两个整数$a_i$ 和$b_i$ ，表示第$i$ 条走廊连接了房间$a_i$ 和$b_i$ 。

接下来的一行输入比赛的天数$m(1<=m<=10^5)$ 。

再接下来的$m$ 行，第$j$ 行包含两个整数$x_j$ 和$y_j(1<=x_j,y_j<=n)$ ，表示比赛的第$j$ 天A将在$x_j$ 房间比赛，B将在$y_j$ 房间比赛。

## 输出格式

在第$i(1<=i<=m)$ 行输出当天分别到A、B比赛的房间距离相等的房间数量。

感谢@lonelysir 提供的翻译

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4
1 2
2 3
2 4
2
1 2
1 3

```

### 输出

```
0
2

```



---

---
title: "Analysis of Pathes in Functional Graph"
layout: "post"
diff: 提高+/省选-
pid: CF702E
tag: ['倍增']
---

# Analysis of Pathes in Functional Graph

## 题目描述

有一个 $n$ 个点 $n$ 条边的带权有向图（点编号 $0\sim n-1$），每个点有且仅有一条出边，对于每个点 $i$ 求出由 $i$ 出发走过 $k$ 条边，这 $k$ 条边权值的最小值与这 $k$ 条边权值之和。

## 输入格式

第一行两个正整数 $n$ 和 $k$。

第二行 $n$ 个正整数，第 $i$ 个数表示点 $i$ 的出边指向的点。

第三行 $n$ 个正整数，第 $i$ 个数表示点 $i$ 的出边的权值。

## 输出格式

共 $n$ 行，每行两个数，第一个数表示由点 $i$ 出发经过 $k$ 条边，这 $k$ 条边的权值和，第二个数表示最小值。

## 样例 #1

### 输入

```
7 3
1 2 3 4 3 2 6
6 3 1 4 2 2 3

```

### 输出

```
10 1
8 1
7 1
10 2
8 2
7 1
9 3

```

## 样例 #2

### 输入

```
4 4
0 1 2 3
0 1 2 3

```

### 输出

```
0 0
4 1
8 2
12 3

```

## 样例 #3

### 输入

```
5 3
1 2 3 4 0
4 1 2 14 3

```

### 输出

```
7 1
17 1
19 2
21 3
8 1

```



---

