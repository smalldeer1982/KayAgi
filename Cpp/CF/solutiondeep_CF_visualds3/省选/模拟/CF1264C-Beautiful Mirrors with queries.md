# 题目信息

# Beautiful Mirrors with queries

## 题目描述

Creatnx has $ n $ mirrors, numbered from $ 1 $ to $ n $ . Every day, Creatnx asks exactly one mirror "Am I beautiful?". The $ i $ -th mirror will tell Creatnx that he is beautiful with probability $ \frac{p_i}{100} $ for all $ 1 \le i \le n $ .

Some mirrors are called checkpoints. Initially, only the $ 1 $ st mirror is a checkpoint. It remains a checkpoint all the time.

Creatnx asks the mirrors one by one, starting from the $ 1 $ -st mirror. Every day, if he asks $ i $ -th mirror, there are two possibilities:

- The $ i $ -th mirror tells Creatnx that he is beautiful. In this case, if $ i = n $ Creatnx will stop and become happy, otherwise he will continue asking the $ i+1 $ -th mirror next day;
- In the other case, Creatnx will feel upset. The next day, Creatnx will start asking from the checkpoint with a maximal number that is less or equal to $ i $ .

There are some changes occur over time: some mirrors become new checkpoints and some mirrors are no longer checkpoints. You are given $ q $ queries, each query is represented by an integer $ u $ : If the $ u $ -th mirror isn't a checkpoint then we set it as a checkpoint. Otherwise, the $ u $ -th mirror is no longer a checkpoint.

