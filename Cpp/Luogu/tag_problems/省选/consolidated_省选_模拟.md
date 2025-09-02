---
title: "[信息与未来 2024] AI 机器人"
layout: "post"
diff: 省选/NOI-
pid: B3983
tag: ['模拟', '搜索', '2024', '矩阵运算', '江苏', '分治', '记忆化搜索', '矩阵加速', '信息与未来']
---
# [信息与未来 2024] AI 机器人
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/27icb51c.png)

在 $n$ 行 $m$ 列的矩形空间中有一个机器人。矩形空间的每一个格子要么是平地（用半角点号 `.` 表示），要么是障碍物 （用井号表示 `#`）。以下是一个 $n = 3, m = 7$ 的例子：

```
...#...
...#...
.......
```

初始时,机器人位于矩形的左上角 （第一行、第一列）。每一时刻，机器人可以遵照程序执行 `U`（Up，向上）、`L` （Left，向左）、 `D` （Down，向下）、`R` （Right，向右） 四种指令中的一个，尝试向某个方向移动一格；如果移动的目标格子超出了边界或是障碍物，则保持原地不动，例如执行程序：

`LLLRRRRRRRRRDDDDRRRRRRRRR`

后，机器人会从空间的左上角移动到右下角。Dr. X 扩展了机器人程序的表达能力,引入了循环。给定程序 `P`，`(P)n` 相当于把程序 `P`“复制粘贴”$n$ 次。循环可以嵌套。例如，在足够大且无阻挡的空间中执行程序：

`(R(DRUL)7)5`

会重复 $5$ 次执行“向右移动一格、转圈 $7$ 次”，而如果机器人在 $n = 1, m = 2$ 的空间中执行上述程序，就会表现为“左右横跳”。

Dr. X 还给机器人装备了人工智能，对于某些指定的循环，机器人可以由深度神经网络自主决定循环的次数（$0$ 次或任意多次），用星号 `*` 表示，例如

`(DR(R)*)3`

外层循环会执行 $3$ 次，由于循环“复制粘贴”的特性，每次向下向右移动一格后，机器人可以根据自己的想法向右移动 $0$ 格或任意多格。人工智能循环也可以嵌套，根据循环“先外层后里层”的执行顺序，总是先确定外层人工智能循环的执行次数，再按照“复制粘贴”的规则执行内层循环代码。

人工智能模块使机器人的行为变得难以预测。给定一个机器人程序，Dr. X 想知道，哪些格子是机器人在执行程序过程中绝无可能经过的（即无论机器人如何选择循环执行的次数，都不会经过）？这样他可以在这些格子上安装监控，并在观察到机器人行为失控的时候及时制止。
## 输入格式

输入第一行两个空格分隔的整数 $n$ 和 $m$，代表矩形空间的大小为 $n$ 行、$m$ 列。

接下来 $n$ 行，每行 $m$ 个字符，描述了矩形空间。其中半角点号为平地、井号为障碍物。

输入最后一行是一个字符串，为机器人执行的程序。程序由 $\tt{U/L/D/R}$、圆括号、正整数、星号组成。输入程序保证合法：圆括号总是正确配对，且之后紧跟一个正整数或一个星号。除此之外，程序中所有的字符都是 $\tt{U,L,D}$ 或 $\tt{R}$。机器人初始时位于左上角，输入保证左上角不是障碍物。**固定次数循环的次数总是在 $1$ 到 $9$ 之间。**
## 输出格式

输出 $n$ 行，每行 $m$ 个字符，按顺序输出矩形空间中每个格子的计算结果。如果是障碍物格子，输出井号 `#`。如果是机器人选择适当的循环次数可以到达的平地格子，输出加号 `+`。否则输出半角点号 `.`。
## 样例

### 样例输入 #1
```
3 7
...#...
...#...
.......
LLLRRRRRRRRRDDDDRRRRRRRRR
```
### 样例输出 #1
```
+++#...
..+#...
..+++++
```
### 样例输入 #2
```
3 7
...#...
##.....
.......
(R(DRUL)7)5
```
### 样例输出 #2
```
+++#...
##+++++
..+++++
```
### 样例输入 #3
```
3 7
.......
.#####.
.......
(R)*(D)*
```
### 样例输出 #3
```
+++++++
+#####+
+.....+
```
## 提示

对于 $30\%$ 的数据，输入程序不含星号 `*` 且在 $10^5$ 步内终止。

对于另外 $30\%$ 的数据，输入程序中不含星号 `*`。

对于 $100\%$ 的数据，$1 \leq n, m \leq 10$，且输入程序的长度不超过 $1000$。

>本题原始满分为 $20\text{pts}$。


---

---
title: "[CEOI 2024] 文本编辑器"
layout: "post"
diff: 省选/NOI-
pid: P10803
tag: ['模拟', '2024', 'CEOI（中欧）', '最短路']
---
# [CEOI 2024] 文本编辑器
## 题目描述

**题目译自 [CEOI 2024](https://ceoi2024.fi.muni.cz/) Day1 T3「[Text editor](https://ceoi2024.fi.muni.cz/page/tasks/statements/editor.pdf)」**

罗伯特正在参加 2024 年 CEOI 编程竞赛。他几乎完成了当天最难的一道题的代码，而且他确信能拿满分！但问题出在一个小小的细节上：他打错了一个字！更糟糕的是，他从 2008 年就开始使用的那只心爱鼠标彻底罢工了，一点反应也没有。因此，他只能用键盘上的方向键移动光标去找到那个错别字。

罗伯特的程序有 $N$ 行，每行的长度分别为 $l_1, l_2, \ldots , l_N$。罗伯特总是以空行作为程序的结尾，所以 $l_N = 0$。光标可以放在两个字符之间，也可以放在行的开头或结尾。因此，第 $i$ 行有 $l_i + 1$ 个可用的光标位置（称为列），编号从 $1$ 到 $l_i + 1$。例如，下面是光标位于第 $2$ 行第 $6$ 列的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/4p5zr0jw.png)

罗伯特想把光标从第 $s_l$ 行的第 $s_c$ 列移动到第 $e_l$ 行的第 $e_c$ 列。他想求出最少需要的按键次数。

水平方向键的使用比较简单。按下 **左键** 会将光标移动到前一列，除非光标位于行首，则会移动到前一行的行尾。类似地，按下 **右键** 会将光标移动到后一列，或者如果光标位于行尾，则会移动到下一行的行首。

例如，**左键** 的移动可以像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/lig1idke.png)

而 **右键** 的移动可以像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/zy9hu3u5.png)

在文件的最开头按下 **左键** 或在文件的最结尾按下 **右键** 都不会有任何效果。

垂直方向键的使用稍微复杂一些。按下 **上键** 会将光标移动到上一行，按下 **下键** 会将光标移动到下一行，列数不会改变。但是，如果这样会使光标超出新行的结尾，光标则会跳到该行末尾。

例如，**上键** 的移动可以像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/2zixw04v.png)

而 **下键** 的移动可以像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/wr5ld99o.png)

如果按下 **上键** 或 **下键** 会把光标移动到不存在的行，则光标根本不会移动。
## 输入格式

输入的第一行包含一个整数 $N$，表示罗伯特程序的行数。

第二行包含两个空格隔开的整数 $s_l$ 和 $s_c$，表示初始光标位置。

类似地，第三行包含两个空格隔开的整数 $e_l$ 和 $e_c$，表示目标光标位置。

第四行包含 $N$ 个空格隔开的整数 $l_1, l_2, \ldots , l_N$，表示每行的长度。
## 输出格式

输出一行包含一个整数，表示将光标从 $(s_l, s_c)$ 移动到 $(e_l, e_c)$ 最少的按键次数。
## 样例

### 样例输入 #1
```
5
3 1
2 8
7 10 9 9 0
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
1 20
3 25
25 10 40 35 0
```
### 样例输出 #2
```
16
```
## 提示

**样例解释 1**

罗伯特可以通过按顺序按 **上键**、**左键** 和 **下键**三个键来将光标移动到目标位置：

