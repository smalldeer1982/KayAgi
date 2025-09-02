# 题目信息

# Expected diameter of a tree

## 题目描述

Pasha is a good student and one of MoJaK's best friends. He always have a problem to think about. Today they had a talk about the following problem.

We have a forest (acyclic undirected graph) with $ n $ vertices and $ m $ edges. There are $ q $ queries we should answer. In each query two vertices $ v $ and $ u $ are given. Let $ V $ be the set of vertices in the connected component of the graph that contains $ v $ , and $ U $ be the set of vertices in the connected component of the graph that contains $ u $ . Let's add an edge between some vertex ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/8ef01bdc02f37e886781700f62479c92154da008.png) and some vertex in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/0479fe8afb5e9211cdac4c2d711ca0b8e2ad6e82.png) and compute the value $ d $ of the resulting component. If the resulting component is a tree, the value $ d $ is the diameter of the component, and it is equal to -1 otherwise. What is the expected value of $ d $ , if we choose vertices $ a $ and $ b $ from the sets uniformly at random?

Can you help Pasha to solve this problem?

The diameter of the component is the maximum distance among some pair of vertices in the component. The distance between two vertices is the minimum number of edges on some path between the two vertices.

Note that queries don't add edges to the initial forest.

## 说明/提示

In the first example the vertices $ 1 $ and $ 3 $ are in the same component, so the answer for the first query is -1. For the second query there are two options to add the edge: one option is to add the edge $ 1-2 $ , the other one is $ 2-3 $ . In both ways the resulting diameter is $ 2 $ , so the answer is $ 2 $ .

In the second example the answer for the first query is obviously -1. The answer for the second query is the average of three cases: for added edges $ 1-2 $ or $ 1-3 $ the diameter is $ 3 $ , and for added edge $ 1-4 $ the diameter is $ 2 $ . Thus, the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/80f05d9f9a5abbad800eeb11e2f309500aaccabe.png).

## 样例 #1

### 输入

```
3 1 2
1 3
3 1
2 3
```

### 输出

```
-1
2.0000000000
```

## 样例 #2

### 输入

```
5 2 3
2 4
4 3
4 2
4 1
2 5
```

### 输出

```
-1
2.6666666667
2.6666666667
```

# AI分析结果



# 算法分类
**树形结构，分治与预处理**

---

## 题解思路与核心难点

### 核心问题
给定森林中的两个连通块，求随机连接两块的任意两点后，新连通块的直径期望。直径可能为原两树直径的最大值，或新路径长度（两顶点最远距离之和+1）。

### 算法要点
1. **预处理每棵树的直径**：通过两次DFS/BFS找到树的直径端点。
2. **计算每个顶点的最远距离**：以直径端点为起点，计算每个顶点的最远距离（记为`mx[i]`）。
3. **前缀和优化**：将每棵树的顶点按`mx`排序，构建前缀和数组，用于快速计算满足条件的顶点对数。
4. **根号分治**：按树的大小分块（√n），小树直接暴力枚举，大树通过记忆化和预处理减少计算量。

### 解决难点
- **高效处理大量查询**：通过记忆化（map）存储已计算的树对结果。
- **快速统计贡献**：枚举小树的每个顶点，在大树的排序数组中使用二分查找确定满足`mx[a] + mx[b] +1 ≥ max_diam`的顶点对数目，利用前缀和快速求和。

---

## 题解评分（≥4星）

### 题解1：Graphcity（4.5星）
- **亮点**：清晰的根号分治策略，高效的前缀和与记忆化实现。
- **代码可读性**：结构清晰，注释合理，变量命名规范。
- **关键代码**：
```cpp
void dfs(int x,int f,int d) {
    mx[x] = max(mx[x], d);
    for(auto y:v[x]) if(y!=f) dfs(y,x,d+1);
}
// 预处理mx数组及前缀和
```

### 题解2：violin_wyl（4星）
- **亮点**：详细解释根号分治的时间复杂度，代码包含调试注释。
- **个人心得**：提到“巨坑”在于边界条件的处理，如`dx-mx[i]`可能为负数的情况。

### 题解3：i207M（4星）
- **亮点**：简洁的双指针优化，代码高度模块化。
- **关键优化**：直接存储每棵树的排序结果，避免重复排序。

---

## 最优思路提炼

### 关键步骤
1. **预处理阶段**：
   - 两次DFS确定每棵树的直径端点。
   - 计算每个顶点的最远距离`mx[i]`。
   - 按`mx`排序，构建前缀和数组`sum`和计数数组`cnt`。

2. **查询阶段**：
   - 若两树相同，返回-1。
   - 选择较小的树枚举顶点，在大树中二分查找满足条件的`mx[b]`下限。
   - 贡献分为两部分：超过原直径的部分和未超过的部分，分别用前缀和快速计算。

### 优化技巧
- **根号分治**：降低时间复杂度至O(n√n)。
- **记忆化查询**：避免重复计算相同树对的结果。

---

## 同类型题推荐
1. **CF 633F**：树的直径与子树查询。
2. **洛谷P3304**：直径必经边问题。
3. **洛谷P4211**：LCA与路径统计。

---

## 可视化与算法演示

### 动画设计
1. **树预处理动画**：
   - **步骤1**：用不同颜色标记每棵树，DFS遍历显示直径端点查找过程。
   - **步骤2**：动态绘制每个顶点的`mx`值，并以颜色深浅表示距离大小。

2. **查询处理动画**：
   - **步骤1**：高亮当前查询的两棵树，展示较小树的枚举顶点。
   - **步骤2**：在大树的排序数组中，用滑动指针动态显示二分查找过程，符合条件的区域用红色标记。

### 复古风格实现
- **像素画风**：树节点用8-bit方块表示，直径路径用闪烁线条标记。
- **音效设计**：
  - **点击查询**：播放短促“选择”音效。
  - **计算完成**：播放胜利音效（8-bit风格）。

---

## 代码片段（核心逻辑）

### 前缀和预处理
```cpp
vector<int> vec[N]; // 存储每棵树的mx值
vector<ll> sum[N];  // 前缀和数组
for (auto j : w[i]) {
    cnt[i][mx[j]]++;
    sum[i][mx[j]] += mx[j] + 1;
}
// 构建前缀和
for (int j=1; j<=siz[i]; j++) {
    cnt[i][j] += cnt[i][j-1];
    sum[i][j] += sum[i][j-1];
}
```

### 查询处理（二分查找）
```cpp
int mxd = max(diam[x], diam[y]);
ll res = 0;
for (int a : vec[x]) {
    int l = 0, r = vec[y].size()-1, pos = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (vec[y][mid] >= mxd - a -1) {
            pos = mid;
            r = mid -1;
        } else l = mid +1;
    }
    // 计算贡献...
}
```

---

## 个人心得摘录
> “在实现二分时，必须注意`mx[a]+mx[b]+1`与原直径的比较，否则会漏算贡献。”（i207M题解调试笔记）  
> “根号分治的复杂度分析需要细致，小树和大树的处理方式完全不同。”（violin_wyl题解总结）

---
处理用时：98.34秒