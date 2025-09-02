---
title: "Sergey and Subway"
layout: "post"
diff: 提高+/省选-
pid: CF1060E
tag: ['分治', '深度优先搜索 DFS', '概率论']
---

# Sergey and Subway

## 题目描述

Sergey Semyonovich is a mayor of a county city N and he used to spend his days and nights in thoughts of further improvements of Nkers' lives. Unfortunately for him, anything and everything has been done already, and there are no more possible improvements he can think of during the day (he now prefers to sleep at night). However, his assistants have found a solution and they now draw an imaginary city on a paper sheet and suggest the mayor can propose its improvements.

Right now he has a map of some imaginary city with $ n $ subway stations. Some stations are directly connected with tunnels in such a way that the whole map is a tree (assistants were short on time and enthusiasm). It means that there exists exactly one simple path between each pair of station. We call a path simple if it uses each tunnel no more than once.

One of Sergey Semyonovich's favorite quality objectives is the sum of all pairwise distances between every pair of stations. The distance between two stations is the minimum possible number of tunnels on a path between them.

Sergey Semyonovich decided to add new tunnels to the subway map. In particular, he connected any two stations $ u $ and $ v $ that were not connected with a direct tunnel but share a common neighbor, i.e. there exists such a station $ w $ that the original map has a tunnel between $ u $ and $ w $ and a tunnel between $ w $ and $ v $ . You are given a task to compute the sum of pairwise distances between all pairs of stations in the new map.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2 \leq n \leq 200\,000 $ ) — the number of subway stations in the imaginary city drawn by mayor's assistants. Each of the following $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \ne v_i $ ), meaning the station with these indices are connected with a direct tunnel.

It is guaranteed that these $ n $ stations and $ n - 1 $ tunnels form a tree.

## 输出格式

Print one integer that is equal to the sum of distances between all pairs of stations after Sergey Semyonovich draws new tunnels between all pairs of stations that share a common neighbor in the original map.

## 说明/提示

In the first sample, in the new map all pairs of stations share a direct connection, so the sum of distances is $ 6 $ .

In the second sample, the new map has a direct tunnel between all pairs of stations except for the pair $ (1, 4) $ . For these two stations the distance is $ 2 $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4

```

### 输出

```
7

```



---

---
title: "Robot on the Board 2"
layout: "post"
diff: 提高+/省选-
pid: CF1607F
tag: ['深度优先搜索 DFS']
---

# Robot on the Board 2

## 题目描述

The robot is located on a checkered rectangular board of size $ n \times m $ ( $ n $ rows, $ m $ columns). The rows in the board are numbered from $ 1 $ to $ n $ from top to bottom, and the columns — from $ 1 $ to $ m $ from left to right.

The robot is able to move from the current cell to one of the four cells adjacent by side.

Each cell has one of the symbols 'L', 'R', 'D' or 'U' written on it, indicating the direction in which the robot will move when it gets in that cell — left, right, down or up, respectively.

The robot can start its movement in any cell. He then moves to the adjacent square in the direction indicated on the current square in one move.

- If the robot moves beyond the edge of the board, it falls and breaks.
- If the robot appears in the cell it already visited before, it breaks (it stops and doesn't move anymore).

Robot can choose any cell as the starting cell. Its goal is to make the maximum number of steps before it breaks or stops.

Determine from which square the robot should start its movement in order to execute as many commands as possible. A command is considered successfully completed if the robot has moved from the square on which that command was written (it does not matter whether to another square or beyond the edge of the board).

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10000 $ ) — the number of test cases in the test.

Each test case's description is preceded by a blank line. Next is a line that contains integers $ n $ and $ m $ ( $ 1 \le n \le 2000 $ ; $ 1 \le m \le 2000 $ ) — the height and width of the board. This line followed by $ n $ lines, the $ i $ -th of which describes the $ i $ -th line of the board. Each of them is exactly $ m $ letters long and consists of symbols 'L', 'R', 'D' and 'U'.

It is guaranteed that the sum of sizes of all boards in the input does not exceed $ 4\cdot10^6 $ .

## 输出格式

For each test case, output three integers $ r $ , $ c $ and $ d $ ( $ 1 \le r \le n $ ; $ 1 \le c \le m $ ; $ d \ge 0 $ ), which denote that the robot should start moving from cell $ (r, c) $ to make the maximum number of moves $ d $ . If there are several answers, output any of them.

## 样例 #1

### 输入

```
7

