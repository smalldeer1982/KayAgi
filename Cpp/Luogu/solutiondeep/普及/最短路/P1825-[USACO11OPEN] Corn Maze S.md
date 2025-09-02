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

本题的核心是通过BFS（广度优先搜索）找到从起点到终点的最短路径，难点在于处理传送门机制。传送门的存在使得路径搜索变得复杂，因为传送门会强制将角色传送到另一个位置，且传送时间为0。大多数题解通过预处理传送门的位置，并在BFS过程中进行特殊处理来解决这一问题。

### 所选高星题解

#### 1. 作者：lxzy_ (赞：193)  
**星级：4.5**  
**关键亮点：**
- 使用BFS模板，思路清晰，代码结构简洁。
- 通过`goto_another`函数处理传送门，确保传送门的使用符合题目要求。
- 代码可读性强，注释详细，适合初学者学习。

**个人心得：**
- 作者提到“传送门需要特判一下，并注意不要重复计算路径”，强调了传送门处理的细节。

**核心代码：**
```cpp
void goto_another(int &nx,int &ny,int k) {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if(a[i][j]==a[nx][ny]&&(i!=nx||j!=ny)) {
                nx=i; ny=j; return;
            }
        }
    }
}
```
**核心思想：**  
通过遍历地图找到与当前传送门配对的另一个传送门，并更新当前位置。

#### 2. 作者：lzxhdxx (赞：87)  
**星级：4.0**  
**关键亮点：**
- 使用双向BFS优化搜索效率，减少搜索空间。
- 详细讨论了传送门的多次使用问题，并提出了解决方案。
- 代码结构清晰，注释详细。

**核心代码：**
```cpp
int expand(int sub) {
    int nowx = Q[sub].front().first, nowy = Q[sub].front().second; Q[sub].pop();
    for(int i=1;i<=4;i++) {
        int newx = nowx + dx[i], newy = nowy + dy[i];
        if(newx>=1&&newy>=1&&newx<=n&&newy<=m&&c[newx][newy]!='#'&&!vis[sub][newx][newy]) {
            if(c[newx][newy]>='A'&&c[newx][newy]<='Z') {
                int x = newx, y = newy;
                vis[sub][newx][newy] = 1; handle(newx, newy);
            }
            else vis[sub][newx][newy] = 1;
            Q[sub].push(make_pair(newx, newy));
            if(vis[1-sub][newx][newy]) return cnt[1-sub][newx][newy] + cnt[sub][newx][newy];
        }
    }
    return 0;
}
```
**核心思想：**  
通过双向BFS从起点和终点同时搜索，减少搜索时间，并在遇到传送门时进行特殊处理。

#### 3. 作者：maorui_cow (赞：65)  
**星级：4.0**  
**关键亮点：**
- 使用BFS模板，代码简洁，易于理解。
- 通过`cz`函数处理传送门，确保传送门的使用符合题目要求。
- 代码结构清晰，适合初学者学习。

**核心代码：**
```cpp
int cz(int x,int y) {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if(!(i==x&&j==y)) {
                if(a[i][j]==a[x][y]) {
                    cz1=i; cz2=j; return 0;
                }
            }
        }
    }
}
```
**核心思想：**  
通过遍历地图找到与当前传送门配对的另一个传送门，并更新当前位置。

### 最优关键思路与技巧

1. **传送门处理：** 通过预处理传送门的位置，并在BFS过程中进行特殊处理，确保传送门的使用符合题目要求。
2. **双向BFS优化：** 使用双向BFS从起点和终点同时搜索，减少搜索时间，适用于较大地图的搜索问题。
3. **代码结构清晰：** 通过函数封装传送门处理逻辑，保持代码的可读性和可维护性。

### 可拓展之处

- **类似题目：** 可以扩展到其他带有特殊机制的路径搜索问题，如带有陷阱、加速带等的地图。
- **算法优化：** 可以进一步优化BFS的实现，如使用优先队列（Dijkstra）处理带权路径问题。

### 推荐题目

1. **P1443 马的遍历** - 考察BFS的基本应用。
2. **P1746 离开中山路** - 考察BFS在网格图中的应用。
3. **P1825 玉米田迷宫** - 本题的变种，考察BFS与特殊机制的结合。

### 个人心得总结

- **调试经历：** 多位作者提到在处理传送门时容易忽略传送门的多次使用问题，导致路径计算错误。
- **踩坑教训：** 传送门的处理需要特别注意，避免重复计算路径或忽略传送门的强制使用规则。
- **顿悟感想：** 通过预处理和函数封装，可以简化复杂逻辑的处理，提高代码的可读性和可维护性。

---
处理用时：44.06秒