After each query, you need to calculate [the expected number](https://en.wikipedia.org/wiki/Expected_value) of days until Creatnx becomes happy.

Each of this numbers should be found by modulo $ 998244353 $ . Formally, let $ M = 998244353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test after the first query, the first and the second mirrors are checkpoints. Creatnx will ask the first mirror until it will say that he is beautiful, after that he will ask the second mirror until it will say that he is beautiful because the second mirror is a checkpoint. After that, he will become happy. Probabilities that the mirrors will say, that he is beautiful are equal to $ \frac{1}{2} $ . So, the expected number of days, until one mirror will say, that he is beautiful is equal to $ 2 $ and the answer will be equal to $ 4 = 2 + 2 $ .

## 样例 #1

### 输入

```
2 2
50 50
2
2
```

### 输出

```
4
6
```

## 样例 #2

### 输入

```
5 5
10 20 30 40 50
2
3
4
5
3
```

### 输出

```
117
665496274
332748143
831870317
499122211
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Beautiful Mirrors with queries 深入学习指南 💡

<introduction>
今天我们来一起分析“Beautiful Mirrors with queries”这道C++编程题。这道题结合了期望动态规划（DP）和数据结构维护，是一道非常经典的算法题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（DP）与数据结构维护（set/线段树）

🗣️ **初步分析**：
解决这道题的关键在于理解期望的动态规划递推，并通过数据结构高效维护检查点的变化。简单来说，动态规划（DP）是一种通过分解问题为子问题并利用子问题解来构建原问题解的方法。在本题中，我们需要计算从一个检查点到下一个检查点的期望步数，而每次修改检查点时，只需调整相邻区间的贡献即可。

- **题解思路**：所有优质题解的核心思路是将问题分解为多个检查点之间的区间，每个区间的期望可以预处理并快速计算。通过维护检查点集合（如使用`set`），每次修改时找到相邻检查点，调整总期望的贡献。
- **核心难点**：如何将期望分解为区间贡献，以及如何高效维护这些区间的动态变化。
- **可视化设计**：我们将设计一个8位像素风格的动画，用不同颜色的方块表示检查点，动态展示检查点的插入/删除操作，以及对应区间期望的加减过程。关键步骤（如计算区间期望、更新总期望）会用高亮和音效提示。

---

## 2. 精选优质题解参考

<eval_intro>
为了帮助大家理解，我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解（评分≥4星）：
</eval_intro>

**题解一：作者Zimo_666**
* **点评**：此题解思路非常清晰，首先通过简化问题（无检查点修改）推导出期望公式，再扩展到动态检查点的情况。代码中使用`set`维护检查点，预处理前缀积和前缀和数组，实现了O(q log n)的高效查询。变量命名规范（如`edf`表示后缀积，`sum`表示前缀和），边界处理严谨，是竞赛中典型的高效解法。

**题解二：作者Lvlinxi2010**
* **点评**：此题解通过弱化版问题（CF1265E）的推导，逐步扩展到本题，逻辑推导过程详细。代码结构简洁，核心函数`calc(l, r)`直接计算区间期望，`set`操作清晰，适合作为学习动态维护检查点的参考。

**题解三：作者Rainbow_qwq**
* **点评**：此题解用模块化的`modint`处理模运算，代码风格优雅。通过预处理`mul`（前缀积）和`sum`（前缀积的前缀和），快速计算区间期望，与`set`结合实现动态维护。关键步骤注释明确，适合理解期望分解的核心逻辑。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题时，我们通常会遇到以下关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何推导检查点之间的期望公式？**
    * **分析**：对于两个相邻检查点`l`和`r`，期望步数可以分解为从`l`走到`r`的所有中间镜子的期望之和。通过递推可得，该期望等于`(1/p_{r-1} + 1/(p_{r-1}p_{r-2}) + ... + 1/(p_{r-1}...p_l))`。优质题解通过预处理前缀积和前缀和，将此公式转化为`(sum[r-2] - sum[l-1])/prod[l-1] + 1) / prod[r-1]`，实现O(1)计算。
    * 💡 **学习笔记**：期望的分解是关键，将大问题拆分为多个独立区间的贡献，便于动态维护。

2.  **关键点2：如何高效维护检查点的动态变化？**
    * **分析**：每次修改检查点时，需要找到其前驱和后继检查点（使用`set`的`lower_bound`和`upper_bound`方法），然后调整总期望：插入检查点时，减去原区间贡献，加上两个新区间的贡献；删除时反之。`set`的查找和插入操作时间复杂度为O(log n)，保证了整体效率。
    * 💡 **学习笔记**：数据结构的选择很重要，`set`的有序性和快速查找是维护动态检查点的关键。

3.  **关键点3：如何处理模运算和逆元？**
    * **分析**：题目要求结果对`998244353`取模，且涉及分数运算（如`1/p_i`）。优质题解通过预处理逆元（如`ip[i] = inv(p[i])`），将除法转换为乘法，避免直接计算分数。例如，`1/p_i`等价于`p_i`的逆元。
    * 💡 **学习笔记**：模运算中，除法需转换为乘逆元，预处理逆元可以提高计算效率。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题分解**：将复杂问题（动态检查点的期望）拆分为多个独立区间的期望之和。
- **预处理优化**：预处理前缀积和前缀和，将区间期望的计算时间从O(n)降为O(1)。
- **数据结构选择**：使用`set`维护检查点，利用其有序性快速找到相邻检查点。
- **模运算处理**：预处理逆元，将除法转换为乘法，避免直接计算分数。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Zimo_666和Lvlinxi2010的思路，使用`set`维护检查点，预处理前缀积和前缀和，实现高效动态维护。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int MOD = 998244353;
    const int N = 2e5 + 10;

    ll p[N], prod[N], sum[N];
    set<int> checkpoints;

    ll qpow(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    ll inv(ll x) { return qpow(x, MOD - 2); }

    ll calc(int l, int r) {
        if (l >= r) return 0;
        ll numerator = (sum[r - 2] - sum[l - 1] + MOD) % MOD;
        numerator = numerator * inv(prod[l - 1]) % MOD;
        numerator = (numerator + 1) % MOD;
        ll denominator = prod[r - 1] * inv(prod[l - 1]) % MOD;
        return numerator * inv(denominator) % MOD;
    }

    int main() {
        int n, q;
        scanf("%d%d", &n, &q);
        ll inv100 = inv(100);
        prod[0] = 1;
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &p[i]);
            p[i] = p[i] * inv100 % MOD;
            prod[i] = prod[i - 1] * p[i] % MOD;
            sum[i] = (sum[i - 1] + prod[i]) % MOD;
        }
        checkpoints.insert(1);
        checkpoints.insert(n + 1);
        ll ans = calc(1, n + 1);
        while (q--) {
            int x;
            scanf("%d", &x);
            auto it = checkpoints.lower_bound(x);
            int l = *prev(it), r = *it;
            if (checkpoints.count(x)) {
                ans = (ans - calc(l, x) - calc(x, r) + calc(l, r) + 2 * MOD) % MOD;
                checkpoints.erase(x);
            } else {
                ans = (ans + calc(l, x) + calc(x, r) - calc(l, r) + 2 * MOD) % MOD;
                checkpoints.insert(x);
            }
            printf("%lld\n", ans);
        }
        return 0;
    }
    ```
