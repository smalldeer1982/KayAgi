---
title: "Three Parts of the Array"
layout: "post"
diff: 普及/提高-
pid: CF1006C
tag: ['递归', '深度优先搜索 DFS', '前缀和']
---

# Three Parts of the Array

## 题目描述

**问题描述**  
给定一个长度为n的整数序列$\{d_1,d_2,\dots,d_n\}$。  
你的任务是将序列分成3部分，每部分可以是空的，并保证每一个数都属于这三个部分的某一个，每一部分都必须是一些连续的整数。  
设三部分的和分别为$sum_1$,$sum_2$,$sum_3$。  那么你需要在所有划分方案中找到一个方案使得$sum_1=sum_3$且$sum_1$尽可能的大。  
确切的说，如果第一部分包含$a$个整数，第二部分包含$b$个整数而第三部分包含$c$个，那么应该有
$$sum_1 = \sum\limits_{1 \le i \le a}d_i,$$
$$sum_2 = \sum\limits_{a + 1 \le i \le a + b}d_i,$$
$$sum_3 = \sum\limits_{a + b + 1 \le i \le a + b + c}d_i.$$
并且对于空的那部分，它的和为0。  
你需要在所有划分方案中找到一个方案使得$sum_1=sum_3$且$sum_1$尽可能的大。

## 输入格式

第一行一个整数$n(1 \le n \le 2 \cdot 10^5)$  
第二行包含n个整数$d_1, d_2, \dots, d_n(1 \le d_i \le 10^9)$

## 输出格式

一行一个整数，表示$sum_1$的最大值  
显然，至少有一种划分方案是合法的$(a=c=0,b=n)$

## 样例 #1

### 输入

```
5
1 3 1 1 4

```

### 输出

```
5

```

## 样例 #2

### 输入

```
5
1 3 2 1 4

```

### 输出

```
4

```

## 样例 #3

### 输入

```
3
4 1 2

```

### 输出

```
0

```



---

---
title: "Vasya and Golden Ticket"
layout: "post"
diff: 普及/提高-
pid: CF1030C
tag: ['搜索', '枚举', '前缀和']
---

# Vasya and Golden Ticket

## 题目描述

Recently Vasya found a golden ticket — a sequence which consists of $ n $ digits $ a_1a_2\dots a_n $ . Vasya considers a ticket to be lucky if it can be divided into two or more non-intersecting segments with equal sums. For example, ticket $ 350178 $ is lucky since it can be divided into three segments $ 350 $ , $ 17 $ and $ 8 $ : $ 3+5+0=1+7=8 $ . Note that each digit of sequence should belong to exactly one segment.

Help Vasya! Tell him if the golden ticket he found is lucky or not.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the number of digits in the ticket.

The second line contains $ n $ digits $ a_1 a_2 \dots a_n $ ( $ 0 \le a_i \le 9 $ ) — the golden ticket. Digits are printed without spaces.

## 输出格式

If the golden ticket is lucky then print "YES", otherwise print "NO" (both case insensitive).

## 说明/提示

In the first example the ticket can be divided into $ 7 $ , $ 34 $ and $ 52 $ : $ 7=3+4=5+2 $ .

In the second example it is impossible to divide ticket into segments with equal sum.

## 样例 #1

### 输入

```
5
73452

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
1248

```

### 输出

```
NO

```



---

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
title: "Coffee Break"
layout: "post"
diff: 普及/提高-
pid: CF1041C
tag: ['搜索', '贪心', '二分']
---

# Coffee Break

## 题目描述

### 题目大意：
给定$n$个数和一个$k$，这$n$个数都不超过$m$

每次从没被去掉的数里面选一个数$a$，去掉$a$，然后可以任意一个$b(b>a+k)$，然后去掉任意一个$c(c>b+k)$，以此类推

问最少能选多少个$a$，然后输出每个数都是选第几个$a$的时候被去掉的

## 输入格式

一行三个整数$n,m,k$

再一行$n$个整数，表示给定的数

## 输出格式

第一行一个整数，表示最少选$a$的个数

