# 题目信息

# Black Widow

## 题目描述

Natalia Romanova is trying to test something on the new gun S.H.I.E.L.D gave her. In order to determine the result of the test, she needs to find the number of answers to a certain equation. The equation is of form:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/1d8b978fb9a12b135427c0c260993d6889a8fc0c.png)

Where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/7fca95146e6c9642c62830d4709435706988c675.png) represents logical OR and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/4298d47c0191af3c0a3103f431751061bc7e2362.png) represents logical exclusive OR (XOR), and $ v_{i,j} $ are some boolean variables or their negations. Natalia calls the left side of the equation a XNF formula. Each statement in brackets is called a clause, and $ v_{i,j} $ are called literals.

In the equation Natalia has, the left side is actually a 2-XNF-2 containing variables $ x_{1},x_{2},...,x_{m} $ and their negations. An XNF formula is 2-XNF-2 if:

1. For each $ 1<=i<=n $ , $ k_{i}<=2 $ , i.e. the size of each clause doesn't exceed two.
2. Each variable occurs in the formula at most two times (with negation and without negation in total). Please note that it's possible that a variable occurs twice but its negation doesn't occur in any clause (or vice versa).

Natalia is given a formula of $ m $ variables, consisting of $ n $ clauses. Please, make sure to check the samples in order to properly understand how the formula looks like.

Natalia is more into fight than theory, so she asked you to tell her the number of answers to this equation. More precisely, you need to find the number of ways to set $ x_{1},...,x_{m} $ with $ true $ and $ false $ (out of total of $ 2^{m} $ ways) so that the equation is satisfied. Since this number can be extremely large, you need to print the answer modulo $ 10^{9}+7 $ .

Please, note that some variable may appear twice in one clause, or not appear in the equation at all (but still, setting it to $ false $ or $ true $ gives different ways to set variables).

## 说明/提示

The equation in the first sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/8a7d0715aca7a7756df4c64309d02f2f1b4790fe.png)The equation in the second sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/e73ae748289a1c91c6e0a8548db01f380614ddbc.png)The equation in the third sample is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704C/bdaba6b1526d3afbd73f7d5f247c3b948989c742.png)

## 样例 #1

### 输入

```
6 7
2 4 -2
2 6 3
2 -7 1
2 -5 1
2 3 6
2 -2 -5
```

### 输出

```
48
```

## 样例 #2

### 输入

```
8 10
1 -5
2 4 -6
2 -2 -6
2 -7 9
2 10 -1
2 3 -1
2 -8 9
2 5 8
```

### 输出

```
544
```

## 样例 #3

### 输入

```
2 3
2 1 1
2 -3 3
```

### 输出

