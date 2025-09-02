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

# 💡 Kay的C++算法解析：[POI2012] PRE-Prefixuffix 深入学习指南 💡

<introduction>
今天我们来一起分析「POI2012 PRE-Prefixuffix」这道经典的字符串编程题。它的核心是**找字符串中最长的“循环同构前缀后缀”**——听起来有点绕？别担心，我们会把它拆成简单的积木，一步步搭建思路。本指南会帮你理解核心算法、避开常见坑点，还会用像素动画直观展示过程，让你“看”到字符串的变化！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理（哈希+border递推）`

🗣️ **初步分析**：
解决这道题的关键，是把“循环同构”的复杂条件**转化为简单的字符串结构**——想象字符串是一条“项链”，循环同构就是项链翻转后和原来一样。题目要求的“前缀和后缀循环同构”，其实等价于整个字符串能写成 `ABCBA` 的形式：
- `A` 是前缀和后缀的公共部分（长度为 `i`），必须相等；
- `B` 是中间部分 `T=S[i+1..n-i]` 的最长**不重叠border**（长度为 `f[i]`）；
- 我们要找最大的 `i + f[i]`（即 `AB` 的总长度）。

### 核心算法流程
1. **哈希预处理**：用字符串哈希快速判断任意两段子串是否相等（避免暴力比较的O(n)时间）；
2. **递推求f数组**：`f[i]` 表示去掉前i个和后i个字符后，中间子串的最长不重叠border长度。利用**递推关系** `f[i] ≤ f[i+1] + 2`（因为中间子串每缩小一圈，border最多减少2个字符），从大到小枚举i，快速计算f[i]；
3. **统计答案**：遍历所有合法的i（前缀i和后缀i相等），取最大的 `i + f[i]`。

### 可视化设计思路
我们会用**8位像素风**模拟字符串的变化：
- 用不同颜色标记 `A`（蓝色）、`B`（绿色）、`C`（灰色）部分；
- 递推f[i]时，用“像素箭头”指向中间子串的前后缀，相等时闪烁并播放“叮”的音效；
- 找到更大的答案时，整个`AB`区域会“发光”并播放胜利音效；
- 支持“单步执行”和“自动播放”，让你慢动作看清楚每一步的调整。


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法创新性**三个维度筛选了3份优质题解，覆盖了主流和巧妙的解法，帮你从不同角度理解问题！
</eval_intro>

### 题解一：Alex_Wei（赞41，标准线性解法）
* **点评**：这份题解是**最经典的线性解法**，思路像“搭积木”一样清晰！作者先用KMP求原串的所有border（快速找到可能的i），再用哈希预处理快速比较子串，最后利用递推关系高效计算f数组。代码风格规范（变量名如`nxt`、`hsh`、`calc`含义明确），边界处理严谨（比如`(i + f[i]) * 2 > n`时调整f[i]），还贴心地加了“双倍经验”提示（CF961F）。**亮点**是将KMP的border和哈希结合，完美覆盖了所有步骤，适合新手入门。

### 题解二：一只绝帆（赞27，巧妙转化为回文问题）
* **点评**：这是**最有创意的解法**！作者把原串重排成 `s1 s_n s2 s_{n-1}...`（比如原串是`ababba`，重排后是`a b b a a b`），把“循环同构前缀后缀”转化为“找两个相邻的回文串”——这一步像“魔法”一样，把陌生问题变成了熟悉的回文问题！然后用Manacher算法求回文半径，并用并查集快速找到最长的覆盖区间。**亮点**是“问题转化”的思维，帮你跳出固定框架，学会用已知算法解决新问题。

### 题解三：maruize（赞24，简洁递推模板）
* **点评**：这份题解是**最简洁的递推模板**！作者直接点出“f[i] ≤ f[i+1]+2”的核心关系，并用哈希判断子串相等，代码片段只有几行却覆盖了所有关键逻辑。**亮点**是把复杂的递推过程写成“模板式”代码，让你一眼就能抓住重点——对于想快速掌握核心逻辑的同学来说，这是最好的参考。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，大家常遇到3个“卡壳点”。我结合优质题解的共性，帮你提炼了**针对性策略**，让你下次遇到类似问题能“秒反应”！
</difficulty_intro>

### 1. 难点1：循环同构的条件怎么转化？
- **问题**：“前缀和后缀循环同构”听起来抽象，不知道怎么和字符串结构结合。
- **策略**：记住“循环同构=AB和BA”——所以前缀A和后缀B循环同构，意味着整个串能写成`ABCBA`（A是前缀，B是中间border，C是剩下的部分）。**转化是关键**，把陌生的“循环同构”变成熟悉的“前后缀相等+中间border”。
- 💡 **学习笔记**：复杂条件先找“等价结构”，比如循环同构→ABCBA。

### 2. 难点2：中间部分的border怎么高效计算？
- **问题**：如果暴力枚举每个i的中间border，时间复杂度是O(n²)，会超时（n=1e6）。
- **策略**：利用递推关系`f[i] ≤ f[i+1]+2`——从大到小枚举i，每次先让f[i] = f[i+1]+2，再逐步减小直到满足条件（中间前后缀相等且不重叠）。这样总调整次数不超过2n，时间复杂度是O(n)！
- 💡 **学习笔记**：找“递推关系”是优化暴力算法的常用技巧，比如本题的f数组。

### 3. 难点3：哈希怎么避免被卡？
- **问题**：自然溢出哈希（比如unsigned long long自动取模）容易被构造数据卡掉，导致错误。
- **策略**：用**双哈希**（比如两个不同的base和mod），只有当两个哈希值都相等时才认为子串相等。比如题解中的`h1`（base=29，mod=1e8+9）和`h2`（base=37，mod=1e8+7）。
- 💡 **学习笔记**：哈希要“稳”，双哈希比单哈希更安全。

### ✨ 解题技巧总结
- **技巧1：问题转化**：把循环同构转化为ABCBA结构，降低理解难度；
- **技巧2：递推优化**：用f[i] ≤ f[i+1]+2避免暴力枚举；
- **技巧3：双哈希**：用两个不同的哈希参数确保比较的正确性；
- **技巧4：边界处理**：始终注意`i ≤ n/2`和`f[i] ≤ (n-2i)/2`（中间border不重叠）。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**综合了优质题解思路的通用核心代码**，帮你建立整体框架。然后拆解3份优质题解的关键片段，点出它们的“精妙之处”！
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：本代码综合了Alex_Wei和maruize的思路，用哈希预处理+递推f数组，逻辑清晰且高效。
* **完整核心代码**：
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;
const int base = 131;
const int mod = 1e9 + 7;

int n, f[N];
ll h[N], pw[N];
char s[N];

ll calc(int l, int r) { // 计算子串s[l..r]的哈希值
    return ((h[r] - h[l-1] * pw[r-l+1] % mod) + mod) % mod;
}

bool same(int l1, int r1, int l2, int r2) { // 判断两个子串是否相等
    return calc(l1, r1) == calc(l2, r2);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> (s + 1);

    // 预处理哈希和幂次
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pw[i] = pw[i-1] * base % mod;
        h[i] = (h[i-1] * base + s[i]) % mod;
    }

    // 递推f数组：从n/2倒推到1
    int m = n / 2;
    f[m] = 0; // 当i=m时，中间子串长度为n-2m≤1，border为0
    for (int i = m-1; i >= 1; --i) {
        f[i] = f[i+1] + 2; // 先尝试加2
        // 确保f[i]不超过中间子串的一半（不重叠）
        if (f[i] + i > m) f[i] = m - i;
        // 逐步减小f[i]直到中间子串的前后缀相等
        while (f[i] > 0 && !same(i+1, i+f[i], n-i-f[i]+1, n-i)) {
            f[i]--;
        }
    }

    // 统计答案：遍历所有i，前缀i和后缀i相等时更新答案
    int ans = 0;
    for (int i = 1; i <= m; ++i) {
        if (same(1, i, n-i+1, n)) {
            ans = max(ans, i + f[i]);
        }
    }

    cout << ans << endl;
    return 0;
}
```
* **代码解读概要**：
  1. **哈希预处理**：`pw`数组存base的幂次，`h`数组存前缀哈希，`calc`函数计算子串哈希；
  2. **递推f数组**：从i=m倒推，利用`f[i] = f[i+1]+2`快速初始化，再调整到合法值；
  3. **统计答案**：遍历所有i，判断前缀i和后缀i是否相等，取最大的`i+f[i]`。

