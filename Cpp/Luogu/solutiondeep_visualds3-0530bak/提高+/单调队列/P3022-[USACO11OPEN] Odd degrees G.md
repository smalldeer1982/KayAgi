# 题目信息

# [USACO11OPEN] Odd degrees G

## 题目描述

奶牛们正在遭受入侵！它们的共和国由 $N$ 个城镇组成（$1 \leq N \leq 50,000$），这些城镇通过 $M$ 条无向路径连接（$1 \leq M \leq 100,000$），每条路径连接两个城镇 $A_i$ 和 $B_i$（$1 \leq A_i \leq N$；$1 \leq B_i \leq N$；$A_i 
eq B_i$；不会出现重复路径）。然而，共和国不一定是连通的——可能存在无法通过路径到达彼此的城镇对。

奶牛们知道入侵者计划对它们共和国内的每一条路径进行清点，所以它们愿意关闭各种路径，以使入侵者的工作尽可能困难。

请帮助奶牛们找到一种关闭路径子集的方法，使得每个城镇连接的剩余路径数为奇数，或者确定不存在这样的子集。

例如，考虑以下的奶牛共和国：

1---2
\ /
3---4
如果我们保留路径 1-3、2-3 和 3-4，并移除路径 1-2，那么城镇 1、2 和 4 将成为正好一条路径的端点，而城镇 3 将成为三条路径的端点：

1   2
\ /
3---4

## 说明/提示

感谢 @cn：苏侨念 提供的 Special Judge（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 4 
1 2 
2 3 
3 1 
3 4 
```

### 输出

```
3 
2 
3 
4 
```

# AI分析结果



# 算法分类选择
图论 - 深度优先搜索（DFS）

---

## 题解思路、算法要点与解决难点

### 核心算法流程
1. **DFS后序遍历**：从任意未访问节点开始DFS，优先处理子节点，回溯时决定是否保留父边
2. **度数奇偶性维护**：
   - 统计子节点保留的边数（即递归返回true的次数）
   - 若保留边数为偶数，需保留父边使当前节点度数变为奇数
3. **连通块验证**：根节点无父边时，若需保留父边则无解

### 解决难点
1. **隐式度数统计**：通过递归返回值动态维护度数，无需显式计算
2. **多连通块处理**：独立处理每个连通块，自动验证奇偶性约束
3. **边标记收集**：在回溯过程中收集保留边的ID，保证输出顺序

### 关键数据结构
```cpp
struct Edge { int to, nxt, id; }; // 邻接表存储边及原始ID
vector<int> ans;                  // 保存保留边的ID
bool vis[N];                      // 访问标记数组
```

---

## 题解评分（≥4星）

### 4星题解：3493441984zz
**亮点**：
- 完整注释说明DFS过程
- 通过链式前向星高效存储边
- 样例模拟帮助理解回溯逻辑
**代码片段**：
```cpp
bool Dfs(int u) {
    vis[u] = 1;
    int du = 0;
    for(int i=head[u];i;i=edge[i].nxt) {
        int v = edge[i].to;
        if(vis[v]) continue;
        if(Dfs(v)) { // 子节点需要保留父边
            ++du;
            ans.push_back(edge[i].id);
        }
    }
    return (du%2 == 0); // 决定是否保留父边
}
```

### 4星题解：Dilute
**亮点**：
- 根节点特殊处理逻辑清晰
- 边ID压缩存储节省空间
- 排序输出符合题目要求
**核心判断**：
```cpp
if(Dfs(i, -1)) { // 根节点返回true说明度数不满足
    printf("-1");
    return 0;
}
```

### 4星题解：Fire_Raku
**亮点**：
- 生成树思想应用明确
- 度数和验证数学严谨
- 独立处理连通块
**数学验证**：
```cpp
if(连通块顶点数%2 != 0) 无解
```

---

## 最优思路提炼
**关键技巧**：
1. **后序决策**：子节点处理完毕后再决定父边取舍
2. **奇偶转换**：通过保留边数奇偶性动态调整度数
3. **根验证**：利用递归返回值隐式检查连通块顶点奇偶

**通用解法**：
```python
def dfs(u, parent_edge):
    visited[u] = True
    degree = 0
    for v in adj[u]:
        if not visited[v]:
            if dfs(v, current_edge):
                degree += 1
                keep_edge(current_edge)
    if parent_edge exists:
        return degree % 2 == 0  # 决定是否保留父边
    else:
        return degree % 2 != 0  # 根节点验证
```

---

## 同类型题目推荐
1. **P1341 无序字母对**（欧拉路径存在性）
2. **P1333 瑞瑞的木棍**（奇度顶点处理）
3. **P3520 [POI2011]SMI-Garbage**（环分解与度数控制）

---

## 可视化设计

### 算法动画方案
![DFS回溯过程可视化](https://i.imgur.com/ZjTQvG8.gif)
1. **节点状态**：
   - 白色：未访问
   - 蓝色：正在处理
   - 绿色：已处理
2. **边标记**：
   - 红色闪烁：正在决策是否保留
   - 金色：已保留边
3. **信息面板**：
   - 当前节点度数统计
   - 保留边数/总边数

### 复古游戏化设计
```javascript
// 伪代码示例
class PixelGraph {
    constructor() {
        this.nodes = []     // 8位风格节点位置
        this.edges = []     // 像素化连线
        this.sfx = {
            select: new Audio('blip.wav'),
            success: new Audio('win.wav')
        }
    }
    
    drawDFS(u) {
        this.nodes[u].color = BLUE
        this.edges.forEach(e => {
            if e.保留状态变化 {
                playSfx(this.sfx.select)
                e.color = GOLD
            }
        })
        if(u是根节点 && 验证失败) {
            playSfx(this.sfx.fail)
            screenShake()
        }
    }
}
```

---

## 核心代码实现
**DFS核心逻辑**：
```cpp
vector<int> ans;
vector<bool> vis;

bool dfs(int u, int parent_id) {
    vis[u] = true;
    int cnt = 0;
    for (auto [v, id] : adj[u]) {
        if (vis[v]) continue;
        if (dfs(v, id)) cnt++;
    }
    if (cnt % 2 == 0) {
        if (parent_id != -1) {
            ans.push_back(parent_id);
            return true;
        } else { // 根节点且需要保留不存在的父边
            return false; 
        }
    }
    return false;
}
```

**主流程**：
```cpp
for(int u = 1; u <= n; u++) {
    if(!vis[u]) {
        if(dfs(u, -1)) {
            cout << -1;
            return 0;
        }
    }
}
sort(ans.begin(), ans.end());
cout << ans.size() << "\n";
for(int id : ans) cout << id << "\n";
```

---
处理用时：110.58秒