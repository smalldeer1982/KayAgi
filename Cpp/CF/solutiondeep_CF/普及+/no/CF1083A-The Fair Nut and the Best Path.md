# 题目信息

# The Fair Nut and the Best Path

## 题目描述

The Fair Nut is going to travel to the Tree Country, in which there are $ n $ cities. Most of the land of this country is covered by forest. Furthermore, the local road system forms a tree (connected graph without cycles). Nut wants to rent a car in the city $ u $ and go by a simple path to city $ v $ . He hasn't determined the path, so it's time to do it. Note that chosen path can consist of only one vertex.

A filling station is located in every city. Because of strange law, Nut can buy only $ w_i $ liters of gasoline in the $ i $ -th city. We can assume, that he has infinite money. Each road has a length, and as soon as Nut drives through this road, the amount of gasoline decreases by length. Of course, Nut can't choose a path, which consists of roads, where he runs out of gasoline. He can buy gasoline in every visited city, even in the first and the last.

He also wants to find the maximum amount of gasoline that he can have at the end of the path. Help him: count it.

## 说明/提示

The optimal way in the first example is $ 2 \to 1 \to 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083A/9cde903713bc2c3037de1f95f6d689e21702b992.png)The optimal way in the second example is $ 2 \to 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083A/ba9b6431b860ed0c426ce30e31a270fdf4bfbaf1.png)

## 样例 #1

### 输入

```
3
1 3 3
1 2 2
1 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
6 3 2 5 0
1 2 10
2 3 3
2 4 1
1 5 1
```

### 输出

```
7
```

# AI分析结果

### 题目内容
# 公平坚果与最佳路径

## 题目描述
公平坚果打算前往树之国旅行，该国共有 \(n\) 座城市。这个国家的大部分土地都被森林覆盖。此外，当地的道路系统构成了一棵树（即连通无环图）。坚果想在城市 \(u\) 租一辆车，然后沿着一条简单路径前往城市 \(v\) 。他还没有确定具体路径，所以现在是时候做这件事了。注意，所选路径可以只包含一个顶点。

每座城市都设有一个加油站。由于奇怪的法律规定，坚果在第 \(i\) 座城市只能购买 \(w_i\) 升汽油。我们可以假设他有无限的钱。每条道路都有长度，一旦坚果驾车经过这条道路，汽油量就会减少相应的长度。当然，坚果不能选择一条会让他在途中耗尽汽油的路径。他可以在每个经过的城市购买汽油，包括起点和终点城市。

他还想找到在路径终点时所能拥有的最大汽油量。请帮助他计算这个最大值。

## 说明/提示
第一个示例中的最优路径是 \(2 \to 1 \to 3\) 。
![第一个示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083A/9cde903713bc2c3037de1f95f6d689e21702b992.png)
第二个示例中的最优路径是 \(2 \to 4\) 。
![第二个示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1083A/ba9b6431b860ed0c426ce30e31a270fdf4bfbaf1.png)

## 样例 #1
### 输入
```
3
1 3 3
1 2 2
1 3 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
5
6 3 2 5 0
1 2 10
2 3 3
2 4 1
1 5 1
```
### 输出
```
7
```

### 算法分类
动态规划

### 综合分析与结论
这些题解均采用树形动态规划解决该问题，核心思路是通过对树进行深度优先搜索（DFS），记录每个节点相关的路径收益值，进而得到全局最优解。各题解的主要区别在于对状态转移方程的描述及代码实现细节。难点在于如何准确地定义状态以及推导出正确的状态转移方程，以确保考虑到所有可能的路径情况。

### 所选的题解
- **作者JustBlack（5星）**
  - **关键亮点**：思路清晰，简洁明了地阐述了树形DP的状态定义和转移方程。`dp[i][0]` 表示以 `i` 为终点的权重最大的路径，`dp[i][1]` 表示 `i` 为中间点的权重最大的路径，并据此给出了清晰的代码实现。
  - **核心代码**：
