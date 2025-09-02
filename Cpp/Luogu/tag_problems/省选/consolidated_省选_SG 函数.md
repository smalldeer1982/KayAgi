---
title: "[GCJ 2019 #1C] Bacterial Tactics"
layout: "post"
diff: 省选/NOI-
pid: P13114
tag: ['博弈论', '2019', 'SG 函数', 'Google Code Jam']
---
# [GCJ 2019 #1C] Bacterial Tactics
## 题目描述

Becca and Terry are microbiologists who have a friendly rivalry. When they need a break from their research, they like to play a game together. The game is played on a matrix of unit cells with $\mathbf{R}$ rows and $\mathbf{C}$ columns. Initially, each cell is either empty, or contains radioactive material.

On each player's turn, if there are no empty cells in the matrix, that player loses the game. Otherwise, they choose an empty cell and place a colony of bacteria there. Bacteria colonies come in two types: H (for "horizontal") and V (for "vertical").

* When a type H colony is placed into an empty cell, it occupies that cell (making it non-empty), and also tries to spread into the cell immediately to the west (if there is one) and the cell immediately to the east (if there is one).
* When a type V colony is placed into an empty cell, it occupies that cell (making it non-empty), and also tries to spread into the cell immediately to the south (if there is one) and the cell immediately to the north (if there is one).

Whenever a colony (of either type) tries to spread into a cell:

* If the cell contains radioactive material, the colony mutates and the player who placed the colony loses the game.
* If that cell is empty, the colony occupies that cell (making it non-empty), and then the rule above is triggered again (i.e. the colony will try to spread further).
* If the cell already contains bacteria (of any type), the colony does not spread into that cell.

Notice that it may be possible that all of a player's available moves would cause them to lose the game, and so they are doomed. See the sample case explanations below for examples of how the game works.

Becca makes the first move, and then the two players alternate moves until one of them loses the game. If both players play optimally, who will win? And, if Becca will win, how many distinct winning opening moves does she have? (Two opening moves are distinct if and only if they either use different cells, or different kinds of colony, or both.)

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each case begins with one line containing two integers $\mathbf{R}$ and $\mathbf{C}$: the number of rows and columns, respectively, in the matrix. Then, there are $\mathbf{R}$ more rows of $\mathbf{C}$ characters each. The j-th character on the i-th of these lines represents the j-th column of the i-th row of the matrix. Each character is either . (an empty cell) or # (a cell with radioactive material).

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1), and $y$ is an integer: either 0 if Becca will not win, or, if Becca will win, the number of distinct winning opening moves she can make, as described above.
## 样例

### 样例输入 #1
```
5
2 2
..
.#
4 4
.#..
..#.
#...
...#
3 4
#.##
....
#.##
1 1
.
1 2
##
```
### 样例输出 #1
```
Case #1: 0
Case #2: 0
Case #3: 7
Case #4: 2
Case #5: 0
```
## 提示

**Sample Explanation**

In Sample Case #1, Becca cannot place an H colony in the southwest empty cell or a V colony in the northeast empty cell, because those would spread onto a radioactive cell and Becca would lose. She has only two possible strategies that do not cause her to lose immediately:

1. Place an H colony in the northwest or northeast empty cells. The colony will also spread to the other of those two cells.
2. Place a V colony in the northwest or southwest empty cell. The colony will also spread to the other of those two cells.

If Becca chooses strategy 1, Terry can place a V colony in the southwest empty cell. If Becca chooses strategy 2, Terry can place an H colony in the northeast empty cell. Either way, Becca has no empty cells to choose from on her next turn, so she loses and Terry wins.

In Sample Case #2, any of Becca's opening moves would cause a mutation.

In Sample Case #3, five of Becca's possible opening moves would cause a mutation, but the other seven are winning. She can place an H colony in any of the cells of the second row, or she can place a V colony in any of the cells of the second column. In either case, she leaves two disconnected sets of 1 or 2 cells each. In each of those sets, only one type of colony can be played, and playing it consumes all of the empty cells in that set. So, whichever of those sets Terry chooses to consume, Becca can consume the other, leaving Terry with no moves.

In Sample Case #4, both of Becca's two distinct possible opening moves are winning.

In Sample Case #5, Becca has no possible opening moves.

**Limits**

$1 \leq \mathbf{T} \leq 100$.

**Test set 1 (Visible)**