第二行$n$个整数，表示每个数都是选第几个$a$时被去掉的

## 样例 #1

### 输入

```
4 5 3
3 5 1 2

```

### 输出

```
3
3 1 1 2 

```

## 样例 #2

### 输入

```
10 10 1
10 5 7 4 6 3 2 1 9 8

```

### 输出

```
2
2 1 1 2 2 1 2 1 1 2 

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
title: "Polygon"
layout: "post"
diff: 普及/提高-
pid: CF1360E
tag: ['模拟', '深度优先搜索 DFS']
---

# Polygon

## 题目描述

Polygon is not only the best platform for developing problems but also a square matrix with side $ n $ , initially filled with the character 0.

On the polygon, military training was held. The soldiers placed a cannon above each cell in the first row and a cannon to the left of each cell in the first column. Thus, exactly $ 2n $ cannons were placed.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)Initial polygon for $ n=4 $ . Cannons shoot character 1. At any moment of time, no more than one cannon is shooting. When a 1 flies out of a cannon, it flies forward (in the direction of the shot) until it collides with a polygon border or another 1. After that, it takes the cell in which it was before the collision and remains there. Take a look at the examples for better understanding.

More formally:

- if a cannon stands in the row $ i $ , to the left of the first column, and shoots with a 1, then the 1 starts its flight from the cell ( $ i, 1 $ ) and ends in some cell ( $ i, j $ );
- if a cannon stands in the column $ j $ , above the first row, and shoots with a 1, then the 1 starts its flight from the cell ( $ 1, j $ ) and ends in some cell ( $ i,         j $ ).

For example, consider the following sequence of shots:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png) 1. Shoot the cannon in the row $ 2 $ . 2. Shoot the cannon in the row $ 2 $ . 3. Shoot the cannon in column $ 3 $ .

You have a report from the military training on your desk. This report is a square matrix with side length $ n $ consisting of 0 and 1. You wonder if the training actually happened. In other words, is there a sequence of shots such that, after the training, you get the given matrix?

Each cannon can make an arbitrary number of shots. Before the training, each cell of the polygon contains 0.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le       1000 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case starts with a line containing an integer $ n $ ( $ 1 \le n \le 50 $ ) — the size of the polygon.

This is followed by $ n $ lines of length $ n $ , consisting of 0 and 1 — the polygon matrix after the training.

The total area of the matrices in all test cases in one test does not exceed $ 10^5 $ .

## 输出格式

For each test case print:

- YES if there is a sequence of shots leading to a given matrix;
- NO if such a sequence does not exist.

The letters in the words YES and NO can be printed in any case.

## 说明/提示

The first test case was explained in the statement.

The answer to the second test case is NO, since a 1 in a cell ( $ 1, 1 $ ) flying out of any cannon would continue its flight further.

## 样例 #1

### 输入

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "White-Black Balanced Subtrees"
layout: "post"
diff: 普及/提高-
pid: CF1676G
tag: ['深度优先搜索 DFS', '树形 DP']
---

# White-Black Balanced Subtrees

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root is vertex $ 1 $ . There is also a string $ s $ denoting the color of each vertex: if $ s_i = \texttt{B} $ , then vertex $ i $ is black, and if $ s_i = \texttt{W} $ , then vertex $ i $ is white.

A subtree of the tree is called balanced if the number of white vertices equals the number of black vertices. Count the number of balanced subtrees.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. In this problem, all trees have root $ 1 $ .

The tree is specified by an array of parents $ a_2, \dots, a_n $ containing $ n-1 $ numbers: $ a_i $ is the parent of the vertex with the number $ i $ for all $ i = 2, \dots, n $ . The parent of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root.

The subtree of a vertex $ u $ is the set of all vertices that pass through $ u $ on a simple path to the root. For example, in the picture below, $ 7 $ is in the subtree of $ 3 $ because the simple path $ 7 \to 5 \to 3 \to 1 $ passes through $ 3 $ . Note that a vertex is included in its subtree, and the subtree of the root is the entire tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) The picture shows the tree for $ n=7 $ , $ a=[1,1,2,3,3,5] $ , and $ s=\texttt{WBBWWBW} $ . The subtree at the vertex $ 3 $ is balanced.

## 输入格式

The first line of input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 2 \le n \le 4000 $ ) — the number of vertices in the tree.

The second line of each test case contains $ n-1 $ integers $ a_2, \dots, a_n $ ( $ 1 \le a_i < i $ ) — the parents of the vertices $ 2, \dots, n $ .

The third line of each test case contains a string $ s $ of length $ n $ consisting of the characters $ \texttt{B} $ and $ \texttt{W} $ — the coloring of the tree.

It is guaranteed that the sum of the values $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of balanced subtrees.

## 说明/提示

The first test case is pictured in the statement. Only the subtrees at vertices $ 2 $ and $ 3 $ are balanced.

In the second test case, only the subtree at vertex $ 1 $ is balanced.

In the third test case, only the subtrees at vertices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are balanced.

## 样例 #1

### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW
```

