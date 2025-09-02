# 题目信息

# [USACO18JAN] MooTube G

## 题目背景

*本题与 [银组同名题目](/problem/P6111) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 10^5$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。

## 样例 #1

### 输入

```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1```

### 输出

```
3
0
2
```

# AI分析结果



---

## 算法分类
**离线处理 + 并查集**

---

## 题解思路与难点分析

### 核心算法流程
1. **离线排序**：将边按权重降序排序，询问按阈值 `k` 降序排序。
2. **并查集维护连通性**：初始化每个节点为独立连通块，合并满足当前查询阈值的边。
3. **动态合并与查询**：按排序后的顺序处理查询，每次将边权≥当前 `k` 的边合并，查询时直接获取连通块大小。

### 解决难点
- **离线处理思维**：将动态查询转化为静态处理，利用排序复用合并结果。
- **连通块动态维护**：通过并查集的合并操作快速统计满足条件的节点数量。

---

## 题解评分（≥4星）

1. **StudyingFather（⭐⭐⭐⭐⭐）**  
   - **亮点**：代码简洁高效，排序与指针操作清晰，完美体现离线处理思想。
   - **代码可读性**：结构清晰，变量命名规范。
   ```cpp
   sort(e+1,e+n,cmp1);  // 边按权值降序
   sort(a+1,a+q+1,cmp2);  // 询问按k降序
   while(cur<=n && a[i].k<=e[cur].w) {
       unionn(find(e[cur].u), find(e[cur].v));
       cur++;
   }
   ans[a[i].id] = siz[find(a[i].v)] - 1;
   ```

2. **elijahqi（⭐⭐⭐⭐）**  
   - **亮点**：代码高效，路径压缩优化到位，变量命名合理。
   - **优化点**：直接使用 `size` 数组维护连通块大小，避免冗余计算。
   ```cpp
   while(now<=n&&data[now].z>=qr[i].k){
       int x=find(data[now].x), y=find(data[now].y);
       fa[x]=y; size[y]+=size[x];
   }
   ```

3. **何俞均（⭐⭐⭐⭐）**  
   - **亮点**：使用 `two pointers` 技巧合并边和查询，代码逻辑紧凑。
   - **代码结构**：排序与合并逻辑分离，便于调试。
   ```cpp
   for (int i=1, j=1; i<=Q; i++) {
       while (e[j].w >= q[i].k && j < N) unite(e[j].u, e[j].v), ++j;
       ans[q[i].id] = size[getf(q[i].v)] - 1;
   }
   ```

---

## 最优思路提炼
1. **离线降序处理**：将边和询问按阈值从大到小排序，确保合并操作只需一次。
2. **并查集动态维护**：合并时统计连通块大小，查询时直接取 `size[find(v)] - 1`。
3. **时间复杂度优化**：离线处理使时间复杂度降至 `O(N log N + Q log Q)`，适合大规模数据。

---

## 类似题目推荐
1. **P1967 货车运输**：最大生成树 + 路径最小值查询。
2. **P4185 [USACO18JAN]MooTube S**：同一问题的小数据版本。
3. **P1197 [JSOI2008]星球大战**：离线逆序处理 + 并查集维护连通性。

---

## 可视化设计（像素风格）
### 核心动画逻辑
1. **网格化节点**：将每个节点表示为像素方块，初始随机分布。
2. **动态合并效果**：合并边时，用闪烁动画连接两个方块，合并后颜色统一。
3. **查询高亮**：处理查询时，当前连通块方块高亮为红色，统计数量显示在顶部。

### 音效与交互
- **合并音效**：8-bit "beep" 短音。
- **查询完成音效**：高音调“叮”。
- **控制面板**：支持暂停/继续、调整动画速度（1x/2x/5x）。

---

## 核心代码实现
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

struct Edge { int u, v, w; };
struct Query { int k, v, id; };

Edge edges[100005];
Query queries[100005];
int fa[100005], size[100005], ans[100005];

bool cmpEdge(Edge a, Edge b) { return a.w > b.w; }
bool cmpQuery(Query a, Query b) { return a.k > b.k; }

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[x] = y;
        size[y] += size[x];
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    
    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        size[i] = 1;
    }
    
    // 输入边和查询
    for (int i = 0; i < n-1; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &queries[i].k, &queries[i].v);
        queries[i].id = i;
    }
    
    // 排序处理
    sort(edges, edges + n-1, cmpEdge);
    sort(queries, queries + q, cmpQuery);
    
    int curEdge = 0;
    for (int i = 0; i < q; i++) {
        int k = queries[i].k;
        // 合并所有满足条件的边
        while (curEdge < n-1 && edges[curEdge].w >= k) {
            unite(edges[curEdge].u, edges[curEdge].v);
            curEdge++;
        }
        // 记录答案
        ans[queries[i].id] = size[find(queries[i].v)] - 1;
    }
    
    // 输出结果
    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);
    return 0;
}
```

---
处理用时：81.29秒