---
title: "[集训队互测 2023] 虹"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10016
tag: ['集训队互测', '2023', '数论', '深度优先搜索 DFS', '最近公共祖先 LCA', '分块', '位运算']
---
# [集训队互测 2023] 虹
## 题目描述

给定一棵 $n$ 个点的树。

- 称点集 $S$ **连通**，当且仅当 $\forall u,v \in S$，所有 $u$ 到 $v$ 的简单路径上的点均在 $S$ 中。
- 称点集 $S$ 是 $[l,r]$ 的**虹**，当且仅当 $S$ **连通**，且 $S$ 包含 $[l,r]$ 中的所有点。
- 称点集 $S_0$ 是 $[l,r]$ 的**最小虹**，当且仅当 $S_0$ 是 $[l,r]$ 的所有**虹**中大小最小的。可以证明，$S_0$ 是唯一的。

点带权，点 $u$ 的权值为 $w_u$，初始所有点权均为 $0$。同时，给定序列 $\{z_1,z_2,\cdots,z_n\}$。

给定 $q$ 次命令，每次命令形如以下两类之一：

- `1 l r`：令 $S_0$ 为 $[l,r]$ 的**最小虹**，$\forall u \in S_0$，将 $w_u$ 加 $1$。
- `2 l r u`：求 $\left(\sum_{i=l}^r 19901991^{z_{\gcd(i,u)} w_i} \right) \bmod {20242024}$ 的值。
## 输入格式

第一行两个正整数 $n,q$。

第二行 $n$ 个非负整数，依次表示 $z_1,z_2,\cdots,z_n$。

接下来 $n-1$ 行，每行两个正整数 $u,v$，描述一条树上从 $u$ 到 $v$ 的边。

最后 $q$ 行，每行 $3$ 或 $4$ 个正整数，描述一次命令。

**注意：本题输入文件行末有 `\r`，请选手自行过滤。**
## 输出格式

对于每次询问（即第二类命令）输出答案。
## 样例

### 样例输入 #1
```
5 4
1 0 0 0 1
1 2
1 3
3 4
3 5
1 2 3
2 1 3 3
1 4 5
2 3 5 3
```
### 样例输出 #1
```
19561959
19561959
```
## 提示

**本题采用捆绑测试**。

对于所有测试数据保证：$1 \le n, q \le 8 \times 10^4,0 \le z_i \le 10^9$，所有命令满足 $1 \le l \le r \le n, 1 \le u \le n$，**保证第一类命令的 $(l,r)$ 随机生成**。随机生成方式如下：
- 在 $[1,n] \cap \mathrm{Z}$ 中等概率随机生成 $l$。
- 在 $[1,n] \cap \mathrm{Z}$ 中等概率随机生成 $r$。
- 若 $l>r$，则交换 $l,r$。

| 子任务编号 | 分值 | $n \le$ | $q \le$ | 特殊性质 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :----------: |
| $1$ | $10$ | $10^3$ | $10^3$ | 无 | 无 |
| $2$ | $20$ | $65536$ | $65536$ | A, B | 无 |
| $3$ | $20$ | $65536$ | $65536$ | A | 依赖于子任务 $2$ |
| $4$ | $30$ | $65536$ | $65536$ | 无 | 依赖于子任务 $1,2,3$ |
| $5$ | $20$ | $80000$ | $80000$ | 无 | 依赖于子任务 $1,2,3,4$ |

特殊性质 A：保证所有第二类命令均在所有第一类命令之后。

特殊性质 B：保证第二类命令次数 $\le 20$。


---

---
title: "[CSP-S 2024] 擂台游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11234
tag: ['贪心', '递归', '2024', 'O2优化', '深度优先搜索 DFS', '树形 DP', '差分', 'CSP-S 提高级']
---
# [CSP-S 2024] 擂台游戏
## 题目描述

小 S 想要举办一场擂台游戏，如果共有 $2^k$ 名选手参加，那么游戏分为 $k$ 轮进行：

- 第一轮编号为 $1, 2$ 的选手进行一次对局，编号为 $3, 4$ 的选手进行一次对局，以此类推，编号为 $2^k - 1, 2^k$ 的选手进行一次对局。
- 第二轮在只保留第一轮的胜者的前提下，相邻的两位依次进行一场对局。
- 以此类推，第 $k - 1$ 轮在只保留第 $k - 2$ 轮的 $4$ 位胜者的前提下，前两位、后两位分别进行对局，也就是所谓的半决赛。
- 第 $k$ 轮即为半决赛两位胜者的决赛。

确定了游戏晋级的规则后，小 S 将比赛的规则设置为了擂台赛。具体而言，每位选手都有一个能力值 $a_1, a_2, \dots , a_{2^k}$，能力值为 $[0,2^{31}-1]$ 之内的整数。对于每场比赛，会先抽签决定一个数 $0/1$，我们将第 $R$ 轮的第 $G$ 场比赛抽到的数记为 $d_{R,G}$。抽到 $0$ 则表示表示编号小的选手为擂主，抽到 $1$ 则表示编号大的选手为擂主。擂主获胜当且仅当他的能力值 $a\geq R$。也就是说，游戏的胜负只取决于**擂主的能力值**与**当前比赛是第几轮**的大小关系，**与另一位的能力值无关**。

