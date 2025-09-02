# 题目信息

# [USACO13OPEN] Fuel Economy S

## 题目描述

Farmer John has decided to take a cross-country vacation. Not wanting his cows to feel left out, however, he has decided to rent a large truck and to bring the cows with him as well!

The truck has a large tank that can hold up to G units of fuel (1 <= G <= 1,000,000).  Unfortunately, it gets very poor mileage: it consumes one unit of fuel for every unit of distance traveled, and FJ has a total of D units of distance to travel along his route (1 <= D <= 1,000,000,000).

Since FJ knows he will probably need to stop to refill his tank several times along his trip, he makes a list of all the N fuel stations along his route (1 <= N <= 50,000).  For each station i, he records its distance X\_i from the start of the route (0 <= X\_i <= D), as well as the price Y\_i per unit of fuel it sells (1 <= Y\_i <= 1,000,000).

Given this information, and the fact that FJ starts his journey with exactly B units of fuel (0 <= B <= D), please determine the minimum amount of money FJ will need to pay for fuel in order to reach his destination. If it is impossible for him to reach the destination, please output -1. Note that the answer to this problem may not fit into a standard 32-bit integer.


Farmer John 决定去一次跨国旅游度假。为了不让他的奶牛们感到被抛弃，他决定租一辆大卡车来带他的奶牛们一起旅行。


这辆卡车有一个很大的油箱，可以装下 $G$ 个单位的油（$1 \le G \le {10}^6$），不幸的是，卡车的耗油量也很大，卡车每运动一个单位的距离，就要消耗一个单位的油。Farmer John 要在他的旅程中走 $D$ 个单位的距离。（$1 \le D \le {10}^9$）


因为 FJ 直到他可能要几次在旅途中停下，给油箱加油，所以他把在旅途沿路上的 $N$ 个加油站的记录做成了表格。对于第 $i$ 个加油站，他记录了加油站与起点的距离 $X_i$（$0 \le X_i \le D$），以及加油站中每单位油的价格 $Y_i$（$1 \le Y_i \le {10}^6$）。

已知以上所给的信息，以及 FJ 在路途开始时拥有的燃油的数量 $B$（$0 \le B \le D$），请计算出 FJ 到达目的地时花费的油费用的最小值。如果 FJ 无法到达旅途的终点，那么请输出 `-1`。本题的答案可能无法使用 32 位整数储存。


## 说明/提示

样例解释：FJ 先移动 $2$ 个单位，然后停下购买 $2$ 个单位的油（要花费 $40 \times 2$）。然后一直前进到距离起点 $5$ 个单位的地方，此时油箱为空。这时向油箱里加满油（要花费 $7 \times 10$）。再向前走 $5$ 个单位，加 $2$ 个单位的油（花费 $12 \times 2$）。最后一直走到终点。此时总花费是 $174$。


## 样例 #1

### 输入

```
4 10 3 17
2 40
9 15
5 7
10 12```

### 输出

```
174
```

# AI分析结果



---

**算法分类选择**  
其他搜索（贪心策略）

---

**综合分析与结论**  

本题的核心在于贪心策略的运用，而非传统的BFS/DFS搜索。解题关键在于在每个加油站做出最优加油决策，确保总花费最小：

1. **预处理与边界判断**  
   - 按距离排序加油站，处理无法到达的边界情况（如初始油量不足、相邻加油站间距过大）。
   - 将终点视为价格为0的加油站，简化最终阶段的处理。

2. **贪心策略的核心逻辑**  
   - **优先寻找更便宜的加油站**：在当前加油站能到达的范围内，若存在更便宜的加油站，则仅加足够到达的油量。
   - **加满油到最便宜的加油站**：若范围内无更便宜的，则在当前加油站加满油，并前往范围内最便宜的加油站。

3. **反悔机制优化**  
   - 使用优先队列或单调栈维护已购买的油量，优先消耗便宜的油，遇到更便宜的油时替换高价油（如反悔贪心策略）。

