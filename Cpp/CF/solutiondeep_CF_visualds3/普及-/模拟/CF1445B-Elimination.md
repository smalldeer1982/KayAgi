# 题目信息

# Elimination

## 题目描述

There is a famous olympiad, which has more than a hundred participants. The Olympiad consists of two stages: the elimination stage, and the final stage. At least a hundred participants will advance to the final stage. The elimination stage in turn consists of two contests.

A result of the elimination stage is the total score in two contests, but, unfortunately, the jury lost the final standings and has only standings for the first and for the second contest separately.

In each contest, the participants are ranked by their point score in non-increasing order. When two participants have a tie (earned the same score), they are ranked by their passport number (in accordance with local regulations, all passport numbers are distinct).

In the first contest, the participant on the 100-th place scored $ a $ points. Also, the jury checked all participants from the 1-st to the 100-th place (inclusive) in the first contest and found out that all of them have at least $ b $ points in the second contest.

Similarly, for the second contest, the participant on the 100-th place has $ c $ points. And the jury checked that all the participants from the 1-st to the 100-th place (inclusive) have at least $ d $ points in the first contest.

After two contests, all participants are ranked by their total score in two contests in non-increasing order. When participants have the same total score, tie-breaking with passport numbers is used. The cutoff score to qualify to the final stage is the total score of the participant on the 100-th place.

Given integers $ a $ , $ b $ , $ c $ , $ d $ , please help the jury determine the smallest possible value of the cutoff score.

## 说明/提示

For the first test case, consider the following olympiad scenario: there are $ 101 $ participants in the elimination stage, each having $ 1 $ point for the first contest and $ 2 $ points for the second contest. Hence the total score of the participant on the 100-th place is $ 3 $ .

For the second test case, consider the following olympiad scenario:

- there are $ 50 $ participants with points $ 5 $ and $ 9 $ for the first and second contest respectively;
- $ 50 $ participants with points $ 4 $ and $ 8 $ for the first and second contest respectively;
- and $ 50 $ participants with points $ 2 $ and $ 9 $ for the first and second contest respectively.

 Hence the total point score of the participant on the 100-th place is $ 12 $ .

## 样例 #1

### 输入

```
2
1 2 2 1
4 8 9 2```

### 输出

```
3
12```

# AI分析结果



---
# 💡 Kay的C++算法解析：Elimination 深入学习指南 💡

<introduction>
今天我们来一起分析“Elimination”这道C++编程题。题目围绕两场比赛的得分规则，要求计算总分排名第100名的最小可能分数。本指南将帮助大家梳理题目思路，理解核心数学逻辑，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学分析与逻辑推理 (属于“数学”分类)

🗣️ **初步分析**：
解决“Elimination”这道题，关键在于通过数学逻辑分析两场比赛的得分规则，推导出总分排名的关键阈值。简单来说，数学分析类问题就像“找规律游戏”，需要从已知条件中提炼出隐藏的数学关系。在本题中，我们需要找到两场比赛前100名选手的最低可能总分，并确定总分排名第100名的最小值。

- **题解思路**：所有优质题解均指出，答案是两场比赛前100名选手的最低总分的最大值，即`max(a+b, c+d)`。核心难点在于理解为何取最大值而非最小值，以及如何通过题目条件推导出这一结论。
- **核心算法流程**：通过分析单场比赛的约束条件（如第一场前100名在第二场至少得b分），得出单场前100名的最低总分为`a+b`（第一场第100名的得分a + 第二场最低b分）；同理，第二场前100名的最低总分为`c+d`。总分排名的第100名至少为这两个值的最大值，否则会有超过100人总分更高。
- **可视化设计**：计划采用8位像素风格动画，用两个“分数小人”分别代表第一场和第二场的第100名选手，动态展示他们的单场得分（a、b、c、d）相加过程，并通过颜色对比（如红色高亮较大值）突出最终取最大值的逻辑。动画中会加入“叮”的音效提示相加操作，“胜利”音效提示确定最终结果。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解：
</eval_intro>

**题解一：作者：洛璟 (赞：4)**
* **点评**：这份题解的亮点在于对结论的详细证明过程（虽然作者笑称“吵架半小时”）。它明确指出了单场前100名的最低总分是`a+b`和`c+d`，并通过反例说明取最小值会导致“多选人”的问题，逻辑严谨。代码简洁规范，使用快速输入函数优化效率，边界处理（如多组测试用例）也很到位。实践中，这样的思路和代码可直接用于竞赛，参考价值极高。

**题解二：作者：_121017_ (赞：2)**
* **点评**：此题解用最直白的语言解释了核心逻辑——“两场比赛前100名的最差总分是`a+b`和`c+d`，取最大值”，思路清晰易懂。代码简短精炼，仅用`max`函数完成计算，非常适合初学者理解。其“水题”的调侃语气，也降低了学习的心理门槛。

