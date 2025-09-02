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



---
# 💡 Kay的C++算法解析：On Changing Tree 深入学习指南 💡

<introduction>
今天我们来一起分析“On Changing Tree”这道C++编程题。这道题涉及树结构上的动态修改与查询，需要巧妙的数学分解和高效的数据结构支持。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`树结构的差分与数据结构应用`（属于“编程技巧应用”）

🗣️ **初步分析**：
解决“On Changing Tree”的关键在于将复杂的增量操作拆解为可维护的形式，并利用树的DFS序将子树转化为连续区间，通过树状数组或线段树高效处理区间修改和单点查询。

简单来说，我们可以把每个修改操作的增量拆分成两部分：一部分是与节点深度相关的项（$-k \cdot \text{dep}_u$），另一部分是常数项（$x + k \cdot \text{dep}_v$）。这样，我们可以用两个树状数组分别维护这两部分的和，查询时通过公式计算即可得到结果。

- **题解思路**：所有优质题解均围绕“增量分解”展开，利用DFS序将子树转化为区间，通过树状数组或线段树维护区间和。例如，nekko的题解直接用两个树状数组分别维护$k$的和与$(x + k \cdot \text{dep}_v)$的和，查询时通过公式计算。
- **核心难点**：如何将增量$x - (i \cdot k)$（$i$为节点到$v$的距离）转化为与深度相关的线性表达式，并找到合适的数据结构维护。
- **可视化设计**：动画将展示DFS序的生成过程（节点按遍历顺序排列成连续区间）、修改操作时的区间覆盖（用不同颜色标记修改范围），以及查询时两部分和的计算过程（高亮当前节点的深度和两个树状数组的查询值）。采用8位像素风格，节点用方块表示，修改时伴随“叮”的音效，查询时显示计算步骤。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下题解因逻辑简洁、实现高效被选为优质参考：
</eval_intro>

**题解一：作者 nekko（赞：8）**
* **点评**：此题解思路极其清晰，通过数学推导将增量拆分为两部分，并用两个树状数组维护。代码风格简洁规范（如变量名`a`、`b`分别对应两部分的树状数组），边界处理严谨（取模操作贯穿始终）。算法时间复杂度为$O(q \log n)$，非常适合竞赛场景。其核心亮点是对增量的巧妙分解，将复杂问题转化为基础的数据结构操作。

**题解二：作者 Pengzt（赞：3）**
* **点评**：此题解同样采用树状数组，但代码更紧凑。通过DFS序预处理子树区间，直接维护两部分的和，查询时公式清晰。代码中使用`eb`（emplace_back）优化容器插入，输入输出采用`ios::sync_with_stdio(false)`加速，体现了竞赛编程的实用技巧。

**题解三：作者 CRTL_xzh2009（赞：0）**
* **点评**：此题解用线段树实现，思路与树状数组一致，但线段树的实现更详细。适合对线段树更熟悉的学习者理解。代码中`PushDown`和`UpDate`函数逻辑清晰，注释较少但变量名直观（如`lz`表示懒标记）。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何拆分增量表达式？**
    * **分析**：操作1的增量是$x - (i \cdot k)$，其中$i$是节点到$v$的距离（即$\text{dep}_u - \text{dep}_v$）。将其展开为$x - k \cdot \text{dep}_u + k \cdot \text{dep}_v$，可拆分为两部分：$-k \cdot \text{dep}_u$（与节点深度相关）和$x + k \cdot \text{dep}_v$（常数项）。这样，两部分可分别用树状数组维护。
    * 💡 **学习笔记**：复杂增量的拆分是解决此类问题的关键，需观察表达式是否能分解为与节点属性（如深度）相关的项和常数项。

2.  **关键点2：如何将子树转化为连续区间？**
    * **分析**：通过DFS遍历树，记录每个节点的进入时间（`dfn`）和子树的最大时间（`r`），子树对应的区间即为`[dfn[v], r[v]]`。这样，子树操作可转化为区间操作，便于树状数组或线段树处理。
    * 💡 **学习笔记**：DFS序是处理子树问题的常用技巧，能将树的非线性结构转化为线性数组。

3.  **关键点3：如何选择数据结构？**
    * **分析**：本题需要区间修改和单点查询，树状数组（BIT）和线段树均适用。树状数组代码更简洁，常数更小；线段树灵活性更高（如支持更多操作）。本题选择树状数组更高效。
    * 💡 **学习笔记**：根据操作类型选择数据结构，区间修改+单点查询优先考虑树状数组。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题分解**：将复杂增量拆分为与节点属性相关的项和常数项，分别维护。
