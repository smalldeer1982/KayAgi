# [JRKSJ R3] practiceZ

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/qpcumiv6.png)

## 题目描述

琴琴给了你两个长为 $n$ 的序列 $a,b$，请你支持三种操作共 $m$ 次：

1. `1 l r x`，将 $a$ 序列的区间 $[l,r]$ 中的所有数修改为 $x$。
2. `2 l r y`，将 $b$ 序列的区间 $[l,r]$ 中的所有数修改为 $y$。
3. `3 l r`，求 $\sum_{i=l}^r \sum_{j=1}^{b_i} a_j$。答案对 $2^{32}$ 取模。

## 说明/提示

**本题采用捆绑测试。**

注：原时间限制为 5s，较为卡常所以被管理改为 7s。

| $\text{Subtask}$ | $n\le$ | $m\le$ | 特殊性质 | 分值 | 子任务依赖 | 时间限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $500$ | $10^3$ | 无 | $10$ | 无 | $2\text{s}$ |
| $2$ | $10^4$ | $10^4$ | 无 | $10$ | $1$ | $2\text{s}$ |
| $3$ | $10^5$ | $10^5$ | 无 | $30$ | $1,2$ | $4\text{s}$ |
| $4$ | $5\times 10^5$ | $3\times 10^5$ |数据随机 | $20$ | 无 | $5\text{s}$ |
| $5$ | $5\times 10^5$ |  $3\times 10^5$ | 无 | $30$ | $1,2,3,4$ | $5\text{s}$ |


对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$1\le m\le 3\times 10^5$，$1\le a_i,x\le 10^9$，$1\le b_i,y\le n$。

## 样例 #1

### 输入

```
4 5
5 5 4 5
3 4 4 1
2 3 3 2
2 2 3 4
3 1 4
1 3 3 2
3 2 4```

### 输出

```
57
39```

## 样例 #2

### 输入

```
5 5
1 7 5 2 5
2 1 5 3 2
1 5 5 3
1 3 5 2
3 1 4
2 1 4 2
3 1 3```

### 输出

```
33
24```

## 样例 #3

### 输入

```
10 10
27 29 12 16 16 6 20 22 17 1
2 6 1 10 4 1 3 10 9 6
2 3 5 6
3 2 10
2 5 10 9
3 5 9
1 1 5 24
1 6 10 12
3 2 3
1 4 6 14
1 4 8 14
3 5 10```

### 输出

```
956
825
264
924```

# 题解

## 作者：critnos (赞：13)

下面认为 $m=\Theta(n)$。

对 $b$ 序列分块，块 $x$ 内维护 $\sum_{b_{id}\in x} \sum_{i=1}^{b_{id}} a_i$。

考虑 $a$ 序列的修改。区间推平不好做，考虑用颜色段均摊方法（ODT）转为区间加。那么要修改 $b$ 的每个块的值。

修改 $a_x$ 会对块内所有 $b_i\ge x$ 的 $b_i$ 做出贡献。

设值域数组 $t$（$t_i$ 表示 $b=i$ 的次数）。设区间加数为 $v$，则贡献为 $\sum_{i=l}^r \sum_{j=i}^n t_j \times v=v\sum_{i=l}^r \sum_{j=i}^n t_j$。用一些数据结构维护即可。

查询的时候，整块直接查，对于散块查询，需要对 $a$ 维护一个 $O(\sqrt n)$ 区间加，$O(1)$ 前缀求和的分块。

考虑 $b$ 序列的修改。对于整块修改可以直接打标记。散块操作的难点在于维护值域上的后缀和的区间求和。每个块维护一个 ODT，这样就可以插入/删除颜色了。现在要维护一个数据结构，支持：

$O(\sqrt n)$ 单点加，$O(1)$ 求 $\sum_{i=1}^x \sum_{j=i}^n t_j$。

分成两类计算。

* $j\le x$。对于这类数，$t_j$ 出现了 $j$ 次。那么这部分的贡献是 $\sum_{j=1}^x t_j \times j$。

* $j>x$。这类数每个数都出现了 $x$ 次。贡献为 $x\sum_{j=x+1}^n t_j$。

两类都可以用分块处理。

注意修改 $b$ 序列的时候同时维护每块的值。

为了做到线性空间，我们需要离线逐块处理。

在逐块处理的时候，要用一些手段让复杂度不退化到 $O(n^2)$。大概就是把 $1,2$ 操作的贡献分别算，以规避掉逐块处理时每块都要对 $a$ 数组维护分块的过程。

注意细节。

时间 $O(n\sqrt n)$，空间线性。

非常神奇的，每一处都恰好根号平衡。

卡常的话自己摸索一下？很快乐的。

btw，这个卡常还是叉姐以前教我的/流泪

---

## 作者：yinianxingkong (赞：10)

> 君の指先を舞ってる電光は、私の一生変わらない信仰であり、このレールガンだけが永遠に生きてる！

好，接下来我们进入正题。

查询一个区间所有数作为下标后的前缀和的和，并需要对两个数组作区间覆盖。

先来处理 b 的区间覆盖。因为这是一道毒瘤题，线段树一类的方法看上去无法简单维护，考虑分块。于是发现需要实现两个功能：查询散块单点前缀和，以及查询整块贡献和。

第一部分。支持区间覆盖求前缀和，容易想到线段树之类的，复杂度会多 $\log$。发现操作与查询次数不对等，考虑继续分块。区间覆盖的处理可以用 ODT 转为区间加。实现一个 $O(\sqrt{n})-O(1)$ 的序列分块即可。

第二部分。如果复杂度要根号，这一部分要做到 $O(1)$，只能对每个块预处理答案。考虑 a 的区间覆盖对 b 的影响。已经 ODT 转成了区间加。这一部分限制二维的，可以将区间加差分成前缀加，这样限制就成一维了。具体地，

$$
\begin{aligned}
&\sum_{i=1}^r\sum_{j=1}^{n}[b[j]\ge i]v
\\
=&v\sum_{j=1}^{n}\sum_{i=1}^r[b[j]\ge i]
\\
=&v\sum_{j=1}^{n}\min(r,b[j])
\end{aligned}
$$

这是一个经典问题，可以考虑维护块内 $< r$ 的数的和 和 $\ge r$ 的数的个数。值域分块可以做到 $O(\sqrt{n})-O(1)$。

对 b 的区间覆盖是平凡的，打上标记后在查询时特判即可，散块暴力重构。时空 $O(n\sqrt{n})-O(n\sqrt{n})$，空间爆炸了。

注意到可以离线，考虑空间复杂度的瓶颈。事实上值域分块相当于直接预处理了所有的答案，而修改次数只有 $O(n)$ 次。考虑每次少维护一点答案，也就是对时间分块。这样每一个时间块里只需要维护 $O(\sqrt{n})$ 种答案即可。求解答案时只需要块内多维护一个排好序的数组，双指针预处理即可。维护排序数组容易做到根号。复杂度 $O(n\sqrt{n})-O(n)$ 理论可过。

然后就是卡常，这题太卡了。

这里给几个建议：

1. 尽量减少对 a 数组前缀和查询的次数，哪怕 $O(1)$ 常数还是大。
2. 减少重复计算，减少冗余循环。
3. 全部使用无符号整形，相信编译器的优化。
4. 块长 $1024$，语音 C++98，编译器会出手优化。

代码太唐了，有需求私信。

---

## 作者：IdnadRev (赞：8)

还不错的题。

对 b 序列序列分块，那么只需维护整块答案和，以及 $O(1)$ 查询 a 序列的某个前缀和。

后者显然可以使用 $O(\sqrt n)$ 加 $O(1)$ 查的分块维护，重点在前者。

操作 1 使用颜色均摊转化成 $O(n)$ 次区间加，每次加完之后我们都得重构每个整块的答案，考虑贡献：

$$\sum_{i=l}^r\sum_{j}[b_j\geqslant i]v$$

差分成：

$$\sum_{i=1}^c\sum_{j}[b_j\geqslant i]v=v\sum_j\min(b_j,c)$$

那么我们就要在每个块内，对于每个值 $k$ 维护有多少个 $b_j=k$，并支持 $O(1)$ 的前缀和查询。

操作 2 整块可以打标记，上式维护平凡。每个散块颜色均摊一下，那么就变成了 $O(1)$ 个位置的修改，使用 $O(\sqrt n)-O(1)$ 分块维护即可。

复杂度 $O(n\sqrt n)$。

---

## 作者：Zzzcr (赞：6)

2024.10.11 最优解，写篇题解纪念一下。

把对 $a$ 序列的推平用 ODT 转成区间加，维护前缀和容易做到 $\mathcal{O}(\sqrt{n})\sim \mathcal{O}(1)$。对 $b$ 序列分块。对散块的查询用上述做法即可，所以只需要维护整块答案。

考虑两种操作分别对每个整块造成的影响：

对于序列 $a$ 的区间加 $(1,R,x)$，不难发现对 $b$ 序列的贡献即 $x\sum_i\min(b_i,R)$，差分一下即可。为了求出其对每一块的贡献，需要查询 $b$ 序列每一块中 $\le x$ 的数之和，以及 $>x$ 的数的数量。

直接维护这些东西很烦，考虑时间分块，动态维护每个块中 $\mathcal{O}(\sqrt{n})$ 种这个信息。

考虑区间 $b$ 推平操作，给每块维护一个 ODT，散块的推平次数就是均摊 $\mathcal{O}(1)$ 了，暴力修改，整块直接打 tag 即可。在这个过程中也顺便算出自身造成的影响，利用维护出的 $a$ 的前缀和即可。

