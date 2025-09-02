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

### 题目内容重写

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

这道题的核心是通过对迷宫中的箭头方向进行合理分配，使得尽可能多的起始点无法离开迷宫。题解的主要思路是通过DFS或BFS遍历迷宫，标记哪些点可以离开迷宫，哪些点无法离开。对于未确定的箭头方向（`?`），通过合理的方向分配，使得这些点也无法离开迷宫。

### 精选题解

#### 1. 作者：Gary0925 (赞：7)  
**星级：5星**  
**关键亮点：**  
- 使用记忆化DFS，通过`out`数组记录每个点是否能离开迷宫。
- 对于`?`的处理非常巧妙，通过临时标记为“可以困住”来简化判断。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码：**
```cpp
bool dfs(int i, int j) {
    if (i < 1 || i > n || j < 1 || j > m) return 1;
    if (out[i][j] == -1) {
        out[i][j] = 0; // 临时标记为可以困住
        if (c[i][j] == 'U') out[i][j] = dfs(i - 1, j);
        else if (c[i][j] == 'D') out[i][j] = dfs(i + 1, j);
        else if (c[i][j] == 'L') out[i][j] = dfs(i, j - 1);
        else if (c[i][j] == 'R') out[i][j] = dfs(i, j + 1);
        else out[i][j] = dfs(i - 1, j) && dfs(i + 1, j) && dfs(i, j - 1) && dfs(i, j + 1);
    }
    return out[i][j];
}
```

#### 2. 作者：littlebug (赞：6)  
**星级：4星**  
**关键亮点：**  
- 使用BFS从外向内遍历，标记所有能离开迷宫的点。
- 对于`?`的处理，通过判断周围是否有无法离开的点来决定其方向。
- 代码结构清晰，适合有一定基础的读者。

**核心代码：**
```cpp
void bfs() {
    queue <pii> q;
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

#### 3. 作者：HetmesAskalana (赞：4)  
**星级：4星**  
**关键亮点：**  
- 使用两轮DFS，分别判断是否能抵达问号点和是否能离开迷宫。
- 对于`?`的处理，通过判断周围是否有无法离开的点来决定其方向。
- 代码逻辑清晰，适合有一定基础的读者。

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

### 最优关键思路与技巧

1. **记忆化DFS**：通过记录每个点的状态，避免重复计算，提高效率。
2. **BFS从外向内遍历**：通过从边界向内遍历，快速标记所有能离开迷宫的点。
3. **`?`的处理**：通过判断周围点的状态，合理分配方向，使得尽可能多的点无法离开迷宫。

### 拓展思路

类似的问题可以通过DFS或BFS进行遍历，结合记忆化或状态记录来优化。对于未确定的点，可以通过合理的方向分配来达到最优解。

### 推荐题目

1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得摘录

- **Gary0925**：通过临时标记为“可以困住”来简化判断，大大减少了代码复杂度。
- **littlebug**：从外向内遍历的思路非常巧妙，避免了复杂的判断逻辑。
- **HetmesAskalana**：两轮DFS的设计使得代码逻辑更加清晰，易于理解。

---
处理用时：51.33秒