# 题目信息

# Dominant Piranha

## 题目描述

There are $ n $ piranhas with sizes $ a_1, a_2, \ldots, a_n $ in the aquarium. Piranhas are numbered from left to right in order they live in the aquarium.

Scientists of the Berland State University want to find if there is dominant piranha in the aquarium. The piranha is called dominant if it can eat all the other piranhas in the aquarium (except itself, of course). Other piranhas will do nothing while the dominant piranha will eat them.

Because the aquarium is pretty narrow and long, the piranha can eat only one of the adjacent piranhas during one move. Piranha can do as many moves as it needs (or as it can). More precisely:

- The piranha $ i $ can eat the piranha $ i-1 $ if the piranha $ i-1 $ exists and $ a_{i - 1} < a_i $ .
- The piranha $ i $ can eat the piranha $ i+1 $ if the piranha $ i+1 $ exists and $ a_{i + 1} < a_i $ .

When the piranha $ i $ eats some piranha, its size increases by one ( $ a_i $ becomes $ a_i + 1 $ ).

Your task is to find any dominant piranha in the aquarium or determine if there are no such piranhas.

Note that you have to find any (exactly one) dominant piranha, you don't have to find all of them.

For example, if $ a = [5, 3, 4, 4, 5] $ , then the third piranha can be dominant. Consider the sequence of its moves:

- The piranha eats the second piranha and $ a $ becomes $ [5, \underline{5}, 4, 5] $ (the underlined piranha is our candidate).
- The piranha eats the third piranha and $ a $ becomes $ [5, \underline{6}, 5] $ .
- The piranha eats the first piranha and $ a $ becomes $ [\underline{7}, 5] $ .
- The piranha eats the second piranha and $ a $ becomes $ [\underline{8}] $ .

You have to answer $ t $ independent test cases.

## 说明/提示

The first test case of the example is described in the problem statement.

In the second test case of the example, there are no dominant piranhas in the aquarium.

In the third test case of the example, the fourth piranha can firstly eat the piranha to the left and the aquarium becomes $ [4, 4, 5, 4] $ , then it can eat any other piranha in the aquarium.

## 样例 #1

### 输入

```
6
5
5 3 4 4 5
3
1 1 1
5
4 4 3 4 4
5
5 5 4 3 2
3
1 1 2
5
5 4 3 5 5```

### 输出

```
3
-1
4
3
3
1```

# AI分析结果



---
# 💡 Kay的C++算法解析：Dominant Piranha 深入学习指南 💡

<introduction>
今天我们来一起分析“Dominant Piranha”这道C++编程题。这道题的关键在于找到一条能吃掉所有其他食人鱼的“主导者”。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`贪心策略应用`

🗣️ **初步分析**：
解决“Dominant Piranha”这道题，关键在于理解并运用贪心策略。贪心策略的核心思想是：每一步选择当前最优的局部解，最终得到全局最优解。就像吃零食时先挑最大的那一块，因为它更容易满足需求。在本题中，我们优先关注体积最大的食人鱼，因为它们最有可能通过吃相邻小鱼成为主导者。

- **题解思路**：所有优质题解的核心思路高度一致——先找到数组中的最大值 `mx`，然后检查是否存在一个位置 `i` 满足：`a[i] = mx` 且至少有一个邻居（左边或右边）的体积小于 `mx`。若存在这样的 `i`，则 `i` 就是答案；否则输出 `-1`。
- **核心难点**：如何快速定位到符合条件的最大值位置？关键在于遍历数组时，同时检查最大值的左右邻居是否更小。
- **可视化设计**：我们将设计一个8位像素风格的动画，用不同颜色的方块表示食人鱼（如红色代表最大值，蓝色代表较小值）。动画会高亮当前检查的最大值位置，并通过“吃小鱼”的动画（如小鱼方块消失，主导者方块变大）展示其如何逐步吃掉所有其他鱼。关键步骤（如发现符合条件的最大值、吃掉小鱼）会伴随“叮”的像素音效，增强操作记忆。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解（均≥4星）：
</eval_intro>

