# 题目信息

# Not Assigning

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ , with edges numbered from $ 1 $ to $ n-1 $ . A tree is a connected undirected graph without cycles. You have to assign integer weights to each edge of the tree, such that the resultant graph is a prime tree.

A prime tree is a tree where the weight of every path consisting of one or two edges is prime. A path should not visit any vertex twice. The weight of a path is the sum of edge weights on that path.

Consider the graph below. It is a prime tree as the weight of every path of two or less edges is prime. For example, the following path of two edges: $ 2 \to 1 \to 3 $ has a weight of $ 11 + 2 = 13 $ , which is prime. Similarly, the path of one edge: $ 4 \to 3 $ has a weight of $ 5 $ , which is also prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/3add991eaafca4c0491e3513c8ebd38f1627bca9.png)Print any valid assignment of weights such that the resultant tree is a prime tree. If there is no such assignment, then print $ -1 $ . It can be proven that if a valid assignment exists, one exists with weights between $ 1 $ and $ 10^5 $ as well.

## 说明/提示

For the first test case, there are only two paths having one edge each: $ 1 \to 2 $ and $ 2 \to 1 $ , both having a weight of $ 17 $ , which is prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/22666e3c2f70cbd5edc23fd608081fffda0715fc.png)The second test case is described in the statement.

It can be proven that no such assignment exists for the third test case.

## 样例 #1

### 输入

```
3
2
1 2
4
1 3
4 3
2 1
7
1 2
1 3
3 4
3 5
6 2
7 2```

### 输出

```
17
2 5 11
-1```

# AI分析结果

# 💡 Kay的C++算法解析：Not Assigning 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：构造算法、树的性质分析（链结构判断）

🗣️ **初步分析**：  
解决“Not Assigning”问题的关键，在于**通过数论性质约束树的结构**，并**构造合法的边权分配**。简单来说，题目要求所有长度为1（单条边）或2（两条相邻边）的路径和为质数。根据数论知识：  
- 单条边的权值必须是质数（因为长度为1的路径和就是边权本身）。  
- 两条相邻边的权值和必须是质数。由于**奇质数+奇质数=偶数（非2，即合数）**，因此相邻边中必有一条是**偶质数2**，另一条是**奇质数**（如3、5等）。  

**核心结论**：若树中存在节点度数≥3，则无法满足条件（因为该节点的三条边中，必有两条奇质数，其和为合数）。因此，**树必须是链结构（每个节点度数≤2）**，否则输出-1。  

对于链结构，**交替分配2和3**即可满足条件（2+3=5，是质数；3+2=5，同样满足）。  

**可视化设计思路**：  
- 用**8位像素风格**展示树的结构（节点为方块，边为线条）。  
- 度数≥3的节点用**红色闪烁**标记（表示无解）。  
- 链的遍历过程用**蓝色箭头**动画展示（从度数为1的端点开始）。  
- 边权分配时，2用**绿色方块**、3用**黄色方块**表示，相邻边颜色交替，伴随“叮”的音效（每分配一个边权）。  


## 2. 精选优质题解参考

为了帮助大家快速掌握解题思路，我筛选了3份**思路清晰、代码规范**的优质题解：

**题解一（来源：wosile）**  
* **点评**：这份题解的**思路逻辑性极强**，先通过数论证明“树必须是链”（若有节点度数≥3则无解），再给出链的构造方法（交替分配2和3）。代码结构规范，用`vector`存储树的邻接表，`dfs`函数从链的端点开始遍历，交替赋值（`col+2`实现2和3的切换）。变量命名（如`d`表示度数、`ans`存储边权）清晰易懂，边界条件（如判断链的端点）处理严谨，非常适合初学者参考。  

**题解二（来源：LRL65）**  
* **点评**：此题解的**代码简洁性**是亮点。用`vector<pair<int,int>>`存储边的信息（目标节点和边编号），`dfs`函数从节点1开始遍历，通过`5-la`（`la`为前一个边权）实现2和3的交替（5-2=3，5-3=2）。虽然遍历起点未严格选择链的端点，但代码逻辑依然正确，适合学习“如何用简单逻辑实现交替赋值”。  

**题解三（来源：2021hych）**  
* **点评**：这份题解的**细节处理**值得学习。用`map`记录边的位置（避免重复存储），遍历链时通过`flag`数组标记已访问节点，确保从端点开始遍历。边权分配用`cnt&1`（奇偶判断）实现2和3的交替，逻辑直观。代码中的`memset`和`clear`操作（处理多组测试用例）非常规范，适合学习“如何处理多组数据”。  


