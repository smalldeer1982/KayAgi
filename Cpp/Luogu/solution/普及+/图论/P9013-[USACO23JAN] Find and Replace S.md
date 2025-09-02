# [USACO23JAN] Find and Replace S

## 题目描述

Bessie 正在使用世界上最先进最伟大的文本编辑器：miV！她想将一个仅由大写和小写英文字母组成的字符串转换为一个新的字符串。每一次操作，miV 可以将字符串中所有的字母  $c_1$ 替换成另一种字母 $c_2$。例：对于字符串`aAbBa`, 如果将其中的 `a` 替换成 `B`, 那么字符串会变为`BAbBB`。

Bessie 非常地忙碌, 所以对于给出的 $T
(1 \le T \le 10)$ 组测试数据, 请输出她至少需要多少次操作才能把原字符串转换为新字符串。

## 说明/提示

- 对于 $ 40 \% $ 的数据，字符串的长度不超过 $50$。
 - 对于另外 $ 20\% $ 的数据，所有的字符串仅包含从 `a` 到 `e` 的小写字母。
 - 对于 $ 100\% $ 的数据，字符串的长度不超过 $10^5$，$1 \le T \le 10$。

## 样例 #1

### 输入

```
4
abc
abc
BBC
ABC
abc
bbc
ABCD
BACD```

### 输出

```
0
-1
1
3```

# 题解

## 作者：泥土笨笨 (赞：26)

此题细节非常多，比赛的时候给我错的死去活来的，还好数据不强。应该也是因为不好造数据吧。

# 关于其他题解的错误

看了一下其他题解，感觉有一些地方可以商榷。没有兴趣的同学可以跳过这一部分。

针对 `@zac2010` 的题解中的代码，给出一组 hack 数据。

```
1
DFB
FDD
```

这组数据答案应该是 $3$，首先把 `F` 变成 `B`，原始字符串变成 `DBB`。第二步把 `D` 变成 `F`，原始字符串变成 `FBB`，第三步把 `B` 变成 `D`，得到答案。由此可见答案为 $3$，但是题解中的代码跑出来答案是 $4$。

针对 @Demeanor_Roy 题解中的思路：

> 若借助字符串中不存在的点或者已经变换完成的联通块中入度为 $0$ 的点，答案增加 $1$。

这里其实有问题，不能借助已经完成的连通块中入度 $0$ 的点进行变换，因为这个点已经变换成了它想要的字符。如果还借助它，就会导致一个点要变成两种不同的字符。

# 解题思路

首先判断无解的情况，显然第一种无解是一个字母要变换成两个或者两个以上不同的字母。这个相信大家可以轻松实现。

第二种无解的情况是，`t` 字符串中出现了所有的字母，但是 `s` 字符串和 `t` 字符串不相同。原因一会儿会详细解释，读者有兴趣可以在这里先思考一下。

在没有第一种无解情况的情况下，我们把这个问题转换成一个图论问题。对于 $s$ 中某个字母 $s_i$ 要变成 $t$ 中另一个字母 $t_i$，就从 $s_i$ 到 $t_i$ 之间连一条有向边。这样我们得到一张最多 $52$ 个点的有向图。重边和自环都不建边。对于这种每个点最多有一条出边的图，大概会分为三种情况：链，带有入度的环，纯环。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/menp89bg.png)

第一种情况，图中 $1$ 到 $2$，$2$ 到 $3$ 这种链。链是很好处理的，答案的数量等于边的条数。

第二种情况，带有入度的链，比如图上 $4$ 到 $7$ 这四个点。虽然环不能直接操作，但是可以在环有入度的位置，把环断开。先把 $7$ 变成 $4$，再把 $6$ 变成 $7$，再把 $5$ 变成 $6$，再把 $4$ 变成 $5$。这样也可以处理，答案的数量等于边的条数。

第三种情况，纯环，图中 $8$ 到 $10$ 这三个点。这三个点如果要解开，需要额外借一个点进来，花 $4$ 步才能处理。所以如果存在这样的纯环，每个纯环的答案等于边的条数加 $1$。

经过刚才的分析，我们发现答案等于边的条数加上纯环的个数。不过这里还有一个特殊情况，刚才说到纯环需要借一个点来拆环，这个点必须是没有在 $t$ 里面出现过的，否则有别的字符要变成它，又要从环里拆一个点变成它，一会儿从它变回环里的点的时候，就会出现一对多的情况。

这时候我们可以解释前文提到的第二种无解情况了。如果所有字符都在 $t$ 中出现过，除非 $s$ 和 $t$ 完全相等，否则无解。

首先因为每个字符只能变换成一种字符，而不会变换成两种以上的字符。（否则在前面情况一已经判掉了）那么 $s$ 中字符的种类数一定大于等于 $t$ 中字符的种类数。而 $t$ 中已经有所有的字母了，那么 $s$ 中一定有所有的字母。既然如此，也就不会出现 $s$ 中某两种字符变成 $t$ 中相同字符的情况。也就是说，$s$ 中字符和 $t$ 中字符构成一对一的映射关系。那么要么就是每个字母变成自己，要么就是形成一个纯环。但是只要出现纯环就解不开，因为已经没有别的点可以借用了。所以必须 $s$ 和 $t$ 完全相等才行。

思路清楚，代码实现就很简单啦。

