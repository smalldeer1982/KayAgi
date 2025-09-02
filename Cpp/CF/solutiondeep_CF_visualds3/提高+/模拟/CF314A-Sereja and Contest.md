# 题目信息

# Sereja and Contest

## 题目描述

During the last Sereja's Codesecrof round the server crashed many times, so the round was decided to be made unrated for some participants.

Let's assume that $ n $ people took part in the contest. Let's assume that the participant who got the first place has rating $ a_{1} $ , the second place participant has rating $ a_{2} $ , $ ... $ , the $ n $ -th place participant has rating $ a_{n} $ . Then changing the rating on the Codesecrof site is calculated by the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF314A/c51703a6e7729252fb6f20e8a44b483ddf07fc8e.png).

After the round was over, the Codesecrof management published the participants' results table. They decided that if for a participant $ d_{i}&lt;k $ , then the round can be considered unrated for him. But imagine the management's surprise when they found out that the participants' rating table is dynamic. In other words, when some participant is removed from the rating, he is removed from the results' table and the rating is recalculated according to the new table. And of course, all applications for exclusion from the rating are considered in view of the current table.

We know that among all the applications for exclusion from the rating the first application to consider is from the participant with the best rank (the rank with the minimum number), for who $ d_{i}&lt;k $ . We also know that the applications for exclusion from rating were submitted by all participants.

Now Sereja wonders, what is the number of participants to be excluded from the contest rating, and the numbers of the participants in the original table in the order of their exclusion from the rating. Pay attention to the analysis of the first test case for a better understanding of the statement.

## 说明/提示

Consider the first test sample.

1. Initially the sequence of the contest participants' ratings equals \[5, 3, 4, 1, 2\]. You can use this sequence to calculate the sequence of rating changes: \[0, -9, -13, 8, 14\]. According to the problem statement, the application of the participant who won the second place will be considered first.
2. As soon as the second place winner is out from the ratings, the participants' rating sequence will equal \[5, 4, 1, 2\]. By this sequence you can count the new sequence of rating changes: \[0, -8, 2, 6\]. According to the problem statement, the application of the participant who won the second place will be considered. Initially this participant won third place.
3. The new rating sequence equals \[5, 1, 2\], the new sequence of rating changes equals \[0, -1, 1\]. The second place participant's application is taken into consideration, initially this participant won the fourth place.
4. The new rating sequence equals \[5, 2\], the new sequence of rating changes equals \[0, 0\]. No more applications will be considered.

Thus, you should print 2, 3, 4.

## 样例 #1

### 输入

```
5 0
5 3 4 1 2
```

### 输出

```
2
3
4
```

## 样例 #2

### 输入

```
10 -10
5 5 1 7 5 1 2 4 9 2
```

### 输出

```
2
4
5
7
8
9
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Sereja and Contest 深入学习指南 💡

<introduction>
今天我们来一起分析“Sereja and Contest”这道C++编程题。这道题需要我们模拟参赛者被移除的过程，并高效计算每个参赛者的评分变化。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟应用`

