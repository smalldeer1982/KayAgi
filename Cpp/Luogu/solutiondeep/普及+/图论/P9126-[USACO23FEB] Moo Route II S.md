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
本题主要是在含时间旅行航班的图中求从起点到各点的最早到达时间，由于存在负边权，不能直接用常规的 Dijkstra 算法。各题解主要围绕 SPFA 算法或其变种、拆点转化为连通性问题、DFS 搜索等方法展开。大部分题解通过对边排序、记录已走过的边等方式进行优化，避免重复计算。

### 所选题解
- **作者：Usada_Pekora（5星）**
    - **关键亮点**：思路清晰，利用 SPFA 算法并对每个点的出边按 $r$ 降序排序，方便跳过走过的边，时间复杂度为 $O(m^2)$ ，代码可读性高。
- **作者：zac2010（4星）**
    - **关键亮点**：提出了 SPFA 的 LLL 优化和记忆化 SPFA 两种思路，对边排序后维护分隔点位置或删除已拓展的边，减少不必要的计算。
- **作者：Genius_Star（4星）**
    - **关键亮点**：采用 DFS 搜索答案，记录每个点出发的航班已遍历到的位置，对航班出发时间降序排序，避免重复走航班，时间复杂度为 $O(N \log M+M)$ ，并注意去重。

### 重点代码
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
**核心思想**：使用 SPFA 算法，对每个点的出边按 $r$ 降序排序，在队列中取出点后，从记录的位置开始遍历出边，若边的起始时间小于当前到达时间加上停留时间则跳过，若能更新距离则更新并加入队列。

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
**核心思想**：对边按起始时间排序，使用 SPFA 算法，维护分隔点位置，跳过起始时间太早的边，更新距离并将未访问的点加入队列，最后删除已拓展的边。

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
**核心思想**：对航班按起点、出发时间等排序并去重，对每个点的航班按出发时间降序排序，使用 DFS 搜索，记录已遍历的航班位置，若航班可用则更新距离并继续搜索。

### 最优关键思路或技巧
- **边排序优化**：对每个点的出边按出发时间排序，方便跳过不满足条件的边，减少不必要的计算。
- **记录已走过的边**：由于每条边的到达时间固定，走过一次后无需再走，通过标记或删除已走过的边避免重复计算。

### 可拓展之处
同类型题如含负边权的最短路问题、有时间限制的路径规划问题等，都可以考虑使用 SPFA 算法或其变种，通过对边排序、记录已走过的边等方式进行优化。类似算法套路还有拆点转化为连通性问题等。

### 推荐题目
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得摘录与总结
- **rhn7**：以 Xy_top 大佬的代码为例，指出图中有环时 `dfs` 可能会重复遍历出边导致 TLE，解决方法是在递归后更新循环变量。总结：在使用 DFS 搜索时，要注意图中是否有环，避免重复遍历。
- **tder**：提到输入顺序看错调了好久。总结：做题时要仔细阅读输入输出格式，避免因粗心导致调试困难。

---
处理用时：49.75秒