于是做到了时间 $\mathcal{O}(n\sqrt{n})$ 空间 $\mathcal{O}(n)$，记得卡卡常，代码为符合 C++98 标准有点唐。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define rg register
#define mkp make_pair
#define fin(filename) freopen(#filename".in", "r", stdin)
#define fout(filename) freopen(#filename".out", "w", stdout)
#define file(filename) fin(filename), fout(filename)
#define _f(i, a, b) for (rg int i = a; i <= b; ++i)
#define _d(i, a, b) for (rg int i = a; i >= b; --i)
typedef unsigned int uint;
#define fi first
#define se second
#define all(container) container.begin(), container.end()
#define dubug() cerr << __LINE__ << '\n';

#define I inline
namespace IO {
	const int S = (1 << 21);
	char b[S], *m = b, *n = b, g[S], *p = g;
	I void f() { fwrite(g, 1, p - g, stdout), p = g; }
	struct R {
		I bool w(char c) { return 47 < c && c < 58; }
		I bool y(char c) { return c == ' ' || c == '\n' || c == '\r' || c == '\t'; }
		I char i() { if (m == n) n = (m = b) + fread(b, 1, S, stdin); return m == n ? ' ' : *m++; }
		template <class T> I R &operator>>(T &x) { char c = i(); T f = 1; for (x = 0; !w(c);) { if(c == '-') f = -1; c = i(); } while (w(c)) x *= 10, x += c ^ 48, c = i(); x *= f; return *this; }
		I R &operator>>(char *s) { int l = 0; char c; operator>>(c); for (; !y(c); s[l++] = c, c = i()) ; s[l] = '\0'; return *this; }
		I R &operator>>(char &c) { do c = i(); while (y(c)); return *this; }
	} cin;
	struct W {
		I void o(char c) { *p++ = c; if (p - g == S) f(); }
		template <class T> I W &operator<<(T x) { if (!x) return o(48), *this; if(x < 0) o('-'), x = -x; static int s[64], t = 0; while (x) s[++t] = x % 10, x /= 10; while (t) o(s[t--] + 48); return *this; }
		I W &operator<<(char c) { o(c); return *this; }
		template <class T> I W &operator<<(T *s) { int c = 0; while (s[c]) o(s[c++]); return *this; }
		~W() { f(); }
	} cout;
} ;

#define cin IO::cin
#define cout IO::cout

const int N = 5e5 + 5, S = 360, M = 3e5 + 5, T = 2500;

typedef pair<uint, uint> puu;
vector<int> toQ;
int n, m, s, num, bel[N], L[S], R[S], len[S], tot, lsh[N], szQ, posi[N];
uint sumA[S], preA[N], sum[S];
puu val[S][T + 5];
int tagB[S], tagA[S], a[N], b[N];
struct Opt { 
    int op, l, r, x;
    Opt() {}
    Opt(int _op, int _l, int _r, int _x)
        : op(_op), l(_l), r(_r), x(_x) {}
} p[N * 3];
struct opt { int l, r, x; } ret;
struct ODT {
    struct node {
        int l, r;
        mutable int v;
        node(int l, int r = 0, int v = 0) : l(l), r(r), v(v) {}
        bool operator<(const node a) const { return l < a.l; }
    } ;
    set<node> s;
    inline void init(int n, int *f) {
        _f(i, 1, n) s.insert(node(i, i, f[i]));
    }
    #define IT set<node>::iterator
    inline IT split(int pos) {
        IT it = s.lower_bound(node(pos));
        if(it != s.end() && it -> l == pos) return it;
        --it;
        if(it -> r < pos) return s.end();
        int l = it -> l, r = it -> r, v = it -> v;
        s.erase(it), s.insert(node(l, pos - 1, v));
        return s.insert(node(pos, r, v)).fi;
    }
    inline vector<opt> assign(int l, int r, int x) {
        vector<opt> ret; ret.clear();
        IT itr = split(r + 1), itl = split(l), iit = itl;
        for(; itl != itr; ++itl) ret.push_back((opt){itl -> l, itl -> r, itl -> v});
        s.erase(iit, itr);
        s.insert(node(l, r, x));
        return ret;
    }
} A, blk[S];
inline void brute_modifyA(int l, int r, uint x) {
    uint ret = 0, now = bel[l];
    _f(i, l, r) ret += x, preA[i] += ret;
    _f(i, r + 1, R[now]) preA[i] += ret;
    _f(i, now, num) sumA[i] += ret;
}
inline uint qC(int now, int c) {
    if(tagB[now]) {
        if(tagB[now] < c) return len[now] * tagB[now];
        return len[now] * c;
    }
    return val[now][posi[c]].se * c + val[now][posi[c]].fi;
}
inline void modifyA(int l, int r, int x) {
    _f(i, 1, num)
        sum[i] += x * (qC(i, r) - qC(i, l - 1));
    if(bel[l] == bel[r]) return brute_modifyA(l, r, x);
    brute_modifyA(l, R[bel[l]], x), brute_modifyA(L[bel[r]], r, x);
    uint ret = 0;
    _f(i, bel[l] + 1, bel[r] - 1)
        tagA[i] += x, ret += len[i] * x, sumA[i] += ret;
    _f(i, bel[r], num) sumA[i] += ret;
} 
inline uint queryPreA(int r) {
    return sumA[bel[r] - 1] + preA[r] + tagA[bel[r]] * (r - L[bel[r]] + 1);
}
inline void remove(int now, int l, int r, int x, bool flg = 0) {
    if(!flg) sum[now] -= queryPreA(x) * (r - l + 1);
    l = r - l + 1, r = x * l;
    _f(i, 0, szQ - 1) {
        if(x < toQ[i]) val[now][i].fi -= r;
        else val[now][i].se -= l;
    }
}
inline void push(int now, int l, int r, int x, bool flg = 0) {
    if(!flg) sum[now] += queryPreA(x) * (r - l + 1);
    l = r - l + 1, r = x * l;
    _f(i, 0, szQ - 1) {
        if(x < toQ[i]) val[now][i].fi += r;
        else val[now][i].se += l;
    }
}
inline void brute_modifyB(int now, int l, int r, int x) {
    if(tagB[now]) {
        vector<opt> ret = blk[now].assign(1, len[now], tagB[now]);
        _f(i, 0, (int)ret.size() - 1) remove(now, ret[i].l, ret[i].r, ret[i].x, 1);
        push(now, 1, len[now], tagB[now], 1);
        fill(b + L[now], b + R[now] + 1, tagB[now]);
        tagB[now] = 0;
    }
    vector<opt> ret = blk[now].assign(l - L[now] + 1, r - L[now] + 1, x);
    _f(i, 0, (int)ret.size() - 1) remove(now, ret[i].l, ret[i].r, ret[i].x);
    push(now, l - L[now] + 1, r - L[now] + 1, x);
    fill(b + l, b + r + 1, x);
}
inline void modifyB(int l, int r, int x) {
    if(bel[l] == bel[r]) return brute_modifyB(bel[l], l, r, x);
    brute_modifyB(bel[l], l, R[bel[l]], x);
    brute_modifyB(bel[r], L[bel[r]], r, x);
    fill(tagB + bel[l] + 1, tagB + bel[r], x);
    fill(sum + bel[l] + 1, sum + bel[r], s * queryPreA(x));
}
inline int query(int now, int l, int r) {
    if(tagB[now]) return queryPreA(tagB[now]) * (r - l + 1);
    uint ret = 0;
    _f(i, l, r) ret += queryPreA(b[i]);
    return ret;
}
void solve() {
    cin >> n >> m, s = sqrt(n * 4), num = (n / s) + !!(n % s);
    _f(i, 1, n) cin >> a[i];
    _f(i, 1, n) cin >> b[i];
    _f(i, 1, num) L[i] = R[i - 1] + 1, R[i] = R[i - 1] + s; R[num] = n;
    _f(i, 1, num) {
        _f(j, L[i], R[i]) bel[j] = i;
        len[i] = R[i] - L[i] + 1;
    }
    A.init(n, a);
    _f(i, 1, num) blk[i].init(len[i], b + L[i] - 1);
    _f(i, 1, num) {
        preA[L[i]] = a[L[i]];
        _f(j, L[i] + 1, R[i]) preA[j] = preA[j - 1] + a[j];
        sumA[i] = preA[R[i]] + sumA[i - 1];
    }
    _f(i, 1, num) _f(j, L[i], R[i]) sum[i] += queryPreA(b[j]);
    _f(i, 1, m) {
        int op, l, r, x; cin >> op >> l >> r;
        if(op == 1) {
            cin >> x;
            vector<opt> now = A.assign(l, r, x);
            _f(i, 0, (int)now.size() - 1)
                p[++tot] = Opt(1, now[i].l, now[i].r, x - now[i].x);
        } else if(op == 2) cin >> x, p[++tot] = Opt(2, l, r, x);
        else p[++tot] = Opt(3, l, r, 0);
    }
    int lft = 1, rgt = 1;
    for(; lft <= tot; ++rgt, lft = rgt) {
        memset(val, 0, sizeof val);
        toQ.clear();
        rg int cnt = 0;
        for(; rgt <= tot; ++rgt) {
            if(p[rgt].op == 1) toQ.push_back(p[rgt].l - 1), toQ.push_back(p[rgt].r), cnt += 2;
            if(cnt >= T) break;
        }
        rgt = min(rgt, (int)tot);
        if(toQ.size()) sort(all(toQ)), toQ.erase(unique(all(toQ)), toQ.end());
        szQ = toQ.size();
        _f(i, 0, szQ - 1) posi[toQ[i]] = i;
        rg int rqt = n + 1;
        fill(lsh, lsh + toQ[0], 0);
        _d(i, szQ - 1, 0) fill(lsh + toQ[i], lsh + rqt + 1, i + 1), rqt = toQ[i] - 1;
        _f(i, 1, num) {
            _f(j, L[i], R[i]) {
                const int id = lsh[b[j]];
                val[i][id].fi += b[j], val[i][id].se--;
            }
            val[i][0].se += len[i];
            _f(j, 1, szQ - 1) val[i][j].fi += val[i][j - 1].fi, val[i][j].se += val[i][j - 1].se;
        }
        _f(tim, lft, rgt) {
            const int op = p[tim].op, l = p[tim].l, r = p[tim].r, x = p[tim].x;
            if(op == 1) modifyA(l, r, x);
            else if(op == 2) modifyB(l, r, x);
            else {
                rg uint ans = 0;
                if(bel[l] == bel[r]) {
                    ans = query(bel[l], l, r);
                } else {
                    ans = query(bel[l], l, R[bel[l]]) + query(bel[r], L[bel[r]], r);
                    _f(i, bel[l] + 1, bel[r] - 1) ans += sum[i];
                }
                cout << ans << '\n';
            }
        }
    }
}

