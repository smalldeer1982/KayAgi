# 题目信息

# Singers' Tour

## 题目描述

$ n $ towns are arranged in a circle sequentially. The towns are numbered from $ 1 $ to $ n $ in clockwise order. In the $ i $ -th town, there lives a singer with a repertoire of $ a_i $ minutes for each $ i \in [1, n] $ .

Each singer visited all $ n $ towns in clockwise order, starting with the town he lives in, and gave exactly one concert in each town. In addition, in each town, the $ i $ -th singer got inspired and came up with a song that lasts $ a_i $ minutes. The song was added to his repertoire so that he could perform it in the rest of the cities.

Hence, for the $ i $ -th singer, the concert in the $ i $ -th town will last $ a_i $ minutes, in the $ (i + 1) $ -th town the concert will last $ 2 \cdot a_i $ minutes, ..., in the $ ((i + k) \bmod n + 1) $ -th town the duration of the concert will be $ (k + 2) \cdot a_i $ , ..., in the town $ ((i + n - 2) \bmod n + 1) $ — $ n \cdot a_i $ minutes.

You are given an array of $ b $ integer numbers, where $ b_i $ is the total duration of concerts in the $ i $ -th town. Reconstruct any correct sequence of positive integers $ a $ or say that it is impossible.

## 说明/提示

Let's consider the $ 1 $ -st test case of the example:

1. the $ 1 $ -st singer in the $ 1 $ -st city will give a concert for $ 3 $ minutes, in the $ 2 $ -nd — for $ 6 $ minutes, in the $ 3 $ -rd — for $ 9 $ minutes;
2. the $ 2 $ -nd singer in the $ 1 $ -st city will give a concert for $ 3 $ minutes, in the $ 2 $ -nd — for $ 1 $ minute, in the $ 3 $ -rd - for $ 2 $ minutes;
3. the $ 3 $ -rd singer in the $ 1 $ -st city will give a concert for $ 6 $ minutes, in the $ 2 $ -nd — for $ 9 $ minutes, in the $ 3 $ -rd — for $ 3 $ minutes.

## 样例 #1

### 输入

```
4
3
12 16 14
1
1
3
1 2 3
6
81 75 75 93 93 87```

### 输出

```
YES
3 1 3 
YES
1 
NO
YES
5 5 4 1 4 5```

# AI分析结果



---
# 💡 Kay的C++算法解析：Singers' Tour 深入学习指南 💡

<introduction>
今天我们来一起分析“Singers' Tour”这道题。这道题需要根据每个城镇的总演唱会时长，还原出每个歌手的初始曲目时长。通过数学推导和线性方程组的求解，我们可以找到关键规律。本指南将带大家理清思路，掌握核心解法！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学推导与线性方程组求解（数学分类）

🗣️ **初步分析**：
解决这道题的关键在于通过数学推导，将题目中的条件转化为线性方程组，并找到简化的求解方法。简单来说，就像解一个“环形方程组”——每个城镇的总时长由多个歌手的贡献叠加而成，而这些贡献遵循等差数列的规律。我们需要通过求和和差分操作，将复杂的方程组简化为直接计算每个变量的公式。

- **题解思路**：所有题解的核心思路一致：先将所有b_i相加，得到总和与a_i总和的关系；再通过相邻b_i的差分，推导出每个a_i的表达式。若所有a_i均为正整数，则存在解，否则不存在。
- **核心难点**：如何从复杂的环形方程组中推导出a_i的表达式？如何处理环形差分（如b_n与b_1的差）？如何验证解的合法性（正整数）？
- **可视化设计**：我们将用像素风格的“环形城镇”场景，动态展示每个歌手的贡献如何累加为b_i，以及通过求和、差分步骤计算a_i的过程。例如，用不同颜色的像素块表示不同歌手的贡献，用闪烁动画强调求和与差分的关键步骤，配合“叮”的音效提示关键操作。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等方面筛选出以下优质题解：
</eval_intro>

