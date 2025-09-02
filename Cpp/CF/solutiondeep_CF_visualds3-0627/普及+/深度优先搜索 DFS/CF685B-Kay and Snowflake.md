# 题目信息

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5
```

### 输出

```
3
2
3
6
```

# AI分析结果



## 算法分类：DFS

### 综合分析与结论

**题目核心**：寻找树中每个子树的重心。重心定义为删除该节点后最大连通块大小不超过原子树大小的一半。

**核心难点**：暴力遍历所有子树会导致 O(nq) 复杂度，需利用树的重心性质进行优化。关键性质是：子树的重心一定在根节点的重儿子子树的重心路径上，或根节点本身。

**解决方案**：通过一次 DFS 预处理每个节点的子树大小和重儿子，回溯时从重儿子的重心开始向上跳，找到满足条件的节点。时间复杂度 O(n)。

**可视化设计思路**：
1. **动画流程**：展示 DFS 遍历树的过程，计算每个节点的子树大小和重儿子。回溯时，从子节点的重心向上跳，颜色标记当前节点和调整路径。
2. **颜色标记**：当前处理节点用红色，已确定重心用绿色，重链用蓝色。
3. **步进控制**：可暂停/继续，观察每个节点的 size 计算和重心调整步骤。
4. **复古风格**：8位像素风格绘制树结构，访问节点时播放音效，找到重心时播放胜利音效。

### 题解评分（≥4星）

1. **mrsrz（★★★★★）**
   - **亮点**：线性时间复杂度，代码简洁，清晰展示重心向上跳的优化。
   - **核心代码**：
     ```cpp
     void dfs(int now) {
         // 预处理子树大小和重儿子
         for (子节点) dfs(子节点);
         // 从子节点的重心向上跳
         int id = now;
         for (每个子节点) {
             int it = 子节点的重心;
             while (父节点不是当前节点) {
                 if (更优则更新，否则跳出循环
             }
         }
     }
     ```

2. **Ryan_（★★★★☆）**
   - **亮点**：明确利用重儿子性质，代码可读性高。
   - **核心代码**：
     ```cpp
     void dfs(int x) {
         // 预处理重儿子
         if (重儿子存在) {
             int now = 重儿子的重心;
             while (向上跳更优) now = 父节点;
             ans[x] = now;
         }
     }
     ```

3. **chihik（★★★★☆）**
   - **亮点**：结合重链剖分，二分查找重心，适用于大数据场景。
   - **核心代码**：
     ```cpp
     int Query(int rt) {
         int u = rt;
         // 在重链上二分
         while (满足条件) u = 父节点;
         return u;
     }
     ```

### 最优思路提炼

1. **DFS预处理**：计算每个节点的子树大小 `size` 和重儿子 `son`。
2. **重心性质**：重心在重链上，且向上调整时只需检查父节点是否更优。
3. **向上跳跃**：从子节点的重心开始，向上跳至第一个满足条件的节点，避免重复计算。

### 同类型题与算法套路

- **通用模式**：预处理子树信息（如大小、深度、重儿子）后，利用性质快速求解。
- **类似问题**：树的直径、最近公共祖先（LCA）、子树统计问题。

### 推荐题目

1. **P1395 会议**（树的重心基础）
2. **P3384 树链剖分**（重链应用）
3. **P2633 Count on a tree**（子树查询与路径处理）

### 个人心得摘录

- **调试教训**：初始暴力 DFS 超时，必须利用重心性质优化。
- **顿悟点**：重心在重链上跳跃时，一旦不优即可终止循环，保证线性复杂度。

### 可视化代码片段（JS Canvas）

```javascript
// 绘制树结构（复古像素风格）
function drawTree() {
    ctx.fillStyle = '#8B8B83'; // 灰色节点
    nodes.forEach(node => {
        ctx.fillRect(node.x * 30, node.y * 30, 20, 20);
    });
    // 高亮当前处理节点
    ctx.fillStyle = '#FF0000';
    ctx.fillRect(currentNode.x * 30, currentNode.y * 30, 20, 20);
}

// 播放音效（8位风格）
function playSound(type) {
    if (type === 'visit') beep(440, 50); // 访问音效
    if (type === 'found') beep(880, 100); // 找到重心
}
```

### 可视化演示步骤

1. **DFS遍历**：逐步显示每个节点的 `size` 计算，重儿子标记为蓝色。
2. **重心调整**：从子节点重心（绿色）向上跳至当前节点（红色），路径用黄色高亮。
3. **完成标记**：确定重心后，节点变为绿色并播放音效。

通过交互式演示，用户可直观理解重心的查找过程和优化策略。

---
处理用时：73.89秒