---

<code_intro_selected>
接下来拆解3份优质题解的关键片段，看看它们的“点睛之笔”！
</code_intro_selected>

### 题解一：Alex_Wei（KMP求原串border）
* **亮点**：用KMP求原串的所有border，快速找到可能的i（避免遍历所有i）。
* **核心代码片段**：
```cpp
int nxt[N]; // nxt[i]表示s[1..i]的最长border长度
// KMP求nxt数组
for (int i = 2, j = 0; i <= n; ++i) {
    while (j && s[j+1] != s[i]) j = nxt[j];
    nxt[i] = j += (s[j+1] == s[i]);
}
// 遍历原串的所有border，统计答案
for (int i = nxt[n]; i; i = nxt[i]) {
    if (i * 2 <= n) ans = max(ans, f[i] + i);
}
```
* **代码解读**：
  - `nxt`数组是KMP的核心，`nxt[i]`表示s[1..i]的最长border长度（即前缀和后缀相等的最大长度）；
  - 遍历原串的所有border（通过`i = nxt[i]`递归找），直接跳过不合法的i（`i*2 >n`），减少循环次数。
* 💡 **学习笔记**：KMP的border数组能快速找到字符串的所有“前后缀相等”的长度，是字符串题的常用工具。

### 题解二：一只绝帆（重排串+Manacher求回文）
* **亮点**：把原串重排为`s1 s_n s2 s_{n-1}...`，将循环同构转化为回文问题。
* **核心代码片段**：
```cpp
char t[N]; // 重排后的串
for (int i = 1, j = 1; j <= n; i++, j += 2) t[j] = s[i]; // 前半部分：s1,s2,...
for (int i = n, j = 2; j <= n; i--, j += 2) t[j] = s[i]; // 后半部分：s_n,s_{n-1},...
// Manacher算法求回文半径p[i]
int mr = 0, mid2 = 0;
for (int i = 1; i <= n-1; ++i) {
    if (mid2 - i -1 > 0 && mr - i -1 > 0) p[i] = min(p[mid2 - i -1], mr - i -1);
    while (t[i - p[i]] == t[i + 1 + p[i]]) p[i]++;
    if (i + 1 + p[i] > mr) { mr = i + 1 + p[i]; mid2 = 2*i + 1; }
    if (i == p[i]) vis[i + p[i]] = 1; // 标记能顶到开头的回文串
}
```
* **代码解读**：
  - 重排后的串`t`把原串的“前缀和后缀”合并成相邻的字符（比如原串的`s1`和`s_n`在`t`中是相邻的）；
  - Manacher算法求`t`的回文半径`p[i]`，`p[i]`表示以`i`和`i+1`为中心的最长回文串长度；
  - 标记能顶到开头的回文串（`i == p[i]`），这些回文串对应原串的“循环同构前缀后缀”。
