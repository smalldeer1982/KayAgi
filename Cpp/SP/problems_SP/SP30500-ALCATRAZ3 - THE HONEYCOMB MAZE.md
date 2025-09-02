---
title: "ALCATRAZ3 - THE HONEYCOMB MAZE"
layout: "post"
diff: 难度0
pid: SP30500
tag: []
---

# ALCATRAZ3 - THE HONEYCOMB MAZE

## 题目描述

你获得了去香港迪士尼乐园的幸运门票，并与 "Taarak Mehta ka Ulta Chasma" 家庭一同前去游玩。然而，Subramaniam Iyer 困在了蜂巢迷宫中。他身边只有一部手机，没有他人可以帮忙。他打电话给你，希望你能帮他找到出路。让我们聚焦于问题本身：迷宫由 $N \times M$ 的蜂巢块组成，你会得到一个起始点。你的任务是帮助 Iyer 先生判断他能否通过迷宫返回到起始位置。需要满足的条件是，每个蜂巢块只能访问一次，而且在返回起点之前至少要移动 $k$ 步。「.」表示可以走的块，而「*」表示无法访问的块。从某个位置 $(x, y)$ 上，Iyer 只能向 $(x-1, y)$、$(x+1, y)$、$(x, y+1)$ 或 $(x, y-1)$ 移动。请帮助 Iyer 先生顺利返回起始位置。

## 输入格式

第一行输入 $N \times M$，代表迷宫的尺寸。

第二行输入整数 $k$，即返回之前需要至少走的步数。

第三行输入起始点的坐标 $(1-n, 1-m)$。

接下来 $N$ 行，每行描述了对应行的迷宫布局。

## 输出格式

如果 Iyer 可以按要求返回起点，输出 `YES`；否则输出 `NO`。

## 数据范围

$1 \le N, M \le 100$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 5
14
1 2
. . . * *
* . . . *
* . . . .
. * . . .
. * . . *
```

### 输出

```
YES\n\n&nbsp;Explanation of the test case :\n1,2 - 2,2 - 3,2 - 3,3 - 4,3 - 5,3 - 5,4 - 4,4 - 4,5 - 3,5 - 3,4 - 2,4 - 2,3 - 1,3 - 1,2 \n\n14 moves were made ( No. of dashes ( - )) .\nSo , its possible . Also , no blocks were repeated . \n
```