现在，小 S 先后陆续收到了 $n$ 位选手的报名信息，他们分别告知了小 S 自己的能力值。小 S 会按照报名的先后顺序对选手进行编号为 $1, 2, \dots, n$。小 S 关心的是，补充**尽量少**的选手使总人数为 $2$ 的整次幂，且所有选手进行一次完整的擂台游戏后，所有可能成为总冠军的选手的**编号之和**是多少。

形式化地，设 $k$ 是最小的非负整数使得 $2^k\geq n$，那么应当补充 $(2^k-n)$ 名选手，且补充的选手的能力值可以任取 $[0,2^{31}-1]$ 之内的整数。**如果补充的选手有可能取胜，也应当计入答案中**。

当然小 S 觉得这个问题还是太简单了，所以他给了你 $m$ 个询问 $c_1,c_2,\dots,c_m$。小 S 希望你帮忙对于每个 $c_i$ 求出，在只收到前 $c_i$ 位选手的报名信息时，这个问题的答案是多少。
## 输入格式

**本题的测试点包含有多组测试数据。** 但不同测试数据只是通过修改 $a_1, a_2, \dots , a_n$ 得到，其他内容均保持不变，请参考以下格式。其中 $\oplus$ 代表异或运算符，$a \bmod b$ 代表 $a$ 除以 $b$ 的余数。

输入的第一行包含两个正整数 $n, m$，表示报名的选手数量和询问的数量。

输入的第二行包含 $n$ 个非负整数 $a'_1,a'_2,\dots,a'_n$，这列数将用来计算真正的能力值。

输入的第三行包含 $m$ 个正整数 $c_1, c_2, \dots , c_m$，表示询问。

设 $K$ 是使得 $2^K \geq n$ 的最小的非负整数，接下来的 $K$ 行当中，第 $R$ 行包含 $2^{K-R}$ 个数（无空格），其中第 $G$ 个数表示第 $R$ 轮的第 $G$ 场比赛抽签得到的 $d_{R,G}=0/1$。

注意，由于询问只是将人数凑齐到 $2^k\geq c_i$，这里的 $k\leq K$，因此你未必会用到全部的输入值。

接下来一行包含一个正整数 $T$，表示有 $T$ 组测试数据。

接下来共 $T$ 行，每行描述一组数据，包含 $4$ 个非负整数 $X_0,X_1,X_2,X_3$，该组数据的能力值 $a_i=a'_i \oplus X_{i\bmod 4}$，其中 $1\leq i\leq n$。
## 输出格式

共输出 $T$ 行，对于每组数据，设 $A_i$ 为第 $i$（$1 \leq i \leq m$）组询问的答案，你只需要输出一行包含一个整数，表示 $(1\times A_1) \oplus (2\times A_2) \oplus \dots \oplus (m\times A_m)$ 的结果。
## 样例

### 样例输入 #1
```
5 5
0 0 0 0 0
5 4 1 2 3
1001
10
1
4
2 1 0 0
1 2 1 0
0 2 3 1
2 2 0 1
```
### 样例输出 #1
```
5
19
7
1
```
## 提示

**【样例 1 解释】**

共有 $T = 4$ 组数据，这里只解释第一组。$5$ 名选手的真实能力值为 $[1, 0, 0, 2, 1]$。$5$ 组询问分别是对长度为 $5, 4, 1, 2, 3$ 的前缀进行的。

1. 对于长度为 $1$ 的前缀，由于只有 $1$ 号一个人，因此答案为 $1$。
2. 对于长度为 $2$ 的前缀，由于 $2$ 个人已经是 $2$ 的幂次，因此不需要进行扩充。根据抽签 $d_{1,1} = 1$ 可知 $2$ 号为擂主，由于 $a_2 < 1$，因此 $1$ 号获胜，答案为 $1$。
3. 对于长度为 $3$ 的前缀，首先 $1$ 号、$2$ 号比赛是 $1$ 号获胜（因为 $d_{1,1} = 1$，故 $2$ 号为擂主，$a_2 < 1$），然后虽然 $4$ 号能力值还不知道，但 $3$ 号、$4$ 号比赛一定是 $4$ 号获胜（因为 $d_{1,2} = 0$，故 $3$ 号为擂主，$a_3 < 1$），而决赛 $1$ 号、$4$ 号谁获胜都有可能（因为 $d_{2,1} = 1$，故 $4$ 号为擂主，如果 $a_4 < 2$ 则 $1$ 号获胜，$a_4 \geq 2$ 则 $4$ 号获胜）。综上所述，答案为 $1 + 4 = 5$。
4. 对于长度为 $4$ 的前缀，我们根据上一条的分析得知，由于 $a_4 \geq 2$ ，所以决赛获胜的是 $4$ 号。
5. 对于长度为 $5$ 的前缀，可以证明，可能获胜的选手包括 $4$ 号、$7$ 号、$8$ 号，答案为 $19$。

