# 题目信息

# Tree Cutting

## 题目描述

You are given a tree with $ n $ vertices.

Your task is to find the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from this tree in such a way that the size of each remaining connected component $ ^{\dagger} $ is at least $ x $ .

 $ ^{\dagger} $ Two vertices $ v $ and $ u $ are in the same connected component if there exists a sequence of numbers $ t_1, t_2, \ldots, t_k $ of arbitrary length $ k $ , such that $ t_1 = v $ , $ t_k = u $ , and for each $ i $ from $ 1 $ to $ k - 1 $ , vertices $ t_i $ and $ t_{i+1} $ are connected by an edge.

## 说明/提示

The tree in the first set of input data:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)After removing the edge $ 1 $ — $ 3 $ , the tree will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)The tree has split into two connected components. The first component consists of two vertices: $ 1 $ and $ 2 $ . The second connected component consists of three vertices: $ 3, 4 $ and $ 5 $ . In both connected components, there are at least two vertices. It can be shown that the answer $ 3 $ is not achievable, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6```

### 输出

```
2
1
3
1
1
2```

# AI分析结果

### 题目翻译
## 题目描述
给定一棵有 $n$ 个顶点的树。

你的任务是找到最大的数 $x$，使得可以从这棵树中恰好移除 $k$ 条边，使得每个剩余连通分量 $^{\dagger}$ 的大小至少为 $x$。

$^{\dagger}$ 如果存在任意长度 $k$ 的数字序列 $t_1, t_2, \ldots, t_k$，使得 $t_1 = v$，$t_k = u$，并且对于从 $1$ 到 $k - 1$ 的每个 $i$，顶点 $t_i$ 和 $t_{i+1}$ 通过一条边相连，则两个顶点 $v$ 和 $u$ 在同一个连通分量中。

## 说明/提示
第一组输入数据中的树：

![树的初始状态](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)

移除边 $1$ — $3$ 后，树将如下所示：

![移除边后的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)

树被分割成两个连通分量。第一个分量由两个顶点组成：$1$ 和 $2$。第二个连通分量由三个顶点组成：$3$、$4$ 和 $5$。在两个连通分量中，顶点数至少为 $2$。可以证明无法达到答案 $3$，因此答案是 $2$。

## 样例 #1
### 输入
```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6
```

### 输出
```
2
1
3
1
1
2
```

### 综合分析与结论
这些题解的核心思路都是利用二分查找来确定最大的 $x$ 值，因为答案具有单调性，若 $x$ 满足条件，那么小于 $x$ 的值也一定满足。在二分查找的 `check` 函数中，主要采用贪心和 DFS 算法来模拟删边过程，判断是否能通过删除 $k$ 条边使得所有连通块大小至少为 $x$。

算法要点：
1. **二分查找**：确定答案的范围，不断缩小范围找到最大的 $x$。
2. **贪心策略**：在 DFS 过程中，当子树大小大于等于 $x$ 时，优先删除该子树与父节点的边。
3. **DFS 遍历**：统计子树大小，根据贪心策略进行删边操作。

解决难点：
1. **边界条件判断**：如最后剩余连通块大小是否满足要求，避免多删或少删边。
2. **数据结构选择**：使用邻接表存储树的结构，便于 DFS 遍历。

### 评分较高的题解
1. **作者：spfa_ (赞：9)，5星**
    - **关键亮点**：思路清晰，代码注释详细，对二分查找和 DFS 过程的实现简洁明了。
    - **核心代码**：
```cpp
void dfs(int x, int fa) {
    sz[x] = 1;
    for (int y:E[x]) if (y!= fa) {
        dfs(y, x);
        if (sz[y] >= w && sum-sz[y] >= w) ++tot, sum -= sz[y];
        else sz[x] += sz[y];
    }
}

bool check(int x) {
    tot = 1, w = x, sum = n; memset(sz, 0, sizeof(sz));
    dfs(1, 0); return tot > k;
}
```
核心实现思想：`dfs` 函数用于统计子树大小，并根据贪心策略删边；`check` 函数初始化相关变量，调用 `dfs` 函数判断是否满足条件。

2. **作者：cute_overmind (赞：4)，4星**
    - **关键亮点**：定义 `lst_p` 变量记录子树可返回的节点数，思路独特，代码实现简洁。
    - **核心代码**：
```cpp
int dfs1(int p, int f, int x){
    int lst = 1;
    for(int i = num[p] ; i ; i = e[i].nxt){
        int t = e[i].t;
        if(t == f) continue;
        lst += dfs1(t, p, x);
    }
    if(lst >= x) ans ++, lst = 0;
    return lst;
}

bool ck(int x){
    ans = 0;
    dfs1(1, 0, x);
    if(ans >= k + 1) return true;
    return false;
}
```
核心实现思想：`dfs1` 函数递归统计子树节点数，当节点数大于等于 $x$ 时，增加答案并重置节点数；`ck` 函数调用 `dfs1` 函数判断是否满足条件。

3. **作者：Shadow_T (赞：3)，4星**
    - **关键亮点**：赛时一遍过，思路清晰，对二分查找和 DFS 过程的实现简洁易懂。
    - **核心代码**：
```cpp
int dfs(int d,int x)
{
    int ans=1;
    for(int i=0;i<g[d].size();i++)
    if(!vis[g[d][i]])
    {
        vis[g[d][i]]=true;
        ans+=dfs(g[d][i],x);
    }
    if(ans>=x) 
    {
        ans=0,tot++;
    }
    return ans;
}

bool check(int x)
{
    tot=0;
    for(int i=1;i<=n;i++)
    vis[i]=false;
    vis[1]=true;
    int z=dfs(1,x);
    if(z<x) tot--;
    if(tot<k) return false;
    return true;
}
```
核心实现思想：`dfs` 函数统计子树大小，当子树大小大于等于 $x$ 时，重置子树大小并增加删边计数；`check` 函数初始化相关变量，调用 `dfs` 函数判断是否满足条件。

### 最优关键思路或技巧
1. **二分查找**：利用答案的单调性，通过二分查找快速确定最大的 $x$ 值。
2. **贪心策略**：在 DFS 过程中，优先删除子树大小大于等于 $x$ 的边，保证连通块大小尽可能大。
3. **数据结构**：使用邻接表存储树的结构，便于 DFS 遍历。

### 拓展思路
同类型题或类似算法套路：
1. 二分查找与贪心结合的题目，如最大化最小值、最小化最大值等问题。
2. 树的遍历和连通块相关的问题，可使用 DFS 或 BFS 算法。

### 推荐题目
1. [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：二分查找与贪心结合的题目。
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：最大化最小值问题，使用二分查找和贪心算法。
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：二分查找与贪心结合的题目。

### 个人心得摘录与总结
- **作者：Shadow_T**：赛时一遍过，说明对二分查找和贪心算法的掌握较为熟练，能够快速分析问题并实现代码。
- **作者：I_will_AKIOI**：赛时最后 5 分钟才写出，还寄了两发，说明该题有一定难度，需要注意边界条件和细节处理。同时提到使用懒标记来优化路径更新，是一种有效的优化技巧。

---
处理用时：46.26秒