# 题目信息

# Infected Tree

## 题目描述

Byteland is a beautiful land known because of its beautiful trees.

Misha has found a binary tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . A binary tree is an acyclic connected bidirectional graph containing $ n $ vertices and $ n - 1 $ edges. Each vertex has a degree at most $ 3 $ , whereas the root is the vertex with the number $ 1 $ and it has a degree at most $ 2 $ .

Unfortunately, the root got infected.

The following process happens $ n $ times:

- Misha either chooses a non-infected (and not deleted) vertex and deletes it with all edges which have an end in this vertex or just does nothing.
- Then, the infection spreads to each vertex that is connected by an edge to an already infected vertex (all already infected vertices remain infected).

As Misha does not have much time to think, please tell him what is the maximum number of vertices he can save from the infection (note that deleted vertices are not counted as saved).

## 说明/提示

In the first test case, the only possible action is to delete vertex $ 2 $ , after which we save $ 0 $ vertices in total.

In the second test case, if we delete vertex $ 2 $ , we can save vertices $ 3 $ and $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1689C/1f479df0f6df9637a1dfee43da055c650bdae647.png)

## 样例 #1

### 输入

```
4
2
1 2
4
1 2
2 3
2 4
7
1 2
1 5
2 3
2 4
5 6
5 7
15
1 2
2 3
3 4
4 5
4 6
3 7
2 8
1 9
9 10
9 11
10 12
10 13
11 14
11 15```

### 输出

```
0
2
2
10```

# AI分析结果

# 💡 Kay的C++算法解析：Infected Tree 深入学习指南 💡

## 引言
今天我们要拆解一道**树形动态规划（树形DP）**的经典题目——《Infected Tree》。这道题的核心是“如何在病毒扩散的限制下，最大化保留树中的节点”。通过本指南，你会理解树形DP的底层逻辑，掌握树结构问题的解题套路，还能通过像素动画直观看到算法运行过程！


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：树形动态规划（树形DP）

🗣️ **初步分析**：
树形DP就像给树的每个节点“贴评分标签”——每个节点的标签值代表**以该节点为根的子树的最优解**，然后从叶子往根“汇总”这些标签。本题中，我们需要计算**当某个节点被感染时，其子树能保留的最大未感染节点数**，这正好契合树形DP“自底向上”的计算逻辑。

### 题目核心逻辑
- 二叉树的根节点（1号）被感染，每回合可以删除一个未感染节点，之后病毒会扩散到所有相邻的未感染节点。
- 目标：最大化**未被感染且未被删除**的节点数（删除的节点不算“保存”）。

### 树形DP的应用
当节点`u`被感染时，我们只能选择**删除它的一个子节点**（因为是二叉树，最多两个子节点）：
- 若删除左子节点`lson`，则`lson`的子树除了它自己都能保存（数量为`size[lson]-1`），右子节点`rson`会被感染，需加上`rson`的最优解`dp[rson]`。
- 若删除右子节点`rson`，同理可得保存数为`dp[lson] + size[rson]-1`。
- 我们要在两种选择中取最大值，这就是**状态转移方程**：  
  `dp[u] = max(dp[lson] + size[rson]-1, dp[rson] + size[lson]-1)`

### 可视化设计思路
我们会用**8位红白机风格**做一个“像素树防疫游戏”：
- 根节点1是红色（感染），子节点是绿色，叶子是浅绿色。
- DFS遍历时用黄色箭头指示当前节点，计算`size`（子树大小）时播放“滴”声，计算`dp`时播放“叮”声。
- 选择删除子节点时，该节点变灰色，同时显示当前保存数的变化。


## 2. 精选优质题解参考

为你筛选了3份**思路清晰、代码规范**的优质题解，覆盖了树形DP的核心逻辑：

### 题解一（作者：冬天的雨）
- **点评**：这份题解的**sum变量优化**是亮点！它用`sum`存储所有子节点的`dp`之和，这样计算“删去当前子节点后的另一个子节点dp值”时，只需用`sum - dp[v]`，避免了重复遍历子节点。代码结构严谨，多组数据的初始化（清零`head`数组）也处理得很到位，是竞赛级的标准写法。

### 题解二（作者：qzhwlzy）
- **点评**：代码简洁到“极致”！用`res`代替`sum`，变量名更直观，注释里特别提醒“数组要开够”——这是竞赛中最容易踩的坑（比如`MAXN`要设为`3e5+5`，否则会越界）。适合入门学习者快速理解树形DP的核心流程。

### 题解三（作者：KukCair）
- **点评**：用`vector`存储邻接表，代码更现代！DFS函数直接返回子树大小`sz[x]`，递归时可以直接累加，逻辑更连贯。范围`for`循环（`for (int v : vc[x])`）简化了子节点遍历，可读性很高。


## 3. 核心难点辨析与解题策略

树形DP的难点在于**状态定义**和**转移逻辑**，结合题解总结3个关键问题：

