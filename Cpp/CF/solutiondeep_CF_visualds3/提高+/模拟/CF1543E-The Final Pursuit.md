# 题目信息

# The Final Pursuit

## 题目描述

Finally, you have defeated Razor and now, you are the Most Wanted street racer. Sergeant Cross has sent the full police force after you in a deadly pursuit. Fortunately, you have found a hiding spot but you fear that Cross and his force will eventually find you. To increase your chances of survival, you want to tune and repaint your BMW M3 GTR.

The car can be imagined as a permuted $ n $ -dimensional hypercube. A simple $ n $ -dimensional hypercube is an undirected unweighted graph built recursively as follows:

- Take two simple $ (n-1) $ -dimensional hypercubes one having vertices numbered from $ 0 $ to $ 2^{n-1}-1 $ and the other having vertices numbered from $ 2^{n-1} $ to $ 2^{n}-1 $ . A simple $ 0 $ -dimensional Hypercube is just a single vertex.
- Add an edge between the vertices $ i $ and $ i+2^{n-1} $ for each $ 0\leq i < 2^{n-1} $ .

A permuted $ n $ -dimensional hypercube is formed by permuting the vertex numbers of a simple $ n $ -dimensional hypercube in any arbitrary manner.

Examples of a simple and permuted $ 3 $ -dimensional hypercubes are given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1543E/aea140f70de8ed5134f37d1a4e3eeede0b9ad62a.png)Note that a permuted $ n $ -dimensional hypercube has the following properties:

- There are exactly $ 2^n $ vertices.
- There are exactly $ n\cdot 2^{n-1} $ edges.
- Each vertex is connected to exactly $ n $ other vertices.
- There are no self-loops or duplicate edges.

Let's denote the permutation used to generate the permuted $ n $ -dimensional hypercube, representing your car, from a simple $ n $ -dimensional hypercube by $ P $ . Before messing up the functionalities of the car, you want to find this permutation so that you can restore the car if anything goes wrong. But the job isn't done yet.

You have $ n $ different colours numbered from $ 0 $ to $ n-1 $ . You want to colour the vertices of this permuted $ n $ -dimensional hypercube in such a way that for each and every vertex $ u $ satisfying $ 0\leq u < 2^n $ and for each and every colour $ c $ satisfying $ 0\leq c < n $ , there is at least one vertex $ v $ adjacent to $ u $ having a colour $ c $ . In other words, from each and every vertex, it must be possible to reach a vertex of any colour by just moving to an adjacent vertex.

Given the permuted $ n $ -dimensional hypercube, find any valid permutation $ P $ and colouring.

## 说明/提示

The colouring and the permuted hypercube for the first test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1543E/24b381f853d139f5b42196277a1d932f42b60e97.png)The colouring and the permuted hypercube for the second test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1543E/782238ab7b06fc67a8cfcb7bb5396c04aba44a9e.png)The permuted hypercube for the third test case is given in the problem statement. However, it can be shown that there exists no way to colour that cube satifying all the conditions. Note that some other permutations like $ [0, 5, 7, 3, 1, 2, 4, 6] $ and $ [0, 1, 5, 2, 7, 4, 3, 6] $ will also give the same permuted hypercube.

## 样例 #1

### 输入

```
3
1
0 1
2
0 1
1 2
2 3
3 0
3
0 1
0 5
0 7
1 2
1 4
2 5
2 6
3 5
3 6
3 7
4 6
4 7```

### 输出

```
0 1
0 0
0 1 3 2
0 0 1 1
5 3 0 7 2 6 1 4
-1```

# AI分析结果

---
# 💡 Kay的C++算法解析：The Final Pursuit 深入学习指南 💡

<introduction>
今天我们要挑战的是“n维排列超立方体”的构造问题！这道题需要我们找到排列P并构造合法染色方案，涉及图论、构造算法和位运算。让我们一步步拆解，掌握核心思路和技巧吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：图论（超立方体结构构造） + 构造性算法（排列与染色）

🗣️ **初步分析**：
解决这道题的关键在于理解“n维排列超立方体”的本质——它是简单超立方体通过顶点置换得到的。简单超立方体的每个顶点i与i⊕2ᵏ（k∈[0,n)）相连，而排列超立方体是这些顶点的重排。我们需要：
1. **构造排列P**：将排列超立方体的顶点映射回简单超立方体的编号。
2. **构造染色方案**：确保每个顶点的邻接点颜色覆盖所有n种颜色（n为2的幂时有解）。

核心难点在于：
- 如何通过图遍历（BFS）确定每个顶点的简单超立方体编号。
- 如何利用位运算构造满足条件的染色方案（仅当n是2的幂时可行）。

