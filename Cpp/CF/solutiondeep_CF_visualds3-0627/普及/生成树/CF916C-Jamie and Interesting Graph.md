# 题目信息

# Jamie and Interesting Graph

## 题目描述

Jamie has recently found undirected weighted graphs with the following properties very interesting:

- The graph is connected and contains exactly $ n $ vertices and $ m $ edges.
- All edge weights are integers and are in range $ [1,10^{9}] $ inclusive.
- The length of shortest path from $ 1 $ to $ n $ is a prime number.
- The sum of edges' weights in the minimum spanning tree (MST) of the graph is a prime number.
- The graph contains no loops or multi-edges.

If you are not familiar with some terms from the statement you can find definitions of them in notes section.

Help Jamie construct any graph with given number of vertices and edges that is interesting!



## 说明/提示

The graph of sample 1: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) Shortest path sequence: $ {1,2,3,4} $ . MST edges are marked with an asterisk (\*).

Definition of terms used in the problem statement:

A shortest path in an undirected graph is a sequence of vertices $ (v_{1},v_{2},...\ ,v_{k}) $ such that $ v_{i} $ is adjacent to $ v_{i+1} $ $ 1<=i<k $ and the sum of weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) is minimized where $ w(i,j) $ is the edge weight between $ i $ and $ j $ . ([https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem))

A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself. ([https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number))

A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight. ([https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree))

[https://en.wikipedia.org/wiki/Multiple\_edges](https://en.wikipedia.org/wiki/Multiple_edges)

## 样例 #1

### 输入

```
4 4
```

### 输出

```
7 7
1 2 3
2 3 2
3 4 2
2 4 4
```

## 样例 #2

### 输入

```
5 4
```

### 输出

```
7 13
1 2 2
1 3 4
1 4 3
4 5 4
```

# AI分析结果



---

### **算法分类**
构造

---

### **题解思路、算法要点与解决难点**

**核心思路**：构造一条从 1 到 n 的链，使其同时成为最短路和最小生成树，边权和为质数，其余边以极大值填充。

**算法要点**：
1. **质数选择**：选取一个足够大的质数（如 1e5+3），保证链的总边权和为质数。
2. **链构造**：
   - 前 n-2 条边权为 1。
   - 最后一条边权调整为 `p - (n-2)`，使总和为质数 p。
3. **剩余边处理**：添加任意不重复的边，权值设为极大值（如 1e9），避免影响最短路和 MST。

**解决难点**：
- 统一最短路径和 MST 的结构。
- 动态生成不重复的剩余边。

---

### **题解评分 (≥4星)**

1. **Fuko_Ibuki (★★★★★)**  
   思路清晰，代码简洁。核心逻辑仅 10 行，通过固定质数和大边权构造，剩余边用双指针填充。  
   **亮点**：高效处理剩余边，代码易读。

2. **0xFF (★★★★☆)**  
   类似思路，但代码稍显冗余。优点在于详细注释和质数选择解释。  
   **亮点**：注释详细，适合教学。

3. **yimuhua (★★★★☆)**  
   代码简洁，核心逻辑与最优解一致。但变量命名不够直观。  
   **亮点**：极简实现，适合快速理解。

---

### **最优思路或技巧提炼**

1. **双目标统一**：将最短路和 MST 合并为同一条链，简化问题。
2. **质数构造法**：通过调整单一边的权值，使总边权和为质数。
3. **极大边填充**：剩余边设为极大值，避免干扰核心结构。

---

### **同类型题或类似算法套路**

- **通用构造法**：通过特定结构（链、星型）满足多目标条件。
- **质数边权和**：在构造图中强制边权和为质数。
- **极值填充法**：用极大/极小值控制图的次要结构。

---

### **推荐题目**
1. **CF1003E**：构造指定直径的树。
2. **CF1176E**：构造满足特定连通性的图。
3. **洛谷 P1119**：构造边权符合条件的最短路图。

---

### **可视化与算法演示**

**核心动画设计**：
1. **链构造阶段**：  
   - 节点按顺序排列，边权 1 显示为绿色。  
   - 最后一条边权调整显示为黄色，标注 `p - (n-2)`。
2. **剩余边填充**：  
   - 随机选取非链边，以红色显示，权值标注 1e9。
3. **像素风格**：  
   - 节点：8-bit 像素方块，链边用绿色像素线，剩余边用红色虚线。
   - 音效：添加链边时播放“哔”声，剩余边播放“嘟”声。

**交互设计**：
- **速度控制**：滑块调节动画速度（1x-5x）。
- **AI 模式**：自动填充剩余边，模拟“贪吃蛇”路径生成。

---

### **代码实现（核心逻辑）**

```cpp
#include <cstdio>
const int P = 1e5 + 3; // 固定质数

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d %d\n1 2 %d\n", P, P, P - n + 2);
    for (int i = 2; i < n; ++i)
        printf("%d %d 1\n", i, i + 1);
    m -= n - 1;
    for (int k = 0, j = n; m--;) {
        if (++j > n) j = ++k + 2;
        printf("%d %d 9999999\n", k, j);
    }
    return 0;
}
```

**核心逻辑**：
- 第 4 行：输出总边权和质数 P。
- 第 5 行：构造前 n-2 条权为 1 的边。
- 第 8-11 行：动态生成剩余边，避免重复。

---

### **复古像素化演示（伪代码）**

```javascript
// Canvas 初始化
const ctx = canvas.getContext('2d');
ctx.fillStyle = '#00FF00'; // 链边颜色

// 绘制链
for (let i = 0; i < n; i++) {
    drawPixelNode(i, 100 + i * 30, 100); // 节点坐标
    if (i > 0) drawEdge(i-1, i, (i === 1) ? P - n + 2 : 1);
}

// 填充剩余边（红色虚线）
ctx.setLineDash([5, 5]);
ctx.strokeStyle = '#FF0000';
for (let edge of remainingEdges) {
    drawEdge(edge.u, edge.v);
    playSound('beep'); // 8-bit 音效
}
```

---
处理用时：71.82秒