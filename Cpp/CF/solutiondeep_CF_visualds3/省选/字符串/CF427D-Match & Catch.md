# 题目信息

# Match & Catch

## 题目描述

Police headquarter is monitoring signal on different frequency levels. They have got two suspiciously encoded strings $ s_{1} $ and $ s_{2} $ from two different frequencies as signals. They are suspecting that these two strings are from two different criminals and they are planning to do some evil task.

Now they are trying to find a common substring of minimum length between these two strings. The substring must occur only once in the first string, and also it must occur only once in the second string.

Given two strings $ s_{1} $ and $ s_{2} $ consist of lowercase Latin letters, find the smallest (by length) common substring $ p $ of both $ s_{1} $ and $ s_{2} $ , where $ p $ is a unique substring in $ s_{1} $ and also in $ s_{2} $ . See notes for formal definition of substring and uniqueness.

## 说明/提示

Imagine we have string $ a=a_{1}a_{2}a_{3}...a_{|a|} $ , where $ |a| $ is the length of string $ a $ , and $ a_{i} $ is the $ i^{th} $ letter of the string.

We will call string $ a_{l}a_{l+1}a_{l+2}...a_{r} $ $ (1<=l<=r<=|a|) $ the substring $ [l,r] $ of the string $ a $ .

The substring $ [l,r] $ is unique in $ a $ if and only if there is no pair $ l_{1},r_{1} $ such that $ l_{1}≠l $ and the substring $ [l_{1},r_{1}] $ is equal to the substring $ [l,r] $ in $ a $ .

## 样例 #1

### 输入

```
apple
pepperoni
```

### 输出

```
2
```

## 样例 #2

### 输入

```
lover
driver
```

### 输出

```
1
```

## 样例 #3

### 输入

```
bidhan
roy
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
testsetses
teeptes
```

### 输出

```
3
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Match & Catch 深入学习指南 💡

<introduction>
今天我们来一起分析“Match & Catch”这道C++编程题。题目要求找到两个字符串的最短公共子串，且该子串在各自字符串中仅出现一次。本指南将帮助大家梳理核心思路，理解关键算法，并掌握解题技巧。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理与后缀结构应用`（涉及后缀自动机SAM、后缀数组SA、哈希法等）

🗣️ **初步分析**：
解决这道题的关键在于高效判断子串的“唯一性”和“公共性”。想象我们需要在两个字符串的“子串海洋”中，找到同时满足“仅出现一次”且“在两个串中都存在”的最短子串。这就像在两个不同的图书馆里找一本“每馆仅存一本”的最薄书。

### 核心思路对比：
- **SAM（后缀自动机）**：通过构建两个字符串的SAM，利用SAM节点的“出现次数”属性（每个节点对应一组子串），快速判断子串在各自字符串中的唯一性，再找公共子串的最短长度。
- **SA（后缀数组）**：将两个字符串拼接后求后缀数组和height数组，通过分析height数组的“峰值”（即相邻height值更小的位置），确定可能的唯一公共子串。
- **哈希法**：枚举子串长度，用哈希表统计每个长度的子串在两个字符串中的出现次数，找到首次满足“各出现一次”的长度。

### 核心算法流程与可视化设计：
以SAM为例，其核心是构建两个SAM后，遍历所有节点，找到在两个SAM中出现次数均为1的节点，并取其代表的最短子串（即`len[fa]+1`）。可视化可设计为“像素图书馆”：每个SAM节点是一个书架（不同颜色区分s1和s2），书的厚度代表子串长度，当某个书架在两个图书馆中都只有一本书时，该书的厚度就是候选答案。动画中高亮这些书架，并通过步进控制展示节点的出现次数统计过程。

---

## 2. 精选优质题解参考

<eval_intro>
经过评估，以下题解在思路清晰性、代码规范性、算法有效性等方面表现突出（评分≥4星）：
</eval_intro>