### 输出

```
2
1
4
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
title: "Arrow Path"
layout: "post"
diff: 普及/提高-
pid: CF1948C
tag: ['搜索']
---

# Arrow Path

## 题目描述

有一个 $2$ 行 $n$ 列的网格，每个格子上有一个向左或向右的箭头（即 `<` 或 `>`）。

现在你从 $(1, 1)$ 开始移动，并遵循以下的移动方式：

- 首先，选择一个移动方向走 $1$ 格，可以是上、下、左、右任意方向，但你需要保证不会走出网格；
- 走完一步后，如果当前所在格为 `<`，则向左走 $1$ 格，否则向右走 $1$​ 格。注意，你也需要保证这一步不会走出网格。

请回答你能否到达 $(2, n)$。

## 输入格式

**本题目含多组数据。**

第一行，一个正整数 $t$，表示数据组数。

接下来每组数据包含三行：

- 第一行，一个正整数 $n$，表示网格列数；
- 第二行，一个长度为 $n$ 的，由 `<` 和 `>` 组成的字符串，表示网格第一行；
- 第三行，一个长度为 $n$ 的，由 `<` 和 `>` 组成的字符串，表示网格第二行。

## 输出格式

对于每组数据，如果能到达 $(2, n)$ 则输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^4, 2 \leq n \leq 2 \times 10^5$。

**保证 $n$ 是偶数，没有箭头指向网格外，$n$ 的总和不超过 $2 \times 10^5$。**

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
4
4
&gt;&gt;&lt;&lt;
&gt;&gt;&gt;&lt;
2
&gt;&lt;
&gt;&lt;
4
&gt;&gt;&gt;&lt;
&gt;&gt;&lt;&lt;
6
&gt;&gt;&lt;&lt;&gt;&lt;
&gt;&lt;&gt;&gt;&gt;&lt;
```

### 输出

```
YES
YES
NO
YES
```



---

---
title: "Permutation Game"
layout: "post"
diff: 普及/提高-
pid: CF1968D
tag: ['搜索', '贪心']
---

# Permutation Game

## 题目描述

Bodya and Sasha found a permutation $ p_1,\dots,p_n $ and an array $ a_1,\dots,a_n $ . They decided to play a well-known "Permutation game".

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

Both of them chose a starting position in the permutation.

The game lasts $ k $ turns. The players make moves simultaneously. On each turn, two things happen to each player:

- If the current position of the player is $ x $ , his score increases by $ a_x $ .
- Then the player either stays at his current position $ x $ or moves from $ x $ to $ p_x $ .

 The winner of the game is the player with the higher score after exactly $ k $ turns.Knowing Bodya's starting position $ P_B $ and Sasha's starting position $ P_S $ , determine who wins the game if both players are trying to win.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of testcases.

The first line of each testcase contains integers $ n $ , $ k $ , $ P_B $ , $ P_S $ ( $ 1\le P_B,P_S\le n\le 2\cdot 10^5 $ , $ 1\le k\le 10^9 $ ) — length of the permutation, duration of the game, starting positions respectively.

