# 题目信息

# Beautiful Bracket Sequence (easy version)

## 题目描述

This is the easy version of this problem. The only difference is the limit of $ n $ - the length of the input string. In this version, $ 1 \leq n \leq 2000 $ . The hard version of this challenge is not offered in the round for the second division.

Let's define a correct bracket sequence and its depth as follow:

- An empty string is a correct bracket sequence with depth $ 0 $ .
- If "s" is a correct bracket sequence with depth $ d $ then "(s)" is a correct bracket sequence with depth $ d + 1 $ .
- If "s" and "t" are both correct bracket sequences then their concatenation "st" is a correct bracket sequence with depth equal to the maximum depth of $ s $ and $ t $ .

For a (not necessarily correct) bracket sequence $ s $ , we define its depth as the maximum depth of any correct bracket sequence induced by removing some characters from $ s $ (possibly zero). For example: the bracket sequence $ s =  $ "())(())" has depth $ 2 $ , because by removing the third character we obtain a correct bracket sequence "()(())" with depth $ 2 $ .

Given a string $ a $ consists of only characters '(', ')' and '?'. Consider all (not necessarily correct) bracket sequences obtained by replacing all characters '?' in $ a $ by either '(' or ')'. Calculate the sum of all the depths of all these bracket sequences. As this number can be large, find it modulo $ 998244353 $ .

Hacks in this problem in the first division can be done only if easy and hard versions of this problem was solved.

## 说明/提示

In the first test case, we can obtain $ 4 $ bracket sequences by replacing all characters '?' with either '(' or ')':

- "((". Its depth is $ 0 $ ;
- "))". Its depth is $ 0 $ ;
- ")(". Its depth is $ 0 $ ;
- "()". Its depth is $ 1 $ .

So, the answer is $ 1 = 0 + 0 + 0 + 1 $ .

In the second test case, we can obtain $ 4 $ bracket sequences by replacing all characters '?' with either '(' or ')':

- "(((())". Its depth is $ 2 $ ;
- "()()))". Its depth is $ 2 $ ;
- "((()))". Its depth is $ 3 $ ;
- "()(())". Its depth is $ 2 $ .

So, the answer is $ 9 = 2 + 2 + 3 + 2 $ .

## 样例 #1

### 输入

```
??
```

### 输出

```
1
```

## 样例 #2

### 输入

```
(?(?))
```

### 输出