可视化设计思路：用8位像素风展示超立方体顶点（格子或小圆点），BFS过程中用不同颜色标记层级（如0层为红色，1层为绿色），边用虚线连接。染色时，顶点用n种像素色显示，邻接点颜色切换时伴随“叮”的音效，突出颜色覆盖效果。

---

## 2. 精选优质题解参考

<eval_intro>
经过评估，以下题解在思路清晰度、代码规范性和算法有效性上表现突出（均≥4星）：
</eval_intro>

**题解一：Leap_Frog的题解**  
* **点评**：此题解逻辑严谨，从理论到代码实现完整。思路上，通过BFS分层确定每个顶点的简单超立方体编号（利用位或运算），并通过位运算构造染色方案。代码规范（如变量名`iv`表示逆映射，`rs`表示排列），边界处理（如`cnt`计数确保遍历所有顶点）严谨。亮点在于对“n必须是2的幂”这一条件的数学推导，以及染色方案的位运算构造技巧，对竞赛实践有强参考价值。

**题解二：dead_X的题解**  
* **点评**：此题解思路直白，代码简洁。通过BFS逐层扩展确定顶点编号，染色部分直接利用位运算（统计每一位是否为1）构造颜色。代码结构清晰（如`cur`和`nxt`队列处理BFS），关键步骤（如`id[j]|=id[i]`）注释明确。亮点是通过`assert`验证染色方案的正确性，体现了严谨的编码习惯，适合新手学习。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题时，以下三个关键点需要特别注意：
</difficulty_intro>

1.  **关键点1：如何构造排列P？**  
    * **分析**：排列P的本质是将排列超立方体的顶点映射到简单超立方体的编号。简单超立方体的顶点i的邻接点是i⊕2⁰, i⊕2¹,...,i⊕2ⁿ⁻¹。因此，我们可以通过BFS分层确定每个顶点的编号：  
      - 钦定任意顶点为0号（简单超立方体的0）。  
      - 0号的邻接点依次对应2⁰, 2¹,...,2ⁿ⁻¹（即第一层）。  
      - 后续层的顶点编号由其邻接的上层顶点编号的位或得到（因为简单超立方体中，顶点i的编号是其所有邻接边的异或位的或）。  
    * 💡 **学习笔记**：BFS分层是构造排列的核心，利用位或运算确保每个顶点编号唯一且符合简单超立方体的邻接关系。

2.  **关键点2：染色方案的构造条件**  
    * **分析**：每个顶点有n个邻接点，需覆盖n种颜色。数学推导表明，颜色总数需满足2ⁿ是n的倍数（即n必须是2的幂）。例如，n=2时，2²/2=2（整数）；n=3时，2³/3≈2.67（非整数），无解。  
    * 💡 **学习笔记**：n为2的幂是染色可行的必要条件，也是解题的关键判断条件。

3.  **关键点3：如何构造合法染色？**  
    * **分析**：当n是2的幂时，利用位运算构造颜色。对于简单超立方体的顶点i，颜色为其所有置位位的索引异或和（如i=5=101₂，颜色为0^2=2）。由于每个邻接点i⊕2ᵏ的颜色是原颜色异或k，因此邻接点颜色覆盖0~n-1。  
    * 💡 **学习笔记**：位运算的异或性质是构造染色方案的核心，确保邻接点颜色无重复。

