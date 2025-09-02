# 题目信息

# Rain

## 题目描述

You are the owner of a harvesting field which can be modeled as an infinite line, whose positions are identified by integers.

It will rain for the next $ n $ days. On the $ i $ -th day, the rain will be centered at position $ x_i $ and it will have intensity $ p_i $ . Due to these rains, some rainfall will accumulate; let $ a_j $ be the amount of rainfall accumulated at integer position $ j $ . Initially $ a_j $ is $ 0 $ , and it will increase by $ \max(0,p_i-|x_i-j|) $ after the $ i $ -th day's rain.

A flood will hit your field if, at any moment, there is a position $ j $ with accumulated rainfall $ a_j>m $ .

You can use a magical spell to erase exactly one day's rain, i.e., setting $ p_i=0 $ . For each $ i $ from $ 1 $ to $ n $ , check whether in case of erasing the $ i $ -th day's rain there is no flood.

## 说明/提示

In the first test case, if we do not use the spell, the accumulated rainfall distribution will be like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/40bd9aae46d3e796ba1ad418de0578aa41ab0c1c.png)If we erase the third day's rain, the flood is avoided and the accumulated rainfall distribution looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/d422db8867ffc7f0ea195742c50ffb3752e7d523.png)In the second test case, since initially the flood will not happen, we can erase any day's rain.

In the third test case, there is no way to avoid the flood.

## 样例 #1

### 输入

```
4
3 6
1 5
5 5
3 4
2 3
1 3
5 2
2 5
1 6
10 6
6 12
4 5
1 6
12 5
5 5
9 7
8 3```

### 输出

```
001
11
00
100110```

# AI分析结果



---
# 💡 Kay的C++算法解析：Rain 深入学习指南 💡

<introduction>
今天我们来一起分析“Rain”这道C++编程题。这道题需要判断抹去某一天的降雨后是否能避免洪水，核心在于高效计算降雨中心的最大积水量，并通过数学推导快速判断每个“抹除天”的有效性。本指南将帮助大家梳理思路，掌握关键算法和解题技巧。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟与数学应用（结合差分数组处理区间操作，数学不等式转化）

🗣️ **初步分析**：
解决“Rain”的关键在于理解降雨对积水量的影响规律，并通过数学推导简化判断条件。降雨的影响是一个倒V形曲线（中心x_i处积水量最大，向两侧线性递减），因此洪水只会出现在降雨中心位置。我们可以将问题简化为：计算每个降雨中心的最终积水量，找出其中超过m的点，再通过数学条件判断抹去某一天的降雨是否能让所有超标点的积水量降至m以下。

- **题解思路**：所有优质题解均围绕“只关注降雨中心”展开，通过差分数组维护每个中心的积水量，再转化为两个不等式条件（`p_i - x_i + m >= mx1`和`p_i + x_i + m >= mx2`）判断是否满足要求。
- **核心难点**：如何高效计算每个降雨中心的积水量（涉及区间操作的差分处理），以及如何将绝对值条件转化为线性不等式。
- **可视化设计**：采用8位像素风格，用不同颜色的倒V形像素块表示每场雨的影响范围；用动态变化的像素条展示积水量变化；关键步骤（如差分数组更新、mx1/mx2计算）通过闪烁和音效提示。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码可读性、算法有效性等维度，筛选出以下3篇优质题解：
</eval_intro>

**题解一：作者ethan_zhou（赞：50）**
* **点评**：此题解数形结合，思路极其清晰。通过差分数组维护斜率和截距，高效计算每个降雨中心的积水量；将绝对值条件转化为两个线性不等式，简化判断逻辑。代码简洁规范（如`umx`函数优化最大值更新），复杂度O(n log n)，是竞赛题解的典范。亮点在于“将问题转化为两个不等式求交”的数学推导，大幅降低了计算复杂度。

**题解二：作者enucai（赞：10）**
* **点评**：此题解逻辑直白，通过排序和二分查找确定降雨影响范围，用差分数组维护斜率和截距。代码结构工整（如`sort`和`lower_bound`的配合），变量名（如`mx1`、`mx2`）含义明确，边界处理严谨。亮点是“只关注降雨中心”的关键观察，将问题规模从无限数轴缩小到n个点。

