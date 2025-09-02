---
title: "[ICPC 2024 Xi'an I] Yet Another Maximum Matching Counting Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10563
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Yet Another Maximum Matching Counting Problem
## 题目描述

There is a two-dimensional plane.
    
    
    
You have a set of points $\{(x_i,y_i)\}$ that satisfies $1\le x_i\le n, 1\le y_i\le m$ (Both $x_i$ and $y_i$ are integers), and there are no two points with the same coordinates.
    
    
    
If two points have the same horizontal or vertical coordinates, we will connect an edge between these two points. This forms a graph.
    
    
    
You need to find the sum of the maximum number of matches in the graphs formed by all possible $2^{nm}-1$ non empty sets, and output the result modulo $998244353$.
    
    
    
Here, the maximum number of matches in a graph is defined as: selecting the most edges so that there are no common vertices between any two edges.
## 输入格式


There are multiple testcases in this problem.
    
    
    
The first line contains an integer $T(1\le T\le 100)$, which represents the number of testcases.
    
    
    
Each of the testcases contains two integers $n,m(1\leq n,m\leq 500)$.
## 输出格式

 
For each of the testcases, print an integer representing the result modulo $998244353$.
    
## 样例

### 样例输入 #1
```
10
1 1
1 2
2 2
4 4
3 3
5 5
1 8
20 20
100 100
500 500
```
### 样例输出 #1
```
0
1
10
241456
964
200419152
448
985051144
370696900
357517517
```


---

---
title: "[ICPC 2013 WF] Map Tiles"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10621
tag: ['2013', 'O2优化', 'ICPC']
---
# [ICPC 2013 WF] Map Tiles
## 题目描述

Publishing maps is not an easy task. First you need some appropriate transformation to display the earth’s spherical shape in a two-dimensional plane. Then another issue arises – most high-quality maps are too large to be printed on a single page of paper. To cope with that, map publishers often split maps into several rectangular tiles, and print each tile on one page. In this problem, you will examine this “tiling” process.

The International Cartographic Publishing Company (ICPC) needs to cut their printing costs by minimizing the number of tiles used for their maps. Even with a fixed tile size (determined by the page size) and map scale, you can still optimize the situation by adjusting the tile grid.
The left side of Figure G.1 shows 14 map tiles covering a region. The right side shows how you can cover the same region with only 10 tiles, without changing the tile sizes or orientation.

![](https://cdn.luogu.com.cn/upload/image_hosting/a9a9dj7t.png)

Your task is to help the ICPC find the minimum number of tiles needed to cover a given region. For simplicity, the region will be given as a closed polygon that does not intersect itself. 

Note that the tiles must be part of a rectangular grid aligned with the $x$-axis and $y$-axis. That is, they touch each other only with their whole sides and cannot be rotated. Also note that although all input coordinates are integers, tiles may be located at non-integer coordinates.

The polygon may touch the edges of marginal lines (as in Sample Input 2). However, to avoid floatingpoint issues, you may assume the optimal answer will not change even if the polygon is allowed to go outside the map tiles by a distance of $10^{-6}$.
## 输入格式

The input consists of a single test case. The first line of a test case contains three integers: $n, x_s$, and $y_s$. The number of polygon vertices is $n (3 \leq n \leq 50)$, and $x_s$ and $y_s (1 \leq x_s, y_s \leq 100)$ are the dimensions of each tile. Each of the next $n$ lines contains two integers $x$ and $y (0 \leq x \leq 10x_s, 0 \leq y \leq 10y_s)$, specifying the vertices of the polygon representing the region (in either clockwise or counter-clockwise order).
## 输出格式

Display the minimal number of tiles necessary to cover the whole interior of the polygon.
## 样例

### 样例输入 #1
```
12 9 9
1 8
1 16
6 16
9 29
19 31
23 24
30 23
29 18
20 12
22 8
14 0
14 8
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
4 5 7
10 10
15 10
15 17
10 17
```
### 样例输出 #2
```
1
```
## 题目翻译

**【题目描述】**

出版地图并非易事。首先，你需要进行适当的变换，以在二维平面上显示地球的球形形状。接着出现另一个问题——大多数高质量的地图都太大，无法印在一页纸上。为了解决这个问题，地图出版商通常将地图分割成若干个矩形块，并在每页上打印一个块。在这个问题中，你将研究这种“瓦片化”过程。

国际制图出版公司（ICPC）需要通过最小化用于其地图的瓦片数量来削减印刷成本。即使固定了瓦片大小（由页面大小决定）和地图比例，你仍然可以通过调整瓦片网格来优化情况。图 G.1 的左侧显示了覆盖一个区域的 14 个地图瓦片。右侧显示了如何在不改变瓦片大小或方向的情况下，仅用 10 个瓦片覆盖相同的区域。

![](https://cdn.luogu.com.cn/upload/image_hosting/a9a9dj7t.png)

你的任务是帮助 ICPC 找出覆盖给定区域所需的最少瓦片数量。为简化起见，该区域将给出为不自相交的闭合多边形。

请注意，瓦片必须是与 $x$ 轴和 $y$ 轴对齐的矩形网格的一部分。也就是说，它们只能用完整的边接触，不能旋转。另外，尽管所有输入坐标都是整数，瓦片的位置可以是非整数坐标。

多边形可能接触边界线的边缘（如样例输入 2 中所示）。但是，为避免浮点数问题，可以假设即使允许多边形超出地图瓦片的距离为 $10^{-6}$，最优答案也不会改变。

**【输入格式】**

输入包含一个测试用例。测试用例的第一行包含三个整数：$n, x_s$ 和 $y_s$。多边形的顶点数为 $n (3 \leq n \leq 50)$，$x_s$ 和 $y_s (1 \leq x_s, y_s \leq 100)$ 是每个瓦片的尺寸。接下来的 $n$ 行中的每一行包含两个整数 $x$ 和 $y (0 \leq x \leq 10x_s, 0 \leq y \leq 10y_s)$，指定表示区域的多边形的顶点（按顺时针或逆时针顺序）。

**【输出格式】**

输出覆盖多边形的整个内部所需的最少瓦片数量。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[EC Final 2020] Tube Master III"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10820
tag: ['2020', 'O2优化', 'ICPC']
---
# [EC Final 2020] Tube Master III
## 题目描述

Prof. Pang is playing ``Tube Master``.

The game field is divided into $n \times m$ cells by $(n + 1) \times m$ horizontal tubes and $n \times (m + 1)$ vertical tubes. The product $n m$ is an $\textbf{even}$ number. There are $(n + 1) (m + 1)$ crossings of the tubes. The 2D coordinate of the crossings are $(i, j)$ ($1\le i\le n+1$, $1\le j\le m+1$). We name the crossing with coordinate $(i, j)$ as crossing $(i, j)$. We name the cell whose corners are crossings $(i, j), (i+1, j), (i, j+1), (i+1, j+1)$ as cell $(i, j)$ for all $1\le i\le n$, $1\le j\le m$. Additionally, each cell $(i, j)$ contains an integer ${count}_{i, j}$.

![](https://cdn.luogu.com.cn/upload/image_hosting/wfw0es17.png)

The above figure shows a game field with $n = 3, m = 2$ (the third sample).

Prof. Pang decides to use some of the tubes. However, the game poses several weird restrictions.

- Either $0$ or $2$ tubes connected to each crossing are used.
- There are exactly ${count}_{i, j}$ turning points adjacent to cell $(i, j)$. A turning point is a crossing such that exactly $1$ horizontal tube and exactly $1$ vertical tube connected to it are used. A turning point $(x, y)$ is adjacent to cell $(i, j)$ if crossing $(x, y)$ is a corner of cell $(i, j)$. 

It costs $a_{i, j}$ to use the tube connecting crossings $(i, j)$ and $(i, j+1)$. It costs $b_{i, j}$ to use the tube connecting crossings $(i, j)$ and $(i+1, j)$. Please help Prof. Pang to find out which tubes he should use such that the restrictions are satisfied and the total cost is minimized.
## 输入格式

The first line contains a single positive integer $T$ denoting the number of test cases.

For each test case, the first line contains two integers $n$, $m$ ($1 \leq n, m \leq 100$) separated by a single space.

The $i$-th of the following $n$ lines contains $m$ integers ${count}_{i, 1}, {count}_{i, 2}, \dots, {count}_{i, m}$ ($0 \leq {count}_{i, j} \leq 4$) separated by single spaces.

The $i$-th of the following $n+1$ lines contains $m$ integers ${a}_{i, 1}, {a}_{i, 2}, \dots, {a}_{i, m}$ ($1 \leq {a}_{i, j} \leq 10^9$) separated by single spaces.

The $i$-th of the following $n$ lines contains $m+1$ integers ${b}_{i, 1}, \mathit{b}_{i, 2}, \dots, {b}_{i, m+1}$ ($1 \leq {b}_{i, j} \leq 10^9$) separated by single spaces.

It is guaranteed that $nm$ is an $\textbf{even}$ number and that the total sum of $nm$ over all test cases does not exceed $10^4$.
## 输出格式

For each test case, output an integer that denotes the minimum cost.

If there is no valid configuration, output $\texttt{-1}$ instead.
## 样例

### 样例输入 #1
```
4
2 3
4 3 2
2 3 4
2 1 1
2 1 2
1 2 1
1 2 1 2
1 1 1 2
2 2
2 1
2 1
1 2
2 2
1 2
1 2 1
2 1 1
3 2
1 2
3 3
3 2
1 1
1 1
2 2
1 1
1 1 1
1 1 1
2 2 2
2 2
1 2
3 4
5 6
7 8
9 10
11 12 13
14 15 16
```
### 样例输出 #1
```
13
8
11
-1
```


---

---
title: "[EC Final 2020] Circle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10825
tag: ['2020', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2020] Circle
## 题目描述

Prof. Pang does research on the minimum covering circle problem. He does not like random algorithms so he decides to find an efficient deterministic one. He starts with the classical idea of binary search. In each iteration of the binary search, the following problem needs to be solved:

Given the radius $r$ of a circle and a convex hull $C$, let $S$ be defined as 

$$S=\{p\ |\  \text{the circle with center $p$ and radius $r$ covers $C$}\}.$$ 

Find the area of $S$.
## 输入格式

The first line contains a single positive integer $T$ denoting the number of test cases.

For each test case, the first line contains two integers $n$ and $r$ ($1\le n\le 1000$, $1\le r\le 30000$) separated by a single space denoting the number of vertices of the convex hull and the radius. If $n=1$, the convex hull contains only $1$ point. If $n=2$, the convex hull is a line segment. 

Each of the following $n$ lines contains two integers $x, y$ ($-10000\le x, y\le 10000$) separated by a single space denoting a vertex at $(x, y)$. It is guaranteed that no two vertices coincide and no three vertices are collinear. Vertices are listed in counter-clockwise order.

It is guaranteed that the sum of $n$ over all test cases does not exceed $200000$.
## 输出格式

Output a single decimal indicating the answer. Your answer will be considered correct if the absolute or relative error is no more than $10^{-6}$.
## 样例

### 样例输入 #1
```
3
4 1
0 0
1 0
1 1
0 1
4 1
0 0
1 1
0 2
-1 1
4 100
0 0
1 0
1 1
0 1
```
### 样例输出 #1
```
0.315146743628
0
31016.928202570849
```


---

---
title: "[EC Final 2020] Fillomino"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10828
tag: ['2020', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2020] Fillomino
## 题目描述

Prof. Pang is the king of Pangland. Pangland is a board with size $n\times m$. The cell at the $i$-th row and the $j$-th column is denoted as cell $(i, j)$ for all $1\le i\le n, 1\le j\le m$. If two cells share an edge, they are connected. The board is $\textbf{toroidal}$, that is, cell $(1,y)$ is also connected to $(n,y)$ and $(x,1)$ is also connected to $(x,m)$ for all $1\le x\le n, 1\le y\le m$.

Prof. Pang has three sons. We call them the first son, the second son and the third son. Each of them lives in a cell in Pangland. The $i$-th son lives in cell $(x_i, y_i)$. No two sons live in the same cell. Prof. Pang wants to distribute the cells in Pangland to his sons such that

- Each cell belongs to exactly one son.
- There are $cnt_i$ cells that belong to the $i$-th son for all $1\le i\le 3$.
- The cells that belong to the $i$-th son are connected for all $1\le i\le 3$.
- The cell that the $i$-th son lives in must belong to the $i$-th son himself for all $1\le i\le 3$.

Please help Prof. Pang to find a solution if possible.
## 输入格式

The first line contains a single integer $T$ ($1\leq T\leq 10^5$) denoting the number of test cases.

For each test case, the first line contains two integers $n, m$ ($3\leq n,m \leq 500$) separated by a single space.

The next line contains three positive integers $cnt_1,cnt_2,cnt_3$ ($cnt_1+cnt_2+cnt_3 = n m$) separated by single spaces.

The $i$-th line of the next $3$ lines contains two integers $x_i, y_i$ ($1\le x_i\le n, 1\le y_i\le m$) separated by a single space.

It is guaranteed that $(x_1,y_1)$, $(x_2, y_2)$, $(x_3, y_3)$ are distinct.

It is guaranteed that the sum of $nm$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, if there is no solution, output $\texttt{-1}$ in one line. Otherwise, output $n$ lines. Each line should contain $m$ characters. The $j$-th character in the $i$-th line should be $\texttt{A}$ if cell $(i, j)$ belongs to the first son, $\texttt{B}$ if cell $(i, j)$ belongs to the second son and $\texttt{C}$ if cell $(i, j)$ belongs to the third son. Cell $(x_i, y_i)$ must belong to the $i$-th son for all $1\le i\le 3$. The cells that belong to the $i$-th son must be connected for all $1\le i\le 3$.
## 样例

### 样例输入 #1
```
2
3 3
1 3 5
1 1
2 2
3 3
4 4
5 5 6
2 2
2 3
3 3
```
### 样例输出 #1
```
ABB
CBC
CCC
BABB
BABC
CACC
AACC
```


---

---
title: "[NERC2024] Cactus without Bridges"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12094
tag: ['2024', 'Special Judge', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Cactus without Bridges
## 题目描述

Caroline asked you for help in solving a cactus problem one year ago. During the last year, she researched extensively about cactuses. Today, she is the one presenting the problem.

You are given a $\textbf{cactus without bridges}$ and also the length of each odd simple cycle is greater than or equal to the number of odd simple cycles in cactus. Your task is to answer whether it's possible to label the cactus edges with positive integers such that the following conditions are satisfied:

- Let's define the maximum label with $t$. All the integers $1$, $2$, $\ldots$, $t$ are used in labeling (note that you do not need to minimize or maximize the value of $t$);
- For each vertex $v$ of the given cactus, the labels of edges incident to the vertex $v$ should be different and should form an interval of consecutive integers.

An edge in the graph is called $\textit{bridge}$ if the deletion of that edge increases the number of connected components of the graph. A $\textit{cactus}$ is a connected undirected graph in which every edge lies on at most one simple cycle. Intuitively, a cactus is a generalization of a tree where some cycles are allowed. Multiedges (multiple edges between a pair of vertices) and loops (edges that connect a vertex to itself) are not allowed in a cactus.
## 输入格式

The first line contains two integers $n$ and $m$ ($3 \le n \le 10^5$, $n \le m \le \lfloor \frac{3(n - 1)}{2} \rfloor$) --- the number of vertices and edges in the cactus. Each of the next $m$ lines contains two integers $u$ and $v$ ($1 \le u, v \le n$; $u \ne v$) --- the edges of the cactus. The given cactus satisfies all constraints from the problem statement.
## 输出格式

If finding the labeling satisfying the problem's conditions is impossible, output the single line with the word $\tt{NO}$.
Otherwise, in the first line output the single word $\tt{YES}$. In the second line output an integer $t$ ($1 \leq t \leq m$) --- the number of different labels. In the third line output should contain $m$ integers $c_i$ ($1 \leq i \leq m$, $1 \leq c_i \leq t$) --- the labels of the edges.
## 样例

### 样例输入 #1
```
5 5
1 2
2 3
3 4
4 5
5 1
```
### 样例输出 #1
```
NO
```
### 样例输入 #2
```
8 10
1 2
2 3
1 3
1 4
1 5
4 5
5 6
6 7
7 8
8 5
```
### 样例输出 #2
```
YES
4
1 2 3 2 4 3 1 2 3 2
```


---

---
title: "[NERC2024] Hunting Hoglins in Hogwarts"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12099
tag: ['2024', '交互题', 'Special Judge', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Hunting Hoglins in Hogwarts
## 题目描述

This is an interactive problem.

Harry and Hermione are trying to hunt down $\emph{hoglins}$ which are haunting Hogwarts. There is a long hallway in Hogwarts, consisting of $n$ individual $\emph{cells}$, numbered from $1$ to $n$ from the left to the right.

Hermione can cast a spell that would $\emph{block}$ any cell of the hallway of her choosing. After the spell is cast, the blocked cell will remain blocked while she casts other spells.

Hoglins are simple creatures; all they do is randomly move around and bump into stuff. To be more precise, every hoglin has a range which it considers to be $\emph{accessible}$. Initially, when the hoglin appears, it is a range from the cell $1$ to the cell $n$.

Initially, a single hoglin appears in a cell of the hallway chosen uniformly at random. Then, until this hoglin is caught, the following happens on every $\emph{round}$ of the hunt:

- Hermione can cast a spell to block any single cell of her choosing, or do nothing.
- If the cell she is trying to block is the cell with a hoglin in it, the hoglin is caught. After that, all the blocked cells become free again, and, if there are more hoglins to be caught, a new hoglin immediately appears in a random location, and the hunt begins again.
- Otherwise, the hoglin chooses a cell uniformly at random from its accessible range and tries to move to that cell, moving one cell at a time towards a chosen cell. Regardless of the distance, all the steps of the movement, as described below, happen in the same round.
- If the chosen cell is to the right of the hoglin, it moves to the right; if the chosen cell is to the left of the hoglin, it moves to the left. If the chosen cell is the same as where the hoglin is now, it does nothing.
- If at any point during the movement towards the chosen cell a hoglin is trying to move to the right or to the left from an unblocked cell at position $i$ to the neighbouring blocked cell at position $i \pm 1$, the hoglin updates the right or left boundary of its accessible range correspondingly to be $i$.
- If on the way to the chosen cell, the hoglin tries to move to a blocked cell, Harry and Hermione hear a loud sound, as the hoglin $\emph{bumps}$ into the blocked cell. In this case, the hoglin returns to the position it has originally started from at the beginning of this round. 
- Otherwise, if the hoglin does not bump into any blocked cells on its way, it does not change its accessible range and stays at the new position. In that case, Harry and Hermione hear nothing.

To free Hogwarts from hoglins, Harry and Hermione should catch $k$ of them, but they don't have much time. They can only afford to hunt hoglins for at most $200\,000$ rounds. Please help them find an efficient strategy to do that.

**Interaction Protocol**

First, the testing system will write two integers $n$ and $k$ ($1 \le n \le 10^{18}; 1 \le k \le 800)$ --- the number of cells in Hogwarts' hallway and the number of hoglins that should be caught. Then the catching process begins.

The following interaction proceeds in rounds as described in the problem statement.

At the start of each round, your program should output Hermione's action --- an integer $p$ ($0 \le p \le n$) representing the position of the cell Hermione is going to block. If $p = 0$ or the cell at position $p$ is already blocked, she does nothing in this round.

Then, if the current position of the hoglin is at the newly blocked cell $p$, the hoglin is caught; the testing system outputs $\texttt{2}$, all the blocked cells become free, and interaction rounds start again. In case you caught the $k$-th hoglin, the testing system outputs $\texttt{3}$ instead of $\texttt{2}$, and your program should immediately stop execution.

Otherwise, the hoglin attempts to move according to the rules described in the problem statement. If in the process it bumps into any blocked cell, the testing system outputs $\texttt{1}$; otherwise, it outputs $\texttt{0}$.

If your $200\,000$-th action does not catch the $k$-th hoglin, the testing system outputs $\texttt{-1}$ instead of its usual answer, and your program should immediately stop execution to guarantee the `Wrong Answer` verdict.

The interactor in this problem is not adaptive. It is guaranteed that the hoglins follow the rules described in the problem statement. The starting cell for each hoglin is chosen uniformly at random and their moves are chosen uniformly at random from the range of cells that they consider accessible.

The problem has at most $15$ tests.

Here is the summary of all possible interactor answers:
- $\texttt{-1}$ --- too many actions;
- $\texttt{0}$ --- hoglin moved successfully, did not bump;
- $\texttt{1}$ --- hoglin attempted to move, bumped into blocked cell;
- $\texttt{2}$ --- hoglin is caught, interaction starts again;
- $\texttt{3}$ --- hoglin is caught, stop.
## 输入格式

See also **Interaction Protocol**.
## 输出格式

See also **Interaction Protocol**.
## 样例

### 样例输入 #1
```
9 2

0

1

1

0

1

2

1

0

0

3
```
### 样例输出 #1
```

3

7

5

1

9

4

5

7

0

2
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/h3gyhxo6.png)

We show the sample from the point of view of the hoglins.

The black dot shows the current position of the hoglin.

Crosses mark blocked cells.

White cells mark the range which the hoglin considers to be accessible; other cells are marked gray.

On the right is the action that was performed by either Hermione or the hoglin to get to this state from the previous one.


---

---
title: "[NERC2024] Legacy Screensaver"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12103
tag: ['2024', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Legacy Screensaver
## 题目描述

On a very old operating system, a screensaver consists of two rectangles flying around the screen. The screen is $W$ pixels wide and $H$ pixels high. Consider the origin to be in the top-left corner of the screen, the $x$-axis to go from the origin to the right, and the $y$-axis to go from the origin to the bottom.

Rectangle $i$ ($i = 1, 2$) has a width of $w_i$ pixels, a height of $h_i$ pixels, initially its top-left corner has coordinates $(x_i, y_i)$, and its initial movement direction is $(\delta x_i, \delta y_i)$, where each of $\delta x_i$ and $\delta y_i$ is either $-1$ or $1$. At the end of each second, rectangle $i$'s top-left corner coordinates instantly change by $(\delta x_i, \delta y_i)$. 

Whenever rectangle $i$ touches the left or the right border of the screen, the value of $\delta x_i$ changes sign before the next second. Similarly, whenever rectangle $i$ touches the top or the bottom border of the screen, the value of $\delta y_i$ changes sign before the next second. Whenever rectangle $i$ touches two borders of the screen at the same time (which can only happen at the corner of the screen), both $\delta x_i$ and $\delta y_i$ change sign.

As a result of the above, both rectangles stay fully within the screen at all times. Informally, collisions of the rectangles with the screen borders are perfectly elastic. Note, however, that rectangle movement is still discrete: each rectangle moves instantly by $1$ pixel in both directions at the end of each second.

You are curious how often these two rectangles overlap. The rectangles are considered to be overlapping if their intersection has a positive area.

Let $f(t)$ be the number of integers $\tau = 0, 1, \ldots, t - 1$ such that the rectangles overlap during second $\tau$ (where second $0$ is before the rectangles start moving).

Find the limit of $\frac{f(t)}{t}$ as $t \rightarrow \infty$ as an irreducible fraction. It can be shown that this limit is a rational number.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $T$ ($1 \le T \le 1000$). The description of the test cases follows.

The first line of each test case contains two integers $W$ and $H$, denoting the width and the height of the screen ($3 \le W, H \le 4000$).

The next two lines describe the two rectangles. Each rectangle is described by six integers $w_i$, $h_i$, $x_i$, $y_i$, $\delta x_i$, $\delta y_i$, describing the $i$-th rectangle and denoting its width, its height, the coordinates of its top-left corner, and its initial movement direction ($1 \le w_i \le W - 2$; $1 \le h_i \le H - 2$; $0 < x_i < W - w_i$; $0 < y_i < H - h_i$; $\delta x_i, \delta y_i \in \{-1, 1\})$.

The sum of the values of $W + H$ across all test cases is guaranteed to not exceed $8000$.
## 输出格式

For each test case, print a non-negative integer $p$ and a positive integer $q$, separated by a slash ($\tt{/}$) without spaces, meaning that the limit of $\frac{f(t)}{t}$ as $t \rightarrow \infty$ is equal to $\frac{p}{q}$. The fraction must be irreducible --- that is, the greatest common divisor of $p$ and $q$ must be equal to $1$.
## 样例

### 样例输入 #1
```
2
3 3
1 1 1 1 1 1
1 1 1 1 1 -1
5 4
2 2 1 1 -1 -1
2 1 2 2 1 -1
```
### 样例输出 #1
```
1/2
1/3
```
## 提示

For the second test case, the state of rectangles during the first few seconds is shown in the following pictures. The rectangles overlap during seconds $\tau = 0$ and $\tau = 6$. Thus, for example, $f(8) = 2$.

![](https://cdn.luogu.com.cn/upload/image_hosting/nskvvhru.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/jaaryddz.png)


---

---
title: "[NWRRC2024] Eight-Shaped Figures"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12109
tag: ['2024', 'ICPC', '俄罗斯西北']
---
# [NWRRC2024] Eight-Shaped Figures
## 题目背景

*Looking at problems `K-Shaped Figures` and `H-Shaped Figures` from the past two years, you took the warning seriously. You came prepared. For each of the remaining 24 letters of the alphabet, you theorized what the problem could be. You even implemented all 24 solutions and used up all of your Digital Team Reference Document space just to bring these codes to the contest. If the judges are so unoriginal that they set another problem about letter shapes, you'll just get it accepted on minute 1 and leave everyone puzzled.*

*What, another shapes problem? Really?! Ha-ha! Oh... wait a second...*
## 题目描述

Let's say that two circles on a plane form an $\textit{8-shaped figure}$ if they touch each other, but neither of them lies inside the other one.

![](https://cdn.luogu.com.cn/upload/image_hosting/selhsqb5.png)

You are given a collection of $n$ circles on the plane. No two circles have more than one common point. In other words, no two circles intersect twice or coincide, but they can touch or lie one within another.

Find the number of pairs of circles from this collection that form an 8-shaped figure.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains a single integer $n$, denoting the number of circles ($2 \le n \le 2 \cdot 10^5$).
 
The $i$-th of the following $n$ lines contains three integers $x_i$, $y_i$, and $r_i$, denoting the coordinates of the center of the $i$-th circle and its radius ($-10^9 \le x_i, y_i \le 10^9$; $1 \le r_i \le 10^9$). No two circles intersect twice or coincide, but they can touch or lie one within another.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.
## 输出格式

For each test case, print the number of pairs of circles that form an 8-shaped figure.

## 样例

### 样例输入 #1
```
2
5
1 1 1
1 3 1
3 1 1
3 3 1
6 7 4
6
-3 0 3
-2 0 2
-1 0 1
1 0 1
2 0 2
3 0 3
```
### 样例输出 #1
```
5
9
```


---

---
title: "[ICPC 2023 WF] A Recurring Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12299
tag: ['2023', 'ICPC']
---
# [ICPC 2023 WF] A Recurring Problem
## 样例

### 样例输入 #1
```
3

```
### 样例输出 #1
```
2
1 1
1 1
2 3 5 8 13 21 34 55 89 144

```
### 样例输入 #2
```
1235

```
### 样例输出 #2
```
4
1 1 3 1
3 2 1 1
9 15 44 99 255 611 1519 3706 9129 22377

```


---

---
title: "[ICPC 2022/2023 WF] Bridging the Gap"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12304
tag: ['2022', '2023', 'ICPC']
---
# [ICPC 2022/2023 WF] Bridging the Gap
## 样例

### 样例输入 #1
```
4 2
1 2 10 5

```
### 样例输出 #1
```
17

```
### 样例输入 #2
```
4 6
1 2 10 5

```
### 样例输出 #2
```
10

```


---

---
title: "[ICPC 2022 WF] Archaeological Recovery"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12311
tag: ['2022', 'Special Judge', 'ICPC']
---
# [ICPC 2022 WF] Archaeological Recovery
## 样例

### 样例输入 #1
```
2 3 4
EEE 1
EIA 1
IAE 1
AAA 1

```
### 样例输出 #1
```
+-0
+++

```
### 样例输入 #2
```
3 2 2
IA 4
AA 4

```
### 样例输出 #2
```
-0
00
00

```


---

---
title: "[NAC 2025] Most Scenic Cycle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12626
tag: ['2025', 'ICPC', 'NAC']
---
# [NAC 2025] Most Scenic Cycle
## 题目描述

The government of the Independent Country of Problem Creators (ICPC) finally saved enough money to construct high speed rail infrastructure. The new rail system has $V$ stations and $E$ bidirectional direct railway lines that each connect two stations together. The head of ICPC Rail Infrastructure Planning, Skib E. Dee, has seen enough programming problems about tree-topology transportation networks in other countries to know that such a network would be a recipe for disaster: a single broken railway line would split the network into disconnected pieces and disrupt travel for days. Instead, Dee decided that the ICPC rail network will be **robustly connected**: every pair of stations $s_1$, $s_2$ must be connected by at least two paths which do not share any direct railway lines, and do not share any railway stations other than $s_1$ and $s_2$ themselves.

Of course, ICPC cannot afford to build too many redundant railway lines. To balance efficiency and resiliency, Dee has also designed the network to be **regionally connected**. A cycle is a non-empty path from a station to itself which doesn't repeat any railway station (apart from the first station, which must repeat exactly once as the last station of the cycle). In order for the network to be regionally connected, there must exist a set $\mathcal{F}$ of $E-V+1$ **regional cycles** satisfying three properties:

- every direct railway line in the transportation network belongs to at least one regional cycle;
- if two regional cycles share any direct railway lines, then all railway lines and stations shared by those cycles lie along a connected path;
- for each subset $f$ of $\mathcal{F}$, at most $|f|-1$ pairs of regional cycles in $f$ share any direct railway lines.

To promote the new high speed rail, Dee needs to create a timelapse video of a train travelling around some cycle in the railway network. Each direct railway line has a (possibly negative) scenic value representing how nice the view out the train window is along that line. Dee wants to send the train around whichever cycle maximizes the sum of scenic values of the direct railway lines on the cycle---compute this maximum possible sum. (The most scenic cycle that Dee is looking for does **not** have to be a regional cycle.) In order to ensure this cycle is not boring, it must traverse at least two direct railway lines, and must not repeat any railway station (apart from the first station, which must repeat exactly once as the last station of the cycle).
## 输入格式

The first line of input contains two space-separated integers $V$ ($2\leq V \leq 2 \cdot 10^5$) and $E$ ($V \leq E \leq 4 \cdot 10^5$), the number of stations and direct railway lines in the rail network, respectively.

The next $E$ lines of input describe the direct railway lines. Each line contains three space-separated integers $a$, $b$, and $s$ ($1\leq a,b \leq V$; $-10^9 \leq s \leq 10^9$), signifying that a direct railway line exists between stations $a$ and $b$ with scenic value $s$. No direct railway line connects a station to itself, but **multiple direct railway lines might exist between the same two stations**. It is guaranteed that the input graph will be both **robustly connected** and **regionally connected**.
## 输出格式

Print the sum of scenic values around the cycle in the railway network that maximizes this sum.
## 样例

### 样例输入 #1
```
6 9
1 2 9
2 3 9
3 4 9
3 4 -9
4 1 9
1 5 1
5 6 1
6 2 1
3 4 8
```
### 样例输出 #1
```
36
```
### 样例输入 #2
```
5 7
1 2 1
2 3 -2
3 4 3
4 5 6
5 1 4
5 3 2
2 5 9
```
### 样例输出 #2
```
16
```
## 提示

For the railway network in Sample Input 2, one possible choice for the regional cycles in $\mathcal{F}$ are  $1 \rightarrow 2 \rightarrow 5 \rightarrow 1$, $2 \rightarrow 5 \rightarrow 3 \rightarrow 2$, and $3 \rightarrow 4 \rightarrow 5 \rightarrow 3$ (pictured on the left). The most scenic cycle (pictured on the right, in blue) has a scenic value sum of $9+6+3-2 = 16$.

![](https://cdn.luogu.com.cn/upload/image_hosting/31jr1qj8.png)


---

---
title: "[ICPC 2024 Yokohama R] Remodeling the Dungeon 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12785
tag: ['2024', 'Special Judge', 'ICPC']
---
# [ICPC 2024 Yokohama R] Remodeling the Dungeon 2
## 题目背景

译自 [ICPC 2024 Yokohama Regional Contest](https://icpc.jp/2024/)。
## 题目描述



_Icpca_ 王国的女王平静地居住在一座城堡中。一天，她决定重造城堡的地牢。  

地牢是一个由方形单元格组成的矩形网格。部分单元格是可进入的房间，而其他则是不可进入的管道空间。所有相邻单元格之间都被一堵墙隔开。某些相邻房间之间的墙上安装了用于通行的门。地牢中任意一对房间都可以通过这些门连通。  

女王希望重造地牢，使得任意一对房间之间仅存在唯一路径。此外，任意两个都只有一扇门的房间应通过一条经过偶数扇门的路径相连。 由于成本限制，重造时只能封锁部分（可能为零扇）门。  

你的任务是找到一种满足女王要求的地牢重造方案。  

## 输入格式


仅一组数据，格式如下所示：
 
>$h$ $w$
> $c_{1,1}$ $c_{1,2}$ $\cdots$ $c_{1,2w+1}$\
> $c_{2,1}$ $c_{2,2}$ $\cdots$ $c_{2,2w+1}$\
> $\vdots$\
> $c_{2h+1,1}$ $c_{2h+1,2}$ $\cdots$ $c_{2h+1,2w+1}$
>

两个整数 $h$ 和 $w$ 表示地牢大小为 $h \times w$（$1 \leq h,w \leq 400$）。  
每个字符 $c_{i,j}$（$1 \leq i \leq 2h+1$, $1 \leq j \leq 2w+1$）为 `.` 或 `#`，其含义如下：  

- 当 $i$ 和 $j$ 均为偶数时，$c_{i,j}$ 表示位于地牢第 $(i/2)$ 行（北向南）、第 $(j/2)$ 列（西向东）的单元格，记作单元格 $(i/2, j/2)$。若为 `.` 则是房间，若为 `#` 则是管道空间。  
- 当 $i$ 为奇数且 $j$ 为偶数时，表示一堵墙。若 $i=1$ 或 $i=2h+1$，则为地牢外墙（始终为 `#`）。否则 $c_{i,j}$ 表示单元格 $((i−1)/2, j/2)$ 和 $((i+1)/2, j/2)$ 之间的墙。若为 `.` 则该墙有门，若为 `#` 则无门（门仅存在于两个房间之间的墙上）。  
- 当 $i$ 为偶数且 $j$ 为奇数时，同样表示一堵墙。若 $j=1$ 或 $j=2w+1$，则为地牢外墙（始终为 `#`）。否则 $c_{i,j}$ 表示单元格 $(i/2, (j−1)/2)$ 和 $(i/2, (j+1)/2)$ 之间的墙。若为 `.` 则该墙有门，若为 `#` 则无门（门仅存在于两个房间之间的墙上）。  
- 当 $i$ 和 $j$ 均为奇数时，$c_{i,j}$ 始终为 `#`，对应墙体的交叉点。  

数据保证地牢中至少有一个房间，且任意一对房间存在连通路径。  
## 输出格式


若无法按要求重造地牢，输出 $\texttt{No}$。否则第一行输出 $\texttt{Yes}$，接着按输入格式输出重造后的地牢配置（若有多种可能配置，输出任意一种即可）。


## 样例

### 样例输入 #1
```
3 3
#######
#.....#
#.#.###
#.#...#
#.#.#.#
#.....#
#######
```
### 样例输出 #1
```
Yes
#######
#.....#
#.#####
#.#...#
#.###.#
#.....#
#######
```
### 样例输入 #2
```
3 3
#######
#.....#
###.###
###...#
###.#.#
#.....#
#######
```
### 样例输出 #2
```
Yes
#######
#.....#
###.###
###...#
#####.#
#.....#
#######
```
### 样例输入 #3
```
3 3
#######
#.....#
#.###.#
#.###.#
#.###.#
#.....#
#######
```
### 样例输出 #3
```
No
```


---

---
title: "[NERC 2022] Cactus Meets Torus"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12792
tag: ['2022', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Cactus Meets Torus
## 题目描述

Alice has a nice cactus graph that she wanted to place on a sheet of paper. Eve threatens to take one cycle of this cactus and cut the paper along all edges on this cycle. This way, the sheet of paper will be divided in two parts, and Alice will be upset. Luckily, Barbara just gave Alice a paper torus --- a sheet of paper where top and bottom edges are connected as well as left and right edges are connected without twisting. On torus, you can sometimes cut paper along all edges on a cycle, but it would still remain in one piece. Help Alice to determine if she can place her cactus on a torus such that Eve cannot cut paper along one cycle dividing the torus into two unconnected pieces.

$\textit{Cactus}$ is a connected undirected graph in which every edge lies on at most one simple cycle. Intuitively, cactus is a generalization of a tree where some cycles are allowed. Multiedges (multiple edges between a pair of vertices) and loops (edges that connect a vertex to itself) are not allowed in a cactus.

We say that a graph is placed on a sheet of paper if each vertex is a point on this sheet, each edge is a segment between points corresponding to its vertices, and these segments only intersect at their ends. On torus segments can go through sheet edges any number of times.
## 输入格式

The input consists of one or more independent test cases.

The first line of each test case contains two integers $n$ and $m$ 
($1 \le n \le 10^5$; $0 \le m \le 10^5$), where $n$ is the number of vertices in the graph. Vertices are numbered from $1$ to $n$. The edges of the graph are represented by a set of edge-distinct paths, where $m$ is the number of such paths. 

Each of the following $m$ lines contains a path in the graph. A path starts
with an integer $s_i$ ($2 \le s_i \le 1000$) followed by $s_i$ integers
from $1$ to $n$. These $s_i$ integers represent vertices of a path. Adjacent vertices in a path are distinct. The path can go through the same vertex multiple times, but every edge is traversed exactly once in the whole test case. There are no multiedges in the graph (there is at most one edge between any two vertices).

The last line of the input after all test cases contains two zeros. It does $\textbf{not}$ define a test case. It just marks the end of the input and does not require any output.

All graphs in the input are cacti. The total sum of all values of $n$ and
the total sum of all values of $m$ throughout the input both do not exceed $10^5$.
## 输出格式

Print the answer for each test case in the same order the cases appear in the input. For each test case, print a single line with ``Yes`` if you can place this cactus on a torus or print ``No`` otherwise.
## 样例

### 样例输入 #1
```
6 1
8 1 2 3 1 4 5 6 4
10 2
9 1 2 3 1 10 4 5 6 4
5 7 8 9 7 10
0 0
```
### 样例输出 #1
```
Yes
No
```
## 提示

One way to place the cactus from the first case on a torus is shown on the picture.

![](https://cdn.luogu.com.cn/upload/image_hosting/dvhu6d05.png)


---

---
title: "[NERC 2022] Jumbled Trees"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12799
tag: ['2022', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Jumbled Trees
## 题目描述

You are given an undirected connected graph with $n$ vertices and $m$ edges. Each edge has an associated counter, initially equal to $0$. In one operation, you can choose an arbitrary spanning tree and add any value $v$ to all edges of this spanning tree. 

Determine if it's possible to make every counter equal to its target value $x_i$ modulo prime $p$, and provide a sequence of operations that achieves it.
## 输入格式

The first line contains three integers $n$, $m$, and $p$ --- the number of vertices, the number of edges, and the prime modulus ($1 \le n \le 500$; $1 \le m \le 1000$; $2 \le p \le 10^9$, $p$ is prime).

Next $m$ lines contain three integers $u_i$, $v_i$, $x_i$ each --- the two endpoints of the $i$-th edge and the target value of that edge's counter ($1 \le u_i, v_i \le n$; $0 \le x_i < p$; $u_i \neq v_i$). 

The graph is connected. There are no loops, but there may be multiple edges between the same two vertices.
## 输出格式

If the target values on counters cannot be achieved, print $\tt{-1}$. 

Otherwise, print $t$ --- the number of operations, followed by $t$ lines, describing the sequence of operations. Each line starts with integer $v$ ($0 \le v < p$) --- the counter increment for this operation. Then, in the same line, followed by $n - 1$ integers $e_1$, $e_2$, $\ldots$ $e_{n - 1}$ ($1 \le e_i \le m$) --- the edges of the spanning tree.

The number of operations $t$ should not exceed $2m$. You don't need to minimize $t$. Any correct answer within the $2m$ bound is accepted. You are allowed to repeat spanning trees.
## 样例

### 样例输入 #1
```
3 3 101
1 2 30
2 3 40
3 1 50
```
### 样例输出 #1
```
3
10 1 2
20 1 3
30 2 3
```
### 样例输入 #2
```
2 2 37
1 2 8
1 2 15
```
### 样例输出 #2
```
2
8 1
15 2
```
### 样例输入 #3
```
5 4 5
1 3 1
2 3 2
2 5 3
4 1 4
```
### 样例输出 #3
```
-1
```


---

---
title: "[NERC 2022] Lisa's Sequences"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12801
tag: ['2022', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Lisa's Sequences
## 题目描述

Lisa loves playing with the sequences of integers. When she gets a new integer sequence $a_i$ of length $n$, she starts looking for all $\textit{monotone}$ subsequences. A monotone subsequence $[l, r]$ is defined by two indices $l$ and $r$ ($1 \le l < r \le n$) such that $\forall i = l, l+1, \ldots, r-1: a_i \le a_{i+1}$ or $\forall i = l, l+1, \ldots, r-1: a_i \ge a_{i+1}$. 

Lisa considers a sequence $a_i$ to be $\textit{boring}$ if there is a monotone subsequence $[l, r]$ that is as long as her boredom threshold $k$, that is when $r - l + 1 = k$.

Lucas has a sequence $b_i$ that he wants to present to Lisa, but the sequence might be boring for Lisa. So, he wants to change some elements of his sequence $b_i$, so that Lisa does not get bored playing with it. However, Lucas is lazy and wants to change as few elements of the sequence $b_i$ as possible. Your task is to help Lucas find the required changes. 
## 输入格式

The first line of the input contains two integers $n$ and $k$ ($3 \le k \le n \le 10^6$) --- the length of the sequence and Lisa's boredom threshold. The second line contains $n$ integers $b_i$ ($1 \le b_i \le 99\,999$) --- the original sequence that Lucas has.
## 输出格式

On the first line output an integer $m$ --- the minimal number of elements in $b_i$ that needs to be changed to make the sequence not boring for Lisa. On the second line output $n$ integers $a_i$ ($0 \le a_i \le 100\,000$), so that the sequence of integers $a_i$ is not boring for Lisa and is different from the original sequence $b_i$ in exactly $m$ positions.
## 样例

### 样例输入 #1
```
5 3
1 2 3 4 5
```
### 样例输出 #1
```
2
1 0 3 0 5
```
### 样例输入 #2
```
6 3
1 1 1 1 1 1
```
### 样例输出 #2
```
3
1 100000 0 1 0 1
```
### 样例输入 #3
```
6 4
1 1 4 4 1 1
```
### 样例输出 #3
```
1
1 1 4 0 1 1
```
### 样例输入 #4
```
6 4
4 4 4 2 2 2
```
### 样例输出 #4
```
2
4 4 0 2 0 2
```
### 样例输入 #5
```
6 4
4 4 4 3 4 4
```
### 样例输出 #5
```
1
4 4 100000 3 4 4
```
### 样例输入 #6
```
8 4
2 1 1 3 3 1 1 2
```
### 样例输出 #6
```
2
2 1 1 3 0 1 0 2
```
### 样例输入 #7
```
10 4
1 1 1 2 2 1 1 2 2 1
```
### 样例输出 #7
```
2
1 1 100000 2 2 100000 1 2 2 1
```
### 样例输入 #8
```
7 5
5 4 4 3 4 4 4
```
### 样例输出 #8
```
0
5 4 4 3 4 4 4
```
### 样例输入 #9
```
10 10
1 1 1 1 1 1 1 1 1 1
```
### 样例输出 #9
```
1
1 1 1 1 1 1 1 1 0 1
```


---

---
title: "[NERC 2021] Admissible Map"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12814
tag: ['2021', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Admissible Map
## 题目描述

A $\textit{map}$ is a matrix consisting of symbols from the set of $\texttt{U}$, $\texttt{L}$, $\texttt{D}$, and $\texttt{R}$.

A $\textit{map graph}$ of a map matrix $a$ is a directed graph with $n \cdot m$ vertices numbered as $(i, j)$ ($1 \le i \le n; 1 \le j \le m$), where $n$ is the number of rows in the matrix, $m$ is the number of columns in the matrix. The graph has $n \cdot m$ directed edges $(i, j) \to (i + di_{a_{i, j}}, j + dj_{a_{i, j}})$, where $(di_U, dj_U) = (-1, 0)$; $(di_L, dj_L) = (0, -1)$; $(di_D, dj_D) = (1, 0)$; $(di_R, dj_R) = (0, 1)$. A map graph is $\textit{valid}$ when all edges point to valid vertices in the graph.

An $\textit{admissible map}$ is a map such that its map graph is valid and consists of a set of cycles.

A $\textit{description}$ of a map $a$ is a concatenation of all rows of the map --- a string $a_{1,1} a_{1,2} \ldots a_{1, m} a_{2, 1} \ldots a_{n, m}$.

You are given a string $s$. Your task is to find how many substrings of this string can constitute a description of some admissible map. 

A $\textit{substring}$ of a string $s_1s_2 \ldots s_l$ of length $l$ is defined by a pair of indices $p$ and $q$ ($1 \le p \le q \le l$) and is equal to $s_ps_{p+1} \ldots s_q$. Two substrings of $s$ are considered different when the pair of their indices $(p, q)$ differs, even if they represent the same resulting string.
## 输入格式

In the only input line, there is a string $s$, consisting of at least one and at most $20\,000$ symbols $\texttt{U}$, $\texttt{L}$, $\texttt{D}$, or $\texttt{R}$.
## 输出格式

Output one integer --- the number of substrings of $s$ that constitute a description of some admissible map.
## 样例

### 样例输入 #1
```
RDUL
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
RDRU
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
RLRLRL
```
### 样例输出 #3
```
6
```
## 提示

In the first example, there are two substrings that can constitute a description of an admissible map --- $\texttt{RDUL}$ as a matrix of size $2 \times 2$ (pic. 1) and $\texttt{DU}$ as a matrix of size $2 \times 1$ (pic. 2). 

In the second example, no substring can constitute a description of an admissible map. E.g. if we try to look at the string $\texttt{RDRU}$ as a matrix of size $2 \times 2$, we can find out that the resulting graph is not a set of cycles (pic. 3).


In the third example, three substrings $\texttt{RL}$, two substrings $\texttt{RLRL}$ and one substring $\texttt{RLRLRL}$ can constitute an admissible map, some of them in multiple ways. E.g. here are two illustrations of substring $\texttt{RLRLRL}$ as matrices of size $3 \times 2$ (pic. 4) and $1 \times 6$ (pic. 5).

![](https://cdn.luogu.com.cn/upload/image_hosting/l6bwviyf.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/s5569ho8.png)


---

---
title: "[NERC 2021] Budget Distribution"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12815
tag: ['2021', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Budget Distribution
## 题目描述

Distributing budgeted money with limited resources and many constraints is a hard problem. A $\textit{budget plan}$ consists of $t$ topics; $i$-th topic consists of $n_i$ items. 
For each topic, the $\textit{optimal relative money distribution}$ is known. The optimal relative distribution for the topic $i$ is a list of real numbers $p_{i,j}$, where $\sum\limits_{j=1}^{n_i}{p_{i,j}} = 1$. 

Let's denote the amount of money assigned to $j$-th item of the topic $i$ as $c_{i, j}$; the total amount of money for the topic is $C_i = \sum\limits_{j=1}^{n_i}{c_{i,j}}$. A $\textit{non-optimality}$ of the plan for the topic $i$ is defined as $\sum\limits_{j=1}^{n_i}\left|\frac{c_{i, j}}{C_i} - p_{i, j}\right|$. Informally, the non-optimality is the total difference between the optimal and the actual ratios of money assigned to all the items in the topic. The $\textit{total plan non-optimality}$ is the sum of non-optimalities of all $t$ topics. Your task is to minimize the total plan non-optimality.

However, the exact amount of money available is not known yet. $j$-th item of $i$-th topic already has $\hat c_{i,j}$ dollars assigned to it and they cannot be taken back. Also, there are $q$ possible values of the extra unassigned amounts of money available $x_k$. For each of them, you need to calculate the minimal possible total non-optimality among all ways to distribute this extra money. You don't need to assign an integer amount of money to an item, any real number is possible, but all the extra money must be distributed among all the items in addition to $\hat c_{i,j}$ already assigned. 
Formally, for each value of extra money $x_k$ you'll need to find its distribution $d_{i,j}$ such that $d_{i, j} \ge 0$ and $\sum\limits_{i=1}^{t}\sum\limits_{j=1}^{n_i} d_{i,j} = x_k$, giving the resulting budget assignments $c_{i,j} = \hat c_{i,j} + d_{i,j}$ that minimize the total plan non-optimality.
## 输入格式

The first line contains two integers $t$ ($1 \le t \le 5 \cdot 10^4$) and $q$ ($1 \le q \le 3 \cdot 10^5$) --- the number of topics in the budget and the number of possible amounts of extra money. 

The next $t$ lines contain descriptions of topics. Each line starts with an integer $n_i$ ($2 \le n_i \le 5$) --- the number of items in $i$-th topic; it is followed by $n_i$ integers $\hat c_{i, j}$ ($0 \le \hat c_{i, j} \le 10^5$; for any $i$, at least one of $\hat c_{i,j} > 0$) --- the amount of money already assigned to $j$-th item in $i$-th topic; they are followed by $n_i$ integers $p'_{i,j}$ ($1 \le p'_{i,j} \le 1000$) --- they determine the values of $p_{i,j}$ as $p_{i, j} = {p'_{i, j}} \big/ {\sum\limits_{j=1}^{n_i}{p'_{i, j}}}$ with $\sum\limits_{j=1}^{n_i}{p_{i,j}} = 1$.  

The next line contains $q$ integers $x_k$ ($0 \le x_k \le 10^{12}$) --- $k$-th possible amount of extra money. 
## 输出格式

Output $q$ real numbers --- the minimal possible non-optimality for the corresponding amount of extra money $x_k$. An absolute or a relative error of the answer must not exceed $10^{-6}$. 
## 样例

### 样例输入 #1
```
1 5
3 1 7 10 700 400 100
0 2 10 50 102
```
### 样例输出 #1
```
1.0555555555555556
0.8666666666666667
0.5476190476190478
0.12745098039215708
0.0
```
### 样例输入 #2
```
2 5
3 10 70 100 700 400 100
3 10 30 100 700 400 100
2 10 50 70 110
```
### 样例输出 #2
```
2.2967032967032974
2.216776340655188
1.8690167362600323
1.7301587301587305
1.5271317829457367
```


---

---
title: "[NERC 2021] Global Warming"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12820
tag: ['2021', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Global Warming
## 题目描述

You are developing a new computer game. Let's consider an island in the middle of the ocean in a three-dimensional space with $z$-axis pointing upwards. The surface of the ocean is a horizontal plane with $z = 0$. The island is a polyhedron of a special form.

You are given $n$ points $(x_i, y_i, z_i)$; there are some edges between them. If we look at the island from above or if we discard $z$ coordinate of each point, points and edges form a planar connected graph. Every face of this planar graph, except the external one, is a nondegenerate triangle. Every edge of the graph belongs to at least one internal face. All points that lie on the edge of the external face of the graph have $z$ coordinates equal to zero. Other points may have arbitrary non-negative $z$ coordinates. Every face of the planar graph corresponds to the face of the polyhedron with the same vertices.

Due to global warming, the level of the ocean is increasing and floods the island. Your task is to compute various global warming scenarios for the game. 

In each scenario, the level of the ocean increased to the height $h$, so that the surface of the ocean is a plane $z = h$. Parts of the island that are $\textbf{below or at the height h}$ are now $\textit{flooded}$, even though some parts may be not reachable from the ocean by water (see the illustration for the second example). In a scenario, a player is standing in $p$-th point. You shall compute the area of the surface of the part of the island where the player is standing, or determine that the player is standing at or below the water level and has drowned. 

Formally, we say that two points on the surface of the island belong to the same part if a player can move between them walking by the surface of the island staying strictly higher than ocean level. Note that you should find the area of the surface of the island itself, not the area of its projection on a horizontal plane.
## 输入格式

The first line contains a single integer $n$ --- the number of points ($1 \le n \le 10^5$).

Each of the next $n$ lines contains three integers $x_i$, $y_i$, and $z_i$ --- the coordinates of $i$-th point ($-10^6 \le x_i, y_i \le 10^6$; $0 \le z_i \le 10^6$).

The next line contains a single integer $m$ --- the number of internal faces of the planar graph ($1 \le m \le 10^5$). They are also the faces of the island's polyhedron.

Each of the next $m$ lines contains three integers $a_i$, $b_i$, and $c_i$ --- the indices of three points that are vertices of $i$-th internal face ($1 \le a_i, b_i, c_i \le n$).

It is guaranteed that if $z$ coordinate is discarded, then the resulting graph is a connected and planar graph. All its faces, except the external one, are nondegenerate triangles. All points that lie on the edge of the external face of the planar graph have $z$ coordinate equal to zero.

The next line contains an integer $q$ --- the number of global warming scenarios to compute ($1 \le q \le 10^5$).

Each of the next $q$ lines contains two integers $h_i$ and $p_i$ --- the level of the ocean and the index of the point where the player is standing respectively ($0 \le h_i \le 10^6$; $1 \le p_i \le n$).
## 输出格式

For every scenario output a single real number --- the area of the surface of part of the island where the player is standing. If the player's position is flooded by water, output $-1$ instead.

The answer is considered correct if its absolute or relative error does not exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
5
0 0 0
2 0 0
2 2 0
0 2 0
1 1 4
4
1 2 5
2 3 5
3 4 5
4 1 5
7
0 1
0 5
1 5
2 5
3 5
4 5
5 5
```
### 样例输出 #1
```
-1
16.492422502470642
9.276987657639736
4.123105625617661
1.030776406404415
-1
-1
```
### 样例输入 #2
```
16
0 5 0
1 2 0
2 5 5
3 7 0
4 0 0
4 3 5
5 5 1
6 2 0
6 6 5
7 4 4
7 8 0
8 2 0
9 4 0
4 6 4
6 3 3
2 4 5
22
11 10 9
12 8 10
2 6 5
9 10 7
8 15 6
16 3 6
15 6 7
7 3 14
8 10 15
11 13 10
16 6 2
12 10 13
10 7 15
16 3 2
3 4 1
14 7 9
11 9 4
3 6 7
5 6 8
14 4 3
3 1 2
9 4 14
7
0 7
1 7
1 16
2 10
3 9
4 16
5 16
```
### 样例输出 #2
```
120.483405354306325
-1
93.929895222484783
68.181919663536940
40.918561474148331
11.067441790921070
-1
```
## 提示

The illustrations of the examples are views of the island from the above. The ocean is hatched. The island is drawn with contour lines, with higher parts in darker colors.

### Sample 1

![](https://cdn.luogu.com.cn/upload/image_hosting/6i7gpzp5.png)

### Sample 2

The island in the second example looks as follows.

![](https://cdn.luogu.com.cn/upload/image_hosting/85a3xso9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/kgxdolc5.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/zf3pxpa6.png)


---

---
title: "[NERC 2021] Heroes of Might"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12821
tag: ['2021', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Heroes of Might
## 题目描述

Recently, Hellen played her favorite game "Heroes of Might". She had a hero with only one Rust dragon, which was attacked by another hero with a lot of peasants. Another hero had $n$ groups of peasants, $i$-th of them had $a_i$ peasants in it. Unfortunately, Hellen lost that battle, but now she is wondering how big the health of the Rust dragon should be to win against such a big army of peasants?

Let's discuss how the battle goes. Initially, the Rust dragon has $h_d$ health points, and each peasant has $h_p$ health points. So $i$-th group of peasants has a total of $H = h_p \cdot a_i$ health points at the start of the battle. The battle consists of several rounds. In each round, two things happen:

- First, $\textbf{the dragon chooses one group of peasants and attacks it}$. The health of that group is decreased by the dragon's damage rating $d$. If the group has zero or less health points, it is destroyed and is removed from the game. 
- Second, $\textbf{each one of the peasant groups attacks the dragon}$. A group with the total current health $H$ has $\lceil\frac{H}{h_p}\rceil$ peasants still alive and each of them decreases the dragon's health by one.

If the dragon's health becomes zero or less at any point, it dies and Hellen loses. If all peasant groups are destroyed, Hellen wins the battle. 

You need to determine the smallest possible $h_d$, which could make Hellen win if she chooses targets on each turn optimally. 
## 输入格式

The first line of the input contains an integer $t$ ($1 \le t \le 1000$) --- the number of test cases you need to solve.

Each of the test cases is described by two lines. The first line contains three numbers $n$ ($1 \le n \le 1000$), $d$ ($1 \le d \le 10^9$), and $h_p$ ($1 \le h_p \le 10^9$) --- the number of peasant groups, the dragon's damage rating, and the health of each peasant. The second line contains $n$ numbers $a_i$ ($1 \le a_i \le 10^9; h_p \cdot \sum{a_i} \le 10^9$) --- the number of peasants in each group.

The sum of $n$ over all test cases does not exceed $1000$.
## 输出格式

For each test case, output one number --- the smallest amount of health $h_d$ that the dragon should have for Hellen to win the battle. If the dragon is never attacked by a peasant, it should still have positive health, so output 1 in this case.
## 样例

### 样例输入 #1
```
4
1 15 10
4
1 10 1
10
2 15 10
4 5
2 11 15
10 17
```
### 样例输出 #1
```
5
1
26
504
```
## 提示

In the third test case, the optimal Hellen's strategy leads to the following battle. At the start, the dragon has $h_d=26$ health points, and two groups of peasants have $H_1=4\cdot10$ and $H_2=5\cdot10$ health points. We'll denote them as $H_1=40(4)$ and $H_2=50(5)$, placing the value of $\lceil\frac{H}{h_p}\rceil$ in the brackets. 

$$\begin{array}{c}
h_d=26, H_1=40(4), H_2=50(5) & \text{Round 1} & \textbf{The dragon attacks the first group}, \text{dealing 15 damage, leaving}\ H_1=25(3). \\
h_d=26, H_1=25(3), H_2=50(5) &  & \text{Peasants attack the dragon}, \text{dealing 3+5 damage, leaving}\ h_d=18. \\
h_d=18, H_1=25(3), H_2=50(5) & \text{Round 2} & \textbf{The dragon attacks the first group}, \text{dealing 15 damage, leaving}\ H_1=10(1). \\
h_d=18, H_1=10(1), H_2=50(5) & & \text{Peasants attack the dragon}, \text{dealing 1+5 damage, leaving}\ h_d=12. \\
h_d=12, H_1=10(1), H_2=50(5) & \text{Round 3} & \textbf{The dragon attacks the second group}, \text{dealing 15 damage, leaving}\ H_2=35(4). \\
h_d=12, H_1=10(1), H_2=35(4) &  & \text{Peasants attack the dragon}, \text{dealing 1+4 damage, leaving}\ h_d=7. \\
h_d=7, H_1=10(1), H_2=35(4) & \text{Round 4} & \textbf{The dragon attacks the second group}, \text{dealing 15 damage, leaving}\ H_2=20(2). \\
h_d=7, H_1=10(1), H_2=20(2) &  & \text{Peasants attack the dragon}, \text{dealing 1+2 damage, leaving}\ h_d=4. \\
h_d=4, H_1=10(1), H_2=20(2) & \text{Round 5} & \textbf{The dragon attacks the second group}, \text{dealing 15 damage, leaving}\ H_2=5(1) \\
h_d=4, H_1=10(1), H_2=5(1) &  & \text{Peasants attack the dragon}, \text{dealing 1+1 damage, leaving}\ h_d=2. \\
h_d=2, H_1=10(1), H_2=5(1) & \text{Round 6} & \textbf{The dragon attacks the second group},  \text{destroying it, so it is removed from the game.} \\
h_d=2, H_1=10(1) &  & \text{Peasants attack the dragon}, \text{dealing 1 damage, leaving}\ h_d=1. \\
h_d=1, H_1=10(1) & \text{Round 7} & \textbf{The dragon attacks the first group}, \text{destroying it, so it is removed from the game.} \\
h_d=1 & \text{Game over} & \text{The dragon is still alive, Hellen wins.}
\end{array}$$


---

---
title: "[NERC 2021] Kingdom Partition"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12824
tag: ['2021', '网络流', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Kingdom Partition
## 题目描述

The King is gone. After the King's rule, all the roads in the Kingdom are run down and need repair. Three of the King's children, Adrian, Beatrice and Cecilia, are dividing the Kingdom between themselves.

Adrian and Beatrice do not like each other and do not plan to maintain any relations between themselves in the future. Cecilia is on good terms with both of them. Moreover, most of the Kingdom's workers support Cecilia, so she has better resources and more opportunity to repair the infrastructure and develop the~economy. 

Cecilia proposes to partition the Kingdom into three districts: A (for Adrian), B (for Beatrice), and C (for Cecilia), and let Adrian and Beatrice to negotiate and choose any towns they want to be in their districts, and agree on how they want to partition the Kingdom into three districts.

Adrian's castle is located in town $a$, and Beatrice's one is located in town $b$. So Adrian and Beatrice want their castles to be located in districts A and B, respectively. Cecilia doesn't have a castle, so district C can consist of no towns.

There is an issue for Adrian and Beatrice. When they choose the towns, they will have to pay for the roads' repair.

The cost to repair the road of length $l$ is $2l$ gold. However, Adrian and Beatrice don't have to bear all the repair costs. The repair cost for the road of length $l$ that they bear depends on what towns it connects:

- For a road between two towns inside district A, Adrian has to pay $2l$ gold;
- For a road between two towns inside district B, Beatrice has to pay $2l$ gold;
- For a road between towns from district A and district C, Adrian has to pay $l$ gold, Cecilia bears the remaining cost;
- For a road between towns from district B and district C, Beatrice has to pay $l$ gold, Cecilia bears the remaining cost.

The roads that connect towns from district A and district B won't be repaired, since Adrian and Beatrice are not planning to use them, so no one pays for them. Cecilia herself will repair the roads that connect the towns inside district C, so Adrian and Beatrice won't bear the cost of their repair either.

Adrian and Beatrice want to minimize the total cost they spend on roads' repair. Find the cheapest way for them to partition the Kingdom into three districts.
## 输入格式

The first line contains two integers $n$ and $m$ --- the number of towns and the number of roads in the Kingdom ($2 \le n \le 1000$; $0 \le m \le 2000$).

The second line contains two integers that represent town $a$ and town $b$ --- the towns that have to be located in district A and district B, respectively ($1 \le a, b \le n$; $a \ne b$).

The following $m$ lines describe the Kingdom roads. The $i$-th of them consists of three integers $u_i$, $v_i$, and $l_i$ representing a road of length $l_i$ between towns $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$; $u_i \ne v_i$; $1 \le l_i \le 10^9$).

Each pair of towns is connected with at most one road.
## 输出格式

In the first line output a single integer --- the minimum total cost of roads' repair for Adrian and Beatrice.

In the second line output a string consisting of $n$ characters $\tt{A}$, $\tt{B}$, and $\tt{C}$, $i$-th of the characters representing the district that the $i$-th town should belong to.

If several cheapest ways to partition the Kingdom exist, print any of them.
## 样例

### 样例输入 #1
```
6 7
1 3
1 2 10
2 3 5
1 3 7
4 5 3
3 6 100
4 6 3
5 6 8
```
### 样例输出 #1
```
16
ABBCBA
```
## 提示

The following picture illustrates the example. Adrian and Beatrice don't pay for the dashed roads, they pay $2l$ for the bold roads, and $l$ for the solid roads.

So the total cost is $2 \cdot 5 + 3 + 3 = 16$.

The castles of Adrian and Beatrice are located in bold towns.

![](https://cdn.luogu.com.cn/upload/image_hosting/11ffx3k7.png)


---

---
title: "[NERC 2020 Online] Find a Square"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12855
tag: ['2020', '各省省选', '2022', '福建', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020 Online] Find a Square
## 题目描述

Frank likes square numbers. That is numbers, which are the product of some integer with itself. Also Frank likes quadratic polynomials. He even has his favorite one: $p(x) = a \cdot x^2 + b \cdot x + c$. 

This morning Frank evaluated his favorite quadratic polynomial for $n$ consecutive integer arguments starting from $0$ and multiplied all the numbers he got.

If the resulting product is a square, his day is just perfect, but that might be not the case. So he asks you to find the largest square number which is a divisor of the resulting product.
## 输入格式

The only line of the input contains 4 integers $a, b, c, n$ ($1 \le a,b,c,n \le 600\,000$). 

## 输出格式

Find the largest square divisor of $\prod\limits_{i=0}^{n-1}{p(i)}$. As this number could be very large, output a single integer --- its remainder modulo $10^9+7$.
## 样例

### 样例输入 #1
```
1 1 1 10
```
### 样例输出 #1
```
74529
```
### 样例输入 #2
```
1 2 1 10
```
### 样例输出 #2
```
189347824
```
## 提示

In the first example, the product is equal to $1\cdot 3\cdot 7\cdot 13\cdot 21\cdot 31\cdot 43\cdot 57\cdot 73\cdot 91 = 2893684641939 = 38826291 \cdot 273^2$.


---

---
title: "[NERC 2020 Online] Hit the Hay"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12857
tag: ['2020', 'Special Judge', '概率论', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020 Online] Hit the Hay
## 题目描述

Some consider putting a baby to sleep to be an art, but this problem will show it is all just maths.

Consider a night during which a parent is trying to put a baby to sleep. An alarm clock will sound at the end of the night, and the parent is not allowed to change the alarm time, so the length of the night is fixed at $k$ hours from now.

The baby can be in one of the three states: state 0 means the baby is awake, state 1 means the baby is in light sleep, and state 2 means the baby is in deep sleep. The baby starts in state 0, and the change in a state happens continuously rather than discretely. You are given three numbers $p_0$, $p_1$, and $p_2$. Whenever the baby is in state $i$, the probability that no state change will happen in the next $x$ hours is $p_i^x$, where $x$ is a positive real number. In other words, the time before the next state change is picked from the $\emph{exponential distribution}$ with the cumulative distribution function of $1-p_i^x$.

Whenever a state change does happen, if the baby was in state 0, it will always switch to state 1; if the baby was in state 2, it will also always switch to state 1; if the baby was in state 1, it will switch to state 0 with the probability $q_0$ and to state 2 with the probability $1-q_0$.

The parent decides when to go to sleep themselves. However, if the baby is in state 0, it will cry and wake the parent up, so the parent can only be asleep if the baby is in state 1 or 2. The parent can choose to still stay awake even if the baby is in one of those states. If they do stay awake, they can:
- see which of the three states the baby is in;
- prevent the baby from waking up: if the baby decides to switch from state 1 to state 0 according to the above rules, and the parent is not asleep, then the baby will be comforted and will stay in state~1 instead.

The parent can decide to go to sleep arbitrarily, for example using the current state of the baby or the current time to make this decision. However, if they do go to sleep, then they will be asleep until either the baby wakes up (goes to state 0), or the alarm clock sounds at the end of the $k$ hours. If they get woken up by the baby waking up, then they can later decide to go to sleep again arbitrarily.

What is the maximum expected number of hours of sleep the parent can get if they decide to go to sleep in the optimal fashion?
## 输入格式

The first line of the input contains an integer $t$ ($1 \le t \le 1000$) --- the number of test cases.

The next $t$ lines describe test cases, each contains five floating-point numbers with exactly $\emph{one}$ digit after the decimal point, in the following order: $k$, $p_0$, $p_1$, $p_2$, $q_0$ ($0.1 \le k \le 10$; $0.1 \le p_0, p_1, p_2, q_0 \le 0.9$).
## 输出格式

Output $t$ lines with a floating-point number on each line --- the maximum expected amount of sleep for each test case. Your outputs will be considered correct if they are within $10^{-9}$ absolute difference from the answers.
## 样例

### 样例输入 #1
```
2
10.0 0.5 0.5 0.5 0.5
8.0 0.1 0.9 0.9 0.1
```
### 样例输出 #1
```
6.5990202123649855
7.540407031059442
```


---

---
title: "[NERC 2020] Fiber Shape"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12905
tag: ['计算几何', '2020', 'Special Judge', '微积分', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Fiber Shape
## 题目描述

Imagine a board with $n$ pins put into it, the $i$-th pin is located at $(x_i, y_i)$. 
For simplicity, we will restrict the problem to the case where the pins are placed in vertices of a convex polygon.

Then, take a non-stretchable string of length $l$, and put it around all the pins. Place a pencil inside the string and draw a curve around the pins, trying to pull the string in every possible direction. The picture below shows an example of a string tied around the pins and pulled by a pencil (a point $P$).

![](https://cdn.luogu.com.cn/upload/image_hosting/ej1gx8wa.png)

Your task is to find an area inside this curve. Formally, for a given convex polygon $S$ and a length $l$ let's define a $\emph{fiber shape}$ $F(S, l)$ as a set of points $t$ such that the perimeter of the convex hull of $S \cup \{t\}$ does not exceed $l$. Find an area of $F(S, l)$.
## 输入格式

The first line contains two integers $n$ and $l$ ($3 \le n \le 10^4$; $1 \le l \le 8 \cdot 10^5$) --- the number of vertices of the polygon $S$ and the length of the string. Next $n$ lines contain integers $x_i$ and $y_i$ ($-10^5 \le x_i, y_i \le 10^5$) --- coordinates of polygon's vertices in counterclockwise order. All internal angles of the polygon are strictly less than $\pi$. The length $l$ exceeds the perimeter of the polygon by at least $10^{-3}$.
## 输出格式

Output a single floating-point number --- the area of the fiber shape $F(S, l)$. Your answer will be considered correct if its absolute or relative error doesn't exceed $10^{-6}$. 
## 样例

### 样例输入 #1
```
3 4
0 0
1 0
0 1
```
### 样例输出 #1
```
3.012712585980357
```
### 样例输入 #2
```
4 5
0 0
1 0
1 1
0 1
```
### 样例输出 #2
```
5.682061989789656
```
### 样例输入 #3
```
5 17
0 0
2 -1
3 0
4 3
-1 4
```
### 样例输出 #3
```
37.719371276930820
```
## 提示

The following pictures illustrate the example tests.

![](https://cdn.luogu.com.cn/upload/image_hosting/lcmvxklh.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/nyr1k7a8.png)


---

---
title: "[NERC 2020] Hard Optimization"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12907
tag: ['2020', '各省省选', '2022', '福建', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Hard Optimization
## 题目描述

You are given a set of $n$ segments on a line $[L_i; R_i]$. All $2n$ segment endpoints are pairwise distinct integers.

The set is $\emph{laminar}$ --- any two segments are either disjoint or one of them contains the other.

Choose a non-empty subsegment $[l_i, r_i]$ with integer endpoints in each segment ($L_i \le l_i < r_i \le R_i$) in such a way that no two subsegments intersect (they are allowed to have common endpoints though) and the sum of their lengths ($\sum_{i=1}^n r_i - l_i$) is maximized.
## 输入格式

The first line contains a single integer $n$ ($1 \le n \le 2 \cdot 10^3$) --- the number of segments.

The $i$-th of the next $n$ lines contains two integers $L_i$ and $R_i$ ($0 \le L_i < R_i \le 10^9$) --- the endpoints of the $i$-th segment.

All the given $2n$ segment endpoints are distinct. The set of segments is laminar.
## 输出格式

On the first line, output the maximum possible sum of subsegment lengths.

On the $i$-th of the next $n$ lines, output two integers $l_i$ and $r_i$ ($L_i \le l_i < r_i \le R_i$), denoting the chosen subsegment of the $i$-th segment.
## 样例

### 样例输入 #1
```
4
1 10
2 3
5 9
6 7
```
### 样例输出 #1
```
7
3 6
2 3
7 9
6 7
```
## 提示

The example input and the example output are illustrated below.

![](https://cdn.luogu.com.cn/upload/image_hosting/b5xwqrzp.png)


---

---
title: "[NERC 2019] Cactus Revenge"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12936
tag: ['2019', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] Cactus Revenge
## 题目描述

NE(E)RC featured a number of problems in previous years about cactuses --- connected undirected graphs in which every edge belongs to at most one simple cycle. Intuitively, a $\textit{cactus}$ is a generalization of a tree where some cycles are allowed. The traditional cactus that was initially used in NEERC 2005 problem is given on the second picture in the Examples section.

You are given $n$ integers $d_1, d_2, \ldots, d_n$. Construct any cactus with $n$ vertices such that vertex $i$ has degree $d_i$ (i.e. exactly $d_i$ incident edges), or determine that no such cactus exists. Parallel edges and loops are not allowed.
## 输入格式

The first line contains a single integer $n$ ($2 \le n \le 2\,000$) --- the number of vertices in the cactus.

The second line contains $n$ integers $d_1, d_2, \ldots, d_n$ ($1 \le d_i \le n-1$) --- the desired vertex degrees.
## 输出格式

If it's impossible to construct a cactus satisfying the conditions, output a single integer $-1$.

Otherwise, by tradition, output the constructed cactus as a set of edge-distinct paths.

In the first line output an integer $m$ --- the number of such paths. Each of the following $m$ lines should contain a path in the graph. A path should start with an integer $k_i$ ($k_i \ge 2$) followed by $k_i$ integers from $1$ to $n$. These $k_i$ integers should represent consecutive vertices of this path. Adjacent vertices in the path should be distinct. The path can visit the same vertex multiple times, but every edge of the cactus should be traversed exactly once in the whole output. 
## 样例

### 样例输入 #1
```
5
2 2 3 2 1
```
### 样例输出 #1
```
4
2 1 2
2 2 3
2 3 1
3 3 4 5
```
### 样例输入 #2
```
4
3 3 2 2
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
6
1 2 1 1 2 1
```
### 样例输出 #3
```
-1
```
### 样例输入 #4
```
15
1 4 3 2 2 2 2 2 4 4 2 2 2 2 2
```
### 样例输出 #4
```
3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10
```
## 提示

**Sample 1**

![](https://cdn.luogu.com.cn/upload/image_hosting/bsskq1wa.png)

**Sample 4**

![](https://cdn.luogu.com.cn/upload/image_hosting/et4kgcwn.png)

Both in the second and the third example, there exist graphs that satisfy the given conditions but none of them are cactuses.


---

---
title: "[NERC 2019] Game Relics"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12940
tag: ['2019', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] Game Relics
## 题目描述

Esports is a form of competitive sports using video games. 
Dota 2 is one of the most popular competitive video games in Esports. Recently, a new video game Dota 3 was released. In Dota 3 a player can buy some relics for their hero. Relics are counters that track hero's actions and statistics in a game.

Gloria likes to play Dota 3, so she wants to buy all $n$ available relics for her favorite hero.

Relics can be bought using an in-game currency called shards. Each relic has its own price --- $c_i$ shards for the $i$-th relic. A player can buy a relic using one of the following options:
- Pay $c_i$ shards to buy the $i$-th relic;
- Pay $x$ shards and randomly get one of all $n$ relics. The probability of getting a relic is the same for all $n$ relics. If a duplicate relic is received, then the relic is recycled and $\frac{x}{2}$ shards are given back to the player.

Gloria wants to buy all $n$ relics. Help her minimize the expected number of shards she spends to buy all the relics.
## 输入格式

The first line contains two integers $n$ and $x$ ($1 \le n \le 100$; $1 \le x \le 10\,000$) --- the number of relics and the cost to receive a random relic.

The second line consists of $n$ integers $c_1, c_2, \ldots, c_n$ ($x \le c_i \le 10\,000$; $\sum{c_i} \le 10\,000$) --- the prices of $n$ relics.
## 输出格式

Print a single real number --- the minimum expected number of shards that Gloria must spend to buy all the relics.

The absolute or relative error should not exceed $10^{-9}$.
## 样例

### 样例输入 #1
```
2 20
25 100
```
### 样例输出 #1
```
47.50000000000000000
```
### 样例输入 #2
```
4 30
60 50 60 80
```
### 样例输出 #2
```
171.25000000000000000
```
## 提示

In the first example, the optimal strategy is to randomly get one of the two relics paying $20$ shards. Then there are two scenarios. 

The first one happens if Gloria receives the first relic. Then she keeps getting random relics until she obtains the second relic. The expected number of shards to spend in this scenario is $20 + 30 = 50$.

In the second scenario, Gloria initially gets the second relic. Then it is better to buy the first relic for $25$ shards, so the expected number of shards to spend in this scenario is $20 + 25 = 45$.

Thus, the expected number of shards to spend is $\frac{50 + 45}{2} = 47.5$.


---

---
title: "[NERC 2019] Help BerLine"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12941
tag: ['2019', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] Help BerLine
## 题目描述

Very soon, the new cell phone services provider "BerLine" will begin its work in Berland!

The start of customer service is planned along the main street of the capital. There are $n$ base stations that are already installed. They are located one after another along the main street in the order from the $1$-st to the $n$-th from left to right. 

Currently, all these base stations are turned off. They will be turned on one by one, one base station per day, according to some permutation $p = [p_1, p_2, \dots, p_n]$ ($ 1 \le p_i \le n$), where $p_i$ is the index of a base station that will be turned on on the $i$-th day. Thus, it will take $n$ days to turn on all base stations.

Each base station is characterized by its operating frequency $f_i$ --- an integer between $1$ and $24$, inclusive.

There is an important requirement for operating frequencies of base stations. Consider an arbitrary moment in time. For any phone owner, if we consider all base stations turned on in the access area of their phone, then in this set of base stations there should be at least one whose operating frequency is unique among the frequencies of these stations. Since the power of the phone and the position are not known in advance, this means that for any nonempty subsegment of turned on base stations, at least one of them has to have the operating frequency that is unique among the stations of this subsegment.

For example, let's take a look at a case of $n = 7$, all $n$ stations are turned on, and their frequencies are equal to $f = [1, 2, 1, 3, 1, 2, 1]$. Consider any subsegment of the base stations --- there is a base station with a unique frequency within this subsegment. However, if $f = [1, 2, 1, 2, 3, 2, 1]$, then there is no unique frequency on the segment $[1, 2, 1, 2]$ from the index $1$ to the index $4$, inclusive.

Your task is to assign a frequency from $1$ to $24$ to each of $n$ base stations in such a way that the frequency requirement is met at every moment. Remember that the base stations are turned on in the order of the given permutation $p$.
## 输入格式

The first line of the input contains an integer $t$ ($1 \le t \le 50$)~--- the number of test cases in the input. Then $t$ test case descriptions follow.

The first line of a test case contains an integer $n$ ($ 1 \le n \le 8\,500$) --- the number of "BerLine" base stations.

The following line contains $n$ distinct integers $p_1, p_2, \dots, p_n$ ($1 \le p_i \le n$) --- the order in which the base stations are turned on, i.e. on the $i$-th day the base station with the index $p_i$ is turned on.

It is guaranteed that a correct answer exists for all test cases in the input.
## 输出格式

The first line of the input contains an integer $t$ ($1 \le t \le 50$)~--- the number of test cases in the input. Then $t$ test case descriptions follow.

The first line of a test case contains an integer $n$ ($ 1 \le n \le 8\,500$) --- the number of "BerLine" base stations.

The following line contains $n$ distinct integers $p_1, p_2, \dots, p_n$ ($1 \le p_i \le n$) --- the order in which the base stations are turned on, i.e. on the $i$-th day the base station with the index $p_i$ is turned on.

It is guaranteed that a correct answer exists for all test cases in the input.
## 样例

### 样例输入 #1
```
5
3
1 3 2
3
1 2 3
1
1
10
6 10 4 2 7 9 5 8 3 1
10
2 4 6 9 1 8 10 5 3 7
```
### 样例输出 #1
```
1 3 2
10 20 10
1
2 3 4 5 3 1 3 5 4 2
1 2 3 4 5 6 7 8 9 10
```
## 提示

In the first test case $n = 3$ and $p = [1, 3, 2]$. The base stations can be assigned frequencies $[1, 3, 2]$.

- Day 1: only the base station $1$ is turned on, its frequency is $1$.
- Day 2: the base stations $1$ and $3$ are turned on, their frequencies are $[1, 2]$.
- Day 3: all base stations are turned on, their frequencies are $[1, 3, 2]$ (in the direction along the street).

On each day, each nonempty subsegment of turned on base stations has a base station with a unique frequency among this subsegment. It can be shown that three distinct frequencies are necessary in this test case.


---

---
title: "[NWRRC 2023] H-Shaped Figures"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13588
tag: ['计算几何', '树状数组', '2023', 'ICPC', '极角排序', 'NWRRC']
---
# [NWRRC 2023] H-Shaped Figures
## 题目描述

After a huge success of the last year's "K-Shaped Figures" problem, we've come up with an innovative "H-Shaped Figures" problem for this year. And we have some plans for the next 24 years.

Let's say that three segments $PQ$, $a$, and $b$ on a plane form an H-shaped figure if:

- point $P$ lies strictly inside segment $a$, and segments $PQ$ and $a$ are not collinear;
- point $Q$ lies strictly inside segment $b$, and segments $PQ$ and $b$ are not collinear;
- segments $a$ and $b$ do not have common points.

![](https://cdn.luogu.com.cn/upload/image_hosting/5qwh7w8x.png)

You are given the coordinates of points $P$ and $Q$, along with $n$ candidate segments for $a$ and $b$. Note that some of the given segments may coincide, but they should still be treated as different segments.

Find the number of possible ways to choose one of the given $n$ segments as $a$ and another one as $b$ to form an H-shaped figure along with the given segment $PQ$.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains four integers $x_P, y_P, x_Q, y_Q$, denoting the coordinates of points $P$ and $Q$ ($-10^9 \le x_P, y_P, x_Q, y_Q \le 10^9$). Points $P$ and $Q$ do not coincide.

The second line contains a single integer $n$, denoting the number of candidate segments ($2 \le n \le 2 \cdot 10^5$).

The $i$-th of the following $n$ lines contains four integers $x_{i,1}, y_{i,1}, x_{i,2}, y_{i,2}$, denoting the coordinates of the endpoints of the $i$-th segment ($-10^9 \le x_{i,1}, y_{i,1}, x_{i,2}, y_{i,2} \le 10^9$). All segments have positive lengths.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.
## 输出格式

For each test case, print the number of ways to form an H-shaped figure using the given segment $PQ$ and two of the candidate segments.
## 样例

### 样例输入 #1
```
1
0 0 4 0
8
0 0 2 1
-1 -1 2 2
3 3 5 -3
0 2 6 -1
2 -2 5 1
-1 1 3 -3
-1 0 2 0
-1 -1 2 2
```
### 样例输出 #1
```
6
```


---

---
title: "[ICPC 2025 APC] Antiparticle Antiphysics"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13615
tag: ['2024', 'Special Judge', 'ICPC']
---
# [ICPC 2025 APC] Antiparticle Antiphysics
## 题目背景

*在一个物理定律失常的平行宇宙里……*

## 题目描述

一座新的研究设施刚刚建成。它被称为大型反强子对撞机（LAC），是同类中最大的反粒子对撞机。反物理学家们正渴望用它来研究一种叫做“常规物质”的东西，这种物质与反物质相似，只是其电荷、宇称和时间都是相反的。在他们的一次 LAC 实验中，反物理学家们成功地将两种粒子——反质子和质子——限制在一个容器中，这些粒子在容器里从左到右排成一行。我们可以用一个下标从 1 开始的字符串来表示容器的状态。字符串的长度等于容器中粒子的数量，如果从左数第 $i$ 个粒子是反质子，则字符串的第 $i$ 个字符为 `A`，如果是质子，则为 `P`。

利用 LAC 的奇异能量束，他们可以通过以下四种不同类型的操作来修改状态：

* **操作 1：** 选择一个特定的质子，然后在它的左边和右边各插入两个反质子。这相当于将状态字符串中对应的字符 `P` 替换为 `APA`。
* **操作 2：** 选择一个特定的反质子，然后在它的左边和右边各插入两个质子。这相当于将状态字符串中对应的字符 `A` 替换为 `PAP`。
* **操作 3：** 选择一个由 $a$ 个反质子组成的连续子序列，然后将它们移除。
* **操作 4：** 选择一个由 $p$ 个质子组成的连续子序列，然后将它们移除。

请注意，操作 3 中的整数 $a$ 和操作 4 中的整数 $p$ 在输入中给出并且是固定的。这些操作可以按任意顺序执行任意次，但每次只能执行一个操作。

*初始状态*由字符串 $S$ 表示。他们希望通过一系列操作将其转变为*目标状态*，即字符串 $E$。请判断这是否可行。如果可行，请找出一个能将初始状态转变为目标状态的操作序列。
## 输入格式

输入的第一行包含一个整数 $t$ ($1 \le t \le 10$)，代表测试用例的数量。之后是 $t$ 个测试用例。每个测试用例包含一行，内含两个整数 $a$ 和 $p$ ($5 \le a, p \le 20$) 以及两个字符串 $S$ 和 $E$ ($1 \le |S|, |E| \le 50, S \ne E$)。字符串 $S$ 和 $E$ 只包含字符 `A` 和 `P`。
## 输出格式

对于每个测试用例，按以下格式输出。


如果无解，则输出一行一个字符串 `-1`。

否则，在第一行输出一个整数 $k$，代表将初始状态转变为目标状态所需的操作次数。在接下来的 $k$ 行中，每行输出以下内容之一（不含引号）来描述一个操作：

1.  "`+P i`" 表示对从左数第 $i$ 个粒子（$i \ge 1$）应用操作 1。该粒子必须是质子。
2.  "`+A i`" 表示对从左数第 $i$ 个粒子（$i \ge 1$）应用操作 2。该粒子必须是反质子。
3.  "`-A i`" 表示对 $a$ 个连续粒子应用操作 3，其中最左边的粒子是从左数的第 $i$ 个粒子（$i \ge 1$）。这些粒子必须是反质子。
4.  "`-P i`" 表示对 $p$ 个连续粒子应用操作 4，其中最左边的粒子是从左数的第 $i$ 个粒子（$i \ge 1$）。这些粒子必须是质子。

这些操作按照输出行的顺序执行，并且必须能将初始状态转变为目标状态。

操作次数 $k$ 必须满足 $1 \le k \le 35,000$。可以证明，如果初始状态可以转变为目标状态，总存在一个满足此 $k$ 值限制的操作序列。任何满足此 $k$ 值限制的有效序列都将被接受。特别地，你不需要最小化 $k$ 的值。
## 样例

### 样例输入 #1
```
4
13 10 PP PAAAAPAAAA
10 13 AAAAAAA PPPPPPP
7 8 PPAAAAAAAAP PPAP
8 9 PAPPPPPPPPP PPAP
```
### 样例输出 #1
```
4
+P 2
+P 3
+P 4
+P 5
-1
1
-A 3
2
+A 2
-P 5
```
## 提示

**样例解释 #1**


在第一个测试用例中，状态字符串的操作序列为 `PP` $\to$ `PAPA` $\to$ `PAAPAA` $\to$ `PAAAPAAAAA` $\to$ `PAAAAAPAAAAAAAAAAA`。

在第四个测试用例中，状态字符串的操作序列为 `PAPPPPPPPPP` $\to$ `PPAPPPPPPPPPP`，然后 `PPAPPPPPPPPPP` $\to$ `PPAP`。



---

---
title: "[ICPC 2025 APC] Symmetric Boundary"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13623
tag: ['2024', 'Special Judge', 'ICPC']
---
# [ICPC 2025 APC] Symmetric Boundary
## 题目描述

对称图形是美丽的，它们也是本题的主题。一个二维平面区域是**凸的**，当且仅当对于区域内的任意一对点 $p$ 和 $q$，连接 $p$ 和 $q$ 的线段完全包含在该区域内。此外，一个二维平面区域是**点对称的**，当且仅当将该区域围绕某个特定点旋转 $180$ 度后，旋转后的区域与原始区域完全重合。

给定一个二维平面上的凸多边形，它有 $n$ 个顶点，按逆时针顺序从 $1$ 到 $n$ 编号。顶点 $i$ 的坐标为 $(x_i, y_i)$。没有三个顶点共线。

请判断是否存在一个凸形的、点对称的区域，其边界包含了所有这 $n$ 个顶点。如果存在一个或多个这样的区域，请计算其中面积最小的区域的面积。
## 输入格式

输入的第一行包含一个整数 $n$ ($3 \le n \le 30$)。
接下来的 $n$ 行，每行包含两个整数。第 $i$ 行包含 $x_i$ 和 $y_i$ ($0 \le x_i, y_i \le 1000$)。

保证给定的多边形是凸的，其顶点按逆时针顺序给出，并且没有三个顶点共线。
## 输出格式

如果存在一个或多个这样的区域，输出其中的最小面积。输出的相对误差必须在 $10^{-9}$ 以内。

如果不存在这样的区域，则输出 $-1$。
## 样例

### 样例输入 #1
```
4
0 0
10 0
8 9
4 9
```
### 样例输出 #1
```
90.0
```
### 样例输入 #2
```
8
8 10
2 9
0 8
0 2
2 0
8 0
10 2
10 8
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
6
231 77
359 20
829 124
998 461
941 735
879 825
```
### 样例输出 #3
```
486567.9669655848
```
## 提示

**样例解释**

图 I.1 将样例输入中的顶点以黑点的形式展示了出来。对于样例输入 #1 和 #3，阴影部分代表了可能实现的最小面积区域。

![](https://cdn.luogu.com.cn/upload/image_hosting/igatyrwx.png)


---

---
title: "[ICPC 2025 APC] Zig-zag"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13627
tag: ['2024', 'ICPC']
---
# [ICPC 2025 APC] Zig-zag
## 题目描述

扎克的泽格工效学学位（Zergonomics Zegree）教会了他，在商店里展示物品的最佳方式是把它们堆叠成一种之字形图案。扎克需要将 $n$ 个装有可动人偶的盒子在店门口排成一列。这些盒子可以相互堆叠，并且它们是相同的、不可区分的。他的目标是决定要堆叠成的堆数，然后将盒子堆起来，使得每一堆都不是空的，并且各堆的盒子数量形成一个之字形序列。

形式上，如果有 $s$ ($s \ge 1$) 堆，从左到右编号为 $1$ 到 $s$，且第 $i$ 堆包含 $a_i$ 个盒子，那么必须满足以下条件：
* 对于每个 $i$（从 $1$ 到 $s$），$a_i \ge 1$，
* $a_1 + a_2 + \dots + a_s = n$，并且
* 以下至少一条为真：
    * $a_1 < a_2 > a_3 < a_4 > \dots$，或者
    * $a_1 > a_2 < a_3 > a_4 < \dots$

例如，对于 $n=6$，总共有 $12$ 种方式，如图 M.1 所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/r26c3d3f.png)

找出扎克可以用多少种不同的方式堆叠这 $n$ 个盒子，结果对 $998,244,353$ 取模。

两种方式被认为是相同的，当且仅当它们的堆数相同，并且在相同位置上的堆所含的盒子数量也相同。
## 输入格式

输入的第一行包含一个整数 $t$ ($1 \le t \le 300,000$)，代表测试用例的数量。之后是 $t$ 个测试用例。每个测试用例包含一行，内含一个整数 $n$ ($1 \le n \le 300,000$)。
## 输出格式

对于每个测试用例，输出一个整数，代表堆叠 $n$ 个盒子的不同方式数量，结果对 $998,244,353$ 取模。
## 样例

### 样例输入 #1
```
4
5
6
7
890
```
### 样例输出 #1
```
7
12
19
502674609
```
## 提示

**样例解释 #1**

第二个测试用例的 $n$ 值为 $6$，其 $12$ 种方式已在题目描述中说明。


---

---
title: "[CERC 2020] Offices"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13657
tag: ['2020', 'ICPC', 'CERC']
---
# [CERC 2020] Offices
## 题目描述

The network of detective offices is growing. New offices are connected to the already existing offices via computer cables. There are two types of cables – optical and quantum – which propagate signal at different speeds. It takes time $T_1$ and $T_2$ for a signal to travel between two offices connected by an optical cable and by a quantum cable, respectively. There can be at most one cable between any two offices and it must be of one of the two types.

There are two ranks of detectives, Technical rank and Social rank. Each detective belongs to exactly one rank.

The process of building and installing a new office is the following. When a request for a new office is raised and it complies with the request rules, a new office is built and gradually populated by detectives of both ranks.

The request for a new office comes from two detectives, say A and B, who have different ranks and who also reside in different offices. Suppose the first detective resides in office OA and the second one in office OB. For safety reasons, the offices OA and OB must not share a connection. It is guaranteed by the administration that no request from two offices sharing a connection is possible, as every officer understands the dangers of such a request.

Suppose that ON is the office that will be newly built. Office ON can be connected only to those already existing offices (denote by OE any one of them), to which at least one of OA and OB is already connected. Office ON will be connected to all offices satisfying the conditions and specifications given below.

The members of both ranks have opposing views on the reliability of the cables. A member of the Technical rank thinks that the type of connection between ON and OE should be the same as the type of connection of his current office to OE. A member of the Social rank thinks that the type of connection between ON and OE should not be the same type as the type of connection of his current office to OE. Therefore, the Headquarters have set the rules regarding new cables:

- When OE is connected to only one of the offices OA and OB, the type of the connection between ON and OE is decided by the detective in the respective office connected to OE.
- When OE is connected to both offices OA and OB, and the detectives A and B disagree on the type of the connection between ON and OE, then the connection is not built.
- When OE is connected to both offices OA and OB, and the detectives A and B agree on the type of connection between ON and OE, then the connection is built. However, it should be stressed, it is of the other type than the one which A and B agree on.

Now, there is a need of an application which keeps track of all the offices and the cables connecting them.

The Headquarters are located in the office labeled 0. After building a new office, the headquarters must be informed on the total sum of distances between the Headquarters and all the other offices that can be reached from it by a sequence of connections. The distance between two offices is the shortest time in which the signal can travel via cables from one office to another, supposing it spends no additional time inside any office on its path.
## 输入格式

The first line of input contains five integers $N, M, R, T_1, T_2$ ($1 < N \leq 5; 0 \leq M \leq \binom{N}{2}; 0 \leq R \leq 10^5; 0 \leq T_1, T_2 \leq 100$), $N$ is the number of existing offices, $M$ is the total number of cables between the existing offices, $R$ is the number of new office requests, $T_1$ and $T_2$ is the time a signal travels through an optical and a quantum cable, respectively.

The offices are labeled as $0, 1, \cdots, N-1$. Each of the next $M$ lines contains two integers $a$ and $b$ ($0 \leq a \neq b < N$) and a character “O” or “Q”. Integers determine the labels of the connected offices, the character determines the type of the cable which connects them (optical or quantum).

Next, there are $R$ lines, each of which represents one request to build a new office. The $i$-th request line (request counter $i$ starts from 0) contains two integers $a$ and $b$ ($0 \leq a \neq b < N+i$), the labels of the offices in which resides the requesting pair of detectives. It is assumed that the office occupied by the detective of Technical rank is always listed first. Furthermore, it is guaranteed that no request will be between two offices that share a direct connection.

## 输出格式

For each request in the input, print on a separate line the sum of distances from the Headquarters to all other offices that can be reached from the Headquarters by a sequence of connections.
## 样例

### 样例输入 #1
```

4 3 1 1 100
0 1 Q
1 2 Q
2 3 Q
3 
```
### 样例输出 #1
```
601
```
### 样例输入 #2
```

5 3 2 1 100
0 1 Q
1 2 O
3 4 O
0 2
5 4
```
### 样例输出 #2
```
302
806
```


---

---
title: "[GCPC 2023] Adolescent Architecture 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13666
tag: ['2023', 'ICPC']
---
# [GCPC 2023] Adolescent Architecture 2
## 题目描述

Three years ago, you helped little Peter stack his toy blocks into a tower. Since then, he has extended his collection of toy blocks, which now features the following base shapes:

- $\texttt{circle}\;a$ - a circle of radius $a$;
- $\texttt{square}\;a$ - a square with side length $a$;
- $\texttt{triangle}\;a$ - an equilateral triangle with side length $a$.

Here, $a$ may be any positive integer. The top shapes of each block are the same as their bottom shapes, so the blocks are cuboids, cylinders, and triangular prisms, respectively. Peter has an infinite supply of blocks of each shape and size.

![A game in progress.](https://cdn.luogu.com.cn/upload/image_hosting/u6yfox4n.png)

:::align{center}
Figure A.1: A game in progress.
:::

Peter and his friend Amy are playing a two-player game, where the blocks need to be stacked on top of each other.
Initially, some blocks are already placed on the floor.
In each move, the current player must take a toy block from the infinite supply and put it on top of one of the existing stacks of blocks.
The block may be rotated around its vertical axis before placing it.
The outline of the new block must be strictly within the outline of the old block; the outlines are not allowed to touch.
The first player who is unable to make a move loses the game.

Given the initial configuration, determine the number of winning moves for the first player.
## 输入格式

The input consists of:

- One line with an integer $n$ ($1 \le n \le 1000$), the number of initial stacks.
- $n$ lines, each with a string $s$ ($s$ is one of "$\texttt{circle}$", "$\texttt{square}$" or "$\texttt{triangle}$") and an integer $a$ ($1 \le a \le 10^9$), giving the topmost blocks of the initial stacks as described above.

## 输出格式

Output the number of winning moves for the first player.
## 样例

### 样例输入 #1
```
2
circle 2
triangle 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2
circle 1
circle 2
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
5
circle 123
triangle 456
square 789
square 789
triangle 555
```
### 样例输出 #3
```
7
```
### 样例输入 #4
```
3
circle 299303201
square 79724391
triangle 437068198
```
### 样例输出 #4
```
3
```
### 样例输入 #5
```
3
square 539715887
circle 518408351
triangle 348712924
```
### 样例输出 #5
```
0
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/mou2c2y4.png)

Figure A.2: Illustration of Sample Input 2, showing all possible end configurations of the game when Peter went first and played optimally to win. The blue blocks are the initial configuration. Peter needs to put one of $\texttt{circle\;1}$, $\texttt{square\;2}$ or $\texttt{triangle\;3}$ on top of $\texttt{circle\;2}$ in order to win. Each of these options corresponds to one row of the figure. Blocks placed by Peter are coloured in red, and blocks placed by Amy are coloured in yellow. As the last two blocks are always of type $\texttt{triangle\;1}$, they are shown in grey. If, for instance, Peter first puts $\texttt{circle\;1}$ (as depicted in the first row), then Peter can win by mirroring the following moves by Amy.





---

---
title: "[GCPC 2024] Fair Fruitcake Fragmenting"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13721
tag: ['计算几何', '2024', 'Special Judge', 'ICPC', '双指针 two-pointer']
---
# [GCPC 2024] Fair Fruitcake Fragmenting
## 题目描述

Frida's birthday is just coming up, and as her best friend, you obviously baked a cake for her.
Since you know that Frida loves rotational symmetry, you thought to bake a cake that
looks the same from above when rotated by $180^\circ$.
Of course, you could have simply baked a boring round cake, but without a perfectly round cake tin, this sounds easier than done.
Therefore, you decided to bake a cake whose shape can be described by straight line segments.

![](https://cdn.luogu.com.cn/upload/image_hosting/j4oo5c4y.png)

:::align{center}

Figure F.1: Visualization of Sample Input 2. The swirly cake looking like an S can be cut into the red and blue part with a single cut.

:::

However, after you are done with your cake, you notice that you also want to cut the cake into two equal pieces, one for Frida and one for yourself.
More precisely, you wonder if it is possible to cut the cake along an infinite line such that it splits into exactly two
parts of equal weight.
You can assume that the cake has uniform density and height.
## 输入格式

The input consists of:
- One line containing an *even* integer $n$ ($4 \leq n\leq 10^5$), the number of points needed to describe the cake's shape.
- $n$ lines, each containing two integers $x$, $y$ ($0\leq x,y \leq 10^6$), the $x$ and $y$ coordinates of a point on the border of the cake's shape.

The following additional guarantees are given for the shape of the cake:
- The cake has a $180^\circ$ rotational symmetry.
- The points are given in counterclockwise order.
- No three consecutive points are collinear.
- The shape is simple (no segments intersect and only consecutive segments touch at their ends).
## 输出格式

Output two different points on the desired line as $x_1/c_1$ $y_1/d_1$ $x_2/c_2$ $y_2/d_2$, where $|x_i|$, $|y_i|$, $|c_i|$ and $|d_i|$ are integers and at most $10^9$, and $x_i/c_i$} is the first coordinate of point $i$ and $y_i/d_i$ is the second ($1\leq i\leq2$). If the denominator of a fraction is $1$ you may output only the numerator. Fractions do not have to be reduced. If there is no such line, output "$\texttt{impossible}$" instead.

It can be shown that if there is a line as desired, it is possible to represent it in the given format.
## 样例

### 样例输入 #1
```
4
0 0
2 0
2 2
0 2
```
### 样例输出 #1
```
1 1 1337/42 3141/1000
```
### 样例输入 #2
```
20
7 1
8 2
8 5
7 6
4 6
4 4
3 4
3 7
6 7
7 8
2 8
1 7
1 4
2 3
5 3
5 5
6 5
6 2
3 2
2 1
```
### 样例输出 #2
```
11 13 -2 -4
```
### 样例输入 #3
```
10
11 5
10 2
12 6
2 2
7 3
1 1
2 4
0 0
10 4
5 3
```
### 样例输出 #3
```
impossible
```


---

---
title: "[CERC 2021] Building on the Moon"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13764
tag: ['2021', 'ICPC', 'CERC']
---
# [CERC 2021] Building on the Moon
## 题目描述

ICPC coaches never properly retire. When they announce their “retirement”, they actually start working for a secret agency (we are not allowed to disclose any further details) that builds monumental structures on the dark side of the Moon. There is currently one such project in progress.

To construct that monumental building they can use hexagonal building blocks of two different types:

* A chamber has three openings that are located on three of its mutually non-incident sides.
* A link has two openings that are located on two opposite sides.

Two links (or a link and a chamber) can be attached together along those sides that contain an opening; then those structures are welded together, so that they become airtight.

The plan is to construct a building that will comprise $N$ chambers on the Moon’s surface. Each of these chambers will be connected to exactly three other chambers via passages. Each passage is built by attaching together $L$ links. Each end (i.e. where the opening is located) of a passage is attached to a chamber. For example, suppose that there are $N = 4$ chambers labeled 1 to 4 and suppose that $L = 3$. A possible structure is shown in the figure (chambers are shaded gray):

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/n4ymvauc.png)
:::

It is guaranteed that any pair of chambers is connected by at most one passage and no passage is connecting a chamber to itself. Also, a person inside the building may reach any chamber from any other chamber via passages. Moreover, the plan was prepared by a former CERC coach, so it is guaranteed that passages do not intersect each other (remember that the structure will be built on the surface of the Moon). Such a plan may be described by a sequence of triples

$$\left(c_{1}^{(1)}, c_{2}^{(1)}, c_{3}^{(1)}\right),\left(c_{1}^{(2)}, c_{2}^{(2)}, c_{3}^{(2)}\right), \ldots,\left(c_{1}^{(n)}, c_{2}^{(n)}, c_{3}^{(n)}\right)$$

This means that chamber $i$ is connected to chambers $c_{1}^{(i)}, c_{2}^{(i)}$ and $c_{3}^{(i)}$. If a person is standing in chamber number $i$ and does a pirouette in the clockwise direction, that person

will see the passage to chamber $c_{1}^{(i)}$, followed by the passage to chamber $c_{2}^{(i)}$, and finally the passage to chamber $c_{3}^{(i)}$. The above plan can be described by the following sequence:

$$ (2,3,4),(1,4,3),(1,2,4),(1,3,2) $$

Since the the dark side of the Moon is dark (as the name conveniently suggests), a neon tube will be attached on each side of each building block (either a chamber or a link). Of course, a side where two building blocks are welded together will only have one neon tube. Because the structure will be on the Moon, we should not waste too much energy, so no two incident neon tubes should be lit at the same time. The coaches have decided that in order to provide sufficient lighting, they will light the maximum number of neon lights (with respect to the energy-saving constraint). Such a lighting will be called a valid lighting and may even be obtained in several ways. One possibility is shown in the following figure:

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/kvs30gsx.png)
:::

The coaches feel that there are many more ways to achieve this. They are now wondering what is the total number of valid lightings. Because they are too lazy to code it, they will prepare a task for a contest, so that students will come up with efficient solutions. Write a program that will read in the description of a monumental structure and determine the total number of valid lightings. Because the solution may be a huge number, output the answer modulo $10^6 + 3$.
## 输入格式

The first line contains space-separated integers $N$ and $L$, where $N$ is the number of chambers and $L$ is the number of links in each passage. This is followed by $N$ lines; the $i$-th line contains space-separated integers $c_{1}^{(i)}, c_{2}^{(i)}$ and $c_{3}^{(i)}$.

## 输出格式

Print a single integer: the total number of valid lightings modulo $10^6 + 3$.

## 样例

### 样例输入 #1
```
4 3
2 3 4
1 4 3
1 2 4
1 3 2
```
### 样例输出 #1
```
4400
```
## 提示

### Input limits

* $4 \leq N \leq 16$
* $1 \leq L \leq 100$
* $1 \leq c_{j}^{(i)} \leq N$ for $j = 1, 2, 3$ and $i = 1, 2, \ldots, N$


---

---
title: "[CERC 2021] Cactus cutting"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13765
tag: ['2021', 'ICPC', 'CERC']
---
# [CERC 2021] Cactus cutting
## 题目描述

Mr Malnar has given up on his tree obsession and found something even more interesting, cacti! Formally, a cactus is a connected graph where each edge is contained in at most one cycle. A cycle is defined as a sequence of more than one distinct edge in which every two consecutive edges share a common endpoint, and the first and last edge share a common endpoint as well.

Unfortunately, the cactus that Mr Malnar bought is rather big, so he would like to cut it up into disjoint sticks. One stick is defined as a pair of edges that share a common endpoint. Mr Malnar is a pedantic individual, so he wants to know the exact number of ways he can cut up his cactus into sticks.
## 输入格式

The first line contains the number of vertices $N$ and the number of edges $M$. This is followed by $M$ lines, each containing two distinct integers $A_{i}$ and $B_{i}$ denoting an edge between vertices $A_{i}$ and $B_{i}$. Each edge will be listed exactly once.
## 输出格式

Compute the number of distinct ways Mr Malnar can cut his cactus up into sticks. Since this number can get quite large, output the result modulo $10^6 + 3$.
## 样例

### 样例输入 #1
```
10 12
1 6
2 5
7 2
8 9
8 1
2 6
4 3
4 10
3 10
3 9
1 3
5 7
```
### 样例输出 #1
```
8
```
## 提示

### Input limits

- $1 \leq N, M \leq 100\,000$
- $1 \leq A_i, B_i \leq N$


---

---
title: "[CERC 2023] Attendance"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13845
tag: ['2023', 'ICPC', 'CERC']
---
# [CERC 2023] Attendance
## 题目描述

An ambitious university student has enrolled in just about every possible course. Unfortunately, the courses require mandatory attendance. He has decided to visit the university campus where the lectures are held several times a day. He will join every lecture that is running at that moment, sign the attendance sheet, and immediately leave the campus due to other obligations. He will return later that day, when he will repeat this process to sign attendance sheets at other lectures and so on until his name is on attendance sheets of all lectures.

As if this was not problematic enough, the student faces another obstacle: the schedule of the lectures keeps changing. Some lectures are added and some are canceled. The student has to keep adjusting his visiting schedule of the university to sign attendance sheets at all lectures.

Write a program that will start with an empty schedule of lectures and read sequential modifications, which are either an addition or removal of a single lecture. For every modification, output the minimum number of visits that the student has to make to sign attendance sheets at all lectures that are currently on the schedule.

## 输入格式

The first line contains the number of modifications $N$, which are given in the following $N$ lines. An addition of a lecture is described with two space-separated integers $A_i$ and $B_i$, which represent a lecture that is running from $A_i$ to $B_i$ (including both bounds). The lectures are numbered as they are added, sequentially from 1 onwards. A negative number $X_i$ represents a removal of lecture with the number $-X_i$.

## 输出格式

For every modification output a single line with the minimum number of required visits for the current schedule of lectures.
## 样例

### 样例输入 #1
```
12
2 2
17 26
-2
12 21
0 0
19 21
16 22
14 20
15 19
13 14
-4
13 17
```
### 样例输出 #1
```
1
2
1
2
3
3
3
3
3
4
3
3
```
## 提示

### Comment

The first lecture to be added is $[2, 2]$ and is given number 1. Next added lecture is $[17, 26]$ with number 2. It is removed immediately afterwards, which is indicated by $-2$ in the input. The following added lecture is $[12, 21]$, which is given number 3 and so on.

### Input limits

- $1 \leq N \leq 300\,000$
- $0 \leq A_i \leq B_i \leq 10^9$
- Every number of the lecture for removal $X_i$ will be valid – it will exist in the schedule at that moment.
- Note the memory limit.


---

---
title: "[CERC 2023] Phylogenetics"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13850
tag: ['2023', 'ICPC', 'CERC']
---
# [CERC 2023] Phylogenetics
## 题目描述

A young biologist is studying evolutionary history and has come across phylogenetic trees. A phylogenetic tree shows evolutionary relationships among various biological species. It is presented in a planar embedding with its leaves arranged in a circular manner for a better visual presentation. We are dealing with an unrooted tree, where the leaves are nodes of degree 1. All nodes of the tree are colored, which makes distinguishing different species easier.

Our biologist is using graph visualization software which needs some help to produce a desired layout. Therefore, she has decided to add edges between adjacent leaves in the planar embedding. The tree has at least 3 leaves, which she connects in a cycle. The illustration below shows an example of such (uncolored) tree with additional edges between adjacent leaves indicated by dashed lines.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/6psd85ey.png)
:::align

Now that the visualization is done, she is interested in the number of ways to color the nodes of this graph with $K$ colors. Every pair of adjacent nodes should have a different color for easier visual recognition. Write a program that will read the description of her graph structure and compute the number of colorings.
## 输入格式

The first line contains integers $N$, $M$ and $K$. The edges of the graph are given in the following $M$ lines as pairs of endpoints $A_i$ and $B_i$ (the nodes of the graph are numbered from 1 to $N$). All integers in the same line are separated by a space.

It is guaranteed that the graph was obtained from a planar embedding of a tree (acyclic connected undirected graph) by also connecting its leaves in a circular manner. The graph will not contain loops or parallel edges (i.e. multiple edges between the same pair of nodes).

## 输出格式

Output the number of colorings modulo $1\ 000\ 000\ 007$.
## 样例

### 样例输入 #1
```
8 12 3
2 5
3 6
2 6
5 4
4 1
1 6
7 5
2 7
3 4
2 8
7 8
1 8
```
### 样例输出 #1
```
24
```
## 提示

### Input limits

- $4 \leq N \leq 10^5$
- $1 \leq K \leq 10^5$


---

---
title: "[ICPC 2019 WF] Directing Rainfall"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6256
tag: ['2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Directing Rainfall
## 题目描述

Porto and the nearby Douro Valley are famous for producing port wine. Wine lovers from all over the world come here to enjoy this sweet wine where it is made. The International Consortium of Port Connoisseurs (ICPC) is organizing tours to the vineyards that are upstream on the Douro River. To make visits more pleasurable for tourists, the ICPC has recently installed sun tarps above the vineyards. The tarps protect tourists from sunburn when strolling among the vines and sipping on a vintage port.

Unfortunately, there is a small problem with the tarps. Grapes need sunlight and water to grow. While the tarps let through enough sunlight, they are entirely waterproof. This means that rainwater might not
reach the vineyards below. If nothing is done, this year's wine harvest is in peril!

The ICPC wants to solve their problem by puncturing the tarps so that they let rainwater through to the vineyards below. Since there is little time to waste before the rainy season starts, the ICPC wants to make the minimum number of punctures that achieve this goal. We will consider a two-dimensional version of this problem. The vineyard to be watered is an interval on the $x$-axis, and the tarps are modeled as line segments above the $x$-axis. The tarps are slanted, that is, not parallel to the $x-$ or $y-$ axes (see Figure F.1 for an example). Rain falls straight down from infinitely high. When any rain falls on a tarp, it flows toward the tarp's lower end and falls off from there, unless there is a puncture between the place where the rain falls and the tarp's lower end—in which case the rain will fall through the puncture instead. After the rain falls off a tarp, it continues to fall vertically.

This repeats until the rain hits the ground (the $x$-axis).

![](https://cdn.luogu.com.cn/upload/image_hosting/acu9ydhw.png)

For legal reasons you have to ensure that at least some of the rain that reaches the vineyard originated from directly above the vineyard. This is to prevent any vineyard from stealing all their rain from neighboring vineyards (see the second sample input for an example).
## 输入格式

The first line of input contains three integers $l$ , $r$ and $n$, where $(l,r)$ $(0 \leq l \lt r \leq 10^9)$ is the interval representing the vineyard and $n$ $(0 \leq n \leq 5 \times 10^5)$ is the number of tarps. Each of the following $n$ linesdescribes a tarp and contains four integers $x_1, y_1, x_2, y_2$ , where $(x_1, y_1)$ is the position of the tarp's lowerend and $(x_2, y_2)$ is the position of the higher end $(0 \leq x_1, x_2 \leq 10^9 , x_1≠x_2, $ and $ 0 \lt y_1 \lt y_2 \leq 10^9)$.
The $x$-coordinates given in the input ($l$, $r$, and the values of $x_1$ and $x_2$ for all tarps) are all distinct. Thetarps described in the input will not intersect, and no endpoint of a tarp will lie on another tarp.
## 输出格式

Output the smallest number of punctures that need to be made to get some rain falling from above the vineyard to the vineyard.
## 样例

### 样例输入 #1
```
10 20 5
32 50 12 60
30 60 8 70
25 70 0 80
15 30 28 40
5 20 14 25

```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2 4 2
3 2 0 3
5 2 1 5
```
### 样例输出 #2
```
1
```
## 提示

Source: ICPC World Finals 2019 Problem F: Directing Rainfall.
## 题目翻译

波尔图和附近的杜罗河谷以生产波尔图葡萄酒而闻名。来自世界各地的葡萄酒爱好者来到这里，在这里品尝酿制的甜酒。国际港口鉴赏家协会（ICPC）正在组织参观杜罗河上游的葡萄园。为了让游客更愉快地参观，ICPC最近在葡萄园上方安装了防晒布。当游客漫步在藤蔓间，在一个古老的港口啜饮时，防水布可以保护他们免受晒伤。

不幸的是，防水布有一个小问题。葡萄生长需要阳光和水。虽然防水油布能让足够的阳光透过，但它们是完全防水的。这意味着雨水可能无法到达下面的葡萄园。如果不采取任何行动，今年的葡萄酒收成将岌岌可危！

ICPC希望通过刺穿防水布来解决他们的问题，这样他们可以让雨水通过下面的葡萄园。由于雨季开始前几乎没有时间可以浪费，ICPC希望实现这一目标的穿刺次数最少。我们将考虑这个问题的二维版本。要浇水的葡萄园是xx轴上的一个间隔，防水布被建模为xx轴上方的线段。防水布是倾斜的，也就是说，与x-x不平行−还是y-y−轴（示例见图F.1）。雨从无限高的地方直下。当任何雨水落在防水油布上时，雨水会流向防水油布的下端并从那里落下，除非雨水落下的地方和防水油布的下端之间有一个小孔，在这种情况下，雨水会通过小孔落下。雨水从防水布上落下后，继续垂直下落。

这将重复进行，直到雨水落在地面上（xx轴）。


---

---
title: "[ICPC 2019 WF] Traffic Blights"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6261
tag: ['2019', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Traffic Blights
## 题目描述

Cars! Where do they come from? Where do they go? Nobody knows. They appear where roads have been built, as if out of nowhere. Some say that no two cars are alike. Some say that if you look closely, you can see the pale ghosts of miserable humans inside them, trapped forever—particularly in
the morning and late afternoon. What scientific eye could frame their fearful symmetry?

Well, yours, hopefully. As part of your government's Urban Traffic Control department, you are trying to write a paper on local traffic congestion. It is too dangerous to observe cars in the wild, of course, but you have been given some data on the traffic lights along your town's Main Street, and you would like to do some theoretical calculations about how well-synchronized they are.

Main Street is set out on a line, with traffic lights placed at various points along it. Each traffic light cycles between red and green with a fixed period, being red for $r$ seconds, then green for $g$ seconds, then red for $r$ seconds, and so on. The values of $r$ and $g$ may be different for different traffic lights. At time $0$, all the lights have just turned red.

Assume that an "ideal" car mystically appears at the west end of Main Street at a uniformly random real-valued time in the interval $[0, 2019!]$ (where $k!$ is the product of the first $k$ positive integers), driving eastwards at a slow crawl of $1$ meter/second until it hits a red light. What is the probability that it will make it through all the lights without being forced to stop? If it does hit a red light, which one is it likely to hit first?

Write a program to answer these questions.
## 输入格式

The first line of input contains an integer $n$ ($1 \leq n \leq 500$), the number of traffic lights. Each of the following $n$ lines contains three integers $x$, $r$, and $g$ describing a traffic light, where $x$ ($1 \leq x \leq 10^5$) is the position of the light along Main Street in meters, and $r$ and $g$ ($0 \leq r, g$ and $1 \leq r + g \leq 100$) are the durations in seconds of the red and green portions of the light's period (so the light is red from time $0$ to $r$, from time $r + g$ to $2r + g$, and so on).

The west end of Main Street is at position $0$, and the lights are listed in order of strictly increasing position.
## 输出格式

For each of the $n$ lights, output a line containing the probability that this light will be the first red light an "ideal" car hits. Then output a line containing the probability that an "ideal" car makes it all the way without stopping. Your answers should have an absolute error of at most $10^-6$.
## 样例

### 样例输入 #1
```
4
1 2 3
6 2 3
10 2 3
16 3 4
```
### 样例输出 #1
```
0.4
0
0.2
0.171428571429
0.228571428571
```
### 样例输入 #2
```
6
4 1 5
9 8 7
13 3 5
21 5 7
30 9 1
2019 20 0
```
### 样例输出 #2
```
0.166666666667
0.466666666667
0.150000000000
0.108333333333
0.091666666667
0.016666666667
0.000000000000
```
## 提示

Source: ICPC 2019 World Finals.
## 题目翻译

### 题目描述

Main 街坐落在一条东西向的直线上，上面有若干位置互异的红绿灯。每个红绿灯以某个固定周期在红绿之间循环。更具体地，它会先持续 $r$ 秒的红灯，再持续 $g$ 秒的绿灯，再持续 $r$ 秒的红灯...如此往复。对于不同的红绿灯，$r$ 和 $g$ 的值可能不同。在时刻 $0$，所有的红绿灯都恰好刚变为红灯。

假设此时有一辆“理想”汽车在前 $2019!$ 秒中的一个随机实数时刻神秘地出现在了 Main 街的最西端，向东以 $1~ \rm m/s$ 龟速行驶，直到遇到第一个红灯时停下，那么它有多大的概率通过所有红绿灯？如果它停下来了，那么它在每个红绿灯处停下的概率有多大？

### 输入格式

第一行一个整数 $n$（$1\le n\le 500$） 表示红绿灯的数量。

接下来每行三个整数 $x,r,g$（$1\le x \le 10^5$，$0\le r,g$ 且 $1\le r+g\le 100$）， 描述一个位置在从西往东 $x$ 米处的，红灯持续时间为 $r$，绿灯持续时间为 $g$ 的红绿灯。

最西侧即 $x=0$ 处，保证 $x$ 严格递增。

### 输出格式

前 $n$ 行第 $i$ 行每行输出一个实数表示在第 $i$ 个红绿灯停下的概率。

第 $n + 1$ 行输出一个实数表示通过所有红绿灯的概率。

你需要保证绝对误差不超过 $10^{-6}$.


---

---
title: "[ICPC 2014 WF] Baggage"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6892
tag: ['2014', 'Special Judge', '构造', 'ICPC']
---
# [ICPC 2014 WF] Baggage
## 题目描述

An airline has two flights leaving at about the same time from ICPCity, one to city B and one to city A. The airline also has $n$ counters where passengers check their baggage. At each counter there is a pair of identical baggage bins, one for city B and one for city A.

Just before the flights depart, each pair of baggage bins is moved by a motorized cart to a sorting area. The cart always moves two bins at a time, one for city B and one for city A. After all the bins have been moved, they line up in the sorting area like this:

  B A B A B A ... B A 

That is, there are $2n$ baggage bins in a row, starting with a bin for city B, then one for city A, and so forth. The task now is to reorder them so all the baggage bins for city A precede the baggage bins for city B. Then the bins can be loaded on the appropriate aircraft.

The reordering is done by moving pairs of adjacent baggage bins (not necessarily B then A), again via the motorized cart. For proper balance, the cart must always carry two bins, never just one. A pair of bins must always be moved to an empty space that is at least two bins wide. On the left of the first bin are some empty spaces that can be used as needed during the reordering.

When the reordering process begins, the bin locations are numbered from $1$ (initially containing the leftmost B baggage bin) to $2n$ (initially containing the rightmost A baggage bin). There are $2n$ initially empty spaces to the left of the bins, numbered from $0$ to $-2n+1$, as shown in Figure 1 for the case $n=4$.
![](https://cdn.luogu.com.cn/upload/image_hosting/fwkcv2gq.png)

   Figure 1: Initial configuration of bins and empty spaces for $n = 4$ 

Given $n$, find a shortest sequence of moves that will reorder the bins so that all the A bins are to the left of all the B bins. At the end of the process, it is possible that the leftmost A bin is at some location other than $1$, but the bins must be adjacent in a sequence of $2n$ locations.
## 输入格式

The input consists of a single test case, which consists of the integer $n$ $(3 \leq n \leq 100)$.
## 输出格式

Display a shortest sequence of moves that will correctly reorder the bins. Each move is of the form “$f$ to $t$”, where $f$ and $t$ are integers representing the movement of the bins in locations $f$ and $f + 1$ to locations $t$ and $t + 1$. If multiple solutions are possible, display any one of them.
## 样例

### 样例输入 #1
```
5

```
### 样例输出 #1
```
8 to -1
3 to 8
6 to 3
0 to 6
9 to 0

```
### 样例输入 #2
```
8

```
### 样例输出 #2
```
10 to -1
3 to 10
14 to 3
7 to 14
0 to 7
11 to 0
4 to 11
15 to 4

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

有一无穷长的流水线 $a$，初始时 $\forall i\le0\text{ 和 } i>2n ,a_i=0$。**否则**，若 $i$ 为奇数，则 $a_i=2$；若 $i$ 为偶数，则 $a_i=1$。**也就是说，$a_i=2$ 和 $a_i=1$ 是交替出现的。**  

现需要进行若干次 **如下** 操作，使得 $a$ 中的所有 **非零元素** 为 **连续** 的一段且所有的 $1$ 均在 $2$ **前面**。  

选择两个位置 $p$ 和 $q$，满足 $a_p\ne0,a_{p+1}\ne0$ 且 $a_q=a_{q+1}=0$，将 $a_q$ 设为 $a_p$，$a_{q+1}$ 设为 $a_{p+1}$，并且将 $a_p$ 和 $a_{p+1}$ 均设为 $0$。**输出时将此操作表示为 ```p to q```（$p$  和 $q$ 是具体的值）**。  

最小化操作步数，并输出操作序列，出题人将用 $\text{Special Judge}$ 来评判您的答案的正确性。  


---

---
title: "[ICPC 2014 WF] Messenger"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6897
tag: ['计算几何', '2014', '二分', 'Special Judge', 'ICPC']
---
# [ICPC 2014 WF] Messenger
## 题目描述

Misha needs to send packages to his friend Nadia. Both of them often travel across Russia, which is very large. So they decide to hire a messenger. Since the cost of the messenger service depends on the time it takes to deliver the package, they need your help to optimize a little bit.

Assume Misha and Nadia move on a two-dimensional plane, each visiting a sequence of places and moving along straight line segments from place to place. Your task is to find the shortest possible delivery time given their two paths.

Misha hands the package to the messenger at some point along his path. The messenger moves without delay along a straight line from the pick-up to intercept Nadia, who is traveling along her path. Misha, Nadia and the messenger move with a constant speed of $1$ distance unit per time unit. The delivery time is the time between Misha handing over the package and Nadia receiving it.
## 输入格式

The input consists of a single test case. The test case contains two path descriptions, the first for Misha and the second for Nadia. Each path description starts with a line containing an integer $n$, the number of places visited ($2 \leq n \leq 50\, 000$). This is followed by $n$ lines, each with two integers $x_ i$ and $y_ i$ specifying the coordinates of a place ($0 \leq x_ i, y_ i \leq 30\, 000$). Coordinates of the places are listed in the order in which they are to be visited, and successive places do not have the same coordinates.

Misha and Nadia start their journeys at the same time, visiting the places along their paths without stopping. The length of each path is at most $10^6$. The package must be picked up at the latest when Misha reaches his final place and it must be delivered at the latest when Nadia reaches her final place.
## 输出格式

Display the minimal time needed for delivery. Give the answer with an absolute error of at most $10^{-3}$ or a relative error of at most $10^{-5}$. If the package cannot be delivered, display impossible instead.
## 样例

### 样例输入 #1
```
2
0 0
0 10
2
4 10
4 0

```
### 样例输出 #1
```
4.00000

```
### 样例输入 #2
```
2
0 0
1 0
3
2 0
3 0
3 10

```
### 样例输出 #2
```
5.00000

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

题目描述：  
平面上有两个移动的点 A,B，其中 A 想要向 B 发送一条信息。两个点会同时出发，各自沿着一个折线移动到终点为止。A 会在移动的途中发送一条信息，这条信息可以视作一个点 C，它会沿一条射线匀速运动，当 C 与 B 重合时，B 即可收到该信息。

A,B,C 的移动速度都是 1 单位长度每秒，A 最晚在它到达终点时发出信息，B 最晚需要在它到达终点时收到信息。令 $t_A$ 代表发送信息的时间，$t_B$ 代表接收信息的时间，那么你需要最小化 $t_B-t_A$ 的值。特别地，如果 B 无论如何都无法收到信息，你需要输出 `impossible`。

输入格式：

第一行包含一个整数 $n$，代表 A 经过折线的点数；  
下面 $n$ 行，每行输入两个整数 $x_i,y_i$，依次描述 A 所走折线的点。  
下面一行包含一个整数 $m$，B 过折线的点数；  
下面 $m$ 行，每行输入两个整数 $u_i,v_i$，描述 B 所走折线。

输出格式：

一行，输出一个实数，代表答案。若无法满足，则输出`impossible`。


---

---
title: "[ICPC 2014 WF] Metal Processing Plant"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6898
tag: ['2014', '2-SAT', 'ICPC']
---
# [ICPC 2014 WF] Metal Processing Plant
## 题目描述

Yulia works for a metal processing plant in Ekaterinburg. This plant processes ores mined in the Ural mountains, extracting precious metals such as chalcopyrite, platinum and gold from the ores. Every month the plant receives $n$ shipments of unprocessed ore. Yulia needs to partition these shipments into two groups based on their similarity. Then, each group is sent to one of two ore processing buildings of the plant.

To perform this partitioning, Yulia first calculates a numeric distance $d(i, j)$ for each pair of shipments $1 \le i \le n$ and $1 \le j \le n$, where the smaller the distance, the more similar the shipments $i$ and $j$ are. For a subset $S \subseteq \{ 1, \ldots , n\} $ of shipments, she then defines the disparity $D$ of $S$ as the maximum distance between a pair of shipments in the subset, that is,

$$ D(S) = \max _{i, j \in S} d(i, j). $$

Yulia then partitions the shipments into two subsets $A$ and $B$ in such a way that the sum of their disparities $D(A) + D(B)$ is minimized. Your task is to help her find this partitioning.
## 输入格式

The input consists of a single test case. The first line contains an integer $n$ ($1 \le n \le 200$) indicating the number of shipments. The following $n - 1$ lines contain the distances $d(i,j)$. The $i^{th}$ of these lines contains $n - i$ integers and the $j^{th}$ integer of that line gives the value of $d(i, i+j)$. The distances are symmetric, so $d(j, i) = d(i, j)$, and the distance of a shipment to itself is $0$. All distances are integers between $0$ and $10^9$ (inclusive).
## 输出格式

Display the minimum possible sum of disparities for partitioning the shipments into two groups.
## 样例

### 样例输入 #1
```
5
4 5 0 2
1 3 7
2 0
4

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
7
1 10 5 5 5 5
5 10 5 5 5
100 100 5 5
10 5 5
98 99
3

```
### 样例输出 #2
```
15

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

**题目描述**

尤利娅在叶卡捷琳堡的一家金属加工厂工作。该工厂在乌拉尔山脉提取矿石中的铜、铂和金。工厂每月收到 $n$ 批未经处理的矿石。尤利娅需要对这些货物进行分割为两组。然后它们会分别被送到工厂的两个冶矿塔。

首先，尤利娅对每对货物 $i,j(1\leq i,j\leq n)$ 给出一个$d_{i,j}$，对于子集 $S$，$D(S)$ 定义为 $\max\limits_{(i,j\in S)}\{d_{(i,j)}\}$。

然后，尤利娅将货物分成 $A$ 和 $B$ 两部分，使 $D(A)+D(B)$ 最小。请你帮助她找到划分方法。

**输入格式**

输入包括多组数据。
对于每组测试数据：
第一行包含一个整数 $n(1\leq n\leq 200)$，表示发货数量。接下来 $n-1$ 行每行有 $n-i$ 个数，第 $j$ 个数表示 $d_{i,i+j}$。且 $d_{j,i}=d_{i,j},d_{i,i}=0$。

**输入格式**

对于每组测试数据，输出 $D(A)+D(B)$ 的最小值。




---

---
title: "[ICPC 2014 WF] Pachinko"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6899
tag: ['数学', '2014', 'Special Judge', '期望', 'ICPC']
---
# [ICPC 2014 WF] Pachinko
## 题目描述

You have been hired by Addictive Coin Machines to help design the next hit in their line of eye-catching, coin-guzzling, just-one-more-try Pachinko machines for casinos around the world.

Playing a Pachinko machine involves launching balls into a rectangular grid filled with pegs, obstacles, and targets. The ball bounces around the grid until it eventually hits one of the targets. The player earns a certain number of points depending on which target is hit.

The grid pattern for the next Pachinko machine has already been designed, but point values for the targets have not been assigned. These must be set so that like all casino machines, the machine is profitable but not too profitable. Thus it is important to figure out the probability of a ball hitting any particular target. That’s your job!

For simplicity, the grid is modeled as a tall rectangle filled with mostly-open spaces (each represented by ‘.’), impassable obstacles (each represented by ‘X’), and targets (each represented by ‘T’).

A ball is launched randomly with uniform probability into one of the mostly-open spaces on the top row of the grid. From that point on, collisions with pegs cause the ball to randomly bounce up, down, left, or right, with various given probabilities. For simplicity, assume these probabilities are the same for every space in the grid. If the ball bounces into an obstacle or attempts to move off the grid, it won’t actually move from its current space. When the ball moves into a target it is removed from play.

You can safely assume that the average number of spaces visited by a ball before hitting a target will not exceed $10^{9}$. It would not make for a very enjoyable game if the ball just bounces forever!

For each target, calculate the probability that it is the one hit by a launched ball.
## 输入格式

The input consists of a single test case. The first line contains integers $w$ and $h$, which are the width and height of the Pachinko grid ($1 \leq w \leq 20$ and $2 \leq h \leq 10\, 000$). The next line contains four non-negative integers $u$, $d$, $l$, and $r$, which sum to 100 and are the percentage probabilities of the ball bouncing up, down, left, or right from any open space.

Each of the next $h$ lines contains $w$ characters, each of which is ‘.’, ‘X’, or ‘T’. These lines describe the Pachinko grid. The first line, which describes the top row of the grid, contains at least one ‘.’ and no ‘T’s.
## 输出格式

Display one line for each ‘T’ in the grid, in order from top to bottom, breaking ties left to right. For each target, display the probability that a launched ball will hit it. Give the answer with an absolute error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
3 2
20 20 20 40
X.X
T.T

```
### 样例输出 #1
```
0.333333333
0.666666667

```
### 样例输入 #2
```
4 5
12 33 28 27
....
.XX.
....
T..T
XTTX

```
### 样例输出 #2
```
0.435853889
0.403753221
0.081202502
0.079190387

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

**题目描述**

有一个宽度为 $w$ 高度为 $h$ 的方格纸， $ w \times h$ 的格子中，有一些是空的，有一些是洞，有一些是障碍物。从第一行的空的格子中随机选一个放置一个球，向上下左右移动的概率比为 $p_u : p_d : p_l : p_r$（满足 $p_u + p_d + p_l + p_r = 100$），不能移动到有障碍物的格子上。对于每个洞，输出落入该洞的概率。$w \le 20, h \le 10000$。保证第一行没有洞。

**输入格式**

第一行两个整数表示 $w, h$ 。

第二行四个整数表示 $p_u, p_d, p_l, p_r$ 。

接下来有一个 $h$ 行 $w$ 的字符矩阵，其中 `.` 表示空，`X` 表示障碍物，`T` 表示洞。

**输出格式**

若干行，每一行一个整数，按照矩阵从上到下，从左到右的顺序，输出每个洞的答案。绝对误差不超过 $10^{-6}$ 即为正确。


---

---
title: "[ICPC 2014 WF] skiing"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6901
tag: ['2014', 'ICPC']
---
# [ICPC 2014 WF] skiing
## 题目描述

As you know, the ACM ICPC is not the only major sporting event taking place in Russia this year. Several months ago, the 2014 Winter Olympics were held in Sochi, which is about 3 000 km from Ekaterinburg.

In an increasing number of sports, it is not only the ability of the athletes that determines who wins a competition but also their equipment. For example in downhill skiing, having the latest ski technology enables athletes to increase their speeds and improve their turning ability.

You have been hired to determine the effect of the latest ski technology on the ability of skiers to navigate a downhill course. The course contains several target locations, and the skier wants to pass over as many of them as possible. Naturally, the better the ski technology, the easier it will be to do this.

For simplicity, use a two-dimensional coordinate system where the skier starts at position (0,0) and where “downhill” corresponds to the direction of the positive $y$-axis.

Assume the $y$-component of the athlete’s velocity is a constant $v_ y$. The athlete can change speed laterally (in the $x$-direction), but the skiing equipment limits this to a maximal lateral acceleration $a_{max}$. The skier starts with a lateral velocity of 0.

![](https://cdn.luogu.com.cn/upload/image_hosting/us59dhj8.png)

   Figure 1: Downhill ski path passing over three targets 

In Figure 1 (which corresponds to the first sample input), the optimal path passes over three out of four possible targets. If $a_{max}$ were smaller, then the skier might be able to pass over only two or fewer of the targets.
## 输入格式

The input contains a single test case. The first line contains three integers $n$, $v_ y$, and $a_{max}$ ($0 \leq n \leq 250$, $0 < v_ y \leq 10^5$ and $0 \leq a_{max} \leq 10^7$), where $n$ is the number of targets, $v_ y$ is the $y$-component of the skier’s velocity, and $a_{max}$ is the maximum lateral acceleration. Here $v_ y$ is given in meters per hour and $a_{max}$ in meters per hour squared.

Following this are $n$ lines, each containing two integers $x_ i$ and $y_ i$ ($-10^5 \leq x_ i, y_ i \leq 10^5$). These give the coordinates of each target to be visited on the course. All coordinates are given in meters. Targets are numbered 1, 2, ..., $n$ in the order they are given.
## 输出格式

Display the maximal-length sequence of targets that the athlete could pass over on the course in a single run. Display the targets in the order they are visited. If there are multiple maximal-length sequences, display only the lexicographically first one. (So the sequence 2 15 would come before the sequence 10 15.) If the athlete cannot pass over any targets, print Cannot visit any targets instead.

To ensure floating-point stability, you may assume the answer will not change if $a_{max}$ is perturbed by up to 0.1.
## 样例

### 样例输入 #1
```
4 100 400
-100 100
50 200
-100 300
150 300

```
### 样例输出 #1
```
1 2 4

```
### 样例输入 #2
```
1 100 100
1000 10

```
### 样例输出 #2
```
Cannot visit any targets

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

**题目描述**

滑雪运动员进行的一次训练可以看作平面上一条从 $(0, 0)$ 出发的曲线，这条曲线在 $y$ 轴正方向上的**速度**是 $v_y$，由于装备限制，在 $x$ 轴上的**加速度**不得超过 $a_{max}$。滑雪运动员在 $x$ 轴上的速度从 $0$ 开始。

在这一次训练中，滑雪运动员需要经过所有 $n$ 个目标点 $(x_i, y_i)$ 中尽可能多的目标点，现在他希望你通过控制他每一时刻的加速度，实现这个目标。

**输入格式**

第一行三个整数 $n, v_y, a_{max}$ 分别表示目标点数，$y$ 轴速度（米每秒）以及 $x$ 轴加速度上限（米每二次方秒）。

接下来 $n$ 行每行两个整数 $x, y$ 表示目标点的横坐标（米）以及纵坐标（米）。

**输出格式**

按照目标点被经过的顺序输出最长的目标点序列。若有多个可能的答案，输出字典序最小的。若运动员不能经过任意一个目标点，输出 `Cannot visit any targets`。

为了避免浮点误差，你可以假设对 $a_max$ 进行不超过 $0.1$ 的扰动的情况下，答案不变。

**数据范围**

$0\le n\le 250, 0\le v_y\le 10^5
, 0\le a_{max}\le 10^7
, −10^5\le x, y\le 10^5$
, 目标点编号从 1 开始。

~~一句话の题意：输入一些数，输出一些数（或字符串），使输出符合要求。~~


---

---
title: "[ICPC 2014 WF] Wire Crossing"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6903
tag: ['计算几何', '2014', '平面图', 'ICPC']
---
# [ICPC 2014 WF] Wire Crossing
## 题目描述

Moore’s Law states that the number of transistors on a chip will double every two years. Amazingly, this law has held true for over half a century. Whenever current technology no longer allowed more growth, researchers have come up with new manufacturing technologies to pack circuits even denser. In the near future, this might mean that chips are constructed in three dimensions instead two. But for this problem, two dimensions will be enough.

A problem common to all two-dimensional hardware design (for example chips, graphics cards, motherboards, and so on) is wire placement. Whenever wires are routed on the hardware, it is problematic if they have to cross each other. When a crossing occurs special gadgets have to be used to allow two electrical wires to pass over each other, and this makes manufacturing more expensive.

Our problem is the following: you are given a hardware design with several wires already in place (all of them straight line segments). You are also given the start and end points for a new wire connection to be added. You will have to determine the minimum number of existing wires that have to be crossed in order to connect the start and end points. This connection need not be a straight line. The only requirement is that it cannot cross at a point where two or more wires already meet or intersect.

  ![](https://vj.z180.cn/df2653f5a1b23d354dbe2e33d6438ea6?v=1602904232) 

   Figure 1: First sample input 

Figure 1 shows the first sample input. Eight existing wires form five squares. The start and end points of the new connection are in the leftmost and rightmost squares, respectively. The black dashed line shows that a direct connection would cross four wires, whereas the optimal solution crosses only two wires (the curved blue line).
## 输入格式

The input consists of a single test case. The first line contains five integers $m, x_0, y_0, x_1, y_1$, which are the number of pre-existing wires ($m \le 100$) and the start and end points that need to be connected. This is followed by $m$ lines, each containing four integers $x_ a, y_ a, x_ b, y_ b$ describing an existing wire of non-zero length from $(x_ a, y_ a)$ to $(x_ b,y_ b)$. The absolute value of each input coordinate is less than $10^5$. Each pair of wires has at most one point in common, that is, wires do not overlap. The start and end points for the new wire do not lie on a pre-existing wire.
## 输出格式

Display the minimum number of wires that have to be crossed to connect the start and end points.
## 样例

### 样例输入 #1
```
8 3 3 19 3
0 1 22 1
0 5 22 5
1 0 1 6
5 0 5 6
9 0 9 6
13 0 13 6
17 0 17 6
21 0 21 6

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
1 0 5 10 5
0 0 10 10

```
### 样例输出 #2
```
0

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

#### 题意简述
给定出发点，终止点和平面上的 $m$ 条线段，线段用两个端点表示，

求从出发点到终止点的连线(形状任意)最少要与线段相交多少次，多次经过一条线段要多次计数。

数据保证任意两条线段最多只有一个交点，注意连线不能经过交点，且线段可能是斜线。

坐标的绝对值不超过 $10^5$


---

---
title: "[ICPC 2015 WF] Asteroids"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6905
tag: ['2015', 'Special Judge', 'ICPC']
---
# [ICPC 2015 WF] Asteroids
## 题目描述

The year is 2115. The asteroid communication relay system was set up a decade ago by the Asteroid Communication Ministry. It is running fine except for one small problem – there are too many asteroids! The smaller ones not only keep interfering with the signals from the relay stations but they are also a danger to all the maintenance aircrafts that fly between the stations. These small asteroids must be destroyed! The Interplanetary Coalition to Prevent Catastrophes (ICPC) has been charged with removing these dangerous asteroids and has hired an elite team of hot-shot pilots for the job. Han Duo is the captain of this team of asteroid destroyers. Armed with his missiles, Han flies through the asteroid belt blowing up any asteroid that the ICPC deems a nuisance.

The ICPC is having some unfortunate budgetary problems. One result of this is that Han and his team do not have as many missiles as they would like, so they cannot blow up all the troublesome asteroids. But the asteroids are small and the missiles are powerful. So if two asteroids are near each other and line up properly, it is possible to take out both with a single missile.

Han’s screen displays asteroids as non-rotating two-dimensional simple convex polygons, each of which moves at a fixed velocity. He has decided that the best time to hit two asteroids is when the overlap of the two polygons is at a maximum. For example, Figure 1, which illustrates Sample Input 1, shows two asteroids and snapshots of their subsequent positions at 1-second intervals. The two asteroids start touching after $3$ seconds and the maximum overlap area occurs between $4$ and $5$ seconds.

  ![](https://vj.z180.cn/c0ee84911e97a539823bc119cb23e0d7?v=1603764626) 

   Figure 1: Sample Input 1. Two asteroids with crossing paths. 

Calculating when the maximum overlap occurs for two asteroids requires a bit of programming, but unfortunately Han slept through most of his coding classes at the flight academy. This is where you come in.
## 输入格式

The input consists of two asteroid specifications. Each has the form $n\; x_{1}\; y_{1}\; x_{2}\; y_{2}\; \ldots \; x_{n}\; y_{n}\; v_{x}\; v_{y}$ where $n$ $(3 \le n \le 10)$ is the number of vertices, each $x_{i}, y_{i}$ ($-10\, 000 \le x_{i}, y_{i} \le 10\, 000$) are the coordinates of a vertex of the asteroid on Han’s screen given in clockwise order, and $v_{x}, v_{y}$ ($-100 \le v_{x}, v_{y} \le 100$) are the $x$ and $y$ velocities (in units/second) of the asteroid. The $x_{i}$, $y_{i}$ values specify the location of each asteroid at time $t=0$, and the polygons do not intersect or touch at this time. The maximum length of any side of an asteroid is $500$. All numbers in the input are integers.
## 输出格式

Display the time in seconds when the two polygons have maximum intersection, using the earliest such time if there is more than one. If the two polygons never overlap but touch each other, treat it as an intersection where the common area is zero and display the earliest such time. If the polygons never overlap or touch, display never instead. You should consider positive times only. Your output should have an absolute or relative error of at most $10^{-3}$.
## 样例

### 样例输入 #1
```
6 3 2 2 4 3 6 6 6 7 4 6 2 2 2
4 18 5 22 9 26 5 22 1 -2 1

```
### 样例输出 #1
```
4.193518

```
### 样例输入 #2
```
4 0 0 0 2 2 2 2 0 -1 1
4 10 0 10 2 12 2 12 0 1 1

```
### 样例输出 #2
```
never

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
 
spj provider:@[shenyouran](/user/137367).
## 题目翻译

## 题目背景
今年是2115年。小行星通信中继系统是十年前由小行星通信部建立的。有一个小问题——小行星太多，它们很危险！比较小的小行星不仅不断干扰中继站的信号，而且对在中继站之间飞行的所有维修飞机也是一种危险。这些小行星必须被摧毁！防止危险的星际联盟（ICPC）已被下达移除这些危险的小行星的指令，并请了一支精英团队来完成这项工作。Han Duo 是这个小行星驱逐舰小组的队长。Han Duo 带着他的导弹飞过小行星带，炸毁了 ICPC 认为的令人讨厌的任何小行星。

ICPC 没那么多钱。后果是 Han Duo 和他的团队没有他们想要的那么多导弹，因此他们无法炸毁所有麻烦的小行星。但是小行星很小，导弹也很强大。因此，如果两颗小行星彼此靠近并正确排列，就有可能用一枚导弹将两者都摧毁。

Han Duo 的屏幕将小行星显示为非旋转的二维简单凸多边形，每个多边形都以固定速度移动。他认为撞击两颗小行星的最佳时间是两个多边形的重叠达到最大值时。例如，图1演示了样例输入1，显示了两颗小行星及其后续的位置，间隔1秒。两颗小行星在33秒后开始接触，最大重叠区域出现在44到55秒之间。

图1：样例输入1。两颗有交叉路径的小行星。

计算两颗小行星的最大重叠时间需要计算机来完成，但不幸的是，Han Duo 在飞行学院的大部分程序设计课中都在睡大觉。现在把这个任务交由你。

## 输入格式

输入包括两个小行星规格。每个形式为 $n, x_1, y_1 ,x_2，y_2  $ $… $ $x_n ,y_n ,v_x, v_y$ 其中 $n$$(3$$\le n \le10)$  是顶点的数量，每个 $x_i,y_i(-10000$$\leq x_i,y_i \leq$$1000)$ 在屏幕上按顺时针顺序给出的小行星顶点的坐标，$v_x，v_y(-100 \le v_x,v_y \le 100)$ 是小行星的$x$和$y$速度（单位/秒）$x,y$ 值代表 $t=0$ 时每个小行星的位置，此时多边形不相交或接触。小行星任意一侧的最大长度为 $500$。输入中的所有数字都是整数。

## 输出格式

以秒为单位输出两个多边形具有最大相交的时间，如果存在多个多边形，则使用最早的时间。如果两个多边形从不重叠，而是彼此接触，则将其视为公共面积为零的交点，并输出最早的时间。如果多边形从不重叠或接触，则输出“never”。你应该只考虑确定的时候。输出的绝对或相对的误差应不超过$10^{-3}$。

## 说明/提示

时间限制：2000毫秒，内存限制：1048576 kB。

2015年国际大学生编程大赛（ACM-ICPC）世界总决赛


---

---
title: "[ICPC 2015 WF] Pipe Stream"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6910
tag: ['2015', 'ICPC']
---
# [ICPC 2015 WF] Pipe Stream
## 题目描述

 ![](https://vj.z180.cn/ba87a214c6b94e2e93a88f7b226c2064?v=1602042036)  

Your hometown has hired some contractors – including you! – to manage its municipal pipe network. They built the network, at great expense, to supply Flubber to every home in town. Unfortunately, nobody has found a use for Flubber yet, but never mind. It was a Flubber network or a fire department, and honestly, houses burn down so rarely, a fire department hardly seems necessary. 

In the possible event that somebody somewhere decides they want some Flubber, they would like to know how quickly it will flow through the pipes. Measuring its rate of flow is your job.

You have access to one of the pipes connected to the network. The pipe is $l$ meters long, and you can start the flow of Flubber through this pipe at a time of your choosing. You know that it flows with a constant real-valued speed, which is at least $v_1$ meters/second and at most $v_2$ meters/second. You want to estimate this speed with an absolute error of at most $\frac{t}{2}$ meters/second.

Unfortunately, the pipe is opaque, so the only thing you can do is to knock on the pipe at any point along its length, that is, in the closed real-valued range $[0,l]$. Listening to the sound of the knock will tell you whether or not the Flubber has reached that point. You are not infinitely fast. Your first knock must be at least $s$ seconds after starting the flow, and there must be at least $s$ seconds between knocks.

Determine a strategy that will require the fewest knocks, in the worst case, to estimate how fast the Flubber is flowing. Note that in some cases the desired estimation might be impossible (for example, if the Flubber reaches the end of the pipe too quickly).
## 输入格式

The input consists of multiple test cases. The first line of input contains an integer $c$ ($1 \leq c \leq 100$), the number of test cases. Each of the next $c$ lines describes one test case. Each test case contains the five integers $l$, $v_1$, $v_2$, $t$ and $s$ ($1 \leq l, v_1, v_2, t, s \leq 10^9$ and $v_1 < v_2$), which are described above.
## 输出格式

For each test case, display the minimal number of knocks required to estimate the flow speed in the worst case. If it might be impossible to measure the flow speed accurately enough, display impossible instead.
## 样例

### 样例输入 #1
```
3
1000 1 30 1 1
60 2 10 2 5
59 2 10 2 5

```
### 样例输出 #1
```
5
3
impossible

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

### **题目描述**

你的家乡雇了一些承包商——包括你！—— 来管理市政管道网络。他们花费巨资建设了该网络，以向城镇中的每个家庭供应弹力胶。不幸的是，目前还没有人找到弹力胶的用途，但没关系。这要么是一个弹力胶网络，要么是一个消防部门。但老实说，房屋很少烧毁，似乎并不需要消防部门。

假设某个地方有人决定要制作一些弹力胶，他们希望知道它会在管道中以多快的速度流动。测量它的流动速度就是你的工作。

你可以访问与网络连接的其中一根管道。该管道长度为 $l$ 米，并且你可以在选择的时间开始通过此管道传输弹力胶。你知道它以恒定的实数速度流动，该速度至少为 $v_1$ 米/秒，最多为 $v_2$ 米/秒。你希望以至多 $\frac{t}{2}$ 米/秒的绝对误差估计此速度(即绝对误差不大于 $\frac {t}{2}$)。

不幸的是，管道是不透明的，所以你唯一能做的事就是在管道的任意一点敲打，即在闭合的实数范围 $[0,l]$ 内。通过听到敲打声，你可以知道弹力胶是否到达了那个点。你的速度并不是无限快的。你第一次敲打必须在开始流动后至少 $s$ 秒，并且敲打之间必须有至少 $s$ 秒的间隔。

你的任务是确定一种策略，需要在最坏情况下用最少的敲击来估算弹力胶的流速。注意，在某些情况下，所需的估计可能是不可能的（例如，弹力胶可能过快地到达管道的末端）。

### **输入格式**

输入包含多组数据。输入的第一行包含一个整数 $c$ $(1 \le c \le 100)$，表示数据组数。接下来的 $c$ 行描述了每组数据。每组数据包含五个整数 $l$，$v_1$，$v_2$ ，$t$ 和 $s$ $（1 \le l, v_1, v_2, t, s \le 10^9 \text{并且}v_1<v_2)$，含义如上所述。

### **输出格式**

对于每组数据，输出在最坏情况下估计流速所需的最小敲击次数。如果无法准确测量流速，则输出 "$impossible$"(不含引号)。

### 说明/提示

时间限制：$1000$ ms，空间限制：$1048576$ kB。

### 题目来源

> International Collegiate Programming Contest (ACM-ICPC) World Finals 2015

> [icpc2015.pdf](https://icpc.global/worldfinals/problems/2015-ICPC-World-Finals/icpc2015.pdf)


---

---
title: "[ICPC 2015 WF] Tours"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6914
tag: ['2015', 'ICPC']
---
# [ICPC 2015 WF] Tours
## 题目描述

The Arca Carania Mountain national park is opening up for tourist traffic. The national park has a number of sites worth seeing and roads that connect pairs of sites. The park commissioners have put together a set of round tours in the park in which visitors can ride buses to view various sites. Each round tour starts at some site (potentially different sites for different tours), visits a number of other sites without repeating any, and then returns to where it started. At least 3 different sites are visited in each round tour. At least one round tour is possible in the national park.

The park commissioners have decided that, for any given road, all buses will be operated by a single company. The commissioners do not want to be accused of favoritism, so they want to be sure that each possible round tour in the park has exactly the same number of roads assigned to each bus company. They realize this may be difficult to achieve. Thus, they want to learn what numbers of bus companies allow for a valid assignment of companies to roads.

Consider Sample Input 1, which is illustrated in Figure 1. There are a total of three round tours for these sites. Some company is assigned road 1-3. It must also be assigned some road on the round tour 1-2-3-4-1, say 2-3. But then it is assigned to two of the three roads on the round tour 1-2-3-1, and no other company can match this – so there can be no other companies. In Sample Input 2 there is only one round tour, so it is enough to assign the roads of this tour equally between companies.

  ![](https://vj.z180.cn/17b3ab5defe058e1bc8649098ddaa63e?v=1603764959) 

   Figure 1: Sample Input 1. 
## 输入格式

The first line of input contains two integers $n$ ($1 \le n \le 2\, 000$), which is the number of sites in the park, and $m$ ($1 \le m \le 2\, 000$), which is the number of roads between the sites. Following that are $m$ lines, each containing two integers $a_ i$ and $b_ i$ ($1 \leq a_ i < b_ i \leq n$), meaning the sites $a_ i$ and $b_ i$ are connected by a bidirectional road. No pair of sites is listed twice.
## 输出格式

Display all integers $k$ such that it is possible to assign the roads to $k$ companies in the desired way. These integers should be in ascending order.
## 样例

### 样例输入 #1
```
4 5
1 2
2 3
3 4
1 4
1 3

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
6 6
1 2
2 3
1 3
1 4
2 5
3 6

```
### 样例输出 #2
```
1 3

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

### 题目描述

给定一张 $n$ 个点 $m$ 条边的无向图，你需要选择一个颜色种类数 $k$，然后用这 $k$ 种颜色给每条边染色，要求对于图中任意一个简单环，每种颜色的边的数量都相同。求所有可行的 $k$。

保证图无重边，无自环。

### 输入格式

第一行两个正整数 $n, m$（$1\leq n, m\leq 2\times 10 ^ 3$）。

接下来 $m$ 行，每行两个正整数 $x, y$（$1\leq x < y \leq n$），表示一条无向边。

### 输出格式

一行按递增顺序输出所有可行的 $k$，用空格隔开。


---

---
title: "[ICPC 2016 WF] Polygonal Puzzle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6923
tag: ['2016', 'Special Judge', 'ICPC']
---
# [ICPC 2016 WF] Polygonal Puzzle
## 题目描述

During last year’s ACM ICPC World Finals in Marrakesh, one of the judges bought a pretty wooden puzzle depicting a camel and palm trees (see Figure 1). Unlike traditional jigsaw puzzles, which are usually created by cutting up an existing rectangular picture, all the pieces of this puzzle have been cut and painted separately. As a result, adjacent pieces often do not share common picture elements or colors. Moreover, the resulting picture itself is irregularly shaped. Given these properties, the shape of individual pieces is often the only possible way to tell where each piece should be placed.

![](https://cdn.luogu.com.cn/upload/image_hosting/ug8atpvc.png)

   Figure 1: The judge’s wooden puzzle. 

The judge has been wondering ever since last year whether it is possible to write a program to solve this puzzle. An important part of such a program is a method to evaluate how well two puzzle pieces “match” each other. The better the match, the more likely it is that those pieces are adjacent in the puzzle.

Pieces are modeled as simple polygons. Your task is to find a placement of two given polygons such that their interiors do not overlap but the polygons touch with their boundaries and the length of the common boundary is maximized. For this placement, polygons can be translated and rotated, but not reflected or resized. Figure 2 illustrates the optimal placement for Sample Input 1.

 ![](https://cdn.luogu.com.cn/upload/image_hosting/xhl8b2h0.png)

   Figure 2: Sample Input 1 and its optimal placement. 
## 输入格式

The input contains the description of two polygons, one after the other. Each polygon description starts with a line containing an integer $n$ ($3 \leq n \leq 50$) denoting the number of vertices of the polygon. This is followed by $n$ lines, each containing two integer coordinates $x$, $y$ of a polygon vertex ($|x|, |y| \leq 100$). The vertices of each polygon are given in clockwise order, and no three consecutive vertices are collinear.

The input data is chosen so that even if the vertices were moved by a distance of up to $10^{-7}$, the answer would not increase by more than $10^{-4}$.
## 输出格式

Display the maximum possible length of the common boundary of these polygons when they are optimally placed. Your answer should have an absolute or relative error of less than $10^{-3}$.
## 样例

### 样例输入 #1
```
8
0 0
0 10
10 10
15 15
24 6
24 10
30 10
30 0
7
-5 0
-5 10
10 10
15 5
20 10
35 10
35 0

```
### 样例输出 #1
```
30.142135624

```
### 样例输入 #2
```
3
1 0
0 30
40 0
3
1 0
0 30
40 0

```
### 样例输出 #2
```
50

```
## 提示

Time limit: 18000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

## 题意简述
有两个多边形，可以平移旋转（但不能对称、缩放等），求这两个多边形贴在一起但不重合的情况下贴贴部分的最大总长度。

## 输入格式
第一行一个数字$n_1$，表示第一个多边形是$n_1$边形。

接下来$n_1$行，每行两个数字，表示第一个多边形每个端点的横、纵坐标。

接下来一个数字$n_2$，表示第二个多边形是$n_2$边形。

最后$n_2$行，每行两个数字，表示第二个多边形每个端点的横、纵坐标。

## 输出格式
一行，最大的贴贴部分长度，绝对误差或相对误差任一小于$10^{-3}$即可通过。

## 数据范围
$3 \leq n_1, n_2 \leq 50$,
横纵坐标均为整数且绝对值不超过100。


---

---
title: "[ICPC 2016 WF] Road Times"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6924
tag: ['2016', 'Special Judge', 'ICPC']
---
# [ICPC 2016 WF] Road Times
## 题目描述

5s,1024MB

Ubol Narongdid is the founder of a brash new startup company called Special D-Liver-E. She wants to corner the market on overnight deliveries of organs between hospitals in the Phuket area. For scheduling purposes it is important to have accurate estimates for the times to perform such deliveries. Several trips between various hospitals have already been performed, so delivery times between those pairs of hospitals are known. The company currently has software to estimate times for other (as yet untraveled) trips, but so far all the estimates have been woefully inaccurate.

You have been asked to come up with a method to improve these estimates. You have at your disposal the following information: 1) the length (in kilometers) of the roads connecting each pair of cities in the Phuket area, and 2) a set of times (in minutes) for various previously executed deliveries.

You know that roads are one-way, and each road has a fixed speed limit that lies between $30$ and $60$ kilometers per hour. Speed limits are real-valued and need not be integers. You also know that delivery trucks always take the route that minimizes distance traveled, and on each road will always travel at a constant speed equal to that road’s speed limit. Thus you know, for example, that if a given trip is $50$ kilometers, the time it will take is between $50$ and $100$ minutes inclusive, in the absence of any other information. Ah, but you do have other information, namely the times of previous deliveries. It is up to you to use it to produce the best possible estimates.
## 输入格式

The input starts with a line containing an integer $n$ ($1 \le n \leq 30$) indicating the number of cities, numbered $0$ to $n-1$. After that are $n$ lines each containing $n$ integers specifying the distance in kilometers between cities: the $j^{\text {th}}$ value on the $i^{\text {th}}$ line indicates the distance when traveling directly from city $i$ to city $j$. A value of $-1$ indicates there is no road directly connecting the two cities, and the distance from any city to itself is always $0$; all other distances are positive and at most $1\, 000$. There are at most $100$ roads.

Following this is a line with a single integer $r$ ($1 \le r \leq 100$) indicating the number of previously executed routes. The next $r$ lines each contain three integers $s$, $d$, and $t$, where $s$ and $d$ are the source and destination cities and $t$ is how long the delivery from $s$ to $d$ took, in minutes.

Finally there is a line containing a single integer $q$ ($1 \le q \leq 100$) indicating the number of future delivery queries. The next $q$ lines each contain two integers $s$ and $d$ giving the source and destination cities for the query.

You may assume that for each of the $r+q$ source/destination pairs in the input there is a unique minimum-distance route.
## 输出格式

Display a single line for each query containing the source and destination cities for that query, followed by the best low and high bounds on the estimate for the travel time, accurate to within an absolute or relative error of $10^{-6}$.
## 样例

### 样例输入 #1
```
3
0 50 -1
55 0 40
-1 40 0
1
0 2 120
3
0 1
1 2
1 0

```
### 样例输出 #1
```
0 1 50.0 80.0
1 2 40.0 70.0
1 0 55.0 110.0

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016


---

---
title: "[ICPC 2016 WF] Spin Doctor"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6925
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] Spin Doctor
## 题目描述

As an employee of the world’s most respected political polling corporation, you must take complex, real-world issues and simplify them down to a few numbers. It isn’t always easy. A big election is coming up and, at the request of Candidate X, you have just finished polling $n$ people. You have gathered three pieces of information from each person, with the values for the $i^\text {th}$ person recorded as:

$a_ i$ – the number of digits of $\pi $ they have memorized

$b_ i$ – the number of hairs on their head

$c_ i$ – whether they will vote for Candidate X

Unfortunately, you are beginning to wonder if these are really the most relevant questions to ask. In fact, you cannot see any correlation between $a$, $b$, and $c$ in the data. Of course, you cannot just contradict your customer – that is a good way to lose your job!

Perhaps the answer is to find some weighting formula to make the results look meaningful. You will pick two real values $S$ and $T$, and sort the poll results $(a_ i, b_ i, c_ i)$ by the measure $a_ i \cdot S + b_ i \cdot T$. The sort will look best if the results having $c_ i$ true are clustered as close to each other as possible. More precisely, if $j$ and $k$ are the indices of the first and last results with $c_ i$ true, you want to minimize the cluster size which is $k-j+1$. Note that some choices of $S$ and $T$ will result in ties among the $(a_ i,b_ i,c_ i)$ triples. When this happens, you should assume the worst possible ordering occurs (that which maximizes the cluster size for this $(S, T)$ pair).
## 输入格式

The input starts with a line containing $n$ ($1 \leq n \leq 250\, 000$), which is the number of people polled. This is followed by one line for each person polled. Each of those lines contains integers $a_ i$ ($0 \leq a_ i \leq 2\, 000\, 000$), $b_ i$ ($0 \leq b_ i \leq 2\, 000\, 000$), and $c_ i$, where $c_ i$ is $1$ if the person will vote for Candidate X and $0$ otherwise. The input is guaranteed to contain at least one person who will vote for Candidate X.
## 输出格式

Display the smallest possible cluster size over all possible $(S, T)$ pairs.
## 样例

### 样例输入 #1
```
6
0 10 0
10 0 1
12 8 1
5 5 0
11 2 1
11 3 0

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
10
6 1 1
0 2 0
2 1 1
6 1 1
8 2 0
4 4 0
4 0 0
2 3 1
6 1 0
6 3 1

```
### 样例输出 #2
```
8

```
### 样例输入 #3
```
5
5 7 0
3 4 0
5 7 0
5 7 1
9 4 0

```
### 样例输出 #3
```
1

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

大选要到了，受候选人X的要求，你调查了 $n$ 个人，并记录了每个人的 $3$ 个信息：

+ $a_i$ 他们能记忆 $\pi$ 的多少位
+ $b_i$ 他们的头发数量
+ $c_i$ 他们是否会给候选人X投票

你需要找到某个公式使这些结果看起来有意义。你要选择 $2$ 个实数 $S$ 和 $T$，将所有调查结果按 $a_i\times S+b_i\times T$ 排序。如果 $c_i$ 为 `true` 的人聚集在了一起，你会觉得这个排序看起来不错。更准确地说，如果 $j$ 和 $k$ 分别是第一个和最后一个 $c_i$ 为 `true` 的人的下标，你想要最小化 $k-j+1$。注意有些 $S$ 和 $T$ 会让排序时出现相等的情况，这时你应该假设最坏情况发生，即排序使得 $k-j+1$ 最大。


---

---
title: "[ICPC 2017 WF] Scenery"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6936
tag: ['2017', 'ICPC']
---
# [ICPC 2017 WF] Scenery
## 题目描述



![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14640/1.png)

Images by John Fowler, Carol Highsmith, and Richard Woodland

You have decided to spend a day of your trip to Rapid City taking photographs of the South Dakota Badlands, which are renowned for their spectacular and unusual land formations. You are an amateur photographer, yet very particular about lighting conditions.

After some careful research, you have located a beautiful location in the Badlands, surrounded by picturesque landscapes. You have determined a variety of features that you wish to photograph from this location. For each feature you have identified the earliest and latest time of day at which the position of the sun is ideal. However, it will take quite a bit of time to take each photograph, given the need to reposition the tripod and camera and your general perfectionism. So you are wondering if it will be possible to successfully take photographs of all these features in one day.


## 输入格式



The first line of the input contains two integers $n (1 \le n \le 10^{4})$ and $t (1 \le t \le 10^{5}),$ where $n$ is the number of desired photographs and $t$ is the time you spend to take each photograph. Following that are $n$ additional lines, each describing the available time period for one of the photographs. Each such line contains two nonnegative integers a and $b$ , where a is the earliest time that you may begin working on that photograph, and $b$ is the time by which the photograph must be completed, with a $+ t \le b \le 10^{9}.$


## 输出格式



Display yes if it is possible to take all $n$ photographs, and no otherwise.


## 样例

### 样例输入 #1
```
2 10
0 15
5 20

```
### 样例输出 #1
```
yes

```
### 样例输入 #2
```
2 10
1 15
0 20

```
### 样例输出 #2
```
no

```
### 样例输入 #3
```
2 10
5 30
10 20

```
### 样例输出 #3
```
yes

```
## 提示

Time limit: 6 s, Memory limit: 512 MB. 


## 题目翻译

你要拍 $n$ 张照片，每张照片必须在 $[a_i,b_i]$ 这个时间段内完成拍摄，并且拍每一张图片都需要用 $t$ 的时间，同一个时间内只能拍摄一张图片。求是否能拍摄完所有照片。

$1 \le n \le 10^4$，$1 \le t \le 10^5$，$a_i+t \le b_i \le 10^9$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2017 WF] Son of Pipe Stream"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6938
tag: ['2017', '网络流', 'Special Judge', '导数', 'ICPC']
---
# [ICPC 2017 WF] Son of Pipe Stream
## 题目描述



Two years ago, you helped install the nation's very first Flubber pipe network in your hometown, to great success. Polls show that everyone loves having their own Flubber dispenser in their kitchen, and now a few enterprising citizens have discovered a use for it. Apparently Flubber, when mixed with water, can help extinguish fires! This is a very timely discovery, as out-of-control fires have lately been surprisingly common.

Your hometown's city council would like to make use of this property of Flubber by creating the $Flubber/water$ mixture at a centrally located station. This station, which is called the Flubber Department (FD) will also have specialized employees trained to travel to the locations of fires and make use of their processed Flubber to control the blazes.

The pipes are already in place all around the city. You are given a layout of the pipes, and must determine how to route Flubber from the Flubber factory and water from a local source through the pipes to the FD.

Note that both Flubber and water will be flowing through the same network of pipes, perhaps even the same pipe. All pipes are bidirectional, but Flubber and water cannot move in opposite directions through the same pipe. Furthermore, if both liquids are sent in the same direction through the same pipe, they will inevitably mix. Therefore the nodes in the network have been equipped with special membranes and filters that enable you to separate and reorganize all incoming mixtures as you see fit. The network is a closed system, so the total rate of each fluid going into a node must equal the total rate of that fluid going out, except at the source of that fluid and the destination (the FD).

Each pipe has a certain capacity. Flubber, being somewhat sluggish, has a viscosity value $v$ , so a pipe that can transport $v liters/second$ of water can transport only $1 liter/second$ of Flubber. The pipe's capacity scales linearly for mixtures of the two. To be precise, if $c$ denotes the water capacity of the pipe and $f$ and $w$ are the rates of Flubber and water moving through the pipe (all measured in $liters/second),$ then the capacity constraint is given by the inequality $v · f + w \le c$ .

Your main concern is balancing the mixture that reaches the FD. You would like as much total liquid as possible, but you also need a sufficient amount of water $-$ because undiluted Flubber is highly flammable $-$ and a sufficient amount of Flubber $-$ because it would not be much of a `Flubber Department` without Flubber! You have come up with a formula to measure the `value` of the final mixture: $F^{a} · W^{1−a},$ where $F$ is the rate of incoming Flubber in $liters/second, W$ is the rate of incoming water in $liters/second,$ and a is a given constant between $0$ and $1$ .

Determine the maximum value of $F^{a} · W^{1−a}$ that can be achieved and how to route the Flubber and water to achieve it.


## 输入格式



The input starts with a line containing the number of locations $n (3 \le n \le 200)$ , the number of pipes $p (n − 1 \le p \le $ n(n $− 1)/2)$ , and the real values $v (1 \le v \le 10)$ and a ($0$ . $01 \le $ a $ \le 0$ . $99$) . Locations are numbered from $1$ to $n$ ; $1$ is the Flubber factory, $2$ is the water source, and $3$ is the FD. The real values have at most $10$ digits after the decimal point.

The following $p$ lines each describe one pipe. Each line contains two integers $j$ and $k (1 \le j < k \le n)$ , giving the locations connected by the pipe, and an integer $c (1 \le c \le 10)$ , giving the water capacity of the pipe in $liters/second.$

No two pipes connect the same pair of locations. Furthermore, it is guaranteed that the network is connected.


## 输出格式



First, for each pipe (in the order given in the input), display two values: the rate of Flubber moving through it, and the rate of water moving through it (negative if the liquid is moving from $k$ to $j)$ , such that $F^{a} ·W^{1−a}$ is maximized. Then display that maximum value accurate to within an absolute error of $10^{−4}.$

If there are multiple solutions, any one will be accepted. All constraints (not sending Flubber and water in opposite directions along the same pipe, flow conservation, pipe capacities, and consistency between the constructed solution and its claimed value) must be satisfied within an absolute error of $10^{−4}.$


## 样例

### 样例输入 #1
```
6 6 3.0 0.66
2 4 8
4 6 1
3 6 1
4 5 5
1 5 7
3 5 3

```
### 样例输出 #1
```
0.000000000 1.360000000
0.000000000 1.000000000
0.000000000 -1.000000000
0.000000000 0.360000000
0.880000000 0.000000000
-0.880000000 -0.360000000
1.02037965897

```
### 样例输入 #2
```
5 5 1.0 0.5
1 2 10
2 3 10
3 4 10
4 5 10
3 5 10

```
### 样例输出 #2
```
5 0
5 5
4.2 3.14159
4.2 3.14159
-4.2 -3.14159
5

```
## 提示

Time limit: 5 s, Memory limit: 512 MB. 


## 题目翻译

### 题目描述
两年以前，你帮助你的家乡安装了国内的第一个 Flubber 管道网络，获得了巨大成功。投票表明每个人都喜欢在自己家的厨房里装上 Flubber 分配器，而现在一些有进取心的市民发现了一种新的用途——Flubber 和水混合后似乎可以帮助灭火！这是一个很及时的发现，因为最近无法控制的大火出奇地常见。

你家乡的市议会想在一个位于中央的地方制造 Flubber 和水的混合物以利用 Flubber 的这个属性。这个被称为 Flubber 部门的地方拥有专门训练的员工去往着火的地点并且利用经过处理的 Flubber 来控制火势。

管道已经在城市中铺设好。你会得到管道布局，而你需要决定如何将 Flubber 从 Flubber 工厂、将水从一个本地水源通过管道运送至 Flubber 部门。

注意 Flubber 和水会在同一管道网络中，甚至可能在同一条管道中流动。所有管道是双向的，但是 Flubber 和水不能在同一条管道中异向流动。此外，如果两种液体同向流过一条管道，它们会不可避免地混合，因此网络中的所有节点配备了特殊的膜和筛，如你所见，可以分离和重新组织所有流入的混合物。管道网络是个封闭系统，因此在每个节点处每种液体的总流入速率必须等于总流出速率，除了每种液体各自的源头和目的地（Flubber 部门）。

每条管道有某个容量，有些粘稠的 Flubber 有一个粘度值 v，所以能运输 v 升每秒的水的管道只能运输 1 升每秒的 Flubber。管道对于混合物的容量是线性变化的。更精确地，假设 c 表示管道对于水的容量，f 和 w 分别表示 Flubber 和水流过管道的速率（单位均为升每秒），则容量的限制用不等式 v⋅f+w≤c 表示。

你主要关心的是平衡流到 Flubber 部门的混合物。你想要尽可能多的混合液体，但是也需要足够的水——因为未经稀释的 Flubber 是高度易燃的——也需要足够的 Flubber——因为 Flubber 部门可不能没了 Flubber！你想出了一个公式来衡量最终混合物的价值：$F^a⋅W^{1−a}$，其中 F 是以升每秒为单位的 Flubber 的流入速率，W 是以升每秒为单位的水的流入速率，a 是一个给定的介于 0 和 1 之间的常数。

求出 $F^a⋅W^{1−a}$ 能达到的最大值以及如何安排 Flubber 和水的路径来达到它。

### 输入格式
输入的第一行包含地点的数量 n (3≤n≤300)，管道的数量 $p (n−1≤p≤\frac12n(n−1))$，和实数 v (1≤v≤10) 和 a (0.01≤a≤0.99)。地点从 1 到 n 标号；1 是 Flubber 工厂，2 是水源，3 是 Flutter 部门。实数的小数点后最多有十位。

接下来的 p 行每行描述了一条管道。每行有两个整数 j 和 k (1≤j<k≤n)，表示管道连接的地点，和一个整数 c (1≤c≤10)，表示这条管道的水容量，以升每秒为单位。

没有两条管道连接相同的两个地点，此外，还保证网络是连通的。

### 输出格式
首先，对于每条管道（按照输入的顺序），输出两个值：其中 Flubber 流过的速率和其中水流过的速率 （如果从 k 流到 j 则为负数），使得 $F^a⋅W^{1−a}$ 最大化。然后输出其最大值，在 $10^{−4}$ 的绝对误差以内。

如果有多解，输出任意一种均可。所有限制（Flubber 和水没有在同一条管道内异向流动、流量守恒、管道容量以及构造的解和其声称的值的一致性）需要在 $10^{−4}$ 的绝对误差内满足。


---

---
title: "[ICPC 2018 WF] Conquer The World"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6943
tag: ['2018', 'ICPC']
---
# [ICPC 2018 WF] Conquer The World
## 题目描述



Bwahahahahaha!!! Your nemesis, the dashingly handsome spy Waco Powers, has at last fallen to your secret volcano base's deathtraps (or so you assume, being a little too busy to witness it firsthand). At long last, you are all set to CONQUER THE WORLD!

Nothing will stand in your way! Well, nothing except a minor problem of logistics. Your evil armies have announced that they will not continue carving their relentless path of destruction across the puny nations of the world without being paid. And unfortunately you are running low on cash $-$ a volcano lair has many wonderful qualities, but `reasonably affordable` is not one of them. You have had to pull funds from the travel budget to pay your ungrateful underlings. Now you are not sure how you will actually get your armies into position to CONQUER THE WORLD.

You have a map of the nations of the world and all your available transport routes between them. Each route connects two nations and has a fixed cost per army that uses it. The routes are laid out such that there is exactly one way to travel between any two nations. You know the current position of each of your armies and how many you will need to place permanently in each nation in order to subjugate it. How can you move the armies into place as cheaply as possible so you can CONQUER THE WORLD?


## 输入格式



The first line of input contains an integer $n (1 \le n \le 250 000)$ , the number of nations. This is followed by $n − 1$ lines, each containing three integers $u , v$ , and $c (1 \le u , v \le n , 1 \le c \le 10^{6}),$ indicating that there is a bidirectional route connecting nations $u$ and $v$ , which costs $c$ per army to use.

Finally, another $n$ lines follow, the $i^{th}$ of which contains two non-negative integers $x_{i}$ and $y_{i},$ indicating that there are currently $x_{i}$ armies in nation $i$ , and you need at least $y_{i}$ armies to end up in that nation in the final configuration. The total number of armies (the sum of the $x_{i}$ values) is at least the sum of the $y_{i}$ values, and no more than $10^{6}.$


## 输出格式



Display the minimum cost to move your armies such that there are at least $y_{i}$ armies in nation $i$ for all $i$ .


## 样例

### 样例输入 #1
```
3
1 2 5
3 1 5
2 1
5 0
1 3

```
### 样例输出 #1
```
15

```
### 样例输入 #2
```
6
1 2 2
1 3 5
1 4 1
2 5 5
2 6 1
0 0
1 0
2 1
2 1
0 1
0 1

```
### 样例输出 #2
```
9

```
## 提示

Time limit: 8 s, Memory limit: 1024 MB. 


## 题目翻译

给定一个 $n$ 点 $n-1$ 边的无向图，每条边 $(u,v)$ 有边权 $c$。

现在第 $i$ 个点有 $x_i$ 的点权，每个点需要 $y_i$ 的点权，所以你可以移动点权到不同的点上。移动一条边上的点 $u$ 的 $k$ 个单位点权到 $v$ 要用 $k \times c$ 的代价。

求满足所有点的需要的最小代价。

$1 \le n \le 2.5 \times 10^5$，$1 \le u,v \le n$，$1 \le c \le 10^6$，$0 \le \sum y_i\le \sum x_i \le 10^6$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2018 WF] Panda Preserve"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6947
tag: ['2018', 'Special Judge', 'ICPC']
---
# [ICPC 2018 WF] Panda Preserve
## 题目描述



Last month, Sichuan province secured funding to establish the Great Panda National Park, a natural preserve for a population of more than $1 800$ giant pandas. The park will be surrounded by a polygonal fence. In order for researchers to track the pandas, wireless receivers will be placed at each vertex of the enclosing polygon and each animal will be outfitted with a wireless transmitter. Each wireless receiver will cover a circular area centered at the location of the receiver, and all receivers will have the same range. Naturally, receivers with smaller range are cheaper, so your goal is to determine the smallest possible range that suffices to cover the entire park.

As an example, Figure G.1 shows the park described by the first sample input. Notice that a wireless range of $35$ does not suffice (a) , while the optimal range of $50$ covers the entire park (b) .

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15695/1.png)

Figure G.1 : Illustration of Sample Input $1$ .


## 输入格式



The first line of the input contains an integer $n (3 \le n \le 2 000)$ specifying the number of vertices of the polygon bounding the park. This is followed by $n$ lines, each containing two integers $x$ and $y (|x|, |y| \le 10^{4})$ that give the coordinates $(x , y)$ of the vertices of the polygon in counter-clockwise order. The polygon is simple; that is, its vertices are distinct and no two edges of the polygon intersect or touch, except that consecutive edges touch at their common vertex.


## 输出格式



Display the minimum wireless range that suffices to cover the park, with an absolute or relative error of at most $10^{−6}.$


## 样例

### 样例输入 #1
```
5
0 0
170 0
140 30
60 30
0 70

```
### 样例输出 #1
```
50

```
### 样例输入 #2
```
5
0 0
170 0
140 30
60 30
0 100

```
### 样例输出 #2
```
51.538820320

```
### 样例输入 #3
```
5
0 0
1 2
1 5
0 2
0 1

```
### 样例输出 #3
```
1.581138830

```
## 提示

Time limit: 10 s, Memory limit: 1024 MB. 


## 题目翻译

给定一个 $n$ 个点的不自交的多边形（不一定是凸多边形），求最小的圆半径 $r$ 使得在每个顶点画一个半径为 $r$ 的圆，这些圆的并覆盖了整个多边形。$n \le 2000$，绝对误差或相对误差不超过 $10^{-6}$。


---

---
title: "[ICPC 2018 WF] Uncrossed Knight’s Tour"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6950
tag: ['2018', 'ICPC']
---
# [ICPC 2018 WF] Uncrossed Knight’s Tour
## 题目描述



A well-known puzzle is to `tour` all the squares of an $8 \times 8$ chessboard using a knight, which is a piece that can move only by jumping one square in one direction and two squares in an orthogonal direction. The knight must visit every square of the chessboard, without repeats, and then return to its starting square. There are many ways to do this, and the chessboard size is manageable, so it is a reasonable puzzle for a human to solve.

However, you have access to a computer, and some coding skills! So, we will give you a harder version of this problem on a rectangular $m \times n$ chessboard with an additional constraint: the knight may never cross its own path. If you imagine its path consisting of straight line segments connecting the centers of squares it jumps between, these segments must form a simple polygon; that is, no two segments intersect or touch, except that consecutive segments touch at their common end point. This constraint makes it impossible to visit every square, so instead you must maximize the number of squares the knight visits. We keep the constraint that the knight must return to its starting square. Figure J.1 shows an optimal solution for the first sample input, a $6 \times 6$ board.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15698/1.png)

Figure J.1 : An optimal solution for a $6 \times 6$ board.


## 输入格式



The input consists of a single line containing two integers $m (1 \le m \le 8)$ and $n (1 \le n \le 10^{15}),$ giving the dimensions of the rectangular chessboard.


## 输出格式



Display the largest number of squares that a knight can visit in a tour on an $m \times n$ chessboard that does not cross its path. If no such tour exists, display $0$ .


## 样例

### 样例输入 #1
```
6 6

```
### 样例输出 #1
```
12

```
### 样例输入 #2
```
8 3

```
### 样例输出 #2
```
6

```
### 样例输入 #3
```
7 20

```
### 样例输出 #3
```
80

```
### 样例输入 #4
```
2 6

```
### 样例输出 #4
```
0

```
## 提示

Time limit: 2 s, Memory limit: 1024 MB. 


## 题目翻译

### 题目描述

马在 $m$ $\times$ $n$ 大小的矩形棋盘上跳跃（走日字）。求从棋盘上一点开始，在保证【性质】的情况下，它最多经过几个格子（包括起点，且终点不算），可以回到初始点？

【性质】：想象马的路径由直线段组成，这些直线段连接着它所跳跃的正方形的中心（如图），这些直线段必须形成一个简单的多边形。也就是说，没有两个线段相交或接触，除非连续线段在其公共端点处接触。

### 输入格式

一行，两个正整数 $m$ $(1 \le m \le 8)$ 和 $n$ $(1 \le n \le 10^{15})$。

### 输出格式

一行，马最多经过的格子数。
若没有这样的路径，输出 $0$ 。


---

---
title: "[NEERC 2017] Hack"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6959
tag: ['2017', '交互题', 'Special Judge', 'ICPC']
---
# [NEERC 2017] Hack
## 题目描述

Heidi is analyzing a peculiar device. This device takes an a as input and computes $a^d(mod n)$ using thefollowing pseudocode and some integers $d$ and $n$ stored in this device:

 ```
modPow(a, d, n) {
  r = 1;
  for (i = 0; i < 60; ++i) {
    if ((d & (1 << i)) != 0) {
      r = r * a % n;
    }
  a = a * a % n;
  }
}
```

Note that the pseudocode assumes arbitrary sized integers, $<<$ denotes bitwise shift left, $&$ denotes bitwise

and, and % denotes modulo.

The device does not tell Heidi the result of the computation. However, Heidi can measure how long does the computation take. She knows that only multiplication modulo $n$ (lines $5$ and $7$ in the above pseudocode) takes any measurable amount of time, all other lines can be assumed to take $0$ nanoseconds.

Moreover, she knows that it takes $(bits(x) + 1) · (bits(y) + 1)$ nanoseconds to multiply $x$ by $y$ modulo $n$ , where $bits(x)$ is the number of bits in the binary representation of $x$ without leading zeros, or more formally $\text{bits(x)} = ⌈\log_2 (x + 1)⌉.

Heidi knows the integer $n$ but does not know the integer $d$ . She wants to find $d$ by feeding the device different integers a as input and measuring the time the computation takes for each a .

She knows that $n$ and $d$ were chosen in the following way: first, two prime numbers $p$ and $q$ with $30$ bits in binary representation (in other words, between $229$ and $230 −1)$ were picked independently and uniformly at random. Then the number $n$ was computed as $n = p · q$ . Then the number $m = φ(n) = (p−1)·(q −1)$

was computed. Then $d$ was picked uniformly at random between $1$ and $m − 1$ inclusive, such that it is coprime with $m$ .

# Interaction Protocol

First, the testing system writes the integer $n$ -- the modulo used by the device. Note that $n$ and the hidden number $d$ are guaranteed to have been generated according to the procedure described above.

Your solution shall print requests of two types:

- “? a” tells to feed a as input to the device. a must be an integer between $0$ and $n−1$ inclusive. The testing system responds with the time it took the device to compute `modPow(a , d , n)` in nanoseconds.

- “! d” tells the value of $d$ that your program has determined.

Don't forget to flush the output after each request!

Your solution must issue exactly one request of the second type, which must be the last request, and the solution must terminate gracefully after issuing it.

Your solution is allowed to issue at most $30 000$ requests of the first type.

Your solution will be run on $30$ testcases, working with one $(n , d)$ pair per run. For each testcase the numbers $n$ and $d$ are fixed and were generated using the procedure described above. The example below

was not generated in that manner and thus will not be used for testing your solution; it only serves to illustrate the input/output format and provide a sanity check for your calculation of the computation time. 
## 样例

### 样例输入 #1
```
15
980
293
```
### 样例输出 #1
```
? 3
? 8
! 5
```
## 题目翻译

有如下的一个程序来计算 $a^d(mod \ n)$，（$d,n$是常数）

```cpp
modPow(a, d, n) {
	r = 1;
 	for (i = 0; i < 60; ++i) {
   		if ((d & (1 << i)) != 0) {
     		r = r * a % n;
   		}
 		a = a * a % n;
 	}
}
```

其中，计算 $x * y\ \  mod \ n$ （上述伪代码中的第 $5$ 行和第 $7$ 行）需要消耗 $(bits(x) + 1)* (bits(y) + 1)$ 纳秒，$bits(x)$ 是 $x$ 的二进制表示中不带前导零的位数，更正式的说，为 $\lceil \log_2(x+1) \rceil$，其他指令可以认为不需要任何时间。

你知道 $n$ ，但不知道 $d$， 你可以通过不超过 $30000$ 次询问对于 $a$ 计算 $a^d(mod \ n)$ 所用纳秒数。

正式数据中，$n,d$ 的生成方式如下：随机挑选两个 $[2^{29},2^{30}-1]$ 的质数 $p,q$，$n=pq$，而 $d$ 为在 $[1,\varphi(n)]$ 随机挑选的，与 $\varphi(n)=(p-1)*(q-1)$ 互质的数

**这是一道交互题**

首先，将给出整数 $n$

有两种指令可用：

“? a”询问对于正整数 $a$ 计算 $a^d(mod \ n)$ 所用纳秒数。要求$a<n$。返回所用的纳秒数

“! d”表示确定了 $d$ 的值并提交，你的程序应当在此后结束。


---

---
title: "[NEERC 2017] Knapsack Cryptosystem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6962
tag: ['2017', 'ICPC']
---
# [NEERC 2017] Knapsack Cryptosystem
## 题目描述



The Merkle-Hellman Knapsack Cryptosystem was one of the earliest public key cryptosystems invented by Ralph Merkle and Martin Hellman in $1978$ . Here is its description

Alice chooses $n$ positive integers ${a_{1}, . . . , a_{n}}$ such that each $a_{i} > \sum^{i−1}_{j=1}a_{j},$ a positive integer $q$ which is greater than the sum of all $a_{i},$ and a positive integer $r$ which is coprime with $q$ . These $n + 2$ integers are Alice's private key.

Then Alice calculates $b_i = (a_{i} · r)$ mod $q$ . These $n$ integers are Alice's public key.

Knowing her public key, Bob can transmit a message of $n$ bits to Alice. To do that he calculates $s$ , the sum of $b_{i}$ with indices $i$ such that his message has bit $1$ in i-th position. This value $s$ is the encrypted message.

Note that an eavesdropper Eve, who knows the encrypted message and the public key, has to solve a (presumably hard) instance of the knapsack problem to find the original message. Meanwhile, after receiving $s$ , Alice can calculate the original message in linear time; we leave it to you as an exercise.

In this problem you deal with the implementation of the Merkle-Hellman Knapsack Cryptosystem in which Alice chose $q = 2^{64},$ for obvious performance reasons, and published this information. Since everyone knows her $q$ , she asks Bob to send her the calculated value $s$ taken modulo $2^{64}$ for simplicity of communication.

You are to break this implementation. Given the public key and an encrypted message, restore the original message.


## 输入格式



The first line contains one integer $n (1 \le n \le 64)$ .

Each of the next $n$ lines contains one integer $b_{i} (1 \le b_{i} < 2^{64}).$

The last line contains one integer $s$ mod $q$ -- the encrypted message $s$ taken modulo $q (0 \le s$ mod $q < 2^{64}).$

The given sequence $b_{i}$ is a valid public key in the described implementation, and the given value $s$ mod $q$ is a valid encrypted message.


## 输出格式



Output exactly $n$ bits ($0$ or $1$ digits) -- the original message.


## 样例

### 样例输入 #1
```
5
10
20
50
140
420
440

```
### 样例输出 #1
```
01001

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

背包密码是一个简单的公钥密码系统，下面是它的具体过程：

- Alice 选择 $n$ 个正整数 $a_1,a_2,\cdots,a_n$，满足 $a_i> \sum\limits_{j=1}^{i-1} a_j$，再选择两个正整数 $q,r$，满足 $q> \sum\limits_{j=1}^n a_i$，$r,q$ 互质。这 $n + 2$ 个数是 Alice 的私钥。再计算 $b_i = (a_i\cdot r)\bmod q$，这 $n+2$ 个数是 Alice 的公钥。

- Bob 有一个 01 串 $t$，他知道 Alice 的公钥，$t$ 加密后得到 $s=\left(\sum\limits_{i=1}^n [t_i=1]b_i\right)\bmod q$. 他把这个 01 串加密后的结果发给了 Alice。那 Alice 就可以在线性时间内解出来。

你现在截获了 $s$，并知道 $b_i$ 和 $q$，其中 $q = 2^{64}$。请解出这个 01 串。

$n\le 64$，保证 $s,b_i$ 合法。


---

---
title: "[NEERC 2016] Binary Code"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6965
tag: ['2016', 'Special Judge', '图论建模', '2-SAT', '字典树 Trie', 'ICPC']
---
# [NEERC 2016] Binary Code
## 题目描述



Ben has recently learned about binary prefix codes. A binary code is a set of $n$ distinct nonempty code words $s_{i}$ , each consisting of 0s and $1s.$ A code is called a prefix code if for every $i ≠ j$ neither $s_{i}$ is a prefix of $s_{j}$ nor $s_{j}$ is a prefix of $s_{i}$ . A word $x$ is called a prefix of a word $w$ if there exists a possibly empty word $y$ , such that xy $= w$ . For example, $x = 11$ is a prefix of $w = 110$ and $x = 0100$ is a prefix of $w = 0100$ .

Ben found a paper with $n$ lines of binary code in it. However, this paper is pretty old and there are some unreadable characters. Fortunately, each word contains at most one unreadable character.

Ben wants to know whether these $n$ lines could represent a binary prefix code. In other words, can he replace every unreadable character with $0$ or $1$ , so that the code becomes a prefix code?


## 输入格式



The first line contains integer $n$ -- the number of code words $(1 \le n \le 5 · 10^{5}).$

Next $n$ lines contain nonempty code word records, one per line. Each code word record consists of `0`, `1` and `?` characters. Every code word record contains at most one `?` character that represents unreadable character.

The total length of words does not exceed $5 · 10^{5}$ .


## 输出格式



Output `NO` in the first line if the code cannot be a prefix code.

Otherwise, output `YES` in the first line. Next $n$ lines shall contain code words in the same order as the corresponding code word records in the input.

If there are several prefix codes, that could have been written on the paper, output any one.


## 样例

### 样例输入 #1
```
4
00?
0?00
?1
1?0

```
### 样例输出 #1
```
YES
000
0100
11
100

```
### 样例输入 #2
```
3
0100
01?0
01?0

```
### 样例输出 #2
```
NO

```
## 提示

Time limit: 2 s, Memory limit: 2048 MB. 


## 题目翻译

### 题目描述

给定 `n` 个01串，每个字符串至多有一位是未知的，可以填 `0` 或 `1` ，求是否存在一种方案，使得任意一个字符串不是其它任意一个字符串的前缀

### 输入格式

第一行是一个正整数 `n` ，代表字符串的数量。 $(1 \leq n \leq 5 \cdot 10^5)$

接下来 `n` 行每行一个字符串，只可能由 `0` 、 `1` 或 `?` 组成。 `?` 代表未知的位置，每个字符串最多一个。

保证字符串总长度不超过 $5 \cdot 10^5$ 。

### 输出格式

如果无解，只需要输出 `NO` 。

如果有解，在第一行输出 `YES` ，接下来 `n` 行输出方案。

如果有多组解，只需要输出任意一组。


---

---
title: "[NEERC 2016] Delight for a Cat"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6967
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NEERC 2016] Delight for a Cat
## 题目描述



A cat is going on an adventure.

Each hour, the cat can be either sleeping or eating. The cat cannot be doing both actions at the same hour, and the cat is doing exactly one of these actions for the whole hour.

For each of the next $n$ hours, the amount of delight the cat is getting if it is sleeping or eating during that hour is known. These amounts can be different for each hour.

An integer time period $k$ is also known. Among every $k$ consecutive hours, there should be at least $m_{s}$ hours when the cat is sleeping, and at least $m_{e}$ hours when the cat is eating. So, there are exactly $n − k + 1$ segments of $k$ hours for which this condition must be satisfied.

Find the maximum total amount of delight the cat can get during the next $n$ hours.


## 输入格式



The first line of the input contains four integers $n , k , m_{s},$ and $m_{e} (1 \le k \le n \le 1000$ ; $0 \le m_{s}, m_{e} \le k$ ; $m_{s} + m_{e} \le k)$ -- the number of upcoming hours, the length of the period (in hours), and the minimum number of hours the cat should be sleeping and eating out of every $k$ consecutive hours, respectively.

The second line contains $n$ integers $s_{1}, s_{2},$ . . . , $s_{n} (0 \le s_{i } \le 10^{9}$ ) -- the amount of delight the cat gets when it is sleeping during the first, the second, $ \cdots ,$ the n-th hour.

The third line contains $n$ integers $e_{1}, e_{2},$ . . . , $e_{n} (0 \le e_{i} \le 10^{9}$ ) -- the amount of delight the cat gets when it is eating during the first, the second, $ \cdots ,$ the n-th hour.


## 输出格式



In the first line, output a single integer -- the maximum total amount of delight the cat can get during the next $n$ hours.

In the second line, output a string of length $n$ consisting of characters `S` and `E`. The i-th character of this string should correspond to whether the cat should sleep $(`S`)$ or eat $(`E`)$ in the i-th hour to get the maximum total amount of delight out of these $n$ hours.


## 样例

### 样例输入 #1
```
10 4 1 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1

```
### 样例输出 #1
```
69
EEESESEESS

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

一只猫猫在连续的 $n$ 个小时中可以进行睡觉或进食两种动作。一个小时内只能选择其中一种进行。

现在你知道这只猫在接下来的这 $n$ 个小时中每第 $i$ 个小时睡觉或进食分别获得的快乐值 $s_i$ 和 $e_i$。

但是对于每一个连续的 $k$ 个小时，这只猫必须满足在这 $k$ 个小时内至少有 $m_e$ 个小时的进食时间和 $m_s$ 个小时的睡觉时间。也就是说在这 $n$ 个小时中的 $n-k+1$ 个 $k$ 长连续区间必须满足睡觉时间 $\geq m_s$ ，进食时间 $\geq m_e$。

现在小猫想知道自己这 $n$ 个小时最多能获得多少快乐值以及相对应的方案。

输入：

第一行分别输入 $n,k,m_s,m_e$ 。

第二行输入 $n$ 个数字 $s_1,s_2,\dots, s_n$ 分别代表每个小时如果睡觉可以获得的快乐值。

第三行输入 $n$ 个数字 $e_1,e_2,\dots,e_n$ 分别代表每个小时如果进食可以获得的快乐值。

输出：

第一行输出可以获得的最大快乐值。

第二行输出**一个合法方案**，$n$ 个字符表示每个小时进行的动作。第 $i$ 个字符用 `S` 表示第 $i$ 个小时在睡觉，或用 `E` 表示第 $i$ 个小时在进食。


---

---
title: "[NWRRC 2016] Hard Cuts"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7038
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NWRRC 2016] Hard Cuts
## 题目描述



Given a rectangle with integer side lengths, your task is to cut it into the smallest possible number $of squares$ with integer side lengths.


## 输入格式



The first line contains a single integer $T$ -- the number of test cases $(1 \le T \le 3600)$ . Each of the $next T$ lines contains two integers $w_{i}, h_{i}$ -- the dimensions of the rectangle $(1 \le w_{i}, h_{i} \le 60$ ; for any $i ≠ j, either w_{i }≠ w_{j}$ or $h_{i} ≠ h_{j} ).$


## 输出格式



For the i-th test case, output $k_{i}$ -- the minimal number of squares, such that it is possible to cut $the w_{i}$ by $h_{i}$ rectangle into $k_{i}$ squares. The following $k_{i} lines$ should contain three integers each: $x_{ij} , y_{ij} -- the$ coordinates of the bottom-left corner of the j-th square and $l_{ij }--$ its side length $(0 \le x_{ij} \le w_{i} − l_{ij} ; 0 \le y_{ij} \le h_{i} −l_{ij} ).$ The bottom-left corner of the rectangle has coordinates $(0 , 0)$ and the top-right $corner has$ coordinates $(w_{i}, h_{i}).$


## 样例

### 样例输入 #1
```
3
5 3
5 6
4 4

```
### 样例输出 #1
```
4
0 0 3
3 0 2
3 2 1
4 2 1
5
0 0 2
0 2 2
0 4 2
2 0 3
2 3 3
1
0 0 4

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

# 题目描述
给定一个边长为整数的矩形，您的任务是将其切割成边长为整数的正方形的尽可能少的正方形。


---

---
title: "[NWRRC 2015] Graph"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7054
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NWRRC 2015] Graph
## 题目描述



The sequence $a_{1}, a_{2},$ . . . , $a_{n}$ is called a permutation, if it contains every integer from $1$ to $n$ .

The permutation of vertices $a_{1}, a_{2},$ . . . , $a_{n}$ is a topological sort of a directed graph, if for every directed edge from $u$ to $v$ , vertex $u$ comes before $v$ in this permutation.

The permutation $a_{1}, a_{2},$ . . . , $a_{n}$ is lexicographically smaller than the permutation $b_{1}, b_{2},$ . . . , $b_{n},$ if there exists $m$ such that $a_{i} = b_{i}$ for every $1 \le i < m$ and $a_{m} < b_{m}.$

Given a directed acyclic graph, add at most $k$ directed edges to it in such a way, that the resulting graph still has no cycles and the lexicographically minimal topological sort of the graph is maximum possible.


## 输入格式



The first line of the input file contains three integers $n , m$ and $k$ -- the number of vertices and directed edges in the original graph, and the number of directed edges, that you are allowed to add $(1 \le n \le 100 000$ ; $0 \le m , k \le 100 000)$ .

Each of the following $m$ lines contains two integers $u_{i}, v_{i},$ describing directed edge from $u_{i}$ to $v_{i} (1 \le u_{i}, v_{i} \le n)$ .

The graph has no cycles.


## 输出格式



The first line of the output file should contain $n$ integers -- the lexicographically minimal topological sort of the modified graph. The second line should contain a single integer $x (0 \le x \le k)$ -- the number of directed edges to add. The following $x$ lines of the output should contain description of added directed edges in the same format as in the input file.


## 样例

### 样例输入 #1
```
5 3 2
1 4
4 2
1 3

```
### 样例输出 #1
```
5 1 4 2 3
2
4 3
5 1

```
### 样例输入 #2
```
2 2 20
1 2
1 2

```
### 样例输出 #2
```
1 2
1
1 2

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

给定一张 $n$ 点 $m$ 条边的有向无环图，你可以至多添加 $k$ 条有向边，使得这仍然是一个有向无环图，使得字典序最小的拓扑序的字典序尽量大。

输出这个拓扑序以及方案。

$n,m,k\le 10^5$


---

---
title: "[NWRRC 2015] Insider’s Information"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7056
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NWRRC 2015] Insider’s Information
## 题目描述



Ian works for a rating agency that publishes ratings of the best universities. Irene is a journalist who plans to write a scandalous article about the upcoming rating.

Using various social engineering techniques (let's not get into more details), Irene received some insider's information from Ian.

Specifically, Irene received several triples $(a_{i}, b_{i}, c_{i}),$ meaning that in the upcoming rating, university $b_{i}$ stands between universities $a_{i}$ and $c_{i}.$ That is, either $a_{i}$ comes before $b_{i}$ which comes before $c_{i},$ or the opposite. All triples told by Ian are consistent -- let's say that actual rating satisfies them all.

To start working on the first draft of the future article, Irene needs to see at least some approximation to the actual rating. She asked you to find a proposal of a rating in which at least half of the triples known by Irene are satisfied.


## 输入格式



The first line contains integers $n$ and $m$ , the number of rated universities, and the number of triples given to Irene by Ian $(3 \le n \le 100 000$ ; $1 \le m \le 100 000)$ .

Each of the next $m$ lines contains three distinct integers $a_{i}, b_{i}, c_{i}$ -- the universities making a triple $(1 \le a_{i}, b_{i}, c_{i} \le n)$ .


## 输出格式



Output the proposal of a rating from the first university to the last one. The proposal rating should satisfy at least $m/2$ triples. If there are many such proposals, output any one of them.


## 样例

### 样例输入 #1
```
4 3
1 2 3
1 2 3
1 4 3

```
### 样例输出 #1
```
4 3 2 1

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

## 题意

对于 $[1, n]$ 的排列，给 $m$ 个限制，第 $i$ 个限制描述 $b_i$ 出现在 $a_i$，$c_i$ 之间。保证存在一个排列满足所有限制。

构造一个 $n$ 的排列至少满足 $\lceil \frac m2 \rceil$ 个限制。


---

---
title: "[NWRRC 2015] Kingdom Trip"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7058
tag: ['2015', 'ICPC']
---
# [NWRRC 2015] Kingdom Trip
## 题目描述



Once upon a time, there was a kingdom ruled by a wise king. After forty three years of his reign, by means of successful military actions and skillful diplomacy, the kingdom became an infinite flat two-dimensional surface. This form of the kingdom greatly simplified travelling, as there were no borders.

A big holiday was planned in the kingdom. There were $n$ locations for people to gather. As the king wanted to have a closer look at his people, he ordered to make a trip through these locations. He wanted to give a speech in each of these locations. Initially his trip was designed as a polygonal chain $p$ : $p_{1} \to p_{2} \to $ . . . $ \to p_{n}.$

Not only the king was wise, but he was old, too. Therefore, his assistants came up with an idea to skip some locations, to make the king to give as few speeches as possible. The new plan of the trip has to be a polygonal chain consisting of some subsequence of $p$ : starting at $p_{1}$ and ending at $p_{n},$ formally, $p_{i_{1}} \to p_{i_{2}} \to · · · \to p_{i_{m}},$ where $1 = i_{1} < i_{2} < · · · < i_{m} = n$ . Assistants know that the king wouldn't allow to skip location $j$ , if the distance from $p_{j}$ to segment $p_{i_{k}} \to p_{i_{k+1}}$ exceeds $d$ , for such $k$ , that $i_{k} < j < i_{k+1}.$

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11476/1.png)

Original route

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11476/2.png)

New route

Help the assistants to find the new route that contains the minimum possible number of locations.


## 输入格式



The first line of the input file contains two integers $n$ and $d$ -- the number of locations in the initial plan of the trip and the maximum allowed distance to skipped locations $(2 \le n \le 2000$ ; $1 \le d \le 10^{6}).$

The following $n$ lines describe the trip. The i-th of these lines contains two integers $x_{i}$ and $y_{i}$ -- coordinates of point $p_{i}.$ The absolute value of coordinates does not exceed $10^{6}.$ No two points coincide.


## 输出格式



Output the minimum number of locations the king will visit. It is guaranteed that the answer is the same for $d ± 10^{−4}.$


## 样例

### 样例输入 #1
```
5 2
2 6
8 2
14 2
12 9
13 8

```
### 样例输出 #1
```
3

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

## 题目描述
很久以前，一位明智的国王统治着一个王国。在他长达43年的统治后，通过成功的军事行动和熟练的外交技巧，这个王国变成了一个无限的平面二维曲面。因为没有边界，这种方式大大地简化了王国的出行。

王国内准备举行一个盛大的节日。人们能聚集在$n$个地点。因为国王想要近一点地看到他的子民，所以他下令去这些地点旅行。他想在每个地点演讲。起初他的旅行被计划成了一串多边形链$P$:从$P_1$到$P_n$。

国王虽然很明智，但他也已经老了。因此，他的助手想出了一个方法来跳过部分地点，来确保国王演讲的次数能尽可能地少。旅程的新计划需要是一串由某个子序列所构成的多边形链$P$:从$P_1$到$P_n$，正规的表示为：从$P_{i_1}$到$P_{i_m}$，且$1=i_1<i_2<...<i_m=n$。国王的助手知道国王不会允许跳过地点$j$，如果$P_j$与$P_{i_k}$到$P_{i_{k+1}}$这一段的距离超过了$d$，对于每个$k$，$i_k<j<i_{k+1}$。

## 输入
第一行，包含两个整数$n$和$d$，分别表示最初的路线的地点数和跳过地点被允许的距离的最大值（$2≤n≤2000$;$1 \le d \le 10^6$)

接下来$n$行，第$i$行包含两个整数$x_1$和$y_1$，表示点$P_i$的坐标。坐标的绝对值不超过$10^6$。不会出现两个点重合的情况。

## 输出

输出国王经过的地点数量的最小值，答案保证在$d \pm 10^{-4}$内；




------------

时间限制：2秒，内存限制：256MB


---

---
title: "[NWRRC 2014] Expression"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7064
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NWRRC 2014] Expression
## 题目描述



In computing, regular expressions is a powerful tool for text search and string matching. In this problem a simplified version of regular expressions is used:

- An empty string ` ` is a regular expression, only the empty string matches it.

- A single lowercase letter `c` is a regular expression, a string consisting of a single letter $c$ matches it.

- A dot `.` is a regular expression, a string consisting of any single letter matches it.

- Alternation: if $α$ and $β$ are regular expressions then `(α|β)` is a regular expression, a string $s$ matches it only if $s$ matches $α$ or $s$ matches $β$.

- Concatenation: if $α$ and $β$ are regular expressions then `(αβ)` is a regular expression, a string $s$ matches it only if $s =$ `xy`, $x$ matches $α$ and $y$ matches $β$.

- Kleene star: if $α$ is regular expression then `(α∗)` is a regular expression, a string $s$ matches it only if $s$ is empty or $s =$ `xy`, $x$ is nonempty and matches $α$ and $y$ matches $(α∗).$ In other words, $s$ consists of zero or more strings, each of them matches $α.$

Parentheses can be omitted, in this problem Kleene star has the highest priority, concatenation has medium priority and alternation has lowest priority. Thus `abc*|de` means `(ab(c*))|(de)`.

For example, string `abcabcab` matches `a(bc|a)*ab`, but string `abcbab` does not.

Your task is to find the shortest string that matches the given regular expression $E$ and contains the given substring $S$ .


## 输入格式



The first line of the input file contains the regular expression $E$ . The second line of the input file contains the substring $S (1 \le |E| , |S| \le 10 000)$ .

String $S$ consists of lowercase English letters. Expression $E$ consists of lowercase English letters and special characters: dots (`.`), parentheses (`(`) and (`)`), pipes (`|`), and asterisks (`*`).


## 输出格式



Output the shortest possible string $T$ that both matches $E$ and contains $S$ as substring. If there are no such strings, output `NO`.

The string $T$ should contain only lowercase English letters.


## 样例

### 样例输入 #1
```
a.*b
bab

```
### 样例输出 #1
```
abab

```
### 样例输入 #2
```
(ab)*
bb

```
### 样例输出 #2
```
NO

```
## 提示

Time limit: 10 s, Memory limit: 256 MB. 


## 题目翻译

在计算机中，正则表达式是文本搜索和字符串匹配的强力工具。这道题将使用简化后的正则表达式：

+ 一个空字符串()是一个正则表达式，且只有空字符串匹配它。

+ 一个小写字母(c)是一个正则表达式，只有仅包含一个字母 $c$ 的字符串匹配它。

+ 点(.)是一个正则运算符，任何仅包含一个字母的字符串都匹配它。

+ 或运算：若 $\alpha$ 和 $\beta$ 是正则表达式，则 ( $\alpha$ | $\beta$ ) 是正则表达式；当且仅当字符串 $s$ 匹配 $\alpha$ 或 匹配 $\beta$ 时，$s$ 匹配 ( $\alpha$ | $\beta$ )。

+ 与运算：若 $\alpha$ 和 $\beta$ 是正则表达式，则 ( $\alpha\beta$ ) 是正则表达式；当且仅当字符串 $s$ 可以分为两个子串 $x$ 和 $y$ ，且 $x$ 匹配 $\alpha$ ，$y$ 匹配 $\beta$ 时，$s$ 匹配 ( $\alpha\beta$ )。

+ 星号运算：若 $\alpha$ 是正则表达式，则 ( $\operatorname{\alpha_*}$ ) 是正则表达式；当且仅当字符串 $s$ 为空或 $s$ 可以被分为若干个匹配 $\alpha$ 的子串时，$s$ 匹配 ( $\operatorname{\alpha_*}$ )。

在本题中，括号可以被省略；运算符的优先级从高到低依次为：星号运算、与运算，或运算。所以 ( $abc_*$ | $de$ ) 即 ( $ab$ ( $c_*$ )) | ( $de$ ) 。

举个例子，字符串 $abcabcab$ 匹配 ( $a$ ( $bc$ | $a$ )$_*ab$ )，而字符串 $abcbab$ 并不匹配它。

现给定正则表达式 $E$ 和字符串 $S$ ，要求找出最短的匹配 $E$ 的字符串 $T$ ，且 $T$ 必须包含 $S$ 。


---

---
title: "[NEERC 2016] Indiana Jones and the Uniform Cave"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7123
tag: ['2016', '交互题', 'Special Judge', 'ICPC']
---
# [NEERC 2016] Indiana Jones and the Uniform Cave
## 题目背景

这是一道 IO 交互题。
## 题目描述

Indiana Jones has stuck in the Uniform Cave. There are many round chambers in the cave, and all of them are indistinguishable from each other. Each chamber has the same number of one-way passages evenly distributed along the chamber’s wall. Passages are indistinguishable from each other, too. The Cave is magical. All passages lead to other chambers or to the same one. However, the last passage, after all passages are visited, leads to the treasure. Even the exact number of chambers is a mystery. It is known that each chamber is reachable from each other chamber using the passages.

Dr. Jones noticed that each chamber has a stone in the center. He decided to use these stones to mark chambers and passages. A stone can be placed to the left or to the right of one of the passages. When Indiana Jones enters the chamber all that he can observe is the location of the stone in the chamber. He can move the stone to the desired location and take any passage leading out of the chamber.

Your task is to help Indiana Jones to visit every passage in the Uniform Cave and find the treasure.
## 输入格式

First, the testing system writes the integer m — the number of passages in each chamber ($2 \leq m \le 20$).

Dr. Jones enters the chamber and sees, in the next line, where the stone is placed: either in the “center” of the chamber or to the “left”, or to the “right” of some passage. On the first visit to the chamber, the stone is in the center.

Your solution shall output his actions: the number and the side of the passage to place the stone to, and the number of the passage to take. Both numbers are relative to the passage marked by the stone, counting clockwise from 0 to m − 1. If the stone is in the center of the chamber, the origin is random.

For example, “3 left 1” tells that Dr. Jones moves the stone three passages clockwise and places it to the left of the passage, then he takes the passage to the right of the initial stone position.

After each move testing system tells either the location of the stone in the next chamber or “treasure”, if Indiana Jones had found it. The testing system writes “treasure” when all the passages are visited.

If Dr. Jones does not find the treasure room after 20 000 passages are taken, he starves to death, and your solution receives the “Wrong Answer” outcome. You also receive this outcome if your solution terminates before all passages are taken.

The total number of chambers in the cave is unknown, but you may assume that it does not exceed 20, and that each chamber is reachable from every other chamber.
## 样例

### 样例输入 #1
```
2
center
left
center
left
right
treasure

```
### 样例输出 #1
```
0 left 0
1 left 1
1 right 0
0 left 0
1 right 0

```
## 提示

Dr. Jones enters the example cave and sees that the stone in the first chamber is in the center. He marks the chamber by placing the stone to the left of some passage and takes it. He sees the chamber where the stone is to the left of the passage, so he is in the first chamber again. He moves the stone clockwise and takes the passage marked by it. This passage leads to the second chamber. He marks it by placing the stone to the right of some passage and takes another one. He is in the first chamber again, so he returns to the second chamber and takes the remaining passage. This passage leads to the treasure.
## 题目翻译

现在在一个洞穴里寻宝。这个洞穴有 $n$ 个房间。房间是不可区分的。每个房间都引出 $m$ 个单向道路，终点可以是自己也可以是其它房间。这些单向道路的入口均匀地分布在房间的墙壁上，且每条单向道路也是不可区分的。保证整个有向图是强连通的。你一开始在某一个房间，如果遍历了所有的边，就能找到宝藏。

每个房间有一个石子，这也是你区分房间和道路的唯一工具。一开始石子是在这个房间的某一个通道的入口前，并且是放在中央的。你每到一个房间，可以选择将石子移动到某个通道前，把它放在通道左边或者右边（不能是中间），然后再从某个通道走出去。你不可以把石子带出房间。你并没有携带过多的食物，所以如果你走了超过 $20000$ 条边，你就会因为食物耗尽而饿死。你要在规定步数之内找到宝藏。

### 输入格式

共 $m$ 行，每行一个字符串，表示该房间内石头被放置的位置为某个通道的 $"center"$，$"left"$ 或 $"right"$。当第一次到达一个墓室时，石头处在中间(center)。

### 输出格式

每行一个非负整数 $st$，表示将石头放在原所在位置顺时针方向第 $st$ 个通道入口；一个字符串，表示将它放在该通道入口 $dir$ 的位置（$"center"$，$"left"$ 或 $"right"$）；一个非负整数 $pa$ ，表示从石子的原来位置顺时针方向第 $pa$ 个通道走出。

通道顺时针从 $0$ 到 $m−1$ 编号。如果石头一开始是在中间（$center$），它会位于随机一个通道入口处。

每走一步，评测机会返回该房间的石头的位置或者 $"treasure"$ （如果您找到了宝藏且所有的通道都被走过时，就会反馈 $"treasure"$ ）。

**举个栗子**：`3 left 1` 表示将石头顺时针移动了 $3$ 个通道，并将其放置在该通道的左侧，然后走向最初石头所在位置的右侧的通道。

你最多可以进行 $20000$ 次操作。


---

---
title: "[ICPC 2020 WF] QC QC"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8135
tag: ['2020', '交互题', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] QC QC
## 题目背景

ICPC2020 WF H
## 题目描述


Innovative Computable Quality Control (ICQC) has developed a ground-breaking
new machine for performing, well, quality control. Thanks to
its novel Deep Intelligence technology, an ICQC quality control (QC)
machine can automatically, with $100\%$ accuracy, detect manufacturing
errors in any machine in existence, whether it is a coffee machine, an
intergalactic space ship, or a quantum computer.

ICQC is now setting up its factory for producing these QC
machines. Like any other manufacturing process, some fraction of
the produced machines will suffer from malfunctions and these need to
be found and discarded. Fortunately, ICQC has just the product
for detecting malfunctioning machines!

Obviously, ICQC should not simply use a QC machine on itself, since
a malfunctioning machine might incorrectly classify itself as working
correctly. Instead, ICQC will take each batch of $n$ machines
produced during a day and have them test each other overnight.
In particular, during every hour of the night, each of the $n$ QC
machines can run a check on one of the other QC machines, and
simultaneously be checked by one other QC machine.

If the machine running the check is correct, it will correctly report
whether the tested machine is correct or malfunctioning, but if the
machine running the check is malfunctioning, it may report either result.
If a machine A is used to test a machine B multiple times it will return the same result every time, even if machine A is malfunctioning.
The exact testing schedule does not have to be fixed in advance,
so the choice of which machines should check which other machines during
the second hour of the night may be based on the result of the tests
from the first hour, and so on.

ICQC are $100\%$ confident that strictly more than a half of the $n$ QC
machines in each batch are working correctly, but the night is only $12$
hours long, so there is only time to do a small number of test rounds.
Can you help ICQC determine which QC machines are malfunctioning?

For example, consider Sample Interaction 1 below. After the fourth hour,
every machine has tested every other machine. For machine $1$,
only one other machine claimed that it was malfunctioning, and if it
was truly malfunctioning then at least $3$ of the other machines would
claim this. For machine $4$, only one other machine claims that it
is working, which implies that machine $2$ must be malfunctioning since
more than half of the machines are supposed to be working. Note that
even though machine $4$ is malfunctioning, it still happened to produce
the correct responses in these specific test rounds.




## 输入格式

## Interaction


The first line of input contains a single integer $b$ ($1 \le b \le 500$),
the number of batches to follow. Each batch is independent.
You should process each batch
interactively, which means the input you receive
will depend on the previous output of your program.

The first line of input for each batch contains a single integer $n$
($1 \le n \le 100$), the number of QC machines in the batch.
The interaction then proceeds in rounds. In each round, your program can
schedule tests for the next hour, by writing a line of
the form
"$\texttt{test}$ $\ x_1\ x_2\ \ldots\ x_n$"
indicating that each machine $i$ should run a test on machine $x_i$.
If $x_i=0$, then machine $i$ is idle in that round and performs no test.
All positive numbers in the sequence must be distinct.

After writing this line, there will be a result to read from the
input. The result is one line containing a string of length
$n$, having a '$\texttt{1}$' in position $i$ if machine $i$ says that machine $x_i$
is working correctly, '$\texttt{0}$' if machine $i$ says that machine $x_i$ is
malfunctioning, and '$\texttt{-}$' (dash) if machine $i$ was idle in the round.

When your program has determined which machines are malfunctioning,
but no later than after $12$ rounds of tests,
it must write a line of the form
"$\texttt{answer}$ $S$"
where $S$ is a binary string of length $n$, having a '$\texttt{1}$' in position $i$
if machine $i$ is working correctly, and a '$\texttt{0}$' if it is malfunctioning.

After writing the answer line, your program should start processing
the next batch by reading its number $n$. When all $b$ batches have been
processed, the interaction ends and your program should exit.


*Notes on interactive judging:*

- *The evaluation is non-adversarial, meaning that the result of each
machine testing each other machine is chosen in advance rather than in
response to your queries.*
- *Do not forget to flush output buffers after writing. See the Addendum to Judging Notes for details.*
- *You are provided with a command-line tool for local testing, together with input files
corresponding to the sample interactions.
The tool has comments at the top to explain its use.*



## 样例

### 样例输入 #1
```
1
5
10101
01110
10101
10101
10101

```
### 样例输出 #1
```
test 5 4 2 1 3
test 4 5 1 3 2
test 2 3 4 5 1
test 3 1 5 2 4
answer 10101
```
### 样例输入 #2
```
2
4
1111
7
0001100
----11-
```
### 样例输出 #2
```
test 2 3 4 1
answer 1111
test 2 3 4 5 6 7 1
test 0 0 0 0 2 4 0
answer 0101110
```
## 题目翻译

**【题目描述】**

创新的可计算质量控制（ICQC）开发了一种开创性的新机器，用于执行良好的质量控制。得益于其新颖的深度智能技术，ICQC 质量控制（QC）机器能够以 $100\%$ 的准确度自动检测现有任何机器的制造错误，无论是咖啡机、星际飞船还是量子计算机。

ICQC 目前正在建立工厂生产这些 QC 机器。像任何其他制造过程一样，生产的机器中有一部分会出现故障，需要找到并丢弃。幸运的是，ICQC 只有检测故障机器的产品！

显然，ICQC 不应该简单地在自己身上使用 QC 机器，因为出现故障的机器可能会错误地将自己归类为正常工作。相反，ICQC 将在一天内生产每批 $n$ 机器，并让它们在一夜之间相互测试。特别是，在夜间的每一个小时，每个 $n$ QC机器都可以在另一台 QC 机器上运行检查，同时由另一台 QC 机器进行检查。

如果运行检查的机器是正确的，它将正确地报告测试机器是正确的还是故障的，但如果运行检查的机器是故障的，它可能会报告任何一个结果。如果使用机器 A 多次测试机器B，即使机器 A 出现故障，每次都会返回相同的结果。准确的测试时间表不必事先确定，因此，在夜间第二个小时，哪些机器应该检查哪些其他机器，可以根据第一个小时的测试结果来选择，以此类推。

ICQC $100\%$ 确信，严格来说，每批 $n$ QC 机器中有一半以上工作正常，但夜间只有$12$ 小时，因此只有时间进行少量测试。您能帮助 ICQC 确定哪些 QC 机器出现故障吗？

例如，考虑下面的样本交互作用 $1$。在第四个小时之后，每台机器都测试了其他每台机器。对于机器 $1$，只有另一台机器声称它有故障，如果它真的有故障，那么其他机器中至少有 $3$ 台会声称这一点。对于机器$4$，只有另一台机器声称它正在工作，这意味着机器 $2$ 一定有故障，因为超过一半的机器应该在工作。请注意，尽管机器 $4$ 出现故障，但在这些特定的测试回合中仍碰巧产生了正确的响应。

**【输入格式】**

第一行输入包含一个整数 $b$（$1≤ b≤500$），要遵循的批次数。每批都是独立的。您应该以交互方式处理每个批，这意味着您收到的输入将取决于您的程序之前的输出。

每个批次的第一行输入包含一个整数 $n$ （$1≤n≤100$），批次中 QC 机器的数量。然后，交互循环进行。在每一轮中，你的程序都可以通过写一行表格来安排下一个小时的测试 “ $\texttt{test}$ $x_1$ $x_2$ $x_n$”指示每台机器 $i$ 应在机器 $x_i$ 上运行测试。如果 $x_i$ 为 $0$，然后，机器 $i$ 在该轮中处于空闲状态，不执行任何测试。序列中的所有正数必须是不同的。

写下这一行后，将有一个从输入中读取的结果。结果是一行包含长度为 $n$ 的字符串，如果机器 $i$ 表示机器 $x_i$，则在位置 $i$ 处有“$\texttt{1}$”，$x_i$ 工作正常，“$\texttt{0}$” 如果机器 $i$ 显示机器 $x_i$ 出现故障，如果机器 $i$ 在循环中处于空闲状态，则为“$\texttt{-}$”（破折号）。

当您的程序确定哪些机器出现故障时，但不迟于 $12$ 轮测试之后，它必须以“$\texttt{answer}$ $S$”的形式写一行，其中 $S$ 是长度为 $n$ 的二进制字符串，如果机器 $i$ 正常工作，则在位置 $i$ 处有“$\texttt{1}$”，如果机器 $i$ 出现故障，则在位置 $i$ 处有“$\texttt{0}$”。

在写下答案行之后，你的程序应该通过读取下一批的编号 $n$ 来开始处理下一批。当所有 $b$ 批处理完成后，交互结束，程序应该退出。

关于互动评判的说明：
 - 评估是非对抗性的，这意味着每台机器测试另一台机器的结果是提前选择的，而不是响应您的查询。
- 写入后不要忘记刷新输出缓冲区。有关详细信息，请参见《评委须知》附录。
- 我们为您提供了一个用于本地测试的命令行工具，以及与示例交互相对应的输入文件。该工具顶部有注释解释其用途。


---

---
title: "[ICPC 2020 WF] Space Walls"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8138
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] Space Walls
## 题目背景

ICPC2020 WF K
## 题目描述

Place-Y Technology Corp. plans to launch a new space station soon. The company
CEO is known for being obsessed with perfection. For example, he insists that all
the outer surfaces of the space station are regularly polished and cleaned of
what he calls ``space debris,'' mainly for the station to appear good in photos.
The engineering team tried but failed to convince the CEO that this was not needed. So instead they
developed an innovative technology to maintain the surfaces while minimizing human
operations outside the station. The maintenance is performed by several
small robots moving over the space station surface, just like robotic
vacuum cleaners. Before their first flight, Place-Y needs to assess the risks of
collision during the operation of the robots. And this is exactly where you step
in.

For the purposes of this problem, we model the space station as a collection of
axis-aligned unit cubes (not necessarily connected). Each robot starts at time $t=0$ in the center of an exposed face
of one of the station's unit cubes (that is, a face which is not shared by a second station
cube). The robot is oriented in one of the four directions parallel to an edge of the cube face.
Every time unit, the robot moves straight ahead to another cube face, possibly
pivoting $90$ degrees across the space station edges so that it always maintains
contact with the station.  Note that if two cubes share an edge, the robot cannot
slip between them (there is no gap).

![](https://cdn.luogu.com.cn/upload/image_hosting/sh28cno8.png)

Given the layout of the station and starting
positions of all the cleaning robots, determine the time of the earliest collision (if any).  The time a collision occurs is either the time unit when two or more robots are on the interior of the same cube
face or the time unit when two robots attempt to swap locations (see Sample Input 3 for the
latter case).
## 输入格式

The first line of input contains two integers $n$ and $k$, where $n$
($1 \le n \le 100$) is the number of regions describing the space station shape,
and $k$ ($0 \le k \le 100$) is the number of robots on the surface.

Each of the following $n$ lines contains six integer coordinates $x_1$, $y_1$, $z_1$,
$x_2$, $y_2$, and $z_2$ ($0 \le x_1 < x_2 \le 10^6$, $0 \le y_1 < y_2 \le 10^6$,
$0 \le z_1 < z_2 \le 10^6$) describing one region and denoting that all the points
$x,y,z$ satisfying $x_1 \le x \le x_2$, $y_1 \le y \le y_2$,
$z_1 \le z \le z_2$ are part of the space station. Note that some
unit cubes may be included in more than one region.

Then follow $k$ lines, each describing the starting position of one robot.  Such
a line contains three coordinates $x$, $y$, and $z$, and two directions $\vec{f}$
and $\vec{d}$. The coordinates specify that the robot starts at a face of the
unit cube $(x,y,z) - (x+1,y+1,z+1)$. The particular face is determined by
$\vec{f}$ and the initial direction of movement is determined by $\vec{d}$.
Both $\vec{f}$ and $\vec{d}$ are specified by one of the six strings $\tt x+$, $\tt x-$, $\tt y+$,
$\tt y-$, $\tt z+$, or $\tt z-$, where $\tt x+$ designates the positive direction
of the x-axis $(1,0,0)$, and so on. The axis letter in $\vec{f}$ will be different
from the axis letter in $\vec{d}$. It is guaranteed that the starting cube
belongs to the space station and the given face is an exposed face.
## 输出格式

Output the time of the first collision. If there will never be a collision,
output $\tt ok$.
## 样例

### 样例输入 #1
```
9 2
1 1 1 7 7 7
0 0 0 3 3 3
5 0 0 8 3 3
0 5 0 3 8 3
0 0 5 3 3 8
5 5 0 8 8 3
5 0 5 8 3 8
0 5 5 3 8 8
5 5 5 8 8 8
0 1 0 z- x+
3 5 1 z- y+
```
### 样例输出 #1
```
44
```
### 样例输入 #2
```
1 3
0 0 0 1 1 1
0 0 0 x+ z+
0 0 0 y+ x+
0 0 0 z- y+
```
### 样例输出 #2
```
ok
```
### 样例输入 #3
```
1 2
0 0 0 2 1 1
0 0 0 y+ x+
1 0 0 y+ x-
```
### 样例输出 #3
```
0
```
## 题目翻译

### 输入格式

每个机器人每次启动一开始t=0
每次机器人到另一个面，可能会旋转90°两个立方体共享一条边时，机器人无法在之间走动。

第一行输入n,k,n是空间站形状的区域数,k是机器人的数量。

接下来n行6个数据分别是：($0 \le x_1 < x_2 \le 10^6$, $0 \le y_1 < y_2 \le 10^6$,
$0 \le z_1 < z_2 \le 10^6$) 

是一个区域中的所有点。满足$x_1 \le x \le x_2$, $y_1 \le y \le y_2$,
$z_1 \le z \le z_2$
请注意，一些立方体可能包含在多个区域中。

接下来k行，每一行代表机器人的位置。有x,y,z以及两个方向f,d,指定面由f确定,初始移动方向由d确定.六种操作x+,x-,y+,y-,z+,z-.
x+表示（1,0,0）的方向，依此类推。f不等于d.

保证起始立方体属于空间站，并且给定的初始面是外面。

### 输出格式
输出第一次碰撞的时间。如果永远不会发生冲突，则输出ok


---

---
title: "[ICPC 2020 WF] Sweep Stakes"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8139
tag: ['2020', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] Sweep Stakes
## 题目背景

ICPC2020 WF L
## 题目描述

You may have already won! In fact, you did already win! You won your very own
island, in the deepest reaches of the unexplored ocean! Well, mostly unexplored.
As it happens, there was a small military base there before you, and when they
packed up and flew out they left behind an assortment of scraps, munitions,
tunnels, $\ldots$ and unexploded defensive ordnance. That's right: You now possess
your very own minefield.

The minefield consists of an $m\times n$ grid, with any square of the grid holding
0 or 1 mines. Fortunately, you were able to recover the engineers' plans from when
they deployed the mines. Unfortunately, the exact locations of the mines were never
written down: the engineers had a preselected independent probability of deploying
a mine in each square. However, you do know how many mines were placed in total.

You would like to estimate how safe various parts of your island are. Write a
program to compute the probability of mine counts over various subsets of the
minefield.
## 输入格式

The first line of input contains four integers $m$, $n$, $t$, and $q$, where $m$
and $n$ ($1 \leq m,n \leq 500$) are the dimensions of the minefield, $t$ 
($0 \leq t \leq mn$) is the total number of mines, and $q$ ($0 \leq q \leq 500$)
is the number of queries. The second line contains $m$ real numbers 
$p_1, p_2, \ldots, p_m$ ($0 \leq p_i \leq 0.1$ for all $i$, with at most six digits
after the decimal point specified), and the third line
contains $n$ real numbers $q_1, q_2, \ldots, q_n$ ($0 \leq q_j \leq 0.1$ for all
$j$, with at most six digits after the decimal point specified).
The preselected probability of the engineers placing a mine on square $(i, j)$
is $p_i + q_j$. All choices of whether to place a mine on a given square were made
independently, and the value of $t$ is chosen so that the probability of deploying
exactly $t$ mines is at least $10^{-5}$. 

Each of the remaining $q$ lines describes a single query. Each of those lines
begins with an integer $s$ ($0 \leq s \leq 500$), followed by $s$ pairs of integers
$i$ and $j$ ($1 \leq i \leq m$, $1 \leq j \leq n$), which are the coordinates of $s$
distinct squares in the grid.
## 输出格式

For each query with $s$ squares, output $s+1$ real numbers, which are the
probabilities of the $s$ given squares containing $0, 1, \ldots, s$ mines. Your
answer should have an absolute error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
2 2 1 2
0.05 0.05
0.05 0.05
1 1 1
2 2 1 1 2
```
### 样例输出 #1
```
0.75 0.25
0.5 0.5 0
```
### 样例输入 #2
```
3 4 3 4
0.02 0.04 0.06
0.005 0.07 0.035 0.09
1 3 2
3 1 4 2 4 3 4
4 1 2 2 3 3 1 1 4
8 1 1 1 2 1 3 2 1 2 3 3 1 3 2 3 3
```
### 样例输出 #2
```
0.649469772 0.350530228
0.219607636 0.527423751 0.237646792 0.015321822
0.267615440 0.516222318 0.201611812 0.014550429 0
0.054047935 0.364731941 0.461044157 0.120175967 0 0 0 0 0
```
## 题目翻译

你赢得了自己的岛屿，在未开发海洋的最深处！那里有一个小型军事基地，当他们收拾行李飞走时，留下了各种碎片、弹药、隧道、炸弹……以及未爆炸的防御弹药。你现在拥有了自己的雷区。

雷场由 $m\times n$ 的网格组成，网格的任何正方形都有 0 或 1 枚地雷。幸运的是，你能够从工程师部署地雷时恢复他们的计划。不幸的是，地雷的确切位置从未被写下来：工程师们在每个方格部署地雷的预先选择的独立概率。然而，你知道总共埋设了多少枚地雷。

你想估计一下你所在岛屿的各个部分有多安全。请编写一个程序来计算雷区各子集上地雷计数的概率。误差需小于 $10^{-6}$。


---

---
title: "[ICPC 2020 WF] What’s Our Vector, Victor?"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8141
tag: ['2020', 'Special Judge', 'O2优化', '线性代数', 'ICPC']
---
# [ICPC 2020 WF] What’s Our Vector, Victor?
## 题目背景

ICPC2020 WF N
## 题目描述

Vector embeddings are a common tool in machine learning systems.
Complex real-world concepts (for instance, words in a dictionary) are mapped onto vectors of real numbers.
If embeddings are trained properly, related concepts remain close together in the vector space, so questions like "are these two words synonyms?" can be reduced to straightforward mathematical tests.

You have been hired by Ye Olde Ice Cream Shoppe to create an embedding model for flavors, so that when they are out of an ice cream flavor they can recommend related flavors to customers.
After training your embedding on six cloud datacenters for four months, you finally had the perfect flavor model!
You were ready to revolutionize the ice cream industry on your street and, dare we say it, your neighborhood!
Well, until you accidentally dripped some free ice cream on your keyboard and deleted half the data.
The Shoppe cannot afford the 30 billion rubles needed to retrain the model, so you are in trouble.

Fortunately, you still have various training results lying around.
For a given deleted vector, the training data tells you how close it was to some known flavor vectors.
The closeness of vectors $A$ and $B$ is just the standard Euclidean distance metric (that is, the length of the vector $A - B$).
Write a tool that reconstructs embeddings which are consistent with the training results.
## 输入格式

The first line contains two integers $d$ and $n$, where $d$ ($1 \leq d \leq 500$) is the number of dimensions of the
vectors, and $n$ ($1 \leq n \leq 500$) is the number of training results for a deleted embedding vector you want to reconstruct.
Each of the next $n$ lines describes a training result using $d + 1$ numbers $x_1, \dots, x_d$ and $e$.
In a training result, $x_1, \dots, x_d$ ($-100 \leq x_i \leq 100$) are the coordinates of a known vector, and 
$e$ ($0 \leq e \leq 5\,000$) is the Euclidean distance from that vector to the deleted one.

Your submission will be tested only with the sample inputs given below and inputs generated according to the following procedure.
First, $d$ and $n$ are chosen.
Then, $n$ input vectors and $1$ output vector, each with dimension $d$, are chosen at random.
The $d \cdot (n + 1)$ coordinates are independent and uniformly distributed in the interval $[-100,100]$.
Next, the Euclidean distance from each input vector to the output vector is computed.
Finally, the output vector is discarded.
Calculations use double-precision floating-point numbers.
Numbers obtained using this procedure appear in the input with $17$ digits after the decimal point.
## 输出格式

Output $d$ values, the coordinates of any vector that has the given distance to each training vector with an absolute or relative error of at most $10^{-5}$.
## 样例

### 样例输入 #1
```
2 3
0 0 2.5
3 0 2.5
1.5 0.5 2.5
```
### 样例输出 #1
```
1.5 -2
```
### 样例输入 #2
```
2 2
0 0 2
4 -4 6
```
### 样例输出 #2
```
1.414213562373 1.414213562373
```
### 样例输入 #3
```
4 3
0 1 2 3 2
1 2 -1 7 5
1 0.3 3.4 1.2 3.3
```
### 样例输出 #3
```
1 2 3 4
```
## 题目翻译

**【题目描述】**

向量嵌入是机器学习系统中的一种常用工具。现实世界中的某些复杂的概念（例如词典中的单词）通过这种方法可以映射到一个实向量上。如果能让机器正确地训练向量嵌入，由于相关概念在向量空间中保持着紧密的联系，因此像“这两个单词是同义词吗？”这种问题可以简化为简单的数学测试了。

你最近被 Ye Olde 冰淇淋专柜受雇，专门负责为冰淇淋口味创建一个向量嵌入式模型，这样当一种口味的冰淇淋卖完以后，这个嵌入式模型就可以像顾客推荐其它味道相近的冰淇淋。在六个云数据中心里训练了四个月以后，你终于拥有了一个完美的模型，正准备好改变你所在街区的冰淇淋行业，乃至整个街区时，你不小心把一些免费的冰淇淋滴到了键盘上，导致一半的数据被删除。重新训练模型需要花费 300 亿卢布，而专柜显然承受不了这么高的价格，因此你陷入了巨大的麻烦之中。幸运的是，你可以通过剩下的数据来还原出被删除的向量。具体地，对于一个给定的被删除的向量，数据会告诉你它与某些已知的味道向量的接近程度。两个向量 $A,B$ 的接近程度即为这两个向量之间的标准欧几里得距离（即向量 $A-B$ 的长度）。

现在，给定向量所处的空间维度 $d$ 和已知向量个数 $n$，并给定所有 $n$ 个向量的坐标 $(x_{i,1},x_{i,2},\cdots,x_{i,d})$ 和到同一个被删除的向量的标准欧几里得距离 $e_i$，请你编写一个程序，求出被删除的向量的坐标。

**【输入格式】**

第一行输入两个整数 $d,n$，分别表示向量空间的维度和向量个数。  
随后 $n$ 行，每行 $d+1$ 个实数 $x_{i,1},x_{i,2},\cdots,x_{i,d},e_i$，其中前 $d$ 个实数描述了第 $i$ 个向量的坐标，第 $d+1$ 个实数则表示第 $i$ 个向量与被删除的向量之间的标准欧几里得距离。

你提交的代码只会在样例输入数据和按以下方式生成的输入数据上进行测试：

- 在区间 $[1,500]$ 中选出两个整数作为 $d,n$。
- 随机生成 $n$ 个 $d$ 维输入向量和一个 $d$ 维输出向量。这 $d\cdot(n+1)$ 个坐标在区间 $[-100,100]$ 中独立且均匀地生成。
- 对于每个输入向量，计算其与输出向量之间的标准欧几里得距离。
- 忽略输出向量。

所有在上述过程中的计算使用双精度浮点数，用这种方式生成的所有实数均保留到小数点后 $17$ 位。

**【输出格式】**

输出 $d$ 个整数，描述被删除向量的坐标。你需要保证你输出的答案和标准答案之间的误差不会超过 $10^{-5}$。

**【样例】**

见『输入输出样例』部分。

**【数据范围】**

对于所有数据：

- $1\leqslant d,n\leqslant 500$。
- $-100\leqslant x_{i,j}\leqslant 100$。
- $0\leqslant e_i\leqslant 5000$。

Translated by Eason_AC


---

---
title: "[ICPC 2022 Xi'an R] Square Grid"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9366
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Square Grid
## 题目描述

Given a square grid, its lattice points labeled from $(0, 0)$ to $(n, n)$, and a number $t$.

You need to answer $q$ queries in this format: given $A = (x_0, y_0)$ and $B = (x_1, y_1)$, how many ways are there to move from $A$ to $B$ in exactly $t$ steps so that in each step you move from a lattice point to one of its neighbors (up, down, left, right). Calculate the answer modulo $998\,244\,353$.
## 输入格式

The first line contains three integers $n$ ($1 \leq n \leq 10^5$), $t$ ($1 \leq t \leq 10^9$) and $q$ ($1 \leq q \leq 3 \times 10^5$).

Each of the following $q$ lines contains four integers $x_0$, $y_0$, $x_1$ and $y_1$ ($0 \leq x_0, y_0, x_1, y_1 \leq n$), representing a query. 
## 输出格式

For each query, output a line containing one integer, representing the answer to the query modulo $998\,244\,353$.
## 样例

### 样例输入 #1
```
2 5 3
0 0 1 2
1 1 2 1
0 0 2 2

```
### 样例输出 #1
```
30
64
0

```
### 样例输入 #2
```
5 20 5
0 0 5 5
1 1 4 4
2 2 3 3
2 3 2 3
1 2 5 2

```
### 样例输出 #2
```
615136704
443203969
899931333
464755094
679729107

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem I.

**Author**: djq_cpp.
## 题目翻译

给定正方形网格，格点坐标从 $(0,0)$ 到 $(n,n)$。

$q$ 组询问，每次询问从 $(x_0, y_0)$ 走恰好 $t$ 步，每步只能朝上、下、左、右走一格，不走出边界，走到 $(x_1, y_1)$ 的方案数，对 $998\,244\,353$ 取模。所有询问的 $t$ 相同。


---

---
title: "[ICPC 2021 WF] Guardians of the Gallery"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9442
tag: ['2021', 'Special Judge', 'ICPC']
---
# [ICPC 2021 WF] Guardians of the Gallery
## 题目描述

Your local art gallery is about to host an exciting new exhibition of sculptures by world-renowned artists, and the gallery expects to attract thousands of visitors. Unfortunately, the exhibition might also attract the wrong kind of visitors, namely burglars who intend to steal the works of art. In the past, the gallery directors did not worry much about this problem, since their permanent collection is, to be honest, not really worth stealing.

The gallery consists of rooms, and each sculpture in the new exhibition will be placed in a different room. Each room has a security guard and an alarm to monitor the artwork. When an alarm sounds, the guard will run (without leaving the room) from their post to a position where they can see the sculpture directly. This is to check whether the sculpture has in fact been stolen, or whether this is yet another false alarm.

To figure out where to best station the security guard, the gallery directors would like to know how long it takes for the guard to see a given sculpture. They hope that you can help!

Every room is on a single floor, and the layout of the walls can be approximated by a simple polygon. The locations of the guard and the sculpture are distinct points strictly inside the polygon. The sculpture is circular, with a negligibly small (but positive) radius. To verify that the sculpture is still present, the guard needs to be able to see at least half of it.

Figure D.1 illustrates two examples. In each case, the guard starts at the blue square on the left, and the sculpture is located at the red circle on the right. The dotted blue line shows the optimal path for the guard to move. Once the guard reaches the location marked by the green diamond, half of the sculpture can be seen.

![](https://cdn.luogu.com.cn/upload/image_hosting/ugrzp1ry.png)
## 输入格式

The first line of input contains an integer $n$ ($3 \leq n \leq 100$), the number of vertices that describe the polygon. This is followed by $n$ lines each containing two integers $x$ and $y$ ($0 \leq x,y \leq 1000$), giving the coordinates of the polygon vertices in counterclockwise order. The next line contains two integers $x_g$ and $y_g$, which specify the location of the guard. Finally, the last line contains two integers $x_s$ and $y_s$, which specify the location of the center of the sculpture. The polygon is simple, that is, its vertices are distinct and no two edges of the polygon intersect or touch, other than consecutive edges which touch at their common vertex. In addition, no two consecutive edges are collinear.
## 输出格式

Output the minimum distance that the guard has to move to be able to see at least half the sculpture. Your answer must have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
8
0 0
20 0
20 30
60 30
60 0
80 0
80 50
0 50
10 10
70 10

```
### 样例输出 #1
```
58.137767414995

```
### 样例输入 #2
```
11
0 0
4 0
4 1
5 1
5 0
7 0
7 2
3 2
3 1
2 2
0 2
1 1
6 1

```
### 样例输出 #2
```
2.000000000000

```
## 题目翻译

#### 简要题意
给定封闭的 $n$ 边形不透明墙壁和其中两个点 $A, B$. 其中，$B$ 是一个半径充分小但大于 $0$ 的透明圆的圆心, 墙壁厚度可视为 $0$. 求所有能直接观察到 $\odot B$ 的至少一半的位置中, 与点 $A$ 距离的最小值.

#### 输入格式
第一行, 一个整数 $n$.

随后 $n$ 行, 每行两个整数 $x_i, y_i$, 依次表示其顶点的坐标。

随后一行, 两个整数 $x_A, y_A$, 表示点 $A$ 的坐标.

最后一行, 两个整数 $x_B, y_B$, 表示圆心 $B$ 的坐标.

#### 输出格式
一行，一个实数，表示最小距离。与标准答案误差不超过 $10^{-6}$ 即可判为正确。


---

---
title: "[ICPC 2021 WF] Take On Meme"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9449
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Take On Meme
## 题目描述

The Internet can be so fickle. You work for a small ad agency, Mimi's Mammoth Memes. Your ad campaigns are very cheap, and rely on the hope of producing the next hit viral meme. Unfortunately, the last four hundred or so memes have failed to take off, despite having been precisely engineered to appeal to every single person on Earth. You're not sure what exactly went wrong, but you've decided to try a new approach: crowd sourcing!

According to your scientific meme theory, all memes can be rated from $-\infty$ to $\infty$ on two scales: xanthochromism, and yellowishness, also known as ($x$, $y$) values. Obviously (you think), the best memes are memorable for being particularly xanthochromic, yellowish, unxanthochromic, or unyellowish. You feel that the "quality" of any meme is directly measurable as its squared Euclidean distance ($x^2 + y^2$) from the Base Meme ($0$, $0$), otherwise known as All Your Base.

To produce the ultimate viral meme, you'll be taking your company's last few failed memes and throwing them into a tournament, decided by online voting. The tournament can be represented as a rooted tree. Input memes come in at the leaves, and at each internal node, a vote will be held among its $k$ child memes ($x_1$, $y_1$), $\ldots$, ($x_k$, $y_k$). After the vote, all the memes will be horrifically mangled and merged into a brand new meme, specifically calculated to emphasize the winner and de-emphasize all the losers: the resultant $x$ value will be $$ \sum_{i=1}^{k} w_i \cdot x_i, $$ where $w_i$ is $1$ if the $i^{th}$ child won, and $-1$ otherwise. The $y$ value is computed similarly. This new meme will move on to the next vote in the tournament $-$ or, if there is no parent, it will be declared the champion and the ultimate meme!

You already have the structure of the tournament planned out, including all the input memes and the internal voting nodes. What is the largest possible quality for any meme that the tournament could produce?
## 输入格式

The first line of input contains an integer $n$ ($1 \leq n \leq 10^4$), giving the total number of nodes in the tournament tree. The next $n$ lines each describe a single tree node indexed from $1$ to $n$. The line for node $i$ starts with an integer $k_i$ ($0 \leq k_i \leq 100$), the number of children of that node. If $k_i$ is $0$, then node $i$ is an input meme and there will be two more integers $x_i$ and $y_i$ ($-10^3 \leq x_i, yi \leq 10^3$) describing it. If $k_i &gt; 0$, then $k_i$ different integers $j$ ($i &lt; j \leq n$) will follow, giving the indices of the $k_i$ nodes entering this voting step.

All input memes will eventually be merged into the final output meme at node $1$. The complete tree will have a height of no more than $10$.
## 输出格式

Output the largest possible quality for the champion meme at node $1$.
## 样例

### 样例输入 #1
```
4
3 2 3 4
0 10 1
0 3 6
0 2 7

```
### 样例输出 #1
```
169
```
### 样例输入 #2
```
8
3 4 2 5
2 3 8
0 -3 9
0 -5 -7
2 6 7
0 1 4
0 -3 -1
0 1 4

```
### 样例输出 #2
```
314
```
## 题目翻译

众所周知，互联网的走红规律总是难以捉摸。你就职于一家名为 Mimi's Mammoth Memes 的小型广告公司。你们的广告策略非常经济实惠，全靠碰运气，使得下一个爆红的病毒式梗图诞生。然而，尽管你们精心设计过，最近的四百多个梗图却无一火爆。你对问题的具体原因并不十分清楚，但决定尝试一种全新的方法：众包创意！

根据你的梗图科学理论，所有梗图都可以在两个维度上被评分，分别是鲜艳度和泛黄程度，简称为 $(x, y)$ 值。显然（你这样认为），最出众的梗图要么特别鲜艳，要么特别不鲜艳，要么特别泛黄，要么特别不泛黄。你认为，一个梗图的“质量”可以直接通过它和基础梗图 $(0, 0)$ 的欧几里得距离平方来衡量，即计算 $(x^2 + y^2)$。

为了创造出终极病毒式梗图，你将把公司最近几个不成功的梗图放入一个通过在线投票来决胜负的锦标赛中。这个锦标赛可以用一棵有根树来表示。输入梗图位于叶子节点，在每个内部节点，针对其 $k$ 个子梗图 $(x_1, y_1),\cdots, (x_k, y_k)$ 进行投票。投票后，梗图将经历恐怖的扭曲并合并成一个新梗图，特别突出了胜者并削弱了所有的败者：得到的 $x$ 值为 

$$ \sum_{i=1}^{k} w_i \cdot x_i, $$ 

其中当第 $i$ 个梗图获胜时，$w_i$ 为 $1$，否则为 $-1$。$y$ 值的计算方式相同。该新梗图将进入锦标赛下一轮的投票——如果它没有父节点，则会被宣布为冠军，也就是最终的完美梗图！

你已经设计好了锦标赛的结构，包括所有输入的梗图和内部的投票节点。那么，该锦标赛可能产生的梗图质量的最大值是多少？

## 输入格式

输入的第一行包含一个整数 $n$ ($1 \leq n \leq 10^4$)，表示锦标赛树中的节点总数。接下来的 $n$ 行，每行描述一个编号从 $1$ 到 $n$ 的节点。对于节点 $i$，这一行先出现一个整数 $k_i$ ($0 \leq k_i \leq 100$)，表示该节点的子节点数。如果 $k_i$ 为 0，则表明节点 $i$ 是一个输入梗图，并包含两个额外整数 $x_i$ 和 $y_i$ ($-10^3 \leq x_i, y_i \leq 10^3$)，描述该梗图的特征值。如果 $k_i > 0$，则接下来会出现 $k_i$ 个不同的整数 $j$ ($i < j \leq n$)，表示参与这一投票步骤的节点索引。

所有输入的梗图将最终被合并为节点 $1$ 中的最终输出梗图。整个树的高度不会超过 $10$。

## 输出格式

输出节点 $1$ 的冠军梗图的最大可能质量。



---

---
title: "[ICPC 2020 Nanjing R] Baby's First Suffix Array Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9623
tag: ['字符串', '2020', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Baby's First Suffix Array Problem
## 题目描述


A suffix array for string $s$ of length $n$ is a permutation $sa$ of integers from $1$ to $n$ such that $s[sa_1.. n], s[sa_2..n], \dots, s[sa_n..n]$ is the list of non-empty suffixes of $s$ sorted in lexicographical order. The rank table for suffixex of $s$ is a permutation $rank$ of integers from $1$ to $n$ such that $rank_{sa_i} = i$.

Kotori has a string $s=s_1s_2\dots s_n$. She would like to ask $m$ queries. And in the $i$-th query, a substring $x=s[l_i..r_i]$ of $s$ is given, Kotori would like to know the rank of suffix $s[k_i..r_i]$ of $x$.

Note $s[l..r]$ means the substring of $s$ which starts from the $l$-th position and ends at the $r$-th position, both inclusive.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n, m \le 5 \times 10^4$) -- the length of the string and the number of queries.

The second line contains a string $s$ of length $n$ consisting only of lowercase English letters.

Each of the next $m$ lines contains three integers $l_i$, $r_i$ and $k_i$ ($1 \le l_i \le r_i \le n, l_i \le k_i \le r_i$) denoting a query.

It is guaranteed that neither the sum of $n$ or the sum of $m$ of all test cases will exceed $5 \times 10^4$.
## 输出格式

For each query output one line containing one integer denoting the answer.
## 样例

### 样例输入 #1
```
2
10 4
baaabbabba
2 8 3
1 1 1
2 3 2
2 5 4
20 3
cccbccbadaacbbbcccab
14 17 16
3 20 17
17 20 18

```
### 样例输出 #1
```
2
1
2
3
4
15
3

```
## 题目翻译

有一个长度为 $n$ 的字符串 $s=[s_1,s_2,..,s_n]$，有 $m$ 个询问，每个询问给定 $l,r,k$，现将 $s$ 的子串 $[s_l,..,s_r]$ 的 $r-l+1$ 个后缀字符串按字典序从小到大排序，问 $[s_k,..,s_r]$ 在其中的排名。

有 $T$ 组数据。

数据保证 $1 \leq n,m,\sum n,\sum m \leq 5 \times 10^4$；对于每组询问，保证 $1 \leq l \leq k \leq r \leq n$。


---

---
title: "[ICPC 2021 Macao R] the Matching System"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9657
tag: ['动态规划 DP', '2021', 'Special Judge', 'O2优化', '前缀和', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] the Matching System
## 题目描述

As the leader of the safety department, you are asked to check an ancient matching system in your company. 

The system is fed with two strings, a to-be-matched string and a pattern string, and will determine whether the former can match the latter. The former string is a strict binary string(i.e., contains only $\textbf{0}$ and $\textbf{1}$), and the latter string consists of four types of characters $\textbf{0}$, $\textbf{1}$, $\textbf{*}$, $^$, where $\textbf{*}$ means match zero or more arbitrary binary characters, and $^$ means match exactly one binary character. 

The system has two matching methods: maximum matching and minimum matching.

Consider the starting positions of the two strings. The maximum matching method will make different decisions based on the current character of the pattern string:
- $\textbf{*}$: The system will enumerate $i$ from $L$ to $0$, where $L$ is the remaining length of the to-be-matched string. Before each enumeration starts, the system consumes 1 unit of energy. Then it temporarily assumes that the current $\textbf{*}$ in the pattern string matches the consecutive $i$ characters in the to-be-matched string, and tries to match the remaining positions of two strings recursively. As long as one attempt is successful, the system will give up the remaining enumeration and stop the whole system. Otherwise, it will try the next enumeration until all attempts are tried and finally return to the previous $\textbf{*}$ enumeration.
- $\textbf{0,1}$: The system will stop and return to the previous $\textbf{*}$ enumeration if the to-be-matched string has been exhausted. Otherwise, it consumes $1$ unit of energy to compare the current characters between the pattern string and the to-be-matched string. It will continue analyzing the remaining positions of these two strings if the result is the same, otherwise, return back to the previous $\textbf{*}$ enumeration.
- $^$: The system will stop and return to the previous $\textbf{*}$ enumeration if the to-be-matched string has been exhausted. Otherwise, it consumes $1$ unit of energy and moves on of two strings.

When the pattern string is exhausted, the system will check the to-be-matched string at the same time. It will return ``Yes`` and stop the whole process if the to-be-matched string is also exhausted, otherwise, it will return to the previous $\textbf{*}$ enumeration. After all attempts are tried and no matching method is found, the system will eventually return ``No``.

Minimum matching does a similar thing except for the enumeration order of $\textbf{*}$ (i.e., enumerate $i$ from $0$ to $L$).

These two matching methods seem not very effective, so you want to hack them. Please construct both a pattern string and a to-be-matched string of length $n$ for each matching method, so that the system answers ``Yes`` and the energy consumption is as large as possible.

## 输入格式

There is only one test case in each test file.

The first and only line contains an integer $n$ ($1 \le n \le 10^3$) indicating the length of strings need to be constructed.
## 输出格式

Please output the pattern string, the to-be-matched string, and the energy cost for the maximum matching method in the first $3$ lines. Then output the pattern string, the to-be-matched string, and the energy cost for the minimum matching method in the next $3$ lines.

If there are multiple constructing ways, you can output any of them.

The energy cost may be very large, so you need to output the value modulo $(10^9+7)$. Note that this is only for your convenience and you need to maximize the energy cost before the modulus.
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
*0*
011
8
**1
101
7
```
## 提示

**【题目描述】**

作为安全部门的负责人，你被要求检查公司的一个古老匹配系统。

该系统输入两个字符串，一个待匹配字符串和一个模式字符串，并确定前者是否能匹配后者。前者字符串是严格的二进制字符串（即仅包含 $\textbf{0}$ 和 $\textbf{1}$），而后者字符串由四种类型的字符组成 $\textbf{0}$、$\textbf{1}$、$\textbf{*}$ 和 $^$，其中 $\textbf{*}$ 表示匹配零个或多个任意二进制字符，$^$ 表示匹配恰好一个二进制字符。

该系统有两种匹配方法：最大匹配和最小匹配。

考虑两个字符串的起始位置。最大匹配方法将根据模式字符串的当前字符做出不同的决定：
- $\textbf{*}$: 系统将从 $L$ 到 $0$ 枚举 $i$，其中 $L$ 是待匹配字符串的剩余长度。在每次枚举开始之前，系统消耗 1 单位的能量。然后，它临时假设模式字符串中的当前 $\textbf{*}$ 匹配待匹配字符串中的连续 $i$ 个字符，并尝试递归地匹配两个字符串的剩余位置。只要有一次尝试成功，系统将放弃剩余的枚举并停止整个系统。否则，它将尝试下一次枚举，直到所有尝试都尝试完毕，最后返回到先前的 $\textbf{*}$ 枚举。
- $\textbf{0,1}$: 如果待匹配字符串已经耗尽，则系统将停止并返回到先前的 $\textbf{*}$ 枚举。否则，它将消耗 $1$ 单位的能量来比较模式字符串和待匹配字符串之间的当前字符。如果结果相同，它将继续分析这两个字符串的剩余位置，否则，返回到先前的 $\textbf{*}$ 枚举。
- $^$: 如果待匹配字符串已经耗尽，则系统将停止并返回到先前的 $\textbf{*}$ 枚举。否则，它将消耗 $1$ 单位的能量并继续分析两个字符串。

当模式字符串耗尽时，系统将同时检查待匹配字符串。如果待匹配字符串也已经耗尽，则系统将返回“是”并停止整个过程，否则，它将返回到先前的 $\textbf{*}$ 枚举。在尝试了所有尝试并找不到匹配方法后，系统最终将返回“否”。

最小匹配执行类似的操作，除了 $\textbf{*}$ 的枚举顺序（即从 $0$ 到 $L$ 枚举 $i$）。

这两种匹配方法似乎不太有效，所以你想黑掉它们。请为每种匹配方法构造一个长度为 $n$ 的模式字符串和待匹配字符串，使得系统返回“是”，能量消耗尽可能大。

**【输入格式】**

每个测试文件中只有一个测试用例。

第一行仅包含一个整数 $n$（$1 \le n \le 10^3$），表示需要构造的字符串的长度。

请输出最大匹配方法的模式字符串、待匹配字符串和能量消耗的前 $3$ 行。然后输出最小匹配方法的模式字符串、待匹配字符串和能量消耗的后 $3$ 行。

**【输出格式】**

如果有多种构造方式，你可以输出任何一种。

能量消耗可能非常大，所以你需要输出取模 $(10^9+7)$ 后的值。请注意，这仅供您方便，您需要在取模之前最大化能量消耗。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[ICPC 2021 Macao R] Colorful Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9665
tag: ['线段树', '2021', 'O2优化', '树论', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Colorful Tree
## 题目描述

Your task is to maintain a colorful tree and process queries.

At the beginning, there is only one vertex numbered $1$ with color $C$ on the tree. Then there are $q$ operations of two types coming in order:
- $0$ $x$ $c$ $d$: Add a new vertex indexed $(n+1)$ with color $c$ to the tree, where $n$ is the current number of existing vertices. An edge connecting vertex $x$ and $(n+1)$ with length $d$ will also be added to the tree.
- $1$ $x$ $c$: Change the color of vertex $x$ to $c$.

After each operation, you should find a pair of vertices $u$ and $v$ ($1 \le u, v \le n$) with $\textbf{different}$ colors in the current tree so that the distance between $u$ and $v$ is as large as possible.

The distance between two vertices $u$ and $v$ is the length of the shortest path from $u$ to $v$ on the tree.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line of the input contains two integers $q$ and $C$ ($1 \le q \le 5 \times 10^5$, $1 \le C \le q$) indicating the number of operations and the initial color of vertex $1$.

For the following $q$ lines, each line describes an operation taking place in order with $3$ or $4$ integers.
- If the $i$-th line contains $4$ integers $0$, $x_i$, $c_i$ and $d_i$ ($1 \le x_i \le n$, $1 \le c_i \le q$, $1 \le d \le 10^9$), the $i$-th operation will add a new vertex $(n + 1)$ with color $c_i$ to the tree and connect it to vertex $x_i$ with an edge of length $d_i$.
- If the $i$-th line contains $3$ integers $1$, $x_i$ and $c_i$ ($1 \le x_i \le n$, $1 \le c_i \le q$), the $i$-th operation will change the color of vertex $x_i$ to $c_i$.

It's guaranteed that the sum of $q$ of all test cases will not exceed $5 \times 10^5$.
## 输出格式

For each operation output the maximum distance between two vertices with different colors. If no valid pair exists output $0$ instead.
## 样例

### 样例输入 #1
```
2
1 1
0 1 1 1
5 1
0 1 1 1
0 1 2 1
0 3 3 1
1 4 1
1 3 1
```
### 样例输出 #1
```
0
0
2
3
2
0
```
## 题目翻译

**【题目描述】**

你的任务是维护一棵有色树并处理查询。

一开始，树上只有一个编号为 $1$ 的顶点，颜色为 $C$。然后按顺序进行 $q$ 个操作，有两种类型：
- $0$ $x$ $c$ $d$：向树中添加一个颜色为 $c$ 的新顶点，其编号为 $(n+1)$，其中 $n$ 是当前存在的顶点数。同时，添加一条连接顶点 $x$ 和 $(n+1)$ 的长度为 $d$ 的边。
- $1$ $x$ $c$：将顶点 $x$ 的颜色更改为 $c$。

在每次操作之后，你应该找到当前树中颜色 $\textbf{不同}$ 的两个顶点 $u$ 和 $v$（$1 \le u, v \le n$），使得它们之间的距离尽可能大。

两个顶点 $u$ 和 $v$ 之间的距离是树上从 $u$ 到 $v$ 的最短路径的长度。

**【输入格式】**

输入的第一行包含两个整数 $q$ 和 $C$（$1 \le q \le 5 \times 10^5$，$1 \le C \le q$），表示操作的数量和顶点 $1$ 的初始颜色。

接下来的 $q$ 行中，每行描述一个按顺序进行的操作，包含 $3$ 或 $4$ 个整数。
- 如果第 $i$ 行包含 $4$ 个整数 $0$、$x_i$、$c_i$ 和 $d_i$（$1 \le x_i \le n$，$1 \le c_i \le q$，$1 \le d \le 10^9$），则第 $i$ 个操作将向树中添加一个颜色为 $c_i$ 的新顶点 $(n + 1)$，并将其与顶点 $x_i$ 连接，边的长度为 $d_i$。
- 如果第 $i$ 行包含 $3$ 个整数 $1$、$x_i$ 和 $c_i$（$1 \le x_i \le n$，$1 \le c_i \le q$），则第 $i$ 个操作将顶点 $x_i$ 的颜色更改为 $c_i$。

保证所有测试用例中 $q$ 的总和不超过 $5 \times 10^5$。

**【输出格式】**

对于每个操作，输出两个不同颜色顶点之间的最大距离。如果不存在有效的顶点对，则输出 $0$。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[ICPC 2022 Jinan R] Grid Points"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9672
tag: ['2022', 'O2优化', 'ICPC', '类欧几里得算法', '济南']
---
# [ICPC 2022 Jinan R] Grid Points
## 题目描述

You are given a simple polygon in the first quadrant of the Cartesian plane. This means that the coordinate $(x, y)$ of any point in the polygon satisfies $x> 0$ and $y> 0$. 

Consider all grid points in the polygon. Order them in increasing order of \textbf{slopes}. Output the $k$-th grid point in this order. 

A grid point is a point $(x, y)$ such that $x$ and $y$ are integers. A point on the boundary of a polygon is considered to be in the polygon. The slope of point $(x, y)$ is $y/x$. If two points have the same slope, they are ordered lexicographically first by $x$, then by $y$. In other words, a point $(x_1, y_1)$ is lexicographically less than $(x_2, y_2)$ if $(x_1<x_2)\vee (x_1=x_2 \wedge y_1<y_2)$. 
## 输入格式

The first line contains one integer $T~(1\le T \le 500)$, the number of test cases.

For each test case, the first line contains two integers $n, k~(n\ge 3, 1\le k)$. Each of the next $n$ lines describes a vertex of the polygon. Each vertex is denoted by two integers $x, y~(1\le x, y\le 10^9)$, representing its coordinate $(x, y)$. The vertices are given in counterclockwise order.

It is guaranteed that the polygon is simple, i.e.~ the vertices are distinct, two edges may overlap only when they are consecutive on the boundary, and the overlap contains exactly $1$ point. It is guaranteed that $k$ is no more than the number of grid points in the polygon.

It is guaranteed that the sum of $n$ over all test cases is no more than $2000$.
## 输出格式

For each test case, output two integers $x, y$ in one line representing the coordinate $(x, y)$ of the $k$-th grid point.
## 样例

### 样例输入 #1
```
4
3 3
1 1
3 1
3 3
4 500000000000000000
1 1
1000000000 1
1000000000 1000000000
1 1000000000
9 22
9 6
6 7
9 7
10 10
6 9
3 9
1 6
1 5
7 3
5 22447972861454999
270353376 593874603
230208698 598303091
237630296 255016434
782669452 568066304
654623868 958264153
```
### 样例输出 #1
```
3 2
500000000 500000000
7 8
730715389 644702744
```
## 题目翻译

## 题目描述



在笛卡尔平面的第一个象限中，您会得到一个简单的多边形。这意味着多边形中任何点的坐标$（x，y）$满足$x>0$和$y>0$。



考虑多边形中的所有网格点。按\textbf｛斜率｝的递增顺序排列。按此顺序输出第$k$个网格点。



网格点是一个点$（x，y）$，使得$x$和$y$是整数。多边形边界上的一个点被认为在多边形中。点$（x，y）$的斜率为$y/x$。如果两个点具有相同的斜率，则它们首先按字典顺序排列$x$，然后按$y$。换句话说，如果$（x_1<x_2）\vee（x_1=x_2\wedge y_1<y_2）$，则点$（x_1，y_1）$在字典上小于$（x_2，y_2）。



## 输入格式



第一行包含一个整数$T~（1\le T\le 500）$，即测试用例的数量。



对于每个测试用例，第一行包含两个整数$n，k~（n\ge 3，1\le k）$。接下来的每一条$n$线都描述了多边形的一个顶点。每个顶点由两个整数$x，y~（1\le x，y\le 10^9）$表示，表示其坐标$（x，y）$。顶点按逆时针顺序排列。



保证多边形是简单的，即顶点是不同的，两条边只有在边界上连续时才能重叠，并且重叠恰好包含$1$点。可以保证$k$不超过多边形中的网格点数。



保证所有测试用例的总金额不超过2000美元。



## 输出格式



对于每个测试用例，在一行中输出两个整数$x，y$，表示第$k$个网格点的坐标$（x，y）$。



## 输入输出样例



### 输入 #1



```
4
3 3
1 1
3 1
3 3
4 5000000000000000
1 1
1000000000 1
1000000000 1000000000
100000000
9 22
9 6
6 7
9 7
10 10
6 9
3 9
1 6
1 5
7 3
5 22447972861454999
270353376 593874603
230208698 598303091
237630296 255016434
782669452 568066304
654623868 958264153
```



### 输出 #1



```
3 2
500000000 500000000
7 8
730715389 644702744
```


---

---
title: "[ICPC 2022 Jinan R] Shortest Path"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9675
tag: ['2022', 'O2优化', '半平面交', 'ICPC', '李超线段树', '济南']
---
# [ICPC 2022 Jinan R] Shortest Path
## 题目描述

You are given an undirected weighted graph $G$ with vertices $1, 2, \ldots, n$. Please output the sum of the answers to the following $x$ questions:
- The $i$-th question $(1\le i\le x$): What is the minimum length of path that starts at vertex $1$, ends at vertex $n$, and contains exactly $i$ edges?

For each question, if such a path does not exist, the answer is considered to be $0$. A path may use one edge multiple times. Output the answer modulo $998244353$. 

## 输入格式

The first line contains one integer $T~(1 \le T\le 2000)$, the number of test cases.

For each test case, the first line contains three integers $n, m, x~(1\le n\le 2000, 0\le m\le 5000, 1\le x\le 10^9)$. Each of the next $m$ lines describes an edge of the graph. Edge $i$ is denoted by three integers $a_i, b_i, w_i$ $(1\le a_i, b_i\le n, 1\le w_i\le 10^9)$, the labels of vertices it connects and its weight. Note that self-loops and parallel edges may exist.

It is guaranteed that the sum of $n$ over all test cases is no more than $2000$ and the sum of $m$ over all test cases is no more than $5000$.
## 输出格式

For each test case, output one integer modulo $998244353$ denoting the answer.
## 样例

### 样例输入 #1
```
4
3 2 10
1 2 5
2 3 4
3 0 1000000000
3 3 100
1 2 3
1 3 4
2 3 5
4 6 1000000000
1 2 244
1 2 325
1 4 927
3 3 248
2 4 834
3 4 285
```
### 样例输出 #1
```
125
0
15300
840659991
```
## 题目翻译

### 题目描述

给定一张 $n$ 个点 $m$ 条边的无向图 $G$，边有边权。你要回答 $x$ 个问题，其中第 $i$ $(1\leqslant i\leqslant x)$ 个问题形如：

- 从结点 $1$ 出发，经过 **恰好** $i$ 条边，到达结点 $n$ 的最短路径长度为多少？

对于每个询问，若不存在这样的路径，答案应当为 $0$。一条路径可能 **多次** 经过一条边。

求出这 $x$ 个问题所对应的答案之和。输出答案对 $998244353$ 取模后的结果。

### 输入格式

第一行包含一个整数 $T$ $(1\leqslant T\leqslant 2000)$，表示测试数据组数。

对于每组测试数据：

第一行三个整数 $n,m,x$ $(1\leqslant n\leqslant 2000,0\leqslant m\leqslant 5000,1\leqslant x\leqslant 10^9)$。

接下来 $m$ 行，每行三个整数 $a_i,b_i,w_i$ $(1\leqslant a_i,b_i\leqslant n,1\leqslant w_i\leqslant 10^9)$，分别表示第 $i$ 条边连接的两个结点的编号和其边权。注意 **可能存在自环和重边**。

保证所有测试数据中 $n$ 的总和不超过 $2000$，且 $m$ 的总和不超过 $5000$。

### 输出格式

对于每组测试数据，输出这组测试数据对应的答案 $\bmod$ $998244353$ 后的结果。


---

---
title: "[ICPC 2022 Jinan R] Tree Distance"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9678
tag: ['点分治', '2022', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Tree Distance
## 题目描述

You are given an unrooted weighted tree $T$ with vertices $1, 2, \ldots, n$. Please answer some queries.

We define $\texttt{dist}(i,j)$ as the distance between vertex $i$ and vertex $j$ in $T$.

For each query, you are given two integers $l, r$. Please answer the value of 

$$\min_{l\le i< j\le r}(\texttt{dist}(i,j)).$$
## 输入格式

The first line contains one integer $n~(1\leq n\le 2 \times 10^5)$, the number of vertices in the tree. 

Each of the next $n-1$ lines describes an edge of the tree. Edge $i$ is denoted by three integers $a_i, b_i, w_i$ $(1\le a_i, b_i\le n, 1\le w_i\le 10^9)$, the labels of vertices it connects and its weight. 

Then one line contains one integer $q~(1\leq q\le 10^6)$, the number of queries.

Each of the following $q$ lines contains two integers $l, r~(1\le l \le r\le n)$ describing a query.

It is guaranteed that the given edges form a tree.
## 输出格式


For each query, output the answer in one line. If there is no $i,j$ such that $l\le i<j\le r$, the answer is $-1$.
## 样例

### 样例输入 #1
```
5
1 2 5
1 3 3
1 4 4
3 5 2
5
1 1
1 4
2 4
3 4
2 5

```
### 样例输出 #1
```
-1
3
7
7
2

```
## 题目翻译

给你一棵 $n$ 个点的树。记 $\operatorname{dist}(i,j)$ 为树上 $i,j$ 之间唯一简单路径的长度。

你要回答 $q$ 次询问：给定 $l,r$，求 $\min\limits_{l\leq i<j\leq r}(\operatorname{dist}(i,j))$。


---

---
title: "[EC Final 2022] Minimum Suffix"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9719
tag: ['字符串', '2022', 'O2优化', 'ICPC', 'Lyndon 分解']
---
# [EC Final 2022] Minimum Suffix
## 题目描述

For a string $s$ of length $n$, we define $p_j = x$ if $s[x\ldots j]$ is the minimum suffix of $s[1\ldots j]$, for all $j=1,\ldots, n$. (A suffix is the minimum suffix of a string if it is lexicographically smaller than any other suffix of that string.)

You are to recover $s$ from $p_1,\ldots, p_n$. If there are multiple answers, find the lexicographically smallest one.
## 输入格式

The first line contains a single integer $T$ ($1\le T\le 10^5$) representing the number of test cases.

For each test case, the first line contains a single integer $n$ ($1\le n\le 3\times 10^6$) representing the length of $s$. The next line contains $n$ integers $p_1,\ldots, p_n$ ($1\le p_i\le i$ for all $1\le i\le n$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $3\times 10^6$.
## 输出格式

For each test case, output one line. If there is no solution, output $-1$. Otherwise, output the lexicographically smallest $s$. Characters of $s$ are represented by positive integers. Smaller integers represent smaller characters in the lexicographical order.
## 样例

### 样例输入 #1
```
6
3
1 1 1
3
1 1 2
3
1 1 3
3
1 2 1
3
1 2 2
3
1 2 3
```
### 样例输出 #1
```
1 2 2
-1
1 2 1
1 1 2
2 1 2
1 1 1
```
## 提示

As the input/output can be huge, it is recommended to use fast input/output methods.
## 题目翻译

**【题目描述】**

对于长度为 $n$ 的字符串 $s$，如果 $s[x\ldots j]$ 是 $s[1\ldots j]$ 的最小后缀，则我们定义 $p_j = x$，其中 $j=1,\ldots, n$。（后缀是字符串的最小后缀，如果它在字典序上小于该字符串的任何其他后缀。）

你需要从 $p_1,\ldots, p_n$ 中恢复出 $s$。如果存在多个答案，则找出字典序最小的那个。

**【输入格式】**

第一行包含一个整数 $T$（$1\le T\le 10^5$），表示测试用例的数量。

对于每个测试用例，第一行包含一个整数 $n$（$1\le n\le 3\times 10^6$），表示 $s$ 的长度。接下来的一行包含 $n$ 个整数 $p_1,\ldots, p_n$（$1\le p_i\le i$，$1\le i\le n$）。

保证所有测试用例中 $n$ 的总和不超过 $3\times 10^6$。

**【输出格式】**

对于每个测试用例，输出一行。如果没有解决方案，则输出 $-1$。否则，输出字典序最小的 $s$。$s$ 中的字符由正整数表示。较小的整数表示字典序较小的字符。

**【提示说明】**

本题输入输出规模较大，建议使用快速的输入输出方式。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[EC Final 2022] Rectangle"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9722
tag: ['线段树', '2022', 'O2优化', 'ICPC', '吉司机线段树 segment tree beats']
---
# [EC Final 2022] Rectangle
## 题目描述

Prof. Pang has $n$ rectangles, the coordinate of the lower left corner of the $i$-th rectangle is $(x_{i,1}, y_{i,1})$, and the coordinate of the upper right corner is $(x_{i,2}, y_{i,2})$. Rectangles may overlap.

You need to choose three straight lines such that:

- Each line should be parallel to the $x$-axis or the $y$-axis, which means its formula is $x = a$ or $y = a$.
- In the formula $x = a$ or $y = a$, $a$ should be an integer in $[1, 10^9]$.
- These three lines should be distinct.
- Each rectangle is $\textbf{touched}$ by at least one line. A line touches a rectangle if it intersects with the boundary and/or the interior of the rectangle.

You need to compute the number of ways to choose three lines. Since the answer can be very large, output it modulo $998244353$. Two ways are considered the same if only the order of three lines differs in these two ways. 
## 输入格式

The first line contains a single integer $T~(1 \le T \le 10^5)$, denoting the number of test cases.

For each test case, the first line contains an integer $n~(1 \le n \le 10^5)$. The $i$-th line of the next $n$ lines contains four integers $x_{i,1}, y_{i,1},x_{i,2}, y_{i,2}~(1\le x_{i,1}<x_{i,2}\le 10^9,1\le y_{i,1}<y_{i,2}\le 10^9)$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\times 10^5$.
## 输出格式

For each test case, output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
3
1
1 1 1000000000 1000000000
3
1 1 2 2
3 3 4 4
5 5 6 6
5
581574116 47617804 999010750 826131769
223840663 366320907 613364068 926991396
267630832 51913575 488301124 223957497
217461197 492085159 999485867 913732845
28144453 603781668 912516656 993160442
```
### 样例输出 #1
```
230616300
64
977066618
```
## 题目翻译

**【题目描述】**

庞教授有 $n$ 个矩形，第 $i$ 个矩形的左下角坐标是 $(x_{i,1}, y_{i,1})$，右上角坐标是 $(x_{i,2}, y_{i,2})$。矩形可以重叠。

你需要选择三条直线，使得：

- 每条直线应该与 $x$ 轴或 $y$ 轴平行，即其方程为 $x = a$ 或 $y = a$。
- 在方程 $x = a$ 或 $y = a$ 中，$a$ 应该是 $[1, 10^9]$ 区间内的整数。
- 这三条直线应该是不同的。
- 每个矩形至少被一条直线 $\textbf{触摸}$。如果一条直线与矩形的边界和/或内部相交，则称该直线触摸该矩形。

你需要计算选择三条直线的方法数。由于答案可能非常大，输出对 $998244353$ 取模的结果。如果两种方法只有三条直线的顺序不同，则认为它们是相同的。

**【输入格式】**

第一行包含一个整数 $T~(1 \le T \le 10^5)$，表示测试用例的数量。

对于每个测试用例，第一行包含一个整数 $n~(1 \le n \le 10^5)$。接下来的 $n$ 行中，第 $i$ 行包含四个整数 $x_{i,1}, y_{i,1},x_{i,2}, y_{i,2}~(1\le x_{i,1}<x_{i,2}\le 10^9,1\le y_{i,1}<y_{i,2}\le 10^9)$。

保证所有测试用例中 $n$ 的总和不超过 $2\times 10^5$。

**【输出格式】**

对于每个测试用例，输出一行整数，表示答案。

**【样例解释】**

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[EC Final 2022] Magic"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9726
tag: ['2022', '网络流', 'O2优化', 'ICPC']
---
# [EC Final 2022] Magic
## 题目描述

**Warning: Unusual memory limit!**

You are given a sequence $a_0,\ldots,a_{2n}$. Initially, all numbers are zero. 

There are $n$ operations. The $i$-th operation is represented by two integers $l_i, r_i$ ($1\le l_i < r_i\le 2n, 1\le i\le n$), which assigns $i$ to $a_{l_i},\ldots,a_{r_i-1}$.  It is guaranteed that all the $2n$ integers, $l_1,l_2,\ldots, l_n, r_1, r_2, \ldots, r_n$, are distinct.

You need to perform each operation exactly once, in arbitrary order.

You want to maximize the number of $i$ $(0\leq i< 2n)$ such that $a_i\neq a_{i+1}$ after all $n$ operations. Output the maximum number.
## 输入格式

The first line contains an integer $n$ ($1\le n\le 5\times 10^3$).

The $i$-th line of the next $n$ lines contains a pair of integers $l_i, r_i$ ($1\le l_i < r_i\le 2n$). It is guaranteed that all the $2n$ integers, $l_1,l_2,\ldots, l_n, r_1, r_2, \ldots, r_n$, are distinct.
## 输出格式

Output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
5
2 3
6 7
1 9
5 10
4 8

```
### 样例输出 #1
```
9

```
## 题目翻译

- 你有一个序列 $a_0,a_1,a_2\dots a_{2n}$，初始全为 $0$。
- 给定 $n$ 个区间赋值操作，第 $i$ 个操作 $(l_i,r_i)(1\le l_i,r_i\le 2n)$ 表示把区间 $[l_i,r_i)$ 全部赋值为 $i$，**保证所有 $l_i,r_i$ 互不相同**。
- 你可以指定一个执行操作的顺序，最大化 $\sum_{i=0}^{2n-1}[a_i\ne a_{i+1}]$，输出这个最大值。
- $1\le n\le 5\times 10^3$，**注意空间限制**。


---

---
title: "[NERC 2018] Harder Satisfiability"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9798
tag: ['2018', 'ICPC']
---
# [NERC 2018] Harder Satisfiability
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) H 题。
## 题目描述

我们定义一个“完全量化的布尔类型的 2-CNF 公式”（下简称 2-CNF）是以 $Q_1 x_1 \ldots Q_n x_n F(x_1,\ldots x_n)$ 构成的，$Q_i$ 只有两种，一种是“通用量词” $\forall$，另一种是“存在量词” $\exists$。然后 $F$ 是一个 $m$ 子句的 $s \lor t$（$\mathtt{OR}$ 运算） 的连词（$\mathtt{AND}$ 运算），其中 $s$ 和 $t$ 不一定不同且不一定是否定（为 $\texttt{false}$）。由于 2-CNF 公式是给定的，所以并没有自由变量（即答案固定为 $\texttt{true}$ 或 $\texttt{false}$）。

至于计算 2-CNF 公式的值，我们可以使用一个简单的递归算法来求：

- 如果没有量词（即 $\forall$ 或 $\exists$ ），则返回剩余表达式的返回值。

- 否则，我们使用递归计算公式：$F_z = Q_2x_2 \ldots Q_nx_n F(z,x_2,\ldots,x_n)$，此处 $z = 0,1$。

- 如果当前符号为 $\exists$，则返回 $F_0 \lor F_1$（$\mathtt{OR}$ 运算）。否则符号为 $\forall$ 返回 $F_0 \land F_1$。

## 输入格式

第一行是一个整数 $t (1 \leq t \leq 10^5)$，表示数据组数。

接下来 $t$ 组数据，每组数据第一行两个整数 $n(1 \leq n \leq 10^5)$ 和 $m (1 \leq m \leq 10^5)$，$n$ 表示量词的长度，$m$ 表示在 $F$ 中的元素个数。

然后一行，一串长度为 $n$ 的字符串 $s$，如果 $s_i = $ `A`，则 $Q_i = \forall$，否则若 $s_i = $ `E`，则 $Q_i = \exists$。

接下来 $m$ 行，一行两个整数 $u_i,v_i(-n \leq u_i,v_i \leq n)$，如果 $u_i \geq 1$ 则第 $i$ 个变量是 $x_{u_i}$，如果 $u_i \leq -1$ 则第 $i$ 个变量是 $-(x_{-u_i})$，$v_i$ 同理。
## 输出格式

对于每组数据，如果 2-CNF 公式为真输出 `TRUE`，否则输出 `FALSE`。
## 样例

### 样例输入 #1
```
3
2 2
AE
1 -2
-1 2
2 2
EA
1 -2
-1 2
3 2
AEA
1 -2
-1 -3

```
### 样例输出 #1
```
TRUE
FALSE
FALSE

```
## 提示

数据保证 $1 \leq t \leq 10^5$，$1 \leq n,m \leq 10^5$，$-n \leq u_i,v_i \leq n$。

第一个 2-CNF 公式可以化简为 $\forall x_1 \exists x_2(x_1 \lor \overline{x_2}) \land (\overline{x_1} \lor x_2) = \forall x_1 \exists x_2 x_1 \oplus x_2$，对于任意的 $x_1$ 都存在 $x_2 = \overline{x_1}$ 使得答案为真。

第二个 2-CNF 改变了公式的顺序，对于任意的 $x_1$，都可以选择 $x_2 = x_1$，使得表达式为 `FALSE`。

第三个表达式是 $\forall x_1 \exists x_2 \forall x_3 (x_1 \lor \overline{x_2}) \land (\overline{x_1} \lor \overline{x_3})$，如果令 $x_1 = 1$，$x_3 = 1$，则没有 $x_2$ 的值可以使得句子赋值为真，所以公式为假。


---

---
title: "[ICPC 2020 Shanghai R] Wowoear"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9819
tag: ['计算几何', '2020', '上海', 'Special Judge', 'O2优化', '线段相交', 'ICPC']
---
# [ICPC 2020 Shanghai R] Wowoear
## 题目描述

Wowo is a solo adventurer who completed many dangerous journeys on his own foot in forests, deserts and even glaciers. The Shanghai ICPC (Shanghai Invitational Contest on Programmable Cheating) committee invited Wowo as a tester of their new running trial.

The trial can be described as a 2D simple polyline $(p_1,\ldots, p_n)$. In other words, the trial consists of $n-1$ line segments $(p_1, p_2),\ldots, (p_{n-1}, p_n)$. The line segments do not intersect with each other except that two consecutive line segments $(p_i, p_{i+1})$ and $(p_{i+1}, p_{i+2})$ intersect at the point $p_{i+1}$. Any two consecutive segments have different directions. The committee wants Wowo to run from $p_1$ to $p_n$ along the line segments $(p_1,p_2),\ldots, (p_{n-1}, p_n)$ in order.

However, Wowo has a smart device that can hack the committee's system for an interval of time. Wowo is able to choose $2$ points $a, b$ on the trial and run directly from $a$ to $b$ along the line segment $(a, b)$. Each of these $a$ and $b$ can be some $p_i$ ($1\le i\le n$) and can be some point on some line segment $(p_i, p_{i+1})$ ($1\le i<n$) as well. Before reaching $a$ and after reaching $b$, Wowo has to run along the original trial. Wowo does not want to be caught cheating, so he decided that the line segment $(a, b)$ should not intersect or touch any line segment of the trial at any point other than $a$ and $b$. Help Wowo to choose $a$ and $b$ wisely and output the shortest distance Wowo need to run from $p_1$ to $p_n$ using his smart cheating device.
## 输入格式

The first line includes a single integer $n$ indicating the number of points on the running trial ($2\le n\le 200$).

The $i+1$-th line ($1\le i\le n$) contains two integers $x$ and $y$ separated by a single space indicating the coordinates of $p_i$ ($-1000\le x, y\le 1000$).

It is guaranteed that the line segments do not intersect with each other except that two consecutive line segments $(p_i, p_{i+1})$ and $(p_{i+1}, p_{i+2})$ intersect at the point $p_{i+1}$. In other words, $(p_i, p_{i+1})\cap (p_{j}, p_{j+1})=\left\{\begin{array}{cc}\emptyset & i\neq j-1\\ \{p_{j}\} & i = j-1\end{array}\right.$ holds for any integers $i, j$ satisfying $1\le i< j<n$. Here $(s, t)$ represents all points on the line segment from $s$ to $t$ including $s$ and $t$.

It is guaranteed that each line segment has nonzero length. In other words, $p_i\neq p_{i+1}$ for any integer $i\in [1, n)$.

It is guaranteed that adjacent line segments are not collinear. In other words, for any integer $i\in [1,n-2]$ and any real number $\lambda$, $p_i - p_{i+1}$ is $\textbf{not}$ equal to $\lambda(p_{i+1}-p_{i+2})$.
## 输出格式

Output the shortest distance Wowo needs to run. Your answer will be considered correct if its absolute or relative error does not exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
5
0 0
1 10
2 0
3 10
4 0
```
### 样例输出 #1
```
22.099751242242
```
## 题目翻译

### 题目描述
Wowo 是一位单人冒险家，他曾独自一人在森林、沙漠甚至冰川中完成过许多危险的旅程。ICPC（上海市可编程作弊邀请赛）组委会邀请 Wowo 作为新的跑步测试员。

该试验可描述为二维简单折线 $(p_1,\ldots, p_n)$。换句话说，试验由 $n-1$ 条线段 $(p_1, p_2),\ldots, (p_{n-1}, p_n)$ 组成。除了两个连续的线段 $(p_i, p_{i+1})$ 和 $(p_{i+1}, p_{i+2})$ 相交于点 $p_{i+1}$ 外，其他线段互不相交。任何两条连续的线段都有不同的方向。委员会希望 Wowo 从 $p_1$ 到 $p_n$ 依次沿着线段 $(p_1,p_2),\ldots, (p_{n-1}, p_n)$ 运行。

然而，Wowo 拥有一个智能设备，可以在一段时间内侵入委员会的系统。Wowo 能够在试验中选择 $2$ 点 $a, b$ ，并沿着线段 $(a, b)$ 直接从 $a$ 跑到 $b$ 。其中每个 $a$ 和 $b$ 都可以是某个 $p_i$ （$1\le i\le n$）。($1\le i\le n$) ，也可以是线段 $(p_i, p_{i+1})$ 上的某一点。($1\le i \le n$)上的某一点。在到达 $a$ 之前和 $b$ 之后，Wowo 必须沿着原来的试验路线运行。沃沃不想被发现作弊，所以他决定线段 $(a, b)$ 不能与试验中的任何线段相交，也不能接触到 $a$ 和 $b$ 以外的任何点。请帮助 Wowo 明智地选择 $a$ 和 $b$ ，并利用他的智能作弊装置输出 Wowo 需要从 $p_1$ 跑到 $p_n$ 的最短距离
### 输入格式

第一行包含一个整数 $n$ ，表示运行试验中的点数（ $2\le n\le 200$ ）。

第 $i+1$（$1\le i\le n$）行包含两个整数 $x$ 和 $y$，中间用一个空格隔开，表示 $p_i$（$-1000\le x, y\le 1000$）的坐标。

除了两条连续的线段 $(p_i, p_{i+1})$ 和 $(p_{i+1}, p_{i+2})$ 相交于点 $p_{i+1}$ 之外，其他线段保证互不相交。换句话说，对于满足 $1 \le i\lt j \lt n$ 的任何整数 $i, j$，$(p_i, p_{i+1})\cap (p_{j}, p_{j+1})=\left\{\begin{array}{cc}\emptyset & i\neq j-1\\ \{p_{j}\} & i = j-1\end{array}\right.$ 都成立。这里的 $(s, t)$ 代表从 $s$ 到 $t$ 的线段上的所有点，包括 $s$ 和 $t$。
可以保证每条线段的长度都不为零。换句话说，$p_i\neq p_{i+1}$ 满足任意整数 $i\in [1, n)$。

保证相邻线段不相交。换句话说，对于任意整数 $i\in [1,n-2]$ 和任意实数 $\lambda$，$p_i - p_{i+1}$ 不**等于**$\lambda(p_{i+1}-p_{i+2})$。
### 输出格式
输出 Wowo 需要运行的最短距离。如果答案的绝对误差或相对误差不超过 $10^{-6}$，则认为答案正确。  
Translation by [nightwatch_ryan](/user/961351)


---

---
title: "[ICPC 2020 Shanghai R] Octasection"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9828
tag: ['2020', '线段树', '上海', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Octasection
## 题目描述


At the Namomo Camp, a cute volunteer celebrates her birthday. Wowo buys her a huge cake. (The cake is so big that it has a 3D coordinate system inside.) There are $n$ cuboid shaped pieces of chocolates $\textbf{in}$ the cake. The $i$-th ($1\le i\le n$) chocolate consists of all points $(x,y,z)$ such that $min\_x[i]\le x\le max\_x[i], min\_y[i]\le y\le max\_y[i], min\_z[i]\le z\le max\_z[i]$. $min\_x,max\_x, min\_y,max\_y, min\_z, max\_z$ are $6$ arrays of integers. Chocolates may overlap or touch each other.

The volunteer wants to distribute the cake to the campers of the Namomo Camp. To show off his knife skill, Wowo decides to cut the cake into pieces by exactly $3$ cuts such that:

- The first cut is a plane whose equation is $x=a$ for some integer $a$ decided by Wowo.
- The second cut is a plane whose equation is $y=b$ for some integer $b$ decided by Wowo.
- The third cut is a plane whose equation is $z=c$ for some integer $c$ decided by Wowo.
- Each chocolate is $\textbf{touched}$ by at least one cut (i.e. each cuboid has a nonempty intersection with at least one plane).

Decide whether Wowo can cut the cake under the rules. If the answer is yes, output any possible solution.
## 输入格式

The first line contains a single integer $n$ ($1\le n\le 100000$).

The $i$-th line of the next $n$ lines contains $6$ integers $min\_x[i],max\_x[i], min\_y[i],max\_y[i], min\_z[i], max\_z[i]$ ($-10^9\le min\_x[i],max\_x[i], min\_y[i],max\_y[i], min\_z[i], max\_z[i]\le 10^9$, $min\_x[i]<max\_x[i]$, $min\_y[i]<max\_y[i]$, $min\_z[i]< max\_z[i]$).
## 输出格式

If Wowo can cut the cake under the rules, the first line of the output should contain ``YES`` and the second line should contain $3$ integers $a$, $b$ and $c$ ($-10^9\le a, b, c\le 10^9$). If Wowo cannot cut the cake under the rules, output only one line containing ``NO``.
## 样例

### 样例输入 #1
```
3
0 1 0 1 0 1
10 11 10 11 10 11
999999999 1000000000 999999999 1000000000 999999999 1000000000
```
### 样例输出 #1
```
YES
0 10 999999999
```
### 样例输入 #2
```
4
0 1 0 1 0 1
999999999 1000000000 0 1 0 1
0 1 999999999 1000000000 0 1
0 1 0 1 999999999 1000000000
```
### 样例输出 #2
```
YES
0 0 0
```
## 题目翻译

有一个巨大的蛋糕，蛋糕里面有$n$块立方体形状的巧克力，每块巧克力的位置由它的对角线坐标定义。一个人想通过三个平面切割这个蛋糕，每个平面的方程分别是$x=a$，$y=b$和$z=c$，其中$a$、$b$和$c$是整数。目标是选择$a$、$b$和$c$这样每块巧克力至少被一个切割平面触及。

输入由一个整数$n$开始，表示巧克力的数量，后面跟着$n$行，每行六个整数，分别代表每块巧克力在三维坐标系中的最小和最大$x$、$y$、$z$坐标。

输出要求是如果存在这样的三个切割平面，第一行输出``YES``，第二行输出三个整数$a$、$b$和$c$。如果不存在，只输出``NO``。


---

---
title: "[ICPC 2021 Nanjing R] Paimon Polygon"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9845
tag: ['计算几何', '2021', 'Special Judge', 'O2优化', '凸包', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Paimon Polygon
## 题目描述

Paimon just puts $(n+1)$ distinct points on the plane, one of which is a special point $O=(0,0)$, and denote the group of remaining points as $\mathbb{S}$.

We call a point set $\mathbb{U}$ $\textit{strict convex set}$, if and only if $|\mathbb{U}| \ge 3$ and all the points from $\mathbb{U}$ lie exactly on the convex hull built from $\mathbb{U}$, with no three points lying on the same line.

You should divide $\mathbb{S}$ into two sets $\mathbb{A}$ and $\mathbb{B}$ so that:
- $\mathbb{A} \cap \mathbb{B}=\emptyset$.
- $\mathbb{A} \cup \mathbb{B}=\mathbb{S}$.
- $|\mathbb{A}| \ge 2, |\mathbb{B}| \ge 2$.
- The point set $\mathbb{A} \cup \{O\}$ is a $\textit{strict convex set}$, and denote its convex hull as $C_{\mathbb{A} \cup \{O\}}$.
- The point set $\mathbb{B} \cup \{O\}$ is a $\textit{strict convex set}$, and denote its convex hull as $C_{\mathbb{B} \cup \{O\}}$.
- The outlines(edges) of $C_{\mathbb{A} \cup \{O\}}$ and $C_{\mathbb{B} \cup \{O\}}$ only intersect at point $O$. That is, only one point $O$ satisfies that it lies both on the outlines of $C_{\mathbb{A} \cup \{O\}}$ and $C_{\mathbb{B} \cup \{O\}}$.

Please help Paimon to maximize the sum of the perimeters of these two convex hulls. That is, find a valid division $\mathbb{A}$ and $\mathbb{B}$ which maximizes $(L(C_{\mathbb{A} \cup \{O\}}) + L(C_{\mathbb{B} \cup \{O\}}))$, where $L(\text{polygon})$ means the perimeter of that polygon.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains one integer $n$ ($4 \le n \le 5 \times 10^5$) indicating the number of points in $\mathbb{S}$.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($-10^9 \le x_i, y_i \le 10^9$, $(x_i, y_i) \ne (0, 0)$) indicating the location of the $i$-th point in $\mathbb{S}$.

It's guaranteed that the points given in the same test case are pairwise different. However, there may be three points lying on the same line.

It's also guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing a number indicating the maximum total perimeter. If there does not exist a valid division output `0` instead.

Your answer will be accepted if the relative or absolute error is less than $10^{-6}$.
## 样例

### 样例输入 #1
```
3
4
0 3
3 0
2 3
3 2
5
4 0
5 -5
-4 -2
1 -2
-5 -2
4
0 1
1 0
0 2
1 1

```
### 样例输出 #1
```
17.2111025509
36.6326947621
0.0000000000

```
## 提示

A valid division (left) and an invalid division (right) of the first sample test case are shown below.

![](https://cdn.luogu.com.cn/upload/image_hosting/v17tmtdh.png)
## 题目翻译

## 题目描述

派蒙在平面上放置了$n+1$个互异的点，其中有一特殊点$O=(0,0)$，并记其余点为$\mathbb{S}$。

我们称一个点集 $\mathbb{U}$ 为$\textit{strict convex set}$，当且仅当点集中点的个数大于等于3（$|\mathbb{U}| \ge 3$）且$\mathbb{U}$中的所有点位于$\mathbb{U}$构成的凸包上，且任意三点不共线。


你需要将$\mathbb{S}$划分为两个集合 $\mathbb{A}$ 和$\mathbb{B}$，使其满足
- $\mathbb{A} \cap \mathbb{B}=\emptyset$.
- $\mathbb{A} \cup \mathbb{B}=\mathbb{S}$.
- $|\mathbb{A}| \ge 2, |\mathbb{B}| \ge 2$.

- 点集 $\mathbb{A} \cup \{O\}$ 是 $\textit{strict convex set}$，并记它的凸包为$C_{\mathbb{A} \cup \{O\}}$。
- 点集 $\mathbb{B} \cup \{O\}$是 $\textit{strict convex set}$，并记它的凸包为 $C_{\mathbb{B} \cup \{O\}}$。
- $C_{\mathbb{A} \cup \{O\}}$和 $C_{\mathbb{B} \cup \{O\}}$ 的轮廓 仅在 $O$相交。 这也就是说，仅有点$O$既在$C_{\mathbb{A} \cup \{O\}}$的轮廓上，又在$C_{\mathbb{B} \cup \{O\}}$的轮廓上。
  
请协助派蒙计算出这两个凸包周长之和的最大值。
这也就是说，找到一个合法的划分方案$\mathbb{A}$ 和 $\mathbb{B}$，使得 $(L(C_{\mathbb{A} \cup \{O\}}) + L(C_{\mathbb{B} \cup \{O\}}))$最大，其中$L(\text{polygon})$代表多边形的周长。 

## 输入格式

多组测试数据，第一行给出数据组数 $T$。

第一行给出一个整数 $n$ ($4 \le n \le 5 \times 10^5$) ，表示 $\mathbb{S}$ 中点的个数。

接下来$n$行，第$i$行 包含两个整数 $x_i$ 和 $y_i$ ($-10^9 \le x_i, y_i \le 10^9$, $(x_i, y_i) \ne (0, 0)$) 表示 $\mathbb{S}$ 中第 $i$个点的坐标。

保证同一组测试数据中的点互异，但可能存在三点共线。

保证 所有测试数据中$n$之和不超过 $10^6$.

## 输出格式

每组测试数据单起一行输出一个整数，表示两个凸包的周长之和的最大值。如不存在合法的划分方案，输出`0`。
与标准答案的相对或绝对误差小于 $10^{-6}$的答案会被视作正确答案。


---

---
title: "[ICPC 2021 Nanjing R] Ancient Magic Circle in Teyvat"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9850
tag: ['图论', '2021', 'Special Judge', 'O2优化', '容斥原理', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Ancient Magic Circle in Teyvat
## 题目描述

Astrologist Mona Megistus discovers an ancient magic circle in Teyvat recently.

![](https://cdn.luogu.com.cn/upload/image_hosting/gohzab6t.png)

The magic circle looks like a complete graph with $n$ vertices, where $m$ edges are colored red and other edges are colored blue. Note that a complete graph is a simple undirected graph in which every pair of distinct vertices is connected by a unique edge.

Mona realizes that if she chooses four different vertices such that the six edges between these four vertices are of the same color, she will get a *key* from the magic circle. If the color is red, she will get a *red key*, and if the color is blue, she will get a *blue key*.

Base on the information written in the ancient books Mona has read, the magic power of the ancient magic circle is the absolute difference between the number of *red keys* and the number of the number of *blue keys* she can get from the magic circle.

Mona needs your help badly, since calculating the magic power of the magic circle is really a tough job.
## 输入格式

There is only one test case in each test file.

The first line of the input contains two integers $n$ and $m$ ($4 \le n \le 10^5$, $0 \le m \le \min(\frac{n(n-1)}{2}, 2 \times 10^5)$) indicating the number of vertices and the number of edges colored red of the ancient magic circle.

For the following $m$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($u_i < v_i$) indicating a red edge connecting vertices $u_i$ and $v_i$. It is guaranteed that each edge appears at most once.
## 输出格式

Output one line containing one integer indicating the magic power of the ancient magic circle.
## 样例

### 样例输入 #1
```
7 6
1 2
1 3
1 4
2 3
2 4
3 4

```
### 样例输出 #1
```
3

```
## 提示

For the sample case, there is only one *red key* $(1,2,3,4)$ and there are four *blue keys* $(1,5,6,7)$, $(2,5,6,7)$, $(3,5,6,7)$ and $(4,5,6,7)$ in the ancient magic circle, thus the magic power of the magic circle is $|1-4|=3$.
## 题目翻译

给定一个 $n$ 个点的完全图，有 $m$ 条边是红色的，其余边是蓝色的，求出边均为蓝色的大小为 $4$ 的完全子图个数与边均为红色的大小为 $4$ 的完全子图个数的差。  
$4\le n\le 10^5$，$0\le m\le \min(\frac{n(n-1)}{2},2\times 10^5)$。


---

---
title: "[EC Final 2021] Vacation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9877
tag: ['2021', 'O2优化', 'ICPC']
---
# [EC Final 2021] Vacation
## 题目描述

Prof. Pang has an annual leave of $c$ days and he wants to go on vacation.

Now there are $n$ days in a year. Prof. Pang can gain $a_i$ happiness if he rests on the $i$-th day. The values of happiness, $a_i$, may be negative.

Prof. Pang wants you to do $m$ operations:

- $1~x~y$, change the happiness of the $x$-th day to $y$.
- $2~l~r$, Prof. Pang wants to find a period of vacation in $[l, r]$. He wants to rest for several (possibly $0$) days in a row and gain as much happiness as possible. However, he only has $c$ days off, thus he can rest for no more than $c$ consecutive days in $[l,r]$.

That means he wants to find 

$$\max\left(\max_{l \leq l' \leq r' \leq r\atop r'-l'+1\leq c}  ~~ \left(\sum_{i=l'} ^{r'} a_i\right), 0\right).$$

## 输入格式

The first line contains three integers $n, m, c (1\leq n\leq 2\times 10^5, 1\leq m \leq 5\times 10^5, 1\leq c\leq n)$ indicating the number of days in a year, the number of operations, and Prof. Pang's annual leave days.

The next line contains $n$ integers $a_1, a_2, \dots, a_n(-10^9 \leq a_i\leq 10^9)$ indicating the values of happiness of every day.

The next $m$ lines are the $m$ operations in the format described above.

It is guaranteed that $1\leq x\leq n, -10^9\leq y\leq 10^9, 1\leq l\leq r \leq n$.
## 输出格式

For each operation of the second type, print the answer.
## 样例

### 样例输入 #1
```
5 6 3
0 -5 -3 8 -3
2 3 5
1 2 5
2 1 5
1 4 -3
2 3 5
2 1 5
```
### 样例输出 #1
```
8
10
0
5
```
## 题目翻译

连续的 $n$ 天，每天的 $Happiness$ 为  $a_i$ 。包含 $m$ 次操作，和一个 $c$ 
。
- $1.$ 将 $a_x$ 的值改为 $y$ 。
- $2.$ 询问 $[l,r]$ 内，连续 $t$ 天内，最大的 $Happiness$ 值的和，其中 $t∈[0,c]$ 。


---

---
title: "[EC Final 2021] Check Pattern is Bad"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9878
tag: ['2021', 'Special Judge', 'O2优化', '构造', 'ICPC']
---
# [EC Final 2021] Check Pattern is Bad
## 题目描述

Prof. Pang is given an $n\times m$ board. Some cells are colored black, some cells are colored white, and others are uncolored.

Prof. Pang doesn't like $\textbf{check patterns}$, so he wants to color all uncolored cells such that there is no check pattern on the board.

$4$ cells forming a $2\times 2$ square are said to have the check pattern if they are colored in one of the following ways:

```plain
BW
WB
```

```plain
WB
BW
```

Here `W` ("wakuda" in Chewa language) means the cell is colored black and `B` ("biancu" in Corsican language) means the cell is colored white.
## 输入格式

The first line contains a single integer $T$ $(1\leq T \leq 10^4)$ denoting the number of test cases.

The first line of each test case contains two integers $n$ and $m$ ($1\le n, m\le 100$) denoting the dimensions of the board.

Each of the next $n$ lines contains $m$ characters. The $j$-th character of the $i$-th line represents the status of the cell on the $i$-th row and $j$-th column of the board. The character is `W` if the cell is colored black, `B` if the cell is colored white, and `?` if the cell is uncolored. 

It is guaranteed that the sum of $nm$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, output a line containing $\texttt{NO}$ if you cannot color all the uncolored cells such that there is no check pattern on the board.

Otherwise, output a line containing $\texttt{YES}$. In the next $n$ lines, output the colored board in the same format as the input. The output board should satisfy the following conditions.

- It does not have any check pattern.
- It consists of only $\texttt{B}$ and $\texttt{W}$.
- If a cell is already colored in the input, its color cannot be changed in the output.

If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
3
2 2
??
??
3 3
BW?
W?B
?BW
3 3
BW?
W?W
?W?
```
### 样例输出 #1
```
YES
BW
WW
NO
YES
BWB
WWW
BWB
```
## 题目翻译

$n \times m$ 的棋盘，知道一些位置是黑色的，一些位置是白色的，一些位置不知道是什么颜色。

请你构造一种方案让棋盘的每个位置被染成黑色或白色（已知的位置不能换颜色），使得棋盘上不存在子矩阵：

```
BW
WB
```

以及
```
WB
BW
```


多组询问。


---

---
title: "[EC Final 2021] Vision Test"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9882
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2021] Vision Test
## 题目描述

Prof. Pang has an extraordinary vision. He can see the pixels on a 4K monitor. To test Prof. Pang's vision, Prof. Shou will show Prof. Pang several pixels and let Prof. Pang guess a straight line that contains these pixels. Given $k$ pixels with coordinates $(i, y_i)$ ($0\le i<k$), Prof. Pang must find nonnegative integers $a, b$ and $c$ (which represent the line $y=\frac{ax+b}{c}$) such that $y_i=\lfloor \frac{ai+b}{c} \rfloor$ for all $0\le i<k$. 

Prof. Shou will ask Prof. Pang multiple questions. They are given as follows: Prof. Shou has a fixed array $x_1,\ldots, x_n$. For each question, Prof. Shou chooses a range in the array, $x_l,\ldots, x_r$. Then he defines $y_i=x_{l+i}$ for $0\le i\le r - l$ and asks Prof. Pang to answer the question for the $r-l+1$ pixels $(0, y_0), \ldots, (r-l, y_{r-l})$.

Please help Prof. Pang answer all the questions. For each question, output the answer with the **minimum** $(c, a, b)$ **in lexical order**.

It is guaranteed that the answer exists when Prof. Pang chooses the whole array $x_1, x_2, \dots, x_n$. So the answer always exists when Prof. Pang chooses an interval of this array.
## 输入格式

The first line contains a single integer $T$ ($1\le T\le 10^5$) denoting the number of test cases.

For each test case, the first line contains an integer $n$ ($1\leq n\leq 10^5$). The second line contains $n$ numbers $x_1, \ldots , x_{n}$ ($0\leq x_i\leq 10^9$).

The next line contains an integer $q$ ($1\le q\le 10^5$) denoting the number of questions.

Each of the following $q$ lines contains two integers $l, r$ ($1\le l\le r\le n$). 

It is guaranteed that the sum of $n$ over all test cases will not exceed $10^5$ and that the sum of $q$ over all test cases will not exceed $10^5$.
## 输出格式

In the order of input, output one line with three integers $a, b, c$ denoting the answer for each question.
## 样例

### 样例输入 #1
```
3
5
1 1 2 2 2
4
1 5
1 1
3 5
2 3
5
1 2 3 4 6
3
1 5
2 4
3 5
3
0 3 5
1
1 3

```
### 样例输出 #1
```
1 4 3
0 1 1
0 2 1
1 1 1
5 4 4
1 2 1
3 6 2
5 1 2

```
## 题目翻译

给定一个长度为 $n$ 的数组 $x$，接下来你有 $q$ 次询问。

第 $i$ 次询问给出一个区间 $l,r$，设 $k=r-l+1$，你提取出 $x$ 数组下标在 $l,r$ 之间的区间 $y_i=x_{i+l}(0\le i<k)$。

考虑 $k$ 个点 $(0,y_0),(1,y_1)\dots(k-1,y_{k-1})$。你需要找到一条直线的三个整数参数 $a,b,c$，满足 $\forall 0\le i<k,y_i=\lfloor \frac{ai+b}{c}\rfloor$。若有多条这样的直线，输出 $(c,a,b)$ 三元组字典序最小的一个。

保证对于整个数组，即 $l=1,r=n$ 的询问一定存在一组合法的解。

$n,q\le 10^5$，多组询问。


---

---
title: "[EC Final 2021] Prof. Pang and Ants"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9884
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2021] Prof. Pang and Ants
## 题目描述

Near Prof. Pang's big house, there is an ant group which has $m$ ants and lives underground in a cave with $n$ holes. They get out of the holes for food. So where is the food? It should be in Prof. Pang's big refrigerator. The ants want to steal the food from the big refrigerator.

![](https://cdn.luogu.com.cn/upload/image_hosting/afep0zz9.png)

Specifically, for an ant, it needs $1$ second to leave from the cave through any hole and $1$ second to enter the cave through any hole. Different holes have different locations. The distance between the $i$-th hole and the refrigerator is $a_i$. Thus, after leaving the cave through the $i$-th hole, an ant needs $a_i$ seconds to go to the refrigerator. After stealing some food from the refrigerator, an ant needs $a_i$ seconds to go back to the $i$-th hole. Stealing food costs no time for the ants since they are skillful enough.

Each ant will leave the cave to steal something from the refrigerator and return to (enter) the cave after stealing. Each ant must leave the cave exactly once and then return to the cave. One ant can arbitrarily choose one hole to leave and also arbitrarily choose one hole to enter, where the two holes need not be the same. For any hole, during any second, there can be at most one ant leaving or entering the cave through it. There cannot be one ant leaving the cave and another ant entering the cave using the same hole during the same second. Because of this capacity constraint, some ants may need to wait before they leave the hole and/or before they return to the hole after stealing.

So you, Prof. Pang's good friend, need to calculate the minimum time cost for ants to achieve the goal and play a trick on Prof. Pang so that the ants can steal the food without being caught by Prof. Pang. The time cost is defined as the total length of time during which at least one ant is not in the cave. When an ant is entering or leaving the cave through some hole, it is not in the cave.
## 输入格式

The first line contains a single integer $T~(1 \le T \le 10^5)$ denoting the number of test cases.

For each test case, the first line contains two integers $n,m$ ($1\le n \le 10^5, 1\le m \le 10^{14}$) denoting the number of the holes and the number of the ants respectively. The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($1\le a_i \le 10^9$) denoting the time needed to get to the refrigerator from the $i$-th hole.

It is guaranteed that the sum of $n$ over all test cases will not exceed $5\times 10^5$.
## 输出格式

For each test case, print one line containing one integer denoting the minimum time cost in seconds.
## 样例

### 样例输入 #1
```
3
2 4
1 2
3 10
1 2 3
5 1
1 2 3 4 5

```
### 样例输出 #1
```
6
9
4

```
## 提示

In the third test case, it takes the ant $2$ seconds to leave and enter the cave through the first hole. And it takes the ant $2$ seconds to move to the refrigerator and back to the hole.
## 题目翻译

在庞教授的大房子边上，有一群包含 $m$ 只蚂蚁的蚁群，居住在有 $n$ 个洞口的洞穴里。 它们会外出寻找食物。食物在庞教授的大冰箱里，蚂蚁们试图从里面偷出食物来。

![](https://cdn.luogu.com.cn/upload/image_hosting/afep0zz9.png)

**传神.jpg**

特别的, 一只蚂蚁需要 $1$ 秒从任何洞口离开，并同样需要 $1$ 秒从任何洞口进入洞穴。不同的洞口有不同的位置，对一个洞口来说，它与冰箱的距离以 $a_i$ 表示，同样的，一只蚂蚁从冰箱偷出食物再到第 $i$ 个洞口的时间也是 $a_i$ 秒。由于蚂蚁们技术高超，从冰箱拿出食物不会消耗它们任何时间。

每只蚂蚁都必须且只能从冰箱偷一次食物。蚂蚁可以任意选择一个洞口出发并进入任何一个洞口，**两个洞口可以不同**。一个洞口在 $1$ 秒内只能有一只蚂蚁进出。因为这个原因，有些蚂蚁在偷完食物后需要等待一段时间才能进入洞口。

所以，你作为庞教授的好朋友， 需要计算出蚂蚁们偷出食物的最短时间。时间的定义为至少存在一只蚂蚁在洞穴外的时间总长，正在进出洞口的蚂蚁不被看作在洞穴里。

## 输入格式

第一行包括一个整数 $T~(1 \le T \le 10^5)$ ，表示测试数据的总数。

对每组测试数据：

第一行包括两个整数 $n,m$  ($1\le n \le 10^5, 1\le m \le 10^{14}$) ，分别代表洞口的总数与蚂蚁的总数。 

第二行包括 $n$ 个整数 $a_1, a_2, \cdots, a_n$ ($1\le a_i \le 10^9$)， 表示第$i$号洞口到冰箱的距离。

数据保证所有数据中 $n$ 的总和不超过 $5\times 10^5$.

## 输出格式

对每组数据，输出一行一个整数代表蚂蚁所用最短时间的秒数。

## 样例 #1

### 样例输入 #1

```
3
2 4
1 2
3 10
1 2 3
5 1
1 2 3 4 5
```

### 样例输出 #1

```
6
9
4
```

## 提示

在第三组测试数据中，蚂蚁需要 $2$ 秒通过第一个洞口进出洞穴，并需要 $2$ 秒前往冰箱并搬回食物。


---

---
title: "[ICPC 2018 Qingdao R] Sequence and Sequence"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9885
tag: ['数学', '2018', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Sequence and Sequence
## 题目描述

Consider the following two sequences $P$ and $Q$. We denote $P(i)$ as the $i$-th element in sequence $P$, and $Q(i)$ as the $i$-th element in sequence $Q$:

- Sequence $P$ is a $\textbf{sorted}$ sequence where for all $k \in \mathbb{Z^+}$, $k$ appears in sequence $P$ for $(k+1)$ times ($\mathbb{Z^+}$ is the set of all positive integers). That is to say, $P = \{1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, \dots \}$
- Sequence $Q$ can be derived from the following equations: 
$$\begin{cases} Q(1) = 1 & \\ Q(i) = Q(i-1) + Q(P(i)) & \text{if } i > 1 \end{cases}$$ 
That is to say, $Q = \{1, 2, 4, 6, 8, 12, 16, 20, 24, 30, 36, 42, 48, 54, 62, \dots \}$

![](https://cdn.luogu.com.cn/upload/image_hosting/ukq7qs74.png)

Given a positive integer $n$, please calculate the value of $Q(n)$.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ (about $10^4$), indicating the number of test cases. For each test case:

The first and only line contains an integer $n$ ($1 \le n \le 10^{40}$).
## 输出格式

For each test case output one line containing one integer, indicating the value of $Q(n)$.
## 样例

### 样例输入 #1
```
4
10
100
1000
987654321123456789
```
### 样例输出 #1
```
30
2522
244274
235139898689017607381017686096176798
```
## 题目翻译

### 题目描述  

考虑下列两个序列 $P$ 和 $Q$。我们用 $P(i)$ 表示序列 $P$ 中的第  $i$ 个元素，用 $Q(i)$ 表示序列 $Q$ 中的第 $i$ 个元素：

- 序列 $P$ 是一个**已排序的**序列，其中，对于所有 $k \in \mathbb{Z^+}$，$k$ 在序列 $P$ 中出现 $(k+1)$ 次（$\mathbb{Z^+}$ 为正整数集）。也就是说，$P = \{1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, \dots \}$
- 序列 $Q$ 可以由以下方程导出：
$$\begin{cases} Q(1) = 1 & \\ Q(i) = Q(i-1) + Q(P(i)) & \text{if } i > 1 \end{cases}$$   
也就是说，$Q = \{1, 2, 4, 6, 8, 12, 16, 20, 24, 30, 36, 42, 48, 54, 62, \dots \}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ukq7qs74.png)

给定一个正整数 $n$，请计算 $Q(n)$ 的值。

### 输入格式

本题的测试点包含多组测试数据。

第一行输入包含一个整数 $T$ （$10^4$ 左右），表示测试数据的数量。对于每组测试数据：

- 第一行（也是唯一一行）包含一个整数 $n$ （$1 \le n \le 10^{40}$）。

### 输出格式

对于每组测试数据，输出一行，包含一个整数，表示 $Q(n)$ 的值。


---

---
title: "[ICPC 2018 Qingdao R] Mirror"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9892
tag: ['计算几何', '2018', 'Special Judge', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Mirror
## 题目描述

There is a non-transparent obstacle and a single-sided mirror in an infinite two-dimensional plane. The obstacle can be represented as a triangle and the mirror can be represented as a $\textbf{directional}$ line segment pointing from $(x_{m,1}, y_{m,1})$ to $(x_{m,2}, y_{m,2})$, with the right side being reflective.

There are $m$ stones at point $(x_1,y_1)$ and DreamGrid would like to move all the stones to point $(x_2,y_2)$. The following constraints must be satisfied:

- DreamGrid can only carry one stone each time.
- Once DreamGrid picks up a stone, he can only put it down at point $(x_2,y_2)$.
- Let $L$ be the path DreamGrid walked, then for each point $p$ on $L$, DreamGrid should see all the stones directly or through the mirror.

Note that:

- If some part of the line vision is inside the obstacle (it's ok that the line vision passes a point or edge of the obstacle), it's considered, that DreamGrid cannot see the stone with this line of vision.
- If one of the two endpoints of the mirror is on the line of vision, it's considered, that DreamGrid can see the stone both in the mirror and through the mirror.
- The reflection process is governed by laws of physics --- the angle of incidence is equal to the angle of reflection. The incident ray is in the same half-plane as the reflected ray, relative to the mirror.
- If the line of vision is parallel to the mirror, reflection doesn't take place, and the mirror isn't regarded as an obstacle.
- DreamGrid cannot move into the obstacle but can move on the edges or the vertices of the obstacle.
- DreamGrid cannot move through the mirror but can move on the mirror. Note that if DreamGrid is on the line segment of the mirror other than the two endpoints, he can only see the side he comes from, and cannot see through the mirror.

DreamGrid would like to know the shortest distance to move all stones from $(x_1,y_1)$ to $(x_2, y_2)$.
## 输入格式

There are multiple test cases. The first line of input is an integer $T$ (about 100), indicates the number of test cases. For each test case:

The first line contains one integer $m$ ($1 \le m \le 10^6$), indicating the number of stones.

The second line contains four integers $x_1$, $y_1$, $x_2$ and $y_2$, indicating the start point and the target point.

The third line contains four integers $x_{m,1}$, $y_{m,1}$, $x_{m,2}$ and $y_{m,2}$, indicating the coordinates of the mirror.

Each of the next $3$ lines has two integers $x_i$ and $y_i$, indicating the coordinates of the vertices of the obstacle.

All the coordinates will not exceed $100$ in absolute value. Both the start point and target point are outside the obstacle and the mirror. The mirror and the obstacle have no points in common.

It is guaranteed that no three points are collinear.
## 输出格式

For each test case, output a real number indicating the shortest distance, or output $-1$ if DreamGrid cannot move all the stones under the constraints.

Your answer will be considered correct if and only if the absolute error or relative error of your answer is less than $10^{-6}$.
## 样例

### 样例输入 #1
```
2
2
-2 0 2 0
-3 3 3 3
0 1
-3 -2
3 -2
2
-2 0 2 0
-3 3 -1 3
0 1
-3 -2
3 -2
```
### 样例输出 #1
```
13.416407864999
-1
```
## 提示

We now welcome our special guest Mashiro, who heartily donates this problem to our problemset, to explain the sample test cases for us using her sketch book.

![](https://cdn.luogu.com.cn/upload/image_hosting/wsxbrf43.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/d2bpz78p.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/nfhakntz.png)

$\textit{(Image from pixiv. ID: 32084305)}$

In the figures above, we indicate the start point as point $A$ and the target point as point $B$. The mirror is indicated by the line segment pointing from $M1$ to $M2$, with the right side being reflective.

For the first sample test case, the optimal path is $A \to C \to B \to C \to A \to C \to B$.

For the second sample test case, as DreamGrid cannot see $A$ from $B$, it's impossible to move all the two stones from $A$ to $B$ while following the constraints in the problem description.

## 题目翻译

### 题目描述

在一个无限二维平面上包含一个不透明障碍物和一个单面镜子。障碍物被表示为一个三角形，而镜子被表示为一个从点 $(x_{m,1}, y_{m,1})$ 指向 $(x_{m,2}, y_{m,2})$ 的有方向的线段，线段的右侧是反射面。

有 $m$ 个石头位于点 $(x_1,y_1)$，DreamGrid 希望将所有石头移动到点 $(x_2,y_2)$。需要满足以下条件：

DreamGrid 每次只能携带一个石头。
一旦 DreamGrid 拿起一个石头，他只能将其放置在点 $(x_2,y_2)$。

设 $L$ 为 DreamGrid 走过的路径，对于路径上的每一个点 $p$，DreamGrid 必须能直接或通过镜子看到所有的石头。

**注意：**

如果视线的某部分在障碍物内（视线穿过障碍物的点或边界是允许的），则认为 DreamGrid 无法通过这条视线看到石头。

如果镜子的一个端点在视线上，认为 DreamGrid 既可以在镜子中看到石头，也可以透过镜子看到石头。

反射过程遵循物理规律：入射角等于反射角。入射光线和反射光线在镜子的同一侧。

如果视线与镜子平行，则不发生反射，镜子不被视为障碍物。
DreamGrid 不能移动进入障碍物，但可以在障碍物的边缘或顶点上移动。

DreamGrid 不能穿过镜子移动，但可以在镜子上移动。注意，如果 DreamGrid 在镜子的线段上（不包括两个端点），他只能看到他来的那一侧，并且不能透过镜子看到。
DreamGrid 想要知道移动所有石头从 $(x_1,y_1)$ 到 $(x_2, y_2)$ 的最短距离。

### 输入格式

输入包括多个测试用例。第一行是一个整数 $T$（大约 100），表示测试用例的数量。对于每个测试用例：

第一行包含一个整数 $m$（$1 \le m \le 10^6$），表示石头的数量。

第二行包含四个整数 $x_1$, $y_1$, $x_2$ 和 $y_2$，表示起始点和目标点。

第三行包含四个整数 $x_{m,1}$, $y_{m,1}$, $x_{m,2}$ 和 $y_{m,2}$，表示镜子的坐标。

接下来的 $3$ 行，每行包含两个整数 $x_i$ 和 $y_i$，表示障碍物顶点的坐标。

所有坐标的绝对值不超过 $100$。起始点和目标点都在障碍物和镜子之外。镜子和障碍物没有公共点。

保证没有三个点是共线的。

### 输出格式

输出对于每个测试用例，输出一个实数表示最短距离，如果 DreamGrid 无法在约束条件下移动所有石头，则输出 $-1$。

如果你的答案的绝对误差或相对误差小于 $10^{-6}$，则认为你的答案是正确的。


---

