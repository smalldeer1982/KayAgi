# 题目信息

# Coupons and Discounts

## 题目描述

The programming competition season has already started and it's time to train for ICPC. Sereja coaches his teams for a number of year and he knows that to get ready for the training session it's not enough to prepare only problems and editorial. As the training sessions lasts for several hours, teams become hungry. Thus, Sereja orders a number of pizzas so they can eat right after the end of the competition.

Teams plan to train for $ n $ times during $ n $ consecutive days. During the training session Sereja orders exactly one pizza for each team that is present this day. He already knows that there will be $ a_{i} $ teams on the $ i $ -th day.

There are two types of discounts in Sereja's favourite pizzeria. The first discount works if one buys two pizzas at one day, while the second is a coupon that allows to buy one pizza during two consecutive days (two pizzas in total).

As Sereja orders really a lot of pizza at this place, he is the golden client and can use the unlimited number of discounts and coupons of any type at any days.

Sereja wants to order exactly $ a_{i} $ pizzas on the $ i $ -th day while using only discounts and coupons. Note, that he will never buy more pizzas than he need for this particular day. Help him determine, whether he can buy the proper amount of pizzas each day if he is allowed to use only coupons and discounts. Note, that it's also prohibited to have any active coupons after the end of the day $ n $ .

## 说明/提示

In the first sample, Sereja can use one coupon to buy one pizza on the first and the second days, one coupon to buy pizza on the second and the third days and one discount to buy pizzas on the fourth days. This is the only way to order pizzas for this sample.

In the second sample, Sereja can't use neither the coupon nor the discount without ordering an extra pizza. Note, that it's possible that there will be no teams attending the training sessions on some days.

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
1 0 1
```

### 输出

```
NO
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Coupons and Discounts 深入学习指南 💡

<introduction>
今天我们来一起分析“Coupons and Discounts”这道C++编程题。这道题的关键在于理解两种优惠方式的使用规则，并通过贪心策略判断是否能恰好满足每天的披萨需求。本指南将帮助大家梳理题目思路，掌握核心算法，并通过可视化方案直观理解解题过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法（结合奇偶性判断）

🗣️ **初步分析**：
> 解决这道题的关键在于理解两种优惠方式的特点：  
> - 方式一（同一天买两个）：每次使用消耗当天2个披萨需求。  
> - 方式二（连续两天各买一个）：每次使用消耗当天和次日各1个披萨需求。  
> 可以比喻为“拆补游戏”：若某天需求为奇数，必须用方式二“借”一个披萨（影响次日需求）；若为偶数，则直接用方式一解决。核心是通过贪心策略逆推或正推调整每天的需求，确保最终所有需求被满足且无残留。  

   - **题解思路对比**：多数题解采用逆推或正推的贪心策略。逆推法从最后一天开始，若当天需求为奇数，则前一天需减少1（用方式二）；正推法跟踪前一天的“残留影响”（方式二带来的需求），动态调整当前需求。  
   - **核心算法流程**：以逆推法为例，从第n天到第2天遍历，若当天需求为奇数，则前一天需求减1（模拟方式二的使用）；最后检查第1天需求是否为偶数（否则无法用方式一满足）。  
   - **可视化设计思路**：用8位像素风格展示每天的披萨需求（像素方块堆叠），奇数天用红色高亮，触发方式二时用绿色箭头连接当天与前一天，动态调整方块数量，关键步骤（如奇偶变化）伴随“叮”的音效。


## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑简洁、实现高效被选为优质参考：
</eval_intro>

**题解一：逆推贪心法（作者：chenyanbo123）**
* **点评**：此题解思路清晰，采用逆推法从最后一天开始处理。代码简洁规范（如变量`a[i]`直接表示每天需求），关键步骤（奇数调整、负数判断）处理严谨。逆推逻辑贴合题目“方式二不能残留到第n天后”的约束，实践价值高，适合竞赛场景。

**题解二：正推残留跟踪法（作者：_Aoi_）**
* **点评**：此题解通过`pizza`变量跟踪前一天方式二的残留影响，正推处理每天需求。代码极简（仅需一次遍历），变量命名直观（`pizza`明确表示残留），对边界条件（如第n天奇数需求、某天需求为0但有残留）的判断精准，是贪心策略的高效实现。

**题解三：奇偶状态标记法（作者：lsr1409111459）**
* **点评**：此题解通过`flag`标记是否存在未完成的方式二残留，逻辑巧妙。代码仅需一次遍历，时间复杂度O(n)，空间复杂度O(1)，是最简洁的实现之一。对样例2的边界（需求为0但有残留）处理准确，适合快速理解核心逻辑。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心在于处理方式二的“跨天影响”，以下是三个关键难点及应对策略：
</difficulty_intro>

