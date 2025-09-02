# 题目信息

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5
```

### 输出

```
3
2
3
6
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Kay and Snowflake 深入学习指南 💡

<introduction>
今天我们来一起分析“Kay and Snowflake”这道C++编程题。这道题的核心是找到树中每个节点的子树重心。本指南将帮助大家理解树的重心性质、掌握高效预处理方法，并通过可视化动画直观感受算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`树的重心性质与预处理` (属于「图论」分类)

🗣️ **初步分析**：
解决这道题的关键在于利用树的重心的特殊性质：以某个节点为根的子树，其重心要么是该节点本身，要么在其最大子树（重儿子）的子树的重心路径上。简单来说，树的重心就像树的“平衡点”，删除它后剩下的最大连通块不会超过原树大小的一半。

在本题中，我们需要预处理每个节点的子树重心，避免对每个查询单独计算（否则会超时）。核心思路是通过一次DFS遍历树，计算每个节点的子树大小，并利用其重儿子的重心向上调整，找到当前节点的重心。

- **题解思路对比**：多数题解采用DFS预处理，利用重儿子的重心向上跳的方法（如mrsrz、Ryan_等的题解），时间复杂度为O(n)；少数题解尝试数据结构或二分（如chen_z的重链剖分+二分），但主流高效方法仍是线性预处理。
- **核心算法流程**：DFS计算每个节点的子树大小和重儿子→对每个节点，从其重儿子的重心开始向上跳，直到满足“最大连通块≤原大小的一半”→记录该节点的重心。
- **可视化设计**：采用8位像素风动画，用不同颜色标记当前节点、重儿子、子树大小（像素块高度表示大小），向上跳的过程用箭头动画展示，关键步骤（如调整重心）伴随“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
经过评估（思路清晰性、代码规范性、算法有效性等），以下题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：作者mrsrz (赞25)**
* **点评**：此题解思路简洁高效，代码结构清晰。通过DFS预处理子树大小和重儿子，然后对每个节点从其重儿子的重心向上跳，找到满足条件的重心。代码中`sz[]`记录子树大小，`mx[]`记录最大子树大小，`rt[]`存储每个节点的重心，变量命名直观。算法复杂度为O(n)，适合竞赛场景。亮点在于利用“重儿子的重心向上跳”的贪心策略，避免重复计算。

**题解二：作者Ryan_ (赞11)**
* **点评**：此题解同样采用DFS预处理，代码逻辑直白。通过`size[]`记录子树大小，`ans[]`存储重心，关键步骤（如向上跳调整重心）注释清晰。代码中`while`循环处理向上跳的条件（`size[x]-size[now]`是否超过原大小的一半），边界处理严谨（如叶子节点直接设为自身）。实践价值高，适合初学者理解重心调整过程。

**题解三：作者くろねこ (赞9)**
* **点评**：此题解结合了树的重心性质和DFS回溯优化，代码中通过位运算（`son[res] << 1`）快速判断是否需要调整重心，提升效率。作者分享了调试经验（如暴力DFS超时的教训），对学习者有启发意义。代码结构规范，输入输出优化（读入/输出函数）值得学习。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们需要突破以下核心难点，并掌握对应的解题策略：
</difficulty_intro>

1.  **关键点1：如何高效预处理所有节点的重心？**
    * **分析**：直接对每个查询单独DFS计算会超时（时间复杂度O(nq)）。利用树的重心性质，通过一次DFS预处理所有节点的重心：DFS计算每个节点的子树大小和重儿子→利用重儿子的重心向上调整，找到当前节点的重心。这样每个节点仅处理一次，时间复杂度O(n)。
    * 💡 **学习笔记**：预处理是解决多查询问题的关键，利用问题性质（如重心的路径性）可大幅降低复杂度。

2.  **关键点2：如何确定重心的位置？**
    * **分析**：对于节点x，若其重儿子y的子树大小超过x子树大小的一半，则x的重心一定在y的子树的重心路径上。从y的重心开始向上跳，直到找到满足“最大连通块≤x子树大小的一半”的节点。若重儿子的子树大小不超过一半，则x本身就是重心。
    * 💡 **学习笔记**：重心的位置具有“路径性”，可通过重儿子的重心快速定位。

3.  **关键点3：如何处理边界条件？**
    * **分析**：叶子节点的子树大小为1，其重心是自身；若某节点的所有子树大小均不超过自身大小的一半，则自身是重心。向上跳时需确保不越界（如不能跳到父节点之外）。
    * 💡 **学习笔记**：边界条件（如叶子节点、重儿子为空）需在代码中单独处理，避免越界错误。

