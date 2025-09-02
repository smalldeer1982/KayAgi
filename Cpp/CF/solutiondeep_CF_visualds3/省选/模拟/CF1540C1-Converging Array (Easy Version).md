# 题目信息

# Converging Array (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ q = 1 $ . You can make hacks only if both versions of the problem are solved.

There is a process that takes place on arrays $ a $ and $ b $ of length $ n $ and length $ n-1 $ respectively.

The process is an infinite sequence of operations. Each operation is as follows:

- First, choose a random integer $ i $ ( $ 1 \le i \le n-1 $ ).
- Then, simultaneously set $ a_i = \min\left(a_i, \frac{a_i+a_{i+1}-b_i}{2}\right) $ and $ a_{i+1} = \max\left(a_{i+1}, \frac{a_i+a_{i+1}+b_i}{2}\right) $ without any rounding (so values may become non-integer).

 See notes for an example of an operation.It can be proven that array $ a $ converges, i. e. for each $ i $ there exists a limit $ a_i $ converges to. Let function $ F(a, b) $ return the value $ a_1 $ converges to after a process on $ a $ and $ b $ .

You are given array $ b $ , but not array $ a $ . However, you are given a third array $ c $ . Array $ a $ is good if it contains only integers and satisfies $ 0 \leq a_i \leq c_i $ for $ 1 \leq i \leq n $ .

Your task is to count the number of good arrays $ a $ where $ F(a, b) \geq x $ for $ q $ values of $ x $ . Since the number of arrays can be very large, print it modulo $ 10^9+7 $ .

## 说明/提示

The following explanation assumes $ b = [2, 1] $ and $ c=[2, 3, 4] $ (as in the sample).

Examples of arrays $ a $ that are not good:

- $ a = [3, 2, 3] $ is not good because $ a_1 > c_1 $ ;
- $ a = [0, -1, 3] $ is not good because $ a_2 < 0 $ .

One possible good array $ a $ is $ [0, 2, 4] $ . We can show that no operation has any effect on this array, so $ F(a, b) = a_1 = 0 $ .

Another possible good array $ a $ is $ [0, 1, 4] $ . In a single operation with $ i = 1 $ , we set $ a_1 = \min(\frac{0+1-2}{2}, 0) $ and $ a_2 = \max(\frac{0+1+2}{2}, 1) $ . So, after a single operation with $ i = 1 $ , $ a $ becomes equal to $ [-\frac{1}{2}, \frac{3}{2}, 4] $ . We can show that no operation has any effect on this array, so $ F(a, b) = -\frac{1}{2} $ .

## 样例 #1

### 输入

```
3
2 3 4
2 1
1
-1```

### 输出

```
56```

# AI分析结果

---
# 💡 Kay的C++算法解析：Converging Array (Easy Version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Converging Array (Easy Version)”这道C++编程题。这道题看似涉及复杂的“收敛”概念，但通过分析操作性质和转化问题模型，我们可以用动态规划（背包问题）轻松解决。本指南将帮助大家梳理思路，掌握核心算法。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`动态规划（背包问题）`

🗣️ **初步分析**：
> 解决这道题的关键在于理解“收敛”操作的本质，并将其转化为可计算的数学条件。简单来说，动态规划（背包问题）就像“装行李”——我们需要计算满足特定条件的“行李组合”数量。在本题中，“行李”是数组`a`的元素，“条件”是其前缀和需满足稳定状态的约束。

   - **题解思路**：所有题解均通过分析操作性质，推导出稳定状态下数组`d`的约束（如`d_2 ≥ d_1 + b_1`，`d_3 ≥ d_2 + b_2`等），并将问题转化为计算满足前缀和条件的数组`a`的数量。核心难点是将“收敛”条件转化为前缀和的数学约束，解决方案是用动态规划（背包）统计符合条件的前缀和组合。
   - **核心算法流程**：动态规划状态`f[i][j]`表示前`i`项前缀和为`j`的方案数，通过遍历每个元素的可能取值（0到`c_i`），累加满足前缀和约束的方案数。可视化中需重点展示前缀和的转移过程（如`f[i][j]`如何由`f[i-1][j-k]`转移而来）。
   - **像素动画设计**：采用8位像素风格，用方块表示数组元素，颜色变化（如红色→绿色）表示操作后的稳定状态；动态规划表格用逐格点亮的方式展示`f[i][j]`的填充过程，关键步骤伴随“叮”的音效（如完成一次转移）。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选了以下3份优质题解（均≥4星），它们各有亮点，值得深入学习：
