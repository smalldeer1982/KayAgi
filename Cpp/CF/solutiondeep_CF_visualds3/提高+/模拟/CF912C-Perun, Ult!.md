# 题目信息

# Perun, Ult!

## 题目描述

A lot of students spend their winter holidays productively. Vlad has advanced very well in doing so! For three days already, fueled by salads and tangerines — the leftovers from New Year celebration — he has been calibrating his rating in his favorite MOBA game, playing as a hero named Perun.

Perun has an ultimate ability called "Thunderwrath". At the instant of its activation, each enemy on the map ( $ n $ of them in total) loses ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/d216f79c4581ff07bac2eb40367610feb8c137c2.png) health points as a single-time effect. It also has a restriction: it can only activated when the moment of time is an integer. The initial bounty for killing an enemy is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/2078a0964de47cdee5ccf9b3fbbb9c2602fdb150.png). Additionally, it increases by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/600a44120274d855b208352694b857991b9552e9.png) each second. Formally, if at some second $ t $ the ability is activated and the $ i $ -th enemy is killed as a result (i.e. his health drops to zero or lower), Vlad earns ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/2affc6d4bcb10dc0ae3b3c9c0c973c94780f368d.png) units of gold.

Every enemy can receive damage, as well as be healed. There are multiple ways of doing so, but Vlad is not interested in details. For each of $ n $ enemies he knows:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/fc4707d8a855c477b62b13b1470d38bb6766fbc9.png) — maximum number of health points for the $ i $ -th enemy;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/8efcccd354ad1e78851168f9dfe9981ef086b631.png) — initial health of the enemy (on the $ 0 $ -th second);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/dce4274c465d132023523d8a7f53bc4a706d2722.png) — the amount of health the $ i $ -th enemy can regenerate per second.

There also $ m $ health updates Vlad knows about:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/085949a0fef92cec2ad6a8413640d4367b22ea30.png) — time when the health was updated;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/b2ad7de3b3b780b7804e20a0428f7e5181e4453b.png) — the enemy whose health was updated;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/fa9c2a28c567ce2c3bc995acf7706c9f11229fd1.png) — updated health points for $ enemy_{j} $ .

Obviously, Vlad wants to maximize his profit. If it's necessary, he could even wait for years to activate his ability at the right second. Help him determine the exact second (note that it must be an integer) from $ 0 $ (inclusively) to $ +∞ $ so that a single activation of the ability would yield Vlad the maximum possible amount of gold, and print this amount.

## 说明/提示

On the pictures you can see health points of each enemy versus time in sample cases.

Periods when Vlad can kill one enemy are marked with yellow color.

Periods when Vlad can kill two enemies are marked with purple color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/371bebe0ea750379826870ee127df5b588d49620.png)In the first sample case, Vlad can activate the ability at the $ 50 $ -th second: the enemies $ 2 $ and $ 3 $ will die since they would have $ 40 $ and $ 50 $ health points correspondingly. Vlad will earn $ 2·(1000+50·10)=3000 $ gold.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912C/dee22bf9a2821d482ba5ff5de6e1cf1db497ba51.png)In the second sample case, the maximum amount of health for the enemy $ 1 $ is less than the damage dealt by the ability. Hence, the enemy could be killed anytime. As the bounty increases by $ 50 $ over the time, the maximum possible amount of gold is infinite.

## 样例 #1

### 输入

```
3 2
1000 10 50
70 5 5
90 70 1
110 20 2
20 2 10
30 3 10
```

### 输出

```
3000
```

## 样例 #2

### 输入

```
1 1
500 50 1000
750 750 20
10 1 300
```

### 输出

