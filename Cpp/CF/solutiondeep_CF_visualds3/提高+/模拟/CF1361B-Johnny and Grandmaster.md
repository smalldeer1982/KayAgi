# 题目信息

# Johnny and Grandmaster

## 题目描述

Johnny has just found the new, great tutorial: "How to become a grandmaster?". The tutorial tells many strange and unexpected for Johnny things, such as you have to be patient or that very important is solving many harder and harder problems.

The boy has found an online judge with tasks divided by topics they cover. He has picked $ p^{k_i} $ problems from $ i $ -th category ( $ p $ is his favorite number). He wants to solve them in two weeks (the patience condition is too hard for Johnny, so for simplicity, he looks only at easy tasks, which can be solved in such a period). Now our future grandmaster has to decide which topics to cover first and which the second week. Help him assign topics in such a way, that workload is balanced.

Formally, given $ n $ numbers $ p^{k_i} $ , the boy wants to divide them into two disjoint sets, minimizing the absolute difference between sums of numbers in each set. Find the minimal absolute difference. Output the result modulo $ 10^{9}+7 $ .

## 说明/提示

You have to minimize the difference, not it's remainder. For example, if the minimum difference is equal to $ 2 $ , but there is also a distribution where the difference is $ 10^9 + 8 $ , then the answer is $ 2 $ , not $ 1 $ .

In the first test case of the example, there're the following numbers: $ 4 $ , $ 8 $ , $ 16 $ , $ 16 $ , and $ 8 $ . We can divide them into such two sets: $ {4, 8, 16} $ and $ {8, 16} $ . Then the difference between the sums of numbers in sets would be $ 4 $ .

## 样例 #1

### 输入

```
4
5 2
2 3 4 4 3
3 1
2 10 1000
4 5
0 1 1 100
1 8
89```

### 输出

```
4
1
146981438
747093407```

# AI分析结果

---
# 💡 Kay的C++算法解析：Johnny and Grandmaster 深入学习指南 💡

<introduction>
今天我们来一起分析“Johnny and Grandmaster”这道C++编程题。这道题需要我们将一组形如 \( p^{k_i} \) 的数分成两组，使得两组和的绝对差最小，并输出这个最小差对 \( 10^9+7 \) 取模的结果。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法 (Greedy Algorithm)

🗣️ **初步分析**：
解决这道题的关键在于理解并运用贪心策略。贪心算法的核心思想是“每一步选择当前最优解，最终逼近全局最优”，就像分糖果时先把最大的糖果分给需要的人，再处理小的。在本题中，由于所有数都是 \( p \) 的幂次（\( p^{k_i} \)），较大的 \( k_i \) 对应的数对总和的影响更大，因此我们需要**将 \( k_i \) 降序排序后，从大到小处理每个数**，尽可能平衡两组的和。

- **题解思路对比**：多数题解（如Alex_Wei、dChengx等）均采用降序排序后贪心分配的策略，但具体实现略有不同：有的通过维护差值 \( df \) 动态调整分配（Alex_Wei），有的通过双模数避免假零问题（dChengx），还有的通过统计相同 \( k_i \) 的出现次数处理（duyi）。
- **核心算法流程**：排序 \( k_i \) → 处理 \( p=1 \) 的特殊情况（所有数为1，结果为 \( n \bmod 2 \)）→ 从大到小遍历 \( k_i \)，动态维护两组和的差值，确保每一步选择使差值最小的分配方式。
- **可视化设计**：我们将设计一个8位像素风格的动画，用不同颜色的像素块表示两组的和（如红色为第一组，蓝色为第二组），动态展示 \( k_i \) 降序排序后的处理过程，高亮当前处理的 \( k_i \) 和差值变化，用“叮”的音效提示关键操作（如分配完成）。

---

## 2. 精选优质题解参考

<eval_intro>
为了帮助大家快速掌握解题关键，我筛选了以下3份思路清晰、代码规范的优质题解（评分≥4星）。
</eval_intro>

**题解一：Alex_Wei的贪心策略（来源：Alex_Wei）**
* **点评**：这份题解的思路非常清晰，通过维护差值 \( df \) 动态调整分配策略。代码中对 \( p=1 \) 的特判、降序排序后的遍历逻辑，以及 \( df \) 的更新规则（如 \( df \) 表示当前第二组欠第一组的 \( p^{k_i} \) 单位数）都解释得很透彻。代码结构简洁，变量命名（如 \( df \)）直观，边界条件处理严谨（如提前终止遍历的条件），是贪心策略的典型实现。

