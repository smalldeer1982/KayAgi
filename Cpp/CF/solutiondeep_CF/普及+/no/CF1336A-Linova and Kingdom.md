# 题目信息

# Linova and Kingdom

## 题目描述

Writing light novels is the most important thing in Linova's life. Last night, Linova dreamed about a fantastic kingdom. She began to write a light novel for the kingdom as soon as she woke up, and of course, she is the queen of it.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/776211708d76e2738717d34c412159f730c6de15.png)There are $ n $ cities and $ n-1 $ two-way roads connecting pairs of cities in the kingdom. From any city, you can reach any other city by walking through some roads. The cities are numbered from $ 1 $ to $ n $ , and the city $ 1 $ is the capital of the kingdom. So, the kingdom has a tree structure.

As the queen, Linova plans to choose exactly $ k $ cities developing industry, while the other cities will develop tourism. The capital also can be either industrial or tourism city.

A meeting is held in the capital once a year. To attend the meeting, each industry city sends an envoy. All envoys will follow the shortest path from the departure city to the capital (which is unique).

Traveling in tourism cities is pleasant. For each envoy, his happiness is equal to the number of tourism cities on his path.

In order to be a queen loved by people, Linova wants to choose $ k $ cities which can maximize the sum of happinesses of all envoys. Can you calculate the maximum sum for her?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/550bbb250626ee83a75f7874e99bb74967e95572.png)

In the first example, Linova can choose cities $ 2 $ , $ 5 $ , $ 6 $ , $ 7 $ to develop industry, then the happiness of the envoy from city $ 2 $ is $ 1 $ , the happiness of envoys from cities $ 5 $ , $ 6 $ , $ 7 $ is $ 2 $ . The sum of happinesses is $ 7 $ , and it can be proved to be the maximum one.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/42ded7a124702f40fc5538e5ca404a7c3df59128.png)

In the second example, choosing cities $ 3 $ , $ 4 $ developing industry can reach a sum of $ 3 $ , but remember that Linova plans to choose exactly $ k $ cities developing industry, then the maximum sum is $ 2 $ .

## 样例 #1

### 输入

```
7 4
1 2
1 3
1 4
3 5
3 6
4 7```

### 输出

```
7```

## 样例 #2

### 输入

```
4 1
1 2
1 3
2 4```

### 输出

```
2```

## 样例 #3

### 输入

```
8 5
7 5
1 7
6 1
3 7
8 3
2 1
4 5```

### 输出

```
9```

# AI分析结果

### 题目翻译
林诺娃生活中最重要的事情就是写轻小说。昨晚，林诺娃梦到了一个奇妙的王国。她一醒来就开始为这个王国写一部轻小说，当然，她是这个王国的女王。

在这个王国里有 $n$ 个城市，有 $n - 1$ 条双向道路连接着各个城市对。从任何一个城市出发，都可以通过走一些道路到达其他任何城市。城市从 $1$ 到 $n$ 编号，城市 $1$ 是王国的首都。所以，这个王国的结构是一棵树。

作为女王，林诺娃计划恰好选择 $k$ 个城市发展工业，而其他城市将发展旅游业。首都也可以是工业城市或旅游城市。

每年都会在首都举行一次会议。为了参加会议，每个工业城市都会派出一名特使。所有特使都会沿着从出发城市到首都的最短路径（这条路径是唯一的）前行。

在旅游城市旅行是令人愉快的。对于每个特使来说，他的幸福感等于他的路径上旅游城市的数量。

为了成为受人民爱戴的女王，林诺娃想选择 $k$ 个城市，使得所有特使的幸福感总和最大。你能为她计算出这个最大总和吗？

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，关键在于确定每个节点对答案的贡献，然后选择贡献最大的 $k$ 个节点。大部分题解通过深度优先搜索（DFS）预处理出每个节点的深度和子树大小，进而计算出节点的贡献。各题解的主要区别在于对节点贡献的计算方式和排序方法略有不同，但本质都是基于贪心策略。

### 所选题解
- **VenusM1nT（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接利用优先队列存储节点贡献，方便选取最大的 $k$ 个贡献。
    - **个人心得**：无
- **STA_Morlin（4星）**
    - **关键亮点**：详细证明了贪心策略的正确性，代码结构清晰，注释丰富，易于理解。
    - **个人心得**：无
- **wsyhb（4星）**
    - **关键亮点**：不仅给出了贪心策略的推导过程，还使用 `nth_element()` 函数优化了排序过程，时间复杂度为 $O(n)$。
    - **个人心得**：无

### 重点代码
#### VenusM1nT 的核心代码
```cpp
void Dfs(reg int u,reg int pre)
{
    dep[u]=dep[pre]+1;
    for(reg int i=fst[u];i;i=nxt[i])
    {
        reg int v=to[i];
        if(v==pre) continue;
        Dfs(v,u);
        siz[u]+=siz[v];
    }
    q.push(dep[u]-siz[u]-1);
    siz[u]++;
}
```
**核心实现思想**：通过 DFS 计算每个节点的深度和子树大小，然后计算该节点的贡献 `dep[u] - siz[u] - 1` 并压入优先队列。

#### STA_Morlin 的核心代码
```cpp
void dfs (int x,int fa) {
    dep[x] = dep[fa]+1;
    siz[x] = 1;
    for (int i = G.hed[x]; i; i = G.nxt[i]) {
        int t = G.to[i];
        if (t != fa) {
            dfs(t, x);
            siz[x] += siz[t];
        }
    }
    q.push(dep[x]-siz[x]);
    return ;
}
```
**核心实现思想**：同样使用 DFS 计算深度和子树大小，将节点贡献 `dep[x] - siz[x]` 压入优先队列。

#### wsyhb 的核心代码
```cpp
void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1;
    sz[x]=1;
    for(int i=Last[x];i;i=Next[i])
    {
        int y=End[i];
        if(y!=fa)
        {
            dfs(y,x);
            sz[x]+=sz[y];
        }
    }
    val[x]=dep[x]-sz[x];
}
```
**核心实现思想**：DFS 计算深度和子树大小，将节点贡献存储在 `val[x]` 中，后续使用 `nth_element()` 求前 $k$ 大。

### 关键思路或技巧
- **贪心策略**：选择一个节点时，其所有子节点都应被选择，通过计算每个节点的贡献（深度减去子树大小），选择贡献最大的 $k$ 个节点。
- **深度优先搜索（DFS）**：用于预处理每个节点的深度和子树大小。
- **优先队列或排序**：用于选取贡献最大的 $k$ 个节点。

### 拓展思路
同类型题目通常是在树结构上进行节点选择，以最大化或最小化某个目标值。类似算法套路包括利用 DFS 或 BFS 遍历树，计算节点的相关属性，然后根据贪心策略进行选择。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：经典的贪心问题，通过优先队列实现。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析出贪心策略，进而求解。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：涉及贪心排序和证明。

### 个人心得摘录与总结
- **FZzzz**：使用实数的 wqs 二分时卡精度，解决办法是把精度改成 `1e-6` 或在二分后面加 `mid = r`。总结：在使用涉及精度的算法时，要注意精度问题并采取相应的解决措施。
- **Vocalise**：比赛时未通过，原因一是没有考虑到接近 $-k$ 的负贡献，二是只考虑了到根的路径上的修改，没有考虑子树内的修改。总结：在实现算法时，要全面考虑各种情况，尤其是边界情况和对整体有影响的部分。 

---
处理用时：48.52秒