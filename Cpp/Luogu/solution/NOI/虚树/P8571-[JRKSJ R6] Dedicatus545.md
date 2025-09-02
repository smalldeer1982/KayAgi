# [JRKSJ R6] Dedicatus545

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/im5jyatm.png)

## 题目描述

对于字符串 $x,y$，定义 $w(x,y)$ 为 $x$ 在 $y$ 中的出现次数。

Index 给了你 $n$ 个字符串 $s_{1\dots n}$，$m$ 次询问，每次询问给定 $l,r,k$，求 $\max_{i=l}^r w(s_i,s_k)$。

## 说明/提示

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n,q\le$ | $\sum\vert s\vert\le$ | $\text{Score}$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |:----------: |
| $1$ | $2\times10^3$ | $10^4$ | $20$ | 无 |
| $2$ | $5\times10^4$ | $3\times 10^5$ | $20$ | 无
| $3$ | $10^5$ | $5\times10^5$ | $20$ | 所有字符串互不相同 |
| $4$ | $10^5$ | $5\times10^5$ | $40$ | 无

对于 $100\%$ 的数据，$1\le n,m\le 10^5$，$1\le \sum |s|\le 5\times 10^5$，$1\le l\le r\le n$，$1\le k\le n$。

Data：abruce&critnos&fjy666

## 样例 #1

### 输入

```
6 3
dedicatus
a
misaka
mikoto
mi
aaa
1 5 6
1 2 4
1 5 4```

### 输出

```
3
0
1```

# 题解

## 作者：世凪 (赞：10)

不知道为什么要猫树分治。

首先建出 AC 自动机。

考虑根号分治，记 $N = \sum |s|, B = \sqrt N$。

如果 $|s_k| \geq B$，不同的 $k$ 不会超过 $B$ 个，对于每个 $k$，把该串在 AC 自动机上的每个点权值加 $1$，然后求出每个点的子树权值之和。这样就可以知道每个点在 $s_k$ 的出现次数，用线段树维护区间最大值，这部分复杂度是 $O((n+N)\sqrt N + m \log n)$。

如果 $|s_k| < B$，考虑对 $s_k$ 建立虚树，如果某个虚树上的点 $x$ 到根的路径上存在某个 $[l, r]$ 的终止节点，说明答案至少是 $siz_x$（$siz_x$ 表示虚树中 $x$ 的子树大小）。

对 $r$ 做扫描线，维护每个点到根的最大标号，如果这个标号 $\geq l$ 说明合法，因此需要一个区间取 $\max$，单点查询的数据结构。可以用分块做到 $O(\sqrt N) - O(1)$。

这部分复杂度是 $O(N\log N + (n+m)\sqrt N)$。

---

## 作者：lzyqwq (赞：6)

想不到吧，SA 能做。

考虑把所有字符串接入分隔符拼接在一起然后后缀排序。

然后对于每个位置，记 $c_i$ 表示 **排名为 $i$** 的后缀来自哪个字符串。

对于 $s_i$，可以得到以她为前缀的后缀排名区间 $[L_i,R_i]$。那么 $s_k$ 在 $s_i$ 中的出现次数就是 $i$ 在 $[L_k,R_k]$ 内的出现次数。

