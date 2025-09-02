# 题目信息

# Balanced Subsequences

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

You are given three integers $ n $ , $ m $ and $ k $ . Find the number of sequences consisting of $ n $ '(' and $ m $ ')', such that the longest balanced subsequence is of length $ 2 \cdot k $ . Since the answer can be large calculate it modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

For the first test case "()()", "(())" are the $ 2 $ sequences

For the second test case no sequence is possible.

For the third test case ")((()", ")(()(", ")()((", "())((" are the $ 4 $ sequences.

## 样例 #1

### 输入

```
3
2 2 2
3 2 3
3 2 1```

### 输出

```
2
0
4```

# AI分析结果



---

## 算法分类  
组合数学（卡特兰数变体）

---

## 题解思路、算法要点与解决难点  
### **核心思路**  
1. **问题转化**：将括号序列视为折线路径，左括号为向右上移动 (`y+1`)，右括号为向右下移动 (`y-1`)。  
2. **最长平衡条件**：最长平衡子序列长度为 `2k` ⇨ 折线最低点纵坐标为 `k-m`（`m`为右括号总数）。  
3. **容斥原理**：统计最低点 ≤ `k-m` 的路径数 `f(k)` 和 `f(k-1)`，最终答案为 `f(k)-f(k-1)`。  
4. **反射对称法**：将触碰 `y=k-m` 的路径关于该线对称，转化为自由路径计数问题，直接得到组合数公式。  

### **算法实现**  
- **组合数预计算**：预处理 `C(n+m, k)` 的模数组合表。  
- **公式直接求解**：答案公式为 `C(n+m, k) - C(n+m, k-1)`。  

### **解决难点**  
- **最低点条件转化为路径计数**：通过反射法避免复杂的动态规划。  
- **组合数差的意义**：利用容斥排除最低点更小的路径。  

---

## 题解评分 (≥4星)  
1. **UnyieldingTrilobite（5星）**  
   - 思路清晰，直接推导反射法核心公式。  
   - 代码极简，仅需组合数差。  
2. **OrezTsim（5星）**  
   - 折线模型与代码对应明确，注释完整。  
   - 预处理组合数提高效率。  
3. **zifanwang（4星）**  
   - 正确实现反射法，但解释较简略。  

---

## 最优思路/技巧提炼  
**关键技巧**：  
1. **反射法（安德鲁斯反射原理）**：将受限路径问题转化为自由路径计数。  
2. **容斥原理**：通过 `f(k)-f(k-1)` 精确统计最低点恰为 `k-m` 的路径数。  

**代码实现核心**：  
```cpp
int ans = (C(n+m, k) - C(n+m, k-1) + MOD) % MOD;
```

---

## 类似算法套路  
- **卡特兰数路径计数**：如 [CF1295D](https://codeforces.com/problemset/problem/1295/D) 的 Möbius 容斥。  
- **受限格点路径**：需不越过对角线的路径统计。  

---

## 推荐相似题目  
1. **P1641 [SCOI2010]生成字符串**：类似折线模型与组合数。  
2. **P1044 栈**：卡特兰数经典问题。  
3. **CF1781F Bracket Insertion**：动态规划与概率结合。  

---

## 个人心得摘录  
- **UnyieldingTrilobite**：“将折线最后一次触碰直线后的部分反转，这是卡特兰数的经典操作。”  
- **OrezTsim**：“调试时注意 `k > min(n,m)` 的边界判断，否则组合数越界。”  

---

## 可视化与算法演示  
### **动画设计**  
1. **折线路径绘制**：  
   - 初始点 `(0,0)`，逐字符绘制右上（左括号）或右下（右括号）线段。  
   - **高亮**触碰 `y=k-m` 的路径段，反转后部分用不同颜色（如红色）。  
2. **反射对称演示**：  
   - 点击“反射”按钮时，将路径后半段关于 `y=k-m` 对称翻转，显示新终点 `(n+m, 2k-n-m)`。  
3. **组合数统计面板**：实时显示 `C(n+m,k)` 和 `C(n+m,k-1)` 的值及其差。  

### **复古像素风格**  
- **8位色盘**：使用深蓝（路径）、亮绿（反转段）、灰色（背景网格）。  
- **音效**：  
  - 移动时播放“哔”声（8-bit 方波）。  
  - 计算完成时播放胜利音效（短旋律）。  

### **交互控制**  
- **步进/暂停**：逐步展示路径构建与反射过程。  
- **自动模式**：AI 自动生成合法路径并标记触碰事件。  

---

**示例代码（核心反射逻辑）**  
```javascript
// Canvas 绘制路径反转（伪代码）
function reflectPath(path, yLine) {
  let reflected = path.slice(lastTouchIndex);
  reflected.forEach(point => {
    point.y = 2 * yLine - point.y; // 对称翻转
  });
  drawPath(reflected, 'red'); // 红色高亮
}
```

---
处理用时：58.81秒