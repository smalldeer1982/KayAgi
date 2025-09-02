# 题目信息

# Equalize Prices

## 题目描述

There are $ n $ products in the shop. The price of the $ i $ -th product is $ a_i $ . The owner of the shop wants to equalize the prices of all products. However, he wants to change prices smoothly.

In fact, the owner of the shop can change the price of some product $ i $ in such a way that the difference between the old price of this product $ a_i $ and the new price $ b_i $ is at most $ k $ . In other words, the condition $ |a_i - b_i| \le k $ should be satisfied ( $ |x| $ is the absolute value of $ x $ ).

He can change the price for each product not more than once. Note that he can leave the old prices for some products. The new price $ b_i $ of each product $ i $ should be positive (i.e. $ b_i > 0 $ should be satisfied for all $ i $ from $ 1 $ to $ n $ ).

Your task is to find out the maximum possible equal price $ B $ of all productts with the restriction that for all products the condiion $ |a_i - B| \le k $ should be satisfied (where $ a_i $ is the old price of the product and $ B $ is the same new price of all products) or report that it is impossible to find such price $ B $ .

Note that the chosen price $ B $ should be integer.

You should answer $ q $ independent queries.

## 说明/提示

In the first example query you can choose the price $ B=2 $ . It is easy to see that the difference between each old price and each new price $ B=2 $ is no more than $ 1 $ .

In the second example query you can choose the price $ B=6 $ and then all the differences between old and new price $ B=6 $ will be no more than $ 2 $ .

In the third example query you cannot choose any suitable price $ B $ . For any value $ B $ at least one condition out of two will be violated: $ |1-B| \le 2 $ , $ |6-B| \le 2 $ .

In the fourth example query all values $ B $ between $ 1 $ and $ 7 $ are valid. But the maximum is $ 7 $ , so it's the answer.

## 样例 #1

### 输入

```
4
5 1
1 1 2 3 1
4 2
6 4 8 5
2 2
1 6
3 5
5 2 5
```

### 输出

