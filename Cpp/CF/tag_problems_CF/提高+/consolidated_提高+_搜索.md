---
title: "Xor-Paths"
layout: "post"
diff: 提高+/省选-
pid: CF1006F
tag: ['搜索', '概率论']
---

# Xor-Paths

## 题目描述

There is a rectangular grid of size $ n \times m $ . Each cell has a number written on it; the number on the cell ( $ i, j $ ) is $ a_{i, j} $ . Your task is to calculate the number of paths from the upper-left cell ( $ 1, 1 $ ) to the bottom-right cell ( $ n, m $ ) meeting the following constraints:

- You can move to the right or to the bottom only. Formally, from the cell ( $ i, j $ ) you may move to the cell ( $ i, j + 1 $ ) or to the cell ( $ i + 1, j $ ). The target cell can't be outside of the grid.
- The xor of all the numbers on the path from the cell ( $ 1, 1 $ ) to the cell ( $ n, m $ ) must be equal to $ k $ (xor operation is the bitwise exclusive OR, it is represented as '^' in Java or C++ and "xor" in Pascal).

Find the number of such paths in the given grid.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n, m \le 20 $ , $ 0 \le k \le 10^{18} $ ) — the height and the width of the grid, and the number $ k $ .

The next $ n $ lines contain $ m $ integers each, the $ j $ -th element in the $ i $ -th line is $ a_{i, j} $ ( $ 0 \le a_{i, j} \le 10^{18} $ ).

## 输出格式

Print one integer — the number of paths from ( $ 1, 1 $ ) to ( $ n, m $ ) with xor sum equal to $ k $ .

## 说明/提示

All the paths from the first example:

- $ (1, 1) \rightarrow (2, 1) \rightarrow (3, 1) \rightarrow (3, 2) \rightarrow (3, 3) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (3, 3) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) \rightarrow (3, 2) \rightarrow (3, 3) $ .

All the paths from the second example:

- $ (1, 1) \rightarrow (2, 1) \rightarrow (3, 1) \rightarrow (3, 2) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (3, 2) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (2, 4) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (1, 3) \rightarrow (2, 3) \rightarrow (3, 3) \rightarrow (3, 4) $ .

## 样例 #1

### 输入

```
3 3 11
2 1 5
7 10 0
12 6 4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 4 2
1 3 3 3
0 3 3 2
3 0 1 1

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 4 1000000000000000000
1 3 3 3
0 3 3 2
3 0 1 1

```

### 输出

```
0

```



---

---
title: "Classy Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF1036C
tag: ['搜索', '记忆化搜索', '数位 DP']
---

# Classy Numbers

## 题目描述

Let's call some positive integer classy if its decimal representation contains no more than $ 3 $ non-zero digits. For example, numbers $ 4 $ , $ 200000 $ , $ 10203 $ are classy and numbers $ 4231 $ , $ 102306 $ , $ 7277420000 $ are not.

You are given a segment $ [L; R] $ . Count the number of classy integers $ x $ such that $ L \le x \le R $ .

Each testcase contains several segments, for each of them you are required to solve the problem separately.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 10^4 $ ) — the number of segments in a testcase.

Each of the next $ T $ lines contains two integers $ L_i $ and $ R_i $ ( $ 1 \le L_i \le R_i \le 10^{18} $ ).

## 输出格式

Print $ T $ lines — the $ i $ -th line should contain the number of classy integers on a segment $ [L_i; R_i] $ .

## 样例 #1

### 输入

```
4
1 1000
1024 1024
65536 65536
999999 1000001

```

### 输出

```
1000
1
0
2

```



---

---
title: "Trips"
layout: "post"
diff: 提高+/省选-
pid: CF1037E
tag: ['搜索', '队列']
---

# Trips

## 题目描述

**题目大意：**

一共有$n$个人，他们开始互不认识，而每天早上不认识的两个人会变成朋友。一共有$m$天，每天晚上有的人要去旅行，去旅行的人必须满足ta有至少$k$个朋友也去旅行

求每天去旅行的最大人数

## 输入格式

第一行3个整数，表示$n,m,k$

往下m行，每行两个整数$x,y$，表示这天早上$x$和$y$会变成朋友

## 输出格式

