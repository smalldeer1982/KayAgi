# 题目信息

# Level Statistics

## 题目描述

Polycarp has recently created a new level in this cool new game Berlio Maker 85 and uploaded it online. Now players from all over the world can try his level.

All levels in this game have two stats to them: the number of plays and the number of clears. So when a player attempts the level, the number of plays increases by $ 1 $ . If he manages to finish the level successfully then the number of clears increases by $ 1 $ as well. Note that both of the statistics update at the same time (so if the player finishes the level successfully then the number of plays will increase at the same time as the number of clears).

Polycarp is very excited about his level, so he keeps peeking at the stats to know how hard his level turns out to be.

So he peeked at the stats $ n $ times and wrote down $ n $ pairs of integers — $ (p_1, c_1), (p_2, c_2), \dots, (p_n, c_n) $ , where $ p_i $ is the number of plays at the $ i $ -th moment of time and $ c_i $ is the number of clears at the same moment of time. The stats are given in chronological order (i.e. the order of given pairs is exactly the same as Polycarp has written down).

Between two consecutive moments of time Polycarp peeked at the stats many players (but possibly zero) could attempt the level.

Finally, Polycarp wonders if he hasn't messed up any records and all the pairs are correct. If there could exist such a sequence of plays (and clears, respectively) that the stats were exactly as Polycarp has written down, then he considers his records correct.

Help him to check the correctness of his records.

For your convenience you have to answer multiple independent test cases.

## 说明/提示

In the first test case at the third moment of time the number of clears increased but the number of plays did not, that couldn't have happened.

The second test case is a nice example of a Super Expert level.

In the third test case the number of plays decreased, which is impossible.

The fourth test case is probably an auto level with a single jump over the spike.

In the fifth test case the number of clears decreased, which is also impossible.

Nobody wanted to play the sixth test case; Polycarp's mom attempted it to make him feel better, however, she couldn't clear it.

## 样例 #1

### 输入

```
6
3
0 0
1 1
1 2
2
1 0
1000 3
4
10 1
15 2
10 2
15 2
1
765 432
2
4 4
4 3
5
0 0
1 0
1 0
1 0
1 0```

### 输出

```
NO
YES
NO
YES
NO
YES```

# AI分析结果



---
# 💡 Kay的C++算法解析：Level Statistics 深入学习指南 💡

<introduction>
今天我们来一起分析“Level Statistics”这道C++编程题。这道题的关键在于判断游戏的游玩次数和通关次数记录是否合法。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟应用

🗣️ **初步分析**：
解决“Level Statistics”这道题，关键在于按时间顺序模拟验证每一条记录的合法性。简单来说，“模拟”就像我们按顺序检查每一步是否符合规则，就像老师批改作业时逐题核对答案一样。在本题中，模拟主要用于逐次验证每个时间点的游玩次数（p）和通关次数（c）是否符合游戏的统计逻辑。

- **题解思路**：所有优质题解均围绕三个核心条件展开验证：
  1. 当前通关次数不超过游玩次数（c_i ≤ p_i）；
  2. 游玩次数和通关次数不减少（p_i ≥ p_{i-1}, c_i ≥ c_{i-1}）；
  3. 两次记录间，增加的游玩次数 ≥ 增加的通关次数（p_i - p_{i-1} ≥ c_i - c_{i-1}）。
- **核心难点**：如何避免因提前终止输入导致后续数据混乱（需用标记法延迟判断）；如何准确理解“增量”的约束关系。
- **可视化设计思路**：用像素化的时间轴展示每次记录，用不同颜色标记合法/非法条件（如红色闪烁表示违反某条规则），动态箭头显示p和c的增量变化，队列可视化存储每次的p和c值。
- **复古游戏化设计**：采用8位像素风，每个时间点的记录作为“关卡”，成功通过所有关卡时播放“胜利”音效（如FC游戏的通关音），违反规则时播放“叮”的提示音。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，筛选出以下3份优质题解（均≥4星）：
</eval_intro>

