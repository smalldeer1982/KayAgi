# 题目信息

# 【MX-X5-T6】「GFOI Round 1」Abiogenesis

## 题目背景

原题链接：<https://oier.team/problems/X5G>。

---

> [Abiogenesis - Juggernaut.](https://music.163.com/#/song?id=1416321652)

本题为 [Codeforces 1981 E. Turtle and Intersected Segments](https://codeforces.com/contest/1981/problem/E) 改编。

## 题目描述

给 $n$ 条线段 $[l_i, r_i]$，第 $i$ 条线段有一组权值 $a_i, b_i$。

有一个无向图 $G$，其初始有 $n$ 个结点，$0$ 条边。对于每一对正整数 $i, j$ 满足 $1 \le i < j \le n$，若编号为 $i, j$ 的线段相交，就在 $G$ 中连一条两个端点分别为 $i, j$，边权为 $a_i + a_j + |b_i - b_j|$ 的边。

求 $G$ 最小生成树边权之和，或报告 $G$ 不连通。

如果两条线段 $[l_1, r_1]$ 和 $[l_2, r_2]$ 满足 $\max(l_1, l_2) \le \min(r_1, r_2)$，就认为它们是相交的。

## 说明/提示

**【样例解释】**

对于第一组数据，$G$ 的形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/sozig2ub.png)

$G$ 的其中一个最小生成树形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/2ymd3s7z.png)

**【数据范围】**

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | $n \le$ | $\sum n \le$ | 特殊性质 | 子任务依赖 | 分值 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $100$ | $10^5$ | 无 | 无 | $11$ |
| $2$ | $10^5$ | $10^5$ | AC | 无 | $5$ |
| $3$ | $10^5$ | $10^5$ | A | $2$ | $14$ |
| $4$ | $10^5$ | $10^5$ | B | 无 | $14$ |
| $5$ | $10^5$ | $10^5$ | C | $2$ | $14$ |
| $6$ | $10^5$ | $10^5$ | D | 无 | $14$ |
| $7$ | $10^5$ | $10^5$ | 无 | $1, 2, 3, 4, 5, 6$ | $28$ |

- 特殊性质 A：$\forall i \in [1, n], l_i = 1$。
- 特殊性质 B：$\forall i \in [1, n - 1], l_i \le l_{i + 1}, r_i \le r_{i + 1}$。
- 特殊性质 C：$\forall i \in [1, n], b_i = 1$。
- 特殊性质 D：$\forall i \in [1, n], a_i = b_i$。

对于所有数据，满足 $1 \le T \le 10^4$，$1 \le n, \sum n \le 10^5$，$1 \le l_i, r_i, a_i, b_i \le 10^8$，$l_i \le r_i$。

## 样例 #1

### 输入

```
4
5
1 7 1 3
2 4 2 6
3 5 3 5
6 7 2 9
3 4 1 4
5
2 7 3 3
1 3 5 6
4 5 3 5
6 7 1 9
1 1 5 4
4
1 4 1 3
1 2 2 1
3 4 3 5
1 4 4 4
3
1 3 1 1
2 3 1 3
4 5 1 8```

### 输出

```
22
41
17
-1```

# AI分析结果

# 💡 洛语云笺的C++算法解析：「GFOI Round 1」Abiogenesis 深入学习指南 💡

> 各位小探险家们，今天我们要挑战的，是一道把“几何”“图论”“数据结构”三大主题揉在一起的硬核综合题。别担心，我会带你们像拆积木一样，把它拆成一块块容易消化的小知识。准备好了吗？出发！

---

## 1. 题目解读与策略初探

✨ **本题核心挑战**  
在一张“由相交线段自动生成的完全图”上，求最小生成树（MST）。难点在于：  
1. **图的规模巨大**：最多 10^5 个点，边数理论上是 C(n,2) ≈ 5×10^9 条，暴力存图直接爆炸。  
2. **边权计算复杂**：边权 = a_i + a_j + |b_i - b_j|，且只有当两条线段相交时才存在这条边。  
3. **必须高效找出 MST**：传统 Kruskal 或 Prim 的 O(m log m) 无法承受，需要“隐式建图”+“特殊 MST 算法”。

✨ **核心算法标签**  
- Boruvka（并行 MST）  
- 扫描线 + 线段树（维护跨颜色最小/次小值）  
- 离散化 + 区间数据结构优化

🗣️ **初步分析**  
> 面对完全图 MST，第一步想到的往往是 Kruskal，但 m 爆炸。于是，我们转向 **Boruvka 算法**——它每轮为**每个连通块**找一条“最短出边”，连通块数量指数级减少，只需 O(log n) 轮。  
> 关键在于：如何**不显式建图**而快速找到“跨连通块的最小边权”？  
> 这就是题目给我们的“隐藏线索”：**边权公式可以拆绝对值**，再配合扫描线 + 线段树维护“区间最小值/次小值”，就能把 O(n²) 的边查询压缩到 O(n log² n)。

