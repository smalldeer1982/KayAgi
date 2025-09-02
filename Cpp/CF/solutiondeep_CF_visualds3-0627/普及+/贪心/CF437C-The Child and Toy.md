# 题目信息

# The Child and Toy

## 题目描述

On Children's Day, the child got a toy from Delayyy as a present. However, the child is so naughty that he can't wait to destroy the toy.

The toy consists of $ n $ parts and $ m $ ropes. Each rope links two parts, but every pair of parts is linked by at most one rope. To split the toy, the child must remove all its parts. The child can remove a single part at a time, and each remove consume an energy. Let's define an energy value of part $ i $ as $ v_{i} $ . The child spend $ v_{f1}+v_{f2}+...+v_{fk} $ energy for removing part $ i $ where $ f_{1},f_{2},...,f_{k} $ are the parts that are directly connected to the $ i $ -th and haven't been removed.

Help the child to find out, what is the minimum total energy he should spend to remove all $ n $ parts.

## 说明/提示

One of the optimal sequence of actions in the first sample is:

- First, remove part $ 3 $ , cost of the action is $ 20 $ .
- Then, remove part $ 2 $ , cost of the action is $ 10 $ .
- Next, remove part $ 4 $ , cost of the action is $ 10 $ .
- At last, remove part $ 1 $ , cost of the action is $ 0 $ .

So the total energy the child paid is $ 20+10+10+0=40 $ , which is the minimum.

In the second sample, the child will spend $ 400 $ no matter in what order he will remove the parts.

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 4
1 2
2 3
```

### 输出

```
40
```

## 样例 #2

### 输入

```
4 4
100 100 100 100
1 2
2 3
2 4
3 4
```

### 输出

```
400
```

## 样例 #3

### 输入

```
7 10
40 10 20 10 20 80 40
1 5
4 7
4 5
5 2
5 7
6 4
1 6
1 3
4 3
1 4
```

### 输出

```
160
```

# AI分析结果



### 综合分析与结论

**题目核心**：通过贪心策略找到删除所有部件的最小总代价。关键在于将问题转化为边的贡献，每条边的贡献取两端点权值的较小值，总和即为最优解。

**核心贪心策略**：
1. **边视角转换**：每条边的贡献由其两端点的较小权值决定，正确性基于无论删除顺序如何，总有一个端点会贡献较小值。
2. **正确性证明**：若某边的较大权值端点先被删除，则较小权值端点必然未被删除，贡献即为较小值。所有边独立处理，总和最小。

**可视化设计思路**：
- **动画方案**：以网格展示点和边，处理每条边时高亮，显示两端点权值并标记较小值累加。
- **复古像素风格**：用 8-bit 像素块表示点，边以线段连接，每次处理边时播放提示音，总积分动态更新。
- **交互功能**：步进控制、自动播放、音效反馈（正确选择音效、积分增长音效）。

---

### 题解清单（≥4星）

1. **无心揽青丝（5星）**  
   **关键亮点**：直接遍历所有边，累加两端点的较小值，代码简洁高效（O(m)），思路清晰。

2. **Prean（5星）**  
   **关键亮点**：同样采用边贡献策略，代码极简，明确问题本质，无需复杂数据结构。

3. **雄鹰展翅（5星）**  
   **关键亮点**：详细推导贪心正确性，代码直观，数学证明与样例结合，易理解。

---

### 最优思路提炼

**核心贪心逻辑**：  
每条边的最小贡献为两端点权值的较小值，总和即为答案。  
**实现关键**：直接遍历所有边，累加 `min(v[u], v[v])`，无需考虑删除顺序。

**代码片段**：
```cpp
ll ans = 0;
for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    ans += min(a[u], a[v]);
}
cout << ans;
```

---

### 同类型题与算法套路

**通用贪心场景**：  
- **边贡献独立**：当问题可分解为独立子问题（如边、区间）时，分别求最优。
- **最小化总和**：通过局部最优（如取较小值）达成全局最优。

**类似题目**：  
1. **区间调度问题**：选择不重叠区间的最大数量。
2. **最小生成树**：每次选择边权最小的边，避免环路。

---

### 推荐题目

1. **P1969 积木大赛**（贪心，独立区间贡献）  
2. **P1223 排队接水**（排序贪心，最小等待时间）  
3. **P1094 纪念品分组**（双指针贪心，配对最小化组数）

---

### 个人心得摘录

- **无心揽青丝**：  
  *“删边视角转化是突破口，直接规避复杂点顺序问题。”*  
- **雄鹰展翅**：  
  *“从数学证明入手，验证每条边的最优贡献，避免陷入点顺序的思维陷阱。”*

---

### 可视化与算法演示

**复古像素风格设计**：  
1. **初始化**：  
   - 点为 16x16 像素块，颜色按权值梯度变化。  
   - 边为灰色线段，选中时高亮为黄色。  
2. **动画流程**：  
   - 遍历每条边，显示 `min(u, v)`，播放“选择音效”。  
   - 总积分动态增长，背景音乐循环 8-bit 风格旋律。  
3. **交互功能**：  
   - 步进控制：空格键单步执行。  
   - 自动播放：Enter 键启动/暂停 AI 自动演示。  
   - 音效反馈：正确累加时播放清脆“叮”声，错误时低沉“哔”声。

**代码片段（Canvas 绘制边）**：  
```javascript
function drawEdge(u, v) {
    ctx.beginPath();
    ctx.moveTo(nodes[u].x, nodes[u].y);
    ctx.lineTo(nodes[v].x, nodes[v].y);
    ctx.strokeStyle = '#888';
    ctx.stroke();
}
```

---
处理用时：129.31秒