**题解一：作者lingfunny**
* **点评**：此题解思路非常清晰，直接围绕三个核心条件展开验证。代码中使用`lp/lw`（上次的p/c）和`np/nw`（本次的p/c）作为关键变量，命名直观易懂。通过`flag`标记法延迟输出，避免了输入混乱的问题。宏定义`wa`简化了代码逻辑，边界处理严谨（如初始化和更新操作）。从实践角度看，代码可直接用于竞赛，是一份高效且易理解的实现。

**题解二：作者Warriors_Cat**
* **点评**：此题解结构工整，变量`p`和`c`数组明确存储各时间点的记录。循环中直接计算增量`x`（p的增量）和`y`（c的增量），条件判断逻辑直白（如`x < 0 || y < 0 || x < y`）。代码可读性高，适合初学者理解核心逻辑。

**题解三：作者AutumnKite**
* **点评**：此题解简洁高效，仅用变量`x`和`y`存储上一次的p/c值，避免了数组的额外空间开销。逻辑判断直接（如`nx < x || ny < y`），代码量少但覆盖所有条件，体现了“极简即极优”的编程思想，适合竞赛中快速实现。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个关键点或难点。结合优质题解的共性，提炼出核心思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何避免输入混乱？
    * **分析**：若在输入过程中发现不合法条件就立即输出`NO`，会导致后续输入未读取，与下一组测试数据混淆。优质题解普遍采用“标记法”：先用`flag`标记是否合法，待所有数据输入完毕后再输出结果。
    * 💡 **学习笔记**：多组输入时，延迟判断是避免输入混乱的关键。

2.  **关键点2**：如何准确验证增量约束？
    * **分析**：两次记录间，增加的游玩次数必须≥增加的通关次数（即`p_i - p_{i-1} ≥ c_i - c_{i-1}`）。这是因为每次游玩至少可能不通关（c不变），但通关必然伴随游玩（p和c同时+1）。若c的增量超过p，说明“通关了但没游玩”，违反规则。
    * 💡 **学习笔记**：增量约束的本质是“通关不能脱离游玩独立发生”。

3.  **关键点3**：如何处理初始条件？
    * **分析**：第一个时间点的p和c需满足`c_1 ≤ p_1`，且隐含初始状态`p_0=0, c_0=0`（即`p_1 ≥ 0, c_1 ≥ 0`）。优质题解通过初始化`lp=0, lw=0`来处理初始状态。
    * 💡 **学习笔记**：初始状态的隐含条件是验证的起点。

