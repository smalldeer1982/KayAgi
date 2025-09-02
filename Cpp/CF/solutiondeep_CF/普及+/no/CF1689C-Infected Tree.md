# 题目信息

# Infected Tree

## 题目描述

Byteland is a beautiful land known because of its beautiful trees.

Misha has found a binary tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . A binary tree is an acyclic connected bidirectional graph containing $ n $ vertices and $ n - 1 $ edges. Each vertex has a degree at most $ 3 $ , whereas the root is the vertex with the number $ 1 $ and it has a degree at most $ 2 $ .

Unfortunately, the root got infected.

The following process happens $ n $ times:

- Misha either chooses a non-infected (and not deleted) vertex and deletes it with all edges which have an end in this vertex or just does nothing.
- Then, the infection spreads to each vertex that is connected by an edge to an already infected vertex (all already infected vertices remain infected).

As Misha does not have much time to think, please tell him what is the maximum number of vertices he can save from the infection (note that deleted vertices are not counted as saved).

## 说明/提示

In the first test case, the only possible action is to delete vertex $ 2 $ , after which we save $ 0 $ vertices in total.

In the second test case, if we delete vertex $ 2 $ , we can save vertices $ 3 $ and $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1689C/1f479df0f6df9637a1dfee43da055c650bdae647.png)

## 样例 #1

### 输入

```
4
2
1 2
4
1 2
2 3
2 4
7
1 2
1 5
2 3
2 4
5 6
5 7
15
1 2
2 3
3 4
4 5
4 6
3 7
2 8
1 9
9 10
9 11
10 12
10 13
11 14
11 15```

### 输出

```
0
2
2
10```

# AI分析结果

### 题目翻译
# 感染的树

## 题目描述
比特兰是一片美丽的土地，以其美丽的树木而闻名。

米莎发现了一棵有 $n$ 个顶点的二叉树，顶点编号从 $1$ 到 $n$。二叉树是一种无环的连通双向图，包含 $n$ 个顶点和 $n - 1$ 条边。每个顶点的度数最多为 $3$，而根节点是编号为 $1$ 的顶点，其度数最多为 $2$。

不幸的是，根节点被感染了。

以下过程会发生 $n$ 次：
- 米莎要么选择一个未被感染（且未被删除）的顶点，并删除该顶点及其所有与之相连的边，要么什么都不做。
- 然后，感染会传播到与已感染顶点通过边相连的每个顶点（所有已感染的顶点仍然保持感染状态）。

由于米莎没有太多时间思考，请告诉他他最多可以拯救多少个顶点免受感染（注意，被删除的顶点不被视为被拯救）。

## 说明/提示
在第一个测试用例中，唯一可能的操作是删除顶点 $2$，之后我们总共拯救了 $0$ 个顶点。

在第二个测试用例中，如果我们删除顶点 $2$，我们可以拯救顶点 $3$ 和 $4$。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1689C/1f479df0f6df9637a1dfee43da055c650bdae647.png)

## 样例 #1
### 输入
```
4
2
1 2
4
1 2
2 3
2 4
7
1 2
1 5
2 3
2 4
5 6
5 7
15
1 2
2 3
3 4
4 5
4 6
3 7
2 8
1 9
9 10
9 11
10 12
10 13
11 14
11 15
```
### 输出
```
0
2
2
10
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕树形动态规划展开，通过定义合适的状态和状态转移方程来解决问题。不同题解的思路本质相同，但在实现细节和代码风格上有所差异。
- **思路**：核心思路是考虑在每个节点被感染的情况下，通过删除其子节点来最大化保留的节点数。对于二叉树的每个节点，删除一个子节点后，问题转化为另一个子节点被感染时的子问题。
- **算法要点**：定义状态 $dp[i]$ 表示以 $i$ 为根的子树中，若 $i$ 被感染，最多能保留的节点数。状态转移方程为 $dp[i]=\max(dp[lson]+size[rson]-1,dp[rson]+size[lson]-1)$，其中 $size[i]$ 表示以 $i$ 为根的子树的大小。
- **解决难点**：处理子树为空的情况，避免 $size[son] - 1$ 为负数；多组数据时需要对数组进行清零操作。

### 所选题解
- **作者：冬天的雨 (赞：20)，4星**
  - **关键亮点**：思路清晰，对动态规划的状态和转移方程解释详细，代码注释丰富，易于理解。
  - **个人心得**：赛时差点写了树链剖分，后发现是二叉树，同机房大佬没注意二叉树条件惨遭爆零，提醒要注意题目条件。
- **作者：linyihdfj (赞：1)，4星**
  - **关键亮点**：对题目分析和状态转移的推导过程清晰，代码结构清晰，注释合理。
- **作者：KukCair (赞：1)，4星**
  - **关键亮点**：对状态和转移的考虑角度明确，代码简洁，使用了 $sum$ 变量来快速计算另一个子树的 $dp$ 值。

### 重点代码
以下是冬天的雨的题解中的核心代码：
```cpp
void dfs(int u,int root){
    sze[u]=1,dp[u]=0; // dp数组存储如果我被感染了能活多少个
    int sum=0;
    for(int i=head[u];i;i=edge[i].pre){
        int v=edge[i].to;
        if(v!=root){
            dfs(v,u);
            sum+=dp[v];
            sze[u]+=sze[v];
        }
    }
    for(int i=head[u];i;i=edge[i].pre){
        int v=edge[i].to;
        if(v!=root){
            dp[u]=max(dp[u],sum-dp[v]+sze[v]-1);
        }
    }
}
```
**核心实现思想**：通过深度优先搜索遍历二叉树，先计算以每个节点为根的子树的大小 $sze$，并累加子节点的 $dp$ 值到 $sum$ 中。然后遍历每个子节点，根据状态转移方程更新当前节点的 $dp$ 值。

### 关键思路或技巧
- **树形动态规划**：利用树形结构的特点，将问题分解为子问题，通过状态转移方程求解。
- **预处理子树大小**：在深度优先搜索过程中计算每个节点的子树大小，方便后续状态转移。
- **多组数据处理**：每次处理新数据时，对相关数组进行清零操作，避免数据干扰。

### 可拓展之处
同类型题或类似算法套路：其他树形动态规划问题，如树上的最大独立集、树上的最小支配集等。这些问题通常都需要根据树的结构特点，定义合适的状态和状态转移方程来解决。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
- [P2014 选课](https://www.luogu.com.cn/problem/P2014)
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

---
处理用时：62.69秒