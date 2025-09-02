# 题目信息

# Greedy Merchants

## 题目描述

In ABBYY a wonderful Smart Beaver lives. This time, he began to study history. When he read about the Roman Empire, he became interested in the life of merchants.

The Roman Empire consisted of $ n $ cities numbered from $ 1 $ to $ n $ . It also had $ m $ bidirectional roads numbered from $ 1 $ to $ m $ . Each road connected two different cities. Any two cities were connected by no more than one road.

We say that there is a path between cities $ c_{1} $ and $ c_{2} $ if there exists a finite sequence of cities $ t_{1},t_{2},...,t_{p} $ $ (p>=1) $ such that:

- $ t_{1}=c_{1} $
- $ t_{p}=c_{2} $
- for any $ i $ $ (1<=i<p) $ , cities $ t_{i} $ and $ t_{i+1} $ are connected by a road

We know that there existed a path between any two cities in the Roman Empire.

In the Empire $ k $ merchants lived numbered from $ 1 $ to $ k $ . For each merchant we know a pair of numbers $ s_{i} $ and $ l_{i} $ , where $ s_{i} $ is the number of the city where this merchant's warehouse is, and $ l_{i} $ is the number of the city where his shop is. The shop and the warehouse could be located in different cities, so the merchants had to deliver goods from the warehouse to the shop.

Let's call a road important for the merchant if its destruction threatens to ruin the merchant, that is, without this road there is no path from the merchant's warehouse to his shop. Merchants in the Roman Empire are very greedy, so each merchant pays a tax (1 dinar) only for those roads which are important for him. In other words, each merchant pays $ d_{i} $ dinars of tax, where $ d_{i} $ ( $ d_{i}>=0 $ ) is the number of roads important for the $ i $ -th merchant.

The tax collection day came in the Empire. The Smart Beaver from ABBYY is very curious by nature, so he decided to count how many dinars each merchant had paid that day. And now he needs your help.

## 说明/提示

The given sample is illustrated in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178B1/4913bb025cb3137535b72c7a1543583701455251.png)Let's describe the result for the first merchant. The merchant's warehouse is located in city $ 1 $ and his shop is in city $ 5 $ . Let us note that if either road, $ (1,2) $ or $ (2,3) $ is destroyed, there won't be any path between cities $ 1 $ and $ 5 $ anymore. If any other road is destroyed, the path will be preserved. That's why for the given merchant the answer is $ 2 $ .

## 样例 #1

### 输入

```
7 8
1 2
2 3
3 4
4 5
5 6
5 7
3 5
4 7
4
1 5
2 4
2 6
4 7
```

### 输出

```
2
1
2
0
```

# AI分析结果

### 题目内容
# 贪婪的商人

## 题目描述
在ABBYY住着一只聪明的海狸。这次，它开始研究历史。当它读到罗马帝国时，对商人的生活产生了兴趣。

罗马帝国由$n$个城市组成，编号从$1$到$n$。它还有$m$条双向道路，编号从$1$到$m$。每条道路连接两个不同的城市。任意两个城市之间最多只有一条道路相连。

如果存在一个有限的城市序列$t_1,t_2,\cdots,t_p$ （$p\geq1$），使得：
 - $t_1 = c_1$
 - $t_p = c_2$
 - 对于任意的$i$（$1\leq i < p$），城市$t_i$和$t_{i + 1}$通过一条道路相连
我们就说城市$c_1$和$c_2$之间存在一条路径。

我们知道在罗马帝国中任意两个城市之间都存在路径。

在帝国中住着$k$个商人，编号从$1$到$k$。对于每个商人，我们知道一对数字$s_i$和$l_i$，其中$s_i$是这个商人仓库所在城市的编号，$l_i$是他商店所在城市的编号。商店和仓库可能位于不同的城市，所以商人们必须把货物从仓库运到商店。

