---
title: "Valid BFS?"
layout: "post"
diff: 普及/提高-
pid: CF1037D
tag: ['排序', '广度优先搜索 BFS', '队列']
---

# Valid BFS?

## 题目描述

The [BFS](https://en.wikipedia.org/wiki/Breadth-first_search) algorithm is defined as follows.

1. Consider an undirected graph with vertices numbered from $ 1 $ to $ n $ . Initialize $ q $ as a new [queue](http://gg.gg/queue_en) containing only vertex $ 1 $ , mark the vertex $ 1 $ as used.
2. Extract a vertex $ v $ from the head of the queue $ q $ .
3. Print the index of vertex $ v $ .
4. Iterate in arbitrary order through all such vertices $ u $ that $ u $ is a neighbor of $ v $ and is not marked yet as used. Mark the vertex $ u $ as used and insert it into the tail of the queue $ q $ .
5. If the queue is not empty, continue from step 2.
6. Otherwise finish.

Since the order of choosing neighbors of each vertex can vary, it turns out that there may be multiple sequences which BFS can print.

In this problem you need to check whether a given sequence corresponds to some valid BFS traversal of the given tree starting from vertex $ 1 $ . The [tree](http://gg.gg/tree_en) is an undirected graph, such that there is exactly one simple path between any two vertices.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) which denotes the number of nodes in the tree.

The following $ n - 1 $ lines describe the edges of the tree. Each of them contains two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ ) — the endpoints of the corresponding edge of the tree. It is guaranteed that the given graph is a tree.

The last line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the sequence to check.

## 输出格式

Print "Yes" (quotes for clarity) if the sequence corresponds to some valid BFS traversal of the given tree and "No" (quotes for clarity) otherwise.

You can print each letter in any case (upper or lower).

## 说明/提示

Both sample tests have the same tree in them.

In this tree, there are two valid BFS orderings:

- $ 1, 2, 3, 4 $ ,
- $ 1, 3, 2, 4 $ .

The ordering $ 1, 2, 4, 3 $ doesn't correspond to any valid BFS order.

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1 2 3 4

```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4
1 2
1 3
2 4
1 2 4 3

```

### 输出

```
No
```



---

---
title: "Labyrinth"
layout: "post"
diff: 普及/提高-
pid: CF1063B
tag: ['搜索', '广度优先搜索 BFS', '剪枝']
---

# Labyrinth

## 题目描述

## 题意描述
你正在玩一款电脑游戏。在其中一关，你位于一个 $n$ 行 $m$ 列的迷宫。每个格子要么是可以通过的空地，要么是障碍。迷宫的起点位于第 $r$ 行第 $c$ 列。你每一步可以向上、下、左、右中的一个方向移动一格，前提是那一格不是障碍。你无法越出迷宫的边界。

不幸的是，你的键盘快坏了，所以你只能向左移动不超过 $x$ 格，并且向右移动不超过 $y$ 格。因为上下键情况良好，所以对向上和向下的移动次数没有限制。

现在你想知道在满足上述条件的情况下，从起点出发，有多少格子可以到达（包括起点）？

## 输入格式

第一行包含两个数 $n, m$ $(1 <= n, m, <= 2000)$ ,表示迷宫的行数和列数。

第二行包含两个数 $r,c$ $(1 <= r <= n, 1 <= c <= m)$ ,表示起点位于第 $r$ 行第 $c$ 列。

第三行包含两个数 $x,y$ $(1 <= x,y <= 10^9)$ ,表示最多向左或向右移动的次数。

接下来 $n$ 行描述这个迷宫，每行为一个长为 $m$ 的由 '.' 和 '\*' 组成的字符串。
'.' 表示空地， '\*' 表示障碍。
输入保证起点不是障碍。

## 输出格式

输出一个整数，表示从起点出发可以到达的格子数，包括起点本身。

## 样例 #1

### 输入

```
4 5
3 2
1 2
.....
.***.
...**
*....

```

### 输出

```
10

```

## 样例 #2

### 输入

```
4 4
2 2
0 1
....
..*.
....
....

```

### 输出

```
7

```



---

---
title: "Required Length"
layout: "post"
diff: 普及/提高-
pid: CF1681D
tag: ['动态规划 DP', '枚举', '广度优先搜索 BFS']
---

# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 输入格式

The only line of the input contains two integers $ n $ and $ x $ ( $ 2 \le n \le 19 $ ; $ 1 \le x < 10^{n-1} $ ).

## 输出格式

Print one integer — the minimum number of operations required to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ , or $ -1 $ if it is impossible.

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
13 42
```

### 输出

```
12
```



---

---
title: "L-shapes"
layout: "post"
diff: 普及/提高-
pid: CF1722F
tag: ['搜索', '广度优先搜索 BFS', '深度优先搜索 DFS']
---

# L-shapes

## 题目描述

An L-shape is a figure on gridded paper that looks like the first four pictures below. An L-shape contains exactly three shaded cells (denoted by \*), which can be rotated in any way.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722F/c4bb8e8c5c94521e87ed2d5ba5ef373384bb7be7.png)You are given a rectangular grid. Determine if it contains L-shapes only, where L-shapes can't touch an edge or corner. More formally:

- Each shaded cell in the grid is part of exactly one L-shape, and
- no two L-shapes are adjacent by edge or corner.

For example, the last two grids in the picture above do not satisfy the condition because the two L-shapes touch by corner and edge, respectively.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 50 $ ) — the number of rows and columns in the grid, respectively.

Then $ n $ lines follow, each containing $ m $ characters. Each of these characters is either '.' or '\*' — an empty cell or a shaded cell, respectively.

## 输出格式

For each test case, output "YES" if the grid is made up of L-shape that don't share edges or corners, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 输入

```
10
6 10
........**
.**......*
..*..*....
.....**...
...*.....*
..**....**
6 10
....*...**
.**......*
..*..*....
.....**...
...*.....*
..**....**
3 3
...
***
...
4 4
.*..
**..
..**
..*.
5 4
.*..
**..
....
..**
..*.
3 2
.*
**
*.
2 3
*..
.**
3 2
..
**
*.
3 3
.**
*.*
**.
3 3
..*
.**
..*
```

### 输出

```
YES
NO
NO
NO
YES
NO
NO
YES
NO
NO
```



---

---
title: "Trapped in the Witch's Labyrinth"
layout: "post"
diff: 普及/提高-
pid: CF2034C
tag: ['搜索', '广度优先搜索 BFS', '深度优先搜索 DFS']
---

# Trapped in the Witch's Labyrinth

## 题目描述

在《列王纪》传奇英雄鲁斯塔姆的第四个任务中，一个老女巫创造了一个迷宫来困住他。迷宫是一个 $n\times m$ 的矩形网格，迷宫中每一个单元格都有箭头，指向上、下、左或右的一个特定方向。女巫对鲁斯塔姆施了魔法，他每进入一个单元格，都会按照箭头的方向移动到下一个单元格。

如果鲁斯塔姆可以离开迷宫，他将战胜女巫。否则他将永远被困在迷宫中。

还有一些单元格的方向没有被女巫确定，她希望你指定一些方向，使得鲁斯塔姆能够被困住的起始格最多。你的任务是找到使得鲁斯塔姆被困住的最多起始单元格数。

## 输入格式

第一行，一个整数 $t$ ($1\le t\le 10^4$)，表示数据组数。

对于每组数据：

- 第一行，两个整数 $n,m$ ($1\le n,m\le 1000$)，表示迷宫的行数和列数。
- 接下来的 $n$ 行，每行 $m$ 个字符，表示这个迷宫。每个字符都是以下之一：
	- `U`：向上；
   - `D`：向下；
   - `L`：向左；
   - `R`：向右；
   - `?`：未确定；

保证所有 $n\times m$ 之和不超过 $10^6$。

## 输出格式

对于每组数据，输出一个整数，表示使得鲁斯塔姆被困住的最多起始单元格数。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
3
3 3
UUU
L?R
DDD
2 3
???
???
3 3
?U?
R?L
RDL
```

### 输出

```
0
6
5
```



---

---
title: "Drunken Maze"
layout: "post"
diff: 普及/提高-
pid: CF2041D
tag: ['广度优先搜索 BFS']
---

# Drunken Maze

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041D/ac90366c626ba21a7610cf55d06b2398a53105ff.png) Image generated by ChatGPT 4o.You are given a two-dimensional maze with a start and end position. Your task is to find the fastest way to get from the start to the end position. The fastest way is to make the minimum number of steps where one step is going left, right, up, or down. Of course, you cannot walk through walls.

There is, however, a catch: If you make more than three steps in the same direction, you lose balance and fall down. Therefore, it is forbidden to make more than three consecutive steps in the same direction. It is okay to walk three times to the right, then one step to the left, and then again three steps to the right. This has the same effect as taking five steps to the right, but is slower.

## 输入格式

The first line contains two numbers $ n $ and $ m $ , which are the height and width of the maze. This is followed by an ASCII-representation of the maze where $ \tt{\#} $ is a wall, $ \tt{.} $ is an empty space, and $ \tt S $ and $ \tt T $ are the start and end positions.

- $ 12 \leq n\times m \leq 200000 $ .
- $ 3\leq n,m \leq 10000 $ .
- Characters are only $ \tt{.\#ST} $ and there is exactly one $ \tt{S} $ and one $ \tt{T} $ .
- The outer borders are only $ \tt{\#} $ (walls).

## 输出格式

The minimum number of steps to reach the end position from the start position or -1 if that is impossible.

## 样例 #1

### 输入

```
7 12
############
#S........T#
#.########.#
#..........#
#..........#
#..#..#....#
############
```

### 输出

```
15
```

## 样例 #2

### 输入

```
5 8
########
#......#
#.####.#
#...T#S#
########
```

### 输出

```
14
```

## 样例 #3

### 输入

```
5 8
########
#.#S...#
#.####.#
#...T#.#
########
```

### 输出

```
-1
```



---

---
title: "Gellyfish and Flaming Peony"
layout: "post"
diff: 普及/提高-
pid: CF2115A
tag: ['动态规划 DP', '广度优先搜索 BFS']
---

# Gellyfish and Flaming Peony

## 题目描述

Gellyfish hates math problems, but she has to finish her math homework:

Gellyfish is given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ .

She needs to do the following two-step operation until all elements of $ a $ are equal:

1. Select two indexes $ i $ , $ j $ satisfying $ 1 \leq i, j \leq n $ and $ i \neq j $ .
2. Replace $ a_i $ with $ \gcd(a_i, a_j) $ .

Now, Gellyfish asks you for the minimum number of operations to achieve her goal.

It can be proven that Gellyfish can always achieve her goal.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5000 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 5000 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \leq a_i \leq 5000 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations to achieve her goal.

## 说明/提示

In the first test case, the following is a way that minimizes the number of operations:

1. Choose $ i = 3 $ and $ j=2 $ and replace $ a_3 $ with $ \gcd(a_3,a_2) = \gcd(30, 20) = 10 $ , then $ a $ becomes $ [12, 20, 10] $ .
2. Choose $ i=1 $ and $ j=3 $ and replace $ a_1 $ with $ \gcd(a_1,a_3) = \gcd(12, 10) = 2 $ , then $ a $ becomes $ [2, 20, 10] $ .
3. Choose $ i=2 $ and $ j=1 $ and replace $ a_2 $ with $ \gcd(a_2,a_1) = \gcd(20, 2) = 2 $ , then $ a $ becomes $ [2, 2, 10] $ .
4. Choose $ i=3 $ and $ j=1 $ and replace $ a_3 $ with $ \gcd(a_3,a_1) = \gcd(10, 2) = 2 $ , then $ a $ becomes $ [2, 2, 2] $ .

## 样例 #1

### 输入

```
3
3
12 20 30
6
1 9 1 9 8 1
3
6 14 15
```

### 输出

```
4
3
3
```



---

---
title: "Biridian Forest"
layout: "post"
diff: 普及/提高-
pid: CF329B
tag: ['广度优先搜索 BFS']
---

# Biridian Forest

## 题目描述

你发现你身处一片森林，你需要找到出口逃离这里。但是在森林中还有其他人和很多树木。他们会给你造成阻碍。

所有人都会沿向终点的最短路径行进。

## 输入格式

输入 $n$ 和 $m$，接下来输入一张 $n \times m$ 的二维地图，地图中只包含以下元素：

- `T`：一棵树，不能通行。
- `S`：你的起始位置，在地图中只有一个。
- `E`：出口，在地图中也只有一个。
- $0 \sim 9$ 中的一个数字：这个位置上的人数，可以从该点通过。

## 输出格式

输出在你到达出口前，到达出口的人数（包括与你同时到达终点的人）。

## 样例 #1

### 输入

```
5 7
000E0T3
T0TT0T0
010T0T0
2T0T0T0
0T0S000

```

### 输出

```
3

```

## 样例 #2

### 输入

```
1 4
SE23

```

### 输出

```
2

```



---

---
title: "Fire Again"
layout: "post"
diff: 普及/提高-
pid: CF35C
tag: ['广度优先搜索 BFS']
---

# Fire Again

## 题目描述

**题目大意：**

有 $n\times m$ 棵树组成的矩形，初始时有 $K$ 棵树被点燃了。如果一棵树有相邻的树被点燃，在一分钟之后，这棵树也会被点燃。问最晚点燃的树的坐标（输出任意一个）。

## 输入格式

第一个输入行包含两个整数 $n,m(1\le n,m\le 2000)$。

第二行包含一个整数 $K(1\le K\le 10)$，表示初始时被点燃的树的个数。

第三行包含 $K$ 对整数 $X_1,Y_1,X_2,Y_2,...,X_K,Y_K$，表示初始时被点燃的树的坐标，保证没有两个坐标重合。

## 输出格式

用两个空格分隔的整数输出一行 $X$ 和 $Y$，即最后一个被点燃的树的坐标。

本题需要使用文件输入输出，输入输出文件分别为 `input.txt` 和`output.txt`。

## 样例 #1

### 输入

```
3 3
1
2 2

```

### 输出

```
1 1

```

## 样例 #2

### 输入

```
3 3
1
1 1

```

### 输出

```
3 3

```

## 样例 #3

### 输入

```
3 3
2
1 1 3 3

```

### 输出

```
2 2
```



---

---
title: "Fair"
layout: "post"
diff: 普及/提高-
pid: CF986A
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# Fair

## 题目描述

一些公司将在Byteland举办商品交易会（or博览会？）。在Byteland有 $n$ 个城市，城市间有 $m$ 条双向道路。当然，城镇之间两两连通。
Byteland生产的货物有 $k$ 种类型，每个城镇只生产一种。
为了举办商品交易会，你必须至少带来 $s$ 种不同类型的商品。将货物从 $u$ 镇带到城镇 $v$ 将花费 $d(u,v)$ 的费用，其中 $d(u,v)$ 是从 $u$ 到 $v$ 的最短路径的长度。
路径的长度是这个路径中的道路的数量。              
组织者将支付所有的运输费用，但他们可以选择从哪些城镇带来货物。现在他们想计算每个城镇举办商品交易会的最小费用。

## 输入格式

第一行 $4$ 个整数$n$ , $m$ , $k$ , $s$ ($1\le n\le 10^5 $,$1\le m\le 10^5 $,$1\le s\le k\le min(n,100)$ )——分别表示 城镇数，道路数，生产的货物数，举办商品交易会所需的货物数。

接下来一行$n$个整数$a_1,a_2,...,a_n(1\le a_i \le k)$ , $a_i$是第$i$个城镇生产的商品种类.保证$1$和$k$之间的所有整数在整数$a_i$中至少出现一次。 

接下来$m$行表示道路。每行两个整数 $u$ $v$ $(1 \le u$,$v \le n, u\ne v)$ 表示  $u$ $v$ 之间有一条双向道路。保证每两个城镇之间只有一条路。并且城镇之间两两连通。

## 输出格式

输出$n$个数。第$i$个数表示在第$i$个城镇举办商品交易会所需花在运输上的最小费用。数与数之间用空格分开。

## 样例 #1

### 输入

```
5 5 4 3
1 2 4 3 2
1 2
2 3
3 4
4 1
4 5

```

### 输出

```
2 2 2 2 3 

```

## 样例 #2

### 输入

```
7 6 3 2
1 2 3 3 2 2 1
1 2
2 3
3 4
2 5
5 6
6 7

```

### 输出

```
1 1 1 2 2 1 1 

```



---

