# 题目信息

# [USACO19DEC] Milk Pumping G

## 题目描述

Farmer John 最近为了扩张他的牛奶产业帝国而收购了一个新的农场。这一新的农场通过一个管道网络与附近的小镇相连，FJ 想要找出其中最合适的一组管道，将其购买并用来将牛奶从农场输送到小镇。

这个管道网络可以用 $N$ 个接合点（管道的端点）来描述，将其编号为 $1 \ldots N$。接合点 $1$ 表示 FJ 的农场，接合点 $N$ 表示小镇。有 $M$ 条双向的管道，每条连接了两个接合点。使用第 $i$ 条管道需要 FJ 花费 $c_i$ 美元购入，可以支持每秒 $f_i$ 升牛奶的流量。

FJ 想要购买一条管道组成一条单一路径，路径的两端点分别为接合点 $1$ 和 $N$。这条路径的花费等于路径上所有管道的费用之和。路径上的流量等于路径上所有管道的最小流量（因为这是沿这条路径输送牛奶的瓶颈）。FJ 想要最大化路径流量与路径花费之比。保证存在从 $1$ 到 $N$之间的路径。


## 说明/提示

在这个例子中，仅由一条路径从 $1$ 到 $N$。 它的流量为 $\min(3,4)=3$，花费为 $2+5=7$。

### 数据范围

测试点 $2\sim 5$ 满足 $N,M\le 100$。

对于 $100\%$ 的数据，$2 \leq N \leq 1000$，$1 \leq M \leq 1000$。

供题：Brian Dean

## 样例 #1

### 输入

```
3 2
2 1 2 4
2 3 5 3```

### 输出

```
428571```

# AI分析结果

### 综合分析与结论
本题要求在无向图中找出从节点 1 到节点 N 的路径，使路径流量与路径花费之比最大。各题解核心思路多为枚举流量，再在满足流量限制的边上跑最短路以获取最小花费，最后更新最大比值。

### 所选题解
- **作者：Hexarhy（5星）**
    - **关键亮点**：思路清晰，详细阐述枚举流量结合 Dijkstra 算法的思路，代码注释丰富，复杂度分析明确。
    - **核心代码**：
```cpp
int dijkstra(const int limit)
{
    priority_queue<node> q;
    memset(visit, false, sizeof(visit));
    memset(dis, INF, sizeof(dis));
    dis[1] = 0;
    q.push(node{1, 0, limit});
    while (!q.empty())
    {
        const int u = q.top().to;
        q.pop();
        if (visit[u])
            continue;
        visit[u] = true;
        for (auto v : edge[u])
            if (v.limit >= limit && dis[v.to] > dis[u] + v.cost)
            {
                dis[v.to] = dis[u] + v.cost;
                q.push(node{v.to, dis[v.to], limit});
            }
    }
    return dis[n];
}

int main()
{
    input();
    for (int i = 1; i <= m; i++)
        ans = max(ans, limit[i] * int(1e6) / dijkstra(limit[i]));
    cout << ans << endl;
    return 0;
}
```
    - **核心思想**：通过枚举每条边的流量限制，每次调用 Dijkstra 算法计算满足该流量限制下从节点 1 到节点 N 的最小花费，进而更新最大比值。

- **作者：ForeverHYX（4星）**
    - **关键亮点**：详细介绍链式前向星加边和搜边方法，对枚举流量和 Dijkstra 算法的思路解释清晰，指出易错点。
    - **核心代码**：
```cpp
void dijkstra()
{
    for (int x = 1; x <= 1000; x++)
    {
        for (int j = 1; j <= n; j++)
        {
            dis[j] = inf;
            vis[j] = 0;
        }
        dis[1] = 0;
        q.push((node){0, 1});
        while (!q.empty())
        {
            node tmp = q.top();
            q.pop();
            int u = tmp.pos;
            if (vis[u])
                continue;
            vis[u] = 1;
            for (int i = head[u]; i; i = edge[i].next)
            {
                if (edge[i].f < x)
                    continue;
                int v = edge[i].to;
                if (dis[u] + edge[i].c < dis[v])
                {
                    dis[v] = dis[u] + edge[i].c;
                    if (!vis[v])
                    {
                        q.push((node){dis[v], v});
                    }
                }
            }
        }
        if (dis[n]!= inf)
        {
            maxx = max(maxx, x * 1000000 / dis[n]);
        }
    }
}
```
    - **核心思想**：枚举 1 到 1000 的流量，每次重置距离和访问数组，使用链式前向星遍历边，过滤不满足流量限制的边，更新最小花费和最大比值。

- **作者：hensier（4星）**
    - **关键亮点**：提供两种解法，详细分析样例，对枚举和标记两种思路解释清晰，代码注释详细。
    - **核心代码（枚举解法）**：
```cpp
int dijkstra(int s, int minf)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    priority_queue<node> Q;
    Q.push((node){s, 0});
    while (Q.size())
    {
        int x = Q.top().pos;
        Q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x]; i; i = e[i].nxt)
        {
            int y = e[i].to;
            if (e[i].f < minf)
                continue;
            if (dis[y] > dis[x] + e[i].w)
            {
                dis[y] = dis[x] + e[i].w;
                if (!vis[y])
                    Q.push((node){y, dis[y]});
            }
        }
    }
    return dis[n];
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        int u = read(), v = read(), c = read(), f = read();
        add(u, v, c, f);
        add(v, u, c, f);
        F[i] = f;
    }
    for (int i = 1; i <= m; i++)
        ans = max(ans, 1e6 * F[i] / dijkstra(1, F[i]));
    printf("%d", int(ans));
    return 0;
}
```
    - **核心思想**：枚举每条边的流量作为最小流量，调用 Dijkstra 算法计算满足该最小流量下从节点 1 到节点 N 的最小花费，更新最大比值。

### 最优关键思路或技巧
- **枚举流量**：通过枚举流量，将双变量问题转化为单变量问题，在满足流量限制的边上跑最短路，简化问题求解。
- **堆优化 Dijkstra**：使用优先队列优化 Dijkstra 算法，降低时间复杂度。
- **链式前向星**：适合稀疏图的存储方式，可高效遍历边。

### 拓展思路
同类型题可考虑在图中增加其他限制条件，如时间限制、容量限制等，仍可采用枚举一个限制条件，在满足该条件的图上求解另一个最优值的思路。类似算法套路可用于解决多目标优化问题，通过枚举一个目标，求解另一个目标的最优解。

### 推荐题目
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：考察 Dijkstra 算法的基本应用。
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)：在图中寻找特定路径，可使用最短路算法解决。
- [P1629 邮递员送信](https://www.luogu.com.cn/problem/P1629)：涉及有向图的往返最短路问题，需要灵活运用最短路算法。

### 个人心得摘录与总结
- **tiger2005**：最初思路是固定边求最短路，但发现最短路中间可能有流量更小的边，后来想到按流量从大到小加边计算答案并更新最短路。总结为在解题时要不断思考思路的合理性，遇到问题尝试换角度解决。
- **x_miracle**：一开始认为最短路上的流量与花费的比就是答案，结果出错。提醒在解决多变量问题时不能想当然，要深入分析变量之间的关系。 

---
处理用时：46.18秒