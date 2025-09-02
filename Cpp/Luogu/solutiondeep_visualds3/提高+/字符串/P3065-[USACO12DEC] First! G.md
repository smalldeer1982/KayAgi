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
今天我们来一起分析“[USACO12DEC] First! G”这道题。题目要求我们判断哪些字符串可以通过重新排列字母表的顺序，成为字典序最小的那个。本指南将帮助大家理解核心思路，掌握关键算法，并通过可视化演示直观感受解题过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`图论（拓扑排序）与Trie树（字典树）的综合应用`

🗣️ **初步分析**：
解决这道题的关键在于两点：一是用Trie树（字典树）高效处理字符串的前缀关系和同一层字符的比较；二是用拓扑排序判断是否存在合法的字母顺序（无环）。简单来说，Trie树就像一个“字符串图书馆”，每个节点代表一个字符，路径代表字符串的前缀；拓扑排序则像“排课表”，检查字母间的顺序约束是否冲突（比如A必须在B前，B必须在A前，就会形成环，无法排课）。

- **题解思路**：对每个字符串，先检查是否存在其他字符串是它的前缀（若有则无法成为最小）；然后在Trie树中，为该字符串的每一层字符建立约束（当前字符必须比同层其他字符小），构建有向图；最后用拓扑排序判断图中是否有环（无环则存在合法顺序）。
- **核心难点**：如何正确构建字符间的约束边，以及如何通过拓扑排序判断是否存在合法顺序。
- **可视化设计**：我们将用8位像素风格演示Trie树的构建（每个节点是像素块），字符约束边用箭头表示，拓扑排序过程用队列动画（像素方块入队、处理边、更新入度），关键步骤高亮（如当前处理的字符、入度为0的节点），并伴随“叮”的音效提示边添加，“成功”音效提示无环。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下3道题解质量突出（≥4星），值得重点学习：
</eval_intro>

**题解一：作者 Heartlessly**
* **点评**：此题解思路清晰，代码规范。通过Trie树存储所有字符串，对每个字符串检查前缀关系后，逐层建立字符间的约束边（当前字符必须小于同层其他字符），再用拓扑排序判断是否有环。代码中`insert`函数构建Trie，`find`函数处理约束边和拓扑排序，变量名（如`ch`表示Trie节点，`in`表示入度）含义明确。亮点在于将Trie的层遍历与拓扑排序结合，高效解决问题，适合竞赛参考。

**题解二：作者 littleming**
* **点评**：此题解代码简洁，逻辑紧凑。用`ch`数组实现Trie树，`addedge`函数构建约束边，`ok`函数执行拓扑排序。代码中通过`used`数组避免重复建边，减少冗余计算，体现了良好的优化意识。虽然变量命名较简略（如`num`表示Trie节点数），但整体结构工整，适合快速理解核心逻辑。

**题解三：作者 liuxu**
* **点评**：此题解结合图示解释思路（如字符约束的拓扑图），对学习者友好。代码中`Node`结构体定义Trie节点，`work`函数处理约束边，`check`函数执行拓扑排序。亮点在于通过`E`数组存储图结构，清晰展示字符间的依赖关系，适合理解拓扑排序的具体应用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的关键在于处理字符串的前缀关系和字符约束的合法性。以下是核心难点及应对策略：
</difficulty_intro>

1.  **关键点1：判断字符串是否是其他字符串的前缀**
    * **分析**：若字符串S是另一个字符串T的前缀（如S="ab", T="abc"），则T的字典序一定比S大，因此S无法通过调整字母顺序成为最小。在Trie树中，若插入S后，其末尾节点标记为其他字符串的结束（`ed[u]=1`），则S是其他字符串的前缀。
    * 💡 **学习笔记**：Trie树的`ed`标记可快速判断前缀关系，是解决此题的前提。

