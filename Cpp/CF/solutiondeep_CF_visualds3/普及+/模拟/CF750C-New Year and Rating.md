# 题目信息

# New Year and Rating

## 题目描述

Every Codeforces user has rating, described with one integer, possibly negative or zero. Users are divided into two divisions. The first division is for users with rating $ 1900 $ or higher. Those with rating $ 1899 $ or lower belong to the second division. In every contest, according to one's performance, his or her rating changes by some value, possibly negative or zero.

Limak competed in $ n $ contests in the year 2016. He remembers that in the $ i $ -th contest he competed in the division $ d_{i} $ (i.e. he belonged to this division just before the start of this contest) and his rating changed by $ c_{i} $ just after the contest. Note that negative $ c_{i} $ denotes the loss of rating.

What is the maximum possible rating Limak can have right now, after all $ n $ contests? If his rating may be arbitrarily big, print "Infinity". If there is no scenario matching the given information, print "Impossible".

## 说明/提示

In the first sample, the following scenario matches all information Limak remembers and has maximum possible final rating:

- Limak has rating $ 1901 $ and belongs to the division $ 1 $ in the first contest. His rating decreases by $ 7 $ .
- With rating $ 1894 $ Limak is in the division $ 2 $ . His rating increases by $ 5 $ .
- Limak has rating $ 1899 $ and is still in the division $ 2 $ . In the last contest of the year he gets $ +8 $ and ends the year with rating $ 1907 $ .

In the second sample, it's impossible that Limak is in the division $ 1 $ , his rating increases by $ 57 $ and after that Limak is in the division $ 2 $ in the second contest.

## 样例 #1

### 输入

```
3
-7 1
5 2
8 2
```

### 输出

```
1907
```

## 样例 #2

### 输入

```
2
57 1
22 2
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
1
-5 1
```

### 输出

```
Infinity
```

## 样例 #4

### 输入

```
4
27 2
13 1
-50 1
8 2
```

### 输出

```
1897
```

# AI分析结果



---
# 💡 Kay的C++算法解析：New Year and Rating 深入学习指南 💡

