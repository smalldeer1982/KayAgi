# 题目信息

# Liar

## 题目描述

The first semester ended. You know, after the end of the first semester the holidays begin. On holidays Noora decided to return to Vičkopolis. As a modest souvenir for Leha, she brought a sausage of length $ m $ from Pavlopolis. Everyone knows that any sausage can be represented as a string of lowercase English letters, the length of which is equal to the length of the sausage.

Leha was very pleased with the gift and immediately ate the sausage. But then he realized that it was a quite tactless act, because the sausage was a souvenir! So the hacker immediately went to the butcher shop. Unfortunately, there was only another sausage of length $ n $ in the shop. However Leha was not upset and bought this sausage. After coming home, he decided to cut the purchased sausage into several pieces and number the pieces starting from $ 1 $ from left to right. Then he wants to select several pieces and glue them together so that the obtained sausage is equal to the sausage that Noora gave. But the hacker can glue two pieces together only when the number of the left piece is less than the number of the right piece. Besides he knows that if he glues more than $ x $ pieces, Noora will notice that he has falsified souvenir sausage and will be very upset. Of course Leha doesn’t want to upset the girl. The hacker asks you to find out whether he is able to cut the sausage he bought, and then glue some of the pieces so that Noora doesn't notice anything.

Formally, you are given two strings $ s $ and $ t $ . The length of the string $ s $ is $ n $ , the length of the string $ t $ is $ m $ . It is required to select several pairwise non-intersecting substrings from $ s $ , so that their concatenation in the same order as these substrings appear in $ s $ , is equal to the string $ t $ . Denote by $ f(s,t) $ the minimal number of substrings to be chosen so that their concatenation is equal to the string $ t $ . If it is impossible to choose such substrings, then $ f(s,t)=∞ $ . Leha really wants to know whether it’s true that $ f(s,t)<=x $ .

## 说明/提示

Let's consider the first sample.

In the optimal answer, Leha should cut the sausage he bought in the following way: hloyaygrt = h + loy + a + y + g + rt. Then he numbers received parts from $ 1 $ to $ 6 $ :

- h — number $ 1 $
- loy — number $ 2 $
- a — number $ 3 $
- y — number $ 4 $
- g — number $ 5 $
- rt — number $ 6 $

Hereupon the hacker should glue the parts with numbers $ 2 $ , $ 4 $ and $ 6 $ and get sausage loyygrt equal to one that is given by Noora. Thus, he will have to glue three pieces. Since $ x=3 $ you should print "YES" (without quotes).

In the second sample both sausages coincide with sausages from the first sample. However since $ x=2 $ you should print "NO" (without quotes).

## 样例 #1

### 输入

```
9
hloyaygrt
6
loyyrt
3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
9
hloyaygrt
6
loyyrt
2
```

### 输出