* 💡 **学习笔记**：问题转化是最高级的技巧——把“循环同构”变成“回文”，用已知算法解决新问题。

### 题解三：maruize（简洁递推模板）
* **亮点**：用几行代码写出f数组的递推逻辑，直接抓住核心。
* **核心代码片段**：
```cpp
int m = n/2 + (n&1);
f[m] = 0;
for (int i = m-1; i >= 0; --i) {
    f[i] = min(f[i+1] + 2, (n - 2*i)/2); // 先加2，再取中间子串的一半
    while (f[i] > 0 && !cmp(i+1, i+f[i], n-i-f[i]+1, n-i)) {
        f[i]--; // 调整到合法
    }
}
```
* **代码解读**：
  - `(n-2*i)/2`是中间子串的最大不重叠border长度（因为border不能超过子串长度的一半）；
  - `cmp`函数判断两个子串是否相等（本质是哈希比较）；
  - 循环调整f[i]，直到满足条件。
* 💡 **学习笔记**：简洁的代码往往最能体现核心逻辑——抓住`f[i] ≤ f[i+1]+2`，其他都是细节。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“看”到字符串的变化，我设计了一个**8位像素风的动画**，像玩FC游戏一样学算法！动画主题是“字符串探险家找宝藏”，核心演示“ABCBA”结构的形成过程。
</visualization_intro>