2.  **关键点2：构建字符间的约束边**
    * **分析**：对于字符串S的第i层字符c，同层的其他字符d必须满足c < d（在字母表中）。因此，需为每个c到d建立有向边c→d（表示c的优先级更高）。建边时需避免重复（如多次遇到相同的c和d），可用`used`数组记录已建边。
    * 💡 **学习笔记**：约束边的正确建立是拓扑排序的基础，需确保覆盖所有同层字符。

3.  **关键点3：通过拓扑排序判断是否存在合法顺序**
    * **分析**：拓扑排序要求图中无环。若存在环（如c→d和d→c），则无法确定c和d的顺序，字符串S无法成为最小。拓扑排序时，统计入度为0的节点，逐步删除节点并更新入度，最终若所有节点入度为0则无环。
    * 💡 **学习笔记**：拓扑排序是判断约束是否冲突的核心工具，需熟练掌握其实现。

### ✨ 解题技巧总结
- **Trie树的灵活应用**：利用Trie树的层级结构，快速定位字符串的前缀和同层字符，减少重复比较。
- **避免重复建边**：用标记数组（如`used`）记录已建立的边，避免图中出现重复边，提升效率。
- **拓扑排序的优化**：使用队列处理入度为0的节点，线性时间内完成环的检测，适合大规模数据。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，结合了Trie树构建、约束边建立和拓扑排序的关键逻辑：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Heartlessly和liuxu的题解思路，提供清晰的Trie树构建、约束边建立及拓扑排序逻辑，适用于竞赛场景。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int MAXM = 3e5 + 5; // 字符串总长度上限
    int n, ans_cnt;
    string s[30005];
    bool is_valid[30005];

    struct Trie {
        int tot; // Trie节点总数
        bool ed[MAXM]; // 标记是否为字符串结尾
        int ch[MAXM][26]; // 子节点数组，ch[u][c]表示节点u的字符c子节点
        int in_degree[26]; // 拓扑排序入度数组
        int graph[26][26]; // 字符间约束边，graph[u][v]=1表示u→v

        Trie() : tot(1) {} // 根节点编号为1

        void insert(const string &str) {
            int u = 1;
            for (char c : str) {
                int idx = c - 'a';
                if (!ch[u][idx]) ch[u][idx] = ++tot;
                u = ch[u][idx];
            }
            ed[u] = true; // 标记字符串结尾
        }

        bool check(const string &str) {
            memset(graph, 0, sizeof(graph));
            memset(in_degree, 0, sizeof(in_degree));
            int u = 1;
            for (int i = 0; i < str.size(); ++i) {
                if (ed[u]) return false; // 存在前缀，无法成为最小
                int c = str[i] - 'a';
                for (int d = 0; d < 26; ++d) {
                    if (d != c && ch[u][d]) { // 同层其他字符d
                        if (!graph[c][d]) {
                            graph[c][d] = 1;
                            in_degree[d]++;
                        }
                    }
                }
                u = ch[u][c];
            }
            // 拓扑排序判断是否有环
            queue<int> q;
            for (int i = 0; i < 26; ++i) {
                if (in_degree[i] == 0) q.push(i);
            }
            int cnt = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                cnt++;
                for (int v = 0; v < 26; ++v) {
                    if (graph[u][v]) {
                        if (--in_degree[v] == 0) {
                            q.push(v);
                        }
                    }
                }
            }
            return cnt == 26; // 所有节点入度为0，无环
        }
    } trie;

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            trie.insert(s[i]);
        }
        for (int i = 1; i <= n; ++i) {
            if (trie.check(s[i])) {
                is_valid[i] = true;
                ans_cnt++;
            }
        }
        cout << ans_cnt << "\n";
        for (int i = 1; i <= n; ++i) {
            if (is_valid[i]) cout << s[i] << "\n";
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先将所有字符串插入Trie树（`insert`函数），然后对每个字符串调用`check`函数：检查是否是其他字符串的前缀（`ed[u]`判断），建立字符间的约束边（`graph`数组），最后用拓扑排序判断是否有环（`cnt == 26`表示无环）。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者 Heartlessly**
* **亮点**：代码结构清晰，`insert`和`find`函数分工明确，拓扑排序单独封装，易于调试。
* **核心代码片段**：
    ```cpp
    inline bool find(string x) {
        int u = 1, len = x.size();
        memset(e, 0, sizeof(e));
        memset(in, 0, sizeof(in));
        for (int i = 0; i < len; ++i) {
            if (ed[u]) return 0; // 存在前缀，返回失败
            int v = x[i] - 'a';
            for (int j = 0; j < 26; ++j)
                if (v != j && ch[u][j] && !e[v][j]) {
                    e[v][j] = 1; // 建立约束边v→j
                    ++in[j]; // j的入度+1
                }
            u = ch[u][v];
        }
        topoSort(); // 拓扑排序
        for (int i = 0; i < 26; ++i)
            if (in[i]) return 0; // 有环，返回失败
        return 1;
    }
    ```
* **代码解读**：`find`函数处理单个字符串的检查。首先清空约束边和入度数组，遍历字符串的每个字符，检查是否是其他字符串的前缀（`ed[u]`），然后为同层其他字符建立约束边（`e[v][j]`），最后拓扑排序判断是否有环。
* 💡 **学习笔记**：通过`memset`清空数组避免状态残留，是处理多测试用例的关键。

**题解二：作者 littleming**
* **亮点**：代码简洁，用`used`数组避免重复建边，减少冗余计算。
* **核心代码片段**：
    ```cpp
    inline void solve(string x) {
        int u = 0, t;
        for (int i = 0; i < x.size(); ++i) {
            t = x[i] - 'a';
            if (vis[u]) { // 存在前缀
                f = 1;
                return;
            }
            for (int j = 0; j < 26; ++j) {
                if (ch[u][j] && j != t && !used[t][j]) {
                    used[t][j] = 1; // 标记已建边
                    addedge(t, j); // 建立约束边t→j
                    ind[j]++; // j的入度+1
                }
            }
            u = ch[u][t];
        }
    }
    ```
* **代码解读**：`solve`函数遍历字符串，检查前缀（`vis[u]`），并用`used`数组避免重复建立相同的边（`used[t][j]`），提升效率。
* 💡 **学习笔记**：`used`数组是优化关键，避免图中出现重复边导致入度错误。

**题解三：作者 liuxu**
* **亮点**：通过`E`数组存储图结构，直观展示字符间的依赖关系。
* **核心代码片段**：
    ```cpp
    int work(string s) {
        int now = 1;
        for (int i = 0; i < s.length(); ++i) {
            int t = s[i] - 'a';
            if (N[now].end) return 0; // 存在前缀，返回0
            for (int j = 0; j < 26; ++j) {
                if (N[now].son[j] && t != j) {
                    E[t].push_back(j); // 建立约束边t→j
                    ind[j]++; // j的入度+1
                }
            }
            now = N[now].son[t];
        }
        return 1;
    }
    ```
* **代码解读**：`work`函数遍历字符串，检查前缀（`N[now].end`），并将约束边存入`E`数组（邻接表），便于后续拓扑排序。
* 💡 **学习笔记**：邻接表存储图结构适合稀疏图，节省空间。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解Trie树构建和拓扑排序的过程，我们设计了一个“像素字母探险”动画，以8位复古风格展示关键步骤！
</visualization_intro>

  * **动画演示主题**：`像素字母探险——寻找最小字典序`

  * **核心演示内容**：展示Trie树的构建（每个节点是彩色像素块），字符串检查时的约束边建立（箭头从当前字符指向同层其他字符），拓扑排序过程（队列中的像素方块入队、处理边、更新入度）。

  * **设计思路简述**：8位像素风格（FC红白机配色）营造轻松氛围，关键步骤高亮（如当前处理的字符、入度为0的节点），音效提示（边建立时“叮”，无环时“胜利”音效），帮助学习者记忆关键操作。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕分为左右两部分：左侧是Trie树区域（网格状，每个节点是16x16像素块，颜色代表字符），右侧是拓扑排序区域（队列和入度表）。
        - 控制面板：单步/自动播放按钮，速度滑块（1-5倍速），重置按钮。
        - 8位风格背景音乐（如《超级马里奥》经典旋律）。

    2.  **Trie树构建**：
        - 输入字符串时，每个字符以像素点形式从输入框“飞”到Trie树区域，生成新节点（绿色像素块），路径用虚线连接。
        - 字符串结尾节点标记为红色（`ed[u]=true`）。

    3.  **字符串检查（约束边建立）**：
        - 选择待检查字符串，字符逐个高亮（黄色闪烁）。
        - 遍历到第i层时，当前字符节点（蓝色）同层的其他字符节点（灰色）出现箭头（蓝色→灰色），表示约束边（当前字符必须更小），伴随“叮”音效。
        - 若发现红色结尾节点（存在前缀），播放“错误”音效，该字符串标记为无效。

    4.  **拓扑排序过程**：
        - 拓扑排序区域显示26个字母的入度（白色数字）。
        - 入度为0的字母（绿色）自动“滑入”队列（像素方块堆叠），播放“入队”音效。
        - 处理队列中的字母时，其出边（箭头）消失，目标字母入度减1（数字变化），若入度变为0则滑入队列。
        - 所有字母处理完成（队列空且入度全0），播放“胜利”音效，该字符串标记为有效。

    5.  **结果展示**：
        - 有效字符串在屏幕下方以金色像素文字显示，无效字符串以灰色显示。

  * **旁白提示**：
      - “看！当前字符是'm'，同层的其他字符是'o'和'm'，所以需要建立'm→o'的约束边。”
      - “入度为0的字母'c'入队啦，它的出边处理后，'d'的入度从2减到1！”
      - “所有字母都处理完了，没有环，这个字符串可以成为最小！”

<visualization_conclusion>
通过这样的动画，我们能直观看到Trie树如何存储字符串，约束边如何建立，以及拓扑排序如何判断是否存在合法顺序，让抽象的算法变得“可见可触”！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的Trie树和拓扑排序后，我们可以尝试解决更多类似问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - Trie树适用于处理字符串前缀、字典序比较等问题（如敏感词过滤、自动补全）。
      - 拓扑排序适用于有依赖关系的顺序判断（如课程安排、任务调度）。
      - 本题的约束边建立思路可迁移到其他需要“定义元素优先级”的问题（如比赛排名、规则制定）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P2580 [ZJOI2008]树的统计**  
        * 🗣️ **推荐理由**：练习Trie树的扩展应用（结合统计信息），提升对字符串处理的理解。
    2.  **洛谷 P4017 最大食物链计数**  
        * 🗣️ **推荐理由**：巩固拓扑排序的应用，理解如何用拓扑序计算路径数。
    3.  **洛谷 P3879 [TJOI2010]阅读理解**  
        * 🗣️ **推荐理由**：练习Trie树的高效查询，适合强化字符串处理能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，以下是值得借鉴的内容：
</insights_intro>

> **参考经验 (来自作者 liuxu)**：“一开始没考虑前缀情况，导致拓扑排序后结果错误。后来通过打印Trie树的`ed`标记，发现某些节点被错误标记，才意识到需要先检查前缀。”

**点评**：liuxu的经验提醒我们，处理字符串前缀是本题的关键前提。调试时打印关键变量（如`ed[u]`）能快速定位问题，这是解决复杂问题的重要技巧。

-----

<conclusion>
本次关于“[USACO12DEC] First! G”的分析就到这里。通过Trie树和拓扑排序的结合，我们学会了如何判断字符串是否能成为最小字典序。希望大家通过练习巩固知识，下次挑战更难的题目！💪
</conclusion>

-----

---
处理用时：180.78秒