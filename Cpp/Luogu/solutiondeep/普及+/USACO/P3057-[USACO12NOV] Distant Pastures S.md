# 题目信息

# [USACO12NOV] Distant Pastures S

## 题目描述

Farmer John's farm is made up of an N x N grid of pastures, where each pasture contains one of two different types of grass.  To specify these two types of grass, we use the characters ( and ), so for example FJ's farm might look like the following grid:

(()) 
)()( 
)((( 
))))
When Bessie the cow travels around the farm, it takes her A units of time to move from a pasture to an adjacent pasture (one step north, south, east, or west) with the same grass type, or B units of time to move to an adjacent pasture with a different grass type.  Whenever Bessie travels from one pasture to a distant pasture, she always uses a sequence of steps that takes the minimum amount of time.  Please compute the greatest amount of time Bessie will ever need to take while traveling between some pair of pastures on the farm.

给出一个n\*n的括号矩阵，从一个点走到相邻的同字符点需付出A的代价，到不同字符点需付出B的代价。求所有点对之间最短路的最大值。


## 说明/提示

It takes Bessie 5 units of time to travel between the upper-left corner and the lower-right corner of the grid.  No other pair of pastures causes her to travel for more time than this.


## 样例 #1

### 输入

```
3 1 2 
((( 
()( 
(() 
```

### 输出

```
5 
```

# AI分析结果

### 综合分析与结论
本题要求在给定的括号矩阵中，计算所有点对之间最短路的最大值。由于数据规模较大，Floyd-Warshall 算法时间复杂度高，多数题解采用了 $n^2$ 次 Dijkstra 算法或类似的最短路算法来求解。

### 所选题解
- **作者：liangbowen（5星）**
    - **关键亮点**：思路清晰，详细阐述了选择 $n^2$ 次 Dijkstra 算法的原因，代码结构清晰，有明确的函数分工，注释详细。
    - **核心代码**：
```cpp
// 建边函数
void add(int x, int y, int k)
{
    e[++cur].now = y;
    e[cur].nxt = head[x];
    e[cur].w = k;
    head[x] = cur;
}
// Dijkstra 函数
int dijkstra(int first) 
{
    priority_queue <Dis> Q;
    for (int i = 1; i <= nn; i++) dis[i].pos = i, dis[i].len = 2147483647, vis[i] = false;
    dis[first].len = 0;
    Q.push(dis[first]);
    while (!Q.empty())
    {
        int topi = Q.top().pos;
        Q.pop();
        if (vis[topi]) continue;
        vis[topi] = true;
        for (int i = head[topi]; i; i = e[i].nxt)
            if (dis[topi].len + e[i].w < dis[e[i].now].len)
            {
                dis[e[i].now].len = dis[topi].len + e[i].w;
                Q.push(dis[e[i].now]);
            }
    }
    int maxn = 0;
    for (int i = 1; i <= nn; i++) maxn = max(maxn, dis[i].len);
    return maxn;
}
```
- **作者：ZolaWatle（4星）**
    - **关键亮点**：提出离散化的思路，使连边和跑图的代码更加美观，方便调试和查错，代码实现简洁。
    - **核心代码**：
```cpp
// 建边函数
inline void add(int i, int j)
{
    long long w=dat[i]==dat[j]?A:B;
    E[i].push_back(make_pair(j,w));
}
// Dijkstra 函数
inline void Dijkstra(int s)
{
    priority_queue < pair <long long,int> > q;
    for(int i=1;i<=n*n;i++)
    {
        dist[i]=1e18;
        vis[i]=false;
    }
    q.push(make_pair(0,s)),dist[s]=0;
    while(!q.empty())
    {
        int x=q.top().second;
        q.pop();
        if(vis[x])
            continue;
        vis[x]=true;
        for(int i=0;i<E[x].size();i++)
        {
            int y=E[x][i].first;
            long long z=E[x][i].second;
            if(dist[x]+z<dist[y])
            {
                dist[y]=dist[x]+z;
                q.push(make_pair(-dist[y],y));
            }
        }
    }
}
```
- **作者：grass8cow（4星）**
    - **关键亮点**：思路简洁明了，代码实现直接，对时间复杂度和空间复杂度进行了分析。
    - **核心代码**：
```cpp
// Dijkstra 函数
void dij(int s)
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;q.push((node){s,0});
    while(!q.empty())
    {
        node qp=q.top();q.pop();int u=qp.u;
        if(vis[u])continue;vis[u]=1;
        for(int i=0,v,w;i<g[u].size();i++)
        {
            v=g[u][i].v;w=g[u][i].w;
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                q.push((node){v,dis[v]});
            }
        }
    }
    for(int i=1;i<=n*n;i++)ans=max(ans,dis[i]);
}
```

### 最优关键思路或技巧
- **算法选择**：由于 Floyd-Warshall 算法时间复杂度高，采用 $n^2$ 次 Dijkstra 算法，利用优先队列进行堆优化，时间复杂度为 $O(n^3 \log n)$。
- **离散化**：将矩阵中的每个点进行编号，方便建边和跑最短路，使代码更加简洁。

### 可拓展之处
同类型题或类似算法套路：
- 可以将矩阵扩展为三维或更高维度，依然使用最短路算法求解。
- 改变边的权值规则，如边权与点的坐标或其他属性相关。

### 推荐题目
- P1144 最短路计数
- P3371 单源最短路径（弱化版）
- P4779 单源最短路径（标准版）

### 个人心得摘录与总结
- **作者：风格雨关**：原代码 TLE 后，尝试了读入优化、玄学加速和氧优化等方法。总结是遇到 TLE 时可以从输入输出优化和编译器优化等方面入手。
- **作者：ZolaWatle**：认为离散化之后连边和跑图的代码能更加美观，方便调试和进行查错。强调了离散化在图论问题中的重要性。
- **作者：dunko**：看到题目想到最短路，最后写了一个又像 SPFA 又像 BFS 的代码，提醒自己注意起点不一定是 (1,1) 点。心得是遇到不会的题可以先暴力尝试，之后再改进。 

---
处理用时：36.23秒