</eval_intro>

**题解一：作者Acfboy (赞：8)**
* **点评**：此题解以“操作本质”为突破口，快速推导出稳定状态的约束条件（如`d_i`的递推关系），思路简洁直接。代码结构紧凑，变量名（如`f[i][j]`）符合动态规划惯例，边界处理（如`max(l, 0)`）严谨。亮点在于将复杂的收敛问题转化为前缀和背包，大幅降低了问题难度。

**题解二：作者monstersqwq (赞：6)**
* **点评**：此题解详细推导了操作的4条性质（如和不变性、前缀和非严格递减），逻辑严谨，适合理解问题本质。对“稳定状态条件”的证明（必要条件与充分条件）尤为透彻，帮助学习者建立“从现象到本质”的分析思维。代码虽未完整展示，但核心思路（前缀和约束+背包）清晰，实践价值高。

**题解三：作者Cry_For_theMoon (赞：1)**
* **点评**：此题解结合数学方程（解`x+y=a`和`x−y=b`）分析操作本质，推导稳定状态的前缀和公式，理论深度强。代码结构清晰（如`sum[i]`表示稳定前缀和下界），变量命名（`f[i][j]`）直观，边界条件（`Max(0, sum[i+1]-j)`）处理细致，是动态规划实现的典范。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题时，我们需要突破以下核心难点，并掌握对应的分析策略：
</difficulty_intro>

1.  **关键点1：理解操作的本质，推导稳定状态的条件**
    * **分析**：操作的核心是让相邻元素的差至少为`b_i`（否则会被调整）。稳定状态下，`d_{i+1} ≥ d_i + b_i`，因此`d_1`的下界决定了后续所有`d_i`的下界（如`d_2 ≥ x + b_1`，`d_3 ≥ x + b_1 + b_2`等）。
    * 💡 **学习笔记**：遇到“无限操作后稳定”的问题，可通过分析单次操作的影响，推导稳定状态的必要条件（如差的约束）。

2.  **关键点2：将问题转化为前缀和的约束**
    * **分析**：原数组`a`的前缀和必须≥稳定数组`d`的前缀和（因操作不增加前缀和），而`d`的前缀和又由`x`和`b`数组决定（如前`i`项和≥`i*x + sum_{j=1}^{i−1}(i−j)*b_j`）。结合`a_i ≤ c_i`的约束，前缀和的上界为`c`的前缀和。
    * 💡 **学习笔记**：复杂的元素约束（如`d_i`的递推）可转化为前缀和的线性约束，简化问题。

3.  **关键点3：设计动态规划的状态转移方程**
    * **分析**：状态`f[i][j]`表示前`i`项前缀和为`j`的方案数。转移时，第`i+1`项的取值`k`需满足`j + k`在合法范围内（下界为`sum[i+1]`，上界为`c`的前缀和），因此`f[i+1][j+k] += f[i][j]`。
    * 💡 **学习笔记**：动态规划的核心是定义状态（如前缀和）和转移条件（如取值范围），需确保覆盖所有合法情况。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题抽象**：将“收敛”操作的影响抽象为数学条件（如差的约束），简化问题模型。
