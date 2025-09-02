# 题目信息

# Coffee and Coursework (Easy version)

## 题目描述

The only difference between easy and hard versions is the constraints.

Polycarp has to write a coursework. The coursework consists of $ m $ pages.

Polycarp also has $ n $ cups of coffee. The coffee in the $ i $ -th cup has $ a_i $ caffeine in it. Polycarp can drink some cups of coffee (each one no more than once). He can drink cups in any order. Polycarp drinks each cup instantly and completely (i.e. he cannot split any cup into several days).

Surely, courseworks are not usually being written in a single day (in a perfect world of Berland, at least). Some of them require multiple days of hard work.

Let's consider some day of Polycarp's work. Consider Polycarp drinks $ k $ cups of coffee during this day and caffeine dosages of cups Polycarp drink during this day are $ a_{i_1}, a_{i_2}, \dots, a_{i_k} $ . Then the first cup he drinks gives him energy to write $ a_{i_1} $ pages of coursework, the second cup gives him energy to write $ max(0, a_{i_2} - 1) $ pages, the third cup gives him energy to write $ max(0, a_{i_3} - 2) $ pages, ..., the $ k $ -th cup gives him energy to write $ max(0, a_{i_k} - k + 1) $ pages.

If Polycarp doesn't drink coffee during some day, he cannot write coursework at all that day.

Polycarp has to finish his coursework as soon as possible (spend the minimum number of days to do it). Your task is to find out this number of days or say that it is impossible.

## 说明/提示

In the first example Polycarp can drink fourth cup during first day (and write $ 1 $ page), first and second cups during second day (and write $ 2 + (3 - 1) = 4 $ pages), fifth cup during the third day (and write $ 2 $ pages) and third cup during the fourth day (and write $ 1 $ page) so the answer is $ 4 $ . It is obvious that there is no way to write the coursework in three or less days in this test.

In the second example Polycarp can drink third, fourth and second cups during first day (and write $ 4 + (2 - 1) + (3 - 2) = 6 $ pages) and sixth cup during second day (and write $ 4 $ pages) so the answer is $ 2 $ . It is obvious that Polycarp cannot write the whole coursework in one day in this test.

In the third example Polycarp can drink all cups of coffee during first day and write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) + (5 - 4) = 15 $ pages of coursework.

In the fourth example Polycarp cannot drink all cups during first day and should drink one of them during the second day. So during first day he will write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) = 14 $ pages of coursework and during second day he will write $ 5 $ pages of coursework. This is enough to complete it.

In the fifth example Polycarp cannot write the whole coursework at all, even if he will drink one cup of coffee during each day, so the answer is -1.

## 样例 #1

### 输入

```
5 8
2 3 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 10
1 3 4 2 1 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 15
5 5 5 5 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5 16
5 5 5 5 5
```

### 输出

```
2
```

## 样例 #5

### 输入

```
5 26
5 5 5 5 5
```

### 输出

