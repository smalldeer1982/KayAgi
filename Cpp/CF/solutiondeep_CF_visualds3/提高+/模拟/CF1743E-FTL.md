# 题目信息

# FTL

## 题目描述

Monocarp is playing a video game. In the game, he controls a spaceship and has to destroy an enemy spaceship.

Monocarp has two lasers installed on his spaceship. Both lasers $ 1 $ and $ 2 $ have two values:

- $ p_i $ — the power of the laser;
- $ t_i $ — the reload time of the laser.

When a laser is fully charged, Monocarp can either shoot it or wait for the other laser to charge and shoot both of them at the same time.

An enemy spaceship has $ h $ durability and $ s $ shield capacity. When Monocarp shoots an enemy spaceship, it receives $ (P - s) $ damage (i. e. $ (P - s) $ gets subtracted from its durability), where $ P $ is the total power of the lasers that Monocarp shoots (i. e. $ p_i $ if he only shoots laser $ i $ and $ p_1 + p_2 $ if he shoots both lasers at the same time). An enemy spaceship is considered destroyed when its durability becomes $ 0 $ or lower.

Initially, both lasers are zero charged.

What's the lowest amount of time it can take Monocarp to destroy an enemy spaceship?

## 说明/提示

In the first example, Monocarp waits for both lasers to charge, then shoots both lasers at $ 10 $ , they deal $ (5 + 4 - 1) = 8 $ damage. Then he waits again and shoots lasers at $ 20 $ , dealing $ 8 $ more damage.

In the second example, Monocarp doesn't wait for the second laser to charge. He just shoots the first laser $ 25 $ times, dealing $ (10 - 9) = 1 $ damage each time.

## 样例 #1

### 输入

```
5 10
4 9
16 1```

### 输出

```
20```

## 样例 #2

### 输入

```
10 1
5000 100000
25 9```

### 输出

```
25```

# AI分析结果

---
# 💡 Kay的C++算法解析：FTL 深入学习指南 💡

<introduction>
今天我们来一起分析“FTL”这道C++编程题。这道题需要计算用两个激光炮摧毁敌方飞船的最短时间，涉及动态规划（DP）的巧妙应用。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（DP）应用

🗣️ **初步分析**：
解决“FTL”问题的关键在于用动态规划（DP）来管理激光炮的攻击状态。动态规划就像“拆问题小能手”——把大问题拆成小问题，用小问题的解推导大问题的解。本题中，我们需要计算不同伤害值对应的最小时间，通过记录“造成i点伤害的最短时间”来逐步推导最终答案。

题解的核心思路是：利用“双发攻击后两炮状态重置”的特性，定义状态为“最后一次攻击是双发”的最小时间，再结合单发攻击的情况。核心难点在于如何设计状态转移方程，平衡单发和双发的时间成本。例如，Leasier的题解用`f[i]`表示“通过若干单发+最后一次双发造成i点伤害的最小时间”，`g[i]`表示“多次双发组合造成i点伤害的最小时间”，通过双重循环转移状态。

可视化设计上，我们可以用8位像素风格的动画演示DP数组的更新过程：每个像素块代表一个伤害值`i`，颜色深浅表示时间长短（越浅时间越短）。当计算`f[i]`时，高亮当前枚举的`j`和`i-j`，并伴随“叮”的音效提示状态转移；双发攻击时，两个激光炮的像素图标会闪烁并同时发射，展示时间计算逻辑（如`max(t1*(j+1), t2*k)`）。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等方面筛选了以下优质题解（≥4星）：
</eval_intro>

**题解一：作者Leasier（赞8）**
* **点评**：此题解思路非常清晰，明确将状态分为“单发+最后一次双发”（`f[i]`）和“多次双发组合”（`g[i]`），并通过双重循环转移状态。代码变量命名规范（如`dp1`对应`f[i]`，`dp2`对应`g[i]`），边界处理严谨（如初始值设为极大值，逐步更新）。算法时间复杂度为O(h²)，在题目数据范围内（h≤5000）可高效运行。亮点在于利用双发攻击的状态重置特性，将问题分解为可递归计算的子问题。

**题解二：作者Lgx_Q（赞2）**
* **点评**：此题解通过二分查找优化“计算造成x伤害的最短时间”（`Find`函数），思路新颖。状态定义`f[i]`表示“最后一次是双发攻击造成i点伤害的最小时间”，结合了双发后的状态重置特性。代码结构工整，关键逻辑（如二分查找的条件判断）注释清晰。亮点在于用二分法简化了时间计算，降低了部分复杂度。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，我们常遇到以下核心难点。结合优质题解的共性，提炼解决策略：
</difficulty_intro>

1.  **关键点1：如何定义状态？**
    * **分析**：状态定义需能覆盖所有可能的攻击组合，并利用“双发后状态重置”的特性。优质题解（如Leasier）选择`f[i]`表示“最后一次是双发攻击造成i点伤害的最小时间”，这样每次双发后两炮回到初始状态，便于后续转移。
    * 💡 **学习笔记**：状态定义要抓住问题的“重置点”，让子问题之间有明确的边界。

