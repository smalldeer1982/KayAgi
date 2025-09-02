# 题目信息

# Sum Graph

## 题目描述

This is an interactive problem.

There is a hidden permutation $ p_1, p_2, \dots, p_n $ .

Consider an undirected graph with $ n $ nodes only with no edges. You can make two types of queries:

1. Specify an integer $ x $ satisfying $ 2 \le x \le 2n $ . For all integers $ i $ ( $ 1 \le i \le n $ ) such that $ 1 \le x-i \le n $ , an edge between node $ i $ and node $ x-i $ will be added.
2. Query the number of edges in the shortest path between node $ p_i $ and node $ p_j $ . As the answer to this question you will get the number of edges in the shortest path if such a path exists, or $ -1 $ if there is no such path.

Note that you can make both types of queries in any order.

Within $ 2n $ queries (including type $ 1 $ and type $ 2 $ ), guess two possible permutations, at least one of which is $ p_1, p_2, \dots, p_n $ . You get accepted if at least one of the permutations is correct. You are allowed to guess the same permutation twice.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ n=6 $ and the hidden permutation $ p = [1,4,2,5,3,6] $ .

Firstly, make a type $ 1 $ query on $ x=12, 2, 3 $ respectively. This adds four edges to the graph in total:

- An edge that connects node $ 6 $ and node $ 6 $ .
- An edge that connects node $ 1 $ and node $ 1 $ .
- An edge that connects node $ 1 $ and node $ 2 $ .
- An edge that connects node $ 2 $ and node $ 1 $ .

Since all of these queries are valid, the interactor returns $ 1 $ after each of them.

Then, query the number of edges in the shortest path between node $ p_1 = 1 $ and $ p_3 = 2 $ , which is equal to $ 1 $ .

Then, make a type $ 1 $ query on $ x=5 $ . This adds four edges to the graph in total:

- An edge that connects node $ 1 $ and node $ 4 $ .
- An edge that connects node $ 2 $ and node $ 3 $ .
- An edge that connects node $ 3 $ and node $ 2 $ .
- An edge that connects node $ 4 $ and node $ 1 $ .

Since this query is valid, the interactor returns $ 1 $ .

Then, query the number of edges in the shortest path between node $ p_1 = 1 $ and $ p_5 = 3 $ , which is equal to $ 2 $ .

Then, query the number of edges in the shortest path between node $ p_4 = 5 $ and $ p_5 = 3 $ . Such a path doesn't exist, therefore the interactor returns $ -1 $ .

Afterwards, due to some magic, two possible permutations that can be $ p $ are determined: the first permutation is $ [1,4,2,5,3,6] $ and the second permutation is $ [1,2,3,4,5,6] $ . Since the first permutation is equal to the hidden permutation, this test case is solved correctly. In total, $ 7 $ queries are used, which is within the limit of $ 2 \cdot 6 = 12 $ queries.

Since the answer is correct, the interactor returns $ 1 $ .

In the second test case, $ n=2 $ and the hidden permutation is $ p = [2,1] $ .

Since there are only $ 2! = 2 $ possible permutations, no queries are needed. It is sufficient to just output the two permutations, $ [1,2] $ and $ [2,1] $ . In total, $ 0 $ queries are used, which is within the limit of $ 2 \cdot 2 = 4 $ queries.

Since the answer is correct, the interactor returns $ 1 $ .

## 样例 #1

### 输入

```
2
6

1

1

1

1

1

2

-1

1
2

1```

### 输出

```
+ 12

+ 2

+ 3

? 1 3

+ 5

? 1 5

? 4 5

! 1 4 2 5 3 6 1 2 3 4 5 6


! 1 2 2 1```

# AI分析结果

---
# 💡 Kay的C++算法解析：Sum Graph 深入学习指南 💡

