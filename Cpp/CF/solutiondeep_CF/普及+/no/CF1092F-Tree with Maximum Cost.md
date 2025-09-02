# 题目信息

# Tree with Maximum Cost

## 题目描述

You are given a tree consisting exactly of $ n $ vertices. Tree is a connected undirected graph with $ n-1 $ edges. Each vertex $ v $ of this tree has a value $ a_v $ assigned to it.

Let $ dist(x, y) $ be the distance between the vertices $ x $ and $ y $ . The distance between the vertices is the number of edges on the simple path between them.

Let's define the cost of the tree as the following value: firstly, let's fix some vertex of the tree. Let it be $ v $ . Then the cost of the tree is $ \sum\limits_{i = 1}^{n} dist(i, v) \cdot a_i $ .

Your task is to calculate the maximum possible cost of the tree if you can choose $ v $ arbitrarily.

## 说明/提示

Picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1092F/fdd33998ce4716fa490f243f16a780e7d58d0e7e.png)

You can choose the vertex $ 3 $ as a root, then the answer will be $ 2 \cdot 9 + 1 \cdot 4 + 0 \cdot 1 + 3 \cdot 7 + 3 \cdot 10 + 4 \cdot 1 + 4 \cdot 6 + 4 \cdot 5 = 18 + 4 + 0 + 21 + 30 + 4 + 24 + 20 = 121 $ .

In the second example tree consists only of one vertex so the answer is always $ 0 $ .

## 样例 #1

### 输入

```
8
9 4 1 7 10 1 6 5
1 2
2 3
1 4
1 5
5 6
5 7
5 8
```

### 输出

```
121
```

## 样例 #2

### 输入