- $1 \leq \mathbf{R} \leq 4$.
- $1 \leq \mathbf{C} \leq 4$.

**Test set 2 (Hidden)**

- $1 \leq \mathbf{R} \leq 15$.
- $1 \leq \mathbf{C} \leq 15$.


---

---
title: "[ZJOI2009] 染色游戏"
layout: "post"
diff: 省选/NOI-
pid: P2594
tag: ['递推', '博弈论', '2009', '各省省选', '浙江', '素数判断,质数,筛法', 'SG 函数']
---
# [ZJOI2009] 染色游戏
## 题目描述

一共n × m 个硬币，摆成n × m 的长方形。dongdong 和xixi 玩一个游戏， 每次可以选择一个连通块，并把其中的硬币全部翻转，但是需要满足存在一个 硬币属于这个连通块并且所有其他硬币都在它的左上方(可以正左方也可以正 上方)，并且这个硬币是从反面向上翻成正面向上。dongdong 和xixi 轮流操作。 如果某一方无法操作，那么他(她) 就输了。dongdong 先进行第一步操作，假 设双方都采用最优策略。问dongdong 是否有必胜策略。

## 输入格式

第一行一个数T，表示他们一共玩T 局游戏。接下来是T 组游戏描述。每 组游戏第一行两个数n;m，接下来n 行每行m 个字符，第i 行第j 个字符如 果是“H” 表示第i 行第j 列的硬币是正面向上，否则是反面向上。第i 行j 列 的左上方是指行不超过i 并且列不超过j 的区域。

## 输出格式

对于每局游戏，输出一行。如果dongdong 存在必胜策略则输出“-\_-”(不含 引号) 否则输出“=\_=”(不含引号)。(注意输出的都是半角符号，即三个符号 ASCII 码分别为45,61,95)

## 样例

### 样例输入 #1
```
3
2 3
HHH
HHH
2 3
HHH
TTH
2 1
T
H
```
### 样例输出 #1
```
=_=
-_-
-_-
```
## 提示

对于40% 的数据，满足1 ≤ n;m ≤ 5。

对于100% 的数据，满足1 ≤ n;m ≤ 100，1 ≤ T ≤ 50。



---

---
title: "「Stoi2031」蒲公英的约定（vol.1）"
layout: "post"
diff: 省选/NOI-
pid: P7490
tag: ['数学', '博弈论', '期望', 'SG 函数']
---
# 「Stoi2031」蒲公英的约定（vol.1）
## 题目背景

> 一起长大的约定 那样清晰 拉过勾的我相信 说好要一起旅行 是你如今 唯一坚持的任性 ——《蒲公英的约定》
## 题目描述

清和如在玩游戏。她们有 $n$ 丛 **蒲公英**，每丛分别有 $s_i$ 朵。这些 **蒲公英** 有一个神奇的性质：有一个给定的常数 $\sigma \in (0,1)$，$x$ 朵 **蒲公英** 会分出 $\lfloor \sigma x \rfloor$ 朵为一组，剩下 $x-\lfloor \sigma x \rfloor$ 朵继续分组，直到分出的组没有 **蒲公英** 即 $\lfloor \sigma x \rfloor=0$ 为止。她们称这种现象为 **任性**。现在她们的每丛 **蒲公英** 都有 **任性** 的现象。她们的游戏规则如下：从清开始，两人轮流进行 **旅行**。一次 **旅行** 为选择一丛 **蒲公英** 并吹散这一丛的第一组中的若干朵 **蒲公英**，至少要吹一朵，至多吹的朵数为第一组的朵数，即不能吹散除第一组外的 **蒲公英**。当第一组为空时，其下一组成为第一组。若这一丛只剩下一组 **蒲公英**，这一丛不能再被选定。每丛 **蒲公英** 都不能被选定时，游戏结束，当前轮到的人落败。她们想知道如果清第一次 **旅行** 时等概率选择其中一丛可吹散的 **蒲公英** 再等概率选择吹散的朵数后两人都按最优策略操作，那么清的胜率 $x \bmod 20190816170251$ 的值将会是多少。

与 vol.2 的区别是，**蒲公英** 在被吹散一部分后 **不会** 重新分组。
## 输入格式

第一行两个正整数 $id,n$，其中 $id$ 表示 Subtask 编号。

第二行 $n$ 个正整数，第 $i$ 个表示 $s_i$。

