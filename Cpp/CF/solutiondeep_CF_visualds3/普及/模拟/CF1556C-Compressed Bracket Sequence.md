# 题目信息

# Compressed Bracket Sequence

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556C/3e1271d095f65d6764f1796fd73b8947fda1c3d9.png)William has a favorite bracket sequence. Since his favorite sequence is quite big he provided it to you as a sequence of positive integers $ c_1, c_2, \dots, c_n $ where $ c_i $ is the number of consecutive brackets "(" if $ i $ is an odd number or the number of consecutive brackets ")" if $ i $ is an even number.

For example for a bracket sequence "((())()))" a corresponding sequence of numbers is $ [3, 2, 1, 3] $ .

You need to find the total number of continuous subsequences (subsegments) $ [l, r] $ ( $ l \le r $ ) of the original bracket sequence, which are regular bracket sequences.

A bracket sequence is called regular if it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not.

## 说明/提示

In the first example a sequence (((()(()))( is described. This bracket sequence contains $ 5 $ subsegments which form regular bracket sequences:

1. Subsequence from the $ 3 $ rd to $ 10 $ th character: (()(()))
2. Subsequence from the $ 4 $ th to $ 5 $ th character: ()
3. Subsequence from the $ 4 $ th to $ 9 $ th character: ()(())
4. Subsequence from the $ 6 $ th to $ 9 $ th character: (())
5. Subsequence from the $ 7 $ th to $ 8 $ th character: ()

In the second example a sequence ()))(()(()))) is described.

In the third example a sequence ()()(()) is described.

## 样例 #1

### 输入

```
5
4 1 2 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
6
1 3 2 1 2 4```

### 输出

```
6```

## 样例 #3

### 输入

```
6
1 1 1 1 2 2```

### 输出

```
7```

# AI分析结果



---
# 💡 Kay的C++算法解析：Compressed Bracket Sequence 深入学习指南 💡

<introduction>
今天我们来一起分析“Compressed Bracket Sequence”这道C++编程题。题目要求我们计算压缩后的括号序列中所有合法的连续子序列数量。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：栈与单调栈应用 (结合折线图分析的高效统计方法)

🗣️ **初步分析**：
解决这道题的关键在于将压缩的括号序列转化为“折线图”模型：奇数位的左括号对应“上坡”（高度增加），偶数位的右括号对应“下坡”（高度减少）。合法的括号序列对应折线图中一段**首尾高度相同且中间无更低点**的区间。

- **核心思路对比**：  
  题解中主要有两种思路：  
  1. **O(n²)枚举法**（如Zxsoul题解）：枚举所有可能的左右端点（左奇右偶），计算中间区间的前缀和最小值和总和，判断是否满足合法条件。  
  2. **O(n)单调栈法**（如maruize、vectorwyx题解）：通过维护“未被遮挡的山谷”的单调栈，统计每个下坡段能匹配的左端点数量，高效计算贡献。  

- **核心算法流程**（以单调栈法为例）：  
  1. 将括号序列转化为折线图，记录每个“山谷”（下坡后的最低点）的高度。  
  2. 对于每个下坡段，计算其能匹配的左端点范围（首尾高度相同且中间无更低点）。  
  3. 用单调栈维护未被遮挡的山谷（栈内元素按高度递增），弹栈时统计这些山谷对当前下坡段的贡献。  

- **可视化设计思路**：  
  采用8位像素风格，用不同颜色表示上坡（绿色）和下坡（红色）线段，山谷用蓝色方块标记。动画中逐步绘制折线图，高亮当前处理的下坡段，用栈结构（像素方块堆叠）动态展示未被遮挡的山谷。关键操作（如弹栈、计算贡献）伴随“叮”的音效，完成统计时播放胜利音效。


## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等，筛选出以下3篇优质题解（评分≥4星）：
</eval_intro>

**题解一：maruize（赞：7）**  
* **点评**：此题解通过折线图模型将问题转化为几何分析，清晰解释了“山谷”和“山峰”的匹配关系。代码中用单调栈维护未被遮挡的山谷，时间复杂度O(n)，是本题的最优解法。变量命名简洁（如`h`表示当前高度，`st`表示栈），边界处理严谨（如栈中存储高度和出现次数），实践价值高，适合竞赛参考。

