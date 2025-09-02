# 题目信息

# [USACO08OCT] Power Failure G

## 题目描述

A vicious thunderstorm has destroyed some of the wires of the farm's electrical power grid! Farmer John has a map of all $N$ ($2\le N \le 1000$) of the powerpoles, which are conveniently numbered $1\ldots N$ and located on integer plane coordinates $(x_i,y_i)$ ($-100000 \le x_i \le 100000, -100000 \le y_i \le 100000$).

Some $W$ ($1 \le W \le 10000$) power wires connect pairs of power poles $P_i$ and $P_j$ ($1 \le Pi \le N, 1 \le Pj \le N$).

He needs to get power from pole $1$ to pole $N$ (which means that some series of wires can traverse from pole $1$ to pole $N$, probably through some intermediate set of poles).

Given the locations of the $N$ poles and the list of remaining power wires, determine the minimum length of power wire required to restore the electrical connection so that electricity can flow from pole $1$ to pole $N$.  No wire can be longer than some real number $M$ ($0.0 < M \le 200000.0$).

As an example, below on the left is a map of the $9$ poles and $3$ wires after the storm. For this task, $M = 2.0$. The best set of wires to add would connect poles $4$ and $6$ and also poles $6$ and $9$.

```cpp
   After the storm              Optimally reconnected
3  . . . 7 9 . . . . .          3  . . . 7 9 . . . . .
                                          /
2  . . 5 6 . . . . . .          2  . . 5 6 . . . . . .
                                        /
1  2-3-4 . 8 . . . . .          1  2-3-4 . 8 . . . . .
   |                               |
0  1 . . . . . . . . .          0  1 . . . . . . . . .

   0 1 2 3 4 5 6 7 8 9             0 1 2 3 4 5 6 7 8 9
```

The total length is then $1.414213562 + 1.414213562 = 2.828427124$.

POINTS: 350


## 说明/提示

Just as in the diagram above.


As above.


## 样例 #1

### 输入

```
9 3 
2.0 
0 0 
0 1 
1 1 
2 1 
2 2 
3 2 
3 3 
4 1 
4 3 
1 2 
2 3 
3 4 
```

### 输出

```
2828 
```

# AI分析结果

### 综合分析与结论
这些题解均围绕单源最短路问题展开，核心思路是先构建图，将已有电线的边权设为 0，其他边权按两点距离计算，若超过给定长度限制则设为无穷大，最后使用最短路算法（主要是 Dijkstra 和 SPFA）求解从点 1 到点 n 的最短路径。各题解的差异主要体现在实现方式（邻接矩阵、前向星、vector 等）和最短路算法的选择及优化上。

### 所选题解
- **作者：火车司机**（4星）
    - **关键亮点**：思路清晰，代码注释详细，使用前向星建图，Dijkstra 算法求解，对建图和输出格式的注意点有明确提示。
    - **个人心得**：强调了此题是无向图，建边时要建两条边，以及输出格式需根据样例推出是 1000 倍的最短路长度保留整数。
- **作者：yx666**（4星）
    - **关键亮点**：对题意、分析和代码实现都有详细的说明，考虑了建边和求距离时的坑点，使用堆优化的 Dijkstra 算法，时间复杂度较优。
    - **个人心得**：指出已有电线要老实加边，否则会得 80 分；求两点距离时开平方根里面的可能爆 int，会得 90 分。
- **作者：rnf5114**（4星）
    - **关键亮点**：使用堆优化的 Dijkstra 算法，代码简洁，思路明确，直接暴力建边，对距离大于限制的情况不连边。

### 重点代码及核心实现思想
#### 作者：火车司机
```cpp
inline void add(int u, int v, double w) {
    e[++tot].u = h[u], e[tot].v = v, e[tot].w = w, h[u] = tot;
}
// 建图，对于幸存的电线边权设为 0，其他边按距离计算，若不超过 m 则建边
for (ri i = 1; i <= w; i++) scanf("%d%d", &x, &y), add(x, y, 0), add(y, x, 0);
for (ri i = 1; i <= n; i++)
    for (ri j = i + 1; j <= n; j++) {
        d = sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));
        if (d <= m) add(i, j, d), add(j, i, d);
    }
// Dijkstra 算法
dis[1] = 0, q.push((node) {0,1});
while (!q.empty()) {
    t = q.top(), q.pop();
    if (vis[t.p]) continue;
    vis[t.p] = 1;
    for (ri i = h[t.p]; i; i = e[i].u)
        if (dis[t.p] + e[i].w < dis[e[i].v])
            dis[e[i].v] = dis[t.p] + e[i].w, q.push((node) {dis[e[i].v],e[i].v});
}
```
核心思想：先使用前向星建图，将已有电线的边权设为 0，其他边按距离计算，若不超过 m 则建边。然后使用 Dijkstra 算法求解最短路。

