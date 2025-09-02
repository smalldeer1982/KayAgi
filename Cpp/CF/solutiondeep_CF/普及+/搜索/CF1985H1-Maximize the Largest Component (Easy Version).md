# 题目信息

# Maximize the Largest Component (Easy Version)

## 题目描述

Easy and hard versions are actually different problems, so read statements of both problems completely and carefully. The only difference between the two versions is the operation.

Alex has a grid with $ n $ rows and $ m $ columns consisting of '.' and '\#' characters. A set of '\#' cells forms a connected component if from any cell in this set, it is possible to reach any other cell in this set by only moving to another cell in the set that shares a common side. The size of a connected component is the number of cells in the set.

In one operation, Alex selects any row $ r $ ( $ 1 \le r \le n $ ) or any column $ c $ ( $ 1 \le c \le m $ ), then sets every cell in row $ r $ or column $ c $ to be '\#'. Help Alex find the maximum possible size of the largest connected component of '\#' cells that he can achieve after performing the operation at most once.

## 说明/提示

In the second test case, it is optimal for Alex to set all cells in column $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 6 $ .

In the third test case, it is optimal for Alex to set all cells in row $ 2 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 9 $ .

In the fourth test case, it is optimal for Alex to set all cells in row $ 4 $ to be '\#'. Doing so will lead to the largest connected component of '\#' having a size of $ 11 $ .

## 样例 #1

### 输入

```
6
1 1
.
4 2
..
#.
#.
.#
3 5
.#.#.
..#..
.#.#.
5 5
#...#
....#
#...#
.....
...##
6 6
.#..#.
#..#..
.#...#
#.#.#.
.#.##.
###..#
6 8
..#....#
.####.#.
###.#..#
.##.#.##
.#.##.##
#..##.#.```

### 输出

```
1
6
9
11
15
30```

# AI分析结果



### 题目内容中文翻译

**题目名称**：最大化最大连通块（简单版）

**题目描述**：

Alex 拥有一个由 `n` 行 `m` 列组成的网格，每个单元格为 `.` 或 `#`。一个 `#` 的连通分量定义为：通过共享边相连的 `#` 单元格集合，且集合内任意两个单元格可互相到达。连通分量的大小为单元格数量。

Alex 可以执行一次操作：选择任意一行或一列，将其所有单元格设为 `#`。求操作后最大连通分量的可能最大值。

**样例说明**：

- 样例2：选择第2列，连通块大小为6。
- 样例3：选择第2行，连通块大小为9。
- 样例4：选择第4行，连通块大小为11。

---

### 题解分析与结论

#### 核心思路总结
1. **预处理连通块**：通过 DFS/BFS/并查集预处理所有原始 `#` 的连通块，记录每个块的大小及所属编号。
2. **枚举行/列**：对每一行或列，计算将其全部设为 `#` 后可能合并的连通块总和，包括新增的 `.` 转换数量和相邻连通块的贡献。
3. **去重优化**：使用 `set` 或 `map` 记录涉及的连通块编号，避免重复累加。

#### 关键技巧
- **连通块预处理**：高效遍历网格并为每个 `#` 单元格分配连通块编号。
- **边界处理**：用 `max`/`min` 限制行列索引，避免越界。
- **去重统计**：通过集合结构快速合并相邻连通块的大小。

---

### 高分题解推荐（评分≥4星）

#### 题解1：Eddie08012025（⭐⭐⭐⭐⭐）
**亮点**：
- 使用并查集预处理，代码结构清晰。
- 通过 `set` 去重，逻辑简洁。
- 详细注释，可读性强。

**核心代码**：
```cpp
// 预处理连通块
void dfs(int x, int y, int idx) {
    sum[idx]++, id[get(x, y)] = idx; 
    for (int i = 1; i <= 4; i++) {
        int xx = dx[i] + x, yy = dy[i] + y;
        if (xx > n || xx < 1 || yy > m || yy < 1 || id[get(xx, yy)] || !mp[get(xx, yy)]) continue;
        dfs(xx, yy, idx);
    }
}

// 计算行/列贡献
void get_ans() {
    set<int> st; int res = 0;
    for (int i = 1; i <= n; i++) {
        st.clear(); res = 0;
        for (int j = 1; j <= m; j++) {
            res += (!id[get(i, j)]); // 新增的 '.' 转换数
            st.insert(id[get(i, j)]); // 当前行及其相邻块
            st.insert(id[get(max(i-1, 1ll), j)]);
            st.insert(id[get(min(i+1, n), j)]);
        }
        for (auto j : st) res += sum[j]; // 累加去重后的块大小
        ans = max(res, ans);
    }
    // 类似处理列...
}
```

#### 题解2：BrotherCall（⭐⭐⭐⭐）
**亮点**：
- DFS 预处理，思路直观。
- 动态处理行列，代码注释详细。

**核心代码**：
```cpp
void dfs(int x, int y) {
    vis[x][y] = 1;
    shu[cnt]++;
    a[x][y] = cnt;
    for (int i = 0; i < 4; i++) {
        int nx = x + xx[i], ny = y + yy[i];
        if (nx < 1 || ny < 1 || nx > n || ny > m || vis[nx][ny] || z[nx][ny] == '.') continue;
        dfs(nx, ny);
    }
}

// 计算行贡献
for (int j = 1; j <= m; j++) {
    c.clear(); sum = 0;
    for (int i = 1; i <= n; i++) {
        if (z[i][j] == '.') sum++;
        else c.insert(a[i][j]);
        // 检查相邻列...
    }
    for (int i : c) sum += shu[i];
    ans = max(ans, sum);
}
```

---

### 相似题目推荐
1. **P1191 矩形覆盖**（枚举行列覆盖后的最大面积）
2. **P1501 矩阵变换**（行列操作与连通块分析）
3. **P3076 [USACO13FEB] Taxi G**（网格连通性与动态操作）

---
处理用时：66.01秒