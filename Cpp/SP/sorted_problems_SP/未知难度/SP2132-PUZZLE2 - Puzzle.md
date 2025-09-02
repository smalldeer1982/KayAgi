---
title: "PUZZLE2 - Puzzle"
layout: "post"
diff: 难度0
pid: SP2132
tag: []
---

# PUZZLE2 - Puzzle

## 题目描述

Sam loves all kinds of puzzles. Recently he received a very special puzzle - a grid of N x M squares, each square is occupied either by a red or by a blue pebble. The puzzle is controlled by several buttons.

Each row of the grid has its corresponding black button. When you press a black button, a complicated mechanism of the puzzle flips the colors of all pebbles in the row corresponding to that button (all red pebbles in this row become blue and vice versa).

Each column of the grid has its corresponding white button. When you press exactly two white buttons simultaneously, the puzzle mechanism exchanges the contents of the two columns corresponding to those buttons without changing the order of the pebbles in the columns.

Sam has found the puzzle very interesting. Unfortunately, he lent it to his daughter Ann yesterday. She was able to understand the idea of the puzzle very quickly and she gave him this teasing task. She drew two arrangements - initial and final and she changed the colors of the pebbles according to the initial arrangement. Sam's task is to decide whether there exists a sequence of puzzle operations which transforms the initial arrangement of the puzzle to the final arrangement.

## 样例 #1

### 输入

```
file:
2
3 4
BLUE RED BLUE RED
RED BLUE BLUE RED
BLUE BLUE BLUE BLUE

BLUE RED BLUE RED
RED RED BLUE BLUE
BLUE BLUE BLUE BLUE
2 2
BLUE BLUE
BLUE RED

RED RED
RED RED
```

### 输出

```
file 
YES
NO
```

