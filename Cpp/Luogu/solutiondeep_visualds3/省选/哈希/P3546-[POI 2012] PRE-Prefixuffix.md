# 题目信息

# [POI 2012] PRE-Prefixuffix

## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。

## 说明/提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。

## 样例 #1

### 输入

```
15
ababbabababbaab```

### 输出

```
6```

# AI分析结果



---
# 💡 Kay的C++算法解析：[POI 2012] PRE-Prefixuffix 深入学习指南 💡

<introduction>
今天我们来一起分析“[POI 2012] PRE-Prefixuffix”这道C++编程题。题目要求找到最长的前缀和后缀，使得它们循环同构（即可以通过移动后缀到开头相互转换）。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理与哈希应用` (结合KMP算法与递推优化)

🗣️ **初步分析**：
> 解决这道题的关键在于理解“循环同构”的本质——两个字符串可表示为AB和BA的形式。我们需要找到最长的L（L≤n/2），使得长度为L的前缀和后缀满足这一条件。  
> 核心思路是利用字符串的`border`（前缀和后缀相等的子串）性质，结合哈希快速比较子串是否相等，并通过递推优化时间复杂度。具体来说：  
> - **border的递推关系**：对于每个可能的L（记为i），去掉首尾i个字符后的子串的最长border（记为f[i]），满足f[i] ≤ f[i+1]+2。这是因为当i减小时，中间子串的border可能最多增加2（首尾各扩展一个字符）。  
> - **哈希的作用**：快速判断两个子串是否相等，避免O(n²)的暴力比较。  
> - **可视化设计**：我们将用8位像素风格展示字符串的每个字符，用不同颜色标记当前处理的i值、对应的子串边界，以及哈希比较的结果。动画中会有“入队”音效提示哈希计算，“叮”声提示子串相等，帮助直观理解递推过程。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性及实践价值，筛选出以下4星及以上题解：
</eval_intro>

**题解一：Alex_Wei的题解（来源：洛谷用户）**
* **点评**：此题解思路清晰，结合KMP求原串border和哈希比较子串，利用递推关系将时间复杂度优化至O(n)。代码规范（如变量名nxt表示KMP的next数组，hsh表示哈希数组），边界处理严谨（如检查i + f[i]是否超过n/2）。亮点在于通过势能分析证明递推的线性复杂度，适合竞赛参考。

**题解二：maruize的题解（来源：洛谷用户）**
* **点评**：此题解用直观的图示解释border的递推关系（f[i] ≤ f[i+1]+2），代码简洁。通过反向枚举i，维护f[i]并逐步调整，逻辑直白。亮点是将问题转化为求中间子串的border，降低理解难度。

**题解三：Leasier的题解（来源：洛谷用户）**
* **点评**：此题解从循环同构的定义出发，结合哈希预处理和递推优化，代码结构清晰（如init函数初始化哈希，get_hash函数快速取哈希值）。亮点是通过“先假设f[i] = f[i+1]+2，再调整”的策略，高效解决问题，适合新手学习。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下核心难点，结合优质题解的共性，提炼思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何将循环同构转化为border问题？**
    * **分析**：循环同构的两个字符串AB和BA，等价于原串可表示为ABSBA（A是前缀，B是中间子串的border）。因此，我们需要找到最大的A长度i，使得中间子串（去掉首尾i个字符）的最长border为f[i]，总长度为i+f[i]。
    * 💡 **学习笔记**：循环同构的本质是寻找嵌套的border结构，外层border（A）和内层border（B）的组合。

2.  **关键点2：如何高效计算每个i对应的f[i]？**
    * **分析**：直接暴力计算每个i的f[i]会超时（O(n²)）。优质题解利用递推关系f[i] ≤ f[i+1]+2，从大到小枚举i，初始时f[i] = f[i+1]+2，再调整至合法（子串相等且不重叠）。此策略将时间复杂度优化至O(n)。
    * 💡 **学习笔记**：递推关系的发现是优化关键，利用问题的单调性减少重复计算。

3.  **关键点3：如何避免哈希冲突？**
    * **分析**：单哈希可能被卡（如自然溢出），优质题解采用双哈希（两个不同基数和模数）或取模哈希（如mod=1e9+7），确保比较的准确性。
    * 💡 **学习笔记**：哈希比较时，双哈希更安全；取模哈希需注意负数处理（+mod后再取模）。

### ✨ 解题技巧总结
- **问题转化**：将循环同构转化为嵌套的border问题，简化求解目标。
- **递推优化**：利用f[i]与f[i+1]的关系，反向枚举i，减少重复计算。
- **双哈希防冲突**：使用两个不同的哈希参数，避免哈希碰撞导致错误。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解的通用核心实现，结合了哈希预处理、递推优化和边界检查。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Alex_Wei和Leasier的思路，使用双哈希防冲突，反向枚举i并递推f[i]，确保高效正确。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int N = 1e6 + 5;
    const int base1 = 131, base2 = 13331;
    const int mod1 = 1e9 + 7, mod2 = 1e9 + 9;

    int n, ans;
    char s[N];
    ll h1[N], h2[N], p1[N], p2[N]; // 双哈希数组

    // 预处理哈希和幂次
    void init_hash() {
        p1[0] = p2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            p1[i] = (p1[i-1] * base1) % mod1;
            p2[i] = (p2[i-1] * base2) % mod2;
            h1[i] = (h1[i-1] * base1 + s[i]) % mod1;
            h2[i] = (h2[i-1] * base2 + s[i]) % mod2;
        }
    }

    // 双哈希比较子串是否相等
    bool check(int l1, int r1, int l2, int r2) {
        if (l1 > r1 || l2 > r2) return false;
        ll hash1_1 = (h1[r1] - h1[l1-1] * p1[r1 - l1 + 1] % mod1 + mod1) % mod1;
        ll hash1_2 = (h1[r2] - h1[l2-1] * p1[r2 - l2 + 1] % mod1 + mod1) % mod1;
        ll hash2_1 = (h2[r1] - h2[l1-1] * p2[r1 - l1 + 1] % mod2 + mod2) % mod2;
        ll hash2_2 = (h2[r2] - h2[l2-1] * p2[r2 - l2 + 1] % mod2 + mod2) % mod2;
        return hash1_1 == hash1_2 && hash2_1 == hash2_2;
    }

    int main() {
        scanf("%d%s", &n, s + 1);
        init_hash();
        int m = n / 2;
        vector<int> f(m + 2, 0); // f[i]表示去掉首尾i个字符后的最长border

        // 反向枚举i，递推f[i]
        for (int i = m; i >= 1; --i) {
            f[i] = min(f[i + 1] + 2, m - i); // 初始化为f[i+1]+2，不超过m-i
            // 调整f[i]至合法
            while (f[i] > 0 && !check(i + 1, i + f[i], n - i - f[i] + 1, n - i)) {
                f[i]--;
            }
            // 检查当前i的前缀和后缀是否相等（即A是否合法）
            if (check(1, i, n - i + 1, n)) {
                ans = max(ans, i + f[i]);
            }
        }
        printf("%d\n", ans);
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先预处理双哈希数组，用于快速比较子串。然后从大到小枚举i（可能的L值），利用递推关系初始化f[i]，并调整至合法（子串相等且不重叠）。最后检查当前i的前缀和后缀是否相等，更新最大答案。核心逻辑在反向枚举和递推调整f[i]，确保线性时间复杂度。

---
<code_intro_selected>
接下来，分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：Alex_Wei的题解（来源：洛谷用户）**
* **亮点**：结合KMP求原串border，哈希比较中间子串，递推优化时间复杂度。
* **核心代码片段**：
    ```cpp
    for(int i = n / 2; i; i--) {
        f[i] = f[i + 1] + 2;
        while(f[i]) {
            if((i + f[i]) * 2 > n) f[i]--;
            else if(calc(i + 1, i + f[i]) != calc(n - i - f[i] + 1, n - i)) f[i]--;
            else break;
        }
    }
    ```
* **代码解读**：
    > 这段代码实现了f[i]的递推。初始时f[i]设为f[i+1]+2（利用递推关系），然后检查两种不合法情况：i+f[i]超过n/2（重叠）或子串不相等，逐步减小f[i]直到合法。这一步是线性复杂度的关键。
* 💡 **学习笔记**：递推时需同时考虑长度限制和子串相等条件，逐步调整确保正确性。

**题解二：maruize的题解（来源：洛谷用户）**
* **亮点**：用图示解释递推关系，代码简洁直观。
* **核心代码片段**：
    ```cpp
    for(int i=m-1;i>=0;i--){
        int&x=f[i]=min(f[i+1]+2,(n-2*i)/2);
        while(x>0&&!cmp(i+1,i+x,n-i-x+1,n-i))x--;
    }
    ```
* **代码解读**：
    > 这里的f[i]初始化为f[i+1]+2，并取最小值（避免超过中间子串长度的一半）。然后循环检查子串是否相等，调整x至合法。min操作确保不重叠，while循环确保子串相等。
* 💡 **学习笔记**：min操作是边界处理的关键，避免i+f[i]超过允许范围。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解递推过程和哈希比较，我们设计一个“像素字符串探险”的8位风格动画。
</visualization_intro>

  * **动画演示主题**：`像素字符串的循环探险`（8位FC风格，背景为复古游戏界面）

  * **核心演示内容**：展示字符串的每个字符（像素方块），动态调整i值（当前处理的L）和f[i]（中间子串的border长度），高亮哈希比较的子串，用音效提示关键操作。

  * **设计思路简述**：8位像素风格降低学习压力；动态调整i和f[i]的动画展示递推过程；哈希比较的高亮和音效强化关键步骤记忆；游戏化的“过关”提示（如每完成一个i的处理，分数+1）增加趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为三部分：顶部显示原字符串（像素方块，每个字符标有字母），中间显示控制面板（开始/暂停、单步、速度滑块），底部显示当前i、f[i]值及哈希比较结果。
          * 播放8位风格背景音乐（如《超级玛丽》主题变奏）。

    2.  **哈希预处理**：
          * 每个字符的哈希值以数字气泡形式从左到右生成（如字符'a'生成哈希值131，伴随“滴”声）。

    3.  **反向枚举i**：
          * i从n/2开始，以像素箭头从右向左移动（伴随“唰”声），当前i值用红色高亮。

    4.  **f[i]的递推与调整**：
          * 初始时f[i]设为f[i+1]+2（绿色像素条从i+1的位置延伸到i的位置）。
          * 若i+f[i]超过n/2（重叠），绿色条缩短（伴随“叮”声）；若子串哈希不等（红色叉号），绿色条逐步缩短（伴随“滴答”声），直到合法（绿色对号，伴随“成功”音效）。

    5.  **答案更新**：
          * 当i的前缀和后缀哈希相等时（蓝色对号），总长度i+f[i]用金色数字弹出，更新最大答案（顶部显示“当前最大：XX”）。

    6.  **AI自动演示**：
          * 点击“AI演示”，算法自动执行，像素箭头快速移动，绿色条动态调整，展示完整递推过程。

  * **旁白提示**：
      * “当前处理i=5，f[5]初始为f[6]+2=3”
      * “i+f[i]=8，超过n/2=7，缩短f[5]至2”
      * “子串比较失败，继续缩短f[5]至1”
      * “子串相等！当前总长度为5+1=6”

<visualization_conclusion>
通过这样的动画，我们可以直观看到i和f[i]的递推过程，以及哈希比较如何影响f[i]的调整，轻松理解算法的核心逻辑。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，可尝试以下题目巩固字符串处理与哈希应用：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的递推优化和哈希比较，可用于处理其他需要快速比较子串的问题（如最长回文子串、重复子串检测）。
      * 利用border性质的思路，可迁移到KMP算法相关的题目（如求字符串周期）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4555 [国家集训队] 最长双回文串**
          * 🗣️ **推荐理由**：本题需要求两个回文子串的拼接，与本题的嵌套border思路类似，可练习回文串处理和哈希应用。
    2.  **洛谷 P3375 [模板] KMP字符串匹配**
          * 🗣️ **推荐理由**：巩固KMP算法的next数组计算，理解border的本质。
    3.  **洛谷 P5410 [模板] 扩展KMP（Z算法）**
          * 🗣️ **推荐理由**：学习扩展KMP的Z数组，处理更复杂的子串匹配问题。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，值得借鉴：
</insights_intro>

> **参考经验 (来自 Alex_Wei)**：“在调试时，发现自然溢出哈希被卡，改用取模哈希后通过。这让我意识到哈希参数的选择很重要，双哈希更安全。”
>
> **点评**：作者的经验提醒我们，哈希冲突可能导致错误，特别是在竞赛中。使用双哈希（不同基数和模数）或大质数模数，能有效避免此类问题。调试时可打印关键哈希值，快速定位冲突。

---

<conclusion>
本次关于“[POI 2012] PRE-Prefixuffix”的分析就到这里。通过理解循环同构的本质、掌握递推优化和哈希技巧，相信大家能轻松解决此类问题。记得多练习，在实践中巩固知识！下次见～💪
</conclusion>

---
处理用时：152.16秒