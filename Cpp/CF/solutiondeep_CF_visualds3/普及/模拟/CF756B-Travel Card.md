# 题目信息

# Travel Card

## 题目描述

A new innovative ticketing systems for public transport is introduced in Bytesburg. Now there is a single travel card for all transport. To make a trip a passenger scan his card and then he is charged according to the fare.

The fare is constructed in the following manner. There are three types of tickets:

1. a ticket for one trip costs $ 20 $ byteland rubles,
2. a ticket for $ 90 $ minutes costs $ 50 $ byteland rubles,
3. a ticket for one day ( $ 1440 $ minutes) costs $ 120 $ byteland rubles.

Note that a ticket for $ x $ minutes activated at time $ t $ can be used for trips started in time range from $ t $ to $ t+x-1 $ , inclusive. Assume that all trips take exactly one minute.

To simplify the choice for the passenger, the system automatically chooses the optimal tickets. After each trip starts, the system analyses all the previous trips and the current trip and chooses a set of tickets for these trips with a minimum total cost. Let the minimum total cost of tickets to cover all trips from the first to the current is $ a $ , and the total sum charged before is $ b $ . Then the system charges the passenger the sum $ a-b $ .

You have to write a program that, for given trips made by a passenger, calculates the sum the passenger is charged after each trip.

## 说明/提示

In the first example, the system works as follows: for the first and second trips it is cheaper to pay for two one-trip tickets, so each time $ 20 $ rubles is charged, after the third trip the system understands that it would be cheaper to buy a ticket for $ 90 $ minutes. This ticket costs $ 50 $ rubles, and the passenger had already paid $ 40 $ rubles, so it is necessary to charge $ 10 $ rubles only.

## 样例 #1

### 输入

```
3
10
20
30
```

### 输出

```
20
20
10
```

## 样例 #2

### 输入

```
10
13
45
46
60
103
115
126
150
256
516
```

### 输出

