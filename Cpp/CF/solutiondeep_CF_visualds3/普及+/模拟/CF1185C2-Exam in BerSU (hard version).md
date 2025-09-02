# 题目信息

# Exam in BerSU (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

If you write a solution in Python, then prefer to send it in PyPy to speed up execution time.

A session has begun at Beland State University. Many students are taking exams.

Polygraph Poligrafovich is going to examine a group of $ n $ students. Students will take the exam one-by-one in order from $ 1 $ -th to $ n $ -th. Rules of the exam are following:

- The $ i $ -th student randomly chooses a ticket.
- if this ticket is too hard to the student, he doesn't answer and goes home immediately (this process is so fast that it's considered no time elapses). This student fails the exam.
- if the student finds the ticket easy, he spends exactly $ t_i $ minutes to pass the exam. After it, he immediately gets a mark and goes home.

Students take the exam in the fixed order, one-by-one, without any interruption. At any moment of time, Polygraph Poligrafovich takes the answer from one student.

The duration of the whole exam for all students is $ M $ minutes ( $ \max t_i \le M $ ), so students at the end of the list have a greater possibility to run out of time to pass the exam.

For each student $ i $ , you should count the minimum possible number of students who need to fail the exam so the $ i $ -th student has enough time to pass the exam.

For each student $ i $ , find the answer independently. That is, if when finding the answer for the student $ i_1 $ some student $ j $ should leave, then while finding the answer for $ i_2 $ ( $ i_2>i_1 $ ) the student $ j $ student does not have to go home.

## 说明/提示

The explanation for the example 1.

Please note that the sum of the first five exam times does not exceed $ M=15 $ (the sum is $ 1+2+3+4+5=15 $ ). Thus, the first five students can pass the exam even if all the students before them also pass the exam. In other words, the first five numbers in the answer are $ 0 $ .

In order for the $ 6 $ -th student to pass the exam, it is necessary that at least $ 2 $ students must fail it before (for example, the $ 3 $ -rd and $ 4 $ -th, then the $ 6 $ -th will finish its exam in $ 1+2+5+6=14 $ minutes, which does not exceed $ M $ ).

In order for the $ 7 $ -th student to pass the exam, it is necessary that at least $ 3 $ students must fail it before (for example, the $ 2 $ -nd, $ 5 $ -th and $ 6 $ -th, then the $ 7 $ -th will finish its exam in $ 1+3+4+7=15 $ minutes, which does not exceed $ M $ ).

## 样例 #1

### 输入

```
7 15
1 2 3 4 5 6 7
```

### 输出

```
0 0 0 0 0 2 3 ```

## 样例 #2

### 输入

```
5 100
80 40 40 40 60
```

### 输出

```
0 1 1 2 3 ```

# AI分析结果



---
# 💡 Kay的C++算法解析：Exam in BerSU (hard version) 深入学习指南 💡

<introduction>
今天我们来分析这道“Exam in BerSU (hard version)”的C++编程题。这道题的核心是通过贪心策略和高效数据结构，快速计算每个学生需要前面多少人不及格才能按时完成考试。本指南将带大家梳理思路、解析核心算法，并通过可视化方案直观理解过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`贪心算法 + 高效数据结构应用`

🗣️ **初步分析**：
解决这道题的关键在于“贪心选择删除最大的元素”。想象一下，你有一个时间预算M，每个学生i需要前面学生的总时间加上自己的时间t_i不超过M。为了让删除的人数最少，我们肯定优先删除前面时间最长的学生（因为大的数对总时间的贡献更大，删除它们能更快减少总时间）。这就是贪心策略的核心——每次选当前最优。

题解中常见两种思路：
- **值域小的情况**（如t_i≤100）：用桶排序统计各值的数量，从大到小枚举删除（如songhn的桶排解法）。
- **值域大的情况**（如t_i≤2e7）：用权值线段树/树状数组维护元素，通过二分或倍增快速查询需要删除的最小数量（如lzyqwq的权值线段树解法）。

核心算法流程：对每个学生i，计算前i-1个学生的总时间sum。若sum + t_i ≤ M，答案为0；否则，需要删除最大的若干元素，使得sum' + t_i ≤ M。难点在于如何高效找到这些最大的元素的数量。

可视化设计思路：用8位像素风格的“时间管理游戏”展示。每个学生用彩色像素块表示（颜色越深时间越长），总时间用进度条显示。当处理学生i时，高亮前面的像素块，动态删除最大的块（颜色最深的），直到进度条不超过M。每次删除时播放“叮”的音效，完成时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选了以下优质题解：
</eval_intro>

**题解一：songhn的桶排解法 (来源：用户songhn)**
* **点评**：这份题解巧妙利用了t_i值域小的特点（题目中t_i≤M，但样例中t_i较小），用桶统计各时间值的出现次数。思路直白：要删除最少人数，就优先删最大的时间值。代码中用数组mp记录每个时间的出现次数，从100到1枚举删除，计算需要删多少个该时间值的学生。代码简洁规范（如read函数快速输入），时间复杂度O(n*100)，非常高效，适合值域小的场景。实践价值高，直接可用于竞赛。

