# 题目信息

# Candy Store

## 题目描述

The store sells $ n $ types of candies with numbers from $ 1 $ to $ n $ . One candy of type $ i $ costs $ b_i $ coins. In total, there are $ a_i $ candies of type $ i $ in the store.

You need to pack all available candies in packs, each pack should contain only one type of candies. Formally, for each type of candy $ i $ you need to choose the integer $ d_i $ , denoting the number of type $ i $ candies in one pack, so that $ a_i $ is divided without remainder by $ d_i $ .

Then the cost of one pack of candies of type $ i $ will be equal to $ b_i \cdot d_i $ . Let's denote this cost by $ c_i $ , that is, $ c_i = b_i \cdot d_i $ .

After packaging, packs will be placed on the shelf. Consider the cost of the packs placed on the shelf, in order $ c_1, c_2, \ldots, c_n $ . Price tags will be used to describe costs of the packs. One price tag can describe the cost of all packs from $ l $ to $ r $ inclusive if $ c_l = c_{l+1} = \ldots = c_r $ . Each of the packs from $ 1 $ to $ n $ must be described by at least one price tag. For example, if $ c_1, \ldots, c_n = [4, 4, 2, 4, 4] $ , to describe all the packs, a $ 3 $ price tags will be enough, the first price tag describes the packs $ 1, 2 $ , the second: $ 3 $ , the third: $ 4, 5 $ .

You are given the integers $ a_1, b_1, a_2, b_2, \ldots, a_n, b_n $ . Your task is to choose integers $ d_i $ so that $ a_i $ is divisible by $ d_i $ for all $ i $ , and the required number of price tags to describe the values of $ c_1, c_2, \ldots, c_n $ is the minimum possible.

For a better understanding of the statement, look at the illustration of the first test case of the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1798C/1160d0ae9da0a28139cfb8794bbbd0911d44c66f.png)Let's repeat the meaning of the notation used in the problem:

 $ a_i $ — the number of candies of type $ i $ available in the store.

 $ b_i $ — the cost of one candy of type $ i $ .

 $ d_i $ — the number of candies of type $ i $ in one pack.

 $ c_i $ — the cost of one pack of candies of type $ i $ is expressed by the formula $ c_i = b_i \cdot d_i $ .

## 说明/提示

In the first test case, you can choose $ d_1 = 4 $ , $ d_2 = 6 $ , $ d_3 = 7 $ , $ d_4 = 5 $ . Then the cost of packs will be equal to $ [12, 12, 35, 35] $ . $ 2 $ price tags are enough to describe them, the first price tag for $ c_1, c_2 $ and the second price tag for $ c_3, c_4 $ . It can be shown that with any correct choice of $ d_i $ , at least $ 2 $ of the price tag will be needed to describe all the packs. Also note that this example is illustrated by a picture in the statement.

In the second test case, with $ d_1 = 4 $ , $ d_2 = 2 $ , $ d_3 = 10 $ , the costs of all packs will be equal to $ 20 $ . Thus, $ 1 $ price tag is enough to describe all the packs. Note that $ a_i $ is divisible by $ d_i $ for all $ i $ , which is necessary condition.

In the third test case, it is not difficult to understand that one price tag can be used to describe $ 2 $ nd, $ 3 $ rd and $ 4 $ th packs. And additionally a price tag for pack $ 1 $ and pack $ 5 $ . Total: $ 3 $ price tags.

## 样例 #1

### 输入

```
5
4
20 3
6 2
14 5
20 7
3
444 5
2002 10
2020 2
5
7 7
6 5
15 2
10 3
7 7
5
10 1
11 5
5 1
2 2
8 2
6
7 12
12 3
5 3
9 12
9 3
1000000000 10000```

### 输出

```
2
1
3
2
5```

# AI分析结果



---
# 💡 Kay的C++算法解析：Candy Store 深入学习指南 💡

<introduction>
今天我们来一起分析“Candy Store”这道C++编程题。这道题需要我们通过合理选择每包糖果的数量，使得价格标签的数量最少。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`贪心算法 + 数论应用（gcd与lcm）`

🗣️ **初步分析**：
解决“Candy Store”这道题，关键在于理解并运用贪心策略，结合数论中的最大公约数（gcd）和最小公倍数（lcm）。简单来说，贪心算法就像“尽可能多装”——每次从当前位置开始，尽可能延长一个能共用同一价格标签的区间。而数论中的gcd和lcm则是判断区间能否共用标签的核心工具。

