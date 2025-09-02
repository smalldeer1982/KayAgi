# 题目信息

# [USACO08NOV] Guarding the Farm S

## 题目描述

The farm has many hills upon which Farmer John would like to place guards to ensure the safety of his valuable milk-cows.

He wonders how many guards he will need if he wishes to put one on top of each hill. He has a map supplied as a matrix of integers; the matrix has N (1 < N <= 700) rows and M (1 < M <= 700) columns. Each member of the matrix is an altitude H\_ij (0 <= H\_ij <= 10,000). Help him determine the number of hilltops on the map.

A hilltop is one or more adjacent matrix elements of the same value surrounded exclusively by either the edge of the map or elements with a lower (smaller) altitude. Two different elements are adjacent if the magnitude of difference in their X coordinates is no greater than 1 and the magnitude of differences in their Y coordinates is also no greater than 1.


## 说明/提示

There are three peaks: The one with height 4 on the left top, one of the points with height 2 at the bottom part, and one of the points with height 1 on the right top corner.


## 样例 #1

### 输入

```
8 7 
4 3 2 2 1 0 1 
3 3 3 2 1 0 1 
2 2 2 2 1 0 0 
2 1 1 1 1 0 0 
1 1 0 0 0 1 0 
0 0 0 1 1 1 0 
0 1 2 2 1 1 0 
0 1 1 1 2 1 0 
```

### 输出

```
3 
```

# AI分析结果



### 综合分析与结论
题目要求统计所有高度相同且被严格更低的区域包围的连通块（山丘）。核心挑战在于高效识别符合条件的连通块并避免重复计数。各题解主要采用两种思路：①排序后从高到低DFS/BFS标记连通块；②两次遍历标记无法成为山丘的区域，统计剩余连通块。最优解法为第二种，因其避免排序，时间复杂度更低。

---

### 精选题解（评分≥4星）

#### 1. 作者：ouuan（★★★★★）
**关键亮点**：  
- **逆向思维**：通过标记所有周边存在更高点的连通块，直接排除非山丘区域，剩余未标记的连通块即为答案。  
- **无需排序**：两次DFS遍历即可完成，时间复杂度为O(nm)，优于排序法的O(nm log nm)。  
- **代码简洁**：使用单个DFS函数完成标记与统计。  

**核心代码**：
```cpp
for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) {
    for (int k=0;k<8;++k) {
        if (a[i][j]<a[i+dir[k][0]][j+dir[k][1]]) 
            dfs(i,j); // 标记无法成为山丘的区域
    }
}
for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) {
    if (!vis[i][j]) { 
        ++ans; 
        dfs(i,j); // 统计剩余连通块
    }
}
```

#### 2. 作者：素质玩家孙1超（★★★★）
**关键亮点**：  
- **排序预处理**：按高度降序处理，确保优先标记最高点所在的连通块。  
- **DFS标记法**：从最高点开始扩散，避免低点干扰。  
- **逻辑清晰**：代码结构易于理解，适合学习DFS应用。  

**核心代码**：
```cpp
sort(a+1,a+1+o,cmp); // 按高度降序排序
for (int i=1;i<=o;++i) {
    int x=a[i].x, y=a[i].y;
    if (!flag[x][y] && 周边无更高点) {
        dfs(x,y); // 标记整个山丘
        ans++;
    }
}
```

#### 3. 作者：沉辰（★★★★）
**关键亮点**：  
- **BFS队列优化**：避免递归栈溢出风险，适合大规模数据。  
- **排序预处理**：与孙1超思路类似，但用队列实现更稳定。  

**核心代码**：
```cpp
sort(a+1,a+tot+1,cmp); // 排序
for (int i=1;i<=tot;++i) {
    if (!vis[a[i].x][a[i].y]) {
        bfs(a[i].x,a[i].y); // BFS标记
        ans++;
    }
}
```

---

### 最优思路总结
**关键技巧**：  
- **逆向标记法**（ouuan）：通过排除法减少计算量，避免排序。  
- **连通块扩散条件**：在DFS/BFS中严格判断高度关系，确保只扩散到更低或等高点。  

**可拓展应用**：  
- **岛屿问题**：如统计封闭岛屿数量（洛谷P1254）。  
- **最大连通区域**：如寻找矩阵中最大全1子矩阵（需调整条件）。  

---

### 推荐相似题目
1. **P1312 棋盘问题**（连通块统计）  
2. **P2895 Meteor Shower**（BFS扩散与条件判断）  
3. **P1162 填涂颜色**（逆向标记法应用）  

---

### 个人心得摘录
- **作者Hiraeth**：在DFS中错误使用全局变量导致逻辑错误，强调局部变量的重要性。  
- **作者吉瑞降临**：将问题类比为“倒水覆盖”，形象化理解山丘扩散过程。  
- **作者ouuan**：通过严格数学推导验证思路正确性，避免盲目尝试。  

（以上内容经过归纳整理，重点突出核心思路与优化技巧，便于快速掌握解题关键。）

---
处理用时：85.71秒