共$m$行，每行一个整数，表示每天晚上最多能去旅游的人数

## 样例 #1

### 输入

```
4 4 2
2 3
1 2
1 3
1 4

```

### 输出

```
0
0
3
3

```

## 样例 #2

### 输入

```
5 8 2
2 1
4 2
5 4
5 2
4 3
5 1
4 1
3 2

```

### 输出

```
0
0
0
3
3
4
4
5

```

## 样例 #3

### 输入

```
5 7 2
1 5
3 2
2 5
3 4
1 2
5 3
1 3

```

### 输出

```
0
0
0
0
3
4
4

```



---

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
title: "Three Pieces"
layout: "post"
diff: 提高+/省选-
pid: CF1065D
tag: ['搜索', '状态合并', '最短路']
---

# Three Pieces

## 题目描述

You stumbled upon a new kind of chess puzzles. The chessboard you are given is not necesserily $ 8 \times 8 $ , but it still is $ N \times N $ . Each square has some number written on it, all the numbers are from $ 1 $ to $ N^2 $ and all the numbers are pairwise distinct. The $ j $ -th square in the $ i $ -th row has a number $ A_{ij} $ written on it.

In your chess set you have only three pieces: a knight, a bishop and a rook. At first, you put one of them on the square with the number $ 1 $ (you can choose which one). Then you want to reach square $ 2 $ (possibly passing through some other squares in process), then square $ 3 $ and so on until you reach square $ N^2 $ . In one step you are allowed to either make a valid move with the current piece or replace it with some other piece. Each square can be visited arbitrary number of times.

A knight can move to a square that is two squares away horizontally and one square vertically, or two squares vertically and one square horizontally. A bishop moves diagonally. A rook moves horizontally or vertically. The move should be performed to a different square from the one a piece is currently standing on.

You want to minimize the number of steps of the whole traversal. Among all the paths to have the same number of steps you want to choose the one with the lowest number of piece replacements.

What is the path you should take to satisfy all conditions?

## 输入格式

The first line contains a single integer $ N $ ( $ 3 \le N \le 10 $ ) — the size of the chessboard.

Each of the next $ N $ lines contains $ N $ integers $ A_{i1}, A_{i2}, \dots, A_{iN} $ ( $ 1 \le A_{ij} \le N^2 $ ) — the numbers written on the squares of the $ i $ -th row of the board.

It is guaranteed that all $ A_{ij} $ are pairwise distinct.

## 输出格式

The only line should contain two integers — the number of steps in the best answer and the number of replacement moves in it.

## 说明/提示

Here are the steps for the first example (the starting piece is a knight):

1. Move to $ (3, 2) $
2. Move to $ (1, 3) $
3. Move to $ (3, 2) $
4. Replace the knight with a rook
5. Move to $ (3, 1) $
6. Move to $ (3, 3) $
7. Move to $ (3, 2) $
8. Move to $ (2, 2) $
9. Move to $ (2, 3) $
10. Move to $ (2, 1) $
11. Move to $ (1, 1) $
12. Move to $ (1, 2) $

## 样例 #1

### 输入

```
3
1 9 3
8 6 7
4 2 5

```

### 输出

```
12 1

```



---

---
title: "Coloring Brackets"
layout: "post"
diff: 提高+/省选-
pid: CF149D
tag: ['搜索', '记忆化搜索', '区间 DP']
---

# Coloring Brackets

## 题目描述

### 题意描述