2.  **关键点2：如何设计状态转移方程？**
    * **分析**：转移方程需考虑单发和双发的组合。例如，`g[i] = min(g[j] + f[i-j])`表示“用多次双发组合造成i点伤害的时间”，其中`f[i-j]`是最后一次双发的时间，`g[j]`是前面的双发组合时间。
    * 💡 **学习笔记**：转移方程的本质是“用已知子问题的解推导当前问题”，需覆盖所有可能的攻击顺序。

3.  **关键点3：如何处理边界条件？**
    * **分析**：初始状态`f[0] = 0`（未攻击时时间为0），其他状态初始化为极大值。最终答案需比较仅用单发（如样例2）和双发组合的情况，避免遗漏。
    * 💡 **学习笔记**：边界条件是DP的“起点”，需确保覆盖所有初始状态。

### ✨ 解题技巧总结
- **问题分解**：将复杂攻击组合拆分为“单发+双发”或“多次双发”的子问题。
- **状态压缩**：利用双发后的状态重置特性，减少状态维度（无需记录两炮的充电进度）。
- **二分优化**：如Lgx_Q的题解，用二分查找快速计算造成x伤害的最短时间，提升效率。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
首先看一个综合优质题解的通用核心实现，帮助理解整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合Leasier和Lgx_Q的思路，采用动态规划，定义`dp1`和`dp2`分别表示“单发+最后一次双发”和“多次双发组合”的最小时间。
* **完整核心代码**：
    ```cpp
    #include <stdio.h>
    typedef long long ll;
    const ll INF = 4e18;

    int main() {
        int p1, p2, h, s;
        ll t1, t2;
        scanf("%d %lld %d %lld %d %d", &p1, &t1, &p2, &t2, &h, &s);
        
        int max_damage = h + 5000; // 扩展伤害范围避免遗漏
        ll dp1[max_damage + 1], dp2[max_damage + 1];
        for (int i = 0; i <= max_damage; i++) {
            dp1[i] = dp2[i] = INF;
        }
        dp1[0] = dp2[0] = 0;

        // 仅用单发的最小时间
        ll single_min = INF;
        if (p1 > s) single_min = t1 * ((h - 1) / (p1 - s) + 1);
        if (p2 > s) single_min = t1 * ((h - 1) / (p2 - s) + 1);

        for (int i = 1; i <= max_damage; i++) {
            // 计算dp1[i]: 单发+最后一次双发的最小时间
            for (int j = 0; j * (p1 - s) + (p1 + p2 - s) <= i; j++) {
                int remain = i - (j * (p1 - s) + (p1 + p2 - s));
                ll shots2 = (remain == 0) ? 0 : (remain - 1) / (p2 - s) + 1;
                dp1[i] = ll(dp1[i], t1 * (j + 1), t2 * (shots2 + 1));
            }
            // 计算dp2[i]: 多次双发组合的最小时间
            for (int j = 0; j < i; j++) {
                dp2[i] = ll(dp2[i], dp2[j] + dp1[i - j]);
            }
            if (i >= h) single_min = ll(single_min, dp2[i]);
        }
        printf("%lld\n", single_min);
        return 0;
    }
    ```
* **代码解读概要**：
  代码首先初始化`dp1`和`dp2`数组为极大值，初始状态`dp1[0]=dp2[0]=0`。然后计算仅用单发的最小时间（`single_min`），再通过双重循环填充`dp1`（单发+双发）和`dp2`（多次双发）数组，最终取`dp2[h]`和`single_min`的最小值作为答案。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：Leasier**
