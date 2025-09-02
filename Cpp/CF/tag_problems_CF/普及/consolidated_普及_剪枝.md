---
title: "Labyrinth"
layout: "post"
diff: 普及/提高-
pid: CF1063B
tag: ['搜索', '广度优先搜索 BFS', '剪枝']
---

# Labyrinth

## 题目描述

## 题意描述
你正在玩一款电脑游戏。在其中一关，你位于一个 $n$ 行 $m$ 列的迷宫。每个格子要么是可以通过的空地，要么是障碍。迷宫的起点位于第 $r$ 行第 $c$ 列。你每一步可以向上、下、左、右中的一个方向移动一格，前提是那一格不是障碍。你无法越出迷宫的边界。

不幸的是，你的键盘快坏了，所以你只能向左移动不超过 $x$ 格，并且向右移动不超过 $y$ 格。因为上下键情况良好，所以对向上和向下的移动次数没有限制。

现在你想知道在满足上述条件的情况下，从起点出发，有多少格子可以到达（包括起点）？

## 输入格式

第一行包含两个数 $n, m$ $(1 <= n, m, <= 2000)$ ,表示迷宫的行数和列数。

第二行包含两个数 $r,c$ $(1 <= r <= n, 1 <= c <= m)$ ,表示起点位于第 $r$ 行第 $c$ 列。

第三行包含两个数 $x,y$ $(1 <= x,y <= 10^9)$ ,表示最多向左或向右移动的次数。

接下来 $n$ 行描述这个迷宫，每行为一个长为 $m$ 的由 '.' 和 '\*' 组成的字符串。
'.' 表示空地， '\*' 表示障碍。
输入保证起点不是障碍。

## 输出格式

输出一个整数，表示从起点出发可以到达的格子数，包括起点本身。

## 样例 #1

### 输入

```
4 5
3 2
1 2
.....
.***.
...**
*....

```

### 输出

```
10

```

## 样例 #2

### 输入

```
4 4
2 2
0 1
....
..*.
....
....

```

### 输出

```
7

```



---

---
title: "Phillip and Trains"
layout: "post"
diff: 普及/提高-
pid: CF585B
tag: ['搜索', '深度优先搜索 DFS', '剪枝']
---

# Phillip and Trains

## 题目描述

The mobile application store has a new game called "Subway Roller".

The protagonist of the game Philip is located in one end of the tunnel and wants to get out of the other one. The tunnel is a rectangular field consisting of three rows and $ n $ columns. At the beginning of the game the hero is in some cell of the leftmost column. Some number of trains rides towards the hero. Each train consists of two or more neighbouring cells in some row of the field.

All trains are moving from right to left at a speed of two cells per second, and the hero runs from left to right at the speed of one cell per second. For simplicity, the game is implemented so that the hero and the trains move in turns. First, the hero moves one cell to the right, then one square up or down, or stays idle. Then all the trains move twice simultaneously one cell to the left. Thus, in one move, Philip definitely makes a move to the right and can move up or down. If at any point, Philip is in the same cell with a train, he loses. If the train reaches the left column, it continues to move as before, leaving the tunnel.

Your task is to answer the question whether there is a sequence of movements of Philip, such that he would be able to get to the rightmost column.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF585B/309f950d64c5a7d55f4952aae670b86363abc76b.png)

## 输入格式

Each test contains from one to ten sets of the input data. The first line of the test contains a single integer $ t $ ( $ 1<=t<=10 $ for pretests and tests or $ t=1 $ for hacks; see the Notes section for details) — the number of sets.

Then follows the description of $ t $ sets of the input data.

The first line of the description of each set contains two integers $ n,k $ ( $ 2<=n<=100,1<=k<=26 $ ) — the number of columns on the field and the number of trains. Each of the following three lines contains the sequence of $ n $ character, representing the row of the field where the game is on. Philip's initial position is marked as 's', he is in the leftmost column. Each of the $ k $ trains is marked by some sequence of identical uppercase letters of the English alphabet, located in one line. Distinct trains are represented by distinct letters. Character '.' represents an empty cell, that is, the cell that doesn't contain either Philip or the trains.

