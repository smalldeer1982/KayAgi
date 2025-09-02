# 题目信息

# Subway

## 题目描述

给出一个 $n$ 个点，$n$ 条边的无向无权图，图上每条边的长度为 $1$，保证图中有且仅由一个环。

你的任务是求出每一个点到环（环上任意一点）的最短路径长度。

## 样例 #1

### 输入

```
4
1 3
4 3
4 2
1 2
```

### 输出

```
0 0 0 0 ```

## 样例 #2

### 输入

```
6
1 2
3 4
6 4
2 3
1 3
3 5
```

### 输出

```
0 0 0 1 1 2 ```

# AI分析结果



**题目中文重写**  
（原题已为中文，无需翻译）

**算法分类**  
图论（基环树处理）

---

**题解综合分析**  
核心任务是处理基环树，分为找环和计算距离两步。各解法主要差异在找环方式（DFS递归回溯、Tarjan缩点、拓扑排序）和距离计算方式（BFS、DFS、Dijkstra）。最优解法需兼顾简洁性与效率。

---

**精选题解与评分**  

1. **August_Light (5星)**  
**亮点**:  
- 通过DFS找到非树边确定环的起点，沿父节点回溯构建环  
- 对环上每个点DFS处理子树距离，逻辑清晰  
**代码核心**:  
```cpp
void dfs(int u, int lst, int dep) {
    ans[u] = dep;
    for(int i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(on_ring[v]) continue; // 跳过环上点
        dfs(v, i, dep+1); // 深度即为距离
    }
}
```

2. **hater (4星)**  
**亮点**:  
- 拓扑排序剔除度=1节点，剩余度为2的节点即为环  
- BFS直接计算最短距离，无需复杂DFS回溯  
**核心思路**:  
```cpp
// 拓扑找环
queue<int> q;
for(int i=1;i<=n;i++) if(deg[i]==1) q.push(i);
while(!q.empty()) {
    int u=q.front(); q.pop();
    for(int v : G[u]) if(--deg[v] == 1) q.push(v);
}
// BFS计算距离
queue<int> q;
for(int i=1;i<=n;i++) if(deg[i]>=2) q.push(i), dis[i]=0;
while(!q.empty()) {
    int u=q.front(); q.pop();
    for(int v:G[u]) if(dis[v] > dis[u]+1) 
        dis[v]=dis[u]+1, q.push(v);
}
```

3. **Zofia (4星)**  
**技巧**: 构造虚点0，连接所有环上点，转化为单源最短路问题  
**代码亮点**:  
```cpp
addedge(0, vec[i], 0); // 虚点0到环上点距离为0
dijkstra(0); // 直接计算所有点到虚点的最短路
```

---

**最优思路总结**  
1. **拓扑找环**：通过不断删除度为1的节点，最终剩余度为2的节点构成环，实现简单高效  
2. **多源BFS**：将环上所有点作为起点同时BFS，天然保证最短距离，时间复杂度O(n)  

---

**举一反三**  
- **基环树常见套路**：找环后对环上每个点处理子树，或拆环为链处理动态规划  
- **类似题目推荐**:  
  - [P4381 岛屿](https://www.luogu.com.cn/problem/P4381)（基环树直径）  
  - [P2607 骑士](https://www.luogu.com.cn/problem/P2607)（基环树DP）  
  - [CF1027F Session in BSU](https://codeforces.com/problemset/problem/1027/F)（并查集找环）  

---

**调试心得摘录**  
> "发现构造虚点可以统一处理多个起点，省去逐个BFS的冗余" —— Zofia  
> "无向图DFS找环需记录父节点防止回头，否则会误判环" —— August_Light

---
处理用时：57.05秒