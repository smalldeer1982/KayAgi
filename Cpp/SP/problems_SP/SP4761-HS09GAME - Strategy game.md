---
title: "HS09GAME - Strategy game"
layout: "post"
diff: 难度0
pid: SP4761
tag: []
---

# HS09GAME - Strategy game

## 题目描述

Julia 和 Robert 玩了一场取木棍的游戏。游戏开始时有 $n$ 堆木棍，第 $i$ 堆里有 $a_i$ 根木棍。每一轮，玩家可以从任意一堆中取出 2、3 或 5 根木棍（取出的木棍不再放回）。Julia 先手。无法继续操作的玩家将输掉比赛，而另一个玩家获胜。请你判断，在双方都采取最佳策略的情况下，谁会赢得游戏。如果 Julia 能获胜，请指出她第一步的最佳操作！如果有多种可能的最佳操作，选择取走最多木棍的方案。如果仍有多个这样的方案，从编号最小的堆中开始取木棍。

## 输入格式

输入包含一个整数 $T$，表示测试用例的数量（$T \leq 1000$）。接下来每个测试用例包含一个整数 $n$，表示堆的数量，接着是 $n$ 个非负整数：$a_1, a_2, \ldots, a_n$，其中 $a_i$ 为第 $i$ 堆木棍的数量。

数据范围：  
1 <= $n$ <= 1000  
0 <= $a_i$ <= 1000000000

## 输出格式

请按照示例的格式输出每个测试用例的结果。每个测试用例的输出后请留下一个空行。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
1
5
1
7
4
1 2 3 4
10
1 2 3 4 5 6 7 8 9 10
2
1000000 1000001
```

### 输出

```
Julia wins.
Take 5 sticks from heap number 1.

Robert wins.

Julia wins.
Take 3 sticks from heap number 4.

Julia wins.
Take 5 sticks from heap number 6.

Julia wins.
Take 5 sticks from heap number 1.
```