```
2
6
-1
7
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Equalize Prices 深入学习指南 💡

<introduction>
今天我们来一起分析“Equalize Prices”这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。通过分析不同题解的亮点与不足，我们还会提炼出最严谨的解法，并设计一个有趣的像素动画来直观展示算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学（区间交集的最大值计算）

🗣️ **初步分析**：
解决“Equalize Prices”这道题，关键在于理解每个价格的调整范围，并找到所有调整范围的交集的最大值。简单来说，每个价格 \( a_i \) 可以调整到区间 \([ \max(a_i - k, 1), a_i + k ]\)（因为新价格 \( B \) 必须为正整数）。我们需要找到所有这样的区间的交集，如果交集存在，最大的 \( B \) 就是交集的右端点；否则输出 \(-1\)。

- **题解思路对比**：  
  多数题解通过两种思路解决：  
  1. 计算数组的最大值 \( \text{maxa} \) 和最小值 \( \text{mina} \)，若 \( \text{maxa} - \text{mina} > 2k \) 则无解，否则 \( B = \text{mina} + k \)（但未处理 \( B \leq 0 \) 的情况）。  
  2. 直接计算每个数的调整区间 \([ \max(a_i - k, 1), a_i + k ]\)，取所有左端点的最大值 \( L \) 和右端点的最小值 \( R \)，若 \( L \leq R \) 则 \( B = R \)，否则无解（更严谨，处理了 \( B > 0 \) 的条件）。  
  第二种思路更全面，能避免 \( B \) 为负数的错误。

- **核心算法流程**：  
  遍历每个价格，更新全局的 \( L \)（左端点最大值）和 \( R \)（右端点最小值）。最后判断 \( L \leq R \)，若成立则 \( B = R \)，否则无解。

- **可视化设计**：  
  采用8位像素风格，用水平进度条表示每个价格的调整区间（绿色为左端点，红色为右端点）。动画中，所有区间条会逐渐合并，最终展示 \( L \)（左边界）和 \( R \)（右边界）的位置，若重叠则 \( R \) 闪烁表示答案，否则显示“无解”。关键步骤（如更新 \( L \) 和 \( R \)）伴随“叮”的像素音效，增强操作记忆。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码严谨性、算法有效性的综合评估，以下题解因逻辑完整、处理边界条件严谨而被选为优质参考。
</eval_intro>

**题解一：作者：decoqwq**
* **点评**：  
  此题解直接计算每个价格的调整区间，通过维护左端点的最大值 \( L \) 和右端点的最小值 \( R \) 来判断交集是否存在。代码中显式处理了 \( B > 0 \) 的条件（左端点取 \( \max(a_i - k, 1) \)），避免了 \( B \) 为负数的错误。变量名 \( l \) 和 \( r \) 含义明确，逻辑简洁高效（时间复杂度 \( O(n) \)），是本题最严谨的解法。

**题解二：作者：knsg251**
* **点评**：  
  此题解思路与decoqwq一致，通过计算每个价格的左端点（\( \max(a_i - k, 1) \)）和右端点（\( a_i + k \)），并维护全局的 \( maxn \)（左端点最大值）和 \( minn \)（右端点最小值）。虽然变量名 \( maxn \) 和 \( minn \) 稍显模糊，但逻辑正确，边界处理到位，适合作为辅助参考。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼核心思考方向和策略：
</difficulty_intro>

1.  **关键点1：确定每个价格的调整区间**  
    * **分析**：每个价格 \( a_i \) 的调整范围是 \( [a_i - k, a_i + k] \)，但 \( B \) 必须为正整数，因此实际区间应为 \( [\max(a_i - k, 1), a_i + k] \)。若忽略 \( \max(a_i - k, 1) \)，可能导致 \( B \) 为负数的错误（例如 \( a_i = 0, k = 0 \) 时，\( B \) 需 \( >0 \)，此时无解）。  
    * 💡 **学习笔记**：边界条件（如 \( B > 0 \)）需显式处理，避免逻辑漏洞。

2.  **关键点2：计算所有区间的交集**  
    * **分析**：所有区间的交集由左端点的最大值 \( L \) 和右端点的最小值 \( R \) 决定。若 \( L \leq R \)，则交集为 \( [L, R] \)，最大 \( B \) 为 \( R \)；否则无解。  
    * 💡 **学习笔记**：交集的左边界是所有左端点的最大值，右边界是所有右端点的最小值。

3.  **关键点3：避免错误的最大值判断**  
    * **分析**：部分题解直接通过 \( \text{maxa} - \text{mina} \leq 2k \) 判断是否有解，并输出 \( \text{mina} + k \)，但未考虑 \( \text{mina} + k \leq 0 \) 的情况（如 \( \text{mina} = -5, k = 3 \)，此时 \( \text{mina} + k = -2 \) 不满足 \( B > 0 \)）。  
    * 💡 **学习笔记**：必须结合 \( B > 0 \) 的条件，通过区间交集判断最终结果。

### ✨ 解题技巧总结
- **区间交集法**：将每个数的调整范围转化为区间，通过维护左端点最大值和右端点最小值，快速判断交集是否存在。  
- **边界条件优先**：处理 \( B > 0 \) 时，左端点需取 \( \max(a_i - k, 1) \)，避免 \( B \) 为负数。  
- **变量名清晰性**：使用 \( L \)（左端点最大值）、\( R \)（右端点最小值）等明确的变量名，提升代码可读性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，先来看一个能够完整解决本题的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了decoqwq和knsg251的思路，显式处理 \( B > 0 \) 的条件，逻辑简洁且严谨。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        int t;
        cin >> t;
        while (t--) {
            int n, k;
            cin >> n >> k;
            int L = 0, R = INT_MAX; // L是左端点最大值，R是右端点最小值
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                // 左端点是max(x - k, 1)
                L = max(L, max(x - k, 1));
                // 右端点是x + k
                R = min(R, x + k);
            }
            if (L <= R) {
                cout << R << endl;
            } else {
                cout << -1 << endl;
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取多组测试用例。对于每组用例，初始化 \( L \) 为0（左端点最大值的初始最小值），\( R \) 为极大值（右端点最小值的初始最大值）。遍历每个价格 \( x \)，更新 \( L \) 为当前左端点（\( \max(x - k, 1) \)）的最大值，\( R \) 为当前右端点（\( x + k \)）的最小值。最后判断 \( L \leq R \)，若成立则输出 \( R \)（最大可能的 \( B \)），否则输出 \(-1\)。

---
<code_intro_selected>
接下来，剖析优质题解中的核心代码片段，理解其亮点和关键思路。
</code_intro_selected>

**题解一：作者：decoqwq**
* **亮点**：代码简洁，显式处理 \( B > 0 \) 的条件，通过 \( L \) 和 \( R \) 直接判断区间交集。
* **核心代码片段**：
    ```cpp
    int l = 0, r = 0x3f3f3f3f;
    for(int i=1;i<=n;i++) {
        int x;
        scanf("%d",&x);
        r = min(r, x + k);
        l = max(l, ((x - k) > 0 ? (x - k) : 1));
    }
    if(l <= r) cout << r << endl;
    else cout << -1 << endl;
    ```
* **代码解读**：  
  - `l` 初始化为0（左端点的最小可能值），`r` 初始化为极大值（右端点的最大可能值）。  
  - 对于每个价格 \( x \)，更新 `r` 为当前右端点（\( x + k \)）的最小值（因为所有右端点的最小值是交集的右边界）。  
  - 更新 `l` 为当前左端点（\( \max(x - k, 1) \)）的最大值（所有左端点的最大值是交集的左边界）。  
  - 若 `l <= r`，说明交集存在，最大 \( B \) 是 `r`；否则无解。  
* 💡 **学习笔记**：通过维护两个变量 \( L \) 和 \( R \)，可以高效计算所有区间的交集，避免复杂的排序或遍历。

**题解二：作者：knsg251**
* **亮点**：思路与decoqwq一致，通过 `maxn`（左端点最大值）和 `minn`（右端点最小值）判断交集。
* **核心代码片段**：
    ```cpp
    int maxn = 0, minn = 999999999;
    for(int i=1;i<=n;i++) {
        scanf("%d",&a);
        minn = min(minn, a + k); // 右端点最小值
        if(a > k) cnt = a - k;
        else cnt = 1; // 左端点是max(a - k, 1)
        maxn = max(maxn, cnt); // 左端点最大值
    }
    if(minn < maxn) printf("-1\n");
    else printf("%d\n", minn);
    ```
* **代码解读**：  
  - `maxn` 初始化为0，`minn` 初始化为极大值。  
  - 遍历每个价格 \( a \)，更新 `minn` 为 \( a + k \) 的最小值（右端点最小值）。  
  - 计算当前左端点（若 \( a > k \) 则为 \( a - k \)，否则为1），更新 `maxn` 为左端点的最大值。  
  - 若 `maxn > minn`，交集不存在；否则最大 \( B \) 是 `minn`。  
* 💡 **学习笔记**：通过条件判断处理左端点的边界（\( a - k \) 可能小于1），确保 \( B > 0 \)。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解区间交集的计算过程，我们设计一个“像素区间探险家”动画，用8位复古风格展示每个价格的调整区间，并动态合并找到最大 \( B \)。
</visualization_intro>

  * **动画演示主题**：像素区间探险家  
  * **核心演示内容**：每个价格对应一个水平的像素条（绿色左端点，红色右端点），动画中所有条逐渐合并，最终展示交集的左边界 \( L \) 和右边界 \( R \)，若重叠则 \( R \) 闪烁表示答案，否则显示“无解”。

  * **设计思路简述**：  
    采用8位像素风格（FC红白机色调），用不同颜色区分区间端点，增强视觉记忆。关键步骤（如更新 \( L \) 和 \( R \)）伴随“叮”的音效，操作完成时播放“胜利”音效，增加趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕下方显示像素化的输入框（如“输入n和k”），上方是一个水平数轴（像素刻度）。  
        - 控制面板包含“单步”“自动播放”“重置”按钮和速度滑块（1-5倍速）。

    2.  **输入处理**：  
        - 输入n和k后，每个价格 \( a_i \) 以像素方块形式从输入框弹出，显示数值（如“5”）。

    3.  **区间绘制**：  
        - 每个价格 \( a_i \) 生成一个水平区间条：左端点为 \( \max(a_i - k, 1) \)（绿色方块），右端点为 \( a_i + k \)（红色方块），中间用黄色像素填充。  
        - 伴随“刷”的音效，区间条从中间展开。

    4.  **合并区间**：  
        - 动画逐步更新全局 \( L \)（左端点最大值）和 \( R \)（右端点最小值）：  
          - \( L \) 用蓝色箭头从左向右移动，指向所有绿色端点的最右位置。  
          - \( R \) 用紫色箭头从右向左移动，指向所有红色端点的最左位置。  
        - 每次更新 \( L \) 或 \( R \) 时，播放“叮”的音效。

    5.  **结果展示**：  
        - 若 \( L \leq R \)，数轴上 \( R \) 位置闪烁金色星星，播放“胜利”音效（如《超级玛丽》的金币声）。  
        - 若 \( L > R \)，所有区间条变为灰色，播放“失败”音效（短促的“咚”声），并显示“无解”文字。

  * **旁白提示**：  
    - “看！每个价格的调整区间像一条彩色的带子，绿色是左边界，红色是右边界～”  
    - “现在，蓝色箭头在找所有左边界的最大值，紫色箭头在找所有右边界的最小值～”  
    - “如果蓝色箭头没超过紫色箭头，说明有共同的价格！最大的那个就是紫色箭头的位置哦～”

<visualization_conclusion>
通过这个像素动画，我们能直观看到每个价格的调整范围如何影响最终的 \( B \)，轻松理解区间交集的计算逻辑！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以将“区间交集最大值”的思路迁移到更多问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    本题的核心是“多区间交集的最大值”，类似思路可用于：  
    - 会议安排问题（找到所有参会者的空闲时间段的交集）。  
    - 任务调度问题（确定所有任务的时间窗口的重叠部分）。  
    - 传感器覆盖问题（找到多个传感器覆盖区域的重叠范围）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1803 凌乱的yyy / 线段覆盖**  
        * 🗣️ **推荐理由**：练习区间覆盖的贪心算法，与本题的区间交集思路相关。  
    2.  **洛谷 P1047 校门外的树**  
        * 🗣️ **推荐理由**：通过区间覆盖问题，巩固对区间交集和并集的理解。  
    3.  **洛谷 P5736 【深基7.例2】质数筛**  
        * 🗣️ **推荐理由**：虽然是质数判断，但可练习边界条件处理（如最小值、最大值），与本题的严谨性要求类似。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分。但通过对比不同题解，我们可以总结：**边界条件的处理是编程的关键**（如本题的 \( B > 0 \)），忽略这些细节可能导致错误。建议在编码前先列出所有边界情况，确保逻辑覆盖全面。
</insights_intro>

-----

<conclusion>
本次关于“Equalize Prices”的C++解题分析就到这里。希望这份指南能帮助你掌握区间交集的计算方法，并学会如何严谨处理边界条件。记住，编程的魅力在于逻辑的严密性，多思考、多验证，你会越来越熟练！下次见～💪
</conclusion>

---
处理用时：227.91秒