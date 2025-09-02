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

**算法分类**  
树结构、动态直径维护、线段树区间操作

---

## **题解思路与核心难点**

### **核心思路**
题目要求动态维护树的二进制深度，即每次添加节点后，求最小的d使得当前树是d-binary树。关键点在于：
1. **动态维护直径**：每次插入新节点后，更新树的直径端点，并调整中心。
2. **度数约束**：根节点度数≤2，其他节点度数≤3，否则无法构成二叉树。
3. **线段树优化**：通过DFS序将子树映射为区间，用线段树维护每个点到中心的距离，并快速查询最小值。

### **解决难点**
1. **动态直径维护**：插入新节点时，直径可能扩展，需重新计算端点。根据引理，直径端点只能来自原有端点或新节点。
2. **中心调整**：当直径变化时，中心可能移动（在点或边上）。通过线段树的区间加减操作调整子树内的距离。
3. **度数处理**：实时检查节点的度数，若度数超过约束，则在线段树中将该节点标记为无效（设为极大值）。

---

## **题解评分**

### **DaiRuiChen007的题解（★★★★☆）**
- **思路清晰**：明确将问题转化为维护离中心最近的2度点，直接点出线段树维护的核心。
- **代码简洁**：使用轻量级线段树和LCA优化，逻辑紧凑。
- **优化到位**：通过DFS序和区间操作高效处理子树更新。

### **Conan15的题解（★★★★☆）**
- **详细注释**：代码中详细注释了中心移动和线段树操作，便于理解。
- **动态调整逻辑**：明确维护直径二元组（a,b）和半径r，适合动态扩展。
- **边界处理完整**：对度数≥4的情况直接标记为-1，保证正确性。

### **irris的题解（★★★☆☆）**
- **理论分析深入**：通过引理和结论系统推导，但代码实现较复杂。
- **Top Tree未实现**：思路中提及Top Tree但未在代码中使用，实践性稍弱。

---

## **最优思路提炼**
1. **动态直径维护**：每次插入节点时，检查其到当前直径端点的距离，更新直径端点。
   ```cpp
   if (dis(u, p) > dis(u, v)) v = p;  // 更新直径端点
   ```
2. **中心移动与区间操作**：通过DFS序将子树映射为区间，线段树区间加减调整距离。
   ```cpp
   T.add(1, L[x], R[x], 1);  // 对子树x内的所有节点距离+1
   ```
3. **度数约束处理**：实时检查度数，若度数≥3则在线段树中标记为无效。
   ```cpp
   if (deg[fa[p]] == 3) T.set(L[fa[p]], inf);
   ```

---

## **类似题目推荐**
1. **P1099 [NOIP2007 提高组] 树网的核**：树的直径与中心相关。
2. **P3304 [SDOI2013] 直径**：动态维护树的直径性质。
3. **P4219 [BJOI2014] 大融合**：动态树结构维护与子树操作。

---

## **可视化设计**

### **动画方案**
- **像素风格**：用16色块表示树节点，直径端点用红色高亮，中心点用绿色闪烁。
- **线段树更新**：在Canvas右侧绘制线段树，每次区间加减时对应子树区间颜色渐变。
- **步进控制**：支持单步执行插入节点、更新直径、调整中心，速度可调节。

### **音效设计**
- **插入节点**：短促“滴”声。
- **直径更新**：低音“咚”声。
- **无效操作（度数≥4）**：长鸣“哔”声。

---

## **代码片段（核心逻辑）**
```cpp
// 线段树维护子树区间加减（DaiRuiChen007题解）
void add(int ul, int ur, int k, int l=1, int r=n, int p=1) {
    if (ul > ur) return;
    if (ul <= l && r <= ur) return adt(p, k);
    int mid = (l + r) >> 1; psd(p);
    if (ul <= mid) add(ul, ur, k, l, mid, p<<1);
    if (mid < ur) add(ul, ur, k, mid+1, r, p<<1|1);
    psu(p);
}

// 动态调整中心（Conan15题解）
void move(int &a, int x) {
    if (lca(a, x) == a) { // x在a的子树内
        tr.add(1, 1, n, 1); // 全局距离+1
        a = getk(x, dep[x] - dep[a] - 1); // a下移
        tr.add(1, dfn[a], dfn[a]+sz[a]-1, -1); // 子树距离-1
    } else {
        tr.add(1, dfn[a], dfn[a]+sz[a]-1, 1); // 子树距离+1
        a = p[a]; // a上移
    }
}
```

---

**总结**  
通过动态维护树的直径和中心，结合线段树高效处理子树区间操作，是解决本题的核心。关键优化点在于将树结构映射为线性区间，并利用度数约束快速排除无效节点。

---
处理用时：70.42秒