**题解一：作者 Bbaka (赞：9)**
* **点评**：这份题解的思路非常清晰，详细推导了线性方程组的求和与差分过程，并给出了完整的代码实现。代码中变量命名规范（如`sum`表示b数组总和），边界处理严谨（如判断`sum`是否能被整除）。其亮点在于通过数学推导直接得到a_i的表达式，避免了复杂的高斯消元，时间复杂度仅为O(n)，非常高效。代码对每个a_i的正整数验证也很细致，是一份适合竞赛的参考代码。

**题解二：作者 Running_a_way (赞：1)**
* **点评**：此题解用“萌萌推式子题”的轻松语气，点明了差分操作的关键作用。虽然推导过程较简略，但准确抓住了“b_i的差分与a_i总和的关系”这一核心，对理解问题本质有启发。代码虽未完整展示，但思路与主流解法一致，适合快速理解问题。

**题解三：作者 Tzs_yousa (赞：1)**
* **点评**：此题解通过手画样例推导公式，强调了“累加法”和“差分法”的应用，符合初学者的思维过程。代码中对`Sn`（a数组总和）的计算和`a[i]`的验证逻辑清晰，特别是对环形差分（如b[1]与b[n]的差）的处理值得学习。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们需要突破以下核心难点：
</difficulty_intro>

1.  **关键点1：如何从复杂的环形方程组中推导出a_i的表达式？**
    * **分析**：题目中的每个b_i由n个歌手的贡献叠加，每个歌手的贡献是一个等差数列（如第i个歌手在第j个城镇的贡献为`(j-i+1) * a_i`）。将所有b_i相加后，每个a_i会被累加`1+2+...+n = n(n+1)/2`次，因此总和关系为`sum(b) = sum(a) * n(n+1)/2`，从而得到`sum(a) = 2*sum(b)/(n(n+1))`。
    * 💡 **学习笔记**：总和的规律是解决环形问题的“突破口”，通过整体求和可以快速建立变量间的关系。

2.  **关键点2：如何处理环形差分（如b_n与b_1的差）？**
    * **分析**：相邻b_i的差（如b_i - b_{i-1}）可以展开为`sum(a) - n*a_i`（因为每个歌手的贡献在相邻城镇的差为a_i，除了第i个歌手的差为`(k+1)a_i - k*a_i = a_i`，但由于环形结构，总差会抵消其他项，最终得到此式）。因此，`a_i = (sum(a) - (b_i - b_{i-1})) / n`。对于i=1，需要用b_n与b_1的差。
    * 💡 **学习笔记**：环形问题的差分需要特别处理首尾项，确保所有a_i都能被正确计算。

3.  **关键点3：如何验证解的合法性（正整数）？**
    * **分析**：计算得到的a_i必须是正整数。因此，需要检查：①`sum(b)`是否能被`n(n+1)/2`整除（否则sum(a)不是整数）；②每个`(sum(a) - (b_i - b_{i-1}))`是否能被n整除且结果大于0。
    * 💡 **学习笔记**：每一步计算都要验证是否符合题目要求的条件（正整数），避免输出错误解。

