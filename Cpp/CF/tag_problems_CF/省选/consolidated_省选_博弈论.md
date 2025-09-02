---
title: "Poachers"
layout: "post"
diff: 省选/NOI-
pid: CF1585G
tag: ['博弈论', '树上启发式合并']
---

# Poachers

## 题目描述

Alice and Bob are two poachers who cut trees in a forest.

A forest is a set of zero or more trees. A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a node $ v $ is the next vertex on the shortest path from $ v $ to the root. Children of vertex $ v $ are all nodes for which $ v $ is the parent. A vertex is a leaf if it has no children.

In this problem we define the depth of vertex as number of vertices on the simple path from this vertex to the root. The rank of a tree is the minimum depth among its leaves.

Initially there is a forest of rooted trees. Alice and Bob play a game on this forest. They play alternating turns with Alice going first. At the beginning of their turn, the player chooses a tree from the forest. Then the player chooses a positive cutting depth, which should not exceed the rank of the chosen tree. Then the player removes all vertices of that tree whose depth is less that or equal to the cutting depth. All other vertices of the tree form a set of rooted trees with root being the vertex with the smallest depth before the cut. All these trees are included in the game forest and the game continues.

A player loses if the forest is empty at the beginning of his move.

You are to determine whether Alice wins the game if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 5 \cdot 10^5 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ) — total number of vertices in the initial forest.

The second line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 0 \leq p_i \leq n $ ) — description of the forest. If $ p_i = 0 $ , then the $ i $ -th vertex is the root of a tree, otherwise $ p_i $ is the parent of the vertex $ i $ . It's guaranteed that $ p $ defines a correct forest of rooted trees.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print "YES" (without quotes) if Alice wins, otherwise print "NO" (without quotes). You can print each letter in any case (upper or lower).

## 说明/提示

In the first test case Bob has a symmetric strategy, so Alice cannot win.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/504019013a3bfbf8eb56c8730800a342f1394e57.png)

In the second test case Alice can choose the second tree and cutting depth $ 1 $ to get a forest on which she has a symmetric strategy.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/8fe2d012fa7f86edd6ce3b0992b73d46bc9c4b34.png)

In third test case the rank of the only tree is $ 2 $ and both possible moves for Alice result in a loss. Bob either can make the forest with a symmetric strategy for himself, or clear the forest.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/eed2cbe70e21303a782188eb3bbbd7989634e2f0.png)

In the fourth test case all leafs have the same depth, so Alice can clear the forest in one move.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/095a24a5876a4e208466c20d0a9b949b0c7e2ff3.png)

## 样例 #1

### 输入

```
4
4
0 1 0 3
7
0 1 2 0 4 5 6
4
0 1 1 2
7
0 1 1 2 2 3 3
```

### 输出

```
NO
YES
NO
YES
```



---

---
title: "Colouring Game"
layout: "post"
diff: 省选/NOI-
pid: CF1704F
tag: ['博弈论']
---

# Colouring Game

## 题目描述

Alice and Bob are playing a game. There are $ n $ cells in a row. Initially each cell is either red or blue. Alice goes first.

On each turn, Alice chooses two neighbouring cells which contain at least one red cell, and paints that two cells white. Then, Bob chooses two neighbouring cells which contain at least one blue cell, and paints that two cells white. The player who cannot make a move loses.

Find the winner if both Alice and Bob play optimally.

Note that a chosen cell can be white, as long as the other cell satisfies the constraints.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of test cases follows.

For each test case, the first line contains an integer $ n $ ( $ 2 \leq n \leq 5 \cdot 10^5 $ ) — the number of cells.

The second line contains a string $ s $ of length $ n $ — the initial state of the cells. The $ i $ -th cell is red if $ s_i =  $ R, blue if $ s_i =  $ B.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output the name of the winner on a separate line.

## 说明/提示

In the notes, the cell numbers increase from left to right.

In the first testcase for Alice, she has two choices: paint the first and the second cells, or paint the second and the third cells. No matter what choice Alice makes, there will be exactly one blue cell after Alice's move. Bob just needs to paint the blue cell and its neighbour, then every cell will be white and Alice can't make a move. So Bob is the winner.

In the second testcase no matter what Alice chooses, Bob can choose to paint the fourth and fifth cells in $ 2 $ turns.

In the third testcase at first, Alice paints the third and the fourth cells. It doesn't matter if Bob paints the first and the second cells or the fifth and sixth cells, as Alice can paint the other two cells.

In the fourth testcase at first, Alice paints the second and the third cells. If Bob paints the fifth and the sixth cells or the fourth and the fifth cells, then Alice paints the seventh and the eighth cells. If Bob paints the seventh and the eighth cells, then Alice paints the fifth and the sixth cells.

In the fifth Alice chooses the middle two cells at first, then Bob obviously has only two options, whichever variant he chooses, Alice can choose the other one and win.

