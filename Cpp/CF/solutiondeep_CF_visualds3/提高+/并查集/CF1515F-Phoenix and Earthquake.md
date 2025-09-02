# 题目信息

# Phoenix and Earthquake

## 题目描述

Phoenix's homeland, the Fire Nation had $ n $ cities that were connected by $ m $ roads, but the roads were all destroyed by an earthquake. The Fire Nation wishes to repair $ n-1 $ of these roads so that all the cities are connected again.

The $ i $ -th city has $ a_i $ tons of asphalt. $ x $ tons of asphalt are used up when repairing a road, and to repair a road between $ i $ and $ j $ , cities $ i $ and $ j $ must have at least $ x $ tons of asphalt between them. In other words, if city $ i $ had $ a_i $ tons of asphalt and city $ j $ had $ a_j $ tons, there would remain $ a_i+a_j-x $ tons after repairing the road between them. Asphalt can be moved between cities if the road between them is already repaired.

Please determine if it is possible to connect all the cities, and if so, output any sequence of roads to repair.

## 说明/提示

In the first example, the roads are repaired in the following order:

- Road $ 3 $ is repaired, connecting cities $ 3 $ and $ 4 $ . City $ 4 $ originally had $ 4 $ tons of asphalt. After this road is constructed, $ 3 $ tons remain.
- Road $ 2 $ is repaired, connecting cities $ 2 $ and $ 3 $ . The asphalt from city $ 4 $ can be transported to city $ 3 $ and used for the road. $ 2 $ tons remain.
- Road $ 1 $ is repaired, connecting cities $ 1 $ and $ 2 $ . The asphalt is transported to city $ 2 $ and used for the road. $ 1 $ ton remain.
- Road $ 4 $ is repaired, connecting cities $ 4 $ and $ 5 $ . The asphalt is transported to city $ 4 $ and used for the road. No asphalt remains.

 All the cities are now connected.In the second example, cities $ 1 $ and $ 2 $ use all their asphalt together to build the road. They each have $ 1 $ ton, so together they have $ 2 $ tons, which is enough.

In the third example, there isn't enough asphalt to connect cities $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
5 4 1
0 0 0 4 0
1 2
2 3
3 4
4 5```

### 输出

```
YES
3
2
1
4```

## 样例 #2

### 输入

```
2 1 2
1 1
1 2```

### 输出

```
YES
1```

## 样例 #3

### 输入

```
2 1 2
0 1
1 2```

### 输出

```
NO```

## 样例 #4

### 输入

```
5 6 5
0 9 4 0 10
1 2
1 3
2 3
3 4
1 4
4 5```

### 输出

```
YES
6
4
1
2```

# AI分析结果


### 💡 Kay的C++算法解析：Phoenix and Earthquake 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：贪心策略 + 生成树遍历 (DFS/BFS)  
🗣️ **初步分析**：
> 解决本题的关键在于**动态资源管理**与**拓扑顺序决策**。想象你是一位城市规划师，需要在沥青资源有限的情况下修复道路网络，每次修路需消耗固定资源$x$吨。核心挑战在于：如何安排修路顺序，使每次修路时相邻区域资源总和足够？  
> - **核心思路**：证明当总资源$≥(n-1)x$时，任意生成树均存在合法修路顺序（数学归纳法）。通过DFS遍历生成树，动态合并资源充足的节点（优先处理），暂存资源不足的边（最后处理）。  
> - **可视化设计**：动画将高亮当前DFS节点、资源合并过程（如像素方块融合），用绿色/红色区分"立即修路"和"暂缓修路"的边，音效标记资源增减（"叮"表示成功合并，"嘟"表示资源不足）。  
> - **复古游戏化**：采用8-bit像素风格，城市化为彩色方块，控制面板含单步/自动模式，背景音乐为循环芯片音乐，资源充足时触发"胜利音效"。

---

#### 2. 精选优质题解参考
**题解一（ix35）**  
* **点评**：思路清晰度满分！用严谨的归纳法证明充要条件，DFS后序遍历逻辑直白（子→父处理）。代码规范（变量名`a[u]`、`ans[]`含义明确），边界处理严谨（根节点跳过）。亮点在于**双队列存储策略**（队列存立即处理边，栈存暂缓边），实践价值极高，可直接用于竞赛。  

**题解二（whiteqwq）**  
* **点评**：代码简洁性突出！仅用**单数组+双指针**实现顺序管理（`h`指针向前存资源充足边，`tt`指针向后存不足边）。DFS动态更新`a[u]`的逻辑干净利落，避免冗余数据结构。虽未显式检查连通性（题目保证连通），但核心算法实现高效，适合初学者学习。  

**题解三（ListenSnow）**  
* **点评**：算法有效性典范！精炼的11行DFS核心代码，用`L`、`R`指针模拟双端队列。亮点在于**隐式栈处理**（不需显式栈结构），资源合并公式`a[u] += a[v] - x`直观体现贪心本质，边界控制严谨（`vis`数组防环）。  

---

#### 3. 核心难点辨析与解题策略
1. **难点1：如何证明总资源≥(n-1)x时必有解？**  
   * **分析**：需用数学归纳法+反证法。假设所有边资源不足，则总和$<(n-1)x$（与条件矛盾）。优质题解通过"最大点+相邻边"推导矛盾（参考Mr_Wu题解）。  
   * 💡 **学习笔记**：鸽巢原理是证明贪心可行性的利器！  

2. **难点2：DFS中资源合并顺序为何影响结果？**  
   * **分析**：必须自底向上（叶子→根）处理！先递归子节点确保局部资源正确聚合，再判断父边。若顺序颠倒（如先处理父边），资源计算会错误。  
   * 💡 **学习笔记**：树形问题中，后序遍历≈动态规划的"自底向上"阶段。  

3. **难点3：为何用双队列管理修路顺序？**  
   * **分析**：资源充足的边立即处理（保证后续操作资源充足），不足的边暂存。后进先出（栈）确保暂存边最后处理（此时全局资源已集中）。  
   * 💡 **学习笔记**：双端队列是处理混合时序问题的瑞士军刀！  

##### ✨ 解题技巧总结
- **技巧1：生成树转化** → 将图问题降维到树结构，简化依赖关系。  
- **技巧2：后序贪心** → 子节点处理完毕后再决策父边，保证局部最优。  
- **技巧3：资源接力** → 合并后更新父节点资源 (`a[u] += a[v]-x`)，实现资源传递。  

---

#### 4. C++核心代码实现赏析
**通用核心实现（综合优质题解）**  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
vector<pair<int, int>> G[N];
int n, m, x, a[N], ans[N], L, R;
bool vis[N];
long long sum;

void dfs(int u) {
    vis[u] = true;
    for (auto [v, id] : G[u]) {
        if (vis[v]) continue;
        dfs(v);
        if (a[u] + a[v] >= x) {  // 资源充足：立即处理
            a[u] += a[v] - x;
            ans[L++] = id;      // 加入队列前部
        } else {
            ans[R--] = id;      // 加入队列后部（逆序）
        }
    }
}

int main() {
    cin >> n >> m >> x;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back({v, i}); G[v].push_back({u, i});
    }
    if (sum < 1LL*(n-1)*x) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    L = 1; R = n - 1;  // 双指针初始化
    dfs(1);
    for (int i = 1; i < n; i++) cout << ans[i] << "\n";
}
```
**代码解读概要**：  
1. 检查总资源与连通性（输入保证连通）  
2. DFS遍历生成树：递归子节点 → 判断资源 → 更新父节点资源  
3. 双指针`L`、`R`分别管理"立即处理"和"暂缓处理"的边  

