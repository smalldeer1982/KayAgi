# 题目信息

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9```

### 输出

```
20```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3
4 2 1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97```

### 输出

```
19200```

# AI分析结果



### 算法分类
动态规划（DP）与组合数学

---

### 题解思路与难点解析

#### 核心算法流程
1. **排序预处理**：将数组从小到大排序，便于后续双指针处理。
2. **预处理 lim 数组**：对每个元素 a[i]，计算最大的 j 满足 2a[j] ≤ a[i]。
3. **动态规划**：定义 dp[i] 表示以 a[i] 为当前最大值的合法排列数。转移时枚举上一个最大值 j（需满足 2a[j] ≤ a[i]），用排列数计算中间可插入的元素方案。
4. **排列数优化**：通过阶乘与逆元预处理，将排列数计算转化为 O(1) 查询，并通过前缀和优化转移复杂度至 O(n)。

#### 解决难点
- **状态转移方程**：需准确建模排列长度限制（每个元素后只能插入 ≤ 当前最大值/2 的元素）。
- **数学优化**：将排列数公式 A(n, m) 分解为阶乘与逆元的组合，利用同余性质约分，实现 O(n) 转移。
- **边界条件**：当最大元素前一个元素的 2 倍超过它时，直接判无解。

---

### 题解评分（≥4星）

1. **LightningUZ（5星）**  
   - 思路清晰，完整推导 DP 转移方程与优化步骤。  
   - 代码结构简洁，预处理阶乘/逆元，双指针求 lim 数组。  
   - 关键代码段：`sum` 数组实现前缀和优化，将暴力 O(n²) 转化为 O(n)。

2. **George1123（5星）**  
   - 图文结合解释排列形态，直观展示子序列结构。  
   - 公式推导详细，给出 `A(n-m, k)` 的数学意义。  
   - 代码中显式二分求 lim 数组，逻辑清晰。

3. **Alex_Wei（4星）**  
   - 代码极简，仅 30 行完成核心逻辑。  
   - 预处理阶乘逆元，直接枚举合法 j 进行转移。  
   - 注释明确，标注调试时间，体现高效编码。

---

### 最优思路与技巧提炼

1. **排序预处理**：排序后相邻元素的 2 倍关系可快速判断合法性（最大元素需 ≥ 次大元素的两倍）。
2. **lim 数组双指针法**：在排序数组上，双指针 O(n) 预处理每个元素的限制位置。
3. **排列数公式优化**：用阶乘与逆元预处理，将排列数计算 `A(n, m) = n!/(n-m)!` 转化为 O(1) 查询。
4. **前缀和优化**：将转移公式中的累加项拆分为与 i/j 无关的部分，利用前缀和数组快速求和。

---

### 同类型题与算法套路

- **相似 DP + 组合数学题**：  
  1. **排列限制问题**：如「P1754 球迷购票问题」（需满足前缀条件）。  
  2. **子序列计数**：如「CF1392F Omkar and Landslide」（相邻元素差值限制）。  
  3. **带权排列数**：如「P1651 塔」（多阶段决策 + 组合数）。

---

### 推荐洛谷题目
1. **P1754** - 球迷购票问题（组合数经典模型）  
2. **P1651** - 塔（动态规划与排列组合结合）  
3. **CF1392F** - Omkar and Landslide（相邻元素关系限制）

---

### 代码核心片段

```cpp
// 预处理阶乘与逆元
void Init() {
    fc[0] = fc[1] = fi[0] = fi[1] = iv[1] = 1;
    for(int i=2; i<=n; ++i) {
        iv[i] = (mod - mod/i) * iv[mod%i] % mod;
        fi[i] = fi[i-1] * iv[i] % mod;
        fc[i] = fc[i-1] * i % mod;
    }
}

// 动态规划转移
for(int i=1; i<=n; ++i) {
    while(2*a[mx] <= a[i] && mx <= n) ++mx;
    --mx; // 计算 lim[i]
    f[i] = fi[n - len[i]] * sum[mx] % mod; // 前缀和优化
    sum[i] = (sum[i-1] + fc[n-1 - len[i]] * f[i]) % mod;
}
```

---

### 可视化设计

#### 动态算法演示
1. **排序与 lim 预处理**：  
   - 柱状图展示排序后数组，高亮当前元素 i 和对应的 lim[i] 位置。  
   - 双指针动画：移动指针 j 直到 2a[j] > a[i]。

2. **DP 状态转移**：  
   - 网格图展示 dp[i] 的累加过程，不同颜色表示不同 j 的贡献。  
   - 步进控制：点击下一步时，显示当前 j 和排列数计算过程。

3. **排列数可视化**：  
   - Canvas 绘制剩余位置的空格，动态填充可插入的元素（颜色区分已选/未选）。

#### 复古像素风格
- **8-bit 音效**：  
  - 移动指针时播放 "beep" 音效。  
  - 成功转移时播放上升音阶，失败（如无解）时播放下降音阶。
- **像素动画**：  
  - 元素用 16x16 像素块表示，转移时显示闪烁箭头。  
  - 背景音乐：8-bit 风格循环旋律，音量可调。

---

### 总结
本题通过排序预处理和动态规划，结合组合数学优化，高效计算合法排列数。关键点在于 lim 数组的预处理和前缀和优化，将复杂度降至 O(n)。可视化设计可增强对状态转移和排列数计算的理解，适合通过交互式学习掌握算法核心。

---
处理用时：73.28秒