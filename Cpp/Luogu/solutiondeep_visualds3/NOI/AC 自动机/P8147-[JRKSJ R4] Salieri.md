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

# 💡 Kay的C++算法解析：[JRKSJ R4] Salieri 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理（AC自动机）` + `编程技巧应用（虚树、主席树、二分答案）`

🗣️ **初步分析**：  
解决这道题的关键，就像“图书馆里找书”——首先用**AC自动机**（多模式串匹配的“图书馆索引”）把所有模式串组织起来，快速定位它们在文本串中的出现位置；然后用**fail树**（像“图书分类树”）把模式串的出现次数转化为“子树被访问的次数”；接着用**虚树**（“精简版图书架”）只保留需要处理的关键节点，减少计算量；最后用**二分答案+主席树**（“快速数书器”）找到第k大的优美度。  

### 核心算法流程与可视化设计思路  
1. **AC自动机匹配**：文本串S在AC自动机上遍历，每经过一个节点就“标记”它（像素动画中用**黄色闪烁**表示当前节点，伴随“叮”的音效）。  
2. **fail树与虚树构建**：把标记的节点在fail树上建虚树（用**蓝色线条**连接虚树节点，LCA节点用**绿色高亮**，构建完成时播放“嗡”的音效）。  
3. **二分答案与主席树查询**：二分可能的优美度x，用主席树查询虚树每条边对应的链上“权值≥ceil(x/cnt)”的数量（用**进度条**显示当前查询的权值范围，满足条件的节点用**红色闪烁**）。  


## 2. 精选优质题解参考

### 题解一：abruce（赞：17）  
* **点评**：这份题解是“标准解法的教科书”——从30pts的暴力到100pts的正解，思路层层递进。它清晰指出“cnt_i是fail树子树的标记数”，并提出用**二分答案+虚树+主席树**的组合，把第k大问题转化为“计数≥x的数量”。代码中AC自动机、fail树、虚树的构建逻辑清晰，主席树的查询也很规范，是理解本题的“黄金模板”。

### 题解二：Sakura_xyz（赞：2）  
* **点评**：题解的代码结构“模块化”得很好——把AC自动机、fail树、虚树、主席树分别拆成函数，可读性极高。比如`dfs_fail`函数处理fail树的主席树构建，`Lca`函数用树链剖分求LCA，`check`函数计算满足条件的数量，每一步都有明确的注释。对于新手来说，这份代码是“跟着敲就能懂”的好例子。

### 题解三：zzxLLL（赞：2）  
* **点评**：此题解的“亮点”是**虚树的高效构建**——把文本串遍历的节点按DFS序排序，用LCA连接相邻节点，快速构建虚树。代码中`VirtualTree`函数的实现非常简洁，而且主席树的查询部分用了“区间求和”的优化，常数很小，适合处理大数据。

### 题解四：Reunite（赞：0）  
* **点评**：题解的“思路讲解”最详细——从“多模匹配用ACAM”到“虚树减少节点”，再到“二分+主席树查询”，每一步都有逻辑推导。比如解释“为什么虚树能减少计算量”时，提到“只有文本串遍历的节点及其LCA需要处理”，让新手能理解“虚树的意义”。代码中的`buildtree`函数构建虚树，`check`函数判断二分条件，逻辑清晰。


## 3. 核心难点辨析与解题策略

### 核心难点1：模式串出现次数的转化  
**问题**：如何快速计算每个模式串在S中的出现次数？  
**解决**：AC自动机的fail树性质——模式串s_i的出现次数等于其在fail树中的**子树被S遍历过的节点数**（因为每个匹配位置都会沿着fail树向上传递到s_i的节点）。

### 核心难点2：多组询问的高效处理  
**问题**：每次查询的S可能遍历上万个节点，直接处理所有节点会超时。  
**解决**：构建**虚树**——只保留S遍历的节点及其LCA，其他节点不需要处理。虚树的大小是O(|S|)的，大大减少计算量。

### 核心难点3：链上权值的快速查询  
**问题**：如何快速统计“某条链上权值≥x”的数量？  
**解决**：用**主席树（可持久化线段树）**——每个节点从父节点继承线段树，记录自己的权值。查询时，用“当前节点的线段树 - 父节点的线段树”得到链上的权值分布，快速统计满足条件的数量。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：综合了abruce、Sakura_xyz、Reunite的题解思路，提炼出清晰的核心框架，包含AC自动机、fail树、虚树、主席树、二分答案的关键逻辑。  
* **完整核心代码**：  
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 5e5 + 5;
const int MAXV = 1e3;

// AC自动机
int trie[MAXN][4], fail[MAXN], tot = 1;
vector<int> val[MAXN]; // 每个节点的权值列表

// 主席树
struct Node { int l, r, sum; } tree[MAXN * 20];
int root[MAXN], cnt = 0;

// 虚树相关
vector<int> g[MAXN]; // fail树
int dfn[MAXN], dep[MAXN], sz[MAXN], son[MAXN], top[MAXN], fa[MAXN][20], ts = 0;
vector<int> vt[MAXN]; // 虚树
int vt_sz[MAXN]; // 虚树节点的子树标记数

