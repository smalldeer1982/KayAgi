---
title: "Maze"
layout: "post"
diff: 普及/提高-
pid: CF377A
tag: ['深度优先搜索 DFS', '栈']
---

# Maze

## 题目描述

Pavel loves grid mazes. A grid maze is an $ n×m $ rectangle maze where each cell is either empty, or is a wall. You can go from one cell to another only if both cells are empty and have a common side.

Pavel drew a grid maze with all empty cells forming a connected area. That is, you can go from any empty cell to any other one. Pavel doesn't like it when his maze has too little walls. He wants to turn exactly $ k $ empty cells into walls so that all the remaining cells still formed a connected area. Help him.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m<=500 $ , $ 0<=k&lt;s $ ), where $ n $ and $ m $ are the maze's height and width, correspondingly, $ k $ is the number of walls Pavel wants to add and letter $ s $ represents the number of empty cells in the original maze.

Each of the next $ n $ lines contains $ m $ characters. They describe the original maze. If a character on a line equals ".", then the corresponding cell is empty and if the character equals "\#", then the cell is a wall.

## 输出格式

Print $ n $ lines containing $ m $ characters each: the new maze that fits Pavel's requirements. Mark the empty cells that you transformed into walls as "X", the other cells must be left without changes (that is, "." and "\#").

It is guaranteed that a solution exists. If there are multiple solutions you can output any of them.

## 样例 #1

### 输入

```
3 4 2
#..#
..#.
#...

```

### 输出

```
#.X#
X.#.
#...

```

## 样例 #2

### 输入

```
5 4 5
#...
#.#.
.#..
...#
.#.#

```

### 输出

```
#XXX
#X#.
X#..
...#
.#.#

```

