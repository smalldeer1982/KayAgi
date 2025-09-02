---
title: "Game on Tree (Medium)"
layout: "post"
diff: 普及+/提高
pid: CF1970C2
tag: ['博弈论', '树形 DP']
---

# Game on Tree (Medium)

## 题目描述

This is the medium version of the problem. The difference in this version is that $ t=1 $ and we work on trees.

Ron and Hermione are playing a game on a tree of $ n $ nodes that are initially inactive. The game consists of $ t $ rounds, each of which starts with a stone on exactly one node, which is considered as activated. A move consists of picking an inactive neighbor of the node with a stone on it and moving the stone there (thus activating this neighbor). Ron makes the first move, after which he alternates with Hermione until no valid move is available. The player that cannot make a move loses the round. If both players play optimally, who wins each round of this game?

Note that all the rounds are played with the same tree; only the starting node changes. Moreover, after each round, all active nodes are considered inactive again.

## 输入格式

The first line contains integers $ n $ ( $ 2 \leq n \leq 2\times 10^5 $ ), $ t $ ( $ t=1 $ ), the number of nodes in the tree and the number of rounds, respectively.

The next $ n-1 $ lines contain two integers $ 1 \leq u, v \leq n $ each, corresponding to an edge of the tree.

The next line contains $ t $ integers $ 1 \leq u_1 , \dots, u_t \leq n $ , corresponding to the node where the stone is initially put.

## 输出格式

The output consists of $ t=1 $ line which is either "Ron" or "Hermione".

## 样例 #1

### 输入

```
5 1
1 2
1 3
3 4
3 5
1
```

### 输出

```
Ron
```



---

---
title: "Resourceful Caterpillar Sequence"
layout: "post"
diff: 普及+/提高
pid: CF2053E
tag: ['动态规划 DP', '博弈论', '树形 DP']
---

# Resourceful Caterpillar Sequence

## 题目描述

无尽的七日轮回

