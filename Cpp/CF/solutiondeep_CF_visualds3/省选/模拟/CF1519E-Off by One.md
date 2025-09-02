# 题目信息

# Off by One

## 题目描述

There are $ n $ points on an infinite plane. The $ i $ -th point has coordinates $ (x_i, y_i) $ such that $ x_i > 0 $ and $ y_i > 0 $ . The coordinates are not necessarily integer.

In one move you perform the following operations:

- choose two points $ a $ and $ b $ ( $ a \neq b $ );
- move point $ a $ from $ (x_a, y_a) $ to either $ (x_a + 1, y_a) $ or $ (x_a, y_a + 1) $ ;
- move point $ b $ from $ (x_b, y_b) $ to either $ (x_b + 1, y_b) $ or $ (x_b, y_b + 1) $ ;
- remove points $ a $ and $ b $ .

However, the move can only be performed if there exists a line that passes through the new coordinates of $ a $ , new coordinates of $ b $ and $ (0, 0) $ .

Otherwise, the move can't be performed and the points stay at their original coordinates $ (x_a, y_a) $ and $ (x_b, y_b) $ , respectively.

The numeration of points does not change after some points are removed. Once the points are removed, they can't be chosen in any later moves. Note that you have to move both points during the move, you can't leave them at their original coordinates.

What is the maximum number of moves you can perform? What are these moves?

If there are multiple answers, you can print any of them.

## 说明/提示

Here are the points and the moves for the ones that get chosen for the moves from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1519E/552d757ed4044221f43bfc2dbbc4063ed579283e.png)

## 样例 #1

### 输入

```
7
4 1 5 1
1 1 1 1
3 3 3 3
1 1 4 1
6 1 1 1
5 1 4 1
6 1 1 1```

### 输出

```
3
1 6
2 4
5 7```

## 样例 #2

### 输入

```
4
2 1 1 1
1 1 2 1
2 1 1 2
1 2 1 2```

### 输出

```
1
1 2```

## 样例 #3

### 输入

```
4
182 168 60 96
78 72 45 72
69 21 144 63
148 12 105 6```

### 输出

```
1
2 4```

# AI分析结果

---
# 💡 Kay的C++算法解析：Off by One 深入学习指南 💡

<introduction>
今天我们来一起分析“Off by One”这道C++编程题。这道题的核心在于将几何问题转化为图论模型，并通过贪心策略找到最大匹配。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`图论（无向图匹配）与贪心策略`

🗣️ **初步分析**：
解决“Off by One”的关键在于将几何问题转化为图论模型。简单来说，每个点移动后的两种可能斜率（向右或向上移动）可以看作图中的两个节点，原问题的点则对应连接这两个节点的边。我们的目标是在这张无向图中找到最多的边对，使得每对边共享至少一个公共节点（即匹配）。

- **题解思路**：所有优质题解均采用“图转化+DFS贪心匹配”的思路。将每个点的两种移动可能转化为图中的边，然后通过DFS遍历图，利用贪心策略（优先匹配子树内的边，剩余边由父节点处理）找到最大匹配。
- **核心难点**：如何将几何共线条件转化为图模型？如何通过DFS遍历处理树边与返祖边的匹配？
- **可视化设计**：采用8位像素风格，用不同颜色区分“斜率节点”和“原节点边”，动态展示DFS遍历过程（如边的高亮、匹配时的闪烁），关键步骤伴随“叮”的音效，完成匹配时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过对思路清晰度、代码规范性、算法有效性等维度的评估，以下题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：作者walk_alone (赞：6)**
* **点评**：此题解思路清晰，详细解释了“形式图”的构建过程（将点转化为边，斜率转化为节点），并通过DFS遍历处理树边与返祖边的匹配。代码注释详尽，变量命名规范（如`norm`函数处理分数约分，`con`数组记录枢轴点匹配的边），边界处理严谨（如避免重边影响）。其贪心策略（子树内匹配，剩余边由父节点处理）是核心亮点，代码可直接用于竞赛，实践价值高。