给出一个配对的括号序列（如 “$\texttt{(())()}$”、“$\texttt{()}$” 等，“$\texttt{)()}$”、“$\texttt{(()}$”是不符合要求的），对该序列按照以下方法染色。

1. 一个括号可以染成红色、蓝色或者不染色。
2. 一对匹配的括号需要且只能将其中一个染色。
3. 相邻两个括号颜色不能相同（但都可以不染色）。

求符合条件的染色方案数，对 $1000000007$ 取模。

## 输入格式

一行一个字符串 $s$，表示括号序列（$2 \leqslant |s| \leqslant 700$）。

## 输出格式

一个数字，表示染色的方案数（对 $1000000007$ 取模）。

## 样例 #1

### 输入

```
(())

```

### 输出

```
12

```

## 样例 #2

### 输入

```
(()())

```

### 输出

```
40

```

## 样例 #3

### 输入

```
()

```

### 输出

```
4

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
title: "Smooth Sailing (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1920F1
tag: ['广度优先搜索 BFS']
---

# Smooth Sailing (Easy Version)

## 题目描述

The only difference between the two versions of this problem is the constraint on $ q $ . You can make hacks only if both versions of the problem are solved.

Thomas is sailing around an island surrounded by the ocean. The ocean and island can be represented by a grid with $ n $ rows and $ m $ columns. The rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The position of a cell at row $ r $ and column $ c $ can be represented as $ (r, c) $ . Below is an example of a valid grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/516df36ca6ac022124866d4043411e04ed0cf48c.png) Example of a valid gridThere are three types of cells: island, ocean and underwater volcano. Cells representing the island are marked with a '\#', cells representing the ocean are marked with a '.', and cells representing an underwater volcano are marked with a 'v'. It is guaranteed that there is at least one island cell and at least one underwater volcano cell. It is also guaranteed that the set of all island cells forms a single connected component $ ^{\dagger} $ and the set of all ocean cells and underwater volcano cells forms a single connected component. Additionally, it is guaranteed that there are no island cells at the edge of the grid (that is, at row $ 1 $ , at row $ n $ , at column $ 1 $ , and at column $ m $ ).

Define a round trip starting from cell $ (x, y) $ as a path Thomas takes which satisfies the following conditions:

- The path starts and ends at $ (x, y) $ .
- If Thomas is at cell $ (i, j) $ , he can go to cells $ (i+1, j) $ , $ (i-1, j) $ , $ (i, j-1) $ , and $ (i, j+1) $ as long as the destination cell is an ocean cell or an underwater volcano cell and is still inside the grid. Note that it is allowed for Thomas to visit the same cell multiple times in the same round trip.
- The path must go around the island and fully encircle it. Some path $ p $ fully encircles the island if it is impossible to go from an island cell to a cell on the grid border by only traveling to adjacent on a side or diagonal cells without visiting a cell on path $ p $ . In the image below, the path starting from $ (2, 2) $ , going to $ (1, 3) $ , and going back to $ (2, 2) $ the other way does not fully encircle the island and is not considered a round trip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/587237f643ee9a450f570eb64a27b00d982a357b.png) Example of a path that does not fully encircle the islandThe safety of a round trip is the minimum Manhattan distance $ ^{\ddagger} $ from a cell on the round trip to an underwater volcano (note that the presence of island cells does not impact this distance).

You have $ q $ queries. A query can be represented as $ (x, y) $ and for every query, you want to find the maximum safety of a round trip starting from $ (x, y) $ . It is guaranteed that $ (x, y) $ is an ocean cell or an underwater volcano cell.

 $ ^{\dagger} $ A set of cells forms a single connected component if from any cell of this set it is possible to reach any other cell of this set by moving only through the cells of this set, each time going to a cell with a common side.

 $ ^{\ddagger} $ Manhattan distance between cells $ (r_1, c_1) $ and $ (r_2, c_2) $ is equal to $ |r_1 - r_2| + |c_1 - c_2| $ .

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 3 \leq n, m \leq 10^5 $ , $ 9 \leq n \cdot m \leq 3 \cdot 10^5 $ , $ 1 \leq q \leq 5 $ ) — the number of rows and columns of the grid and the number of queries.

Each of the following $ n $ lines contains $ m $ characters describing the cells of the grid. The character '\#' denotes an island cell, '.' denotes an ocean cell, and 'v' denotes an underwater volcano cell.

It is guaranteed that there is at least one island cell and at least one underwater volcano cell. It is guaranteed that the set of all island cells forms a single connected component and the set of all ocean cells and underwater volcano cells forms a single connected component. Also, it is guaranteed that there are no island cells at the edge of the grid (that is, at the row $ 1 $ , at the row $ n $ , at the column $ 1 $ , and at the column $ m $ ).

The following $ q $ lines describe the queries. Each of these lines contains two integers $ x $ and $ y $ ( $ 1 \leq x \leq n $ , $ 1 \leq y \leq m $ ) denoting a round trip starting from $ (x, y) $ .

It is guaranteed that $ (x, y) $ is an ocean cell or an underwater volcano cell.

## 输出格式

For each query, output a single integer — the maximum safety of a round trip starting from the specified position.

## 说明/提示

For the first example, the image below shows an optimal round trip starting from $ (1, 1) $ . The round trip has a safety of $ 3 $ as the minimum Manhattan distance from a cell on the round trip to an underwater volcano is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F1/b0d58ba7a9650556e586a3235109c2b13f201dd2.png) Example of an optimal round tripFor the fourth example, remember that it is allowed for Thomas to visit the same cell multiple times in the same round trip. For example, doing so is necessary for the round trip starting from $ (7, 6) $ .

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
title: "Zebra-like Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF2086E
tag: ['数学', '贪心', '记忆化搜索', '数位 DP']
---

# Zebra-like Numbers

## 题目描述

我们称一个正整数为斑马数（zebra-like），如果它的二进制表示从最高有效位开始是交替的比特位，并且最低有效位等于 $1$。例如，数字 $1$、$5$ 和 $21$ 都是斑马数，因为它们的二进制表示 $1$、$101$ 和 $10101$ 满足要求，而数字 $10$ 不是斑马数，因为它的二进制表示 $1010$ 的最低有效位是 $0$。

我们定义一个正整数 $e$ 的斑马值为最小的整数 $p$，使得 $e$ 可以表示为 $p$ 个斑马数（可以相同也可以不同）的和。

给定三个整数 $l$、$r$ 和 $k$，计算满足 $l \le x \le r$ 且 $x$ 的斑马值等于 $k$ 的整数 $x$ 的数量。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。接下来是测试用例的描述。

每个测试用例的唯一一行包含三个整数 $l$、$r$（$1 \le l \le r \le 10^{18}$）和 $k$（$1 \le k \le 10^{18}$）。

## 输出格式

对于每个测试用例，输出一个整数——区间 $[l, r]$ 内斑马值为 $k$ 的整数的数量。

## 说明/提示

- 在第一个测试用例中，有 $13$ 个符合条件的数字：$3, 7, 11, 15, 23, 27, 31, 43, 47, 63, 87, 91, 95$。每个数字都可以表示为 $3$ 个斑马数的和。
- 在第二个测试用例中，数字 $1$ 的斑马值为 $1$，因此输出 $1$。
- 在第四个测试用例中，区间 $[2, 10]$ 内没有数字的斑马值为 $100$，因此输出 $0$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1 100 3
1 1 1
15 77 2
2 10 100
1234567 123456789101112131 12
```

### 输出

```
13
1
3
0
4246658701
```



---

---
title: "Gleb and Boating"
layout: "post"
diff: 提高+/省选-
pid: CF2091G
tag: ['动态规划 DP', '广度优先搜索 BFS', '标签465']
---

# Gleb and Boating

## 题目描述

程序员 Gleb 经常访问 IT Campus "NEIMARK" 参加编程训练。

Gleb 不仅是程序员，还是一位著名的划船运动员，因此他选择通过划皮划艇沿河流完成部分通勤路程。假设 Gleb 从点 $0$ 出发，必须到达点 $s$（即沿直线划行 $s$ 米）。为增加挑战性，Gleb 决定不离开线段 $[0, s]$。皮划艇的尺寸可忽略不计。

Gleb 是实力强劲的程序员！初始时他的力量为 $k$。Gleb 的力量直接影响皮划艇的运动：若当前力量为 $x$，则每次划桨可使皮划艇沿当前方向移动 $x$ 米。Gleb 可以调头并继续向相反方向移动，但此操作十分困难，每次调头后力量会减少 $1$。力量永远不会变为 $0$ —— 若当前力量为 $1$，则即使调头后仍保持 $1$。此外，Gleb 不能连续两次调头 —— 每次调头后必须至少移动一次才能再次调头。同理，Gleb 不能在出发后立即调头 —— 必须先进行一次划桨。

Gleb 希望在从点 $0$ 到达点 $s$ 的过程中不离开线段 $[0, s]$ 并尽可能保留最多力量。请帮助他 —— 给定 $s$ 和初始力量 $k$，确定到达点 $s$ 时可能保留的最大力量。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$ ($1 \leq t \leq 100$)。接下来是测试用例描述。

每个测试用例单独一行，包含两个整数 $s$ 和 $k$ ($1 \leq s \leq 10^9$，$1 \leq k \leq 1000$，$k \leq s$)。

保证所有测试用例的 $k$ 之和不超过 $2000$。

## 输出格式

对于每个测试用例，输出 Gleb 在旅程结束时可能保留的最大力量。


## 说明/提示

第一个样例中 Gleb 的一种可能移动方式：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091G/776d3b954c1b6c71e54b3d9667d6f17ccd68b4e7.png)  

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
9 6
10 7
24 2
123456 777
6 4
99 6
10 4
99 4
```

### 输出

```
4
1
2
775
1
4
2
2
```



---

---
title: "Commentator problem"
layout: "post"
diff: 提高+/省选-
pid: CF2C
tag: ['模拟', '搜索', '模拟退火']
---

# Commentator problem

## 题目描述

The Olympic Games in Bercouver are in full swing now. Here everyone has their own objectives: sportsmen compete for medals, and sport commentators compete for more convenient positions to give a running commentary. Today the main sport events take place at three round stadiums, and the commentator's objective is to choose the best point of observation, that is to say the point from where all the three stadiums can be observed. As all the sport competitions are of the same importance, the stadiums should be observed at the same angle. If the number of points meeting the conditions is more than one, the point with the maximum angle of observation is prefered.

Would you, please, help the famous Berland commentator G. Berniev to find the best point of observation. It should be noted, that the stadiums do not hide each other, the commentator can easily see one stadium through the other.

## 输入格式

The input data consists of three lines, each of them describes the position of one stadium. The lines have the format $ x,y,r $ , where ( $ x,y $ ) are the coordinates of the stadium's center ( $ -10^{3}<=x,y<=10^{3} $ ), and $ r $ ( $ 1<=r<=10^{3} $ ) is its radius. All the numbers in the input data are integer, stadiums do not have common points, and their centers are not on the same line.

## 输出格式

Print the coordinates of the required point with five digits after the decimal point. If there is no answer meeting the conditions, the program shouldn't print anything. The output data should be left blank.

## 样例 #1

### 输入

```
0 0 10
60 0 10
30 30 10

