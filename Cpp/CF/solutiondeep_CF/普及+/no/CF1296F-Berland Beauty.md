# 题目信息

# Berland Beauty

## 题目描述

There are $ n $ railway stations in Berland. They are connected to each other by $ n-1 $ railway sections. The railway network is connected, i.e. can be represented as an undirected tree.

You have a map of that network, so for each railway section you know which stations it connects.

Each of the $ n-1 $ sections has some integer value of the scenery beauty. However, these values are not marked on the map and you don't know them. All these values are from $ 1 $ to $ 10^6 $ inclusive.

You asked $ m $ passengers some questions: the $ j $ -th one told you three values:

- his departure station $ a_j $ ;
- his arrival station $ b_j $ ;
- minimum scenery beauty along the path from $ a_j $ to $ b_j $ (the train is moving along the shortest path from $ a_j $ to $ b_j $ ).

You are planning to update the map and set some value $ f_i $ on each railway section — the scenery beauty. The passengers' answers should be consistent with these values.

Print any valid set of values $ f_1, f_2, \dots, f_{n-1} $ , which the passengers' answer is consistent with or report that it doesn't exist.

## 样例 #1

### 输入

```
4
1 2
3 2
3 4
2
1 2 5
1 3 3```

### 输出

```
5 3 5```

## 样例 #2

### 输入

```
6
1 2
1 6
3 1
1 5
4 1
4
6 1 3
3 4 1
6 5 2
1 2 5```

### 输出

```
5 3 1 2 1```

## 样例 #3

### 输入

```
6
1 2
1 6
3 1
1 5
4 1
4
6 1 1
3 4 3
6 5 3
1 2 4```

### 输出

```
-1```

# AI分析结果

### 题目翻译
## 伯兰美景

### 题目描述
伯兰有 $n$ 个火车站。它们由 $n - 1$ 条铁路段相互连接。铁路网络是连通的，即可以表示为一棵无向树。

你有该网络的地图，因此对于每条铁路段，你都知道它连接哪些车站。

$n - 1$ 条铁路段中的每一段都有一些整数值的风景美丽度。然而，这些值没有标记在地图上，你也不知道它们。所有这些值都在 $1$ 到 $10^6$ 之间（包括 $1$ 和 $10^6$）。

你向 $m$ 位乘客询问了一些问题：第 $j$ 位乘客告诉你三个值：
- 他的出发站 $a_j$；
- 他的到达站 $b_j$；
- 从 $a_j$ 到 $b_j$ 路径上的最小风景美丽度（火车沿着从 $a_j$ 到 $b_j$ 的最短路径行驶）。

你计划更新地图，并在每条铁路段上设置一些值 $f_i$ —— 风景美丽度。乘客的回答应该与这些值一致。

打印任何一组有效的值 $f_1, f_2, \dots, f_{n - 1}$，使得乘客的回答与之一致，或者报告不存在这样的值。

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，先将乘客的询问按照最小风景美丽度从小到大排序，然后依次处理每个询问，将路径上的边权赋值为该询问的最小风景美丽度，最后检查是否满足所有询问条件。各题解的主要区别在于实现细节，如使用不同的方法求最近公共祖先（LCA）、不同的图的存储方式等。

### 所选题解
- **ix35（4星）**
    - **关键亮点**：思路清晰，代码注释较详细，使用倍增法求 LCA，实现了边权的赋值和检查过程。
- **Awdrgysxc（4星）**
    - **关键亮点**：代码结构清晰，使用邻接表存储图，暴力处理路径上的边权更新和检查，还提到了对于更大数据范围的优化思路。
- **Zimo_666（4星）**
    - **关键亮点**：同样使用倍增法求 LCA，代码实现简洁，对边权的赋值和检查逻辑明确。