## 3. 核心难点辨析与解题策略

在解决本题时，以下3个难点需要重点突破：

### 1. **难点1：判断树是否为链**  
- **问题**：如何快速判断树是否为链（每个节点度数≤2）？  
- **策略**：统计每个节点的度数（`deg`数组），若存在`deg[i]≥3`，则直接输出-1。  
- 💡 **学习笔记**：度数统计是树结构分析的基础，也是判断链的关键。  

### 2. **难点2：构造合法的边权分配**  
- **问题**：如何分配边权，使得相邻边和为质数？  
- **策略**：交替分配2和3（或其他奇质数，如2和5）。因为2是唯一的偶质数，奇质数+2=奇质数（如3+2=5），满足条件。  
- 💡 **学习笔记**：利用数论性质（偶质数+奇质数=奇质数）是构造的核心。  

### 3. **难点3：遍历链并分配边权**  
- **问题**：如何遍历链（避免循环），并给每条边赋值？  
- **策略**：找到链的端点（度数为1的节点），用`dfs`或`bfs`遍历链，记录前一个边的权值，交替赋值。  
- 💡 **学习笔记**：链的端点是遍历的起点，避免循环的关键是标记已访问节点。  


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：本代码综合了wosile和LRL65的题解思路，是链结构判断与边权分配的典型实现。  
* **完整核心代码**：  
```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;
int deg[MAXN], ans[MAXN];
vector<pair<int, int>> G[MAXN]; // 邻接表：(目标节点, 边编号)

void dfs(int u, int fa, int val) {
    for (auto &edge : G[u]) {
        int v = edge.first, id = edge.second;
        if (v == fa) continue;
        ans[id] = val; // 分配当前边权
        dfs(v, u, 5 - val); // 交替赋值（5-2=3，5-3=2）
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
        // 初始化
        for (int i = 1; i <= n; i++) {
            deg[i] = 0;
            G[i].clear();
        }
        // 读入边
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v, i);
            G[v].emplace_back(u, i);
            deg[u]++;
            deg[v]++;
        }
        // 判断是否为链
        bool is_chain = true;
        for (int i = 1; i <= n; i++) {
            if (deg[i] >= 3) {
                is_chain = false;
                break;
            }
        }
        if (!is_chain) {
            cout << "-1\n";
            continue;
        }
        // 找到链的端点（度数为1的节点）
        int start = 1;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 1) {
                start = i;
                break;
            }
        }
        // 分配边权（从2开始）
        dfs(start, 0, 2);
        // 输出结果
        for (int i = 1; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
```  
* **代码解读概要**：  
  1. **输入处理**：读取多组测试用例，用邻接表存储树的结构，统计每个节点的度数。  
  2. **链判断**：若存在节点度数≥3，输出-1。  
  3. **端点查找**：找到度数为1的节点（链的端点）。  
  4. **边权分配**：用`dfs`遍历链，从端点开始交替分配2和3（`5-val`实现交替）。  


### 针对各优质题解的片段赏析  

**题解一（来源：wosile）**  
* **亮点**：用`col^1`（异或）实现交替赋值，逻辑简洁。  
* **核心代码片段**：  
```cpp
void dfs(int rt, int fa, int col) {
    for (int i = 0; i < T[rt].size(); i++) {
        if (T[rt][i].first != fa) {
            ans[T[rt][i].second] = col + 2; // col=0→2，col=1→3
            dfs(T[rt][i].first, rt, col ^ 1); // 异或切换col
        }
    }
}
```  
* **代码解读**：  
  - `col`表示当前边的“颜色”（0或1），`col+2`将0转换为2，1转换为3。  
  - `col^1`（异或1）实现0和1的切换，从而交替分配2和3。  
* 💡 **学习笔记**：异或是实现交替逻辑的常用技巧，代码更简洁。  

**题解二（来源：LRL65）**  
* **亮点**：用`5-la`实现交替赋值，无需额外变量。  
* **核心代码片段**：  
```cpp
void dfs(int x, int fa, int la) {
    for (int i = 0; i < e[x].size(); i++) {
        if (e[x][i].first == fa) continue;
        ans[e[x][i].second] = 5 - la; // la=2→3，la=3→2
        dfs(e[x][i].first, x, 5 - la);
    }
}
```  
* **代码解读**：  
  - `la`表示前一个边的权值（2或3），`5-la`计算当前边的权值（5-2=3，5-3=2）。  
  - 无需额外变量记录“颜色”，直接通过前一个边权计算当前边权。  
