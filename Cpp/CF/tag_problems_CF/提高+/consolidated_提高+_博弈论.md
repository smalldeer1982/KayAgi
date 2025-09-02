---
title: "Game on Tree (Hard)"
layout: "post"
diff: 提高+/省选-
pid: CF1970C3
tag: ['博弈论', '树形 DP']
---

# Game on Tree (Hard)

## 题目描述

This is the hard version of the problem. The only difference in this version is the constraint on $ t $ .

Ron and Hermione are playing a game on a tree of $ n $ nodes that are initially inactive. The game consists of $ t $ rounds, each of which starts with a stone on exactly one node, which is considered as activated. A move consists of picking an inactive neighbor of the node with a stone on it and moving the stone there (thus activating this neighbor). Ron makes the first move, after which he alternates with Hermione until no valid move is available. The player that cannot make a move loses the round. If both players play optimally, who wins each round of this game?

Note that all the rounds are played with the same tree; only the starting node changes. Moreover, after each round, all active nodes are considered inactive again.

## 输入格式

The first line contains integers $ n $ ( $ 2 \leq n \leq 2\times 10^5 $ ), $ t $ ( $ 1 \leq t \leq n $ ), the number of nodes in the tree and the number of rounds, respectively.

The next $ n-1 $ lines contain two integers $ 1 \leq u, v \leq n $ each, corresponding to an edge of the tree.

The next line contains $ t $ integers $ 1 \leq u_1 , \dots , u_t \leq n $ , corresponding to the node where the stone is initially put.

## 输出格式

The output consists of $ t $ lines, each line being either "Ron" or "Hermione".

## 样例 #1

### 输入

```
5 2
1 2
1 3
3 4
3 5
1 2
```

### 输出

```
Ron
Ron
```

## 样例 #2

### 输入

```
6 3
1 2
2 3
1 4
4 5
4 6
1 4 6
```

### 输出

```
Hermione
Ron
Hermione
```



---

---
title: "Not a Nim Problem"
layout: "post"
diff: 提高+/省选-
pid: CF2004E
tag: ['博弈论']
---

# Not a Nim Problem

## 题目描述

有 $n$ 堆石子，每堆有 $a_i$ 个。

Alice 和 Bob 轮流取石子。Alice 先手。每个人在当前回合下可以随意选择一堆石子取任意数量个，要求：

- 设选择的这堆石子有 $x$，取走 $y$ 个，则必须使 $x$ 与 $y$ 互质。

第一个不能操作的人输掉这场游戏。在两人都使用最优策略的前提下，求获胜者。

## 输入格式

第一行一个正整数 $t(1 \leq t \leq 10^4)$ 表示测试数据组数。

每一组测试数据中： 

- 第一行输入一个正整数 $n(1 \leq n \leq 3 \times 10^5)$。
- 第二行输入 $n$ 个正整数 $a_i(1 \leq a_i \leq 10^7)$。

保证单测试点内所有测试数据下 $n$ 的总和不超过 $3 \times 10^5$。

## 输出格式

对于每一组测试数据，输出一行一个字符串 $\texttt{Alice}$ 或 $\texttt{Bob}$ 表示获胜者。

$\scriptsize \text{Written by McIron233.}$

## 样例 #1

### 输入

```
3
3
3 2 9
4
3 3 6 1
5
1 2 3 4 5
```

### 输出

```
Bob
Alice
Bob
```



---

---
title: "Nim"
layout: "post"
diff: 提高+/省选-
pid: CF2043F
tag: ['动态规划 DP', '博弈论', '鸽笼原理']
---

# Nim

## 题目描述

重温一下「Nim」游戏的规则。游戏开始时有 $ n $ 堆石子，第 $ i $ 堆中有若干石子。两名玩家轮流行动：选择一个不为空的石子堆，从中取走至少一个石子。不能进行操作的玩家将输掉游戏。

现有一个包含 $ n $ 个整数的数组 $ a $。Artem 和 Ruslan 打算在数组的部分区间上进行 Nim 游戏。每个游戏回合由一个区间 $ (l_i, r_i) $ 确定，其中 $ a_{l_i}, a_{l_i+1}, \dots, a_{r_i} $ 是各个石子堆的大小。

