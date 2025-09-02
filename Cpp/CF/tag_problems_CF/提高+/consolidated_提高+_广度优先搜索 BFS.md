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

