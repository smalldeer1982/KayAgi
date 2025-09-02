# 题目信息

# DeadLee

## 题目描述

Lee bought some food for dinner time, but Lee's friends eat dinner in a deadly way. Lee is so scared, he doesn't want to die, at least not before seeing Online IOI 2020...

There are $ n $ different types of food and $ m $ Lee's best friends. Lee has $ w_i $ plates of the $ i $ -th type of food and each friend has two different favorite types of food: the $ i $ -th friend's favorite types of food are $ x_i $ and $ y_i $ ( $ x_i \ne y_i $ ).

Lee will start calling his friends one by one. Whoever is called will go to the kitchen and will try to eat one plate of each of his favorite food types. Each of the friends will go to the kitchen exactly once.

The only problem is the following: if a friend will eat at least one plate of food (in total) then he will be harmless. But if there is nothing left for him to eat (neither $ x_i $ nor $ y_i $ ), he will eat Lee instead $ \times\_\times $ .

Lee can choose the order of friends to call, so he'd like to determine if he can survive dinner or not. Also, he'd like to know the order itself.

## 说明/提示

In the first example, any of the following orders of friends are correct : $ [1, 3, 2] $ , $ [3, 1, 2] $ , $ [2, 3, 1] $ , $ [3, 2, 1] $ .

In the second example, Lee should call the second friend first (the friend will eat a plate of food $ 1 $ ) and then call the first friend (the friend will eat a plate of food $ 2 $ ). If he calls the first friend sooner than the second one, then the first friend will eat one plate of food $ 1 $ and food $ 2 $ and there will be no food left for the second friend to eat.

## 样例 #1

### 输入

```
3 3
1 2 1
1 2
2 3
1 3```

### 输出

```
ALIVE
3 2 1```

## 样例 #2

### 输入

```
3 2
1 1 0
1 2
1 3```

### 输出

```
ALIVE
2 1```

## 样例 #3

### 输入

```
4 4
1 2 0 1
1 3
1 2
2 3
2 4```

### 输出

```
ALIVE
1 3 2 4```

## 样例 #4

### 输入

```
5 5
1 1 1 2 1
3 4
1 2
2 3
4 5
4 5```

### 输出

```
ALIVE
5 4 1 3 2```

## 样例 #5

### 输入

```
4 10
2 4 1 4
3 2
4 2
4 1
3 1
4 1
1 3
3 2
2 1
3 1
2 4```

### 输出

```
DEAD```

# AI分析结果

---
# 💡 Kay的C++算法解析：DeadLee 深入学习指南 💡

<introduction>
今天我们来一起分析“DeadLee”这道C++编程题。这道题需要我们判断Lee能否通过调整朋友的顺序，让所有朋友至少吃到一种喜欢的食物，避免被吃掉。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法与拓扑排序结合的应用

🗣️ **初步分析**：
解决“DeadLee”的关键在于逆向思考——先假设所有朋友都吃掉两种食物，再通过贪心策略逐步调整。贪心算法的核心思想是“每一步选择当前最优的局部解”，就像整理书架时先把容易归类的书放好，再处理复杂的。本题中，我们需要优先处理那些“无论如何都不会让食物不够”的朋友，确保他们的顺序不影响后续选择。

- **题解思路**：所有优质题解均采用类似拓扑排序的贪心策略：初始时计算每种食物被“假设吃掉”后的剩余量（`w[i]`），若某食物剩余量≥0（说明关联的朋友吃它不会不够），则将这些朋友加入队列，调整另一种食物的剩余量，并重复此过程。若最终能处理所有朋友，输出顺序；否则输出“DEAD”。
- **核心难点**：如何逆向确定朋友的处理顺序，确保每一步选择的朋友不会导致后续无法满足条件。
- **可视化设计**：用8位像素风格展示食物（绿色方块表示剩余足够，红色表示不足），朋友用像素小人表示。当处理一个朋友时，对应食物的方块闪烁并调整数值，队列用像素堆叠的方块动态展示，关键步骤伴随“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，我为大家筛选了以下3份优质题解：
</eval_intro>