```cpp
#include <iostream>
#include <cstring>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;

int T, n, to[300];//to表示i要变成什么
int in[300];//每个字符的入度
int vis[300];//vis数组记录每个字母是否已经能成功变化到它想去的字母
char s[MAXN], t[MAXN];

//从入度为0的点出发，把能到的点都标记vis
void topo() {
    queue<int> q;
    for (int i = 'A'; i <= 'Z'; ++i) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    for (int i = 'a'; i <= 'z'; ++i) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 1;
        int v = to[u];
        if (vis[v] == 0) {
            in[v] = 0;//只要能从不在环上的点走过来，强制进队
            q.push(v);
        }
    }
}

//把从u出发同一个环上的点都标记一遍
void dfs(int u) {
    vis[u] = 1;
    int v = to[u];
    if (vis[v] == 0) dfs(v);
}

int main() {
    cin >> T;
    while (T--) {
        set<char> b;//集合记录所有在s中出现过的字母
        memset(to, 0, sizeof to);
        memset(in, 0, sizeof in);
        memset(vis, 0, sizeof vis);
        cin >> s >> t;
        n = ::strlen(s);
        //第一种无解的情况，一个字符要变成两种以上不同字符，肯定不行
        int good = 1;
        for (int i = 0; i < n; ++i) {
            if (to[s[i]] == 0 || to[s[i]] == t[i]) {
                to[s[i]] = t[i];
            } else {
                good = 0;
            }
            b.insert(t[i]);
        }
        if (!good) {
            cout << -1 << endl;
            continue;
        }
        //第二种无解的情况，如果所有字母都在t中出现过，那么s和t必须相等才行。
        if (b.size() == 52) {
            if (strcmp(s, t) == 0) {
                cout << 0 << endl;
            } else {
                cout << -1 << endl;
            }
            continue;
        }
        //把每个原始字母向结果字母连边，建一张有向图，自环不管
        memset(to, 0, sizeof to);
        int ans = 0;//统计边的条数，其实就是需要的变化的数量
        for (int i = 0; i < n; ++i) {
            if (to[s[i]] == 0 && s[i] != t[i]) {
                to[s[i]] = t[i];
                in[t[i]]++;
                ans++;
            }
        }
        topo();
        //此时一定有解，对于现在还没标记的点，一定是在一个纯环里面，此时对于每个环答案加1
        for (int i = 'a'; i <= 'z'; ++i) {
            if (vis[i] == 0) {
                ans++;
                dfs(i);
            }
        }
        for (int i = 'A'; i <= 'Z'; ++i) {
            if (vis[i] == 0) {
                ans++;
                dfs(i);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：PikachuQAQ (赞：3)

## Description

[Link](https://www.luogu.com.cn/problem/P9013)

## Solution

写这篇题解是因为模拟赛差点因为这题 boom 0，特此纪念。

不妨对于 $s$ 和 $t$ 二字符串进行**建图操作**：对于 $s_i,t_i(i \in n)$ 建一条对于字母 $s_i$ 到 $t_i$ 的有向边。

比如 $s = \texttt{ABCD}$，$t = \texttt{BADE}$，图示如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/6owg1c6z.png)

我们首先注意到一个显然的无解情况：对于一类字符，如果其需要**转化为多类**而不是**另一类字符**，则给定情况无解。如样例中的 $s = \texttt{BBC}$，$t = \texttt{ABC}$。

与此同时，注意到对于形成环的两种字符，如 $s = \texttt{AB}$，$t = \texttt{BA}$，需要**多出一类字符**进行转化。当且仅当字母集大小为 $52$，也就是 $\texttt{a}\sim\texttt{z}$，$\texttt{A}\sim\texttt{Z}$ 全部用上时图中**有环且并非基环树**，无法多出一类字母进行转化，则情况无解。

至此，本题所有无解情况上述完毕。

考虑如何计算有解情况下的答案。

首先，对于每个 $s_i$ 对应字母建一条到 $t_i$ 对应字母的边，意味着需要进行一次转化，对答案产生的贡献为 $1$。

然后，前文写到对于图中的每个环，需要多出一个字符以辅助转化，多产生 $1$ 的贡献，所以我们**对于整张图进行拓扑排序**，然后**对整张图 DFS 一遍**，找到整张图环的个数，加上**环的个数**和整张图**边的个数**即为答案。

最后记得多测要清空，本题就做完了。

对于每一组数据，时间复杂度 $O(n)$。

## Code

```cpp
// 2023/8/20 Accept__

#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

const int kMaxN = 1e5 + 7, kL = 256, kA = 52;

int T, ans, n, in[kL], m, to[kL];
bool flag, vis[kL];
string s, t;
vector<int> g[kL];
set<int> st;
queue<int> q;

void topo() {
    int res = 0;
    for (int i = 1; i <= kA; i++) {
        (in[i] == 0) && (q.push(i), 1);
    }
    while (q.size()) {
        int u = q.front();
        q.pop(), vis[u] = 1;
        for (int v : g[u]) {
            (vis[v] == 0) && (q.push(v), in[v] = 0);
        }
    }
}

void DFS(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
        (vis[v] == 0) && (DFS(v), 1);
    }
}

void clear() {
    fill(to, to + kL, 0), fill(in, in + kL, 0), fill(vis, vis + kL, 0);
    ans = flag = 0;
    for_each(g, g + kL, [](vector<int> &a){ a.clear(); }), st.clear();
    while (q.size()) {
        q.pop();
    }
}

