---
title: "Levko and Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF360E
tag: []
---

# Levko and Game

## 题目描述

Levko loves sports pathfinding competitions in his city very much. In order to boost his performance, Levko spends his spare time practicing. The practice is a game.

The city consists of $ n $ intersections connected by $ m+k $ directed roads. Two or more roads can connect the same pair of intersections. Besides, there can be roads leading from an intersection to itself.

Levko and Zenyk are playing a game. First Levko stands on intersection $ s_{1} $ , and Zenyk stands on intersection $ s_{2} $ . They both want to get to intersection $ f $ . The person who does it quicker wins. If they get there at the same time, the game ends with a draw. By agreement both players start simultaneously and move with the same speed.

Levko wants to win very much. He knows the lengths of all the roads in the city. Also he knows that he can change the lengths of some roads (there are $ k $ such roads at all) if he pays the government. So, the government can change the length of the $ i $ -th road to any integer value in the segment \[ $ l_{i} $ , $ r_{i} $ \] (both borders inclusive). Levko wondered if he can reconstruct the roads so as to win the game and whether he can hope for the draw if he cannot win.

You should consider that both players play optimally well. It is guaranteed that we can get from intersections $ s_{1} $ and $ s_{2} $ to intersection $ f $ .

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1<=n,m<=10^{4} $ , $ 1<=k<=100 $ ). The second line contains three integers $ s_{1} $ , $ s_{2} $ and $ f $ ( $ 1<=s_{1},s_{2},f<=n $ ).

The next $ m $ lines contains the descriptions of the roads that cannot be changed by Levko. Each line contains three integers $ a_{i} $ , $ b_{i} $ and $ c_{i} $ ( $ 1<=a_{i},b_{i}<=n,1<=c_{i}<=10^{9} $ ), representing a road from intersection $ a_{i} $ to intersection $ b_{i} $ of length $ c_{i} $ .

The next $ k $ lines contains the descriptions of the roads that can be changed by Levko. Each line contains four integers $ a_{i} $ , $ b_{i} $ , $ l_{i} $ and $ r_{i} $ ( $ 1<=a_{i},b_{i}<=n,1<=l_{i}<=r_{i}<=10^{9} $ ), representing a road from intersection $ a_{i} $ to intersection $ b_{i} $ , Levko can set the road's length within limits $ [l_{i},r_{i}] $ .

Consider all intersections numbered from 1 to $ n $ . It is guaranteed that you can get from intersections $ s_{1} $ and $ s_{2} $ to intersection $ f $ .

## 输出格式

In the first line print string "WIN" (without the quotes) if Levko can win this game, string "DRAW" (without the quotes) if Levko can end the game with a draw and "LOSE" (without the quotes) if he loses for sure.

If the answer is "WIN" or "DRAW", then print on the second line $ k $ space-separated integers — the length of the roads Levko sets in the order they occur in the input.

## 样例 #1

### 输入

```
4 1 3
1 3 4
3 2 2
1 2 1 3
2 4 1 3
3 4 1 3

```

### 输出

```
WIN
1 1 3 
```

## 样例 #2

### 输入

```
4 1 3
1 3 4
3 2 2
1 2 1 3
2 4 1 3
3 4 1 2

```

### 输出

```
DRAW
1 1 2 
```

## 样例 #3

### 输入

```
5 4 2
1 2 5
1 3 3
1 4 4
2 3 2
2 4 3
3 5 1 5
4 5 4 7

```

### 输出

```
LOSE

```

