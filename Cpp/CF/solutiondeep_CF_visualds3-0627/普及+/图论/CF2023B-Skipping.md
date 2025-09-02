# 题目信息

# Skipping

## 题目描述

现在已经是3024年了，出题的想法早就枯竭。现今的OI以一种修改后的个人参赛形式进行。比赛有$n$道题，编号从$1$到$n$，一道题有一个分数$a_i$和一个参数$b_i$。最开始，评测系统会把第$1$道题丢给选手。当一个选手拿到第$i$道题，他有两个选择：

- 提交，获得$a_i$分
- 跳过，但他再不能去交这道题了。

接下来，评测系统会把编号最大的符合下述条件的题目$j$丢给选手：

- 如果选手提交了$i$题，那么$j<i$
- 如果选手选择跳过，那么$j\leq b_i$

系统不能给选手一道之前给过的题目。如果系统找不到这样的题，那么比赛结束。特别的，如果选手提交第一题，比赛结束。

请你帮助小p拿到最高的可能得分。

## 样例 #1

### 输入

```
4
2
15 16
2 1
5
10 10 100 100 1000
3 4 1 1 1
3
100 49 50
3 2 2
4
100 200 300 1000
2 3 4 1```

### 输出

```
16
200
100
1000```

# AI分析结果



---

## 算法分类  
**图论（最短路）**

---

## 综合分析与结论  

### 核心算法流程  
1. **建图模型**：  
   - 每个题目视为一个节点  
   - **提交操作**：从节点i到i-1连权值为0的边（可以回溯到更小编号题目）  
   - **跳过操作**：从节点i到b_i连权值为a_i的边（跳过i题需要损失a_i分）  

2. **最短路求解**：  
   - 用Dijkstra算法计算从节点1到所有节点的最短路径（最小损失）  
   - 前缀和数组sum[i]记录前i题的分数总和  
   - 最终答案：max(sum[i] - dis[i])，即选择到达i点时能获得的最大分数  

3. **可视化设计**：  
   - **动画效果**：展示节点间蓝边（提交操作）和绿边（跳过操作），用不同颜色区分权值  
   - **高亮机制**：当前处理的节点用红色闪烁，已确定最短路径的节点用绿色标记  
   - **步进控制**：允许单步执行Dijkstra算法，观察优先队列的更新过程  

---

## 题解评分（≥4星）  

### AquariusZhao（5星）  
- **亮点**：最短路模型简洁，代码可读性极强  
- **核心代码**：  
  ```cpp
  for(int i=1; i<=n; i++) {
    g[i].push_back({b[i], a[i]});
    if(i>1) g[i].push_back({i-1, 0});
  }
  ```

### Guchenxi0971（4.5星）  
- **亮点**：明确将答案拆分为前缀和与损失，理论推导清晰  
- **关键公式**：  
  ```
  ans = max(sum[i] - dis[i])
  ```

### zhm080507（4星）  
- **亮点**：完整包含建图与Dijkstra实现，适合快速参考  

---

## 最优思路提炼  

**关键技巧**：  
1. **问题转化**：将每个决策转化为图的边权问题  
2. **损失最小化**：将最大化得分转化为最小化跳过的分数总和  
3. **前缀和优化**：利用前缀和快速计算总分，避免重复求和  

---

## 同类题目推荐  
1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)  
2. [P1354 房间最短路问题](https://www.luogu.com.cn/problem/P1354)  
3. [P4568 飞行路线](https://www.luogu.com.cn/problem/P4568)  

---

## 个人心得摘录  
> "赛时的我还傻傻地写了个前缀优化建图，赛后才想起来根本不需要" —— 提醒优先考虑最直观的建模方式  

---

## 可视化设计（复古像素版）  

**实现要点**：  
```javascript
// 伪代码示例
class PixelVisualizer {
  constructor(nodes) {
    this.grid = new CanvasGrid(16, 16); // 16x16像素块
    this.nodes = nodes.map((_,i) => 
      new PixelNode(i, 8-bit色彩[i%16])
    );
  }
  
  drawEdge(from, to, color) {
    this.grid.drawLine(from*8, to*8, color); 
    if(color === GREEN) playSound('blip.wav');
  }
  
  dijkstraStep() {
    let u = priorityQueue.pop();
    this.highlightNode(u, RED); 
    // ...更新相邻节点逻辑
  }
}
```

**交互设计**：  
- **方向键**：控制算法执行速度  
- **A键**：切换自动播放模式  
- **BGM**：8-bit风格循环音乐  
- **得分系统**：每找到一个新的最优路径获得10分  

---

## 核心代码实现  
```cpp
void solve() {
  int n; cin >> n;
  vector<ll> a(n+1), sum(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    sum[i] = sum[i-1] + a[i];
  }
  
  vector<vector<pair<int,int>>> g(n+1);
  for(int i=1; i<=n; i++) {
    int b; cin >> b;
    g[i].emplace_back(b, a[i]);
    if(i > 1) g[i].emplace_back(i-1, 0);
  }

  priority_queue<pll> pq;
  vector<ll> dis(n+1, LLONG_MAX);
  pq.push({0, 1});
  dis[1] = 0;
  
  while(!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if(-d > dis[u]) continue;
    for(auto [v, w] : g[u]) {
      if(dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pq.push({-dis[v], v});
      }
    }
  }

  ll ans = 0;
  for(int i=1; i<=n; i++)
    ans = max(ans, sum[i] - dis[i]);
  cout << ans << "\n";
}
```

---
处理用时：79.73秒