# 题目信息

# Buy a Ticket

## 题目描述

Musicians of a popular band "Flayer" have announced that they are going to "make their exit" with a world tour. Of course, they will visit Berland as well.

There are $ n $ cities in Berland. People can travel between cities using two-directional train routes; there are exactly $ m $ routes, $ i $ -th route can be used to go from city $ v_{i} $ to city $ u_{i} $ (and from $ u_{i} $ to $ v_{i} $ ), and it costs $ w_{i} $ coins to use this route.

Each city will be visited by "Flayer", and the cost of the concert ticket in $ i $ -th city is $ a_{i} $ coins.

You have friends in every city of Berland, and they, knowing about your programming skills, asked you to calculate the minimum possible number of coins they have to pay to visit the concert. For every city $ i $ you have to compute the minimum number of coins a person from city $ i $ has to spend to travel to some city $ j $ (or possibly stay in city $ i $ ), attend a concert there, and return to city $ i $ (if $ j≠i $ ).

Formally, for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you have to calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/f2e29a8bb6e05026242d6e3afeeabb7241997635.png), where $ d(i,j) $ is the minimum number of coins you have to spend to travel from city $ i $ to city $ j $ . If there is no way to reach city $ j $ from city $ i $ , then we consider $ d(i,j) $ to be infinitely large.

## 样例 #1

### 输入

```
4 2
1 2 4
2 3 7
6 20 1 25
```

### 输出

```
6 14 1 25 
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 1
30 10 20
```

### 输出

```
12 10 12 
```

# AI分析结果



**唯一算法分类**  
最短路（Dijkstra + 虚拟源点）

---

### **题解思路、算法要点与解决难点**  
**核心思路**  
1. **虚拟源点转化**：将点权（城市票价）转化为虚拟源点到该点的边权。  
2. **往返边权处理**：原图边权乘2（往返两次）。  
3. **单源最短路**：从虚拟源点跑一次 Dijkstra，结果即为所有城市的最小花费。  

**算法要点**  
- **虚拟源点 0**：向每个城市连边，边权为该城市的票价 `a_i`。  
- **边权调整**：原图边权 `w_i` → `2*w_i`（往返路径）。  
- **Dijkstra 优化**：优先队列实现，时间复杂度 O((M+N)logN)。  

**解决难点**  
- **点权→边权**：通过虚拟源点将终点点权与路径分离，统一为边权问题。  
- **无穷大处理**：正确初始化 `dis` 数组为极大值，避免溢出。  

---

### **题解评分（≥4星）**  
1. **傅思维666（★★★★★）**  
   - 亮点：详细推导虚拟源点逻辑，代码清晰，附博客链接。  
   - 代码关键：显式构建虚拟源点边，优先队列优化。  

2. **Mr_think（★★★★★）**  
   - 亮点：图文结合解释虚拟源点，同类题推荐。  
   - 代码关键：优先队列反向压入负数实现小根堆。  

3. **E1_de5truct0r（★★★★☆）**  
   - 亮点：代码简洁，强调往返边权处理。  
   - 代码关键：直接使用 `vector` 邻接表，无多余封装。  

---

### **最优思路或技巧提炼**  
**关键技巧**  
1. **虚拟源点法**：将多源问题转化为单源问题，适用于「终点需附加点权」的场景。  
2. **往返边权预处理**：在无向图中提前将边权乘2，避免后续计算冗余。  

**思维角度**  
- **逆向建模**：将「选择终点」转化为「从虚拟源点出发的最短路径」。  
- **统一化处理**：通过虚拟边将点权与路径分离，简化最短路逻辑。  

---

### **同类型题或类似算法套路**  
1. **POJ 1062 昂贵的聘礼**：虚拟源点 + 等级限制最短路。  
2. **洛谷 P1629 邮递员送信**：往返最短路问题。  
3. **虚拟边技巧**：点权转边权、多条件约束统一建模。  

---

### **推荐相似洛谷题目**  
1. **P4779** 【模板】单源最短路径（标准 Dijkstra 模板）  
2. P1875 佳佳的魔法药水（虚拟源点 + 最短路变形）  
3. P4568 [JLOI2011] 飞行路线（分层图最短路）  

---

### **个人心得摘录**  
- **调试教训**：多位题解作者因未开 `long long` 或忘记边权乘2导致 WA。  
- **核心顿悟**：虚拟源点的引入将多终点问题简化为单源问题，极大降低复杂度。  

---

### **可视化与算法演示**  
**核心算法动画方案**  
1. **虚拟源点高亮**：  
   - 颜色：紫色节点表示虚拟源点，黄色节点表示当前处理的节点。  
   - 操作：虚拟源点逐步扩展到各城市，显示 `dis` 数组更新过程。  

2. **边权动态标记**：  
   - 原图边：蓝色线条，宽度与 `2*w_i` 成比例。  
   - 虚拟边：绿色虚线，宽度与 `a_i` 成比例。  

3. **步进控制与音效**：  
   - **单步执行**：按空格键逐步推进 Dijkstra 流程。  
   - **音效触发**：节点松弛时播放短促“滴”声，完成时播放上扬音效。  

**复古像素化实现（伪代码）**  
```javascript
// Canvas 初始化（8位风格）  
const grid = new PixelGrid(16, 16);  
grid.drawNode(0, 0, PURPLE); // 虚拟源点  
nodes.forEach((node, i) => {  
  grid.drawNode(i+1, 0, BLUE);  
  grid.drawLine(0, 0, i+1, 0, GREEN_DASHED);  
});  
// Dijkstra 动画循环  
while (!queue.empty()) {  
  const u = queue.pop();  
  grid.highlightNode(u, YELLOW);  
  playSound('step');  
  neighbors.forEach(v => {  
    if (dis[v] > dis[u] + w) {  
      dis[v] = dis[u] + w;  
      grid.updateText(v, dis[v]);  
      grid.flashEdge(u, v);  
    }  
  });  
}  
```

---

### **核心代码实现**  
**Dijkstra 核心片段（C++）**  
```cpp  
void dijkstra(int s) {  
    priority_queue<pair<ll, int>> pq;  
    memset(dis, 0x3f, sizeof(dis));  
    dis[s] = 0;  
    pq.push({0, s});  
    while (!pq.empty()) {  
        int u = pq.top().second;  
        pq.pop();  
        if (vis[u]) continue;  
        vis[u] = true;  
        for (auto &e : adj[u]) {  
            int v = e.to;  
            ll w = e.w;  
            if (dis[v] > dis[u] + w) {  
                dis[v] = dis[u] + w;  
                pq.push({-dis[v], v}); // 小根堆技巧  
            }  
        }  
    }  
}  
// 建图关键代码  
for (int i=1; i<=n; i++) {  
    ll a; cin >> a;  
    adj[0].push_back({i, a}); // 虚拟源点连边  
}  
for (int i=1; i<=m; i++) {  
    int u, v; ll w;  
    cin >> u >> v >> w;  
    adj[u].push_back({v, 2*w}); // 往返边权  
    adj[v].push_back({u, 2*w});  
}  
```

---

**总结**  
本题通过虚拟源点将多终点问题转化为单源最短路，结合往返边权预处理，实现 O((M+N)logN) 的高效解法。核心技巧适用于需附加终点权值的场景，是图论建模的经典思路。

---
处理用时：79.04秒