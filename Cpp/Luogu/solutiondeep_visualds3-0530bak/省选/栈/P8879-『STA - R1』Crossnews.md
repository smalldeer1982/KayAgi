# 题目信息

# 『STA - R1』Crossnews

## 题目背景

Informational problems make us better.

## 题目描述

定义两个序列 $\{a_n\}$，$\{b_n\}$ 的联合权值为
$$\operatorname{unval}(a,b)=\sum_{i=1}^nb_i(b_i-a_i)$$

现给定一个序列 $\{a_n\}$，求满足 $\operatorname{unval}(a,b)$ 最小的单调不减序列 $\{b\}$，只需输出 $\operatorname{unval}(a,b)$ 的值即可。

注意，$\{b\}$ 中的元素不一定要为整数。

## 说明/提示

提示：如果你不会做这道题，可以问问 [APJifengc](/user/279652)。
***

样例 1 解释：使得联合权值取到最小值的 $\{b\}$ 为 `0.5 1 1.5 2 2.5`。

***
数据范围和约定：
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n}\le & \textbf{分值} & \textbf{特殊性质}\\\hline
\textsf{1} & 100 & 10 & \textbf{无} \\\hline
\textsf{2} & 10^6 & 5 & \{a\}\textbf{ 全部相等} \\\hline
\textsf{3} & 10^6 & 5 & \{a\}\textbf{ 单调不减} \\\hline
\textsf{4} & 10^4 & 30 & \textbf{无} \\\hline
\textsf{5} & 10^6 & 50 & \textbf{无}
\\\hline\hline
\end{array}
$$

对于全部数据，有 $1\le n\le 10^6$，$|a_i|\le 10^3$。

***

评分规则：

本题使用 Special Judge，如果你的答案是 $pans$，标准答案是 $cans$，则你将获得
$$\min\Bigg\{100,\Bigg\lfloor\dfrac{0.1}{\min\Big\{|pans-cans|,\Big|\dfrac{|pans-cans|}{cans}\Big|\Big\}}\Bigg\rfloor\Bigg\}$$
分。

**每个 Subtask 内捆绑测试**。即取 Subtask 内得分最小的作为 Subtask 得分。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
-13.7500000```

## 样例 #2

### 输入

```
10
1000 1 2 8 9 5 4 1000 -40 1000```

### 输出

```
-403015.7500000```

# AI分析结果



## 算法分类
贪心算法 + 单调栈

## 综合分析与结论
### 核心思路
题目要求找到单调不减序列 $\{b\}$ 使 $\sum_{i=1}^n b_i(b_i-a_i)$ 最小。通过数学变形，问题转化为最小化 $\sum (b_i - \frac{a_i}{2})^2$。当 $\frac{a_i}{2}$ 单调不减时直接取 $b_i = \frac{a_i}{2}$；否则需合并相邻区间，使得每个区间的 $b$ 值取该区间的均值，并保证整体递增。

### 解决难点
1. **数学推导**：将原式转化为平方和最小问题，分离出固定项。
2. **贪心策略**：通过合并相邻不满足单调性的区间，保证每个区间平均值单调不减。
3. **高效实现**：使用单调栈维护区间的均值和长度，时间复杂度 $O(n)$。

### 核心算法流程
1. 将每个 $a_i$ 除以2得到 $A_i$。
2. 遍历 $A_i$，将当前元素作为新区间（长度1，值 $A_i$）入栈。
3. 检查栈顶两个区间是否满足单调性，若当前区间均值小于前一个，则合并，直到栈内区间均值单调递增。
4. 最终每个区间的均值即为对应位置的 $b$ 值。

### 可视化设计思路
- **动画展示**：每个元素入栈时显示为独立方块，合并时方块合并并更新颜色。栈结构动态变化，高亮当前操作区间。
- **颜色标记**：当前处理元素用红色，栈内区间用不同颜色区分，合并时显示合并动画。
- **音效提示**：合并时播放“咔嚓”音效，完成时播放成功音效，背景音乐为8位风格循环。

## 题解清单（≥4星）
1. **Thunder_S（5星）**  
   - 思路清晰，详细推导几何意义，代码简洁高效。
   - 关键亮点：利用几何直观解释合并策略，代码结构清晰。
2. **Otomachi_Una_（5星）**  
   - 数学证明严谨，代码可读性强。
   - 关键亮点：明确极长区间平均值的性质，代码逻辑严密。
3. **WRT_Partisan（4星）**  
   - 图文结合解释平面几何模型，代码易理解。
   - 关键亮点：可视化辅助理解，代码注释详细。

## 最优思路提炼
- **贪心合并**：将不满足单调性的区间合并为均值，保证全局单调性。
- **数学转换**：将原问题转化为最小化平方和，利用平均值性质。
- **单调栈维护**：高效处理区间合并，确保线性时间复杂度。

## 类似算法题目
1. **P1115 最大子段和**（贪心或动态规划）
2. **P2422 良好的序列**（区间合并与单调性维护）
3. **Largest Rectangle in Histogram（LeetCode 84）**（单调栈处理区间极值）

## 代码片段（核心逻辑）
```cpp
struct node { int len; double val; };
stack<node> st;

for (int i = 1; i <= n; ++i) {
    double a_i = a[i] / 2.0;
    node cur(1, a_i);
    while (!st.empty() && st.top().val > cur.val) {
        cur.len += st.top().len;
        cur.val = (cur.val * cur.len + st.top().val * st.top().len) / (cur.len + st.top().len);
        st.pop();
    }
    st.push(cur);
}
```

## 复古游戏化设计
- **像素风格**：用16色块表示区间，合并时块体增大，颜色渐变。
- **音效设计**：合并时触发“哔”声，错误操作播放低沉音效。
- **自动演示**：按步执行算法，右侧面板显示栈状态和当前操作。
- **积分系统**：每正确合并一次得分，连续合并触发连击奖励。

---

**可视化演示示例（伪代码）**  
```javascript
// 初始化 Canvas
const canvas = document.getElementById('animation');
const ctx = canvas.getContext('2d');
let stack = [];

function drawBlock(x, y, len, val) {
    // 绘制代表区间的方块，颜色根据 val 变化
}

function animateMerge() {
    // 合并栈顶元素，播放合并动画
}

// 自动演示循环
setInterval(() => {
    if (currentStep < n) {
        processNextElement();
        animateMerge();
    }
}, 1000);
```

---
处理用时：131.79秒