### **题解一：SAM解法（作者：oisdoaiu）**
* **点评**：此题解巧妙利用SAM的parent树特性，通过判断叶子节点（仅出现一次的子串）来快速筛选候选子串。代码结构规范，变量命名清晰（如`mk`标记非叶子节点），核心逻辑简洁高效。其通过两次SAM构建（分别处理s1和s2）并结合匹配过程的思路，是解决此类唯一性子串问题的经典方法。

### **题解二：哈希法（作者：zombie462）**
* **点评**：思路直白易懂，枚举子串长度并使用哈希表统计出现次数。代码中手写哈希表优化了效率，`insert`和`check`函数逻辑清晰，边界处理严谨（如`init`函数清空哈希表）。适合理解基础子串统计方法的学习者参考。

### **题解三：SA解法（作者：huayucaiji）**
* **点评**：利用后缀数组的height数组特性，通过分析“峰值”位置（height[i] > height[i-1]且height[i] > height[i+1]）快速定位唯一公共子串。代码中`DA`（构建后缀数组）和`get_height`函数实现标准，`solve`函数逻辑巧妙，是SA应用的典型案例。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的关键在于处理“唯一性”和“公共性”的结合。以下是三个核心难点及应对策略：
</difficulty_intro>

1.  **难点1：如何高效判断子串在单字符串中的唯一性？**
    * **分析**：子串的唯一性意味着该子串在字符串中仅出现一次。SAM的每个节点可表示一组子串，其出现次数可通过parent树传递统计（子节点的出现次数累加到父节点）。若节点的出现次数为1，则其代表的所有子串（长度在`[len[fa]+1, len[cur]]`之间）均唯一。
    * 💡 **学习笔记**：SAM的“出现次数统计”是解决唯一性问题的利器，通过parent树的后序遍历可高效计算。

2.  **难点2：如何找到两个字符串的公共子串？**
    * **分析**：公共子串需同时存在于两个字符串中。SAM方法中，可通过在s1的SAM上匹配s2的子串，记录匹配节点；SA方法中，拼接字符串后，公共子串对应后缀数组中相邻且来自不同原串的后缀。
    * 💡 **学习笔记**：公共子串的本质是“两个字符串的子串集合的交集”，SAM的匹配过程或SA的height数组分析可高效找到交集。

3.  **难点3：如何确保找到最短的满足条件的子串？**
    * **分析**：最短子串对应SAM中满足条件的节点的最小`len[fa]+1`（节点代表的最短子串长度），或SA中峰值位置的`max(height[i-1], height[i+1])+1`（比左右更长的最短长度）。
    * 💡 **学习笔记**：最短性可通过遍历所有候选节点/位置并取最小值实现。

### ✨ 解题技巧总结
- **问题分解**：先解决单字符串的唯一性子串统计，再处理两个字符串的公共性。
- **数据结构选择**：SAM适合处理子串的出现次数统计，SA适合分析子串的公共前缀长度，哈希法适合基础枚举。
- **边界处理**：注意空字符串、全相同字符等特殊情况，确保代码鲁棒性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合SAM思路的通用核心实现，结合了高效性与可读性：
</code_intro_overall>

