# 题目信息

# GCD Counting

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Let's denote the function $ g(x, y) $ as the greatest common divisor of the numbers written on the vertices belonging to the simple path from vertex $ x $ to vertex $ y $ (including these two vertices). Also let's denote $ dist(x, y) $ as the number of vertices on the simple path between vertices $ x $ and $ y $ , including the endpoints. $ dist(x, x) = 1 $ for every vertex $ x $ .

Your task is calculate the maximum value of $ dist(x, y) $ among such pairs of vertices that $ g(x, y) > 1 $ .

## 样例 #1

### 输入

```
3
2 3 4
1 2
2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 3 4
1 3
2 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 1 1
1 2
2 3
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
## GCD计数

### 题目描述
给定一棵由 $n$ 个顶点组成的树。每个顶点上都写有一个数字；顶点 $i$ 上的数字等于 $a_i$。

我们将函数 $g(x, y)$ 定义为从顶点 $x$ 到顶点 $y$ 的简单路径（包括这两个顶点）上所有顶点所写数字的最大公约数。同时，将 $dist(x, y)$ 定义为顶点 $x$ 和顶点 $y$ 之间简单路径上的顶点数，包括端点。对于每个顶点 $x$，$dist(x, x) = 1$。

你的任务是计算满足 $g(x, y) > 1$ 的顶点对 $(x, y)$ 中 $dist(x, y)$ 的最大值。

### 样例 #1
#### 输入
```
3
2 3 4
1 2
2 3
```
#### 输出
```
1
```

### 样例 #2
#### 输入
```
3
2 3 4
1 3
2 3
```
#### 输出
```
2
```

### 样例 #3
#### 输入
```
3
1 1 1
1 2
2 3
```
#### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕树形动态规划和点分治两种思路展开。树形动态规划的核心在于利用质因数分解，以相同质因数为条件进行状态转移，更新最长链长度；点分治则是通过不断寻找树的重心，以重心的质因子为 $gcd$ 进行深度搜索，合并最长链。

各题解的共性在于都利用了质因数分解，因为点权的最大公约数只与质因子有关，且点权范围决定了质因子数量较少，可作为状态转移的依据。不同点在于实现方式，树形动态规划直接在树上进行状态转移，而点分治则是通过不断分割树来求解。

### 所选题解
- **作者：Realityang (赞：17)，4星**
    - **关键亮点**：思路清晰，详细解释了利用质因数进行动态规划的过程，代码注释丰富，易于理解。
    - **个人心得**：无

- **作者：Strelitzia (赞：4)，4星**
    - **关键亮点**：直接点明树形DP的思路，代码结构简洁，通过定义 $dp_{u,x}$ 表示以 $u$ 为断点最长的一条链，质因数是 $x$，清晰地实现了状态转移。
    - **个人心得**：无

- **作者：lxzy_ (赞：3)，4星**
    - **关键亮点**：详细推导了动态规划的方程，将处理链的问题拆分成子问题，通过 $f_{u,i}$ 和 $g_{u,i}$ 分别表示以 $u$ 为起点的链和以 $u$ 为顶点的最长链，逻辑严谨。
    - **个人心得**：无

### 重点代码
#### Realityang的核心代码
```cpp
void dfs(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(fa==v)continue;
        dfs(v,u);
        for(int j=1;j<=y[u][0];j++){
            for(int k=1;k<=y[v][0];k++){
                if(y[u][j]==y[v][k]){
                    ans=max(ans,f[u][j]+f[v][k]+1);
                    f[u][j]=max(f[u][j],f[v][k]+1);
                }
            }
        }
    }
}
```
**核心实现思想**：通过深度优先搜索遍历树，对于每个节点的子节点，找到它们相同的质因子，更新以当前节点为端点的最长链长度和全局最长链长度。

#### Strelitzia的核心代码
```cpp
void dfs(int u,int fa) {
    for (int e = head[u] ; e ; e = nxt[e]) {
        int v = ver[e];
        if (v == fa) continue;
        dfs(v,u);
        for (int i = 0 ; i < prime[u].size() ; ++ i) {
            for (int j = 0 ; j < prime[v].size() ; ++ j) {
                if (prime[u][i] == prime[v][j]) {
                    ans = max(ans,dp[v][j] + dp[u][i]);
                    dp[u][i] = max(dp[u][i],dp[v][j] + 1);
                }
            }
        }
    }
}
```
**核心实现思想**：同样是深度优先搜索，在搜索过程中，对于当前节点和子节点的质因子进行比较，若相同则更新答案和状态数组。

#### lxzy_的核心代码
```cpp
void DFS(int u,int fa)
{
    for(int k=head[u];k;k=a[k].nxt){
        int v=a[k].to;
        if(v!=fa){
            DFS(v,u);
            for(int i=1;i<=Cnt[u];i++){
                for(int j=1;j<=Cnt[v];j++){
                    if(Fac[u][i]==Fac[v][j]){
                        g[u][i]=Max(g[u][i],f[u][i]+f[v][j]);
                        f[u][i]=Max(f[u][i],f[v][j]+1);
                    }
                }
            }
        }
    }
}
```
**核心实现思想**：深度优先搜索，利用 $f_{u,i}$ 和 $g_{u,i}$ 进行状态转移，$f_{u,i}$ 表示以 $u$ 为起点的链的最大长度，$g_{u,i}$ 表示以 $u$ 为顶点的最长链。

### 关键思路或技巧
- **质因数分解**：由于点权范围较小，一个数的质因子数量有限，可将质因子作为状态转移的依据，降低复杂度。
- **树形动态规划**：将处理链的问题拆分成子问题，通过状态转移方程更新最长链长度。
- **点分治**：不断寻找树的重心，以重心的质因子为 $gcd$ 进行深度搜索，合并最长链。

### 拓展思路
同类型题或类似算法套路包括：
- 树上的其他动态规划问题，如树上背包问题、树上最长路径问题等。
- 点分治在其他树上问题中的应用，如树上距离问题、树上路径计数问题等。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树形动态规划经典题目，与本题的树形动态规划思路类似。
- [P2634 [国家集训队]聪聪可可](https://www.luogu.com.cn/problem/P2634)：点分治的经典题目，可加深对点分治算法的理解。
- [P4178 Tree](https://www.luogu.com.cn/problem/P4178)：同样是点分治的题目，涉及树上路径的统计问题。

---
处理用时：49.19秒