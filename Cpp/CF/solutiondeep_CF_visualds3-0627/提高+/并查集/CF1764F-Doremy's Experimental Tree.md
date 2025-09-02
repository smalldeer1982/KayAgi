# 题目信息

# Doremy's Experimental Tree

## 题目描述

Doremy has an edge-weighted tree with $ n $ vertices whose weights are integers between $ 1 $ and $ 10^9 $ . She does $ \frac{n(n+1)}{2} $ experiments on it.

In each experiment, Doremy chooses vertices $ i $ and $ j $ such that $ j \leq i $ and connects them directly with an edge with weight $ 1 $ . Then, there is exactly one cycle (or self-loop when $ i=j $ ) in the graph. Doremy defines $ f(i,j) $ as the sum of lengths of shortest paths from every vertex to the cycle.

Formally, let $ \mathrm{dis}_{i,j}(x,y) $ be the length of the shortest path between vertex $ x $ and $ y $ when the edge $ (i,j) $ of weight $ 1 $ is added, and $ S_{i,j} $ be the set of vertices that are on the cycle when edge $ (i,j) $ is added. Then,
 $$ f(i,j)=\sum_{x=1}^{n}\left(\min_{y\in S_{i,j}}\mathrm{dis}_{i,j}(x,y)\right).  $$
 
 Doremy writes down all values of  $ f(i,j) $  such that  $ 1 \leq j \leq i \leq n $ , then goes to sleep. However, after waking up, she finds that the tree has gone missing. Fortunately, the values of  $ f(i,j) $  are still in her notebook, and she knows which  $ i $  and  $ j $  they belong to. Given the values of  $ f(i,j)$, can you help her restore the tree?

It is guaranteed that at least one suitable tree exists.

## 说明/提示

In the first test case, the picture below, from left to right, from top to bottom, shows the graph when pairs $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,2) $ , $ (2,3) $ , $ (3,3) $ are connected with an edge, respectively. The nodes colored yellow are on the cycle.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764F/65b459471236cb3c4f73ac2ff04b74120b42f624.png)

## 样例 #1

### 输入

```
3
7
3 5
0 2 8```

### 输出

```
2 3 3
1 2 2```

## 样例 #2

### 输入

```
9
8081910646
8081902766 8081903751
8081902555 8081903540 8081905228
3090681001 3090681986 3090681775 7083659398
7083657913 7083658898 7083658687 2092437133 15069617722
1748216295 1748217280 1748217069 5741194692 749972427 10439821163
2377558289 2377559274 2377559063 6370536686 1379314421 5028071980 8866466178
1746983932 1746984917 1746984706 5739962329 748740064 10438588800 5026839617 10448447704
2341942133 2341943118 2341942907 6334920530 1343698265 4992455824 8830850022 4991223461 9115779270```

### 输出

```
1 2 985
2 3 211
2 4 998244353
2 5 998244853
4 6 671232353
6 8 1232363
4 7 356561356
7 9 35616156```

# AI分析结果



## 算法分类
生成树（最小/最大）

## 题解思路、算法要点与解决难点

### 核心思路
通过分析实验值 $f(i,j)$ 的数学性质，推导出任意两点间的距离，并构建生成树还原原树结构。关键公式为 $dis(i,j) = \frac{f(i,i) + f(j,j) - 2f(i,j)}{n}$，利用此公式可计算所有点对间的距离，进而通过生成树算法（如 Kruskal/Prim）确定树结构。

### 解决难点
1. **距离计算**：发现 $f(i,i) + f(j,j) - 2f(i,j)$ 的几何意义为 $n$ 倍两点间距离。
2. **树结构还原**：证明原树是这些距离构成的最大/最小生成树。
3. **边权计算**：通过子树大小与 $f(u,u) - f(u,fa)$ 的比值确定边权。

## 题解评分（≥4星）

1. **Leasier（★★★★☆）**  
   - 思路清晰，通过父子关系递归构建树。
   - 代码简洁，使用排序和动态规划确定父子结构。
   - 时间复杂度 $O(n^2)$，适合中等规模数据。

2. **MSqwq（★★★★☆）**  
   - 直接计算所有点对距离后构建最小生成树。
   - 代码极简，仅需 Kruskal 算法实现。
   - 正确性基于数学推导，时间复杂度 $O(n^2 \log n)$。

3. **周子衡（★★★★☆）**  
   - 提出最大生成树性质，与 Boruvka 算法结合。
   - 边权计算逻辑清晰，利用子树大小分割贡献。
   - 思维角度独特，但代码未给出完整实现。

## 最优思路或技巧提炼
1. **距离公式**：$dis(i,j) = \frac{f(i,i) + f(j,j) - 2f(i,j)}{n}$，通过容斥原理推导。
2. **生成树构建**：原树是点对距离图的最小生成树（或最大生成树，需具体推导）。
3. **边权计算**：断开边后的子树大小与 $f$ 差值之比直接给出边权。

## 同类型题或类似算法套路
- **树结构还原**：通过特定函数值推导树形（如 Prufer 序列）。
- **生成树应用**：如次小生成树、最优比率生成树。
- **容斥与距离计算**：在网格或树形结构中利用容斥简化距离计算。

## 推荐洛谷题目
1. P3366 【模板】最小生成树  
2. P1396 营救（Kruskal 应用）  
3. P1967 货车运输（最大生成树 + LCA）

## 个人心得摘录
- **Leasier**：通过固定根节点简化父子关系推导，类似拓扑排序。
- **MSqwq**：发现 $f(x,x)$ 的特殊性质是解题突破口，强调容斥思想。
- **Alex_Wei**：在生成树构建中引入随机检查优化，降低错误率。

## 可视化与算法演示

### 核心算法流程
1. **计算距离矩阵**：遍历所有点对 $(i,j)$，计算 $dis(i,j)$。
2. **构建生成树**：以距离为边权运行 Kruskal 算法，选择最小边。
3. **高亮操作**：
   - **当前处理边**：红色边框标记。
   - **已加入生成树边**：绿色填充。
   - **无效边（成环）**：灰色淡化。

### 复古像素风格设计
- **颜色方案**：16 色 EGA 调色板，绿色表示树边，红色表示候选边。
- **音效**：加入边时播放 8-bit 上升音效，无效边播放低沉音效。
- **Canvas 动画**：以网格表示点，边动态绘制，每步延迟 200ms。

### 关键代码片段（Kruskal 实现）
```cpp
struct Edge { int u, v; ll w; };
vector<Edge> edges;
for (int i = 1; i <= n; i++)
    for (int j = i+1; j <= n; j++)
        edges.push_back({i, j, (f[i][i] + f[j][j] - 2*f[i][j])/n});

sort(edges.begin(), edges.end(), [](Edge a, Edge b){ return a.w < b.w; });

vector<int> parent(n+1);
iota(parent.begin(), parent.end(), 0);
function<int(int)> find = [&](int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); };

for (auto e : edges) {
    int fu = find(e.u), fv = find(e.v);
    if (fu != fv) {
        parent[fu] = fv;
        cout << e.u << " " << e.v << " " << e.w << endl;
    }
}
```

### 交互设计
- **暂停/继续**：Space 键控制。
- **步进执行**：→ 键单步执行。
- **速度调节**：滑块调整帧间隔（100ms~1000ms）。
- **自动模式**：AI 自动运行，类似贪吃蛇 AI 连续决策。

---
处理用时：69.76秒