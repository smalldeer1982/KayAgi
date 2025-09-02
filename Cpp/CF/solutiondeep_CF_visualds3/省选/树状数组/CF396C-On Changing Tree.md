# 题目信息

# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2
```

### 输出

```
2
1
```

# AI分析结果


# 💡 Kay的C++算法解析：On Changing Tree 深入学习指南 💡

<introduction>
  今天我们来一起分析"On Changing Tree"这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`树状数组/线段树的应用` 与 `树上差分技巧`

🗣️ **初步分析**：
> 解决"On Changing Tree"这道题，关键在于将树上操作转化为序列操作，并利用差分技巧拆分影响。简单来说，就像在树上"铺开"一张网，每个节点的修改会对其子树产生深度相关的影响。我们可以通过DFS序将子树映射到连续区间，然后利用两个树状数组分别维护常数项和深度系数。

   - 核心思路是将操作1的影响拆分为两个部分：与深度无关的常数项 (x + dep[v]*k) 和与深度相关的系数项 (-k)。这样，每个节点的值可以通过两个树状数组的查询组合得到。
   - 难点在于如何设计数据结构以支持高效的区间修改和单点查询。树状数组因其简洁性和效率成为首选。
   - 在可视化设计中，我们可以用两个并行的像素网格分别表示两个树状数组的更新过程。当执行操作1时，在对应子树的区间上添加颜色块（代表加的值），并随着深度变化调整颜色深浅（代表-k的影响）。查询时，将两个网格的值合并显示。

   - 可视化方案采用8位像素风格，使用不同颜色表示两个树状数组。操作1时，子树区间会闪烁并添加颜色块；查询时，节点会高亮并显示计算过程（A_val - dep[v]*B_val）。添加音效：操作1时播放"添加"音效，查询时播放"成功"音效。可调速播放整个操作序列。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性与优化程度、实践价值等几个方面，为大家筛选了以下评分较高（≥4星）的题解：
</eval_intro>

**题解一：(作者：nekko)**
* **点评**：该题解思路清晰，直接点明拆分为两个树状数组的核心思想。代码简洁规范，使用树状数组实现区间修改和单点查询。亮点在于将公式推导为 (x + dep[v]*k) 和 -k 两部分，并分别维护。代码可读性强，变量命名合理（如`a`, `b`数组），边界处理严谨。实践价值高，可直接用于竞赛。

**题解二：(作者：Pengzt)**
* **点评**：题解同样采用树状数组，但代码更为简洁。亮点在于使用结构体封装两个树状数组，提高了代码复用性。思路推导清晰，强调了深度属性的利用。代码规范，边界处理到位，具有很好的参考价值。

**题解三：(作者：shadowice1984)**
* **点评**：该题解采用离线处理，利用DFS栈的性质确保只有祖先节点的影响被计入。思路独特，但可能不如在线方法直观。亮点在于严格处理了时间顺序和路径条件。代码中树状数组的使用规范，但实现稍复杂。提供了另一种视角，值得学习。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下一些关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何将深度相关的修改拆分为可维护的部分？**
    * **分析**：优质题解普遍将操作拆分为常数部分和深度系数部分。常数部分用区间加维护，深度系数部分则利用深度固有属性在查询时组合。
    * 💡 **学习笔记**：将复杂公式拆解为独立变量是算法设计中的常用技巧。

2.  **关键点2：如何高效实现子树区间修改和单点查询？**
    * **分析**：DFS序将子树映射为连续区间，使我们可以用序列数据结构（树状数组/线段树）维护。树状数组因代码简单、效率高而被广泛采用。
    * 💡 **学习笔记**：DFS序是处理子树问题的有力工具。

3.  **关键点3：如何处理负数取模问题？**
    * **分析**：题解中普遍在最后输出时对负数加模再取模，确保结果非负。
    * 💡 **学习笔记**：在模运算中，负数结果需调整为正数。

### ✨ 解题技巧总结
<summary_best_practices>
通过对本题及类似问题的分析，我总结了以下一些通用的解题技巧：
</summary_best_practices>
-   **技巧1：公式拆分**：将复杂操作拆分为独立变量，分别维护。
-   **技巧2：DFS序应用**：将树上问题转化为序列问题。
-   **技巧3：树状数组/线段树选择**：根据操作类型（区间修改、单点查询）选择高效数据结构。
-   **技巧4：边界处理**：注意子树区间边界和负数取模。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合自优质题解思路，使用两个树状数组分别维护常数项和深度系数。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int N = 3e5 + 10, mod = 1e9 + 7;

    int n, l[N], r[N], dep[N];
    vector<int> g[N];

    struct BIT {
        ll c[N];
        void update(int x, ll v) {
            for (; x <= n; x += x & -x) 
                c[x] = (c[x] + v) % mod;
        }
        ll query(int x) {
            ll res = 0;
            for (; x; x -= x & -x)
                res = (res + c[x]) % mod;
            return res;
        }
        void add(int l, int r, ll v) {
            update(l, v);
            update(r + 1, -v);
        }
    } bit1, bit2; // bit1维护常数项，bit2维护k

    void dfs(int u, int d) {
        static int cnt = 0;
        l[u] = ++cnt;
        dep[u] = d;
        for (int v : g[u]) 
            dfs(v, d + 1);
        r[u] = cnt;
    }

    int main() {
        scanf("%d", &n);
        for (int i = 2, fa; i <= n; i++) {
            scanf("%d", &fa);
            g[fa].push_back(i);
        }
        dfs(1, 1);
        int q; scanf("%d", &q);
        while (q--) {
            int op, v; scanf("%d%d", &op, &v);
            if (op == 1) {
                ll x, k; scanf("%lld%lld", &x, &k);
                ll val1 = (x + 1LL * dep[v] * k) % mod;
                bit1.add(l[v], r[v], val1);
                bit2.add(l[v], r[v], k);
            } else {
                ll a = bit1.query(l[v]);
                ll b = bit2.query(l[v]);
                ll ans = (a - 1LL * dep[v] * b) % mod;
                printf("%lld\n", (ans % mod + mod) % mod);
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 该代码首先通过DFS预处理每个节点的深度和子树区间（dfs序）。使用两个树状数组分别处理常数项（x+dep[v]*k）和系数项（k）。操作1时在子树区间上添加值，操作2时查询节点值 = bit1的值 - dep[v] * bit2的值，并调整负数模。

---
<code_intro_selected>
接下来，我们将逐一剖析筛选出的优质题解中，最能体现核心逻辑的C++实现片段：
</code_intro_selected>

**题解一：(来源：nekko)**
* **亮点**：代码简洁，树状数组封装良好。
* **核心代码片段**：
    ```cpp
    struct BIT {
        ll sum[N];
        void addsig(int x, ll y) {
            for( ; x <= n ; x += x & -x)
                (sum[x] += y) %= mod;
        }
        void add(int l, int r, ll s) {
            addsig(l, s), addsig(r + 1, -s);
        }
        ll ask(int x) {
            ll r = 0;
            for( ; x ; x -= x & -x)
                (r += sum[x]) %= mod;
            return r;
        }
    } a, b;
    ```
* **代码解读**：
    > 此代码定义了树状数组结构体，支持区间加（add）和单点查询（ask）。a和b分别对应常数项和系数项。区间加通过两次单点加实现（差分）。
* 💡 **学习笔记**：树状数组的差分实现是区间修改的常用技巧。

**题解二：(来源：Pengzt)**
* **亮点**：使用结构体封装两个树状数组，代码复用性高。
* **核心代码片段**：
    ```cpp
    struct BIT {
        ll c[N];
        void upd(int l, int r, ll v) {
            auto add = [&](int x, ll v) {
                for (; x <= n; x += x & -x) c[x] = (c[x] + v) % mod;
            };
            add(l, v), add(r + 1, -v);
        }
        ll qry(int x) {
            ll res = 0;
            for (; x; x -= x & -x) res = (res + c[x]) % mod;
            return res;
        }
    } t1, t2;
    ```
* **代码解读**：
    > 与题解一类似，但使用了lambda表达式简化代码，体现了C++11的特性。t1和t2分别维护两个部分。
* 💡 **学习笔记**：合理使用lambda可以提升代码可读性。

**题解三：(来源：shadowice1984)**
* **亮点**：离线处理确保只计算祖先节点的影响。
* **核心代码片段**：
    ```cpp
    void dfs(int u) {
        for (auto &q: queries[u]) 
            ta1.update(q.t, q.x + dep[u] * q.k), 
            ta2.update(q.t, q.k);
        for (auto q: asks[u]) 
            ans[q.idx] = ta1.query(q.idx) - dep[u] * ta2.query(q.idx);
        for (int v: g[u]) dfs(v);
        for (auto &q: queries[u]) 
            ta1.update(q.t, -(q.x + dep[u] * q.k)), 
            ta2.update(q.t, -q.k);
    }
    ```
* **代码解读**：
    > 在DFS过程中，进入节点时添加影响，离开时移除。这样查询时只考虑祖先节点。ta1和ta2维护两个部分。
* 💡 **学习笔记**：离线处理有时可以简化问题，但实现复杂度较高。

-----

## 5. 算法可视化：像素动画演示

<visualization_intro>
为了更直观地理解树状数组如何维护树上操作，我设计了一个像素风格的动画演示方案：
</visualization_intro>

  * **动画演示主题**：`树状数组的深度影响`

  * **核心演示内容**：展示操作1如何影响两个树状数组，以及查询时如何组合结果。

  * **设计思路简述**：
    - 采用8位像素风格，左侧显示树结构（像素节点），右侧并排两个网格（代表两个树状数组）
    - 操作1时，子树区间高亮，添加颜色块（常数项用蓝色，系数项用红色）
    - 查询时，节点闪烁，显示公式计算过程（A_val - dep[v]*B_val）

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        * 左侧：FC风格树结构，节点用不同颜色像素块表示，深度标记在下方
        * 右侧：两个16×16网格，分别标记"常数项"和"系数项"
        * 控制面板：开始/暂停、单步执行、速度滑块

    2.  **操作1演示**：
        * 用户选择节点v（如节点3），输入x=5, k=1
        * 动画效果：
            - v的子树在树结构中高亮（黄色边框）
            - 常数项网格：区间[l[v], r[v]]填充蓝色（值=x+dep[v]*k=8）
            - 系数项网格：相同区间填充红色（值=k=1）
            - 播放"叮"音效（8-bit风格）

    3.  **查询操作演示**：
        * 用户选择查询节点u（如节点5）
        * 动画效果：
            - 节点u在树结构中闪烁
            - 两个网格中u的位置高亮
            - 显示公式：结果 = 常数项值(8) - 深度(3)*系数项值(1) = 5
            - 播放"成功"音效（上扬音调）

    4.  **自动演示模式**：
        * 点击"AI演示"：自动执行预设操作序列
        * 类似"贪吃蛇AI"逐步展示算法流程
        * 每完成一个操作，播放相应音效

    5.  **数据结构可视化**：
        * 树状数组更新时，显示二进制索引的路径（发光效果）
        * 深度变化时，颜色深浅渐变（深红=高系数，浅蓝=低常数）

  * **技术实现考量**：
    - 使用HTML5 Canvas绘制树和网格
    - 颜色方案：常数项（蓝色系），系数项（红色系）
    - 音效：Web Audio API生成8-bit音效
    - 单文件实现，轻量易用

<visualization_conclusion>
通过这个融合了像素艺术和复古游戏元素的动画，我们能直观看到树状数组如何维护树上操作，理解深度系数的影响。
</visualization_conclusion>

-----

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考该算法/技巧的适用范围和变形应用：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 类似问题：子树区间修改（加等差数列）、路径查询
    - 核心技巧：DFS序、树状数组/线段树、公式拆分
    - 适用场景：需要维护子树聚合信息且操作与深度相关的问题

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P3384** - 树链剖分模板
        * 🗣️ **推荐理由**：练习树链剖分实现路径修改和子树修改，巩固DFS序应用。
    2.  **洛谷 P3373** - 线段树2
        * 🗣️ **推荐理由**：练习同时维护加法和乘法标记，与本题拆分思想相关。
    3.  **洛谷 P3178** - 树上操作
        * 🗣️ **推荐理由**：子树修改和查询，与本题类似但更基础。

-----

## 7. 学习心得与经验分享

<insights_intro>
从题解中提炼出以下有价值的经验：
</insights_intro>

> **参考经验 (来自nekko)**："将公式拆分为(x+dep[v]*k)和-k两部分，是解决本题的关键突破点。"
>
> **点评**：这种拆分思想不仅适用于本题，也是处理复杂依赖关系的通用技巧。在实际编码中，明确变量职责（常数项 vs 系数项）能大幅提升代码可维护性。
>
> **参考经验 (来自Pengzt)**："使用结构体封装树状数组，减少重复代码。"
>
> **点评**：良好的封装提高代码复用性，这在竞赛中能节省宝贵时间。同时，注意负数取模的细节避免隐蔽错误。

<conclusion>
本次关于"On Changing Tree"的C++解题分析就到这里。记住，编程能力的提升在于持续学习、勤于思考和勇于实践。下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：201.81秒