The next line contains $ n $ integers $ p_1,\dots,p_n $ ( $ 1 \le p_i \le n $ ) — elements of the permutation $ p $ .

The next line contains $ n $ integers $ a_1,\dots,a_n $ ( $ 1\le a_i\le 10^9 $ ) — elements of array $ a $ .

It is guaranteed that the sum of values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase output:

- "Bodya" if Bodya wins the game.
- "Sasha" if Sasha wins the game.
- "Draw" if the players have the same score.

## 说明/提示

Below you can find the explanation for the first testcase, where the game consists of $ k=2 $ turns.

 TurnBodya's positionBodya's scoreBodya's moveSasha's positionSasha's scoreSasha's movefirst $ 3 $  $ 0 + a_3 = 0 + 5 = 5 $ stays on the same position $ 2 $  $ 0 + a_2 = 0 + 2 = 2 $ moves to $ p_2=1 $ second $ 3 $  $ 5 + a_3 = 5 + 5 = 10 $ stays on the same position $ 1 $  $ 2 + a_1 = 2 + 7 = 9 $ stays on the same positionfinal results $ 3 $  $ 10 $  $ 1 $  $ 9 $ As we may see, Bodya's score is greater, so he wins the game. It can be shown that Bodya always can win this game.

## 样例 #1

### 输入

```
10
4 2 3 2
4 1 2 3
7 2 5 6
10 8 2 10
3 1 4 5 2 7 8 10 6 9
5 10 5 1 3 7 10 15 4 3
2 1000000000 1 2
1 2
4 4
8 10 4 1
5 1 4 3 2 8 6 7
1 1 2 1 2 100 101 102
5 1 2 5
1 2 4 5 3
4 6 9 4 2
4 2 3 1
4 1 3 2
6 8 5 3
6 9 5 4
6 1 3 5 2 4
6 9 8 9 5 10
4 8 4 2
2 3 4 1
5 2 8 7
4 2 3 1
4 1 3 2
6 8 5 3
2 1000000000 1 2
1 2
1000000000 2
```

### 输出

```
Bodya
Sasha
Draw
Draw
Bodya
Sasha
Sasha
Sasha
Sasha
Bodya
```



---

---
title: "Sakurako's Hobby"
layout: "post"
diff: 普及/提高-
pid: CF2008D
tag: ['深度优先搜索 DFS', '图遍历']
---

# Sakurako's Hobby

## 题目描述

对于一个给定的排列 $ p $，Sakurako 称整数 $ j $ 从整数 $ i $ 可达，意思是可以通过若干次操作将 $ i $ 改为 $ p_i $，最终使 $ i $ 等于 $ j $。

举个例子，如果 $ p=[3,5,6,1,2,4] $，那么 $ 4 $ 是从 $ 1 $ 可达的，因为变化过程可以是：$ i=1 \rightarrow i=p_1=3 \rightarrow i=p_3=6 \rightarrow i=p_6=4 $。这样 $ i $ 就变成了 $ 4 $，因此 $ 4 $ 是从 $ 1 $ 可达的。

在这个排列中，每个数字都有两种颜色：黑色或白色。

Sakurako 定义了一个函数 $ F(i) $，表示从 $ i $ 可达的黑色整数的总数。

她对每一个 $ 1\le i\le n $ 的 $ F(i) $ 都很感兴趣，但计算所有值太过复杂，因此她希望你能帮助她解决这个问题。

一个长度为 $ n $ 的排列是一个由 $ 1 $ 到 $ n $ 这 $ n $ 个不同整数构成的数组。例如，$ [2,3,1,5,4] $ 是一个排列，而 $ [1,2,2] $ 却不是（因为数字 $ 2 $ 出现了两次），同样地，$ [1,3,4] $ 也不是（$ n=3 $，但数组中包含 $ 4 $）。

## 输入格式

第一行输入一个整数 $ t $（$ 1\le t\le 10^4 $），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $ n $（$ 1\le n\le 2\cdot 10^5 $），表示数组中元素的数量。

