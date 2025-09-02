# 题目信息

# Array Sharpening

## 题目描述

You're given an array $ a_1, \ldots, a_n $ of $ n $ non-negative integers.

Let's call it sharpened if and only if there exists an integer $ 1 \le k \le n $ such that $ a_1 < a_2 < \ldots < a_k $ and $ a_k > a_{k+1} > \ldots > a_n $ . In particular, any strictly increasing or strictly decreasing array is sharpened. For example:

- The arrays $ [4] $ , $ [0, 1] $ , $ [12, 10, 8] $ and $ [3, 11, 15, 9, 7, 4] $ are sharpened;
- The arrays $ [2, 8, 2, 8, 6, 5] $ , $ [0, 1, 1, 0] $ and $ [2, 5, 6, 9, 8, 8] $ are not sharpened.

You can do the following operation as many times as you want: choose any strictly positive element of the array, and decrease it by one. Formally, you can choose any $ i $ ( $ 1 \le i \le n $ ) such that $ a_i>0 $ and assign $ a_i := a_i - 1 $ .

Tell if it's possible to make the given array sharpened using some number (possibly zero) of these operations.

## 说明/提示

In the first and the second test case of the first test, the given array is already sharpened.

In the third test case of the first test, we can transform the array into $ [3, 11, 15, 9, 7, 4] $ (decrease the first element $ 97 $ times and decrease the last element $ 4 $ times). It is sharpened because $ 3 < 11 < 15 $ and $ 15 > 9 > 7 > 4 $ .

In the fourth test case of the first test, it's impossible to make the given array sharpened.

## 样例 #1

### 输入

```
10
1
248618
3
12 10 8
6
100 11 15 9 7 8
4
0 1 1 0
2
0 0
2
0 1
2
1 0
2
1 1
3
0 1 0
3
1 0 1```

### 输出

```
Yes
Yes
Yes
No
No
Yes
Yes
Yes
Yes
No```

# AI分析结果



---
# 💡 Kay的C++算法解析：Array Sharpening 深入学习指南 💡

<introduction>
今天我们来一起分析“Array Sharpening”这道C++编程题。本指南将帮助大家梳理题目思路，理解如何通过贪心策略判断数组能否通过递减操作变成“锐化数组”，并掌握关键解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法与数组边界分析

🗣️ **初步分析**：
> 解决“Array Sharpening”的关键在于理解“锐化数组”的结构特征——存在一个峰顶k，使得前半部分严格递增（a₁ < a₂ < ... < aₖ），后半部分严格递减（aₖ > aₖ₊₁ > ... > aₙ）。由于只能通过**减少正数元素**操作调整数组，我们需要用贪心思想找出数组能形成的最长递增前缀和最长递减后缀，判断是否存在交集。

- **题解思路对比**：大部分优质题解均采用“双指针扫描”策略：从前往后找最长递增前缀的结束位置（满足a[i] ≥ i-1），从后往前找最长递减后缀的起始位置（满足a[i] ≥ n-i）。若这两个区间有交集（即递减后缀的起始位置 ≤ 递增前缀的结束位置），则存在峰顶k。
- **核心算法流程**：通过两次线性扫描（O(n)时间）确定递增前缀和递减后缀的边界，最终比较边界判断是否存在解。
- **可视化设计**：采用8位像素风格动画，用不同颜色方块表示数组元素。扫描递增前缀时，绿色高亮满足a[i]≥i-1的元素；扫描递减后缀时，蓝色高亮满足a[i]≥n-i的元素。最终用红色箭头标注交集区域，提示是否存在峰顶。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰性、代码规范性、算法有效性等维度的评估，以下题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：作者liuyongle**
* **点评**：此题解思路简洁直接，代码规范高效。通过两次线性扫描分别计算递增前缀和递减后缀的边界，时间复杂度O(n)，非常适合竞赛场景。变量名`prefixEnd`和`suffixEnd`含义明确，边界处理严谨（如初始值设为-1和n）。关键逻辑（如break条件）清晰，直接反映了贪心策略的核心。

**题解二：作者OIer_Hhy**
* **点评**：此题解与liuyongle思路一致，但代码更简洁。通过`l`和`r`分别记录递增前缀和递减后缀的边界，判断条件`r <= l`直接明了。代码中使用`ans[2]`数组简化输出，体现了良好的代码优化意识。

**题解三：作者邓布利多6**
* **点评**：此题解详细处理了边界条件（如`high`和`high2`的初始化），确保了极端情况（如整个数组已递增或递减）的正确性。代码注释清晰，适合初学者理解每一步的作用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题时，我们需要重点突破以下三个关键点：
</difficulty_intro>