**题解三：作者览遍千秋（赞：2）**
* **点评**：此题解详细推导了“洪水仅出现在降雨中心”的结论，并通过差分数组和扫描线维护积水量。代码中`lfind`和`rfind`函数通过二分查找确定影响区间，逻辑清晰。亮点是对绝对值条件的拆解（`R_i + x_i <= x_j + p_j +m`和`R_i - x_i <= -x_j + p_j + m`），直接关联到最终判断条件。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于如何高效计算积水量并转化判断条件。以下是三个关键步骤的分析：
</difficulty_intro>

1.  **关键点1：如何高效计算降雨中心的积水量？**
    * **分析**：每场雨对中心x_i的积水量贡献是`max(0, p_i - |x_i - j|)`，但直接计算每个j的复杂度是O(n²)。优质题解通过差分数组维护斜率（k）和截距（b），将区间操作转化为差分更新。例如，对于雨i的影响区间[L, R]，左半段（L到i）的斜率为1，右半段（i+1到R）的斜率为-1，通过差分累加即可得到每个中心的积水量。
    * 💡 **学习笔记**：差分数组是处理区间线性变化的高效工具，能将O(n)操作优化为O(1)差分更新。

2.  **关键点2：如何将绝对值条件转化为线性不等式？**
    * **分析**：若抹去第i天的雨后，某中心j的积水量需≤m，即原积水量a_j - (p_i - |x_i - x_j|) ≤m。拆开绝对值后得到两个不等式：`a_j - x_j ≤ m + p_i - x_i`和`a_j + x_j ≤ m + p_i + x_i`。维护所有超标中心的`a_j - x_j`和`a_j + x_j`的最大值（mx1和mx2），即可快速判断i是否满足条件。
    * 💡 **学习笔记**：绝对值的拆解需要分情况讨论，但通过维护最大值可将多个条件简化为两个全局约束。

3.  **关键点3：如何处理离散化和排序？**
    * **分析**：由于降雨中心x_i可能很大，需先排序并离散化，将无限数轴映射到有限的索引。排序后，通过二分查找确定每场雨的影响区间[L, R]，确保差分数组的正确更新。
    * 💡 **学习笔记**：离散化是处理大范围数据的常用技巧，结合排序和二分查找可高效缩小问题规模。

