# 题目信息

# Catch the Mole(Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is the limit on the number of queries.

This is an interactive problem.

You are given a tree of $ n $ nodes with node $ 1 $ as its root node.

There is a hidden mole in one of the nodes. To find its position, you can pick an integer $ x $ ( $ 1 \le x \le n $ ) to make an inquiry to the jury. Next, the jury will return $ 1 $ when the mole is in subtree $ x $ . Otherwise, the judge will return $ 0 $ . If the judge returns $ 0 $ and the mole is not in root node $ 1 $ , the mole will move to the parent node of the node it is currently on.

Use at most $ 300 $ operations to find the current node where the mole is located.

## 说明/提示

In the first test case, the mole is in node $ 2 $ initially.

For the query "? 2", the jury returns $ 1 $ because the mole is in subtree $ 2 $ . After this query, the mole does not move.

The answer $ 2 $ is the current node where the mole is located, so the answer is considered correct.

In the second test case, the mole is in node $ 6 $ initially.

For the query "? 2", the jury returns $ 0 $ because the mole is not in subtree $ 2 $ . After this query, the mole moves from node $ 6 $ to node $ 5 $ .

For the query "? 6", the jury returns $ 0 $ because the mole is not in subtree $ 6 $ . After this query, the mole moves from node $ 5 $ to node $ 4 $ .

For the query "? 4", the jury returns $ 1 $ because the mole is in subtree $ 4 $ . After this query, the mole does not move.

The answer $ 4 $ is the current node where the mole is located, so the answer is considered correct.

Please note that the example is only for understanding the statement, and the queries in the example do not guarantee to determine the unique position of the mole.

## 样例 #1

### 输入

```
2
2
1 2

1

6
1 2
1 3
1 4
4 5
5 6

0

0

1```

### 输出

```
? 2

! 2






? 2

? 6

? 4

! 4```

# AI分析结果

---
# 💡 Kay的C++算法解析：Catch the Mole (Easy Version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Catch the Mole (Easy Version)”这道交互式编程题。这道题需要通过有限的询问次数定位隐藏的鼹鼠位置，核心涉及根号分治和二分查找的巧妙结合。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`交互式问题与根号分治` 

🗣️ **初步分析**：
解决这道题的关键在于利用“根号分治”思想，将问题规模缩小到可处理的范围，再结合二分查找定位目标。简单来说，根号分治就像“分块整理”——把问题分成两部分，一部分处理小规模（如深度小于√n的节点），另一部分处理大规模（深度≥√n的节点），总操作次数控制在O(√n)级别。

在本题中，我们首先通过多次询问叶子节点（约√n次），让鼹鼠向上移动，排除深度较小的子树。剩下的问题规模被缩小后，再通过DFS遍历可能的子树，最后在确定的链上用二分法定位鼹鼠位置。核心难点在于如何通过有限的询问次数排除无效子树，并在链上高效定位。

可视化设计上，我们将采用8位像素风格，用不同颜色的像素块表示树节点、鼹鼠位置及询问结果。例如，询问叶子节点时，节点会闪烁并伴随“叮”的音效；鼹鼠移动时，像素块会向上滑动；二分链时，中间节点会高亮显示，帮助直观理解每一步操作。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解值得重点参考：
</eval_intro>

**题解一：来源：Federico2903（赞：5）**
* **点评**：这份题解思路非常清晰，巧妙结合了根号分治与二分查找。作者首先通过预处理计算每个节点的最大深度，然后通过多次询问叶子节点排除深度较小的子树，再利用DFS处理剩余子树，最后在链上二分确定位置。代码中变量命名规范（如`dep[u]`表示节点u的最大深度），边界处理严谨（如`dfs1`函数中只询问前k-1个子树），算法复杂度分析合理（约2√n + logn），实践价值高，可直接用于竞赛。