如果一条道路的破坏会威胁到某个商人，也就是说，没有这条道路，就没有从这个商人的仓库到他商店的路径，那么我们称这条道路对这个商人来说是重要的。罗马帝国的商人非常贪婪，所以每个商人只对那些对他来说重要的道路交税（1第纳尔）。换句话说，每个商人支付$d_i$第纳尔的税，其中$d_i$（$d_i\geq0$）是对第$i$个商人来说重要的道路的数量。

帝国的收税日到了。来自ABBYY的聪明海狸生性好奇，所以它决定数一数每个商人那天交了多少第纳尔。现在它需要你的帮助。

## 说明/提示
给定的样例如下图所示。
![样例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178B1/4913bb025cb3137535b72c7a1543583701455251.png)
让我们来描述第一个商人的结果。这个商人的仓库位于城市$1$，他的商店位于城市$5$。我们注意到，如果道路$(1,2)$或$(2,3)$中的任何一条被破坏，城市$1$和$5$之间就不再有路径了。如果其他任何一条道路被破坏，路径仍然存在。这就是为什么对于这个给定的商人，答案是$2$。

## 样例 #1
### 输入
```
7 8
1 2
2 3
3 4
4 5
5 6
5 7
3 5
4 7
4
1 5
2 4
2 6
4 7
```
### 输出
```
2
1
2
0
```

### 算法分类
图论

### 题解综合分析与结论
这些题解的核心思路都是通过边双连通分量缩点，将原图转化为树，把问题转化为求树上两点间的距离，即割边数量，使用LCA（最近公共祖先）算法求解。
- **思路方面**：均先明确关键边即割边，利用边双连通分量性质，将边双连通分量缩成点，使原图变为树，树上边皆为割边，然后通过LCA求树上两点距离得出关键边数量。
- **算法要点**：都要进行Tarjan算法求边双连通分量，之后构建缩点后的图，再用DFS等方式初始化LCA相关数组，最后通过LCA计算两点间割边数。
- **解决难点**：主要难点在于理解边双连通分量与割边关系，以及缩点后图的构建和LCA的运用。部分题解提到要注意缩点后连边可能出现重边情况，不同题解在处理方式上有差异。

### 所选的题解
#### 作者：Isshiki·Iroha (5星)
- **关键亮点**：思路讲解详细，结合配图清晰展示边双连通分量和割边关系，代码实现完整且有注释，还包含快速读入输出模板。
- **个人心得**：无

```cpp
// Tarjan求边双连通分量
void Tarjan(int u){
    dfn[u]=low[u]=++dfstime;
    Instack[u]=1;
    St[++top]=u;
    for(int i(head[u]);i;i=kano[i].nxt){
        if(side_vis[i])continue;
        side_vis[i]=side_vis[i^1]=1;
        int v=kano[i].v;
        if(!dfn[v]){
            Tarjan(v);
            low[u]=Min(low[u],low[v]);
        }
        else if(Instack[v]){
            low[u]=Min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        int v;
        ++scc_cnt;
        do{
            v=St[top--];
            Instack[v]=0;
            scc_belong[v]=scc_cnt;
        }while(v!=u);
    }
}
// LCA相关
void dfs(int u,int fa){
    f[u][0]=fa;
    dep[u]=dep[fa]+1;
    for(int i(head[u]);i;i=kano[i].nxt){
        int v=kano[i].v;
        if(v==fa)continue;
        dfs(v,u);
    }
}
void Pre(){
    for(int i(1);i<=LogN;++i){
        for(int j(1);j<=n;++j){
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
}
inline int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i(LogN);i>=0;--i){
        if(dep[f[x][i]]>=dep[y]){
            x=f[x][i];
        }
    }
    if(x==y)return x;
    for(int i(LogN);i>=0;--i){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
inline int Dist(int x,int y){
    return dep[x]+dep[y]-(dep[lca(x,y)]<<1);
}
```
#### 作者：LuomuQDM (4星)
- **关键亮点**：对题意转化清晰，针对其他题解提出优化点，如$\text{instack}$数组无意义及无需特判缩点后重边，代码简洁且有注释说明个人代码习惯。
- **个人心得**：无