**题解三：作者：vеctorwyx (赞：2)**
* **点评**：此题解对题目大意的提炼非常到位（“原题面很啰嗦，这里简述”），并明确指出“两个单场内的排名一定是第100名”，帮助学习者抓住问题本质。代码中使用快速输入函数，兼顾了效率和可读性，是竞赛代码的典型风格。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何理解单场排名与总分排名的关系？
    * **分析**：单场排名仅反映该场得分，但总分排名是两场得分之和。题目中给出的“第一场第100名得分a”意味着，在第一场中，至少有100人得分≥a（且前100名在第二场至少得b分）。因此，这100人的总分至少为`a+b`。同理，第二场前100人的总分至少为`c+d`。
    * 💡 **学习笔记**：单场排名的约束条件会转化为总分的下限。

2.  **关键点2**：为何答案是`max(a+b, c+d)`而非`min`？
    * **分析**：假设取`min(a+b, c+d)`为分数线，例如`a+b < c+d`，那么第二场前100人的总分（至少`c+d`）都大于`a+b`，这意味着总分≥`c+d`的人数至少有100人（第二场前100人），此时第100名的分数至少是`c+d`，比`min`值大。因此，正确的分数线是两者的最大值。
    * 💡 **学习笔记**：分数线由“更严格”的约束决定，即更高的下限。

3.  **关键点3**：如何验证结论的正确性？
    * **分析**：可以通过构造反例或数学证明。例如，若答案小于`a+b`，则第一场前100人的总分（≥`a+b`）都大于答案，导致至少100人总分超过答案，与“第100名的分数是答案”矛盾。因此，答案不能小于`a+b`，同理不能小于`c+d`，故取最大值。
    * 💡 **学习笔记**：反证法是验证数学结论的常用工具。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题抽象**：将复杂的题目描述转化为数学表达式（如`a+b`和`c+d`），抓住核心变量。
