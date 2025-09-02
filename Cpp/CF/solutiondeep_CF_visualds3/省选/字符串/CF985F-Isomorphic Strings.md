# 题目信息

# Isomorphic Strings

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase English letters.

For two given strings $ s $ and $ t $ , say $ S $ is the set of distinct characters of $ s $ and $ T $ is the set of distinct characters of $ t $ . The strings $ s $ and $ t $ are isomorphic if their lengths are equal and there is a one-to-one mapping (bijection) $ f $ between $ S $ and $ T $ for which $ f(s_{i})=t_{i} $ . Formally:

1. $ f(s_{i})=t_{i} $ for any index $ i $ ,
2. for any character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/f0f59850188390351c083ddc0339cc47c4315e9d.png) there is exactly one character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/cfd6520533d25a050303bbfc24cf098c4a7d5d3f.png) that $ f(x)=y $ ,
3. for any character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/cfd6520533d25a050303bbfc24cf098c4a7d5d3f.png) there is exactly one character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/f0f59850188390351c083ddc0339cc47c4315e9d.png) that $ f(x)=y $ .

For example, the strings "aababc" and "bbcbcz" are isomorphic. Also the strings "aaaww" and "wwwaa" are isomorphic. The following pairs of strings are not isomorphic: "aab" and "bbb", "test" and "best".

You have to handle $ m $ queries characterized by three integers $ x,y,len $ ( $ 1<=x,y<=n-len+1 $ ). For each query check if two substrings $ s[x...\ x+len-1] $ and $ s[y...\ y+len-1] $ are isomorphic.

## 说明/提示

The queries in the example are following:

1. substrings "a" and "a" are isomorphic: $ f(a)=a $ ;
2. substrings "ab" and "ca" are isomorphic: $ f(a)=c $ , $ f(b)=a $ ;
3. substrings "bac" and "aba" are not isomorphic since $ f(b) $ and $ f(c) $ must be equal to $ a $ at same time;
4. substrings "bac" and "cab" are isomorphic: $ f(b)=c $ , $ f(a)=a $ , $ f(c)=b $ .

## 样例 #1

### 输入

```
7 4
abacaba
1 1 1
1 4 2
2 1 3
2 4 3
```

### 输出

```
YES
YES
NO
YES
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Isomorphic Strings 深入学习指南 💡

<introduction>
今天我们来一起分析“Isomorphic Strings”这道C++编程题。这道题的关键在于判断两个子串是否可以通过字符的一一映射（双射）互相转换。本指南将帮助大家理解核心思路、掌握哈希技巧，并通过可视化动画直观感受算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（哈希方法结合字符串特征提取）`

🗣️ **初步分析**：
解决这道题的关键在于“如何用哈希表示字符串的同构特征”。简单来说，同构的两个字符串，其字符的“出现模式”必须一致——比如，第一个字符串中的第一个字符出现的位置，在第二个字符串中必须对应另一个唯一字符的相同位置模式。我们可以用哈希来捕捉这种模式。

举个例子，对于字符串 "aab" 和 "bbc"，它们的同构性体现在：第一个字符在第1、2位出现（模式为110），第二个字符在第3位出现（模式为001），第三个字符不出现（模式为000）。如果两个子串的所有26个字符的模式哈希值排序后相同，它们就是同构的。

- **题解思路**：所有优质题解均采用“字符01串哈希+排序比较”的思路：对每个字符生成01串（该位置是否为当前字符），计算哈希值，排序后比较两组哈希值是否一致。
- **核心难点**：如何高效表示字符的出现模式，避免哈希冲突。
- **可视化设计**：动画将用像素方块表示字符串位置，每个字符对应一种颜色，动态生成01串并计算哈希，最后排序比较哈希值。关键步骤（如01串生成、哈希计算、排序）会用高亮和音效提示。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性的评估，以下题解因逻辑清晰、实现高效被选为优质题解（评分≥4星）。
</eval_intro>

**题解一：作者peterwuyihong**
* **点评**：此题解直接抓住问题本质，通过预处理每个字符的01串哈希，每次查询时提取26个哈希值并排序比较。代码简洁规范（如`f[j][i]`表示前i位字符j的哈希值），变量命名直观。亮点在于使用单哈希+模数优化，时间复杂度O(n+26m log26)，适合竞赛场景。作者提到“自然溢出挂了”，提醒我们注意哈希冲突问题。

**题解二：作者rui_er**
* **点评**：此题解结构工整，使用模板类封装哈希逻辑（`struct Hash`），代码复用性强。通过`rep`宏简化循环，变量`hsh[26]`存储各字符的哈希数组，逻辑清晰。亮点是将哈希初始化和查询分离，提升代码可读性，适合学习模块化编程。

**题解三：作者yeshubo_qwq**
* **点评**：此题解强调双哈希的重要性（“单哈希容易被卡”），并给出双哈希实现。通过`node`结构体封装26个哈希值，重载`==`运算符简化比较。代码中`read`函数处理输入，`check`函数生成排序后的哈希数组，逻辑严谨。亮点是双哈希降低冲突概率，适合高要求场景。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题时，我们需要突破以下关键难点，并掌握对应的解题策略：
</difficulty_intro>

