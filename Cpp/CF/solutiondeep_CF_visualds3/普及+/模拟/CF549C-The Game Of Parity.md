# 题目信息

# The Game Of Parity

## 题目描述

There are $ n $ cities in Westeros. The $ i $ -th city is inhabited by $ a_{i} $ people. Daenerys and Stannis play the following game: in one single move, a player chooses a certain town and burns it to the ground. Thus all its residents, sadly, die. Stannis starts the game. The game ends when Westeros has exactly $ k $ cities left.

The prophecy says that if the total number of surviving residents is even, then Daenerys wins: Stannis gets beheaded, and Daenerys rises on the Iron Throne. If the total number of surviving residents is odd, Stannis wins and everything goes in the completely opposite way.

Lord Petyr Baelish wants to know which candidates to the throne he should support, and therefore he wonders, which one of them has a winning strategy. Answer to this question of Lord Baelish and maybe you will become the next Lord of Harrenholl.

## 说明/提示

In the first sample Stannis will use his move to burn a city with two people and Daenerys will be forced to burn a city with one resident. The only survivor city will have one resident left, that is, the total sum is odd, and thus Stannis wins.

In the second sample, if Stannis burns a city with two people, Daenerys burns the city with one resident, or vice versa. In any case, the last remaining city will be inhabited by two people, that is, the total sum is even, and hence Daenerys wins.

## 样例 #1

### 输入

```
3 1
1 2 1
```

### 输出

```
Stannis
```

## 样例 #2

### 输入

```
3 1
2 2 1
```

### 输出

```
Daenerys
```

## 样例 #3

### 输入

```
6 3
5 20 12 7 14 101
```

### 输出

```
Stannis
```

# AI分析结果



---
# 💡 Kay的C++算法解析：The Game Of Parity 深入学习指南 💡

<introduction>
今天我们来一起分析这道“The Game Of Parity”编程题。这道题看似是一个“屠城游戏”，实则是一场关于奇偶性的策略博弈。本指南将带大家梳理题目核心，理解博弈策略，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：博弈论与奇偶性分析

🗣️ **初步分析**：
解决这道题的关键在于理解“双方如何通过摧毁城市，最终控制剩余城市总人口的奇偶性”。博弈论的核心是“最优策略”——两位玩家都会选择对自己最有利的操作。而奇偶性分析则像一把钥匙，能帮我们快速判断最终结果。

简单来说，游戏的胜负由两个因素决定：
1. 剩余操作次数（即 `m = n - k`）的奇偶性（谁最后操作）。
2. 奇数、偶数人口的城市数量（因为摧毁偶数城市不改变总人口奇偶性，奇数城市才是关键）。

**题解思路对比**：
两个优质题解均围绕“统计奇偶城市数量”和“根据操作次数m的奇偶性分类讨论”展开。CASSINI_Thx的题解通过函数封装不同操作情况，233zhang的题解则更简洁直接，但核心逻辑一致。

**核心算法流程**：
- 统计奇数城市数（`odd`）和偶数城市数（`even`）。
- 计算操作次数 `m = n - k`。
- 根据 `m` 的奇偶性（最后操作玩家），结合 `odd` 和 `even` 的数量，判断最终总人口的奇偶性。

**可视化设计思路**：
我们将用8位像素风动画模拟游戏过程：用红色像素块表示奇数城市（影响奇偶性），蓝色表示偶数城市（不影响）。每一步操作时，当前玩家选择摧毁一个城市（像素块消失），并伴随“咔嚓”音效。最后剩余k个城市时，统计红色块数量的奇偶性，决定胜负（胜利时播放“叮”的上扬音效）。

---

## 2. 精选优质题解参考

<eval_intro>
经过评估，以下两道题解在思路清晰度、代码规范性和算法有效性上表现突出（均≥4星），值得参考：
</eval_intro>

**题解一：CASSINI_Thx的题解**
* **点评**：这道题解思路非常清晰，通过分类讨论操作次数的奇偶性（即最后操作玩家），并结合奇数/偶数城市的数量，逐步推导胜负条件。代码中使用函数封装不同操作情况（`xianshou()`和`houshou()`），结构工整；变量名`odd`（奇数城市数）、`even`（偶数城市数）含义明确，易于理解。特别值得学习的是对边界条件（如`m=0`）的严谨处理，以及通过预处理统计奇偶城市数的高效方法。

**题解二：233zhang的题解**
* **点评**：此题解代码简洁高效，直接通过逻辑判断完成胜负条件推导，没有冗余代码。变量命名规范（如`m`表示操作次数），关键步骤（如`m>>1`计算后手操作次数）注释清晰。对奇偶性判断的核心逻辑（如`(m>>1)>=odd`）处理巧妙，体现了对问题本质的深刻理解。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，我们需要突破以下核心难点：
</difficulty_intro>

