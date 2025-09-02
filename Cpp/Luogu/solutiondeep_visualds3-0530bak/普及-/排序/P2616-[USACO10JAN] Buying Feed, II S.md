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



## 算法分类
贪心

---

## 综合分析与结论

### 核心思路
题目要求最小化购买饲料的成本与运输成本之和。每个商店的每磅饲料总成本可拆解为 **购买价 + 运输到终点的费用**，即 `C_i + (E - X_i)`。通过贪心策略，优先购买总成本最低的饲料，直到满足需求量 K。

### 关键难点与解决
1. **正确计算总成本**：需将运输费用分摊到每磅饲料，确保每个商店的总成本计算正确。
2. **部分购买处理**：当某个商店的库存超过剩余需求时，只需购买所需量。

### 算法流程
1. **预处理**：计算每个商店的每磅总成本。
2. **排序**：按总成本升序排列所有商店。
3. **贪心购买**：依次从总成本最低的商店购买，直至满足 K 磅。

### 可视化设计
- **像素风格动画**：用不同颜色方块表示商店，位置基于 X 轴，标签显示总成本。
- **排序过程**：动态展示商店按总成本排序后的排列。
- **购买过程**：高亮当前处理的商店，显示购买量及剩余需求。
- **音效提示**：购买时播放音效，完成时播放成功音效。

---

## 题解清单（≥4星）

### 1. 幽界の冥神（5星）
- **亮点**：代码简洁，结构清晰，注释明确，直接体现贪心核心。
- **代码片段**：
  ```cpp
  struct food{int val,num;};
  sort(f+1,f+1+n,cmp); // 按总成本排序
  for(int i=1;i<=n&&number>0;i++){
      ans += Min(number,f[i].num)*f[i].val;
      number -= f[i].num;
  }
  ```

### 2. tktp_AK（4星）
- **亮点**：结构体命名规范，变量说明详细，适合新手理解。
- **代码片段**：
  ```cpp
  struct node{int x,f,c;};
  sort(a+1,a+n+1,cmp); // 按总成本排序
  for(int i=1;i<=n&&t<k;i++){
      ans += min(k-t,a[i].f)*a[i].c;
      t += a[i].f;
  }
  ```

### 3. SunsetLake（4星）
- **亮点**：详细注释，结构体设计合理，适合教学。
- **代码片段**：
  ```cpp
  struct node{int x,f,c,tal;};
  sort(st+1,st+1+n,cmp); // 按总成本排序
  for(int i=1;;i++){
      k -= st[i].f;
      ans += st[i].tal*st[i].f;
  }
  ```

---

## 最优思路提炼

### 关键技巧
1. **总成本拆分**：将动态的运输费用转化为静态的每磅成本。
2. **贪心排序**：按总成本升序处理商店，确保每次选择最优解。
3. **部分购买处理**：用 `min()` 函数处理剩余需求不足的情况。

---

## 类似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心选择最小代价合并。
2. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：按单位价值排序后贪心。
3. [P4544 Buying Feed G](https://www.luogu.com.cn/problem/P4544)：进阶版，需动态规划优化。

---

## 可视化算法演示

### 动画方案
1. **初始化**：在 Canvas 上绘制 X 轴（0 到 E），标记商店位置和总成本。
2. **排序阶段**：动态展示商店按总成本升序排列的过程。
3. **购买阶段**：
   - 高亮当前商店，显示购买量。
   - 更新剩余需求，显示累计费用。
4. **音效**：购买时播放“收集”音效，结束时播放“完成”音效。

### 复古像素风格
- **颜色方案**：使用 8 位色系，商店用不同颜色区分。
- **交互设计**：支持暂停/继续，调整动画速度，显示当前步骤说明。

### 核心代码片段（JavaScript）
```javascript
// 绘制商店（伪代码）
function drawStores() {
  stores.forEach(store => {
    ctx.fillStyle = store.color;
    ctx.fillRect(store.x * scaleX, 50, 20, 20);
    ctx.fillText(`$${store.cost}`, store.x * scaleX, 45);
  });
}

// 贪心购买动画
function animatePurchase() {
  let currentStore = sortedStores[index];
  let buyAmount = Math.min(remainingK, currentStore.f);
  totalCost += buyAmount * currentStore.cost;
  remainingK -= buyAmount;
  // 播放音效
  playSound('collect');
}
```

---

通过上述分析与设计，可直观理解贪心策略在此题中的应用，并通过交互式学习加深对动态成本计算的理解。

---
处理用时：98.01秒