**题解一（ix35）片段赏析**  
```cpp
// 递归后处理父边（关键！）
if (u == 1) return;  // 跳过根节点
if (a[u] >= x) {     // 资源充足
    a[fa] += a[u] - x;
    ans[++cnt] = id;  // 加入队列
} else {
    ans[--cnt2] = id; // 加入栈
}
```
**学习笔记**：递归后序确保子节点全处理完！根节点无父边需跳过。  

**题解三（ListenSnow）片段赏析**  
```cpp
// 双指针实现顺序管理
if (a[u] + a[v] >= x) {
    a[u] += a[v] - x;  // 资源合并
    ans[L++] = id;     // 前向存储
} else {
    ans[R--] = id;     // 后向存储
}
```
**学习笔记**：单数组`ans` + 指针移动 → 极致空间优化！  

---

#### 5. 算法可视化：像素动画演示  
**主题**：8-bit城市规划师  
**核心演示**：生成树DFS遍历 + 动态资源合并  

1. **场景初始化**  
   - 像素网格（FC风格），城市=彩色方块（标资源值），边=连线  
   - 控制面板：开始/暂停、单步、速度滑块  

2. **DFS执行阶段**  
   ```mermaid
   graph LR
   A[当前节点闪烁] --> B[递归子节点]
   B --> C{资源≥x？}
   C -->|是| D[绿色高亮边<br>“叮”音效<br>方块融合]
   C -->|否| E[红色高亮边<br>“嘟”音效<br>边入栈区]
   ```

3. **资源合并动效**  
   - 子节点方块滑向父节点 → 融合为新方块 → 显示`a[u]+a[v]-x`  
   - 资源充足：融合时迸发星星特效 + 上扬音效  

4. **顺序演示**  
   - 先按序播放队列中的边（绿色）  
   - 再逆序播放栈中的边（红色）→ 最后触发"胜利BGM"  

---

#### 6. 拓展练习与相似问题
1. **洛谷P1111**：修复公路 → 基础连通性判断  
2. **洛谷P3366**：最小生成树 → 贪心选边实践  
3. **洛谷P1967**：货车运输 → 最大生成树应用  

---

#### 7. 学习心得与经验分享
> **参考经验**：  
> "DFS递归顺序是核心！我调试时发现若先处理父边，资源计算全乱。必须确保子节点处理完再更新父节点。"  
>   
> **Kay点评**：  
> 这是深度优先遍历的经典陷阱！递归后序处理（子→父）才能保证子问题完全解决，类似动态规划的记忆化搜索。  

--- 
**让我们在像素城市的资源管理中感受算法魅力吧！** 🚀

---
处理用时：202.31秒