signed main() {
    solve();
    return 0;
}

// by zzzcr.
```

---

## 作者：Tx_Lcy (赞：6)

## 思路

与官方题解不同的维护方法。

首先考虑对 $b$ 序列分块，这样我们只需要支持查询整块答案以及 $\Theta(1)$ 求 $a$ 序列前缀和。

对 $a$ 序列前缀和的维护是简单的，直接分块即可。

考虑操作 $1$ 对整块答案的影响，首先显然可以将操作 $1$ 颜色段均摊后变成总共 $\Theta(n)$ 次区间加，考虑一个区间加 $(l,r,v)$ 的贡献：

$$\sum_{i=l}^r \sum_j [b_j \ge i] \times v$$

然后差分一下，转变成两个前缀相减：

$$\sum_{i=1}^c \sum_j [b_j \ge i] \times v$$

$$=\sum_j \min(b_j,c) \times v$$

我们现在需要解决的问题是对于整块查询 $\ge c$ 的元素个数以及 $<c$ 的元素和。

首先这可以轻松做到 $\Theta(n \sqrt n \log n)$，做到根号空间根号时间也是简单的。

由于查询的 $c$ 的种类以及修改操作只有 $\Theta(n)$ 种，但对整块的查询有 $\Theta(n \sqrt n)$ 个，考虑对查询分块，给每个块开 $\sqrt n$ 长度的数组，每次修改时动态维护这 $\sqrt n$ 种 $c$ 的答案。

接着是操作 $2$，这个的维护是简单的，对于整块直接打标记，散块暴力重构一下。

时间复杂度 $\Theta(n \sqrt n)$，空间复杂度 $\Theta(n)$。

需要一点卡常。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define uint unsigned int
#define all(x) (x).begin(),(x).end()
#define rep(i,j,k) for (uint i=j;i<=k;++i)
#define per(i,j,k) for (uint i=j;i>=k;--i)
int const N=5e5+10;
int const B=3000;
uint n,m,a[N],b[N],bel[N],co[N],L[N],R[N],smb[N],Q[N];
set< pair<uint,uint> >s;
struct Data_Structure{
    int const B=400;
    uint s1[N],s2[N],sg[N],tag[N],bel[N],L[N],R[N];
    inline void init(){
        memset(s1,0,sizeof(s1));
        memset(s2,0,sizeof(s2));
        memset(sg,0,sizeof(sg));
        memset(tag,0,sizeof(tag));
        rep(i,1,n){
            s1[bel[i]]+=a[i],bel[i]=(i-1)/B+1;
            if (!L[bel[i]]) L[bel[i]]=i;
            R[bel[i]]=i;
        }
        rep(i,1,n)
            if (bel[i]==bel[i-1]) s2[i]=s2[i-1]+a[i];
            else s2[i]=a[i];
        rep(i,1,bel[n]) sg[i]=sg[i-1]+s1[i];
    }
    inline void pushdown(uint x){
        if (!tag[x]) return;
        rep(i,L[x],R[x]) s2[i]=tag[x];
        rep(i,L[x]+1,R[x]) s2[i]+=s2[i-1];
        s1[x]=s2[R[x]],tag[x]=0;
    }
    inline void cover(uint l,uint r,uint V){
        rep(i,bel[l],bel[r]){
            uint idl=L[i],idr=R[i];
            if (idl<=l && r<=idr){
                pushdown(i);
                per(i,idr,idl+1) s2[i]-=s2[i-1];
                rep(i,l,r) s2[i]=V;
                rep(i,idl+1,idr) s2[i]+=s2[i-1];
                s1[i]=s2[idr];
            }else if (l<=idl && idr<=r) tag[i]=V,s1[i]=V*(idr-idl+1);
            else if (idl<l){
                //idl ... idr
                //     l  ... r
                pushdown(i);
                per(i,idr,idl+1) s2[i]-=s2[i-1];
                rep(i,l,idr) s2[i]=V;
                rep(i,idl+1,idr) s2[i]+=s2[i-1];
                s1[i]=s2[idr];
            }else{
                //    idl ... idr
                //l ...   r
                pushdown(i);
                per(i,idr,idl+1) s2[i]-=s2[i-1];
                rep(i,idl,r) s2[i]=V;
                rep(i,idl+1,idr) s2[i]+=s2[i-1];
                s1[i]=s2[idr];
            }
        }
        rep(i,bel[l],bel[n]) sg[i]=sg[i-1]+s1[i];
    }
    inline uint qry(uint k){
        return sg[bel[k]-1]+((tag[bel[k]])?(tag[bel[k]]*(k-L[bel[k]]+1)):(s2[k]));
    }
}DS;
uint tong[B+50][6005],tong2[B+50][6005];
vector<uint>V,nw;
uint gd,Id[N],Id2[N],tag[N],tag2[N];
int itr=-1,ct=-1,M;
inline uint cnt(uint x,uint y){
    if (co[x]) return (co[x]>=y)*(R[x]-L[x]+1);
    return tong2[x][Id2[y]];
}
inline uint tot(uint x,uint y){
    if (co[x]){
        if (co[x]<y) return co[x]*(R[x]-L[x]+1);
        else return 0;
    }
    return tong[x][Id[y]];
}
inline void pushdown(uint x){
    if (!co[x]) return;
    rep(j,0,gd) tong[x][j]=tong2[x][j]=0;
    rep(i,L[x],R[x]) b[i]=co[x];
    tong[x][tag[co[x]]]=(R[x]-L[x]+1)*co[x];
    tong2[x][tag2[co[x]]]=R[x]-L[x]+1;
    rep(j,1,gd) tong[x][j]+=tong[x][j-1],tong2[x][j]+=tong2[x][j-1];
    co[x]=0;
}
inline void Add(uint t,uint k){
    ++ct;
    if (ct>itr){
        nw.clear();
        int m=min((int)V.size()-1,ct+M);
        for (int i=itr+1;i<=m;++i) nw.push_back(V[i]);
        itr=m;
        sort(all(nw)),nw.erase(unique(all(nw)),nw.end());
        memset(tag,0,sizeof(tag));
        memset(tag2,0,sizeof(tag2));
        memset(Id,0,sizeof(Id));
        gd=0;
        uint la=1;
        for (auto i:nw){
            Id[i]=++gd;
            if (i>la){
                rep(j,la,i-1) tag[j]=gd;
                la=i;
            }
        }
        la=n;
        reverse(all(nw));
        gd=0;
        uint fl=0;
        for (auto i:nw){
            Id2[i]=++gd;
            if (la>=i){
                if (!fl){
                    per(j,la,i){tag2[j]=gd;if (!j) break;}
                }
                if (i) la=i-1;
                else fl=1;
            }
        }
        rep(i,1,n) if (!tag[i]) tag[i]=gd+2;
        rep(i,1,n) if (!tag2[i]) tag2[i]=gd+2;
        rep(i,1,bel[n])
            if (!co[i]) rep(j,0,gd) tong[i][j]=tong2[i][j]=0;
        rep(i,1,n) tong[bel[i]][tag[b[i]]]+=b[i],tong2[bel[i]][tag2[b[i]]]++;
        rep(i,1,bel[n])
            if (!co[i]) rep(j,1,gd) tong[i][j]+=tong[i][j-1],tong2[i][j]+=tong2[i][j-1];
    }
    rep(i,1,bel[n]){
        uint k1=cnt(i,t),k2=tot(i,t);
        smb[i]+=k1*t*k+k2*k;
    }
}
inline void work(uint L,uint R,uint ad){
    if (L>R) return;
    Add(R,ad),Add(L-1,-ad);
}
inline void update1(uint l,uint r,uint val){
    DS.cover(l,r,val);
    auto itl=s.lower_bound({l,0}),itr=s.upper_bound({r+1,0});
    if (itl->first!=l) --itl;
    vector< pair<uint,uint> >add;
    for (auto it=itl;it!=itr;++it){
        uint lef=it->first,rig=it->second;
        work(max(lef,l),min(rig,r),val-a[lef]);
        if (!(l<=lef && rig<=r)){
            if (lef<l) add.push_back({lef,l-1});
            if (r<rig) a[r+1]=a[lef],add.push_back({r+1,rig});
        }
    }
    s.erase(itl,itr),s.insert({l,r}),a[l]=val;
    for (auto i:add) s.insert(i);
}
inline void update2(uint l,uint r,uint val){
    uint S=DS.qry(val);
    if (bel[l]==bel[r]){
        if (!co[bel[l]]){
            per(i,gd,1) tong[bel[l]][i]-=tong[bel[l]][i-1],tong2[bel[l]][i]-=tong2[bel[l]][i-1];
            rep(i,l,r) tong[bel[l]][tag[b[i]]]-=b[i],tong2[bel[l]][tag2[b[i]]]--,b[i]=val,tong[bel[l]][tag[val]]+=val,tong2[bel[l]][tag2[b[i]]]++;
            rep(i,1,gd) tong[bel[l]][i]+=tong[bel[l]][i-1],tong2[bel[l]][i]+=tong2[bel[l]][i-1];
            smb[bel[l]]=0;
            rep(i,L[bel[l]],R[bel[l]])
                smb[bel[l]]+=DS.qry(b[i]);
        }else{
            uint all=R[bel[l]]-L[bel[l]]+1,del=r-l+1;
            rep(j,L[bel[l]],R[bel[l]]) b[j]=co[bel[l]];
            rep(j,l,r) b[j]=val;
            smb[bel[l]]=DS.qry(co[bel[l]])*(all-del)+DS.qry(val)*del;
            rep(j,0,gd){
                tong[bel[l]][j]=tong2[bel[l]][j]=0;
                if (j>=tag[co[bel[l]]]) tong[bel[l]][j]+=co[bel[l]]*(all-del);
                if (j>=tag[val]) tong[bel[l]][j]+=val*del;
                if (j>=tag2[co[bel[l]]]) tong2[bel[l]][j]+=all-del;
                if (j>=tag2[val]) tong2[bel[l]][j]+=del;
            }
            co[bel[l]]=0;
        }
        return;
    }
    rep(i,bel[l],bel[r]){
        uint lef=L[i],rig=R[i];
        if (l<=lef && rig<=r) co[i]=val,smb[i]=(rig-lef+1)*S;
        else if (lef<l){
            //lef ... rig
            //     l  ... r
            if (!co[i]){
                smb[i]=0;
                per(j,gd,1) tong[i][j]-=tong[i][j-1],tong2[i][j]-=tong2[i][j-1];
                rep(j,l,rig) tong[i][tag[b[j]]]-=b[j],tong2[i][tag2[b[j]]]--,b[j]=val,tong[i][tag[b[j]]]+=b[j],tong2[i][tag2[b[j]]]++;
                rep(j,1,gd) tong[i][j]+=tong[i][j-1],tong2[i][j]+=tong2[i][j-1];
                rep(j,L[i],R[i]) smb[i]+=DS.qry(b[j]);
            }else{
                uint all=R[i]-L[i]+1,del=rig-l+1;
                rep(j,L[i],R[i]) b[j]=co[i];
                rep(j,l,rig) b[j]=val;
                smb[i]=DS.qry(co[i])*(all-del)+DS.qry(val)*del;
                rep(j,0,gd){
                    tong[i][j]=tong2[i][j]=0;
                    if (j>=tag[co[i]]) tong[i][j]+=co[i]*(all-del);
                    if (j>=tag[val]) tong[i][j]+=val*del;
                    if (j>=tag2[co[i]]) tong2[i][j]+=all-del;
                    if (j>=tag2[val]) tong2[i][j]+=del;
                }
                co[i]=0;
            }
        }else{
            //    lef ... rig
            //l ...   r
            if (!co[i]){
                smb[i]=0;
                per(j,gd,1) tong[i][j]-=tong[i][j-1],tong2[i][j]-=tong2[i][j-1];
                rep(j,lef,r) tong[i][tag[b[j]]]-=b[j],tong2[i][tag2[b[j]]]--,b[j]=val,tong[i][tag[b[j]]]+=b[j],tong2[i][tag2[b[j]]]++;
                rep(j,1,gd) tong[i][j]+=tong[i][j-1],tong2[i][j]+=tong2[i][j-1];
                rep(j,L[i],R[i]) smb[i]+=DS.qry(b[j]);
            }else{
                uint all=R[i]-L[i]+1,del=r-lef+1;
                rep(j,L[i],R[i]) b[j]=co[i];
                rep(j,lef,r) b[j]=val;
                smb[i]=DS.qry(co[i])*(all-del)+DS.qry(val)*del;
                rep(j,0,gd){
                    tong[i][j]=tong2[i][j]=0;
                    if (j>=tag[co[i]]) tong[i][j]+=co[i]*(all-del);
                    if (j>=tag[val]) tong[i][j]+=val*del;
                    if (j>=tag2[co[i]]) tong2[i][j]+=all-del;
                    if (j>=tag2[val]) tong2[i][j]+=del;
                }
                co[i]=0;
            }
        }
    }
}
inline uint query(uint l,uint r){
    uint ans=0;
    if (bel[l]==bel[r]){
        if (co[bel[l]]){
            ans+=DS.qry(co[bel[l]])*(r-l+1);
        }else{
            rep(i,l,r) ans+=DS.qry(b[i]);
        }
        return ans;
    }
    if (co[bel[l]]){
        ans+=DS.qry(co[bel[l]])*(R[bel[l]]-l+1);
    }else{
        rep(i,l,R[bel[l]]) ans+=DS.qry(b[i]);
    }
    if (co[bel[r]]){
        ans+=DS.qry(co[bel[r]])*(r-L[bel[r]]+1);
    }else{
        rep(i,L[bel[r]],r) ans+=DS.qry(b[i]);
    }
    rep(i,bel[l]+1,bel[r]-1) ans+=smb[i];
    return ans;
}
uint oop[N],leff[N],rigg[N],xxx[N],aa[N],bb[N];
inline void Work(uint L,uint R,uint ad){
    if (L>R) return;
    V.push_back(R),V.push_back(L-1);
}
inline void Update1(uint l,uint r,uint val){
    DS.cover(l,r,val);
    auto itl=s.lower_bound({l,0}),itr=s.upper_bound({r+1,0});
    if (itl->first!=l) --itl;
    vector< pair<uint,uint> >add;
    for (auto it=itl;it!=itr;++it){
        uint lef=it->first,rig=it->second;
        Work(max(lef,l),min(rig,r),val-a[lef]);
        if (!(l<=lef && rig<=r)){
            if (lef<l) add.push_back({lef,l-1});
            if (r<rig) a[r+1]=a[lef],add.push_back({r+1,rig});
        }
    }
    s.erase(itl,itr),s.insert({l,r}),a[l]=val;
    for (auto i:add) s.insert(i);
}
void solve(){
    cin>>n>>m;
    rep(i,1,n) cin>>a[i],aa[i]=a[i];
    rep(i,1,n) cin>>b[i],bb[i]=b[i];
    rep(i,1,n) Q[i]=Q[i-1]+a[i];
    rep(i,1,n){
        bel[i]=(i-1)/B+1;
        if (!L[bel[i]]) L[bel[i]]=i;
        R[bel[i]]=i,smb[bel[i]]+=Q[b[i]];
    }
    DS.init();
    rep(i,1,n) s.insert({i,i});
    rep(i,1,m){
        cin>>oop[i];
        switch (oop[i]){
            case 1:{
                cin>>leff[i]>>rigg[i]>>xxx[i];
                break;
            }
            case 2:{
                cin>>leff[i]>>rigg[i]>>xxx[i];
                break;
            }
            case 3:{
                cin>>leff[i]>>rigg[i];
                break;
            }
        }
    }
    rep(i,1,m){
        uint op=oop[i];
        switch (op){
            case 1:{
                uint l=leff[i],r=rigg[i],x=xxx[i];
                Update1(l,r,x);
                break;
            }
            case 2:{
                break;
            }
            case 3:{
                break;
            }
        }
    }
    M=6000;
    rep(i,1,n) a[i]=aa[i],b[i]=bb[i],Q[i]=Q[i-1]+a[i];
    DS.init(),s.clear();
    rep(i,1,n) s.insert({i,i});
    rep(i,1,m){
        uint op=oop[i];
        switch (op){
            case 1:{
                uint l=leff[i],r=rigg[i],x=xxx[i];
                update1(l,r,x);
                break;
            }
            case 2:{
                uint l=leff[i],r=rigg[i],x=xxx[i];
                update2(l,r,x);
                break;
            }
            case 3:{
                uint l=leff[i],r=rigg[i];
                cout<<query(l,r)<<'\n';
                break;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    uint t=1;
    // cin>>t;
    while (t--) solve();
    cerr<<"Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
    return 0;
}
```

