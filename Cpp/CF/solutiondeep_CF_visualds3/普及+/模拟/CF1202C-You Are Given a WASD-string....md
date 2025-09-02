# 题目信息

# You Are Given a WASD-string...

## 题目描述

You have a string $ s $ — a sequence of commands for your toy robot. The robot is placed in some cell of a rectangular grid. He can perform four commands:

- 'W' — move one cell up;
- 'S' — move one cell down;
- 'A' — move one cell left;
- 'D' — move one cell right.

Let $ Grid(s) $ be the grid of minimum possible area such that there is a position in the grid where you can place the robot in such a way that it will not fall from the grid while running the sequence of commands $ s $ . For example, if $ s = \text{DSAWWAW} $ then $ Grid(s) $ is the $ 4 \times 3 $ grid:

1. you can place the robot in the cell $ (3, 2) $ ;
2. the robot performs the command 'D' and moves to $ (3, 3) $ ;
3. the robot performs the command 'S' and moves to $ (4, 3) $ ;
4. the robot performs the command 'A' and moves to $ (4, 2) $ ;
5. the robot performs the command 'W' and moves to $ (3, 2) $ ;
6. the robot performs the command 'W' and moves to $ (2, 2) $ ;
7. the robot performs the command 'A' and moves to $ (2, 1) $ ;
8. the robot performs the command 'W' and moves to $ (1, 1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1202C/14db41d91dc6fffe218fcbada16fff9a7890d775.png)You have $ 4 $ extra letters: one 'W', one 'A', one 'S', one 'D'. You'd like to insert at most one of these letters in any position of sequence $ s $ to minimize the area of $ Grid(s) $ .

What is the minimum area of $ Grid(s) $ you can achieve?

## 说明/提示

In the first query you have to get string $ \text{DSAWW}\underline{D}\text{AW} $ .

In second and third queries you can not decrease the area of $ Grid(s) $ .

## 样例 #1

### 输入

```
3
DSAWWAW
D
WA
```

### 输出

```
8
2
4
```

# AI分析结果



---
处理用时：203.62秒