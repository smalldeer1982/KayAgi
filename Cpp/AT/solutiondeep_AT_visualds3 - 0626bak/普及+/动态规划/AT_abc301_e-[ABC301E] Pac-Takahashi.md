# 题目信息

# [ABC301E] Pac-Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_e

$ H $ 行 $ W $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマス目を $ (i,j) $ と表します。 グリッドの各マスはスタートマス、ゴールマス、空マス、壁マス、お菓子マスのいずれかです。 $ (i,j) $ が何のマスであるかは文字 $ A_{i,j} $ によって表され、$ A_{i,j}= $ `S` のときスタートマス、 $ A_{i,j}= $ `G` のときゴールマス、 $ A_{i,j}= $ `.` のとき空マス、 $ A_{i,j}= $ `#` のとき壁マス、 $ A_{i,j}= $ `o` のときお菓子マスです。 ここで、スタートマスとゴールマスはちょうど $ 1 $ つずつあり、お菓子マスは **$ 18 $ 個以下**であることが保証されます。

高橋くんは現在スタートマスにいます。 高橋くんは、上下左右に隣接するマスであって壁マスでないマスに移動することを繰り返し行えます。 高橋くんは今から $ T $ 回以下の移動によってゴールマスに到達したいです。 そのようなことは可能かどうか判定してください。 可能な場合は、最終的にゴールマスにいるという条件のもとで、移動の途中に訪れるお菓子マスの数の最大値を求めてください。 ただし、$ 1 $ つのお菓子マスに複数回訪れた場合でも、カウントするのは $ 1 $ 回のみです。

## 说明/提示

### 制約

- $ 1\leq\ H,W\ \leq\ 300 $
- $ 1\ \leq\ T\ \leq\ 2\times\ 10^6 $
- $ H,W,T $ は整数
- $ A_{i,j} $ は `S`, `G`, `.`, `#`, `o` のいずれか
- $ A_{i,j}= $ `S` を満たす $ (i,j) $ の組がちょうど $ 1 $ つ存在する
- $ A_{i,j}= $ `G` を満たす $ (i,j) $ の組がちょうど $ 1 $ つ存在する
- $ A_{i,j}= $ `o` を満たす $ (i,j) $ の組は **$ 18 $ 個以下**
 
### Sample Explanation 1

$ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (1,3)\ \rightarrow\ (2,3)\ \rightarrow\ (1,3) $ と $ 4 $ 回移動すると、 $ 1 $ 個のお菓子マスを訪れた上で最終的にゴールマスにいることができます。 $ 5 $ 回以下の移動で $ 2 $ 個のお菓子マスを訪れた上で最終的にゴールマスにいることはできないので、$ 1 $ が答えです。 なお、$ (1,1)\ \rightarrow\ (2,1)\ \rightarrow\ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (1,3)\ \rightarrow\ (2,3) $ と移動すると $ 5 $ 回の移動で $ 2 $ 個のお菓子マスを訪れることができますが、最終的にゴールマスにいないため無効であることに注意してください。

### Sample Explanation 2

$ 1 $ 回以下の移動でゴールマスに到達することはできません。

## 样例 #1

### 输入

```
3 3 5

S.G

o#o

.#.```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3 1

S.G

.#o

o#.```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 10 2000000

S.o..ooo..

..o..o.o..

..o..ooo..

..o..o.o..

..o..ooo.G```

### 输出

```
18```

# AI分析结果



# 题目翻译

## 题目描述

给定一个 $H$ 行 $W$ 列的网格。从上到下第 $i$ 行、从左到右第 $j$ 列的格子记为 $(i,j)$。每个格子可能是起点（`S`）、终点（`G`）、空地（`.`）、墙壁（`#`）或糖果（`o`）。保证起点和终点各有一个，糖果数量不超过 18 个。

高桥君需要从起点出发，在 **最多 $T$ 次移动** 内到达终点。求在满足条件的情况下，最多能经过多少个不同的糖果格子（多次访问同一糖果仅算一次）。

## 输入格式
输入包含 $H+1$ 行：
- 第一行为三个整数 $H, W, T$
- 后续 $H$ 行每行一个长度为 $W$ 的字符串，表示网格

## 输出格式
输出一个整数表示最大糖果数，若无法在 $T$ 步内到达终点则输出 `-1`

---

# 算法分类
无算法分类（核心为 **状压动态规划**）

---

# 综合分析与结论

## 题解思路与核心难点
**核心思路**：将问题拆解为两个阶段：
1. **预处理关键点间的最短路径**：使用 BFS 计算起点、终点和所有糖果之间的两两最短距离
2. **状态压缩动态规划**：用二进制状态表示已访问的糖果集合，DP 状态为 `dp[当前所在点][状态] = 最小步数`

**解决难点**：
1. **高效预处理**：对每个关键点进行 BFS，时间复杂度 $O(20 \times HW)$，满足网格规模
2. **状态设计**：将 $2^{18}$ 种状态压缩为可处理的范围，通过动态规划寻找最优路径
3. **时空平衡**：使用 `dp[状态][当前位置]` 的二维状态存储，避免三维数组的内存爆炸