```
NO
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Liar 深入学习指南 💡

<introduction>
今天我们来分析这道“Liar”题目。它的核心是判断能否从字符串s中选取不超过x个不相交的子串，拼接成另一个字符串t。通过分析题解，我们将掌握动态规划（DP）结合字符串匹配的解题技巧，并用像素动画直观理解算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划 (DP) + 字符串处理（最长公共前缀LCP计算）

🗣️ **初步分析**：
解决这道题的关键在于用动态规划跟踪“选取j个子串时最多能匹配t的前多少位”，并结合贪心思想尽可能匹配最长的子串。  
简单来说，动态规划（DP）就像“记录每一步的最优状态”——比如，用`f[i][j]`表示s的前i个字符选j个子串时，最多能匹配t的前`f[i][j]`位。而LCP（最长公共前缀）则是用来快速找到s和t当前位置的最长匹配长度，避免逐字符比较。  

- **题解思路**：所有优质题解均采用DP状态设计，结合LCP计算（用后缀数组SA或哈希+二分实现）。核心差异在于LCP的计算方式：SA更高效（O(n log n)预处理），哈希+二分更易实现（O(n x log n)）。  
- **核心难点**：如何设计DP状态以避免状态爆炸？如何高效计算LCP？如何通过贪心确保每次匹配最长子串？  
- **可视化设计**：用8位像素风展示s和t的字符块，动态更新DP表格（如用不同颜色标记`f[i][j]`的数值变化），匹配时用闪烁箭头高亮LCP的起始和结束位置，关键操作（如状态转移）伴随“叮”的像素音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等，筛选出以下3道优质题解（均≥4星）：
</eval_intro>

**题解一：作者Alex_Wei（赞：4）**  
* **点评**：此题解思路清晰，巧妙结合后缀数组（SA）计算LCP，时间复杂度低（O(n(x + log n))）。代码规范，变量名（如`f[31][N]`）含义明确，边界处理严谨（如`i <= n`的循环条件）。亮点在于用SA预处理LCP，避免了哈希冲突的风险，适合竞赛场景。作者调试记录（如“start coding at 8:55”）也体现了实战经验。

**题解二：作者tzc_wk（赞：3）**  
* **点评**：此题解采用哈希+二分计算LCP，代码简洁易读（如`check`函数用哈希值比较），适合对SA不熟悉的学习者。动态规划转移逻辑直白（`f[i+1][j] = max(f[i+1][j], f[i][j])`），变量名（如`s1`、`s2`表示哈希前缀）易懂。亮点是将复杂的LCP计算转化为二分搜索，降低了实现难度。

**题解三：作者violin_wyl（赞：2）**  
* **点评**：此题解使用双哈希（两种模数+底数）避免冲突，代码鲁棒性强（如`mod1=11451499, mod2=19260817`的阴间模数选择）。DP状态初始化（`memset(dp, ~0x3f, sizeof(dp))`）和转移（`dp[x][j+1] = max(dp[x][j+1], ...)`）体现了严谨性。亮点是双哈希的应用，适合学习如何提高字符串匹配的准确性。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，常见的核心难点及应对策略如下：
</difficulty_intro>

1.  **关键点1：DP状态的设计**  
    * **分析**：状态`f[i][j]`需表示“s的前i个字符选j个子串时，最多能匹配t的前多少位”。这样设计是因为我们需要跟踪两个维度：s的处理位置（i）和已选子串数（j），同时记录匹配t的进度（f[i][j]）。优质题解均通过此状态覆盖所有可能的匹配情况。  
    * 💡 **学习笔记**：状态设计需同时覆盖输入的关键维度（如本题的i、j），并记录关键结果（如匹配长度）。

2.  **关键点2：LCP的高效计算**  
    * **分析**：每次转移时，需计算s从i+1开始和t从f[i][j]+1开始的最长公共前缀。SA预处理LCP数组后，可通过RMQ快速查询（O(1)）；哈希+二分则通过二分搜索（O(log n)）。SA适合大规模数据，哈希+二分更易实现。  
    * 💡 **学习笔记**：根据数据规模选择LCP计算方式——n大用SA，代码简洁用哈希+二分。

3.  **关键点3：贪心匹配最长子串**  
    * **分析**：每次选择子串时，匹配越长越好（贪心）。例如，若s[i+1..i+k]与t[f[i][j]+1..f[i][j]+k]匹配，则直接选k长度的子串，避免后续重复计算。优质题解均通过LCP确保每次匹配最长。  
    * 💡 **学习笔记**：贪心策略可大幅减少状态数，是优化DP的关键。

### ✨ 解题技巧总结
- **状态转移的“刷表法”**：先继承前一状态（不扩展子串），再尝试扩展新子串（用LCP找最长匹配）。  
- **预处理优化**：SA或哈希的预处理能将LCP查询从O(n)降至O(1)或O(log n)，避免超时。  
- **边界条件处理**：初始化时将DP数组设为极小值（如`-0x3f3f3f3f`），仅`f[0][0] = 0`（初始状态），确保合法状态被正确更新。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解，选择Alex_Wei的SA实现作为通用核心代码（高效且规范）。
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码综合了Alex_Wei的SA预处理和动态规划思路，适合理解LCP与DP的结合。  
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int K = 18;
const int N = 2e5 + 5;
int n, m, tot, x, lg[N], f[31][N];
int ht[N], mi[K][N];
char s[N], t[N], st[N];
int sa[N], rk[N], ork[N], buc[N], id[N];

bool cmp(int a, int b, int w) { return ork[a] == ork[b] && ork[a + w] == ork[b + w]; }
void build() { /* SA预处理LCP数组，代码略 */ }
int lcp(int i, int j) { /* LCP查询，代码略 */ }

int main() {
    cin >> n >> s + 1 >> m >> t + 1;
    // 拼接s和t，用特殊字符分隔
    for (int i = 1; i <= n; i++) st[++tot] = s[i];
    st[++tot] = '#';
    for (int i = 1; i <= m; i++) st[++tot] = t[i];
    build(); // 构建SA和LCP数组
    cin >> x;
    // 动态规划转移
    for (int i = 1; i <= x; i++)
        for (int j = 0; j < n; j++) {
            int L = lcp(j + 1, f[i-1][j] + 1); // 计算LCP
            f[i][j + L] = max(f[i][j + L], f[i-1][j] + L);
            f[i][j + 1] = max(f[i][j + 1], f[i][j]);
        }
    cout << (f[x][n] == m ? "YES" : "NO") << endl;
    return 0;
}
```
* **代码解读概要**：  
  代码首先将s和t拼接成一个新字符串（用`#`分隔），通过后缀数组（SA）预处理得到LCP数组。动态规划部分，`f[i][j]`表示选i个子串处理s前j个字符时，最多匹配t的前`f[i][j]`位。每次转移时，先继承前一状态（`f[i][j+1] = max(f[i][j+1], f[i][j]`），再用LCP找到最长匹配长度L，更新`f[i][j+L]`。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者Alex_Wei**  
