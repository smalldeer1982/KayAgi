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



### 算法分类
**树链剖分 + 线段树 + 分类讨论**

---

### 综合分析与结论

#### 核心思路
题目要求在换根操作下进行子树修改和查询，核心在于：
1. **不实际换根**，始终以原根（1号节点）为基准，通过分类讨论处理新根与操作节点的位置关系。
2. **LCA 动态计算**：换根后的 LCA 需要通过原树 LCA 和路径分析推导。
3. **子树范围判断**：利用 DFS 序的连续性，通过容斥原理处理根节点在子树中的情况。

#### 难点与解决方案
- **LCA 动态计算**：通过比较原树中三个 LCA（u-v, u-root, v-root）的深度，取最深者为新 LCA。
- **子树范围判断**：
  - 若根在子树外 → 直接操作原子树区间。
  - 若根即为操作子树根 → 操作全局。
  - 若根在子树内 → 全局操作后减去多余区间（容斥）。

#### 可视化设计思路
1. **动画流程**：
   - **换根**：高亮新根位置，展示原根到新根的路径。
   - **LCA 计算**：用不同颜色标出 u、v 到根的路径，动态显示三者 LCA 的比较过程。
   - **子树操作**：当根在子树内时，用半透明色块覆盖全局，再用反向色块剔除多余区间。
2. **复古像素风格**：
   - 树结构用 8 位网格表示，节点为 16x16 像素方块，路径用对比色线条连接。
   - 音效设计：操作确认时播放短促电子音，错误操作时播放低沉警示音。

---

### 题解清单（≥4星）

1. **Siyuan（⭐⭐⭐⭐⭐）**
   - **亮点**：逻辑清晰，代码简洁，利用 DFS 序 + 线段树直接处理子树范围。
   - **关键代码**：
     ```cpp
     void treeModify(int u, int x) {
         if (u == root) modify(1, 1, n, x);
         else if (isOutsideSubtree(root, u)) modifyRange(u, x);
         else modifyGlobalAndExclude(x, findExcludedSubtree(u));
     }
     ```

2. **Farkas_W（⭐⭐⭐⭐）**
   - **亮点**：详细图解换根后子树形态变化，分类讨论全面。
   - **个人心得**：强调通过画图辅助理解根在子树内的容斥逻辑。

3. **xunzhen（⭐⭐⭐⭐）**
   - **亮点**：结合树剖与倍增快速定位跳转节点，代码工业级优化。
   - **关键优化**：利用 `jump` 函数快速找到根在子树内的子节点。

---

### 核心代码实现
```cpp
// 线段树维护区间和（略）
// 分类处理子树操作
void update(int u, int x) {
    if (u == root) updateAll(x);
    else if (lca(u, root) != u) updateSubtree(u, x);
    else {
        int v = findChildInSubtree(u, root);
        updateAll(x);
        updateSubtree(v, -x);
    }
}

// 动态 LCA 计算
int getLCA(int u, int v, int root) {
    int l1 = lca(u, v), l2 = lca(u, root), l3 = lca(v, root);
    return maxDepth(l1, l2, l3); // 取深度最大者
}
```

---

### 同类型题与拓展
1. **洛谷 P3979【遥远的国度】**  
   换根后的子树最小值查询，需类似分类讨论。
2. **Codeforces 379F**  
   动态树结构中的 LCA 查询与子树操作。
3. **SPOJ QTREE5**  
   结合边权修改与最近白色节点查询，需灵活处理路径和子树。

---

### 复古像素动画实现（伪代码）
```javascript
class PixelTree {
    constructor() {
        this.canvas = document.getElementById('pixel-canvas');
        this.ctx = this.canvas.getContext('2d');
        this.nodes = {}; // 节点坐标与状态
    }

    drawNode(x, y, color) {
        this.ctx.fillStyle = color;
        this.ctx.fillRect(x*32, y*32, 30, 30); // 32x32网格
    }

    highlightPath(u, v) {
        // 用闪烁线条绘制u到v的路径
    }
}

// 音效触发
function playSound(effect) {
    const sfx = { success: [500, 0.3], error: [200, 0.5] };
    const oscillator = new OscillatorNode(ctx, { frequency: sfx[effect][0] });
    oscillator.connect(gain);
    oscillator.start();
}
```

---

### 总结
本题核心在于**动态逻辑推导**而非复杂数据结构，推荐优先掌握分类讨论与容斥原理。可视化时重点关注根变化对子树形态的影响，通过动画强化位置关系理解。

---
处理用时：72.77秒