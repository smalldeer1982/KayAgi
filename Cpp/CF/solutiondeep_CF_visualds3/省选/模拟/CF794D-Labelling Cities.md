# 题目信息

# Labelling Cities

## 题目描述

Oleg the bank client lives in Bankopolia. There are $ n $ cities in Bankopolia and some pair of cities are connected directly by bi-directional roads. The cities are numbered from $ 1 $ to $ n $ . There are a total of $ m $ roads in Bankopolia, the $ i $ -th road connects cities $ u_{i} $ and $ v_{i} $ . It is guaranteed that from each city it is possible to travel to any other city using some of the roads.

Oleg wants to give a label to each city. Suppose the label of city $ i $ is equal to $ x_{i} $ . Then, it must hold that for all pairs of cities $ (u,v) $ the condition $ |x_{u}-x_{v}|<=1 $ holds if and only if there is a road connecting $ u $ and $ v $ .

Oleg wonders if such a labeling is possible. Find an example of such labeling if the task is possible and state that it is impossible otherwise.

## 说明/提示

For the first sample, $ x_{1}=2 $ , $ x_{2}=3 $ , $ x_{3}=x_{4}=1 $ is a valid labeling. Indeed, $ (3,4) $ , $ (1,2) $ , $ (1,3) $ , $ (1,4) $ are the only pairs of cities with difference of labels not greater than $ 1 $ , and these are precisely the roads of Bankopolia.

For the second sample, all pairs of cities have difference of labels not greater than $ 1 $ and all pairs of cities have a road connecting them.

For the last sample, it is impossible to construct a labeling satisfying the given constraints.

## 样例 #1

### 输入

```
4 4
1 2
1 3
1 4
3 4
```

### 输出

```
YES
2 3 1 1 
```

## 样例 #2

### 输入

```
5 10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
5 4
```

### 输出

```
YES
1 1 1 1 1 
```

## 样例 #3

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
NO
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Labelling Cities 深入学习指南 💡

<introduction>
今天我们来一起分析“Labelling Cities”这道C++编程题。这道题要求我们为图中的每个城市分配标签，使得两个城市有边当且仅当它们的标签差不超过1。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：图论（分层图验证与构造）

🗣️ **初步分析**：
解决“Labelling Cities”的关键在于将图的结构转化为分层模型。简单来说，我们需要将城市分成若干层，同一层内的城市标签相同，相邻层的标签差1。这样的分层模型需要满足：同一层内的城市两两相连（完全图），相邻层的城市也两两相连（完全二分图）。这就像给城市“建高楼”，每一层的居民（城市）标签相同，上下层的居民标签差1，且同一层和相邻层的居民必须互相认识（有边）。

- **题解思路**：多数题解采用“分层验证”策略：首先通过BFS或邻居集合哈希确定分层结构，然后验证该结构是否满足原图的边数和连接关系。例如，wishapig的题解通过两次BFS分层，天命之路的题解通过邻居集合缩点后分析新图结构。
- **核心难点**：如何正确分层（确定层内和层间的连接关系），以及如何验证分层后的边数与原图一致。
- **可视化设计**：计划采用8位像素风格，用不同颜色的像素块表示不同层（如红色层标签1，蓝色层标签2），动画展示分层过程（如BFS扩展层）、层内完全图（像素块间闪烁连线）、层间完全二分图（跨层像素块连线）。关键步骤高亮当前处理的层或边，音效提示“入队”“边验证”等操作。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等方面筛选了以下优质题解：
</eval_intro>

**题解一：来源：wishapig**
* **点评**：这份题解思路非常清晰！作者通过两次BFS确定分层结构，并验证边数是否匹配，时间复杂度为线性，适合处理大规模数据（n≤3e5）。代码规范（变量名如`d1`、`d2`表示BFS距离，`siz`记录层大小），边界处理严谨（特判完全图情况）。亮点在于分层策略的巧妙设计——利用BFS最大距离点确定分层起点，再结合两次BFS结果分层，避免了复杂的数学推导。

**题解二：来源：天命之路**
* **点评**：此题解通过“邻居集合相同则标签相同”的性质，将原图缩点为新图，分析新图的度数限制（度数≤2）。思路巧妙，利用图的结构特性（链或环）判断是否有解，代码中使用`set`处理邻接关系，逻辑清晰。亮点在于将问题转化为新图的结构验证，降低了问题复杂度。

**题解三：来源：_fairytale_**
* **点评**：此题解采用异或哈希快速判断邻居集合是否相同，缩点后分析新图度数，与天命之路思路类似但实现更简洁（使用`gp_hash_table`哈希）。代码中`dfs`遍历链结构并分配标签，逻辑直接。亮点在于哈希方法的高效性，适合处理大规模数据。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于分层结构的确定与验证，结合优质题解的共性，我们提炼以下关键点：
</difficulty_intro>

