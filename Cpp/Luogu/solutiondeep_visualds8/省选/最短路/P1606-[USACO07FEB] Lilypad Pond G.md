# 题目信息

# [USACO07FEB] Lilypad Pond G

## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.


## 说明/提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$

## 样例 #1

### 输入

```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0
```

### 输出

```
2
3
```

# AI分析结果

---
# 💡 洛语云笺的C++算法解析：Lilypad Pond G 深入学习指南 💡

今天我们来一起分析 USACO07FEB 的「Lilypad Pond G」。这道题把“骑士跳”与“最短路+方案数”结合，还要巧妙处理“原有荷叶”带来的 0 权环，是一场非常有趣的思维探险。

---

## 1. 题目解读与策略初探

✨ **本题核心挑战**：  
在一张 30×30 的棋盘上，用类似国际象棋“马走日”的跳跃方式，从起点 (3) 到终点 (4)。棋盘上有 3 种格子：  
- 0：清水，可放荷叶（代价 1）  
- 1：已有荷叶，可免费通行  
- 2：岩石，不可通行  

求：最少要额外放几片荷叶？有多少种放置这些最少荷叶的方案？

✨ **核心算法标签**：BFS / DFS 建图、最短路（SPFA / Dijkstra）、最短路计数

🗣️ **思路演进路径**  
1. 朴素想法：二维 BFS 直接跑。但原有荷叶会形成“0 权边”，导致第二问计数时 0 环无限累加。  
2. 关键转化：把“放置荷叶”视为“边权 1”，把“免费荷叶”视为“边权 0”，再跑最短路计数。但 0 环会爆炸。  
3. 最终钥匙：用 **“每个 0/3 点为起点做一次 DFS”** 的方式，只记录“必须花 1 片荷叶才能到达的下一个 0/4 点”，把所有边强制成 1，彻底消灭 0 环。建图后跑 SPFA/Dijkstra 即可。

### 🔍 算法侦探：如何在题目中发现线索？

| 线索 | 侦探笔记 |
|---|---|
| 1. 棋盘 ≤ 30×30 | N≤900，提示 O(N² log N) 甚至 O(N³) 都可接受 |
| 2. 骑士跳 8 方向 | 每个点最多 8 条出边，图非常稀疏 |
| 3. 既有“免费荷叶”又有“付费荷叶” | 出现 0 权边 & 1 权边 → 最短路计数经典场景 |
| 4. 要求“最少”+“方案数” | 双目标：最短路长度 & 计数 → SPFA/Dijkstra 套模板 |

### 🧠 思维链构建：从线索到策略
1. 朴素 BFS 想解决“最少荷叶”？可行。  
2. 但第二问“方案数”会被 0 环卡死 → 必须重构图。  
3. 关键灵感：把“连续免费荷叶”视为一个 **超级节点**，只向外连 1 权边，保证无 0 环。  
4. 用 DFS 或 BFS 预处理每个 0/3 点的“一步可达 0/4”，再跑最短路计数 → 完美！

---

## 2. 精选优质题解参考

### 题解一：D_14134（赞 35）
- **亮点**：最早提出“DFS 建 1 权图 + SPFA”的简洁思路。  
- **点评**：用 DFS 遍历每个 0/3 点，跳过免费荷叶，只把“必须花 1 片荷叶才能到的下一个 0/4”连边，彻底避免 0 环。代码短、思路清晰，是学习本题建图技巧的范本。

### 题解二：s_ShotღMaki（赞 12）
- **亮点**：完整给出“编号 → 建图 → SPFA 计数”三段式模板，变量注释详尽。  
- **点评**：代码风格现代（`read()` 快读、`long long` 防溢出），对初学者非常友好。  
- **额外提示**：作者特别提醒“输出时要减 1”，因为起点 3 的那一步不算“额外荷叶”。

### 题解三：顾 z（赞 9）
- **亮点**：用二维数组 `d[i][j]` 存最短路，直观易懂；同时指出“终点 4 不必放荷叶”。  
- **点评**：思路与 D_14134 一致，但用二维下标代替一维编号，帮助新手建立“棋盘 ↔ 图”的映射感。

### 题解四：寒鸽儿（赞 6）
- **亮点**：深入解释了“为什么 0 环会破坏计数”，并用“跳过荷叶建边”解决。  
- **点评**：文字讲解细致，适合想彻底搞懂 0 环问题的同学。

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤

| 关键点 | 分析 | 💡 学习笔记 |
|---|---|---|
| 1. 建图：消灭 0 环 | 对每个 0/3 点 DFS，遇到 1 继续走，遇到 0/4 则连 1 权边。 | 把“连续免费荷叶”视为一个超级节点，只保留“跨出”时的 1 权边。 |
| 2. 最短路计数 | SPFA/Dijkstra 模板：  
`if dis[v] > dis[u]+1` → 更新并重置计数  
`else if dis[v] == dis[u]+1` → 累加计数 | 计数时务必 `long long` 防溢出。 |
| 3. 输出细节 | 起点 3 的“首跳”不算额外荷叶，故 `ans1 = dis[ed] - 1`。 | 同时注意终点 4 本身不必放荷叶。 |

### ⚔️ 策略竞技场

| 策略 | 核心思想 | 优点 | 缺点 | 适用/得分 |
|---|---|---|---|---|
| 朴素二维 BFS | 0/1 权 BFS | 代码最短 | 无法处理计数 | 只能拿第一问部分分 |
| 直接建 0/1 权图 | 普通最短路计数 | 思路自然 | 0 环导致计数爆炸 | 会 WA |
| DFS 建 1 权图 | 本题正解 | 无 0 环，计数正确 | 需写 DFS 建图 | 100 分 |

