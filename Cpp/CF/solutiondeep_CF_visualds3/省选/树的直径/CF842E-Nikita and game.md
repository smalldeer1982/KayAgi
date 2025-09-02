# 题目信息

# Nikita and game

## 题目描述

Nikita plays a new computer game. There are $ m $ levels in this game. In the beginning of each level a new class appears in the game; this class is a child-class of the class $ y_{i} $ (and $ y_{i} $ is called parent-class for this new class). Thus, the classes form a tree. Initially there is only one class with index $ 1 $ .

Changing the class to its neighbour (child-class or parent-class) in the tree costs $ 1 $ coin. You can not change the class back. The cost of changing the class $ a $ to the class $ b $ is equal to the total cost of class changes on the path from $ a $ to $ b $ in the class tree.

Suppose that at $ i $ -th level the maximum cost of changing one class to another is $ x $ . For each level output the number of classes such that for each of these classes there exists some other class $ y $ , and the distance from this class to $ y $ is exactly $ x $ .

## 样例 #1

### 输入

```
4
1
1
2
1
```

### 输出

```
2
2
2
3
```

## 样例 #2

### 输入

```
4
1
1
2
3
```

### 输出

```
2
2
2
2
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Nikita and game 深入学习指南 💡

<introduction>
今天我们要分析的是「Nikita and game」这道题，它的核心是**动态维护树的直径端点集合**——就像我们要跟踪一棵树中所有能作为“最长主干道”两端的点。这道题能帮我们巩固树论中的重要性质，还能学习如何高效处理动态数据！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：图论（树的直径维护）

🗣️ **初步分析**：
树的直径就像树的“最长主干道”——从树中某点到另一点的最长路径。解决这道题的关键，是利用树直径的一个**核心性质**：**所有直径必然交于一点或一条边**。这就像城市里的主干道，不管有多少条“最长路”，它们的中间部分一定是重叠的！

我们可以把这些直径的端点分成两部分（比如“主干道的东端”和“西端”），用两个集合`S1`和`S2`分别保存。每次新增一个节点时，只需要计算它到`S1`、`S2`中任意一点的距离：
- 如果这个距离超过当前直径，说明找到了更长的主干道，需要更新`S1`或`S2`；
- 如果等于当前直径，说明这个节点可以成为新的端点，加入对应的集合；
- 如果更小，就不用管它。

**可视化设计思路**：我们用8位像素风展示树的生长——
- 用不同颜色的像素块表示`S1`（红）、`S2`（蓝）和普通节点（灰）；
- 新增节点时，闪烁新节点并播放“叮”的像素音效；
- 计算LCA（最长公共祖先）时，用箭头动画展示“向上跳父节点”的过程；
- 直径延长时，播放“升级”音效，同时旧集合的颜色变淡，新集合高亮。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码效率、实践价值等角度筛选了3份优质题解，帮大家快速理解核心逻辑：
</eval_intro>

**题解一：(来源：skylee，Codeforces Rank2)**
* **点评**：这份题解的思路像“精准打击”——用`vector`维护`S1`和`S2`（比`set`更快！），用LCA快速计算两点距离（时间复杂度`O(logn)`）。代码风格极其规范，变量名清晰（比如`dep`存深度，`anc`存祖先），甚至优化了输入函数`getint()`来加速。最厉害的是，它利用“集合中任意一点的距离都能代表整个集合”的性质，避免了重复计算，把总时间复杂度压到了`O(nlogn)`，完美通过大数据！

**题解二：(来源：N1K_J，详细证明)**
* **点评**：这份题解的亮点是**完整证明了直径的性质**——比如“新直径的另一端一定来自旧集合”。它的代码逻辑和题解一类似，但更注重细节（比如处理`S1`和`S2`的重复加入问题）。对于想理解“为什么这么做”的同学，这份题解的证明部分能帮你彻底搞懂！

**题解三：(来源：wxzzzz，set实现)**
* **点评**：这份题解用`set`维护`S1`和`S2`，虽然效率比`vector`略低，但思路更直观。它的代码结构简单，适合刚学树论的同学入门——比如`dis`函数直接调用LCA，`insert`操作直接加元素，容易模仿。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键，是突破三个“小障碍”：
</difficulty_intro>

1. **如何快速计算两点距离？**
   - **分析**：树中两点距离=深度之和 - 2×LCA的深度。LCA（最长公共祖先）是两个节点的“最近共同祖先”，就像两个人的家族树中最近的共同长辈。
   - **解决方案**：用**倍增法**预处理每个节点的2^k级祖先（比如`anc[i][k]`表示节点`i`的2^k倍祖先），这样找LCA只需要`O(logn)`时间！

2. **如何维护直径端点集合？**
   - **分析**：如果直接暴力存储所有端点，每次更新会很慢。但利用“所有直径交于一点/边”的性质，我们可以把端点分成两部分（`S1`和`S2`），每次只需要和集合中的**任意一点**计算距离！
   - **解决方案**：用`vector`或`set`保存`S1`和`S2`，每次新增节点时，只算它到`S1[0]`、`S2[0]`的距离——因为集合内的点到其他点的距离是一样的！

3. **如何处理直径延长的情况？**
   - **分析**：当新增节点让直径变长时，旧的端点集合可能部分失效。比如新节点在`S1`一侧，那么旧`S2`中能和新节点形成新直径的点，需要转移到`S1`。
   - **解决方案**：遍历旧集合中的点，检查是否能和新节点形成新直径——能的话加入新集合，否则丢弃。


### ✨ 解题技巧总结
- **性质优先**：先记住树直径的核心性质（所有直径交于一点/边），能帮你跳过很多弯路；
- **倍增LCA**：处理树中距离问题的“万能工具”，一定要掌握；
- **集合简化**：不用存所有端点，只存两部分——利用“集合内任意点的距离都代表集合”的性质！


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心实现**——它综合了题解一的高效思路，是解决这道题的“标准模板”！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码来自skylee的题解，是动态维护树直径端点的**高效模板**，用`vector`维护集合，倍增LCA求距离，时间复杂度`O(nlogn)`。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>
    using namespace std;

    const int N = 3e5 + 5, LOG = 19;
    int dep[N], anc[N][LOG];
    vector<int> S1, S2;

    // 快速读入（优化输入速度）
    inline int getint() {
        char ch;
        while (!isdigit(ch = getchar()));
        int x = ch - '0';
        while (isdigit(ch = getchar())) x = x * 10 + (ch - '0');
        return x;
    }

    // 预处理倍增祖先
    inline void add_node(int u, int parent) {
        dep[u] = dep[parent] + 1;
        anc[u][0] = parent;
        for (int k = 1; k < LOG; ++k)
            anc[u][k] = anc[anc[u][k-1]][k-1];
    }

    // 找LCA（最长公共祖先）
    inline int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        // 跳到同一深度
        for (int k = LOG-1; k >= 0; --k)
            if (dep[anc[x][k]] >= dep[y]) x = anc[x][k];
        if (x == y) return x;
        // 一起跳
        for (int k = LOG-1; k >= 0; --k)
            if (anc[x][k] != anc[y][k]) x = anc[x][k], y = anc[y][k];
        return anc[x][0];
    }

    // 计算两点距离
    inline int dist(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }

    int main() {
        int n = getint() + 1; // 总节点数（初始1个，加n次）
        add_node(1, 0); // 初始化根节点1
        S1.push_back(1);
        int maxd = 0; // 当前直径长度

        for (int u = 2; u <= n; ++u) {
            int parent = getint();
            add_node(u, parent);

            // 计算到S1、S2的距离
            int d1 = S1.empty() ? 0 : dist(u, S1[0]);
            int d2 = S2.empty() ? 0 : dist(u, S2[0]);

            // 更新直径和集合
            if (max(d1, d2) > maxd) {
                maxd = max(d1, d2);
                if (d1 == maxd) {
                    // 旧S2中能和u形成新直径的点，加入S1
                    for (int x : S2)
                        if (dist(x, u) == maxd) S1.push_back(x);
                    S2.clear();
                    S2.push_back(u);
                } else {
                    for (int x : S1)
                        if (dist(x, u) == maxd) S2.push_back(x);
                    S1.clear();
                    S1.push_back(u);
                }
            } else if (max(d1, d2) == maxd) {
                (d1 == maxd ? S2 : S1).push_back(u);
            }

            // 输出端点总数
            cout << S1.size() + S2.size() << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
  1. **预处理**：用`add_node`函数预处理每个节点的深度`dep`和祖先`anc`；
  2. **LCA计算**：`lca`函数通过倍增法找到两个节点的最近共同祖先；
  3. **距离计算**：`dist`函数用深度差计算两点距离；
  4. **动态维护**：每次新增节点时，计算到`S1`、`S2`的距离，更新直径和集合；
  5. **输出结果**：每次操作后输出`S1+S2`的大小（所有直径端点的数量）。


---
<code_intro_selected>
接下来，我们剖析优质题解中的**核心片段**，看看它们的“点睛之笔”！
</code_intro_selected>

**题解一：(来源：skylee)**
* **亮点**：用`vector`代替`set`，插入和遍历更快——这是它能跑到Rank2的关键！
* **核心代码片段**：
    ```cpp
    // 处理新直径的情况
    if (d1 == maxd) {
        for (int x : S2)
            if (dist(x, u) == maxd) S1.push_back(x);
        S2.clear();
        S2.push_back(u);
    }
    ```
* **代码解读**：
  这段代码是“更新集合”的核心——当新节点`u`让直径变长时：
  1. 遍历旧`S2`中的点，检查是否能和`u`形成新直径（距离等于新直径）；
  2. 能的话，把这些点加入`S1`（因为它们现在属于“主干道的另一端”）；
  3. 清空`S2`，把`u`加入`S2`（新的端点集合）。
  为什么用`vector`？因为`vector`的遍历速度比`set`快很多，而我们不需要频繁查找元素！

* **学习笔记**：能用`vector`就不用`set`——除非需要自动排序或去重！


**题解二：(来源：N1K_J)**
* **亮点**：处理“重复加入”的问题——避免同一个节点被同时加入`S1`和`S2`！
* **核心代码片段**：
    ```cpp
    else {
        if (dis1 == d) t.push_back(id);
        else if (dis2 == d) s.push_back(id); // 用else，避免重复
    }
    ```
* **代码解读**：
  这段代码的关键是`else if`——如果新节点到`S1`的距离等于直径，就加入`S2`；否则，如果到`S2`的距离等于直径，就加入`S1`。**不能同时加入**，否则输出时会把同一个节点算两次！
  比如，假设新节点到`S1`和`S2`的距离都是直径，这时随便加一个就行——因为它属于“主干道的任意一端”，不影响结果。

* **学习笔记**：细节决定成败——一定要避免集合中的重复元素！


**题解三：(来源：wxzzzz)**
* **亮点**：用`set`维护集合，代码更直观——适合新手理解！
* **核心代码片段**：
    ```cpp
    set<int> s1, s2;
    // 加入新节点
    if (dis1 == maxd) s2.insert(n);
    else if (dis2 == maxd) s1.insert(n);
    ```
* **代码解读**：
  这段代码用`set`的`insert`操作加入新节点——`set`会自动去重，但插入速度比`vector`慢。对于新手来说，`set`的代码更直观，因为不需要担心重复元素；但对于大数据来说，`vector`更高效。

* **学习笔记**：新手可以先用`set`理解思路，熟练后再换`vector`优化！


## 5. 算法可视化：像素动画演示

<visualization_intro>
为了让大家“看得到”算法的运行过程，我设计了一个**8位像素风的动画**——就像玩FC游戏一样学习树直径维护！
</visualization_intro>

### 🌟 动画主题：像素树的“主干道”追踪
- **场景设定**：屏幕左侧是一棵像素树（用不同颜色的方块表示节点：`S1`红、`S2`蓝、普通灰），右侧是“控制面板”（开始/暂停、单步、速度滑块）。
- **核心演示内容**：
  1. **节点新增**：每次点“新增节点”，屏幕上会出现一个闪烁的像素块（新节点），沿着父节点的方向“生长”，同时播放“叮”的音效；
  2. **LCA计算**：计算两点距离时，会用黄色箭头展示“向上跳父节点”的过程——比如从节点`u`跳到`anc[u][0]`，再跳到`anc[u][1]`（即祖父节点），直到找到LCA；
  3. **集合更新**：当直径延长时，旧集合的颜色会慢慢变淡，新集合的颜色会高亮，同时播放“升级”音效（比如FC游戏中的“Power Up”声）；
  4. **成功提示**：当找到新直径时，屏幕下方会弹出“新主干道长度：X”的像素文字，伴随“胜利”音效！

### 🎮 游戏化元素
- **关卡设计**：把“新增10个节点”作为一个小关卡，完成后解锁“LCA加速”技能（比如跳过重复计算）；
- **积分系统**：每成功更新一次集合，加10分；每找到新直径，加50分——积分可以用来解锁“像素皮肤”（比如把树变成“蘑菇树”）；
- **AI演示**：点“AI自动玩”，算法会自动新增节点、更新集合，就像“贪吃蛇AI”一样——你可以跟着AI的步骤，一步步理解逻辑！


## 6. 拓展练习与相似问题思考

\<similar_problems_intro\>
掌握了动态维护树直径的方法，你可以挑战这些**相似问题**，巩固所学！
\</similar_problems_intro\>

### 🌱 通用思路迁移
树直径的性质（所有直径交于一点/边），还能解决这些问题：
- 静态树的直径查询（比如找一棵树的最长路径）；
- 动态树的直径更新（比如删节点、加边）；
- 树的“中心”查询（所有直径的交点）。


### 📚 洛谷练习推荐
1. **洛谷 P1099** - 树的直径  
   🗣️ **推荐理由**：静态树的直径模板题，帮你巩固LCA和直径的基本计算；
2. **洛谷 P2921** - 动态树的直径  
   🗣️ **推荐理由**：需要处理“删节点”的情况，比本题更难，适合进阶；
3. **洛谷 P3304** - 树的直径（带权）  
   🗣️ **推荐理由**：树的边有权值，需要修改距离计算方式——拓展你的思路！


## 7. 学习心得与经验分享 (若有)

\<insights_intro\>
从题解中，我挖到了两个**超有用的经验**，分享给大家：
\</insights_intro\>

> **经验1（来自skylee）**：“用vector代替set，能快很多！”  
> **点评**：skylee提到，他的代码能跑到Rank2，就是因为用`vector`代替了`set`——`vector`的遍历速度比`set`快3-5倍！所以，写代码时要优先选择“更简单的数据结构”，除非必须用复杂的。

> **经验2（来自N1K_J）**：“一定要处理重复加入的问题！”  
> **点评**：N1K_J在代码中用`else if`避免了同一个节点被加入两个集合——这是很多新手会犯的错误！写代码时，一定要想：“这个情况会不会重复？”


\<conclusion\>
这次的分析就到这里啦！这道题的核心是**树直径的动态维护**，关键是记住“所有直径交于一点/边”的性质，用LCA快速计算距离，用集合简化端点存储。  

记住：学算法不是记代码，而是记**性质**和**思路**——比如树直径的性质，能帮你解决很多类似问题！下次我们再一起挑战更难的树论问题，加油！💪
\</conclusion\>

---

---
处理用时：109.73秒