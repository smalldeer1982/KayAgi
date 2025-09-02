# 题目信息

# Two Hundred Twenty One (hard version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that the hard version does require you to output the numbers of the rods to be removed. You can make hacks only if all versions of the problem are solved.

Stitch likes experimenting with different machines with his friend Sparky. Today they built another machine.

The main element of this machine are $ n $ rods arranged along one straight line and numbered from $ 1 $ to $ n $ inclusive. Each of these rods must carry an electric charge quantitatively equal to either $ 1 $ or $ -1 $ (otherwise the machine will not work). Another condition for this machine to work is that the sign-variable sum of the charge on all rods must be zero.

More formally, the rods can be represented as an array of $ n $ numbers characterizing the charge: either $ 1 $ or $ -1 $ . Then the condition must hold: $ a_1 - a_2 + a_3 - a_4 + \ldots = 0 $ , or $ \sum\limits_{i=1}^n (-1)^{i-1} \cdot a_i = 0 $ .

Sparky charged all $ n $ rods with an electric current, but unfortunately it happened that the rods were not charged correctly (the sign-variable sum of the charge is not zero). The friends decided to leave only some of the rods in the machine. Sparky has $ q $ questions. In the $ i $ th question Sparky asks: if the machine consisted only of rods with numbers $ l_i $ to $ r_i $ inclusive, what minimal number of rods could be removed from the machine so that the sign-variable sum of charges on the remaining ones would be zero? Also Sparky wants to know the numbers of these rods. Perhaps the friends got something wrong, and the sign-variable sum is already zero. In that case, you don't have to remove the rods at all.

If the number of rods is zero, we will assume that the sign-variable sum of charges is zero, that is, we can always remove all rods.

Help your friends and answer all of Sparky's questions!

## 说明/提示

In the first test case for the first query you can remove the rods numbered $ 5 $ and $ 8 $ , then the following set of rods will remain: +--+--++-++-. It is easy to see that here the sign-variable sum is zero.

In the second test case:

- For the first query, we can remove the rods numbered $ 1 $ and $ 11 $ , then the following set of rods will remain: --++---++---. It is easy to see that here the sign-variable sum is zero.
- For the second query we can remove the rod numbered $ 9 $ , then the following set of rods will remain: ---++-. It is easy to see that here the variable sum is zero.
- For the third query we can not remove the rods at all.

## 样例 #1

### 输入

```
3
14 1
+--++---++-++-
1 14
14 3
+--++---+++---
1 14
6 12
3 10
4 10
+-+-
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4```

### 输出

```
2
5 8
2
1 11
1
9
0
1
1
2
1 2
1
2
2
1 3
1
2
2
2 3
1
3
1
3
2
3 4
1
4```

# AI分析结果

---
# 💡 Kay的C++算法解析：Two Hundred Twenty One (hard version) 深入学习指南 💡

