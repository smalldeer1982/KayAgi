# 题目信息

# 「KDOI-04」挑战 NPC Ⅲ

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/zn5t5x28.png)

## 题目描述

小 S 有一个伟大的梦想：证明 $\text{P}=\text{NP}$。

有一天，他得知一般图最大独立集是 NPC 问题后，决定解决他。

当然小 S 太菜了，解决不了，于是求助于你：

> 给出一个含有 $n$ 个顶点，$m$ 条边的无向图 $G$，求 $G$ 中大小恰好为 $n-k$ 的独立集的数量。由于答案可能很大，请将其对 $998~244~353$ 取模。

小 S 不喜欢多测，因为他在 NOIp 中因为多测挂分，所以本题包含多组测试数据。

## 说明/提示

**【样例解释】**

对于第 $1,2$ 组测试数据，图是完全图，容易发现，完全图的最大独立集为 $1$，并且每一个顶点都单独构成一个独立集。因此第 $1$ 组测试数据的答案为 $0$，第 $2$ 组测试数据的答案为 $4$。

对于第 $3$ 组测试数据，该组数据中给出的无向图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/abt8ho3b.png)

其中，所有大小为 $3$ 的独立集为：

+ $\{2,4,8\}$；
+ $\{2,3,7\}$；
+ $\{3,4,6\}$；
+ $\{2,4,6\}$；
+ $\{1,4,6\}$；
+ $\{2,3,6\}$；
+ $\{1,4,5\}$；
+ $\{2,3,4\}$。

**【数据范围】**

**本题采用捆绑测试。**