![](https://cdn.luogu.com.cn/upload/image_hosting/wsz8bcr4.png)

或者，他也可以通过按 **左键**、**上键** 和 **下键** 来同样快速地将光标移动到目标位置。

**样例解释 2**

可以很容易地证明，不可能使用最多两个按键到达目标位置。

最短的可能按键序列是按两次 **下键** 然后按十四次 **右键**。

对于所有输入数据，满足：

- $1 \leq N \leq 10^6$
- $0 \leq l_i \leq 10^9\ (1\leq i\leq n)$
- $l_N = 0$
- $1 \leq s_l, e_l \leq N$
- $1 \leq s_c \leq l_{s_l} + 1$
- $1 \leq e_c \leq l_{e_l} + 1$

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :--: | :--: | :--: |
|  $1$  | $N \leq 2$ | $5$  |
|  $2$  | $N \leq 1\,000, l_i \leq 5\,000\ (1 \leq i \leq N)$| $14$ |
|  $3$  | $N \leq 1\,000$ | $26$ |
|  $4$  | $l_i = l_j\ (1 \leq i, j \leq N - 1)$ | $11$ |
|  $5$  | 无附加限制| $44$ |


---

---
title: "「SFMOI Round I」Strange Dino Game"
layout: "post"
diff: 省选/NOI-
pid: P11147
tag: ['模拟', '动态规划 DP', '贪心', '二分', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「SFMOI Round I」Strange Dino Game
## 题目背景

[English statement](https://www.luogu.com.cn/problem/T517979). **You must submit your code at the Chinese version of the statement.**


![](https://cdn.luogu.com.cn/upload/image_hosting/59joca92.png?x-oss-process=image/resize,m_lfit,h_600)

![](https://cdn.luogu.com.cn/upload/image_hosting/iyhol5l6.png?x-oss-process=image/resize,m_lfit,h_600)

Watersphere 同学在家没网了，只好玩起了 dino 游戏，但是他很菜，一玩到后面就头晕眼花，所以想让你编个程序帮助他拿到更高分，于是有了这题。

本题的游戏背景是 [Dino](https://dinosaur.game)。可以考虑点击链接游玩，以便更好理解题意。
## 题目描述


我们将问题放在二维平面上描述。我们给出一些游戏要素：

- 玩家：Dino。可以将其视为一个点。
- 障碍物：
    - 仙人掌：形如 $(x_i',0),(x_i',h_i)$ 的线段。
    - 飞鸟：形如 $(x_i,d_i),(x_i,u_i)$ 的线段。
- 游戏结束：Dino 与障碍物上的任意一点（包括线段端点）重合时，游戏结束。
- 起点：原点 $(0,0)$。
- 终点：使游戏结束的位置，位于第一象限（或 $x$ 轴上）。可能不存在（即游戏能无限进行）。
- 游戏分数：终点的 $x$ 坐标。终点不存在时定义为无穷大。
- 跳跃参数：正整数 $d,h$。
- 步行：Dino 在 $x$ 轴上沿着 $x$ 轴正方向移动。
- 跳跃：当 Dino 在 $x$ 轴上时，可以进行一次跳跃。以起跳点为原点，跳跃轨迹为
    $$f(x) = \begin{cases}
    \displaystyle  \frac{h}{d}x & x\in [0, d)  \\
    \displaystyle-\frac{h}{d}x+2h  & x\in [d, 2d)  \\
    \end{cases}$$
    - 需要注意的是，由上述定义可以推出：**在一次跳跃后落地的瞬间进行第二次跳跃是合法的。**
    - 需要注意的是，可以在任意**实数点**（只要在 $x$ 轴上）处开始跳跃。也就是说，跳跃不一定在整点开始。
    
下图展示了 $d=2,h=6$ 时的一次跳跃。

![](https://cdn.luogu.com.cn/upload/image_hosting/1gxrno9x.png?x-oss-process=image/resize,m_lfit,h_400)

在一局游戏中，Dino 从起点出发向 $x$ 轴正方向移动。目标是最大化得分，即尽量避开障碍物，使自己移动的距离尽量长。

每一时刻，Dino 只能做一件事：步行，或跳跃。当且仅当 Dino 在 $x$ 轴上时可以进行跳跃。

形式化地说，Dino 的行为可以被描述为一个长度为 $(k+1)$ 的实数二元组序列 $[(x_0,t_0),(x_1,t_1),\cdots,(x_k,t_k)]$，满足：

- $x_0=0$；
- $t_i\in \{0,1\}$；
- $\forall 0\le i\lt k$, $x_i\lt x_{i+1}$；
- $t_i=1,i\lt k\implies x_{i+1}-x_i\ge 2d$；(二段跳是不允许的)
- $\forall 0\le i\lt k$, $t_i=t_{i+1}\implies t_i=t_{i+1}=1$。

当 $t_i=0$ 时，我们定义 Dino 在 $x_i$ **进入步行状态**，否则定义 Dino 在 $x_i$ **进入跳跃状态**。

当 Dino 与障碍物重合时，游戏结束。此时 Dino 在的位置为终点，得分为终点的 $x$ 坐标。

已知有 $b$ 只飞鸟和 $c$ 个仙人掌，求出 Dino 的最大得分。特别地，得分可以为无穷大。

可参阅样例解释的图片。
## 输入格式


**本题单个测试点内有多组测试数据。**

第一行，一个正整数 $T$，代表游戏次数。

接下来依次描述 $T$ 组数据：

- 每组数据第一行，两个正整数 $d,h$，表示 dino 的跳跃参数。
- 每组数据第二行，两个整数 $b,c$，表示飞鸟个数与仙人掌个数。
- 接下来 $b$ 行，每行三个正整数 $x_{i},u_i,d_i$，描述第 $i$ 只飞鸟。
- 接下来 $c$ 行，每行两个正整数 $x'_{i},h_{i}$，描述第 $i$ 株仙人掌。

## 输出格式

对于每组数据输出一行，表示得分的最大值。

特别地，如果得分为正无穷，输出 `Dino!`。

## 样例

### 样例输入 #1
```
2
1 3
1 2
1 2 1
2 2
3 2
1000000000 1000000000
1 0
114514 1919 810
```
### 样例输出 #1
```
3
Dino!
```
### 样例输入 #2
```
1
8 16
8 3
5 18 13
4 20 10
6 13 1
2 17 11
1 11 6
5 1 1
2 6 3
1 16 1
7 20
7 13
3 2
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
1
5 5
1 2
5 5 1
6 1
16 3
```
### 样例输出 #3
```
16
```
### 样例输入 #4
```
1
5 5
1 4
19 10 8
4 1
15 1
22 2
20 1
```
### 样例输出 #4
```
22
```
## 提示


样例 $1$ 解释：  

- 对于第 $1$ 组数据，dino 无论如何也无法跳过连续的两株高为 $2$ 的仙人掌，答案即为第二株仙人掌的 $x$ 轴坐标。
- 对于第 $2$ 组数据，dino 可以在原点直接起跳跳过唯一的一只鸟，也完全可以不起跳从飞鸟下方走过。

其中第一组数据的解释如下所示，红线代表飞鸟，绿线代表仙人掌，粉线代表 Dino 的轨迹。

![](https://cdn.luogu.com.cn/upload/image_hosting/ge17so5a.png?x-oss-process=image/resize,m_lfit,h_400)

### 数据范围

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$c=0$；
- Subtask 2（5 pts）：$b,c \le 10$；
- Subtask 3（20 pts）：$b=0$；
- Subtask 4（20 pts）：$1 \le d,h,x_{b_i},d_i,u_i,x_i',h_i \le 10^5$;
- Subtask 5（40 pts）：无特殊限制。
- Subtask 6（10 pts）：无特殊限制。

对于 $100\%$ 的数据，保证：
- $1 \le T \le 10$；
- $0 \le b,c \le 2\times 10^4$；
- $1 \le d,h,x_{b_i},d_i,u_i,x_i',h_i\le 10^9$；
- $d_i\le u_i$。


---

---
title: "[GCJ 2016 #2] The Gardener of Seville"
layout: "post"
diff: 省选/NOI-
pid: P13200
tag: ['模拟', '贪心', '2016', 'Special Judge', '构造', 'Google Code Jam']
---
# [GCJ 2016 #2] The Gardener of Seville
## 题目描述

You are the Gardener of Seville, a minor character in an opera. The setting for the opera is a courtyard which is a rectangle of unit cells, with $\mathbf{R}$ rows and $\mathbf{C}$ columns. You have been asked to install a maze of hedges in the courtyard: every cell must contain a hedge that runs diagonally from one corner to another. For any cell, there are two possible kinds of hedge: lower left to upper right, which we represent with /, and upper left to lower right, which we represent with $\backslash$. Wherever two hedges touch, they form a continuous wall.

Around the courtyard is an outer ring of unit cells, one cell wide, with the four corners missing. Each of these outer cells is the home of a courtier. The courtiers in these outer cells are numbered clockwise, starting with 1 for the leftmost of the cells in the top row, and ending with $2 \times (\mathbf{R}+\mathbf{C})$ for the topmost cell in the left column. For example, for $\mathbf{R}=2, \mathbf{C}=2$, the numbering in the outer ring looks like this. (Note that no hedges have been added yet.)

```
 12 
8  3
7  4
 65
```

In this unusual opera, love is mutual and exclusive: each courtier loves exactly one other courtier, who reciprocally loves only them. Each courtier wants to be able to sneak through the hedge maze to his or her lover without encountering any other courtiers. That is, any two courtiers in love with each other must be connected by a path through the maze that is separated from every other path by hedge walls. It is fine if there are parts of the maze that are not part of any courtier's path, as long as all of the pairs of lovers are connected.

Given a list of who loves who, can you construct the hedge maze so that every pair of lovers is connected, or determine that this is IMPOSSIBLE?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each consists of one line with two integers $\mathbf{R}$ and $\mathbf{C}$, followed by another line with a permutation of all of the integers from 1 to $2 \times (\mathbf{R}+\mathbf{C})$, inclusive. Each integer is the number of a courtier; the first and second courtiers in the list are in love and must be connected, the third and fourth courtiers in the list are in love and must be connected, and so on.

## 输出格式

For each test case, output one line containing only `Case #x:`, where $\mathrm{x}$ is the test case number (starting from 1). Then, if it is impossible to satisfy the conditions, output one more line with the text IMPOSSIBLE. Otherwise, output $\mathbf{R}$ more lines of $\mathbf{C}$ characters each, representing a hedge maze that satisfies the conditions, where every character is $/$ or $\backslash$. You may not leave any cells in the maze blank. If multiple mazes are possible, you may output any one of them.
## 样例

### 样例输入 #1
```
4
1 1
1 4 3 2
1 3
1 8 2 7 3 4 5 6
2 2
8 1 4 5 2 3 7 6
1 1
1 3 2 4
```
### 样例输出 #1
```
Case #1:
/
Case #2:
//\
Case #3:
//
\/
Case #4:
IMPOSSIBLE
```
## 提示

**Sample Explanation**

In Case #3, the following pairs of courtiers are lovers: $(8, 1), (4, 5), (2, 3), (7, 6)$. Here is an illustration of our sample output:

![](https://cdn.luogu.com.cn/upload/image_hosting/bxa3n9a8.png)

For Case #3, note that this would also be a valid maze:

```
/\
\/
```

In Case #4, the courtyard consists of only one cell, so the courtiers living around it, starting from the top and reading clockwise, are 1, 2, 3, and 4. There are only two possible options to put in the one cell: / or \\. The first of these choices would form paths from 1 to 4, and from 2 to 3. The second of these choices would form paths from 1 to 2, and from 3 to 4. However, neither of these helps our lovesick courtiers, since in this case, 1 loves 3 and 2 loves 4. So this case is IMPOSSIBLE, and the opera will be full of unhappy arias!

**Limits**

**Small dataset (6 Pts, Test Set 1 - Visible)**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{R} \times \mathbf{C} \leqslant 16$.

**Large dataset (23 Pts, Test Set 2 - Hidden)**

- $1 \leqslant \mathbf{T} \leqslant 500$.
- $1 \leqslant \mathbf{R} \times \mathbf{C} \leqslant 100$.



---

---
title: "[GCJ 2014 Finals] Symmetric Trees"
layout: "post"
diff: 省选/NOI-
pid: P13266
tag: ['模拟', '2014', '树形 DP', '哈希 hashing', 'Google Code Jam']
---
# [GCJ 2014 Finals] Symmetric Trees
## 题目描述

Given a vertex-colored tree with $\mathrm{N}$ nodes, can it be drawn in a 2D plane with a line of symmetry?

Formally, a tree is line-symmetric if each vertex can be assigned a location in the 2D plane such that:

* All locations are distinct.
* If vertex $\mathbf{v}_{\mathrm{i}}$ has color $\mathbf{C}$ and coordinates $\left(\mathrm{x}_{\mathrm{i}}, \mathrm{y}_{\mathrm{i}}\right)$, there must also be a vertex $\mathbf{v}_{\mathrm{i}}^{\prime}$ of color $\mathbf{C}$ located at $\left(-\mathrm{x}_{\mathrm{i}}, \mathrm{y}_{\mathrm{i}}\right)$ -- Note if $\mathrm{x}_{\mathrm{i}}$ is 0, $\mathbf{v}_{\mathrm{i}}$ and $\mathbf{v}_{\mathrm{i}}^{\prime}$ are the same vertex.
* For each edge $\left(\mathbf{v}_{\mathrm{i}}, \mathbf{v}_{\mathrm{j}}\right)$, there must also exist an edge $\left(\mathbf{v}_{\mathrm{i}}^{\prime}, \mathbf{v}_{\mathrm{j}}^{\prime}\right)$.
* If edges were represented by straight lines between their end vertices, no two edges would share any points except where adjacent edges touch at their endpoints.
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow.

Each test case starts with a line containing a single integer $\mathrm{N}$, the number of vertices in the tree.

$\mathrm{N}$ lines then follow, each containing a single uppercase letter. The $\mathrm{i}$-th line represents the color of the $\mathrm{i}$-th node.

$\mathrm{N}-1$ lines then follow, each line containing two integers $\mathrm{i}$ and $\mathrm{j}(1 \leq \mathrm{i}<\mathrm{j} \leq \mathrm{N})$. This denotes that the tree has an edge from the $\mathrm{i}$-th vertex to the $\mathrm{j}$-th vertex. The edges will describe a connected tree.
## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the case number (starting from 1) and $\mathrm{y}$ is "SYMMETRIC" if the tree is line-symmetric by the definition above or "NOT SYMMETRIC" if it isn't.
## 样例

### 样例输入 #1
```
3
4
R
G
B
B
1 2
2 3
2 4
4
R
G
B
Y
1 2
2 3
2 4
12
Y
B
Y
G
R
G
Y
Y
B
B
B
R
1 3
1 9
1 10
2 3
3 7
3 8
3 11
4 8
5 7
6 7
8 12
```
### 样例输出 #1
```
Case #1: SYMMETRIC
Case #2: NOT SYMMETRIC
Case #3: SYMMETRIC
```
## 提示

**Sample Explanation**

The first case can be drawn as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/ithqougs.png)

No arrangement of the second case has a line of symmetry:

![](https://cdn.luogu.com.cn/upload/image_hosting/0kmct7ap.png)

One way of drawing the third case with a symmetry line is as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/9yzlvp9q.png)

**Limits**

- $1 \leq T \leq 100$

**Small dataset(7 Pts)**

- Time Limit: ~~60~~ 3 seconds
- $2 \leq N \leq 12$

**Large dataset(18 Pts)**

- Time Limit: ~~120~~ 5 seconds
- $2 \leq N \leq 10000$


---

---
title: "[GCJ 2012 Qualification] Hall of Mirrors"
layout: "post"
diff: 省选/NOI-
pid: P13314
tag: ['模拟', '计算几何', '2012', 'Google Code Jam']
---
# [GCJ 2012 Qualification] Hall of Mirrors
## 题目描述

You live in a 2-dimensional plane, and one of your favourite places to visit is the Hall of Mirrors. The Hall of Mirrors is a room (a 2-dimensional room, of course) that is laid out in a grid. Every square on the grid contains either a square mirror, empty space, or you. You have width 0 and height 0, and you are located in the exact centre of your grid square.

Despite being very small, you can see your reflection when it is reflected back to you exactly. For example, consider the following layout, where '#' indicates a square mirror that completely fills its square, '.' indicates empty space, and the capital letter 'X' indicates you are in the center of that square:

```
######
#..X.#
#.#..#
#...##
######
```

If you look straight up or straight to the right, you will be able to see your reflection.

Unfortunately in the Hall of Mirrors it is very foggy, so you can't see further than $D$ units away. Suppose $D=3$. If you look up, your reflection will be 1 unit away (0.5 to the mirror, and 0.5 back). If you look right, your reflection will be 3 units away (1.5 to the mirror, and 1.5 back), and you will be able to see it. If you look down, your reflection will be 5 units away and you won't be able to see it.

It's important to understand how light travels in the Hall of Mirrors. Light travels in a straight line until it hits a mirror. If light hits any part of a mirror but its corner, it will be reflected in the normal way: it will bounce off with an angle of reflection equal to the angle of incidence. If, on the other hand, the light would touch the corner of a mirror, the situation is more complicated. The following diagrams explain the cases:

In the following cases, light approaches a corner and is reflected, changing its direction:

![](https://cdn.luogu.com.cn/upload/image_hosting/u55batrx.png)

In the first two cases, light approached two adjacent mirrors at the point where they met. Light was reflected in the same way as if it had hit the middle of a long mirror. In the third case, light approached the corners of three adjacent mirrors, and returned in exactly the direction it came from.

In the following cases, light approaches the corners of one or more mirrors, but does not bounce, and instead continues in the same direction:

![](https://cdn.luogu.com.cn/upload/image_hosting/6wlefjn2.png)

This happens when light reaches distance 0 from the corner of a mirror, but would not have to pass through the mirror in order to continue in the same direction. In this way, a ray of light can pass between two mirrors that are diagonally adjacent to each other -- effectively going through a space of size 0. Good thing it's of size 0 too, so it fits!

In the final case, light approaches the corner of one mirror and is destroyed:

![](https://cdn.luogu.com.cn/upload/image_hosting/3lb0xedn.png)

The mirror was in the path of the light, and the ray of light didn't approach the corners of any other mirrors.

Note that light stops when it hits you, but it has to hit the exact centre of your grid square.

How many images of yourself can you see?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing three space-separated integers, $H$, $W$ and $D$. $H$ lines follow, and each contains $W$ characters. The characters constitute a map of the Hall of Mirrors for that test case, as described above.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the number of reflections of yourself you can see.
## 样例

### 样例输入 #1
```
6
3 3 1
###
#X#
###
3 3 2
###
#X#
###
4 3 8
###
#X#
#.#
###
7 7 4
#######
#.....#
#.....#
#..X..#
#....##
#.....#
#######
5 6 3
######
#..X.#
#.#..#
#...##
######
5 6 10
######
#..X.#
#.#..#
#...##
######
```
### 样例输出 #1
```
Case #1: 4
Case #2: 8
Case #3: 68
Case #4: 0
Case #5: 2
Case #6: 28
```
## 提示

**Sample Explanation**

In the first case, light travels exactly distance 1 if you look directly up, down, left or right.

In the second case, light travels distance $1.414\dots $ if you look up-right, up-left, down-right or down-left. Since light does not travel through you, looking directly up only shows you one image of yourself.

In the fifth case, while the nearby mirror is close enough to reflect light back to you, light that hits the corner of the mirror is destroyed rather than reflected.

**Limits**

- $1 \leq T \leq 100$.
- $3 \leq H, W \leq 30$.
- $1 \leq D \leq 50$.
- All characters in each map will be '#', '.', or 'x'.
- Exactly one character in each map will be 'x'.
- The first row, the last row, the first column and the last column of each map will be entirely filled with '#' characters.

**Test set 1 (15 Pts, Visible Verdict)**

- There will be no more than $2W + 2H - 4$ '#' characters.

**Test set 2 (25 Pts, Hidden Verdict)**

- The restriction from the Small dataset does not apply.


---

---
title: "[GCJ 2011 Finals] Rains Over Atlantis"
layout: "post"
diff: 省选/NOI-
pid: P13383
tag: ['模拟', '2011', '最短路', '均摊分析', 'Google Code Jam']
---
# [GCJ 2011 Finals] Rains Over Atlantis
## 题目描述

Rains fall on the isle of Atlantis, and will erode all the land to nothingness. What you want to know, so that you can organize the evacuation, is how soon it will happen.

You have a map of Atlantis. The map is a square grid, and each square contains the height of the land in that square, in metres, above sea level. All squares outside the map have height 0; all squares with height 0 are water, and all squares with larger heights are land. There are no squares with lower height.

Water can flow from a source square to a target square if the source square and target square share an edge, and if the height of the water in the target square is lower than or equal to the height of water in the source square.

It's raining very quickly, which means that if there is nowhere for the rain water in a square to flow, water in that square will accumulate until there is a square to which the rain water can flow. Squares that are not on the map can accept any amount of flow. For example, the following map:

```
5 9 9 9 9 9
0 8 9 0 2 5
3 9 9 9 9 9
```

Will quickly fill up with water. We'll call the height of water in each square, plus the height of the land, the water level. It will be:

```
5 9 9 9 9 9
0 8 9 5 5 5
3 9 9 9 9 9
```

Note that the 0 in the middle of the land, although it's water, is not connected to the outside of the map and so just accumulates water. The 0 on the border of the land, however, is connected to the outside of the map, and so the water from the 8 can flow through it to the outside.

The direction in which water flows is determined by the water level. If there are multiple possible squares where water could flow from one particular source square, the water from that source will flow to the square with the lowest water level (ties don't matter, as you will see).

Now the erosion begins. Each day, a square is eroded—its height decreases—depending on how water is flowing from it. If water is flowing from $S$ to $T$, then $S$'s height decreases by $\min(\text{WaterLevel}(S) - \text{WaterLevel}(T), M)$. All erosion happens at exactly the same time, at the end of the day. For example, with $M=5$, the map above will erode to:
```
0 4 4 4 4 4
0 3 5 0 2 0
0 4 4 4 4 4
```
After a day's erosion, excess water will flow away: squares with water level higher than a neighbour's water level will lose water until they are of the same height. Water will also accumulate in the same way that it did on the first day. After the first day, this map's water level will become:
```
0 4 4 4 4 4
0 3 5 2 2 0
0 4 4 4 4 4
```
After another day of erosion, the map will look like:
```
0 0 0 0 0 0
0 0 2 0 0 0
0 0 0 0 0 0
```
...and the Atlanteans will need to escape in a big hurry. Your task is to determine how many days it will take for all the heights to erode to $0$.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing three space-separated integers: $H$, $W$ and $M$. The first two denote the size of the map, while the third is the maximum amount a square can erode in one day, as described above. $H$ lines follow, each of which contains $W$ space-separated integers. The $i^{th}$ integer on the $j^{th}$ line denotes the height of the square at $(i, j)$.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the number of days it takes to erode all the island.
## 样例

### 样例输入 #1
```
2
3 6 5
5 9 9 9 9 9
0 8 9 0 2 5
3 9 9 9 9 9
3 6 3
3 8 10 11 10 8
7 5 2 12 8 8
6 9 11 9 8 4
```
### 样例输出 #1
```
Case #1: 3
Case #2: 5
```
## 提示

In the second case, the water height looks like:
```
3 8 10 11 10 8
7 7 7 12 8 8
6 9 11 9 8 4
```

After one day the island looks as follows:
```
0 5 7 8 7 5
4 5 2 9 8 5
3 6 8 6 5 1
```

And after the second day:
```
0 2 4 5 4 2
1 4 2 6 5 2
0 3 5 3 2 0
```

And the third day:
```
0 0 1 2 1 0
0 1 2 3 2 0
0 0 2 0 0 0
```

After the fourth day, things are looking desperate for the Atlanteans:
```
0 0 0 0 0 0
0 0 1 0 0 0
0 0 0 0 0 0
```

Finally, on the fifth day the last square erodes away. Atlantis lasted for five days; they probably shouldn't have built their city out of brown sugar.

**Limits**

- $1 \leq T \leq 40$.

**Small dataset (7 Pts, Test set 1 - Visible)**

- $1 \leq H, W \leq 10$.
- $1 \leq M \leq 100$.
- $0 \leq \text{all heights} \leq 100$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $1 \leq H, W \leq 20$.
- $1 \leq M \leq 10^{15}$.
- $0 \leq \text{all heights} \leq 10^{15}$.
- Time limit: ~~60~~ 6 seconds.



---

---
title: "[NWRRC 2023] First Solved, Last Coded"
layout: "post"
diff: 省选/NOI-
pid: P13586
tag: ['模拟', '动态规划 DP', '2023', 'Special Judge', '区间 DP', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] First Solved, Last Coded
## 题目描述

In ICPC, teamwork is everything. That's why everyone on your team has a well-defined role: Sol the Solver can solve any problem in the problem set, Codie the Coder can implement any solution that Sol comes up with, and you... are the glue that holds everything together. Sol and Codie are very picky about the order of problems they would solve/code, and your job is to satisfy their preferences.

There will be $n$ problems in the upcoming contest, and you know the general topic of each problem: greedy, geometry, graphs, etc. For simplicity, we will represent each topic with an integer from $1$ to $n$. These integers don't have to be distinct, that is, multiple problems in the contest can have the same topic.

Sol wants to solve problems in a specific order of topics: first, the problem with the topic $a_1$, after that, the problem with the topic $a_2$, $\ldots$, and finally, the problem with the topic $a_n$. Codie also has a preference list: $b_1, b_2, \ldots, b_n$, only willing to code problems in that order of topics.

Your job during the contest will be to take solution sheets from Sol and hand them to Codie in the correct order. As your team only has one table to work with, you don't have enough space to arrange all the solutions neatly. Thus, you came up with the following workflow: you will ask Sol for solutions (who will hand them to you in order $a_1, a_2, \ldots, a_n$), store them in a stack on your part of the table, and hand them to Codie to code (in order $b_1, b_2, \ldots, b_n$).

More formally, at any moment during the contest, you have (at most) two actions you can make:

- If there are still any unsolved problems remaining, ask Sol for another solution and put it on top of your stack of solution sheets. This action is denoted by the character $\tt{S}$.
- If your stack is not empty, take the solution sheet from the top of your stack and give it to Codie to implement. This action is denoted by the character $\tt{C}$.

For the given lists of Sol's and Codie's preferences, find a sequence of actions that ensures that all problems are solved and coded in the correct order. Consider all solving and coding times insignificant --- managing solution sheets is a much harder and more important job anyway.
## 输入格式

The first line contains a single integer $n$, denoting the number of problems in the contest ($1 \le n \le 100$).

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$, denoting Sol's preferred order of topics ($1 \le a_i \le n$).

The third line contains $n$ integers $b_1, b_2, \ldots, b_n$, denoting Codie's preferred order of topics ($1 \le b_i \le n$).

The given lists are equal as multisets: every integer occurs the same number of times in $A$ and in $B$.
## 输出格式

If your task is impossible, print $\tt{NO}$. Otherwise, print $\texttt{YES}$ on the first line, followed by the sequence of actions on the second line: a string consisting of $2n$ characters $\tt{S}$ or $\tt{C}$ ($n$ of each), describing your actions in order.

You are not allowed to ask Sol for more solutions if all $n$ problems have already been solved, or give Codie a solution with the wrong topic. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
4
4 1 2 2
1 2 4 2
```
### 样例输出 #1
```
YES
SSCSCCSC
```
### 样例输入 #2
```
3
2 3 1
1 2 3
```
### 样例输出 #2
```
NO
```


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
title: "[NOI2005] 维护数列"
layout: "post"
diff: 省选/NOI-
pid: P2042
tag: ['模拟', '2005', '平衡树', 'NOI']
---
# [NOI2005] 维护数列
## 题目描述


请写一个程序，要求维护一个数列，支持以下 $6$ 种操作：

| 编号 | 名称 | 格式 | 说明 |
| :-----------: | :-----------: | :-----------: | :----------- |
| 1 | 插入 | $\operatorname{INSERT}\ posi \ tot \ c_1 \ c_2 \cdots c_{tot}$ | 在当前数列的第 $posi$ 个数字后插入 $tot$ 个数字：$c_1, c_2 \cdots c_{tot}$；若在数列首插入，则 $posi$ 为 $0$ |
| 2 | 删除 | $\operatorname{DELETE} \ posi \ tot$ | 从当前数列的第 $posi$ 个数字开始连续删除 $tot$ 个数字 |
| 3 | 修改 | $\operatorname{MAKE-SAME} \ posi \ tot \ c$ | 从当前数列的第 $posi$ 个数字开始的连续 $tot$ 个数字统一修改为 $c$ |
| 4 | 翻转 | $\operatorname{REVERSE} \ posi \ tot$ | 取出从当前数列的第 $posi$ 个数字开始的 $tot$ 个数字，翻转后放入原来的位置 |
| 5 | 求和 | $\operatorname{GET-SUM} \ posi \ tot$ | 计算从当前数列的第 $posi$ 个数字开始的 $tot$ 个数字的和并输出 |
| 6 | 求最大子列和 | $\operatorname{MAX-SUM}$ | 求出当前数列中和最大的一段子列，并输出最大和 |
## 输入格式

第一行包含两个整数 $N$ 和 $M$，$N$ 表示初始时数列中数的个数，$M$ 表示要进行的操作数目。

第二行包含 $N$ 个数字，描述初始时的数列。以下 $M$ 行，每行一条命令，格式参见问题描述中的表格。
## 输出格式

对于输入数据中的 $\operatorname{GET-SUM}$ 和 $\operatorname{MAX-SUM}$ 操作，向输出文件依次打印结果，每个答案（数字）占一行。
## 样例

### 样例输入 #1
```
9 8 
2 -6 3 5 1 -5 -3 6 3 
GET-SUM 5 4
MAX-SUM
INSERT 8 3 -5 7 2
DELETE 12 1
MAKE-SAME 3 3 2
REVERSE 3 6
GET-SUM 5 4
MAX-SUM
```
### 样例输出 #1
```
-1
10
1
10
```
## 提示

#### 数据规模与约定

- 你可以认为在任何时刻，数列中至少有 $1$ 个数。
- 输入数据一定是正确的，即指定位置的数在数列中一定存在。
- 对于 $50\%$ 的数据，任何时刻数列中最多含有 $3 \times 10^4$ 个数。
- 对于 $100\%$ 的数据，任何时刻数列中最多含有 $5 \times 10^5$ 个数，任何时刻数列中任何一个数字均在 $[-10^3, 10^3]$ 内，$1 \le M \le 2 \times 10^4$，插入的数字总数不超过 $4 \times 10^6$。

题面由 @syksykCCC 提供。


---

---
title: "[HNOI2004] FTP服务器"
layout: "post"
diff: 省选/NOI-
pid: P2262
tag: ['模拟', '2004', '各省省选', '湖南']
---
# [HNOI2004] FTP服务器
## 题目背景

File Transfer Protocol，文件传输协议，简称 FTP。人们可以通过 FTP 实现资源共享。一般的情况下用户访问一个 FTP 服务器是通过类似资源管理器的形式对该服务器上的资源进行浏览，并且不同权限的用户可以实现下载文件/文件夹，上传文件/文件夹。

## 题目描述

一个FTP服务器的所有资源都以文件的形式按树形结构存储在不同的文件夹里，最低一级的是根目录（即根文件夹），根目录里有若干个文件和文件夹，每一个文件夹里都可以拥有 $0$ 个或多个文件及文件夹，同一文件夹里不存在名称相同的文件和文件夹。

一个用户包含三个属性：

- $\text{userType}$：用户类型；
- $\text{userState}$：用户状态（用户正在执行的操作）；
- $\text{userPosition}$：用户当前所处的位置（即用户正在浏览的文件夹）。

用户分 $3$ 种类型：上传用户 $\text{uploadUser}$，下载用户 $\text{downloadUser}$，匿名用户 $\text{guest}$。

操作分 $3$ 种类型：浏览 $\text{scan}$，下载 $\text{download}$，上传 $\text{upload}$。

用户的权限是指用户允许进行的操作。不同类型的用户的权限是不同的。

任何一个用户是不能进行其没有权限的操作的，例如：一个匿名用户想要下载一个文件或者文件夹是不允许的。

一个文件/文件夹包含三个属性：

- $\text{fileName/folderName}$：文件名（不包含空格和回车）；
- $\text{fileSize/folderSize}$：文件大小
（单位 $\text{byte}$，$0 <\mathrm{filesize}< 10^5$，$0<\mathrm{folderSize}< 10^8$，文件夹的大小是它里面所包含的所有文件大小的总和）；
- $\text{fileState/folderState}$：当前状态，当前状态有两种：
  - 一种为正常 $\text{normal}$（文件/文件夹为正常状态时，允许用户对其进行操作）；
  - 另一种为上传未完成 $\text{uploading}$（处在此种状态时，用户只能够对其进行浏览操作，如果一个文件夹中有一个或多个文件处于 $\text{uploading}$ 状态，那么这个文件夹也处于 $\text{uploading}$ 状态）。

一个 FTP 服务器除了它所拥有的文件资源外，还有如下属性：

1. 访问用户的最大数量（包括所有不同类型的用户） $\text{maxUserNumber}<100$。如果当前访问用户数量已经达到最大值的话，其他新的用户对服务器的访问将是失败的。
2. 服务器的最大流量 $\text{maxServerFlux}<10^7$。
3. 单个用户允许的最大下载/上传流量 $\text{maxUserFlux}$。

FTP 服务器运行的最小时间单位为秒。

每一个用户在同一时刻只能进行一种操作。用户下载和上传文件/文件夹是需要一定时间的，而这个时间决定于用户流量 $\text{userFlux}$，单位为 $\text{byte/second}$，注意如果某一时刻文件/文件夹仍须上传/下载的大小（$>0$）小于 $\text{userFlux}$ 的话，上传/下载时间仍将按照一秒钟看待。

而 $\text{userFlux}$ 的值是如何确定的呢？

 $$\mathrm{userFlux} = \min(\mathrm{presentMaxUserFlux},\mathrm{maxUserFlux})$$

其中，$\text{presentMaxUserFlux}$ 为当前服务器的单个用户最大流量：

$$\mathrm{presentMaxUserFlux} = \lfloor \mathrm{maxServerFlux} / \mathrm{userTotal}\rfloor$$

（$\text{userTotal}$ 表示该时刻的正在进行上传和下载操作的用户数量）

一个用户通过一系列命令实现其在 FTP 服务器上的相关操作。下面介绍这些命令：

### $\verb!connect!$ 命令

- 格式：$\verb![name] + 空格 + connect + 空格 + 参数A!$。
- 例：$\verb!tsinghua connect 1!$。
- 表示在名叫 $\verb!name!$ 的用户请求以 $\verb!A!$ 身份连接到服务器上。如果当前的最大使用用户还没达到 $\text{maxUserNumber}$，并且该用户未连接到服务器，则连接成功，服务器反馈回一个相关信息 $\verb!success!$。否则反馈信息为 $\verb!unsuccess!$。一旦连接成功，用户其所处的位置 $\text{userPosition}$ 为服务器的根目录。$A=1$ 表示上传用户，$A=2$ 下载表示用户，$A=3$ 表示匿名用户。

### $\verb!quit!$ 命令

- 格式：$\verb![name] + 空格 + quit!$。
- 例：$\verb!tsinghua quit!$。
- 表示名叫 $\verb!name!$ 的用户断开与服务器的连接。如果用户未连接反馈 $\verb!unsuccess!$，否则反馈 $\verb!success!$。（注意用户在任何状态下都可以断开与服务器的连接）。

### $\verb!cd!$ 命令

- 格式：$\verb![name] + 空格 + cd + 空格 + [folderName/文件夹名称]!$。
- 例：$\verb!THU cd FD!$。
- 表示名叫 $\verb!name!$ 的用户希望从当前所处的文件夹进入该文件夹中的一个名叫 $\text{folderName}$ 的文件夹。如果名叫 $\text{folderName}$ 的文件夹存在并且处于 $\text{normal}$ 状态，则改变用户当前所处位置 $\text{userPosition}$，反馈相关信息 $\verb!success!$，如果该文件夹不存在或该用户没有成功连接，则反馈信息为 $\verb!unsuccess!$。

### $\verb!cd..!$ 命令

- 格式：$\verb![name] + 空格 + cd..!$。
- 例：$\verb!9# cd..!$。
- 表示名叫 $\verb!name!$ 的用户希望从当前所处的文件夹返回到他的上一级文件夹。如果用户处于根目录或者用户未连接，则命令执行失败返回 $\verb!unsuccess!$，否则返回 $\verb!success!$，并且改变用户所处位置 $\text{userPosition}$。

### $\verb!download!$ 命令

- 格式：$\verb![name] + 空格 + download + 空格 + [name1]!$。
- 例：$\verb!A download 1.txt!$。
- 表示名叫 $\verb!name!$ 的用户希望从当前所处文件夹下载名为 $\verb!name1!$ 的文件或者文件夹。如果用户未连接，用户没有下载权限，名为 $\verb!name1!$ 的文件/文件夹不存在，或者该文件/文件夹处于 $\text{uploading}$ 状态时，反馈信息 $\verb!unsuccess!$，否则返回 $\verb!success!$ 并且开始下载该文件/文件夹。（一旦一个下载命令开始执行，那么执行该命令的用户所下载的是下载命令执行的那一时刻的那一个文件/文件夹，也就是说如果一个用户正在下在某个文件夹，在下载过程中，有另外一用户在这个文件夹里面上传文件，那么原下载用户是不可能下载到这个新上传的文件的）。

### $\verb!upload!$ 命令

- 格式：$\verb![name] + 空格 + upload + 空格 + [name1] + 空格 + [size]!$。
- 例：$\verb!A upload B 1!$。
- 表示名叫 $\verb!name!$ 的用户希望在当前所处的文件夹上传一个名叫 $\verb!name1!$ 的大小为 $\text{size}$ 的文件/文件夹。注意：
  - 用户通过 $\verb!upload!$ 命令上传文件夹只能为空文件夹，当 $\text{size}=0$ 表示上传文件夹，size>0表示上传文件。
  - 如果当前目录已经存在了同名的文件/文件夹，用户未成功连接或者用户没有上传权限，反馈信息 $\verb!unsuccess!$，否则反馈 $\verb!success!$，并且开始上传文件/文件夹。（如果一个用户想要上传一个非空文件夹，是很容易通过一系列 $\verb!upload!$ 以及 $\verb!cd!$ 命令实现的）。

---

除上传文件和下载文件/文件夹命令需要耗时外，其他的命令都不需要执行时间。

你的任务是模拟一个 FTP 服务器在某一时间段内的运行过程。
## 输入格式

一开始你将从文件中获得 FTP 的服务器的初始信息。第一行为 $3$ 个正整数，分别表示 $\text{maxUserNumber},\text{maxServerFlux},\text{maxUserFlux}$。接下来的若干行描述 $\text{server}$ 里已有文件资源的存储情况。

第一行总是描述的根目录中的一个文件或者文件夹。

如果某一行描述的是一个文件或者文件夹那么该行的数据为 $\verb!name + 空格 + size!$，如果 $\text{size}=0$ 表示这是一个文件夹，否则表示一个大小为 $\text{size}$ 的文件。

如果某一行描述的是一个文件夹，那么接下来的若干行描述的都是这个文件夹里的内容，直到一个与之对应的减号为止。这些数据都是递归描述的。因为一开始就是描述整个根目录里的文件和文件夹，所以文件信息的最后一行也为减号。（参看输入示例）。

下面的每一行为 $\verb!time + 空格 + order!$ 的形式给出，例如 $\verb!4 ares connect 1!$ 表示：在服务器开启后 $4$ 秒钟，名叫 $\verb!ares!$ 的用户请求以 $\text{uploadUser}$ 的身份连接到服务器上来。

输入的最后一行为一个字符串 $\verb!down!$。

所有输入命令的时刻 $\text{time}$ 都以命令出现的先后递增，同一时刻的命令以输入中出现的先后顺序确定其执行顺序。

## 输出格式

请你将每一条命令的反馈信息输出。

## 样例

### 样例输入 #1
```
5 200 200
unzip.exe 100
xxxx 50
bin 0
tpx.exe 200
turbo.exe 300
tpx.tp 400
temp 0
-
-
readme.txt 100
-
0 ares connect 2
0 ares download zip.exe
1 ares download bin
5 ares download xxxx
6 ares cd bin
6 ares connect 1
6 ares quit
7 ares connect 1
7 rosen connect 2
7 ares cd bin
8 ares upload A 300
9 rosen download bin
10 rosen download bin
down

```
### 样例输出 #1
```
success
unsuccess
success
unsuccess
success
unsuccess
success
success
success
success
success
unsuccess
success

```
## 提示

来源：HNOI2004 经过修改。



---

---
title: "[HNOI2003] 多边形"
layout: "post"
diff: 省选/NOI-
pid: P2283
tag: ['模拟', '贪心', '2003', '各省省选', '湖南', '深度优先搜索 DFS']
---
# [HNOI2003] 多边形
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1330.png)

## 输入格式

输入文件名：input.txt

输入文件第一行是一个自然数N，表示多边形的顶点数。N不超过1500。之后N行每行两个整数(用空格分开)，依次表示多边形的每个顶点的坐标。

## 输出格式

输出文件名：output.txt

输出文件仅1行，是阴影部分的面积，保留2位小数。

## 样例

### 样例输入 #1
```
5									

0 0

0 6

6 6

6 0

3 3


```
### 样例输出 #1
```
9.00
```


---

---
title: "[SCOI2007] 蜥蜴"
layout: "post"
diff: 省选/NOI-
pid: P2472
tag: ['模拟', '2007', '四川', '各省省选', '网络流']
---
# [SCOI2007] 蜥蜴
## 题目描述

在一个 $r$ 行 $c$ 列的网格地图中有一些高度不同的石柱，第 $i$ 行 $j$ 列的石柱高度为 $h_{i,j}$。

一些石柱上站着一些蜥蜴，你的任务是让尽量多的蜥蜴逃到边界外。

每行每列中相邻石柱的距离为 $1$，蜥蜴的跳跃距离是 $d$，即蜥蜴可以跳到**平面距离**不超过 $d$ 的任何一个石柱上。

石柱都不稳定，每次当蜥蜴跳跃时，所离开的石柱高度减 $1$（如果仍然落在地图内部，则到达的石柱高度不变）。

如果该石柱原来高度为 $1$，则蜥蜴离开后消失，以后其他蜥蜴不能落脚。

任何时刻不能有两只蜥蜴在同一个石柱上。
## 输入格式


#### 输入格式
输入第一行为三个整数 $r,c,d$，即地图的规模与最大跳跃距离。

接下来 $r$ 行每行 $c$ 个数字为石柱的初始状态，$0$ 表示没有石柱，否则表示石柱的初始高度 $h_{i,j}$。

接下来 $r$ 行每行 $c$ 个字符为蜥蜴位置，`L` 表示蜥蜴，`.` 表示没有蜥蜴。
## 输出格式

输出仅一行，包含一个整数，即无法逃离的蜥蜴总数的最小值。
## 样例

### 样例输入 #1
```
5 8 2
00000000
02000000
00321100
02000000
00000000
........
........
..LLLL..
........
........

```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据满足：$1\le r,c\le20$，$1\le d\le 4$，$1\le h\le 3$。


---

---
title: "[SDOI2010] 猪国杀"
layout: "post"
diff: 省选/NOI-
pid: P2482
tag: ['模拟', '字符串', '2010', '各省省选', '山东']
---
# [SDOI2010] 猪国杀
## 题目描述

### 游戏背景

《猪国杀》是一种多猪牌类回合制游戏，一共有 $3$ 种角色：主猪，忠猪，反猪。每局游戏主猪有且只有 $1$ 只，忠猪和反猪可以有多只，每只猪扮演 $1 $ 种角色。

### 游戏目的

主猪 / $\texttt{MP}$：自己存活的情况下消灭所有的反猪。  
忠猪 / $\texttt{ZP}$：不惜一切保护主猪，胜利条件与主猪相同。  
反猪 / $\texttt{FP}$：杀死主猪。

### 游戏过程

游戏开始时，每个玩家手里都会有 $4$ 张牌，且体力上限和初始体力都是 $4$ 。

开始游戏时，从主猪开始，按照逆时针方向（数据中就是按照编号从 $ 1 , 2, 3 \ldots n , 1 \ldots $ 的顺序）依次行动。

每个玩家自己的回合可以分为 2 个阶段：

* **摸牌阶段**：从牌堆顶部摸 $2$ 张牌，依次放到手牌的最右边；  
* **出牌阶段**：你可以使用任意张牌，每次使用牌的时候都使用最靠左的能够使用的牌。当然，要满足如下规则：
  1. 如果没有猪哥连弩，每个出牌阶段只能使用 $1$ 次「杀」来攻击；
  2. 任何牌被使用后被弃置（武器是装备上）；被弃置的牌以后都不能再用，即与游戏无关。

### 各种牌介绍

每张手牌用 $1$ 个字母表示，字母代表牌的种类。

#### 基本牌

- 『桃 / $\texttt{P}$』在自己的回合内，如果自己的体力值不等于体力上限，那么使用 $1$ 个桃可以为自己补充 $1$ 点体力，否则不能使用桃；桃只能对自己使用；在自己的回合外，如果自己的血变为 $0$ 或者更低，那么也可以使用。

- 『杀 / $\texttt{K}$』在自己的回合内，对攻击范围内除自己以外的 $1$ 名角色使用。如果没有被『闪』抵消，则造成 $1$ 点伤害。无论有无武器，杀的攻击范围都是 $1$。

- 『闪 / $\texttt{D}$』当你受到杀的攻击时，可以弃置 $1$ 张闪来抵消杀的效果。

#### 锦囊牌

- 『决斗 / $\texttt{F}$』出牌阶段，对除自己以外任意 $1$ 名角色使用，由目标角色先开始，自己和目标角色轮流弃置 $1$ 张杀，首先没有杀可弃的一方受到 $1$ 点伤害，另一方视为此伤害的来源。

- 『南猪入侵 / $\texttt{N}$』出牌阶段，对除你以外所有角色使用，按逆时针顺序从使用者下家开始依次结算，除非弃置 $1$ 张杀，否则受到 $1$ 点伤害。

- 『万箭齐发 / $\texttt{W}$』和南猪入侵类似，不过要弃置的不是杀而是闪。

- 『无懈可击 / $\texttt{J}$』在目标锦囊生效前抵消其效果。每次有 $1$ 张锦囊即将生效时，从使用这张锦囊的猪开始，按照逆时针顺序，依次得到使用无懈可击的机会；效果：用于决斗时，决斗无效并弃置；用于南猪入侵或万箭齐发时，当结算到某个角色时才能使用，当前角色不需弃置牌并且不会受到伤害（仅对 $1$ 个角色产生效果）；用于无懈可击时，成为目标的无懈可击被无效。

#### 装备牌

- 『猪哥连弩 / $\texttt{Z}$』武器，攻击范围 $1$ ，出牌阶段你可以使用任意张杀; 同一时刻最多只能装 $1$ 把武器；如果先前已经有了 $1$ 把武器，那么之后再装武器的话，会弃置以前的武器来装现在的武器。

### 特殊事件及概念解释

* **伤害来源**：杀、南猪入侵、万箭齐发的伤害来源均是使用该牌的猪，决斗的伤害来源如上；

* **距离**：两只猪的距离定义为沿着逆时针方向间隔的猪数 $+1$ 。即初始时 $1$ 和 $2$ 的距离为 $1$ ，但是 $2$ 和 $1$ 的距离就是 $n-1$ 。注意一个角色的死亡会导致一些猪距离的改变；

* **玩家死亡**：如果该玩家的体力降到 $0$ 或者更低，并且自己手中没有足够的桃使得自己的体力值回到 $1$ ，那么就死亡了，死亡后所有的牌（装备区，手牌区）被弃置；

* **奖励与惩罚**：反猪死亡时，最后一个伤害来源处（即使是反猪）立即摸 $3$ 张牌。忠猪死亡时，如果最后一个伤害来源是主猪，那么主猪所有装备牌、手牌被弃置。

注意：一旦达成胜利条件，游戏立刻结束，因此即使会摸 $3$ 张牌或者还有牌可以用也不用执行了。

现在，我们已经知道每只猪的角色、手牌，还有牌堆初始情况，并且假设每个角色会按照如下的行为准则进行游戏，你需要做的就是告诉小猪 iPig 最后的结果。

### 几种行为

* **献殷勤**：使用无懈可击挡下南猪入侵、万箭齐发、决斗；使用无懈可击抵消表敌意；  
* **表敌意**：对某个角色使用杀、决斗；使用无懈可击抵消献殷勤；  
* **跳忠**：即通过行动表示自己是忠猪。跳忠行动就是对主猪或对某只已经跳忠的猪献殷勤，或者对某只已经跳反的猪表敌意；  
* **跳反**：即通过行动表示自己是反猪。跳反行动就是对主猪或对某只已经跳忠的猪表敌意，或者对某只已经跳反的猪献殷勤。

**注意：忠猪不会跳反，反猪也不会跳忠；不管是忠猪还是反猪，能够跳必然跳**。

### 行动准则

#### 共性

* 每个角色如果手里有桃且生命值未满，那么必然吃掉；
* 有南猪入侵、万箭齐发、必然使用；有装备必然装上；
* 受到杀时，有闪必然弃置；
* 响应南猪入侵或者万箭齐发时候，有杀 / 闪必然弃置；
* 不会对未表明身份的猪献殷勤（**包括自己**）。

#### 特性

 - 主猪：
   + 主猪会认为「没有跳身份，且用南猪入侵 / 万箭齐发对自己造成伤害的猪」是**类**反猪（没伤害到不算，注意类反猪并没有表明身份），如果之后跳了，那么主猪会重新认识这只猪；  
   + 对于每种表敌意的方式，对逆时针方向能够执行到的第一只类反猪或者已跳反猪表；如果没有，那么就不表敌意；
   + 决斗时会不遗余力弃置杀；
   + 如果能对已经跳忠的猪或自己献殷勤，那么一定献；如果能够对已经跳反的猪表敌意，那么一定表。
 - 忠猪：
   + 对于每种表敌意的方式，对「逆时针方向能够执行到的第一只已经跳反的猪」表，如果没有，那么就不表敌意；
   + 决斗时，如果对方是主猪，那么不会弃置杀，否则，会不遗余力弃置杀；
   + 如果有机会对主猪或者已经跳忠的猪献殷勤，那么一定献。
 - 反猪：
   + 对于每种表敌意的方式，如果有机会则对主猪表，否则，对「逆时针方向能够执行到的第一只已经跳忠的猪」表，如果没有，那么就不表敌意；
   + 决斗时会不遗余力弃置杀；
   + 如果有机会对已经跳反的猪献殷勤，那么一定献。

限于 iPig 只会用 P++ 语言写 A + B，他请你用 Pigcal (Pascal)、P (C) 或 P++ (C++) 语言来帮他预测最后的结果。
## 输入格式

输入文件第一行包含两个正整数 $ n $ $ (2 \leqslant n \leqslant 10) $ 和 $m$ $ (m \leqslant 2000) $，分别代表玩家数和牌堆中牌的数量。数据保证牌的数量够用。

接下来 $n$ 行，每行 $5$ 个字符串，依次表示对第 $i$ 只猪的角色和初始 $4 $ 张手牌描述。编号为 $1$ 的肯定是主猪。

再接下来一行，一共 $m$ 个字符串，按照从牌堆顶部到牌堆底部的顺序描述每张牌。

**注意：所有的相邻的两个字符串都严格用 $1$ 个空格隔开，行尾没有多余空格**。
## 输出格式

输出数据第一行包含一个字符串代表游戏结果。如果是主猪胜利，那么输出 $\texttt{MP}$ ，否则输出 $\texttt{FP}$ 。数据保证游戏总会结束。

接下来 $n$ 行，第 $i$ 行是对第 $i$ 只猪的手牌描述（注意只需要输出手牌），按照手牌从左往右的顺序输出，相邻两张牌用 $1$ 个空格隔开，行末尾没有多余空格。如果这只猪已阵亡，那么只要输出 $\texttt{DEAD}$ 即可。

**注意：如果要输出手牌而没有手牌的话，那么只需输出 $1$ 个空行**。

**由于数据问题，若牌堆已空，按照每次抽牌抽到的都是最后一张。**
## 样例

### 样例输入 #1
```
3 10
MP D D F F
ZP N N N D
FP J J J J
F F D D J J F F K D

```
### 样例输出 #1
```
FP
DEAD
DEAD
J J J J J J D

```
## 提示

### 样例解释

第一回合：
* 主猪没有目标可以表敌意；
* 接下来忠猪使用了 $3$ 张南猪入侵，主猪掉了 $3$ 点体力，并认为该角色为类反猪，$3$ 号角色尽管手里有无懈可击，但是因为自己未表明身份，所以同样不能对自己用，乖乖掉 $3$ 点体力；  

下一回合：
* 反猪无牌可出；
* 接下来主猪对着类反猪爆发，使用 $4$ 张决斗，忠猪死亡，结果主猪弃掉所有牌；
* 下来反猪摸到 $1$ 张杀直接杀死主猪获胜。

### 子任务

一共 $20$ 组测试数据，每个点 $5$ 分。

$10\%$ 的数据没有锦囊牌，另外 $20\%$ 的数据没有无懈可击。


---

---
title: "[SCOI2008] 警告"
layout: "post"
diff: 省选/NOI-
pid: P2509
tag: ['模拟', '2008', '四川', '各省省选']
---
# [SCOI2008] 警告
## 题目描述

有一个简单的脚本语言，只有赋值语句、条件语句和返回语句三种。变量名必须是单个大写字母，且变量都是 $32$ 位带符号整数。

该语言的每条语句必须单独占一行。程序中不含空行，且每行的行首行末均无空格。每行的不同 token 之间用单个空格隔开。该语言的 BNF 如下：

```cpp
<line> :: <head> | <assignment> | <if> | ELSE | END IF | <return>
<head> :: PARAM <paramlist> | PARAM
<assignment> :: <variable> = <rvalue>
<if> :: IF <variable> <relation> <value> THEN
<return> :: RETURN <value>
<paramlist> :: <variable> | <variable> <paramlist>
<rvalue> :: <value> | <value> <operator> <value>
<value> :: <variable> | <integer>
<operator> :: + | - | * | /
<relation> :: < | = | >
<variable> :: A | B | ... | Z
<integer> :: 不含前导 0 的 32 位带符号整数
```
程序的第一行是一条 `<head>` 语句，定义了函数的参数，而最后一行一定是 `<return>` 语句。`<head>` 语句不能在除了第一行之外的其他任何地方出现，但 `<return>` 语句可以在程序中多次出现。行号从 $1$ 开始编号。
每条 `IF` 语句一定有一个配套的 `END IF` 语句，还有一个可选的 `ELSE` 语句（注意没有 `ELSE IF` 语句）。`IF` 语句可以嵌套，它总是比较一个变量和一个整数或者另一个变量。

你应该分析一个给定的程序，并输出两类警告信息（格式见样例输出）：

- 第一类警告：无法到达的代码行。不管各条 `IF` 语句的布尔表达式是真还是假（假设每条 `IF` 语句的布尔表达式都是既可能为真也可能为假，不受其他 `IF` 语句结果影响）。

- 第二类警告：可能未初始化的变量。该语句用到了某个变量的值，但这个变量既不在第一行指定的参数列表里，也没有在此之前由赋值语句赋值过。如果这条语句无法到达，那么不应该给出这类警告。

注意，语句 `ELSE` 和 `END IF` 不是可执行语句，因此不应该收到任何警告信息。

## 输入格式

最多包含 $50$ 行，即你要处理的程序。保证该程序合法。

## 输出格式

警告按照行号从小到大排序。如果同一行内有多个可能未初始化的变量，按照字母顺序从小到大排列。如果没有任何警告信息，你的输出应该为空。
## 样例

### 样例输入 #1
```
PARAM A B

IF A > 5 THEN

C = B * A

END IF

D = B - C

Z = Y + X

E = T

F = E + E

V = G + G

RETURN F
```
### 样例输出 #1
```
Line 5: variable C might not have been

initialized

Line 6: variable X might not have been

initialized

Line 6: variable Y might not have been

initialized

Line 7: variable T might not have been

initialized

Line 9: variable G might not have been

initialized
```
### 样例输入 #2
```
PARAM G

RETURN G

B = K

RETURN C
```
### 样例输出 #2
```
Line 3: unreachable code

Line 4: unreachable code
```
### 样例输入 #3
```
PARAM T C

B = T

A = 4

IF A < 4 THEN

IF B > 3 THEN

Q = 100 + F

ELSE

IF C = -1111111111 THEN

Q = T - A

IF Q = 0 THEN

V = V - 1

END IF

ELSE

RETURN I

E = A

END IF

END IF

ELSE

Q = 1

END IF

RETURN Q
```
### 样例输出 #3
```
Line 6: variable F might not have been

initialized

Line 11: variable V might not have

been initialized

Line 14: variable I might not have

been initialized

Line 15: unreachable code
```


---

---
title: "[ZJOI2008] 杀蚂蚁"
layout: "post"
diff: 省选/NOI-
pid: P2586
tag: ['模拟', '2008', '各省省选', '浙江']
---
# [ZJOI2008] 杀蚂蚁
## 题目描述

最近，佳佳迷上了一款好玩的小游戏：antbuster。

游戏规则非常简单：在一张地图上，左上角是蚂蚁窝，右下角是蛋糕，蚂蚁会源源不断地从窝里爬出来，试图把蛋糕搬回蚂蚁窝。而你的任务，就是用原始资金以及杀蚂蚁获得的奖金造防御塔，杀掉这些试图跟你抢蛋糕的蚂蚁~

为了拿到尽可能高的分数，佳佳设计了很多种造塔的方案，但在尝试了其中的一小部分后，佳佳发现，这个游戏实在是太费时间了。为了节省时间，佳佳决定写个程序，对于每一种方案，模拟游戏进程，根据效果来判断方案的优劣。

根据自己在游戏中积累的一些经验，以及上网搜到的一些参数，佳佳猜了蚂蚁爬行的算法，并且假设游戏中的蚂蚁也是按这个规则选择路线：

1. 每一秒钟开始的时候，蚂蚁都在平面中的某个整点上。如果蚂蚁没有扛着蛋糕，它会在该点留下 $2$ 单位的信息素，否则它会留下 $5$ 单位的信息素。然后蚂蚁会在正北、正南、正东、正西四个方向中选择一个爬过去。

2. 选择方向的规则是：首先，爬完一个单位长度后到达的那个点上，不能有其他蚂蚁或是防御塔，并且那个点不能是蚂蚁上一秒所在的点（除非上一个时刻蚂蚁就被卡住，且这个时刻它仍无法动），当然，蚂蚁也不会爬出地图的边界（我们定义这些点为不可达点）。如果此时有多个选择，蚂蚁会选择信息素最多的那个点爬过去。

3. 如果此时仍有多种选择，蚂蚁先面向正东，如果正东不是可选择的某个方向，它会顺时针转 $90^\degree$，再次判断，如果还不是，再顺时针旋转 $90^\degree$，直到找到可以去的方向。

4. 如果将每只蚂蚁在洞口出现的时间作为它的活动时间的第 $1$ 秒，那么每当这只蚂蚁的活动时间秒数为 $5$ 的倍数的时候，它先按规则 $1\sim 3$ 确定一个方向，面对该方向后逆时针转 $90^\degree$，若它沿当前方向会走到一个不可达点，它会不停地每次逆时针转 $90^\degree$，直到它面对着一个可达的点，这样定下的方向才是蚂蚁最终要爬去的方向。

5. 如果蚂蚁的四周都是不可达点，那么蚂蚁在这一秒内会选择停留在当前点。下一秒判断移动方向时，它上一秒所在点为其当前停留的点。

6. 你可以认为蚂蚁在选定方向后，瞬间移动到它的目标点，这一秒钟剩下的时间里，它就停留在目标点。

7. 蚂蚁按出生的顺序移动，出生得比较早的蚂蚁先移动。

然后，是一些有关地图的信息：

1. 每一秒，地图所有点上的信息素会损失 $1$ 单位，如果那个点上有信息素的话。

2. 地图上某些地方是炮台。炮台的坐标在输入中给出。

3. 地图的长、宽在输入中给出，对于 $n\times m$ 的地图，它的左上角坐标为 $(0,0)$，右下角坐标为 $(n,m)$。蚂蚁洞的位置为 $(0,0)$，蛋糕的位置为 $(n,m)$。

4. 你可以把蚂蚁看做一个直径为 $1$ 单位的圆，圆心位于蚂蚁所在的整点。

5. 游戏开始时，地图上没有蚂蚁，每个点上的信息素含量均为 $0$。

一些有关炮塔的信息：

1. 炮塔被放置在地图上的整点处。

2. 为了简单一些，我们认为这些炮塔都是激光塔。激光塔的射速是 $1$ 秒每次，它的攻击伤害为 $d$ 单位每次，攻击范围为 $r$。你可以认为每秒蚂蚁移动完毕后，塔才开始攻击。并且，只有当代表蚂蚁的圆的圆心与塔的直线距离不超过 $r$ 时，塔才算打得到那只蚂蚁。

3. 如果一只蚂蚁扛着蛋糕，那么它会成为 target，也就是说，任何打得到它的塔的炮口都会对准它。如果蛋糕好好地呆在原位，那么每个塔都会挑离它最近的蚂蚁进行攻击，如果有多只蚂蚁，它会选出生较早的一只。如果有蚂蚁扛着蛋糕，但是不在某个塔的攻击范围内，这个塔会选择最近的蚂蚁进行攻击。

4. 激光塔有个比较奇怪的特性：它在选定了打击目标后，只要目标在其射程内，塔到目标蚂蚁圆心的连线上的所有蚂蚁（这里“被打到”的判定变成了表示激光的线段与表示蚂蚁的圆有公共点）都会被打到并损 $d$ 格血，但激光不会穿透它的打击目标打到后面的蚂蚁。

5. 尽管在真实游戏中，塔是可以升级的，但在这里我们认为塔的布局和等级就此定了下来，不再变动。

再介绍一下蚂蚁窝：

1. 如果地图上的蚂蚁不足 $6$ 只，并且洞口（即点 $(0,0)$）没有蚂蚁，那么窝中每秒会爬出一只蚂蚁，直到地图上的蚂蚁数为 $6$ 只。

2. 刚出生的蚂蚁站在洞口。

3. 每只蚂蚁有一个级别，级别决定了蚂蚁的血量，级别为 $k$ 的蚂蚁的血量为 $\lfloor 4\times 1.1^k\rfloor$（$\lfloor x\rfloor$ 表示对 $x$ 下取整）。每被塔打一次，蚂蚁的血减少 $d$。注意，血量为 $0$ 的蚂蚁仍能精力充沛地四处乱爬，只有一只蚂蚁的血被打成负数时，它才算挂了。

4. 蚂蚁的级别是这样算的：前 $6$ 只出生的蚂蚁是 $1$ 级，第 $7\sim 12$ 只是 $2$级，依此类推第 $6k+1\sim 6k+6$ 的等级是 $k+1(k\in \Bbb{N})$。

最后给出关于蛋糕的介绍：

1. 简单起见，你可以认为此时只剩最后一块蛋糕了。如果有蚂蚁走到蛋糕的位置，并且此时蛋糕没有被扛走，那么这只蚂蚁就扛上了蛋糕。蚂蚁被打死后蛋糕回到点 $(n,m)$。

2. 如果一只扛着蛋糕的蚂蚁走到蚂蚁窝的位置，我们就认为蚂蚁成功抢到了蛋糕，游戏结束。这个回合不会对蚂蚁的年龄产生贡献。

3. 蚂蚁扛上蛋糕时，血量会增加 $\left\lfloor\dfrac{x}{2}\right\rfloor$（$x$ 表示蚂蚁出生时的血量），但不会超过蚂蚁的血量上限。

整理一下 $1$ 秒钟内发生的事件：

1. $1$ 秒的最初，如果地图上蚂蚁数不足 $6$，一只蚂蚁就会在洞口出生。

2. 接着，蚂蚁们在自己所在点留下一些信息素后，考虑移动。先出生的蚂蚁先移动。

3. 移动完毕后，如果有蚂蚁在蛋糕的位置上并且蛋糕没被拿走，它把蛋糕扛上，血量增加，并在这时被所有塔设成 target。

4. 然后所有塔同时开始攻击。如果攻击结束后那只扛着蛋糕的蚂蚁挂了，蛋糕瞬间归位。扛着蛋糕的蚂蚁死后，蛋糕会在下一秒钟所有蚂蚁移动完之后再出现。下一秒钟出现在 $(n,m)$ 的蚂蚁才会获得蛋糕。

5. 攻击结束后，如果发现扛蛋糕的蚂蚁没死并在窝的位置，就认为蚂蚁抢到了蛋糕，游戏也在此时结束。

6. 最后，地图上所有点的信息素损失 $1$ 单位。所有蚂蚁的年龄加 $1$。漫长的 $1$ 秒到此结束。
## 输入格式

输入的第一行是两个用空格隔开的正整数，$n,m$，分别表示了地图的长和宽。

第二行是三个用空格隔开的整数，$s,d,r$，依次表示炮塔的个数、单次攻击伤害以及攻击范围。

接下来 $s$ 行，每行两个用空格隔开的整数 $x,y$，描述了一个炮塔的位置。当然，蚂蚁窝的洞口以及蛋糕所在的位置上一定没有炮塔。

最后一行是一个正整数 $t$，表示我们模拟游戏的前 $t$ 秒钟。
## 输出格式

如果在第 $t$ 秒或之前蚂蚁抢到了蛋糕，输出一行 `Game over after x seconds`，其中 $x$ 为游戏结束的时间，否则输出 `The game is going on`。

如果游戏在 $t$ 秒或之前结束，输出游戏结束时所有蚂蚁的信息，否则输出 $t$ 秒后所有蚂蚁的信息。格式如下：

第一行是一个整数 $s$，表示此时活着的蚂蚁的总数。

接下来 $s$ 行，每行五个整数，依次表示一只蚂蚁的年龄（单位为秒）、等级、当前血量，以及在地图上的位置 $(a,b)$。输出按蚂蚁的年龄递减排序。
## 样例

### 样例输入 #1
```
3 5
1 1 2
2 2
5

```
### 样例输出 #1
```
The game is going on
5
5 1 3 1 4
4 1 3 0 4
3 1 3 0 3
2 1 3 0 2
1 1 4 0 1

```
## 提示

### 样例说明：

$3\times 5$ 的地图，有一个单次伤害为 $1$、攻击范围为 $2$ 的激光炮塔，它的位置为 $(2,2)$，模拟游戏的前 $5$ 秒。

$5$ 秒内有 $5$ 只蚂蚁出生，都是向东爬行，其中第 $1\sim 4$ 只在路过 $(0,2)$ 点时被激光塔射伤了 $1$ 格血。在第 $5$ 秒的时候，最早出生的蚂蚁按移动规则 $1\sim 3$ 本来该向东移动，但由于规则 $4$ 的作用，它在发现向北和向西移动都会到达不可达点后，最终选择了向南移动。

### 数据范围说明：

对于 $100\%$ 的数据，满足 $1\leqslant n,m\leqslant 8,s\leqslant 20,t\leqslant 2\times 10^5,0\leqslant d\leqslant 10^4,0\leqslant r\leqslant 15$。（这里的 $s$ 指的是炮塔的总数）。


---

---
title: "[USACO13OPEN] Yin and Yang G"
layout: "post"
diff: 省选/NOI-
pid: P3085
tag: ['模拟', '2013', 'USACO', '分治']
---
# [USACO13OPEN] Yin and Yang G
## 题目描述

Farmer John is planning his morning walk on the farm. The farm is structured like a tree: it has N barns (1 <= N <= 100,000) which are connected by N-1 edges such that he can reach any barn from any other. Farmer John wants to choose a path which starts and ends at two different barns, such that he does not traverse any edge twice. He worries that his path might be a little long, so he also wants to choose another "rest stop" barn located on this path (which is distinct from the start or the end).

Along each edge is a herd of cows, either of the Charcolais (white hair) or the Angus (black hair) variety. Being the wise man that he is, Farmer John wants to balance the forces of yin and yang that weigh upon his walk. To do so, he wishes to choose a path such that he will pass by an equal number of Charcolais herds and Angus herds-- both on the way from the start to his rest stop, and on the way from the rest stop to the end.

Farmer John is curious how many different paths he can choose that are "balanced" as described above.  Two paths are different only if they consist of different sets of edges; a path should be counted only once even if there are multiple valid "rest stop" locations along the path that make it balanced.

Please help determine the number of paths Farmer John can choose!

给出一棵n个点的树，每条边为黑色或白色。问满足以下条件的路径条数：路径上存在一个不是端点的点，使得两端点到该点的路径上两种颜色的边数都相等。

## 输入格式

\* Line 1: The integer N.

\* Lines 2..N: Three integers a\_i, b\_i and t\_i, representing the two barns that edge i connects. t\_i is 0 if the herd along that edge is Charcolais, and 1 if the  herd is Angus.

## 输出格式

\* Line 1: One integer, representing the number of possible paths Farmer John can choose from.

## 样例

### 样例输入 #1
```
7 
1 2 0 
3 1 1 
2 4 0 
5 2 0 
6 3 1 
5 7 1 

```
### 样例输出 #1
```
1 

```
## 提示

There are 7 barns and 6 edges. The edges from 1 to 2, 2 to 4 and 2 to 5 have Charcolais herds along them.


No path of length 2 can have a suitable rest stop on it, so we can only consider paths of length 4. The only path that has a suitable rest stop is 3-1-2-5-7, with a rest stop at 2.



---

---
title: "[CQOI2012] 模拟工厂"
layout: "post"
diff: 省选/NOI-
pid: P3161
tag: ['模拟', '贪心', '2012', '重庆', '各省省选']
---
# [CQOI2012] 模拟工厂
## 题目描述

有一个称为“模拟工厂”的游戏是这样的：在时刻 $0$，工厂的生产力等于 $1$。在每个时刻，你可以提高生产力或者生产商品。如果选择提高生产力，在下一个时刻时工厂的生产力加 $1$；如果选择生产商品，则下一个时刻你所拥有的商品数量增加 $p$，其中 $p$ 是本时刻工厂的生产力。  

有 $n$ 个订单，可以选择接受或者不接受。第 $i$ 个订单 $(t_i, g_i, m_i)$ 要求在时刻 $t_i$ 给买家提供 $g_i$ 个商品，事成之后商品数量减少 $g_i$，而收入增加 $m_i$ 元。如果接受订单 $i$，则必须恰好在时刻 $t_i$ 交易，不能早也不能晚。同一时刻可以接受多个订单，但每个订单只能被接受一次。要求最后的总收入最大。  

例如，如果一共有两个订单 $(5,1,8)$ 和 $(7,15,3)$，用如下策略是最优的：时刻 $0$, $1$, $2$ 提高生产力（时刻 $3$ 的生产力为 $4$），然后在时刻 $3$，$4$ 生产商品，则在时刻 $5$ 时将拥有 $8$ 个商品。此时接受第 $1$ 个订单（还会剩下 $7$ 个商品），并且在时刻 $5$，$6$ 继续生产商品，则在时刻 $7$ 时拥有 $7+4+4=15$ 个商品，正好满足订单 $2$。
## 输入格式

输入第一行包含一个整数 $n$，即订单数目。以下 $n$ 行每行三个整数 $t_i, g_i, m_i$。
## 输出格式

输出仅一行，为最大总收入。输出保证在 $32$ 位带符号整数范围内。
## 样例

### 样例输入 #1
```
2
5 1 8
7 15 3
```
### 样例输出 #1
```
11
```
## 提示

**【数据范围】**

| 编号 | $n \le$ | $t_i \le$ | $g_i \le$ | $m_i \le$ |
|:-:|:-:|:-:|:-:|:-:|
| $1 \sim 3$ | $5$ | $100$ | $10000$ | $10000$ |
| $4 \sim 6$ | $10$ | $100$ | $10000$ | $10000$ |
| $7 \sim 10$ | $15$ | $100000$ | $10^9$ | $10^9$ |


---

---
title: "[SCOI2013] 摩托车交易"
layout: "post"
diff: 省选/NOI-
pid: P3280
tag: ['模拟', '2013', '四川', '倍增', '生成树']
---
# [SCOI2013] 摩托车交易
## 题目描述

mzry1992 在打完吊针出院之后，买了辆新摩托车，开始了在周边城市的黄金运送生意。在 mzry1992 生活的地方，城市之间是用双向高速公路连接的。另外，每条高速公路有一个载重上限，即在不考虑驾驶员和摩托车重量的情况下，如果所载货物的量超过某个值，则不能驶上该条高速公路。

今年，mzry1992 一共收到了来自 $n$ 个不同城市的 $n$ 份定订单，每个订单要求卖出上限为一定量的黄金，或是要求买入上限为一定量的黄金。由于订单并不是同时发来的，为了维护生意上的名声，mzry1992 不得不按照订单发来的顺序与客户进行交易。他与第i 个客户进行交易的具体步骤是：

1. 前往第 $i$ 个客户所在城市。当然，中途是完全允许经过其他城市的。 
2. 与第 $i$ 个客户进行交易，在此过程中他希望有限制的让交易额尽量大。具体的限制有两个：    
(a) 他希望与最后一个客户完成交易后，手上没有剩余黄金。  
(b) 由于黄金是很贵重的物品，不能出现因为买入过多黄金而造成在以后的运送过程中不得不丢弃黄金的情况。

一开始，mzry1992 位于第一个订单客户所在的城市。现在有一个好消息，有人提供了 mzry1992 免费试用周边城市的列车系统的资格。具体来讲，如果mzry1992希望从 $A$ 城市到达 $B$ 城市，且 $A$、$B$ 城市均有列车站的话，他可以携带着黄金与摩托车从 $A$ 城市乘坐列车到 $B$ 城市，这里假定乘坐列车没有载重限制。

现在已知城市间的交通系统情况和订单情况，请帮助 mzry1992 计算每个向 mzry1992 购买黄金的客户的购买量。

## 输入格式

输入的第一行有三个整数 $n,m,q$，分别表示城市数，连通城市的高速公路数和有列车站的城市数。

接下来的一行有 $n$ 个数，每个数均不相同，且值介于 $1$ 到 $n$ 之间，代表订单的顺序。

第三行有 $n$ 个数，第 $i$ 个数表示 $i$ 号城市的订单的上限额 $b_i$，$b_i$ 为正值表示该订单为买入交易（针对mzry1992 而言），上限为 $b_i$，$b_i$ 为负值表示该订单为卖出交易（同样针对mzry1992 而言）上限为 $-b_i$。

接下来的 $m$ 行每行有三个数，$u, v, w$，表示城市 $u$ 和城市 $v$ 之间有一条载重上限为 $w$ 的高速公路，这里假定所有高速公路都是双向的，城市的序号是从 $1$ 到 $n$ 的。

输入的最后一行有 $q$ 个数，代表有列车站城市的序号。

## 输出格式

按照订单顺序对于每个卖出交易，输出一行，该行只有一个整数 $x$，表示卖出黄金的量。

## 样例

### 样例输入 #1
```
Sample #1
3 3 2
2 3 1
-6 5 -3
1 3 5
2 3 2
2 1 6
1 3

```
### 样例输出 #1
```
3
2


```
### 样例输入 #2
```
4 4 0
1 2 3 4
5 4 -6 -1
1 2 4
2 3 100
3 4 1
4 1 4
```
### 样例输出 #2
```
6
1 

```
## 提示

### 样例解释

第一组样例：其中一种合法的方案是最初从 $2$ 号城市买入 $5$ 单位的黄金，先走第三条高速公路到 $1$ 号城市，然后再坐列车到 $3$ 号城市，在 $3$ 号城市卖出 $3$ 单位的黄金，然后乘坐列车到 $1$ 城市，在 $1$ 号城市卖出 $2$ 单位的黄金。


第二组样例：其中一种合法的方案是最初从 $1$ 号城市买入 $4$ 单位的黄金，走第一条高速公路，在 $2$ 号城市买入 $3$ 单位的黄金，走第二条高速公路，在三城市点卖出 $6$ 单位的黄金，走第三条高速公路，在 $4$ 号城市卖出 $1$ 单位的黄金。

### 数据范围与约定

- 对于 $20\%$ 数据，$n \le 100$，$m \le 200$。
- 对于 $50\%$ 数据，$n \le 3000$，$m \le 6000$。
- 对于 $100\%$ 数据，$1 \le n \le 10^5$，$n - 1 \le m \le 2\times 10^5$，$0 \le q \le n$，$0 < |b_i| < 10^9$，$0 < w < 10^9$，保证任意两个城市之间是通过高速公路连通的。



---

---
title: "[ZJOI2014] 消棋子"
layout: "post"
diff: 省选/NOI-
pid: P3341
tag: ['模拟', '2014', '浙江', '枚举', '队列']
---
# [ZJOI2014] 消棋子
## 题目描述

消棋子是一个有趣的游戏。游戏在一个 $r \times c$ 的棋盘上进行。棋盘的每个格子，要么是空，要么是一种颜色的棋子。同一种颜色的棋子恰好有两个。

每一轮，玩家可以选择一个空格子 $(x, y)$，并选择上下左右四个方向中的两个方向，如果在这两个方向上均存在有棋子的格子，而且沿着这两个方向上第一个遇到的棋子颜色相同，那么，我们将这两个棋子拿走，并称之为合法的操作。否则称这个操作不合法，游戏不会处理这个操作。游戏的目的是消除尽量多的棋子。

给出这样一个游戏和一个人的玩法。你需要： 
1. 指出此人能消去多少棋子。 
1. 输出能消去最多棋子数量。
## 输入格式

第一行给出了整数 $r$，$c$。

第二行给出了整数 $n$，表示不同颜色数。接下来 $n$ 行，第 $i$ 行含 $4$ 个整数 $a_i$，$b_i$，$c_i$，$d_i$，表示颜色为 $i$ 的两个格子分别是 $(a_i, b_i)$，$(c_i, d_i)$。然后是一个整数 $m$，表示此人的操作数。接下来 $m$ 行，每行有 $2$ 个整数和 $2$ 个字母，代表了他选择的格子，以及两个方向。我们用 `UDLR` 分别表示上下左右。
## 输出格式

输出用空格分隔的两个数字：此人能消去多少棋子和一个整数 $k$，表示能消去最多棋子数量。
## 样例

### 样例输入 #1
```
4 4
4
1 1 1 4
1 2 3 4
1 3 3 2
4 1 2 3
6
2 3 U R
2 1 D R
2 2 L R
2 4 L D
3 1 L R
3 3 L U
```
### 样例输出 #1
```
2 4
```
## 提示

对于所有数据，$1\leq r,c,n \leq 10^5$，数据保证答案的操作数 $0\leq k \leq 10^6$。


---

---
title: "[POI 2013] POL-Polarization"
layout: "post"
diff: 省选/NOI-
pid: P3563
tag: ['模拟', '动态规划 DP', '贪心', '2013', 'POI（波兰）']
---
# [POI 2013] POL-Polarization
## 题目描述

Everyone knew it would only be a matter of time.  So what?

  Faced for years on, a peril becomes the every-day reality.

It loses its meaning...

Today the letter of the Bitotian char Bittard to the Byteotian king Byteasar  was released to the public.

Bitotia requested annexation of the whole Byteotia on pain of using  the Bit Polarizing Magnet (BPM).

If used, the BPM would make each and every road in Byteotia unidirectional.

The enemy knows only too well that this could be a fatal blow to the  minimalist Byteotian infrastructure - there is a unique way between  each pair of towns.

  How badly can the BPM damage the Byteotian infrastructure?

Determine the minimum and the maximum number of such pairs of towns that  it will still be possible to travel from one of them to the other while  observing the new roads orientation.



## 输入格式

The first line of the standard input gives a single integer ![](http://main.edu.pl/images/OI20/pol-en-tex.1.png) (![](http://main.edu.pl/images/OI20/pol-en-tex.2.png)), the number of towns in Byteotia.

The ![](http://main.edu.pl/images/OI20/pol-en-tex.3.png) lines that follow describe these roads.

Each such line holds two integers, ![](http://main.edu.pl/images/OI20/pol-en-tex.4.png) and ![](http://main.edu.pl/images/OI20/pol-en-tex.5.png) (![](http://main.edu.pl/images/OI20/pol-en-tex.6.png)),  which indicate that there is a direct road (still bidirectional at the  moment) linking the towns no. ![](http://main.edu.pl/images/OI20/pol-en-tex.7.png) and ![](http://main.edu.pl/images/OI20/pol-en-tex.8.png).

In tests worth 60% of the total points, the additional constraint ![](http://main.edu.pl/images/OI20/pol-en-tex.9.png) holds;moreover, in some of those, worth 30% of the total points, it even holds that ![](http://main.edu.pl/images/OI20/pol-en-tex.10.png).

## 输出格式

Two integers should be printed to the first and only line of the standard output.

The first number should be the minimum and the second - the maximum number  of pairs of towns which could remain connected (though in one direction  only) after the roads are polarized.

## 样例

### 样例输入 #1
```
4
1 2
1 3
1 4

```
### 样例输出 #1
```
3 5

```
## 题目翻译

给定一颗树，请给树边改成有向边，求连通的点对个数的最大最小值。点对连通，要么 $a$ 能到达 $b$，要么 $b$ 能到达 $a$。$(1\le n\le 250000)$。



---

---
title: "[USACO17OPEN] COWBASIC P"
layout: "post"
diff: 省选/NOI-
pid: P3666
tag: ['模拟', '2017', 'USACO', '矩阵乘法', '栈', '构造']
---
# [USACO17OPEN] COWBASIC P
## 题目描述

Bessie has invented a new programming language, but since there is no compiler yet, she needs your help to actually run her programs.


COWBASIC is a simple, elegant language. It has two key features: addition and MOO loops. Bessie has devised a clever solution to overflow: all addition is done modulo $10^9+7$. But Bessie's real achievement is the MOO loop, which runs a block of code a fixed number of times. MOO loops and addition can, of course, be nested.


Given a COWBASIC program, please help Bessie determine what number it returns.

## 输入格式

You are given a COWBASIC program at most 100 lines long, with each line being at most 350 characters long. A COWBASIC program is a list of statements.

There are three types of statements:

```cpp
<variable> = <expression>

<literal> MOO {
<list of statements>
}

RETURN <variable>
```

There are three types of expressions:

```cpp
<literal>

<variable>

( <expression> ) + ( <expression> )
```

A literal is a positive integer at most 100,000.

A variable is a string of at most 10 lowercase English letters.

It is guaranteed that no variable will be used or RETURNed before it is defined. It is guaranteed that RETURN will happen exactly once, on the last line of the program.
## 输出格式

Output a single positive integer, giving the value of the RETURNed variable.

## 样例

### 样例输入 #1
```
x = 1
10 MOO {
x = ( x ) + ( x )
}
RETURN x
```
### 样例输出 #1
```
1024
```
### 样例输入 #2
```
n = 1
nsq = 1
100000 MOO {
100000 MOO {
nsq = ( nsq ) + ( ( n ) + ( ( n ) + ( 1 ) ) )
n = ( n ) + ( 1 )
}
}
RETURN nsq
```
### 样例输出 #2
```
4761
```
## 提示

Scoring

In 20 percent of all test cases - MOO loops are not nested.

In another 20 percent of all test cases - The program only has 1 variable. MOO loops can be nested.

In the remaining test cases, there are no further restrictions.
## 题目翻译

### 题目描述

Bessie 发明了一种新的编程语言，但由于还没有编译器，她需要你的帮助来实际运行她的程序。

COWBASIC 是一种简单而优雅的语言。它有两个关键特性：加法和 MOO 循环。Bessie 设计了一个巧妙的解决方案来处理溢出：所有的加法都是在模 $10^9+7$ 下进行的。但 Bessie 的真正成就是 MOO 循环，它可以固定次数地运行一段代码。当然，MOO 循环和加法可以嵌套。

给定一个 COWBASIC 程序，请帮助 Bessie 确定它返回的数字。

### 输入格式

你将获得一个最多 100 行的 COWBASIC 程序，每行最多 350 个字符。一个 COWBASIC 程序是一个语句列表。

有三种类型的语句：

```cpp
<variable> = <expression>

<literal> MOO {
<list of statements>
}

RETURN <variable>
```

有三种类型的表达式：

```cpp
<literal>

<variable>

( <expression> ) + ( <expression> )
```

字面量是一个最多为 100,000 的正整数。

变量是一个最多由 10 个小写英文字母组成的字符串。

保证在定义之前不会使用或 RETURN 任何变量。保证 RETURN 恰好发生一次，并且在程序的最后一行。

### 输出格式

输出一个正整数，表示 RETURN 的变量的值。

### 说明/提示

评分

在 20% 的测试用例中，MOO 循环不会嵌套。

在另外 20% 的测试用例中，程序只有一个变量。MOO 循环可以嵌套。

在剩余的测试用例中，没有进一步的限制。


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
title: "CYaRon!语"
layout: "post"
diff: 省选/NOI-
pid: P3695
tag: ['模拟', '字符串', '洛谷原创', 'O2优化', '洛谷月赛']
---
# CYaRon!语
## 题目背景

「千歌です」（我是千歌）、「曜です」（我是曜）、「ルビィです」（我是露比）、「3人合わせて、We are CYaRon！ よろしくね！」（三人在一起，我们是CYaRon！多多指教哦！）


CYaRon!的三人在学习了编程之后，决定发明一种自己的编程语言，她们称为CYaRon!语。



(ltt: 明明是我帮她们发明的。)

可是，因为洛谷评测机这时候突然爆了，ltt没有时间再帮CYaRon!的三位小姐姐写CYaRon!语的解释器了。


于是ltt就出了这样一道题，然后等着有人交了AC程序就偷走给小姐姐们。

## 题目描述

以下是一个典型的CYaRon! 语程序。


```cpp
{ vars
    chika:int
    you:int
    ruby:array[int, 1..2]
    i:int
}
# 以上变量默认值均为0
# 变量名只可是英文字母。

# yosoro语句可以输出一个数字，随后跟一个空格。
:yosoro 2
# 输出2和一个空格(以下不再提到空格)。

# set语句可以为变量赋值。
# 运算符只支持加减号即可。
:set chika, 1
:set you, 2
:yosoro chika + you
# 上一条语句将输出3

# 以下的判断语句均使用以下的格式：
# 操作符，表达式，表达式
# 例如eq, a, 1即C语言中 a==1
# 所有操作符包括: lt: < gt: > le: <= ge: >= eq: == neq: !=

# 日本来的CYaRon三人没法正确地发出if这个音，因此她们就改成了ihu。
{ ihu eq, chika, 1
    :set you, 3
    :yosoro 1
}
# 输出1
# 以上是ihu语句，无需支持else。

# hor语句同理，
# for i=1 to you如下
{ hor i, 1, you
    :yosoro i
}
# 输出1 2 3

# 如下是while和数组的使用方法。
:set i, 1
{ while le, i, 2
    :yosoro i
    :set ruby[i], i+1
    :yosoro ruby[i]
    :set i, i+1
}
# 输出1 2 2 3

# 数组不会出现嵌套，即只会有a[i]、a[i+2]而不会有类似于a[i+b[i]]这样的。

# CYaRon语的最后一行，一定是一个换行。
 
```

你的任务是写一个CYaRon!语的解释器，实现输入CYaRon!语的程序，解释之执行后输出执行结果。

## 输入格式

输入文件全部为CYaRon!语程序，最后一行保证是个空行。

请处理输入的时候，一直读到EOF为止。

## 输出格式

该CYaRon!语程序的执行结果。

具体上，是该CYaRon!语程序所有:yosoro语句的输出。

## 样例

### 样例输入 #1
```
{ vars
    a:int
    b:int
}

:set a, 1
:set b, 2
:yosoro a+b

```
### 样例输出 #1
```
3
```
## 提示

对数据做出以下保证：

1. 输入数据一定是合法的CYaRon!语程序，不包含注释，代码、缩进风格 （四个空格）与上述样例相同。**但不保证逗号、运算符前面的空格数量和有无一定相同**。

2. 变量名在10个字符以下，仅包含小写英文，数组最大大小为1000，变量最多50个，所有表达式的运算结果，包括变量的值一定在int范围内。 （但数组可能是类似于[2001..3000]的，下标可能范围为0到1亿）

3. 所有指令小写。

4. 该程序一定能够在合理的时间、内存限制内执行完毕。

5. hor语句执行过程中，循环变量、初始值、结束值不会被循环中的代码改变。

6. **该程序最多500行**

![](https://cdn.luogu.com.cn/upload/pic/4595.png)



---

---
title: "[AH2017/HNOI2017] 单旋"
layout: "post"
diff: 省选/NOI-
pid: P3721
tag: ['模拟', '2017', '线段树', '各省省选', '离散化', '湖南', '动态树 LCT']
---
# [AH2017/HNOI2017] 单旋
## 题目描述

H国是一个热爱写代码的国家，那里的人们很小去学校学习写各种各样的数据结构。伸展树（splay）是一种数据结构，因为代码好写，功能多，效率高，掌握这种数据结构成为了H国的必修技能。有一天，邪恶的“卡”带着他的邪恶的“常数”来企图毁灭H国。“卡”给H国的人洗脑说，splay如果写成单旋的，将会更快。“卡”称“单旋splay”为“spaly”。虽说他说的很没道理，但还是有H国的人相信了，小H就是其中之一，spaly马上成为他的信仰。而H国的国王，自然不允许这样的风气蔓延，国王构造了一组数据，数据由m（不超过10^5）个操作构成，他知道这样的数据肯定打垮spaly，但是国王还有很多很多其他的事情要做，所以统计每个操作

所需要的实际代价的任务就交给你啦。数据中的操作分为5种：

1. 插入操作：向当前非空spaly中插入一个关键码为key的新孤立节点。插入方法为，先让key和根比较，如果key比根小，则往左子树走，否则往右子树走，如此反复，直到某个时刻，key比当前子树根x小，而x的左子树为空，那就让key成为x的左孩子；或者key比当前子树根x大，而x的右子树为空，那就让key成为x的右孩子。该操作的代价为：插入后，key的深度。特别地，若树为空，则直接让新节点成为一个单个节点的树。（各节点关键码互不相等。对于“深度”的解释见末尾对spaly的描述。）

2. 单旋最小值:将spaly中关键码最小的元素xmin单旋到根。操作代价为：单旋前xmin的深度。（对于单旋操作的解释见末尾对spaly的描述。）

3. 单旋最大值:将spaly中关键码最大的元素xmax单旋到根。操作代价为：单旋前xmax的深度。

4. 单旋删除最小值：先执行2号操作，然后把根删除。由于2号操作之后，根没有左子树，所以直接切断根和右子树的联系即可。（具体见样例解释）。操作代价同2号操作。

5. 单旋删除最大值：先执行3号操作，然后把根删除。操作代价同3号操作。

 ![](https://cdn.luogu.com.cn/upload/pic/5106.png) 

对于不是H国的人，你可能需要了解一些spaly的知识，才能完成国王的任务：

1. spaly是一棵二叉树，满足对于任意一个节点x，它如果有左孩子lx，那么lx的关键码小于x的关键码。如果有右孩子rx，那么rx的关键码大于x的关键码。

2. 一个节点在spaly的深度定义为：从根节点到该节点的路径上一共有多少个节点（包括自己）。

3. 单旋操作是对于一棵树上的节点x来说的。一开始，设f为x在树上的父亲。如果x为f的左孩子，那么执行zig(x)操作（如上图中，左边的树经过zig(x)变为了右边的树）,否则执行zag(x)操作（在上图中，将右边的树经过zag(f)就变成了左边的树）。每当执行一次zig(x)或者zag(x),x的深度减小1，如此反复，直到x为根。总之，单旋x就是通过反复执行zig和zag将x变为根。

## 输入格式

输入文件名为 splay.in。

第一行单独一个正整数 m (1 <= m <= 10^5)。

接下来 m 行，每行描述一个操作：首先是一个操作编号 c（ 1<=c<=5），既问题描述中给出的 5 种操作中的编号，若 c= 1，则再输入一个非负整数 key，表示新插入节点的关键码。

## 输出格式

输出文件名为 splay.out。

输出共 m 行，每行一个整数，第 i 行对应第 i 个输入的操作的代价。

## 样例

### 样例输入 #1
```
5
1 2
1 1
1 3
4 
5
```
### 样例输出 #1
```
1 
2 
2
2 
2
```
## 提示

20%的数据满足： 1 <= m <= 1000。

另外 30%的数据满足： 不存在 4,5 操作。

100%的数据满足： 1<=m<=10^5； 1<=key<=10^9。 所有出现的关键码互不相同。 任何一个非插入操作，一定保证树非空。 在未执行任何操作之前，树为空。



---

---
title: "Coloring"
layout: "post"
diff: 省选/NOI-
pid: P3936
tag: ['搜索', '洛谷原创', 'Special Judge', '模拟退火']
---
# Coloring
## 题目描述

$\text{Snakes}$正在玩游戏，他在一张画有$n*m$个格子的白纸上给方格染色。然而，杂乱无章的染色并不有趣，所以他想出了一个奇怪的问题：


在$n*m$的方格中用$c$种不同的颜色尝试将所有方格染色，不同的颜色用$1..c$间的整数表示。染色需要满足以下条件：


+ 每个方格只能且必须染一种颜色。

+ 第$i$种颜色最多可以且必须染$p_i$个格子，保证满足$\sum_{i=1}^cp_i=n*m$。

+ 将每个格子上下左右与其颜色相同的格子视为位于同一个联通块内，并定义不同联通块之间的方格边的条数为$q$。可参考样例说明。


现在，$\text{Snakes}$想知道，如果给出$n,m,c$以及$p_1..p_c$，你能够构造出的符合条件且$q$尽量小的染色方案。

## 输入格式

第一行，三个数，$n,m,c$。


第二行，$c$个数，第$i$个数为$p_i$。

## 输出格式

输出共$n$行，每行$m$个数，表示你构造出的$n*m$的$q$尽量少的染色方案。

## 样例

### 样例输入 #1
```
2 3 3
1 2 3
```
### 样例输出 #1
```
2 3 1
2 3 3
```
## 提示

```plain
   |   |   
 2 | 3 | 1 
   +   +---
 2 | 3   3 
   |       
```

对于样例，有$q=4$，其中三条竖边，一条横边。


#### 约定


本题为 Special Judge。


对于每个测试点，将会设置阈值$w$，并保证存在构造使得$q\leq w$。


对于程序输出的答案，我们将会以以下方式计算得分：


$$\begin{matrix}q&score&q&score\\\\ q \leq w&10&1.75w < q \leq 2w&5\\\\ w < q \leq 1.1w&9&2w < q \leq 2.3w&4\\\\ 1.1w < q \leq 1.25w&8&2.3w < q \leq 2.6w&3\\\\ 1.25w < q \leq 1.5w&7&2.6w < q \leq 3w&2\\\\ 1.5w < q \leq 1.75w&6&3w < q \leq 3.5w&1\end{matrix}$$


若$q > 3.5w$，将以 `Wrong Answer` 处理。


比赛时显示的得分即为最后得分。


#### 数据规模


对于$10\%$的数据，有$1\leq n,m\leq 3$，$c\leq 3$。


对于$30\%$的数据，有$1\leq n,m\leq 8$，$c\leq 6$。


对于$50\%$的数据，有$1\leq n,m\leq 15$，$c\leq 25$。


对于$100\%$的数据，有$1\leq n,m\leq 20$，$c\leq 50$，$p_i\leq 20$。



---

---
title: "[SHOI2013] 发牌"
layout: "post"
diff: 省选/NOI-
pid: P3988
tag: ['模拟', '2013', '线段树', '各省省选', '平衡树', '树状数组', '上海', '可持久化线段树']
---
# [SHOI2013] 发牌
## 题目描述

在一些扑克游戏里，如德州扑克，发牌是有讲究的。一般称呼专业的发牌手为荷官。荷官在发牌前，先要销牌（burn card）。所谓销牌，就是把当前在牌库顶的那一张牌移动到牌库底，它用来防止玩家猜牌而影响游戏。

假设一开始，荷官拿出了一副新牌，这副牌有 $N$ 张不同的牌，编号依次为 $1$ 到 $N$。由于是新牌，所以牌是按照顺序排好的，从牌库顶开始，依次为 $1,2,\cdots,N$，$N$ 号牌在牌库底。为了发完所有的牌，荷官会进行 $N$ 次发牌操作，在第 $i$ 次发牌之前，他会连续进行 $R_i$ 次销牌操作，$R_i$ 由输入给定。请问最后玩家拿到这副牌的顺序是什么样的？

举个例子，假设 $N=4$，则一开始的时候，牌库中牌的构成顺序为 $1,2,3,4$。

- 假设 $R_1=2$，则荷官应该连销两次牌，将 $1$ 和 $2$ 放入牌库底，再将 $3$ 发给玩家。目前牌库中的牌顺序为 $4,1,2$。
- 假设 $R_2=0$，荷官不需要销牌，直接将 $4$ 发给玩家，目前牌库中的牌顺序为 $1,2$。
- 假设 $R_3=3$，则荷官依次销去了 $1,2,1$，再将 $2$ 发给了玩家。目前牌库仅剩下一张牌 $1$。
- 假设 $R_4=2$，荷官在重复销去两次 $1$ 之后，还是将 $1$ 发给了玩家，这是因为 $1$ 是牌库中唯一的一张牌。
## 输入格式

第一行，一个整数 $N$，表示牌的数量。

第二行到第 $N+1$ 行，在第 $i+1$ 行，有一个整数 $R_i$。

## 输出格式

共 $N$ 行，第 $i$ 行有一个整数，表示玩家收到的第 $i$ 张牌的编号。
## 样例

### 样例输入 #1
```
4
2
0
3
2
```
### 样例输出 #1
```
3
4
2
1
```
## 提示

#### 数据规模与约定

对于 $100 \%$ 的数据，$0 \le R_i < N$。  

| 测试点编号 | $N=$ | 测试点编号 | $N=$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5\times 10^3$ | $6$ | $3\times 10^5$ |
| $2$ | $10^4$ |  $7$ | $4\times 10^5$ |
| $3$ | $5\times 10^4$ | $8$ | $5\times 10^5$ |
| $4$ | $10^5$ | $9$ | $6\times 10^5$ |
| $5$ | $2\times 10^5$ | $10$ | $7\times 10^5$ |


---

---
title: "小 Y 和地铁"
layout: "post"
diff: 省选/NOI-
pid: P4005
tag: ['模拟', '搜索', '2017', '树状数组', 'O2优化', '枚举', '模拟退火', 'CTT（清华集训/北大集训）']
---
# 小 Y 和地铁
## 题目描述

小 Y 是一个爱好旅行的 OIer。一天，她来到了一个新的城市。由于不熟悉那里的交通系统，她选择了坐地铁。

她发现每条地铁线路可以看成平面上的一条曲线，不同线路的交点处一定会设有换乘站 。通过调查得知，没有线路是环线，也没有线路与自身相交。任意两条不同的线路只会在若干个点上相交，没有重合的部分，且没有三线共点的情况。即，如图所示的情况都是不存在的：

 ![](https://cdn.luogu.com.cn/upload/pic/12055.png) 

小 Y 坐着地铁 $0$ 号线，路上依次经过了 $n$ 个换乘站。她记下了每个换乘站可以换乘的线路编号，发现每条线路与她所乘坐的线路最多只有 $2$ 个换乘站。现在小 Y 想知道，除掉她经过的换乘站以外，这个城市里最少有几个换乘站。只有你告诉她正确的答案，她才会答应下次带你去玩呢。

## 输入格式

**请注意本题有多组输入数据。**

输入数据的第一行是一个整数 $T$，表示输入数据的组数。接下来依次给出每组数据。

对于每组数据，第一行是一个整数 $n$，表示小 Y 经过的换乘站的数目。第二行为 $n$ 个用空格隔开的整数，依次表示每个换乘站的可以换乘的线路编号。这些编号都在 $1\sim n$ 之内。

## 输出格式

对于每组输入数据，输出一行一个整数，表示除掉这 $n$ 个换乘站之外，最少有几个换乘站。

## 样例

### 样例输入 #1
```
4 4
1 2 1 2
8
1 2 3 4 1 2 3 4
5
5 4 3 3 5
8
1 2 3 4 1 3 2 4
```
### 样例输出 #1
```
0 
0 
0 
1
```
## 提示

【样例 1 解释】

对于样例的前两组数据，一种可能的最优答案如下图所示。

 ![](https://cdn.luogu.com.cn/upload/pic/12053.png) 

【子任务】

一共有 $50$ 个测试点，每个测试点 $2$ 分。你只有在答案完全正确时才能得到该测试点的全部分数，否则不得分。

对于所有测试点，以及对于样例， $1 \leq T \leq 100$, $1 \leq n \leq 44$。对于每个测试点， $n$ 的范围如下表：

![](https://cdn.luogu.com.cn/upload/pic/12054.png)



---

---
title: "序列终结者"
layout: "post"
diff: 省选/NOI-
pid: P4146
tag: ['模拟', '线段树', '平衡树']
---
# 序列终结者
## 题目背景

网上有许多题，就是给定一个序列，要你支持几种操作：A、B、C、D。一看另一道题，又是一个序列要支持几种操作：D、C、B、A。尤其是我们这里的某人，出模拟试题，居然还出了一道这样的，真是没技术含量……

这样我也出一道题，我出这一道的目的是为了让大家以后做这种题目有一个“库”可以依靠，没有什么其他的意思。

这道题目就叫序列终结者吧。

## 题目描述

给定一个长度为N的序列，每个序列的元素是一个整数（废话）。要支持以下三种操作：

1. 将$[L,R]$这个区间内的所有数加上$V$。
2. 将$[L,R]$这个区间翻转，比如`1 2 3 4`变成`4 3 2 1`。
3. 求$[L,R]$这个区间中的最大值。

最开始所有元素都是$0$。

## 输入格式

第一行两个整数`N，M`。`M`为操作个数。

以下$M$行，每行最多四个整数，依次为`K，L，R，V`。`K`表示是第几种操作，如果不是第1种操作则`K`后面只有两个数。

## 输出格式

对于每个第3种操作，给出正确的回答。


## 样例

### 样例输入 #1
```
4 4
1 1 3 2
1 2 4 -1
2 1 3
3 2 4
```
### 样例输出 #1
```
2
```
## 提示

$N \le 50000,M \le 100000$。



---

---
title: "[NOI2004] 小H的小屋"
layout: "post"
diff: 省选/NOI-
pid: P4274
tag: ['动态规划 DP', '贪心', '2004', 'NOI', '模拟退火']
---
# [NOI2004] 小H的小屋
## 题目描述

小 H 发誓要做 $21$ 世纪最伟大的数学家。他认为，做数学家与做歌星一样，第一步要作好包装，不然本事再大也推不出去。为此他决定先在自己的住所上下功夫，让人一看就知道里面住着一个“未来的大数学家”。

为了描述方便，我们以向东为 $x$ 轴正方向，向北为 $y$ 轴正方向，建立平面直角坐标系。小 H 的小屋东西长为 $100$  Hil（Hil 是小 H 自己使用的长度单位，至于怎样折合成“m”，谁也不知道）。东墙和西墙均平行于 $y$ 轴，北墙和南墙分别是斜率为 $k_1$ 和 $k_2$ 的直线，$k_1$ 和 $k_2$ 为正实数。北墙和南墙的墙角处有很多块草坪，每块草坪都是一个矩形，矩形的每条边都平行于坐标轴。相邻两块草坪的接触点恰好在墙上，接触点的横坐标被称为它所在墙的“分点”，这些分点必须是 $1$ 到 $99$ 的整数。

小 H 认为，对称与不对称性的结合才能充分体现“数学美”。因此，在北墙角要有 $m$ 块草坪，在南墙角要有 $n$ 块草坪，并约定 $m \leq n$。如果记北墙和南墙的分点集合分别为 $X_1$，$X_2$，则应满足 $X_1 \subseteq X_2$，即北墙的任何一个分点一定是南墙的分点。

由于小 H 目前还没有丰厚的收入，他必须把草坪的造价降到最低，即草坪
的占地总面积最小。你能编程帮他解决这个难题吗？
## 输入格式

仅一行，包含 $4$ 个数 $k_1$，$k_2$，$m$，$n$。$k_1$ 和 $k_2$ 为正实数，分别表示北墙和南墙的斜率，精确到小数点后第一位。$m$ 和 $n$ 为正整数，分别表示北墙角和南墙角的草坪的块数。
## 输出格式

一个实数，表示草坪的最小占地总面积。精确到小数点后第一位。
## 样例

### 样例输入 #1
```
0.5 0.2 2 4
```
### 样例输出 #1
```
3000.0
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/y83es0b9.png)
【约定】

○ $2 \leq m \leq n \leq 100$

○ 南北墙距离很远，不会出现南墙草坪和北墙草坪重叠的情况


---

---
title: "封兽鵺的激光游戏"
layout: "post"
diff: 省选/NOI-
pid: P4276
tag: ['模拟', '计算几何', '枚举']
---
# 封兽鵺的激光游戏
## 题目背景

#盛大的宴会已经开始
![](https://cdn.luogu.com.cn/upload/pic/15071.png)
## 题目描述

在你的帮助下，萃香终于在一天内送出了所有的请柬。

夜幕低垂，随着由河城荷取提供的烟花"嗖"的一声蹿上天际，这场盛大的宴会终于如期开始。

顷刻之间，偌大的会场就已经被大家的欢声笑语充满：萃香和勇仪把酒言欢，散发着醉醺醺的酒香；帕秋莉和爱丽丝拽着魔理沙的两只胳膊争论着先逛哪边；琪露诺和大妖精在地上写写画画钻研着数学难题......一切都显得和谐而美满。

可是，随着会场愈发热闹，宴会的举办者萃香总感觉还是少了些什么，转念一想，她方才发觉自己没有准备游戏活动。没有游戏的宴会又怎能叫做宴会？为了解决这个严重的问题，萃香放下了酒葫芦，找到了路边的封兽鵺请她帮忙。

这可愁死封兽鵺啦！只擅长搞事情和打马赛克的她苦思冥想，终于想出了一个好主意，于是她将自己的UFO翻出来一些，再找圣白莲借几束激光，而下面就是封兽鵺制定的游戏规则：

封兽鵺在平面上放置了一些实心的质量均匀的UFO(可视为凸多边形)，由于她的能力有限，所以这些UFO最多只有五条边。现在你可以从一给定点向任意方向发射一束激光(x轴正方向为0°，y轴正方形为90°，保证发射角度为两位小数，即激光从0°开始旋转，每次旋转0.01°)，激光碰到UFO的边界便会发生反射，且激光每反射一次能量便会增加w(初始能量为0)，这里要注意的是，每当一条边被激光打中过一次后便会失去反射的能力变成一条可以直接透过的边，这时候你的激光可以直接穿进UFO的内部从内部进行反射。

如果你还没有理解，封兽鵺已经贴心的为你准备了下面这张图：
![](https://cdn.luogu.com.cn/upload/pic/15112.png)

本来唯恐天下不乱的封兽鵺想让激光射出时能量最大，但是萃香担心会场被破坏而将"能量最大"改为"能量最接近一整数E"。同时为了保证游戏的难度，封兽鵺会在游戏开始前将每个UFO绕重心顺时针旋转k*90°。

现在，轮到了你参加这个游戏，如果你射出激光的角度与封兽鵺的答案相符，那么你就会获得两份奖励——100分和封兽鵺的写真集！

当然，拥有电脑的你当然不会一次一次去试，而是通过编程预先解决这个问题，然后真正实践的时候直接用最优解拔得头筹。
## 输入格式

第一行一个整数n，为UFO的数量。

之后n行每行一个整数m，随后有m个实数对x[i],y[i]表示按顺时针顺序给出的UFO的m个顶点。

之后n行每行一个整数k，表示将该UFO顺时针旋转k*90°。

第2n+2行两个整数w和E，分别为每次反射激光的能量增量及规定的接近量。

最后一行两个实数x0，y0表示激光的射出点。
## 输出格式

一个实数d，保留到两位小数，表示使激光出射能量最接近E的出射角度。(如果有多个解符合题意，请输出角度最小的那个)
## 样例

### 样例输入 #1
```
2
4 0 0 0 4 4 4 4 0
3 8 0 12 4 12 0
0 
0
1 2
5 5
```
### 样例输出 #1
```
300.97
```
## 提示

【样例解释】：

如图所示，当激光射出偏角为300.97度时恰好能反射两次，E1-2*w=2=E，符合题意
![](https://cdn.luogu.com.cn/upload/pic/15105.png)

#你需要特别注意的一些事:
1. 当一束激光碰到UFO顶点的时候不认为它们相撞
2. 多边形不会重叠，初始激光射出点不会在UFO上或UFO内
3. 不要在这里讲科学，所以激光可以射到UFO内部进行反射


【数据范围】：

![](https://cdn.luogu.com.cn/upload/pic/15115.png)

奖励：

![](https://cdn.luogu.com.cn/upload/pic/15074.png)

(没错就是zun绘写真集，如果你AC了此题就可以获得)



---

---
title: "[HAOI2008] 排名系统"
layout: "post"
diff: 省选/NOI-
pid: P4291
tag: ['模拟', '字符串', '2008', '河南', '各省省选', '平衡树']
---
# [HAOI2008] 排名系统
## 题目描述

排名系统通常要应付三种请求：上传一条新的得分记录、查询某个玩家的当前排名以及返回某个区段内的排名记录。当某个玩家上传自己最新的得分记录时，他原有的得分记录会被删除。为了减轻服务器负担，在返回某个区段内的排名记录时，最多返回10条记录。
## 输入格式

第一行是一个整数n（10<=n<=250000）表示请求总数目。接下来n行,每行包含了一个请求。请求的具体格式如下：

+Name Score 上传最新得分记录。Name表示玩家名字，由大写英文字母组成，不超过10个字符。Score为最多8位的正整数。

?Name 查询玩家排名。该玩家的得分记录必定已经在前面上传。如果两个玩家的得分相同，则先得到该得分的玩家排在前面。

?Index 返回自第Index名开始的最多10名玩家名字。Index必定合法，即不小于1，也不大于当前有记录的玩家总数。
## 输出格式

对于?Name格式的请求，应输出一个整数表示该玩家当前的排名。

对于?Index格式的请求，应在一行中依次输出从第Index名开始的最多10名玩家姓名，用一个空格分隔。
## 样例

### 样例输入 #1
```
20
+ADAM 1000000
+BOB 1000000
+TOM 2000000
+CATHY 10000000
?TOM
?1
+DAM 100000
+BOB 1200000
+ADAM 900000
+FRANK 12340000
+LEO 9000000
+KAINE 9000000
+GRACE 8000000
+WALT 9000000
+SANDY 8000000
+MICK 9000000
+JACK 7320000
?2
?5
?KAINE
```
### 样例输出 #1
```
2
CATHY TOM ADAM BOB
CATHY LEO KAINE WALT MICK GRACE SANDY JACK TOM BOB
WALT MICK GRACE SANDY JACK TOM BOB ADAM DAM
4
```
## 提示

20%数据满足N<=100

100%数据满足N<=250000


---

---
title: "[SHOI2014] 三叉神经树"
layout: "post"
diff: 省选/NOI-
pid: P4332
tag: ['模拟', '2014', '线段树', '各省省选', '上海', 'O2优化', '分治', '树链剖分', '动态树 LCT']
---
# [SHOI2014] 三叉神经树
## 题目描述

计算神经学作为新兴的交叉学科近些年来一直是学术界的热点。一种叫做 SHOI 的神经组织因为其和近日发现的化合物 SHTSC 的密切联系引起了人们的极大关注。

SHOI 组织由若干个 SHOI 细胞构成，SHOI 细胞之间形成严密的树形结构。每个 SHOI 细胞都有且只有一个输出端,被称为轴突,除了一个特殊的、被称为根细胞的 SHOI 细胞的输出作为整个组织的输出以外,其余细胞的轴突均连向其上级 SHOI 细胞；并且有且只有三个接收端,被称为树突,从其下级细胞或者其它神经组织那里接收信息。SHOI 细胞的信号机制较为简单,仅有 $0$和 $1$ 两种。每个 SHOI 细胞根据三个输入端中 $0$和 $1$ 信号的多寡输出较多的那一种。

现在给出了一段 SHOI 组织的信息，以及外部神经组织的输入变化情况。请你模拟 SHOI 组织的输出结果。
## 输入格式

输入的第一行包含一个整数 $n$。表示 SHOI 组织的总细胞个数。SHOI 细胞由 $1\sim n$ 编号,编号为 $1$ 的是根细胞。

从第二行开始的 $n$ 行,每行三个整数 $x_1, x_2, x_3$，分别表示编号为 $1\sim n$ 的 SHOI 细胞的树突连接。$1 < x_i \leq n$ 表示连向编号为 $x_i$ 的细胞的轴突, $n < x_i \leq 3n+1$ 表示连向编号为 $x_i$ 的外界输入。输入数据保证给出的 SHOI 组织是合法的，且所有的 $x_i$ 两两不同。

接下来一行包含 $2n+1$ 个整数（$0$ 或者 $1$），表示初始时的外界输入。

第 $n+3$ 行有一个整数 $q$，表示总操作数。

之后 $q$ 行，每行一个整数 $x$，表示编号为 $x$ 的外界输入发生了变化。
## 输出格式

输出共 $q$ 行，每行一个整数，对应第 $i$ 次外界输入变化后的根细胞的输出。
## 样例

### 样例输入 #1
```
3
2 3 4
5 6 7
8 9 10
0 0 0 0 1 1 1
5
4
4
5
6
8

```
### 样例输出 #1
```
1
0
0
1
1

```
## 提示

- 对于 $10 \%$ 的数据，满足 $1\le n \leq 10^3$，$ 1\le q \leq 10^3$。
- 对于 $30 \%$ 的数据，满足 $1\le n \leq 10^5$，$ 1\le q \leq 10^5$。
- 对于 $100 \%$ 的数据，满足 $1\le n \leq 5\times 10^5$，$ 1\le q \leq 5\times 10^5$。


---

---
title: "[CEOI 2004] 锯木厂选址"
layout: "post"
diff: 省选/NOI-
pid: P4360
tag: ['模拟', '动态规划 DP', '2004', '单调队列', 'CEOI（中欧）', '模拟退火', '斜率优化']
---
# [CEOI 2004] 锯木厂选址
## 题目描述

从山顶上到山底下沿着一条直线种植了 $n$ 棵老树。当地的政府决定把他们砍下来。为了不浪费任何一棵木材，树被砍倒后要运送到锯木厂。 

木材只能朝山下运。山脚下有一个锯木厂。另外两个锯木厂将新修建在山路上。你必须决定在哪里修建这两个锯木厂，使得运输的费用总和最小。假定运输每公斤木材每米需要一分钱。 

你的任务是编写一个程序，从输入文件中读入树的个数和他们的重量与位置，计算最小运输费用。
## 输入格式

输入的第一行为一个正整数 $n$ ——树的个数 $(2\leq n\leq 20000)$。树从山顶到山脚按照 $1,2,\dots,n$ 标号。 

接下来 $n$ 行，每行有两个正整数（用空格分开）。 

第 $i+1$ 行含有：$w_i$ ——第 $i$ 棵树的重量（公斤为单位）和 $d_i$——第 $i$ 棵树和第 $i+1$ 棵树之间的距离， $1\leq w_i\leq 10000,0\leq d_i\leq 10000$。 

最后一颗树的 $d_n$，表示第 $n$ 棵树到山脚的锯木厂的距离。保证所有树运到山脚的锯木厂所需要的费用小于 $2\times 10^9$ 分。
## 输出格式

输出最小的运输费用。
## 样例

### 样例输入 #1
```
9 
1 2 
2 1 
3 3 
1 1 
3 2 
1 6 
2 1 
1 2 
1 1

```
### 样例输出 #1
```
26
```
## 提示

样例图示，黑点为锯木厂

![](https://cdn.luogu.com.cn/upload/pic/16339.png)

本题共有 $13$ 个测试点，每个测试点的数据范围如下

测试点 $1\sim 5$：$n\leq 200$；

测试点 $6\sim7$：$n\leq 1000$；

测试点 $7\sim13$：$2\leq n\leq 20000$；


---

---
title: "[TJOI2018] 教科书般的亵渎"
layout: "post"
diff: 省选/NOI-
pid: P4593
tag: ['模拟', '递推', '2018', '各省省选', '天津', '差分']
---
# [TJOI2018] 教科书般的亵渎
## 题目描述

小豆喜欢玩游戏，现在他在玩一个游戏遇到这样的场面，每个怪的血量为 $a_i$，且每个怪物血量均不相同，小豆手里有无限张“亵渎”。亵渎的效果是对所有的怪造成 $1$ 点伤害，如果有怪死亡，则再次施放该法术。我们认为血量为 $0$ 怪物死亡。

小豆使用一张“亵渎”会获得一定的分数，分数计算如下，在使用一张“亵渎”之后，每一个被亵渎造成伤害的怪会产生 $x^k$，其中 $x$ 是造成伤害前怪的血量为 $x$ 和需要杀死所有怪物所需的“亵渎”的张数 $k$。
## 输入格式

第一行输入一个 $T$（$T\leq10$），表示有多少组测试数据。

每组测试数据第一行为 $n$，$m$，表示有当前怪物最高的血量 $n$，和 $m$ 种没有出现的血量。

接下来 $m$ 行，每行 $1$ 个数 $a_i$，表示场上没有血量为 $a_i$ 的怪物。
## 输出格式

一共 $T$ 行，每行一个数，第 $i$ 行表示第 $i$ 组测试数据中小豆的最后可以获得的分数，因为这个分数会很大需要模 $10^9+7$。
## 样例

### 样例输入 #1
```
2
10 1
5
4 2
1
2
```
### 样例输出 #1
```
415
135
```
## 提示

- 对于 $10\%$ 的数据，有 $m=0$；
- 对于 $20\%$ 的数据，有 $m\leq1$；
- 对于 $30\%$ 的数据，有 $m\leq2$
- 对于 $40\%$ 的数据，有 $m\leq3$；
- 对于 $50\%$ 的数据，有 $m\leq4$；
- 对于 $60\%$ 的数据，有 $m\leq5$；
- 对于 $100\%$ 的数据，有 $m\leq50$，$n\leq10^{13}$，$1 \le a_i <n$。


---

---
title: "河童重工的计算机"
layout: "post"
diff: 省选/NOI-
pid: P4911
tag: ['模拟', '字符串', '栈']
---
# 河童重工的计算机
## 题目背景

河童重工业会社的计算机产品在幻想乡中有着极其广泛的应用。

有一天，妖怪之山发大水啦！洪水夹杂着泥沙和滚木汹涌着冲进了河童的城市。

本来河童们的机械设施都是防水的，可是洪水还是对城市造成了不小的破坏。其中，河童们的服务器被砸坏了！

坏掉的电脑在短时间内不能修复，可是幻想乡里的许多事情都离不开河童们的服务器！河童们也很无奈，于是荷取找到了你！你作为一名优秀的信竞选手，决定帮助荷取，减轻服务器故障所带来的压力。
## 题目描述

你从荷取那里得到了一份纸质资料，扫描版在这里：

[Ktx-65式微处理器汇编语言规范文件.pdf](https://www.touhou-oi.tk/uploads/Ktx-65%E5%BC%8F%E5%BE%AE%E5%A4%84%E7%90%86%E5%99%A8%E6%B1%87%E7%BC%96%E8%AF%AD%E8%A8%80%E8%A7%84%E8%8C%83%E6%96%87%E4%BB%B6.pdf)

（若此网站无法打开，请在附件中下载）

（为什么说是扫描版呢，因为，你应该不能复制里面的文字）

以下这一段是汇编教程附带的示例：
```asm
[ progfunc.asm ]
[ Shows the function functionailties of the KTX-65 ALI ]

[main]
wint #line;    [output the current physical line number]
wch 13;        [putchar \r]
wch 10;        [putchar \n]
callfunc $Function1;
callfunc $Function2;
hlt;           [halt]

function $Function1;
rint %r1;      [read int]
add %r2 1 %r2; [loop contents]
lle %r2 %r1;   [loop conditions]
jif 2;         [end loop conditional jump]
wint %r2;      [output int]
wch 13;        [putchar \r]
wch 10;        [putchar \n]
ret;           [return]

function $Function2;
rint %r1;      [read int]
rint %r2;      [read int]
add %r1, %r2;  [add]
wint %val;     [output value]
wch 13;        [putchar \r]
wch 10;        [putchar \n]
ret;           [return]
```
你需要用洛谷评测机支持的语言编写一个程序，它读入一个Ktx-65汇编语言程序和一段输入，解释运行这个程序，然后输出这个程序输出的东西。
## 输入格式

第一行是一个整数N，表示汇编程序的行数。

接下来N行是这个汇编程序，保证不会出现空行。

接下来的所有行都是这个汇编程序的输入。
## 输出格式

一堆东西，表示这个汇编程序的输出。

~~**评测系统将以逐字节比较的方式判断你的输出是否正确。**~~假的，洛谷不支持
## 样例

### 样例输入 #1
```
5
rint %r1;
rint %r2;
add %r1 %r2;
wint;
hlt;
5 4
```
### 样例输出 #1
```
9
```
## 提示



**注意**：样例输出中只有9这一个字节。

**保证一行中只有一个指令。**

对于10%的数据：程序中只有输入和输出的指令，且不会出现数字常量，也不会有注释。

对于另外10%：程序中只有输入、输出和加法指令，且没有注释。

对于另外30%：包括除函数调用和跳转在内的所有指令。

对于剩下50%：指令没有限制。

对于全部的数据：命令条数不超过50000条，剩余输入不超过500千字节，程序需要执行的步数不超过80000步。

保证汇编程序和数据不出现编译或是运行时错误。

保证程序输入足够满足汇编程序中读入的需要。

不保证这是或不是一道毒瘤题

不保证考试时会不会有人AC这道题

不保证这次考试会不会有人AK

保证出题人为：[洩矢诹访子](https://www.luogu.org/space/show?uid=53151)

考试时打不开河童给的文件可以向我索要，不保证是否会回答

~~其实这道题数据非常简单，只是量大而已~~


---

---
title: "基地建设"
layout: "post"
diff: 省选/NOI-
pid: P4966
tag: ['2018', 'Special Judge', 'O2优化', '模拟退火', '生成树']
---
# 基地建设
## 题目背景

在茫茫宇宙中……
## 题目描述

有一群生物 ccj，他们发现了一个超星系群。其中有 $n$ 个恒星，$m$ 条双向星际航线，每条星际航线都需要消耗 $val_i$ 的燃料值。两个恒星不属于同一个星系当且仅当他们之间没有任何航线，且没有任何路径可以到达。只有每个恒星才可以为飞船补充燃料。每次航行的路线都是一条简单路径。由于燃料系统过于简陋，每个燃料罐只能用于一次航行。他们的首长 ccj 想在其中一个恒星上建立基地。但是 ccj 花了太多钱购买高速飞船，没有太多钱购买燃料罐，所以他对于两个恒星之间的航行一定选择最经济的航行方式，购买最小的燃料罐。他想问你，在基地要备多少的燃料总量，使得在任意一个恒星上建立基地都能从那个基地分别到达那个星系的其他所有恒星。

但是，这个超星系群发生了战争，一些黑洞改变了这里的空间结构。这群生物只知道每条航线花费的燃料值，找不到连接的两个恒星。但是他们的科学家发现了一个性质：每个战争有一个标志值 $q$，航线有不同的排列方式，对于其中一种排列，第 $i$ 条航线连接着 $((q^{i} \bmod 2^{32}+i \times val_i) \bmod n+n) \bmod n+1$ 和 $((q^{i} \bmod 2^{32}-i \times val_i) \bmod n+n) \bmod n+1$ 两个恒星。**运算方式为无符号整型运算**。如果连接的两个恒星一样，说明科学家计算有误，忽略这条航线。ccj 的目标改变了。他想知道对于所有星系的构成情况，最少需要准备多少的燃料总量，使得在这种结构中，在任意一个恒星上建立基地都能分别到达该结构下那个恒星所处星系的其他所有恒星。

你需要输出航线排列顺序。

## 输入格式

第一行三个正整数 $n$，$m$ 和 $q$，表示有 $n$ 个恒星，$m$ 条航线，战争标志值 $q$。

第二行 $m$ 个正整数 $val_i$，表示第 $i$ 条航线消耗 $val_i$ 的燃料值。
## 输出格式

第一行一个正整数 $ans$，表示 ccj 需要你求的数值。

从第二行到第 $m+1$ 行，每行输出一个整数，第 $i$ 行输出这个排列下的 $val_{i-1}$。
## 样例

### 样例输入 #1
```
3 5 2
1 2 3 4 5

```
### 样例输出 #1
```
1
5
4
2
3
1

```
## 提示

**样例解释：**

这 $5$ 条航线分别是：

$2$ 与 $2$ 往返，花费燃料 $5$

$1$ 与 $1$ 往返，花费燃料 $4$

$3$ 与 $3$ 往返，花费燃料 $2$

$2$ 与 $2$ 往返，花费燃料 $3$

$1$ 与 $2$ 往返，花费燃料 $1$

前四条航线被忽略，故有四个恒星系，$\{1,2\},\{3\},\{4\},\{5\}$

基地建在 $1$ 时，从 $1$ 到 $2$ 需要购买燃料量为 $1$ 的燃料罐，可以发现，没有其他比这个更优的答案。

$2 \le n \le 100\quad 1 \le m \le 40\quad 0 \le q \le 10^9\quad 0 \le val_i \le 1000$

你的答案只需要比std优秀或者和std一样且方案正确即可

1~4数据都为最优答案，5~10数据都为次优答案

~~此题会给出第10个数据的输入~~
[输入数据](https://www.luogu.org/paste/3xkq6bar)

详细范围参见”标程“

数据均为随机构造，请注意常数！


---

---
title: "不围棋"
layout: "post"
diff: 省选/NOI-
pid: P4997
tag: ['模拟', '并查集', 'Special Judge', '连通块', '洛谷月赛']
---
# 不围棋
## 题目背景

「不围棋」是一种非常有趣的棋类游戏。

大家都知道，围棋的「气」是指一个棋子所在的联通块相邻的空格。两粒棋如果在棋盘上线段的两端就认为是相邻的，也就是在同一个连通块里。比如在图中，白子为四个独立的连通块，黑子构成一个连通块，绿色点是黑子连通块唯一的「气」：

![](https://cdn.luogu.com.cn/upload/pic/41011.png )

「提子」是指将没有「气」的棋子提出棋盘，在上图中，如果白方走绿点，那么就可以将黑子全部提走。

在围棋中，我们想尽量多地占领地盘、提走对方棋子。然而，不围棋恰恰相反——不围棋是一种非常和平的游戏，双方的走子不能产生任何提子，也就是说，**任何一次走子不能让棋盘上任何一个棋子所在的连通块没有气**。比如，白方在上图中不能走绿点。

在你的某一步棋后，对方无棋可走，那么你就赢了。
## 题目描述

小 F 对不围棋特别感兴趣，不过他经常输，所以他想做出一个 AI 来替他完成这局游戏。

不过造 AI 实在是太困难啦，小 F 千辛万苦写出来的 AI 被同学们的 AI 锤爆啦！

现在，他想请你帮他实现一个 AI 中一部分的功能——随机模拟，因为他相信你写的程序非常优秀，一定能优化他的 AI。

给你一个 $n \times n$ 的棋盘，上面或许已经有一些棋子了，但此时局面一定是合法的，即**不存在没有气的连通块**；此时轮到黑棋下棋，因此棋盘上**黑白棋子的数量一定是相等的**。

你的任务是，**依次**为黑棋和白棋**随意**指定一个可行的走子位置，直到某一步游戏无法进行，决出胜负为止。

在正式的不围棋比赛还存在一些禁手规则。不过由于小 F 玩的是一种棋盘大小可变的新型不围棋，我们只用考虑上面提到的气的规则就好。
## 输入格式

输入一行一个整数 $n$，表示棋盘大小。
输入接下来 $n$ 行，每行有一个长度为 $n$ 的字符串，表示第 $i$ 行的情况。

* `.` 表示空
* `X` 表示黑棋
* `O` 表示白棋

详细请参考样例。

输入保证，棋盘初始局面合法，`X` 与 `O` 数量相等。
## 输出格式

你需要输出至少一行，假设你输出了 $L$ 行，那么对于前 $L - 1$ 行，你应该输出两个用空格分隔的正整数表示下棋坐标 $x_i, y_i$，其中奇数行表示黑棋的行动，偶数行表示白棋的行动。$x$ 坐标为从上到下从 $1$ 到 $n$，$y$ 坐标为从左到右从 $1$ 到 $n$。

请在第 $L$ 行输出 `-1 -1`，表示此时第 $L$ 手执棋人已经无棋可走。

你的输出可能会很大，即使本题时限为 $3s$，也请你不要使用太慢的方法输出大量内容。

#### 评分方式：

本题启用 Special Judge，并且有部分分。我们将通过以下方式进行计分：

* 如果你输出格式错误，那么该测试点不得分。格式错误包括但不限于：输出了非数字内容；一行输出了超过或者少于两个正整数；输出的坐标在棋盘外；最后一行的输出不是 `-1 -1`。
* 如果你的输出格式正确，但是你的输出的第一行的答案就是不可接受的，那么该测试点不得分。例如：输出的坐标是黑棋不可以下的位置；黑棋有棋可走却输出了 `-1 -1`。
* 如果你的输出格式正确，并且你的前 $k(1 \leq k <L)$ 行输出是可以接受的，那么该测试点将至少得到 $s$ 分，其中 $s = \lfloor \lg k \rfloor + 1$，含义是 $k$ 在十进制表示下是一个 $s$ 位数。
* 如果你的输出完全正确，无论你输出了多少行，你都将得到 $10$ 分。

详情请参考样例解释。
## 样例

### 样例输入 #1
```
3
XXX
OOX
OO.
```
### 样例输出 #1
```
-1 -1
```
### 样例输入 #2
```
3
XOO
XO.
X..
```
### 样例输出 #2
```
2 3
-1 -1
```
## 提示

#### 样例 1 解释：

注意到将棋盘下满会让棋盘上所有连通块都没有气，所以黑棋是无棋可走的。

#### 样例 2 解释：

样例 2 还有两个正确的输出是这样的：
```
3 2
2 3
-1 -1
```
```
3 3
2 3
-1 -1
```
我们将棋盘表示出来：

![](https://cdn.luogu.com.cn/upload/pic/41216.png)

其中，黑棋是三个空格都可以走的。

* 如果黑棋走 $(2, 3)$，如图，此时白棋走任何位置都会提走相邻的黑棋，白棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41219.png)

* 如果黑棋走 $(3, 2)$，如图，此时白棋唯一可走的点是 $(2, 3)$，之后黑棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41218.png)

* 如果黑棋走 $(3, 3)$，如图，此时白棋唯一可走的点是 $(2, 3)$，之后黑棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41217.png)

这三种情况依次对应三个输出，输出任意一种可得到满分。

#### 评分规则解释：

为了解释评分规则，我们以样例 2 为例，对于以下几种输出：
```
I AK IOI
```
很不幸，因为您太强了，所以为了按住躁动的您，我们会给您 $0$ 分。

```
-1 -1
```
```
1 1
-1 -1
```
很不幸，你的第一行没有输出正确，得 $0$ 分。

```
3 3
-1 -1
```
你输出的前 $1$ 行是正确方案的一部分。由于 $1$ 是 $1$ 位数，恭喜你得到了整整 $1$ 分！

#### 数据范围：

![](https://cdn.luogu.com.cn/upload/pic/41855.png)


---

---
title: "随机生成树"
layout: "post"
diff: 省选/NOI-
pid: P5036
tag: ['模拟', '枚举', '连通块']
---
# 随机生成树
## 题目背景

@葛军 改编的水题


## 题目描述

rainheavy在纸上画了N个点（从1到N编号），每个点的颜色用一个整数描述。rainheavy决定用这N个点随机生成一棵树，生成的规则如下：

对于2号点到N号点，每个点随机指定连接一个点。i号点(2 <= i <= N)的连的点在i的约数中和i的倍数中不超过N的中随机挑选一个。（例如N=30时10号点的可以连接1号，2号，5号，20号，30号）

生成的树中不能有重边（不然就不叫树了）

树生成完之后，rainheavy可以计算出这个树有多少个联通块，一个联通块是一些点的集合，需要满足以下两个条件：

1、从集合中任取两个点都满足：两个点颜色相同，且这两个点之间存在一条树边组成的路径，路径上的所有点都和这两个点颜色相同

2、对于集合中的任意一个点和集合外的任意一个点：两点要么不同色，要么不存在一条树边组成的路径使得路径上所有点都和这两个点同色。

rainheavy希望计算出生成的树中联通块个数最多时，需要连接哪些边，但是rainheavy太强了，不屑于做这种辣鸡题目，~~更重要的是他要去AK IOI~~，于是就把题目扔给了你

注：边的顺序

1.首先，满足连通块个数最多的优先（即对于生成连通块有贡献的优先）

2.同样满足条件1时，连接的两个点编号之和较小的边优先（如满足条件1时，连接3号点和5号点的边比连接4号点和5号点的边优先）

3.同时满足条件2时，连接的两个点编号的之中较小的一个较小的边优先（如满足条件2时，连接2号点和6号点的边比连接3号点和5号点的边优先）
## 输入格式

第一行一个整数N代表点数

第二行N个整数，第i个整数$c_i$代表第i个点的颜色

## 输出格式

输出共n-1行，每行两个整数x,y表示需要一条边连接点x和点y（要求x<y，且输出的顺序满足题目描述中边的顺序）

Tip：由于输出较多，建议用快速输出（不会就算了顶多T掉嘛对不对）
## 样例

### 样例输入 #1
```
4
3 2 3 2
```
### 样例输出 #1
```
1 2
1 4
1 3
```
## 提示

对于样例的解释：因为2号、4号点会对生成联通块有贡献（3号你连了也没用），又因为1+2<1+4，所以1 2比1 4优先输出，最后再输出1 3


对于30%的数据, 2 <= N <= 10

对于60%的数据, 2 <= N <= 5000

对于80%的数据, 2 <= N <= 200000

对于100%的数据, 2 <= N <= 500000，1<=颜色<=1e9（反正多了也没用）


---

---
title: "[JSOI2016] 炸弹攻击1"
layout: "post"
diff: 省选/NOI-
pid: P5544
tag: ['2016', '各省省选', '江苏', '模拟退火']
---
# [JSOI2016] 炸弹攻击1
## 题目背景

JYY 最近迷上了一款塔防游戏，在游戏中，JYY 除了建设建筑，还可以使用炸弹对屏幕上的敌人进行范围杀伤。
## 题目描述

游戏地图可以简单认为是一个二维平面。JYY 建造了 $N$ 个建筑，每个建筑都是一个圆，其中第 $i$ 个建筑的圆心位于 $(x_i,y_i)$ 且半径为 $r_i$。地图上一共有 $M$ 个敌人，一个敌人可以近似看成一个平面上的点，其中第 $i$ 个敌人位于$ (p_i,q_i)$。JYY 可以使用一枚可以设置半径的炸弹，可以设置一个不超过 $R$ 的范围，然后选择平面上的一个点引爆，范围内的所有敌人全部消灭。

当然，由于炸弹威力巨大，如果爆炸范围接触到 JYY 的建筑，那么 JYY 的建筑也会受到损伤。（注：如果炸弹的爆炸范围仅接触到了 JYY 建筑的边界，则不会对 JYY 的建筑造成损伤；如果敌人出现在了爆炸范围的边界，则该敌人被消灭）JYY 可以自由控制炸弹的爆炸地点和爆炸半径。作为一个保守的玩家，他希望在保证自己建筑毫发无损的情况下，消灭尽量多的敌人。
## 输入格式

第一行包含三个非负整数，分别为 $N,M,R$；

接下来 $N$ 行，每行三个整数，其中第 $i$ 行为 $x_i,y_i,r_i$，表示第 $i$ 个建筑的位置和半径。数据保证所有建筑不相交（但是有可能边界接触）；

接下来 $M$ 行，每行两个整数，其中第 $i$ 行为 $p_i,q_i$，表示第 $i$ 个敌人的位置。
## 输出格式

输出一行一个整数，表示 JYY 最多可以消灭的敌人数量。
## 样例

### 样例输入 #1
```
1 5 3
0 0 1
3 3
-3 3
3 -3
3 0
0 3 
```
### 样例输出 #1
```
3
```
## 提示

- 对于 $20\%$ 的数据，满足 $M = 2$；
- 对于另外 $20\%$ 的数据，满足 $N = 0$；
- 对于另外 $20\%$ 的数据，满足 $M \leq 50$；
- 对于 $100\%$ 的数据，满足：
  - $0 \leq N \leq 10$；
  - $0 < M \leq 10^3$；
  - $1 \leq R, r_i \leq 2 \times 10^4$；
  - $|p_i|, |q_i|, |x_i|, |y_i| \leq 2 \times 10^4$。



---

---
title: "[CTSC1998] 算法复杂度"
layout: "post"
diff: 省选/NOI-
pid: P5698
tag: ['模拟', '字符串', '1998', '栈', 'CTSC/CTS']
---
# [CTSC1998] 算法复杂度
## 题目背景

CTSC1998 D1T3

我们在编程时，最关心的一个问题就是算法的时间复杂度。但是分析一个程序的复杂度是一项很困难的工作，在程序的码风不是很好的情况下更是如此。

所以，专门研究算法的 SERKOI 小组决定开发出一个分析程序时间复杂度的软件。由于这是一个全新的领域，所以 SERKOI 小组决定先从简单情况入手进行分析。
## 题目描述

为了简化问题,程序只包含循环和顺序结构,程序的结构定义如下：

$\texttt{begin <statement> end}$ 

一个语句块的结构是**递归定义**的，如下所示：

$\texttt{loop x <statement> end}$

或者 $\texttt{op <statement>}$ 

或者为 $\texttt{break <statement>}$ 

或者为 $\texttt{continue <statement>}$ 

语句块可以为空。

注意：

1. 一个程序都是以 $\texttt{begin}$ 开始，以相应的 $\texttt{end}$ 结束；

2. $\texttt{loop x <statement> end}$ 表示其中的语句重复执行 $x$ 次；

3. $\texttt{op x}$ 表示执行 $x$ 个单位操作；

4. 上面两点中的 $x$ 可以是一个正整数或 $n$；

5. $\texttt{break}$ 语句的作用是跳出这一层循环, $\texttt{continue}$ 语句的作用是跳过这一层循
环的其它语句，直接进入下一次循环。如果它（$\texttt{break}$ 或 $\texttt{continue}$）不在任何一层循环中，**请忽略它们**。

你需要写一个程序，用来求出题目描述的程序的时间复杂度，并以多项式的形式输出。

注意，该多项式是关于 $n$ 的多项式，而且，**常数项和系数不能省略**。

数据保证能求出该程序的时间复杂度。
## 输入格式

输入中包含一个完整的程序，
每两条语句之间至少用一个空格或换行符隔开。

## 输出格式

将计算出的时间复杂度多项式按**降幂排列**输出。
## 样例

### 样例输入 #1
```
begin loop n loop 3 loop n
op 20
end end end
loop n op 3 break end
loop n loop n
op 1
break
end end
end

```
### 样例输出 #1
```
60n^2+n+3
```
### 样例输入 #2
```
begin
op n
loop 3
op n
break
end
loop n
loop n
op 1
continue
op n
end
end
end 
```
### 样例输出 #2
```
n^2+2n
```
## 提示

循环的嵌套最多不超过 $20$ 层。

保证最终时间复杂度多项式每项的系数不超过 ${10}^9$。


---

---
title: "[NEERC 2016] Mole Tunnels"
layout: "post"
diff: 省选/NOI-
pid: P6122
tag: ['2016', 'ICPC', '模拟费用流']
---
# [NEERC 2016] Mole Tunnels
## 题目描述

鼹鼠们在底下开凿了 $n$ 个洞，由 $n-1$ 条隧道连接，对于任意的 $i>1$，第 $i$ 个洞都会和第 $\frac{i}{2}$（取下整）个洞间有一条隧道，第 $i$ 个洞内还有 $c_i$ 个食物能供最多 $c_i$ 只鼹鼠吃。一共有 $m$ 只鼹鼠，第 $i$ 只鼹鼠住在第 $p_i$ 个洞内。

一天早晨，前 $k$ 只鼹鼠醒来了，而后 $m-k$ 只鼹鼠均在睡觉，前 $k$ 只鼹鼠就开始觅食，最终他们都会到达某一个洞，使得所有洞的 $c_i$ 均大于等于该洞内醒着的鼹鼠个数，而且要求鼹鼠行动路径总长度最小。现对于所有的 $1 \le k \le m$，输出最小的鼹鼠行动路径的总长度，保证一定存在某种合法方案。
## 输入格式

第一行两个数 $n,m$，表示有 $n$ 个洞，$m$ 只鼹鼠。
第二行 $n$ 个整数 $c_i$ 表示第 $i$个洞的食物数。
第三行 $m$ 个整数 $p_i$ 表示第 $i$只鼹鼠所在洞 $p_i$。
## 输出格式

输出一行 $m$ 个整数，第 $i$ 个整数表示当 $k=i$ 时最小的鼹鼠行动路径总长度。

## 样例

### 样例输入 #1
```
5 4
0 0 4 1 1
2 4 5 2
```
### 样例输出 #1
```
1 1 2 4
```
## 提示

$1 \le n,m \le 10^5$，$0 \le c_i \le m$，$1 \le p_i \le n$。


---

---
title: "[THUPC 2021 初赛] 狗蛋和二五仔"
layout: "post"
diff: 省选/NOI-
pid: P7144
tag: ['模拟', '2021', 'Special Judge', 'THUPC']
---
# [THUPC 2021 初赛] 狗蛋和二五仔
## 题目背景

**那女孩对我说**  
**代价为十辆铲车**
## 题目描述

小 E 喜欢和老师变换着花样玩牌。最近，他们又发明了一种叫做“狗蛋和二五仔”的玩法。

规则是这样的：

游戏开始时小 E 和老师各有 $30$ 点体力值，手上各有 $2$ 张牌。所有的牌是完全相同的。每个玩家的面前都可以放置牌，开始时双方面前没有任何牌。

双方轮流进行操作。玩家在每个自己的回合开始时先抽一张牌。“抽一张牌”的操作指的是，如果手上的牌的数量小于 $3$ 张，则再抓一张牌放在手上；如果手上恰好有 $3$ 张牌，则不能再抓牌。操作分为 $4$ 种类型。

- 技能。让自己的体力值 $- 2$，然后抽一张牌。
- 攻击。具体地，玩家可以选择一张放在自己面前的**本回合还未攻击过**的牌，选择对方面前的一张牌同归于尽，或者选择一张放在自己面前的**本回合还未攻击过**的牌，让对方的体力值 $- 3$。如果是后者，则将这张选择的牌标记为已攻击。
- 打牌。如果你面前的牌的数量小于 $4$ 张，且手上有牌才能进行此操作。先进行下面的过程 $3$ 次：
  - 随机选择一个角色，让它的体力值 $- 1$。这个角色可以是自己、对方或者某一方面前的一张牌。如果双方场上的牌一共有 $k$ 张，那么选择到任何一个角色的概率为 $\frac{1}{k + 2}$。如果该角色是一张牌且体力值变为了 $0$，那么将它摧毁；如果该角色是一个玩家且体力值变为了 $0$，那么该玩家直接输掉游戏。
  
  在进行完 $3$ 次后将手上的一张牌放在自己面前。牌的体力值为 $2$。这张牌在本回合中被认为已攻击过。
- 结束回合，接下来轮到对方的回合。

一回合中，玩家可以进行多次操作，但是技能和打牌的操作次数**之和**不能超过 $O$。除了结束回合，这些操作没有顺序限制，比如你可以先打一张牌，然后使用技能，然后再打一张牌。在结束回合之前，玩家需要进行至少一次任意的操作才能结束回合。

在任何时刻如果有玩家的体力值小于或等于 $0$，那么该玩家输掉游戏。

游戏进行了几个回合后，现在轮到了小 E 的回合开始前。小 E 想让你帮他分析，如果双方都采用最优策略，那么现在自己赢的概率是多少。
## 输入格式

第一行一个正整数 $T, O$，分别表示数据组数和每回合中技能和打牌的操作次数上限。  
对于每组数据，第一行两个正整数 $E, S$，分别表示小 E 和老师现在的体力值。保证 $1 \le E, S \le 20$。  
第二行一个非负整数 $c$，然后跟着 $c$ 个正整数 $a_1, \ldots , a_c$，表示老师面前有 $c$ 张牌，它们的体力值分别为 $a_1, \ldots , a_c$。保证 $0 \le c \le 4$，$1 \le a_i \le 2$。  
第三行一个非负整数 $p$，然后跟着 $p$ 个正整数 $e_1, \ldots , e_p$，表示小 E 面前有 $p$ 张牌，
它们的体力值分别为 $e_1, \ldots , e_p$。保证 $0 \le p \le 4$，$1 \le e_i \le 2$。  
第四行两个 $[0, 3]$ 之间的非负整数，分别表示老师和小 E 的手牌数。  
在你到来之前老师可能作了弊，你不需要判断输入的情况是否真的是游戏进行了几个回合后的情况。
## 输出格式

对于每组数据输出一行一个实数，表示小 E 在双方采用最优决策时获胜的概率。你的输出的和标准答案的绝对误差不超过 ${10}^{-6}$ 时算作正确。
## 样例

### 样例输入 #1
```
1 5
1 1
0
0
0 1

```
### 样例输出 #1
```
0.500000000

```
### 样例输入 #2
```
1 4
5 14
1 1
1 1
1 0

```
### 样例输出 #2
```
0.041879441

```
## 提示

**【样例解释 #1】**

回合开始，小 E 抽一张牌。此时小 E 手上有 $2$ 张牌，老师手上没有牌，双方的面前都没有牌。双方的体力值均为 $1$。这时，最优策略下，小 E 不能使用技能，因为使用后会因为自己的体力值小于等于 $0$ 而输掉游戏；小 E 不能攻击，因为自己面前没有牌；小 E 也不能结束回合，因为本回合他还没有进行任何操作。所以小 E 的最优策略是打一张牌，这时会随机选到小 E 或者老师中的一个角色，让他体力值 $- 1$ 然后输掉游戏。所以小 E 的获胜概率为 $0.5$。

**【子任务】**

保证 $1\le T\le 351493,3\le O \le 5$ 。

**【后记】**

最后小 E 还是战胜了老师。

**“老师你术士玩多了就知道怎么玩了，你打得还不够多。”**

**“吹牛现在都流行这么吹的吗？兄弟你知道我术士多少胜场嘛，啊？我跟你说全世界没有一个人术士比我胜场多的。”**

**【题目来源】**

来自 2021 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2021）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2021-pre> 查看。


---

---
title: "[CTSC2002] 灭鼠行动"
layout: "post"
diff: 省选/NOI-
pid: P7196
tag: ['模拟', '2002', 'CTSC/CTS']
---
# [CTSC2002] 灭鼠行动
## 题目描述

最近，有一些繁殖力很强的老鼠在下水道非常猖獗，灭鼠特工队正在计划消灭这些老鼠。下水道只有东西方向和南北方向的管道，如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/k86ntxbk.png)

灭鼠特工队的队员拥有强大的武器。他们将在某些时刻 $t$ 在某些位置 $(x,y)$ 放置武器。他们所使用的武器包括：

1. 强力炸弹：它的攻击范围限定在管道内部，是沿竖直和水平方向，离 $(x,y)$ 的距离不超过 $L$ 的区域，但是不能穿透下水道壁。它将在放置之后立刻爆炸，且攻击范围内的老鼠将被全部炸死。

2. 神秘射线：它的攻击范围是以 $(x,y)$ 为圆心，半径为 $R$ 的圆，而且可以穿透下水道壁。射线在时刻 $t$ 施放后，将使攻击范围内的所有老鼠立刻陷入昏迷状态，失去知觉，停止一切生理活动，待到第 $t+3$ 时刻才能恢复（保持失去知觉前的朝向）。如果在昏迷状态中再次受到射线攻击，那么它将再推迟 $3$ 个时刻恢复。例如，若老鼠在时刻 $t$ 和时刻 $t+1$ 个受到一次射线的攻击，则它要昏迷到第 $t+3+3$ 时刻才能恢复知觉。恢复知觉以后，老鼠将继续以前的生理活动。

3. 定时炸弹：它的攻击范围仅包括 $(x,y)$。它在时刻 $t$放置后，将在第 $t+3$ 时刻爆炸，爆炸时处在 $(x,y)$ 点的老鼠将全部被炸死。

4. 生物炸弹：它的攻击范围仅包括 $(x,y)$。它将在放置之后立刻爆炸，使处在 $(x,y)$ 点的所有老鼠的性别改变（无论大小，雌变成雄，雄变成雌），但不影响老鼠的正常生理活动。

虽然特工队的实力很强，但是老鼠的实力也不容忽视。

我们定义，相邻两个时刻之间是一个时间单位。从 $t=0$ 时刻开始，每只老鼠就从初始位置向某一初始方向运动。只要前方有管道，如上图中沿方向 $\texttt{N}$ 到达点 $\texttt{A}$，老鼠就会一直向前走，运动速度为 $1$。否则，如果只有左边或者只有右边有管道，如上图中沿方向 $\texttt{E}$ 到达点 $\texttt{B}$ 时，再不能沿原方向继续前进，它就会花费一个时间单位朝该方向原地转动 $90$ 度，即它将改变方向朝向 $\texttt{S}$。如果它左边和右边都有管道，如上图中沿方向 $\texttt{W}$ 到达点 $\texttt{C}$，老鼠会回忆这是第几次处于这种情况。如果是第奇数次遇到，它会向左转，第偶数次就向右转。如果它处于一条死路的尽头，如上图中沿方向 $\texttt{W}$ 到达点 $\texttt{D}$，那么它会花费两个时间单位连续向右转两次，即它将改变方向朝向E。

   如果在 $t$ 时刻某点恰好只有两只老鼠，一只为成年雄老鼠，一只为成年雌老鼠，则它们将会因为进行繁殖而在该点停留两个单位时间，$t+2$ 时刻会在该点对每个有管道的方向生出一只朝着该方向的小老鼠，南北方向为雄小老鼠，东西方向为雌小老鼠。如上图中的 $\texttt{C}$ 点，$t$ 时刻恰好只有两只老鼠，它们都已成年且性别相异，那么在第 $t+2$ 时刻就会在该点生出三只小老鼠，它们分别朝向 $\texttt{N}$、$\texttt{S}$、$\texttt{E}$，性别分别是雄性、雄性、雌性。小老鼠一出生就立刻开始移动，而成年老鼠需要再休息一个时间单位，即在 $t+3$ 时刻继续活动（两只老鼠都保持生育前的朝向）。小老鼠需要成长 $5$ 个时间单位才会长成为成年老鼠。

   特工队现在制定了一套灭鼠计划，其中包括在下水管道放置武器的位置、时间和类型。你需要帮他们计算灭鼠行动的效果，如果在该计划实施的过程中，老鼠的数量超过了某个限定值，就会爆发鼠疫。
## 输入格式

第一行为 $4$ 个整数 $L, R, m, n(0\le L,R\le 10,1\le m,n\le 50)$，其中 $L$ 代表强力炸弹的有效攻击距离，$R$ 代表神秘射线的作用半径，$m$ 和 $n$ 代表下水道平面图的规模。$x$ 坐标的范围为 $[1,m]$, $y$ 坐标的范围为 $[1,n]$。

从第 $2$ 行到第 $m+1$ 行为下水道结构图。我们用方向数 $1$ 代表 $\texttt{N}$ (北)，用方向数 $2$ 代表$\texttt{E}$ (东)，用方向数 $4$ 代表 $\texttt{S}$ (南)，用方向数 $8$ 代表 $\texttt{W}$ (西)。第 $i+1$ 行的第 $j$ 个数字 $c_{i,j}$ 代表点 $(i,j)$ 处有管道连接的所有方向数之和，如上图中的点 $\texttt{B}$ 的方向数之和为 $12$。

第 $m+2$ 行为一个整数 $K（1\le K\le 50）$，代表时刻 $0$ 时老鼠的个数（此时老鼠都是成年的）。

第 $m+3$ 行到第 $m+K+2$ 行每行描述一只老鼠，包括该老鼠的初始坐标 $(x,y), (1\le x\le m, 1\le y\le n)$，朝向（’$\texttt{E}$’,’$\texttt{S}$’,’$\texttt{W}$’,’$\texttt{N}$’）以及性别（’$\texttt{X}$’=雄，’$\texttt{Y}$’=雌）。输入保证每个老鼠都在水管内。

第 $m+K+3$ 行为两个整数 $P，Limit(1\le P, Limit\le 100)$，分别表示特工队准备使用的武器个数以及控制鼠疫发生的老鼠数量的极限。

第 $m+K+4$ 行到第 $m+K+P+3$ 行每行描述一个武器，包括该武器的类型($1$-强力炸弹，$2$-神秘射线，$3$-定时炸弹，$4$-生物炸弹)，放置的时刻 $t(t\ge 1)$，放置的坐标 $(x,y) (1\le x\le m, 1\le y\le n)$，输入保证武器放置在管道内。武器按照放置的时间不降序排列。

最后一行包含一个整数 $Time(1\le Time\le 1000)$，表示模拟的结束时刻。$Time$ 保证比所有武器的放置时刻大。
## 输出格式

包含一个整数。如果爆发了鼠疫，该整数为 $-1$，否则该整数为时刻 $Time$ 的老鼠数目。
## 样例

### 样例输入 #1
```
1 1 3 3
6 14 12
7 15 13
3 11 9
3
1 3 W X
1 2 W X
3 3 S X
3 100
1 1 2 2
3 1 3 1
2 2 3 2
10
```
### 样例输出 #1
```
1
```
## 提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/lwexoo5d.png)


---

---
title: "[JOISC 2020] 伝説の団子職人"
layout: "post"
diff: 省选/NOI-
pid: P7218
tag: ['2020', '提交答案', 'Special Judge', '模拟退火', '随机化', 'JOI（日本）']
---
# [JOISC 2020] 伝説の団子職人
## 题目背景

您是做团子带师，您太强了。
## 题目描述

您面前有一个 $R \times C$ 的网格，每一个格子里有一个团子，您可以横向，竖向，斜向地将三个连续的团子按顺序串起来，按顺序指可以串上中下，下中上之类的，但是不能串中下上，上下中之类的。

如果一串团子的颜色为绿，白，粉或者粉，白，绿，那么称这串团子叫 AK IOI 串。

求串最多 AK IOI 串的方法（我坚信做了几个 AK IOI 串就会 AK 几次 IOI）。
## 输入格式

第一行两个整数 $R,C$ 代表网格大小。    
接下来 $R$ 行每行 $C$ 个字符代表网格：

- `P` 代表粉色团子
- `W` 代表白色团子
- `G` 代表绿色团子
## 输出格式

$R$ 行每行 $C$ 个字符代表串好的网格：

- 可以为 `-`，`|`，`/`，`\`，代表一个团子串
- 如果不是以上四种线，那么原样输出

输出文件应为 `01.ans` ~ `06.ans`。
## 样例

### 样例输入 #1
```
3 4
PWGP
WGPW
GWPG
```
### 样例输出 #1
```
P-GP
WGP|
G-PG
```
### 样例输入 #2
```
3 4
PWWP
WWWW
PGGP
```
### 样例输出 #2
```
PWWP
W\/W
PGGP
```
## 提示

#### 样例 1 解释

您做了 $3$ 个 AK IOI 串。

#### 样例 2 解释

您做了 $2$ 个 AK IOI 串。

#### 数据规模与约定

**本题为提交答案题。**

**本题使用 Special Judge。**

一共有 $6$ 组数据，保证 $3 \le R,C \le 500$，输入文件可在附加文件中得到，具体数据表格如下：

|数据点|分数 $S$|及格线 $X$|良好线 $Y$|优秀线 $Z$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$15$|$44000$|$47000$|$47220$|
|$2$|$15$|$39000$|$41700$|$41980$|
|$3$|$15$|$45000$|$51000$|$51390$|
|$4$|$15$|$18000$|$19000$|$19120$|
|$5$|$20$|$43000$|$48200$|$48620$|
|$6$|$20$|$44000$|$46000$|$46500$|

假设 $N$ 为得到的 AK IOI 串个数，那么评分标准为（四舍五入）：

- $N<X$，$0$ 分
- $X \le N <Y$，$\dfrac{N-X}{2(Y-X)} \times S$ 分
- $Y \le N < Z$，$\left(\dfrac{1}{2}+\dfrac{N-Y}{2(Z-Y)}\right) \times S$ 分
- $Z \le N$，$S$ 分

如果输出格式有误或输出无效，判 $0$ 分。

#### 说明

翻译自 [第１９回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) [Day4 B 伝説の団子職人 ](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/day4/dango2.pdf)。


---

---
title: "[THUPC 2021] 群星连结"
layout: "post"
diff: 省选/NOI-
pid: P7610
tag: ['模拟', '2021', 'O2优化', 'THUPC']
---
# [THUPC 2021] 群星连结
## 题目背景

众所周知，群星和公主连结联动啦！联动的结果是一个叫做群星连结的游戏。

这是一个双人回合制竞赛游戏，双方记为 Alice 和 Bob。游戏有若干**回合**，每个回合依次由先手和后手分别行动一次。

现在聪明的你写了一个优秀的 AI 来玩这个游戏，这个 AI 会遵从游戏规则，并且按照游戏过程条目里既定的策略进行游戏。但是由于您太强了，所以世界上只有这么一个 AI，所以只能自己和自己打。

现在给定这个游戏的初始局面，让这个 AI 分别作为 Alice 和 Bob 对战，其中 Alice 先手。你需要模拟游戏过程，并且判断最终是 Alice 获胜还是 Bob 获胜。

游戏初始局面会通过输入给出。

**【提示】**

本题中，**伤害**、**真实伤害**、**生命值扣除**是三个不同的概念，请注意区分。
## 题目描述

#### 基础参数

首先，在游戏开始之前，每个玩家需要选择恰好 $n$ 个角色，并编号 $1,2,3,\dots,n$。

每个角色都有一些基础参数：

1. $HP,hp$ ：最大生命值，生命值；
2. $MP,mp$：最大能量值，能量值；
3. $atk,\Delta_{atk}$：基础攻击力，攻击力增益；
4. $def,\Delta_{def}$：基础防御力，防御力增益；

另外，为方便起见，下文中记 $A=\max(atk+\Delta_{atk},1)$，$D=\max(def+\Delta_{def},0)$。

游戏开始时，生命值 $hp$ 等于最大生命值 $HP$，能量值 $mp$、攻击力增益 $\Delta_{atk}$、防御力增益 $\Delta_{def}$ 均等于 $0$。

$HP,MP,atk,def$ 将由输入给出。

除此之外，每个角色分别拥有一个**天赋**和一个**技能**，分别见**天赋**条目和**技能**条目。

#### 死亡判定

游戏过程的任意时刻，如果某个角色生命值 $hp$ 降到 $0$ **及**以下，则判定该角色【死亡】。

一个角色一旦被判定为【死亡】，则该角色将从场上完全退出，并且生命值被恒定为 $0$，不能通过任何方式回复生命值（即不能起死回生，即使拥有【天赋 — 心胜于物】；另外，也不能通过己方其它角色技能回复生命值），不能普通攻击、发动技能，也不能被选定为优先目标，因而不能被普通攻击。

总之就是不以任何形式参与后续游戏的进程，并且本题中所有“全体”、“所有角色”等词均不包含【死亡】角色。

当某方角色全部被判定【死亡】时，游戏立刻结束，并判定另一方胜利（若此时仍有尚未完成的结算，也全部不再进行）。

#### 参数溢出

在游戏过程的任意时刻，如果某个角色的生命值 $hp>HP$，则 $hp$ 会立刻变成为 $HP$。

在游戏过程的任意时刻，如果某个角色的能量值 $mp>MP$，则 $mp$ 会立刻变成为 $MP$。

#### 优先目标

游戏开始前，每个玩家需要为每个角色选定一个攻击顺序。

具体来说，对编号为 $i$ 的角色，需要确定一个攻击顺序 $p_{i,1},\ldots,p_{i,n}$，满足 $p_{i,1},\ldots,p_{i,n}$ 是一个关于 $1,\ldots,n$ 的排列。

游戏过程的任意时刻，称编号为 $i$ 的优先目标是 $p_{i,j}$，当且仅当 $p_{i,1},\ldots,p_{i,j-1}$ 全部【死亡】，并且 $p_{i,j}$ 没有【死亡】。

#### 普通攻击

普通攻击会对优先目标造成 $A$ 点伤害。

拥有【天赋 — 超凡入圣】的角色则会对优先目标造成 $A$ 点真实伤害。详见**天赋**条目。

拥有【天赋 — 星河力量投射】的角色普通攻击会附加真实伤害。详见**天赋**条目。

#### 天赋

天赋有以下几种类型（每行前的编号为天赋类型的编号，圆括弧 `()` 内部为附加参数）：

0. 【天赋 — 我自闭了】该角色的天赋毫无作用；
1. 【天赋 — 血肉皮囊】该角色免疫一半真实伤害。详情见**生命值扣除环节**条目。  
   **真实伤害见生命值扣除条目**；
2. 【天赋 — 星河力量投射】$(x)$ 该角色每次普通攻击会附加的 $x$ 点真实伤害；
3. 【天赋 — 心胜于物】$(x,y)$ 该角色每次己方行动结束后回复 $x$ 点生命值，并**额外**回复 $y$ 点能量值；
4. 【天赋 — 超凡入圣】该角色的普通攻击被视为真实伤害攻击，即该角色的普通攻击不造成伤害，但造成 $A$ 点真实伤害。
5. 【天赋 — 科技至上】$(x,y)$ 该角色每次进行普通攻击后，回复 $x$ 点生命值；该角色每次发动技能后，**额外**回复 $y$ 点能量值。注意：如果普通攻击或发动技能造成对方全部角色【死亡】，则该角色不再回复生命值或能量值。

本题保证天赋附加参数均为**正**整数（但在输入数据中可能会有 $0$，详情参见**输入格式**条目）。

#### 技能

当某个角色能量值等于其最大能量值时（并且在游戏过程中被选定为发动技能的角色），可以清零其能量值并发动一次技能。

技能有以下几种类型（每行前的编号为技能类型的编号，圆括弧` ()` 内部为附加参数）：

0. 【技能：心态崩了！】该角色的主动技能毫无作用。注意，该技能仍然可以被发动，只不过毫无效果而已。
1. 【技能：格林炸裂！】$(x)$ 对敌方**所有**角色造成 $x$ 点伤害，**然后**使敌方**所有**角色能量值减少 $\left\lfloor\frac{mp_{enemy}}{10}\right\rfloor$，其中 $mp_{enemy}$ 为敌方该角色能量值（即对于每个敌方角色，若其当前的能量值为 $mp_{enemy}$，那么受此技能影响，其能量值会变成 $mp_{enemy}-\left\lfloor\frac{mp_{enemy}}{10}\right\rfloor$）。注意，根据规则，敌方角色会先受到伤害而进入生命值扣除环节，在该环节中回复能量值，然后再被该技能扣除能量值。
2. 【技能：日 (zhou) 昇 (ji) 之 (dao) 雨 (dan)！】对敌方**所有**角色造成 $A$ 点真实伤害。
3. 【技能：天楼霸断剑！】$(x)$ 对敌方**所有**目标造成 $\min\left(\left\lfloor\frac{HP_{enemy}}{10}\right\rfloor,x\times A\right)$ 点伤害，其中 $HP_{enemy}$ 为被攻击目标的最大生命值。
4. 【技能：演出开始！】$(x,y)$ 设当前为第 $t$ 回合，则从发动技能开始，到第 $t+x-1$ 回合结束期间，在己方行动结束时，己方全体角色**额外**回复 $y$ 点能量值。
5. 【技能：天狼噬斩！】$(x)$ 将优先目标的防御力增益减小 $x$，**然后**对优先目标造成 $A$ 点真实伤害。
6. 【技能：地 (太) 球 (虚) 蓝 (苍) 色 (蓝) 闪 (闪) 电！】$(x,y)$ 对优先目标造成 $A$ 点真实伤害。另外，设当前为第 $t$ 回合，则从发动技能开始，到第 $t+x-1$ 回合结束期间，敌方所有角色攻击力增益减小 $y$。
7. 【技能：极光绽放！】$(x,y,z)$ 使己方未【死亡】角色生命值最低（如有多个，则编号最小）的恰好一名角色回复 $z$ 点生命值。另外，设当前为第 $t$ 回合，则从发动技能开始到第 $t+x-1$ 回合结束期间，己方所有角色攻击力增益增大 $y$。
8. 【技能：流星！】$(x,y)$ 对敌方所有角色造成 $A$ 点伤害。设当前为第 $t$ 回合，则**从该技能造成伤害后**，到第 $t+x-1$ 回合结束期间，使敌方所有角色防御力增益减小 $y$。注意，本技能先造成伤害，再产生减益。
9. 【技能：精灵庇护！】$(x,y,z)$ 己方全体角色回复 $z$ 点生命值。设当前为第 $t$ 回合，则从发动技能开始，到第 $t+x-1$ 回合结束期间，己方所有角色防御力增益增大 $y$。
10. 【技能：全力超全开！轮回之终末！】$(x)$ 己方所有角色基础攻击力 $atk$、基础防御力 $def$ 变为原先的两倍 $2\times atk, 2\times def$；未【死亡】角色生命值 $hp$ 变为 $\max\left(\left\lfloor\frac{HP}2\right\rfloor,hp\right)$，能量值 $mp$ 变为 $\max\left(\left\lfloor\frac{MP}2\right\rfloor,mp\right)$；设当前为第 $t$ 回合，则从发动技能开始，到第 $t+x-1$ 回合结束期间，己方行动结束时，己方所有角色**额外**回复 $1$ 点能量值。在第 $t+x-1$ 回合结束时，若敌方仍有角色未【死亡】，则己方全体角色强制生命值清零，并被判定为【死亡】。另外，在发动该技能时，场上所有拥有这个技能的角色（包括自己）的技能将被强制替换为 0 号【技能：心态崩了！】（因此该技能最多在游戏中被发动一次）。

本题保证技能附加参数均为**正**整数（但在输入数据中可能会有 $0$，详情参见**输入**条目）。

注意：上述形如“设当前为第 $t$ 回合，则从发动技能开始到第 $t+x-1$ 回合结束期间，……”产生的效果是**可以叠加**的。

#### 生命回复与能量回复

生命值仅可通过天赋和技能回复。

己方行动结束时，己方全体角色能量值增加 $1$。拥有【天赋 — 心胜于物】的角色，以及受【技能：演出开始！】和【技能：全力超全开！轮回之终末！】影响的角色可以额外回复能量值。

当己方角色进行普通攻击或者发动技能后，该角色能量值增加 $1$。拥有【天赋 — 科技至上】的角色发动技能后会回复额外的能量值。

注意，发动技能时，先扣除全部能量值，再发动技能，然后再增加能量值。

特别的，若该技能为【技能：全力超全开！轮回之终末！】，则使发动该技能的角色 $mp=\max\left(mp,\left\lfloor\frac{MP}2\right\rfloor\right)$ 后再增加能量值。

当己方角色因受到伤害而进入生命值扣除环节时，该角色能量值增加 $1$（无论其是否实际扣除生命值）。

**生命值扣除见生命值扣除环节。**

#### 生命值扣除环节

当角色受到伤害或者真实伤害时，该角色立即进入生命值扣除环节（注意，即使受到了 $0$ 点伤害，也会进入生命值扣除环节）。

进入生命值扣除环节后，由能量回复条目，该角色能量值增加 $1$。

假设其受到 $x$ 点伤害和 $y$ 点真实伤害，那么：

- 若该角色因拥有【天赋—血肉皮囊】而免疫一半真实伤害，则其生命值扣除 $\max(x-D,0)+y-\left\lfloor\frac y2\right\rfloor$。
- 否则，其生命值扣除 $\max(x-D,0)+y$。

#### 游戏过程

游戏开始后，可视为若干回合，编号从 $1$ 开始。

每个回合，可以划分为如下 $5$ 个阶段：Alice 行动（期间）、Alice 行动结束、Bob 行动（期间）、Bob 行动结束、当前回合结束。

己方行动期间，

1. 如果己方存在至少一个角色可以发动技能时，则按照技能编号从大到小的顺序选择其中一位发动技能。如果有多个角色满足可以发动相同编号的技能，则选择这些角色中角色编号最大的角色发动技能。
2. 如果己方没有角色可以发动技能，则选择一个优先目标生命值最高的角色发动普通攻击。如果有多个角色的优先目标生命值最高，则选择能对优先目标扣除更多生命值（而不是造成更多伤害！）的角色发动攻击。如果仍然有多个角色可以选择，则选择其中编号最大的角色发动普通攻击。

己方行动结束。

注意，己方行动期间，仅能选择一位角色发动技能，或者选择一位角色进行普通攻击。
## 输入格式

第一行一个正整数 $n$，表示 `Alice` 和 `Bob` 分别有 $n$ 个角色。

接下来 $4 n$ 行，第 $4 i - 3$ 到第 $4 i$ 行描述 `Alice` 的编号为 $i$ 的角色。

在这四行中：

- 第一行，四个非负整数 $HP,MP,atk,def$ 分别表示该角色的最大生命值、最大能量值、基础攻击力、基础防御力，保证 $HP,MP>0$。
- 第二行，$n$ 个正整数 $p_{i,1},p_{i,2}, \ldots ,p_{i,n}$，表示该角色攻击顺序，保证这是一个关于 $1$ 到 $n$ 的排列。
- 第三行，三个非负整数 $tf,x,y$ 表示天赋编号以及附加参数。如果该天赋附加参数不足两个，那么你可以忽略多余的部分（保证此时多余的部分在输入数据中是 $0$）。
- 第四行，四个非负整数 $jn,x,y,z$ 表示技能编号及附加参数。如果该技能附加参数不足三个，那么你可以忽略多余的部分（保证此时多余的部分在输入数据中是 $0$）。

接下来 $4n$ 行描述 `Bob` 的 $n$ 个角色，形式同上。
## 输出格式

如果游戏能够以某一方胜利而结束，那么：

- 第一行，输出一个正整数 $x$，表示游戏在第 $x$ 个回合结束的。
- 第二行，输出一个字符串（`Alice` 或 `Bob`）表示胜者。
- 第三行，输出 $n$ 个非负整数，依次表示胜者的每一个角色在游戏结束时的 $hp$，若该角色已死亡则输出 $0$。

如果游戏永远不会结束或者双方平局，请输出任意卖萌表情。
## 样例

### 样例输入 #1
```
3
2 8 1 1
1 2 3
3 1 1
7 2 1 2
6 6 3 0
1 2 3
5 1 1
7 2 1 1
99 10 1 1
2 1 3
1 0 0
10 10 0 0
9 10 1 0
1 2 3
2 1 0
8 2 1 0
8 7 2 1
2 1 3
1 0 0
4 2 1 0
99 10 2 0
2 1 3
1 0 0
10 10 0 0

```
### 样例输出 #1
```
15
Alice
2 0 96 

```
## 提示

**【数据范围】**

$n \le 10$，$HP, MP, atk \gt 0$，$def \ge 0$。

保证在游戏中的任意时刻，所有题面中提及到的参数及表达式的绝对值均不超过 ${10}^9$。

保证游戏在 $23333$ 回合内结束。

**【题目来源】**

来自 2021 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2021）。

题解等资源可在 [https://github.com/yylidiw/thupc_2/tree/master](https://github.com/yylidiw/thupc_2/tree/master) 查看。


---

---
title: "[JRKSJ R2] Dark Forest"
layout: "post"
diff: 省选/NOI-
pid: P7812
tag: ['2021', '洛谷原创', '提交答案', 'Special Judge', '模拟退火', '遗传算法', '随机化']
---
# [JRKSJ R2] Dark Forest
## 题目背景

**本题为提交答案题。**
## 题目描述

给你一个长为 $n$ 的序列 $a$，定义 $1\dots n$ 的排列 $p$ 的权值为

$$\sum_{i=1}^n p_i a_{p_{i-1}} a_{p_i}a_{p_{i+1}}$$

你可以理解为这个排列是一个环，即 $p_{0}=p_n,p_{n+1}=p_1$。

请构造一个权值**尽量大**的 $1\dots n$ 的排列。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数表示序列 $a$。
## 输出格式

一行 $n$ 个整数表示排列。
## 样例

### 样例输入 #1
```
5
1 4 3 2 5
```
### 样例输出 #1
```
1 3 5 2 4
```
## 提示

注意是 `a[p[i-1]] a[p[i+1]]`，数据有一定梯度。

### 数据范围

对于 $100\%$ 的数据，$1\le n,a_i\le 10^3$。

### 样例解释

该排列的权值为 $1\times2\times1\times3+3\times1\times3\times5+5\times3\times5\times4+2\times5\times4\times2+4\times4\times2\times1=463$，可以证明这是最优的排列之一。

### 评分方式

**本题使用 Special Judge**，每个测试点都有 $10$ 个参数 $v_1,v_2,\dots v_{10}$。如果你的输出的权值 $V\ge v_i$，则该测试点您至少会获得 $i$ 分。

特别的，如果您的输出不是一个 $1\dots n$ 的排列，您会在该测试点获得 $0$ 分。

评分参数已经放至附件。


---

---
title: "「SWTR-7」Spider Solitaire"
layout: "post"
diff: 省选/NOI-
pid: P7877
tag: ['模拟', 'Special Judge', 'O2优化', '图论建模', '拓扑排序', '洛谷月赛']
---
# 「SWTR-7」Spider Solitaire
## 题目背景

#### 题目描述下方有简化题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/7tdo8cdf.png)

---

小 A 在玩蜘蛛纸牌。  
为了方便你理解蜘蛛纸牌，小 A 给出了简化后的游戏规则：

- 一副牌有 $n$ 张，从小到大分别为 $1,2,\cdots,n$。
- 现有 $m$ 个牌堆，$1$ 副牌。每个牌堆中有 $0$ 张或多张牌。
- 定义「龙」$a_1,a_2,\cdots,a_d$ 为满足 $a_i-1=a_{i+1}\ (1\leq i<d)$ 的任意多张连续的牌。**一张牌也是一个「龙」。**
- 一组连续的牌可以移动，当且仅当这组牌形成了一个「龙」，且「龙」在牌堆的**最右边**。
- 一组连续的牌只能移动到一个**非空**牌堆的最右边，**且必须满足可以与该非空牌堆最右边的「龙」构成一条更大的「龙」**。
- 游戏胜利，当且仅当所有的 $n$ 张牌形成了一个「龙」。

---

例如当 $m=3$，$n=9$，局面为

```plain
9 8 4 3 2 1
7 5
6
```

时，第一个牌堆最右边的 `4 3 2 1` 形成了一个「龙」，所以 `4 3 2 1` 可以移动。将 `4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 5 4 3 2 1
6
```

接下来将第二个牌堆右边的 `5 4 3 2 1` 移动到第三个牌堆的最右边，此时局面为

```plain
9 8
7
6 5 4 3 2 1
```

接下来将第三个牌堆的 `6 5 4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 6 5 4 3 2 1
\
```

接下来将第二个牌堆的 `7 6 5 4 3 2 1` 移动到第一个牌堆的最右边，此时牌堆为

```plain
9 8 7 6 5 4 3 2 1
\
\
```

因为所有 $9$ 张牌形成了一个「龙」，所以游戏胜利。
## 题目描述

给定一个蜘蛛纸牌初始局面，小 A 想知道能否获得胜利。若能，请输出 $\texttt{YES}$ 以及**获胜所需的最小步数**。否则输出 $\texttt{NO}$。

小 A 还想知道，对于每张牌 $i$，如果要移动 $i$ 至少需要多少步，**包括移动 $i$ 的这一步**。如果无法移动输出 `-1`。

---

#### 「简化题意」

有 $m$ 个**横向**的数堆，数堆里共有 $n$ 个数，每个数堆里有 $0$ 或多个数。所有数堆里的数组成了 $1\sim n$ 中的所有数。

你可以将一个数堆**最右边递减且公差为 $-1$ 的**连续若干个数 $a_1,a_2,\cdots,a_c$ **按照原来的顺序移到另外一个非空数堆的最右边**，当且仅当该非空数堆最右边的一个数 $b=a_1+1$。

求将所有的 $n$ 个数都移动到同一个数堆且满足从左往右依次递减的最小步数。如果无解输出 $\texttt{NO}$。

**此外，你还需要对于每个数 $i$，输出如果要移动 $i$ 至少需要多少步。**
## 输入格式

第一行一个整数 $T$，表示子任务编号。  
第二行两个整数 $n,m$，分别表示一副牌的张数和牌堆的个数。  
接下来 $m$ 行，每行首先一个整数 $c$ 表示该牌堆中牌的个数，接下来 $c$ 个整数 $b_1,b_2,\cdots,b_c$ **从左到右**描述这个牌堆。
## 输出格式

如果能够获胜，在第一行输出 $\texttt{YES}$，**第二行输出最少步数**。否则输出一行 $\texttt{NO}$。

无论是否能够获胜，你还需输出 $n$ 行，第 $i$ 行一个**介于 $-1$ 与 $n$ 之间的整数**，表示移动 $i$ 至少需要多少步。
## 样例

### 样例输入 #1
```
0
9 3
6 9 8 4 3 2 1
2 7 5
1 6

```
### 样例输出 #1
```
YES
4
1
1
1
1
1
2
3
-1
-1

```
### 样例输入 #2
```
0
13 4
4 13 10 1 7
3 11 4 8
4 6 5 3 2
2 12 9

```
### 样例输出 #2
```
YES
10
2
2
2
3
3
3
1
1
3
6
7
8
-1

```
### 样例输入 #3
```
0
5 1
5 5 4 3 2 1

```
### 样例输出 #3
```
YES
0
-1
-1
-1
-1
-1

```
### 样例输入 #4
```
0
17 10
2 12 14
1 3
3 1 13 15
0
2 9 8
1 5
3 16 7 6
2 11 2
1 4
2 17 10

```
### 样例输出 #4
```
YES
14
4
1
1
1
1
1
1
1
1
2
3
4
3
1
2
4
-1
```
### 样例输入 #5
```
0
13 4
4 10 1 13 7
4 11 12 4 8
4 6 5 3 2
1 9

```
### 样例输出 #5
```
NO
-1
2
2
3
3
3
1
1
-1
-1
6
5
-1

```
## 提示

**「样例 1 说明」**

因为 1,2,3,4,5 可以直接移动，所以至少需要 1 步即可移动。  
因为需要先将 5 移至 6 右侧，6 才能移动，所以至少需要 2 步即可移动。  
因为需要先将 5 移至 6 右侧，再将 4,3,2,1 移至 5 右侧，7 才能移动，所以至少需要 3 步即可移动。  
显然 8,9 无法移动。

**「Special Judge」**

本题使用 Special Judge，请**严格遵守输出格式**：

- 如果你正确输出对能否获胜的判定，且如果能够获胜，你正确输出最小步数，你将获得该测试点**至少** $40\%$ 的分数。
- **在上一部分的基础上**，如果你正确输出移动每张牌的最小步数，你将获得该测试点**剩下** $60\%$ 的分数。也就是说，如果你上一部分输出错误，你在这一部分也不会获得任何分数。
- **如果你的输出格式错误，你将获得该测试点 $0\%$ 的分数**，包括但不限于**只输出对能否获胜的判定**。
- 需要特别注意的是，如果你不能正确求出移动每张牌的最小步数，请**随机输出 $[-1,n]$ 之间的任意整数**，否则你将获得该测试点 $0\%$ 的分数。
- 每行结束后你都需要输出换行符，**包括最后一行**。

checker 将在题目最后给出。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask #0（0 points）：是样例。
- Subtask #1（15 points）：$n\leq 3\times 10^3$，$m=2$。
- Subtask #2（15 points）：$b_i>b_{i+1}\ (1\leq i<c)$，$n\leq 3\times 10^3$。
- Subtask #3（25 points）：$n\leq 14$，$m=3$。
- Subtask #4（30 points）：$n\leq 3\times 10^3$。
- Subtask #5（15 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 5\times 10^4$。时间限制 1s，空间限制 512MB。

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) D。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

---

以下是 checker，你需要有 testlib.h 才能成功编译。

```cpp
#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair <int,int>
#define fi first
#define se second
#define pb emplace_back
#define mp make_pair 
#define vint vector <int>
#define vpii vector <pii>
#define all(x) x.begin(),x.end()
#define sor(x) sort(all(x))
#define rev(x) reverse(all(x))
#define mem(x,v) memset(x,v,sizeof(x))

#define rint inf.readInt
#define reof inf.readEof()
#define reoln inf.readEoln()
#define rspace inf.readSpace()

// wrong answer : quitf(_wa,"The answer is wrong")
// accepted :  quitf(_ok,"The answer is correct")
// partly correct : quitp(0.5,"The answer is partly correct")

int main(int argc,char* argv[]){
	registerTestlibCmd(argc,argv);
	
	string jans=ans.readToken();
	string pans=ouf.readToken(jans);
	int sub=rint(),n=rint(),diff=0;
	
	if(jans=="YES"){
		int jstep=ans.readInt();
		int pstep=ouf.readInt();
		if(jstep!=pstep)quitf(_wa,"The answer is wrong");
	}
	
	for(int i=1;i<=n;i++){
		int jans=ans.readInt();
		int pans=ouf.readInt();
		if(jans!=pans)diff=1;
	}
	
	while(!ouf.seekEof())ouf.readToken();
	while(!inf.seekEof())inf.readToken();
	while(!ans.seekEof())ans.readToken();
	if(diff)quitp(0.4,"The answer is partially correct");
	else quitf(_ok,"OK, you AK IOI");
	
	return 0;
}
```


---

---
title: "『JROI-3』1÷0"
layout: "post"
diff: 省选/NOI-
pid: P7894
tag: ['模拟', '单调队列', '2021', 'O2优化', '洛谷月赛']
---
# 『JROI-3』1÷0
## 题目背景

```
1÷0=梦恋
```
```
   在距离遥远的山丘上，看得见彼方宛如天地崩毁的光景。

    「——『设计体』传来报告——以功率《七二·八％》重现设计成功——开始同步。」

    一机机凯种的女性体这么告知里克，然后举起手。

    「【典开】——Org.0000——『真典·弑星者』——拜托您了。」

    ——出现在虚空中的是，外形有如小型的塔，刺在地上的一把枪。

    方才目睹的，有如让世界终结的暴力漩涡。

```
## 题目描述

空想用跳棋模拟「圣战」中机凯种的移动方式。

一条**无限长**的数轴上有 $n$ 个不能动的跳棋，空会询问把一颗可以动的跳棋放在一个位置可以**最多**进行几次跳跃。空会问很多次，每次询问**互相独立**。

设第 $i$ 颗不能动的棋子的坐标为 $x_i\left(\forall i\in\left[1,n\right]\right)$.

则跳棋移动的规则如下：

- 这颗跳棋必须是允许移动的。
- 若这颗棋子位于 $a$，目标位置为 $b$，则应**仅有一颗**棋子位于二个位置之间且中间棋子到 $a,b$ 的距离相等。

形式化的讲应有：

$$\sum_{k=1}^n \left[x_k\in\left[b,a\right]\right]=1$$

且 $\exists k\ x_k=\dfrac{a+b}{2}$.


- 出题人过于良心（，你只能向左边跳。

## 输入格式

第一行两个整数 $n,q$，同题意。

接下来一行 $n$ 个整数，第 $i$ 个表示 $x_i$。

接下来一行 $q$ 个数 $x_0$，表示放置可以动的棋子的位置。
## 输出格式

$q$ 行，每行一个整数，第 $i$ 行表示第 $i$ 次询问的结果。
## 样例

### 样例输入 #1
```
3 3
3 5 8
4 6 7
```
### 样例输出 #1
```
1
2
0
```
## 提示

#### 样例解释 1

$$\Huge\Box\Box\blacksquare{\color{red}{\Box}}\blacksquare{\color{red}{\Box}}{\color{red}{\Box}}\blacksquare\Box\Box$$

从左到右的三个红色方块是询问的位置。

- 对于第一个询问，可以跳 $1$ 步，从 4 跳到 2。
- 对于第二个询问，可以跳 $2$ 步，从 6 跳到 4 跳到 2。
- 对于第三个询问，棋子不能向左移动，因为左边同距离位置有一颗不能动的棋子。

对于 $100\%$ 的数据满足 $1\le n\leq 3\times 10^6$，$1\le q\leq3\times 10^5$，$1\le x\le 10^{18}$，$x_i+1\lt x_{i+1}(\forall i \in [1,n-1])$。

| Subtask 编号 | $n\le$ | $q\le$ | 时限 | 空间限制 | 特殊限制 |
| :-----------: | :-----: | :---: | :--: | :------:| :------: |
| Subtask 0 (10 pts) | $10^3$ | $10^3$ |  $1000\ \rm\small ms$ | $\rm512.00\small\  MB$ |  |
| Subtask 1 (30 pts) |  |  | $1000\ \rm\small ms$ | $\rm512.00\small\  MB$ | $\rm A$|
| Subtask 2 (25 pts) |  |  | $1000\ \rm\small ms$ | $\rm512.00\small\  MB$ | $\rm B$ |
| Subtask 3 (25 pts) | $3 \times 10^5$ |  | $400\ \rm\small ms$ | $\rm512.00\small\  MB$ |
| Subtask 4 (10 pts) |  |  | $400\ \rm\small ms$ | $\rm512.00\small\  MB$ |

- 限制 $\text{A}$： $x_n\le2\times 10^5$。
- 限制 $\text{B}$：有不超过 $50$ 个 $i$ 不满足 $x_i-x_{i-1}\le 100$ ，其余 $i$ 满足 $\sum_{i}{x_i-x_{i-1}} \le 2\times 10^5$。


---

---
title: "[NOIP2021] 方差"
layout: "post"
diff: 省选/NOI-
pid: P7962
tag: ['动态规划 DP', '2021', 'NOIP 提高组', 'O2优化', '模拟退火', '动态规划优化']
---
# [NOIP2021] 方差
## 题目描述

给定长度为 $n$ 的非严格递增正整数数列 $1 \le a_1 \le a_2 \le \cdots \le a_n$。每次可以进行的操作是：任意选择一个正整数 $1 < i < n$，将 $a_i$ 变为 $a_{i - 1} + a_{i + 1} - a_i$。求在若干次操作之后，该数列的方差最小值是多少。请输出最小值乘以 $n^2$ 的结果。

其中方差的定义为：数列中每个数与平均值的差的平方的平均值。更形式化地说，方差的定义为 $D = \frac{1}{n} \sum_{i = 1}^{n} {(a_i - \bar a)}^2$，其中 $\bar a = \frac{1}{n} \sum_{i = 1}^{n} a_i$。
## 输入格式

输入的第一行包含一个正整数 $n$，保证 $n \le {10}^4$。

输入的第二行有 $n$ 个正整数，其中第 $i$ 个数字表示 $a_i$ 的值。数据保证 $1 \le a_1 \le a_2 \le \cdots \le a_n$。
## 输出格式

输出仅一行，包含一个非负整数，表示你所求的方差的最小值的 $n^2$ 倍。
## 样例

### 样例输入 #1
```
4
1 2 4 6

```
### 样例输出 #1
```
52

```
### 样例输入 #2
```
见附件中的 variance/variance2.in
```
### 样例输出 #2
```
见附件中的 variance/variance2.ans
```
### 样例输入 #3
```
见附件中的 variance/variance3.in
```
### 样例输出 #3
```
见附件中的 variance/variance3.ans
```
### 样例输入 #4
```
见附件中的 variance/variance4.in
```
### 样例输出 #4
```
见附件中的 variance/variance4.ans
```
## 提示

**【样例解释 #1】**

对于 $(a_1, a_2, a_3, a_4) = (1, 2, 4, 6)$，第一次操作得到的数列有 $(1, 3, 4, 6)$，第二次操作得到的新的数列有 $(1, 3, 5, 6)$。之后无法得到新的数列。

对于 $(a_1, a_2, a_3, a_4) = (1, 2, 4, 6)$，平均值为 $\frac{13}{4}$，方差为 $\frac{1}{4}({(1 - \frac{13}{4})}^2 + {(2 - \frac{13}{4})}^2 + {(4 - \frac{13}{4})}^2 + {(6 - \frac{13}{4})}^2) = \frac{59}{16}$。

对于 $(a_1, a_2, a_3, a_4) = (1, 3, 4, 6)$，平均值为 $\frac{7}{2}$，方差为 $\frac{1}{4} ({(1 - \frac{7}{2})}^2 + {(3 - \frac{7}{2})}^2 + {(4 - \frac{7}{2})}^2 + {(6 - \frac{7}{2})}^2) = \frac{13}{4}$。

对于 $(a_1, a_2, a_3, a_4) = (1, 3, 5, 6)$，平均值为 $\frac{15}{4}$，方差为 $\frac{1}{4} ({(1 - \frac{15}{4})}^2 + {(3 - \frac{15}{4})}^2 + {(5 - \frac{15}{4})}^2 + {(6 - \frac{15}{4})}^2) = \frac{59}{16}$。

**【数据范围】**

| 测试点编号 | $n \le$ | $a_i \le$ |
|:-:|:-:|:-:|
| $1 \sim 3$ | $4$ | $10$ |
| $4 \sim 5$ | $10$ | $40$ |
| $6 \sim 8$ | $15$ | $20$ |
| $9 \sim 12$ | $20$ | $300$ |
| $13 \sim 15$ | $50$ | $70$ |
| $16 \sim 18$ | $100$ | $40$ |
| $19 \sim 22$ | $400$ | $600$ |
| $23 \sim 25$ | ${10}^4$ | $50$ |

对于所有的数据，保证 $1 \le n \le {10}^4$，$1 \le a_i \le 600$。


---

---
title: "[THUPC 2022 初赛] 喵喵花園"
layout: "post"
diff: 省选/NOI-
pid: P8212
tag: ['计算几何', '2022', 'Special Judge', 'O2优化', '模拟退火', 'THUPC']
---
# [THUPC 2022 初赛] 喵喵花園
## 题目描述

喵喵是一只非常富有的猫咪，他在海淀区拥有一个大花园。

这个大花园是由一些旧栅栏为边界所形成的 $N$-gon（即具有 $N$ 边的多边形）。

由于圣诞节快到了，喵喵想用 $K$ 棵圣诞树来装饰一下花园。 同时，喵喵坚信找到一些好的位置来种树会给他带来好运。

作为一只好猫咪，他决定寻找最佳位置如下：

- 所有的树都应该在花园的边界上。
- 这些 $K$ 树应该平均划分花园的周长。
- 由树木形成的新凸面$K$-gon 的面积应尽可能小。

虽然喵喵比你有钱，但他没有你那么聪明。 因此，他给了你一些钱，让你帮他找出凸$K$-gon 的最小面积。
## 输入格式

第一行包含两个整数，$N$ 和 $K$，代表原本花园边界的顶点数和树的数量。

接下来的每行 $N$ 行包含两个整数 $x_i$ 和 $y_i$，表示花园边界顶点的坐标。

所有座标均为逆时针给出的。
## 输出格式

输出凸面 $K$-gon 的最小面积。 如果相对或绝对误差不超过 $10^{-8}$，则您的答案被认为是正确的。
## 样例

### 样例输入 #1
```
5 4
0 0
1 0
2 1
2 2
0 2
```
### 样例输出 #1
```
1.9892766953
```
### 样例输入 #2
```
3 3
0 0
1 0
0 1
```
### 样例输出 #2
```
0.1226170434
```
## 提示

【数据范围】

- $3 \le N, K \le 1000$；
- $-10^5 \le x_i, y_i \le 10^5$。


---

---
title: "[THUPC 2022 决赛] 德州消消乐"
layout: "post"
diff: 省选/NOI-
pid: P8422
tag: ['模拟', '2022', 'O2优化', 'THUPC']
---
# [THUPC 2022 决赛] 德州消消乐
## 题目背景

众所周知小 c 是开心消消乐的高手，而小 z 玩这种稍微需要动一点脑子的游戏都很不在行。正值五一假期，小 c 闲得无聊就打算来教小 z。

经过五天五夜不间断教学，小 z 终于领悟了一点门道（小 z 内心 os：但凡能拿出一点热情来学概率论……），然而他俩都忽略了这玩意是会玩上瘾的，更关键的是小 z 来自山东，于是他打算融入一点家乡特色……

小 z：”……众所周知德州在山东，那我们就叫它‘德州消消乐’吧！“

小 c 连忙制止道你快算了吧，上次的大杂糅棋局你忘了？再说此德州非彼德州啊喂，这次你要搞就自己搞吧别拉我下水了。

话还没说完，小 z 转手把规则甩给了小 c。

小 c：“真香”。

## 题目描述

给定大小为 $n \times m$ 的棋盘，记左上角坐标为 $(1,1)$ ，右下角坐标为 $(n,m)$ 。有不同颜色的棋子共 $k$ 种，颜色编号为 $1\sim k$ 。最初每个格子都有一个棋子。

共有 $q$ 次操作，每次操作形如交换相邻（在上、下、左、右方向）的两个棋子。在此之后，在同一行或同一列的连续至少 $3$ 个相同颜色的棋子会被消除。

消除后，所有棋子会遵循重力下落，这一列的最上方变成空位。所有棋子下落完成后，如果又产生了能消除的情况，则会触发连锁反应继续消除，直到无法消除为止。称一次消除+一次下落为“一轮消除”，由此可以定义一次操作触发的消除“轮数”。

其中，有些棋子具有特殊属性，被消除时会触发特殊效果，一共有以下 $6$ 类：

- 1、消除时将同一行的全部棋子消除；
- 2、消除时将同一列的全部棋子消除；
- 3、消除时将同一行和同一列的全部棋子消除；
- 4、消除时将以之为中心 $3 \times 3$ 的正方形范围内的棋子全部消除；
- 5、消除时将以之为中心 $5 \times 5$ 的正方形范围内的棋子全部消除；
- 6、消除时将与之颜色相同的棋子全部消除； 

触发一个棋子的特殊效果时可能连锁触发其他棋子的特殊效果，但是这些都是在同一轮消除内触发的（即连锁反应触发的过程中不会引起下落）。

游戏中，每次操作都要求必须有效，即操作的两个位置相邻且均不为空位，且在操作之后能进行棋子的消除。若某此操作并非有效，则直接跳过这一次操作。所有 $q$ 次操作结束后游戏结束。

定义一次有效操作的“主颜色”为通过交换而直接被消除的颜色（即不包括特殊效果触发和下落引起的消除），容易发现一次有效操作的主颜色至少有 $1$ 种，最多有 $2$ 种。

游戏中，玩家要通过操作来获取尽可能多的得分。得分的规则有如下 $5$ 种：消除奖分+连锁奖分+组合奖分+牌型奖分+终局奖分。

- 消除奖分：每次有效操作中，第 $i$ 轮消除的消除奖分为这一轮中所有被消除的棋子的颜色编号之和的 $i$ 倍。
- 连锁奖分：设某次有效操作的总消除轮数为 $x$ ，则有连锁奖分 $80(x-1)^2$ 。
- 组合奖分：某一轮消除中，在仅考虑由“同一行或同一列至少连续 $3$ 个相同颜色”引发的消除的情况下（即不考虑所有特殊效果引起的消除），设某个被消除的同色四连通块大小为 $x$ ，则有组合奖分 $50(x-3)^2$ 。如： $4$ 个同色棋子组成四连的组合奖分为 $50$ ，$5$ 个同色棋子组成五连、十字或T字等形状的组合奖分为 $200$ ，$2\times3$ 的方形同色棋子的组合奖分为 $450$ 。
 - 牌型奖分：每 $5$ 次有效操作计算一次牌型奖分，取之前 $5$ 次有效操作的主颜色（若某次操作有多个主颜色，取能按照以下规则计算出的最大奖分的主颜色），按照如下牌型规则计算奖分：
   
   - 高牌： $5$ 种颜色全部不同，奖 $50$ 分 + 所有牌中最大的颜色编号；
   - 一对： $2$ 个相同颜色 + $3$ 个不同颜色，奖 $100$ 分 + 一对的颜色编号 $\times 2$ ；
   
   - 两对： $2$ 对相同颜色 + $1$ 个其他颜色，奖 $200$ 分 + 两对中较大的颜色编号 $\times 2$ + 两对中较小的颜色编号；
   - 三条： $3$ 个相同颜色 + $2$ 个不同颜色，奖 $300$ 分 + 三条的颜色编号 $\times 3$ ；
   - 葫芦： $3$ 个相同颜色 + 另外 $2$ 个相同颜色，奖 $500$ 分 + 三个相同的颜色编号 $\times 3$ + 两个相同的颜色编号；
   - 四条： $4$ 个相同颜色 + $1$ 个其他颜色，奖 $750$ 分 + 四条的颜色编号 $\times 5$ ；
   - 五条： $5$ 个颜色全部相同，奖 $1000$ 分 + 五条的颜色编号 $\times 10$ 。
 - 终局奖分：若所有 $q$ 次操作均有效，在终局时额外获得 $1000$ 分终局奖分；若游戏结束时棋盘被全部清空，额外获得 $10000$ 分的终局奖分。

给定一局游戏的初始局面和玩家的每一次操作，你需要计算玩家的总得分。
## 输入格式

第 $1$ 行： $4$ 个正整数 $n,m,k,q$ 。

接下来 $n$ 行，每行 $m$ 个正整数 $a_{i,j}$ ，表示初始状态下，从上往下第 $i$ 行、从左往右第 $j$ 列的棋子的颜色。

接下来 $n$ 行，每行 $m$ 个非负整数 $b_{i,j}$ ，表示初始状态下，从上往下第 $i$ 行、从左往右第 $j$ 列的棋子的特殊效果，含义如题面所述。特别地， $b_{i,j}=0$ 表示没有特殊效果。

接下来 $q$ 行，每行 $4$ 个正整数 $x_{i,1},y_{i,1},x_{i,2},y_{i,2}$ ，表示交换坐标 $(x_{i,1},y_{i,1})$ 和 $(x_{i,2},y_{i,2})$ 位置的棋子。
## 输出格式

输出一行，一个非负整数表示终局时的总得分。
## 样例

### 样例输入 #1
```
8 8 5 5
1 1 5 1 5 4 5 3
2 1 2 2 5 4 3 2
1 4 1 4 2 1 5 4
2 1 5 5 2 1 4 4
2 3 5 2 3 4 2 2
4 2 4 3 3 2 4 5
1 3 4 3 5 2 4 3
3 4 2 5 2 1 1 2
0 0 0 0 0 0 0 0
2 0 0 0 0 0 0 0
0 0 0 0 5 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 6 0 0 3 1
0 0 0 0 3 0 0 0
0 0 0 0 0 0 1 4
3 2 4 2
5 4 5 5
7 2 7 3
8 5 8 6
6 7 6 8

```
### 样例输出 #1
```
11692

```
### 样例输入 #2
```
8 8 5 8
1 1 5 1 5 4 5 3
2 1 2 2 5 4 3 2
1 4 1 4 2 1 5 4
2 1 5 5 2 1 4 4
2 3 5 2 3 4 2 2
4 2 4 3 3 2 4 5
1 3 4 3 5 2 4 3
3 4 2 5 2 1 1 2
0 0 0 0 0 0 0 0
2 0 0 0 0 0 0 0
0 0 0 0 5 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 6 0 0 3 1
0 0 0 0 3 0 0 0
0 0 0 0 0 0 0 0
1 1 2 2
3 2 4 2
3 2 3 3
4 2 4 3
5 4 5 5
7 2 7 3
8 5 8 6
6 7 6 8

```
### 样例输出 #2
```
684

```
### 样例输入 #3
```
5 5 2 1
1 1 2 1 1
1 1 2 1 1
2 2 1 2 2
1 1 2 1 1
1 1 2 1 1
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
3 3 4 3

```
### 样例输出 #3
```
3023

```
## 提示

【样例 1 解释】

每次操作后，前 $3$ 类奖分的和分别为：$315,\ 417,\ 429,\ 435,\ 482$ 。第 $5$ 次操作后计算牌型奖分，最优牌型为 $(1\ 2\ 4\ 2\ 4)$ ，奖分为 $200 + 4\times 2 + 2 \times 1 = 210$ 。终局时两种终局奖分均可获得，故总分为 $11692$ 。

【样例 2 解释】

与上一组样例相比，增加了 $3$ 次无效操作，且最后不能实现全消，因此得不到终局奖分。

【数据范围与约定】


$n,m\leq 50,\ k \leq 100,\ q \leq 1000,\ a_{i,j} \leq k,\ b_{i,j} \leq 6,\ x_{i,1},x_{i,2} \leq n,\ y_{i,1},y_{i,2} \leq m$ 。

保证初始局面没有可以直接消除的情况。


---

---
title: "[JRKSJ R7] TSM eerT"
layout: "post"
diff: 省选/NOI-
pid: P8934
tag: ['模拟', '2023', '洛谷原创', 'O2优化', '树的直径']
---
# [JRKSJ R7] TSM eerT
## 题目描述

对于一个 $n$ 个结点的带边权的树 $T$，定义 $dis(x,y)$ 为 $T$ 中 $x\to y$ 路径上的边权和。再定义一个 $n$ 个结点的无向完全图 $p(T)=G$，其中 $\forall x,y\in [1,n]$，$G$ 中边 $(x,y)$ 的边权为 $dis(x,y)$。

定义 $f(T)$ 为 $p(T)$ 的最大生成树。特别的，若 $p(T)$ 的最大生成树不唯一，请立刻判断出并报告。

给定树 $T_0$ 和整数 $k$，求 $f^k(T_0)$。其定义将在下文给出。
## 输入格式

第一行两个整数 $n,k$。\
下面第 $2\sim n$ 行，第 $i$ 行两个整数 $i-f_i,v_i$ 表示 $T_0$ 的一条边 $(i,f_i)$，边权为 $v_i$。**也就是说，这一行输入了两个整数 $f'_i,v_i$，真实的 $f_i=i-f'_i$。**
## 输出格式

输出仅有一个整数表示答案。

若 $\exists x\in[0,k-1]$ 使得 $p(f^x(T_0))$ 的最大生成树不唯一，输出 $-1$。否则，输出 $f^k(T_0)$ 的所有边权和对 $2^{32}$ 取模的结果。
## 样例

### 样例输入 #1
```
3 3
1 1
2 2
```
### 样例输出 #1
```
13
```
### 样例输入 #2
```
10 2
1 7
1 2
1 5
4 5
2 1
3 9
2 9
4 4
9 4
```
### 样例输出 #2
```
736
```
### 样例输入 #3
```
4 1
1 1
2 1
3 1
```
### 样例输出 #3
```
-1
```
## 提示

### 定义

$f^k(T)$ 的定义为：
$$f^k(T)=\begin{cases}T&k=0\\f(f^{k-1}(T))&k>0\end{cases}$$

### 样例 $1$ 解释


![](https://cdn.luogu.com.cn/upload/image_hosting/fpcq3bmt.png)

分别是 $T_0,f(T_0),f^2(T_0),f^3(T_0)$。

以计算 $f(T_0)$ 的过程为例，生成的 $p(T_0)=G$ 为

![](https://cdn.luogu.com.cn/upload/image_hosting/3st5aet7.png)

最大生成树上的边为 $(1,3),(2,3)$。

### 数据规模

本题采用捆绑测试。
| $\text{Subtask}$ | $n\le$ |  $k\le$ | $\text{Score}$ | 
| :----------: | :----------: | :----------: | :----------: | 
| $1$ | $10^3$ | $1$ | $10$ | 
| $2$ | $10^5$ | $1$ |$20$ |
| $3$ | $10^6$ | $1$ |$30$ |
| $4$ | $10^6$ | $10^7$ |$40$ |

对于 $100\%$ 的数据，$2\le n\le 10^6$，$1\le k\le 10^7$，$1\le f_i<i$，$1\le v_i\le10^9$。

### 特殊评分方式
本题开启子任务依赖，具体如下：
- 对于子任务 $i$，您需要答对所有 $j\in[1,i]$ 的子任务 $j$ 才能获得子任务 $i$ 的分数。


---

---
title: "[THUPC 2023 初赛] 拧螺丝"
layout: "post"
diff: 省选/NOI-
pid: P9134
tag: ['模拟', '高精度', '2023', 'O2优化', 'THUPC']
---
# [THUPC 2023 初赛] 拧螺丝
## 题目背景

张华考上了北京大学；李萍进了中等技术学校；~~小 E 在工地搬砖~~：他们都有光明的前途。

由于搬砖太累，小 E 决定进厂拧螺丝。但是小 E 遇到了一个各种刁难人的老板。
## 题目描述

加工一个模块需要拧 $n$ 个螺丝。但是，每隔 $10$ 分钟，小 E 的老板就会到小 E 的工位上收走一个未完工的模块。在这期间，只够小 E 拧 $k$ 个螺丝。

小 E 的老板刚刚离开。问老板接下来第几次来的时候小 E 才可能有一个完工的模块？假设小 E 的老板极力不想让小 E 达成这件事。
## 输入格式

一行两个正整数，$n,k$。
## 输出格式

如果小 E 无论如何也不能有一个完工的模块，那么输出一行 `Poor E.S.!`。

否则输出一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
3 2

```
### 样例输出 #1
```
2

```
## 提示

#### 样例解释 1

小 E 先选择两个模块各拧上一个螺丝，然后老板来了拿走一个。接下来小 E 只需要在剩下的那个零件上面拧两个螺丝就可以完工了。所以老板第二次来的时候小 E 就有了一个完工的模块。注意小 E 在老板来的时候不能有只拧上了一半的螺丝，不然老板看到了会说小 E 加工不合格。

#### 子任务

保证 $1\le k \le n \le 10^5$。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

---
title: "[THUPC 2023 决赛] 那些脑海里最珍贵的"
layout: "post"
diff: 省选/NOI-
pid: P9381
tag: ['模拟', '2023', 'O2优化', 'THUPC']
---
# [THUPC 2023 决赛] 那些脑海里最珍贵的
## 题目背景

E.Space：设定很怪，别问为什么，问就是看附件。

_没有人听懂的傻话_

_还记得吗_

_写满青春的围墙_

_好努力练习的倔强_

_浅浅伤疤_

_勇敢是我们的翅膀_

_——张韶涵《还记得吗》_
## 题目描述

故事的世界观大概是这样的。这个世界的人分为三类，根据其某种特点被直接命名为 Weak，Average 和 Strong。你可以理解为这是一个关于种族或者职业的分类。

两个队伍之间发生了一场回合制战斗。你知道双方做了什么，现在希望你把所有的细节还原出来。

下面是本题的一些技术细节。

**【人物】**

一个人有以下几种属性值：「种族」、「等级」、「体力上限」、「基础攻击指数」、「基础防御指数」、「主动技能等级」、「被动技能等级」。其中「体力上限」、「基础攻击指数」、「基础防御指数」完全由「种族」和「等级」决定。但是为了输入方便，本题中所有信息都会给出。在战斗中，每个人有一个「体力值」。在战斗开始时，「体力值」等于「体力上限」。当「体力值」小于等于 $0$ 时这个人就会「倒下」。对于同一个「种族」而言，「体力上限」、「基础攻击指数」、「基础防御指数」大致随「等级」指数增长。每个人持有一把「武器」。「武器」的细节在下一节给出。

**【武器】**

「武器」的属性只有两种：「武器类型」和「武器攻击力」。所有「武器」都有「普通攻击」和「特殊攻击」两种攻击方式。发起「攻击」指使用这两种方式中的任意一种。「普通攻击」的效果与「武器类型」无关，但不同的「武器类型」有着不同的「特殊攻击」效果。「武器」有三种类型，分别叫做「B」、「G」、「M」。

**【战场与队伍】**

交战双方的每一方包含不超过 $6$ 名队员，一字排开，从西到东的编号分别为 $5,3,1,2,4,6$（若不足 $6$ 名则删去较大的若干个编号）。方便起见，就叫两队为「南队」和「北队」。

**【回合】**

每个「回合」中，只有一个人可以「行动」。第奇数个「回合」是「南队」的队员「行动」，第偶数个「回合」是「北队」的队员「行动」。第一个「回合」和第二个「回合」中，「行动」的人是队伍里未「倒下」的编号最小的人。之后的「回合」中，若本队中没有编号比本队上一个「行动」的人大且未「倒下」的人，则由本队中编号最小的未「倒下」的人「行动」。否则由编号大于本队上一个「行动」者的人中，编号最小且未「倒下」的人「行动」。若一个队伍中的所有队员均已「倒下」，则判另一个队伍「胜利」。

**【行动】**

「行动」一共有三种。当前「回合」中「行动」的人必须选择三种之一来完成。

1. 「普通攻击」；
2. 「特殊攻击」；
3. 「主动技能」。

这些「行动」的效果会在之后介绍。「特殊攻击」和「主动技能」是有次数限制的，但是在本题中，保证所有「行动」均合法，所以你不需要考虑这个限制。

**【伤害计算】**

「伤害」指的是因为「普通攻击」或「特殊攻击」而造成的「体力值」减少。

「伤害」，即「体力值」减少的量，由「攻击强度」和受到「伤害」的人的「防御指数」决定。

一个人的「防御指数」等于这个人的「基础防御指数」乘以队伍的「防御加成」。

具体地，若一个人受到「攻击强度」为 $x$ 的「伤害」，那么这个人的「体力值」就会减少 $y$。其中 $y$ 的值等于 $x$ 除以这个人的「防御指数」下取整。

「攻击强度」等于「基础攻击强度」乘以发起「攻击」的人的「技能加成」乘以队伍的「攻击加成」乘以「种族克制加成」乘以「方位加成」。这些概念会在之后介绍。

**【普通攻击】**

选择一个敌方未「倒下」的队员作为「目标」。「目标」受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」的「伤害」。

**【特殊攻击】**

选择一个敌方未「倒下」的队员作为「目标」。

「武器」有三种，不同「武器类型」的「特殊攻击」效果如下：

- 「B」：「目标」受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $125\%$ 的「伤害」。
- 「G」：「目标」和「目标」东西两侧与「目标」距离最近的各一名未「倒下」的队员（如果存在）均受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $x\%$ 的「伤害」。其中 $x$ 的值等于 $135$ 除以将要受到「伤害」的人数。「伤害」按照「目标」、「目标」西侧、「目标」东侧的顺序计算。注意如果过程中有人「倒下」，那么这个人的「被动技能」将不再对该顺序中位于这个人之后的人的「伤害」结算起作用。特别地，所有「伤害」的「方位加成」以「目标」的「躲闪方位」来计算。
- 「M」：「目标」受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $115\%$ 的「伤害」。「目标」东西两侧与「目标」距离最近的各一名未「倒下」的队员（如果存在）分别受到「基础攻击强度」为发起「攻击」的人的「基础攻击指数」乘「武器攻击力」乘 $23\%$ 的「伤害」。「伤害」按照「目标」、「目标」西侧、「目标」东侧的顺序计算。注意如果过程中有人「倒下」，那么这个人的「被动技能」将不再对该顺序中位于这个人之后的人的「伤害」结算起作用。特别地，所有「伤害」的「方位加成」以「目标」的「躲闪方位」来计算。

**【技能】**

「技能」分为「主动技能」和「被动技能」。每个「种族」的人都有一个「主动技能」和一个「被动技能」。「技能」的效果因「种族」和「技能等级」的不同而不同。「技能等级」为一个 $0$ 到 $5$ 之间的整数。「技能等级」为 $0$ 表示没有该「技能」。

使用「主动技能」需要选择一个人作为「技能目标」。

「主动技能」描述如下：（$1$ 到 $5$ 级的「技能」效果由斜杠隔开，保证使用「主动技能」的人的「主动技能等级」不为 $0$）

- 「Weak 种族」：使本队一名未「倒下」的队员的「体力值」增加这名队员的「体力上限」乘以 $10\%/12\%/15\%/17\%/20\%$ 下取整。
- 「Average 种族」：选择一名敌方未「倒下」的队员，在使用该「主动技能」这一队的「回合」结束时，其「体力值」减去其「体力上限」的 $6\%/7\%/8\%/9\%/10\%$ 下取整。该效果持续 $3$ 个回合，即会触发 $3$ 次。若该队员已有同类型（可以是不同等级）的「技能」施加的效果，那么这个效果将会覆盖之前的效果。
- 「Strong 种族」：使本队一名未「倒下」的队员的「技能加成」变为 $2.1/2.17/2.24/2.32/2.4$。

一名队员的「被动技能」只有当该队员未「倒下」时才能发挥效果，「倒下」之后不再发挥效果。

「被动技能」描述如下：

- 「Weak 种族」：在本队的「回合」开始时，本队所有未「倒下」的成员的「体力值」增加该成员「体力上限」的 $1.3\%/1.6\%/1.9\%/2.2\%/2.5\%$。若本队有多名队员有这个「技能」，这个效果的数值可以相加至最多 $5\%$。超过 $5\%$ 按照 $5\%$ 计算。「体力值」增加的量在效果叠加后需要下取整。
- 「Average 种族」：队伍的「防御加成」初始为 $1$。该技能使队伍的「防御加成」增加 $0.01/0.02/0.03/0.04/0.05$。若本队有多名队员有这个「技能」，这个效果的数值可以相加至最多 $0.1$。超过 $0.1$ 按照 $0.1$ 计算。
- 「Strong 种族」：队伍的「攻击加成」初始为 $1$。该技能使队伍的「攻击加成」增加 $0.01/0.02/0.03/0.04/0.05$。若本队有多名队员有这个「技能」，这个效果的数值可以相加至最多 $0.1$。超过 $0.1$ 按照 $0.1$ 计算。

一名队员的「体力值」增加时，不能超过这名队员的「体力上限」。若增加后的「体力值」超过了「体力上限」，则把这次增加「体力值」的效果改为将这名队员的「体力值」变成这名队员的「体力上限」。

**【技能加成】**

战斗开始时，所有人的「技能加成」都是 $1$。只有两种方式能够改变「技能加成」：

- 「Strong 种族」的「主动技能」。见「技能」的描述。
- 当一个人发起「攻击」且计算完这次「攻击」的所有「伤害」之后，这个人的「技能加成」变为 $1$。

**【种族克制加成】**

「种族克制加成」与发起「攻击」的人的「种族」以及受到「伤害」的人的「种族」有关。「种族克制加成」的值如下表：


| 发起「攻击」方/受到「伤害」方 | Weak  | Average | Strong |
| :---------------------------: | :---: | :-----: | :----: |
|             Weak              | $1.0$ |  $0.9$  | $1.1$  |
|            Average            | $1.1$ |  $1.0$  | $0.9$  |
|            Strong             | $0.9$ |  $1.1$  | $1.0$  |



**【方位加成】**

在「攻击」时，发起「攻击」的一方有一个「攻击方位」，「攻击」的「目标」有一个「躲闪方位」。「攻击方位」和「躲闪方位」分别为一个 $1$ 到 $6$ 之间的整数。当「攻击方位」为 $a$，「躲闪方位」为 $d$ 时，「方位加成」的值由下表所示：


| $(a-d)\bmod 6$ | 「方位加成」 |
| :------------: | :----------: |
|      $0$       |    $1.25$    |
|   $1$ 或 $5$   |    $1.00$    |
|   $2$ 或 $4$   |    $0.75$    |
|      $3$       |    $0.00$    |


## 输入格式

从标准输入读入数据。

第一行两个正整数 $n,m$，分别表示「南队」的人数和「北队」的人数。

接下来 $n$ 行，其中第 $i$ 行表示「南队」中编号为 $i$ 的队员的信息，格式如下：

`<Type> Lv=<Lv> maxhp=<maxhp> atk=<atk> def=<def> skillLv=<skillLv> passivesklLv=<passivesklLv> <weapontype> weaponatk=<weaponatk>`

其中尖括号中的内容表示一个变量。

`<Type>` 为 `Weak`，`Average`，`Strong` 中的一种，分别表示对应名称的「种族」。

`<Lv>` 为一个 $1$ 到 $100$ 之间的整数，表示队员的「等级」。

`<maxhp>` 为一个整数，表示队员的「体力上限」。

`<atk>` 为一个实数，表示队员的「基础攻击指数」。

`<def>` 为一个实数，表示队员的「基础防御指数」。

`<skillLv>` 为一个 $0$ 到 $5$ 之间的整数，表示队员的「主动技能等级」。

`<passivesklLv>` 为一个 $0$ 到 $5$ 之间的整数，表示队员的「被动技能等级」。

`<weapontype>` 为 `B`，`G`，`M` 中的一种，分别表示对应名称的「武器类型」。

`<weaponatk>` 为一个实数，表示队员的「武器攻击力」。

接下来 $m$ 行，其中第 $i$ 行表示「北队」中编号为 $i$ 的队员的信息，格式与「南队」相同。

接下来一行一个正整数 $T$，表示进行的「回合」数。

接下来 $T$ 行，其中第 $i$ 行表示第 $i$ 个「回合」的「行动」。

「行动」的描述以一个字符串开头，表示「行动」的类型。

`Basicattack target=<target> atkpos=<atkpos> ddgpos=<ddgpos>` 表示一次「普通攻击」。

`Specialattack target=<target> atkpos=<atkpos> ddgpos=<ddgpos>` 表示一次「特殊攻击」。

`Skill target=<target>` 表示使用 「主动技能」。保证该队员的「技能等级」不是 $0$。

其中，`<target>` 表示「目标」或「技能目标」的编号。若是「Weak 种族」或「Strong 种族」的「主动技能」，这个编号是一个己方队员的编号，否则是一个敌方队员的编号。

`<atkpos>` 为一个 $1$ 到 $6$ 之间的整数，表示「攻击方位」。

`<ddgpos>` 为一个 $1$ 到 $6$ 之间的整数，表示「躲闪方位」。

保证所有的「行动」均合法。

为了方便起见，本题中实数的表示方法较为特殊。具体的表示方法是，用 `<mag>e<exp>` 的方式来表示 `<mag>` 乘以 $10$ 的 `<exp>` 次方。其中 `<mag>` 是一个 $1$ 到 $99999$ 之间的正整数，`<exp>` 是一个 $-6$ 到 $0$ 之间的整数。如 $42.195$ 可以表示成 `42195e-3`，$6$ 可以表示成 `6e0` 或 `600e-2` 等，$0.04$ 可以表示成 `4e-2` 等。
## 输出格式

输出到标准输出。

对于每个「回合」，按时间顺序把这个「回合」的信息输出来。

信息的格式如下：

`<team> <id> recovered +<heal> hp -> <curhp>/<maxhp>` 表示「Weak 种族」的「技能」所造成的「体力值」增加。如果在增加之前「体力值」就已经等于「体力上限」，那么不需要输出这一行。

`<team> <id> took <dmg> damage from <atkteam> <atkid> -> <curhp>/<maxhp>` 表示一名队员受到「伤害」。

`<team> <id> took <dmg> damage from skill -> <curhp>/<maxhp>` 表示「Average 种族」的「主动技能」所造成的「体力值」减少。

`<team> <id> applied <type> skill to <targetteam> <targetid>` 表示使用「主动技能」。

其中 `<team>` 表示队伍名称，为 `South` 或 `North` 之一，分别表示南队/北队。

`<id>` 表示「体力值」发生改变的人在队伍中的编号，为一个 $1$ 到 $6$ 之间的正整数。

`<heal>` 表示本应该增加的「体力值」数量（不考虑「体力上限」的限制），为一个正整数。

`<curhp>` 指的是「体力值」发生改变之后的「体力值」，为一个非负整数。若「体力值」减小到 $0$ 以下输出 $0$。

`<maxhp>` 表示「体力值」发生改变的人的「体力上限」，为一个正整数。

`<dmg>` 为受到的「伤害」或「Average 种族」的「主动技能」所造成的「体力值」减少，为一个非负整数。

`<type>` 为使用「主动技能」的人的「种族」，为 `Weak`，`Average`，`Strong` 之一。

`<atkteam>` 和 `<atkid>` 为发起「攻击」的人的队伍名称和编号，格式同 `<team>` 和 `<id>`。

`<targetteam>` 和 `<targetid>` 为「技能目标」的队伍名称和编号，格式同 `<team>` 和 `<id>`。

时间顺序如下：

「回合」开始时，可能触发「Weak 种族」的「被动技能」效果，按照编号从小到大输出。

如果是使用「主动技能」，则输出一行使用「主动技能」的信息。

然后输出「行动」所造成的「体力值」变化信息。若「伤害」为 $0$ 也要输出。若没有造成「伤害」则不输出。若「特殊攻击」改变了多个人的「体力值」，则按照「目标」、「目标」西边的人、「目标」东边的人的顺序输出。

「回合」结束时，可能触发「Average 种族」的「主动技能」效果，按照编号从小到大输出。

每个「回合」结束后输出两队的「体力值」信息，格式如下：

`<team>: [<curhp5>/<maxhp5>] [<curhp3>/<maxhp3>] <curhp1>/<maxhp1> [<curhp2>/<maxhp2>] [<curhp4>/<maxhp4>] [<curhp6>/<maxhp6>]`

其中，`<team>` 表示队伍名称，`<curhpi>` 表示队伍中编号为 $i$ 的人的「体力值」，`<maxhpi>` 表示队伍中编号为 $i$ 的人的「体力上限」。两个人的「体力值」信息之间有恰好一个空格，第一个「体力值」信息和冒号之间有恰好一个空格。已「倒下」的人的「体力值」信息也需要输出。方括号表示，若队伍中不存在编号为 $i$ 的人则不输出。注意这里按照位置顺序而不是编号顺序输出，即顺序为 $5,3,1,2,4,6$。

先输出一行「北队」的信息，再输出一行「南队」的信息。

每个「回合」的信息以一个空行结束。

所有「回合」结束后，若有一个队伍「胜利」，则输出一行 `Team <team> won.`。其中 `<team>` 是队伍名称，为 `South` 或 `North`。因为「行动」需要指定一个未「倒下」的人作为「目标」或「技能目标」，且所有「行动」均合法，所以，如果有队伍「胜利」，则一定是在最后一个「回合」结束后才「胜利」。若没有队伍「胜利」则不输出。
## 样例

### 样例输入 #1
```
2 1
Strong Lv=90 maxhp=2451 atk=15588e-4 def=96931e-3 skillLv=5 passivesklLv=5 M weaponatk=80000e0
Strong Lv=100 maxhp=3512 atk=16385e-4 def=12511e-2 skillLv=5 passivesklLv=5 G weaponatk=80000e0
Weak Lv=1 maxhp=100000 atk=75000e-5 def=10000e-6 skillLv=5 passivesklLv=5 B weaponatk=80000e0
3
Skill target=2
Specialattack target=1 atkpos=3 ddgpos=3
Specialattack target=1 atkpos=5 ddgpos=5

```
### 样例输出 #1
```
South 1 applied Strong skill to South 2
North: 100000/100000
South: 2451/2451 3512/3512

South 1 took 1063 damage from North 1 -> 1388/2451
North: 100000/100000
South: 1388/2451 3512/3512

North 1 took 52556526 damage from South 2 -> 0/100000
North: 0/100000
South: 1388/2451 3512/3512

Team South won.

```
## 提示

**【样例 #2】**

见题目目录下的 *2.in* 与 *2.ans*。

**【样例解释 #2】**

这个样例，无疑是善良的出题人无私的馈赠。中间忘了。出题人相信，这个美妙的样例，可以给拼搏于 AC 这道题的逐梦之路上的你，提供一个有力的援助。

**【数据范围】**

保证 $1\le n,m \le 6$。

保证 $1\le T \le 50000$。

保证「武器攻击力」的范围在 $300$ 到 $80000$ 之间。

「体力上限」「基础攻击指数」「基础防御指数」的范围见下表。

| 「种族」与「等级」 | 「体力上限」 | 「基础攻击指数」 | 「基础防御指数」 |
| :----------------: | :----------: | :--------------: | :--------------: |
|     Weak Lv.1      |   $100000$   |    $0.75000$     |    $0.010000$    |
|    Average Lv.1    |    $5000$    |    $0.80000$     |    $0.20000$     |
|    Strong Lv.1     |    $100$     |     $1.0000$     |     $10.000$     |
|    Weak Lv.100     |  $7807514$   |     $1.0089$     |    $0.10464$     |
|   Average Lv.100   |   $252234$   |     $1.3108$     |     $1.8101$     |
|   Strong Lv.100    |    $3512$    |     $1.6385$     |     $125.11$     |

 

**【后记】**

_有一天我将会老去_

_希望你会觉得满意_

_我没有 对不起那个_

_十五岁的自己_

_——刘若英《继续-给十五岁的自己》_

**【题目来源】**

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）决赛。

题解等资源可在 [https://github.com/THUSAAC/THUPC2023](https://github.com/THUSAAC/THUPC2023) 查看。


---

---
title: "「PFLOI R1」PFL 变换"
layout: "post"
diff: 省选/NOI-
pid: P9591
tag: ['洛谷原创', 'Special Judge', 'O2优化', '模拟退火', '构造', 'Ad-hoc', '分类讨论']
---
# 「PFLOI R1」PFL 变换
## 题目背景

五大高手云集于此，思想的火花激烈碰撞。很快，PFLOI Round 1 准备完毕。

开始了……
## 题目描述

新的征途已经开始：智力踏上了寻香蕉之旅。道路上共有 $n$ 个香蕉，编号从 $1$ 到 $n$。

智力看到如此美食，非常激动。但是智力不想吃得太饱或太少，所以它会吃**刚好** $m$ 个香蕉。

智力是一个挑剔的人，只有当它吃的 $m$ 个香蕉的编号的异或和**恰好为** $2^{\lfloor\log_2 n\rfloor+1}-1$ 时他才会满意。请你帮忙找出他应该吃哪些香蕉，好让他满意。

如果怎样都不能满足智力的需求，就请输出 `-1` 吧。

------------

**形式化题面**：

请你从 $1$ 到 $n$ 中选出 $m$ 个数，使得它们的异或和恰好为 $2^{\lfloor\log_2 n\rfloor+1}-1$。若无解输出 `-1`。
## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示一共有 $T$ 组测试数据。

对于每组测试数据，每行两个整数 $n$ 和 $m$，含义见题面。
## 输出格式

对于每组测试数据，若有解，输出一行共 $m$ 个整数，表示你选择的 $m$ 个数；若无解，输出 `-1`。

**本题采用 Special Judge**。若有多种可能的解，任意输出一个即可。
## 样例

### 样例输入 #1
```
7
5 2
6 6
7 6
8 3
9 3
10 1
7 4
```
### 样例输出 #1
```
3 4
1 6 2 4 3 5 
1 2 3 4 5 6
8 6 1
8 1 6
-1
3 5 6 7
```
## 提示

**本题不采用捆绑测试**。

| 测试点编号 | 特殊性质 | 分值 |
| :----------: | :----------: | :-----:| 
| $1,2$ | $n\le15$ | $2\times4=8$ |
| $3\sim11 $ | $n\le128$ | $9\times3=27$ |
| $12\sim24 $ | $\sum n\le10^5$ | $13\times3=39$ |
| $25\sim29$ | 无特殊限制 | $5\times4=20$ |
| $30$ | 无特殊限制 | $1\times6=6$ |

对于所有数据，$1\le m\le n\le10^6$，$1\le\sum n,T\le10^6$。


---

---
title: "[ICPC 2020 Nanjing R] Go"
layout: "post"
diff: 省选/NOI-
pid: P9628
tag: ['模拟', '图论', '2020', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Go
## 题目描述

$\textit{Go}$ is an adversarial game with the objective of surrounding a larger total area of the board with one's stones than the opponent's. The core idea of the game is the concept of $\textit{liberty}$, which is an open point, or rather, an intersection of vertical and horizontal lines on the chessboard with no stones on it, bordering the group.

A stone, white or black, is called $\textit{alive}$ if it has at least one liberty directly orthogonally adjacent (up, down, left, or right), or must be in the same connected group with a stone of the same color which is alive. We say two stones of the same color are directly connected if they're orthogonally adjacent. We say two stones $s_1$ and $s_k$ of the same color are in the same connected group if there exists a sequence of stones $s_1, s_2,\cdots, s_k$ such that for all $1 \le i < k$, $s_{i-1}$ and $s_i$ are of the same color and are directly connected.

For example, in the left part of the below figure, neither of the two white stones is alive, as they're captured by the surrounding black stones; While in the right part, the rightmost white stone is also not alive, even if the leftmost black stone is also not alive.

![](https://cdn.luogu.com.cn/upload/image_hosting/zjm3icu0.png)

Given a chessboard with $n$ vertical and $n$ horizontal lines where some stones might be lying on, please calculate the number of white stones captured by the black ones (that is to say, calcaulate the number of white stones not alive). The results for the above examples are $2$ and $1$, respectively.

However, our dear friend Kotori thinks that this problem is too simple for our clever contestants to solve, so she would like to heat things up by instead asking you to flip the color of each stone (that is to say, change a black stone to a white one, or vice versa$^1$) independently and find out the corresponding answer after each flip.

By flipping independently we mean that before flipping the color of a stone, the other stones should change back to their original color. Also note that the data in this problem is not from the real world, which means that the size of the chessboard is not necesssarily $19 \times 19$, and the number of white and black stones can be any integer.

$^1$ Vice versa: The reverse is also true. Here it can be replaced with ``change a white stone to a black one``. This is a very common phrase in modern English especially in academic writing, so please bear it in mind.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains one integer $n$ ($2\le n \le 10^3$) indicating the length of the board side.

For the next $n$ lines, the $i$-th line contains a string $s_{i,1},s_{i,2},\cdots,s_{i,n}$ ($s_{i,j}$ $\in$ $\{\text{`x' (ascii: 120)}$, $\text{`o' (ascii: 111)}$, $\text{`.' (ascii: 46)}\}$), where $s_{i,j} = \text{`x'}$ indicates that the intersection on the $i$-th row and the $j$-th column contains a black stone. Similarly $s_{i, j} = \text{`o'}$ for a white stone and $s_{i,j} = \text{`.'}$ for an empty intersection.

It's guaranteed that the sum of $n$ over all test cases does not exceed $5 \times 10^3$.
## 输出格式

For each test case output an integer $E$ modulo $(10^9 + 7)$ which is the answer encoded as follows:
- Sort all the stones with their row number (from top to bottom) as the primary sort key and their column number (from left to right) as the secondary sort key;
- $E=\sum \limits_{i=1}^m (10^6 + 7)^{m-i}a_i$, where $m$ is the number of stones and $a_i$ is the number of white stones not alive after flipping the color of the $i$-th stone.

$\underline{\text{NOTE that the MODULUS and the BASE are} \textbf{ DIFFERENT}}$. (We're begging you to notice this sentence. If this is not a pdf file I would rather it flashes and twinkles like crazy.)

## 样例

### 样例输入 #1
```
3
2
.o
..
3
.x.
xoo
ox.
2
oo
oo
```
### 样例输出 #1
```
0
870527216
485539347
```
## 提示

For the second sample test case, after flipping the stones in the order of $(1,2)$, $(2,1)$, $(2,2)$, $(2,3)$, $(3,1)$, $(3,2)$, the number of dead white stones are $1$, $0$, $1$, $2$, $0$, $0$, repectively.

For the third sample test case all stones on the chessboard, black or white, are not alive.
## 题目翻译

### 题目描述

**围棋**是一种对抗性游戏，目的是用自己的石头比对手的石头包围更大的棋盘总面积。游戏的核心理念是**自由**，即一个开放点，或者更确切地说，是棋盘上垂直线和水平线的交叉点，上面没有石头，与群体接壤。

一个白色或黑色的石头，如果它至少有一个直接正交相邻的自由（上、下、左或右），或者必须与一块有生命的相同颜色的石头在同一个连接组中，那么它是有生命的，被称为**活着**。我们说，如果两块颜色相同的石头正交相邻，它们就直接相连。如果存在一系列石头 $s_1,s_2,…,s_k$ ，对于所有 $1\leq i<k$ ， $s_{i-1}$ 和 $s_i$ 颜色相同且正交相邻，则相同颜色的两块石头 $s_1$ 和 $s_k$ 属于同一连通组。

例如，在下图的左侧，两块白色的石头都没有活着，因为它们被周围的黑色石头捕获了；而在右边的部分，最右边的白色石头也没有生命，即使最左边的黑色石头也没有。

![Go](https://cdn.luogu.com.cn/upload/image_hosting/zjm3icu0.png)

给定一个有 $n$ 条垂直线和 $n$ 条水平线的棋盘，其中可能有一些石头躺在上面，请计算黑色石头捕获的白色石头的数量（也就是说，计算没有生命的白色石头数量）。上述例子的结果分别为 $2$ 和 $1$ 。

然而，我们亲爱的朋友 Kotori 认为这个问题让我们聪明的参赛者解决太简单了，所以她想让你独立翻转每块石头的颜色（也就是说，把黑色的石头变成白色的石头，反之亦然$^1$），并在每次翻转后找到相应的答案。

独立翻转的意思是，在翻转石头的颜色之前，其他石头应该变回原来的颜色。还要注意，这个问题中的数据不是来自真实世界，这意味着棋盘的大小不一定是 $19×19$ ，黑白石头的数量可以是任意整数。

$^1$反之亦然：在这里，它可以用 ```把白色的石头变成黑色的石头``` 来代替。这是现代英语中非常常见的短语，尤其是在学术写作中，所以请记住。

### 输入格式

有多个测试样例。输入的第一行包含一个整数 $T$ 表示测试样例的数量。对于每个测试样例：

第一行包含一个整数 $n$ ($2\leq n\leq 10^3$)，表示棋盘的边长。

对于接下来 $n$ 行，第 $i$ 行包含一个字符串 $s_{i,1},s_{i,2},…,s_{i,n}$ 。其中 $s_{i,j}=‘x’$ 表示第 $i$ 行第 $j$ 列有一个黑石头，$s_{i,j}=‘o’$ 表示第 $i$ 行第 $j$ 列有一个白石头，$s_{i,j}=‘.’$ 表示第 $i$ 行第 $j$ 列是空的。

保证所有测试样例的 $n$ 之和不超过 $5×10^3$ 。

### 输出格式

对于每个测试用例输出一个整数 $E\bmod10^9+7$ 作为如下编码的答案：

- 对所有石头进行排序，以其行号（从上到下）为第一关键字，以其列号（从左到右）为第二关键字；
- $E=\sum\limits_{i=1}^m(10^6+7)^{m-i}a_i$ ，其中 $m$ 是石头的数量， $a_i$ 是翻转第 $i$ 次颜色后没有生命的白色石头的数量。

$\underline{\textbf{注意}\text{：\textsf{模数}和\textsf{基数}是}\textbf{不同}{的}}$ 。（我们恳求你注意这句话。如果这不是 pdf 文件，我宁愿它像疯了一样闪烁。）

### 说明/提示

对于第二个测试样例，按照 $(1,2),(2,1),(2,2),(2,3),(3,1),(3,2)$ 的顺序翻转石头后，死亡的白色石头数量分别为 $1,0,1,2,0,0$ 。

对于第三个测试样例，棋盘上的所有石头，无论是黑色还是白色，都不是活着的。


---

---
title: "[THUPC 2024 初赛] 机器人"
layout: "post"
diff: 省选/NOI-
pid: P9966
tag: ['模拟', '2024', 'THUPC']
---
# [THUPC 2024 初赛] 机器人
## 题目描述

有 $n$ 个机器人围成一圈，编号按照逆时针顺序分别为 $0\sim n-1$。

每个机器人有两只手。编号为 $i$ 的机器人初始「左手」指向编号 $l_i$ 的机器人，「右手」指向编号 $r_i$ 的机器人。

所有的机器人内部都写有 $m$ 行「指令」，「指令」有以下这些形式：

### 指令

「指令」分为「基础指令」和「高级指令」两种。「高级指令」的功能会更复杂一些，但它们本质上没有多大区别。下面介绍这些「指令」的格式以及它们被「执行」时的效果。文中的“自己”一词均指拥有这条「指令」的机器人。

#### 基础指令

- `SLACKOFF`：**「摸鱼」**，即什么也不做。
- `MOVE h z`：将第 $h$ 只手向逆时针方向 **「移动」** $z$ 个机器人的位置。当 $h=0$ 时表示「左手」，当 $h=1$ 时表示「右手」，下同。
- `SWAP h x y`：将第 $h$ 只手指向的机器人的第 $x$ 行「指令」与自己的第 $y$ 行「指令」 **「对调」**。
- `MIRROR h x`：将第 $h$ 只手指向的机器人的第 $x$ 行「指令」**「镜像」** 取反，即将「指令」中的 $h$ 取反（$0$ 变成 $1$，$1$ 变成 $0$）。特殊地，它对 `SLACKOFF` 指令没有效果；而对 `TRIGGER` 指令，会直接修改「触发」时「执行」的「指令」中的 $h$。
- `REPLACE h x <COMMAND>`：将第 $h$ 只手指向的机器人的第 $x$ 行「指令」**「替换」** 为 `<COMMAND>`。其中 `<COMMAND>` 为一条完整的「指令」。

#### 高级指令 

- `ACTIVATE h`：**「激活」** 第 $h$ 只手指向的机器人，即按顺序「执行」那个机器人的所有「指令」。前一行「指令」「执行」完毕之后才会「执行」后一行。注意在「执行」前面的「指令」时后面的「指令」可能会发生更改，这时需要「执行」更改后的「指令」。当那个机器人的所有「指令」「执行」完毕后，该「指令」才算「执行」完毕。

- `TRIGGER <COMMANDNAME>: <COMMAND>`：其中 `<COMMANDNAME>` 表示「指令」的名称，即一条「指令」中的第一个全大写单词；`<COMMAND>` 表示一条完整的「基础指令」。`TRIGGER` 指令不会被「执行」，即按顺序「执行」时会跳过该「指令」。但是，当一个 **其他** 机器人「执行」完一条「指令」之后，且「右手」指向自己的时候，自己最靠前的满足如下条件的 `TRIGGER` 指令（如果有）就会被 **「触发」**——「执行」一次对应的 `<COMMAND>`：

  - `<COMMANDNAME>` 不为 `TRIGGER` 时，刚刚「执行」完毕的「指令」为 `<COMMANDNAME>` 指令；
  - `<COMMANDNAME>` 为 `TRIGGER` 时，刚刚「执行」完毕的「指令」是 `TRIGGER` 指令被「触发」时「执行」的「指令」。

  「执行」完毕后会回到原来的「执行」顺序中。

你需要从 $0$ 号机器人开始按照编号顺序一圈又一圈地「激活」这些机器人，并输出「执行」的前 $k$ 条指令的有关信息。
## 输入格式

第一行三个正整数 $n,m,k$。

接下来按照编号从小到大的顺序表示 $n$ 个机器人的信息。

对于每个机器人，第一行两个非负整数 $l_i,r_i$ 表示「左手」指向的机器人编号和「右手」指向的机器人编号。

接下来 $m$ 行，按顺序表示机器人的「指令」，「指令」的格式见题目描述。
## 输出格式

输出 $k$ 行，按顺序描述前 $k$ 条开始「执行」的指令的相关信息，在开始「执行」前输出，每条一行，格式如下：

- 「摸鱼」时输出 `Robot <id> slacks off.`。其中 `<id>` 为一个整数，表示「执行」当前「指令」的机器人编号，下同。
- 「移动」时输出 `Robot <id> moves its <side> hand towards Robot <id2>.`。其中 `<side>` 为 `left` 或 `right`，表示移动了哪只手（`left` 表示「左手」，`right` 表示「右手」）；`<id2>` 为一个整数，表示移动之后这只手指向的机器人的编号。
- 「对调」时输出 `Robot <id> swaps a line of command with Robot <id2>.`。其中 `<id2>` 为一个整数，表示与之「对调」「指令」的机器人编号。
- 「镜像」取反时输出 `Robot <id> modifies a line of command of Robot <id2>.`。其中 `<id2>` 为一个整数，表示被「镜像」取反「指令」的机器人编号。
- 「替换」时输出 `Robot <id> replaces a line of command of Robot <id2>.`。其中 `<id2>` 为一个整数，表示被「替换」「指令」的机器人编号。
- 「执行」 `ACTIVATE` 指令「激活」（区别于你的一圈又一圈的「激活」）时输出 `Robot <id> activates Robot <id2>.`。其中  `<id2>` 为一个整数，表示被「激活」的机器人编号。
- `TRIGGER` 指令由于不会被「执行」就不需要输出，但当它们被「触发」时，仍然需要按照上面的格式输出对应的「基础指令」被「执行」的信息。
## 样例

### 样例输入 #1
```
2 2 5
0 0
MOVE 1 1
MOVE 0 1
0 1
TRIGGER MOVE: MOVE 0 1
SLACKOFF

```
### 样例输出 #1
```
Robot 0 moves its right hand towards Robot 1.
Robot 1 moves its left hand towards Robot 1.
Robot 0 moves its left hand towards Robot 1.
Robot 1 moves its left hand towards Robot 0.
Robot 1 slacks off.

```
### 样例输入 #2
```
2 2 4
0 1
ACTIVATE 1
SLACKOFF
0 1
SWAP 0 2 2
MIRROR 0 1

```
### 样例输出 #2
```
Robot 0 activates Robot 1.
Robot 1 swaps a line of command with Robot 0.
Robot 1 slacks off.
Robot 0 modifies a line of command of Robot 0.

```
### 样例输入 #3
```
3 2 6
1 2
ACTIVATE 0
ACTIVATE 0
2 1
SWAP 0 2 2
TRIGGER ACTIVATE: REPLACE 0 2 SLACKOFF
0 1
TRIGGER MIRROR: SLACKOFF
SLACKOFF

```
### 样例输出 #3
```
Robot 0 activates Robot 1.
Robot 1 swaps a line of command with Robot 2.
Robot 1 slacks off.
Robot 2 replaces a line of command of Robot 0.
Robot 0 slacks off.
Robot 1 swaps a line of command with Robot 2.

```
### 样例输入 #4
```
3 2 8
0 1
SLACKOFF
TRIGGER MOVE: SLACKOFF
1 2
TRIGGER TRIGGER: SLACKOFF
TRIGGER SLACKOFF: MOVE 0 1
2 0
TRIGGER SLACKOFF: MOVE 1 2
TRIGGER TRIGGER: MOVE 1 1

```
### 样例输出 #4
```
Robot 0 slacks off.
Robot 1 moves its left hand towards Robot 2.
Robot 2 moves its right hand towards Robot 1.
Robot 1 slacks off.
Robot 2 moves its right hand towards Robot 0.
Robot 0 slacks off.
Robot 1 slacks off.
Robot 2 moves its right hand towards Robot 2.

```
### 样例输入 #5
```
见附加文件的 5.in。
```
### 样例输出 #5
```
见附加文件的 5.ans。
```
## 提示

### 样例 \#1 解释

`TRIGGER` 指令的「触发」时机是「执行」完毕之后。注意不能「触发」自己的 `TRIGGER` 指令。

### 样例 \#2 解释

注意在「执行」前面的「指令」时后面的「指令」可能会发生更改，这时需要「执行」更改后的「指令」。

### 样例 \#3 解释

`ACTIVATE` 指令「激活」另一个机器人时，当那个机器人的所有「指令」「执行」完毕后，该「指令」才算「执行」完毕。

### 样例 \#4 解释

只有自己最靠前的满足条件的 `TRIGGER` 指令才会被 **「触发」**。

### 样例 \#5 解释

无私的馈赠？有力的援助？

### 子任务

保证所有的指令的格式均正确。

保证输入文件的长度不超过 $5\mathtt{MB}$。

保证能够「执行」至少 $k$ 条「指令」。

保证 $2\le n\le 100$，$1\le m \le 10$，$1\le k \le 3\times 10^5$。

保证 $0\le l_i,r_i<n$。

保证 $0\le h \le 1$，$1\le x,y \le m$，$1\le z<n$。所有输入的数都是整数。

### 题目使用协议

来自 THUPC2024（2024年清华大学学生程序设计竞赛暨高校邀请赛）初赛。

以下『本仓库』皆指 THUPC2024 初赛 官方仓库（[https://github.com/ckw20/thupc2024_pre_public](https://github.com/ckw20/thupc2024_pre_public)）

1. 任何单位或个人都可以免费使用或转载本仓库的题目；

2. 任何单位或个人在使用本仓库题目时，应做到无偿、公开，严禁使用这些题目盈利或给这些题目添加特殊权限；

3. 如果条件允许，请在使用本仓库题目时同时提供数据、标程、题解等资源的获取方法；否则，请附上本仓库的 github 地址。



---