在每轮游戏开始前，Ruslan 可以选择从该区间中移除任意数量的堆，但至少要留下一个堆，因此最多可移除 $ (r_i - l_i) $ 堆。他可以选择不移除任何堆。移除后，游戏将在留下的堆上进行。

每个回合相互独立：某一回合的变动不会影响原始数组或其他回合。

Ruslan 的目标是移除尽可能多的石子堆，以确保始终是先手的 Artem 输掉游戏。

对于每个回合：

1. 确定 Ruslan 可以移除的最大石子堆数量；
2. 计算达到最大移除数量的方法数，并输出其对 $ 998\,244\,353 $ 取模的结果。

若两种移除方法在某个索引 $ i $ 上存在区别，即一种方法移除了该索引对应的堆而另一种没有，则视为两种不同的方法。若 Ruslan 无法确保 Artem 输掉某回合，则输出 -1。

## 输入格式

第一行包含两个整数 $ n $ 和 $ q $（$ 1 \le n, q \le 10^5 $），分别表示数组的大小和需要计算结果的区间数。

第二行是 $ n $ 个整数 $ a_1, a_2, \dots, a_n $（$ 0 \le a_i \le 50 $），表示初始数组中的元素。

接下来的 $ q $ 行中，每行包含两个整数 $ l_i, r_i $（$ 1 \le l_i \le r_i \le n $），定义第 $ i $ 个回合中要进行操作的区间。

## 输出格式

对于每个回合：

- 如果 Ruslan 能赢，输出两个整数——可以移除的最大堆数及其对应的移除方案数量（对 $ 998\,244\,353 $ 取模）；
- 否则输出 -1。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
9 5
0 1 2 1 3 4 5 6 0
1 5
2 5
3 5
4 5
1 9
```

### 输出

```
4 1
2 1
0 1
-1
8 2
```



---

---
title: "Game with Binary String"
layout: "post"
diff: 提高+/省选-
pid: CF2070E
tag: ['博弈论', '线段树']
---

# Game with Binary String

## 题目描述

考虑以下游戏。两个玩家拥有一个二进制字符串（一个由字符 0 和/或 1 组成的字符串）。玩家轮流行动，由第一位玩家先手。在玩家的回合中，必须选择字符串中恰好两个相邻元素并移除它们（首元素和末元素也被视为相邻）。此外，根据当前行动玩家的不同存在额外约束：

- 如果是第一位玩家的回合，所选的两个字符必须都是 0；
- 如果是第二位玩家的回合，所选的两个字符中至少有一个必须是 1。

无法进行有效移动的玩家输掉游戏。这也意味着如果当前字符串长度小于 2，当前玩家输掉游戏。

给定一个长度为 $n$ 的二进制字符串 $s$。你需要计算其满足以下条件的子串数量：若在该子串上进行游戏且双方都采取最优决策，第一位玩家将获胜。换句话说，计算满足 $1 \le l \le r \le n$ 的有序对 $(l, r)$ 的数量，使得在字符串 $s_l s_{l+1} \dots s_r$ 上第一位玩家拥有必胜策略。

## 输入格式

第一行包含一个整数 $n$（$1 \le n \le 3 \cdot 10^5$）。

第二行包含字符串 $s$，由恰好 $n$ 个字符组成。每个字符为 0 或 1。

## 输出格式

输出一个整数——满足条件的子串数量（即第一位玩家能获胜的子串数量）。


## 说明/提示

第一个示例中，以下子串是第一位玩家的必胜子串（$s[l:r]$ 表示 $s_l s_{l+1} \dots s_r$）：

- $s[1:2]$；
- $s[1:3]$；
- $s[1:7]$；
- $s[2:4]$；
- $s[2:8]$；
- $s[3:5]$；
- $s[4:5]$；
- $s[4:6]$；
- $s[5:7]$；
- $s[6:8]$；
- $s[7:8]$；
- $s[7:9]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
10
0010010011
```

### 输出

```
12
```



---

---
title: "Fox and Card Game"
layout: "post"
diff: 提高+/省选-
pid: CF388C
tag: ['贪心', '博弈论']
---

# Fox and Card Game

## 题目描述

