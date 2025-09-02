---
title: "WONKA1 - Wonkas Oompa-Impa Dilemma"
layout: "post"
diff: 难度0
pid: SP6885
tag: []
---

# WONKA1 - Wonkas Oompa-Impa Dilemma

## 题目描述

威利·旺卡，这位传奇的巧克力制造商，眼下面临一个严重的问题。他的工厂里所有的工人都是奥姆帕·卢姆帕人，而这个群体的人数正在急剧减少。这一趋势最初是由于测试新产品时发生意外导致的，而后随着年龄的增长，问题变得更加严峻。由于奥姆帕·卢姆帕人全是男性，他们无法通过自我繁衍来填补人员的减少。

为了改变这种状况，威利·旺卡再次踏上了前往未被探索的卢姆帕兰的旅程，意在为奥姆帕·卢姆帕人寻找妻子。这次，他找到了伊帕·林帕人——一个正在寻找丈夫的文明女性部落。这是否就意味着问题已经解决了呢？其实不然。因为这些女性相较于野蛮的奥姆帕·卢姆帕人，已经接受了逻辑与智慧的力量，她们不会贸然同意婚嫁。为了考验奥姆帕·卢姆帕人的智力，伊帕·林帕人为他们设计了一个任务。

在卢姆帕兰的中心，一个完全平坦的场地上，他们竖起了两根彼此相对的图腾柱。其中一根属于伊帕·林帕人，另一根属于奥姆帕·卢姆帕人。

![](../../../content/programmer111:Diagram1.png "初始设置")

任务的目标是：根据图腾柱每秒下降角度的速度，确定两个图腾柱被推倒的时间间隔，使它们的顶部在停止运动时准确相碰。威利·旺卡了解，图腾柱最初的角度不会影响它倒下的方向，倒下的方向完全由推动方式决定（通常应朝向对方的图腾柱）。无论如何，我们可以假设一旦两个顶点接触，所有运动都会立即停止，重力对这个问题并没有影响。

![](../../../content/programmer111:Diagram2.png "期望结果")

伊帕·林帕人表现出一定的慷慨，提供了一个二维坐标系下的图腾柱设置图给奥姆帕·卢姆帕人，但他们也在其中小施手段，对图进行了某一种角度的旋转，这让看起来本应平坦的场地可能显得倾斜。由于奥姆帕·卢姆帕人大多比较原始，威利·旺卡对他们解决这个任务的能力并不抱希望。自己尝试解决后，由于数学技能欠佳，他只能寄希望于你——那位被他启发成长为程序员的小朋友，请务必帮他解决这个难题！威利·旺卡将给你6个关键的信息，包括：$H_1$ 和 $H_2$（图腾柱顶部的坐标），$B_1$ 和 $B_2$（图腾柱底部的坐标），以及 $A_1$ 和 $A_2$（每个图腾柱每秒下降的角度）。为你的童年英雄，为了不让威利失望，无论如何都要完成这个任务。

## 输入格式

第一行包含一个整数 $T$（$1 \leq T \leq 10000$），表示接下来的测试用例数量。

接下来的 $T$ 行中，每行包含 4 个点坐标 $(x, y)$：分别是 $H_1$、$B_1$、$H_2$ 和 $B_2$（$-50000 \leq x, y \leq 50000$），以及两个实数 $A_1$ 和 $A_2$（$0 < A_1, A_2 \leq 90$），表示每个图腾柱每秒下降的角度。

## 输出格式

输出一个实数 $S$（四舍五入到小数点后三位），$S$ 表示两个图腾柱在被推倒后，它们在空中停留的时间差的绝对值，直到图腾柱的顶部接触从而停止运动。如果这种情况永远无法实现（例如，图腾柱在倒下之前未能碰到对方），则输出 "-1"。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n3\n0 5 0 0 6 5 6 0 1 1 \n-1 6 -4 5 -1 3 -2 1 0.5 0.25\n4 -1 3 -1 4 -5 3 -5 12 10.6\n&nbsp;\n&nbsp;\n
```

### 输出

```
\n0.000\n61.087\n-1\n\n\nInput Explanation:\nCASE 1:\n\nH1 Coordinates: (0,5)\nB1 Coordinates: (0,0)\nH2 Coordinates: (6,5)\nB2 Coordinates: (6,0)\nA1 Ratio : 1 degree drop per 1 second (clockwise, in this case)\nA2 Ratio : 1 degree drop per 1 second (counter-clockwise, in this case)\n\nCASE 2:\n\nH1 Coordinates: (-1,6)\nB1 Coordinates: (-4,5)\nH2 Coordinates: (-1,3)\nB2 Coordinates: (-2,1)\nA1 Ratio : 0.5 degree drop per 1 second \nA2 Ratio : 0.25 degree drop per 1 second\n\nCASE 3:\n\nH1 Coordinates: (4,-1)\nB1 Coordinates: (3,-1)\nH2 Coordinates: (4,-5)\nB2 Coordinates: (3,-5)\nA1 Ratio : 12 degree drop per 1 second \nA2 Ratio : 10.6 degree drop per 1 second\n\n\nOutput Explanation:\n\nCASE 1:   It takes both totem poles the exact same amount of time to reach the point \nwhere their tops hit each other. The difference as expressed through S is thus 0.\n\nCASE 2:   For the tops of the totem poles to meet, one totem pole must be pushed \napproximately 61.087 seconds before the other.\n\nCASE 3:   The tops of the totem poles will never meet, so you must print "-1" as shown. \n\n\nHint: \n\nPencil and Paper is the way to go! \n\n\n\n\n\n\n\n
```

