---
title: "BALLSAG - Ball Stacking Again"
layout: "post"
diff: 普及/提高-
pid: SP10581
tag: []
---

# BALLSAG - Ball Stacking Again

## 题目描述

XYZ 电视台推出一个新的游戏节目，其中参赛者需要通过做出选择来赢取奖品。游戏设有一堆球叠放成三角形，每个球上都有一个整数值，如下图所示：

![](http://maratona.ic.unicamp.br/~ivan/escola_de_verao_2012/images/ball_stacking_again.png)

参赛者需要选择一个球，他的奖品即为所选球及其上所有直接位于其上的球的值之和。请注意，奖品也可能为负数！

你的朋友即将参加该节目，他希望你能为他编写一个程序，以帮助他计算出可以赢取的最大奖品。

## 输入格式

每组测试数据由多行组成。第一行是一个整数 $N$，表示堆叠的行数（$0 < N < 1001$）。接下来的 $N$ 行中，第 $i$ 行包含 $i$ 个整数 $B_{ij}$（$-1000 \le B_{ij} \le 1000$，其中 $1 \le j \le i \le N$）；$B_{ij}$ 是指在第 $i$ 行中位置为第 $j$ 的球的值（第一行从上算起，而每行的第一个球是最左边的）。每组测试数据的结尾会有一行空行。最后的测试数据后有一行仅包含一个数字零。

## 输出格式

对于每组测试数据，输出一行，表示参赛者可以通过选择某一球而获得的最大奖品值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2\n-2\n1 -10\n\n3\n1\n-5 3\n6 -4 1\n0\n\n
```

### 输出

```
-1\n5\n\nNote:\nOn the first test case, the optimal solution is to take the ball with value 1, making you remove the ball\nwith value -2, resulting in -1.\nOn the second test case the best option is to take the ball with value 1 on the bottom row, resulting in\n1+3+1 = 5. \n
```