```
20
20
10
0
20
0
0
20
20
10
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Travel Card 深入学习指南 💡

<introduction>
今天我们来一起分析“Travel Card”这道C++编程题。本指南将帮助大家梳理题目思路，理解动态规划的核心应用，并掌握如何高效计算每次乘车的最优费用增量。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`动态规划（DP）`

🗣️ **初步分析**：
解决“Travel Card”这道题，关键在于用动态规划（DP）逐步计算每次乘车的最小累计费用。动态规划就像“搭积木”——我们通过已知的“小积木”（前i-1次的最小费用）来搭建“大积木”（前i次的最小费用）。在本题中，每次乘车后，系统需要选择三种车票（单程、90分钟、全天）中的最优解，这正是动态规划状态转移的典型场景。

- **题解思路对比**：所有优质题解均采用动态规划，但在“如何快速找到90分钟/全天票覆盖的最早乘车点”上有差异：部分用双指针维护时间窗口（O(n)），部分用二分查找（O(n log n)），后者代码更简洁，前者效率更高。
- **核心算法流程**：定义`dp[i]`为前i次乘车的最小费用。对于第i次乘车，有三种选择：
  1. 单程票：`dp[i] = dp[i-1] + 20`；
  2. 90分钟票：找到最早的j，使得第j次到第i次乘车的时间差≤89分钟（因票的有效期是t到t+89），则`dp[i] = dp[j-1] + 50`；
  3. 全天票：同理，找到最早的k，时间差≤1439分钟，则`dp[i] = dp[k-1] + 120`。取三者最小值更新`dp[i]`。
- **可视化设计**：采用8位像素风格的时间轴动画，用不同颜色方块表示乘车时间点（如黄色），用蓝色/绿色矩形覆盖90分钟/全天票的有效范围。每次计算`dp[i]`时，高亮当前处理的乘车点，动态显示三种选择的费用，并通过音效（“叮”声）提示最优选择。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选了以下4星及以上题解：
</eval_intro>

**题解一：作者ChenZQ（双指针优化）**
* **点评**：此题解巧妙用双指针维护90分钟和全天票的时间窗口，避免了二分查找的额外复杂度。代码中`l1`和`l2`分别表示当前90分钟和全天票覆盖的最早乘车点，通过滑动窗口实时更新，时间复杂度O(n)。变量命名直观（如`f[i]`表示前i次的最小费用），边界处理严谨（如循环更新指针），是高效且易理解的实现。

**题解二：封禁用户（二分查找）**
* **点评**：此题解用`lower_bound`快速找到时间窗口的左端点，代码简洁且逻辑清晰。状态转移方程明确，直接取三种选择的最小值，适合新手学习动态规划的基础应用。时间复杂度O(n log n)，在数据规模较大时仍能高效运行。

**题解三：ATION001（标准DP+二分）**
* **点评**：此题解完整展示了动态规划的核心步骤，从输入处理到状态转移再到结果输出，逻辑连贯。代码注释虽少但变量名（如`a[i]`表示乘车时间）和结构（循环处理每个乘车点）清晰，是标准DP解法的典型示例。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们需要重点突破以下三个关键点：
</difficulty_intro>

1.  **关键点1：如何定义动态规划的状态？**
    * **分析**：状态`dp[i]`需表示“前i次乘车的最小总费用”。这个定义能覆盖所有可能的车票组合，且无后效性（后续状态仅依赖前i次的结果）。例如，当计算`dp[3]`时，只需考虑前3次乘车的最优解，无需关心更早的状态。
    * 💡 **学习笔记**：动态规划的状态定义是解题的基石，需确保能覆盖所有子问题且便于转移。

2.  **关键点2：如何高效找到时间窗口的左端点？**
    * **分析**：对于90分钟票，需找到最大的j，使得第j次乘车时间≥第i次时间-89分钟（因票的有效期是t到t+89）。用双指针或`lower_bound`可高效实现：双指针通过滑动窗口（O(n)），二分查找通过有序数组（O(n log n)）。
    * 💡 **学习笔记**：当问题涉及时间范围或区间查询时，双指针或二分查找是常用的优化手段。

3.  **关键点3：如何处理三种车票的选择逻辑？**
    * **分析**：每次需比较三种选择的费用，取最小值。例如，若前i-1次费用是100元，单程票总费用是120元；若前j-1次费用是80元，90分钟票总费用是130元（80+50），则选择单程票更优。
    * 💡 **学习笔记**：动态规划的状态转移需全面考虑所有可能的决策，并选择最优解。

### ✨ 解题技巧总结
- **问题分解**：将“计算每次乘车的费用增量”分解为“计算前i次的最小总费用”，通过差分得到结果。
- **有序处理**：乘车时间需先排序（题目未说明是否有序，但样例输入无序时需先排序）。
- **边界处理**：注意时间差的计算（如90分钟票的有效范围是t到t+89，故时间差需≤89）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，采用二分查找优化，代码简洁且高效：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合封禁用户和ATION001的题解，使用动态规划+二分查找，时间复杂度O(n log n)，适合理解核心逻辑。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 2e5 + 10;
    int a[N], dp[N];

    int main() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        sort(a + 1, a + n + 1); // 乘车时间可能无序，需排序
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 20; // 单程票
            // 找90分钟票的左端点：第一个≥a[i]-89的位置
            int x = lower_bound(a + 1, a + i + 1, a[i] - 89) - a;
            dp[i] = min(dp[i], dp[x - 1] + 50);
            // 找全天票的左端点：第一个≥a[i]-1439的位置
            int y = lower_bound(a + 1, a + i + 1, a[i] - 1439) - a;
            dp[i] = min(dp[i], dp[y - 1] + 120);
        }
        for (int i = 1; i <= n; ++i) 
            cout << dp[i] - dp[i - 1] << '\n';
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取并排序乘车时间（确保时间有序），初始化`dp[0]=0`（0次乘车费用为0）。对于每个乘车点i，计算三种车票的费用：
    - 单程票：直接累加20元；
    - 90分钟票：用`lower_bound`找到时间≥a[i]-89的最早乘车点x，费用为`dp[x-1]+50`；
    - 全天票：同理，找到时间≥a[i]-1439的最早乘车点y，费用为`dp[y-1]+120`。取三者最小值更新`dp[i]`。最后输出每次乘车的费用增量（`dp[i]-dp[i-1]`）。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者ChenZQ（双指针优化）**
* **亮点**：双指针维护时间窗口，时间复杂度O(n)，适合处理大规模数据。
* **核心代码片段**：
    ```cpp
    int l1 = 1, l2 = 1;
    for (int i = 1; i <= n; ++i) {
        while (a[i] - a[l1] >= 90) l1++; // 维护90分钟窗口左端点
        while (a[i] - a[l2] > 1439) l2++; // 维护全天窗口左端点
        f[i] = min({f[i-1]+20, f[l1-1]+50, f[l2-1]+120});
    }
    ```
* **代码解读**：
    `l1`和`l2`分别表示当前90分钟和全天票覆盖的最早乘车点。每次i递增时，若当前乘车时间与`l1`的时间差≥90分钟，则`l1`右移（排除超出窗口的乘车点）。同理调整`l2`。最终取三种车票的最小费用。
* 💡 **学习笔记**：双指针适合处理滑动窗口问题，避免了二分查找的log复杂度，更高效。

**题解二：封禁用户（二分查找）**
* **亮点**：代码简洁，利用STL的`lower_bound`快速查找，适合新手学习。
* **核心代码片段**：
    ```cpp
    int x = lower_bound(a + 1, a + i + 1, a[i] - 89) - a;
    dp[i] = min(dp[i], dp[x - 1] + 50);
    ```
* **代码解读**：
    `lower_bound`在已排序的数组中查找第一个≥`a[i]-89`的元素位置x。`x-1`即为90分钟票覆盖的最后一个乘车点的前一个位置，费用为`dp[x-1]+50`。
* 💡 **学习笔记**：`lower_bound`是处理有序数组区间查询的利器，需掌握其用法。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解动态规划的状态转移和车票选择过程，我们设计一个“时间探险家”像素动画，用8位复古风格展示每次乘车的最优费用计算！
</visualization_intro>

  * **动画演示主题**：`时间探险家的车票选择`
  * **核心演示内容**：展示每次乘车时，系统如何比较单程、90分钟、全天票的费用，最终选择最优解，并更新总费用。
  * **设计思路简述**：8位像素风（如FC游戏画面）营造轻松氛围；时间轴上的黄色方块表示乘车时间点，蓝色/绿色矩形覆盖90分钟/全天票的有效范围；关键操作（如选择车票）伴随“叮”声，完成所有乘车后播放胜利音效，增强沉浸感。

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：屏幕左侧是时间轴（横向排列的像素格，每个格代表1分钟），右侧显示控制面板（开始/暂停、单步按钮、速度滑块）。顶部显示当前处理的乘车点i（如“第3次乘车”）。
    2. **处理第i次乘车**：时间轴上高亮当前乘车点（黄色闪烁），同时弹出三个对话框显示三种车票的费用（如“单程票：+20元”“90分钟票：+10元”“全天票：+30元”）。
    3. **选择最优车票**：最优费用的对话框变为绿色并放大，时间轴上覆盖对应车票的有效范围（蓝色矩形覆盖90分钟，绿色矩形覆盖1440分钟），伴随“叮”的音效。
    4. **更新总费用**：屏幕顶部的总费用数字从`dp[i-1]`渐变为`dp[i]`，并显示费用增量（如“本次收费：10元”）。
    5. **AI自动演示**：点击“自动播放”，动画自动按设定速度（可调节）演示所有乘车点的处理过程，学习者可观察每一步的选择逻辑。

  * **旁白提示**：
    - “现在处理第3次乘车，时间是30分钟。系统需要比较三种车票的费用！”
    - “看，90分钟票覆盖了前两次乘车（时间10和20分钟），总费用只需50元，比之前的40元多10元，所以本次收费10元！”

<visualization_conclusion>
通过这个动画，我们能直观看到动态规划的状态转移过程，以及三种车票如何影响总费用。下次遇到类似问题时，你也能像“时间探险家”一样快速找到最优解啦！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
动态规划在解决“最优选择”类问题中非常实用，以下是几个类似场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 背包问题：选择不同物品组合使总价值最大（类似本题选择不同车票组合使总费用最小）；
    - 最长递增子序列：通过状态转移找到最长序列（类似本题通过状态转移找到最优费用）；
    - 股票买卖：选择买卖时机使利润最大（类似本题选择车票时机使费用最小）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1048 采药** - 经典01背包问题，巩固动态规划状态转移。
    2.  **洛谷 P1803 凌乱的yyy / 线段覆盖** - 贪心与动态规划结合，练习区间选择。
    3.  **洛谷 P1216 数字三角形** - 基础动态规划题，理解自顶向下/自底向上的转移。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到调试时遇到的问题，例如时间差计算错误（如误用90而不是89），这对我们很有启发：
</insights_intro>

> **参考经验 (来自多位题解作者)**：“在计算90分钟票的有效范围时，容易忽略题目中‘t到t+x-1’的描述，导致时间差计算错误（如用a[i]-90而不是a[i]-89）。通过打印中间变量（如x的值）才定位到问题。”

**点评**：这些经验提醒我们，处理时间/区间问题时，需仔细阅读题目中的边界条件（如“包含t到t+x-1”）。调试时打印关键变量（如`x`和`y`的值）能快速定位错误，这是非常实用的技巧！

-----

<conclusion>
本次关于“Travel Card”的C++解题分析就到这里。希望这份指南能帮助你掌握动态规划的核心应用，以及如何高效处理时间窗口问题。记住，多动手写代码、多调试，你的算法能力会越来越强！下次见~ 💪
</conclusion>

-----

---
处理用时：142.48秒