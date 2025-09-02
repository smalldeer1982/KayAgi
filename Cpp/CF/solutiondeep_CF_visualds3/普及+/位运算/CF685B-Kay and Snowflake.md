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
今天我们来一起分析“Kay and Snowflake”这道C++编程题。这道题的核心是找到树中每个子树的重心，需要我们结合树的重心的性质和高效预处理方法来解决。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`图论（树的重心性质应用）`

🗣️ **初步分析**：
解决这道题的关键在于理解树的重心的性质，并利用这些性质高效预处理每个子树的重心。树的重心是指，删除该节点后，所有连通块中最大的那个的大小不超过原树大小的一半。简单来说，重心是树的“平衡中心”，就像跷跷板的支点，让两边尽可能平衡。

在本题中，我们需要处理多个查询，每个查询要求某个子树的重心。直接对每个查询单独计算会超时，因此需要预处理每个节点的子树重心。核心思路是利用树的重心的一个重要性质：子树的重心要么在当前节点，要么在其重儿子（子树最大的子节点）的子树的重心路径上。通过一次DFS预处理子树大小，并利用重儿子的重心向上跳，可以高效找到每个子树的重心。

- **题解思路**：多数题解采用DFS预处理子树大小（`size[u]`）和重儿子（`son[u]`），然后从重儿子的重心向上跳，直到找到满足条件的重心。
- **核心难点**：如何利用重儿子的重心快速确定当前节点的重心；如何处理边界条件（如叶子节点的重心是自身）。
- **可视化设计**：用8位像素风格展示树的结构，用不同颜色标记当前处理节点、重儿子、重心候选节点。动画中动态更新子树大小（用像素方块堆叠表示），并演示“向上跳”的过程（用箭头移动高亮节点），配合“叮”的音效提示关键步骤。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑清晰、实现高效且易于学习，被选为优质题解（≥4星）：
</eval_intro>

**题解一：作者mrsrz**
* **点评**：此题解思路简洁，利用DFS预处理子树大小和重儿子，通过“向上跳”的方式快速确定重心。代码中`rt[u]`存储u子树的重心，`sz[u]`和`mx[u]`分别记录子树大小和最大子树大小。亮点在于“向上跳”的循环优化（一旦当前节点更优则停止），确保时间复杂度为O(n)。代码变量命名清晰（如`rt`表示重心），边界处理严谨（叶子节点默认重心为自身），适合竞赛参考。

**题解二：作者Ryan_**
* **点评**：此题解直接利用重心性质（最大子树大小不超过原树的一半），通过DFS递归计算`size[u]`和`f[u]`（最大子树大小）。核心逻辑在`ans[x]`的更新：若重儿子的子树大小超过原树的一半，则从该重儿子的重心向上跳。代码结构工整，关键步骤注释明确（如“暴力往上走”），适合初学者理解。

**题解三：作者shao0320**
* **点评**：此题解代码简洁，通过`son[u]`记录重儿子，`siz[u]`记录子树大小。核心逻辑中，若重儿子的子树大小超过原树的一半，则从该重儿子的重心向上跳，直到找到满足条件的节点。代码中循环条件（`max(siz[son[xx]], siz[x]-siz[xx])*2 > siz[x]`）准确体现重心定义，变量命名直观（如`siz`表示大小），是典型的O(n)解法。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼核心思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何高效预处理子树大小？**
    * **分析**：子树大小（`size[u]`）是计算重心的基础。通过后序遍历（DFS），从叶子节点开始累加子树大小。例如，`size[u] = 1 + sum(size[v])`（v是u的子节点）。优质题解通常用一次DFS完成所有节点的`size`计算，时间复杂度O(n)。
    * 💡 **学习笔记**：子树大小的预处理是树问题的“地基”，后序遍历是常用方法。

2.  **关键点2：如何利用重儿子的重心快速找到当前节点的重心？**
    * **分析**：根据重心性质，若当前节点u的重儿子v的子树大小超过原树的一半，则u的重心一定在v的子树的重心路径上。因此，从v的重心（`ans[v]`）开始向上跳，直到找到满足`max(子树大小, 原树大小 - 当前节点子树大小) ≤ 原树大小/2`的节点。
    * 💡 **学习笔记**：重儿子是树的“最胖分支”，其重心路径是当前节点重心的候选路径。

