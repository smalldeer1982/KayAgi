# 题目信息

# [POI 2003] Monkeys

## 题目描述

一棵树上有 $n$ 只猴子。他们从 $1 \sim n$ 编号。编号为 $1$ 的猴子用它的尾巴盘住了一个树枝，剩下的猴子要么被其他的猴子钩住要么就是自己用手钩住其他的猴子。每只猴子都可以用两只手去钩其他的猴子，每只手最多只能钩一只。

从 $0$ 时刻开始，每一秒都有一只猴子松开它的一只手。这也许会造成一些猴子掉落到地上，我们想要知道它们掉落地上的时间（猴子掉落的速度都非常的快，可以忽略掉落的时间）。

## 说明/提示

对于所有数据，$1 \le n \le 2 \times 10^5$，$1 \le m \le 4 \times 10^5$。

## 样例 #1

### 输入

```
3 2
-1 3
3 -1
1 2
1 2
3 1```

### 输出

```
-1
1
1```

# AI分析结果

### 综合分析与结论
这些题解均采用了“正难则反”的思路，将删边问题转化为加边问题，以降低问题的复杂度。具体实现上，主要分为使用并查集和直接 DFS 两种方法。使用并查集的题解通过维护连通块信息来更新节点与 1 号节点的连通时间；直接 DFS 的题解则通过深度优先搜索标记与 1 号节点连通的节点。各题解在时间复杂度上大多为线性，能满足题目要求。

### 所选题解
- **作者：Alex_Wei（5 星）**
  - **关键亮点**：思路清晰，代码简洁，直接使用 DFS 实现，时间复杂度线性，细节处理得当。
  - **核心代码**：
```cpp
void dfs(int id, int as) {
    if(id == -1 || vis[id]) return;
    vis[id] = 1, ans[id] = as;
    if(!ban[id][0]) dfs(ls[id], as);
    if(!ban[id][1]) dfs(rs[id], as);
    for(auto it : e[id]) if(!ban[it.first][it.second]) dfs(it.first, as);
}
int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> ls[i] >> rs[i];
        if(ls[i] != -1) e[ls[i]].push_back({i, 0});
        if(rs[i] != -1) e[rs[i]].push_back({i, 1});
    } 
    for(int i = 0; i < m; i++) cin >> id[i] >> dir[i], ban[id[i]][--dir[i]] = 1;
    dfs(1, -1);
    for(int i = m - 1; ~i; i--) {
        ban[id[i]][dir[i]] = 0;
        if(vis[id[i]]) dfs(dir[i] ? rs[id[i]] : ls[id[i]], i);
        if(vis[dir[i] ? rs[id[i]] : ls[id[i]]]) dfs(id[i], i);
    } 
    for(int i = 1; i <= n; i++) cout << ans[i] << "\n";
    return 0;
}
```
  - **核心实现思想**：先将所有要删的边标记，从 1 号节点开始 DFS 标记初始连通的节点。然后倒序遍历删边操作，撤销标记并进行 DFS 更新连通节点的答案。

- **作者：wzy2021（4 星）**
  - **关键亮点**：使用并查集维护连通块信息，通过链表更新连通块内节点的答案，思路巧妙。
  - **核心代码**：
```cpp
int find(int x){
    if (fa[x] == x)return x;
    return fa[x] = find(fa[x]);
}
void merge (int u, int v, int p) {
    int fu = find(u), fv = find(v);
    if (fu == fv) return ;
    if (fu > fv) swap (fu, fv);
    if (fu == 1 && p != -1) {
        for (int use = head[fv]; use; use = nxt[use]) ans[use] = p;
    }
    fa[fv] = fu; nxt[tail[fu]] = head[fv]; tail[fu] = tail[fv];
} 
int main() {
    int n, m; scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf ("%d%d", &a[i][1], &a[i][2]); ans[i] = -1;
    }
    for (int i = 0; i < m; ++i) {
        scanf ("%d%d", &p[i], &w[i]);
        vis[p[i]][w[i]] = 1;
    }
    for (int i = 1; i <= n; ++i) fa[i] = head[i] = tail[i] = i, nxt[i] = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i][1] && a[i][1] != -1) merge (i, a[i][1], -1);
        if (!vis[i][2] && a[i][2] != -1) merge (i, a[i][2], -1);
    }
    for (int i = m - 1; i >= 0; --i) {
        int u = p[i], v = a[p[i]][w[i]];
        merge (u, v, i);
    }
    for (int i = 1; i <= n; ++i) printf("%d\n",ans[i]);
    return 0;
} 
```
  - **核心实现思想**：先标记要删的边，初始化并查集和链表信息。将未被删的边合并，然后倒序遍历删边操作，合并边并更新答案。

### 最优关键思路或技巧
- **思维方式**：“正难则反”，将删边问题转化为加边问题，降低问题复杂度。
- **算法优化**：使用 DFS 或并查集维护连通性，保证每个节点和边只被处理一次，时间复杂度线性。

### 可拓展之处
同类型题如删点、删边求连通性问题，都可以考虑使用“正难则反”的思路，将删操作转化为加操作。类似算法套路还有离线处理，先预处理所有操作，再倒序执行。

### 推荐题目
- P1197 [JSOI2008]星球大战
- P1653 猴子
- P3916 图的遍历

### 个人心得
- **作者：ningago**：“首先想到的是并查集，于是并查集调炸了，无意中发现了另一种不用并查集的小清新做法。” 总结：在解题时，若一种方法实现困难，可以尝试换一种思路，可能会有新的发现。 

---
处理用时：35.21秒