### ✨ 解题技巧总结
- **子树大小预处理**：DFS时同步计算每个节点的子树大小，为后续判断提供依据。
- **重儿子优先**：利用重儿子（最大子树）的重心作为起点，减少调整次数。
- **向上跳的终止条件**：当向上跳后最大连通块不再变小时，停止调整（否则更优解已找到）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合多个优质题解（如mrsrz、Ryan_的代码），提炼出一个通用的核心C++实现，帮助大家快速掌握完整解题框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了mrsrz和Ryan_的思路，通过DFS预处理子树大小和重儿子，然后向上调整找到每个节点的重心。代码结构清晰，适合竞赛场景。
* **完整核心代码**：
    ```cpp
    #include <cstdio>
    #include <algorithm>
    #define N 300005
    using namespace std;

    int n, q, fa[N], head[N], cnt;
    int sz[N], mx[N], ans[N]; // sz:子树大小，mx:最大子树大小，ans:重心

    struct Edge {
        int to, nxt;
    } e[N];

    void add(int u, int v) {
        e[++cnt] = {v, head[u]};
        head[u] = cnt;
    }

    void dfs(int u) {
        sz[u] = 1;
        mx[u] = 0;
        int son = 0; // 重儿子
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            dfs(v);
            sz[u] += sz[v];
            if (sz[v] > mx[u]) {
                mx[u] = sz[v];
                son = v;
            }
        }
        if (son == 0) { // 叶子节点
            ans[u] = u;
            return;
        }
        // 从重儿子的重心开始向上跳
        int now = ans[son];
        while (fa[now] != u) { // 未跳到u的子节点外
            int current_max = max(mx[now], sz[u] - sz[now]);
            int parent_max = max(mx[fa[now]], sz[u] - sz[fa[now]]);
            if (parent_max < current_max) {
                now = fa[now];
            } else {
                break;
            }
        }
        ans[u] = now;
    }

    int main() {
        scanf("%d%d", &n, &q);
        for (int i = 2; i <= n; ++i) {
            scanf("%d", &fa[i]);
            add(fa[i], i);
        }
        dfs(1);
        while (q--) {
            int x;
            scanf("%d", &x);
            printf("%d\n", ans[x]);
        }
        return 0;
    }
    ```
* **代码解读概要**：
    - 首先通过`add`函数构建树的邻接表。
    - `dfs`函数递归计算每个节点的子树大小（`sz[]`）和最大子树大小（`mx[]`），并确定重儿子。
    - 对于非叶子节点，从其重儿子的重心（`ans[son]`）开始向上跳，比较当前节点和父节点的最大连通块大小，找到满足条件的重心。
    - 主函数读取输入，调用`dfs`预处理所有节点的重心，最后处理查询并输出结果。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：作者mrsrz**
* **亮点**：利用`rt[]`数组存储每个节点的重心，通过DFS递归处理重儿子的重心并向上调整，代码简洁高效。
* **核心代码片段**：
    ```cpp
    void dfs(int now, int pre) {
        sz[now] = 1;
        for (int i = head[now]; i; i = e[i].nxt) {
            dfs(e[i].to, now);
            sz[now] += sz[e[i].to];
            mx[now] = max(mx[now], sz[e[i].to]);
        }
        int id = now, me = mx[now];
        for (int i = head[now]; i; i = e[i].nxt) {
            int it = rt[e[i].to], pre_val = max(mx[it], sz[now] - sz[it]), p = it;
            while (fa[it] != now) {
                it = fa[it];
                int new_val = max(mx[it], sz[now] - sz[it]);
                if (new_val < pre_val) pre_val = new_val, p = it;
                else break;
            }
            if (me > pre_val) {
                me = pre_val;
                id = p;
            }
        }
        rt[now] = id;
    }
    ```
* **代码解读**：
    - `sz[now]`计算当前节点的子树大小，`mx[now]`记录最大子树大小。
    - 对于每个子节点，取其子树的重心（`rt[e[i].to]`），并向上跳（`while`循环），找到使最大连通块最小的节点（`p`）。
    - 比较所有子节点的最优解，更新当前节点的重心（`rt[now]`）。
* 💡 **学习笔记**：通过递归和向上跳的贪心策略，确保每个节点的重心在O(1)时间内确定，整体复杂度O(n)。

**题解二：作者Ryan_**
* **亮点**：代码逻辑直白，`ans[]`数组直接存储每个节点的重心，`while`循环处理向上跳的条件，易理解。
* **核心代码片段**：
    ```cpp
    void dfs(int x) {
        ans[x] = x;
        size[x] = 1;
        int maxn = 0, t = 0;
        for (int i = first[x]; i; i = nxt[i]) {
            int v = go[i];
            dfs(v);
            size[x] += size[v];
            if (size[v] > maxn) {
                maxn = size[v];
                t = v;
            }
        }
        f[x] = maxn;
        if (f[x] * 2 < size[x]) ans[x] = x;
        else {
            int now = ans[t];
            while (fa[now] && max(f[now], size[x] - size[now]) > max(f[fa[now]], size[x] - size[fa[now]])) 
                now = fa[now];
            ans[x] = now;
        }
    }
    ```