```

### 输出

```
30.00000 0.00000

```



---

---
title: "Valera and Fools"
layout: "post"
diff: 提高+/省选-
pid: CF369D
tag: ['动态规划 DP', '广度优先搜索 BFS']
---

# Valera and Fools

## 题目描述

One fine morning, $ n $ fools lined up in a row. After that, they numbered each other with numbers from $ 1 $ to $ n $ , inclusive. Each fool got a unique number. The fools decided not to change their numbers before the end of the fun.

Every fool has exactly $ k $ bullets and a pistol. In addition, the fool number $ i $ has probability of $ p_{i} $ (in percent) that he kills the fool he shoots at.

The fools decided to have several rounds of the fun. Each round of the fun looks like this: each currently living fool shoots at another living fool with the smallest number (a fool is not stupid enough to shoot at himself). All shots of the round are perfomed at one time (simultaneously). If there is exactly one living fool, he does not shoot.

Let's define a situation as the set of numbers of all the living fools at the some time. We say that a situation is possible if for some integer number $ j $ ( $ 0<=j<=k $ ) there is a nonzero probability that after $ j $ rounds of the fun this situation will occur.

Valera knows numbers $ p_{1},p_{2},...,p_{n} $ and $ k $ . Help Valera determine the number of distinct possible situations.

## 输入格式

The first line contains two integers $ n,k $ ( $ 1<=n,k<=3000 $ ) — the initial number of fools and the number of bullets for each fool.

The second line contains $ n $ integers $ p_{1},p_{2},...,p_{n} $ ( $ 0<=p_{i}<=100 $ ) — the given probabilities (in percent).

## 输出格式

Print a single number — the answer to the problem.

## 说明/提示

In the first sample, any situation is possible, except for situation $ {1,2} $ .

In the second sample there is exactly one fool, so he does not make shots.

In the third sample the possible situations are $ {1,2} $ (after zero rounds) and the "empty" situation $ {} $ (after one round).

In the fourth sample, the only possible situation is $ {1,2,3} $ .

## 样例 #1

### 输入

```
3 3
50 50 50