### ✨ 优化之旅
从“0 环爆炸”到“DFS 强制 1 权”是一次典型的 **“问题转化”** 优化：  
把“免费荷叶”的 0 权边，通过 DFS 预处理后 **隐藏** 在超级节点内部，只留下“必须花钱”的 1 权边，从而让最短路计数模板直接适用。

---

## 4. C++核心代码实现赏析

### 通用核心实现（参考 D_14134）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 35, M = 900;
int n, m, st, ed;
int g[N][N], id[N][N], tot;
int dx[8] = {-2,-2,-1,-1, 1, 1, 2, 2};
int dy[8] = {-1, 1,-2, 2,-2, 2,-1, 1};
struct Edge { int to, nxt; } e[M*M*8];
int head[M], cnt, dis[M];
long long cntPath[M];
bool vis[M];

inline void add(int u, int v) {
    e[++cnt] = {v, head[u]}; head[u] = cnt;
}
inline int idx(int x, int y) { return (x-1)*m + y; }

bool used[N][N];
void dfs(int from, int x, int y) {
    if (used[x][y]) return;
    used[x][y] = 1;
    for (int k = 0; k < 8; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 1 || ny < 1 || nx > n || ny > m || used[nx][ny]) continue;
        if (g[nx][ny] == 1) dfs(from, nx, ny);
        else if (g[nx][ny] != 2) add(from, idx(nx, ny));
    }
}

void spfa() {
    queue<int> q;
    memset(dis, 0x3f, sizeof dis);
    dis[st] = 0; cntPath[st] = 1; q.push(st);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                cntPath[v] = cntPath[u];
                q.push(v);
            } else if (dis[v] == dis[u] + 1) {
                cntPath[v] += cntPath[u];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
            if (g[i][j] == 3) st = idx(i, j);
            if (g[i][j] == 4) ed = idx(i, j);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (g[i][j] == 0 || g[i][j] == 3) {
                memset(used, 0, sizeof used);
                dfs(idx(i, j), i, j);
            }
    spfa();
    if (dis[ed] == 0x3f3f3f3f) cout << "-1\n";
    else cout << dis[ed] - 1 << '\n' << cntPath[ed] << '\n';
    return 0;
}
```
- **代码解读概要**：  
  - 编号：`(i,j)` → 一维 `idx(i,j)`  
  - DFS 建图：跳过岩石，连续荷叶视为免费，仅向“必须花 1 片荷叶”的 0/4 连 1 权边。  
  - SPFA：经典最短路计数模板，边权全为 1，无 0 环。  
  - 输出：起点 3 的“首跳”不计，故 `dis[ed]-1`。

---

## 5. 算法可视化：像素动画演示

### 主题：像素骑士的荷叶之旅  
- **场景**：8×8 像素棋盘，绿色荷叶、蓝色水、灰色岩石、黄色起点、红色终点。  
- **动画步骤**：
  1. **DFS 建图**：黄色像素骑士站在每个 0/3 格，8 方向 DFS，遇到绿色荷叶继续走，遇到蓝色/红色格子则拉一条“+1”金色箭头，并高亮“荷叶计数 +1”。  
  2. **SPFA 计数**：从黄色起点开始，像素骑士沿金色箭头逐层扩散，每到达一格，格子闪白并显示当前最短路长度 & 方案数（像素字体）。  
  3. **成功/失败**：到达红色终点时，播放 8-bit 胜利音效，像素礼花；若不可达，播放失败音并显示“-1”。

- **交互**：  
  - 步进/自动播放/重置按钮  
  - 速度滑块（0.2× – 4×）  
  - 右侧实时显示 SPFA 队列 & dis/cnt 数组（像素滚动条）

---

## 6. 拓展练习与相似问题思考

### 通用思路迁移
- “0/1 权图 + 最短路计数”套路同样适用于：  
  1. 网格中“可免费拐弯”的最短路径计数  
  2. 带“传送门”的迷宫最少传送次数 & 方案数  
  3. 图上“免费边”与“付费边”混合的改造问题

### 洛谷推荐
| 题号 | 推荐理由 |
|---|---|
| P1144 最短路计数 | 裸最短路计数，巩固 SPFA/Dijkstra 模板 |
| P1608 路径统计 | 图上有 0 权边，需类似技巧处理 |
| P1979 华容道 | 状态压缩 + 最短路，锻炼“建图抽象”能力 |

---

## 7. 学习心得与经验分享

- **D_14134**：“DFS 建 1 权图”是避免 0 环的万能钥匙，任何“免费通行”场景都适用。  
- **s_ShotღMaki**：输出减 1 的坑点常踩，建议写 `assert(dis[ed] >= 1)` 自测。  
- **寒鸽儿**：调试时打印 `dis` 与 `cnt`，能快速发现 0 环导致的计数爆炸。

---

<conclusion>
今天我们学会了：  
1. 如何把“棋盘跳跃”抽象为“最短路计数”问题；  
2. 用 DFS 预处理消灭 0 环，让经典模板直接可用；  
3. 输出细节 `ans-1` 与 `long long` 防溢出。  

下次遇到“免费/付费混合”的图论题，不妨先想想“超级节点 + 强制边权”这一招！祝各位像素骑士一路顺风 🐎🌿
</conclusion>

---
处理用时：104.53秒