1.  **关键点1**：如何确定“最后操作的玩家”？
    * **分析**：操作次数 `m = n - k` 的奇偶性决定了最后操作的玩家。若 `m` 是奇数（如3次操作），则先手（Stannis）最后操作；若 `m` 是偶数（如4次），则后手（Daenerys）最后操作。这一步是后续策略分析的基础。
    * 💡 **学习笔记**：操作次数的奇偶性直接决定“谁有最后一次决策权”，是博弈问题的关键突破口。

2.  **关键点2**：如何判断双方能否“控制”最终的奇偶性？
    * **分析**：奇数城市是影响结果的核心（偶数城市摧毁后不改变总人口奇偶性）。若后手能摧毁所有奇数城市（即后手操作次数 ≥ `odd`），则最终总人口必为偶数（Daenerys赢）。否则，先手可以保留至少一个奇数城市，控制结果。
    * 💡 **学习笔记**：奇数城市的数量是“胜负开关”，双方会优先摧毁对方的“开关”。

3.  **关键点3**：如何处理边界情况（如 `m=0`）？
    * **分析**：当 `m=0`（无需操作，直接剩k个城市），直接统计剩余城市总人口的奇偶性即可。若奇数城市数为奇数，Stannis赢；否则Daenerys赢。
    * 💡 **学习笔记**：边界情况常被忽略，但往往是解题的“陷阱”，需特别关注。

### ✨ 解题技巧总结
- **问题抽象**：将复杂的游戏规则抽象为“奇偶性控制问题”，抓住“奇数城市”这一核心变量。
- **分类讨论**：根据操作次数的奇偶性（最后操作玩家），分别分析双方的最优策略。
- **预处理统计**：提前统计奇数/偶数城市数，简化后续逻辑判断。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合两个优质题解的核心实现，逻辑清晰且覆盖所有情况：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了两个优质题解的思路，通过预处理统计奇偶城市数，结合操作次数的奇偶性判断胜负，逻辑简洁高效。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        int n, k, m;
        cin >> n >> k;
        m = n - k;
        int odd = 0, even = 0;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            if (a % 2 == 1) odd++;
            else even++;
        }

        if (m == 0) { // 无需操作，直接判断剩余城市的奇偶性
            cout << (odd % 2 == 1 ? "Stannis" : "Daenerys") << endl;
            return 0;
        }

        int half = m / 2; // 后手操作次数
        if (half >= odd) { // 后手能摧毁所有奇数城市，最终必为偶数
            cout << "Daenerys" << endl;
            return 0;
        }

        if (m % 2 == 1) { // 先手最后操作
            if (half >= even && (k % 2 == 0)) { // 后手能摧毁所有偶数城市且k为偶数
                cout << "Daenerys" << endl;
            } else {
                cout << "Stannis" << endl;
            }
        } else { // 后手最后操作
            if (half >= even && (k % 2 == 1)) { // 后手能摧毁所有偶数城市且k为奇数
                cout << "Stannis" << endl;
            } else {
                cout << "Daenerys" << endl;
            }
        }

        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取输入并统计奇数（`odd`）、偶数（`even`）城市数。若无需操作（`m=0`），直接判断剩余城市的奇偶性。否则，根据后手能否摧毁所有奇数城市（`half >= odd`）快速判断。若不能，则根据操作次数的奇偶性（最后操作玩家）和偶数城市的数量，决定最终胜负。

---
<code_intro_selected>
接下来，我们分析两个优质题解的核心代码片段：
</code_intro_selected>

**题解一（CASSINI_Thx）**
* **亮点**：通过函数封装不同操作情况（`xianshou()`和`houshou()`），代码结构清晰，便于维护。
* **核心代码片段**：
    ```cpp
    void xianshou() {
        if ((m>>1)>=odd) { // 后手操作次数≥奇数城市数
            printf("Daenerys\n");
            return;
        } 
        if ((m>>1)>=even && !(k&1)) { // 后手操作次数≥偶数城市数且k为偶数
            printf("Daenerys\n");
            return;
        }
        printf("Stannis\n");
    }
    ```
* **代码解读**：
    这段代码处理“先手最后操作”的情况。`m>>1`等价于`m/2`（后手操作次数）。若后手能摧毁所有奇数城市（`(m>>1)>=odd`），则Daenerys赢；否则，若后手能摧毁所有偶数城市且k为偶数，Daenerys仍赢；否则Stannis赢。这里的`k&1`是位运算判断奇偶，简洁高效。
* 💡 **学习笔记**：函数封装能让代码逻辑更清晰，尤其在分类讨论时。

**题解二（233zhang）**
* **亮点**：代码简洁，直接通过逻辑判断完成所有情况处理，无冗余。
* **核心代码片段**：
    ```cpp
    if ((m>>1)>=odd) {
        cout<<"Daenerys\n";return 0;
    }
    if (m&1) {
        if ((m>>1)>=even&&(!(k&1))) {cout<<"Daenerys\n";return 0;}
        cout<<"Stannis\n";
    }
    else {
        if ((m>>1)>=even&&(k&1)) {cout<<"Stannis\n";return 0;}
        cout<<"Daenerys\n";
    }
    ```
