# 题目信息

# Table

## 题目描述

John Doe has an $ n×m $ table. John Doe can paint points in some table cells, not more than one point in one table cell. John Doe wants to use such operations to make each square subtable of size $ n×n $ have exactly $ k $ points.

John Doe wondered, how many distinct ways to fill the table with points are there, provided that the condition must hold. As this number can be rather large, John Doe asks to find its remainder after dividing by $ 1000000007 $ $ (10^{9}+7) $ .

You should assume that John always paints a point exactly in the center of some cell. Two ways to fill a table are considered distinct, if there exists a table cell, that has a point in one way and doesn't have it in the other.

## 说明/提示

Let's consider the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF232B/8876a3223960f71627c5d6c6a4c6ddb988dcaef6.png) The gray area belongs to both $ 5×5 $ squares. So, if it has one point, then there shouldn't be points in any other place. If one of the white areas has a point, then the other one also must have a point. Thus, there are about $ 20 $ variants, where the point lies in the gray area and $ 25 $ variants, where each of the white areas contains a point. Overall there are $ 45 $ variants.

## 样例 #1

### 输入

```
5 6 1
```

### 输出

```
45```

# AI分析结果



---

### 算法分类
**动态规划、组合数学**

---

### 题解思路与核心难点

#### **核心思路**
1. **等价类划分**：观察到每相隔 `n` 的列的点数必须相同，转化为处理前 `n` 列的等价类问题。
2. **组合数预处理**：计算每个列选 `t` 个点的组合数 `C(n, t)`，并预处理其幂次（出现次数）。
3. **动态规划**：定义 `dp[i][j]` 为前 `i` 列放置 `j` 个点的总方案数，转移时累加不同点数选择的贡献。

#### **解决难点**
- **列出现次数计算**：对每个列 `i`，计算其在 `m` 列中的出现次数 `cnt[i]`，利用数学公式快速求解。
- **组合数幂次优化**：通过快速幂预处理 `C(n, t)^cnt[i]`，避免重复计算。

---

### 题解评分（≥4星）

1. **MCAdam（★★★★☆）**
   - **亮点**：代码简洁，预处理快速幂优化到位，状态转移清晰。
   - **代码片段**：预处理 `fp[i][j]` 和动态规划三重循环。

2. **ZHR100102（★★★★☆）**
   - **亮点**：分组背包思路，优化空间使用，解释清晰。
   - **代码片段**：滚动数组优化，动态规划逆向枚举。

3. **feecle6418（★★★★☆）**
   - **亮点**：数学推导明确，预处理组合数幂次。
   - **代码片段**：直接计算 `cnt[i]`，快速幂预处理。

---

### 最优思路提炼
1. **等价类与循环节**：利用列循环性质，将大范围 `m` 列压缩为前 `n` 列处理。
2. **组合数幂次预处理**：快速计算 `C(n, t)` 的幂次，避免动态规划中重复计算。
3. **分组背包式DP**：将每列视为一组物品，每组选择不同点数，累加方案数。

---

### 同类型题推荐
1. **P3750 [六省联考 2017] 分手是祝愿**：组合数学与动态规划结合。
2. **P2523 [HAOI2011] Problem c**：大模数下的动态规划与组合计数。
3. **CF559C Gerald and Giant Chess**：组合数路径计数，动态规划优化。

---

### 代码核心实现
```cpp
// 预处理组合数
for (int i = 1; i <= n; i++) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; j++)
        C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
}

// 计算每个列的幂次
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
        ll cnt = (m-1)/n + (i <= (m-1)%n + 1);
        fp[i][j] = power(C[n][j], cnt);
    }
}

// 动态规划转移
f[0][0] = 1;
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= k; j++) {
        for (int t = 0; t <= min(j, n); t++) {
            f[i][j] = (f[i][j] + f[i-1][j-t] * fp[i][t]) % mod;
        }
    }
}
```

---

### 可视化设计
1. **像素风格动态规划演示**：
   - **网格展示**：用 `n×n` 网格表示列和点数选择，当前操作列高亮为红色。
   - **动态转移**：点击列时，展示组合数幂次和状态转移。
2. **音效与动画**：
   - **转移音效**：每次成功转移播放“滴”声。
   - **背景音乐**：8-bit 风格循环音乐。
3. **交互控制**：
   - **步进执行**：允许单步观察转移过程。
   - **参数调节**：动态调整 `n`、`m`、`k` 实时查看结果。

---

### 结论
通过等价类压缩和动态规划，将大范围问题转化为有限状态转移，结合组合数学预处理，高效求解方案数。

---
处理用时：117.70秒