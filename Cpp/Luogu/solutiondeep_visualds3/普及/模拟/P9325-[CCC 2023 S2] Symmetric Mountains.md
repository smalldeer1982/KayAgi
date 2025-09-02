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
今天我们来一起分析“Symmetric Mountains”这道C++编程题。本指南将帮助大家梳理题目核心，理解如何用动态规划或中心扩展法高效求解，并掌握关键解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`动态规划（区间DP）与中心扩展法`

🗣️ **初步分析**：
解决“Symmetric Mountains”的关键在于高效计算所有可能长度的连续子数组的最小不对称值。不对称值的定义是子数组中对称位置元素差的绝对值之和（例如子数组`[l, r]`的不对称值为`|h[l]-h[r]| + |h[l+1]-h[r-1]| + ...`）。

- **暴力思路**：枚举所有长度和子数组，计算不对称值，复杂度为$O(n^3)$，无法通过大测试用例。
- **优化思路**：利用动态规划（区间DP）或中心扩展法将复杂度降至$O(n^2)$：
  - **区间DP**：定义`dp[l][r]`为子数组`[l, r]`的不对称值，状态转移方程为`dp[l][r] = dp[l+1][r-1] + |h[l]-h[r]|`（利用子问题结果避免重复计算）。
  - **中心扩展法**：枚举每个中心点（奇数长度中心为单个元素，偶数长度为两个相邻元素），向两边扩展计算不对称值，同时更新各长度的最小值。

**核心算法可视化设计**：用8位像素风格动画演示中心扩展过程。例如，奇数长度的中心用黄色方块标记，向左右扩展时，左右对称位置的方块（如左1和右1）闪烁并显示差值，累加的不对称值用数字动态更新。动画支持单步/自动播放，同步高亮当前计算的`l`和`r`对应的代码行。

---

## 2. 精选优质题解参考

<eval_intro>
通过对题解的思路清晰度、代码规范性、算法效率等维度评估，以下3道题解（评分≥4星）值得重点学习：
</eval_intro>

**题解一：作者ZepX_D（赞：11）**
* **点评**：此题解采用中心扩展法，思路简洁直观。通过枚举每个可能的中心点（奇数和偶数长度），向两边扩展计算不对称值，并实时更新各长度的最小值。代码结构清晰，变量命名易懂（如`l`、`r`表示当前扩展的左右端点），边界处理严谨（通过`while(l && r <= n)`确保不越界）。时间复杂度为$O(n^2)$，实际运行效率高，是竞赛中常用的优化思路。

**题解二：作者玄学OIER荷蒻（赞：9）**
* **点评**：此题解使用区间DP，状态定义`dp[i][j]`表示子数组`[i, j]`的不对称值，状态转移方程直接（`dp[i][j] = dp[i+1][j-1] + |h[i]-h[j]|`）。代码简洁（去除注释后仅426B），变量命名规范（如`minn`记录各长度的最小值），适合学习区间DP的基础实现。

**题解三：作者GeXiaoWei（赞：0）**
* **点评**：此题解同样采用区间DP，代码结构工整。通过双重循环枚举长度和子数组起点，利用`dp[l][r]`的递推关系计算不对称值，并维护各长度的最小值。代码逻辑直白，边界条件处理明确（如`l+len-1 <=n`确保子数组不越界），适合初学者理解区间DP的流程。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决此题时，我们需要突破以下核心难点：
</difficulty_intro>

1.  **关键点1：如何避免暴力枚举的高复杂度？**
    * **分析**：暴力枚举所有子数组并计算不对称值的复杂度为$O(n^3)$，无法处理$n=5000$的情况。优化的关键是利用子问题的重叠性，通过动态规划或中心扩展法避免重复计算。例如，区间DP中`dp[l][r]`的值可以通过`dp[l+1][r-1]`直接推导，无需重新计算内部对称对的和。
    * 💡 **学习笔记**：动态规划的核心是利用子问题的解，避免重复计算。观察问题是否具有“最优子结构”和“重叠子问题”是关键。

