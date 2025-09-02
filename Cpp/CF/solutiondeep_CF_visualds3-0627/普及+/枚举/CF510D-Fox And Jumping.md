# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果



**唯一算法分类**：动态规划（状压DP与map优化）

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
题目转化为选择若干卡片，使其长度的最大公约数（GCD）为1，且总费用最小。数学基础为裴蜀定理，多个数的GCD为1时可组合得到任意整数。

#### **关键算法对比**
1. **状压DP（ZYF_B）**：
   - **质因数分解**：每个数的质因数最多9个，状态压缩至2^9。
   - **状态定义**：`f[s]`表示质因数集合为s时的最小费用，通过合并新卡片的质因数状态更新。
   - **优化点**：质因数分解减少状态数，时间复杂度O(n²·2^9)。

2. **Map动态规划（Kohakuwu）**：
   - **状态维护**：用`map`维护每个GCD值的最小费用，遍历现有状态与新卡片计算新GCD。
   - **实现简洁**：无需预处理质因数，直接处理所有可能的GCD值，时间复杂度依赖于状态数。

3. **Dijkstra算法（fanfansann）**：
   - **图论模型**：将GCD视为节点，费用为边权，求从0到1的最短路径。
   - **优先队列**：按费用贪心扩展，保证最先找到最优解。

#### **解决难点**
- **状态爆炸**：通过质因数分解（状压DP）或动态剪枝（map）控制状态数。
- **数学转化**：将跳跃问题转换为数论中的GCD问题，需深入理解裴蜀定理。

---

### **题解评分（≥4星）**
1. **ZYF_B（5星）**  
   - **亮点**：质因数分解+状压DP，时间复杂度明确，优化思路清晰。代码结构严谨，预处理分解质因数。
   - **核心代码**：质因数状态转移与费用更新。

2. **Kohakuwu（4星）**  
   - **亮点**：map实现简洁，无需复杂预处理。适合快速实现，但理论复杂度较高。
   - **核心代码**：遍历map并更新GCD费用。

3. **fanfansann（4星）**  
   - **亮点**：图论视角创新，Dijkstra算法直观展示状态转移。利用优先队列优化搜索顺序。

---

### **最优思路或技巧提炼**
- **状压DP优化**：质因数分解将状态压缩至可控范围，适用于数论问题。
- **Map动态规划**：灵活处理未知状态，适合状态数不确定的问题。
- **Dijkstra贪心策略**：适用于最短路径类问题，确保最优解优先扩展。

---

### **同类型题或算法套路**
- **GCD+动态规划**：如洛谷P1891（疯狂LCM）、CF510D（类似本题）。
- **状压质因数**：适用于需处理因数分解的优化问题，如质数覆盖问题。

---

### **推荐相似题目**
1. **洛谷P1891**：需利用GCD性质进行动态规划。
2. **CF510D**：几乎相同题型，可练习map优化。
3. **洛谷P1441**：质因数分解与状态压缩结合。

---

### **个人心得摘录**
- **调试经验**：质因数分解需处理重复因子（如平方数），分解后排序避免状态冲突。
- **优化教训**：map中重复插入同一GCD时需判断最小值，否则状态数爆炸。

---

### **可视化与算法演示**
#### **动画方案（状压DP）**
1. **网格绘制**：每个卡片显示其质因数，状态用二进制位表示。
2. **颜色标记**：
   - **当前卡片**：高亮质因数（如红色）。
   - **状态更新**：绿色表示费用降低，黄色表示新状态。
3. **步进控制**：单步展示质因数交集计算，状态位变化。
4. **像素风格**：8位像素字体显示状态和费用，音效提示状态更新。

#### **复古游戏化设计**
- **Canvas动画**：卡片为像素块，质因数用不同颜色方块排列。
- **音效**：
  - **状态更新**：8位“哔”声。
  - **找到解**：经典通关音效。
- **自动演示**：AI模拟状压DP流程，逐步展开质因数合并。

---

### **代码片段（状压DP核心逻辑）**
```cpp
for(int i=1; i<=n; i++) {
    memset(f,0x3f,sizeof(f));
    int M = 1<<cnt[i];
    f[M-1] = cost[i]; // 初始状态（选中所有质因数）
    for(int j=1; j<=n; j++) {
        if(i == j) continue;
        int s = 0;
        // 计算卡片j的质因数交集
        for(int k=1; k<=cnt[i]; k++) {
            for(int x=1; x<=cnt[j]; x++) {
                if(g[i][k] == g[j][x]) s |= (1<<(k-1));
            }
        }
        // 状态转移
        for(int k=0; k<M; k++) {
            f[k & s] = min(f[k & s], f[k] + cost[j]);
        }
    }
    ans = min(ans, f[0]); // 最终状态为无质因数（GCD=1）
}
```

---

### **总结**
状压DP通过质因数分解高效压缩状态，是本题最优解法；map方法灵活但理论复杂度高，适合快速实现。可视化设计可结合像素风格与步进演示，增强算法理解。

---
处理用时：119.27秒