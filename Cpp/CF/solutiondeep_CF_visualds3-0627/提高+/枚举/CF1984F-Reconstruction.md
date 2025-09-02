# 题目信息

# Reconstruction

## 题目描述

There is a hidden array $ a_1, a_2, \ldots, a_n $ of length $ n $ whose elements are integers between $ -m $ and $ m $ , inclusive.

You are given an array $ b_1, b_2, \ldots, b_n $ of length $ n $ and a string $ s $ of length $ n $ consisting of the characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{?} $ .

For each $ i $ from $ 1 $ to $ n $ inclusive, we must have:

- If $ s_i = \texttt{P} $ , $ b_i $ is the sum of $ a_1 $ through $ a_i $ .
- If $ s_i = \texttt{S} $ , $ b_i $ is the sum of $ a_i $ through $ a_n $ .

Output the number of ways to replace all $ \texttt{?} $ in $ s $ with either $ \texttt{P} $ or $ \texttt{S} $ such that there exists an array $ a_1, a_2, \ldots, a_n $ with elements not exceeding $ m $ by absolute value satisfying the constraints given by the array $ b_1, b_2, \ldots, b_n $ and the string $ s $ .

Since the answer may be large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, we can see that the following array satisfies all constraints, thus the answer is $ 1 $ :

1. $ \texttt{P} $ — $ {[\color{red}{\textbf{1}},3,4,2]} $ : sum of $ 1 $ .
2. $ \texttt{S} $ — $ {[1,\color{red}{\textbf{3},4,2}]} $ : sum of $ 9 $ .
3. $ \texttt{P} $ — $ {[\color{red}{1,3,\textbf{4}},2]} $ : sum of $ 8 $ .
4. $ \texttt{P} $ — $ {[\color{red}{1,3,4,\textbf{2}}]} $ : sum of $ 10 $ .

In the second test case, it can be shown that no array $ a $ with all $ |a_i| \leq m = 10^9 $ satisfies all constraints.

## 样例 #1

### 输入

```
6
4 10
PSPP
1 9 8 10
4 1000000000
????
1 1 1 4000000000
8 1000000000
?P?SSP?P
-857095623 -1424391899 -851974476 673437144 471253851 -543483033 364945701 -178537332
4 7
PPSS
4 2 1 3
9 20
?????????
1 2 3 4 5 6 7 8 9
3 1000000000
P??
-145463248 -974068460 -1287458396```

### 输出

```
1
0
2
1
14
1```

# AI分析结果



---

**唯一算法分类**：动态规划

---

### **综合分析与结论**

#### **核心思路**
所有题解均采用**动态规划 (DP)** 解决。关键在于确定隐藏数组 $a$ 的总和 $sum$，通过枚举可能的 $sum$ 值（如 $b_i + b_{i+1}$ 或端点值），结合 DP 统计合法方案数。核心步骤如下：
1. **确定 $sum$ 的可能值**：根据 `PS` 相邻的位置或端点条件，枚举所有可能的 $sum$。
2. **动态规划转移**：定义状态 $f_{i,0/1}$ 表示前 $i$ 个字符中，第 $i$ 位为 `P` 或 `S` 的方案数。转移时检查相邻字符组合（`PP`、`PS`、`SP`、`SS`）的约束条件，确保每个 $a_i$ 的绝对值不超过 $m$。

#### **解决难点**
- **$sum$ 的确定**：需枚举所有可能的 $sum$ 并验证其合法性。
- **状态转移的条件约束**：不同字符组合对应不同的 $a_i$ 计算公式，需在转移时动态检查范围限制。

#### **可视化设计**
- **动画流程**：
  1. **枚举 $sum$**：逐个高亮可能的 $sum$ 值（如 `b[i]+b[i+1]`），标记其来源位置。
  2. **DP 状态转移**：
     - 用网格展示每个位置 $i$ 的两种状态（`P/S`），颜色标记当前处理的位置（如绿色）。
     - 当相邻字符组合满足约束时，绘制箭头表示转移路径，红色箭头表示无效转移（条件不满足），蓝色表示有效。
  3. **结果统计**：在右侧面板实时更新当前 $sum$ 对应的合法方案数。

