# 题目信息

# I Love Balls

## 题目描述

Alice and Bob are playing a game. There are $ n $ balls, out of which $ k $ are special. Each ball has a value associated with it.

The players play turn by turn. In each turn, the player randomly picks a ball and adds the value of the ball to their score, which is $ 0 $ at the beginning of the game. The selected ball is removed from the game. If the ball was special, the same player takes the next turn if at least one ball is remaining. If the ball picked was not special, the next player plays their turn.

They play this game until no balls are remaining in the game. Alice plays first.

Find the expected score that both the players have at the end of the game modulo $ 10^9+7 $ .

Formally, let $ M = 10^9+7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, Alice's expected score is $ 45 $ , and Bob's is $ 30 $ at the end of the game.

## 样例 #1

### 输入

```
1
5 2
10 20 5 15 25```

### 输出

```
45 30```

## 样例 #2

### 输入

```
5
1 1
732507
2 2
5817860 5398510
5 1
2122894 4951549 2750585 7821535 3214167
8 4
1405323 5069867 6883092 6972029 328406 2478975 7628890 9973340
4 2
9662050 3566134 3996473 9872255```

### 输出

```
732507 0
11216370 0
810642660 210218077
722402997 318336932
349086489 678010430```

## 样例 #3

### 输入

```
5
3 3
1095611 8219204 7773462
2 1
8176490 2774103
3 1
9178636 5138057 3367761
12 9
7597698 6843019 2298534 1522386 4969588 1340345 3967362 9152890 6689668 9986080 4745473 7407325
10 5
6986368 2397882 5804127 6980694 3740836 3215836 5195724 3179261 4136769 4544231```

### 输出

```
17088277 0
6862348 4088245
677038671 340645790
36949997 29570371
725118051 321063684```

# AI分析结果

---
# 💡 Kay的C++算法解析：I Love Balls 深入学习指南 💡

