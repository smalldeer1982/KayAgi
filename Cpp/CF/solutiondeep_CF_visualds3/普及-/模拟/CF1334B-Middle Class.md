# 题目信息

# Middle Class

## 题目描述

Many years ago Berland was a small country where only $ n $ people lived. Each person had some savings: the $ i $ -th one had $ a_i $ burles.

The government considered a person as wealthy if he had at least $ x $ burles. To increase the number of wealthy people Berland decided to carry out several reforms. Each reform looked like that:

- the government chooses some subset of people (maybe all of them);
- the government takes all savings from the chosen people and redistributes the savings among the chosen people equally.

For example, consider the savings as list $ [5, 1, 2, 1] $ : if the government chose the $ 1 $ -st and the $ 3 $ -rd persons then it, at first, will take all $ 5 + 2 = 7 $ burles and after that will return $ 3.5 $ burles to the chosen people. As a result, the savings will become $ [3.5, 1, 3.5, 1] $ .

A lot of data was lost from that time, so we don't know how many reforms were implemented and to whom. All we can do is ask you to calculate the maximum possible number of wealthy people after several (maybe zero) reforms.

## 说明/提示

The first test case is described in the statement.

In the second test case, the government, for example, could carry out two reforms: $ [\underline{11}, \underline{9}, 11, 9] \rightarrow [10, 10, \underline{11}, \underline{9}] \rightarrow [10, 10, 10, 10] $ .

In the third test case, the government couldn't make even one person wealthy.

In the fourth test case, the government could choose all people to carry out a reform: $ [\underline{9}, \underline{4}, \underline{9}] \rightarrow [7\frac{1}{3}, 7\frac{1}{3}, 7\frac{1}{3}] $ .

## 样例 #1

### 输入

```
4
4 3
5 1 2 1
4 10
11 9 11 9
2 5
4 3
3 7
9 4 9```

### 输出

```
2
4
0
3```

# AI分析结果



---
# 💡 Kay的C++算法解析：Middle Class 深入学习指南 💡

<introduction>
今天我们来一起分析“Middle Class”这道C++编程题。本指南将帮助大家梳理题目思路，理解核心贪心算法，并掌握解题技巧。通过分析多个优质题解，我们还会设计一个有趣的像素动画来直观展示算法过程，最后推荐拓展练习巩固知识。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法应用

🗣️ **初步分析**：
解决“Middle Class”这道题，关键在于理解并运用贪心算法。贪心算法的核心思想是：每一步选择当前最优的局部解，最终组合成全局最优解。就像分糖果时，先给最需要的人分最多的，这样整体满足感更强。在本题中，我们需要找到最多的数，使得它们的平均值≥x。贪心策略是：选择最大的k个数，因为它们的和更可能满足k*x的条件，从而通过一次操作（取平均）让这k个数都≥x。

- **题解思路**：所有优质题解均采用“排序后贪心选择最大数”的思路。具体来说：将数组从大到小排序，依次累加前k个数的和，判断是否≥k*x。最大的满足条件的k即为答案。
- **核心难点**：如何高效确定最大的k值？关键在于排序后从大到小累加，并实时判断和是否满足条件。
- **可视化设计**：我们将设计一个8位像素风格的动画，展示数组排序过程（像素方块从高到低排列），然后用绿色高亮当前累加的数，红色提示不满足条件的步骤，配合“叮”的音效表示成功累加，“滴滴”声表示不满足条件。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑简洁、代码高效被选为优质参考（评分≥4星）：
</eval_intro>

**题解一：作者Warriors_Cat (赞：4)**
* **点评**：此题解思路非常清晰，通过将每个数先减去x，转化为“总和≥0”的问题，简化了判断逻辑。代码中使用`sort`排序和循环累加的方式，时间复杂度为O(n log n)，适合处理n≤1e5的规模。变量命名简洁（如`sum`），边界处理（`sum=0`清零）严谨，是竞赛代码的典型风格。亮点在于将问题转化为“总和是否非负”，降低了理解难度。

**题解二：作者AutumnKite (赞：1)**
* **点评**：此题解直接点明“最优策略是选择最大的s个数”，逻辑直白。代码中使用`sort`+`reverse`实现从大到小排序，循环累加并判断`sum >= x*i`，代码简洁且易读。变量`sum`的使用直观，体现了贪心的核心逻辑。亮点在于对问题本质的精准把握——“最大的s个数的和是否≥s*x”。