int toidx(char c) {
    return ('A' <= c && c <= 'Z') ? (c - 'A'+ 1) : (c - 'a' + 27);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> T; T; T--) {
        cin >> s >> t;
        n = s.length(), s = " " + s, t = " " + t, clear();
        for (int i = 1; i <= n; i++) {
            (to[toidx(s[i])] && to[toidx(s[i])] != t[i]) ? (flag = 1) : (to[toidx(s[i])] = t[i]);
            st.insert(toidx(t[i]));
        }  
        if (flag || st.size() == kA && s != t) {
            cout << -1 << '\n';
            continue;
        }
        for (int i = 1; i <= n; i++) {
            if (g[toidx(s[i])].empty() && s[i] != t[i]) {
                g[toidx(s[i])].push_back(toidx(t[i])), in[toidx(t[i])]++, ans++;
            }
        }
        topo();
        for (int i = 1; i <= kA; i++) {
            (vis[i] == 0) && (ans++, DFS(i), 1);
        }
        cout << ans << '\n';
    }

    return 0;
}
```


---

## 作者：tzyt (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P9013)

[强烈推荐博客中观看](https://ttzytt.com/2023/02/USACO23JAN%20Find%20and%20Replace%20S/)

# 分析

题意非常简洁，即问你通过一系列的字符替换，最少花多少步能把一个 $s$ 串变成 $t$ 串。

拿到题之后，可以先从样例开始分析。

从 $\texttt{BBC} \to \texttt{ABC}$ 这个样例可以发现，不可能同时把某个字符替换成两个字符（$\texttt{BB} \to \texttt{AB}$），会起冲突。

那直接统计 $s_i \ne t_i$ 的个数（给串去重之后，即不存在 $s = \texttt{AA}$，$t = \texttt{BB}$ 这种）就可以作为答案了吗？可以从最后一个样例发现不是这样的。

## 环的处理

因为最后一个样例中，$\texttt{CD}$ 的部分是一样的。我们直接考虑 $\texttt{AB} \to \texttt{BA}$ 的变换。如果直接执行 $\texttt{A} \to \texttt{B}$ 的操作，会得到一个 $\texttt{BB}$ 的串。这个时候就有了和前面一样的问题，不能将其转换成 $\texttt{BA}$。执行 $\texttt{B} \to \texttt{A}$ 也是同理。

解决的办法就是先执行 $\texttt{AB} \to x\texttt{B}$ 再处理 $x\texttt{B} \to \texttt{BA}$。（$x$ 是任意别的字符）

是否所有“相互依赖”的情况下，都可以通过这种方式解决呢？我们可以再思考一个大一点的样例 $\texttt{ABCD} \to \texttt{BCDA}$，用图（创建 $s_i \to t_i$ 的边，并且去掉重边和自环）的方式表示出来会更加清晰：

![](https://cdn.luogu.com.cn/upload/image_hosting/wwgdkdnt.png)

可以发现，这是一个环。无论我们先执行哪种 $x \to y$ 的变换，都会需要再执行 $y \to z$ 的变换。因为 $y$ 希望能变成别的。这个时候，先前 $x$ 会跟着一起被变成 $z$。

不过，如果能“化环为链”，就可以解决问题了。比如我们可以先执行 $\texttt{A} \to x$，这个链就会变成：

![](https://cdn.luogu.com.cn/upload/image_hosting/dwz6v4hh.png)

这样，就有一个执行 $x \to y$ 后，不用再执行 $y \to z$ 的地方了。即 $\texttt{D} \to \texttt{A}$ （执行完之后，$\texttt{C} \to \texttt{D}$ 也符合这个条件，我们倒着的按照链的顺序就可以把整条串转换为目标）。

从这两个例子可以看出，**在一般的情况下，一个操作能把环转化为链，或者把链的长度（边的数量）减少 1。**

所以答案的数量就是（环的数量 + 链的长度）了吗？

## 两种特例

### 1

首先，化环为链的操作需要一个不在环中出现的字符，假设环包含了字符集中所有的字符，我们是不能处理的。

假设我们的字符集只有 $\texttt{A} \sim \texttt{D}$ 这四个字符，那处理下面这个例子时候，就会发现问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/p2gwqygh.png)

不管先把 $\texttt{A}$ 变成什么字符，这个字符之后都会再经历最少一次的变换，导致 $\texttt{A}$ 不能被转换成目标字符 $\texttt{B}$。

当然，我们处理不了的情况不一定要求整张图中只有一个环，只要符合：

1. 所有节点都在环里
2. 字符集中的所有字符都被用到了

就不能处理了，比如下面这个例子，有两个环还是不行（字符集为 $\texttt{A} \sim \texttt{C}$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/2izqg5nx.png)

### 2

考虑这样一个输入：$\texttt{ABCDEF} \to \texttt{BCDABE}$

![](https://cdn.luogu.com.cn/upload/image_hosting/p2xw06bt.png)

我们可以在一个操作内即化环为链，又把链的长度减少 1。观察到 $\texttt{A}$ 和 $\texttt{E}$ 都希望能被转换成 $\texttt{B}$。从字符转换的角度来说，$\texttt{A} \to \texttt{B} \And \texttt{E} \to \texttt{B}$ 和 $\texttt{A} \to \texttt{E} \And \texttt{E} \to \texttt{B}$ 的最终结果和操作步数都是一样的。但是第二种方法在执行 $\texttt{A} \to \texttt{E}$ 时，也把环中的一个字符转换成了环外的字符，将环化成了链。

能这么做的前提条件是，有多个环外字符希望变成环内的一个字符。更严谨的说就是环中某个节点的入度大于等于 2。

到此为止，所有的情况都基本分析好了，可以写出以下的总结（括号中的为实际判断方法）：

1. 一个字符希望转换成多个字符是无解的。（节点出度最多为 1）。
2. 所有节点（所有可能的字符）全部在环中是无解的 （每种字符的入度都为 1）。
3. 答案 = 边的数量 + 绝对环的数量（环中每个节点的入度出度都为 1）。

这里第二点的判断方法可以稍微解释一下：

没有选择使用出度是考虑到了环连着树的情况，参考上图。

# 代码实现

实现的时候找环的部分需要注意一下，其他部分都比较简单。

我们知道 tarjan 算法就可以判环，不过这道题可以用“简化版”的 tarjan，不用记录访的时间戳。我们把 dfs 的时候把所有访问过的节点从队尾压入一个双向队列。

如果我们开始 dfs 的时候是从一个环上的点进入的，之后一定会访问到一个和队头一样的节点。这个时候把所有在队头和队尾之间的节点都弹出，就得到了环中的所有节点。

如果我们发现某个节点之前访问过，但是并不在队头，就可以确定队列中的节点都不是“绝对环”，因为有树连着他（参考上图，如果从 F 节点开始搜就会出现这种情况）。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int CHSZ = 52;  // char set size
int out[CHSZ + 1];   // 出度只能有一个
int lpid[CHSZ + 1];  // 环的 id，不知道 -> -1，不是环 -> 0，是环 -> 1,2,3...
enum LP_STAT { UNKNOWN = -1, NOT_ABS_LP = 0 };
deque<int> vised_dq;   // 用于在找环的时候储存信息
bool vised[CHSZ + 1];  // 用于在找环的时候储存信息

set<int> in_nds[CHSZ + 1]; // in nodes，入度可以有多个
int in1_cnt = 0; // 入读为 1 的节点的数量

int abs_lp_cnt = 0;  // 绝对环数，即环不连树的环数
int diff_chs = 0;

void init() {
    memset(out, 0, sizeof(out));
    fill(lpid, lpid + CHSZ + 1, UNKNOWN);
    vised_dq.clear();
    memset(vised, 0, sizeof(vised));
    for (int i = 0; i <= CHSZ; i++) in_nds[i].clear();
    in1_cnt = 0;
    abs_lp_cnt = 0;
    diff_chs = 0;
}

inline int ch2id(char x) {
    // char to id
    if (x >= 'a' && x <= 'z') return x - 'a' + 1;
    if (x >= 'A' && x <= 'Z') return x - 'A' + 27;
    return -1;
}

bool check_loop_connect_to_tree() {
    for (int cur : vised_dq) 
        if (in_nds[cur].size() >= 2) 
            // 有树连这个环
            return true;
    return false;
}

void fill_lpid_in_vised_dq(int val) {
    for (int cur : vised_dq)
        lpid[cur] = val;
    vised_dq.clear();
}

void mark_loop(int cur) {
    if (vised[cur] && vised_dq.front() != cur) {
        // 从一个树进入的环，不是绝对环
        fill_lpid_in_vised_dq(NOT_ABS_LP);
        return;
    }
    vised[cur] = true;
    if (out[cur] == cur) {
        // 没有出度，找到一个链
        fill_lpid_in_vised_dq(NOT_ABS_LP);
        return;
    }

    if (vised_dq.size() && vised_dq.front() == cur) {
        // 找到环
        if (!check_loop_connect_to_tree()) {
            // 如果环不连树
            abs_lp_cnt++;
            fill_lpid_in_vised_dq(abs_lp_cnt);
        } else {
            fill_lpid_in_vised_dq(NOT_ABS_LP);
        }
        return;
    }
    vised_dq.push_back(cur);
    mark_loop(out[cur]);
}

void solve(const string& origs, const string& tars) {
    // orig str -> tar str
    init();
    for (int i = 0; i < origs.size(); i++) {
        int och = ch2id(origs[i]);
        int tch = ch2id(tars[i]);
        if (out[och] && out[och] != tch) {
            // 如果 o 串已经有要转换的字符，但是不是 t
            // 串的字符，那么会产生多对一
            cout << -1 << '\n';
            return;
        }
        if (!out[och]) {
            out[och] = tch;
            in_nds[tch].insert(och);
            if (och != tch) 
                diff_chs++;
        }
    }
    for (int i = 1; i <= CHSZ; i++) {
        if (in_nds[i].size() == 1) 
            in1_cnt++; // 统计入度为 1 的节点数量
    }
    for (int i = 1; i <= CHSZ; i++) {
        if (out[i] && lpid[i] == UNKNOWN) {
            // 标记环
            vised_dq.clear();
            memset(vised, 0, sizeof(vised));
            mark_loop(i);
        }
    }
    if (origs != tars && in1_cnt == CHSZ) {
        // 判断是否全部都在环中，用入度为 1 的数量来判断
        cout << -1 << '\n';
        return;
    }
    cout << diff_chs + abs_lp_cnt << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string origs, tars;
        cin >> origs >> tars;
        solve(origs, tars);
    }
}
```