```c++
void dfs(int u,int fa)
{
    lli max1=0,max2=0;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,u);
        if(dp[v][0]-e[i].w>=max1)
        {
            max2=max1;
            max1=dp[v][0]-e[i].w;
        }
        else if(dp[v][0]-e[i].w>max2)
            max2=dp[v][0]-e[i].w;
    }
    dp[u][1]=max1+max2+a[u];
    dp[u][0]=max1+a[u];
    ans=max(ans,max(dp[u][0],dp[u][1]));
}
```
  - **核心实现思想**：在DFS过程中，对于每个节点 `u`，遍历其所有子节点 `v`，计算以 `v` 为终点的路径最值来更新 `max1` 和 `max2`（分别表示最大和次大值），从而得到 `dp[u][0]` 和 `dp[u][1]`，并更新全局答案 `ans`。

- **作者Nicrobot（4星）**
  - **关键亮点**：先对题目限制进行简化，指出任意时刻收益值不为负这个限制是多余的，使问题更易于理解。代码简洁，逻辑清晰。
  - **核心代码**：
```c++
void dfs(int now, int fa) {
    long long p1 = 0, p2 = 0;
    for (pair<int, int> tmp : e[now]) {
        int i = tmp.first, c = tmp.second;
        if (i == fa) continue;
        dfs(i, now);
        long long t = dp[i] - c; 
        if (t > p1) p2 = p1, p1 = t; 
        else if (t > p2) p2 = t;
    }
    dp[now] = p1 + w[now];  
    ans = max(ans, p1 + p2 + w[now]);  
}
```
  - **核心实现思想**：通过DFS遍历树，在每个节点 `now` 处，从其子节点 `i` 的 `dp[i]` 减去边权 `c` 得到到 `i` 这棵子树内结点路径的最值 `t`，更新总体最值 `p1` 和次大值 `p2`，进而得到 `dp[now]` 并更新答案 `ans`。

- **作者CRTL_xzh2009（4星）**
  - **关键亮点**：详细地将题意转化为在树上求一条路径使所有点权值和减去所有边权值和最大，并清晰地阐述了状态定义和转移方程，考虑了经过节点的不同路径情况。
  - **核心代码**：
```c++
void dfs(int u,int fa){
    f1[u]=f2[u]=0;
    for(int i=h[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa)continue;dfs(v,u);
        if(f1[v]+a[v]-c[i]>f1[u])f2[u]=f1[u],f1[u]=f1[v]-c[i]+a[v];
        else if(f1[v]+a[v]-c[i]>f2[u])f2[u]=f1[v]-c[i]+a[v];
    }    
    ans=max(ans,f1[u]+f2[u]+a[u]);
}
```
  - **核心实现思想**：在DFS中，对于节点 `u`，遍历其子节点 `v`，根据 `f1[v]` 等计算并更新 `f1[u]` 和 `f2[u]`（分别表示到其子孙结点的最大费用和来自不同子树的次大费用），从而更新全局最大费用 `ans`。

### 最优关键思路或技巧
采用树形动态规划，通过DFS遍历树，定义合适的状态（如以某节点为终点或中间点的最大路径收益），利用子树信息推导状态转移方程，从而高效地解决问题。同时，简化问题条件（如指出收益值不为负的限制多余）有助于更好地理解和解决问题。

### 可拓展之处
同类型题通常围绕树上路径的权值计算，类似算法套路是利用树的递归结构进行动态规划，状态定义一般与节点自身及子树相关，通过DFS实现状态转移。例如，可能会改变点权和边权的计算规则，或者对路径有其他限制条件。

### 洛谷相似题目推荐
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：同样是树上的动态规划问题，需要根据节点间的关系（树结构）定义状态并进行状态转移。
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：在二叉树上进行动态规划，涉及对树结构的处理和状态的定义与转移。
- [P3398 仓鼠找sugar](https://www.luogu.com.cn/problem/P3398)：结合树的性质和动态规划，通过处理树上路径来解决问题。 

---
处理用时：110.88秒