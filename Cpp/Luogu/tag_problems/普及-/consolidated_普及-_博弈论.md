---
title: "[USACO24FEB] Palindrome Game B"
layout: "post"
diff: 普及-
pid: P10187
tag: ['数学', '贪心', '博弈论', 'USACO', '2024', 'O2优化']
---
# [USACO24FEB] Palindrome Game B
## 题目描述

Bessie 和 Elsie 正在使用一堆初始时共 $S$ 个石子（$1\le S<10^{10^5}$）进行一个游戏。两头奶牛依次行动，Bessie 先行动。当轮到一头奶牛行动时，她必须从堆中取走 $x$ 个石子，其中 $x$ 是该奶牛选定的任意正整数回文数。如果当一头奶牛的回合开始时石子堆是空的，那么这头奶牛就输了。

**定义**：一个正整数如果从前向后和从后向前读相同，则该数为回文数；回文数的例子有 $1$，$121$ 和 $9009$。数不允许有前导零；例如，$990$ **不是**回文数。

有 $T$（$1\le T\le 10$）个独立的测试用例。对于每一个测试用例，输出如果两头奶牛都采取最优策略，谁会赢得游戏。 
## 输入格式

输入的第一行包含 $T$，为测试用例的数量。以下 $T$ 行为测试用例，每个测试用例一行。

每个测试用例均由一个整数 $S$ 指定。 
## 输出格式

对于每一个测试用例输出一行，如果 Bessie 在最优策略下可以从一堆 $S$ 个石子的石子堆开始赢得游戏，则输出 `B`，否则输出 `E`。
## 样例

### 样例输入 #1
```
3
8
10
12
```
### 样例输出 #1
```
B
E
B
```
## 提示

### 样例解释

对于第一个测试用例，Bessie 可以在第一次行动中取走所有石子，因为 $8$ 是回文数，使她获胜。

对于第二个测试用例，$10$ 不是回文数，因此 Bessie 无法在第一次行动中取走所有石子。无论 Bessie 第一回合取走多少石子，Elsie 总能在第二回合取走所有余下的石子，使她获胜。

对于第三个测试用例，可以证明在最优策略下 Bessie 可以获胜。 

### 测试点性质

- 测试点 $2-4$：$S<100$。
- 测试点 $5-7$：$S<10^6$。
- 测试点 $8-10$：$S<10^9$。
- 测试点 $11-13$：没有额外限制。


---

---
title: "「FSLOI Round I」石子"
layout: "post"
diff: 普及-
pid: P11077
tag: ['博弈论', '洛谷原创', 'O2优化', '洛谷月赛', 'Ad-hoc']
---
# 「FSLOI Round I」石子
## 题目背景

