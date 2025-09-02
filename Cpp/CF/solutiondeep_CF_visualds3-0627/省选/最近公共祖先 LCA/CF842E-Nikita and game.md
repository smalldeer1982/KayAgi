# 题目信息

# Nikita and game

## 题目描述

Nikita plays a new computer game. There are $ m $ levels in this game. In the beginning of each level a new class appears in the game; this class is a child-class of the class $ y_{i} $ (and $ y_{i} $ is called parent-class for this new class). Thus, the classes form a tree. Initially there is only one class with index $ 1 $ .

Changing the class to its neighbour (child-class or parent-class) in the tree costs $ 1 $ coin. You can not change the class back. The cost of changing the class $ a $ to the class $ b $ is equal to the total cost of class changes on the path from $ a $ to $ b $ in the class tree.

Suppose that at $ i $ -th level the maximum cost of changing one class to another is $ x $ . For each level output the number of classes such that for each of these classes there exists some other class $ y $ , and the distance from this class to $ y $ is exactly $ x $ .

## 样例 #1

### 输入

```
4
1
1
2
1
```

### 输出

```
2
2
2
3
```

## 样例 #2

### 输入

```
4
1
1
2
3
```

### 输出

```
2
2
2
2
```

# AI分析结果



**唯一算法分类**：树的直径动态维护

---

### **综合分析与结论**

**核心思路**  
题目要求动态维护树的直径端点数目。基于直径的交点性质（所有直径交于一点或一条边），维护两个集合 `S1` 和 `S2`，分别表示直径两端可能的端点。每次新增节点时，计算其与两个集合中任意节点的距离，动态调整集合以保持最大直径性质。

**算法要点**  
1. **动态维护直径**：每次新增节点时，检查其是否能扩展当前直径长度。若能，则清空另一集合，并筛选原集合中仍满足新直径长度的节点。
2. **LCA优化距离计算**：使用倍增法预处理LCA，快速计算两点距离。
3. **集合管理**：通过两个 `vector` 维护集合，确保每个节点只被处理一次，时间复杂度为 `O(n log n)`。

**解决难点**  
- **中点变化处理**：当新节点导致直径长度变化时，需重新划分集合中的端点，确保端点分布在正确的一侧。
- **高效过滤**：通过遍历原集合并保留符合条件的节点，避免重复计算。

**可视化设计思路**  
- **动画方案**：以动态树结构展示新增节点和直径变化。每次新增节点时，高亮其父节点及路径，并突出显示集合 `S1/S2` 的调整过程。
- **颜色标记**：红色表示 `S1`，蓝色表示 `S2`，新增节点用绿色闪烁。
- **步进控制**：允许单步执行，观察集合变化和LCA计算步骤。

---

### **题解评分 (≥4星)**

1. **skylee（★★★★★）**  
   - **亮点**：利用两个 `vector` 高效维护端点集合，时间复杂度 `O(n log n)`，代码简洁。
   - **关键代码**：动态调整集合的逻辑清晰，LCA预处理优化显著。

2. **N1K_J（★★★★）**  
   - **亮点**：详细证明直径端点分布性质，提供完整思路推导。
   - **心得**：强调避免重复加入集合的细节处理。

3. **Mirasycle（★★★★）**  
   - **亮点**：统一处理中点和边的情况，代码实现简洁。
   - **优化**：通过直接维护两个集合避免复杂中点跟踪。

---

### **最优思路或技巧提炼**

1. **双集合维护**：用两个集合分别管理直径两端的端点，确保任意两点来自不同集合即可构成直径。
2. **LCA倍增法**：预处理父节点信息，快速计算两点距离。
3. **动态过滤**：当直径更新时，遍历原集合筛选符合条件的节点，保证正确性。

---

### **同类型题与算法套路**

- **套路**：树的直径动态维护问题，通常利用直径交点的性质和端点集合的动态调整。
- **类似题目**：  
  - [CF1192B] Dynamic Diameter  
  - [LeetCode 1245] Tree Diameter  
  - [SPOJ QTREE] Query on a Tree  

---

### **推荐洛谷题目**

1. **P1099 树网的核**（树的直径性质应用）  
2. **P3304 [SDOI2013]直径**（求所有直径的公共边）  
3. **P5536 [XR-3]核心城市**（树的直径与关键节点选择）

---

### **个人心得摘录**

- **skylee**：使用 `vector` 而非 `set` 显著优化常数，避免冗余操作。
- **N1K_J**：处理新节点到两个集合距离相等时，需避免重复计数，`else if` 是关键。

---

### **核心代码实现**

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 3e5 + 5, LOG = 20;
int dep[N], anc[N][LOG];
vector<int> s1, s2;

void add_node(int u, int fa) {
    dep[u] = dep[fa] + 1;
    anc[u][0] = fa;
    for (int i = 1; (1 << i) <= dep[u]; i++)
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (dep[anc[u][i]] >= dep[v])
            u = anc[u][i];
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}

int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int main() {
    int m, maxd = 0;
    scanf("%d", &m);
    add_node(1, 0);
    s1.push_back(1);
    for (int i = 2; i <= m + 1; i++) {
        int fa; scanf("%d", &fa);
        add_node(i, fa);
        int d1 = s1.empty() ? 0 : dist(i, s1[0]);
        int d2 = s2.empty() ? 0 : dist(i, s2[0]);
        if (max(d1, d2) > maxd) {
            maxd = max(d1, d2);
            if (d1 == maxd) {
                for (int x : s2) 
                    if (dist(x, i) == d1) s1.push_back(x);
                s2.clear();
                s2.push_back(i);
            } else {
                for (int x : s1)
                    if (dist(x, i) == d2) s2.push_back(x);
                s1.clear();
                s1.push_back(i);
            }
        } else if (max(d1, d2) == maxd) {
            (d1 == maxd ? s2 : s1).push_back(i);
        }
        printf("%lu\n", s1.size() + s2.size());
    }
    return 0;
}
```

**代码解释**  
- `add_node`：预处理父节点及深度，用于LCA计算。
- `lca`：倍增法求最近公共祖先。
- `dist`：计算两点间距离。
- 动态维护 `s1` 和 `s2`，根据新节点距离调整集合，输出集合大小之和。

---

### **可视化与算法演示**

**复古像素风格设计**  
- **颜色方案**：`S1`（红色方块），`S2`（蓝色方块），新增节点（绿色闪烁）。
- **Canvas动画**：树结构以网格展开，新增节点时动态绘制父节点连线，高亮直径路径。
- **音效**：节点加入集合时播放“收集”音效，直径更新时播放“升级”音效。
- **自动演示**：模拟逐个添加节点，展示集合变化和直径更新过程。

---
处理用时：99.69秒