```

### 输出

```
7

```

## 样例 #2

### 输入

```
1 1
100

```

### 输出

```
1

```

## 样例 #3

### 输入

```
2 1
100 100

```

### 输出

```
2

```

## 样例 #4

### 输入

```
3 3
0 0 0

```

### 输出

```
1

```



---

---
title: "New Year Tree"
layout: "post"
diff: 提高+/省选-
pid: CF379F
tag: ['广度优先搜索 BFS', '最近公共祖先 LCA', '树的直径']
---

# New Year Tree

## 题目描述

You are a programmer and you have a New Year Tree (not the traditional fur tree, though) — a tree of four vertices: one vertex of degree three (has number 1), connected with three leaves (their numbers are from 2 to 4).

On the New Year, programmers usually have fun. You decided to have fun as well by adding vertices to the tree. One adding operation looks as follows:

- First we choose some leaf of the tree with number $ v $ .
- Let's mark the number of vertices on the tree at this moment by variable $ n $ , then two vertexes are added to the tree, their numbers are $ n+1 $ and $ n+2 $ , also you get new edges, one between vertices $ v $ and $ n+1 $ and one between vertices $ v $ and $ n+2 $ .

Your task is not just to model the process of adding vertices to the tree, but after each adding operation print the diameter of the current tree. Come on, let's solve the New Year problem!

## 输入格式

The first line contains integer $ q $ $ (1<=q<=5·10^{5}) $ — the number of operations. Each of the next $ q $ lines contains integer $ v_{i} $ $ (1<=v_{i}<=n) $ — the operation of adding leaves to vertex $ v_{i} $ . Variable $ n $ represents the number of vertices in the current tree.

It is guaranteed that all given operations are correct.

## 输出格式

Print $ q $ integers — the diameter of the current tree after each operation.

## 样例 #1

### 输入

```
5
2
3
4
8
5

