# 题目信息

# 「VUSC」Math Game

## 题目背景

**upd 2023.1.22**：新增一组 Hack 数据 by @[MCRS_lizi](https://www.luogu.com.cn/user/585805)。

远在哞利坚的 Bessie 也要在新春之际走亲访友！为了打发时间，她常和 Farmer John 玩一个有趣的数字游戏。

## 题目描述

Farmer John 有一个集合 $S$，集合初始为 $\{2,3,4,...,N\}$。

对于两个**在集合 $S$ 内的**正整数 $p,q$，我们称它们为「一对好数」当且仅当 $p^k=q(k\ge 2\land k\in\N)$。

我们将每个 $S$ 中的数看成一张**无向图**中的节点，对于每一对「好数」，我们在这两个数间连一条无向边。

Farmer John 会进行 $Q$ 次操作，操作有以下两种：

1. 给出 $x$，询问结点 $x$ 所在的连通块大小。
2. 给出 $x$，从 $S$ 中移除 $x$。**与此同时，无向图中的结点 $x$ 也被移除。**

由于 Bessie 的速度太慢了，她想要你来帮忙。

## 说明/提示

#### 【样例解释】

这是原始无向图（上面一排都是孤点）：
![](https://cdn.luogu.com.cn/upload/image_hosting/utsz04dt.png)

这是进行第一次操作 $2$ 后的无向图（删除了结点 $9$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/wmexc9ks.png)

这是进行第二次操作 $2$ 后的无向图（删除了结点 $2$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/9mi0l18p.png)

---

#### 【数据范围】

全部数据满足：
- $2\le N \le 10^{18}$
- $1\le Q \le 10^6$
- $x_i\in S$
- $op_i \in \{1,2\}$

测试点 $1\sim2$ 另外满足 $2\le N \le 10^5$，$1\le Q \le 10^4$。

测试点 $3\sim4$ 另外满足所有 $x_i=m^{p_i}$，其中 $m$ 为一满足 $m\ge 2 \land m\in \N$ 的**常数**。

测试点 $5\sim10$ 没有额外限制。


## 样例 #1

### 输入

```
30 6
1 6
1 4
2 9
1 3
2 2
1 16```

### 输出

```
1
4
2
2```

# AI分析结果

# 💡 洛语云笺的C++算法解析：「VUSC」Math Game 深入学习指南 💡

> 各位少年探险家，欢迎来到今天的“数字连通图”实验室！  
> 我们的主角是一棵由指数关系编织的“幂次森林”：  
> 任意两数若满足 `p^k = q` 就牵手成为朋友。  
> 接下来，我们要在 10^18 的辽阔疆域里，一边删除节点，一边实时回答“某节点所在的连通块有多大”。  
> 准备好跟随洛语云笺，把这道“黄题”拆解成一场思维游戏了吗？

---

## 1. 题目解读与策略初探

✨ **本题核心挑战**  
“如何在 10^18 的超大值域、10^6 次操作下，动态维护幂次关系的连通块？”

✨ **核心算法标签**  
离散化 + 离线并查集 / 在线 `map` + 指数枚举

---

🗣️ **初步分析**  
1. 暴力建边 → 边数爆炸  
2. 暴力 DFS/BFS → 删除后需 O(siz) 更新，超时  
3. 观察“幂次”本质：  
   每个数可唯一表示为 `x = base^exp`（base 最小），  
   于是整棵森林被拆成若干条“base 链”，链内再按指数连边。  
4. 删除操作天然“逆序”友好 → 离线“时光倒流”成加点，并查集维护即可。

---

### 🔍 算法侦探：如何在题目中发现线索？

| 线索 | 侦探笔记 |
|---|---|
| **线索1 超大值域 10^18** | 离散化是唯一出路 |
| **线索2 幂次连边** | 把 `x` 拆成 `(base,exp)` 二元组，base 相同的数在同一棵“指数树” |
| **线索3 删除后查询** | 并查集支持“加边”易、“删边”难 → 离线逆序即可 |

### 🧠 思维链构建：从线索到策略

