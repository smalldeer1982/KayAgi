# 题目信息

# Books Exchange (easy version)

## 题目描述

The only difference between easy and hard versions is constraints.

There are $ n $ kids, each of them is reading a unique book. At the end of any day, the $ i $ -th kid will give his book to the $ p_i $ -th kid (in case of $ i = p_i $ the kid will give his book to himself). It is guaranteed that all values of $ p_i $ are distinct integers from $ 1 $ to $ n $ (i.e. $ p $ is a permutation). The sequence $ p $ doesn't change from day to day, it is fixed.

For example, if $ n=6 $ and $ p=[4, 6, 1, 3, 5, 2] $ then at the end of the first day the book of the $ 1 $ -st kid will belong to the $ 4 $ -th kid, the $ 2 $ -nd kid will belong to the $ 6 $ -th kid and so on. At the end of the second day the book of the $ 1 $ -st kid will belong to the $ 3 $ -th kid, the $ 2 $ -nd kid will belong to the $ 2 $ -th kid and so on.

Your task is to determine the number of the day the book of the $ i $ -th child is returned back to him for the first time for every $ i $ from $ 1 $ to $ n $ .

Consider the following example: $ p = [5, 1, 2, 4, 3] $ . The book of the $ 1 $ -st kid will be passed to the following kids:

- after the $ 1 $ -st day it will belong to the $ 5 $ -th kid,
- after the $ 2 $ -nd day it will belong to the $ 3 $ -rd kid,
- after the $ 3 $ -rd day it will belong to the $ 2 $ -nd kid,
- after the $ 4 $ -th day it will belong to the $ 1 $ -st kid.