**题解一：作者 ttq012**
* **点评**：此题解逻辑清晰，代码结构工整。作者首先明确“最大值是关键”的核心思路，通过分类讨论边界情况（如第一个/最后一个元素是否为最大值且邻居更小）和中间元素，确保覆盖所有可能。代码中变量名 `mx` 直接表示最大值，`nlbl` 标签用于跳出循环，简洁高效。从实践角度看，代码边界处理严谨（如 `n=1` 的特殊情况），可直接用于竞赛。

**题解二：作者 Natsume_Rin**
* **点评**：此题解代码极其简洁，通过预定义 `a[0]` 和 `a[n+1]` 为最大值，简化了边界条件的判断。遍历数组时，直接检查每个最大值位置是否有邻居不等于最大值，逻辑直白。变量 `pd` 用于标记是否找到答案，可读性强。算法时间复杂度为 `O(tn)`，高效且易实现。

**题解三：作者 vectorwyx**
* **点评**：此题解结构清晰，函数 `work()` 封装了核心逻辑，代码模块化程度高。通过 `read()` 函数优化输入效率，符合竞赛编程习惯。关键逻辑（找最大值、检查邻居）在循环中一步完成，无冗余操作，是典型的竞赛风格代码。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个核心难点。结合优质题解的共性，我为大家提炼了思考方向和策略：
</difficulty_intro>

1.  **关键点1：确定“最大值是关键”的贪心策略**
    * **分析**：为什么优先考虑最大值？因为只有体积最大的食人鱼才有资格吃掉邻居（邻居体积必须更小）。若存在多个最大值，它们的邻居可能都是最大值，此时无法吃掉任何鱼，因此必须找到至少有一个邻居较小的最大值。
    * 💡 **学习笔记**：贪心的核心是抓住问题的“优势点”——本题中，体积越大的食人鱼越可能成为主导者。

2.  **关键点2：检查最大值的邻居是否更小**
    * **分析**：对于每个最大值位置 `i`，需要检查其左边（`i-1`）或右边（`i+1`）是否存在体积小于 `mx` 的食人鱼。若存在，则 `i` 可以先吃掉这个邻居，体积变为 `mx+1`，成为唯一的最大值，进而吃掉所有其他鱼。
    * 💡 **学习笔记**：邻居的“更小”是触发后续操作的关键条件，必须仔细检查。

3.  **关键点3：处理边界情况**
    * **分析**：当最大值位于数组两端（第一个或最后一个元素）时，只需检查其唯一的邻居是否更小。例如，第一个元素是最大值时，只需检查第二个元素是否小于它；最后一个元素同理。
    * 💡 **学习笔记**：边界情况往往是易错点，需单独处理。

### ✨ 解题技巧总结
- **技巧A：先找全局最大值**：通过 `max_element` 或遍历数组快速找到最大值 `mx`，缩小后续检查范围。
- **技巧B：简化边界判断**：预定义数组的 `a[0]` 和 `a[n+1]` 为 `mx`（如题解Natsume_Rin的做法），避免越界判断。
- **技巧C：提前终止循环**：找到符合条件的 `i` 后立即输出并跳出循环，避免不必要的计算。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先看一个综合优质题解思路的通用核心实现。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了多个优质题解的思路，逻辑清晰且覆盖所有边界情况，适合作为竞赛参考。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int a[300005];

    int main() {
        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            for (int i = 1; i <= n; ++i) cin >> a[i];
            if (n == 1) { // 特判：只有一条鱼
                cout << "1\n";
                continue;
            }
            int mx = *max_element(a + 1, a + n + 1); // 找最大值
            bool found = false;
            // 检查第一个元素
            if (a[1] == mx && a[2] < mx) {
                cout << "1\n";
                found = true;
            }
            // 检查最后一个元素
            else if (a[n] == mx && a[n - 1] < mx) {
                cout << n << "\n";
                found = true;
            }
            // 检查中间元素
            else {
                for (int i = 2; i < n; ++i) {
                    if (a[i] == mx && (a[i - 1] < mx || a[i + 1] < mx)) {
                        cout << i << "\n";
                        found = true;
                        break;
                    }
                }
            }
            if (!found) cout << "-1\n"; // 没找到符合条件的
        }
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先处理 `n=1` 的特殊情况，直接输出1。然后通过 `max_element` 找到数组最大值 `mx`。接着依次检查第一个元素、最后一个元素和中间元素是否为最大值且有邻居更小。若找到符合条件的位置则输出，否则输出 `-1`。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段，点出各自的亮点和关键思路。
</code_intro_selected>

