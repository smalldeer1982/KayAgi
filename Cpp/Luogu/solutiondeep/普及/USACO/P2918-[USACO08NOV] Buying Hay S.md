# 题目信息

# [USACO08NOV] Buying Hay S

## 题目描述

Farmer John is running out of supplies and needs to purchase H (1 <= H <= 50,000) pounds of hay for his cows.

He knows N (1 <= N <= 100) hay suppliers conveniently numbered 1..N. Supplier i sells packages that contain P\_i (1 <= P\_i <= 5,000) pounds of hay at a cost of C\_i (1 <= C\_i <= 5,000) dollars. Each supplier has an unlimited number of packages available, and the packages must be bought whole.

Help FJ by finding the minimum cost necessary to purchase at least H pounds of hay.

约翰的干草库存已经告罄，他打算为奶牛们采购 $H(1 \leq H \leq 50000)$ 磅干草。

他知道 $N(1 \leq N\leq 100)$ 个干草公司，现在用 $1$ 到 $N$ 给它们编号。第 $i$ 公司卖的干草包重量为 $P_i (1 \leq P_i \leq 5,000)$ 磅，需要的开销为 $C_i (1 \leq C_i \leq 5,000)$ 美元。每个干草公司的货源都十分充足， 可以卖出无限多的干草包。

帮助约翰找到最小的开销来满足需要，即采购到至少 $H$ 磅干草。

## 说明/提示

FJ can buy three packages from the second supplier for a total cost of 9.


## 样例 #1

### 输入

```
2 15 
3 2 
5 3 
```

### 输出

```
9 
```

# AI分析结果



### 综合分析与结论
本题核心是完全背包的变形，难点在于处理“至少 H 磅”的条件。各题解主要围绕以下思路展开：
1. **完全背包框架**：将干草包视为物品，重量为体积，花费为价值，求解最小价值。
2. **容量扩展技巧**：将背包容量上限设为 `H + 5000`（单包重量最大值），覆盖所有可能更优的超额购买情况。
3. **状态转移优化**：动态规划时从 `H` 到 `H + 5000` 取最小值，确保答案正确性。

关键优化点在于容量扩展，避免因“恰好装满”限制而遗漏更优解。

---

### 高星题解推荐

#### 1. CCF_zkskyer（⭐⭐⭐⭐⭐）
- **核心亮点**：  
  - 明确解释容量扩展的必要性（覆盖“超过 H 但更便宜”的情况）。
  - 代码结构清晰，包含详细注释，适合初学者理解。
- **代码核心**：
  ```cpp
  for (int j = weight[i]; j <= h + Max; j++)
      f[j] = min(f[j], f[j - weight[i]] + val[i]);
  for (int i = h; i <= h + Max; i++)
      Min = min(Min, f[i]);
  ```
- **个人心得**：  
  作者强调初始化时需将 `f` 数组设为极大值，避免状态转移错误。

#### 2. EarthGiao（⭐⭐⭐⭐）
- **核心亮点**：  
  - 通过反证法证明容量扩展上限为 `H + 5000` 的合理性。
  - 提供完整代码及变量命名规范，增强可读性。
- **代码核心**：
  ```cpp
  for (int i = 1; i <= n; i++)
      for (int j = p[i]; j <= h + 5000; j++)
          bb[j] = min(bb[j], bb[j - p[i]] + c[i]);
  ```

#### 3. YosemiteHe（⭐⭐⭐⭐）
- **核心亮点**：  
  - 直接对比完全背包模板，突出最小值处理的差异。
  - 代码简洁，适合快速复习完全背包框架。
- **代码核心**：
  ```cpp
  for (int j = a[i]; j <= h + 5000; j++)
      dp[j] = min(dp[j], dp[j - a[i]] + b[i]);
  ```

---

### 关键代码实现
**核心逻辑**：动态规划求解最小花费。
```cpp
memset(f, 0x3f, sizeof(f)); // 初始化为极大值
f[0] = 0; // 0 磅花费为 0
for (int i = 1; i <= n; i++) {
    for (int j = p[i]; j <= h + 5000; j++) {
        f[j] = min(f[j], f[j - p[i]] + c[i]);
    }
}
int ans = *min_element(f + h, f + h + 5001);
```

---

### 拓展与相似题目
1. **完全背包基础**：[P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)  
2. **条件转换思维**：[P1510 精卫填海](https://www.luogu.com.cn/problem/P1510)（类似“体积作为价值”的转换）  
3. **多重约束优化**：[P1853 投资的最大化](https://www.luogu.com.cn/problem/P1853)（结合容量扩展与价值最大化）

---
处理用时：75.87秒