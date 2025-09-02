---
title: "Infinite Maze"
layout: "post"
diff: 普及+/提高
pid: CF196B
tag: []
---

# Infinite Maze

## 题目描述

We've got a rectangular $ n×m $ -cell maze. Each cell is either passable, or is a wall (impassable). A little boy found the maze and cyclically tiled a plane with it so that the plane became an infinite maze. Now on this plane cell $ (x,y) $ is a wall if and only if cell ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF196B/90d712000eb85a8bfa2ea0243ba4ea17c7b21954.png) is a wall.

In this problem ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF196B/8f971526abdeb0e01a924ce3de8c76d38e0d2bfd.png) is a remainder of dividing number $ a $ by number $ b $ .

The little boy stood at some cell on the plane and he wondered whether he can walk infinitely far away from his starting position. From cell $ (x,y) $ he can go to one of the following cells: $ (x,y-1) $ , $ (x,y+1) $ , $ (x-1,y) $ and $ (x+1,y) $ , provided that the cell he goes to is not a wall.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=1500 $ ) — the height and the width of the maze that the boy used to cyclically tile the plane.

Each of the next $ n $ lines contains $ m $ characters — the description of the labyrinth. Each character is either a "\#", that marks a wall, a ".", that marks a passable cell, or an "S", that marks the little boy's starting point.

The starting point is a passable cell. It is guaranteed that character "S" occurs exactly once in the input.

## 输出格式

Print "Yes" (without the quotes), if the little boy can walk infinitely far from the starting point. Otherwise, print "No" (without the quotes).

## 说明/提示

In the first sample the little boy can go up for infinitely long as there is a "clear path" that goes vertically. He just needs to repeat the following steps infinitely: up, up, left, up, up, right, up.

In the second sample the vertical path is blocked. The path to the left doesn't work, too — the next "copy" of the maze traps the boy.

## 样例 #1

### 输入

```
5 4
##.#
##S#
#..#
#.##
#..#

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
5 4
##.#
##S#
#..#
..#.
#.##

```

### 输出

```
No

```