**题解二：lzyqwq的权值线段树解法 (来源：用户lzyqwq)**
* **点评**：针对t_i值域大的情况（如t_i≤2e7），此题解使用动态开点权值线段树，维护元素的数量和总和。查询时二分选择右子树（优先删大的元素），直到总和满足条件。代码规范（如模板化的read/write函数），时间复杂度O(n log m)，适合处理大范围数据。虽然动态开点稍复杂，但思路清晰，是处理大范围值域问题的典型方法。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于如何高效找到需要删除的最大元素数量。结合优质题解，我们提炼以下关键点：
</difficulty_intro>

1.  **关键点1：贪心策略的选择**
    * **分析**：为什么优先删除最大的元素？因为要让总时间减少得最快，删除大的元素比小的更有效。例如，总时间超了10，删一个10的元素只需要删1个，而删两个5的需要删2个。优质题解（如songhn）都明确采用了这一策略。
    * 💡 **学习笔记**：贪心的核心是“局部最优导致全局最优”，本题中删除最大元素是局部最优选择。

2.  **关键点2：高效维护元素集合**
    * **分析**：当t_i值域小时（如≤100），可以用桶排序（数组统计）；当值域大时（如≤2e7），需要用权值线段树或树状数组。例如，lzyqwq的线段树维护了每个值的出现次数和总和，支持快速查询需要删除的元素数量。
    * 💡 **学习笔记**：数据结构的选择要结合问题特性（如值域大小、操作类型）。

3.  **关键点3：动态更新与查询**
    * **分析**：每个学生i处理完后，需要将t_i加入集合，供后续学生查询。例如，songhn的代码中每次循环结束后更新mp[a[i]]++，lzyqwq的线段树每次插入新元素。动态维护是保证算法高效的关键。
    * 💡 **学习笔记**：动态数据结构（如线段树、树状数组）能高效处理“插入+查询”的组合操作。

### ✨ 解题技巧总结
- **问题转化**：将“最少删除人数”转化为“找最大的若干元素，其和≥sum_prev + t_i - M”。
- **值域分治**：根据t_i的值域大小选择数据结构（桶排/线段树/树状数组）。
- **前缀和预处理**：用sum数组快速计算前i个学生的总时间，减少重复计算。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们选取songhn的桶排解法作为通用核心实现（适用于t_i较小的场景），并分析其核心逻辑。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码基于songhn的题解，利用桶排统计各时间值的出现次数，从大到小枚举删除，适用于t_i≤100的场景。
* **完整核心代码**：
    ```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;
    const int maxn=200050;
    int n, m, a[maxn], mp[105]; // mp[t]记录时间t的出现次数
    inline int read() { /* 快速输入函数 */ }

    int main() {
        n = read(), m = read();
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            a[i] = read();
            sum += a[i];
            if (sum <= m) {
                printf("0 ");
            } else {
                int need = sum - m; // 需要删除的总时间
                int cnt = 0;
                // 从大到小枚举时间值，优先删大的
                for (int t = 100; t >= 1; --t) {
                    if (mp[t] == 0) continue;
                    // 最多删k个t，使得k*t ≤ need
                    int k = min(mp[t], need / t + (need % t != 0));
                    cnt += k;
                    need -= k * t;
                    if (need <= 0) break;
                }
                printf("%d ", cnt);
            }
            mp[a[i]]++; // 将当前时间加入桶
        }
        return 0;
    }
    ```
* **代码解读概要**：
  代码首先读取输入，维护前缀和sum。对于每个学生i，若sum≤m直接输出0；否则计算需要删除的总时间need，从大到小枚举时间值t（100到1），统计需要删除的t的数量，直到need≤0。最后将当前时间t_i加入桶mp，供后续学生使用。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：songhn的桶排解法**
* **亮点**：利用值域小的特点，用桶排O(100)时间完成删除统计，时间复杂度O(n*100)，非常高效。
* **核心代码片段**：
    ```cpp
    int need = sum - m;
    int cnt = 0;
    for (int t = 100; t >= 1; --t) {
        if (mp[t] == 0) continue;
        int k = min(mp[t], need / t + (need % t != 0));
        cnt += k;
        need -= k * t;
        if (need <= 0) break;
    }
    ```
* **代码解读**：
  这段代码计算需要删除的学生数。`need`是需要减少的总时间（sum - m）。从大到小枚举时间t（100到1），计算最多能删多少个t（k为当前t的数量和需要的数量的较小值），累加cnt并减少need。当need≤0时停止，此时cnt即为最少删除人数。
* 💡 **学习笔记**：值域小的问题可以用桶排简化，避免复杂数据结构。

