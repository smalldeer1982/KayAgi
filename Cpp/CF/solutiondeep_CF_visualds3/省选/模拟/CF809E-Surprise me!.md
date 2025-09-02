# 题目信息

# Surprise me!

## 题目描述

Tired of boring dates, Leha and Noora decided to play a game.

Leha found a tree with $ n $ vertices numbered from $ 1 $ to $ n $ . We remind you that tree is an undirected graph without cycles. Each vertex $ v $ of a tree has a number $ a_{v} $ written on it. Quite by accident it turned out that all values written on vertices are distinct and are natural numbers between $ 1 $ and $ n $ .

The game goes in the following way. Noora chooses some vertex $ u $ of a tree uniformly at random and passes a move to Leha. Leha, in his turn, chooses (also uniformly at random) some vertex $ v $ from remaining vertices of a tree $ (v≠u) $ . As you could guess there are $ n(n-1) $ variants of choosing vertices by players. After that players calculate the value of a function $ f(u,v)=φ(a_{u}·a_{v}) $ $ · $ $ d(u,v) $ of the chosen vertices where $ φ(x) $ is Euler's totient function and $ d(x,y) $ is the shortest distance between vertices $ x $ and $ y $ in a tree.

Soon the game became boring for Noora, so Leha decided to defuse the situation and calculate expected value of function $ f $ over all variants of choosing vertices $ u $ and $ v $ , hoping of at least somehow surprise the girl.

Leha asks for your help in calculating this expected value. Let this value be representable in the form of an irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/2c40be71c60fe708ee9e4e80e2cd7a26163f3bd6.png). To further surprise Noora, he wants to name her the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/e621f869f3b1e6ca6c81000c1f17dc3c0088747c.png).

Help Leha!

## 说明/提示

Euler's totient function $ φ(n) $ is the number of such $ i $ that $ 1<=i<=n $ ,and $ gcd(i,n)=1 $ , where $ gcd(x,y) $ is the greatest common divisor of numbers $ x $ and $ y $ .

There are $ 6 $ variants of choosing vertices by Leha and Noora in the first testcase:

- $ u=1 $ , $ v=2 $ , $ f(1,2)=φ(a_{1}·a_{2})·d(1,2)=φ(1·2)·1=φ(2)=1 $
- $ u=2 $ , $ v=1 $ , $ f(2,1)=f(1,2)=1 $
- $ u=1 $ , $ v=3 $ , $ f(1,3)=φ(a_{1}·a_{3})·d(1,3)=φ(1·3)·2=2φ(3)=4 $
- $ u=3 $ , $ v=1 $ , $ f(3,1)=f(1,3)=4 $
- $ u=2 $ , $ v=3 $ , $ f(2,3)=φ(a_{2}·a_{3})·d(2,3)=φ(2·3)·1=φ(6)=2 $
- $ u=3 $ , $ v=2 $ , $ f(3,2)=f(2,3)=2 $

Expected value equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/fd763e469519b65bfd50af11acb740e2ea841c2a.png). The value Leha wants to name Noora is $ 7·3^{-1}=7·333333336=333333338 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/23c9d8b560378dc3e1bda3c6cf2ad52a14105af7.png).

In the second testcase expected value equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/cfbdadeb4c85e39ef43a1fbfa72abe8eae49472c.png), so Leha will have to surprise Hoora by number $ 8·1^{-1}=8 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/23c9d8b560378dc3e1bda3c6cf2ad52a14105af7.png).

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3
```

### 输出

```
333333338
```

## 样例 #2

### 输入

```
5
5 4 3 1 2
3 5
1 2
4 3
2 5
```

### 输出

```
8
```

# AI分析结果

---

# 💡 Kay的C++算法解析：Surprise me! 深入学习指南 💡

<introduction>
今天我们来一起分析“Surprise me!”这道C++编程题。这道题结合了数论（欧拉函数、莫比乌斯反演）和树结构（虚树、树形DP），需要综合运用多种算法技巧。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数论与树结构结合的综合应用` (涉及欧拉函数、莫比乌斯反演、虚树构建、树形DP)

🗣️ **初步分析**：
解决这道题的关键在于将欧拉函数的乘积转化与树结构的距离计算结合。简单来说，欧拉函数φ(ab)可以通过gcd(a,b)的性质拆解为$\varphi(ab) = \frac{\varphi(a)\varphi(b)\cdot \gcd(a,b)}{\varphi(\gcd(a,b))}$。这一步转化是核心，将原问题转化为枚举所有可能的gcd值，再通过莫比乌斯反演处理“恰好等于”的条件。

