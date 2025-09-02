# 题目信息

# [USACO19JAN] Shortcut G

## 题目背景

USACO 19 年一月月赛金组第三题

## 题目描述

每天晚上，Farmer John 都会敲响一个巨大的铃铛，召唤他的奶牛们前来牛棚享用晚餐。奶牛们都急切地想要前往牛棚，所以她们都会沿着最短的路径行走。
农场可以描述为 $N$ 块草地（$1 \leq N \leq 10,000$），方便起见编号为 $1 \ldots N$，牛棚位于草地 $1$。草地之间由 $M$ 条双向的小路连接（$N-1 \leq M \leq 50,000$）。每条小路有其通过时间，从每块草地出发都存在一条由一些小路组成的路径可以到达牛棚。

草地 $i$ 中有 $c_i$ 头奶牛。当她们听到晚餐铃时，这些奶牛都沿着一条消耗最少时间的路径前往牛棚。如果有多条路径并列消耗时间最少，奶牛们会选择其中“字典序”最小的路径（也就是说，她们通过在两条路径第一次出现分支的位置优先选择经过编号较小的草地的方式来打破并列关系，所以经过草地 $7$、$3$、$6$、$1$ 的路径会优先于经过 $7$、$5$、$1$ 的路径，如果它们所消耗的时间相同）。

Farmer John 担心牛棚距离某些草地太远。他计算了每头奶牛路上的时间，将所有奶牛消耗的时间相加，称这个和为总移动时间。他想要通过额外添加一条从牛棚（草地 $1$）连接到某块他选择的其他草地的、通过时间为 $T$（$1 \leq T \leq 10,000$）的“近道”来尽可能地减少总移动时间。当一头奶牛在她平时前往牛棚的路上偶然看见这条近道时，如果这条近道能够使她更快地到达牛棚，她就会走这条路。否则，一头奶牛会仍然沿着原来的路径行走，即使使用这条近道可能会减少她的移动时间。

请帮助 Farmer John 求出通过添加一条近道能够达到的总移动时间减少量的最大值。


## 样例 #1

### 输入

```
5 6 2
1 2 3 4 5
1 2 5
1 3 3
2 4 3
3 4 5
4 5 2
3 5 7```

### 输出

```
40```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均是先求出从节点 1 出发的最短路，再构建最短路树，最后通过遍历树来计算添加近道后总移动时间的最大减少量。在构建最短路树时，为满足字典序最小的要求，大部分题解采用从小到大枚举节点的方式。不同题解在最短路算法（Dijkstra、SPFA）、树的遍历方式（DFS、BFS）以及代码实现细节上存在差异。

### 所选题解
- **作者：hsfzLZH1（5星）**
    - **关键亮点**：思路清晰，详细说明了建最短路树的方法和注意事项，代码注释丰富，可读性高。
    - **个人心得**：“注意 $c_i$ 有可能是 $0$ 。在 DFS 的过程中，不能按照 $siz$ 的值判断是否访问过结点，而应增加一个附加数组，我被这个坑了好久。”
- **作者：linluke（4星）**
    - **关键亮点**：对最短路树的概念解释清晰，代码结构合理，易于理解。
- **作者：Na2PtCl6（4星）**
    - **关键亮点**：分析过程详细，对记录路径和建树的步骤有明确的注意事项说明。

### 重点代码及核心实现思想
#### hsfzLZH1
```cpp
// 建最短路树
for(int i=1;i<=n;i++)for(int j=h[i];j;j=nxt[j])
if(dist[p[j]]==dist[i]+w[j]&&!tf[p[j]])tf[p[j]]=true,
g[i].push_back(p[j]),g[p[j]].push_back(i);
// DFS 遍历最短路树
void dfs(int x)
{
    siz[x]=c[x];f[x]=true;
    for(vector<int>::iterator it=g[x].begin();it!=g[x].end();it++)
    if(!f[*it])dfs(*it),siz[x]+=siz[*it];
    ans=max(ans,siz[x]*(dist[x]-T));
}
```
核心思想：先根据最短路条件构建最短路树，再通过 DFS 遍历树，计算每个节点子树中奶牛的数量，进而更新最大减少量。

#### linluke
```cpp
// 建最短路树
for(int i = 1; i <= n; ++i)
    for(int c_e = head[i]; c_e; c_e = edges[c_e].next)
        if(dis[edges[c_e].to] == dis[i] + edges[c_e].dis &&!v2[edges[c_e].to]){
            v2[edges[c_e].to] = 1;
            vec[i].push_back(edges[c_e].to), vec[edges[c_e].to].push_back(i);
        }
// DFS 遍历最短路树
int DFS(int u){
    int v, cnt = 0; vis[u] = 1;
    for (int i = 0; i < vec[u].size(); ++i){
        v = vec[u][i];
        if (!vis[v])
            cnt += DFS(v);
    }
    cnt += a[u];
    ans = max(ans, (dis[u] - t) * cnt);
    return cnt;
}
```
核心思想：同样先构建最短路树，再通过 DFS 计算子树中奶牛数量，更新答案。

#### Na2PtCl6
```cpp
// 记录路径
void dij(int start){
    //...
    for(int i=0;i<g[ind].size();i++){
        edge now=g[ind][i];
        int to=now.to,l=dis[ind]+now.w;
        if(dis[to]>l){
            nxt[to]=ind;
            dis[to]=l;
            if(!vis[to])
                q.push((node){to,l});
        }
        if(dis[to]==l&&nxt[to]>ind)
            nxt[to]=ind;
    }
    //...
}
// 建树
for(int i=2;i<=n;i++){
    tree[i].push_back(nxt[i]);
    tree[nxt[i]].push_back(i);
}
// DFS 遍历树
void dfs(int node,int fa){
    for(int i=0;i<tree[node].size();i++){
        int now=tree[node][i];
        if(now==fa)
            continue;
        dfs(now,node);
        size[node]+=size[now];
    }
    res=_max(res,(dis[node]-t)*size[node]);
}
```
核心思想：先通过 Dijkstra 记录路径，再根据路径构建树，最后 DFS 遍历树计算最大减少量。

### 最优关键思路或技巧
- **最短路树的构建**：利用最短路算法（如 Dijkstra）求出最短路径，再根据 $dist_y = dist_x + edgeweight$ 的条件构建最短路树，同时通过从小到大枚举节点保证字典序最小。
- **DFS 遍历树**：通过深度优先搜索遍历最短路树，计算每个节点子树中奶牛的数量，从而方便计算添加近道后的减少量。

### 可拓展之处
同类型题或类似算法套路：
- 带权图中添加边使某些指标优化的问题，如添加边使图的直径最小等。
- 基于最短路树的其他应用，如计算树中节点的其他统计信息等。

### 推荐题目
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)：考察最短路算法的应用。
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：最短路模板题。
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：同样是最短路模板题，数据规模更大。

### 个人心得总结
- hsfzLZH1 提醒在 DFS 过程中，由于 $c_i$ 可能为 $0$，不能用 $siz$ 判断节点是否访问过，需增加附加数组。这是一个容易忽略的细节，在处理类似问题时要注意避免。 

---
处理用时：42.95秒