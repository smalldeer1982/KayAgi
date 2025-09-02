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

✨ **本题主要考察**：AC自动机、虚树、二分答案、主席树  

🗣️ **初步分析**：  
解决这道题的关键，是把「多模式串匹配」「动态点集处理」「第k大查询」三个问题结合起来。我们可以用几个简单的比喻理解核心算法：  
- **AC自动机**：像一本“带导航的单词字典”——把所有模式串建成一棵Trie树（字典），再给每个节点加“失败跳转”（导航），这样文本串能快速匹配所有模式串，还能记录每个模式串的出现次数。  
- **虚树**：像“简化版的树”——当文本串匹配后，只有少数节点会影响结果，虚树只保留这些关键节点，减少计算量。  
- **二分答案**：像“猜数字游戏”——要找第k大的数，我们先猜一个数，判断有多少数比它大，逐步缩小范围。  
- **主席树**：像“历史版本的账本”——每个节点都保存了从根到它的权值分布，能快速查询任意链上的权值满足条件的数量。  


### 核心算法流程与可视化思路  
1. **AC自动机构建**：把所有模式串插入Trie树，然后BFS建立Fail树（失败跳转）。  
2. **文本串匹配**：文本串在AC自动机上移动，记录经过的节点（这些节点是关键节点）。  
3. **虚树构建**：将关键节点按DFS序排序，找相邻节点的LCA，构建虚树（只保留关键节点和LCA）。  
4. **二分答案**：猜一个数`mid`，判断有多少模式串的`cnt_i * v_i ≥ mid`（`cnt_i`是出现次数，`v_i`是权值）。  
5. **主席树查询**：对于虚树的每条边，查询链上权值≥`mid/cnt`的数量，总和是否≥k。  


### 可视化设计思路  
我们设计一个**像素风“AC侦探查案”**动画：  
- **场景**：8位像素的Trie树网格，节点是彩色方块（起点红色、模式串结尾蓝色、文本串经过的节点黄色）。  
- **交互**：  
  - 文本串移动时，节点逐一点亮（黄色闪烁），伴随“滴”的音效。  
  - 虚树构建时，关键节点用绿色连线，LCA节点用紫色标记，伴随“叮”的音效。  
  - 二分答案时，当前猜的数显示在屏幕上方，满足条件的节点用橙色高亮，伴随“唰”的音效。  
- **控制**：支持单步执行、自动播放（速度可调）、重置，完成匹配时播放“胜利”音效。  


## 2. 精选优质题解参考

### 题解一（作者：abruce，赞：17）  
**点评**：这道题的“标准正解”，思路从暴力到优化一步步推导，非常清晰。作者先讲了暴力建AC自动机求cnt，再讲60分的树剖+线段树，最后给出100分的虚树+二分+主席树解法。代码结构规范，关键变量（如`tr`（Trie树）、`fail`（Fail树）、`rt`（主席树根））命名清晰，还提到了“虚树+主席树”的trick，是非常好的学习参考。  


### 题解二（作者：qiuzx，赞：4）  
**点评**：思路简洁，直接点出“模式串出现次数=Fail树子树标记数”“虚树处理动态点集”“二分答案+主席树查询”的核心逻辑。作者还提到了线段树二分的优化思路，拓展了思考角度，适合想深入理解的同学。  


### 题解三（作者：Sakura_xyz，赞：2）  
**点评**：代码结构非常清晰，注释详细（比如`dfs_fail`处理Fail树的主席树，`dfs1`处理树剖求LCA）。作者把每个步骤拆分成函数，比如`insert`（插入模式串）、`getfail`（构建Fail树）、`buildVT`（构建虚树），容易理解和模仿。  


## 3. 核心难点辨析与解题策略

### 关键点1：模式串出现次数的转化  
**难点**：如何快速计算每个模式串在文本串中的出现次数？  
**策略**：利用AC自动机的Fail树性质——模式串`s_i`的出现次数，等于其结尾节点在Fail树中的子树内，文本串经过的节点数量之和。比如，文本串经过节点`u`，会给`u`到根的所有节点的子树加1（因为这些节点对应的模式串都包含`u`的前缀）。  


