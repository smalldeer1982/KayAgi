# 题目信息

# Equal Tree Sums

## 题目描述

You are given an undirected unrooted tree, i.e. a connected undirected graph without cycles.

You must assign a nonzero integer weight to each vertex so that the following is satisfied: if any vertex of the tree is removed, then each of the remaining connected components has the same sum of weights in its vertices.

## 说明/提示

In the first case, when removing vertex $ 1 $ all remaining connected components have sum $ 5 $ and when removing vertex $ 3 $ all remaining connected components have sum $ 2 $ . When removing other vertices, there is only one remaining connected component so all remaining connected components have the same sum.

## 样例 #1

### 输入

```
2
5
1 2
1 3
3 4
3 5
3
1 2
1 3```

### 输出

```
-3 5 1 2 2
1 1 1```

# AI分析结果



---

## 算法分类  
**树的性质应用**

---

## 综合分析与结论  

### 核心思路与难点  
所有题解均基于树的两个核心性质：  
1. **树是二分图**，可通过黑白染色/奇偶深度染色实现交替符号  
2. **每条边的度数贡献互为相反数**，使得整棵树权值和为0  

**关键构造**：  
- 黑节点权值 = 度数，白节点权值 = -度数  
- 删除任意节点后，每个连通块的和为 ±1（具体符号由被删节点颜色决定）  

**难点突破**：  
- 证明删除节点后各连通块和相等  
- 权值构造需满足整树和为0，同时每个边的贡献抵消  

---

## 题解清单 (≥4星)  

1. **I_am_Accepted**（⭐️⭐️⭐️⭐️）  
   - **亮点**：最短代码，直接给出构造方法  
   - **证明简化**：每条边贡献抵消 → 整树和为0  
   - **代码**：DFS染色，权值=度数×符号  

2. **Shunpower**（⭐️⭐️⭐️⭐️⭐️）  
   - **亮点**：详细数学推导，通过子树和递推证明构造正确性  
   - **核心公式**：  
     $$ a_x = (-1)^{dep_x} \cdot deg_x $$  
   - **实现**：DFS记录深度，权值=度数×符号  

3. **王熙文**（⭐️⭐️⭐️⭐️）  
   - **亮点**：强调父亲与儿子颜色交替的抵消机制  
   - **证明重点**：删除节点的度数对应连通块数量，各块和相等  

---

## 最优思路提炼  

### 核心技巧  
1. **二分图染色**：树天然是二分图，通过DFS/BFS交替染色  
2. **权值符号绑定度数**：符号由颜色或深度奇偶性决定，权值=±度数  
3. **全局和为0**：每条边两端权值贡献相消  

### 代码实现片段  
```cpp
void dfs(int u, int fa, int color_sign) {
    // 染色并赋值
    weight[u] = (color_sign == 1) ? degree[u] : -degree[u];
    for (auto v : tree[u]) {
        if (v != fa) dfs(v, u, -color_sign);
    }
}

// 调用入口
dfs(root, -1, 1); // root的初始符号为1
```

---

## 可视化与算法演示  

### 动画设计  
1. **树结构绘制**：  
   - 节点以像素方块表示，颜色区分黑白节点  
   - 边用直线连接，标注度数  

2. **染色过程**：  
   - **步进动画**：DFS遍历时，当前节点高亮闪烁，染色后显示权值  
   - **颜色交替**：子节点颜色自动取反，权值符号同步更新  

3. **删除验证**：  
   - 点击任意节点触发删除  
   - 连通块用不同颜色区域标记，显示每个块的权值和  

### 复古游戏化效果  
- **8位像素风格**：  
  - 节点：黑色（#000000）与白色（#FFFFFF）交替  
  - 背景：深蓝（#000033），边线：灰色（#888888）  
- **音效**：  
  - 染色成功：短促“滴”声（440Hz方波）  
  - 删除验证：成功时播放“胜利”音效（C大调和弦）  
- **自动演示模式**：  
  - 按空格键切换自动/手动模式  
  - AI自动执行DFS染色，速度可调（快/中/慢）  

---

## 类似题目推荐  
1. **P1352 没有上司的舞会**（树形DP，交替选择）  
2. **P3386 【模板】二分图匹配**（二分图性质应用）  
3. **P1040 加分二叉树**（树结构构造与性质）  

---

## 个人心得摘录  
- **调试教训**：初始未考虑根节点特殊处理，导致权值和不为0  
- **顿悟时刻**：发现树作为二分图的天然交替性可直接绑定权值符号  

---

## 可视化代码片段（Canvas动画）  
```javascript
// 绘制节点（8位风格）
function drawNode(x, y, color, value) {
    ctx.fillStyle = color;
    ctx.fillRect(x-15, y-15, 30, 30); // 像素方块
    ctx.fillStyle = "#FF0000";
    ctx.font = "8px Arial";
    ctx.fillText(value, x-8, y+5); // 显示权值
}

// DFS动画核心
function animateDFS(node, parent, colorSign) {
    setTimeout(() => {
        highlightNode(node); // 高亮当前节点
        drawNode(node.x, node.y, (colorSign === 1) ? "black" : "white", node.degree * colorSign);
        node.children.forEach(child => {
            if (child !== parent) {
                animateDFS(child, node, -colorSign);
            }
        });
    }, currentDelay);
    currentDelay += 500; // 步进延迟
}
```

---
处理用时：69.00秒