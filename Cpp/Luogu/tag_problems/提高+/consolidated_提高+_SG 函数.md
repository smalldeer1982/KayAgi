---
title: "[GCJ 2019 #3] Zillionim"
layout: "post"
diff: 提高+/省选-
pid: P13119
tag: ['博弈论', '2019', '交互题', 'Special Judge', 'SG 函数', 'Google Code Jam']
---
# [GCJ 2019 #3] Zillionim
## 题目描述

Zillionim is a turn-based game for two players. Initially, $10^{12}$ coins are arranged end-to-end in a single line, numbered from 1 to $10^{12}$ from left to right. During a turn, a player must select $10^{10}$ consecutive coins and remove them. Two coins that were not originally consecutive do not become consecutive even if all of the coins in between them are removed.

On their turn, a player makes a valid move if possible, and then it is their opponent's turn. If a player cannot make a valid move on their turn, they lose the game (and the opponent wins the game).

Because our engineers are still hard at work training our machine learning model to play Zillionim, we have created a simple AI that plays Zillionim by making random moves. The AI always gets the first turn. On each of the AI's turns, the AI determines all valid moves and chooses one of them uniformly at random.

Can you beat this AI... at least most of the time?

### Interactive Protocol

This is an interactive problem.

Initially, your program should read a single line containing two integers $\mathbf{T}$, the number of test cases, and $\mathbf{W}$, the minimum number of games you need to win for your solution to be considered correct. Then, you need to process $\mathbf{T}$ test cases, each of which is a single game of Zillionim.

Each test case is processed by making exchanges with the judge until one player wins the game. For each exchange, the judge first outputs a single line with a single integer $\mathbf{P}$, to be interpreted as follows:

* If $1 \leq \mathbf{P} \leq 10^{12} - 10^{10} + 1$, then the AI has removed coins numbered $\mathbf{P}$, $\mathbf{P} + 1$, ..., $\mathbf{P} + 10^{10} - 1$ and it is your turn. Note that this means there is at least one valid move remaining for you to play. The AI always plays a valid move.
* If $\mathbf{P} = -2$, your last move caused you to win the current game.
* If $\mathbf{P} = -3$, the AI has made a move that caused it to win the current game. Notice that in this case, the judge does not send you the AI's last move.
* If $\mathbf{P} = -1$, the last information you sent to the judge was malformed data or an invalid move (out of range or attempting to remove coins that were not there), meaning that you will get a Wrong Answer verdict for not playing correctly (more below).

After receiving a positive integer $\mathbf{P}$, you should send back a single line with a positive integer $\mathbf{Q}$ ($1 \leq \mathbf{Q} \leq 10^{12} - 10^{10} + 1$) representing that you are removing coins numbered $\mathbf{Q}$, $\mathbf{Q} + 1$, ..., $\mathbf{Q} + 10^{10} - 1$. Each of these coins must not have been previously removed during the current game.

After the judge sends a -2 or -3, if it was the last game, the judge will terminate and so should your program. Otherwise, the judge will proceed to send data corresponding to the first exchange of the next game. The judge will not check how many games you have won or lost until all games have been processed correctly. For example, if you win $\mathbf{T} - 1$ games and then send malformed data during the last game, you will receive a Wrong Answer verdict, regardless of the value of $\mathbf{W}$.

After receiving a -1, your program should terminate to receive a Wrong Answer verdict. If your program continues to wait for the judge after receiving -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit normally and within the time limit to receive a Wrong Answer verdict instead of a Runtime Error or Time Limit Exceeded.

The seed for the random generator is predetermined (and is different) for each game. This means that two submissions that make the exact same sequence of moves in a given game will receive the exact same sequence of moves from the AI for that game. It also means the play of the AI in a game does not depend, even in the pseudo-random generation sense, on the plays made in previous games within the same test set.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

**Sample Interaction**

For simplicity, the following interaction uses 50 coins in total instead of $10^{12}$, and each move removes 10 consecutive coins instead of $10^{10}$. The rules are otherwise the same.