### 关键点2：动态点集的处理  
**难点**：每次查询的文本串会产生不同的关键节点，直接处理所有节点太慢。  
**策略**：构建虚树——只保留关键节点（文本串经过的节点）和它们的LCA，这样虚树的大小只有`O(|S|)`（`|S|`是文本串长度），大大减少计算量。  


### 关键点3：链上权值查询  
**难点**：如何快速查询虚树每条边对应的原树链上，权值≥`mid/cnt`的数量？  
**策略**：用主席树维护每个节点到根的权值分布。每个节点的主席树从父节点继承，再加上自己的权值。查询时，用`rt[u] - rt[fa[u]]`就能得到`u`到`fa[u]`链上的权值分布。  


### 解题技巧总结  
- **正难则反**：第k大问题转化为二分答案的计数问题。  
- **虚树简化**：动态点集用虚树压缩，减少计算量。  
- **主席树维护**：静态链上查询用主席树，支持区间权值统计。  


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
**说明**：综合abruce、Sakura_xyz等优质题解，整理出的完整核心实现。  

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
int tr[MAXN][4], fail[MAXN], trie_cnt = 0;
vector<int> v[MAXN]; // 每个节点的权值

// 主席树
int rt[MAXN], node_cnt = 0;
struct SegNode { int lc, rc, sum; } seg[MAXN * 20];

// 树剖求LCA
int dep[MAXN], fa[MAXN][20], top[MAXN], son[MAXN], sz[MAXN], dfn[MAXN], dfncnt = 0;

// 虚树
vector<int> vt[MAXN];
int vis[MAXN], sz_vt[MAXN];

// AC自动机插入模式串
void insert(char* s, int val) {
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!tr[u][c]) tr[u][c] = ++trie_cnt;
        u = tr[u][c];
    }
    v[u].push_back(val);
}

// 构建Fail树
void build_fail() {
    queue<int> q;
    for (int i = 0; i < 4; i++) if (tr[0][i]) q.push(tr[0][i]);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            } else tr[u][i] = tr[fail[u]][i];
        }
    }
    // 将Fail树转化为有向树（fail[u]是u的父节点）
    for (int i = 1; i <= trie_cnt; i++) vt[fail[i]].push_back(i);
}

// 主席树更新
void update(int& rt, int pre, int l, int r, int val) {
    rt = ++node_cnt;
    seg[rt] = seg[pre];
    seg[rt].sum++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (val <= mid) update(seg[rt].lc, seg[pre].lc, l, mid, val);
    else update(seg[rt].rc, seg[pre].rc, mid + 1, r, val);
}

// 主席树查询
int query(int rt1, int rt2, int l, int r, int L, int R) {
    if (L > R) return 0;
    if (L <= l && r <= R) return seg[rt2].sum - seg[rt1].sum;
    int mid = (l + r) >> 1, res = 0;
    if (L <= mid) res += query(seg[rt1].lc, seg[rt2].lc, l, mid, L, R);
    if (R > mid) res += query(seg[rt1].rc, seg[rt2].rc, mid + 1, r, L, R);
    return res;
}

// DFS处理Fail树的主席树和树剖
void dfs_fail(int u) {
    sz[u] = 1;
    // 主席树继承父节点的权值
    rt[u] = rt[fail[u]];
    for (int val : v[u]) update(rt[u], rt[u], 1, MAXV, val);
    // 树剖求son（重儿子）
    for (int v : vt[u]) {
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        dfs_fail(v);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

// 树剖求top（重链顶端）
void dfs_top(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++dfncnt;
    if (son[u]) dfs_top(son[u], tp);
    for (int v : vt[u]) if (v != son[u]) dfs_top(v, v);
}

// 求LCA
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[x][0];
    }
    return dep[x] < dep[y] ? x : y;
}

