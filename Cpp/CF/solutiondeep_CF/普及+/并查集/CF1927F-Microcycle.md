# 题目信息

# Microcycle

## 题目描述

Given an undirected weighted graph with $ n $ vertices and $ m $ edges. There is at most one edge between each pair of vertices in the graph, and the graph does not contain loops (edges from a vertex to itself). The graph is not necessarily connected.

A cycle in the graph is called simple if it doesn't pass through the same vertex twice and doesn't contain the same edge twice.

Find any simple cycle in this graph in which the weight of the lightest edge is minimal.

## 样例 #1

### 输入

```
5
6 6
1 2 1
2 3 1
3 1 1
4 5 1
5 6 1
6 4 1
6 6
1 2 10
2 3 8
3 1 5
4 5 100
5 6 40
6 4 3
6 15
1 2 4
5 2 8
6 1 7
6 3 10
6 5 1
3 2 8
4 3 4
5 3 6
2 6 6
5 4 5
4 1 3
6 4 5
4 2 1
3 1 7
1 5 5
4 6
2 3 2
1 3 10
1 4 1
3 4 7
2 4 5
1 2 2
4 5
2 1 10
3 1 3
4 2 6
1 4 7
2 3 3```

### 输出

```
1 3
1 2 3 
3 3
6 4 5 
1 5
4 2 1 6 3 
1 4
1 4 3 2 
3 3
2 3 1```

# AI分析结果

### 题目内容翻译
## 微环

### 题目描述
给定一个具有 $n$ 个顶点和 $m$ 条边的无向加权图。图中每对顶点之间最多有一条边，并且图中不包含自环（从一个顶点到自身的边）。该图不一定是连通的。

如果图中的一个环不重复经过同一个顶点，也不包含同一条边两次，则称该环为简单环。

在这个图中找出任意一个简单环，使得该环中最轻边的权重最小。

### 样例 #1
#### 输入
```
5
6 6
1 2 1
2 3 1
3 1 1
4 5 1
5 6 1
6 4 1
6 6
1 2 10
2 3 8
3 1 5
4 5 100
5 6 40
6 4 3
6 15
1 2 4
5 2 8
6 1 7
6 3 10
6 5 1
3 2 8
4 3 4
5 3 6
2 6 6
5 4 5
4 1 3
6 4 5
4 2 1
3 1 7
1 5 5
4 6
2 3 2
1 3 10
1 4 1
3 4 7
2 4 5
1 2 2
4 5
2 1 10
3 1 3
4 2 6
1 4 7
2 3 3
```
#### 输出
```
1 3
1 2 3 
3 3
6 4 5 
1 5
4 2 1 6 3 
1 4
1 4 3 2 
3 3
2 3 1
```

### 综合分析与结论
这些题解主要围绕在无向加权图中寻找边权最小的简单环展开，多数题解都借助了图论中的经典算法，如 Kruskal 算法、Tarjan 算法、LCA 算法等。

#### 思路对比
- **Kruskal 算法思路**：yyrwlj、escapist404、SamHJD、Wf_yjqd 等题解采用此思路，将边按权值降序排序，利用并查集判断加入边时是否形成环，最后一个使环形成的边即为目标边，再通过 DFS 或 BFS 找出环上的点。
- **Tarjan 算法思路**：Diaоsi、MrPython、Zemu_Ooo、aeiouaoeiu 等题解运用 Tarjan 算法找出非割边（非桥边），在非割边中找到权值最小的边，然后通过 DFS 或 BFS 构建环。
- **DFS 树 + LCA 思路**：CYZZ 题解通过构建 DFS 树，找出非树边，利用倍增 LCA 计算每个非树边与树边构成的环的最小边权，取最小值得到结果。

#### 算法要点对比
- **Kruskal 算法**：核心是边排序和并查集操作，时间复杂度主要取决于排序，为 $O(m log m)$。
- **Tarjan 算法**：用于寻找割边（桥），时间复杂度为 $O(n + m)$。
- **DFS 树 + LCA**：构建 DFS 树和进行 LCA 计算，时间复杂度为 $O(m log n)$。

#### 解决难点对比
- **Kruskal 算法**：难点在于证明最后形成环的边是最小边权的边，以及如何找出环上的点。
- **Tarjan 算法**：准确找出所有非割边，并在这些边中确定最小边权的边，然后构建环。
- **DFS 树 + LCA**：构建 DFS 树和实现倍增 LCA 算法，以及处理多组测试数据时数组的初始化。

### 所选题解
- **CYZZ（5星）**
    - **关键亮点**：思路清晰，详细阐述了通过 DFS 树和倍增 LCA 解决问题的方法，代码注释丰富，易于理解。
    - **个人心得**：作者提到数组没清零暴调 3h，提醒大家多测时要清空数组，尤其是像 fa 数组这样的。