1 1
R

1 3
RRL

2 2
DL
RU

2 2
UD
RU

3 2
DL
UL
RU

4 4
RRRD
RUUD
URUD
ULLR

4 4
DDLU
RDDU
UUUU
RDLD
```

### 输出

```
1 1 1
1 1 3
1 1 4
2 1 3
3 1 5
4 3 12
1 1 4
```



---

---
title: "Happy Life in University"
layout: "post"
diff: 提高+/省选-
pid: CF1916E
tag: ['线段树', '深度优先搜索 DFS']
---

# Happy Life in University

## 题目描述

Egor and his friend Arseniy are finishing school this year and will soon enter university. And since they are very responsible guys, they have started preparing for admission already.

First of all, they decided to take care of where they will live for the long four years of study, and after visiting the university's website, they found out that the university dormitory can be represented as a root tree with $ n $ vertices with the root at vertex $ 1 $ . In the tree, each vertex represents a recreation with some type of activity $ a_i $ . The friends need to choose $ 2 $ recreations (not necessarily different) in which they will settle. The guys are convinced that the more the value of the following function $ f(u, v) = diff(u, lca(u, v)) \cdot diff(v, lca(u, v)) $ , the more fun their life will be. Help Egor and Arseniy and find the maximum value of $ f(u, v) $ among all pairs of recreations!

 $ ^{\dagger} diff(u, v) $ — the number of different activities listed on the simple path from vertex $ u $ to vertex $ v $ .

 $ ^{\dagger} lca(u, v) $ — a vertex $ p $ such that it is at the maximum distance from the root and is a parent of both vertex $ u $ and vertex $ v $ .

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^{5} $ ).

The second line of each test case contains $ {n - 1} $ integers $ p_2, p_3, \ldots,p_n $ ( $ 1 \le p_i \le i - 1 $ ), where $ p_i $ — the parent of vertex $ i $ .

The third line of each test case contains $ {n} $ integers $ a_1, a_2, \ldots,a_n $ ( $ 1 \le a_i \le n $ ), where $ a_i $ — the number of the activity located at vertex $ i $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of $ f(u, v) $ for all pairs of recreations $ (u, v) $ .

## 说明/提示

Consider the fourth test case. The tree has the following structure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1916E/310c7cd8a93a46df2248a6a8b87aa515f4626d82.png)  All recreations are colored. The same colors mean that the activities in the recreations match. Consider the pair of vertices $ (11, 12) $ , $ lca(11, 12) = 1 $ . Write down all activities on the path from $ 11 $ to $ 1 $ — $ [11, 5, 1, 11] $ , among them there are $ 3 $ different activities, so $ diff(11, 1) = 3 $ . Also write down all activities on the path from $ 12 $ to $ 1 $ — $ [7, 8, 2, 11] $ , among them there are $ 4 $ different activities, so $ diff(12, 1) = 4 $ . We get that $ f(11, 12) = diff(12, 1) \cdot diff(11, 1) = 4 \cdot 3 = 12 $ , which is the answer for this tree. It can be shown that a better answer is impossible to obtain.

## 样例 #1

### 输入

```
4
2
1
1 2
7
1 1 2 2 3 3
6 5 2 3 6 5 6
13
1 1 1 2 2 2 3 3 4 5 6 6
2 2 2 1 4 9 7 2 5 2 1 11 2
12
1 1 1 2 2 3 4 4 7 7 6
11 2 1 11 12 8 5 8 8 5 11 7
```

### 输出

```
2
9
9
12
```



---

---
title: "Maximize the Largest Component (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1985H2
tag: ['深度优先搜索 DFS', '差分']
---

# Maximize the Largest Component (Hard Version)

## 题目描述

简单版本和困难版本实际上是不同的问题，因此请完整仔细地阅读两个问题的陈述。两个版本之间的唯一区别是操作。
Alex有一个由 $ n $ 行和 $ m $ 列组成的网格，由“.”和“#”字符组成。如果从该组中的任何单元格开始，通过仅移动到该组中共享一个共同边的另一个单元格，就可以到达该组中的任何其他单元格，则一组“#”单元格形成一个连通分量。连通分量的尺寸是该组中的单元格数量。
在一次操作中，Alex选择任意行$ r $（$ 1 \le r \le n $）和任意列$ c $（$ 1 \le c \le m $），然后将行$ r $和列$ c $中的每个单元格设置为“＃”。帮助Alex找到他在最多执行一次操作后，可以实现的“＃”个单元格的最大连通分量的最大可能大小。

## 输入格式

输入的第一行包含一个整数 $ t $（$ 1 \leq t \leq 10^4 $）——测试用例的数量。
每个测试用例的第一行包含两个整数$n$和$m$（$1 \le n \cdot m \le 10^6$）——网格的行数和列数。
接下来的 $n$ 行每行包含 $m$ 个字符。每个字符要么是 '.'或
保证所有测试用例中的 $ n \cdot m $ 的总和不超过 $ 10^6 $。

## 输出格式

对于每个测试用例，输出一个整数——Alex可以实现的“#”单元的连通分量的最大可能大小。

## 说明/提示

在第四个测试用例中，Alex将第4行和第2列的所有单元格设置为“#”是最优的。这样做将导致“#”的最大连通分量大小为16。
在第五个测试用例中，Alex将第2行和第4列的所有单元格设置为“#”是最优的。这样做将导致“#”的最大连通分量大小为22。

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
7
11
16
22
36
```