**题解一：作者 ttq012**
* **亮点**：代码结构清晰，通过 `goto` 标签快速跳出循环，避免多层嵌套。
* **核心代码片段**：
    ```cpp
    else {
        for (int i = 2; i < n; i ++)
            if (a[i] == mx && (a[i + 1] != mx || a[i - 1] != mx)) {
                printf ("%d\n", i);
                goto nlbl;
            }
        puts("-1");
    }
    nlbl:;
    ```
* **代码解读**：
    这段代码处理中间元素的检查。当找到一个最大值位置 `i` 且其左右邻居不全为最大值时（即至少有一个更小），直接输出 `i` 并通过 `goto` 跳转到标签 `nlbl`，避免继续循环。这一设计简化了逻辑，提高了效率。
* 💡 **学习笔记**：`goto` 在竞赛中可用于快速跳出多层循环，但需注意代码可读性。

**题解二：作者 Natsume_Rin**
* **亮点**：预定义 `a[0]` 和 `a[n+1]` 为 `mx`，简化边界判断。
* **核心代码片段**：
    ```cpp
    a[0] = a[n+1] = maxn;
    for(RI i=1;i<=n;++i){
        if(a[i]==maxn&&(a[i+1]!=maxn||a[i-1]!=maxn)){
            printf("%d\n",i);
            pd=0;
            break;
        }
    }
    ```
* **代码解读**：
    作者将数组的首尾虚拟位置 `a[0]` 和 `a[n+1]` 设为最大值 `maxn`，这样在检查第一个元素（`i=1`）时，`a[i-1]` 就是 `a[0] = maxn`，若 `a[i+1] != maxn`（即第二个元素更小），则满足条件；同理，最后一个元素（`i=n`）的 `a[i+1]` 是 `a[n+1] = maxn`，若 `a[i-1] != maxn` 则满足条件。这种设计统一了边界和中间元素的判断逻辑。
* 💡 **学习笔记**：虚拟边界的设置可以简化条件判断，是竞赛中的常用技巧。

**题解三：作者 vectorwyx**
* **亮点**：函数封装核心逻辑，代码模块化。
* **核心代码片段**：
    ```cpp
    void work(){
        int n=read(),mx=-1,ans=-1;
        fo(i,1,n) a[i]=read(),mx=max(mx,a[i]);
        a[0]=a[n+1]=mx;
        fo(i,1,n) if(a[i]==mx&&(a[i-1]<a[i]||a[i+1]<a[i])){
            ans=i;
            break;
        }
        printf("%d\n",ans);
    }
    ```
* **代码解读**：
    函数 `work()` 封装了从输入到输出的所有步骤，结构清晰。通过 `read()` 函数快速读取输入，`fo` 宏简化循环写法。关键逻辑在循环中一步完成：遍历所有元素，找到第一个符合条件的最大值位置。