1.  **关键点1：如何表示字符的“出现模式”？**
    * **分析**：同构的核心是“字符的出现位置模式相同”。例如，若字符a在子串的第1、3位出现，则对应字符b也需在另一子串的第1、3位出现。优质题解通过生成01串（当前位置是否为该字符）来表示此模式，并用哈希压缩01串为数值。
    * 💡 **学习笔记**：01串是捕捉字符出现位置的“指纹”，哈希是压缩指纹的高效方法。

2.  **关键点2：如何避免哈希冲突？**
    * **分析**：单哈希可能因模数选择不当导致不同模式哈希值相同（冲突）。优质题解多采用双哈希（两个不同基数和模数），只有两组哈希值均匹配时才判定为同构，大幅降低冲突概率。
    * 💡 **学习笔记**：双哈希是竞赛中避免哈希冲突的常用技巧。

3.  **关键点3：如何高效比较两组模式？**
    * **分析**：直接比较26个哈希值的顺序无意义（因字符映射可能不同），但排序后比较可消除顺序影响。例如，两组哈希值排序后若完全相同，说明存在一一映射关系。
    * 💡 **学习笔记**：排序是消除字符顺序差异的关键步骤。

### ✨ 解题技巧总结
<summary_best_practices>
- **特征提取**：将复杂问题转化为可计算的特征（如01串哈希）是关键。
- **双哈希防冲突**：使用两个不同的哈希参数（基数、模数）降低冲突概率。
- **排序消除顺序**：通过排序统一特征的顺序，便于比较。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合多个优质题解的思路，提炼出一个简洁高效的通用核心实现，帮助大家快速掌握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了peterwuyihong和yeshubo_qwq的思路，采用双哈希防冲突，预处理每个字符的01串哈希，查询时排序比较。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int N = 2e5 + 5;
    const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
    const int BASE1 = 13331, BASE2 = 131;

    int n, m;
    char s[N];
    ll h1[26][N], h2[26][N]; // 分别存储26个字符的两种哈希值
    ll p1[N], p2[N]; // 预处理的幂次

    void init() {
        p1[0] = p2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            p1[i] = p1[i-1] * BASE1 % MOD1;
            p2[i] = p2[i-1] * BASE2 % MOD2;
        }
        for (int c = 0; c < 26; ++c) {
            for (int i = 1; i <= n; ++i) {
                h1[c][i] = (h1[c][i-1] * BASE1 + (s[i] == 'a' + c)) % MOD1;
                h2[c][i] = (h2[c][i-1] * BASE2 + (s[i] == 'a' + c)) % MOD2;
            }
        }
    }

    pair<ll, ll> get_hash(int c, int l, int r) {
        ll hash1 = (h1[c][r] - h1[c][l-1] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
        ll hash2 = (h2[c][r] - h2[c][l-1] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;
        return {hash1, hash2};
    }

    int main() {
        scanf("%d%d%s", &n, &m, s + 1);
        init();
        while (m--) {
            int x, y, len;
            scanf("%d%d%d", &x, &y, &len);
            vector<pair<ll, ll>> a, b;
            for (int c = 0; c < 26; ++c) {
                a.push_back(get_hash(c, x, x + len - 1));
                b.push_back(get_hash(c, y, y + len - 1));
            }
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());
            puts(a == b ? "YES" : "NO");
        }
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先预处理每个字符的01串哈希（`h1`和`h2`数组分别存储两种哈希值），然后通过`get_hash`函数快速计算任意子串的哈希值。查询时，提取两个子串的26个哈希值，排序后比较是否相同，从而判断同构性。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：作者peterwuyihong**
* **亮点**：代码简洁，单哈希实现，适合快速验证思路。
* **核心代码片段**：
    ```cpp
    for(int i=0;i<26;i++)va.push_back(H(l,l+len-1,i));
    for(int i=0;i<26;i++)vb.push_back(H(r,r+len-1,i));
    sort(va.begin(),va.end()),sort(vb.begin(),vb.end());
    cout<<(va==vb?"YES":"NO")<<endl;
    ```
* **代码解读**：
    这段代码提取两个子串的26个字符哈希值（`va`和`vb`），排序后比较。为什么排序？因为同构允许字符重映射，排序后哈希值的顺序不再重要，只要集合相同即可。例如，若子串1的哈希集合是`{h_a, h_b, h_c}`，子串2的是`{h_x, h_y, h_z}`，排序后若相等，则存在映射`a→x, b→y, c→z`。
* 💡 **学习笔记**：排序是消除字符顺序差异的关键操作。

**题解二：作者yeshubo_qwq（双哈希）**
* **亮点**：双哈希降低冲突概率，代码健壮性强。
* **核心代码片段**：
    ```cpp
    struct node{
        int num[26];
        bool operator == (const node &t) const {
            go(i,0,25) if (num[i]!=t.num[i]) return 0;
            return 1;
        }
    };
    node check(int l,int r){
        node tmp;
        go(c,0,25) tmp.num[c]=query(l,r,c);
        sort (tmp.num,tmp.num+26);
        return tmp;
    }
    ```
* **代码解读**：
    `node`结构体存储26个哈希值，重载`==`运算符简化比较。`check`函数生成排序后的哈希数组，确保两个子串的哈希集合相同即同构。双哈希通过两个`Hash`实例实现，只有两组哈希值均匹配时才返回`YES`。
* 💡 **学习笔记**：双哈希是竞赛中应对严格判题的“安全牌”。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“字符模式哈希+排序比较”的过程，我们设计一个8位像素风格的动画，模拟哈希生成、排序和比较的每一步！
</visualization_intro>

  * **动画演示主题**：`像素哈希探险——寻找同构宝藏`

  * **核心演示内容**：
    两个“哈希小探险家”分别处理两个子串，生成每个字符的01串（像素块闪烁表示1，灰色表示0），计算哈希值（数字气泡弹出），排序后比较哈希值是否一致（相同则发射烟花，不同则显示问号）。

  * **设计思路简述**：
    8位像素风（类似FC游戏）降低学习压力；01串生成时的闪烁音效（“叮”）强化操作记忆；排序时哈希值像扑克牌一样重新排列，直观展示消除顺序差异的过程。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕分为左右两部分，分别显示两个子串的像素块（每个位置一个小方块，颜色代表原字符）。
        - 底部控制面板：单步/自动按钮、速度滑块、重置按钮。
        - 背景音乐：8位风格的轻快旋律。

    2.  **01串生成**：
        - 选择字符a（例如），左子串的位置块若为a则变为亮绿色（1），否则灰色（0），伴随“滴”音效。
        - 右子串同步生成对应字符的01串（颜色不同，如亮蓝色）。

    3.  **哈希计算**：
        - 01串从左到右滚动，每个像素块的数值（1或0）被“哈希计算器”（一个像素风格的小机器）处理，最终弹出一个哈希值气泡（如“12345”）。

    4.  **排序比较**：
        - 左右两侧的26个哈希值气泡像扑克牌一样升序排列。
        - 若排序后的气泡完全一致，播放“胜利”音效（上扬音调），并弹出“YES”标志；否则播放“错误”音效（短促“咚”），弹出“NO”标志。

    5.  **交互控制**：
        - 单步模式：点击“下一步”逐步查看01串生成、哈希计算、排序的每一步。
        - 自动模式：滑块调节速度，观察完整流程。
        - 重置模式：回到初始状态，重新选择子串。

  * **旁白提示**：
    - “看！字符a在左子串的第1、2位出现，生成01串110...”
    - “哈希计算器将110转换为哈希值，就像把一串数字压缩成一个密码～”
    - “排序后，左右两边的哈希密码完全相同，说明它们可以通过字符替换互相转换！”

<visualization_conclusion>
通过这个像素动画，我们能清晰看到每个字符的出现模式如何被哈希捕捉，以及排序如何消除字符顺序的影响，从而判断同构性。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的哈希技巧后，我们可以将其应用到更多字符串特征提取的问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 字符出现模式提取：可用于判断字符串的“形态”是否相同（如回文串、周期串）。
    - 多哈希防冲突：适用于需要高可靠性的哈希场景（如竞赛判题、数据校验）。
    - 排序消除顺序：在需要忽略元素顺序的问题中（如字母异位词判断）非常有用。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1381** - `单词背诵`
          * 🗣️ **推荐理由**：需要提取单词的特征（如哈希值），与本题的特征提取思路类似，适合巩固哈希技巧。
    2.  **洛谷 P3370** - `【模板】字符串哈希`
          * 🗣️ **推荐理由**：直接练习哈希的实现与应用，掌握哈希的核心原理。
    3.  **洛谷 P5357** - `【模板】AC自动机（二次加强版）`
          * 🗣️ **推荐理由**：结合哈希与自动机，处理多模式串匹配问题，拓展哈希的应用场景。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了哈希冲突的教训，这些经验对我们很有帮助：
</insights_intro>

> **参考经验 (来自作者peterwuyihong)**：“自然溢出挂了，差评，这就是CF吗”
>
> **点评**：自然溢出（利用无符号整数溢出）虽然简单，但在严格的竞赛中容易因哈希冲突被卡。本题的优质题解多采用双哈希（两个不同的基数和模数），显著降低冲突概率。这提醒我们，在需要高可靠性的场景中，双哈希是更安全的选择。

---

<conclusion>
本次关于“Isomorphic Strings”的分析就到这里。通过理解字符模式的哈希表示、排序比较的逻辑，以及双哈希防冲突的技巧，相信大家已经掌握了这类问题的核心解法。记得多练习洛谷推荐的题目，巩固所学！下次见～ 💪
</conclusion>

---
处理用时：117.18秒