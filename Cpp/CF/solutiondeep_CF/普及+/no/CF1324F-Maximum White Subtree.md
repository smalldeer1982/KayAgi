# 题目信息

# Maximum White Subtree

## 题目描述

You are given a tree consisting of $ n $ vertices. A tree is a connected undirected graph with $ n-1 $ edges. Each vertex $ v $ of this tree has a color assigned to it ( $ a_v = 1 $ if the vertex $ v $ is white and $ 0 $ if the vertex $ v $ is black).

You have to solve the following problem for each vertex $ v $ : what is the maximum difference between the number of white and the number of black vertices you can obtain if you choose some subtree of the given tree that contains the vertex $ v $ ? The subtree of the tree is the connected subgraph of the given tree. More formally, if you choose the subtree that contains $ cnt_w $ white vertices and $ cnt_b $ black vertices, you have to maximize $ cnt_w - cnt_b $ .

## 说明/提示

The first example is shown below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1324F/e1f60f9681db9f4f9199c7a23c4eb447ad36532b.png)

The black vertices have bold borders.

In the second example, the best subtree for vertices $ 2, 3 $ and $ 4 $ are vertices $ 2, 3 $ and $ 4 $ correspondingly. And the best subtree for the vertex $ 1 $ is the subtree consisting of vertices $ 1 $ and $ 3 $ .

## 样例 #1

### 输入

```
9
0 1 1 1 0 0 0 0 1
1 2
1 3
3 4
3 5
2 6
4 7
6 8
5 9```

### 输出

```
2 2 2 2 2 1 1 0 2```

## 样例 #2

### 输入

```
4
0 0 1 0
1 2
1 3
1 4```

### 输出

```
0 -1 1 -1```

# AI分析结果

### 题目翻译
#### 最大白色子树

#### 题目描述
给定一棵由 $n$ 个顶点组成的树。树是一个有 $n - 1$ 条边的连通无向图。这棵树的每个顶点 $v$ 都被赋予了一种颜色（如果顶点 $v$ 是白色，则 $a_v = 1$；如果顶点 $v$ 是黑色，则 $a_v = 0$）。

你必须为每个顶点 $v$ 解决以下问题：如果你选择给定树的某个包含顶点 $v$ 的子树，你能得到的白色顶点数和黑色顶点数的最大差值是多少？树的子树是给定树的连通子图。更正式地说，如果你选择的子树包含 $cnt_w$ 个白色顶点和 $cnt_b$ 个黑色顶点，你必须最大化 $cnt_w - cnt_b$。

#### 说明/提示
第一个样例如下所示：
（此处有图，描述为黑色顶点有粗边框）

在第二个样例中，顶点 $2$、$3$ 和 $4$ 的最佳子树分别就是顶点 $2$、$3$ 和 $4$ 本身。而顶点 $1$ 的最佳子树是由顶点 $1$ 和 $3$ 组成的子树。

#### 样例 #1
##### 输入
```
9
0 1 1 1 0 0 0 0 1
1 2
1 3
3 4
3 5
2 6
4 7
6 8
5 9
```
##### 输出
```
2 2 2 2 2 1 1 0 2
```