---

## 作者：lzyqwq (赞：4)

人话翻译一下官方题解。

> - 琴琴给了你两个长为 $n$ 的序列 $a,b$，请你支持三种操作共 $m$ 次：
>
>    -  `1 l r x`，将 $a$ 序列的区间 $[l,r]$ 中的所有数修改为 $x$。
>    -  `2 l r y`，将 $b$ 序列的区间 $[l,r]$ 中的所有数修改为 $y$。
>    -  `3 l r`，求 $\sum_{i=l}^r \sum_{j=1}^{b_i} a_j$。答案对 $2^{32}$ 取模。
> - $n\le 5\times 10^5$，$m\le 3\times 10^5$。

考虑以 $B=\mathcal{O}(\sqrt n)$ 为块长分块。对于一个块 $(\text{bl},\text{br},\text{id})$，维护 $\text{ans}_\text{id}=\sum\limits_{i=\text{bl}}^{\text{br}}\sum\limits_{j=1}^{b_i}a_j$。那么对于一次查询，可以直接累加整的 $\text{ans}_{\text{id}}$ 和 $\mathcal{O}(\sqrt n)$ 个散块元素。

---

**`1` 操作**

考虑颜色段均摊转化为 $\mathcal{O}(n+m)$ 次 $a$ 序列区间加。为了配合散块查询，我们需要支持：

> $\mathcal{O}(\sqrt n)$ 区间加，$\mathcal{O}(1)$ 前缀和查询。

记 $s_i=\sum\limits_{j=1}^ia_j$，考虑将其表示成 $s_i=k_ii+v_i$ 的形式，则 $a$ 的区间加可以转化成 $\mathcal{O}(1)$ 次 $k,v$ 的区间加。查询就是单点查询 $k_i,v_i$ 的值。可以考虑开两个 $\mathcal{O}(\sqrt n)-\mathcal{O}(1)$ 区间加单点查的分块维护，但是这题卡常，不得不写在同一个分块里。

再考虑其对整块答案的影响。考虑一个位置 $a_j$ 对块中所有 $b_i$ 为右端点的前缀的贡献。未被区间加的 $a_j$ 贡献不变。被区间加的位置的贡献会增加加数乘以贡献次数。

若一次区间加为 $(l,r,v)$，则块内答案的增量为：

