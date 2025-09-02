# 题目信息

# Smooth Sailing (Hard Version)

## 题目描述

The only difference between the two versions of this problem is the constraint on $ q $ . You can make hacks only if both versions of the problem are solved.

Thomas is sailing around an island surrounded by the ocean. The ocean and island can be represented by a grid with $ n $ rows and $ m $ columns. The rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The position of a cell at row $ r $ and column $ c $ can be represented as $ (r, c) $ . Below is an example of a valid grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/516df36ca6ac022124866d4043411e04ed0cf48c.png) Example of a valid gridThere are three types of cells: island, ocean and underwater volcano. Cells representing the island are marked with a '\#', cells representing the ocean are marked with a '.', and cells representing an underwater volcano are marked with a 'v'. It is guaranteed that there is at least one island cell and at least one underwater volcano cell. It is also guaranteed that the set of all island cells forms a single connected component $ ^{\dagger} $ and the set of all ocean cells and underwater volcano cells forms a single connected component. Additionally, it is guaranteed that there are no island cells at the edge of the grid (that is, at row $ 1 $ , at row $ n $ , at column $ 1 $ , and at column $ m $ ).

Define a round trip starting from cell $ (x, y) $ as a path Thomas takes which satisfies the following conditions:

- The path starts and ends at $ (x, y) $ .
- If Thomas is at cell $ (i, j) $ , he can go to cells $ (i+1, j) $ , $ (i-1, j) $ , $ (i, j-1) $ , and $ (i, j+1) $ as long as the destination cell is an ocean cell or an underwater volcano cell and is still inside the grid. Note that it is allowed for Thomas to visit the same cell multiple times in the same round trip.
- The path must go around the island and fully encircle it. Some path $ p $ fully encircles the island if it is impossible to go from an island cell to a cell on the grid border by only traveling to adjacent on a side or diagonal cells without visiting a cell on path $ p $ . In the image below, the path starting from $ (2, 2) $ , going to $ (1, 3) $ , and going back to $ (2, 2) $ the other way does not fully encircle the island and is not considered a round trip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/587237f643ee9a450f570eb64a27b00d982a357b.png) Example of a path that does not fully encircle the islandThe safety of a round trip is the minimum Manhattan distance $ ^{\ddagger} $ from a cell on the round trip to an underwater volcano (note that the presence of island cells does not impact this distance).

You have $ q $ queries. A query can be represented as $ (x, y) $ and for every query, you want to find the maximum safety of a round trip starting from $ (x, y) $ . It is guaranteed that $ (x, y) $ is an ocean cell or an underwater volcano cell.

 $ ^{\dagger} $ A set of cells forms a single connected component if from any cell of this set it is possible to reach any other cell of this set by moving only through the cells of this set, each time going to a cell with a common side.

 $ ^{\ddagger} $ Manhattan distance between cells $ (r_1, c_1) $ and $ (r_2, c_2) $ is equal to $ |r_1 - r_2| + |c_1 - c_2| $ .

## 说明/提示

For the first example, the image below shows an optimal round trip starting from $ (1, 1) $ . The round trip has a safety of $ 3 $ as the minimum Manhattan distance from a cell on the round trip to an underwater volcano is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/b0d58ba7a9650556e586a3235109c2b13f201dd2.png) Example of an optimal round tripFor the fourth example, remember that it is allowed for Thomas to visit the same cell multiple times in the same round trip. For example, doing so is necessary for the round trip starting from $ (7, 6) $ .

## 样例 #1

### 输入

```
9 9 3
.........
.........
....###..
...v#....
..###....
...##...v
...##....
.........
v........
1 1
9 1
5 7```

### 输出

```
3
0
3```

## 样例 #2

### 输入

```
3 3 5
..v
.#.
...
1 2
1 3
2 3
2 1
3 2```

### 输出

```
0
0
0
0
0```

## 样例 #3

### 输入

```
14 13 5
.............
.............
.............
...vvvvvvv...
...v.....v...
...v.###.v...
...v.#.#.v...
...v..v..v...
...v..v..v...
....v...v....
.....vvv.....
.............
.............
.............
1 1
7 7
5 6
4 10
13 6```

### 输出

```
3
0
1
0
2```

## 样例 #4

### 输入

