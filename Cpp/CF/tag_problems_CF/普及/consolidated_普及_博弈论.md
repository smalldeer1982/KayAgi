---
title: "Arena of Greed"
layout: "post"
diff: 普及/提高-
pid: CF1425A
tag: ['贪心', '博弈论']
---

# Arena of Greed

## 题目描述

Lately, Mr. Chanek frequently plays the game Arena of Greed. As the name implies, the game's goal is to find the greediest of them all, who will then be crowned king of Compfestnesia.

The game is played by two people taking turns, where Mr. Chanek takes the first turn. Initially, there is a treasure chest containing $ N $ gold coins. The game ends if there are no more gold coins in the chest. In each turn, the players can make one of the following moves:

- Take one gold coin from the chest.
- Take half of the gold coins on the chest. This move is only available if the number of coins in the chest is even.

Both players will try to maximize the number of coins they have. Mr. Chanek asks your help to find the maximum number of coins he can get at the end of the game if both he and the opponent plays optimally.

## 输入格式

The first line contains a single integer $ T $ $ (1 \le T \le 10^5) $ denotes the number of test cases.

The next $ T $ lines each contain a single integer $ N $ $ (1 \le N \le 10^{18}) $ .

## 输出格式

$ T $ lines, each line is the answer requested by Mr. Chanek.

## 说明/提示

For the first case, the game is as follows:

1. Mr. Chanek takes one coin.
2. The opponent takes two coins.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

For the second case, the game is as follows:

1. Mr. Chanek takes three coins.
2. The opponent takes one coin.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

## 样例 #1

### 输入

```
2
5
6
```

### 输出

```
2
4
```



---

---
title: "Swap Game"
layout: "post"
diff: 普及/提高-
pid: CF1747C
tag: ['博弈论']
---

# Swap Game

## 题目描述

Alice and Bob are playing a game on an array $ a $ of $ n $ positive integers. Alice and Bob make alternating moves with Alice going first.

In his/her turn, the player makes the following move:

- If $ a_1 = 0 $ , the player loses the game, otherwise:
- Player chooses some $ i $ with $ 2\le i \le n $ . Then player decreases the value of $ a_1 $ by $ 1 $ and swaps $ a_1 $ with $ a_i $ .

Determine the winner of the game if both players play optimally.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 2 \cdot 10^4) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (2 \leq n \leq 10^5) $ — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2 \ldots a_n $ $ (1 \leq a_i \leq 10^9) $ — the elements of the array $ a $ .

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if Alice will win the game, output "Alice". Otherwise, output "Bob".

You can output each letter in any case. For example, "alIcE", "Alice", "alice" will all be considered identical.

## 说明/提示

In the first testcase, in her turn, Alice can only choose $ i = 2 $ , making the array equal $ [1, 0] $ . Then Bob, in his turn, will also choose $ i = 2 $ and make the array equal $ [0, 0] $ . As $ a_1 = 0 $ , Alice loses.

In the second testcase, once again, players can only choose $ i = 2 $ . Then the array will change as follows: $ [2, 1] \to [1, 1] \to [1, 0] \to [0, 0] $ , and Bob loses.

In the third testcase, we can show that Alice has a winning strategy.

## 样例 #1

### 输入

```
3
2
1 1
2
2 1
3
5 4 4
```

### 输出

```
Bob
Alice
Alice
```



---

---
title: "Game with Marbles (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1914E1
tag: ['贪心', '博弈论']
---

# Game with Marbles (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the easy version, the number of test cases does not exceed $ 10^3 $ , and $ n $ does not exceed $ 6 $ .

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains a single integer $ n $ ( $ 2 \le n \le 6 $ ) — the number of colors;
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of marbles of the $ i $ -th color that Alice has;
- the third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ), where $ b_i $ is the number of marbles of the $ i $ -th color that Bob has.

## 输出格式

For each test case, output a single integer — the score at the end of the game if both Alice and Bob act optimally.