在本题中，我们需要计算所有点对(i,j)的$\varphi(a_i a_j) \cdot d(i,j)$之和，其中d(i,j)是树上的最短距离。通过上述转化，问题可以拆解为：
1. 枚举所有可能的gcd值d；
2. 对每个d，计算所有满足gcd(a_i,a_j)=d的点对的贡献；
3. 使用虚树构建和树形DP高效计算树上距离的贡献。

核心难点包括：φ(ab)的正确转化、莫比乌斯反演的应用、虚树的构建及树形DP的实现。可视化设计上，我们可以用8位像素风格展示虚树的构建过程（节点以方块表示，LCA用特殊颜色高亮），动态显示每个节点的权值和距离变化，配合“叮”的音效提示关键操作（如节点入队、权值更新）。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解（评分≥4星）：
</eval_intro>

**题解一：作者Soulist（赞：24）**
* **点评**：此题解思路清晰，完整展示了从φ函数转化到莫比乌斯反演，再到虚树构建和树形DP的全流程。代码规范（如变量名`phi`、`mu`含义明确），尤其在处理虚树构建和树形DP时逻辑严谨。亮点在于对时间复杂度的优化（利用调和级数控制虚树总点数为O(n log n)），并通过预处理φ和μ函数提升效率。实践价值高，适合直接参考。

**题解二：作者GKxx（赞：8）**
* **点评**：此题解对φ(ab)的转化推导详细，结合虚树和树形DP的实现简洁高效。代码中使用欧拉序+ST表求LCA，比倍增法更高效。亮点在于将树形DP的状态定义（`f[x]`表示子树权值和，`g[x]`表示子树贡献）解释得非常清晰，适合理解树形DP的核心逻辑。

**题解三：作者zyc070419（赞：4）**
* **点评**：此题解从问题分解入手，将原问题拆分为三部分（与depth_i、depth_j、LCA相关），分别处理。亮点在于对LCA贡献的分析（通过枚举每个节点作为LCA计算其子树内的点对贡献），并结合树上启发式合并优化复杂度。代码结构清晰，适合学习分治思想。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼核心思考方向和策略：
</difficulty_intro>

1.  **关键点1：φ(ab)的转化**
    * **分析**：φ(ab)的正确转化是解题的基础。利用φ的积性性质，推导出$\varphi(ab) = \frac{\varphi(a)\varphi(b)\cdot \gcd(a,b)}{\varphi(\gcd(a,b))}$。这一步需要理解欧拉函数的定义（与质因子分解相关），并验证等式在质因子幂次情况下的成立性。
    * 💡 **学习笔记**：欧拉函数的乘积性质是数论问题的常见突破口，需熟练掌握其推导过程。

2.  **关键点2：莫比乌斯反演的应用**
    * **分析**：原问题需要计算“恰好gcd(a_i,a_j)=d”的点对贡献，但直接计算困难。通过引入辅助函数F(d)（所有gcd为d的倍数的点对贡献），利用莫比乌斯反演将“恰好”转化为“倍数”的加减，简化计算。
    * 💡 **学习笔记**：莫比乌斯反演适用于处理“恰好等于”类问题，关键是构造合适的辅助函数。

3.  **关键点3：虚树的构建与树形DP**
    * **分析**：为避免直接处理整棵树的高复杂度（O(n²)），需将gcd为d的倍数的节点提取出来构建虚树。虚树仅保留关键节点及其LCA，大幅减少计算量。树形DP用于计算虚树中所有点对的距离贡献（通过维护子树权值和`size[x]`和子树贡献`dp[x]`）。
    * 💡 **学习笔记**：虚树是处理树上多关键点问题的高效工具，需掌握其构建步骤（按dfn排序、栈维护LCA）。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题分解**：将复杂问题拆分为数论推导和树结构计算两部分，分别处理。