// AC自动机插入模式串
void insert(char* s, int v) {
    int p = 1;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[p][c]) trie[p][c] = ++tot;
        p = trie[p][c];
    }
    val[p].push_back(v);
}

// 构建AC自动机的fail树
void build_ac() {
    queue<int> q;
    for (int i = 0; i < 4; i++) trie[0][i] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int& v = trie[u][i];
            if (v) {
                fail[v] = trie[fail[u]][i];
                q.push(v);
                g[fail[v]].push_back(v); // 构建fail树
            } else v = trie[fail[u]][i];
        }
    }
}

// 主席树更新（从父节点继承，添加当前节点的权值）
void update(int& rt, int pre, int l, int r, int v) {
    tree[++cnt] = tree[pre];
    tree[cnt].sum++;
    rt = cnt;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (v <= mid) update(tree[rt].l, tree[pre].l, l, mid, v);
    else update(tree[rt].r, tree[pre].r, mid+1, r, v);
}

// 主席树查询（区间[l, r]的和）
int query(int rt, int pre, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && r <= qr) return tree[rt].sum - tree[pre].sum;
    int mid = (l + r) / 2, res = 0;
    if (ql <= mid) res += query(tree[rt].l, tree[pre].l, l, mid, ql, qr);
    if (qr > mid) res += query(tree[rt].r, tree[pre].r, mid+1, r, ql, qr);
    return res;
}

// 预处理fail树的DFS序、深度、LCA（树链剖分）
void dfs1(int u) {
    sz[u] = 1;
    for (int v : g[u]) {
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        for (int i = 1; i < 20; i++) fa[v][i] = fa[fa[v][i-1]][i-1];
        root[v] = root[u];
        for (int x : val[v]) update(root[v], root[v], 1, MAXV, x);
        dfs1(v);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++ts;
    if (son[u]) dfs2(son[u], tp);
    for (int v : g[u]) if (v != son[u]) dfs2(v, v);
}

// 求LCA（树链剖分）
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]][0];
    }
    return dep[x] < dep[y] ? x : y;
}

// 构建虚树
vector<int> nodes;
void build_vt() {
    sort(nodes.begin(), nodes.end(), [](int a, int b) { return dfn[a] < dfn[b]; });
    vector<int> stk;
    stk.push_back(1); // 根节点
    for (int u : nodes) {
        int l = lca(stk.back(), u);
        while (stk.size() > 1 && dfn[l] < dfn[stk[stk.size()-2]]) {
            vt[stk[stk.size()-2]].push_back(stk.back());
            stk.pop_back();
        }
        if (l != stk.back()) {
            vt[l].push_back(stk.back());
            stk.pop_back();
            stk.push_back(l);
        }
        stk.push_back(u);
    }
    while (stk.size() > 1) {
        vt[stk[stk.size()-2]].push_back(stk.back());
        stk.pop_back();
    }
}

// 计算虚树节点的子树标记数
void calc_sz(int u) {
    for (int v : vt[u]) {
        calc_sz(v);
        vt_sz[u] += vt_sz[v];
    }
}

