# 题目信息

# Discarding Game

## 题目描述

Eulampius has created a game with the following rules:

- there are two players in the game: a human and a computer;
- the game lasts for no more than $ n $ rounds. Initially both players have $ 0 $ points. In the $ j $ -th round the human gains $ a_j $ points, and the computer gains $ b_j $ points. The points are gained simultaneously;
- the game ends when one of the players gets $ k $ or more points. This player loses the game. If both players get $ k $ or more points simultaneously, both lose;
- if both players have less than $ k $ points after $ n $ rounds, the game ends in a tie;
- after each round the human can push the "Reset" button. If the human had $ x $ points, and the computer had $ y $ points before the button is pushed (of course, $ x < k $ and $ y < k $ ), then after the button is pushed the human will have $ x' = max(0, \, x - y) $ points, and the computer will have $ y' = max(0, \, y - x) $ points. E. g. the push of "Reset" button transforms the state $ (x=3, \, y=5) $ into the state $ (x'=0, \, y'=2) $ , and the state $ (x=8, \, y=2) $ into the state $ (x'=6, \, y'=0) $ .

Eulampius asked his friend Polycarpus to test the game. Polycarpus has quickly revealed that amounts of points gained by the human and the computer in each of $ n $ rounds are generated before the game and stored in a file. In other words, the pushes of the "Reset" button do not influence the values $ a_j $ and $ b_j $ , so sequences $ a $ and $ b $ are fixed and known in advance.

Polycarpus wants to make a plan for the game. He would like to win the game pushing the "Reset" button as few times as possible. Your task is to determine this minimal number of pushes or determine that Polycarpus cannot win.

## 说明/提示

In the second test case, if the human pushes the "Reset" button after the second and the fourth rounds, the game goes as follows:

1. after the first round the human has $ 5 $ points, the computer — $ 4 $ points;
2. after the second round the human has $ 7 $ points, the computer — $ 10 $ points;
3. the human pushes the "Reset" button and now he has $ 0 $ points and the computer — $ 3 $ points;
4. after the third round the human has $ 8 $ points, the computer — $ 6 $ points;
5. after the fourth round the human has $ 10 $ points, the computer — $ 9 $ points;
6. the human pushes "Reset" button again, after it he has $ 1 $ point, the computer — $ 0 $ points;
7. after the fifth round the human has $ 5 $ points, the computer — $ 5 $ points;
8. after the sixth round the human has $ 11 $ points, the computer — $ 6 $ points;
9. after the seventh round the human has $ 12 $ points, the computer — $ 13 $ points;
10. after the eighth round the human has $ 14 $ points, the computer — $ 17 $ points;
11. the human wins, as the computer has $ k $ or more points and the human — strictly less than $ k $ points.

## 样例 #1

### 输入

```
3
4 17
1 3 5 7
3 5 7 9
11 17
5 2 8 2 4 6 1 2 7 2 5
4 6 3 3 5 1 7 4 2 5 3
6 17
6 1 2 7 2 5
1 7 4 2 5 3
```

### 输出

```
0

2
2 4
-1```

# AI分析结果

---
# 💡 Kay的C++算法解析：Discarding Game 深入学习指南 💡

<introduction>
今天我们来一起分析“Discarding Game”这道C++编程题。本指南将帮助大家梳理题目规则，理解核心贪心策略，并掌握如何通过最少的Reset操作让人类玩家获胜。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心策略与模拟操作 (属于“贪心”算法分类)

🗣️ **初步分析**：
> 解决“Discarding Game”的关键在于理解Reset操作的核心性质——**操作前后双方的分差不变**。例如，若操作前人类得分为x，电脑得分为y，操作后变为(x', y') = (max(0, x-y), max(0, y-x))，此时x' - y' = (x - y) 或 -(y - x)，但绝对值分差保持不变。这一性质是贪心策略的基石。
   - **题解思路**：优质题解普遍利用分差不变性，通过前缀和预处理每轮后的总得分，结合双指针或贪心扫描确定最少Reset次数。核心难点在于如何在保证人类不提前输掉的前提下，找到让电脑率先达到k分的最优Reset位置。
   - **核心算法流程**：预处理每轮的前缀和，枚举最后一次Reset的位置，双指针判断人类能否坚持到该位置且电脑输掉。可视化中需重点展示每轮得分变化、Reset操作后的分数调整，以及关键位置的高亮（如最后一次Reset的轮次）。
   - **复古像素设计**：动画采用8位像素风格，用不同颜色方块表示人类（蓝色）和电脑（红色）的得分，每轮得分通过“+a[j]”“+b[j]”的像素文字弹出。Reset操作时，分数方块闪烁并缩小（如3→0，5→2），伴随“叮”的音效；找到最优解时播放胜利音效，路径用金色箭头标记。