* **代码解读概要**：
    该代码首先预处理`prod`（前缀积）和`sum`（前缀积的前缀和），用于快速计算区间期望。`checkpoints`集合维护当前所有检查点。每次查询时，找到修改点的前驱和后继检查点，调整总期望的贡献（插入时加新区间，删除时减旧区间）。核心函数`calc(l, r)`利用预处理数组，O(1)计算区间`[l, r)`的期望。

---
<code_intro_selected>
接下来，我们将逐一剖析筛选出的优质题解中，最能体现核心逻辑的C++实现片段。
</code_intro_selected>

**题解一：作者Zimo_666**
* **亮点**：预处理`edf`（后缀积）和`sum`（后缀积的前缀和），通过`calc(l, r)`快速计算区间期望。
* **核心代码片段**：
    ```cpp
    int calc(int l, int r) {
        return ((sum[r-2] - sum[l-1] + mod) % mod * lg_get._inv(edf[l-1]) + 1) % mod * edf[l-1] % mod * lg_get._inv(edf[r-1]) % mod;
    }
    ```
* **代码解读**：
    这段代码计算区间`[l, r)`的期望。`sum[r-2] - sum[l-1]`是后缀积的区间和，除以`edf[l-1]`（即`prod[l-1]`）得到分子部分，加1后除以`edf[r-1]/edf[l-1]`（即`prod[r-1]/prod[l-1]`）得到最终期望。这里通过逆元处理模运算，确保计算正确。
* 💡 **学习笔记**：预处理后缀积和前缀和是快速计算区间期望的关键，逆元处理模运算中的除法。

**题解二：作者Lvlinxi2010**
* **亮点**：代码结构简洁，`calc(l, r)`函数直接实现区间期望的计算，`set`操作清晰。
* **核心代码片段**：
    ```cpp
    ll calc(int l, int r) {
        return ((s[r-2] - s[l-1] + mod) % mod * qpow(a[l-1], mod-2) % mod + 1) * a[l-1] % mod * qpow(a[r-1], mod-2) % mod;
    }
    ```
* **代码解读**：
    该函数与Zimo_666的`calc`类似，`s`是前缀积的前缀和，`a`是前缀积。通过`qpow`计算逆元，将除法转换为乘法，确保模运算正确。