---

---
title: "Propagating tree"
layout: "post"
diff: 提高+/省选-
pid: CF383C
tag: ['模拟', '线段树', '深度优先搜索 DFS']
---

# Propagating tree

## 题目描述

很久以前，有一棵神橡树(oak)，上面有$n$个节点，从$1$~$n$编号，由$n-1$条边相连。它的根是$1$号节点。  

这棵橡树每个点都有一个权值，你需要完成这两种操作：
$1$ $u$ $val$ 表示给$u$节点的权值增加$val$  
$2$ $u$ 表示查询$u$节点的权值   

但是这不是普通的橡树，它是神橡树。  
所以它还有个神奇的性质：当某个节点的权值增加$val$时，它的子节点权值都增加$-val$，它子节点的子节点权值增加$-(-val)$...... 如此一直进行到树的底部。

## 输入格式

第一行两个正整数$n,m$，表示节点数量和操作数量。  
第二行$n$个正整数$a_i$，依次表示每个节点的权值。     
接下来$n-1$行，每行两个正整数$u,v$，表示$u,v$之间有一条边相连。  
最后$m$行，每行若干个正整数，表示一次操作。

## 输出格式

对于每次询问，输出一行一个整数表示答案。

## 说明/提示

$1\le n,m \le 2\times 10^5$  
$1\le a_i,val \le 1000$  
$1\le u,v \le n$

## 样例 #1

### 输入

```
5 5
1 2 1 1 2
1 2
1 3
2 4
2 5
1 2 3
1 1 2
2 1
2 2
2 4

```

### 输出

```
3
3
0

```



---

---
title: "Progress Monitoring"
layout: "post"
diff: 提高+/省选-
pid: CF509F
tag: ['动态规划 DP', '深度优先搜索 DFS']
---

# Progress Monitoring

## 题目描述

### 题面翻译

编程老师$Dmitry Olegovich$（以下简称小$D$）准备在一次考试中出以下题目：
**以邻接矩阵的方式给定一颗树，求下面这段伪代码的输出结果**。

```
used[1 ... n] = {0, ..., 0};

procedure dfs(v):
    print v;
    used[v] = 1;
    for i = 1, 2, ..., n:
        if (a[v][i] == 1 and used[i] == 0):
            dfs(i);

dfs(1);
```

为了简化测试结果的检查过程 ~~（其实就是懒）~~ ，小 $D$ 决定创建一棵树 $T$ ，使得结果是他最喜欢的序列 $b$ 。不过，小 $D$ 不想为学生用相同的树作为输入（这意味着他们可能会作弊）。**所以小 $D$ 试图找出不同的树 $T$ 的数量，以便以 $T$ 作为输入运行上述伪代码的结果恰好是序列 $b$ ，答案对$10 ^9+7$取模**。

（两棵树“不同”的定义：它们的邻接矩阵不相同）

### 题面简述

见题面翻译中加粗部分。

## 输入格式

第一行一个整数 $n$，代表题目中序列 $b$ 的长度。

第二行 $n$ 个整数，表示序列 $b$（题目确保这是一个$1 \sim n$的排列，而且 $b_1=1$）。

## 输出格式

一行一个整数表示答案，意思如题面所述。

