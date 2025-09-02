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
这些题解主要围绕如何在给定无向图中找到从节点 1 到节点 n 的路径，使得路径流量与路径花费之比最大这一问题展开。大部分题解采用枚举流量并结合最短路算法（如 Dijkstra、SPFA）的思路，通过控制流量，在满足条件的边上跑最短路来计算最小花费，进而更新答案。各题解在数据结构（邻接表、链式前向星）、枚举方式（枚举边的流量、枚举所有可能流量）和最短路算法实现细节上存在差异，但整体思路相似。

### 所选题解
- **作者：Hexarhy (赞：27)，4星**
  - **关键亮点**：思路清晰，对解题步骤和实现细节有明确说明，使用堆优化的 Dijkstra 算法，复杂度可接受。
  - **核心代码**：
```cpp
int dijkstra(const int limit)
{
    priority_queue<node> q;
    memset(visit,false,sizeof(visit));
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
    q.push(node{1,0,limit});
    while(!q.empty())
    {
        const int u=q.top().to;
        q.pop();
        if(visit[u])
            continue;
        visit[u]=true;
        for(auto v:edge[u])
            if(v.limit>=limit && dis[v.to]>dis[u]+v.cost)
            {
                dis[v.to]=dis[u]+v.cost;
                q.push(node{v.to,dis[v.to],limit});
            }
    }
    return dis[n];
}
```
  - **核心实现思想**：在 Dijkstra 算法的基础上，增加对边的流量限制判断，只考虑流量大于等于给定限制的边，以确保路径满足当前流量要求，最后返回从节点 1 到节点 n 的最小花费。

- **作者：ForeverHYX (赞：10)，4星**
  - **关键亮点**：详细介绍了链式前向星加边和搜边的方法，对枚举和 Dijkstra 算法的结合有清晰的阐述，代码注释详细。
  - **核心代码**：
```cpp
void dijkstra()
{
    for (int x = 1; x <= 1000; x++)
    {
        for(int j=1;j<=n;j++){
            dis[j]=inf;
            vis[j]=0;
        } 
        dis[1]=0;
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
                if(edge[i].f<x) continue;
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
        if(dis[n]!=inf){
            maxx=max(maxx,x*1000000/dis[n]);
        }
    }
}
```
  - **核心实现思想**：枚举所有可能的流量，对于每个流量，初始化距离数组和访问标记数组，使用 Dijkstra 算法在满足流量条件的边上计算最小花费，最后更新最大的流量与花费之比。

- **作者：hensier (赞：4)，4星**
  - **关键亮点**：提供了两种解法，枚举法和标记法，对思路和代码实现有详细解释，通过样例图辅助理解。
  - **枚举法核心代码**：
```cpp
int dijkstra(int s,int minf)
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,false,sizeof(vis));
    dis[s]=0;
    priority_queue<node>Q;
    Q.push((node){s,0});
    while(Q.size())
    {
        int x=Q.top().pos;
        Q.pop();
        if(vis[x])continue;
        vis[x]=true;
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to;
            if(e[i].f<minf)continue;
            if(dis[y]>dis[x]+e[i].w)
            {
                dis[y]=dis[x]+e[i].w;
                if(!vis[y])Q.push((node){y,dis[y]});
            }
        }
    }
    return dis[n];
}
```
  - **核心实现思想**：枚举每条边的流量作为最小流量，在 Dijkstra 算法中只考虑流量大于等于该最小流量的边，计算从节点 1 到节点 n 的最小花费，更新最大的流量与花费之比。

### 最优关键思路或技巧
- **枚举流量**：由于流量范围有限，通过枚举流量，将问题转化为在满足流量条件的边上求最小花费，简化了问题。
- **最短路算法**：使用 Dijkstra 或 SPFA 算法计算最小花费，保证了时间复杂度的可行性。
- **链式前向星**：在处理图的存储时，链式前向星可以高效地存储和遍历图的边，避免了邻接矩阵的空间浪费。

### 可拓展之处
同类型题或类似算法套路：
- **多条件路径规划问题**：当问题中存在多个条件（如时间、成本、容量等）需要同时考虑时，可以采用枚举其中一个条件，在满足该条件的情况下优化其他条件的思路。
- **分数规划问题**：对于要求最大化或最小化某个分数（如比值、效率等）的问题，可以尝试使用二分法或枚举法结合其他算法来求解。

### 推荐题目
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：考察 Dijkstra 算法的基本应用。
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)：涉及图的建模和最短路算法的应用。
- [P2829 大逃离](https://www.luogu.com.cn/problem/P2829)：需要综合考虑多个因素，使用最短路算法求解。

### 个人心得摘录与总结
- **tiger2005**：一开始想到固定边求最短路的方法，但发现最短路中间可能有流量更小的边，后来想到按流量从大到小加边的方法。总结是在解题时要考虑到各种情况，及时调整思路。
- **x_miracle**：一开始认为最短路上的流量与花费的比就是答案，结果出错。总结是不能想当然，对于有多个条件的问题要仔细分析条件之间的关系。

---
处理用时：45.09秒