接下来的每一行包含 $ n $ 个整数 $ p_1, p_2, \dots, p_n $（$ 1\le p_i\le n $），表示排列的具体内容。

随后的一行包含一个由字符 '0' 和 '1' 组成的长度为 $ n $ 的字符串 $ s $。如果 $ s_i=0 $，则表示数字 $ p_i $ 是黑色；如果 $ s_i=1 $，则表示数字 $ p_i $ 是白色。

保证所有测试用例之中 $ n $ 的总和不超过 $ 2\cdot 10^5 $。

## 输出格式

对于每个测试用例，输出 $ n $ 个整数 $ F(1), F(2), \dots, F(n) $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
1
1
0
5
1 2 4 5 3
10101
5
5 4 1 3 2
10011
6
3 5 6 1 2 4
010000
6
1 2 3 4 5 6
100110
```

### 输出

```
1 
0 1 1 1 1 
2 2 2 2 2 
4 1 4 4 1 4 
0 1 1 0 0 1
```



---

---
title: "Add Zeros"
layout: "post"
diff: 普及/提高-
pid: CF2027C
tag: ['动态规划 DP', '数学', '记忆化搜索']
---

# Add Zeros

## 题目描述

You're given an array $ a $ initially containing $ n $ integers. In one operation, you must do the following:

- Choose a position $ i $ such that $ 1 < i \le |a| $ and $ a_i = |a| + 1 - i $ , where $ |a| $ is the current size of the array.
- Append $ i - 1 $ zeros onto the end of $ a $ .

After performing this operation as many times as you want, what is the maximum possible length of the array $ a $ ?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^{12} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible length of $ a $ after performing some sequence of operations.

## 说明/提示

In the first test case, we can first choose $ i = 4 $ , since $ a_4 = 5 + 1 - 4 = 2 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0] $ . We can then choose $ i = 3 $ since $ a_3 = 8 + 1 - 3 = 6 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0, 0, 0] $ , which has a length of $ 10 $ . It can be shown that no sequence of operations will make the final array longer.

In the second test case, we can choose $ i=2 $ , then $ i=3 $ , then $ i=4 $ . The final array will be $ [5, 4, 4, 5, 1, 0, 0, 0, 0, 0, 0] $ , with a length of $ 11 $ .

## 样例 #1

### 输入

```
4
5
2 4 6 2 5
5
5 4 4 5 1
4
6 8 2 3
1
1
```

### 输出

```
10
11
10
1
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
title: "Beautiful IP Addresses"
layout: "post"
diff: 普及/提高-
pid: CF292C
tag: ['搜索']
---

# Beautiful IP Addresses

## 题目描述

The problem uses a simplified TCP/IP address model, please read the statement carefully.

An IP address is a 32-bit integer, represented as a group of four decimal 8-bit integers (without leading zeroes), separated by commas. For example, record 0.255.1.123 shows a correct IP address and records 0.256.1.123 and 0.255.1.01 do not. In the given problem an arbitrary group of four 8-bit integers is a correct IP address.

Our hero Polycarpus still works as a system administrator in some large corporation. He likes beautiful IP addresses. To check if some IP address is beautiful, he should do the following:

1. write out in a line four 8-bit numbers of the IP address, without the commas;
2. check if the resulting string is a palindrome.

Let us remind you that a palindrome is a string that reads the same from right to left and from left to right.

For example, IP addresses 12.102.20.121 and 0.3.14.130 are beautiful (as strings "1210220121" and "0314130" are palindromes), and IP addresses 1.20.20.1 and 100.4.4.1 are not.

Polycarpus wants to find all beautiful IP addresses that have the given set of digits. Each digit from the set must occur in the IP address at least once. IP address must not contain any other digits. Help him to cope with this difficult task.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10) $ — the number of digits in the set. The second line contains the set of integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=9) $ . It is guaranteed that all digits in the set are distinct.

## 输出格式

In the first line print a single integer $ k $ — the number of beautiful IP addresses that contain the given set of digits. In the following $ k $ lines print the IP addresses, one per line in the arbitrary order.