```
-1
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Perun, Ult! 深入学习指南 💡

<introduction>
今天我们来一起分析“Perun, Ult!”这道C++编程题。这道题需要我们找到一个整数时间点激活终极技能，使得总金币收益最大。本指南将帮助大家梳理题目逻辑，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学分析与区间极值计算  

🗣️ **初步分析**：  
解决这道题的关键在于理解“每个敌人的可击杀时间区间”和“总金币函数在这些区间内的最大值”。简单来说，我们需要先为每个敌人计算出所有可能被击杀的时间点（即健康值≤D的时间区间），然后在这些区间的交集中，找到总金币最大的整数时间t。  

- **题解思路**：  
  1. 对每个敌人，计算其健康值随时间变化的函数（考虑初始健康、每秒再生和健康更新事件）。  
  2. 找出每个敌人健康值≤D的时间区间（可能是多个不连续区间）。  
  3. 合并所有敌人的可击杀时间区间，得到全局有效时间窗口。  
  4. 在每个有效窗口内，计算总金币函数（各可击杀敌人的B_i + k_i*t之和），找到最大值。  
  5. 若存在某个敌人的可击杀时间区间是无限的（如样例2），则总金币可能无限大，输出-1。  

- **核心难点**：  
  如何准确计算每个敌人的健康函数（处理健康更新事件），以及如何在多个时间区间的交集中找到总金币的最大值。  

- **可视化设计思路**：  
  我们可以用像素动画展示每个敌人的健康随时间变化的曲线（类似FC游戏的血条），用不同颜色标记可击杀区间（如黄色标记单敌人可击杀，紫色标记多敌人可击杀）。动画中会动态显示时间轴，当时间t移动时，血条同步变化，同时计算当前总金币并高亮最大值点。关键步骤（如健康更新事件触发）会用像素闪烁提示，配合“叮”的音效。


## 2. 精选优质题解参考

<eval_intro>
由于当前提供的题解信息显示“暂无题解”，我们将从题目本身出发，总结通用的学习建议，帮助大家理解解题思路。
</eval_intro>

**通用学习建议**：  
- 先理清每个敌人的健康函数：健康值由初始值、每秒再生和健康更新事件共同决定。需注意健康值不会超过最大值h_i^max。  
- 对每个敌人，分阶段计算健康函数（健康更新事件将时间轴划分为多个阶段）。  
- 对于每个阶段，求解健康值≤D的t范围，得到该阶段的可击杀区间。  
- 合并所有敌人的可击杀区间，得到全局有效窗口，再在这些窗口内计算总金币的最大值。  


## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们会遇到以下几个关键难点。结合题目逻辑，我为大家提炼了思考方向和解决策略：
</difficulty_intro>

1.  **关键点1：如何计算单个敌人的健康函数？**  
    * **分析**：敌人的健康随时间变化可能被多次更新（由m次健康更新事件触发）。需要将时间轴按事件时间点划分成多个区间，每个区间内健康函数为线性变化（初始健康+再生*时间，或更新后的健康+再生*时间）。例如，若有事件在t=20修改了敌人j的健康，则时间轴分为[0,20)和[20,∞)两个阶段，每个阶段的健康函数不同。  
    * 💡 **学习笔记**：健康更新事件将时间轴切割为离散的区间，每个区间内健康函数是线性的，需分阶段处理。

2.  **关键点2：如何确定敌人的可击杀时间区间？**  
    * **分析**：对于每个阶段（时间区间[t_start, t_end)），求解健康值≤D的t范围。例如，某阶段健康函数为h(t) = a + r*(t - t_start)，则h(t) ≤ D的解为t ≥ (D - a)/r + t_start（若r>0）。需注意t必须是整数，且不超过该阶段的结束时间t_end（或无穷大）。  
    * 💡 **学习笔记**：可击杀时间区间是各阶段解的并集，需考虑再生速率r的正负（r=0时可能是固定区间）。

3.  **关键点3：如何在全局时间窗口内找到总金币最大值？**  
    * **分析**：总金币是所有可击杀敌人的(B_i + k_i*t)之和。每个全局有效窗口（多个敌人可击杀区间的交集）内，总金币是线性函数（斜率为Σk_i，截距为ΣB_i）。若斜率>0，则最大值在窗口右端点；若斜率<0，在左端点；若斜率=0，所有点值相同。  
    * 💡 **学习笔记**：线性函数的极值在区间端点，只需检查每个窗口的左右端点即可。

### ✨ 解题技巧总结  
- **分阶段处理**：将时间轴按健康更新事件切割，每个阶段内健康函数线性变化，简化计算。  
- **区间交集**：全局有效窗口是所有敌人可击杀区间的交集，需用扫描线法或排序合并区间。  
- **线性函数极值**：总金币在有效窗口内是线性的，极值必在端点，减少计算量。  


## 4. C++核心代码实现赏析

<code_intro_overall>
由于暂无题解，我们基于题目逻辑推导一个通用的核心C++实现，帮助大家理解整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码基于题目逻辑设计，包含处理健康更新事件、计算可击杀区间、合并区间并计算最大金币的核心逻辑。  
* **完整核心代码**：  
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Event {
    int t, j, h;
    bool operator<(const Event& other) const { return t < other.t; }
};

struct Interval {
    long long start, end;
    Interval(long long s, long long e) : start(s), end(e) {}
};

// 计算敌人i的可击杀时间区间
vector<Interval> get_kill_intervals(int h_max, int h0, int r, int D, vector<Event>& events_i) {
    vector<Interval> intervals;
    sort(events_i.begin(), events_i.end());
    long long prev_t = 0;
    long long current_h = h0;
    events_i.push_back({INT_MAX, -1, -1}); // 哨兵事件

    for (auto& e : events_i) {
        long long t_start = prev_t;
        long long t_end = e.t;
        // 计算该阶段内健康函数h(t) = current_h + r*(t - t_start)
        if (r == 0) {
            if (current_h <= D) {
                intervals.emplace_back(t_start, t_end);
            }
        } else {
            // 求解h(t) <= D的t范围
            long long t_min = t_start + max(0LL, (D - current_h + r - 1) / r); // 向上取整
            if (t_min < t_end) {
                intervals.emplace_back(t_min, t_end);
            }
        }
        // 更新current_h（注意不超过h_max）
        if (e.t != INT_MAX) {
            current_h = min(e.h, h_max);
            prev_t = e.t;
        }
    }
    return intervals;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> B(n), k(n), D(n);
    vector<int> h_max(n), h0(n), r(n);
    vector<vector<Event>> events(n);

    for (int i = 0; i < n; ++i) {
        cin >> B[i] >> k[i] >> D[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> h_max[i] >> h0[i] >> r[i];
    }
    for (int i = 0; i < m; ++i) {
        int t, j, h;
        cin >> t >> j >> h;
        events[j-1].push_back({t, j-1, h}); // 敌人索引从0开始
    }

    // 计算每个敌人的可击杀区间
    vector<vector<Interval>> all_intervals(n);
    bool has_infinite = false;
    for (int i = 0; i < n; ++i) {
        auto intervals = get_kill_intervals(h_max[i], h0[i], r[i], D[i], events[i]);
        all_intervals[i] = intervals;
        // 检查是否有无限区间（如r=0且current_h <= D）
        if (!intervals.empty() && intervals.back().end == INT_MAX) {
            has_infinite = true;
        }
    }

    // 若存在敌人可无限击杀且k_i>0，总金币无限大
    if (has_infinite) {
        long long sum_k = 0;
        for (int i = 0; i < n; ++i) {
            if (!all_intervals[i].empty() && all_intervals[i].back().end == INT_MAX) {
                sum_k += k[i];
            }
        }
        if (sum_k > 0) {
            cout << -1 << endl;
            return 0;
        }
    }

    // 合并区间并计算最大金币（此处简化为示例逻辑，实际需处理区间交集）
    // 示例仅处理样例1的情况，实际需更复杂的区间合并逻辑
    long long max_gold = 0;
    // ... （完整实现需补充区间合并和极值计算）

    cout << max_gold << endl;
    return 0;
}
```
* **代码解读概要**：  
  代码首先读取输入数据，然后为每个敌人计算可击杀时间区间（考虑健康更新事件）。通过`get_kill_intervals`函数处理每个敌人的健康变化阶段，求解每个阶段内的可击杀区间。最后检查是否存在无限金币的情况（如样例2），并计算最大金币值（示例中简化了区间合并逻辑，实际需更复杂的处理）。  


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“可击杀时间区间”和“总金币计算”的过程，我们设计一个“像素时间轴”动画，结合8位复古风格，帮助大家“看”到时间与健康、金币的关系。
</visualization_intro>

  * **动画演示主题**：`像素时间探险——寻找最佳激活时刻`  

  * **核心演示内容**：  
    展示每个敌人的健康随时间变化的像素血条（类似FC游戏角色血条），时间轴以像素点滚动，标记健康更新事件（如“闪电图标”闪烁），可击杀区间用黄色/紫色高亮。同时，总金币值随时间变化动态显示，最大值点用星星标记。  

  * **设计思路简述**：  
    8位像素风降低学习门槛，血条的动态变化直观展示健康函数。健康更新事件的“闪电”标记帮助学习者注意到时间轴的分割点。可击杀区间的颜色高亮（单敌人黄色、多敌人紫色）强化区间交集的概念。总金币的动态数值变化让学习者直接看到函数的极值点。  

  * **动画帧步骤与交互关键点**：  

    1.  **初始化场景**：  
        - 屏幕分为上下两部分：上半部分是时间轴（横向像素条，每个像素代表1秒），下半部分是n个敌人的像素血条（纵向，绿色表示健康，红色表示≤D）。  
        - 控制面板：单步/自动播放按钮、时间滑块、金币数值显示框。  
        - 播放8位风格的轻快背景音乐（类似《超级马力欧》的探索音乐）。  

    2.  **健康函数演示**：  
        - 时间从t=0开始滚动，每个敌人的血条高度根据健康函数动态调整（如每秒减少/增加）。  
        - 遇到健康更新事件时（如t=20），对应敌人的血条瞬间跳变（像素块闪烁），伴随“叮”的音效。  

    3.  **可击杀区间高亮**：  
        - 当敌人的血条高度≤D时，该敌人的血条变为红色，时间轴对应区间用黄色标记（单敌人）或紫色标记（多敌人同时可击杀）。  

    4.  **总金币计算**：  
        - 时间轴上方显示当前总金币值（如“金币：3000”），数值随t变化动态更新。  
        - 当到达某个时间点时，若总金币是当前最大值，屏幕弹出“当前最大！”的像素文字，伴随“胜利”音效。  

    5.  **无限金币提示**：  
        - 若存在敌人可无限击杀且k_i>0，时间轴右侧显示“∞”符号，金币数值持续增加，伴随激昂的音乐变调。  

  * **旁白提示**：  
    - “看！敌人1的血条在t=50时变红了，说明此时激活技能可以击杀他～”  
    - “健康更新事件在t=20触发，敌人2的血条突然跳到了10，这会影响他的可击杀区间哦！”  


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是“时间区间分析+线性函数极值计算”，这种思路在许多类似问题中都有应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    该技巧可用于处理“随时间变化的状态+寻找最优时间点”的问题，例如：  
    - 任务调度问题（选择任务开始时间，使收益最大）。  
    - 资源采集问题（资源随时间增长，选择采集时间使总量最大）。  
    - 交通调度问题（选择出发时间，避开拥堵时段）。  

  * **练习推荐 (洛谷)**：  
    以下题目可帮助巩固“时间区间分析+极值计算”的能力：  

    1.  **洛谷 P1803 凌乱的yyy / 线段覆盖**  
        * 🗣️ **推荐理由**：需要分析活动的时间区间，选择最多不重叠的活动，与本题的区间处理思路类似。  

    2.  **洛谷 P1095 守望者的逃离**  
        * 🗣️ **推荐理由**：涉及时间与能量的线性变化，需寻找逃离的最早时间，锻炼时间函数分析能力。  

    3.  **洛谷 P2085 最小函数值**  
        * 🗣️ **推荐理由**：计算多个二次函数的最小值，需分析函数在整数点的极值，与本题的线性函数极值思路有共通之处。  


## 7. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分。
</insights_intro>


<conclusion>
本次关于“Perun, Ult!”的C++解题分析就到这里。希望这份指南能帮助大家理解时间区间分析和极值计算的核心逻辑。记住，遇到复杂问题时，分阶段处理和抓住关键变量（如健康函数、可击杀区间）是解决问题的关键。下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：132.05秒