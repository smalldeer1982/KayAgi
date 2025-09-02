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
本题核心在于寻找两点间激光路径的最少转向次数（即镜子数）。各题解主要采用BFS变种，结合方向状态记录，确保不重复处理同一方向上的点。关键优化点包括：沿同一方向扩展所有可达点、分层图建模、双端队列处理0-1权值边等。

---

### 高星题解推荐

#### 1. 作者：saipubw（5星）
**关键亮点**：
- **方向扩展优化**：每次处理一个点时，沿四个方向直线扩展到底，避免重复入队。
- **简洁高效**：普通队列实现，时间复杂度稳定，代码易读。
- **剪枝合理**：遇到障碍或边界立即停止扩展。

**核心代码**：
```cpp
void bfs(){
    while(!q.empty()){
        node now=q.front(); q.pop();
        if(到达终点) 输出答案;
        for(四个方向){
            while(沿该方向直线移动){
                if(未访问过则入队并标记)
            }
        }
    }
}
```

#### 2. 作者：学而思李老师（5星）
**关键亮点**：
- **双端队列BFS**：将同方向移动视为0权边，转向视为1权边，利用队列单调性优化。
- **状态设计**：记录位置和方向，通过队首/队尾插入区分不同权值。

**核心代码**：
```cpp
deque<Node> dq;
while(!dq.empty()){
    Node u = dq.front();
    if(同方向扩展) dq.push_front(新状态); // 0权
    else dq.push_back(新状态);          // 1权
}
```

#### 3. 作者：Delva（4星）
**关键亮点**：
- **分层图建模**：将每个点的四个方向作为独立层，转化为标准最短路问题。
- **算法普适性**：Dijkstra实现清晰，适合理解分层图思想。

**核心代码**：
```cpp
// 层内建图（同方向移动）
addEdge(point_ID(t,i,j), point_ID(t,nx,ny), 0);
// 层间建图（转向）
addEdge(point_ID(t,i,j), point_ID(u,i,j), 1);
```

---

### 关键思路总结
1. **方向状态记录**：将当前位置+方向作为状态，避免重复计算。
2. **直线扩展优化**：沿当前方向一次性处理所有可达点，减少队列操作。
3. **权值分离处理**：通过双端队列或分层图区分直行/转向代价。

---

### 同类题目推荐
1. **P1126 机器人搬重物** - 方向控制移动步数
2. **P1649 障碍路线** - 最小转向次数的路径
3. **P4667 [NOIP2016] 换教室** - 状态分层图应用

---

### 调试心得摘录
- **初始状态处理**：多个题解提到起点方向需特殊处理（如IRipple代码中减1）。
- **转向计数逻辑**：需明确是否包含起点方向（如GTAyin题解中的-1初始化）。
- **剪枝重要性**：必须及时终止无效扩展（saipubw遇到障碍立即break）。

---
处理用时：61.25秒