**题解二：来源：Hoks（赞：0）**
* **点评**：此题解思路与Federico2903类似，但代码更简洁。作者通过预处理深度、询问叶子节点排除无效子树、DFS遍历剩余子树，最后二分链的流程，完整实现了算法。代码中使用`vector`存储树结构，`dfs`函数计算深度，逻辑清晰，适合学习根号分治的基础实现。

**题解三：来源：cyc001（赞：3）**
* **点评**：此题解提出了不同的根号分治思路，通过调整深度区间（如L=0.8, R=1.3）优化询问次数，具有创新性。虽然提到可能被链卡次数，但通过调整参数（如将阈值设为50）可通过测试，适合拓展思考分治策略的灵活性。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下关键点或难点，结合优质题解的共性，提炼出核心策略：
</difficulty_intro>

1.  **关键点1：如何排除深度较小的子树？**
    * **分析**：通过多次询问叶子节点（约√n次），若返回0，鼹鼠会向上移动。经过B次询问后，深度≤B的子树中不可能存在鼹鼠（因鼹鼠已移动B次）。例如，Federico2903的题解中，先询问叶子节点B次（B=70），若返回0则排除这些子树。
    * 💡 **学习笔记**：通过“主动移动”鼹鼠，缩小搜索范围是交互式问题的常用技巧。

2.  **关键点2：如何高效处理剩余子树？**
    * **分析**：预处理每个节点的最大深度，DFS遍历剩余子树（仅处理深度>B的子树）。为避免链卡次数，询问前k-1个子树，若均返回0则进入最后一个子树。例如，Federico2903的`dfs1`函数中，仅询问前`son.size()-1`个子树，确保操作次数可控。
    * 💡 **学习笔记**：子树选择策略是避免最坏情况（如链状树）的关键。

3.  **关键点3：如何在链上定位鼹鼠？**
    * **分析**：记录DFS路径，形成一条链。通过二分法在链上确定位置，结合鼹鼠移动次数（即失败询问次数）调整二分区间。例如，Hoks的题解中，通过`l`、`r`指针二分，`ss`记录失败次数，最终定位节点。
    * 💡 **学习笔记**：二分查找是缩小范围的高效手段，需结合移动次数调整逻辑。

