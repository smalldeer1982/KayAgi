# 题目信息

# [USACO09OCT] Heat Wave G

## 题目描述

有一个 $n$ 个点 $m$ 条边的无向图，请求出从 $s$ 到 $t$ 的最短路长度。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 2500$，$1\le m \le 6200$，$1\le w \le 1000$。

【样例说明】   
$5 \to 6 \to 1 \to 4$ 为最短路，长度为 $3+1+3 = 7$。



## 样例 #1

### 输入

```
7 11 5 4
2 4 2
1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1```

### 输出

```
7```

# AI分析结果

### 综合分析与结论
这些题解使用了多种算法来解决无向图的单源最短路径问题，包括Dijkstra（含无优化、堆优化、线段树优化、zkw线段树优化等）、SPFA、Ford、Floyd、Bellman等。各算法的时间复杂度和实现方式有所不同，Dijkstra系列算法在处理无负权边的图时表现较好，SPFA在某些情况下效率较高但不稳定，Ford和Bellman适用于存在负权边的图，Floyd则可用于求所有点对的最短路径。

### 所选题解
- **作者：yizimi远欣（赞：87）** - 4星
  - **关键亮点**：提出用线段树代替优先队列优化Dijkstra算法，思路新颖，代码实现详细且有注释。
  - **个人心得**：提到从集训大佬处学到此优化方法，对Dijkstra算法优化有新的思路。
- **作者：扬皓2006（赞：24）** - 4星
  - **关键亮点**：以堆优化的Dijkstra为解法，代码简洁明了，适合新手学习。
  - **个人心得**：引导不了解最短路算法的同学参考相关资料。
- **作者：R_a_v_e_n（赞：1）** - 4星
  - **关键亮点**：dijkstra代码最长用时8ms，效率较高，详细说明了优化思路，如用struct存边信息、vector存以某点为起点的边编号、pair存起点到各点距离等。
  - **个人心得**：提到题目数据范围导致RE两次，提醒注意数据范围。

### 重点代码及核心实现思想
#### 作者：yizimi远欣（线段树优化Dijkstra）
```cpp
// 线段树更新操作
inline void update(int rt){
    z[rt].minw = min(z[rt << 1].minw, z[rt << 1 | 1].minw);
    z[rt].minv = (z[rt << 1].minw < z[rt << 1 | 1].minw) ? z[rt << 1].minv : z[rt << 1 | 1].minv;
}
// 线段树建树操作
inline void build(int l,int r,int rt){
    if(l==r){
        z[rt].minw = l == s ? 0 : inf;
        z[rt].minv = l;
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    update(rt);
}
// 线段树单点修改操作
inline void modify(int l,int r,int rt,int now,int v){
    if(l==r){
        z[rt].minw = v;
        return;
    }
    int m = (l + r) >> 1;
    if(now<=m)
        modify(lson, now, v);
    else
        modify(rson, now, v);
    update(rt);
}
// Dijkstra核心部分
inline void Dij(){
    go(i,1,n,1){
        dis[i] = inf;
    }
    dis[s] = 0;
    while(tr.z[1].minw < inf){
        int x = tr.z[1].minv;
        tr.modify(root, x, inf);
        rep(i,x){
            int v = e[i].v;
            if(dis[v] > dis[x] + e[i].w){
                dis[v] = dis[x] + e[i].w;
                tr.modify(root, v, dis[x] + e[i].w);
            }
        }
    }
}
```
**核心实现思想**：用线段树维护dis数组的最小值及位置，通过单点修改模拟优先队列的出队和入队操作，每次取出线段树中最小值对应的点进行松弛操作。