2.  **关键点2：如何处理奇偶长度的子数组？**
    * **分析**：奇数长度的子数组中心是单个元素（如长度5的中心是第3个元素），偶数长度的中心是两个相邻元素（如长度4的中心是第2和第3个元素）。中心扩展法需要分别处理这两种情况，枚举所有可能的中心点，向两边扩展计算不对称值。
    * 💡 **学习笔记**：奇偶长度的处理是此类对称问题的常见细节，需分别枚举中心点并设计扩展逻辑。

3.  **关键点3：如何高效维护各长度的最小不对称值？**
    * **分析**：对于每个子数组，计算其不对称值后，需要更新对应长度的最小值。例如，中心扩展法中，每扩展一步得到一个长度的子数组，直接比较并更新该长度的最小值。
    * 💡 **学习笔记**：维护最小值时，初始值应设为极大值（如`0x3f3f3f3f`），确保所有可能的子数组都能正确比较。

### ✨ 解题技巧总结
- **问题分解**：将大问题（所有长度的最小不对称值）分解为子问题（每个子数组的不对称值），利用动态规划或中心扩展法解决子问题。
- **状态定义**：区间DP中，状态`dp[l][r]`应直接对应子数组`[l, r]`的不对称值，确保状态转移的简洁性。
- **边界处理**：扩展或枚举子数组时，需检查左右端点是否越界（如`l >=1`且`r <=n`），避免数组越界错误。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，采用区间DP方法，代码简洁且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了区间DP题解的思路，通过递推计算每个子数组的不对称值，并维护各长度的最小值。代码结构清晰，适合学习区间DP的基础应用。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 5010;
    int h[N], dp[N][N], minn[N];

    int main() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> h[i];
        memset(minn, 0x3f, sizeof(minn));
        minn[1] = 0; // 长度为1的不对称值为0

        for (int len = 2; len <= n; ++len) {
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                dp[l][r] = dp[l + 1][r - 1] + abs(h[l] - h[r]);
                minn[len] = min(minn[len], dp[l][r]);
            }
        }

        for (int i = 1; i <= n; ++i) cout << minn[i] << ' ';
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取输入，初始化`minn`数组（记录各长度的最小不对称值）。对于每个长度`len`（从2到n），枚举所有可能的左端点`l`，计算右端点`r`，利用`dp[l+1][r-1]`的值递推得到`dp[l][r]`（当前子数组的不对称值），并更新`minn[len]`的最小值。最后输出各长度的最小不对称值。