* **亮点**：用SA预处理LCP，LCP查询时间O(1)，适合大规模数据。  
* **核心代码片段**：
```cpp
int lcp(int i, int j) { // s[i] & t[j]
    if (j > m || i > n) return 0;
    j += n + 1; // t的起始位置在s之后（s长度n，分隔符1位）
    if ((i = rk[i]) > (j = rk[j])) swap(i, j);
    int d = lg[j - (i++)];
    return min(mi[d][i], mi[d][j - (1 << d) + 1]);
}
```
* **代码解读**：  
  这段代码计算s从i开始和t从j开始的LCP。`j += n + 1`将t的位置映射到拼接后的字符串中（s占n位，分隔符占1位，t从n+2位开始）。通过SA的rk数组找到两后缀的排名，用RMQ查询LCP（mi数组存储LCP的ST表）。  
* 💡 **学习笔记**：SA预处理后，LCP查询的关键是将t的位置映射到拼接后的字符串中，确保正确性。

**题解二：作者tzc_wk**  
* **亮点**：哈希+二分实现LCP，代码简洁，适合学习。  
* **核心代码片段**：
```cpp
int get(int x, int y) { // 二分找s[x..n]和t[y..m]的最长公共前缀
    int l = x, r = min(n, m + x - y);
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(x, mid, y, mid - x + y)) l = mid + 1;
        else r = mid - 1;
    }
    return r;
}
```
* **代码解读**：  
  `get`函数通过二分搜索找到最大的mid，使得s[x..mid]等于t[y..y+(mid-x)]。`check`函数用哈希值比较两子串是否相等。二分左边界l初始为x，右边界r是s和t剩余长度的较小值（避免越界）。  
* 💡 **学习笔记**：二分搜索是求LCP的常用方法，关键是确定二分范围和终止条件。

**题解三：作者violin_wyl**  
* **亮点**：双哈希避免冲突，提高匹配准确性。  
* **核心代码片段**：
```cpp
bool check(int l1, int r1, int l2, int r2) {
    int fa1 = (ha1[r1] - ha1[l1-1] + mod1) % mod1 * inv1[l1-1] % mod1;
    int fa2 = (ha2[r1] - ha2[l1-1] + mod2) % mod2 * inv2[l1-1] % mod2;
    int fb1 = (hb1[r2] - hb1[l2-1] + mod1) % mod1 * inv1[l2-1] % mod1;
    int fb2 = (hb2[r2] - hb2[l2-1] + mod2) % mod2 * inv2[l2-1] % mod2;
    return (fa1 == fb1) && (fa2 == fb2);
}
```
* **代码解读**：  
  `check`函数计算s的子串（l1..r1）和t的子串（l2..r2）的双哈希值（mod1和mod2），只有两个哈希值都相等时才认为子串相同。双哈希大幅降低了哈希冲突的概率。  