### ✨ 解题技巧总结
- **整体求和**：遇到环形或对称结构的问题时，先尝试整体求和，简化变量关系。
- **差分操作**：相邻项的差能消去大部分变量，突出关键变量（如本题中的a_i）。
- **边界处理**：环形结构的首尾项需要单独处理（如b_n与b_1的差），避免遗漏。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，给出一个通用的核心C++实现，代码简洁高效，适合竞赛使用。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Bbaka等优质题解的思路，通过求和与差分快速计算a_i，并验证其合法性。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;

    int main() {
        int t;
        cin >> t;
        while (t--) {
            ll n;
            cin >> n;
            vector<ll> b(n + 1); // b[1..n]
            ll sum_b = 0;
            for (int i = 1; i <= n; ++i) {
                cin >> b[i];
                sum_b += b[i];
            }
            // 计算sum_a = 2*sum_b / (n*(n+1))
            if (n == 1) { // 特判n=1的情况
                cout << "YES\n" << b[1] << "\n";
                continue;
            }
            if (sum_b * 2 % (n * (n + 1)) != 0) {
                cout << "NO\n";
                continue;
            }
            ll sum_a = sum_b * 2 / (n * (n + 1));
            vector<ll> a(n + 1);
            bool valid = true;
            for (int i = 2; i <= n; ++i) {
                ll diff = b[i] - b[i - 1];
                if ((sum_a - diff) % n != 0 || (sum_a - diff) <= 0) {
                    valid = false;
                    break;
                }
                a[i] = (sum_a - diff) / n;
            }
            // 处理i=1的情况（环形差分：b[1]与b[n]的差）
            ll diff = b[1] - b[n];
            if ((sum_a - diff) % n != 0 || (sum_a - diff) <= 0) {
                valid = false;
            }
            a[1] = (sum_a - diff) / n;
            if (!valid) {
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
            for (int i = 1; i <= n; ++i) {
                cout << a[i] << " ";
            }
            cout << "\n";
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入并计算b数组的总和`sum_b`。通过`sum_b * 2 % (n*(n+1))`判断是否存在整数解`sum_a`（a数组的总和）。若不存在，直接输出NO。若存在，通过环形差分计算每个a_i（i=2到n用b[i]-b[i-1]，i=1用b[1]-b[n]），并验证每个a_i是否为正整数。最后输出结果。

---
<code_intro_selected>
接下来，我们分析优质题解中的核心代码片段，学习其亮点。
</code_intro_selected>

**题解一：作者 Bbaka**
* **亮点**：代码结构清晰，边界处理严谨（如特判n=1），变量命名直观（sum表示sum_b），对每个a_i的验证细致。
* **核心代码片段**：
    ```cpp
    if (sum%(((1 + n) * n / 2))!=0) {
        cout<<"NO"<<endl;
        continue;
    }
    sum/=((1+n)*n/2);
    // 计算a[i]并验证
    ```
* **代码解读**：
    > 这段代码首先检查`sum_b`是否能被`n(n+1)/2`整除，这是判断是否存在解的第一步。若不能整除，直接输出NO。若能，则计算`sum_a`（a数组的总和）。这一步是推导的关键，确保后续计算的a_i为整数。
* 💡 **学习笔记**：总和的整除性判断是解存在的必要条件，必须优先检查。

**题解二：作者 Tzs_yousa**
* **亮点**：通过`Sn`（sum_a）和差分直接计算a_i，代码简洁，逻辑清晰。
* **核心代码片段**：
    ```cpp
    a[i] = (Sn - (b[i] - b[i - 1])) / n;
    if(a[i] <= 0) fl = 0;
    ```
* **代码解读**：
    > 这段代码利用推导出的公式`a_i = (sum_a - (b[i]-b[i-1])) / n`计算每个a_i，并检查是否为正整数。若为非正数，标记`fl`为0，最终输出NO。这一步确保了每个a_i符合题目要求。
* 💡 **学习笔记**：每个a_i的正整数验证是关键，遗漏会导致错误解。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解求和与差分的过程，我们设计一个“像素城镇环”动画，用8位复古风格展示算法步骤！
</visualization_intro>

  * **动画演示主题**：`像素歌手的环游记`
  * **核心演示内容**：展示n个城镇围成环，每个歌手的演唱会时长如何累加为b_i，以及通过求和、差分计算a_i的过程。
  * **设计思路简述**：采用8位像素风格（如FC游戏画面），用不同颜色的像素块表示不同歌手的贡献（如红色块代表歌手1，蓝色块代表歌手2）。通过动态叠加块展示b_i的形成，用闪烁箭头强调求和与差分步骤，配合音效增强记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕中央显示一个环形排列的n个像素城镇（每个城镇用方块表示，标有编号1~n）。
          * 控制面板包含“开始/暂停”“单步”“重置”按钮和速度滑块。
          * 播放8位风格的轻快背景音乐（如《超级玛丽》的经典旋律）。

    2.  **输入与求和演示**：
          * 输入b数组的数值，每个城镇的方块上方显示对应的b_i（如城镇1显示“b1=12”）。
          * 所有b_i的数值从方块中“飞出”，汇聚到屏幕中央的“求和球”中，球上显示总和`sum_b`（如“sum_b=42”）。
          * 音效：每次数值飞入时播放“叮”的音效，求和完成时播放“叮咚”音效。

    3.  **计算sum_a演示**：
          * “求和球”分裂为`n(n+1)/2`个小球（如n=3时分裂为6个），每个小球代表一个a_i的贡献。
          * 小球重新组合成一个新球，显示`sum_a = 2*sum_b/(n(n+1))`（如“sum_a=7”）。
          * 音效：小球重组时播放“唰”的音效。

    4.  **差分与a_i计算演示**：
          * 城镇环上出现箭头，依次指向相邻城镇（如1→2→3→1），显示差分`b_i - b_{i-1}`（如b2-b1=4）。
          * 每个差分数值与`sum_a`结合，通过公式计算a_i（如a2=(7-4)/3=1），结果以像素数字形式从城镇方块中弹出。
          * 音效：每次计算完成时播放“滴答”音效，若结果合法（正整数），城镇方块闪烁绿色；若非法（非正或非整数），闪烁红色并播放“嗡嗡”提示音。

    5.  **结果展示**：
          * 所有a_i计算完成后，城镇方块上方显示对应的a_i（如城镇2显示“a2=1”）。
          * 若所有a_i合法，播放“胜利”音效（如《魂斗罗》的胜利旋律），城镇环旋转并撒下像素星星；若非法，显示“NO”并播放“失败”音效。

<visualization_conclusion>
通过这个动画，我们可以直观看到求和与差分如何一步步推导出a_i，理解数学公式背后的实际意义！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的关键是通过求和与差分推导变量关系，这种思路在类似的环形或对称问题中也很常见。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 环形数组的求和与差分：适用于“每个元素由其他元素循环贡献”的问题（如环形均分纸牌、环形加油站问题）。
      * 线性方程组的简化：通过整体求和或差分消元，将高维问题降维（如二维前缀和、矩阵快速幂中的递推关系）。
      * 正整数解的验证：在构造类问题中（如求合法序列），需严格检查每一步的计算结果是否符合条件。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1031 均分纸牌**
          * 🗣️ **推荐理由**：这道题涉及环形均分纸牌的变形，需要通过求和与差分找到每个位置的调整量，与本题的思路类似。
    2.  **洛谷 P1223 排队接水**
          * 🗣️ **推荐理由**：虽然是贪心题，但需要通过数学推导找到最优排列，锻炼数学建模能力。
    3.  **洛谷 P1115 最大子段和**
          * 🗣️ **推荐理由**：通过前缀和与差分快速计算最大子段和，强化对求和与差分的理解。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了推导过程中的心得，这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自作者 Tachibana27)**：“手玩样例不难发现规律，通过瞪眼法解方程比高斯消元更高效。”
>
> **点评**：手玩样例是理解问题的重要方法！通过具体例子推导规律，能快速抓住问题本质，避免陷入复杂的形式化推导。这提醒我们，遇到新问题时，先尝试用小数据量的样例手动计算，往往能发现关键规律。

-----

<conclusion>
本次关于“Singers' Tour”的分析就到这里。通过数学推导、代码实现和可视化演示，我们掌握了环形问题的解决思路。记住，遇到复杂问题时，先尝试整体求和或差分简化，再逐步推导每个变量！期待下次一起挑战新的算法问题！💪
</conclusion>

---
处理用时：145.75秒