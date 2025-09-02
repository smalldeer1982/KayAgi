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



### 综合分析结论
本题核心在于高效识别满足条件的等高连通块。各题解主要采用两种思路：  
1. **按高度降序处理**：优先处理最高点，通过DFS/BFS标记整个山丘区域，避免低处重复计数  
2. **两次遍历法**：首次排除存在更高邻接点的区域，剩余连通块即为答案  

关键难点在于正确处理等高区域的归属，避免重复统计。按高度降序处理的方式更优，时间复杂度约为O(NM log(NM))，适合题目数据规模。

---

### 优质题解推荐

#### 1. 素质玩家孙1超（⭐⭐⭐⭐⭐）
**核心亮点**：  
- 按高度降序处理，确保每个山丘只统计一次  
- 结构体排序清晰，DFS标记逻辑简洁  
- 包含快读优化，代码高效  

**关键代码**：
```cpp
sort(a+1,a+1+o,cmp); // 按高度降序排序
for(int i=1;i<=o;i++) {
    if(!flag[x][y]) {
        bool f=1;
        for(int p=0;p<8;p++) // 检查是否山顶
            if(q[x][y]<q[x+dx[p]][y+dy[p]]) f=0;
        if(f) dfs(x,y),ans++; 
    }
}
```

#### 2. 沉辰（⭐⭐⭐⭐）
**核心亮点**：  
- BFS实现层次遍历，避免递归栈溢出  
- 使用队列维护待扩展区域，逻辑清晰  
- 通过提前标记优化重复访问  

**关键代码**：
```cpp
void bfs(int x,int y) {
    queue<int> qx,qy;
    qx.push(x); qy.push(y);
    while(!qx.empty()) {
        int fx=qx.front(), fy=qy.front();
        qx.pop(); qy.pop();
        for(int i=0;i<8;i++) {
            int rx=fx+X[i], ry=fy+Y[i];
            if(h[rx][ry]<=H && !v[rx][ry]) {
                qx.push(rx); qy.push(ry);
                v[rx][ry]=1;
            }
        }
    }
}
```

#### 3. ouuan（⭐⭐⭐⭐）
**核心亮点**：  
- 逆向思维先排除非法区域  
- 两次DFS分别处理标记和计数  
- 代码简洁，无排序操作  

**关键代码**：
```cpp
// 第一次DFS标记非山顶区域
for(int k=0;k<8;k++) 
    if(a[i][j]<a[i+dir[k][0]][j+dir[k][1]]) 
        dfs(i,j);
// 第二次统计剩余连通块
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if(!vis[i][j]) ans++, dfs(i,j);
```

---

### 关键思路总结
**最优技巧**：按高度降序处理 + 连通块标记  
1. **降序处理**：将点按高度降序排列，确保先处理最高点  
2. **标记扩散**：从每个未访问的最高点开始DFS/BFS，标记所有≤当前高度的邻接点  
3. **山顶判定**：检查当前点的八个邻接点是否均≤自身高度  

**调试经验**：  
- 注意方向数组的正确性（8方向）  
- 使用`vis`数组避免重复访问时，需在访问前标记而非访问后（防重入）  

---

### 拓展练习
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141) - 连通块统计  
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162) - 边界扩散技巧  
3. [P3958 奶酪](https://www.luogu.com.cn/problem/P3958) - 三维连通块处理

---
处理用时：81.62秒