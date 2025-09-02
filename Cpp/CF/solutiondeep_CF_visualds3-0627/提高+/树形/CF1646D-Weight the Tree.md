# 题目信息

# Weight the Tree

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . A tree is a connected undirected graph without cycles.

For each $ i=1,2, \ldots, n $ , let $ w_i $ be the weight of the $ i $ -th vertex. A vertex is called good if its weight is equal to the sum of the weights of all its neighbors.

Initially, the weights of all nodes are unassigned. Assign positive integer weights to each vertex of the tree, such that the number of good vertices in the tree is maximized. If there are multiple ways to do it, you have to find one that minimizes the sum of weights of all vertices in the tree.

## 说明/提示

This is the tree for the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646D/c1443959610684ba1c023451af2be26a243d7782.png) In this case, if you assign a weight of $ 1 $ to each vertex, then the good vertices (which are painted black) are $ 1 $ , $ 3 $ and $ 4 $ . It impossible to assign weights so that all vertices are good vertices. The minimum sum of weights in this case is $ 1+1+1+1=4 $ , and it is impossible to have a lower sum because the weights have to be positive integers.This is the tree for the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646D/5f2b683a0e657b99ca0eb99ee84a2529445c05d6.png) In this case, if you assign a weight of $ 1 $ to each vertex, then the good vertices (which are painted black) are $ 2 $ and $ 3 $ . It can be proven that this is an optimal assignment.

## 样例 #1

### 输入

```
4
1 2
2 3
2 4```

### 输出

```
3 4
1 1 1 1```

## 样例 #2

### 输入

```
3
1 2
1 3```

### 输出

```
2 3
1 1 1```

## 样例 #3

### 输入

```
2
1 2```

### 输出

```
2 2
1 1```

## 样例 #4

### 输入

```
9
3 4
7 6
2 1
8 3
5 6
1 8
8 6
9 6```

### 输出

```
6 11
1 1 1 1 1 1 1 3 1```

# AI分析结果



### 唯一算法分类  
树形动态规划

---

### 题解思路与算法要点  

#### 核心逻辑
1. **状态定义**：设 `f[u][0/1]` 表示以 u 为根的子树，u 不作为/作为好节点时的最大好节点数。对应 `g[u][0/1]` 记录最小权值和。
2. **转移方程**：
   - 若 u 是好节点（`f[u][1]`），则所有子节点必须不是好节点：`f[u][1] = Σf[v][0] + 1`
   - 若 u 不是好节点（`f[u][0]`），子节点可选最优状态：`f[u][0] = Σmax(f[v][0], f[v][1])`
3. **权值构造**：非好节点权值为 1，好节点权值为其度数（保证最小总和）

#### 解决难点
1. **相邻节点冲突**：通过树形 DP 状态设计保证相邻节点不同时为好节点
2. **最小权值构造**：在状态转移时同步维护权值和，当最大好节点数相同时选择更小权值
3. **特例处理**：n=2 时两个节点都可以是好节点（需特殊处理）

---

### 题解评分（≥4星）

1. **Zimo_666（5星）**
   - 亮点：双状态设计清晰，转移方程完整，代码可读性极佳
   - 核心代码：
     ```cpp
     f[u][1] += f[v][0];  // 父节点选则子节点不选
     if(f[v][0] == f[v][1]) 
         g[u][0] += min(g[v][0], g[v][1]); // 权值取小
     ```

2. **Duramente（5星）**
   - 亮点：使用 pair 同时处理最大数量和最小权值，代码简洁高效
   - 核心代码：
     ```cpp
     dp[u][1] = m_p(1, g[u].size()); // (数量, 权值)
     if(cmp(dp[v][0], dp[v][1])) // 比较函数处理最优选择
     ```

3. **文曲兔（4星）**
   - 亮点：详细数学证明相邻节点冲突，构造性证明最优权值方案
   - 关键证明：
     ```text
     假设相邻节点 u,v 同为好节点 → 推导出 w_u > w_v 且 w_v > w_u → 矛盾
     ```

---

### 最优思路提炼

1. **独立集模型**：将问题转化为求树的最大独立集（好节点不相邻）
2. **权值构造策略**：
   ```python
   if 节点u是好节点: 
       w[u] = degree(u)  # 最小满足条件的值
   else: 
       w[u] = 1          # 最小正整数
   ```
3. **双目标优化**：在树形 DP 中同时维护最大数量和最小权值

---

### 同类题型推荐

1. **P1352 没有上司的舞会**  
   （树形 DP 最大独立集基础模板）

2. **CF1324F Maximum White Subtree**  
   （树形 DP 维护双目标最优解）

3. **P2014 [CTSC1997] 选课**  
   （树形 DP 结合背包问题）

---

### 可视化算法演示设计

**核心动画流程**：
1. **树结构展示**：用嵌套方框表示树形结构，初始状态全灰
2. **状态转移演示**：
   - 点击节点时弹出状态面板显示 `f[u][0]`/`f[u][1]` 值
   - 用绿色高亮当前处理的子树根节点
3. **权值构造过程**：
   - 回溯时动态显示节点颜色变化（红色=好节点，蓝色=普通节点）
   - 在节点旁实时显示计算出的权值（如：红节点显示度数）

**复古像素风格实现**：
```javascript
// Canvas 绘制示例
function drawNode(x, y, state) {
  ctx.fillStyle = state === 'good' ? '#FF5555' : '#5555FF';
  ctx.fillRect(x-15, y-15, 30, 30); // 像素方块
  ctx.font = '8px "Press Start 2P"'; // 复古字体
  ctx.fillText(w[u], x-3, y+5);
}

// 音效触发
function playSound(type) {
  if(type === 'select') new Audio('blip.wav').play(); // 8-bit 音效
}
```

**自动演示模式**：
- 按空格键逐步执行 DP 过程
- 方向键控制演示速度
- 终局时播放胜利音效（8-bit 风格 MIDI）

---

### 关键代码实现

**状态转移核心逻辑**：
```cpp
void dfs(int u, int fa) {
  f[u][1] = 1;        // 选u时的好节点数
  g[u][1] = deg[u];    // 选u时的权值和
  g[u][0] = 1;         // 不选u时的权值和
  
  for(int v : G[u]) {
    if(v == fa) continue;
    dfs(v, u);
    
    // 选u则子节点必须不选
    f[u][1] += f[v][0];
    g[u][1] += g[v][0];
    
    // 不选u则子节点取最优
    if(f[v][0] > f[v][1] || (f[v][0]==f[v][1] && g[v][0]<g[v][1])) {
      f[u][0] += f[v][0];
      g[u][0] += g[v][0];
    } else {
      f[u][0] += f[v][1];
      g[u][0] += g[v][1];
    }
  }
}
```

**构造权值方案**：
```cpp
void build(int u, int fa, bool is_good) {
  w[u] = is_good ? deg[u] : 1;
  for(int v : G[u]) {
    if(v == fa) continue;
    build(v, u, !is_good); // 选父节点则子节点必须不选
  }
}
```

---

### 总结启示

1. **模型转换**：将看似复杂的约束转化为经典树形 DP 问题
2. **双目标处理**：在状态转移中同步维护多个优化目标
3. **构造性证明**：通过数学推导确定权值分配的最优策略

通过此题的深度分析，可掌握树形 DP 处理双目标优化问题的典型方法，以及如何通过数学推导辅助算法设计。

---
处理用时：80.84秒