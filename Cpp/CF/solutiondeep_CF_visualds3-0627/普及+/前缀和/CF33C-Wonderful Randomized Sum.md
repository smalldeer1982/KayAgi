# 题目信息

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 样例 #1

### 输入

```
3
-1 -2 -3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
-4 2 0 5 0
```

### 输出

```
11
```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2
```

### 输出

```
18
```

# AI分析结果



**唯一算法分类**：最大子段和（Kadane算法）

---

### **题解思路与算法要点**
#### **核心推导**
1. **数学转化**：通过观察发现，前缀和后缀的交叉部分会被翻转两次（等价于不翻转）。设原总和为 `sum`，中间未翻转段的和为 `C`，则翻转后的总和可推导为 `2C - sum`。
2. **最大子段和**：问题转化为求原数组的最大子段和 `C`（允许空子段，此时 `C=0`），最终答案由公式 `2*C - sum` 直接计算。

#### **解决难点**
- **思维跳跃**：将操作转化为中间段的选择需要数学直觉，需突破常规的「翻转前后缀」思维。
- **空子段处理**：当全为负数时，最优策略是翻转整个数组，此时最大子段和为 `0`。

#### **关键实现**
- **Kadane算法**：动态维护当前子段和 `cur_sum`，当 `cur_sum < 0` 时重置为 `0`，最终 `max_sum` 即为最大子段和。

---

### **题解评分（≥4星）**
1. **LuckyCloud（★★★★★）**  
   - **亮点**：数学推导清晰，代码简洁高效，时间复杂度 `O(n)`，空间 `O(1)`。
   - **代码**：直接计算最大子段和并应用公式，可读性强。
   
2. **Z_M__（★★★★★）**  
   - **亮点**：变量命名更直观，代码逻辑与推导完全对应，适合教学。
   - **代码片段**：
     ```cpp
     int mx = 0, mid = -inf;
     for (int i=0; i<n; i++) {
         mx = max(mx + x, 0);
         mid = max(mid, mx);
     }
     ```

3. **_lxy_（★★★★☆）**  
   - **亮点**：代码极简，核心逻辑仅需 10 行，适合竞赛快速编码。
   - **优化点**：注释较少，但逻辑自洽。

---

### **最优思路与技巧**
- **数学转化**：将操作问题转化为求最大子段和的数学模型。
- **空子段处理**：通过重置 `cur_sum` 为 `0` 允许空子段，应对全负数情况。
- **Kadane算法模板**：动态维护当前和与最大和，实现线性时间复杂度。

---

### **类似题目推荐**
1. **P1115 最大子段和**  
   - 直接应用 Kadane 算法的模板题。
2. **P2642 双子序列最大和**  
   - 需分割数组为两段独立子段，拓展思维。
3. **P1121 环状最大子段和**  
   - 处理环状数组，需结合首尾拼接与普通最大子段和。

---

### **可视化与算法演示**
#### **动画设计**
- **像素风格**：数组元素以 8-bit 方块表示，绿色表示当前子段，红色表示历史最大子段。
- **关键步骤**：
  1. 遍历数组，动态更新当前子段和（绿色方块扩展或重置）。
  2. 更新最大子段和时触发音效（短促“叮”声）。
  3. 最终结果以闪烁黄色方块展示，背景音乐切换为胜利音效。
- **交互功能**：支持暂停/继续、速度调节，可单步观察 `cur_sum` 和 `max_sum` 变化。

#### **代码片段（Canvas 绘制）**
```javascript
function drawArray(ctx, arr, maxSumIndex) {
  for (let i = 0; i < arr.length; i++) {
    ctx.fillStyle = i <= maxSumIndex ? '#00FF00' : '#FF0000';
    ctx.fillRect(i * 30, 100 - arr[i], 25, 25);
  }
}
```

---

### **个人心得**
- **调试经验**：初始未考虑空子段导致全负数用例错误，通过重置 `cur_sum` 修复。
- **思维突破**：意识到中间段可空是解题关键，数学推导需跳出操作细节。

---
处理用时：199.33秒