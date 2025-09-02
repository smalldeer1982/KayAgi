# 题目信息

# [IOI 2018] werewolf 狼人

## 题目背景

本题为交互题，但在此请提交**完整程序**。

## 题目描述

在日本的茨城县内共有 $N$ 个城市和 $M$ 条道路。这些城市是根据人口数量的升序排列的，依次编号为 $0$ 到 $N - 1$。每条道路连接两个不同的城市，并且可以双向通行。由这些道路，你能从任意一个城市到另外任意一个城市。

你计划了 $Q$ 个行程，这些行程分别编号为 $0$ 至 $Q - 1$。第 $i(0 \leq i \leq Q - 1)$ 个行程是从城市 $S_i$ 到城市 $E_i$。

你是一个狼人。你有两种形态：**人形**和**狼形**。在每个行程开始的时候，你是人形。在每个行程结束的时候，你必须是狼形。在行程中，你必须要变身（从人形变成狼形）恰好一次，而且只能在某个城市内（包括可能是在 $S_i$ 或 $E_i$ 内）变身。

狼人的生活并不容易。当你是人形时，你必须避开人少的城市，而当你是狼形时，你必须避开人多的城市。对于每一次行程 $i(0 \leq i \leq Q - 1)$，都有两个阈值 $L_i$ 和 $R_i(0 \leq L_i \leq R_i \leq N - 1)$，用以表示哪些城市必须要避开。准确地说，当你是人形时，你必须避开城市 $0, 1, \ldots , L_i - 1$ ；而当你是狼形时，则必须避开城市 $R_i + 1, R_i + 2, \ldots , N - 1$。这就是说，在行程 $i$ 中，你必须在城市 $L_i, L_i + 1, \ldots , R_i$ 中的其中一个城市内变身。

你的任务是，对每一次行程，判定是否有可能在满足上述限制的前提下，由城市 $S_i$ 走到城市 $E_i$。你的路线可以有任意长度。

## 说明/提示

**限制条件**

- $2 \leq N \leq 200, 000$
- $N - 1 \leq M \leq 400, 000$
- $1 \leq Q \leq 200, 000$
- 对于每个 $0 \leq j \leq M - 1$
    - $0 \leq X_j \leq N - 1$
    - $0 \leq Y_j \leq N - 1$
    - $X_j \neq Y_j$
- 你可以通过道路由任意一个城市去另外任意一个城市。
- 每一对城市最多只由一条道路直接连起来。换言之，对于所有 $0 \leq j < k \leq M - 1$，都有 $(X_j, Y_j) \neq (X_k, Y_k)$ 和 $(Y_j, X_j) \neq (X_k, Y_k)$
- 对于每个 $0 \leq i \leq Q - 1$
    - $0 \leq L_i \leq S_i \leq N - 1$
    - $0 \leq E_i \leq R_i \leq N - 1$
    - $S_i \neq E_i$
    - $L_i \leq R_i$

**子任务**

- 1.（7 分）$N \leq 100$，$M \leq 200$，$Q \leq 100$。
- 2.（8 分）$N \leq 3, 000$，$M \leq 6, 000$，$Q \leq 3, 000$。
- 3.（34 分）$M = N - 1$ 且每个城市最多与两条路相连（所有城市是以一条直线的形式连起来）。
- 4.（51 分）没有附加限制。

## 样例 #1

### 输入

```
6 6 3
5 1
1 2
1 3
3 4
3 0
5 2
4 2 1 2
4 2 2 2
5 4 3 4
```

### 输出

```
1
0
0
```

## 样例 #2

### 输入

```
10 9 10
6 7
1 5
8 0
2 9
9 4
2 7
8 5
6 0
3 4
4 9 0 9
8 1 8 9
1 8 1 8
8 3 5 5
8 9 3 9
0 1 0 2
9 0 6 6
1 7 1 8
9 4 5 6
9 5 0 9
```

### 输出

```
1
1
1
0
1
1
0
1
0
1
```

# AI分析结果


### 题目分析：狼人（Werewolf）

#### 题目背景
给定一个无向图，要求判断从起点 \(s\) 到终点 \(e\) 是否存在一条路径，该路径分为三个阶段：
1. **人形阶段**：从 \(s\) 出发，只经过编号 \(\geq L\) 的点。
2. **变身阶段**：在编号 \([L, R]\) 的某个点变身（从人形变为狼形）。
3. **狼形阶段**：只经过编号 \(\leq R\) 的点到达 \(e\)。