In the eighth no matter what Alice chooses, Bob can choose the other two symmetrical cells.

## 样例 #1

### 输入

```
8
3
BRB
5
RRBBB
6
RBRBRB
8
BBRRBRRB
6
BRRBRB
12
RBRBRBRBRRBB
12
RBRBRBRBBBRR
4
RBBR
```

### 输出

```
Bob
Bob
Alice
Alice
Alice
Alice
Bob
Bob
```



---

---
title: "Grid Game 2"
layout: "post"
diff: 省选/NOI-
pid: CF1906G
tag: ['博弈论', '最大公约数 gcd']
---

# Grid Game 2

## 题目描述

You are playing "Grid Game 2" with your friend. There is a grid with $ 10^9 $ rows (numbered from $ 1 $ to $ 10^9 $ ) and $ 10^9 $ columns (numbered from $ 1 $ to $ 10^9 $ ). The cell at row $ r $ and column $ c $ is denoted as $ (r, c) $ .

Each cell can have a colour of either black or white. Initially, there are exactly $ N $ black cells (numbered from $ 1 $ to $ N $ ). Black cell $ i $ is located at $ (R_i, C_i) $ . The rest of the cells are white.

You and your friend will alternately take turn playing on this grid, and you are playing in the first turn. In one turn, a player will choose a black cell $ (r, c) $ , then toggle cells $ (r - x, c - y) $ for all $ 0 \leq x, y < \min(r, c) $ . If a cell is toggled, then the cell becomes black if it was a white cell, and the cell becomes white if it was a black cell.

For example, the following illustration shows how the grid changes after a player chooses a black cell $ (5, 4) $ in their turn.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/e2fd54c73d9615e1033b8dd1a01d70086e6fa600.png)A player who is unable to play on their turn, i.e. no remaining black cells, loses the game, and the opposing player wins the game. If you and your friend are playing optimally, determine who will win the game.

## 输入格式

The first line consists of an integer $ N $ ( $ 1 \le N \le 200\,000 $ ).

Each of the next $ N $ lines consists of two integers $ R_i $ $ C_i $ ( $ 1 \leq R_i, C_i \leq 10^9) $ . For $ 1 \leq i < j \leq N $ , $ (R_i, C_i) \neq (R_j, C_j) $ .

## 输出格式

Output FIRST if you will win the game, or SECOND otherwise.

## 说明/提示

Explanation for the sample input/output #1

You can start your move by choosing $ (2, 4) $ , whose effect was demonstrated in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/2b04f438065762fd04c672bc2aeca49fdf0ed64a.png)The remaining black cells are $ (1, 3) $ and $ (1, 4) $ , each of which will only toggle itself when chosen. Whichever your friend chooses on the next move, the you can choose the remaining black cell.

Explanation for the sample input/output #2

You have only one cell to choose, and will toggle cells $ (1, 1) $ , $ (1, 2) $ , $ (2, 1) $ , and $ (2, 2) $ . Your friend and you will alternately choose the remaining black cells with your friend choosing the last black cell.

## 样例 #1

### 输入

```
2
2 3
2 4
```

### 输出

```
FIRST
```

## 样例 #2

### 输入

```
1
2 2
```

### 输出

```
SECOND
```

## 样例 #3

### 输入

```
13
1 1
1 4
1 5
2 1
2 4
2 5
4 1
4 2
4 4
5 1
5 2
5 4
5 5
```

### 输出

```
SECOND
```



---

---
title: "Bit Game (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2027E1
tag: ['博弈论', 'SG 函数']
---

# Bit Game (Easy Version)

## 题目描述

### 题面
**这是这个问题的简单版本。唯一不同的是，在这个版本中，您需要输出游戏的获胜者，而且每堆棋子的数量是固定的。您必须同时解出这两个版本才能破解**。

爱丽丝和鲍勃正在玩一个熟悉的游戏，他们轮流从 $n$ 堆中取出棋子。最初，在第 $i$ 堆中有 $x_i$ 颗棋子，它的相关值为 $a_i$ 。当且仅当以下两个条件都满足时，棋手才能从第 $i$ 堆中拿走 $d$ 颗棋子：

- $1 \le d \le a_i$ ，以及
- $x \ \&\  d = d$ ，其中 $x$ 是当前第 $i$ 中的棋子数量， $\&$ 表示[位和运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。
 
无法下棋的棋手输棋，爱丽丝先下。

给你每堆棋子的 $a_i$ 和 $x_i$ 值，请判断如果双方都以最佳方式下棋，谁会赢。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 1000$ )。测试用例说明如下。

每个测试用例的第一行包含 $n$ ( $1 \le n \le 10^4$ ) - 堆数。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $1 \le a_i\lt 2^{30}$ )。