$$\sum\limits_{j=l}^rv\sum\limits_{i=\text{bl}}^{\text{br}}[j\le b_i]=v\sum\limits_{j=l}^r\sum\limits_{i=\text{bl}}^{\text{br}}[j\le b_i]$$

考虑将上式差分，则只需要知道 $\sum\limits_{j=1}^r\sum\limits_{i=\text{bl}}^{\text{br}}[j\le b_i]$ 的值。我们有：

$$\sum\limits_{j=1}^r\sum\limits_{i=\text{bl}}^{\text{br}}[j\le b_i]=\sum\limits_{i=\text{bl}}^{{\text{br}}}\sum\limits_{j=1}^r[j\le b_i]=\sum\limits_{i=\text{bl}}^{{\text{br}}}\min\{r,b_i\}$$

拆 $\min$，由于有 $\mathcal{O}((n+m)\sqrt n)$ 次整块修改，所以要支持 $\mathcal{O}(1)$ 查询一个值域区间 $[l,r]$ 内 $b_i$ 的个数以及和。用某种数据结构维护即可。至于是什么数据结构，你先别急，这需要去配合接下来的操作讲。

时间复杂度 $\mathcal{O}((n+m)\sqrt n)$。

---

**`2` 操作**

整块修改打区间覆盖标记，然后用被覆盖的数乘以块的大小更新块内答案。

至于散块，考虑每个块内的 $b_i$ 颜色段均摊，由于散块修改一共 $\mathcal{O}(m)$ 次，因此一共会带来 $\mathcal{O}(n+m)$ 个 $b_i$ 颜色段。现在需要支持散块内插入和删除颜色。此时会有 $\mathcal{O}(n+m)$ 次修改上一部分中的某种数据结构中 $b_i$ 权值和以及个数。使用 $\mathcal{O}(\sqrt n)-\mathcal{O}(1)$ 的值域分块维护即可。同样的，为了卡常需要写在同一个分块里。

这个值域分块保留**上一次非整块修改的信息**，那么只有散块覆盖的时候才需要重构。有标记的时候，查询上式可以直接判断标记和 $r$ 的大小计算。

时间复杂度 $\mathcal{O}((n+m)\sqrt n)$。**空间复杂度 $\mathcal{O}(n\sqrt n)$，因为要对每个块开一个值域分块。**

---

**空间优化**

考虑离线逐块处理。但是你发现处理每个块时都需要维护 $a$，时间会退化成 $\mathcal{O}(n^2)$。但是注意到需要查询 $a$ 仅出现在 `2` 操作的整块、散块修改重构块内答案。对于整块重构块内答案，可以先考虑按顺序扫一遍操作，然后记录覆盖数 $v$ 对应的前缀和，重构时访问记录的值即可。对于散块重构块内答案，由于一共只有 $\mathcal{O}(m)$ 次，因此考虑在按顺序扫操作重构散块信息的时候记录对应的散块答案。离线逐块处理遇到 `2` 操作对于当前块的散块修改时，直接继承记录的信息即可。

空间复杂度  $\mathcal{O}(n+m)$。

---

**卡常**

- 上文提到的，不要开过多的值域分块，可以合并一些。
- 值域分块块长取 $B=512$，$b$ 序列分块取块长 $F\in[2000,2500]$。
- 查询一个位置所在块编号时，可以使用位运算 `(x - 1 >> 9) + 1`，比预处理后访问数组快不少。