<introduction>
今天我们来一起分析“New Year and Rating”这道C++编程题。这道题需要我们根据Limak参加的n场比赛信息，计算他最终可能的最大rating。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟与区间维护` (属于“编程技巧应用”分类)

🗣️ **初步分析**：
> 解决这道题的关键在于模拟Limak初始rating的可能区间，并根据每场比赛的division（d_i）动态调整这个区间。简单来说，“模拟与区间维护”就像我们在玩一个“边界游戏”——每一步比赛的条件（d_i=1或d_i=2）会给初始rating的可能范围划出“新的边界”，我们需要不断缩小这个范围，最终根据范围的状态判断结果。
   - **题解思路对比**：题解中主要有两种思路：一种是直接模拟初始rating的可能区间（minn和maxn），逐步根据每场比赛调整区间；另一种是二分初始rating，检查是否满足所有比赛条件。其中模拟法更直接，代码更简洁，是主流解法。
   - **核心算法流程**：初始时，初始rating的可能区间是(-∞, +∞)。对于每场比赛i：
     - 若d_i=1（比赛前属于Div1），则初始rating必须≥1900 - 前i-1场的总变化（否则比赛前rating会低于1900），因此更新区间下界为max(当前下界, 1900 - 前i-1场总变化)；
     - 若d_i=2（比赛前属于Div2），则初始rating必须≤1899 - 前i-1场总变化，因此更新区间上界为min(当前上界, 1899 - 前i-1场总变化)；
     - 若区间下界>上界，说明无解（Impossible）；若最终上界仍为+∞，说明初始rating无上限（Infinity）；否则最终rating为上界+所有比赛总变化。
   - **可视化设计思路**：用像素动画展示初始rating的区间变化。例如，用绿色方块表示下界，红色方块表示上界，初始时分别位于屏幕左右两端。每处理一场比赛，方块会向中间移动（区间缩小），若两方块重叠则显示“Impossible”；若红色方块一直未动则显示“Infinity”；最终红色方块位置+总变化即为答案。动画中会用“叮”声提示区间调整，用闪烁标记关键比赛的d_i条件。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解（≥4星）：
</eval_intro>

**题解一：作者frankchenfu (赞：2)**
* **点评**：这份题解思路非常清晰，通过维护初始rating的上下界（lans和rans），逐步根据每场比赛的d_i调整区间，代码简洁且变量命名直观（如lans表示下界，rans表示上界）。算法上，通过前缀和思想计算总变化，避免了重复计算，时间复杂度O(n)，效率很高。从实践角度看，边界条件处理严谨（如初始下界设为-INF，上界设为INF），代码可直接用于竞赛，是模拟法的典型代表。

**题解二：作者Loi_Anina (赞：6)**
* **点评**：此题解用模拟法维护minn和maxn区间，注释详细，易于理解。虽然变量初始化（如maxn=3e8）稍显随意，但逻辑正确。代码中通过判断每场比赛的d_i是否符合当前区间，直接处理Impossible的情况，是新手友好的实现方式。其调试经验（“考试写WA了”）也提醒我们注意区间更新的顺序。

**题解三：作者caibet (赞：2)**
* **点评**：此题解用前缀和优化，将每场比赛的总变化预先计算，简化了区间调整的表达式（如用c[i]表示前i场的总变化）。通过不等式组的形式推导初始rating的范围，数学建模能力突出，适合想深入理解问题本质的学习者。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何准确定义初始rating的区间？**
    * **分析**：初始rating的可能范围需要根据每场比赛的d_i动态调整。例如，若第i场比赛是Div1（d_i=1），则比赛前Limak的rating必须≥1900。由于比赛前的rating等于初始rating+前i-1场的总变化，因此初始rating≥1900 - 前i-1场总变化。这需要我们维护一个下界，每次取最大值。同理，Div2比赛需要维护上界，每次取最小值。
    * 💡 **学习笔记**：区间的上下界是“所有约束条件的交集”，下界取所有约束的最大值，上界取所有约束的最小值。

2.  **关键点2：如何处理Impossible和Infinity的情况？**
    * **分析**：若最终区间的下界>上界（lans>rans），说明没有初始rating能满足所有比赛条件，输出Impossible；若上界仍为初始的+∞（rans未被更新过），说明初始rating可以无限大，最终rating也无限大，输出Infinity。
    * 💡 **学习笔记**：Impossible是区间不存在，Infinity是区间无上限，这两种情况需要在最后单独判断。

3.  **关键点3：如何正确计算最终rating？**
    * **分析**：最终rating=初始rating+所有比赛的总变化。由于我们要找最大的最终rating，初始rating应取区间的最大值（即rans），因此最终rating=rans+总变化。
    * 💡 **学习笔记**：最大最终rating对应最大的初始rating，即区间的上界。

### ✨ 解题技巧总结
<summary_best_practices>
通过对本题的分析，我总结了以下通用解题技巧：
</summary_best_practices>
-   **问题抽象**：将问题转化为初始变量的区间约束问题，用数学不等式描述每场比赛的条件。
-   **动态维护区间**：每一步根据新的约束调整区间的上下界，确保区间始终表示可能的初始值范围。
-   **边界条件处理**：初始区间设为(-∞, +∞)，处理完所有比赛后再判断是否存在有效区间或是否无上限。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个优质题解的思路，采用模拟法维护初始rating的区间，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;

    const int INF = 0x7fffffff;

    int main() {
        int n;
        cin >> n;
        int sum = 0; // 前i-1场的总变化（初始为0，处理第i场时sum是前i-1场的和）
        int lans = -INF; // 初始rating的下界
        int rans = INF;  // 初始rating的上界

        for (int i = 1; i <= n; ++i) {
            int c, d;
            cin >> c >> d;

            // 根据当前比赛的d_i调整区间
            if (d == 1) {
                // 比赛前属于Div1，初始rating + sum >= 1900 → 初始rating >= 1900 - sum
                lans = max(lans, 1900 - sum);
            } else {
                // 比赛前属于Div2，初始rating + sum <= 1899 → 初始rating <= 1899 - sum
                rans = min(rans, 1899 - sum);
            }

            sum += c; // 更新总变化（下一场的sum是前i场的和）
        }

        if (lans > rans) {
            cout << "Impossible" << endl;
        } else if (rans == INF) {
            cout << "Infinity" << endl;
        } else {
            cout << rans + sum << endl; // 最终rating = 初始rating上界 + 所有比赛总变化
        }

        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取比赛场数n，初始化总变化sum和初始rating的区间（lans=-INF，rans=INF）。然后遍历每场比赛，根据d_i调整区间：Div1比赛提高下界，Div2比赛降低上界。遍历结束后，判断区间是否有效（lans<=rans）、是否无上限（rans=INF），并计算最终rating。

---
<code_intro_selected>
接下来，我们将剖析优质题解中的核心代码片段，并点出各自的亮点和关键思路。
</code_intro_selected>

**题解一：作者frankchenfu**
* **亮点**：代码简洁，变量命名直观（lans表示下界，rans表示上界），通过sum维护前i-1场的总变化，逻辑清晰。
* **核心代码片段**：
    ```cpp
    int lans=-INF,rans=INF;
    int sum=0;
    for(int i=1;i<=n;i++){
        if(state[i][1]==1)
            lans=max(lans,1900-sum);
        else
            rans=min(rans,1899-sum);
        sum+=state[i][0];
    }
    ```
* **代码解读**：
    > 这段代码遍历每场比赛，根据d_i调整区间。`sum`是前i-1场的总变化（因为处理第i场时，sum还未加上c[i]）。对于Div1比赛（d=1），初始rating必须≥1900 - sum（因为初始rating+sum≥1900），所以更新下界为max(lans, 1900-sum)；Div2比赛（d=2）同理，初始rating≤1899-sum，更新上界为min(rans, 1899-sum)。`sum`在每次循环后加上当前场的c[i]，为下一场的计算做准备。
* 💡 **学习笔记**：sum的维护是关键，它表示“初始rating到比赛前的总变化”，确保了每次区间调整的正确性。

**题解二：作者Loi_Anina**
* **亮点**：通过minn和maxn直接维护当前可能的rating区间，注释详细，适合新手理解。
* **核心代码片段**：
    ```cpp
    int minn=0,maxn=300000000;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&c,&d);
        if(d==1&&maxn<1900||d==2&&minn>1899){
            printf("Impossible");
            return 0;
        }
        if(d==1&&minn<1900) minn=1900;
        if(d==2&&maxn>1899) maxn=1899;
        if(minn!=0) minn+=c;
        if(maxn!=300000000) maxn+=c;
    }
    ```
* **代码解读**：
    > 这段代码用minn和maxn表示当前可能的rating范围（初始为0和3e8，近似-∞和+∞）。对于每场比赛，若d=1但当前maxn<1900（无法参加Div1），或d=2但minn>1899（无法参加Div2），则输出Impossible。否则，调整minn或maxn为Div1/Div2的边界（1900或1899），并加上当前场的c[i]（更新当前可能的rating范围）。
* 💡 **学习笔记**：直接维护当前可能的rating范围（而非初始rating的区间），是另一种直观的模拟思路。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“区间维护”的过程，我设计了一个“像素边界探险”动画，用8位像素风格展示初始rating区间的变化过程。
</visualization_intro>

  * **动画演示主题**：`像素边界探险——寻找最大初始Rating`

  * **核心演示内容**：初始时，屏幕左右两侧有两个像素方块（绿色代表下界，红色代表上界），中间是初始rating的可能区间。每处理一场比赛，根据d_i调整方块的位置（绿色右移或红色左移），最终根据方块的位置判断结果（Impossible、Infinity或最大最终rating）。

  * **设计思路简述**：8位像素风格营造轻松氛围，方块移动直观展示区间收缩。关键操作（如调整边界）伴随“叮”声，增强记忆；最终结果用闪烁或音效提示，增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕背景为8位像素风格，顶部显示“初始Rating区间”，左右两侧分别有绿色（下界）和红色（上界）方块，初始位置在屏幕最左（-∞）和最右（+∞）。
          * 控制面板包含“开始/暂停”“单步”“重置”按钮和速度滑块。

    2.  **处理第一场比赛**：
          * 显示比赛信息（c和d），例如d=1时，绿色方块右移到1900的位置（初始rating≥1900），伴随“叮”声。
          * 总变化sum更新，方块位置加上c（表示当前可能的rating范围）。

    3.  **处理后续比赛**：
          * 每处理一场比赛，根据d_i调整方块位置：d=1则绿色方块右移（下界提高），d=2则红色方块左移（上界降低）。
          * 方块移动时用像素动画（如逐格滑动），并显示当前约束条件（如“Div1要求初始Rating≥1900-前i-1场总变化”）。

    4.  **结果判断**：
          * 若绿色方块超过红色方块（lans>rans），屏幕显示“Impossible”并播放短促音效。
          * 若红色方块未移动（仍在最右端），显示“Infinity”并播放上升音效。
          * 否则，计算最终rating（红色方块位置+总变化），用金色像素星星围绕方块闪烁，播放胜利音效。

  * **旁白提示**：
      * （处理d=1时）“这场比赛是Div1，初始Rating必须至少为1900-前几场的总变化，所以下界要右移啦！”
      * （方块重叠时）“哎呀，下界超过上界了，说明没有初始Rating能满足所有比赛条件，输出Impossible！”
      * （红色方块未动时）“上界一直没动，说明初始Rating可以无限大，最终Rating也是Infinity～”

<visualization_conclusion>
通过这个动画，我们可以直观看到初始Rating的区间如何一步步被比赛条件“压缩”，最终得出结果。像素风格和音效让学习过程更有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考区间维护和约束处理的应用场景。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的“区间维护”思想还可用于处理类似“动态约束下的最大/最小值”问题，例如：
        - 股票买卖中的最大利润（每日价格约束）；
        - 游戏角色属性的动态调整（每关后的属性限制）；
        - 资源分配中的边界控制（每步操作后的资源上下限）。

  * **练习推荐 (洛谷)**：
    以下是几道与本题思维方式相关的题目，建议尝试：

    1.  **洛谷 P1058 立体图**
          * 🗣️ **推荐理由**：考察空间想象与模拟能力，需要动态维护图形的边界，与本题的区间维护思想有共通之处。
    2.  **洛谷 P1098 字符串的展开**
          * 🗣️ **推荐理由**：需要根据不同的展开规则调整字符的范围，锻炼约束条件下的逻辑处理能力。
    3.  **洛谷 P1100 高低位交换**
          * 🗣️ **推荐理由**：涉及位运算的边界处理，适合巩固“动态调整边界”的思维。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些对我们很有参考价值：
</insights_intro>

> **参考经验 (来自作者Loi_Anina)**：“我考试写WA了，后来发现是区间更新的顺序错了。比如，应该先调整区间再加上当前场的c[i]，而不是先加c[i]再调整。”
>
> **点评**：这位作者的经验提醒我们，区间调整的顺序非常重要。在本题中，每场比赛的约束是“比赛前”的rating条件，因此必须先用前i-1场的总变化调整区间，再加上当前场的c[i]（更新到前i场的总变化）。这是容易出错的细节，需要特别注意。

-----

<conclusion>
本次关于“New Year and Rating”的C++解题分析就到这里。希望这份学习指南能帮助大家理解区间维护的核心思想，掌握模拟法的关键技巧。记住，编程的关键在于理清逻辑、注意细节，多动手调试才能避免类似错误。下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：170.21秒