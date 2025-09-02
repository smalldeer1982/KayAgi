---
title: "Sleepy Game"
layout: "post"
diff: 提高+/省选-
pid: CF936B
tag: []
---

# Sleepy Game

## 题目描述

Petya and Vasya arranged a game. The game runs by the following rules. Players have a directed graph consisting of $ n $ vertices and $ m $ edges. One of the vertices contains a chip. Initially the chip is located at vertex $ s $ . Players take turns moving the chip along some edge of the graph. Petya goes first. Player who can't move the chip loses. If the game lasts for $ 10^{6} $ turns the draw is announced.

Vasya was performing big laboratory work in "Spelling and parts of speech" at night before the game, so he fell asleep at the very beginning of the game. Petya decided to take the advantage of this situation and make both Petya's and Vasya's moves.

Your task is to help Petya find out if he can win the game or at least draw a tie.

## 输入格式

The first line of input contain two integers $ n $ and $ m $ — the number of vertices and the number of edges in the graph ( $ 2<=n<=10^{5} $ , $ 0<=m<=2·10^{5} $ ).

The next $ n $ lines contain the information about edges of the graph. $ i $ -th line ( $ 1<=i<=n $ ) contains nonnegative integer $ c_{i} $ — number of vertices such that there is an edge from $ i $ to these vertices and $ c_{i} $ distinct integers $ a_{i,j} $ — indices of these vertices ( $ 1<=a_{i,j}<=n $ , $ a_{i,j}≠i $ ).

It is guaranteed that the total sum of $ c_{i} $ equals to $ m $ .

The next line contains index of vertex $ s $ — the initial position of the chip ( $ 1<=s<=n $ ).

## 输出格式

If Petya can win print «Win» in the first line. In the next line print numbers $ v_{1},v_{2},...,v_{k} $ ( $ 1<=k<=10^{6} $ ) — the sequence of vertices Petya should visit for the winning. Vertex $ v_{1} $ should coincide with $ s $ . For $ i=1...\ k-1 $ there should be an edge from $ v_{i} $ to $ v_{i+1} $ in the graph. There must be no possible move from vertex $ v_{k} $ . The sequence should be such that Petya wins the game.

If Petya can't win but can draw a tie, print «Draw» in the only line. Otherwise print «Lose».

## 说明/提示

In the first example the graph is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936B/933142db306dc9f63dae26cdeb8c3bafdfa66ba8.png)Initially the chip is located at vertex $ 1 $ . In the first move Petya moves the chip to vertex $ 2 $ , after that he moves it to vertex $ 4 $ for Vasya. After that he moves to vertex $ 5 $ . Now it is Vasya's turn and there is no possible move, so Petya wins.

In the second example the graph is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936B/8e2fea186d4a4262837a056dce297e786dfbf02f.png)Initially the chip is located at vertex $ 2 $ . The only possible Petya's move is to go to vertex $ 1 $ . After that he has to go to $ 3 $ for Vasya. Now it's Petya's turn but he has no possible move, so Petya loses.

In the third example the graph is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936B/100651d77b5f87ec828b8f8f5fba499fe3f37744.png)Petya can't win, but he can move along the cycle, so the players will draw a tie.

## 样例 #1

### 输入

```
5 6
2 2 3
2 4 5
1 4
1 5
0
1

```

### 输出

```
Win
1 2 4 5 

```

## 样例 #2

### 输入

```
3 2
1 3
1 1
0
2

```

### 输出

```
Lose

```

## 样例 #3

### 输入

```
2 2
1 2
1 1
1

```

### 输出

```
Draw

```

