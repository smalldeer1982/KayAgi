# 题目信息

# [USACO21DEC]  Tickets P

## 题目描述

Bessie 正在参加远足旅行！她当前正在旅行的路线由编号为 $1\ldots N$（$1\le N\le 10^5$）的 $N$ 个检查点组成。

有 $K$（$1\le K\le 10^5$）张票可供购买。第 $i$ 张票可以在检查站 $c_i$（$1\le c_i\le N$）以 $p_i$（$1\le p_i\le 10^9$）的价格购得，并且可以用其进入所有检查站 $[a_i,b_i]$（$1\le a_i\le b_i\le N$）。在进入任何检查站之前，Bessie 必须已购买一张允许其进入该检查站的票。一旦 Bessie 可以前往某一检查站，她就可以在未来的任何时候回到该检查站。

对于每一个 $i\in [1,N]$，如果 Bessie 最初只能进入检查点 $i$，输出使得可以进入检查点 $1$ 和 $N$ 所需的最低总价。如果无法这样做，输出 $-1$。


## 说明/提示

【样例解释】

如果 Bessie 从检查点 $i=4$ 开始，那么一种购得进入检查点 $1$ 和 $N$ 的方法如下：

在检查点 $4$ 购买第一张票，使 Bessie 可以进入检查点 $2$ 和 $3$。

在检查点 $2$ 购买第三张票，使 Bessie 可以进入检查点 $7$。

回到检查点 $4$ 购买第二张票，使 Bessie 可以进入检查点 $5$ 和 $6$。

在检查点 $6$ 购买第四张票，使 Bessie 可以进入检查点 $1$。

【数据范围】

- 测试点 1-7 满足 $N,K\le 1000$。
- 测试点 8-19 没有额外限制。


## 样例 #1

### 输入

```
7 6
4 1 2 3
4 10 5 6
2 100 7 7
6 1000 1 1
5 10000 1 4
6 100000 5 6```

### 输出

```
-1
-1
-1
1111
10100
110100
-1```

# AI分析结果

---
# 💡 洛语云笺的C++算法解析：[USACO21DEC] Tickets P 深入学习指南 💡

> 今天我们一起拆解这张“门票迷宫”——Bessie 的远足路线。  
> 题目看似复杂，实则隐藏着一条“最短路 + 数据结构”的黄金通道。  
> 让我们像侦探一样，从线索到策略，一步步揭开最优解的面纱！

---

## 1. 题目解读与策略初探

✨ **本题核心挑战**：  
“区间票”带来**区间连边**，而“重复经过只算一次”带来**路径重叠**问题。  
如何高效建图并同时计算到 1 与 n 的最小代价，是最大难点。

✨ **核心算法标签**：  
- 最短路 (Dijkstra)  
- 线段树优化建图 (Segment-Tree Graph)  
- 反图技巧  
- 三次 Dijkstra 套路  

### 🗣️ 初步分析
> 1. 最直观想法：枚举起点 → 跑最短路 → 合并到 1 与 n 的距离。  
> 2. 发现区间 [a,b] 到 c 的边数量高达 O(N·K)，无法暴力连边。  
> 3. **线段树优化建图**登场：把区间连边压缩到 O(log N) 级别。  
> 4. **三次 Dijkstra** 解决重叠：  
>   - 第一次：以 1 为源跑最短路（反图）。  
>   - 第二次：以 n 为源跑最短路（反图）。  
>   - 第三次：把 `dis1[i] + dis2[i]` 作为初始值再跑一遍最短路，消除重复边。

🔑 **钥匙比喻**：  
“线段树”像一把万能钥匙，把巨大的区间门拆成 log 级的小门；  
“三次 Dijkstra”像三把尺子，分别量出到 1、到 n、以及消除重叠后的最短距离。

---

### 🔍 算法侦探：如何在题目中发现线索？
| 线索 | 发现与解读 |
|------|------------|
| **区间票** | `[a_i,b_i]` 暗示需要 **区间数据结构** 优化建图。 |
| **重复边只算一次** | 直接相加 `dis1[i]+dis2[i]` 会重复 → 需要 **再跑一遍最短路** 消除重叠。 |
| **N,K ≤ 1e5** | 允许 `O(N log N)` 或 `O(N log² N)`，排除暴力 O(N·K)。 |

---

