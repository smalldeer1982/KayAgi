# 题目信息

# [USACO11MAR] Meeting Place S

## 题目描述

Bessie and Jonell are great friends. Since Farmer John scrambles where the cows graze every day, they are sometimes quite far from each other and can't talk.

The pastures and paths on FJ's farm form a 'tree' structure.  Each pasture has exactly one distinct path to any other pasture, and each pasture (except pasture #1, the 'root') also has a single parent node.

Bessie and Jonell have decided that they will always meet at the closest pasture that that is both an ancestor of Jonell's pasture and of Bessie's pasture.

FJ created a map of his N (1 <= N <= 1,000) pastures (conveniently numbered 1..N) that tells the parent P\_i (1 <= P\_i <= N) of each pasture except pasture 1, which has no parent.

FJ has released his daily grazing schedule for the next M (1 <= M <= 1,000) days, so Bessie and Jonell are deciding where they should meet each day for gossip. On day k, Bessie is in pasture B\_k (1 <= B\_k <= N) and Jonell is in pasture J\_k (1 <= J\_k <= N).

Given a map and schedule, help Bessie and Jonell find their meeting places.

```cpp
Consider, for example, the following farm layout:

                            Pasture      Parent Pasture
             [1]           ---------    ----------------
            / | \              1              ---
           /  |  \             2               1 
         [2] [3] [6]           3               1
         /        | \          4               2
        /         |  \         5               8
      [4]        [8]  [9]      6               1
                /   \          7               8
               /     \         8               6
             [5]     [7]       9               6

Here are the meeting places that Bessie and Jonell would choose
given a six day schedule of their initial grazing locations:

              Bessie      Jonell       Meeting Place
             --------    --------     ---------------
                 2           7               1
                 4           2               2
                 1           1               1
                 4           1               1
                 7           5               8
                 9           5               6
```




## 样例 #1

### 输入

```
9 6 
1 
1 
2 
8 
1 
8 
6 
6 
2 7 
4 2 
3 3 
4 1 
7 5 
9 5 
```

### 输出

```
1 
2 
3 
1 
8 
6 
```

# AI分析结果



### 综合分析与结论
本题要求多次查询两节点的最近公共祖先（LCA）。题解中主要包含暴力法、倍增法、树链剖分、Tarjan离线算法、欧拉序+RMQ等方法。根据数据规模（N,M ≤ 1,000），暴力法时间复杂度可接受，而倍增法则是更通用的高效解法。

---

### 高星题解推荐

#### 1. 作者：StudyingFather（★★★★☆）
**关键亮点**  
- **暴力法实现简洁**：通过标记路径快速找到首个公共祖先，代码仅需20行。
- **适用场景明确**：针对小数据量直接模拟，无需复杂预处理。
- **代码可读性高**：逻辑清晰，易于理解。

**核心代码**  
```cpp
while(1) {
    if(t[b]==1) { // 找到首个公共祖先
        printf("%d\n",b);
        break;
    }
    b = fa[b]; // 向上跳转
}
```

#### 2. 作者：hulean（★★★★★）
**关键亮点**  
- **详解倍增法原理**：深入讲解倍增思想与LCA的关系，适合学习。
- **代码结构规范**：预处理祖先表，通过二进制拆分高效跳跃。
- **鲁棒性强**：处理深度差与路径同步跳跃，覆盖所有边界情况。

**核心代码**  
```cpp
int lca(int u, int v) {
    if (deep[u] < deep[v]) swap(u, v);
    // 深度对齐
    for (int i = log2n; i >= 0; i--)
        if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
    // 同步跳跃找LCA
    for (int i = log2n; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
```

#### 3. 作者：meisr（★★★★☆）
**关键亮点**  
- **倍增法标准实现**：代码模块化，分离DFS预处理与查询逻辑。
- **优化代码结构**：通过递归实现树形遍历，减少冗余计算。
- **易拓展性**：代码框架可直接用于其他LCA变种问题。

**核心代码**  
```cpp
void dfs(int u) {
    for (int i = 1; (1<<i) <= deep[u]; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1]; // 倍增预处理
    for (int v : son[u]) dfs(v);
}
```

---

### 关键思路总结
1. **暴力标记法**：适用于小规模数据，通过记录路径上的所有祖先，线性查找首个交点。
2. **倍增法**：通过预处理每个节点的2^k级祖先，将跳跃复杂度降至O(log N)，平衡时间与空间。
3. **树链剖分**：将树分解为重链，通过链头跳跃快速定位LCA，常数更优但实现稍复杂。

---

### 拓展与举一反三
- **相似题目推荐**  
  - [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)  
  - [P1967 货车运输](https://www.luogu.com.cn/problem/P1967)（LCA结合最大生成树）  
  - [P4281 [AHOI2008] 紧急集合](https://www.luogu.com.cn/problem/P4281)（多节点LCA扩展）

- **个人心得摘录**  
  - **调试教训**（In_blue）：需注意根节点父指针的处理，否则会提前终止循环。  
  - **思维顿悟**（hulean）：倍增的二进制拆分本质是“从高位尝试跳跃”，避免回溯。

---
处理用时：92.19秒