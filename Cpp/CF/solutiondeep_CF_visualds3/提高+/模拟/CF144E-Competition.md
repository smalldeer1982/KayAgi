# 题目信息

# Competition

## 题目描述

The secondary diagonal of a square matrix is a diagonal going from the top right to the bottom left corner. Let's define an $ n $ -degree staircase as a square matrix $ n×n $ containing no squares above the secondary diagonal (the picture below shows a 5-degree staircase).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144E/e3fce56b75bea8833ad5e51edea79f8a51661523.png)The squares of the $ n $ -degree staircase contain $ m $ sportsmen.

A sportsman needs one second to move to a side-neighboring square of the staircase. Before the beginning of the competition each sportsman must choose one of the shortest ways to the secondary diagonal.

After the starting whistle the competition begins and all sportsmen start moving along the chosen paths. When a sportsman reaches a cell of the secondary diagonal, he stops and moves no more. The competition ends when all sportsmen reach the secondary diagonal. The competition is considered successful if during it no two sportsmen were present in the same square simultaneously. Any square belonging to the secondary diagonal also cannot contain more than one sportsman. If a sportsman at the given moment of time leaves a square and another sportsman comes to it, then they are not considered to occupy the same square simultaneously. Note that other extreme cases (for example, two sportsmen moving towards each other) are impossible as the chosen ways are the shortest ones.

You are given positions of $ m $ sportsmen on the staircase. Your task is to choose among them the maximum number of sportsmen for who the competition can be successful, that is, so that there existed such choice of shortest ways for the sportsmen at which no two sportsmen find themselves in the same square simultaneously. All other sportsmen that are not chosen will be removed from the staircase before the competition starts.

## 说明/提示

A note to the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144E/3d94f14c44e777f4fdd801207cac70018a6b3b0e.png) The picture shows a three-degree staircase. The arrows show the shortest paths that the sportsmen choose.

## 样例 #1

### 输入

```
3 3
2 3
3 2
3 3
```

### 输出