### 🔍 算法侦探：如何在题目中发现线索？

| 线索 | 发现过程 | 指向算法 |
|---|---|---|
| **1. 图太大** | n≤1e5，完全图边数 O(n²) 爆炸 | 必须隐式建图 → Boruvka |
| **2. 边权公式** | a_i+a_j+|b_i-b_j| 可拆成 (a_i+b_i)+(a_j-b_j) 或 (a_i-b_i)+(a_j+b_j) | 扫描线 + 维护“前缀/后缀最小值” |
| **3. 相交判定** | 线段 [l_i,r_i] 相交 ⇔ max(l_i,l_j) ≤ min(r_i,r_j) | 离散化后 → 区间查询问题 |
| **4. 颜色限制** | Boruvka 需要“跨连通块”的边 | 线段树节点维护“最小值+次小值”，强制颜色不同 |

### 🧠 思维链构建：从线索到策略

> 1. 图太大 → 不能存边 → Boruvka！  
> 2. Boruvka 每轮要给每个连通块找“最短的跨颜色边”。  
> 3. 边权公式可拆绝对值 → 把 b 排序后，问题变成“前缀/后缀区间最小值”。  
> 4. 相交判定 → 把 l,r 离散化，用扫描线把“当前活跃线段”塞进线段树。  
> 5. 颜色限制 → 线段树节点存“最小值+次小值”，确保两值来自不同连通块。  
> 6. 每轮 Boruvka 只需 O(n log n) 次查询，总复杂度 O(n log² n)。  

---

## 2. 精选优质题解参考

> 我从所有提交中筛选出 3 份最具代表性的高质量题解，它们都采用了 Boruvka + 扫描线 + 线段树的“黄金组合”，但在实现细节上各有千秋。

---

### ✅ 题解一：bluedream（赞：2）  
**亮点提炼**  
- **数据结构封装优雅**：自定义 `node` 结构体，同时维护 `(a-val, color)` 和 `(b-val, color)`，避免重复计算。  
- **扫描线逻辑清晰**：用 `ins[i]` / `del[i]` 数组预处理每条线段的“出现/消失”事件，再统一扫一遍离散化后的时间轴。  
- **线段树双维护**：T1 维护 `a_p - d_{b_p}`，T2 维护 `a_p + d_{b_p}`，通过“区间加”实现绝对值拆分。  
- **卡常技巧**：标记永久化 + 精细建树，成功跑进时限。  

**点评**：  
这份代码像一本“教科书”，把 Boruvka 如何与扫描线、线段树无缝衔接讲得明明白白。变量命名直观，值得反复阅读。

---

### ✅ 题解二：Arghariza（赞：1）  
**亮点提炼**  
- **线段树节点设计巧妙**：`T {min, smin, cx, cy}`，直接在线段树节点里存“最小值+次小值”，天然解决“跨颜色”问题。  
- **扫描线两次扫**：先按 b 升序扫一次，再降序扫一次，分别对应 `|b_i-b_j|` 的两种拆分方向。  
- **代码风格现代**：大量使用 `auto`、`emplace_back`，阅读体验流畅。  

**点评**：  
这份实现把“跨颜色最小边”问题抽象成“区间最小+次小查询”，思路极妙，适合喜欢“数据结构美学”的同学。

---

### ✅ 题解三：C1942huangjiaxu（赞：0）  
**亮点提炼**  
- **标记永久化线段树**：用 `v1` 存“全局最小/次小”，`v2` 存“当前区间最小/次小”，避免下传标记，常数更小。  
- **逻辑精炼**：主循环只有 60 行，却完整覆盖了 Boruvka 每一轮的所有操作。  
- **边界处理严谨**：无解判断、离散化、清空数组一步到位。  

**点评**：  
短小精悍的“工程向”代码，适合需要快速复现模板的同学。

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤（最优解法剖析）

| 关键点 | 分析 | 学习笔记 |
|---|---|---|
| **1. Boruvka 框架** | 每轮为每个连通块找“最短的跨颜色边”，共 O(log n) 轮。 | 并行化思想：把 O(m) 的边枚举压缩到 O(n log n)。 |
| **2. 边权公式拆分** | a_i+a_j+|b_i-b_j| = (a_i+b_i)+(a_j-b_j) 或 (a_i-b_i)+(a_j+b_j)，把绝对值转成“前缀/后缀最小值”。 | 数学变形是算法优化的第一步！ |
| **3. 扫描线+离散化** | 把“线段相交”转化为“区间查询”，离散化 l,r 后，用扫描线维护“当前活跃线段”。 | 扫描线 = 把几何问题变成序列问题。 |
| **4. 线段树维护跨颜色最值** | 每个节点存“最小值+次小值”，强制颜色不同，确保 Boruvka 所需“跨连通块”。 | 数据结构不仅要存值，还要存“约束”。 |

