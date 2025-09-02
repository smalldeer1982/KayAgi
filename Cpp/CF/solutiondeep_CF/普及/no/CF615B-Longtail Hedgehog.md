# 题目信息

# Longtail Hedgehog

## 题目描述

This Christmas Santa gave Masha a magic picture and a pencil. The picture consists of $ n $ points connected by $ m $ segments (they might cross in any way, that doesn't matter). No two segments connect the same pair of points, and no segment connects the point to itself. Masha wants to color some segments in order paint a hedgehog. In Mashas mind every hedgehog consists of a tail and some spines. She wants to paint the tail that satisfies the following conditions:

1. Only segments already presented on the picture can be painted;
2. The tail should be continuous, i.e. consists of some sequence of points, such that every two neighbouring points are connected by a colored segment;
3. The numbers of points from the beginning of the tail to the end should strictly increase.

Masha defines the length of the tail as the number of points in it. Also, she wants to paint some spines. To do so, Masha will paint all the segments, such that one of their ends is the endpoint of the tail. Masha defines the beauty of a hedgehog as the length of the tail multiplied by the number of spines. Masha wants to color the most beautiful hedgehog. Help her calculate what result she may hope to get.

Note that according to Masha's definition of a hedgehog, one segment may simultaneously serve as a spine and a part of the tail (she is a little girl after all). Take a look at the picture for further clarifications.

## 说明/提示

The picture below corresponds to the first sample. Segments that form the hedgehog are painted red. The tail consists of a sequence of points with numbers $ 1 $ , $ 2 $ and $ 5 $ . The following segments are spines: ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 5 $ ) and ( $ 4 $ , $ 5 $ ). Therefore, the beauty of the hedgehog is equal to $ 3·3=9 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF615B/dbda6af90158fd5ce193a3a2582b631a7f4eefdf.png)

## 样例 #1

### 输入

```
8 6
4 5
3 5
2 5
1 2
2 8
6 7
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
12
```

# AI分析结果



# Longtail Hedgehog

## 题目描述

圣诞老人送给玛莎一幅魔法画和一支铅笔。这幅画由 $n$ 个点和 $m$ 条线段组成（线段可能以任意方式交叉）。没有两条线段连接同一对点，且没有线段连接点自身。玛莎希望给部分线段上色，绘制一只刺猬。在玛莎的构想中，刺猬包含一条尾巴和若干刺。尾巴需满足以下条件：

1. 仅使用图中存在的线段；
2. 尾巴是连续的，即由一系列点构成，相邻点间有染色线段连接；
3. 从尾端到末端的点编号必须严格递增。

尾巴长度定义为点的个数。刺被定义为所有以尾巴末端为端点的线段。刺猬的美丽值为尾巴长度乘以刺的数量。求可能的最大美丽值。

## 说明/提示

样例示意图中，尾巴由点 $1 \rightarrow 2 \rightarrow 5$ 构成，末端点 $5$ 的度数为 $3$，故美丽值为 $3 \times 3 = 9$。

## 样例 #1

### 输入
```
8 6
4 5
3 5
2 5
1 2
2 8
6 7
```

### 输出
```
9
```

---

**算法分类**：动态规划 + 图论

---

## 题解分析与结论

### 核心思路
1. **有向图建模**：将原无向图的边转换为从小编号节点指向大编号节点的有向边，确保链严格递增。
2. **动态规划状态设计**：定义 `f[u]` 表示以节点 `u` 结尾的最长链长度。
3. **拓扑序优化**：通过入度控制处理顺序，当节点的入度降为0时（所有前驱节点已处理完毕）才进行状态转移，确保时间复杂度为 $O(n+m)$。
4. **度数的预处理**：每个节点的度数在输入阶段直接计算，与有向图处理无关。

---

## 精选题解

### 题解1（jch123）⭐⭐⭐⭐
**亮点**：  
- 使用动态规划配合入度剪枝
- 代码简洁，状态转移清晰
- 通过 `in[]` 数组控制DFS触发时机

**核心代码**：
```cpp
void dfs(int u) {
    vis[u] = 1;
    for(auto v : edge[u]) {
        l[v] = max(l[v], l[u] + 1); // 状态转移
        in[v]--;
        if(in[v] == 0) dfs(v);      // 确保前驱已处理完毕
    }
}
```

### 题解2（__Shine__）⭐⭐⭐⭐
**亮点**：  
- 显式拓扑排序思想
- 通过入度数组维护未处理前驱数
- 个人心得：提到直接DFS会TLE，改用拓扑排序优化

**核心代码**：
```cpp
void dfs(int u, LL x) {
    for(int i=head[u]; i!=-1; i=edge[i].next) {
        int v = edge[i].to;
        ans[v] = max(ans[v], x);
        in[v]--;
        if(in[v] == 0) dfs(v, ans[v] + 1);
    }
}
```

---

## 关键技巧总结
1. **有向图转换**：将无向边转换为单向边，确保编号递增特性。
2. **拓扑序处理**：通过入度控制状态转移顺序，避免重复计算。
3. **度数预处理**：在输入阶段直接计算原始度数，与有向图处理解耦。

---

## 类似题目推荐
1. [P1137 旅游计划](https://www.luogu.com.cn/problem/P1137)  
   （最长路径问题，拓扑排序应用）
2. [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)  
   （入度出度统计，拓扑排序DP）
3. [P2196 挖地雷](https://www.luogu.com.cn/problem/P2196)  
   （DAG上的动态规划）

---
处理用时：59.24秒