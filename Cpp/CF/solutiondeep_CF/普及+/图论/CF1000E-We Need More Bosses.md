# 题目信息

# We Need More Bosses

## 题目描述

**题目大意：**

给定一个 $n$ 个点 $m$ 条边的无向图，保证图连通。找到两个点$s,t$，使得$s$到$t$**必须**经过的边最多（一条边无论走哪条路线都经过ta，这条边就是必须经过的边），$2<=n<=3*10^5,1<=m<=3*10^5$

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 1
4 1
5 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
1 2
4 3
3 2
```

### 输出

```
3
```

# AI分析结果

### 题目翻译
# 我们需要更多的首领

## 题目描述

**题目大意：**

给定一个具有 $n$ 个点和 $m$ 条边的无向图，确保该图是连通的。找出两个点 $s$ 和 $t$，使得从 $s$ 到 $t$ **必须**经过的边的数量最多（如果一条边无论走哪条路线都必然经过它，那么这条边就是必须经过的边），其中 $2\leq n\leq3\times10^5$，$1\leq m\leq3\times10^5$。

## 样例 #1

### 输入
```
5 5
1 2
2 3
3 1
4 1
5 2
```

### 输出
```
2
```

## 样例 #2

### 输入
```
4 3
1 2
4 3
3 2
```

### 输出
```
3
```

### 综合分析与结论
- **思路对比**：多数题解思路一致，先利用 Tarjan 算法找出边双连通分量，将同一边双内的点缩成一个点，把图转化为树，再求树的直径得到结果。仅 RyexAwl 的题解通过建生成森林、树上差分处理边权来求直径。
- **算法要点**：Tarjan 算法是关键，用于识别边双连通分量；缩点后求树的直径，常用方法有两次 DFS 或 BFS，也有用树形 DP 的。
- **解决难点**：主要难点在于理解边双连通分量的性质，即同一边双内的边对答案无贡献，需将其缩点；另外，树的直径求解方法的选择和实现也需要注意。

### 所选题解
- **小菜鸟（5星）**
    - **关键亮点**：思路清晰，详细阐述了边双连通分量和缩点的原理，代码注释丰富，可读性强。
    - **个人心得**：膜你赛时看错题意后秒出思路，交题时碰上 system test 跑了半小时才出结果。
- **TKXZ133（4星）**
    - **关键亮点**：思路分析简洁明了，直接点明答案是边双连通分量之间的割边数量，代码实现规范。
- **shame_djj（4星）**
    - **关键亮点**：对“必须经过的边”解释详细，算法流程清晰，代码结构清晰。

### 重点代码
#### 小菜鸟
```cpp
// Tarjan 算法求边双连通分量
void tarjan(int u,int fa)
{
    static std::stack<int> s;
    low[u]=dfn[u]=++cnt;
    s.push(u);
    for(int i=head[u];i;i=E[i].next)
    {
    	int v=E[i].to;
        if(v==fa)continue;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u]=std::min(low[u],low[v]);
        }
        else
        {
            if(cir[v]==0)low[u]=std::min(low[u],dfn[v]);
        }
    }
    if(low[u]!=dfn[u])return;
    cir_cnt++;
    while(1)
    {
        int x=s.top();
        s.pop();
        cir[x]=cir_cnt;
        if (x==u)break;
    }
}

// 两次 BFS 求树的直径
int bfs(int s)
{
    int res=s;
    memset(dis,0x3f,sizeof(dis));
    std::queue<int> q;
    q.push(s);
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(dis[v]!=0x3f3f3f3f)continue;
            dis[v]=dis[u]+1;
            q.push(v);
            if(dis[v]>dis[res])res=v;
        }
    }
    return res;
}
```
核心思想：先用 Tarjan 算法找出边双连通分量，将同一边双内的点标记为同一编号；再通过两次 BFS 找出树的直径。

#### TKXZ133
```cpp
// Tarjan 算法找桥
void tarjan(int s,int last){
    dfn[s]=low[s]=++cnt;
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(i==(last^1)) continue;
        if(!dfn[v]){
            tarjan(v,i);
            low[s]=min(low[s],low[v]);
            if(dfn[s]<=low[v]){bridge[i]=bridge[i^1]=1;}//找桥
        }
        else low[s]=min(low[s],dfn[v]);
    }
}

// DFS 标记点所在的连通分量
void dfs_0(int s){
    rid[s]=num;//记录点所在的连通分量
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(bridge[i]||rid[v]) continue;
        dfs_0(v);
    }
}

// 两次 DFS 求树的直径
void dfs_1(int s,int fa,int &u){
    for(int i=rhead[s];i;i=nxt[i]){
        int v=to[i];
        if(v==fa) continue;
        dis[v]=dis[s]+1;
        if(dis[0]<dis[v]){dis[0]=dis[v];u=v;}//找树的直径
        dfs_1(v,s,u);
    }
}
```
核心思想：通过 Tarjan 算法找出图中的桥，再用 DFS 标记点所在的连通分量，最后通过两次 DFS 求出树的直径。

#### shame_djj
```cpp
// Tarjan 算法求边双连通分量
void tarjan (int x, int in_edge) {
    dfn[x] = low[x] = ++ cnt_;
    for (register int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan (y, i);
            low[x] = min (low[x], low[y]);
            if (low[y] > dfn[x])
                cut[i] = cut[i ^ 1] = 1;
        }
        else if (i!= (in_edge ^ 1))
            low[x] = min (low[x], dfn[y]);
    }
}

// DFS 标记点所在的边双
void dfs (int x) {
    id[x] = gg;
    for (register int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (id[y] || cut[i]) continue;
        dfs (y);
    }
}

// 两次 DFS 求树的直径
void dfs_ (int x, int s) {
    vis[x] = 1;
    if (s > s_)
        s_ = s, id_ = x;
    for (register int i = 0; i < h[x].size (); i ++)
        if (!vis[h[x][i]])
            dfs_ (h[x][i], s + 1);
}
```
核心思想：用 Tarjan 算法找出边双连通分量，标记割边；再用 DFS 标记点所在的边双；最后通过两次 DFS 求出树的直径。

### 最优关键思路或技巧
- **思维方式**：利用边双连通分量的性质，将图转化为树，把复杂的图问题转化为简单的树问题。
- **算法优化**：使用 Tarjan 算法高效找出边双连通分量。
- **代码实现技巧**：用栈来辅助 Tarjan 算法的实现，方便标记边双内的点。

### 拓展思路
同类型题可考虑有向图的强连通分量缩点问题，或在树的基础上增加一些条件，如边有权值，求最大权值路径等。类似算法套路可用于解决其他图的连通性问题，如求割点、桥等。

### 推荐题目
- [P2860 冗余路径](https://www.luogu.com.cn/problem/P2860)：考察边双连通分量的知识。
- [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)：涉及强连通分量缩点。
- [P4016 负载平衡问题](https://www.luogu.com.cn/problem/P4016)：与图的连通性和优化有关。

### 个人心得总结
- 小菜鸟：膜你赛时看错题意后仍能快速想出思路，但交题时遇到 system test 耗时久的问题。
- shame_djj：一遍 AC 很舒适，强调写代码要有清晰思路，同时提醒新 Noip 前要复习知识。
- wcyQwQ：寒假听课时没做出此题，近期补题，说明学习是一个循序渐进的过程。
- 大菜鸡 fks：代码去掉 vis 数组后出现问题，长时间未找出错误，提醒在调试代码时要注意细节。 

---
处理用时：56.14秒