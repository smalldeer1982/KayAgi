# 题目信息

# Obsession with Robots

## 题目描述

The whole world got obsessed with robots,and to keep pace with the progress, great Berland's programmer Draude decided to build his own robot. He was working hard at the robot. He taught it to walk the shortest path from one point to another, to record all its movements, but like in many Draude's programs, there was a bug — the robot didn't always walk the shortest path. Fortunately, the robot recorded its own movements correctly. Now Draude wants to find out when his robot functions wrong. Heh, if Draude only remembered the map of the field, where he tested the robot, he would easily say if the robot walked in the right direction or not. But the field map was lost never to be found, that's why he asks you to find out if there exist at least one map, where the path recorded by the robot is the shortest.

The map is an infinite checkered field, where each square is either empty, or contains an obstruction. It is also known that the robot never tries to run into the obstruction. By the recorded robot's movements find out if there exist at least one such map, that it is possible to choose for the robot a starting square (the starting square should be empty) such that when the robot moves from this square its movements coincide with the recorded ones (the robot doesn't run into anything, moving along empty squares only), and the path from the starting square to the end one is the shortest.

In one movement the robot can move into the square (providing there are no obstrutions in this square) that has common sides with the square the robot is currently in.

## 样例 #1

### 输入

```
LLUUUR
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
RRUULLDD
```

### 输出

```
BUG
```

# AI分析结果

### 题目内容重写

#### 题目描述

整个世界都对机器人着迷，为了跟上时代的步伐，伟大的Berland程序员Draude决定建造自己的机器人。他努力地工作，教会了机器人从一个点到另一个点走最短路径，并记录下所有的移动。然而，像Draude的许多程序一样，这个机器人也有一个bug——它并不总是走最短路径。幸运的是，机器人正确地记录了自己的移动。现在Draude想要找出机器人何时出错。如果Draude还记得他测试机器人时的地图，他就能轻松判断机器人是否走对了方向。但地图丢失了，再也找不到了，所以他请你帮忙判断是否存在至少一张地图，使得机器人记录的路径是最短的。

地图是一个无限的方格区域，每个方格要么是空的，要么包含一个障碍物。已知机器人从不试图撞上障碍物。通过记录的机器人移动，判断是否存在至少一张这样的地图，使得可以为机器人选择一个起始方格（起始方格应该是空的），这样当机器人从这个方格移动时，它的移动与记录的移动一致（机器人不会撞上任何东西，只沿着空的方格移动），并且从起始方格到终点方格的路径是最短的。

在一次移动中，机器人可以移动到与当前方格相邻的方格（前提是该方格没有障碍物）。

### 样例 #1

#### 输入

```
LLUUUR
```

#### 输出

```
OK
```

### 样例 #2

#### 输入

```
RRUULLDD
```

#### 输出

```
BUG
```

---

### 题解分析与结论

#### 综合分析

该题的核心是判断机器人记录的路径是否可能是最短路径。所有题解都基于以下两个关键条件进行判断：

1. **路径不能重复经过同一个点**：如果机器人重复经过某个点，那么路径肯定不是最短的。
2. **路径不能绕路**：如果机器人到达某个点时，除了刚经过的点，周围还有其他点已经被访问过，那么路径肯定不是最短的。

大多数题解都采用了模拟机器人移动的方式，通过记录访问过的点，并在每一步移动时检查上述两个条件。如果发现路径不满足最短路径的条件，则输出`BUG`，否则输出`OK`。

#### 最优思路与技巧

1. **模拟移动与标记**：通过模拟机器人的移动，记录每一步的位置，并标记访问过的点。
2. **条件检查**：在每一步移动时，检查当前点是否被访问过，以及周围点是否被访问过（除了刚经过的点）。
3. **初始化与边界处理**：为了避免负数坐标，通常将起点设置在数组的中间位置（如`(101, 101)`），并确保数组足够大以防止越界。

#### 推荐题解

1. **作者：封禁用户 (赞：14)**  
   - **星级**：5星  
   - **关键亮点**：代码清晰，逻辑严谨，详细解释了每一步的判断条件，且代码可读性高。  
   - **核心代码**：
     ```cpp
     inline bool check(int x_,int y_) {
         if (data[x_][y_]) return true;
         int tot=0;
         for (int i=0; i<4; i++) {
             int dx=fx[i]+x;
             int dy=fy[i]+y;
             if (data[dx][dy]) tot++;
         }
         return tot>1;
     }
     ```
   - **个人心得**：作者强调了不要使用`x1`和`y1`作为变量名，否则会编译错误。

2. **作者：Loner_Knowledge (赞：8)**  
   - **星级**：4星  
   - **关键亮点**：代码简洁，逻辑清晰，使用了方向数组来简化移动操作。  
   - **核心代码**：
     ```cpp
     bool Check(int x,int y) {
         if(mark[x][y]) return 1;
         int cnt=0;
         for(int k=0;k<4;++k) {
             int i=x+Const[0][k];
             int j=y+Const[1][k];
             if(mark[i][j]) ++cnt;
         }
         return cnt>1;
     }
     ```

3. **作者：cyrxdzj (赞：4)**  
   - **星级**：4星  
   - **关键亮点**：详细解释了两种不满足最短路径的情况，并通过图示帮助理解。  
   - **核心代码**：
     ```cpp
     if(graph[x][y]) {
         printf("BUG\n");
         return 0;
     }
     if(graph[x-1][y]+graph[x+1][y]+graph[x][y-1]+graph[x][y+1]>1) {
         printf("BUG\n");
         return 0;
     }
     ```

---

### 推荐题目

1. **P1141 01迷宫**：考察最短路径与广度优先搜索（BFS）的应用。
2. **P1443 马的遍历**：涉及最短路径与BFS，适合练习路径模拟与条件判断。
3. **P1162 填涂颜色**：考察路径搜索与条件判断，适合巩固类似题型的解题思路。

---
处理用时：35.21秒