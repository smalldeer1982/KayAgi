# 题目信息

# [USACO12DEC] First! G

## 题目描述

Bessie has been playing with strings again. She found that by changing the order of the alphabet she could make some strings come before all the others lexicographically (dictionary ordering).

For instance Bessie found that for the strings "omm", "moo", "mom", and "ommnom" she could make "mom" appear first using the standard alphabet and that she could make "omm" appear first using the alphabet

"abcdefghijklonmpqrstuvwxyz".  However, Bessie couldn't figure out any way to make "moo" or "ommnom" appear first.

Help Bessie by computing which strings in the input could be lexicographically first by rearranging the order of the alphabet.  To compute if string X is lexicographically before string Y find the index of the first character in which they differ, j.  If no such index exists then X is lexicographically before Y if X is shorter than Y.  Otherwise X is lexicographically before Y if X[j] occurs earlier in the alphabet than Y[j].

Bessie 一直在研究字符串。她发现，通过改变字母表的顺序，她可以按改变后的字母表来排列字符串（字典序大小排列）。

例如，Bessie 发现，对于字符串 $\texttt{omm},\texttt{moo},\texttt{mom}$ 和 $\texttt{ommnom}$，她可以使用标准字母表使 $\texttt{mom}$ 排在第一个（即字典序最小），她也可以使用字母表 $\texttt{abcdefghijklonmpqrstuvwxyz}$ 使得 $\texttt{omm}$ 排在第一个。然而，Bessie 想不出任何方法（改变字母表顺序）使得 $\texttt{moo}$ 或 $\texttt{ommnom}$ 排在第一个。

接下来让我们通过重新排列字母表的顺序来计算输入中有哪些字符串可以排在第一个（即字典序最小），从而帮助 Bessie。

要计算字符串 $X$ 和字符串 $Y$ 按照重新排列过的字母表顺序来排列的顺序，先找到它们第一个不同的字母 $X_i$ 与 $Y_i$，按重排后的字母表顺序比较，若 $X_i$ 比 $Y_i$ 先，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前；若没有不同的字母，则比较 $X$ 与 $Y$ 长度，若 $X$ 比 $Y$ 短，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前。

## 说明/提示

The example from the problem statement.

Only "omm" and "mom" can be ordered first.

样例即题目描述中给出的例子，只有 $\texttt{omm}$ 和 $\texttt{mom}$ 在各自特定的字典序下可以被排列在第一个。

## 样例 #1

### 输入

```
4
omm
moo
mom
ommnom
```

### 输出

```
2
omm
mom
```

# AI分析结果



---
# 💡 Kay的C++算法解析：[USACO12DEC] First! G 深入学习指南 💡

<introduction>
今天我们来一起分析“[USACO12DEC] First! G”这道C++编程题。这道题的核心是判断哪些字符串可以通过重新排列字母表顺序成为字典序最小的字符串。本指南将帮助大家梳理思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`Trie树应用 + 拓扑排序` (编程技巧应用：数据结构与图论结合)

🗣️ **初步分析**：
> 要判断一个字符串能否通过调整字母表顺序成为字典序最小的，关键在于两点：一是它不能是其他字符串的前缀（否则必然更小），二是它与其他字符串的第一个不同字符必须能通过字母优先级调整满足“更小”。  
> 这里我们用 **Trie树（字典树）** 高效处理字符串的前缀关系——每个节点记录是否为某个字符串的结尾（即是否存在更短的字符串作为前缀）。然后，对每个字符串，我们在Trie树的每一层建立字母间的优先级边（当前字符必须比同层其他字符优先级高），最后用 **拓扑排序** 判断这些边是否构成无环图（无环则存在合法字母顺序）。  
> 核心算法流程：插入所有字符串到Trie树→对每个字符串检查前缀冲突→建立字母优先级边→拓扑排序检测环→统计合法字符串。  
> 可视化设计：用8位像素风展示Trie树的构建（节点用方块表示，红色标记前缀冲突），字母边用箭头动画添加，拓扑排序时队列处理节点（高亮当前节点，入度数字动态变化），成功时播放“叮”的音效，失败时用短促提示音。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等方面筛选了3份优质题解（均≥4星），它们在Trie树构建、拓扑排序实现上各有亮点：
</eval_intro>

**题解一：作者 Heartlessly**  
* **点评**：这份题解思路非常清晰，代码结构工整。通过Trie树插入所有字符串，再对每个字符串逐字符检查前缀冲突，并在Trie的每一层建立字母间的有向边（当前字符指向同层其他字符）。拓扑排序时用队列处理入度，最终判断是否存在环。代码中变量命名规范（如`ch`表示Trie子节点，`in`表示入度数组），边界条件处理严谨（如`ed[u]`标记前缀冲突）。其核心逻辑“边的建立+拓扑检测”直接对应问题本质，是竞赛中典型的高效实现。