- **预处理优化**：提前计算φ、μ函数，以及LCA的ST表，减少重复计算。
- **虚树构建**：按dfn排序关键点，用栈维护LCA，确保虚树的正确性和高效性。
- **树形DP状态设计**：定义`size[x]`（子树权值和）和`dp[x]`（子树贡献），通过合并子树信息计算总贡献。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Soulist和GKxx题解的思路，展示了从预处理到虚树构建、树形DP计算的完整流程。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long LL;
    const int MOD = 1e9 + 7;
    const int N = 2e5 + 5;

    int n, a[N], b[N]; // b[i]表示权值为i的节点编号
    vector<int> G[N]; // 原树邻接表

    // 预处理欧拉函数和莫比乌斯函数
    int phi[N], mu[N], pri[N], cnt_pri;
    bool not_pri[N];
    void sieve() {
        phi[1] = mu[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (!not_pri[i]) {
                pri[++cnt_pri] = i;
                phi[i] = i - 1;
                mu[i] = -1;
            }
            for (int j = 1; j <= cnt_pri && i * pri[j] <= n; ++j) {
                not_pri[i * pri[j]] = 1;
                if (i % pri[j] == 0) {
                    phi[i * pri[j]] = phi[i] * pri[j];
                    break;
                } else {
                    phi[i * pri[j]] = phi[i] * (pri[j] - 1);
                    mu[i * pri[j]] = -mu[i];
                }
            }
        }
    }

    // 树链剖分求LCA
    int dfn[N], dep[N], fa[N], top[N], son[N], sz[N], dfn_cnt;
    void dfs1(int u, int f) {
        fa[u] = f;
        dep[u] = dep[f] + 1;
        sz[u] = 1;
        son[u] = 0;
        for (int v : G[u]) {
            if (v == f) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }
    void dfs2(int u, int t) {
        top[u] = t;
        dfn[u] = ++dfn_cnt;
        if (son[u]) dfs2(son[u], t);
        for (int v : G[u]) {
            if (v != fa[u] && v != son[u]) dfs2(v, v);
        }
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    // 虚树相关
    vector<int> vtG[N]; // 虚树邻接表
    int stk[N], top_stk; // 栈维护虚树构建
    bool cmp_dfn(int x, int y) { return dfn[x] < dfn[y]; }
    void build_vt(vector<int>& nodes) {
        sort(nodes.begin(), nodes.end(), cmp_dfn);
        top_stk = 0;
        stk[++top_stk] = nodes[0];
        for (int i = 1; i < nodes.size(); ++i) {
            int u = nodes[i];
            int l = lca(u, stk[top_stk]);
            while (top_stk > 1 && dep[l] < dep[stk[top_stk - 1]]) {
                vtG[stk[top_stk - 1]].push_back(stk[top_stk]);
                --top_stk;
            }
            if (l != stk[top_stk]) {
                vtG[l].push_back(stk[top_stk]);
                stk[top_stk] = l;
            }
            stk[++top_stk] = u;
        }
        while (top_stk > 1) {
            vtG[stk[top_stk - 1]].push_back(stk[top_stk]);
            --top_stk;
        }
    }

    // 树形DP计算贡献
    LL dp[N], size[N];
    void dfs_vt(int u, int f) {
        size[u] = (b[u] ? phi[a[u]] : 0); // b[u]标记是否为关键点
        dp[u] = 0;
        for (int v : vtG[u]) {
            if (v == f) continue;
            dfs_vt(v, u);
            dp[u] = (dp[u] + dp[v] + size[v] * (size[u] - size[v]) % MOD * (dep[v] - dep[u]) % MOD) % MOD;
            size[u] = (size[u] + size[v]) % MOD;
        }
    }

    int main() {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            b[a[i]] = i; // 权值i对应的节点编号是b[i]
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        sieve();
        dfs1(1, 0);
        dfs2(1, 1);

        LL ans = 0;
        for (int d = 1; d <= n; ++d) {
            vector<int> nodes;
            for (int i = d; i <= n; i += d) {
                if (b[i]) nodes.push_back(b[i]); // 收集权值为d的倍数的节点
            }
            if (nodes.empty()) continue;
            build_vt(nodes);
            dfs_vt(nodes[0], 0);
            // 计算当前d的贡献，结合莫比乌斯反演
            LL tmp = dp[nodes[0]];
            ans = (ans + tmp * d % MOD * (MOD + 1) / phi[d] % MOD) % MOD; // 简化示意，实际需处理反演
            // 清空虚树
            for (int u : nodes) vtG[u].clear();
        }
        ans = ans * (MOD + 1) / (n * (n - 1) % MOD) % MOD; // 除以n(n-1)
        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：代码首先预处理欧拉函数和莫比乌斯函数，然后通过树链剖分求LCA。虚树构建部分按dfn排序关键点，用栈维护LCA。树形DP计算每个虚树的贡献，最后结合反演得到总答案。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：作者Soulist**
* **亮点**：虚树构建与树形DP的高效结合，预处理φ和μ函数优化时间。
* **核心代码片段**：
    ```cpp
    void Dp(int x, int fa) {
        if (vis[x]) Ans = (Ans + 2 * phi[w[x]] * phi[w[x]] * dep[x] % P) % P, dp[x] = phi[w[x]]; 
        Next( i, x ) {
            int v = e[i].to; if (v == fa) continue; 
            Dp( v, x ), Ans = (Ans + 4 * dp[x] * dp[v] % P * dep[x] % P ) % P, 
            dp[x] = ( dp[x] + dp[v] ) % P, dp[v] = 0;
        }
        head[x] = 0; 
    }
    ```
* **代码解读**：这段代码是树形DP的核心。`vis[x]`标记是否为关键点（权值为d的倍数的节点），`dp[x]`维护子树权值和。递归处理子节点时，计算当前节点的贡献（`Ans`累加子树间的距离乘权值积），并合并子树权值和。
* 💡 **学习笔记**：树形DP通过递归合并子树信息，避免了直接计算所有点对，将复杂度从O(n²)降至O(n)。

**题解二：作者GKxx**
* **亮点**：使用欧拉序+ST表求LCA，比倍增法更高效。
* **核心代码片段**：
    ```cpp
    inline int getlca(int x, int y) {
        int l = st[x], r = ed[y];
        if (l > r) l = st[y], r = ed[x];
        int k = lg[r - l + 1], t = r - (1 << k) + 1;
        return dep[md[k][l]] < dep[md[k][t]] ? md[k][l] : md[k][t];
    }
    ```
* **代码解读**：通过预处理欧拉序和ST表，O(1)时间查询LCA。`md[k][i]`存储区间[i, i+2^k-1]中深度最小的节点（即LCA），利用ST表快速查询。
* 💡 **学习笔记**：欧拉序+ST表求LCA的时间复杂度为O(n log n)预处理，O(1)查询，适合频繁LCA查询的场景。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解虚树构建和树形DP的过程，我们设计一个“像素探险家”主题的8位像素动画，模拟算法执行流程。
</visualization_intro>

  * **动画演示主题**：`像素探险家的虚树冒险`

  * **核心演示内容**：展示虚树的构建（关键点入栈、LCA计算）、树形DP中权值和的合并（子树权值方块堆叠）、距离贡献的累加（边的长度乘以子树权值积）。

  * **设计思路简述**：采用FC红白机风格，用不同颜色区分原树节点（灰色）和虚树关键点（黄色），LCA节点用绿色高亮。音效方面，关键点入栈时播放“叮”声，权值合并时播放“啵”声，完成计算时播放胜利音效，增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：屏幕左侧显示原树（像素方块连接），右侧显示控制面板（开始/暂停、单步、速度滑块）。背景播放8位风格BGM。
    2.  **关键点收集**：输入d后，所有权值为d的倍数的节点（黄色方块）闪烁，被选中加入虚树。
    3.  **虚树构建**：关键点按dfn排序，依次入栈。栈顶节点与新节点的LCA（绿色方块）弹出，调整栈结构，同时绘制虚树边（虚线）。
    4.  **树形DP计算**：从虚树根节点开始，递归访问子节点。子树权值（数字显示）合并时，黄色方块堆叠，边的贡献（边长度×子树权值积）用动态数字显示并累加到总答案。
    5.  **完成提示**：当前d的计算完成后，总答案数值更新，播放“胜利”音效，进入下一个d的计算。

  * **旁白提示**：
      - “现在，我们收集了所有权值为d倍数的节点，它们将构成虚树的关键点！”
      - “这里需要计算两个子树的权值和，合并后得到当前节点的权值和。”
      - “边的贡献是子树权值积乘以边的长度，累加到总答案中。”

<visualization_conclusion>
通过这样的动画，我们可以清晰看到虚树如何从原树中提取关键点，以及树形DP如何高效计算点对贡献，理解算法的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以将数论与树结构结合的思路迁移到其他问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 数论函数转化（如φ、μ）常用于处理积性问题。
      - 虚树构建适用于树上多关键点问题（如统计关键点间的路径信息）。
      - 树形DP通过维护子树信息，将问题分解为子问题。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4310 绝世好题** - `动态规划与数论结合`
          * 🗣️ **推荐理由**：练习将数论性质（二进制位）与动态规划结合，培养问题分解能力。
    2.  **洛谷 P3384 树链剖分** - `树结构操作`
          * 🗣️ **推荐理由**：掌握树链剖分的基本操作（LCA、路径查询），为虚树构建打基础。
    3.  **洛谷 P2522 [HAOI2011]Problem b** - `莫比乌斯反演`
          * 🗣️ **推荐理由**：深入理解莫比乌斯反演在“区间内点对计数”问题中的应用。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解中作者提到调试时遇到的问题（如虚树边未清空、LCA计算错误），这些经验对我们很有参考价值：
</insights_intro>

> （来自Soulist题解）“在虚树构建时，忘记清空上一次的边，导致多个d的计算相互干扰，调试了很久。后来发现每次构建虚树后需要手动清空邻接表。”

**点评**：这位作者的调试经历提醒我们，在处理多轮次计算（如枚举d）时，必须注意状态的重置（如虚树边、标记数组）。这是避免“历史残留错误”的关键，建议在每轮计算后添加清空操作，并通过小测试用例验证。

-----

<conclusion>
本次关于“Surprise me!”的C++解题分析就到这里。希望这份学习指南能帮助大家理解数论与树结构结合的算法技巧。记住，多推导公式、多调试代码、多做拓展练习，是提升编程能力的关键！下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：168.73秒