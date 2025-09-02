# 题目信息

# [USACO11JAN] Profits S

## 题目描述

The cows have opened a new business, and Farmer John wants to see how well they are doing. The business has been running for N (1 <= N <= 100,000) days, and every day i the cows recorded their net profit P\_i (-1,000 <= P\_i <= 1,000).

Farmer John wants to find the largest total profit that the cows have made during any consecutive time period. (Note that a consecutive time period can range in length from one day through N days.) Help him by writing a program to calculate the largest sum of consecutive profits.


奶牛们开始了新的生意，它们的主人约翰想知道它们到底能做得多好。这笔生意已经做了N（1≤N≤100,000）天，每天奶牛们都会记录下这一天的利润Pi（-1,000≤Pi≤1,000）。


约翰想要找到奶牛们在连续的时间期间所获得的最大的总利润。（注：连续时间的周期长度范围从第一天到第N天）。


请你写一个计算最大利润的程序来帮助他。


## 说明/提示

The maximum sum is obtained by taking the sum from the second through the sixth number (4, 9, -2, -5, 8) => 14.

感谢@smartzzh 提供的翻译。


## 样例 #1

### 输入

```
7 
-3 
4 
9 
-2 
-5 
8 
-3 
```

### 输出

```
14 
```

# AI分析结果



# 算法分类
线性DP

---

# 题解思路与算法要点

## 核心思路
所有题解均围绕 **最大子段和** 问题展开，核心解法为动态规划或贪心。核心状态转移方程为：  
`dp[i] = max(nums[i], dp[i-1] + nums[i])`  
其中 `dp[i]` 表示以第 `i` 个元素结尾的最大子段和。  

### 动态规划解法（主流）
1. **状态定义**  
   `dp[i]` 表示以第 `i` 天为结尾的连续时间段的最大利润和。
2. **状态转移**  
   - 若前一天的 `dp[i-1]` 为负，则从当前天重新开始累加  
   - 若前一天的 `dp[i-1]` 为正，则继续累加当前天的利润  
3. **空间优化**  
   仅需维护前一天的 `dp` 值，空间复杂度从 `O(n)` 优化到 `O(1)`  

### 贪心解法
1. **滑动窗口思想**  
   维护当前累加和 `current_sum`，若其变为负数则重置为0，因为负数累加会拖累后续结果。  
2. **全负数处理**  
   额外记录全局最大值，若所有利润为负，则直接取最大单日利润。

### 解决难点
- **负数的处理**：动态规划中需保证初始值为极小负数，贪心中需单独处理全负场景  
- **空间优化**：通过滚动变量替代数组存储历史状态  
- **代码简洁性**：合并输入与状态更新步骤，实现单循环完成计算  

---

# 题解评分（≥4星）

### 1. QianianXY（★★★★☆）
- **亮点**：代码极简，输入与状态更新合并，空间复杂度 `O(1)`  
- **优化**：边读入边处理，无需额外数组存储原始数据  
- **代码片段**：  
  ```cpp
  for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      a[i] = max(a[i], a[i] + a[i-1]);  // 状态转移
      ans = max(a[i], ans);              // 实时更新最大值
  }
  ```

### 2. Y15BeTa（★★★★★）
- **亮点**：空间优化到极致，仅用变量 `temp` 代替 `dp` 数组  
- **关键注释**：明确提示全负数场景的陷阱（第三个测试点）  
- **代码片段**：  
  ```cpp
  for (int i=1; i<=n; i++) {
      int x; scanf("%d", &x);
      temp = max(temp+x, x);   // 滚动更新 dp 值
      ans = max(ans, temp);    // 维护全局最大值
  }
  ```

### 3. In_blue（★★★★☆）
- **亮点**：贪心思路清晰，通过布尔变量处理全负数场景  
- **可读性**：变量命名明确（`Max` 记录全局最大，`bol` 判断是否有正数）  
- **代码片段**：  
  ```cpp
  if (t < 0) t = 0;           // 负数则重置累加和
  Max = max(Max, t);           // 更新最大值
  if (a[i] > 0) bol = 1;       // 标记存在正数
  ```

---

# 最优思路提炼
1. **动态规划核心公式**  
   ```cpp
   current = max(nums[i], current + nums[i]);
   max_sum = max(max_sum, current);
   ```
2. **贪心优化点**  
   - 累加和为负时立即重置  
   - 全负数场景需取最大单元素值  

---

# 类似算法题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   **相似点**：完全相同的问题，可直接套用代码  
2. [P2642 双子序列最大和](https://www.luogu.com.cn/problem/P2642)  
   **扩展点**：需分割序列为两段，求各自最大子段和之和  
3. [P1121 环状最大子段和](https://www.luogu.com.cn/problem/P1121)  
   **变体**：序列首尾相连，需处理环形结构  

---

# 个人心得摘录
- **Y15BeTa**：  
  > "WA了第三个点之后看看题才发现不能一天都不选，因此状态转移方程不可以误写为 `dp[i] = max(0, dp[i-1]+a[i])`"  
  **总结**：初始化 `ans` 必须为极小值，不能默认0。

- **光和热**：  
  > "ans 初值要足够小，不能是0"  
  **教训**：未考虑全负数时需取最小负值而非0。

---

# 可视化与算法演示

## 动态规划动画设计
1. **网格绘制**  
   - 每个单元格表示 `dp[i]` 的值  
   - 背景色渐变：数值越大颜色越暖（如绿→黄→红）  
2. **状态转移高亮**  
   - 当前单元格高亮闪烁  
   - 箭头从 `dp[i-1]` 指向 `dp[i]`，标注 `max(a[i], a[i]+dp[i-1])`  
3. **实时最大值追踪**  
   - 最大子段和的单元格边框加粗显示金色  
   - 侧边栏动态更新 `max_sum` 数值  

## 复古像素风格实现
```javascript
// Canvas绘制核心逻辑（伪代码）
function drawDPGrid() {
  for (let i = 0; i < n; i++) {
    // 绘制16x16像素块，颜色按dp值映射
    ctx.fillStyle = getColor(dp[i]);
    ctx.fillRect(i * 20, 0, 16, 16);
    
    // 高亮当前处理的位置
    if (i === currentStep) {
      ctx.strokeStyle = "#FFD700"; // 金色边框
      ctx.strokeRect(i * 20, 0, 16, 16);
    }
  }
}
```

## 音效设计
- **状态更新**：8-bit "哔"声（Web Audio API合成）  
- **找到新最大值**：上升音阶（C→E→G）  
- **重置累加和**：低音鼓声  

---

# 题解完整代码（最优版本）
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int n, temp = 0, ans = -0x7fffffff;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x; scanf("%d", &x);
        temp = max(temp + x, x);    // 核心状态转移
        ans = max(ans, temp);       // 更新全局最大值
    }
    printf("%d\n", ans);
    return 0;
}
```

---
处理用时：68.20秒