* **代码解读**：
    - `size[x]`计算子树大小，`maxn`记录最大子树大小（`t`为对应的子节点）。
    - 若最大子树大小不超过当前子树大小的一半（`f[x]*2 < size[x]`），则当前节点是重心。
    - 否则，从`ans[t]`（重儿子的重心）开始向上跳，直到找到满足条件的节点。
* 💡 **学习笔记**：通过简单的条件判断（`max(...)`比较），快速调整重心位置，代码可读性强。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解重心的调整过程，我们设计一个“像素树探险”动画，用8位像素风格展示DFS预处理和重心调整的每一步。
</visualization_intro>

  * **动画演示主题**：`像素树的重心探险`

  * **核心演示内容**：展示DFS遍历树，计算子树大小（用像素块高度表示），并从重儿子的重心向上跳调整重心的过程。

  * **设计思路简述**：8位像素风（如FC游戏画面）营造轻松氛围；用不同颜色标记当前节点（黄色）、重儿子（绿色）、重心（蓝色）；子树大小用像素块高度动态变化，向上跳时用箭头动画（红色）指示路径。音效（“叮”）在关键步骤（如子树大小更新、重心调整）响起，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧显示像素树（节点为方块，边为线条），右侧显示控制面板（单步/自动/重置按钮，速度滑块）。
          * 顶部显示当前处理的节点和子树大小，底部显示代码片段（高亮当前执行行）。

    2.  **DFS遍历与子树大小计算**：
          * 从根节点（1号）开始，像素块颜色变为黄色（当前节点）。
          * 递归访问子节点时，子节点颜色依次变黄，子树大小（像素块高度）逐渐增加（如叶子节点高度为1，父节点高度为子节点之和）。
          * 计算最大子树时，重儿子的像素块边框变为绿色，并标注“重儿子”。

    3.  **重心调整（向上跳）**：
          * 对于非叶子节点，从其重儿子的重心（蓝色方块）开始，红色箭头向上移动（跳父节点）。
          * 每跳一步，比较当前节点和父节点的最大连通块大小（用数字显示），若父节点更优则继续跳，否则停止。
          * 最终重心节点变为蓝色，标注“当前重心”。

    4.  **完成与查询**：
          * 预处理完成后，支持输入查询节点，对应节点的重心（蓝色）闪烁，伴随“胜利”音效。
          * 可切换“自动播放”模式，观看完整预处理过程。

  * **旁白提示**：
      * “现在处理节点3，它的子树大小是5。”
      * “节点3的重儿子是5号，它的重心是6号。”
      * “向上跳到父节点5号，最大连通块大小是2（原大小5的一半是2.5），满足条件！”

<visualization_conclusion>
通过这个动画，我们能直观看到子树大小的计算和重心调整的每一步，理解“重儿子→重心→向上跳”的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
树的重心性质在图论中应用广泛，掌握此题后，可尝试以下拓展练习：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 树的重心可用于优化路径问题（如最小距离和）、树的分割问题（如将树分成两部分）。
      - 类似地，利用“重链”或“子树性质”预处理的方法，可解决树的直径、LCA等问题。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1395 会议** 
          * 🗣️ **推荐理由**：直接考察树的重心，求使所有节点到重心的距离和最小的点，巩固重心性质。
    2.  **洛谷 P2986 [USACO10MAR]The Rock Game S** 
          * 🗣️ **推荐理由**：结合树的重心与游戏策略，锻炼综合应用能力。
    3.  **洛谷 P4582 [FJOI2015]树** 
          * 🗣️ **推荐理由**：涉及树的重心的动态调整，适合进阶练习。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，对我们很有启发：
</insights_intro>

> **参考经验 (来自作者くろねこ)**：“最初尝试暴力对每个查询DFS，结果超时。后来意识到需要预处理，利用重儿子的重心向上跳的方法，才AC。”
>
> **点评**：这位作者的经验提醒我们，多查询问题需优先考虑预处理。树的重心的路径性质是关键，利用重儿子减少计算量是常见优化策略。遇到超时问题时，应分析时间复杂度，寻找更优的预处理方法。

-----

<conclusion>
本次关于“Kay and Snowflake”的分析就到这里。希望大家通过本指南掌握树的重心的性质与预处理方法，并能在类似问题中灵活运用。记住，多画图、多调试是理解树结构问题的关键！下次再见～💪
</conclusion>

---
处理用时：145.90秒