1.  **关键点1：如何处理奇数需求的“跨天调整”？**
    * **分析**：若某天需求为奇数，必须用方式二（借一个披萨），这会导致前一天（逆推）或后一天（正推）的需求减1。例如，逆推法中，第i天需求为奇数时，第i-1天需求减1（模拟方式二的使用）。  
    * 💡 **学习笔记**：奇数需求是触发方式二的信号，需通过调整相邻天的需求来“平衡”。

2.  **关键点2：如何避免需求变为负数？**
    * **分析**：调整需求时（如逆推中第i-1天减1），若结果为负，说明无法满足需求（例如样例2中第2天需求为0，但前一天调整后变为-1）。需在代码中及时判断并输出“NO”。  
    * 💡 **学习笔记**：负数需求是无效的，遇到时直接终止判断。

3.  **关键点3：如何确保第n天后无残留？**
    * **分析**：方式二不能在第n天使用（否则残留到第n+1天），因此第n天的需求必须为偶数（逆推法中最后检查第1天是否为偶数；正推法中检查最终残留是否为0）。  
    * 💡 **学习笔记**：最后一天的需求奇偶性是最终判断的关键。

### ✨ 解题技巧总结
- **逆推/正推选择**：逆推更直观（从最后一天开始，避免残留问题），正推更简洁（仅需一次遍历）。  
- **奇偶性敏感**：所有操作围绕奇偶性展开，需特别关注奇数需求的调整。  
- **边界条件优先**：提前判断负数需求、第n天残留等边界，避免后续无效计算。


## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，结合了逆推法的清晰逻辑和正推法的高效性：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合逆推法和正推法的优点，采用逆推法处理奇数需求，确保无残留，逻辑清晰且易于调试。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    using namespace std;

    const int MAX_N = 200005;
    int a[MAX_N];

    int main() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        // 逆推处理奇数需求
        for (int i = n; i >= 2; --i) {
            if (a[i] < 0) { // 提前判断负数需求
                cout << "NO" << endl;
                return 0;
            }
            if (a[i] % 2 == 1) { // 奇数需求，前一天减1（方式二）
                a[i - 1]--;
            }
        }
        // 检查第一天是否为偶数（可全部用方式一）
        if (a[1] % 2 == 1) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取每天的披萨需求，然后从最后一天逆推处理。若当天需求为奇数，则前一天需求减1（模拟方式二的使用）。过程中若出现负数需求，直接输出“NO”。最后检查第一天需求是否为偶数（偶数可用方式一满足），输出结果。

---

<code_intro_selected>
接下来分析优质题解的核心代码片段，理解不同实现的巧妙之处：
</code_intro_selected>

**题解一：逆推贪心法（作者：chenyanbo123）**
* **亮点**：逆推逻辑直接，代码简洁，边界条件（负数判断）处理严谨。
* **核心代码片段**：
    ```cpp
    for(int i=n;i>=2;i--){
        if(a[i]<0){ 
            cout<<"NO";
            return 0;
        }
        if(a[i]%2==1)a[i-1]--;
    }
    if(a[1]%2==1)cout<<"NO";
    else cout<<"YES";
    ```
* **代码解读**：  
  逆推循环从第n天到第2天，若当天需求为奇数（`a[i]%2==1`），则前一天需求减1（`a[i-1]--`）。若处理过程中某一天需求为负（`a[i]<0`），直接输出“NO”。最后检查第1天需求是否为偶数，决定输出。  
  *为什么逆推？* 因为方式二不能残留到第n天后，逆推确保第n天的需求被完全处理，避免残留。
* 💡 **学习笔记**：逆推法是处理“跨天影响”类问题的常用技巧，能直观避免后续残留。

**题解二：正推残留跟踪法（作者：_Aoi_）**
* **亮点**：仅用一个变量`pizza`跟踪残留，代码极简，时间复杂度O(n)。
* **核心代码片段**：
    ```cpp
    int pizza = 0; // 前一天用方式二的残留
    for(int i=1;i<=n;i++){
        if(a[i]==0&&pizza==1){ // 当天需求为0但有残留，无法满足
            cout<<"NO";
            return 0;
        }
        if(i==n&&(a[i]-pizza)%2==1){ // 最后一天残留后为奇数，无法满足
            cout<<"NO";
            return 0;
        }
        pizza=(a[i]-pizza)%2; // 更新残留（当前需求-残留后的奇偶性）
    }
    cout<<"YES";
    ```