### 关键点1：状态定义——`dp[u]`到底代表什么？
- **问题**：为什么`dp[u]`是“`u`被感染时，其子树能保留的最大节点数”？
- **分析**：树形DP的核心是“子问题的最优解”。父节点的选择（删左或右子节点）会影响子节点的状态，因此必须从叶子往根计算——叶子节点的`dp`值是0（没有子节点，被感染时无法保留任何节点），父节点的`dp`值由子节点的结果推导而来。
- 💡 **学习笔记**：状态定义要“精准覆盖子问题”，否则转移逻辑会全错！

### 关键点2：转移方程——为什么是`size[son]-1`？
- **问题**：删除子节点`son`后，为什么保存数是`size[son]-1`？
- **分析**：`size[son]`是`son`的子树大小（包括`son`自己）。删除`son`后，它的子树中**除了`son`自己**都能保留（因为`son`被删除，病毒无法扩散到它的子树），所以是`size[son]-1`。
- 💡 **学习笔记**：转移方程要“对应实际操作的结果”，每一步都要问自己“这个值代表什么”。

### 关键点3：多组数据——为什么要清零数组？
- **问题**：多组数据时，为什么要清空`head`、`size`、`dp`数组？
- **分析**：如果不清零，上一组数据的邻接表、`size`值会残留，导致当前组的DFS遍历错误。比如`head[u]`残留上一组的边，会遍历到不属于当前树的节点。
- 💡 **学习笔记**：多组数据的初始化是“必做项”，哪怕题目没提醒也要记得！

### ✨ 解题技巧总结
1. **邻接表存储树**：用`struct Edge`或`vector`存储树的边，是树形DP的标准操作。
2. **sum变量优化**：计算子节点`dp`之和，避免重复遍历子节点，提高效率。
3. **自底向上DFS**：先递归到叶子节点，再回溯计算`size`和`dp`，确保子节点的结果先于父节点计算。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
* **说明**：综合了冬天的雨和KukCair的题解，用`vector`存储邻接表，代码简洁且易读。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 3e5 + 5;

vector<int> G[MAXN];  // 邻接表存储树
int size_[MAXN], dp[MAXN];  // size_[u]: u的子树大小；dp[u]: u被感染时的最大保存数

