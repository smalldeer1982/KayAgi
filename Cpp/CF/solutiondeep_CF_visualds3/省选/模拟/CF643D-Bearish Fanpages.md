# 题目信息

# Bearish Fanpages

## 题目描述

There is a social website with $ n $ fanpages, numbered $ 1 $ through $ n $ . There are also $ n $ companies, and the $ i $ -th company owns the $ i $ -th fanpage.

Recently, the website created a feature called following. Each fanpage must choose exactly one other fanpage to follow.

The website doesn’t allow a situation where $ i $ follows $ j $ and at the same time $ j $ follows $ i $ . Also, a fanpage can't follow itself.

Let’s say that fanpage $ i $ follows some other fanpage $ j_{0} $ . Also, let’s say that $ i $ is followed by $ k $ other fanpages $ j_{1},j_{2},...,j_{k} $ . Then, when people visit fanpage $ i $ they see ads from $ k+2 $ distinct companies: $ i,j_{0},j_{1},...,j_{k} $ . Exactly $ t_{i} $ people subscribe (like) the $ i $ -th fanpage, and each of them will click exactly one add. For each of $ k+1 $ companies $ j_{0},j_{1},...,j_{k} $ , exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/21bba61653cf179f89248142af248d7df7419d53.png) people will click their ad. Remaining ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/41e88e0191cf8cbf46af6c24ce4f538a6481272e.png) people will click an ad from company $ i $ (the owner of the fanpage).

The total income of the company is equal to the number of people who click ads from this copmany.

Limak and Radewoosh ask you for help. Initially, fanpage $ i $ follows fanpage $ f_{i} $ . Your task is to handle $ q $ queries of three types:

- 1 i j — fanpage $ i $ follows fanpage $ j $ from now. It's guaranteed that $ i $ didn't follow $ j $ just before the query. Note an extra constraint for the number of queries of this type (below, in the Input section).
- 2 i — print the total income of the $ i $ -th company.
- 3 — print two integers: the smallest income of one company and the biggest income of one company.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/d9db9bc44e733c82215e5751c44c438174d7820a.png)In the sample test, there are $ 5 $ fanpages. The $ i $ -th of them has $ i·10 $ subscribers.

On drawings, numbers of subscribers are written in circles. An arrow from $ A $ to $ B $ means that $ A $ follows $ B $ .

The left drawing shows the initial situation. The first company gets income ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/66341a4c63fe8dcbff87b6d1efb8920e9cbb8631.png) from its own fanpage, and gets income ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/e1ae5946de33df9032cda69753ae955ed119e264.png) from the $ 2 $ -nd fanpage. So, the total income is $ 5+5=10 $ . After the first query ("2 1") you should print $ 10 $ .

The right drawing shows the situation after a query "1 4 2" (after which fanpage $ 4 $ follows fanpage $ 2 $ ). Then, the first company still gets income $ 5 $ from its own fanpage, but now it gets only ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643D/2ec2bf132e45182de4904da17cfe1690c0fccba6.png) from the $ 2 $ -nd fanpage. So, the total income is $ 5+4=9 $ now.

## 样例 #1

### 输入

```
5 12
10 20 30 40 50
2 3 4 5 2
2 1
2 2
2 3
2 4
2 5
1 4 2
2 1
2 2
2 3
2 4
2 5
3
```

### 输出

```
10
36
28
40
36
9
57
27
28
29
9 57
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Bearish Fanpages 深入学习指南 💡

<introduction>
今天我们来一起分析“Bearish Fanpages”这道C++编程题。这道题涉及动态维护粉丝专页的关注关系，并计算公司收益，需要灵活运用数据结构优化操作效率。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（数据结构维护动态贡献）` 

🗣️ **初步分析**：
解决“Bearish Fanpages”的关键在于高效维护每个粉丝专页的关注关系变化，并快速计算其对公司收益的影响。简单来说，每个专页的收益由其自身、关注的专页以及被关注的专页共同决定。我们需要用数据结构（如`multiset`）动态跟踪这些关系的变化，避免每次修改都暴力更新所有相关点。