### **本题通用核心C++实现参考**
* **说明**：本代码综合了oisdoaiu和zhengrunzhe的SAM思路，通过构建两个SAM并统计出现次数，最终遍历所有节点找到最短满足条件的子串。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int MAXN = 10010; // 两倍于最大字符串长度

    struct SAM {
        struct Node {
            int len, fa;
            int son[26];
            int cnt[2]; // cnt[0]表示在s1中的出现次数，cnt[1]表示在s2中的出现次数
        } t[MAXN << 1];
        int node_cnt, last;

        SAM() : node_cnt(1), last(1) {
            t[1].len = 0;
            t[1].fa = 0;
            memset(t[1].son, 0, sizeof(t[1].son));
            memset(t[1].cnt, 0, sizeof(t[1].cnt));
        }

        int extend(int c, int op) {
            int p = last, np = ++node_cnt;
            t[np].len = t[p].len + 1;
            t[np].cnt[op] = 1;
            memset(t[np].son, 0, sizeof(t[np].son));
            while (p && !t[p].son[c]) {
                t[p].son[c] = np;
                p = t[p].fa;
            }
            if (!p) {
                t[np].fa = 1;
            } else {
                int q = t[p].son[c];
                if (t[p].len + 1 == t[q].len) {
                    t[np].fa = q;
                } else {
                    int nq = ++node_cnt;
                    t[nq] = t[q];
                    t[nq].len = t[p].len + 1;
                    t[nq].cnt[0] = t[nq].cnt[1] = 0; // 复制时清空次数，后续重新统计
                    while (p && t[p].son[c] == q) {
                        t[p].son[c] = nq;
                        p = t[p].fa;
                    }
                    t[q].fa = t[np].fa = nq;
                }
            }
            last = np;
            return last;
        }

        void build() {
            vector<int> ord(node_cnt + 1);
            iota(ord.begin() + 1, ord.end(), 1);
            sort(ord.begin() + 1, ord.end(), [&](int a, int b) {
                return t[a].len > t[b].len;
            });
            for (int u : ord) {
                if (t[u].fa) {
                    t[t[u].fa].cnt[0] += t[u].cnt[0];
                    t[t[u].fa].cnt[1] += t[u].cnt[1];
                }
            }
        }
    };

    int main() {
        string s1, s2;
        cin >> s1 >> s2;

        SAM sam;
        // 插入s1，标记op=0
        sam.last = 1;
        for (char c : s1) sam.extend(c - 'a', 0);
        // 插入s2，标记op=1（注意重置last）
        sam.last = 1;
        for (char c : s2) sam.extend(c - 'a', 1);
        sam.build();

        int ans = INT_MAX;
        for (int i = 2; i <= sam.node_cnt; ++i) {
            if (sam.t[i].cnt[0] == 1 && sam.t[i].cnt[1] == 1) {
                ans = min(ans, sam.t[sam.t[i].fa].len + 1);
            }
        }

        cout << (ans == INT_MAX ? -1 : ans) << endl;
        return 0;
    }
    ```
* **代码解读概要**：代码首先构建两个字符串的SAM，插入时分别标记属于s1或s2（`op`参数）。通过`build`函数后序遍历parent树，累加子节点的出现次数到父节点。最后遍历所有节点，找到在两个字符串中出现次数均为1的节点，取其代表的最短子串长度（`fa.len + 1`）。

---

<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

### **题解一：SAM解法（作者：oisdoaiu）**
* **亮点**：利用parent树的叶子节点特性快速筛选唯一子串，代码简洁高效。
* **核心代码片段**：
    ```cpp
    struct SAM{
        struct node{ int son[26], fa, len; }t[MAXN<<1];
        int node_cnt=1, prv=1;
        char mk[MAXN<<1]; // 标记非叶子节点（即出现次数>1）
        inline void Unique(){ for(int i=1; i<=node_cnt; i++) mk[fa(i)] = true; }
    };

    // 主函数中：
    S.Unique(); T.Unique(); // 标记非叶子节点（出现次数>1的节点）
    for(int i=1, cur=1, len=0; i<=n; i++){
        // 匹配s2的字符到s1的SAM中
        if(S.mk[cur] || T.mk[pos[i]]) continue; // 非叶子节点跳过
        ans = min(ans, max(S.len(S.fa(cur))+1, T.len(T.fa(pos[i]))+1));
    }
    ```
* **代码解读**：`Unique`函数通过父节点标记非叶子节点（即出现次数>1的节点）。主循环中，匹配s2的字符到s1的SAM，若当前节点是叶子节点（未被标记），则计算其代表的最短子串长度。
* 💡 **学习笔记**：通过标记父节点快速排除出现次数>1的节点，是SAM处理唯一性问题的高效技巧。

### **题解二：哈希法（作者：zombie462）**
* **亮点**：枚举长度+哈希表统计，思路直接，适合理解基础子串统计。
* **核心代码片段**：
    ```cpp
    bool check(){
        for(int i=1; i<=etot; ++i){
            if(tot[i][0]==1 && tot[i][1]==1) return true; // 各出现一次
        }
        return false;
    }

    // 主函数中：
    for(int i=1; i<=min(n,m); ++i){
        hashTable.init();
        for(int j=i; j<=n; ++j) hashTable.insert(getHashA(j-i+1,j), 0); // s1的子串
        for(int j=i; j<=m; ++j) hashTable.insert(getHashB(j-i+1,j), 1); // s2的子串
        if(hashTable.check()) { printf("%d\n",i); break; }
    }
    ```
* **代码解读**：枚举子串长度`i`，将s1和s2中所有长度为`i`的子串插入哈希表，统计出现次数。`check`函数判断是否存在哈希值在两个字符串中各出现一次。
* 💡 **学习笔记**：哈希法适合小长度枚举，需注意哈希冲突（可通过双哈希优化）。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解SAM如何统计子串唯一性，我们设计一个“像素图书馆”动画，模拟SAM构建和唯一性判断过程：
</visualization_intro>

  * **动画演示主题**：`像素图书馆的唯一藏书`（8位复古风格）

  * **核心演示内容**：展示s1和s2的SAM构建过程，每个节点是一个书架（s1书架为蓝色，s2为红色），书架上的书代表该节点对应的子串集合。当某个书架在两个图书馆中都只有一本书时，该书的厚度（子串长度）即为候选答案。

  * **设计思路简述**：8位像素风格降低学习门槛，书架颜色区分两个字符串，书的厚度动态变化体现子串长度。关键操作（如节点插入、父节点标记）通过音效和高亮强化记忆。

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：两个像素图书馆（左为s1，右为s2），每个图书馆有一个初始书架（根节点）。
    2. **插入字符**：逐个插入s1的字符，每个字符生成新书架（节点），通过箭头连接父节点（parent树）。插入时播放“叮”音效，新书架高亮。
    3. **统计出现次数**：后序遍历parent树，子书架的书数累加到父书架（用像素数字显示次数）。次数>1的书架标记为灰色（非叶子节点）。
    4. **匹配公共子串**：在s1的图书馆中，用绿色指针遍历s2的字符，找到匹配的书架。若该书架在两个图书馆中均为非灰色（次数=1），则书的厚度（`fa.len+1`）闪烁，记录最小值。
    5. **结果展示**：最终找到的最小厚度书弹出“胜利”音效，背景播放8位风格胜利音乐。

  * **旁白提示**：
    - “看！插入字符时，新书架会连接到父书架，形成树结构~”
    - “后序遍历统计次数，子书架的书会被加到父书架哦！”
    - “绿色指针在s1的图书馆里找s2的子串，找到两个图书馆都只有一本书的书架啦！”

<visualization_conclusion>
通过这个动画，我们能直观看到SAM如何高效统计子串唯一性，并快速找到最短公共唯一子串。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是“子串唯一性+公共性”的结合，其思路可迁移到以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 子串唯一性统计：可用于“找字符串中仅出现一次的最长子串”。
    - 多字符串公共子串：如三个字符串的公共唯一子串。
    - 动态子串查询：在线查询两个字符串的公共唯一子串。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1117** - `ZAP 反素数`：练习因数分解与唯一性统计，类似SAM的次数统计。
    2.  **洛谷 P3804** - `【模板】后缀自动机`：强化SAM的构建与应用，掌握出现次数统计。
    3.  **洛谷 P4081** - `[USACO17DEC]Standing Out from the Herd`：多字符串唯一子串统计，与本题思路类似。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者提到调试时遇到的困难，例如：
</insights_intro>

> （来自作者：zhengrunzhe）“一开始忘记清空SAM的`last`指针，导致插入s2时错误地继续使用s1的SAM状态，调试了很久才发现。”

**点评**：这位作者的经验提醒我们，在处理多字符串的SAM时，务必重置`last`指针（回到根节点）。这是多字符串插入SAM的常见易错点，通过打印关键变量（如`last`的初始值）可快速定位问题。

---

<conclusion>
本次关于“Match & Catch”的分析就到这里。希望大家通过SAM、SA和哈希法的学习，掌握子串唯一性与公共性的处理技巧。记住，多动手写代码、调试，是提升算法能力的关键！下次见~ 💪
</conclusion>

---
处理用时：129.23秒