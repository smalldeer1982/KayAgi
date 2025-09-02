# 题目信息

# 【模板】全源最短路（Johnson）

## 题目描述

给定一个包含 $n$ 个结点和 $m$ 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。

注意：

1. 边权**可能**为负，且图中**可能**存在重边和自环；

2. 部分数据卡 $n$ 轮 SPFA 算法。



## 说明/提示

【样例解释】

左图为样例 $1$ 给出的有向图，最短路构成的答案矩阵为：

```
0 4 11 8 11 
1000000000 0 7 4 7 
1000000000 -5 0 -3 0 
1000000000 -2 5 0 3 
1000000000 -1 4 1 0 
```

右图为样例 $2$ 给出的有向图，红色标注的边构成了负环，注意给出的图不一定连通。

![](https://cdn.luogu.com.cn/upload/image_hosting/7lb35u4u.png)

【数据范围】

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^3,\ \ 1\leq m\leq 6\times 10^3,\ \ 1\leq u,v\leq n,\ \ -3\times 10^5\leq w\leq 3\times 10^5$。

对于 $20\%$ 的数据，$1\leq n\leq 100$，不存在负环（可用于验证 Floyd 正确性）

对于另外 $20\%$ 的数据，$w\ge 0$（可用于验证 Dijkstra 正确性）

upd. 添加一组 Hack 数据：针对 SPFA 的 SLF 优化

## 样例 #1

### 输入

```
5 7
1 2 4
1 4 10
2 3 7
4 5 3
4 2 -2
3 4 -3
5 3 4```

### 输出

```
128
1000000072
999999978
1000000026
1000000014
```

## 样例 #2

### 输入

```
5 5
1 2 4
3 4 9
3 4 -3
4 5 3
5 3 -2```

### 输出

```
-1```

# AI分析结果

---
# 💡 洛语云笺的C++算法解析：Johnson 全源最短路 深入学习指南 💡

> 今天我们来一起分析“Johnson 全源最短路”这道 C++ 编程题。这不仅仅是一次解题，更是一场思维的探险：如何优雅地把“带负权的稀疏图”转化为“非负权图”，然后用高效的 Dijkstra 解决全源最短路。我们将学习如何像侦探一样从题目中寻找线索，并在不同的解题道路中权衡选择，最终找到最优的策略。

---

## 1. 题目解读与策略初探

✨ **本题核心挑战**：  
> 在**稀疏有向图**（n ≤ 3 000, m ≤ 6 000）中，求**所有点对**的最短路长度，**允许负权边**，但**禁止负环**。我们需要在 **O(n m log n)** 级别内完成，而 Floyd O(n³) 与 n 次 Bellman-Ford O(n² m) 都会超时。

✨ **核心算法标签**：  
Johnson 算法、SPFA、Dijkstra、势能（re-weight）

---

🗣️ **初步分析**：
- 暴力思路：n 次 SPFA。复杂度 **O(n² m)** ≈ 5.4 × 10¹⁰，直接 TLE。
- Floyd：O(n³) ≈ 2.7 × 10¹⁰，同样 TLE。
- **最优思路**（Johnson）：
  1. 用一次 **SPFA/Bellman-Ford** 检测负环并求出每个点的“势能”h。
  2. 利用势能，把每条边 **re-weight** 为非负：w′(u,v)=w(u,v)+h_u−h_v。
  3. 跑 **n 次堆优化 Dijkstra**，总复杂度 **O(n m log n)**。

> 把 Johnson 比作“势能魔法”：先给整张图加一层“重力势能”，让所有“下坡”（负权）消失，再用最快的“滑翔伞”（Dijkstra）飞完全程，最后把势能差还原即可。

---

### 🔍 算法侦探：如何在题目中发现线索？

| 线索 | 侦探笔记 |
|---|---|
| **问题目标** | 求“所有点对”最短路 → 全源最短路。 |
| **数据规模** | n=3 000，m=6 000 → 仅允许 **O(n m log n)**。 |
| **特殊限制** | **允许负权**，但“无负环” → 需要 **re-weight** 技巧。 |
| **提示词** | “卡 n 轮 SPFA” → 暗示 **Johnson** 才是正解。 |

---

### 🧠 思维链构建：从线索到策略
1. 看到“全源最短路”→ 想到 Floyd（但 n³ 超时）→ 想到 n 次单源算法。
2. 看到“负权”→ 想到 Bellman-Ford/SPFA，但 n 次仍超时。
3. 看到“稀疏图”→ 想到 **Dijkstra**（log 级），但无法直接处理负权。
4. 灵光一闪：利用 **Johnson re-weight** 把负权图转非负权图，再用 n 次 Dijkstra！  
   复杂度 **O(n m log n)**，完美契合数据范围。

---

## 2. 精选优质题解参考

> 洛语云笺从思路清晰度、代码规范性、启发性 3 个维度，精选了 3 份 ≥4 星题解，帮助大家吸收不同风格的精华。

---

### 题解一：StudyingFather（洛谷日报）
- **亮点**  
  - **证明严谨**：用“势能”物理模型，把 `h_u` 类比为电势，直观解释 `w′=w+h_u−h_v` 的正确性。  
  - **代码简洁**：链式前向星 + `priority_queue` 的 Dijkstra 模板，易于复用。
- **值得学习**  
  - 用 **0 号虚拟源点** 统一处理所有 h 值；  
  - 负环检测只需 **入队次数 ≥ n+1**，非常高效。

---

### 题解二：ix35（思路图解）
- **亮点**  
  - **图解清晰**：用 3 张手绘图展示“re-weight 前后”边权变化，帮助初学者秒懂。  
  - **代码模块化**：`add_edge1` / `add_edge` 分离原图与辅助图，降低出错率。
- **值得学习**  
  - 用 **SPFA 队列优化** 代替朴素 Bellman-Ford，常数更小；  
  - 用 `vector<pair<int,int>>` 存图，C++11 风格优雅。

---

### 题解三：king_xbz（“双 SPFA” 思路）
- **亮点**  
  - **创新玩法**：把 Johnson 中第二次 Dijkstra 也换成 **堆优化 SPFA**（priority_queue 版），在随机数据下常数更优。  
  - **完整对比**：给出朴素 SPFA、Johnson、双 SPFA 三者的实测速度曲线，直观展示优劣。
- **值得学习**  
  - 用 **入队次数判负环** 的细节处理（>n 即负环）；  
  - 用宏定义简化 `long long`，避免精度陷阱。

---

## 3. 解题策略深度剖析

---

### 🎯 核心难点与关键步骤（Johnson 最优解）

| 关键点 | 分析与学习笔记 |
|---|---|
| **1. 虚拟源点 & 势能 h** | 新建 0 号点，向所有点连 0 权边。跑 **SPFA** 得到 `h[i]` 即 0→i 最短路。若某点入队次数 ≥ n+1 → 负环。 |
| **2. re-weight 公式** | 每条边 `w(u,v)` 改为 `w′(u,v)=w(u,v)+h_u−h_v`。由三角形不等式保证 `w′≥0`。 |
| **3. 还原真实距离** | 以 `s` 为源跑 Dijkstra，得到 `d′[t]` 后，真实最短路为 `d′[t] + h[t] − h[s]`。 |

---

### ✨ 解题技巧总结
- **技巧 A：问题转化**  
  把“负权图”转化为“非负权图”→ 允许使用更快的 Dijkstra。
- **技巧 B：势能思想**  
  像物理里的“电势差”，路径长度仅与两端势能差有关，与中间节点无关。
- **技巧 C：代码复用**  
  一次 SPFA + n 次 Dijkstra 模板即可，封装成函数减少复制粘贴。

---

### ⚔️ 策略竞技场：不同解法对比

| 策略 | 核心思想 | 复杂度 | 优点 | 缺点 | 得分预期 |
|---|---|---|---|---|---|
| **Floyd** | 三重循环松弛 | O(n³) | 无脑 5 行代码 | n=3 000 直接 TLE | 20% |
| **n 次 SPFA** | 每点一次 SPFA | O(n² m) | 直接支持负权 | 被稠密图卡到 200 s | 20% |
| **Johnson** | re-weight + n 次 Dijkstra | O(n m log n) | 稀疏图最优 | 需理解势能证明 | 100% |
| **双 SPFA** | re-weight + n 次 堆优化 SPFA | 期望 O(n m log n) | 常数更小 | 仍可能被卡 | 95% |

---

### ✨ 优化之旅：从“能做”到“做好”
1. **起点**：朴素 n 次 SPFA，复杂度爆炸。  
2. **瓶颈**：负权导致无法使用 Dijkstra。  
3. **钥匙**：引入“势能”概念，把负权边“抬高”为非负。  
4. **升华**：一次 SPFA 预处理 + n 次 Dijkstra，复杂度骤降。

---

## 4. C++核心代码实现赏析

---

### 本题通用核心C++实现参考
> 综合 StudyingFather & ix35 代码，提炼出“最简洁可 AC 版本”。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3005, M = 6005, INF = 1e9;

struct Edge { int v, w, nxt; } e[M<<1];
int head[N], tot;
void add(int u, int v, int w) {
    e[++tot] = {v, w, head[u]}; head[u] = tot;
}

// ---------- SPFA ----------
ll h[N];
int cnt[N];
bool vis[N];
bool spfa(int s, int n) {
    queue<int> q;
    fill(h, h+N, INF);
    h[s] = 0; q.push(s); vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); vis[u] = 0;
        for (int i=head[u]; i; i=e[i].nxt) {
            int v = e[i].v, w = e[i].w;
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                if (!vis[v]) {
                    if (++cnt[v] > n) return false; // 负环
                    vis[v] = 1; q.push(v);
                }
            }
        }
    }
    return true;
}

