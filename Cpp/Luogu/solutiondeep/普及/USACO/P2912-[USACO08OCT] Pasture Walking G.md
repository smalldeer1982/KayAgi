# 题目信息

# [USACO08OCT] Pasture Walking G

## 题目描述

The N cows (2 <= N <= 1,000) conveniently numbered 1..N are grazing among the N pastures also conveniently numbered 1..N. Most conveniently of all, cow i is grazing in pasture i.

Some pairs of pastures are connected by one of N-1 bidirectional walkways that the cows can traverse. Walkway i connects pastures A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N) and has a length of L\_i (1 <= L\_i <= 10,000).

The walkways are set up in such a way that between any two distinct pastures, there is exactly one path of walkways that travels between them. Thus, the walkways form a tree.

The cows are very social and wish to visit each other often. Ever in a hurry, they want you to help them schedule their visits by computing the lengths of the paths between 1 <= L\_i <= 10,000 pairs of pastures (each pair given as a query p1,p2 (1 <= p1 <= N; 1 <= p2 <= N).

POINTS: 200

有N(2<=N<=1000)头奶牛，编号为1到W，它们正在同样编号为1到N的牧场上行走.为了方 便，我们假设编号为i的牛恰好在第i号牧场上.

有一些牧场间每两个牧场用一条双向道路相连，道路总共有N - 1条，奶牛可以在这些道路 上行走.第i条道路把第Ai个牧场和第Bi个牧场连了起来(1 <= A\_i <= N; 1 <= B\_i <= N)，而它的长度 是 1 <= L\_i <= 10,000.在任意两个牧场间，有且仅有一条由若干道路组成的路径相连.也就是说，所有的道路构成了一棵树.

奶牛们十分希望经常互相见面.它们十分着急，所以希望你帮助它们计划它们的行程，你只 需要计算出Q(1 < Q < 1000)对点之间的路径长度•每对点以一个询问p1,p2 (1 <= p1 <= N; 1 <= p2 <= N). 的形式给出.



## 说明/提示

Query 1: The walkway between pastures 1 and 2 has length 2.

Query 2: Travel through the walkway between pastures 3 and 4, then the one between 4 and 1, and finally the one between 1 and 2, for a total length of 7.


## 样例 #1

### 输入

```
4 2 
2 1 2 
4 3 2 
1 4 3 
1 2 
3 2 
```

### 输出

```
2 
7 
```

# AI分析结果



### 综合分析与结论
本题核心在于高效计算树上两点间路径长度，各题解围绕LCA算法展开，主流解法包括倍增法、树链剖分、Tarjan离线LCA等。关键思路是将路径长度拆解为节点到根的距离差，即 `dist(u,v) = dist[u] + dist[v] - 2*dist[lca(u,v)]`。不同解法在预处理效率、代码复杂度、适用场景上各有优劣。

---

### 精选题解列表（评分≥4星）

#### 1. bztMinamoto（★★★★★）
**关键亮点**：  
- 完整讲解倍增与树剖两种主流解法，代码规范，注释清晰  
- 树剖实现效率高（预处理O(N)，查询O(logN)），倍增解法在线处理适合动态场景  
- 提供两种实现代码，对比学习价值高  

**核心代码（树剖LCA）**：  
```cpp
void dfs(int u){
    siz[u]=1; int maxson=-1;
    for(int i=head[u];i;i=edge[i].u){
        int v=edge[i].v;
        if(v==f[u][0]) continue;
        len[v]=len[u]+edge[i].w; // 维护到根距离
        dfs(v); siz[u]+=siz[v];
        if(siz[v]>maxson) son[u]=v, maxson=siz[v];
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]]) swap(x,y);
        x=f[top[x]][0];
    }
    return d[x]<d[y] ? x : y;
}
```

---

#### 2. Watermatter（★★★★☆）
**关键亮点**：  
- 倍增LCA标准实现，代码可读性强，注释详细  
- 预处理节点深度与2^k级祖先，通过二进制拆分高效跳转  
- 适合作为模板代码学习  

**核心代码（倍增预处理）**：  
```cpp
void dfs(int u,int d){
    dep[u]=d; vis[u]=1;
    for(int i=now[u];i;i=pre[i]){
        int v=son[i];
        if(!vis[v]){
            f[v][0]=u; val[v]=val[u]+len[i];
            dfs(v,d+1);
        }
    }
}
void dp(){
    for(int i=1;i<=19;i++)
        for(int j=1;j<=n;j++)
            f[j][i]=f[f[j][i-1]][i-1];
}
```

---

#### 3. Dijkspfa（★★★★☆）
**关键亮点**：  
- Tarjan离线LCA实现，时间复杂度最优（O(N+Q)）  
- 并查集优化路径压缩，巧妙利用DFS遍历特性  
- 适合处理批量查询场景  

**核心代码（Tarjan离线处理）**：  
```cpp
void dfs(int p){
    vis[p]=1; f[p]=p;
    for(auto &e:G[p]){
        if(vis[e.to]) continue;
        len[e.to]=len[p]+e.w;
        dfs(e.to); f[e.to]=p;
    }
    for(auto &q:queries[p]){
        if(vis[q.v]) 
            ans[q.id]=len[p]+len[q.v]-2*len[find(q.v)];
    }
}
```

---

### 最优思路总结
**关键技巧**：  
1. **LCA核心公式**：`dist(u,v)=dist[u]+dist[v]-2*dist[lca]`  
2. **倍增法**：预处理每个节点的2^k级祖先和距离，通过二进制拆分跳转  
3. **树剖优化**：重链划分减少跳跃次数，将树结构转化为链式查询  
4. **离线处理**：Tarjan算法通过DFS与并查集合并查询  

---

### 推荐相似题目
1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)  
2. [P3884 [JLOI2008]二叉树问题](https://www.luogu.com.cn/problem/P3884)  
3. [P3398 仓鼠找sugar](https://www.luogu.com.cn/problem/P3398)  

---

### 个人心得摘录
1. **调试经验**：  
   - "树剖实现时注意重链顶端的更新，轻边要单独处理"（雪颜）  
   - "倍增预处理循环顺序易错，应先处理低bit再处理高bit"（Watermatter）  
2. **优化技巧**：  
   - "Tarjan离线处理时合并查询集合能极大提升效率"（Dijkspfa）  
3. **思维突破**：  
   - "发现路径长度可转化为到根距离的线性组合，是本题关键突破口"（bztMinamoto）

---
处理用时：83.67秒