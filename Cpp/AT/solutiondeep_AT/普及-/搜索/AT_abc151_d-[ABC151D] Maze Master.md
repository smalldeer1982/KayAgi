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

高橋君有一个由 $H$ 行 $W$ 列组成的迷宫，每个格子要么是墙（`#`），要么是路（`.`）。从路的格子可以上下左右移动到相邻的路的格子，但不能移动到墙或迷宫外。高橋君可以自由选择起点和终点，青木君需要从起点移动到终点，且移动次数最少。求高橋君选择起点和终点时，青木君的最大移动次数。

### 样例解释

**样例1**  
输入：
```
3 3

...

...

...
```
输出：
```
4
```
解释：选择左上角为起点，右下角为终点，青木君的移动次数为4。

**样例2**  
输入：
```
3 5

...#.

.#.#.

.#...
```
输出：
```
10
```
解释：选择左下角为起点，右上角为终点，青木君的移动次数为10。

### 题解分析与结论

#### 综合分析
本题的核心是求迷宫中任意两点之间的最长路径。由于迷宫的大小较小（$1 \leq H, W \leq 20$），可以采用暴力枚举每个起点，并通过BFS计算从该起点到所有其他点的最短路径，最后取最大值。

#### 题解评分与亮点

1. **Zachary_Cloud (4星)**  
   - **亮点**：代码结构清晰，使用四维数组存储每对点的距离，通过BFS计算最短路径，最后取最大值。
   - **代码核心**：
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

2. **HYdroKomide (4星)**  
   - **亮点**：代码简洁，使用队列进行BFS，通过二维数组存储距离，并在BFS过程中更新最大值。
   - **代码核心**：
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

3. **洛璟 (4星)**  
   - **亮点**：代码结构清晰，使用队列和二维数组进行BFS，并在BFS过程中更新最大值。
   - **代码核心**：
     ```cpp
     void bfs(int sx, int sy) {
         q.push((cccp) { sx, sy });
         t.push(0);
         fg[sx][sy] = 1;
         while (!q.empty()) {
             int nx = q.front().x;
             int ny = q.front().y;
             int nt = t.front();
             ans = max(nt, ans);
             q.pop();
             t.pop();
             for (register int i = 1; i <= 4; ++i) {
                 int dx = nx + wk[1][i];
                 int dy = ny + wk[2][i];
                 int dt = nt + 1;
                 if (dx < 0 || dy < 0 || dx >= n || dy >= m || fg[dx][dy] == 1 || c[dx][dy] == '#') continue;
                 fg[dx][dy] = 1;
                 q.push((cccp) { dx, dy });
                 t.push(dt);
             }
         }
     }
     ```

### 最优关键思路
- **暴力枚举+BFS**：由于迷宫大小较小，可以暴力枚举每个起点，通过BFS计算从该起点到所有其他点的最短路径，最后取最大值。
- **优化**：在BFS过程中，使用队列和二维数组存储距离，避免重复计算。

### 拓展思路
- **Floyd算法**：对于更大的迷宫，可以考虑使用Floyd算法计算所有点对之间的最短路径。
- **双向BFS**：对于较大的迷宫，可以使用双向BFS来加速搜索。

### 推荐题目
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得
- **调试经历**：在BFS过程中，需要注意边界条件的判断，避免数组越界。
- **踩坑教训**：初始化距离数组时，确保所有值都被正确初始化，避免出现未定义行为。
- **顿悟感想**：暴力枚举+BFS在小规模问题中是非常有效的解决方案，代码实现也相对简单。

---
处理用时：51.09秒