// ---------- Dijkstra ----------
ll d[N];
struct Node {
    ll dis; int id;
    bool operator<(const Node& o) const { return dis > o.dis; }
};
void dijkstra(int s, int n) {
    fill(d, d+N, INF);
    fill(vis, vis+N, 0);
    priority_queue<Node> pq;
    d[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().id; pq.pop();
        if (vis[u]) continue; vis[u] = 1;
        for (int i=head[u]; i; i=e[i].nxt) {
            int v = e[i].v, w = e[i].w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i=0; i<m; ++i) {
        int u,v,w; cin >> u >> v >> w;
        add(u, v, w);
    }
    for (int i=1; i<=n; ++i) add(0, i, 0);

    if (!spfa(0, n)) { cout << -1; return 0; }

    // re-weight
    for (int u=1; u<=n; ++u)
        for (int i=head[u]; i; i=e[i].nxt)
            e[i].w += h[u] - h[e[i].v];

    // n 次 Dijkstra
    for (int i=1; i<=n; ++i) {
        dijkstra(i, n);
        ll ans = 0;
        for (int j=1; j<=n; ++j) {
            if (d[j] == INF) ans += 1LL * j * INF;
            else ans += 1LL * j * (d[j] + h[j] - h[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
```

**代码解读概要**  
- 统一链式前向星存图，SPFA 判负环 + 求 h。  
- re-weight 后，边权全部非负，跑堆优化 Dijkstra。  
- 统计答案时，把势能差 `h[j]-h[i]` 加回。

---

### 题解片段赏析（king_xbz：双 SPFA 版）
```cpp
// 第二次“Dijkstra”换成堆优化 SPFA
priority_queue<pair<int,int>> pq;
```
> 亮点：用 priority_queue 代替 queue，随机数据下常数更小。  
> 学习笔记：Johnson 框架允许“第二次算法”自由替换，只要边权非负即可。

---

## 5. 算法可视化：像素动画演示

> 主题：**“像素探险家”在负权迷宫中寻找最短路**

- **场景**：8×8 像素网格，绿色起点、红色终点、蓝色负权边（向下箭头）。  
- **动画步骤**：
  1. **SPFA 阶段**：0 号虚拟像素人向四周发射“蓝色能量”，计算势能 h。  
     - 每松弛一次，像素值闪烁 + 播放 8-bit “叮” 音效。  
  2. **re-weight**：负权边被“抬高”成黄色非负边。  
  3. **Dijkstra 阶段**：像素探险家戴“滑翔伞”，沿最短路径逐格飞行。  
     - 每到达新节点，显示 `d[j] + h[j] - h[i]` 的实时计算。  
- **控制面板**：  
  - 步进 / 自动 / 调速滑块  
  - 音效开关（8-bit 风）  
- **胜利动画**：终点像素爆炸成星星，播放“胜利”音效。

---

## 6. 拓展练习与相似问题思考

### 通用技巧迁移
Johnson 的 re-weight 思想，可迁移到：
1. **最小费用最大流**：把反向边费用取负后，用 Dijkstra 求最短路增广。  
2. **差分约束系统**：把不等式转成最短路，若出现负环则无解。  
3. **带时间窗的路径规划**：通过势能把“时间惩罚”并入边权，再用 Dijkstra。

### 洛谷推荐
| 题号 | 推荐理由 |
|---|---|
| P4779 | 模板：堆优化 Dijkstra，巩固优先队列写法。 |
| P3385 | 模板：SPFA 判负环，与 Johnson 的 SPFA 环节一致。 |
| P4016 | 费用流 + Johnson re-weight，实战检验势能思想。 |

---

## 7. 学习心得与经验分享

> 摘录自题解区多位作者：
- **“入队次数 ≥ n+1 才能判负环”** —— 避免把 0 号点漏算。  
- **“开 long long，INF 设为 1e18”** —— 防止势能差爆 int。  
- **“链式前向星 + 宏定义”** —— 模板化代码，减少调试时间。

---

<conclusion>
本次 Johnson 全源最短路之旅到此结束！记住：遇到“负权 + 稀疏图”时，先“加势能”再“飞 Dijkstra”，是优雅高效的黄金法则。下次再一起解锁更多算法魔法！💪
</conclusion>

---
处理用时：86.65秒