<introduction>
今天我们来一起分析“ILoveBalls”这道C++编程题。这道题涉及概率期望的计算，需要我们理解如何将复杂的取球过程转化为数学概率问题。本指南将帮助大家梳理题目思路，掌握核心算法，并通过代码和可视化加深理解。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学概率与期望计算`

🗣️ **初步分析**：
解决这道题的关键在于理解每个球被Alice或Bob取到的概率，并利用线性期望的性质（总期望等于各独立事件期望之和）计算总得分。简单来说，期望计算就像“分蛋糕”——每个球的价值是蛋糕块，我们需要算出Alice和Bob各自能分到多少块的概率，再乘以块的大小。

在本题中，取球过程可以等价为球的一个排列（所有球被取的顺序是随机的）。核心难点在于：
- 特殊球的连续取球规则会影响玩家轮换，如何将其转化为“段”的概念？
- 普通球和特殊球的概率如何分别计算？

各题解的共性思路是将问题拆解为两类球的贡献：
1. **普通球**：总共有 $n-k$ 个，它们将整个取球过程划分为 $n-k$ 个“段”（每段以普通球结尾），Alice取奇数段的普通球，概率为 $\frac{\lceil (n-k)/2 \rceil}{n-k}$。
2. **特殊球**：分布在 $n-k+1$ 个“段”（包括普通球划分的段和末尾无普通球的段），Alice取奇数段的特殊球，概率为 $\frac{\lceil (n-k+1)/2 \rceil}{n-k+1}$。

可视化设计思路：采用8位像素风格，用不同颜色的方块表示普通球（蓝色）和特殊球（红色）。动画中，普通球会将屏幕横向划分为若干段（用虚线分隔），特殊球随机分配到各段。每段的奇偶性用背景色区分（奇数段绿色，偶数段黄色），Alice取绿色段的球，Bob取黄色段的球。关键步骤（如段划分、球分配）会高亮并伴随“叮”的音效，帮助理解概率计算逻辑。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，以下题解表现突出（≥4星），值得重点学习：
</eval_intro>

**题解一：DrAlfred（赞：2）**
* **点评**：此题解思路清晰，将问题拆解为特殊球和普通球的贡献，并通过数学推导得出概率公式。代码使用`ModInt`类封装模运算，规范且易懂，边界处理严谨（如模逆元计算）。亮点在于将概率计算与模运算结合，直接输出结果，适合竞赛场景。

**题解二：Ether13（赞：10）**
* **点评**：此题解用“段”的概念简化问题，明确指出普通球划分段数和特殊球分布段数，逻辑直白。代码片段简洁，关键变量（如`invn`、`invn1`）命名清晰，直接计算概率并累加，实践价值高。

**题解三：TTpandaS（赞：7）**
* **点评**：此题解抓住问题本质，直接点明“每个球的贡献等于权值乘被Alice取到的概率”，思路简洁。虽未给出完整代码，但概率公式推导明确，对理解核心逻辑有重要启发。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们需要突破以下核心难点，掌握对应的解题策略：
</difficulty_intro>

1.  **关键点1：如何将取球过程转化为“段”的概念？**
    * **分析**：普通球的取球会触发玩家轮换，因此每个普通球将取球过程划分为一个“段”（段内可能包含多个特殊球）。例如，若有3个普通球，则形成3段（每段以普通球结尾）和1个末尾段（无普通球），共4段。特殊球分布在这4段中，普通球分布在3段中。
    * 💡 **学习笔记**：段的划分是连接取球规则与概率计算的桥梁，将复杂的轮换规则转化为段的奇偶性判断。

2.  **关键点2：如何计算特殊球和普通球的概率？**
    * **分析**：普通球的概率由其所在段的奇偶性决定（奇数段归Alice），总共有 $n-k$ 个普通球，奇数段数为 $\lceil (n-k)/2 \rceil$，故概率为 $\frac{\lceil (n-k)/2 \rceil}{n-k}$。特殊球分布在 $n-k+1$ 个段中，奇数段数为 $\lceil (n-k+1)/2 \rceil$，概率为 $\frac{\lceil (n-k+1)/2 \rceil}{n-k+1}$。
    * 💡 **学习笔记**：概率计算的核心是“段的奇偶性”，这需要结合取球顺序的排列等价性（所有排列等概率）。

3.  **关键点3：如何处理模逆元计算？**
    * **分析**：由于结果需要对 $10^9+7$ 取模，且概率涉及分数（如 $\frac{a}{b}$），需用模逆元将除法转化为乘法（即 $a \times b^{-1} \mod 1e9+7$）。代码中通过快速幂计算模逆元（如`qpow(b, mod-2)`）。
    * 💡 **学习笔记**：模逆元是处理分数取模的关键工具，需熟练掌握快速幂实现。

### ✨ 解题技巧总结
- **问题分解**：将复杂问题拆解为普通球和特殊球的独立贡献，利用线性期望的可加性简化计算。
- **排列等价性**：取球过程等价于所有球的一个随机排列，简化概率计算。
- **模运算封装**：使用类或函数封装模加、乘、逆元计算，提高代码可读性和复用性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析题解后，我们选取DrAlfred的代码作为通用核心实现，因其结构清晰、规范，且完整覆盖了所有关键步骤。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了DrAlfred和Ether13的思路，使用模运算类处理概率计算，适用于竞赛场景。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using i64 = long long;
    const int mod = 1e9 + 7;

    template <int MOD>
    struct ModInt {
        i64 x;
        ModInt(i64 x = 0) : x((x % MOD + MOD) % MOD) {}
        ModInt operator+(const ModInt& o) const { return ModInt(x + o.x); }
        ModInt operator-(const ModInt& o) const { return ModInt(x - o.x); }
        ModInt operator*(const ModInt& o) const { return ModInt((__int128)x * o.x % MOD); }
        ModInt operator/(const ModInt& o) const { return *this * o.inv(); }
        ModInt inv() const { return pow(MOD - 2); }
        ModInt pow(i64 b) const {
            ModInt res = 1, a = *this;
            for (; b; b >>= 1, a = a * a) if (b & 1) res = res * a;
            return res;
        }
        friend ostream& operator<<(ostream& os, const ModInt& o) { return os << o.x; }
    };
    using mint = ModInt<mod>;

    void solve() {
        int n, k;
        cin >> n >> k;
        int ns = n - k; // 普通球数量
        vector<mint> v(n);
        for (auto& x : v) cin >> x;

        mint spec_sum = accumulate(v.begin(), v.begin() + k, mint(0)); // 特殊球权值和
        mint non_spec_sum = accumulate(v.begin() + k, v.end(), mint(0)); // 普通球权值和

        // 特殊球被Alice取到的概率：(ns+1)/2 向上取整 / (ns+1)
        mint spec_prob = mint((ns + 1 + 1) / 2) / (ns + 1);
        // 普通球被Alice取到的概率：ns/2 向上取整 / ns
        mint non_spec_prob = mint((ns + 1) / 2) / ns;

        mint alice = spec_prob * spec_sum + non_spec_prob * non_spec_sum;
        mint bob = (spec_sum + non_spec_sum) - alice;

        cout << alice << " " << bob << "\n";
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) solve();
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先定义了模运算类`ModInt`，封装了加减乘除和模逆元计算。`solve`函数读取输入后，分别计算特殊球和普通球的权值和，再根据推导的概率公式计算Alice的期望得分，Bob的得分通过总和减去Alice的得分得到。核心逻辑是概率的计算与权值的加权求和。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点和实现思路。
</code_intro_selected>

**题解一：DrAlfred（来源：用户题解）**
* **亮点**：使用`ModInt`类统一处理模运算，代码简洁规范；概率计算逻辑清晰，直接对应数学公式。
* **核心代码片段**：
    ```cpp
    mint spec_frac = mint(ns / 2 + 1) / (ns + 1);
    mint non_spec_frac = mint((ns + 1) / 2) / ns;
    mint alice = spec_frac * spec + non_spec_frac * non_spec;
    ```
* **代码解读**：
    - `ns`是普通球数量（`n-k`）。`spec_frac`计算特殊球被Alice取到的概率：`(ns+1)/2`向上取整（即`ns/2 + 1`）除以段数`ns+1`。
    - `non_spec_frac`计算普通球被Alice取到的概率：`ns/2`向上取整（即`(ns+1)/2`）除以普通球数量`ns`。
    - `alice`是两类球的贡献之和，体现了线性期望的可加性。
* 💡 **学习笔记**：使用类封装模运算可避免重复代码，提高效率；概率公式的推导是解题的核心，需确保与数学推导一致。

**题解二：Ether13（来源：用户题解）**
* **亮点**：直接计算概率并累加，代码简洁，关键变量命名清晰（如`invn`表示普通球数量的逆元）。
* **核心代码片段**：
    ```cpp
    ll ea=0,eb=0,invn=qpow(n-k,MOD-2),invn1=qpow(n-k+1,MOD-2);
    rep(i,k+1,n){
        ea=(ea+v[i]*((n-k+1)/2)%MOD*invn%MOD)%MOD;
        eb=(eb+v[i]*((n-k)/2)%MOD*invn%MOD)%MOD;
    }
    rep(i,1,k){
        ea=(ea+v[i]*(n/2+1)%MOD*invn1%MOD)%MOD;
        eb=(eb+v[i]*((n+1)/2)%MOD*invn1%MOD)%MOD;
    }
    ```
* **代码解读**：
    - `invn`和`invn1`分别是普通球数量和特殊球段数的模逆元。
    - 第一个循环处理普通球：`(n-k+1)/2`是普通球中奇数段的数量，乘以逆元得到概率，累加到`ea`（Alice得分）。
    - 第二个循环处理特殊球：`(n/2 + 1)`是特殊球中奇数段的数量，乘以逆元得到概率，累加到`ea`。
* 💡 **学习笔记**：直接计算每类球的贡献，避免复杂数据结构，适合快速编码。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“段的划分”和“概率计算”，我们设计了一个8位像素风格的动画，模拟取球过程和概率分布。
</visualization_intro>

  * **动画演示主题**：`像素取球大冒险`
  * **核心演示内容**：展示普通球如何划分段，特殊球如何分布在各段中，以及Alice和Bob如何根据段的奇偶性取球。
  * **设计思路简述**：采用FC红白机风格，用不同颜色区分普通球（蓝色）和特殊球（红色），段用虚线分隔。奇数段背景为绿色（Alice的回合），偶数段为黄色（Bob的回合）。关键操作（如段划分、球分配）伴随“叮”的音效，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕左侧显示像素网格（8x8方块），顶部显示“当前段数”和“当前玩家”。
        - 控制面板包含“单步”“自动播放”“调速”按钮，底部显示当前处理的球类型（普通/特殊）。

    2.  **普通球划分段**：
        - 普通球（蓝色方块）依次出现在网格中，每出现一个普通球，用虚线向下划分一段（如第1个普通球划分第1段，第2个划分第2段）。
        - 音效：每划分一段播放“叮”的短音。

    3.  **特殊球分布段**：
        - 特殊球（红色方块）随机落入各段（包括末尾段），每个段的位置用白色标记。
        - 动画：红色方块从顶部滑入目标段，伴随“咻”的音效。

    4.  **取球过程演示**：
        - 按段的顺序（从第1段到最后一段），奇数段的球（绿色背景）被Alice取走（用白色箭头指向Alice头像），偶数段的球被Bob取走（箭头指向Bob头像）。
        - 音效：取球时播放“啪”的音效，取到特殊球时额外播放“叮”的长音。

    5.  **概率统计**：
        - 动画结束后，屏幕右侧显示“Alice取到X个特殊球，Y个普通球”“Bob取到M个特殊球，N个普通球”。
        - 动态计算概率：X/(k) 和 Y/(n-k) 与理论值对比，用柱状图展示。

  * **旁白提示**：
      - “看！普通球把取球过程分成了3段，每段末尾是普通球哦～”
      - “特殊球可以落在这4个段里（包括最后一段），奇数段的特殊球会被Alice取到～”
      - “现在播放的是自动模式，你可以调慢速度，仔细看每个球的归属！”

<visualization_conclusion>
通过这个动画，我们能直观看到段的划分和球的分布，理解为什么特殊球的概率是段数的奇偶比。像素风格和音效让学习过程更有趣！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是概率期望的计算和问题分解，这类思路可迁移到多种场景。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 排列等价性：许多取球/抽样问题可转化为排列问题，简化概率计算（如抽奖、随机选择）。
      - 线性期望：总期望等于各独立事件期望之和，适用于多阶段决策问题（如游戏得分、任务奖励）。
      - 模逆元处理：涉及分数取模时，需用模逆元转化除法，常见于组合数学和概率问题。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1297** - `单选错位`  
        * 🗣️ **推荐理由**：考察排列等价性和概率计算，与本题思路类似，适合巩固排列与期望的关系。
    2.  **洛谷 P4316** - `绿豆蛙的归宿`  
        * 🗣️ **推荐理由**：涉及期望的动态规划，需分解子问题，锻炼问题拆解能力。
    3.  **洛谷 P3750** - `分手是祝愿`  
        * 🗣️ **推荐理由**：结合概率与贪心策略，需计算不同操作的期望，提升综合解题能力。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了解题过程中的经验，这些对我们很有启发：
</insights_intro>

> **参考经验 (来自 不知名用户)**：“我一开始没看出特殊球的概率规律，后来通过打表发现删掉特殊球不影响概率。这让我意识到，遇到复杂问题时，先尝试小例子找规律是个好方法。”

**点评**：这位作者的经验很实用！在编程竞赛中，打表（计算小数据找规律）是探索问题的重要手段。当数学推导困难时，通过小例子观察结果，可能快速发现隐藏的规律，如本题中特殊球的概率与段数的关系。

---

<conclusion>
本次关于“ILoveBalls”的分析就到这里。通过理解概率分解、段的概念和模运算处理，我们掌握了这类问题的核心解法。希望大家通过练习和动画演示，进一步巩固知识，下次挑战更难的题目！💪
</conclusion>

---
处理用时：137.66秒