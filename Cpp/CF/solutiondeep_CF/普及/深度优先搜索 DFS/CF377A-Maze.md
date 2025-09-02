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

Pavel 喜欢网格迷宫。网格迷宫是一个 $n \times m$ 的矩形迷宫，每个单元格要么是空的，要么是墙。你只能从一个空单元格移动到另一个空单元格，且这两个单元格必须相邻（共享一条边）。

Pavel 画了一个网格迷宫，其中所有空单元格形成一个连通区域。也就是说，你可以从任何一个空单元格移动到任何其他空单元格。Pavel 不喜欢他的迷宫中有太少的墙。他想将恰好 $k$ 个空单元格变成墙，使得剩下的空单元格仍然形成一个连通区域。请你帮助他。

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

### 题解综合分析与结论

本题的核心在于如何在保证连通性的前提下，将 $k$ 个空单元格变为墙。各题解的思路大致可以分为两类：

1. **逆向思维**：先将所有空单元格变为墙，然后通过 DFS 或 BFS 恢复部分单元格为空地，确保连通性。
2. **正向思维**：通过 DFS 或 BFS 遍历空单元格，按照某种顺序（如后序遍历）将部分单元格变为墙，确保连通性。

### 所选高星题解

#### 1. 作者：Mistybranch (赞：22) - 评分：5星

**关键亮点**：
- 使用逆向思维，先将所有空单元格变为墙，然后通过 DFS 恢复部分单元格为空地，确保连通性。
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

#### 2. 作者：LRL65 (赞：20) - 评分：4星

**关键亮点**：
- 提供两种解法：常规 DFS 和“偷懒” DFS。
- 常规解法通过后序遍历删除叶子节点，确保连通性。
- “偷懒”解法直接 DFS 遍历 $sum - k$ 个单元格，逻辑简单。

**核心代码**：
```cpp
void dfs(int x, int y) {
    vis[x][y]=1;
    for(int i=0;i<4;i++) {
        int dx=x+disx[i],dy=y+disy[i];
        if(dx<=n && dx>=1 && dy>=1 && dy<=m && a[dx][dy]=='.'&&vis[dx][dy]==0) {
            dfs(dx,dy);
            if(cnt<k)cnt++,a[dx][dy]='X';
        }
    }
}
```

#### 3. 作者：JeffWang2019 (赞：4) - 评分：4星

**关键亮点**：
- 使用 BFS 恢复部分单元格为空地，确保连通性。
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

- **逆向思维**：先将所有空单元格变为墙，然后通过 DFS 或 BFS 恢复部分单元格为空地，确保连通性。这种方法避免了正向删除时的复杂判断，简化了问题。
- **后序遍历删除**：在 DFS 中，按照后序遍历的顺序删除叶子节点，确保删除后仍然保持连通性。

### 可拓展之处

- 类似问题：在保证连通性的前提下，删除或添加某些节点或边，可以借鉴本题的逆向思维或后序遍历删除策略。
- 其他应用：在图论中，类似的思路可以用于生成最小生成树、拓扑排序等问题。

### 推荐相似题目

1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得摘录

- **Mistybranch**：逆向思维的应用使得问题简化，避免了复杂的判断。
- **LRL65**：后序遍历删除叶子节点的方法确保了连通性，逻辑清晰。
- **JeffWang2019**：BFS 的队列操作和恢复顺序确保了连通性，代码结构清晰。

---
处理用时：50.72秒