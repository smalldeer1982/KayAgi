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



### 唯一算法分类
**构造**

---

### 综合分析与结论
#### 核心思路与难点
题目要求构造一个满足双重质数条件（最短路径和MST权值）的图。各题解的核心思路如下：
1. **链式结构构造**：将图的1→n节点连成一条链，使得该链既是唯一的最短路径，又是唯一的MST。
2. **质数控制**：通过前n-1条边构造总权值为一个大质数（如1e5+3），其中1→2边权为质数差值，其余链边权为1。
3. **冗余边处理**：剩余边用极大权值（如1e9）填充，确保不影响最短路径和MST结构。

**解决难点**：
- 双重质数的同步满足：通过链式结构的权值总和直接控制两个条件。
- 边数填充：通过枚举非相邻节点补充边，避免破坏核心结构。

#### 可视化设计思路
1. **动画流程**：
   - **步骤1**：绘制节点1~n的链式排列，用绿色高亮。
   - **步骤2**：动态添加链边，其中1→2边标红并显示权值调整过程（如p-n+2的计算）。
   - **步骤3**：剩余边以灰色虚线动态连接，权值标注1e9。
   - **步骤4**：触发质数校验动画（如质数数值闪烁）。
2. **复古风格**：
   - **像素网格**：节点用8-bit方块表示，边用不同颜色像素线连接。
   - **音效**：添加链边时播放“叮”声，冗余边时播放低沉音效，质数校验成功时播放胜利音效。
   - **自动演示**：AI模式按步骤执行，用户可暂停观察权值变化逻辑。

---

### 题解清单（≥4星）
1. **Fuko_Ibuki（5星）**
   - **亮点**：代码极度简洁，直接使用1e5+3作为质数模板，剩余边填充逻辑高效。
   - **关键代码**：
     ```cpp
     printf("%d %d\n",p,p);
     printf("1 2 %d\n",p-n+2);
     for (i=2;i<n;i++) printf("%d %d 1\n",i,i+1);
     ```
2. **0xFF（4.5星）**
   - **亮点**：详细注释说明质数选择逻辑，代码可读性强。
   - **心得**：“打9999999的时候真的爽”体现构造题的暴力美学。
3. **yimuhua（4星）**
   - **亮点**：变量命名清晰，循环逻辑优雅，适合教学演示。

---

### 最优思路提炼
1. **链式结构**：将1→n连成唯一路径，保证最短路径和MST重合。
2. **质数生成公式**：`总质数 = 1→2边权 + (n-2)*1`，其中1→2边权为`p-n+2`（p为大质数）。
3. **边权隔离**：非链边用极大值隔离，确保不影响核心结构。

---

### 同类型题与算法套路
- **构造特定权值图**：如CF1003E（构造直径限制的树）、Luogu P1119（灾后重建-时间约束最短路）。
- **质数特殊条件**：如CF45G（将数列拆分为质数和的构造问题）。
- **最小生成树与最短路结合**：如USACO 2005 Dec Gold（设计最短路径同时满足MST条件）。

---

### 推荐练习题
1. **CF1003E** - Tree Constructing（构造指定直径的树）
2. **Luogu P1119** - 灾后重建（时间约束的最短路径）
3. **CF45G** - Prime Problem（质数拆分构造）

---

### 个人心得摘录
- **Fuko_Ibuki**：“打9999999的时候真的爽”——构造题中暴力填充冗余边是常见且有效的技巧。
- **东灯**：通过筛法预选质数，体现了算法鲁棒性，但代码复杂度较高。
- **wuyixiang**：尝试菊花图构造，虽未被采纳，但拓展了构造思路的多样性。

---

### 可视化代码片段（JS Canvas）
```javascript
// 绘制链式结构核心边
function drawChainEdges(ctx, nodes) {
  ctx.strokeStyle = "#00FF00"; // 绿色高亮
  nodes.forEach((node, i) => {
    if (i > 0) {
      ctx.beginPath();
      ctx.moveTo(nodes[i-1].x, nodes[i-1].y);
      ctx.lineTo(node.x, node.y);
      ctx.stroke(); // 绘制链边
      playSound('beep'); // 触发音效
    }
  });
}

// 填充冗余边（像素风格）
function fillRedundantEdges(ctx, edges) {
  ctx.setLineDash([5, 3]); // 虚线样式
  edges.forEach(edge => {
    ctx.strokeStyle = "#808080"; // 灰色
    ctx.beginPath();
    ctx.moveTo(edge.from.x, edge.from.y);
    ctx.lineTo(edge.to.x, edge.to.y); 
    ctx.stroke();
    playSound('low_beep'); // 低频音效
  });
}
```

---

### 复古游戏化设计
- **颜色方案**：16色调色板，节点用亮蓝（#00F），链边用绿色（#0F0），冗余边用深灰（#555）。
- **音效**：Web Audio生成方波音效，链边添加时频率800Hz，冗余边400Hz，质数校验成功时播放上升琶音。
- **自动演示**：通过setInterval分步执行构造逻辑，用户可按空格暂停/继续。
- **积分系统**：每正确构造一条链边+10分，填充冗余边+1分，质数校验成功+100分。

---
处理用时：65.16秒