### ✨ 解题技巧总结
- **问题分解**：将问题拆分为“构造排列”和“构造染色”两部分，分别解决。  
- **BFS分层**：利用BFS遍历超立方体，通过位或运算确定顶点编号。  
- **位运算构造**：染色时，利用位的异或和生成颜色，确保邻接点颜色覆盖所有可能。  

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合Leap_Frog和dead_X题解的通用核心实现，逻辑清晰且高效：
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码综合了两位优质题解的思路，通过BFS构造排列P，并根据n是否为2的幂构造染色方案。  
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 65536; // 2^16的最大顶点数

    vector<int> adj[MAXN]; // 邻接表存储超立方体
    int id[MAXN], inv[MAXN]; // id[u]：排列超立方体顶点u对应的简单超立方体编号；inv[i]：简单超立方体顶点i对应的排列超立方体顶点
    int color[MAXN]; // 染色结果

    void solve() {
        int n;
        cin >> n;
        int N = 1 << n; // 顶点总数2^n
        int m = n * (1 << (n-1)); // 边总数n*2^(n-1)

        // 初始化邻接表
        for (int i = 0; i < N; ++i) adj[i].clear();
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // 步骤1：构造排列P（id和inv数组）
        memset(id, 0, sizeof(id));
        vector<int> cur, nxt;
        id[0] = 0; // 钦定顶点0为简单超立方体的0号
        cur.push_back(0);
        int cnt = 1;

        // BFS分层确定各顶点编号
        for (int layer = 1; layer <= n; ++layer) {
            for (int u : cur) {
                for (int v : adj[u]) {
                    if (id[v] == 0 && v != 0) { // 未访问过的顶点
                        id[v] = 1 << (layer - 1); // 第一层对应2^0, 2^1,...,2^(n-1)
                        nxt.push_back(v);
                        cnt++;
                    }
                }
            }
            swap(cur, nxt);
            nxt.clear();
        }

        // 后续层通过位或确定编号（BFS扩展）
        while (cnt < N) {
            nxt.clear();
            for (int u : cur) {
                for (int v : adj[u]) {
                    if (id[v] == 0) { // 未确定编号的顶点
                        id[v] |= id[u]; // 位或邻接的上层顶点编号
                        if (find(nxt.begin(), nxt.end(), v) == nxt.end()) {
                            nxt.push_back(v);
                            cnt++;
                        }
                    }
                }
            }
            swap(cur, nxt);
            nxt.clear();
        }

        // 生成排列P（inv[i]表示简单超立方体顶点i对应的排列超立方体顶点）
        for (int i = 0; i < N; ++i) inv[id[i]] = i;

        // 输出排列P
        for (int i = 0; i < N; ++i) {
            cout << inv[i] << " ";
        }
        cout << endl;

        // 步骤2：构造染色方案（仅当n是2的幂时）
        int temp = n;
        while (temp % 2 == 0) temp /= 2;
        if (temp != 1) { // n不是2的幂，无解
            cout << -1 << endl;
            return;
        }

        // 利用位运算构造颜色
        for (int i = 0; i < N; ++i) {
            color[inv[i]] = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    color[inv[i]] ^= j; // 颜色为所有置位位的索引异或和
                }
            }
        }

        // 输出颜色
        for (int i = 0; i < N; ++i) {
            cout << color[i] << " ";
        }
        cout << endl;
    }

    int main() {
        int T;
        cin >> T;
        while (T--) {
            solve();
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取输入并构建邻接表，然后通过BFS分层确定每个顶点的简单超立方体编号（`id`数组），生成排列`inv`。接着判断n是否为2的幂，若否输出-1；若是则通过位运算构造颜色（每个顶点颜色为其简单超立方体编号中所有置位位的索引异或和）。

---

<code_intro_selected>
接下来，分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：Leap_Frog的代码片段**  
* **亮点**：BFS分层与位或运算结合，高效构造排列；染色部分直接利用位异或生成颜色。  
* **核心代码片段**：
    ```cpp
    vector<int>ls,nw;iv[0]=0,v[0]=1;int cnt=1;
    for(int i=head[0],j=0;i;i=e[i].nxt,j++)
        iv[e[i].to]=1<<j,ls.push_back(e[i].to),cnt++,v[e[i].to]=1;
    while(cnt!=lim){
        for(int x:ls) for(int i=head[x];i;i=e[i].nxt) if(!v[e[i].to]) iv[e[i].to]|=iv[x];
        for(int x:ls) for(int i=head[x];i;i=e[i].nxt)
            if(!v[e[i].to]) nw.push_back(e[i].to),v[e[i].to]=1,cnt++;
        swap(nw,ls),nw.clear();
    }
    ```
* **代码解读**：  
  这段代码通过BFS分层构造排列。初始时，顶点0的邻接点被标记为2⁰, 2¹,...,2ⁿ⁻¹（`iv[e[i].to]=1<<j`）。后续层的顶点通过邻接的上层顶点的`iv`值进行位或（`iv[e[i].to]|=iv[x]`），确保每个顶点的编号唯一且符合简单超立方体的邻接关系。`v`数组标记已访问顶点，`cnt`计数确保遍历所有顶点。  
* 💡 **学习笔记**：BFS分层+位或运算是构造排列的关键，确保每个顶点编号正确反映其在简单超立方体中的位置。

**题解二：dead_X的代码片段**  
* **亮点**：染色部分通过`assert`验证正确性，确保代码鲁棒性；位运算构造颜色简洁高效。  
* **核心代码片段**：
    ```cpp
    for(int i=0; i<N; ++i)
    {
        int s=0;
        for(int j=0; j<n; ++j) if(i&(1<<j)) s^=j;
        col[inv[i]]=s;
    }
    ```
* **代码解读**：  
  这段代码为每个简单超立方体顶点i计算颜色。`s`初始为0，遍历i的每一位j，若该位为1（即i包含2ʲ），则将s异或j。最终`col[inv[i]]`即为排列超立方体中对应顶点的颜色。由于每个邻接点i⊕2ᵏ的颜色是s异或k（因为i⊕2ᵏ的第k位翻转），因此邻接点颜色覆盖0~n-1。  
* 💡 **学习笔记**：位异或的性质（相同位异或为0，不同为1）确保了邻接点颜色的唯一性。

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解BFS构造排列和染色过程，我们设计一个“像素超立方体探险”动画，用8位像素风格展示顶点和边的变化！
</visualization_intro>

  * **动画演示主题**：像素超立方体大冒险——寻找排列与染色  
  * **核心演示内容**：  
    - BFS构造排列：从顶点0出发，逐层扩展，标记每个顶点的简单超立方体编号。  
    - 染色验证：展示每个顶点的邻接点颜色是否覆盖所有n种。  
  * **设计思路简述**：  
    8位像素风（如FC游戏画面）营造轻松氛围，顶点用彩色方块表示，边用虚线连接。BFS过程中，当前处理层的顶点闪烁（如绿色），已处理层变灰，突出层级扩展。染色时，顶点颜色随计算结果变化，邻接点颜色切换时播放“叮”音效，验证成功时播放胜利音效。

  * **动画帧步骤与交互关键点**：  
    1. **场景初始化**：  
       - 屏幕左侧显示排列超立方体（顶点为灰色方块，边为虚线），右侧显示简单超立方体（顶点为白色方块，边为实线）。  
       - 控制面板包含“开始”“单步”“重置”按钮和速度滑块。  
       - 播放8位风格背景音乐（如《超级玛丽》经典旋律）。  

    2. **BFS构造排列**：  
       - 顶点0（红色方块）被选中，显示“我是起点！”旁白。  
       - 顶点0的邻接点依次变为绿色（第一层），显示编号（如“我是2⁰！”），伴随“入队”音效（短“叮”）。  
       - 后续层顶点通过位或计算编号（如顶点u的邻接点v的编号为u的编号位或结果），v变为黄色并显示编号，加入队列。  
       - 所有顶点处理完成后，显示“排列构造完成！”旁白，播放“成功”音效（上扬音调）。  

    3. **染色验证**：  
       - 若n是2的幂，顶点按位异或结果染色（如0号顶点为蓝色，1号为红色，...）。  
       - 点击任意顶点，其邻接点颜色高亮（如闪烁），旁白显示“看！我的邻居有所有颜色！”。  
       - 若n不是2的幂，顶点保持灰色，显示“无解哦~”旁白，播放“失败”音效（短促“咚”）。  

    4. **交互控制**：  
       - 单步模式：点击“单步”按钮，逐步执行BFS或染色步骤。  
       - 自动播放：拖动速度滑块（慢→快），算法自动执行，类似“AI探险”。  

  * **旁白提示**：  
    - BFS时：“当前处理层的顶点会帮助确定下一层顶点的编号哦！”  
    - 染色时：“每个顶点的颜色由它的二进制位决定，这样邻居的颜色就不会重复啦！”  

<visualization_conclusion>
通过这个动画，我们能直观看到BFS如何分层构造排列，以及染色方案的巧妙之处。像素风格和音效让学习过程更有趣！
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是图的构造与位运算，以下是相关拓展练习：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    构造排列和染色的思路可迁移至：  
    - 其他特殊图（如树、环）的顶点映射问题。  
    - 需要覆盖条件的染色问题（如棋盘染色、图着色）。  
    - 位运算在构造性算法中的应用（如格雷码、异或变换）。  

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P5318** - 【深基18.例3】查找文献  
        * 🗣️ **推荐理由**：练习BFS和DFS遍历图，巩固图的基本操作。  
    2.  **洛谷 P4781** - 【模板】拉格朗日插值  
        * 🗣️ **推荐理由**：学习构造性算法，理解如何通过数学推导解决问题。  
    3.  **洛谷 P1514** - 引水入城  
        * 🗣️ **推荐理由**：结合图的遍历和染色思想，解决覆盖问题。  

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中dead_X提到“读错了巨大多次题浪费了巨大多时间”，这对我们很有启发：
</insights_intro>

> **参考经验 (来自 dead_X)**：“我读错了巨大多次题浪费了巨大多时间。”  
> **点评**：读题是解题的第一步！题目中的条件（如“排列超立方体”的定义）和要求（如染色覆盖所有颜色）必须仔细理解。建议用荧光笔标记关键条件，避免因误解题意走弯路。

---

<conclusion>
通过这次分析，我们掌握了n维排列超立方体的构造方法，以及染色方案的条件和实现。记住，遇到复杂问题时，分解步骤、利用图遍历和位运算技巧是关键！期待下次一起挑战更难的算法题！💪
</conclusion>

---
处理用时：139.96秒