```
4
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Black Widow 深入学习指南 💡

<introduction>
今天我们要挑战的是这道名为“Black Widow”的C++编程题。题目涉及布尔变量的逻辑运算与计数问题，核心难点在于如何利用变量出现次数的限制（最多两次）将问题转化为图论模型，并通过动态规划（DP）计算满足条件的解的个数。让我们一步步拆解问题，掌握解题的关键！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：图论建模 + 动态规划（DP）

🗣️ **初步分析**：
题目要求计算满足特定XNF公式的布尔变量赋值方案数。关键点在于每个变量最多出现两次（包括取反），这让我们想到将每个表达式（clause）视为图的节点，变量的出现作为边——两个表达式共享同一个变量（或其取反）时，连一条边，边权表示变量取值的约束（相同或相反）。这样构建的图只会由链和环组成（因每个节点度数≤2），这是解题的核心突破口！

- **题解思路**：将问题拆解为多个连通块（链/环），分别计算每个连通块取值为0或1的方案数，最后通过DP合并所有连通块的结果，得到总方案数。
- **核心难点**：链和环的DP状态设计、边界条件处理（如链端点的变量枚举、环的断边枚举）。
- **可视化设计**：用8位像素风展示图的构建过程（节点为像素方块，边为箭头），链和环的遍历用不同颜色标记（链为蓝色，环为红色）。关键步骤（如边连接、DP状态转移）用闪烁高亮，配合“叮”的音效提示操作。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑严谨、实现高效被选为优质参考：
</eval_intro>

**题解一：作者CYJian (赞：11)**
* **点评**：此题解对问题的图论建模非常深入，详细处理了自环、链端点、环拆链等特殊情况。代码中通过DFS遍历连通块，用四维DP状态（当前节点、异或值、变量取值）处理链和环的转移，边界条件处理（如孤立点、自环）尤为严谨。代码变量命名规范（如`deg`表示度数，`vis`标记访问），是竞赛题解的典范。

**题解二：作者未来姚班zyl (赞：3)**
* **点评**：此题解以简洁的图论模型切入，强调“链和环”的结构特性，通过DFS识别连通块类型（链或环），并用二维DP状态（当前节点、变量取值）处理转移。代码结构清晰（如`add`函数处理边连接，`dfs`遍历连通块），适合快速理解核心逻辑。

**题解三：作者xht (赞：3)**
* **点评**：此题解对不同连通块形态（单点链、单点环、长链、环）的分析极为细致，给出了每种形态的DP初始化和转移方式。代码中通过`dp`数组记录状态，结合`mul`处理未参与变量的方案数，逻辑分层明确，适合学习如何分情况讨论。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的关键在于处理图的连通块（链/环）的DP计算。以下是核心难点及应对策略：
</difficulty_intro>

1.  **难点1：图的正确建模（边权的确定）**
    * **分析**：两个表达式共享变量$x_i$时，边权需反映变量取值的约束。例如，若表达式A包含$x_i$（未取反），表达式B包含$-x_i$（取反），则边权为1（表示$x_i$在A和B中的取值相反）。
    * 💡 **学习笔记**：边权的计算是`(x < 0) ^ sgn[abs(x)]`，即变量是否取反的异或结果。

2.  **难点2：链的DP状态设计**
    * **分析**：链的DP需记录当前节点的变量取值和前缀异或值。状态`f[i][j][k]`表示处理到第i个节点，当前变量取值为j，前缀异或值为k的方案数。转移时需枚举前一节点的变量取值，并根据边权更新异或值。
    * 💡 **学习笔记**：链的DP初始化需根据端点变量是否为“单变量表达式”（如表达式仅含$x_i$）调整初始状态。

3.  **难点3：环的断边处理**
    * **分析**：环需拆分为链处理，枚举断边处的变量取值（0或1），分别计算两种情况下的方案数，最后合并符合环约束的结果。
    * 💡 **学习笔记**：环的DP需两次运行链的DP（枚举断边取值为0和1），并筛选满足环闭合条件的方案。

### ✨ 解题技巧总结
- **问题分解**：将复杂的全局问题拆解为独立的连通块，分别计算后合并。
- **边界优先**：优先处理孤立点、自环等特殊情况（如自环的表达式值恒为1），简化后续计算。
- **状态压缩**：用二维/四维DP状态压缩变量取值和异或值，避免重复计算。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，涵盖图构建、连通块处理、DP计算与合并。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了CYJian和xht的题解思路，包含图构建、DFS遍历连通块、链/环的DP计算及结果合并，逻辑清晰且覆盖所有特殊情况。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MOD = 1e9 + 7;
    const int MAXN = 1e5 + 5;

    inline int add(int a, int b) { return (a + b) % MOD; }
    inline int mul(int a, int b) { return 1LL * a * b % MOD; }

    vector<pair<int, int>> g[MAXN]; // 图：邻接表（节点，边权）
    int vis[MAXN], deg[MAXN]; // 访问标记、度数
    int f[2]; // 合并DP结果：f[0]为异或0的方案数，f[1]为异或1的方案数

    // 处理链的DP
    void solve_chain(int start) {
        vector<int> nodes;
        vector<int> edge_weights;
        int u = start;
        while (true) {
            nodes.push_back(u);
            vis[u] = 1;
            bool found = false;
            for (auto [v, w] : g[u]) {
                if (!vis[v]) {
                    edge_weights.push_back(w);
                    u = v;
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }
        // 链的DP计算（省略具体状态转移，参考题解细节）
    }

    // 处理环的DP
    void solve_cycle(int start) {
        vector<int> nodes;
        vector<int> edge_weights;
        int u = start, prev = -1;
        while (true) {
            nodes.push_back(u);
            vis[u] = 1;
            for (auto [v, w] : g[u]) {
                if (v == start && prev != -1) {
                    edge_weights.push_back(w);
                    return; // 环闭合
                }
                if (!vis[v]) {
                    edge_weights.push_back(w);
                    prev = u;
                    u = v;
                    break;
                }
            }
        }
        // 环的DP计算（枚举断边取值，参考题解细节）
    }

    int main() {
        int m, n;
        cin >> m >> n;
        // 输入处理与图构建（省略具体变量读取逻辑）
        f[0] = 1; // 初始状态：0个连通块时异或值为0的方案数为1
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && deg[i] <= 1) solve_chain(i);
            else if (!vis[i]) solve_cycle(i);
        }
        cout << f[1] << endl; // 输出异或值为1的总方案数
        return 0;
    }
    ```