* 💡 **学习笔记**：模块化代码能提高可读性和复用性，适合复杂问题。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“如何找到主导食人鱼”，我设计了一个8位像素风格的动画演示方案，让我们“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素食人鱼大冒险`（复古FC风格）

  * **核心演示内容**：展示算法如何找到最大值，并检查其邻居是否更小，最终确定主导食人鱼的位置。

  * **设计思路简述**：采用8位像素风（如FC游戏《超级玛丽》的方块风格），用不同颜色区分食人鱼体积（红色方块表示最大值，蓝色表示较小值）。关键步骤（如找到最大值、检查邻居）通过高亮和音效强化记忆，游戏化的“过关”概念增加趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕显示像素化的水族箱，每个食人鱼用16x16像素方块表示，颜色根据体积渐变（如蓝色→绿色→红色，红色为最大值）。
          * 控制面板包含“开始/暂停”“单步”“重置”按钮和速度滑块（1-5倍速）。
          * 播放8位风格的轻快背景音乐（类似《俄罗斯方块》BGM）。

    2.  **找最大值**：
          * 算法开始时，所有食人鱼方块闪烁白色，随后一个黄色箭头从左到右扫描，停在最大值位置（红色方块），伴随“滴”的音效。
          * 最大值 `mx` 显示在屏幕上方，如“当前最大值：5”。

    3.  **检查邻居**：
          * 黄色箭头移动到当前最大值位置，检查其左右邻居：
            - 若邻居是蓝色（体积更小），邻居方块闪烁绿色，箭头指向邻居，播放“叮”的音效，表示“可以吃！”。
            - 若邻居是红色（体积相同），邻居方块闪烁灰色，音效“嗒”表示“不能吃”。
          * 找到符合条件的最大值位置后，该位置的红色方块变大（1.5倍）并闪烁金色，播放“胜利”音效（如《超级玛丽》吃金币声）。

    4.  **模拟吃鱼过程**（可选AI自动演示）：
          * 点击“AI演示”，主导食人鱼开始吃鱼：先吃掉较小的邻居（邻居方块消失，主导者体积+1，颜色变亮），然后依次吃掉其他鱼，最终水族箱只剩一个金色大方块，显示“成功！”。

    5.  **无主导者情况**：
          * 若所有最大值的邻居都是红色（体积相同），所有方块变为灰色，播放“呜”的失败音效，屏幕显示“-1”。

  * **旁白提示**：
      - “看！黄色箭头正在找最大的食人鱼～”
      - “这个红色方块是最大值，检查它左边和右边有没有蓝色的小鱼～”
      - “找到啦！这个红色方块可以吃蓝色小鱼，它就是主导者！”

<visualization_conclusion>
通过这样的像素动画，我们不仅能看到算法如何找到主导食人鱼，还能在轻松的游戏氛围中理解贪心策略的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以思考贪心策略在其他问题中的应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 贪心策略常用于“找最优局部解”的问题，例如：活动选择（选结束最早的活动）、区间覆盖（选覆盖最远的区间）、硬币问题（选面值最大的硬币）等。本题的关键是找到“体积最大且有邻居更小”的食人鱼，类似地，其他问题可能需要找到“最符合某条件”的元素。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1090** - `合并果子`
          * 🗣️ **推荐理由**：经典贪心题，需要每次选最小的两堆合并，与本题“找最优局部解”的思路类似，能巩固贪心策略的应用。
    2.  **洛谷 P1223** - `排队接水`
          * 🗣️ **推荐理由**：通过排序使总等待时间最小，需要理解“局部最优→全局最优”的贪心逻辑，适合拓展思维。
    3.  **洛谷 P2240** - `硬币问题`
          * 🗣️ **推荐理由**：在硬币面值满足贪心性质时，每次选最大面值，与本题“优先选最大值”的思路相似，可加深对贪心条件的理解。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了解题时的经验，这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自作者 ql12345)**：“这题做的时候真傻了，想了半天各种复杂做法，然后发现其实这么简单，导致D和E切得晚了...”
>
> **点评**：这位作者的经验提醒我们，遇到问题时要先观察其本质，避免过度复杂化。本题的关键是“最大值且有邻居更小”，抓住这一点就能快速解决。在编程竞赛中，“简化问题”往往比“复杂算法”更有效。

-----

<conclusion>
本次关于“Dominant Piranha”的C++解题分析就到这里。希望这份学习指南能帮助大家理解贪心策略的应用，并掌握此类问题的解题技巧。记住，多观察、多总结，编程能力会一步步提升！下次见～💪
</conclusion>

---
处理用时：136.50秒