在本题中，我们需要为每段区间找到一个公共价格标签 \( c \)，使得：
1. \( c \) 是该区间所有 \( b_i \) 的公倍数（即 \( \text{lcm}(b_l, b_{l+1}, \dots, b_r) \mid c \)）；
2. \( c \) 是该区间所有 \( a_i \times b_i \) 的公约数（即 \( c \mid \gcd(a_l \times b_l, a_{l+1} \times b_{l+1}, \dots, a_r \times b_r) \)）。

当且仅当 \( \text{lcm}(b_l, \dots, b_r) \mid \gcd(a_l \times b_l, \dots, a_r \times b_r) \) 时，这段区间可以共用一个标签。贪心策略的核心是：从左到右遍历，每次尽可能延长当前区间，直到无法满足条件，再开启新的区间。

可视化设计思路：用8位像素风格的网格展示每类糖果，用不同颜色的像素块表示当前区间的 \( \text{lcm}(b) \) 和 \( \gcd(a \times b) \)。当 \( \text{lcm} \) 能整除 \( \gcd \) 时，区间扩展（像素块向右滑动），否则当前区间结束（播放“叮”的音效），并开启新的区间（新颜色的像素块）。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解在关键步骤推导和实现上表现突出（评分≥4星）：
</eval_intro>

**题解一：作者：一扶苏一**
* **点评**：此题解逻辑清晰，详细推导了区间合法的条件（\( \text{lcm}(b) \mid \gcd(a \times b) \)），并通过贪心策略实现。代码规范，使用标准库的 `std::gcd` 和 `std::lcm`（需注意NOI赛事环境可能需调整），变量命名简洁（如 `x` 存当前lcm，`y` 存当前gcd）。实践价值高，边界处理（如 `i` 的更新）严谨，适合竞赛参考。

**题解二：作者：Larryyu**
* **点评**：此题解代码简洁，变量命名直观（`ansg` 存gcd，`ansl` 存lcm），逻辑直接。通过遍历数组动态维护当前区间的gcd和lcm，当条件不满足时重置并增加标签数。对贪心策略的实现非常高效，适合快速理解核心逻辑。

**题解三：作者：inc1ude_c**
* **点评**：此题解准确抓住了问题的数学本质（\( \text{lcm}(b) \mid \gcd(a \times b) \) 是区间合法的充要条件），并简洁说明贪心策略的正确性。代码虽未完整展示，但关键思路清晰，对理解条件推导有很大帮助。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个核心难点。结合优质题解的共性，我为大家提炼了关键思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何确定区间合法的条件？**
    * **分析**：一个区间 \( [l, r] \) 能共用一个标签，需存在一个公共价格 \( c \)，满足 \( c = b_i \times d_i \)（\( d_i \mid a_i \)）。由此推导出 \( c \) 必须是 \( \text{lcm}(b_l, \dots, b_r) \) 的倍数（因 \( b_i \mid c \)），同时 \( c \) 必须是 \( \gcd(a_l \times b_l, \dots, a_r \times b_r) \) 的因数（因 \( d_i \mid a_i \) 等价于 \( c \mid a_i \times b_i \)）。因此，合法条件为 \( \text{lcm}(b) \mid \gcd(a \times b) \)。
    * 💡 **学习笔记**：区间合法的核心是数论条件 \( \text{lcm}(b) \mid \gcd(a \times b) \)，这是解题的关键公式。

2.  **关键点2：如何设计贪心策略？**
    * **分析**：贪心策略的核心是“尽可能延长当前区间”。从左到右遍历，维护当前区间的 \( \text{lcm}(b) \) 和 \( \gcd(a \times b) \)，每次尝试将下一个元素加入区间。若加入后仍满足 \( \text{lcm} \mid \gcd \)，则继续；否则结束当前区间，开启新的区间。这样能保证标签数最少，因为提前结束区间不会更优（后续区间的限制更严格）。
    * 💡 **学习笔记**：贪心的正确性在于“当前最优选择不会影响全局最优”，尽可能延长区间是减少标签数的直接方法。

3.  **关键点3：如何高效计算gcd和lcm？**
    * **分析**：在遍历过程中，需要动态维护当前区间的 \( \text{lcm}(b) \) 和 \( \gcd(a \times b) \)。\( \text{lcm}(x, y) = x \times y / \gcd(x, y) \)，因此可以通过迭代计算（如 \( \text{lcm}(x, y) \) 是当前lcm与新 \( b_i \) 的lcm）。\( \gcd \) 则通过迭代取当前gcd与新 \( a_i \times b_i \) 的gcd。
    * 💡 **学习笔记**：动态维护gcd和lcm的时间复杂度为 \( O(n) \)，是高效的关键。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题转化**：将“最小标签数”问题转化为“寻找最长合法区间”问题，利用贪心策略简化求解。