- **yyrwlj（4星）**
    - **关键亮点**：思路简洁明了，利用 Kruskal 算法的思想，结合 DFS 找出环，代码实现较为清晰。
- **Diaоsi（4星）**
    - **关键亮点**：提供了两种思路，一种是用 LCT 维护最小生成树，另一种是线性做法，通过边双连通分量和 DFS 解决问题，具有一定的创新性。

### 重点代码
#### CYZZ
```cpp
// 构建 DFS 树
void dfs1(int u,int fat)
{
    bk[u]=1;dfn[u]=++idx;
    for(int i=hd1[u];i;i=e1[i].next)
    {
        int v=e1[i].to;Edge tmp={u,v,e1[i].w};
        if(v==fat) continue;
        if(bk[v]) {vec.emplace_back(tmp);continue;}
        else add_edge2(u,v,e1[i].w);
        dfs1(v,u);
    }
}
// 倍增 LCA 计算
PII LCA(int x,int y)
{
    int ret=1e9;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--)
    {
        if(dep[fa[x][i]]>=dep[y])
            ret=min(ret,mn[x][i]),x=fa[x][i];
    }
    if(x==y) return {x,ret};
    for(int i=20;i>=0;i--)
    {
        if(fa[x][i]!=fa[y][i])
        {
            ret=min(ret,mn[x][i]),x=fa[x][i];
            ret=min(ret,mn[y][i]),y=fa[y][i];
        }
    }
    return {fa[x][0],min({ret,mn[x][0],mn[y][0]})};
}
```
**核心思想**：先构建 DFS 树，找出所有非树边，再通过倍增 LCA 计算每个非树边与树边构成的环的最小边权。

#### yyrwlj
```cpp
// 并查集查找
int find(int x)
{
    if (x == f[x])
        return x;
    return f[x] = find(f[x]);
}
// DFS 找环
bool dfs(int u,int fa)
{
    ans[++tot] = u;
    if (u == End)
    {
        printf("%d\n", tot);
        for (int i=1;i<=tot;i++)
            printf("%d ", ans[i]);
        putchar('\n');
        return true;
    }
    vis[u] = true;
    for (int i = h[u]; i; i = G[i].nxt)
    {
        int j = G[i].to;
        if (j == fa || vis[j])
            continue;
        if (dfs(j, u))
            return true;
    }
    tot --;
    return false;
}
```
**核心思想**：利用并查集判断加入边时是否形成环，最后通过 DFS 找出环上的点。

#### Diaоsi
```cpp
// Tarjan 找边双连通分量
void tarjan(int x,int fa=0)
{
    dfn[x]=low[x]=++num;
    st[++top]=x;
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(y==fa)continue;
        if(!dfn[y])
        {
            tarjan(y,x);
            low[x]=min(low[x],low[y]);
        }
        else low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x])
    {
        int y;++col;
        do
        {
            y=st[top--];
            bl[y]=col;
        }while(x!=y);
    }
}
// DFS 找环
bool dfs(int x,int fa,int t)
{
    st[++top]=x;v[x]=1;
    if(x==t)
    {
        printf("%d\n",top);
        for(int i=1;i<=top;i++)
            printf("%d ",st[i]);
        puts("");
        return 1;
    }
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(y==fa||v[y]||bl[y]!=bl[x])continue;
        if(dfs(y,x,t))return 1;
    }
    --top;
    return false;
}
```
**核心思想**：通过 Tarjan 算法找出边双连通分量，在边双连通分量中找到最小边权的边，然后通过 DFS 找出环。

### 最优关键思路或技巧
- **Kruskal 算法变种**：将边按权值降序排序，利用并查集判断环的形成，可有效找到最小边权的环。
- **Tarjan 算法**：用于快速找出非割边，缩小寻找最小边权环的范围。
- **倍增 LCA**：在处理树上路径问题时，能高效计算路径上的最小边权。

### 可拓展之处
- **同类型题**：寻找图中最大边权最小的环、寻找指定长度的最小边权环等。
- **类似算法套路**：在图论中，利用并查集、Tarjan 算法、LCA 算法解决环相关问题是常见的套路。

### 推荐题目
- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
- [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

### 个人心得摘录与总结
- **CYZZ**：数组没清零暴调 3h，提醒在多组测试数据时要注意数组的初始化，尤其是像 fa 数组这样在算法中起关键作用的数组。
- **Zemu_Ooo**：做这道题忘了图不连通，吃了两发罚时，强调在解题时要考虑图的连通性等特殊情况。 

---
处理用时：51.87秒