3.  **关键点3：如何处理边界条件（如叶子节点）？**
    * **分析**：叶子节点没有子节点，其子树大小为1，最大子树大小为0。根据重心定义，叶子节点自身就是重心（删除后无连通块，满足条件）。优质题解通常在DFS中默认`ans[u] = u`，后续根据重儿子调整。
    * 💡 **学习笔记**：边界条件（如叶子、单节点子树）需优先处理，避免逻辑错误。

### ✨ 解题技巧总结
- **问题分解**：将问题拆解为“预处理子树大小”和“确定每个节点的重心”两部分，分步解决。
- **利用重链性质**：重儿子是树的关键分支，其重心路径是当前节点重心的候选，减少无效搜索。
- **循环优化**：向上跳时，一旦当前节点更优则停止，避免不必要的计算（时间复杂度O(n)）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解的通用核心实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了mrsrz、Ryan_等优质题解的思路，通过DFS预处理子树大小和重儿子，利用重儿子的重心向上跳确定每个节点的重心。代码简洁高效，适合竞赛使用。
* **完整核心代码**：
    ```cpp
    #include <cstdio>
    #include <algorithm>
    #define N 300005
    using namespace std;

    int n, q, fa[N], head[N], rt[N], sz[N], son[N], cnt;
    struct Edge { int to, nxt; } e[N];

    void add(int u, int v) {
        e[++cnt] = {v, head[u]};
        head[u] = cnt;
    }

    void dfs(int u) {
        sz[u] = 1;
        son[u] = 0; // 重儿子初始化为0（无子节点）
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            dfs(v);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v; // 更新重儿子
        }
        rt[u] = u; // 默认重心为自身
        if (son[u] == 0) return; // 叶子节点直接返回
        int cur = rt[son[u]]; // 从重儿子的重心开始跳
        while (true) {
            int max_part = max(sz[son[cur]], sz[u] - sz[cur]);
            int parent_max = (fa[cur] == u) ? 0 : max(sz[son[fa[cur]]], sz[u] - sz[fa[cur]]);
            if (max_part <= parent_max) break; // 当前节点更优，停止
            cur = fa[cur]; // 向上跳
        }
        rt[u] = cur;
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
            printf("%d\n", rt[x]);
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先通过`add`函数建立树的邻接表，然后`dfs`函数递归计算每个节点的子树大小（`sz[u]`）和重儿子（`son[u]`）。对于每个节点，默认重心为自身（`rt[u] = u`），若存在重儿子，则从其重心开始向上跳，直到找到满足条件的重心。主函数处理输入并输出查询结果。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段，理解其亮点和实现思路。
</code_intro_selected>

**题解一：作者mrsrz**
* **亮点**：利用`mx[u]`记录最大子树大小，通过循环向上跳优化，确保时间复杂度O(n)。
* **核心代码片段**：
    ```cpp
    void dfs(int now,int pre){
        sz[now]=1;
        for(int i=head[now];i;i=e[i].nxt){
            dfs(e[i].to,now);
            sz[now]+=sz[e[i].to];
            mx[now]=max(mx[now],sz[e[i].to]);
        }
        int id=now,me=mx[now];
        for(int i=head[now];i;i=e[i].nxt){
            int it=rt[e[i].to],pre=max(mx[it],sz[now]-sz[it]),p=it;
            while(fa[it]!=now){
                it=fa[it];
                int New=max(mx[it],sz[now]-sz[it]);
                if(New<pre)pre=New,p=it;else break;
            }
            if(me>pre){
                me=pre;
                id=p;
            }
        }
        rt[now]=id;
    }
    ```
* **代码解读**：`dfs`函数中，`sz[now]`计算子树大小，`mx[now]`记录最大子树大小。对于每个子节点，从其子树的重心（`rt[e[i].to]`）开始向上跳，比较跳后的最大连通块大小（`New`），若更优则更新。最终`rt[now]`存储当前节点的重心。
* 💡 **学习笔记**：向上跳时，一旦当前节点更优则停止，避免无效计算，是O(n)时间复杂度的关键。

**题解二：作者Ryan_**
* **亮点**：直接利用重心定义（最大子树大小不超过原树的一半），代码简洁易读。
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
* **代码解读**：`size[x]`计算子树大小，`f[x]`记录最大子树大小。若最大子树大小不超过原树的一半（`f[x] * 2 < size[x]`），则当前节点是重心；否则从该子树的重心（`ans[t]`）向上跳，直到找到更优的节点。
* 💡 **学习笔记**：通过比较当前节点和父节点的最大连通块大小，快速确定重心，逻辑直接。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“如何从重儿子的重心向上跳找到当前节点的重心”，我们设计一个8位像素风格的动画，模拟DFS遍历和重心确定过程。
</visualization_intro>

  * **动画演示主题**：`像素树的重心探险`（复古FC游戏风格）

  * **核心演示内容**：展示树的结构（像素方块节点），动态更新子树大小（节点旁显示数字），并演示从重儿子的重心向上跳的过程（箭头移动高亮节点）。

  * **设计思路简述**：采用8位像素风（红、绿、蓝等简洁色调），节点用方块表示，边用细线连接。子树大小用数字显示在节点上方，重心候选节点用黄色高亮。向上跳时，箭头从当前重心指向父节点，配合“叮”的音效提示关键步骤，增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕显示像素树（节点为彩色方块，根节点为红色），控制面板包含“开始/暂停”“单步”“重置”按钮和速度滑块。
          * 播放8位风格背景音乐（轻快的电子音效）。

    2.  **DFS遍历与子树大小计算**：
          * 从根节点开始，DFS遍历每个节点（节点闪烁蓝色）。
          * 子节点访问完成后，父节点大小更新（数字从1开始累加，伴随“滴”的音效）。

    3.  **重儿子标记与重心候选**：
          * 重儿子用绿色方块高亮（子树大小最大）。
          * 重儿子的重心（`ans[son[u]]`）用黄色方块高亮，箭头指向该节点。

    4.  **向上跳过程演示**：
          * 从黄色节点开始，箭头向上移动（父节点），比较最大连通块大小（数字显示在节点旁）。
          * 若当前节点更优（最大连通块更小），箭头停留；否则继续移动，直到找到重心（最终节点用金色高亮，播放“胜利”音效）。

    5.  **查询结果展示**：
          * 用户输入查询节点，对应节点闪烁金色，显示其重心（金色箭头指向结果）。

  * **旁白提示**：
      * （遍历节点时）“现在处理节点u，它的子节点是v和w，先访问v…”
      * （更新子树大小时）“u的子树大小变为3，因为v的子树大小是2，w是1。”
      * （向上跳时）“当前节点的最大连通块是2，父节点的最大连通块是1，更优！继续向上跳。”

<visualization_conclusion>
通过这样的像素动画，我们可以直观看到子树大小的计算、重儿子的选择，以及向上跳确定重心的过程，轻松理解算法核心逻辑。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以将树的重心的性质应用到更多场景，例如树的结构分析、动态树问题等。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 树的重心性质可用于树的分割（如将树分成大小相近的子树）。
      * 预处理子树信息（如大小、深度）是解决树问题的常用方法。
      * 利用重链（重儿子路径）优化搜索是树问题的高效策略。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1395 会议**
          * 🗣️ **推荐理由**：直接考察树的重心，帮助巩固基础性质。
    2.  **洛谷 P4582 [FJOI2014]树的重心**
          * 🗣️ **推荐理由**：涉及多棵子树的重心统计，提升对重心性质的灵活应用。
    3.  **洛谷 P5043 树的距离之和**
          * 🗣️ **推荐理由**：结合重心与距离和的性质，拓展树问题的综合应用。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些经验对我们有重要参考价值：
</insights_intro>

> **参考经验 (来自作者くろねこ)**：“最初尝试暴力对每个查询DFS，结果超时。后来意识到需要预处理，利用树的重心性质，从重儿子的重心向上跳，最终AC。”
>
> **点评**：这位作者的经验提醒我们，暴力解法在大数据量下会超时，需结合问题性质寻找高效预处理方法。遇到超时问题时，应分析时间复杂度，寻找优化点（如本题的O(n)预处理）。

---

<conclusion>
本次关于“Kay and Snowflake”的C++解题分析就到这里。希望这份学习指南能帮助大家理解树的重心的性质和预处理方法。记住，多画图、多模拟是理解树问题的关键，下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：128.35秒