```
10 11 4
...........
..#######..
..#..#..#..
..#.....#..
..#..v..#..
..#.###.#..
..#.#.#.#..
..#...#.#..
..#####.#..
...........
7 6
3 7
6 8
1 1```

### 输出

```
1
2
3
4```

# AI分析结果



---

**唯一算法分类**  
并查集/离线处理 + Kruskal重构树

---

### 综合分析与结论

#### 核心思路与难点
1. **问题转化**：将路径环绕条件转化为穿越特定射线的奇偶次数判断，通过拆点（奇/偶状态）建立二维状态空间。
2. **权值处理**：用多源BFS预处理每个点到火山的最小曼哈顿距离dis，路径安全值即路径上dis的最小值。
3. **连通性维护**：构建最大生成树，边权为两端点dis的最小值，通过并查集/Kruskal重构树维护状态连通性。
4. **高效查询**：对于每个查询点，判断其奇偶状态能否连通，转化为LCA查询问题。

**可视化设计要点**：
- **网格动画**：用Canvas绘制网格，不同颜色区分火山（红色）、岛屿（灰色）、海洋（蓝色）。
- **状态拆解**：将每个单元格拆分为上下两半，分别表示奇/偶状态，用半透明颜色标记连通性。
- **Kruskal过程**：动态展示按dis从大到小添加边的过程，高亮当前处理的边及其连接状态。
- **LCA查询**：用闪烁效果显示从(x,y,0)到(x,y,1)在重构树上的路径，最终LCA节点显示为金色。

---

### 题解评分（≥4星）

1. **cjZYZtcl（5星）**  
   关键亮点：同时给出整体二分和Kruskal重构树两种解法，代码实现清晰。重构树解法通过倍增LCA实现O(1)查询。

2. **Wuyanru（5星）**  
   关键亮点：用几何视角解释奇偶穿越原理，重构树解法代码简洁，附带详细图示说明。

3. **EuphoricStar（4星）**  
   关键亮点：完整代码实现Kruskal重构树，处理了射线穿越的边界条件，注释清晰。

---

### 最优思路与代码实现

**核心步骤**：
```cpp
// 多源BFS预处理dis
void bfs(){
    queue<Pi> q;
    repn(i) repm(j) if(s[i][j]=='v') q.emplace(i,j);
    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        rep(dir,0,3){
            int nx=x+dx[dir], ny=y+dy[dir];
            if(dis[nx][ny] > dis[x][y]+1)
                dis[nx][ny] = dis[x][y]+1, q.emplace(nx,ny);
        }
    }
}

// Kruskal重构树构建
void build_kruskal(){
    sort(edges.begin(), edges.end(), [](edge a, edge b){
        return min(dis[a.x],dis[a.y]) > min(dis[b.x],dis[b.y]); 
    });
    for(auto &e : edges){
        int fx=find(e.x0), fy=find(e.y0); // x0,y0为奇偶状态对应的节点
        if(fx != fy){
            fa[fx] = fa[fy] = new_node;
            new_node->w = min(dis[e.x], dis[e.y]);
        }
    }
}

// 查询处理
int query(int x, int y){
    int u = get_id(x,y,0), v = get_id(x,y,1);
    return lca(u, v)->w;
}
```

---

### 相似题目推荐
1. **P4197 Peaks**（Kruskal重构树经典题）
2. **P1967 货车运输**（最大生成树+LCA）
3. **CF1513D GCD and MST**（并查集离线处理）

---

### 可视化与复古动画设计

**像素风格实现**：
1. **网格绘制**：用16x16像素块表示单元格，火山用红色闪烁，岛屿用深灰色静态块。
2. **状态区分**：奇状态单元格上方显示半透明绿色层，偶状态显示半透明蓝色层。
3. **边添加动画**：添加边时显示黄色连线，成功合并时播放"哔"音效。
4. **LCA路径**：查询时显示从起点到LCA节点的金色光点追踪效果。

**音效设计**：
- 边合并成功：短促"滴"声（Web Audio合成方波）
- 查询完成：8-bit风格胜利音效（频率快速爬升）
- 错误操作：低沉"嗡"声

---

**总结**：本题通过几何特性转化问题，结合Kruskal重构树实现高效查询。可视化重点在于状态拆分与重构树构建过程的动态演示，复古像素风格可增强算法理解趣味性。

---
处理用时：59.40秒