## 输出格式

For each set of the input data print on a single line word YES, if it is possible to win the game and word NO otherwise.

## 说明/提示

In the first set of the input of the first sample Philip must first go forward and go down to the third row of the field, then go only forward, then go forward and climb to the second row, go forward again and go up to the first row. After that way no train blocks Philip's path, so he can go straight to the end of the tunnel.

Note that in this problem the challenges are restricted to tests that contain only one testset.

## 样例 #1

### 输入

```
2
16 4
...AAAAA........
s.BBB......CCCCC
........DDDDD...
16 4
...AAAAA........
s.BBB....CCCCC..
.......DDDDD....

```

### 输出

```
YES
NO

```

## 样例 #2

### 输入

```
2
10 4
s.ZZ......
.....AAABB
.YYYYYY...
10 4
s.ZZ......
....AAAABB
.YYYYYY...

```

### 输出

```
YES
NO

```



---

---
title: "Almost Arithmetic Progression"
layout: "post"
diff: 普及/提高-
pid: CF978D
tag: ['搜索', '枚举', '剪枝']
---

# Almost Arithmetic Progression

## 题目描述

Polycarp 喜欢等差数列，对于一个数列 $ [a_1,a_2,a_3,\dots,a_n] $，如果对于每个 $ i\,(1\le i < n) $，$ a_{i+1}-a_i $ 的值均相同，那么这个数列就是一个等差数列。例如，$ [42] $ ，$ [5,5,5] $ ，$ [2,11,20,29] $ 和 $ [3,2,1,0] $ 是等差数列，但是 $ [1,0,1] $，$ [1,3,9] $ 和 $ [2,3,1] $ 不是。

根据定义，任何长度为 $ 1 $ 或 $ 2 $ 的数列都是等差数列。

Polycarp 找到了一个只包含正整数的数列 $ [b_1,b_2,b_3,\dots,b_n] $ 。他只想最多将每个元素改变一次。换句话说，对于每个元素，有三种选项：自增 $ 1 $，自减 $ 1 $ 或者不变。

你需要找到对 $ b $ 中元素操作（每个只能操作一次）的最小次数，使 $ b $ 变成一个等差数列。

操作完成后的数列可以含有 $ 0 $ 。

## 输入格式

第 $ 1 $ 行有 $ 1 $ 个整数 $ n\,(1\le n\le 100\,000) $ ，表示 $ b $ 中元素的个数。

第 $ 2 $ 行包含一个数列 $ b_1,b_2,b_3,\dots,b_n \,(1\le b_i \le 10^9)$。

## 输出格式

如果无法使用上述的操作将数列变为等差数列，输出 $ -1 $ 。在另一种情况下，输出一个非负整数，表示要将 $ b $ 变为等差数列所需要改变的元素的个数。唯一允许的操作是元素的自增 $/$ 减（不能够对一个元素操作两次）。

## 说明/提示

在样例 $ 1 $ 中，Polycarp 应该将第 $ 1 $ 个元素加 $ 1 $ ，将第 $ 2 $ 个元素加 $ 1 $ ，将第 $ 3 $ 个元素加 $ 1 $ ，并且不改变第 $ 4 $ 个元素。所以，Polycarp 操作之后的数列为 $ [25,20,15,10] $ 。

在样例 $ 2 $ 中，Polycarp 不应进行操作，因为他的数列已经是等差数列了。

在样例 $ 3 $ 中，不可能通过上述的操作将数列变为等差数列。

在样例 $ 4 $ 中，Polycarp 应该只将第 $ 1 $ 个元素加 $ 1 $ 。操作之后的数列为 $ [0,3,6,9,12] $ 。

## 样例 #1

### 输入

```
4
24 21 14 10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
500 500

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
14 5 1

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
5
1 3 6 9 12

```

### 输出

```
1

```



---

