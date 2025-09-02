# 题目信息

# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1
```

### 输出

```
1 2 3 0 3 
```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1
```

### 输出

```
2 2 2 1 1 0 4 3 4 4 
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Petya's Exams 深入学习指南 💡

<introduction>
今天我们来一起分析“Petya's Exams”这道题。这道题需要我们为Petya安排考试复习和考试的时间，确保所有考试都能按时准备好。本指南将帮助大家梳理题目思路，理解贪心算法的应用，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法

🗣️ **初步分析**：
解决“Petya's Exams”这道题，关键在于理解并运用贪心算法。贪心算法就像“赶早不赶晚”的生活智慧——每一步都选择当前最紧急的任务优先完成。在本题中，“最紧急”的任务是考试时间更早的考试，因为它们的复习时间窗口（从公布时间到考试前一天）更短，需要优先安排复习。

- **题解思路与核心难点**：所有优质题解均采用“按考试时间排序，优先安排早考的考试”的贪心策略。核心难点在于如何高效分配复习时间，确保每门考试都能在其复习窗口内找到足够的天数。若某门考试的复习窗口内无法凑够所需天数，则无解。
- **核心算法流程**：首先将所有考试按考试时间（d_i）升序排序；然后初始化考试当天为“考试”状态；接着为每门考试从公布时间（s_i）到考试前一天（d_i-1）遍历，将空闲天数分配给该考试的复习；最后检查是否所有考试都满足复习天数要求。
- **可视化设计思路**：采用8位像素风格动画，用不同颜色的方块代表不同考试（如红色为考试1，蓝色为考试2），考试当天用金色方块标记，空闲天为灰色。动画中，每为一门考试分配一个复习天，对应颜色的方块会从s_i开始“填充”到d_i-1的位置，直到填满c_i个方块。若无法填满，动画会闪烁红色并播放提示音效。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下3道题解因逻辑简洁、代码规范且能准确体现贪心策略，被选为优质题解（评分≥4星）。
</eval_intro>

**题解一：风中の菜鸡 (赞：6)**
* **点评**：此题解思路清晰，代码结构工整。通过结构体存储考试信息，按考试时间排序后，从公布时间到考试前一天遍历空闲天数分配复习。变量命名（如`promulgate`对应s_i，`start`对应d_i）直观易懂，边界处理严谨（如初始化考试当天为`m+1`）。亮点在于通过`num`变量统计已复习天数，确保每门考试的复习天数达标后及时跳出循环，避免无效遍历。

**题解二：fls233666 (赞：4)**
* **点评**：此题解代码简洁高效，使用`inline`和`rgt`（寄存器变量）优化，提升运行速度。核心逻辑直接——排序后遍历复习窗口，空闲天分配复习。变量`plan`数组明确记录每天状态（0为空闲，考试当天为`m+1`），代码可读性强。亮点是通过`e[i].ci--`直接统计剩余复习天数，逻辑简洁。

**题解三：kimidonatsu (赞：1)**
* **点评**：此题解结构清晰，将代码分为`read`（输入）、`work`（核心处理）、`write`（输出）三个函数，模块化设计值得学习。注释详细，解释了每一步的目的（如“在读入时标记考试天”）。亮点是使用`stable_sort`保持相同d_i的考试顺序稳定，避免因排序导致的逻辑错误。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼核心思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何确定贪心策略的正确性？
    * **分析**：贪心策略的核心是“优先处理考试时间早的考试”。因为早考的考试复习窗口（s_i到d_i-1）更短，若不优先安排，可能因后续考试占用时间导致无法满足复习天数。优质题解均通过按d_i排序验证了这一策略的正确性。
    * 💡 **学习笔记**：当问题涉及“截止时间”时，优先处理截止时间早的任务是贪心的常见策略。

2.  **关键点2**：如何处理考试天的初始化？
    * **分析**：考试当天必须用于考试，不能复习或休息。优质题解在输入阶段直接将考试天（d_i）标记为`m+1`（如`plan[d_i] = m+1`），避免后续分配复习时占用这些天。
    * 💡 **学习笔记**：提前标记特殊状态（如考试天）是避免后续逻辑错误的关键。

3.  **关键点3**：如何判断是否存在足够的复习天数？
    * **分析**：为每门考试分配复习天时，需统计已分配的天数（如`num`或`e[i].ci--`）。若遍历完复习窗口后，已分配天数仍小于所需天数（c_i），则输出-1。
    * 💡 **学习笔记**：及时检查每一步的结果（如是否满足c_i）是避免后续无效计算的重要手段。

### ✨ 解题技巧总结
- **问题抽象**：将问题转化为“为每个考试在指定区间内分配足够的天数”，简化为区间调度问题。
- **排序优化**：按d_i排序后，后续处理只需遍历一次考试列表，时间复杂度为O(nm)，适合本题数据规模（n≤100）。
- **边界处理**：考试天必须提前标记，避免复习天分配时冲突。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合了优质题解思路的通用核心实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了风中の菜鸡和fls233666的思路，按d_i排序，初始化考试天，遍历复习窗口分配复习天，确保逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;

    struct Exam {
        int s, d, c, id; // 公布时间、考试时间、复习天数、考试编号
    };

    bool cmp(Exam a, Exam b) {
        return a.d < b.d; // 按考试时间升序排序
    }

    int main() {
        int n, m;
        cin >> n >> m;
        Exam exams[m + 1];
        int plan[n + 1] = {0}; // 0表示空闲，m+1表示考试天

        // 输入并初始化考试天
        for (int i = 1; i <= m; ++i) {
            cin >> exams[i].s >> exams[i].d >> exams[i].c;
            exams[i].id = i;
            plan[exams[i].d] = m + 1; // 标记考试天
        }

        sort(exams + 1, exams + m + 1, cmp); // 按考试时间排序

        // 分配复习天
        for (int i = 1; i <= m; ++i) {
            int need = exams[i].c;
            for (int j = exams[i].s; j < exams[i].d; ++j) {
                if (need == 0) break;
                if (plan[j] == 0) { // 空闲天分配复习
                    plan[j] = exams[i].id;
                    need--;
                }
            }
            if (need > 0) { // 复习天数不足
                cout << -1 << endl;
                return 0;
            }
        }

        // 输出结果（空闲天设为0）
        for (int i = 1; i <= n; ++i) {
            cout << plan[i] << " ";
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先输入考试信息并标记考试天，然后按考试时间排序。接着遍历每门考试，从公布时间到考试前一天分配空闲天作为复习天。若某门考试无法满足复习天数，输出-1；否则输出每天的安排。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段，理解其亮点和思路。
</code_intro_selected>

**题解一：风中の菜鸡**
* **亮点**：通过结构体存储考试信息，明确记录考试编号（`place`），避免排序后编号混乱。
* **核心代码片段**：
    ```cpp
    struct Exam{
        int promulgate, start, review, place; 
    };
    sort(exam+1, exam+m+1, cmp); // 按start（d_i）排序
    for(int i=1; i<=m; i++){
        num=0;
        for(int j=exam[i].promulgate; j<exam[i].start; j++){
            if(num == exam[i].review) break;
            if(jh[j] == -1){
                jh[j] = exam[i].place;
                num++;
            }
        }
        if(num < exam[i].review) { /* 输出-1 */ }
    }
    ```
* **代码解读**：结构体`Exam`的`place`字段记录原始考试编号，确保排序后仍能正确标记复习天对应的考试。外层循环遍历排序后的考试，内层循环遍历复习窗口，`num`统计已分配的复习天数，若达标则跳出循环，避免无效遍历。
* 💡 **学习笔记**：当排序可能打乱原始顺序时，记录原始编号是关键。

**题解二：fls233666**
* **亮点**：使用`rgt`（寄存器变量）优化循环变量，提升运行速度；通过`e[i].ci--`直接统计剩余复习天数，逻辑简洁。
* **核心代码片段**：
    ```cpp
    sort(e+1, e+1+m, cmp);
    for(rgt i=1; i<=m; i++){
        for(rgt j=e[i].si; j<e[i].di; j++){
            if(!plan[j]){
                plan[j] = e[i].id;
                e[i].ci--;
                if(!e[i].ci) break;
            }
        }
        if(e[i].ci){ /* 输出-1 */ }
    }
    ```
* **代码解读**：排序后，内层循环遍历复习窗口，`plan[j]`为0表示空闲，分配复习后`e[i].ci--`。若`e[i].ci`减至0，说明复习天数达标，跳出循环。
* 💡 **学习笔记**：直接操作剩余复习天数（`ci`）可简化代码逻辑。

**题解三：kimidonatsu**
* **亮点**：代码模块化（`read`、`work`、`write`函数），注释详细，易于理解和维护。
* **核心代码片段**：
    ```cpp
    void work() {
        stable_sort(exams + 1, exams + m + 1, cmp);
        for (re int i = 1; i <= m; i++) {
            for (re int j = exams[i].s; j < exams[i].d; j++) {
                if (!ans[j]) {
                    ans[j] = exams[i].id;
                    exams[i].c--;
                    if (!exams[i].c) break;
                }
            }
            if (exams[i].c) { /* 输出-1 */ }
        }
    }
    ```
* **代码解读**：`stable_sort`保持相同d_i的考试顺序稳定，避免因排序导致的逻辑错误。`ans[j]`为0时分配复习，`exams[i].c--`统计剩余复习天数。
* 💡 **学习笔记**：模块化设计能提高代码的可读性和可维护性。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解贪心算法如何分配复习天，我们设计了一个“像素复习计划”动画，用8位复古风格模拟考试复习的分配过程。
</visualization_intro>

  * **动画演示主题**：`像素复习计划——帮Petya安排考试`

  * **核心演示内容**：模拟按考试时间排序后，每门考试从公布时间到考试前一天分配复习天的过程，展示空闲天如何被填充为对应考试的复习天，若无法填满则提示失败。

  * **设计思路简述**：采用8位像素风格（如FC游戏的方块造型），用不同颜色区分考试（考试1为红色，考试2为蓝色），考试天用金色方块标记，空闲天为灰色。动画通过颜色变化和音效反馈关键操作（如分配复习天的“叮”声），增强学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕显示n个像素方块（代表n天），初始为灰色（空闲）。
          * 控制面板包含“开始”“暂停”“单步”按钮和速度滑块。
          * 播放8位风格背景音乐（如《超级玛丽》的轻快旋律）。

    2.  **输入与排序**：
          * 输入考试信息时，对应考试天（d_i）的方块变为金色，显示“考试”文字。
          * 按d_i排序时，考试卡片（带d_i、s_i、c_i信息）从右到左滑动，按d_i升序排列。

    3.  **分配复习天**：
          * 处理第一门考试（d_i最小）时，从s_i到d_i-1的方块依次闪烁白色（表示检查是否空闲）。
          * 遇到灰色方块（空闲）时，变为对应考试的颜色（如红色），播放“叮”音效，显示“复习考试1”文字。
          * 当该考试的复习天数（c_i）达标时，播放“滴”音效，显示“考试1复习完成”。

    4.  **失败提示**：
          * 若某门考试遍历完复习窗口仍有剩余c_i，所有方块变为红色，播放“嗡”音效，显示“无法完成复习！”。

    5.  **成功结束**：
          * 所有考试复习完成后，金色考试天闪烁，播放“胜利”音效，显示“所有考试准备就绪！”。

  * **旁白提示**：
      * （排序时）“先处理考试时间早的考试，因为它们的复习时间更少哦~”
      * （分配复习天时）“看！这个灰色的空闲天被分配给考试1复习啦~”
      * （失败时）“哎呀，考试2的复习天数不够，Petya无法参加考试了...”

<visualization_conclusion>
通过这个像素动画，我们能直观看到贪心算法如何一步步分配复习天，理解“优先处理早考考试”的策略为何能解决问题。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握贪心算法在本题的应用后，我们可以尝试解决更多类似的区间调度问题。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 贪心算法适用于“每一步选择当前最优”的问题，如任务调度（优先处理截止时间早的任务）、资源分配（优先满足需求紧迫的用户）、区间覆盖（选择结束时间早的区间）等。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1230 智力大冲浪** 
          * 🗣️ **推荐理由**：这道题需要安排游戏时间，涉及贪心策略（优先完成时间紧迫的任务），与本题思路相似。
    2.  **洛谷 P1803 线段覆盖** 
          * 🗣️ **推荐理由**：此题要求选择最多不重叠的线段，需按结束时间排序，是贪心算法的经典应用。
    3.  **洛谷 P1090 合并果子** 
          * 🗣️ **推荐理由**：通过贪心选择最小的两堆合并，培养“每一步选最优”的思维，适合巩固贪心策略。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些经验对我们很有参考价值：
</insights_intro>

> **参考经验 (来自 风中の菜鸡)**：“在初始化考试天时，我一开始忘记将`jh[exam[i].start]`设为`m+1`，导致复习天分配到了考试天，结果输出错误。后来通过打印`jh`数组发现了问题。”

**点评**：这位作者的经验提醒我们，边界条件（如考试天的初始化）是容易出错的地方。调试时，打印关键数组（如`plan`或`jh`）的状态能快速定位错误。这是非常实用的调试技巧！

-----

<conclusion>
本次关于“Petya's Exams”的C++解题分析就到这里。贪心算法的核心是“每一步选当前最优”，通过本题的学习，相信大家对这一策略有了更深刻的理解。记住，多练习、多调试，编程能力会稳步提升！下次我们再一起探索新的算法挑战！💪
</conclusion>

---
处理用时：182.76秒