**题解一：作者：7KByte**
* **点评**：此题解逻辑清晰，通过邻接表存储朋友与食物的关系，队列处理拓扑排序。代码变量名如`sta`（存储答案顺序）、`del`（标记已处理朋友）含义明确，边界处理严谨（如初始化`w[i]`为原始值减去所有关联朋友的数量）。亮点在于逆向处理朋友顺序，通过队列逐步调整食物剩余量，最终倒序输出答案。

**题解二：作者：chen_qian**
* **点评**：此题解将问题转化为“需求数”的贪心调整，用`vector`存储邻接表，队列维护可处理的食物。变量`stk`（栈存储答案）设计巧妙，通过标记`vis`数组避免重复处理朋友。亮点在于将“需求数”与食物剩余量直接对比，逻辑简洁，易于理解。

**题解三：作者：Caro23333**
* **点评**：此题解代码规范，使用`readint`优化输入，变量`sum`（记录每种食物的需求数）、`col`（记录朋友选择的食物）含义清晰。亮点在于通过维护`col`数组明确朋友选择的食物，确保调整需求数时的准确性，算法流程与拓扑排序高度契合。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的过程中，我们需要重点突破以下核心难点：
</difficulty_intro>

1.  **关键点1**：如何逆向确定朋友的处理顺序？
    * **分析**：直接正向安排顺序难以处理“朋友吃两种食物”的依赖关系。优质题解采用逆向思路：先假设所有朋友都吃两种食物（初始`w[i] -= 朋友数`），再找出剩余量≥0的食物（说明关联朋友吃它不会不够），将这些朋友加入队列，并调整另一种食物的剩余量（因为朋友不再需要另一种食物）。
    * 💡 **学习笔记**：逆向思考能将复杂的依赖关系转化为可逐步处理的局部问题。

2.  **关键点2**：如何维护食物的剩余量并调整？
    * **分析**：当处理一个朋友时，他选择的食物已满足需求，因此另一种食物的需求数需减1（因为朋友不再需要它）。若另一种食物的剩余量因此变为≥0，则将其关联的朋友加入队列，继续处理。
    * 💡 **学习笔记**：维护队列动态调整剩余量，是贪心策略的核心操作。

3.  **关键点3**：如何构造最终的朋友顺序？
    * **分析**：处理朋友时按队列顺序存入数组（或栈），最终倒序输出即为可行顺序。这是因为先处理的朋友应放在后面，避免消耗其他食物的资源。
    * 💡 **学习笔记**：倒序输出确保先处理的朋友不影响后续选择。