> 1. 值域大到无法存数组 → 离散化 `base`  
> 2. 指数关系天然成树 → 用 `(base,exp)` 作为并查集坐标  
> 3. 删除点 → 逆序加点，并查集合并 `exp` 与其倍数/因数  
> 4. 时间复杂度 O(Q log²N)，空间 O(Q log N)

---

## 2. 精选优质题解参考

| 题解 | 亮点提炼 |
|---|---|
| **enucai** | 在线做法，用 `map<ll,ll>` 存 `f(x)`，枚举 `base^k` 时直接 `set` 判删除，思路极简洁，但复杂度多一个 log |
| **STUDENT00** | 离线并查集模板 + 离散化 `(base,exp)` 双关键字，代码结构清晰，细节注释丰富，适合学习 |
| **Moeebius** | 出题人官方题解，离线 + 离散化 + 并查集，变量命名规范，把 0/1 下标转换细节讲透 |
| **xieziheng** | 在线思路，用 `__int128` 防溢出，`sqrtl` + 微调精度，代码短小精悍 |
| **MCRS_lizi** | 在线 + 预处理 `low[x]`（最小 base）+ 向上跳 base，卡常思路，适合练手 |

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤（最优离线并查集）

| 关键点 | 解析 | 学习笔记 |
|---|---|---|
| **离散化 base** | 把每个 `x` 拆成 `base^exp`，base 取最小，用 map 存 `(x → base,exp)`，再对 base 数组排序去重 | 离散化是处理超大值域的第一步 |
| **并查集坐标** | 二维：`fa[id][exp]`，`id` 为离散化后的 base 编号，`exp` 为指数 | 二维并查集常用套路 |
| **离线逆序** | 先标记所有被删点，逆序处理：遇到删除 → 变“加点”，把 `exp` 与 `k*exp` 合并，与 `exp/k`（整除）合并 | 并查集只能“加边”不能“删边” |
| **复杂度** | 每个数最多 log 个指数，合并次数 O(Q log N)，总复杂度 O(Q log²N) | 时限充裕，无需卡常 |

### ✨ 解题技巧总结

- **幂次拆分**：把数拆成 `(base,exp)`，base 最小，exp ≥ 1  
- **离线思想**：删除 → 逆序加点，避免并查集删边  
- **二维并查集**：`(id,exp)` 作为节点，合并倍数/因数指数  
- **精度处理**：`sqrtl` + 检查 ±1，或二分 + `__int128` 快速幂

### ⚔️ 策略竞技场

| 策略 | 思想 | 优点 | 缺点 | 适用/得分 |
|---|---|---|---|---|
| 在线枚举 + map | 实时枚举 `base^k`，用 set 判删除 | 无需离线 | 多一个 log，常数大 | 在线场景，吸氧可过 |
| 离线并查集 | 离散化后逆序加点 | 复杂度 O(Q log²N) | 实现细节多 | 官方做法，100% |
| 在线 + 向上跳 base | 预处理 `low[x]`，被删后向上找下一个 base | 思路直观 | 常数大，易写挂 | 练手/卡常 |

---

## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考（离线并查集版）

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e6 + 10;

ll n, num[MAXN];
int q, tot;
struct Q { int op; ll x; } qs[MAXN];
map<ll, pair<ll,int>> pool;     // x -> (base,exp)
set<ll> del;

// 并查集
int fa[MAXN][64], sz[MAXN][64];
int find(int id, int x) {
    return fa[id][x] == x ? x : fa[id][x] = find(id, fa[id][x]);
}
void unite(int id, int x, int y) {
    x = find(id, x), y = find(id, y);
    if (x != y) {
        fa[id][y] = x;
        sz[id][x] += sz[id][y];
    }
}

