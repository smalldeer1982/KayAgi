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



# Obsession with Robots

## 题目描述

整个世界都对机器人着迷，为了跟上时代步伐，伟大的伯兰程序员Draude决定建造自己的机器人。他努力开发机器人，教它走两点之间的最短路径并记录所有移动。但就像Draude的许多程序一样，这个机器人存在一个bug——它并不总是走最短路径。幸运的是，机器人正确记录了所有移动轨迹。现在Draude想知道机器人何时出错。如果他能记住测试场地图，就能轻易判断机器人是否走对了方向。但由于地图丢失，他需要你判断是否存在至少一种可能的地图，使得机器人记录的路径是最短的。

地图是一个无限的方格区域，每个方格可以是空的或包含障碍物。机器人永远不会试图进入障碍物方格。根据记录的移动轨迹，判断是否存在至少一种地图，使得：
1. 存在一个起始空方格，机器人从该点出发时的移动与记录一致（仅在空方格移动，不触碰障碍物）
2. 该路径是从起点到终点的最短路径

每次移动机器人只能进入与当前方格相邻（共享边）的空方格。

---

## 题解综合分析

所有题解均围绕两个核心验证条件：
1. **路径唯一性**：移动轨迹不得重复经过同一坐标（违反BFS最短路径特性）
2. **邻域约束性**：每个新到达点的四周（除上一步来源方向）最多存在0个已访问点

### 最优题解亮点（评分4星以上）

#### 1. 封禁用户（4.5星）
**核心思路**：
- 使用二维数组记录访问状态
- `check()`函数同时验证坐标重复和邻域污染
- 初始化坐标到中心点（101,101）防止负坐标

**关键代码**：
```cpp
bool check(int x_,int y_) {
    if (data[x_][y_]) return true;
    int cnt = 0;
    for (四个方向检查) if (访问过) cnt++;
    return cnt > 1; // 除前一点外还有其他已访问点
}
```
**个人心得**：避免使用`x1/y1`变量名（某些编译器保留名称）

#### 2. Loner_Knowledge（4星）
**优化亮点**：
- 将方向数组与字符映射结合
- 通过紧凑的坐标检查实现高效验证
- 使用返回布尔值的Check函数简化逻辑

**代码亮点**：
```cpp
bool Check(int x,int y) {
    if(mark[x][y]) return true;
    int cnt = 0;
    for(四方向检查) if(mark[相邻坐标]) cnt++;
    return cnt > 1;
}
```

#### 3. cyrxdzj（4星）
**思维模型**：
- 用图形示例解释两种违规情况
- 将邻域检查简化为四方向计数
- 统一使用`graph[x][y]`进行状态标记

**实现技巧**：
```cpp
if(graph[x-1][y] + graph[x+1][y] + graph[x][y-1] + graph[x][y+1] > 1)
    printf("BUG");
```

---

## 关键实现技巧

1. **坐标系初始化**：
```cpp
int x = 101, y = 101; // 在200x200网格中心初始化
```
2. **四方向污染检查**：
```cpp
int cnt = 0;
for(int dx : {-1,1,0,0})
    for(int dy : {0,0,-1,1})
        if(当前方向不是来源方向 && 已访问) cnt++;
```
3. **移动与验证顺序**：
先移动坐标 → 检查新坐标合法性 → 标记访问状态

---

## 同类题目推荐

1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141) - BFS连通块与路径验证
2. [P1126 机器人搬重物](https://www.luogu.com.cn/problem/P1126) - 带转向约束的最短路径
3. [P1512 迷路的机器人](https://www.luogu.com.cn/problem/P1512) - 障碍地图下的路径验证

---

## 调试经验摘录

1. **坐标初始化教训**：
> "初始坐标必须设置在足够大的数组中心，防止移动时越界" —— liaokq

2. **变量命名坑点**：
> "不要用x1/y1，某些编译器会CE，用x_/y_代替" —— 封禁用户

3. **验证顺序关键**：
> "必须在新坐标处先检查再标记，否则会漏判重复" —— Level_Down

---
处理用时：48.57秒