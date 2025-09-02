# 题目信息

# Add, Divide and Floor

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ). In one operation, you can choose an integer $ x $ ( $ 0 \le x \le 10^{18} $ ) and replace $ a_i $ with $ \lfloor \frac{a_i + x}{2} \rfloor $ ( $ \lfloor y \rfloor $ denotes rounding $ y $ down to the nearest integer) for all $ i $ from $ 1 $ to $ n $ . Pay attention to the fact that all elements of the array are affected on each operation.

Print the smallest number of operations required to make all elements of the array equal.

If the number of operations is less than or equal to $ n $ , then print the chosen $ x $ for each operation. If there are multiple answers, print any of them.

## 说明/提示

In the first testcase, all elements are already equal, so $ 0 $ operations are required. It doesn't matter if you print an empty line afterwards or not.

In the second testcase, you can't make less than $ 2 $ operations. There are multiple answers, let's consider the answer sequence $ [2, 5] $ . After applying an operation with $ x = 2 $ , the array becomes $ [\lfloor \frac{4 + 2}{2} \rfloor, \lfloor \frac{6 + 2}{2} \rfloor] = [3, 4] $ . After applying an operation with $ x = 5 $ after that, the array becomes $ [\lfloor \frac{3 + 5}{2} \rfloor, \lfloor \frac{4 + 5}{2} \rfloor] = [4, 4] $ . Both elements are the same, so we are done.

In the last testcase, you can't make less than $ 6 $ operations. Since $ 6 $ is greater than $ n $ , you don't have to print them. One possible answer sequence is $ [0, 0, 0, 0, 0, 0] $ . We are just dividing the second element by $ 2 $ every time and not changing the first element.

## 样例 #1

### 输入

```
4
1
10
2
4 6
6
2 1 2 1 2 1
2
0 32```

### 输出

```
0
2
2 5
1
1
6```

# AI分析结果



---
# 💡 Kay的C++算法解析：Add, Divide and Floor 深入学习指南 💡