* **代码解读**：
    这段代码先判断后手能否摧毁所有奇数城市（`(m>>1)>=odd`）。若不能，则根据`m`的奇偶性（`m&1`）进入不同分支，结合偶数城市数和k的奇偶性，判断胜负。逻辑紧凑，一步到位。
* 💡 **学习笔记**：简洁的代码往往更高效，但需确保逻辑覆盖所有情况。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解双方如何通过摧毁城市控制奇偶性，我们设计了一个“像素屠城战”动画，用8位复古风格模拟游戏过程！
</visualization_intro>

  * **动画演示主题**：像素屠城战——奇偶大作战

  * **核心演示内容**：
    屏幕左侧是n个像素城市（红色=奇数，蓝色=偶数），右侧显示当前玩家（史坦尼斯/丹妮莉丝）、剩余操作次数（m）和最终目标（剩k个城市）。每一步操作时，玩家选择摧毁一个城市（像素块消失），伴随“咔嚓”音效。最后统计剩余城市的红色块数量，决定胜负（胜利时播放“叮”的上扬音效）。

  * **设计思路简述**：
    红色/蓝色像素块直观区分奇数/偶数城市，帮助学习者观察“奇数城市是如何影响结果的”。操作次数和当前玩家的实时显示，强化“谁最后操作”的关键逻辑。音效和动画反馈（如消失动画）增加趣味性，降低理解门槛。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：
        - 屏幕顶部用8位字体显示“THE GAME OF PARITY”，背景为淡蓝色（FC风格）。
        - 左侧排列n个像素块（红色/蓝色），每个块下方标注人口数（如“1”“2”）。
        - 右侧控制面板有“开始/暂停”“单步”“重置”按钮，速度滑块（1-5倍速）。

    2.  **操作演示**：
        - 史坦尼斯先操作：鼠标点击选择一个城市，对应像素块闪烁3次后消失，播放“咔嚓”音效。剩余操作次数m减1。
        - 丹妮莉丝操作：同理，像素块消失，音效提示。
        - 关键步骤高亮：当玩家摧毁奇数城市时，红色块消失的同时，屏幕右侧“奇数城市剩余数”数字跳动（如从3→2）。

    3.  **最终结果**：
        - 当剩余k个城市时，所有像素块停止操作，剩余城市的红色块数量自动统计（如“红色块数=1”）。
        - 若总数为奇数，史坦尼斯胜利：屏幕弹出“STANNIS WIN！”，播放8位风格胜利音乐；若为偶数，丹妮莉丝胜利，同理。

  * **旁白提示**：
    - “注意看，史坦尼斯选择了红色城市（奇数），这会改变最终总人口的奇偶性！”
    - “现在剩余操作次数是偶数，最后一步由丹妮莉丝完成~”
    - “红色块数为奇数，史坦尼斯获胜！”

<visualization_conclusion>
通过这个动画，我们可以直观看到每一步操作如何影响最终结果，尤其是奇数城市的关键作用。下次遇到类似问题时，你也能像“像素探险家”一样，快速抓住核心啦！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了这道题的奇偶性博弈策略后，我们可以尝试解决更多类似问题，巩固思路：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    本题的核心是“通过统计关键变量（如奇数城市数），结合操作次数的奇偶性判断胜负”。这种思路还适用于：
    - 取石子游戏（每次取1或2个，最后取完者胜）。
    - 硬币翻转问题（每次翻转奇数枚，最终状态判断）。
    - 棋盘覆盖问题（覆盖奇偶格子影响胜负）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1288** - 取数游戏II
        * 🗣️ **推荐理由**：涉及奇偶性和博弈策略，需分析每一步对最终结果的影响。
    2.  **洛谷 P1512** - 伊甸园日历游戏
        * 🗣️ **推荐理由**：通过日期的奇偶性判断胜负，与本题思路类似。
    3.  **洛谷 P4310** - 绝世好题
        * 🗣️ **推荐理由**：结合位运算和奇偶性分析，锻炼综合思维。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解作者CASSINI_Thx提到：“在解决这个问题时，我一开始忽略了`m=0`的情况，导致测试用例出错。后来通过仔细检查边界条件，才修正了错误。”
</insights_intro>

> **参考经验**：“处理边界条件（如`m=0`）时，一定要单独考虑，否则容易出错。”

**点评**：这位作者的经验非常实用！在编程中，边界条件（如输入为0、数组越界）往往是bug的高发区。通过提前列出所有可能的边界情况（如本题的`m=0`），并逐一测试，可以有效避免错误。这也是竞赛编程中“鲁棒性”的重要体现哦~

-----

<conclusion>
关于“The Game Of Parity”的分析就到这里啦！希望大家通过这篇指南，掌握了博弈论中奇偶性分析的技巧，也理解了如何用代码实现策略判断。记住，遇到类似问题时，先找“关键变量”（如本题的奇数城市数），再分析“操作次数的奇偶性”，就能快速找到突破口。下次见~ 💪
</conclusion>

---
处理用时：80.12秒