**题解二：vectorwyx（赞：2）**  
* **点评**：此题解进一步细化了折线图的“匹配”定义，明确区分了“平凡匹配”和“非平凡匹配”。代码中用`stk`栈存储未被遮挡的山谷，通过弹栈操作统计贡献，逻辑清晰。虽然赞数不高，但算法复杂度与maruize一致，且对匹配类型的分析对理解问题有启发。

**题解三：Zxsoul（赞：5）**  
* **点评**：此题解采用O(n²)枚举法，适合理解基础逻辑。通过维护当前左括号剩余量`res`和累计高度`tot`，逐步向右扩展右括号，计算每对左右端点的贡献。代码变量命名直观（如`res`表示剩余左括号），适合初学者理解合法序列的条件。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下核心难点，结合优质题解的共性，提炼解决策略：
</difficulty_intro>

1.  **难点1：如何将压缩序列转化为可分析的结构？**  
    * **分析**：直接处理压缩的括号序列（如`[3,2,1,3]`对应`((())()))`）需考虑连续括号的影响。优质题解（如maruize）将其转化为“折线图”模型，左括号对应上坡（高度+数量），右括号对应下坡（高度-数量），将问题转化为几何中的“首尾等高且中间无更低点”区间统计。  
    * 💡 **学习笔记**：将抽象的括号序列转化为直观的几何模型（如折线图），能更清晰地观察合法序列的特征。

2.  **难点2：如何高效统计所有合法子序列？**  
    * **分析**：暴力枚举左右端点（O(n²)）在n较大时效率低。优质题解（如maruize）利用单调栈维护“未被遮挡的山谷”，每个下坡段的贡献可通过栈快速计算，时间复杂度优化到O(n)。关键在于发现“后面的山谷会遮挡前面更高的山谷”这一性质，用栈保持山谷高度递增。  
    * 💡 **学习笔记**：单调栈适合处理“遮挡”“最值”类问题，能避免重复计算，提升效率。

3.  **难点3：如何处理前缀和的最小值约束？**  
    * **分析**：合法括号序列要求任意前缀和≥0。优质题解（如Cry_For_theMoon）通过预处理前缀和数组`sum`和最小值数组`minn`，快速判断中间区间的最小值是否满足条件。对于压缩序列，需计算中间区间的最小前缀和，并确保左右端点的括号数量足够覆盖该最小值。  
    * 💡 **学习笔记**：预处理关键数组（如前缀和、最小值）是解决区间约束问题的常用技巧。

### ✨ 解题技巧总结
- **模型转换**：将括号序列转化为折线图，用几何特征（首尾等高、中间无更低点）辅助分析。  
- **单调栈维护**：利用栈的单调性（如高度递增）快速统计未被遮挡的关键点（山谷）。  
- **预处理数组**：预处理前缀和、最小值数组，快速判断区间约束条件（如前缀和≥0）。  


## 4. C++核心代码实现赏析