现在问题转化成了有 $n$ 个区间，$q$ 次询问一个颜色在编号为 $l,\dots ,r$ 的区间中出现次数的最大值。直接套用[这题](https://www.luogu.com.cn/problem/P11750)做法即可。

记拼接后的字符串总长为 $L$，时间复杂度为 $\mathcal{O}(L\sqrt n)$，空间复杂度为 $\mathcal{O}(L\log L)$。

---

## 作者：IdnadRev (赞：4)

就差一点，烦。

为了方便，默认 $n$ 与总串长同阶。

一眼根号分治，大串平凡，可以算出所有串的答案。

小串猫树分治，我们只需处理：加入一个串、查询所有串在一个长度不超过根号的串中出现次数最大值。

根据 [[ZJOI2022] 众数](https://www.luogu.com.cn/problem/P8330) 的经典技巧，从大到小枚举这个出现次数，查询是否有一个串被包含这么多次。

取出查询串在 ACAM 上的虚树，我们只需枚举根号个结点到根的路径上是否存在加入过的串。

“单点标记，链查”转化成“区间标记，单点查”，而我们有 $O(n\log n)$ 次修改，$O(n\sqrt n)$ 次查询。

由于只需处理 0/1 信息，我们只需将序列压位后分块即可，复杂度 $O(n\sqrt n)$。

当然你也可以用 $O(n^{\epsilon})-O(1)$ 的分块做。

---

## 作者：critnos (赞：4)

[总长一定，可以考虑根号分治。](https://www.luogu.com.cn/problem/CF587F)

设 $sum=\sum|s|$。认为 $n=m$。

把每个 $s_k$ 分别处理。设根号分治阈为 $b$。

如果这个 $|s_k|>b$，这样的 $s_k$ 不超过 $\dfrac {sum} b$ 个。直接用 SAM 或者 ACAM 匹配每个串在 $s_k$ 中的出现次数，区间 $\max$ 用线段树等 $O(n)$ 建立的东西。

如果 $|s_k|\le b$，我们考虑用 $O(|s_k|)$ 的复杂度回答一个询问。

考虑分治。对于 $mid=(L+R)/2$，若询问 $l\le mid <r$，我们就用 $[l,mid]$ 和 $[mid+1,r]$ 的信息合并回答。

那么对 $s$ 序列分治。以回答 $[l,mid]$ 的询问为例，就是做一个 $mid\rightarrow L$ 的扫描线。

这个好像被称为“猫树分治”。

那么就是维护一个集合 $S$，支持插入一个字符串，和对于一个长度 $\le \sqrt n$ 的字符串 $x$，求 $\max w(S_i,x)$。

建立 ACAM。那么就是支持标记一个点为关键点，和给出 $O(\sqrt n)$ 个临时点，询问关键点的子树中的临时点数量的最大值。

对临时点建虚树（这个虚树最好进行一些预处理），按子树中临时点数量枚举，判断每个点到根的路径上是否存在关键点。

那么就是单点加链求和，转化为区间加单点求值。

比较糟糕的事情是单点加次数为 $O(n\log n)$，这里要用 $O(n^k)$，$k\in [0,0.5)$ 修改，$O(1)$ 查询的分块。

其实是这样的：

令块长 $b=\sqrt n$，整块打 tag，散块暴力加，得到一个 $O(\sqrt n)$ 的做法。

再分块一次，对打 tag 的过程使用上面的做法，设块长为 $b'$，则时间复杂度为 $O(b'+\sqrt{\dfrac n b'})$。解得 $b'=n^{1/3}$。

所以得到了一个 $O(n^{1/3})$ 修改的东西。或者对散块也用 $O(\sqrt n)$ 的做法维护，得到 $O(n^{1/4})$。


另一种方法是，转化为区间赋 $1$ 单点查询，这个可以在一般的分块上压位把修改的时间复杂度除掉 $w$，也可以做到比较可以的时间复杂度。

时间复杂度为 $O(n^{1+eps}\log n+\dfrac {sum^2} b+nb)$ 或者 $O(n\sqrt n+\dfrac {sum^2} b+nb)$，解得 $b=\dfrac {sum} {\sqrt n}$

因此时间复杂度 $O(sum\sqrt n)$，空间 $O(sumc)$，$c$ 为字符集大小。不过理论上是线性空间。

感觉不是很难啊，一年前的题还能作为现在的 F 吗。

---

## 作者：小超手123 (赞：2)

##### 题意：

对于字符串 $x,y$，定义 $w(x,y)$ 为 $x$ 在 $y$ 中的出现次数。

Index 给了你 $n$ 个字符串 $s_{1\dots n}$，$m$ 次询问，每次询问给定 $l,r,k$，求 $\max_{i=l}^r w(s_i,s_k)$。

$n,m \le 10^5, \sum|s| \le 5 \times 10^5$。

##### 分析：

先考虑暴力，先建出 AC 自动机的 $fail$ 树。对于一个询问，在 $fail$ 树上对 $s_{k}$ 的每个位置打个标记。查询时对于每个 $s_{i}$ 求子树内被标记的点的个数。

考虑根号分治，设 $N= \sum |s|,B= \sqrt N$，把 $fail$ 树节点数近似看成 $N$。

- 对于 $|s_{k}| \ge B$ 的询问：这样的询问的 $k$ 不超过 $\sqrt N$ 种。离线下来，对 $k$ 相同的一起处理。需要用到线段树。这部分时间复杂度 $O(N \sqrt N+m \log n)$。
- 对于 $|s_{k}| < B$ 的询问：对 $s_{k}$ 的每个位置建立一棵虚树。同样需要把 $k$ 相同的一起处理，否则会重复建虚树导致时间复杂度错误。对于虚树上的每个节点 $x$，如果 $x$ 到根节点的路径上存在一个点在 $[l,r]$ 里，执行 $ans \leftarrow siz_{x}$，其中 $siz_{x}$ 为子树内被标记的点的个数。现在问题变成了如何判断 $x$ 到根节点的路径中存在一个点在 $[l,r]$ 里。把刚刚想要知道的信息再离线下来。使用扫描线，$r$ 从小到大枚举，记 $h_{x}$ 表示点 $x$ 到根节点路径上的编号小于等于 $r$ 的点中编号最大的点的编号。判断 $h_{x} \ge l$ 即可。$r$ 变大时，做的是一个子树 $h_{i} = \max(h_{i},r)$ 操作。由于查询需要支持 $O(1)$，故使用分块，修改时间复杂度 $O(\sqrt N)$。 算完这个后就可以再跑一遍算答案了。这部分时间复杂度 $O(N \log N+ n \sqrt N)$。

总复杂度 $O(N \log N + m \log n+(n+N) \sqrt N)$。

---

## 作者：_Ch1F4N_ (赞：2)

既然字符串的总长一定，不妨对于每个询问中的 $s_k$ 的长度根号分治，假定分治阈值为 $B$。下面令 $L$ 为所有串长度总和。

对于长度大于 $B$ 的字符串，这样的不同字符串至多有 $\frac{L}{B}$ 个，考虑对于每个字符串建立 AC 自动机，然后暴力匹配出其他字符串的出现次数，并 $O(n)$ 建立一个线段树来回答询问，这一部分复杂度是 $O(\frac{L^2}{B} + q \log n)$ 的。

对于长度小于等于 $B$ 的字符串，它的前缀至多有 $B$ 个，映射到 AC 自动机上 $B$ 个点，我们要查询这些点在失配树上到祖先的路径上处于区间 $[l,r]$ 内的终止节点出现最多的终止节点出现次数。

不妨假定这个终止节点是点 $x$，根据 AC 自动机的性质，其产生贡献的前缀节点在失配树上 $x$ 的子树内，这提示我们，无论如何产生贡献的前缀节点都在某一个子树内。并且这个子树内的前缀节点也都产生了贡献。

所以考虑建出所有前缀节点的虚树，那么我们枚举虚树上的节点，问题转变为判断这个节点是否会产生贡献。

显然这是一个二维数点问题，不妨对 $r$ 做一遍扫描线，问题转变为点修链查最大值，再将其转变为子树修改单点查最大值，考虑用一个 $O(\sqrt L)$ 修改 $O(1)$ 查询的分块维护，由于虚树大小是 $O(B)$ 的，所以这部分复杂度是 $O(L \sqrt L + L \times B + L \log L)$。

显然当 $B = \sqrt L$ 的时候取到最小值 $O(L \sqrt L + q \log n + L \log L)$ 此时空间也是 $O(L)$ 的。

注意时间空间常数问题。

要是你被卡常了可以尝试一个经典的 trick，将遍历树的过程用在树的 dfs 序上扫描完成。

```cpp
#include <bits/stdc++.h>
#define query(x) (max(a[x],tag[bp[x]]))
using namespace std;
const int maxn = 1e5 + 5;
const int warma = 707;
string s[maxn];
int Len[maxn];
struct Query {
    Query(int L, int R, int ID) {
        l = L, r = R, id = ID;
    }
    int l, r, id;
};
int n, q;
vector<Query> Q[maxn];
int answer[maxn];
vector<int> Vtree;//虚树
int L[maxn * 5], R[maxn * 5], Node[maxn * 5];
int bp[maxn * 5];
int son[maxn * 5][26], fail[maxn * 5], rt, tot, dfncnt;
int sz[maxn * 5], Hson[maxn * 5], top[maxn * 5], dep[maxn * 5];
vector< pair<int, int>> w[maxn];
vector<int> edge[maxn * 5];
vector<int> fa[maxn];
vector<int> road[maxn * 5]; //虚树上的节点
int endpos[maxn * 5];
int found[maxn];
inline void insert(int pos) {
    int len = s[pos].size(), now = rt;

    for (register int i = 0; i < len; i = -~i) {
        if (son[now][s[pos][i] - 'a'] == 0)
            son[now][s[pos][i] - 'a'] = ++tot;

        now = son[now][s[pos][i] - 'a'];
        fa[pos].push_back(now);
    }

    if (endpos[now] == 0)
        found[pos] = endpos[now] = pos;
    else
        found[pos] = endpos[now];
}
inline void build() {
    queue<int> q;

    for (register int i = 0; i < 26; i = -~i)
        if (son[rt][i])
            fail[son[rt][i]] = rt, q.push(son[rt][i]);

    while (q.size() > 0) {
        int u = q.front();
        q.pop();

        for (register int i = 0; i < 26; i = -~i) {
            if (son[u][i]) {
                fail[son[u][i]] = son[fail[u]][i];
                q.push(son[u][i]);
            } else
                son[u][i] = son[fail[u]][i];
        }
    }

    for (register int i = 1; i <= tot; i = -~i) {
        edge[fail[i]].push_back(i);
    }
}
inline void dfs(int u) {
    L[u] = ++dfncnt, Node[dfncnt] = u, sz[u] = 1;

    for (register int i = 0; i < edge[u].size(); i = -~i) {
        dep[edge[u][i]] = dep[u] + 1;
        dfs(edge[u][i]);
        sz[u] += sz[edge[u][i]];

        if (Hson[u] == -1 || sz[edge[u][i]] > sz[Hson[u]])
            Hson[u] = edge[u][i];
    }

    R[u] = dfncnt;
}
inline void HLD(int u, int tp) {
    top[u] = tp;

    for (register int i = 0; i < edge[u].size(); i = -~i) {
        if (edge[u][i] != Hson[u])
            HLD(edge[u][i], edge[u][i]);
    }

    if (Hson[u] != -1)
        HLD(Hson[u], tp);
}
inline int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);

        u = fail[top[u]];
    }

    if (dep[u] < dep[v])
        swap(u, v);

    return v;
}
int tag[maxn], a[maxn * 5];
inline void cover(int l, int r, int v) {
    int bl = bp[l], br = bp[r];

    if (bl == br) {
        for (register int i = l; i <= r; i = -~i)
            a[i] = v;

        return ;
    }

    for (register int i = bl + 1; i < br; i = -~i)
        tag[i] = v;

    for (register int i = l; i <= bl * warma; i = -~i)
        a[i] = v;

    for (register int i = (br - 1) * warma + 1; i <= r; i = -~i)
        a[i] = v;
}
struct ASK {
    int l, k, id;
    ASK(int L, int K, int ID) {
        l = L, k = K, id = ID;
    }
};
int tr[maxn << 2];
inline void build(int cur, int lt, int rt) {
    if (lt == rt) {
        tr[cur] = sz[fa[lt].back()];
        return ;
    }

    int mid = (lt + rt) >> 1;
    build(cur << 1, lt, mid);
    build(cur << 1 | 1, mid + 1, rt);
    tr[cur] = max(tr[cur << 1], tr[cur << 1 | 1]);
}
inline int query_mx(int cur, int l, int r, int lt, int rt) {
    if (l <= lt && rt <= r)
        return tr[cur];

    if (r < lt || l > rt)
        return 0;

    int mid = (lt + rt) >> 1;
    return max(query_mx(cur << 1, l, r, lt, mid), query_mx(cur << 1 | 1, l, r, mid + 1, rt));
}
inline bool cmp(int A, int B) {
    return L[A] < L[B];
}
vector<ASK> ask[maxn];
inline void V_build(int u) {
    for (register int i = 0; i < road[u].size(); i = -~i) {
        int v = road[u][i];
        V_build(v);
        sz[u] += sz[v];
    }
}
inline bool cmp1(pair<int, int> A, pair<int, int> B) {
    return A.second > B.second;
}
inline string sread() {
    string ans;
    char ch = getchar();

    while (ch < 'a' || ch > 'z')
        ch = getchar();

    while (ch >= 'a' && ch <= 'z')
        ans += ch, ch = getchar();

    return ans;
}
inline int read() {
    bool flag = false;
    int x = 0;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            flag = true;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }

    return flag ? -x : x;
}
void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }

    if (x > 9)
        write(x / 10);

    putchar(x % 10 ^ 48);
}
int flag[maxn];
int B;
set<int> S;
int root;
int main() {
    memset(Hson, -1, sizeof(Hson));
    n = read();
    q = read();

    for (register int i = 1; i <= n; i = -~i)
        s[i] = sread(), Len[i] = s[i].size(), B += Len[i];

    B = sqrt(B) * 1.4;

    for (register int i = 1; i <= n; i = -~i)
        insert(i);

    for (register int i = 1; i <= q; i = -~i) {
        int l, r, k;
        l = read();
        r = read();
        k = read();

        if (Len[k] <= B) {
            flag[k] = 1;
            ask[r].push_back(ASK(l, k, i));
        } else {
            Q[found[k]].push_back(Query(l, r, i));
        }
    }

    build();
    dfs(rt);
    HLD(rt, rt);

    for (register int i = 1; i <= dfncnt; i++)
        bp[i] = (i - 1) / warma + 1;

    for (register int i = 0; i <= tot; i++)
        sz[i] = 0;

    for (register int i = 1; i <= n; i = -~i) {
        if (flag[i] == 0)
            continue;

        S.clear();
        Vtree.clear();
        root = -1;

        for (register int j = 0; j < fa[i].size(); j = -~j)
            Vtree.push_back(fa[i][j]), S.insert(fa[i][j]), sz[fa[i][j]]++;

        sort(Vtree.begin(), Vtree.end(), cmp);

        for (register int j = 0; j < Vtree.size() - 1; j = -~j) {
            int u = LCA(Vtree[j], Vtree[j + 1]);
            S.insert(u);
        }

        Vtree.clear();

        for (set<int>::iterator i = S.begin(); i != S.end(); ++i) {
            Vtree.push_back((*i));

            if (root == -1 || dep[(*i)] < dep[root])
                root = (*i);
        }

        sort(Vtree.begin(), Vtree.end(), cmp);

        for (register int j = 0; j < Vtree.size() - 1; j = -~j) {
            int u = LCA(Vtree[j], Vtree[j + 1]);
            road[u].push_back(Vtree[j + 1]);
        }

        V_build(root);

        for (register int j = 0; j < Vtree.size(); j = -~j)
            w[i].push_back(make_pair(Vtree[j], sz[Vtree[j]]));

        sort(w[i].begin(), w[i].end(), cmp1);

        for (register int j = 0; j < Vtree.size(); j = -~j) {
            sz[Vtree[j]] = 0;
            road[Vtree[j]].clear();
        }
    }

    for (register int i = 1; i <= n; i = -~i) {
        cover(L[fa[i].back()], R[fa[i].back()], i);

        for (register int j = 0; j < ask[i].size(); j = -~j) {
            for (register int k = 0; k < w[ask[i][j].k].size(); k = -~k) {
                if (query(L[w[ask[i][j].k][k].first]) >= ask[i][j].l) {
                    answer[ask[i][j].id] = max(answer[ask[i][j].id], w[ask[i][j].k][k].second);
                    break;
                }
            }
        }
    }

    for (register int i = 1; i <= n; i = -~i) {
        if (Q[i].size() > 0) {
            for (register int j = 0; j <= tot; j = -~j)
                sz[j] = 0;

            for (register int j = 0; j < fa[i].size(); j = -~j) {
                ++sz[fa[i][j]];
            }

            for (int u = dfncnt; u >= 1; --u) {
                if (Node[u] != rt)
                    sz[fail[Node[u]]] += sz[Node[u]];
            }

            build(1, 1, n);

            for (register int j = 0; j < Q[i].size(); j = -~j) {
                answer[Q[i][j].id] = query_mx(1, Q[i][j].l, Q[i][j].r, 1, n);
            }
        }
    }

    for (register int i = 1; i <= q; i = -~i)
        write(answer[i]), putchar('\n');

    return 0;
}
/*
6 1
a
aaa
dedicatus
misaka
mikoto
mi
1 2 2
*/
```


---

## 作者：王熙文 (赞：0)

想了三个多小时才想出来，数据结构水平有待提高。不过好像是一种新的做法，而且还爆标了，记录一下。

## 思路

设 $N=\sum |S|$。

考虑对字符串序列分块。对于每一个块，对每个 $s_k$ 要通过不遍历整个块的方法求出它的答案（否则复杂度就退化了）。从[这道题](https://www.luogu.com.cn/problem/P11750)的第一篇题解可以获得启发：可以对块内的信息进行一些压缩（比如删除被偏序的元素）让查询的复杂度变成常数。考虑对块内的字符串建 AC 自动机。普通的做法是对于每个 $s_k$ 的位置链加，并对特定的 $B$ 个位置求出 $\max$。考虑压缩信息，发现若一个点是另一个点子树内的点，则这个点可以删掉。经过这样操作之后，每个 $s_k$ 的位置贡献到的位置就是唯一的了，于是可以动态维护最大值。这部分的复杂度是 $\mathcal O(\dfrac{n}{B} N)$。

对于散块，求出 $s_i$ 在 $s_k$ 的次数就是在 AC 自动机上单点修改子树求和，于是可以对每个 $s_k$ 先加入它的贡献，算出所有包含它的查询，再删除它的贡献。这样将问题转化成了 $N$ 次单点修改，$\mathcal O(mB)$ 次区间求和。如果用 $\mathcal O(\sqrt{N})-O(1)$ 的做法，会带一个 $\mathcal O(N\sqrt{N})$。但是这个问题有更加优秀的解法。上述分块过程中转化成了两个对 $\sqrt{N}$ 长度的相同问题，于是可以继续使用这个做法。比如，再做一次可以做到 $\mathcal O(N^{0.25})-\mathcal O(1)$。一直做下去可以让单点修改的复杂度一直变小，不过查询也会一直变大，不会分析，总之这个问题的复杂度是非常小的。

取 $B=\sqrt{N}$，假设 $n,m$ 同阶，时间复杂度为 $\mathcal O(n\sqrt{N}+N\cdot N^k)$，其中 $k\in (0,0.5)$，取决于算法。

## 代码

非常好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int l[100010],r[100010],k[100010];
struct Query { int l,r,id; }; vector<Query> vec[100010];
int ans[100010];
string s[100010];
int B=500,L[100010],R[100010],pos[100010]; 
void init()
{
	for(int i=1; i<=(n+B-1)/B; ++i)
	{
		L[i]=R[i-1]+1,R[i]=L[i]+B-1;
		if(i==(n+B-1)/B) R[i]=n;
		for(int j=L[i]; j<=R[i]; ++j) pos[j]=i;
	}
}
struct Fenwick
{
	int tree[500010];
	void upd(int wz,int x)
	{
		for(int i=wz; i<=5e5+5; i+=i&-i) tree[i]+=x;
	}
	int get_sum(int wz)
	{
		int sum=0;
		for(int i=wz; i>0; i-=i&-i) sum+=tree[i];
		return sum;
	}
} fen;
int BB=1000,LL[500010],RR[500010],ppos[500010];
void iinit()
{
	for(int i=1; i<=((int)5e5+BB-1)/BB; ++i)
	{
		LL[i]=RR[i-1]+1,RR[i]=LL[i]+BB-1;
		if(i==((int)5e5+BB-1)/BB) RR[i]=5e5;
		for(int j=LL[i]; j<=RR[i]; ++j) ppos[j]=i;
	}
}
struct DS
{
	int sumx[500010],sumb[500010];
	void upd(int x,int y)
	{
		for(int i=x; i<=RR[ppos[x]]; ++i) sumx[i]+=y;
		for(int i=ppos[x]; i<=((int)5e5+BB-1)/BB; ++i) sumb[i]+=y;
	}
	int query(int l,int r)
	{
		if(ppos[l]==ppos[r]) return sumx[r]-(l==LL[ppos[l]]?0:sumx[l-1]);
		else return sumx[RR[ppos[l]]]-(l==LL[ppos[l]]?0:sumx[l-1])+sumb[ppos[r]-1]-sumb[ppos[l]]+sumx[r];
	}
} ds;
struct AC_Automation
{
	int tot=0,son[500010][26];
	bool vis[500010];
	int insert(string &s)
	{
		int now=0;
		for(char c:s)
		{
			if(son[now][c-'a']==0) son[now][c-'a']=++tot;
			now=son[now][c-'a'];
		}
		vis[now]=1;
		return now;
	}
	int fail[500010];
	queue<int> q;
	vector<int> e[500010];
	void get_fail()
	{
		for(int i=0; i<26; ++i)
		{
			if(son[0][i]!=0) q.push(son[0][i]),fail[son[0][i]]=0;
		}
		while(!q.empty())
		{
			int frn=q.front(); q.pop();
			for(int i=0; i<26; ++i)
			{
				if(son[frn][i]!=0) fail[son[frn][i]]=son[fail[frn]][i],q.push(son[frn][i]);
				else son[frn][i]=son[fail[frn]][i];
			}
		}
		for(int i=0; i<=tot; ++i) e[i].clear();
		for(int i=1; i<=tot; ++i) e[fail[i]].push_back(i);
	}
	int gx[500010],cnt[500010];
	void dfs1(int u,int now)
	{
		if(now==0 && vis[u]) now=u;
		gx[u]=now;
		for(int v:e[u]) dfs1(v,now);
	}
	int get_ans(string &s)
	{
		int now=0,ans=0;
		for(char c:s) now=son[now][c-'a'],ans=max(ans,(gx[now]==0?0:++cnt[gx[now]]));
		now=0;
		for(char c:s) now=son[now][c-'a'],--cnt[gx[now]];
		return ans;
	}
	int ttot=0,id[500010],siz[500010];
	void dfs2(int u)
	{
		id[u]=++ttot,siz[u]=1;
		for(int v:e[u]) dfs2(v),siz[u]+=siz[v];
	}
	void upd(string &s,int op)
	{
		int now=0;
		for(char c:s) now=son[now][c-'a'],ds.upd(id[now],op);
	}
	int query(int u)
	{
		return ds.query(id[u],id[u]+siz[u]-1);
	}
} ac1,ac2;
int vis[410][100010]; 
int now[100010];
int wz[100010];
int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; ++i) cin>>s[i];
	init();
	for(int i=1; i<=m; ++i)
	{
		cin>>l[i]>>r[i]>>k[i],vec[k[i]].push_back({l[i],r[i],i});
		for(int j=pos[l[i]]+1; j<=pos[r[i]]-1; ++j) vis[j][k[i]]=1;
	}
	for(int i=1; i<=(n+B-1)/B; ++i)
	{
		for(int j=0; j<=ac1.tot; ++j) memset(ac1.son[j],0,sizeof(ac1.son[j])),ac1.vis[j]=0;
		ac1.tot=0;
		for(int j=L[i]; j<=R[i]; ++j) ac1.insert(s[j]);
		ac1.get_fail(),ac1.dfs1(0,0);
		for(int j=1; j<=n; ++j)
		{
			if(vis[i][j]!=0) vis[i][j]=ac1.get_ans(s[j]);
		}
	}
	for(int i=1; i<=m; ++i)
	{
		for(int j=pos[l[i]]+1; j<=pos[r[i]]-1; ++j) ans[i]=max(ans[i],vis[j][k[i]]);
	}
	for(int i=1; i<=n; ++i) wz[i]=ac2.insert(s[i]);
	ac2.get_fail(),ac2.dfs2(0);
	iinit();
	for(int i=1; i<=n; ++i)
	{
		if(vec[i].empty()) continue;
		else
		{
			ac2.upd(s[i],1);
			for(Query j:vec[i])
			{
				if(pos[j.l]==pos[j.r])
				{
					for(int k=j.l; k<=j.r; ++k) ans[j.id]=max(ans[j.id],ac2.query(wz[k]));
				}
				else
				{
					for(int k=j.l; k<=R[pos[j.l]]; ++k) ans[j.id]=max(ans[j.id],ac2.query(wz[k]));
					for(int k=L[pos[j.r]]; k<=j.r; ++k) ans[j.id]=max(ans[j.id],ac2.query(wz[k]));
				}
			}
			ac2.upd(s[i],-1);
		}
	}
	for(int i=1; i<=m; ++i) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
好题/折磨题。

写完这题算是长见识了。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
下文中我们用 $k$ 代表字符串总长，也就是 $k$ 的范围是 $5\times10^5$，$n,m$ 的范围是 $10^5$。

题面都和 [CF587F Duff is Mad](https://www.luogu.com.cn/problem/CF587F) 差不多了，肯定是类似的思路先尝试想想。

考虑直接套做法，上来一个根号分治。

上一题里我们考虑根号分治后差分，把复杂度降下去，但是这个是 $\max$ 并不支持差分。

不管了还是尝试根号分治，设块长为 $B$，我们先考虑比较简单的长度 $>B$ 的。

还是一样的做法，对询问串整个链加，然后对于区间 $[l,r]$ 子树查。

因为不能差分，所以我们要换一个东西来查询区间的最大值。

可以考虑用线段树/ST 表。

但是分析下复杂度就会发现，如果用 ST 表，要对 $\frac{k}{B}$ 个串进行 $n\log n$ 的处理，如果不用 $O(n)$ 预处理的 ST 表是过不了的。

而查询次数顶满也就 $m$，所以肯定是把 $\log$ 放在询问上更合理。

然后对于子树查询，同理，因为我们要对 $\frac{k}{B}$ 个串都进行构造，所以复杂度要压在 $O(k)$ 处理出 $k$ 个点的子树值。

反正是静态的，直接前缀和预处理出来就行了。

至此第一部分完成了，总的复杂度 $O(n\frac{k}{B}+m\log n)$。

然后来考虑第二部分。

显然的是，在这个部分我们不能枚举区间 $[l,r]$，不然就会炸飞。

但是好处就是这个部分的点数只有 $B$。

考虑下，因为最多只有 $B$ 的长度，所以最大的答案就是 $B$。

把这个意义搞到 Fail 树上再理解一下。

那就是，我们对查询串链加后，子树查的值只会有 $B$ 种。

因为他有用的点就最多只有 $2B$ 个，因为每两个点召唤出来一个新点。

反正答案这么少，我们考虑找到每一个答案改变的断点。

也就是对于 $fa_i,i$，如果二者答案一样，我们就不要 $fa_i$。

不难发现，其实这些断点，组成的树，就是这 $B$ 个点的虚树。

因为你的答案只有在一个新的点和之前点的 LCA 处，会把二者的答案合并从而改变答案。

所以我们对于每个询问串，建一个属于他的虚树。

那对于虚树上的每个点 $i$，处理出 $s_i$，那么只要有一个 $[l,r]$ 的字符串的结尾点子树中有 $i$，答案就能取到 $s_i$。

我们不要考虑 $[l,r]$，还是考虑 $i$，就是根节点到 $i$ 的路径上有有 $[l,r]$ 字符串结尾点。

接着问题就变成，怎么做链查询是否存在编号 $[l,r]$ 的点了。

考虑扫描线，把所有区间 $[l,r]$ 的询问都扔到 $r$ 上去。

扫描线了，所以是单调的，我们只要一直覆盖就行了。

查询也直接查询即可，如果查询出来的最大值是 $\ge l$，就说明能取到。

因为我们现在放入的数只有 $[1,r]$，所以找到 $\ge l$ 的就是能取到。

考虑使用分块，这里显然是把块长取到 $\sqrt{k}$ 优，可以做到整块散块复杂度不变。

因为分块是 $O(\sqrt{k}),O(1)$ 的，所以我们的复杂度是 $O(k\log{k}+n\sqrt{k}+mB)$。

第一部分是虚树的复杂度，第二部分是分块修改，第三部分是查询询问。

所以总的复杂度就是 $O(n\frac{k}{B}+m\log n+k\log{k}+n\sqrt{k}+mB)$，所以最优块长应该是取 $\sqrt{\frac{nk}{m}}$。

即是 $O(m\log n+k\log{k}+n\sqrt{k}+\sqrt{nkm})$。

但是因为虚树和线段树的常数问题，实际写的话写个 $O(\sqrt{2k})$ 就能跑的飞快。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=1e5+10,M=5e5+10,blo=707,INF=0x3f3f3f3f,mod=998244353;
int n,m,k,p,B,le[N],ed[M],ans[N];char tt[M];
int cnt,dfn[M],si[M],sum[M],t[N<<2];
vector<int>e[M],g[M];vector<tuple<int,int,int>>q[N],Q[N];
vector<pair<int,int>>T[N];
int a[M],st[M],mp[M];
int bl[M],tag[M];
int tv[M][26],nxt[M];int tot=0;
vector<char>s[N];
inline void insert(int n,int id)
{
    int u=0;
    for(int i=1;i<=n;i++){s[id].emplace_back(tt[i]);if(!tv[u][tt[i]-'a']) tv[u][tt[i]-'a']=++tot;u=tv[u][tt[i]-'a'];}
    ed[id]=u;
}
inline void build()
{
    queue<int>q;
    for(int i=0;i<26;i++) if(tv[0][i]) nxt[tv[0][i]]=0,q.push(tv[0][i]);
    while(!q.empty())
    {
        int u=q.front();q.pop();e[nxt[u]].emplace_back(u);
        for(int i=0;i<26;i++)
            if(tv[u][i]) nxt[tv[u][i]]=tv[nxt[u]][i],q.push(tv[u][i]);
            else tv[u][i]=tv[nxt[u]][i];
    }
}
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='&'||c=='|'||c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void build(int p,int l,int r)
{
    if(l==r) return t[p]=sum[dfn[ed[l]]+si[ed[l]]-1]-sum[dfn[ed[l]]-1],void();
    build(ls,l,mid);build(rs,mid+1,r);t[p]=max(t[ls],t[rs]);
}
inline int query(int p,int l,int r,int s,int e)
{
    if(l>=s&&r<=e) return t[p];int res=0;
    if(mid>=s) res=query(ls,l,mid,s,e);
    if(mid<e) res=max(res,query(rs,mid+1,r,s,e));
    return res;
}
inline void init(int x)
{
    int u=0;for(int i=1;i<=p;i++) sum[i]=0;
    for(int i=0;i<le[x];i++) u=tv[u][s[x][i]-'a'],sum[dfn[u]]++;
    for(int i=1;i<=p;i++) sum[i]+=sum[i-1];build(1,1,n);
}
namespace tree_decomposition
{
    int fa[M],son[M],dep[M],top[M];
    inline void dfs1(int u,int ff)
    {
        fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;
        for(auto v:e[u])
        {
            if(v==ff) continue;
            dfs1(v,u);si[u]+=si[v];
            if(si[son[u]]<si[v]) son[u]=v;
        }
    }
    inline void dfs2(int u,int topf)
    {
        top[u]=topf;dfn[u]=++cnt;
        if(~son[u]) dfs2(son[u],topf);
        for(auto v:e[u])
        {
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
}
using namespace tree_decomposition;
inline void add(int u,int v){g[u].emplace_back(v);}
inline int dfs(int u,int x)
{
    int s=mp[u];for(auto v:g[u]) s+=dfs(v,x);
    T[x].emplace_back(dfn[u],s);mp[u]=0;g[u].clear();return s;
}
inline bool cmp(int x,int y){return dfn[x]<dfn[y];}
inline void build(int x)
{
    int cot=0,top=1,u=0;a[++cot]=0;
    for(int i=0;i<le[x];i++) u=tv[u][s[x][i]-'a'],mp[a[++cot]=u]=1;
    sort(a+1,a+1+cot,cmp);st[top]=a[1];
    for(int i=2;i<=cot;i++)
    {
        u=a[i];int lc=LCA(u,st[top]);
        while(1)
        {
            if(dep[lc]>=dep[st[top-1]])
            {
                if(lc!=st[top])
                {
                    add(lc,st[top]);
                    if(lc!=st[top-1]) st[top]=lc;
                    else top--;
                }
                break;
            }add(st[top-1],st[top]),top--;
        }st[++top]=u;
    }while(--top) add(st[top],st[top+1]);dfs(st[1],x);
}
inline void cov(int l,int r,int x)
{
    if(bl[l]==bl[r])
    {
        if(tag[bl[l]]) for(int i=(bl[l]-1)*blo+1;i<=min(bl[l]*blo,p);i++) a[i]=tag[bl[l]];
        tag[bl[l]]=0;for(int i=l;i<=r;i++) a[i]=x;return;
    }if(tag[bl[l]]) for(int i=(bl[l]-1)*blo+1;i<=bl[l]*blo;i++) a[i]=tag[bl[l]];tag[bl[l]]=0;
    if(tag[bl[r]]) for(int i=(bl[r]-1)*blo+1;i<=min(bl[r]*blo,p);i++) a[i]=tag[bl[r]];tag[bl[r]]=0;
    for(int i=l;i<=bl[l]*blo;i++) a[i]=x;for(int i=(bl[r]-1)*blo+1;i<=r;i++) a[i]=x;
    for(int i=bl[l]+1;i<bl[r];i++) tag[i]=x;
}
inline void solve()
{
    n=read(),m=read();for(int i=1;i<=n;i++) rd(tt,le[i]),k+=le[i],insert(le[i],i);B=sqrt(k)*1.4;
    for(int i=1,l,r,x;i<=m;i++)
    {
        l=read(),r=read(),x=read();
        if(le[x]>=B) Q[x].emplace_back(l,r,i);
        else q[r].emplace_back(l,x,i);
    }
    build();memset(son,-1,sizeof son);dfs1(0,0);dfs2(0,0);p=tot+1;
    for(int i=1;i<=n;i++) if(le[i]>=B)
    {
        init(i);
        for(auto [l,r,id]:Q[i]) ans[id]=query(1,1,n,l,r);
    }else build(i);
    for(int i=1;i<=p;i++) a[i]=0,bl[i]=(i-1)/blo+1;
    for(int i=1;i<=n;i++)
    {
        cov(dfn[ed[i]],dfn[ed[i]]+si[ed[i]]-1,i);
        for(auto [l,x,id]:q[i])
            for(auto [v,w]:T[x])
                if(max(tag[bl[v]],a[v])>=l)
                    ans[id]=max(ans[id],w);
    }
    for(int i=1;i<=m;i++) print(ans[i]),put('\n');
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Luciylove (赞：0)

折磨抽象的。

不难想到建出 ACAM。

先根号分治一把，你对于每个对大串就是平凡的暴力匹配，然后就是查询 $[l, r]$ 的一个 RMQ。

然后就是困难的大串了，观察到只有 $O(\sqrt n)$，你尝试对于这些点建出虚树是吧。那么一个序列上点 $v$ 的贡献无非就是满足子树内有一个虚树上的点 $x$，那么那个点的贡献就是 $sz_{x, k}$。

考虑扫描线 $1 \to n$，每次我们相当于对于 $p_i$ 的子树全部作用一次，扫到一个 $r$ 相当于遍历虚树，看下 $x$ 是否有贡献。

那你扫描线维护的就是节点是否有贡献，所以相当于维护一个上一次出现的端点 $l$，然后这个是区间取 $\max$，单点查询。不难使用 $O(\sqrt n) - O(1)$ 分块。

时间复杂度是 $O(L \log L + (N + L) \sqrt L + Q \log N )$。

注意到字符串可能相同，可以使用一些指针维护减少建虚树的空间。

```cpp
#define LUOGU
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")
#if defined(LOCAL) or not defined(LUOGU)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, r, l) for (int i = r; i >= l; --i)

using namespace std;

const int _ = 1e5 + 5, L = 5e5 + 50;


int read () {
    int ans = 0; char c = getchar(), last = ' ';
    while(c < '0' || c > '9') last = c,c = getchar();
    while(c >= '0' && c <= '9') ans = (ans << 1) + (ans << 3) + c - '0',c = getchar();
    return last == '-' ? - ans : ans;
}

bool MB;
int n, q;
int tot = 1, ch[L][26], fail[L], edp[_], iter[L], to[_];
vector <int> e[L], G[L];
vector <int> node[_];
vector <pair<int, int> > vT[_]; 

void insert (string s, int id) {
	int x = 1;
	rep(i, 0, s.size() - 1) {
		int c = s[i] - 'a';
		if (!ch[x][c])
			ch[x][c] = ++ tot;
		x = ch[x][c], node[id].push_back(x);
	}
	edp[id] = x;
	if (!iter[x]) iter[x] = id;
	else node[id].clear();  
	to[id] = iter[x];
}
void BFS () {
	queue <int> q; 
    rep(i, 0, 25) ch[0][i] = 1;
    q.push(1);
	while (! q.empty()) {
		int u = q.front(); q.pop();
		rep(i, 0, 25) {
			if (ch[u][i]) q.push(ch[u][i]), fail[ch[u][i]] = ch[fail[u]][i];
			else ch[u][i] = ch[fail[u]][i];
		}
		e[fail[u]].push_back(u);
	}
} 

int dfc, dL[L], dR[L], tr[L];
int sz[L], dep[L], son[L], cnt[L], top[L];
void dfs1 (int x, int fa) {
	dL[x] = ++ dfc, tr[dfc] = x;
	sz[x] = 1, dep[x] = dep[fa] + 1;
	for (int y : e[x]) {
		dfs1(y, x),
		sz[x] += sz[y];
		if (sz[y] > sz[son[x]]) son[x] = y;
	}
	dR[x] = dfc;
}
void dfs2 (int x, int tp) {
	top[x] = tp;
	if (son[x]) dfs2(son[x], tp);
	for (int y : e[x]) if (y ^ son[x]) dfs2(y, y);
}
int LCA (int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) 
			swap(x, y);
		x = fail[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

int mx[_ << 2];
void build (int x, int l, int r) {
	if (l == r) 
		return mx[x] = cnt[edp[l]], void();
	int mid = (l + r) >> 1;
	build(x * 2, l, mid), build(x * 2 + 1, mid + 1, r);
	mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
}
int query (int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr)
		return mx[x];
	int mid = (l + r) >> 1, ret = 0; 
	if (ql <= mid)
		ret = query(x * 2, l, mid, ql, qr);
    if (qr > mid)
		ret = max(ret, query(x * 2 + 1, mid + 1, r, ql, qr));
	return ret;
}

int block, tag[_], val[L];
void chk (int L, int R, int t) {
	int bl = (L - 1) / block + 1, br = (R - 1) / block + 1;
	if (bl == br) {
		for (int i = L; i <= R; i ++)
			val[i] = t;
		return ;
	}
	for (int i = bl + 1; i < br; i ++) tag[i] = t;
	for (int i = L; i <= bl * block; i ++) val[i] = t;
	for (int i = (br - 1) * block + 1; i <= R; i ++) val[i] = t;
}
int qVal (int x) { return max(val[x], tag[(x - 1) / block + 1]); }

struct complexQuery { int l, r, id; } ;
vector <complexQuery> Q[_], qv[_];

int ans[_];
bool masked[_];
int Slen;
string str[_];
bool cmp (int x, int y) { return dL[x] < dL[y]; }
	
bool NMMB;

int dfsVT (int x, int id) {
	for (int y : G[x]) cnt[x] += dfsVT(y, id);
	vT[id].push_back({x, cnt[x]});
	cnt[x] = 0, G[x].clear();
	return vT[id].back().second;
}

void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }

    if (x > 9)
        write(x / 10);

    putchar(x % 10 ^ 48);
}

int st[L], stp;
inline void ins(int x){
    if (stp == 1) { st[++ stp] = x; return;}
    int ance = LCA(x,st[stp]);
    while (stp > 1 && dep[ance] < dep[st[stp - 1]])
      G[st[stp - 1]].push_back(st[stp]),stp --;
    if (dep[ance] < dep[st[stp]]) G[ance].push_back(st[stp --]);
    if (!stp || st[stp] != ance) st[++ stp] = ance;
    st[++ stp] = x;
}

int main () {
	// cout << (&MB - &NMMB) / (1024 * 1024) << endl;
	n = read(), q = read();
	rep(i, 1, n)
		 cin >> str[i], insert(str[i], i), Slen += str[i].size();
	block = sqrt(Slen) * 1.4;
	rep(i, 1, q) {
		int l = read(), r = read(), k = read();
		if (str[k].size() <= block)
			qv[r].push_back({l, to[k], i}), masked[to[k]] = 1;
		else Q[to[k]].push_back({l, r, i});
	}
	BFS();
	dfs1(1, 1), dfs2(1, 1);
	rep(i, 1, n) if (Q[i].size() > 0) {
		for (int j = 1; j <= tot; j ++) cnt[j] = 0;
		for (int v : node[i]) cnt[v] ++;
		for (int j = tot; j >= 1; j --)
			cnt[fail[tr[j]]] += cnt[tr[j]];
		build(1, 1, n);
		for (complexQuery v : Q[i])
	 		ans[v.id] = query(1, 1, n, v.l, v.r);
	}

	rep(i, 1, n) {
		if (masked[i]) {

			for (int v : node[i]) cnt[v] ++;

			st[stp = 1] = 1;
			sort(node[i].begin(), node[i].end(), cmp);
			for (int j = 0; j < node[i].size(); j ++)
				ins(node[i][j]);
			while (stp) G[st[stp - 1]].push_back(st[stp]), stp --;

			dfsVT(1, i);
		}
	}
	block = sqrt(tot);
	rep(i, 1, n) {
		chk(dL[edp[i]], dR[edp[i]], i);		
		for (auto [l, k, id] : qv[i]) 
			for (auto [x, v] : vT[k]) {
				if (qVal(dL[x]) >= l) ans[id] = max(ans[id], v);
			}
	}
	rep(i, 1, q) {
		write(ans[i]), putchar('\n');
	}
	return 0;
}
/*
6 3
dedicatus
a
misaka
mikoto
mi
aaa
1 5 6
1 2 4
1 5 4
*/
```

---

