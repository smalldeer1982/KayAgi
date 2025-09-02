---
title: "GRAPHGAM - Charlesbert and Merangelou"
layout: "post"
diff: 难度0
pid: SP3108
tag: []
---

# GRAPHGAM - Charlesbert and Merangelou

## 题目描述

Charlesbert 和 Merangelou 正在一个由多个圆圈组成的游戏板上进行双人对抗游戏。板上的每个圆圈可能与其他一些圆圈相连。Charlesbert 使用一枚称为 GoalPiece 的棋子，而 Merangelou 使用一枚称为 ChasePiece 的棋子。

游戏规则如下：游戏开始时，Charlesbert 可选择任何一个圆圈并将 GoalPiece 放在上面，同时，Merangelou 将 ChasePiece 放在第一个圆圈上。在接下来的 K 秒内，Merangelou 每秒可以进行一次移动，移动时可以选择不动，也可以将 ChasePiece 从当前圆圈移动到一个直接相连的圆圈。如果 Merangelou 在 Charlesbert 最后一次移动 GoalPiece 前或刚好在第 K 秒后，将 ChasePiece 移动到与 GoalPiece 相同的圆圈上，则 Merangelou 获胜。否则，Charlesbert 将重新选择一个圆圈放置 GoalPiece，然后 Merangelou 可以再移动 K 次（每次都是在 Charlesbert 移动 GoalPiece 后进行）。这一过程重复进行，直到 ChasePiece 和 GoalPiece 在同一圆圈上。需要注意的是，Merangelou 可能在不到 K 秒内就取得胜利。

Merangelou 希望能尽快赢得比赛，而 Charlesbert 则希望游戏能持续得更久。假设两位玩家都采取最优策略，请确定 Merangelou 确保获胜的最短时间（以秒为单位）。如果 Charlesbert 能够无限期拖延游戏，致使 Merangelou 无法获胜，则输出 "INFINITE GAME"。

## 输入格式

输入的第一行是一个整数 C (0 < C < 100)，表示有多少组测试数据。每组测试数据的第一行包含两个整数 M 和 K (1 < M < 100, 0 < K < 100)，分别表示游戏板上的圆圈数量和 Charlesbert 移动 GoalPiece 之间的秒数。接下来的 M 行，每行有 M 个字符，这些字符为 'Y' 或 'N'。如果第 i 行的第 j 个字符为 'Y'，表示圆圈 i 和圆圈 j 是相连的；反之则不相连。第 i 行的第 j 个字符总是和第 j 行的第 i 个字符相同，并且第 k 行的第 k 个字符总是 'N'。这些 M 行构成了圆圈之间的邻接矩阵。ChasePiece 始终从第一个圆圈开始。

## 输出格式

对于每组测试数据，如果 Merangelou 能够获胜，则输出她获胜所需的最短时间；否则，输出 "INFINITE GAME"。每组结果应单独占一行。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5 1
NNNNY
NNNNY
NNNNY
NNNNY
YYYYN
4 2
NYNN
YNYN
NYNY
NNYN
4 1
NYNY
YNYN
NYNY
YNYN
```

### 输出

```
2
4
INFINITE GAME
```

