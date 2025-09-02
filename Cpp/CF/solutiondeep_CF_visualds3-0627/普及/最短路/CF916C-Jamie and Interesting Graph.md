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



### 算法分类
**构造算法**

---

### 题解思路与算法要点
**核心思路**：构造一条链式结构，使得该链既是 1→n 的最短路径，又是最小生成树。通过以下步骤实现：
1. **链式构造**：将 1→n 连成一条链，前 n-2 条边权为 1，最后一条边权为 `p - (n-2)`（其中 p 为大质数）。
2. **质数控制**：选择足够大的质数（如 1e5+3），确保链的总权值为该质数。
3. **填充冗余边**：剩余边设为极大值（如 1e9），避免影响最短路径和 MST。

**解决难点**：
- **双质数条件**：通过链式结构将最短路径和 MST 的权值统一为一个质数。
- **边权分配**：通过调整最后一条边的权值确保总和为质数。
- **冗余边处理**：使用极大值避免干扰核心链结构。

---

### 题解评分（≥4星）
1. **Fuko_Ibuki（★★★★★）**  
   - 思路清晰，代码简洁，直接使用固定大质数 1e5+3，逻辑高效。
2. **0xFF（★★★★☆）**  
   - 类似思路，变量命名更清晰，代码可读性略优。
3. **yimuhua（★★★★☆）**  
   - 代码简短，变量名简洁，适合快速实现。

---

### 最优思路提炼
**关键技巧**：
1. **链式统一**：将最短路径与 MST 合并为同一路径，简化条件。
2. **质数构造**：通过调整边权使总和为质数（如 `p = 1e5+3`）。
3. **冗余边隔离**：大边权填充非关键边，避免干扰核心逻辑。

**代码片段**（Fuko_Ibuki）：
```cpp
int p = 1e5+3; // 固定大质数
printf("%d %d\n", p, p); // 总权值输出
printf("1 2 %d\n", p-n+2); // 首边调整权值
for (int i=2; i<n; i++) printf("%d %d 1\n", i, i+1); // 填充边权为1的链
```

---

### 同类型题与算法套路
**通用解法**：构造特定结构的图（链/树）以满足多个条件，常见于：
1. 最短路径与 MST 的联合构造。
2. 质数相关约束的图论问题。
3. 极值边权分配（极大/极小值隔离）。

**相似题目推荐**：
1. [CF1005E2 - Balanced Tree](https://codeforces.com/problemset/problem/1005/E2)（构造平衡树）
2. [CF118E - Bertown roads](https://codeforces.com/problemset/problem/118/E)（构造欧拉路）
3. [CF723F - st-Spanning Tree](https://codeforces.com/problemset/problem/723/F)（生成树约束）

---

### 可视化与算法演示
**动画设计**：
1. **像素风格**：节点以 8-bit 方块表示，链边为绿色，冗余边为红色。
2. **步进演示**：
   - **步骤1**：绘制节点 1→2→3→...→n，绿色高亮链边，显示边权调整过程。
   - **步骤2**：填充冗余边（红色），边权显示为 1e9。
3. **交互控制**：支持暂停/步进，速度调节（1x/2x/5x）。

**复古游戏化**：
- **音效**：链边添加时播放“哔”声，冗余边添加时播放“咔”声。
- **积分系统**：每正确构造一条链边得 10 分，填充冗余边得 1 分。
- **自动演示模式**：AI 自动按逻辑顺序添加边，可切换手动/自动。

---

### 个人心得摘录
- **Fuko_Ibuki**：  
  “构造链时故意让冗余边极大，最短路径和 MST 自然落在核心链上，无需复杂计算。”
- **东灯**：  
  “质数预处理虽繁琐，但为大规模 n 提供了灵活性。”

---

### 核心代码实现
```cpp
#include <cstdio>
int main() {
    int n, m, p = 1e5 + 3;
    scanf("%d%d", &n, &m);
    printf("%d %d\n1 2 %d\n", p, p, p - n + 2);
    for (int i = 2; i < n; ++i) printf("%d %d 1\n", i, i + 1);
    m -= n - 1;
    for (int k = 0, j = n; m--;) {
        if (++j > n) j = ++k + 2;
        printf("%d %d 9999999\n", k, j);
    }
}
```

---
处理用时：84.81秒