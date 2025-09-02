# 题目信息

# [SDCPC 2023] Not Another Path Query Problem

## 题目描述

**【题目背景】**

> 都什么年代了还在做传统路径查询问题？


在阅读《Distributed Exact Shortest Paths in Sublinear Time》这篇论文后，您学会了如何在 $\mathcal{O}(D^{1/3} \cdot (n \log n)^{2/3})$ 的复杂度内解决分布式单源最短路问题。为了测试您是否真的学有所成，小青鱼为您准备了如下问题。

小青鱼有一张包含 $n$ 个节点与 $m$ 条无向边的图，节点编号从 $1$ 到 $n$。第 $i$ 条边连接节点 $u_i$ 和 $v_i$，边权为 $w_i$。

对于任意一条连接节点 $u$ 和 $v$ 的路径，定义路径的价值为路径上所有边的边权进行按位与（bitwise AND）计算的结果。

小青鱼很喜欢高价值的路径，因此他设定了一个固定的阈值 $V$。称小青鱼喜爱一条路径，当且仅当这条路径的价值至少为 $V$。

接下来，小青鱼将会提出 $q$ 次询问，第 $i$ 次询问可以用一对整数 $(u_i, v_i)$ 表示。对于每次询问，您需要判断节点 $u_i$ 到 $v_i$ 是否存在一条小青鱼喜爱的路径。

## 样例 #1

### 输入

```
9 8 4 5
1 2 8
1 3 7
2 4 1
3 4 14
2 5 9
4 5 7
5 6 6
3 7 15
1 6
2 7
7 6
1 8
```

### 输出

```
Yes
No
Yes
No
```

## 样例 #2

### 输入

```
3 4 1 4
1 2 3
1 2 5
2 3 2
2 3 6
1 3
```

### 输出

```
Yes
```

# AI分析结果

### 综合分析与结论
这些题解均利用按位与运算性质，将边按二进制前缀分类，用并查集维护连通性来解决问题。主要思路是基于按位与运算会使结果不大于参与运算的数这一特性，通过分析二进制前缀，找到满足路径价值至少为V的边集，进而判断两点是否连通。

### 所选的题解
- **FFFFFAN（5星）**
    - **关键亮点**：思路阐述清晰，从按位与运算性质出发，详细分析二进制前缀情况，对边集分类及并查集维护讲解透彻，代码简洁明了，可读性高。
    - **核心代码片段**：
```cpp
int find(int x, int i) {
    return x==fa[x][i]? x : fa[x][i]=find(fa[x][i], i);
}

int main() {
    scanf("%d%d%d%lld", &n, &m, &q, &V);
    for(int i=1; i<=n; ++i)
        for(int j=0; j<=61; ++j) fa[i][j] = i;
    for(int j=60; ~j; --j)
        if(V&(1ll<<j)) b[j] = 1;
    for(int i=1; i<=m; ++i) {
        int u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        for(int j=60; ~j; --j) {
            bool f = (w&(1ll<<j));
            if((!b[j]) && f) fa[find(u, j)][j] = find(v, j);
            else if(b[j] && (!f)) break;
        }
        if((w&V) >= V) fa[find(u, 61)][61]=find(v, 61);
    }
    for(int i=1; i<=q; ++i) {
        int u, v, flag=0;
        scanf("%d%d", &u, &v);
        for(int j=61; ~j; --j)
            if(find(u, j) == find(v, j)) {
                flag = 1;
                break;
            }
        puts(flag? "Yes" : "No");
    }
    return 0;
}
```
    - **核心实现思想**：`find`函数用于查找并查集代表元素。主函数中，初始化并查集，根据V的二进制位标记数组b。遍历每条边，根据边权与b数组判断是否合并并查集。特殊处理边权等于V的边。查询时，枚举并查集判断两点是否连通。
- **OldDriverTree（4星）**
    - **关键亮点**：简洁地概括出路径按位与结果≥V的条件，代码结构清晰，利用模板封装并查集操作，增强了代码的复用性。
    - **核心代码片段**：
```cpp
struct DSU {
    int fa[N];
    void init() { for (int i=1;i<=n;i++) fa[i]=i; }
    int find(int x) { return fa[x]^x?fa[x]=find(fa[x]):x; }
    void merge(int x,int y) { fa[find(x)]=find(y); }
    bool query(int x,int y) { return find(x)==find(y); }
}T[61];

bool judge(int x,int y)
{
    for (int i=60;~i;i--)
        if (T[i].query(x,y) )
            return true;
    return false;
}
```
    - **核心实现思想**：`DSU`结构体封装并查集操作，`init`初始化，`find`查找代表元素，`merge`合并集合，`query`判断两点是否连通。`judge`函数枚举61个并查集判断两点是否在某一满足条件的并查集中连通。
- **_liuyi_（4星）**
    - **关键亮点**：思路清晰，对v进行二进制拆位分析，详细阐述了如何确定有用边并利用并查集维护连通性，代码注释详细，易于理解。
    - **核心代码片段**：
```cpp
inline int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
inline void mg(int x,int y){
    x=find(x);y=find(y);
    if(x!=y) fa[x]=y;
    return;
}

int main(){
    scanf("%d%d%d%lld",&n,&m,&q,&v);
    rep(i,1,n) fa[i]=i;
    rep(i,1,m) scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].w);
    rep(i,1,q) scanf("%d%d",&pos[i][0],&pos[i][1]);
    rep(i,0,59){
        if(!((1ll<<i)&v)){
            ll cnt=(((v>>i)+1)<<i);
            rep(i,1,n) fa[i]=i;
            rep(i,1,m) if((e[i].w&cnt)==cnt) mg(e[i].u,e[i].v);
            rep(i,1,q) if(find(pos[i][0])==find(pos[i][1])) can[i]=1;
        }
    }
    rep(i,1,n) fa[i]=i;
    rep(i,1,m) if((e[i].w&v)==v) mg(e[i].u,e[i].v);
    rep(i,1,q) if(find(pos[i][0])==find(pos[i][1])) can[i]=1;
    rep(i,1,q) YesNo(can[i]);
    return 0;
}
```
    - **核心实现思想**：`find`函数查找并查集代表元素，`mg`函数合并集合。主函数中，初始化并查集和读入数据。枚举v的二进制位，对于v当前位为0的情况，构造cnt并处理满足条件的边，查询两点连通性。最后特殊处理边权等于v的情况并查询。

### 最优关键思路或技巧
利用按位与运算在二进制下的特性，将边按与V相关的二进制前缀分类，通过并查集高效维护不同边集形成子图的连通性，快速判断两点间是否存在满足条件的路径。

### 可拓展思路
此类题目可拓展到更多基于位运算性质结合图论的问题，如按位或、异或等运算与路径问题结合。类似算法套路是分析位运算对数值在二进制下的影响，利用数据结构（如并查集、图的连通分量等）维护相关关系。

### 推荐题目
- [P1879 [USACO06NOV]玉米田Corn Fields](https://www.luogu.com.cn/problem/P1879)：状态压缩DP结合位运算，判断合法状态。
- [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)：同样是状态压缩DP，利用位运算处理状态转移。
- [P1171 售货员的难题](https://www.luogu.com.cn/problem/P1171)：涉及图论与状态压缩，通过位运算优化路径搜索。

### 个人心得摘录
无。 

---
处理用时：37.29秒