So after the fourth day, the book of the first kid will return to its owner. The book of the fourth kid will return to him for the first time after exactly one day.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
3
2 3 1
6
4 6 2 1 5 3
1
1
4
3 4 1 2
5
5 1 2 4 3
```

### 输出

```
1 1 1 1 1 
3 3 3 
2 3 3 2 1 3 
1 
2 2 2 2 
4 4 4 1 4 
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Books Exchange (easy version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Books Exchange (easy version)”这道C++编程题。这道题的核心是通过分析小朋友之间的书传递关系，找到每本书第一次回到主人手中所需的天数。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：图论（循环检测）

🗣️ **初步分析**：
> 解决这道题的关键在于理解“置换中的循环检测”。简单来说，每个小朋友每天将书传给固定的另一个小朋友，这相当于在图中每个节点（小朋友）向唯一的后继节点（p_i）连一条有向边。由于p是一个排列（每个数唯一），整个图由若干个不相交的环组成。例如，若小朋友A→B→C→A，这就是一个长度为3的环，A的书需要3天回到自己手中。  
> 题解的核心思路是找到每个小朋友所在环的长度。常见解法有两种：  
> - **DFS标记法**：通过深度优先搜索遍历每个未访问的节点，记录环的长度并标记环内所有节点。  
> - **并查集法**：将每个节点与它的后继合并，最终同一集合内的节点构成一个环，集合大小即为环的长度（需注意并查集法在统计集合大小时可能需要额外遍历）。  
> 核心算法流程的可视化设计可以围绕“环的形成过程”展开：用不同颜色标记环中的节点，动画展示书传递的路径，当路径回到起点时高亮环的所有节点并显示长度。若采用复古像素风格，可设计“像素小人”传递书本，每传递一次伴随“叮”的音效，形成环时播放“胜利”音效。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性与优化程度等方面筛选了以下优质题解（评分≥4星）：
</eval_intro>

**题解一：作者Karry5307（赞：2）**
* **点评**：此题解思路非常清晰，直接利用DFS遍历每个未访问的节点，标记环内节点并记录环的长度。代码风格规范（如`vis`数组标记访问状态，`size`数组记录环长度），变量命名直观易懂。算法时间复杂度为O(n)，在n=200时效率很高。从实践角度看，代码可直接用于竞赛，边界处理（如初始化数组）严谨，是学习循环检测的优秀示例。

**题解二：作者盧鋅（赞：0）**
* **点评**：此题解通过DFS标记环的方式，用`vis`数组记录环的起点，`map`数组记录环的长度。虽然变量命名（如`map`）稍显模糊，但核心逻辑简洁高效（时间复杂度O(n)），代码结构清晰。其“标记环起点”的技巧（`vis[i] = root`）能有效避免重复计算，是值得学习的优化思路。

**题解三：作者_Harrisonwhl_（赞：3）**
* **点评**：此题解采用并查集法，将每个节点与后继合并，最终通过统计集合大小得到环的长度。思路正确且符合题目“并查集”的提示，但统计集合大小时需要遍历所有节点（时间复杂度O(n²)），在n=200时仍可通过。代码中`tf`数组（负责人数组）和`fd`（查找函数）的命名直观，适合理解并查集的基础应用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何识别“环”的存在？
    * **分析**：由于p是一个排列（每个数唯一），每个节点的出度为1，因此整个图必然由若干不相交的环组成。例如，若节点i的后继是j，j的后继是k，k的后继是i，则i、j、k构成一个环。DFS或并查集法的核心都是找到这些环。
    * 💡 **学习笔记**：排列中的每个节点必然属于且仅属于一个环。

2.  **关键点2**：如何高效计算环的长度？
    * **分析**：DFS法通过遍历环内所有节点，每访问一个节点就计数，直到回到起点，即可得到环的长度（如Karry5307的代码）。并查集法通过合并节点，最终同一集合内的节点数即为环的长度（需遍历所有节点统计集合大小）。
    * 💡 **学习笔记**：DFS法时间复杂度更优（O(n)），适合处理大规模数据；并查集法更直观，适合理解环的结构。

3.  **关键点3**：如何避免重复计算？
    * **分析**：使用标记数组（如`vis`）记录已访问的节点，确保每个节点只被处理一次。例如，DFS法中`vis[cur] = 1`标记当前节点已访问，后续跳过；并查集法中合并操作自动将节点归入同一集合，避免重复统计。
    * 💡 **学习笔记**：标记数组是避免重复计算的“利器”，能显著提升算法效率。

### ✨ 解题技巧总结
<summary_best_practices>
-   **问题抽象**：将书传递问题抽象为图论中的循环检测问题，每个小朋友是节点，传递关系是有向边。
-   **标记数组应用**：使用`vis`数组记录已访问节点，避免重复遍历（如DFS法）或统计（如并查集法）。
-   **环长度统计**：DFS遍历环时直接计数，或并查集统计集合大小，两种方法各有优劣，根据数据规模选择。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考（DFS标记法）**
* **说明**：此代码综合了Karry5307和盧鋅的DFS思路，通过一次遍历标记所有环并记录长度，时间复杂度O(n)，是高效且易懂的典型实现。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    using namespace std;

    const int MAXN = 205; // 题目中n最大为200
    int p[MAXN];          // 存储传递关系
    int vis[MAXN];        // 标记数组，0未访问，1已访问
    int len[MAXN];        // 记录每个节点所在环的长度

    void dfs(int start, int current, int step) {
        if (vis[current]) {
            if (current == start) { // 回到起点，记录环长度
                len[start] = step;
            }
            return;
        }
        vis[current] = 1;
        dfs(start, p[current], step + 1); // 递归访问下一个节点
        len[current] = len[start]; // 环内所有节点的长度相同
    }

    int main() {
        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            for (int i = 1; i <= n; ++i) {
                cin >> p[i];
            }
            memset(vis, 0, sizeof(vis));
            memset(len, 0, sizeof(len));
            for (int i = 1; i <= n; ++i) {
                if (!vis[i]) {
                    dfs(i, i, 0);
                }
            }
            for (int i = 1; i <= n; ++i) {
                cout << len[i] << " ";
            }
            cout << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 该代码首先读取输入数据，然后通过`dfs`函数遍历每个未访问的节点。`dfs`函数从起点`start`出发，递归访问`p[current]`，直到回到起点时记录环的长度（`step`）。环内所有节点的长度与起点相同，因此递归返回时将`len[current]`设为`len[start]`。最后输出每个节点的环长度。

---
<code_intro_selected>
接下来，我们将剖析优质题解中最能体现核心逻辑的C++实现片段，并点出各自的亮点和关键代码思路。
</code_intro_selected>

**题解一：作者Karry5307**
* **亮点**：通过DFS标记环并记录长度，时间复杂度O(n)，代码结构清晰，变量命名直观。
* **核心代码片段**：
    ```cpp
    inline ll dfs(ll cur, ll cnt, ll tot) {
        if(vis[cur]) {
            return cnt;
        }
        vis[cur]=1, size[tot]++, bel[cur]=tot;
        return dfs(perm[cur], cnt+1, tot);
    }
    ```
* **代码解读**：
    > 这段代码是DFS的核心逻辑。`cur`是当前节点，`cnt`是当前步数，`tot`是环的编号。如果`cur`已访问（`vis[cur]`为真），返回当前步数（环的长度）。否则标记`cur`为已访问（`vis[cur]=1`），将`cur`归入环`tot`（`bel[cur]=tot`），并增加环`tot`的大小（`size[tot]++`）。最后递归访问下一个节点`perm[cur]`，步数加1。
* 💡 **学习笔记**：DFS递归过程中可以同时完成环的标记和长度统计，避免重复遍历。

**题解二：作者盧鋅**
* **亮点**：通过`do-while`循环遍历环，标记环起点，代码简洁高效。
* **核心代码片段**：
    ```cpp
    if(!vis[i]){
        int root=i, step=0;
        vis[i]=root;
        do{
            i=a[i];
            vis[i]=root;
            step++;
        }while(i!=root);
        map[root]=step;
    }
    ```
* **代码解读**：
    > 这段代码处理未访问的节点`i`。首先将`i`设为环的起点（`root=i`），并标记`vis[i]=root`。然后进入`do-while`循环：访问下一个节点`a[i]`，标记其`vis`为`root`，步数`step`加1，直到回到起点`root`。最后将环的长度`step`存入`map[root]`。环内所有节点的`vis`值都是`root`，因此查询时直接取`map[vis[i]]`即可。
* 💡 **学习笔记**：`do-while`循环适合处理“至少执行一次”的场景（如环的遍历），确保起点被正确标记。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“循环检测”的过程，我设计了一个“像素书传递”的复古动画演示方案。通过8位像素风格的画面，我们可以“看到”书如何在小朋友之间传递，最终形成环的过程！
</visualization_intro>

  * **动画演示主题**：像素书传递大冒险！

  * **核心演示内容**：展示书从某个小朋友出发，经过若干次传递后回到起点，形成一个环的过程，并显示环的长度。

  * **设计思路简述**：采用8位像素风格（类似FC游戏画面），用不同颜色的像素方块代表小朋友，箭头表示书的传递方向。动画中，书每传递一次伴随“叮”的音效，形成环时播放“胜利”音效，增强操作记忆和成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化 (8位像素风)**：
          * 屏幕左侧显示n个像素方块（小朋友），每个方块上方标有编号（如①、②），颜色初始为灰色（未访问）。
          * 右侧显示“控制面板”：开始/暂停、单步、重置按钮，速度滑块（0.5x~2x）。
          * 播放8位风格的轻快背景音乐（如《超级马力欧》的经典旋律）。

    2.  **算法启动与数据初始化**：
          * 输入传递关系数组p，例如p=[5,1,2,4,3]。
          * 选择第一个未访问的节点（如①），将其颜色变为黄色（当前处理），书（一个像素星星）出现在①的位置。

    3.  **核心传递过程演示**：
          * **单步执行**：点击“单步”按钮，书从当前节点①传递到p[1]=5（⑤），⑤变为黄色，①变为绿色（已访问），播放“叮”音效。
          * **自动播放**：调整速度滑块，书自动依次传递：⑤→p[5]=3（③）→③→p[3]=2（②）→②→p[2]=1（①）。每传递一次，当前节点变黄，前一个节点变绿，音效“叮”响起。
          * **环形成提示**：当书回到起点①时，所有环内节点（①、⑤、③、②）变为红色（环高亮），播放“胜利”音效（如《超级马力欧》的吃金币音效），并在屏幕上方显示环的长度“4”。

    4.  **AI自动演示模式**：
          * 点击“AI自动演示”，算法自动处理所有未访问节点，依次展示每个环的形成过程，学习者可以观察整个图的环结构。

    5.  **目标达成/结束状态**：
          * 所有节点处理完成后，背景音乐停止，屏幕显示“所有环已找到！”，并列出每个节点的环长度。

    6.  **旁白提示**：
          * （书传递到⑤时）“看！书从①传到了⑤，⑤现在是当前节点～”
          * （回到①时）“哇！书回到了起点①，说明这里有一个环～环的长度是4天哦！”

<visualization_conclusion>
通过这样一个融合了像素艺术和复古游戏元素的动画，我们不仅能清晰地看到“循环检测”的执行流程，还能在轻松有趣的环境中理解环的形成过程和长度计算逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考“循环检测”的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 循环检测不仅能解决本题，还常用于处理以下场景：
        - **信息传递问题**（如洛谷P2661）：求信息在人群中传递的最小环长度。
        - **置换分解问题**：将排列分解为不相交的循环，用于密码学或数学问题。
        - **游戏角色移动**：角色按固定路径移动，求回到起点的周期。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P2661 信息传递**
          * 🗣️ **推荐理由**：这道题与本题几乎完全相同，是“循环检测”的经典应用，可以帮助你巩固对环长度计算的理解。
    2.  **洛谷 P1967 [NOIP2013 提高组] 货车运输**
          * 🗣️ **推荐理由**：此题涉及图论中的最大生成树和LCA，但核心思想是“路径检测”，能拓展你对图论问题的思考。
    3.  **洛谷 P1330 封锁阳光大学**
          * 🗣️ **推荐理由**：此题需要检测图中是否存在奇环，是循环检测的变形应用，能提升你对环性质的理解。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中，作者盧鋅提到：“虽然这是一个简单题，我还是写较好的形式吧。” 这提醒我们，即使面对简单问题，也要保持严谨的代码风格和优化意识，这对培养良好的编程习惯非常重要。
</insights_intro>

> **参考经验 (来自作者盧鋅)**：“简单难度的话很明显可以写一个N²的算法（每个点暴搜就好了），困难的话对访问加个记忆即可（时间O(N)）。”
>
> **点评**：盧鋅的经验告诉我们，面对不同数据规模时，需要选择合适的算法。简单数据可以用暴力法，但复杂数据必须优化（如标记数组避免重复计算）。这对竞赛中的时间管理非常重要。

-----

<conclusion>
本次关于“Books Exchange (easy version)”的C++解题分析就到这里。希望这份学习指南能帮助大家更好地理解循环检测的算法和编程技巧。记住，编程能力的提升在于持续学习、勤于思考和勇于实践。下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：130.00秒