```
1
1337
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 具有最大成本的树

## 题目描述
给定一棵恰好由 $n$ 个顶点组成的树。树是一个具有 $n - 1$ 条边的连通无向图。这棵树的每个顶点 $v$ 都有一个赋予它的值 $a_v$。

设 $dist(x, y)$ 为顶点 $x$ 和 $y$ 之间的距离。顶点之间的距离是它们之间简单路径上的边数。

我们将树的成本定义为以下值：首先，固定树的某个顶点。设它为 $v$。那么树的成本为 $\sum\limits_{i = 1}^{n} dist(i, v) \cdot a_i$。

你的任务是计算如果可以任意选择 $v$，树的最大可能成本。

## 说明/提示
与第一个示例对应的图：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1092F/fdd33998ce4716fa490f243f16a780e7d58d0e7e.png)

你可以选择顶点 $3$ 作为根，然后答案将是 $2 \cdot 9 + 1 \cdot 4 + 0 \cdot 1 + 3 \cdot 7 + 3 \cdot 10 + 4 \cdot 1 + 4 \cdot 6 + 4 \cdot 5 = 18 + 4 + 0 + 21 + 30 + 4 + 24 + 20 = 121$。

在第二个示例中，树仅由一个顶点组成，所以答案始终为 $0$。

## 样例 #1
### 输入
```
8
9 4 1 7 10 1 6 5
1 2
2 3
1 4
1 5
5 6
5 7
5 8
```
### 输出
```
121
```

## 样例 #2
### 输入
```
1
1337
```
### 输出
```
0
```

### 算法分类
动态规划（树形DP中的换根法）

### 综合分析与结论
这些题解主要思路均为通过换根DP解决问题。先任选一个节点作为根节点，通过第一次DFS计算出子树的相关信息，如子树权值和、子树费用等；再通过第二次DFS，利用父亲节点的费用推出儿子节点的费用，从而得到以所有节点为根时树的费用，最后取最大值。各题解在具体实现细节上略有不同，如记录的变量、递推公式的写法等。

### 所选的题解
- **作者：CreeperK (赞：10)  星级：5星**
    - **关键亮点**：思路清晰，详细阐述了两次DFS的具体过程及原理，与类似题目进行对比，帮助理解。代码简洁明了，注释详细。
    - **重点代码**：
```cpp
void dfs1(int u,int fa){
    s[u]=a[u]; s2[u]=0;
    for(int i=h[u],v;i;i=nex[i]){//链式前向星
        if((v=to[i])==fa)continue;
        dfs1(v,u);
        s[u]+=s[v];
        s2[u]+=s[v]+s2[v];
    }
}
void dfs2(int u,int fa,ll sum){
    for(int i=h[u],v;i;i=nex[i]){
        if((v=to[i])==fa)continue;
        dp[v]=(sum+s[u]-s[v])+dp[u]-s[v];
        dfs2(v,u,sum+s[u]-s[v]);
    }
}
```
    - **核心实现思想**：`dfs1`通过递归计算每个节点的子树权值和`s[u]`以及子树费用`s2[u]`。`dfs2`利用父亲节点的费用`dp[u]`和子树权值和等信息，递推计算儿子节点的费用`dp[v]`。
- **作者：_l_l_ (赞：5)  星级：4星**
    - **关键亮点**：表述简洁，通过清晰的图示说明换根过程中贡献值的变化，代码实现简洁高效。
    - **重点代码**：
```cpp
void dfs1(int x, int fa, int dep) {
    depth[x] = dep;
    size[x] = a[x];
    for (int i = head[x]; i; i = edges[i].nxt) {
        int v = edges[i].to;
        if (v == fa) continue;
        dfs1(v, x, dep + 1);
        size[x] += size[v];
    }
}
void dfs2(int x, int fa) {
    if (x!= 1) dp[x] = dp[fa] + QwQ - size[x] - size[x];
    for (int i = head[x]; i; i = edges[i].nxt) {
        int v = edges[i].to;
        if (v == fa) continue;
        dfs2(v, x);
    }
}
```
    - **核心实现思想**：`dfs1`计算每个节点深度`depth[x]`和子树权值和`size[x]`。`dfs2`根据父亲节点的答案`dp[fa]`，结合子树权值和`size[x]`以及所有节点权值和`QwQ`，递推计算儿子节点的答案`dp[x]`。
- **作者：lgswdn_SA (赞：0)  星级：4星**
    - **关键亮点**：对两次DFS维护的变量解释清晰，明确指出换根时答案的变化规律，代码逻辑清晰。
    - **重点代码**：
```cpp
void dfs1(int u,int fa){
    s[u]=a[u];
    for(int i=hd[u],v;i;i=e[i].nxt) {
        if((v=e[i].to)==fa) continue;
        d[v]=d[u]+1;
        dfs1(v,u);
        s[u]+=s[v], f[u]+=(f[v]+s[v]);
    }
} 
void dfs2(int u,int fa){
    if(u==1) ans[u]=f[u];
    for(int i=hd[u],v;i;i=e[i].nxt){
        if((v=e[i].to)==fa) continue;
        ans[v]=ans[u]+sum-2*s[v];
        dfs2(v,u);
    }
    anss=max(anss,ans[u]);
}
```
    - **核心实现思想**：`dfs1`维护子树点权和`s[u]`、深度`d[u]`和子树的$\sum dist$`f[u]`。`dfs2`根据父亲节点的答案`ans[u]`、所有节点权值和`sum`以及子树点权和`s[v]`，递推计算儿子节点的答案`ans[v]`，并更新全局最大值`anss`。

### 最优关键思路或技巧
通过换根DP，将无根树问题转化为有根树问题进行处理。利用两次DFS，第一次DFS自底向上计算子树信息，第二次DFS自顶向下递推以不同节点为根时的答案，从而高效解决问题。

### 可拓展之处
同类型题常涉及树形结构上的动态规划问题，类似算法套路如在树中计算距离、权值和等相关问题，常通过换根DP改变根节点，利用子树信息递推全局信息。

### 推荐题目
- [P2986 伟大的奶牛聚集](https://www.luogu.org/problemnew/show/P2986)
- [P3478 [POI2008]STA-Station](https://www.luogu.com.cn/problem/P3478)
- [P4178 Tree](https://www.luogu.com.cn/problem/P4178)

### 个人心得摘录与总结
作者CreeperK提到本题与[P2986 伟大的奶牛聚集](https://www.luogu.org/problemnew/show/P2986)类似，只是本题求最大值，那道题求最小值，且那道题边有长度，通过对比相似题目，能更好地理解本题的解法。 

---
处理用时：107.77秒