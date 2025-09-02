# 题目信息

# [USACO23FEB] Moo Route II S

## 题目描述

注意：本题的时间限制为 4 秒，是默认限制的两倍。

Bessie 正在度假！由于最近的技术进步，Bessie 可以通过先进的航班旅行，这些航班甚至可以进行时间旅行。此外，即使存在多个“平行”的 Bessie 同时出现也不会有任何问题。

在这个国家，有 $N$ 个机场，编号为 $1,2,\cdots,N$，以及 $M$ 条时间旅行航班（$1 \leq N,M \leq 200000$）。第 $j$ 条航班从机场 $c_j$ 在时间 $r_j$ 起飞，并在时间 $s_j$ 抵达机场 $d_j$（$0 \leq r_j,s_j \leq 10^9$，$s_j < r_j$ 是可能的）。此外，Bessie 在机场 $i$ 需要停留 $a_i$ 时间（$1 \leq a_i \leq 10^9$）。也就是说，如果 Bessie 乘坐一趟航班在时间 $s$ 抵达机场 $i$，她可以转乘一趟从该机场出发的航班，只要该航班的起飞时间 $r \geq s + a_i$。需要注意的是，停留时间不会影响 Bessie 抵达某机场的实际时间。

Bessie 从城市 $1$ 出发，起始时间为 $0$。对于从 $1$ 到 $N$ 的每个机场，求出 Bessie 最早可以到达该机场的时间。

## 样例 #1

### 输入

```
3 3
1 0 2 10
2 11 2 0
2 1 3 20
10 1 10```

### 输出

```
0
0
20```

## 样例 #2

### 输入

```
3 3
1 0 2 10
2 10 2 0
2 1 3 20
10 1 10```

### 输出

```
0
10
-1```

# AI分析结果

### 综合分析与结论
这些题解主要围绕解决带有时间旅行航班的最短路问题展开，核心在于处理负边权和优化搜索过程。各题解普遍采用图论算法，如 SPFA、DFS 等，并结合排序、拆点、记忆化等优化手段。
- **思路方面**：部分题解将等待时间算入边权转化为普通最短路问题，部分利用航班特性采用记忆化搜索避免重复计算。
- **算法要点**：涉及拆点、排序、队列维护、记忆化等技巧，以降低时间复杂度。
- **解决难点**：主要解决负边权、图中存在环导致的重复计算和超时问题。

### 所选题解
- **作者：Usada_Pekora（4星）**
    - **关键亮点**：思路清晰，利用 SPFA 算法并对每个点的出边按 $r$ 降序排序，方便跳过已走过的边，优化时间复杂度至 $O(m^2)$。
- **作者：zac2010（4星）**
    - **关键亮点**：提出 SPFA 的 LLL 优化和记忆化 SPFA 两种思路，记忆化 SPFA 时间复杂度有保证且代码短，通过排序和维护分隔点位置减少不必要的边遍历。
- **作者：Genius_Star（4星）**
    - **关键亮点**：采用 DFS 搜索答案，记录已遍历的航班避免重复，对每个点出发的航班按出发时间降序排序，优化时间复杂度为 $O(N \log M+M)$，还注意去重。

### 重点代码及核心实现思想
#### Usada_Pekora 的题解
```cpp
struct edge {
    int v, in, out;
    edge(int _v = 0, int _in = 0, int _out = 0) {
        v = _v, in = _in, out = _out;
    }
    bool operator < (const edge &o) const {
        return (in ^ o.in) ? (in > o.in) : (out < o.out);
    }
};
vector<edge> g[N];
int n, m, a[N], dis[N], cur[N];
bool inq[N];
inline void spfa() {
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    dis[1] = 0, inq[1] = true;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        inq[u] = false;
        q.pop();
        for (int _ = cur[u]; _ < g[u].size(); _++) {
            int v = g[u][_].v, in = g[u][_].in, out = g[u][_].out;
            cur[u] = _;
            if (in < dis[u] + a[u])
                break;
            if (out < dis[v]) {
                dis[v] = out;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}
```
**核心思想**：定义边结构体并按出发时间降序排序，使用 SPFA 算法，队列维护待更新的点，通过 `cur` 数组记录每个点已遍历的边，避免重复遍历。

