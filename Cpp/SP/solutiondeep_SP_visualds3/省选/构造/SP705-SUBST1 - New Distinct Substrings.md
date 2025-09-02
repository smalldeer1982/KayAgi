# 题目信息

# SUBST1 - New Distinct Substrings

## 题目描述

 Given a string, we need to find the total number of its distinct substrings.

## 样例 #1

### 输入

```
2
CCCCC
ABABA```

### 输出

```
5
9```

# AI分析结果



---
# 💡 Kay的C++算法解析：SUBST1 - New Distinct Substrings 深入学习指南 💡

<introduction>
今天我们来一起分析“SUBST1 - New Distinct Substrings”这道C++编程题。这道题要求计算一个字符串中本质不同的子串个数，是字符串处理的经典问题。本指南将帮助大家梳理题目思路，理解核心算法（后缀数组和后缀自动机），并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理（后缀数组/后缀自动机应用）`

🗣️ **初步分析**：
解决这道题的关键在于理解如何高效统计本质不同的子串。子串的本质是某个后缀的前缀，因此可以通过两种主流方法解决：  
- **后缀数组（SA）**：利用后缀排序后的`height`数组，计算所有后缀的前缀中重复部分的总和，用总子串数减去重复数。  
- **后缀自动机（SAM）**：利用SAM中`parent树`的性质，每个节点代表一组结束位置相同的子串，通过节点长度差统计不同子串数。  

**核心思路对比**：后缀数组通过排序和公共前缀去重，适合理解后缀结构；SAM通过自动机的状态压缩直接统计，时间复杂度更优（线性）。  
**核心算法流程**：  
- 后缀数组：构建`sa`（后缀排序数组）→ 计算`height`（相邻后缀最长公共前缀）→ 总子串数（n(n+1)/2）减去`height`数组和。  
- SAM：构建自动机时动态维护每个状态的长度差（`len[i] - len[fa[i]]`），累加得到答案。  

**可视化设计**：计划采用8位像素风动画，演示后缀数组的排序过程（如“像素方块”按字典序排列）或SAM的节点扩展（如“自动机精灵”插入字符时生成新节点）。关键步骤高亮（如`height`计算时的公共前缀长度，SAM中`fa`指针的跳转），并配合“叮”声提示关键操作。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选出以下优质题解（≥4星）：
</eval_intro>

**题解一：Mars_Dingdang（后缀数组实现）**  
* **点评**：此题解思路清晰，详细推导了公式（总子串数 - `height`和），代码规范（变量名如`sa`、`height`含义明确）。核心部分完整实现了后缀数组和`height`数组的计算，多测清空处理严谨，适合作为后缀数组的入门参考。亮点在于对`height`数组作用的透彻解释（“重复子串的根源”），以及代码中对边界条件的处理（如`k`的递减优化）。

**题解二：Polaris_Australis_（SAM实现）**  
* **点评**：此题解利用SAM的`parent树`性质，直接通过节点长度差统计答案，代码简洁高效（线性时间复杂度）。关键步骤（如`insert`函数中分裂节点的逻辑）注释清晰，多测清空操作（`memset(son[1],0,sizeof(son[1]))`）确保正确性。亮点是对SAM性质的灵活应用（`len[i] - len[fa[i]]`即为当前节点的贡献），适合学习SAM的核心思想。

**题解三：Fading（SAM动态更新答案）**  
* **点评**：此题解在SAM插入字符时动态累加答案（`ANS += len[newp] - len[pa[newp]]`），避免了后续遍历统计，代码更简洁。关键逻辑（如节点分裂和`fa`指针调整）实现精准，多测清空函数（`clear`）确保状态重置。亮点是“边插入边统计”的优化，减少了额外遍历步骤，适合理解SAM的实时计算特性。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题时，常见的核心难点及应对策略如下：
</difficulty_intro>

1.  **关键点1：理解`height`数组在后缀数组中的作用**  
    * **分析**：`height[i]`表示排名第`i`和`i-1`的后缀的最长公共前缀长度。所有重复子串的数量等于`height`数组的总和（因为每对相邻后缀的公共前缀会被重复计算）。例如，字符串“ABABA”的`height`数组和为6，总子串数为5*6/2=15，15-6=9（与样例输出一致）。  
    * 💡 **学习笔记**：`height`数组是后缀数组去重的关键，其和即为所有重复子串的数量。

2.  **关键点2：掌握SAM中`parent树`的性质**  
    * **分析**：SAM的每个状态`i`对应一组结束位置相同的子串，其长度范围是`[len[fa[i]]+1, len[i]]`，因此该状态贡献的不同子串数为`len[i] - len[fa[i]]`。例如，插入字符时，新节点`newp`的贡献即为`len[newp] - len[fa[newp]]`。  
    * 💡 **学习笔记**：SAM的`parent树`结构天然避免了重复子串，每个节点的长度差直接对应新子串数。

3.  **关键点3：多测试用例下的数组清空**  
    * **分析**：题目有多组输入，需确保每次测试前清空`sa`、`height`、`SAM`的节点等数组，否则残留数据会导致错误。例如，后缀数组的`cnt`、`rk`数组，SAM的`son`、`fa`数组都需要重置。  
    * 💡 **学习笔记**：多测问题中，“初始化”是容易忽略的细节，需为每个测试用例独立分配状态。

### ✨ 解题技巧总结
- **问题转化**：将“本质不同子串数”转化为“总子串数 - 重复子串数”（后缀数组）或“SAM节点贡献累加”（SAM）。  
- **数据结构选择**：后缀数组适合理解后缀结构，SAM适合高效计算（线性时间）。  
- **边界处理**：处理`height`数组时，注意`rk[i]==1`的情况（无前驱后缀）；SAM插入时，注意空指针（`p==0`）的处理。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
首先来看一个基于后缀自动机（SAM）的通用核心实现，因其线性时间复杂度和代码简洁性，适合作为典型参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Polaris_Australis_和Fading的SAM题解，优化了多测清空和动态统计逻辑，适合快速理解SAM的核心思想。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    struct SAM {
        struct Node {
            int fa, len;
            int son[26];
        } nodes[100010];
        int tot, last;
        long long ans;

        void init() {
            tot = last = 1;
            ans = 0;
            nodes[1].fa = nodes[1].len = 0;
            memset(nodes[1].son, 0, sizeof(nodes[1].son));
        }

        void insert(int c) {
            int p = last, np = ++tot;
            nodes[np].len = nodes[p].len + 1;
            memset(nodes[np].son, 0, sizeof(nodes[np].son));
            while (p && !nodes[p].son[c]) {
                nodes[p].son[c] = np;
                p = nodes[p].fa;
            }
            if (!p) {
                nodes[np].fa = 1;
            } else {
                int q = nodes[p].son[c];
                if (nodes[q].len == nodes[p].len + 1) {
                    nodes[np].fa = q;
                } else {
                    int nq = ++tot;
                    nodes[nq] = nodes[q];
                    nodes[nq].len = nodes[p].len + 1;
                    nodes[q].fa = nodes[np].fa = nq;
                    while (p && nodes[p].son[c] == q) {
                        nodes[p].son[c] = nq;
                        p = nodes[p].fa;
                    }
                }
            }
            last = np;
            ans += nodes[np].len - nodes[nodes[np].fa].len;
        }
    } sam;

    int main() {
        int T;
        scanf("%d", &T);
        while (T--) {
            sam.init();
            char s[50010];
            scanf("%s", s);
            int len = strlen(s);
            for (int i = 0; i < len; ++i) {
                sam.insert(s[i] - 'a');
            }
            printf("%lld\n", sam.ans);
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码使用SAM结构，`init`函数初始化自动机，`insert`函数插入字符并动态维护节点关系。每次插入时，通过调整`fa`指针和分裂节点（`nq`）确保状态正确，同时累加当前节点的贡献（`len[np] - len[fa[np]]`）。主函数处理多测输入，每次初始化SAM后插入字符并输出结果。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：Mars_Dingdang（后缀数组）**  
* **亮点**：完整实现后缀数组和`height`计算，公式推导清晰（总子串数 - `height`和）。  
* **核心代码片段**：
    ```cpp
    inline void solve() {
        // 多测清空
        memset(sa, 0, sizeof sa);
        memset(cnt, 0, sizeof cnt);
        memset(height, 0, sizeof height);
        memset(rk, 0, sizeof rk);
        scanf("%s", s + 1);
        n = strlen(s + 1), m = 128;
        getSA(); getH();
        ll ans = 0;
        rep(i, 1, n) 
            ans += (ll)(n - sa[i] + 1 - height[i]);
        writeln(ans);
    }
    ```
* **代码解读**：  
  `solve`函数处理单组输入，先清空数组避免残留数据。通过`getSA`构建后缀数组`sa`，`getH`计算`height`数组。最后遍历`sa`和`height`，累加每个后缀的贡献（长度 - 与前一个后缀的公共前缀）。  
* 💡 **学习笔记**：多测清空是保证正确性的关键，`sa`和`height`的计算需严格按照后缀数组的构建步骤。

**题解二：Polaris_Australis_（SAM）**  
* **亮点**：利用SAM的`parent树`性质，直接统计节点贡献，代码简洁高效。  
* **核心代码片段**：
    ```cpp
    void insert(int x) {
        int p = lst, np = lst = ++tot;
        len[np] = len[p] + 1;
        memset(son[np], 0, sizeof(son[np]));
        while (p && !son[p][x]) {
            son[p][x] = np;
            p = fa[p];
        }
        if (!p) fa[np] = 1;
        else {
            int q = son[p][x];
            if (len[q] == len[p] + 1) fa[np] = q;
            else {
                int nq = ++tot;
                memcpy(son[nq], son[q], sizeof(son[nq]));
                fa[nq] = fa[q];
                len[nq] = len[p] + 1;
                fa[q] = fa[np] = nq;
                while (p && son[p][x] == q) {
                    son[p][x] = nq;
                    p = fa[p];
                }
            }
        }
    }
    ```
* **代码解读**：  
  `insert`函数插入字符`x`，创建新节点`np`。通过`while`循环调整`p`的`son`指针，处理节点分裂（`nq`）以保持状态正确性。`fa`指针的调整确保`parent树`结构正确，为后续统计贡献做准备。  
* 💡 **学习笔记**：SAM的节点分裂是核心操作，需确保`nq`继承`q`的转移并调整长度。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解SAM的插入过程，我们设计一个“像素自动机”动画，用8位风格展示节点扩展和`fa`指针调整。
</visualization_intro>

  * **动画演示主题**：`像素自动机：字符插入大冒险`

  * **核心演示内容**：  
    演示SAM插入字符时，新节点`np`的创建、`p`指针的跳转、节点分裂（`nq`的生成），以及`fa`指针的调整过程。同时高亮当前插入的字符和节点贡献的累加值（`len[np]-len[fa[np]]`）。

  * **设计思路简述**：  
    采用FC红白机风格（8色调色板），用不同颜色的像素块表示SAM节点（根节点为蓝色，普通节点为绿色，分裂节点`nq`为黄色）。关键操作（如`p`跳转、`nq`生成）伴随“叮”声，目标达成（插入完成）时播放胜利音效，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        屏幕左侧为“字符输入区”（像素文本显示当前插入字符），右侧为“自动机森林”（节点以像素方块堆叠，`fa`指针用虚线连接）。控制面板包含“单步”、“自动播放”按钮和速度滑块。

    2.  **插入字符`c`**：  
        输入区高亮字符`c`，触发“插入”音效。新节点`np`以绿色像素块形式从底部升起，显示其`len`值（如`len=3`）。

    3.  **`p`指针跳转**：  
        `p`指针（红色箭头）从`last`节点开始，逐个访问`fa`节点。每跳转到一个无`c`转移的节点，该节点的`son[c]`指针指向`np`（绿色虚线连接），伴随“滴答”声。

    4.  **节点分裂（若需要）**：  
        若遇到已有`c`转移的节点`q`，且`len[q]≠len[p]+1`，则生成黄色节点`nq`。`nq`复制`q`的转移（像素块复制动画），调整`len`和`fa`指针（虚线重连），`q`和`np`的`fa`指向`nq`。

    5.  **贡献累加**：  
        每次插入后，屏幕顶部显示当前总答案（如`ans=5`），用数字像素块逐个弹出，伴随“叮咚”声。

    6.  **自动演示模式**：  
        点击“AI自动演示”，算法自动插入所有字符，节点像“贪吃蛇”一样扩展，学习者可观察完整构建过程。

  * **旁白提示**：  
    - “现在插入字符'A'，创建新节点np，它的长度是前一个节点+1哦！”  
    - “p指针在跳转，寻找没有'A'转移的节点，找到了！把它的son[A]指向np～”  
    - “遇到冲突啦！需要分裂节点q，生成nq来继承q的转移～”  

<visualization_conclusion>
通过这个像素动画，我们能直观看到SAM如何通过节点扩展和指针调整，动态统计不同子串数。每个操作的视觉反馈和音效提示，让抽象的自动机结构变得“可触摸”！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心思想（后缀数组去重、SAM统计贡献）可迁移到多种字符串问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 后缀数组的`height`数组可用于求最长重复子串、不同子串数等。  
    - SAM的`parent树`可用于求两个字符串的最长公共子串、多个字符串的公共子串等。  
    - 例如，求两个字符串的最长公共子串时，可将其中一个字符串构建SAM，另一个在SAM上匹配，记录最长匹配长度。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 SP694 - DISTINCT SUBSTRINGS**  
        * 🗣️ **推荐理由**：与本题完全相同，适合通过不同解法（如后缀数组和SAM）对比练习。  
    2.  **洛谷 P1948 - [USACO08JAN]Cow Contest S**  
        * 🗣️ **推荐理由**：考察字符串的最长公共子串，可尝试用SAM解决，巩固自动机的应用。  
    3.  **洛谷 P3804 - 【模板】后缀自动机**  
        * 🗣️ **推荐理由**：SAM的综合应用题，包含不同子串数、最长子串等，适合深入练习SAM的各种操作。  

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试经验，例如：
</insights_intro>

> **参考经验 (来自Fading)**：“一开始没注意多测清空，导致后几组数据结果错误。后来在`clear`函数中重置了所有节点的`fa`、`len`和`son`数组，问题解决。”  
> **点评**：多测问题中，“初始化”是常见的坑点。Fading的经验提醒我们，每次测试前必须清空所有全局数组或类成员变量，避免残留数据干扰。建议在代码中显式调用`init`函数，确保状态隔离。

---

<conclusion>
本次关于“SUBST1 - New Distinct Substrings”的C++解题分析就到这里。无论是后缀数组的巧妙去重，还是SAM的高效统计，都体现了字符串处理的智慧。希望大家通过练习和动画演示，真正掌握这些算法的核心思想。编程的道路上，每一次思考都是成长的阶梯，加油！💪
</conclusion>

---
处理用时：280.73秒