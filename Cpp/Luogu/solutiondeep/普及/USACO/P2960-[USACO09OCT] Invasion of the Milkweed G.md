# 题目信息

# [USACO09OCT] Invasion of the Milkweed G

## 题目描述

Farmer John has always done his best to keep the pastures full of luscious, delicious healthy grass for the cows. He has lost the battle, though, as the evil milkweed has attained a foothold in the northwest part of his farm.

The pasture, as usual, is partitioned into a rectilinear grid of height Y (1 <= Y <= 100) and width X (1 <= X <= 100) with (1,1) being in the lower left corner (i.e., arranged as a normal X,Y coordinate grid). The milkweed has initially begun growing at square (Mx,My). Each week the milkweed propagates to all non-rocky squares that surround any square it already occupies, as many as eight more squares (both the rectilinear squares and the diagonals). After only one week in those squares, it is ready to move on to more squares.

Bessie wants to enjoy all the grass she can before the pastures are taken over by milkweed. She wonders how long it can last. If the milkweed is in square (Mx,My) at time zero, at what time does it complete its invasion of the pasture (which, for the given input data, will always happen)?

The pasture is described by a picture with '.'s for grass and '\*'s for boulders, like this example with X=4 and Y=3:

```
....
..*.
.**.
```

If the milkweed started in the lower left corner (row=1, column=1), then the map would progress like this:

```
    ....  ....  MMM.  MMMM  MMMM
    ..*.  MM*.  MM*.  MM*M  MM*M
    M**.  M**.  M**.  M**.  M**M
week  0    1    2    3    4
```

The milkweed has taken over the entire field after 4 weeks.

## 样例 #1

### 输入

```
4 3 1 1 
.... 
..*. 
.**. 
```

### 输出

```
4 
```

# AI分析结果



### 综合分析与结论
本题是典型的 **多方向BFS** 应用，关键在于正确处理坐标系转换与八方向扩散。所有题解均认同BFS是最优解法，递推与DFS存在效率或正确性问题。核心要点包括：
1. **坐标转换**：题目坐标系左下角为(1,1)，需翻转行序存储网格。
2. **层次遍历**：BFS天然保证每个点的首次访问时间即为其最短扩散时间。
3. **八方向处理**：使用方向数组涵盖所有可能的扩散方向。

### 高星题解推荐

#### 1. [hater] ⭐⭐⭐⭐⭐
**关键亮点**：
- 对比递推、DFS、BFS三种方法的效率差异，强调BFS的正确性。
- 代码简洁，使用标准队列结构，维护每个点的时间。
- **个人心得**：强调不要局限于单一解法，尝试不同思路提升理解。

**核心代码**：
```cpp
struct mmp { int x,y,step; };
queue<mmp> q;
int bfs() {
    int tot = 0;
    while (!q.empty()) {
        auto f = q.front(); q.pop();
        tot = max(tot, f.step);
        for (int i = 0; i < 8; i++) {
            mmp v = {f.x + dx[i], f.y + dy[i], f.step + 1};
            if (边界检查 && 未被访问 && 非岩石) {
                vis[v.x][v.y] = 1;
                q.push(v);
            }
        }
    }
    return tot;
}
```

#### 2. [Arcturus1350] ⭐⭐⭐⭐
**关键亮点**：
- **手写队列优化**：减少STL开销，入队时直接更新最大值，避免最后遍历。
- 明确处理坐标转换逻辑，代码可读性强。

**核心代码**：
```cpp
int q[10002][2]; // 手写队列
while (head <= tail) {
    int now_x = q[head][0], now_y = q[head][1];
    head++;
    for (int i = 0; i < 8; i++) {
        int tx = now_x + dx[i], ty = now_y + dy[i];
        if (可访问) {
            dis[tx][ty] = dis[now_x][now_y] + 1;
            ans = max(ans, dis[tx][ty]); // 实时更新最大值
            q[++tail][0] = tx; q[tail][1] = ty;
        }
    }
}
```

#### 3. [qzcbw] ⭐⭐⭐⭐
**关键亮点**：
- 详细解释坐标转换的坑点，适合新手避坑。
- 代码结构清晰，使用标准BFS模板。

**核心代码**：
```cpp
void bfs(int x, int y) {
    queue<node> q;
    q.push({x, y, 0});
    while (!q.empty()) {
        node now = q.front(); q.pop();
        ans = now.step;
        for (int i = 0; i < 8; i++) {
            int nx = now.x + dx[i], ny = now.y + dy[i];
            if (可访问) {
                vis[nx][ny] = 1;
                q.push({nx, ny, now.step + 1});
            }
        }
    }
}
```

### 关键技巧总结
- **坐标系处理**：输入的行需倒序存储，起点坐标需转换。
- **实时最大值更新**：在BFS扩展时更新最大值，减少后续遍历。
- **方向数组**：使用`dx[8]`和`dy[8]`简化八方向判断。

### 同类题目推荐
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)（八方向BFS）
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)（多方向扩散）
3. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)（层序BFS应用）

---
处理用时：47.45秒