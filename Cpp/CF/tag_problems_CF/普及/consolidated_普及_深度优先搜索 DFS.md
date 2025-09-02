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

