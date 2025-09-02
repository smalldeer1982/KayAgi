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
这些题解核心思路都是利用按位与性质和并查集解决问题。按位与运算结果不增，路径边权按位与不小于 $V$ 需满足一定二进制前缀条件。各题解通过枚举二进制前缀，将满足条件的边分类，用多个并查集维护边的连通性，查询时判断两点在某个并查集中是否连通。

### 所选题解
- **作者：FFFFFAN（5星）**
    - **关键亮点**：思路清晰，详细阐述按位与性质及前缀分析过程，代码简洁易懂。
    - **核心代码**：
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
    - **核心思想**：先初始化并查集，根据 $V$ 标记二进制位。遍历边，根据边权和 $V$ 的二进制位关系将边加入不同并查集。查询时，遍历并查集判断两点是否连通。

- **作者：OldDriverTree（4星）**
    - **关键亮点**：思路简洁明了，准确指出路径按位与结果 $\ge V$ 的条件，代码结构清晰。
    - **核心代码**：
```c++
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
int main()
{
    read(n),read(m),read(q),read(V);
    for (int i=0;i<=60;i++) T[i].init();
    while (m--) {
        int x,y; ll z=0;
        read(x),read(y),read(z);
        for (int i=59;~i;i--) {
            if (!(V>>i&1)&&(z>>i&1) ) T[i].merge(x,y);
            else if ( (V>>i&1)&&!(z>>i&1) ) break;
        }
        if ( (z&V)==V) T[60].merge(x,y);
    }
    while (q--) {
        int x,y; read(x),read(y);
        puts(judge(x,y)?"Yes":"No");
    }
    return 0;
}
```
    - **核心思想**：定义并查集结构体，初始化 61 个并查集。遍历边，根据边权和 $V$ 的二进制位关系合并并查集。查询时，遍历并查集判断两点是否连通。

### 最优关键思路或技巧
- **二进制前缀分析**：利用按位与性质，从二进制高位到低位分析，将边按满足的二进制前缀分类，用并查集维护连通性。
- **多并查集维护**：开多个并查集分别处理不同前缀条件下的边的连通性，查询时遍历并查集判断两点是否连通。

### 可拓展之处
同类型题可拓展到有向图、带负权边图，或改变路径价值计算方式，如按位或、按位异或等。类似算法套路可用于解决其他涉及位运算和连通性判断的问题。

### 推荐题目
- [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)：并查集应用，涉及动态图连通性问题。
- [P1525 [NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)：并查集维护对立关系，解决二分图问题。
- [P3367 [模板] 并查集](https://www.luogu.com.cn/problem/P3367)：并查集基础模板题，可巩固并查集操作。

### 个人心得摘录与总结
- **作者：SDLTF_凌亭风**：SDCPC2023 比赛时该题未做出来，现在尝试解决。总结出要研究与操作性质，枚举最长公共前缀长度解题，同时提醒注意变量类型。
- **作者：Hadtsti**：该题在 SDCPC2024 热身赛试机时一直 TLE，后来发现是评测机慢，不加按秩合并过不了，但洛谷不加也能过。提醒做题时要考虑评测机性能对代码的影响。 

---
处理用时：37.58秒