**题解二：作者 littleming**  
* **点评**：此题解代码简洁高效，通过`ch`数组构建Trie树，用邻接表存储字母边，拓扑排序时用双端队列优化。亮点在于用`used`数组避免重复建边，减少了冗余操作。虽然代码量较少，但关键步骤（如前缀检查、边建立、拓扑排序）都完整保留，非常适合快速理解核心逻辑。

**题解三：作者 liuxu**  
* **点评**：此题解结合图示解释，帮助理解Trie树和拓扑排序的关系。代码中用`Node`结构体封装Trie节点，`E`数组存储字母边，拓扑排序时用队列处理。其`work`函数将前缀检查和边建立合并，逻辑紧凑。作者提到的“动手画图理解环”的学习经验，对新手很有启发。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的关键在于处理前缀冲突和建立合法的字母优先级。结合优质题解，我们提炼出以下核心难点及策略：
</difficulty_intro>

1.  **关键点1：如何快速判断字符串是否是其他字符串的前缀？**  
    * **分析**：利用Trie树的特性，插入字符串时标记每个节点是否为某个字符串的结尾（`ed[u]`）。当检查字符串`s`时，若在遍历过程中遇到`ed[u]==true`，说明存在更短的字符串是`s`的前缀，此时`s`无法成为最小。  
    * 💡 **学习笔记**：Trie树的“路径唯一性”是处理前缀问题的天然工具。

2.  **关键点2：如何建立字母间的优先级边？**  
    * **分析**：对于字符串`s`的第`i`个字符`c`，在Trie的第`i`层（当前节点`u`），所有同层存在的其他字符`d`（即`ch[u][d]`存在）必须满足`c`的优先级高于`d`。因此，建立有向边`c→d`，表示`c < d`。  
    * 💡 **学习笔记**：边的建立需覆盖同层所有其他字符，避免遗漏导致错误。

3.  **关键点3：如何检测字母优先级是否存在环？**  
    * **分析**：用拓扑排序检测环。若所有字母的入度最终都能被消为0，说明无环（存在合法顺序）；否则存在环（无法调整顺序）。  
    * 💡 **学习笔记**：拓扑排序是判断有向无环图（DAG）的标准方法，入度数组和队列是核心工具。

