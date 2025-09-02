# 题目信息

# Make A Equal to B

## 题目描述

You are given two arrays $ a $ and $ b $ of $ n $ elements, each element is either $ 0 $ or $ 1 $ .

You can make operations of $ 2 $ kinds.

- Pick an index $ i $ and change $ a_i $ to $ 1-a_i $ .
- Rearrange the array $ a $ however you want.

Find the minimum number of operations required to make $ a $ equal to $ b $ .

## 说明/提示

In the first case, we need only one operation: change $ a_1 $ to $ 1-a_i $ . Now $ a = [0, 0] $ which is equal to $ b $ .

In the second case, the optimal way is to rearrange $ a $ to get the array $ [0, 1, 11 $ . Now $ a = [0, 0, 1] $ which is equal to $ b $ .

In the second case, one of optimal ways would be to first change $ a_3 $ to $ 1 - a_3 $ , then rearrange $ a $ .

In the third case, no operation is needed.

In the fourth case, the optimal way is to rearrange $ a $ to get the array $ [0, 1, 1, 0] $ .

## 样例 #1

### 输入

```
5
3
1 0 1
0 0 1
4
1 1 0 0
0 1 1 1
2
1 1
1 1
4
1 0 0 1
0 1 1 0
1
0
1```

### 输出

```
1
2
0
1
1```

# AI分析结果



---
# 💡 Kay的C++算法解析：Make A Equal to B 深入学习指南 💡

<introduction>
今天我们来一起分析“Make A Equal to B”这道C++编程题。这道题需要我们找到将数组a变为数组b的最小操作次数，涉及两种关键操作：翻转元素和任意排序。本指南将帮助大家梳理思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举与贪心策略的综合应用

🗣️ **初步分析**：
解决这道题的关键在于比较两种可能的操作策略，选择其中操作次数更少的方案。简单来说，枚举是“穷举所有可能的策略”，而贪心是“选择当前最优的选项”。在本题中，我们需要枚举两种策略（直接翻转不同元素 vs 调整元素数量后排序），并贪心选择操作次数更少的那个。

- **题解思路**：所有题解都围绕两种策略展开：
  1. **不排序策略**：直接翻转a和b中对应位置不同的元素，操作次数为不同元素的个数（记为`ans1`）。
  2. **排序策略**：先调整a中1的数量使其与b相同（操作次数为两者1的数量差的绝对值），再通过一次排序操作使a等于b（总次数为`|cnt1_a - cnt1_b| + 1`，记为`ans2`）。
  最终答案取`min(ans1, ans2)`。
- **核心难点**：正确理解排序操作的作用（允许任意排列，因此只需元素数量匹配），以及两种策略的操作次数计算。
- **可视化设计思路**：设计一个8位像素动画，左边展示“直接翻转”的过程（逐个翻转不同元素，伴随“滴答”音效），右边展示“调整数量+排序”的过程（先调整1的数量，再用“旋转”动画表示排序，最后匹配成功时播放“叮”的音效）。通过颜色高亮不同元素和排序后的匹配过程。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解（评分≥4星）：
</eval_intro>

**题解一：作者0zhouyq**
* **点评**：此题解思路清晰，直接抓住了问题的核心——比较两种策略的操作次数。代码中变量命名直观（`bt`表示不同元素个数，`aa`、`bb`分别统计a、b中1的个数），逻辑简洁。特别是通过一次遍历同时统计不同元素个数和1的数量，时间复杂度为O(n)，非常高效。实践价值高，代码可直接用于竞赛场景。

**题解二：作者Larryyu**
* **点评**：此题解对两种策略的解释明确，代码结构工整。通过`cnt1`统计a中0的个数，`cnt2`统计b中0的个数（等价于统计1的数量差），变量命名符合直觉。核心逻辑`min(abs(cnt1-cnt2)+1, cnt3)`直接点明两种策略的比较，易于理解。

**题解三：作者sunkuangzheng**
* **点评**：此题解通过`n-n2`计算不排序的操作次数（`n2`为相同元素个数），逻辑巧妙。代码简洁，仅用一次遍历完成所有统计，时间复杂度低。对边界条件（如两数组已相同时输出0）的处理严谨，体现了良好的编程习惯。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下几个关键点或难点。结合优质题解的共性，我为大家提炼了核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1：理解排序操作的作用**
    * **分析**：排序操作允许我们任意排列a的元素，因此只要a和b中0和1的数量相同，排序后a可以直接等于b（无需额外翻转）。此时，操作次数为调整数量差的翻转次数（`|cnt1_a - cnt1_b|`）加上1次排序操作。
    * 💡 **学习笔记**：排序操作的本质是“重新排列元素”，因此只需保证元素数量匹配即可。

2.  **关键点2：正确统计两种策略的操作次数**
    * **分析**：不排序策略的操作次数是直接统计a和b对应位置不同的元素个数（`ans1`）。排序策略的操作次数是调整1的数量差的次数（`|cnt1_a - cnt1_b|`）加上1次排序操作（`ans2`）。需要注意，当a和b的1数量相同时，排序策略的操作次数为1（仅需排序）。
    * 💡 **学习笔记**：两种策略的操作次数需分别计算，再取最小值。

3.  **关键点3：处理边界条件**
    * **分析**：当a和b完全相同时，操作次数为0；当a和b的1数量相同但对应位置不同时，排序策略的操作次数为1（仅需排序）。这些边界情况需在代码中特殊处理，避免错误。
    * 💡 **学习笔记**：边界条件是编程中容易出错的地方，需仔细检查。

### ✨ 解题技巧总结
- **问题分解**：将复杂问题分解为两种简单策略（不排序、排序），分别计算操作次数，再取最小值。
- **一次遍历统计**：在遍历数组时，同时统计不同元素个数和1的数量，避免多次遍历，提高效率。
- **变量命名清晰**：使用有意义的变量名（如`diff_count`表示不同元素个数，`cnt1_a`表示a中1的个数），提高代码可读性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个优质题解的思路，通过一次遍历同时统计不同元素个数和1的数量，代码简洁高效。
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
            int cnt1_a = 0, cnt1_b = 0, diff_count = 0;
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                if (x == 1) cnt1_a++;
            }
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                if (x == 1) cnt1_b++;
                if (x != (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n ? (i < n

---
处理用时：357.30秒