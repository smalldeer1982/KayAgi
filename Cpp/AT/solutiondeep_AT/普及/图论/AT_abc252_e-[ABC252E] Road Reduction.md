# 题目信息

# [ABC252E] Road Reduction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc252/tasks/abc252_e

AtCoder 王国には都市 $ 1,2,\ldots,N $ の $ N $ 個の都市と、道路 $ 1,2,\ldots,M $ の $ M $ 本の道路があります。  
道路 $ i $ は都市 $ A_i $ と $ B_i $ を双方向に結び、距離は $ C_i $ です。  
どの都市間もいくつかの道路を通って行き来することができます。

財政難である王国は、どの都市間もいくつかの道路を通って行き来できるという条件を満たすように $ N-1 $ 本の道路を保守し、それ以外の道路を廃道にすることにしました。

保守する道路のみを通って都市 $ 1 $ から都市 $ i $ へ移動するときの距離を $ d_i $ とするとき、保守する道路の選び方であって、$ d_2+d_3+\ldots+d_N $ を最小化するようなものを $ 1 $ つ出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ i\neq\ j $ のとき、$ (A_i,B_i)\neq(A_j,B_j) $
- $ 1\leq\ C_i\ \leq\ 10^9 $
- どの都市間もいくつかの道路を通って行き来することができる
- 入力に含まれる値は全て整数である

### Sample Explanation 1