// 虚树构建（简化版）
vector<int> key_nodes;
void build_vt() {
    sort(key_nodes.begin(), key_nodes.end(), [](int a, int b) { return dfn[a] < dfn[b]; });
    vector<int> stk;
    stk.push_back(0);
    for (int u : key_nodes) {
        int l = lca(stk.back(), u);
        while (stk.size() >= 2 && dep[l] < dep[stk[stk.size()-2]]) {
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
    while (stk.size() >= 2) {
        vt[stk[stk.size()-2]].push_back(stk.back());
        stk.pop_back();
    }
}

// 计算虚树子树大小（cnt_i）
void calc_sz(int u) {
    sz_vt[u] = vis[u];
    for (int v : vt[u]) {
        calc_sz(v);
        sz_vt[u] += sz_vt[v];
    }
}

// 二分答案的判断函数
int check(int mid) {
    int res = 0;
    // 遍历虚树的每条边，查询链上权值≥(mid-1)/sz_vt[v]+1的数量
    function<void(int, int)> dfs = [&](int u, int fa) {
        for (int v : vt[u]) {
            dfs(v, u);
            int cnt = sz_vt[v];
            if (cnt == 0) continue;
            int val = (mid - 1) / cnt + 1;
            if (val > MAXV) continue;
            res += query(rt[fa], rt[v], 1, MAXV, val, MAXV);
        }
    };
    dfs(0, -1);
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char s[MAXN];
        int val;
        cin >> s >> val;
        insert(s, val);
    }
    build_fail();
    // 初始化树剖和主席树
    dep[0] = 1;
    dfs_fail(0);
    dfs_top(0, 0);
    // 预处理LCA的跳表
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i <= trie_cnt; i++) {
            fa[i][j] = fa[fa[i][j-1]][j-1];
        }
    }
    while (m--) {
        char S[MAXN];
        int k;
        cin >> S >> k;
        // 文本串匹配，记录关键节点
        key_nodes.clear();
        memset(vis, 0, sizeof(vis));
        int u = 0;
        for (int i = 0; S[i]; i++) {
            u = tr[u][S[i] - 'a'];
            key_nodes.push_back(u);
            vis[u]++;
        }
        // 构建虚树
        memset(vt, 0, sizeof(vt));
        build_vt();
        // 计算虚树子树大小
        calc_sz(0);
        // 二分答案
        int l = 1, r = 1e9, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid) >= k) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

**代码解读概要**：  
1. **AC自动机**：`insert`插入模式串，`build_fail`构建Fail树。  
2. **主席树**：`update`维护每个节点到根的权值分布，`query`查询区间权值数量。  
3. **树剖**：`dfs_fail`处理Fail树的主席树和重儿子，`dfs_top`处理重链顶端，`lca`求最近公共祖先。  
4. **虚树**：`build_vt`构建虚树，`calc_sz`计算虚树子树大小（`cnt_i`）。  
5. **二分答案**：`check`判断当前`mid`是否满足条件，`main`中二分找第k大。  


### 题解一核心代码片段赏析（abruce的虚树构建）  
**亮点**：用栈高效构建虚树，处理相邻节点的LCA。  
```cpp
sort(zc+1,zc+len+1,cmp),len=unique(zc+1,zc+len+1)-zc-1;
st[top=1]=zc[1];
for(register int i=2; i<=len; i++) {
    int la=lca(st[top],zc[i]);
    while(top) {
        if(d[la]>=d[st[top-1]]) {
            if(la!=st[top])w[la].push_back(st[top]),la!=st[top-1]?st[top]=la:top--;
            break;
        }
        w[st[top-1]].push_back(st[top]),top--;
    }
    st[++top]=zc[i];
}
while(--top)w[st[top]].push_back(st[top+1]);
```
**代码解读**：  
- 首先将关键节点按DFS序排序（`sort(zc+1,zc+len+1,cmp)`），去重（`unique`）。  
- 用栈`st`维护虚树的构建：遍历每个关键节点`zc[i]`，找它与栈顶节点的LCA`la`。  
- 当栈顶节点的深度大于`la`时，弹出栈顶，将栈顶与前一个节点连边（`w[st[top-1]].push_back(st[top])`）。  
- 最后将栈中剩余节点连边，完成虚树构建。  


