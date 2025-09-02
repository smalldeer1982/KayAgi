# 题目信息

# Imbalance Value of a Tree

## 题目描述

给定一棵树，每个顶点都被写上了一个数，第 $i$ 个顶点写上的数是 $a_i$。定义一个函数 $I(x,y)$ 表示从顶点 $x$ 到 $y$ 的简单路径上 $a_i$ 的最大值和最小值的差。

你要求出 $\sum_{i=1}^{n}\sum_{j=i}^{n}I(i,j)$。

## 样例 #1

### 输入

```
4
2 2 3 1
1 2
1 3
1 4
```

### 输出

```
6
```

# AI分析结果



### 算法分类
并查集

### 题解思路与算法要点
1. **问题拆解**  
   将总和分解为 $\sum \text{路径最大值} - \sum \text{路径最小值}$，分别计算两部分。

2. **点权转边权**  
   - 计算最大值时，边的权值取两端点权值的较大者，按升序排序。
   - 计算最小值时，边的权值取两端点权值的较小者，按降序排序。

3. **并查集合并策略**  
   - 按排序后的顺序逐步合并边的两端点。
   - 每次合并时，当前边的权值即为路径中的最大/最小值，贡献为两连通块大小乘积乘以边权。

4. **核心难点**  
   - **正确性证明**：确保合并顺序能覆盖所有路径，且每条路径的极值被正确统计。
   - **复杂度优化**：通过路径压缩的并查集实现 $O(n \alpha(n))$ 的时间复杂度。

### 题解评分（≥4星）
1. **lottle1212（5星）**  
   - 代码结构清晰，变量命名规范。
   - 对边权的处理与排序逻辑明确，注释说明到位。
   - 代码可读性强，适合教学演示。

2. **Karry5307（4.5星）**  
   - 使用自定义排序函数简化代码。
   - 通过结构体封装边属性，增强代码可维护性。

3. **Cry_For_theMoon（4星）**  
   - 直接处理点权排序，避免边权转换。
   - 通过遍历邻接表动态维护连通块，思路独特。

### 最优思路提炼
1. **极值分离策略**  
   将问题拆分为最大值和最小值独立计算，避免路径遍历的重复操作。

2. **贪心合并思想**  
   - 按极值排序后，每次合并的边是当前连通块的边界，确保统计不重不漏。
   - 贡献公式 $\text{sz}[x] \times \text{sz}[y] \times w$ 精准覆盖所有新增路径。

### 同类型题与算法套路
- **通用模式**  
  统计连通块间路径属性总和的问题（如路径长度、极值、权重和等）。
- **类似题目**  
  - 洛谷 P1967（货车运输）：最大生成树 + 路径极值查询。
  - 洛谷 P1118（数字三角形）：全排列路径权值和的优化计算。
  - 洛谷 P1552（派遣）：树形结构下的极值统计。

### 推荐题目
1. **P1967**：最大生成树与路径极值查询。
2. **P1552**：树形结构下连通块的极值统计。
3. **P1118**：路径权值和的数学优化。

### 可视化与算法演示
**核心动画设计**  
1. **边排序与合并过程**  
   - 用不同颜色区分最大值（红色）和最小值（蓝色）处理阶段。
   - 高亮当前处理的边，显示其权值与两端连通块大小。

2. **贡献计算动态展示**  
   - 在合并时，弹出公式 $\text{sz}[x] \times \text{sz}[y] \times w$ 并显示计算结果。
   - 实时更新总和数值，用进度条表示计算进度。

3. **复古像素风格**  
   - 使用 8-bit 像素树结构，边合并时播放经典音效（如《超级马里奥》金币声）。
   - 自动演示模式中，AI 按排序顺序逐步点亮边，合并连通块。

**代码片段（JS 动画核心）**  
```javascript
class UnionFind {
  constructor(n) {
    this.parent = Array.from({length: n}, (_, i) => i);
    this.size = Array(n).fill(1);
  }
  find(x) { /* 路径压缩 */ }
  merge(x, y, w, callback) {
    const fx = this.find(x), fy = this.find(y);
    if (fx !== fy) {
      callback(this.size[fx], this.size[fy], w);
      this.parent[fy] = fx;
      this.size[fx] += this.size[fy];
    }
  }
}

// 模拟边处理动画
function animateEdges(edges, isMax) {
  edges.sort((a, b) => isMax ? a.w - b.w : b.w - a.w);
  const uf = new UnionFind(n);
  let sum = 0;
  edges.forEach(edge => {
    uf.merge(edge.u, edge.v, edge.w, (sz1, sz2, w) => {
      sum += sz1 * sz2 * w;
      // 触发像素动画：高亮边、显示贡献值、播放音效
    });
  });
  return sum;
}
```

### 代码实现（关键逻辑）
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6+5;

struct Edge { int u, v, w; };
vector<Edge> edges;
int a[MAXN], n;

ll solve(bool is_max) {
    for (auto &e : edges)
        e.w = is_max ? max(a[e.u], a[e.v]) : min(a[e.u], a[e.v]);
    sort(edges.begin(), edges.end(), [&](Edge x, Edge y) {
        return is_max ? (x.w < y.w) : (x.w > y.w);
    });
    
    vector<int> parent(n+1), sz(n+1, 1);
    iota(parent.begin(), parent.end(), 0);
    function<int(int)> find = [&](int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    };
    
    ll res = 0;
    for (auto &e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            res += (ll)sz[fu] * sz[fv] * e.w;
            parent[fv] = fu;
            sz[fu] += sz[fv];
        }
    }
    return res;
}

int main() {
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> a[i];
    for (int i=1; i<n; ++i) {
        int u, v; cin >> u >> v;
        edges.push_back({u, v});
    }
    ll max_sum = solve(true);
    ll min_sum = solve(false);
    cout << max_sum - min_sum << endl;
}
```

---
处理用时：105.69秒