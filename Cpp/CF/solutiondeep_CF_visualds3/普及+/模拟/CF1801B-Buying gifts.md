# 题目信息

# Buying gifts

## 题目描述

Little Sasha has two friends, whom he wants to please with gifts on the Eighth of March. To do this, he went to the largest shopping center in the city.There are $ n $ departments in the mall, each of which has exactly two stores. For convenience, we number the departments with integers from $ 1 $ to $ n $ . It is known that gifts in the first store of the $ i $ department cost $ a_i $ rubles, and in the second store of the $ i $ department — $ b_i $ rubles.

Entering the mall, Sasha will visit each of the $ n $ departments of the mall, and in each department, he will enter exactly one store. When Sasha gets into the $ i $ -th department, he will perform exactly one of two actions:

1. Buy a gift for the first friend, spending $ a_i $ rubles on it.
2. Buy a gift for the second friend, spending $ b_i $ rubles on it.

Sasha is going to buy at least one gift for each friend. Moreover, he wants to pick up gifts in such a way that the price difference of the most expensive gifts bought for friends is as small as possible so that no one is offended.

More formally: let $ m_1 $ be the maximum price of a gift bought to the first friend, and $ m_2 $ be the maximum price of a gift bought to the second friend. Sasha wants to choose gifts in such a way as to minimize the value of $ \lvert m_1 - m_2 \rvert $ .

## 说明/提示

In the first test case, Sasha has two possible options: buy a gift for the first friend in the first department, and the second friend — in the second department, or vice versa. In the first case, $ m_1 = m_2 = 1 $ , and in the second case — $ m_1 = m_2 = 2 $ . In both cases, the answer is $ 0 $ . In the second test case, you can buy gifts for the first friend in the $ 2 $ , $ 4 $ and $ 5 $ departments, and for the second friend — in the $ 1 $ and $ 3 $ departments.So $ m_1 = \max(2, 4, 2) = 4 $ , $ m_2 = \max(5, 3) = 5 $ . The answer is $ \lvert 4 - 5 \rvert = 1 $ .

## 样例 #1

### 输入

```
2
2
1 2
2 1
5
1 5
2 7
3 3
4 10
2 5```

### 输出

```
0
1```

# AI分析结果



---
# 💡 Kay的C++算法解析：Buying gifts 深入学习指南 💡

<introduction>
今天我们来一起分析“Buying gifts”这道C++编程题。这道题需要我们在每个部门的两个商店中选择一个购买礼物，确保两个朋友都至少收到一个礼物，并最小化他们收到礼物的最大价格之差。本指南将帮助大家梳理核心思路，理解关键算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举+数据结构优化（枚举最大值，结合集合维护候选值）

🗣️ **初步分析**：
解决这道题的关键在于“枚举其中一个朋友的最大价格，高效计算另一个朋友的最大价格候选值”。简单来说，就像在一堆糖果中，先确定给A的最大糖果是哪颗，再找给B的最大糖果，使得两者的差距最小。

在本题中，我们首先将所有部门按`a_i`（给第一个朋友的价格）排序，然后枚举每个`a_i`作为A的最大价格。此时，所有`a_j > a_i`的部门必须给B（否则A的最大值会更大），而`a_j ≤ a_i`的部门可以自由选择。我们需要在这些自由选择的部门中，找到B的最大价格，使得与`a_i`的差距最小。

核心难点在于：
1. 如何高效维护`a_j > a_i`部门的B的最大价格（后缀最大值）。
2. 如何在`a_j ≤ a_i`的部门中快速找到最接近`a_i`的B的价格（通过集合查询前驱和后继）。

可视化设计思路：用8位像素风格展示排序后的数组，每个部门用两个像素块表示`a_i`和`b_i`。枚举时，当前`a_i`的像素块高亮（如红色），后缀部分（必须给B的部门）用蓝色标记，集合中的候选B价格用绿色动态添加。查询前驱和后继时，用黄色箭头指向最接近的两个绿色块，伴随“叮”的音效提示。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等，以下题解因逻辑清晰、实现高效且考虑边界细节，被选为优质参考（≥4星）：
</eval_intro>