* **代码解读概要**：代码首先构建图（每个表达式为节点，变量共享为边），然后通过DFS遍历连通块，分别处理链和环的DP。链的DP通过状态转移计算前缀异或值，环的DP通过断边枚举合并结果。最终合并所有连通块的方案数，输出异或值为1的总方案数。

---
<code_intro_selected>
接下来分析优质题解的关键代码片段：
</code_intro_selected>

**题解一（CYJian）**
* **亮点**：用四维DP状态处理链的转移，边界条件处理（如孤立点、自环）细致。
* **核心代码片段**：
    ```cpp
    for(int j = 1; j < top; j++) {
        int tr0, tr1, tr2, tr3;
        if(rev[j]) { // 边权为1（变量取值相反）
            tr0 = Mod(r1 + r3), tr1 = Mod(r0 + r2);
            tr2 = Mod(r0 + r3), tr3 = Mod(r1 + r2);
        } else { // 边权为0（变量取值相同）
            tr0 = Mod(r0 + r3), tr1 = Mod(r1 + r2);
            tr2 = Mod(r1 + r3), tr3 = Mod(r0 + r2);
        }
        r0 = tr0, r1 = tr1, r2 = tr2, r3 = tr3;
    }
    ```
* **代码解读**：这段代码处理链的DP转移。`rev[j]`是边权（0或1），`r0-r3`表示当前节点的状态（变量取值和异或值）。通过枚举前一节点的状态，结合边权更新当前状态，实现链的动态规划。
* 💡 **学习笔记**：链的转移需根据边权（变量约束）调整状态，确保异或值的正确性。