### 重点代码
#### ix35 的代码核心片段
```cpp
// 倍增求 LCA
void dfs (int x,int fa) {
    f[x][0]=fa,dep[x]=dep[fa]+1;
    for (int i=1;i<=15;i++) {f[x][i]=f[f[x][i-1]][i-1];}
    for (int i=hd[x];i;i=nx[i]) {
        if (ver[i]==fa) {continue;}
        num[ver[i]]=(i+1)/2;
        dfs(ver[i],x);
    }
}
int query_lca (int x,int y) {
    if (dep[x]<dep[y]) {swap(x,y);}
    for (int i=15;i>=0;i--) {
        if (dep[x]-(1<<i)>=dep[y]) {x=f[x][i];}
    }
    if (x==y) {return x;}
    for (int i=15;i>=0;i--) {
        if (f[x][i]!=f[y][i]) {x=f[x][i],y=f[y][i];}
    }
    return f[x][0];
}
// 修改路径上的边权
void modify (int u,int v,int we) {
    int l=query_lca(u,v);
    while (u!=l) {
        w[num[u]]=we;
        u=f[u][0];
    }
    while (v!=l) {
        w[num[v]]=we;
        v=f[v][0];
    }
}
// 查询路径上的最小边权
int query (int u,int v) {
    int l=query_lca(u,v);
    int res=1000001;
    while (u!=l) {
        res=min(res,w[num[u]]);
        u=f[u][0];
    }
    while (v!=l) {
        res=min(res,w[num[v]]);
        v=f[v][0];
    }
    return res;
}
```
**核心实现思想**：通过 `dfs` 函数预处理节点的深度和倍增数组，`query_lca` 函数利用倍增法求两个节点的最近公共祖先，`modify` 函数将路径上的边权赋值为指定值，`query` 函数查询路径上的最小边权。

#### Awdrgysxc 的代码核心片段
```cpp
// 深度优先搜索预处理节点信息
void dfs(int u, int pre) {
    int si = int(adj[u].size());
    fa[u] = pre, dep[u] = dep[pre] + 1;
    for (int i = 0;i < si; ++i) {
        int v = adj[u][i].first;
        if (v == pre) continue;
        dfs(v, u), id[v] = adj[u][i].second;
    }
}
// 修改路径上的边权
void modify(int u, int v, int w) {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) {
        f[id[u]] = max(f[id[u]], w);
        u = fa[u];
    }
    while (u != v) {
        f[id[u]] = max(f[id[u]], w),
        f[id[v]] = max(f[id[v]], w),
        u = fa[u],
        v = fa[v];
    }
}
// 查询路径上的最小边权并检查是否满足条件
bool query(int u, int v, int w) {
    int res = 2e9;
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) {
        res = min(f[id[u]], res);
        if (res < w) return false;
        u = fa[u];
    }
    while (u != v) {
        res = min(f[id[u]], res),
        res = min(f[id[v]], res);
        if (res < w) return false;
        u = fa[u],
        v = fa[v];
    }
    return w == res;
}
```
**核心实现思想**：`dfs` 函数预处理节点的父节点和深度信息，`modify` 函数更新路径上的边权为最大值，`query` 函数查询路径上的最小边权并检查是否等于指定值。

#### Zimo_666 的代码核心片段
```cpp
// 深度优先搜索预处理节点信息
void dfs(int x,int fa){
    for(int i=head[x];i;i=nxt[i]){
        int y=to[i];
        if(y==fa) continue;
        num[y]=(i+1)/2;
        dep[y]=dep[x]+1;fat[y]=x;dfs(y,x);
    }
}
// 初始化倍增数组
void init(){
    for(int i=1;i<=n;i++) f[i][0]=fat[i];
    for(int j=1;j<=20;j++){
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
        }
    }
}
// 求最近公共祖先
int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    if (dep[x] != dep[y]) {
        for (int i = 20; i >= 0; i--)
            if (dep[f[x][i]] > dep[y])
                x = f[x][i];
        x = f[x][0];
    }
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
// 修改路径上的边权
void modify(int u,int v,int val){
    int _lca=lca(u,v);
    while(u!=_lca) w[num[u]]=val,u=f[u][0];
    while(v!=_lca) w[num[v]]=val,v=f[v][0];
}
// 查询路径上的最小边权
int query(int u,int v){
    int _lca=lca(u,v);
    int res=0x3f3f3f3f;
    while(u!=_lca) res=min(res,w[num[u]]),u=f[u][0];
    while(v!=_lca) res=min(res,w[num[v]]),v=f[v][0];
    return res;
}
```
**核心实现思想**：`dfs` 函数预处理节点信息，`init` 函数初始化倍增数组，`lca` 函数求最近公共祖先，`modify` 函数更新路径上的边权，`query` 函数查询路径上的最小边权。

### 可拓展之处
同类型题可能会有更复杂的树结构或更多的限制条件，类似算法套路可以考虑使用树链剖分等更高效的数据结构来处理路径操作，以应对更大的数据范围。

### 洛谷相似题目推荐
- [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
- [P1967 [NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)
- [P2420 让我们异或吧](https://www.luogu.com.cn/problem/P2420)

### 个人心得摘录与总结
- **Karry5307**：提到如果 TLE/WA on 148 要注意数组是否开小了，提醒我们在写代码时要注意数组大小的问题，避免因数组越界导致错误。

---
处理用时：64.81秒