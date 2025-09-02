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



## 【算法分类】  
**组合数学**

---

## 【题解思路、算法要点与解决难点】  
### **核心逻辑与公式推导**  
1. **最大值位置固定**  
   - 整个排列的最大值 $n$ 必须位于前缀最大值的最后一个位置 $p_{m1}$ 和后缀最大值的第一个位置 $s_1$，即 $p_{m1}=s_1$，否则无解。  
   - **验证条件**：若 $p_1 \neq 1$ 或 $s_{m2} \neq n$ 或 $p_{m1} \neq s_1$，直接输出 $0$。

2. **分治与乘法原理**  
   - 将排列分为左半部分 $[1, p_{m1}-1]$ 和右半部分 $[p_{m1}+1, n]$。  
   - **左半部分**：从 $n-1$ 个数中选择 $p_{m1}-1$ 个填充左侧，方案数为组合数 $\binom{n-1}{p_{m1}-1}$。  
   - **递归处理子区间**：对于前缀最大值序列 $p_i$，每个区间 $[p_i, p_{i+1})$ 的排列需满足：  
     - $p_{i+1}$ 处是当前区间最大值。  
     - 剩余数在区间内任意排列，方案数为 $\binom{p_{i+1}-2}{p_i-1} \cdot (p_{i+1}-p_i-1)!$。  
   - **右半部分**同理，但方向对称。

### **解决难点**  
1. **条件验证**：需严格检查输入的前缀/后缀序列是否满足极值位置逻辑。  
2. **分治递归计算**：如何正确拆分区间并组合各部分的方案数，避免重复或遗漏。  
3. **组合数与阶乘的快速计算**：预处理阶乘和逆元以支持快速查询。

---

## 【题解评分 (≥4星)】  
1. **Yharimium (5星)**  
   - **亮点**：逻辑清晰，代码简洁，通过分治和乘法原理直接计算方案数，预处理组合数优化性能。  
   - **代码片段**：  
     ```cpp  
     llong res = binomial(n - 1, p[m1] - 1);  
     for (遍历前缀序列) res *= 组合数 * 阶乘;  
     for (遍历后缀序列) res *= 组合数 * 阶乘;  
     ```

2. **FBW2010 (4星)**  
   - **亮点**：与 Yharimium 思路一致，但代码实现略有冗余，可读性稍差。  
   - **代码片段**：  
     ```cpp  
     ans *= A(p[i+1]-2, p[i]-1) * fac[p[i+1]-p[i]-1];  
     ```

3. **arrow_king (4星)**  
   - **亮点**：通过动态规划思想递推方案数，但需额外处理离散化逻辑。  
   - **代码片段**：  
     ```cpp  
     dp[i] = dp[i-1] * C(p[i-1]-1, p[i]-2) * A(...);  
     ```

---

## 【最优思路或技巧提炼】  
### **关键思路**  
1. **极值位置唯一性**：最大值 $n$ 的位置必须同时是前缀和后缀的极值，且分割左右子问题。  
2. **组合数分治**：将问题分解为独立子区间，每个子区间的排列方案数通过组合数和阶乘计算。  
3. **预处理优化**：预处理阶乘和逆元以快速计算组合数 $\binom{n}{k}$ 和排列数 $A_n^k$。

### **核心公式**  
总方案数 =  
$$  
\binom{n-1}{p_{m1}-1} \cdot \prod_{i=1}^{m1-1} \binom{p_{i+1}-2}{p_i-1} \cdot (p_{i+1}-p_i-1)! \cdot \prod_{i=2}^{m2} \binom{n-s_{i-1}-1}{n-s_i} \cdot (s_i-s_{i-1}-1)!  
$$

---