* 💡 **学习笔记**：前缀积和前缀和的预处理是通用技巧，适用于类似区间乘积求和问题。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解检查点修改和期望计算的过程，我设计了一个8位像素风格的动画演示方案，帮助大家“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素镜子探险`  
  背景设定为一个复古游戏场景，Creatnx需要通过一排镜子（用像素方块表示），检查点用金色方块标记，普通镜子用蓝色方块。

  * **核心演示内容**：  
  展示检查点的插入/删除操作，以及对应区间期望的加减过程。例如，插入检查点时，原区间（蓝色）被拆分为两个新区间（绿色和紫色），总期望数值动态更新。

  * **设计思路简述**：  
  采用8位像素风（FC红白机风格），用不同颜色区分检查点和普通镜子；关键操作（如插入检查点）用闪烁和音效提示，增强记忆点。步进控制和自动播放模式让学习者可以逐步观察算法流程。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕左侧显示镜子序列（1到n的像素方块，初始时镜子1为金色，其他为蓝色）。
        - 右侧显示控制面板（开始/暂停、单步、重置按钮，速度滑块）和当前总期望数值。
        - 播放8位风格的轻松背景音乐。

    2.  **检查点修改操作**：  
        - 当用户点击修改检查点`x`时，镜子`x`颜色变化（金色↔蓝色），伴随“叮”的音效。
        - 自动找到`x`的前驱`l`和后继`r`，用红色箭头标记这三个点。

    3.  **区间期望计算**：  
        - 原区间`[l, r)`用蓝色高亮，显示其贡献值（如“原贡献：100”）。
        - 插入`x`后，新区间`[l, x)`和`[x, r)`分别用绿色和紫色高亮，显示各自的贡献值（如“新贡献：40+60”）。
        - 总期望数值从“100”变为“40+60=100”（插入时）或反向变化（删除时），伴随“滴”的音效。

    4.  **自动演示模式**：  
        - 点击“AI演示”后，算法自动执行所有查询，快速展示检查点修改和期望更新的过程，类似“自动寻路”的游戏效果。

    5.  **目标达成提示**：  
        - 当所有镜子通过时，播放“胜利”音效，总期望数值用金色闪烁，庆祝动画（像素星星）出现。

  * **旁白提示**：  
      - （单步执行时）“现在，我们插入检查点2，原区间[1,3)的贡献是100，现在拆分为[1,2)和[2,3)，贡献分别是40和60，总期望变为40+60=100。”
      - （高亮检查点）“金色方块是检查点，失败时会回到这里重新开始。”

<visualization_conclusion>
通过这样的像素动画，我们可以直观看到检查点修改如何影响总期望，理解区间分解和动态维护的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考该算法/技巧的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
      本题的核心是“区间分解+动态维护”，这种思路适用于：
      - 动态修改区间属性并求全局和（如动态树、线段树维护区间和）。
      - 期望问题中，将总期望分解为独立子问题的期望和（如多阶段决策问题）。
      - 其他需要快速查询和修改区间贡献的问题（如动态连通性问题）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P5024** - `保卫王国`  
        * 🗣️ **推荐理由**：这道题使用动态DP（矩阵树）维护树链的贡献，与本题的“区间分解+动态维护”思路类似，适合巩固动态规划与数据结构结合的能力。
    2.  **洛谷 CF1265E** - `Beautiful Mirrors`  
        * 🗣️ **推荐理由**：本题的弱化版，无检查点修改，适合先练习基础期望DP，再挑战本题。
    3.  **洛谷 P3372** - `线段树模板`  
        * 🗣️ **推荐理由**：线段树是动态维护区间和的经典数据结构，本题中`set`的使用可视为一种简化的线段树应用，练习线段树有助于深入理解动态维护的本质。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
在提供的题解中，部分作者分享了调试和思考的经验，这些对我们很有启发：
</insights_intro>

> **参考经验 (来自作者Zimo_666)**：“在预处理前缀积和前缀和时，需要注意模运算的减法可能产生负数，要加上模数再取模。例如，`sum[r-2] - sum[l-1]`可能为负，需要加上`mod`后再取模。”

> **点评**：这位作者的经验提醒我们，模运算中的减法需要特别处理，避免负数导致的错误。在实际编码中，类似的边界条件（如区间左端点大于右端点）也需要仔细检查，确保计算的正确性。

-----

<conclusion>
本次关于“Beautiful Mirrors with queries”的C++解题分析就到这里。希望这份学习指南能帮助大家理解期望DP的核心思想，掌握动态维护检查点的技巧。记住，编程能力的提升在于持续学习和实践，下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：150.37秒