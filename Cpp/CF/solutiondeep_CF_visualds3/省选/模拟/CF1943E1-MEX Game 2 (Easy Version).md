# 题目信息

# MEX Game 2 (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ t $ , $ m $ and the sum of $ m $ . You can make hacks only if both versions of the problem are solved.

Alice and Bob play yet another game on an array $ a $ of size $ n $ . Alice starts with an empty array $ c $ . Both players take turns playing, with Alice starting first.

On Alice's turn, she picks one element from $ a $ , appends that element to $ c $ , and then deletes it from $ a $ .

On Bob's turn, he picks at most $ k $ elements from $ a $ , and then deletes it from $ a $ .

The game ends when the array $ a $ is empty. Alice's score is defined to be the MEX $ ^\dagger $ of $ c $ . Alice wants to maximize her score while Bob wants to minimize it. Find Alice's final score if both players play optimally.

The array will be given in compressed format. Instead of giving the elements present in the array, we will be giving their frequencies. Formally, you will be given $ m $ , the maximum element in the array, and then $ m + 1 $ integers $ f_0, f_1, \ldots, f_m $ , where $ f_i $ represents the number of times $ i $ occurs in the array $ a $ .

 $ ^\dagger $ The $ \operatorname{MEX} $ (minimum excludant) of an array of integers is defined as the smallest non-negative integer which does not occur in the array. For example:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ , because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, the array $ a $ is $ [0, 0, 0, 0, 1, 1, 1, 1, 1] $ . A possible game with a score of $ 2 $ is as follows:

1. Alice chooses the element $ 0 $ . After this move, $ a = [0, 0, 0, 1, 1, 1, 1, 1] $ and $ c=[0] $ .
2. Bob chooses to remove the $ 3 $ elements $ 0 $ , $ 0 $ and $ 1 $ . After this move, $ a = [0, 1, 1, 1, 1] $ and $ c=[0] $ .
3. Alice chooses the element $ 1 $ . After this move, $ a = [0,1,1,1] $ and $ c=[0,1] $ .
4. Bob removes the $ 4 $ remaining elements $ 0 $ , $ 1 $ , $ 1 $ and $ 1 $ . After this move, $ a=[\,] $ and $ c=[0,1] $ .

At the end, $ c=[0,1] $ which has a MEX of $ 2 $ . Note that this is an example game and does not necessarily represent the optimal strategy for both players.

In the second test case, Alice can choose a $ 0 $ in her first turn, guaranteeing that her score is at least $ 1 $ . While Bob can remove all copies of element $ 1 $ in his first turn, thus guaranteeing that Alice's score cannot exceed $ 1 $ . So Alice's score is $ 1 $ if both players play optimally.

## 样例 #1

### 输入

```
5
1 4
4 5
2 1000000000
1000000000 1000000000 1000000000
3 2
2 3 100 1
1 1
2 2
3 1
1 1 1 1```

### 输出

```
2
1
3
2
1```

# AI分析结果

---
# 💡 Kay的C++算法解析：MEX Game 2 (Easy Version) 深入学习指南 💡

<introduction>
今天我们来一起分析“MEX Game 2 (Easy Version)”这道C++编程题。这道题涉及博弈论与贪心策略的结合，Alice和Bob的最优操作需要仔细分析。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`贪心策略与二分答案结合`

🗣️ **初步分析**：
解决这道题的关键在于理解Alice和Bob的最优策略，并通过二分法确定Alice能保证的最大MEX。简单来说，二分答案就像“试钥匙”——我们猜测一个MEX值mid，然后验证Alice是否能保证c数组包含0到mid-1的所有数（即MEX至少为mid）。若能，则尝试更大的mid；否则尝试更小的。

在本题中，核心矛盾是Alice希望收集0到mid-1的所有数，而Bob试图破坏这一目标。通过分析双方的最优策略（Alice每次选剩余最少的数，Bob每次尽可能删除关键数），我们可以设计验证函数来判断某个mid是否可行。

