# 题目信息

# [USACO07OCT] Obstacle Course S

## 题目描述

Consider an N x N (1 <= N <= 100) square field composed of 1

by 1 tiles. Some of these tiles are impassible by cows and are marked with an 'x' in this 5 by 5 field that is challenging to navigate:

```cpp
. . B x . 
. x x A . 
. . . x . 
. x . . . 
. . x . . 
```
Bessie finds herself in one such field at location A and wants to move to location B in order to lick the salt block there.  Slow, lumbering creatures like cows do not like to turn and, of course, may only move parallel to the edges of the square field. For a given field, determine the minimum number of ninety degree turns in any path from A to B. The path may begin and end with Bessie facing in any direction. Bessie knows she can get to the salt lick.



## 说明/提示

只可以上下左右四个方向行走，并且不能走出这些格子之外。开始和结束时的方向可以任意。

### 数据范围及约定

对于全部数据，保证 $2\le N\le 100$。


## 样例 #1

### 输入

```
3
. x A
. . .
B x .```

### 输出

```
2```

# AI分析结果



### 综合分析与结论
该题核心在于求路径中90度转弯的最少次数，各题解主要采用BFS优化、记忆化搜索、拆点最短路等思路。关键在于如何高效处理方向变化与状态更新，避免重复计算。

---

### 精选题解推荐

#### 1. 白烛葵（洪水填充BFS） ★★★★★  
**关键亮点**：  
- 采用洪水填充思想，每次沿直线扩展到底，记录转弯次数。  
- 利用队列分层处理，保证同一方向扩展的连续性，时间复杂度O(N²)。  
**核心代码**：  
```cpp
while(l<r){
    for(int i=0;i<4;i++)
    for(int k=1;;k++){ // 沿当前方向扩展到底
        int xx=hrb[l].x+k*xy[i], yy=hrb[l].y+k*yx[i];
        if(越界或障碍) break;
        emm[xx][yy] = emm[当前点] + 1; // 转弯次数更新
        hrb[r++] = {xx, yy};
    }
    l++;
}
```
**个人心得**：  
> "常规BFS需多次回溯，洪水填充一次扩展完所有直线路径，效率显著提升。"

---

#### 2. GNAQ（分层BFS） ★★★★☆  
**关键亮点**：  
- 将每个点的四个方向拆分为独立状态，用桶记录转弯次数。  
- 通过优先处理同方向扩展，避免重复计算转弯。  
**核心代码**：  
```cpp
for(int i=0; i<4; i++){
    node v = {x+dx[i], y+dy[i], i, turns+1};
    if(新方向不同) v.turns++;
    if(更优) 更新并入队;
}
```
**优化点**：通过方向分层保证状态唯一性，减少无效搜索。

---

#### 3. 杨先达（拆点Dijkstra） ★★★★  
**关键亮点**：  
- 将每个点拆为4个方向节点，构建分层图。  
- 用双端队列优化Dijkstra，边权为0/1，时间复杂度O(N²)。  
**核心代码**：  
```cpp
for(int k=0;k<4;k++) // 起点四个方向入队
    q.push_back({sx,sy,k}), v[sx][sy][k]=0;
while(!q.empty()){
    node x = q.front(); q.pop_front();
    if(终点) return x.turn;
    for(四个方向扩展){
        if(同方向) 边权0，队头入队；
        else 边权1，队尾入队；
    }
}
```

---

### 关键思路总结
1. **洪水填充BFS**：直线扩展到底，转弯时次数+1，避免逐格判断。  
2. **方向分层处理**：将方向作为独立状态，确保每个方向的最优解独立更新。  
3. **拆点最短路**：将点拆分为多个方向节点，转化为边权为0/1的最短路问题。  

---

### 举一反三推荐题目
1. **P2937 [USACO09JAN]激光电话Laserphones**（类似转弯计数）  
2. **P2296 寻找道路**（BFS+方向限制）  
3. **P4667 Switch the Lamp On**（边权0/1的双端队列BFS）  

---

### 调试与优化教训
- **方向数组顺序影响剪枝**：Lidy的DFS因方向遍历顺序不同可能AC或WA。  
- **多次入队更新更优解**：QQ红包的BFS允许同一节点多次入队以更新最小转弯次数。  
- **初始方向处理**：多个题解需特殊处理起点无方向的情况（如初始方向设为-1）。

---
处理用时：49.75秒