因此，该组测试数据的答案为 $(1 \times 19) \oplus (2 \times 4) \oplus (3 \times 1) \oplus (4 \times 1) \oplus (5 \times 5) = 5$。

**【样例 2】**

见选手目录下的 arena/arena2.in 与 arena/arena2.ans。

这组样例满足特殊性质 A。

**【样例 3】**

见选手目录下的 arena/arena3.in 与 arena/arena3.ans。

这组样例满足特殊性质 B。

**【样例 4】**

见选手目录下的 arena/arena4.in 与 arena/arena4.ans。

**【样例 5】**

见选手目录下的 arena/arena5.in 与 arena/arena5.ans。

**【数据范围】**

对于所有测试数据，保证：$2 \leq n, m \leq 10^5$，$0 \leq a_i, X_j < 2^{31}$，$1 \leq c_i \leq n$，$1 \leq T \leq 256$。

| 测试点 | $T=$ | $n,m\leq$ | 特殊性质 A | 特殊性质 B |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1\sim 3$ | $1$ | $8$ | 否 | 否 |
| $4,5$ | $1$ | $500$ | 是 | 否 |
| $6\sim 8$ | $1$ | $500$ | 否 | 是 |
| $9,10$ | $1$ | $5000$ | 否 | 否 |
| $11,12$ | $1$ | $10^5$ | 是 | 否 |
| $13\sim 15$ | $1$ | $10^5$ | 否 | 是 |
| $16,17$ | $4$ | $10^5$ | 否 | 否 |
| $18,19$ | $16$ | $10^5$ | 否 | 否 |
| $20,21$ | $64$ | $10^5$ | 否 | 否 |
| $22,23$ | $128$ | $10^5$ | 否 | 否 |
| $24,25$ | $256$ | $10^5$ | 否 | 否 |


特殊性质 A：保证询问的 $c_i$ 均为 $2$ 的幂次。

特殊性质 B：保证所有的 $d_{R,G} = 0$。


---

---
title: "【MX-X13-T7】「KDOI-12」No one can be anything without comparison."
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13012
tag: ['O2优化', '深度优先搜索 DFS', '树论', '前缀和', '分块', '梦熊比赛']
---
# 【MX-X13-T7】「KDOI-12」No one can be anything without comparison.
## 题目描述

**请注意本题对 $\bm{n,k}$ 的特殊限制。**

$n$ 名选手参加了 $k$ 场 Tetris Tournament。每一场 Tetris Tournament 包含 $n-1$ 轮，每轮会选出两个目前还未淘汰的选手 $x,y$ 并让他们参加一场比赛，输的人淘汰。最后会有唯一胜者。你现在得知第 $j$ 个人在第 $i$ 场 Tetris Tournament 中被 $a_{i,j}$ 淘汰了。$j$ 是第 $i$ 场 Tetris Tournament 的胜者当且仅当 $a_{i,j}=0$。

选手们喜欢比较。他们都希望自己在某种意义上能够胜过别人，或至少跟别人水平差不多。

定义第 $i$ 场 Tetris Tournament 中 $x$ 严格吊打 $y$ 当且仅当存在 $x=p_1,p_2,\dots,p_m=y$（$m\ge 2$，也就是说 $x\neq y$），使得对于任意 $1\leq j<m$，$a_{i,p_{j+1}}=p_j$。

定义一个有序的选手 $k$ 元组 $(i_1,i_2,\dots,i_k)$ 是水平相似的当且仅当对于 $1\leq j<k$，$i_j$ 在第 $j$ 场比赛中严格吊打 $i_{j+1}$ 且 $i_k$ 在第 $k$ 场比赛中严格吊打 $i_1$。

求水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 输入格式

第一行，两个正整数 $n,k$。**保证 $\bm{3\leq k\leq 5}$**。

接下来 $k$ 行，第 $i$ 行 $n$ 个非负整数 $a_{i,1}, \ldots, a_{i,n}$。
## 输出格式

