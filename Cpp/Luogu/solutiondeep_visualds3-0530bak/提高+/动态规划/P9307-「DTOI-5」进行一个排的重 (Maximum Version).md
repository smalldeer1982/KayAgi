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



0. **题目翻译**

---

# 「DTOI-5」进行一个排的重（Maximum Version）

## 题目背景

**本题与 Minimum Version 的区别是所求最值和数据范围不同。**

小 L 热衷于重排数列使之规整。

## 题目描述

小 L 有一个长为 $n$ 的序列 $a$，其中每一项 $a_i$ 都是一个二元组 $(p_i, q_i)$。

为了让 $a$ 看起来规整，他规定 $p, q$ 各自都是长为 $n$ 的排列。

量化规则定义为权值函数 $f(a) = \sum_{i=1}^n ([p_i > \max_{j=1}^{i-1} p_j] + [q_i > \max_{j=1}^{i-1} q_j])$。**注意当 $i=1$ 时，两个方括号都能取到值，因为我们认为 $\max_{j=1}^0 p_j = \max_{j=1}^0 q_j = -\infty$。**

小 L 希望通过重排 $a$ 得到 $a'$ 使得 $f(a')$ 最大。**重排时必须将每个 $(p'_i, q'_i)$ 视为整体。**

你需要求出 $f(a')_{\max}$ 的值及取到该值的方案数，对 $998244353$ 取模。

## 输入输出样例

### 输入
```
5
1 5 2 4 3
1 4 2 5 3
```

### 输出
```
9 2
```

---

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**

### 核心思路
将序列按 $p$ 升序排列后，问题转化为求 $q$ 序列的最长递增子序列（LIS）。最大贡献值为 $n + \text{LIS长度}$，方案数通过组合计数与动态规划结合的方式计算。

### 状态转移设计
- **LIS 计算**：线性 DP 求最长递增子序列长度
- **方案数 DP**：从后往前统计满足 LIS 条件的组合数，利用前缀和优化

### 可视化设计
**动画方案**：
1. 将排序后的 $q$ 序列以像素方块展示，LIS 元素用绿色高亮
2. DP 矩阵更新时，用黄色光晕标记当前更新的状态
3. 转移路径用蓝色箭头动态绘制

**复古风格**：
- 8-bit 音效：状态转移时播放电子音，找到 LIS 元素时播放金币音效
- Canvas 网格：每个状态对应 16x16 像素块，背景循环播放芯片音乐

**AI 演示**：
- 自动模式逐步展开 LIS 计算过程，关键步骤暂停 0.5 秒
- 错误路径播放低沉蜂鸣声，正确转移播放清脆提示音

---

3. **题解清单 (≥4星)**

**Leasier 题解（★★★★★）**
- 亮点：将双维度问题降维至 LIS，组合数学优化方案数计算
- 关键代码段：
```cpp
sort(pr + 1, pr + n + 1); // 按 p 升序排列
for (int i = 1; i <= ni; i++) { // LIS 计算
    for (int j = 1; j < i; j++)
        if (pr[i].second > pr[j].second) 
            dp1[i] = max(dp1[i], dp1[j]);
    dp1[i]++;
}
```

---

4. **代码实现核心**

**LIS 计算与组合优化**
```cpp
// 排序后处理 q 序列
sort(pr + 1, pr + n + 1);

// 计算 LIS 长度
for (int i = 1; i <= n + 1; i++) {
    for (int j = 1; j < i; j++) {
        if (pr[j].second < pr[i].second)
            dp1[i] = max(dp1[i], dp1[j]);
    }
    dp1[i]++;
}

// 方案数 DP
for (int i = n; i >= 0; i--) {
    for (int j = i + 1; j <= n + 1; j++) {
        if (pr[j].second > pr[i].second && dp1[j] == dp1[i] + 1) {
            int t = get_sum(1, i-1, pr[i].second+1, pr[j].second-1);
            dp2[i] = (dp2[i] + dp2[j] * comb(t + get_sum(i+1, j-1, 1, pr[i].second), t)) % mod;
        }
    }
}
```

---

5. **同类型题目**
- P1020 导弹拦截（LIS 模板）
- P1439 【模板】最长公共子序列（排列转化技巧）
- P3005 [USACO10DEC] Cow Tennis G（组合计数与DP结合）

---

6. **可视化代码片段**

```javascript
// Canvas 绘制 LIS 过程
function drawDPGrid() {
    ctx.clearRect(0, 0, width, height);
    for (let i = 0; i < n; i++) {
        const x = (i % 10) * 20 + 50;
        const y = Math.floor(i / 10) * 20 + 50;
        ctx.fillStyle = isLISMember[i] ? '#00ff00' : '#8888ff';
        ctx.fillRect(x, y, 18, 18);
        if (i === currentHighlight) { // 高亮当前操作元素
            ctx.strokeStyle = '#ffff00';
            ctx.lineWidth = 3;
            ctx.strokeRect(x-2, y-2, 22, 22);
        }
    }
}
```

---
处理用时：76.85秒