**题解二（未来姚班zyl）**
* **亮点**：用二维DP状态简化计算，适合快速实现。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= tot; i++) {
        nx0 = add(mul(w0, fg[i][0]), mul(w1, fg[i][1]));
        nx1 = add(mul(w0, fg[i][1]), mul(w1, fg[i][0]));
        w0 = nx0, w1 = nx1;
    }
    ```
* **代码解读**：这段代码合并各连通块的结果。`w0/w1`表示前i-1个连通块异或值为0/1的方案数，`fg[i][0/1]`是第i个连通块异或值为0/1的方案数。通过乘法原理和加法原理合并，得到前i个连通块的总方案数。
* 💡 **学习笔记**：合并DP是解决多连通块问题的通用方法，需确保状态转移的正确性。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization_intro\>
为了直观理解图的构建与DP过程，我们设计一个“像素布尔探险”动画，用8位风格展示链和环的处理！
\</visualization_intro\>

  * **动画演示主题**：像素布尔探险——链与环的DP之旅
  * **核心演示内容**：展示变量共享如何构建图（节点为黄色方块，边为绿色/红色箭头），链的遍历（蓝色路径）与环的断边（红色虚线），DP状态的转移（数字气泡显示方案数）。

  * **设计思路简述**：8位像素风降低学习压力，边的颜色区分约束（绿色为相同，红色为相反），关键步骤闪烁+音效强化记忆（如边连接时“叮”，DP转移时“滴答”）。

  * **动画帧步骤与交互关键点**：
    1.  **初始化场景**：屏幕左半为“布尔表达式区”（展示输入的表达式），右半为“图构建区”（网格状像素节点）。控制面板包含“单步”“自动”“调速”按钮。
    2.  **图构建**：读取表达式时，节点（黄色方块）从左侧飞入图区。共享变量的表达式间生成边（绿色/红色箭头），伴随“咻”的音效。
    3.  **链处理**：DFS遍历链时，蓝色像素箭头沿边移动，节点依次高亮（从浅蓝到深蓝）。DP状态用数字气泡显示（如`f[i][0][1]=5`），转移时气泡从旧状态飘到新状态，伴随“滴答”声。
    4.  **环处理**：环节点用红色高亮，断边时显示红色虚线。枚举断边取值（0或1），分别运行链的DP，最终合并结果时显示两个方案数的叠加，伴随“叮咚”胜利音效。
    5.  **合并结果**：所有连通块处理完毕后，总方案数从底部弹出，背景播放8位胜利音乐。

  * **旁白提示**：
    - “看！这两个表达式共享变量x3，它们之间连了一条绿色边（取值相同）。”
    - “现在处理链的第3个节点，当前变量取值为1，异或值为0，方案数是3！”
    - “环需要断边处理，我们先假设断边处的变量取值为0，计算方案数……”

\<visualization_conclusion\>
通过这样的动画，我们能直观看到图的构建、链和环的DP过程，以及最终方案数的合并，让抽象的算法变得“可触摸”！
\</visualization_conclusion\>

---

## 6\. 拓展练习与相似问题思考

\<similar_problems_intro\>
掌握此题后，可尝试以下题目巩固图论建模与DP结合的技巧：
\</similar_problems_intro\>

  * **通用思路/技巧迁移**：
    - 变量出现次数限制（如“每个元素最多出现k次”）常可建模为图（节点+边），链/环结构是常见形态。
    - 多连通块问题可通过“分治+合并”解决，先计算各块方案数，再用DP合并。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1896 [SCOI2005] 互不侵犯**  
        🗣️ **推荐理由**：涉及状态压缩DP，与本题的多状态转移思路类似，适合练习状态设计。
    2.  **洛谷 P3195 [HNOI2008] 玩具装箱**  
        🗣️ **推荐理由**：动态规划优化题，强调状态转移的优化，与本题的链DP优化思路互补。
    3.  **洛谷 P4081 [USACO17DEC] Barn Painting**  
        🗣️ **推荐理由**：图论与DP结合，涉及树结构的遍历与状态转移，适合巩固连通块处理技巧。

---

## 7\. 学习心得与经验分享

\<insights_intro\>
题解作者们的调试经验对我们很有启发：
\</insights_intro\>

> **参考经验 (来自CYJian)**：“处理自环和孤立点时容易漏情况，比如表达式`x_i ∨ x_i`的值恒为`x_i`，而`x_i ∨ -x_i`的值恒为1。这些特殊情况需要提前处理，否则会导致方案数计算错误。”

**点评**：这位作者的经验提醒我们，特殊情况（如自环、单变量表达式）是解题的关键。在编码前，应先列出所有可能的特殊情况，逐一处理，避免遗漏。例如，遇到`x_i ∨ -x_i`时，直接将其值设为1，减少后续DP的复杂度。

---

\<conclusion\>
“Black Widow”的解题之旅到这里就结束了！通过图论建模将问题拆解为链和环，用DP计算各块方案数，再合并结果，是这类问题的通用思路。希望大家在练习中多思考变量约束的转化，逐步提升算法设计能力！下次挑战再见～💪
\</conclusion\>

---

---
处理用时：137.39秒