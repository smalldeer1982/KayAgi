# 题目信息

# Cat Party (Easy Edition)

## 题目描述

This problem is same as the next one, but has smaller constraints.

Shiro's just moved to the new house. She wants to invite all friends of her to the house so they can play monopoly. However, her house is too small, so she can only invite one friend at a time.

For each of the $ n $ days since the day Shiro moved to the new house, there will be exactly one cat coming to the Shiro's house. The cat coming in the $ i $ -th day has a ribbon with color $ u_i $ . Shiro wants to know the largest number $ x $ , such that if we consider the streak of the first $ x $ days, it is possible to remove exactly one day from this streak so that every ribbon color that has appeared among the remaining $ x - 1 $ will have the same number of occurrences.

For example, consider the following sequence of $ u_i $ : $ [2, 2, 1, 1, 5, 4, 4, 5] $ . Then $ x = 7 $ makes a streak, since if we remove the leftmost $ u_i = 5 $ , each ribbon color will appear exactly twice in the prefix of $ x - 1 $ days. Note that $ x = 8 $ doesn't form a streak, since you must remove exactly one day.

Since Shiro is just a cat, she is not very good at counting and needs your help finding the longest streak.

## 说明/提示

In the first example, we can choose the longest streak of $ 13 $ days, since upon removing the last day out of the streak, all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ will have the same number of occurrences of $ 3 $ . Note that the streak can also be $ 10 $ days (by removing the $ 10 $ -th day from this streak) but we are interested in the longest streak.

In the fourth example, if we take the streak of the first $ 6 $ days, we can remove the third day from this streak then all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ will occur exactly once.

## 样例 #1

### 输入

```
13
1 1 1 2 2 2 3 3 3 4 4 4 5
```

### 输出

```
13```

## 样例 #2

### 输入

```
5
10 2 5 4 1
```

### 输出

```
5```

## 样例 #3

### 输入

```
1
10
```

### 输出

```
1```

## 样例 #4

### 输入

```
7
3 2 1 1 4 5 1
```

### 输出

```
6```

## 样例 #5

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
5```

# AI分析结果



---
# 💡 Kay的C++算法解析：Cat Party (Easy Edition) 深入学习指南 💡

<introduction>
今天我们来一起分析“Cat Party (Easy Edition)”这道C++编程题。题目要求找到最长的前缀x，使得删除其中恰好一天后，剩下的所有颜色出现次数相同。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟与枚举` (结合动态统计与条件判断)

🗣️ **初步分析**：
解决这道题的关键在于**动态统计颜色出现次数**，并在每一步枚举当前前缀是否满足条件。简单来说，我们需要像“记账本”一样，记录每个颜色出现的次数（比如颜色3出现了5次），同时还要记录“出现次数”本身的分布（比如有多少个颜色出现了5次）。每处理一天的数据，就更新这些记录，并检查是否符合题目要求的三种情况。

- **题解思路**：所有优质题解的核心思路都是动态维护两个关键数组：`cnt[u]`（颜色u的出现次数）和`sum[c]`（出现次数为c的颜色数量）。每读入一个颜色，先更新这两个数组，再通过条件判断当前前缀是否满足以下任一情况：
  1. 所有颜色都只出现1次（如`[1,2,3,4]`）；
  2. 只有1个颜色出现1次，其余颜色出现次数相同（如`[1,2,2,3,3]`）；
  3. 有1个颜色出现次数比其他多1次（如`[1,1,2,2,3,3,3]`）。

- **核心难点**：如何高效维护`sum`数组，并在每一步快速判断是否满足条件。例如，当颜色u的出现次数从c变为c+1时，需要将`sum[c]`减1，`sum[c+1]`加1。

- **可视化设计思路**：采用8位像素风格的动画，用不同颜色的像素块代表不同颜色的猫。每加入一只猫（输入一个颜色），对应颜色的像素块“生长”（高度增加表示出现次数），同时右侧显示“次数统计栏”（用堆叠的小方块表示有多少颜色出现了k次）。关键步骤高亮（如当前处理的颜色块闪烁，次数统计变化时播放“叮”的音效）。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下3道题解因逻辑清晰、代码简洁且覆盖核心情况，值得重点学习：
</eval_intro>

**题解一：ikunTLE的题解 (来源：洛谷用户)**
* **点评**：此题解思路非常清晰，利用`cnt`数组记录颜色出现次数，`sum`数组记录次数的分布，每一步更新后通过4个条件快速判断是否满足要求。代码规范（如变量名`cnt`、`sum`含义明确），处理了特判情况（i=1），是典型的“模拟+枚举”解法，适合作为入门参考。

**题解二：_Fontainebleau_的题解 (来源：洛谷用户)**
* **点评**：此题解代码极其简洁，通过维护`mx`（当前最大出现次数）和`num`数组（次数的分布），直接判断三种核心情况。变量命名直观（如`mx`表示最大次数），逻辑紧凑，体现了对问题本质的深刻理解，适合进阶学习。

