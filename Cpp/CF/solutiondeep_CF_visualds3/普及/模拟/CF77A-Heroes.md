# 题目信息

# Heroes

## 题目描述

The year of 2012 is coming...

According to an ancient choradrican legend in this very year, in 2012, Diablo and his brothers Mephisto and Baal will escape from hell, and innumerable hordes of demons will enslave the human world. But seven brave heroes have already gathered on the top of a mountain Arreat to protect us mere mortals from the effect of this terrible evil.

The seven great heroes are: amazon Anka, barbarian Chapay, sorceress Cleo, druid Troll, necromancer Dracul, paladin Snowy and a professional hit girl Hexadecimal. Heroes already know how much experience will be given for each of the three megabosses: $ a $ for Mephisto, $ b $ for Diablo and $ c $ for Baal.

Here's the problem: heroes are as much as seven and megabosses are only three! Then our heroes decided to split into three teams, where each team will go to destroy their own megaboss. Each team member will receive a ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77A/4ac5ad94fb5392cd96ac09e5b84eb06e8c8a0edb.png) of experience, rounded down, where $ x $ will be the amount of experience for the killed megaboss and $ y $ — the number of people in the team.

Heroes do not want to hurt each other's feelings, so they want to split into teams so that the difference between the hero who received the maximum number of experience and the hero who received the minimum number of experience were minimal. Since there can be several divisions into teams, then you need to find the one in which the total amount of liking in teams were maximum.

It is known that some heroes like others. But if hero $ p $ likes hero $ q $ , this does not mean that the hero $ q $ likes hero $ p $ . No hero likes himself.

The total amount of liking in teams is the amount of ordered pairs $ (p,q) $ , such that heroes $ p $ and $ q $ are in the same group, and hero $ p $ likes hero $ q $ (but it is not important if hero $ q $ likes hero $ p $ ). In case of heroes $ p $ and $ q $ likes each other and they are in the same group, this pair should be counted twice, as $ (p,q) $ and $ (q,p) $ .

A team can consist even of a single hero, but it is important that every megaboss was destroyed. All heroes must be involved in the campaign against evil. None of the heroes can be in more than one team.

It is guaranteed that every hero is able to destroy any megaboss alone.

## 说明/提示

A note to first example: it the first team should be Dracul, Troll and Anka, in the second one Hexadecimal and Snowy, and in the third Cleo и Chapay.

## 样例 #1

### 输入

```
3
Troll likes Dracul
Dracul likes Anka
Snowy likes Hexadecimal
210 200 180
```

### 输出

```
30 3
```

## 样例 #2

### 输入

```
2
Anka likes Chapay
Chapay likes Anka
10000 50 50
```

### 输出