## 样例 #1

### 输入

```
6
0 1 2 9 8 7

```

### 输出

```
6
78.190.209.187
79.180.208.197
87.190.209.178
89.170.207.198
97.180.208.179
98.170.207.189

```

## 样例 #2

### 输入

```
1
4

```

### 输出

```
16
4.4.4.4
4.4.4.44
4.4.44.4
4.4.44.44
4.44.4.4
4.44.4.44
4.44.44.4
4.44.44.44
44.4.4.4
44.4.4.44
44.4.44.4
44.4.44.44
44.44.4.4
44.44.4.44
44.44.44.4
44.44.44.44

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
title: "Maze"
layout: "post"
diff: 普及/提高-
pid: CF377A
tag: ['深度优先搜索 DFS', '栈']
---

# Maze

## 题目描述

Pavel loves grid mazes. A grid maze is an $ n×m $ rectangle maze where each cell is either empty, or is a wall. You can go from one cell to another only if both cells are empty and have a common side.

Pavel drew a grid maze with all empty cells forming a connected area. That is, you can go from any empty cell to any other one. Pavel doesn't like it when his maze has too little walls. He wants to turn exactly $ k $ empty cells into walls so that all the remaining cells still formed a connected area. Help him.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m<=500 $ , $ 0<=k&lt;s $ ), where $ n $ and $ m $ are the maze's height and width, correspondingly, $ k $ is the number of walls Pavel wants to add and letter $ s $ represents the number of empty cells in the original maze.

Each of the next $ n $ lines contains $ m $ characters. They describe the original maze. If a character on a line equals ".", then the corresponding cell is empty and if the character equals "\#", then the cell is a wall.

## 输出格式

Print $ n $ lines containing $ m $ characters each: the new maze that fits Pavel's requirements. Mark the empty cells that you transformed into walls as "X", the other cells must be left without changes (that is, "." and "\#").

It is guaranteed that a solution exists. If there are multiple solutions you can output any of them.

## 样例 #1

### 输入

```
3 4 2
#..#
..#.
#...

```

### 输出

```
#.X#
X.#.
#...

```

## 样例 #2

### 输入

```
5 4 5
#...
#.#.
.#..
...#
.#.#

```

### 输出

```
#XXX
#X#.
X#..
...#
.#.#

```



---

---
title: "Mysterious Present"
layout: "post"
diff: 普及/提高-
pid: CF4D
tag: ['动态规划 DP', '搜索', '递归']
---

# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 输入格式

The first line contains integers $ n $ , $ w $ , $ h $ ( $ 1<=n<=5000 $ , $ 1<=w,h<=10^{6} $ ) — amount of envelopes Peter has, the card width and height respectively. Then there follow $ n $ lines, each of them contains two integer numbers $ w_{i} $ and $ h_{i} $ — width and height of the $ i $ -th envelope ( $ 1<=w_{i},h_{i}<=10^{6} $ ).

## 输出格式

In the first line print the maximum chain size. In the second line print the numbers of the envelopes (separated by space), forming the required chain, starting with the number of the smallest envelope. Remember, please, that the card should fit into the smallest envelope. If the chain of maximum size is not unique, print any of the answers.

If the card does not fit into any of the envelopes, print number $ 0 $ in the single line.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2

```

### 输出

```
1
1 

```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8

```

### 输出

```
3
1 3 2 

