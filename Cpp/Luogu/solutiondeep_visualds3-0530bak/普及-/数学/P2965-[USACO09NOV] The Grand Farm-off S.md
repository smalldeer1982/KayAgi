# 题目信息

# [USACO09NOV] The Grand Farm-off S

## 题目描述

Farmer John owns 3\*N (1 <= N <= 500,000) cows surprisingly numbered 0..3\*N-1, each of which has some associated integer weight W\_i (1 <= W\_i <= d). He is entering the Grand Farm-off, a farming competition where he shows off his cows to the greater agricultural community.

This competition allows him to enter a group of N cows. He has given each of his cows a utility rating U\_i (1 <= U\_i <= h), which

represents the usefulness he thinks that a particular cow will have in the competition, and he wants his selection of cows to have the maximal sum of utility.

There might be multiple sets of N cows that attain the maximum utility sum. FJ is afraid the competition may impose a total weight limit on the cows in the competition, so a secondary priority is to bring lighter weight competition cows.

Help FJ find a set of N cows with minimum possible total weight among the sets of N cows that maximize the utility, and print the remainder when this total weight is divided by M (10,000,000 <= M <= 1,000,000,000).

Note: to make the input phase faster, FJ has derived polynomials which will generate the weights and utility values for each cow. For each cow 0 <= i < 3\*N,

 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

The formulae do sometimes generate duplicate numbers; your algorithm should handle this properly. 

农夫约翰有3N(1 < N < 500000)头牛，编号依次为1..#N，每头牛都有一个整数值的体 重。约翰准备参加农场技艺大赛，向广大的农业社区展示他的奶牛.
大赛规则允许约翰带N头牛参赛.约翰给每头牛赋予了一个“有用度”Ui，它表 示了某头牛在比赛中的有用程度.约翰希望他选出的奶牛的有用度之和最大.

有可能选出很多组的N头牛都能达到有用度最大和.约翰害怕选出的N头牛的总重量会给大赛 带来震撼，所以，要考虑优先选择体重轻的奶牛.

帮助约翰选出N头总重量最轻，并且有用度之和最大的奶牛.输出体重模M后的余数.

注意：为了使输入更快，约翰使用了一个多项式来生成每头牛的体重和有用度.对每头牛/， 体重和有用度的计算公式为：



 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

## 说明/提示

The functions generate weights of 5, 6, 9, 14, 21, and 30 along with utilities of 0, 1, 8, 27, 64, and 125.


The two cows with the highest utility are cow 5 and 6, and their combined weight is 21+30=51.


## 样例 #1

### 输入

```
2 0 1 5 55555555 0 1 0 55555555 55555555 
```

### 输出

```
51 
```

# AI分析结果



### 算法分类
排序、模拟

---

### 题解思路与难点分析

**核心逻辑**：
1. **生成属性**：按公式计算每头牛的重量 `W_i` 和效用 `U_i`，需分步骤计算高次幂并取模。
2. **排序规则**：先按效用降序排列，效用相同时按重量升序排列。
3. **选择与求和**：取前 `N` 头牛，累加其重量并取模 `M`。

**关键难点**：
1. **大数计算与溢出**：直接计算 `i^5` 会导致数值溢出，需分步取模。
2. **排序效率**：对 `3N` 个元素排序需用 `O(N log N)` 算法（如快速排序）。
3. **参数预处理**：对多项式系数提前取模（如 `a %= d`），减少中间值大小。

**解决策略**：
- 分步计算 `i^2`, `i^3`, `i^5`，每次乘法后取模。
- 使用 `long long` 类型存储中间结果。
- 预处理多项式系数，避免数值过大。

---

### 题解评分 (≥4星)

1. **Qing_s (4.5星)**
   - **亮点**：详细分析错误原因（如 `pow` 的精度问题），分步计算次幂。
   - **代码**：清晰的排序逻辑和取模优化。
   - **心得**：强调调试经验，避免 `pow` 和数组越界。

2. **FourteenObsidian (4.5星)**
   - **亮点**：预处理参数取模，分步计算次幂。
   - **代码**：结构体排序高效，可读性强。
   - **优化**：显式处理每一步的取模，减少溢出风险。

3. **zy小可爱ღ (4星)**
   - **亮点**：正确实现排序规则，强调下标从0开始。
   - **不足**：代码中高次幂计算较冗长，可读性略低。

---

### 最优思路与技巧

1. **分步取模**：计算 `i^5` 时分解为 `i^2 = (i*i) % mod` → `i^3 = (i^2*i) % mod` → `i^5 = (i^3*i^2) % mod`。
2. **参数预处理**：多项式系数先取模（如 `a %= d`），避免中间值过大。
3. **排序规则设计**：
   ```cpp
   bool cmp(Node a, Node b) {
       if (a.u != b.u) return a.u > b.u; // 效用降序
       return a.w < b.w;                  // 重量升序
   }
   ```

---

### 类似题目推荐

1. **P1177 【模板】快速排序**  
   - 练习高效排序算法实现。
2. **P1068 [NOIP2009 普及组] 分数线划定**  
   - 多关键字排序与选择前N项。
3. **P1223 排队接水**  
   - 贪心选择与排序结合。

---

### 核心代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    ll w, u;
} cows[1500005];

bool cmp(const Node& a, const Node& b) {
    if (a.u != b.u) return a.u > b.u;
    return a.w < b.w;
}

int main() {
    ll n, a, b, c, d, e, f, g, h, m;
    cin >> n >> a >> b >> c >> d >> e >> f >> g >> h >> m;

    // 预处理系数取模
    a %= d; b %= d; c %= d;
    e %= h; f %= h; g %= h;

    for (ll i = 0; i < 3 * n; ++i) {
        // 计算 W_i
        ll i_mod_d = i % d;
        ll i2 = (i_mod_d * i_mod_d) % d;
        ll i3 = (i2 * i_mod_d) % d;
        ll i5 = (i3 * i2) % d;
        cows[i].w = (a * i5 + b * i2 + c) % d;

        // 计算 U_i
        ll i_mod_h = i % h;
        ll ii3 = (i_mod_h * i_mod_h % h) * i_mod_h % h;
        ll ii5 = (ii3 * i_mod_h % h) * i_mod_h % h;
        cows[i].u = (e * ii5 + f * ii3 + g) % h;
    }

    sort(cows, cows + 3 * n, cmp);

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + cows[i].w) % m;
    }
    cout << ans % m << endl;
    return 0;
}
```

---

### 可视化算法设计

**动画方案**：
1. **计算阶段**：
   - 展示每头牛 `i` 的 `W_i` 和 `U_i` 计算过程，高亮当前计算的次幂步骤（如 `i^2`→`i^3`→`i^5`）。
2. **排序阶段**：
   - 用颜色区分不同效用等级（红色高效用，蓝色低效用），效用相同时用绿色标记较轻的牛。
3. **选择阶段**：
   - 前 `N` 头牛被选中时闪烁，并实时更新总重量和模运算结果。

**复古像素风格**：
- **Canvas 网格**：每头牛表示为 16x16 像素方块，颜色按效用渐变。
- **音效**：
  - 计算完成时播放“滴”声。
  - 选中牛时播放“金币”音效。
- **自动演示**：按步进播放计算、排序、选择过程，支持暂停/继续。

---

### 总结

本题关键在于正确处理大数运算和多关键字排序。通过分步取模和参数预处理避免溢出，结合高效排序算法实现最优解。可视化设计通过分步动画和复古元素增强理解，适合教学演示。

---
处理用时：140.31秒