- **数论工具**：熟练运用gcd和lcm的性质（如 \( \text{lcm}(a, b) = a \times b / \gcd(a, b) \)），快速判断区间合法性。
- **动态维护**：在遍历过程中动态更新当前区间的gcd和lcm，避免重复计算，提升效率。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个优质题解的思路，采用贪心策略动态维护当前区间的gcd和lcm，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm> // 包含gcd和lcm（C++17及以上）
    using namespace std;
    using ll = long long;

    ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
    ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) {
            int n;
            cin >> n;
            vector<ll> a(n), b(n);
            for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
            int ans = 1;
            ll current_gcd = a[0] * b[0];
            ll current_lcm = b[0];
            for (int i = 1; i < n; ++i) {
                current_gcd = gcd(current_gcd, a[i] * b[i]);
                current_lcm = lcm(current_lcm, b[i]);
                if (current_gcd % current_lcm != 0) {
                    ans++;
                    current_gcd = a[i] * b[i];
                    current_lcm = b[i];
                }
            }
            cout << ans << '\n';
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入数据，然后初始化当前区间的gcd（`current_gcd`）为第一个元素的 \( a_0 \times b_0 \)，lcm（`current_lcm`）为第一个元素的 \( b_0 \)。遍历后续元素时，动态更新当前区间的gcd和lcm。若更新后gcd无法被lcm整除，则结束当前区间，开启新的区间（`ans++`，并重置gcd和lcm为当前元素的值）。最终输出最少标签数。

---
<code_intro_selected>
接下来，我们将剖析优质题解中的核心代码片段，并点出各自的亮点和关键思路。
</code_intro_selected>

**题解一：作者：一扶苏一**
* **亮点**：使用标准库的 `std::lcm` 和 `std::gcd`（需注意C++17支持），代码简洁，逻辑清晰。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; ++i) {
        ++ans;
        long long x = b[i], y = 1ll * a[i] * b[i];
        for (int j = i + 1; j <= n; ++j) {
            x = std::lcm(1ll * b[j], x);
            y = std::gcd(y, 1ll * a[j] * b[j]);
            if (y % x != 0) {
                i = j - 1; break;
            }
            if (j == n) {
                i = j; break;
            }
        }
    }
    ```
* **代码解读**：
    > 外层循环遍历每个可能的区间起点 `i`，内层循环尝试扩展区间到 `j`。`x` 维护当前区间的lcm（`b`的lcm），`y` 维护当前区间的gcd（`a*b`的gcd）。若 `y % x != 0`（不满足条件），则结束当前区间（`i = j-1`），否则继续扩展。当 `j` 到达末尾时，结束循环。
* 💡 **学习笔记**：嵌套循环的写法直观展示了贪心扩展区间的过程，适合理解贪心策略的细节。

**题解二：作者：Larryyu**
* **亮点**：代码简洁，变量命名直观（`ansg` 存gcd，`ansl` 存lcm），逻辑直接。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n;i++){
        ansg=gcd(ansg,a[i]*b[i]);
        ansl=lcm(ansl,b[i]);
        if((ansg%ansl)!=0){
            ansg=a[i]*b[i];
            ansl=b[i];
            cnt++;
        }
    }
    ```
* **代码解读**：
    > 遍历每个元素，动态更新当前区间的gcd（`ansg`）和lcm（`ansl`）。若当前gcd无法被lcm整除（`ansg % ansl != 0`），则重置gcd和lcm为当前元素的 `a[i] * b[i]` 和 `b[i]`，并增加标签数（`cnt++`）。这种写法避免了嵌套循环，时间复杂度为 \( O(n) \)，更高效。
