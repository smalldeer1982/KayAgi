# 题目信息

# White-Black Balanced Subtrees

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root is vertex $ 1 $ . There is also a string $ s $ denoting the color of each vertex: if $ s_i = \texttt{B} $ , then vertex $ i $ is black, and if $ s_i = \texttt{W} $ , then vertex $ i $ is white.

A subtree of the tree is called balanced if the number of white vertices equals the number of black vertices. Count the number of balanced subtrees.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. In this problem, all trees have root $ 1 $ .

The tree is specified by an array of parents $ a_2, \dots, a_n $ containing $ n-1 $ numbers: $ a_i $ is the parent of the vertex with the number $ i $ for all $ i = 2, \dots, n $ . The parent of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root.

The subtree of a vertex $ u $ is the set of all vertices that pass through $ u $ on a simple path to the root. For example, in the picture below, $ 7 $ is in the subtree of $ 3 $ because the simple path $ 7 \to 5 \to 3 \to 1 $ passes through $ 3 $ . Note that a vertex is included in its subtree, and the subtree of the root is the entire tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) The picture shows the tree for $ n=7 $ , $ a=[1,1,2,3,3,5] $ , and $ s=\texttt{WBBWWBW} $ . The subtree at the vertex $ 3 $ is balanced.

## 说明/提示

The first test case is pictured in the statement. Only the subtrees at vertices $ 2 $ and $ 3 $ are balanced.

In the second test case, only the subtree at vertex $ 1 $ is balanced.

In the third test case, only the subtrees at vertices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are balanced.

## 样例 #1

### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW```

### 输出

```
2
1
4```

# AI分析结果



---

**算法分类**：DFS

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
所有题解均采用 **DFS后序遍历**，自底向上统计每个子树的黑白节点数量，并判断是否平衡。关键在于递归时合并子节点的统计结果，并在回溯时更新当前节点的状态。

#### **算法要点**
1. **树结构的构建**：通过父节点数组建立邻接表表示的树结构。
2. **DFS遍历**：从根节点开始递归访问子节点，后序回溯时累加子树数据。
3. **状态表示**：用 `(black, white)` 计数或数值（黑+1，白-1）表示子树的平衡状态。
4. **平衡判断**：检查当前节点的黑白数量是否相等或总和是否为0。

#### **解决难点**
- **树结构处理**：需正确构建单向树（父→子），避免双向边导致错误遍历。
- **多组数据初始化**：每组测试需清空邻接表和统计数组，防止数据残留。
- **递归合并逻辑**：确保子节点统计结果正确传递到父节点，无重复或遗漏。

---

### **题解评分 (≥4星)**

1. **a1co0av5ce5az1cz0ap_ (5星)**  
   - **亮点**：代码最简洁，将颜色映射为数值（黑1，白-1），仅需判断总和是否为0。  
   - **代码可读性**：变量命名清晰，无冗余操作。  
   - **优化点**：减少变量数目，简化判断逻辑。

2. **Withers (4星)**  
   - **亮点**：显式维护 `struct node` 存储黑白计数，逻辑直观。  
   - **实践性**：适合初学者理解子树状态的合并过程。  
   - **缺点**：代码结构稍显冗长。

3. **5k_sync_closer (4星)**  
   - **亮点**：使用全局数组 `s[x][0/1]` 存储状态，代码紧凑。  
   - **优化点**：合并父节点统计时直接累加，无需额外条件判断。

---

### **最优思路或技巧提炼**

1. **数值映射法**：将颜色转换为数值（黑+1，白-1），总和为0即平衡。**优势**：减少变量维护，简化判断逻辑。
2. **后序遍历合并**：DFS返回时累加子节点的统计结果，确保父节点状态正确。
3. **邻接表优化**：仅构建父→子的单向边，避免冗余遍历。

---

### **同类型题或类似算法套路**

- **子树统计问题**：如统计子树节点数、子树和、子树最大值等，均可用DFS后序遍历合并子节点结果。
- **树形DP**：如[P1271 聚会的快乐](https://www.luogu.com.cn/problem/P1271)（需同时考虑选/不选节点的状态传递）。

---

### **推荐相似题目**

1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)（区间覆盖统计，类似子树覆盖）
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)（树形DP，状态合并）
3. [P3379 最近公共祖先](https://www.luogu.com.cn/problem/P3379)（LCA问题，DFS遍历应用）

---

### **个人心得摘录**

- **调试教训**：  
  > "多测不清空，爆零两行泪。每次需重置邻接表和统计数组，否则残留数据导致错误。" —— a1co0av5ce5az1cz0ap_
- **思维突破**：  
  > "将颜色转为数值，问题转化为求和为零，简化代码逻辑。" —— Jadebo1

---

### **可视化与算法演示**

#### **动画方案**
1. **树形结构展示**：用Canvas绘制树，根节点在顶部，子节点按层次展开。
2. **DFS过程高亮**：
   - **当前节点**：红色边框标记。
   - **访问顺序**：递归进入子节点时显示蓝色箭头，回溯时显示绿色箭头。
3. **数值更新**：每个节点旁动态显示当前黑白计数或数值总和，平衡时闪烁黄色。
4. **音效反馈**：访问节点时播放“滴”声，平衡时播放“叮”声。

#### **复古游戏化设计**
- **像素风格**：节点用16x16像素方块表示，黑色节点为■，白色为□，平衡时变为★。
- **自动演示**：按DFS顺序逐步访问节点，模拟红白机回合制风格。
- **积分系统**：每发现一个平衡子树得10分，显示在右上角。

---

### **核心代码片段**

#### **数值映射法（a1co0av5ce5az1cz0ap_）**
```cpp
int co(int rt) {
    int sum = color[rt];
    for (int child : v[rt]) sum += co(child);
    if (sum == 0) ans++;
    return sum;
}
```

#### **显式计数法（Withers）**
```cpp
void dfs(int u, int fa) {
    for (int child : g[u]) {
        dfs(child, u);
        k[u].b += k[child].b;
        k[u].w += k[child].w;
    }
    if (k[u].b == k[u].w) ans++;
}
```

---

### **可视化代码示例（JavaScript）**

```javascript
// 绘制树结构（Canvas）
function drawTree(nodes) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    nodes.forEach(node => {
        drawNode(node.x, node.y, node.color, node.balanced);
        node.children.forEach(child => drawEdge(node, child));
    });
}

// DFS自动演示
async function autoDFS(node) {
    node.highlight = true;
    drawTree(nodes);
    await sleep(500);
    for (const child of node.children) {
        await autoDFS(child);
        node.b += child.b;
        node.w += child.w;
    }
    if (node.b === node.w) score += 10;
    node.highlight = false;
    node.balanced = (node.b === node.w);
    drawTree(nodes);
    playSound('ding');
}
```

---
处理用时：73.35秒