- **前缀和转化**：将元素级别的约束转化为前缀和的线性约束，降低复杂度。
- **动态规划设计**：用`f[i][j]`记录前`i`项前缀和为`j`的方案数，通过遍历取值范围完成转移。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合三份优质题解的思路，提炼出一个清晰、完整的通用核心实现，帮助大家把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了三份题解的思路，采用动态规划（背包）计算满足前缀和条件的方案数，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;

    const int MOD = 1e9 + 7;
    const int MAXN = 105;
    const int MAX_SUM = 1e4 + 10; // 根据c的范围调整

    int n, c[MAXN], b[MAXN];
    int q, x;
    long long f[MAXN][MAX_SUM]; // f[i][j]表示前i项前缀和为j的方案数
    long long sum_c[MAXN];      // c的前缀和（上界）
    long long sum_d[MAXN];      // d的前缀和下界

    int main() {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> c[i];
        for (int i = 1; i <= n - 1; ++i) cin >> b[i];
        cin >> q >> x;

        // 计算c的前缀和（上界）
        for (int i = 1; i <= n; ++i) sum_c[i] = sum_c[i - 1] + c[i];

        // 计算d的前缀和下界：sum_d[i] = i*x + sum_{j=1}^{i-1} (i-j)*b[j]
        for (int i = 1; i <= n; ++i) {
            sum_d[i] = 1LL * i * x;
            for (int j = 1; j <= i - 1; ++j) sum_d[i] += 1LL * (i - j) * b[j];
        }

        // 初始化动态规划
        f[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= sum_c[i]; ++j) {
                if (f[i][j] == 0) continue;
                // 第i+1项的取值k需满足：j + k >= sum_d[i+1]（下界）且k <= c[i+1]（上界）
                int L = max(0LL, sum_d[i + 1] - j);
                int R = c[i + 1];
                for (int k = L; k <= R; ++k) {
                    f[i + 1][j + k] = (f[i + 1][j + k] + f[i][j]) % MOD;
                }
            }
        }

        // 统计所有满足sum_d[n] <= j <= sum_c[n]的方案数
        long long ans = 0;
        int lower = max(0LL, sum_d[n]);
        int upper = sum_c[n];
        for (int j = lower; j <= upper; ++j) {
            ans = (ans + f[n][j]) % MOD;
        }

        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先计算`c`的前缀和（上界）和稳定状态`d`的前缀和下界（`sum_d`）。然后用动态规划数组`f[i][j]`记录前`i`项前缀和为`j`的方案数。通过遍历每个元素的可能取值（`k`），累加满足前缀和约束的方案数。最后统计所有符合条件的前缀和对应的方案数之和。

---
<code_intro_selected>
接下来，我们剖析各优质题解的核心代码片段，学习其亮点和实现思路。
</code_intro_selected>

**题解一：作者Acfboy**
* **亮点**：代码简洁高效，直接通过前缀和转移实现动态规划。
* **核心代码片段**：
    ```cpp
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        l += b[i] + f1, r += c[i];
        for (int j = std::max(l, 0); j <= r; j++)
            for (int k = 0; k <= c[i]; k++)
                f[i][j] = (f[i][j] + f[i-1][j-k]) % P;
    }
    ```
* **代码解读**：
    > 这段代码初始化`f[0][0]=1`（前0项和为0的方案数为1）。对于第`i`项，计算其前缀和的下界`l`（由`b`和`x`推导）和上界`r`（由`c`的前缀和推导）。内层循环遍历所有可能的前缀和`j`，并枚举第`i`项的取值`k`，将`f[i-1][j-k]`累加到`f[i][j]`中。这一步实现了动态规划的状态转移。
* 💡 **学习笔记**：动态规划的转移需明确当前项的取值范围（下界和上界），避免无效计算。

**题解三：作者Cry_For_theMoon**
* **亮点**：代码结构清晰，变量命名直观（如`sum2`表示`c`的前缀和，`sum`表示`d`的前缀和下界）。
* **核心代码片段**：
    ```cpp
    rep(i,0,n-1){
        rep(j,0,sum2[i]){
            ll L=Max(0,sum[i+1]-j),R=c[i+1];
            rep(k,L,R){
                f[i+1][j+k]=(f[i+1][j+k]+f[i][j])%moder;
            }
        }
    }
    ```
* **代码解读**：
    > 这段代码遍历前`i`项的所有可能前缀和`j`，计算第`i+1`项的取值范围`L`（下界）和`R`（上界）。对于每个合法的`k`（第`i+1`项的取值），将`f[i][j]`累加到`f[i+1][j+k]`中。`L`的计算确保`j + k`至少为`sum[i+1]`（稳定前缀和下界），`R`为`c[i+1]`（当前项的最大值）。