### ✨ 解题技巧总结
- **问题简化**：通过观察降雨的倒V形影响，将问题从无限数轴缩小到n个降雨中心。
- **差分数组**：用斜率（k）和截距（b）的差分数组处理区间线性变化，高效计算积水量。
- **最大值维护**：维护超标中心的`a_j - x_j`和`a_j + x_j`的最大值，将多条件判断转化为两个全局约束。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，结合了差分数组和数学推导，逻辑清晰且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了ethan_zhou和enucai的题解思路，通过差分数组维护斜率和截距，计算每个降雨中心的积水量，并判断是否满足条件。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    const ll INF = 1e18;
    const int MXN = 2e5 + 5;

    ll n, m;
    ll x[MXN], p[MXN];
    ll k[MXN], b[MXN]; // 斜率和截距的差分数组

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t;
        cin >> t;
        while (t--) {
            cin >> n >> m;
            for (int i = 1; i <= n; ++i) cin >> x[i] >> p[i];
            vector<pair<ll, ll>> rains(n);
            for (int i = 0; i < n; ++i) rains[i] = {x[i+1], p[i+1]};
            sort(rains.begin(), rains.end()); // 按x排序

            fill(k, k + n + 2, 0);
            fill(b, b + n + 2, 0);

            for (int i = 0; i < n; ++i) {
                auto [xi, pi] = rains[i];
                // 找到影响区间的左右边界（二分）
                int L = lower_bound(rains.begin(), rains.end(), make_pair(xi - pi, 0ll)) - rains.begin();
                int R = upper_bound(rains.begin(), rains.end(), make_pair(xi + pi, 0ll)) - rains.begin() - 1;

                // 左半段 [L, i] 斜率+1，截距 += (pi - xi)
                k[L]++; k[i+1]--;
                b[L] += (pi - xi); b[i+1] -= (pi - xi);

                // 右半段 [i+1, R] 斜率-1，截距 += (pi + xi)
                k[i+1]--; k[R+1]++;
                b[i+1] += (pi + xi); b[R+1] -= (pi + xi);
            }

            // 计算每个降雨中心的积水量a_i
            ll mx1 = -INF, mx2 = -INF;
            ll cur_k = 0, cur_b = 0;
            for (int i = 0; i < n; ++i) {
                cur_k += k[i];
                cur_b += b[i];
                auto [xi, pi] = rains[i];
                ll a_i = cur_k * xi + cur_b;
                if (a_i > m) {
                    mx1 = max(mx1, a_i - xi);
                    mx2 = max(mx2, a_i + xi);
                }
            }

            // 判断每个i是否满足条件
            string ans(n, '0');
            for (int i = 0; i < n; ++i) {
                auto [xi, pi] = rains[i];
                if (pi - xi + m >= mx1 && pi + xi + m >= mx2) ans[i] = '1';
            }
            cout << ans << "\n";
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先按x排序降雨中心，通过差分数组维护斜率（k）和截距（b），计算每个中心的积水量a_i。然后维护超标中心的`a_i - x_i`和`a_i + x_i`的最大值mx1、mx2。最后，对每个i判断是否满足两个不等式条件，输出结果。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者ethan_zhou**
* **亮点**：用`map`离散化处理影响区间，代码简洁高效。
* **核心代码片段**：
    ```cpp
    map<ll, ll> delt;
    // 差分数组更新
    delt[x[i] - p[i] + 1]++;
    delt[x[i] + 1] -= 2;
    delt[x[i] + p[i] + 1]++;
    // 计算积水量b和斜率k
    ll b = 0, k = 0, lastx = -INF;
    ll b_1 = -INF, b1 = -INF;
    for (auto it : delt) {
        b += k * (it.fi - lastx);
        k += it.se;
        if (b > m) {
            umx(b1, b - it.fi + 1);
            umx(b_1, b + it.fi - 1);
        }
        lastx = it.fi;
    }
    ```
* **代码解读**：`delt`是一个`map`，用于离散化处理每个雨的影响区间。通过三次差分操作（+1, -2, +1）维护斜率k的变化。遍历`map`时，计算当前区间的积水量b，并更新mx1（b1）和mx2（b_1）。`umx`函数优化了最大值更新逻辑。
* 💡 **学习笔记**：`map`适合处理离散的区间端点，自动排序且避免重复，是处理大范围离散数据的高效选择。

**题解二：作者enucai**
* **亮点**：通过排序和二分查找确定影响区间，差分数组维护斜率和截距。
* **核心代码片段**：
    ```cpp
    For(i,1,n) {
        int tmp=lower_bound(op+1,op+n+1,(node){op[i].x-op[i].p,0,0})-op;
        b[tmp]+=op[i].p-op[i].x,b[i+1]-=op[i].p-op[i].x;
        c[tmp]++,c[i+1]--;
    }
    For(i,1,n) {
        int tmp=upper_bound(op+1,op+n+1,(node){op[i].x+op[i].p,0,0})-op-1;
        b[i+1]+=op[i].p+op[i].x,b[tmp+1]-=op[i].p+op[i].x;
        c[i+1]--,c[tmp+1]++;
    }
    ```
* **代码解读**：`lower_bound`和`upper_bound`确定雨i的影响区间左端点L和右端点R。`b`数组维护截距的差分，`c`数组维护斜率的差分。左半段（L到i）斜率+1，截距+(`p_i - x_i`)；右半段（i+1到R）斜率-1，截距+(`p_i + x_i`)。
* 💡 **学习笔记**：二分查找是确定区间端点的关键，结合差分数组可高效处理区间线性变化。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解降雨的影响和积水量计算，我们设计一个“像素雨探险家”动画，以8位复古风格展示算法过程。
</visualization_intro>

  * **动画演示主题**：像素雨探险家——追踪每场雨的影响范围与积水量变化
  * **核心演示内容**：展示每场雨的倒V形影响范围（用蓝色像素块表示），差分数组的更新过程（绿色箭头标记斜率和截距变化），以及mx1、mx2的计算（红色高亮最大值）。
  * **设计思路简述**：8位像素风格营造轻松氛围，动态变化的像素块直观展示积水量；关键操作（如差分数组更新、最大值计算）通过闪烁和音效强化记忆；单步控制和自动播放模式满足不同学习需求。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：屏幕左侧显示排序后的降雨中心（黄色像素点），右侧显示控制面板（开始/暂停、单步、速度滑块）。背景播放8位风格BGM。
    2.  **雨的影响范围演示**：点击“开始”，每场雨以蓝色倒V形像素块展开（从x_i向两侧延伸，高度为p_i），伴随“叮”的音效。
    3.  **差分数组更新**：当雨i的影响范围覆盖到中心j时，差分数组的k和b值变化（绿色箭头指向对应的数组位置，数值动态更新）。
    4.  **积水量计算**：每个降雨中心j的积水量用垂直像素条表示（高度为a_j），超过m时像素条变为红色（洪水警告）。
    5.  **mx1/mx2计算**：遍历所有红色像素条，计算`a_j - x_j`和`a_j + x_j`的最大值（红色数字弹出，伴随“滴”的音效）。
    6.  **判断条件**：对每个i，检查`p_i - x_i + m`是否≥mx1（绿色对勾）和`p_i + x_i + m`是否≥mx2（绿色对勾），全部满足则i的答案为1（金色像素星）。
    7.  **自动演示模式**：点击“AI自动运行”，算法自动完成所有步骤，像“像素探险家”一样逐步解决问题。

  * **旁白提示**：
    - “看！这场雨的影响范围像一个倒V形，中心x_i的积水量最大～”
    - “差分数组的k和b在悄悄变化，这是计算积水量的关键哦！”
    - “红色像素条表示积水量超过m，我们需要找到它们的a_j - x_j和a_j + x_j的最大值～”

<visualization_conclusion>
通过这个像素动画，我们可以直观看到每场雨的影响、积水量的计算过程，以及最终判断条件的满足情况，让抽象的算法变得生动易懂！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的差分数组和数学转化技巧后，可尝试以下拓展练习：
</similar_problems_intro>

  * **通用思路/技巧迁移**：本题的“只关注关键点”和“差分数组处理区间线性变化”技巧，可用于解决以下问题：
    - 区间加权求和（如多次区间加等差数列，求单点值）。
    - 最大值维护（如多次区间修改后求全局最大值）。
    - 绝对值条件转化（如求满足多个绝对值不等式的参数范围）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1972 [SDOI2009]HH的项链**  
       🗣️ **推荐理由**：练习区间查询和离散化，与本题的离散化思路相似。
    2.  **洛谷 P3372 线段树模板**  
       🗣️ **推荐理由**：巩固区间修改和单点查询，与本题的差分数组思想互补。
    3.  **洛谷 P1439 排列LCS问题**  
       🗣️ **推荐理由**：练习转化问题为数学条件，与本题的绝对值转化思路类似。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，以下是值得借鉴的部分：
</insights_intro>

> **参考经验 (来自作者ethan_zhou)**：“最初没有想到洪水仅出现在降雨中心，导致尝试枚举所有位置，结果超时。后来通过画图观察雨的影响曲线，才意识到只需关注中心。”

**点评**：这位作者的经验提醒我们，遇到大范围数据问题时，观察问题的几何特性（如本题的倒V形曲线）往往能简化问题。画图或找规律是发现关键性质的有效方法。

---

<conclusion>
本次“Rain”的解题分析就到这里。通过理解降雨的影响规律、掌握差分数组和数学转化技巧，相信大家能轻松解决类似问题。记得多动手画图、调试，在实践中提升算法能力！下次再见～💪
</conclusion>

---
处理用时：165.48秒