---

## 作者：lnwhl (赞：2)

首先将问题转化为一个图论问题。

每个 $s_i$ 向 $t_i$ 连边，去掉重边和自环，构成一张图。

首先判断无解的情况：
- 如果一个点的出度 $\ge2$，那么一定无解，因为一个字母无法变成多个字母。
- 如果 $t$ 包含所有的字母并且 $s\ne t$，那么也是无解，因为无论怎么变换 $s$ 的字符数都会小于 $52$。

对于有解的情况，考虑计算答案。

在不考虑重边和自环的情况，答案等于图中边的条数。

那么如果有环呢？我们就无法直接变换，需要借助外点。
- 如果环上某点的入度 $\ge2$，就说明环外的某点有指向该点的边，我们就可以从此处破环，答案不变。具体破环方法如下：假设有 $1\to2,2\to1,3\to2$ 三条边，点 $2$ 的入度 $\ge2$，我们把 $1$ 先变成 $3$，这样就可以把环破掉了。
- 如果没有点的入度 $\ge2$，我们就需要新建一个点，答案加 $+1$。

解决这个题的关键在于将问题转化成图论问题，并细致的分类讨论，实现的时候要注意对每个连通块打好标记。

代码如下（没有用到任何高级算法）：
```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
const int N=55;
int T,to[N],col[N],ideg[N];
string s,t;
il int cg(char ch)
{
	if(ch<='Z'&&ch>='A')return ch-'A'+1;
	return ch-'a'+27; 
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		memset(to,0,sizeof(to));
		memset(col,0,sizeof(col));
		memset(ideg,0,sizeof(ideg));
		cin>>s>>t;set<int>st;
		bool ok=1,same=1;
		for(int i=0;i<s.size();++i)
		{
			if(to[cg(s[i])]&&to[cg(s[i])]!=cg(t[i]))ok=0;
			to[cg(s[i])]=cg(t[i]);st.insert(cg(t[i]));
			if(s[i]!=t[i])same=0;
		}
		if(st.size()==52&&!same)ok=0;
       //判断无解，ok=0表示无解，same表示s和t是否相同，set维护t中字符个数
		if(ok)
		{
			int ans=0;
			for(int i=1;i<=52;++i)
				if(to[i]&&to[i]!=i)ideg[to[i]]++,ans++;
			for(int i=1;i<=52;++i)
			{
				if(col[i])continue;
				int u=i;
				while(u&&!col[u])col[u]=i,u=to[u];
				if(u&&u!=to[u]&&col[u]==i)
				{
					int v=u;bool fl=0;//fl表示是否有点入度>1
					do
					{
						col[v]=-1;
						if(ideg[v]>1)fl=1;
						v=to[v];
					}while(v!=u);
					if(!fl)ans++; 
				}
			}
			cout<<ans<<"\n";
		}
		else cout<<-1<<"\n";
	}
	return 0;
}

```

