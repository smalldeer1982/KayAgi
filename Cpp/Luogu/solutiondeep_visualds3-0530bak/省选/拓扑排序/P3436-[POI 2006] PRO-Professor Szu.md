# 题目信息

# [POI 2006] PRO-Professor Szu

## 题目描述

The Byteotian University is situated in the city of Byteion.

Apart from the main building the university owns \(n\) cottages for its academic staff. The cottages are connected with one - way alleys, however, there could be more than one alley between any two cottages (the alley can also form a loop connecting a building to itself). There are also alleys connecting the cottages to the main building. Byteion has been constructed so that no two alleys intersect in a point different from a cottage or the main building (there can however be bridges or tunnels on alleys). Moreover, each and every alley starts and ends in a cottage or the main building. It is known that a route exists between at least one of the cottages and the main building.

Once upon a time, the Byteotian University fancied to hire a well - known computer science pundit - professor Szu. As most outstanding scientists professor Szu has a certain peculiarity to him: each day he wishes to go to the university using a different route (a route being a sequence of alleys, each starting at the cottage the previous one ended at; the main building and each of the cottages may be visited many times). The professor considers two routes distinct if they differ by at least one alley (the order matters; two different alleys connecting the very same two cottages are considered distinct).

Knowing the diagram of connections help the university in finding a cottage which has the greatest number of different routes to the main building possible (staying in such a cottage professor Szu will spend the longest time working at the university). Should there be more than one such cottage - find all of them. Should there be more than 36500 possible routes between a certain cottage and the main building we will assume that professor Szu can stay in this particular cottage forever (as he surely cannot live infinitely and 100 years seems a safe guess).

### Task

Write a programme which:
- reads from the standard input the diagram of connections between the cottages of Byteion,
- determines the cottages which Professor Szu could live the longest time in and the longest possible time of habitation,
- writes the outcome to the standard output.


## 样例 #1

### 输入

```
3 5
1 2
1 3
2 3
3 4
3 4```

### 输出

```
4
1
1```

# AI分析结果



**唯一算法分类**：强连通分量缩点（Tarjan） + 拓扑排序动态规划

---

### **题解思路与算法要点**
1. **反向建图**  
   将原问题中的路径方向反转（别墅→主楼变为主楼→别墅），便于从主楼出发进行路径数统计。

2. **Tarjan缩点**  
   - 识别强连通分量（SCC），标记含环的SCC（包括自环）。
   - 缩点后构建DAG，统计每个SCC的入度。

3. **拓扑排序与动态规划**  
   - 从主楼所在SCC出发，按拓扑序递推各节点的路径数。
   - 若节点属于有环SCC或路径数超过36500，则标记为36501。

4. **结果统计**  
   遍历所有别墅节点，找出最大路径数及对应节点。

---

### **核心难点与解决方案**
- **环处理**：通过Tarjan缩点识别环，并在拓扑排序中将环内节点的路径数设为无穷大。
- **路径数溢出**：在动态规划过程中，累加路径数时若超过阈值则直接截断为36501。
- **主楼自环**：主楼所在SCC若有环，需避免影响别墅节点的统计。

---

### **最优思路提炼**
- **反向建图+缩点**：将原问题转化为DAG上的路径统计问题。
- **拓扑序动态规划**：确保无环图上的递推顺序正确，处理环的逻辑统一。
- **路径数截断优化**：在累加过程中即时判断是否超过阈值，减少计算量。

---

### **题解评分**
1. **Jμdge（★★★★★）**  
   - **亮点**：自环处理清晰，代码注释详细，缩点与拓扑逻辑严密。
   - **代码可读性**：结构清晰，关键变量命名合理。
   - **优化点**：通过反向建图简化路径统计。

2. **Alex_Wei（★★★★☆）**  
   - **亮点**：预处理无法到达主楼的节点，提升效率。
   - **不足**：代码中未显式处理主楼自环的特殊情况。

3. **Coros_Trusds（★★★★☆）**  
   - **亮点**：代码模块化程度高，缩点与DP分离明确。
   - **不足**：路径数截断逻辑稍显冗余。

---

### **关键代码片段（Jμdge题解）**
```cpp
void tarjan(int u) {
    // 判断自环并标记含环SCC
    for (int i=head[u];i!=-1;i=e[i].next) {
        int v=e[i].v; 
        if(u==v) flag=true; // 自环检测
    }
    // 缩点逻辑...
    if (flag || stk.top()!=u) is[part]=true; // 标记含环SCC
}

void topo() {
    queue<int> Q; 
    f[blg[n]] = 1; // 主楼路径数初始化为1
    while (!Q.empty()) {
        int now = Q.front();
        if (is[now] && f[now]) f[now] = 36501; // 环处理
        for (邻接节点v) {
            f[v] = min(f[v] + f[now], 36501); // 动态规划累加
        }
    }
}
```

---

### **同类型题目推荐**
1. **P3387 【模板】缩点**  
   - **关键词**：强连通分量缩点、DAG动态规划。

2. **P2746 [USACO5.3]校园网Network of Schools**  
   - **关键词**：缩点后入度/出度分析。

3. **P4017 最大食物链计数**  
   - **关键词**：拓扑排序路径计数。

---

### **可视化设计思路**
1. **动画流程**  
   - **步骤1**：展示原图与反向建图效果，高亮主楼节点。
   - **步骤2**：动态演示Tarjan缩点过程，用颜色区分含环SCC。
   - **步骤3**：拓扑排序时，逐步填充路径数，超过阈值时触发红色警示。

2. **复古像素风格**  
   - **颜色方案**：SCC用8色调色板区分，路径数用渐变绿色表示大小。
   - **音效**：累加路径数时播放“点击”音效，发现环时播放警告音。

3. **交互控制**  
   - **步进控制**：允许暂停观察当前路径数状态。
   - **自动演示**：模拟AI自动运行拓扑排序，关键步骤文字说明。

---

### **个人心得**
- **调试经验**：自环易被漏判，需在Tarjan中显式检查边起点与终点是否相同。
- **优化感悟**：路径数截断需在累加时即时处理，而非最后统一判断，减少溢出风险。

---
处理用时：121.24秒