# 题目信息

# Crypto Lights

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523E/5925bbb9bbb86a373ea1b1a63885d119a4446a59.png)To monitor cryptocurrency exchange rates trader William invented a wonderful device consisting of $ n $ lights arranged in a row. The device functions in the following way:

Initially, all lights on William's device are turned off. At the beginning of a new iteration the device randomly, with a uniform distribution, picks a light that is turned off and turns it on, telling William which cryptocurrency he should invest in. After this iteration if any $ k $ consecutive lights contain more than one turned on light, then the device finishes working.

William doesn't like uncertainty, so he wants you to calculate the expected value of the number of lights that are turned on in the device after it finishes working.

## 说明/提示

Explanation of the first sample test case:

Let's write out all possible sequences of light toggles, which will make the device complete its operation:

1. $ (1, 2) $ — $ 2 $ lights are turned on
2. $ (1, 3, 2) $ — $ 3 $ lights are turned on
3. $ (2, 1) $ — $ 2 $ lights are turned on
4. $ (2, 3) $ — $ 2 $ lights are turned on
5. $ (3, 2) $ — $ 2 $ lights are turned on
6. $ (3, 1, 2) $ — $ 3 $ lights are turned on

Then the final expected value will be equal to $ \frac{2}{6} $ + $ \frac{3}{6} $ + $ \frac{2}{6} $ + $ \frac{2}{6} $ + $ \frac{2}{6} $ + $ \frac{3}{6} $ = $ \frac{14}{6} $ = $ \frac{7}{3} $ .

Then the required output will be $ 333333338 $ , since $ 333333338 \cdot 3 \equiv 7 \pmod{10^9+7} $ .

## 样例 #1

### 输入

```
3
3 2
15 2
40 15```

### 输出

```
333333338
141946947
329622137```

# AI分析结果

---
# 💡 Kay的C++算法解析：Crypto Lights 深入学习指南 💡