**题解三：作者syzf2222 (赞：0)**
* **点评**：此题解代码极为简洁，通过`sort`+自定义比较函数（从大到小排序），循环累加并判断`sum >= x*i`，直接输出最大的i。代码中使用`int long long`避免溢出，考虑了数据范围，实践价值高。亮点在于将问题转化为“前i个最大数的和是否≥i*x”，一步到位。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个关键点或难点。结合优质题解的共性，提炼出核心思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何选择最优的数集合？
    * **分析**：要使k个数的平均值≥x，等价于这k个数的和≥k*x。由于较大的数更易满足这个条件，因此最优策略是选择最大的k个数（排序后前k个）。优质题解均通过排序后从大到小累加的方式实现这一点。
    * 💡 **学习笔记**：贪心选择最大的数，是解决此类“最大化数量”问题的常用策略。

2.  **关键点2**：如何高效判断最大的k值？
    * **分析**：排序后，从k=1到k=n依次判断前k个数的和是否≥k*x。一旦不满足，最大k即为当前i-1。此过程只需一次遍历，时间复杂度为O(n)，结合排序的O(n log n)，整体高效。
    * 💡 **学习笔记**：排序+前缀和是解决“最大k值”问题的经典组合。

3.  **关键点3**：如何处理数据范围避免溢出？
    * **分析**：题目中a_i和n可能较大（a_i≤1e9，n≤1e5），累加和可能达到1e14，需用`long long`类型存储。优质题解均注意到这一点，使用`long long sum`避免溢出。
    * 💡 **学习笔记**：数据范围较大时，优先使用`long long`存储累加和。

### ✨ 解题技巧总结
- **问题转化**：将“平均值≥x”转化为“总和≥k*x”，简化判断条件。
- **排序方向**：从大到小排序，优先选择较大的数，是贪心的核心操作。
- **边界处理**：多组数据时，注意清空变量（如`sum=0`），避免上一组数据的干扰。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个优质题解的思路，采用排序后从大到小累加的方式，简洁高效地解决问题。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;

    const int MAXN = 1e5 + 10;
    long long a[MAXN]; // 使用long long避免溢出

    int main() {
        int t;
        cin >> t;
        while (t--) {
            int n, x;
            cin >> n >> x;
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
            }
            // 从大到小排序
            sort(a, a + n, greater<long long>());
            long long sum = 0;
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                sum += a[i];
                if (sum >= 1LL * x * (i + 1)) { // 前i+1个数的和是否≥(i+1)*x
                    ans = i + 1;
                } else {
                    break; // 不满足则后续更小的数也不满足
                }
            }
            cout << ans << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入，将数组从大到小排序。然后依次累加前i+1个数的和，判断是否≥(i+1)*x。若满足，更新答案为i+1；否则跳出循环。最终输出最大的ans。核心逻辑是利用排序后的数组，贪心选择最大的数并验证其和是否满足条件。

---
<code_intro_selected>
接下来，我们将剖析优质题解中的核心代码片段，点出各自的亮点和关键思路。
</code_intro_selected>

**题解一：作者Warriors_Cat**
* **亮点**：将每个数先减去x，转化为“总和≥0”的问题，简化判断逻辑。
* **核心代码片段**：
    ```cpp
    for(int i = 1; i <= n; ++i){
        scanf("%lld", a + i);
        a[i] -= m; // 每个数减去x
        sum += a[i]; 
    }
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; ++i){
        if(sum >= 0){
            printf("%lld\n", n - i + 1);
            flag = 1;
            break;
        }
        sum -= a[i]; // 减去最小的数（排序后a[i]从小到大）
    }
    ```
* **代码解读**：
    > 这段代码将每个数减去x（即`m`），使得问题转化为“选择k个数，它们的和≥0”。排序后数组从小到大，依次减去最小的数（即排除不满足条件的小数），直到剩余数的和≥0。此时剩余的数个数即为答案。例如，若排序后数组为[-2, -1, 1, 3]，初始sum=1（-2-1+1+3=1），直接满足sum≥0，答案为4。若sum<0，则减去最小的数（-2），sum=3，此时剩余3个数，继续判断。
* 💡 **学习笔记**：问题转化是简化计算的重要技巧，将“平均值≥x”转化为“总和≥0”后，判断更直观。

**题解二：作者AutumnKite**
* **亮点**：直接排序后从大到小累加，判断前i个数的和是否≥i*x，逻辑直白。
* **核心代码片段**：
    ```cpp
    std::sort(a + 1, a + 1 + n);
    std::reverse(a + 1, a + 1 + n); // 从大到小排序
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += a[i];
        if (sum < 1ll * x * i) { // 不满足则输出i-1
            print(i - 1);
            return;
        }
    }
    print(n); // 所有数都满足
    ```
* **代码解读**：
    > 这段代码先排序数组，再反转得到从大到小的顺序。然后累加前i个数的和，若和小于i*x，说明前i个数无法通过平均得到≥x的数，最大k为i-1。例如，数组[11,9,11,9]排序后为[11,11,9,9]，i=4时sum=40≥4*10=40，满足条件，答案为4。