```
  t, w = readline_int_list()   // reads 500 into t and 300 into w
  p = readline_int()           // reads 23 into p; this is the beginning of the first game. The
                               //   AI has taken coins 23 through 32, inclusive.
  printline 38 to stdout       // we decide to take coins 38 through 47, inclusive
  flush stdout
  p = readline_int()           // reads 3 into p. The AI has taken coins 3 through 12, inclusive.
  printline 13 to stdout       // we decide to take coins 13 through 22, inclusive
                               //  (and this is our only remaining move!)
  flush stdout
  p = readline_int()           // reads -2 into p. We won the first game since the AI had no move.
  p = readline_int()           // reads 32 into p; this is the beginning of the second game. The
                               //   AI has taken coins 32 through 41, inclusive.
  printline 13 to stdout       // we decide to take coins 13 through 22, inclusive
  flush stdout
  p = readline_int()           // reads -3 into p. We don't know the AI's move, but it left us
                               //   with no valid move, so we lost the second game.
  p = readline_int()           // reads 10 into p; this is the beginning of the third game. The
                               //   AI has taken coins 10 through 19, inclusive.
  printline 0 to stdout        // we select an invalid index (coin numbering starts at 1!)
  flush stdout
  p = readline_int()           // reads -1 into p -- we have made a mistake!
  exit                         // exits to avoid an ambiguous TLE error
```

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $\mathbf{T} = 500$.
- $-3 \leq \mathbf{P} \leq 10^{12} - 10^{10} + 1$.
- $\mathbf{P} \neq 0$.
- $\mathbf{P}$ represents a valid play or valid information about the game's status, as explained above.

**Test set 1 (1 Pt, Visible)**

- $\mathbf{W} = 300$.

**Test set 2 (5 Pts, Visible)**

- $\mathbf{W} = 475$.

**Test set 3 (6 Pts, Visible)**

- $\mathbf{W} = 499$.


---

---
title: "[SDOI2009] E&D"
layout: "post"
diff: 提高+/省选-
pid: P2148
tag: ['博弈论', '2009', '各省省选', '树状数组', '山东', '枚举', '位运算', 'SG 函数']
---
# [SDOI2009] E&D
## 题目描述

小 E 与小 W 进行一项名为 `E&D` 游戏。

游戏的规则如下：桌子上有 $2n$ 堆石子，编号为 $1 \sim 2n$。其中，为了方便起见，我们将第 $2k-1$ 堆与第 $2k$ 堆（$1 \le k \le n$）视为同一组。第 $i$ 堆的石子个数用一个正整数 $S_i$ 表示。

一次分割操作指的是，从桌子上任取一堆石子，将其移走。然后分割它同一组的另一堆石子，从中取出若干个石子放在被移走的位置，组成新的一堆。操作完成后，所有堆的石子数必须保证大于 $0$。显然，被分割的一堆的石子数至少要为 $2$。两个人轮流进行分割操作。如果轮到某人进行操作时，所有堆的石子数均为 $1$，则此时没有石子可以操作，判此人输掉比赛。

小 E 进行第一次分割。他想知道，是否存在某种策略使得他一定能战胜小 W。因此，他求助于小 F，也就是你，请你告诉他是否存在必胜策略。例如，假设初始时桌子上有 $4$ 堆石子，数量分别为 $1,2,3,1$。小 E 可以选择移走第 $1$ 堆，然后将第 $2$ 堆分割（只能分出 $1$ 个石子）。接下来，小 W 只能选择移走第 $4$ 堆，然后将第 $3$ 堆分割为 $1$ 和 $2$。最后轮到小 E，他只能移走后两堆中数量为 $1$ 的一堆，将另一堆分割为 $1$ 和 $1$。这样，轮到小 W 时，所有堆的数量均为 $1$，则他输掉了比赛。故小 E 存在必胜策略。
## 输入格式

**本题有多组数据。**

第一行一个整数 $T$，表示数据组数。

对于每组数据：

第一行一个整数 $N$，表示桌子上共有 $N$ 堆石子，这里的 $N$ 即为题目描述中的 $2n$。

第二行 $N$ 个整数 $S_{1 \dots N}$。
## 输出格式

对于每组数据，如果小 E 必胜，则一行一个字符串 `YES`，否则一行一个字符串 `NO`。


## 样例

### 样例输入 #1
```
2
4
1 2 3 1
6
1 1 1 1 1 1

```
### 样例输出 #1
```
YES
NO

```
## 提示

对于 $20\%$ 的数据，$N=2$。

对于另外 $20\%$ 的数据，$N \le 4$，$S_i \le 50$。

对于 $100\%$ 的数据，$1 \le T \le 20$，$1 \le N \le 2 \times 10^4$ 且 $N$ 为偶数，$1 \le S_i \le 2 \times 10^9$。


---