### 🧠 思维链构建：从线索到策略
> 1. 看到“区间”+“最短路” → 想到线段树优化建图（CF786B Legacy 套路）。  
> 2. 看到“重复边只算一次” → 想到经典 trick：先分别求 `dis1`、`dis2`，再以 `dis1+dis2` 为初值跑第三次最短路。  
> 3. 复杂度验证：线段树 + 三次 Dijkstra 为 `O((N+K) log² N)`，可过。

---

## 2. 精选优质题解参考

| 题解 | 亮点提炼 |
|------|----------|
| **ETHANK**（赞14） | 最早完整阐述“三次 Dijkstra”思路，并给出 `O(N log² N)` 线段树建图代码；同时提出 `O(N log N)` 势能线段树优化方向。 |
| **Benq 思路（Anonymely）** | 把“线段树区间”当作动态边，第一次松弛即永久删除区间，达到 `O(N log N)`。 |
| **xiezheyuan**（赞0） | 用“超级汇点 T”统一解释 `dis1+dis2` 再跑最短路的思想，图论模型清晰。 |
| **vectorwyx & cmll02** | 提供简洁易读的线段树建图模板，便于初学者上手。 |

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤
| 关键点 | 分析与学习笔记 |
|--------|----------------|
| **1. 区间连边压缩** | 用线段树把 `[a,b] → 点` 的 O(N) 边拆成 O(log N) 条。  
💡 学习笔记：线段树优化建图是解决“区间→点”的经典套路。 |
| **2. 反图技巧** | 把“从 i 出发到 1” 转成“从 1 出发到 i”的最短路，减少源点数量。 |
| **3. 消除重叠路径** | 把 `dis1[i]+dis2[i]` 作为新边权，再跑一遍最短路即可保证每条边只算一次。  
💡 学习笔记：这是“多源最短路”的通用技巧，可推广到其他重叠路径问题。 |

---

### ⚔️ 策略竞技场：不同解法对比
| 策略 | 核心思想 | 复杂度 | 适用场景 |
|------|----------|--------|----------|
| 暴力枚举源点 | 每个点跑一次 Dijkstra | O(N·K log N) | 仅 37 分 |
| 线段树建图 + 三次 Dijkstra | 区间压缩 + 重叠消除 | O(N log² N) | 通用满分 |
| 势能线段树 | 动态删除已用区间 | O(N log N) | 理论最优 |

---

### ✨ 优化之旅：从“能做”到“做好”
> 1. **起点**：暴力连区间边 → 边数爆炸。  
> 2. **发现瓶颈**：区间连边数量多。  
> 3. **钥匙**：线段树压缩区间 → 边数降至 O(log N)。  
> 4. **升华**：三次 Dijkstra 消除重叠 → 保证每条边只算一次。  

---

## 4. C++核心代码实现赏析

### 本题通用核心实现参考
> 来源：综合 ETHANK、Anonymely 思路，给出清晰易读的 `O(N log² N)` 版本。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const ll INF = 1e18;

int n, m, tot;
vector<pair<int, ll>> g[N * 4];
int pos[N];                // 叶子编号
ll dis[3][N * 4];

// ===== 线段树建图 =====
void build(int p, int l, int r) {
    if (l == r) { pos[l] = p; return; }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    g[p << 1].emplace_back(p, 0);
    g[p << 1 | 1].emplace_back(p, 0);
}
void link(int p, int l, int r, int ql, int qr, int v, ll w) {
    if (ql <= l && r <= qr) { g[p].emplace_back(v, w); return; }
    int mid = (l + r) >> 1;
    if (ql <= mid) link(p << 1, l, mid, ql, qr, v, w);
    if (qr > mid) link(p << 1 | 1, mid + 1, r, ql, qr, v, w);
}

