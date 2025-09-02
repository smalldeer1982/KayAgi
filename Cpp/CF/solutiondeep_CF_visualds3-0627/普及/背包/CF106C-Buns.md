# 题目信息

# Buns

## 题目描述

Lavrenty, a baker, is going to make several buns with stuffings and sell them.

Lavrenty has $ n $ grams of dough as well as $ m $ different stuffing types. The stuffing types are numerated from 1 to $ m $ . Lavrenty knows that he has $ a_{i} $ grams left of the $ i $ -th stuffing. It takes exactly $ b_{i} $ grams of stuffing $ i $ and $ c_{i} $ grams of dough to cook a bun with the $ i $ -th stuffing. Such bun can be sold for $ d_{i} $ tugriks.

Also he can make buns without stuffings. Each of such buns requires $ c_{0} $ grams of dough and it can be sold for $ d_{0} $ tugriks. So Lavrenty can cook any number of buns with different stuffings or without it unless he runs out of dough and the stuffings. Lavrenty throws away all excess material left after baking.

Find the maximum number of tugriks Lavrenty can earn.

## 说明/提示

To get the maximum number of tugriks in the first sample, you need to cook 2 buns with stuffing 1, 4 buns with stuffing 2 and a bun without any stuffing.

In the second sample Lavrenty should cook 4 buns without stuffings.

## 样例 #1

### 输入

```
10 2 2 1
7 3 2 100
12 3 1 10
```

### 输出

```
241```

## 样例 #2

### 输入

```
100 1 25 50
15 5 20 10
```

### 输出

```
200```

# AI分析结果



# 算法分类
**动态规划（多重背包问题）**

---

## 综合分析与结论

### 核心思路与难点
题目要求用有限的面团和馅料制作包子，求最大收益。核心思路为动态规划，具体为多重背包模型：
1. **物品拆分**：每个馅料类型视为多重背包中的物品，数量为 `a_i / b_i`（最多能做的包子数），体积为 `c_i`，价值为 `d_i`。
2. **无馅包子处理**：视为一种特殊物品，数量为 `n / c0`，体积为 `c0`，价值为 `d0`。
3. **状态设计**：`dp[i]` 表示恰好使用 `i` 克面团时的最大收益。需在最后遍历所有 `dp[i]` 取最大值，确保剩余面团无法使用时也能找到最优解。

### 题解对比
- **0x3F 的解法**：将无馅包子作为初始状态，其他馅料拆分为 0-1 背包处理。时间复杂度较低，代码简洁。
- **StupidSeven 的解法**：二维 DP 处理，最后计算剩余面团的无馅包子收益。思路直观但复杂度较高。
- **Yeji_ 的解法**：直接初始化无馅包子，其他馅料按多重背包处理。代码简洁但初始化可能不全面。
- **Victorique 的解法**：类似多重背包，但初始化方式不同。

### 最优思路提炼
1. **多重背包转化**：将每个馅料拆分为多个独立物品，每个物品对应一次制作。
2. **无馅包子初始化**：预先计算所有可能的无馅包子组合，作为 DP 初始状态。
3. **逆向更新**：使用一维 DP 数组，逆向更新以避免重复计算。

---

## 题解清单（≥4星）

### 0x3F（★★★★★）
- **亮点**：一维 DP 逆向更新，代码简洁高效，时间复杂度低。
- **关键代码**：
  ```cpp
  for (int i = 1; i <= n/c; i++) dp[i*c] = i*d; // 初始化无馅包子
  while (m--) {
      // 处理每个馅料
      for (int t = 1; t <= a/b; t++) {
          for (int i = n; i >= c; i--) {
              dp[i] = max(dp[i], dp[i-c] + d);
          }
      }
  }
  ```

### Yeji_（★★★★）
- **亮点**：直接处理多重背包，代码可读性强。
- **关键代码**：
  ```cpp
  for (int i=c0; i<=n; i++) f[i] = i/c0*d0; // 无馅包子初始化
  for (int i=1; i<=m; i++) {
      // 拆分物品为 0-1 背包
      for (int j=1; j<=a[i]/b[i]; j++) {
          for (int k=n; k>=c[i]; k--) {
              f[k] = max(f[k], f[k-c[i]] + d[i]);
          }
      }
  }
  ```

### StupidSeven（★★★★）
- **亮点**：二维状态明确，最后处理剩余面团的无馅包子。
- **关键代码**：
  ```cpp
  for (int k=1; k<=m; k++) {
      for (int now=0; now<=n; now++) {
          for (int i=0; i*b[k]<=a[k] && i*c[k]<=now; i++) {
              dp[k][now] = max(dp[k][now], dp[k-1][now-i*c[k]] + i*d[k]);
          }
      }
  }
  // 计算剩余面团的无馅包子价值
  for (int i=0; i<=n; i++) ans = max(ans, dp[m][i] + (n-i)/c0*d0);
  ```

---

## 同类型题与算法套路
- **多重背包问题**：如 [洛谷 P1776 宝物筛选](https://www.luogu.com.cn/problem/P1776)。
- **资源分配优化**：如 [洛谷 P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)。
- **动态规划状态设计**：如 [洛谷 P1541 乌龟棋](https://www.luogu.com.cn/problem/P1541)。

---

## 可视化与算法演示

### 动态规划状态更新动画
1. **网格展示**：以 `n` 为横轴，`dp[i]` 为纵轴，动态显示每次更新后的值。
2. **颜色标记**：当前更新的 `i` 值高亮为黄色，转移来源 `i-c` 标记为绿色。
3. **音效提示**：每次更新成功时播放清脆音效，最终答案出现时播放胜利音效。

### 复古像素风格设计
- **8位调色板**：面团用棕色，馅料用红色，DP 值用蓝色渐变。
- **Canvas 动画**：每次背包更新时，对应面团位置“闪烁”显示价值变化。
- **自动演示模式**：AI 逐步选择最优解，类似贪吃蛇自动寻路。

---

## 核心代码实现（0x3F 解法）
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, c, d, dp[1010], ans;
int main() {
    cin >> n >> m >> c >> d;
    // 初始化无馅包子
    for (int i = 1; i <= n/c; i++) 
        dp[i*c] = i*d;
    // 处理每个馅料
    while (m--) {
        cin >> a >> b >> c >> d;
        int cnt = a / b; // 最多能做 cnt 个
        for (int t = 1; t <= cnt; t++) 
            for (int i = n; i >= c; i--)
                dp[i] = max(dp[i], dp[i - c] + d);
    }
    // 找最大值（可能剩余面团未使用）
    for (int i = 1; i <= n; i++) 
        ans = max(ans, dp[i]);
    cout << ans << endl;
    return 0;
}
```

---
处理用时：204.45秒