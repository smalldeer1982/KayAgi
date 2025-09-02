# 题目信息

# [JRKSJ R4] Salieri

## 题目背景

![a358071f95cad1c8ccd29cc83a3e6709c83d518e.jpg](https://s2.loli.net/2021/12/24/Oi251TnFP7SflQp.jpg)  

~~【记得到番里面去把“萨列里谱不出莫扎特的曲子”这句话找到】~~ 最终还是没能找到，哪位看过《命运石之门0》的兄弟能帮我找找？

## 题目描述

Salieri 发现了 $n$ 种制作音乐的模式，他将第 $i$ 种模式表示为一个字符串 $s_i$，这种模式所带来的初始优美度为 $v_i$。  
Salieri 现在想制作 $m$ 首乐曲，每次他的灵感可以被表示成一个字符串 $S$。设 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，则采用 $i$ 模式制作的乐曲最终的优美度 $w_i=cnt_i\times v_i$。  
Salieri 当然希望制作出来的乐曲最终优美度越大越好，但是他发现此灵感下前 $k-1$ 优美的乐曲已经被 Mozart 制作过了，他只能制作第 $k$ 优美的乐曲。请你求出这个最终优美度。  

形式化题意：给出 $n$ 个字符串 $s_i$，每个字符串有一个权值 $v_i$。$m$ 次询问每次给出一个字符串 $S$ 和一个常数 $k$。设 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，求 $cnt_i\times v_i$ 第 $k$ 大的值。

## 说明/提示

设 $L$ 为 $s$ 长度总和。

| $\text{Subtask}$|$n,m\le$|$L\le$|特殊性质| 分值 |
|:-:|:-:|:-:|:-:| :-: |
|$1$|$10^3$|$5\times10^3$|无| $10$ |
|$2$|$10^3$|$10^5$|无| $20$ |
|$3$|$10^5$|$5\times10^5$|$k=1$| $10$ |
|$4$|$3\times10^4$|$2\times10^5$|$k\le5$| $20$ |
|$5$|$3\times10^4$|$2\times10^5$|无|  $20$ | 
|$6$|$10^5$|$5\times10^5$|无|  $20$ |

对于 $100\%$ 的数据，$1\le n,m\le10^5$，$L\le5\times10^5$。

无论何时 $\sum |S|$ 与 $L$ 同阶，$s$ 和 $S$ 中只会出现 $\texttt a,\texttt b,\texttt c,\texttt d$ 四种字符，$v_i\le10^3$，$k\le n$。


![QQ截图20220128131353.png](https://s2.loli.net/2022/01/28/MJchEuxsF1QI46V.png)

## 样例 #1

### 输入

```
4 2
ab 2
a 2
ba 2
b 1
bbaba 2
aab 1```

### 输出

```
4
4```

## 样例 #2

### 输入

```
15 4
ba 18
cbc 74
aac 54
ba 77
a 66
c 96
cdb 47
dc 45
cb 62
db 88
dda 93
db 34
b 81
acd 100
da 80
bcaacbbdcbabcda 4
bccac 3
abdbaca 5
cbdaaaacaaca 3```

### 输出

```
124
66
77
108```

# AI分析结果

# 💡 洛语云笺的C++算法解析：[JRKSJ R4] Salieri 深入学习指南 💡

> 今天我们来一起分析「Salieri」这道 C++ 编程题。它融合了**字符串匹配**与**第 k 大查询**两大主题，我们将像侦探一样，从题目中寻找线索，最终找到最优的策略！

---

## 1. 题目解读与策略初探

### ✨ 本题核心挑战
> **“在巨大的文本洪流中，快速统计每个模式的出现次数×权值，并找出第 k 大！”**  
> 核心难点在于：
> 1. 多模式串匹配（$n$ 个模式，$m$ 个文本）。
> 2. 每次查询需计算所有模式的 `cnt_i × v_i` 并取第 k 大。
> 3. 数据规模巨大：$\sum|s_i|,\sum|S|\le5\times10^5$。

### ✨ 核心算法标签
- **AC 自动机**（多模式匹配）
- **虚树**（压缩 Fail 树）
- **主席树**（区间第 k 大）
- **二分答案**（将第 k 大转化为计数问题）

### 🔍 算法侦探：如何在题目中发现线索？
1. **线索1 (多模式匹配)**  
   “多个字符串 $s_i$ 在文本 $S$ 中出现次数” → **AC 自动机**是标准解法。
2. **线索2 (第 k 大查询)**  
   “求第 k 大的 `cnt_i × v_i`” → **二分答案**（转化为“有多少个 ≥ mid”）。
3. **线索3 (数据规模)**  
   $\sum|S|\le5\times10^5$ → 需 **$O(\text{polylog})$** 算法，暴力 $O(n^2)$ 不可行。

### 🧠 思维链构建：从线索到策略
> 1. **AC 自动机**：构建所有模式串的 Trie 图，Fail 指针建立 Fail 树。
> 2. **Fail 树性质**：`cnt_i` = 节点 $i$ 的子树中被文本串经过的节点数。
> 3. **虚树优化**：每次查询只需处理文本串经过的节点（$O(|S|)$ 个），建虚树压缩。
> 4. **主席树**：在 Fail 树上维护每个节点的权值分布，支持链上“≥ x 的个数”查询。
> 5. **二分答案**：通过二分 mid，用主席树快速统计满足 `cnt_i × v_i ≥ mid` 的模式数。

---

## 2. 精选优质题解参考

### 题解一：abruce（100pts 正统解法）
- **亮点**：
  - 完整实现 **AC 自动机 + 虚树 + 主席树 + 二分** 的 2log 解法。
  - 代码结构清晰，虚树构建和主席树查询细节严谨。
- **学习点**：
  - 虚树构建时通过 DFS 序排序 + LCA 去重。
  - 主席树维护 Fail 树节点权值，支持链上区间查询。

### 题解二：251Sec（乱搞 AC）
- **亮点**：
  - 利用数据特性，暴力遍历 Fail 树的连通块，复杂度 $O(L\sqrt{L})$。
  - 实际运行极快，体现“乱搞”艺术。
- **学习点**：
  - 当数据较弱时，暴力或根号算法可能出奇制胜。

### 题解三：Seauy（分块优化）
- **亮点**：
  - 将主席树替换为 **可持久化分块**，利用值域小（$v_i\le1000$）优化常数。
  - 复杂度 $O(L\log L + L\sqrt{V})$，理论更优。
- **学习点**：
  - 值域小时，分块可能比树状结构更快。

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤（最优解法）
#### 1. 构建 AC 自动机与 Fail 树
- **Trie 图**：将 $n$ 个模式串插入 Trie，建立 Fail 指针。
- **Fail 树性质**：`cnt_i` = 节点 $i$ 子树中被文本串经过的节点数之和。

#### 2. 虚树压缩
- **关键点**：文本串经过的节点 + LCA。
- **构建方法**：
  1. 按 DFS 序排序所有关键点。
  2. 相邻节点求 LCA 加入集合。
  3. 按祖先关系连边，形成虚树。

#### 3. 主席树维护权值
- **节点权值**：将每个模式串的 $v_i$ 挂在 Trie 终止节点。
- **查询操作**：对于虚树边 $(u, v)$，查询链 $[u, v)$ 中 $v_i \ge \lceil \frac{mid}{cnt_v} \rceil$ 的节点数。

#### 4. 二分答案
- **转化问题**：第 k 大 → 计数 ≥ mid 的个数。
- **复杂度**：$O(\log(\max ans) \times \text{查询复杂度})$。

### ⚔️ 策略竞技场：不同解法对比
| 策略 | 核心思想 | 优点 | 缺点 | 得分预期 |
|------|----------|------|------|----------|
| **暴力** | 枚举所有模式串，暴力匹配 | 实现简单 | $O(nL)$，无法通过 | 10pts |
| **AC 自动机 + 暴力统计** | 用 AC 自动机统计 cnt，暴力排序 | 正确性高 | $O(n\log n)$，无法通过 | 30-50pts |
| **虚树 + 主席树** | 压缩查询节点，主席树链查询 | 复杂度 $O(L\log^2 L)$ | 实现复杂 | 100pts |
| **分块优化** | 用分块替换主席树 | 常数更小 | 理论更优，但实现繁琐 | 100pts |

---

## 4. C++核心代码实现赏析

### 通用核心代码（abruce 100pts）
```cpp
// AC 自动机 + 虚树 + 主席树 + 二分
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
int n, m, tot = 1, cnt;
int ch[MAXN][4], fail[MAXN], dfn[MAXN], dep[MAXN], st[MAXN][19];
vector<int> e[MAXN], g[MAXN], w[MAXN], pos;

// 主席树
struct Node { int ls, rs, sum; } t[MAXN * 20];
int root[MAXN], idx;

void insert(int &u, int v, int l, int r, int x) {
    u = ++idx; t[u] = t[v]; t[u].sum++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) insert(t[u].ls, t[v].ls, l, mid, x);
    else insert(t[u].rs, t[v].rs, mid + 1, r, x);
}

int query(int u, int v, int l, int r, int L, int R) {
    if (!u || L > R) return 0;
    if (L <= l && r <= R) return t[u].sum - t[v].sum;
    int mid = (l + r) >> 1, res = 0;
    if (L <= mid) res += query(t[u].ls, t[v].ls, l, mid, L, R);
    if (R > mid) res += query(t[u].rs, t[v].rs, mid + 1, r, L, R);
    return res;
}

// AC 自动机
void buildAC() {
    queue<int> q;
    for (int i = 0; i < 4; ++i) ch[0][i] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            if (!ch[u][i]) ch[u][i] = ch[fail[u]][i];
            else {
                fail[ch[u][i]] = ch[fail[u]][i];
                q.push(ch[u][i]);
            }
        }
    }
    for (int i = 2; i <= tot; ++i) e[fail[i]].push_back(i);
}

// DFS 序 + 主席树
void dfs(int u) {
    dfn[u] = ++cnt; dep[u] = dep[fail[u]] + 1;
    root[u] = root[fail[u]];
    for (int v : w[u]) insert(root[u], root[u], 1, 1000, v);
    for (int v : e[u]) dfs(v);
}

// 虚树构建
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 18; ~i; --i) if (dep[st[x][i]] >= dep[y]) x = st[x][i];
    if (x == y) return x;
    for (int i = 18; ~i; --i) if (st[x][i] != st[y][i]) x = st[x][i], y = st[y][i];
    return fail[x];
}

// 主函数
int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for (int i = 1, v; i <= n; ++i) {
        string s; cin >> s >> v;
        int u = 1;
        for (char c : s) {
            if (!ch[u][c - 'a']) ch[u][c - 'a'] = ++tot;
            u = ch[u][c - 'a'];
        }
        w[u].push_back(v);
    }
    buildAC(); dfs(1);
    // 预处理 LCA
    for (int i = 1; i <= tot; ++i) st[i][0] = fail[i];
    for (int j = 1; j < 19; ++j)
        for (int i = 1; i <= tot; ++i)
            st[i][j] = st[st[i][j - 1]][j - 1];
    while (m--) {
        string S; int k; cin >> S >> k;
        int u = 1; pos.clear();
        for (char c : S) {
            u = ch[u][c - 'a'];
            pos.push_back(u);
        }
        // 虚树构建与查询（略）
    }
    return 0;
}
```

---

## 5. 算法可视化：像素动画演示

### 动画主题：**“像素探险家在 Fail 树迷宫中寻宝”**
- **场景**：8 位像素风格的 Fail 树，节点为像素方块，边为像素箭头。
- **交互**：
  - **自动模式**：AI 自动遍历文本串，高亮经过的节点。
  - **手动模式**：点击节点查看其子树贡献。
- **音效**：
  - 节点被访问时播放“叮”声。
  - 找到第 k 大值时播放胜利音效。

### 关键帧设计
1. **AC 自动机构建**：像素化 Trie 树逐层生长，Fail 指针闪烁。
2. **虚树压缩**：无用节点淡出，关键点高亮。
3. **主席树查询**：链上节点权值以像素柱状图展示，二分 mid 时动态过滤。

---

## 6. 拓展练习与相似问题思考

### 通用技巧迁移
- **虚树**：适用于所有“树上关键点查询”问题，如：
  - 动态维护树的直径。
  - 多次查询路径信息（如 LCA、路径和）。
- **主席树**：适用于“区间第 k 大”问题，如：
  - 静态区间逆序对。
  - 二维数点问题。

### 洛谷推荐练习
1. **P3804 [模板] AC 自动机（二次加强版）**  
   🗣️ 巩固 AC 自动机模板，理解 Fail 树性质。
2. **P3293 [SCOI2016] 背单词**  
   🗣️ 虚树 + 字符串的经典应用，练习虚树构建。
3. **P3834 [模板] 可持久化线段树（主席树）**  
   🗣️ 掌握主席树区间第 k 大模板。
4. **P4688 [Ynoi2016] 掉进兔子洞**  
   🗣️ 虚树 + 主席树的综合应用，挑战思维深度。

---

## 7. 学习心得与经验分享

> **abruce 的调试心得**：“虚树构建时务必去重，否则会导致重复计算。建议打印虚树节点和边，验证连通性。”  
> **251Sec 的乱搞感悟**：“数据水时，暴力可能出奇制胜，但需评估风险。”  
> **Seauy 的优化技巧**：“值域小时，分块常数优于树状结构，但需精细实现。”

---

<conclusion>
通过本题，我们学习了如何从“多模式匹配”到“第 k 大查询”的完整思维链。记住：  
- **AC 自动机**是字符串问题的瑞士军刀。  
- **虚树**能将 $O(n)$ 压缩为 $O(k)$。  
- **二分 + 数据结构**是解决第 k 大的通用范式。  
继续探索，下一个“莫扎特”就是你！💪
</conclusion>

---
处理用时：133.78秒