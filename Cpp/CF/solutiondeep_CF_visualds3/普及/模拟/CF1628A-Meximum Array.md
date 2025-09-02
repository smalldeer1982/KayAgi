# 题目信息

# Meximum Array

## 题目描述

Mihai has just learned about the [MEX](https://en.wikipedia.org/wiki/Mex_(mathematics)) concept and since he liked it so much, he decided to use it right away.

Given an array $ a $ of $ n $ non-negative integers, Mihai wants to create a new array $ b $  that is formed in the following way:

While $ a $ is not empty:

- Choose an integer $ k $ ( $ 1 \leq k \leq |a| $ ).
- Append the MEX of the first $ k $ numbers of the array $ a $ to the end of array $ b $ and erase them from the array $ a $ , shifting the positions of the remaining numbers in $ a $ .

But, since Mihai loves big arrays as much as the MEX concept, he wants the new array $ b $ to be the lexicographically maximum. So, Mihai asks you to tell him what the maximum array $ b $ that can be created by constructing the array optimally is.

An array $ x $ is lexicographically greater than an array $ y $ if in the first position where $ x $ and $ y $ differ $ x_i > y_i $ or if $ |x| > |y| $ and $ y $ is a prefix of $ x $ (where $ |x| $ denotes the size of the array $ x $ ).

The MEX of a set of non-negative integers is the minimal non-negative integer such that it is not in the set. For example, MEX({ $ {1, 2, 3} $ }) $ = 0 $ and MEX({ $ {0, 1, 2, 4, 5} $ }) $ = 3 $ .

## 说明/提示

In the first test case, the lexicographically maximum array $ b $ is obtained by selecting $ k=5 $ , resulting in the $ MEX $ of the whole array $ a $ . It is lexicographically maximum because an array starting with a smaller number than $ 4 $ is lexicographically smaller, and choosing a $ k<5 $ would result in an array starting with a number smaller than $ 4 $ .

In the second test case, there are two ways to obtain the maximum array: first selecting $ k=6 $ , then $ k=2 $ , or first selecting $ k=7 $ and then $ k=1 $ .

## 样例 #1

### 输入

```
6
5
1 0 2 0 3
8
2 2 3 4 0 1 2 0
1
1
5
0 1 2 3 4
4
0 1 1 0
10
0 0 2 1 1 1 0 0 1 1```

### 输出

```
1
4 
2
5 1 
1
0 
1
5 
2
2 2 
4
3 2 2 0```

# AI分析结果



---
# 💡 Kay的C++算法解析：Meximum Array 深入学习指南 💡

<introduction>
今天我们来一起分析“Meximum Array”这道C++编程题。本指南将帮助大家理解如何通过贪心策略构造字典序最大的数组b，并掌握关键算法和编程技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法 (Greedy Algorithm)

🗣️ **初步分析**：
> 解决“Meximum Array”的关键在于贪心策略——每一步选择能使当前MEX最大的最短前缀。贪心算法的核心思想是“每一步做局部最优选择，最终达到全局最优”，就像吃蛋糕时先选最大的那一块，剩下的再选次大的。  
> 在本题中，我们需要每次从数组a的前缀中找到最大的MEX值，并选择满足该MEX的最短前缀删除，这样既能保证当前b的字典序最大，又为后续步骤保留更多可能。  
> 核心难点在于如何高效计算当前最大MEX及对应的最短前缀。优质题解通常通过维护每个数值的位置序列（如deque或vector），快速确定MEX并更新剩余数组状态。  
> 可视化设计将采用8位像素风格，用不同颜色的方块表示数组元素，动态展示每一步选择前缀的过程（如高亮当前处理的元素、闪烁显示MEX值），并通过音效（如“叮”声）提示关键操作，增强直观理解。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法效率等维度评估，以下题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：作者vectorwyx**
* **点评**：此题解思路非常清晰，采用贪心策略结合deque维护数值位置，时间复杂度O(n)，是最优解法之一。代码变量命名规范（如`g[i]`表示数值i的位置队列），逻辑简洁。亮点在于通过遍历数值0到n，找到第一个无位置的数值（即当前MEX），并取之前所有数值位置的最大值作为删除的k，高效维护剩余数组状态。实践价值高，可直接用于竞赛。

**题解二：作者cqbzhzf**
* **点评**：此题解采用贪心+二分的思路，时间复杂度O(n log n)，代码结构清晰。通过vector存储各数值的位置，利用二分查找快速确定当前前缀的右端点。亮点在于用`lb`函数（类似lower_bound）快速找到大于当前左端点的最小位置，确保选择最短前缀。适合理解二分优化在贪心问题中的应用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决本题时，我们通常会遇到以下核心难点，结合优质题解的思路，一起来看如何突破：
</difficulty_intro>

1.  **关键点1**：如何确定当前最大的MEX？
    * **分析**：MEX是当前前缀中未出现的最小非负整数。优质题解（如vectorwyx）通过维护每个数值的位置队列，从小到大遍历数值，找到第一个无位置的数值，即为当前MEX。例如，若数值0、1、2的位置都存在，但数值3的位置队列为空，则MEX为3。
    * 💡 **学习笔记**：MEX的计算是贪心选择的基础，需从小到大检查每个数值是否存在。

2.  **关键点2**：如何选择满足当前MEX的最短前缀？
    * **分析**：要保证前缀的MEX等于当前最大MEX，需确保前缀包含0到MEX-1的所有数值。优质题解（如vectorwyx）通过取0到MEX-1所有数值的第一个位置的最大值，作为前缀的右端点，这样前缀最短且包含所有必要数值。
    * 💡 **学习笔记**：最短前缀的右端点是0到MEX-1各数值位置的最大值。

3.  **关键点3**：如何高效维护剩余数组的状态？
    * **分析**：删除前缀后，剩余数组的位置需要更新。优质题解（如vectorwyx）用deque维护各数值的位置队列，每次删除前缀后，弹出所有小于等于右端点的位置，确保后续MEX计算仅考虑剩余元素。
    * 💡 **学习笔记**：用队列（deque/vector）维护数值位置，可高效更新剩余数组状态。

### ✨ 解题技巧总结
<summary_best_practices>
- **贪心选择优先**：每一步选择当前最大的MEX，确保字典序最大。
- **位置队列维护**：用队列存储各数值的位置，快速找到当前前缀的右端点。
- **边界处理**：注意当MEX为0时（所有前缀都包含0），后续每个元素单独成段，MEX均为0。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
首先，我们来看一个综合优质题解思路的通用核心实现，它结合了贪心策略和高效的位置队列维护。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合vectorwyx和cqbzhzf的思路，采用deque维护数值位置，时间复杂度O(n)，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int N = 2e5 + 5;
    int a[N], n, b[N], m;
    deque<int> pos[N]; // 存储每个数值的位置队列

    void solve() {
        cin >> n;
        for (int i = 0; i <= n; ++i) pos[i].clear(); // 初始化队列
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        int current_pos = 0; // 当前处理的左端点
        m = 0;
        while (current_pos < n) {
            int mex = 0;
            int max_k = current_pos;
            // 找到当前MEX并计算最大k（前缀右端点）
            while (!pos[mex].empty() && pos[mex].front() <= current_pos) {
                pos[mex].pop_front(); // 弹出已处理的位置
            }
            if (pos[mex].empty()) { // mex即为当前MEX
                b[++m] = mex;
                current_pos++; // 前缀长度为1（仅当前位置）
                continue;
            }
            max_k = pos[mex].front();
            mex++;
            // 检查0到mex-1是否都有位置在current_pos之后
            while (true) {
                while (!pos[mex].empty() && pos[mex].front() <= current_pos) {
                    pos[mex].pop_front();
                }
                if (pos[mex].empty()) { // 找到MEX
                    b[++m] = mex;
                    current_pos = max_k; // 更新左端点为max_k
                    break;
                }
                max_k = max(max_k, pos[mex].front());
                mex++;
            }
        }
        cout << m << '\n';
        for (int i = 1; i <= m; ++i) {
            cout << b[i] << ' ';
        }
        cout << '\n';
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) {
            solve();
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先初始化各数值的位置队列，然后循环处理数组。每次循环中，通过遍历数值0到n，找到当前MEX（第一个无有效位置的数值），并计算包含0到MEX-1所有数值的最短前缀（右端点为这些数值位置的最大值）。删除该前缀后，更新左端点，继续处理剩余数组，直到所有元素被处理完毕。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：作者vectorwyx**
* **亮点**：用deque维护数值位置，O(n)时间复杂度，高效处理前缀删除。
* **核心代码片段**：
    ```cpp
    int pos = 0; m = 0;
    while (pos < n) {
        int t = pos;
        for (int i = 0; i <= n; ++i) {
            if (g[i].empty()) {
                b[++m] = i;
                break;
            } 
            big(pos, g[i][0]);
        }
        big(pos, t + 1);
        for (int i = 0; i <= n; ++i) {
            if (g[i].empty()) break;
            while (!g[i].empty() && g[i][0] <= pos) g[i].pop_front();
        }
    }
    ```
* **代码解读**：
    > 这段代码是贪心策略的核心。`pos`表示当前处理的左端点。循环中，遍历数值0到n，若`g[i]`（数值i的位置队列）为空，则当前MEX为i，否则取`g[i]`的第一个位置更新`pos`（即前缀右端点）。最后，弹出所有小于等于`pos`的位置，确保后续处理剩余元素。例如，当`g[0]`的第一个位置是3，`g[1]`的是5，则`pos`会被更新为5，此时前缀长度为5，MEX为2（假设`g[2]`为空）。
* 💡 **学习笔记**：用deque维护位置队列，可快速弹出已处理的位置，保证每次循环的时间复杂度为O(1)均摊。

**题解二：作者cqbzhzf**
* **亮点**：用vector存储位置，二分查找快速确定右端点。
* **核心代码片段**：
    ```cpp
    int lb(int x, int L) {
        int l = 0, r = v[x].size() - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (v[x][mid] <= L) l = mid + 1;
            else r = mid - 1;
        }
        return (l >= v[x].size()) ? (n + 1) : v[x][l];
    }
    // 主循环中：
    int r = l + 1;
    for (int i = 0; i <= n; ++i) {
        int p = lb(i, l);
        if (p > n) {
            mex.push_back(i);
            break;
        }
        r = max(r, p);
    }
    l = r;
    ```
* **代码解读**：
    > `lb`函数通过二分查找，找到数值x在左端点L之后的第一个位置。主循环中，遍历数值0到n，若数值i在L之后无位置（p > n），则MEX为i，否则更新右端点r为所有数值i的p的最大值。例如，数值0的p是3，数值1的p是5，则r=5，此时前缀长度为5，MEX为2（假设数值2的p > n）。
* 💡 **学习笔记**：二分查找适用于位置有序的情况，可快速定位有效位置，优化时间复杂度。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解贪心选择前缀的过程，我们设计了一个“像素探险家”主题的8位像素动画，模拟每一步选择前缀的操作。
</visualization_intro>

  * **动画演示主题**：像素探险家的MEX寻宝之旅

  * **核心演示内容**：探险家从数组左端出发，每次寻找当前最大的MEX，并选择最短的前缀（用像素方块标记），将其MEX加入宝藏袋（数组b），然后删除该前缀，继续探索剩余数组。

  * **设计思路简述**：采用FC红白机风格的8位像素画面（16色调色板，如#0F0、#F00表示不同数值），通过动态高亮当前处理的元素、闪烁显示MEX值，配合“叮”声（关键操作）和“胜利”音效（完成所有操作），增强学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕下方显示像素化数组a（每个元素是16x16像素方块，颜色对应数值大小，如0是绿色，1是红色等）。
          * 上方显示控制面板：单步/自动按钮、速度滑块（1-10级）、重置按钮。
          * 播放8位风格背景音乐（如《超级马里奥》经典旋律变调）。

    2.  **算法启动**：
          * 探险家（黄色像素小人）站在数组左端（位置1），头顶显示“当前左端点：1”。
          * 数值位置队列（如deque）用堆叠的像素方块在屏幕右侧展示，每个方块标有数值和位置。

    3.  **计算MEX与选择前缀**：
          * 探险家从数值0开始检查（用白色箭头指向数值0的队列），若队列非空（有位置方块），则箭头移动到下一个数值，直到找到空队列（MEX）。
          * 找到MEX后，探险家收集所有0到MEX-1数值的位置方块，取最大位置（用红色方框高亮），确定前缀右端点（用蓝色虚线标出前缀范围）。
          * 播放“叮”声，前缀方块变为灰色（表示删除），MEX值（如3）飞入宝藏袋（数组b），显示“b添加：3”。

    4.  **更新剩余数组**：
          * 剩余数组左移（像素方块滑动动画），探险家移动到新的左端点（右端点+1），数值位置队列弹出已删除的位置（方块消失）。

    5.  **目标达成**：
          * 当所有元素被删除，宝藏袋（数组b）完整显示，播放“胜利”音效（如《超级玛丽》通关音），屏幕显示“成功！”。

  * **旁白提示**：
      * “现在探险家要找当前的MEX啦！从0开始检查每个数值的位置队列~”
      * “看，数值2的队列空了，所以当前MEX是2！”
      * “需要选包含0和1的最短前缀，它们的最大位置是5，所以删除前5个元素~”

<visualization_conclusion>
通过这个像素动画，我们能直观看到每一步如何选择前缀，MEX如何计算，以及数组状态的变化，轻松理解贪心策略的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
贪心算法和MEX计算在多种场景中都有应用，掌握本题后，可尝试以下练习巩固：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * MEX计算：适用于需要“最小未出现数”的问题（如集合覆盖、游戏规则设计）。
      * 贪心选择最短前缀：适用于需要字典序最大的序列划分问题（如字符串分割、区间选择）。
      * 位置队列维护：适用于需要快速查询/更新元素位置的问题（如滑动窗口、动态数组处理）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4137 Rmq Problem / mex**
          * 🗣️ **推荐理由**：此题需高效计算区间MEX，与本题MEX计算逻辑相关，可练习数据结构（如主席树）的应用。
    2.  **洛谷 P1247 取火柴游戏**
          * 🗣️ **推荐理由**：贪心策略的经典应用，练习如何通过每一步最优选择达到全局最优。
    3.  **洛谷 P1090 合并果子**
          * 🗣️ **推荐理由**：贪心+优先队列的典型题，巩固贪心算法与数据结构的结合使用。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中，作者vectorwyx提到：“最初在处理MEX计算时，容易忽略队列中已删除的位置，导致错误。后来通过用deque维护位置，并在每次循环中弹出已处理的位置，问题迎刃而解。”
</insights_intro>

> **参考经验 (来自 vectorwyx)**：“在维护数值位置时，必须及时删除已处理的位置，否则后续MEX计算会错误包含已删除的元素。通过deque的front()和pop_front()操作，可以高效处理这一点。”
>
> **点评**：这位作者的经验非常实用。在处理动态数组时，及时更新数据结构的状态（如弹出已处理元素）是避免错误的关键。这提醒我们，在编写代码时，要特别注意数据结构的维护逻辑，确保每一步操作的准确性。

-----

<conclusion>
本次关于“Meximum Array”的C++解题分析就到这里。通过贪心策略和高效的数据结构维护，我们可以轻松构造出字典序最大的数组b。希望大家通过练习和动画演示，深入理解贪心算法的核心思想，下次挑战更难的题目！💪
</conclusion>

---
处理用时：133.74秒