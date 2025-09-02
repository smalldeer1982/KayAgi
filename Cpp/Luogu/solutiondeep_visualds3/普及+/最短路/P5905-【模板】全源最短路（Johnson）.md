# 题目信息

# 【模板】全源最短路（Johnson）

## 题目描述

给定一个包含 $n$ 个结点和 $m$ 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。

注意：

1. 边权**可能**为负，且图中**可能**存在重边和自环；

2. 部分数据卡 $n$ 轮 SPFA 算法。



## 说明/提示

【样例解释】

左图为样例 $1$ 给出的有向图，最短路构成的答案矩阵为：

```
0 4 11 8 11 
1000000000 0 7 4 7 
1000000000 -5 0 -3 0 
1000000000 -2 5 0 3 
1000000000 -1 4 1 0 
```

右图为样例 $2$ 给出的有向图，红色标注的边构成了负环，注意给出的图不一定连通。

![](https://cdn.luogu.com.cn/upload/image_hosting/7lb35u4u.png)

【数据范围】

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^3,\ \ 1\leq m\leq 6\times 10^3,\ \ 1\leq u,v\leq n,\ \ -3\times 10^5\leq w\leq 3\times 10^5$。

对于 $20\%$ 的数据，$1\leq n\leq 100$，不存在负环（可用于验证 Floyd 正确性）

对于另外 $20\%$ 的数据，$w\ge 0$（可用于验证 Dijkstra 正确性）

upd. 添加一组 Hack 数据：针对 SPFA 的 SLF 优化

## 样例 #1

### 输入

```
5 7
1 2 4
1 4 10
2 3 7
4 5 3
4 2 -2
3 4 -3
5 3 4```

### 输出

```
128
1000000072
999999978
1000000026
1000000014
```

## 样例 #2

### 输入

```
5 5
1 2 4
3 4 9
3 4 -3
4 5 3
5 3 -2```

### 输出

```
-1```

# AI分析结果


# 💡 Kay的C++算法解析：Johnson全源最短路 深入学习指南 💡

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`图论/全源最短路`  

🗣️ **初步分析**：
> 解决"Johnson全源最短路"问题，核心在于理解**势能转换**思想。想象每条边有一个"高度差"，通过调整高度使所有下坡路（负权边）变成上坡路（非负权边）。  
> - 关键思路：添加虚拟节点计算势能h[i]，将边权w(u,v)调整为w(u,v)+h[u]-h[v]消除负权，再用Dijkstra高效求解
> - 核心难点：负环检测（SPFA）、势能转换证明、多源Dijkstra实现
> - 可视化设计：将虚拟节点设为"能量源"，节点高度随h[i]动态变化，负权边转正时显示数值变化，Dijkstra执行时显示"探索者"在高度图上爬坡

---

## 2. 精选优质题解参考

**题解一：(来源：StudyingFather)**
* **点评**：该题解在算法推导上极为严谨（如用物理势能解释边权转换），代码结构规范（SPFA+Dijkstra分离），变量命名清晰（h[i]表示势能）。亮点在于：
  1. 完整证明转换后边权非负（三角形不等式）
  2. 处理路径回溯时巧妙抵消势能差
  3. 空间优化避免冗余数组
  实践价值高，可直接用于竞赛

**题解二：(来源：Mine_King)**
* **点评**：提供被Hack后的修正方案，强调边界处理（虚拟节点入队次数>n判负环）。亮点：
  1. 详细图解说明转换前后路径变化
  2. 堆优化SPFA提高检测效率
  3. 完整注释帮助理解关键步骤

**题解三：(来源：D2T1)**
* **点评**：代码最简洁高效（<100行），突出核心逻辑。亮点：
  1. 严格复杂度分析（O(nm + n·mlogn)）
  2. 模块化设计（spfa/dijkstra独立函数）
  3. 完整势能转换公式注释

---

## 3. 核心难点辨析与解题策略

1.  **负环检测与处理**
    * **分析**：SPFA中虚拟节点0的入队次数>n即存在负环。优质解常用队列优化+计数数组，注意虚拟节点需连接所有真实节点
    * 💡 **学习笔记**：虚拟节点是检测全图负环的关键桥梁

2.  **势能转换的数学证明**
    * **分析**：基于不等式h[v]≤h[u]+w(u,v)，转换后边权w'=w+h[u]-h[v]≥0。路径总长变化仅与端点势能相关（+h[s]-h[t]）
    * 💡 **学习笔记**：势能差在路径累加中抵消，如同海拔高度不影响两地水平距离

3.  **高效实现多源最短路**
    * **分析**：使用priority_queue实现堆优化Dijkstra。注意：
      - 转换后边权需存入邻接表
      - 结果需还原：dist[u][v] = dist'[u][v] - h[u] + h[v]
    * 💡 **学习笔记**：优先队列的operator<重载决定节点处理顺序

### ✨ 解题技巧总结
- **虚拟节点法**：通过添加节点统一处理全图性质（负环/势能）
- **模块化编程**：分离SPFA和Dijkstra逻辑，提高可读性
- **边界防御**：对未连通节点设INF=1e9，避免溢出
- **势能预计算**：先SPFA求h[i]再转换边权，确保Dijkstra前提

---

## 4. C++核心代码实现赏析

**本题通用核心C++实现参考**
* **说明**：综合优质题解的最简实现，包含负环检测、势能转换、多源Dijkstra
```cpp
#include <cstring>
#include <queue>
#define N 3005
#define ll long long
const ll INF=1e9;
using namespace std;

struct Edge{ int v,w; };
vector<Edge> G[N];
ll h[N], dist[N]; // 势能数组和距离数组
int cnt[N], n, m; // SPFA计数

bool spfa() { // 负环检测+势能计算
    queue<int> q;
    memset(h, 0x3f, sizeof(h));
    h[0]=0; q.push(0);
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(auto [v,w]: G[u]) 
            if(h[v] > h[u]+w) {
                h[v]=h[u]+w;
                if(++cnt[v] > n) return false; // 负环检测
                q.push(v);
            }
    }
    return true;
}

void dijkstra(int s) { // 堆优化Dijkstra
    priority_queue<pair<ll,int>> pq;
    memset(dist, 0x3f, sizeof(dist));
    dist[s]=0; pq.push({0,s});
    while(!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if(-d != dist[u]) continue; // 旧节点跳过
        for(auto [v,w]: G[u]) {
            ll nd=dist[u]+w+h[u]-h[v]; // 调整后边权
            if(dist[v] > nd) {
                dist[v]=nd;
                pq.push({-nd, v}); // 负号实现最小堆
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for(int u,v,w; m--;) {
        cin >> u >> v >> w;
        G[u].push_back({v,w});
    }
    // 添加虚拟节点0
    for(int i=1; i<=n; i++) G[0].push_back({i,0});
    
    if(!spfa()) { cout << -1; return 0; }
    
    // 边权转换
    for(int u=1; u<=n; u++)
        for(auto &e: G[u]) 
            e.w += h[u]-h[e.v]; // 势能调整
    
    // 全源最短路
    for(int i=1; i<=n; i++) {
        dijkstra(i);
        ll ans=0;
        for(int j=1; j<=n; j++) 
            ans += (dist[j]<INF/2) ? j*(dist[j]-h[i]+h[j]) : j*INF;
        cout << ans << endl;
    }
}
```

**题解一核心片段赏析**
```cpp
// SPFA势能计算（StudyingFather）
bool spfa(int s) {
    queue<int> q;
    memset(h,63,sizeof(h));
    h[s]=0, vis[s]=1; q.push(s);
    while(!q.empty()) {
        int u=q.front(); q.pop(); vis[u]=0;
        for(int i=head[u];i;i=e[i].next) {
            int v=e[i].v;
            if(h[v]>h[u]+e[i].w) {
                h[v]=h[u]+e[i].w;
                if(!vis[v]) {
                    vis[v]=1, q.push(v);
                    if(++t[v]==n+1) return 0; // 负环判断
                }
            }
        }
    }
    return 1;
}
```
* **亮点**：严格遵循SPFA模板，vis数组避免重复入队
* **代码解读**：
  - `h[v]>h[u]+e[i].w`触发松弛操作
  - `t[v]`计数确保及时检测负环
  - `vis[]`优化减少无效计算
* 💡 **学习笔记**：SPFA队列管理是效率关键

---

## 5. 算法可视化：像素动画演示

### 像素探险家之旅：势能转换全记录
**设计思路**：采用8位机风格，将节点绘为像素方块（不同颜色区分状态），边权用动态数字显示。通过"高度差"视觉化势能概念。

**动画帧步骤**：
1. **初始化场景**（复古绿背景）：
   - 创建虚拟节点0（蓝色闪光方块）
   - 灰色连线连接0与所有节点（边权0）

2. **SPFA执行过程**：
   - 队列可视化（底部像素条）
   - 节点入队时变红，出队复原
   - 势能h[i]实时显示在节点上方
   - 检测负环时全屏红光闪烁

3. **边权转换特效**：
   - 负权边（红色）→ 调整后（绿色）
   - 公式浮动显示：`w_new = w + h[u]-h[v]`
   - 音效：负转正时"叮"声

4. **Dijkstra探索**：
   - 像素小人从源点出发
   - 优先队列显示为背包中的排序节点
   - 路径延伸伴随"脚步声"音效
   - 到达终点播放胜利旋律

**交互控制**：
- 步进/暂停：空格键
- 速度调节：方向键←→
- 模式切换：Tab键（单源/全源视角）

**技术实现**：
```javascript
// 伪代码示例
class PixelAnimator {
  constructor(graph) {
    this.nodes = graph.nodes.map(createPixelSprite); // 创建像素节点
    this.edges = graph.edges.map(createLine); 
    this.queueView = new QueueVisualizer(); // SPFA队列动画
  }
  
  runSPFA() {
    this.playSound('spfa_start');
    while(!queue.empty()) {
      const u = queue.pop();
      u.sprite.flash('yellow'); // 当前处理节点高亮
      for(const edge of u.edges) {
        if(relax(edge)) { // 松弛成功
          edge.lineColor = 'green';
          playSound('relax');
        }
      }
    }
  }
}
```

---

## 6. 拓展练习与相似问题

### 通用技巧迁移
Johnson的势能思想可用于：
1. 网络流中的Primal-Dual算法
2. 差分约束系统求解
3. 带负权费用流的处理

### 推荐练习（洛谷）：
1. **P3385 【模板】负环**  
   → 巩固SPFA负环检测技巧
2. **P4779 【模板】单源最短路径**  
   → 熟练掌握堆优化Dijkstra
3. **P5960 【模板】差分约束**  
   → 应用势能思想转化不等式

---

## 7. 学习心得与经验分享

> **参考经验**（来自Mine_King）：  
> "被Hack数据卡后意识到：虚拟节点0的松弛必须严格遵循SPFA逻辑，入队次数>n而非>n-1"

> **点评**：调试负环检测时，注意图结构变化（添加节点后总节点数=n+1）。建议：
> 1. 打印松弛过程验证势能计算
> 2. 极限测试（单节点负环/大权重负边）
> 3. 用小规模图人工演算

---

通过本次分析，我们深入理解了Johnson算法如何巧妙转化负权图，以及SPFA和Dijkstra的协同工作。记住：势能转换如同给地图赋予海拔，让Dijkstra能在"上坡世界"安全航行。下次遇到负权图时，不妨构建你的虚拟能量源吧！💪

---
处理用时：143.18秒