---

## 作者：cff_0102 (赞：2)

考虑按原字符连向新字符建一个图，如果一个字符有两个出边那么显然无解，如果新字符串所有 $52$ 个字符都占满了但两字符串不相等那么也是无解的。

那么如果有解，每个点都有不超过一条出边。由此每个连通块都有以下三种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/c2bgpbtd.png)

1. 这是一棵树（如上图的 $b\to y,s\to k\to y$）。直接按链从头到尾修改即可，操作数为边的数量。
2. 这是一个基环树。这时可以把环上一个入度大于 $1$ 的点（如上图的点 $N$）前面的那个在环上的顶点（如上图的点 $A$）改成这个点的另一个不在环上的顶点（如上图的点 $I$），接着就可以对这块子树正常操作，前一个点会由此变成它应该变成的点。即使这个点也有其它入边也没关系，后面的点还是可以正常操作过去。一直以此类推，最后的操作数也为边的数量。
3. 这是一个环（如上图的 $a\to q\to u\to a\dots$）。此时就需要找到一个空闲的点使得环断开成链，或者说把一个空的点接进来使得它变成第二种情况。这也是 $52$ 个字符都被占满就无解的原因（因为原字符串最多也就 $52$ 个不同的字符，每个字符最多一条出边，要让新字符串每个字符都出现，那么就必须形成一个环，而此时找不到一个空的点了）。因为凭空增加了一条边，此时需要的操作数为边数 $+1$。

