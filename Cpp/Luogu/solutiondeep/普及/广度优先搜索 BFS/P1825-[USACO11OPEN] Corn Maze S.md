# 题目信息

# [USACO11OPEN] Corn Maze S

## 题目描述

This past fall, Farmer John took the cows to visit a corn maze. But this wasn't just any corn maze: it featured several gravity-powered teleporter slides, which cause cows to teleport instantly from one point in the maze to another. The slides work in both directions: a cow can slide from the slide's start to the end instantly, or from the end to the start. If a cow steps on a space that hosts either end of a slide, she must use the slide.

The outside of the corn maze is entirely corn except for a single exit.

The maze can be represented by an N x M (2 <= N <= 300; 2 <= M <= 300) grid. Each grid element contains one of these items:

\* Corn (corn grid elements are impassable) 

\* Grass (easy to pass through!) 

\* A slide endpoint (which will transport a cow to the other endpoint) 

\* The exit

A cow can only move from one space to the next if they are adjacent and neither contains corn. Each grassy space has four potential neighbors to which a cow can travel. It takes 1 unit of time to move from a grassy space to an adjacent space; it takes 0 units of time to move from one slide endpoint to the other.

Corn-filled spaces are denoted with an octothorpe (#). Grassy spaces are denoted with a period (.). Pairs of slide endpoints are denoted with the same uppercase letter (A-Z), and no two different slides have endpoints denoted with the same letter. The exit is denoted with the equals sign (=).

Bessie got lost. She knows where she is on the grid, and marked her current grassy space with the 'at' symbol (@). What is the minimum time she needs to move to the exit space?


## 说明/提示

例如以下矩阵，$N=5,M=6$。

```plain
###=##
#.W.##
#.####
#.@W##
######
```

唯一的一个装置的结点用大写字母 $\tt{W}$ 表示。

最优方案为：先向右走到装置的结点，花费一个单位时间，再到装置的另一个结点上，花费 $0$ 个单位时间，然后再向右走一个，再向上走一个，到达出口处，总共花费了 $3$ 个单位时间。

## 样例 #1

### 输入

```
5 6
###=##
#.W.##
#.####
#.@W##
######
```

### 输出

```
3```

# AI分析结果

### 综合分析与结论

本题的核心是通过BFS（广度优先搜索）来寻找从起点到终点的最短路径，难点在于如何处理传送门。传送门的特点是强制传送，且传送时间为0，因此需要在BFS中对传送门进行特殊处理。大多数题解通过预处理传送门的位置，并在BFS中直接跳转到对应的传送门位置，避免了重复计算。部分题解还使用了双向BFS或SPFA等优化算法，但整体思路相似。

### 所选高星题解

#### 1. 作者：lxzy_ (赞：193)  
**星级：★★★★★**  
**关键亮点：**
- 思路清晰，详细解释了BFS的基本框架和传送门的处理方式。
- 代码结构清晰，使用了STL中的`queue`，便于理解和实现。
- 提供了传送门处理的详细逻辑，确保传送门的强制传送特性。

**个人心得：**
- 作者提到“传送门需要特判一下，并注意不要重复计算路径”，强调了传送门处理的难点。
- 通过`goto_another`函数实现传送门的跳转，代码简洁且高效。

**核心代码：**
```cpp
void goto_another(int &nx, int &ny, int k) {
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(a[i][j]==a[nx][ny] && (i!=nx || j!=ny)) {
                nx = i;
                ny = j;
                return;
            }
        }
    }
}
```
**核心思想：** 通过遍历地图找到与当前传送门配对的另一个传送门，并直接跳转。

#### 2. 作者：lzxhdxx (赞：87)  
**星级：★★★★☆**  
**关键亮点：**
- 使用了双向BFS优化，从起点和终点同时进行搜索，减少了搜索空间。
- 详细解释了传送门的多次使用问题，确保传送门不会被误标记。

**个人心得：**
- 作者提到“传送器不一定只用一次，有可能只是一个中转点”，强调了传送门可能被多次使用的情况。
- 通过`handle`函数处理传送门的跳转，确保传送门的正确使用。

**核心代码：**
```cpp
void handle(int& x, int& y) {
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(c[x][y] == c[i][j] && (x != i || y != j)) {
                x = i;
                y = j;
                return;
            }
        }
    }
}
```
**核心思想：** 通过遍历地图找到与当前传送门配对的另一个传送门，并直接跳转。

#### 3. 作者：ThinkofBlank (赞：11)  
**星级：★★★★☆**  
**关键亮点：**
- 提供了多种解法（01BFS、双向BFS、SPFA等），展示了不同算法的应用场景。
- 详细解释了传送门的处理方式，确保传送门的强制传送特性。

**个人心得：**
- 作者提到“传送门就是个~~hanpi~~”，强调了传送门处理的复杂性。
- 通过`goto_another`函数实现传送门的跳转，代码简洁且高效。

**核心代码：**
```cpp
void goto_another(int &nx, int &ny, int k) {
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(a[i][j]==a[nx][ny] && (i!=nx || j!=ny)) {
                nx = i;
                ny = j;
                return;
            }
        }
    }
}
```
**核心思想：** 通过遍历地图找到与当前传送门配对的另一个传送门，并直接跳转。

### 最优关键思路与技巧

1. **传送门处理：** 通过预处理传送门的位置，并在BFS中直接跳转到对应的传送门位置，避免重复计算。
2. **双向BFS优化：** 从起点和终点同时进行搜索，减少搜索空间，适用于较大规模的地图。
3. **SPFA与Dijkstra：** 适用于边权不固定的情况，但本题中传送门的边权为0，BFS已经足够高效。

### 可拓展之处

- **类似题目：** 可以拓展到其他带有特殊规则的最短路径问题，如带有陷阱、加速带等。
- **算法优化：** 在更大规模的地图中，可以考虑使用A*算法或IDA*算法进行进一步优化。

### 推荐题目

1. **P1443 马的遍历** - 考察BFS的基本应用。
2. **P1746 离开中山路** - 考察BFS在网格图中的应用。
3. **P1825 玉米田迷宫** - 本题的变种，考察带有传送门的最短路径问题。

### 个人心得总结

- **调试经历：** 多位作者提到在调试过程中遇到的传送门处理问题，如传送门多次使用、传送门不成对等，强调了细节处理的重要性。
- **踩坑教训：** 传送门的强制传送特性容易被忽略，导致路径计算错误，需特别注意。
- **顿悟感想：** 通过预处理传送门的位置，可以大大简化BFS的实现，提高代码的可读性和效率。

---
处理用时：35.08秒