void dfs(int u, int fa) {
    size_[u] = 1;  // 子树大小初始化为1（自己）
    dp[u] = 0;     // 初始保存数为0
    int sum = 0;   // 子节点的dp之和

    // 第一次遍历：计算size_和sum
    for (int v : G[u]) {
        if (v == fa) continue;  // 跳过父节点
        dfs(v, u);              // 递归计算子节点
        size_[u] += size_[v];   // 累加子树大小
        sum += dp[v];           // 累加子节点的dp值
    }

    // 第二次遍历：计算dp[u]
    for (int v : G[u]) {
        if (v == fa) continue;
        // 删去v时的保存数：sum - dp[v]（另一个子节点的dp） + size_[v]-1（v的子树保存数）
        dp[u] = max(dp[u], sum - dp[v] + size_[v] - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        // 初始化邻接表
        for (int i = 1; i <= n; ++i) G[i].clear();
        memset(size_, 0, sizeof(size_));
        memset(dp, 0, sizeof(dp));

        // 读入边
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        dfs(1, 0);  // 根节点是1，父节点是0（不存在）
        cout << dp[1] << '\n';  // 根节点的dp值就是答案
    }
    return 0;
}
```
* **代码解读概要**：
  1. 用`vector`存储邻接表`G`，更简洁。
  2. `dfs`函数**自底向上**计算`size_`（子树大小）和`dp`（最优保存数）。
  3. `sum`变量存储子节点的`dp`之和，避免重复计算。
  4. 多组数据时，清空`G`、`size_`、`dp`数组，避免残留数据。

### 题解一（冬天的雨）核心片段赏析
* **亮点**：`sum`变量优化转移计算。
* **核心代码片段**：
```cpp
int sum = 0;
for (int i = head[u]; i; i = edge[i].pre) {
    int v = edge[i].to;
    if (v == fa) continue;
    dfs(v, u);
    size_[u] += size_[v];
    sum += dp[v];
}
for (int i = head[u]; i; i = edge[i].pre) {
    int v = edge[i].to;
    if (v == fa) continue;
    dp[u] = max(dp[u], sum - dp[v] + size_[v] - 1);
}
```
* **代码解读**：
  - 第一次循环：计算`size_`（子树大小）和`sum`（子节点`dp`之和）。
  - 第二次循环：遍历每个子节点`v`，计算“删去`v`时的保存数”——`sum - dp[v]`是另一个子节点的`dp`值，`size_[v]-1`是`v`的子树保存数，取最大值作为`dp[u]`。
* 💡 **学习笔记**：`sum`变量把两次遍历的时间复杂度从`O(n^2)`降到`O(n)`，是树形DP的常用优化技巧！


## 5. 算法可视化：像素动画演示（核心部分）

### 动画演示主题：像素树的“防疫大作战”（8位红白机风格）
我们用**Canvas+JavaScript**实现一个复古游戏式动画，让你“看”到树形DP的每一步！

### 核心设计细节
1. **场景与UI**：
   - 左侧是**像素树**：根节点1在顶部（红色，感染），子节点分层排列（绿色），叶子是浅绿色。
   - 右侧是**控制面板**：开始/暂停、单步、重置按钮，速度滑块（0.5x~2x）。
   - 底部是**数据面板**：显示当前节点的`size`和`dp`值。
   - 背景是淡蓝色，搭配红白机风格的像素边框。

2. **动画流程**：
   - **初始化**：树结构绘制完成，根节点1闪烁，播放8位风格的背景音乐（轻快的“叮叮咚”）。
   - **DFS遍历**：用黄色箭头从根节点1开始，递归遍历子节点。遍历到叶子节点时，叶子变亮，`size`变为1，`dp`变为0（播放“滴”声）。
   - **size计算**：回溯时，父节点的`size`加上子节点的`size`，数值闪烁（比如节点2的`size`从1变成3，播放“滴”声）。
   - **dp计算**：父节点的所有子节点遍历完成后，计算`dp`值。比如节点1有两个子节点，左子节点`size=3`、`dp=2`，右子节点`size=4`、`dp=3`，则`dp[1] = max(2+4-1, 3+3-1) = max(5,5)=5`。此时节点1变金色，播放“叮”声。
   - **胜利状态**：计算完`dp[1]`后，屏幕弹出“胜利！保存数：5”，播放8位风格的胜利音效（“叮当当”）。

3. **交互设计**：
   - **单步执行**：点击“单步”按钮，逐步展示DFS和`dp`计算过程，适合仔细观察每一步。
   - **自动播放**：点击“开始”按钮，动画自动运行，速度可通过滑块调节（比如0.5x是慢动作，2x是快进）。
   - **重置**：点击“重置”按钮，回到初始状态，重新开始动画。

### 为什么这样设计？
- **像素风格**：复古游戏的视觉效果能降低学习的“距离感”，让你更愿意主动探索。
- **音效提示**：关键操作（`size`更新、`dp`计算）用不同的音效强化记忆，比如“滴”对应`size`，“叮”对应`dp`。
- **交互控制**：单步和自动播放结合，既可以仔细研究细节，也能整体观察流程。


## 6. 拓展练习与相似问题思考

### 通用思路迁移
树形DP的核心是“**子问题的最优解汇总**”，能解决很多树结构的问题：
1. **树的最大独立集**：选择一些节点，使得没有两个节点相邻，求最大权值和。
2. **树的最长路径**（直径）：用树形DP计算每个节点的最长子路径，再求最大值。
3. **二叉树的最优保留问题**：比如保留k条边，最大化苹果数（洛谷P2015）。

### 洛谷练习推荐
1. **洛谷 P1352 - 没有上司的舞会**  
   🗣️ **推荐理由**：树形DP的经典入门题！状态定义是“选或不选当前节点”，转移逻辑和本题类似，能帮你巩固状态定义的思路。
2. **洛谷 P2015 - 二叉苹果树**  
   🗣️ **推荐理由**：二叉树的进阶树形DP！需要保留k条边，最大化苹果数，转移时要考虑子树的边数限制，是本题的“升级版本”。
3. **洛谷 P2279 - 消防局的设立**  
   🗣️ **推荐理由**：树形DP的拓展题！求最少需要设立多少消防局才能覆盖整棵树，状态定义需要考虑节点的覆盖范围，能帮你开拓思路。


## 7. 学习心得与经验分享

### 参考经验（来自冬天的雨）
> “多组数据所以每次需要将各种数组清零，清零`head`数组也相当于清零边，小小地卡一点常数。”  
> **点评**：多组数据的初始化是“隐形的坑”！比如本题中如果不清零`head`数组，邻接表会残留上一组的边，导致DFS遍历错误。冬天的雨的经验提醒我们，**再小的细节也不能忽略**。

### 参考经验（来自artalter）
> “我没有注意到是二叉树，试图寻找一个适用于多叉树的做法，惨遭爆零。”  
> **点评**：题目中的“二叉树”是关键限制！因为二叉树只有两个子节点，所以转移时只需要考虑两种选择。artalter的教训提醒我们，**读题要仔细，不要忽略关键条件**。


## 结语
《Infected Tree》是树形DP的“入门标杆题”，它的核心逻辑——**状态定义、自底向上计算、转移方程**——适用于大多数树结构问题。通过本指南的分析，希望你能掌握树形DP的“套路”，并通过像素动画直观理解算法的运行过程。

记住：树形DP的本质是“**给树的每个节点打分，然后汇总**”。多练习类似题目，你会发现树结构的问题其实“万变不离其宗”！💪

下次我们再一起探索更有趣的算法问题～

---
处理用时：230.26秒