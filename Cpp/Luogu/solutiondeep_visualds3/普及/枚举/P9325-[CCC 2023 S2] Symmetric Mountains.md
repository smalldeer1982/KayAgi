# 题目信息

# [CCC 2023 S2] Symmetric Mountains

## 题目描述

Rebecca is a tour guide and is trying to market the Rocky Mountains for her magazine. She recently took a beautiful picture consisting of $N$ mountains where the $i\text{-th}$ mountain from the left has a height $h_i$. She will crop this picture for her magazine, by possibly removing some mountains from the left side of the picture and possibly removing some mountains from the right side of the picture. That is, a crop consists of consecutive mountains starting from the $l\text{-th}$ to the $r\text{-th}$ mountain where $l \leq r$. To please her magazine readers, Rebecca will try to find the most symmetric crop.

We will measure the $asymmetric\ value$ of a crop as the sum of the absolute difference for every pair of mountains equidistant from the midpoint of the crop. To help understand that definition, note that the absolute value of $a$ number $v$, written as $|v|$, is the non-negative value of v: for example $\lvert -6 \rvert = 6$ and $|14| = 14$. The asymmetric value of a crop is the sum of all $|h_{l+i} - h_{r-i}|$ for $0 \leq i \leq \frac{r-l}{2}$. To put that formula in a different way, we pair up the mountains working from the outside in toward the centre, calculate the absolute difference in height of each of these pairs, and sum them up.

Because Rebecca does not know how wide the picture needs to be, for all possible crop lengths, find the asymmetric value of the most symmetric crop (the crop with the minimum asymmetric value).

## 说明/提示

Explanation of Output for Sample Input $1$:

We will show why the fifth value from the left is $2$.Let us try to compute all the asymmetric values of crops with length $5$.

The height of the mountains in the first crop is $[3, 1, 4, 1, 5]$. The asymmetric value of this crop is $|3 - 5| + |1 - 1| + |4 - 4| = 2$.

The height of the mountains in the second crop is $[1, 4, 1, 5, 9]$. The asymmetric value of this crop is $|1 - 9| + |4 - 5| + |1 - 1| = 9$.

The height of the mountains in the last crop is $[4, 1, 5, 9, 2]$. The asymmetric value of this crop is $|4 - 2| + |1 - 9| + |5 - 5| = 10$.

Hence, the most symmetric crop of length $5$ is $2$.

Explanation of Output for Sample Input $2$:

This sample satisfies the second subtask. Note that the only crop of length $4$ is $[1, 3, 5, 6]$ which has asymmetric value of $|1 - 6| + |3 - 5| = 7$.

**本题采用捆绑测试**：

- Subtask 1（5 points）：$1\leq N \leq 300$，$0\leq h_i \leq 10^5$。

- Subtask 2（5 points）：$1 \leq N \leq 5000$，$0 \leq h_i \leq 10^5$，保证山的高度从左到右单调不减。

- Subtask 3（5 points）：$1\leq N\leq 5000$，$0 \leq h_i \leq 10^5$。

## 样例 #1

### 输入

```
7
3 1 4 1 5 9 2```

### 输出

```
0 2 0 5 2 10 10```

## 样例 #2

### 输入

```
4
1 3 5 6```

### 输出

```
0 1 3 7```

# AI分析结果



---
# 💡 Kay的C++算法解析：Symmetric Mountains 深入学习指南 💡

<introduction>
今天我们来一起分析“Symmetric Mountains”这道C++编程题。这道题需要找到不同长度的连续山脉中最对称的部分（即不对称值最小），本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（DP）与中心扩展法

🗣️ **初步分析**：
解决“Symmetric Mountains”的关键在于高效计算所有可能区间的不对称值。动态规划（DP）的核心思想是“用子问题的解推导原问题的解”，就像搭积木一样，小积木（子区间）的结果可以组合成大积木（大区间）的结果。在本题中，区间[i,j]的不对称值等于其内部更小的区间[i+1,j-1]的不对称值，加上两端山高的绝对差（即`|h[i]-h[j]|`）。这种递推关系让我们避免了重复计算，将时间复杂度从暴力的O(n³)优化到O(n²)。

