# 题目信息

# Work Group

## 题目描述

One Big Software Company has $ n $ employees numbered from $ 1 $ to $ n $ . The director is assigned number $ 1 $ . Every employee of the company except the director has exactly one immediate superior. The director, of course, doesn't have a superior.

We will call person $ a $ a subordinates of another person $ b $ , if either $ b $ is an immediate supervisor of $ a $ , or the immediate supervisor of $ a $ is a subordinate to person $ b $ . In particular, subordinates of the head are all other employees of the company.

To solve achieve an Important Goal we need to form a workgroup. Every person has some efficiency, expressed by a positive integer $ a_{i} $ , where $ i $ is the person's number. The efficiency of the workgroup is defined as the total efficiency of all the people included in it.

The employees of the big software company are obsessed with modern ways of work process organization. Today pair programming is at the peak of popularity, so the workgroup should be formed with the following condition. Each person entering the workgroup should be able to sort all of his subordinates who are also in the workgroup into pairs. In other words, for each of the members of the workgroup the number of his subordinates within the workgroup should be even.

Your task is to determine the maximum possible efficiency of the workgroup formed at observing the given condition. Any person including the director of company can enter the workgroup.

## 说明/提示

In the sample test the most effective way is to make a workgroup from employees number $ 1,2,4,5,6 $ .

## 样例 #1

### 输入

```
7
-1 3
1 2
1 1
1 4
4 5
4 3
5 2
```

### 输出

```
17
```

# AI分析结果

### 题目内容
# 工作小组

## 题目描述
一家大型软件公司有 $n$ 名员工，编号从 $1$ 到 $n$ 。公司董事编号为 $1$ 。除董事外，公司的每位员工都恰好有一位直属上级。当然，董事没有上级。

如果 $b$ 是 $a$ 的直属上级，或者 $a$ 的直属上级是 $b$ 的下属，我们就称 $a$ 是 $b$ 的下属。特别地，董事的下属是公司的所有其他员工。

为了实现一个重要目标，我们需要组建一个工作小组。每个员工都有一定的工作效率，用正整数 $a_{i}$ 表示，其中 $i$ 是员工的编号。工作小组的效率定义为小组中所有成员的效率总和。

这家大型软件公司的员工热衷于现代工作流程组织方式。如今，结对编程非常流行，因此工作小组的组建应满足以下条件：进入工作小组的每个员工，都应能够将其同样在工作小组中的下属分成若干对。换句话说，对于工作小组中的每个成员，其在小组中的下属数量应为偶数。

你的任务是确定在满足给定条件下，工作小组的最大可能效率。包括公司董事在内的任何人都可以进入工作小组。

## 说明/提示
在示例测试中，最有效的方法是从编号为 $1,2,4,5,6$ 的员工中组建工作小组。

## 样例 #1
### 输入
```
7
-1 3
1 2
1 1
1 4
4 5
4 3
5 2
```
### 输出
```
17
```

### 算法分类
动态规划

### 综合分析与结论
这些题解均采用树形动态规划来解决问题。核心思路是通过定义状态表示以某节点为根的子树在不同奇偶选择情况下的最大权值和，利用状态转移方程进行递推。各题解的算法要点和难点类似，主要区别在于状态定义的细节和代码实现风格。

### 所选的题解
 - **作者：bunH2O (5星)**
    - **关键亮点**：思路清晰，状态定义简洁明了，用 $f[x][0/1]$ 分别表示子树 $x$ 中有偶数/奇数个在点集中的点时最大的权值和，转移方程解释详细。
    - **重点代码**：
```cpp
void dfs(ll u)
{
    f[u][1]=-1145141919810;
    for(int i=0;i<tree[u].size();i++)
    {
        ll v=tree[u][i];
        dfs(v);
        ll x=f[u][0],y=f[u][1];
        f[u][0]=max(f[v][0]+x,f[v][1]+y);
        f[u][1]=max(f[v][1]+x,f[v][0]+y);
    }
    f[u][1]=max(f[u][1],f[u][0]+a[u]);
}
```
核心实现思想：通过深度优先搜索遍历树，在每个节点根据子节点的状态更新自身状态，考虑子树中选择偶数或奇数个节点的情况，最后根据题意，若当前节点选入点集需满足子树在点集的点为奇数，更新 $f[u][1]$。
 - **作者：Hello，yearning (4星)**
    - **关键亮点**：状态定义明确，转移方程表述清晰，代码简洁且注释详细。
    - **重点代码**：
```cpp
void dfs(int u,int fa)
{
    dp[u][1]=-1ll<<62;
    for(int i=h[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,u);
        ll x1=dp[u][1],x0=dp[u][0];
        dp[u][0]=max(dp[v][1]+x1,dp[v][0]+x0);
        dp[u][1]=max(dp[v][1]+x0,dp[v][0]+x1);
    }
    dp[u][1]=max(dp[u][1],dp[u][0]+v[u]);
}
```
核心实现思想：同样利用深度优先搜索，在遍历过程中根据子节点状态更新当前节点状态，最后根据条件更新当前节点选入点集时的最大权值和。
 - **作者：heshuxi (4星)**
    - **关键亮点**：做题思路阐述详细，从分析题目限制入手，逐步得出状态设计和转移方程，易于理解。
    - **重点代码**：
```cpp
void dfs(int u){
    f[u][1]=LONG_LONG_MIN;
    for(int e=head[u];e;e=edge[e].next){
        int v=edge[e].to;dfs(v);
        int x=f[u][0],y=f[u][1];
        f[u][0]=max(f[v][0]+x,f[v][1]+y);
        f[u][1]=max(f[v][1]+x,f[v][0]+y);
    }
    f[u][1]=max(f[u][1],f[u][0]+p[u]);
}
```
核心实现思想：通过深度优先搜索，在每个节点处基于子节点状态更新自身状态，考虑奇偶情况，最后根据题目条件更新当前节点选入时的最大权值和。

### 最优关键思路或技巧
利用树形动态规划，通过定义合适的二维状态表示子树的奇偶选择情况，根据奇偶运算特性构建状态转移方程，在深度优先搜索遍历树的过程中完成状态更新。

### 可拓展之处
同类型题通常围绕树形结构，结合特定条件求最值或方案数。类似算法套路是根据题目条件定义合适的状态，利用树的递归性质进行状态转移。

### 推荐洛谷题目
 - [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
 - [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)
 - [P2431 正妹吃月饼](https://www.luogu.com.cn/problem/P2431)

---
处理用时：73.89秒