**题解二：dChengx的双模数优化（来源：dChengx）**
* **点评**：此题解巧妙地引入双模数（\( 10^9+7 \) 和 \( 1621836843 \)）避免了模数下的假零问题。通过维护两个模数下的差值 \( sum1 \) 和 \( sum2 \)，确保只有当两个模数下的差值均为零时，才认为两组和相等。代码中快速幂的实现简洁高效，排序和遍历逻辑直接，适合竞赛场景。

**题解三：duyi的相同 \( k_i \) 处理（来源：duyi）**
* **点评**：此题解针对相同 \( k_i \) 的情况进行了优化，通过统计每个 \( k \) 的出现次数，从大到小处理，尝试用较小的 \( k \) 补齐差值。代码中对 \( cnt \)（出现次数）的奇偶判断、以及通过 \( \log_p n \) 限制暴力枚举范围的技巧，体现了对问题本质的深刻理解，适合进阶学习。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题时，我们通常会遇到以下3个核心难点，结合优质题解的共性，我为大家提炼了应对策略：
</difficulty_intro>

1.  **难点1：如何处理 \( p=1 \) 的特殊情况？**
    * **分析**：当 \( p=1 \) 时，所有数都是 \( 1 \)，分组后的差值即为 \( n \bmod 2 \)（奇数差为1，偶数差为0）。优质题解（如Alex_Wei）均通过特判直接处理此情况，避免后续复杂计算。
    * 💡 **学习笔记**：特判特殊情况是优化代码效率的关键，需优先处理。

2.  **难点2：如何避免模数下的假零问题？**
    * **分析**：直接维护一个模数下的差值时，可能出现差值实际非零但模数结果为零的“假零”。dChengx的题解通过双模数（如 \( 10^9+7 \) 和 \( 1621836843 \)）降低了假零概率，只有当两个模数下的差值均为零时，才认为两组和相等。
    * 💡 **学习笔记**：双模数是处理假零问题的有效手段，适用于需要高精度判断的场景。

3.  **难点3：如何动态维护差值 \( df \) 并提前终止？**
    * **分析**：在贪心过程中，若 \( df \) 增长到超过剩余数的个数（\( n-i+1 \)），则后续所有数无法补足差值，可提前终止遍历。Alex_Wei的题解通过 \( df \times p \geq n-i+1 \) 判断提前终止，避免了无效计算。
    * 💡 **学习笔记**：提前终止条件的设计能显著降低时间复杂度，需结合问题性质推导。

### ✨ 解题技巧总结
- **问题分解**：将问题拆解为特判 \( p=1 \)、排序 \( k_i \)、动态维护差值三个子问题，逐个解决。
- **双模数防假零**：维护两个不同模数下的差值，降低假零概率。
- **提前终止**：通过 \( df \) 的增长速度与剩余数个数的关系，提前终止无效遍历。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解思路的通用核心实现。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Alex_Wei的贪心策略和dChengx的双模数优化，结构清晰，适合竞赛场景。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int MOD1 = 1e9 + 7;
    const int MOD2 = 1621836843; // 避免假零的辅助模数
    const int MAXN = 1e6 + 5;

    int n, p, k[MAXN];

    // 快速幂函数，支持模数选择
    long long qpow(long long base, int exp, int mod) {
        long long res = 1;
        while (exp > 0) {
            if (exp % 2 == 1) res = res * base % mod;
            base = base * base % mod;
            exp /= 2;
        }
        return res;
    }

    void solve() {
        cin >> n >> p;
        for (int i = 1; i <= n; ++i) cin >> k[i];
        if (p == 1) {
            cout << (n % 2) << "\n";
            return;
        }
        sort(k + 1, k + n + 1, greater<int>()); // 降序排序

        long long sum1 = 0, sum2 = 0; // 双模数下的差值
        for (int i = 1; i <= n; ++i) {
            long long val1 = qpow(p, k[i], MOD1);
            long long val2 = qpow(p, k[i], MOD2);
            if (sum1 == 0 && sum2 == 0) { // 初始时，第一个数加入第一组
                sum1 = val1;
                sum2 = val2;
            } else { // 后续数加入第二组，调整差值
                sum1 = (sum1 - val1 + MOD1) % MOD1;
                sum2 = (sum2 - val2 + MOD2) % MOD2;
            }
        }
        cout << sum1 << "\n"; // 输出最小差模MOD1的结果
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int T; cin >> T;
        while (T--) solve();
        return 0;
    }
    ```
* **代码解读概要**：代码首先处理 \( p=1 \) 的特殊情况，然后将 \( k_i \) 降序排序。通过双模数 \( sum1 \) 和 \( sum2 \) 维护两组和的差值，初始时将最大的数加入第一组，后续数加入第二组并调整差值。最终输出 \( sum1 \)（即最小差模 \( 10^9+7 \) 的结果）。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点和关键逻辑。
</code_intro_selected>

**题解一：Alex_Wei的贪心策略（来源：Alex_Wei）**
* **亮点**：通过维护差值 \( df \) 动态调整分配，提前终止无效遍历。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n;i++){
        if(i>1&&df) for(int j=k[i-1]-1;j>=k[i];j--)
            if((df*=p)>=(n-i+1)){while(i<=n)b=(b+ksm(p,k[i++]))%mod; return;}
        df?(b=(b+ksm(p,k[i]))%mod,df--):(a=(a+ksm(p,k[i]))%mod,df=1);
    }
    ```