<introduction>
今天我们要挑战的是这道“Two Hundred Twenty One (hard version)”。这道题不仅需要计算最少删除次数，还要输出具体的删除位置。别担心，跟着Kay的思路，我们一步步拆解问题，掌握核心技巧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学与前缀和应用` (结合奇偶性分析、前缀和优化及二分查找)

🗣️ **初步分析**：
解决这道题的关键在于理解“符号交替和”的性质，并通过前缀和快速定位删除位置。简单来说，符号交替和可以转化为一个普通的前缀和问题——我们给偶数位的数值取反（比如原数是+1，偶数位就变为-1），这样符号交替和就变成了新数组的普通区间和。这就像给每个位置“戴了顶帽子”，偶数位的帽子是“-”，奇数位是“+”，总和就是这些戴帽子后的数的和。

- **题解思路**：所有题解的核心结论是“删除次数最多为2”：
  - 若原区间和为0，无需删除（0次）。
  - 若区间长度为奇数且和为奇数，删1次即可。
  - 若区间长度为偶数且和为偶数，删2次（先删末尾转为奇数长度，再删1次）。
- **核心难点**：如何快速找到需要删除的位置？通过预处理前缀和的位置列表，利用二分查找快速定位。
- **可视化设计**：用8位像素风格展示区间和的计算过程（如每个位置的“帽子”变化），删除操作时用闪烁的像素块标记位置，前缀和数值用动态变化的数字显示，二分查找过程用箭头移动高亮候选位置。

---

## 2. 精选优质题解参考

<eval_intro>
通过对思路清晰度、代码规范性、算法有效性的评估，以下题解值得重点学习：
</eval_intro>

**题解一：作者遮云壑 (赞：6)**
* **点评**：此题解逻辑清晰，直接点明“删除次数只能是0、1、2”的核心结论，并通过前缀和数组和二分查找实现高效定位。代码中预处理每个前缀和的位置列表（如`pos[sum[i]].push_back(i)`），查询时通过`lower_bound`快速找到目标位置，体现了对数据结构的巧妙运用。边界处理严谨（如处理负数前缀和时的偏移），代码可读性强。

**题解二：作者FoXreign (赞：0)**
* **点评**：此题解代码简洁，注释清晰。通过将前缀和偏移处理（`sum[i] + n`）避免负数索引，利用`vector`存储各前缀和的位置，查询时直接二分，完美解决了定位问题。对奇偶情况的分类处理（如偶数长度先删末尾转为奇数）逻辑流畅，是典型的“结论+优化”解法。

**题解三：作者cmll02 (赞：0)**
* **点评**：此题解从数学角度深入分析，证明了“删除1次必可行”的结论（利用前缀和的连续性），并给出了具体的定位方法。虽然代码未完全展示，但分析过程对理解问题本质有很大帮助，适合深入思考。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的关键在于突破以下三个核心难点：
</difficulty_intro>

1.  **难点1：如何判断最少删除次数？**
    * **分析**：通过符号交替和的奇偶性与区间长度的奇偶性关联。若区间和为0，次数为0；若和为奇数（此时区间长度必为奇数），次数为1；若和为偶数（区间长度必为偶数），次数为2。这是因为符号交替和的奇偶性与区间长度的奇偶性一致（每次+1或-1改变和的奇偶性，长度增加1也改变奇偶性）。
    * 💡 **学习笔记**：奇偶性分析是解决此类问题的“钥匙”，先判断奇偶性，再决定策略。

2.  **难点2：如何快速定位删除位置？**
    * **分析**：预处理前缀和数组`sum`，其中`sum[i]`表示前i项的符号交替和（偶数位取反后）。当需要删除一个位置时，目标位置的前缀和需满足特定条件（如`sum[k] = sum[l-1] + (res+1)/2`）。通过`vector`存储每个前缀和的出现位置，查询时用`lower_bound`二分查找，时间复杂度O(log n)。
    * 💡 **学习笔记**：预处理+二分查找是处理“快速定位”问题的经典组合。

3.  **难点3：如何处理负数前缀和？**
    * **分析**：前缀和可能为负数，直接作为数组下标会越界。通过偏移量（如加n）将所有前缀和转为非负数（如`sum[i] + n`），避免索引错误。
    * 💡 **学习笔记**：偏移量处理是解决“负数下标”问题的常用技巧。

### ✨ 解题技巧总结
- **结论先行**：先通过观察样例和简单情况，总结出“删除次数最多为2”的结论，简化问题。
- **前缀和转换**：将符号交替和转化为普通前缀和，利用前缀和的性质快速计算区间和。
- **预处理位置列表**：用`vector`记录每个前缀和的出现位置，查询时二分查找，提升效率。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，提炼出一个通用的核心实现，兼顾清晰性和效率。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了遮云壑和FoXreign的思路，预处理前缀和位置列表，通过二分查找定位删除位置，适用于所有测试用例。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 3e5 + 5;

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        int T;
        cin >> T;
        while (T--) {
            int n, q;
            string s;
            cin >> n >> q >> s;
            vector<vector<int>> pos(2 * n + 1); // 偏移量处理负数
            vector<int> sum(n + 1);
            sum[0] = n; // 初始偏移
            pos[sum[0]].push_back(0);
            for (int i = 1; i <= n; ++i) {
                // 偶数位取反：i为偶数时，符号为-1
                int val = (s[i - 1] == '+') ? 1 : -1;
                sum[i] = sum[i - 1] + (i % 2 ? val : -val);
                pos[sum[i]].push_back(i); // 记录前缀和的位置
            }
            while (q--) {
                int l, r;
                cin >> l >> r;
                int current_sum = sum[r] - sum[l - 1];
                if (current_sum == 0) {
                    cout << "0\n";
                    continue;
                }
                if (abs(current_sum) % 2 == 1) { // 奇数和，删1次
                    cout << "1\n";
                    int target = sum[l - 1] + (current_sum > 0 ? current_sum / 2 + 1 : current_sum / 2 - 1);
                    auto it = lower_bound(pos[target].begin(), pos[target].end(), l);
                    cout << *it << "\n";
                } else { // 偶数和，删2次（先删末尾）
                    cout << "2\n";
                    int new_r = r - 1;
                    current_sum = sum[new_r] - sum[l - 1];
                    int target = sum[l - 1] + (current_sum > 0 ? current_sum / 2 + 1 : current_sum / 2 - 1);
                    auto it = lower_bound(pos[target].begin(), pos[target].end(), l);
                    cout << *it << " " << r << "\n";
                }
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：
  - 预处理阶段：计算前缀和数组`sum`，并记录每个前缀和的出现位置到`pos`中（处理负数偏移）。
  - 查询阶段：根据区间和的奇偶性判断删除次数，奇数和直接二分查找目标位置，偶数和先删末尾再查找。

---
<code_intro_selected>
接下来，我们赏析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：作者遮云壑**
* **亮点**：通过`vector<int> pos[N<<1]`存储前缀和位置，处理负数时用`sum[i] + n`偏移，代码简洁高效。
* **核心代码片段**：
    ```cpp
    vector<int> pos[N<<1];
    sum[0] = n;
    pos[sum[0]].push_back(0);
    for(int i=1;i<=n;i++){
        // 计算前缀和并记录位置
        if(i&1) sum[i] = sum[i-1] + (s[i] == '+' ? 1 : -1);
        else sum[i] = sum[i-1] - (s[i] == '+' ? 1 : -1);
        pos[sum[i]].push_back(i);
    }
    ```
* **代码解读**：
  - `sum[0] = n`：初始偏移量，避免负数索引。
  - 奇偶位处理：奇数位直接加值，偶数位取反后加（因为符号交替和的偶数位是减）。
  - `pos[sum[i]].push_back(i)`：记录每个前缀和对应的位置，便于后续二分查找。
* 💡 **学习笔记**：预处理前缀和位置是快速查询的基础，偏移量处理是关键细节。

**题解二：作者FoXreign**
* **亮点**：代码简洁，直接通过`lower_bound`查找目标位置，逻辑清晰。
* **核心代码片段**：
    ```cpp
    int tmp = sum[l - 1] + (res > 0 ? res / 2 + 1 : res / 2 - 1);
    cout << *lower_bound(pos[tmp].begin(), pos[tmp].end(), l) << endl;
    ```
* **代码解读**：
  - `tmp`计算目标前缀和：当区间和为正时，目标前缀和为`sum[l-1] + (res+1)/2`；为负时为`sum[l-1] + (res-1)/2`。
  - `lower_bound`查找第一个≥l的位置，确保在查询区间内。
* 💡 **学习笔记**：二分查找是快速定位的核心，需注意区间范围的限制。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization_intro\>
为了更直观地理解前缀和计算和删除位置的查找过程，我们设计了一个“像素探险家”主题的8位风格动画！
\</visualization_intro\>

  * **动画演示主题**：`像素探险家的符号迷宫`

  * **核心演示内容**：展示区间和的计算、前缀和数组的生成，以及通过二分查找定位删除位置的过程。

  * **设计思路简述**：8位像素风格（如FC游戏画面）让学习更轻松；用不同颜色的像素块表示+1（红色）和-1（蓝色），偶数位的块戴“-”帽子（绿色边框）；删除操作时用闪烁的黄色块标记位置，前缀和数值用动态数字显示，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧是“符号迷宫”（像素网格，每个格子标有+/-和位置编号）。
          * 右侧是“前缀和计算器”（动态数字显示当前前缀和）。
          * 控制面板：单步/自动播放按钮、速度滑块、重置按钮。

    2.  **前缀和计算**：
          * 探险家（像素小人）从位置0出发，每走到一个位置i，计算当前前缀和（如位置1：+1→和为1；位置2：-1→和为0，因偶数位取反）。
          * 每个前缀和值对应的位置用小旗子标记（如和为0的位置有旗子）。

    3.  **查询处理**：
          * 用户输入区间[l, r]，迷宫高亮显示该区间。
          * 计算区间和：若和为0，播放“胜利音效”（叮~），显示“无需删除”。
          * 若和为奇数，探险家开始二分查找：从中间位置开始，比较当前前缀和与目标值，逐步缩小范围，最终找到目标位置（闪烁黄色块）。
          * 若和为偶数，先删除末尾位置（该块变灰），再重复奇数和的查找流程。

    4.  **关键操作音效**：
          * 前缀和变化：“滴答”声。
          * 找到目标位置：“叮”的上扬音。
          * 删除操作：“噗”的轻响。

  * **旁白提示**：
      * “看！偶数位的符号被取反了，就像戴了顶小绿帽~”
      * “现在区间和是3（奇数），我们需要找一个位置，让前后两段和抵消！”
      * “二分查找开始，中间位置的前缀和是2，比目标值小，往右找~”

\<visualization_conclusion\>
通过这个像素动画，我们能直观看到前缀和如何变化，以及删除位置是如何被“找”出来的。是不是更容易理解了？
\</visualization_conclusion\>

-----

## 6\. 拓展练习与相似问题思考

\<similar_problems_intro\>
掌握此题后，可以尝试以下题目巩固数学与前缀和的应用：
\</similar_problems_intro\>

  * **通用思路/技巧迁移**：
      - 前缀和可用于快速计算区间和，结合奇偶性分析能简化问题。
      - 预处理+二分查找适用于需要快速定位的场景（如求最长子数组、最近位置等）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1115 最大子段和**
          * 🗣️ **推荐理由**：练习前缀和与动态规划，理解如何用前缀和快速计算区间和。
    2.  **洛谷 P2671 求和**
          * 🗣️ **推荐理由**：结合颜色和位置的奇偶性分析，与本题的奇偶性思路类似。
    3.  **洛谷 P1908 逆序对**
          * 🗣️ **推荐理由**：练习归并排序或树状数组，学习如何用预处理和二分优化复杂问题。

-----

## 7\. 学习心得与经验分享 (若有)

\<insights_intro\>
题解中作者“xuanxuan001”提到：“比赛时因负数除法的取整问题出错，用位运算处理更可靠。” 这提醒我们注意细节！
\</insights_intro\>

> **参考经验**：“在计算`res/2`时，系统除法对负数是向上取整的，导致错误。改用位运算或显式处理符号更可靠。”
>
> **点评**：数值计算的细节（如除法取整、负数处理）容易出错，测试时应覆盖边界情况（如负数和、零和）。遇到类似问题，可通过显式判断符号或使用位运算避免错误。

-----

\<conclusion\>
这道题的关键在于奇偶性分析和前缀和的灵活运用。通过预处理和二分查找，我们能高效解决问题。记住，多观察样例、总结结论，是解决这类“结论题”的关键！下次挑战更难的题目时，你一定能更自信~ 💪
\</conclusion\>

-----

---
处理用时：125.95秒