#### 核心算法：Kruskal重构树 + 主席树
1. **问题转化**：
   - 存在一条路径当且仅当存在一个中间点 \(x\)：
     - 从 \(s\) 到 \(x\) 只经过 \(\geq L\) 的点（人形阶段）。
     - 从 \(x\) 到 \(e\) 只经过 \(\leq R\) 的点（狼形阶段）。
   - 等价于两个点集的交集非空：\(A\)（\(s\) 通过 \(\geq L\) 的点可达）和 \(B\)（\(e\) 通过 \(\leq R\) 的点可达）。

2. **Kruskal重构树**：
   - **A树（人形阶段）**：
     - 边权定义为 \(\min(u, v)\)。
     - 按边权**从大到小**排序，构建**最大生成树**重构树。
     - 性质：从叶节点 \(s\) 向上跳，找到最后一个满足点权 \(\geq L\) 的祖先节点 \(u\)，其子树表示 \(s\) 通过 \(\geq L\) 的点可达的所有点。
   - **B树（狼形阶段）**：
     - 边权定义为 \(\max(u, v)\)。
     - 按边权**从小到大**排序，构建**最小生成树**重构树。
     - 性质：从叶节点 \(e\) 向上跳，找到最后一个满足点权 \(\leq R\) 的祖先节点 \(v\)，其子树表示 \(e\) 通过 \(\leq R\) 的点可达的所有点。

3. **二维数点问题**：
   - 将每个点在A树的DFS序作为横坐标，在B树的DFS序作为纵坐标。
   - 查询：A树子树区间 \([A_l, A_r]\) 和 B树子树区间 \([B_l, B_r]\) 是否有交集。
   - 用**主席树**维护：对A树的DFS序排序，以B树的DFS序为值域建树。

#### 算法步骤
1. **构建两棵重构树**：
   - A树：边权为 \(\min(u,v)\)，按边权降序构建最大生成树。
   - B树：边权为 \(\max(u,v)\)，按边权升序构建最小生成树。

2. **DFS预处理**：
   - 对两棵树求DFS序，并预处理倍增数组。

3. **主席树构建**：
   - 按A树的DFS序排序原图节点。
   - 以B树的DFS序为值域插入主席树。

4. **查询处理**：
   - 在A树上倍增找到 \(s\) 对应的子树根 \(u\)（点权 \(\geq L\)）。
   - 在B树上倍增找到 \(e\) 对应的子树根 \(v\)（点权 \(\leq R\)）。
   - 查询主席树：A树区间 \([dfn_u, dfn_u + size_u - 1]\) 中是否存在值在 \([dfn_v, dfn_v + size_v - 1]\)。

#### 可视化算法：像素动画演示
- **主题**："像素探险家"在网格迷宫中寻找路径。
- **核心演示**：
  1. **初始化**：8位像素风格网格，不同颜色区分起点、终点、障碍、可通行区域。
  2. **A树构建过程**：动态展示边按 \(\min(u,v)\) 降序加入，新增重构节点。
  3. **B树构建过程**：动态展示边按 \(\max(u,v)\) 升序加入，新增重构节点。
  4. **查询演示**：
     - 起点 \(s\) 在A树上跳：高亮当前节点，播放“跳跃”音效。
     - 终点 \(e\) 在B树上跳：高亮当前节点，播放“跳跃”音效。
     - 主席树查询：网格中高亮两子树区间，若有交集则播放“成功”音效。

- **交互控制**：
  - 单步执行/自动播放（速度可调）。
  - 重置动画。
  - 显示当前步骤伪代码。

