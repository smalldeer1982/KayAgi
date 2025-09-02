---
title: "Purple Crayon"
layout: "post"
diff: 省选/NOI-
pid: CF1615E
tag: []
---

# Purple Crayon

## 题目描述

Two players, Red and Blue, are at it again, and this time they're playing with crayons! The mischievous duo is now vandalizing a rooted tree, by coloring the nodes while playing their favorite game.

The game works as follows: there is a tree of size $ n $ , rooted at node $ 1 $ , where each node is initially white. Red and Blue get one turn each. Red goes first.

In Red's turn, he can do the following operation any number of times:

- Pick any subtree of the rooted tree, and color every node in the subtree red.

 However, to make the game fair, Red is only allowed to color $ k $ nodes of the tree. In other words, after Red's turn, at most $ k $ of the nodes can be colored red.Then, it's Blue's turn. Blue can do the following operation any number of times:

- Pick any subtree of the rooted tree, and color every node in the subtree blue. However, he's not allowed to choose a subtree that contains a node already colored red, as that would make the node purple and no one likes purple crayon.

 Note: there's no restriction on the number of nodes Blue can color, as long as he doesn't color a node that Red has already colored.After the two turns, the score of the game is determined as follows: let $ w $ be the number of white nodes, $ r $ be the number of red nodes, and $ b $ be the number of blue nodes. The score of the game is $ w \cdot (r - b) $ .

Red wants to maximize this score, and Blue wants to minimize it. If both players play optimally, what will the final score of the game be?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 1 \le k \le n $ ) — the number of vertices in the tree and the maximum number of red nodes.

Next $ n - 1 $ lines contains description of edges. The $ i $ -th line contains two space separated integers $ u_i $ and $ v_i $ ( $ 1 \le u_i, v_i \le n $ ; $ u_i \neq v_i $ ) — the $ i $ -th edge of the tree.

It's guaranteed that given edges form a tree.

## 输出格式

Print one integer — the resulting score if both Red and Blue play optimally.

## 说明/提示

In the first test case, the optimal strategy is as follows:

- Red chooses to color the subtrees of nodes $ 2 $ and $ 3 $ .
- Blue chooses to color the subtree of node $ 4 $ .

 At the end of this process, nodes $ 2 $ and $ 3 $ are red, node $ 4 $ is blue, and node $ 1 $ is white. The score of the game is $ 1 \cdot (2 - 1) = 1 $ .In the second test case, the optimal strategy is as follows:

- Red chooses to color the subtree of node $ 4 $ . This colors both nodes $ 4 $ and $ 5 $ .
- Blue does not have any options, so nothing is colored blue.

 At the end of this process, nodes $ 4 $ and $ 5 $ are red, and nodes $ 1 $ , $ 2 $ and $ 3 $ are white. The score of the game is $ 3 \cdot (2 - 0) = 6 $ .For the third test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1615E/4f1ce64388408bbdd02cef561a7e83cee70927f0.png)The score of the game is $ 4 \cdot (2 - 1) = 4 $ .

## 样例 #1

### 输入

```
4 2
1 2
1 3
1 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 2
1 2
2 3
3 4
4 5
```

### 输出

```
6
```

## 样例 #3

### 输入

```
7 2
1 2
1 3
4 2
3 5
6 3
6 7
```

### 输出

```
4
```

## 样例 #4

### 输入

```
4 1
1 2
1 3
1 4
```

### 输出

```
-1
```