## 说明/提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5
```

### 输出

```
1
-9
2999999997
8
-6
```



---

---
title: "Game with Marbles (Hard Version)"
layout: "post"
diff: 普及/提高-
pid: CF1914E2
tag: ['贪心', '博弈论']
---

# Game with Marbles (Hard Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the hard version, the number of test cases does not exceed $ 10^4 $ , and the sum of values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Furthermore, there are no additional constraints on $ n $ in a single test case.

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of colors;
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of marbles of the $ i $ -th color that Alice has;
- the third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ), where $ b_i $ is the number of marbles of the $ i $ -th color that Bob has.

Additional constraint on the input: the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the score at the end of the game if both Alice and Bob act optimally.

## 说明/提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5
```

### 输出

```
1
-9
2999999997
8
-6
```



---

---
title: "Training Before the Olympiad"
layout: "post"
diff: 普及/提高-
pid: CF1916C
tag: ['博弈论']
---

# Training Before the Olympiad

## 题目描述

Masha and Olya have an important team olympiad coming up soon. In honor of this, Masha, for warm-up, suggested playing a game with Olya:

There is an array $ a $ of size $ n $ . Masha goes first, and the players take turns. Each move is described by the following sequence of actions:

 $ \bullet $ If the size of the array is $ 1 $ , the game ends.

 $ \bullet $ The player who is currently playing chooses two different indices $ i $ , $ j $ ( $ 1 \le i, j \le |a| $ ), and performs the following operation — removes $ a_i $ and $ a_j $ from the array and adds to the array a number equal to $ \lfloor \frac{a_i + a_j}{2} \rfloor \cdot 2 $ . In other words, first divides the sum of the numbers $ a_i $ , $ a_j $ by $ 2 $ rounding down, and then multiplies the result by $ 2 $ .

Masha aims to maximize the final number, while Olya aims to minimize it.

Masha and Olya decided to play on each non-empty prefix of the initial array $ a $ , and asked for your help.

For each $ k = 1, 2, \ldots, n $ , answer the following question. Let only the first $ k $ elements of the array $ a $ be present in the game, with indices $ 1, 2, \ldots, k $ respectively. What number will remain at the end with optimal play by both players?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array.

The second line contains $ n $ integers $ a_1,a_2, \ldots,a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the array on which Masha and Olya play.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ integers. The $ k $ -th of these numbers should be equal to the number that will remain at the end with optimal play by both players, on the array consisting of the first $ k $ elements of the array $ a $ .

## 说明/提示

In the third test case, for a prefix of length $ 1 $ , the answer is $ 3 $ . For a prefix of length $ 2 $ , Masha has only one move, so the answer is $ 12 $ . For a prefix of length $ 3 $ , Masha has three possible moves: she chooses $ 3 $ and $ 10 $ , then the final number is $ 22 $ , $ 3 $ and $ 11 $ , then the final number is $ 24 $ , $ 10 $ and $ 11 $ , then the final number is $ 22 $ , so Masha will choose $ 3 $ and $ 11 $ and get $ 24 $ .

## 样例 #1

### 输入

```
4
1
31
6
6 3 7 2 5 4
3
3 10 11
5
7 13 11 19 1
```

### 输出

```
31 
6 8 16 18 22 26 
3 12 24 
7 20 30 48 50
```



---

---
title: "Eat the Chip"
layout: "post"
diff: 普及/提高-
pid: CF1921E
tag: ['博弈论']
---

# Eat the Chip

## 题目描述

Alice and Bob are playing a game on a checkered board. The board has $ h $ rows, numbered from top to bottom, and $ w $ columns, numbered from left to right. Both players have a chip each. Initially, Alice's chip is located at the cell with coordinates $ (x_a, y_a) $ (row $ x_a $ , column $ y_a $ ), and Bob's chip is located at $ (x_b, y_b) $ . It is guaranteed that the initial positions of the chips do not coincide. Players take turns making moves, with Alice starting.

On her turn, Alice can move her chip one cell down or one cell down-right or down-left (diagonally). Bob, on the other hand, moves his chip one cell up, up-right, or up-left. It is not allowed to make moves that go beyond the board boundaries.