若 $id>3$，第三行输入两个正整数 $p,q$ 表示 $\sigma=\dfrac{p}{q}$。
## 输出格式

一行一个整数，表示清的胜率 $x \bmod{20190816170251}$。
## 样例

### 样例输入 #1
```
4 3
1 1 1
1 6

```
### 样例输出 #1
```
0

```
### 样例输入 #2
```
6 3
1 7 3
1 3

```
### 样例输出 #2
```
5047704042563

```
## 提示

#### 简述版题意：

有 $n$ 丛 **蒲公英**，第 $i$ 丛有 $s_i$ 朵。给定实数 $\sigma$，每丛会分为若干组，第 $j$ 组有 $t_j$ 朵，且满足 $t_j=\left\lfloor \sigma\left(s_i - \sum\limits_{k=1}^{j-1}t_k\right) \right\rfloor$，当 $t_j=0$ 时不再分组。两人轮流操作，每次操作可以选择一丛 **蒲公英**，并选择一个整数 $c \in t_j$，从这丛 **蒲公英** 中吹散 $c$ 朵，将 $t_j$ 变为 $t_j-c$，其中 $j$ 为操作之前这丛 **蒲公英** 中满足 $t_j \neq 0$ 的最小正整数。必须至少吹一朵，不能操作者败。求先手第一步等概率选择任意一丛可操作的 **蒲公英** 再等概率选择吹散的朵数后两人都采取最优策略时先手的胜率 $x \bmod{20190816170251}$ 的值。

#### 样例解释：

对于样例 $1$，清无法操作，胜率为 $0$。

对于样例 $2$，初始局面为 $\{0;1\},\{2,1,1,1,0;2\},\{1,0;2\}$，清可以选择第 $2$ 丛并在两种操作中选择吹散 $2$ 朵变成 $\{0;1\},\{1,1,1,0;2\},\{1,0;2\}$，选择第 $3$ 丛没有可取胜的策略，且第 $1$ 丛不能选择，总胜率为 $\dfrac{\frac{1}{2}+0}{2}=\dfrac{1}{4}$。

#### 数据范围：

**本题采用捆绑测试，各个 Subtask 的分数与限制如下。**

| Subtask No. | $n \le$ | $s_i \le$ | $\sigma$ 限制 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{2}+1}{3}$ | $10$ |
| $2$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{3}+1}{5}$ | $10$ |
| $3$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{5}-1}{2}$ | $10$ |
| $4$ | $100$ | $1$ | 无 | $3$ |
| $5$ | $100$ | $100$ | $\sigma=\dfrac{1}{2}$ | $7$ |
| $6$ | $100$ | $10^6$ | 无 | $13$ |
| $7$ | $3 \times 10^5$ | $10^{10}$ | $\sigma \ge \dfrac{1}{2}$ | $47$ |

对于 $100\%$ 的数据，$1 \le n \le 3 \times 10^5,1 \le s_i \le 10^{10},1 \le p<q \le 10^9$。

**本题读入量较大，可以选择使用比赛描述中的快速读入模板以加快读入速度。**


---

---
title: "「Stoi2031」蒲公英的约定（vol.2）"
layout: "post"
diff: 省选/NOI-
pid: P7491
tag: ['数学', '博弈论', '期望', 'SG 函数']
---
# 「Stoi2031」蒲公英的约定（vol.2）
## 题目背景

> 一起长大的约定 那样清晰 拉过勾的我相信 说好要一起旅行 是你如今 唯一坚持的任性 ——《蒲公英的约定》
## 题目描述

清和如在玩游戏。她们有 $n$ 丛 **蒲公英**，每丛分别有 $s_i$ 朵。这些 **蒲公英** 有一个神奇的性质：有一个给定的常数 $\sigma \in (0,1)$，$x$ 朵 **蒲公英** 会分出 $\lfloor \sigma x \rfloor$ 朵为一组，剩下 $x-\lfloor \sigma x \rfloor$ 朵继续分组，直到分出的组没有 **蒲公英** 即 $\lfloor \sigma x \rfloor=0$ 为止。她们称这种现象为 **任性**。现在她们的每丛 **蒲公英** 都有 **任性** 的现象。她们的游戏规则如下：从清开始，两人轮流进行 **旅行**。一次 **旅行** 为选择一丛 **蒲公英** 并吹散这一丛的第一组中的若干朵 **蒲公英**，至少要吹一朵，至多吹的朵数为第一组的朵数，即不能吹散除第一组外的 **蒲公英**。当第一组为空时，其下一组成为第一组。若这一丛只剩下一组 **蒲公英**，这一丛不能再被选定。每丛 **蒲公英** 都不能被选定时，游戏结束，当前轮到的人落败。她们想知道如果清第一次 **旅行** 时等概率选择其中一丛可吹散的 **蒲公英** 再等概率选择吹散的朵数后两人都按最优策略操作，那么清的胜率 $x \bmod{20190816170251}$ 的值将会是多少。

