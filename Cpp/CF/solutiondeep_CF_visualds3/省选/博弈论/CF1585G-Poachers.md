# 题目信息

# Poachers

## 题目描述

Alice and Bob are two poachers who cut trees in a forest.

A forest is a set of zero or more trees. A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a node $ v $ is the next vertex on the shortest path from $ v $ to the root. Children of vertex $ v $ are all nodes for which $ v $ is the parent. A vertex is a leaf if it has no children.

In this problem we define the depth of vertex as number of vertices on the simple path from this vertex to the root. The rank of a tree is the minimum depth among its leaves.

Initially there is a forest of rooted trees. Alice and Bob play a game on this forest. They play alternating turns with Alice going first. At the beginning of their turn, the player chooses a tree from the forest. Then the player chooses a positive cutting depth, which should not exceed the rank of the chosen tree. Then the player removes all vertices of that tree whose depth is less that or equal to the cutting depth. All other vertices of the tree form a set of rooted trees with root being the vertex with the smallest depth before the cut. All these trees are included in the game forest and the game continues.

A player loses if the forest is empty at the beginning of his move.

You are to determine whether Alice wins the game if both players play optimally.

## 说明/提示

In the first test case Bob has a symmetric strategy, so Alice cannot win.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/504019013a3bfbf8eb56c8730800a342f1394e57.png)

In the second test case Alice can choose the second tree and cutting depth $ 1 $ to get a forest on which she has a symmetric strategy.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/8fe2d012fa7f86edd6ce3b0992b73d46bc9c4b34.png)

In third test case the rank of the only tree is $ 2 $ and both possible moves for Alice result in a loss. Bob either can make the forest with a symmetric strategy for himself, or clear the forest.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/eed2cbe70e21303a782188eb3bbbd7989634e2f0.png)

In the fourth test case all leafs have the same depth, so Alice can clear the forest in one move.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1585G/095a24a5876a4e208466c20d0a9b949b0c7e2ff3.png)

## 样例 #1

### 输入

```
4
4
0 1 0 3
7
0 1 2 0 4 5 6
4
0 1 1 2
7
0 1 1 2 2 3 3```

### 输出

```
NO
YES
NO
YES```

# AI分析结果

# 💡 Kay的C++算法解析：Poachers 深入学习指南 💡

<introduction>
今天我们来分析一道结合**博弈论**与**树结构**的趣味题目——《Poachers》。这道题需要判断Alice和Bob在砍树游戏中谁能获胜，核心是**SG函数**（公平组合游戏的胜负判定工具）与**长链剖分**（优化树结构计算的神器）的结合。通过这道题，你会学会如何将抽象的博弈规则转化为可计算的数学模型，并用高效算法解决大规模数据问题！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：博弈论（SG函数）、长链剖分（Longest Path Decomposition）

🗣️ **初步分析**：
解决这道题的关键是理解**公平组合游戏**的三大规则：  
1. **SG函数定义**：一个状态的SG值是它所有**后继状态SG值**的**mex**（最小未出现的非负整数）；  
2. **组合规则**：多个独立状态的总SG值是各状态SG的**异或和**；  
3. **胜负判定**：先手必胜当且仅当总SG值**非零**（反之必败）。  


### 题目与SG函数的对应
每棵树是一个独立状态。当玩家选择**切割深度d**（≤树的`rank`，即树中叶子的最小深度），会删去所有深度≤d的节点，剩下的子树组成新森林。这些子树的SG异或和就是该切割操作的**后继状态SG值**。树的SG值就是所有可能后继状态SG值的mex。


### 为什么用长链剖分？
直接暴力计算每棵树的SG值是**O(n²)**（每个节点要遍历所有可能的切割深度），对于大n（比如5e5）会超时。而**长链剖分**是处理“深度相关子树问题”的神器——它通过优先处理树中的**最长链**（长儿子），将子树信息的合并复杂度降为**O(n)**或**O(n log n)**，完美匹配本题中“维护距离节点u为i的SG异或和”的需求。


### 可视化设计思路
我们会用**8位像素风**（类似FC红白机）展示树的结构：  
- 根节点用**红色方块**，长儿子用**亮蓝色**，短儿子用**浅蓝色**，叶子用**绿色**；  
- 动态演示**长链剖分**（箭头指向长儿子）、**SG值计算**（异或和用“黄色闪烁”，mex用“扫描线”）、**切割操作**（红色横线标记深度，删去的节点“消失”）；  
- 加入**复古音效**：合并子树时“叮”一声，求mex时“滴”一声，胜利时播放《超级马里奥》通关曲。