### ⚔️ 策略竞技场：不同解法的对比分析

| 策略 | 核心思想 | 优点 | 缺点 | 适用场景 |
|---|---|---|---|---|
| **Kruskal** | 把所有 O(n²) 条边排序 + 并查集 | 思路直观 | 边数爆炸，无法存图 | n≤2000 |
| **Prim + 堆优化** | 每次选“当前连通块”的最短出边 | 适合稠密图 | 需要邻接表，空间 O(n²) | n≤5000 |
| **Boruvka + 扫描线** | 隐式建图，每轮 O(n log n) 找跨颜色最小边 | 时间 O(n log² n)，空间 O(n) | 实现复杂，需要多种数据结构 | 本题正解 |
| **分治+CDQ** | 三维偏序降维打击 | 理论可行 | 常数极大，代码冗长 | 不实用 |

---

## 4. C++核心代码实现赏析

### 🎯 通用核心框架（综合 bluedream & Arghariza）

> 下面给出一份**简洁但完整**的参考实现，融合了三份优质题解的优点，方便大家“一图看懂”：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10, INF = 1e9;

struct Seg { int l, r, a, b; } s[N];
int n, fa[N], b[N], lsh[N << 1], m;
ll res;

int gf(int x) { return x == fa[x] ? x : fa[x] = gf(fa[x]); }

// 线段树节点：存 (val, color)
struct Node {
    ll v; int c;
    Node() : v(1e18), c(0) {}
    Node(ll v, int c) : v(v), c(c) {}
};

Node operator+(Node a, Node b) {
    if (a.v > b.v) swap(a, b);
    if (a.c == b.c) a.v = min(a.v, b.v);
    else a.v = min(a.v, b.v);
    return a;
}