// 预处理 x = base^exp
void init() {
    for (ll i = 2; i * i * i <= n; ++i) {
        ll v = i;
        for (int e = 1; v <= n; v *= i, ++e)
            if (!pool.count(v)) pool[v] = {i, e};
    }
    for (auto &pr : pool) {
        ll x = pr.first;
        ll base = (ll)sqrtl(x);
        if (base * base == x && !pool.count(x))
            pool[x] = {base, 2};
    }
    // 离散化 base
    for (auto &pr : pool) num[++tot] = pr.second.first;
    sort(num + 1, num + tot + 1);
    tot = unique(num + 1, num + tot + 1) - num - 1;

    // 初始化并查集
    for (int i = 1; i <= tot; ++i) {
        ll base = num[i];
        int maxExp = logl(n) / logl(base) + 1;
        for (int e = 1; e <= maxExp; ++e) {
            fa[i][e] = e;
            sz[i][e] = del.find(pool[base*e].first) == del.end();
        }
        // 连边：e 与 k*e
        for (int e = 1; e <= maxExp / 2; ++e) {
            for (int k = 2; k * e <= maxExp; ++k)
                if (!del.count(pool[base*e].first) && !del.count(pool[base*k*e].first))
                    unite(i, e, k * e);
        }
    }
}

int ans[MAXN], acnt;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> qs[i].op >> qs[i].x;
        if (qs[i].op == 2) del.insert(qs[i].x);
        pool[qs[i].x] = {qs[i].x, 1};
    }
    init();

    // 离线逆序处理
    for (int i = q; i >= 1; --i) {
        ll x = qs[i].x;
        auto [base, exp] = pool[x];
        int id = lower_bound(num + 1, num + tot + 1, base) - num;
        if (qs[i].op == 1) {
            ans[++acnt] = sz[id][find(id, exp)];
        } else {
            del.erase(x);
            sz[id][exp] = 1;
            // 连倍数
            int maxExp = logl(n) / logl(base) + 1;
            for (int k = 2; k * exp <= maxExp; ++k)
                if (!del.count(pool[base*k*exp].first))
                    unite(id, exp, k * exp);
            // 连因数
            for (int k = 1; k < exp; ++k)
                if (exp % k == 0 && !del.count(pool[base*k].first))
                    unite(id, k, exp);
        }
    }
    for (int i = acnt; i >= 1; --i) cout << ans[i] << '\n';
    return 0;
}
```

---

## 5. 算法可视化：像素动画演示

**主题**：“像素探险家”在指数森林中寻找伙伴  
**核心算法**：离线并查集的“时光倒流”加点过程

| 场景 | 像素化表现 |
|---|---|
| **森林初始化** | 每棵 base 树用不同颜色方块垂直排列，exp 从小到大，高度=指数 |
| **删除标记** | 被删节点变灰色，闪烁 2 帧 |
| **逆序加点** | 灰色方块恢复颜色，并自动与上下相邻同色方块“握手”合并（并查集 unite） |
| **查询** | 高亮询问节点，连通块内所有方块同步闪烁 3 帧，显示当前大小 |
| **音效** | 合并时“叮”，查询时“嗒”，成功恢复时“胜利音” |
| **交互** | 步进/自动播放滑块，可暂停查看当前 base/exp 坐标与并查集父节点 |

---

## 6. 拓展练习与相似问题思考

**通用技巧迁移**  
离散化 + 离线并查集适用于：
1. 区间删点查询连通块  
2. 树上删边求连通块  
3. 动态图删边离线处理

**洛谷推荐**  
1. P1190 牛奶工厂（离散化 + 并查集）  
2. P1525 关押罪犯（二分 + 并查集）  
3. P1955 程序自动分析（离散化 + 并查集）  
4. P3367 并查集模板（巩固离线思想）

---

## 7. 学习心得与经验分享

> STUDENT00 的调试心得：  
> “变量命名要直观，二维并查集容易把 0/1 下标搞混，建议写注释标 `// 1-indexed`。”  
> 洛语云笺点评：命名 + 注释 = 后期维护的救命稻草！

---

<conclusion>
今天我们一起把“超大幂次森林”拆成了可管理的 `(base,exp)` 二维坐标，再用“时光倒流”让并查集重获新生。  
记住：离散化解决值域，离线化解决删边，二维并查集解决指数关系。  
下次遇到“动态图删点”类题目，不妨先想想能否离线逆序！  
探险结束，少年们，继续向下一座算法高峰进发吧！

---
处理用时：73.86秒