* **亮点**：状态定义清晰，双重循环转移，直接覆盖所有可能的攻击组合。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; i++) {
        dp1[i] = dp2[i] = 4e18;
        for (int j = 0; j * (p1 - s) + (p1 + p2 - s) <= i; j++) {
            ll x = i - (j * (p1 - s) + (p1 + p2 - s));
            dp1[i] = min(dp1[i], max(t1 * (j + 1), t2 * ((x == 0 ? 0 : (x - 1) / (p2 - s) + 1) + 1)));
        }
        for (int j = 0; j < i; j++) {
            dp2[i] = min(dp2[i], dp2[j] + dp1[i - j]);
        }
        if (i >= h) ans = min(ans, dp2[i]);
    }
    ```
* **代码解读**：
  - 外层循环`i`枚举当前伤害值，内层循环`j`枚举激光炮1的单发次数。`j*(p1-s)`是激光炮1的单发总伤害，`(p1+p2-s)`是双发伤害，`x`是激光炮2需要补充的伤害。
  - `max(t1*(j+1), t2*(shots2+1))`计算双发的时间（取两炮充电时间的最大值）。
  - `dp2[i]`通过`dp2[j] + dp1[i-j]`转移，即多次双发的时间累加。
* 💡 **学习笔记**：双重循环是DP转移的常用方式，需确保枚举覆盖所有可能的子问题。

**题解二：Lgx_Q**
* **亮点**：用二分查找优化时间计算，减少状态转移的复杂度。
* **核心代码片段**：
    ```cpp
    int Find(int ted1, int ted2, int n) {
        int lo = max(ted1, ted2), hi = 1e16;
        while (lo <= hi) {
            int mid = lo + hi >> 1;
            int c1 = (mid - ted1)/t1, c2 = (mid - ted2)/t2;
            if (c1*(p1 -s) + c2*(p2 -s) >= n) hi = mid -1;
            else lo = mid +1;
        }
        return lo;
    }
    ```
* **代码解读**：
  - `Find`函数通过二分查找，计算在已有充电时间`ted1`和`ted2`的基础上，造成`n`点伤害的最短时间。
  - 二分区间左边界是两炮已有充电时间的最大值（必须等两炮充能完成），右边界设为极大值（1e16）。
  - 每次取中点`mid`，计算此时两炮能发射的次数`c1`和`c2`，判断总伤害是否足够，调整二分区间。
* 💡 **学习笔记**：二分查找适用于“求最小时间满足条件”的问题，能将线性查找优化为对数复杂度。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解动态规划的状态转移和双发攻击的时间计算，我们设计一个“激光炮像素战场”动画，用8位复古风格展示算法过程！
</visualization_intro>

  * **动画演示主题**：`像素激光战：最短时间摧毁计划`

  * **核心演示内容**：动态规划数组`dp1`和`dp2`的更新过程，双发攻击时两炮的充电进度条变化，以及时间计算的逻辑。

  * **设计思路简述**：采用FC红白机风格的像素界面（16色调色板），用不同颜色的像素块表示伤害值`i`（绿色代表已计算，红色代表当前处理）。双发攻击时，两炮的充电条（像素进度条）同步增长，时间显示为`max(t1*(j+1), t2*k)`，伴随“叮”的音效。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          - 屏幕左侧展示DP数组（`dp1`和`dp2`），每个格子是5x5像素的方块，颜色越深表示时间越长（初始为红色，值为INF）。
          - 右侧展示两个激光炮（像素飞船造型），下方有充电进度条（黄色像素块）。
          - 控制面板包含“单步执行”“自动播放”按钮和速度滑块。

    2.  **初始状态**：
          - `dp1[0]`和`dp2[0]`变为绿色（时间0），其他为红色。
          - 两炮的充电条归零，播放“滴”的初始化音效。

    3.  **状态转移演示**：
          - 当计算`dp1[i]`时，外层循环`i`的像素块闪烁（黄色→绿色），内层循环`j`的像素块高亮（蓝色）。
          - 激光炮1的充电条按`j+1`次充电（每次充电时间`t1`），进度条填满后发射（播放“咻”音效）。
          - 激光炮2的充电次数`k`根据`x`计算，进度条同步增长，双发时两炮同时发射（播放“轰”音效），`dp1[i]`的时间更新为`max(t1*(j+1), t2*k)`，像素块变绿色（时间更小）或橙色（时间较大）。

    4.  **双发组合演示**：
          - 计算`dp2[i]`时，`j`和`i-j`的像素块同时高亮（紫色），表示`dp2[j] + dp1[i-j]`的转移。
          - 时间累加时，`dp2[i]`的像素块颜色根据新时间调整（更浅表示更优）。

    5.  **最终结果**：
          - 当`i≥h`时，`dp2[i]`和仅用单发的时间比较，最终答案对应的像素块闪烁（金色），播放胜利音效（“啦~”）。

  * **旁白提示**：
      - “现在计算`dp1[10]`，激光炮1发射了3次，激光炮2需要发射2次，时间取两者最大值~”
      - “看，`dp2[20]`由`dp2[8] + dp1[12]`转移而来，时间更短啦！”

<visualization_conclusion>
通过这样的动画，我们能直观看到DP状态如何一步步更新，双发攻击的时间如何计算，轻松理解动态规划的核心逻辑！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，可以尝试以下题目巩固动态规划和状态转移的应用：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      本题的动态规划思想（状态定义+转移）适用于：
      - 资源分配问题（如背包问题，选择不同物品组合）；
      - 时间调度问题（如任务安排，选择不同任务顺序）；
      - 游戏策略问题（如角色升级，选择不同技能组合）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1048 采药** - 01背包问题
          * 🗣️ **推荐理由**：经典动态规划题，练习状态定义和转移方程设计。
    2.  **洛谷 P1077 摆花** - 多重背包问题
          * 🗣️ **推荐理由**：扩展背包问题，练习处理物品数量限制的状态转移。
    3.  **洛谷 P1156 垃圾陷阱** - 状态DP
          * 🗣️ **推荐理由**：结合时间和生命值的状态转移，挑战复杂状态定义。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本题解中未发现明确的作者个人心得分享部分。但根据题解特点，Kay想提醒大家：
</insights_intro>

> 在动态规划问题中，**状态定义**是关键！多尝试用“最后一步”的操作来定义状态（如本题的“最后一次是双发攻击”），往往能简化问题。调试时，可打印小数据的DP数组，观察状态转移是否符合预期，快速定位错误。

-----

<conclusion>
本次关于“FTL”的C++解题分析就到这里。希望大家通过动态规划的思想，理解如何拆解问题、设计状态，并在实践中灵活运用。下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：137.58秒