最后也是成功跑进了原时限。[提交记录](https://www.luogu.com.cn/record/205148135)。

---

**代码**

不卡常大概写了 4.7 KB，不算很难写。卡完之后写了 5.5 KB。为了符合 C++98 标准写的有点抽象，但是这题好像 C++98 真不快。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define int unsigned
#define IT set<Tp>::iterator
#define IL inline
#define be(x) (((x) - 1 >> 9) + 1)
using namespace std; const int N = 500005, M = 2e6, K = 1000; bool vs[N];
int n, q, a[N], b[N], bl[N], br[N], B, o[N], cq, cl[M],
    fl[N], fr[N], fe[N], F, pa[N], pb[N], vc[N], L, R, tag, ans, id;
struct QR { int op, l, r, x; } qr[M]; pair<int, int> sk[2][M];
struct Tp { int l, r, c; IL bool operator<(const Tp &o) const { return l < o.l; } };
struct ODT {
	set<Tp> s; IL void clr() { s.clear(); }
	IL void ins(int l, int r, int c) { s.insert(Tp{l, r, c}); }
	IL IT spl(int x) {
		IT i = s.lower_bound({x, 0, 0}); if (i != s.end() && i->l == x) return i;
		Tp j = *(--i); s.erase(i); s.insert(Tp{j.l, x - 1, j.c});
		return s.insert(Tp{x, j.r, j.c}).fi;
	}
	IL vector<Tp> cov(int l, int r, int c) {
		IT ir = spl(r + 1), il = spl(l); vector<Tp> ret;
		for (IT it = il; it != ir; ++it) ret.push_back(*it);
		s.erase(il, ir); s.insert(Tp{l, r, c}); return ret;
	}
} odt;
struct BLK {
	int a0[N], t0[K], a1[N], t1[K];
	IL void C() {
		memset(a0, 0, sizeof a0); memset(a1, 0, sizeof a1);
		memset(t0, 0, sizeof t0); memset(t1, 0, sizeof t1);
	}
	IL void U(int x, int v) {
		for (int i = be(x) + (x != bl[be(x)]); i <= be(n); ++i)
			t0[i] += v, t1[i] += v * x;
		if (x != bl[be(x)])
			for (int i = x; i <= br[be(x)]; ++i) a0[i] += v, a1[i] += v * x;
	}
	IL int Q(int x) {
		return a1[x] + t1[be(x)] + x * (a0[n] + t0[be(n)] - a0[x] - t0[be(x)]);
	}
} b1;
struct RAPQ {
	int a0[N], t0[K], a1[N], t1[K];
	IL void I() { for (int i = 1; i <= n; ++i) a0[i] = pa[i]; }
	IL int Q(int x) { return x * (a1[x] + t1[be(x)]) + a0[x] + t0[be(x)]; }
	IL void suf(int x, int v) {
		for (int i = be(x) + (x != bl[be(x)]); i <= be(n); ++i)
			t0[i] += (1 - x) * v, t1[i] += v;
		if (x != bl[be(x)])
			for (int i = x; i <= br[be(x)]; ++i) a0[i] += (1 - x) * v, a1[i] += v;
	}
	IL void U(int l, int r, int v) { suf(l, v); if (r ^ n) suf(r + 1, -v); }
} ds;
struct BLKc {
	int a[N], t[K];
	void U(int id, int l, int r, int v, bool o) {
		if (fe[l] == fe[r]) {
			for (int i = l; i <= r; ++i) a[i] = v;
			if (t[fe[l]]) {
				for (int i = fl[fe[l]]; i < l; ++i) a[i] = t[fe[l]];
				for (int i = fr[fe[l]]; i > r; --i) a[i] = t[fe[l]];
				sk[o][id].se = (r - l + 1) * ds.Q(v) +
				               (fr[fe[l]] - fl[fe[l]] + l - r) * ds.Q(t[fe[l]]);
				t[fe[l]] = 0;
			} else {
				for (int i = l; i <= r; ++i) a[i] = v;
				sk[o][id].se = ds.Q(v) * (r - l + 1);
				for (int i = fl[fe[l]]; i < l; ++i) sk[o][id].se += ds.Q(a[i]);
				for (int i = fr[fe[l]]; i > r; --i) sk[o][id].se += ds.Q(a[i]);
			}
			return void(sk[o][id].fi = fe[l]);
		}
		U(id, l, fr[fe[l]], v, 0); U(id, fl[fe[r]], r, v, 1);
		for (int i = fe[l] + 1; i < fe[r]; ++i) t[i] = v;
	}
	int qs(int l, int r) {
		if (fe[l] == fe[r]) {
			if (t[fe[l]]) return ds.Q(t[fe[l]]) * (r - l + 1);
			int k = 0; for (int i = l; i <= r; ++i) k += ds.Q(a[i]); return k;
		}
		return qs(l, fr[fe[l]]) + qs(fl[fe[r]], r);
	}
	IL void I() { for (int i = 1; i <= n; ++i) a[i] = b[i]; }
} bc;
IL int pre(int x) { return x ? tag ? min(tag, x) * (R - L + 1) : b1.Q(x) : 0; }
IL void add(int l, int r, int v) { ans += v * (pre(r) - pre(l - 1)); }
IL void cov(int ql, int qr, int qc) {
	if (tag) {
		vector<Tp> u = odt.cov(L, R, tag);
		for (int i = 0, l, r, c; i < u.size(); ++i)
			l = u[i].l, r = u[i].r, c = u[i].c, vs[c] = 1, vc[c] -= r - l + 1;
		for (int i = 0, l, r, c; i < u.size(); ++i) {
			l = u[i].l, r = u[i].r, c = u[i].c;
			if (vs[c]) b1.U(c, vc[c]), vs[c] = vc[c] = 0;
		}
		b1.U(tag, R - L + 1);
	}
	tag = 0; vector<Tp> u = odt.cov(ql, qr, qc);
	for (int i = 0, l, r, c; i < u.size(); ++i)
		l = u[i].l, r = u[i].r, c = u[i].c, vs[c] = 1, vc[c] -= r - l + 1;
	for (int i = 0, l, r, c; i < u.size(); ++i) {
		l = u[i].l, r = u[i].r, c = u[i].c;
		if (vs[c]) b1.U(c, vc[c]), vs[c] = vc[c] = 0;
	}
	b1.U(qc, qr - ql + 1);
}
IL void who() {
	odt.clr(); b1.C(); ans = pb[R] - pb[L - 1]; tag = 0;
	for (int i = L; i <= R; ++i) odt.ins(i, i, b[i]), b1.U(b[i], 1);
	for (int i = 1; i <= cq; ++i)
		if (qr[i].op == 1) add(qr[i].l, qr[i].r, qr[i].x);
		else if (qr[i].op & 1)
			o[qr[i].x] += ans * (fe[qr[i].l] < id && id < fe[qr[i].r]);
		else if (qr[i].r >= L && qr[i].l <= R) {
			if (id == sk[0][i].fi) ans = sk[0][i].se;
			if (id == sk[1][i].fi) ans = sk[1][i].se;
			if (qr[i].l <= L && R <= qr[i].r)
				tag = qr[i].x, ans = (R - L + 1) * cl[i];
			else cov(max(L, qr[i].l), min(R, qr[i].r), qr[i].x);
		}
}
signed main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin >> n >> q; B = 512; F = 2000;
	for (int i = 1; i <= n; ++i)
		cin >> a[i], odt.ins(i, i, a[i]), pa[i] = pa[i - 1] + a[i];
	for (int i = 1; i <= n; ++i)
		cin >> b[i], pb[i] = pb[i - 1] + pa[b[i]], fe[i] = (i - 1) / F + 1;
	for (int i = 1; i <= be(n); ++i) bl[i] = br[i - 1] + 1, br[i] = min(i * B, n);
	for (int i = 1; i <= fe[n]; ++i) fl[i] = fr[i - 1] + 1, fr[i] = min(i * F, n);
	bc.I(); ds.I();
	for (int i = 1, p, l, r, x; i <= q; ++i) {
		cin >> p >> l >> r;
		if (p == 1) {
			cin >> x; vector<Tp> u = odt.cov(l, r, x);
			for (int j = 0; j < u.size(); ++j)
				qr[++cq] = {1, u[j].l, u[j].r, x - u[j].c};
		} else if (p & 1) qr[++cq] = {3, l, r, i};
		else cin >> x, qr[++cq] = {2, l, r, x};
	}
	for (int i = 1; i <= cq; ++i)
		if (qr[i].op == 1) ds.U(qr[i].l, qr[i].r, qr[i].x);
		else if (qr[i].op & 1) o[qr[i].x] = bc.qs(qr[i].l, qr[i].r);
		else bc.U(i, qr[i].l, qr[i].r, qr[i].x, 0), cl[i] = ds.Q(qr[i].x);
	for (int i = 1; i <= fe[n]; ++i) id = i, L = fl[i], R = fr[i], who();
	for (int i = 1; i <= cq; ++i) if (qr[i].op == 3) cout << o[qr[i].x] << '\n';
	return 0;
}
```

---

## 作者：XZhuRen (赞：3)

总算卡过了。具体就是块长开大，换 C++98。

可爱的分块题。

考虑对序列 $B$ 分块，这样便于处理整块贡献，发现散块容易通过对 $A$ 直接维护 $\mathcal{O}(\sqrt{n})-\mathcal{O}(1)$ 的分块暴力。

先不考虑 $2$ 操作。

每次我们对 $A$ 推平，即用珂朵莉树转化为线性次区间加，之后考虑对于序列 $B$ 上整块的贡献。

对于前缀和，区间加转化为两次等差数列加即可，一次等差数列加的贡献记为：$(x,k)$，即 $\forall b_i\ge x,b_i\to b_i+k(b_i-x)$。

考虑整块贡献，每次直接取所有 $b_i\ge x$，对整块累加贡献即可，这个在没有修改的时候容易用前缀和解决。

加入对于序列 $B$ 的推平操作：

考虑一个不好的事情：

分块后被散块修改的区间都需要重置，要求重置做到 $\mathcal{O}(\sqrt{n})$ 明显不太可能。

首先考虑需要什么样的数据结构可以维护：

对于线性次修改，我们只需要维护一个 $\mathcal{O}(\sqrt{n})-\mathcal{O}(1)$ 的分块即可。

问题在于散块的修改是 $\mathcal{O}(\sqrt{n})$ 的，我们并不能让散块的修改变成常数次的（笑）。

考虑如何不全部重构？即想让修改次数转化为线性。

有以下的结论：

序列分块下，在所有块内部维护珂朵莉树，总复杂度为 $\mathcal{O}(q\sqrt{n}+(q+n)\log n)$，其中第二部分恰好为散块操作复杂度，证明显然。

则我们先对序列分块，一次推平操作，整块打标记（注意这里不能直接打，如果之前有散区间需要先清空，有标记的区间直接通过标记加贡献），散块对珂朵莉树修改，改贡献。

则我们需要统计的信息有：

1. $\mathcal{O}(n+q)$ 次散块推平时被推平的 $b_i$ 前缀和。

2. $\mathcal{O}(q)$ 次散块操作时推平的 $b_i$ 前缀和。

3. $A$ 序列的珂朵莉树在每次操作后的贡献。

没了，总共需要写三个分块，两棵珂朵莉树，注意以下离线操作和升天的常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void in(T &n){
    n=0;char c=getchar();bool flag=0;
    for(;c<'0'||c>'9';c=getchar()) if (c=='-') flag=1;
    for(;c>='0'&&c<='9';c=getchar()) (n*=10)+=(c^48);
    if (flag) n=-n;
}
int wlsk[45];int wltp;
template<typename T>
void out(T n,char c=0){
    if (n==0){putchar('0');if (c)putchar(c);return ;}
    if (n<0) putchar('-'),n=-n;
    while(n) wlsk[++wltp]=(n%10),n/=10;
    while(wltp) putchar(wlsk[wltp--]^48);
    if (c) putchar(c);
}
typedef unsigned int ll1;
#define int ll1
const int N=5e5+5;
const int MaxB=1005;
struct Node{
    int l,r;
    ll1 dt;
    bool operator <(const Node&o)const{return l<o.l;}
};
int n,q;
int a[N],b[N];
ll1 sb[N];
vector<pair<int,int> >opers[N];//区间加:大于 x 的元素+y(pos-x)
#define mkp make_pair
namespace Chtholly{
    set<Node>s;
    void build(){
        for(int r=1;r<=n;r++){
            int l=r;
            while(a[r+1]==a[r]&&r<n)++r;
            s.insert((Node){l,r,(ll1)a[l]});
        }
    }
    set<Node>::iterator iter,iter1,iter2;
    void split(int dv){//划分为 dv-1,dv
        iter=--(s.upper_bound((Node{dv,0,0})));
        if(iter->l>=dv)return;
        Node tmp=*iter;s.erase(iter);
        s.insert((Node){tmp.l,dv-1,tmp.dt});
        s.insert((Node){ dv ,tmp.r,tmp.dt});
    }
    void mer(set<Node>::iterator iter){
        if(iter==s.end()||iter==s.begin())return;
        iter1=iter--;
        if(iter1->dt!=iter->dt)return;
        Node tmp=(Node){iter->l,iter1->r,iter->dt};
        s.erase(iter,++iter1);
        s.insert(tmp);
    }
    void push_off(int l,int r,int x,int t){
        split(l),split(r+1);
        iter1=s.lower_bound((Node){l,0,0});
        iter2=s.upper_bound((Node){r,0,0});
        for(iter=iter1;iter!=iter2;++iter){
            opers[t].push_back(mkp((iter->l)-1,x-(iter->dt)));
            opers[t].push_back(mkp((iter->r),(iter->dt)-x));
        }
        s.erase(iter1,iter2);
        s.insert((Node){l,r,(ll1)x});
        mer(s.upper_bound((Node){r,0,0}));
        mer(s.lower_bound((Node){l,0,0}));
    }
}
namespace block_A{//后缀加，单点查前缀和
    int B,tb=0;
    int L[N],R[N],bel[N];
    ll1 K[N],adtg[N];
    ll1 sum[N];
    void build(){
        B=sqrt(n);
        L[tb=0]=-B;
        for(int i=1;i<=n;i++){
            if(L[tb]+B<=i)L[++tb]=i;
            R[tb]=i,bel[i]=tb;
        }
        ll1 sm=0;
        for(int o=1;o<=tb;o++){
            int l=L[o],r=R[o];
            adtg[o]=K[o]=0;
            for(int i=l;i<=r;i++){
                sm+=a[i];
                sum[i]=sm;
            }
        }
    }
    void add(int st,ll1 k){
        for(int o=bel[st+1];o<=tb;o++){
            int l=L[o],r=R[o];
            if(l>=st){
                K[o]+=k,adtg[o]+=ll1(l-st)*k;
            }else for(int i=max(l,st);i<=r;i++)sum[i]+=(i-st)*k;
        }
    }
    ll1 query(int x){
        return adtg[bel[x]]+sum[x]+K[bel[x]]*(x-L[bel[x]]);
    }
}
namespace block_V{//单点加，区间查后缀和
    int B,tb=0;
    int L[N],R[N],bel[N];
    ll1 sumb[N],cntb[N],sum[N],cnt[N];
    void build(){//这个是主要的花销
        B=sqrt(n);
        L[tb=0]=-B;
        for(int i=1;i<=n;i++){
            if(L[tb]+B<=i)L[++tb]=i;
            R[tb]=i,bel[i]=tb;
        }
    }
    void clear(){
        for(int i=1;i<=n;i++)sum[i]=cnt[i]=0;
        for(int o=1;o<=tb;o++)cntb[o]=sumb[o]=0;
    }
    void add(int x,ll1 c){
        for(int o=bel[x];o;o--){
            int l=L[o],r=R[o];
            if(r<=x)sumb[o]+=c*x,cntb[o]+=c;
            else for(int i=x;i>=l;i--)cnt[i]+=c,sum[i]+=c*x;
        }
    }
    ll1 querysm(int x){
        if(!x)x=1;
        return sumb[bel[x]]+sum[x];
    }
    ll1 querycnt(int x){
        if(!x)x=1;
        return cntb[bel[x]]+cnt[x];
    }
}
namespace block{
    int B,tb=0;
    int L[N],R[N],bel[N];
    ll1 sm[N];//总和
    int tagc[N];
    int b1[N];
    void build(){
        B=sqrt(n*14);
        L[tb=0]=-B;
        for(int i=1;i<=n;i++){
            if(L[tb]+B<=i)L[++tb]=i;
            R[tb]=i,bel[i]=tb;
            b1[i]=b[i];
        }
        for(int o=1;o<=tb;o++){
            sm[o]=0;tagc[o]=0;
            for(int i=L[o];i<=R[o];i++)
            sm[o]+=sb[i];
        }
    }
}
struct OPER{int c;int dt;ll1 w;int t;};vector<OPER>rplc[N];
//每个时间的替换方案：从给块 A 增加/减去了 c 个 dt，
//此时在 A 中权值为 w。
struct ODT{
    set<Node>s;
    void build(int L,int R){
        for(int r=L;r<=R;r++){
            int l=r;
            while(b[r+1]==b[r]&&r<R)++r;
            s.insert((Node){l,r,(ll1)b[l]});
        }
    }
    set<Node>::iterator iter,iter1,iter2;
    void split(int dv){//划分为 dv-1,dv
        iter=s.upper_bound((Node{dv,0,0}));
        if(iter==s.begin())return;
        --iter;
        if(iter->l>=dv)return;
        Node tmp=*iter;s.erase(iter);
        s.insert((Node){tmp.l,dv-1,tmp.dt});
        s.insert((Node){ dv ,tmp.r,tmp.dt});
    }
    void mer(set<Node>::iterator iter){
        if(iter==s.end()||iter==s.begin())return;
        iter1=iter--;
        if(iter1->dt!=iter->dt)return;
        Node tmp=(Node){iter->l,iter1->r,iter->dt};
        s.erase(iter,++iter1),s.insert(tmp);
    }
    void push_off(int l,int r,int x,int o,int t){
        split(l),split(r+1);
        iter1=s.lower_bound((Node){l,0,0});
        iter2=s.upper_bound((Node){r,0,0});
        for(iter=iter1;iter!=iter2;++iter){
            rplc[o].push_back((OPER){-((iter->r)-(iter->l)+1),int(iter->dt),block_A::query(iter->dt),t});
        }//删除段
        s.erase(iter1,iter2);
        s.insert((Node){l,r,(ll1)x});
        mer(s.upper_bound((Node){r,0,0}));
        mer(s.lower_bound((Node){l,0,0}));
    }
    void push_off1(int l,int r,int x){//不产生贡献
        split(l),split(r+1);
        iter1=s.lower_bound((Node){l,0,0});
        iter2=s.upper_bound((Node){r,0,0});
        s.erase(iter1,iter2);
        s.insert((Node){l,r,(ll1)x});
        mer(s.upper_bound((Node){r,0,0}));
        mer(s.lower_bound((Node){l,0,0}));
    }
}odts[MaxB];
int OP[N],Lt[N],Rt[N],Dt[N];
ll1 Vals[N],Ans[N];
void init(){
    in(n),in(q);
    ll1 sma[N];
    for(int i=1;i<=n;i++)
        in(a[i]),sma[i]=sma[i-1]+a[i];
    for(int i=1;i<=n;i++)
        in(b[i]),sb[i]=sma[b[i]];
    Chtholly::build();//大珂朵莉
    for(int t=1;t<=q;t++){
        in(OP[t]),in(Lt[t]),in(Rt[t]);
        if(OP[t]<3)in(Dt[t]);
        if(OP[t]==1)Chtholly::push_off(Lt[t],Rt[t],Dt[t],t);//记录 Chtholly 操作
    }
}
void prework(){//第一次离线操作
    block_A::build();
    block::build();
    for(int o=1;o<=block::tb;o++)//小珂朵莉
        odts[o].build(block::L[o],block::R[o]);
    for(int t=1;t<=q;t++){
        int lt=Lt[t],rt=Rt[t];
        if(OP[t]==1){
            for(ll1 xx=0;xx<opers[t].size();xx++){
                pair<int,int> df=opers[t][xx];
                block_A::add(df.first,df.second);//修改
            }
            continue;
        }
        if(OP[t]==2){//修改 B 序列
            using namespace block;
            Vals[t]=block_A::query(Dt[t]);
            for(int o=bel[lt];o<=bel[rt];o++){//对每个块内的 ODT 操作
                int l=L[o],r=R[o];//珂朵莉修改
                if(l>=lt&&r<=rt){
                    if(!tagc[o])//清空，放入 tag
                        odts[o].push_off(l,r,Dt[t],o,t);
                    tagc[o]=Dt[t];//整块不贡献到 ODT 上
                }else{//散块
                    if(tagc[o]){
                        for(int i=l;i<=r;i++)b1[i]=tagc[o];
                        //在值域分块上打上整块
                        rplc[o].push_back((OPER){r-l+1,tagc[o],block_A::query(tagc[o]),t});
                        odts[o].push_off1(l,r,tagc[o]);//在珂朵莉树上打标记，不用删除旧贡献（因为没有加上）
                        tagc[o]=0;
                    }
                    odts[o].push_off(max(l,lt),min(r,rt),Dt[t],o,t);
                    rplc[o].push_back((OPER){min(r,rt)-max(l,lt)+1,Dt[t],block_A::query(Dt[t]),t});
                    for(int i=max(l,lt);i<=min(r,rt);i++)b1[i]=Dt[t];
                    //这样就处理了所有的整块 sum 变化量
                }
            }
            continue;
        }
        if(OP[t]==3){
            using namespace block;
            for(int o=bel[lt];o<=bel[rt];o++){
                if(L[o]>=lt&&R[o]<=rt)continue;
                for(int i=max(L[o],lt);i<=min(R[o],rt);i++)
                    Ans[t]+=block_A::query(tagc[o]?tagc[o]:b1[i]);
            }
        }
    }
}
vector<OPER>opint[N];
void solve(int o){
    block_V::clear();
    int l=block::L[o],r=block::R[o],len=r-l+1;
    for(int i=l;i<=r;i++)
        block_V::add(b[i],1);
    int nwtg=0;//当前的整块标记
    ll1 sm=block::sm[o];//初始的和
    for(int t=1;t<=q;t++)opint[t].clear();
    for(int xx=0;xx<rplc[o].size();xx++){
        OPER cq=rplc[o][xx];
        opint[cq.t].push_back(cq);
    }
    for(int t=1;t<=q;t++){
        int lt=Lt[t],rt=Rt[t];
        if(OP[t]==1){//对于值域做修改
            for(int xx=0;xx<opers[t].size();xx++){
                pair<int,int> cq=opers[t][xx];
                if(nwtg){
                    if(nwtg>=cq.first)
                    sm+=len*(nwtg-cq.first)*cq.second;
                }else sm+=(-(block_V::querycnt(cq.first)*cq.first)+block_V::querysm(cq.first))*cq.second;
            }
        }
        if(OP[t]==2){//修改 B 序列，分 tag 和非 tag 处理
            for(int xx=0;xx<opint[t].size();xx++){//修改值域分块
                OPER cq=opint[t][xx];
                block_V::add(cq.dt,cq.c);
            }
            if(l>=lt&&r<=rt){//整块，打 tag
                nwtg=Dt[t];
                sm=len*Vals[t];//直接覆盖，更新 sm
            }else if(!(r<lt||l>rt)){
                if(nwtg){
                    nwtg=0;//破坏整块，不仅重置分块还要重置 sm
                    sm=0;
                }
                for(int xx=0;xx<opint[t].size();xx++){
                    OPER cq=opint[t][xx];
                    sm+=cq.w*cq.c;
                }
            }
        }
        if(OP[t]==3&&l>=lt&&r<=rt)
            Ans[t]+=sm;
    }
}
void work(){
    block_V::build();
    block::build();
    for(int o=1;o<=block::tb;o++)solve(o);
    for(int t=1;t<=q;t++){
        if(OP[t]<3)continue;
        out(Ans[t],'\n');
    }
}
signed main(){
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    init();
    prework();
    work();
    return 0;
}
/*
考虑我们块内维护有关 B_i 的值域分块
则我们需要推平某种元素的时候：（散块）
直接对它做修改。
否则我们推平这个东西，之后打整块标记（整块不满足总修改线性）
*/
```