与 vol.1 的区别是，**蒲公英** 在被吹散一部分后 **会** 重新分组。
## 输入格式

第一行两个正整数 $id,n$，其中 $id$ 表示 Subtask 编号。

第二行 $n$ 个正整数，第 $i$ 个表示 $s_i$。

若 $id>3$，第三行输入两个正整数 $p,q$ 表示 $\sigma=\dfrac{p}{q}$。
## 输出格式

一行一个整数，表示清的胜率 $x \bmod{20190816170251}$。
## 样例

### 样例输入 #1
```
4 3
1 1 1
1 6

```
### 样例输出 #1
```
0

```
### 样例输入 #2
```
6 3
1 7 3
1 3

```
### 样例输出 #2
```
15143112127689

```
## 提示

#### 简述版题意：

有 $n$ 丛 **蒲公英**，第 $i$ 丛有 $s_i$ 朵。给定实数 $\sigma$，两人轮流操作，每次操作可以选择一丛 **蒲公英**，并选择一个整数 $c \in (0,\sigma s]$，从这丛 **蒲公英** 中吹散 $c$ 朵，其中 $s$ 为操作之前这丛 **蒲公英** 的朵数。必须至少吹一朵，不能操作者败。求先手第一步等概率选择任意一丛可操作的 **蒲公英** 再等概率选择吹散的朵数后两人都采取最优策略时先手的胜率 $x \bmod{20190816170251}$ 的值。

#### 样例解释：

对于样例 $1$，清无法操作，胜率为 $0$。

对于样例 $2$，清可以选择第 $2$ 丛并在两种操作中选择吹散 $2$ 朵变成 $1,5,3$，或选择第 $3$ 丛并选择唯一的操作变成 $1,7,2$，且第 $1$ 丛不能选择，总胜率为 $\dfrac{\frac{1}{2}+1}{2}=\dfrac{3}{4}$。

#### 数据范围：

**本题采用捆绑测试，各个 Subtask 的分数与限制如下。**

| Subtask No. | $n \le$ | $s_i \le$ | $\sigma$ 限制 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{2}+1}{3}$ | $10$ |
| $2$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{3}+1}{5}$ | $10$ |
| $3$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{5}-1}{2}$ | $10$ |
| $4$ | $100$ | $1$ | 无 | $3$ |
| $5$ | $100$ | $100$ | $\sigma=\dfrac{1}{2}$ | $7$ |
| $6$ | $100$ | $10^6$ | 无 | $13$ |
| $7$ | $3 \times 10^5$ | $10^{10}$ | $\sigma \ge \dfrac{1}{2}$ | $47$ |

对于 $100\%$ 的数据，$1 \le n \le 3 \times 10^5,1 \le s_i \le 10^{10},1 \le p<q \le 10^9$。

**本题读入量较大，可以选择使用比赛描述中的快速读入模板以加快读入速度。**


---

---
title: "[北大集训 2021] 经典游戏"
layout: "post"
diff: 省选/NOI-
pid: P8994
tag: ['树状数组', '2021', 'O2优化', '分治', '树链剖分', '字典树 Trie', 'SG 函数']
---
# [北大集训 2021] 经典游戏
## 题目背景

CTT2021 D4T2
## 题目描述

某天，`C` 和 `K` 觉得很无聊，于是决定玩一个经典小游戏：

在一棵有 $n$ 个结点的有根树上，标号为 $i$ 的节点上有 $a_i$ 个棋子。游戏时玩家轮流操作，每次可以将任意一个节点 $u$ 上的一个棋子放置到任意一个点 $v \in U(u)$上，其中 $U(u)=subtree\{u\}\setminus\{u\}$ ，表示 $u$ 的子树内（不包含 $u$ 本身）的点组成的集合。不能进行操作者失败。

