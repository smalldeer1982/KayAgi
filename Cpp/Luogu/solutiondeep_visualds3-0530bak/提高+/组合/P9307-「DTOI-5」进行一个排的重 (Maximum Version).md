# 题目信息

# 「DTOI-5」进行一个排的重 (Maximum Version)

## 题目背景

**本题与 Minimum Version 的区别是所求最值和数据范围不同。**

小 L 热衷于重排数列使之规整。

## 题目描述

小 L 有一个长为 $n$ 的序列 $a$，其中每一项 $a_i$ 都是一个 pair $(p_i, q_i)$。

为了让 $a$ 看起来规整一些，他钦定 $p, q$ 分别均为长为 $n$ 的排列。

为了对 $a$ 的规整程度进行量化计算，他给出了一个权值函数 $f(a) = \displaystyle\sum_{i = 1}^n ([p_i > \max_{j = 1}^{i - 1} p_j] + [q_i > \max_{j = 1}^{i - 1} q_j])$。**注意 $i = 1$ 时两个方括号都能取到值，因为我们认为 $\displaystyle\max_{j = 1}^0 p_j = \displaystyle\max_{j = 1}^0 q_j = -\infty$。**

为了让 $a$ 看起来更加规整，他决定分别以某种方式重排 $a$ 得到 $a'$ 使得 $f(a')$ 最大。**注意重排时必须将 $a'_i = (p'_i, q'_i)$ 视为整体。**

他希望你求出 $f(a')_{\max}$ 的值，以及分别有多少个 $a'$ 可以取到 $f(a')_{\max}$。

由于方案数可能很大，你只需要求出结果对 $998244353$ 取模的值。

## 说明/提示

**【数据范围】**

$$
\def\or{\operatorname{or}}
%\def\arrayscretch{1.5}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask}&n\le &\textbf{Points}\cr\hline
\sf1&10&10 \operatorname{pts}\cr\hline
\sf2&50&20 \operatorname{pts}\cr\hline
\sf3&500&20 \operatorname{pts}\cr\hline
\sf4&2\times 10^3&20 \operatorname{pts}\cr\hline
\sf5&/&30 \operatorname{pts}\cr\hline
\end{array}
$$
对于 $100\%$ 的数据，$1 \leq n \leq 10^4$，$1 \leq p_i, q_i \leq n$，保证 $p, q$ 均为**排列**。

## 样例 #1

### 输入

```
5
1 5 2 4 3
1 4 2 5 3```

### 输出

```
9 2```

# AI分析结果



### 唯一算法分类
**动态规划（LIS 变种）**

---

### 综合分析与结论
#### 核心思路与难点
1. **问题转化**  
   将 pair 按 `p` 升序排列后，`p` 的贡献固定为 `n`（每个元素均为前缀最大）。此时只需最大化 `q` 的贡献，转化为求排序后 `q` 序列的 **最长递增子序列（LIS）长度**。总最大值为 `n + LIS长度`。
   
2. **方案数计算**  
   利用动态规划统计所有可能的 LIS 组合，并结合组合数学计算插入非关键元素的合法方案数。关键点在于对 LIS 元素的拓扑排序和组合数插板法的应用。

#### 可视化设计
- **核心动画**：将排序后的 `q` 序列以网格形式展示，逐步构建 LIS：
  - **当前处理元素**：高亮为红色，动态显示是否加入 LIS。
  - **LIS 路径**：用绿色箭头标记递增关系。
  - **组合数插板**：以蓝色方块表示可插入的非关键元素位置。
- **音效与交互**：
  - **成功扩展 LIS**：播放上扬音效。
  - **插入元素**：播放轻微点击音效。
  - **步进控制**：允许单步观察 LIS 构建和插板过程。

---

### 题解清单（≥4星）
#### [Leasier 的题解] ⭐⭐⭐⭐⭐
- **亮点**：高效转化为 LIS 问题，时间复杂度 `O(n²)`，代码逻辑清晰。
- **关键代码**：
  ```cpp
  sort(pr + 1, pr + n + 1); // 按 p 升序排列
  for (int i = 1; i <= n; i++) 
      for (int j = 1; j < i; j++) 
          if (pr[i].second > pr[j].second) 
              dp1[i] = max(dp1[i], dp1[j]); // 计算 LIS
  ```
- **心得**：通过调整策略证明每个元素至少贡献 `p` 或 `q`，确保最优性。

---

### 最优思路提炼
1. **排序定界**：按 `p` 升序排列固定其贡献，问题简化为 `q` 的 LIS。
2. **组合插板**：非 LIS 元素需插入不影响前缀最大值的位置，利用组合数计算合法插入方式。
3. **逆向 DP**：从后往前统计 LIS 的方案数，结合前缀和优化加速。

---

### 类似题目推荐
1. **P1020**（导弹拦截）：经典 LIS 问题。
2. **P1439**（最长公共子序列）：转化为 LIS 模型。
3. **P4303**（基因匹配）：双序列匹配的 LIS 扩展。

---

### 可视化代码片段（JS）
```javascript
// 绘制排序后的 q 序列和 LIS 构建
function drawLIS(qArray, LIS) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < qArray.length; i++) {
        if (LIS.includes(i)) ctx.fillStyle = '#00ff00'; // LIS 元素绿色
        else ctx.fillStyle = '#666'; 
        ctx.fillRect(i * 30, 100 - qArray[i] * 5, 25, 25);
    }
}
// 音效触发（Web Audio API）
function playSound(freq) {
    const oscillator = audioCtx.createOscillator();
    oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
    oscillator.connect(audioCtx.destination);
    oscillator.start(); oscillator.stop(audioCtx.currentTime + 0.1);
}
```

---

### 复古像素风设计
- **调色板**：8 位经典绿、红、蓝、灰。
- **动画流程**：
  1. 像素方块表示 `q` 元素，绿色为 LIS 元素。
  2. 红色闪烁标记当前比较的元素。
  3. 蓝色插板位置动态生成，音效同步。
- **自动演示**：模拟 LIS 构建和插板过程，每步延迟可调。

---
处理用时：114.03秒