#### 作者：扬皓2006（堆优化Dijkstra）
```cpp
// 插入边操作
void add(int x,int y,int z)
{
    edge[++tot].next=hea[x];
    edge[tot].to=y;
    edge[tot].dis=z;
    hea[x]=tot;
}
// 主函数部分
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&e);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    memset(d,0x3f,sizeof(d));
    memset(v,0,sizeof(v));
    d[s]=0;q.push(make_pair(0,s));
    while(!q.empty())
    {
        int x=q.top().second;q.pop();
        if(v[x]) continue;
        v[x]=1;
        for(int i=hea[x];i;i=edge[i].next)
        {
            int y=edge[i].to;
            if(d[y]>d[x]+edge[i].dis)
            {
                d[y]=d[x]+edge[i].dis;
                q.push(make_pair(-d[y],y));
            }
        }
    } 
    printf("%d",d[e]); 
    return 0; 
}
```
**核心实现思想**：用邻接表存图，优先队列（小根堆）存储待处理的点，每次取出距离起点最近的点进行松弛操作，更新其他点的距离并加入优先队列。

#### 作者：R_a_v_e_n（优化Dijkstra）
```cpp
// 主函数部分
int main()
{
    cin>>t>>c>>s>>e;
    for(int i=0;i<c;i++)
    {
        p=2*i,q=2*i+1;
        cin>>way[p].start>>way[p].finish>>way[p].lenth;
        way[q].start=way[p].finish;
        way[q].finish=way[p].start;
        way[q].lenth=way[p].lenth;
        point[way[p].start].push_back(p);
        point[way[q].start].push_back(q);
    }
    for(int i=1;i<=t;i++)
    {
        dis[i].first=infinite;
        dis[i].second=i;
        k.push(dis[i]);
    }
    dis[s].first=0;
    k.push(dis[s]);
    while(!b[e])
    {
        while(true)
        {
            x=k.top().second;
            if(b[x])
            {
                k.pop();
            }
            else
            {
                k.pop();
                b[x]=true;
                break;
            }
        }
        for(int i=point[x].size()-1;i>=0;i--)
        {
            if(!b[way[point[x][i]].finish]&&dis[way[point[x][i]].finish].first>dis[x].first+way[point[x][i]].lenth)
            {
                dis[way[point[x][i]].finish].first=dis[x].first+way[point[x][i]].lenth;
                k.push(dis[way[point[x][i]].finish]);
            }
        }
    }
    cout<<dis[e].first;
}
```
**核心实现思想**：用struct存边信息，vector存以某点为起点的边编号，pair存起点到各点距离，优先队列存储待处理的点，每次取出距离起点最近且未访问过的点进行松弛操作，更新其他点的距离并加入优先队列。

### 最优关键思路或技巧
- **数据结构**：使用邻接表（链式前向星、vector等）存图，可有效减少空间复杂度和遍历边的时间复杂度。
- **算法优化**：
  - **堆优化Dijkstra**：用优先队列（小根堆）快速找到距离起点最近的点，将时间复杂度从$O(n^2)$优化到$O((n + m)\log n)$。
  - **线段树优化Dijkstra**：用线段树代替优先队列维护dis数组的最小值及位置，可实现类似优先队列的功能。
- **代码实现技巧**：使用快读、快输优化输入输出，提高程序效率。

### 可拓展之处
- **同类型题**：存在负权边的单源最短路径问题可使用Bellman-Ford或SPFA算法；所有点对的最短路径问题可使用Floyd算法。
- **类似算法套路**：在图的遍历和搜索中，可根据图的特点选择合适的数据结构和算法，如邻接矩阵适用于稠密图，邻接表适用于稀疏图；广度优先搜索（BFS）和深度优先搜索（DFS）可用于图的遍历。

### 推荐题目
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.org/problemnew/show/P3371)
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.org/problem/P4779)
- [P1144 最短路计数](https://www.luogu.org/problem/P1144)

### 个人心得摘录与总结
- **yizimi远欣**：从集训大佬处学到线段树优化Dijkstra的方法，提醒注意无向图要正反两条边。
- **扬皓2006**：引导不了解最短路算法的同学参考相关资料。
- **R_a_v_e_n**：提到题目数据范围导致RE两次，提醒注意数据范围。
- **qq924675986**：看到数据范围较大，注意是无向图，贴出丑陋的spfa代码。
- **ExBritainia**：尝试用kruskal+dfs做最短路，结果得60分，提醒此方法不可行。
- **DaCong**：被无向图邻接表开两倍和读入优化问题坑到，提醒注意这些细节。

---
处理用时：62.27秒