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
今天我们来一起分析“[POI 2012] PRE-Prefixuffix”这道C++编程题。这道题的核心是找到字符串的最长前缀和后缀，使得它们循环同构且长度不超过原串的一半。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理与递推优化`

🗣️ **初步分析**：
解决这道题的关键在于理解循环同构的定义（如AB和BA）和如何高效找到满足条件的最长前缀后缀。简单来说，循环同构的两个子串可以看作是“首尾交换”的关系。在本题中，我们需要枚举可能的前缀长度L，验证其对应的后缀是否循环同构，并找到最大的L。

- **题解思路对比**：多数题解采用哈希（快速比较子串）+递推优化（利用f[i] = f[i+1]+2的递推关系）；少数题解（如一只绝帆）用Manacher算法转化为回文问题。核心难点是如何高效判断循环同构及优化重复计算。
- **核心算法流程**：通过KMP预处理原串的border，从大到小枚举可能的L（前缀长度），利用递推关系维护中间部分的最长border长度f[i]，每次调整f[i]到合法值后统计最大L+f[i]。
- **可视化设计**：采用8位像素风格，用不同颜色标记前缀（红）、后缀（蓝）和中间部分（绿），动态展示f[i]的调整过程（如像素块滑动、颜色渐变），关键步骤（如哈希匹配成功）伴随“叮”的音效，自动演示模式模拟递推过程。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下题解评分≥4星，值得重点参考：
</eval_intro>

**题解一：Alex_Wei的哈希+KMP递推解法**
* **点评**：此题解思路清晰，结合KMP预处理原串的border，利用递推关系优化中间部分border的计算，代码规范（如变量名nxt、f含义明确），哈希取模避免冲突，时间复杂度线性（O(n)），适合竞赛直接使用。亮点是通过势能分析证明递推的时间复杂度，确保高效性。

**题解二：maruize的递推哈希解法**
* **点评**：此题解用简洁的递推式f[i] = min(f[i+1]+2, (n-2i)/2)，结合哈希快速验证，代码简洁易懂。亮点是通过画图推导递推关系，直观解释f[i]的变化规律，适合理解递推优化的核心思想。

**题解三：MikukuOvO的哈希递推解法**
* **点评**：此题解代码结构清晰，哈希判断函数和递推逻辑分离，变量命名直观（如f[i]表示删去i个字符后的最长border）。亮点是明确限制f[i]的范围（f[i]+i ≤n/2），避免无效计算，适合新手学习边界条件处理。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于如何高效判断循环同构及优化重复计算。以下是关键步骤的分析和策略：
</difficulty_intro>

1.  **关键点1：循环同构的判断**
    * **分析**：循环同构的两个子串S1和S2可表示为AB和BA。判断时需验证S1的后缀+前缀是否等于S2（如AB的后缀B+前缀A等于BA）。通过哈希预处理原串的前缀哈希值，可在O(1)时间内比较任意子串是否相等。
    * 💡 **学习笔记**：哈希是处理字符串比较的高效工具，预处理哈希数组后，子串比较只需计算哈希差。

2.  **关键点2：中间部分border的递推优化**
    * **分析**：中间部分（删去前缀和后缀后的子串）的最长border长度f[i]满足f[i] ≤ f[i+1]+2（因为i减小时，中间部分两端各添加一个字符，border最多增加2）。从大到小枚举i时，先令f[i] = f[i+1]+2，再调整到合法值（哈希验证），避免重复计算。
    * 💡 **学习笔记**：递推关系的发现能大幅降低时间复杂度，关键是找到相邻状态的关联性。

3.  **关键点3：边界条件处理**
    * **分析**：需确保前缀和后缀长度L≤n/2，且中间部分的border长度f[i]满足i+f[i] ≤n/2（避免重叠）。递推时需限制f[i]的最大值，并在哈希验证失败时逐步减小f[i]。
    * 💡 **学习笔记**：边界条件的严谨处理是代码正确性的关键，需仔细验证每一步的合法性。

### ✨ 解题技巧总结
- **哈希预处理**：预先计算字符串的前缀哈希和幂次数组，快速比较子串是否相等。
- **递推优化**：利用相邻状态的递推关系（如f[i] = f[i+1]+2），减少重复计算，时间复杂度从O(n²)降至O(n)。
- **边界限制**：在递推过程中动态调整f[i]的最大值，确保不超过n/2-i，避免无效计算。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，结合哈希预处理和递推优化，代码简洁高效：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合Alex_Wei、maruize等题解的思路，采用哈希预处理和递推优化，适合竞赛场景。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    const int N = 1e6 + 5;
    const int mod = 1e9 + 7;
    const int base = 131;

    int n, f[N];
    ll h[N], pw[N];
    char s[N];

    ll get_hash(int l, int r) {
        return (h[r] - h[l - 1] * pw[r - l + 1] % mod + mod) % mod;
    }

    int main() {
        scanf("%d%s", &n, s + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pw[i] = pw[i - 1] * base % mod;
            h[i] = (h[i - 1] * base + s[i]) % mod;
        }

        int m = n / 2;
        for (int i = m; i >= 1; --i) {
            f[i] = f[i + 1] + 2;
            if (f[i] + i > m) f[i] = m - i; // 限制不超过n/2
            while (f[i] > 0 && get_hash(i + 1, i + f[i]) != get_hash(n - i - f[i] + 1, n - i)) {
                f[i]--;
            }
        }

        int ans = 0;
        for (int i = 1; i <= m; ++i) {
            if (get_hash(1, i) == get_hash(n - i + 1, n)) {
                ans = max(ans, i + f[i]);
            }
        }
        printf("%d\n", ans);
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先预处理哈希数组h和幂次数组pw，用于快速比较子串。然后从大到小枚举前缀长度i，利用递推关系初始化f[i]，调整到合法值后，验证前缀和后缀是否相等，统计最大i+f[i]。

---
<code_intro_selected>
接下来，分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：Alex_Wei的KMP+哈希解法**
* **亮点**：结合KMP预处理原串的border，递推中间部分的border，时间复杂度线性。
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
    这段代码从大到小枚举i（前缀长度），初始化f[i]为f[i+1]+2（递推关系），然后调整f[i]到合法值（不超过n/2且哈希匹配）。`calc`函数通过预处理的哈希数组快速比较子串是否相等。
* 💡 **学习笔记**：递推关系的应用是关键，利用i+1的结果推导i的结果，避免重复计算。

**题解二：maruize的递推哈希解法**
* **亮点**：递推式简洁，明确限制f[i]的最大值。
* **核心代码片段**：
    ```cpp
    f[i] = min(f[i+1]+2, (n-2*i)/2);
    while(x>0&&!cmp(i+1,i+x,n-i-x+1,n-i))x--;
    ```
* **代码解读**：
    `min(f[i+1]+2, (n-2*i)/2)`确保f[i]不超过中间部分长度的一半（避免重叠）。`cmp`函数通过哈希比较子串是否相等，调整x到合法值。
* 💡 **学习笔记**：限制f[i]的最大值能避免无效计算，提升效率。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解递推和哈希验证的过程，我们设计一个“像素探险家”主题的8位像素动画，模拟前缀、后缀和中间部分的动态变化。
</visualization_intro>

  * **动画演示主题**：`像素探险家寻找最长循环同构对`

  * **核心演示内容**：展示字符串的前缀（红色方块）、后缀（蓝色方块）和中间部分（绿色方块），动态调整中间部分的border长度f[i]（黄色方块），并验证哈希匹配（闪烁效果）。

  * **设计思路简述**：8位像素风格（FC红白机色调）营造轻松氛围，颜色标记区分不同部分；音效（入队“叮”、匹配“叮咚”）强化操作记忆；自动演示模式模拟递推过程，帮助理解f[i]的调整逻辑。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：屏幕显示原字符串的像素块（每个字符为一个小方块，颜色随机但固定），控制面板包含“单步”“自动”“重置”按钮和速度滑块。
    2.  **哈希预处理**：顶部显示哈希数组h和pw的计算过程（数字逐渐填充），伴随“滴答”音效。
    3.  **递推过程演示**：从i=m（n/2）开始，红色方块标记前缀i，蓝色方块标记后缀i，绿色方块标记中间部分。f[i]初始化为f[i+1]+2（黄色方块向右扩展），若超过n/2则收缩（黄色方块左移），哈希验证不通过时逐步缩短（黄色方块逐个减少）。
    4.  **哈希验证**：当调整f[i]时，比较中间部分的前后子串（黄色方块的左右部分），匹配时闪烁绿色，不匹配时闪烁红色，伴随“叮”或“嗡”音效。
    5.  **结果统计**：找到最大i+f[i]时，所有相关方块闪烁金色，播放“胜利”音效，顶部显示最终答案。

  * **旁白提示**：
      - “现在处理前缀长度i=6，中间部分的border初始化为f[7]+2=4...”
      - “哈希匹配失败，f[i]减少到3...”
      - “找到最大长度L=6，恭喜探险家完成任务！”

<visualization_conclusion>
通过这样的动画，我们能直观看到递推和哈希验证的每一步，理解f[i]的调整逻辑和循环同构的判断过程。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是字符串处理和递推优化，这类技巧在其他字符串问题中也有广泛应用：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 哈希预处理可用于快速比较子串，适用于回文判断（如最长回文子串）、字符串匹配（如KMP优化）等。
      - 递推优化适用于状态转移可表示为相邻状态关系的问题（如最长递增子序列的O(n)优化）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4555 [国家集训队] 最长双回文串**
          * 🗣️ **推荐理由**：涉及回文子串处理，需结合Manacher算法，与本题的字符串处理技巧互补。
    2.  **洛谷 P3375 [模板] KMP字符串匹配**
          * 🗣️ **推荐理由**：巩固KMP算法，理解前缀函数（border数组）的计算，本题的KMP预处理部分可在此题中深入练习。
    3.  **洛谷 P5410 [模板] 扩展KMP（Z函数）**
          * 🗣️ **推荐理由**：扩展KMP用于计算每个后缀与原串的最长公共前缀，本题的哈希比较可与Z函数结合，提升字符串处理能力。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到哈希取模的重要性（如自然溢出会被卡），以及递推关系的推导过程。以下是值得借鉴的经验：
</insights_intro>

> **参考经验 (来自 Alex_Wei)**：“自然溢出哈希会被卡，建议使用取模哈希（如mod=1e9+7）。递推关系的势能分析证明了时间复杂度的线性性，确保了算法的高效性。”

**点评**：哈希冲突是字符串问题的常见陷阱，使用双哈希（两个不同模数）或大模数取模可降低冲突概率。递推关系的推导需要结合问题特性（如本题的中间部分border变化规律），通过画图或小例子验证，确保正确性。

---

<conclusion>
本次关于“[POI 2012] PRE-Prefixuffix”的C++解题分析就到这里。希望这份指南能帮助大家理解字符串处理和递推优化的核心技巧。记住，多动手写代码、调试和验证是提升编程能力的关键！下次再见～💪
</conclusion>

---
处理用时：133.57秒