把这三种情况合起来，那么最终的答案就是边数加上纯环的个数。

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
char mp[128];
bool f[128];
bool v[128];
int now;
int ccnt;
void dfs(int x){
	if(x==0)return;
	if(v[x]){
		if(x==now)ccnt++;
		return;
	}
	v[x]=1;
	dfs(mp[x]);
}
int mian(){
	string s,t;cin>>s>>t;
	memset(f,0,sizeof f);
	memset(v,0,sizeof v);
	memset(mp,0,sizeof mp);
	int n=s.length();s=' '+s;t=' '+t;
	for(int i=1;i<=n;i++){
		if(mp[s[i]]&&mp[s[i]]!=t[i]){
			cout<<-1<<endl;
			return 0;
		}
		mp[s[i]]=t[i];
		f[t[i]]=1;
	}
	int cnt=0;
	for(int i='A';i<='z';i++)cnt+=f[i];
	if(cnt==52&&s!=t)return cout<<-1<<endl,0;
	int ecnt=0;ccnt=0;
	vector<int>in[128];
	for(int i='A';i<='z';i++){
		if(mp[i]==i)mp[i]=0;
		ecnt+=(bool)(mp[i]);
		in[mp[i]].push_back(i);
	}
	for(int i='A';i<='z';i++){
		if(in[i].size()>=2){
			if(!v[i])dfs(i);
		}
	}
	for(int i='A';i<='z';i++){
		if(!v[i])now=i,dfs(i);
	}
	cout<<ccnt+ecnt<<endl;
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;while(t--)mian();
	return 0;
}
```

---

## 作者：huhangqi (赞：1)

***你说得对，但是图论是初学者的弱点。***

首先每个字母只能对应一个字母，这应该没有异议吧。

通过对示例进行模拟，我们不难发现，这道题的难点在于：环该如何处理。

情况比较复杂需要仔细分析，但是由于每个点出度均为 $1$ ，所以分析起来并不难。

假设每一个字母都是一个点建图，分两种情况讨论。

第一种情况，如果字母没有全部选择完。

如果这部分形成树状，那么每个点需要改变一次，除非这个点连接的是自己。

所用次数为所需改变的树上节点的个数，若连接自己则不用加一。

例如：
```
abc
bbc
```

如果形成环状，那么每一个环中都需要有一个点先变成某一个不在图中，其他点形成树状，将这个树处理后，将那个点变为需要变的点即可。

由于如果你本来就不需要变，出度为 $1$ 则不可能和其他点成为环，所以不考虑有自连的情况。

那么除了环内的点加一以外长度额外加一。

例如:
```
ABC
BCA
```
最特殊的形式，叫基环树，就是一个环上插一颗树，大概就是这样：

```
ABCDEF
BCAADE
```
那么此时就有一个很好的处理方式了。

将 $C$ 变为 $D$ ,把环拆成树，之后再将新树 $ABC$ 解决了，再把 $D$ 变为 $A$ ，最后解决掉树 $DEF$ 即可。

那么就和树所耗的次数相同，都是每有一个点就改变一次。

而这种同样没有自连情况。

那么我们不难发现在此情况下，大部分都用一次，而唯独在树上自恋时减一和有普通环时额外加一。

那么还有第二种情况：所有字母都用完了。

需要变成其他字母的只有环，所以环的处理会受到影响。

如果全都是环，那么肯定不行了。

但是如果产生了基环树或者有自连的树（非单个点），那么就会有空位产生，就能够解决。

这样就讨论完了全部情况，使用一个并查集查找环再具体分析处理即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char s1[100005],s2[100005];
int a[100005],b[100005],len,q,ans,p[105],t[105],fa[105],w[105],g[105],fl[105];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	fa[x]=y;
}
signed main(){
	cin>>q;
	while(q--){
		memset(p,0,sizeof(p));
		memset(t,0,sizeof(t));
		memset(w,0,sizeof(w));
		memset(g,0,sizeof(g));
		memset(fl,0,sizeof(fl));
		for(int i=1;i<=100;i++)fa[i]=i;
		cin>>s1+1>>s2+1;
		len=strlen(s1+1);
		for(int i=1;i<=len;i++){
			if(s1[i]<='Z')a[i]=s1[i]-'A'+1;//转数字，好处理
			else a[i]=s1[i]-'a'+27;
			if(s2[i]<='Z')b[i]=s2[i]-'A'+1;
			else b[i]=s2[i]-'a'+27;
		}
		bool f=true;
		ans=0;
		int cnt=0;
		for(int i=1;i<=len;i++){
			if(p[a[i]]==0){
				p[a[i]]=b[i];
				t[b[i]]++;//记录这个点被连接的次数
			}
			else if(p[a[i]]!=b[i]){//判断是否每个点只对应一个点
				f=false;
				break;
			}
			w[a[i]]++;//记录这个点是否在a串出现过
			if(w[a[i]]==1)cnt++;
		}
		if(!f){
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=52;i++){
			if(!w[i])continue;
			merge(i,p[i]);//连边
		}
		bool ff=0;
		for(int i=1;i<=52;i++){
			if(w[i]){
				g[find(i)]++;//图的部分节点数普查
				if(t[p[i]]>1){
					fl[find(i)]=1;//保证给基环树或者有自恋的树记录
					ff=1;//判断是否由以上图存在
				}
				
			}
		}
		f=0;
		for(int i=1;i<=52;i++){
			if(!w[i])continue;
			if(find(i)!=i)ans++;//判断所处部分是否有环或自恋
			else {
				if(p[i]==i)continue;//自恋不用加
				if(fl[i])ans++;//基环树，正常对待
				else if(ff||cnt!=52)ans+=2;//可以向其它点转移
				else {
					f=1;//否则不可行
					break;
				}
			}
		}
		if(f){
			cout<<-1<<endl;
			continue;
		}
		cout<<ans<<endl;
	}
	return 0;
} 
``````

---

## 作者：_3Zinc_ (赞：1)

## 前言

这是考试的时候放的一道题，考的时候没做出来。

调了一个晚上，心态爆炸，故作此篇。顺便，鸣谢[泥土笨笨](https://www.luogu.com.cn/user/43206)大佬的题解，给我的代码提供了强有力的对拍参照。

## 正题

首先看到题目，虽然字符串长度不超过 $10^5$，但是还是嫌多；再一看，**至多只有 $52$ 个字符**。

那么从这个数据范围入手，思考可以按照变换前后的字符串给所有字符建一张图，其中的每一条有向边 $a \rightarrow b$ 表示变换前的字符 $a$ 变成了字符 $b$。接下来思考这个图可能有哪几种形式：![](https://cdn.luogu.com.cn/upload/image_hosting/avf46pt2.png)

首先讨论 1：显然**无解**！一个字符不可能同时分裂成两种不同的字符。所以，我们得到了第一种无解的判定。

其次讨论形成一条链（2）：显然的，假设这条链有 $n$ 条边，可以在 $n$ 次转化后完成。

然后是一个环（3）：这就无法用 $n$ 次完成了，必须先将某个点换成另一种字符，转化成一条有 $n+1$ 个节点的链来做，所以要 $n+1$ 次完成。

最后是生出尾巴的环（4）：刹一看，好像要 $n+1$ 次完成；其实不用。把入度为 $2$ 的点叫做点 $a$，尾巴上指向 $a$ 的点是 $b$，环上指向 $a$ 的是 $c$，可以现将点 $c$ 换成字符 $b$，转换成一条 $n$ 的链，最后 $c$ 和 $b$ 一起变成 $a$。所以也是只用 $n$ 次。

当然，实际处理中这三种总是会一起出现（2,3,4），那么只要意义处理就行。

除了上面提到的第一种无解，还有一种情况就是转换后的字符串包含了所有的字符（$52$ 个），并且和转换前的字符串不同。这时候，若画出图来应该是一个 $52$ 个点的环，由于没有一个点可以变成另一个不同于这 $52$ 个点的字符，所以也是无解。

那么代码就好实现了。不过这里有几点需要注意：

- 从入度小的点开始遍历图，而不是按照字母顺序。

- 判断一个字符是否要同事变成两个字符时，别忘了把它自己算上。

接下来是代码时间（写法丑陋，仅作参考）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int nxt[55],id[128],ans,T;
bool vis[55],has[55],noind[55];
char s1[100005],s2[100005];
void init() {
    ans=0;
    memset(nxt,0,sizeof(nxt));
    memset(vis,false,sizeof(vis));
    memset(has,false,sizeof(has));
    memset(noind,true,sizeof(noind));
    memset(s1,0,sizeof(s1));
    memset(s2,0,sizeof(s2));
    return ;
}
void addans(int p) {
    if(vis[p]) return ;
    int v=p,type=0;
    vis[p]=true;
    while(nxt[v]) {
        type++,v=nxt[v];
        if(v==p) {
            ans+=type+1;
            return ;
        }
        if(vis[v]) {
            ans+=type;
            return ;
        }
        vis[v]=true;
    }
    ans+=type;
    return ;
}
int main() {
    scanf("%d",&T);
    for(int i=0;i<26;i++) id[i+'A']=i+1,id[i+'a']=i+27;
//    for(int i='A';i<='Z';i++) cout<<char(i)<<":"<<id[i]<<endl;
//    for(int i='a';i<='z';i++) cout<<char(i)<<":"<<id[i]<<endl;
    while(T--) {
        init();
        scanf("%s%s",s1+1,s2+1);
        int len=strlen(s1+1);
        bool no_ans=false,same=true;
        set<char> chset;
        for(int i=1;i<=len;i++) {
            int id1=id[s1[i]],id2=id[s2[i]];
            if(has[id1]&&(id2!=nxt[id1])) {
                no_ans=true;
                break;
            }
            else {
                has[id1]=true,nxt[id1]=id2;
                if(id1!=id2) noind[id2]=false,same=false;;
            }
            chset.insert(s2[i]);
        }
        if(same) {
            printf("0\n");
            continue;
        }
        for(int i=1;i<=52;i++)
            if(nxt[i]==i) nxt[i]=0;
        for(int i=1;i<=52;i++)
            if(noind[i]) addans(i);
        for(int i=1;i<=52;i++)
            if(has[i]) addans(i);
        if(no_ans) printf("-1\n");
        else if(chset.size()==52) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
```

