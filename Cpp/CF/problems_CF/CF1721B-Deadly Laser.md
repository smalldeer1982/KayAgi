---
title: "Deadly Laser"
layout: "post"
diff: 普及-
pid: CF1721B
tag: ['数学']
---

# Deadly Laser

## 题目描述

# Deadly Laser


The robot is placed in the top left corner of a grid, consisting of $ n $ rows and $ m $ columns, in a cell $ (1, 1) $ .

In one step, it can move into a cell, adjacent by a side to the current one:

- $ (x, y) \rightarrow (x, y + 1) $ ;
- $ (x, y) \rightarrow (x + 1, y) $ ;
- $ (x, y) \rightarrow (x, y - 1) $ ;
- $ (x, y) \rightarrow (x - 1, y) $ .

The robot can't move outside the grid.

The cell $ (s_x, s_y) $ contains a deadly laser. If the robot comes into some cell that has distance less than or equal to $ d $ to the laser, it gets evaporated. The distance between two cells $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ .

Print the smallest number of steps that the robot can take to reach the cell $ (n, m) $ without getting evaporated or moving outside the grid. If it's not possible to reach the cell $ (n, m) $ , print -1.

The laser is neither in the starting cell, nor in the ending cell. The starting cell always has distance greater than $ d $ to the laser.

有一个长$n$宽$m$的网格，一个机器人被放在此网格的左上角$(1,1)$。
每一步，机器人可以移动到与其所在格子相邻的四个格子：
- $(x,y) \rightarrow (x,y+1)$;
- $(x,y) \rightarrow (x+1,y)$;
- $(x,y) \rightarrow (x,y-1)$;
- $(x,y) \rightarrow (x-1,y)$。

机器人不能移出网格。\
在$(s_x,s_y)$处，放置着致命的激光。所有与激光所在格子的距离小于等于$d$的格子都不可通行。（$(x_1,y_1)$到$(x_2,y_2)$的距离为: $|x_1-x_2|+|y_1-y_2|$）\
输出机器人从$(1,1)$移至$(n,m)$的最小步数。如果机器人不能到达$(n,m)$，输出`-1`。

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The only line of each testcase contains five integers $ n, m, s_x, s_y, d $ ( $ 2 \le n, m \le 1000 $ ; $ 1 \le s_x \le n $ ; $ 1 \le s_y \le m $ ; $ 0 \le d \le n + m $ ) — the size of the grid, the cell that contains the laser and the evaporating distance of the laser.

The laser is neither in the starting cell, nor in the ending cell ( $ (s_x, s_y) \neq (1, 1) $ and $ (s_x, s_y) \neq (n, m) $ ). The starting cell $ (1, 1) $ always has distance greater than $ d $ to the laser ( $ |s_x - 1| + |s_y - 1| > d $ ).

第一行为一个整数$t$($1\leq t\leq 10^4$)，代表测试数据的数量。\
对于每一组测试数据，只有一行输入，包含5个整数：$n$, $m$, $s_x$, $s_y$, $d$ ($2\leq n,m\leq 1000$; $1\leq s_x \leq n$; $1\leq s_y \leq m$; $0\leq d\leq n+m$)，其意义与上方相同。\
输入数据保证激光既不在起点的格子，也不在终点的格子；保证起点的格子可以通行。（$(s_x,s_y)\neq(1,1)$; $(s_x,s_y)\neq(n,m)$; $|s_x-1|+|s_y-1|>d$）

## 输出格式

For each testcase, print a single integer. If it's possible to reach the cell $ (n, m) $ from $ (1, 1) $ without getting evaporated or moving outside the grid, then print the smallest amount of steps it can take the robot to reach it. Otherwise, print -1.

# 中文翻译
对于每组测试数据，输出一个整数。如果机器人可以达到终点，输出到达终点所需的最小步数。否则，输出`-1`

## 输入输出样例
### 样例输入
```
3
2 3 1 3 0
2 3 1 3 1
5 5 3 4 1
```
### 样例输出
```
3
-1
8
```

## 样例 #1

### 输入

```
3
2 3 1 3 0
2 3 1 3 1
5 5 3 4 1
```

### 输出

```
3
-1
8
```

