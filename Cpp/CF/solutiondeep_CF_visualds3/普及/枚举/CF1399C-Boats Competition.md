# 题目信息

# Boats Competition

## 题目描述

There are $ n $ people who want to participate in a boat competition. The weight of the $ i $ -th participant is $ w_i $ . Only teams consisting of two people can participate in this competition. As an organizer, you think that it's fair to allow only teams with the same total weight.

So, if there are $ k $ teams $ (a_1, b_1) $ , $ (a_2,       b_2) $ , $ \dots $ , $ (a_k, b_k) $ , where $ a_i $ is the weight of the first participant of the $ i $ -th team and $ b_i $ is the weight of the second participant of the $ i $ -th team, then the condition $ a_1 + b_1 = a_2 + b_2 =       \dots = a_k + b_k = s $ , where $ s $ is the total weight of each team, should be satisfied.

Your task is to choose such $ s $ that the number of teams people can create is the maximum possible. Note that each participant can be in no more than one team.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, we can reach the optimal answer for $ s=6 $ . Then the first boat is used by participants $ 1 $ and $ 5 $ and the second boat is used by participants $ 2 $ and $ 4 $ (indices are the same as weights).

In the second test case of the example, we can reach the optimal answer for $ s=12 $ . Then first $ 6 $ participants can form $ 3 $ pairs.

In the third test case of the example, we can reach the optimal answer for $ s=3 $ . The answer is $ 4 $ because we have $ 4 $ participants with weight $ 1 $ and $ 4 $ participants with weight $ 2 $ .

In the fourth test case of the example, we can reach the optimal answer for $ s=4 $ or $ s=6 $ .

