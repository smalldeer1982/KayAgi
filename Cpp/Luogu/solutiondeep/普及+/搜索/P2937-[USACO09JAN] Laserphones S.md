# 题目信息

# [USACO09JAN] Laserphones S

## 题目描述

The cows have a new laser-based system so they can have casual conversations while out in the pasture which is modeled as a W x H grid of points (1 <= W <= 100; 1 <= H <= 100).

The system requires a sort of line-of-sight connectivity in order to sustain communication. The pasture, of course, has rocks and trees that disrupt the communication but the cows have purchased diagonal mirrors ('/' and '\' below) that deflect the laser beam through a 90 degree turn. Below is a map that illustrates the

problem.

H is 8 and W is 7 for this map.  The two communicating cows are notated as 'C's; rocks and other blocking elements are notated as '\*'s:

```plain
7 . . . . . . .         7 . . . . . . . 
6 . . . . . . C         6 . . . . . /-C 
5 . . . . . . *         5 . . . . . | * 
4 * * * * * . *         4 * * * * * | * 
3 . . . . * . .         3 . . . . * | . 
2 . . . . * . .         2 . . . . * | . 
1 . C . . * . .         1 . C . . * | . 
0 . . . . . . .         0 . \-------/ . 
0 1 2 3 4 5 6           0 1 2 3 4 5 6 
```
Determine the minimum number of mirrors M that must be installed to maintain laser communication between the two cows, a feat which is always possible in the given test data.


## 样例 #1

### 输入

```
7 8 
....... 
......C 
......* 
*****.* 
....*.. 
....*.. 
.C..*.. 
....... 
```

### 输出

```
3 
```

# AI分析结果



### 综合分析与结论
本题核心在于寻找两点间路径的最少转弯次数（等价于镜子数）。各题解主要围绕BFS的变种展开，关键点在于方向状态管理与剪枝优化。最优解法普遍采用「方向扩展+同向延展」思路，将转弯视为状态切换，确保首次到达终点的路径即最优。

---

### 高星题解推荐

#### 1. 学而思李老师（4星）
**关键亮点**：使用双端队列BFS，同方向延展时入队首（权值0），转向时入队尾（权值1），完美契合最短路性质。  
**个人心得**：通过维护当前方向状态，将问题转化为带权最短路问题，代码简洁高效。  
**核心代码**：
```cpp
void bfs2() {
    queue<Node> q;
    Node s; s.init(sx,sy,1,-1);
    q.push(s);
    while(q.size()){
        Node u=q.front(); q.pop();
        u.val++;
        for(int i=1;i<=4;i++){ // 四个方向扩展
            if(vis[u.x][u.y][i]) continue;
            vis[u.x][u.y][i]=1;
            Node v = {u.x+dx[i], u.y+dy[i], i, u.val};
            // 同方向延展直到障碍物
            while(v.x在边界内且非障碍物){
                if(到达终点) return v.val;
                q.push(v);
                v.x += dx[i]; v.y += dy[i];
            }
        }
    }
}
```

#### 2. IRipple（4星）
**关键亮点**：BFS结合DFS方向延展，每次将同方向直线上的点全部标记，避免逐格入队。  
**技巧**：使用`dfs`函数处理同一方向的连续可通行区域，减少队列操作次数。  
**核心逻辑**：
```cpp
void dfs(int fx, node u){
    while(同一方向可通行){
        标记该点并加入队列，继续延展
    }
}
void bfs(){
    每次取出节点后，向四个方向调用dfs处理直线路径
}
```

#### 3. songhongyi（4星）
**关键亮点**：纯BFS实现，每次处理节点时向四个方向延展到边界/障碍物，代码极简。  
**优化点**：利用`while`循环一次性扩展整条直线路径，避免逐格判断。  
**核心代码**：
```cpp
while(!q.empty()){
    Node u = q.front(); q.pop();
    for(四个方向){
        while(沿当前方向移动且合法){
            if(未访问过){
                标记并加入队列
                if(到达终点) 输出答案
            }
        }
    }
}
```

---

### 关键思路与技巧总结
1. **方向状态记录**：使用三维数组`vis[x][y][dir]`记录每个点在某个方向上的最小转弯次数。
2. **同向延展优化**：沿当前方向直线扩展所有可达点，避免逐格入队。
3. **双端队列应用**：将不转弯的路径（权0）优先处理，确保队列单调性。
4. **分层图思想**：将方向视为独立状态层，转换为图的最短路径问题。

---

### 相似题目推荐
1. [P1649 障碍路线](https://www.luogu.com.cn/problem/P1649) - 最少转弯路径
2. [P1126 机器人搬重物](https://www.luogu.com.cn/problem/P1126) - 方向控制与路径规划
3. [P4667 定向越野](https://www.luogu.com.cn/problem/P4667) - 分层图最短路应用

---
处理用时：52.46秒