<introduction>
今天我们来一起分析“Add, Divide and Floor”这道C++编程题。这道题的关键在于通过最少的操作次数让数组所有元素相等，每次操作需要选择一个x，将所有元素替换为(a_i + x)/2的下取整。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟与数学分析` (结合操作模拟与奇偶性/二进制特性分析)

🗣️ **初步分析**：
解决这道题的关键在于抓住一个核心观察：每次操作不会改变数组元素的相对大小（即最大值始终是最大值，最小值始终是最小值）。因此，我们只需关注数组的最大值和最小值——当它们相等时，所有元素必然相等。

简单来说，这像一场“追逐游戏”：最大值和最小值需要通过若干次操作“相遇”。每次操作选择一个x，让两者都变成新的值（(max+x)/2和(min+x)/2的下取整），直到两者相等。

- **题解思路对比**：多数题解（如2huk、灵茶山艾府等）均围绕“维护最大值和最小值”展开，但具体选择x的策略不同。例如，有的通过奇偶性选择x（0或1），有的通过二进制位分析优化次数。
- **核心算法流程**：初始化max和min，循环操作直到max=min。每次根据max和min的奇偶性选择x，更新max和min，并记录x。
- **可视化设计**：采用8位像素风，用两个彩色方块（红代表max，蓝代表min）在“数字赛道”上移动，每一步操作后显示新的位置，伴随“叮”的音效（x选择时）和“咔嗒”音效（移动时）。AI自动演示模式可快速展示最优路径。

---

## 2. 精选优质题解参考

<eval_intro>
经过对各题解的思路清晰度、代码规范性、算法有效性的评估，以下题解因逻辑简洁、实现高效被选为优质参考（评分≥4星）：
</eval_intro>

**题解一：灵茶山艾府（赞：9）**
* **点评**：此题解从二进制角度切入，提出“公共前缀”优化思路，通过第一次操作将max扩展为全1的二进制数（如max=100→111），后续操作选x=0，大幅减少操作次数。代码逻辑清晰，时间复杂度O(n)，适合竞赛场景，对二进制特性的应用极具启发性。

**题解二：Union_Find（赞：0）**
* **点评**：此题解抓住x仅需选0或1的关键观察（因奇偶性决定差异），通过维护max和min的奇偶性选择x，代码简洁高效（仅需维护两个变量），边界处理严谨（如多测清空vector），适合新手学习基础模拟逻辑。

**题解三：I_will_AKIOI（赞：0）**
* **点评**：此题解明确“x的选择由min的奇偶性决定”，通过位运算（minn&1）快速确定x，代码简洁（仅需循环维护max和min），对奇偶性分析的应用直观易懂，适合理解基础操作逻辑。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼核心策略如下：
</difficulty_intro>

1.  **关键点1：为何只需关注最大值和最小值？**
    * **分析**：每次操作对所有元素应用相同的x，因此元素的相对大小不变（max始终是max，min始终是min）。当max和min相等时，所有元素必然相等。这一观察将问题复杂度从O(n)降至O(1)（仅需维护两个变量）。
    * 💡 **学习笔记**：抓住“相对大小不变”的特性，简化问题为双变量维护。

2.  **关键点2：如何选择x以最小化操作次数？**
    * **分析**：x的选择需缩小max和min的差距。通过奇偶性分析：若min为奇数，选x=1可让min+1后除以2（缩小与max的差）；否则选x=0（直接除以2）。这一策略确保每次操作后差距至少减半。
    * 💡 **学习笔记**：奇偶性是缩小差距的“钥匙”，x的选择应让min和max的差尽可能快地减小。

3.  **关键点3：如何处理操作次数超过n的情况？**
    * **分析**：题目仅要求输出次数，无需记录x。由于每次操作后max和min的差至少减半，操作次数最多为log2(max-min)+1（指数级下降），因此无需担心超时。
    * 💡 **学习笔记**：操作次数受限于二进制位数，具有高效性。

### ✨ 解题技巧总结
- **双变量维护**：仅维护max和min，避免遍历整个数组。
- **奇偶性决策**：根据min的奇偶性选择x（0或1），确保每一步最优。
- **二进制优化（进阶）**：将max扩展为全1的二进制数（如max=100→111），后续选x=0，减少操作次数（灵茶山艾府的思路）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解的通用核心实现，它结合了奇偶性决策和双变量维护，简洁高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Union_Find和I_will_AKIOI的思路，通过维护max和min，根据min的奇偶性选择x（0或1），确保每次操作后差距缩小。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    void solve() {
        int n;
        cin >> n;
        int max_val = -1e9, min_val = 1e9;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            max_val = max(max_val, x);
            min_val = min(min_val, x);
        }
        vector<int> ops;
        while (max_val != min_val) {
            int x = min_val & 1; // 根据min的奇偶性选x（0或1）
            max_val = (max_val + x) / 2;
            min_val = (min_val + x) / 2;
            ops.push_back(x);
        }
        cout << ops.size() << '\n';
        if (ops.size() <= n) {
            for (int x : ops) cout << x << ' ';
            cout << '\n';
        }
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) solve();
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取输入，维护max和min；然后循环直到两者相等，每次根据min的奇偶性选择x（0或1），更新max和min并记录x；最后输出操作次数和x序列（若次数≤n）。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点和实现思路。
</code_intro_selected>

**题解一：灵茶山艾府（来源：B站@灵茶山艾府）**
* **亮点**：通过二进制分析，第一次操作将max扩展为全1的二进制数（如max=100→111），后续选x=0，减少操作次数。
* **核心代码片段**：
    ```go
    u := 1<<bits.Len(uint(M)) - 1
    x := u - M
    ans := 1 + bits.Len(uint((u/2)^((m+x)/2)))
    ```
* **代码解读**：`bits.Len(uint(M))`获取max的二进制位数L，`u=2^L-1`是全1的二进制数（如L=3时u=111）。第一次选x=u-M，将max变为u；后续选x=0，max变为u/2（即111→11），min变为(m+x)/2。操作次数为1加新max和min的异或二进制位数（因异或的二进制长度即为差距的二进制位数）。
* 💡 **学习笔记**：二进制全1数的特性可快速缩小max和min的差距，是优化操作次数的关键。

**题解二：Union_Find（来源：用户题解）**
* **亮点**：仅维护max和min，通过奇偶性选x（0或1），代码极简。
* **核心代码片段**：
    ```cpp
    while (x != y) {
        k = y & 1;
        x = (x + k) >> 1;
        y = (y + k) >> 1;
        a.push_back(k);
    }
    ```
* **代码解读**：`y`是当前min，`y&1`获取其奇偶性（k=0或1）。每次选k作为x，将max（x）和min（y）更新为新值（(x+k)/2和(y+k)/2），直到两者相等。此逻辑直接体现“奇偶性决策”的核心。
* 💡 **学习笔记**：奇偶性决定x的选择，是缩小差距的最直接策略。

**题解三：I_will_AKIOI（来源：用户题解）**
* **亮点**：通过位运算快速确定x，代码简洁高效。
* **核心代码片段**：
    ```cpp
    x=minn&1;
    minn=minn+x>>1;
    maxx=maxx+x>>1;
    ans.push_back(x);
    ```
* **代码解读**：`minn&1`通过位运算快速判断min的奇偶性（x=0或1）。`minn+x>>1`等价于(minn+x)/2（下取整），`maxx+x>>1`同理。此逻辑利用位运算提升效率，适合大规模数据。
* 💡 **学习笔记**：位运算（如&1、>>1）是处理奇偶性和除法的高效方式。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“最大值和最小值如何通过操作相遇”，我们设计了一个“像素追逐”动画，用8位复古风格展示每一步操作！
</visualization_intro>

  * **动画演示主题**：`像素小蓝（min）和小红（max）的相遇之旅`

  * **核心演示内容**：小蓝（蓝色方块）和小红（红色方块）在“数字赛道”上移动，每次操作选择x（0或1），两者同时跳转到新的位置（(val+x)/2），直到相遇。

  * **设计思路简述**：8位像素风格（FC红白机配色）营造轻松氛围；小蓝和小红的移动动画直观展示max和min的变化；音效（选择x时“叮”，移动时“咔嗒”）强化操作记忆；每完成一次操作视为“小关卡”，增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕下方是“数字赛道”（水平像素条，刻度为0~10^9），小蓝（蓝色）和小红（红色）初始位置为数组的min和max。
          * 控制面板包含“开始/暂停”“单步”“重置”按钮和速度滑块（1x~5x）。
          * 播放8位风格背景音乐（如《超级玛丽》经典旋律变奏）。

    2.  **操作启动**：
          * 点击“开始”，小蓝和小红头顶显示当前值（如min=4，max=6），控制面板显示“选择x：0或1？”。
          * 根据奇偶性，自动选择x（如min=4是偶数→x=0），播放“叮”音效，x值显示在屏幕上方。

    3.  **移动动画**：
          * 小蓝和小红同时向上跳跃（像素化跳跃动画），落地后移动到新位置（(4+0)/2=2，(6+0)/2=3），头顶显示新值。
          * 赛道上用虚线标记旧位置，新位置用实线高亮，伴随“咔嗒”音效。

    4.  **关键步骤提示**：
          * 当小蓝或小红的奇偶性变化时（如min=3→奇数），屏幕弹出文字气泡：“注意！小蓝现在是奇数，下次选x=1哦~”。
          * 每次操作后，显示当前操作次数和剩余差距（如“操作1次，差距=1”）。

    5.  **相遇庆祝**：
          * 当小蓝和小红位置重合时，播放“胜利”音效（上扬音调），两者头顶显示“相遇！”，屏幕飘落像素星星。
          * 控制面板显示总操作次数，可查看每一步的x值。

    6.  **AI自动演示**：
          * 点击“AI演示”，算法自动选择最优x，快速展示小蓝和小红的相遇过程（速度可调），适合观察整体流程。

  * **旁白提示**：
      * （初始）“小蓝和小红需要相遇，每次操作选x，让它们同时跳转到新位置~”
      * （选x时）“小蓝是偶数，选x=0，这样它们的差距会缩小！”
      * （相遇时）“成功！小蓝和小红终于见面啦~”

<visualization_conclusion>
通过这个像素动画，我们可以直观看到max和min如何一步步缩小差距，理解x的选择逻辑和操作次数的计算方式。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，我们可以尝试以下拓展练习，巩固“维护最值”“奇偶性分析”等技巧：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的“维护最值”思想可用于处理“数组操作后统一值”的问题（如每次操作影响所有元素）。
      * “奇偶性分析”适用于需要缩小差距的问题（如游戏中的血量平衡、资源分配）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1020** - `导弹拦截`
          * 🗣️ **推荐理由**：需要维护最大值和最小值（拦截系统的高度），与本题“维护最值”思想类似。
    2.  **洛谷 P1106** - `删数问题`
          * 🗣️ **推荐理由**：通过逐位删除缩小数值，需分析奇偶性对结果的影响，锻炼逻辑决策能力。
    3.  **洛谷 P1618** - `三连击（升级版）`
          * 🗣️ **推荐理由**：需枚举可能的数值组合，结合奇偶性分析优化枚举次数，与本题的“缩小差距”思路相通。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到调试中的奇偶性处理经验，值得借鉴：
</insights_intro>

> **参考经验 (来自用户Union_Find)**：“最初没注意到x只需选0或1，尝试了随机x，导致代码超时。后来发现奇偶性决定差距变化，简化x的选择后顺利AC。”

**点评**：这位用户的经验提醒我们，复杂问题往往有简化的关键观察（如本题的“x仅需0或1”）。遇到类似问题时，先分析操作对数据的影响（如奇偶性、相对大小），可大幅简化代码。

-----

<conclusion>
本次关于“Add, Divide and Floor”的C++解题分析就到这里。希望这份学习指南能帮助大家理解“维护最值”和“奇偶性分析”的核心技巧。记住，编程的关键在于观察问题本质，找到简化的突破口。下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：141.64秒