---

## 2. 精选优质题解参考

<eval_intro>
通过对题解的思路清晰度、代码规范性、算法有效性等维度评估，以下题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：Refined_heart的贪心扫描法**
* **点评**：此题解深入利用分差不变性，通过前缀和数组（sa、sb）快速计算每轮总得分，结合指针扫描找到关键位置（pre）。代码虽含较多辅助函数，但核心逻辑清晰（如work函数中的指针移动和Reset构造），边界处理严谨（如pre的初始化和循环条件）。亮点在于通过“差值不变”将问题简化为单指针扫描，时间复杂度O(n)，适合竞赛场景。

**题解二：robinyqc的双指针贪心法**
* **点评**：此题解思路简洁，通过预处理每轮Reset后的剩余得分（h、c数组），结合双指针（i和p）快速判断人类能否坚持到目标位置。代码变量命名直观（h表示人类得分，c表示电脑得分），逻辑推导清晰（如从后往前枚举最后一次Reset的位置）。亮点在于双指针优化，避免了O(n²)的暴力枚举，时间复杂度O(n)，适合作为入门参考。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决Discarding Game的过程中，我们通常会遇到以下核心难点，结合优质题解的共性，提炼解决策略：
</difficulty_intro>

1.  **关键点1：理解Reset操作的分差不变性**
    * **分析**：Reset操作后，人类和电脑的分差绝对值不变（如x=3,y=5→x'=0,y'=2，分差仍为-2）。这意味着，若某轮后电脑总得分≥k且人类<k，无论之前如何Reset，只要分差允许，该轮就是胜利点。优质题解通过前缀和计算总得分，直接利用这一性质缩小搜索范围。
    * 💡 **学习笔记**：分差不变性是解题的“钥匙”，它将复杂的动态Reset问题简化为静态的得分差分析。

2.  **关键点2：确定最少Reset次数的贪心策略**
    * **分析**：最少Reset次数的关键是“尽可能晚Reset”，避免不必要的操作。例如，若当前人类得分+下轮得分≥k，则必须Reset；否则继续累积得分。优质题解通过双指针或指针扫描，从后往前枚举最后一次Reset的位置，确保人类在到达该位置前不提前输掉。
    * 💡 **学习笔记**：贪心策略的核心是“延迟操作”，优先累积得分，仅在必要时Reset。

3.  **关键点3：构造具体的Reset位置**
    * **分析**：找到胜利轮次后，需模拟得分过程，记录所有必要的Reset位置。例如，若人类在第i轮前得分+下轮得分≥k，则必须在第i轮后Reset。优质题解通过遍历前缀和，动态调整当前得分（hn、cn），确保每一步操作后人类得分<k。
    * 💡 **学习笔记**：构造Reset位置时，需严格模拟每轮得分，避免遗漏关键操作。