```cpp
// Tarjan求边双连通分量
void tj(int x){
    dfn[x]=low[x]=++ct;
    s[++h]=x;
    int y;
    for(int i=head[x];i;i=nxt[i]){
        if(v[i])continue;
        v[i]=v[i^1]=1;
        y=to[i];
        if(!dfn[y]){
            tj(y);
            low[x]=min(low[x],low[y]);
        }else low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]){
        sum++;
        do{
            y=s[h--];
            c[y]=sum;
        }while(y!=x);
    }
}
// 初始化LCA相关数组
void dfs(int x){
    vis[x]=1,d[x]=d[f[x][0]]+1;
    int y;
    for(int i=0;i<p[x].size();i++){
        y=p[x][i];
        if(vis[y])continue;
        f[y][0]=x;
        for(int j=1;f[f[y][j-1]][j-1];j++){
            f[y][j]=f[f[y][j-1]][j-1];
        }
        dfs(y);
    }
}
inline int lca(int x,int y){
    if(d[x]<d[y])swap(x,y);
    for(int i=19;~i;i--){
        if(d[f[x][i]]>=d[y])x=f[x][i];
    }
    if(x==y)return x;
    for(int i=19;~i;i--){
        if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
    }
    return f[x][0];
}
```
#### 作者：lzyqwq (4星)
- **关键亮点**：思路表述简洁清晰，代码逻辑紧凑，在构建缩点后的图时通过判断`ebc[i] < ebc[j]`来避免重边，代码整体可读性较好。
- **个人心得**：无

```cpp
// Tarjan求边双连通分量
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++cnt;
    s.push(x);
    is[x] = 1;
    for (int i : g[x]) {
        if (i!= fa) {
            if (!dfn[i]) {
                tarjan(i, x);
                low[x] = min(low[x], low[i]);
            } else if (is[i]) {
                low[x] = min(low[x], dfn[i]);
            }
        }
    }
    if (dfn[x] == low[x]) {
        ++sum;
        while (1) {
            int p = s.top();
            s.pop();
            is[p] = 0;
            ebc[p] = sum;
            if (x == p) {
                break;
            }
        }
    }
}
// 初始化LCA相关数组
void dfs(int x, int fa) {
    if (fa) {
        d[x] = d[fa] + 1;
        f[0][x] = fa;
        for (int i = 1; i <= lg[d[x]]; i++) {
            f[i][x] = f[i - 1][f[i - 1][x]];
        }
    }
    for (int i : e[x]) {
        if (i!= fa) {
            dfs(i, x);
        }
    }
}
inline int lca(int x, int y) {
    if (d[x] < d[y]) {
        swap(x, y);
    }
    while (d[x] > d[y]) {
        x = f[lg[d[x] - d[y]]][x];
    }
    if (x == y) {
        return x;
    }
    for (int i = lg[d[x]]; i >= 0; i--) {
        if (f[i][x]!= f[i][y]) {
            x = f[i][x];
            y = f[i][y];
        }
    }
    return f[0][x];
}
```

### 最优关键思路或技巧
利用边双连通分量缩点将无向连通图转化为树结构，把求两点间关键边数量问题转化为求树上两点间距离问题，通过Tarjan算法求边双连通分量，用LCA算法高效计算树上距离。在实现过程中，部分题解在处理无向图边的存储和缩点后图的构建上有优化技巧，如使用`i^1`处理无向图边的成对存储，通过判断条件避免缩点后图的重边。

### 可拓展思路
此类题目属于图论中结合边双连通分量和LCA的经典题型。相似套路还可用于解决一些涉及连通性、关键边（点）判断以及路径相关的图论问题。例如在一些网络拓扑结构分析题目中，判断某些连接的重要性等。

### 洛谷相似题目推荐
- [P2860 运输计划](https://www.luogu.com.cn/problem/P2860)：结合树上路径与二分查找，涉及边双连通分量相关概念。
- [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)：LCA模板题，可巩固LCA算法理解。
- [P1600 天天爱跑步](https://www.luogu.com.cn/problem/P1600)：树上路径与统计问题，需要运用LCA及一些树上差分技巧。 

---
处理用时：120.59秒