- **题解思路对比**：大部分题解采用两种思路：一种是区间DP（如玄学OIER荷蒻的题解），直接定义`dp[i][j]`为区间[i,j]的不对称值；另一种是中心扩展法（如ZepX_D的题解），枚举每个可能的中心（奇数长度以单个点为中心，偶数长度以两个相邻点为中心），向两边扩展计算不对称值。两种方法本质都是利用子问题结果，时间复杂度均为O(n²)。
- **核心算法流程**：以区间DP为例，先计算长度为1（不对称值为0）和长度为2（直接计算两端差）的区间，再递推计算更长的区间。例如，长度为3的区间[i,j]的不对称值等于长度为1的区间[i+1,j-1]的不对称值（0）加上`|h[i]-h[j]|`。
- **可视化设计**：计划采用8位像素风动画，用不同颜色的像素块表示山脉高度。动画中，每个区间的扩展过程会被动态展示（如红色标记当前处理的中心，蓝色箭头表示向两边扩展的方向），关键步骤（如计算绝对差、累加不对称值）会伴随“叮”的音效，帮助学习者直观看到子问题如何组合成大问题的解。

---

## 2. 精选优质题解参考

<eval_intro>
通过对题解的思路清晰度、代码规范性和算法有效性评估，以下题解因逻辑简洁、实现高效被选为优质参考：
</eval_intro>

**题解一：ZepX_D（赞11）**
* **点评**：此题解采用中心扩展法，思路非常直观。作者枚举每个可能的中心（奇数长度以单一点为中心，偶数长度以相邻两点为中心），然后向两边扩展，逐步计算不对称值。代码中通过`l`和`r`指针的移动模拟扩展过程，并用`ans`数组实时记录各长度的最小不对称值。代码结构清晰（如`memset(ans,0x3f,sizeof(ans))`初始化最小值），边界处理严谨（如`while(l && r <= n)`避免越界），是理解中心扩展法的优秀示例。

**题解二：玄学OIER荷蒻（赞9）**
* **点评**：此题解明确使用区间DP，状态定义`dp[i][j]`直接对应区间[i,j]的不对称值，状态转移方程`dp[i][j] = dp[i+1][j-1] + |h[i]-h[j]|`简洁明了。代码通过双重循环枚举区间长度和起点，逐步填充DP表，最后取各长度的最小值。代码非常简短（去除注释后仅426B），但关键逻辑完整，是区间DP的典型实现。

**题解三：Jorisy（赞4）**
* **点评**：此题解采用记忆化搜索优化暴力枚举。通过`f[l][r]`数组记录已计算的区间结果，避免重复计算。代码中`d(l,r)`函数递归计算区间[l,r]的不对称值，若已计算则直接返回，否则递归求解。这种方法将暴力的O(n³)优化到O(n²)，适合理解记忆化搜索与动态规划的联系。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点，结合优质题解的共性，提炼出核心思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何避免暴力枚举的高复杂度？**
    * **分析**：暴力枚举所有区间并计算不对称值的时间复杂度为O(n³)（枚举长度O(n)、枚举区间O(n)、计算不对称值O(n)），对于n=5000会超时。优质题解通过动态规划或中心扩展法，利用子问题结果（如区间[i+1,j-1]的不对称值）推导大区间的结果，将计算不对称值的步骤优化为O(1)，总时间复杂度降为O(n²)。
    * 💡 **学习笔记**：遇到需要重复计算子问题的题目时，动态规划或记忆化搜索是常用的优化手段。

2.  **关键点2：如何处理奇偶长度的区间？**
    * **分析**：奇数长度的区间中心是一个点（如长度5的中心是第3个元素），偶数长度的区间中心是两个相邻点（如长度4的中心是第2和第3个元素）。优质题解通过分别枚举奇数和偶数的中心（如ZepX_D的题解中，先处理奇数中心`i`，再处理偶数中心`i`和`i+1`），确保所有可能的区间都被覆盖。
    * 💡 **学习笔记**：奇偶情况的区分是解决对称问题的常见技巧，需注意边界条件（如扩展时是否越界）。

3.  **关键点3：如何高效记录各长度的最小值？**
    * **分析**：需要为每个长度维护当前的最小不对称值。优质题解通常初始化一个`ans`数组（如`memset(ans,0x3f,sizeof(ans))`），然后在计算每个区间时更新对应长度的最小值（如`ans[r-l+1] = min(ans[r-l+1], s)`）。
    * 💡 **学习笔记**：结果数组的初始化和动态更新是记录最优解的关键步骤。

