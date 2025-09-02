# 题目信息

# [USACO09FEB] Revamping Trails G

## 题目描述

Farmer John dutifully checks on the cows every day. He traverses some of the M (1 <= M <= 50,000) trails conveniently numbered 1..M from pasture 1 all the way out to pasture N (a journey which is always possible for trail maps given in the test data). The N (1 <= N <= 10,000) pastures conveniently numbered 1..N on Farmer John's farm are currently connected by bidirectional dirt trails.  Each trail i connects pastures P1\_i and P2\_i (1 <= P1\_i <= N; 1 <= P2\_i <= N) and requires T\_i (1 <= T\_i <= 1,000,000) units of time to traverse.

He wants to revamp some of the trails on his farm to save time on his long journey. Specifically, he will choose K (1 <= K <= 20) trails to turn into highways, which will effectively reduce the trail's traversal time to 0. Help FJ decide which trails to revamp to minimize the resulting time of getting from pasture 1 to N.

TIME LIMIT: 2 seconds



## 说明/提示

K is 1; revamp trail 3->4 to take time 0 instead of 100. The new shortest path is 1->3->4, total traversal time now 1.


## 样例 #1

### 输入

```
4 4 1 
1 2 10 
2 4 10 
1 3 1 
3 4 100 
```

### 输出