<code_intro_overall>
首先展示一个综合了maruize和vectorwyx思路的O(n)单调栈核心实现，适合竞赛参考。
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码综合了maruize和vectorwyx的单调栈思路，通过维护高度栈统计每个下坡段的贡献，时间复杂度O(n)。  
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>
    using namespace std;

    typedef long long ll;
    typedef pair<ll, int> pii; // 栈中元素：(高度，出现次数)

    int main() {
        int n;
        cin >> n;
        vector<ll> a(n + 1); // 输入数组，下标从1开始
        for (int i = 1; i <= n; ++i) cin >> a[i];

        vector<pii> stk; // 单调栈，保存未被遮挡的山谷高度（递增）
        stk.emplace_back(0, 1); // 初始高度0，出现1次
        ll h = a[1]; // 当前折线高度（初始为第一个左括号的高度）
        ll ans = 0;

        for (int i = 2; i <= n; ++i) {
            if (i % 2 == 1) { // 奇数位：左括号，上坡
                // 弹出所有高度大于当前高度的山谷（被当前上坡遮挡）
                while (!stk.empty() && stk.back().first > h) {
                    ans += stk.back().second;
                    stk.pop_back();
                }
                // 合并或新增当前高度到栈中
                if (stk.empty() || stk.back().first != h) {
                    stk.emplace_back(h, 1);
                } else {
                    stk.back().second++;
                }
                h += a[i]; // 上坡，高度增加
            } else { // 偶数位：右括号，下坡
                ll new_h = h - a[i]; // 下坡后的新高度
                // 计算当前下坡段的平凡贡献（首尾等高且中间无更低点）
                ll low = stk.front().first; // 最低山谷高度
                ans += max(h - max(low, new_h), 0LL);
                // 弹出所有高度大于new_h的山谷（被当前下坡遮挡）
                while (!stk.empty() && stk.back().first > new_h) {
                    if (stk.size() > 1) ans += stk.back().second; // 非最低山谷的额外贡献
                    stk.pop_back();
                }
                // 合并或新增new_h到栈中（作为新的山谷）
                if (stk.empty() || stk.back().first != new_h) {
                    stk.emplace_back(new_h, 1);
                } else {
                    stk.back().second++;
                }
                h = new_h; // 更新当前高度为下坡后的高度
            }
        }

        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：  
  代码通过维护一个单调递增的栈`stk`，保存未被遮挡的山谷高度。对于每个左括号（上坡），弹出比当前高度高的山谷（被遮挡），并将当前高度入栈；对于每个右括号（下坡），计算当前下坡段的平凡贡献（首尾等高区间），弹出比新高度高的山谷（被遮挡），并将新高度入栈。最终统计所有合法子序列的数量。


<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：maruize**  
* **亮点**：用折线图模型将问题转化为几何分析，单调栈维护未被遮挡的山谷，时间复杂度O(n)。  
* **核心代码片段**：
    ```cpp
    int ans=0;
    for(int i=1;i<n;i+=2){
        ans+=h[i]-max(h[i]-a[i+1],st[1].fs);
        while(top>0&&st[top].fs>h[i+1]){
            if(top>1)ans+=st[top].sc;
            top--;
        }
        if(st[top].fs!=h[i+1])st[++top]=pii(h[i+1],1);
        else ans+=st[top].sc,st[top].sc++;
    }
    ```
* **代码解读**：  
  `h[i]`表示当前上坡后的高度，`a[i+1]`是当前下坡的右括号数量。`st`栈保存山谷高度（`fs`）和出现次数（`sc`）。第一行计算当前下坡段的平凡贡献（首尾等高区间长度）；`while`循环弹出比新高度高的山谷，统计它们的额外贡献；最后将新高度入栈（合并相同高度的山谷）。  
* 💡 **学习笔记**：合并相同高度的山谷可避免重复计算，保证时间复杂度为O(n)。

**题解二：Zxsoul（O(n²)枚举法）**  
* **亮点**：思路直观，适合理解合法序列的条件。  
* **核心代码片段**：
    ```cpp
    for (int i=1;i<=n;i+=2) {
        int res=a[i]-1;
        int tot=a[i];
        for (int j=i+1;j<=n;j+=2) {
            ans+=max(0ll,res-max(0ll,tot-a[j])+1ll);
            tot-=a[j];
            if (tot<0) break;
            res=min(tot,res);
            tot+=a[j+1];
        }
    }
    ```
* **代码解读**：  
  外层循环枚举左括号段`i`，内层循环枚举右括号段`j`。`res`表示当前左括号剩余可匹配量，`tot`表示累计高度。每次计算`[i,j]`区间的贡献（`max(0ll, res - max(0ll, tot - a[j]) + 1ll)`），并更新`tot`和`res`。  
* 💡 **学习笔记**：枚举法虽复杂度较高，但能直观展示合法序列的匹配过程，适合初学者理解问题。


## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解单调栈法的执行过程，设计一个“像素折线探险”动画，用8位风格展示折线图、栈变化和贡献统计。
</visualization_intro>

  * **动画演示主题**：像素折线探险——寻找合法括号序列  
  * **核心演示内容**：展示折线图的绘制（上坡/下坡）、单调栈的入栈/弹栈过程，以及每一步贡献的计算。  

  * **设计思路简述**：  
    采用FC红白机风格的像素画面（8色调色板：绿-上坡，红-下坡，蓝-山谷，黄-当前处理点），用动态线段绘制折线图。栈用垂直堆叠的像素方块表示，每个方块显示高度和出现次数。关键操作（弹栈、计算贡献）伴随“叮”的音效，完成统计时播放胜利音效（如《超级玛丽》的金币声）。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕左侧绘制像素网格（16x16像素/格），顶部显示“Compressed Bracket Sequence”标题。  
        - 底部控制面板包含：开始/暂停按钮、单步按钮、速度滑块（0.5x-2x）、重置按钮。  
        - 背景播放8位风格的轻快BGM（如《俄罗斯方块》主题曲变奏）。

    2.  **折线图绘制**：  
        - 输入数组`a`显示在屏幕右侧，奇数位标绿（左括号），偶数位标红（右括号）。  
        - 从左到右逐段绘制折线：奇数位向上绘制绿色线段（长度为`a[i]`），偶数位向下绘制红色线段（长度为`a[i]`）。每绘制一段，播放“刷”的音效。

    3.  **单调栈操作演示**：  
        - 栈显示在屏幕右侧，用垂直堆叠的蓝色方块表示（每个方块高度为栈中元素的`fs`，宽度为`sc`）。  
        - 处理上坡段（奇数位）时，当前高度`h`用黄色箭头标记。弹出比`h`高的栈顶方块（蓝色方块向上消失，播放“噗”的音效），统计贡献时方块变为金色并累加至`ans`（屏幕顶部显示`ans`的实时值）。  
        - 处理下坡段（偶数位）时，计算新高度`new_h`，用红色箭头标记。弹出比`new_h`高的栈顶方块（同样消失并统计贡献），将`new_h`入栈（蓝色方块从底部升起，播放“叮”的音效）。

    4.  **贡献计算高亮**：  
        - 平凡贡献（首尾等高区间）用绿色边框高亮对应的折线段，显示“平凡贡献+X”的文字气泡。  
        - 非平凡贡献（未被遮挡的山谷）用蓝色边框高亮对应的山谷方块，显示“非平凡贡献+X”的文字气泡。

    5.  **结束状态**：  
        - 所有线段绘制完成后，`ans`显示最终结果，播放上扬的胜利音效（如《超级玛丽》的通关声），屏幕中央弹出“成功！总共有X个合法序列”的庆祝文字。

  * **旁白提示**：  
    - “现在处理第i段，这是左括号段，折线向上绘制...注意看栈的变化！”  
    - “这个蓝色方块被弹出了，因为它的高度比当前高度高，会被遮挡哦～”  
    - “计算到一个新的合法序列，ans增加了！”

<visualization_conclusion>
通过这个像素动画，我们能直观看到折线图的变化、栈的操作和贡献的计算过程，更轻松地理解单调栈法的核心逻辑。
</visualization_conclusion>


## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的单调栈和折线图模型后，可迁移到以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    折线图模型和单调栈法不仅适用于括号序列，还可处理：  
    1. 柱状图中最大矩形面积（LeetCode 84）：用单调栈维护递增的柱子高度。  
    2. 接雨水（LeetCode 42）：用折线图模型统计每个位置能接的雨水量。  
    3. 股票价格波动中的最大利润（LeetCode 121）：用单调栈维护最低价格。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1944 括号序列**  
        * 🗣️ **推荐理由**：直接考察括号序列的合法性判断，需处理压缩形式的括号，与本题模型类似。  
    2.  **洛谷 P1115 最大子段和**  
        * 🗣️ **推荐理由**：需预处理前缀和数组，与本题中前缀和最小值的处理思路相似。  
    3.  **洛谷 P5788 【模板】单调栈**  
        * 🗣️ **推荐理由**：专项练习单调栈的使用，巩固本题的核心算法。  


## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，以下是值得借鉴的内容：
</insights_intro>

> **参考经验 (来自 maruize)**：“在实现单调栈时，容易漏掉栈中相同高度的合并，导致时间复杂度退化为O(n²)。后来通过将相同高度的山谷合并（记录出现次数），才保证了O(n)的复杂度。”  

> **点评**：maruize的经验提醒我们，处理单调栈问题时，合并相同元素是避免重复计算、保证复杂度的关键。在类似问题（如柱状图最大矩形）中，同样需要注意这一点。


<conclusion>
本次关于“Compressed Bracket Sequence”的C++解题分析就到这里。通过折线图模型、单调栈法和可视化动画，我们深入理解了合法括号序列的统计方法。希望大家在练习中多思考模型转换和优化技巧，提升算法能力！下次再见～💪
</conclusion>

---
处理用时：158.66秒