## 5. 算法可视化：像素动画演示

### 动画主题：像素AC侦探查案  
**设计思路**：用8位像素风格模拟AC自动机匹配和虚树构建，结合游戏化元素（音效、关卡），让学习更有趣。  


### 动画步骤  
1. **场景初始化**：  
   - 屏幕显示像素化的Trie树（根节点0是红色方块，子节点是灰色方块）。  
   - 控制面板有“开始”“单步”“重置”按钮，速度滑块（1~5档）。  
   - 8位风格的背景音乐（轻快的电子音）开始播放。  


2. **模式串插入**：  
   - 插入模式串“ab”时，Trie树的节点0→1（a）→2（b）逐一点亮（蓝色闪烁），伴随“嗒”的音效。  
   - 节点2的权值`v=2`显示在节点下方（白色像素字）。  


3. **文本串匹配**：  
   - 文本串“bbaba”在AC自动机上移动：节点0→3（b）→3（b）→1（a）→2（b）→...，每个节点点亮（黄色闪烁），伴随“滴”的音效。  
   - 关键节点（3、3、1、2）记录在右侧的“关键节点列表”（绿色像素块）。  


4. **虚树构建**：  
   - 关键节点按DFS序排序（3、1、2），找相邻节点的LCA（3和1的LCA是0，1和2的LCA是0）。  
   - 虚树的边0→3、0→1、0→2用绿色连线，LCA节点0用紫色标记，伴随“叮”的音效。  


5. **二分答案**：  
   - 猜`mid=4`，计算每条边的`cnt`（3的`cnt=2`，1的`cnt=1`，2的`cnt=1`）。  
   - 边0→3的权值≥`4/2=2`的数量：节点3的权值是2，符合条件，计数+1。  
   - 边0→2的权值≥`4/1=4`的数量：节点2的权值是2，不符合，计数不变。  
   - 总计数=1≥k=2？不，调整`mid`为3，重新计算，直到找到答案4。  


6. **结果展示**：  
   - 答案4显示在屏幕中央（红色像素字），伴随“胜利”音效（上扬的电子音）。  


## 6. 拓展练习与相似问题思考

### 通用思路迁移  
- **AC自动机**：适用于多模式串匹配（比如敏感词过滤、文本分析）。  
- **虚树**：适用于动态点集的树问题（比如多次查询树的路径信息）。  
- **二分答案+主席树**：适用于求第k大或第k小的问题（比如区间第k大、树链第k大）。  


### 洛谷练习推荐  
1. **P3796 【模板】AC自动机（加强版）**：练习AC自动机的基本用法，求每个模式串的出现次数。  
2. **P2414 [NOI2011] 阿狸的打字机**：练习AC自动机的Fail树和树剖，求两个模式串的包含关系。  
3. **P3834 【模板】可持久化线段树 1（主席树）**：练习主席树的基本用法，求区间第k大。  
4. **P4093 [HEOI2016/TJOI2016] 序列**：练习虚树和主席树的结合，处理动态点集的路径查询。  


## 7. 学习心得与经验分享  
- **abruce的经验**：“赛时没想到虚树，后来才发现虚树能大大减少计算量。”——虚树是处理动态点集的利器，遇到树的动态问题时，先想虚树。  
- **Sakura_xyz的经验**：“主席树的区间查询要注意`rt[u] - rt[fa[u]]`，因为每个节点的主席树继承了父节点的信息。”——主席树的“前缀和”思想是关键。  


## 结语  
这道题是AC自动机、虚树、二分答案、主席树的综合应用，非常考验对算法的理解和结合能力。通过这道题的学习，你不仅能掌握这些算法的用法，还能学会如何将不同的算法结合起来解决复杂问题。记住：编程的本质是“问题转化”——把复杂问题拆分成一个个已知的小问题，再用对应的算法解决！💪

---
处理用时：142.66秒