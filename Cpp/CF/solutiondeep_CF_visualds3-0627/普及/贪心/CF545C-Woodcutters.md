# 题目信息

# Woodcutters

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1},x_{2},...,x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i},x_{i}] $ or $ [x_{i};x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 说明/提示

In the first sample you can fell the trees like that:

- fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1;1] $
- fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2;3] $
- leave the $ 3 $ -rd tree — it occupies point $ 5 $
- leave the $ 4 $ -th tree — it occupies point $ 10 $
- fell the $ 5 $ -th tree to the right — now it occupies segment $ [19;20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10;19] $ .

## 样例 #1

### 输入

```
5
1 2
2 1
5 10
10 9
19 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2
2 1
5 10
10 9
20 1
```

### 输出

```
4
```

# AI分析结果



---

### **题解思路与算法要点**

#### **核心贪心策略**
1. **首尾处理**：首棵树必须向左倒，最后一棵必须向右倒（确保不影响中间树的决策）。
2. **中间树策略**：
   - 优先向左倒：若当前树的左倒区间与前一棵已倒树不冲突，则左倒。
   - 无法左倒则尝试右倒：若右倒后不覆盖下一棵树的原始位置，则右倒。
3. **坐标更新**：若某棵树右倒，需更新其坐标为 `x[i] + h[i]`，以便后续比较。

#### **解决难点**
- **贪心正确性证明**：优先左倒不会影响后续选择，右倒可能影响下一棵树的左倒，但此时下一棵树的左倒已被当前树右倒占据，此时两种选择对总答案的贡献相同，因此贪心有效。
- **边界处理**：首尾树必须倒，需单独处理。

---

### **题解评分（≥4星）**

| 作者          | 评分 | 关键亮点                                                                 |
|---------------|------|--------------------------------------------------------------------------|
| yzx72424      | ★★★★☆ | 代码简洁，直接体现贪心策略，但缺少详细证明。                             |
| ddmd          | ★★★★☆ | 明确讨论贪心策略的正确性，代码结构清晰。                                 |
| 一只书虫仔    | ★★★★☆ | 分点总结动态规划与贪心思路，对比分析到位。                               |
| 李若谷        | ★★★★☆ | 代码高效，记录前一棵树的倒向，逻辑严密。                                 |

---

### **最优思路提炼**
1. **贪心方向优先级**：左倒优先，右倒次之。
2. **动态更新坐标**：右倒后更新当前树坐标，避免后续冲突。
3. **首尾特判**：首尾树直接倒向两侧，不参与中间决策。

---

### **同类型题目与算法套路**
- **区间调度问题**：如活动选择问题（选择不重叠区间最大化数量）。
- **常见贪心场景**：按某一规则排序后，依次选择最优解（如按右端点排序）。
- **洛谷推荐题目**：
  1. [P2887 Sunscreen G](https://www.luogu.com.cn/problem/P2887)（区间匹配贪心）
  2. [P2859 Stall Reservations S](https://www.luogu.com.cn/problem/P2859)（区间分组贪心）
  3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)（二维排序贪心）

---

### **个人心得摘录**
- **李若谷**：首棵树必须左倒，动态维护前一棵树的倒向状态。
- **When**：向右倒若不影响下一棵左倒，则最优；否则贡献相同。
- **傅思维666**：贪心与动态规划对比，贪心更简洁高效。

---

### **可视化算法演示设计**
#### **核心贪心过程动画方案**
1. **像素风格展示**：
   - 每棵树用不同颜色方块表示，坐标轴横向排列。
   - 左倒/右倒时，用延伸色块表示覆盖区间。
   - 冲突检测：红色闪烁提示无法倒。
2. **交互功能**：
   - **步进控制**：手动点击或自动播放，速度可调。
   - **高亮当前树**：绿色边框标记当前决策树。
   - **状态面板**：显示已倒树数量、当前决策结果。
3. **音效与反馈**：
   - 成功倒树：清脆“叮”声。
   - 冲突发生：低沉“嗡”声。
   - 背景音乐：8-bit 轻快循环曲。

#### **复古游戏化设计**
- **积分系统**：每成功倒树+10分，连续无冲突+50连击分。
- **关卡模式**：每关增加树的数量或调整位置，难度递增。
- **Canvas 实现**：通过 `<canvas>` 绘制像素树和区间，代码片段如下：

```javascript
// 绘制树和倒向区间
function drawTree(x, height, isFallen, direction) {
  ctx.fillStyle = isFallen ? "#FF5555" : "#55FF55";
  ctx.fillRect(x * scale, 100, 5, 20); // 树身
  if (isFallen) {
    const len = height * scale;
    const startX = direction === 'left' ? x * scale - len : x * scale;
    ctx.fillRect(startX, 120, len, 5); // 倒向区间
  }
}
```

---

### **关键代码片段（贪心核心逻辑）**
```cpp
int ans = 2; // 首尾必倒
for (int i = 2; i < n; i++) {
    if (x[i] - h[i] > x[i-1]) { // 左倒不冲突
        ans++;
    } else if (x[i] + h[i] < x[i+1]) { // 右倒不冲突
        ans++;
        x[i] += h[i]; // 更新坐标
    }
}
```

---

### **总结**
本题通过贪心策略最大化倒树数量，关键在于优先左倒的动态选择与坐标更新。可视化设计结合复古像素风格和步进交互，能直观展示贪心决策过程，适合教学与算法理解。

---
处理用时：71.11秒