完结撒花！！！

---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给定一个字符串，有一个转换器，可以将字符串中的所有字符 $a$ 替换成字符 $b$，问要经过多少次转换可以将原字符串变成另一个字符串。

### 题目分析

考虑将每个字母看作一个点，对于每一位，将 $s_i$ 向 $t_i$ 连边。

首先如果某个点连出边的数量大于等于二，说明它要变成两个点，无解。

如没有坏，答案为边的数量。

如有环，我们不能直接将环内的点变换成环内的点，于是就需要破环。

1. 所以可以看看有没有点连接着环内的点，从而从这里开始改，达到破环，答案依旧是边的数量。

2. 如果没有，我们就必须引进一个点，环中某个点变成它，从而达到破环的目的，答案为边数加 $1$。

3. 若不存在上述点，则无法破环，无解。

※ 注：可能存在很多环，对于每个环都要进行上述分类讨论。


---

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/P9013)

## 题意

给定两个字符串 $s$ 和 $t$，让后使用查找替换，也就是编辑器里面的 `Ctrl + H`。然后要你求最少需要几次操作完成从 $s$ 串改成 $t$ 串。

**注意：要改必须所有相同字母全部改**

## 思路

转化为图论，建图。每个 $s_i$ 和对应的 $t_i$ 建一条边。

接下来我们来看无解情况：对于一种字符，如果需要转化成多种字符，则无解。在图论中则指的是一个点的出度大于 $1$。

```
针对这种情况的Hack:
IN:
1
AAB
abB
OUT:
-1
```

第二种无解情况就是环，也就是多种字符互相转换，如果是这样，那就需要另一种字符来中转，就像我们手写 `swap` 一样。如果有环而且没有中转字符，也就是 $52$ 种字符全部用完则无解。

接着来看一下如何计算答案。

如果一条不在环里的边，答案加 $1$。

如果在环里，那么每一个环都需要一个字符来中转。所以要用拓扑排序来搜环。然后 **dfs** 来找环计算答案。

---

