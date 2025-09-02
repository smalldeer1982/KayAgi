# 题目信息

# Graph Cost

## 题目描述

You are given an initially empty undirected graph with $ n $ nodes, numbered from $ 1 $ to $ n $ (i. e. $ n $ nodes and $ 0 $ edges). You want to add $ m $ edges to the graph, so the graph won't contain any self-loop or multiple edges.

If an edge connecting two nodes $ u $ and $ v $ is added, its weight must be equal to the greatest common divisor of $ u $ and $ v $ , i. e. $ \gcd(u, v) $ .

In order to add edges to the graph, you can repeat the following process any number of times (possibly zero):

- choose an integer $ k \ge 1 $ ;
- add exactly $ k $ edges to the graph, each having a weight equal to $ k + 1 $ . Adding these $ k $ edges costs $ k + 1 $ in total.

 Note that you can't create self-loops or multiple edges. Also, if you can't add $ k $ edges of weight $ k + 1 $ , you can't choose such $ k $ .For example, if you can add $ 5 $ more edges to the graph of weight $ 6 $ , you may add them, and it will cost $ 6 $ for the whole pack of $ 5 $ edges. But if you can only add $ 4 $ edges of weight $ 6 $ to the graph, you can't perform this operation for $ k = 5 $ .

Given two integers $ n $ and $ m $ , find the minimum total cost to form a graph of $ n $ vertices and exactly $ m $ edges using the operation above. If such a graph can't be constructed, output $ -1 $ .

Note that the final graph may consist of several connected components.

## 说明/提示

In the first test case, we can add an edge between the vertices $ 2 $ and $ 4 $ with $ \gcd = 2 $ . This is the only possible way to add $ 1 $ edge that will cost $ 2 $ .

In the second test case, there is no way to add $ 10 $ edges, so the answer is $ -1 $ .

In the third test case, we can add the following edges:

- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 2 $ and $ 4 $ ( $ \gcd(2, 4) = 2 $ ). Cost: $ 2 $ ;
- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 4 $ and $ 6 $ ( $ \gcd(4, 6) = 2 $ ). Cost: $ 2 $ ;
- $ k = 2 $ : edges of weight $ 3 $ : $ (3, 6) $ and $ (3, 9) $ ( $ \gcd(3, 6) = \gcd(3, 9) = 3 $ ). Cost: $ 3 $ .

 As a result, we added $ 1 + 1 + 2 = 4 $ edges with total cost $ 2 + 2 + 3 = 7 $ , which is the minimal possible cost.

## 样例 #1

### 输入

```
4
4 1
6 10
9 4
10 11```

### 输出

```
2
-1
7
21```

# AI分析结果



### 综合分析与结论

**核心思路**：  
通过预处理欧拉函数前缀和，计算每个边权对应的可用边数。采用贪心策略，从大边权开始尽可能多地选边，确保总代价最小。

**贪心选择策略**：  
1. **策略推导**：  
   - 边权越大，每次操作的代价性价比越高（平均每条边代价趋近于1）。  
   - 数学证明：假设存在两个边权 $s_1 > s_2$，优先选 $s_1$ 的决策不会更差。  
2. **实现方式**：  
   - 从大到小枚举边权 $s =k+1$，计算当前边权能贡献的边数上限。  
   - 每次尽可能多选边，直到满足剩余边数需求或无法继续选择当前边权。  

**可视化设计思路**：  
- **颜色标记**：当前处理的边权 $s$ 用高亮色块表示，已选边数用进度条动态更新。  
- **动画方案**：  
  - 初始状态显示所有可能的边权及对应边数。  
  - 贪心选择时，高亮当前边权块，展示其贡献边数的计算过程（如 $\text{sum}[n/s]$）。  
  - 动态更新剩余边数 $m$ 和总代价。  
- **音效触发**：成功添加边时播放“收集金币”音效，不足时触发警告音。  

### 题解清单（≥4星）

