# 题目信息

# MEXimize the Score

## 题目描述

Suppose we partition the elements of an array $ b $ into any number $ k $ of non-empty multisets $ S_1, S_2, \ldots, S_k $ , where $ k $ is an arbitrary positive integer. Define the score of $ b $ as the maximum value of $ \operatorname{MEX}(S_1) $ $ ^{\text{∗}} $ $  + \operatorname{MEX}(S_2) + \ldots + \operatorname{MEX}(S_k) $ over all possible partitions of $ b $ for any integer $ k $ .

Envy is given an array $ a $ of size $ n $ . Since he knows that calculating the score of $ a $ is too easy for you, he instead asks you to calculate the sum of scores of all $ 2^n - 1 $ non-empty subsequences of $ a $ . $ ^{\text{†}} $ Since this answer may be large, please output it modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ $ \operatorname{MEX} $ of a collection of integers $ c_1, c_2, \ldots, c_k $ is defined as the smallest non-negative integer $ x $ that does not occur in the collection $ c $ . For example, $ \operatorname{MEX}([0,1,2,2]) = 3 $ and $ \operatorname{MEX}([1,2,2]) = 0 $

 $ ^{\text{†}} $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deleting several (possibly, zero or all) elements.

## 说明/提示

In the first testcase, we must consider seven subsequences:

- $ [0] $ : The score is $ 1 $ .
- $ [0] $ : The score is $ 1 $ .
- $ [1] $ : The score is $ 0 $ .
- $ [0,0] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,0,1] $ : The score is $ 3 $ .

 The answer for the first testcase is $ 1+1+2+2+2+3=11 $ .In the last testcase, all subsequences have a score of $ 0 $ .

## 样例 #1

### 输入

```
4
3
0 0 1
4
0 0 1 1
5
0 0 1 2 2
4
1 1 1 1```

### 输出

```
11
26
53
0```

# AI分析结果



**算法分类**：组合数学

---

### **题解思路与核心难点**

#### **问题转化与核心公式**
对于每个子序列，其score为各数i的前缀最小值之和：
$$
\text{score} = \sum_{i=0}^{n-1} \min_{j \leq i} c_j
$$
其中$c_j$为子序列中j的出现次数。目标是统计所有子序列的score之和。

#### **动态规划与组合数学**
- **状态设计**：定义$f[i][j]$表示前i种数值的前缀最小值为j时的方案数，$ans[i]$为对应分数总和。
- **转移方程**：
  - **方案数转移**：分两种情况：当前数取的数量不小于之前的j，或当前数取的数量更小。
  - **分数转移**：当前数的贡献为j乘以其方案数，并继承之前分数的加权和。
- **组合数优化**：预处理组合数与后缀和，加速状态转移。

#### **难点对比**
- **Exp10re**：通过动态维护前缀最小值的最小有效值，利用后缀和优化转移。
- **Zeoykkk**：直接计算每个子序列的前缀最小值贡献，利用组合数乘积处理方案数。
- **Luzhuoyuan**：枚举每个数值i的最小可能值，结合前缀组合数乘积和后缀2的幂次。

---

### **最优思路提炼**
- **前缀最小值贡献法**：每个数值i的贡献由其前缀最小值决定，利用动态规划维护有效状态。
- **组合数与后缀和优化**：预处理组合数，用后缀和数组快速计算方案数，将时间复杂度优化至$O(n)$。

---

### **关键代码实现**
```cpp
// 组合数预处理
void comb_init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
    inv[n] = qpow(fac[n], mod-2);
    for (int i = n-1; i >= 0; --i) inv[i] = inv[i+1] * (i+1) % mod;
}

// DP转移核心
vector<vector<ll>> dp(n + 5);
for (int i = 0; i < n; ++i) {
    int m = min(m, c[i]);
    dp[i].resize(m + 1);
    for (int j = 0; j <= m; ++j) {
        ll way1 = (s[j + 1] * binom(c[i], j)) % mod;
        ll way2 = (binom_sum[j] * dp_prev[j]) % mod;
        dp[i][j] = (way1 + way2) % mod;
    }
    // 更新后缀和数组s
}
```

---

### **同类型题目推荐**
1. **CF1540B Tree Array**：组合数学与期望计算。
2. **Luogu P3773 组合数问题**：模意义下组合数性质。
3. **CF1392F Omkar and Landslide**：前缀最小值与动态规划。

---

### **可视化设计**
- **动画方案**：以横向进度条表示数值0到n-1的遍历，每个数值i处显示当前前缀最小值j及对应方案数。
- **颜色高亮**：当前处理的数值用红色标记，有效j值用绿色高亮，组合数计算步骤分步显示。
- **复古像素风格**：用Canvas绘制进度条和数值块，音效在状态转移时触发8-bit音效。

---

### **题解评分（≥4星）**
1. **Exp10re（5星）**：思路清晰，后缀和优化巧妙，代码可读性强。
2. **Zeoykkk（4星）**：组合数乘积处理直观，但代码复杂度较高。
3. **Luzhuoyuan（4星）**：枚举最小值贡献，结合前缀后缀优化，实现简洁。

---

**总结**：通过前缀最小值的动态规划与组合数优化，将问题转化为高效计算方案数的总和，核心在于状态转移的设计与数学推导的巧妙结合。

---
处理用时：63.43秒