#### zac2010 的题解
```cpp
struct Edge{
    int v, s, t;
    friend bool operator < (Edge a, Edge b){
        return a.s == b.s? a.v < b.v : a.s < b.s;
    }
};
int n, m, a[N], dis[N], vis[N], id[N];
queue<int> q; vector<Edge> g[N];
void Spfa(){
    L(i, 2, n) dis[i] = 2e9;
    vis[1] = 1, q.push(1);
    while(!q.empty()){
        int u = q.front(); q.pop();
        int tm = (u == 1? 0 : dis[u] + a[u]);
        while(id[u] && g[u][id[u] - 1].s >= tm) id[u]--;
        vis[u] = 0;
        L(i, id[u], (int)g[u].size() - 1){
            int v = g[u][i].v, t = g[u][i].t;
            if(t < dis[v]){
                dis[v] = t;
                if(!vis[v]) vis[v] = 1, q.push(v);
            }
        }
        while(g[u].size() > id[u]) g[u].pop_back(); id[u] = g[u].size();
    }
}
```
**核心思想**：定义边结构体并排序，使用 SPFA 算法，`id` 数组维护分隔点位置，跳过起始时间太早的边，每次更新后删除已拓展的边，避免重复计算。

#### Genius_Star 的题解
```cpp
struct Node{
    ll c,r,d,s;
    bool operator<(const Node&rhs)const{
        return r>rhs.r;
    }
    bool operator==(const Node&rhs)const{
        return c==rhs.c&&r==rhs.r&&d==rhs.d&&s==rhs.s;
    }
}a[N];
bool cmp(const Node&x,const Node&y){
    if(x.c!=y.c)
        return x.c<y.c;
    if(x.r!=y.r)
        return x.r<y.r;
    if(x.d!=y.d)
        return x.d<y.d;
    return x.s<y.s;
}
ll n,m;
ll w[N],k[N],dis[N];
bool f[N];
vector<pair<Node,ll>> E[N];
void dfs(ll u,ll t){
    for(ll i=k[u];i<(ll)E[u].size();i++){
        ll id=E[u][i].second;
        Node v=E[u][i].first;
        if(v.r<t) 
            break;
        if(f[id])
            continue;
        f[id]=1;
        dis[v.d]=min(dis[v.d],v.s);
        k[u]++;
        dfs(v.d,v.s+w[v.d]);
    }
    return;
}
```
**核心思想**：定义节点结构体并排序去重，使用 DFS 搜索，`k` 数组记录每个点已遍历的航班，`f` 数组标记已坐过的航班，按出发时间降序排序，若当前航班不合法则直接退出。

### 最优关键思路或技巧
- **排序优化**：对每个点的出边按出发时间排序，可快速跳过不合法的边，减少不必要的计算。
- **记忆化**：利用每条边只会松弛一次的特性，标记已走过的边或航班，避免重复计算。
- **拆点**：将每个点按可能的到达/出发时间拆点，转化为连通性问题，用 BFS 求解。

### 可拓展之处
同类型题或类似算法套路：
- 带有时间限制的路径规划问题，可借鉴排序和记忆化的思想。
- 负边权的最短路问题，可考虑使用 SPFA 及其优化算法。
- 图中存在环的搜索问题，可通过记录已遍历的状态避免重复计算。

### 推荐题目
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得摘录与总结
- **rhn7**：发现原代码在图中有环时会重复遍历出边导致 TLE，通过将 $i = f[x] + 1$ 解决该问题。总结为在处理图中存在环的搜索问题时，要注意避免重复遍历。
- **tder**：输入顺序看错调了好久，提醒在做题时要仔细读题，注意输入输出的顺序。

---
处理用时：50.53秒