```
1 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕分层图最短路算法来解决问题，核心思路是通过构建分层图，将使用不同次数免费机会的状态表示在不同层图中，再利用最短路算法（如 Dijkstra、SPFA 等）求出从起点到终点的最短路径。部分题解也尝试用动态规划结合最短路的思想来解题。

### 所选题解
- **作者：QQQfy（5星）**
    - **关键亮点**：思路清晰，对分层图的概念、意义、应用范围都有详细解释，代码注释丰富，易于理解。
    - **个人心得**：作者表示很久以前就想学分层图，但一直找不到易于理解的教程，所以希望通过自己的题解为和自己一样弱的蒟蒻们提供良好的体验。
- **作者：齐天の小猴（4星）**
    - **关键亮点**：详细说明了分层图的构建过程，代码结构清晰，使用了快读优化输入。
    - **个人心得**：作者写了多次题解很多都没过，分层图最短路也是最近才学会，希望自己的题解能得到认可。
- **作者：Diamiko（4星）**
    - **关键亮点**：以通俗易懂的语言解释分层图，对建图细节和数组大小的计算有详细说明，代码注释丰富。
    - **个人心得**：作者自认为讲解比较详细，希望题解能过审，朋友们有疑问可以私聊或 at 他。

### 重点代码及核心实现思想
#### QQQfy 的题解
```cpp
// 建图
for (int i=1;i<=m;i++)
{
    int u,v,cost;
    cin>>u>>v>>cost;
    add(u,v,cost);add(v,u,cost);
    for (int j=1;j<=k;j++)
    {
        add(n*j+u,n*j+v,cost);add(n*j+v,n*j+u,cost);
        add(n*(j-1)+u,n*j+v,0);add(n*(j-1)+v,n*j+u,0);
    }
}
// Dijkstra 最短路
void dij(int s)
{
    memset(dist,0x3f,sizeof(dist));
    dist[s]=0;
    q.push((node){s,0});
    while (!q.empty())
    {
        node fr=q.top();q.pop();
        int u=fr.u,dis=fr.dis;
        if (dis!=dist[u]) continue;
        for (int v=head[u];v;v=nextt[v])
            if (dist[to[v]]>dist[u]+w[v])
            {
                dist[to[v]]=dist[u]+w[v];
                q.push((node){to[v],dist[to[v]]});
            }
    }
}
```
**核心实现思想**：先构建分层图，同层节点之间的边权与原图相同，相邻层之间的边权为 0 表示使用一次免费机会。然后使用 Dijkstra 算法求最短路，最后取各层终点的最短距离中的最小值作为答案。

#### 齐天の小猴的题解
```cpp
// 建图
for(int i=1;i<=m;i++)
{
    readx(u);readx(v);readx(t);
    add(u,v,t);add(v,u,t);
    for(int j=1;j<=k;j++)
    {
        add(j*n+u,j*n+v,t);
        add(j*n+v,j*n+u,t);
        add((j-1)*n+u,j*n+v,0);
        add((j-1)*n+v,j*n+u,0);
    }
}
// Dijkstra 最短路
void dij()
{
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    memset(vis,0,sizeof(vis));
    q.push(make_pair(0,1));
    while(q.size()){
        int x=q.top().second;
        q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i;i=edge[i].nexty)
        {
            int y=edge[i].to,z=edge[i].w;
            if(dis[y]>dis[x]+z)
            {
                dis[y]=dis[x]+z;
                q.push(make_pair(-dis[y],y));
            }
        } 
    } 
}
```
**核心实现思想**：同样是构建分层图，使用 Dijkstra 算法求最短路，最后比较各层终点的最短距离得到答案。

#### Diamiko 的题解
```cpp
// 建图
for(int i=1;i<=m;i++)
{
    read(u),read(v),read(w);
    for(int j=0;j<=k;j++)
    {
        addEdge(u+j*n,v+j*n,w);
        addEdge(v+j*n,u+j*n,w);
        if(j==k)break;
        addEdge(u+j*n,v+(j+1)*n,0);
        addEdge(v+j*n,u+(j+1)*n,0);
    }
}
// Dijkstra 最短路
void Dijkstra()
{
    for(int i=1;i<=n*(k+1);i++)
    {
        node[i].dis=INF;
    }
    node[1].dis=0;
    priority_queue<pii,vector<pii>,greater<pii> >q;
    q.push({0,1});
    while(q.size())
    {
        pii tmp=q.top();
        q.pop();
        int d=tmp.first,u=tmp.second;
        if(d!=node[u].dis)continue;
        for(int e=node[u].head;e;e=edge[e].next)
        {
            int v=edge[e].to;
            if(node[v].dis>edge[e].len+d)
            {
                node[v].dis=edge[e].len+d;
                q.push({node[v].dis,v});
            }
        }
    }
}
```
**核心实现思想**：构建分层图，注意当 `j == k` 时不建层与层之间的边。使用 Dijkstra 算法求最短路，最后统计各层终点的最短距离的最小值。

### 最优关键思路或技巧
- **分层图思想**：将图分层，每一层表示使用不同次数免费机会的状态，层与层之间通过边权为 0 的边连接，将问题转化为普通的最短路问题。
- **Dijkstra 堆优化**：使用优先队列优化 Dijkstra 算法，降低时间复杂度。
- **数组大小计算**：点数为 `n * (k + 1)`，边数通常为 `m * (k + 1) * 4`，注意数组要开足够大，避免越界。

### 可拓展之处
同类型题或类似算法套路：
- 当题目中存在可以改变某些边权的操作时，可考虑使用分层图来解决。
- 分层图可以与其他图论算法（如网络流）结合，解决更复杂的问题。

### 推荐题目
- [P4568 [JLOI2011]飞行路线](https://www.luogu.org/problem/P4568)
- [P4822 [BJWC2012]冻结](https://www.luogu.org/problem/P4822)
- [P1948 [USACO08JAN]电话线Telephone Lines](https://www.luogu.org/problem/P1948)

### 个人心得总结
- 部分作者表示分层图学习起来有一定难度，缺乏易于理解的教程，希望自己的题解能帮助到其他同学。
- 一些作者在解题过程中遇到了数组大小、算法超时等问题，提醒我们在做题时要注意这些细节。
- 还有作者尝试用不同的思路解题，如动态规划结合最短路，但可能会遇到后效性等问题，需要不断调整和优化。

---
处理用时：50.74秒