**题解二：lzyqwq的权值线段树解法**
* **亮点**：动态开点线段树处理大范围值域，支持高效插入和查询。
* **核心代码片段**：
    ```cpp
    struct SegmentTree {
        int rt, sum[N*30], tot[N*30], cnt, ls[N*30], rs[N*30];
        void modify(int &x, int l, int r, int val) { /* 插入val */ }
        int query(int x, int l, int r, int k) { /* 查询需要删除的最小数量 */ }
    } sgt;

    // 主函数中查询需要删除的数量
    sgt.query(sgt.rt, 1, 2e7, s[i] - m);
    ```
* **代码解读**：
  `modify`函数动态插入元素，维护每个节点的总和（sum）和数量（tot）。`query`函数递归查询右子树（优先删大的元素），若右子树总和≥k，则继续在右子树找；否则删右子树所有元素，去左子树找剩余部分。这样能快速找到最少需要删除的数量。
* 💡 **学习笔记**：动态开点线段树适合处理值域大但实际元素少的场景，节省空间。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“贪心删除最大元素”的过程，我们设计一个8位像素风格的“时间管理游戏”动画！
</visualization_intro>

  * **动画演示主题**：`像素学生时间大作战`

  * **核心演示内容**：展示每个学生i的处理过程：计算总时间→超限时删除最大的前面学生→更新总时间→输出删除人数。

  * **设计思路简述**：8位像素风格（FC红白机色调）让学习更轻松；用不同颜色的像素块表示学生时间（红色>蓝色>绿色，颜色越深时间越长）；删除操作时播放“叮”音效，完成时播放胜利音效，增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕分为三部分：左上方显示当前学生i，中间是像素网格（每个格子代表一个学生，颜色表示时间），右下方是总时间进度条（绿色≤M，红色>M）。
        - 控制面板有“单步”“自动播放”按钮和速度滑块。

    2.  **处理学生i**：
        - 新学生i的像素块（黄色）从右侧滑入网格，总时间进度条更新。
        - 若进度条绿色（总时间≤M），播放“成功”音效，输出0。
        - 若进度条红色（总时间>M），进入删除流程：

    3.  **删除最大元素**：
        - 用白色箭头指向当前最大的像素块（颜色最深），闪烁提示。
        - 该像素块被“擦除”（变灰色），总时间减少其时间值，进度条缩短。
        - 播放“删除”音效（短促“叮”），删除人数+1。
        - 重复直到进度条变绿色，输出删除人数。

    4.  **AI自动演示**：
        - 点击“AI演示”，动画自动处理所有学生，展示完整流程，学习者可观察删除策略的动态调整。

    5.  **结束状态**：
        - 所有学生处理完成后，播放“通关”音乐，显示最终输出结果。

  * **旁白提示**：
    - “当前总时间超过M，需要删除前面的学生！”
    - “看，这个红色块时间最长，先删它！”
    - “总时间达标啦，删除了2个学生~”

<visualization_conclusion>
通过这个像素动画，我们能直观看到贪心策略如何选择删除最大元素，总时间如何变化，以及每个学生的处理过程。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的贪心+数据结构思路可迁移到多种场景，比如资源分配、任务调度等。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - **资源分配问题**：如给定总资源，选择最少任务完成目标（优先选资源消耗大的）。
    - **任务调度问题**：如安排任务顺序，使总延迟最小（优先处理耗时多的任务）。
    - **数组优化问题**：如删除最少元素使数组满足条件（优先删对条件影响大的元素）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1090** - `合并果子`
        * 🗣️ **推荐理由**：贪心选择最小的两堆合并，用堆维护，与本题贪心思想类似。
    2.  **洛谷 P3378** - `堆的模板`
        * 🗣️ **推荐理由**：练习堆的基本操作，为解决需要动态维护最值的问题打基础。
    3.  **洛谷 P1484** - `种树`
        * 🗣️ **推荐理由**：贪心选择价值最大的树，用堆+标记处理删除，与本题动态维护元素的思路相似。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到调试中的经验，例如Special_Tony提到初始堆方法的错误，通过回滚操作修复。这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自用户Special_Tony)**：“最初用大根堆直接弹数，但没考虑后续学生可能需要回滚。通过小根堆记录弹出的数，在插入新数时比较并回滚，解决了错误。”

> **点评**：这个经验提醒我们，贪心策略可能因后续操作需要调整，动态维护已删除的元素（如用小根堆记录）可以方便回滚。调试时，自制测试数据（如Hack数据）能有效发现逻辑漏洞。

-----

<conclusion>
本次分析帮助大家理解了“Exam in BerSU (hard version)”的贪心策略和高效数据结构应用。记住，遇到类似问题时，先想贪心策略（局部最优），再根据数据范围选数据结构（桶排/线段树/堆）。多练习洛谷推荐的题目，巩固思路！下次见~ 💪
</conclusion>

---
处理用时：82.63秒