**题解一：作者芷陌陌吖**
* **点评**：此题解思路非常清晰，通过排序后枚举每个`a_i`作为A的最大值，用`multiset`维护前后部分的B值。代码规范（如变量名`pre`、`nxt`含义明确），处理了边界问题（如判断`nxt`是否为空）。特别是动态更新`multiset`的方法，高效解决了候选值的维护问题，实践价值高。

**题解二：作者lingying**
* **点评**：此题解详细描述了预处理后缀最大值`maxn`和用`set`维护前缀B值的过程，强调了边界条件（如`maxn[n+1]`初始化为-1e9），避免了测试点69的错误。代码结构简洁，变量命名直观（如`maxn`表示后缀最大值），对枚举逻辑的解释透彻，适合学习。

**题解三：作者chlchl**
* **点评**：此题解重点分析了实现细节（如排序时的第二关键字处理相等`a_i`的情况），并提供了hack数据验证。代码中使用双指针预处理后缀最大值，结合`set`查询前驱后继，逻辑严谨。对边界情况的处理（如多测清空`mx`数组）体现了良好的编程习惯。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，我们通常会遇到以下关键点或难点，结合优质题解的共性，提炼思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何选择枚举对象？**
    * **分析**：枚举A的最大价格（或B的最大价格）是核心策略。选择枚举A的最大值后，所有`a_j > a_i`的部门必须给B，这部分的B最大值可预处理为后缀最大值。枚举B的最大值同理，但通常选择A的最大值更直观（因排序后处理更方便）。
    * 💡 **学习笔记**：枚举最大值是处理“最小化最大值之差”问题的常用策略。

2.  **关键点2：如何高效维护候选值？**
    * **分析**：对于`a_j ≤ a_i`的部门，B的价格可以自由选择，需找到最接近`a_i`的候选。使用`set`或`multiset`可以高效查询前驱和后继（时间复杂度O(log n)），这是处理大规模数据的关键。
    * 💡 **学习笔记**：集合（如`set`）是维护动态候选值、支持快速查询的利器。

3.  **关键点3：如何处理相等的`a_i`？**
    * **分析**：排序后，相等的`a_i`可能被分到同一组。若枚举其中一个作为A的最大值，其他相等的`a_i`可以自由选择给A或B，需避免重复计算或遗漏候选值（如chlchl题解中使用双指针处理相等的`a_i`）。
    * 💡 **学习笔记**：排序时需考虑第二关键字（如`|a_i - b_i|`），确保相等值的处理顺序正确。

### ✨ 解题技巧总结
- **预处理后缀最大值**：按`a_i`排序后，从后往前遍历预处理后缀B的最大值，快速获取必须给B的部门的最大价格。
- **集合维护前驱后继**：用`set`动态插入自由选择部门的B值，通过`lower_bound`查询最接近当前`a_i`的候选。
- **边界条件处理**：初始化后缀最大值为极小值（如-1e9），避免空集时的错误；多测时清空集合和数组，防止数据污染。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解前，我们先看一个综合优质题解的通用核心实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了芷陌陌吖和lingying的思路，排序后枚举每个`a_i`作为A的最大值，预处理后缀B的最大值，并用`set`维护前缀B值，查询前驱后继。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 5e5 + 5, INF = 0x3f3f3f3f;

    struct Store {
        int a, b;
        bool operator<(const Store& other) const {
            return a < other.a;
        }
    } stores[N];

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            for (int i = 1; i <= n; ++i) {
                cin >> stores[i].a >> stores[i].b;
            }
            sort(stores + 1, stores + n + 1);
            vector<int> suffix_max(n + 2, -INF);
            for (int i = n; i >= 1; --i) {
                suffix_max[i] = max(suffix_max[i + 1], stores[i].b);
            }
            set<int> prefix_b;
            int ans = INF;
            for (int i = 1; i <= n; ++i) {
                int current_a = stores[i].a;
                int b_max = suffix_max[i + 1]; // 必须给B的部门的B最大值
                ans = min(ans, abs(current_a - b_max));
                if (b_max < current_a) { // 需要在自由选择的部门中找更接近的B值
                    auto it = prefix_b.lower_bound(current_a);
                    if (it != prefix_b.end()) {
                        ans = min(ans, *it - current_a);
                    }
                    if (it != prefix_b.begin()) {
                        --it;
                        ans = min(ans, current_a - *it);
                    }
                }
                prefix_b.insert(stores[i].b); // 将当前部门的B值加入前缀集合
            }
            cout << ans << '\n';
        }
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取输入并按`a`排序，预处理后缀B的最大值数组`suffix_max`。然后枚举每个`a_i`作为A的最大值，计算必须给B的部门的B最大值（`suffix_max[i+1]`），并在自由选择的部门（前缀）中用`set`查询最接近`a_i`的B值，更新最小差值。