— r-906, [Panopticon](https://www.youtube.com/watch?v=_-Vd0ZGB-lo)

在一个由 $n$ 个顶点组成的树中，定义了一种“毛毛虫”。一个毛毛虫用整数对 $(p, q)$（$1 \leq p, q \leq n$，且 $p \neq q$）表示，它的头在顶点 $p$，尾在顶点 $q$，并且该毛毛虫支配从 $p$ 到 $q$ 的简单路径上的所有顶点（包括 $p$ 和 $q$）。$(p, q)$ 的毛毛虫序列是按到 $p$ 的距离递增排序后的路径上的顶点序列。

Nora 和 Aron 轮流移动这条毛毛虫，Nora 先手。两个人都采用各自的最优策略来进行游戏：

- 他们会尽全力争取胜利；
- 如果无法赢得胜利，他们将努力阻止对方获胜（这样，游戏就会以平局收场）。

在 Nora 的回合中，她需要从与顶点 $p$ 相邻且未被毛毛虫支配的顶点中选择一个 $u$，然后将毛毛虫向顶点 $u$ 移动一个边。同样，在 Aron 的回合中，他需要从与顶点 $q$ 相邻且未被毛毛虫支配的顶点中选择一个 $v$，并将毛毛虫向顶点 $v$ 移动一个边。注意，两位玩家的移动方式是不同的。

若 $p$ 是叶子节点时，Nora 赢得胜利。而当 $q$ 是叶子节点时，Aron 赢得胜利。如果初始时 $p$ 和 $q$ 都是叶子，或经过 $10^{100}$ 回合游戏仍未结束，最终结果为平局。

请统计能让 Aron 赢得游戏的整数对 $(p, q)$ 的数量：$1 \leq p, q \leq n$ 且 $p \neq q$。

*用简单的话来说：当前的毛毛虫序列是 $c_1, c_2, \ldots, c_k$，移动后，新序列变为 $d(u, c_1), d(u, c_2), \ldots, d(u, c_k)$。这里，$d(x, y)$ 表示从 $y$ 到 $x$ 的简单路径上的下一个顶点。

*在树中，一个顶点的度数为1时，该顶点称为叶子节点。

*因此，只要游戏未结束，Nora 总能找到一个顶点 $u$ 来进行移动。Aron 也是一样。

## 输入格式

每个测试组包含多个测试用例。第一行给出一个整数 $t$（$1 \leq t \leq 2 \cdot 10^4$），表示测试用例的数量。接下来是各个测试用例的具体描述。

每个测试用例的第一行包含一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示树中的顶点数。

接下来的 $n - 1$ 行，每行有两个整数 $u$ 和 $v$（$1 \leq u, v \leq n$），表示顶点 $u$ 和 $v$ 之间存在一条边。保证这些边构成了一棵树。

保证所有测试用例中 $n$ 的总和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数，表示能够让 Aron 得胜的整数对 $(p, q)$ 的数量。

## 说明/提示

在第一个测试例中，所有可能的毛毛虫是 $(1, 2)$ 和 $(2, 1)$。由于初始时 $p$ 和 $q$ 都是叶子，因此结果为平局。

在第二个测试例中，满足 Aron 赢得游戏的毛毛虫包括：$(1, 3)$、$(1, 4)$、$(1, 5)$、$(2, 3)$、$(2, 4)$、$(2, 5)$。下面我们来具体分析一些毛毛虫的情况：

- 对于毛毛虫 $(1, 5)$：顶点 $p = 1$ 不是叶子，而 $q = 5$ 是叶子，因此 Aron 在一开始就胜利。
- 对于毛毛虫 $(2, 1)$：顶点 $p = 2$ 不是叶子，$q = 1$ 也不是叶子。在 Nora 的第一次移动中，她可以选择将毛毛虫移向顶点 $5$，此时毛毛虫变为 $(5, 2)$，顶点 $p = 5$ 是叶子，因此 Nora 在下一步中胜利。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
5
1 2
1 3
2 4
2 5
12
1 6
11 2
4 8
12 3
2 7
6 12
8 1
2 3
5 12
9 2
10 3
10
1 2
2 3
3 4
4 5
5 6
4 7
6 8
4 9
4 10
25
1 16
11 22
6 14
3 1
20 14
23 17
25 19
10 11
3 18
10 6
2 21
4 5
11 12
4 9
9 13
8 6
6 1
3 7
8 19
10 24
15 13
1 2
3 4
17 8
```

### 输出

```
0
6
40
27
171
```



---

---
title: "A Lot of Games"
layout: "post"
diff: 普及+/提高
pid: CF455B
tag: ['博弈论', '递归', '进制']
---

# A Lot of Games

## 题目描述

Andrew, Fedor and Alex are inventive guys. Now they invent the game with strings for two players.

Given a group of $ n $ non-empty strings. During the game two players build the word together, initially the word is empty. The players move in turns. On his step player must add a single letter in the end of the word, the resulting word must be prefix of at least one string from the group. A player loses if he cannot move.

Andrew and Alex decided to play this game $ k $ times. The player who is the loser of the $ i $ -th game makes the first move in the $ (i+1) $ -th game. Guys decided that the winner of all games is the player who wins the last ( $ k $ -th) game. Andrew and Alex already started the game. Fedor wants to know who wins the game if both players will play optimally. Help him.

## 输入格式

The first line contains two integers, $ n $ and $ k $ ( $ 1<=n<=10^{5} $ ; $ 1<=k<=10^{9} $ ).

Each of the next $ n $ lines contains a single non-empty string from the given group. The total length of all strings from the group doesn't exceed $ 10^{5} $ . Each string of the group consists only of lowercase English letters.

## 输出格式

If the player who moves first wins, print "First", otherwise print "Second" (without the quotes).

## 样例 #1

### 输入

```
2 3
a
b

```

### 输出

```
First

```

## 样例 #2

### 输入

```
3 1
a
b
c

```

### 输出

```
First

```

## 样例 #3

### 输入

```
1 2
ab

```

### 输出

```
Second

```



---

---
title: "Sweets Game"
layout: "post"
diff: 普及+/提高
pid: CF63E
tag: ['动态规划 DP', '搜索', '博弈论', '记忆化搜索']
---

# Sweets Game

## 题目描述

Karlsson has visited Lillebror again. They found a box of chocolates and a big whipped cream cake at Lillebror's place. Karlsson immediately suggested to divide the sweets fairly between Lillebror and himself. Specifically, to play together a game he has just invented with the chocolates. The winner will get the cake as a reward.

The box of chocolates has the form of a hexagon. It contains 19 cells for the chocolates, some of which contain a chocolate. The players move in turns. During one move it is allowed to eat one or several chocolates that lay in the neighboring cells on one line, parallel to one of the box's sides. The picture below shows the examples of allowed moves and of an unacceptable one. The player who cannot make a move loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)Karlsson makes the first move as he is Lillebror's guest and not vice versa. The players play optimally. Determine who will get the cake.

## 输入格式

The input data contains 5 lines, containing 19 words consisting of one symbol. The word "O" means that the cell contains a chocolate and a "." stands for an empty cell. It is guaranteed that the box contains at least one chocolate. See the examples for better understanding.

## 输出格式

If Karlsson gets the cake, print "Karlsson" (without the quotes), otherwise print "Lillebror" (yet again without the quotes).

## 样例 #1

### 输入

```
  . . .
 . . O .
. . O O .
 . . . .
  . . .

```

### 输出

```
Lillebror
```

## 样例 #2

### 输入

```
  . . .
 . . . O
. . . O .
 O . O .
  . O .

```

### 输出

```
Karlsson
```



---

