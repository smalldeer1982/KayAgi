# 题目信息

# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()
```

### 输出

```
6
```

## 样例 #2

### 输入

```
()()()
```

### 输出

```
7
```

## 样例 #3

### 输入

```
)))
```

### 输出

```
0
```

# AI分析结果


# 💡 Kay的C++算法解析：Anton and School - 2 深入学习指南 💡

<introduction>
今天我们来一起分析“Anton and School - 2”这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`组合数学与范德蒙德卷积应用`

🗣️ **初步分析**：
> 解决“Anton and School - 2”这道题，关键在于理解并运用`组合数学与范德蒙德卷积`。简单来说，这就像在迷宫中寻找所有可能的宝藏路径，每条路径都有特定的规则（前半段全是左括号，后半段全是右括号）。在本题中，`范德蒙德卷积`主要用于高效计算符合条件的子序列数量。
   - 核心思路是枚举每个左括号作为子序列的最后一个左括号，计算其贡献
   - 难点在于避免O(n²)暴力枚举，通过范德蒙德卷积将组合数求和简化为单次组合数计算
   - 可视化方案中，我们将高亮当前处理的左括号位置，动态展示左侧左括号和右侧右括号的计数变化
   - 采用8位像素风格展示括号序列，左括号显示为绿色方块，右括号为红色方块，当前处理位置闪烁黄色
   - 动画中将加入"叮"的音效标记关键操作，组合数计算时显示像素化公式，成功累加答案时播放胜利音效

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性与优化程度、实践价值等几个方面，为大家筛选了以下评分较高（≥4星）的题解。
</eval_intro>

**题解一：(来源：_Life_)**
* **点评**：此解法思路清晰直白，直接应用范德蒙德卷积公式将原问题转化为单次组合数计算，避免了复杂的推导过程。代码规范整洁，变量名`l[]`和`r[]`含义明确，预处理阶乘和逆元的实现高效。算法上采用O(n)预处理+O(1)查询的组合数计算方式，空间优化得当。从实践角度看，代码可直接用于竞赛场景，边界处理严谨，特别是`C(n,m)`函数中处理了n<m的情况，展现了良好的健壮性。

**题解二：(来源：YuntianZhao)**
* **点评**：此解法在组合数计算上采用快速幂求逆元的方式，提供了另一种实现思路。代码结构清晰，主函数逻辑简明，预处理部分封装得当。特别值得学习的是`power()`函数的实现采用标准的快速幂模板，可复用性强。虽然在变量命名上略抽象（如`cnt1`, `cnt2`），但整体可读性良好，实践价值高。

**题解三：(来源：是个汉子)**
* **点评**：此解法详细推导了范德蒙德卷积的应用过程，教学性极强。代码中`fpow()`函数的实现采用了标准的快速幂模板，预处理部分完整规范。亮点在于将组合数计算抽象为`C(n,m)`函数并处理了非法情况，体现了良好的编程习惯。虽然变量命名可以更具体（如`qwq`, `qaq`），但核心逻辑清晰，对学习者理解组合数优化很有帮助。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下一些关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略，希望能帮助大家在后续解题时举一反三：
</difficulty_intro>

1.  **关键点：如何避免子序列重复计数？**
    * **分析**：优质解法都采用固定关键位置（最后一个左括号）的策略，确保每个子序列只被计算一次。通过枚举每个左括号位置作为子序列的"分界点"，左侧选左括号，右侧选右括号，自然避免重复。
    * 💡 **学习笔记**：固定关键位置是组合计数中避免重复的常用技巧。

2.  **关键点：如何优化组合数求和？**
    * **分析**：原始解法需要O(n²)时间计算组合数求和。通过应用范德蒙德卷积公式$\sum_{k} \binom{a-1}{k}\binom{b}{k+1} = \binom{a+b-1}{a}$，将问题转化为单次组合数计算，时间复杂度降至O(n)。
    * 💡 **学习笔记**：掌握组合恒等式（如范德蒙德卷积）能极大优化计数问题。

3.  **关键点：如何高效计算组合数？**
    * **分析**：所有优质解法都采用预处理阶乘和阶乘逆元的方式，实现O(1)的组合数查询。预处理时注意0的处理（0! = 1），并使用快速幂计算逆元。
    * 💡 **学习笔记**：阶乘与逆元预处理是组合计数问题的标准优化手段。

### ✨ 解题技巧总结
<summary_best_practices>
通过对本题及类似问题的分析，我总结了以下一些通用的解题技巧，希望对大家有所启发：
</summary_best_practices>
-   **关键位置固定法**：在序列类问题中，固定某个关键位置（如子序列的最后一个特定元素）可避免重复计数
-   **组合恒等式应用**：遇到组合数求和时，考虑能否用范德蒙德卷积等恒等式简化计算
-   **预处理优化**：对需要重复计算的数学量（如阶乘、逆元）进行预处理，将O(n)计算降至O(1)
-   **边界条件处理**：始终检查数组边界和数学边界（如组合数中n<m的情况）

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合多个优质题解思路，采用预处理阶乘逆元+范德蒙德卷积的最优解法
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    #define int long long
    const int mod = 1e9+7;
    const int maxn = 200005;
    using namespace std;

    int fac[maxn], inv[maxn];
    char s[maxn];
    int l[maxn], r[maxn]; // l[i]: 1~i的左括号数; r[i]: i~n的右括号数

    int power(int a, int b) {
        int res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    void init(int n) {
        fac[0] = 1;
        for (int i = 1; i <= n; i++) 
            fac[i] = fac[i-1] * i % mod;
        inv[n] = power(fac[n], mod-2);
        for (int i = n-1; i >= 0; i--)
            inv[i] = inv[i+1] * (i+1) % mod;
    }

    int C(int n, int m) {
        if (n < m || m < 0) return 0; // 边界处理
        return fac[n] * inv[m] % mod * inv[n-m] % mod;
    }

    signed main() {
        cin >> (s+1);
        int n = strlen(s+1);
        init(n);
        
        // 预处理前缀和
        for (int i = 1; i <= n; i++) 
            l[i] = l[i-1] + (s[i]=='(');
        for (int i = n; i >= 1; i--)
            r[i] = r[i+1] + (s[i]==')');
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i] == '(') { // 枚举作为最后一个左括号
                ans = (ans + C(l[i] + r[i] - 1, l[i])) % mod;
            }
        }
        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 该实现包含三个关键部分：
    > 1. **预处理模块**：`init()`函数预计算阶乘和逆元数组，实现O(1)组合数查询
    > 2. **前缀和计算**：`l[]`数组统计每个位置左侧的左括号数量，`r[]`统计右侧的右括号数量
    > 3. **主逻辑**：遍历字符串，当遇到左括号时，应用范德蒙德卷积公式计算贡献
    
---
<code_intro_selected>
接下来，我们将逐一剖析筛选出的优质题解中，最能体现核心逻辑的C++实现片段，并点出各自的亮点和关键代码思路。
</code_intro_selected>

**题解一：(来源：_Life_)**
* **亮点**：简洁高效地应用范德蒙德卷积，线性预处理逆元
* **核心代码片段**：
    ```cpp
    for(int i = 1; i <= n; i++) {
        if (str[i] == '(') {
            ans = (ans + C(x[i] + y[i] - 1, x[i])) % mod;
        }
    }
    ```
* **代码解读**：
    > 这段代码是算法的核心逻辑：遍历每个字符，当遇到左括号时，直接计算`C(a+b-1, a)`并累加到答案中。其中`x[i]`表示位置i左侧的左括号数（包含自身），`y[i]`表示右侧的右括号数。范德蒙德卷积的应用使得代码异常简洁。
* 💡 **学习笔记**：优质算法往往能将复杂问题转化为简洁的数学表达式

**题解二：(来源：YuntianZhao)**
* **亮点**：使用快速幂计算逆元，组合数计算完整展示
* **核心代码片段**：
    ```cpp
    long long power(long long x, int n) {
        long long ans = 1;
        while (n) {
            if (n & 1) ans = ans * x % mod;
            x = x * x % mod;
            n >>= 1;
        }
        return ans;
    }
    ```
* **代码解读**：
    > 此快速幂实现是组合数计算的基础。采用二进制分解的思想，通过对指数n的二进制位判断，将O(n)计算优化到O(log n)。参数`x`是底数，`n`是指数，返回$x^n \mod \text{mod}$。该模板可广泛应用于需要模幂运算的场景。
* 💡 **学习笔记**：快速幂是数论算法的核心基础组件，务必掌握

**题解三：(来源：是个汉子)**
* **亮点**：边界处理完善，变量含义明确
* **核心代码片段**：
    ```cpp
    int C(ll n, ll m) {
        if (n < m) return 0; // 边界处理
        return fac[n] * inv[n - m] % mod * inv[m] % mod;
    }
    ```
* **代码解读**：
    > 此组合数函数体现了良好的健壮性。首先检查`n < m`的非法情况，避免访问非法内存或逻辑错误。返回$\binom{n}{m} = \frac{n!}{(n-m)!m!} \mod \text{mod}$。函数使用预处理的阶乘和逆元数组，实现O(1)时间复杂度。
* 💡 **学习笔记**：健壮的程序必须处理边界情况，这是竞赛编程的关键

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解`范德蒙德卷积优化`是如何工作的，我基于8位像素风格设计了一个动画演示方案。通过复古的视觉风格和游戏化元素，帮助大家"看见"算法的每一步！
</visualization_intro>

  * **动画演示主题**：`括号山谷探险`

  * **核心演示内容**：`像素小人在括号序列上移动，遇到左括号时触发组合数计算，动态展示范德蒙德卷积的魔力`

  * **设计思路简述**：采用FC游戏风格的像素艺术（16色调色板），将括号序列可视化为彩色方块。当小人移动到关键位置时，触发"魔法计算"动画，通过视觉对比展示暴力枚举与卷积优化的效率差异，强化学习记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          - 屏幕顶部显示括号序列：左括号=绿色砖块(■)，右括号=红色砖块(□)
          - 底部控制面板：开始/暂停/步进按钮，速度滑块(▲1x▼10x)
          - 右侧信息区：显示当前答案、位置、组合数公式
          - 背景：8-bit风格的山谷像素画，播放轻快的芯片音乐

    2.  **小人移动与数据统计**：
          - 像素小人(黄色▲)从左向右移动，经过位置时方块短暂高亮
          - 实时显示当前位置i和两个统计量：左侧左括号数l[i]（绿色数字），右侧右括号数r[i]（红色数字）
          - 当遇到左括号时：该方块闪烁3次（黄→绿→黄→绿），播放"叮"的音效

    3.  **组合数计算演示**：
          - 小人停下，弹出气泡框显示公式：`C(l[i] + r[i] - 1, l[i])`
          - 背景显示虚拟计算：$\binom{a+b-1}{a}$ 的像素化数字
          - 右侧信息区更新：`ans += C(...) = [值]`
          - 同时播放"咔嗒"计算音效，公式中的变量随实际值闪烁

    4.  **卷积原理对比演示**：
          - 按空格键触发"对比模式"：屏幕分割显示
          - 左侧：暴力枚举法（O(n²)），显示∑和嵌套循环
          - 右侧：卷积优化（O(1)），显示单次组合数计算
          - 用不同颜色流动箭头展示数据依赖关系

    5.  **结果展示**：
          - 当遍历完成时，所有贡献过的左括号保持绿色高亮
          - 答案区金色闪烁，播放胜利音效（短促的上扬旋律）
          - 弹出统计面板：总步数n vs 有效计算次数（左括号数量）

    6.  **游戏化元素**：
          - 每正确计算一个位置得10金币，显示连击计数器
          - 收集满20金币触发"技能解锁"：展示范德蒙德卷积证明
          - 通关后根据效率评分（计算次数/n）给予奖杯（铜/银/金）

  * **技术实现要点**：
      - 使用Canvas绘制动画，每个括号用16x16像素块表示
      - 状态更新函数：`updateState()`处理位置移动，`calculate()`处理组合数计算
      - 音效使用Web Audio API，8-bit音效生成器

<visualization_conclusion>
通过这样一个融合了像素艺术和数学美学的动画，我们能直观理解`范德蒙德卷积`如何将O(n²)问题优化为O(n)，并在游戏中掌握组合计数的核心技巧！
</visualization_conclusion>

-----

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考该算法/技巧的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - `组合计数+固定位置法` 不仅能解决括号序列问题，也常用于：
        1. 路径计数问题（如网格路径不穿越对角线）
        2. 栈操作序列计数（如卡特兰数相关问题）
        3. 二进制序列问题（如固定某个1的位置）

  * **练习推荐 (洛谷)**：
    以下是几道洛谷上与本题考察知识点或思维方式相关的题目：

    1.  **洛谷 P3200 [HNOI2009]有趣的数列**
          * 🗣️ **推荐理由**：同样需要组合计数技巧，是卡特兰数的经典应用，可巩固组合数预处理技能
    
    2.  **洛谷 P1641 [SCOI2010]生成字符串**
          * 🗣️ **推荐理由**：组合计数与卡特兰数变形，需要类似的位置固定思想
    
    3.  **洛谷 P2532 [AHOI2012]树屋阶梯**
          * 🗣️ **推荐理由**：卡特兰数应用的经典问题，训练组合数优化技巧

-----

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中多位作者分享了宝贵的调试经验，这些实战技巧对我们至关重要：
</insights_intro>

> **参考经验 (来自 是个汉子)**："我在边界处理上卡了很久，特别是组合数中n<m的情况，最后通过添加`if(n<m)return 0`解决"
>
> **点评**：这是非常典型的边界问题。在组合计数中，始终需要检查`C(n,m)`中n≥m的条件，否则会导致数组越界或逻辑错误。建议在组合数函数开头就处理这种情况。

> **参考经验 (来自 _Life_)**："预处理逆元时忘记处理0的阶乘，导致WA"
>
> **点评**：数学预处理的常见陷阱。记住：0! = 1，且0的逆元也需要特殊处理。建议初始化时显式设置`fac[0]=inv[0]=1`

> **参考经验 (来自 Last_Reincarnation)**："范德蒙德卷积的指标变换容易出错，我通过实际数值验证公式"
>
> **点评**：当推导复杂公式时，用小规模数据手工计算验证是极其有效的调试手段。

-----

<conclusion>
本次关于"Anton and School - 2"的C++解题分析就到这里。记住，算法能力的提升在于：理解本质→掌握优化→勤于实践。下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：201.28秒