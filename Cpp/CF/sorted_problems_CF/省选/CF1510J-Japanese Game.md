---
title: "Japanese Game"
layout: "post"
diff: 省选/NOI-
pid: CF1510J
tag: []
---

# Japanese Game

## 题目描述

Joseph really likes the culture of Japan. Last year he learned Japanese traditional clothes and visual arts and now he is trying to find out the secret of the Japanese game called Nonogram.

In the one-dimensional version of the game, there is a row of $ n $ empty cells, some of which are to be filled with a pen. There is a description of a solution called a profile — a sequence of positive integers denoting the lengths of consecutive sets of filled cells. For example, the profile of $ [4, 3, 1] $ means that there are sets of four, three, and one filled cell, in that order, with at least one empty cell between successive sets.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/00e502cee5b1e7dd59d45d59dc6659a6a0146886.png)A suitable solution for $ n = 12 $ and $ p = [4, 3, 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/16bbe71feae06df40c8df421f6ec72b82b435ae1.png)A wrong solution: the first four filled cells should be consecutive.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/25f6dcf6154fe32ad9548fdf4a5f7e89e3b49fc5.png)A wrong solution: there should be at least one empty cell before the last filled cell.

Joseph found out that for some numbers $ n $ and profiles $ p $ there are lots of ways to fill the cells to satisfy the profile. Now he is in the process of solving a nonogram consisting of $ n $ cells and a profile $ p $ . He has already created a mask of $ p $ — he has filled all the cells that must be filled in every solution of the nonogram.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/c808943bd3773423d6c30a389b313c56fa04b926.png)The mask for $ n = 12 $ and $ p = [4, 3, 1] $ : all the filled cells above are filled in every solution.

After a break, he lost the source profile $ p $ . He only has $ n $ and the mask $ m $ . Help Joseph find any profile $ p' $ with the mask $ m $ or say that there is no such profile and Joseph has made a mistake.

## 输入格式

The only line contains a string $ m $ — the mask of the source profile $ p $ . The length of $ m $ is $ n $ ( $ 1 \le n \le 100\,000 $ ). The string $ m $ consists of symbols \# and \_ — denoting filled and empty cells respectively.

## 输出格式

If there is no profile with the mask $ m $ , output the number $ -1 $ . Otherwise, on the first line, output an integer $ k $ — the number of integers in the profile $ p' $ . On the second line, output $ k $ integers of the profile $ p' $ .

## 说明/提示

**【题目描述】**

Joseph 特别喜欢日本文化。去年他学习了日本传统服装和日本艺术，但是现在他正在寻找日本拼图（一种日本传统游戏）的秘密。

在此游戏的一维版本上，连续 $n$ 个方格排成一排。Joseph 需要将一些格子涂黑。Joseph 还会得到一个数组 $p$。例如，若 $p = [4,3,1]$，则 Joseph 需要涂 $3$ 个区块，长度分别为 $4,3,1$，他们彼此不能相连，这是例子的一种正确涂色方法：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/00e502cee5b1e7dd59d45d59dc6659a6a0146886.png)

但下面两种是错误的：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/16bbe71feae06df40c8df421f6ec72b82b435ae1.png)

原因：前四个格子没有相连。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/25f6dcf6154fe32ad9548fdf4a5f7e89e3b49fc5.png)

原因：长度为 $3$ 的区块和长度为 $1$ 的区块连上了。

Joseph 发现，对于某些 $n$ 和 $p$，有不止一种方法完成日本拼图游戏，但是不论有多少种方法，有一些格子是必须涂色的，他现在正在将这些格子涂色。

例如，当 $n = 12$、$p = [4,3,1]$ 时，下图黑色的格子是必须涂色的：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1510J/c808943bd3773423d6c30a389b313c56fa04b926.png)

Joseph 将这张图叫做 $m$。

但是在 Joseph 歇了一会后，他忘记了刚刚的 $p$ 数组，他现在只有 $n$ 和 $m$ 图。帮 Joseph 找到任意一种符合 $m$ 图涂色方块的 $p'$ 数组吧！如果没有符合的 $p'$ 数组，请输出 $-1$。

**【输入格式】**

输入共 $1$ 行：

第 $1$ 行，一个字符串 $m$，表示 $m$ 图，黑色的格子用 `#` 表示，其他格子用 `_` 表示。

**【输出格式】**

若没有符合要求的 $p'$ 数组，输出 $-1$。

否则输出共 $2$ 行：

第 $1$ 行，一个整数 $k$，表示找到的 $p'$ 数组的长度。

第 $2$ 行，输出 $k$ 个整数 $a_1, a_2, \cdots, a_k$，$a_i$ 表示数组 $p'$ 的第 $i$ 项。

**【样例】**

输入 #1：

```
__#_____
```

输出 #1：

```
2
3 2
```

输入 #2：

```
_#
```

输出 #2：

```
-1
```

输入 #3：

```
___
```

输出 #3：

```
0
```

**【数据范围】**

$|m| = n$。

$1 \le n \le 10^5$。

翻译贡献者 @[六八七十二](/user/341353)

## 样例 #1

### 输入

```
__#_____
```

### 输出

```
2
3 2
```

## 样例 #2

### 输入

```
_#
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
___
```

### 输出

```
0
```