**题解二：作者Mihari (赞：2)**
* **点评**：此题解简洁明了，将问题转化为“无向图最大边匹配”，并通过DFS遍历生成树，利用“子债父还”的贪心策略（子树内奇数边时由父边补足）实现匹配。代码结构工整（如`dfs`函数递归处理子树），关键逻辑（如`match`数组记录未匹配边）解释到位，适合快速理解核心思路。

**题解三：作者丛雨 (赞：2)**
* **点评**：此题解强调“联通块处理”，通过DFS遍历每个联通块，利用深度标记（`h`数组）区分树边与返祖边，贪心匹配时优先处理子树内的边。代码中`ans`数组记录各枢轴点的匹配边，逻辑清晰，适合学习如何处理多联通块的情况。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于模型转化与贪心匹配策略的设计。以下是关键步骤与应对策略：
</difficulty_intro>

1.  **关键点1：如何将几何共线条件转化为图模型？**
    * **分析**：两个点移动后与原点共线的条件是它们的斜率相等。每个点有两种移动可能（右或上），对应两个斜率值（如点`(x,y)`移动后可能为`(x+1,y)`或`(x,y+1)`，对应斜率`(x+1)/y`和`x/(y+1)`）。将这两个斜率视为图中的节点，原问题的点视为连接这两个节点的边。
    * 💡 **学习笔记**：几何问题转化为图论模型的关键是找到“等价条件”（如共线→斜率相等），并将原问题的操作转化为图的边。

2.  **关键点2：如何通过DFS遍历处理树边与返祖边的匹配？**
    * **分析**：在DFS生成树中，树边是遍历路径上的边，返祖边是连接当前节点与祖先的边。贪心策略为：优先匹配子树内的边（偶数边直接两两匹配），若子树内边数为奇数，则将剩余边与父边匹配（子债父还）。
    * 💡 **学习笔记**：DFS遍历能有效区分树边与返祖边，利用深度标记（`depth`数组）可简化匹配逻辑。

3.  **关键点3：如何保证匹配数最大？**
    * **分析**：每个联通块的最大匹配数为边数的一半（向下取整）。通过DFS贪心处理，每个子树最多剩余一条边由父节点处理，最终根节点可能剩余一条边（无法匹配），但整体接近理论最大值。
    * 💡 **学习笔记**：贪心策略的核心是“局部最优”（子树内匹配），最终整体达到全局最优。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题转化**：将几何条件转化为图论模型（如斜率→节点，点→边）。
