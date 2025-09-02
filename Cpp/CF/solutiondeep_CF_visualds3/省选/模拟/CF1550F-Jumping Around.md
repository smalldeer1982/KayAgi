# 题目信息

# Jumping Around

## 题目描述

There is an infinite pond that can be represented with a number line. There are $ n $ rocks in the pond, numbered from $ 1 $ to $ n $ . The $ i $ -th rock is located at an integer coordinate $ a_i $ . The coordinates of the rocks are pairwise distinct. The rocks are numbered in the increasing order of the coordinate, so $ a_1 < a_2 < \dots < a_n $ .

A robot frog sits on the rock number $ s $ . The frog is programmable. It has a base jumping distance parameter $ d $ . There also is a setting for the jumping distance range. If the jumping distance range is set to some integer $ k $ , then the frog can jump from some rock to any rock at a distance from $ d - k $ to $ d + k $ inclusive in any direction. The distance between two rocks is an absolute difference between their coordinates.

You are assigned a task to implement a feature for the frog. Given two integers $ i $ and $ k $ determine if the frog can reach a rock number $ i $ from a rock number $ s $ performing a sequence of jumps with the jumping distance range set to $ k $ . The sequence can be arbitrarily long or empty.

You will be given $ q $ testcases for that feature, the $ j $ -th testcase consists of two integers $ i $ and $ k $ . Print "Yes" if the $ i $ -th rock is reachable and "No" otherwise.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", "Yes" and 'YES"' will be recognized as a positive answer).

## 说明/提示

Explanation of the first example:

In the first testcase the destination rock is the same as the starting rock, thus no jumps are required to reach it.

In the second testcase the frog can jump any distance in the range $ [5 - 2; 5 + 2] $ . Thus, it can reach rock number $ 5 $ (by jumping $ 7 $ to the right) and rock number $ 3 $ (by jumping $ 3 $ to the left). From rock number $ 3 $ it can reach rock number $ 2 $ (by jumping $ 5 $ to the left). From rock number $ 2 $ it can reach rock number $ 1 $ (by jumping $ 4 $ to the left). However, there is no way to reach rock number $ 7 $ .

In the third testcase the frog can jump any distance in the range $ [5 - 3; 5 + 3] $ . Thus, it can reach rock number $ 7 $ by jumping to rock $ 5 $ first and to $ 7 $ afterwards.

The fourth testcase is shown in the explanation for the second testcase.

## 样例 #1

### 输入

```
7 4 4 5
1 5 10 13 20 22 28
4 1
7 2
7 3
3 2```

### 输出

```
Yes
No
Yes
Yes```

## 样例 #2

### 输入

```
10 8 6 11
1 2 4 7 8 9 11 13 19 20
2 13
5 8
8 1
6 15
1 15
2 7
7 6
8 9```

### 输出

```
Yes
Yes
No
Yes
Yes
Yes
Yes
Yes```

## 样例 #3

### 输入

```
6 9 6 6
1 2 4 9 18 19
2 17
1 18
5 4
2 11
5 17
6 8
4 3
3 3
6 6```

### 输出

```
Yes
Yes
Yes
Yes
Yes
Yes
No
No
Yes```

## 样例 #4

### 输入

```
4 1 1 10
1 8 10 19
2 1```

### 输出

```
Yes```

# AI分析结果

---
# 💡 Kay的C++算法解析：Jumping Around 深入学习指南 💡

<introduction>
今天我们来一起分析“Jumping Around”这道C++编程题。这道题的关键在于理解如何通过图论中的最小生成树（MST）思想，解决机器人青蛙的跳跃可达性问题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：图论（最小生成树MST，Boruvka算法）

🗣️ **初步分析**：
解决“Jumping Around”的关键在于将跳跃问题转化为图论中的最小瓶颈路问题。简单来说，每块石头可以看作图中的一个节点，两块石头之间的“跳跃难度”（即所需的最小k值）是它们的边权，定义为 \( w_{i,j} = \left| |a_i - a_j| - d \right| \)。我们需要判断是否存在一条从起点s到目标i的路径，使得路径上的最大边权不超过给定的k。根据图论中的经典结论，这个最大边权的最小值等于最小生成树（MST）中s到i路径上的最大边权。

由于边数是 \( O(n^2) \)，普通MST算法（如Kruskal、Prim）无法处理，因此需要使用更高效的**Boruvka算法**。Boruvka算法的核心是每轮为每个连通块找到连向其他连通块的最小边，合并连通块，直到所有节点连通。这一过程仅需 \( O(\log n) \) 轮，每轮通过二分查找快速定位最小边。