### ✨ 解题技巧总结
- **Trie树预处理**：先插入所有字符串，标记前缀冲突，避免重复检查。  
- **边的去重**：用`used`数组（如`used[c][d]`）避免重复建立相同的边，减少计算量。  
- **拓扑排序优化**：用队列处理入度为0的节点，动态更新入度，时间复杂度仅为O(26)。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合Heartlessly的题解（逻辑清晰、实现完整），给出一个通用的核心C++实现参考：
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码综合了优质题解的思路，完整实现了Trie树构建、前缀检查、边建立和拓扑排序检测，是本题的典型高效实现。  
* **完整核心代码**：  
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int MAXM = 3e5 + 5; // 总字符数上限
    struct Trie {
        int tot, ch[MAXM][26];
        bool ed[MAXM]; // 标记是否为字符串结尾（前缀）
        int in[26], e[26][26]; // 入度数组、边矩阵

        Trie() : tot(1) {} // 根节点为1

        void insert(const string& s) {
            int u = 1;
            for (char c : s) {
                int v = c - 'a';
                if (!ch[u][v]) ch[u][v] = ++tot;
                u = ch[u][v];
            }
            ed[u] = true;
        }

        bool check(const string& s) {
            memset(e, 0, sizeof(e));
            memset(in, 0, sizeof(in));
            int u = 1;
            for (char c : s) {
                if (ed[u]) return false; // 存在前缀冲突
                int v = c - 'a';
                for (int j = 0; j < 26; ++j) {
                    if (j != v && ch[u][j] && !e[v][j]) {
                        e[v][j] = 1; // 建立边v->j
                        in[j]++; // 入度+1
                    }
                }
                u = ch[u][v];
            }
            // 拓扑排序检测环
            queue<int> q;
            for (int i = 0; i < 26; ++i)
                if (!in[i]) q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v = 0; v < 26; ++v) {
                    if (e[u][v]) {
                        if (--in[v] == 0) q.push(v);
                    }
                }
            }
            for (int i = 0; i < 26; ++i)
                if (in[i]) return false;
            return true;
        }
    } tr;

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int n;
        cin >> n;
        vector<string> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
            tr.insert(s[i]);
        }
        vector<string> ans;
        for (const string& str : s) {
            if (tr.check(str)) ans.push_back(str);
        }
        cout << ans.size() << '\n';
        for (const string& str : ans) cout << str << '\n';
        return 0;
    }
    ```
* **代码解读概要**：  
    代码首先通过`insert`函数将所有字符串插入Trie树，标记前缀节点（`ed[u]`）。`check`函数对每个字符串进行检查：遍历其字符，若遇到前缀节点则返回`false`；否则在每一层建立字母边（当前字符指向同层其他字符），最后用拓扑排序判断是否存在环。主函数统计并输出所有合法字符串。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者 Heartlessly**  
* **亮点**：Trie树结构清晰，边建立和拓扑排序逻辑分离，代码易读。  
* **核心代码片段**：  
    ```cpp
    inline bool find(string x) {
        int u = 1, len = x.size();
        memset(e, 0, sizeof (e));
        memset(in, 0, sizeof (in));
        for (int i = 0; i < len; ++i) {
            if (ed[u]) return 0; // 前缀冲突检测
            int v = x[i] - 'a';
            for (int j = 0; j < 26; ++j)
                if (v != j && ch[u][j] && !e[v][j]) {
                    e[v][j] = 1; // 建立边v->j
                    ++in[j]; // 入度统计
                }
            u = ch[u][v];
        }
        topoSort(); // 拓扑排序
        for (int i = 0; i < 26; ++i)
            if (in[i]) return 0; // 存在环
        return 1;
    }
    ```
* **代码解读**：  
    `find`函数是核心逻辑：首先重置边和入度数组，然后遍历字符串的每个字符。若当前节点是其他字符串的结尾（`ed[u]`），说明存在前缀冲突，直接返回`false`。否则，在Trie的当前层，为当前字符`v`建立指向同层其他字符`j`的边，并统计入度。最后调用`topoSort`检测环，若所有入度都能消为0则合法。  
* 💡 **学习笔记**：前缀检测和边建立的顺序很关键，必须先检查前缀，再处理当前层的边。

**题解二：作者 littleming**  
* **亮点**：用邻接表存储边，节省空间，拓扑排序用双端队列优化。  
* **核心代码片段**：  
    ```cpp
    inline void solve(string x) {
        int u = 0, t;
        for (int i = 0; i < x.size(); ++i) {
            t = x[i] - 'a';
            if (vis[u]) { // vis[u]标记是否为前缀
                f = 1;
                return;
            }
            for (int j = 0; j < 26; ++j) {
                if (ch[u][j] && j != t && !used[t][j]) {
                    used[t][j] = 1;
                    addedge(t, j); // 邻接表建边
                    ind[j]++; // 入度+1
                }
            }
            u = ch[u][t];
        }
    }
    ```
* **代码解读**：  
    `solve`函数中，`vis[u]`标记当前节点是否为其他字符串的结尾（即前缀冲突）。通过`used`数组避免重复建边，`addedge`用邻接表存储边（`head`、`to`、`nxt`数组）。这种方式比矩阵存储更节省空间，适合大规模数据。  
* 💡 **学习笔记**：邻接表适合稀疏图（本题边数最多26*26=676条），空间复杂度更低。

**题解三：作者 liuxu**  
* **亮点**：结合图示解释，`E`数组存储边，拓扑排序用队列处理。  
* **核心代码片段**：  
    ```cpp
    int work(string s) {
        int now = 1;
        for (int i = 0; i < s.length(); ++i) {
            int t = s[i] - 'a';
            if (N[now].end) return 0; // 前缀冲突
            for (int j = 0; j < 26; ++j) {
                if (N[now].son[j] && t != j) {
                    E[t].push_back(j); // 向量存储边
                    ind[j]++; // 入度+1
                }
            }
            now = N[now].son[t];
        }
        return 1;
    }
    ```
* **代码解读**：  
    `work`函数中，`N[now].end`标记前缀冲突。通过`E[t].push_back(j)`向量化存储边，代码更简洁。返回1表示无冲突，可继续拓扑排序检测。  
* 💡 **学习笔记**：向量（`vector`）是C++中灵活的动态数组，适合边数不确定的场景。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解Trie树构建和拓扑排序过程，我们设计一个“像素字母探险”动画，以8位复古风格展示算法步骤！
</visualization_intro>

  * **动画演示主题**：`像素字母探险——寻找最小字典序的秘密`  
  * **核心演示内容**：展示字符串插入Trie树（节点生成）、前缀冲突检测（红色标记）、字母边建立（箭头动画）、拓扑排序（队列处理节点）的全过程。  

  * **设计思路简述**：  
    8位像素风（FC红白机风格）营造轻松氛围，用不同颜色区分节点状态（绿色：正常节点；红色：前缀节点）。字母边用黄色箭头表示，入度用数字显示。拓扑排序时，队列中的节点用蓝色闪烁，处理完成的节点变灰色，成功时播放“叮~”音效，失败时用“咚”提示。

  * **动画帧步骤与交互关键点**：  

    1. **场景初始化**：  
       - 屏幕左侧是Trie树区域（网格状，每个节点是16x16像素方块），右侧是字母边和拓扑排序控制面板（按钮：开始/暂停/单步，速度滑块）。  
       - 背景播放8位风格BGM（类似《超级玛丽》的轻快旋律）。

    2. **插入字符串到Trie树**：  
       - 输入字符串时，字符逐个从顶部下落，生成Trie节点（绿色方块）。若节点是某个字符串的结尾（前缀），变为红色方块（如插入"mom"后，路径上的节点依次变绿，最后一个节点变红色）。

    3. **检查字符串合法性（以"omm"为例）**：  
       - 单步执行时，字符"o"→"m"→"m"依次移动到Trie树路径上。遇到红色节点（前缀）时，播放“咚”音效，标记该字符串不合法。  
       - 无冲突时，在每一层节点（如第一个"o"所在层），生成黄色箭头（o→a, o→b, ..., o→n, o→p...，除"m"外的所有同层字符），同时对应字符的入度数字+1（如a的入度从0→1）。

    4. **拓扑排序检测环**：  
       - 队列初始化为入度0的字母（如假设初始时o的入度为0），节点o变蓝色闪烁，入队。  
       - 处理o时，所有o指向的字母（a、b等）入度-1（如a的入度从1→0），a变蓝色入队。  
       - 若所有字母入度最终为0（无环），播放“叮~”音效，字符串"omm"变金色；若有字母入度不为0（如m→n→m形成环），播放“咚”音效，字符串变灰色。

    5. **交互控制**：  
       - 单步执行：点击“单步”按钮，逐步展示插入、边建立、拓扑排序的每一步。  
       - 自动播放：滑动速度滑块（慢/中/快），算法自动运行，适合观察整体流程。  
       - 重置：点击“重置”按钮，清空Trie树和边，重新开始。

  * **旁白提示**：  
    - （插入字符串时）“看！字符一个一个掉进Trie树，生成新的节点~”  
    - （检测前缀时）“红色节点表示这里有一个更短的字符串，当前字符串不能成为最小哦~”  
    - （建立边时）“黄色箭头表示当前字符必须比其他字符优先级高，比如o→a表示o < a~”  
    - （拓扑排序时）“队列里的字母入度为0，开始处理它们~ 处理完所有字母就成功啦！”

<visualization_conclusion>
通过这样的像素动画，我们能直观看到Trie树的结构、边的建立逻辑，以及拓扑排序如何检测环。边看边学，算法不再抽象！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，我们可以用Trie树和拓扑排序解决更多类似问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    Trie树+拓扑排序的组合适用于处理“字典序优先级调整”问题，例如：  
    - 多字符串的最小表示法判断；  
    - 自定义字母顺序下的字符串排序问题；  
    - 带约束的字母优先级分配（如某些字母必须在其他字母前）。

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P2580 [ZJOI2006] 树的统计**  
        * 🗣️ **推荐理由**：此题涉及树结构的统计，能帮助巩固Trie树的变形应用（如权值树）。  
    2.  **洛谷 P4587 [FJOI2016] 神秘数**  
        * 🗣️ **推荐理由**：此题需用拓扑排序处理约束关系，与本题的字母优先级约束思路类似。  
    3.  **洛谷 P1168 中位数**  
        * 🗣️ **推荐理由**：此题涉及数据结构的灵活运用（如平衡树），能提升对数据结构的理解。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解中作者们分享了调试经验，这些对我们很有参考价值：
</insights_intro>

> **参考经验 (来自作者 liuxu)**：“一开始没考虑到前缀冲突，导致代码总是出错。后来通过打印Trie树的`ed`标记，才发现某些节点被错误标记。这让我意识到，处理前缀问题时一定要仔细检查每个节点的`ed`状态。”  
> **点评**：liuxu的经验提醒我们，调试时打印关键变量（如`ed[u]`、`in[i]`）能快速定位问题。遇到逻辑错误时，手动模拟小数据（如样例输入）也是有效的方法。

-----

<conclusion>
本次关于“[USACO12DEC] First! G”的解题分析就到这里。希望大家通过Trie树和拓扑排序的结合，掌握字典序问题的处理方法。记住，多动手画图、调试，算法会越来越清晰！下次见~ 💪
</conclusion>

---
处理用时：202.42秒