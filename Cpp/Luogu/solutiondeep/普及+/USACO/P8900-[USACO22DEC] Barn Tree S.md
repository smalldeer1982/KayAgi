# 题目信息

# [USACO22DEC] Barn Tree S

## 题目描述

Farmer John 的农场有 $N$ 个牛棚 $(2 \le N \le 2 \times 10^5)$，编号为 $1 \cdots N$。有 $N−1$ 条道路，每条道路连接两个牛棚，并且从任一牛棚均可通过一些道路到达任一其他牛棚。目前，第 $j$ 个牛棚中有 $h_j$ 个干草捆 $(1 \le h_j \le 10^9)$。 

为使他的奶牛们满意，Farmer John 想移动这些干草，使得每个牛棚都有相同数量的干草捆。他可以选择任何一对由一条道路连接的牛棚，并命令他的农场工人将不超过第一个牛棚中干草捆数量的任意正整数个干草捆从第一个牛棚移动到第二个牛棚。 

请求出一个 Farmer John 可以发出的命令序列，以尽可能少的命令数完成这一任务。输入保证存在符合要求的命令序列。 

## 说明/提示

### 样例 1 解释

在这个例子中，共有十二个干草捆和四个牛棚，这意味着每个牛棚最后必须有三个干草捆。输出样例中的命令顺序可以用以下的自然语言表述： 

1. 从牛棚 $3$ 到牛棚 $2$，移动 $1$ 个干草捆。
2. 从牛棚 $4$ 到牛棚 $2$，移动 $2$ 个干草捆。
3. 从牛棚 $2$ 到牛棚 $1$，移动 $1$ 个干草捆。

### 测试点性质

- 测试点 $2-8$ 满足 $N \le 5000$。
- 测试点 $7-10$ 满足 $v_i=u_i+1$。
- 测试点 $11-16$ 没有额外限制。

## 样例 #1

### 输入

```
4
2 1 4 5
1 2
2 3
2 4```

### 输出

```
3
3 2 1
4 2 2
2 1 1```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是将无根树以 1 号节点为根定形，计算每个节点应有的干草捆平均值，通过深度优先搜索（DFS）来处理节点间干草捆的转移。不同题解在处理转移顺序和实现细节上有所差异，但都围绕着让子树内尽可能自给自足，以减少操作次数的原则。难点在于保证转移过程中节点的干草捆数量非负，多数题解通过先“上传”多余干草捆，再“下传”缺少的干草捆来解决。

### 所选题解
- **作者：yemuzhe（5星）**
    - **关键亮点**：思路清晰，详细阐述了方案、顺序、具体流程及证明，代码可读性高，注释丰富。
    - **核心代码**：
```c++
void dfs (int x, int fa) {
    for (int i = head[x], y; i; i = nxt[i]) {
        if ((y = ver[i]) == fa) continue;
        dfs (y, x);
    }
    f[x] = a[x] - ave, a[fa] += f[x], ans += (bool) f[x];
}

void sol (int x, int fa) {
    for (int i = head[x], y; i; i = nxt[i]) {
        if ((y = ver[i]) == fa || f[y] < 0) continue;
        sol (y, x);
    }
    for (int i = head[x], y; i; i = nxt[i]) {
        if ((y = ver[i]) == fa || f[y] >= 0) continue;
        printf ("%d %d %lld\n", x, y, -f[y]), sol (y, x);
    }
    if (f[x] > 0) printf ("%d %d %lld\n", x, fa, f[x]);
}
```
    - **核心实现思想**：`dfs` 函数用于处理每个节点多余或缺少的干草捆，并累计到父节点上，统计答案。`sol` 函数解决转移顺序问题，先处理多余干草捆的子节点，再处理缺少干草捆的子节点，最后将多余的干草捆上传给父节点。

- **作者：Lantrol（4星）**
    - **关键亮点**：思路简洁明了，对策略的最优性有详细解释，代码实现难度不大。
    - **核心代码**：
```cpp
void dfs1(int u, int fa) {
    for(int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs1(v, u);
        if(val[v] > 0) {
            ansu[++ansc] = v; ansv[ansc] = u; answ[ansc] = val[v];
        }
        val[u] += val[v];
    }
}

void dfs2(int u, int fa) {
    for(int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == fa) continue;
        if(val[v] < 0) {
            ansu[++ansc] = u; ansv[ansc] = v; answ[ansc] = -val[v];
        }
        dfs2(v, u);
    }
}
```
    - **核心实现思想**：`dfs1` 函数从下往上做上传操作，将子树中多余的干草捆贡献给父节点。`dfs2` 函数从上往下做下传操作，将父节点的干草捆下传给缺少的子树。

- **作者：Untitled10032（4星）**
    - **关键亮点**：详细说明了初步想法的问题及最终解法，通过确定递归顺序保证节点权值非负。
    - **核心代码**：
```cpp
pair<ll, ll> dfssum(int x, int fa) {
    ll val = 0, cnt = 0;
    for (auto i : g[x])
        if (i!= fa) {
            const pair<ll, ll> t = dfssum(i, x);
            val += t.first;
            cnt += t.second;
        }
    v[x] = (val - cnt * target) + h[x];
    return {val + h[x], cnt + 1};
}

void dfs(int x, int fa) {
    for (auto i : g[x])
        if (i!= fa && v[i] >= target)
            dfs(i, x);
    for (auto i : g[x]) 
        if (i!= fa) {
            const ll t = v[i] - target;
            if (t > 0) ans.push_back({i, x, t});
        }
    for (auto i : g[x]) 
        if (i!= fa) {
            const ll t = v[i] - target;
            if (t < 0) ans.push_back({x, i, -t});
        }
    for (auto i : g[x])
        if (i!= fa && v[i] < target)
            dfs(i, x);
}
```
    - **核心实现思想**：`dfssum` 函数计算以每个节点为根的子树处理后根节点的权值。`dfs` 函数先递归处理权值大于等于目标值的子节点，再调整子节点的权值，最后递归处理权值小于目标值的子节点。

### 最优关键思路或技巧
- **确定递归顺序**：先“上传”多余干草捆，再“下传”缺少的干草捆，保证节点的干草捆数量非负。
- **相对点权**：将每个节点的实际点权与平均点权的差作为相对点权，方便处理节点间的转移。

### 可拓展之处
同类型题可拓展到有向树、带权树等情况，类似算法套路可用于解决资源分配、流量平衡等问题。

### 推荐题目
- [P1311 选择客栈](https://www.luogu.com.cn/problem/P1311)
- [P1087 FBI树](https://www.luogu.com.cn/problem/P1087)
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)

### 个人心得
- **作者：Untitled10032**：提到初步想法在特定数据下会出现负权点的问题，从而确定递归顺序，让正被递归到的节点点权尽量大。这表明在解题时要考虑特殊情况，对算法进行优化。

---
处理用时：37.02秒