## 关键状态转移方程
$$
dp_{new\_state}^{new\_pos} = \min(
   dp_{new\_state}^{new\_pos}, \ 
   dp_{old\_state}^{old\_pos} + dis(old\_pos, new\_pos)
)
$$
其中：
- `new_state = old_state | (1 << new_pos)`
- `dis` 为预处理的最短距离

## 可视化设计要点
**复古像素风格 DP 演示**：
1. **网格绘制**：将关键点编号并绘制为 16x16 像素方块，起点用绿色、终点用红色、糖果用黄色
2. **状态转移动画**：用闪烁效果显示当前更新的状态位，转移时显示两点间的连线
3. **音效设计**：
   - 状态更新：8-bit "滴" 声
   - 找到更优解：上升音阶
   - 最终解：胜利小号音效
4. **自动演示模式**：按状态大小升序自动遍历，用不同颜色区分已访问/未访问状态

---

# 题解清单（4星及以上）

## 1. DengDuck（⭐⭐⭐⭐⭐）
**亮点**：
- 清晰的预处理与 DP 分离结构
- 显式处理起点终点编号
- 最终状态检查逻辑完备  
**核心代码**：
```cpp
for(int i=(1<<(cnt-2));i<=(1<<cnt)-1;i++){
    if(f[cnt][i] > t) continue;
    LL sum = 0;
    for(int k=1;k<=cnt-2;k++) 
        if((i>>(k-1))&1) sum++;
    mx = max(mx,sum);
}
```

## 2. sunzz3183（⭐⭐⭐⭐）
**亮点**：
- 按状态中 1 的数量分阶段转移
- 显式处理起点终点与其他点的关系  
**优化技巧**：
```cpp
vector<int> vt[22]; // 按状态中1的数量分组
for(int szz=1; szz<=cnt; szz++)
    for(auto i : vt[szz])
        for(int j=1; j<=cnt; j++)
            if((i>>(j-1))&1)
                for(int l=1; l<=cnt; l++)
                    if(!((i>>(l-1))&1))
                        f[i|(1<<(l-1))][l] = min(...);
```

## 3. Kylin_ZHH（⭐⭐⭐⭐）
**亮点**：
- 记忆化搜索实现 DP
- 使用 __builtin_popcount 快速计算糖果数  
**剪枝技巧**：
```cpp
for(int i=(1<<to)-1; i>=0; i--) {
    if(__builtin_popcount(i) <= ans) continue; // 剪枝
    if(dfs(to, i) <= T) ans = __builtin_popcount(i);
}
```

---

# 核心代码实现

## 预处理关键点距离
```cpp
vector<PII> key_points; // 存储所有关键点
void bfs(int idx) {
    auto [sx, sy] = key_points[idx];
    memset(dis[idx], 0x3f, sizeof dis[idx]);
    queue<pair<int, int>> q;
    q.emplace(sx, sy);
    dis[idx][sx][sy] = 0;
    
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (valid(nx, ny) && dis[idx][nx][ny] > dis[idx][x][y] + 1) {
                dis[idx][nx][ny] = dis[idx][x][y] + 1;
                q.emplace(nx, ny);
            }
        }
    }
}
```

## 状压 DP 核心
```cpp
memset(dp, 0x3f, sizeof dp);
dp[start_id][1 << start_id] = 0; // 初始化起点

for (int state = 0; state < (1 << n); state++) {
    for (int u = 0; u < n; u++) {
        if (!(state & (1 << u))) continue;
        for (int v = 0; v < n; v++) {
            if (state & (1 << v)) continue;
            int new_state = state | (1 << v);
            dp[v][new_state] = min(dp[v][new_state], 
                                 dp[u][state] + dist[u][v]);
        }
    }
}
```

---

# 同类型题目推荐
1. **洛谷P1433** - 吃奶酪（状压DP经典）
2. **洛谷P1171** - 售货员的难题（旅行商问题变形）
3. **Codeforces 580D** - Kefa and Dishes（状压DP+转移优化）

---

# 可视化示例（伪代码）

```javascript
// Canvas绘制关键点
function drawGrid() {
    ctx.fillStyle = "#2C3E50";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    
    keyPoints.forEach((p, i) => {
        ctx.fillStyle = getColor(i); // 起点/终点/糖果不同颜色
        ctx.fillRect(p.x*16, p.y*16, 14, 14);
    });
}

// DP状态更新动画
function animateDP() {
    let state = currentState++;
    if (state >= (1 << 18)) return;
    
    // 高亮当前状态位
    highlightBits(state); 
    
    // 更新所有可能的转移
    keyPoints.forEach(u => {
        if (!(state & (1 << u))) return;
        keyPoints.forEach(v => {
            if (state & (1 << v)) return;
            let newState = state | (1 << v);
            let newCost = dp[u][state] + dist[u][v];
            if (newCost < dp[v][newState]) {
                playSound('update'); // 播放更新音效
                dp[v][newState] = newCost;
                drawArrow(u, v); // 绘制转移箭头
            }
        });
    });
    
    requestAnimationFrame(animateDP);
}
```

---

**互动提示**：点击不同糖果可锁定查看其状态转移路径，按空格键切换自动/手动模式。最终最优路径将用闪烁金色边框显示。

---
处理用时：113.10秒