- **复古游戏化效果**：
  - **8位像素风格**：用 16 色调色板渲染字符网格，`P` 为蓝色方块，`S` 为红色，`?` 为灰色。
  - **音效**：转移成功时播放短促“滴”声，失败时播放低音；累计方案数时播放上扬音调。
  - **自动演示模式**：按顺序播放每个 $sum$ 的 DP 过程，用户可暂停或调整速度。

---

### **题解清单 (≥4星)**

1. **作者：_fairytale_ (5星)**
   - **亮点**：简洁的预处理（添加虚拟首尾字符），通过 `PS` 确定 $sum$，代码逻辑清晰，边界处理严谨。
   - **关键代码**：
     ```cpp
     rep(_,0,n) {
       if (ch[_] == 'S' || ch[_+1] == 'P') continue;
       ll sum = b[_] + b[_+1];
       // DP 转移逻辑
     }
     ```

2. **作者：Fesdrer (4星)**
   - **亮点**：显式列出所有可能的 $sum$，转移条件分情况讨论详细。
   - **关键代码**：
     ```cpp
     for (int _=1; _<=n+1; _++) {
       sum = b[_] + b[_-1];
       // 初始化与转移
     }
     ```

3. **作者：happybob (4星)**
   - **亮点**：使用 `set` 去重优化枚举，转移条件用 Lambda 表达式封装。
   - **关键代码**：
     ```cpp
     set<ll> sum;
     for (int i=1; i<n; i++) sum.insert(b[i]+b[i+1]);
     sum.insert(b[1]); sum.insert(b[n]);
     ```

---

### **最优思路与技巧提炼**

1. **关键思路**：
   - **枚举 $sum$**：所有可能的 $sum$ 值由相邻 `PS` 或端点确定。
   - **状态压缩**：仅需记录前一位的状态 (`P/S`) 即可转移。

2. **实现技巧**：
   - **预处理边界**：在字符串首尾添加虚拟字符 `P` 和 `S`，简化边界条件判断。
   - **约束检查**：在转移时直接计算 $a_i$ 并检查其范围，避免显式构造 $a$ 数组。

---

### **同类型题与算法套路**

- **通用解法**：动态规划结合约束条件检查，常用于计数类问题（如合法路径数、方案数统计）。
- **类似题目**：
  1. **洛谷 P1357 食物链**：状态转移与条件约束结合。
  2. **LeetCode 639. Decode Ways II**：字符替换与方案数统计。
  3. **Codeforces 1325E. Ehab's REAL Number Theory Problem**：枚举关键变量后的动态规划。

---

### **推荐洛谷题目**
1. **P1357**：动态规划与状态压缩。
2. **P2657 [SCOI2009] windy数**：数位 DP 与约束检查。
3. **P1140 相似基因**：字符串匹配与动态规划。

---

### **个人心得摘录**
- **调试教训**（来自 _fairytale_）：初始代码未处理虚拟首尾字符的冲突情况，导致部分测试用例失败。通过添加 `if (ch[_] == 'S' || ch[_+1] == 'P') continue;` 解决。
- **优化技巧**（来自 happybob）：用 `set` 存储 $sum$ 避免重复计算，减少 DP 次数。

---

### **代码片段（核心逻辑）**
```cpp
// 来自 _fairytale_ 的 DP 转移逻辑
rep(i, 1, n+1) {
  f[i][0] = f[i][1] = 0;
  if (ch[i] != 'S') {
    // PP 转移
    if (abs(b[i] - b[i-1]) <= m) add(f[i][0], f[i-1][0]);
    // SP 转移
    ll mx = b[i] + b[i-1] - sum;
    if (abs(mx) <= 2*m) add(f[i][0], f[i-1][1]);
  }
  if (ch[i] != 'P') {
    // PS 转移
    if (b[i-1] + b[i] == sum) add(f[i][1], f[i-1][0]);
    // SS 转移
    if (abs(b[i] - b[i-1]) <= m) add(f[i][1], f[i-1][1]);
  }
}
```

---
处理用时：98.33秒