可视化设计上，我们将采用8位像素风格，用不同颜色的方块表示连通块，通过动画展示连通块合并过程（如闪烁的边连接两个块），并在关键步骤（如选择最小边、合并连通块）添加“叮”的音效。控制面板支持单步执行和自动播放，帮助学习者直观看到MST的构建过程。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑清晰、实现高效被选为优质参考（≥4星）：
</eval_intro>

**题解一：作者Cry_For_theMoon**
* **点评**：此题解深入分析了问题的单调性和图论模型，明确将问题转化为MST的最小瓶颈路问题。代码使用Boruvka算法，通过维护两个有序集合（升序和降序set）快速查找每个连通块的最小边，逻辑严谨。变量命名（如`nxt`、`gnxt`）清晰，边界处理（如删除/恢复连通块节点）细致，是Boruvka算法的典型实现，适合学习MST的构建技巧。

**题解二：作者Saliеri（做法三）**
* **点评**：此题解提出分治求MST的超集，通过递归分治和双指针技巧减少边数，代码简洁高效。核心逻辑（如`Div`函数递归分割区间并连接左右部分的最小边）巧妙，避免了直接处理所有边，时间复杂度优化到 \( O(n \log n) \)，是思路创新的亮点。

**题解三：作者Purslane**
* **点评**：此题解基于Boruvka算法，通过维护左右指针（`l`、`r`）快速定位每个节点的最近可达点，代码结构清晰。`init`函数预处理连通块边界，`update`函数动态更新最小边，充分体现了Boruvka算法的核心思想，适合理解连通块合并的具体过程。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下核心难点。结合优质题解的共性，提炼关键策略：
</difficulty_intro>

1.  **关键点1：如何高效构建完全图的MST？**
    * **分析**：普通MST算法无法处理 \( O(n^2) \) 条边，需利用Boruvka算法。Boruvka每轮为每个连通块找到连向其他块的最小边（通过二分查找最近点），合并后减少连通块数量。优质题解通过维护有序集合（如set）快速查找 \( a_i \pm d \) 附近的点，确保每轮操作的时间复杂度为 \( O(n \log n) \)。
    * 💡 **学习笔记**：Boruvka算法适合处理完全图或边数极大的MST问题，核心是快速找到每个连通块的最小边。

2.  **关键点2：如何确定路径的最大边权？**
    * **分析**：MST中任意两点的路径是唯一的，且路径上的最大边权即为该两点的最小瓶颈路。优质题解通过DFS遍历MST，预处理每个节点到起点s的路径最大边权（如`dep`数组），实现O(1)查询。
    * 💡 **学习笔记**：预处理MST的路径最大边权是解决此类可达性问题的关键。

3.  **关键点3：如何选择数据结构优化查找？**
    * **分析**：为快速找到 \( a_i \pm d \) 附近的点，优质题解使用有序集合（set）或双指针。例如，Cry_For_theMoon维护两个set（升序和降序），通过`lower_bound`快速定位最近点；Saliеri的分治做法通过双指针遍历区间，减少查找时间。
    * 💡 **学习笔记**：有序数据结构（如set）和双指针是处理区间查找问题的常用优化手段。

