---
title: "NPC2014A - I Ken Bit Yu"
layout: "post"
diff: 难度0
pid: SP21456
tag: []
---

# NPC2014A - I Ken Bit Yu

## 题目描述

### 题意翻译

有$N$堆硬币，两个人玩游戏，每人每次可以选择一堆硬币，从中取出一些(取出的硬币数量必须是取之前这堆硬币个数的因数)，比如：现在这堆硬币有6个，则你可以拿走1或2或3个。

当一个人没有任何硬币可以取，他就输了。

两个人Puguh，Joke玩这个游戏，如果Puguh先拿,最后谁是赢家？

## 输入格式

**本题有多组数据。**

第一行，一个整数$T$，表示数据组数。

对于每组数据：

第一行，一个整数$N$，表示硬币的堆数。

接下来$N$行，每行一个整数$X_i$，表示第i堆硬币的数量。

## 输出格式

对于每组数据：

输出一行，一个字符串。如果Puguh是最终赢家，输出`Puguh is the bestest player in teh wurld`。否则输出`Joke is the bestest player in teh wurld`。

