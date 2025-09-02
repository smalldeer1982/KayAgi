# 题目信息

# [ABC151D] Maze Master

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc151/tasks/abc151_d

高橋君は、縦 $ H $ マス、横 $ W $ マスの $ H\ \times\ W $ マスからなる迷路を持っています。

上から $ i $ 行目、左から $ j $ 列目のマス $ (i,j) $ は、 $ S_{ij} $ が `#` のとき壁であり、`.` のとき道です。

道のマスからは、上下左右に隣接する道のマスに移動することができます。

迷路の外に移動すること、壁のマスへ移動すること、斜めに移動することはできません。

高橋君は、道のマスからスタートとゴールを自由に決め、迷路を青木君に渡します。

青木君は、移動回数が最小になるようにしてスタートからゴールまで移動します。

高橋君がスタートとゴールの位置を適切に定めたとき、青木君の移動回数は最大で何回になるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 20 $
- $ S_{ij} $ は `.` か `#`
- $ S $ は `.` を $ 2 $ つ以上含む
- 任意の道のマスから任意の道のマスまで $ 0 $ 回以上の移動で到達できる

### Sample Explanation 1

高橋君が左上のマスをスタート、右下のマスをゴールにした場合、青木君の移動回数は $ 4 $ 回になります。

### Sample Explanation 2

高橋君が左下のマスをスタート、右上のマスをゴールにした場合、青木君の移動回数は $ 10 $ 回になります。

## 样例 #1

### 输入

```
3 3

...

...

...```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5

...#.

.#.#.

.#...```

### 输出

```
10```

# AI分析结果

### 题目内容重写
高橋君有一个由 $H$ 行 $W$ 列组成的迷宫，每个格子要么是墙（`#`），要么是路（`.`）。路与路之间可以上下左右移动，但不能斜向移动或移动到墙或迷宫外。高橋君可以自由选择起点和终点，青木君需要从起点到终点移动，且移动次数最少。求高橋君选择起点和终点后，青木君的最大移动次数。

### 题解分析与结论
本题的核心是求迷宫中任意两点之间的最长最短路径。由于迷宫的大小较小（$1 \le H, W \le 20$），可以采用暴力枚举每个起点，通过 BFS 计算到其他所有点的最短路径，最终取最大值。

#### 题解对比
1. **Zachary_Cloud**（4星）
   - **亮点**：代码结构清晰，使用了四维数组 `f[i][j][x][y]` 存储从 `(i,j)` 到 `(x,y)` 的最短路径，避免了重复计算。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; ++i)
         for (int j = 1; j <= m; ++j) {
             if (a[i][j] == '#') continue;
             for (int x = 1; x <= n; ++x)
                 for (int y = 1; y <= m; ++y) b[x][y] = 0;
             b[i][j] = 1;
             f[i][j][i][j] = 0;
             head = 1; tail = 1;
             q[head].l = i; q[head].r = j;
             while (head <= tail) {
                 for (int k = 0; k <= 3; k++) {
                     int x = q[head].l + dx[k], y = q[head].r + dy[k];
                     if (a[x][y] == '.' && b[x][y] == 0) {
                         tail++; b[x][y] = 1;
                         q[tail].l = x; q[tail].r = y;
                         f[i][j][x][y] = f[i][j][q[head].l][q[head].r] + 1;
                         Max = max(Max, f[i][j][x][y]);
                     }
                 }
                 head++;
             }
         }
     ```

2. **HYdroKomide**（4星）
   - **亮点**：使用了 `dis` 数组记录距离，`vis` 数组记录访问状态，代码简洁易懂。
   - **核心代码**：
     ```cpp
     int bfs(int sx, int sy) {
         int ret = 0;
         memset(vis, false, sizeof(vis));
         memset(dis, 0, sizeof(dis));
         q.push(node{sx, sy});
         vis[sx][sy] = true;
         while (!q.empty()) {
             int x = q.front().x, y = q.front().y;
             q.pop();
             for (int i = 0; i < 4; i++) {
                 int xn = x + dx[i], yn = y + dy[i];
                 if (xn < 1 || xn > n || yn < 1 || yn > m || a[xn][yn] == '#' || vis[xn][yn]) continue;
                 vis[xn][yn] = true;
                 dis[xn][yn] = dis[x][y] + 1;
                 ret = max(ret, dis[xn][yn]);
                 q.push(node{xn, yn});
             }
         }
         return ret;
     }
     ```

3. **Herowin**（3星）
   - **亮点**：使用了 Floyd 算法，虽然时间复杂度较高，但思路新颖。
   - **核心代码**：
     ```cpp
     for (int k = 1; k <= omiga; k++) {
         for (int i = 1; i <= omiga; i++) {
             for (int j = 1; j <= omiga; j++) {
                 d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
             }
         }
     }
     ```

### 最优关键思路
- **BFS 暴力枚举**：由于迷宫大小较小，可以通过 BFS 枚举每个起点，计算到其他所有点的最短路径，最终取最大值。
- **优化存储**：使用 `dis` 数组记录距离，`vis` 数组记录访问状态，避免重复计算。

### 拓展思路
- **Floyd 算法**：虽然时间复杂度较高，但可以用于解决更复杂的图论问题。
- **双向 BFS**：对于更大的迷宫，可以考虑使用双向 BFS 来优化搜索效率。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)

### 个人心得
- **调试经历**：在 BFS 中，注意边界条件和访问状态的更新，避免死循环或重复访问。
- **踩坑教训**：Floyd 算法虽然思路简单，但在大数据量下容易超时，需谨慎使用。

---
处理用时：44.44秒