## 说明/提示

$1\le n \le 500$

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
1 3 2

```

### 输出

```
1

```



---

---
title: "Alyona and a tree"
layout: "post"
diff: 提高+/省选-
pid: CF739B
tag: ['深度优先搜索 DFS', '前缀和', '差分']
---

# Alyona and a tree

## 题目描述

Alyona有一棵有 $n$ 个节点的树。这棵树的根节点是 $1$。在每个节点里，Alyona写了一个正整数，在节点 $i$ 她写了正整数 $a_i$ 。另外，她在这棵树上的每条边上写了一个正整数（不同边上可能有不同的数）。

让我们定义 $dist(v,u)$ 作为从 $v$ 到 $u$ 的简单路径上的边权和。

当且仅当 $u$ 在 $v$ 的子树中并且 $dist(v,u)\leq a_u$，顶点 $v$ 控制顶点 $u(v\neq u)$ 。

Alyona想在某些顶点定居。为了做到这件事，她想知道在每个节点 $v$ 能控制几个节点。

## 输入格式

第一行包含一个整数 $n (1\leq n\leq 2\times 10^5)$

第二行有 $n$ 个整数 $a_1,a_2,\ldots,a_n(1\leq a_i\leq 10^9)$ ,作为节点 $i$ 的数。

下面的 $n-1$ 行，每行有两个整数。第 $i$ 行包含整数 $p_i,w_i(1\leq p_i\leq n,1\leq w_i\leq 10^9)$ ,分别为节点 $i+1$ 的在树上的父节点和 $p_i$ 和 $(i+1)$ 的边上的数字。

数据保证是个树。

## 输出格式

输出 $n$ 个整数，第 $i$ 个数为节点 $i$ 能控制的点数。

## 说明/提示

在样例中，节点 $1$ 控制了节点 $3$ ，节点 $3$ 控制节点 $5$ （注意，这并不代表节点 $1$ 控制了节点 $5$ ）

Translated by @lolte

## 样例 #1

### 输入

```
5
2 5 1 4 6
1 7
1 1
3 5
3 6

```

### 输出

```
1 0 1 0 0

```

## 样例 #2

### 输入

```
5
9 7 8 6 5
1 1
2 1
3 1
4 1

```

### 输出

```
4 3 2 1 0

```



---

---
title: "Reachability from the Capital"
layout: "post"
diff: 提高+/省选-
pid: CF999E
tag: ['深度优先搜索 DFS', '强连通分量', '概率论']
---

# Reachability from the Capital

## 题目描述

在 Berland 有 $n$ 座城市和 $m$ 条道路，每条道路连接着一对城市。

Berland 的道路都是**单向**的

为了能让首都能够到达所有的城市，最少需要新修建多少新道路？

新道路也是单向的

## 输入格式

输入的第一行包含三个整数 $n,m$ 和 $s$ $(1\le n \le 5000,0\le m \le 5000 , 1\le s \le n)$ ——城市数，道路数和首都所在城市的标号。 城市的标号为 $1$ \~ $n$
接下来 $m$ 行每行包含一条道路连接着一对城市 $u_i,v_i$ $(1\le u_i,v_i\le n,u_i\ne v_i)$

 对于每对城市 $u,v$，从 $u$ 到 $v$ 最多只能有一条道路。 允许在一对城市之间建造相反方向的道路（即从 $u$ 到 $v$ 和从 $v$ 到 $u$ ）。

## 输出格式

输出一个整数——使从首都可以到达所有城市所需的最少新修建道路数。如果从 $s$ 已经可以到达所有城市，则输出 $0$。

## 说明/提示

样例 1：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/cfa72c5c5f72e8ccb5babda1e509efae921c1e73.png)

例如，您可以添加道路 ( 6, 4 ) , ( 7 , 9 ) , ( 1 , 7 )，以使从 $s = 1$ 可到达所有城市。
样例 2：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/62d78c6df2be4fcc0d6c17ba856e4ad627c47d5f.png)

在此样例中，您可以添加道路（5 , 1），（5 , 2），（5 , 3），（5 , 4）中的任何一条，以使可从 $s = 5$ 到达所有城市。

## 样例 #1

### 输入

```
9 9 1
1 2
1 3
2 3
1 5
5 6
6 1
1 8
9 8
7 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 4 5
1 2
2 3
3 4
4 1

```

### 输出

```
1

```



---

