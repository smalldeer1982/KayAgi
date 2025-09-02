# 题目信息

# Construct the Binary Tree

## 题目描述

You are given two integers $ n $ and $ d $ . You need to construct a rooted binary tree consisting of $ n $ vertices with a root at the vertex $ 1 $ and the sum of depths of all vertices equals to $ d $ .

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. A parent of a vertex $ v $ is the last different from $ v $ vertex on the path from the root to the vertex $ v $ . The depth of the vertex $ v $ is the length of the path from the root to the vertex $ v $ . Children of vertex $ v $ are all vertices for which $ v $ is the parent. The binary tree is such a tree that no vertex has more than $ 2 $ children.

You have to answer $ t $ independent test cases.

## 说明/提示

Pictures corresponding to the first and the second test cases of the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/514e626aa001052fb71d69f413a53a8e6f0cb5f0.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/6407c12a699d89084b087667ed6f21f3aeed074d.png)

## 样例 #1

### 输入

```
3
5 7
10 19
10 18```

### 输出

```
YES
1 2 1 3 
YES
1 2 3 3 9 9 2 1 6 
NO```

# AI分析结果



### 综合分析与结论

**题目核心**：构造一棵 $n$ 节点的二叉树，使得所有节点的深度和为 $d$。关键在于判断 $d$ 是否在完全二叉树（最小深度和）和链（最大深度和）之间，并通过贪心策略调整初始结构。

**贪心策略核心**：
1. **初始构造**：从完全二叉树（最小深度和）或链（最大深度和）出发。
2. **调整过程**：每次选择能带来最大深度变化的节点（如最底层或编号最大的节点），通过调整其父节点位置，逐步逼近目标 $d$。
3. **数据结构**：维护链的末端、每层节点数或优先队列，快速找到可调整的节点。

**解决难点**：
- 如何高效计算调整后的深度和变化。
- 如何确保调整过程覆盖所有可能的 $d$ 值。
- 避免调整过程中出现无效操作（如破坏二叉树结构）。

---

### 题解评分（≥4星）

1. **万弘的题解（5星）**
   - **亮点**：线性时间复杂度，从完全二叉树出发，通过链式调整快速逼近目标。代码简洁高效，直观体现贪心策略。
   - **关键代码**：
     ```cpp
     for (ll i = n; i; --i) {
         if ((i & (i - 1)) == 0) continue;
         sum_dep -= dep[pos] + 1 - dep[i];
         if (sum_dep <= 0) {
             while (sum_dep) pos = fa[pos], ++sum_dep;
             fa[i] = pos; break;
         }
         fa[i] = pos, dep[i] = dep[pos] + 1, pos = i;
     }
     ```

2. **CCA的题解（4星）**
   - **亮点**：分层维护节点数，通过移动节点逐步增加深度和。代码结构清晰，可读性强。
   - **关键逻辑**：
     ```cpp
     while (sum < d) {
         for (int i = Max; i >= 0; i--) {
             if (cnt[i] >= 2 && cnt[i + 1] < (cnt[i] - 1) * 2) {
                 // 移动节点到下一层
             }
         }
     }
     ```

3. **syksykCCC的题解（4星）**
   - **亮点**：维护每层节点数，通过调整层间节点分布，逐步逼近目标。代码可读性好，逻辑明确。
   - **关键代码**：
     ```cpp
     while (sumdep < d) {
         for (int i = mxdep; ~i; i--) {
             if (node[i].size() >= 2 && node[i + 1].size() < node[i].size() * 2 - 2) {
                 // 移动节点并更新深度和
             }
         }
     }
     ```

---

### 最优思路与技巧提炼

1. **贪心选择依据**：每次调整带来最大深度变化（如移动最底层或编号最大的节点）。
2. **初始化策略**：从完全二叉树（最小和）或链（最大和）开始，确保调整方向正确。
3. **数据结构优化**：
   - 维护链的末端（万弘）或每层节点数（CCA），快速定位调整位置。
   - 使用优先队列（Iam1789）管理深度最大的节点，确保每次操作最优。
4. **边界处理**：通过计算最小/最大深度和预先排除无解情况。

---

### 同类型题目与算法套路

1. **算法套路**：
   - **调整法**：从极端情况出发，通过局部调整逼近目标。
   - **分层管理**：维护每层节点数，优化调整过程。
   - **优先队列**：快速获取最优调整节点。

2. **推荐题目**：
   - **P1090 合并果子**：贪心选择最小代价合并。
   - **P1230 智力大冲浪**：按截止时间贪心安排任务。
   - **P5019 铺设道路**：贪心填坑，调整相邻深度。

---

### 可视化与算法演示设计

**核心贪心过程动画设计**：
1. **像素风格展示**：
   - 用不同颜色方块表示节点（绿色：链上节点，蓝色：普通节点）。
   - 高亮当前调整的节点，显示其父节点变化。
2. **交互功能**：
   - **步进控制**：单步执行调整，显示深度和变化。
   - **速度调节**：调整动画播放速度，观察贪心策略的逐步推进。
3. **音效提示**：
   - 调整成功时播放“升级”音效，失败时播放“错误”音效。
   - 背景音乐采用 8-bit 风格循环曲目。

**关键动画步骤**：
1. 初始完全二叉树的像素化展示。
2. 从最底层节点开始，逐步将其移动到链的末端。
3. 每次移动后更新深度和，颜色标记链的延伸部分。
4. 目标达成时，显示成功动画和最终树结构。

---

### 代码片段（万弘题解核心逻辑）

```cpp
for (ll i = n; i; --i) {
    if ((i & (i - 1)) == 0) continue; // 跳过链上节点
    sum_dep -= (dep[pos] + 1 - dep[i]); // 计算调整后的深度变化
    if (sum_dep <= 0) {
        while (sum_dep) pos = fa[pos], ++sum_dep; // 回溯到合适的位置
        fa[i] = pos; break; // 更新父节点
    }
    fa[i] = pos; // 挂到链的末端
    dep[i] = dep[pos] + 1;
    pos = i; // 更新链末端
}
```

---

### 个人心得摘录

> “构造题的核心是找到极端情况与调整策略。从完全二叉树到链的调整，每一步必须保证贪心选择的最优性，否则会陷入无效操作。” —— CCA

---

**总结**：通过贪心策略快速调整初始结构，结合高效数据结构和边界处理，是解决此类构造问题的通用方法。

---
处理用时：91.28秒