时间复杂度 $O(T \times n)$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxC = 256 + 5;
int mmt, n, to[kMaxC], indeg[kMaxC], vis[kMaxC];  //mmt是多组数据；to是s[i]对应的t[i]；indeg是入度，bfs要用；vis是dfs用来标记是否到达过的。
string s, t;
void T() {  //bfs标记
  queue<int> q;
  for (int i = 'A'; i <= 'z'; i++) {
    if (!indeg[i]) {
      q.push(i);
    }
  }
  while(!q.empty()) {
    int x = q.front(), y = to[x];
    q.pop();
    vis[x] = 1;
    if (!vis[y]) {
      indeg[y] = 0;
      q.push(y);
    }
  }
}
void S(int x) {  //dfs扫路径
  vis[x] = 1;
  int y = to[x];
  if (!vis[y]) {
    S(y);
  }
}
int main() {
  for (cin >> mmt; mmt; mmt--) {
    set<char> e;  //看有多少种字母
    fill(to, to + kMaxC - 2, 0);
    fill(indeg, indeg + kMaxC - 2, 0);
    fill(vis, vis + kMaxC - 2, 0);
    cin >> s >> t;
    int l = s.size(), flag = 1;
    for (int i = 0; i < l; i++) {
      if (!to[s[i]] || to[s[i]] == t[i]) {
        to[s[i]] = t[i];
      } else {
        flag = 0;
      }
      e.insert(t[i]);
    }
    if (!flag) {  //如果有重复就-1
      cout << "-1\n";
      continue;
    }
    if (e.size() == (26 * 2)) {
      if (s == t) {  //如果两个字符串完全相等
        cout << "0\n";
      } else {  //如果没有点来过渡
        cout << "-1\n";
      }
      continue;
    }
    fill(to, to + kMaxC - 2, 0);  //这里要清空一下，因为要重新建边
    int tot = 0;
    for (int i = 0; i < l; i++) {
      if (!to[s[i]] && s[i] != t[i]) {
        tot++, indeg[t[i]]++, to[s[i]] = t[i];
      }
    }
    T();  //调用bfs
    for (int i = 'A'; i <= 'z'; i++) {
      if (!vis[i]) {
        tot++;
        S(i);  //扫路径
      }
    }
    cout << tot << '\n';
  }
  return 0;
}
```

---

## 作者：Xy_top (赞：0)

### 简要题意

一个字符串想要转换成另一个字符串。

每一次你可以选择两个字母，然后把第一个字符串中所有的第一个字母变成第二个字母，最小化步数或者输出 ``-1``。

如，当前是 ``aabc``，你选择两个字母是 ``b`` 和 ``d``，那么就变成了 ``aadc``。

### 分析

我们先来看样例，这里只有这个样例最重要（稍微简化了一下）。

``ABC``
``BCA``

 ``A`` 想转换成 ``B``，而 ``B`` 想转换成 ``C``，``C`` 想转换成 ``A``。

我们发现如果先拿 ``ABC`` 动手都不太行，所以我们加一个点 ``D``，``A`` 变成 ``D``，其他的先转换成想要的，``A`` 再回去。

### how to do it？

由此我们可以得出，如果有环那就需要没出现的点来帮助。

想到这里，就应该知道要建图了。如果 字母 ``a`` 想要转换成字母 ``b``，那么连一条 ``a`` -> ``b`` 的边。

建好图后，首先发现一个点出度为 ``2`` 显然不可能。紧接着发现这个图被分成了几个连通块，连通块内有环或无环。设环的大小为 $sz$。

无环：$sz-1$ 次就可以完成，因为总是有一个点没有想要变成的点。

有环：$sz + 1$ 次，因为要额外加点。

### 最后

这题的细节很多，我说一下。

首先，图中有环并且包含了所有的字母，那么无解。

其次，如果两个字母想要转换成同一字母，那么可以把第一个字母变成第二个再一起变成。

所以输入的时候我们就先改一下图再 dfs 就可以通过这道题啦！

---

## 作者：Light_Star_RPmax_AFO (赞：0)

### 前言

[传送门](https://www.luogu.com.cn/problem/P9013)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-p9013)

## 思路

首先分析一下，一看就是图论建模。

在一张所有点的出度都不超过 $1$ 的有向图中，组成的图会有三种， 一种一种来分类讨论。

1. 环

![](https://cdn.luogu.com.cn/upload/image_hosting/393yqwx0.png)


```
ABC
CAB
```

在这个时候我们需要把 $1$ 变为 $5$ 之后，才能进行操作，如果直接改变：


| ABC |
| :-----------: |
| CBC |
| CAC |
| BAB |

实际操作应该是：

| ABC |
| :-----------: |
| EAB |
| EAC |
| EAB |
| CAB |

所以说当图为环时，需要改变的是 $\text{边数} + 1$。

2. 链

![](https://cdn.luogu.com.cn/upload/image_hosting/ef3ntldv.png)

可以直接改变，需要改变的是边数。

3. 环+链

可以分裂成以上两种。

### 实现

> 边数 + 环数

如何判环？使用 **拓扑排序** 将所有环取出之后就可以得到答案。

# AC Code 

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
  int f = 1,x = 0;
  int ch = getchar();
  while(!isdigit(ch)){
	if(ch == '-')f = -1;
  	ch = getchar();
  }
  while(isdigit(ch)){
  	x = (x << 1) + (x << 3) + (ch ^ 48);
  	ch = getchar();
  }
  return x * f;
}
inline void print(int x){
  if(x > 9)print(x / 10);
  putchar(x % 10 + '0');
}

int to[200];int in[200], vis[200];

void topo(){
	queue<int> q;
	for(int i = 'a'; i <= 'z'; i++){
		if(!in[i])
			q.push(i);
	}
	for(int i = 'A'; i <= 'Z'; i++){
		if(!in[i])
			q.push(i);
	}
	while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = 1;
        int v = to[u];
        if(vis[v] == 0){
            in[v] = 0;
            q.push(v);
        }
    }
} 

void dfs(int u){
    vis[u] = 1;
    if(vis[to[u]] == 0)dfs(to[u]);
}
bool cn[200];
int sums = 0;
void solve(){
    memset(in, 0, sizeof(in));
    memset(vis, 0, sizeof(vis));
	memset(to, 0, sizeof(to));
    memset(cn, 0, sizeof(cn));
    sums = 0;
	string a, b;
	cin >> a >> b;
	for(int i = 0; i < a.length(); i++){
        if(!cn[b[i]])sums++, cn[b[i]] = 1;
		if(to[a[i]] == 0 || to[a[i]] == b[i]) {
            to[a[i]] = b[i];
        }else{
			cout << "-1" << endl; return ;
		}
	}
    if(sums == 52){
        if(a != b)
            cout << "-1" << endl;
        else cout << 0 << endl;
        return ;
    }
	int ans = 0;
    memset(to, 0, sizeof(to));
	for(int i = 0;i < a.length();i++){
		if(to[a[i]] == 0 && a[i] != b[i]){
			to[a[i]] = b[i];
			in[b[i]]++;
			ans++;
		}
	} 
    topo();
    for(int i = 'a'; i <= 'z'; i++){
        if(vis[i] == 0){
            ans++;
            dfs(i);
        }
    }
    for(int i = 'A'; i <= 'Z'; i++){
        if(vis[i] == 0){
            ans++;
            dfs(i);
        }
    }
    cout << ans << endl;
}

signed main(){
	int T = read();
	while(T--)
		solve();
  return 0;
}
```

---