1.  **关键点1：如何定义“最长递增前缀”？**
    * **分析**：递增前缀要求前k项严格递增，即调整后a₁=0, a₂=1, ..., aₖ=k-1（最小可能值）。因此，原数组必须满足a[i] ≥ i-1（i从1开始）。通过从前往后扫描，找到第一个不满足a[i]≥i-1的位置，其前一个位置即为最长递增前缀的结束位置。
    * 💡 **学习笔记**：递增前缀的边界由“最小可能值”决定，原数组元素只需不小于该最小值即可通过递减操作满足条件。

2.  **关键点2：如何定义“最长递减后缀”？**
    * **分析**：递减后缀要求后m项严格递减，即调整后aₖ=m-1, aₖ₊₁=m-2, ..., aₙ=0（最小可能值）。因此，原数组必须满足a[i] ≥ n-i（i从n开始倒序扫描）。找到第一个不满足a[i]≥n-i的位置，其后一个位置即为最长递减后缀的起始位置。
    * 💡 **学习笔记**：递减后缀的边界同样由“最小可能值”决定，原数组元素只需不小于该最小值即可通过递减操作满足条件。

3.  **关键点3：如何判断是否存在峰顶k？**
    * **分析**：若递增前缀的结束位置≥递减后缀的起始位置，则两个区间存在交集，说明存在k使得前半部分递增、后半部分递减。例如，递增前缀结束于位置5，递减后缀起始于位置3，则k可以是3到5之间的任意位置。
    * 💡 **学习笔记**：交集的存在是判断锐化数组的充要条件。

### ✨ 解题技巧总结
<summary_best_practices>
- **贪心策略**：通过“最小可能值”快速确定边界，避免复杂计算。
- **双指针扫描**：两次线性扫描（O(n)时间）高效解决问题，适合处理大规模数据。
- **边界处理**：注意数组首尾的特殊情况（如整个数组已递增或递减），初始化边界值时需考虑极端情况。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，逻辑清晰且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了liuyongle和OIer_Hhy的思路，通过两次线性扫描确定边界，判断是否存在交集。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
            }

            int prefix_end = -1;
            for (int i = 0; i < n; ++i) {
                if (a[i] >= i) { // 递增前缀要求a[i] >= i（索引从0开始时，i-1变为i）
                    prefix_end = i;
                } else {
                    break;
                }
            }

            int suffix_start = n;
            for (int i = n - 1; i >= 0; --i) {
                if (a[i] >= (n - 1) - i) { // 递减后缀要求a[i] >= (n-1)-i（索引从0开始）
                    suffix_start = i;
                } else {
                    break;
                }
            }

            if (suffix_start <= prefix_end) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入，然后通过两次循环分别计算最长递增前缀的结束位置`prefix_end`和最长递减后缀的起始位置`suffix_start`。最后判断`suffix_start <= prefix_end`是否成立，若成立则输出"Yes"，否则输出"No"。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，学习其中的亮点和关键思路。
</code_intro_selected>

**题解一：作者liuyongle**
* **亮点**：变量命名直观，边界处理严谨（初始值设为-1和n），逻辑简洁。
* **核心代码片段**：
    ```cpp
    int prefixEnd = -1, suffixEnd = nbElem;
    for (int i = 0; i < nbElem; ++i) {
        if (tab[i] < i) break;
        prefixEnd = i;
    }
    for (int i = nbElem-1; i >= 0; --i) {
        if (tab[i] < (nbElem-1)-i) break;
        suffixEnd = i;
    }
    if (suffixEnd <= prefixEnd) cout << "Yes\n";
    else cout << "No\n";
    ```
* **代码解读**：
    > 第一个循环从前往后扫描，找到最长递增前缀的结束位置`prefixEnd`（满足`tab[i] >= i`）。第二个循环从后往前扫描，找到最长递减后缀的起始位置`suffixEnd`（满足`tab[i] >= (nbElem-1)-i`）。最后比较`suffixEnd`和`prefixEnd`，判断是否存在交集。
* 💡 **学习笔记**：通过初始值设置（如`prefixEnd=-1`），可以处理整个数组都不满足递增的情况（此时`prefixEnd`保持-1，`suffixEnd`可能大于-1，输出"No"）。