### ✨ 解题技巧总结
- **预处理深度**：通过DFS计算每个节点的最大深度，快速判断子树是否可能包含鼹鼠。
- **主动移动策略**：多次询问叶子节点，迫使鼹鼠移动，排除无效子树。
- **子树选择优化**：仅询问前k-1个子树，避免链状树卡次数。
- **二分链定位**：记录路径后，结合移动次数二分，高效确定位置。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，结合了Federico2903和Hoks的代码，逻辑清晰且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Federico2903和Hoks的思路，预处理深度→询问叶子排除子树→DFS处理剩余子树→链上二分，完整实现了算法。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int T, n, fail_cnt;
    vector<int> G[5005];
    int max_depth[5005], depth[5005];
    vector<int> path;

    int query(int x) {
        cout << "? " << x << endl;
        int res; cin >> res;
        if (!res) fail_cnt++;
        return res;
    }

    void found(int x) {
        cout << "! " << x << endl;
    }

    void dfs_depth(int u, int parent) {
        max_depth[u] = 1;
        depth[u] = depth[parent] + 1;
        for (int v : G[u]) {
            if (v == parent) continue;
            dfs_depth(v, u);
            max_depth[u] = max(max_depth[u], max_depth[v] + 1);
        }
    }

    void dfs_subtree(int u, int parent) {
        path.push_back(u);
        vector<int> children;
        for (int v : G[u]) {
            if (v == parent || max_depth[v] <= fail_cnt) continue;
            children.push_back(v);
        }
        for (int i = 0; i < (int)children.size() - 1; ++i) {
            if (query(children[i])) {
                dfs_subtree(children[i], u);
                return;
            }
        }
        if (!children.empty()) {
            dfs_subtree(children.back(), u);
        }
    }

    void solve() {
        fail_cnt = 0;
        path.clear();
        cin >> n;
        for (int i = 1; i <= n; ++i) G[i].clear();
        for (int i = 1; i < n; ++i) {
            int u, v; cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs_depth(1, 0);

        // 找一个叶子节点（max_depth=1）
        int leaf = 0;
        for (int i = 1; i <= n; ++i) {
            if (max_depth[i] == 1) {
                leaf = i;
                break;
            }
        }

        if (query(leaf)) {
            found(leaf);
            return;
        }
        // 再询问B-1次（B=70）
        for (int i = 1; i < 70; ++i) query(leaf);

        dfs_subtree(1, 0);

        // 链上二分
        int l = 1, r = path.size() - 1, ans = 0, cnt = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int pos = mid > cnt ? mid - cnt : 0;
            if (pos == 0) {
                l = mid + 1;
                ans = mid;
                continue;
            }
            if (query(path[pos])) {
                l = mid + 1;
                ans = mid;
            } else {
                r = mid - 1;
                cnt++;
            }
        }
        if (ans > cnt) found(path[ans - cnt]);
        else found(1);
    }

    int main() {
        cin >> T;
        while (T--) solve();
        return 0;
    }
    ```
* **代码解读概要**：代码首先预处理每个节点的最大深度（`dfs_depth`），然后通过询问叶子节点排除深度较小的子树。接着用`dfs_subtree`遍历剩余子树，记录路径。最后在路径上二分查找，结合失败次数（`cnt`）确定鼹鼠位置。

---
<code_intro_selected>
以下是优质题解的核心片段赏析：
</code_intro_selected>

**题解一：来源：Federico2903**
* **亮点**：预处理最大深度，DFS时仅询问前k-1个子树，避免链卡次数。
* **核心代码片段**：
    ```cpp
    void dfs1(int u, int fa) {
        s[++top] = u;
        vector <int> son;
        for (auto v : G[u]) {
            if (v == fa || dep[v] <= zc) continue;
            son.push_back(v);
        }
        rep (i, 0, son.size() - 2) {
            if (ask(son[i])) return dfs1(son[i], u);
        }
        if (son.size()) dfs1(son.back(), u);
    }
    ```
* **代码解读**：这段代码是DFS处理子树的核心。`son`存储深度>失败次数的子节点。仅询问前`son.size()-1`个子节点，若均返回0，则进入最后一个子节点。这样避免了链状树中多次询问导致的操作次数爆炸，是关键优化点。
* 💡 **学习笔记**：子树选择策略是平衡最坏情况的关键，优先排除部分子树可大幅减少操作次数。

**题解二：来源：Hoks**
* **亮点**：链上二分逻辑简洁，结合失败次数调整区间。
* **核心代码片段**：
    ```cpp
    int l=1,r=b.size()-1,ss=0,ans=0;
    while(l<=r) {
        int mid=(l+r)>>1;x=mid>ss?mid-ss:-1;
        if(x==-1){l=mid+1;ans=mid;continue;}
        if(query(b[x])) l=mid+1,ans=mid;
        else r=mid-1,ss++;
    }
    ```
* **代码解读**：这段代码实现链上二分。`ss`记录失败次数（鼹鼠移动次数），`mid`是当前中间位置。若`mid>ss`，则询问路径中`mid-ss`的位置（因鼹鼠已移动ss次），根据结果调整区间。最终通过`ans-ss`定位当前位置。
* 💡 **学习笔记**：二分查找需结合鼹鼠移动次数，确保查询位置与当前状态匹配。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解算法流程，我们设计了“鼹鼠大冒险”像素动画，以8位复古风格展示询问、移动和定位过程。
</visualization_intro>

  * **动画演示主题**：`鼹鼠大冒险——在像素树中定位`
  * **核心演示内容**：展示树结构初始化、询问叶子节点、鼹鼠移动、DFS遍历子树、链上二分的全过程。
  * **设计思路简述**：采用8位像素风格（如FC红白机色调），用不同颜色标记节点（绿色=可能包含鼹鼠，红色=排除，黄色=当前询问）。关键操作（如询问、移动）伴随“叮”或“滴答”音效，增强记忆点。每完成一个阶段（如排除子树）视为“小关卡”，增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕左侧显示像素树（节点用小方块表示，边用细线条连接），右侧显示控制面板（开始/暂停、单步、重置按钮，速度滑块）。
        - 背景播放8位风格轻音乐（如《超级玛丽》经典旋律）。

    2.  **询问叶子节点**：
        - 选中叶子节点（黄色高亮），点击“单步”或“自动播放”，节点闪烁并播放“叮”音效。
        - 若返回0，鼹鼠所在节点（初始为未知，用灰色问号表示）向上移动一格（像素块上滑），并播放“滴答”音效；若返回1，节点变绿色，动画结束。

    3.  **DFS遍历子树**：
        - 遍历到子节点时，箭头从当前节点指向子节点（蓝色闪烁），子节点黄色高亮。
        - 若返回0，子节点变红色（排除）；若返回1，进入该子树递归（箭头持续指向）。

    4.  **链上二分**：
        - 路径显示为一条水平链（节点按顺序排列），中间节点黄色高亮。
        - 每次二分询问时，中间节点闪烁，根据结果调整区间（左半或右半部分变灰色），最终定位节点变绿色，播放“胜利”音效（如《魂斗罗》通关音）。

  * **旁白提示**：
      - （询问叶子时）“现在询问叶子节点，若返回0，鼹鼠会向上移动哦！”
      - （DFS遍历）“这一步在排除不可能的子树，剩下的子树更可能包含鼹鼠~”
      - （二分链）“中间节点是关键！通过比较结果缩小范围，很快就能找到啦！”

<visualization_conclusion>
通过这样的动画，我们可以直观看到每一步操作如何影响鼹鼠位置和搜索范围，轻松理解根号分治与二分查找的协同作用。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，可尝试以下拓展练习，巩固交互式问题与分治思想的应用：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 根号分治不仅适用于树结构，还可用于数组（如分块处理区间查询）、图（如分层处理最短路径）等场景。
      - 交互式问题的关键是“主动引导”目标状态（如本题中迫使鼹鼠移动），缩小搜索范围。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1829 [国家集训队]Crash的数字表格 / JZPTAB**  
          * 🗣️ **推荐理由**：涉及分块处理数论问题，巩固根号分治思想。
    2.  **洛谷 P5318 【深基18.例3】查找文献**  
          * 🗣️ **推荐理由**：交互式查找问题，练习通过有限询问定位目标。
    3.  **洛谷 P4781 【模板】矩阵求逆**  
          * 🗣️ **推荐理由**：涉及分治优化矩阵运算，拓展分治策略的应用场景。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
Federico2903在题解中提到：“这个做法会被链卡操作次数，通过询问前k-1个子树规避了这个问题。”这提醒我们在设计算法时需考虑极端情况（如链状树），并通过策略调整（如子树选择优化）避免最坏情况。
</insights_intro>

> **参考经验 (来自 Federico2903)**：“最初的做法在链状树中会超时，后来发现只询问前k-1个子树，最后一个子树直接进入，避免了多次无效询问。”
>
> **点评**：这位作者的经验非常实用。在交互式问题中，极端数据（如链、菊花图）常导致算法失效，需通过针对性优化（如子树选择策略）提升鲁棒性。调试时可手动构造极端数据测试，确保算法在各种情况下都能通过。

-----

<conclusion>
本次关于“Catch the Mole (Easy Version)”的分析就到这里。通过根号分治缩小范围、DFS处理子树、二分链上定位，我们高效解决了问题。希望这份指南能帮助大家理解交互式问题的核心思路，在实践中灵活运用分治与二分技巧。下次挑战更难的问题时，记得先分析数据特点，再设计针对性策略哦！💪
</conclusion>

---
处理用时：143.94秒