### ✨ 解题技巧总结
- **标记法**：用布尔变量标记合法性，避免提前终止输入。
- **增量计算**：直接计算两次记录的差值，简化条件判断。
- **变量命名**：使用`last_p/last_c`等直观变量名，提升代码可读性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，先来看一个综合优质题解的通用核心C++实现。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了lingfunny和Warriors_Cat的题解思路，采用标记法和增量计算，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    using namespace std;

    int main() {
        int T;
        cin >> T;
        while (T--) {
            int n;
            cin >> n;
            int last_p = 0, last_c = 0; // 初始状态p0=0, c0=0
            bool valid = true;
            for (int i = 0; i < n; ++i) {
                int p, c;
                cin >> p >> c;
                // 条件1：当前c不能超过p
                if (c > p) valid = false;
                // 条件2：p和c不能减少
                if (p < last_p || c < last_c) valid = false;
                // 条件3：增量约束（i=0时，last_p=0, last_c=0）
                if (i > 0 && (p - last_p) < (c - last_c)) valid = false;
                // 更新上一次的p和c
                last_p = p;
                last_c = c;
            }
            cout << (valid ? "YES" : "NO") << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取测试用例数T，对每个测试用例：
    - 初始化`last_p`和`last_c`为0（初始状态）；
    - 逐次读取每个时间点的p和c，检查三个核心条件；
    - 若任意条件不满足，标记`valid`为false；
    - 最后根据`valid`输出结果。

---
<code_intro_selected>
接下来，剖析优质题解的核心代码片段，理解其亮点和实现思路。
</code_intro_selected>

**题解一：作者lingfunny**
* **亮点**：使用宏定义`wa`简化标记操作，代码简洁；变量`lp/lw`（上次的p/c）命名直观，避免混淆。
* **核心代码片段**：
    ```cpp
    #define wa flag=0;
    // ...
    cin>>lp>>lw;
    if(lp<lw)wa
    for(int i=1;i<n;++i){
        cin>>np>>nw;
        if(nw>np)wa
        if(np<lp || nw<lw)wa
        if(lp-lw > np-nw)wa
        lp=np; lw=nw;
    }
    ```
* **代码解读**：
    - `wa`宏将标记置为false，简化重复操作；
    - 首先检查第一个时间点的`lp<lw`（c>p）；
    - 循环中检查后续时间点的三个条件（c>p、p/c减少、增量约束）；
    - 每次循环后更新`lp/lw`为当前值，以便下次比较。
* 💡 **学习笔记**：宏定义可简化重复逻辑，但需注意作用域和可读性。

**题解二：作者Warriors_Cat**
* **亮点**：直接计算增量`x`和`y`，条件判断更直观；数组存储所有记录，适合需要回溯的场景。
* **核心代码片段**：
    ```cpp
    for(int i = 2; i <= n; ++i){
        int x = p[i] - p[i - 1], y = c[i] - c[i - 1];
        if(x < 0 || y < 0 || x < y || p[i] < c[i]){
            flag = 0; break;
        }
    }
    ```
* **代码解读**：
    - `x`和`y`分别表示p和c的增量；
    - 检查增量是否非负（x≥0, y≥0）、增量约束（x≥y）、当前c≤p；
    - 发现不合法条件时立即标记并跳出循环。
* 💡 **学习笔记**：直接计算增量可让条件判断更清晰，适合逻辑简单的场景。

**题解三：作者AutumnKite**
* **亮点**：仅用变量存储上一次的p/c，空间复杂度O(1)，代码极简。
* **核心代码片段**：
    ```cpp
    int x = 0, y = 0; // 初始状态p0=0, c0=0
    for (int i = 1; i <= n; ++i) {
        int nx, ny;
        cin >> nx >> ny;
        if (nx < x || ny < y || nx - x < ny - y) flag = false;
        x = nx, y = ny;
    }
    ```
* **代码解读**：
    - `x/y`存储上一次的p/c，无需数组；
    - 直接检查p/c是否减少、增量约束；
    - 代码简洁，适合竞赛中快速编写。
* 💡 **学习笔记**：无需存储所有记录时，用变量代替数组可节省空间。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“模拟验证”的过程，我们设计一个8位像素风格的动画演示，名为“统计小卫士闯关”。通过像素化的时间轴和动态提示，帮助大家“看”到每一步的验证逻辑！
</visualization_intro>

  * **动画演示主题**：统计小卫士的关卡挑战（8位像素风）

  * **核心演示内容**：小卫士需要通过n个“时间关卡”，每个关卡对应一个(p_i, c_i)记录。每通过一个关卡，需验证三个条件；若任意条件不满足，关卡失败。

  * **设计思路简述**：
    - 8位像素风：模仿FC游戏的简洁画面（如《超级马力欧》的色块风格），营造轻松学习氛围；
    - 音效提示：关键操作（如验证通过/失败）播放经典像素音效（“叮”表示通过，“咚”表示失败）；
    - 关卡制：每个时间点作为一个小关卡，完成所有关卡后播放胜利音乐，增强成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          - 屏幕分为左右两部分：左侧是“时间轴”（8个像素块表示n个关卡），右侧是“数据面板”（显示当前p/c值、增量）；
          - 控制面板：单步/自动播放按钮、速度滑块（1x-4x）、重置按钮；
          - 播放8位风格的背景音乐（如《俄罗斯方块》的轻快旋律）。

    2.  **初始状态**：
          - 时间轴第一个关卡高亮（绿色），数据面板显示初始状态(p0=0, c0=0)；
          - 小卫士（像素角色）站在第一个关卡前，准备挑战。

    3.  **验证过程**（单步播放为例）：
          - 点击“单步”，读取第一个关卡的(p1, c1)；
          - **条件1验证**：数据面板用红色框圈住c1，若c1 > p1，红色闪烁并播放“咚”音效，关卡失败；否则绿色勾标记；
          - **条件2验证**：比较p1与p0（0）、c1与c0（0），若减少则红色闪烁，否则绿色勾；
          - **条件3验证**（i>0时）：计算增量Δp=p1-p0、Δc=c1-c0，若Δp < Δc，红色闪烁，否则绿色勾；
          - 所有条件通过后，小卫士移动到下一个关卡，时间轴对应关卡变为绿色。

    4.  **自动演示模式**：
          - 点击“自动播放”，小卫士自动挑战所有关卡，速度由滑块控制；
          - 遇到失败关卡时暂停，数据面板显示具体错误（如“c > p”）。

    5.  **胜利/失败状态**：
          - 所有关卡通过：小卫士到达时间轴终点，播放胜利音乐（如《超级马力欧》的通关音），屏幕显示“YES”；
          - 任意关卡失败：小卫士摔倒，播放失败音效，屏幕显示“NO”并高亮错误条件。

  * **旁白提示**：
      - （条件1验证前）“注意啦！通关次数不能超过游玩次数哦～”
      - （条件2验证时）“时间是向前的，游玩和通关次数不能变少～”
      - （条件3验证时）“每次玩至少可能不通关，所以通关增量不能超过游玩增量！”

<visualization_conclusion>
通过这样一个融合像素艺术和游戏化的动画，我们能直观看到每一步验证的逻辑，就像小卫士亲自闯关一样！这种方式不仅有趣，还能加深对条件约束的理解。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题的模拟验证思路后，我们可以将其迁移到其他需要按顺序验证条件的问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 本题的“按顺序验证多条件”思路，可用于：
        1. 验证序列的合法性（如温度记录是否符合递增且差值合理）；
        2. 检查游戏任务进度（如任务完成数是否随时间合理增长）；
        3. 审核财务报表（如收入和支出是否符合时间顺序约束）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P5736** - `质数筛`  
          * 🗣️ **推荐理由**：通过模拟筛法过程，练习按顺序验证数的性质，巩固“逐次检查”的思维。
    2.  **洛谷 P1059** - `明明的随机数`  
          * 🗣️ **推荐理由**：需要按顺序处理重复数并排序，锻炼数据处理和条件判断能力。
    3.  **洛谷 P1035** - `级数求和`  
          * 🗣️ **推荐理由**：按顺序计算级数，验证何时满足条件，适合练习循环和条件判断。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些对我们很有参考价值：
</insights_intro>

> **参考经验 (来自作者lingfunny)**：“一开始没考虑输入混乱的问题，直接在发现错误时输出`NO`，导致后面的测试数据读错。后来改用标记法，等所有数据输入完再判断，就解决了。”

> **点评**：这位作者的经验很实用！多组输入时，输入顺序的严格性非常重要。标记法是处理这类问题的常用技巧，它能避免因提前终止输入导致的数据错位。这提醒我们，在编写多组输入的程序时，一定要确保所有数据都被正确读取后再输出结果。

-----

<conclusion>
本次关于“Level Statistics”的C++解题分析就到这里。通过理解核心条件、学习优质题解和可视化演示，相信大家已经掌握了这类模拟验证问题的解决方法。记住，编程的关键在于逻辑清晰和细节处理，多练习多总结，你会越来越熟练！下次再见～ 💪
</conclusion>

---
处理用时：164.36秒