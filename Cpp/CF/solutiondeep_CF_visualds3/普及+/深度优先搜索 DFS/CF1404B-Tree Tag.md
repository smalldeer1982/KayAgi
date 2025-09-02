# 题目信息

# Tree Tag

## 题目描述

Alice and Bob are playing a fun game of tree tag.

The game is played on a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . Recall that a tree on $ n $ vertices is an undirected, connected graph with $ n-1 $ edges.

Initially, Alice is located at vertex $ a $ , and Bob at vertex $ b $ . They take turns alternately, and Alice makes the first move. In a move, Alice can jump to a vertex with distance at most $ da $ from the current vertex. And in a move, Bob can jump to a vertex with distance at most $ db $ from the current vertex. The distance between two vertices is defined as the number of edges on the unique simple path between them. In particular, either player is allowed to stay at the same vertex in a move. Note that when performing a move, a player only occupies the starting and ending vertices of their move, not the vertices between them.

If after at most $ 10^{100} $ moves, Alice and Bob occupy the same vertex, then Alice is declared the winner. Otherwise, Bob wins.

Determine the winner if both players play optimally.

## 说明/提示

In the first test case, Alice can win by moving to vertex $ 1 $ . Then wherever Bob moves next, Alice will be able to move to the same vertex on the next move.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/49586895aed4babac3e35aba1e1c4162a3ac0674.png)In the second test case, Bob has the following strategy to win. Wherever Alice moves, Bob will always move to whichever of the two vertices $ 1 $ or $ 6 $ is farthest from Alice.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404B/514885d88075ac42c59e9da88fb4903131f99500.png)

## 样例 #1

### 输入

```
4
4 3 2 1 2
1 2
1 3
1 4
6 6 1 2 5
1 2
6 5
2 3
3 4
4 5
9 3 9 2 5
1 2
1 6
1 9
1 3
9 5
7 9
4 8
4 3
11 8 11 3 3
1 2
11 9
4 9
6 5
2 10
3 2
5 9
8 3
7 4
7 10```

### 输出

```
Alice
Bob
Alice
Alice```

# AI分析结果

# 💡 Kay的C++算法解析：Tree Tag 深入学习指南 💡

<introduction>
  今天我们来一起分析「Tree Tag」这道有趣的树上博弈题！想象一下，Alice和Bob在一棵“像素树”上玩捉迷藏——Alice要抓Bob，Bob要逃。这道题的关键不是“怎么移动”，而是“判断Alice能不能在无限步内抓住Bob”。本指南会帮你拆解核心逻辑，用树的小技巧解决博弈问题～
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：树的性质应用（直径、距离计算）+ 博弈策略分析（编程技巧应用）

🗣️ **初步分析**：
解决「Tree Tag」的关键，是**把博弈问题转化为树的“范围覆盖”问题**。简单来说，Alice能赢的本质是：她的移动范围能“锁死”Bob的逃生路径。就像玩“抓人游戏”时，如果你能守住所有出口，对方肯定跑不掉～

具体来说，Alice能赢的三种情况（对应树的三个计算）：
1. **初始距离太近**：Alice第一步就能摸到Bob（`dis(a,b) ≤ da`）；
2. **Alice的“网够大”**：Bob跳再远也跳不出Alice的两倍范围（`2×da ≥ db`）——比如Alice每次能跑5步，Bob最多跑9步，Alice两步就能追上；
3. **树太小**：Alice站在树的“正中间”，能覆盖整棵树（树的直径≤2×da）——就像在小房间里抓人，对方根本没地方躲！

这些条件都需要**计算树的直径**（树中最长的路径，用两次DFS/BFS）和**两点间距离**（用一次DFS/BFS）。比如计算直径时，先随便选个点找最远点A，再从A找最远点B，A到B的距离就是直径～

**可视化设计思路**：我们会用8位像素风（像FC游戏）展示树的结构——Alice是红色像素点，Bob是蓝色点，他们的移动范围用彩色圆圈标记。比如：
- 初始时，红色圈（Alice的范围）如果覆盖蓝色点（Bob），直接播放“叮”的胜利音效；
- 如果Alice的两倍范围能覆盖Bob的移动范围，动画会展示Alice一步步“缩小包围圈”，Bob的蓝色圈慢慢被红色圈覆盖；
- 如果树的直径很小，Alice移动到直径中点，红色圈覆盖整棵树，Bob只能“原地转圈”～


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和实践价值等方面，筛选了3份超棒的题解。它们都抓住了“三个条件”的核心，代码简洁易读～
</eval_intro>