* 💡 **学习笔记**：利用数学运算简化逻辑，是代码优化的常用方法。  


## 5. 算法可视化：像素动画演示 (核心部分)

### 动画演示主题  
**《像素链探险》**（仿FC红白机风格）：玩家操控“像素探险家”遍历树，判断是否为链，并分配边权。  

### 核心演示内容  
1. **场景初始化**：  
   - 屏幕左侧显示**树的像素结构**（节点为16x16的方块，边为8x8的线条）。  
   - 屏幕右侧显示**控制面板**（开始/暂停、单步执行、重置按钮；速度滑块）。  
   - 背景音乐：8位风格的轻快旋律（如《超级马里奥》的背景音）。  

2. **链判断过程**：  
   - 节点度数≥3时，**红色闪烁**（伴随“警告”音效：短促的“滴滴”声）。  
   - 若所有节点度数≤2，**绿色提示**（“链结构有效！”）。  

3. **边权分配过程**：  
   - 探险家从**度数为1的端点**（蓝色闪烁）出发，沿链移动（动画：方块滑动）。  
   - 每走一步，当前边显示**绿色方块（2）**或**黄色方块（3）**，伴随“叮”的音效。  
   - 相邻边颜色交替，显示“2+3=5（质数）”的文字提示（如“当前边和：5，质数！”）。  

4. **目标达成**：  
   - 遍历完所有边后，**屏幕中央显示“任务完成！”**（红色像素字），伴随“胜利”音效（上扬的“叮~”声）。  

### 交互设计  
- **单步执行**：点击“下一步”按钮，探险家移动一步，分配一个边权。  
- **自动播放**：拖动速度滑块（1x~5x），探险家自动遍历链，边权分配动画加速。  
- **重置**：点击“重置”按钮，回到初始状态，重新开始。  

### 设计思路  
- **像素风格**：营造复古游戏氛围，降低学习压力。  
- **音效提示**：用声音强化关键操作（如分配边权、警告），帮助记忆。  
- **动画交互**：通过“探险家移动”模拟链的遍历，让算法过程更直观。  


## 6. 拓展练习与相似问题思考

### 通用思路/技巧迁移  
- **构造算法**：本题的核心是“通过约束条件构造解”，类似问题包括：  
  1. 给图的边分配权值，使得路径和满足某种条件（如质数、偶数）。  
  2. 构造一棵树，满足某些节点的度数约束（如每个节点度数≤k）。  
- **树的性质**：链是树的特殊结构，类似问题包括：  
  1. 判断树是否为平衡树（如AVL树）。  
  2. 求树的直径（最长链）。  

### 练习推荐 (洛谷)  
1. **洛谷 P1280 《尼克的任务》**  
   - 🗣️ **推荐理由**：这道题是构造题，要求安排任务的时间，使得总收益最大。需要通过约束条件（任务时间不重叠）构造解，类似本题的“边权分配约束”。  
2. **洛谷 P2661 《信息传递》**  
   - 🗣️ **推荐理由**：这道题考察树的遍历（寻找最小环），需要处理节点的度数和邻接关系，类似本题的“链判断”。  
3. **洛谷 P3371 《单源最短路径》**  
   - 🗣️ **推荐理由**：这道题考察树的遍历（Dijkstra算法），需要从端点开始遍历，类似本题的“链遍历”。  


## 7. 学习心得与经验分享 (若有)  
**参考经验 (来自 wosile)**：“我在解决这个问题时，最初没有想到‘树必须是链’，后来通过数论分析（奇质数+奇质数=合数）才意识到这一点。这让我意识到，**数论性质是构造题的关键**，必须先分析约束条件，再设计算法。”  
**点评**：这位作者的经验很典型。构造题往往需要先通过数学分析缩小解的范围（如本题的“链结构”），再寻找构造方法。**先分析、后构造**是解决构造题的核心思路。  


## 结语  
本次关于“Not Assigning”的C++解题分析就到这里。希望这份指南能帮助大家理解**构造算法**和**树的性质**，掌握“先分析约束条件、再设计解”的解题思路。记住，编程的乐趣在于“用逻辑解决问题”，只要多思考、多练习，你一定能攻克更多难题！💪  

---  
**Kay的小提示**：下次遇到构造题时，不妨先问自己：“问题有哪些约束条件？这些条件能缩小解的范围吗？” 相信你会有新的启发！😊

---
处理用时：197.96秒