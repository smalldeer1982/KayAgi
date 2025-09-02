---
title: "Robot on the Board 1"
layout: "post"
diff: 普及+/提高
pid: CF1607E
tag: []
---

# Robot on the Board 1

## 题目描述

The robot is located on a checkered rectangular board of size $ n \times m $ ( $ n $ rows, $ m $ columns). The rows in the board are numbered from $ 1 $ to $ n $ from top to bottom, and the columns — from $ 1 $ to $ m $ from left to right.

The robot is able to move from the current cell to one of the four cells adjacent by side.

The sequence of commands $ s $ executed by the robot is given. Each command is denoted by one of the symbols 'L', 'R', 'D' or 'U', and triggers the movement to left, right, down or up, respectively.

The robot can start its movement in any cell. The robot executes the commands starting from the first one, strictly in the order in which they are listed in $ s $ . If the robot moves beyond the edge of the board, it falls and breaks. A command that causes the robot to break is not considered successfully executed.

The robot's task is to execute as many commands as possible without falling off the board. For example, on board $ 3 \times 3 $ , if the robot starts a sequence of actions $ s= $ "RRDLUU" ("right", "right", "down", "left", "up", "up") from the central cell, the robot will perform one command, then the next command will force him to cross the edge. If the robot starts moving from the cell $ (2, 1) $ (second row, first column) then all commands will be executed successfully and the robot will stop at the cell $ (1, 2) $ (first row, second column).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1607E/e9041329204b86a5b243e3524c9fedaa23a2383e.png)The robot starts from cell $ (2, 1) $ (second row, first column). It moves right, right, down, left, up, and up. In this case it ends in the cell $ (1, 2) $ (first row, second column).Determine the cell from which the robot should start its movement in order to execute as many commands as possible.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The next $ 2t $ lines contain descriptions of the test cases.

In the description of each test case, the first line contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 10^6 $ ) — the height and width of the field that the robot is located on. The second line of the description is a string $ s $ consisting solely of characters 'L', 'R', 'D' and 'U' — the sequence of commands the robot executes. The string has a length from $ 1 $ to $ 10^6 $ commands.

It is guaranteed that the total length of $ s $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

Print $ t $ lines, each of which contains the answer to the corresponding test case. The answer to the test case are two integers $ r $ ( $ 1 \leq r \leq n $ ) and $ c $ ( $ 1 \leq c \leq m $ ), separated by a space — the coordinates of the cell (row number and column number) from which the robot should start moving to perform as many commands as possible.

If there are several such cells, you may output any of them.

## 样例 #1

### 输入

```
4
1 1
L
1 2
L
3 3
RRDLUU
4 3
LUURRDDLLLUU
```

### 输出

```
1 1
1 2
2 1
3 2
```