```
1950 2
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Heroes 深入学习指南 💡

<introduction>
今天我们来一起分析“Heroes”这道C++编程题。这道题需要将七位英雄分成三组挑战三个大BOSS，目标是最小化英雄间经验差的最大值，同时最大化组内的好感度。本指南将帮助大家梳理思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：搜索（DFS/回溯）

🗣️ **初步分析**：
> 解决“Heroes”这道题，关键在于用“搜索（DFS/回溯）”枚举所有可能的分组方式。简单来说，搜索算法就像“走迷宫”——每一步尝试不同的选择（把英雄分到哪个组），如果走到死胡同（分组不合法）就回头，直到找到所有可能的路径（合法的分组）。在本题中，我们需要用DFS遍历七位英雄的所有分组可能，计算每种分组的经验差和好感度，最终找到最优解。
   - 题解思路：通过递归函数`sc`尝试将每个英雄依次分配到三个组之一，同时计算当前分组的好感度。最终比较所有合法分组的经验差（取最小），并在差相同时取好感度最大的。
   - 核心难点：① 如何高效枚举所有合法分组（每个组至少1人）；② 快速计算组内好感度；③ 处理双目标优化（先最小化经验差，再最大化好感度）。
   - 可视化设计思路：用像素网格表示三个组，每个英雄是一个像素块（不同颜色区分组）。动画中，英雄逐个“飞入”选中的组，同时显示当前组的人数和经验值。关键步骤高亮（如当前处理的英雄、好感度增加的配对），并伴随“叮”的音效提示好感度变化。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面评估，本题解（作者：小杨小小杨）思路正确且能解决问题，评分4星。以下是详细点评：
</eval_intro>

**题解一：来源：小杨小小杨**
* **点评**：这份题解采用DFS回溯法枚举所有分组，思路直接易懂。代码中通过递归函数`sc`实现分组尝试，变量`b1/b2/b3`记录三个组的成员，`s`累加当前好感度。虽然变量命名（如`b1`）可更清晰，但核心逻辑（分组尝试+好感度计算）完整。算法上，由于英雄仅7人，暴力枚举在时间上是可行的（总共有约3^7=2187种分组，减去不合法的情况后更少）。实践价值高，代码稍作调整即可用于类似分组问题。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，我们常遇到以下关键点。结合题解思路，提炼策略如下：
</difficulty_intro>

1.  **关键点1**：如何枚举所有合法分组（每个组至少1人）？
    * **分析**：递归时需确保最终三个组的人数`aa/bb/cc`均≥1。题解中通过递归终止条件`if (t==8)`（处理完7人后）检查`aa/bb/cc`是否为0，若为0则跳过该分组。
    * 💡 **学习笔记**：枚举分组时，需明确终止条件并过滤非法情况（如空组）。

2.  **关键点2**：如何高效计算组内好感度？
    * **分析**：好感度是组内所有有序对(p,q)（p喜欢q）的数量。题解中，每次将英雄`t`加入某个组时，遍历该组已有成员，累加`t`与他们的互相喜欢关系（如`f[t][b1[i]]`和`f[b1[i]][t]`）。
    * 💡 **学习笔记**：动态计算好感度（每加入一个成员就更新）比最后统计更高效，避免重复遍历。

3.  **关键点3**：如何处理双目标优化（先最小差，再最大好感度）？
    * **分析**：先比较当前分组的经验差，若更小则更新最小差和最大好感度；若差相同，则取好感度更大的。题解中通过`if...else if`实现这一逻辑。
    * 💡 **学习笔记**：双目标优化需明确优先级（本题先差后好感度），并在代码中按顺序判断。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题抽象**：将“分组问题”抽象为递归枚举，用三个数组记录各组人员。
- **状态记录**：递归时传递当前各组人数和好感度，避免重复计算。
- **边界处理**：递归终止时检查各组人数是否合法（≥1）。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
首先，我们来看一个综合题解思路的通用核心实现，帮助理解整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码基于题解思路优化，变量命名更清晰，逻辑更易读。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int n, a, b, c;
    int like[8][8] = {0}; // like[p][q]表示p喜欢q
    map<string, int> hero_id = {
        {"Anka", 1}, {"Chapay", 2}, {"Cleo", 3}, {"Troll", 4},
        {"Dracul", 5}, {"Snowy", 6}, {"Hexadecimal", 7}
    };

    int min_diff = INT_MAX; // 最小经验差
    int max_like = 0;       // 最大好感度

    // 递归函数：当前处理第t个英雄，各组人数为x/y/z，当前好感度为current_like
    void dfs(int t, int x, int y, int z, int current_like) {
        if (t > 7) { // 所有英雄分配完毕
            if (x == 0 || y == 0 || z == 0) return; // 空组不合法
            int exp1 = a / x, exp2 = b / y, exp3 = c / z;
            int current_max = max({abs(exp1 - exp2), abs(exp2 - exp3), abs(exp1 - exp3)});
            // 更新最小差和最大好感度
            if (current_max < min_diff) {
                min_diff = current_max;
                max_like = current_like;
            } else if (current_max == min_diff) {
                max_like = max(max_like, current_like);
            }
            return;
        }

        // 尝试将t加入第一组
        int new_like = current_like;
        for (int i = 1; i <= x; ++i) { // 遍历当前第一组的成员（假设成员是1~t-1中已分配的）
            new_like += like[t][i] + like[i][t]; // 累加t与组内成员的互相喜欢
        }
        dfs(t + 1, x + 1, y, z, new_like);

        // 尝试加入第二组（同理）
        new_like = current_like;
        for (int i = 1; i <= y; ++i) {
            new_like += like[t][i] + like[i][t];
        }
        dfs(t + 1, x, y + 1, z, new_like);

        // 尝试加入第三组（同理）
        new_like = current_like;
        for (int i = 1; i <= z; ++i) {
            new_like += like[t][i] + like[i][t];
        }
        dfs(t + 1, x, y, z + 1, new_like);
    }

    int main() {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            string p, _, q;
            cin >> p >> _ >> q;
            like[hero_id[p]][hero_id[q]] = 1;
        }
        cin >> a >> b >> c;
        dfs(1, 0, 0, 0, 0); // 初始时各组人数为0，好感度为0
        cout << min_diff << " " << max_like << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码通过`dfs`函数递归分配每个英雄到三个组，动态计算当前组的好感度。主函数读取输入并初始化喜欢关系，最终输出最小经验差和最大好感度。关键逻辑在`dfs`中：每次递归尝试将当前英雄加入三个组之一，累加该组已有成员与当前英雄的喜欢关系，最终在所有英雄分配完毕后计算经验差并更新最优解。

---
<code_intro_selected>
接下来，剖析原解题的核心代码片段，理解其关键实现。
</code_intro_selected>

**题解一：来源：小杨小小杨**
* **亮点**：通过三个数组`b1/b2/b3`记录各组成员，递归时直接遍历数组计算好感度，逻辑直观。
* **核心代码片段**：
    ```cpp
    void sc(int t,int aa,int bb,int cc,int s){
        if (t==8){
            // 计算经验差并更新min_diff和ma（即max_like）
        }
        // 尝试将t加入第一组，计算新的s
        for (int i=1;i<=aa;i++){
            if (f[t][b1[i]]) ss++;
            if (f[b1[i]][t]) ss++;// 累加好感度
        }
        b1[aa+1]=t;sc(t+1,aa+1,bb,cc,ss);b1[aa+1]=0;
        // 同理处理第二、三组...
    }
    ```
* **代码解读**：
    > `sc`函数是递归的核心。参数`t`表示当前处理第t个英雄（1~7），`aa/bb/cc`是三组的人数，`s`是当前好感度。当`t=8`时（所有英雄分配完毕），检查是否有空组，计算经验差并更新最优解。尝试将`t`加入第一组时，遍历当前第一组的成员数组`b1`（已存储的成员），累加`t`与他们的互相喜欢关系（`f[t][b1[i]]`和`f[b1[i]][t]`），得到新的好感度`ss`，然后递归处理下一个英雄。第二、三组的逻辑类似。
* 💡 **学习笔记**：递归时用数组记录各组具体成员，虽然增加了空间开销，但能方便地遍历计算好感度，是解决此类分组问题的常用方法。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解英雄分组的过程，我们设计一个“像素英雄分组大战”动画，用8位像素风格展示DFS枚举分组的过程！
</visualization_intro>

  * **动画演示主题**：像素英雄分组记——寻找最优挑战方案
  * **核心演示内容**：七位像素英雄（不同颜色）逐个被分配到红、绿、蓝三个组（对应三个BOSS），动画展示每个分配步骤的好感度变化和最终经验差计算。
  * **设计思路简述**：8位像素风（如FC游戏）营造轻松氛围，英雄用Q版像素块表示，组用方框区分。关键步骤（如英雄入组、好感度增加）用闪烁/音效提示，帮助记忆算法逻辑。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为三部分，红、绿、蓝方框分别代表三个组，顶部显示“当前英雄：？”（初始为问号）。
          * 控制面板：单步/自动按钮、速度滑块（1x~5x）、重置按钮。
          * 背景音乐：8位风格的轻快旋律（类似《超级马力欧》）。

    2.  **英雄分配开始**：
          * 第一个英雄（如Anka，黄色像素块）出现在屏幕中央，箭头提示“请选择分组（红/绿/蓝）”。
          * 点击“单步”或自动播放，英雄飞入选中的组（如红组），组人数+1，伴随“咻”的音效。

    3.  **好感度计算**：
          * 当英雄加入组时，遍历组内已有成员：若存在喜欢关系（如A喜欢B），对应像素块闪烁，同时屏幕上方弹出“+1”（好感度），伴随“叮”音效。

    4.  **递归回溯**：
          * 若当前分组导致空组（如所有英雄都选红组），屏幕提示“非法分组！”，伴随“咚”音效，然后英雄飞回重新选择（回溯动画）。

    5.  **最优解展示**：
          * 所有分组枚举完成后，屏幕高亮显示最优分组（经验差最小，好感度最大），三组英雄摆出胜利姿势，播放“胜利”音效（如《魂斗罗》通关音）。

  * **旁白提示**：
      * （英雄入组时）“现在，Anka加入了红组！检查红组已有成员，看看有没有互相喜欢的～”
      * （好感度增加时）“看！Anka和Dracul互相喜欢，好感度加2！”
      * （最优解出现时）“找到啦！这个分组的经验差最小，好感度最大，是我们的最佳方案！”

<visualization_conclusion>
通过这个动画，大家可以直观看到DFS如何尝试所有分组，以及好感度和经验差的计算过程，就像在玩一个“英雄分组游戏”，轻松理解算法逻辑！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的DFS枚举思路可迁移到多种分组问题，关键是找到“枚举对象”和“目标计算方式”。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 学生分组活动：将学生分到若干组，最小化组间人数差，最大化组内友谊值（类似本题好感度）。
      * 任务分配：将任务分给多个团队，最小化完成时间差，最大化团队协作效率。
      * 资源分配：将资源分给多个项目，最小化资源利用率差，最大化总收益。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1036** - 选数  
          * 🗣️ **推荐理由**：经典DFS枚举问题，练习如何从n个数中选k个并计算质数，巩固搜索基础。
    2.  **洛谷 P1118** - [USACO06FEB]Backward Digit Sums G  
          * 🗣️ **推荐理由**：通过DFS枚举排列，计算特定和，训练递归与剪枝思维。
    3.  **洛谷 P1706** - 全排列问题  
          * 🗣️ **推荐理由**：基础全排列枚举，熟悉DFS生成所有排列的方法，为复杂分组问题打基础。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本题解未明确包含作者个人心得，但结合解题过程，我们可以总结以下经验：
</insights_intro>

> 调试时需注意：① 确保每个组至少1人（题解中通过`aa/bb/cc==0`判断）；② 好感度是有序对（p→q和q→p算两次）；③ 经验是向下取整（用`a/aa`直接计算）。

**点评**：这些细节是解题的关键。例如，若忽略“空组”判断，会导致错误解；若忘记有序对的双向计算，好感度会少算。调试时可打印中间分组的`aa/bb/cc`和好感度，快速定位问题。

-----

<conclusion>
本次关于“Heroes”的C++解题分析就到这里。通过DFS枚举分组、动态计算好感度，我们解决了这道双目标优化问题。希望大家通过动画和代码分析，掌握搜索算法的应用。编程的乐趣在于尝试和思考，下次见！💪
</conclusion>

-----

---
处理用时：115.51秒