### ✨ 解题技巧总结
- **问题分解**：将大区间的不对称值分解为子区间的不对称值加两端差，利用动态规划或中心扩展法复用子问题结果。
- **奇偶分离**：分别处理奇数和偶数长度的区间，确保所有可能的对称中心被覆盖。
- **结果记录**：用数组实时记录各长度的最小值，避免重复遍历所有区间。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合了区间DP和中心扩展法的通用核心实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了中心扩展法的直观性和区间DP的高效性，通过枚举每个中心并向两边扩展，计算各长度的最小不对称值。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    #include <algorithm>
    using namespace std;

    const int MAXN = 5005;
    int h[MAXN], ans[MAXN];

    int main() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> h[i];
        memset(ans, 0x3f, sizeof(ans));
        ans[1] = 0; // 长度为1的不对称值为0

        // 处理奇数长度的中心（单一点）
        for (int i = 1; i <= n; ++i) {
            int l = i, r = i, s = 0;
            while (l >= 1 && r <= n) {
                ans[r - l + 1] = min(ans[r - l + 1], s);
                l--; r++;
                s += abs(h[l] - h[r]); // 扩展后加上新两端的差
            }
        }

        // 处理偶数长度的中心（两个相邻点）
        for (int i = 1; i < n; ++i) {
            int l = i, r = i + 1, s = abs(h[l] - h[r]);
            ans[2] = min(ans[2], s); // 长度为2的初始值
            while (l >= 1 && r <= n) {
                ans[r - l + 1] = min(ans[r - l + 1], s);
                l--; r++;
                s += abs(h[l] - h[r]); // 扩展后加上新两端的差
            }
        }

        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << " ";
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先初始化`ans`数组为极大值，长度为1的不对称值直接设为0。然后分别枚举奇数长度的中心（单一点）和偶数长度的中心（相邻两点），向两边扩展计算不对称值，并更新各长度的最小值。扩展时，`s`变量累加新加入的两端山高的绝对差，确保每次计算都是O(1)。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点和关键逻辑。
</code_intro_selected>