Fox Ciel is playing a card game with her friend Fox Jiro. There are $ n $ piles of cards on the table. And there is a positive integer on each card.

The players take turns and Ciel takes the first turn. In Ciel's turn she takes a card from the top of any non-empty pile, and in Jiro's turn he takes a card from the bottom of any non-empty pile. Each player wants to maximize the total sum of the cards he took. The game ends when all piles become empty.

Suppose Ciel and Jiro play optimally, what is the score of the game?

## 输入格式

The first line contain an integer $ n $ ( $ 1<=n<=100 $ ). Each of the next $ n $ lines contains a description of the pile: the first integer in the line is $ s_{i} $ ( $ 1<=s_{i}<=100 $ ) — the number of cards in the $ i $ -th pile; then follow $ s_{i} $ positive integers $ c_{1} $ , $ c_{2} $ , ..., $ c_{k} $ , ..., $ c_{si} $ ( $ 1<=c_{k}<=1000 $ ) — the sequence of the numbers on the cards listed from top of the current pile to bottom of the pile.

## 输出格式

Print two integers: the sum of Ciel's cards and the sum of Jiro's cards if they play optimally.

## 说明/提示

In the first example, Ciel will take the cards with number 100 and 1, Jiro will take the card with number 10.

In the second example, Ciel will take cards with numbers 2, 8, 6, 5, 9 and Jiro will take cards with numbers 4, 7, 1, 3.

## 样例 #1

### 输入

```
2
1 100
2 1 10

```

### 输出

```
101 10

```

## 样例 #2

### 输入

```
1
9 2 8 6 5 9 4 7 1 3

```

### 输出

```
30 15

```

## 样例 #3

### 输入

```
3
3 1 3 2
3 5 4 6
2 8 7

```

### 输出

```
18 18

```

## 样例 #4

### 输入

```
3
3 1000 1000 1000
6 1000 1000 1000 1000 1000 1000
5 1000 1000 1000 1000 1000

```

### 输出

```
7000 7000

```



---

---
title: "Funny Game"
layout: "post"
diff: 提高+/省选-
pid: CF731E
tag: ['动态规划 DP', '博弈论']
---

# Funny Game

## 题目描述

Once upon a time Petya and Gena gathered after another programming competition and decided to play some game. As they consider most modern games to be boring, they always try to invent their own games. They have only stickers and markers, but that won't stop them.

The game they came up with has the following rules. Initially, there are $ n $ stickers on the wall arranged in a row. Each sticker has some number written on it. Now they alternate turn, Petya moves first.

One move happens as follows. Lets say there are $ m>=2 $ stickers on the wall. The player, who makes the current move, picks some integer $ k $ from $ 2 $ to $ m $ and takes $ k $ leftmost stickers (removes them from the wall). After that he makes the new sticker, puts it to the left end of the row, and writes on it the new integer, equal to the sum of all stickers he took on this move.

Game ends when there is only one sticker left on the wall. The score of the player is equal to the sum of integers written on all stickers he took during all his moves. The goal of each player is to maximize the difference between his score and the score of his opponent.

Given the integer $ n $ and the initial sequence of stickers on the wall, define the result of the game, i.e. the difference between the Petya's and Gena's score if both players play optimally.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 2<=n<=200000 $ ) — the number of stickers, initially located on the wall.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ -10000<=a_{i}<=10000 $ ) — the numbers on stickers in order from left to right.

## 输出格式

Print one integer — the difference between the Petya's score and Gena's score at the end of the game if both players play optimally.

## 说明/提示

In the first sample, the optimal move for Petya is to take all the stickers. As a result, his score will be equal to $ 14 $ and Gena's score will be equal to $ 0 $ .

In the second sample, the optimal sequence of moves is the following. On the first move Petya will take first three sticker and will put the new sticker with value $ -8 $ . On the second move Gena will take the remaining two stickers. The Petya's score is $ 1+(-7)+(-2)=-8 $ , Gena's score is $ (-8)+3=-5 $ , i.e. the score difference will be $ -3 $ .

## 样例 #1

### 输入

```
3
2 4 8

```

### 输出

```
14

```

## 样例 #2

### 输入

```
4
1 -7 -2 3

```

### 输出

```
-3

```



---