---
title: "高手过招"
layout: "post"
diff: 提高+/省选-
pid: P2575
tag: ['博弈论', 'SG 函数']
---
# 高手过招
## 题目描述

AKN 玩游戏玩累了，于是他开始和同伴下棋了，玩的是跳棋！对手是 wwx！这两位上古神遇在一起下棋，使得棋局变得玄幻莫测，高手过招，必有一赢，他们都将用最佳策略下棋，现在给你一个 $n \times 20$ 的棋盘，以及棋盘上有若干个棋子，问谁赢？akn 先手！

游戏规则是这样的：

对于一个棋子，能将它向右移动一格，如果右边有棋子，则向右跳到第一个空格，如果右边没有空格，则不能移动这个棋子，如果所有棋子都不能移动，那么将输掉这场比赛。
## 输入格式

第一行一个 $T$，表示 $T$ 组数据。

每组数据第一行 $n$，表示 $n \times 20$ 的棋盘。

接下来 $n$ 行每行第一个数 $m$ 表示第 $i$ 行有 $m$ 个棋子。

随后跟着 $m$ 个数 $p_j$ 表示第 $i$ 行的棋子布局。
## 输出格式

如果 AKN 能赢，则输出 `YES`，否则输出 `NO`。
## 样例

### 样例输入 #1
```
2
1
2 19 20
2
1 19
1 18

```
### 样例输出 #1
```
NO
YES

```
## 提示

$10\%$ 的数据 $T \leq 1,n \leq 1$。

另外 $10\%$ 的数据 $m \leq 1$。

$100\%$ 的数据 $T \leq 100$，$n \leq  1000$，$m \leq 20$，$1 \leq p_j \leq 20$。


---

---
title: "「JYLOI Round 1」让"
layout: "post"
diff: 提高+/省选-
pid: P6639
tag: ['博弈论', '博弈树', 'Nim 积', 'SG 函数']
---
# 「JYLOI Round 1」让
## 题目描述

Alice 和 Bob 在玩游戏。

现在有多堆石子，其中第 $k$ 堆石子有 $p_k$ 个，先后手轮流操作。取石子时，可以选任意一堆进行操作。若记 $i$ 为在这次取之前这堆石子的个数，$j$ 为这次要取的石子数，$R$ 为给定的常数，则需满足以下条件：

$$1 \leq i + j \leq R,i \geq j \geq 1$$

使对方无法操作者即为胜者。游戏时，双方都采用最优策略。

有多次游戏，具体来说，共有 $T$ 个操作，分为两类：

1. “``change x``” 表示将 $R$ 更改为 $x$。

2. “``query n``” 表示进行一次游戏，接下来有 $n$ 行，这 $n$ 行中的第 $i$ 行有两个正整数 $l_i$ 和 $r_i$，表示这次游戏的石子的堆数和个数可以用这 $n$ 个区间来表示。第 $i$ 个区间表示这次游戏的石子的堆数新增了 $(r_i - l_i + 1)$ 堆，并且其中这个区间所表示的第 $j(1 \leq j \leq r_i - l_i + 1)$ 堆的石子个数为 $(l_i + j - 1)$。

	例如当这次游戏的 $n = 2$，并且两个区间分别为 $[1, 7]$ 和 $[2, 3]$ 的时候，这次游戏一共有 $[(7 - 1 + 1) + (3 - 2 + 1)] = 9$ 堆石子，这 $9$ 堆石子的个数分别为 $1, 2, 3, 4, 5, 6, 7, 2, 3$。

由于 Bob 和 Alice 都非常聪明，而 Bob 希望不赢太多次，在适当的时候让让 Alice。因而他希望你帮他编写一个程序，对于每次游戏，如果先手有必胜策略输出“``1``”，否则输出“``0``”，你能做到吗？
## 输入格式

第一行有一个正整数 $T$，表示操作的个数。

接下来有 $T$ 个操作，格式如题所述。

## 输出格式

输出共一行，为一个长度小于 $T$ 的由字符 0 和 1 组成的字符串，含义如题所述。
## 样例

### 样例输入 #1
```
5
change 3
query 1
2 2
change 4
query 1
2 2
change 2
```
### 样例输出 #1
```
01
```
### 样例输入 #2
```
5
change 11
change 68
query 15
15 16
54 64
49 55
33 38
27 52
20 30
45 46
29 60
58 64
11 55
17 40
15 58
41 63
7 30
15 37
query 14
15 57
13 34
4 13
35 43
12 20
16 62
63 65
17 29
19 67
48 63
25 49
1 8
1 37
44 49
query 14
15 24
6 50
49 60
30 53
33 52
4 44
1 5
44 59
4 40
45 48
1 20
12 27
44 63
21 39
```
### 样例输出 #2
```
001
```
## 提示