- **边界分析**：关注题目中“至少”“第100名”等关键词，确定变量的取值范围。
- **反例验证**：对猜想的结论，尝试构造反例（如取`min`是否可行），验证其正确性。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了多个优质题解的思路，采用简洁的输入输出和`max`函数计算，是本题的典型实现。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm> // 用于max函数
    using namespace std;

    int main() {
        int t;
        cin >> t; // 读取测试用例数
        while (t--) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << max(a + b, c + d) << endl; // 输出最大值
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取测试用例数`t`，然后对每个测试用例读取`a, b, c, d`四个整数。通过`max(a+b, c+d)`计算两场比赛前100名的最低总分的最大值，即为总分排名第100名的最小可能分数。代码结构简单，逻辑清晰，直接体现了题目核心数学关系。

---
<code_intro_selected>
接下来，我们将剖析优质题解中最能体现核心逻辑的代码片段。
</code_intro_selected>

**题解一：作者：洛璟**
* **亮点**：使用快速输入函数`read()`优化输入效率，适合处理大规模输入（虽然本题数据量小，但习惯值得学习）。
* **核心代码片段**：
    ```cpp
    inline int read() {
        int x=0,f=1;
        char c=getchar();
        while(c<'0' || c>'9') {
            if(c=='-') f=-1;
            c=getchar();
        }
        while(c>='0' && c<='9') {
            x=(x<<1)+(x<<3)+(c^'0');
            c=getchar();
        }
        return x*f;
    }
    // main函数中计算max(a+b, c+d)
    ```
* **代码解读**：
    > `read()`函数通过逐字符读取输入，避免了`cin`的慢速问题（尤其在数据量大时）。`x=(x<<1)+(x<<3)`等价于`x*10`，`c^'0'`将字符转换为数字（如`'5'-'0'=5`）。这种输入方式是竞赛中的常见优化技巧。
* 💡 **学习笔记**：竞赛中，快速输入输出函数能显著提升程序效率，尤其是处理大数据时。

**题解二：作者：_121017_**
* **亮点**：代码极简，直接体现核心逻辑，适合初学者理解。
* **核心代码片段**：
    ```cpp
    int main() {
        int t;
        cin >> t;
        while(t--) {
            int a,b,c,d;
            cin >> a >> b >> c >> d;
            cout << max(a+b,c+d) << endl;
        }
        return 0;
    }
    ```
* **代码解读**：
    > 代码没有冗余操作，直接读取输入并计算输出。`max`函数来自`<algorithm>`头文件，用于取两个数的最大值。这种“极简”风格在思路明确时非常实用，避免了复杂代码带来的错误。
* 💡 **学习笔记**：代码的简洁性和可读性同样重要，清晰的逻辑应直接体现在代码中。

**题解三：作者：vеctorwyx**
* **亮点**：使用`read()`函数优化输入，同时代码结构工整。
* **核心代码片段**：
    ```cpp
    int read() {
        int x=0,y=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
        while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
        return x*y;
    }
    // main函数中调用read()读取输入
    ```
* **代码解读**：
    > `read()`函数与洛璟的实现类似，但变量名更简洁（如`y`表示符号）。通过逐字符处理，确保输入的高效性。这种函数在竞赛中可以预先写好，重复使用。
* 💡 **学习笔记**：预定义快速输入输出函数是竞赛中的“必备工具”，能节省大量时间。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“为何取max(a+b, c+d)”，我设计了一个8位像素风格的动画演示方案，让我们“看”到分数的计算和比较过程！
</visualization_intro>

  * **动画演示主题**：《分数小人大作战》——两场比赛的分数对决！
  * **核心演示内容**：通过两个像素小人（红小人代表第一场第100名，蓝小人代表第二场第100名）的得分相加，展示`a+b`和`c+d`的计算过程，并比较两者大小，最终确定分数线。
  * **设计思路简述**：采用8位像素风（如FC游戏的方块角色），营造轻松的学习氛围。关键步骤的音效（如相加时的“叮”声）和颜色高亮（较大值用金色闪烁）能强化记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 像素屏幕分为左右两部分：左半部分显示第一场比赛（背景为红色），右半部分显示第二场比赛（背景为蓝色）。
          * 两个像素小人（红、蓝）站在各自场地上，头顶显示单场得分（a、c）。
          * 控制面板包含“开始”“单步”“重置”按钮和速度滑块。

    2.  **计算单场最低总分**：
          * 点击“开始”，红小人头顶弹出第二场的最低分b（绿色数字），与a相加（`a+b`），伴随“叮”的音效，结果显示在红小人脚下（黄色数字）。
          * 蓝小人同理，计算`c+d`，结果显示在蓝小人脚下。

    3.  **比较两个总分**：
          * 两个总分数字（`a+b`和`c+d`）从地面升起，移动到屏幕中央。
          * 较大的数字周围出现金色光环并闪烁，同时播放“胜利”音效（如《超级玛丽》的金币音效）。
          * 旁白提示：“看！较大的分数就是最终的分数线，因为它能保证至少100人达到或超过这个分数～”

    4.  **AI自动演示**：
          * 点击“AI自动演示”，动画会自动重复计算和比较过程，像“小老师”一样讲解每一步。

    5.  **结束状态**：
          * 最终，金色数字（`max(a+b, c+d)`）作为分数线显示在屏幕顶部，伴随庆祝动画（像素烟花）。

  * **旁白提示**：
      * （红小人相加时）“红小人在第一场得了a分，第二场至少得b分，所以他的总分至少是a+b！”
      * （比较时）“如果选较小的分数，另一个分数的小人会比他高，这样就有超过100人总分更高啦～所以必须选大的！”

<visualization_conclusion>
通过这样的动画，我们不仅能看到分数的计算过程，还能直观理解为何取最大值。像素风格和游戏化元素让学习变得更有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考数学分析类问题的通用思路。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的核心是“通过单场约束推导总分下限”，类似的思路可用于：
        1. 多科考试的录取分数线问题（如“语文≥90且数学≥80的学生中，总分前50名的最低分”）。
        2. 游戏角色属性的最小值计算（如“攻击≥100且防御≥50的角色中，综合战力的最低值”）。
        3. 资源分配的边界问题（如“两个仓库的库存分别至少为A和B，总库存的最低警戒线”）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1088 火星人**  
          * 🗣️ **推荐理由**：这道题考察排列组合的数学逻辑，需要分析边界条件，与本题的“约束推导”思维类似。
    2.  **洛谷 P1217 [USACO1.5]回文质数**  
          * 🗣️ **推荐理由**：此题需要结合数学性质（回文数、质数）筛选结果，锻炼逻辑分析能力。
    3.  **洛谷 P1423 小玉在游泳**  
          * 🗣️ **推荐理由**：通过数学累加计算达到目标的次数，适合巩固“边界分析”技巧。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解中洛璟提到：“比赛的时候还因为正解的正确性和同学讨论（吵架）了半个小时。” 这是非常宝贵的学习经验。
</insights_intro>

> **参考经验 (来自 洛璟)**：“为了证明结论的正确性，和同学讨论了半小时。手造数据发现取min会多选人，最终确定取max。”
>
> **点评**：这位作者的经验告诉我们，遇到不确定的结论时，通过“手造数据验证”和“逻辑辩论”是有效的学习方法。在编程中，即使思路看似简单，也需要通过测试用例或反例验证，避免想当然。

-----

<conclusion>
本次关于“Elimination”的C++解题分析就到这里。希望这份学习指南能帮助大家理解数学分析类问题的核心逻辑，掌握“约束推导”和“反例验证”的技巧。记住，多思考、多验证，编程能力会越来越强！下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：136.73秒