- **题解思路**：所有题解均围绕“动态维护每个点的入度（被关注数）和出度（关注对象）”展开，通过`multiset`或线段树存储各点贡献，修改时仅影响有限个相关点（如原关注对象、新关注对象及其父节点），从而将时间复杂度优化到O(q log n)。
- **核心难点**：修改操作的连锁反应（如修改i的关注对象j，需更新i原关注对象、j、i原关注对象的父节点等的贡献）；全局最大最小值的高效维护。
- **可视化设计**：采用8位像素风格，用不同颜色的方块表示专页（如红色为当前修改点，蓝色为原关注对象，绿色为新关注对象），用数字气泡展示贡献值。修改时，方块间的箭头（关注关系）动态调整，贡献值数字实时变化，关键步骤（如删除旧贡献、插入新贡献）伴随“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等，我筛选出以下3篇优质题解：
</eval_intro>

**题解一：作者xht**
* **点评**：这篇题解逻辑清晰，详细描述了修改操作的每一步连锁反应（如修改i的关注对象时，需更新原关注对象f_i的贡献、f_i的父节点的贡献等）。代码中使用`multiset`维护各点的贡献集合，并通过`del`和`add`函数同步更新全局最大最小值集合`s0`，结构规范（变量名如`a[i]`表示i的贡献，`d[i]`表示入度）。其对修改操作的分层处理（先删除旧贡献，再修改入度，最后插入新贡献）是亮点，确保了数据一致性。

**题解二：作者关怀他人**
* **点评**：此题解将每个点的贡献拆分为“自身贡献”和“儿子贡献”，用`multiset s[i]`维护i的儿子节点贡献，全局`multiset S`维护各点的最大最小值。代码中`addmax`和`delmax`函数设计巧妙，通过插入/删除全局集合中的最值来快速响应查询。虽然实现细节稍简略，但思路直接，适合理解核心逻辑。

**题解三：作者Diwanul**
* **点评**：此题解用`multiset ch[i]`存储i的儿子贡献，通过`Addm`和`Delm`函数同步全局集合`mm`，代码简洁。修改操作（`Del`和`Link`函数）通过调整入度和贡献值，确保每一步修改仅影响有限个点。其将“自身贡献”和“父亲贡献”分离的思路，是解决动态问题的经典技巧。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们会遇到以下核心难点。结合优质题解的共性，我为大家提炼了解决策略：
</difficulty_intro>

1.  **关键点1：如何高效处理修改操作的连锁反应？**
    * **分析**：修改i的关注对象j时，会影响i原关注对象f_i的入度（减少）、新关注对象j的入度（增加），进而影响f_i和j的贡献值，以及它们父节点的贡献值。优质题解通过分层处理：先删除旧贡献（原关注对象的相关集合），修改入度，再插入新贡献（新关注对象的相关集合），确保每一步仅操作O(1)个点。
    * 💡 **学习笔记**：修改操作时，先处理旧关系的“断链”，再处理新关系的“连链”，避免数据混乱。

2.  **关键点2：如何维护全局最大最小值？**
    * **分析**：每个点的收益由其自身贡献和被关注的贡献组成。优质题解用`multiset`维护各点的贡献集合，全局集合存储各点的最大最小值。修改时，先从全局集合中删除旧最值，更新局部集合后再插入新最值，保证查询时直接取全局集合的首尾即可。
    * 💡 **学习笔记**：全局最值的维护依赖于局部集合的实时更新，需确保每次修改后局部集合与全局集合同步。

3.  **关键点3：如何设计数据结构存储贡献？**
    * **分析**：每个点的贡献由入度决定（入度k时，贡献为t_i/(k+1)），入度变化会导致贡献变化。优质题解用`multiset`存储各点的贡献，利用其自动排序特性快速获取最值。对于频繁的插入/删除操作，`multiset`的O(log n)时间复杂度是关键。
    * 💡 **学习笔记**：`multiset`适合维护动态变化的有序集合，尤其在需要频繁获取最值的场景中。