而 `C` 和 `K` 作为 `P**` 和 `T**` 的在读学生，这种一眼就能找出必胜策略的游戏实在是索然无味，于是两人觉得，每个人给自己一个特殊能力可能会比较有趣：

`C` 在开始游戏之前，**可以选择**将当前树的树根 $R$ 换到与 $R$ 相邻的任意一个点 $R^{\prime}$ 上。定义两个点相邻当且仅当这两个点有边直接相连。

`K` 在开始游戏之前，**必须选择**树上的一个节点，在上面加上一颗棋子。

`C` 和 `K` 决定玩 $m$ 局游戏。每局游戏的流程如下：

1. 游戏开始前，`C` 和 `K` 会商量好，先在标号为 $x$ 的节点上放上一个棋子，然后将树根设为 $y$。
2. 之后 `C` 可以选择是否发动特殊能力，`C` 决策完之后 `K` 可以选择是否发动特殊能力。
3. 特殊能力的决策结束后，会在这棵树上进行一局 `C` 先手、`K` 后手的游戏。游戏完成后会将树上棋子的状态**还原到流程 `1` 结束后的状态**。

`C` 觉得这个游戏可以出成一个简单题，于是他决定考考你：`C` 在每局游戏的第二步的时候，有多少种决策方式使得不管 `K` 如何进行特殊能力的操作，开始游戏时都存在**必胜策略**？两种决策方式不同，**当且仅当**两种决策**更换的树根** $R^{\prime}$ **不同**，或者**两者中仅有一个没有发动特殊能力**。

## 输入格式

第一行包括一个整数，表示该测试点所在的子任务的分数。你可以使用这个信息判断该测试点满足的特殊性质。特别的，下发样例中此行使用 $0$ 代替。

第二行包含两个用空格隔开的正整数 $n, m$，表示树的节点数目以及游戏的轮数。树上的节点从 $1$ 到 $n$ 编号。

接下来 $n-1$ 行，每行包含两个用空格隔开的正整数 $u_i,v_i$，满足 $1 \le u_i,v_i \le n$，表示编号为 $u_i$ 和 $v_i$ 的节点之间有边直接相连。

接下来一行包含 $n$ 个用空格隔开的整数 $a_1,a_2,\ldots,a_n$，满足 $0 \leq a_1,a_2,\ldots,a_n \leq 10^9$。

接下来 $m$ 行，每行包含两个用空格隔开的正整数 $x, y$ 描述一局游戏，满足 $1 \le x,y \le n$。

## 输出格式


你需要输出 $m$ 行，其中第 $i$ 行应当包含一个非负整数 $x$ 表示第 $i$ 局游戏中，`C` 存在多少种使用特殊能力的决策方案，使得 `C` 在这局游戏中存在必胜策略。注意，**不使用特殊能力**也是一种**可能可行**的决策方案。

## 样例

### 样例输入 #1
```
0
5 2
1 2
1 3
2 4
2 5
1 0 1 0 1
2 2
4 4
```
### 样例输出 #1
```
2
1

```
### 样例输入 #2
```
0
10 10
6 3
7 4
8 2
2 1
9 1
1 3
3 4
4 5
5 10
0 0 1 1 1 0 1 1 0 0 
8 3
2 3
7 10
7 3
6 7
8 5
9 8
2 10
5 4
3 9

```
### 样例输出 #2
```
1
1
0
1
1
1
0
0
2
1

```
## 提示

| 子任务分数 | $1\le n,m\le$ | $\max\{a_1,a_2,\dots,a_n\}\le$ |              特殊性质              |
| :--------: | :-----------: | :----------------------------: | :--------------------------------: |
|    $16$    |      $5$      |              $1$               |                 无                 |
|    $15$    |     $300$     |              $1$               |                 无                 |
|    $14$    |    $5000$     |             $10^9$             |                 无                 |
|    $13$    |   $100000$    |             $10^9$             |        保证给出的树是一条链        |
|    $12$    |   $100000$    |             $10^9$             | 保证给出的树存在一个点度数为 $n-1$ |
|    $11$    |   $100000$    |             $10^9$             |   保证 $m$ 次游戏初始给定根一致    |
|    $10$    |   $500000$    |             $10^9$             |                 无                 |
|    $9$     |   $1000000$   |             $10^9$             |                 无                 |





---