<introduction>
今天我们来一起分析“Crypto Lights”这道C++编程题。这道题需要计算设备停止时已点亮灯的期望数量，核心在于期望的转化和组合数学的应用。本指南将帮助大家梳理思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学（期望转化与组合数应用）`

🗣️ **初步分析**：
解决“Crypto Lights”的关键在于将期望问题转化为概率后缀和的计算，并结合组合数学求解合法方案数。简单来说，期望的计算可以通过“后缀和”技巧简化——原本需要计算每个停止时刻的概率乘其值，现在转化为计算“点亮i-1盏灯仍未停止的概率”之和。这就像把“每个终点的贡献”转化为“所有未到达终点的路径的累计贡献”。

题解的核心思路是：定义 \( s_i \) 为“点亮 \( i-1 \) 盏灯后仍未停止的概率”，则期望 \( E = \sum_{i=1}^n s_i \)。计算 \( s_i \) 时，需利用组合数求出合法方案数（即 \( i-1 \) 盏灯两两间隔至少 \( k-1 \) 个不亮灯的方案数）除以总方案数（所有选 \( i-1 \) 盏灯的方案数）。

核心算法流程：
1. 预处理阶乘和逆元，快速计算组合数。
2. 遍历 \( i \) 从1到n，计算每个 \( s_i \) 并累加得到期望。
3. 输出模 \( 10^9+7 \) 下的结果。

可视化设计思路：采用8位像素风格动画，用不同颜色的像素块表示亮灯（如绿色）和不亮灯（灰色），动态展示选灯过程。关键步骤高亮（如选灯时绿色闪烁），用队列或网格展示当前亮灯位置，配合“叮”的音效提示选灯操作。当出现 \( k \) 连续亮灯时，播放胜利音效并停止动画。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解表现突出（评分≥4星）：
</eval_intro>

**题解一：作者FjswYuzu**
* **点评**：此题解思路简洁直接，通过期望转化和组合数公式快速求解。代码规范（如预处理阶乘和逆元），变量命名清晰（`fac`/`ifac`表示阶乘和逆元阶乘），边界处理严谨（特判 \( n < m \) 时组合数为0）。算法时间复杂度为 \( O(n + Tn) \)，适合竞赛场景，是典型的高效实现。

**题解二：作者walk_alone**
* **点评**：此题解详细解释了 \( s_i \) 的意义（点亮 \( i-1 \) 盏灯仍未停止的概率），并通过插板法推导合法方案数，逻辑清晰。对组合数的推导过程（如插入 \( k-1 \) 个不亮灯）解释透彻，适合理解原理。代码结构工整，关键步骤注释明确。

**题解三：作者chroneZ**
* **点评**：此题解深入讨论了概率单位的问题，纠正了“等概率选灯”的常见误解，强调合法方案的概率需考虑选灯的顺序。代码中对组合数的预处理和逆元计算高效，边界条件（如 \( n - (i-2)(k-1) < i-1 \) 时终止循环）处理严谨，适合深入学习。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于期望的转化和组合数的推导。以下是关键步骤的分析与策略：
</difficulty_intro>

1.  **关键点1：期望的转化（\( s_i \) 的意义）**
    * **分析**：直接计算每个停止时刻的概率 \( p_i \) 较复杂，通过后缀和 \( s_i = \sum_{j=i}^n p_j \) 转化为“点亮 \( i-1 \) 盏灯仍未停止的概率”，简化了计算。例如，当 \( i=2 \) 时，\( s_2 \) 表示点亮1盏灯后未停止的概率（显然为1，因为单盏灯无法形成 \( k \) 连续亮灯）。
    * 💡 **学习笔记**：期望的后缀和转化是概率问题的常用技巧，将“终点贡献”转化为“路径存活概率”。

2.  **关键点2：合法方案数的组合数推导**
    * **分析**：合法方案要求 \( i-1 \) 盏亮灯两两间隔至少 \( k-1 \) 个不亮灯。通过插板法，先固定 \( i-2 \) 个间隔各放 \( k-1 \) 个不亮灯，剩余不亮灯自由分配，总合法位置数为 \( n - (i-2)(k-1) \)，合法方案数为 \( \binom{n - (i-2)(k-1)}{i-1} \)。
    * 💡 **学习笔记**：插板法适用于“间隔分配”问题，关键是将约束条件转化为预分配的“固定间隔”。

3.  **关键点3：组合数的高效计算与逆元预处理**
    * **分析**：组合数 \( \binom{n}{m} \) 的计算需预处理阶乘 \( fac \) 和逆元阶乘 \( ifac \)，利用 \( \binom{n}{m} = \frac{fac[n]}{fac[m] \cdot fac[n-m]} \mod MOD \)。逆元通过快速幂预处理，确保组合数计算的高效性。
    * 💡 **学习笔记**：预处理阶乘和逆元是组合数问题的“标配”，能将单次组合数计算复杂度降至 \( O(1) \)。

### ✨ 解题技巧总结
- **问题转化**：将期望 \( E = \sum ip_i \) 转化为 \( E = \sum s_i \)，简化计算。
- **插板法应用**：通过预分配间隔的不亮灯，将合法方案数转化为组合数问题。
- **预处理优化**：预处理阶乘和逆元，快速计算组合数，适应多测试用例场景。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，代码简洁高效，适合竞赛参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了FjswYuzu和chroneZ的题解思路，预处理阶乘和逆元，遍历计算每个 \( s_i \) 并累加得到期望。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long LL;
    const LL MOD = 1e9 + 7;
    const int MAXN = 1e5 + 5;

    LL fac[MAXN], ifac[MAXN];

    LL QuickPow(LL x, LL p) {
        LL ans = 1, base = x;
        while (p) {
            if (p & 1) ans = ans * base % MOD;
            base = base * base % MOD;
            p >>= 1;
        }
        return ans;
    }

    LL C(LL n, LL m) {
        if (n < m || m < 0) return 0;
        return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
    }

    int main() {
        // 预处理阶乘和逆元阶乘
        fac[0] = 1;
        for (int i = 1; i < MAXN; ++i)
            fac[i] = fac[i - 1] * i % MOD;
        ifac[MAXN - 1] = QuickPow(fac[MAXN - 1], MOD - 2);
        for (int i = MAXN - 2; i >= 0; --i)
            ifac[i] = ifac[i + 1] * (i + 1) % MOD;

        int T;
        scanf("%d", &T);
        while (T--) {
            LL n, k;
            scanf("%lld %lld", &n, &k);
            LL ans = 1; // s_1=1（点亮0盏灯未停止的概率为1）
            for (LL i = 2; i <= n; ++i) { // i从2开始对应s_i（i-1=1盏灯）
                LL total = C(n, i - 1);
                if (total == 0) break;
                LL valid = C(n - (i - 2) * (k - 1), i - 1);
                ans = (ans + valid * QuickPow(total, MOD - 2) % MOD) % MOD;
            }
            printf("%lld\n", ans);
        }
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先预处理阶乘 `fac` 和逆元阶乘 `ifac`，用于快速计算组合数。主函数中，对于每个测试用例，遍历 \( i \) 从2到n（对应 \( i-1 \) 盏灯），计算合法方案数 `valid` 和总方案数 `total`，通过逆元求概率 \( s_i = \frac{valid}{total} \) 并累加得到期望。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者FjswYuzu**
* **亮点**：代码简洁，预处理阶乘和逆元，循环计算 \( s_i \)，边界处理（如 \( n < m \) 时组合数为0）严谨。
* **核心代码片段**：
    ```cpp
    LL C(LL n,LL m){if(n<m) return 0;return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;}
    // ...
    for(LL i=1;i<n;++i) (ans+=C(n-(i-1)*(k-1),i)*QuickPow(C(n,i),MOD-2))%=MOD;
    ```
* **代码解读**：
    `C(n, m)` 函数处理组合数的计算，特判 \( n < m \) 时返回0。循环中，`C(n-(i-1)*(k-1), i)` 计算合法方案数，`QuickPow(C(n, i), MOD-2)` 计算总方案数的逆元，两者相乘得到 \( s_{i+1} \)（因为 \( i \) 从1开始对应 \( i \) 盏灯）。
* 💡 **学习笔记**：组合数的逆元通过快速幂计算，是模运算中除法的常用技巧。

**题解二：作者chroneZ**
* **亮点**：代码中明确处理了概率单位问题，循环终止条件（`if(n - (i - 2) * (k - 1) < i - 1) break`）避免无效计算。
* **核心代码片段**：
    ```cpp
    for(int i = 1; i <= n; i++){
        if(n - (i - 2) * (k - 1) < i - 1) break;
        ans += binom(n - (i - 2) * (k - 1), i - 1) * inv(binom(n, i - 1)) % mod;
        ans %= mod;
    }
    ```
* **代码解读**：
    循环中，当剩余位置不足以放置 \( i-1 \) 盏灯（间隔 \( k-1 \)）时，提前终止循环。`binom(n - (i-2)*(k-1), i-1)` 是合法方案数，`inv(binom(n, i-1))` 是总方案数的逆元，累加得到 \( s_i \)。
* 💡 **学习笔记**：提前终止循环可优化时间复杂度，避免无效计算。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解期望的计算过程，我们设计一个“像素灯阵”动画，模拟选灯过程并展示 \( s_i \) 的计算逻辑。
</visualization_intro>

  * **动画演示主题**：`像素灯阵大冒险`
  * **核心演示内容**：展示 \( n \) 盏灯排成一行，每次随机选一盏灯点亮（绿色像素块），当出现 \( k \) 连续亮灯时停止。动画同步计算 \( s_i \)（点亮 \( i-1 \) 盏灯未停止的概率），用进度条和数字显示当前概率。

  * **设计思路简述**：8位像素风格（FC游戏画面），绿色代表亮灯，灰色代表不亮灯。关键步骤高亮（如选灯时绿色闪烁），用音效（“叮”）提示选灯操作，胜利音效（“哇”）提示停止。通过动态网格展示亮灯位置和间隔，帮助理解合法方案数的计算。

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：屏幕中央显示 \( n \times 1 \) 的像素灯阵（灰色方块），顶部显示控制面板（开始/暂停/单步/重置按钮、速度滑块），右侧显示当前 \( i \) 和 \( s_i \) 的值。
    2. **选灯过程**：点击“开始”后，AI自动选灯（或手动单步），选中的灯变为绿色并闪烁，伴随“叮”音效。每选一盏灯，更新右侧的 \( i \)（当前已选灯数）和 \( s_i \)（通过组合数公式计算）。
    3. **合法/非法判断**：当新选灯导致存在 \( k \) 连续亮灯时，该灯变为红色，播放“哇”音效，动画停止并显示最终期望。否则，继续选灯。
    4. **数据可视化**：右侧用柱状图展示各 \( s_i \) 的值，颜色越深表示概率越大。组合数计算过程用文字气泡解释（如“合法方案数：C(5,2)=10”）。

  * **旁白提示**：
    - （选灯时）“现在点亮第 \( i \) 盏灯，检查是否存在 \( k \) 连续亮灯...”
    - （合法时）“当前 \( i-1 \) 盏灯合法，\( s_i \) 增加 \( \frac{valid}{total} \)！”
    - （非法时）“发现 \( k \) 连续亮灯，设备停止！”

<visualization_conclusion>
通过这个动画，我们可以直观看到每一步选灯的概率变化，理解 \( s_i \) 的意义和组合数的计算逻辑，让抽象的数学问题变得生动有趣！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是期望转化与组合数应用，这类方法在概率问题中广泛适用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 期望转化：将 \( E = \sum ip_i \) 转化为后缀和 \( E = \sum s_i \)，适用于“停止条件与步骤相关”的问题（如随机游走、游戏结束条件）。
    - 组合数插板法：处理“间隔约束”的选法问题（如分糖果、放置物品）。
    - 逆元预处理：模运算中除法的通用解法，适用于组合数、概率等需要取模的场景。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4316 绿豆蛙的归宿** - `概率与期望DP`
          * 🗣️ **推荐理由**：通过期望DP计算路径期望，巩固期望的线性性质和递推求解。
    2.  **洛谷 P1850 换教室** - `动态规划与期望`
          * 🗣️ **推荐理由**：结合概率与DP，处理多状态转移，提升状态定义能力。
    3.  **洛谷 P5656 [SDOI2016] 硬币游戏** - `概率与KMP`
          * 🗣️ **推荐理由**：综合概率、字符串匹配和矩阵快速幂，拓展组合数学应用场景。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试时的经验，例如：
</insights_intro>

> **参考经验 (来自作者chroneZ)**：“需要注意选灯的顺序影响概率，不能直接用组合数的等概率假设。例如，选灯序列 (1,2) 和 (2,1) 的概率不同，需通过逆元统一单位。”

**点评**：这位作者的经验非常重要！在概率问题中，选法的顺序（排列）和组合的概率不同，需特别注意单位统一。通过逆元处理组合数的除法，能有效避免这类错误，这是竞赛中容易踩坑的点。

---

<conclusion>
本次关于“Crypto Lights”的C++解题分析就到这里。希望这份指南能帮助大家理解期望转化和组合数学的应用。记住，多动手推导公式、调试代码，是掌握这类问题的关键！下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：126.30秒