# 题目信息

# The Destruction of the Universe (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, $ n \leq 10^6 $ . You can only make hacks if both versions of the problem are solved.

Orangutans are powerful beings—so powerful that they only need $ 1 $ unit of time to destroy every vulnerable planet in the universe!

There are $ n $ planets in the universe. Each planet has an interval of vulnerability $ [l, r] $ , during which it will be exposed to destruction by orangutans. Orangutans can also expand the interval of vulnerability of any planet by $ 1 $ unit.

Specifically, suppose the expansion is performed on planet $ p $ with interval of vulnerability $ [l_p, r_p] $ . Then, the resulting interval of vulnerability may be either $ [l_p - 1, r_p] $ or $ [l_p, r_p + 1] $ .

Given a set of planets, orangutans can destroy all planets if the intervals of vulnerability of all planets in the set intersect at least one common point. Let the score of such a set denote the minimum number of expansions that must be performed.

Orangutans are interested in the sum of scores of all non-empty subsets of the planets in the universe. As the answer can be large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, there are seven non-empty subsets of planets we must consider:

- For each of the subsets $ \{[1,1]\}, \{[2,3]\}, \{[3,3]\} $ , the score is $ 0 $ .
- For the subset $ \{[2,3], [3,3]\} $ , the score is $ 0 $ , because the point $ 3 $ is already contained in both planets' interval of vulnerability.
- For the subset $ \{[1,1], [2,3]\} $ , the score is $ 1 $ . By using one operation on changing the interval of vulnerability of the second planet to be $ [1,3] $ , the two planets now both have the point $ 1 $ in their interval.
- For the subset $ \{[1,1], [3,3]\} $ , the score is $ 2 $ . By using two operations on changing the interval of vulnerability of the first planet to be $ [1,3] $ , the two planets now both have the point $ 3 $ in their interval.
- For the subset $ \{[1,1], [2,3], [3,3]\} $ , the score is $ 2 $ . By using one operation on changing the interval of vulnerability of the first planet to be $ [1,2] $ and one operation on changing the interval of vulnerability of the third planet to $ [2,3] $ , all three planets will have the point $ 2 $ in their interval.

The sum of scores of all non-empty subsets of the first testcase is $ 0 \cdot 4 + 1 \cdot 1 + 2\cdot2 = 5 $ .

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5```

### 输出

```
5
6
24```

# AI分析结果



## 算法分类
**组合数学 + 离散化 + 前缀和**

---

## 题解思路与解决难点

### 核心思路
1. **中位数性质**：最优交点x必为线段端点的中位数，可将问题转化为枚举所有端点作为候选交点。
2. **离散化处理**：对端点重新编号解决重复值问题，确保每个端点有唯一顺序。
3. **组合数优化**：利用范德蒙德卷积简化组合数求和式，将双重循环优化为单次查询。
4. **前缀和加速**：预处理左右区间的线段数和贡献值，实现O(1)查询每个x的贡献。

### 解决难点
1. **端点重复处理**：通过离散化后增加偏移量，确保每个端点有独立位置。
2. **组合数推导**：将贡献式中的双重求和转换为组合数单式，大幅降低计算复杂度。
3. **动态计数维护**：遍历端点时动态维护左右线段数，并同步更新贡献值。

---

## 题解评分（≥4星）
1. **ForgotMe（5星）**
   - **亮点**：通过中位数转化巧妙简化问题，利用前缀和快速计算贡献，代码高效清晰。
   - **优化**：离散化后使用桶排序预处理，实现O(n)复杂度。
2. **_abcd_（4星）**
   - **亮点**：完整推导组合数公式，离散化处理详尽。
   - **不足**：未显式处理端点重复，可能引入边界问题。
3. **Deep_Kevin（4星）**
   - **亮点**：详细分类讨论x作为左右端点的情况，数学推导严谨。
   - **不足**：代码实现稍显复杂。

---

## 最优思路提炼
1. **端点中位数性质**：最优交点为线段端点中位数，避免枚举所有可能位置。
2. **组合恒等式**：利用$\sum_{j} \binom{a}{j}\binom{b}{c-j} = \binom{a+b}{c}$快速计算贡献。
3. **动态前缀和**：维护左右端点数量和贡献总和，实现高效查询。

---

## 同类题目推荐
1. **CF1548B**：区间覆盖中位数应用。
2. **P2184**：离散化+前缀和统计区间贡献。
3. **AT_abc233_g**：组合数与中位数性质结合。

---

## 可视化设计
### 算法动画方案
- **网格绘制**：Canvas绘制离散化后的端点序列，高亮当前处理的端点x。
- **动态计数**：左右区域用不同颜色标记，实时显示cnt1（左）、cnt2（右）。
- **组合数计算**：弹出公式$\binom{cnt1+cnt2-1}{cnt2}$，同步显示计算结果。
- **音效触发**：
  - **步进音效**：每次处理新端点时播放"beep"音。
  - **贡献计算**：成功累加贡献时播放上升音调。

### 复古像素风格
- **8位调色板**：端点用绿色像素块，当前x用闪烁红色块。
- **网格动画**：端点序列以16x16网格展示，组合数结果以8位字体显示。
- **自动演示**：按端点顺序自动播放，速度可调。

---

## 核心代码实现
```cpp
// 预处理阶乘和逆元
void init_C(int n) {
    fac[0] = 1;
    for(int i=1; i<=n; i++) fac[i] = fac[i-1] * i % mod;
    inv[n] = ksm(fac[n], mod-2);
    for(int i=n-1; i>=0; i--) inv[i] = inv[i+1] * (i+1) % mod;
}

// 主计算逻辑
for(int i=1; i<=2*n; i++) {
    int val = rev[i], op = fk[i];
    // 动态维护左右计数和贡献
    cnt1 = s1[i-1], cnt2 = s2[i+1];
    pro = n - cnt1 - cnt2;
    
    // 左贡献计算
    int left_contrib = (1ll * val * cnt1 - s3[i-1]) % mod;
    int comb = binom(cnt1 + cnt2 - 1, cnt1);
    res = (res + 1ll * left_contrib * mi[pro] % mod * comb) % mod;
    
    // 右贡献计算
    int right_contrib = (s4[i+1] - 1ll * val * cnt2) % mod;
    comb = binom(cnt1 + cnt2 - 1, cnt2);
    res = (res + 1ll * right_contrib * mi[pro] % mod * comb) % mod;
}
```

---

## 个人心得
- **离散化技巧**：通过`l2[x] = ++cnt`确保端点唯一顺序，巧妙避免重复值比较。
- **负数取模**：减法后需加mod再取模，防止负值影响结果。
- **组合数优化**：预处理阶乘逆元是提升效率的关键，避免每次动态计算。

---
处理用时：63.89秒