<introduction>
今天我们来一起分析“Sum Graph”这道交互编程题。本指南将帮助大家理解如何通过构造特定图结构和交互查询，在有限步骤内推断隐藏排列的可能值。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（交互题与图结构构造）`

🗣️ **初步分析**：
解决“Sum Graph”的关键在于通过类型1操作构造一个链状图，再利用类型2的最短路查询推断隐藏排列的可能值。简单来说，我们需要“用最少的边构造特殊图结构”，就像用两根绳子（两次类型1操作）把零散的珠子（节点）串成一条链，这样珠子的顺序就能通过“摸距离”（最短路查询）确定。

- **题解思路**：多数题解采用“构造链→找端点→查距离→输出两种可能排列”的流程。例如，通过类型1操作添加`x=n+1`和`x=n+2`的边，将图构造成链；通过查询与某点的最远距离确定链的端点；再通过端点与其他点的距离生成排列的两种可能（正序和逆序）。
- **核心难点**：如何构造链状图？如何通过查询确定端点？如何生成两种可能的排列？
- **可视化设计**：用8位像素风格展示链的构造过程（边添加时像素块闪烁）、查询时路径高亮（如绿色箭头）、距离数值动态更新。动画中会有“叮”的音效提示边添加，“滴”的提示查询完成，终点确定时播放“胜利”音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等，以下题解值得重点参考：
</eval_intro>

**题解一：Hisaishi_Kanade**
* **点评**：此题解逻辑清晰，代码结构工整。作者巧妙通过两次类型1操作（`x=n+1`和`x=n+2`）构造链，并通过两次`n-1`次查询（找端点、查距离）完成推断。代码中`addedge()`、`decide()`、`print()`函数分工明确，变量名如`pos`（记录端点）、`ans[]`（存储排列）含义清晰。亮点在于利用链的对称性，输出正逆两种排列，确保至少一个正确。

**题解二：World_Creater**
* **点评**：此题解详细解释了链的构造原理（如`n=6`时链为`1-6-2-5-3-4`），并通过`p[]`数组预计算链的顺序，便于后续排列生成。代码中`modify()`和`query()`函数封装交互操作，提高可读性。亮点是通过`maxn`变量快速确定端点，再利用距离数组`dis2[]`直接映射链上位置，逻辑简洁高效。

**题解三：zhlzt**
* **点评**：此题解代码简洁，边界处理严谨。作者通过`dp[]`数组记录各距离对应的节点，避免复杂索引计算。亮点是通过位运算（`i&1`）交替生成正逆排列，代码精炼且不易出错。例如，`ans1[dp[i]]=(i>>1)+1`和`ans2[dp[i]]=n-(j>>1)`巧妙处理了链的正逆顺序。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题时，以下三个关键点需重点突破：
</difficulty_intro>

1.  **关键点1：如何构造链状图？**
    * **分析**：通过类型1操作添加`x=n+1`和`x=n+2`的边。`x=n+1`会连接`(1,n), (2,n-1), ...`，`x=n+2`会连接`(1,n+1-1= n), (2,n+2-2= n), ...`？不，实际构造中，两次操作会形成交替连接的链。例如，`n=6`时，`x=7（n+1）`连接`(1,6), (2,5), (3,4)`；`x=8（n+2）`连接`(1,7-1=6), (2,6), ...`？实际更简单：两次操作后，节点形成`1-6-2-5-3-4`的链（相邻节点通过边连接）。
    * 💡 **学习笔记**：选择`x=n+1`和`x=n+2`是构造链的关键，确保图连通且结构规则。

2.  **关键点2：如何确定链的端点？**
    * **分析**：任选一个节点（如节点1），查询其与其他所有节点的最短路。距离最大的节点必为链的一个端点（链的两端离中间点最远）。例如，在链`1-6-2-5-3-4`中，节点1到节点4的距离是5（最长），故节点4是端点之一。
    * 💡 **学习笔记**：最远距离对应链的端点，这是链的性质决定的（链上两点最远距离是链的长度）。

3.  **关键点3：如何生成两种可能的排列？**
    * **分析**：由于链的正序和逆序都可能是隐藏排列，只需将端点作为链的起点或终点，根据其他节点到端点的距离生成两种排列即可。例如，若端点是链的起点，距离为1的节点是下一个节点；若端点是终点，距离为1的节点是前一个节点。
    * 💡 **学习笔记**：题目允许输出两种排列，利用链的对称性可轻松覆盖所有可能。

### ✨ 解题技巧总结
- **构造特殊图结构**：通过选择特定的`x`值（如`n+1`和`n+2`），将图构造成链，简化最短路查询。
- **利用最远距离找端点**：链的特性决定了最远距离对应端点，减少查询次数。
- **输出正逆排列**：利用链的对称性，生成两种可能的排列，确保至少一个正确。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解的通用核心实现，逻辑清晰且符合2n次查询限制。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Hisaishi_Kanade和World_Creater的思路，通过两次类型1操作构造链，两次`n-1`次类型2操作确定端点和距离，最后生成两种排列。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int query(int x, int y) {
        cout << "? " << x << " " << y << endl;
        cout.flush();
        int res; cin >> res;
        return res;
    }

    void modify(int x) {
        cout << "+ " << x << endl;
        cout.flush();
        int rub; cin >> rub; // 读取交互器返回值（无用）
    }

    int main() {
        int t; cin >> t;
        while (t--) {
            int n; cin >> n;
            modify(n + 1); // 构造链的第一步
            modify(n + 2); // 构造链的第二步

            // 找端点：查询节点1与其他节点的最远距离
            int max_dist = -1, endpoint = 1;
            for (int i = 2; i <= n; ++i) {
                int d = query(1, i);
                if (d > max_dist) {
                    max_dist = d;
                    endpoint = i;
                }
            }

            // 生成链的正序和逆序排列
            vector<int> chain(n);
            chain[0] = endpoint;
            for (int i = 1; i < n; ++i) {
                // 链的构造：交替连接n+1和n+2的边
                chain[i] = (i % 2 == 1) ? (n + 1 - chain[i-1]) : (n + 2 - chain[i-1]);
            }

            // 生成两种排列（正序和逆序）
            vector<int> ans1(n + 1), ans2(n + 1);
            for (int i = 1; i <= n; ++i) {
                int d = query(endpoint, i);
                ans1[i] = chain[d];
                ans2[i] = chain[n - 1 - d];
            }

            // 输出结果
            cout << "! ";
            for (int i = 1; i <= n; ++i) cout << ans1[i] << " ";
            for (int i = 1; i <= n; ++i) cout << ans2[i] << " ";
            cout << endl;
            cout.flush();
            int rub; cin >> rub; // 读取交互器确认
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先通过`modify`函数添加`n+1`和`n+2`的边构造链；然后通过`query`函数找到与节点1距离最远的端点；接着预计算链的顺序（`chain`数组）；最后通过端点与其他节点的距离生成两种排列（正序和逆序）并输出。

---
<code_intro_selected>
接下来分析优质题解的核心片段：
</code_intro_selected>

**题解一：Hisaishi_Kanade**
* **亮点**：通过`ord`数组预计算链的顺序，简化排列生成逻辑。
* **核心代码片段**：
    ```cpp
    rep(i, 1, n) if(i&1) ord[i]=l++; else ord[i]=r--;
    rep(i, 1, n) p[i]=ord[ans[i]]; 
    rep(i, 1, n) p[i]=ord[n-ans[i]+1];
    ```
* **代码解读**：`ord`数组通过奇偶交替赋值`l`（左端点递增）和`r`（右端点递减），模拟链的顺序（如`n=6`时`ord`为`[1,6,2,5,3,4]`）。`p[i]`通过`ans[i]`（距离）映射到`ord`的正序或逆序位置，生成两种排列。
* 💡 **学习笔记**：预计算链的顺序能避免重复计算，提高代码效率。

**题解二：World_Creater**
* **亮点**：通过`p`数组直接存储链的顺序，逻辑清晰。
* **核心代码片段**：
    ```cpp
    for(int i=2;i<=n;i++){
        if(i&1) p[i]=n+2-p[i-1];
        else p[i]=n+1-p[i-1];
    }
    ```
* **代码解读**：`p[i]`通过交替使用`n+2`和`n+1`减去前一个节点的值，生成链的顺序（如`p[2]=n+2-p[1]`，`p[3]=n+1-p[2]`）。这种递推方式完美模拟了链的构造过程。
* 💡 **学习笔记**：递推生成链的顺序比硬编码更灵活，适用于不同`n`的情况。

**题解三：zhlzt**
* **亮点**：通过`dp`数组记录各距离对应的节点，简化排列生成。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n;i++){
        if(i==pos) continue;
        printf("? %d %d\n",pos,i); 
        int temp;scanf("%d",&temp); 
        dp[temp]=i;
    }
    ```
