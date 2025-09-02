# 题目信息

# Jamie and Tree

## 题目描述

To your surprise, Jamie is the final boss! Ehehehe.

Jamie has given you a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Initially, the root of the tree is the vertex with number $ 1 $ . Also, each vertex has a value on it.

Jamie also gives you three types of queries on the tree:

 $ 1\ v $ — Change the tree's root to vertex with number $ v $ .

 $ 2\ u\ v\ x $ — For each vertex in the subtree of smallest size that contains $ u $ and $ v $ , add $ x $ to its value.

 $ 3\ v $ — Find sum of values of vertices in the subtree of vertex with number $ v $ .

A subtree of vertex $ v $ is a set of vertices such that $ v $ lies on shortest path from this vertex to root of the tree. Pay attention that subtree of a vertex can change after changing the tree's root.

Show your strength in programming to Jamie by performing the queries accurately!

## 说明/提示

The following picture shows how the tree varies after the queries in the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916E/9b296178af98e90dbbac00c785fb2ed88745e7bd.png)

## 样例 #1

### 输入

```
6 7
1 4 2 8 5 7
1 2
3 1
4 3
4 5
3 6
3 1
2 4 6 3
3 4
1 6
2 2 4 -5
1 4
3 3
```

### 输出

```
27
19
5
```

## 样例 #2

### 输入

```
4 6
4 3 5 6
1 2
2 3
3 4
3 1
1 3
2 2 4 3
1 1
2 2 4 -3
3 1
```

### 输出

```
18
21
```

# AI分析结果



# 算法分类
树链剖分（树剖） + 线段树 + 分类讨论

---

## 核心思路与难点分析

### 核心思路
1. **预处理树结构**：以初始根（1号节点）进行树链剖分，预处理DFS序和子树区间。
2. **线段树维护**：用线段树维护DFS序区间，支持区间加值与求和。
3. **换根分类讨论**：
   - **操作子树时**，根据当前根的位置分为三种情况：
     - 若根是当前节点 → 操作整个树
     - 若根在子树外 → 直接操作原子树区间
     - 若根在子树内 → 操作全树后扣除根所在分支的子树区间
4. **动态LCA计算**：换根后求LCA需比较原LCA和根路径上的LCA，取最深节点。

### 解决难点
1. **子树范围动态变化**：通过分类讨论和容斥原理调整操作区间。
2. **高效处理换根**：不重构树结构，仅通过逻辑判断动态计算子树范围。
3. **LCA的快速计算**：利用倍增法预处理，结合树剖快速跳转。

---

## 最优题解 (Siyuan, 4⭐️)

### 题解亮点
1. **清晰的分类逻辑**，将子树操作分为三种情况处理。
2. **高效的LCA计算**，通过三次LCA比较得到正确结果。
3. **代码结构清晰**，将核心逻辑封装为`treeModify`和`treeQuery`函数。

### 关键代码片段
```cpp
int getlca(int u, int v, int p) {
    int x = lca(u, v), y = lca(u, p), z = lca(v, p);
    if (dep[y] > dep[x]) x = y;
    if (dep[z] > dep[x]) x = z;
    return x;
}

void treeModify(int u, int k) {
    if (u == root) modify(1, n, 1, k);
    else if (dfn[root] < dfn[u] || dfn[root] > dfn[u] + sz[u] - 1) {
        modify(dfn[u], dfn[u] + sz[u] - 1, 1, k);
    } else {
        int son = jump(root, dep[root] - dep[u] - 1);
        modify(1, n, 1, k);
        modify(dfn[son], dfn[son] + sz[son] - 1, 1, -k);
    }
}
```

---

## 可视化算法设计

### 动画演示方案
1. **树结构展示**：用Canvas绘制树形结构，节点按DFS序排列。
2. **动态高亮**：
   - 换根时，新根节点闪烁黄色。
   - 修改/查询时，当前操作区间用红色覆盖层标记。
3. **操作演示**：
   - **情况1**（根即当前节点）：全树节点短暂变绿。
   - **情况2**（根在子树外）：原子树区间快速闪烁。
   - **情况3**（根在子树内）：先全树变绿，再红色闪烁扣除区域。

### 复古像素风格实现
```javascript
// 示例：8位风格树节点渲染
class PixelTree {
    constructor(canvas) {
        this.ctx = canvas.getContext('2d');
        this.ctx.imageSmoothingEnabled = false;
        this.colors = ['#2C2C2C', '#7F7F7F', '#FFD700', '#FF0000'];
    }
    
    drawNode(x, y, colorIdx) {
        this.ctx.fillStyle = this.colors[colorIdx];
        this.ctx.fillRect(x*16, y*16, 14, 14); // 16x16像素块
    }
    
    highlightSubtree(root, node) {
        // 实现子树高亮动画
    }
}
```

---

## 同类型题目推荐
1. **P3979 遥远的国度**：换根操作+子树最值查询
2. **P2146 [NOI2015] 软件包管理器**：树剖+子树/路径操作
3. **P3384 【模板】树链剖分**：树剖基础练习

---

## 核心算法流程总结
1. **预处理阶段**：树剖获取DFS序和子树区间。
2. **换根处理**：
   - 记录当前根`root`，不实际修改树结构。
3. **子树操作**：
   - 判断根与目标节点的位置关系。
   - 使用线段树对相应区间进行加/求和操作。
4. **LCA计算**：动态比较三种LCA取最深。

该方案时间复杂度为$O(n \log n + q \log n)$，空间复杂度$O(n)$。

---
处理用时：75.17秒