```
9
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Beautiful Bracket Sequence (easy version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Beautiful Bracket Sequence (easy version)”这道题。这道题需要计算所有可能的括号序列（将问号替换为左或右括号）的深度之和。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：组合数学应用 (涉及组合数计算、前缀和预处理、范德蒙德卷积优化)

🗣️ **初步分析**：
解决这道题的关键在于将深度问题转化为左右括号的最小数量问题。简单来说，组合数学就像“分糖果”——我们需要计算所有可能的“分配方式”（即问号替换为左/右括号的方式），并统计每种方式的贡献（深度）。在本题中，深度是左右两侧左括号和右括号数量的较小值的最大值，因此我们需要枚举分界点，计算左右两侧的括号和问号能提供的有效括号数，用组合数统计贡献。

- **题解思路**：多数题解通过枚举分界点（将序列分为左右两部分），计算左侧能提供的左括号数（原左括号数+部分问号变左括号）和右侧能提供的右括号数（原右括号数+部分问号变右括号），然后用组合数计算每种可能的深度的贡献之和。例如，若左侧有a个左括号、x个问号，右侧有b个右括号、y个问号，当左侧选i个问号变左括号时，右侧需选(i + a - b)个问号变右括号，此时深度为i + a，贡献为i + a乘以对应的组合数。
- **核心难点**：如何高效计算不同情况下的组合数贡献，以及如何处理问号的不确定性。
- **可视化设计**：我们将设计一个8位像素动画，用不同颜色的方块表示左括号（蓝色）、右括号（红色）、问号（黄色）。动画中，分界点会用绿色箭头标记，左右两侧的问号会动态“切换”颜色（黄→蓝或黄→红），同时显示当前组合数的计算过程，关键步骤伴随“叮”的音效，最终深度累加时播放轻快的音乐。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解：
</eval_intro>

**题解一：letitdown (赞：11)**
* **点评**：此题解思路非常清晰，通过枚举分界点并利用组合数公式直接计算贡献，避免了复杂的动态规划。代码中预处理了阶乘和逆元，确保了组合数计算的高效性。特别是将原式拆分为两部分并利用范德蒙恒等式优化，将时间复杂度从O(n²)优化到O(n)，这是非常值得学习的亮点。代码结构简洁，变量命名规范（如jc表示阶乘，inv表示逆元），边界处理严谨，适合直接用于竞赛。

**题解二：Genius_Star (赞：3)**
* **点评**：此题解对小白非常友好，详细解释了思路的推导过程，包括如何将深度转化为左右括号的最小数量问题，以及如何拆分式子并利用范德蒙德卷积优化。代码中使用了清晰的变量名（如a表示左括号数，b表示右括号数），并通过预处理阶乘和逆元确保组合数计算的准确性。特别地，作者将复杂的求和式子拆分为两部分，分别用组合数性质化简，这种拆分技巧对解决类似问题很有启发。

**题解三：Link_Cut_Y (赞：2)**
* **点评**：此题解提供了动态规划和组合数学两种思路，拓宽了学习者的视野。动态规划部分（f[i][j]表示前i个字符有j个左括号的方案数）状态定义清晰，转移逻辑直接；组合数学部分（枚举分界点计算贡献）与其他题解思路一致，但代码结构更模块化（如预处理前缀和）。代码中使用了循环展开和取模优化，体现了良好的编程习惯。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何将深度转化为左右括号的最小数量问题？
    * **分析**：深度是所有可能的正确括号子序列的最大深度。通过观察，最优的正确子序列一定是“左括号尽可能多，右括号尽可能多”的结构，即左侧选k个左括号，右侧选k个右括号，此时深度为k。因此，深度等于左右两侧能提供的左、右括号数的较小值的最大值。
    * 💡 **学习笔记**：深度的本质是左右括号的“平衡”，找到最大的k，使得左侧能提供至少k个左括号，右侧能提供至少k个右括号。

2.  **关键点2**：如何高效计算组合数贡献？
    * **分析**：对于分界点i，左侧有a个左括号、x个问号，右侧有b个右括号、y个问号。要使得左侧能提供k个左括号（k ≥ a），需选(k - a)个问号变左括号；右侧需选(k - b)个问号变右括号（k ≥ b）。贡献为k × C(x, k - a) × C(y, k - b)。直接枚举k会得到O(n²)的复杂度，优质题解通过范德蒙恒等式将其优化到O(n)。
    * 💡 **学习笔记**：组合数的化简是关键，利用范德蒙恒等式（如∑C(m, i)C(n, k-i) = C(m+n, k)）可以大幅降低计算量。

3.  **关键点3**：如何处理问号的不确定性？
    * **分析**：问号可以变为左或右括号，因此需要统计所有可能的替换方式。通过前缀和预处理左括号、右括号、问号的数量，可以快速获取任意区间内的各类括号数，从而计算组合数。
    * 💡 **学习笔记**：前缀和是处理区间统计问题的常用工具，能有效减少重复计算。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题转化**：将深度问题转化为左右括号的最小数量问题，简化计算。
- **组合数预处理**：预处理阶乘和逆元，快速计算组合数，避免重复计算。
- **前缀和优化**：预处理各位置的左括号、右括号、问号数量，快速获取区间信息。
- **公式化简**：利用范德蒙恒等式等组合数性质，将复杂求和式化简为简单组合数，降低时间复杂度。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了letitdown和Genius_Star的题解思路，基于组合数学和前缀和预处理，实现了高效的深度和计算。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MOD = 998244353;
    const int MAXN = 2005; // 题目中n≤2000

    int n;
    char s[MAXN];
    int jc[MAXN], inv[MAXN]; // 阶乘和逆元
    int pre_left[MAXN], pre_q[MAXN]; // 前缀和：左括号数、问号数
    int suf_right[MAXN], suf_q[MAXN]; // 后缀和：右括号数、问号数

    int qpow(int a, int b) {
        int res = 1;
        while (b) {
            if (b & 1) res = 1LL * res * a % MOD;
            a = 1LL * a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    void init() {
        jc[0] = 1;
        for (int i = 1; i < MAXN; ++i) jc[i] = 1LL * jc[i - 1] * i % MOD;
        inv[MAXN - 1] = qpow(jc[MAXN - 1], MOD - 2);
        for (int i = MAXN - 2; i >= 0; --i) inv[i] = 1LL * inv[i + 1] * (i + 1) % MOD;
    }

    int C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return 1LL * jc[n] * inv[k] % MOD * inv[n - k] % MOD;
    }

    int main() {
        init();
        scanf("%s", s + 1);
        n = strlen(s + 1);

        // 预处理前缀和
        for (int i = 1; i <= n; ++i) {
            pre_left[i] = pre_left[i - 1] + (s[i] == '(');
            pre_q[i] = pre_q[i - 1] + (s[i] == '?');
        }
        // 预处理后缀和
        for (int i = n; i >= 1; --i) {
            suf_right[i] = suf_right[i + 1] + (s[i] == ')');
            suf_q[i] = suf_q[i + 1] + (s[i] == '?');
        }

        int ans = 0;
        for (int i = 1; i < n; ++i) { // 枚举分界点i（左侧[1,i]，右侧[i+1,n]）
            int a = pre_left[i];      // 左侧原左括号数
            int x = pre_q[i];         // 左侧问号数
            int b = suf_right[i + 1]; // 右侧原右括号数
            int y = suf_q[i + 1];     // 右侧问号数

            // 计算贡献：a*C(x+y, y + b - a) + x*C(x+y-1, y + b - a - 1)
            int term1 = 1LL * a * C(x + y, y + b - a) % MOD;
            int term2 = 1LL * x * C(x + y - 1, y + b - a - 1) % MOD;
            ans = (ans + term1 + term2) % MOD;
        }
        printf("%d\n", ans);
        return 0;
    }
    ```
