# 题目信息

# Trapped in the Witch's Labyrinth

## 题目描述

在《列王纪》传奇英雄鲁斯塔姆的第四个任务中，一个老女巫创造了一个迷宫来困住他。迷宫是一个 $n\times m$ 的矩形网格，迷宫中每一个单元格都有箭头，指向上、下、左或右的一个特定方向。女巫对鲁斯塔姆施了魔法，他每进入一个单元格，都会按照箭头的方向移动到下一个单元格。

如果鲁斯塔姆可以离开迷宫，他将战胜女巫。否则他将永远被困在迷宫中。

还有一些单元格的方向没有被女巫确定，她希望你指定一些方向，使得鲁斯塔姆能够被困住的起始格最多。你的任务是找到使得鲁斯塔姆被困住的最多起始单元格数。

## 样例 #1

### 输入

```
3
3 3
UUU
L?R
DDD
2 3
???
???
3 3
?U?
R?L
RDL```

### 输出

```
0
6
5```

# AI分析结果

### 题目翻译
在《列王纪》传奇英雄鲁斯塔姆的第四个任务中，一个老女巫创造了一个迷宫来困住他。迷宫是一个 $n\times m$ 的矩形网格，迷宫中每一个单元格都有箭头，指向上、下、左或右的一个特定方向。女巫对鲁斯塔姆施了魔法，他每进入一个单元格，都会按照箭头的方向移动到下一个单元格。

如果鲁斯塔姆可以离开迷宫，他将战胜女巫。否则他将永远被困在迷宫中。

还有一些单元格的方向没有被女巫确定，她希望你指定一些方向，使得鲁斯塔姆能够被困住的起始格最多。你的任务是找到使得鲁斯塔姆被困住的最多起始单元格数。

### 样例 #1

#### 输入
```
3
3 3
UUU
L?R
DDD
2 3
???
???
3 3
?U?
R?L
RDL
```

#### 输出
```
0
6
5
```

### 题解分析与结论

#### 综合分析与结论
该题的核心在于如何通过指定未确定方向（`?`）的单元格方向，使得鲁斯塔姆被困住的起始单元格数最大化。题解中主要采用了DFS、BFS、并查集等算法来判断每个单元格是否能够被困住，并通过优化策略来确定未确定方向单元格的最优方向。

#### 所选题解

1. **题解作者：Gary0925 (赞：7)**  
   **星级：4.5**  
   **关键亮点：**  
   - 使用记忆化DFS来判断每个起始单元格是否能够被困住。
   - 通过临时设置当前单元格状态为“被困住”来简化判断逻辑。
   - 代码简洁，逻辑清晰，易于理解。

   **核心代码：**
   ```cpp
   bool dfs(int i, int j) {
       if (i < 1 || i > n || j < 1 || j > m) return 1;
       if (out[i][j] == -1) {
           out[i][j] = 0;
           if (c[i][j] == 'U') out[i][j] = dfs(i - 1, j);
           else if (c[i][j] == 'D') out[i][j] = dfs(i + 1, j);
           else if (c[i][j] == 'L') out[i][j] = dfs(i, j - 1);
           else if (c[i][j] == 'R') out[i][j] = dfs(i, j + 1);
           else out[i][j] = dfs(i - 1, j) && dfs(i + 1, j) && dfs(i, j - 1) && dfs(i, j + 1);
       }
       return out[i][j];
   }
   ```

2. **题解作者：littlebug (赞：6)**  
   **星级：4.0**  
   **关键亮点：**  
   - 使用BFS从边缘向内筛选出一定能走出去的单元格。
   - 通过分析未确定方向单元格的周围情况，确定其是否能够被困住。
   - 代码实现较为复杂，但思路清晰。

   **核心代码：**
   ```cpp
   void bfs() {
       queue<pii> q;
       rep(i,1,n) a[i][1]=='L' && (q.emplace(i,1),mask(i,1),1),a[i][m]=='R' && (q.emplace(i,m),mask(i,m),1);
       rep(j,1,m) a[1][j]=='U' && (q.emplace(1,j),mask(1,j),1),a[n][j]=='D' && (q.emplace(n,j),mask(n,j),1);

       pii ck; int x,y,nx,ny;
       while(!q.empty()) {
           ck=q.front(); q.pop();
           x=ck.st,y=ck.nd;

           rep(i,1,4) {
               nx=x+dx[i],ny=y+dy[i];
               if(nx<1 || nx>n || ny<1 || ny>m || b[nx][ny] || a[nx][ny]!=dc[i]) continue;
               q.emplace(nx,ny),mask(nx,ny);
           }
       }
   }
   ```

3. **题解作者：HetmesAskalana (赞：4)**  
   **星级：4.0**  
   **关键亮点：**  
   - 通过两轮DFS分别判断单元格是否能够抵达问号点和是否能够离开迷宫。
   - 通过分析问号点的周围情况，确定其是否能够被困住。
   - 代码实现较为复杂，但思路清晰。

   **核心代码：**
   ```cpp
   bool dfs(int nowx, int nowy) {
       if (nowx < 1 || nowx > n || nowy > m || nowy < 1) return false;
       if (G[nowx][nowy] == '?') return true;
       if (vis[nowx][nowy]) return type[nowx][nowy];
       vis[nowx][nowy] = true;
       int prex = nowx, prey = nowy;
       if (G[nowx][nowy] == 'U') nowx -= 1;
       else if (G[nowx][nowy] == 'D') nowx += 1;
       else if (G[nowx][nowy] == 'R') nowy += 1;
       else if (G[nowx][nowy] == 'L') nowy -= 1;

       if (dfs(nowx, nowy)) {
           type[prex][prey] = true;
           return true;
       } else return false;
   }
   ```

### 最优关键思路或技巧
1. **记忆化DFS**：通过记忆化DFS来判断每个单元格是否能够被困住，避免重复计算，提高效率。
2. **BFS筛选**：从边缘向内使用BFS筛选出一定能走出去的单元格，简化问题。
3. **两轮DFS**：通过两轮DFS分别判断单元格是否能够抵达问号点和是否能够离开迷宫，确保判断的准确性。

### 可拓展之处
该题的思路可以拓展到其他类似的图论问题，如判断图中是否存在环、判断路径是否可达等。通过DFS、BFS、并查集等算法，可以解决许多与图相关的复杂问题。

### 推荐题目
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：52.04秒