* **代码解读**：  
  `pizza`表示前一天方式二带来的残留需求（0或1）。当天需求需先减去残留（`a[i]-pizza`），若结果为奇数，则当前残留变为1（需用方式二影响下一天）；否则残留为0。若当天需求为0但残留为1（无法用方式一满足），或最后一天残留后为奇数（无法用方式一满足），输出“NO”。  
  *为什么用`(a[i]-pizza)%2`？* 因为方式二的使用会改变残留的奇偶性，取模后直接得到新的残留状态。
* 💡 **学习笔记**：用奇偶性状态跟踪残留，是贪心策略的高效实现，适合处理线性递推问题。


## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解逆推法的处理过程，我们设计一个“像素披萨店”动画，用8位风格模拟每天的需求调整和方式二的使用。
</visualization_intro>

  * **动画演示主题**：像素披萨店的“奇偶调整”之旅  
  * **核心演示内容**：逆推处理每天的披萨需求，奇数天触发方式二（绿色箭头连接前一天），动态调整需求方块数量，最终检查第一天是否为偶数。  
  * **设计思路简述**：8位像素风格（FC游戏画面）营造轻松氛围，用不同颜色标记奇数（红色）、偶数（蓝色）需求，绿色箭头表示方式二的跨天影响。音效（“叮”）强化关键操作记忆，小关卡（每处理一天）增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕左侧显示n个像素方块列（每列高度为a_i），代表每天的披萨需求；右侧显示控制面板（开始/暂停、单步、重置按钮，速度滑块）。  
        - 播放8位风格背景音乐（如《超级玛丽》经典旋律）。

    2.  **逆推启动**：  
        - 从第n天（最右侧列）开始，用黄色箭头指向当前处理天。  
        - 若当前天需求为奇数（红色方块），播放“叮”音效，绿色箭头向左延伸（连接前一天），前一天方块高度减1（动画：方块缩小一格）。

    3.  **负数检测**：  
        - 若某一天方块高度变为负数（红色闪烁），播放“失败”音效，弹出文字提示“需求负数，无法满足！”。

    4.  **最终检查**：  
        - 处理完所有天后，检查第1天方块高度是否为偶数（蓝色闪烁），若是则播放“胜利”音效，弹出“YES”；否则红色闪烁，弹出“NO”。

    5.  **交互控制**：  
        - 支持单步执行（逐天查看调整过程）、自动播放（调速滑块控制速度）、重置（重新初始化需求）。

  * **旁白提示**：  
    - “现在处理第4天，需求是2（蓝色），偶数，不需要调整～”  
    - “第3天需求是1（红色），奇数！需要用方式二，前一天（第2天）需求减1～”  
    - “第1天需求是1（红色），奇数，无法用方式一满足，输出NO！”

<visualization_conclusion>
通过这样的动画，我们可以直观看到逆推法如何调整每天的需求，理解奇数需求如何触发方式二，以及最终如何判断是否满足条件。
</visualization_conclusion>


## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是贪心策略结合奇偶性判断，这类思路可迁移到多种“跨天/跨步骤调整”问题中：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 调整类问题（如资源分配、任务调度）：通过贪心策略调整相邻步骤的资源，确保每一步满足条件。  
    - 奇偶性判断（如硬币翻转、灯的开关）：利用奇偶性简化状态跟踪，避免复杂模拟。  
    - 边界条件处理（如最后一步限制）：提前判断关键边界，避免无效计算。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1208 [USACO1.3] 混合牛奶**  
        * 🗣️ **推荐理由**：贪心策略的基础应用，学习如何通过排序和贪心选择最优解。  
    2.  **洛谷 P1094 纪念品分组**  
        * 🗣️ **推荐理由**：贪心策略在分组问题中的应用，需结合奇偶性处理边界。  
    3.  **洛谷 P1803 凌乱的yyy / 线段覆盖**  
        * 🗣️ **推荐理由**：贪心策略在区间覆盖中的应用，学习如何选择最优区间序列。  


## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自 lsr1409111459)**：“这道题被困在了冗长的题面里。题目难度不高，可以说是贪心，但更多其实是模拟？要注意的是特判，幸亏有样例 #2 ，否则必 WA 一次并调试十分钟以上。”  
> **点评**：这位作者的经验提醒我们，阅读题面时要抓住关键条件（如“第n天后不能有残留”），并通过样例验证边界条件。遇到问题时，样例是调试的最佳工具！


<conclusion>
本次关于“Coupons and Discounts”的C++解题分析就到这里。通过理解贪心策略和奇偶性判断的核心，结合可视化动画，相信大家能更轻松地掌握这类问题的解法。记住，多动手调试、多分析样例，是提升编程能力的关键！下次见～💪
</conclusion>

---
处理用时：120.35秒