每个测试用例的第三行包含 $n$ 个整数 $x_1, x_2, \ldots, x_n$ ( $1 \le x_i\lt 2^{30}$ ) 。

保证所有测试用例中 $n$ 的总和不超过 $10^4$ 。

## 输出格式

打印一行赢家姓名。如果 Alice 获胜，则打印 "Alice"，否则打印 "Bob"(不带引号)。

### 样例解释

在第一个测试案例中，由于没有满足条件的 $d$ 值，两位棋手都无法从第一堆棋子中取出任何棋子。对于第二堆棋子，首先，爱丽丝可以取出 $1$ 和 $6$ 之间的棋子。无论爱丽丝下哪一步棋，鲍勃都可以在他的回合中取出剩下的棋子。在鲍勃下棋之后，爱丽丝再也无法下棋，因此鲍勃获胜。

在第二个测试案例中，下面是游戏可能进行的一个例子。爱丽丝先下棋，她决定从第一堆中取出棋子。她不能取走 $17$ 颗棋子，因为 $17\gt 10$ 不符合第一个条件。她不能取 $10$ 颗棋子，因为 $25 \, \& \, 10 = 8$ 不符合第二个条件。一种选择是取 $9$ 颗棋子；现在这堆棋子还剩下 $16$ 颗。轮到鲍勃时，他决定从第二堆中取石；这里唯一的选择是取走所有的 $4$ 。现在，前两堆棋子都不能再取了，所以爱丽丝必须从最后一堆中取一些棋子。她决定取 $12$ 颗棋子，然后鲍勃紧随其后，取下这堆棋子中的最后一颗 $2$ 颗棋子。由于爱丽丝现在没有合法棋步了，鲍勃获胜。由此可以看出，无论爱丽丝采用哪种策略，只要鲍勃的下法是最优的，他就总是能够获胜。

## 样例 #1

### 输入

```
7
2
1 6
10 7
3
10 8 15
25 4 14
4
8 32 65 64
7 45 126 94
3
20 40 1
23 55 1
5
12345 9876 86419 8641 1
6789 54321 7532 97532 1
2
20 64
44 61
3
57 109 55
69 90 85
```

### 输出

```
Bob
Bob
Bob
Bob
Bob
Alice
Alice
```



---

---
title: "Peanuts"
layout: "post"
diff: 省选/NOI-
pid: CF2032F
tag: ['动态规划 DP', '博弈论']
---

# Peanuts

## 题目描述

Having the magical beanstalk, Jack has been gathering a lot of peanuts lately. Eventually, he has obtained $ n $ pockets of peanuts, conveniently numbered $ 1 $ to $ n $ from left to right. The $ i $ -th pocket has $ a_i $ peanuts.

Jack and his childhood friend Alice decide to play a game around the peanuts. First, Alice divides the pockets into some boxes; each box will have a non-zero number of consecutive pockets, and each pocket will, obviously, belong to exactly one box. At the same time, Alice does not change the order of the boxes, that is, the boxes are numbered in ascending order of the indices of the pockets in them.

After that, Alice and Jack will take turns alternately, with Alice going first.

At each turn, the current player will remove a positive number of peanuts from exactly one pocket which belongs to the leftmost non-empty box (i.e., the leftmost box containing at least one non-empty pocket). In other words, if we number the boxes from left to right, then each player can only pick peanuts from the pocket in the $ j $ -th box ( $ j \ge 2 $ ) only if the $ (j - 1) $ -th box has no peanuts left. The player who cannot make a valid move loses.

Alice is sure she will win since she has the advantage of dividing the pockets into boxes herself. Thus, she wanted to know how many ways there are for her to divide the peanuts into boxes at the start of the game so that she will win, assuming both players play optimally. Can you help her with the calculation?

As the result can be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the number of pockets.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the number of peanuts in each pocket.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the number of ways for Alice to divide the pockets into boxes at the start of the game to guarantee her win, assuming both players play optimally, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the only way for Alice to win is to divide the pockets into two boxes as follows: $ ([1, 2], [3]) $ (the first box contains the first two pockets and the second box contains the third pocket). Alice wins by taking both peanuts from the second pocket, leaving Jack with $ ([1], [3]) $ . Jack is forced to take the only peanut left in the first box, which allows Alice to take the remaining ones in the second box.

In the second test case, the winning divisions for Alice are $ ([1], [2, 3, 1]) $ , $ ([1, 2, 3, 1]) $ , $ ([1, 2], [3], [1]) $ , and $ ([1, 2], [3, 1]) $ .

In the third test case, Alice always wins no matter how she divides the pockets into boxes.

In the fourth test case, Alice always loses no matter how she divides the pockets into boxes.

## 样例 #1

### 输入

```
5
3
1 2 3
4
1 2 3 1
5
1 1 1 1 1
2
1 1
10
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
1
4
16
0
205
```



---

