# 题目信息

# Hamiltonian Wall

## 题目描述

Sir Monocarp Hamilton is planning to paint his wall. The wall can be represented as a grid, consisting of $ 2 $ rows and $ m $ columns. Initially, the wall is completely white.

Monocarp wants to paint a black picture on the wall. In particular, he wants cell $ (i, j) $ (the $ j $ -th cell in the $ i $ -th row) to be colored black, if $ c_{i, j} = $ 'B', and to be left white, if $ c_{i, j} = $ 'W'. Additionally, he wants each column to have at least one black cell, so, for each $ j $ , the following constraint is satisfied: $ c_{1, j} $ , $ c_{2, j} $ or both of them will be equal to 'B'.

In order for the picture to turn out smooth, Monocarp wants to place down a paint brush in some cell $ (x_1, y_1) $ and move it along the path $ (x_1, y_1), (x_2, y_2), \dots, (x_k, y_k) $ so that:

- for each $ i $ , $ (x_i, y_i) $ and $ (x_{i+1}, y_{i+1}) $ share a common side;
- all black cells appear in the path exactly once;
- white cells don't appear in the path.

Determine if Monocarp can paint the wall.

## 说明/提示

In the first testcase, Monocarp can follow a path $ (2, 1) $ , $ (2, 2) $ , $ (1, 2) $ , $ (1, 3) $ with his brush. All black cells appear in the path exactly once, no white cells appear in the path.

In the second testcase, Monocarp can follow a path $ (1, 1) $ , $ (2, 1) $ .

In the third testcase:

- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ doesn't suffice because a pair of cells $ (1, 3) $ and $ (2, 4) $ doesn't share a common side;
- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ doesn't suffice because cell $ (2, 3) $ is visited twice;
- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ doesn't suffice because a black cell $ (1, 3) $ doesn't appear in the path;
- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ , $ (1, 4) $ , $ (1, 3) $ doesn't suffice because a white cell $ (1, 4) $ appears in the path.

## 样例 #1

### 输入

```
6
3
WBB
BBW
1
B
B
5
BWBWB
BBBBB
2
BW
WB
5
BBBBW
BWBBB
6
BWBBWB
BBBBBB```

### 输出

```
YES
YES
NO
NO
NO
YES```

# AI分析结果

### 题目内容中文重写
# 哈密顿墙

## 题目描述

Sir Monocarp Hamilton 计划粉刷他的墙。墙可以表示为一个由 $2$ 行和 $m$ 列组成的网格。最初，墙是完全白色的。

Monocarp 想在墙上画一幅黑色的图案。具体来说，如果 $c_{i, j} = $ 'B'，他希望单元格 $ (i, j) $（第 $i$ 行的第 $j$ 个单元格）被涂成黑色；如果 $c_{i, j} = $ 'W'，则保持白色。此外，他希望每一列至少有一个黑色单元格，因此对于每个 $j$，以下约束条件成立：$c_{1, j}$、$c_{2, j}$ 或两者都等于 'B'。

为了使图案看起来平滑，Monocarp 希望将画笔放在某个单元格 $ (x_1, y_1) $ 上，并沿着路径 $ (x_1, y_1), (x_2, y_2), \dots, (x_k, y_k) $ 移动，使得：

- 对于每个 $i$，$ (x_i, y_i) $ 和 $ (x_{i+1}, y_{i+1}) $ 共享一个共同的边；
- 所有黑色单元格在路径中恰好出现一次；
- 白色单元格不出现在路径中。

判断 Monocarp 是否可以成功粉刷这面墙。

## 说明/提示

在第一个测试用例中，Monocarp 可以沿着路径 $ (2, 1) $ , $ (2, 2) $ , $ (1, 2) $ , $ (1, 3) $ 移动画笔。所有黑色单元格在路径中恰好出现一次，没有白色单元格出现在路径中。

在第二个测试用例中，Monocarp 可以沿着路径 $ (1, 1) $ , $ (2, 1) $ 移动。

在第三个测试用例中：

- 路径 $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ 不满足条件，因为单元格 $ (1, 3) $ 和 $ (2, 4) $ 不共享共同的边；
- 路径 $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ 不满足条件，因为单元格 $ (2, 3) $ 被访问了两次；
- 路径 $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ 不满足条件，因为黑色单元格 $ (1, 3) $ 没有出现在路径中；
- 路径 $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ , $ (1, 4) $ , $ (1, 3) $ 不满足条件，因为白色单元格 $ (1, 4) $ 出现在路径中。

## 样例 #1

### 输入

```
6
3
WBB
BBW
1
B
B
5
BWBWB
BBBBB
2
BW
WB
5
BBBBW
BWBBB
6
BWBBWB
BBBBBB```

### 输出

```
YES
YES
NO
NO
NO
YES```

### 算法分类
深度优先搜索 (DFS)

### 题解分析与结论
题目要求判断是否能够通过一笔画的方式覆盖所有黑色单元格，且路径中不包含白色单元格。由于墙只有两行，因此可以通过深度优先搜索 (DFS) 或广度优先搜索 (BFS) 来模拟画笔的移动路径。关键在于如何确保路径的连通性和唯一性。

### 所选高星题解
1. **作者：_dijkstra_ (赞：11)**  
   - **星级：4.5**  
   - **关键亮点**：通过简单的模拟和状态转移，分别尝试从第一列的两个单元格出发，检查是否能够覆盖所有黑色单元格。代码简洁，思路清晰。  
   - **核心代码**：
     ```cpp
     bool chk0() {
         bool now = 0;
         if (s[1][0] == 'B') now = 1;
         for (int i = 1; i < n; i++) {
             if (s[now][i] == 'W') return false;
             if (s[!now][i] == 'B') now = !now;
         }
         return true;
     }
     ```
   - **个人心得**：通过简单的状态转移，避免了复杂的DFS或BFS实现，代码效率较高。

2. **作者：Ryouko_miku (赞：1)**  
   - **星级：4**  
   - **关键亮点**：使用DFS从两个可能的起点出发，分别检查是否能够覆盖所有黑色单元格。思路清晰，代码可读性强。  
   - **核心代码**：
     ```cpp
     bool dfs(int x, int y, int cnt) {
         vis[x][y] = 1;
         bool tag = false;
         if (!cnt) return true;
         if (x + 1 <= 2 && m[x + 1][y] == 'B' && !vis[x + 1][y]) {
             tag = dfs(x + 1, y, cnt - 1);
         }
         else if (x - 1 >= 1 && m[x - 1][y] == 'B' && !vis[x - 1][y]) {
             tag = dfs(x - 1, y, cnt - 1);
         }
         else if (y + 1 <= n && m[x][y + 1] == 'B' && !vis[x][y + 1]) {
             tag = dfs(x, y + 1, cnt - 1);
         }
         else if (y - 1 >= 1 && m[x][y - 1] == 'B' && !vis[x][y - 1]) {
             tag = dfs(x, y - 1, cnt - 1);
         }
         return tag;
     }
     ```
   - **个人心得**：通过DFS的递归实现，清晰地模拟了画笔的移动路径，代码逻辑清晰。

### 最优关键思路
通过从两个可能的起点出发，分别尝试覆盖所有黑色单元格，确保路径的连通性和唯一性。使用简单的状态转移或DFS实现，避免了复杂的算法设计。

### 拓展思路
类似的问题可以扩展到更多行或列的网格，或者考虑路径中的其他约束条件（如路径长度限制）。可以通过DFS、BFS或动态规划来解决。

### 推荐题目
1. [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

---
处理用时：49.78秒