### 样例 1 说明

共有 $T=5$ 个操作。

第 1 个操作将 $R$ 改成了 3。

第 2 个操作表示进行了一次游戏，这次游戏的 $n=1$，区间为 $[2, 2]$，表示这次游戏共有 $(2 - 2 + 1) = 1$ 堆石子，这 1 堆石子的个数为 $(2 + 1 - 1) = 2$。因为 $R=3$，因此先手最多只能够取 1 个。若取 2 个则不满足 **题目描述** 中的条件 $1 \leq i + j \leq R$，若取 3 个及以上则不满足 **题目描述** 中的条件 $1 \leq i + j \leq R,i \geq j \geq 1$，其中 $i$、$j$、$R$ 的含义如题所述。先手取完后唯一的一堆只剩下 1 颗石子，因为后手取了 1 颗石子后使先手无法操作，所以先手落败，又因为这是唯一的一种取法，所以先手必败，因此先手无必胜策略，输出“``0``”。

第 3 个操作将 $R$ 改成了 4。

第 4 个操作表示进行了一次游戏，这次游戏的 $n=1$，区间为 $[2, 2]$，表示这次游戏共有 $(2 - 2 + 1) = 1$ 堆石子，这 1 堆石子的个数为 $(2 + 1 - 1) = 2$。先手最多可以取 2 颗石子，因为当先手取 3 颗或以上时，不满足 **题目描述** 中的条件 $1 \leq i + j \leq R,i \geq j \geq 1$，其中 $i$、$j$、$R$ 的含义如题所述。因为当先手选择取 2 颗石子时，先手取完了所有石子，使后手无法操作，所以先手必胜，输出“``1``”。

第 5 个操作将 $R$ 改成了 2。

____________

### 数据范围

对于 $100\%$ 的数据，满足 $1 \leq T \leq 10^5, 2 \leq R \leq 10^{15}, 0 \leq l_i \leq r_i < R, 1 \leq \sum{n} \leq 5 \times 10^5$，并且第一个操作一定是第 1 类操作。

对于测试点 1~2 ，满足 $T \leq 10, l_i \leq r_i \leq 3$，并且在一轮游戏中石子的堆数不会超过 4。

对于测试点 3~6 ，满足 $T \leq 100, R \leq 100, \sum{n} \leq 100$。

对于测试点 7~10 ，满足 $T \leq 10, R \leq 10^5, \sum{n} \leq 50$。

对于测试点 11~12 ，满足 $R \leq 5 \times 10^3, \sum{n} \leq 5 \times 10^5$，并且只有一次修改操作。

对于测试点 13~16 ，满足 $T \leq 10^5,R \leq 10^5,\sum{n} \leq 5 \times 10^5$。

共 20 个测试点，每个测试点 5 分。

## 题目来源

「JYLOI Round 1」 E

Idea / Solution / Data：abcdeffa


---

---
title: "[POI 2000] 条纹"
layout: "post"
diff: 提高+/省选-
pid: P8369
tag: ['博弈论', '2000', 'POI（波兰）', 'SG 函数']
---
# [POI 2000] 条纹
## 题目描述

条纹游戏是一个双人的游戏。所需要的物品有一个棋盘以及三种颜色的长方形条纹，这三种颜色分别是红色、绿色和蓝色。所有的红色条纹的尺寸是 $c \times 1$，所有的绿色条纹的尺寸是 $z \times 1$，所有的蓝色条纹的尺寸是 $n \times 1$，这里 $c,z,n$ 是正整数。每种颜色的条纹每个游戏者都拥有无限多个。

一个棋盘是一个尺寸为 $p \times 1$ 的长方形，由 $p$ 个 $1 \times 1$ 的方格组成。

游戏者轮流走，每一步都是由一个游戏者任选一种长方形条纹覆盖到棋盘上，并要求遵循以下规则：

1. 条纹不能伸出棋盘之外。
2. 不能覆盖在已有的条纹之上（即使部分也不行）。
3. 条纹的边缘必须与棋盘方格的边缘相重叠。谁不能再走，谁就输了。

先手是指在游戏中第一个走的游戏者。那么是否不管后手怎么走，先手都有必胜策略呢？