```
-1
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Coffee and Coursework (Easy version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Coffee and Coursework (Easy version)”这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法（二分答案+贪心验证），并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：二分答案 + 贪心策略

🗣️ **初步分析**：
解决这道题的关键在于理解“最少天数”的单调性——如果用d天能完成，那么d+1天也一定能完成。这就像“试鞋”：如果穿37码的鞋刚好，那么38码肯定也能穿。我们可以用**二分法**快速找到最小的可行天数。同时，验证某个天数是否可行时，需要**贪心策略**（优先喝咖啡因高的咖啡）来最大化每日的总贡献。

- **题解思路**：多数优质题解采用“二分答案+贪心验证”框架。首先对咖啡因数组降序排序（大的咖啡因优先喝，减少损失），然后二分可能的天数d，用贪心计算d天内能完成的最大页数，若≥m则尝试更小的d，否则增大d。
- **核心难点**：如何设计高效的check函数验证给定天数d是否可行？关键是正确计算每杯咖啡在d天内的实际贡献（即每杯咖啡被分配到第k天的第t杯时，贡献为max(0, a_i - (t-1))）。
- **可视化设计**：用8位像素风展示排序后的咖啡（高咖啡因用亮黄色方块，低的用暗黄色），动画中模拟二分过程（左右指针移动），check函数执行时逐杯计算贡献（方块颜色随贡献值变化，如贡献≥0时变绿，否则变红），并累加总页数（顶部显示当前总和）。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选出以下4星以上题解：
</eval_intro>

**题解一：作者yaaaaaan**
* **点评**：此题解逻辑清晰，代码规范。二分框架完整，check函数通过`ceil(i/x)`巧妙计算每杯咖啡的“损失次数”（即被分配到第几天的第几个位置）。变量名如`a`（咖啡因数组）、`cnt`（总贡献）含义明确。亮点是将排序与二分结合，利用贪心思想最大化总贡献，时间复杂度O(n log n)，适合竞赛场景。

**题解二：作者信息学carryHarry**
* **点评**：此题解的check函数实现更直观（用`i`记录当前天数，`k`记录当天已喝的杯数），代码可读性强。二分过程中通过`ans`变量记录最小可行天数，边界处理严谨（最后判断`ans`是否为初始值）。适合新手理解二分+贪心的流程。

**题解三：作者Merge_all**
* **点评**：此题解在check函数中提前终止循环（当总贡献≥m时直接返回true），优化了常数时间。代码结构简洁，变量`L`、`R`表示二分区间，符合常规命名习惯。美中不足的是`mid`变量在check函数中未明确传递，需结合上下文理解，但整体仍为优质实现。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，我们常遇到以下关键点，结合优质题解的共性，总结策略如下：
</difficulty_intro>

1.  **关键点1：如何确定二分的上下界？**
    * **分析**：最少天数d的下界是1（所有咖啡一天喝完），上界是n（每天喝一杯）。若所有咖啡的总咖啡因和<m，直接返回-1（无解）。
    * 💡 **学习笔记**：二分的上下界需覆盖所有可能情况，本题中d的范围是[1, n]。

2.  **关键点2：如何设计check函数验证d天是否可行？**
    * **分析**：将咖啡降序排序后，第i杯咖啡（从1开始）在d天中的“损失次数”是`ceil(i/d) - 1`（即被分配到第k天的第t杯时，损失t-1次）。总贡献为所有`max(a_i - (损失次数), 0)`的和。若总和≥m，则d可行。
    * 💡 **学习笔记**：贪心策略的核心是“大咖啡因优先喝”，减少高价值咖啡的损失次数。

3.  **关键点3：如何优化check函数的计算？**
    * **分析**：优质题解通过数学公式`ceil(i/d)`快速计算损失次数，避免逐天模拟（如`i=1~n`时，损失次数为`(i-1)/d`）。例如，d=2时，i=1的损失次数是0（第1天第1杯），i=2的损失次数是0（第1天第2杯），i=3的损失次数是1（第2天第1杯），以此类推。
    * 💡 **学习笔记**：用数学公式替代循环模拟，可将check函数的时间复杂度从O(n²)优化到O(n)。

### ✨ 解题技巧总结
<summary_best_practices>
- **排序是贪心的前提**：降序排序确保高咖啡因咖啡优先被分配，减少总损失。
- **二分答案的本质**：利用问题的单调性（d越大，总贡献可能越小？不，d越小，每天喝的杯数越多，损失次数越多，总贡献可能越小。所以d越小越难满足条件，需找最小的可行d）。
- **边界条件处理**：总咖啡因和<m时直接返回-1，避免无效计算。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，选取yaaaaaan的代码作为通用核心实现，因其逻辑清晰且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了多个优质题解的思路，采用二分答案+贪心验证框架，时间复杂度O(n log n)，适合竞赛场景。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    #define int long long
    using namespace std;
    int n, m, sum;
    int a[200001];

    bool cmp(int x, int y) { return x > y; }

    bool check(int x) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            int loss = (i - 1) / x; // 等价于ceil(i/x)-1，计算损失次数
            cnt += max(a[i] - loss, 0LL);
            if (cnt >= m) return true; // 提前终止优化
        }
        return cnt >= m;
    }

    signed main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            sum += a[i];
        }
        if (sum < m) {
            cout << -1 << endl;
            return 0;
        }
        sort(a + 1, a + n + 1, cmp);
        int l = 1, r = n, ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取输入并计算总咖啡因和，若总和<m直接输出-1。否则将咖啡因数组降序排序，通过二分法寻找最小天数d。check函数计算d天内的总贡献：每杯咖啡i的损失次数为`(i-1)/d`（即被分配到第`(i-1)/d + 1`天的第`i - d*(i-1)/d`杯），贡献为`a[i] - 损失次数`（不小于0）。若总贡献≥m，说明d可行，尝试更小的d；否则增大d。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者yaaaaaan**
* **亮点**：用`(i-1)/x`替代`ceil(i/x)-1`，简化计算；提前终止check函数（当cnt≥m时直接返回true），优化常数。
* **核心代码片段**：
    ```cpp
    bool check(int x) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            int loss = (i - 1) / x;
            cnt += max(a[i] - loss, 0LL);
            if (cnt >= m) return true;
        }
        return cnt >= m;
    }
    ```
* **代码解读**：
    这段代码是check函数的核心。`x`是当前二分的天数d，`i`遍历排序后的咖啡因数组（降序）。`loss`计算第i杯咖啡的损失次数（即被分配到第几天的第几个位置，损失次数=天数-1）。例如，d=2时，i=1对应loss=0（第1天第1杯），i=2对应loss=0（第1天第2杯），i=3对应loss=1（第2天第1杯）。总贡献`cnt`累加每杯的有效贡献（≥0），若中途超过m则提前返回true，提升效率。
* 💡 **学习笔记**：数学公式`(i-1)/x`比`ceil(i/x)-1`更简洁，且避免浮点运算，减少误差。

**题解二：作者信息学carryHarry**
* **亮点**：用`i`记录当前天数，`k`记录当天已喝杯数，逻辑更直观。
* **核心代码片段**：
    ```cpp
    bool check(int x) {
        int i = 0, j = 0, k = 0;
        for (int s = 1; s <= n; s++) {
            k++;
            j += max(a[s] - i, 0LL);
            if (k >= x) {
                i++;
                k = 0;
            }
        }
        return j >= m;
    }
    ```
* **代码解读**：
    `x`是当前天数d，`i`是当前天数（从0开始），`k`是当天已喝杯数。每喝一杯（s循环），`k`加1，贡献为`a[s]-i`（第i+1天的第k杯，损失i次）。当`k>=x`时，天数i加1，k重置为0（进入下一天）。最后判断总贡献j是否≥m。
* 💡 **学习笔记**：这种逐天模拟的方式更易理解，适合新手掌握贪心分配的逻辑。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解二分+贪心的过程，我们设计一个“咖啡能量分配”的8位像素动画，模拟排序、二分查找和check验证的全流程。
</visualization_intro>

  * **动画演示主题**：像素咖啡屋的“最快写作业挑战”

  * **核心演示内容**：展示咖啡因数组降序排序（方块从高到低排列），二分查找最小天数d，check函数中每杯咖啡的贡献计算（方块颜色随贡献值变化），总页数累加至m的过程。

  * **设计思路简述**：8位像素风（红/黄/绿三色调）营造复古游戏感，通过颜色变化（贡献≥0时绿，否则红）和音效（“叮”声表示有效贡献）强化关键操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：
        - 屏幕左侧显示像素方块（代表咖啡，高度=咖啡因值，颜色=亮黄色），顶部显示总页数目标m（红色数字）。
        - 控制面板包含“开始”“暂停”“单步”按钮和速度滑块（1-5倍速）。

    2.  **排序动画**：
        - 方块从左到右自动降序排列（类似冒泡排序动画，交换时伴随“唰”的音效），最终排列为高→低。

    3.  **二分查找过程**：
        - 底部显示二分区间[L, R]（初始L=1，R=n），中间指针mid（黄色箭头）。点击“开始”后，mid自动计算，箭头指向mid位置（如mid=3）。

    4.  **check函数验证**（以mid=3为例）：
        - 第1天：前3杯咖啡（最高3个方块）依次被选中（蓝色边框闪烁），贡献分别为a[1]-0（绿）、a[2]-0（绿）、a[3]-0（绿），总页数累加（顶部数字动态增加）。
        - 第2天：接下来3杯咖啡，贡献为a[4]-1（绿）、a[5]-1（绿）、a[6]-1（红，若a[6]-1<0），总页数继续累加。
        - 每计算一杯，方块颜色变化（绿/红），伴随“叮”（有效）或“噗”（无效）音效。若总页数≥m，播放“胜利”音效（升调），否则继续。

    5.  **二分调整区间**：
        - 若check(mid)成功（总页数≥m），R=mid-1（箭头左移）；否则L=mid+1（箭头右移），直到L>R，找到最小d。

    6.  **结束状态**：
        - 最终d值显示在屏幕中央（金色字体），所有有效贡献的方块闪烁庆祝（绿色星光），播放“成功”BGM。

  * **旁白提示**：
    - （排序时）“先把咖啡因高的咖啡排前面，这样损失更少哦！”
    - （check时）“第1天喝前3杯，每杯贡献是原咖啡因值，因为是当天第1-3杯～”
    - （二分调整时）“如果3天能完成，试试更少的天数，比如2天？”

<visualization_conclusion>
通过这样的动画，我们能清晰看到二分如何快速缩小范围，以及贪心分配如何最大化总贡献。下次遇到类似问题，你也可以想象自己在玩这个像素游戏，一步步找到最优解！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的二分+贪心思路可迁移到许多“最小化最大值”或“最大化最小值”的问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 当问题要求“最少天数”“最少次数”等，且答案具有单调性时，二分法是首选。
    - 验证函数需结合贪心策略（如优先处理大值），确保计算高效。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1873 砍树**
          * 🗣️ **推荐理由**：同样用二分法找最大可砍高度，验证函数计算总木材量，与本题思路类似。
    2.  **洛谷 P2678 跳石头**
          * 🗣️ **推荐理由**：二分法找最小跳跃距离，验证函数计算需移除的石头数，贪心策略（保留最近石头）与本题异曲同工。
    3.  **洛谷 P3853 [TJOI2007]路标设置**
          * 🗣️ **推荐理由**：二分法找最大间距，验证函数计算需添加的路标数，贪心分配路标位置，适合巩固二分+贪心。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分，但可以总结：
</insights_intro>

> 调试时可打印check函数中的总贡献值，观察是否与预期一致。例如，当d=2时，总贡献是否正确计算每杯的损失次数？通过输出中间变量，能快速定位逻辑错误。

---

<conclusion>
本次关于“Coffee and Coursework (Easy version)”的C++解题分析就到这里。希望这份指南能帮助你掌握二分+贪心的核心思路，以及如何将算法转化为清晰的代码。记住，多动手调试、多思考贪心策略的合理性，是提升算法能力的关键！下次见～💪
</conclusion>

---
处理用时：154.52秒