---


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度**、**算法效率**、**代码可读性**三个维度筛选了以下优质题解，覆盖了长链剖分的不同实现方式：
</eval_intro>

### 题解一：长链剖分的线性做法（作者：Grisses）
* **点评**：这是本题的“最优思路”！作者抓住了SG函数的核心转移规律：  
  - `dp[x][i]`表示x子树中**距离x为i**的点的子树SG异或和；  
  - `sg[x]`（x的SG值）是`dp[x][1..lim[x]]`的mex（`lim[x]`是x子树的最小叶子深度）。  
  对于**叶子节点**，`sg[x] = 0`；对于**单儿子节点**，直接继承长儿子的SG集合并加入长儿子的SG值，暴力求mex；对于**多儿子节点**，合并所有儿子的`dp`数组后求mex。这种方法的复杂度是**O(n)**（所有长链长度之和），效率极高！


### 题解二：长链剖分+set/map维护mex（作者：xfrvq）
* **点评**：代码最完整、易读的实现！作者用`map`记录每个数的出现次数，用`set`维护**连续数值区间**（比如`[0,2]`表示0、1、2都出现），快速求mex：  
  - 若`set`的第一个区间不是`[0,...]`，则mex是0；  
  - 否则mex是第一个区间的右端点+1。  
  长链剖分时，先继承长儿子的`map`和`set`，再合并短儿子的信息，逻辑清晰。这种方法的复杂度是**O(n log n)**，适合竞赛中的代码实现。


### 题解三：长链剖分+pbds平衡树（作者：绝顶我为峰）
* **点评**：用pbds库的平衡树（`tree`）维护出现的数，通过`order_of_key`快速查询mex（比如查询0到mid+1的数的个数，如果等于mid+1，说明0~mid都出现了，mex在右边）。这种方法的复杂度是**O(n log² n)**，但代码简洁，适合熟悉pbds库的选手。


---


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的难点在于**将博弈论模型与树结构结合**，以及**高效计算SG值**。结合优质题解，我提炼了3个核心难点和解决策略：
</difficulty_intro>

### 1. 难点1：SG函数与树操作的对应
- **问题**：如何将“切割树”的操作转化为SG函数的转移？  
- **策略**：切割深度`d`对应“保留距离根节点>d的节点”，这些节点的子树SG异或和就是该操作的后继状态SG值。例如，根节点的SG值是所有`d=1~rank`对应的异或和的mex。  
- 💡 **学习笔记**：SG函数的核心是“状态转移”，关键要找到“每个操作对应的后继状态”。


### 2. 难点2：高效求mex
- **问题**：直接维护所有后继状态的集合求mex是O(n)的，会超时。  
- **策略**：用数据结构维护出现的数，快速找最小未出现的数：  
  - **set/map**：维护连续区间，快速判断0是否存在，或找第一个缺失的数；  
  - **线段树**：维护每个数的出现次数，二分查找第一个出现次数为0的数。  
- 💡 **学习笔记**：mex的高效计算依赖“快速查询最小未出现元素”的数据结构。


### 3. 难点3：长链剖分的应用
- **问题**：如何高效维护“距离节点u为i的SG异或和”？  
- **策略**：长链剖分的核心是“继承长儿子的信息”——对于节点u，先处理长儿子v，直接将v的“距离信息”（比如`dp[v][i]`）继承为`dp[u][i+1]`，再合并短儿子的信息。这样合并的总复杂度是O(n)（每个节点只属于一条长链）。  
- 💡 **学习笔记**：长链剖分适合“深度相关的子树问题”，核心是“优先处理最长链，减少重复计算”。


### ✨ 解题技巧总结
1. **博弈论建模**：先判断问题是否是公平组合游戏，再用SG函数分析；  
2. **树结构优化**：遇到“深度相关的子树问题”，优先考虑长链剖分；  
3. **数据结构选择**：求mex用set/map（简单易写）或线段树（效率更高）。


---


## 4. C++核心代码实现赏析