#### 作者：yx666
```cpp
inline double get_dis(const pii&a,const pii&b){
    return sqrt((ll)(a.first-b.first)*(a.first-b.first)+(ll)(a.second-b.second)*(a.second-b.second));
}
// 建图
for(int i=2;i<=n;++i){
    for(int j=1;j<i;++j){
        double t=get_dis(pos[i],pos[j]);
        if(t<=m){
            val[i][j]=val[j][i]=t;
            mp[i].push_back(j);
            mp[j].push_back(i);
        }else{
            val[i][j]=val[j][i]=inf;
        }
    }
}
int a,b;
for(int i=1;i<=w;++i){
    cin>>a>>b;
    mp[a].push_back(b);
    mp[b].push_back(a);
    val[a][b]=val[b][a]=0.0f;
}
// 堆优化 Dijkstra 算法
inline void dij(){
    fill(dis,dis+1+n,inf);
    dis[1]=0.0f;
    using T=pair<double,int>;
    priority_queue<T,vector<T>,greater<T> >q;
    q.push({dis[1],1});
    int now;
    while(q.size()){
        now=q.top().second;
        q.pop();
        if(vis[now]) continue;
        vis[now]=1;
        for(auto to:mp[now]){
            if(!vis[to]&&dis[to]>dis[now]+val[now][to]){
                dis[to]=dis[now]+val[now][to];
                q.push({dis[to],to});
            }
        }
    }
    return;
}
```
核心思想：先计算两点间距离，若不超过 m 则建边，已有电线的边权设为 0。然后使用堆优化的 Dijkstra 算法求解最短路。

#### 作者：rnf5114
```cpp
double calc(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
// 建图
for(int i=1;i<=w;i++){
    int x,y;
    cin>>x>>y;
    v[x].push_back({y,0});
    v[y].push_back({x,0});
}
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        if(j!=i&&calc(i,j)<=m)
            v[i].push_back({j,calc(i,j)});
// 堆优化 Dijkstra 算法
void dij(){
    for(int i=1;i<=n;i++)
        dis[i]=1e15+10;
    dis[1]=0;
    q.push({0,1});
    while(!q.empty()){
        pair<int,int>tmp=q.top();
        q.pop();
        if(-tmp.first>dis[tmp.second])
            continue;
        for(int i=0;i<v[tmp.second].size();i++){
            int x=tmp.second,tmp1=v[tmp.second][i].y;
            if(dis[x]+v[x][i].z<dis[tmp1])
                dis[tmp1]=dis[x]+v[x][i].z,q.push({-dis[tmp1],tmp1});
        }
    }
}
```
核心思想：先将已有电线的边权设为 0，其他边按距离计算，若不超过 m 则建边。然后使用堆优化的 Dijkstra 算法求解最短路。

### 最优关键思路或技巧
- **建图技巧**：将已有电线的边权设为 0，其他边按两点距离计算，若超过给定长度限制则设为无穷大。
- **算法优化**：使用堆优化的 Dijkstra 算法，时间复杂度为 $O((n + m)\log n)$，可提高效率。
- **注意细节**：注意无向图建边要建两条边，求两点距离时要考虑数据范围，避免爆 int。

### 可拓展之处
同类型题：涉及图的最短路问题，如带权图中求两点间最短路径、有边权限制的最短路问题等。类似算法套路可用于解决网络规划、路径选择等实际问题。

### 推荐题目
- P3371【模板】单源最短路径（Dijkstra 算法模板题）
- P4779【模板】单源最短路径（标准版，可使用堆优化 Dijkstra 算法）
- P1144 最短路计数（在求最短路的基础上统计最短路的数量）

---
处理用时：58.35秒