仅一行，一个非负整数，表示水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3 3
0 1 2
3 0 2
3 1 0
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 5
0 1 1 2 3 4
3 3 0 6 6 1
2 4 1 0 1 1
3 0 2 6 6 2
5 3 6 1 0 4
```
### 样例输出 #2
```
18
```
## 提示

**【样例解释 \#1】**

符合要求的三元组 $(i_1,i_2,i_3)$ 有：$(1,2,3)$，$(2,3,1)$。

**【数据范围】**

**本题使用捆绑测试。**

| 子任务编号 | 分值 | $n\leq$ | $k=$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $7$ | $100$ | $3$ | 无 |
| $2$ | $8$ | $500$ | $3$ | 无 |
| $3$ | $13$ | $3\times10^3$ | $3$ | 无 |
| $4$ | $14$ | $2.5\times10^5$ | $3$ | A |
| $5$ | $15$ | $10^5$ | $3$ | B |
| $6$ | $7$ | $10^5$ | $3$ | 无 |
| $7$ | $14$ | $2.5\times10^5$ | $3$ | 无 |
| $8$ | $7$ | $5\times10^4$ | $4$ | 无 |
| $9$ | $6$ | $7.5\times10^4$ | $4$ | 无 |
| $10$ | $9$ | $4\times10^4$ | $5$ | 无 |

* 特殊性质 A：对于 $1\leq i\leq n$，$a_{1,i}=a_{2,i}$；
* 特殊性质 B：对于 $1\leq i\leq k$，不存在 $1\leq j_1<j_2\leq n$ 使得 $a_{i,j_1}=a_{i,j_2}$。

对于所有数据：$1\leq n\leq2.5\times10^5$，$\bm{3\leq k\leq 5}$，保证 $a$ 数组符合题意，且：

* $k=3$ 时，$n\leq2.5\times10^5$；
* $k=4$ 时：$n\leq7.5\times10^4$；
* $k=5$ 时：$n\leq4\times10^4$。


---

---
title: "[GCJ 2017 Finals] Stack Management"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13183
tag: ['图论', '2017', '深度优先搜索 DFS', '图论建模', 'Google Code Jam']
---
# [GCJ 2017 Finals] Stack Management
## 题目描述

You are playing a solitaire game in which there are $\mathbf{N}$ stacks of face-up cards, each of which initially has $\mathbf{C}$ cards. Each card has a value and a suit, and no two cards in the game have the same value/suit combination.

In one move, you can do one of the following things:

1. If there are two or more cards with the same suit that are on top of different stacks, you may remove the one of those cards with the smallest value from the game. (Whenever you remove the last card from a stack, the stack is still there — it just becomes empty.)
2. If there is an empty stack, you may take a card from the top of any one of the non-empty stacks and place it on top of (i.e., as the only card in) that empty stack.

You win the game if you can make a sequence of moves such that eventually, each stack contains at most one card. Given a starting arrangement, determine whether it is possible to win the game.
## 输入格式

The first line of the input gives the number $\mathbf{P}$ of premade stacks that will be used in the test cases. Then, $\mathbf{P}$ lines follow. The i-th of those lines begins with an integer $\mathbf{C}_{\mathbf{i}}$, the number of cards in the i-th of those premade stacks, and continues with $\mathbf{C}_{\mathbf{i}}$ ordered pairs of integers. The j-th of these ordered pairs has two integers $\mathbf{V}_{\mathbf{i j}}$ and $\mathbf{S}_{\mathbf{i j}}$, representing the value and suit of the j-th card from the top in the i-th premade stack.

Then, there is another line with one integer $\mathbf{T}$, the number of test cases. $\mathbf{T}$ test cases follow. Each case begins with one line with two integers $\mathbf{N}$ and $\mathbf{C}$: the number of stacks, and the number of cards in each of those stacks. Then, there is one line with $\mathbf{N}$ integers $\mathbf{P}_{\mathbf{i}}$, representing the indexes (starting from 0) of the test case's set of premade stacks.

## 输出格式

For each test case, output one line containing Case #x: y, where $x$ is the test case number (starting from 1) and $y$ is POSSIBLE if it is possible to win the game, or IMPOSSIBLE otherwise.
## 样例

### 样例输入 #1
```
5
2 7 2 7 1
2 6 4 7 4
2 3 2 6 2
2 4 2 10 2
2 5 4 7 3
2
2 2
0 2
3 2
4 1 3
```
### 样例输出 #1
```
Case #1: POSSIBLE
Case #2: IMPOSSIBLE
```
## 提示

**Sample Explanation**

In sample case #1, there are two stacks, each of which has two cards. The first stack has a 7 of suit 2 on top and a 7 of suit 1 below that. The second stack has a 3 of suit 2 on top and a 6 of suit 2 below that.

It is possible to win the game as follows:

* Remove the 3 of suit 2 from the second stack.
* Remove the 6 of suit 2 from the second stack. This makes the second stack empty.
* Move the 7 of suit 2 to the second stack. Then the win condition is satisfied: all stacks have at most one card.

In sample case #2, there are three stacks, each of which has two cards. It is not possible to win the game in this case; the only possible move is to remove the 5 of suit 4 on top of the third stack, and this does not open up any new moves.

**Limits**

- $1 \leq T \leq 100$.
- $2 \leq P \leq 60000$.
- $0 \leq P_i < P$, for all $i$.
- The $P_i$-th premade stack has exactly $C$ cards.
- No two cards in a test case have the same value/suit combination.

**Small dataset (10 Pts, Test Set 1 - Visible)**

- $2 \leq N \leq 4$.
- $2 \leq C_i \leq 13$, for all $i$.
- $2 \leq C \leq 13$.
- $1 \leq V_{ij} \leq 13$, for all $i$ and $j$.
- $1 \leq S_{ij} \leq 4$, for all $i$ and $j$.

**Large dataset (30 Pts, Test Set 2 - Hidden)**

- $2 \leq N \leq 50000$.
- $2 \leq C_i \leq 50000$, for all $i$.
- $2 \leq C \leq 50000$.
- $4 \leq N \times C \leq 10^5$.
- $1 \leq V_{ij} \leq 50000$, for all $i$ and $j$.
- $1 \leq S_{ij} \leq 50000$, for all $i$ and $j$.


---

---
title: "[NOI2011] 兔兔与蛋蛋游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1971
tag: ['2011', 'NOI', '深度优先搜索 DFS', '二分图']
---
# [NOI2011] 兔兔与蛋蛋游戏
## 题目描述

这些天，兔兔和蛋蛋喜欢上了一种新的棋类游戏。

这个游戏是在一个 $n$ 行 $m$ 列的棋盘上进行的。游戏开始之前，棋盘上有一个格子是空的，其它的格子中都放置了一枚棋子，棋子或者是黑色，或者是白色。

每一局游戏总是兔兔先操作，之后双方轮流操作，具体操作为：

* 兔兔每次操作时，选择一枚与空格相邻的白色棋子，将它移进空格。
* 蛋蛋每次操作时，选择一枚与空格相邻的黑色棋子，将它移进空格。

第一个不能按照规则操作的人输掉游戏。为了描述方便，下面将操作“将第x行第y列中的棋子移进空格中”记为 $M(x,y)$。

例如下面是三个游戏的例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/6wfmhuf2.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/j7vox6n7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/er1t5wpb.png)

最近兔兔总是输掉游戏，而且蛋蛋格外嚣张，于是兔兔想请她的好朋友——你——来帮助她。她带来了一局输给蛋蛋的游戏的实录，请你指出这一局游戏中所有她“犯错误”的地方。

注意：

* 两个格子相邻当且仅当它们有一条公共边。
* 兔兔的操作是“犯错误”的，当且仅当，在这次操作前兔兔有必胜策略，而这次操作后蛋蛋有必胜策略。

## 输入格式

输入的第一行包含两个正整数 $n,m$。

接下来 $n$ 行描述初始棋盘。其中第 $i$ 行包含 $m$ 个字符，每个字符都是大写英文字母 `X`、大写英文字母 `O` 或点号 `.` 之一，分别表示对应的棋盘格中有黑色棋子、有白色棋子和没有棋子。其中点号 `.` 恰好出现一次。

接下来一行包含一个整数 $k$（$1\leq k\leq 1000$） ，表示兔兔和蛋蛋各进行了 $k$ 次操作。

接下来 $2k$ 行描述一局游戏的过程。其中第 $2i - 1$ 行是兔兔的第 $i$ 次操作（编号为 $i$ 的操作） ，第 $2i$ 行是蛋蛋的第 $i$ 次操作。每个操作使用两个整数 $x,y$ 来描述，表示将第 $x$ 行第 $y$ 列中的棋子移进空格中。

输入保证整个棋盘中只有一个格子没有棋子， 游戏过程中兔兔和蛋蛋的每个操作都是合法的，且最后蛋蛋获胜。

## 输出格式

输出文件的第一行包含一个整数 $r$，表示兔兔犯错误的总次数。

接下来 $r$ 行按递增的顺序给出兔兔“犯错误”的操作编号。其中第 $i$ 行包含一个整数 $a_i$ 表示兔兔第 $i$ 个犯错误的操作是他在游戏中的第 $a_i$ 次操作。


## 样例

### 样例输入 #1
```
1 6 
XO.OXO 
1 
1 2 
1 1 
```
### 样例输出 #1
```
1
1
```
### 样例输入 #2
```
3 3 
XOX 
O.O 
XOX 
4 
2 3 
1 3 
1 2 
1 1 
2 1 
3 1 
3 2 
3 3 
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4 4 
OOXX 
OXXO 
OO.O 
XXXO 
2 
3 2 
2 2 
1 2 
1 3 
```
### 样例输出 #3
```
2
1
2
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 40$，$1 \leq m\leq 40$，$1\leq k\leq 1000$。

