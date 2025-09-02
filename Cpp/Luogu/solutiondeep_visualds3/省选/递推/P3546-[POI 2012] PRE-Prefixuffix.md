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
# 💡 Kay的C++算法解析：[POI2012] PRE-Prefixuffix 深入学习指南 💡

<introduction>
今天我们来一起分析“[POI2012] PRE-Prefixuffix”这道字符串处理的经典题目。本指南将帮助大家梳理题目核心，理解关键算法，并掌握高效解题的技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理与哈希应用`（结合KMP算法与递推优化）

🗣️ **初步分析**：
解决这道题的关键在于理解“循环同构”的定义：两个字符串若能通过移动后缀到开头互相转换（如AB和BA），则它们是循环同构的。题目要求找到最长的前缀和后缀（长度均为L，L≤n/2），使得它们循环同构。

- **题解思路**：大部分优质题解采用“哈希+递推”的思路。首先，通过哈希快速比较子串是否相等；然后，利用递推关系优化计算：对于去掉首尾i个字符后的子串，其最长border（记为f[i]）满足f[i] ≤ f[i+1]+2，从而可以从大到小枚举i，逐步调整f[i]，避免重复计算。
- **核心难点**：如何高效判断子串循环同构，以及如何利用递推关系减少计算量。
- **可视化设计**：采用8位像素风格动画，用不同颜色的像素块表示前缀、后缀和中间子串。动态演示f[i]的递推过程（如i从n/2递减时，f[i]如何基于f[i+1]调整），高亮哈希比较的子串位置，用“叮”声提示比较成功，“嗒”声提示失败。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法有效性等维度的评估，以下题解因逻辑清晰、实现高效被选为优质参考：
</eval_intro>

**题解一：来源（Alex_Wei）**
* **点评**：这份题解思路非常清晰，结合了KMP求原串border和哈希判断子串相等，递推优化f[i]的过程解释透彻。代码规范（如nxt数组表示KMP的next数组，hsh数组存储哈希值），边界处理严谨（如f[i]的调整条件）。特别是利用“f[i] ≤ f[i+1]+2”的递推性质，将时间复杂度优化到O(n)，是竞赛中典型的高效解法。

**题解二：来源（maruize）**
* **点评**：此题解用直观的图示解释了f[i]的递推关系，代码简洁。通过从大到小枚举i，每次先令f[i] = f[i+1]+2，再调整到合法值，逻辑直接。哈希比较的实现（cmp函数）清晰，适合理解核心递推逻辑。

**题解三：来源（MikukuOvO）**
* **点评**：此题解代码风格简洁，关键变量（如f数组）命名明确。递推过程与哈希判断结合紧密，特别是对f[i]的调整条件（f[i]+i > n/2时截断）处理到位，适合快速上手。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的核心难点主要集中在以下三个方面，结合优质题解的共性，我们逐一分析：
</difficulty_intro>

1.  **关键点1：如何判断两个子串循环同构？**
    * **分析**：循环同构的子串可表示为AB和BA，因此需要判断是否存在k，使得前缀的后k个字符等于后缀的前k个字符，且前缀的前(L−k)个字符等于后缀的后(L−k)个字符。优质题解中通过哈希快速比较子串是否相等（如比较i+1到i+f[i]与n−i−f[i]+1到n−i），避免了O(L)的逐字符比较。
    * 💡 **学习笔记**：哈希是处理字符串相等问题的“加速引擎”，双哈希（不同基数+模数）可避免碰撞。

2.  **关键点2：如何高效计算f[i]？**
    * **分析**：f[i]表示去掉首尾i个字符后的子串的最长border。观察到f[i]的递推性质f[i] ≤ f[i+1]+2（去掉更多首尾字符后，中间子串的border长度最多减少2），因此从大到小枚举i时，可先令f[i] = f[i+1]+2，再逐步调整到合法值（即子串相等）。这种递推将时间复杂度优化到O(n)。
    * 💡 **学习笔记**：递推优化的关键是找到状态间的约束关系，减少重复计算。

3.  **关键点3：如何处理边界条件？**
    * **分析**：需要确保i+f[i] ≤ n/2（前缀和后缀不重叠）。优质题解中通过“if (i + f[i]) * 2 > n”截断f[i]，并在调整时不断检查哈希是否相等，确保结果合法。
    * 💡 **学习笔记**：边界条件是代码鲁棒性的关键，需在每一步调整中验证。

### ✨ 解题技巧总结
- **哈希预处理**：预先计算字符串的哈希前缀和幂次数组，快速获取任意子串的哈希值。
- **递推优化**：利用状态间的约束关系（如f[i] ≤ f[i+1]+2），从大到小枚举i，减少计算量。
- **双哈希防碰撞**：使用两组不同的基数和模数计算哈希值，避免自然溢出哈希的碰撞问题。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合Alex_Wei和maruize的题解，提炼出一个逻辑清晰、高效的核心实现，帮助大家把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了哈希预处理、KMP求border和递推优化f[i]的思路，是解决本题的典型高效实现。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int N = 1e6 + 5;
    const int mod = 1e9 + 7;
    const int base = 131;

    int n, ans;
    int nxt[N];          // KMP的next数组，用于求原串的border
    ll hsh[N], pw[N];    // 哈希前缀和幂次数组
    char s[N];
    int f[N];            // f[i]表示去掉首尾i个字符后的最长border长度

    // 计算子串[l..r]的哈希值
    inline ll calc(int l, int r) {
        l--;
        return (hsh[r] - hsh[l] * pw[r - l] % mod + mod) % mod;
    }

    int main() {
        cin >> n >> s + 1;
        // 预处理幂次数组和哈希前缀
        for (int i = pw[0] = 1; i <= n; i++) 
            pw[i] = 1ll * pw[i - 1] * base % mod;
        for (int i = 1; i <= n; i++) 
            hsh[i] = (hsh[i - 1] * base + s[i]) % mod;
        
        // KMP求原串的next数组（用于找所有border）
        for (int i = 2, j = 0; i <= n; i++) {
            while (j && s[j + 1] != s[i]) j = nxt[j];
            nxt[i] = j += (s[j + 1] == s[i]);
        }

        // 递推计算f数组
        for (int i = n / 2; i; i--) {
            f[i] = f[i + 1] + 2;  // 利用递推性质初始化
            // 调整f[i]到合法值
            while (f[i]) {
                if ((i + f[i]) * 2 > n) f[i]--;  // 不超过n/2
                else if (calc(i + 1, i + f[i]) != calc(n - i - f[i] + 1, n - i)) 
                    f[i]--;  // 哈希比较不相等，缩小f[i]
                else break;
            }
        }

        // 统计最大答案：遍历所有border i，取i + f[i]的最大值
        for (int i = nxt[n]; i; i = nxt[i]) 
            if (i * 2 <= n) ans = max(ans, f[i] + i);
        cout << ans << "\n";
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先预处理哈希前缀和幂次数组，用于快速比较子串。通过KMP求原串的next数组，找到所有可能的border。然后从大到小枚举i（前缀长度），利用递推性质初始化f[i]，并调整到合法值。最后遍历所有border，计算i+f[i]的最大值即为答案。

---
<code_intro_selected>
接下来，我们分析优质题解中的核心代码片段，学习其亮点。
</code_intro_selected>

**题解一（Alex_Wei）**
* **亮点**：结合KMP和哈希，利用next数组快速找到原串的border，递推f[i]时逻辑严谨。
* **核心代码片段**：
    ```cpp
    for (int i = n / 2; i; i--) {
        f[i] = f[i + 1] + 2;
        while (f[i]) {
            if ((i + f[i]) * 2 > n) f[i]--;
            else if (calc(i + 1, i + f[i]) != calc(n - i - f[i] + 1, n - i)) 
                f[i]--;
            else break;
        }
    }
    ```
* **代码解读**：
    这段代码是递推f[i]的核心。初始时，f[i]设为f[i+1]+2（利用递推性质），然后通过循环调整：如果i+f[i]超过n/2（不重叠条件）或子串哈希不相等（循环同构不成立），则减小f[i]，直到找到合法值。这一步确保了f[i]是去掉i个首尾字符后的最长合法border。
* 💡 **学习笔记**：递推初始化+调整的方式，将时间复杂度优化到O(n)，是处理此类问题的经典技巧。

**题解二（maruize）**
* **亮点**：用直观的图示解释递推关系，代码简洁，突出核心逻辑。
* **核心代码片段**：
    ```cpp
    for(int i=m-1;i>=0;i--){
        int&x=f[i]=min(f[i+1]+2,(n-2*i)/2);
        while(x>0&&!cmp(i+1,i+x,n-i-x+1,n-i))x--;
    }
    ```
* **代码解读**：
    这里的m是n/2，f[i]初始化为f[i+1]+2和(n-2i)/2的较小值（确保不超过n/2）。然后通过while循环调整x（即f[i]），直到子串相等。cmp函数通过哈希比较子串是否相等，保证循环同构。
* 💡 **学习笔记**：min函数处理边界条件，避免越界，是代码鲁棒性的体现。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解递推f[i]和哈希比较的过程，我们设计一个8位像素风格的动画，让算法“动起来”！
</visualization_intro>

  * **动画演示主题**：`像素探险家的字符串之旅`
  * **核心演示内容**：展示字符串S被分割为前缀、中间子串和后缀的过程，动态调整f[i]的长度，用颜色变化和音效提示哈希比较结果。

  * **设计思路简述**：采用FC红白机风格的8位像素画面（16色调色板），用不同颜色区分前缀（蓝色）、后缀（绿色）和中间子串（黄色）。通过动画演示i从n/2递减时，f[i]如何基于f[i+1]调整，高亮哈希比较的子串位置，用“叮”声提示比较成功，“嗒”声提示失败，增强操作记忆。

  * **动画帧步骤与交互关键点**：
    1. **场景初始化**：屏幕中央显示字符串S的像素块（每个字符一个小方块），下方显示控制面板（单步/自动按钮、速度滑块），背景播放8位风格的轻快音乐。
    2. **哈希预处理**：顶部显示哈希前缀数组hsh和幂次数组pw的计算过程（数字逐个生成，伴随“滴答”声）。
    3. **递推f[i]**：i从n/2开始递减，每个i对应的中间子串（i+1到n−i）用黄色高亮。f[i]初始为f[i+1]+2（绿色箭头从i+1指向i，长度+2），若超过n/2或哈希比较失败（子串颜色变红，“嗒”声），则f[i]缩短（箭头长度减小），直到合法（子串颜色变绿，“叮”声）。
    4. **统计答案**：遍历所有border i时，i+f[i]的值用红色数字弹出，最终最大的ans用金色星标标记，伴随“胜利”音效。

  * **旁白提示**：
    - “现在i=6，中间子串是位置7到9，f[6]初始设为f[7]+2=3！”
    - “检查i+f[i]=9是否超过n/2？不超过。哈希比较位置7-9和位置11-13…颜色变红，f[6]需要减1！”
    - “比较成功！f[6]最终为2，i+f[6]=8，更新答案！”

<visualization_conclusion>
通过这样的动画，我们能直观看到f[i]的递推过程和哈希比较的关键步骤，理解算法如何高效找到最大L。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是字符串循环同构的判断和递推优化，这类思路还可用于以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 字符串循环移位问题（如判断两个字符串是否为循环移位）。
    - 最长双回文子串问题（需要同时处理前缀和后缀的回文性）。
    - 多模式匹配中的子串比较（如AC自动机中的哈希预处理）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4555** - `最长双回文串`
          * 🗣️ **推荐理由**：此题需要处理两个回文子串的拼接，与本题“前缀+后缀”的思路类似，可巩固回文串和子串处理的技巧。
    2.  **洛谷 P3375** - `KMP字符串匹配`
          * 🗣️ **推荐理由**：KMP算法是处理字符串border的核心工具，本题中求原串的border即依赖KMP，此题可强化KMP的理解。
    3.  **洛谷 P5410** - `[模板] 双哈希`
          * 🗣️ **推荐理由**：本题中哈希防碰撞是关键，此题可练习双哈希的实现，避免自然溢出的缺陷。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试中的经验，对我们很有启发：
</insights_intro>

> **参考经验 (来自 Alex_Wei)**：“调试时发现自然溢出哈希会被卡，改用取模哈希后通过。这让我意识到哈希碰撞的问题，双哈希更可靠。”
>
> **点评**：这位作者的经验提醒我们，在竞赛中处理字符串问题时，应优先使用双哈希（不同基数+模数），避免因碰撞导致错误。这是提升代码鲁棒性的重要技巧。

---

<conclusion>
本次关于“[POI2012] PRE-Prefixuffix”的分析就到这里。通过理解循环同构的本质、掌握哈希和递推优化的技巧，相信大家能轻松解决这类问题。记得多动手写代码、调试验证，编程能力会在实践中不断提升！下次见~ 💪
</conclusion>

---
处理用时：153.98秒