```



---

---
title: "Smallest number"
layout: "post"
diff: 普及/提高-
pid: CF55B
tag: ['搜索', '枚举', '深度优先搜索 DFS']
---

# Smallest number

## 题目描述

Recently, Vladimir got bad mark in algebra again. To avoid such unpleasant events in future he decided to train his arithmetic skills. He wrote four integer numbers $ a $ , $ b $ , $ c $ , $ d $ on the blackboard. During each of the next three minutes he took two numbers from the blackboard (not necessarily adjacent) and replaced them with their sum or their product. In the end he got one number. Unfortunately, due to the awful memory he forgot that number, but he remembers four original numbers, sequence of the operations and his surprise because of the very small result. Help Vladimir remember the forgotten number: find the smallest number that can be obtained from the original numbers by the given sequence of operations.

## 输入格式

First line contains four integers separated by space: $ 0<=a,b,c,d<=1000 $ — the original numbers. Second line contains three signs ('+' or '\*' each) separated by space — the sequence of the operations in the order of performing. ('+' stands for addition, '\*' — multiplication)

## 输出格式

Output one integer number — the minimal result which can be obtained.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 样例 #1

### 输入

```
1 1 1 1
+ + *

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2 2 2 2
* * +

```

### 输出

```
8

```

## 样例 #3

### 输入

```
1 2 3 4
* + +

```

### 输出

```
9

```



---

---
title: "Phillip and Trains"
layout: "post"
diff: 普及/提高-
pid: CF585B
tag: ['搜索', '深度优先搜索 DFS', '剪枝']
---

# Phillip and Trains

## 题目描述

The mobile application store has a new game called "Subway Roller".

The protagonist of the game Philip is located in one end of the tunnel and wants to get out of the other one. The tunnel is a rectangular field consisting of three rows and $ n $ columns. At the beginning of the game the hero is in some cell of the leftmost column. Some number of trains rides towards the hero. Each train consists of two or more neighbouring cells in some row of the field.

All trains are moving from right to left at a speed of two cells per second, and the hero runs from left to right at the speed of one cell per second. For simplicity, the game is implemented so that the hero and the trains move in turns. First, the hero moves one cell to the right, then one square up or down, or stays idle. Then all the trains move twice simultaneously one cell to the left. Thus, in one move, Philip definitely makes a move to the right and can move up or down. If at any point, Philip is in the same cell with a train, he loses. If the train reaches the left column, it continues to move as before, leaving the tunnel.

Your task is to answer the question whether there is a sequence of movements of Philip, such that he would be able to get to the rightmost column.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF585B/309f950d64c5a7d55f4952aae670b86363abc76b.png)

## 输入格式

Each test contains from one to ten sets of the input data. The first line of the test contains a single integer $ t $ ( $ 1<=t<=10 $ for pretests and tests or $ t=1 $ for hacks; see the Notes section for details) — the number of sets.

Then follows the description of $ t $ sets of the input data.

The first line of the description of each set contains two integers $ n,k $ ( $ 2<=n<=100,1<=k<=26 $ ) — the number of columns on the field and the number of trains. Each of the following three lines contains the sequence of $ n $ character, representing the row of the field where the game is on. Philip's initial position is marked as 's', he is in the leftmost column. Each of the $ k $ trains is marked by some sequence of identical uppercase letters of the English alphabet, located in one line. Distinct trains are represented by distinct letters. Character '.' represents an empty cell, that is, the cell that doesn't contain either Philip or the trains.

## 输出格式

For each set of the input data print on a single line word YES, if it is possible to win the game and word NO otherwise.

## 说明/提示

In the first set of the input of the first sample Philip must first go forward and go down to the third row of the field, then go only forward, then go forward and climb to the second row, go forward again and go up to the first row. After that way no train blocks Philip's path, so he can go straight to the end of the tunnel.

Note that in this problem the challenges are restricted to tests that contain only one testset.

## 样例 #1

### 输入

```
2
16 4
...AAAAA........
s.BBB......CCCCC
........DDDDD...
16 4
...AAAAA........
s.BBB....CCCCC..
.......DDDDD....

```

### 输出

```
YES
NO

```

## 样例 #2

### 输入

```
2
10 4
s.ZZ......
.....AAABB
.YYYYYY...
10 4
s.ZZ......
....AAAABB
.YYYYYY...

```

### 输出

```
YES
NO

