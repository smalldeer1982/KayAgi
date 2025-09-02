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
这些题解大多围绕枚举流量并结合最短路算法（如 Dijkstra、SPFA）来解决问题。核心思路是枚举路径中的最小流量，然后在满足该流量限制的边中找出最小花费路径，最后计算流量与花费的比值并取最大值。不同题解在数据结构（邻接表、链式前向星）、算法细节（堆优化、普通队列）和代码实现上存在差异，但整体思路一致。

### 所选题解
- **作者：Hexarhy (赞：27)  ★★★★**
    - **关键亮点**：思路清晰，对解题步骤和实现细节有详细说明，使用堆优化的 Dijkstra 算法，时间复杂度分析明确。
- **作者：ForeverHYX (赞：10)  ★★★★**
    - **关键亮点**：详细介绍了链式前向星加边和搜边的方法，对枚举算法的复杂度进行了分析，代码注释丰富。
- **作者：hensier (赞：4)  ★★★★**
    - **关键亮点**：提供了两种不同的解法，分别是枚举和标记法，对每种解法的思路和复杂度都有详细分析。

### 重点代码与核心实现思想
#### Hexarhy 的题解
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
        if(visit[u]) continue;
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
**核心实现思想**：使用堆优化的 Dijkstra 算法，在每次松弛操作前检查边的限制是否大于等于当前枚举的流量，若满足条件则更新最短路径。

#### ForeverHYX 的题解
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
            if (vis[u]) continue;
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
**核心实现思想**：使用链式前向星存储图，枚举流量，在每次枚举中使用 Dijkstra 算法计算最短路径，过滤掉流量小于当前枚举值的边，最后更新答案。

#### hensier 的题解（枚举法）
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
**核心实现思想**：枚举每条边的流量作为最小流量，在每次枚举中使用 Dijkstra 算法计算最短路径，过滤掉流量小于当前枚举值的边，最后更新答案。

### 最优关键思路或技巧
- **枚举流量**：通过枚举路径中的最小流量，将问题转化为在满足流量限制的边中求最小花费路径，简化了问题的复杂度。
- **最短路算法**：使用 Dijkstra 或 SPFA 算法在满足流量限制的边中找出最小花费路径。
- **链式前向星**：使用链式前向星存储图，节省空间，方便遍历边。

### 可拓展之处
同类型题可能会有更复杂的图结构或限制条件，例如增加边的属性、限制路径长度等。类似算法套路可以应用于其他需要同时考虑多个因素的最短路问题，通过枚举其中一个因素，将问题转化为单因素的最短路问题。

### 推荐题目
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

### 个人心得摘录与总结
- **tiger2005**：一开始想固定边求最短路，但发现最短路中间可能有流量更小的边，后来想到按流量从大到小加边的方法。总结是在解题时要考虑到各种情况，当思路遇到问题时要尝试换一种方法。
- **Fairicle**：认为这道题很练耐心，有些地方写错了很难找，特别是 Dijkstra 部分。总结是在实现复杂算法时要仔细检查，注意细节。

---
处理用时：44.23秒