---

## 作者：Eterna (赞：2)

考虑对 $\{b\}$ 分块，对于每个块 $[l_i,r_i]$ 维护答案 $\sum\limits_{j=l_i}^{r_i}\sum\limits _{k=1}^{b_j}a_k$。散块用其他方法，就是考虑如何 $\mathcal{O}(1)$ 查 $\{a\}$ 的前缀和。

直接维护 $\{a\}$ 的前缀和，用颜色段均摊的技巧将所有操作 $1$ 变为 $\mathcal{O}(n+m)$ 次的区间加。对于前缀和来说，区间加就是区间加等差数列和后缀加。用 $\mathcal{O}(\sqrt{n})-\mathcal{O}(1)$ 的分块即可维护。

对于整块答案的维护，有两种贡献，第一类是 $\{a\}$ 的区间加，第二类是 $\{b\}$ 的区间赋值。

对于第一类，差分后区间加是 $(1,r,v)$ 的形式，即对 $i \in [1,r]$ 的 $a_i$ 加上 $v$。

直接考虑这样对块答案的贡献。对于一个块，它的答案显然增加：

$$\sum _{j=1}^{r}v\sum _{k=l_i}^{r_i}[j \le b_k]=v\sum_{j=l_i}^{r_i}\min \{r,b_j\}$$

分别维护 $r \le b_j$ 的 $b_j$ 之和，$r > b_j$ 的数量。如果可以 $\mathcal{O}(1)$ 查询上面的两个，则操作 $1$ 可以做到 $\mathcal{O}(\sqrt{n})$。