* 💡 **学习笔记**：单哈希可能因冲突导致错误，双哈希是竞赛中常用的防冲突技巧。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
我们设计一个“像素匹配探险”动画，用8位复古风格展示DP状态转移和LCP匹配过程！
</visualization_intro>

  * **动画演示主题**：像素小探险家在s和t的字符网格中寻找匹配路径，最多使用x个“子串卷轴”。

  * **核心演示内容**：  
    展示s（左网格）和t（右网格）的字符块，动态更新DP表格（中间）。每选一个子串，探险家从s的当前位置出发，用LCP找到最长匹配，在t中标记匹配的字符，并消耗一个“子串卷轴”。

  * **设计思路简述**：  
    8位像素风（如FC游戏《超级马里奥》的色块）降低学习压力；匹配时的闪烁动画（如s[i]和t[j]同时变亮）强化视觉记忆；“子串卷轴”剩余数（x）用数字显示，增加紧张感。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：  
        - 屏幕分为三部分：左（s的n个像素块，颜色#66CCFF）、中（DP表格，行是i，列是j，初始全0）、右（t的m个像素块，颜色#FF99CC）。  
        - 控制面板：单步/自动按钮、速度滑块（1x-5x）、重置按钮。  
        - 背景音乐：8位风格的轻快旋律（类似《俄罗斯方块》BGM）。

    2.  **状态转移演示**：  
        - **继承状态**（不扩展子串）：当i=j=0时，DP[0][0]=0（绿色高亮）。点击单步，i=1，j=0，DP[1][0]继承DP[0][0]（绿色从[0][0]滑到[1][0]），伴随“滴答”音效。  
        - **扩展子串**（用LCP）：当i=2，j=0，计算LCP（s[3..n]和t[1..m]的最长前缀）。探险家从s[3]出发，用放大镜扫描t[1]，匹配到k=3个字符（s[3]→t[1], s[4]→t[2], s[5]→t[3]）。DP[5][1]更新为3（绿色从[2][0]跳到[5][1]），伴随“叮”音效。

    3.  **目标达成**：  
        - 当DP[n][x]等于m时，t的所有字符块变金色，弹出“成功！”对话框，播放胜利音效（类似《超级马里奥》吃金币声）。  
        - 若DP[n][x] < m，t的最后一个字符块变红，弹出“失败”提示，播放短促“呜”音效。

    4.  **交互控制**：  
        - 单步执行：每点击一次，执行一个状态转移，暂停时可查看当前DP值和匹配路径。  
        - 自动播放：探险家自动执行，速度可调，适合观察整体流程。

  * **旁白提示**：  
    - （单步时）“现在处理s的第i=3个字符，已用j=0个子串。当前匹配t的第0位，我们需要找最长匹配！”  
    - （匹配时）“看！s的3-5位和t的1-3位完全匹配，所以DP[5][1]更新为3！”

<visualization_conclusion>
通过这个动画，我们能直观看到DP状态如何随匹配过程更新，LCP如何帮助找到最长子串，以及x的限制如何影响最终结果。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，可尝试以下题目巩固动态规划+字符串匹配的技巧：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    本题的DP+LCP思路可用于处理“多段不相交子串匹配”问题，例如：  
    - 分割字符串成回文子串（如LeetCode 132）。  
    - 多模式串匹配（如AC自动机+DP）。  
    - 最长公共子序列的变种（如允许分割成k段）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4516 [JSOI2018] 潜入行动**  
        * 🗣️ **推荐理由**：考察动态规划状态设计，需处理多维度限制（如覆盖、选中），与本题的DP思想类似。  
    2.  **洛谷 P5496 [THUPC2019] 鸽鸽的分割**  
        * 🗣️ **推荐理由**：涉及字符串分割和匹配，需结合哈希或后缀数组，与本题的LCP计算相关。  
    3.  **洛谷 P1967 [NOIP2009 提高组] 货车运输**  
        * 🗣️ **推荐理由**：虽然是图论题，但动态规划的状态转移思想（如记录路径最大值）与本题相通。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试经验，例如作者Alex_Wei提到“调试到9:20”，这提示我们：
</insights_intro>

> **参考经验**（来自Alex_Wei）：“在实现SA时，需注意拼接s和t的顺序（s在前，t在后，用特殊字符分隔），否则LCP计算会出错。”  
> **点评**：字符串拼接的细节（如分隔符的选择）是LCP计算的关键。调试时，可打印拼接后的字符串和SA数组，确认预处理是否正确。这提醒我们，处理字符串问题时，边界和预处理的检查非常重要。

-----

<conclusion>
通过分析“Liar”这道题，我们掌握了动态规划结合LCP的解题思路，理解了如何用SA或哈希高效计算最长公共前缀，并用像素动画直观感受了算法过程。希望大家能举一反三，在类似问题中灵活运用这些技巧！下次再见~ 💪
</conclusion>

---
处理用时：151.34秒