* **代码解读**：
  - `df` 表示当前第二组欠第一组的 \( p^{k_i} \) 单位数。
  - 当 \( i>1 \) 且 \( df>0 \) 时，通过 \( df *= p \) 模拟 \( p \) 进制下的单位缩小（如 \( p^3 \) 变为 \( p^2 \) 时，单位缩小 \( p \) 倍）。
  - 若 \( df \geq n-i+1 \)，说明剩余数无法补足差值，直接将剩余数加入第二组并终止遍历。
  - 否则，根据 \( df \) 的值决定将当前数加入第二组（\( df>0 \)）或第一组（\( df=0 \)）。
* 💡 **学习笔记**：\( df \) 的维护是贪心策略的核心，通过单位缩小和提前终止，确保了算法的高效性。

**题解二：dChengx的双模数优化（来源：dChengx）**
* **亮点**：双模数避免假零，确保差值判断的准确性。
* **核心代码片段**：
    ```cpp
    sum1=(sum1-qkm(p,k[i],mod1)+mod1)%mod1;
    sum2=(sum2-qkm(p,k[i],mod2)+mod2)%mod2;
    ```
* **代码解读**：
  - `sum1` 和 `sum2` 分别维护两组和的差值在 \( mod1 \) 和 \( mod2 \) 下的结果。
  - 每次将当前数加入第二组时，通过 `sum1 - val1 + mod1` 确保结果非负，再取模。
  - 仅当 `sum1` 和 `sum2` 均为零时，才认为两组和相等。
* 💡 **学习笔记**：双模数是处理模数假零问题的有效方法，适用于需要高精度判断的场景。

**题解三：duyi的相同 \( k_i \) 处理（来源：duyi）**
* **亮点**：统计相同 \( k \) 的出现次数，用较小 \( k \) 补齐差值。
* **核心代码片段**：
    ```cpp
    if(cnt&1){
        // 尝试用较小k补齐差值
        for(int kk=k-1;kk>=0;--kk){
            need*=p;
            if(need>MAXN)break;
            if(mp.count(-kk)){
                if(mp[-kk]>=need){
                    mp[-kk]-=need;
                    need=0;
                    break;
                }
                need-=mp[-kk];
                mp[-kk]=0;
            }
        }
    }
    ```