![数据范围](https://cdn.luogu.com.cn/upload/image_hosting/p3jwdqp3.png)

对于 $100\%$ 的数据，保证 $1\leq n\leq10^5$，$0\le m\le 10^5$，$0\leq k\leq \min(n-1,18)$，$1\leq T\leq 10^{4}$，$\sum n,\sum m\leq10^6$。

并且对于每个测试点保证：

设 $K=\max k$，即该测试点中所有 $k$ 的最大值，

+ 若 $K\ge 17$，则 $T=1$；
+ 若 $K\ge 15$，则 $T\le 3$；
+ 若 $K\ge 10$，则 $T\le 5$；
+ 若 $K\ge 5$，则 $T\le 300$。


## 样例 #1

### 输入

```
3
4 6 1
1 2
1 3
1 4
2 3
2 4
3 4
4 6 3
1 2
1 3
1 4
2 3
2 4
3 4
8 13 5
1 2
7 8
1 3 
2 5
3 8
6 8
4 7
5 6
5 7
5 8
6 7
1 8
3 5```

### 输出

```
0
4
8```

# AI分析结果



## 唯一算法分类
**搜索与剪枝**

---

## 综合分析与结论

### 题目核心思路
1. **问题转化**：求大小为 `n-k` 的独立集等价于求大小为 `k` 的点覆盖集
2. **关键性质**：度数超过 `k` 的点必须被选入点覆盖集（否则无法覆盖其所有边）
3. **剪枝优化**：
   - 预处理所有度数 >k 的点后，剩余边数不超过 `k²`（否则无解）
   - 用 DFS 处理剩余边，每次选择一条未覆盖的边，分支处理选两端点的三种情况

### 算法流程可视化设计
1. **预处理阶段**：
   - 高亮度数 >k 的节点，标记为“必选”状态
   - 动态更新相邻节点度数（删除已覆盖边）
2. **DFS 分支阶段**：
   - 当前未覆盖边用红色高亮
   - 分支选择时：
     - 选左端点：蓝色标记左节点，绿色标记右节点为“禁止选”
     - 选右端点：蓝色标记右节点，绿色标记左节点
     - 选两个端点：蓝色标记双节点
3. **回溯状态恢复**：
   - 用灰色渐变动画表示状态撤销
4. **组合数计算阶段**：
   - 剩余可选节点用黄色高亮，显示组合数公式 `C(剩余节点数, 剩余需选数)`

### 复古像素化实现方案
1. **视觉设计**：
   - 节点：8-bit 风格的圆形像素块（直径 16px）
   - 边：低分辨率线段（带抖动效果）
   - 状态标记：必选（红色闪烁）、已选（蓝色）、禁止选（绿色）
2. **音效设计**：
   - 分支选择：8-bit 短音效（类似 FC 跳跃音）
   - 找到解：经典 FC 过关音效
   - 回溯：低音“嘟嘟”声
3. **自动演示模式**：
   - 用队列记录 DFS 路径，自动播放分支过程
   - 支持暂停查看当前状态参数（剩余边数、已选点数）

---

## 题解清单（评分 ≥4星）

### 1. Alex_Wei（5星）
- **核心亮点**：
  - 精确处理重边与度数动态更新
  - 使用 `ban` 数组标记节点状态（0-未定，1-必选，2-禁止选）
  - 剪枝条件 `buc.size() > k*(k - cnt)` 优化显著
- **代码简析**：
  ```cpp
  void dfs(int rest, int cur) {
    if(cur > k) return;
    int e = -1;
    // 找第一条未覆盖边
    for(auto it : buc) if(ban[u[it]] != 1 && ban[v[it]] != 1) { e = it; break; }
    if(e == -1) { // 所有边已覆盖
      ans = (ans + bin(n - cnt, k - cur)) % mod;
      return;
    }
    // 分支处理三种选择情况
    int &x = ban[u[e]], &y = ban[v[e]];
    if(x == 0 && y == 0) {
      x = 1, y = 1; dfs(rest - 2, cur + 2); // 选两端
      x = 1, y = 2; dfs(rest - 2, cur + 1); // 选左禁右
      x = 2, y = 1; dfs(rest - 2, cur + 1); // 选右禁左
      x = y = 0; // 回溯
    }
  }
  ```

### 2. _Diu_（4.5星）
- **核心亮点**：
  - 动态维护度数最大点（优先队列实现）
  - 组合数预处理优化计算
- **关键代码**：
  ```cpp
  void dfs(int x, int num) {
    if(s.empty() || s.begin()->first == 0) { // 无未覆盖边
      ans = (ans + C[num][x]) % p;
      return;
    }
    int t = s.begin()->second; // 取度数最大点
    erase(t); dfs(x-1, num-1); insert(t); // 选该点
    if(d[t] > x || x == num) return;
    // 不选该点，需选其所有邻居
    int st[K], tp = 0;
    for(int y : g[t]) if(!vis[y]) erase(y), st[++tp] = y;
    dfs(x - tp, num - tp - 1);
    for(int i = tp; i >= 1; i--) insert(st[i]); // 回溯
  }
  ```

### 3. Jorisy（4星）
- **核心亮点**：
  - 状态压缩清晰（`a[i]` 表示节点状态）
  - 分支逻辑完整覆盖所有可能情况
- **解决难点**：
  ```cpp
  if(a_u == 0 && a_v == 0) {
    a_u = a_v = 1; dfs(x+2, r-2); // 选两端
    a_u = 1, a_v = 2; dfs(x+1, r-2); // 选左禁右
    a_u = 2, a_v = 1; dfs(x+1, r-2); // 选右禁左
  }
  ```

---

## 同类型题目推荐
1. **P1979 华容道**（BFS+剪枝）
2. **P1074 靶形数独**（回溯+优先级剪枝）
3. **P1120 小木棍**（DFS+强剪枝）

---

## 个人心得摘录
> "月赛快结束时听说这题难，仔细分析后发现关键在于动态处理度数大的点。回溯时要注意点的删除与恢复顺序，否则会破坏图的结构。预处理组合数能大幅提升计算效率，这也是本题时间优化的关键。" —— _Diu_

---

## 算法核心代码（Alex_Wei 解法）
```cpp
// 预处理必选点
for(int i = 1; i <= n && cnt <= k; i++) {
  if(e[i].size() > k - cnt) {
    ban[i] = 1, cnt++;
    for(int it : e[i]) e[it].erase(i); // 删除关联边
  }
}
// DFS 处理剩余边
void dfs(int rest, int cur) {
  if(cur > k) return;
  int e = -1;
  for(auto it : buc) // 找第一条未覆盖边
    if(ban[u[it]] != 1 && ban[v[it]] != 1) { e = it; break; }
  if(e == -1) { // 计算组合数
    ans = (ans + bin(n - cnt, k - cur)) % mod;
    return;
  }
  // 分支处理三种情况
  int &x = ban[u[e]], &y = ban[v[e]];
  if(x == 0 && y == 0) {
    x = 1, y = 1; dfs(rest - 2, cur + 2);
    x = 1, y = 2; dfs(rest - 2, cur + 1);
    x = 2, y = 1; dfs(rest - 2, cur + 1);
    x = y = 0; // 回溯恢复状态
  }
}
```

---

## 可视化代码片段（Canvas 动画核心）
```javascript
// 绘制节点（8-bit 风格）
function drawNode(ctx, x, y, state) {
  ctx.fillStyle = stateColors[state]; // 红/蓝/绿/灰
  ctx.beginPath();
  ctx.arc(x, y, 8, 0, Math.PI*2);
  ctx.fill();
  ctx.strokeStyle = '#000';
  ctx.stroke();
}

// DFS 动画步骤
function dfsStep(edges) {
  let currentEdge = edges.find(e => !isCovered(e));
  if(!currentEdge) { // 找到解，播放音效
    playSound('success');
    drawCombinatorics();
    return;
  }
  highlightEdge(currentEdge); // 红色高亮当前边
  // 分支处理
  setTimeout(() => {
    selectNode(currentEdge.u); // 选左端点
    dfsStep(edges);
    deselectNode(currentEdge.u);
    selectNode(currentEdge.v); // 选右端点
    dfsStep(edges);
    deselectNode(currentEdge.v);
  }, 500);
}
```

---
处理用时：83.50秒