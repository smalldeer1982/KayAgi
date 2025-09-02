# 题目信息

# Tree Pruning

## 题目描述

[t+pazolite, ginkiha, Hommarju - Paved Garden](https://soundcloud.com/fractalex-gd/ginkiha-paved-garden-little)

⠀



You are given a tree with $ n $ nodes, rooted at node $ 1 $ . In this problem, a leaf is a non-root node with degree $ 1 $ .

In one operation, you can remove a leaf and the edge adjacent to it (possibly, new leaves appear). What is the minimum number of operations that you have to perform to get a tree, also rooted at node $ 1 $ , where all the leaves are at the same distance from the root?

## 说明/提示

In the first two examples, the tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2018C/46789adad3b93ca642b297f7ca0ca574c7f98f60.png)In the first example, by removing edges $ (1, 3) $ and $ (2, 5) $ , the resulting tree has all leaves (nodes $ 6 $ and $ 7 $ ) at the same distance from the root (node $ 1 $ ), which is $ 3 $ . The answer is $ 2 $ , as it is the minimum number of edges that need to be removed to achieve the goal.

In the second example, removing edges $ (1, 4) $ and $ (5, 7) $ results in a tree where all leaves (nodes $ 4 $ and $ 5 $ ) are at the same distance from the root (node $ 1 $ ), which is $ 2 $ .

## 样例 #1

### 输入

```
3
7
1 2
1 3
2 4
2 5
4 6
4 7
7
1 2
1 3
1 4
2 5
3 6
5 7
15
12 9
1 6
6 14
9 11
8 7
3 5
13 5
6 10
13 15
13 6
14 12
7 2
8 1
1 4```

### 输出

```
2
2
5```

# AI分析结果



# Tree Pruning

## 题目描述

给定一棵包含 $n$ 个节点的树，根节点为 $1$。在该问题中，叶子节点被定义为非根且度数为 $1$ 的节点。

每次操作可以删除一个叶子节点及其相邻的边（删除后可能产生新的叶子节点）。求最少需要多少次操作，才能使剩下的树满足所有叶子节点到根节点的距离相同。

## 样例 #1

### 输入

```
3
7
1 2
1 3
2 4
2 5
4 6
4 7
7
1 2
1 3
1 4
2 5
3 6
5 7
15
12 9
1 6
6 14
9 11
8 7
3 5
13 5
13 15
13 6
14 12
7 2
8 1
1 4
```

### 输出

```
2
2
5
```

---

### 综合题解分析

#### 关键思路总结
1. **枚举最终深度**：所有题解均围绕枚举最终叶子深度 $d$ 展开，通过预处理以下两部分计算删除次数：
   - **深度 >d 的节点**：直接统计数量（后缀和）
   - **深度 <d 的路径**：通过拓扑排序剪枝或差分数组统计
2. **子树最大深度预处理**：通过 DFS 预处理每个节点的子树最大深度，结合差分数组快速计算需要删除的子树
3. **动态维护度数**：使用 BFS 分层处理，动态维护节点度数来判断是否需要剪枝

#### 最优题解推荐

##### 1. 作者：_xm（⭐⭐⭐⭐⭐）
**核心亮点**：
- BFS 分层维护当前保留的节点集合
- 动态维护节点度数，递归删除无效链
- 代码逻辑清晰，时间复杂度 $O(n)$
```cpp
vector<ll> lst = {1}; // BFS分层处理
for(ll dep = 1; dep <= n; dep++) {
    vector<ll> q; // 当前层节点
    for(auto u : lst) {
        for(auto v : G[u]) if(v != fa[u]) { // 添加下一层节点
            fa[v] = u; q.push_back(v); tot++;
        }
        while(u != 1 && de[u] - 1 == 0) { // 递归删除无效链
            de[fa[u]]--; de[u]--; tot--; u = fa[u];
        }
    }
    ans = max(ans, tot); // 记录最大保留节点数
    lst = q;
}
```

##### 2. 作者：TianTianChaoFang（⭐⭐⭐⭐）
**核心亮点**：
- 差分数组统计需要删除的子树
- 预处理子树最大深度，结合两次前缀和
```cpp
void dfs(int st, int pre) {
    mx[st] = d[st]; 
    for(auto &i : g[st]) if(i != pre) {
        dfs(i, st);
        k[d[st]] += sz[i]; // 直接子树的贡献
        mx[st] = max(mx[st], mx[i]);
    }
    if(st != 1) z[mx[st] + 1]++; // 差分数组标记
}
```

##### 3. 作者：Super_Cube（⭐⭐⭐⭐）
**代码简洁性**：
- 使用 `g[]` 和 `w[]` 分别统计深度贡献
- 单次 DFS 完成所有预处理
```cpp
for(int i=n;i!=1;--i){
    pre-=g[i]; // 深度>i的贡献
    ans=min(ans,pre+suf); // pre为深度>i，suf为深度<i
    suf+=w[i]; // 累计深度i的节点
}
```

---

### 同类型题目推荐
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)  
   **相似点**：树形 DP 中处理子树关系
2. [P2014 选课](https://www.luogu.com.cn/problem/P2014)  
   **相似点**：树形依赖问题中的分组处理
3. [P3177 树上染色](https://www.luogu.com.cn/problem/P3177)  
   **相似点**：子树贡献统计与最优解枚举

---

### 调试技巧摘录
1. **虚树构建陷阱**（作者：Richard_Whr）
   > "按 dfs 序排序后用深度和减去相邻结点 lca 的深度，这是虚树经典结论，但需要注意根节点必须包含在虚树中"
2. **差分数组边界**（作者：TianTianChaoFang）
   > "差分数组的标记位置是 mx[st]+1 而非 mx[st]，因为当保留深度 d 时，所有 mx[i] <d 的子树都需要删除"
3. **度数维护顺序**（作者：_xm）
   > "递归删除链时需要先更新父节点度数，再回溯处理可能新产生的无效链"

---
处理用时：51.11秒