### ✨ 解题技巧总结
<summary_best_practices>
- **逆向思维**：将“安排顺序”转化为“逆向调整剩余量”，简化依赖关系。
- **队列维护**：用队列动态处理可安全安排的朋友，确保每一步选择最优。
- **标记数组**：用`vis`或`del`数组避免重复处理朋友，保证算法效率。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，提炼一个通用的核心C++实现，帮助大家把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了7KByte、chen_qian等题解的思路，采用队列维护可处理的食物，邻接表存储朋友与食物的关系，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int MAXN = 200005;
    int n, m, w[MAXN];
    vector<pair<int, int>> g[MAXN]; // 邻接表存储（食物，朋友编号）
    bool vis[MAXN]; // 标记朋友是否已处理
    int ans[MAXN], tot;

    int main() {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
        for (int i = 1; i <= m; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            g[x].emplace_back(y, i);
            g[y].emplace_back(x, i);
            w[x]--; w[y]--; // 初始假设朋友吃两种食物
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i)
            if (w[i] >= 0) q.push(i); // 剩余量≥0的食物入队

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, idx] : g[u]) {
                if (!vis[idx]) {
                    vis[idx] = true;
                    ans[++tot] = idx; // 记录处理顺序
                    w[v]++; // 朋友不再需要另一种食物，剩余量+1
                    if (w[v] == 0) q.push(v); // 若剩余量变为0，入队
                }
            }
        }

        if (tot < m) puts("DEAD");
        else {
            puts("ALIVE");
            for (int i = tot; i >= 1; --i) printf("%d ", ans[i]);
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入并初始化每种食物的剩余量（初始假设所有朋友都吃两种食物）。然后将剩余量≥0的食物加入队列，处理其关联的朋友：标记朋友已处理，调整另一种食物的剩余量，若剩余量变为0则入队。最终若处理所有朋友，倒序输出顺序；否则输出“DEAD”。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，理解其亮点和实现思路。
</code_intro_selected>

**题解一：作者：7KByte**
* **亮点**：使用邻接表存储边，队列处理拓扑排序，代码简洁高效。
* **核心代码片段**：
    ```cpp
    rep(i,1,n)if(w[i]>=0)q.push(i),v[i]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=h[x];i;i=e[i].nxt)if(!del[e[i].val]){
            del[e[i].val]=1;sta[++top]=e[i].val;
            w[e[i].to]++;
            if(w[e[i].to]==0)q.push(e[i].to);
        }
    }
    ```
* **代码解读**：
    > 这段代码是拓扑排序的核心。首先将剩余量≥0的食物（`w[i]>=0`）加入队列（`q`）。然后循环处理队列中的食物（`x`），遍历其关联的朋友（`e[i].val`），若未处理（`!del[e[i].val]`）则标记为已处理（`del[e[i].val]=1`），并记录到`sta`数组。调整另一种食物的剩余量（`w[e[i].to]++`），若剩余量变为0则入队，继续处理。
* 💡 **学习笔记**：队列维护可处理的食物，确保每一步选择的朋友不会导致后续无法满足条件。

**题解二：作者：chen_qian**
* **亮点**：用`vector`存储邻接表，`stk`栈存储答案，逻辑清晰。
* **核心代码片段**：
    ```cpp
    queue<int> q;
    for(int i=1;i<=N-2;i++)
        if(t[i]<=w[i]&&t[i]) q.push(i);
    while(!q.empty()){
        int x=q.front(); q.pop();
        for(int i=0;i<v[x].size();i++){
            pair<int,int> now=v[x][i];
            if(!vis[now.second]){
                vis[now.second]=1;
                stk[++top]=now.second;
                if(--t[now.first]<=w[now.first])
                    q.push(now.first);
            }
        }
    }
    ```
* **代码解读**：
    > 这段代码中，`t[i]`表示食物`i`的需求数。初始将需求数≤剩余量（`t[i]<=w[i]`）的食物入队。处理队列中的食物（`x`）时，遍历其关联的朋友（`now.second`），若未处理（`!vis[now.second]`）则标记并压入栈（`stk`），调整另一种食物的需求数（`--t[now.first]`），若满足条件则入队。
* 💡 **学习笔记**：需求数的调整是贪心策略的关键，确保每一步处理的朋友不会破坏后续条件。

**题解三：作者：Caro23333**
* **亮点**：用`col`数组记录朋友选择的食物，明确调整方向。
* **核心代码片段**：
    ```cpp
    while(front<rear){
        int u = q[front++];
        ans[++tot] = u;
        if(x[u]!=col[u])
            swap(x[u],y[u]);
        sum[y[u]]--;
        if(sum[y[u]]<=w[y[u]]&&!vis[y[u]]){
            vis[y[u]] = 1;
            for(int i = 0; i<p[y[u]].size(); i++)
                if(!col[p[y[u]][i]])
                    col[p[y[u]][i]] = y[u], q[rear++] = p[y[u]][i];
        }
    }
    ```
* **代码解读**：
    > 这段代码中，`col[u]`表示朋友`u`选择的食物。处理队列中的朋友（`u`）时，调整另一种食物的需求数（`sum[y[u]]--`），若该食物的需求数≤剩余量且未被标记（`!vis[y[u]]`），则将其关联的朋友入队，并记录选择的食物（`col[p[y[u]][i]] = y[u]`）。
* 💡 **学习笔记**：明确朋友选择的食物，确保需求数调整的准确性。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解贪心策略和拓扑排序的过程，我设计了一个“像素餐厅”主题的动画演示，让我们一起“看”到算法如何工作！
</visualization_intro>

  * **动画演示主题**：像素餐厅大作战——Lee的朋友顺序大调整

  * **核心演示内容**：展示食物剩余量的变化、朋友的处理顺序，以及队列如何动态调整。关键步骤包括：食物初始化、队列处理朋友、剩余量调整、最终顺序输出。

  * **设计思路简述**：采用8位像素风格（FC游戏画面），用不同颜色的像素方块表示食物（绿色：剩余足够，红色：剩余不足），朋友用戴帽子的像素小人表示。关键操作（如朋友入队、剩余量调整）伴随“叮”的音效，完成所有朋友处理时播放“胜利”音效，增强趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化 (8位像素风)**：
          * 屏幕左侧展示`n`个食物方块（每个方块标注食物编号和剩余量），右侧展示`m`个朋友小人（标注编号）。
          * 底部控制面板包含“开始”“暂停”“单步”“重置”按钮和速度滑块。
          * 播放8位风格的轻快背景音乐（如《超级马里奥》主题变奏）。

    2.  **食物初始化**：
          * 每个食物方块的初始剩余量为`w[i] - 关联朋友数`（初始假设所有朋友都吃两种食物）。绿色方块表示剩余量≥0，红色表示<0。
          * 队列区域（屏幕上方）用像素堆叠的方块展示初始可处理的食物（绿色方块入队）。

    3.  **核心处理过程**：
          * **处理队列中的食物**：队列头部的绿色食物方块“弹出”，对应的朋友小人被选中（黄色高亮）。
          * **朋友入栈**：选中的朋友小人被移动到“答案栈”区域（屏幕右侧），伴随“入栈”音效（短“叮”声）。
          * **剩余量调整**：另一种食物的方块剩余量+1（数值更新），若变为0则从红色变为绿色，并“滑入”队列。
          * **逻辑判断提示**：当剩余量调整后，屏幕下方弹出文字提示：“朋友X已处理，食物Y的剩余量变为Z！”

    4.  **AI自动演示模式**：
          * 点击“AI演示”按钮，算法自动执行，朋友小人按处理顺序自动移动，队列和剩余量动态更新，学习者可观察完整流程。

    5.  **结果展示**：
          * 若所有朋友被处理（答案栈填满），播放“胜利”音效（长“啦”声），所有朋友小人欢呼（像素星星闪烁）。
          * 若无法处理所有朋友（答案栈未填满），播放“失败”音效（短“咚”声），红色食物方块闪烁提示问题所在。

  * **旁白提示**：
      * （初始化时）“看！每个食物的剩余量已经计算好啦，绿色表示足够，红色表示不够～”
      * （处理朋友时）“现在处理食物X的朋友，他们被放到后面，不会影响其他食物的选择哦！”
      * （调整剩余量时）“朋友Y选择了食物X，所以食物Z的剩余量增加了，可能可以处理更多朋友啦！”

<visualization_conclusion>
通过这个像素动画，我们能清晰看到贪心策略如何一步步调整朋友顺序，确保Lee的安全。下次遇到类似问题，你也可以想象自己在玩这个小游戏，轻松找到解题思路！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的贪心+拓扑排序思路后，我们可以尝试解决更多类似问题，巩固这一技巧。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 贪心+拓扑排序的策略适用于需要“逐步确定顺序”且存在依赖关系的问题，例如：任务调度（任务A依赖任务B，需先完成B）、课程安排（课程A是课程B的先修课）、资源分配（资源有限时优先满足某些需求）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1347** - 排序
          * 🗣️ **推荐理由**：考察拓扑排序的基本应用，需判断是否能唯一确定序列，适合巩固拓扑排序的基础。
    2.  **洛谷 P3916** - 图的遍历
          * 🗣️ **推荐理由**：需要逆向处理图，用贪心策略标记每个点能到达的最大节点，与本题逆向思维类似。
    3.  **洛谷 P2746** - 校园网（Tarjan+拓扑排序）
          * 🗣️ **推荐理由**：结合强连通分量和拓扑排序，适合提升复杂图论问题的解决能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了解题时的经验，这些对我们很有启发：
</insights_intro>

> **参考经验 (来自7KByte)**：“VP的时候被当场降智。。。”（注：VP指虚拟参赛）作者提到初始时没有想到逆向处理，后来通过观察食物剩余量的变化找到思路。
>
> **点评**：遇到复杂问题时，逆向思考往往能打开思路。就像本题，直接安排顺序困难，但逆向调整剩余量却能简化问题。这提醒我们，当正向无法突破时，不妨尝试逆向分析。

-----

<conclusion>
本次关于“DeadLee”的C++解题分析就到这里。希望这份指南能帮助你理解贪心+拓扑排序的应用，掌握逆向思考的技巧。记住，编程的关键在于多练习、多总结，下次我们再一起挑战新的算法题！💪
</conclusion>

---
处理用时：512.60秒