1.  **关键点1：如何确定分层结构？**
    * **分析**：分层的核心是让同一层内的城市标签相同，相邻层标签差1。wishapig的题解通过两次BFS找到最大距离点作为分层起点，天命之路的题解通过邻居集合缩点，本质都是找到“层”的边界。例如，若BFS最大距离≥2，说明存在至少3层；若≤1，可能是完全图或特殊分层。
    * 💡 **学习笔记**：分层的关键是找到“层”的代表点（如BFS的最大距离点），并确保层内和层间的连接关系符合要求。

2.  **关键点2：如何验证分层的正确性？**
    * **分析**：分层后需验证两点：①原图中每条边的两个端点必须在同一层或相邻层（标签差≤1）；②分层后的总边数（层内完全图边数+层间完全二分图边数）必须等于原图边数。例如，wishapig的题解通过`cnt`变量计算理论边数，与输入`m`比较。
    * 💡 **学习笔记**：边数验证是分层正确性的“硬指标”，必须精确计算。

3.  **关键点3：如何处理特殊情况（如完全图）？**
    * **分析**：完全图的所有城市两两相连，因此所有标签必须相同（标签差≤1对所有点成立）。题解中特判完全图（边数等于n*(n-1)/2），直接输出全1标签。
    * 💡 **学习笔记**：特殊情况的处理能简化问题，需优先考虑。