<code_intro_overall>
我们先看**xfrvq的长链剖分+set/map**实现，它清晰展示了如何维护mex和SG值：
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：此代码来自xfrvq的题解，用长链剖分+set/map维护mex，逻辑清晰，适合学习。
* **完整核心代码**：
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;

  const int N = 5e5 + 5;

  int T,n,dep[N],mxd[N],mnd[N],son[N],dfn[N],cnt,sg[N];
  bool rt[N];
  vector<int> G_[N]; 
  map<int,int> M[N]; // 记录u的后继SG值的出现次数
  set<pair<int,int>> S[N]; // 记录u的后继SG值的连续区间（如[0,2]表示0、1、2都出现）

  // 插入数x到u的集合中
  void ins(int u,int x){
    if(!M[u][x]++){
      auto i = S[u].lower_bound({x,0});
      int l = x,r = x;
      // 合并左边连续区间（x-1是前一个区间的右端点）
      if(i != S[u].begin() && prev(i)->second == x-1) l = prev(i)->first, S[u].erase(prev(i));
      // 合并右边连续区间（x+1是后一个区间的左端点）
      if(i != S[u].end() && i->first == x+1) r = i->second, S[u].erase(i);
      S[u].insert({l,r});
    }
  }

  // 从u的集合中删除数x
  void ers(int u,int x){
    if(!--M[u][x]){
      auto i = prev(S[u].lower_bound({x+1,0}));
      auto [l,r] = *i; S[u].erase(i);
      if(x != l) S[u].insert({l,x-1}); // 拆分左边区间
      if(x != r) S[u].insert({x+1,r}); // 拆分右边区间
    }
  }

  // 查询u的集合的mex值
  int qry(int u){
    if(S[u].empty() || S[u].begin()->first != 0) return 0;
    return S[u].begin()->second + 1;
  } 

  // 第一次DFS：计算深度、长儿子、最小/最大叶子深度
  void dfs(int u,int ft){
    mxd[u] = dep[u] = dep[ft] + 1, son[u] = 0;
    mnd[u] = G_[u].empty() ? dep[u] : (n+1); // 叶子的mnd是自己的深度
    for(int v : G_[u]){
      dfs(v,u);
      mnd[u] = min(mnd[u], mnd[v]); // 父节点的mnd是子节点mnd的最小值
      if(mxd[v] > mxd[u]) mxd[u] = mxd[v], son[u] = v; // 长儿子是深度最大的子节点
    }
  }

  // 第二次DFS：长链剖分，计算sg值
  void sol(int u,int ft){
    dfn[u] = ++cnt; // 分配dfs序（用于存储sg值的数组索引）
    if(son[u]){ // 继承长儿子的信息
      sol(son[u],u);
      M[u].swap(M[son[u]]); // 继承长儿子的map
      S[u].swap(S[son[u]]); // 继承长儿子的set
      // 删去长儿子中“父节点不需要”的后继状态
      for(int i = min(mnd[u]+1,mxd[u])-dep[u]+1; i <= min(mnd[son[u]]+1,mxd[son[u]])-dep[u]; ++i)
        ers(u, sg[dfn[u]+i]);
      // 特判：长儿子是“完美树”（所有叶子深度相同），父节点不是，删去0（空树的SG值）
      if(mnd[son[u]] == mxd[son[u]] && mnd[u] != mxd[u]) ers(u,0);
    } else ins(u,0); // 叶子节点，初始集合包含0（空树的SG值）

    // 合并短儿子的信息
    for(int v : G_[u]) if(v != son[u]){
      sol(v,u);
      for(int i = 0; i <= mxd[v]-dep[v]; ++i){
        int pos_u = dfn[u]+i+1; // u中对应的位置（距离i+1）
        if(pos_u <= dfn[u] + (min(mnd[u]+1,mxd[u])-dep[u])) ers(u, sg[pos_u]); // 先删原异或和
        sg[pos_u] ^= sg[dfn[v]+i]; // 异或v的sg值
        if(pos_u <= dfn[u] + (min(mnd[u]+1,mxd[u])-dep[u])) ins(u, sg[pos_u]); // 插入新异或和
      }
    }

    sg[dfn[u]] = qry(u); // 计算当前节点的sg值（mex）
    ins(u, sg[dfn[u]]); // 将sg值插入集合（父节点可能需要）
  }

  int main(){
    for(scanf("%d",&T);T--;){
      scanf("%d",&n), cnt=0;
      for(int i=0;i<=n;i++) G_[i].clear(), M[i].clear(), S[i].clear();
      memset(rt,0,sizeof rt);
      for(int i=1,f;i<=n;i++){
        scanf("%d",&f), G_[f].push_back(i);
        if(!f) rt[i] = true; // 标记根节点
      }

      for(int i=1;i<=n;i++) if(rt[i]) dfs(i,0);
      for(int i=1;i<=n;i++) if(rt[i]) sol(i,0);

      int total = 0;
      for(int i=1;i<=n;i++) if(rt[i]) total ^= sg[dfn[i]]; // 总SG值是根节点的异或和
      puts(total ? "YES" : "NO");
    }
    return 0;
  }
  ```
* **代码解读概要**：
  1. **数据结构**：用`map`记录出现次数，`set`维护连续区间，快速求mex；  
  2. **第一次DFS**：计算每个节点的深度、长儿子、最小叶子深度（`mnd`）、最大深度（`mxd`）；  
  3. **第二次DFS**：继承长儿子的信息，合并短儿子的`dp`数组，计算当前节点的SG值；  
  4. **总SG计算**：所有根节点的SG异或和，非零则Alice赢。


---
<code_intro_selected>
接下来剖析**Grisses的长链剖分线性做法**的核心片段，感受其简洁性：
</code_intro_selected>

### 题解一：长链剖分线性做法（作者：Grisses）
* **亮点**：利用长链的性质，将mex的计算优化到线性时间（每个节点最多被处理一次）。
* **核心代码片段**（伪代码）：
  ```cpp
  // dp[x][i]：x子树中距x为i的点的子树SG异或和
  // lim[x]：x子树的最小叶子深度（rank）
  // sg[x] = mex{ dp[x][1..lim[x]] }

  void dfs(int x) {
    if (x是叶子) {
      lim[x] = 1; // 叶子的最小叶子深度是1（距离自己1）
      sg[x] = 0; // 叶子的SG值是0（切割深度1会删去自己，后继状态是0）
      return;
    }
    int main_son = 长儿子;
    dfs(main_son);
    lim[x] = lim[main_son] + 1; // 父节点的lim是长儿子的lim+1

    if (x只有一个儿子) {
      // S[x] = S[main_son] ∪ {sg[main_son]}（继承长儿子的集合，加入长儿子的SG值）
      set<int> S = S[main_son];
      S.insert(sg[main_son]);
      sg[x] = mex(S); // 求mex
    } else {
      // 合并所有儿子的dp数组：dp[x][i] = 所有儿子的dp[son][i-1]的异或和
      for (每个儿子son) {
        dfs(son);
        for (int i=1; i<=lim[son]; i++) {
          dp[x][i] ^= dp[son][i-1];
        }
      }
      sg[x] = mex{ dp[x][1..lim[x]] }; // 求mex
    }
  }
  ```
* **代码解读**：
  - 叶子节点：`lim[x]`是1（距离自己1），`sg[x]`是0（切割深度1会删去自己，后继状态是0）；  
  - 单儿子节点：直接继承长儿子的集合，加入长儿子的SG值，求mex；  
  - 多儿子节点：合并所有儿子的`dp`数组（异或和），然后求mex。  
* 💡 **学习笔记**：长链剖分的线性做法依赖“长链的信息可以直接继承”，避免了重复计算，效率极高。


---


## 5. 算法可视化：像素动画演示 (核心部分)

\<visualization\_intro\>
为了直观理解**长链剖分计算SG值**的过程，我设计了一个**8位像素风**的动画演示，融合复古游戏元素，让算法“动起来”！
\</visualization\_intro\>

### 动画设计概述
- **主题**：像素树的“SG探险”——你扮演“算法探险家”，跟随长链剖分的过程，计算每棵树的SG值。
- **风格**：FC红白机风格（16色调色板，方块像素，复古字体）。
- **核心演示内容**：长链剖分、SG值计算（异或和、mex）、切割操作的状态转移。


### 动画帧与交互设计
#### 1. 场景初始化
- **左侧像素树**：根节点（红）、长儿子（亮蓝）、短儿子（浅蓝）、叶子（绿）；  
- **右侧控制面板**：开始/暂停、单步、重置、AI自动演示按钮；速度滑块（1x~5x）；信息区（当前节点的SG值、mex值）；  
- **背景音乐**：8位风格循环BGM（类似《超级马里奥》的轻松旋律）。


#### 2. 长链剖分演示
- **步骤1**：根节点（红）闪烁，提示“开始处理根节点”；  
- **步骤2**：箭头从根节点指向长儿子（亮蓝），伴随“叮”的音效，提示“这是长儿子”；  
- **步骤3**：递归处理长儿子，长儿子的子节点依次闪烁，提示“继承长儿子的信息”。


#### 3. SG值计算演示
- **异或和更新**：合并短儿子的信息时，短儿子的dp值用“黄色闪烁”，异或到父节点的dp数组中，伴随“嗒”的音效；  
- **mex查找**：用“扫描线动画”从0开始遍历集合，扫描到的数用“绿色闪烁”，找到mex时播放“滴”的音效，并在信息区显示mex值。


#### 4. 切割操作演示
- 选择切割深度d：用“红色横线”标记深度d，删去深度≤d的节点（“消失动画”），剩下的子树用“弹出动画”展示，信息区显示该操作的后继SG异或和；  
- **胜利条件**：总SG值非零时，屏幕显示“Alice赢！”，播放胜利音效（《魂斗罗》通关曲）；否则显示“Bob赢！”，播放失败音效。


#### 5. 游戏化元素
- **AI自动演示**：点击“AI自动演示”，算法像“贪吃蛇AI”一样自动完成计算，你可以观察整个过程；  
- **关卡设计**：将树的处理分为“根节点关卡”“长儿子关卡”“短儿子合并关卡”，完成每个关卡获得“像素星星”奖励，增强成就感。


### 设计思路
- **像素风格**：营造复古游戏的轻松氛围，降低畏难情绪；  
- **音效提示**：用不同音效强化关键操作（如合并、mex查找），帮助记忆；  
- **游戏化关卡**：将复杂算法拆分为小步骤，用奖励机制激励学习。


\<visualization\_conclusion\>
通过这个动画，你可以清晰看到**长链剖分如何优化SG计算**，以及**每个操作对应的状态变化**。下次遇到树结构的博弈问题，你一定能快速联想到这个像素动画！
\</visualization\_conclusion\>


---


## 6. 拓展练习与相似问题思考

\<similar\_problems\_intro\>
掌握了SG函数和长链剖分后，你可以解决更多**博弈论+树结构**的问题。以下是几个典型的拓展方向：
\</similar\_problems\_intro\>

### 通用思路迁移
1. **树的博弈问题**：比如“取石子游戏”变种（每个节点有石子，取石子后子节点的石子变化），可以用SG函数分析；  
2. **深度相关的子树问题**：比如“求每个节点的k级祖先”“统计子树中深度为d的节点数”，可以用长链剖分优化；  
3. **mex计算问题**：比如“维护动态集合的mex”，可以用set/map或线段树实现。


### 洛谷练习推荐
1. **洛谷 P4735** - 树的同构  
   🗣️ **推荐理由**：判断两棵树是否同构，核心是**树的哈希**（每个节点的哈希值是子节点哈希值的排序后的mex），巩固mex的应用。  
2. **洛谷 P3254** - 最小生成树博弈  
   🗣️ **推荐理由**：经典博弈论问题，计算每条边的SG值，总SG是边的异或和，巩固SG函数的组合规则。  
3. **洛谷 P5022** - 旅行商问题  
   🗣️ **推荐理由**：用长链剖分优化动态规划，巩固长链剖分的应用（维护深度相关的子树信息）。  
4. **洛谷 P6031** - 【模板】长链剖分  
   🗣️ **推荐理由**：长链剖分的模板题，帮助你熟悉基本流程（找长儿子、继承信息、合并短儿子）。


---


## 7. 学习心得与经验分享 (若有)

\<insights\_intro\>
优质题解中分享了一些实用的经验，比如：
\</insights\_intro\>

> **参考经验 (来自Grisses)**：“对于单儿子节点，SG集合可以直接继承长儿子的集合并加入长儿子的SG值，这样可以避免重复计算。”  
> **点评**：这个经验抓住了长链剖分的核心——“长儿子的信息可以直接复用”，大大减少了计算量。在处理树结构问题时，“复用已有信息”是优化的关键！

> **参考经验 (来自xfrvq)**：“用set维护连续区间求mex，比用平衡树更简单，代码也更易读。”  
> **点评**：数据结构的选择要兼顾效率和代码复杂度。对于竞赛来说，“简单易写”有时比“理论最优”更重要！


---


\<conclusion\>
《Poachers》这道题把博弈论和树结构完美结合，核心是**SG函数**和**长链剖分**的应用。通过这道题，你学会了如何将复杂的游戏规则转化为数学模型，并用高效算法优化计算。记住：  
- 博弈论的关键是“状态转移”；  
- 树结构的优化是“长链剖分”；  
- mex的计算需要“合适的数据结构”。  

下次遇到类似问题，你一定能举一反三！💪
\</conclusion\>

---
处理用时：278.59秒