### ✨ 解题技巧总结
<summary_best_practices>
- **前缀和预处理**：用sa[i]、sb[i]存储前i轮的总得分，快速计算任意轮次的累积得分。
- **双指针优化**：从后往前枚举最后一次Reset的位置，用指针p动态调整人类能坚持的最右轮次，避免暴力枚举。
- **模拟得分过程**：通过变量hn（当前人类得分）、cn（当前电脑得分）实时更新，确保每一步操作后人类得分<k。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合robinyqc题解的核心实现，代码逻辑清晰、效率高，适合作为通用参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了robinyqc题解的双指针贪心思路，通过预处理和双指针快速确定最少Reset次数，逻辑简洁高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    using namespace std;
    using i64 = long long;

    vector<int> ans;

    void solve() {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        for (int& i : a) cin >> i;
        for (int& i : b) cin >> i;

        vector<i64> h(n + 1), c(n + 1); // 预处理每轮Reset后的剩余得分
        for (int i = 1; i <= n; ++i) {
            h[i] = h[i - 1] + a[i - 1];
            c[i] = c[i - 1] + b[i - 1];
            i64 v = min(h[i], c[i]);
            h[i] -= v;
            c[i] -= v;
        }

        int p = n, mn = n;
        i64 hn = 0, cn = 0;

        // 双指针找最左胜利位置
        for (int i = n - 1; i >= 0; --i) {
            hn += a[i];
            cn += b[i];
            while (h[i] + hn >= k) { // 人类得分超过k，需左移p
                --p;
                hn -= a[p];
                cn -= b[p];
            }
            if (c[i] + cn >= k) mn = i; // 电脑得分≥k，记录位置
        }

        if (mn == n) { // 无解
            cout << "-1\n";
            return;
        } else if (mn == 0) { // 0次Reset
            cout << "0\n\n";
            return;
        }

        // 构造Reset位置
        hn = 0, cn = 0;
        ans.clear();
        for (int i = 0; i < mn; ++i) {
            if (hn + a[i] >= k) { // 必须Reset
                i64 v = min(hn, cn);
                hn -= v;
                cn -= v;
                ans.push_back(i);
                if (hn + a[i] >= k) { // Reset后仍超k，无解
                    cout << "-1\n";
                    return;
                }
            }
            hn += a[i];
            cn += b[i];
        }
        ans.push_back(mn); // 最后一次Reset

        // 输出结果
        cout << ans.size() << '\n';
        for (int i : ans) cout << i << ' ';
        cout << '\n';
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t;
        cin >> t;
        while (t--) solve();
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先预处理每轮Reset后的剩余得分（h、c数组），然后通过双指针从后往前枚举最后一次Reset的位置（mn），确保电脑得分≥k且人类<k。接着模拟得分过程，记录所有必要的Reset位置，最后输出结果。核心逻辑在双指针找mn和构造Reset位置两部分，时间复杂度O(n)。

---
<code_intro_selected>
接下来分析robinyqc题解的核心代码片段，理解其贪心策略的实现：
</code_intro_selected>

**题解二：robinyqc的双指针贪心法**
* **亮点**：双指针优化枚举，时间复杂度O(n)；预处理Reset后的得分，简化后续判断。
* **核心代码片段**：
    ```cpp
    // 双指针找最左胜利位置
    for (int i = n - 1; i >= 0; --i) {
        hn += a[i];
        cn += b[i];
        while (h[i] + hn >= k) { 
            --p;
            hn -= a[p];
            cn -= b[p];
        }
        if (c[i] + cn >= k) mn = i; 
    }
    ```
* **代码解读**：
    > 这段代码从后往前枚举最后一次Reset的位置i（即第i轮后Reset）。hn和cn是i轮后到当前轮的累积得分。若人类得分（h[i] + hn）≥k，说明i轮后Reset无法让人类存活，需左移p（减少后续轮次）。当电脑得分（c[i] + cn）≥k时，记录当前i为可能的胜利位置mn。这一步通过双指针快速缩小范围，确保找到最左的胜利位置。
* 💡 **学习笔记**：双指针从后往前扫描，利用得分的单调性（累积得分随轮次增加而增大），快速定位目标位置，避免了暴力枚举的低效。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization_intro\>
为了直观理解贪心策略和Reset操作的过程，我们设计一个“像素得分大战”动画，用8位复古风格展示每轮得分、Reset操作和胜利条件达成。
\</visualization_intro\>

  * **动画演示主题**：像素得分大战（8位复古风）
  * **核心演示内容**：展示每轮人类（蓝方块）和电脑（红方块）的得分变化，Reset操作时的分数调整，以及通过双指针找到的最后一次Reset位置。
  * **设计思路简述**：8位像素风营造轻松氛围，得分变化用方块大小/颜色体现（如得分增加时方块膨胀），Reset操作时方块闪烁并缩小（如5→2），关键位置用金色箭头标记。音效在Reset时播放“叮”，胜利时播放“胜利音效”，增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为左右两部分，左边显示“人类得分”（蓝底白字），右边显示“电脑得分”（红底白字）。下方是轮次进度条（1-8轮，每轮用小方块表示）。
          * 控制面板：单步/自动播放按钮、速度滑块（0.5x-2x）、重置按钮。

    2.  **每轮得分演示**：
          * 第j轮开始时，蓝方块弹出“+a[j]”文字，红方块弹出“+b[j]”文字，方块大小随得分增加（如初始0→5，蓝方块从1x1变为2x2）。
          * 得分更新后，检查是否达到k分（k=17时，得分≥17的方块变红闪烁，提示“输掉”）。

    3.  **Reset操作演示**：
          * 当需要Reset时，蓝、红方块同时闪烁（黄色边框），伴随“叮”音效。
          * 分数调整：如当前蓝=7，红=10，Reset后蓝=0，红=3（蓝方块缩小为1x1，红方块缩小为1x2）。

    4.  **双指针找胜利位置**：
          * 用绿色箭头从右向左扫描轮次（i从n-1到0），红色箭头标记p的位置（当前能坚持的最右轮次）。
          * 当电脑得分≥k时，绿色箭头停在该轮，弹出“胜利位置！”文字，播放胜利音效（上扬音调）。

    5.  **游戏结束**：
          * 若找到胜利位置，蓝方块保持<k，红方块≥k，屏幕中央弹出“人类胜利！”（金色文字），背景播放8位胜利音乐。
          * 若无解，弹出“游戏失败”（灰色文字），播放短促提示音效。

  * **旁白提示**：
      * （单步时）“现在是第3轮，人类得分7，电脑得分10，需要Reset！”
      * （双指针扫描时）“绿色箭头在找最后一次Reset的位置，红色箭头调整能坚持的轮次。”
      * （胜利时）“找到啦！最后一次Reset在第4轮，电脑得分17，人类得分14，胜利！”

\<visualization_conclusion\>
通过这个动画，我们能直观看到每轮得分的变化、Reset操作的调整效果，以及双指针如何快速定位胜利位置，让抽象的贪心策略变得“可见可触”。
\</visualization_conclusion\>

---

## 6\. 拓展练习与相似问题思考

\<similar_problems_intro\>
Discarding Game的贪心策略和模拟操作思路，可迁移到多种需要“延迟决策”或“最小操作次数”的问题中。
\</similar_problems_intro\>

  * **通用思路/技巧迁移**：
      * 分差不变性：适用于需要平衡双方状态的问题（如交替操作、资源分配）。
      * 双指针扫描：适用于需要快速定位边界的问题（如最长子数组、最小区间覆盖）。
      * 贪心延迟操作：适用于需要最小化操作次数的问题（如区间调度、任务安排）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1223 排队接水**
          * 🗣️ **推荐理由**：贪心策略的典型应用，通过排序最小化总等待时间，与本题“延迟操作”思路类似。
    2.  **洛谷 P1090 合并果子**
          * 🗣️ **推荐理由**：贪心选择最小代价合并，需用优先队列优化，锻炼数据结构与贪心结合的能力。
    3.  **洛谷 P1803 凌乱的yyy**
          * 🗣️ **推荐理由**：贪心区间覆盖问题，通过排序选择最早结束的区间，与本题双指针扫描思路相通。

---

## 7\. 学习心得与经验分享 (若有)

\<insights_intro\>
本次分析的题解中，robinyqc提到：“在模拟得分过程时，需要严格检查每次Reset后人类是否仍<k，否则会提前输掉。” 这一经验对避免逻辑错误非常关键。
\</insights_intro\>

> **参考经验 (来自 robinyqc)**：“在构造Reset位置时，必须确保每次Reset后，人类下一轮的得分仍<k。否则即使找到胜利位置，也可能因中间步骤输掉而无解。”
>
> **点评**：这一经验提醒我们，贪心策略不仅要关注最终目标，还要确保中间步骤的合法性。在模拟过程中，每一步都要验证约束条件（如人类得分<k），避免“顾头不顾尾”的错误。

---

\<conclusion\>
本次关于“Discarding Game”的C++解题分析就到这里。希望这份指南能帮助大家理解贪心策略的核心，掌握如何利用分差不变性简化问题，并通过可视化动画直观感受算法流程。记住，多动手模拟、多思考边界条件，是提升编程能力的关键！下次见～💪
\</conclusion\>

---
处理用时：365.95秒