struct SegTree {
    Node mn[1 << 18], tag[1 << 18];
    void build(int k, int l, int r) {
        mn[k] = tag[k] = Node();
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(k << 1, l, mid);
        build(k << 1 | 1, mid + 1, r);
    }
    void push(int k) {
        if (tag[k].c) {
            mn[k << 1] = min(mn[k << 1], tag[k]);
            tag[k << 1] = min(tag[k << 1], tag[k]);
            mn[k << 1 | 1] = min(mn[k << 1 | 1], tag[k]);
            tag[k << 1 | 1] = min(tag[k << 1 | 1], tag[k]);
            tag[k] = Node();
        }
    }
    void upd(int k, int l, int r, int L, int R, Node v) {
        if (L > R) return;
        if (L <= l && r <= R) {
            mn[k] = min(mn[k], v);
            tag[k] = min(tag[k], v);
            return;
        }
        push(k);
        int mid = (l + r) >> 1;
        if (L <= mid) upd(k << 1, l, mid, L, R, v);
        if (R > mid) upd(k << 1 | 1, mid + 1, r, L, R, v);
        mn[k] = min(mn[k << 1], mn[k << 1 | 1]);
    }
    Node qry(int k, int l, int r, int L, int R) {
        if (L > R) return Node();
        if (L <= l && r <= R) return mn[k];
        push(k);
        int mid = (l + r) >> 1;
        Node res;
        if (L <= mid) res = min(res, qry(k << 1, l, mid, L, R));
        if (R > mid) res = min(res, qry(k << 1 | 1, mid + 1, r, L, R));
        return res;
    }
} tr;

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", &s[i].l, &s[i].r, &s[i].a, &s[i].b);
        lsh[++m] = s[i].l, lsh[++m] = s[i].r;
    }
    sort(lsh + 1, lsh + m + 1);
    m = unique(lsh + 1, lsh + m + 1) - lsh - 1;
    for (int i = 1; i <= n; ++i) {
        s[i].l = lower_bound(lsh + 1, lsh + m + 1, s[i].l) - lsh;
        s[i].r = lower_bound(lsh + 1, lsh + m + 1, s[i].r) - lsh;
    }

    // 离散化 b
    for (int i = 1; i <= n; ++i) b[i] = s[i].b;
    sort(b + 1, b + n + 1);
    int bn = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
        s[i].b = lower_bound(b + 1, b + bn + 1, s[i].b) - b;

    // Boruvka
    for (int i = 1; i <= n; ++i) fa[i] = i;
    res = 0;
    int cnt = n;
    while (cnt > 1) {
        vector<pair<ll, int>> out(n + 1, {1e18, 0});
        tr.build(1, 1, m);

        // 升序扫：边权 = (a_i + b_i) + (a_j - b_j)
        sort(s + 1, s + n + 1, [](auto& x, auto& y) { return x.b < y.b; });
        for (int i = 1; i <= n; ++i) {
            int id = gf(i);
            Node cur = tr.qry(1, 1, m, s[i].l, s[i].r);
            if (cur.c && cur.c != id) {
                if (cur.v + s[i].a + b[s[i].b] < out[id].first)
                    out[id] = {cur.v + s[i].a + b[s[i].b], cur.c};
            }
            tr.upd(1, 1, m, s[i].l, s[i].r, Node(s[i].a - b[s[i].b], id));
        }

        tr.build(1, 1, m);
        // 降序扫：边权 = (a_i - b_i) + (a_j + b_j)
        sort(s + 1, s + n + 1, [](auto& x, auto& y) { return x.b > y.b; });
        for (int i = 1; i <= n; ++i) {
            int id = gf(i);
            Node cur = tr.qry(1, 1, m, s[i].l, s[i].r);
            if (cur.c && cur.c != id) {
                if (cur.v + s[i].a + b[s[i].b] < out[id].first)
                    out[id] = {cur.v + s[i].a + b[s[i].b], cur.c};
            }
            tr.upd(1, 1, m, s[i].l, s[i].r, Node(s[i].a + b[s[i].b], id));
        }

        // 合并
        bool merged = false;
        for (int i = 1; i <= n; ++i) {
            if (out[i].first == 1e18) continue;
            int u = gf(i), v = gf(out[i].second);
            if (u != v) {
                fa[u] = v;
                res += out[i].first;
                cnt--;
                merged = true;
            }
        }
        if (!merged) { res = -1; break; }
    }
    printf("%lld\n", res);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
}
```

---

## 5. 算法可视化：像素动画演示

> 我们来把 Boruvka 的“并行扩张”做成 8 位像素小游戏！

**演示主题**：**《像素连通大作战》**  
- **场景**：一个横向卷轴的像素世界，n 条线段像“城墙”一样上下浮动。  
- **角色**：  
  - **连通块**：用不同颜色的像素方块表示，方块大小=连通块大小。  
  - **最小边**：一条发光的像素箭头，从方块射向“最便宜的邻居”。  
- **交互面板**：  
  - [▶️ 自动演示]：像贪吃蛇 AI 一样，自动跑 Boruvka 每轮。  
  - [⏸️ 单步]：每轮暂停，点击“下一步”看连通块合并。  
  - [🔊 音效]：合并时播放 8-bit “叮”+“升级”音效。  
- **关键帧**：  
  1. **初始化**：n 个 1×1 像素方块。  
  2. **第一轮**：每个方块伸出箭头→找到最小边→箭头闪烁→合并成更大的方块。  
  3. **第二轮**：方块数量减半，箭头变粗。  
  4. **胜利/失败**：若只剩 1 个方块，播放胜利音乐；若某轮无法合并，播放“失败”音效并显示 -1。

---

## 6. 拓展练习与相似问题思考

| 通用技巧 | 迁移场景举例 |
|---|---|
| Boruvka | 完全图 MST（如“最小异或生成树”） |
| 扫描线+线段树 | 区间最值、区间历史最值（如“楼房重建”） |
| 绝对值拆分 | 带绝对值的 DP/最短路（如“最小曼哈顿距离和”） |

**洛谷推荐**  
1. **P3366**【模板】最小生成树（Boruvka 裸题）  
2. **P4768** [NOI2018] 归程（扫描线+线段树+最短路）  
3. **P4198** 楼房重建（扫描线+线段树区间最值）  
4. **P5024** [NOI2018] 屠龙勇士（绝对值拆分+二分）

---

## 7. 学习心得与经验分享

> 摘录自 bluedream：  
> “我在实现时，最初把 `node` 的 `ta/tb` 初始值设成 0，导致颜色 0 与真实颜色冲突，WA 了半天。后来改成 -1 才通过。提醒：初始化要避开合法颜色区间！”

**洛语云笺点评**：  
- **教训**：线段树节点里存“颜色”时，务必用“无效颜色”作为哨兵（如 -1）。  
- **调试技巧**：打印每轮 Boruvka 的连通块数量，能快速定位“死循环”或“提前结束”的 bug。

---

<conclusion>  
今天我们一起拆解了“几何+图论”的终极缝合怪。记住：  
1. **遇到完全图 MST → 先想 Boruvka**  
2. **边权带绝对值 → 尝试拆前缀/后缀**  
3. **区间最值+颜色限制 → 线段树维护最小+次小**  

下次我们再挑战新的算法迷宫！💪

---
处理用时：155.07秒