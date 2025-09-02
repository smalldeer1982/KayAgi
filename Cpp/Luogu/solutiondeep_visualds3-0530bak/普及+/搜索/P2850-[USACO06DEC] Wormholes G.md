# 题目信息

# [USACO06DEC] Wormholes G

## 题目背景

[英文题面见此链接](https://www.luogu.com.cn/paste/mxuf6zpl)

## 题目描述

John 在他的农场中闲逛时发现了许多虫洞。虫洞可以看作一条十分奇特的有向边，并可以使你返回到过去的一个时刻（相对你进入虫洞之前）。

John 的每个农场有 $m$ 条小路（无向边）连接着 $n$ 块地（从 $1 \sim n$ 标号），并有 $w$ 个虫洞。

现在 John 希望能够从某块地出发，走过一条路径回到出发点，且同时也回到了出发时刻以前的某一时刻。请你告诉他能否做到。

## 说明/提示

#### 样例 2 解释

John 只需要沿着 $1 \rightarrow 2 \rightarrow 3 \rightarrow 1$ 的路径一直转圈即可，每转完一圈，时间就会减少一秒。

#### 数据范围与约定

对于 $100\%$ 的数据，$1 \le T \le 5$，$1 \le n \le 500$，$1 \le m \le 2500$，$1 \le w \le 200$，$1 \le p \le 10^4$。

## 样例 #1

### 输入

```
2
3 3 1
1 2 2
1 3 4
2 3 1
3 1 3
3 2 1
1 2 3
2 3 4
3 1 8```

### 输出

```
NO
YES```

# AI分析结果



---

## 算法分类
**其他搜索**（基于 SPFA 的 BFS/DFS 变形）

---

## 题解思路与难点对比

### 核心算法共性
所有题解均围绕**负环检测**展开，核心差异在于判环策略与搜索方式：
1. **Floyd 判环**（Drifting 题解）
   - 要点：通过动态规划求解所有点对最短路，若存在 `dis[i][i]<0` 则存在负环
   - 难点：O(n³) 复杂度，需卡常优化（如 register 变量、循环顺序优化）
2. **DFS 版 SPFA**（wjy666、Sakura_Peng 等）
   - 要点：递归松弛时若再次访问同一节点则判环
   - 难点：需维护访问状态数组，避免重复递归导致死循环
3. **BFS 版 SPFA**（ljcljc、dunko 等）
   - 要点：统计节点入队次数，若超过 n 次则判环
   - 难点：需处理重边与超级源点，队列性能影响较大
4. **Bellman-Ford**（动态WA、fuking 等）
   - 要点：n-1 次全局松弛后仍可松弛则判环
   - 难点：需存储所有边，无法利用邻接表加速

---

## 题解评分（≥4星）

### 1. wjy666 的 DFS 版 SPFA（4.5星）
- **亮点**：DFS 递归天然适合快速发现环，代码中 `fl[]` 数组精准控制递归路径
- **优化点**：每个节点作为起点独立判断，确保覆盖全图
- **代码片段**：
```cpp
void spfa(int k) {
    if (fl[k]) { flag = 1; return; }
    fl[k] = 1;
    for (auto e : mp[k]) {
        if (sum[e.nex] > e.dis + sum[k]) {
            sum[e.nex] = e.dis + sum[k];
            spfa(e.nex);
        }
    }
    fl[k] = 0;
}
```

### 2. Sakura_Peng 的超级源点（4.2星）
- **亮点**：引入虚拟节点连接所有真实节点，避免多次枚举起点
- **可视化价值**：超级源点（0 节点）与全图的连接关系可图形化展示
- **代码片段**：
```cpp
for(int i=1;i<=n;i++) cun(0,i,0); // 建立超级源点
spfa(0); // 仅需一次搜索
```

### 3. kczno1 的 BFS 理论分析（4.0星）
- **理论贡献**：对比 BFS/DFS 判环复杂度差异，指出 DFS 的时间优势
- **实践指导**：解释了为何 DFS 版 SPFA 在负环场景更高效

---

## 最优思路与技巧

### 关键优化技巧
1. **初始距离归零法**（EightSixSun 题解）
   ```cpp
   memset(dis, 0, sizeof(dis)); // 仅关注负权边变化
   ```
2. **递归路径标记**（wjy666 的 `fl[]` 数组）
   ```cpp
   fl[k] = 1; // 标记当前递归路径
   if (fl[e.nex]) flag = 1; // 发现环立即终止
   ```
3. **超级源点降维**（Sakura_Peng）
   - 将多源问题转化为单源问题，减少计算量 50%+

---

## 同类型题目推荐
1. [P3385 负环模板](https://www.luogu.com.cn/problem/P3385)  
   （DFS/BFS 版 SPFA 的直接应用）
2. [P2136 拉近距离](https://www.luogu.com.cn/problem/P2136)  
   （带权图的双向负环检测）
3. [P2868 观光奶牛](https://www.luogu.com.cn/problem/P2868)  
   （分数规划与负环结合）

---

## 可视化设计要点

### 8位像素风格演示
```javascript
// 示例：Canvas 绘制节点与边（伪代码）
const NODE_COLORS = {
    default: '#6B8CFF',
    active: '#FF5151',
    visited: '#4CAF50'
};

function drawNode(x, y, state) {
    ctx.fillStyle = NODE_COLORS[state];
    ctx.fillRect(x*50, y*50, 40, 40); // 像素方块式节点
}

// 音效触发逻辑
function playSound(type) {
    if(type === 'visit') new Audio('blip.wav').play();
    if(type === 'found') new Audio('success.wav').play();
}
```

### 动画控制逻辑
1. **步进模式**：按空格键单步执行松弛操作
2. **路径高亮**：当前访问节点显示红色，已访问显示绿色
3. **负环特效**：检测到环时，循环闪烁相关节点并播放胜利音效

---

## 核心代码实现（DFS 版 SPFA）
```cpp
bool spfa_dfs(int u) {
    vis[u] = true;
    for (Edge e : adj[u]) {
        if (dis[e.v] > dis[u] + e.w) {
            dis[e.v] = dis[u] + e.w;
            if (vis[e.v] || spfa_dfs(e.v)) 
                return true;
        }
    }
    vis[u] = false;
    return false;
}
// 调用方式：对每个节点i初始化dis后调用spfa_dfs(i)
```

---

## 总结结论
**DFS 版 SPFA 判负环**是该题最优解，兼顾代码简洁性与时间复杂度。其核心优势在于递归路径的自然回溯机制，能快速发现环路存在，配合超级源点技巧可进一步提升效率。可视化时应重点展示递归路径的生成与回溯过程，通过像素动画强化环路检测的直觉理解。

---
处理用时：72.31秒