* **代码解读**：`dp[temp]=i`将距离`temp`映射到节点`i`，后续通过`dp`数组的索引直接获取链上位置，避免复杂的循环查找。
* 💡 **学习笔记**：用数组记录映射关系是处理距离与节点对应的高效方法。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解链的构造和查询过程，我们设计一个“像素链探险”动画，用8位风格展示每一步操作！
</visualization_intro>

  * **动画演示主题**：`像素链探险——寻找隐藏的排列`
  * **核心演示内容**：展示类型1操作如何添加边构造链，类型2查询如何通过最短路确定端点，以及最终生成两种排列的过程。
  * **设计思路简述**：8位像素风格（如FC游戏画面）营造轻松氛围；边添加时像素块闪烁+“叮”音效，查询时路径高亮+“滴”音效，终点确定时播放“胜利”音效，增强操作记忆。

  * **动画帧步骤与交互关键点**：
    1.  **场景初始化**：屏幕左侧是n个灰色像素块（节点），右侧是控制面板（开始/暂停、单步按钮、速度滑块）。顶部显示当前操作类型（“添加边”或“查询”）。
    2.  **类型1操作（添加边）**：
        - 输入`x=n+1`，所有满足`i + j = n+1`的节点对（如`1-6`, `2-5`）之间出现黄色边（像素线），伴随“叮”音效。
        - 输入`x=n+2`，满足`i + j = n+2`的节点对（如`1-6`, `2-6`？不，实际是`1-7-1=6`, `2-7-2=5`？需修正）之间出现绿色边，链形成（如`1-6-2-5-3-4`）。
    3.  **类型2查询（找端点）**：
        - 从节点1（红色高亮）出发，用蓝色箭头依次指向其他节点，显示最短路长度（如节点1到节点4的距离是5）。距离最大的节点（节点4）变为金色（端点），播放“叮”音效。
    4.  **生成排列**：
        - 以端点（金色）为起点，蓝色箭头按距离递增顺序连接其他节点（如距离1→节点6，距离2→节点2...），生成正序排列。
        - 以端点为终点，红色箭头按距离递减顺序连接，生成逆序排列。两种排列同时显示，终点播放“胜利”音效。

  * **旁白提示**：
    - “看！添加`x=n+1`后，节点1和6连起来了，像串珠子一样～”
    - “现在查询节点1到其他节点的距离，最大的那个就是链的端点哦！”
    - “最后，我们把链的正序和逆序都输出，保证至少一个正确～”