对于第二类，用颜色段均摊的技巧可以看作是 $\mathcal{O}(n+m)$ 次颜色段删除或插入。整块打标记，询问时特判。散块暴力维护 $\mathcal{O}(n+m)$ 的颜色数增减。结合 $\mathcal{O}(1)$ 查询 $r \le b_j$ 的 $b_j$ 之和，$r > b_j$ 的数量。可以用 $\mathcal{O}(\sqrt{n})-\mathcal{O}(1)$ 的值域分块解决。

但是我们要开 $\mathcal{O}(\sqrt{n})$ 个值域分块，空间会达到 $\mathcal{O}(n\sqrt{n})$，连编译都过不去。

考虑离线逐块处理，但是我们发现对于每个块都维护 $\{a\}$ 复杂度不对。对于询问的散块，我们先扫一遍做掉。

于是只用考虑操作 $2$ 对整块的贡献，因为颜色段数是 $\mathcal{O}(n+m)$ 的，所以这种贡献本质不同的询问次数也是 $\mathcal{O}(n+m)$ 的。

提前处理出每个时刻插入删除对应 $b_i$ 的贡献即可。

哈哈，但是我们发现处理出来后没法快速映射，写完发现复杂度是 $\mathcal{O}((n+m)\sqrt{n} \log n)$，空间卡的还很死。

我们发现离线逐块处理和元素处理可以同方向，删除元素维护一个双指针即可。加入元素只有一个，可以单独做。

时间复杂度 $\mathcal{O}((n+m)\sqrt{n})$，空间复杂度 $\mathcal{O}(n+m)$。可以卡进原时限。


```cpp
#include<bits/stdc++.h>
#define IT set<node>::iterator
#define int unsigned int
#define rd read()
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
using namespace std;
static char buf[100000], * pa(buf), * pb(buf);
inline int read()
{
	register int x=0,s=gc;
	while(!isdigit(s))s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+(s^48),s=gc;
	return x;
}
const int N=500005,Q=300005,M=1500000;
const int block=2000,S=N/block+5,bk=600,W=N/bk+5;
int n,m,tot,to2,cnt,fl,X,Y,sumb,tg,id;
int A[N],B[N],bl[N],b2[N],a[N],p[M];
int ans[N<<2],ct[N],b[N],g[M];
int L[S],R[S],Lk[W],Rk[W],tag[S];
vector<int> f[M],f2[M];
struct mak{int op,l,r,v;}q[M];
struct lxl
{
	int c[N],tag1[W],tag2[W];
	inline void get(){for(int i=1;i<=n;++i)c[i]=a[i];}
	inline void up(int l,int r,int v)
	{
		if(l>r)return;
		if(b2[l]==b2[r]){for(int i=l;i<=r;++i)c[i]+=(i-l+1)*v;return;}
		up(l,Rk[b2[l]],v);for(int i=Lk[b2[r]];i<=r;++i)c[i]+=(i-l+1)*v;
		for(int i=b2[l]+1;i<b2[r];++i)tag1[i]+=v,tag2[i]+=(1-l)*v;
	}
	inline void ad(int l,int v)
	{
		if(l>n)return;
		for(int i=l;i<=Rk[b2[l]];++i)c[i]+=v;
		for(int i=b2[l]+1;i<=to2;++i)tag2[i]+=v;
	}
	inline int ask(int x){return tag1[b2[x]]*x+tag2[b2[x]]+c[x];}
	inline void add(int l,int r,int v){ad(r+1,(r-l+1)*v),up(l,r,v);}
}D;
struct crs
{
	int tg[W],tg2[W],c2[N],c3[N];
	inline void ad(int l,int v){int s=l*v;for(int i=l;i<=Rk[b2[l]];++i)c2[i]+=v,c3[i]+=s;for(int i=b2[l]+1;i<=to2;++i)tg[i]+=v,tg2[i]+=s;}
	inline int ask(int x){return tg[b2[x]]+c2[x];}
	inline int ask2(int x){return tg2[b2[x]]+c3[x];}
	inline void clear(){memset(tg,0,sizeof(tg)),memset(c2,0,sizeof(c2)),memset(tg2,0,sizeof(tg)),memset(c3,0,sizeof(c3));}
}ds;
struct node
{
	int l,r,v;
	inline node(int L,int R=0,int V=0):l(L),r(R),v(V){}
	inline bool operator <(const node &o)const{return l<o.l;}
};
struct ODT
{	
	set<node> s;
	inline IT split(int l)
	{
		IT it=s.lower_bound(node(l));
		if(it!=s.end()&&it->l==l)return it;
		--it;int L=it->l,R=it->r,V=it->v;
		s.erase(it),s.insert(node(L,l-1,V));
		return s.insert(node(l,R,V)).first;
	}
	inline void assign(int l,int r,int v)
	{
		IT itr=split(r+1),itl=split(l);
		if(fl==1)for(IT i=itl;i!=itr;++i)q[++cnt]={1,i->l,i->r,v-i->v};
		if(fl==2){for(IT i=itl;i!=itr;++i)if(itl->l<=X||itl->r>=Y)f[cnt].push_back(i->v);g[cnt]=v;}
		s.erase(itl,itr),s.insert(node(l,r,v));
	}
}T,K;
inline void pushdown(int id){if(tag[id]){for(int i=L[id];i<=R[id];++i)b[i]=tag[id];tag[id]=0;}}
inline void sing(int l,int r,int v)
{
	if(bl[l]==bl[r]){pushdown(bl[l]);for(int i=l;i<=r;++i)b[i]=v;return;}
	sing(l,R[bl[l]],v),sing(L[bl[r]],r,v);for(int i=bl[l]+1;i<bl[r];++i)tag[i]=v;
}
inline int ask(int l,int r)
{
	if(bl[l]==bl[r])
	{
		if(L[bl[l]]==l&&R[bl[r]]==r)return 0;
		if(tag[bl[l]])return D.ask(tag[bl[l]])*(r-l+1);
		int s=0;for(int i=l;i<=r;++i)s+=D.ask(b[i]);return s;
	}
	return ask(l,R[bl[l]])+ask(L[bl[r]],r);
}
inline int get(int x){return tg?(R[id]-L[id]+1)*min(tg,x):ds.ask2(x)+x*(ds.ask(n)-ds.ask(x));}
inline int ak(int i,int v){while(f[i][p[i]]!=v)++p[i];return f2[i][p[i]];}
inline void solve()
{
	ds.clear(),sumb=tg=0;
	for(int i=L[id];i<=R[id];++i)sumb+=a[B[i]],b[i]=B[i],++ds.c2[B[i]],ds.c3[B[i]]+=B[i];
	for(int i=1;i<=n;++i)ds.c2[i]+=ds.c2[i-1],ds.c3[i]+=ds.c3[i-1];
	for(int i=1;i<=cnt;++i)
	{
		auto [op,l,r,v]=q[i];
		if(op==1)sumb+=(get(r)-get(l-1))*v;
		if(op==2)
		{
			l=max(l,L[id]),r=min(r,R[id]);
			if(l>r)continue;
			if(l==L[id]&&r==R[id])tg=v,sumb=g[i]*(R[id]-L[id]+1);
			else
			{
				if(tg)
				{
					for(int j=L[id];j<=R[id];++j)++ct[b[j]];
					for(int j=L[id];j<=R[id];++j)if(ct[b[j]])ds.ad(b[j],-ct[b[j]]),ct[b[j]]=0;
					for(int j=L[id];j<=R[id];++j)b[j]=tg;
					sumb+=(r-l+1)*(g[i]-ak(i,tg)),ds.ad(tg,R[id]-L[id]-r+l),ds.ad(v,r-l+1),tg=0;
				}
				else
				{
					for(int j=l;j<=r;++j)++ct[b[j]];
					for(int j=l;j<=r;++j)if(ct[b[j]])sumb-=ct[b[j]]*ak(i,b[j]),ds.ad(b[j],-ct[b[j]]),ct[b[j]]=0;
					sumb+=g[i]*(r-l+1),ds.ad(v,r-l+1);
				}
				for(int j=l;j<=r;j++)b[j]=v;
			}
		}
		if(op==3&&l<=L[id]&&r>=R[id])ans[i]+=sumb;
	}
}
signed main()
{
	n=rd,m=rd;tot=(n-1)/block+1;to2=(n-1)/bk+1,T.s.insert(node(n+1,N,0)),K.s.insert(node(n+1,N,0));
	for(int i=1;i<=n;bl[i]=(i-1)/block+1,++i)A[i]=rd,a[i]=a[i-1]+A[i];
	for(int i=1;i<=n;b2[i]=(i-1)/bk+1,++i)b[i]=B[i]=rd;D.get();
	for(int i=1;i<=n;++i)T.s.insert(node(i,i,A[i])),K.s.insert(node(i,i,B[i]));
	for(int i=1;i<=tot;++i)L[i]=R[i-1]+1,R[i]=i*block;R[tot]=n;
	for(int i=1;i<=to2;++i)Lk[i]=Rk[i-1]+1,Rk[i]=i*bk;Rk[to2]=n;
	for(int i=1,op,l,r,v;i<=m;++i)
	{
		op=rd,l=rd,r=rd;
		if(op==1)fl=1,T.assign(l,r,rd);
		if(op==2)fl=2,++cnt,X=R[bl[l]],Y=L[bl[r]],v=rd,K.assign(l,r,v),q[cnt]={op,l,r,v};
		if(op==3)q[++cnt]={op,l,r,0};
	}
	for(int i=1;i<=cnt;g[i]=D.ask(g[i]),++i)
	{
		auto [op,l,r,v]=q[i];
		if(op==1)D.add(l,r,v);
		if(op==2)sing(l,r,v);
		if(op==3)ans[i]=ask(l,r);
		for(int j:f[i])f2[i].push_back(D.ask(j));
	}
	for(int i=1;i<=tot;++i)id=i,solve();
	for(int i=1;i<=cnt;++i)if(q[i].op==3)cout<<ans[i]<<'\n';
	return 0;
}
```

---