**[English statement.](https://www.luogu.com.cn/problem/T500971) You must submit your code at the Chinese version of the statement.**

小 F 和小 L 正在玩一种古老的博弈游戏的改版。
## 题目描述

给定 $n$ 堆石子，第 $i$ 堆有 $a_i$ 个石子。设序列 $a_1,a_2,\cdots,a_n$ 的平均数为 $x$。此外，还会给定一个不大于 $x$ 的数字 $k$。小 F 和小 L 将轮流进行以下操作直至一方胜出，小 F 先手：

- 选定两堆石子 $i,j$，满足 $a_i < x < a_j$。若无法选出这样的两堆石子，则对方获胜。

- 从第 $j$ 堆石子中拿出 $k$ 个石子放到第 $i$ 堆中。

小 F 和小 L 都将用最优策略进行操作。

若游戏会无限进行下去，输出 `Draw`。若小 F 将获胜，输出 `F`。否则，输出 `L`。

小 F 一共会进行 $T$ 场游戏，你需要告诉他每场游戏的结果。
## 输入格式

第一行一个整数 $T$，表示共有 $T$ 组数据。

每组数据共两行。

第一行输入两个整数 $n,k$。

第二行输入 $n$ 个整数 $a_i$。
## 输出格式

共 $T$ 行。

每行应为 `Draw`，`F`，`L` 中的一种。
## 样例

### 样例输入 #1
```
1
5 2
1 5 7 9 13
```
### 样例输出 #1
```
L
```
### 样例输入 #2
```
2
6 3
4 7 5 3 1 16
7 2
2 6 4 8 12 4 6

```
### 样例输出 #2
```
Draw
L
```
## 提示

**【样例 1 解释】**

平均数为 $7$。

小 F 可以选择 $i=1,j=5$ 进行操作，使得石子数分别为 $3,5,7,9,11$。

小 L 可以选择 $i=1,j=4$ 进行操作，使得石子数分别为 $5,5,7,7,11$。

小 F 可以选择 $i=2,j=5$ 进行操作，使得石子数分别为 $5,7,7,7,9$。

小 L 可以选择 $i=1,j=5$ 进行操作，使得石子数分别为 $7,7,7,7,7$。

小 F 无法进行操作。小 L 获胜。可以证明无论小 F 如何操作，小 L 都有必胜策略。

**【数据规模与约定】**

**本题采用捆绑测试。**

设 $x$ 为序列 $a$ 的平均值。

对于 $100 \%$ 的数据，保证：
- $1 \leq T \leq 10$
- $1 \leq n \leq 2\times10^5$
- $0 \leq a_i \leq 10^9$
- $1 \leq k \leq x$
- $x$ 为整数

|子任务|分值|特殊性质|
|:-----:|:-----:|:-----:|
|$1$|$5$|$A$|
|$2$|$10$|$k = 1$|
|$3$|$15$|$n \leq 5, T =1$|
|$4$|$25$|$n \leq 1000$|
|$5$|$45$|无|

特殊性质 $A$：$a_1=a_2=a_3=\cdots=a_n$。


---

---
title: "「SFMOI Round I」Strange Cake Game"
layout: "post"
diff: 普及-
pid: P11143
tag: ['贪心', '博弈论', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「SFMOI Round I」Strange Cake Game
## 题目背景

[English statement](https://www.luogu.com.cn/problem/T510646). **You must submit your code at the Chinese version of the statement.**

小 $\mathcal{W}$ 和 小 $\mathcal{M}$ 在 CF 庄园里分蛋糕。

## 题目描述


有一块面积为 $n\times m$ 的矩形蛋糕。记其左上角顶点为 $(0,0)$，右下角顶点为 $(n,m)$，右上角顶点为 $(0,m)$。

蛋糕上分布着 $k$ 块巧克力，第 $i$ 块的位置为 $(x_i-0.5,y_i-0.5)$。**一个点上可能有不止一块巧克力。**

小 M 和 小 W 要切蛋糕。蛋糕刀起初在 $(0,0)$，小 W 先手，轮流移动蛋糕刀。设蛋糕刀在 $(x,y)$，则它可以被移动到 $(x,y+1)$ 或 $(x+1,y)$。

在若干步后，蛋糕会被切割轨迹完全分成两个部分——右上角的部分归小 W，左下角的部分归小 M。小 W 和小 M 都想吃到最多的巧克力，请帮他们计算：如果双方都按照最优策略行动，小 W 能分到几块巧克力。

如下是蛋糕的示例和一种可能的切蛋糕的方式。

![蛋糕示例](https://cdn.luogu.com.cn/upload/image_hosting/er9wuv91.png?x-oss-process=image/resize,m_lfit,h_500)
![切蛋糕示例](https://cdn.luogu.com.cn/upload/image_hosting/9o6ntvlb.png?x-oss-process=image/resize,m_lfit,h_500)
## 输入格式

第一行，两个正整数 $n,m$，含义见题面。

第二行，一个整数 $k$ ，表示巧克力块数。

接下来 $k$ 行，每行两个正整数 $x_i,y_i$，表示第 $i$ 块巧克力的坐标为 $(x_i-0.5,y_i-0.5)$。

注意：第 $i$ 块巧克力的坐标为 $(x_i-0.5,y_i-0.5)$。**一个格子上可能有多块巧克力。**
## 输出格式

输出一个整数，代表小 W 最多能拿到的巧克力块数。
## 样例

### 样例输入 #1
```
3 3
1
1 3
```
### 样例输出 #1
```
1
```
## 提示

### 数据范围

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$n=m=1$；
- Subtask 2（10 pts）：$1 \le n \times m \le 60$；
- Subtask 3（15 pts）：$1 \le n \times m \le 10^5$；
- Subtask 4（20 pts）：$k=1$；
- Subtask 5（50 pts）：无特殊限制。


对于 $100\%$ 的数据，保证：

- $0 \le k \le 2 \times 10^5$；
- $1 \le n,m \le 10^{18}$；
- $1 \le x_i \le n$，$1 \le y_i \le m$。



---

---
title: "取数游戏 II"
layout: "post"
diff: 普及-
pid: P1288
tag: ['数学', '博弈论']
---
# 取数游戏 II
## 题目描述

有一个取数的游戏。初始时，给出一个环，环上的每条边上都有一个非负整数。这些整数中至少有一个 $0$。然后，将一枚硬币放在环上的一个节点上。两个玩家就是以这个放硬币的节点为起点开始这个游戏，两人轮流取数，取数的规则如下：

1.  选择硬币左边或者右边的一条边，并且边上的数非 $0$；
1.  将这条边上的数减至任意一个非负整数（至少要有所减小）；
1.  将硬币移至边的另一端。

如果轮到一个玩家走，这时硬币左右两边的边上的数值都是 $0$，那么这个玩家就输了。

如下图，描述的是 Alice 和 Bob 两人的对弈过程（其中黑色节点表示硬币所在节点）。

 ![](https://cdn.luogu.com.cn/upload/pic/93.png) 

各图的结果为：

- $\text{A}$：轮到 Alice 操作；
- $\text{B}$：轮到 Bob 操作；
- $\text{C}$：轮到 Alice 操作；
- $\text{D}$：轮到 Bob 操作。

$\text{D}$ 中，轮到 Bob 走时，硬币两边的边上都是 $0$，所以 Alice 获胜。

现在，你的任务就是根据给出的环、边上的数值以及起点（硬币所在位置），判断先走方是否有必胜的策略。
## 输入格式

第一行一个整数 $N$ $(N \leq 20)$，表示环上的节点数。

第二行 $N$ 个数，数值不超过 $30$，依次表示 $N$ 条边上的数值。硬币的起始位置在第一条边与最后一条边之间的节点上。
## 输出格式

仅一行。若存在必胜策略，则输出 ```YES```，否则输出 ```NO```。
## 样例

### 样例输入 #1
```
4
2 5 3 0

```
### 样例输出 #1
```
YES

```
### 样例输入 #2
```
3
0 0 0

```
### 样例输出 #2
```
NO

```


---

---
title: "[GCJ 2015 #1C] Brattleship"
layout: "post"
diff: 普及-
pid: P13221
tag: ['贪心', '博弈论', '2015', 'Google Code Jam']
---
# [GCJ 2015 #1C] Brattleship
## 题目描述

You're about to play a simplified "battleship" game with your little brother. The board for this game is a rectangular grid with $R$ rows and $C$ columns. At the start of the game, you will close your eyes, and you will keep them closed until the end of the game. Your little brother will take a single rectangular $1 \times W$ ship and place it **horizontally** somewhere on the board. The ship must always fit entirely on the board, with each cell of the ship occupying exactly one of the grid's cells, and it can never be rotated.

In each turn of the game, you name a cell on the board, and your little brother tells you whether that is a hit (one of the cells occupied by the ship) or a miss. (Your little brother doesn't say which part of the ship was hit -- just that the cell you named has a part of the ship in it.) You have perfect memory, and can keep track of all the information he has given you. Once you have named all of the cells occupied by the ship, the game is over (the ship is sunk), and your score is the number of turns taken. Your goal is to minimize your score.

Although the ship is not supposed to be moved once it is placed, you know that your little brother, who is a brat, plans to cheat by changing the location of the ship whenever he wants, as long as the ship remains horizontal and completely on the board, and the new location is consistent with all the information he has given so far. For example, for a $1 \times 4$ board and $1 \times 2$ ship, your little brother could initially place the ship such that it overlaps the leftmost two columns. If your first guess was row 1, column 2, he could choose to secretly move the ship to the rightmost two columns, and tell you that $(1, 2)$ was a miss. If your next guess after that was $(1, 3)$, though, then he could not say that was also a miss and move the ship back to its original location, since that would be inconsistent with what he said about $(1, 2)$ earlier.

Not only do you know that your little brother will cheat, he knows that you know. If you both play optimally (you to minimize your score, him to maximize it), what is the lowest score that you can **guarantee** you will achieve, regardless of what your little brother does?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow, each with three space-separated integers $R$, $C$, and $W$: the number of rows and columns of the board, followed by the width of the ship.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from 1) and $y$ is the minimum score you can guarantee.
## 样例

### 样例输入 #1
```
3
1 4 2
1 7 7
2 5 1
```
### 样例输出 #1
```
Case #1: 3
Case #2: 7
Case #3: 10
```
## 提示

**Sample Explanation**

In Case #1, the board has one row and four columns, and the ship takes up one row and two columns. One optimal strategy is for you to start by naming cell $(1, 2)$:

If your little brother says it is a hit, then the other cell of the $1 \times 2$ ship must be in either $(1, 1)$ or $(1, 3)$, and you just have to name both. If you happen to correctly name the cell where the other part of the ship is, your little brother will just reposition the ship so that $(1, 2)$ is still hit, but your guess is a miss. Notice that your little brother can still move the ship even after it has been hit, as long as the new position is not inconsistent with the information he has already given.

If your little brother says it is a miss, then the only remaining consistent scenario is that the ship is in $(1, 3)$ and $(1, 4)$, and your little brother will be unable to change this from now on; you just need to name those two cells.

So no matter what your little brother does after you say $(1, 2)$, you can finish the game in two more moves after that, for a total of three moves.

Moreover, a three-move solution is optimal, because it is impossible to guarantee a finish in only two moves: without loss of generality, pick a first move. No matter what you pick, there is still a $1 \times 2$ area open and your little brother can just move the ship there and claim that you missed. It is impossible for you to sink that ship, which has not yet been hit, with only one more move.

In Case #2, the ship completely fills in the board and so your little brother has only one place to put it. All you have to do is name every cell.

In Case #3, your little brother can always move the $1 \times 1$ ship to a cell you have not tried yet, so you must name all 10 cells, only finally getting a hit (and immediately sinking the ship) on the last one.

**Limits**

- $1 \leq W \leq C$.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $T = 55$.
- $R = 1$.
- $1 \leq C \leq 10$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq T \leq 100$.
- $1 \leq R \leq 20$.
- $1 \leq C \leq 20$.


---