**题解一：ZepX_D（中心扩展法）**
* **亮点**：通过枚举中心并向两边扩展，直观覆盖所有可能的区间，代码简洁易懂。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; i++) {
        s = 0, l = r = i;
        while (l && r <= n) {
            ans[r - l + 1] = min(ans[r - l + 1], s);
            l--, r++, s += abs(h[r] - h[l]);
        }
        s = abs(h[i + 1] - h[i]), l = i, r = i + 1;
        while (l && r <= n) {
            ans[r - l + 1] = min(ans[r - l + 1], s);
            l--, r++, s += abs(h[r] - h[l]);
        }
    }
    ```
* **代码解读**：这段代码分两部分处理奇数和偶数长度的区间。第一部分以`i`为中心（奇数长度），初始`l=r=i`，`s=0`（长度为1的不对称值），然后每次扩展`l--, r++`，累加新两端的差到`s`，并更新对应长度的最小值。第二部分以`i`和`i+1`为中心（偶数长度），初始`s`为两端的差（长度为2的不对称值），同样扩展并更新。
* 💡 **学习笔记**：中心扩展法通过“从中心出发，逐步扩大”的方式，自然覆盖所有可能的区间，是解决对称问题的经典思路。

**题解二：玄学OIER荷蒻（区间DP）**
* **亮点**：状态定义直接，转移方程清晰，代码简短高效。
* **核心代码片段**：
    ```cpp
    for (register int j = 2; j <= n; j++) {
        minn[j] = 250000000;
        for (register int i = 1; i <= n - j + 1; i++) {
            dp[i][i + j - 1] = dp[i + 1][i + j - 2] + abs(h[i] - h[i + j - 1]);
            minn[j] = min(minn[j], dp[i][i + j - 1]);
        }
    }
    ```
* **代码解读**：外层循环枚举区间长度`j`（从2开始），内层循环枚举区间起点`i`，终点为`i+j-1`。`dp[i][i+j-1]`表示区间[i, i+j-1]的不对称值，等于子区间[i+1, i+j-2]的不对称值（`dp[i+1][i+j-2]`）加上两端的绝对差。每次计算后更新长度为`j`的最小值`minn[j]`。
* 💡 **学习笔记**：区间DP的关键是正确定义状态和转移方程，确保子问题先于父问题被计算。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解中心扩展法的工作流程，我们设计一个8位像素风格的动画，让学习者“看”到算法如何从中心扩展并计算不对称值。
</visualization_intro>

  * **动画演示主题**：`像素山脉探险家`（结合复古游戏元素）

  * **核心演示内容**：以ZepX_D的中心扩展法为基础，展示如何从每个中心（红色标记）向左右扩展（蓝色箭头），每次扩展时计算新两端的山高差（显示绝对值），并累加到总不对称值（顶部文字显示）。同时，不同长度的区间用不同颜色标记，最终找到各长度的最小不对称值。

  * **设计思路简述**：采用8位像素风（如FC游戏的简洁色彩）营造轻松氛围；扩展时的“叮”音效（如硬币收集声）强化操作记忆；每完成一个长度的最小不对称值计算，播放“过关”音效（如短笛声），增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕上方显示“像素山脉”标题，下方是一个像素网格（每个格子代表一座山，高度用垂直堆叠的像素块表示，如高度3对应3个绿色块）。
        - 控制面板包含“开始/暂停”、“单步”、“重置”按钮，以及速度滑块（1-5级，1最慢）。
        - 播放8位风格的轻快背景音乐（如《超级马里奥》的经典旋律变奏）。

    2.  **奇数长度扩展演示**：
        - 选择中心`i=3`（红色像素箭头标记），初始区间为[3,3]（长度1，不对称值0，顶部文字显示“长度1：0”）。
        - 点击“单步”，`l`左移至2，`r`右移至4，计算`|h[2]-h[4]|`（如h[2]=1，h[4]=1，差为0），累加到`s`（当前s=0），区间变为[2,4]（长度3，顶部文字更新“长度3：0”）。
        - 再次单步，`l=1`，`r=5`，计算`|h[1]-h[5]|`（如h[1]=3，h[5]=5，差为2），s=0+2=2，区间变为[1,5]（长度5，顶部文字“长度5：2”）。

    3.  **偶数长度扩展演示**：
        - 选择中心`i=2`和`i+1=3`（黄色像素箭头标记），初始区间为[2,3]（长度2，计算`|h[2]-h[3]|=|1-4|=3`，顶部文字“长度2：3”）。
        - 单步扩展，`l=1`，`r=4`，计算`|h[1]-h[4]|=|3-1|=2`，s=3+2=5，区间变为[1,4]（长度4，顶部文字“长度4：5”）。

    4.  **结果高亮与音效**：
        - 当所有中心扩展完成后，顶部显示各长度的最小不对称值（如样例1的输出“0 2 0 5 2 10 10”），对应长度的区间用金色边框高亮。
        - 每更新一个长度的最小值，播放“叮”音效；全部完成后播放“胜利”音效（如升调短旋律）。

<visualization_conclusion>
通过这样的像素动画，学习者可以直观看到中心扩展的过程，理解子问题如何组合成大问题的解，以及各长度最小值是如何被逐步更新的。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题的动态规划和中心扩展法后，我们可以将思路迁移到更多对称或区间优化问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 动态规划可用于解决“子问题重叠”的优化问题（如最长回文子串、石子合并）。
    - 中心扩展法适用于“对称结构”的问题（如回文串判断、最小区间覆盖）。
    - 结果数组的动态更新是记录多维度最优解的常用方法（如不同长度、不同状态的最小值）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1220 关路灯**：考察区间DP的应用，需要计算关闭路灯的最小功耗，与本题的区间递推思路类似。
    * 🗣️ **推荐理由**：这道题是区间DP的经典应用，能帮助你巩固“子问题组合”的思维。
    2.  **洛谷 P1880 石子合并**：同样使用区间DP，需要计算合并石子的最小代价，与本题的递推结构相似。
    * 🗣️ **推荐理由**：此题在区间DP的基础上增加了环形处理，是思维拓展的好练习。
    3.  **洛谷 P5162 WD与积木**：涉及对称结构的最优化问题，中心扩展法是关键思路。
    * 🗣️ **推荐理由**：此题将对称结构与三维空间结合，能强化对中心扩展法的理解。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试中的经验，这些经验对我们避免常见错误很有帮助：
</insights_intro>

> **参考经验 (来自 0x282e202e2029)**：“在编写记忆化搜索时，一开始没有使用`vis`数组记录已计算的区间，导致重复计算TLE。后来加上`vis`数组后，时间复杂度降为O(n²)，顺利AC。”

> **点评**：这位作者的经验提醒我们，记忆化搜索或动态规划中，记录已计算的子问题结果是避免重复计算、降低时间复杂度的关键。在类似问题中，一定要为子问题设计“记忆数组”（如`vis`或`dp`表），确保每个子问题只计算一次。

-----

<conclusion>
本次关于“Symmetric Mountains”的C++解题分析就到这里。希望这份学习指南能帮助大家理解动态规划和中心扩展法的核心思想，掌握高效解决对称问题的技巧。记住，编程能力的提升需要多思考、多练习，下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：167.99秒