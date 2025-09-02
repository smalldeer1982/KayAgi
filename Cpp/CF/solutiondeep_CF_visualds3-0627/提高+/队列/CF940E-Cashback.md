# 题目信息

# Cashback

## 题目描述

Since you are the best Wraith King, Nizhniy Magazin «Mir» at the centre of Vinnytsia is offering you a discount.

You are given an array $ a $ of length $ n $ and an integer $ c $ .

The value of some array $ b $ of length $ k $ is the sum of its elements except for the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF940E/7767e68a87566f0732f029bd691b100b0a741ae2.png) smallest. For example, the value of the array $ [3,1,6,5,2] $ with $ c=2 $ is $ 3+6+5=14 $ .

Among all possible partitions of $ a $ into contiguous subarrays output the smallest possible sum of the values of these subarrays.

## 说明/提示

In the first example any partition yields 6 as the sum.

In the second example one of the optimal partitions is $ [1,1],[10,10,10,10,10,10,9,10,10,10] $ with the values 2 and 90 respectively.

In the third example one of the optimal partitions is $ [2,3],[6,4,5,7],[1] $ with the values 3, 13 and 1 respectively.

In the fourth example one of the optimal partitions is $ [1],[3,4,5,5,3,4],[1] $ with the values 1, 21 and 1 respectively.

## 样例 #1

### 输入

```
3 5
1 2 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
12 10
1 1 10 10 10 10 10 10 9 10 10 10
```

### 输出

```
92
```

## 样例 #3

### 输入

```
7 2
2 3 6 4 5 7 1
```

### 输出

```
17
```

## 样例 #4

### 输入

```
8 4
1 3 4 5 5 3 4 1
```

### 输出

```
23
```

# AI分析结果



**唯一算法分类**：动态规划 + 单调队列优化

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
1. **最优分割性质**：任何长度大于等于 `c` 的子数组均可拆分为多个长度为 `c` 的子数组，使得总贡献更优。因此，最优解只需考虑分割成长度为 `1` 或 `c` 的子数组。
2. **动态规划定义**：设 `dp[i]` 为前 `i` 个元素的最小贡献值。转移时有两种选择：
   - **单独成段**：`dp[i] = dp[i-1] + a[i]`
   - **以 `c` 长度成段**（当 `i >= c` 时）：`dp[i] = dp[i-c] + (区间和) - (区间最小值)`
3. **区间最小值预处理**：使用单调队列维护滑动窗口最小值，高效计算每个长度为 `c` 的子数组的最小值。

#### **解决难点**
- **贪心策略证明**：通过数学推导证明分割为 `c` 长度的子数组不会劣于其他分割方式。
- **高效维护区间最小值**：单调队列在 `O(n)` 时间内预处理所有长度为 `c` 的区间最小值。

---

### **题解评分 (≥4星)**

1. **Alarm5854 (5星)**  
   - **亮点**：思路清晰，推导严谨；代码简洁，使用单调队列高效预处理；注释明确，可读性高。
   - **代码**：动态规划与单调队列完美结合，预处理和转移逻辑紧凑。

2. **Plozia (4星)**  
   - **亮点**：代码简洁，包含详细注释；动态规划转移方程明确。
   - **不足**：缺少对贪心策略的详细推导。

3. **wwlw (4星)**  
   - **亮点**：反向思路（最大化删除值），代码简洁；动态规划转移方程直观。
   - **不足**：变量命名可读性稍差。

---

### **最优思路或技巧提炼**

1. **贪心分割策略**：仅考虑长度为 `1` 或 `c` 的子数组，避免复杂分割情况。
2. **单调队列优化**：滑动窗口最小值预处理，时间复杂度 `O(n)`，空间复杂度 `O(n)`。
3. **动态规划状态转移**：通过前缀和快速计算区间和，结合预处理的最小值进行转移。

#### **代码片段**
```cpp
// 单调队列预处理区间最小值
int h = 1, t = 0;
for (int i = 1; i <= n; ++i) {
    while (h <= t && q[h] + c <= i) h++; // 维护窗口左边界
    while (h <= t && a[q[t]] >= a[i]) t--; // 保持队列单调递增
    q[++t] = i;
    minn[i] = a[q[h]]; // 当前窗口的最小值
}

// 动态规划转移
for (int i = 1; i < c; ++i) dp[i] = dp[i-1] + a[i];
for (int i = c; i <= n; ++i) {
    dp[i] = min(dp[i-1] + a[i], dp[i-c] + (sum[i] - sum[i-c] - minn[i]));
}
```

---

### **同类型题或类似算法套路**

1. **滑动窗口最值**：如 [Sliding Window Maximum (LeetCode 239)](https://leetcode.com/problems/sliding-window-maximum/)。
2. **动态规划分段优化**：如 [Minimum Cost to Cut a Stick (LeetCode 1547)](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)，利用区间最值优化分段决策。
3. **贪心策略结合DP**：如 [Best Time to Buy and Sell Stock with Cooldown (LeetCode 309)](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)，通过状态机简化决策。

---

### **推荐相似题目**

1. **洛谷 P1886 滑动窗口**  
   - **考察点**：单调队列维护滑动窗口最值。

2. **洛谷 P1043 数字游戏**  
   - **考察点**：动态规划结合区间分割，需维护区间最值。

3. **洛谷 P1273 有线电视网**  
   - **考察点**：树形动态规划，需结合子树分割策略。

---

### **可视化与算法演示**

#### **动画设计**
1. **像素风格界面**：  
   - 使用 8-bit 像素风格绘制数组元素，每个元素显示为方块，颜色区分当前操作（如红色表示当前窗口，绿色表示最小值）。
2. **滑动窗口动态演示**：  
   - 显示单调队列的进出过程，队列元素用不同颜色标记，窗口移动时高亮覆盖区域。
3. **动态规划状态转移**：  
   - 用箭头连接 `dp[i-c]` 和 `dp[i]`，显示转移时的区间和与最小值扣除。

#### **交互功能**
- **步进控制**：支持暂停/继续，调整动画速度观察单调队列变化。
- **音效反馈**：窗口滑动时播放“滴”声，最小值更新时播放“咔”声，增强操作感知。

#### **示例代码（Canvas 绘制）**
```javascript
// 绘制数组元素（伪代码）
function drawArray(ctx, arr, c, currentIndex) {
    for (let i = 0; i < arr.length; i++) {
        ctx.fillStyle = (i >= currentIndex - c && i <= currentIndex) ? "#FF0000" : "#00FF00";
        ctx.fillRect(i * 30, 100, 25, 25);
        ctx.fillText(arr[i], i * 30 + 5, 120);
    }
}
```

---

### **个人心得摘录**

- **Alarm5854**：  
  > “通过分析区间合并与分割的优劣，发现最优解仅由长度为 `1` 或 `c` 的子数组构成，避免了对复杂情况的处理。”

- **Plozia**：  
  > “动态规划的关键在于定义状态和转移方程，而单调队列的预处理让复杂问题变得简洁高效。”

---

### **总结**

本题核心在于结合贪心策略与动态规划，通过单调队列优化区间最值预处理，实现高效求解。可视化设计通过复古像素风格和交互式步进控制，帮助理解滑动窗口和动态规划的关键步骤。

---
处理用时：89.67秒