* 💡 **学习笔记**：单循环写法通过动态维护变量，将时间复杂度优化到线性，是竞赛中常用的高效实现。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解贪心策略和数论条件的判断过程，我设计了一个8位像素风格的动画演示方案。让我们通过“像素糖果店”的故事，一起“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素糖果店的标签挑战`

  * **核心演示内容**：展示如何从左到右扩展区间，动态计算当前区间的 \( \text{lcm}(b) \) 和 \( \gcd(a \times b) \)，并判断是否满足 \( \text{lcm} \mid \gcd \)。当条件满足时，区间扩展；否则结束当前区间，开启新的区间。

  * **设计思路简述**：采用8位像素风格（类似FC红白机），用不同颜色的像素块表示不同糖果类型。通过动态更新的数值框展示当前 \( \text{lcm} \) 和 \( \gcd \)，并用颜色变化（绿色表示满足条件，红色表示不满足）提示关键步骤。音效（如“叮”）在区间扩展时播放，增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为三部分：左侧为糖果展示区（每类糖果用不同颜色的像素块表示，标注 \( a_i \) 和 \( b_i \)），中间为动态数值区（显示当前 \( \text{lcm} \) 和 \( \gcd \)），右侧为控制面板（单步/自动播放按钮、速度滑块）。
          * 播放8位风格的轻快背景音乐（如《超级玛丽》的经典旋律变奏）。

    2.  **算法启动**：
          * 初始时，选中第一个糖果（像素块闪烁），数值区显示 \( \text{lcm} = b_1 \)，\( \gcd = a_1 \times b_1 \)。

    3.  **区间扩展**：
          * 单步执行时，尝试将下一个糖果加入当前区间：
            - 计算新的 \( \text{lcm} \)（当前lcm与新 \( b_i \) 的lcm），数值区用黄色高亮更新。
            - 计算新的 \( \gcd \)（当前gcd与新 \( a_i \times b_i \) 的gcd），数值区用蓝色高亮更新。
            - 检查 \( \gcd \% \text{lcm} \)：若为0（绿色背景），区间扩展（像素块向右滑动，播放“叮”音效）；否则（红色背景），结束当前区间（播放“滴”音效），并将下一个糖果设为新区间起点（像素块变色）。

    4.  **目标达成**：
          * 当遍历完所有糖果时，数值区显示最终标签数（如“最少需要2个标签！”），播放胜利音效（如《超级玛丽》吃金币音效），并展示庆祝动画（像素烟花）。

    5.  **交互控制**：
          * 单步按钮：每次点击执行一步扩展，适合仔细观察每一步的数值变化。
          * 自动播放按钮：以用户设定的速度（通过滑块调整）自动执行，适合整体观察算法流程。
          * 重置按钮：回到初始状态，重新开始演示。

  * **旁白提示**：
      * （单步执行前）“现在，我们尝试将第2类糖果加入当前区间。当前lcm是 \( b_1 \)，gcd是 \( a_1 \times b_1 \)。”
      * （计算后）“新的lcm是 \( \text{lcm}(b_1, b_2) \)，新的gcd是 \( \gcd(a_1 \times b_1, a_2 \times b_2) \)。检查gcd是否能被lcm整除？”
      * （满足条件时）“满足条件！当前区间扩展到第2类糖果，继续尝试加入下一类。”
      * （不满足条件时）“不满足条件！当前区间结束，开启新的区间。”

<visualization_conclusion>
通过这样一个融合了像素艺术和复古游戏元素的动画，我们不仅能清晰地看到贪心算法的执行流程，还能直观理解数论条件（\( \text{lcm} \mid \gcd \)）的判断过程。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考贪心策略和数论工具的适用范围。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 贪心策略：适用于需要“局部最优推导全局最优”的问题（如区间覆盖、任务调度）。
      * 数论工具（gcd与lcm）：常用于处理涉及因数、倍数的问题（如分数化简、周期问题）。
      * 动态维护变量：在遍历过程中实时更新关键参数（如最大值、最小值），适用于滑动窗口、双指针等场景。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1892 [BOI2003] 团伙**
          * 🗣️ **推荐理由**：这道题需要将朋友和敌人关系转化为并查集的合并问题，与贪心策略的“局部最优”思想类似，适合练习问题转化能力。
    2.  **洛谷 P1029 最大公约数和最小公倍数问题**
          * 🗣️ **推荐理由**：直接考察gcd和lcm的性质，通过本题可以巩固数论基础，理解 \( a \times b = \text{gcd}(a,b) \times \text{lcm}(a,b) \) 的应用。
    3.  **洛谷 P1621 集合**
          * 🗣️ **推荐理由**：需要筛选数的因数，并利用并查集合并，结合了数论与数据结构，能提升综合解题能力。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了解题过程中的思考，这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自作者：一扶苏一)**：“vp时考虑了很久大力dp，但后来发现贪心更高效。这让我意识到，遇到问题时先观察是否有贪心性质，可能比复杂的动态规划更简单。”
>
> **点评**：这位作者的经验提醒我们，贪心策略往往能简化问题。在解题时，先分析问题是否满足贪心选择性质（局部最优导致全局最优），可以避免走弯路。例如本题中，“尽可能延长区间”的贪心策略明显优于复杂的动态规划。

---

<conclusion>
本次关于“Candy Store”的C++解题分析就到这里。希望这份学习指南能帮助大家理解贪心策略与数论工具的结合应用，掌握动态维护gcd和lcm的技巧。记住，编程能力的提升在于多思考、多练习，下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：348.67秒