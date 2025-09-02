# 题目信息

# Girl Permutation

## 题目描述

Some permutation of length $ n $ is guessed.

You are given the indices of its prefix maximums and suffix maximums.

Recall that a permutation of length $ k $ is an array of size $ k $ such that each integer from $ 1 $ to $ k $ occurs exactly once.

Prefix maximums are the elements that are the maximum on the prefix ending at that element. More formally, the element $ a_i $ is a prefix maximum if $ a_i > a_j $ for every $ j < i $ .

Similarly, suffix maximums are defined, the element $ a_i $ is a suffix maximum if $ a_i > a_j $ for every $ j > i $ .

You need to output the number of different permutations that could have been guessed.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

## 说明/提示

The following permutations are suitable for the second set of input data:

- $ [1, 4, 3, 2] $
- $ [2, 4, 3, 1] $
- $ [3, 4, 2, 1] $

The following permutations are suitable for the sixth set of input data:

- $ [2, 1, 6, 5, 3, 4] $
- $ [3, 1, 6, 5, 2, 4] $
- $ [3, 2, 6, 5, 1, 4] $
- $ [4, 1, 6, 5, 2, 3] $
- $ [4, 2, 6, 5, 1, 3] $
- $ [4, 3, 6, 5, 1, 2] $
- $ [5, 1, 6, 4, 2, 3] $
- $ [5, 2, 6, 4, 1, 3] $
- $ [5, 3, 6, 4, 1, 2] $
- $ [5, 4, 6, 3, 1, 2] $

## 样例 #1

### 输入

```
6
1 1 1
1
1
4 2 3
1 2
2 3 4
3 3 1
1 2 3
3
5 3 4
1 2 3
2 3 4 5
20 5 4
1 2 3 4 12
12 13 18 20
6 2 3
1 3
3 4 6```

### 输出

```
1
3
1
0
317580808
10```

# AI分析结果



**唯一算法分类**: 组合数学

---

### 题解思路与解决难点

#### **核心思路**
1. **最大值位置验证**：必须满足 `p[m1] = s[1]`（最大值位置），`p[1]=1`（首项必为前缀最大值），`s[m2]=n`（末项必为后缀最大值），否则直接返回0。
2. **分治策略**：将排列分为左右两部分，最大值 `n` 位于 `p[m1]`。左边处理前缀最大值序列，右边处理后缀最大值序列。
3. **组合与排列计算**：
   - **整体划分**：用组合数 $\binom{n-1}{p_{m1}-1}$ 选择左边分配的数值。
   - **前缀处理**：从右往左遍历前缀最大值，每个区间贡献组合数 $\binom{p_{i+1}-2}{p_i-1}$ 和排列数 $(p_{i+1}-p_i-1)!$。
   - **后缀处理**：从左往右遍历后缀最大值，每个区间贡献组合数 $\binom{n-s_{i-1}-1}{n-s_i}$ 和排列数 $(s_i-s_{i-1}-1)!$。

#### **解决难点**
- **区间边界处理**：确保每个前缀/后缀最大值之间的区间满足严格递增/递减约束。
- **组合数快速计算**：通过预处理阶乘和逆元实现 $O(1)$ 的组合数查询。
- **分治方向**：前缀从后往前处理，后缀从前往后处理，确保每个子问题的独立性。

---

### 题解评分（≥4星）

1. **Yharimium（5星）**  
   - **亮点**：详细推导不等式链，明确分治策略，代码结构清晰。
   - **核心代码**：
     ```cpp
     llong res = binomial(n - 1, p[m1] - 1);
     for (处理前缀) res *= 组合数 * 阶乘;
     for (处理后缀) res *= 组合数 * 阶乘;
     ```

2. **FBW2010（4星）**  
   - **亮点**：对称处理左右区间，使用阶乘逆元优化计算。
   - **代码片段**：
     ```cpp
     ans *= C(p[i+1]-2, p[i]-1) * fac[p[i+1]-p[i]-1];
     ```

3. **MaxBlazeResFire（4星）**  
   - **亮点**：树形结构建模依赖关系，计算拓扑序数。
   - **关键步骤**：
     ```cpp
     E[a[i]].push_back(j); // 建树
     dfs(root); // 计算子树大小
     ans = fac[n] / ∏siz[i]; // 拓扑序公式
     ```

---

### 最优思路提炼

1. **分治组合**：将排列分解为左右独立区间，递归处理每个子区间。
2. **预处理优化**：通过预处理阶乘和逆元快速计算组合数。
3. **边界约束验证**：三个必要条件的快速剪枝避免无效计算。

---

### 类似题目推荐

1. **P1754 球迷购票问题**（组合数递推）
2. **P1287 盒子与球**（排列组合应用）
3. **P3223 [HNOI2012] 排队**（组合数学与容斥）

---

### 算法可视化设计

1. **分步动画**：
   - **步骤1**：高亮 `p[m1]` 作为最大值，左右分割为蓝色/红色区域。
   - **步骤2**：左侧从后往前遍历，每次高亮当前前缀最大值区间，显示组合数选择过程。
   - **步骤3**：右侧从前往后遍历，类似左侧动画，用红色箭头标记区间扩展。
   - **颜色标记**：当前操作用黄色高亮，已处理区域渐变淡化。

2. **复古像素风格**：
   - **界面**：8-bit 网格布局，数值用像素方块表示。
   - **音效**：组合数选择时播放 "blip" 音效，阶乘计算时播放 "click" 音效。
   - **自动演示**：按空格键逐步执行，回车键切换自动播放速度。

---

### 核心代码实现

```cpp
// 预处理阶乘与逆元
void pretask() {
    fac[0] = inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = (Mod - Mod/i) * inv[Mod%i] % Mod;
    // ... 计算阶乘和逆元
}

// 主计算逻辑
llong solve() {
    if (边界条件不满足) return 0;
    llong res = C(n-1, p[m1]-1);
    for (int i = m1-1; i >= 1; i--) {
        res = res * C(p[i+1]-2, p[i]-1) % Mod;
        res = res * fac[p[i+1]-p[i]-1] % Mod;
    }
    // 类似处理后缀部分
    return res;
}
```

---

### 关键调试教训

- **逆元初始化顺序**：必须先计算阶乘再计算逆元，否则会导致错误。
- **数组越界**：前缀/后缀数组需检查是否严格递增/递减，否则组合数返回0。

---
处理用时：65.34秒