### ✨ 解题技巧总结
- **问题转化**：将跳跃可达性问题转化为图论中的最小瓶颈路问题，利用MST的性质简化求解。
- **Boruvka算法**：处理完全图MST时，通过每轮合并连通块的最小边，避免枚举所有边。
- **预处理优化**：DFS遍历MST预处理路径最大边权，实现高效查询。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，基于Boruvka算法构建MST，并预处理路径最大边权。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Cry_For_theMoon和Purslane的思路，使用Boruvka算法构建MST，并通过DFS预处理每个节点的最大边权。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int MAXN = 2e5 + 10;

    int n, q, s, d;
    int a[MAXN], fa[MAXN], dep[MAXN];
    vector<pair<int, int>> g[MAXN]; // 邻接表存MST，存储（邻点，边权）

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void dfs(int u, int parent, int max_w) {
        dep[u] = max_w;
        for (auto &e : g[u]) {
            int v = e.first, w = e.second;
            if (v != parent) {
                dfs(v, u, max(max_w, w));
            }
        }
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);

        cin >> n >> q >> s >> d;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            fa[i] = i;
        }
        s--; // 转换为0-based索引

        set<int> plane; // 维护所有石头的坐标
        for (int i = 1; i <= n; ++i) plane.insert(a[i]);

        int cnt = n;
        while (cnt > 1) {
            vector<pair<int, int>> edges; // 每轮找到的最小边
            vector<int> compo[MAXN]; // 每个连通块的节点

            // 构建连通块
            for (int i = 1; i <= n; ++i) {
                compo[find(i)].push_back(i);
            }

            for (int i = 1; i <= n; ++i) {
                if (compo[i].empty()) continue;
                // 暂时删除当前连通块的节点，避免自环
                for (int x : compo[i]) plane.erase(a[x]);

                int min_u = -1, min_v = -1, min_w = INT_MAX;
                for (int x : compo[i]) {
                    // 查找a[x]+d附近的点
                    auto it = plane.lower_bound(a[x] + d);
                    if (it != plane.end()) {
                        int y = *it;
                        int w = abs(abs(a[x] - y) - d);
                        if (w < min_w) {
                            min_w = w;
                            min_u = x;
                            min_v = find(y); // 找到y所在连通块的根
                        }
                    }
                    if (it != plane.begin()) {
                        --it;
                        int y = *it;
                        int w = abs(abs(a[x] - y) - d);
                        if (w < min_w) {
                            min_w = w;
                            min_u = x;
                            min_v = find(y);
                        }
                    }
                    // 查找a[x]-d附近的点
                    it = plane.lower_bound(a[x] - d);
                    if (it != plane.end()) {
                        int y = *it;
                        int w = abs(abs(a[x] - y) - d);
                        if (w < min_w) {
                            min_w = w;
                            min_u = x;
                            min_v = find(y);
                        }
                    }
                    if (it != plane.begin()) {
                        --it;
                        int y = *it;
                        int w = abs(abs(a[x] - y) - d);
                        if (w < min_w) {
                            min_w = w;
                            min_u = x;
                            min_v = find(y);
                        }
                    }
                }

                // 恢复当前连通块的节点
                for (int x : compo[i]) plane.insert(a[x]);

                if (min_u != -1 && min_v != -1 && find(min_u) != find(min_v)) {
                    edges.emplace_back(min_u, min_v);
                    edges.emplace_back(min_v, min_u);
                    edges.emplace_back(min_w);
                }
            }

            // 合并连通块并构建MST
            for (auto &e : edges) {
                int u = e.first, v = e.second, w = e.third;
                if (find(u) != find(v)) {
                    fa[find(u)] = find(v);
                    g[u].emplace_back(v, w);
                    g[v].emplace_back(u, w);
                    cnt--;
                }
            }
        }

        // 预处理每个节点到s的路径最大边权
        dfs(s, -1, 0);

        // 处理查询
        while (q--) {
            int i, k;
            cin >> i >> k;
            i--; // 转换为0-based索引
            cout << (dep[i] <= k ? "Yes" : "No") << "\n";
        }

        return 0;
    }
    ```
* **代码解读概要**：代码首先读取输入并初始化并查集。通过Boruvka算法构建MST：每轮为每个连通块找到最小边（通过set快速查找附近点），合并连通块并记录边权。最后DFS遍历MST，预处理每个节点到起点s的路径最大边权，实现O(1)查询。

---
<code_intro_selected>
接下来，分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者Cry_For_theMoon（Boruvka算法）**
* **亮点**：使用两个set（升序和降序）快速查找附近点，确保每轮找到最小边的效率。
* **核心代码片段**：
    ```cpp
    // 处理每个连通块，查找最小边
    rep(i,1,n){
        int sz=group[i].size();
        rep(j,0,sz-1){
            s1.erase(a[group[i][j]]);
            s2.erase(a[group[i][j]]);
        }
        rep(j,0,sz-1){
            // 查找a[x]+d附近的点
            if(s1.lower_bound(a[group[i][j]]+d)!=s1.end()){
                ll v=*s1.lower_bound(a[group[i][j]]+d);
                // 更新最小边
            }
            // 类似处理a[x]-d附近的点
        }
        // 恢复set中的点
    }
    ```
* **代码解读**：`s1`和`s2`分别维护升序和降序的石头坐标。对于当前连通块的每个点，先删除其坐标（避免自环），然后查找`a[x]+d`和`a[x]-d`附近的点，计算边权并更新最小边。处理完后恢复坐标，确保下一轮的正确性。
* 💡 **学习笔记**：使用有序集合快速查找附近点是Boruvka算法的关键优化，避免了枚举所有边。

**题解二：作者Saliеri（分治求MST超集）**
* **亮点**：通过分治减少边数，仅保留可能构成MST的边，时间复杂度更优。
* **核心代码片段**：
    ```cpp
    void Div(int l, int r) {
        if (l != r) {
            int mid = l + r >> 1;
            Div(l, mid);
            for (int i = mid + 1; i <= r; ++i) lnk(a[i] - D, i, l);
            Div(mid + 1, r);
            for (int i = l; i <= mid; ++i) lnk(a[i] + D, i, mid + 1);
        }
        V.clear();
        for (int i = l; i <= r; ++i) V.push_back(a[i]);
    }
    ```
* **代码解读**：`Div`函数递归分割区间，连接左右部分的最小边（`lnk`函数处理具体连接）。通过分治，仅保留左右部分可能的最小边，构成MST的超集，后续用Kruskal算法构建MST。
* 💡 **学习笔记**：分治思想可有效减少边数，适用于完全图MST问题。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解Boruvka算法构建MST的过程，我们设计一个8位像素风格的动画，模拟石头的连通块合并和最小边选择。
</visualization_intro>

  * **动画演示主题**：`像素青蛙的跳跃冒险`
  * **核心演示内容**：展示连通块的合并过程（如不同颜色的方块代表不同连通块），高亮每轮选择的最小边（闪烁的箭头），并显示边权值。最终生成MST后，演示从s到目标i的路径最大边权。
  * **设计思路简述**：8位像素风格（如FC游戏画面）营造轻松氛围，颜色区分连通块（如红色块代表初始s所在块，蓝色、绿色等代表其他块）。关键操作（如选择最小边、合并块）伴随“叮”的音效，增强记忆点。

  * **动画帧步骤与交互关键点**：
    1.  **初始化场景**：屏幕上方显示石头坐标（像素方块排列成数轴），下方是控制面板（开始/暂停、单步、速度滑块）。背景播放8位风格BGM。
    2.  **初始连通块**：每个石头是一个独立的小块（1x1像素），颜色随机。起点s的块标记为红色。
    3.  **Boruvka轮次**：每轮开始时，所有连通块的块颜色变深（表示正在处理）。对于每个块，用白色箭头指向其找到的最小边（如从红色块指向最近的蓝色块），边权值显示在箭头旁。
    4.  **合并连通块**：选中最小边后，两个块合并为一个大的块（颜色继承较大的块），播放“叮”音效。合并后的块覆盖原两个块的位置。
    5.  **路径演示**：MST构建完成后，输入目标i，动画用黄色箭头高亮s到i的路径，路径上的边权值依次闪烁，最终显示最大边权是否≤k。
    6.  **交互控制**：支持单步执行（逐轮查看合并过程）、自动播放（调整速度滑块控制快慢）、重置（回到初始状态）。

  * **旁白提示**：
    - “现在是第1轮，每个连通块需要找到连向其他块的最小边。看！红色块找到了离它最近的蓝色块，边权是3！”
    - “合并成功！红色块和蓝色块现在属于同一个连通块，颜色变成红色（更大的块）。”
    - “查询时，路径上的最大边权是5，给定的k是6，所以可以到达！”

<visualization_conclusion>
通过这样的动画，我们能清晰看到连通块的合并过程和MST的构建逻辑，理解为何路径的最大边权是最小瓶颈路的关键。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的MST和Boruvka算法后，可尝试以下拓展练习，巩固相关技巧：
</similar_problems_intro>

  * **通用思路/技巧迁移**：本题的MST和最小瓶颈路思想可用于：
    - 网络规划：确定两个节点间的最大带宽限制。
    - 物流路径：找到运输过程中最大载重限制的路径。
    - 社交网络：确定两个用户间的最短信任链（信任值为边权，取路径最小最大值）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1967** - `货车运输`
        * 🗣️ **推荐理由**：经典最小瓶颈路问题，与本题思路一致，适合巩固MST和路径最大边权的预处理。
    2.  **洛谷 P2245** - `星际导航`
        * 🗣️ **推荐理由**：涉及完全图的MST构建，需用Boruvka算法，与本题的Boruvka实现高度相关。
    3.  **洛谷 P4180** - `[BJWC2010]严格次小生成树`
        * 🗣️ **推荐理由**：拓展MST的应用，学习如何处理次小生成树，深化对MST性质的理解。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验和优化技巧，以下是有价值的参考：
</insights_intro>

> **参考经验 (来自作者Cry_For_theMoon)**：“在实现Boruvka算法时，最初忘记处理连通块节点的删除和恢复，导致出现自环边。后来通过打印set的内容，发现连通块内的点被错误地选为边，添加了删除和恢复步骤后解决。”
>
> **点评**：这位作者的调试经验提醒我们，处理连通块时需注意临时移除当前块的节点，避免自环。打印中间变量（如set的内容）是定位此类错误的有效方法，这对处理图论问题中的边界条件非常重要。

-----

<conclusion>
本次关于“Jumping Around”的C++解题分析就到这里。希望这份指南能帮助大家理解MST和Boruvka算法的应用，掌握跳跃可达性问题的解决技巧。记住，多动手实践和调试是提升编程能力的关键！下次我们再一起探索新的算法挑战！💪
</conclusion>

---
处理用时：155.10秒