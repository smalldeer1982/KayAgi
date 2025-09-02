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
**构造**（图结构的特殊构造）

---

### 题解思路与核心难点
#### 核心思路
1. **构造链式结构**：将顶点连成一条链（1→2→3→...→n），使其同时为最短路和最小生成树。
2. **质数控制**：链的总边权选为大质数（如 $10^5+3$），其中前 $n-2$ 条边权为 1，最后一条边权调整为 $p - (n-2)$，保证总权值为质数。
3. **剩余边处理**：其他边的权值设为极大值（如 $10^9$），确保不影响最短路和 MST。

#### 解决难点
- **双重质数约束**：通过将最短路和 MST 合并为同一条链，只需保证链的总权值为质数。
- **边权分配策略**：通过调整首条边权，将链的总权值动态调整为质数。
- **避免多余边干扰**：剩余边设为极大值，确保算法正确性。

---

### 题解评分（≥4星）
#### 1. Fuko_Ibuki（★★★★★）
- **亮点**：代码简洁高效，固定质数选择（1e5+3），剩余边处理采用递增起点策略避免重复。
- **关键代码**：
  ```cpp
  printf("%d %d %d\n",p,p,p-n+2); // 首边动态调整
  for(i=2;i<n;i++) printf("%d %d 1\n",i,i+1); // 构造链
  ```

#### 2. 0xFF（★★★★☆）
- **亮点**：逻辑清晰，采用固定质数 1e5+3，剩余边处理与 Fuko_Ibuki 类似。
- **核心优化**：使用 `if(++j>n) j=++i+2` 确保边不重复。

#### 3. Mlzsan_HP（★★★★☆）
- **亮点**：极简代码实现，直接复用固定质数策略，适合快速理解算法本质。
- **代码片段**：
  ```cpp
  for(int i=2,j=n;m--;){ // 剩余边填充逻辑
    if(++j>n) j=++k+2;
    printf("%d %d 1000000000\n",k,j);
  }
  ```

---

### 最优思路提炼
1. **链式结构合并约束**：最短路与 MST 共用一条链，减少双重质数控制的复杂度。
2. **质数动态调整**：通过首边权值调整（如 $p-n+2$）使总权值为固定大质数。
3. **剩余边填充策略**：从非相邻顶点开始添加极大权值边，确保不破坏核心结构。

---

### 类似题目
1. **[CF1005E1](https://codeforces.com/problemset/problem/1005/E1)**：构造满足特定路径条件的树。
2. **[CF723F](https://codeforces.com/problemset/problem/723/F)**：构造图使得特定边在 MST 中。
3. **[洛谷 P1113](https://www.luogu.com.cn/problem/P1113)**：构造满足多重约束的图结构。

---

### 可视化设计（核心算法过程）
#### 动画方案
1. **链构造阶段**：
   - **高亮顶点**：1→2→3→...→n 逐步连接，边权标记为 1（绿色）。
   - **首边特殊标记**：1→2 的边权动态计算为红色，显示公式 $p-n+2$。
2. **剩余边填充**：
   - **随机起点填充**：从顶点 0 开始，向非相邻顶点添加灰色边（权值 1e9）。
3. **质数验证**：
   - **动态显示总权值**：链的边权总和实时更新，最终显示质数验证结果。

#### 复古像素风格
- **颜色方案**：绿色（链边）、红色（首边）、灰色（剩余边）。
- **音效设计**：
  - **链构造**：8-bit 短音效（类似 FC 金币声）。
  - **质数验证通过**：上扬音效（类似 FC 过关声）。

---

### 代码片段（核心逻辑）
```cpp
const int p = 1e5 + 3;
int main() {
    int n, m; cin >> n >> m;
    // 构造链结构
    cout << p << " " << p << "\n1 2 " << p - n + 2 << "\n";
    for (int i = 2; i < n; ++i) 
        cout << i << " " << i + 1 << " 1\n";
    // 填充剩余边
    m -= (n - 1);
    for (int k = 0, j = n; m--; ) {
        if (++j > n) j = ++k + 2; // 非相邻顶点策略
        cout << k << " " << j << " 1000000000\n";
    }
}
```

---

### 总结
通过构造链式结构并动态调整边权，将最短路和 MST 的质数约束合并为单一问题。剩余边的极大权值填充策略确保了算法的简洁性和高效性。此方法适用于需要同时满足多个图论约束的构造类题目。

---
处理用时：64.21秒