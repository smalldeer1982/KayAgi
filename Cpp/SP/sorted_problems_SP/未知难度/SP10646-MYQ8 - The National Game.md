---
title: "MYQ8 - The National Game"
layout: "post"
diff: 难度0
pid: SP10646
tag: []
---

# MYQ8 - The National Game

## 题目描述

Prasanna 和 Nithin 对 Thuvax 的国粹游戏「井字棋」已驾轻就熟。井字棋是一款两人对弈的棋类游戏，玩家 x 和 o 轮流在一个 3 × 3 的网格中用他们的标记 'x' 和 'o' 占据空格。x 玩家先走。任何玩家只要成功将三个相同的标记连成一条横线、竖线或对角线，便可立即获胜，游戏也随之结束。

在井字棋比赛结束归来的路上，Prasanna 和 Nithin 发现一个棋盘已经有了部分标记。他们决定在现有棋盘状态的基础上继续进行游戏。请帮助 Nithin 判断下一个行动的玩家是否会在接下来的回合中获胜、失败或者是否游戏会以平局结束（假设两位玩家都采取最佳策略），或者判断该局面是否无效。

## 输入格式

输入的第一行为整数 $T$，表示测试用例的数量，$1 \le T \le 10^6$。接下来的内容由 $4 \times T$ 行组成。每个测试用例的第一行为一个空行，接下来的三行表示当前棋盘的状态。

## 输出格式

对于每个测试用例，输出一行结果，结果为 `win`（胜利）、`lose`（失败）、`tie`（平局）或 `invalid`（无效状态）。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 \n&nbsp;\noox \n.x. \n..x \n&nbsp;\nxox \nxoo \noxx \n&nbsp;\no.. \n... \n...
```

### 输出

```
lose \ntie \ninvalid\n\nExplanation: \nCase 1: Player x can win by placing x in either last cell of the middle row, or the first cell of the last row. So the next player, o, cant prevent him from winning from this state. \nCase 2: It is completed game, as you can see no one has won. So, it has ended in a tie. \nCase 3: Player x should have started the game. Hence such a state can never be reached.
```

