# 题目信息

# [USACO09OCT] The Leisurely Stroll G

## 题目描述

Bessie looks out the barn door at the beautiful spring day and thinks to herself, 'I'd really like to enjoy my walk out to the pastures for the tender spring grass.' She knows that once she leaves the barn, she will traverse a path for a while, take one of two choices that lead to other paths, follow one of them, take one of two other choices, and continue on until the path leads to a verdant pasture.

She decides to make the set of path choices that enables her to walk over the greatest number of cow paths on her way to breakfast. Given the description of these paths, determine how many cow paths she traverses, presuming that she commences choosing various paths as soon as she leaves the barn.

The farm has P (1 <= P <= 1,000) pastures that are lead to by P-1 choice-nodes (range 1..P-1) connected by paths. From the barn (which is node 1), only one set of path traversals exists to reach any choice-node or pasture.

Consider this set of paths (lines), pastures ('%'), and the highlighted ('#') route to a pasture on the right:

```cpp

                 %                             %
                /                             /
      2----%   7----8----%          2----%   7####8----%
     / \      /      \             # #      #      #
    1   5----6        9----%      1   5####6        9----%
     \   \    \        \           \   \    \        #
      \   %    %        %           \   %    %        %
       \                             \
        3-----%                       3-----%
         \                             \
          4----%                        4----%
           \                             \
            %                             %
```
The pasture reached from choice-node 9 is one of two that enable Bessie to traverse seven different cowpaths on the way to breakfast. These are the 'furthest' pastures from node 1, the barn.

Three integers describe each node: Cn, D1, and D2. Cn is the

nodenumber (1 <= Cn <= P-1); D1 and D2 are the destinations from that node (0 <= D1 <= P-1; 0 <= D2 <= P-1). If D1 is 0, the node leads to a pasture in that direction; D2 has the same property.

POINTS: 100

Bessie透过牛棚的大门向外望去。发现今天是一个美丽的春季早晨。她想，“我真的好想好想沐浴着春风，走在草地之中，感受嫩草温柔地抚摸四蹄地的感觉。”她知道一旦她离开了牛棚，她将沿着一条小径走一段路，然后就会出现一个三岔路口，她必须在两条小径中选择一条继续走下去。然后她又会遇到更多的三岔路口，进行更多的选择，知道她到达一个青翠的牧场为止。

她决定作一个选择使得她在去吃早草的路途中可以走过最多的小径。给你这些小径的描述，求出Bessie最多可以走过多少条小径。假定Bessie一出牛棚就有2条路径，Bessie需要从中选择一条。

农场中有P-1 (1 <= P <= 1,000) 个分岔节点（范围是1..P），引向P片草地，它们之间由小径连接。对任意一个节点来说，只有一条从牛棚（被标记为节点1）开始的路径可以到达。

考虑下面的图。线段表示小径，"%"表示草地。右边的图中的"#"表示一条到达草地的高亮的路径。

从分岔节点9到达的草地是两个可以让Bessie走过最多小径的草地之一。在去吃早草的路上Bessie将走过7条不同的小径。这些草地是离牛棚也就是节点1最“远”的。

由3个整数来表示每一个节点：Cn, D1和D2，Cn是节点的编号(1 <= Cn <= P-1); D1和D2是由该节点引出的两条小径的终点(0 <= D1 <= P-1; 0 <= D2 <= P-1)。如果D1为0，表示这条小径引向的是一片牧草地；D2也一样。


## 说明/提示

This input describes the example farm layout in the task description.


1-2-5-6-7-8-9-P is one of the longest routes.


## 样例 #1

### 输入

```
10 
7 8 0 
5 0 6 
9 0 0 
6 0 7 
3 4 0 
2 5 0 
8 0 9 
4 0 0 
1 2 3 
```

### 输出

```
7 
```

# AI分析结果



### 综合分析与结论
本题本质是求二叉树的深度。各题解主要采用DFS/BFS/DP三种思路，其中递归计算子树高度的动态规划方法最优（O(n)）。关键点在于理解题目描述对应二叉树结构，以及最长路径即树高的转化。

---

### 精选题解与评分

#### 1. 作者：xwmwr（★★★★★）
**关键亮点**：将问题转化为树高计算，采用后序遍历动态规划思路。每个节点的高度由左右子树高度决定，时间复杂度O(n)。
```cpp
struct Node{ int lc, rc, height; };
void replace(int u) {
    if(u == 0) return;
    replace(node[u].lc);
    replace(node[u].rc);
    node[u].height = max(node[node[u].lc].height, 
                        node[node[u].rc].height) + 1;
}
// 调用后直接输出 node[1].height-1
```

#### 2. 作者：Alex_Wei（★★★★☆）
**关键亮点**：简洁DFS实现，直接维护当前深度。代码极简，适合新手理解DFS框架。
```cpp
void dfs(int m, int s) {
    if(a[m]) dfs(a[m], s+1);
    if(b[m]) dfs(b[m], s+1);
    n = max(n, s);
}
// 从dfs(1,1)开始，输出累计的n
```

#### 3. 作者：封禁用户（★★★★☆）
**亮点**：双解法对比，明确问题本质。DFS实现清晰，包含暴力到优化的思考过程。
```cpp
void dfs(int x, int res) {
    if(!x) { ans=max(ans,res); return; }
    dfs(g[x][0], res+1);
    dfs(g[x][1], res+1);
}
// 存储二叉树的左右子节点直接递归
```

---

### 关键思路总结
1. **树高即答案**：将牧场抽象为叶子节点，转化为二叉树深度问题。
2. **动态规划优化**：后序遍历计算子树高度，避免重复计算。
3. **递归终止条件**：遇到0值（牧场）时更新最大深度。

---

### 同类题目推荐
1. [P1047 二叉树的最大深度](https://www.luogu.com.cn/problem/P1047)（基础树深）
2. [P1053 二叉树的直径](https://www.luogu.com.cn/problem/P1053)（树形DP扩展）
3. [P1359 二叉苹果树](https://www.luogu.com.cn/problem/P1359)（带权树路径问题）

---

### 调试心得摘录
- **zy小可爱**："数路径长度后发现直接当1处理即可" → 抓住问题本质简化模型。
- **荷叶下**："每个点都BFS一遍" → 指出错误优化方向，提醒合理选择遍历起点。
- **xwmwr**：通过树高公式推导，将复杂路径问题转化为清晰数学关系。

---
处理用时：40.91秒