---
<code_intro_selected>
接下来，分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者ZepX_D（中心扩展法）**
* **亮点**：通过枚举中心点向两边扩展，避免了区间DP的二维数组存储，空间复杂度更低。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; i++) {
        s = 0, l = r = i;
        while (l && r <= n) {
            ans[r - l + 1] = min(ans[r - l + 1], s);
            l--, r++, s += abs(h[r] - h[l]);
        }
        s = abs(h[i+1] - h[i]), l = i, r = i + 1;
        while (l && r <= n) {
            ans[r - l + 1] = min(ans[r - l + 1], s);
            l--, r++, s += abs(h[r] - h[l]);
        }
    }
    ```
* **代码解读**：
    外层循环枚举每个中心点`i`（奇数长度）和`i`与`i+1`（偶数长度）。对于奇数长度，初始`l=r=i`（中心为`i`），扩展时`l--, r++`，累加`h[r]-h[l]`的绝对值到`s`（当前不对称值），并更新对应长度的最小值。偶数长度类似，初始`l=i, r=i+1`，累加差值。
* 💡 **学习笔记**：中心扩展法通过“从中心出发，逐步扩大”的方式，直接覆盖所有可能的子数组，逻辑更直观，适合处理对称问题。

**题解二：作者玄学OIER荷蒻（区间DP）**
* **亮点**：代码简洁，利用区间DP的状态转移方程直接递推，时间复杂度$O(n^2)$。
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
* **代码解读**：
    外层循环枚举长度`j`（从2到n），内层循环枚举左端点`i`，计算右端点`i+j-1`。`dp[i][i+j-1]`由更小的子区间`dp[i+1][i+j-2]`递推而来，同时更新`minn[j]`（长度为`j`的最小不对称值）。
* 💡 **学习笔记**：区间DP的关键是按长度从小到大枚举，确保计算大区间时，其内部的子区间已计算完成。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解中心扩展法的执行过程，我们设计一个8位像素风格的动画，模拟“像素山”的对称扩展过程。
</visualization_intro>

  * **动画演示主题**：`像素山的对称探险`

  * **核心演示内容**：展示以某个中心点（如第3座山）为中心，向左右扩展时，每对对称山的高度差如何累加为不对称值，并记录各长度的最小值。

  * **设计思路简述**：采用FC红白机风格的像素画面（8色调色板，如深绿代表山，黄色标记中心），通过闪烁、颜色变化突出对称位置的山，配合音效（如“叮”声表示一对差值的累加），增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕左侧显示像素化的山脉（每个山用绿色方块表示，高度由方块数量体现），右侧显示控制面板（单步/自动按钮、速度滑块）。
        - 顶部显示当前处理的长度和最小不对称值。

    2.  **奇数长度扩展演示**：
        - 选择中心点（如第3座山），用黄色方块高亮。初始长度1（仅中心山），不对称值为0。
        - 单步执行时，左扩展至第2座山，右扩展至第4座山，这对山闪烁并显示差值（如`|h[2]-h[4]|`），不对称值累加，长度变为3。
        - 继续扩展，每对山闪烁并累加差值，长度逐步增加。

    3.  **偶数长度扩展演示**：
        - 选择相邻两座山（如第3和第4座）作为中心，用黄色方块并排高亮。初始长度2，不对称值为`|h[3]-h[4]|`。
        - 扩展时，左至第2座，右至第5座，累加差值，长度变为4，以此类推。

    4.  **最小值更新提示**：
        - 每次扩展得到新长度的不对称值时，若小于当前最小值，用红色数字闪烁更新顶部的最小值显示。

    5.  **音效与交互**：
        - 每对山闪烁时播放“叮”的轻脆音效；更新最小值时播放“滴”的提示音。
        - 支持调速（0.5x-2x）和单步执行，方便观察每一步的计算。

<visualization_conclusion>
通过这样的动画，我们能直观看到中心扩展法如何逐步计算各长度的最小不对称值，理解对称位置的差值如何累加，以及最小值的更新过程。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的动态规划或中心扩展法后，可尝试以下类似问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 中心扩展法可用于求解最长回文子串（LeetCode 5）、最短回文串（LeetCode 214）等对称相关问题。
      - 区间DP可用于矩阵链乘法（LeetCode 312）、石子合并（NOI 1995）等区间最优问题。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1279 字串距离**：考察动态规划，计算两字符串的编辑距离，与本题的区间递推思想类似。
    2.  **洛谷 P1115 最大子段和**：动态规划求解连续子数组的最大和，与本题维护各长度最小值的思路相似。
    3.  **洛谷 P1044 栈**：区间DP求解栈的合法序列数，需设计状态转移方程，适合巩固区间DP能力。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如：
</insights_intro>

> 参考经验（来自作者0x282e202e2029）：“在递归计算时，必须用`vis`数组记录已计算的子问题，否则重复计算会导致TLE。”

**点评**：这一经验非常重要。在动态规划或递归中，记录已计算的子问题（记忆化）是避免重复计算、优化时间复杂度的关键。对于类似的对称问题，记忆化或递推的顺序（如区间DP按长度从小到大）是确保效率的核心。

---

<conclusion>
本次关于“Symmetric Mountains”的C++解题分析就到这里。希望通过这份指南，大家能掌握动态规划和中心扩展法的核心思想，理解如何高效计算对称子数组的最小不对称值。编程能力的提升需要多练习、多思考，期待大家在后续题目中灵活运用这些技巧！💪
</conclusion>

---

---
处理用时：154.05秒