# 题目信息

# Berland SU Computer Network

## 题目描述

In the computer network of the Berland State University there are $ n $ routers numbered from $ 1 $ to $ n $ . Some pairs of routers are connected by patch cords. Information can be transmitted over patch cords in both direction. The network is arranged in such a way that communication between any two routers (directly or through other routers) is possible. There are no cycles in the network, so there is only one path between each pair of routers over patch cords.

Unfortunately, the exact topology of the network was lost by administrators. In order to restore it, the following auxiliary information was collected.

For each patch cord $ p $ , directly connected to the router $ i $ , list of routers located behind the patch cord $ p $ relatively $ i $ is known. In other words, all routers path from which to the router $ i $ goes through $ p $ are known. So for each router $ i $ there are $ k_{i} $ lists, where $ k_{i} $ is the number of patch cords connected to $ i $ .

For example, let the network consists of three routers connected in chain $ 1-2-3 $ . Then:

- the router $ 1 $ : for the single patch cord connected to the first router there is a single list containing two routers: $ 2 $ and $ 3 $ ;
- the router $ 2 $ : for each of the patch cords connected to the second router there is a list: one list contains the router $ 1 $ and the other — the router $ 3 $ ;
- the router $ 3 $ : for the single patch cord connected to the third router there is a single list containing two routers: $ 1 $ and $ 2 $ .

Your task is to help administrators to restore the network topology, i. e. to identify all pairs of routers directly connected by a patch cord.

## 说明/提示

The first example is analyzed in the statement.

The answer to the second example is shown on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847L/e101c14c7ca1e10d8c7b2619158ff5db62d03be1.png)The first router has one list, which contains all other routers. The second router has three lists: the first — the single router $ 4 $ , the second — the single router $ 1 $ , the third — two routers $ 3 $ and $ 5 $ . The third router has one list, which contains all other routers. The fourth router also has one list, which contains all other routers. The fifth router has two lists: the first — the single router $ 3 $ , the second — three routers $ 1 $ , $ 2 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
2:3,2
1:1-1:3
2:1,2
```

### 输出

```
2
2 1
2 3
```

## 样例 #2

### 输入

```
5
4:2,5,3,4
1:4-1:1-2:5,3
4:4,5,2,1
4:2,1,3,5
1:3-3:4,2,1
```

### 输出

```
4
2 1
2 4
5 2
3 5
```

## 样例 #3

### 输入

```
3
1:2-1:3
1:1-1:3
1:1-1:2
```

### 输出

```
-1
```

# AI分析结果


### 💡 Kay的C++算法解析：Berland SU Computer Network 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`树结构重建`（拓扑排序应用）

🗣️ **初步分析**：
> 本题如同在玩"像素拼图游戏"——已知每个路由器连接的"碎片区域"（子树节点列表），需拼出完整的树形网络。核心是**拓扑排序**思想：从叶子节点（度数为1）开始逐步剥离，如同消除类游戏中消除边缘方块。  
> - **题解对比**：  
>   - *解法1*：利用数学性质（边两端子树大小和=n）直接找边，再验证树结构  
>   - *解法2*：模拟拓扑排序，从叶子节点逐步删除并记录边  
> - **可视化设计**：  
>   - 用8位像素方块表示路由器，绿色为待处理节点，红色闪烁表示当前处理的叶子节点  
>   - 连线动画伴随"叮"音效，删除节点时播放方块消除音效  
>   - 控制面板含速度滑块和"AI自动演示"（如贪吃蛇自动消除叶子）

---

#### 2. 精选优质题解参考
**题解一（极寒神冰）**  
* **点评**：  
  思路创新性强，利用数学性质`cnt[u][v]+cnt[v][u]==n`直接确定边（如同拼图时寻找完美匹配的碎片）。代码采用DFS验证三要素：边数校验、连通性检查、子树列表比对。亮点在于用`vector<vector<int>>`存储子树并排序比对，虽可能达O(n³)但n≤1000可接受。实践时需注意输入处理复杂度。

**题解二（xzggzh1）**  
* **点评**：  
  采用拓扑排序逐步构建树（类似"层层剥洋葱"），从叶子节点入队开始，动态更新邻居的子树列表。代码亮点在于用`sz[i][in[x][i]]`跟踪子树大小变化，验证时检查路径一致性。更易理解但实现稍复杂，队列操作和DFS验证展现完整解题逻辑。

---

#### 3. 核心难点辨析与解题策略
1. **难点1：从子树列表确定边**  
   * **分析**：每个节点的列表描述删除某边后的子树，但未直接给出邻居信息。解法1用数学性质直接映射，解法2通过叶子节点反向推导。
   * 💡 **学习笔记**：树中边(u,v)满足|u的v所在子树|+|v的u所在子树|=n

2. **难点2：验证树的正确性**  
   * **分析**：必须检查三点：边数=n-1、整树连通、每个节点的子树列表匹配输入。解法1重建子树比对，解法2用DFS检查路径一致性。
   * 💡 **学习笔记**：验证是构造题的保险锁

3. **难点3：处理复杂输入格式**  
   * **分析**：输入含`:`、`,`、`-`分隔符，需逐字符解析。题解均用`scanf`配合循环处理，注意边界条件。
   * 💡 **学习笔记**：解析输入时优先处理分隔符再读数据

---

#### 4. C++核心代码实现赏析
**通用核心实现参考**  
```cpp
#include <vector>
#include <algorithm>
using namespace std;