|测试点编号|$n$|$m$|
|:-:|:-:|:-:|
|$1,2$|$n=1$|$1\leq m\leq 20$|
|$3$|$n=3$|$m=4$|
|$4,5$|$n=4$|$m=4$|
|$6,7$|$n=4$|$m=5$|
|$8$|$n=3$|$m=7$|
|$9\sim 14$|$n=2$|$1\leq m\leq 40$|
|$15,16$|$1\leq n\leq 16$|$1\leq m\leq 16$|
|$17\sim 20$|$1\leq n\leq 40$|$1\leq m\leq 40$|



---

---
title: "[IOI 2017] Nowruz"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3836
tag: ['搜索', '贪心', '2017', 'IOI', '提交答案', 'Special Judge', '深度优先搜索 DFS']
---
# [IOI 2017] Nowruz
## 题目背景

**[数据以及checker下载](http://pan.baidu.com/s/1o8jwPmy)**

## 题目描述

再过几天就是诺鲁孜节了（波斯人的新年），爷爷邀请他的全家人到他的花园来聚会。在众多的宾客中有$k$个小孩。为了让这些孩子们在聚会中更开心，爷爷打算让他们玩一个捉迷藏的游戏。

整个花园可以看成一个有$m\times n$个方格的网格。其中有一些（或许没有）方格被岩石堵住了，而剩下的方格就称为**空格**。如果两个格子共享同一条边，我们就称这两个格子是**邻居**。因此，每一个方格最多有$4$个邻居：两个水平方向的和两个垂直方向的。爷爷想把花园变成一个迷宫。为达此目的，他会在花园中的一些**空格**上种植灌木来堵住他们。而这些被灌木丛堵住的方格就不再是**空格**了。

一个迷宫必须具有下面所述的性质。在迷宫中的任意一对空格$a$和$b$之间都只会恰有唯一的一条简单路径相连。而这条由$a$到$b$的简单路径就是一个从空格$a$开始并以空格$b$结束的序列，序列中所有的方格必须是不同的，而且每个相连的方格都是邻居。

一个小孩能够躲藏的方格当且仅当这个方格是**空格**，而且它恰有唯一一个邻居是空格。同一个空格内只能躲藏一个小孩。

题目会给出整个花园的地图作为输入文件。你的任务就是帮助爷爷构造一个能够躲藏尽量多小孩的迷宫。


## 评分

一个**有效**的输出文件必须符合下列所有的条件：

- 除了把输入文件中的任意多个字母`.`修改成字母`X`（即被灌木堵塞）外，输出的地图必须和输入地图完全一样。

- 输出的地图必须符合在上文中提及的迷宫的所有性质。


对于某一个测试数据，如果你的输出不是**有效**的，你的这个测试数据的得分将会是$0$。反之，你的得分是$\min(10, 10\cdot l/k)$，向下取值至小数后二位，这里的$l$是指你输出的迷宫中能够最多藏着的小孩，而$k$则表示在输入文件中题目要求你躲藏的小孩数目。对于一个测试数据，你能够得到$10$分，当且仅当你的输入是一个能够躲藏$k$个或更多个小孩的迷宫。

对于每组测试数据都存在一个能得到$10$分的答案。

请注意如果你答案是有效的，但根据上述公式你的得分仍然是$0$分，则在评分系统中，现实的结果将会是'Wrong Answer'。

## 输入格式

这是一个提交答案型的题目，而且它有部份分。题目会给出$10$个描述爷爷花园的输入文件。对于每个输入文件你应该提交一个含有迷宫的地图作为输出文件我们会根据你提交的每个输入文件中的迷宫能够躲藏的小孩数目来给出你的分数。

这道题目你不需要提交任何源代码。

每个输入文件都描述了一个表示整个花园的网格，我们也会给出爷爷邀请的小孩数目$k$。格式如下：

第$1$行： $1 : \ \ m \ n \ k$

第$1+i\ (1 \leqslant i \leqslant m)$行： 网格中的第$i$行，它是一个长度为$n$的字符串，包含以下的字符（中间没有空格）：

- `.`： 一个空格，

- `#`： 一块岩石。

## 输出格式

第$i\ (1 \leqslant i \leqslant m)$行： 迷宫中的第$i$行（种植了树木的花园）。它是一个长度为$n$的字符串，包含以下字母（中间没有空格）：

\* `.` ： 一个空格，

\* `#`： 一块岩石，

\* `X`： 一个灌木（注意字母X必须为大写字母）。

## 样例

### 样例输入 #1
```
4 5 5
....#
.#..#
...#.
....#
```
### 样例输出 #1
```
.X.X#
.#..#
...#X
XX..#

//这是其中一个有效的输出

```
## 提示

样例输出是其中一个有效的输出。

对于这个输出，因为$l=4$个小孩能够这个迷宫中，所以这个解答能够得到$10 \cdot 4 / 5 = 8$分。小孩能够躲藏的方格如下以O所示：

```plain
OXOX#
.#.O#
...#X
XX.O#
```
以下的三个输出都不是有效的输出：

```plain
.XXX#    ...X#    XXXX#
.#XX#    .#.X#    X#XX#
...#.    ...#X    ..X#X
XX..#    XXXX#    ..XX#
```
在最左边的输出中，左上角的空格和最右列（位于右下方）的空格之间并没有一条简单路径。

在其他的两个输出中，对于任意两个空格之间都恰有两条简单路径相连。


## 限制条件

$1 \leqslant m,n \leqslant 1024$


---

---
title: "[USACO17DEC] Push a Box P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4082
tag: ['2017', 'USACO', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [USACO17DEC] Push a Box P
## 题目描述

**题目译自 [USACO 2017 December Contest, Platinum](http://usaco.org/index.php?page=dec17results) Problem 2. [Push a Box](http://usaco.org/index.php?page=viewproblem2&cpid=769)**

一个谷仓是一个 $N \times M$ 的矩形网格，有一些网格里有干草。 Bessie 站在其中一个格子内，还有一个格子里有一个大木箱。 Bessie 不能和大木箱在一个格子里，也不能和干草在一个格子里。

如果她不与干草在同一个格子，她就可以往自己旁边的四个方向（东西南北）移动，如果她想移动到有木箱的格子里，那个木箱就会被她推一格（只要木箱的那个方向还有空间），如果没有空间，那 Bessie 就不能移动了。

给你谷仓的布局（空格子，干草以及木箱位置）以及 Bessie 的出发位置和箱子要被推到的位置，请你帮忙计算 Bessie 能不能把木箱推到指定位置。
## 输入格式

第一行有三个数 $N,M,Q$，其中 $N$ 是谷仓的行数，$M$ 是列数，$Q$ 是询问数。

接下来 $N$ 行是谷仓的初始布局，其中 `.` 代表空格子， `#` 代表干草格子， `A` 代表 Bessie 的初始位置， `B` 是木箱的初始位置。

接下来 $Q$ 行，每行一个坐标 $(R,C)$ ，代表第 $R$ 行第 $C$ 行。对于每行，你要输出 Bessie 是否有可能把箱子推到这个位置。
## 输出格式

$Q$ 行，每行一个答案，如果 Bessie 能走到，输出 `YES` ，否则输出 `NO` 。
## 样例

### 样例输入 #1
```
5 5 4
##.##
##.##
A.B..
##.##
##.##
3 2
3 5
1 3
5 3
```
### 样例输出 #1
```
NO
YES
NO
NO
```
## 提示

对于 $100\%$ 的数据，保证 $1\leq N,M \leq 1500$，$1\leq Q\leq 50000$。


---

---
title: "[IOI 2020] 网络站点"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6838
tag: ['2020', 'IOI', '交互题', 'Special Judge', '深度优先搜索 DFS']
---
# [IOI 2020] 网络站点
## 题目描述

新加坡的互联网主干网由 $n$ 个网络站点组成，这些站点分配了从 $0$ 到 $n-1$ 的 **序号**。互联网中还有 $n-1$ 条双向链路，它们从 $0$ 到 $n-2$ 编号。每条链路连接两个不同的站点。被一条链路连接着的两个站点互相称作对方的邻居。

一个由互不相同的站点所组成的站点序列 $a_0,a_1,\ldots,a_p$ 被称作一条从站点 $x$ 到站点 $y$ 的路径，当且仅当 $a_0=x$，$a_p=y$，并且序列中每两个连续的站点都是邻居。保证从任意站点 $x$ 到任意其他站点 $y$ **有且仅有** 一条路径。

任意站点 $x$ 可以生成一个数据包，并把它发送给任意其他站点 $y$，站点 $y$ 称作这个数据包的 **目的站点**。数据包需要按下述规则在站点 $x$ 到站点 $y$ 的唯一路径上进行路由。假设数据包当前发送到了站点 $z$，其中 $y$ 是数据包的目的站点且 $z \ne y$，则站点 $z$ 会：

1. 执行 **路由函数**，找到 $z$ 到 $y$ 的唯⼀路径中 $z$ 的邻居。然后
2. 将数据包转发给这个邻居。

然而，站点有存储内存限制，可能无法存下路由函数中需要使用的完整的主干网链路列表。

你的任务是实现主干网的路由机制，它由两个函数组成。

- 第一个函数的输入参数为 $n$、主干网链路的列表和一个整数 $k \ge n-1$。该函数需要为每个站点分配一个独一无二的  **编号**，其大小在 $0$ 到 $k-1$ 之间（包括 $0$ 和 $k-1$）。
- 第二个函数是路由函数，它在站点编号分配好后部署到所有站点上。它的输入参数如下：
	- $s$，数据包当前所处的站点的 **编号**，
	- $t$，数据包的目的站点的 **编号** $(t \ne s)$，
	- $c$，表示 $s$ 的所有邻居站点的 **编号** 的列表。
    
该函数应该返回一个 $s$ 的邻居的 **编号**，表示数据包需要转发到的下个站点。

在每个子任务中，你的得分取决于所有站点被分配到的编号的最大值（通常来说，编号最大值越小越好）。

#### 实现细节

你需要实现下列函数：

```cpp
int[] label(int n, int k, int[] u, int[] v)
  ```

- $n$: 主干网中站点的数量。
- $k$: 可用的编号的最大值。
- $u$ 和 $v$: 大小为 $n-1$ 的数组，表示链路。对每个 $i(0 \le i \le  \le n-2)$，链路 $i$ 连接着序号为 $u[i]$ 和 $v[i]$ 的站点。
- 该函数应该返回一个大小为 $n$ 的数组 $L$。对每个 $i(0 \le i \le n-1)$，$L[i]$ 表示序号为 $i$ 的站点所分配到的编号。数组 $L$ 中的所有元素必须互不相同并且大小在 $0$ 到 $k$ 之间。

```cpp
int find_next_station(int s, int t, int[] c)
```

- $s$: 数据包当前所在站点的编号。
- $t$: 数据包目的站点的编号。
- $c$: 一个数组，包含 $s$ 的所有邻居的编号。数组 $c$ 按照元素大小升序排列。
- 该函数应该返回一个 $s$ 的邻居的编号，表示数据包需要转发到的下个站点。

每个测试用例包含一个或多个独立的场景（也就是不同的主干网描述）。 对于一个包含 $r$ 个场景的测试用例，调用上述函数的评测程序会按下列步骤运行恰好两次。

程序第一次运行期间：

- `label` 函数被调用 $r$ 次，
- 返回的编号将被评测系统保存，并且
- `find_next_station` 不会被调用。

程序第二次运行期间：

- `find_next_station` 会被调用若干次。对于每次调用，评测程序会选择任意某个场景，该场景中的 `label` 函数所返回的编号方式将用于本次 `find_next_station` 调用。
- `label` 不会被调用。
- 特别地，在评测程序第一次运行期间，保存在静态或全局变量中的信息将无法在 `find_next_station` 函数中使用。
## 提示

#### 样例说明

#### 例 1

考虑下列调用：

```cpp
label(5, 10, [0, 1, 1, 2], [1, 2, 3, 4])
```

共有 $5$ 个站点和 $4$ 条链路，链路对应的站点序号对分别为 $(0,1)$, $(1,2)$, $(1,3)$ 和 $(2,4)$。编号的大小范围为 $0$ 到 $k=10$。

为了返回下列编号方案：

|序号|编号|
|:-:|:-:|
|$0$| $6$|
|$1$| $2$|
|$2$|$9$|
|$3$ |$3$|
|$4$ |$7$|

函数 `label` 应该返回 $[6,2,9,3,7]$。下图中的数字表示站点的序号（左图）与分配到的编号（右图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/xpq3km1p.png)

假设编号按照上图所示进行分配，考虑下列的调用：

```cpp
find_next_station(9, 6, [2, 7])
```

它表示数据包当前所处的站点编号为 $9$，其目的站点的编号为 $6$。从当前站点到目的站点的路径上，站点编号依次为 $[9,2,6]$。因此，函数应该返回 $2$，表示数据包应该转发给编号为 $2$ 的站点（其序号为 $1$）。

考虑另一个可能的调用：

```cpp
find_next_station(2, 3, [3, 6, 9])
  ```
该函数应该返回 $3$，因为目的站点（编号 $3$）是当前站点（编号 $2$）的邻居，因此目的站点直接接收到了数据包。

#### 约束条件

- $1 \le r \le 10$

对于 `label` 的每次调用：

- $2 \le n \le 1000$
- $k \ge n-1$
- $0 \le u[i],v[i] \le n-1$（对于所有 $0 \le i \le n-2$）

对于 `find_next_station` 的每次调用，其输入参数来自于任意选择的某次之前对 `label` 的调用。考虑它所产生的编号，

- $s$ 和 $t$ 是两个不同站点的编号。
- $c$ 是编号为 $s$ 的站点的所有邻居的编号的序列，升序排列。

对于每个测试用例，所有场景加到⼀起，传递给函数  `find_next_station` 的所有数组 $c$ 的总长度不超过 $10^5$。

#### 子任务

1. （5 分）$k=1000$，不会出现拥有多于 $2$ 个邻居的站点。
2. （8 分）$k=1000$，链路 $i$ 连接站点 $i+1$ 和 $\lfloor\frac{i}{2}\rfloor$。
3. （16 分）$k=10^6$，最多一个站点拥有多于 $2$ 个的邻居。
4. （10 分）$n \le 6$，$k \le 10^9$
5. （61 分）$k \le 10^9$

在子任务 5 中，你可以获得部分分。 令 $m$ 为所有场景中 `label` 返回的最大编号。 对于这个子任务，你的得分将根据下表计算得到：

|最大编号|得分|
|:-:|:-:|
|$m \ge 10^9$|$0$|
|$2000 \le m < 10^9$|$50 \cdot \log_{5 \cdot10^5}(\frac{10^9}{m})$|
|$1000 < m < 5000$|$50$|
|$m \le 1000$|$61$|

#### 评测程序示例

评测程序示例以如下格式读取输入数据：

第 $1$ 行：$r$

接下来是 $r$ 块内容，每块描述了一个单独的场景，格式如下：

第 $1$ 行：$n\ k$        
第 $2+i(0 \le i \le n-2)$ 行：$u[i]\ v[i]$         
第 $1+n$ 行：$q$，`find_next_station` 的调用次数    
第 $2+n+j(0 \le j \le q-1)$ 行：$z[j]\ y[j]\ w[j]$，第 $j$ 次调用 `find_next_station` 时所涉及的站点的 **序号**。此时，数据包在站点 $z[j]$，目的站点为 $y[j]$，应该要转发给站点 $w[j]$。

评测程序示例以如下格式打印你的结果：

第 $1$ 行：$m$

接下来是 $r$ 块内容，分别对应输入中的场景。每块的格式如下：

第 $1+j(0 \le j \le q-1)$ 行：站点的 **序号**，它所对应的 **编号** 是第 $j$ 次调用 `find_next_station` 时返回的结果。

注意：评测程序示例每次执行时会同时调用 `label` 和 `find_next_station`。


---