**题解三：dingzj2022的题解 (来源：洛谷用户)**
* **点评**：此题解结构清晰，将条件判断拆分为多个独立分支，代码可读性高。通过`max(mx, sum[a[i]])`动态更新最大次数，边界处理严谨（如i=1时直接返回1），适合理解条件判断的具体实现。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼出核心思考方向：
</difficulty_intro>

1.  **关键点1：动态维护颜色出现次数及其分布**
    * **分析**：每读入一个颜色，需要更新该颜色的出现次数（`cnt[u]++`），同时调整“次数的分布”（`sum[c]--`，`sum[c+1]++`）。例如，颜色u原本出现3次（`sum[3]`加过1），现在变为4次，需要将`sum[3]`减1，`sum[4]`加1。
    * 💡 **学习笔记**：维护两个数组`cnt`和`sum`是关键，前者记录“颜色→次数”，后者记录“次数→颜色数量”。

2.  **关键点2：快速判断是否满足题目条件**
    * **分析**：需要检查三种情况：
      - 所有颜色出现次数为1（`sum[1] == i`）；
      - 只有1个颜色出现1次，其余次数相同（`sum[1] == 1`且`sum[mx] * mx == i-1`）；
      - 有1个颜色次数多1，其余次数相同（`sum[mx] == 1`且`sum[mx-1] * (mx-1) + mx == i`）。
    * 💡 **学习笔记**：条件判断的核心是利用`sum`数组的当前状态，结合当前前缀长度i，验证是否符合三种模式。

3.  **关键点3：处理边界条件（如i=1）**
    * **分析**：当i=1时，只有1个颜色出现1次，直接满足条件。其他边界如所有颜色出现次数相同（如样例5中前5天，删除1个颜色后次数均为2）。
    * 💡 **学习笔记**：特判i=1，避免数组越界或逻辑错误。

### ✨ 解题技巧总结
- **动态统计**：用两个数组分别记录颜色次数和次数的分布，避免重复计算。
- **条件拆分**：将复杂条件拆分为三种可验证的子情况，简化判断逻辑。
- **边界特判**：处理i=1、所有颜色出现次数为1等特殊场景，确保代码鲁棒性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解的通用核心实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了ikunTLE和_Fontainebleau_的思路，结构清晰，覆盖所有条件，适合直接学习。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int N = 1e5 + 10;
    int cnt[N]; // cnt[u]：颜色u的出现次数
    int sum[N]; // sum[c]：出现次数为c的颜色数量
    int a[N];   // 输入的颜色序列

    int main() {
        int n;
        cin >> n;
        if (n == 1) { // 特判：只有1天
            cout << 1 << endl;
            return 0;
        }
        int ans = 0, mx = 0; // mx：当前最大出现次数
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            sum[cnt[a[i]]]--; // 旧次数对应的颜色数量减1
            cnt[a[i]]++;      // 颜色a[i]出现次数+1
            sum[cnt[a[i]]]++; // 新次数对应的颜色数量加1
            mx = max(mx, cnt[a[i]]); // 更新最大次数

            // 判断是否满足条件
            if (mx == 1) { // 所有颜色出现1次（如[1,2,3]）
                ans = i;
            } else if (sum[mx] * mx == i - 1) { // 1个颜色出现1次，其余次数相同（如[1,2,2,3,3]）
                ans = i;
            } else if (sum[mx - 1] * (mx - 1) + mx == i) { // 1个颜色次数多1（如[1,1,2,2,3,3,3]）
                ans = i;
            }
        }
        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取输入，特判n=1的情况。然后遍历每一天，动态更新`cnt`和`sum`数组。每一步计算当前最大出现次数`mx`，并通过三个条件判断当前前缀是否满足题目要求，更新答案`ans`。核心逻辑集中在条件判断部分，覆盖了所有可能的情况。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点和实现思路。
</code_intro_selected>

**题解一：ikunTLE的题解**
* **亮点**：代码简洁，通过`sum`数组直接统计次数的分布，条件判断覆盖所有情况。
* **核心代码片段**：
    ```cpp
    --sum[cnt[a[i]]], ++cnt[a[i]], ++sum[cnt[a[i]]];
    maxx = max(maxx, cnt[a[i]]);
    if (sum[i] == 1 || sum[1] == i || sum[1] == 1 && sum[maxx] * maxx == i - 1 || sum[maxx] == 1 && sum[maxx - 1] * (maxx - 1) + maxx == i)
        ans = i;
    ```
* **代码解读**：
    这部分代码首先更新`sum`和`cnt`数组（旧次数减1，新次数加1），然后更新最大次数`maxx`。条件判断中，`sum[i]==1`对应所有颜色出现i次（仅1个颜色）；`sum[1]==i`对应所有颜色出现1次；后两个条件分别对应“1个颜色出现1次”和“1个颜色次数多1”的情况。
* 💡 **学习笔记**：通过`sum`数组的状态直接验证条件，避免了复杂的遍历，时间复杂度O(n)。

