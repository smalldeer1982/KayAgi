# 题目信息

# [SDOI2009] Elaxia的路线

## 题目描述

最近，Elaxia 和 w** 的关系特别好，他们很想整天在一起，但是大学的学习太紧张了，他们必须合理地安排两个人在一起的时间。

Elaxia 和 w** 每天都要奔波于宿舍和实验室之间，他们 希望在节约时间的前提下，一起走的时间尽可能的长。

现在已知的是 Elaxia 和 w** 所在的宿舍和实验室的编号以及学校的地图：  
地图上有 $n$ 个路口，$m$ 条路，经过每条路都需要一定的时间。 具体地说，就是要求无向图中，两对点间最短路的最长公共路径。


## 说明/提示

【数据范围】    
对于 $30\%$ 的数据，$1\le n \le 100$；   
对于 $60\%$ 的数据，$1\le n \le 1000$；   
对于 $100\%$ 的数据，$1\le n \le 1500$，$1 \leq m \leq 3 \times 10^5$，$1\le w \le 10^4$，输入数据保证没有重边和自环。


## 样例 #1

### 输入

```
9 10
1 6 7 8
1 2 1
2 5 2
2 3 3
3 4 2
3 9 5
4 5 3
4 6 4
4 7 2
5 8 1
7 9 1```

### 输出

```
3```

# AI分析结果



---

## 唯一算法分类
图论-最短路与拓扑排序结合

---

## 综合分析与结论

### 核心思路
1. **四次最短路计算**：分别计算两对起点到终点的最短路径（Elaxia的宿舍→实验室、w**的宿舍→实验室）
2. **筛选公共路径边**：满足以下两个条件的边视为公共路径：
   - 在Elaxia的最短路径中：dis(x1, u) + w + dis(y1, v) = dis(x1, y1)
   - 在w**的最短路径中（分两种方向情况）：
     - 同向：dis(x2, u) + w + dis(y2, v) = dis(x2, y2)
     - 反向：dis(y2, u) + w + dis(x2, v) = dis(x2, y2)
3. **构建DAG并拓扑排序**：对筛选出的边构建有向无环图（DAG），通过拓扑排序计算最长路径

### 难点与突破
- **方向处理**：必须分别处理同向和反向两种情况（否则会被hack数据卡掉）
- **边筛选优化**：通过最短路公式高效判断边是否属于公共路径
- **DAG构建技巧**：将筛选后的边转换为拓扑结构，避免环干扰

---

## 题解清单（≥4星）

### 1. caeious（★★★★☆）
**亮点**：
- 详细证明公共路径必须为链状结构
- 用Dijkstra+拓扑排序两次处理方向问题
- 通过两次建图覆盖所有合法情况

**核心代码段**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=head[i];j!=-1;j=nxt[j]){
        if(d[1][i] + el[j].cst + d[2][el[j].to] == d[1][y1]){
            // 处理同向边
            if(d[3][i] + el[j].cst + d[4][el[j].to] == d[3][y2])
                addedge2(i,el[j].to,el[j].cst);
            // 处理反向边
            if(d[4][i] + el[j].cst + d[3][el[j].to] == d[3][y2])
                addedge2(i,el[j].to,el[j].cst);
        }
    }
}
```

### 2. BJpers2（★★★★★）
**亮点**：
- 使用优先队列优化Dijkstra
- 单次拓扑同时处理两种方向
- 代码简洁高效（仅50行）

**核心思路**：
```cpp
FOR(u,1,n) REP(u) // 遍历所有边
    if(dis[0][u]+w+dis[1][v]==dis[0][t1]) 
        ok[i]=1; // 标记合法边

// 拓扑时同时判断两种方向
if(dis[2][u]+w+dis[3][v]==dis[2][t2]) f[v]=max(f[v],f[u]+w); // 同向
if(dis[3][u]+w+dis[2][v]==dis[2][t2]) g[v]=max(g[v],g[u]+w); // 反向
```

---

## 最优思路与技巧

### 关键技巧
1. **四维最短路标记法**：同时维护四个距离数组（x1,y1,x2,y2出发的最短路）
2. **双向边筛选**：分别计算同向和反向的合法情况
3. **拓扑排序优化**：在拓扑过程中直接维护最长路径，无需额外DP

### 同类型题目
- P1144 最短路计数
- P2680 运输计划
- P1608 路径统计

---

## 可视化设计

### 算法演示方案
1. **像素风格呈现**（Canvas实现）：
   - 节点：8×8像素方块（绿色=起点，红色=终点，蓝色=普通节点）
   - 边：黄色线段（合法公共路径边高亮为橙色）
   
2. **动态分步演示**：
   ```javascript
   class Animation {
       constructor() {
           this.steps = ["dijkstra", "filter_edges", "topo_sort"];
           this.speed = 500; // 毫秒/步
       }
       
       showDijkstra() {
           // 高亮当前计算的起点（x1闪烁→y1→x2→y2）
       }
       
       filterEdges() {
           // 用橙色闪烁显示被选中的公共边
       }
       
       runTopo() {
           // 拓扑排序时用流动光效显示当前处理的节点
       }
   }
   ```

3. **音效设计**：
   - 边被选中时：8-bit "哔"声（440Hz方波）
   - 完成拓扑排序：胜利音效（升调和弦）

4. **交互功能**：
   ```html
   <div class="control-panel">
       <button onclick="anim.pause()">⏸</button>
       <input type="range" min="100" max="2000" onchange="anim.setSpeed(this.value)">
       <button onclick="anim.showDataStructure()">📊显示数据结构</button>
   </div>
   ```

---

## 核心算法实现（BJpers2精简版）

```cpp
void dijkstra(int s, int k) {
    priority_queue<P> q;
    fill(dis[k]+1, dis[k]+n+1, INF);
    q.push({dis[k][s]=0, s});
    while(!q.empty()) {
        int u = q.top().second; q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int i=hd[u];i;i=e[i].n) {
            int v = e[i].v, w = e[i].w;
            if(dis[k][v] > dis[k][u] + w)
                q.push({dis[k][v]=dis[k][u]+w, v});
        }
    }
}

// 拓扑排序核心
while(l < r) {
    int u = q[l++];
    for(int i=hd[u];i;i=e[i].n) if(ok[i]) {
        int v = e[i].v, w = e[i].w;
        if(符合同向条件) f[v] = max(f[v], f[u]+w);
        if(符合反向条件) g[v] = max(g[v], g[u]+w);
        if(--in[v] == 0) q[r++] = v;
    }
}
```

---
处理用时：75.84秒