```

### 输出

```
3
4
4
5
6

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
title: "Strictly Positive Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF402E
tag: ['搜索', '强连通分量', '栈']
---

# Strictly Positive Matrix

## 题目描述

You have matrix $ a $ of size $ n×n $ . Let's number the rows of the matrix from $ 1 $ to $ n $ from top to bottom, let's number the columns from $ 1 $ to $ n $ from left to right. Let's use $ a_{ij} $ to represent the element on the intersection of the $ i $ -th row and the $ j $ -th column.

Matrix $ a $ meets the following two conditions:

- for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the following inequality holds: $ a_{ij}>=0 $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF402E/5a3402d889c26bb1dab24aca748b24c9c6e8398d.png).

Matrix $ b $ is strictly positive, if for any numbers $ i,j $ ( $ 1<=i,j<=n $ ) the inequality $ b_{ij}&gt;0 $ holds. You task is to determine if there is such integer $ k>=1 $ , that matrix $ a^{k} $ is strictly positive.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=2000 $ ) — the number of rows and columns in matrix $ a $ .

The next $ n $ lines contain the description of the rows of matrix $ a $ . The $ i $ -th line contains $ n $ non-negative integers $ a_{i1},a_{i2},...,a_{in} $ ( $ 0<=a_{ij}<=50 $ ). It is guaranteed that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF402E/5a3402d889c26bb1dab24aca748b24c9c6e8398d.png).

## 输出格式

If there is a positive integer $ k>=1 $ , such that matrix $ a^{k} $ is strictly positive, print "YES" (without the quotes). Otherwise, print "NO" (without the quotes).

## 样例 #1

### 输入

```
2
1 0
0 1

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
5
4 5 6 1 2
1 2 3 4 5
6 4 1 2 4
1 1 1 1 1
4 4 4 4 4

```

### 输出

