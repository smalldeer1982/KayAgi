---
title: "DFLOOR - Dance Floor"
layout: "post"
diff: 难度0
pid: SP98
tag: []
---

# DFLOOR - Dance Floor

## 题目描述

 You recently watched a video clip in which a singer danced on a grid of colourful tiles enlightened from below. Each step on a tile flipped the tile's state, i.e. light on or off. In addition to that, all the neighbouring tiles flipped their states, too.   
  
 In this task, you are supposed to come up with a short program that decides if it is possible for the singer to switch on the lights of all the tiles, provided that he dances on the appropriate tiles.   
  
 The dance floor has rectangular shape. At the beginning, some of the tiles are already alight. Your program may temporarily switch off some tiles, if it deems that necessary to reach its goal. Stepping on a tile toggles its own state as well as the states of the four neighbouring tiles directly above, below, to the left and to the right. Of course, in the case of a peripheral tile, there will be only three or two neighbouring tiles.   
  
 Here comes an example:   
![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP98/bf44d1fec142d6d814944a04fb48942c08c4d265.png)  
 If the dancer steps on the tile indicated by the brown shoe, all the tiles within the white area change their states. The resulting dance floor is depicted on the right.   
  
 You may assume that the singer is fit enough to jump from any tile to any other tile, even if the destination tile lies on the opposite side of the dance floor.

## 输入格式

 There are several test cases. The first line of each case contains two integer numbers _x_ and _y_, indicating the width and the height of the dance floor grid. The numbers are separated by a single space and satisfy 3 ≤ _x_,_y_ ≤ 15.   
  
 The following _y_ lines containing _x_characters each describe the initial on/off states of the tiles. A zero means "the tile is switched off", a one digit means "the tile is alight".   
  
Input ends with 0 0.

## 输出格式

 For each test case your program should output the number of steps needed to switch all the lights on, followed by exactly that many lines with two space-separated numbers _i_ and _j_. Each individual line commands the singer to step on the _i_-th tile of the _j_-th row. Starting with the situation of the input file and executing all the commands in the output file, all the tiles must be switched on.   
  
 If more than one solution exist, your program should output an arbitrary one of them. If, on the other hand, no solution exists, your program should write the number "-1".

## 样例 #1

### 输入

```
4 3
0111
1010
1000

0 0
```

### 输出

```
3
1 2
1 3
4 3
```