```
3
1 2 3 
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Competition 深入学习指南 💡

<introduction>
今天我们来一起分析“Competition”这道C++编程题。这道题的核心是通过贪心算法选择最多的运动员，使得他们沿最短路径移动时互不冲突。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法 (Greedy Algorithm)

🗣️ **初步分析**：
> 解决“Competition”这道题，关键在于理解并运用贪心算法。贪心算法的核心思想是“每一步选择当前最优解”，最终组合成全局最优解，就像搭积木时每次选最稳的那块，最后搭出最高的塔。在本题中，贪心算法用于选择运动员的终点区间，确保每一步选的终点不会与之前的冲突，从而最大化总人数。

   - **题解思路**：两个题解均将问题转化为“区间调度”问题。每个运动员对应一个可行终点区间（左端点s，右端点t），目标是选最多不重叠的点（每个点代表一个终点）。核心难点在于如何高效选择这些点，确保不冲突。jifbt的题解通过排序+优先队列贪心选右边界最左的区间；Allanljx的题解则按左端点分组，用优先队列维护右端点最小的选项。
   - **核心算法流程**：首先计算每个运动员的s和t（s为左端点，t为右端点），按s排序；然后遍历每个可能的终点位置i，用优先队列维护当前可选的区间（s≤i≤t），每次选t最小的区间，确保后续有更多选择空间。
   - **可视化设计**：采用8位像素风，用不同颜色的方块代表运动员，副对角线用金色像素线标记。动画中，每个运动员的可行区间（s到t）用淡蓝色像素条展示，优先队列的“选t最小”过程用绿色箭头指向当前最优区间，关键操作（如入队、选点）伴随“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下两个题解评分均≥4星，值得重点学习。
</eval_intro>

**题解一：作者jifbt**
* **点评**：此题解思路清晰，将问题巧妙转化为区间调度问题，并通过排序+优先队列高效实现贪心选择。代码规范，变量名（如s、t、i）含义明确；边界处理严谨（如循环中j的递增和队列的弹出）。算法时间复杂度为O(m log m)，适合竞赛场景。亮点在于利用优先队列动态维护可选区间，确保每次选右边界最左的区间，最大化后续选择空间。

**题解二：作者Allanljx**
* **点评**：此题解同样采用贪心策略，按左端点分组后用优先队列维护右端点最小的区间。代码简洁，逻辑直接（如t数组存储左端点对应的区间），变量名（x、y、ans1）易于理解。算法核心与jifbt一致，但实现方式更侧重按左端点分组处理，适合理解区间调度的不同实现角度。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个核心难点。结合优质题解的共性，我为大家提炼了思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何确定每个运动员的可行终点区间？
    * **分析**：每个运动员的最短路径只能往左或往上走，因此其终点在副对角线上的位置（记为k）需满足：从起点(x,y)到(k, n+1−k)的最短距离（x−k + y−(n+1−k) = x+y−n−1）是固定的。因此，k的取值范围是max(1, x+y−n) ≤k ≤min(n, x)（左端点s=max(1, x+y−n)，右端点t=min(n, x)）。优质题解通过坐标变换（如jifbt的a[i]={n+1−x,y,i}）快速计算s和t。
    * 💡 **学习笔记**：最短路径的终点区间由起点坐标的x和y决定，需结合矩阵边界（1和n）确定有效范围。

2.  **关键点2**：如何高效选择不冲突的终点？
    * **分析**：冲突的条件是两个运动员的终点区间重叠且选中同一k。贪心策略选择右边界t最小的区间，可最大化后续选择空间。jifbt的题解通过排序s，并用优先队列维护当前可选的区间（s≤i≤t），每次选t最小的，确保每一步最优。
    * 💡 **学习笔记**：区间调度问题中，按左端点排序+优先队列选右端点最小，是经典贪心策略。

3.  **关键点3**：如何处理优先队列的动态维护？
    * **分析**：遍历每个可能的终点i时，需将所有s≤i的区间加入队列，并移除t<i的无效区间（因k=i时这些区间的t<i，无法选i）。jifbt的代码通过while循环处理j的递增和队列的弹出，确保队列始终包含当前可选的区间。
    * 💡 **学习笔记**：优先队列是动态维护候选集的高效工具，需注意入队和出队的条件。

### ✨ 解题技巧总结
<summary_best_practices>
-   **问题抽象**：将实际问题（运动员移动冲突）抽象为数学模型（区间调度），是解决复杂问题的关键。
-   **坐标变换**：通过调整坐标（如jifbt的n+1−x）简化计算，使s和t的推导更直观。
-   **优先队列的应用**：在需要动态选择最优元素（如最小t）时，优先队列能显著降低时间复杂度。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解的通用核心C++实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了jifbt和Allanljx的题解思路，采用排序+优先队列的贪心策略，清晰实现区间调度。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    struct Athlete {
        int s; // 左端点
        int t; // 右端点
        int idx; // 原始编号
    };

    int main() {
        int n, m;
        cin >> n >> m;
        vector<Athlete> athletes(m);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            // 计算s和t：s = max(1, x + y - n), t = min(n, x)
            athletes[i].s = max(1, x + y - n);
            athletes[i].t = min(n, x);
            athletes[i].idx = i + 1; // 题目中编号从1开始
        }

        // 按左端点s升序排序
        sort(athletes.begin(), athletes.end(), [](const Athlete& a, const Athlete& b) {
            return a.s < b.s;
        });

        priority_queue<Athlete, vector<Athlete>, function<bool(Athlete, Athlete)>> pq(
            [](const Athlete& a, const Athlete& b) { return a.t > b.t; } // 小根堆（t小的优先）
        );

        vector<int> selected;
        int j = 0;
        for (int i = 1; i <= n; ++i) { // 遍历每个可能的终点k=i
            // 将s<=i的运动员加入队列
            while (j < m && athletes[j].s <= i) {
                pq.push(athletes[j]);
                ++j;
            }
            // 移除t<i的无效区间（无法选k=i）
            while (!pq.empty() && pq.top().t < i) {
                pq.pop();
            }
            // 选择t最小的区间（当前最优）
            if (!pq.empty()) {
                selected.push_back(pq.top().idx);
                pq.pop();
            }
        }

        cout << selected.size() << endl;
        for (int idx : selected) {
            cout << idx << " ";
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入，计算每个运动员的s和t；然后按s排序，用优先队列动态维护当前可选的区间（s≤i≤t）；遍历每个可能的终点k=i时，加入s≤i的区间，移除t<i的无效区间，选择t最小的区间作为当前终点。最终输出选中的运动员编号。

---
<code_intro_selected>
接下来，我们剖析两个优质题解的核心代码片段，理解其亮点和逻辑。
</code_intro_selected>

**题解一：作者jifbt**
* **亮点**：通过坐标变换（n+1−x）简化s和t的计算，优先队列按t大顶堆（实际用小顶堆逻辑）实现贪心选择。
* **核心代码片段**：
    ```cpp
    rp(i,1,m){int x,y;rd(x,y);a[i]={n+1-x,y,i};}
    sort(a+1,a+m+1,[](const T&a,const T&b){return a.s<b.s;});
    int j=1;
    rp(i,1,n){
        while(a[j].s==i)q.push(a[j]),++j;
        if(!q.empty())v.push_back(q.top().i),q.pop();
        while(!q.empty()&&q.top().t==i)q.pop();
    }
    ```
* **代码解读**：
    > 第一行将输入的x坐标转换为n+1−x（对应s的计算），y作为t；第二行按s排序；第三行遍历i（终点k=i），将s=i的运动员入队；若队列非空，选队首（t最小）加入结果；最后移除t=i的区间（避免重复选）。这里的q是大顶堆（因operator<定义为a.t>b.t），队首是t最小的。
* 💡 **学习笔记**：坐标变换能简化数学推导，优先队列的比较函数需注意方向（大顶堆/小顶堆）。

**题解二：作者Allanljx**
* **亮点**：按左端点分组存储，用优先队列直接维护右端点最小的区间，代码简洁。
* **核心代码片段**：
    ```cpp
    t[n-y[i]+1].push_back(mp(x[i],i));
    for(int i=1;i<=n;i++){
        for(int j=0;j<t[i].size();j++){
            q.push(t[i][j]);
        }
        while(q.size()&&q.top().first<i) q.pop();
        if(q.size()){
            ans1[++ans]=q.top().second;
            q.pop();
        }
    }
    ```
* **代码解读**：
    > 第一行将左端点s=n−y[i]+1（对应s= x+y−n的变形）存入t数组；第二行遍历i（终点k=i），将s=i的区间入队；第三行移除左端点< i的无效区间；若队列非空，选右端点最小的（q.top().first是x[i]即t）加入结果。这里的q是小顶堆（greater<pair<int,int>>），队首是t最小的。
* 💡 **学习笔记**：按左端点分组存储，能减少排序步骤，适合理解区间调度的另一种实现方式。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解贪心选择过程，我们设计一个“像素探险家”主题的8位动画，模拟运动员的区间选择和移动过程。
</visualization_intro>

  * **动画演示主题**：像素迷宫中的终点争夺战  
  * **核心演示内容**：展示每个运动员的可行区间（s到t），贪心算法如何选择t最小的区间，确保无冲突。

  * **设计思路简述**：  
    采用8位像素风（FC红白机色调），用不同颜色方块代表运动员（如红色），副对角线用金色像素线标记。动画通过“入队”“选点”“移动”等步骤，配合音效和文字提示，直观展示贪心策略的每一步。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕左侧显示n×n的阶梯矩阵（副对角线金色），右侧显示优先队列（像素方块堆叠）。  
        - 控制面板：开始/暂停、单步、重置按钮；速度滑块（1-5倍速）。  
        - 播放8位风格背景音乐（如《超级玛丽》经典旋律）。

    2.  **输入与区间计算**：  
        - 每个运动员的起点（x,y）用红色像素点标出，其可行区间（s到t）用淡蓝色像素条从s到t延伸（如s=2, t=4则覆盖k=2,3,4）。  
        - 文字提示：“每个探险家的可行终点区间是[s, t]哦！”

    3.  **排序与入队**：  
        - 按s升序排序，运动员依次“滑入”队列区（音效：“唰”）。  
        - 队列区显示当前可选的运动员（淡蓝色像素条），t值用白色数字标注。

    4.  **贪心选择**（单步/自动模式）：  
        - 遍历k=1到n，当前k用绿色箭头标记。  
        - 将s≤k的运动员“弹入”队列（音效：“叮”），t<k的运动员“弹出”队列（音效：“噗”）。  
        - 队列顶部的运动员（t最小）用黄色高亮，被选中后“飞”到k位置（音效：“呜~”），k位置用绿色标记。  
        - 文字提示：“选t最小的探险家，这样后面有更多选择空间！”

    5.  **冲突检测**：  
        - 若两个运动员的区间重叠且未被选中，用红色闪烁提示“冲突可能”；若被选中则无闪烁。

    6.  **结束状态**：  
        - 所有选中的运动员到达副对角线（金色闪烁），播放胜利音效（“啦~”），显示总人数和编号。  
        - 未选中的运动员“消失”（淡入淡出效果）。

  * **旁白提示**：  
    - “看！这个探险家的区间是[2,4]，他可以选k=2、3、4哦~”  
    - “现在k=3，我们选t最小的探险家（t=3），这样后面k=4还能选其他探险家！”

<visualization_conclusion>
通过这个像素动画，我们能清晰看到贪心算法如何一步步选择最优终点，避免冲突，从而最大化运动员数量。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
贪心算法在区间调度问题中应用广泛，以下是一些相似场景和练习推荐：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    贪心算法的“每一步最优”思想还可用于：  
    - 活动选择问题（选最多不重叠活动）；  
    - 任务调度（按截止时间排序，选最早截止的）；  
    - 区间覆盖（选覆盖当前点且右端点最大的区间）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1803** - 线段覆盖  
          * 🗣️ **推荐理由**：经典区间调度问题，巩固贪心选右端点最小的策略。
    2.  **洛谷 P2081** - 绿豆蛙的归宿  
          * 🗣️ **推荐理由**：结合图论与贪心，思考如何用贪心优化路径选择。
    3.  **洛谷 P1090** - 合并果子  
          * 🗣️ **推荐理由**：用优先队列实现贪心，选择最小两堆合并，与本题队列应用类似。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分。但根据解题过程，我们可以总结：遇到复杂问题时，先抽象为数学模型（如本题的区间调度），再选择合适的算法（如贪心），最后用数据结构（如优先队列）高效实现，是解决编程题的通用思路。
</insights_intro>

-----

<conclusion>
本次关于“Competition”的C++解题分析就到这里。希望这份指南能帮助大家理解贪心算法的应用，并掌握区间调度问题的解决方法。记住，多动手写代码、画流程图，是提升算法能力的关键！下次见~ 💪
</conclusion>

---
处理用时：120.16秒