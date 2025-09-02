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

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
本题的核心是求从根节点出发到最远叶子节点的路径长度，本质上是一个树的深度问题。大多数题解都采用了DFS或BFS来遍历树结构，计算最大深度。DFS是更常见的解法，因为它天然适合树的递归结构，且代码简洁。BFS虽然也能解决问题，但代码相对复杂，且没有明显的性能优势。

### 所选题解
#### 1. 作者：Alex_Wei (赞：36)
- **星级**: 5星
- **关键亮点**: 代码简洁，思路清晰，直接使用DFS遍历树结构，更新最大深度。
- **核心代码**:
  ```cpp
  void dfs(int m, int s) {
      if(a[m] != 0) dfs(a[m], s + 1);
      if(b[m] != 0) dfs(b[m], s + 1);
      n = max(n, s);
  }
  ```
  **实现思想**: 递归遍历每个节点，更新当前路径长度，最终得到最大深度。

#### 2. 作者：xwmwr (赞：2)
- **星级**: 4星
- **关键亮点**: 将问题转化为求树高，使用递归计算每个子树的高度，思路清晰。
- **核心代码**:
  ```cpp
  void replace(int u) {
      if(u == 0) return;
      replace(node[u].lc);
      replace(node[u].rc);
      node[u].height = max(node[node[u].lc].height, node[node[u].rc].height) + 1;
  }
  ```
  **实现思想**: 通过递归计算每个节点的子树高度，最终得到树高。

#### 3. 作者：chlchl (赞：2)
- **星级**: 4星
- **关键亮点**: 使用DFS遍历树结构，避免走回头路，代码简洁且高效。
- **核心代码**:
  ```cpp
  void dfs(int res, int father, int dep) {
      ans = max(ans, dep);
      for(int i = 0; i < tree[res].size(); i++) {
          int v = tree[res][i];
          if(v == father) continue;
          dfs(v, res, dep + 1);
      }
  }
  ```
  **实现思想**: 通过DFS遍历树结构，避免重复访问父节点，更新最大深度。

### 最优关键思路或技巧
1. **DFS递归遍历**: 通过递归遍历树的每个节点，计算从根节点到叶子节点的路径长度，最终得到最大深度。
2. **避免重复访问**: 在DFS遍历时，通过记录父节点来避免走回头路，提高效率。
3. **树高计算**: 将问题转化为求树高，通过递归计算每个子树的高度，最终得到树高。

### 可拓展之处
1. **树的直径问题**: 类似的问题可以扩展到求树的直径，即树中任意两个节点之间的最长路径。
2. **加权树**: 如果树的边有权重，可以扩展到求加权树的最长路径。

### 推荐题目
1. [P1351 树的直径](https://www.luogu.com.cn/problem/P1351)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

### 个人心得摘录
- **Alex_Wei**: "DFS新手友好，直接递归遍历即可。"
- **xwmwr**: "将问题转化为求树高，思路清晰且易于实现。"
- **chlchl**: "通过记录父节点避免重复访问，代码简洁且高效。"

---
处理用时：27.39秒