- **DFS遍历**：利用DFS生成树区分树边与返祖边，简化匹配逻辑。
- **贪心匹配**：优先处理子树内的边，剩余边由父节点补足，确保最大匹配。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解的通用核心实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了walk_alone和Mihari的题解思路，采用形式图构建、DFS遍历和贪心匹配策略，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <cstdio>
    #include <algorithm>
    #include <map>
    #include <vector>
    using namespace std;

    typedef long long ll;
    ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }

    struct Frac {
        ll p, q;
        bool operator<(const Frac& b) const {
            return (long double)p / q < (long double)b.p / b.q;
        }
    };
    Frac norm(Frac a) { ll g = gcd(a.p, a.q); return {a.p / g, a.q / g}; }

    map<Frac, int> idMap;
    vector<int> con[500005]; // 记录枢轴点的匹配边
    int depth[500005];

    struct Edge { int to, id, next; } edges[2000005];
    int cnt, head[500005];
    void addEdge(int from, int to, int id) {
        edges[++cnt] = {to, id, head[from]};
        head[from] = cnt;
    }

    void dfs(int u, int fa) {
        depth[u] = depth[fa] + 1;
        int parentEdge = -1; // 记录与父节点的树边

        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to, eid = edges[i].id;
            if (!depth[v]) {
                dfs(v, u);
            } else {
                if (depth[v] > depth[u]) continue; // 非返祖边
                if (v == fa && parentEdge == -1) parentEdge = eid; // 树边
                else con[v].push_back(eid); // 返祖边给祖先
            }
        }

        if (fa) {
            if (con[u].size() % 2) con[u].push_back(parentEdge); // 奇数边，父边加入当前枢轴
            else con[fa].push_back(parentEdge); // 偶数边，父边给父节点枢轴
        }
    }

    int main() {
        int n, tot = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            ll x1, y1, x2, y2;
            scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
            Frac left = norm({y2 * (x1 + y1), x2 * y1});
            Frac up = norm({(y2 + x2) * y1, x1 * x2});
            if (!idMap[left]) idMap[left] = ++tot;
            if (!idMap[up]) idMap[up] = ++tot;
            addEdge(idMap[left], idMap[up], i);
            addEdge(idMap[up], idMap[left], i);
        }

        for (int i = 1; i <= tot; ++i)
            if (!depth[i]) dfs(i, 0);

        int ans = 0;
        for (int i = 1; i <= tot; ++i) ans += con[i].size() / 2;
        printf("%d\n", ans);

        for (int i = 1; i <= tot; ++i)
            for (int j = 0; j + 1 < con[i].size(); j += 2)
                printf("%d %d\n", con[i][j], con[i][j + 1]);

        return 0;
    }
    ```
* **代码解读概要**：
    该代码首先将每个点的两种移动可能转化为两个斜率（`left`和`up`），构建形式图（斜率为节点，原问题的点为边）。通过DFS遍历形式图，处理树边与返祖边的匹配（`con`数组记录各枢轴点的匹配边）。最后统计各枢轴点的匹配数，输出结果。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点与实现细节。
</code_intro_selected>

**题解一：作者walk_alone**
* **亮点**：形式图构建清晰，DFS中处理树边与返祖边的逻辑明确，`con`数组记录枢轴点匹配边，避免重复计算。
* **核心代码片段**：
    ```cpp
    void dfs(int place, int father) {
        int nownode = -1;
        depth[place] = depth[father] + 1;
        for (int i = headers[place]; i; i = que[i].next) {
            if (!depth[que[i].to]) dfs(que[i].to, place);
            else {
                if (depth[que[i].to] > depth[place]) continue;
                if (que[i].to == father && nownode == -1) nownode = que[i].id;
                else con[que[i].to].push_back(que[i].id);
            }
        }
        if (father) {
            if (con[place].size() & 1) con[place].push_back(nownode);
            else con[father].push_back(nownode);
        }
    }
    ```
* **代码解读**：
    `dfs`函数中，`depth`数组记录节点深度。遍历当前节点的所有边：若邻接节点未访问，递归处理子树；若邻接节点已访问且深度较小（返祖边），则将该边加入祖先的`con`数组。最后处理与父节点的树边（`nownode`），根据当前枢轴点的边数奇偶性决定是否将树边加入当前或父节点的`con`数组。
* 💡 **学习笔记**：通过深度标记区分树边与返祖边，利用奇偶性贪心匹配，是处理无向图匹配的经典技巧。

**题解二：作者Mihari**
* **亮点**：代码简洁，`match`数组记录未匹配的边，DFS递归处理子树，直接匹配剩余边。
* **核心代码片段**：
    ```cpp
    void dfs(int u) {
        vis[u] = 1;
        for (int i = tail[u], v, nde; ~i; i = e[i].nxt) {
            v = e[i].to, nde = e[i].id;
            e[i].to = e[i^1].to = 0; // 标记边已处理
            if (v) {
                if (!vis[v]) dfs(v);
                if (match[v]) {
                    ans.push_back({nde, match[v]});
                    match[v] = 0;
                } else if (match[u]) {
                    ans.push_back({nde, match[u]});
                    match[u] = 0;
                } else match[u] = nde;
            }
        }
    }
    ```
* **代码解读**：
    `dfs`函数中，`vis`数组标记已访问节点。遍历当前节点的所有边，递归处理子树后，若子树有未匹配的边（`match[v]`非零），则与当前边匹配；否则将当前边暂存到`match[u]`中。最终`ans`数组保存所有匹配对。
* 💡 **学习笔记**：`match`数组暂存未匹配边，递归处理子树后回溯匹配，是贪心策略的简洁实现。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解形式图构建与匹配过程，我们设计一个“像素斜率探险”动画，以8位复古风格展示算法执行流程。
</visualization_intro>

  * **动画演示主题**：`像素斜率探险——在斜率森林中寻找匹配对`

  * **核心演示内容**：
    展示形式图的构建（原问题的点转化为边，斜率转化为节点），DFS遍历过程（树边与返祖边的区分），以及贪心匹配时的边配对（如子树内的边两两匹配，剩余边与父边匹配）。

  * **设计思路简述**：
    采用8位像素风格（FC红白机色调），用不同颜色区分斜率节点（蓝色方块）和原节点边（黄色线条）。DFS遍历时用绿色箭头标记当前路径，返祖边用红色虚线。匹配时边闪烁并伴随“叮”的音效，完成所有匹配后播放胜利音效（如《超级玛丽》的通关音乐）。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕左侧显示输入点（像素点），右侧显示形式图（蓝色斜率节点+黄色边）。
        - 控制面板包含“开始”、“单步”、“重置”按钮和速度滑块（1-10倍速）。

    2.  **形式图构建**：
        - 每个输入点（像素点）向右/上移动，生成两个斜率（蓝色节点弹出），并在两节点间绘制黄色边（原问题的点）。

    3.  **DFS遍历**：
        - 绿色箭头从根节点出发，遍历形式图（树边用绿色线条，返祖边用红色虚线）。
        - 当前处理节点闪烁（如蓝色→白色循环），深度用数字标注（如根节点深度1，子节点深度2）。

    4.  **贪心匹配**：
        - 子树内的边两两匹配时，黄色边变为紫色并闪烁，伴随“叮”音效。
        - 若子树内边数为奇数，剩余边与父边匹配（父边变为紫色，音效“叮”）。

    5.  **结果展示**：
        - 所有匹配对显示在屏幕下方（如“匹配对：1-6，2-4，5-7”）。
        - 完成所有匹配后，播放胜利音效，屏幕中央弹出“成功！匹配数：3”。

  * **旁白提示**：
    - （形式图构建时）“看！每个点移动后的两个斜率变成了蓝色方块，它们之间的黄线就是原问题的点哦～”
    - （DFS遍历时）“绿色箭头在遍历图，遇到未访问的节点就继续前进，这是树边；遇到已访问的祖先节点，这是返祖边～”
    - （匹配时）“子树里的黄线两两配对，变紫啦！如果剩一条，就找父节点的黄线帮忙配对～”

<visualization_conclusion>
通过这样的像素动画，我们能清晰看到形式图的构建、DFS遍历和贪心匹配的全过程，轻松理解算法的核心逻辑。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的图论转化与贪心匹配后，我们可以尝试以下拓展问题，巩固相关技巧：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    本题的核心是“问题转化+贪心匹配”，类似思路可用于：
    - 二分图最大匹配（如P3386）：将问题转化为二分图，用匈牙利算法求解。
    - 树的最大匹配（如P1355）：通过DFS遍历树，贪心匹配子节点。
    - 无向图边覆盖（如P2763）：转化为匹配问题，求最小边覆盖。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P3386** - `二分图最大匹配`
          * 🗣️ **推荐理由**：直接应用二分图匹配算法，巩固“匹配”概念。
    2.  **洛谷 P1355** - `神秘大三角`
          * 🗣️ **推荐理由**：涉及树的最大匹配，与本题的贪心策略类似。
    3.  **洛谷 P2763** - `试题库问题`
          * 🗣️ **推荐理由**：将问题转化为二分图匹配，训练模型转化能力。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，以下是值得借鉴的内容：
</insights_intro>

> **参考经验 (来自作者walk_alone)**：“我在解决这个问题时，最初在处理返祖边时卡了很久，后来通过打印`depth`数组和`con`数组的中间值，才定位到问题。这让我意识到，调试时输出关键变量的状态非常重要。”

> **点评**：作者的经验提醒我们，在处理复杂图论问题时，打印关键变量（如`depth`、`con`数组）的中间状态，能有效定位逻辑错误。这是调试图论问题的实用技巧。

---

<conclusion>
本次关于“Off by One”的C++解题分析就到这里。通过模型转化、DFS遍历和贪心匹配，我们解决了几何共线条件下的最大匹配问题。希望这份指南能帮助大家掌握图论模型转化与贪心策略的应用，在编程之路上更进一步！💪
</conclusion>

---
处理用时：139.78秒