- **题解思路对比**：多个题解均采用二分答案框架，但在验证函数的实现上有所不同。例如，Purslane的代码通过模拟Bob的删除操作来验证mid是否可行；Felix72的代码则通过贪心策略优化了验证过程。
- **核心算法流程**：二分mid → 提取0到mid-1的频率数组 → 排序后模拟Bob的删除操作，检查是否所有数都能被Alice收集。可视化设计中，需要展示Alice选择最小数的过程（如像素块高亮最小数），以及Bob删除多个数的动画（如像素块消失）。
- **复古游戏化演示**：采用8位像素风格，用不同颜色的方块表示不同数值的元素。Alice的选择用绿色箭头指向最小方块，Bob的删除用红色爆炸动画（伴随“嘭”的音效）。控制面板支持单步/自动播放，展示每一步操作后的数组状态。

---

## 2. 精选优质题解参考

<eval_intro>
通过对题解的思路清晰度、代码可读性、算法有效性等方面评估，以下题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：来源：Purslane（赞：4）**
* **点评**：这份题解思路非常清晰，采用二分答案框架，验证函数通过模拟Bob的删除操作来判断mid是否可行。代码结构规范（如变量名`simulate`、`solve`含义明确），核心逻辑（`del`函数模拟删除操作）实现简洁。算法上，虽然时间复杂度为O(m³log m)，但在Easy Version的数据范围内足够高效。实践价值高，代码可直接用于竞赛，边界处理（如排序后数组的初始化）严谨。

**题解二：来源：Alex_Wei（赞：4）**
* **点评**：此题解深入分析了Alice和Bob的最优策略（Alice必选最小数，Bob优先删除后续数），并通过归纳法证明了策略的正确性。虽然代码未直接展示，但思路推导对理解问题本质有重要启发，适合学习者深入理解博弈论中的最优策略选择。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下核心难点。结合优质题解的共性，提炼思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何确定Alice和Bob的最优策略？**
    * **分析**：Alice的最优策略是每次选择当前剩余数量最少的数（因为这样能最小化Bob破坏的可能性）；Bob的最优策略是优先删除可能被Alice选中的数，尤其是通过删除较大的数来维持较小数的数量，避免被Alice快速收集。优质题解通过排序和模拟操作验证了这一策略。
    * 💡 **学习笔记**：博弈问题中，双方的最优策略往往围绕“最小化对方优势”展开，需通过归纳或反证法验证策略的正确性。

2.  **关键点2：如何设计二分答案的验证函数？**
    * **分析**：验证函数需要判断对于mid，Alice能否收集0到mid-1的所有数。这需要模拟Bob的删除操作，检查是否存在某个数被Bob提前删光。Purslane的代码通过`simulate`数组模拟每一步操作，`del`函数处理删除逻辑，确保验证的准确性。
    * 💡 **学习笔记**：二分答案的核心是设计高效的验证函数，需明确验证条件（如“所有数未被删光”）和模拟过程。

3.  **关键点3：如何优化模拟过程的时间复杂度？**
    * **分析**：Easy Version中m较小（如≤50），直接模拟（O(m³)）即可通过。对于Hard Version，需进一步优化（如用差分或数学公式简化模拟）。优质题解通过排序和贪心策略减少了不必要的计算。
    * 💡 **学习笔记**：数据范围决定算法选择，小范围问题可优先考虑暴力模拟，大范围需寻找数学规律或优化策略。