### 动画设计细节
#### 1. 场景与UI初始化（FC风格）
- 屏幕左侧是**像素字符串**：用不同颜色块表示字符（比如`a`是红色，`b`是蓝色，`c`是绿色）；
- 屏幕右侧是**控制面板**：有“开始/暂停”“单步”“重置”按钮，还有速度滑块（1x~5x）；
- 背景是复古的“像素草地”，播放8位风格的轻松BGM（比如《超级马里奥》的背景音乐）。

#### 2. 核心步骤演示（结合动画与音效）
- **步骤1：初始化字符串**：像素字符串从左到右展开，每个字符用不同颜色闪烁一下；
- **步骤2：递推f数组**：
  - 用“蓝色箭头”指向当前i对应的前缀和后缀（`A`部分），闪烁表示“正在检查A是否相等”；
  - 用“绿色箭头”指向中间子串的前后缀（`B`部分），如果相等，播放“叮”的音效，绿色箭头变成“对勾”；
  - 如果不相等，绿色箭头变成“叉号”，`f[i]`减1，直到找到合法值；
- **步骤3：统计答案**：当找到更大的`i+f[i]`时，`A`和`B`部分同时“发光”，播放胜利音效（比如《魂斗罗》的通关音乐）；
- **步骤4：结束状态**：最终答案用“像素大字体”显示在屏幕中央，背景放“庆祝烟花”动画。

#### 3. 游戏化元素（增强趣味性）
- **关卡设计**：把递推过程分成5个“小关卡”（比如i从m到m-5是第一关），完成一关奖励“像素星星”；
- **AI自动演示**：点击“AI模式”，动画会自动执行，像“贪吃蛇AI”一样一步步找答案，你可以跟着看思路；
- **错误提示**：如果哈希比较错误，播放“滴滴”的提示音，屏幕上弹出“注意：子串不相等！”的像素文字。

<visualization_conclusion>
通过这个动画，你能**直观看到**字符串如何变成`ABCBA`，f数组如何调整，哈希如何比较——就像玩游戏一样，把抽象的算法变成“看得见、听得到”的过程！


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了本题的思路后，我们可以把**字符串哈希+递推**的技巧用到更多问题中。下面是几个相似的练习，帮你巩固所学！
</similar_problems_intro>

### 通用思路迁移
- **场景1**：找字符串的最长“循环同构子串”（比如CF961F）；
- **场景2**：求字符串的“最长双回文串”（比如P4555，用Manacher算法）；
- **场景3**：找两个字符串的“最长循环公共子串”（用哈希+后缀数组）。

### 洛谷练习推荐
1. **洛谷 P4555** - [国家集训队] 最长双回文串
   - 🗣️ **推荐理由**：和题解二的思路一样，把问题转化为回文串，能巩固“问题转化”的技巧。
2. **洛谷 CF961F** - k-substring
   - 🗣️ **推荐理由**：是本题的“双倍经验”，用哈希+递推求最长循环同构子串，直接套用本题的思路。
3. **洛谷 P3435** - [POI2006] OKR-Periods of Words
   - 🗣️ **推荐理由**：用KMP的border数组求字符串的最长周期，能巩固“border”的概念。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
从题解中，我摘录了几个**高频踩坑点**，帮你避免走弯路！
</insights_intro>

> **经验1（来自Alex_Wei）**：“自然溢出哈希会被卡，一定要用模数哈希！”  
> **点评**：很多同学用unsigned long long自动取模，容易被构造的数据（比如全a的串）卡掉。用双哈希（两个不同的base和mod）能大幅降低冲突概率。

> **经验2（来自一只绝帆）**：“问题转化比暴力更重要！”  
> **点评**：作者把循环同构转化为回文问题，用Manacher算法解决，这比暴力枚举高效得多。遇到陌生问题时，先想“有没有类似的已知问题”。

> **经验3（来自CuteMurasame）**：“递推关系能把O(n²)降到O(n)！”  
> **点评**：作者一开始用暴力枚举，结果TLE；后来用`f[i] ≤ f[i+1]+2`的递推关系，直接把时间复杂度降到O(n)，成功AC。


<conclusion>
本次关于「POI2012 PRE-Prefixuffix」的分析就到这里。记住：**字符串题的核心是“找结构+用工具”**——结构比如ABCBA，工具比如哈希、KMP、Manacher。多做相似题，多思考“转化”，你会越来越熟练！下次我们再一起探索更有趣的字符串问题～💪
</conclusion>

---
处理用时：126.36秒