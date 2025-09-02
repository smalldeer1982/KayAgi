# 题目信息

# Iris's Full Binary Tree

## 题目描述

Iris likes full binary trees.

Let's define the depth of a rooted tree as the maximum number of vertices on the simple paths from some vertex to the root. A full binary tree of depth $ d $ is a binary tree of depth $ d $ with exactly $ 2^d - 1 $ vertices.

Iris calls a tree a  $ d $ -binary tree if some vertices and edges can be added to it to make it a full binary tree of depth $ d $ . Note that any vertex can be chosen as the root of a full binary tree.

Since performing operations on large trees is difficult, she defines the binary depth of a tree as the minimum $ d $ satisfying that the tree is $ d $ -binary. Specifically, if there is no integer $ d \ge 1 $ such that the tree is $ d $ -binary, the binary depth of the tree is $ -1 $ .

Iris now has a tree consisting of only vertex $ 1 $ . She wants to add $ n - 1 $ more vertices to form a larger tree. She will add the vertices one by one. When she adds vertex $ i $ ( $ 2 \leq i \leq n $ ), she'll give you an integer $ p_i $ ( $ 1 \leq p_i < i $ ), and add a new edge connecting vertices $ i $ and $ p_i $ .

Iris wants to ask you the binary depth of the tree formed by the first $ i $ vertices for each $ 1 \le i \le n $ . Can you tell her the answer?

## 说明/提示

In the first test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/7f900739a2145e9bd80715ede4260b35ba51b9fd.png)- The tree consisting of the vertex $ 1 $ has the binary depth $ 1 $ (the tree itself is a full binary tree of depth $ 1 $ ).
- The tree consisting of the vertices $ 1 $ and $ 2 $ has the binary depth $ 2 $ (we can add the vertex $ 3 $ to make it a full binary tree of depth $ 2 $ ).
- The tree consisting of the vertices $ 1 $ , $ 2 $ and $ 3 $ has the binary depth $ 2 $ (the tree itself is a full binary tree of depth $ 2 $ ).

In the second test case, the formed full binary tree after adding some vertices to the tree consisting of $ n $ vertices is shown below (bolded vertices are added):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/90faca99e1781d73f69b5b60a32aa2a2da38a68c.png)The depth of the formed full binary tree is $ 4 $ .

In the fifth test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/2c0d039efae462812828b42368688f46ffc8b41e.png)It can be proved that Iris can't form any full binary tree by adding vertices and edges, so the binary depth is $ -1 $ .

## 样例 #1

### 输入

```
7
3
1 1
6
1 2 3 4 5
7
1 1 3 2 5 1
10
1 1 2 1 4 2 4 5 8
10
1 1 3 1 3 2 2 2 6
20
1 1 2 2 4 4 5 5 7 6 8 6 11 14 11 8 13 13 12
25
1 1 3 3 1 5 4 4 6 8 11 12 8 7 11 13 7 13 15 6 19 14 10 23```

### 输出

```
1 2 2 
1 2 2 3 3 4 
1 2 2 3 3 4 4 
1 2 2 3 3 3 4 4 5 5 
1 2 2 3 3 4 4 4 -1 -1 
1 2 2 3 3 4 4 4 4 5 5 5 5 6 6 6 6 6 6 7 
1 2 2 3 3 4 4 4 4 5 5 6 6 6 6 6 7 7 7 7 7 8 8 8 8```

# AI分析结果



---

## 唯一算法分类
**树的动态处理与高级数据结构**

---

## 综合分析与结论
### 核心思路与难点
题目要求动态维护树的二进制深度，关键在于以下两点：
1. **根节点约束**：满足度数 ≤2 的节点才能作为满二叉树的根。
2. **最远距离优化**：对于每个可能的根，其深度为到最远节点的距离，需动态维护最小值。

**核心算法流程**：
1. **动态维护直径**：每次添加节点时更新树的直径端点（利用引理：新直径端点必为原直径端点或新节点）。
2. **中心点维护**：直径中心决定了距离变化的范围，通过 DFS 序将子树映射到线段树区间，实现区间加减操作。
3. **线段树优化**：维护每个点到当前中心的最远距离，并在度数超过限制时标记为无效（设为极大值）。

**可视化设计**：
- **动画效果**：以像素风格展示树的生长过程，新节点用闪烁方块标记，直径端点用红色/蓝色高亮，中心点用黄色方块。
- **线段树操作**：右侧画布显示线段树结构，更新区间时用绿色覆盖，无效节点用灰色标记。
- **音效提示**：添加节点时播放“滴”声，直径扩展时播放上升音阶，无效操作（度数≥3）播放警告音。

---

## 题解清单 (≥4星)
### 1. Conan15 的题解（★★★★☆）
- **亮点**：详细维护直径中心二元组 `(a,b)`，通过移动中心调整距离，代码注释清晰。
- **关键代码**：`move` 函数实现中心点移动时的区间加减，线段树动态维护各点距离。

### 2. DaiRuiChen007 的题解（★★★★☆）
- **亮点**：直接维护直径端点 `u,v` 及其对应中心 `x,y`，利用 `nxt` 函数高效计算子树范围。
- **关键优化**：通过 `LCA` 和 `dis` 快速计算距离，代码结构简洁高效。

---

## 最优思路与技巧提炼
### 关键技巧
1. **直径动态维护**：利用每次添加节点后的距离比较，快速判断是否需要扩展直径。
2. **DFS 序区间映射**：将子树操作转化为线段树上的区间加减，实现 O(1) 范围操作。
3. **度数剪枝**：度数≥3 的节点直接标记为无效，避免后续计算。

### 代码实现片段（DaiRuiChen007 题解）
```cpp
void solve() {
    // 初始化线段树与直径端点
    T.init(), T.set(1,0);
    u = v = x = y = 1;
    for (int p=2; p<=n; ++p) {
        // 处理度数约束
        if (deg[fa[p]] >3) { /* 标记无效 */ }
        // 更新线段树中的距离
        T.set(L[p], min(dis(p,x), dis(p,y)));
        // 调整直径端点与中心
        if (dis(u,p) > dis(u,v)) { /* 移动端点 */ }
        // 输出线段树全局最小值
        cout << T.tr[1] + (dis(u,v)+1)/2 +1 << " ";
    }
}
```

---

## 同类型题推荐
1. **P1099 [NOIP2007 提高组] 树网的核**（树的直径与中心性质）
2. **P3304 [SDOI2013] 直径**（动态维护直径的扩展问题）
3. **P4219 [BJOI2014] 大融合**（动态树操作与子树维护）

---

## 可视化与算法演示
### 动画方案设计
- **像素风格树**：节点显示为 16x16 像素方块，边用直线连接，当前操作节点闪烁。
- **线段树面板**：右侧网格显示线段树节点值，颜色深浅表示距离大小，无效节点灰显。
- **交互控制**：支持暂停/继续、单步执行，速度调节滑块（1x~10x）。

### 关键帧示例
1. **添加节点**：新节点亮绿色，父节点度数增加，若度数≥3则变红。
2. **直径扩展**：旧端点变暗，新端点高亮，线段树对应区间绿色闪动。
3. **中心移动**：黄色中心点平滑移动到新位置，触发区间加减操作。

---

**注**：以上设计可在 Web 端用 Canvas + Web Audio API 实现，保持轻量化与交互性。

---
处理用时：74.02秒