* **代码解读**：
  - 当 \( k \) 的出现次数 \( cnt \) 为奇数时，两组和相差 \( p^k \)。
  - 通过遍历较小的 \( k \)（\( k-1, k-2, \dots \)），计算需要多少个 \( p^{k'} \) 才能补齐 \( p^k \)（即 \( need \times p^{k'} = p^k \)）。
  - 若找到足够的 \( k' \)，则补齐差值；否则，将剩余数加入较小的组。
* 💡 **学习笔记**：相同 \( k \) 的处理需结合 \( p \) 进制的特性，通过统计和暴力枚举较小 \( k \) 实现差值补齐。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization_intro\>
为了更直观地理解贪心算法的执行过程，我们设计了一个8位像素风格的动画演示方案，让大家“看”到每一步如何分配 \( p^{k_i} \) 并调整差值。
\</visualization_intro\>

  * **动画演示主题**：`像素分配大战——平衡两组和的冒险`

  * **核心演示内容**：展示 \( k_i \) 降序排序后的处理过程，用红色像素块表示第一组的和，蓝色像素块表示第二组的和，动态调整两者的高度（高度代表和的大小），高亮当前处理的 \( k_i \) 并提示差值变化。

  * **设计思路简述**：采用8位像素风格（如FC游戏画面），用不同颜色区分两组和，通过像素块的移动和颜色变化直观展示分配过程。音效（如“叮”）提示关键操作，增强记忆点；游戏化的“关卡”设计（每处理完一个 \( k_i \) 算一关）增加趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为左右两部分（第一组和第二组），顶部显示降序排列的 \( k_i \)（像素数字）。
          * 控制面板包含“开始/暂停”、“单步”、“重置”按钮和速度滑块。
          * 播放8位风格的轻快背景音乐。

    2.  **初始分配**：
          * 第一个 \( k_i \)（最大的）以红色像素块形式从顶部滑入第一组区域，高度为 \( p^{k_i} \)，伴随“入队”音效。
          * 差值显示为 \( p^{k_i} \)（红色数字）。

    3.  **动态调整**：
          * 处理下一个 \( k_i \) 时，若差值为0（两组和相等），则当前数滑入第一组；否则滑入第二组，蓝色像素块高度增加 \( p^{k_i} \)，差值更新（如 \( 8 \rightarrow 8-4=4 \)）。
          * 差值变化时，用黄色箭头高亮当前操作的 \( k_i \) 和差值数字，播放“调整”音效。

    4.  **提前终止**：
          * 若 \( df \geq n-i+1 \)，剩余 \( k_i \) 全部滑入第二组，蓝色像素块高度快速增加，差值数字变为“剩余数无法补足”，播放“终止”音效。

    5.  **结果展示**：
          * 所有 \( k_i \) 处理完成后，显示最终差值（红色和蓝色像素块的高度差），播放“胜利”音效（如上升的“叮~”）。

  * **旁白提示**：
      - “当前处理最大的 \( k_i=5 \)，将其放入第一组，差值变为 \( p^5 \)。”
      - “下一个 \( k_i=4 \)，差值非零，放入第二组，差值更新为 \( p^5 - p^4 \)。”
      - “注意！差值增长过快，剩余数无法补足，提前终止分配。”

\<visualization_conclusion\>
通过这个像素动画，我们可以直观看到贪心算法如何通过优先处理大数、动态调整分配来最小化差值，理解 \( df \) 的维护和提前终止条件的意义。
\</visualization_conclusion\>

-----

## 6\. 拓展练习与相似问题思考

\<similar_problems_intro\>
理解并掌握了本题的贪心策略后，我们可以进一步思考其在其他场景的应用。
\</similar_problems_intro\>

  * **通用思路/技巧迁移**：
      - 贪心算法适用于“每一步选择当前最优”的问题，如资源分配、任务调度等。
      - 本题中“优先处理大数”的思想可迁移至“合并果子”（每次合并最小的两堆）、“活动选择”（按结束时间排序选择最多活动）等问题。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1090 合并果子** - `合并果子`
          * 🗣️ **推荐理由**：需要贪心选择最小的两堆合并，与本题“优先处理大数”思路互补，巩固贪心策略。
    2.  **洛谷 P1223 排队接水** - `排队接水`
          * 🗣️ **推荐理由**：通过排序最小化总等待时间，与本题“降序排序”思路类似，训练贪心排序的应用。
    3.  **洛谷 P1803 凌乱的yyy** - `凌乱的yyy`
          * 🗣️ **推荐理由**：活动选择问题，需按结束时间排序选择最多活动，训练贪心策略的灵活性。

-----

## 7\. 学习心得与经验分享 (若有)

\<insights_intro\>
部分题解提到了处理假零问题的经验，这对我们调试代码非常有帮助：
\</insights_intro\>

> **参考经验 (来自 dChengx)**：“在模数下，差值为零可能是假零（实际差值为模数的倍数）。通过双模数（如 \( 10^9+7 \) 和 \( 1621836843 \)）可以降低假零概率，确保判断的准确性。”

> **点评**：这位作者的经验很实用！在需要高精度判断的问题中，双模数是避免假零的有效手段。学习者在处理类似问题时，可尝试引入辅助模数，提高代码的鲁棒性。

-----

\<conclusion\>
本次关于“Johnny and Grandmaster”的C++解题分析就到这里。希望这份学习指南能帮助大家理解贪心算法的核心思想，掌握双模数防假零、提前终止等技巧。记住，编程能力的提升需要多思考、多练习，下次我们再一起探索新的编程挑战！💪
\</conclusion\>

---
处理用时：420.35秒