```
YES

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
title: "Anya and Cubes"
layout: "post"
diff: 提高+/省选-
pid: CF525E
tag: ['搜索', '枚举', '剪枝', '折半搜索 meet in the middle']
---

# Anya and Cubes

## 题目描述

Anya loves to fold and stick. Today she decided to do just that.

Anya has $ n $ cubes lying in a line and numbered from $ 1 $ to $ n $ from left to right, with natural numbers written on them. She also has $ k $ stickers with exclamation marks. We know that the number of stickers does not exceed the number of cubes.

Anya can stick an exclamation mark on the cube and get the factorial of the number written on the cube. For example, if a cube reads $ 5 $, then after the sticking it reads $ 5! $, which equals $ 120 $.

You need to help Anya count how many ways there are to choose some of the cubes and stick on some of the chosen cubes at most $ k $ exclamation marks so that the sum of the numbers written on the chosen cubes after the sticking becomes equal to $ S $. Anya can stick at most one exclamation mark on each cube. Can you do it?

Two ways are considered the same if they have the same set of chosen cubes and the same set of cubes with exclamation marks.

## 输入格式

The first line of the input contains three space-separated integers $ n $, $ k $ and $ S\ (1\le n\le25,\ 0\le k\le n,\ 1\le S\le10^{16})$ — the number of cubes and the number of stickers that Anya has, and the sum that she needs to get.

The second line contains $ n $ positive integers $ a_{i}\ ( 1\le a_{i}\le10^{9}) $ — the numbers, written on the cubes. The cubes in the input are described in the order from left to right, starting from the first one.

Multiple cubes can contain the same numbers.

## 输出格式

Output the number of ways to choose some number of cubes and stick exclamation marks on some of them so that the sum of the numbers became equal to the given number $ S $ .

## 说明/提示

In the first sample the only way is to choose both cubes and stick an exclamation mark on each of them.

In the second sample the only way is to choose both cubes but don't stick an exclamation mark on any of them.

In the third sample it is possible to choose any of the cubes in three ways, and also we may choose to stick or not to stick the exclamation mark on it. So, the total number of ways is six.

## 样例 #1

### 输入

```
2 2 30
4 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 2 7
4 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1 1
1 1 1

```

### 输出

```
6

```



---

---
title: "Zuma"
layout: "post"
diff: 提高+/省选-
pid: CF607B
tag: ['字符串', '搜索', '记忆化搜索', '区间 DP']
---

# Zuma

## 题目描述

$\texttt{Genos}$ 最近在他的手机上下载了祖玛游戏。在祖玛游戏里，存在 $n$ 个一行的宝石，第 $i$ 个宝石的颜色是 $C_i$。这个游戏的目标是尽快的消灭一行中所有的宝石。

在一秒钟，$\texttt{Genos}$ 能很快的挑选出这些有颜色的宝石中的一个回文的、连续的子串，并将这个子串移除。每当一个子串被删除后，剩余的宝石将连接在一起，形成一个新的行列。

你的任务是：求出把整个宝石串都移除的最短时间。

## 输入格式

第一行包含一个整数 $n(1 \le n \le 500)$，表示宝石串的长度。第二行包含 $n$ 个被空格分开的整数，第 $i(1 \le i \le n)$ 个表示这行中第 $i$ 个珠子的颜色。

## 输出格式

输出一个整数，把这行珠子移除的最短时间。

## 说明/提示

在第一个例子中，$\texttt{Genos}$ 可以在一秒钟就把这行珠子全部移走。在第二个例子中，$\texttt{Genos}$ 一次只能移走一个珠子，所以移走三个珠子花费他三秒。在第三个例子中，为了达到 $2$ 秒的最快时间，先移除回文串 $\texttt{4 4}$,再移除回文串 $\texttt{1 2 3 2 1}$。

感谢 @Administrator2004 提供的翻译

## 样例 #1

### 输入

```
3
1 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
7
1 4 4 2 3 2 1

```

### 输出

```
2

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
title: "Vladik and chat"
layout: "post"
diff: 提高+/省选-
pid: CF754C
tag: ['动态规划 DP', '搜索']
---

# Vladik and chat

## 题目描述

Recently Vladik discovered a new entertainment — coding bots for social networks. He would like to use machine learning in his bots so now he want to prepare some learning data for them.

At first, he need to download $ t $ chats. Vladik coded a script which should have downloaded the chats, however, something went wrong. In particular, some of the messages have no information of their sender. It is known that if a person sends several messages in a row, they all are merged into a single message. It means that there could not be two or more messages in a row with the same sender. Moreover, a sender never mention himself in his messages.

Vladik wants to recover senders of all the messages so that each two neighboring messages will have different senders and no sender will mention himself in his messages.