1. **Inui_Sana（★★★★★）**  
   - **亮点**：线性筛预处理欧拉函数，时间复杂度 $O(n)$；贪心逻辑清晰，代码简洁。  
   - **关键代码**：从大到小枚举 $k$，优先处理高边权。  
   ```cpp
   for(int i=n-1;i&&m;i--){
       ll cnt = sum[n/(i+1)]; // 计算当前边权对应边数
       ll take = min(cnt, m) / i; // 最多选 take 次操作
       ans += (i+1) * take;
       m -= i * take;
   }
   ```

2. **MortisM（★★★★☆）**  
   - **亮点**：严格数学证明贪心策略正确性，时间复杂度 $O(n)$。  
   - **优化点**：直接复用欧拉函数前缀和，避免冗余计算。  

3. **yingkeqian9217（★★★★☆）**  
   - **亮点**：详细推导欧拉函数与边数关系，代码注释清晰。  
   - **个人心得**：强调预处理时需注意 $\phi(1)=0$ 的特殊处理。  

### 最优思路提炼

**关键步骤**：  
1. **预处理**：线性筛计算欧拉函数 $\phi(x)$，并生成前缀和数组 $\text{sum}[x]$。  
2. **贪心枚举**：从 $s =n$ 到 $s=2$（对应 $k =n-1$ 到 $k=1$），计算每个 $s$ 的最大贡献。  
3. **贡献计算**：  
   - 可用边数 $= \text{sum}[\lfloor n/s \rfloor]$。  
   - 每次操作贡献 $k$ 条边，代价 $s$。尽可能多次操作。  

**代码实现核心**：  
```cpp
// 预处理欧拉函数及前缀和
phi[1] = 0;
for (int i = 2; i <= maxn; i++) {
    if (!vis[i]) primes.push_back(i), phi[i] = i-1;
    for (auto p : primes) {
        if (i*p > maxn) break;
        vis[i*p] = true;
        if (i % p == 0) { phi[i*p] = phi[i] * p; break; }
        else phi[i*p] = phi[i] * (p-1);
    }
    sum[i] = sum[i-1] + phi[i];
}

// 贪心选择
int ans = 0;
for (int s = n; s >= 2; s--) {
    int k = s - 1;
    int max_edges = sum[n/s];
    int take = min(max_edges, m) / k;
    if (take > 0) {
        ans += take * s;
        m -= take * k;
    }
}
if (m != 0) ans = -1;
```

### 同类型题与算法套路

**常见贪心场景**：  
- **代价性价比排序**：如背包问题按单位重量价值排序。  
- **区间调度**：选择结束时间最早的活动。  
- **资源分配**：优先满足高收益需求。  

**推荐题目**：  
1. [CF1772D] Absolute Sorting（贪心边界判断）  
2. [Luogu P1233] 木棍加工（二维偏序贪心）  
3. [LeetCode 1353] 最多可以参加的会议数目（区间贪心）  

### 复古游戏化动画设计

**像素风格实现**：  
- **Canvas 绘制**：用色块表示边权，高度表示边数，动态消减。  
- **交互设计**：  
  - **步进控制**：按空格键单步执行当前边权选择。  
  - **音效**：选择成功时播放“金币+1”音效，失败时“error”提示音。  
- **自动演示模式**：AI 自动以最优策略运行，速度可调。  

**关键代码片段**：  
```javascript
// 伪代码：贪心动画逻辑
function drawGreedyStep(s) {
    ctx.fillStyle = "#FF0000"; // 当前边权高亮红色
    ctx.fillRect(x, y, width, height); // 绘制边权块
    setTimeout(() => {
        ctx.fillStyle = "#00FF00"; // 已选边数绿色填充
        ctx.fillRect(x, y, width * takenEdges / maxEdges, height);
        playSound('coin.wav');
    }, 500);
}
```

### 个人心得摘录

1. **Inui_Sana**：  
   > “必须注意前缀和数组用 `long long`，否则大数据溢出会导致 WA。”  
   - **教训**：预处理时务必考虑数据范围。  

2. **yingkeqian9217**：  
   > “$\phi(1)$ 初始化为 0，否则会导致前缀和多算一对。”  
   - **调试经验**：边界值需特殊处理。  

3. **Priestess_SLG**：  
   > “暴力容斥法在 $n=1e6$ 时会 TLE，必须用线性筛优化。”  
   - **优化技巧**：优先选择线性复杂度算法。

---
处理用时：80.01秒