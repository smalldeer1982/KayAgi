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
title: "Digital Village (Extreme Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2021E3
tag: ['动态规划 DP', 'Kruskal 重构树', '凸包']
---

# Digital Village (Extreme Version)

## 题目描述

**这是问题的极端版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 2000$ )。对每个测试用例说明如下：

每个测试用例的第一行包含三个整数 $n$ , $m$ , $p$ ( $2 \le n \le 2\times 10^5$ ; $n-1 \le m \le 2\times 10^5$ ; $1 \le p \le n$ )，表示房屋数量、电缆数量和需要网络的房屋数量。

每个测试用例的第二行包含 $p$ 个整数 $s_1, s_2, \ldots, s_p$ ( $1 \le s_i \le n$ )，表示需要上网的房屋。保证 $s$ 中的所有元素都是不同的。

每个测试用例下 $m$ 行每行包含三个整数 $u_i$、$v_i$ 和 $w_i$（$1 \le u_i , v_i \le n$ ; $1 \le w_i \le 10^9$）表示一条连接房屋 $u_i$ 和房屋 $v_i$ 的网线，延迟为 $w_i$。保证给定的边构成一个连通的简单图。

保证 $n$ 和 $m$ 之和不超过 $2 \times 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数：对**每个**$k = 1,2,\ldots,n$，计算所有需要上网的房屋所能达到的最小总延迟。

**样例解释**

第一个测试用例中，$k=3$ 的一个的最佳解决方案是在顶点 $2$ 、 $6$ 和 $8$ 安装服务器，并获得以下延迟：

- $\text{latency}(2) = 0$
- $\text{latency}(5) = \max(3, 5) = 5$
- $\text{latency}(6) = 0$
- $\text{latency}(8) = 0$
- $\text{latency}(9) = \max(2, 4) = 4$

因此总延迟为 $0+5+0+0+4=9$ 。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2
```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0
```



---