---

**题解清单 (≥4星)**  

1. **xuxinyu的题解（4.5星）**  
   - **亮点**：简洁的贪心策略实现，通过动态查找下一个更优加油站，处理边界清晰。  
   - **代码可读性**：直接排序后遍历，逻辑清晰，添加终点加油站巧妙。

2. **红黑树的题解（4星）**  
   - **亮点**：使用单调栈维护最近更优加油站，预处理快速定位，减少重复判断。  
   - **优化**：时间复杂度为O(N log N)，适合大规模数据。

3. **John_yangliwu的题解（4星）**  
   - **亮点**：反悔贪心结合单调队列，优先消耗便宜油，动态调整购买策略。  
   - **实践性**：代码结构清晰，适合理解反悔贪心思想。

---

**最优思路或技巧提炼**  

1. **终点处理技巧**  
   - 将终点视为价格为0的加油站，避免对终点的特殊处理，统一逻辑。

2. **单调栈/队列优化**  
   - 预处理每个加油站的“最近更优加油站”，减少运行时决策时间。

3. **反悔贪心实现**  
   - 使用优先队列维护已购买的油，优先消耗低价油，遇到更低价格时动态替换高价油。

---

**同类型题推荐**  
1. **LeetCode 134. Gas Station**：加油站环路问题，贪心策略判断可行解。
2. **P1090 合并果子**：优先队列实现贪心选择最小代价。
3. **P5019 铺设道路**：区间覆盖问题，贪心处理最小操作次数。

---

**个人心得摘录**  
- **调试教训**：需注意初始油量是否足够到达第一个加油站，否则直接返回-1。  
- **关键顿悟**：反悔贪心通过“虚拟油箱”动态调整已购油量，将高价油替换为低价油。  
- **边界处理**：相邻加油站间距需严格小于等于油箱容量，否则直接无解。

---

**可视化与算法演示**  

**核心逻辑演示方案**：  
1. **动画流程**：  
   - 车辆从起点出发，油量随移动减少。  
   - 到达加油站时，显示当前油价，并高亮可到达的加油站范围。  
   - 决策过程动态显示：若范围内有更便宜的加油站，仅加所需油量；否则加满油，并前往最便宜的加油站。  

2. **复古像素风格设计**：  
   - **颜色方案**：绿色表示加油站，红色为车辆，黄色为当前油量条。  
   - **Canvas绘制**：加油站以像素点表示，车辆移动时显示轨迹，加油时弹出价格标签。  

3. **音效与交互**：  
   - **加油音效**：8位风格的“滴答”声。  
   - **成功/失败音效**：终点到达时播放胜利音效，无解时播放低沉音效。  
   - **交互控制**：支持暂停/继续，单步执行观察决策过程。

---

**代码片段示例（反悔贪心核心）**  
```cpp
deque<gas> q; // 单调队列维护油量（价格递增）
q.push_back(gas(0, B)); // 初始油量
for (int i = 1; i <= N; i++) {
    int need = e[i].x - e[i-1].x;
    // 消耗油量，优先用便宜的
    while (need > 0) {
        gas &g = q.front();
        if (g.amount <= need) {
            ans += g.amount * g.price;
            need -= g.amount;
            q.pop_front();
        } else {
            ans += need * g.price;
            g.amount -= need;
            need = 0;
        }
    }
    // 反悔高价油，替换为当前低价油
    while (!q.empty() && q.back().price > e[i].price) {
        total -= q.back().amount;
        q.pop_back();
    }
    q.push_back(gas(e[i].price, G - total)); // 加满当前油
    total = G;
}
```

---

**总结**  
本题通过贪心策略结合高效数据结构（单调栈、优先队列）实现最优决策，重点在于动态调整加油策略与反悔机制。可视化设计可直观展示决策过程，复古风格增强学习趣味性。

---
处理用时：126.65秒