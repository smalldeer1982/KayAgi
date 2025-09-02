# 题目信息

# [USACO07JAN] Protecting the Flowers S

## 题目描述

Farmer John went to cut some wood and left N (2 ≤ N ≤ 100,000) cows eating the grass, as usual. When he returned, he found to his horror that the cluster of cows was in his garden eating his beautiful flowers. Wanting to minimize the subsequent damage, FJ decided to take immediate action and transport each cow back to its own barn.

Each cow i is at a location that is Ti minutes (1 ≤ Ti ≤ 2,000,000) away from its own barn. Furthermore, while waiting for transport, she destroys Di (1 ≤ Di ≤ 100) flowers per minute. No matter how hard he tries, FJ can only transport one cow at a time back to her barn. Moving cow i to its barn requires 2 × Ti minutes (Ti to get there and Ti to return). FJ starts at the flower patch, transports the cow to its barn, and then walks back to the flowers, taking no extra time to get to the next cow that needs transport.

Write a program to determine the order in which FJ should pick up the cows so that the total number of flowers destroyed is minimized.

有 $n$ 头奶牛跑到 FJ 的花园里去吃花儿了，它们分别在距离牛圈 $T_i$（这里指 FJ 到那里需要 $T_i$ 分钟) 处吃花，每分钟会吃掉 $D_i$ 朵花，FJ 现在要将它们给弄回牛圈，但是他每次只能弄一头回去，来回用时总共为 $2 \times T_i$ 分钟，在这段时间内，其它的奶牛会继续吃 FJ 的花，速度保持不变，当然正在被赶回牛圈的奶牛不能继续吃了。现在求在最好的方案下奶牛吃掉花的最小朵数。


## 说明/提示

FJ returns the cows in the following order: 6, 2, 3, 4, 1, 5. While he is transporting cow 6 to the barn, the others destroy 24 flowers; next he will take cow 2, losing 28 more of his beautiful flora. For the cows 3, 4, 1 he loses 16, 12, and 6 flowers respectively. When he picks cow 5 there are no more cows damaging the flowers, so the loss for that cow is zero. The total flowers lost this way is 24 + 28 + 16 + 12 + 6 = 86.


## 样例 #1

### 输入

```
6
3 1
2 5
2 3
3 2
4 1
1 6```

### 输出

```
86```

# AI分析结果



### 综合分析与结论

本题核心是通过贪心策略确定赶牛顺序，使总破坏最小。所有题解均采用贪心思路，核心策略是：**按 $t_i/d_i$ 的比值从小到大排序**，即优先处理单位时间破坏量高的牛。关键在于推导相邻两头牛的交换对总损失的影响，证明该排序方式的全局最优性。

#### 贪心策略推导
- **相邻交换法**：比较交换两头牛的顺序对总损失的影响。设牛 $x$ 和 $y$，先赶 $x$ 的损失为 $2 \cdot t_x \cdot D_y$，先赶 $y$ 的损失为 $2 \cdot t_y \cdot D_x$。因此，当 $t_x \cdot D_y < t_y \cdot D_x$ 时，应优先赶 $x$。
- **排序依据**：转化为比较 $t_i/d_i$ 的比值，等价于按 $d_i/t_i$ 从大到小排序。

#### 实现关键
1. **前缀和优化**：在排序后，计算剩余牛的破坏量之和，利用前缀和或累减方式快速计算。
2. **数据范围处理**：由于 $N \leq 10^5$，需使用 $O(n \log n)$ 的排序算法，并注意 `long long` 防止溢出。

---

### 题解清单（≥4星）

1. **曦行夜落（★★★★★）**
   - **亮点**：详细推导贪心策略，代码结构清晰，使用前缀和数组优化计算。
   - **代码**：通过排序后计算后缀和，时间复杂度 $O(n \log n)$，代码注释明确。

2. **lzqy_（★★★★）**
   - **亮点**：采用结构体排序和前缀和，实现简洁。强调数据类型转换避免精度问题。
   - **注意点**：前缀和数组从0开始，索引处理需谨慎。

3. **Dawn_Sdy（★★★★）**
   - **亮点**：代码简短高效，直接按贪心策略排序后累加时间和破坏量。
   - **优化**：实时更新剩余破坏量，避免额外空间。

---

### 最优思路提炼

1. **贪心选择策略**：
   - 比较相邻两头牛的 $t_i \cdot D_j$ 与 $t_j \cdot D_i$，确定最优顺序。
   - 排序依据：$t_i / D_i$ 从小到大（或 $D_i / t_i$ 从大到小）。

2. **实现技巧**：
   - **前缀和/累减**：快速计算剩余牛的破坏量之和。
   - **结构体排序**：自定义比较函数，避免浮点运算（直接交叉相乘比较）。

---

### 同类型题目与算法套路

- **常见贪心场景**：
  - **任务调度**：按截止时间或惩罚最小化排序。
  - **区间选择**：如不重叠区间问题，按右端点排序。
  - **性价比优化**：如背包问题中的部分背包。

- **通用解法**：
  1. **相邻交换法**：验证局部调整是否影响全局最优。
  2. **排序策略**：根据题意设计排序依据（如比值、差值等）。

---

### 推荐相似题目

1. **P1230 智力大冲浪**（任务调度，贪心选择截止时间）
2. **P1080 国王游戏**（排序贪心，处理乘积关系）
3. **P1016 旅行家的预算**（油价贪心，分段决策）

---

### 代码片段（核心逻辑）

#### 贪心排序与计算
```cpp
struct Cow { int t, d; };
bool cmp(Cow x, Cow y) {
    return x.t * y.d < y.t * x.d; // 避免浮点运算
}

// 计算总损失
long long ans = 0, sum_d = 0;
for (int i = 0; i < n; i++) sum_d += cows[i].d;
for (int i = 0; i < n; i++) {
    sum_d -= cows[i].d;
    ans += 2LL * cows[i].t * sum_d;
}
```

---

### 可视化设计思路（复古像素风格）

#### 动画方案
- **像素元素**：牛用不同颜色方块表示，方块上标注 $t_i$ 和 $D_i$。
- **贪心高亮**：当前选择的牛闪烁显示，右侧面板动态更新剩余破坏量。
- **音效提示**：
  - **选择牛**：8-bit 点击音效。
  - **更新总和**：短促“金币”音效。

#### 交互功能
- **步进控制**：允许暂停/继续，观察每一步的选择和损失计算。
- **自动演示**：AI 按排序顺序自动执行，速度可调。
- **对比模式**：并行展示不同排序策略（如按 $t$ 或 $D$ 排序）的结果差异。

#### Canvas 绘制
```javascript
// 伪代码：绘制牛队列
ctx.fillStyle = '#FF0000'; // 当前选择牛
ctx.fillRect(x, y, 30, 30); // 绘制方块
ctx.fillText(`${t} / ${D}`, x, y + 35); // 标注数据
```

---

### 个人心得摘录

- **精度问题**：比较比值时，避免浮点误差，使用交叉相乘（如 `x.t * y.d < y.t * x.d`）。
- **数据范围**：`ans` 需用 `long long`，前缀和可能超过 `int` 范围。
- **贪心验证**：通过小样例（如提示中的样例）手动模拟，确保排序正确。

---
处理用时：129.91秒