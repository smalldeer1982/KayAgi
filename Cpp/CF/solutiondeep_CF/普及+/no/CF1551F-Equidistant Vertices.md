# 题目信息

# Equidistant Vertices

## 题目描述

A tree is an undirected connected graph without cycles.

You are given a tree of $ n $ vertices. Find the number of ways to choose exactly $ k $ vertices in this tree (i. e. a $ k $ -element subset of vertices) so that all pairwise distances between the selected vertices are equal (in other words, there exists an integer $ c $ such that for all $ u, v $ ( $ u \ne v $ , $ u, v $ are in selected vertices) $ d_{u,v}=c $ , where $ d_{u,v} $ is the distance from $ u $ to $ v $ ).

Since the answer may be very large, you need to output it modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3

4 2
1 2
2 3
2 4

3 3
1 2
2 3

5 3
1 2
2 3
2 4
4 5```

### 输出

```
6
0
1```

# AI分析结果

### 题目内容（中文重写）
# 等距顶点

## 题目描述
树是一种无环的无向连通图。

给定一棵具有 $n$ 个顶点的树。求在这棵树中恰好选择 $k$ 个顶点（即顶点的一个 $k$ 元子集）的方法数，使得所选顶点之间的所有成对距离都相等（换句话说，存在一个整数 $c$，使得对于所有 $u, v$（$u \ne v$，$u, v$ 是所选顶点），$d_{u,v}=c$，其中 $d_{u,v}$ 是从 $u$ 到 $v$ 的距离）。

由于答案可能非常大，你需要将其对 $10^9 + 7$ 取模后输出。

## 样例 #1
### 输入
```
3

4 2
1 2
2 3
2 4

3 3
1 2
2 3

5 3
1 2
2 3
2 4
4 5
```

### 输出
```
6
0
1
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先特判 $k = 2$ 的情况，此时方案数为 $C_{n}^{2}$。对于 $k > 2$ 的情况，都发现满足条件的 $k$ 个点一定存在一个“中心点”，使得这些点到中心点的距离相等，且这些点分布在以中心点为根的不同子树中。

各题解的主要区别在于实现细节和状态定义：
- **Acfboy**：通过枚举根节点，dfs 记录每个子树不同深度的点数，再枚举深度进行 dp 计算方案数。
- **beauty_son_whm**：定义了 $down$ 和 $up$ 数组分别记录子树内和子树外的信息，进行树形 dp 计数。
- **ncwzdlsd**：让每个点成为根，计算其他点深度求方案数，同样使用 dp 统计。
- **little_sheep917**：枚举根节点和距离，dfs 求每个子树距离根为特定距离的节点个数，用背包计算方案数。
- **jun头吉吉**：通过枚举根节点和深度，利用多项式 $\prod_i 1+a_ix$ 计算方案数。
- **happybob**：枚举中心点，处理每个儿子子树中各深度的点数，再枚举深度进行 dp 计算。
- **TernaryTree**：枚举中心点和深度，预处理子树各深度节点数，然后 dp 计算，还对复杂度进行了优化分析。
- **FiraCode**：特判 $k \leq 2$ 的情况，对于 $k \geq 3$ 枚举分叉点，统计距离分叉点为 $d$ 的点个数，用 dp 计算，还提到可以用 floyd 求最短路。
- **peterwuyihong**：枚举关键点和深度，求 $[x^k]\prod1+a_ix$ 计算方案数。
- **Wf_yjqd**：枚举子图的根，树上 dp 求深度相同的点个数，用滚动数组优化 dp 计算方案数。

### 所选题解
- **Acfboy（4星）**
    - **关键亮点**：思路清晰，代码实现详细，对调试过程有分享，方便读者理解。
    - **个人心得**：因为清空数组时的错误代码 `for (int j = 1; j <= n; j++) for (int l = 0; l <= n; l++) num[i][j] = 0;` 调了一个小时，提醒读者要好好清空数组。
- **TernaryTree（4星）**
    - **关键亮点**：对复杂度进行了分析，通过度数判断减少不必要的枚举，优化了算法。
- **Wf_yjqd（4星）**
    - **关键亮点**：使用滚动数组优化 dp，减少了空间复杂度。

