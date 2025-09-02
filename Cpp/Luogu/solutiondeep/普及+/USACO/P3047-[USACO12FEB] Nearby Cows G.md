# 题目信息

# [USACO12FEB] Nearby Cows G

## 题目描述

Farmer John has noticed that his cows often move between nearby fields. Taking this into account, he wants to plant enough grass in each of his fields not only for the cows situated initially in that field, but also for cows visiting from nearby fields.

Specifically, FJ's farm consists of N fields (1 <= N <= 100,000), where some pairs of fields are connected with bi-directional trails (N-1 of them in total).  FJ has designed the farm so that between any two fields i and j, there is a unique path made up of trails connecting between i and j. Field i is home to C(i) cows, although cows sometimes move to a different field by crossing up to K trails (1 <= K <= 20).

FJ wants to plant enough grass in each field i to feed the maximum number of cows, M(i), that could possibly end up in that field -- that is, the number of cows that can potentially reach field i by following at most K trails.  Given the structure of FJ's farm and the value of C(i) for each field i, please help FJ compute M(i) for every field i.

给你一棵 $n$ 个点的树，点带权，对于每个节点求出距离它不超过 $k$ 的所有节点权值和 $m_i$。

## 说明/提示

There are 6 fields, with trails connecting (5,1), (3,6), (2,4), (2,1), and (3,2).  Field i has C(i) = i cows.


Field 1 has M(1) = 15 cows within a distance of 2 trails, etc.

【数据范围】  
对于 $100\%$ 的数据：$1 \le n \le 10^5$，$1 \le k \le 20$，$0 \le c_i \le 1000$

## 样例 #1

### 输入

```
6 2 
5 1 
3 6 
2 4 
2 1 
3 2 
1 
2 
3 
4 
5 
6 
```

### 输出

```
15 
21 
16 
10 
8 
11 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕树形 DP 展开，多数采用两次 DFS 解决问题，也有部分使用换根法、容斥原理等。思路上，先计算子树内的信息，再处理非子树部分的信息，处理非子树信息时需用容斥原理去重。算法要点在于状态定义和状态转移方程的推导，难点在于理解和处理重复计算的部分。

### 所选题解
- **作者：asuldb（5 星）**
  - **关键亮点**：思路清晰，对两次 DFS 的过程和状态转移方程解释详细，代码简洁，可读性高。
  - **个人心得**：作者提到在调这道题时中耳炎、发烧，在学长的指导下过了题，说明即使在身体不适的情况下，借助他人帮助也能解决难题。
- **作者：Yuyuanqi（4 星）**
  - **关键亮点**：思路阐述详细，将点能到达的点分为子树中和经过父亲两种情况，便于理解。代码结构清晰，注释详细。
- **作者：whyl（4 星）**
  - **关键亮点**：采用换根法解题，思路新颖，对换根的过程和操作解释清楚，代码实现简洁。

### 重点代码及核心实现思想
#### asuldb 的题解
```cpp
// 第一遍 DFS，计算子树内的信息
inline void build(int r)
{
    for(re int i=head[r];i;i=e[i].nxt)
    if(!deep[e[i].v])
    {
        deep[e[i].v]=deep[r]+1;
        build(e[i].v);
        for(re int j=1;j<=k;j++)
        f[r][j]+=f[e[i].v][j-1];
    }
}
// 第二遍 DFS，利用父亲更新儿子，处理非子树信息
inline void dfs(int r)
{
    for(re int i=head[r];i;i=e[i].nxt)
    if(deep[e[i].v]>deep[r])
    {
        for(re int j=k;j>=2;j--)
            f[e[i].v][j]-=f[e[i].v][j-2];// 简单的容斥原理
        for(re int j=1;j<=k;j++)
            f[e[i].v][j]+=f[r][j-1];
        dfs(e[i].v);
    }
}
```
核心思想：第一遍 DFS 计算以每个节点为根的子树中距离为 `j` 的节点权值和，第二遍 DFS 利用父亲节点的信息更新儿子节点，通过容斥原理去除重复计算的部分。

#### Yuyuanqi 的题解
```cpp
// 第一次 DFS，求出所有的 f[n][k]
void dfs(int x, int fa)
{
    for (int i = 0; i <= k; i++) f[x][i] = val[x];
    for (int i = head[x]; i; i = a[i].next)
    {
        int u = a[i].to;
        if (u != fa)
        {
            dfs(u, x);
            for (int i = 1; i <= k; i++)
                f[x][i] += f[u][i - 1];
        }
    }
}
// 第二次 DFS，通过已经求出的 f 数组推 d 数组
void dfs2(int x, int fa)
{
    for (int i = head[x]; i; i = a[i].next)
    {
        int u = a[i].to;
        if (u != fa)
        {
            d[u][1] += f[x][0];
            for (int i = 2; i <= k; i++)
                d[u][i] += d[x][i - 1] - f[u][i - 2];
            dfs2(u, x);
        }
    }
}
```
核心思想：第一次 DFS 计算子树内的信息，第二次 DFS 利用父亲节点的信息更新儿子节点，通过容斥原理去除重复计算的部分。

#### whyl 的题解
```cpp
// 预处理，计算子树内的信息
inline void dfs_pre(int x,int fa){
    for(int i=head[x];i;i=nxt[i]){
        int y=ver[i];
        if(y==fa) continue;
        dfs_pre(y,x);
        for(int j=1;j<=k;j++) dp[x][j]+=dp[y][j-1];
    }
}
// 去除原来的贡献
inline void cut(int root1,int root2){
    for(int i=1;i<=k;i++) dp[root1][i]-=dp[root2][i-1];
} 
// 加上贡献
inline void link(int root1,int root2){
    for(int i=1;i<=k;i++) dp[root1][i]+=dp[root2][i-1];
}
// 换根操作
inline void change_root(int x,int y){
    cut(x,y);
    link(y,x);
}
// 进行换根和答案统计
inline void dfs(int x,int fa){
    for(int i=0;i<=k;i++) ans[x]+=dp[x][i];
    for(int i=head[x];i;i=nxt[i]){
        int y=ver[i];
        if(y==fa) continue;
        change_root(x,y);
        dfs(y,x);
        change_root(y,x);
    }
}
```
核心思想：先进行预处理，计算子树内的信息，然后通过换根操作，利用 `cut` 和 `link` 函数更新节点的信息，最后统计答案。

### 最优关键思路或技巧
- **两次 DFS**：先计算子树内的信息，再利用父亲节点的信息更新儿子节点，处理非子树部分的信息。
- **容斥原理**：在更新儿子节点的信息时，去除重复计算的部分。
- **换根法**：通过换根操作，利用已知节点的信息快速计算其他节点的信息。

### 可拓展之处
同类型题或类似算法套路：
- 树上路径问题：如求树上两点间的距离、路径上的最大值等。
- 树上动态规划：如树上的最大独立集、最小支配集等。
- 换根 DP：适用于需要计算以每个节点为根的树的相关信息的问题。

### 推荐题目
- P2986 [USACO10MAR] Great Cow Gathering G
- P3174 [HAOI2009] 毛毛虫
- P4299 首都

### 个人心得摘录与总结
- **asuldb**：在身体不适的情况下，借助学长的指导也能解决难题，说明团队合作和交流的重要性。
- **Forever_Lin**：在做题时遇到困难，尝试在错误的状态转移上稍加修改，通过画图理解重复计算的部分，最终解决问题，说明遇到问题时要积极思考，尝试不同的方法。

---
处理用时：53.49秒