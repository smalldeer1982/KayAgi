---
title: "The Game (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2062E2
tag: []
---

# The Game (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, you need to find all possible nodes Cirno may choose. You can hack only if you solved all versions of this problem.

Cirno and Daiyousei are playing a game with a tree $ ^{\text{∗}} $ of $ n $ nodes, rooted at node $ 1 $ . The value of the $ i $ -th node is $ w_i $ . They take turns to play the game; Cirno goes first.

In each turn, assuming the opponent chooses $ j $ in the last turn, the player can choose any remaining node $ i $ satisfying $ w_i>w_j $ and delete the subtree $ ^{\text{†}} $ of node $ i $ . In particular, Cirno can choose any node and delete its subtree in the first turn.

The first player who can not operate wins, and they all hope to win. Find all possible nodes Cirno may choose in the first turn so that she wins if both of them play optimally.

 $ ^{\text{∗}} $ A tree is a connected graph without cycles.

 $ ^{\text{†}} $ Node $ u $ is considered in the subtree of node $ i $ if any path from $ 1 $ to $ u $ must go through $ i $ .

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of input test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 4\cdot 10^5 $ ) — the number of nodes in the tree.

The second line contains $ n $ integers $ w_1,w_2,\ldots,w_n $ ( $ 1 \le w_i \le n $ ) — the value of each node.

The next $ n-1 $ lines contain the edges of the tree. The $ i $ -th line contains two integers $ u_i,v_i $ ( $ 1\le u_i,v_i \le n $ , $ u_i \neq v_i $ ) — an edge connecting $ u_i $ and $ v_i $ . It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 4\cdot 10^5 $ .

## 输出格式

For each test case, print one line.

If Cirno wins the game, print several integers. The first integer $ k $ represents the number of possible nodes she may choose in the first turn. The other $ k $ integers are all possible nodes in increasing order.

Otherwise, print "0" (without quotes).

## 说明/提示

In the first test case:

1. If Cirno chooses $ 1 $ or $ 3 $ in the first turn, Daiyousei cannot make a move, so Daiyousei wins.
2. If Cirno chooses $ 2 $ or $ 4 $ in the first turn, Daiyousei can only choose $ 3 $ , but after it Cirno cannot make a move, so Cirno wins.

Therefore, all possible nodes Cirno may choose are $ 2 $ and $ 4 $ .

In the second test case, regardless of which node Cirno chooses, Daiyousei cannot make a move, so Daiyousei wins.

In the third and fourth test case, the only possible node Cirno may choose in the first turn is $ 2 $ .

In the fifth test case, all possible nodes Cirno may choose in the first turn are $ 3,4,6,7 $ and $ 10 $ .

## 样例 #1

### 输入

```
5
4
2 2 4 3
1 2
1 3
2 4
5
1 2 3 4 5
1 2
2 3
3 4
4 5
3
1 2 3
1 2
1 3
5
3 1 3 4 5
1 2
2 3
3 4
4 5
10
1 2 3 2 4 3 3 4 4 3
1 4
4 6
7 4
6 9
6 5
7 8
1 2
2 3
2 10
```

### 输出

```
2 2 4
0
1 2
1 2
5 3 4 6 7 10
```