### ✨ 解题技巧总结
<summary_best_practices>
- **分层处理修改**：将修改操作拆分为“断链”（处理旧关系）和“连链”（处理新关系），确保每一步仅影响有限个点。
- **分离贡献类型**：将贡献分为“自身贡献”和“被关注贡献”，简化计算逻辑。
- **同步全局与局部集合**：局部集合维护单点的贡献，全局集合维护所有点的最值，修改时同步更新，保证查询效率。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个综合自优质题解的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了xht和关怀他人的题解思路，使用`multiset`维护各点的贡献集合，并同步全局最值集合，结构清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    const int N = 1e5 + 7;

    int n, q, d[N], f[N];
    ll t[N], a[N]; // a[i]存储i的总贡献（自身+被关注）
    multiset<ll> s[N]; // s[i]存储i的被关注者的贡献
    multiset<ll> global_minmax; // 全局最大最小值集合
    bool active[N]; // 标记s[i]是否非空

    inline void del_from_global(int x) {
        if (active[x] && !s[x].empty()) {
            active[x] = false;
            global_minmax.erase(global_minmax.find(*s[x].begin() + t[x]/(d[x]+1)));
            global_minmax.erase(global_minmax.find(*s[x].rbegin() + t[x]/(d[x]+1)));
        }
    }

    inline void add_to_global(int x) {
        if (!active[x] && !s[x].empty()) {
            active[x] = true;
            global_minmax.insert(*s[x].begin() + t[x]/(d[x]+1));
            global_minmax.insert(*s[x].rbegin() + t[x]/(d[x]+1));
        }
    }

    void modify(int i, int j) {
        int old_f = f[i];
        // 处理旧关系：i不再关注old_f
        del_from_global(old_f);
        del_from_global(f[old_f]);
        del_from_global(f[f[old_f]]);
        s[old_f].erase(s[old_f].find(a[i]));

        // 更新old_f的贡献
        a[old_f] -= t[i]/(d[i]+1);
        ll old_self = t[old_f] - d[old_f]*(t[old_f]/(d[old_f]+1));
        d[old_f]--;
        ll new_self = t[old_f] - d[old_f]*(t[old_f]/d[old_f]);
        a[old_f] += (new_self - old_self);
        s[f[old_f]].erase(s[f[old_f]].find(a[old_f]));
        s[f[old_f]].insert(a[old_f]);

        // 处理新关系：i关注j
        d[j]++;
        a[j] += t[i]/(d[i]+1);
        ll old_j_self = t[j] - (d[j]-1)*(t[j]/d[j]);
        ll new_j_self = t[j] - d[j]*(t[j]/(d[j]+1));
        a[j] += (new_j_self - old_j_self);
        s[f[j]].erase(s[f[j]].find(a[j]));
        s[f[j]].insert(a[j]);
        s[j].insert(a[i]);

        // 同步全局集合
        add_to_global(old_f);
        add_to_global(f[old_f]);
        add_to_global(f[f[old_f]]);
        add_to_global(j);
        add_to_global(f[j]);
        add_to_global(f[f[j]]);
        f[i] = j;
    }

    int main() {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) scanf("%lld", &t[i]);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &f[i]);
            d[f[i]]++; // 初始入度
        }
        // 初始化a[i]和s[f[i]]
        for (int i = 1; i <= n; i++) {
            a[i] = t[i] - d[i]*(t[i]/(d[i]+1)); // 自身贡献
            a[f[i]] += t[i]/(d[i]+1); // 被关注贡献
        }
        for (int i = 1; i <= n; i++) s[f[i]].insert(a[i]);
        for (int i = 1; i <= n; i++) add_to_global(i);

        while (q--) {
            int op, i, j;
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &i, &j);
                modify(i, j);
            } else if (op == 2) {
                scanf("%d", &i);
                printf("%lld\n", a[i] + t[f[i]]/(d[f[i]]+1));
            } else {
                printf("%lld %lld\n", *global_minmax.begin(), *global_minmax.rbegin());
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：代码通过`d[i]`记录入度，`a[i]`记录i的总贡献（自身+被关注），`s[i]`存储i的被关注者的贡献。`del_from_global`和`add_to_global`函数同步全局最值集合。`modify`函数处理修改操作，先删除旧关系的贡献，调整入度和贡献值，再插入新关系的贡献，确保所有集合同步。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者xht**
* **亮点**：分层处理修改操作的连锁反应，代码逻辑清晰，变量命名直观（如`d[i]`表示入度，`a[i]`表示贡献）。
* **核心代码片段**：
    ```cpp
    inline void del(int x) {
        if (v[x] && s[x].size())
            v[x] = 0,
            s[0].erase(s[0].find((*s[x].begin()) + t[x] / (d[x] + 1))),
            s[0].erase(s[0].find((*(--s[x].end())) + t[x] / (d[x] + 1)));
    }

    inline void add(int x) {
        if (!v[x] && s[x].size())
            v[x] = 1,
            s[0].insert((*s[x].begin()) + t[x] / (d[x] + 1)),
            s[0].insert((*(--s[x].end())) + t[x] / (d[x] + 1));
    }
    ```
* **代码解读**：`del`和`add`函数用于从全局集合`s0`中删除/插入当前点的最值。`v[x]`标记`s[x]`是否非空，避免重复操作。例如，`del(x)`会删除`s[x]`的最小和最大值在全局集合中的记录，`add(x)`则插入新的记录。这两个函数是维护全局最值的关键。
* 💡 **学习笔记**：通过标记变量（如`v[x]`）避免重复操作，是优化集合维护的常用技巧。

**题解二：作者关怀他人**
* **亮点**：将贡献拆分为“自身贡献”和“儿子贡献”，用`calcself`和`calcson`函数分离计算逻辑，提高代码可读性。
* **核心代码片段**：
    ```cpp
    ll calcself(int i) {return t[i] - (t[i] / (num[i] + 2)) * (num[i] + 1);}
    ll calcson(int i) {return t[i] / (num[i] + 2);}
    ```
* **代码解读**：`calcself`计算i的自身贡献（订阅者未分配给其他点的部分），`calcson`计算i对被关注者的贡献（每个被关注者获得的订阅数）。通过函数封装，将复杂的公式转化为清晰的逻辑，方便后续修改和维护。
* 💡 **学习笔记**：将复杂计算封装为函数，能显著提高代码的可读性和可维护性。

**题解三：作者Diwanul**
* **亮点**：使用`Change`函数统一处理贡献修改，减少重复代码。
* **核心代码片段**：
    ```cpp
    inline void Change(int u,LL x){
        int f=fa[u];
        Delm(f);
        ch[f].erase(ch[f].find(ic[u]));
        ic[u]+=x;
        ch[f].insert(ic[u]);
        Addm(f);
    }
    ```
* **代码解读**：`Change`函数用于修改u对其父亲f的贡献。首先删除f的旧贡献（`Delm(f)`），从f的集合`ch[f]`中删除u的旧贡献值`ic[u]`，更新`ic[u]`后重新插入，最后将新贡献加入f的集合（`Addm(f)`）。这种封装使得修改操作更简洁。
* 💡 **学习笔记**：将重复的修改逻辑封装为函数，可减少代码冗余，降低出错概率。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解修改操作和贡献计算的过程，我设计了一个“像素粉丝专页”动画演示方案，结合8位复古风格和游戏化元素。
</visualization_intro>

  * **动画演示主题**：`像素粉丝专页大冒险——关注关系与收益变化`

  * **核心演示内容**：展示修改关注关系（操作1）时，原关注对象、新关注对象及其父节点的贡献值如何变化；查询收益（操作2）时，单个公司的收益如何由自身和被关注贡献组成；查询全局最值（操作3）时，所有公司收益的最小和最大值如何动态更新。

  * **设计思路简述**：采用FC红白机风格的像素画面（8色调色板，方块代表专页），用箭头表示关注关系（红色箭头为当前修改点的旧关注，绿色箭头为新关注）。贡献值用数字气泡悬浮在专页上方，修改时气泡数字动态变化，关键操作（如插入/删除贡献）伴随“叮”的音效，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕中央是n个像素方块（颜色随机但固定），每个方块上方显示专页编号（如“1”“2”）。
        - 控制面板位于下方，包含“单步”“自动播放”“重置”按钮和速度滑块。
        - 播放8位风格的轻快背景音乐（如《超级马里奥》经典旋律变调）。

    2.  **修改操作演示（操作1）**：
        - 当用户点击“单步”或“自动播放”时，动画展示修改i的关注对象为j的过程：
          - 原关注对象old_f的方块变为黄色（高亮），其箭头（i→old_f）变为红色并闪烁，伴随“叮”的音效（删除旧贡献）。
          - old_f的入度d[old_f]减1，其贡献值数字气泡减少（如从“50”变为“45”）。
          - 新关注对象j的方块变为绿色（高亮），新箭头（i→j）绿色闪烁，伴随“叮”的音效（插入新贡献）。
          - j的入度d[j]加1，其贡献值数字气泡增加（如从“30”变为“35”）。
          - 全局最值区域（屏幕右侧）的数字实时更新，最小值和最大值用不同颜色（蓝色为最小，红色为最大）高亮。

    3.  **查询操作演示（操作2）**：
        - 用户输入查询i的收益时，i的方块变为紫色（高亮），其贡献值数字气泡放大，并显示分解：“自身贡献（20） + 被关注贡献（15） = 35”。

    4.  **全局最值查询（操作3）**：
        - 屏幕右侧的全局最值区域显示所有公司的收益，最小值和最大值的方块分别用蓝色和红色闪烁，伴随“胜利”音效（上扬音调）。

    5.  **交互控制**：
        - 用户可通过滑块调整动画速度（如0.5倍速到2倍速），单步执行时每点击一次播放一个修改步骤。
        - 点击“重置”按钮，动画回到初始状态，所有贡献值和关注关系恢复。

  * **旁白提示**：
      - （修改旧关系时）“注意！i不再关注old_f，old_f的入度减少，贡献值需要更新。”
      - （插入新关系时）“现在i关注j，j的入度增加，贡献值重新计算。”
      - （查询时）“i的收益由自身贡献和被关注贡献组成，看，这两个部分加起来就是最终收益！”

<visualization_conclusion>
通过这样的像素动画，我们能直观看到关注关系变化如何影响贡献值，以及全局最值是如何动态维护的。这种游戏化的演示方式，能让我们更快理解复杂的动态数据维护逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是动态维护图结构中的节点贡献，这种思路可迁移到许多需要高效处理动态关系的问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - **动态树维护**：如处理动态树的路径查询（如LCT，Link-Cut Tree），本题的关注关系可视为动态树的边，修改操作即边的断开与连接。
      - **堆/集合维护最值**：如任务调度问题中，动态维护任务的优先级，用堆或`multiset`快速获取最值。
      - **贡献拆分**：如网络流中的容量分配问题，将总流量拆分为各边的贡献，动态调整。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1090 [NOIP2004 提高组] 合并果子**
          * 🗣️ **推荐理由**：这道题需要用优先队列（堆）维护每次合并的最小代价，与本题用`multiset`维护最值的思路类似，能巩固数据结构维护动态最值的技巧。
    2.  **洛谷 P3372 [模板] 线段树 1**
          * 🗣️ **推荐理由**：线段树是高效处理区间修改和查询的工具，本题的动态贡献更新可类比线段树的区间操作，适合练习数据结构的综合运用。
    3.  **洛谷 P5024 [NOIP2018 提高组] 保卫王国**
          * 🗣️ **推荐理由**：此题涉及动态树的路径查询和修改，需要结合动态规划与树链剖分，能进一步提升动态问题的处理能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本题的题解中，作者xht提到：“修改操作时，必须先删除旧贡献再修改入度，否则会导致集合中的值与实际入度不匹配。”这一经验对避免数据错误至关重要。
</insights_intro>

> **参考经验 (来自作者xht)**：“在修改i的关注对象时，我最初直接修改了入度，导致集合中的贡献值未及时删除旧数据，结果查询时出现错误。后来调整顺序，先删除旧贡献，再修改入度，最后插入新贡献，问题就解决了。”

> **点评**：xht的经验提醒我们，动态数据维护中“先断后连”的顺序至关重要。修改关系时，必须先处理旧关系的影响（如删除旧贡献），再修改数据结构（如调整入度），最后处理新关系的影响（如插入新贡献）。这能避免因顺序错误导致的集合值与实际状态不一致的问题。

-----

<conclusion>
本次关于“Bearish Fanpages”的C++解题分析就到这里。希望这份学习指南能帮助大家理解动态数据维护的核心思路，掌握`multiset`等数据结构的运用。记住，编程能力的提升需要多思考、多实践，下次我们再一起探索新的挑战！💪
</conclusion>

---
处理用时：172.11秒