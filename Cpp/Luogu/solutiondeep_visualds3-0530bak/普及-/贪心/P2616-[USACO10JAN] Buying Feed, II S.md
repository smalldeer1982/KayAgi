# 题目信息

# [USACO10JAN] Buying Feed, II S

## 题目描述

Farmer John needs to travel to town to pick up K (1 <= K <= 100) pounds of feed. Driving D miles with K pounds of feed in his truck costs D\*K cents.

The county feed lot has N (1 <= N <= 100) stores (conveniently numbered 1..N) that sell feed. Each store is located on a segment of the X axis whose length is E (1 <= E <= 350). Store i is at location X\_i (0 < X\_i < E) on the number line and can sell FJ as much as F\_i (1 <= F\_i <= 100) pounds of feed at a cost of C\_i (1 <= C\_i <= 1,000,000) cents per pound. Amazingly, a given point on the X axis might have more than one store.

FJ starts at location 0 on this number line and can drive only in the positive direction, ultimately arriving at location E, with at least K pounds of feed. He can stop at any of the feed stores along the way and buy any amount of feed up to the the store's limit.

What is the minimum amount FJ has to pay to buy and transport the K pounds of feed? FJ knows there is a solution.

Consider a sample where FJ needs two pounds of feed from three stores (locations: 1, 3, and 4) on a number line whose range is 0..5:

```
0   1   2   3   4   5 
+---|---+---|---|---+ 
    1       1   1      Available pounds of feed 
    1       2   2      Cents per pound 
```
It is best for FJ to buy one pound of feed from both the second and third stores. He must pay two cents to buy each pound of feed for a total cost of 4. When FJ travels from 3 to 4 he is moving 1 unit of length and he has 1 pound of feed so he must pay 1\*1 = 1 cents.

When FJ travels from 4 to 5 he is moving one unit and he has 2 pounds of feed so he must pay 1\*2 = 2 cents.

The total cost is 4+1+2 = 7 cents. 

FJ 开车去买 $K$ 份食物，如果他的车上有 $X$ 份食物。每走一里就花费 $X$ 元。FJ 的城市是一条线，总共 $E$ 里路，有 $E+1$ 个地方，标号 $0\sim E$。 FJ 从 $0$ 开始走，到 $E$ 结束（不能往回走），要买 $K$ 份食物。 城里有 $N$ 个商店，每个商店的位置是 $X_i$（一个点上可能有多个商店），有 $F_i$ 份食物，每份 $C_i$ 元。 问到达 $E$ 并买 $K$ 份食物的最小花费。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/1720.png)


## 样例 #1

### 输入

```
2 5 3
3 1 2
4 1 2
1 1 1```

### 输出

```
7```

# AI分析结果



### 综合分析与结论

**题目核心**：在购买饲料的过程中，总成本由饲料价格和运输到终点的费用组成。由于运输费用与路径无关（只需到达终点），贪心策略通过将每个商店的每份饲料总成本固定为 `c_i + (E - x_i)`，排序后依次购买，确保全局最优。

**难点与解决**：正确识别运输费用的固定性，将问题转化为排序后的贪心选择。动态规划解法虽可行，但贪心策略更高效（O(n log n)）。

**可视化设计**：
1. **动画方案**：用像素网格表示 0 到 E 的路径，商店显示为不同颜色方块（颜色深浅表示总成本）。卡车从起点出发，按排序顺序购买饲料，高亮当前选择，显示累计费用。
2. **音效与交互**：购买时播放提示音，自动模式可观察贪心过程，单步控制便于理解每一步的选择逻辑。

---

### 题解清单（≥4星）

1. **tktp_AK（5星）**  
   - **亮点**：结构清晰，变量命名明确，使用 `long long` 避免溢出风险，代码注释详细。  
   - **引用**：*"成本为每份食物的价格加上路费"* 直接点明贪心依据。

2. **幽界の冥神（4星）**  
   - **亮点**：代码简洁高效，正确实现贪心策略，适合快速理解算法核心。  
   - **不足**：缺少对总成本公式的推导解释。

3. **zilingheimei（4星）**  
   - **亮点**：注释详细，变量名语义明确，强调购买策略（买光或补足）。  
   - **心得**：*"因为花费不可能是负数"* 强调贪心的正确性边界。

---

### 核心代码实现

```cpp
// 结构体定义与排序
struct node { int x, f, c; };
bool cmp(node a, node b) { return (a.c + E - a.x) < (b.c + E - b.x); }

// 贪心购买逻辑
sort(a + 1, a + n + 1, cmp);
long long ans = 0, bought = 0;
for (int i = 1; i <= n && bought < k; i++) {
    int take = min(a[i].f, k - bought);
    ans += take * (a[i].c + E - a[i].x);
    bought += take;
}
```

---

### 同类型题与算法套路

**常见贪心场景**：  
- **固定成本合并**（如运输费、时间成本）转化为单一指标排序。  
- **区间选择**：按结束时间排序，优先选最早结束的任务。  
- **性价比排序**：如背包问题中的单位重量价值排序。

**推荐题目**：  
1. [P2949 USACO09OPEN] Work Scheduling G  
2. [P1208 USACO1.3] 混合牛奶 Mix Milk  
3. [P1090 NOIP2004] 合并果子  

---

### 可视化与游戏化设计

**复古像素动画**：  
1. **Canvas 绘制**：  
   - 商店为彩色方块，颜色亮度表示总成本（低→绿，高→红）。  
   - 卡车像素动画移动，购买时显示数值变化。  
2. **音效与自动演示**：  
   - 购买成功时播放“金币音效”，背景 8-bit 音乐循环。  
   - AI 自动按排序顺序购买，用户可暂停/加速观察。  

**交互设计**：  
```javascript
// 示例：绘制商店和路径
ctx.fillStyle = '#00FF00'; // 低总成本商店
ctx.fillRect(x * scale, 0, 10, 10);
// 更新卡车位置
function moveTruck(nextX) {
    animate(truck.x, nextX, () => playSound('move'));
}
```

---

### 总结

贪心策略通过**合并固定成本**和**排序**高效解决此问题，动态规划适用于更复杂的场景。可视化设计通过像素动画和音效增强理解，适合教学与自学。

---
处理用时：92.31秒