* **代码解读概要**：
    > 该代码首先预处理阶乘和逆元，用于快速计算组合数。然后通过前缀和数组`pre_left`、`pre_q`统计左侧的左括号和问号数，通过后缀和数组`suf_right`、`suf_q`统计右侧的右括号和问号数。接着枚举分界点i，计算左右两侧的括号和问号数，利用组合数公式直接计算贡献，最终累加得到答案。

---
<code_intro_selected>
接下来，我们将逐一剖析筛选出的优质题解中，最能体现核心逻辑的C++实现片段，并点出各自的亮点和关键代码思路。
</code_intro_selected>

**题解一：letitdown (来源：用户题解)**
* **亮点**：利用范德蒙恒等式将复杂求和式化简为两个组合数，时间复杂度O(n)，代码简洁高效。
* **核心代码片段**：
    ```cpp
    (ans += (1ll*l*C(u+v,v-l+r)%mod + 1ll*u*C(u+v-1,r+v-l-1)%mod)%mod) %= mod;
    ```
* **代码解读**：
    > 这段代码计算了分界点i的贡献。其中，`l`是左侧原左括号数，`u`是左侧问号数，`r`是右侧原右括号数，`v`是右侧问号数。`C(u+v, v-l+r)`对应左侧选i个问号变左括号、右侧选(i + l - r)个问号变右括号的方案数乘以l；`C(u+v-1, r+v-l-1)`对应i个问号变左括号的贡献乘以u。两者相加即为当前分界点的总贡献。
* 💡 **学习笔记**：范德蒙恒等式能将求和式转化为单个组合数，大幅简化计算，是组合数学中的重要技巧。

**题解二：Genius_Star (来源：用户题解)**
* **亮点**：详细推导了式子的拆分过程，利用组合数性质将原式拆分为两部分，分别用范德蒙恒等式化简。
* **核心代码片段**：
    ```cpp
    ans=Add(ans,(b*C(x+y,x+a-b)%mod + y*C(x+y-1,x+a-b-1)%mod)%mod);
    ```
* **代码解读**：
    > 这段代码中，`x`是左侧问号数，`a`是左侧原左括号数，`y`是右侧问号数，`b`是右侧原右括号数。`C(x+y, x+a-b)`对应右侧选(a + x - b)个问号变右括号的方案数乘以b；`C(x+y-1, x+a-b-1)`对应左侧选(a + x - b)个问号变左括号的方案数乘以y。两者相加即为当前分界点的贡献。
* 💡 **学习笔记**：拆分式子是解决复杂组合问题的常用方法，能将大问题分解为可处理的小问题。

**题解三：Link_Cut_Y (来源：用户题解)**
* **亮点**：提供了动态规划和组合数学两种思路，动态规划部分状态定义清晰，转移逻辑直接。
* **核心代码片段（动态规划部分）**：
    ```cpp
    f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod; // s[i]是'('或'?'，选作'('
    f[i][j] = (f[i][j] + f[i - 1][j]) % mod;     // s[i]是')'或'?'，选作')'
    ```
* **代码解读**：
    > `f[i][j]`表示前i个字符有j个左括号的方案数。当s[i]是'('或'?'时，前i-1个字符有j-1个左括号的方案数可以转移到当前状态；当s[i]是')'或'?'时，前i-1个字符有j个左括号的方案数可以转移到当前状态。通过这种方式，动态规划统计了所有可能的左括号数量的方案数。
