# 题目信息

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

## 样例 #1

### 输入

```
3
2 3 1 3 0
2 3 1 3 1
5 5 3 4 1```

### 输出

```
3
-1
8```

# AI分析结果

### 题目内容中文重写

有一个长$n$宽$m$的网格，一个机器人被放在此网格的左上角$(1,1)$。每一步，机器人可以移动到与其所在格子相邻的四个格子：
- $(x,y) \rightarrow (x,y+1)$;
- $(x,y) \rightarrow (x+1,y)$;
- $(x,y) \rightarrow (x,y-1)$;
- $(x,y) \rightarrow (x-1,y)$。

机器人不能移出网格。在$(s_x,s_y)$处，放置着致命的激光。所有与激光所在格子的距离小于等于$d$的格子都不可通行。（$(x_1,y_1)$到$(x_2,y_2)$的距离为: $|x_1-x_2|+|y_1-y_2|$）输出机器人从$(1,1)$移至$(n,m)$的最小步数。如果机器人不能到达$(n,m)$，输出`-1`。

### 题解综合分析与结论

本题的核心在于判断机器人是否能够从起点$(1,1)$到达终点$(n,m)$，且路径上不经过激光的影响范围。由于激光的影响范围是曼哈顿距离，因此可以通过分类讨论来判断是否存在可行路径。大多数题解都采用了类似的思路，即通过判断激光是否完全阻断了起点到终点的路径来决定输出`-1`或$n+m-2$。

### 评分较高的题解

#### 1. 作者：wimg6_ (评分：4星)
**关键亮点**：通过五种情况判断是否输出`-1`，思路清晰，代码简洁。
**代码实现**：
```cpp
if
(
    cal(sx,sy,n,m)<=d ||
    (sx-d<=1 && sx+d>=n) ||
    (sy-d<=1 && sy+d>=m) ||
    (sx-d<=1 && sy-d<=1) ||
    (sx+d>=n && sy+d>=m)
)
    printf("-1\n");
else printf("%d\n",n+m-2);
```
**核心思想**：通过判断激光是否完全阻断了起点到终点的路径来决定输出`-1`或$n+m-2$。

#### 2. 作者：xiaomuyun (评分：4星)
**关键亮点**：通过判断激光是否阻断了两条可能的路径来决定输出`-1`或$n+m-2$，思路清晰。
**代码实现**：
```cpp
if((sx-1<=d||m-sy<=d)&&(sy-1<=d||n-sx<=d)) printf("-1\n");
else printf("%d\n",n+m-2);
```
**核心思想**：通过判断激光是否阻断了从左上角到右上角或从左下角到右下角的路径来决定输出`-1`或$n+m-2$。

#### 3. 作者：Dry_ice (评分：4星)
**关键亮点**：通过四种情况判断是否输出`-1`，思路清晰，代码简洁。
**代码实现**：
```cpp
if (sx - d <= 1 && sy - d <= 1 ||
    sx + d >= n && sy + d >= m ||
    sx - d <= 1 && sx + d >= n ||
    sy - d <= 1 && sy + d >= m) puts("-1");
else printf("%d\n", n + m - 2);
```
**核心思想**：通过判断激光是否完全阻断了起点到终点的路径来决定输出`-1`或$n+m-2$。

### 最优关键思路或技巧

1. **分类讨论**：通过判断激光是否完全阻断了起点到终点的路径来决定输出`-1`或$n+m-2$。
2. **曼哈顿距离**：利用曼哈顿距离来判断激光的影响范围。
3. **路径选择**：机器人只能向右或向下移动，因此最短路径长度为$n+m-2$。

### 可拓展之处

1. **多激光点**：如果题目中有多个激光点，可能需要更复杂的判断逻辑。
2. **不同距离定义**：如果距离定义不同（如欧几里得距离），可能需要不同的判断方法。

### 推荐题目

1. **洛谷P1141 01迷宫**：考察路径搜索与障碍物处理。
2. **洛谷P1162 填涂颜色**：考察网格图的处理与路径判断。
3. **洛谷P1443 马的遍历**：考察网格图中的最短路径问题。

### 个人心得摘录

1. **调试经历**：部分题解提到通过打表观察规律，发现激光的影响范围是辐射状的，从而简化了判断逻辑。
2. **踩坑教训**：部分题解提到赛时只判了横向纵向拦截而没有判断别的，导致WA，提醒大家考虑要全面。
3. **顿悟感想**：通过分类讨论，发现只要判断激光是否完全阻断了起点到终点的路径，就能快速得出答案。

---
处理用时：40.61秒