---
<code_intro_selected>
接下来，剖析优质题解的核心代码片段，理解其亮点和关键思路。
</code_intro_selected>

**题解一：作者芷陌陌吖**
* **亮点**：使用`multiset`动态维护前后部分的B值，处理枚举时的动态更新。
* **核心代码片段**：
    ```cpp
    multiset<int> pre, nxt;
    for (int i = 1; i <= n; i++) {
        nxt.erase(nxt.find(s[i].b));
        int maxn = -INF;
        if (!nxt.empty()) {
            auto w = nxt.end(); w--;
            maxn = *w;
        }
        // 更新ans逻辑...
        pre.insert(s[i].b);
    }
    ```
* **代码解读**：
    `nxt`集合存储未处理的部门的B值，枚举时从`nxt`中移除当前部门的B值（因当前部门可能给A），然后取`nxt`的最大值作为必须给B的部门的B最大值。处理完后，将当前部门的B值加入`pre`集合（自由选择的前缀）。这种动态维护集合的方式，高效处理了枚举过程中的候选值更新。
* 💡 **学习笔记**：动态集合（如`multiset`）适合处理枚举过程中需要动态增删元素的场景。

**题解二：作者lingying**
* **亮点**：预处理后缀最大值`maxn`，并用`set`维护前缀B值，逻辑简洁。
* **核心代码片段**：
    ```cpp
    int maxn[N];
    for(int i=n,j=n;i>=1;i=j-1,j=i) {
        int ret=now;
        while(a[j-1].a==a[i].a&&j>1) {
            maxn[j]=ret;
            now=max(now,a[j].b);
            j--;
        }
        maxn[j]=ret;
        now=max(now,a[j].b);
    }
    set<int> s;
    for(int i=1;i<=n;i++) {
        ans=min(ans,abs(maxn[i]-a[i].a));
        if(maxn[i]<a[i].a) {
            auto it=s.lower_bound(a[i].a);
            // 查询前驱后继...
        }
        s.insert(a[i].b);
    }
    ```
* **代码解读**：
    `maxn`数组存储每个位置的后缀B最大值（必须给B的部门的B最大值）。预处理时，双指针处理相等的`a_i`，确保`maxn`正确。枚举时，若`maxn[i] < a[i].a`，则在`set`中查询最接近`a[i].a`的B值，更新答案。这种预处理+集合查询的方式，时间复杂度为O(n log n)，适合大规模数据。