More formally, if at the beginning of Alice's turn she is in the cell with coordinates $ (x_a, y_a) $ , then she can move her chip to one of the cells $ (x_a + 1, y_a) $ , $ (x_a + 1, y_a - 1) $ , or $ (x_a + 1, y_a + 1) $ . Bob, on his turn, from the cell $ (x_b, y_b) $ can move to $ (x_b - 1, y_b) $ , $ (x_b - 1, y_b - 1) $ , or $ (x_b - 1, y_b + 1) $ . The new chip coordinates $ (x', y') $ must satisfy the conditions $ 1 \le x' \le h $ and $ 1 \le y' \le w $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921E/132ee8f6414f793fc5ccbac975e03978861ca953.png) Example game state. Alice plays with the white chip, Bob with the black one. Arrows indicate possible moves. A player immediately wins if they place their chip in a cell occupied by the other player's chip. If either player cannot make a move (Alice—if she is in the last row, i.e. $ x_a = h $ , Bob—if he is in the first row, i.e. $ x_b = 1 $ ), the game immediately ends in a draw.

What will be the outcome of the game if both opponents play optimally?

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. This is followed by the description of the test cases.

Each test case consists of a single line containing six integers $ h $ , $ w $ , $ x_a $ , $ y_a $ , $ x_b $ , $ y_b $ ( $ 1 \le x_a, x_b \le h \le 10^6 $ , $ 1 \le y_a, y_b \le w \le 10^9 $ ) — the dimensions of the board and the initial positions of Alice's and Bob's chips. It is guaranteed that either $ x_a \ne x_b $ or $ y_a \ne y_b $ .

It is guaranteed that the sum of $ h $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output "Alice" if Alice wins, "Bob" if Bob wins, and "Draw" if neither player can secure a victory. You can output each letter in any case (lowercase or uppercase). For example, the strings "bOb", "bob", "Bob", and "BOB" will be accepted as Bob's victory.

## 样例 #1

### 输入

```
12
6 5 2 2 5 3
4 1 2 1 4 1
1 4 1 3 1 1
5 5 1 4 5 2
4 4 1 1 4 4
10 10 1 6 10 8
10 10 2 6 10 7
10 10 9 1 8 1
10 10 8 1 10 2
10 10 1 1 2 1
10 10 1 3 4 1
10 10 3 1 1 1
```

### 输出

```
Alice
Bob
Draw
Draw
Draw
Alice
Draw
Draw
Bob
Alice
Alice
Draw
```



---

---
title: "Everything Nim"
layout: "post"
diff: 普及/提高-
pid: CF1965A
tag: ['贪心', '博弈论']
---

# Everything Nim

## 题目描述

Alice 和 Bob 在用 $n\ (n\le2\times10^5 ) $ 堆石子做游戏。在其中一位玩家的回合里，他可以选择一个不超过当前所有**非空**堆中石子数量**最小值**的**正整数** $ k$，并从目前所有非空堆中移除 $k$ 颗石子。当一名玩家在他的回合中无法进行操作时（此时所有石子堆都是空的），即判为负。

现在给出 $n$ 堆石子的初始石子数，已知 Alice 先手且两人都足够聪明，请你判断最后谁会获胜。

---

## 输入格式

输入包含多组数据。

第一行一个整数 $T\ (T\le10^4 ) $，表示输入数据组数。

对于每组数据，第一行包含一个整数 $n\ (n\le2\times10^5 ) $，表示石子堆数；第二行包含 $n$ 个整数 $a_{1\sim n}\ (a_i\le10^9 ) $，表示第 $i$ 堆石子的数量。

题目保证对于单个测试点的所有数据，满足 $\sum n\le2\times10^5$。

---

## 输出格式

对于每组测试数据，输出一行一个字符串，表示胜者的名字。如 Alice 获胜则输出 `Alice`，否则输出 `Bob`。

## 样例 #1

