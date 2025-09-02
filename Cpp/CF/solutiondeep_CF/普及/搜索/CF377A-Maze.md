# 题目信息

# Maze

## 题目描述

Pavel loves grid mazes. A grid maze is an $ n×m $ rectangle maze where each cell is either empty, or is a wall. You can go from one cell to another only if both cells are empty and have a common side.

Pavel drew a grid maze with all empty cells forming a connected area. That is, you can go from any empty cell to any other one. Pavel doesn't like it when his maze has too little walls. He wants to turn exactly $ k $ empty cells into walls so that all the remaining cells still formed a connected area. Help him.

## 样例 #1

### 输入

```
3 4 2
#..#
..#.
#...
```

### 输出

```
#.X#
X.#.
#...
```

## 样例 #2

### 输入

```
5 4 5
#...
#.#.
.#..
...#
.#.#
```

### 输出

```
#XXX
#X#.
X#..
...#
.#.#
```

# AI分析结果

### 题目内容重写

#### 迷宫

##### 题目描述

Pavel喜欢网格迷宫。网格迷宫是一个 $n \times m$ 的矩形迷宫，每个单元格要么是空的，要么是墙。你只能从一个空单元格移动到另一个空单元格，且这两个单元格必须共享一条边。

Pavel画了一个网格迷宫，其中所有空单元格形成一个连通区域。也就是说，你可以从任何一个空单元格到达任何其他空单元格。Pavel不喜欢他的迷宫中有太少的墙。他想将恰好 $k$ 个空单元格变成墙，使得剩下的所有空单元格仍然形成一个连通区域。请你帮助他。

##### 样例 #1

###### 输入

```
3 4 2
#..#
..#.
#...
```

###### 输出

```
#.X#
X.#.
#...
```

##### 样例 #2

###### 输入

```
5 4 5
#...
#.#.
.#..
...#
.#.#
```

###### 输出

```
#XXX
#X#.
X#..
...#
.#.#
```

### 题解分析与结论

#### 综合分析与结论

本题的核心要求是在一个连通的网格迷宫中，将恰好 $k$ 个空单元格变成墙，同时保证剩下的空单元格仍然连通。题解中主要采用了两种思路：**逆向思维**和**DFS/BFS遍历**。

1. **逆向思维**：将所有的空单元格先变成墙，然后通过DFS或BFS恢复一部分墙为空单元格，确保恢复的数量为 $k$。这种方法避免了直接删除单元格时可能导致的连通性问题。
2. **DFS/BFS遍历**：通过DFS或BFS遍历迷宫，记录遍历顺序，然后从后往前删除单元格，确保删除的单元格不会影响剩余单元格的连通性。

#### 评分较高的题解

##### 题解1：Mistybranch (赞：22) - 5星

**关键亮点**：
- 采用逆向思维，先将所有空单元格变成墙，再通过DFS恢复部分墙为空单元格，确保连通性。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
void Search (int x, int y) {
    int curX, curY;
    
    if (k <= 0) {
        return ;
    }
    
    ma[x][y] = '.';
    k--;
    
    for (int i = 0; i < 4; i++) {
        curX = x + changeX[i];
        curY = y + changeY[i];
        
        if (1 <= curX && curX <= n && 1 <= curY && curY <= m && ma[curX][curY] == 'X' && k) {
            Search(curX, curY);
        }
    }
}
```

##### 题解2：LRL65 (赞：20) - 4星

**关键亮点**：
- 通过DFS遍历迷宫，记录遍历顺序，然后从后往前删除单元格，确保删除的单元格不会影响剩余单元格的连通性。
- 提供了两种实现方式，常规做法和偷懒做法，思路清晰。

**核心代码**：
```cpp
void dfs(int x, int y) {
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int dx = x + disx[i], dy = y + disy[i];
        if (dx <= n && dx >= 1 && dy >= 1 && dy <= m && a[dx][dy] == '.' && vis[dx][dy] == 0) {
            dfs(dx, dy);
            if (cnt < k) cnt++, a[dx][dy] = 'X';
        }
    }
}
```

##### 题解3：JeffWang2019 (赞：4) - 4星

**关键亮点**：
- 采用BFS遍历迷宫，记录恢复为空单元格的数量，确保恢复的数量为 $k$。
- 代码结构清晰，注释详细，易于理解。

**核心代码**：
```cpp
void bfs(int sx, int sy) {
    c[sx][sy] = '.';
    st = (node){sx, sy};
    q.push(st);
    cnt++;
    while (!q.empty()) {
        node ff = q.front();
        q.pop();
        int fx = ff.x, fy = ff.y;
        for (int i = 0; i < 4; i++) {
            int xx = fx + dx[i], yy = fy + dy[i];
            if (_cnt <= cnt) return;
            if (xx < 1 || yy < 1 || xx > n || yy > m || c[xx][yy] != 'X') continue;
            node gg = (node){xx, yy};
            q.push(gg);
            c[xx][yy] = '.';
            cnt++;
        }
    }
}
```

### 最优关键思路或技巧

1. **逆向思维**：将问题转化为先破坏再恢复的思路，避免直接删除单元格时可能导致的连通性问题。
2. **DFS/BFS遍历**：通过遍历迷宫记录单元格的顺序，确保删除的单元格不会影响剩余单元格的连通性。

### 可拓展之处

- **类似题目**：可以拓展到其他需要保持连通性的网格问题，如最小生成树、图的连通分量等。
- **算法优化**：可以考虑使用并查集（Union-Find）来维护单元格的连通性，进一步提高效率。

### 推荐题目

1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得摘录

- **Mistybranch**：逆向思维的应用使得问题简化，避免了直接删除单元格时的复杂情况。
- **LRL65**：通过DFS记录遍历顺序，确保删除的单元格不会影响剩余单元格的连通性，思路清晰。
- **JeffWang2019**：BFS的实现方式代码结构清晰，注释详细，易于理解。

---
处理用时：41.73秒