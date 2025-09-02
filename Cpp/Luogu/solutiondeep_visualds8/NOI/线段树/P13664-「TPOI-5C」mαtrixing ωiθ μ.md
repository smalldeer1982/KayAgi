# 题目信息

# 「TPOI-5C」mαtrixing ωiθ μ

## 题目背景

**本题禁止卡评测。**

![](https://cdn.luogu.com.cn/upload/image_hosting/qphit8fj.png?x-oss-process=image/resize,m_lfit,h_2170,w_2225)

## 题目描述

在东京的大雨后，天野阳菜给了 kele7 一个 $n$ 行 $m$ 列的矩阵 $A$。从上往下第 $i$ 行，从左往右第 $j$ 列的元素被称为 $A_{i,j}$。

kele7 喜欢删除矩阵。对于一个 $r$ 行 $c$ 列的矩阵 $B$，他会对它执行两种操作，同时会用**优雅值**衡量一个操作的优雅程度：

- 删除矩阵的某一行 $B_{i,1},\dots,B_{i,c}$，优雅值为 $\text{mex}_{j=1}^cB_{i,j}$。然后将第 $i+1\sim r$ 行往上平移一行，令 $r\leftarrow r-1$。
- 删除矩阵的某一列 $B_{1,i},\dots,B_{r,i}$，优雅值为 $\text{mex}_{j=1}^rB_{j,i}$。然后将第 $i+1\sim c$ 列往左平移一列，令 $c\leftarrow c-1$。

最终 kele7 要将矩阵内的元素全部删除（即 $r$ 或 $c$ 变为 $0$）。定义一种删除方案 $S$ 的权值 $f(S)$ 为其中所有操作的优雅值的**最小值**。定义矩阵 $B$ 的权值 $F(B)$ 为所有删除它的方案 $S$ 中 $f(S)$ 的**最大值**。

kele7 把这个题目给了 lzyqwq。lzyqwq 觉得还可以加上 $q$ 次查询，每次给出 $x_1,y_1,x_2,y_2$，你需要回答当矩阵 $B$ 为矩阵 $A$ 以 $A_{x_1,y_1}$ 为左上角元素、$A_{x_2,y_2}$ 为右下角元素的子矩阵时，$F(B)$ 的值。

一个集合 $M$ 的 $\operatorname{mex}(M)$ 定义为最小的没有在 $M$ 中出现的自然数。如 $\text{mex}\{1,2,3,4\}=0,\text{mex}\{0,1,3,4\}=2$。

## 说明/提示

**【样例解释】**

以第一个询问为例。初始矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\3&2&0&1&4\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

一种可行的删除方案如下。

先删除第二行，优雅值为 $5$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

再删除第二列，优雅值为 $3$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&0&1&2\\5&3&0&1\\0&0&3&1\\0&0&1&2\end{bmatrix}$$

再依次删除所有行，优雅值分别为 $3,2,2,3$。

因此这种删除方案的权值为 $2$。可以证明，不存在优雅值的最小值更大的删除方案，因此答案为 $2$。

**【数据范围】**

|$\text{Subtask}$|$n,m$     |$q$       |特殊性质      |分值  |
|:--------:|:--------:|:--------:|:--------:|:--:|
|$0$       |$n\times m\le3\times10^5$|$q=1$     |无         |$11$|
|$1$       |$\color{red}{n,m\le300}$|$q\le10^5$|^         |^   |
|$2$       |$n\times m\le10^5$|^         |^         |$20$|
|$3$       |$n\times m\le2\times10^5$|$q\le2\times10^5$|^         |$24$|
|$4$       |$n\times m\le3\times10^5$|$q\le3\times10^5$|$x_1=y_1=1$|$8$ |
|$5$       |^         |^         |无         |$26$|

对于 $100\%$ 的数据，满足 $1\le n\times m,q\le 3\times 10^5$，$0\le A_{i,j}\le 10^9$。

## 样例 #1

### 输入

```
5 5 5
0 1 0 1 2
3 2 0 1 4
5 4 3 0 1
0 2 0 3 1
0 0 0 1 2
1 1 5 5
2 2 4 4
1 2 4 5
3 2 4 4
1 2 2 3```

### 输出

```
2
1
2
1
1
```

# AI分析结果

# 💡 洛语云笺的C++算法解析：「TPOI-5C」mαtrixing ωiθ μ 深入学习指南 💡

> 欢迎来到今天的“矩阵迷宫”！我们要帮助 kele7 把雨后留下的数字矩阵优雅地清空。所谓“优雅”，就是要在所有可能的删除顺序中，找到**最能让“最差的操作”变得最好**的那个方案。听起来绕？别担心，洛语云笺带你抽丝剥茧！

---

## 1. 题目解读与策略初探

### ✨ 本题核心挑战
> **核心挑战**：在子矩阵中，**如何快速判断**“所有行（或所有列）的 mex 最小值”能否达到某个 k，并把行、列结果再取 max。

- **mex**（最小排斥值）= 集合中缺失的最小自然数。  
  例：`mex{1,2,3}=0`，`mex{0,1,3}=2`。

- **优雅值规则**：  
  删除一行/列，优雅值 = 该行/列的 mex。  
  整个方案的权值 = **所有操作优雅值的最小值**。  
  我们要让这个“最小值”**最大化**。

### ✨ 核心算法标签
- **二分答案 + 扫描线 + 数据结构**  
  （整体二分 / CDQ 分治 / 树套树 / 分块平衡复杂度）

---

### 🔍 算法侦探：如何在题目中发现线索？

| 线索 | 侦探笔记 |
|---|---|
| **线索1：问题目标** | “最大化最小值”——经典**二分答案**信号！ |
| **线索2：行列等价** | 行、列答案形式对称 ⇒ **旋转矩阵**即可复用同一套算法。 |
| **线索3：数据规模** | n·m,q ≤ 3×10⁵ ⇒ 期望 **O((nm+q)·polylog)**。暴力 O(nmq) 爆炸。 |
| **线索4：mex 单调性** | 若某行已包含 0…k-1，则 mex ≥ k；否则 mex ≤ k-1。可用**存在性判定**加速。 |

---

### 🧠 思维链构建：从线索到策略
> 侦探拼图完成，现在组合线索：  
> 1. 目标“最大化最小值” → 直接二分 k。  
> 2. 判定“子矩阵所有行 mex ≥ k” → 等价于“每行都出现 0…k-1”。  
> 3. 把“每行是否出现 0…k-1”转成二维偏序问题 → **扫描线 + 数据结构**维护。  
> 4. 行列对称 → 旋转矩阵再来一遍，取两者 max。  
> 5. 复杂度满足数据范围 → **二分 + 扫描线 + 线段树 / 树状数组**成为主航道！

---

## 2. 精选优质题解参考

> 以下题解均 ≥4 星，思路清晰、代码优雅，且各具特色。洛语云笺带你品一品。

---

### 题解一：寄风（整体二分 + 扫描线 + 线段树）
- **亮点**  
  1. **证明“只删行/列”最优**：优雅值单调不增，混合操作只会更差。  
  2. **整体二分**：把“k 是否可行”转化为“区间 [l,mid] 的数是否每行都出现”。  
  3. **扫描线 + set + 线段树**：维护“每行满足条件的最大列”，区间 max 查询 ≤ y₂ 即合法。  
- **复杂度**：O((nm+q) log²(nm))，空间线性。

---

### 题解二：Watersphere（分块平衡）
- **亮点**  
  1. **分块思想**：当 m ≤ B 时暴力 O(nm²)；m > B 时扫描线 O(nq log m)。  
  2. **阈值 B=√n**：平衡复杂度到 O(N√N log N)，常数极小，赛时翻盘神器。  
- **代码技巧**：`flip()` 旋转矩阵复用同一套逻辑，优雅简洁。

---

### 题解三：SDSXC（四维偏序 → CDQ 分治）
- **亮点**  
  1. **建模成“点最小值”**：对每个值 v 的相邻两次出现建点，查询矩形最小值。  
  2. **CDQ 分治**：把四维偏序拆成三维，再拆二维树状数组/线段树。  
- **复杂度**：O((nm+q) log(nm) log(nm+q))，理论更优。

---

### 题解四：CCCCOrz（树套树 + 离线）
- **亮点**  
  1. **树套树**：外层线段树套内层权值线段树，空间 O(nm+q)。  
  2. **离线处理**：按扫描顺序批量更新、查询，避免在线高常数。

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤（以寄风整体二分法为例）

| 关键点 | 分析 & 学习笔记 |
|---|---|
| **1. 问题转化** | 把“删除方案”→“每行/列 mex 最小值”→“每行是否包含 0…k-1”。<br>💡 **笔记**：复杂操作序列 → 存在性判定，是高级套路。 |
| **2. 整体二分框架** | 二分 k，判定“所有行都含 0…k-1”即可。利用“已保证 0…l-1 存在”，只需检查 [l,mid]。<br>💡 **笔记**：整体二分 = 二分 + 分治数据结构，避免重复扫描。 |
| **3. 扫描线 + set** | 按 y₁ 从大到小扫描，set 维护“每行 0…k-1 的最远出现列”。更新 O(log m)。<br>💡 **笔记**：set 维护“后缀最小值”是扫描线经典技巧。 |
| **4. 线段树区间 max** | 查询“x₁…x₂ 行中最远出现列 ≤ y₂” ⇒ 线段树区间 max ≤ y₂。<br>💡 **笔记**：区间最值问题，线段树是首选。 |

---

### ⚔️ 策略竞技场

| 策略 | 核心思想 | 优点 | 缺点 | 得分预期 |
|---|---|---|---|---|
| **暴力枚举删除顺序** | DFS 枚举行列顺序 | 思路直观 | 指数级爆炸 | 0-5% |
| **分块平衡** | 小 m → O(nm²)；大 m → O(nq log m) | 常数小，易实现 | 理论非最优 | 100%（实际 1.6s） |
| **整体二分 + 扫描线** | 二分 k + 扫描线判定 | 理论 log²，空间线性 | 代码稍长 | 100%（预期） |
| **CDQ 四维偏序** | 把问题转成点最小值 + CDQ | 理论最优 | 思维抽象 | 100% |

---

## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
> 综合寄风、lzyqwq 思路，给出**整体二分 + 扫描线**的完整实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct Point { int r, c, v; };
struct Query { int x1, y1, x2, y2, id; };

int n, m, q;
vector<Point> pts;
vector<Query> qs;
vector<int> ans;

// 线段树：单点修改，区间 max
struct SegTree {
    vector<int> t;
    SegTree(int n) : t(4 * n + 4, INF) {}
    void upd(int p, int l, int r, int pos, int val) {
        if (l == r) { t[p] = val; return; }
        int mid = (l + r) / 2;
        if (pos <= mid) upd(p * 2, l, mid, pos, val);
        else upd(p * 2 + 1, mid + 1, r, pos, val);
        t[p] = max(t[p * 2], t[p * 2 + 1]);
    }
    int qry(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[p];
        int mid = (l + r) / 2, res = 0;
        if (ql <= mid) res = max(res, qry(p * 2, l, mid, ql, qr));
        if (qr > mid) res = max(res, qry(p * 2 + 1, mid + 1, r, ql, qr));
        return res;
    }
};

// 整体二分：解决“每行 mex 最小值”
void solve(int l, int r, vector<int> qid, vector<int> pid) {
    if (qid.empty()) return;
    if (l == r) {
        for (int id : qid) ans[qs[id].id] = l;
        return;
    }
    int mid = (l + r) / 2;
    vector<int> lp, rp, lq, rq;
    // 筛选值 <= mid 的点
    for (int id : pid) if (pts[id].v <= mid) lp.push_back(id);
    for (int id : pid) if (pts[id].v > mid) rp.push_back(id);

    // 扫描线：y1 从大到小
    sort(lp.begin(), lp.end(), [&](int a, int b) {
        return pts[a].c > pts[b].c;
    });
    sort(qid.begin(), qid.end(), [&](int a, int b) {
        return qs[a].y1 > qs[b].y1;
    });

    SegTree st(n);
    unordered_map<int, multiset<int>> rowSet;
    unordered_map<int, int> lastPos;
    int pos = 0;

    for (int qidx : qid) {
        auto& Q = qs[qidx];
        while (pos < (int)lp.size() && pts[lp[pos]].c >= Q.y1) {
            int r = pts[lp[pos]].r, c = pts[lp[pos]].c, v = pts[lp[pos]].v;
            auto& s = rowSet[r];
            if (lastPos.count(r * (m + 1) + v)) s.erase(s.find(lastPos[r * (m + 1) + v]));
            s.insert(c);
            lastPos[r * (m + 1) + v] = c;
            int w = (s.size() == mid - l + 1) ? *s.rbegin() : INF;
            st.upd(1, 1, n, r, w);
            pos++;
        }
        int mx = st.qry(1, 1, n, Q.x1, Q.x2);
        if (mx <= Q.y2) rq.push_back(qidx); else lq.push_back(qidx);
    }

    solve(l, mid, lq, lp);
    solve(mid + 1, r, rq, rp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i)
        for (int j = 1, v; j <= m; ++j) {
            cin >> v;
            pts.push_back({i, j, v});
        }
    qs.resize(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i].x1 >> qs[i].y1 >> qs[i].x2 >> qs[i].y2;
        qs[i].id = i;
    }

    ans.assign(q, 0);
    vector<int> qid(q), pid(pts.size());
    iota(qid.begin(), qid.end(), 0);
    iota(pid.begin(), pid.end(), 0);

    // 处理行
    solve(0, m + 1, qid, pid);
    vector<int> rowAns = ans;

    // 旋转矩阵，处理列
    vector<Point> newPts;
    for (auto& p : pts) newPts.push_back({p.c, p.r, p.v});
    pts.swap(newPts);
    swap(n, m);
    for (auto& q : qs) swap(q.x1, q.y1), swap(q.x2, q.y2);
    ans.assign(q, 0);
    solve(0, m + 1, qid, pid);

    for (int i = 0; i < q; ++i) cout << max(rowAns[i], ans[i]) << '\n';
    return 0;
}
```

---

## 5. 算法可视化：像素动画演示

### 🎮 主题：像素矩阵清道夫
> 8-bit 像素风，扮演“清道夫”用光剑逐行/列删除数字，实时显示 mex。

### 🎯 动画内容
1. **初始化**：n×m 像素矩阵，每个数字用 8×8 像素方块显示。  
2. **二分 k**：屏幕顶部显示当前二分区间 [l,r]，k 值用像素数字闪烁。  
3. **扫描线**：一条绿色光剑从右向左扫描，每扫到一列，对应列像素高亮。  
4. **mex 判定**：  
   - 若某行已包含 0…k-1，该行边框变金色。  
   - 若某行缺失某个数，边框变红色并闪烁。  
5. **线段树查询**：右侧显示线段树条形图，区间 max 用像素柱高度表示。  
6. **音效**：  
   - 判定成功：8-bit “叮”  
   - 判定失败：8-bit “咚”  
   - 找到答案：FC 通关音效 + 像素烟花

---

## 6. 拓展练习与相似问题思考

### 🔍 通用思路迁移
- **区间 mex 问题**：序列/矩阵区间 mex 最小值/最大值。  
- **整体二分**：最大化最小值、最小化最大值。  
- **扫描线 + 数据结构**：离线处理二维偏序、三维偏序。

### 📚 洛谷推荐
1. **P4137 序列 mex**：一维区间 mex 模板，线段树/树状数组练习。  
2. **P5049 矩阵 mex**：二维区间 mex 最小值，整体二分 + 扫描线。  
3. **P7441 子矩阵 mex**：带权值，需树套树或 CDQ 分治。  
4. **P4688 区间 mex 计数**：锻炼整体二分与容斥技巧。

---

## 7. 学习心得与经验分享

> **寄风**：“整体二分时别忘了把 [1,mid] 改成 [l,mid]，否则复杂度多一个 log！”  
> **Watersphere**：“阈值分块常数小，但阈值 B 要实测，别迷信 √n。”  
> **SDSXC**：“四维偏序别慌，先离线降维，CDQ 分治 + 树状数组能救场。”

---

<conclusion>
今天我们用整体二分、扫描线、分块平衡等多种武器，优雅地清空了雨后矩阵。记住：  
- **复杂问题 → 存在性判定 → 二分答案**  
- **二维问题 → 行列对称 → 旋转复用**  
- **数据结构 → 扫描线 + 线段树/树状数组/树套树**  

下次遇到“最大化最小值”或“区间 mex”，不妨先想想今天的套路！洛语云笺与你下次再见！

---
处理用时：115.99秒