### 重点代码
#### Acfboy 的核心代码
```cpp
void dfs(int u, int fa) {
    num[u][0] = 1;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u);
        for (int j = 1; j <= n; j++)
            num[u][j] += num[v][j-1];
    }
}
// main 函数中关键部分
for (int i = 1; i <= n; i++) {
    dfs(i, 0);
    for (int j = 1; j <= n; j++) {
        for (int l = 0; l < (int)g[i].size(); l++) 
            a.push_back(num[g[i][l]][j-1]);
        f[0][0] = 1;
        for (int x = 1; x <= (int)a.size(); x++) {
            f[x][0] = 1;
            for (int y = 1; y <= x; y++)
                f[x][y] = (f[x-1][y] + f[x-1][y-1]*a[x-1]%P) % P;
        }
        ans = (ans + f[a.size()][k]) % P;
        a.clear();
    }
    for (int j = 1; j <= n; j++)
        for (int l = 0; l <= n; l++) num[j][l] = 0;
}
```
**核心实现思想**：dfs 函数用于记录以当前节点为根的子树中各深度的点数。在主函数中，枚举根节点和深度，将每个子树中该深度的点数存入数组 `a`，然后进行 dp 计算方案数。

#### TernaryTree 的核心代码
```cpp
void dfs(int u, int fa, int rt, int dep) {
    ++cnt[rt][dep];
    for (int v : g[u]) if (v != fa) dfs(v, u, rt, dep + 1);
}
// main 函数中关键部分
for (int u = 1; u <= n; u++) {
    if (deg[u] < k) continue;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cnt[i][j] = 0;
    for (int i = 0; i < g[u].size(); i++) dfs(g[u][i], u, i + 1, 1);
    for (int c = 1; c <= n; c++) {
        for (int i = 0; i <= g[u].size(); i++) for (int j = 0; j <= k; j++) f[i][j] = 0;
        f[0][0] = 1;
        for (int i = 1; i <= g[u].size(); i++) for (int j = 0; j <= k; j++) f[i][j] = (f[i - 1][j] + cnt[i][c] * f[i - 1][j - 1] % mod) % mod;
        (ans += f[g[u].size()][k]) %= mod;
    }
}
```
**核心实现思想**：dfs 函数用于统计以当前节点的儿子为根的子树中各深度的点数。在主函数中，先判断节点度数是否小于 $k$，若小于则跳过。然后枚举深度，进行 dp 计算方案数。

#### Wf_yjqd 的核心代码
```cpp
inline void dfs(ll x, ll fa) {
    dep[x]=dep[fa]+1;
    cnt[x][dep[x]]=1;
    for(ll i=head[x];i;i=e[i].ne)
        if(e[i].to!=fa){
            dfs(e[i].to,x);
            for(ll j=1;j<=n;j++)
                cnt[x][j]+=cnt[e[i].to][j];
        }
    return ;
}
// main 函数中关键部分
for(ll i=1;i<=n;i++){
    if(du[i]<k)
        continue;
    for(ll j=1;j<=n;j++)
        for(ll l=1;l<=n;l++)
            cnt[j][l]=0;
    dfs(i,0);
    for(ll j=1;j<=n;j++){
        if(cnt[i][j]<k)
            continue;
        for(ll l=1;l<=k;l++)
            f[l]=0;
        f[0]=1;
        for(ll l=head[i];l;l=e[l].ne)
            for(ll m=k;m>=1;m--)
                f[m]=(f[m]+f[m-1]*cnt[e[l].to][j]%mod)%mod;
        ans=(ans+f[k])%mod;
    }
}
```
**核心实现思想**：dfs 函数用于记录以当前节点为根的子树中各深度的点数。在主函数中，先判断节点度数是否小于 $k$，若小于则跳过。然后枚举深度，使用滚动数组进行 dp 计算方案数。

### 最优关键思路或技巧
- **枚举中心点**：通过枚举树中的每个点作为中心点，将问题转化为在以该中心点为根的不同子树中选择满足条件的点。
- **动态规划**：使用 dp 数组记录不同状态下的方案数，通过状态转移方程进行计算。
- **复杂度优化**：如 TernaryTree 题解中通过度数判断减少不必要的枚举，Wf_yjqd 题解中使用滚动数组减少空间复杂度。

### 拓展思路
同类型题或类似算法套路：
- 树的路径问题：如求树中满足特定条件的路径数量、路径长度等。
- 树形 dp 问题：在树结构上进行动态规划，解决与树的节点、边相关的计数或优化问题。

### 推荐洛谷题目
- P1352 没有上司的舞会（树形 dp 经典题）
- P2014 选课（树形 dp 应用）
- P2015 二叉苹果树（树形 dp 求子树的最优值）

---
处理用时：68.21秒