// ===== 三次 Dijkstra =====
void dijkstra(int s, ll *d, bool init = false) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    if (!init) {
        fill(d, d + tot + 1, INF);
        d[s] = 0; pq.emplace(0, s);
    } else {
        for (int i = 1; i <= tot; ++i) pq.emplace(d[i], i);
    }
    vector<bool> vis(tot + 1);
    while (!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [v, w] : g[u]) {
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.emplace(d[v], v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    tot = 4 * n; // 线段树节点
    build(1, 1, n);

    for (int i = 1, c, p, a, b; i <= m; ++i) {
        cin >> c >> p >> a >> b;
        int ticket = ++tot; // 票节点
        g[ticket].emplace_back(pos[c], p);   // 票 → c 权 p
        link(1, 1, n, a, b, ticket, 0);      // 区间 → 票 权 0
    }

    dijkstra(pos[1], dis[0]);
    dijkstra(pos[n], dis[1]);
    for (int i = 1; i <= tot; ++i) dis[2][i] = dis[0][i] + dis[1][i];
    dijkstra(0, dis[2], true); // 以 dis[0]+dis[1] 为初值再跑

    for (int i = 1; i <= n; ++i)
        cout << (dis[2][pos[i]] >= INF ? -1 : dis[2][pos[i]]) << '\n';
    return 0;
}
```

---

### 代码片段赏析（Benq 势能线段树核心）
> 亮点：利用“第一次松弛即永久删除区间”，实现 `O(N log N)`。

```cpp
// 线段树节点保存所有右端点 ≥ x 的票
struct SegTree {
    int n; vector<int> mx;
    void build(int sz) {
        n = 1; while (n < sz) n <<= 1;
        mx.assign(2 * n, -1);
    }
    void insert(int idx, int r) {
        for (int p = idx + n; p; p >>= 1) mx[p] = max(mx[p], r);
    }
    void remove(int x, vector<int>& res) {
        dfs(1, 0, n - 1, x, res);
    }
    void dfs(int p, int l, int r, int x, vector<int>& res) {
        if (mx[p] < x) return;
        if (l == r) { res.push_back(l); mx[p] = -1; return; }
        dfs(p << 1, l, (l + r) >> 1, x, res);
        dfs(p << 1 | 1, ((l + r) >> 1) + 1, r, x, res);
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
};
```
💡 学习笔记：势能线段树把“区间删除”转化为“单点删除”，从而把复杂度降到 `O(N log N)`。

---

## 5. 算法可视化：像素动画演示

### 主题
**“像素探险家”在三段 Dijkstra 迷宫中寻宝**

### 设计思路
- **8 位像素风**：用 16×16 像素方块表示节点、边、队列。  
- **颜色编码**：  
  - 起点 1 → 绿色宝石  
  - 终点 n → 红色旗帜  
  - 当前松弛节点 → 闪烁黄色  
- **音效**：  
  - 入队“叮”，松弛“咔哒”，到达终点“胜利音”。  
- **交互**：  
  - 步进/自动播放滑块  
  - 可切换“线段树视图”看区间连边压缩过程  

### 关键帧
1. **建图**：线段树节点逐层亮起，区间边像藤蔓一样生长。  
2. **第一次 Dijkstra**：绿色波纹从 1 扩散。  
3. **第二次 Dijkstra**：红色波纹从 n 扩散。  
4. **第三次 Dijkstra**：黄色节点把 `dis1+dis2` 作为能量，再次扩散。  
5. **结果**：每个节点上方显示最终金币数（-1 为骷髅）。

---

## 6. 拓展练习与相似问题思考

### 通用思路迁移
- **区间连边 + 最短路**：课程表选课、区间覆盖最小代价。  
- **重叠路径消除**：多源最短路、联合省选 2023 火车站。  

### 洛谷推荐
1. **P4779** [模板] 单源最短路径（标准版）  
   🗣️ 巩固 Dijkstra 模板，为线段树建图打基础。  
2. **P786B** Legacy  
   🗣️ 线段树优化建图入门题，区间向点连边模板。  
3. **P543B** Destroying Roads  
   🗣️ 重叠路径消除的经典题，三次最短路思路同源。  

---

## 7. 学习心得与经验分享

> **ETHANK 赛后总结**：  
> “第一次 WA 是因为把区间直接暴力连边，内存爆炸。后来意识到线段树可以把区间拆成 log 条边，才豁然开朗。”  
> **洛语云笺点评**：  
> 遇到区间连边时，先问自己：能否用数据结构压缩？  
> 遇到重叠路径时，先问自己：能否把 `dis1+dis2` 再跑一遍最短路？  
> 这两个“自问”能解决 80% 的区间图论题。

---

<conclusion>
今天我们从“区间连边”到“重叠路径”，从 `O(N·K)` 到 `O(N log N)`，完成了一次完整的算法探险。  
记住：线段树压缩区间，三次 Dijkstra 消除重叠——这两把钥匙，将帮你打开更多图论迷宫的大门！  
下次我们再一起挑战新的 USACO 难题！💪
</conclusion>

---
处理用时：101.81秒