**题解一：来源：SSerxhs（赞8）**
* **点评**：这份题解把“三个条件”的逻辑写得特别清楚！代码里用两次DFS计算树的直径，一次DFS计算Alice到Bob的距离，每一步判断都对应一个赢的条件。比如先判断初始距离，再判断Alice的范围是否覆盖Bob的移动，最后判断树的大小。变量命名也很直观（比如`dep`表示深度，`md`表示最大深度），边界处理很严谨——比如DFS时避免回走父节点。最棒的是，作者用“树的直径”这个关键性质，直接锁定了Alice能覆盖整棵树的条件，思路特别透亮！

**题解二：来源：AFOier（赞7）**
* **点评**：这题解的代码更简洁！作者用两次DFS求直径的方法很经典——第一次找最远点，第二次从最远点找直径。计算Alice到Bob的距离时，直接用DFS从Alice出发遍历，`dis[b]`就是初始距离。判断条件的顺序也很合理：先看初始距离，再看树的大小，最后看Alice的范围。代码里的`vector`邻接表写得很规范，适合刚学树结构的同学参考～

**题解三：来源：CYZZ（赞4）**
* **点评**：这份题解的“思路讲解”特别适合入门！作者用“逼进死路”“覆盖整树”这样的通俗说法，把博弈逻辑讲得很明白。代码里的`dfs`函数专门用来求最远点，计算直径的过程很清晰。最贴心的是，作者在代码里加了注释，比如“判断初始距离”“判断树的直径”，新手能快速看懂每一步在做什么～


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这题时，大家常遇到三个“卡住的点”。结合优质题解的经验，我帮你拆解成“问题+解决技巧”～
</difficulty_intro>

1. **难点1：为什么要用树的直径？**
    * **分析**：树的直径是树中最长的路径——如果Alice能覆盖直径的一半（2×da≥直径），说明她站在直径中点时，能覆盖整棵树（因为任何点到中点的距离都不超过直径的一半）。就像你站在操场跑道的中间，能看到两端的人～
    * 💡 **学习笔记**：树的直径是“覆盖整树”的关键指标！

2. **难点2：为什么2×da≥db时Alice能赢？**
    * **分析**：Bob每次最多移动db步，如果Alice的两倍范围（2×da）能覆盖Bob的移动，说明Bob不管怎么跳，下一步Alice都能追上。比如Bob跳db步，Alice只需要两步（共2×da）就能摸到他～
    * 💡 **学习笔记**：博弈问题常转化为“范围覆盖”，比谁的“网”更大！

3. **难点3：如何正确计算两点间距离？**
    * **分析**：从Alice的初始位置a出发，用DFS/BFS遍历树，记录每个点的深度（`dep`），`dep[b]`就是a到b的距离。注意DFS时要避免回走父节点（比如`if (v == fa) continue;`）～
    * 💡 **学习笔记**：树的遍历是计算距离的基础！

### ✨ 解题技巧总结
- **技巧1：问题转化**：把博弈问题转化为“范围覆盖”，用树的性质（直径、距离）代替复杂的移动模拟；
- **技巧2：直径计算**：两次DFS/BFS求直径——先找任意点的最远点，再从该点找最远点；
- **技巧3：边界处理**：DFS时一定要判断父节点，避免无限递归；多组测试用例要初始化邻接表！


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心代码**——它综合了优质题解的思路，结构清晰，能直接解决问题～
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码来自优质题解的思路整合，用两次DFS求直径，一次DFS求初始距离，逻辑简洁明了。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];  // 邻接表存树
int dep[MAXN];          // 记录深度（距离）
int farthest_node;      // 记录最远点

// DFS：找从u出发的最远点，fa是父节点
void dfs(int u, int fa) {
    for (int v : adj[u]) {
        if (v == fa) continue;  // 不回走父节点
        dep[v] = dep[u] + 1;    // 子节点深度=父节点+1
        dfs(v, u);
    }
    // 更新最远点（深度最大的点）
    if (dep[u] > dep[farthest_node]) {
        farthest_node = u;
    }
}