In the fifth test case of the example, we can reach the optimal answer for $ s=3 $ . Note that participant with weight $ 3 $ can't use the boat because there is no suitable pair for him in the list.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
8
6 6 6 6 6 6 8 8
8
1 2 2 1 2 1 1 2
3
1 3 3
6
1 1 3 4 2 2```

### 输出

```
2
3
4
1
2```

# AI分析结果



---
# 💡 Kay的C++算法解析：Boats Competition 深入学习指南 💡

<introduction>
今天我们来一起分析“Boats Competition”这道C++编程题。题目要求我们找到一种方式，将n个人的体重组成尽可能多的两人队伍，且每队的体重和相等。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`枚举与双指针（或计数统计）的综合应用`

🗣️ **初步分析**：
解决“Boats Competition”的关键在于枚举所有可能的队伍体重和s，然后对每个s计算能组成的最大队伍数。简单来说，就像“试不同的钥匙开同一把锁”——我们枚举所有可能的“钥匙”（s值），找到能打开最多“锁”（队伍数）的那把。

在本题中，由于每个人的体重w_i最大为50（n≤50），因此s的可能范围是2到100（最小是1+1=2，最大是50+50=100）。枚举所有s值后，如何高效统计每个s对应的队伍数是核心。常见方法有两种：
- **双指针法**：将体重排序后，用左右指针从两端向中间移动，统计和为s的对数（如Tenshi和wmy_goes_to_thu的题解）。
- **计数统计法**：用桶记录每个体重的出现次数，直接计算能组成s的对数（如Werner_Yin的题解）。

核心算法流程（以双指针法为例）：
1. 对体重数组排序。
2. 枚举每个可能的s（2到100）。
3. 对每个s，用左指针l=1、右指针r=n，若w[l]+w[r]==s，则组成队伍（l右移，r左移），否则调整指针位置（和小则l右移，和大则r左移）。
4. 记录所有s对应的最大队伍数。

可视化设计思路：采用8位像素风格，用不同颜色的方块表示体重值，排序后水平排列。枚举s时，用闪烁的文字显示当前s值；双指针l和r用箭头标记，移动时伴随“滴答”音效；当组成队伍时，对应的两个方块消失（或变灰），并播放“叮”的音效。最终展示最大队伍数的s值，用金色高亮。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑简洁、实现高效被选为优质参考（评分≥4星）。
</eval_intro>

**题解一：Tenshi（尺取法/双指针）**
* **点评**：此题解思路清晰，利用排序和双指针法高效统计每个s的队伍数。代码中通过`sort`排序后，枚举s并移动指针，逻辑直白。变量名`val`（体重数组）、`s`（左指针）、`t`（右指针）含义明确。算法时间复杂度为O(T*100*n)（n≤50），非常高效。亮点在于双指针的移动策略，确保每个元素仅被使用一次，避免重复计数。

**题解二：wmy_goes_to_thu（双指针法）**
* **点评**：此题解代码极为简洁，排序后直接枚举s，用双指针l和r快速统计和为s的对数。核心逻辑仅用一个循环完成，代码可读性高。变量名`l`、`r`、`anss`（当前s的队伍数）直观。算法优化了枚举范围（s从2到2*n），减少不必要的计算。实践价值高，适合竞赛中快速实现。

**题解三：Werner_Yin（桶计数法）**
* **点评**：此题解利用桶数组统计体重出现次数，枚举s后直接计算能组成的对数。逻辑巧妙，避免了双指针的移动操作。例如，当s为偶数时，统计`tong[s/2]/2`（相同体重配对）；奇数时统计`min(tong[i], tong[s-i])`（不同体重配对）。代码结构清晰，变量名`tong`（桶数组）、`res`（当前s的队伍数）易于理解。适用于对双指针不熟悉的学习者。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼出核心思考方向：
</difficulty_intro>

1.  **关键点1：如何枚举所有可能的s值？**
    * **分析**：由于w_i≤50，s的可能范围是2到100（最小1+1，最大50+50）。优质题解通常直接枚举该范围内的所有s值（如Tenshi枚举`mina+1`到`maxa*2`，wmy_goes_to_thu枚举2到2*n），确保覆盖所有可能。
    * 💡 **学习笔记**：枚举范围由数据范围决定，本题中w_i的小范围是枚举可行的关键。

2.  **关键点2：如何高效统计每个s的队伍数？**
    * **分析**：双指针法（排序后移动指针）和桶计数法（统计频率后计算）是两种主流方法。双指针法通过排序后“两端向中间”移动，确保每个元素仅用一次；桶计数法则通过频率直接计算，避免重复操作。例如，双指针法中，当w[l]+w[r]==s时，l右移、r左移，即这两个元素已被配对。
    * 💡 **学习笔记**：排序是双指针法的前提，它让元素有序，便于指针移动时调整和的大小。

3.  **关键点3：如何避免重复计数？**
    * **分析**：每个元素只能在一个队伍中出现。双指针法通过移动指针自然避免重复（配对后指针跳过已用元素）；桶计数法则通过减少对应体重的频率（如`tong[i]--`）来实现。例如，桶计数法中，若i和s-i配对，则`tong[i]`和`tong[s-i]`各减1，确保后续不会重复使用。
    * 💡 **学习笔记**：“消耗”已配对的元素是避免重复的核心，无论是指针移动还是频率减少，本质都是标记元素已被使用。

### ✨ 解题技巧总结
<summary_best_practices>
-   **问题分解**：将大问题拆解为“枚举s”和“统计s对应的队伍数”两部分，分别解决。
-   **排序预处理**：排序后数组有序，便于双指针等贪心策略的应用。
-   **边界处理**：注意s为偶数时（如s=4，需两个2配对）和奇数时（如s=5，需1和4配对）的不同统计方式。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解（双指针法）的通用核心实现，逻辑清晰且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Tenshi和wmy_goes_to_thu的双指针思路，排序后枚举s，用双指针统计队伍数，代码简洁高效。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            vector<int> w(n);
            for (int i = 0; i < n; ++i) cin >> w[i];
            sort(w.begin(), w.end());
            int max_teams = 0;
            // 枚举所有可能的s值（2到2*最大体重）
            for (int s = 2; s <= 2 * w.back(); ++s) {
                int l = 0, r = n - 1, teams = 0;
                while (l < r) {
                    int sum = w[l] + w[r];
                    if (sum == s) {
                        teams++;
                        l++;
                        r--;
                    } else if (sum < s) {
                        l++;
                    } else {
                        r--;
                    }
                }
                max_teams = max(max_teams, teams);
            }
            cout << max_teams << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入并排序体重数组。然后枚举所有可能的s（从2到最大体重的两倍）。对每个s，用左右指针l和r从数组两端向中间移动：若和为s则组成队伍（指针移动），和过小则l右移，和过大则r左移。最终记录最大队伍数并输出。

---
<code_intro_selected>
接下来，剖析优质题解的核心代码片段，理解其亮点和思路。
</code_intro_selected>

**题解一：Tenshi（尺取法）**
* **亮点**：明确处理n=1的边界情况，枚举s的范围优化为`mina+1`到`maxa*2`，减少无效枚举。
* **核心代码片段**：
    ```cpp
    for(k=mina+1;k<=maxa*2;k++){
        int s=1,t=n;
        rec=0;
        while (1) {
            while(val[s]+val[t]==k && s<t){
                s++,t--;
                rec++;
            }
            while(val[s]+val[t]<k && s<t){
                s++;
            }
            while(val[s]+val[t]>k && s<t){
                t--;
            }
            if(s>=t){
                ans=max(ans,rec);
                break;
            }
        }
    }
    ```
* **代码解读**：
    > 这段代码枚举s值（k），用s（左指针）和t（右指针）遍历排序后的数组。当和为k时，指针移动并计数（rec++）；和过小则左指针右移，和过大则右指针左移。当指针相遇时，记录当前s的最大队伍数（ans）。
* 💡 **学习笔记**：尺取法（双指针）通过调整指针位置，高效统计符合条件的对数，避免了暴力枚举所有数对的O(n²)复杂度。

**题解二：wmy_goes_to_thu（双指针法）**
* **亮点**：代码极简，直接枚举s到2*n（因w_i≤n），双指针逻辑清晰。
* **核心代码片段**：
    ```cpp
    for(int s=2;s<=mx;s++){
        int l=1,r=n,anss=0;
        while(l<r){
            if(w[l]+w[r]>s) r--;
            else if(w[l]+w[r]<s) l++;
            else anss++,l++,r--;
        }
        ans=max(ans,anss);
    }
    ```
* **代码解读**：
    > 枚举s值后，左指针l从1开始，右指针r从n开始。若和大于s，r左移（减小和）；若和小于s，l右移（增大和）；若和等于s，计数并移动指针（避免重复使用元素）。
* 💡 **学习笔记**：双指针的移动方向由当前和与s的大小关系决定，确保每一步都在逼近目标和。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解双指针法的工作过程，我们设计一个“像素船配对”的8位复古动画，模拟排序后的体重数组和双指针移动过程。
</visualization_intro>

  * **动画演示主题**：`像素船配对大挑战`
  * **核心演示内容**：展示排序后的体重数组（如`[1,2,3,4,5]`），枚举s值（如s=6）时，左右指针从两端移动，找到和为s的数对（如1+5=6，2+4=6），最终统计队伍数。
  * **设计思路简述**：8位像素风格（红、绿、蓝等低饱和度颜色）模拟FC游戏界面，用不同颜色的方块表示体重值，指针用箭头标记。关键操作（指针移动、配对成功）伴随音效，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕顶部显示“Boats Competition”标题，下方是一个像素网格，水平排列排序后的体重方块（如黄色代表1，绿色代表2等）。
          * 控制面板包含“开始/暂停”、“单步”、“重置”按钮，以及速度滑块（1x到5x）。
          * 播放8位风格的轻快背景音乐（如《超级玛丽》的简单变奏）。

    2.  **枚举s值**：
          * 屏幕左侧显示当前枚举的s值（如s=6），用闪烁的文字提示“当前尝试s=6”。

    3.  **双指针移动**：
          * 左指针（红色箭头）指向最左方块（1），右指针（蓝色箭头）指向最右方块（5）。
          * 计算和：1+5=6，等于s，配对成功！两个方块变灰（表示已使用），指针分别右移和左移（箭头移动），伴随“叮”的音效。
          * 左指针指向2，右指针指向4，和为6，再次配对成功，重复上述动画。

    4.  **统计队伍数**：
          * 屏幕右侧显示当前s的队伍数（如2），最终找到最大队伍数时，用金色闪光和“胜利”音效（如《魂斗罗》的得分音）提示。

    5.  **交互控制**：
          * 单步执行：点击“单步”按钮，逐次展示指针移动和配对过程。
          * 自动播放：选择速度后，算法自动枚举所有s值，展示完整过程。

  * **旁白提示**：
      * （配对成功时）“看！1和5组成了一队，他们的和正好是6！”
      * （指针移动时）“和太小了，左指针右移；和太大了，右指针左移。”
      * （展示结果时）“最终，s=6时能组成2队，这是最多的！”

<visualization_conclusion>
通过这样的动画，我们能直观看到双指针如何高效找到最多队伍数，理解枚举s和指针移动的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的枚举+双指针/计数法后，可以尝试以下拓展练习，巩固算法应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 枚举可能的目标值（如和、差、积），结合双指针或计数法统计符合条件的对数。
      * 适用于“寻找最多配对”类问题（如两数之和、三数之和的变形）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1102 A-B数对** 
          * 🗣️ **推荐理由**：枚举A-B=C，统计C的出现次数，与本题枚举s统计队伍数的思路类似。
    2.  **洛谷 P1219 八皇后** 
          * 🗣️ **推荐理由**：枚举每行的皇后位置，结合剪枝策略，锻炼枚举与条件判断能力。
    3.  **洛谷 P1678 烦恼的高考志愿** 
          * 🗣️ **推荐理由**：排序后用双指针匹配分数，与本题双指针法思想一致。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如Tenshi提到“特判n=1的情况”，这提醒我们注意边界条件。
</insights_intro>

> **参考经验 (来自 Tenshi)**：“记得特判n=1的情况，此时无法组成任何队伍。”
>
> **点评**：边界条件（如n=1、数组全为同一元素）是编程中易出错的点。在本题中，n=1时直接输出0，避免后续枚举的无效计算。这提醒我们，编码前需先考虑所有可能的输入情况。

-----

<conclusion>
本次关于“Boats Competition”的C++解题分析就到这里。希望这份指南能帮助大家理解枚举与双指针的核心思想，掌握高效解题技巧。记住，多练习、多思考，编程能力会稳步提升！下次见~💪
</conclusion>

---
处理用时：123.72秒