🗣️ **初步分析**：
> 解决“Sereja and Contest”这道题，关键在于理解并运用“模拟”的算法思想。简单来说，“模拟”就是按照题目描述的规则，一步步复现问题的执行过程。就像玩拼图游戏，每一步都要按照规则移动拼图块，直到完成目标。在本题中，我们需要模拟参赛者被移除的过程：每次计算当前所有参赛者的评分，找到第一个评分小于k的参赛者并移除，然后更新剩余参赛者的信息，重复这个过程直到没有符合条件的参赛者。

   - **题解思路与核心难点**：题目核心是高效计算每个参赛者的评分 \( d_i \)，避免重复计算。直接暴力模拟每次移除后重新计算所有评分的时间复杂度为 \( O(n^2) \)，无法处理大数据。优质题解通过观察 \( d_i \) 的公式结构，发现可以维护一个累加和 \( sum \)（表示 \( \sum_{j=1}^{i-1} a_j \cdot (j-1) \)），从而将每次计算 \( d_i \) 的时间降为 \( O(1) \)，整体时间复杂度优化为 \( O(n) \)。
   - **核心算法流程**：从第一个参赛者开始，依次计算 \( d_i = sum - (i-1) \cdot (n-i) \cdot a_i \)。若 \( d_i < k \)，则记录该参赛者的原始编号并移除（调整 \( n \) 和当前索引 \( i \)）；否则将 \( a_i \cdot (i-1) \) 加入 \( sum \)，继续处理下一个参赛者。
   - **可视化设计**：采用8位像素风格，用不同颜色的像素方块表示参赛者，初始排列成一行。每次找到 \( d_i < k \) 的参赛者时，该方块闪烁并播放“叮”的音效，随后从队列中移除，后面的方块自动左移。累加和 \( sum \) 和当前 \( n \) 的值在屏幕上方实时显示，用数字变化体现状态更新。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性与优化程度、实践价值等几个方面，筛选了以下评分较高（≥4星）的题解：
</eval_intro>

**题解一：来源：liangbowen**
* **点评**：这份题解思路非常清晰，明确指出了 \( d_i \) 的公式可以分解为累加和 \( sum \) 减去当前项的部分，避免了重复计算。代码风格规范，变量名（如 `d` 表示累加和）含义明确。算法上通过维护 \( sum \) 将时间复杂度优化到 \( O(n) \)，是本题的关键优化点。从实践角度看，代码简洁且边界处理严谨（如 `n--, i--` 调整索引），直接可用于竞赛，参考价值极高。

**题解二：来源：Lee666666**
* **点评**：此题解详细解释了公式的分解过程和优化思路，强调了 \( a_{i+1} \) 到 \( a_n \) 的改变不影响 \( d_i \) 的计算，从而说明维护 \( sum \) 的合理性。代码中包含输入优化（`read` 函数），提升了效率。变量 `sum` 明确表示累加和，逻辑清晰，是理解公式优化的优秀示例。

**题解三：来源：BADFIVE**
* **点评**：此题解代码极其简洁，直接抓住了问题的核心逻辑（维护累加和 \( sum \) 并判断 \( d_i \) 是否小于 \( k \)）。虽然解释较少，但代码结构工整，变量 `tmp` 表示当前 \( a_i \)，`j` 记录原始编号，体现了对问题本质的深刻理解，适合快速上手。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下一些关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何高效计算 \( d_i \)？
    * **分析**：直接按公式计算 \( d_i = \sum_{j=1}^{i-1} [a_j \cdot (j-1) - (n-i) \cdot a_i] \) 会涉及大量重复计算。优质题解通过观察公式结构，发现 \( d_i \) 可以拆分为 \( \sum_{j=1}^{i-1} a_j \cdot (j-1) \)（累加和 \( sum \)）减去 \( (i-1)(n-i) \cdot a_i \)，从而用 \( sum \) 维护前半部分，将每次计算 \( d_i \) 的时间降为 \( O(1) \)。
    * 💡 **学习笔记**：遇到复杂公式时，尝试拆分变量，寻找可维护的中间量（如本题的 \( sum \)），能大幅优化计算效率。

2.  **关键点2**：如何处理删除操作后的索引调整？
    * **分析**：删除一个参赛者后，剩余参赛者的排名会前移（即原第 \( i+1 \) 名变为第 \( i \) 名）。因此，删除操作需要调整当前遍历的索引 \( i \)（`i--`）和总人数 \( n \)（`n--`），确保后续计算基于最新的排名。
    * 💡 **学习笔记**：模拟过程中，每一步操作都要同步更新相关变量（如本题的 \( n \) 和 \( i \)），避免索引错误。