#### 样例 #2
##### 输入
```
4
0 0 1 0
1 2
1 3
1 4
```
##### 输出
```
0 -1 1 -1
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕树形动态规划（Tree DP）和换根动态规划（Rerooting DP）展开。思路核心是先将无根树转化为有根树，通过第一次 DFS 计算以每个节点为根的子树的贡献，再通过第二次 DFS 换根计算包含该节点的所有子树的最大贡献。
- **思路对比**：多数题解思路一致，先树形 DP 计算子树贡献，再换根 DP 计算全局贡献；部分题解如夏子汐的不用换根，用 map 记录贡献避免重复计算。
- **算法要点**：给黑点赋值 -1，白点赋值 1，将 $cnt_w - cnt_b$ 转化为权值和；树形 DP 状态转移方程 $dp_i = col_i + \sum_{v \in son_i} \max(0, dp_v)$；换根 DP 根据父子节点关系更新答案。
- **解决难点**：避免重复计算子树贡献，换根时正确处理父子节点关系。

### 所选题解
- **作者：WYXkk (赞：19)，4星**
    - **关键亮点**：思路清晰，详细给出状态转移方程，代码规范，注释较全。
- **作者：F_Mu (赞：16)，4星**
    - **关键亮点**：分析过程详细，通过分类讨论父子节点关系更新答案，代码简洁。
- **作者：一扶苏一 (赞：14)，4星**
    - **关键亮点**：对树形 DP 和换根 DP 的原理分析透彻，给出详细的状态转移方程推导。

### 重点代码
#### WYXkk 的代码
```cpp
void dfs1(int u,int f)
{
    dp[u]=col[u];
    for(ri i=head[u];i;i=nxt[i]) if(to[i]!=f) {dfs1(to[i],u);dp[u]+=max(0,dp[to[i]]);}
}
void dfs2(int u,int f)
{
    if(u!=1) dp2[u]=max(dp2[f]-max(0,dp[u]),0)+dp[u];
    for(ri i=head[u];i;i=nxt[i]) if(to[i]!=f) dfs2(to[i],u);
}
```
**核心实现思想**：`dfs1` 计算以每个节点为根的子树的贡献，`dfs2` 换根计算包含该节点的所有子树的最大贡献。

#### F_Mu 的代码
```cpp
void dfs(int now, int pre) {
    for (auto &to:v[now]) {
        if (to == pre)
            continue;
        dfs(to, now);
        if (a[to] > 0)
            a[now] += a[to];
    }
}
void dfs2(int now, int pre) {
    for (auto &to:v[now]) {
        if (to == pre)
            continue;
        if (a[to] > 0)
            a[to] = max(a[to], a[now]);
        else
            a[to] = max(a[to], a[now] + a[to]);
        dfs2(to, now);
    }
}
```
**核心实现思想**：`dfs` 计算子树贡献，`dfs2` 根据子树贡献是否大于 0 分类讨论更新答案。

#### 一扶苏一的代码
```cpp
void dfs(const int u, const int p) {
    fa[u] = p;
    f[u] = a[u] ? 1 : -1;
    for (auto v : e[u]) if (v != p) {
        dfs(v, u);
        if (f[v] > 0) f[u] += f[v];
    }
}
void dfs(const int u) {
    int p = fa[u], tt = g[p] + f[p] - (a[p] ? 1 : -1);
    if (f[u] > 0) tt -= f[u];
    if (tt < 0) tt = 0;
    ans[u] = f[u] + tt;
    g[u] = tt + (a[u] ? 1 : -1);
    for (auto v : e[u]) if (v != fa[u]) {
        dfs(v);
    }
}
```
**核心实现思想**：第一个 `dfs` 计算以每个节点为根的子树的贡献，第二个 `dfs` 换根计算全局贡献。

### 关键思路或技巧
- 给黑点赋值 -1，白点赋值 1，将 $cnt_w - cnt_b$ 转化为权值和，简化计算。
- 利用树形 DP 和换根 DP 两次 DFS 计算答案，时间复杂度 $O(n)$。
- 换根时注意避免重复计算子树贡献，正确处理父子节点关系。

### 拓展思路
同类型题或类似算法套路：
- 其他树形 DP 问题，如树的重心、树的直径等。
- 换根 DP 可用于解决一些需要计算每个节点为根的相关问题。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
- [P2014 选课](https://www.luogu.com.cn/problem/P2014)
- [P2986 [USACO10MAR]Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)

### 个人心得摘录与总结
- **devout**：开始想复杂往树剖方向思考，后发现是 div3 比赛不太可能考树剖，转向树形 DP 并解决问题。总结是要根据比赛难度和数据范围合理选择算法，避免过度复杂化。
- **夏子汐**：在解决求节点除自己和儿子外的树的最大值时，发现父亲答案可能包含该节点及其子树导致答案重复计算，用 map 存储贡献解决问题。提示在动态规划中要注意状态转移的正确性，避免重复计算。 

---
处理用时：50.90秒