int main() {
    ios::sync_with_stdio(false);  // 加速输入输出
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, a, b, da, db;
        cin >> n >> a >> b >> da >> db;
        // 初始化邻接表
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        // 读入树的边
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // 步骤1：计算Alice(a)到Bob(b)的初始距离
        memset(dep, 0, sizeof(dep));
        farthest_node = a;  // 从a出发
        dfs(a, 0);
        int dis_ab = dep[b];  // b的深度就是a到b的距离
        if (dis_ab <= da) {
            cout << "Alice\n";
            continue;  // 初始距离太近，Alice赢
        }

        // 步骤2：计算树的直径
        memset(dep, 0, sizeof(dep));
        farthest_node = 1;  // 第一次DFS找任意点的最远点
        dfs(1, 0);
        int u = farthest_node;  // 第一个端点
        memset(dep, 0, sizeof(dep));
        farthest_node = u;  // 第二次DFS找直径的另一端点
        dfs(u, 0);
        int diameter = dep[farthest_node];  // 直径长度

        // 步骤3：判断Alice能否赢
        if (2 * da >= db || 2 * da >= diameter) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
    return 0;
}
```
* **代码解读概要**：
  1. **邻接表**：用`vector`存树的边，适合树的遍历；
  2. **DFS函数**：计算每个点的深度，同时找到最远点；
  3. **主逻辑**：
     - 先算Alice到Bob的初始距离，如果太近直接赢；
     - 再算树的直径（两次DFS）；
     - 最后判断Alice的范围是否覆盖Bob的移动，或覆盖整树。

---

<code_intro_selected>
接下来看**优质题解的核心片段**，学习它们的“小技巧”～
</code_intro_selected>

**题解一：来源：SSerxhs**
* **亮点**：用`md`数组记录每个点的最大深度，计算直径更直观。
* **核心代码片段**：
```cpp
void dfs(int x) {
    ed[x] = 1; md[x] = dep[x];
    for (int i = fir[x]; i; i = nxt[i]) if (!ed[lj[i]]) {
        dep[lj[i]] = dep[x] + 1;
        dfs(lj[i]);
        md[x] = max(md[x], md[lj[i]]);  // 更新当前点的最大深度
    }
}
```
* **代码解读**：
  这个`dfs`函数里，`md[x]`表示以x为根的子树中的最大深度。比如，当遍历子节点`lj[i]`时，`md[x]`会取自己的深度和子节点的`md`最大值。这样，最后`md[b]`就是以b为根的子树的最大深度——用来找直径的端点～
* 💡 **学习笔记**：用`md`数组记录子树最大深度，是计算树直径的另一种方法！

**题解二：来源：AFOier**
* **亮点**：用`vector`邻接表，代码更简洁。
* **核心代码片段**：
```cpp
void dfs(int w, int fa) {
    dis[w] = dis[fa] + 1;
    for(int i = 0; i < (int)e[w].size(); i++) {
        int ver = e[w][i];
        if(ver != fa) dfs(ver, w);
    }
}
```
* **代码解读**：
  这个`dfs`函数直接用`vector`的`size()`遍历邻接表，`dis[w]`是w的深度。比如，从a出发调用`dfs(a, 0)`，`dis[b]`就是a到b的距离——写法特别简洁！
* 💡 **学习笔记**：`vector`邻接表比数组邻接表更易写，适合新手～


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“亲眼看到”Alice怎么抓Bob，我设计了一个**8位像素风的动画**——像玩《超级马里奥》一样，直观感受“范围覆盖”的逻辑！
</visualization_intro>

### 🎮 动画设计方案
**动画主题**：像素树的“抓人游戏”（FC红白机风格）
**核心演示内容**：展示Alice的三个赢的条件，用像素点、彩色圈和音效强化理解。

#### 1. 场景初始化（8位像素风）
- **树的展示**：用绿色像素块表示树的节点，灰色线条表示边（像FC游戏里的“迷宫”）；
- **角色位置**：Alice是红色像素点（初始在a），Bob是蓝色像素点（初始在b）；
- **控制面板**：屏幕下方有“开始/暂停”“单步”“重置”按钮，还有速度滑块（从“慢”到“快”）；
- **背景音乐**：循环播放8位风格的轻松BGM（像《冒险岛》的背景音）。

#### 2. 核心步骤演示（结合动画+音效）
**Case 1：初始距离≤da**
- Alice的红色圈（半径da）直接覆盖Bob的蓝色点；
- 播放“叮”的音效，Alice移动到Bob的位置，蓝色点变成红色，屏幕显示“Alice Win！”。

**Case 2：2×da≥db**
- Alice的红色圈（半径da）慢慢扩大到两倍（模拟“两步的范围”）；
- Bob的蓝色圈（半径db）被红色圈覆盖；
- 播放“哒哒哒”的逼近音效，Alice一步步向Bob移动，最后红色圈完全包裹蓝色圈，显示“Alice Win！”。

**Case 3：树的直径≤2×da**
- 动画先展示树的直径（用黄色线条标出最长路径）；
- Alice移动到直径中点，红色圈覆盖整棵树；
- Bob的蓝色点不管怎么移动，都在红色圈里；
- 播放“嗡嗡”的“范围锁定”音效，最后显示“Alice Win！”。

#### 3. 交互设计
- **单步执行**：点击“单步”，动画走一步（比如Alice移动一次，Bob移动一次）；
- **自动播放**：点击“开始”，动画按滑块速度自动运行；
- **重置**：点击“重置”，回到初始状态，重新演示。

#### 4. 游戏化元素
- **关卡设计**：把三个Case做成三个“小关卡”，完成一个关卡解锁下一个；
- **积分奖励**：每完成一个关卡，获得100分，积分可以解锁“像素皮肤”（比如Alice变成粉色，Bob变成绿色）；
- **音效反馈**：移动时播放“哔”的声音，胜利时播放上扬的“叮—”，失败时播放短促的“嗡”。

<visualization_conclusion>
这个动画用像素风和游戏化元素，把抽象的“范围覆盖”变成了直观的“抓人与逃跑”。你可以自己操作，看Alice怎么“锁死”Bob的路径——比死记公式有趣100倍！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了“树的直径+范围覆盖”的思路，你可以解决更多树的博弈或覆盖问题～
</similar_problems_intro>

### 通用思路迁移
- 树的直径可以用来解决“覆盖整树”的问题（比如医院设置、消防栓放置）；
- 范围覆盖的思路可以用来解决“追击问题”（比如猫抓老鼠、机器人巡逻）；
- 博弈问题常转化为“谁的范围更大”（比如棋类游戏、资源争夺）。

### 洛谷练习推荐
1. **洛谷 P1099 树网的核**
   * 🗣️ **推荐理由**：这题要找树网的“核”（覆盖所有点的最短路径），和本题的“覆盖整树”思路一样，能巩固树的直径应用！
2. **洛谷 P2921 [USACO08DEC]在农场万圣节**
   * 🗣️ **推荐理由**：这题要找树中的“循环路径”，需要用到树的遍历和距离计算，能练DFS/BFS的基础！
3. **洛谷 P1364 医院设置**
   * 🗣️ **推荐理由**：这题要找“最优医院位置”（使所有点到医院的距离和最小），和本题的“直径中点”思路类似，能深化树的性质理解！


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解里有很多“踩坑经验”，比如：
</insights_intro>

> **参考经验（来自SSerxhs）**：“我一开始忘记初始化`ed`数组（标记是否访问过），导致DFS无限递归，程序崩溃。后来加了`memset(ed+1,0,n*sizeof(bool))`才解决！”
>
> **点评**：这个经验太重要了！多组测试用例时，一定要初始化所有数组（比如邻接表、深度数组、访问标记），否则会出现“上次的数据残留”问题——比如DFS时走到已经访问过的节点，无限循环～


<conclusion>
本次关于「Tree Tag」的分析就到这里啦！这道题的核心是“把博弈转化为树的范围覆盖”，用两次DFS求直径，一次DFS求距离。记住：**树的问题常和“最长路径”（直径）、“最短路径”（距离）有关**！下次遇到树的博弈题，试试先想“谁的范围更大”～

编程能力的提升，在于“多练+多总结”。比如今天学了树的直径，明天就去做P1099——你会发现，原来“核”就是直径的中间部分！加油，下次我们再一起解决新的问题～💪
</conclusion>

---
处理用时：209.57秒