### 输入

```
7
5
3 3 3 3 3
2
1 7
7
1 3 9 7 4 2 100
3
1 2 3
6
2 1 3 4 2 4
8
5 7 2 9 6 3 3 2
1
1000000000
```

### 输出

```
Alice
Bob
Alice
Alice
Bob
Alice
Alice
```



---

---
title: "Game on Tree (Easy)"
layout: "post"
diff: 普及/提高-
pid: CF1970C1
tag: ['博弈论']
---

# Game on Tree (Easy)

## 题目描述

This is the easy version of the problem. The difference in this version is that $ t=1 $ and we work on an array-like tree.

Ron and Hermione are playing a game on a tree of $ n $ nodes that are initially inactive. This tree is special because it has exactly two leaves. It can thus be seen as an array. The game consists of $ t $ rounds, each of which starts with a stone on exactly one node, which is considered as activated. A move consists of picking an inactive neighbor of the node with a stone on it and moving the stone there (thus activating this neighbor). Ron makes the first move, after which he alternates with Hermione until no valid move is available. The player that cannot make a move loses the round. If both players play optimally, who wins each round of this game?

Note that all the rounds are played with the same tree; only the starting node changes. Moreover, after each round, all active nodes are considered inactive again.

## 输入格式

The first line contains integers $ n $ ( $ 2 \leq n \leq 2\times 10^5 $ ), $ t $ ( $ t=1 $ ), the number of nodes in the tree and the number of rounds, respectively.

The next $ n-1 $ lines contain two integers $ 1 \leq u, v \leq n $ each, corresponding to an edge of the tree. It is guaranteed that the tree has exactly two leaves.

The next line contains $ t $ integers $ 1 \leq u_1 , \dots, u_t \leq n $ , corresponding to the node where the stone is initially put.

## 输出格式

The output consists of $ t=1 $ line which is either "Ron" or "Hermione".

## 样例 #1

### 输入

```
3 1
2 3
3 1
3
```

### 输出

```
Ron
```

## 样例 #2

### 输入

```
5 1
1 2
2 3
3 4
4 5
5
```

### 输出

```
Hermione
```



---

---
title: "Board Game"
layout: "post"
diff: 普及/提高-
pid: CF533C
tag: ['博弈论']
---

# Board Game

## 题目描述

Polycarp and Vasiliy love simple logical games. Today they play a game with infinite chessboard and one pawn for each player. Polycarp and Vasiliy move in turns, Polycarp starts. In each turn Polycarp can move his pawn from cell $ (x,y) $ to $ (x-1,y) $ or $ (x,y-1) $ . Vasiliy can move his pawn from $ (x,y) $ to one of cells: $ (x-1,y),(x-1,y-1) $ and $ (x,y-1) $ . Both players are also allowed to skip move.

There are some additional restrictions — a player is forbidden to move his pawn to a cell with negative $ x $ -coordinate or $ y $ -coordinate or to the cell containing opponent's pawn The winner is the first person to reach cell $ (0,0) $ .

You are given the starting coordinates of both pawns. Determine who will win if both of them play optimally well.

## 输入格式

The first line contains four integers: $ x_{p},y_{p},x_{v},y_{v} $ ( $ 0<=x_{p},y_{p},x_{v},y_{v}<=10^{5}) $ — Polycarp's and Vasiliy's starting coordinates.

It is guaranteed that in the beginning the pawns are in different cells and none of them is in the cell $ (0,0) $ .

## 输出格式

Output the name of the winner: "Polycarp" or "Vasiliy".

## 说明/提示

In the first sample test Polycarp starts in $ (2,1) $ and will move to $ (1,1) $ in the first turn. No matter what his opponent is doing, in the second turn Polycarp can move to $ (1,0) $ and finally to $ (0,0) $ in the third turn.

## 样例 #1

### 输入

```
2 1 2 2

```

### 输出

```
Polycarp

```

## 样例 #2

### 输入

```
4 7 7 4

```

### 输出

```
Vasiliy

```



---

