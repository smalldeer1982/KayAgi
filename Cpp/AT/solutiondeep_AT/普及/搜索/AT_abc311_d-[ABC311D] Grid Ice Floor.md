# 题目信息

# [ABC311D] Grid Ice Floor

## 题目描述

有一个 $N \times M$ 的矩阵，并且有一个玩家站在上面。
其中 $(i, j)$ 表示矩阵的第 $i$ 行第 $j$ 列。
矩阵被表示为 $N$ 个字符串 $S_1 S_2S_3...S_N$，每个字符串长 $M$ 个字符。

矩阵每个格子都是冰或者岩石：如果 $S_i$ 的第 $j$ 个字符，即 $(i, j)$ 对应的字符为 `.`，那么 $(i, j)$ 是冰；如果是 `#`，$(i, j)$ 就是岩石。

这个矩阵的一周（第 $1$ 行、第 $N$ 行、第 $1$ 列，第 $M$ 列）均为岩石。
玩家起始所站的点 $(2, 2)$ 恒为冰。

玩家可以移动零次或任意次，每次移动需要先选定一个方向（上下左右），并且一直沿着这个方向移动直到遇到岩石（或不是冰）。

计算出玩家可以抵达或途径的所有格点（包括滑过的）。

## 说明/提示

对于 $100\%$ 的数据：

$ 3 \le N, M \le 200 $

$S_i$ 是长为 $M$ 的字符串，仅包含 `.` 和 `#`。

矩阵的边缘都是 `#`（岩石），且 $(2,2)$ 处一定为 `.`（冰）。

#### 样例1解释
比如玩家可以经过 $(5,5)$ 通过这样移动：

$(2, 2)$ → $(5, 2)$ → $(5, 5)$

玩家也可以经过 $(2, 4)$：

$(2, 2)$ → $(2, 5)$，途经 $(2, 4)$。

但玩家无法到达 $(3, 4)$。

## 样例 #1

### 输入

```
6 6

######

#....#

#.#..#

#..#.#

#....#

######```

### 输出

```
12```

## 样例 #2

### 输入

```
21 25

#########################

#..............###...####

#..............#..#...###

#........###...#...#...##

#........#..#..#........#

#...##...#..#..#...#....#

#..#..#..###...#..#.....#

#..#..#..#..#..###......#

#..####..#..#...........#

#..#..#..###............#

#..#..#.................#

#........##.............#

#.......#..#............#

#..........#....#.......#

#........###...##....#..#

#..........#..#.#...##..#

#.......#..#....#..#.#..#

##.......##.....#....#..#

###.............#....#..#

####.................#..#

#########################```

### 输出

```
215```

# AI分析结果

### 题目内容重写
有一个 $N \times M$ 的矩阵，玩家站在上面。矩阵的每个格子是冰（`.`）或岩石（`#`）。矩阵的边缘都是岩石，玩家起始位置 $(2,2)$ 是冰。玩家可以选择一个方向（上下左右）并一直移动，直到遇到岩石。要求计算玩家可以抵达或途径的所有格点（包括滑过的）。

### 题解综合分析
本题的核心是模拟玩家在冰面上的滑动过程，直到遇到岩石为止。由于玩家不能在中途停止，因此需要一种方法来记录每个点的访问状态，并确保不会重复计算。大多数题解采用了 BFS 或 DFS 来解决这个问题，重点在于如何有效地记录和更新访问状态。

### 最优关键思路与技巧
1. **状态记录**：使用三维数组记录每个点从不同方向的访问状态，避免重复访问。
2. **滑动模拟**：在 BFS 或 DFS 中，模拟玩家滑动过程，直到遇到岩石为止。
3. **剪枝优化**：通过记忆化搜索或方向限制，减少不必要的重复计算。

### 推荐题解
#### 1. 作者：rickyxrc (赞：3) - 4星
**关键亮点**：
- 使用 BFS 进行状态转移，状态定义为 $(x, y, pos)$，即坐标和方向。
- 使用三维数组 `vis` 记录每个点从不同方向的访问状态，避免重复访问。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
std::queue<std::pair<std::pair<int, int>, int>> qu;
qu.push({{2, 2}, 0});
qu.push({{2, 2}, 1});
qu.push({{2, 2}, 2});
qu.push({{2, 2}, 3});
while (!qu.empty()) {
    auto u = qu.front();
    qu.pop();
    if (!mp[u.first.first][u.first.second] || u.first.first == 0 || u.first.second == 0 || u.first.first > n || u.first.second >= m)
        continue;
    if (vis[u.first.first][u.first.second][u.second])
        continue;
    vis[u.first.first][u.first.second][u.second] = 1;
    if (!book[u.first.first][u.first.second])
        book[u.first.first][u.first.second] = 1,
        res++;
    if (mp[u.first.first + dx[u.second]][u.first.second + dy[u.second]])
        qu.push({{u.first.first + dx[u.second], u.first.second + dy[u.second]}, u.second});
    else
        for (int i = 0; i < 4; i++)
            qu.push({{u.first.first + dx[i], u.first.second + dy[i]}, i});
}
```

#### 2. 作者：2c_s (赞：3) - 4星
**关键亮点**：
- 使用 BFS 搜索“落脚点”，即每次在岩石前停下的冰块。
- 使用二维数组 `cnt` 记录经过的格子，避免重复计算。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
while (q.size()) {
    node now = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
        int xx = now.x;
        int yy = now.y;
        while (c[xx + dx[i]][yy + dy[i]] == '.') {
            xx += dx[i];
            yy += dy[i];
            cnt[xx][yy] = 1;
        }
        if (vis[xx][yy]) continue;
        vis[xx][yy] = 1;
        q.push({xx, yy});
    }
}
```

#### 3. 作者：c1ampy (赞：0) - 4星
**关键亮点**：
- 使用 DFS 进行搜索，通过记忆化剪枝优化。
- 使用 `searched` 和 `reachable` 数组分别记录搜索状态和可达状态。
- 代码逻辑清晰，优化得当。

**核心代码**：
```cpp
void dfs(const int r, const int c, const int last_direction) {
    if (searched[r][c]) return;
    searched[r][c] = true;
    reachable[r][c] = true;
    for (int direction = 1; direction <= 4; ++direction) {
        if (direction + last_direction == 5) continue;
        int cur_r = r, cur_c = c;
        while (map[cur_r + dr[direction]][cur_c + dc[direction]] == '.') {
            cur_r += dr[direction];
            cur_c += dc[direction];
            reachable[cur_r][cur_c] = true;
        }
        dfs(cur_r, cur_c, direction);
    }
}
```

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1131 拯救大兵瑞恩](https://www.luogu.com.cn/problem/P1131)

这些题目都涉及到网格图的遍历和状态记录，与本题的解题思路相似，适合进一步练习。

---
处理用时：45.13秒