He has no idea of how to do this, and asks you for help. Help Vladik to recover senders in each of the chats!

## 输入格式

The first line contains single integer $ t $ ( $ 1<=t<=10 $ ) — the number of chats. The $ t $ chats follow. Each chat is given in the following format.

The first line of each chat description contains single integer $ n $ ( $ 1<=n<=100 $ ) — the number of users in the chat.

The next line contains $ n $ space-separated distinct usernames. Each username consists of lowercase and uppercase English letters and digits. The usernames can't start with a digit. Two usernames are different even if they differ only with letters' case. The length of username is positive and doesn't exceed $ 10 $ characters.

The next line contains single integer $ m $ ( $ 1<=m<=100 $ ) — the number of messages in the chat. The next $ m $ line contain the messages in the following formats, one per line:

- <username>:<text> — the format of a message with known sender. The username should appear in the list of usernames of the chat.
- <?>:<text> — the format of a message with unknown sender.

The text of a message can consist of lowercase and uppercase English letter, digits, characters '.' (dot), ',' (comma), '!' (exclamation mark), '?' (question mark) and ' ' (space). The text doesn't contain trailing spaces. The length of the text is positive and doesn't exceed $ 100 $ characters.

We say that a text mention a user if his username appears in the text as a word. In other words, the username appears in a such a position that the two characters before and after its appearance either do not exist or are not English letters or digits. For example, the text "Vasya, masha13 and Kate!" can mention users "Vasya", "masha13", "and" and "Kate", but not "masha".

It is guaranteed that in each chat no known sender mention himself in his messages and there are no two neighboring messages with the same known sender.

## 输出格式

Print the information about the $ t $ chats in the following format:

If it is not possible to recover senders, print single line "Impossible" for this chat. Otherwise print $ m $ messages in the following format:

<username>:<text>

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
1
2
Vladik netman
2
?: Hello, Vladik!
?: Hi

```

### 输出

```
netman: Hello, Vladik!
Vladik: Hi

```

## 样例 #2

### 输入

```
1
2
netman vladik
3
netman:how are you?
?:wrong message
vladik:im fine

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
2
3
netman vladik Fedosik
2
?: users are netman, vladik, Fedosik
vladik: something wrong with this chat
4
netman tigerrrrr banany2001 klinchuh
4
?: tigerrrrr, banany2001, klinchuh, my favourite team ever, are you ready?
klinchuh: yes, coach!
?: yes, netman
banany2001: yes of course.

```

### 输出

```
Impossible
netman: tigerrrrr, banany2001, klinchuh, my favourite team ever, are you ready?
klinchuh: yes, coach!
tigerrrrr: yes, netman
banany2001: yes of course.

```



---

---
title: "Connected Components?"
layout: "post"
diff: 提高+/省选-
pid: CF920E
tag: ['枚举', '广度优先搜索 BFS', '连通块']
---

# Connected Components?

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920E/2671f3d87e6b285ebb30abeafea800e65bb56d51.png) edges. Instead of giving you the edges that exist in the graph, we give you $ m $ unordered pairs ( $ x,y $ ) such that there is no edge between $ x $ and $ y $ , and if some pair of vertices is not listed in the input, then there is an edge between these vertices.

You have to find the number of connected components in the graph and the size of each component. A connected component is a set of vertices $ X $ such that for every two vertices from this set there exists at least one path in the graph connecting these vertices, but adding any other vertex to $ X $ violates this rule.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=200000 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920E/2a08d4fdef413c2e634516e97a2188a97c148ac8.png)).

Then $ m $ lines follow, each containing a pair of integers $ x $ and $ y $ ( $ 1<=x,y<=n $ , $ x≠y $ ) denoting that there is no edge between $ x $ and $ y $ . Each pair is listed at most once; ( $ x,y $ ) and ( $ y,x $ ) are considered the same (so they are never listed in the same test). If some pair of vertices is not listed in the input, then there exists an edge between those vertices.

## 输出格式

Firstly print $ k $ — the number of connected components in this graph.

Then print $ k $ integers — the sizes of components. You should output these integers in non-descending order.

## 样例 #1

### 输入

```
5 5
1 2
3 4
3 2
4 2
2 5

```

### 输出

```
2
1 4 
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