请你编写一个程序：

1. 读入条纹的尺寸以及至少一个棋盘的尺寸。
2. 对每一个给出的棋盘判断先手是否必胜。
3. 将结果输出。
## 输入格式

第 $\text{1}$ 行包含三个整数 $c,z,n$，表示三种条纹的长度，依次为红色，绿色以及蓝色。每两个数之间都用空格隔开。

文件的第 $\text{2}$ 行包括一个整数 $m$ 表示需要考虑的不同棋盘个数。以下 $\text{3}$ 到 $\text{m+2}$ 行每行包括一个整数 $p$ ,第 $\text{i+2}$ 行表示第 $\text{i}$ 个棋盘的长度。
## 输出格式

应当包含 $m$ 行。只有一个数字应当被写入文件的第 $i$ 行：

如果对第 $i$ 个棋盘先手有必胜策略，输出 $1$，否则输出 $2$。
## 样例

### 样例输入 #1
```
1 5 1
3
1
5
6
```
### 样例输出 #1
```
1
1
2
```
## 提示

对于 $100$ % 的数据： $1 \le c,z,n,m,p \le 1000$。


---

---
title: "[THUPC 2023 决赛] 巧克力"
layout: "post"
diff: 提高+/省选-
pid: P9387
tag: ['2023', 'O2优化', '数位 DP', 'THUPC', 'SG 函数']
---
# [THUPC 2023 决赛] 巧克力
## 题目描述

上回你帮小 I 在开火车上薄纱小 J 后，小 J 十分不服气，决定拉上小 I 再玩玩别的游戏。这次小 J 找到了他家珍藏的巧克力。

小 J 准备了 $(N + 1)$ 条巧克力，其中除了第 $(N + 1)$ 条巧克力有 $M$ 块外，其他第 $i$ 条巧克力恰好有 $i$ 块。

游戏由小 I 先手，双方轮流操作，每次操作方可以进行如下操作：

- 选择一条巧克力，将其分成左中右有序的三段，其中**每段必须有整数块，中间一段不能为空，左右两段可以为空**；
- 将中间一段吃掉，左右两段放回游戏。

当某个人操作时没有巧克力了，那个人就输了。

游戏开始，小 I 还没来得及算好最优策略小 J 就连忙催促，于是小 I 只好**在所有的合法操作中等概率随机选择一个进行操作**。小 J 自然是有备而来，每次操作都是最优的；而在这次随机操作之后，小 I 也终于是算清楚了游戏策略，之后的每次操作都是最优的。

小 I 想知道，第一次的随机操作中，有多少种操作能够让他取得游戏胜利。答案可能很大，你只需要输出其对 $(10^9+7)$ 取模的结果。

认为两个操作不同当且仅当选择的巧克力不同或巧克力分成的有序的三段的块数有一段不同。
## 输入格式

**本题有多组测试数据。** 第一行一个整数 $T$ 表示测试数据组数。接下来依次输入每组测试数据。

每组测试数据一行两个整数 $N,M$，意义如题目描述所述。
## 输出格式

对于每组测试数据输出一行一个整数，表示能使小 I 胜利的第一次操作数对 $(10^9+7)$ 取模。
## 样例

### 样例输入 #1
```
4
3 0
3 1
3 12345678987654321
0 0

```
### 样例输出 #1
```
0
4
450617288
0

```
## 提示

#### 样例解释

- 对于第一组测试数据，容易证明先手必败，所以无论怎么操作小 I 都会输。
- 对于第二组测试数据，有以下四种操作：
  - 将第一条巧克力分成 $(0,1,0)$ 三段，将中间一段吃掉；
  - 将第四条巧克力分成 $(0,1,0)$ 三段，将中间一段吃掉；
  - 将第三条巧克力分为 $(0,1,2)$ 三段，将中间一段吃掉；
  - 将第三条巧克力分为 $(2,1,0)$ 三段，将中间一段吃掉。
- 对于第三组测试数据，所有的合法操作都是将第四条巧克力分成三段，其中左右两段长度相同。
- 对于第四组测试数据，游戏只是个幌子罢了，小 J 只是想小 I 输。

#### 数据范围

本题仅有一个 $T = 5 \times 10^4$ 的测试点，对于每组测试数据 $0 \le N,M \le 10^{18}$。

#### 后记

“下次能继续和你玩游戏吗……”

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）决赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023> 查看。


---