* 💡 **学习笔记**：从大到小排序后直接累加，是贪心策略的直观体现。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解贪心算法的执行过程，我们设计了一个“像素财富分配”动画，以8位复古游戏风格展示排序、累加和判断的过程。
</visualization_intro>

  * **动画演示主题**：像素小镇的财富分配游戏

  * **核心演示内容**：展示数组从乱序到排序的过程，然后逐步选择最大的数，用颜色变化表示是否满足“平均值≥x”的条件。

  * **设计思路简述**：采用8位像素风格（如FC游戏的方块造型），通过颜色区分不同数值的“财富块”。排序时，财富块从高到低排列；累加时，绿色高亮当前选中的块，红色提示不满足条件的步骤。音效（如“叮”声）强化关键操作记忆，增加学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧显示乱序的像素财富块（每个块高度代表数值大小，颜色随机），右侧显示控制面板（开始/暂停、单步、重置按钮，速度滑块）。
          * 播放8位风格的轻快背景音乐（如《超级马力欧》的经典旋律）。

    2.  **排序过程**：
          * 点击“开始”，财富块开始排序动画：相邻块比较，较大的块向右“跳跃”，直到所有块从高到低排列（类似冒泡排序的像素版）。
          * 每完成一次比较，播放“滴答”音效；完成排序后，播放“叮咚”音效。

    3.  **累加判断**：
          * 从左到右依次选中财富块（第1个、第1-2个、第1-3个…），选中的块变为绿色，未选中的保持原色。
          * 计算当前选中块的和与i*x的大小：
            - 若和≥i*x，绿色块闪烁，播放“叮”声，并显示“满足条件！”文字提示。
            - 若和<i*x，绿色块变为红色，播放“滴滴”声，并显示“不满足，尝试更少的块…”。
          * 最终最大的满足条件的i值用金色边框高亮，播放“胜利”音效（如《塞尔达传说》的胜利旋律）。

    4.  **交互控制**：
          * 支持“单步”执行，每点击一次“单步”按钮，执行一次累加判断。
          * 速度滑块可调整动画速度（慢、中、快），适合不同学习节奏。
          * 点击“重置”按钮，回到初始乱序状态，重新开始演示。

  * **旁白提示**：
      - （排序时）“看！财富块在跳舞~ 它们要排好队，从高到低站好！”
      - （累加时）“现在选中前i个块，它们的总和是多少？和i*x比谁大？”
      - （满足条件时）“太棒了！这i个块的平均值≥x，可以成为富人！”

<visualization_conclusion>
通过这个像素动画，我们可以直观看到贪心算法如何通过排序和累加，一步步找到最大的k值。颜色、音效和交互设计让抽象的算法变得生动有趣，帮助我们更好地理解核心逻辑。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的贪心策略后，我们可以进一步思考该算法的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 贪心选择最大/最小元素：此类策略还适用于“最大子数组和”“活动选择问题”“任务调度”等场景。
      * 排序+前缀和：在需要快速判断“前k个元素是否满足条件”的问题中，此方法非常高效（如“最大k个数的平均值”“最小k个数的和”）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1208 [USACO1.3] 混合牛奶**
          * 🗣️ **推荐理由**：这道题需要选择价格最低的牛奶，贪心选择最小价格的牛奶，与本题“选择最大数”的思路类似，可巩固贪心策略的应用。
    2.  **洛谷 P1094 [NOIP2007 提高组] 纪念品分组**
          * 🗣️ **推荐理由**：此题需要将纪念品分组，每组价格和不超过x，贪心选择最大和最小配对，是贪心策略的变形应用。
    3.  **洛谷 P1803 [NOI2003] 线段覆盖**
          * 🗣️ **推荐理由**：此题需要选择最多的不重叠线段，贪心选择结束最早的线段，与本题“最大化数量”的目标一致，适合拓展练习。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验和注意事项，这些经验对我们很有参考价值：
</insights_intro>

> **参考经验 (来自作者Warriors_Cat)**：“记得在多组数据时清空sum变量，否则上一组的sum会影响当前组的计算。”
>
> **点评**：多组数据的处理是竞赛中的常见问题。作者的提醒非常关键——累加变量（如sum）在每组数据开始前必须清零，否则会导致错误。这提醒我们在编写多组数据的代码时，要特别注意变量的初始化。

---

<conclusion>
本次关于“Middle Class”的C++解题分析就到这里。希望这份学习指南能帮助大家理解贪心算法的应用，掌握排序+累加的解题技巧。记住，编程能力的提升在于多思考、多练习，下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：145.93秒