// 核心结构：用邻接表存树
vector<vector<int>> tree;
vector<pair<int, int>> edges;

// 关键验证函数
bool validateTree(int n) {
    if (edges.size() != n-1) return false;
    // 添加DFS连通性检查
    // 重建每个节点的子树列表并比对输入
    return true;
}
```

**题解一核心片段**  
```cpp
// 数学性质找边
for (int u=1; u<=n; u++) 
    for (int v=u+1; v<=n; v++)
        if (cnt[u][v] + cnt[v][u] == n) 
            edges.push_back({u, v});

// 验证子树列表
vector<vector<int>> rebuildLists(int node) {
    vector<vector<int>> res;
    for (int neighbor : tree[node]) {
        vector<int> subtree;
        dfs(neighbor, node, subtree); // DFS遍历子树
        sort(subtree.begin(), subtree.end());
        res.push_back(subtree);
    }
    sort(res.begin(), res.end());
    return res;
}
```
* **解读**：  
  > 如同玩数独时寻找唯一解，`cnt[u][v]+cnt[v][u]==n`确保(u,v)是合法边。`rebuildLists`像"拼图比对器"——重建实际子树与输入比对，sort使比较标准化。

**题解二核心片段**  
```cpp
// 拓扑排序核心
queue<int> leaves;
for (int i=1; i<=n; i++)
    if (degree[i] == 1) leaves.push(i);

while (!leaves.empty()) {
    int leaf = leaves.front();
    leaves.pop();
    int parent = findParent(leaf); // 在邻居中找唯一有效父节点
    edges.push_back({leaf, parent});
    updateSubtreeInfo(parent, leaf); // 删除leaf并更新parent
    if (--degree[parent] == 1) 
        leaves.push(parent);
}
```
* **解读**：  
  > 类似"俄罗斯方块消除"——叶子节点入队时如同方块悬空，`findParent`找落地位置，`updateSubtreeInfo`像消除后刷新界面。队列操作保证按层处理。

---

#### 5. 算法可视化：像素动画演示
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847L/e101c14c7ca1e10d8c7b2619158ff5db62d03be1.png)  
* **主题**：`路由器消除大作战`（FC红白机风格）  
* **核心流程**：  
  1. **初始化**：像素方块路由器排列，叶子节点闪烁红光  
  2. **消除动画**：  
     - 叶子节点闪烁后"吸入"父节点，伴随8-bit音效  
     - 连线显示为黄色像素轨迹  
     - 父节点度数-1显示在头顶  
  3. **AI演示模式**：  
     - 自动按拓扑序消除节点，速度可调  
     - 每连一条边得分+10，连击额外+50  
  4. **验证阶段**：  
     - 成功重建树时所有节点变绿，播放胜利音效  
     - 失败则问题节点闪烁红光  

---

#### 6. 拓展练习与相似问题
1. **洛谷P1359** 租用游艇  
   → 练习拓扑排序在DAG的应用  
2. **洛谷P3884** [JLOI2009]二叉树问题  
   → 强化树结构重建技巧  
3. **洛谷P1038** 神经网络  
   → 学习拓扑排序的动态更新  

---

#### 7. 学习心得与经验分享
> **极寒神冰的调试经验**：  
> *"验证子树列表时忘记排序导致WA，必须保证数据标准化"*  
> **Kay总结**：比较复杂数据结构前务必排序或哈希标准化，这是避免隐蔽错误的金科玉律。

---

通过本次分析，我们掌握了树重建的核心技巧：活用数学性质或拓扑过程逐步推导，最后严谨验证。记住，好的算法如同拼图——找到关键连接点，一切将迎刃而解！🚀

---
处理用时：131.81秒