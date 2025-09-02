# 题目信息

# [USACO07FEB] Lilypad Pond G

## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.


## 说明/提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$

## 样例 #1

### 输入

```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0
```

### 输出

```
2
3
```

# AI分析结果



# 算法分类：BFS

## 题解思路与核心难点

### 核心算法分析
题目要求通过放置最少荷叶实现从起点到终点的骑士跳跃，其本质是**带权最短路计数**问题。关键突破点在于以下三点：

1. **预处理建图**  
   每个水格（0）和起点（3）需要预处理其通过一个荷叶能到达的所有位置。通过DFS/BFS遍历原有荷叶（1）的连通区域，将这些区域内的跳跃终点作为边权为1的边加入邻接表。

2. **避免0权环**  
   原有荷叶（1）之间跳跃无需放置荷叶，直接将其连通区域视为中转节点，最终所有边权强制为1，彻底消除0权边导致的循环问题。

3. **SPFA动态更新**  
   使用SPFA算法进行松弛操作，同时维护两个数组：`dis[]`记录最小荷叶数，`cnt[]`记录方案数。当发现更短路径时重置计数，相同路径时累加计数。

### 可视化设计思路
1. **像素风格网格**  
   用32x32像素绘制每个池塘格子，颜色编码：蓝色（水）、绿色（荷叶）、灰色（岩石）、红色（起点）、金色（终点）。每次节点被访问时闪烁黄色边框。

2. **BFS扩展动画**  
   展示队列节点的扩展过程：起点入队→遍历8个方向→遇到荷叶连通区域时展开波纹扩散动画→最终路径用光点连线示意。

3. **音效系统**  
   - `jump.wav`：每次节点入队时播放8-bit跳跃音
   - `success.wav`：找到终点时播放经典FC过关音效
   - `countup.ogg`：方案数更新时发出金币收集声

## 高分题解推荐 (≥4★)

### 1. D_14134 的SPFA解法（★★★★☆）
**核心亮点**：  
- DFS预处理每个水格的跳跃范围，建立精确的边权为1的邻接表  
- SPFA中动态维护`dis`和`cnt`数组，代码简洁高效  
- 使用二维→一维坐标映射降低复杂度

**代码片段**：
```cpp
void dfs(int o,int x,int y){ // o为当前节点编号
    b[x][y] = 1;
    for(int k=0; k<8; k++){
        int xx=x+dx[k], yy=y+dy[k];
        if(越界跳过);
        if(mp[xx][yy]==1) dfs(o,xx,yy); // 原有荷叶继续探索
        else adde(o, p[xx][yy]); // 水格或终点建边
    }
}
```

### 2. 顾z 的DFS建图解法（★★★★☆）
**核心亮点**：  
- 通过`used`数组精确控制每个节点的预处理范围  
- 使用`vis[][]`二维标记避免重复访问  
- 独立处理起点和终点的特殊逻辑

**调试心得**：  
"预处理时发现原有荷叶区域必须完全展开，否则会漏掉某些跳跃路径。通过增加`vis[nowx][nowy]=true`在非荷叶节点及时终止搜索"

### 3. wwlw 的双重BFS解法（★★★★★）
**创新点**：  
- 第一层BFS预处理荷叶连通区域  
- 第二层BFS建立跨区域跳跃边  
- 最终SPFA求最短路，彻底避免0权问题

**关键代码**：
```cpp
void dfs1(int x,int y){
    if(是荷叶) 加入待处理队列;
    for(8方向){
        if(是荷叶)继续dfs;
        else 标记为待连接节点;
    }
}
void dfs2(int x,int y){
    for(所有待连接节点)
        建立当前区域到这些节点的边;
}
```

## 核心代码实现

### SPFA松弛与计数
```cpp
void spfa(int st){
    queue<int> q;
    dis[st]=0, cnt[st]=1;
    q.push(st);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i=head[u]; i; i=e[i].next){
            int v = e[i].to;
            if(dis[v] > dis[u]+1){ // 发现更短路径
                dis[v] = dis[u]+1;
                cnt[v] = cnt[u];
                q.push(v);
            }else if(dis[v] == dis[u]+1) // 相同长度
                cnt[v] += cnt[u]; // 累加方案数
        }
    }
}
```

## 相似题目推荐
1. **P1144 最短路计数** - 无权图最短路方案数
2. **P1608 路径统计** - 带权图最短路计数
3. **P1979 华容道** - 复杂预处理建图+SPFA

## 可视化代码片段（Canvas绘制节点）
```javascript
// 绘制池塘网格
function drawGrid(){
    ctx.clearRect(0,0,512,512);
    for(let i=0; i<n; i++){
        for(let j=0; j<m; j++){
            let color;
            if(i==sx&&j==sy) color = '#FF0000'; // 起点红色
            else if(i==ex&&j==ey) color = '#FFD700'; // 终点金色
            else if(mp[i][j]==1) color = '#00FF00'; // 荷叶绿色
            // ...其他颜色逻辑
            ctx.fillStyle = color;
            ctx.fillRect(j*32, i*32, 30, 30); // 32x32网格
        }
    }
}
// SPFA动画帧
function animate(){
    let u = queue.shift();
    drawNode(u, '#FFFF00'); // 高亮当前节点
    for(let v of adj[u]){
        if(updateDistance(u,v)){
            drawEdge(u,v, '#FFA500'); // 绘制橙色边
            requestAnimationFrame(animate);
        }
    }
}
```

通过这种结合经典算法与游戏化可视化的方式，学习者可以直观理解预处理建图的重要性，以及SPFA在带权最短路计数中的动态更新过程。

---
处理用时：76.09秒