**题解二：_Fontainebleau_的题解**
* **亮点**：代码极简，仅用两个数组实现，逻辑紧凑。
* **核心代码片段**：
    ```cpp
    num[cnt[x]++]--;
    num[cnt[x]]++;
    mx = max(mx, cnt[x]);
    if (mx == 1 || (num[mx - 1] + 1) * (mx - 1) == i - 1 || num[mx] * mx == i - 1)
        p = i;
    ```
* **代码解读**：
    `num[cnt[x]++]--`表示旧次数对应的颜色数减1，`num[cnt[x]]++`表示新次数对应的颜色数加1。`mx`动态更新最大次数。条件判断中，`mx==1`对应所有颜色出现1次；`(num[mx-1]+1)*(mx-1)==i-1`对应“1个颜色次数多1”；`num[mx]*mx==i-1`对应“1个颜色出现1次”。
* 💡 **学习笔记**：通过合并条件简化代码，体现了对问题本质的深刻理解。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解算法过程，我们设计一个“像素猫派对”动画，用8位复古风格展示每一天的颜色加入、次数更新和条件判断。
</visualization_intro>

  * **动画演示主题**：`像素猫派对：寻找最长完美前缀`

  * **核心演示内容**：模拟输入序列，每加入一只猫（颜色），对应颜色的像素柱“生长”（高度表示出现次数），右侧显示“次数统计栏”（堆叠的小方块表示有多少颜色出现了k次）。关键步骤高亮并播放音效。

  * **设计思路简述**：8位像素风格（如FC游戏画面）营造轻松氛围；颜色柱的动态生长直观展示次数变化；次数统计栏用不同颜色的小方块区分次数，帮助理解`sum`数组的含义；关键操作（如次数更新、条件满足）播放“叮”或“胜利”音效，强化记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕分为左右两部分：左半部分是“颜色柱区域”（每个颜色对应一个垂直像素柱），右半部分是“次数统计栏”（横向排列，每个格子表示出现次数k，堆叠的小方块数表示`sum[k]`）。
        - 控制面板：单步/自动播放按钮、速度滑块、重置按钮。

    2.  **逐天处理**：
        - 输入第i天的颜色（如颜色3），对应颜色柱（蓝色）底部出现一个像素块（高度+1），播放“滴答”音效。
        - 旧次数（假设颜色3之前出现2次）对应的次数统计栏（k=2的格子）的小方块减少1个（播放“咔嚓”音效）。
        - 新次数（k=3）对应的次数统计栏的小方块增加1个（播放“叮”音效）。
        - 更新最大次数mx（如从2变为3），用黄色箭头标注当前最大次数的格子。

    3.  **条件判断**：
        - 当满足条件（如所有颜色出现1次），颜色柱区域整体闪烁绿色，次数统计栏显示“完美前缀！”，播放“胜利”音效。
        - 不满足条件时，颜色柱区域保持原色，次数统计栏显示“继续加油~”。

    4.  **AI自动演示**：
        - 点击“AI演示”按钮，算法自动播放所有天数的处理过程，学习者可观察每一步的变化。

  * **旁白提示**：
    - “看！颜色3的柱子变高了，现在它出现3次啦~”
    - “次数统计栏里，k=2的格子少了一个方块，k=3的格子多了一个，这就是sum数组的变化哦！”
    - “当前前缀长度是5，检查是否满足条件...哇，满足！这就是我们要找的完美前缀~”

<visualization_conclusion>
通过这个动画，我们可以直观看到每一步的次数更新和条件判断，理解`cnt`和`sum`数组如何协同工作，轻松掌握算法核心。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以将“动态统计次数+条件判断”的思路迁移到更多问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 统计出现次数的问题（如“最长无重复子串”）。
      - 需要动态维护数据分布的问题（如“滑动窗口中的众数”）。
      - 条件判断依赖统计结果的问题（如“数组中出现次数超过一半的元素”）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1102** - `A-B数对`
          * 🗣️ **推荐理由**：需要统计元素出现次数，并利用次数计算符合条件的数对，练习`map`或数组的统计技巧。
    2.  **洛谷 P1908** - `逆序对`
          * 🗣️ **推荐理由**：需要动态统计元素出现次数（如归并排序中统计逆序对），练习分治与统计的结合。
    3.  **洛谷 P2602** - `数字计数`
          * 🗣️ **推荐理由**：需要统计每个数字在数位中的出现次数，练习数位DP与统计的结合。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如：
</insights_intro>

> **参考经验 (来自 ikunTLE)**：“最初忘记处理i=1的情况，导致样例3（输入1）输出错误。后来通过特判n=1解决了问题。”
>
> **点评**：这位作者的经验提醒我们，边界条件（如n=1、所有颜色出现1次）是容易出错的点。在编码时，应优先考虑这些特殊情况，通过测试用例验证代码的鲁棒性。

-----

<conclusion>
本次关于“Cat Party (Easy Edition)”的C++解题分析就到这里。希望这份指南能帮助大家理解动态统计与条件判断的核心思路，掌握解题技巧。记住，多动手调试、观察每一步的变量变化，是提升算法能力的关键！下次再见~ 💪
</conclusion>

-----

---
处理用时：141.06秒