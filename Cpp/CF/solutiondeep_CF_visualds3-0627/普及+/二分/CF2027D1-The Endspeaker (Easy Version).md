# 题目信息

# The Endspeaker (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is that you only need to output the minimum total cost of operations in this version. You must solve both versions to be able to hack.

You're given an array $ a $ of length $ n $ , and an array $ b $ of length $ m $ ( $ b_i > b_{i+1} $ for all $ 1 \le i < m $ ). Initially, the value of $ k $ is $ 1 $ . Your aim is to make the array $ a $ empty by performing one of these two operations repeatedly:

- Type $ 1 $ — If the value of $ k $ is less than $ m $ and the array $ a $ is not empty, you can increase the value of $ k $ by $ 1 $ . This does not incur any cost.
- Type $ 2 $ — You remove a non-empty prefix of array $ a $ , such that its sum does not exceed $ b_k $ . This incurs a cost of $ m - k $ .

You need to minimize the total cost of the operations to make array $ a $ empty. If it's impossible to do this through any sequence of operations, output $ -1 $ . Otherwise, output the minimum total cost of the operations.

## 说明/提示

In the first test case, one optimal sequence of operations which yields a total cost of $ 1 $ is as follows:

- Perform an operation of type $ 2 $ . Choose the prefix to be $ [9] $ . This incurs a cost of $ 1 $ .
- Perform an operation of type $ 1 $ . The value of $ k $ is now $ 2 $ . This incurs no cost.
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3, 4] $ . This incurs a cost of $ 0 $ .
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3] $ . This incurs a cost of $ 0 $ .
- The array $ a $ is now empty, and the total cost of all operations is $ 1 $ .

In the second test case, it's impossible to remove any prefix of the array since $ a_1 > b_1 $ , so array $ a $ cannot be made empty by any sequence of operations.

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1```

### 输出

```
1
-1
2
10
4```

# AI分析结果



**算法分类**  
二分  

---

### **题解思路与算法要点**  
本题核心是动态规划结合二分查找。由于操作二中删除的前缀越大，后续操作越少，总花费可能更优。各题解普遍采用以下思路：  
1. **状态设计**：`dp[i][k]` 表示处理到数组 `a` 的前 `i` 项且当前 `k` 值对应的最小花费。  
2. **转移策略**：  
   - **操作一**：直接增加 `k`，即 `dp[i][k+1] = min(dp[i][k])`。  
   - **操作二**：删除尽可能长的前缀，通过二分查找或双指针找到满足 `sum ≤ b[k]` 的最大前缀结束位置。  
3. **优化手段**：利用前缀和快速计算子数组和，二分查找优化转移位置搜索。  

**解决难点**：  
- **高效查找转移点**：通过二分查找在 `O(log n)` 时间内定位可删除的最大前缀。  
- **状态转移优化**：部分题解使用双指针代替二分，利用单调性将时间复杂度降至 `O(nm)`。  

---

### **题解评分（≥4星）**  
1. **Super_Cube（4.5星）**  
   - 思路清晰，二维DP状态易理解。  
   - 代码简洁，利用 `upper_bound` 实现二分查找。  
   - 时间复杂度 `O(nm log n)`，适合大部分数据范围。  

2. **灵乌路空（5星）**  
   - 双指针优化将时间降至 `O(nm)`，显著提升效率。  
   - 滚动数组节省空间，代码实现高效。  
   - 状态转移设计巧妙，结合单调性避免重复计算。  

3. **Yorg（4星）**  
   - 明确状态设计与转移方程，理论分析到位。  
   - 复杂度分析详细，但未给出代码实现。  

---

### **最优思路与技巧提炼**  
1. **双指针优化转移**：  
   - 维护窗口 `[l, r]`，随着 `r` 递增调整 `l`，保证 `sum[r]-sum[l-1] ≤ b[k]`。  
   - 避免二分查找，降低常数时间。  
2. **滚动数组**：仅保留当前 `k` 和上一层的状态，空间复杂度降至 `O(n)`。  
3. **前缀和预处理**：快速计算子数组和，为二分或双指针提供基础。  

---

### **同类型题与算法套路**  
1. **二分答案**：如「寻找有序数组中第一个大于目标的位置」（模板题）。  
2. **双指针优化DP**：常见于子数组和限制问题，如「最长连续子数组和不超过k」。  
3. **动态规划状态压缩**：通过滚动数组或状态合并减少空间。  

---

### **推荐题目**  
1. **P1182 数列分段 II**（二分答案）  
2. **P2280 激光炸弹**（前缀和+动态规划）  
3. **P1090 合并果子**（贪心+优先队列，类似操作选择优化）  

---

### **可视化与算法演示**  
**核心二分过程动画设计**：  
1. **初始化**：绘制数组 `a` 的前缀和曲线，标记当前 `k` 值对应的 `b[k]`。  
2. **二分步骤**：  
   - **区间高亮**：以不同颜色标记 `left`、`right`、`mid`。  
   - **条件判断**：显示 `sum[mid]` 与 `b[k]` 的比较结果，收缩区间。  
   - **结果标记**：找到最大前缀后，用闪烁效果突出该区间。  
3. **复古像素风格**：  
   - **8位音效**：区间更新时播放“哔”声，找到结果时播放“叮”声。  
   - **Canvas绘制**：网格显示前缀和，像素块表示区间变化。  

**代码片段（灵乌路空的双指针优化）**：  
```cpp
for (int i = 1; i <= m; ++ i, now ^= 1) {
    for (int r = 1, l = 1; r <= n; ++ r) {
        while (l <= r && sum[r] - sum[l - 1] > b[i]) ++ l;
        if (l <= r) f[now][r] = min(f[now][r], f[now][l - 1] + m - i);
    }
}
```

---

### **总结**  
本题通过动态规划结合二分或双指针，高效解决了前缀删除与状态转移问题。双指针优化显著提升性能，滚动数组降低空间消耗，是此类问题的经典解法。

---
处理用时：74.85秒