- **DFS序应用**：利用DFS序将子树转化为连续区间，简化子树操作。
- **取模处理**：所有运算需及时取模，避免溢出（尤其是负数情况）。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，先看一个能够完整解决本题的通用核心C++实现参考（综合nekko和Pengzt的思路，使用树状数组）。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个优质题解的思路，使用树状数组维护两部分和，代码简洁高效，适合竞赛场景。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int N = 3e5 + 10, mod = 1e9 + 7;

    int n, l[N], r[N], dep[N];
    vector<int> g[N];

    struct BIT {
        ll sum[N];
        void addsig(int x, ll y) {
            for (; x <= n; x += x & -x)
                (sum[x] += y) %= mod;
        }
        void add(int l, int r, ll s) {
            addsig(l, s);
            addsig(r + 1, -s);
        }
        ll ask(int x) {
            ll res = 0;
            for (; x; x -= x & -x)
                (res += sum[x]) %= mod;
            return res;
        }
    } a, b; // a维护k的和，b维护(x + k*dep[v])的和

    void dfs(int u) {
        static int tot = 0;
        l[u] = ++tot;
        for (int v : g[u]) {
            dep[v] = dep[u] + 1;
            dfs(v);
        }
        r[u] = tot;
    }

    int main() {
        scanf("%d", &n);
        for (int i = 2, fa; i <= n; ++i) {
            scanf("%d", &fa);
            g[fa].push_back(i);
        }
        dep[1] = 0;
        dfs(1);
        int q; scanf("%d", &q);
        while (q--) {
            int op, v, x, k;
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d%d", &v, &x, &k);
                a.add(l[v], r[v], k % mod);
                b.add(l[v], r[v], (x + 1ll * dep[v] * k % mod) % mod);
            } else {
                scanf("%d", &v);
                ll qa = a.ask(l[v]);
                ll qb = b.ask(l[v]);
                ll ans = (qb - 1ll * dep[v] * qa % mod + mod) % mod;
                printf("%lld\n", ans);
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先通过DFS预处理每个节点的进入时间`l[u]`、子树最大时间`r[u]`和深度`dep[u]`。两个树状数组`a`和`b`分别维护$k$的和与$(x + k \cdot \text{dep}_v)$的和。操作1时，对区间`[l[v], r[v]]`进行区间加；操作2时，查询单点`l[v]`的两个和，通过公式计算结果。

---
<code_intro_selected>
接下来，剖析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：作者 nekko**
* **亮点**：代码简洁，直接通过两个树状数组维护两部分和，取模操作严谨。
* **核心代码片段**：
    ```cpp
    struct BIT {
        ll sum[N];
        void addsig(int x, ll y) {
            for (; x <= n; x += x & -x)
                (sum[x] += y) %= mod;
        }
        void add(int l, int r, ll s) {
            addsig(l, s);
            addsig(r + 1, -s);
        }
        ll ask(int x) {
            ll res = 0;
            for (; x; x -= x & -x)
                (res += sum[x]) %= mod;
            return res;
        }
    } a, b;

    // 操作1处理
    a.add(l[v], r[v], k % mod);
    b.add(l[v], r[v], (x + 1ll * dep[v] * k % mod) % mod);

    // 操作2查询
    ll qa = a.ask(l[v]);
    ll qb = b.ask(l[v]);
    ll ans = (qb - 1ll * dep[v] * qa % mod + mod) % mod;
    ```
* **代码解读**：
    > `BIT`结构体实现了树状数组的区间加和单点查询。`add`函数通过差分实现区间加（在`l`处加`s`，`r+1`处减`s`）。操作1时，树状数组`a`维护$k$的和（区间加$k$），`b`维护$(x + k \cdot \text{dep}_v)$的和（区间加该值）。查询时，`qa`是$k$的和，`qb`是常数项的和，结果为`qb - dep[v] * qa`（取模后）。
* 💡 **学习笔记**：树状数组的区间加操作通过差分实现，单点查询时累加前缀和即可。

**题解二：作者 Pengzt**
* **亮点**：代码紧凑，输入输出优化（`ios::sync_with_stdio(false)`），适合竞赛。
* **核心代码片段**：
    ```cpp
    struct BIT {
        int v[300010];
        void add(int x, int y) {
            for (; x <= n; x += x & -x) v[x] = (v[x] + y) % mod;
        }
        int ask(int x) {
            int res = 0;
            for (; x; x -= x & -x) res = (res + v[x]) % mod;
            return res;
        }
        void upd(int l, int r, int v) { add(l, v), add(r + 1, -v); };
    } t1, t2;

    // 操作1处理
    t1.upd(l, r, k);
    t2.upd(l, r, (dep[v] * 1ll * k + x) % mod);

    // 操作2查询
    cout << (t2.ask(dfn[v]) - t1.ask(dfn[v]) * 1ll * dep[v] % mod + 2 * mod) % mod << "\n";
    ```
* **代码解读**：
    > `BIT`结构体的`upd`函数直接实现区间加。操作1时，`t1`维护$k$的和，`t2`维护$(x + k \cdot \text{dep}_v)$的和。查询时，`t2.ask`得到常数项和，`t1.ask`得到$k$的和，结果通过公式计算。
* 💡 **学习笔记**：输入输出优化能显著提升竞赛代码的效率，尤其是处理大数据量时。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“增量分解+树状数组”的工作流程，我们设计了一个8位像素风格的动画演示，帮助大家“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素树的修改与查询之旅`

  * **核心演示内容**：展示DFS序的生成、子树区间的标记、树状数组的区间加操作，以及查询时的两部分和计算。

  * **设计思路简述**：采用FC红白机风格的像素画面（8色调色板），节点用彩色方块表示，DFS序用数字标注。修改操作时，子树区间用金色边框高亮，树状数组的更新过程用箭头动画表示。查询时，显示当前节点的深度和两个树状数组的查询值，最终结果用绿色数字弹出。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧显示树结构（节点用圆形像素块，根节点为红色，子节点颜色渐变），右侧显示DFS序数组（每个位置对应一个节点的`dfn`值）。
          * 控制面板包含“单步”“自动播放”“重置”按钮和速度滑块（1-10倍速）。

    2.  **DFS序生成**：
          * 从根节点开始DFS遍历，每访问一个节点，右侧数组对应位置显示`dfn`值（如根节点`dfn=1`，子节点依次递增），伴随“滴答”音效。

    3.  **操作1演示（修改）**：
          * 输入操作1的参数（如`v=1, x=2, k=1`），动画高亮节点`v`及其子树（用黄色闪光）。
          * 右侧数组中，`[l[v], r[v]]`区间用蓝色覆盖，树状数组`a`和`b`的对应位置显示增量（`a`加`k`，`b`加`x + k*dep[v]`），伴随“刷”的音效。

    4.  **操作2演示（查询）**：
          * 输入操作2的参数（如`v=2`），动画高亮节点`v`，并显示其深度`dep[v]`。
          * 树状数组`a`和`b`分别查询`dfn[v]`位置的值（用放大镜动画），计算结果时显示公式`qb - dep[v]*qa`，最终结果用绿色弹出。

    5.  **音效与反馈**：
          * 修改操作：区间覆盖时播放“叮”音效；
          * 查询操作：结果弹出时播放“叮咚”音效；
          * 错误输入（如节点不存在）：播放“嗡”的短音效并提示。

  * **旁白提示**：
      * （DFS序生成时）“看！节点被访问的顺序就是DFS序，子树的节点在数组中是连续的哦～”
      * （修改操作时）“黄色区域是v的子树，树状数组a记录k的和，b记录x + k*dep[v]的和～”
      * （查询时）“查询结果等于b的和减去深度乘以a的和，就像解数学题一样！”

<visualization_conclusion>
通过这样的动画，我们能直观看到DFS序如何将子树转化为区间，树状数组如何高效处理修改，以及查询时的计算过程。像素风格的设计让学习过程更轻松有趣！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以将思路迁移到更多树结构问题中，以下是相关练习推荐：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的“增量分解+DFS序+树状数组”思路可用于处理树的子树加权和、等差数列更新等问题。
      * 例如：处理“子树中每个节点加$a + i \cdot b$”（$i$为深度差）的问题，同样可拆分为常数项和与深度相关项和，用树状数组维护。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P3178** - `[HAOI2015]树上操作`
          * 🗣️ **推荐理由**：本题要求子树加和路径查询，需结合DFS序和树状数组，与本题思路类似，可巩固区间操作技巧。
    2.  **洛谷 P4514** - `上帝造题的七分钟`
          * 🗣️ **推荐理由**：本题涉及二维区间修改和查询，虽然维度不同，但“分解操作+数据结构”的思想与本题一致，适合拓展思维。
    3.  **洛谷 P2486** - `[SDOI2011]染色`
          * 🗣️ **推荐理由**：本题需处理路径修改和查询，可尝试用树链剖分实现，与本题的DFS序思想互补。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如：
</insights_intro>

> **参考经验 (来自作者 nekko)**：“一开始没意识到增量可以拆分成两部分，走了很多弯路。后来发现将$x - (dep_u - dep_v)k$展开后，刚好能分离出与$u$无关的项和与$u$深度相关的项，这才想到用两个树状数组。”

> **点评**：这位作者的经验提醒我们，遇到复杂增量时，先尝试数学推导，观察是否能分解为可维护的形式。这是解决此类问题的关键步骤！

---

<conclusion>
本次关于“On Changing Tree”的C++解题分析就到这里。希望这份学习指南能帮助大家掌握树结构的差分技巧和数据结构的应用。记住，多动手推导和调试，才能真正理解算法的核心！下次我们再一起探索新的编程挑战！💪
</conclusion>

---

---
处理用时：165.26秒