**题解二：作者OIer_Hhy**
* **亮点**：代码简洁，使用`ans[2]`数组简化输出，减少条件判断。
* **核心代码片段**：
    ```cpp
    int l=0,r=n+1;
    for(int i=1;i<=n;i++){
        if(a[i]<i-1) break;
        l=i;
    }
    for(int i=n;i>=1;i--){
        if(a[i]<n-i) break;
        r=i;
    }
    cout<<ans[(r<=l)];
    ```
* **代码解读**：
    > 变量`l`记录递增前缀的结束位置（满足`a[i] >= i-1`），`r`记录递减后缀的起始位置（满足`a[i] >= n-i`）。直接通过`r <= l`判断是否存在交集，输出结果。
* 💡 **学习笔记**：简化输出逻辑（如`ans[0]`和`ans[1]`分别对应"No"和"Yes"）可以提高代码效率和可读性。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解递增前缀和递减后缀的计算过程，我们设计一个“像素探险家”主题的8位风格动画，帮助大家“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：像素探险家寻找峰顶
  * **核心演示内容**：展示数组元素如何通过递减操作变成递增前缀和递减后缀，最终判断是否存在交集。
  * **设计思路简述**：采用8位像素风格（FC游戏画面），用不同颜色标记递增/递减区域，音效提示关键操作（如找到边界时播放“叮”声），增强学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕显示像素化数组（每个元素为彩色方块，如蓝色），下方是控制面板（单步/自动/重置按钮、速度滑块）。
          * 播放8位风格背景音乐（轻快的电子音效）。

    2.  **递增前缀扫描**：
          * 探险家（黄色像素小人）从左到右移动，检查每个方块。若方块值≥当前位置（i），方块变绿色（表示满足递增条件），探险家继续右移；若不满足，探险家停止，绿色区域结束位置即为`prefixEnd`，播放“滴答”音效。

    3.  **递减后缀扫描**：
          * 探险家从右到左移动，检查每个方块。若方块值≥(n-1)-i（i为当前位置），方块变蓝色（表示满足递减条件），探险家继续左移；若不满足，探险家停止，蓝色区域起始位置即为`suffixStart`，播放“滴答”音效。

    4.  **交集判断**：
          * 绿色区域（递增前缀）和蓝色区域（递减后缀）重叠时，屏幕中央弹出“胜利”字样，播放上扬的“胜利”音效；若不重叠，显示“失败”，播放短促“提示”音效。

  * **旁白提示**：
      * （扫描递增前缀时）“看！黄色小人在检查每个方块是否满足递增条件，绿色表示可以通过递减操作变成0,1,2...哦~”
      * （扫描递减后缀时）“现在小人从右边回来啦！蓝色表示可以通过递减操作变成...,2,1,0~”
      * （判断交集时）“绿色和蓝色重叠了吗？重叠就说明存在峰顶k哦！”

<visualization_conclusion>
通过这个像素动画，我们能清晰看到递增前缀和递减后缀的计算过程，以及如何通过交集判断是否存在锐化数组。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的贪心策略后，我们可以将其迁移到其他数组操作问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 贪心策略确定边界：适用于需要通过调整（如增减）使数组满足特定条件的问题（如严格递增/递减、山峰数组等）。
      * 双指针扫描：适用于需要同时处理数组前后部分的问题（如两数之和、盛最多水的容器）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1106** - 删数问题
          * 🗣️ **推荐理由**：通过贪心策略删除数字，使剩余数最小，与本题的贪心思想类似。
    2.  **洛谷 P1094** - 纪念品分组
          * 🗣️ **推荐理由**：双指针扫描处理数组，判断能否分组，锻炼边界分析能力。
    3.  **洛谷 P1223** - 排队接水
          * 🗣️ **推荐理由**：贪心策略优化总等待时间，与本题的“最小可能值”思路有共通之处。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，对我们很有启发：
</insights_intro>

> **参考经验 (来自作者Loser_King)**：“这题虽然思路简单，但一开始没考虑到整个数组已经递增/递减的情况，导致边界条件出错。后来通过测试样例发现问题，调整了初始值设置。”
>
> **点评**：这位作者的经验提醒我们，处理数组问题时一定要考虑极端情况（如全递增、全递减）。通过测试样例验证边界条件是避免错误的有效方法！

---

<conclusion>
本次关于“Array Sharpening”的C++解题分析就到这里。希望大家掌握贪心策略和双指针扫描的技巧，通过练习巩固所学。记住，编程能力的提升需要多思考、多实践，下次挑战更难的题目吧！💪
</conclusion>

---

---
处理用时：65.95秒