```



---

---
title: "New Reform"
layout: "post"
diff: 普及/提高-
pid: CF659E
tag: ['递归', '深度优先搜索 DFS']
---

# New Reform

## 题目描述

有 $n$ 个城市，$m$ 条双向道路，没有一个城市存在自己到自己的道路，两个不同的城市间，最多有一条道路，也不能保证能从一个城市到达任意一个其他城市。

现在需要对每一条道路定向，使之成为单向道路，当然需要尽可能少地产生孤立的城市。当其他所有城市都不能到达某个城市，则称这个城市为孤立城市。要求出最少的孤立城市的个数。

## 输入格式

第一行，两个整数，$n$ 和 $m$。

接下来 $m$ 行，每行两个整数 $x_i$ 和 $y_i$，表示一条道路连接城市 $x_i$ 和城市 $y_i$ 的双向道路。

## 输出格式

一行，一个整数，表示最少的孤立城市的个数。

### 数据规模与约定
$2\le n\le 100000$，$1\le m\le 100000$。

对于每一个合法的 $x_i$ 和 $y_i$，都有 $1\le x_i,y_i\le n$，且 $x_i \not\ =y_i$。

## 样例 #1

### 输入

```
4 3
2 1
1 3
4 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 5
2 1
1 3
2 3
2 5
4 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 5
1 2
2 3
4 5
4 6
5 6

```

### 输出

```
1

```



---

---
title: "Almost Arithmetic Progression"
layout: "post"
diff: 普及/提高-
pid: CF978D
tag: ['搜索', '枚举', '剪枝']
---

# Almost Arithmetic Progression

## 题目描述

Polycarp 喜欢等差数列，对于一个数列 $ [a_1,a_2,a_3,\dots,a_n] $，如果对于每个 $ i\,(1\le i < n) $，$ a_{i+1}-a_i $ 的值均相同，那么这个数列就是一个等差数列。例如，$ [42] $ ，$ [5,5,5] $ ，$ [2,11,20,29] $ 和 $ [3,2,1,0] $ 是等差数列，但是 $ [1,0,1] $，$ [1,3,9] $ 和 $ [2,3,1] $ 不是。

根据定义，任何长度为 $ 1 $ 或 $ 2 $ 的数列都是等差数列。

Polycarp 找到了一个只包含正整数的数列 $ [b_1,b_2,b_3,\dots,b_n] $ 。他只想最多将每个元素改变一次。换句话说，对于每个元素，有三种选项：自增 $ 1 $，自减 $ 1 $ 或者不变。

你需要找到对 $ b $ 中元素操作（每个只能操作一次）的最小次数，使 $ b $ 变成一个等差数列。

操作完成后的数列可以含有 $ 0 $ 。

## 输入格式

第 $ 1 $ 行有 $ 1 $ 个整数 $ n\,(1\le n\le 100\,000) $ ，表示 $ b $ 中元素的个数。

第 $ 2 $ 行包含一个数列 $ b_1,b_2,b_3,\dots,b_n \,(1\le b_i \le 10^9)$。

## 输出格式

如果无法使用上述的操作将数列变为等差数列，输出 $ -1 $ 。在另一种情况下，输出一个非负整数，表示要将 $ b $ 变为等差数列所需要改变的元素的个数。唯一允许的操作是元素的自增 $/$ 减（不能够对一个元素操作两次）。

## 说明/提示

在样例 $ 1 $ 中，Polycarp 应该将第 $ 1 $ 个元素加 $ 1 $ ，将第 $ 2 $ 个元素加 $ 1 $ ，将第 $ 3 $ 个元素加 $ 1 $ ，并且不改变第 $ 4 $ 个元素。所以，Polycarp 操作之后的数列为 $ [25,20,15,10] $ 。

在样例 $ 2 $ 中，Polycarp 不应进行操作，因为他的数列已经是等差数列了。

在样例 $ 3 $ 中，不可能通过上述的操作将数列变为等差数列。

在样例 $ 4 $ 中，Polycarp 应该只将第 $ 1 $ 个元素加 $ 1 $ 。操作之后的数列为 $ [0,3,6,9,12] $ 。

## 样例 #1

### 输入

```
4
24 21 14 10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
500 500

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
14 5 1

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
5
1 3 6 9 12

```

### 输出

```
1

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