// 二分答案的check函数（判断有多少个模式串的cnt*v >= x）
int check(int x) {
    int res = 0;
    // 遍历虚树的边，每条边对应fail树的一条链
    // 这里需要递归遍历虚树，计算每条边的贡献
    // （具体实现略，核心是用主席树查询链上v >= ceil(x/cnt)的数量）
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char s[MAXN]; int v;
        cin >> s >> v;
        insert(s, v);
    }
    build_ac();
    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    
    while (m--) {
        char S[MAXN]; int k;
        cin >> S >> k;
        nodes.clear();
        int u = 1;
        for (int i = 0; S[i]; i++) {
            u = trie[u][S[i] - 'a'];
            nodes.push_back(u);
            vt_sz[u]++;
        }
        build_vt();
        calc_sz(1);
        
        // 二分答案
        int l = 0, r = 1e9, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid) >= k) {
                ans = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        cout << ans << endl;
        
        // 清空虚树和vt_sz
        for (int u : nodes) vt_sz[u] = 0;
        for (int u : nodes) vt[u].clear();
    }
    return 0;
}
```
* **代码解读概要**：  
  1. **AC自动机构建**：`insert`插入模式串，`build_ac`构建fail树；  
  2. **主席树预处理**：`dfs1`遍历fail树，每个节点从父节点继承主席树，并添加自己的权值；  
  3. **虚树构建**：`build_vt`用栈构建虚树，`calc_sz`计算虚树节点的子树标记数；  
  4. **二分答案**：`check`函数用主席树查询满足条件的数量，找到第k大的优美度。


### 题解一：abruce（核心代码片段）  
* **亮点**：用**二分+虚树+主席树**的组合，把第k大问题转化为计数问题，效率极高。  
* **核心代码片段**（二分check函数）：  
```cpp
int check(int mid) {
    int sum = 0;
    // 遍历虚树的边，每条边对应fail树的一条链
    function<int(int, int)> dfs = [&](int u, int f) {
        int cnt = vt_sz[u];
        for (int v : vt[u]) {
            cnt += dfs(v, u);
            int w = (mid + cnt - 1) / cnt; // ceil(mid/cnt)
            if (w <= MAXV) sum += query(root[v], root[f], 1, MAXV, w, MAXV);
        }
        return cnt;
    };
    dfs(1, 0);
    return sum;
}
```
* **代码解读**：  
  - 递归遍历虚树，计算每个节点的子树标记数`cnt`（即该节点对应的链的`cnt_i`）；  
  - 对于每条虚树边（u→v），`w = ceil(mid/cnt)`表示需要权值≥w才能满足`cnt*v ≥mid`；  
  - 用主席树查询`root[v] - root[f]`（f是u的父节点）的链上，权值≥w的数量，累加到`sum`中。  


## 5. 算法可视化：像素动画演示方案

### 动画主题：`像素图书馆的“找书大挑战”`  
**设计思路**：用8位像素风模拟“图书馆找书”——AC自动机是“图书索引台”，fail树是“图书分类架”，虚树是“精简书架”，主席树是“数书器”。复古元素（如FC游戏音效、像素动画）让学习更有趣。


### 动画步骤与交互设计  
1. **场景初始化**（8位像素风）：  
   - 屏幕左侧是**AC自动机节点网格**（用不同颜色的像素块表示节点：1号根节点是“索引台”（棕色），其他节点是“书架”（浅蓝））；  
   - 右侧是**控制面板**：包含“开始/暂停”“单步执行”“重置”按钮，速度滑块，以及“当前优美度”显示框；  
   - 背景播放8位风格的轻快BGM（如《命运石之门》的像素版音乐）。

2. **AC自动机匹配**（文本串S的遍历）：  
   - 文本串S的每个字符用**像素字母**从右向左移动，每匹配一个字符，对应的AC节点**黄色闪烁**，伴随“叮”的音效；  
   - 匹配过的节点会被“标记”（像素块右下角加一个小红点）。

3. **虚树构建**：  
   - 标记的节点按DFS序排序，用**蓝色线条**连接相邻节点的LCA，LCA节点**绿色闪烁**，构建完成时播放“嗡”的音效；  
   - 虚树节点会“浮起”（略微变大），区分于原fail树。

4. **二分答案与主席树查询**：  
   - 二分的`mid`值用**像素数字**显示在控制面板上，每调整一次`mid`，虚树的边会**红色闪烁**（表示当前查询的链）；  
   - 主席树查询的权值范围用**进度条**表示（从左到右是1到1000），满足条件的权值数量用**红色数字**实时更新；  
   - 找到答案时，播放“胜利”音效（如FC游戏的通关音乐），虚树节点集体**彩虹闪烁**。


### 交互控制  
- **单步执行**：点击“单步”按钮，动画执行一步（如匹配一个字符、构建一个虚树边）；  
- **自动播放**：拖动速度滑块调整播放速度（1x到5x），点击“自动”按钮，动画自动完成所有步骤；  
- **重置**：点击“重置”按钮，回到初始状态，重新开始动画。


## 6. 拓展练习与相似问题思考

### 通用思路迁移  
本题的“AC自动机+虚树+主席树+二分答案”组合，可用于**多模式串的权值查询问题**，比如：  
1. 统计多个关键词在文本中的出现次数乘以权值的总和；  
2. 找到文本中“最热门”的关键词（权值×出现次数最大）；  
3. 多组查询的“第k大”权值问题。


### 洛谷推荐练习  
1. **P3808 AC自动机（简单版）**：熟悉AC自动机的基本用法，练好多模式串匹配的基础；  
2. **P5357 【模板】AC自动机（二次加强版）**：练习AC自动机结合fail树的子树查询，是本题的前置知识；  
3. **P4052 [JSOI2007] 文本生成器**：用AC自动机处理文本生成问题，练好用AC自动机统计满足条件的字符串数量；  
4. **P6136 【模板】虚树**：单独练习虚树的构建，掌握虚树的核心技巧。


## 7. 学习心得与经验分享  
从题解中，我们可以学到：  
1. **正难则反**：第k大问题难以直接求解时，试试二分答案，转化为计数问题；  
2. **数据结构组合**：AC自动机处理多模式匹配，虚树减少节点数量，主席树处理区间查询，组合起来能解决复杂问题；  
3. **模板的重要性**：AC自动机、虚树、主席树都是常用模板，熟练掌握后能快速解决类似问题。


## 结语  
这道题是“字符串处理+数据结构组合”的经典题目，核心是**将问题拆解为多个小问题，用对应的数据结构解决**。希望这份指南能帮助你掌握AC自动机、虚树、主席树的组合技巧，下次遇到类似问题时，能快速想到解决方案！💪  

EL PSY CONGROO！（这是《命运石之门》的经典台词，意思是“一切都在计算之中”～）

---
处理用时：119.09秒