* 💡 **学习笔记**：动态规划的状态定义需准确反映子问题的解，转移方程要覆盖所有可能情况。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解组合数学方法是如何计算深度和的，我设计了一个8位像素风格的动画演示方案，让我们“看”到每个分界点的贡献是如何计算的！
</visualization_intro>

  * **动画演示主题**：`像素括号探险——计算深度大作战`

  * **核心演示内容**：展示枚举分界点时，左右两侧的左括号（蓝色方块）、右括号（红色方块）、问号（黄色方块）的数量变化，以及组合数计算的过程，最终累加所有分界点的贡献得到答案。

  * **设计思路简述**：采用8位像素风格（类似FC游戏），通过颜色区分不同类型的括号，动态显示问号“变身”为左/右括号的过程。关键步骤（如分界点选择、组合数计算）伴随“叮”的音效，增强操作记忆；完成所有计算后播放胜利音效，增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为左右两部分，左侧显示原括号序列（蓝色：左括号，红色：右括号，黄色：问号），右侧显示控制面板（单步/自动播放按钮、速度滑块）。
          * 底部显示当前分界点i（用绿色箭头标记），以及左右两侧的统计信息（左括号数a、问号数x；右括号数b、问号数y）。

    2.  **枚举分界点**：
          * 绿色箭头从左到右移动，每停在一个位置i，左侧区域高亮显示[1,i]，右侧区域高亮显示[i+1,n]。
          * 左侧的黄色问号方块开始“闪烁”，表示它们可以变身为左括号；右侧的黄色问号方块同样闪烁，表示可以变身为右括号。

    3.  **组合数计算**：
          * 左侧的问号方块逐个变蓝（表示选为左括号），右侧的问号方块逐个变红（表示选为右括号），每完成一次选择，屏幕上方显示对应的组合数C(x, k-a)和C(y, k-b)，并计算贡献k × C(x, k-a) × C(y, k-b)。
          * 贡献值用金色数字从下往上飘动，累加到总答案中（总答案显示在屏幕顶部）。

    4.  **自动演示模式**：
          * 点击“AI自动演示”，箭头自动遍历所有分界点，问号方块快速切换颜色，组合数计算过程加速播放，总答案动态更新。

    5.  **完成状态**：
          * 所有分界点处理完毕后，总答案以大字体显示，伴随“胜利”音效（如8位风格的短旋律），屏幕下方弹出“深度和计算完成！”的提示。

  * **旁白提示**：
      * （箭头移动时）“现在我们枚举分界点i，将序列分为左右两部分。”
      * （问号闪烁时）“问号可以变身为左或右括号，这里我们计算所有可能的变身方式。”
      * （组合数显示时）“这是组合数C(x, k-a)，表示从x个问号中选k-a个变左括号的方案数。”
      * （贡献累加时）“这个分界点的贡献是k乘以两个组合数的乘积，累加到总答案中。”

<visualization_conclusion>
通过这样的像素动画，我们不仅能看到每个分界点的贡献是如何计算的，还能直观理解组合数学在括号序列问题中的应用。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考组合数学在括号序列问题中的其他应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 组合数学中的前缀和预处理、组合数化简（如范德蒙恒等式）不仅能解决本题，还常用于处理类似“统计所有可能情况的贡献和”的问题，例如：
        - 统计所有可能的子序列的某种特征和（如最长递增子序列长度和）。
        - 处理带问号的字符串问题（如统计合法字符串的数量）。
        - 计算排列组合中的期望或方差。

  * **练习推荐 (洛谷)**：
    以下是几道洛谷上与本题考察知识点相关的题目，建议大家尝试练习：

    1.  **洛谷 P1115 最大子段和**
          * 🗣️ **推荐理由**：这道题需要统计所有子段的和的最大值，与本题的“统计所有可能情况的深度和”类似，需要枚举分界点并计算贡献，能帮助巩固前缀和和组合数的应用。

    2.  **洛谷 P1044 栈**
          * 🗣️ **推荐理由**：这道题涉及括号匹配的经典问题（卡特兰数），与本题的括号序列深度问题相关，能帮助理解合法括号序列的结构。

    3.  **洛谷 P1313 计算系数**
          * 🗣️ **推荐理由**：这道题需要计算二项式展开式的系数，与本题的组合数计算直接相关，能帮助强化组合数的预处理和应用能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
虽然部分题解未明确提及个人心得，但通过分析可以总结出以下宝贵经验：
</insights_intro>

> 参考经验（来自多个题解）：在处理带问号的括号序列问题时，预处理前缀和和后缀和能大幅提高效率；组合数的预处理（阶乘和逆元）是解决此类问题的关键，需注意边界条件（如k < 0或k > n时组合数为0）。

**点评**：这些经验提醒我们，预处理是解决复杂组合问题的重要步骤，而边界条件的处理直接影响代码的正确性。在实际编程中，建议先画流程图理清思路，再编写代码，并通过小测试用例验证边界条件。

-----

<conclusion>
本次关于“Beautiful Bracket Sequence (easy version)”的C++解题分析就到这里。希望这份学习指南能帮助大家更好地理解组合数学在括号序列问题中的应用。记住，编程能力的提升在于持续学习、勤于思考和勇于实践。下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：197.82秒