### ✨ 解题技巧总结
- **问题转化**：将博弈问题转化为“能否收集所有0到mid-1的数”，通过二分答案简化问题。
- **排序与贪心**：排序后处理频率数组，利用贪心策略确定双方最优操作。
- **模拟验证**：通过模拟Bob的删除操作，验证mid的可行性，确保逻辑覆盖所有可能情况。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解思路的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Purslane和Felix72的题解思路，采用二分答案框架，通过排序和模拟Bob的删除操作验证mid是否可行。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    #define int long long
    using namespace std;

    int m, k;
    int f[60], simulate[60];

    void del(int l, int r) {
        int remain = k;
        while (remain > 0) {
            int len = 1;
            while (r - len >= l && simulate[r - len] == simulate[r - len + 1]) len++;
            int diff = simulate[r - len + 1] - (r - len >= l ? simulate[r - len] : 0);
            if (diff * len <= remain) {
                for (int i = r - len + 1; i <= r; i++) simulate[i] -= diff;
                remain -= diff * len;
            } else {
                int dec = remain / len;
                int rem = remain % len;
                for (int i = r - len + 1; i <= r; i++) simulate[i] -= dec;
                for (int i = r - len + 1; i < r - len + 1 + rem; i++) simulate[i]--;
                remain = 0;
            }
        }
    }

    bool check(int mid) {
        if (mid == 0) return true;
        vector<int> g;
        for (int i = 0; i < mid; i++) g.push_back(f[i]);
        sort(g.begin(), g.end());
        for (int i = 1; i < mid; i++) {
            for (int j = 0; j < mid; j++) simulate[j] = g[j];
            for (int j = 0; j < i; j++) del(j + 1, i);
            if (simulate[i] <= 0) return false;
        }
        return true;
    }

    signed main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        int T;
        cin >> T;
        while (T--) {
            cin >> m >> k;
            for (int i = 0; i <= m; i++) cin >> f[i];
            int ans = 0, l = 0, r = m + 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (check(mid)) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            cout << ans << '\n';
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取输入，然后通过二分法确定最大MEX。`check`函数验证当前mid是否可行：提取0到mid-1的频率数组，排序后模拟Bob的删除操作（`del`函数处理删除逻辑），检查是否所有数都未被删光。核心逻辑在`check`和`del`函数中，通过排序和贪心策略模拟双方操作。

---
<code_intro_selected>
接下来，剖析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：来源：Purslane**
* **亮点**：通过`simulate`数组模拟每一步操作，`del`函数高效处理Bob的删除逻辑，代码结构清晰。
* **核心代码片段**：
    ```cpp
    void del(int l,int r,int op) {
        int rst=m;
        while(rst) {
            int len=min(r-l+1,get_longest(r)),psl=0;
            if(len!=r-l+1) psl=simulate[r-len+1]-simulate[r-len];
            else psl=INT_MAX;
            if(len*psl>=rst) {
                ffor(j,r-len+1,r) simulate[j]-=rst/len;
                ffor(j,r-len+1,r-len+rst%len) simulate[j]--;
                rst=0;
            } else {
                ffor(j,r-len+1,r) simulate[j]-=psl;
                rst-=len*psl;	
            }
        }
    }
    ```
* **代码解读**：这段代码模拟Bob的删除操作。`len`表示当前连续相同值的长度，`psl`表示当前段与前一段的差值。根据剩余删除次数（`rst`），决定是直接减少当前段（`len*psl>=rst`）还是按差值减少（`len*psl<rst`）。通过这种方式，高效模拟了Bob删除多个数的过程。
* 💡 **学习笔记**：模拟删除操作时，利用连续段的差值可以减少计算量，提高效率。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解Alice和Bob的操作过程，我们设计一个“像素寻宝”主题的8位风格动画，展示双方如何争夺MEX值！
</visualization_intro>

  * **动画演示主题**：`像素寻宝：Alice的MEX大冒险`
  * **核心演示内容**：Alice（绿色小方块）每次选择当前剩余最少的元素（蓝色像素块）加入背包（c数组），Bob（红色小恶魔）每次删除最多k个元素（像素块爆炸）。动画展示每一步操作后的数组状态，最终判断MEX值。
  * **设计思路简述**：8位像素风格（如FC游戏画面）营造复古氛围，颜色区分不同角色（Alice绿、Bob红）和元素（蓝色为普通元素，黄色为关键元素）。音效（选择“叮”、删除“嘭”、成功“胜利音效”）强化操作记忆，小关卡设计（每收集一个数算一关）增加成就感。

  * **动画帧步骤与交互关键点**：
    1.  **场景初始化**：屏幕左侧为数组a（像素块排列，颜色越深表示数量越多），右侧为c数组（空背包）。控制面板包含“单步”“自动”“重置”按钮和速度滑块。播放8位风格BGM。
    2.  **Alice选择元素**：绿色箭头指向当前最小的蓝色像素块（数量最少），该块移动到c数组（伴随“叮”音效），a数组对应数量减1（像素块缩小）。
    3.  **Bob删除元素**：红色小恶魔释放红色射线，最多k个像素块爆炸消失（伴随“嘭”音效），a数组对应数量减少。
    4.  **关键步骤高亮**：当Alice收集到0、1等关键数时，像素块变为黄色并闪烁；当Bob删除关键数时，爆炸特效更明显（红色闪光）。
    5.  **目标达成**：当a数组为空时，计算c数组的MEX（金色数字弹出），播放胜利音效（如《超级玛丽》通关音）。若MEX未达标，播放提示音效（短促“滴”声）。
    6.  **AI自动演示**：点击“AI演示”，动画自动播放最优策略，学习者可观察双方操作全过程。

  * **旁白提示**：
    - “看！Alice选择了当前数量最少的元素，这样能最小化Bob破坏的可能～”
    - “Bob在删除元素啦！他最多可以删k个，目标是阻止Alice收集所有关键数～”
    - “恭喜！Alice成功收集了0到mid-1的所有数，MEX至少为mid！”

<visualization_conclusion>
通过这样的像素动画，我们能清晰看到每一步操作对数组的影响，理解Alice和Bob的最优策略如何相互作用，最终决定MEX值。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，我们可以将贪心与二分结合的思路迁移到更多博弈或最值问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 二分答案+贪心验证：适用于“求最大/最小值，且验证可行”的问题（如求最大资源分配、最小等待时间）。
    - 博弈策略分析：通过归纳法确定双方最优策略（如取最小/最大元素、优先删除关键元素）。
    - 模拟操作：小数据范围下，直接模拟双方操作验证可行性。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1803 凌乱的yyy / 线段覆盖**
          * 🗣️ **推荐理由**：贪心策略的典型应用，练习如何选择最优区间覆盖，与本题的贪心思路类似。
    2.  **洛谷 P2678 跳石头**
          * 🗣️ **推荐理由**：二分答案+贪心验证的经典题，练习如何通过二分确定最小跳跃距离，与本题的验证思路一致。
    3.  **洛谷 P1024 一元三次方程求解**
          * 🗣️ **推荐理由**：二分法在数学问题中的应用，练习如何通过二分缩小解的范围，提升二分法的灵活运用能力。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试和思路推导的经验，对我们有重要参考价值：
</insights_intro>

> **参考经验 (来自Purslane)**：“学弟说这是唐题，我想了一段时间才明白。关键是要抓住Alice和Bob的最优策略，尤其是Alice必选最小数这一点。”
>
> **点评**：这位作者的经验提醒我们，博弈问题中双方的策略往往基于“最小化对方优势”，抓住关键策略（如Alice选最小数）是解题的突破口。遇到类似问题时，先分析双方的最优操作，再设计验证逻辑。

---

<conclusion>
本次关于“MEX Game 2 (Easy Version)”的C++解题分析就到这里。希望这份指南能帮助大家理解贪心与二分结合的解题思路，掌握博弈问题的策略分析方法。记住，多思考、多模拟，编程能力会稳步提升！下次见～💪
</conclusion>

---
处理用时：115.62秒