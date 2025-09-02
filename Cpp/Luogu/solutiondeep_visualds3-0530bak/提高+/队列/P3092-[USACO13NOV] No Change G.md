# 题目信息

# [USACO13NOV] No Change G

## 题目描述

Farmer John is at the market to purchase supplies for his farm.  He has in his pocket K coins (1 <= K <= 16), each with value in the range 1..100,000,000.  FJ would like to make a sequence of N purchases (1 <= N <= 100,000), where the ith purchase costs c(i) units of money (1 <= c(i) <= 10,000).  As he makes this sequence of purchases, he can periodically stop and pay, with a single coin, for all the purchases made since his last payment (of course, the single coin he uses must be large enough to pay for all of these).  Unfortunately, the vendors at the market are completely out of change, so whenever FJ uses a coin that is larger than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making his N purchases in sequence.  Output -1 if it is impossible for FJ to make all of his purchases.

约翰到商场购物，他的钱包里有K(1 <= K <= 16)个硬币，面值的范围是1..100,000,000。

约翰想按顺序买 N个物品(1 <= N <= 100,000)，第i个物品需要花费c(i)块钱，(1 <= c(i) <= 10,000)。

在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1


## 说明/提示

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.


FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases.  This leaves him with the 12-unit coin.


## 样例 #1

### 输入

```
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7 
```

### 输出

```
12 
```

# AI分析结果



# 算法分类
**状态压缩动态规划（状压DP）**

---

## 题解思路与核心难点分析
### 核心思路
1. **状态压缩**：由于硬币数 \( K \le 16 \)，用二进制状态表示硬币使用情况。  
   - 状态 `s` 的第 `i` 位为 1 表示第 `i` 枚硬币已被使用。
2. **状态定义**：`dp[s]` 表示使用状态 `s` 的硬币后，能买到的最远商品位置。
3. **转移方法**：
   - 枚举当前状态 `s`，尝试添加未使用的硬币 `j`。
   - 计算使用硬币 `j` 后能覆盖的连续商品范围，更新 `dp[s | (1<<j)]`。
4. **优化手段**：
   - **前缀和+二分**：快速计算硬币 `j` 能覆盖的最大商品范围（时间复杂度 \( O(\log N) \)）。
   - **双指针预处理**：预先计算每个硬币从每个位置开始的最大覆盖范围（时间复杂度 \( O(NK) \)）。

### 难点对比
| 方法              | 优点                          | 缺点                          |
|-------------------|-------------------------------|-------------------------------|
| 前缀和+二分       | 实现简单，代码易读            | 每次转移需二分，常数较大      |
| 双指针预处理      | 转移时 O(1) 查询，速度更快    | 预处理需额外空间和计算步骤    |

### 结论
- **最优思路**：双指针预处理法（如 Imakf 的题解），适用于 \( N \) 较大的场景。
- **关键技巧**：预处理每个硬币的覆盖范围，状态转移时直接查表。

---

## 题解评分（≥4星）
1. **jun1lesszZZ（★★★★☆）**  
   - **亮点**：清晰的状压DP框架+二分查找实现，注释详细。  
   - **改进点**：二分查找可优化为预处理。

2. **Imakf（★★★★★）**  
   - **亮点**：双指针预处理覆盖范围，时间复杂度 \( O(NK + 2^K K) \)，高效且代码简洁。  
   - **心得**：“用双指针搞，复杂度 \( O(NK) \)” —— 预处理优化思想。

3. **zjy111（★★★★☆）**  
   - **亮点**：使用 `bitset` 提升代码可读性，适合状压DP初学者。  
   - **心得**：“用 `bitset` 就不需要预处理，直接使用 `x.count()`” —— 强调代码简洁性。

---

## 最优思路代码实现
```cpp
// Imakf 的预处理+双指针法
int far[17][MX]; // far[i][j]: 硬币i从位置j开始能覆盖的最大右端点
for (int i = 1; i <= k; i++) { // 预处理每个硬币的覆盖范围
    int All = 0, r = 1;
    for (int j = 1; j <= n; j++) {
        while (r <= n && All + cost[r] <= coin[i]) 
            All += cost[r++];
        far[i][j] = r - 1;
        if (All) All -= cost[j]; // 左指针右移
    }
}
// 状态转移
for (int s = 0; s < (1<<k); s++) {
    for (int j = 1; j <= k; j++) {
        if ((s & (1<<(j-1))) || dp[s] >= n) continue;
        int new_s = s | (1<<(j-1));
        dp[new_s] = max(dp[new_s], far[j][dp[s] + 1]);
    }
}
```

---

## 相似题目推荐
1. **P1879 [Corn Fields]**：状压DP处理棋盘覆盖问题。
2. **P2831 [愤怒的小鸟]**：状压DP优化抛物线覆盖。
3. **P3959 [宝藏]**：状态压缩+最小生成树变种。

---

## 可视化与算法演示
### 动画设计
1. **状态压缩动态展示**：
   - **网格表示**：16位二进制状态以像素块显示，选中位高亮（黄色）。
   - **覆盖范围**：用颜色条标记当前状态能覆盖的商品区间（绿色为已覆盖）。
2. **双指针预处理**：
   - **硬币移动**：硬币图标从当前位置滑动到最远右端点，覆盖区域渐变色填充。
3. **音效与交互**：
   - **音效**：硬币选中（8-bit "coin" 音效），覆盖完成（胜利音效）。
   - **速度控制**：滑块调节动画速度，支持单步调试。

### 复古像素风格
- **调色板**：16色FC风格，硬币用红/蓝像素块，商品为绿色像素点。
- **Canvas 渲染**：每个商品为 8x8 像素块，状态网格动态更新。

---

## 个人心得
- **调试教训**：初始代码未处理 `sum[0] = 0`，导致二分查找错误。  
- **优化顿悟**：双指针替代二分，预处理时间换查询效率，适合高频查询场景。

---
处理用时：78.61秒