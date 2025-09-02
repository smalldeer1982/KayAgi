---
title: "[NOI2013] 树的计数"
layout: "post"
diff: 省选/NOI-
pid: P1232
tag: ['递推', '2013', 'NOI', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOI2013] 树的计数
## 题目描述

我们知道一棵有根树可以进行深度优先遍历（DFS）以及广度优先遍历（BFS）来生成这棵树的 DFS 序以及 BFS 序。两棵不同的树的 DFS 序有可能相同，并且它们的 BFS 序也有可能相同，例如下面两棵树的 DFS 序都是 `1 2 4 5 3`，BFS 序都是 `1 2 3 4 5`。

![](https://cdn.luogu.com.cn/upload/image_hosting/kagmha60.png)

现给定一个 DFS 序和 BFS 序，我们想要知道，符合条件的有根树中，树的高度的平均值。即，假如共有 $K$ 棵不同的有根树具有这组 DFS 序和 BFS 序，且他们的高度分别是 $h_1, h_2, \ldots, h_K$，那么请你输出：

$$
\frac{h_1+h_2+\ldots+h_K}K
$$
## 输入格式

第一行包含 $1$ 个正整数 $n$，表示树的节点个数。

第二行包含 $n$ 个正整数，是一个 $1 \ldots n$ 的排列，表示树的 DFS 序。

第三行包含 $n$ 个正整数，是一个 $1 \ldots n$ 的排列，表示树的 BFS 序。

输入保证至少存在一棵树符合给定的两个序列。
## 输出格式

输出 $1$ 个实数，四舍五入保留恰好三位小数，表示树高的平均值。
## 样例

### 样例输入 #1
```
5 
1 2 4 5 3 
1 2 3 4 5

```
### 样例输出 #1
```
3.500

```
## 提示

如果输出文件的答案与标准输出的差不超过 $0.001$，则将获得该测试点上的分数，否则不得分。

### 数据范围

- 对于 $20\%$ 的测试数据，满足：$n \le 10$；
- 对于 $40\%$ 的测试数据，满足：$n \le 100$；
- 对于 $85\%$ 的测试数据，满足：$n \le 2 \times 10^3$；
- 对于 $100\%$ 的测试数据，满足：$2 \le n \le 2 \times 10^5$。


---

---
title: "[GCJ 2019 Finals] Go To Considered Helpful"
layout: "post"
diff: 省选/NOI-
pid: P13128
tag: ['动态规划 DP', '2019', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ 2019 Finals] Go To Considered Helpful
## 题目描述

Marlin is a fish who lost his son and is trying to find him. Fortunately, he ran into Cynthia, a turtle, as she swam around with her brothers, Wally and Seymour. Cynthia knows exactly where Marlin needs to go, and she can be very precise in giving directions. While Marlin is smart and can follow them perfectly, keeping track of a long list of directions can be problematic. Cynthia needs to find a way to make the list of directions short.

Marlin lives in a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns. Some cells of the matrix are dangerous and cannot be entered. Marlin and his son are currently in different non-dangerous cells. Marlin's son never moves to a different cell. Cynthia decided to give Marlin directions in the form of a program consisting of a list of instructions, each on a single line. Each instruction is of one of 5 types:

* $\mathbf{N}$: move one cell North (up),
* $\mathbf{S}$: move one cell South (down),
* $\mathbf{W}$: move one cell West (left),
* $\mathbf{E}$: move one cell East (right), and
* $\mathbf{G}(\mathbf{i})$: jump to the i-th line of the instruction list (counting starting from 1).

After executing a line with any of the first 4 instructions, Marlin jumps to the next line on the list if there is one. If there is no next line, Marlin just stands still forever.

For example, if Marlin were following the program

1. $\mathbf{N}$
2. $\mathbf{E}$
3. $\mathbf{G}(6)$
4. $\mathbf{S}$
5. $\mathbf{G}(1)$
6. $\mathbf{W}$
7. $\mathbf{G}(4)$

he would move North (line 1), then East (2), then jump to line 6 without physically moving (3), then move West (6), then jump to line 4 (7), then move South (4), then jump to line 1 (5), then move North (1), etc.

If at any point Marlin and his son are at the same cell, they will be reunited and Marlin will no longer follow any instructions. Cynthia the turtle wants to find out the smallest number of lines in a program that would get Marlin to the same cell as his son, without him ever going into a dangerous cell or moving outside of the matrix boundaries. All $\mathbf{G}$ instructions must jump to existing lines in the program.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing $\mathbf{R}$ and $\mathbf{C}$, the number of rows and columns in the matrix. Then, $\mathbf{R}$ lines follow containing a string of $\mathbf{C}$ characters each. The $j$-th character of the $i$-th of these lines $\mathbf{A}_{ij}$ represents the cell in the $i$-th row and $j$-th column of the matrix. The character is $\#$ if the cell is dangerous, an uppercase $\mathbf{M}$ if the cell is the one Marlin is currently at, an uppercase $\mathbf{N}$ if the cell is the one Marlin's son is currently at and $\mathbf{.}$ if the cell is an unoccupied non-dangerous cell.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is $\text{IMPOSSIBLE}$ if there is no program that would get Marlin to his son under the conditions explained above, or the smallest number of instructions in such a program.
## 样例

### 样例输入 #1
```
5
2 5
N...#
....M
2 5
N#...
...#M
5 5
N..##
#.###
#...#
##.##
##..M
5 5
..N##
#.###
#...#
##.##
##..M
3 3
#M#
###
#N#
```
### 样例输出 #1
```
Case #1: 4
Case #2: 7
Case #3: 5
Case #4: 6
Case #5: IMPOSSIBLE
```
## 提示

**Sample Explanation**

Below are some shortest programs for each of the possible sample case.

- Sample Case #1:
```
1: W
2: N
3: S
4: G(1)
```
or
```
1: W
2: N
3: W
4: G(3)
```

- Sample Case #2:
```
1: N
2: W
3: W
4: S
5: W
6: W
7: N
```
- Sample Case #3:
```
1: W
2: W
3: N
4: N
5: G(2)
```
- Sample Case #4:
```
1: W
2: W
3: N
4: N
5: E
6: G(1)
```

**Sample Explanation**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{A}_{ij}$ is either $\#$, $\mathbf{.}$, uppercase $\mathbf{M}$ or uppercase $\mathbf{N}$, for all $i$ and $j$.
- $\mathbf{A}_{ij} = \mathbf{M}$ for exactly one pair of $i$ and $j$.
- $\mathbf{A}_{ij} = \mathbf{N}$ for exactly one pair of $i$ and $j$.

**Test set 1 (19 Pts, Visible)**

- Time limit: 30 seconds.
- $1 \leq \mathbf{R} \leq 10$.
- $1 \leq \mathbf{C} \leq 10$.

**Test set 2 (30 Pts, Hidden)**

- Time limit: 120 seconds.
- For at most 10 test cases:
  - $1 \leq \mathbf{R} \leq 100$.
  - $1 \leq \mathbf{C} \leq 100$.
- For the remaining test cases:
  - $1 \leq \mathbf{R} \leq 50$.
  - $1 \leq \mathbf{C} \leq 50$.


---

---
title: "[GCJ 2017 #2] Shoot the Turrets"
layout: "post"
diff: 省选/NOI-
pid: P13174
tag: ['2017', 'Special Judge', '广度优先搜索 BFS', '二分图', 'Google Code Jam']
---
# [GCJ 2017 #2] Shoot the Turrets
## 题目描述

The fight to free the city from extraterrestrial invaders is over! People are happy that love and peace have returned.

The city is represented as a grid with $R$ rows and $C$ columns. Some cells on the grid are buildings (through which nobody can see, nobody can shoot, and nobody can walk), and some are streets (through which everybody can see, shoot and walk). Unfortunately, during the war, the now-defeated invaders set up automatic security turrets in the city. These turrets are only in streets (not in buildings). They pose a threat to the citizens, but fortunately, there are also some soldiers on the streets (not in buildings). Initially, no soldier is in the same place as a turret.

The invader turrets do not move. They are small, so they don't block sight and shooting. A soldier cannot walk through an active turret's cell, but can walk through it once it is destroyed. A turret can only see soldiers in the cells for which it has a horizontal or vertical line of sight. If a soldier enters such a cell, the turret does not fire. If a soldier attempts to exit such a cell (after entering it, or after starting in that cell), the turret fires. Luckily, a soldier can still shoot from that cell, and the turret will not detect that as movement. It means that none of your soldiers will actually die, because in the worst case they can always wait, motionless, for help (perhaps for a long time). Maybe you will have a chance to rescue them later.

Each soldier can make a total of $M$ unit moves. Each of these moves must be one cell in a horizontal or vertical direction. Soldiers can walk through each other and do not block the lines of sight of other soldiers or turrets. Each soldier also has one bullet. If a soldier has a turret in her horizontal or vertical line of sight, the soldier can shoot and destroy it. Each shot can only destroy one turret, but the soldiers are such excellent shooters that they can even shoot past one or several turrets or soldiers in their line of sight and hit another turret farther away!

You are given a map (with the soldier and turret positions marked). What is the largest number of turrets that the soldiers can destroy?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the integer $C$ (the width of the map), $R$ (the height of the map) and $M$ (the number of unit moves each soldier can make). The next $R$ lines contain $C$ characters each, with . representing a street, # representing a building, S representing a soldier and T representing a turret.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum number of turrets that it is possible to destroy. Then $y$ lines should follow: each should contain two integers $s_i$ and $t_i$ denoting that the $i$th thing that happens should be soldier $s_i$ destroying turret $t_i$ (you don't need to specify exactly how the soldier has to move). If multiple valid strategies exist, you may output any one of them.

Soldiers are numbered from 1, reading from left to right along the top row, then left to right along the next row down from the top, and so on, from top to bottom.
## 样例

### 样例输入 #1
```
4
2 2 1
#S
T.
2 6 4
.T
.T
.T
S#
S#
S#
5 5 4
.....
SS#.T
SS#TT
SS#.T
.....
3 3 8
S.#
.#.
#.T
```
### 样例输出 #1
```
Case #1: 1
1 1
Case #2: 3
3 3
1 1
2 2
Case #3: 3
1 2
2 1
6 3
Case #4: 0
```
## 提示

**Sample Explanation**

In Case #2, one of the possible solutions is to move soldier $3$ up three cells and shoot turret $3$. Then soldier $1$ can move up one cell and right one cell (to where turret $3$ was) and shoot past turret $2$ to destroy turret $1$. Finally, soldier $2$ can move up three cells and shoot turret $2$.

In Case #3, soldier $1$ can move up one cell, then right three cells and shoot turret $2$. Then soldier $2$ can move up one cell, then right three cells and shoot turret $1$. Finally, soldier $6$ can move down one cell, then right three cells and shoot turret $3$. Other soldiers have insufficient move range to shoot any other turrets.

In Case #4, the soldier cannot move to within the same row or column as the turret, so the turret cannot be destroyed.

**Limits**

- $1 \leq T \leq 100$.
- $0 \leq M < C \times R$.

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~30~~ 7.5 seconds.
- $1 \leq C \leq 30$.
- $1 \leq R \leq 30$.
- The number of S symbols is between $1$ and $10$.
- The number of T symbols is between $1$ and $10$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~60~~ 15 seconds.
- $1 \leq C \leq 100$.
- $1 \leq R \leq 100$.
- The number of S symbols is between $1$ and $100$.
- The number of T symbols is between $1$ and $100$.


---

---
title: "[USACO07FEB] Lilypad Pond G"
layout: "post"
diff: 省选/NOI-
pid: P1606
tag: ['图论', '2007', 'USACO', '广度优先搜索 BFS', '最短路']
---
# [USACO07FEB] Lilypad Pond G
## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.

## 输入格式

第一行两个用空格分开的整数 $M$ 和 $N$。

第二行到 $M+1$ 行，第 $i+1$ 行有 $N$ 个用空格分开的整数，描述了池塘第 $i$ 行的状态：

- $0$ 为水，$1$ 为莲花，$2$ 为岩石，$3$ 为贝西所在的起点，$4$ 为贝西想去的终点。
## 输出格式

第一行一个整数，需要增加的最少莲花数；如果无解，输出 $-1$。

第二行输出放置这些莲花的方案数量，保证这个数字可用一个 $64$ 位的有符号整数，表示。

特别地，如果第一行是 $-1$，不要输出第二行。
## 样例

### 样例输入 #1
```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0

```
### 样例输出 #1
```
2
3

```
## 提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$
## 题目翻译

为了让奶牛们娱乐和锻炼，农夫约翰建造了一个美丽的池塘。这个长方形的池子被分成了 $M$ 行 $N$ 列个方格（$1 \le M,N \le 30$）。一些格子是坚固得令人惊讶的莲花，还有一些格子是岩石，其余的只是美丽、纯净、湛蓝的水。

贝西正在练习芭蕾舞，她站在一朵莲花上，想跳到另一朵莲花上去，她只能从一朵莲花跳到另一朵莲花上，既不能跳到水里，也不能跳到岩石上。

贝西的舞步很像象棋中的马步：每次总是先横向移动一格，再纵向移动两格，或先纵向移动两格，再横向移动一格。最多时，贝西会有八个移动方向可供选择。

约翰一直在观看贝西的芭蕾练习，发现她有时候不能跳到终点，因为中间缺了一些荷叶。于是他想要添加几朵莲花来帮助贝西完成任务。一贯节俭的约翰只想添加最少数量的莲花。当然，莲花不能放在石头上。

请帮助约翰确定必须要添加的莲花的最少数量，以及有多少种放置这些莲花的方法。


---

---
title: "魔法指纹"
layout: "post"
diff: 省选/NOI-
pid: P1822
tag: ['模拟', '广度优先搜索 BFS']
---
# 魔法指纹
## 题目描述

对于任意一个至少两位的正整数 $n$，按如下方式定义 $\mathrm{magic}(n)$：将 $n$ 按十进制顺序写下来，依次对相邻两个数写下差的绝对值。这样，得到了一个新数，去掉前导 $0$，则定义为 $\mathrm{magic}(n)$。特别地，若 $n$ 为一位数，则 $mag_ic(n)=n$。

例如：$\mathrm{magic}(5913)=482$，$\mathrm{magic}(1198)=081=81$，$\mathrm{magic}(666)=00=0$。

对任意一个数 $n$，反复迭代计算 $\mathrm{magic}$ 值直到 $n$ 变成一个一位数，可以得到一个序列 $[n,\mathrm{magic}(n),\mathrm{magic}(\mathrm{magic}(n)),\cdots]$。最后的这个值称为数 $n$ 的 $\mathrm{magic}$ 指纹。

例如，对于 $n=5913$，我们得到序列：$[5913,482,46,2]$。所以 $5913$ 的 $\mathrm{magic}$ 指纹为 $2$。

若一个数的 $\mathrm{magic}$ 指纹为 $7$，则认为这个数是个幸运数。

现在，给定 $A,B$，计算出 $[A,B]$ 中有多少个数是幸运数。
## 输入格式

输入两行，每行一个数。第一行是 $A$，第二行表示 $B$。

## 输出格式

输出 $[A,B]$ 中有多少个数是幸运数。

## 样例

### 样例输入 #1
```
1
9
```
### 样例输出 #1
```
1

```
## 提示

### 数据范围及约定

- 对于 $30\%$ 数据，$B \le 10^4$。
- 对于 $100\%$ 数据，$0<A \le B \le 10^9$。



---

---
title: "[HNOI2006] 潘多拉的宝盒"
layout: "post"
diff: 省选/NOI-
pid: P2321
tag: ['搜索', '2006', '各省省选', '湖南', '广度优先搜索 BFS', 'Tarjan']
---
# [HNOI2006] 潘多拉的宝盒
## 题目描述

 ![](https://cdn.luogu.com.cn/upload/pic/1372.png) 

![](https://cdn.luogu.com.cn/upload/pic/1373.png)

## 输入格式

 ![](https://cdn.luogu.com.cn/upload/pic/1374.png) 

![](https://cdn.luogu.com.cn/upload/pic/1375.png)

## 输出格式

输出一行一个数$t$，表示最长升级序列的长度。

## 样例

### 样例输入 #1
```
4
1  1
0
0  0
2  1
0
1  1
0  0
3  1
0
1  1
2  2
0  0
4  1
0
1  1
2  2
3  3
0  0
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3
1  1
0
0  0
3  1
0
0  1
2  0
1  2
9  1
0
0  1
2  3
4  5
6  7
8  0
1  2
3  4
5  6
7  8
```
### 样例输出 #2
```
3
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1380.png)



---

---
title: "[AHOI2005] 穿越磁场"
layout: "post"
diff: 省选/NOI-
pid: P2537
tag: ['2005', '各省省选', '离散化', '安徽', '广度优先搜索 BFS', '最短路']
---
# [AHOI2005] 穿越磁场
## 题目描述

探险机器人在Samuel星球上寻找一块奇特的矿石，然而此时它陷入了一片神秘的磁场区域，动弹不得。

探险空间站立刻扫描了这片区域，绘制出该区域的磁场分布平面图。这片区域中分布了N个磁场，每个磁场呈正方形，且边与坐标轴平行。

例如下图中，存在3个磁场，白点表示机器人的位置，黑点表示矿石的位置：

 ![](https://cdn.luogu.com.cn/upload/pic/1642.png) 

科学家们分析平面图，进一步发现：这些磁场为大小不一的正方形，可能相交，甚至覆盖，但是它们的边缘不会重合，顶点也不会重合。

例如下面的两种情形是不会出现的：

 ![](https://cdn.luogu.com.cn/upload/pic/1643.png) 

科学家们给探险机器人启动了磁力罩，这样它就可以在磁场中自由穿越了。

初始时，探险机器人和所有矿石都不在任何磁场的边缘。由于技术限制，在穿越过程中机器人只能够水平或垂直移动，且不能够沿着磁场的边缘行动。

由于磁力罩的能量有限，科学家们希望探险机器人穿越尽量少的磁场边缘采集到这块矿石。例如上图中，探险机器人最少需要穿越两次磁场边缘。

现在小联请你编写程序，帮助科学家们设计探险机器人的路线，统计探险机器人最少需要穿越多少次磁场边缘。

## 输入格式

第一行有一个整数N，表示有N个磁场（1 < N < 100）。随后有N行，每行有三个整数X、Y、C（0 < X ,Y ,C < 10000），表示一个磁场左下角坐标为（X,Y），边长为C。接下来有一行，共有四个整数SX, SY, TX, TY，表示机器人初始坐标为（SX, SY），矿石坐标为（TX，TY）（其中，1 < SX, SY, TX, TY < 10000）。

## 输出格式

单行输出一个整数，表示机器人最少需要穿越多少次磁场边缘。

## 样例

### 样例输入 #1
```
2
1 3 3 
2 1 4
0 0 3 4
```
### 样例输出 #1
```
2
```


---

---
title: "[USACO13DEC] The Bessie Shuffle G"
layout: "post"
diff: 省选/NOI-
pid: P3098
tag: ['2013', 'USACO', '并查集', '广度优先搜索 BFS', '图论建模']
---
# [USACO13DEC] The Bessie Shuffle G
## 题目描述

Bessie is practicing her card tricks.  She has already mastered the Bessie- shuffle -- a shuffle on M (2 <= M <= 100,000) cards that reorganizes the cards so the i-th card from the top is now the P[i]-th card from the top.

Now Bessie is practicing shuffles on larger decks.  She has a deck of N cards (M <= N <= 1,000,000,000) conveniently labeled 1 to N.  She shuffles this deck by taking the first M cards and performing the Bessie-shuffle on them, placing the shuffled cards back on top of the deck.  She then removes the top card from the deck and places it face down.  She repeats this process, placing the top cards successively on top of each other, until she is out of cards.  When Bessie has less than M cards left, she no longer performs the Bessie-shuffle, but continues to place the top card on top of the others.

Bessie knows that the deck initially started in sorted order, with 1 on top, 2 next, and N on the bottom.  Given the description of the Bessie-shuffle, help Bessie compute which cards end up located at Q different specified positions (1 <= Q <= N, Q <= 5,000) in the deck.

50% of test cases will have N <= 100,000. 

贝西有一种独门的洗牌方法，称为 A 类洗牌法；

A 类洗牌法的具体过程：将一堆共 $M$（$2 \le M \le 10 ^ 5$）张从上到下编号 $1, 2, \cdots, M$ 的纸牌，从上到下第 $i$ 张牌洗到位置 $p _ i$。

例如，$M=3，p = \{3, 1, 2\}$，则执行一次 A 类洗牌法后，从上到下将变为 $2, 3, 1$，即牌 $1$ 放到位置 $3$，牌 $2$ 放到位置 $1$，牌 $3$ 放到位置 $2$。


贝西现在要练习另外一种洗牌方法，称为 B 类洗牌法。


B 类洗牌法的具体过程： 

有一堆 $N$（$M \le N \le 10 ^ 9$）张编号为 $1, 2, \cdots, N$ 的牌，并按从上到下 $1$ 到 $N$ 的顺序堆放。另有一个牌堆用来辅助洗牌，称为临时堆，开始时为空。

1. 将最上面 $M$ 张牌进行一次 A 类洗牌法；
2. 将最上面的一张牌放到临时堆的最上方；
3. 重复前两个操作，直到原先的堆没有牌为止。


以上过程中，当原先堆的牌不足 $M$ 张的时候，将不进行 A 类洗牌法，而是将最上面的牌依次放到临时堆上。


给定 $N, M$ 和排列 $p$。现在有 $Q$（$1 \le Q \le \min(N, 5000)$）个询问，请求出对其做一次 B 类洗牌法后临时堆中 $q _ i$ 位置上的牌的编号。

$50\%$ 的数据中，$N \le 10 ^ 5$。

## 输入格式

\* Line 1: A single line containing N, M and Q separated by a space.

\* Lines 2..1+M: Line i+1 indicates the position from the top, P[i], of the i-th card in the Bessie-shuffle (1 <= P[i] <= M).

\* Lines 2+M..1+M+Q: Line i+1+M contains a single integer q\_i

describing the i-th query.  You are to compute the label on the card located in position q\_i from the top (1 <= q\_i <= N).

## 输出格式

\* Lines 1..Q: On the i-th line, print a single integer indicating the card at position q\_i from the top.

## 样例

### 样例输入 #1
```
5 3 5 
3 
1 
2 
1 
2 
3 
4 
5 

```
### 样例输出 #1
```
4 
5 
3 
1 
2 

```
## 提示

Bessie has a deck of 5 cards initially ordered as [1, 2, 3, 4, 5].  Her shuffle is on 3 cards and has the effect of moving the top card to the bottom.  There are 5 queries querying each position in the deck.


The shuffle proceeds as:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (put 2 face down) 
[3, 1, 4, 5] -> [1, 4, 3, 5] (put 1 face down) 
[4, 3, 5] -> [3, 5, 4] (put 3 face down) 
[5, 4] (put 5 face down) 
[4] (put 4 face down) 
```
This produces the final order of [4, 5, 3, 1, 2]

贝西的五张牌刚开始顺序为 [1, 2, 3, 4, 5]。她一次洗三张牌，效果是将第一张牌放到底部。以上五个问题询问了每一张牌的位置。


洗牌的顺序是:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (将2正面向下放置)
[3, 1, 4, 5] -> [1, 4, 3, 5] (将1正面向下放置) 
[4, 3, 5] -> [3, 5, 4] (将3正面向下放置) 
[5, 4] (将5正面向下放置) 
[4] (将4正面向下放置) 
```
这就形成了最终的顺序：[4, 5, 3, 1, 2]



---

---
title: "[HNOI2008] 神奇的国度"
layout: "post"
diff: 省选/NOI-
pid: P3196
tag: ['2008', '湖南', '广度优先搜索 BFS', '哈希 hashing', '弦图']
---
# [HNOI2008] 神奇的国度
## 题目描述

K国是一个热衷三角形的国度,连人的交往也只喜欢三角原则.他们认为三角关系:即AB相互认识,BC相互认识,CA相互认识,是简洁高效的.为了巩固三角关系,K国禁止四边关系,五边关系等等的存在.

所谓N边关系,是指N个人 A1A2...An之间仅存在N对认识关系:(A1A2)(A2A3)...(AnA1),而没有其它认识关系.比如四边关系指ABCD四个人 AB,BC,CD,DA相互认识,而AC,BD不认识.全民比赛时,为了防止做弊，规定任意一对相互认识的人不得在一队，国王相知道，最少可以分多少支队。

## 输入格式

第一行两个整数N，M。1<=N<=10000,1<=M<=1000000.表示有N个人，M对认识关系. 接下来M行每行输入一对朋友

## 输出格式

输出一个整数，最少可以分多少队

## 样例

### 样例输入 #1
```
4 5
1 2
1 4
2 4
2 3
3 4
```
### 样例输出 #1
```
3
```
## 提示

一种方案(1,3)(2)(4)



---

---
title: "[SCOI2011] 地板"
layout: "post"
diff: 省选/NOI-
pid: P3272
tag: ['动态规划 DP', '2011', '四川', 'O2优化', '广度优先搜索 BFS', '进制']
---
# [SCOI2011] 地板
## 题目描述

lxhgww 的小名叫“小 L”，这是因为他总是很喜欢 L 型的东西。

小 L 家的客厅是一个 $r\times c$ 的矩形，现在他想用 L 型的地板来铺满整个客厅，客厅里有些位置有柱子，不能铺地板。

现在小 L 想知道，用 L 型的地板铺满整个客厅有多少种不同的方案？

需要注意的是，如下图所示，L 型地板的两端长度可以任意变化，但不能长度为 $0$。

![](https://cdn.luogu.com.cn/upload/pic/4636.png)

铺设完成后，客厅里面所有没有柱子的地方都必须铺上地板，但同一个地方不能被铺多次。
## 输入格式

输入的第一行包含两个整数，$r$ 和 $c$，表示客厅的大小。

接着是 $r$ 行，每行 $c$ 个字符，字符要么是 `_`，要么是 `*`，`_` 表示对应的位置是空的，必须铺地板；`*` 表示对应的位置有柱子，不能铺地板。
## 输出格式

输出一行，包含一个整数，表示铺满整个客厅的方案数。由于这个数可能很大，只需输出它除以 $20110520$ 的余数。
## 样例

### 样例输入 #1
```
2 2
*_
__
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 3
 ___
 _*_
 ___
```
### 样例输出 #2
```
8
```
## 提示

#### 数据规模与约定
| 测试点编号 | 数据限制 |
| :----------: | :----------: |
| $1\sim 2$ | $1\le r\times c\le 25$ |
| $3\sim 5$ | $1\le r\times c\le 100$ 并且 （$r=2$ 或者 $c=2$） |
| $6\sim 10$ | $1\le r\times c\le 100$ |


---

---
title: "[ZJOI2014] 璀灿光华"
layout: "post"
diff: 省选/NOI-
pid: P3342
tag: ['2014', '浙江', '枚举', '广度优先搜索 BFS', '图论建模']
---
# [ZJOI2014] 璀灿光华
## 题目描述

金先生有一个女朋友没名字。她勤劳勇敢、智慧善良。金先生很喜欢她。为此，金先生用 $a^3$ 块 $1\times 1 \times 1$ 的独特的水晶制作了一个边长为 $a$ 的水晶立方体，他要将这个水晶立方体送给他见过最单纯善良的她。

由于水晶立方体太太，不好运送，金先生还是将它拆开来送出。他相信拼好这个水晶立方难不倒聪明的她。

没名字收到了礼物后果然不一会儿就根据说明将水晶立方体拼好了。没名字发现，有 $n$ 块水晶在漆黑安静的夜晚会随机以等概率向上下左右前后六个方向的一个发出穿透光。被光照到的水晶显得格外好看。没名字给每一块不会发光的水晶定义了一个好看程度。水晶立方体在夜晚中的好看程度就是每块被光照到的水晶的好看程度之和。没名字想知道，水晶立方体在夜晚中的好看程度的最小值和最大值。
## 输入格式

第一行是 $a$，表示水晶立方体的边长。
接下来 $a^3$ 行，每行若干整数。
第一个数 $g_i$ 表示第 $i$ 块水晶的好看程度。如果 $g_i=0$，代表这块水晶会发光。接下来 $3\sim 6$ 个整数，代表与这块水晶有共同面的水晶编号。
## 输出格式

两个整数，代表水晶立方体在夜晚好看程度的最小值与最大值。
## 样例

### 样例输入 #1
```
2
0 7 2 3
0 8 1 4
4 5 4 1
8 6 3 2
16 3 6 7
32 4 5 8
1 1 8 5
2 2 7 6
```
### 样例输出 #1
```
0 12
```
## 提示

对于所有数据，$1<a\leq 70$，$g_i<10^6$，$n\leq 8$。



---

---
title: "[POI 2006] ZAB-Frogs"
layout: "post"
diff: 省选/NOI-
pid: P3438
tag: ['2006', '二分', '单调队列', 'POI（波兰）', '广度优先搜索 BFS']
---
# [POI 2006] ZAB-Frogs
## 题目描述

A scourge of frogs destroying all the crop has started in Byteotia. A farmer named Byteasar has decided to fight the vermin with peculiar "scarefrogs", that he has set up at certain points of his field. While moving from one place to another, every frog tries to keep as far of them as possible, i.e. maximizes the distance to the closest scarefrog.

The field that belongs to Byteasar has rectangular shape. The frogs leap in directions parallel to the field's sides and their leaps are unitary (of length 1). The scarefrogs-distance, for a given frog's route, is the minimum of all distances from all scarefrogs at all inter-leap-points of the route.

Byteasar already knows the most common starting and destination points of the frogs' routes, therefore he experiments with various deployments of the scarefrogs. He asks you for help, namely he would like you to write a programme that calculates the maximum (over all routes) scarefrogs-distance for a given deployment of scarefrogs - which we call in short the frogshold distance.

TaskWrite a programme that:

reads from the standard input the size of the field, the coordinates of the screfrogs and the source and target position of a frog,determines the frogshold distance (the maximum scarefrogs-distance a frog may achieve while still being able to reach the target point)writes the square of this number to the standard output.

给定一个网格图，其中有一些坏点，要求使起点到终点的路径上的所有点到离该点最近的坏点的最小距离距离最大，求这个最大值。

## 输入格式

The first line of the input contains two integers: $w_x$ and $w_y$ separated by a single space - the breadth and length of the field ($2 \le w_x, w_y \le 1000$). The second line of the input contains four integers: $p_x$, $p_y$, $k_x$ and $k_y$ separated by single spaces; $(p_x, p_y)$ is the initial position of the frog, $(k_x, k_y)$is the target (final) position of the frog ($1 \le p_x, k_x \le w_x$, $1 \le p_y, k_y \le w_y$). The third line of the standard input contains one integer $n$ - these are the coordinates of the ith scarefrog ($1 \le n \le w_x \cdot w_y$). No two scarefrogs occupy the same position and none of them is at the point $(p_x, p_y)$ nor $(k_x, k_y)$.

## 输出格式

In the first and only line of the standard output one integer should be written, namely the square of the frogshold distance. If the frog cannot avoid leaping directly on some scarefrog the result is 0.

## 样例

### 样例输入 #1
```
5 5
1 1 5 5
2
3 3
4 2
```
### 样例输出 #1
```
4
```


---

---
title: "[POI 2009] BAJ-The Walk of Bytie-boy"
layout: "post"
diff: 省选/NOI-
pid: P3485
tag: ['动态规划 DP', '2009', 'POI（波兰）', 'Special Judge', '广度优先搜索 BFS']
---
# [POI 2009] BAJ-The Walk of Bytie-boy
## 题目背景

[English Edition](/paste/9lmt83m9)
## 题目描述

给出一张 $n$ 个点 $m$ 条边的有向图，每条边上有一个字母，并给出一个整数 $d$ 和一个序列 $s_1, s_2, \dots, s_d$。  

你需要对每一个 $i(1\le i<n)$ 求出一条从 $s_i$ 到 $s_{i+1}$ 的最短路径满足这条路径上的边上的字母连起来后是回文的。  

不保证每个点最多只在 $s$ 中出现一次。
## 输入格式

第一行两个整数 $n, m$。

之后 $m$ 行，每行两个整数 $x_i, y_i$ 与一个字母 $c_i$，表示有一条从 $x_i$ 到 $y_i$ 的边，这条边上的字母是 $c_i$。

之后一行一个整数 $d$。

之后一行 $d$ 个整数， 表示序列 $s$。
## 输出格式

输出共 $d-1$ 行，第 $i$ 行输出一条从 $s_i$ 到 $s_{i+1}$ 的满足条件的路径。  

若不存在这样的路径，则输出 `-1`，否则输出这条路径上的所有字母。  

如果有多条满足条件的路径，任意输出一条即可。
## 样例

### 样例输入 #1
```
6 7
1 2 a
1 3 x
1 4 b
2 6 l
3 5 y
4 5 z
6 5 a
3
1 5 3

```
### 样例输出 #1
```
3 ala
-1

```
## 提示

对于 $100\%$ 的数据，$2\le n\le 400$，$1\le m\le 6\times10^4$，$1\le x_i,y_i\le n$，$2\le d\le100$，$1\le s_i\le n$。

同时保证不会出现重边与自环。


---

---
title: "[POI 2012] BEZ-Minimalist Security"
layout: "post"
diff: 省选/NOI-
pid: P3544
tag: ['2012', 'POI（波兰）', '广度优先搜索 BFS']
---
# [POI 2012] BEZ-Minimalist Security
## 题目描述

A map of Mafiatown's road network is given.

The network consists of intersections and bidirectional streets that connect them.

The streets cross only at the intersections, but they may lead through tunnels or flyovers.

Each pair of intersections is linked by at most one street.

At every intersection $v$ there is a police station manned by $p(v)$ policemen.

A street linking the intersections $u$ and $v$ is considered safe if there are at least $b(u,v)$ policemen in total in the two stations at the streets ends. Initially    $p(u)+p(v)\ge b(u,v)$ holds for every street.

However, due to an ongoing crisis the mayor Byteasar has ordained the Minimalist Security Act (MSA), which states that:

a certain number (which may be zero) of policemen is to be laid off from each police station        (we denote the number of policemen laid off from the station at the intersection $v$ by $z(v)$),                  after the layoff, the total number of the policemen at both ends of every street connecting some two intersections,        say $u$ and $v$, should equal $b(u,v)$ exactly, i.e.:

$p(u)-z(u)+p(v)-z(v)=b(u,v)$ These rules do not determine uniquely how many policemen are to be laid off.

Byteasar wonders what is the minimum and the maximum number of laid off policemen    (the sum of $z$ values over all intersections) that complies with aforementioned rules.
## 输入格式

In the first line of the standard input there are two integers, $n$ and $m$ ($1\le n\le 500\ 000$, $0\le m\le 3\ 000\ 000$), separated by a single space, that denote    the number of intersections and the number of streets in Mafiatown, respectively.

The intersections are numbered from 1 to $n$.

In the second line $n$ nonnegative integers separated by single spaces are given.

These are the numbers of policemen currently employed at successive stations, i.e., the values $p(1),p(2),\cdots,p(n)$($0\le p(i)\le 10^6$).

Each of the following $m$ lines describes a single bidirectional street. Such description consists of three integers,$u_i,v_i,b(u_i,v_i)$($1\le u_i,v_i\le n$,$u_i\ne v_i$,$0\le b(u_i,v_i)\le 10^6$), separated by single spaces, that denote respectively: the numbers of the intersections at the ends of the street and the minimum total number of policemen that have to man the stations at those intersections.

## 输出格式

If Byteasar's ordinance can be carried out, your program should print, on the standard output,    exactly one line with two integers separated by a single space.

The numbers should be the minimum and the maximum number of policemen that should be laid off    in order to carry out the ordinance.

If carrying out the ordinance is impossible, your program should print a single line containing    the word NIE (Polish for no).

## 样例

### 样例输入 #1
```
3 2
5 10 5
1 2 5
2 3 3
```
### 样例输出 #1
```
12 15
```
## 题目翻译

### 题目描述

**译自 POI 2012 Stage 3. Day 2「[Bezpieczeństwo minimalistyczne](https://szkopul.edu.pl/problemset/problem/aSbIC_LB4H-CGMYPEVue5jFw/site/?key=statement)」**

给定一张无向图，点有点权 $p(v)$，边有边权 $b(u,v)$，初始时保证对每条边有 $p(u) + p(v) \ge b(u,v)$。

现在需要减少一部分点的点权，使得对每条边都恰有 $p(u) + p(v) = b(u,v)$.

求整张图减少的点权和的最小值和最大值。

### 输入格式

第一行两个整数 $n$ 和 $m$（$1 \le n \le 500\ 000,0 \le m \le 3\ 000\ 000$），表示图的点数和边数。

接下来一行 $n$ 个非负整数 $p(1),p(2),\ldots,p(n) (0 \le p(i) \le 10^6)$，表示点权。

接下来 $m$ 行每行三个整数 $u_i, v_i, b(u_i, v_i)$（$1 \le u_i,v_i \le n,u_i \neq v_i,0 \le b(u_i,v_i) \le 10^6$），表示边和边权。

### 输出格式

如果存在符合条件的方案，输出一行两个整数，表示整张图减少的点权和的最小值和最大值。

如果不存在，输出 `NIE`.

### 数据范围

对于 $56\%$ 的数据有 $n \le 2000,m \le 8000$.

对于所有数据有 $1 \le n \le 500\ 000,0 \le m \le 3\ 000\ 000$.

翻译来自于 [LibreOJ](https://loj.ac/p/2702)。


---

---
title: "琪露诺的冰雪小屋"
layout: "post"
diff: 省选/NOI-
pid: P3693
tag: ['模拟', '洛谷原创', '枚举', '广度优先搜索 BFS', '连通块']
---
# 琪露诺的冰雪小屋
## 题目背景

琪露诺有一片正方形的雪地，她想在上面盖一栋小冰屋。

## 题目描述

琪露诺偶然间得到了一片 $N\times N$ 大小的正方形的雪地，她想在上面盖一栋冰雪小屋。

但调皮的⑨才不会认真地收集冰块呢，她要在这片土地上使用冰雪弹幕来制造冰砖，然后一块一块地搭起一个房子。

琪露诺制造冰砖的方式是这样的：她会站在某个方格上，然后向上，下，左，右，左上，左下，右上，右下这八个方向之一发射强力的冰雪弹幕，弹幕能影响到该方向一条直线上一定的距离以内的所有方格。

地面的每个方格都有一个冷冻度，初始为 $0$。被冰雪弹幕影响一次，冷冻度 $+1$，冷冻度的上限为 $4$。

在发射弹幕的间隙中，琪露诺会来到所有冷冻度为 $4$ 的格子，把那里的雪堆到一起，制作一个冰砖（大小为 $1\times1\times1$ 方格），并且将冷冻度重新归零。

琪露诺会拿着这些冰砖来盖房子。这个房子的长度、宽度和坐落位置她在一开始就已经规划好了，但她并不愿意提早确定房子的高度。

琪露诺是这样计划的：这个房子外观上看起来是一个长方体。

她会先盖起这个房子的四面墙（厚度为 $1$ 个方格），并在贴近地面的位置（废话）留一个宽度和高度分别为 $1$ 和 $2$ 的空位不放冰砖，作为房门。（显然，门无法开在墙的拐角处，但可以紧贴拐角）。

在她喜欢的时候，她会结束四面墙的建造，并一次性在墙顶部盖上一个厚度为 $1$ 方格的屋顶，使房子成为一个空心有顶的长方体。

计划已经非常充分了，但琪露诺还是不放心，所以她想请你帮她写一个程序，来随时提醒着她别出什么差错。这个程序需要具备的功能将在下文详细介绍。

----------------------
雪地由 $N$ 行 $N$ 列，$N\times N$ 个方格组成。（下标从 $0$ 开始，也就是说，存在第 $0$ 行第 $0$ 列，但不存在第 $N$ 行第 $N$ 列）每个方格都有一个冷冻度,范围 $[0,4]$，初始为 $0$。注意，空间是三维的，而冷冻度只是地面的属性。

琪露诺想将房子的左上角放在第 $H_R$行，$H_C$ 列（外墙也是房子的一部分，因此左上角位置不应该是房子的内部,而是外墙,并且是墙的拐角）。

这个房子的长度（平行于每列）是 $H_X$，宽度（平行于每行）是 $H_Y$，包含墙。保证房子所占空间不会超出雪地的范围。

除了最后搭建屋顶，琪露诺只会在高度 $[0,H_M-1]$ 放置冰砖。

一开始，琪露诺一个冰砖也没有。
在以下的介绍中，我们用俯视图来作示意：
```plain
0000
0000
4x90
0x01
```
数字代表当前该格子的冷冻度。如果位置紧贴地面（高度为 $0$）的地方放上了冰砖，那么用字母 $x$ 表示。

如果紧贴地面的位置没有冰砖，但是位置正上方的高空存在冰砖，那么仍然用数字表示地面的冷冻度，但这个数字会增加 $5$。即如果在示意图中看到了一个数字 $t\ge5$，表示该位置地面是空的，但高处有冰砖，且地面的冷冻度为 $t-5$。

第一个操作：`ICE_BARRAGE R C D S`  
---------------
表示琪露诺站在第 $R$ 行 $C$ 列的位置，朝着方向 $D$ 发射了一个强度为 $S$ 的弹幕。  
$R,C,D,S\in\mathbf{Z},0\le D\le7,0\le R,C,S<N$。  
方向编号 $0$ 表示上 $(R-1,C)$，$1$ 表示左上 $(R-1,C-1)$，   
$2$ 表示左 $(R,C-1)$，$3$ 表示左下 $(R+1,C-1)$，  
$4$ 表示下 $(R+1,C)$，$5$ 表示右下 $(R+1,C+1)$，  
$6$ 表示右 $(R,C+1)$，$7$ 表示右上 $(R-1,C+1)$。  
强度为 $S$ 的弹幕，可以使“处在发射方向直线上，距离琪露诺不超过 $S$ 格的所有格子（包括她站的格子）”的冷冻度都 $+1$。有以下几种特殊情况：

1. 如果某个格子冷冻度为 $4$，那么该格子冷冻度不变。
2. 如果弹幕所经路途上，有一个位置的地面上（高度为 $0$）已经放了冰砖（就是弹幕撞上了琪露诺已经盖了一半的房子），那么弹幕将被阻挡，无法影响到冰砖所在的格子以及冰砖后面被挡住的格子。
3. 弹幕超出雪地的部分忽略不计。

对于这个操作，需要如下输出一行：`CIRNO FREEZED k BLOCK(S)`  
如果这个弹幕将某个方格的冷冻度成功增加了 $1$，那么认为这个弹幕冻住了该方格。

`k` 表示这个弹幕总共冻住了多少方格。

如图：发射弹幕前地图如下：
```plain
00000
00000
00000
000x0
00000
```
执行操作 `ICE_BARRAGE 1 1 5 4`，地图变为：
```plain
00000
01000
00100
000x0
00000
```
输出：`CIRNO FREEZED 2 BLOCK(S)`  
解释：琪露诺站在第一行第一列，面对右下角发射了一个强度为 $4$ 的弹幕，但弹幕被 `x` 所阻挡，只能影响到 `x` 之前的格子。

第二个操作：`MAKE_ICE_BLOCK`  
-------------------------
琪露诺走遍地图上所有冷冻度为 $4$ 的方格，每个方格可以收集一个冰砖，然后将它们的冷冻度归零。 

对于这个操作，你需要给出如下输出一行：`CIRNO MADE x ICE BLOCK(S),NOW SHE HAS y ICE BLOCK(S)`  
表示琪露诺制造了 $x$ 个冰砖，目前她有 $y$ 个冰砖。  
比如琪露诺一开始有 $0$ 个冰砖，并且状态如下：
```plain
0xxx
0x4x
0x9x
0400
```
执行操作 `MAKE_ICE_BLOCK` 后变为
```plain
0xxx
0x0x
0x5x
0000
```
输出：`CIRNO MADE 3 ICE BLOCK(S),NOW SHE HAS 3 ICE BLOCK(S)`  
在这个示例中，房子已经完成了一部分，`x` 表示墙，`9` 这个位置地面没有冰砖，但高处有（可以猜出是门）。房间内唯一一块空地、门的位置，以及房间外的一个位置的冷冻度都达到了 $4$，因此可以收集到 $3$ 块冰砖，收集后将三个位置冷冻度都归零。

第三个操作：`PUT_ICE_BLOCK R C H` 
-----------------
表示在第 $R$ 行，第 $C$ 列，高度为 $H$ 的地方放一个冰砖。$0\le R,C<N,0\le H<H_M$。

贴近地面的位置高度为 $0$。如果冰砖放置成功，那么琪露诺库存的冰砖数量将减 $1$。

如果放置的位置贴近地面，该位置冷冻度立即归 $0$。

有以下几种情况，序号越小优先级越高，并且只能满足一种情况。

如果满足 $1$ 的话就忽视后面的，不满足 $1$ 的前提下才可能满足 $2\cdots\cdots$ 以此类推。

1. 琪露诺目前没有任何冰砖，无法放置。这种情况下你需要输出：`CIRNO HAS NO ICE_BLOCK`
2. 冰砖将放在半空中，无法依附其他任何冰砖，或者目标位置已有冰砖了。  
这种情况下你需要输出一行：`BAKA CIRNO,CAN'T PUT HERE`，并无视此次操作，不做任何工作。
3. 冰砖放在了规划建造房子的区域之外，即
$R<H_R$ 或 $R>H_R+H_x-1$  
或 $C<H_C$ 或 $C>H_C+H_Y-1$。请输出一行：`CIRNO MISSED THE PLACE`  
尽管琪露诺放错了地方，但你并不能阻止她放置这个冰砖。  
4. 冰砖留在了房子的内部，本应留空的地方被占用了，即  
$H_R+1\le R\le H_R+H_X-2$ 且 $H_C+1\le C\le H_C+H_Y-2$  
在屋顶的高度固定下来前，我们将所有满足上式的情况都认为是放在了房屋内部。  
请输出一行：`CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE`  
尽管琪露诺放错了地方，但你并不能阻止她放置这个冰砖。
5. 冰砖放在了正确的位置（不必考虑是否堵住了留给门的地方）  
请输出一行：`CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS x ICE_BLOCK(S)`  
`x` 表示放过这块冰砖后琪露诺剩余的冰砖。

第四个操作：`REMOVE_ICE_BLOCK R C H` 
---------
表示取走第 $R$ 行，第 $C$ 列，高度为 $H$ 处的冰砖。  
有以下几种情况，序号越小优先级越高，并且只能满足一种情况。

如果满足 $1$ 的话就忽视后面的，不满足 $1$ 的前提下才可能满足 $2\cdots\cdots$ 以此类推。

1. 目标位置没有冰砖，输出一行：`BAKA CIRNO,THERE IS NO ICE_BLOCK`
2. 目标位置有冰砖，并且在这个冰砖被移走后，至少有一个冰砖形成了一个悬空的块。  
如下面的“侧视图”，`x` 表示冰砖，`0` 表示空位。
```plain
xxxx
x000
x000
x000
```
$\ \ $在移走左上角的冰砖后，第一行右边三个冰砖没有了依靠，形成了一个悬空的连通块，就属于这种情况。  
$\ \ $这个冰砖将成功移走，琪露诺的冰砖库存将会 $+1$。并且所有的悬空连通块都会掉下来摔碎并消失  
$\ \ $（既不会进入冰砖库存，也不会在地面上留有任何痕迹）。  
$\ \ $输出一行：`CIRNO REMOVED AN ICE_BLOCK,AND k BLOCK(S) ARE BROKEN`，`k` 表示摔碎的冰砖数量。  
3. 琪露诺挪走了冰砖，并且其他冰砖不受任何影响。    
$\ \ \ $琪露诺的冰砖库存 $+1$，输出一行：`CIRNO REMOVED AN ICE_BLOCK`
    
第五个操作：`MAKE_ROOF` 
--------
这个操作只会出现一次，并且只会作为最后一个操作。  
这个操作表明琪露诺已经完成了冰雪小屋的四墙，只剩屋顶了！  

一般情况下，琪露诺将放置最后的 $H_X\times H_Y$ 个冰砖，把它们放置在墙壁最高的高度 $+1$ 的那一层，  
形成一个屋顶。然后她移除所有多余的冰砖，接下来补好所有残缺的墙壁。

你需要按顺序来执行整个过程，一旦遇到某种用 $\bullet$ 标识的特殊情况，则执行完该情况后退出流程。

在特殊情况之间所描述的均为一般情况，只要之前没有因为满足某种特殊情况而退出流程，均认为满足了一般情况。

首先，琪露诺将会一次性放置最多 $H_X\times H_Y$ 个冰砖来建造屋顶。

为什么是最多呢？请注意一点：如果之前错误放置在房子内部的冰砖恰好充当了屋顶的一部分，那么就不用在这个位置再放冰砖了。并且，所有比屋顶高的冰砖在之后将视为错误放置在了房子外部。

注意，放屋顶的时候可能会触及到高度为 $H_M$ 的那个平面。

建造屋顶前后将会碰到两种特殊情况：
- 琪露诺剩余的冰砖不足以建造屋顶。输出一行：`SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF`
- 墙壁的最高高度小于 $2$ 个方格，或者内部有效空间小于两个方格。  
墙壁所在的一圈不算内部空间。计算内部有效空间时请忽视错误放置的冰砖，因为它们将来要被移除。  
输出一行：`SORRY CIRNO,HOUSE IS TOO SMALL`

（特殊情况结束）

此后，我们认为琪露诺已经造好了屋顶，接下来该移除所有多余冰砖了。在移除过程中，琪露诺会尽可能让更少的冰砖摔碎。如果墙壁上某个冰砖因为移走了多余的冰砖而将要摔碎，那么她会先拆掉墙壁上的那个冰砖，然后在填补墙壁残缺时重新补回来（显然，这种行为不会影响到墙壁有无残缺的定性，但可以少损失一个冰砖）。她不会故意拆掉一个处在墙壁上且不会摔碎的冰砖。  
输出两行：  
`K1 ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED`  
`K2 ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED`  
`K1`表示房子内部错误放置的冰砖数量，`K2`表示房子外部错误放置的冰砖数量。

将有可能遭遇一种特殊情况：
- 琪露诺移除了所有多余的冰砖，但在移除过程中，屋顶塌陷了。  
输出一行：`SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS`

（特殊情况结束）

此后，我们认为琪露诺已经移除了所有多余的冰砖，接下来该填补墙壁的残缺了。

墙壁有残缺的定义是：除了宽为 $1$，高为 $2$ 的门以外，
在房子内部看外面还能看到其他缺口。

如果某个空位将来要作为门的一部分，则不属于残缺。并且房子只能有一个门。

如果墙壁没有残缺，则不要填补，否则需要填补。你需要记下墙壁是否有残缺，之后会用到。

填补的策略是：使用尽可能少的冰砖，在正确的位置填补墙壁，使房屋的状态不满足墙壁有残缺的定义（即不能放置多余的冰砖，通过遮挡视线来达到目的）。在此定义下，**大多数**情况我们无需考虑四角的柱子是否完整，因为在房间里看不到。

将有可能遭遇一种特殊情况：
- 琪露诺剩余的冰砖不足以填补墙壁的残缺。  
输出一行：`SORRY CIRNO,NOT ENOUGH ICE_BLOCKS TO FIX THE WALL`

（特殊情况结束）

此后，我们认为房子被成功建成了，这时你需要输出几行内容来对房子进行评价。

首先输出这么一行来庆祝房子的建成：`GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE`  
1. 在贴近地面的位置找不到一个宽度为 $1$，高度为 $2$ 的位置留给门。  
	输出一行：`HOUSE HAS NO DOOR`，然后琪露诺会尽可能利用墙壁上的残缺来开一个门。  
    否则，输出一行：`DOOR IS OK`
2. 接下来输出一行表示填补之前墙壁的完整程度  
	2.1. 在之前的记录中，墙壁不完整而需要修补。输出：`WALL NEED TO BE FIXED`  
    2.2. 在之前的记录中，墙壁完整而无需修补。输出：`WALL IS OK`  
3. 接下来一行表示四角的完整程度。  
	如果四个角的柱子有不完整的地方，就输出：`CORNER NEED TO BE FIXED`  
    在这种情况下，如果琪露诺剩余的冰砖足够修复拐角的空缺，那么她直接会修复这个空缺。  
    如果不够的话，她会再多收集几个冰砖，数量恰好修复这个空缺，然后修复这个空缺。  
    否则，输出：`CORNER IS OK`
    
接下来，输出一行：`CIRNO FINALLY HAS k ICE_BLOCK(S)`  
`k` 表示琪露诺最后剩余的冰砖的数量。

最后，如果在之前的记录中，墙壁完整无缺，没有一个位置需要填补。房子内外都无任何多余的方块，没有一个位置需要移除。没有出现房子没门的情况，房子四角的柱子也在造屋顶前完全造好，而不是通过修补完善的。并且门恰好开在了某面墙的正中央（如果长度为偶数，中间的两个都算），输出一行：   
`CIRNO IS PERFECT!`
## 输入格式

第一行一个正整数 $N$，表示雪地的大小。

第二行一个正整数$H_M$，表示琪露诺放置方块的最大高度。

第三行四个正整数 $H_R,H_C,H_X,H_Y$，表示房子左上角位置的行列坐标，房子的长度以及宽度。

第四行一个正整数 $M$，表示操作的数量。

接下来 $M$ 行，每行表示一个操作，输入格式见题目描述。
## 输出格式

在题目描述中已经介绍。

## 样例

### 样例输入 #1
```
8
10
4 0 4 4
63
ICE_BARRAGE 2 1 1 3
ICE_BARRAGE 0 1 3 1
MAKE_ICE_BLOCK
PUT_ICE_BLOCK 3 2 0
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 2 0 6 7
ICE_BARRAGE 3 0 6 7
ICE_BARRAGE 4 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 4 0 0
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 3 0 1
REMOVE_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 4 2 0
PUT_ICE_BLOCK 6 1 0
PUT_ICE_BLOCK 4 3 0
PUT_ICE_BLOCK 5 3 0
PUT_ICE_BLOCK 6 3 0
PUT_ICE_BLOCK 7 3 0
ICE_BARRAGE 0 1 4 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
REMOVE_ICE_BLOCK 6 1 0
PUT_ICE_BLOCK 5 0 0
PUT_ICE_BLOCK 6 0 0
PUT_ICE_BLOCK 7 0 0
PUT_ICE_BLOCK 7 1 0
PUT_ICE_BLOCK 7 2 0
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 5 0 1
PUT_ICE_BLOCK 6 0 1
PUT_ICE_BLOCK 7 0 1
PUT_ICE_BLOCK 7 1 1
PUT_ICE_BLOCK 7 2 1
PUT_ICE_BLOCK 7 3 1
PUT_ICE_BLOCK 6 3 1
PUT_ICE_BLOCK 5 3 1
PUT_ICE_BLOCK 4 3 1
PUT_ICE_BLOCK 4 2 1
MAKE_ROOF

```
### 样例输出 #1
```
CIRNO FREEZED 2 BLOCK(S)
CIRNO FREEZED 2 BLOCK(S)
CIRNO MADE 0 ICE BLOCK(S),NOW SHE HAS 0 ICE BLOCK(S)
CIRNO HAS NO ICE_BLOCK
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO FREEZED 0 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 8 ICE BLOCK(S)
BAKA CIRNO,CAN'T PUT HERE
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 7 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 6 ICE_BLOCK(S)
CIRNO MISSED THE PLACE
CIRNO REMOVED AN ICE_BLOCK,AND 1 BLOCK(S) ARE BROKEN
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 5 ICE_BLOCK(S)
CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 3 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 2 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 1 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 0 ICE_BLOCK(S)
CIRNO FREEZED 6 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 8 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 16 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 24 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 32 ICE BLOCK(S)
CIRNO REMOVED AN ICE_BLOCK
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 32 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 31 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 30 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 29 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 28 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 27 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 26 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 25 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 24 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 23 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 22 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 21 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 20 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 19 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 18 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 17 ICE_BLOCK(S)
0 ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED
0 ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED
GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE
DOOR IS OK
WALL IS OK
CORNER IS OK
CIRNO FINALLY HAS 1 ICE_BLOCK(S)
CIRNO IS PERFECT!

```
## 提示

共分为 $6$ 个 **Subtask**，每个 **Subtask** 的数据都满足一定条件，并且同时满足序号更大的 **Subtask** 的条件。  
如 **Subtask #0** 同时满足 **Subtask #0~5** 的条件。  
每一个 **Subtask** 的得分取所有测试点的最低分。

**Subtask #0** $20\%$  
琪露诺只想玩玩冰雪弹幕，她不会放置任何冰砖，也不会盖房子(即只有操作一和操作二)。  


**Subtask #1** $10\%$  
琪露诺不会移除已经放置的冰砖。

**Subtask #2** $20\%$  
琪露诺很有信心，她将在没有 `MAKE_ROOF` 的情况下建造她的冰屋(这种情况下，放置方块的高度仍然会小于 $H_M$ 且没有 `MAKE_ROOF` 操作)。

**Subtask #3** $20\%$  
琪露诺在移除方块时会谨慎考虑,不会造成任何冰砖摔落。`MAKE_ROOF` 操作移除多余冰砖时，也不会造成屋顶塌陷。

**Subtask #4** $20\%$  
琪露诺不喜欢把门开到四角的柱子旁边(数据保证在所有可能作为门的墙壁空缺中，有一种可能使得门不紧贴四角的柱子)。 

**Subtask #5** $10\%$  
$4\le N\le 16$，$5\le H_M\le 20$，$10\le M\le 10^3$，保证不属于冰屋范围内的所有空地至多构成一个连通块。

注意：判断墙壁是否有残缺时，候选的开门位如果被方块堵住，在当时还未被清空。"能看到残缺"以当时的情况作为判断依据。


---

---
title: "[六省联考 2017] 寿司餐厅"
layout: "post"
diff: 省选/NOI-
pid: P3749
tag: ['2017', '各省省选', '广度优先搜索 BFS', '深度优先搜索 DFS', '最小割']
---
# [六省联考 2017] 寿司餐厅
## 题目描述

Kiana 最近喜欢到一家非常美味的寿司餐厅用餐。

每天晚上，这家餐厅都会按顺序提供 $n$ 种寿司，第 $i$ 种寿司有一个代号 $a_i$ 和美味度 $d_{i, i}$，不同种类的寿司有可能使用相同的代号。每种寿司的份数都是无限的，Kiana 也可以无限次取寿司来吃，但每种寿司每次只能取一份，且每次取走的寿司必须是按餐厅提供寿司的顺序连续的一段，即 Kiana 可以一次取走第 $1, 2$ 种寿司各一份，也可以一次取走第 $2, 3$ 种寿司各一份，但不可以一次取走第 $1, 3$ 种寿司。

由于餐厅提供的寿司种类繁多，而不同种类的寿司之间相互会有影响：三文鱼寿司和鱿鱼寿司一起吃或许会很棒，但和水果寿司一起吃就可能会肚子痛。因此，Kiana 定义了一个综合美味度 $d_{i, j} \ (i < j)$，表示在一次取的寿司中，如果包含了餐厅提供的从第 $i$ 份到第 $j$ 份的所有寿司，吃掉这次取的所有寿司后将获得的额外美味度。由于取寿司需要花费一些时间，所以我们认为分两次取来的寿司之间相互不会影响。注意在吃一次取的寿司时，不止一个综合美味度会被累加，比如若 Kiana 一次取走了第 $1, 2, 3$ 种寿司各一份，除了 $d_{1, 3}$ 以外，$d_{1, 2}, d_{2, 3}$ 也会被累加进总美味度中。

神奇的是，Kiana 的美食评判标准是有记忆性的，无论是单种寿司的美味度，还是多种寿司组合起来的综合美味度，在计入 Kiana 的总美味度时都只会被累加一次。比如，若 Kiana 某一次取走了第 $1, 2$ 种寿司各一份，另一次取走了第 $2, 3$ 种寿司各一份，那么这两次取寿司的总美味度为 $d_{1, 1} + d_{2, 2} + d_{3, 3} + d_{1, 2} + d_{2, 3}$，其中 $d_{2, 2}$ 只会计算一次。

奇怪的是，这家寿司餐厅的收费标准很不同寻常。具体来说，如果 Kiana 一共吃过了 $c \ (c > 0)$ **种**代号为 $x$ 的寿司，则她需要为这些寿司付出 $mx^2 + cx$ 元钱，其中 $m$ 是餐厅给出的一个常数。

现在 Kiana 想知道，在这家餐厅吃寿司，自己能获得的总美味度（包括所有吃掉的单种寿司的美味度和所有被累加的综合美味度）减去花费的总钱数的最大值是多少。由于她不会算，所以希望由你告诉她。
## 输入格式

第一行包含两个正整数 $n, m$，分别表示这家餐厅提供的寿司总数和计算寿司价格中使用的常数。  
第二行包含 $n$ 个正整数，其中第 $k$ 个数 $a_k$ 表示第 $k$ 份寿司的代号。  
接下来 $n$ 行，第 $i$ 行包含 $n - i + 1$ 个整数，其中第 $j$ 个数 $d_{i, i+j-1}$ 表示吃掉寿司能获得的相应的美味度，具体含义见问题描述。
## 输出格式

输出共一行包含一个正整数，表示 Kiana 能获得的总美味度减去花费的总钱数的最大值。
## 样例

### 样例输入 #1
```
3 1
2 3 2
5 -10 15
-10 15
15
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
5 0
1 4 1 3 4
50 99 8 -39 30
68 27 -75 -32
70 24 72
-10 81
-95
```
### 样例输出 #2
```
381
```
### 样例输入 #3
```
10 1
5 5 4 4 1 2 5 1 5 3
83 91 72 29 22 -5 57 -14 -36 -3
-11 34 45 96 32 73 -1 0 29
-48 68 44 -5 96 66 17 74
88 47 69 -9 2 25 -49
86 -9 -77 62 -10 -30
2 40 95 -74 46
49 -52 2 -51
-55 50 -44
72 22
-68
```
### 样例输出 #3
```
1223
```
## 提示

### 样例解释 1

在这组样例中，餐厅一共提供了 $3$ 份寿司，它们的代号依次为 $a_1 = 2, a_2 = 3, a_3 = 2$，计算价格时的常数 $m = 1$。

在保证每次取寿司都能获得新的美味度的前提下，Kiana 一共有 $14$ 种不同的吃寿司方案。以下列出其中几种：
1. Kiana 一个寿司也不吃，这样她获得的总美味度和花费的总钱数都是 $0$，两者相减也是 $0$；
2. Kiana 只取 $1$ 次寿司，且只取第 $1$ 个寿司，即她取寿司的情况为 $\{[1, 1]\}$，这样获得的总美味度为 $5$，花费的总钱数为 $1 \times 2^2 + 1 \times 2 = 6$，两者相减为 $-1$；
3. Kiana 取 $2$ 次寿司，第一次取第 $1, 2$ 个寿司，第二次取第 $2, 3$ 个寿司，即她取寿司的情况为 $\{[1, 2], [2, 3]\}$，这样获得的总美味度为 $5 + (-10) + 15 + (-10) + 15 = 15$，花费的总钱数为 $(1 \times 2^2 + 2 \times 2) + (1 \times 3^2 + 1 \times 3) = 20$，两者相减为 $-5$；
4. Kiana 取 $2$ 次寿司，第一次取第 $1$ 个寿司，第二次取第 $3$ 个寿司，即她取寿司的情况为 $\{[1, 1], [3, 3]\}$，这样获得的总美味度为 $5 + 15 = 20$，花费的总钱数为 $1 \times 2^2 + 2 \times 2 = 8$，两者相减为 $12$。

在 $14$ 种方案中，惟一的最优方案是列出的最后一种方案，这时她获得的总美味度减去花费的总钱数的值最大为 $12$。

### 数据范围

对于所有数据，保证 $-500 \leq d_{i, j} \leq 500$。

数据的一些特殊约定如下表：

| Case # | $n$ | $a_i$ | $m$ | 附加限制 |
|:-:|:-:|:-:|:-:|:-:|
| 1 | $\leq 2$ | $\leq 30$ | $= 0$ | - |
| 2 | $\leq 2$ | $\leq 30$ | $= 1$ | - |
| 3 | $\leq 3$ | $\leq 30$ | $= 0$ | - |
| 4 | $\leq 3$ | $\leq 30$ | $= 1$ | - |
| 5 | $\leq 5$ | $\leq 30$ | $= 0$ | - |
| 6 | $\leq 5$ | $\leq 30$ | $= 1$ | - |
| 7 | $\leq 10$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 8 | $\leq 10$ | $\leq 30$ | $= 1$ | - |
| 9 | $\leq 15$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 10 | $\leq 15$ | $\leq 30$ | $= 1$ | - |
| 11 | $\leq 30$ | $\leq 1000$ | $= 0$ | 所有的 $a_i$ 相同 |
| 12 | $\leq 30$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 13 | $\leq 30$ | $\leq 1000$ | $= 0$ | - |
| 14 | $\leq 30$ | $\leq 1000$ | $= 1$ | - |
| 15 | $\leq 50$ | $\leq 1000$ | $= 0$ | 所有的 $a_i$ 相同 |
| 16 | $\leq 50$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 17 | $\leq 50$ | $\leq 1000$ | $= 0$ | - |
| 18 | $\leq 50$ | $\leq 1000$ | $= 1$ | - |
| 19 | $\leq 100$ | $\leq 1000$ | $= 0$ | - |
| 20 | $\leq 100$ | $\leq 1000$ | $= 1$ | - |


---

---
title: "[HEOI2015] 最短不公共子串"
layout: "post"
diff: 省选/NOI-
pid: P4112
tag: ['2015', '各省省选', '河北', '后缀自动机 SAM', 'O2优化', '广度优先搜索 BFS', '后缀数组 SA']
---
# [HEOI2015] 最短不公共子串
## 题目描述

在虐各种最长公共子串、子序列的题虐的不耐烦了之后，你决定反其道而行之。

下面给出一些定义：

- 一个串的“子串”指的是它的连续的一段，例如 `bcd` 是 `abcdef` 的子串，但 `bde` 不是。
- 一个串的“子序列”指的是它的可以不连续的一段，例如 `bde` 是 `abcdef` 的子串，但 `bdd` 不是。

下面，给两个小写字母串 $a, b$，请你计算：

1. $a$ 的一个最短的子串，它不是 $b$ 的子串。
2. $a$ 的一个最短的子串，它不是 $b$ 的子序列。
3. $a$ 的一个最短的子序列，它不是 $b$ 的子串。
4. $a$ 的一个最短的子序列，它不是 $b$ 的子序列。

## 输入格式

有两行，每行一个小写字母组成的字符串，分别代表 $a$ 和 $b$。

## 输出格式

输出 $4$ 行，每行一个整数，依次表示以上 $4$ 个问题的答案的长度。如果没有符合要求的答案，输出 $-1$。

## 样例

### 样例输入 #1
```
aabbcc
abcabc
```
### 样例输出 #1
```
2
4
2
4
```
### 样例输入 #2
```
aabbcc
aabbcc
```
### 样例输出 #2
```
-1
-1
2
-1
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $20$。
- 对于 $50\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $500$。
- 对于 $100\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $2000$。



---

---
title: "[NOI2006] 最大获利"
layout: "post"
diff: 省选/NOI-
pid: P4174
tag: ['2006', 'NOI', '网络流', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOI2006] 最大获利
## 题目描述

新的技术正冲击着手机通讯市场，对于各大运营商来说，这既是机遇，更是挑战。THU 集团旗下的 CS&T 通讯公司在新一代通讯技术血战的前夜，需要做太多的准备工作，仅就站址选择一项，就需要完成前期市场研究、站址勘测、最优化等项目。

在前期市场调查和站址勘测之后，公司得到了一共 $N$ 个可以作为通讯信号中转站的地址，而由于这些地址的地理位置差异，在不同的地方建造通讯中转站需要投入的成本也是不一样的，所幸在前期调查之后这些都是已知数据：建立第 $i$ 个通讯中转站需要的成本为 $P_i$（$1 \leq i \leq N$）。

另外公司调查得出了所有期望中的用户群，一共 $M$ 个。关于第 $i$ 个用户群的信息概括为 $A_i$，$B_i$ 和 $C_i$ ：这些用户会使用中转站 $A_i$ 和中转站 $B_i$ 进行通讯，公司可以获益 $C_i$。（$1 \leq i \leq M$，$1 \leq A_i, B_i \leq N$）

THU 集团的 CS&T 公司可以有选择的建立一些中转站（投入成本），为一些用户提供服务并获得收益（获益之和）。那么如何选择最终建立的中转站才能让公司的净获利最大呢？（净获利 = 获益之和 – 投入成本之和）

## 输入格式

输入文件中第一行有两个正整数 $N$ 和 $M$。

第二行中有 $N$ 个整数描述每一个通讯中转站的建立成本，依次为 $P_1 , P_2 , …,P_N$。

以下 $M$ 行，第 $i + 2$ 行的三个数 $A_i , B_i$ 和 $C_i$ 描述第 $i$ 个用户群的信息。

所有变量的含义可以参见题目描述。

## 输出格式

你的程序只要向输出文件输出一个整数，表示公司可以得到的最大净获利。

## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2 3
2 3 4
1 3 3
1 4 2
4 5 3
```
### 样例输出 #1
```
4
```
## 提示

样例：选择建立 $1,2,3$ 号中转站，则需要投入成本 $6$，获利为 $10$，因此得到最大收益 $4$。

$100\%$ 的数据中：$N \leq 5\,000$，$M \leq50\,000$，$0 \leq C_i \leq 100$，$0 \leq P_i  \leq 100$。



---

---
title: "[CQOI2018] 解锁屏幕"
layout: "post"
diff: 省选/NOI-
pid: P4460
tag: ['2018', '重庆', '各省省选', '广度优先搜索 BFS', '状压 DP']
---
# [CQOI2018] 解锁屏幕
## 题目背景

使用过 Android 手机的同学一定对手势解锁屏幕不陌生。 Android 的解锁屏幕由 $3 \times 3$ 个点组成，手指在屏幕上画一条线，将其中一些点连接起来，即可构成一个解锁图案。如下面三个例子所示：

![](https://cdn.luogu.com.cn/upload/pic/17556.png)
![](https://cdn.luogu.com.cn/upload/pic/17557.png)
![](https://cdn.luogu.com.cn/upload/pic/17558.png)
## 题目描述

画线时还需要遵循一些规则：
1. 连接的点数不能少于 $4$ 个。也就是说只连接两个点或者三个点会提示错误。
2. 两个点之间的联线不能弯曲。
3. 每个点只能“使用”一次，不可重复。这里的“使用”是指手指划过一个点，该点变绿。
4. 两个点之间的连线不能“跨过”另一个点，除非那个点之前已经被“使用”过。

对于最后一条规则，参见下图的解释。左边两幅图违反了该规则；而右边两幅图（分别为 $ 2 \rightarrow 4 \rightarrow 1 \rightarrow 3 \rightarrow 6$ 和 $ 6 \rightarrow 5 \rightarrow 4 \rightarrow 1 \rightarrow 9 \rightarrow 2$ ）则没有违反规则，因为在“跨过”点时，点已经被使用过了。

![](https://cdn.luogu.com.cn/upload/pic/17566.png)

现在工程师希望改进解锁屏幕，增减点的数目，并移动点的位置，不再是一个九宫格形状，但保持上述画线规则不变。

请计算新的解锁屏幕上，一共有多少满足规则的画线方案。
## 输入格式

输入第一行为一个整数 $n$ ，表示点的数目。

接下来 $n$ 行，每行两个空格分开的整数 $x_i$ 和 $y_i$ ，表示每个点的坐标。
## 输出格式

输出共一行，为题目所求方案数除以 $10^8+7$ 的余数。
## 样例

### 样例输入 #1
```
4
0 0
1 1
2 2
3 3
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
4
0 0
0 1
0 2
1 0
```
### 样例输出 #2
```
18
```
## 提示

#### 样例解释 1

设 $4$ 个点编号为 $1$ 到 $4$ ，方案有 $1 \rightarrow 2 \rightarrow 3 \rightarrow 4$ ， $2 \rightarrow 1 \rightarrow 3 \rightarrow 4$ ，  $3 \rightarrow 2 \rightarrow 1 \rightarrow 4$ ，  $2 \rightarrow 3 \rightarrow 1 \rightarrow 4$ 以及它们的镜像。

### 数据范围

- 对于 $30\%$ 的数据，$1 \le n \le 10$。
- 对于 $100\%$ 的数据，$-1000 \le x_i ,y_i \le 1000$，$ 1 \le n < 20$。各点坐标不相同。


---

---
title: "[NEERC 2015] Binary vs Decimal"
layout: "post"
diff: 省选/NOI-
pid: P6124
tag: ['高精度', '2015', '广度优先搜索 BFS', 'ICPC']
---
# [NEERC 2015] Binary vs Decimal
## 题目描述

一个正数 $A$，如果它只包含 `0` 或 `1`，且它转成二进制后的 $B$，$A$ 是 $B$ 的后缀，这个数就是我们所要的。

现在给出数字 $N$，求第 $N$ 个这样的数。
## 输入格式

一行一个数 $N$。
## 输出格式

一行一个数，第 $N$ 个数。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
10
```
### 样例输出 #2
```
1100
```
## 提示

$1 \le N \le 10^4$。

|原数|二进制|评论|
| :-----------: | :-----------: | :-----------: |
|$1$|$1$|√|
|$10$|$1010$|√|
|$11$|$1011$|√|
|$100$|$1100100$|√|
|$101$|$1100101$|√|
|$110$|$1101110$|√|
|$111$|$1101111$|√|
|$1000$|$1111101000$|√|
|$1001$|$1111101001$|√|
|$1010$|$1111110010$|×|
|$1011$|$1111110011$|×|
|$1100$|$10001001100$|√| 


---

---
title: "【模板】二分图最大权完美匹配"
layout: "post"
diff: 省选/NOI-
pid: P6577
tag: ['Special Judge', 'O2优化', '\ufeff基础算法', '广度优先搜索 BFS', 'KM算法', '其它技巧']
---
# 【模板】二分图最大权完美匹配
## 题目背景

> $\rm Love ~of ~my ~life$
>
> $\rm U~are~far~from~me$
> 
> $\rm U've ~ turned ~ me ~ on$
> 
> $\rm and ~ now ~ I ~ try ~ to ~ catch ~ up ~ with ~ you$
>
> $\rm Love ~ of ~ my ~ life ~ can't ~ you ~ see$
>
> $\rm I'll ~ always ~ try, ~ always ~ try$
>
> $\rm U ~ are ~ the ~ brightest ~ star ~ to ~ me$
> 
> $\rm No ~ matter ~ others ~ don't ~ know$
>
> $\rm what ~ it ~ means ~ to ~ me$
>
> ——  An adaptation of _Love of My Life_ by Queen


这是一道夹带私货的模板题。
## 题目描述

给定一张二分图，左右部均有 $n$ 个点，共有 $m$ 条带权边，且保证有完美匹配。

求一种完美匹配的方案，使得最终匹配边的边权之和最大。
## 输入格式

第一行两个整数 $n,m$，含义见题目描述。

第 $2\sim m+1$ 行，每行三个整数 $y,c,h$ 描述了图中的一条从左部的 $y$ 号结点到右部的 $c$ 号节点，边权为 $h$ 的边。
## 输出格式

**本题存在 Special Judge**。

第一行一个整数 $ans$ 表示答案。

第二行共 $n$ 个整数 $a_1,a_2,a_3\cdots a_n$，其中 $a_i$ 表示完美匹配下与**右部**第 $i$ 个点相匹配的左部点的编号。如果存在多种方案，请输出任意一种。
## 样例

### 样例输入 #1
```
5 7
5 1 19980600
4 2 19980587
1 3 19980635
3 4 19980559
2 5 19980626
1 2 -15484297
4 5 -17558732

```
### 样例输出 #1
```
99903007
5 4 1 3 2 

```
## 提示

#### 数据规模与约定
- 对于 $10\%$ 的数据，满足 $n\leq 10$。
- 对于 $30\%$ 的数据，满足 $n\leq 100$。
- 对于 $60\%$ 的数据，满足 $n\leq 500$，且保证数据随机 。
- 对于 $100\%$ 的数据，满足 $1\leq n\leq 500$，$1\leq m\leq n^2$，$-19980731\leq h \leq 19980731$ 。且保证没有重边。

数据由善于出锅的出题人耗时好久制造完成。

善良的杨村花提醒你，别忘了仔细观察一下边权范围哦~

善良的杨村花又提醒你，你的复杂度可能只是「看起来」很对哦~


---

---
title: "「SWTR-5」String"
layout: "post"
diff: 省选/NOI-
pid: P6652
tag: ['动态规划 DP', 'O2优化', '广度优先搜索 BFS', '哈希 hashing']
---
# 「SWTR-5」String
## 题目描述

小 A 有一个字符串 $t$。他可以进行以下操作：切掉 $t$ 的一个前/后缀，满足切掉的前/后缀为**切割后** $t$ 的子串。小 A 想得到字符串 $s$，请问他最少需要进行多少次操作。无解输出 $-1$。
## 输入格式

两行字符串分别表示 $t,s$。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
abbabb
ba
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
fxofoxxooffoxooo
fox
```
### 样例输出 #2
```
8
```
### 样例输入 #3
```
abcdefghijklmnopq
rstuvwxyzz
```
### 样例输出 #3
```
-1
```
### 样例输入 #4
```
ycxcy
cxy
```
### 样例输出 #4
```
-1
```
## 提示

「样例说明」

样例 $1$：$\texttt{abbabb}\to \texttt{abba}\to \texttt{bba}\to \texttt{ba}$。方案不唯一。

样例 $2$：$\texttt{fxofoxxooffoxooo}\to\texttt{xofoxxooffoxooo}\to\texttt{foxxooffoxooo}\to\texttt{xooffoxooo}\to\texttt{ffoxooo}\to\texttt{ffoxoo}\to\texttt{ffoxo}\to\texttt{ffox}\to\texttt{fox}$。方案不唯一。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 points）：$s=t$。
- Subtask 2（9 points）：$s$ 仅包含字母 $\texttt{a}$。
- Subtask 3（15 points）：$|t|\leq 100$。
- Subtask 4（17 points）：$|t|\leq 500$。
- Subtask 5（18 points）：$|t|\leq 1.5\times 10^3$。
- Subtask 6（15 points）：$|s|=4$，*数据随机。
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据：$1 \leq |s| \leq |t| \leq 5\times 10^3$，字符集 $\in[\texttt{a,z}]$。

*数据随机：$s,t$ 字符均随机，字符集 $\in[\texttt{a,c}]$。

**请注意常数优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) E。    
idea & solution：[Isaunoya](https://www.luogu.com.cn/user/96580) & [Alex_Wei](https://www.luogu.com.cn/user/123294)。


---

---
title: "[CCO 2021] Bread First Search"
layout: "post"
diff: 省选/NOI-
pid: P7832
tag: ['动态规划 DP', '线段树', '2021', 'CCO（加拿大）', '广度优先搜索 BFS']
---
# [CCO 2021] Bread First Search
## 题目描述

这个国家有 $n$ 个城市和 $m$ 条双向道路。

有一个人要游览这个国家，但他很讲究。他要求游览线路必须是一个 BFS（Bread First Search，面包优先搜索）序，必须访问每个城市各一次，且满足以下条件：

- 首个城市可以任选；
- 除了首个城市外，每个城市被访问前至少有一个相邻城市已经被访问过；
- 每个城市与首个城市的距离单调不降。其中两个城市的距离定义为它们路径边数的最小值。

这个人还有强迫症，一定要按照编号 $1 \sim n$ 的顺序将每个城市访问一次。为了使这条游览线路符合上述所有要求，政府需要新修若干条道路。请问最少需要新修多少条道路？
## 输入格式

第一行，两个整数 $n, m$；

接下来 $m$ 行，每行两个整数 $a, b$，表示这个国家的一条双向道路。
## 输出格式

一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
2 0
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
6 3
1 3
2 6
4 5
```
### 样例输出 #2
```
2
```
## 提示

#### 样例 #2 解释
一种符合要求的方式是，在城市 $1, 2$ 之间修一条路，在城市 $1, 4$ 之间修一条路。此时城市 $1$ 与城市 $1 \sim 6$ 的距离分别是 $0, 1, 1, 1, 2, 2$。
#### 数据范围
对于 $\frac{11}{32}$ 的数据，$1 \leq n \leq 200$；

对于 $\frac{5}{8}$ 的数据，$1 \leq n \leq 5 \times 10^3$；

对于 $100\%$ 的数据，$1 \leq n \leq 2 \times 10^5$，$0 \leq m \leq \min(2 \times 10^5, \frac{n(n - 1)}{2})$，$1 \leq a, b \leq n$，**保证没有重边和自环**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D2T2


---

---
title: "[COCI 2021/2022 #2] Hiperkocka"
layout: "post"
diff: 省选/NOI-
pid: P7966
tag: ['搜索', '2021', 'Special Judge', '广度优先搜索 BFS', '位运算', '构造', 'COCI（克罗地亚）']
---
# [COCI 2021/2022 #2] Hiperkocka
## 题目描述

给定一个 $n$ 维的超正方体。

将该超正方体抽象为一个含 $2^n$ 个结点的图，结点分别用序号 $0,1,\cdots,2^n-1$ 表示。两个结点 $x,y$ 联通，当且仅当 $x \oplus y$ 为 $2$ 的整数幂。

现需将若干棵含有 $n$ 条边的树 $T$ 放置于该超正方体中。结点分别用序号 $0,1,\cdots,n$ 表示。给定每棵树的 $n$ 条边所连接的点的序号，则每一棵树需满足下列条件：

- 每个树上的结点都与超正方体的其中一个结点一一对应
- 每个结点互不相同
- 每一棵树的每一条边所连接的两个结点在超正方体中所对应的两个结点在超正方体中有边相连（即对应的两个结点的异或值为 $2$ 的整数幂）
- 每两棵树的边集在超正方体中所对应的边集不交，即超正方体中的每条边最多包含于一棵树中

请给定一种放置方案，使得放在超正方体中的每一棵树都符合题意。
## 输入格式

第一行一个正整数 $n$，表示超正方体的维数。

接下来的 $n$ 行，每行两个整数 $x,y$，表示在每棵树 $T$ 中，有一条连接 $x,y$ 的边。
## 输出格式

第一行输出放置的树的数目 $k$。

接下来的 $k$ 行，每行输出 $n+1$ 个整数，表示这棵树的对应结点在超正方体中的结点编号。
## 样例

### 样例输入 #1
```
1
0 1
```
### 样例输出 #1
```
1
0 1
```
### 样例输入 #2
```
2
0 1
1 2
```
### 样例输出 #2
```
2
0 1 3
0 2 3
```
### 样例输入 #3
```
3
0 1
0 2
0 3
```
### 样例输出 #3
```
4
0 1 2 4
3 1 2 7
5 1 4 7
6 2 4 7
```
## 提示

**【样例 3 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/58a0p43i.png)

**【数据规模与约定】**

对于 $100\%$ 的数据，$1 \le n \le 16$，$0 \le x,y \le n$，$x \neq y$。

**【提示与说明】**

如果程序正确地放置了 $k$ 棵树，则每个测试点的得分为 $f(k) \cdot 110$，其中：

$$f(k)=\begin{cases}
\dfrac{0.7k}{2^{n-1}} & (k \lt 2^{n-1}) \cr
1 & (k=2^{n-1}) \cr
\end{cases}$$

若放置方式错误，则该测试点得分为 $0$。可以证明，总存在一种方式可以放置 $2^{n-1}$ 棵树。

因评分方式特殊，本题启用自行编写的 [Special Judge](https://www.luogu.com.cn/discuss/738608)，欢迎大家 hack。

**题目译自 [COCI 2021-2022](https://hsin.hr/coci/) [CONTEST #2](https://hsin.hr/coci/contest2_tasks.pdf) _Task 3 Hiperkocka_。**

**本题在 COCI 原题中满分 $110$，但由于为了计算方便，将满分修改为 $26 \times 5=130$。**


---

---
title: "[省选联考 2023] 过河卒"
layout: "post"
diff: 省选/NOI-
pid: P9169
tag: ['博弈论', '各省省选', '2023', 'O2优化', '广度优先搜索 BFS', '拓扑排序']
---
# [省选联考 2023] 过河卒
## 题目背景

棋盘上有一个过河卒，需要走到底线。卒行走的规则是可以向左移动一格，向右移动一格或者向前移动一格。同时在棋盘上有两个另一方的棋子，需要拦截这个卒走到底线。这两个棋子的走法和帅一致，可以走到前后左右四个方向上相邻的格子。因此本题可以称为“帅拦过河卒”。
## 题目描述

有一个 $n$ 行 $m$ 列的棋盘。我们用 $(i,j)$ 表示第 $i$ 行第 $j$ 列的位置。棋盘上有一些 障碍，还有一个黑棋子和两个红棋子。

游戏的规则是这样的: 红方先走，黑方后走，双方轮流走棋。红方每次可以选择一个红棋子，向棋盘的相邻一格走一步。具体而言，假设红方选择的这个棋子位置在 $(i,j)$，那么它可以走到 $(i-1,j),(i+1,j),(i,j-1),(i,j+1)$ 中的一个，只要这个目的地在棋盘内且没有障碍且没有红方的另一个棋子。

黑方每次可以将自己的棋子向三个方向之一移动一格。具体地，假设这个黑棋子位置在 $(i,j)$，那么它可以走到 $(i-1,j),(i,j-1),(i,j+1)$ 这三个格子中的一个，只要这个目的地在棋盘内且没有障碍。

在一方行动之前，如果发生以下情况之一，则立即结束游戏，按照如下的规则判断胜负（列在前面的优先）：

- 黑棋子位于第一行。此时黑方胜。

- 黑棋子和其中一个红棋子在同一个位置上。此时进行上一步移动的玩家胜。

- 当前玩家不能进行任何合法操作。此时对方胜。

现在假设双方采用最优策略，不会进行不利于自己的移动。也就是说:

- 若存在必胜策略，则会选择所有必胜策略中，不论对方如何操作，本方后续获胜所需步数最大值最少的操作。
- 若不存在必胜策略，但存在不论对方如何行动，自己都不会落败的策略，则会选择任意一种不败策略。
- 若不存在不败策略，则会选择在所有策略中，不论对方如何操作，对方后续获胜所需步数最小值最大的操作。

如果在 $100^{100^{100}}$ 个回合之后仍不能分出胜负，则认为游戏平局。请求出游戏结束时双方一共移动了多少步，或者判断游戏平局。
## 输入格式

**本题有多组测试数据**。

输入的第一行包含两个整数 $\text{id},T$，分别表示测试点编号和数据组数。特别地，样例的 $\text{id}$ 为 $0$。

接下来包含 $T$ 组数据，每组数据的格式如下：

第一行包含两个正整数 $n,m$，表示棋盘的行数和列数。

接下来 $n$ 行，每行包含一个长度为 $m$ 的字符串，其中第 $i$ 行的第 $j$ 个字符表示棋盘上 $(i,j)$ 这个位置的状态。

在这些字符中：$\texttt{'.'}$ 表示空位；$\texttt{'\#'}$ 表示障碍物；$\texttt{'X'}$ 表示黑棋；$\texttt{'O'}$ 表示红棋。

保证黑棋恰好有一个，红棋恰好有两个，且黑棋不在第一行。
## 输出格式

对于每组数据，输出一行字符串。

如果游戏平局，请输出一行 $\texttt{"Tie"}$。

如果红方胜，请输出一行 $\texttt{"Red t"}$。其中 $\texttt{t}$ 为游戏结束时双方移动的步数之和。显然这应该是一个奇数。

如果黑方胜，请输出一行 $\texttt{"Black t"}$。其中 $\texttt{t}$ 为游戏结束时双方移动的步数之和。显然这应该是一个偶数。

注意，请输出双引号内的字符串，不包含双引号。
## 样例

### 样例输入 #1
```
0 5
4 5
...#O
.#..#
#O#..
.#..X
3 3
#.#
O.O
.X.
3 3
O..
.#X
.O.
5 5
.....
.....
..O..
#..#.
O#.X.
9 9
...######
.#.......
.#######.
.#.#.....
.#O#.####
.#.#.....
.#######.
.#X......
.O.......

```
### 样例输出 #1
```
Black 0
Black 2
Black 2
Tie
Red 75

```
### 样例输入 #2
```
见附件中的 zu/zu2.in
```
### 样例输出 #2
```
见附件中的 zu/zu2.ans
```
## 提示

**【样例 1 解释】**

第一组数据，红方第一步没有可行的移动，所以黑方胜。

第二组数据，无论第一步红方怎么移动，黑方都可以在下一步让黑棋子与红棋子在同一个位置。

第三组数据，无论第一步红方怎么移动，黑方都可以将自己的棋子往上移动一枚来达成胜利。

第四组数据，有一个红棋子不能动。另一个红棋子可以在第三行移动来防止黑棋子进入第一行。黑棋子也可以一直在第五行移动。如果红棋子到达第五行，黑棋子可以选择从另一边逃走。

第五组数据，在最后一行的那个红棋子可以从左边绕一圈抓住黑棋子。注意另一个红棋子可以移动。

**【样例 2 解释】**

这个样例中的每一组数据都满足测试点 $5$ 到 $13$ 中某一个测试点的限制。

**【子任务】**

对于所有的数据，保证：$1 \leq T \leq 10$，$2 \leq n \leq 10$，$1 \leq m \leq 10$，$\text{id}$ 等于测试点编号。

对于每组数据保证：棋盘上的黑棋恰好有一个，红棋恰好有两个，且黑棋不在第一 行。

- 测试点 $1 \sim 4$：保证要么平局，要么红方在开始时无法移动。

- 测试点 $5 \sim 6$：保证 $n \geq 4$ 。保证棋盘上第 $n-1$ 行的每一个格子都是障碍物，且 棋盘上其他行没有障碍物。保证黑棋在前 $n-2$ 行，有一个红棋在前 $n-2$ 行，另一个红棋在第 $n$ 行。

- 测试点 $7 \sim 9$：保证 $m=1$。

- 测试点 $10 \sim 13$：保证要么平局，要么存在策略可以在 $9$ 步之内结束游戏。

- 测试点 $14 \sim 20$：无特殊限制。


---

---
title: "「EZEC-14」终点"
layout: "post"
diff: 省选/NOI-
pid: P9462
tag: ['二分', '洛谷原创', '交互题', 'Special Judge', 'O2优化', '广度优先搜索 BFS', '深度优先搜索 DFS', '洛谷月赛']
---
# 「EZEC-14」终点
## 题目背景

~~出题人怎么还没鸟加这首歌啊。~~

于 2023.8.5 拿下。
## 题目描述

**这是一道交互题。**

dXqwq 有一棵 $n$ 个点的无根树，结点从 $1$ 到 $n$ 编号。您需要通过若干次询问得到这棵树的结构。

您可以选择两个整数 $1\leq u,v\leq n$，并输出 `? u v` 进行询问。

对于每次询问，如果 $u,v$ 的路径中点在一个结点上，交互库返回该点的编号，否则返回 ``0``。

请通过不超过 $147154$ 次询问，得到这棵树的结构。

保证树的形态是提前确定的，即**交互库不自适应。**

### 交互方式

输入测试点所在子任务编号 $id$ 和树的大小 $n$ 以开始交互。

交互过程中，您可以进行题目描述中的询问。

对于每次询问，如果你提供的 $u,v$ 不合法或者超出询问次数上限，交互库会返回 ``-1``，否则交互库将会返回一个非负整数，含义见「题目描述」。

当你读取到 ``-1`` 后应立刻退出程序，在此之后交互库的行为未定义。

在您确定答案后，请先输出 `!`，然后接下来 $n-1$ 行依次输出两个整数 ``u[i] v[i]`` 代表树的每条边，最后退出程序。你可以以任意顺序输出这些边。

在您输出一行后，请清空缓冲区：

- 在 C++ 中，使用 `fflush(stdout)` 或 `cout.flush()`。
- 在 Pascal 中，使用 `flush(output)`。
- 在 Python 中，使用 `stdout.flush()`。
- 其它语言请自行查阅文档。
## 输入格式

见「交互方式」。
## 输出格式

见「交互方式」。
## 样例

### 样例输入 #1
```
1 5

1

2

3

4

0
```
### 样例输出 #1
```
 
? 1 1

? 1 3

? 2 4

? 3 5

? 4 5

!
1 2
2 3
3 4
4 5
```
### 样例输入 #2
```
5 5

1

0

0

2

2
```
### 样例输出 #2
```
 
? 1 1

? 1 3

? 2 4

? 3 5

? 4 5

!
1 3
2 3
2 4
2 5
```
## 提示

**本题采用捆绑测试。**

-  Subtask 1（10 pts）：$n \leq 10$，树满足性质 A。
-  Subtask 2（10 pts）：保证存在一个点度数为 $n-1$。
-  Subtask 3（10 pts）：保证所有点度数 $\leq 2$。
-  Subtask 4（10 pts）：$n \leq 500$，树满足性质 A。
-  Subtask 5（20 pts）：$n \leq 500$。 
-  Subtask 6（20 pts）：树满足性质 A。
-  Subtask 7（20 pts）：无特殊限制。

性质 A：对于 $i=2,3,\cdots,n$ 存在整数 $1\leq j<i$ 满足有一条边连接 $i,j$。

对于 $100\%$ 的数据，$2 \leq n \leq 10^4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3u2zy1q5.png)


---