3.  **关键点3**：如何记录原始编号？
    * **分析**：题目要求输出被移除参赛者的原始编号（即他们在初始列表中的位置）。优质题解通过一个独立变量（如 `nowi`、`id` 或 `t`）来记录当前处理的原始编号，确保删除操作不影响原始编号的计数。
    * 💡 **学习笔记**：需要保留原始信息时，用独立变量跟踪是简单有效的方法。

### ✨ 解题技巧总结
<summary_best_practices>
通过对本题及类似问题的分析，我总结了以下一些通用的解题技巧：
</summary_best_practices>
-   **公式拆分与中间量维护**：遇到复杂公式时，尝试拆分出可累加或可维护的中间量（如本题的 \( sum \)），避免重复计算。
-   **变量同步更新**：模拟过程中，每一步操作（如删除）需同步更新相关变量（如 \( n \)、\( i \)），确保后续步骤基于最新状态。
-   **独立跟踪原始信息**：需要保留原始顺序或编号时，用独立变量（如 `id`）跟踪，避免被动态变化的索引干扰。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个优质题解的思路，旨在提供一个清晰且完整的核心实现，重点体现累加和 \( sum \) 的维护和删除操作的索引调整。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    using namespace std;

    int main() {
        int n, k;
        cin >> n >> k;
        long long sum = 0; // 维护累加和 sum = sum_{j=1}^{i-1} a_j*(j-1)
        int original_id = 1; // 记录原始编号

        for (int i = 1; i <= n; ) { // 注意：i 的更新在循环内处理
            int a;
            cin >> a;
            // 计算当前 d_i = sum - (i-1)*(n-i)*a
            if (sum - 1LL * (i - 1) * (n - i) * a < k) {
                cout << original_id << endl; // 输出原始编号
                n--; // 总人数减1
                // 不更新 sum（因为当前 a 被删除，不贡献到后续的 sum）
            } else {
                sum += 1LL * a * (i - 1); // 将当前 a 的贡献加入 sum
                i++; // 处理下一个参赛者
            }
            original_id++; // 原始编号递增（无论是否删除）
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 该代码首先读取输入的 \( n \) 和 \( k \)，然后初始化累加和 \( sum \) 和原始编号计数器 `original_id`。通过循环遍历每个参赛者，计算当前 \( d_i \)：若 \( d_i < k \)，则输出原始编号并调整 \( n \)；否则将当前参赛者的贡献（\( a_i \cdot (i-1) \)）加入 \( sum \)，继续处理下一个参赛者。`original_id` 独立递增，确保记录的是初始顺序的编号。

---
<code_intro_selected>
接下来，我们将逐一剖析筛选出的优质题解中，最能体现核心逻辑的C++实现片段，并点出各自的亮点和关键代码思路。
</code_intro_selected>

**题解一：来源：liangbowen**
* **亮点**：代码简洁，直接通过 `d` 变量维护累加和，用 `nowi` 跟踪原始编号，逻辑清晰。
* **核心代码片段**：
    ```cpp
    int main() {
        int n, k, nowi = 0;
        cin >> n >> k;
        long long d = 0; 
        for (int i = 1; i <= n; i++) {
            nowi++;
            int ai; cin >> ai;
            if (d - 1ll * (i - 1) * (n - i) * ai < k) {
                cout << nowi << endl; 
                n--, i--;
            } else {
                d += 1ll * ai * (i - 1);
            }
        }
        return 0;
    }
    ```
* **代码解读**：
    > 这段代码中，`d` 是累加和 \( sum \)，`nowi` 记录原始编号。循环中，每次读取当前参赛者的评分 `ai`，计算 \( d_i = d - (i-1)(n-i) \cdot ai \)。若 \( d_i < k \)，输出 `nowi`（原始编号），并调整 `n` 和 `i`（`n--` 表示总人数减少，`i--` 确保下次循环处理当前位置的下一个参赛者）；否则将 `ai*(i-1)` 加入 `d`，继续处理下一个参赛者。
* 💡 **学习笔记**：用 `i--` 调整索引是处理动态数组删除的常用技巧，确保后续元素正确前移。

**题解二：来源：Lee666666**
* **亮点**：包含输入优化（`read` 函数），提升了处理大输入时的效率，同时详细注释了关键逻辑。
* **核心代码片段**：
    ```cpp
    int main() {
        n = read();
        k = read();
        for (register int i = 1; i <= n; i++) { 
            tmp = read();
            if (sum - 1LL * (i - 1) * (n - i) * tmp < k) { 
                n--;
                i--;
                printf("%d\n", id);
            } else {
                sum += 1LL * tmp * (i - 1);
            }
            id++;
        }
        return 0;
    }
    ```
* **代码解读**：
    > 这段代码中，`read` 函数快速读取输入，`sum` 维护累加和，`id` 记录原始编号。循环中，若当前 \( d_i < k \)，则调整 `n` 和 `i` 并输出 `id`；否则将 `tmp*(i-1)` 加入 `sum`。`register` 关键字优化循环变量，提升效率。
* 💡 **学习笔记**：输入输出优化（如快速读入函数）在处理大规模数据时非常重要，可避免超时。

**题解三：来源：BADFIVE**
* **亮点**：代码极简，直接抓住核心逻辑，适合快速理解问题本质。
* **核心代码片段**：
    ```cpp
    signed main() {
        int n,k,tmp=0,j=1;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            int a; cin>>a;
            if(tmp-(i-1)*(n-i)*a<k){
                cout<<j<<endl;
                n--,i--;
            } else tmp+=a*(i-1);
            j++;
        }
    }
    ```
* **代码解读**：
    > 这段代码中，`tmp` 是累加和 \( sum \)，`j` 记录原始编号。循环中，若 \( d_i < k \)，输出 `j` 并调整 `n` 和 `i`；否则将 `a*(i-1)` 加入 `tmp`。代码简洁，变量名直观（`tmp` 表示临时累加和），是快速实现的典范。
* 💡 **学习笔记**：简洁的代码往往能更清晰地体现核心逻辑，避免冗余操作。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“参赛者删除过程”的模拟逻辑，我设计了一个8位像素风格的动画演示方案。通过像素方块的移动、颜色变化和音效提示，帮助大家“看”到每一步的操作！
</visualization_intro>

  * **动画演示主题**：`像素排行榜大冒险`

  * **核心演示内容**：参赛者初始排列成一行像素方块（颜色随机，如红色、蓝色、绿色），每个方块顶部显示原始编号（如①、②）。屏幕上方显示当前总人数 \( n \) 和累加和 \( sum \)。每次计算 \( d_i \) 时，当前方块闪烁黄色；若 \( d_i < k \)，方块变为灰色并播放“叮”的音效，随后从队列中消失，后面的方块左移；否则方块变为绿色，继续处理下一个。

  * **设计思路简述**：8位像素风格（如FC游戏画面）营造轻松氛围，颜色变化（黄→灰/绿）直观区分当前状态；音效（“叮”提示删除）强化操作记忆；实时显示 \( n \) 和 \( sum \) 帮助理解变量更新。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕中央显示像素网格，10个像素方块（对应初始 \( n \)）横向排列，每个方块顶部标有原始编号（①~⑩）。
          * 左上角显示“当前人数：\( n \)”和“累加和：\( sum \)”，初始 \( n \) 为输入值，\( sum \) 为0。
          * 控制面板包含“开始”“暂停”“单步”按钮和速度滑块（0.5x~2x）。

    2.  **算法启动**：
          * 点击“开始”，播放8位风格背景音乐（如《超级玛丽》经典旋律）。
          * 第一个方块（原始编号①）闪烁黄色，显示“计算 \( d_1 \)”。

    3.  **核心步骤演示**：
          * **计算 \( d_i \)**：当前方块（如第 \( i \) 个）闪烁黄色，屏幕上方弹出公式 \( d_i = sum - (i-1)(n-i) \cdot a_i \)，并高亮 \( sum \)、\( i \)、\( n \)、\( a_i \) 的当前值。
          * **判断 \( d_i < k \)**：若成立，方块变为灰色，播放“叮”音效，屏幕显示“删除！原始编号：①”；随后该方块消失，后面的方块左移（如②→①，③→②），\( n \) 减1，\( sum \) 不变。
          * **保留 \( d_i \geq k \)**：方块变为绿色，播放“滴答”音效，\( sum \) 增加 \( a_i \cdot (i-1) \)，数值实时更新，继续处理下一个方块。

    4.  **AI自动演示模式**：
          * 点击“AI演示”，算法自动执行，方块按规则删除或保留，学习者可观察完整流程。

    5.  **结束状态**：
          * 当没有更多方块被删除时，播放“胜利”音效（如《超级玛丽》通关音），屏幕显示“删除结束！”，并列出所有被删除的原始编号。

  * **旁白提示**：
      * （计算 \( d_i \) 时）“现在计算第 \( i \) 个参赛者的评分 \( d_i \)，它等于累加和 \( sum \) 减去 \( (i-1)(n-i) \times a_i \)。”
      * （删除时）“这个参赛者的评分 \( d_i \) 小于 \( k \)，被移除！后面的参赛者排名前移。”
      * （保留时）“这个参赛者的评分符合要求，保留！它的贡献被加入累加和 \( sum \)。”

<visualization_conclusion>
通过这样一个融合了像素艺术和复古游戏元素的动画，我们不仅能清晰地看到参赛者删除过程的每一步，还能在轻松有趣的环境中理解累加和 \( sum \) 和索引调整的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考“模拟”算法的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 模拟算法不仅能解决本题，还常用于处理**动态变化的序列操作**（如游戏角色移动、队列任务处理）、**状态逐步更新的问题**（如天气预测、资源分配）、**规则明确的流程复现**（如订单处理、交通信号灯模拟）。关键在于抓住每一步的状态变化，用变量维护关键信息（如本题的 \( sum \) 和 \( n \)）。

  * **练习推荐 (洛谷)**：
    以下是几道洛谷上与本题考察知识点或思维方式相关的题目，建议大家尝试练习：

    1.  **洛谷 P1007** - `独木桥`
          * 🗣️ **推荐理由**：这道题需要模拟士兵在桥上的相遇和转向过程，通过维护士兵的位置和方向变化，锻炼对动态过程的模拟能力。
    2.  **洛谷 P1093** - `奖学金`
          * 🗣️ **推荐理由**：此题需要模拟学生的分数排序和奖学金分配过程，涉及多条件排序和状态更新，适合巩固模拟算法的细节处理。
    3.  **洛谷 P1157** - `组合的输出`
          * 🗣️ **推荐理由**：此题需要模拟组合数的生成过程，通过递归或迭代生成所有可能的组合，是理解“按规则逐步生成”类问题的好练习。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中，作者们分享了许多宝贵的经验。例如，liangbowen提到“通过分解公式找到累加和 \( sum \)，避免了重复计算”，这对我们有重要的启发：
</insights_intro>

> **参考经验 (来自 liangbowen)**：“我在解决这个问题时，发现直接计算每个 \( d_i \) 会重复计算前面的累加部分。后来通过分解公式，发现可以用一个变量维护累加和 \( sum \)，这样每次计算 \( d_i \) 只需 \( O(1) \) 时间，大大优化了效率。”

> **点评**：这位作者的经验非常实用。在编程中，遇到重复计算的问题时，我们可以尝试分解公式，寻找可维护的中间量（如本题的 \( sum \)），从而将时间复杂度从 \( O(n^2) \) 优化到 \( O(n) \)。这是解决类似问题的关键技巧。

-----

<conclusion>
本次关于“Sereja and Contest”的C++解题分析就到这里。希望这份学习指南能帮助大家更好地理解模拟算法和编程技巧。记住，编程能力的提升在于持续学习、勤于思考和勇于实践。下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：157.64秒