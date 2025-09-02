---
title: "OMWG - One more weird game "
layout: "post"
diff: 难度0
pid: SP27308
tag: []
---

# OMWG - One more weird game 

## 题目描述

$Leha$ 正在玩一个非常有趣的游戏。游戏将在由 $N$ 行和 $M$ 列组成的矩形网格上进行。最初，网格的所有单元格都是无色的。
$Leha$ 的初始得分为零。在每个回合，他都会选择一些尚未着色的单元格，并为该单元格着色。在此步骤中获得的分数，将是 $Leha$ 在此步骤中着色的单元格的相邻彩色单元格的数量。如果两个单元格之间共享一侧，则它们是彼此的邻居。当所有单元格都着色时，游戏将结束。最后，游戏结束时获得的总分是每回合获得分数的总和。
$Leha$ 想知道他能得到多少分？你能帮他找出答案吗？

## 输入格式

第一行包含一个整数 $T$，表示游戏回合数。接下来 $T$ 行，包含两个以空格分隔的整数 $N$，$M$ 表示网格的尺寸。

## 输出格式

对于每个回合，输出一行，其中包含对应于 $Leha$ 可以获得的最大可能分数的整数。
### 样例解释
$Leha$ 可以通过以下方式获得总分 $4$：

$1$.第一步，他向下着色左侧单元格，该单元格的所有相邻单元格均未着色。
因此，它将总分加 $0$。

$2$.在第二步中，他可以给右上角的单元格着色，这也为分数增加了总分 $0$。

$3$.在第三步中，他可以给左上角的单元格着色。此单元格有两个相邻的单元格，这两个单元格都是彩色的。因此，这增加了 $2$ 分。

$4$.在最后一步中，他可以选择剩余的右下单元格。此单元格有两个相邻的单元格，这两个单元格都是彩色的。因此，这也增加了 $2$ 分。

$Leha$ 不能获得超过4的分数。因此，4 是答案。

## 样例 #1

### 输入

```
1
2 2
```

### 输出

```
4
Explaination
Leha can obtain total score 4 in the following way.

    1. In the first step, he colors down left cell, all the neighboring cells of this cell are uncolored.
        So, it adds 0 to total score.
    2. In second step, he can color upper right cell, it also adds total 0 to the score.
    3. In third step, he can color top left cell. 
        There are two neighboring cell of this cell, both of which are colored. So, this add 2 to the score.
    4. In the last step, he can choose the remaining down right cell. 
        There are two neighboring cell of this cell, both of which are colored. 
        So, this also add 2 to the score.

Leha can't obtain a score more than 4. Hence 4 is the answer.
```