#### 代码实现（C++）
```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 400005, MAXM = 400005, LOG = 20;

struct Edge { int u, v; };
struct Node { int ls, rs, sum; } tree[MAXN * 40];
int root[MAXN], n, m, q, cnt, total_nodes;
int dfnA[MAXN], dfnB[MAXN], sizeA[MAXN], sizeB[MAXN], valA[MAXN], valB[MAXN];
int faA[LOG][MAXN], faB[LOG][MAXN];
vector<int> gA[MAXN], gB[MAXN];
Edge edges[MAXM];

// Kruskal重构树
struct KruskalTree {
    int parent[MAXN], node_val[MAXN], timer;
    vector<int> graph[MAXN];

    int find(int x) { 
        return parent[x] == x ? x : parent[x] = find(parent[x]); 
    }

    void build(bool isMaxTree) {
        for (int i = 1; i <= 2 * n; i++) parent[i] = i;
        sort(edges + 1, edges + m + 1, [isMaxTree](Edge a, Edge b) {
            return isMaxTree ? min(a.u, a.v) > min(b.u, b.v) : max(a.u, a.v) < max(b.u, b.v);
        });
        int node_cnt = n;
        for (int i = 1; i <= m; i++) {
            int u = find(edges[i].u), v = find(edges[i].v);
            if (u == v) continue;
            int new_node = ++node_cnt;
            node_val[new_node] = isMaxTree ? min(edges[i].u, edges[i].v) : max(edges[i].u, edges[i].v);
            parent[u] = parent[v] = new_node;
            graph[new_node].push_back(u);
            graph[new_node].push_back(v);
        }
        // 从根节点开始DFS（根为node_cnt）
        for (int i = 1; i <= node_cnt; i++) {
            for (int j = 1; j < LOG; j++) 
                faA[j][i] = faA[j-1][faA[j-1][i]];
        }
    }

    void dfs(int u, int f, bool isA) {
        if (u <= n) {
            if (isA) dfnA[u] = ++timer;
            else dfnB[u] = ++timer;
        }
        for (int v : graph[u]) {
            if (v == f) continue;
            if (isA) faA[0][v] = u;
            else faB[0][v] = u;
            dfs(v, u, isA);
        }
        if (isA) sizeA[u] = timer - dfnA[u] + 1;
        else sizeB[u] = timer - dfnB[u] + 1;
    }

    int query(int u, int limit, bool isA) {
        for (int i = LOG - 1; i >= 0; i--) {
            int f = isA ? faA[i][u] : faB[i][u];
            if (f && ((isA && node_val[f] >= limit) || (!isA && node_val[f] <= limit)))
                u = f;
        }
        return u;
    }
} treeA, treeB;

// 主席树
void update(int &cur, int pre, int l, int r, int pos) {
    cur = ++cnt;
    tree[cur] = tree[pre];
    tree[cur].sum++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(tree[cur].ls, tree[pre].ls, l, mid, pos);
    else update(tree[cur].rs, tree[pre].rs, mid + 1, r, pos);
}

int query(int l, int r, int L, int R, int rt_l, int rt_r) {
    if (!rt_r || tree[rt_r].sum - tree[rt_l].sum == 0) return 0;
    if (L <= l && r <= R) return tree[rt_r].sum - tree[rt_l].sum;
    int mid = (l + r) >> 1, res = 0;
    if (L <= mid) res += query(l, mid, L, R, tree[rt_l].ls, tree[rt_r].ls);
    if (R > mid) res += query(mid + 1, r, L, R, tree[rt_l].rs, tree[rt_r].rs);
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &edges[i].u, &edges[i].v);
        edges[i].u++; edges[i].v++; // 0-indexed to 1-indexed
    }

    // 构建两棵重构树
    treeA.build(true); // A树：边权为min(u,v)的最大生成树
    treeB.build(false); // B树：边权为max(u,v)的最小生成树
    treeA.dfs(total_nodes, 0, true);
    treeB.dfs(total_nodes, 0, false);

    // 按A树的DFS序排序原图节点
    vector<int> nodes(n);
    for (int i = 1; i <= n; i++) nodes[i-1] = i;
    sort(nodes.begin(), nodes.end(), [](int x, int y) { return dfnA[x] < dfnA[y]; });

    // 构建主席树（值域为B树的DFS序）
    for (int i = 0; i < n; i++) {
        int node = nodes[i];
        update(root[i+1], root[i], 1, n, dfnB[node]);
    }

    while (q--) {
        int s, e, L, R;
        scanf("%d%d%d%d", &s, &e, &L, &R);
        s++; e++; L++; R++; // 0-indexed to 1-indexed

        // 在A树上找s的子树根（点权 >= L）
        int rootA = treeA.query(s, L, true);
        // 在B树上找e的子树根（点权 <= R）
        int rootB = treeB.query(e, R, false);

        // 查询A树子树在B树区间是否有交集
        int lA = dfnA[rootA], rA = lA + sizeA[rootA] - 1;
        int lB = dfnB[rootB], rB = lB + sizeB[rootB] - 1;
        int res = query(1, n, lB, rB, root[lA-1], root[rA]);

        printf("%d\n", res > 0 ? 1 : 0);
    }
    return 0;
}
```

#### 学习心得
1. **重构树本质**：将图论问题转化为树问题，利用子树表示连通性。
2. **二维数点技巧**：通过DFS序将子树映射为区间，用主席树高效查询区间交集。
3. **倍增优化**：快速定位子树根节点，时间复杂度 \(O(\log n)\)。
4. **实践建议**：先掌握Kruskal重构树基础，再练习DFS序映射，最后实现主席树。

#### 拓展练习
1. **洛谷 P4197**：Peaks（重构树+主席树）
2. **洛谷 P4768**：[NOI2018]归程（重构树应用）
3. **洛谷 P3302**：[SDOI2013]森林（主席树动态加点）

---
处理用时：156.19秒