<visualization_conclusion>
通过这样的动画，我们能清晰看到链的构造过程和查询逻辑，就像在玩一个像素版的“寻宝游戏”！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是构造特殊图结构+交互查询，这类思路还适用于以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - **构造树/链结构**：在交互题中，通过特定操作构造树或链，利用其性质（如最远距离、层级关系）推断隐藏信息（如排列、序列）。
    - **利用对称性**：输出两种可能结果（如正序和逆序），覆盖所有情况。
    - **预计算辅助**：预计算图的结构（如链的顺序），简化后续查询和排列生成。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1198** - `[NOI2002] 银河英雄传说`
        * 🗣️ **推荐理由**：考察并查集与链结构的结合，需维护节点间的距离，与本题构造链的思路类似。
    2.  **洛谷 P1521** - `[USACO2.4] 逆序对`
        * 🗣️ **推荐理由**：交互题，需通过查询确定排列的逆序对，锻炼交互逻辑和问题分解能力。
    3.  **洛谷 P4551** - `[TJOI2018] 最长异或路径`
        * 🗣️ **推荐理由**：考察图的最路径与异或性质，需构造树结构并利用前缀异或和，与本题构造链的思路有共通之处。

-----

## 7\. 学习心得与经验分享 

<insights_intro>
部分题解提到了交互格式的重要性，这是本题的易错点：
</insights_intro>

> **参考经验 (来自 Hisaishi_Kanade)**：“注意交互格式！输出`+ x`或`? i j`后要及时刷新输出（`fflush(stdout)`），否则可能导致交互器接收不到数据。”

**点评**：交互题中，输入输出的顺序和刷新非常关键。每次输出后调用`fflush`或使用`cout.flush()`能确保交互器及时接收数据，避免因缓冲区未刷新导致的错误。这是交互题调试的重要技巧！

-----

<conclusion>
本次关于“Sum Graph”的分析就到这里。通过构造链、找端点、查距离，我们成功解决了这道交互题。记住，交互题的关键是“构造+查询”，多练习类似题目能快速提升这类问题的解决能力。下次见！💪
</conclusion>

---
处理用时：130.56秒