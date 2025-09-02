# 题目信息

# Road Map

## 题目描述

There are $ n $ cities in Berland. Each city has its index — an integer number from $ 1 $ to $ n $ . The capital has index $ r_{1} $ . All the roads in Berland are two-way. The road system is such that there is exactly one path from the capital to each city, i.e. the road map looks like a tree. In Berland's chronicles the road map is kept in the following way: for each city $ i $ , different from the capital, there is kept number $ p_{i} $ — index of the last city on the way from the capital to $ i $ .

Once the king of Berland Berl XXXIV decided to move the capital from city $ r_{1} $ to city $ r_{2} $ . Naturally, after this the old representation of the road map in Berland's chronicles became incorrect. Please, help the king find out a new representation of the road map in the way described above.

## 样例 #1

### 输入

```
3 2 3
2 2
```

### 输出

```
2 3 ```

## 样例 #2

### 输入

```
6 2 4
6 1 2 4 2
```

### 输出

```
6 4 1 4 2 ```

# AI分析结果



# Road Map 题解分析

## 题目重述
在 Berland 有 $n$ 个城市，构成以 $r_1$ 为根的树形结构。每个非根节点的父节点信息 $p_i$ 被记录。现需将根节点改为 $r_2$，求新的父节点表示。

## 算法分类
图论 / 深度优先搜索 DFS

## 题解对比与结论

### 最优题解亮点
1. **yewanxingkong（4星）**
   - 邻接表存储树结构，DFS 遍历重构父节点关系
   - 输入处理简洁，跳过原根节点读取父节点
   - 代码清晰易懂，使用 vector 实现邻接表

2. **Reobrok_Kk（4星）**
   - 链式前向星存图，DFS 遍历记录父节点
   - 结构体封装边信息，代码模块化程度高
   - 输入处理准确，特判原根节点

3. **Na2PtCl6（4星）**
   - BFS 实现层级遍历，避免递归栈溢出风险
   - 使用标记数组避免重复访问
   - 队列实现简洁，适合大规模数据

### 核心思路
**无向图重构法**：将原树的父子关系转换为无向图，从新根节点出发进行 DFS/BFS 遍历，记录每个节点的父节点即为新树结构。

```cpp
// 以 yewanxingkong 的实现为例
void dfs(int xu, int fa) {
    chu[xu] = fa; // 记录父节点
    for (auto v : cun[xu]) 
        if (v != fa) dfs(v, xu);
}
```

## 拓展建议
1. **换根DP**：可学习树形动态规划的换根技巧
2. **树链剖分**：处理路径相关问题时的高效方法
3. **推荐题目**：
   - P1395 会议（换根DP经典）
   - P2633 Count on a tree（树结构处理）
   - P3379 最近公共祖先（LCA应用）

---
处理用时：85.85秒