保守する道路の選び方と $ d_i $ の値は次のようになります。 - 道路 $ 1,2 $ を保守するとき、$ d_2=1 $, $ d_3=3 $ - 道路 $ 1,3 $ を保守するとき、$ d_2=1 $, $ d_3=10 $ - 道路 $ 2,3 $ を保守するとき、$ d_2=12 $, $ d_3=10 $ よって、道路 $ 1,2 $ を保守するときに $ d_2+d_3 $ が最小になります。

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 2
1 3 10```

### 输出

```
1 2```

## 样例 #2

### 输入

```
4 6
1 2 1
1 3 1
1 4 1
2 3 1
2 4 1
3 4 1```

### 输出

```
3 1 2```

# AI分析结果

### 题目翻译
在 AtCoder 王国，有编号为 $1,2,\ldots,N$ 的 $N$ 个城市，以及编号为 $1,2,\ldots,M$ 的 $M$ 条道路。
道路 $i$ 双向连接城市 $A_i$ 和 $B_i$，距离为 $C_i$。
任意两个城市之间都可以通过若干条道路相互通达。

由于财政困难，王国决定在满足任意两个城市之间都能通过若干条道路相互通达的条件下，保留 $N - 1$ 条道路，其余道路废弃。

设仅通过保留的道路从城市 $1$ 移动到城市 $i$ 的距离为 $d_i$，请输出一种保留道路的选择方案，使得 $d_2 + d_3 + \ldots + d_N$ 最小。

### 综合分析与结论
这些题解的核心思路都是利用 Dijkstra 算法来解决问题。因为 Dijkstra 算法在求单源最短路的过程中，对于连通图会形成一棵最短路径树，树中边的数量恰好为 $N - 1$ 条，且能保证从起点 $1$ 到其他各点的距离最短，满足题目要求。在实现上，部分题解使用了链式前向星存图，部分使用邻接表存图，在 Dijkstra 算法执行过程中，当发生松弛操作时记录下对应的边编号，最后输出除起点外各点对应的边编号即可。

### 所选题解
- **xixiyan（4星）**
    - **关键亮点**：使用链式前向星存图，代码注释详细，对边的编号处理有明确提示，思路清晰，适合初学者理解。
    - **核心代码**：
```cpp
struct bian{
    int w;
    int num;
}W[400001];
int head[200001],Nxt[400001],To[400001],tot;
void add(int x,int y,int w){
    W[++tot].w=w;
    To[tot]=y;
    Nxt[tot]=head[x];
    head[x]=tot;
}
// ...
while(!o_o.empty())
{
    int d=o_o.top().d;
    o_o.pop();
    if(vis[d]) continue;
    vis[d]=1;
    for(int i=head[d],y;i;i=Nxt[i])
    {
        y=To[i];
        if(dis[y]>dis[d]+W[i].w)
        {
            dis[y]=dis[d]+W[i].w;
            o_o.push((qwq){dis[y],y});
            ans[y]=W[i].num;
        }
    }
}
```
核心实现思想：先使用链式前向星存储图的信息，在 Dijkstra 算法的松弛过程中，当发现更短路径时，更新距离数组 `dis` 并记录下对应的边编号到 `ans` 数组中。

- **FL_sleake（4星）**
    - **关键亮点**：使用邻接表存图，代码结构清晰，对 Dijkstra 算法的优化有一定说明，思路简洁明了。
    - **核心代码**：
```cpp
struct node{
    int v,w,id;
    bool operator<(const node &b)const{
        return w>b.w;
    }
};
vector<node> G[200010];
// ...
void Dijkstra(){
    memset(dis,0x3f,sizeof(dis));
    q.push({1,0,0});
    dis[1]=0;
    while(!q.empty()){
        int u=q.top().v,D=q.top().w;
        q.pop();
        if(dis[u]<D) continue;
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i].v,w=G[u][i].w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                ans[v]=G[u][i].id;
                q.push({v,dis[v],0});
            }
        }
    }
}
```
核心实现思想：使用邻接表 `G` 存储图，在 Dijkstra 算法中，当从优先队列取出节点后，若其距离不是最短则跳过，否则遍历其邻接节点，若发现更短路径则更新距离并记录边编号。

- **FFTotoro（4星）**
    - **关键亮点**：代码简洁，使用 `pair` 和 `vector` 实现邻接表，利用 C++17 的结构化绑定简化代码，实现思路清晰。
    - **核心代码**：
```cpp
typedef pair<int,int> pii;
// ...
priority_queue<pii,vector<pii>,greater<> >q;
q.emplace(d[0]=0,0);
while(!q.empty()){
    auto [f,e]=q.top(); q.pop();
    if(f>d[e])continue;
    if(e)cout<<p[e]+1<<' ';
    for(auto [v,i]:g[e]){
        if(d[e]+w[i]>=d[v])continue;
        p[v]=i; q.emplace(d[v]=d[e]+w[i],v);
    }
}
```
核心实现思想：使用 `vector<vector<pii>>` 存储图，在 Dijkstra 算法中，利用结构化绑定取出优先队列中的元素，若距离不是最短则跳过，否则遍历邻接节点，若发现更短路径则更新距离并记录边编号。

### 最优关键思路或技巧
- **利用 Dijkstra 算法的性质**：Dijkstra 算法在求单源最短路的过程中会形成最短路径树，树中边的数量为 $N - 1$ 条，且能保证从起点到其他各点的距离最短，可直接利用这个性质来解决问题。
- **边编号的记录**：在 Dijkstra 算法的松弛操作中，当更新最短距离时，同时记录下对应的边编号，最后输出这些边编号即可。

### 可拓展之处
同类型题目通常涉及图的最短路问题，可能会有不同的约束条件，如边权有正负、图为有向图等。类似算法套路包括使用 Bellman - Ford 算法处理有负权边的图，使用 SPFA 算法（在某些情况下可能会超时）优化 Bellman - Ford 算法等。

### 洛谷相似题目
- P3371 【模板】单源最短路径（弱化版）
- P4779 【模板】单源最短路径（标准版）
- P1339 [USACO09OCT]Heat Wave G

### 个人心得摘录与总结
- **FL_sleake**：在 Dijkstra 算法中添加 `if(dis[u]<D) continue;` 判断，否则会在 `after_contest` 的数据上 TLE，但不清楚具体原因。总结：在实现算法时，要注意一些细节优化，即使不清楚具体原因，某些优化可能会避免超时问题。 

---
处理用时：42.69秒