### ✨ 解题技巧总结
- **问题转化**：将标签约束转化为图的分层结构，利用分层的完全图和完全二分图性质简化问题。
- **哈希与缩点**：通过邻居集合哈希（如异或哈希）快速判断哪些点应处于同一层，降低问题复杂度。
- **边数验证**：分层后计算理论边数，与原图边数对比，确保分层正确。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们选择wishapig的题解作为通用核心实现，因其思路清晰、代码高效，适合大规模数据。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了wishapig题解的思路，通过两次BFS分层并验证边数，适用于大规模图的处理。
* **完整核心代码**：
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=3e5+5;
    int n,m,u,v,mx,pos; long long cnt;
    int Eu[N],Ev[N],id[N],siz[N],d1[N],d2[N],deg[N];
    queue<int> q;
    vector<int> G[N];
    void GG(){ puts("NO"); exit(0); }
    void BFS(int s, int* d){
        q.push(s); d[s]=0;
        while (!q.empty()){
            int u=q.front(); q.pop();
            for (int v:G[u]) if (d[v]==-1) d[v]=d[u]+1,q.push(v);
        }
    }
    int main(){
        scanf("%d%d",&n,&m);
        for (int i=1; i<=m; i++){
            scanf("%d%d",&u,&v); Eu[i]=u,Ev[i]=v;
            G[u].push_back(v),G[v].push_back(u);
            deg[u]++,deg[v]++;
        }
        // 特判完全图
        if (m==1ll*n*(n-1)/2){
            puts("YES");
            for (int i=1; i<=n; i++) printf("1 ");
            return 0;
        }
        memset(d1,-1,sizeof(d1));
        BFS(1,d1);
        for (int i=1; i<=n; i++) if (d1[i]>d1[pos]) pos=i;
        if (d1[pos]>=2){ // 分层处理
            memset(d2,-1,sizeof(d2));
            BFS(pos,d2);
            for (int i=1; i<=n; i++) 
                id[i]=d2[i]>=2?d2[i]+1:(d1[i]==d1[pos]?1:2);
        } else { // 处理小距离情况
            for (int i=1; i<=n; i++) if (deg[i]==n-1) id[i]=2;
            for (int i=1; i<=n; i++) if (!id[i]) { fill(id+1,id+n+1,3); break; }
        }
        // 验证边是否在相邻层
        for (int i=1; i<=m; i++) 
            if (abs(id[Eu[i]]-id[Ev[i]])>1) GG();
        // 验证边数
        for (int i=1; i<=n; i++) siz[id[i]]++,mx=max(mx,id[i]);
        for (int i=1; i<=mx; i++) 
            cnt+=1ll*siz[i]*(siz[i]-1)/2+1ll*siz[i]*siz[i-1];
        if (cnt!=m) GG();
        puts("YES");
        for (int i=1; i<=n; i++) printf("%d ",id[i]);
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取输入并构建图，特判完全图情况。通过两次BFS确定分层（`d1`和`d2`数组记录距离），然后验证每条边是否在相邻层，并计算分层后的理论边数是否与输入一致。最后输出标签或判定无解。

---
<code_intro_selected>
接下来分析wishapig题解的核心代码片段：
</code_intro_selected>

**题解一：来源：wishapig**
* **亮点**：通过两次BFS分层，线性时间复杂度，处理大规模数据高效；特判完全图简化问题。
* **核心代码片段**：
    ```cpp
    if (d1[pos]>=2){ 
        memset(d2,-1,sizeof(d2));
        BFS(pos,d2);
        for (int i=1; i<=n; i++) 
            id[i]=d2[i]>=2?d2[i]+1:(d1[i]==d1[pos]?1:2);
    } else { 
        for (int i=1; i<=n; i++) if (deg[i]==n-1) id[i]=2;
        for (int i=1; i<=n; i++) if (!id[i]) { fill(id+1,id+n+1,3); break; }
    }
    ```
* **代码解读**：这段代码处理分层逻辑。当BFS最大距离≥2时，以最大距离点为起点再次BFS（`d2`数组），根据`d2`的值分层（如`d2[i]>=2`对应高层）；若最大距离≤1，则通过度数判断中间层（度数为n-1的点），剩余点分为其他层。这样分层确保了层内和层间的连接关系。
* 💡 **学习笔记**：BFS是确定分层结构的有效工具，两次BFS能更准确地划分层边界。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解分层过程和边验证，我们设计一个“像素城市分层”动画，用8位像素风格展示城市分层和边连接。
</visualization_intro>

  * **动画演示主题**：像素城市分层大挑战！
  * **核心演示内容**：展示BFS分层过程、层内完全图（同一颜色像素块间连线）、层间完全二分图（相邻颜色像素块间连线），并验证边数是否匹配。
  * **设计思路简述**：8位像素风（红、蓝、绿等8色调色板）营造复古氛围；像素块颜色代表层（红色层1，蓝色层2，绿色层3）；关键操作（如BFS入队、边验证）用闪烁和音效提示，增强记忆点。

  * **动画帧步骤与交互关键点**：
    1. **场景初始化**：屏幕左侧显示像素网格（n个小方块），右侧显示控制面板（开始/暂停、单步、速度滑块）。背景音乐为8位风格的轻快旋律。
    2. **BFS分层**：起点（黄色方块）入队，伴随“叮”音效。BFS扩展时，相邻方块按距离变色（如距离0→红色，距离1→蓝色，距离2→绿色）。
    3. **层内完全图验证**：同一颜色方块间自动生成连线（白色虚线），若原图有边则连线变粗（绿色实线），否则变细（红色虚线）。
    4. **层间完全二分图验证**：相邻颜色方块间生成跨层连线（白色虚线），同样根据原图边调整颜色。
    5. **边数统计**：屏幕上方显示理论边数（层内+层间）和实际边数（输入m），若相等则播放胜利音效（“叮咚”），否则播放错误音效（“滴——”）。
    6. **AI自动演示**：点击“AI演示”按钮，算法自动完成分层和验证，学习者可观察完整流程。

  * **旁白提示**：
    - “看！黄色方块是起点，它入队啦（音效）。”
    - “红色层的方块两两相连，这是层内完全图哦～”
    - “蓝色层和红色层的方块也两两相连，这是层间完全二分图！”

<visualization_conclusion>
通过这个动画，我们能直观看到分层的过程和边的验证逻辑，轻松理解“层内完全图+层间完全二分图”的核心结构。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的分层思路可迁移到其他图论问题，例如判断图是否为某种特殊结构（如树、环、二分图）。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 分层验证：将复杂图分解为简单结构（如层），验证其是否符合特定条件。
    - 哈希缩点：通过特征（如邻居集合）将点分组，简化图的结构。
    - 边数验证：通过计算理论边数与实际边数对比，判断结构是否合法。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1330 封锁阳光大学** - 二分图判定
          * 🗣️ **推荐理由**：练习判断图是否为二分图，与本题分层思路类似（二分图可视为两层结构）。
    2.  **洛谷 P3386 二分图匹配** - 最大匹配
          * 🗣️ **推荐理由**：进一步理解二分图的性质，巩固分层与匹配的关系。
    3.  **洛谷 P5789 动态树** - 树的结构验证
          * 🗣️ **推荐理由**：练习树的边数验证（树的边数=n-1），与本题边数验证逻辑相似。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解中作者提到：“一开始给我看蒙了，然后突然想到暴力check要n²，那checker怎么写啊？后来YY出分层图的算法。” 这提醒我们遇到复杂问题时，要尝试寻找问题的结构特性，将问题转化为更简单的模型。
</insights_intro>

> **参考经验 (来自 wishapig)**：“一开始被题目难住，后来想到分层图的结构，发现可以通过BFS分层并验证边数。”
> 
> **点评**：这位作者的经验很有启发！遇到复杂约束时，寻找问题的隐藏结构（如分层）是关键。通过观察样例（如样例1的分层结构），可以快速找到解题方向。

---

<conclusion>
本次关于“Labelling Cities”的C++解题分析就到这里。希望这份指南能帮助大家理解分层图的构造与验证，掌握图论问题的解题技巧。记住，多观察样例、寻找结构特性，是解决复杂图论问题的关键！下次再见～💪
</conclusion>

---
处理用时：110.07秒