* 💡 **学习笔记**：预处理关键数组（如后缀最大值）可以显著简化后续枚举逻辑。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解枚举和集合查询的过程，我们设计一个“像素寻宝”动画，用8位风格展示部门、价格和枚举过程。
</visualization_intro>

  * **动画演示主题**：像素探险家寻找最小差值宝藏

  * **核心演示内容**：排序后的部门数组，每个部门用两个像素块（红色代表`a_i`，蓝色代表`b_i`）。探险家（黄色小方块）从左到右枚举每个红色块作为A的最大值，动态更新必须给B的部门（蓝色高亮），并在自由选择的部门（绿色区域）中用放大镜（像素图标）查询最接近的蓝色块。

  * **设计思路简述**：8位像素风格营造轻松氛围，颜色标记区分不同状态（红色枚举点、蓝色必须给B、绿色自由选择）。音效（如“叮”提示查询成功）和小关卡（每枚举一个点算一关）增强趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：
        - 屏幕顶部显示排序后的部门数组，每个部门有两个像素块（红`a_i`、蓝`b_i`）。
        - 控制面板包含“开始/暂停”“单步”“重置”按钮和速度滑块。
        - 播放8位风格背景音乐（如《超级玛丽》主题曲变调）。

    2.  **预处理后缀最大值**：
        - 从右到左遍历部门，用蓝色箭头标记每个部门的后缀最大值（最大的蓝色块），伴随“刷”的音效。

    3.  **枚举过程**：
        - 探险家（黄色方块）移动到当前枚举的红色块（`a_i`），该块闪烁（红色→粉色）。
        - 右侧所有红色块大于当前`a_i`的部门的蓝色块高亮（深蓝），表示必须给B，顶部显示这些蓝色块的最大值（`suffix_max[i+1]`）。
        - 左侧的蓝色块（自由选择的部门）加入绿色集合区域，用“+”动画提示插入。

    4.  **查询前驱后继**：
        - 探险家举起放大镜，在绿色集合区域中查找最接近当前红色块的蓝色块。找到前驱（左箭头）和后继（右箭头）时，箭头闪烁，伴随“叮”音效。
        - 计算当前差值（`|a_i - b_max|`或前驱/后继的差值），屏幕顶部显示当前最小差值。

    5.  **目标达成**：
        - 枚举完成后，最小差值用金色字体高亮，播放胜利音效（如《塞尔达传说》获得道具音效）。

  * **旁白提示**：
    - “现在，探险家选择第3个部门的a值作为A的最大值！”
    - “右边的部门必须给B，它们的最大b值是5哦~”
    - “看！在左边的自由选择部门中，最接近a值的b值是4和6，差值分别是1和1~”

<visualization_conclusion>
通过这个像素动画，我们能直观看到枚举过程中每个步骤的变化，理解集合查询如何帮助找到最优解。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是枚举最大值+集合优化，这种思路可迁移到多种“最小化最大值之差”的问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - **区间最值问题**：如求数组中两数之差的最小值（枚举一个数，用集合维护其他数）。
      - **双变量优化问题**：如两个数组各选一个数，最小化差值（排序后双指针或集合查询）。
      - **动态规划辅助**：如某些DP问题中，用集合维护状态转移的候选值。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1886** - 滑动窗口最值
          * 🗣️ **推荐理由**：练习用双端队列或集合维护滑动窗口的最值，与本题的集合查询思路类似。
    2.  **洛谷 P1091** - 合唱队形
          * 🗣️ **推荐理由**：需要枚举中间点，求左右两侧的最长递增子序列，与枚举最大值的思路相通。
    3.  **洛谷 P1972** - [SDOI2009]HH的项链
          * 🗣️ **推荐理由**：用集合维护元素最后出现位置，处理区间查询问题，练习集合的灵活应用。

---

## 7\. 学习心得与经验分享

<insights_intro>
部分题解作者分享了调试经历和细节处理的经验，这些对我们很有启发：
</insights_intro>

> **参考经验 (来自作者lingying)**：“考试时交了9次才过，结果被CF当场FST。需要注意`maxn[n+1]`要初始化为-1e9，否则会在第69个测试点错误。”
> 
> **参考经验 (来自作者chlchl)**：“排序时若`a_i`相等，需按`|a_i - b_i|`从大到小排序，避免漏掉更优的B值。”

**点评**：这些经验提醒我们，边界条件（如数组初始化）和排序的第二关键字处理是编程中容易出错的地方。在调试时，应特别注意这些细节，通过构造测试数据（如chlchl提供的hack数据）验证代码的鲁棒性。

---

<conclusion>
本次关于“Buying gifts”的C++解题分析就到这里。通过枚举最大值、预处理后缀和集合查询，我们能高效解决这类问题。希望大家在练习中多思考边界条件和优化方法，提升编程能力！下次再见~ 💪
</conclusion>

---
处理用时：158.90秒