* 💡 **学习笔记**：动态规划的转移需严格满足前缀和的上下界约束，避免遗漏或重复。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解动态规划的转移过程和稳定状态的推导，我们设计了一个“像素背包探险”动画，带大家“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素背包探险——寻找满足条件的数组a`

  * **核心演示内容**：动态规划数组`f[i][j]`的填充过程，以及稳定状态`d`的前缀和下界如何约束`a`的前缀和。

  * **设计思路简述**：采用8位像素风（FC红白机风格），用方块表示数组元素，颜色区分稳定状态（绿色）和原始状态（蓝色）。动态规划表格用网格展示，逐格点亮表示`f[i][j]`的方案数累加。关键操作（如转移）伴随“叮”的音效，完成所有转移后播放“胜利”音效，增强学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为左右两部分：左侧是数组`a`的像素方块（蓝色）和稳定数组`d`的像素方块（绿色）；右侧是动态规划表格（`f[i][j]`的网格，初始为灰色）。
          * 控制面板包含“单步”、“自动播放”按钮和速度滑块。

    2.  **稳定状态推导**：
          * 演示`d_1 ≥x`，`d_2 ≥d_1 +b_1`等条件，用绿色箭头连接相邻方块，显示`d_i`的下界（如`d_2`的下界为`x + b_1`）。

    3.  **动态规划转移**：
          * 单步执行时，高亮当前处理的`i`和`j`（如`i=1, j=0`），显示第`i+1`项的取值范围`L`到`R`（用黄色边框标记）。
          * 对于每个合法的`k`，从`f[i][j]`的网格（点亮为橙色）向`f[i+1][j+k]`的网格（点亮为红色）发射像素粒子，伴随“叮”的音效。
          * 自动播放时，粒子流动速度可通过滑块调整，整体过程如“像素瀑布”般填充表格。

    4.  **结果统计**：
          * 所有转移完成后，统计`f[n][j]`中满足`sum_d[n] ≤j ≤sum_c[n]`的格子（点亮为金色），播放上扬的“胜利”音效，并显示总方案数（如“56”）。

  * **旁白提示**：
      * “看！`d_2`的下界是`x + b_1`，所以`a`的前两项和至少要达到这个值～”
      * “现在处理第`i`项，`k`的取值范围是`L`到`R`，每个`k`都会把`f[i][j]`的方案数传递给`f[i+1][j+k]`哦！”
      * “最后，所有满足条件的`j`对应的方案数加起来，就是答案啦～”

<visualization_conclusion>
通过这个像素动画，我们不仅能直观看到动态规划的转移过程，还能理解稳定状态的约束如何影响`a`的取值。这种“边看边学”的方式，让复杂的算法变得生动有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的动态规划（背包）和前缀和分析后，我们可以尝试以下拓展练习，巩固相关技巧：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的“前缀和约束+动态规划”模型，还可用于解决：
        1. 统计满足区间和条件的数组数量（如“和为定值的子数组数”）。
        2. 带上下界的整数拆分问题（如“将数拆分为若干数，每数不超过某个值”）。
        3. 资源分配问题（如“将资源分配给多个任务，每个任务有最小/最大需求”）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1049** - `装箱问题`
          * 🗣️ **推荐理由**：经典01背包问题，帮助巩固动态规划基础。
    2.  **洛谷 P1164** - `小A点菜`
          * 🗣️ **推荐理由**：统计满足金额约束的点菜方案数，与本题的“统计满足前缀和约束的数组数”思路类似。
    3.  **洛谷 P1832** - `A+B Problem（再升级）`
          * 🗣️ **推荐理由**：需要分析质数条件，结合动态规划统计方案数，锻炼问题转化能力。

-----

## 7\. 学习心得与经验分享 

<insights_intro>
题解作者的经验能帮助我们少走弯路，以下是值得借鉴的心得：
</insights_intro>

> **参考经验 (来自Acfboy)**：“别被‘收敛’吓到，先研究操作对数组的影响，再推导稳定条件。”
>
> **点评**：Acfboy的经验提醒我们，遇到陌生概念（如“收敛”）时，应先分析具体操作的影响，再推导数学条件。这是解决复杂问题的关键步骤！遇到难题时，“拆解问题→分析操作→推导条件”是屡试不爽的策略哦～

-----

<conclusion>
本次关于“Converging Array (Easy Version)”的分析就到这里。希望大家通过本指南，掌握动态规划（背包）的应用和问题转化技巧。记住，编程的魅力在于“拆解复杂，创造简单”——多动手分析，多尝试代码，你会越来越强！下次再见～💪
</conclusion>

-----

---
处理用时：148.85秒