## 【同类型题或类似算法套路】  
1. **极值分割问题**：将排列或数组按极值分割为独立子区间，如 [LeetCode 456. 132模式](https://leetcode.cn/problems/132-pattern/)。  
2. **组合数乘法原理**：分阶段计算方案数并相乘，如 [洛谷 P3773 [CTSC2017] 吉夫特](https://www.luogu.com.cn/problem/P3773)。  
3. **排列约束问题**：根据特定条件限制排列结构，如 [CF1292E Rin and the Unknown Flower](https://codeforces.com/problemset/problem/1292/E)。

---

## 【推荐题目】  
1. **洛谷 P4921 [MtOI2018] 情侣？给我烧了！**  
   - **关键点**：组合数计算与容斥原理。  
2. **洛谷 P4369 [Code+#4] 组合数问题**  
   - **关键点**：组合数的拆分与乘法原理。  
3. **CF888D Almost Identity Permutations**  
   - **关键点**：排列中固定错位数的组合计算。

---

## 【可视化与算法演示】  
### **动画设计**  
1. **分步演示**：  
   - **Step 1**：高亮最大值位置 $p_{m1}$，将排列分为左右两部分。  
   - **Step 2**：左侧填充蓝色块（组合数选择），右侧填充红色块（组合数选择）。  
   - **Step 3**：递归处理子区间，用不同颜色标记当前处理的区间。  

2. **复古像素风格**：  
   - **Canvas 绘制**：用 8-bit 像素块表示排列元素，最大值用金色闪烁效果。  
   - **音效**：  
     - 选择组合数时播放 `coin.wav`（硬币音效）。  
     - 完成一个子区间时播放 `levelup.wav`（升级音效）。  

3. **交互式控制**：  
   - **速度调节**：滑动条控制动画速度（1x/2x/5x）。  
   - **单步执行**：点击按钮逐步观察组合数计算流程。  

### **代码片段（Canvas 绘制）**  
```javascript  
// 绘制排列分治过程  
function drawPermutation(ctx, pos, colors) {  
  ctx.fillStyle = '#FFD700'; // 金色最大值  
  ctx.fillRect(pos * 10, 0, 8, 8);  
  // 绘制左右子区间  
  for (let i = 0; i < pos; i++) {  
    ctx.fillStyle = colors[i];  
    ctx.fillRect(i * 10, 10, 8, 8);  
  }  
}  
```

---

## **核心代码实现**  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  
const int MOD = 1e9+7, N = 2e5+5;  
ll fac[N], inv[N];  

// 预处理阶乘和逆元  
void pretask() {  
  fac[0] = 1;  
  for (int i=1; i<N; i++) fac[i] = fac[i-1] * i % MOD;  
  inv[N-1] = pow(fac[N-1], MOD-2);  
  for (int i=N-2; i>=0; i--) inv[i] = inv[i+1] * (i+1) % MOD;  
}  

// 计算组合数  
ll C(int n, int m) {  
  return (n >= m) ? fac[n] * inv[m] % MOD * inv[n-m] % MOD : 0;  
}  

int main() {  
  pretask();  
  int T; cin >> T;  
  while (T--) {  
    int n, m1, m2;  
    cin >> n >> m1 >> m2;  
    vector<int> p(m1+1), s(m2+1);  
    for (int i=1; i<=m1; i++) cin >> p[i];  
    for (int i=1; i<=m2; i++) cin >> s[i];  
    if (p[1]!=1 || s[m2]!=n || p[m1]!=s[1]) {  
      cout << "0\n"; continue;  
    }  
    ll ans = C(n-1, p[m1]-1);  
    // 处理前缀  
    for (int i=m1-1; i>=1; i--) {  
      int len = p[i+1] - p[i] - 1;  
      ans = ans * C(p[i+1]-2, p[i]-1) % MOD;  
      ans = ans * fac[len] % MOD;  
    }  
    // 处理后缀  
    for (int i=2; i<=m2; i++) {  
      int len = s[i] - s[i-1] - 1;  
      ans = ans * C(n - s[i-1] - 1, s[i] - s[i-1] - 1) % MOD;  
      ans = ans * fac[len] % MOD;  
    }  
    cout << ans << '\n';  
  }  
}  
```

---
处理用时：91.81秒