# [PA 2025] 子序列 / Podciągi

## 题目背景

PA 2025 R5B.

**警告：滥用本题评测一次即可封号。**

## 题目描述

本题中下标均为 $\text{1-indexed}$。

给定长度为 $n$ 的字符串 $s$，字符集 $\Sigma=\{\texttt{a},\texttt{b},\ldots,\texttt{f}\}$。

有 $q$ 次操作，每次操作对 $s$ 进行单点修改。

对于 $i=1,2,\ldots,q+1$，求出：进行前 $(i-1)$ 次操作后，$s$ 中满足以下条件的**非空**子序列 $t$ 的数量：

- $t$ 在 $s$ 中出现至少两次。

由于答案可能很大，只需要求出答案对 $998\, 244\, 353$ 取模后的结果。


## 说明/提示


### 样例解释

- 初始字符串为 $s=\texttt{abca}$，唯一符合条件的子序列为 $\texttt{a}$。
- 进行 $1$ 次操作后，字符串为 $s=\texttt{abca}$，唯一符合条件的子序列为 $\texttt{a}$。
- 进行前 $2$ 次操作后，字符串为 $s=\texttt{abcd}$，无符合条件的子序列。
- 进行前 $3$ 次操作后，$s=\texttt{accd}$，符合条件的子序列有 $\texttt{ac},\texttt{cd},\texttt{acd},\texttt{c}$。

### 子任务

存在大于 $0$ 分的子任务满足 $\Sigma=\{\texttt{a},\texttt{b}\}$。

### 数据范围

- $3 \le n \le 5\times 10^4$；
- $0 \le q \le 5\times 10^4$；
- $s_i,c_i\in \Sigma=\{\texttt{a},\texttt{b},\ldots,\texttt{f}\}$；
- $1\le p_i\le n$。


## 样例 #1

### 输入

```
4 3
abca
1 a
4 d
2 c```

### 输出

```
1
1
0
4```

# 题解

## 作者：rainygame (赞：15)

出现至少两次的本质不同子序列不好计数，容斥一下就可以变为两个问题：求本质不同子序列个数、求出现恰好一次的本质不同子序列个数。

### 求本质不同子序列个数

设 $f_{i,j}$ 表示前 $i$ 个数构成的以 $j$ 为结尾的本质不同子序列个数。那么有转移：

$$
f_{i,j}=\begin{cases}
f_{i-1,j}, &s_i\ne j\\
\sum\limits_kf_{i-1,k}+1, &s_i=j
\end{cases}
$$

这表示对于一个子序列，每次选择的点都是尽量靠后的。这保证了只计算一次。

显然这个形式可以写成矩阵乘法的形式，然后直接上线段树维护矩阵乘法即可。此处时间复杂度 $O(nk^3\log n)$，其中 $k=6$。

### 求出现恰好一次的本质不同子序列个数

“出现恰好一次”等价于“既是第一个也是最后一个”。举个 `abc` 的例子。这说明这个子序列中的 `a` 前面不能有 `a`，这个子序列中的 `a`、`b` 之间不能有 `a` 或 `b`、这个子序列中的 `b`、`c` 之间不能有 `b` 或 `c`、这个子序列中的 `c` 后面不能有 `c`。如果满足了这些条件，那么可以推得 `abc` 这个子序列在串中唯一出现。

这个不是很好 DP，因为还好考虑到两个字符之间的字符集。但是因为是在线段树上做，所以可以改成区间信息合并。区间需要维护 $f(x,y)$ 表示区间内以 $x$ 开头 $y$ 结尾的唯一出现子序列个数，$p(x),s(x)$ 分别表示序列中第一个/最后一个 $x$ 的前面/后面的字符集。合并过程为：

$$
f(x,y)=\sum\limits_{a}\sum\limits_{b}[a,b \notin (s(a)\cup p(b))]f_l(x,a)f_r(b,y)
$$

注意还需要特判某个唯一出现子序列在某一边的情况。

这样就可以做到 $O(nk^4\log n)$ 了，由于 15s 的超长时限，应该可以通过。但是还可以优化。

容易发现这是一个类似矩阵乘法的东西，设 $A_{i,j}=f_l(i,j),B_{i,j}=[i,j \notin (s(i)\cup p(j))],C_{i,j}=f_r(i,j)$，那么显然 $f(x,y)=(ABC)_{x,y}$。时间复杂度 $O(nk^3\log n)$。

代码很好写：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 50005
const int MOD(998244353);

int n, q; string t;

struct Matrix{
    int n, m, a[7][7]; Matrix(){memset(a, 0, sizeof(a));}
    Matrix operator*(Matrix b){
        Matrix c; c.n = n; c.m = b.m;
        for (int i(0); i<n; ++i) for (int j(0); j<b.m; ++j) for (int k(0); k<m; ++k){
            (c.a[i][j] += a[i][k]*b.a[k][j]) %= MOD;
        }
        return c;
    }
    void print(){for (int i(0); i<n; ++i, cerr << '\n') for (int j(0); j<m; ++j) cerr << a[i][j] << ' ';}
};

namespace Seg{
    struct Node{Matrix f, g; int st, p[6], s[6];}tr[MAXN<<2];
    void modify(int p, int l, int r, int x, int k){
        if (l == r){
            tr[p].st = 1<<k; tr[p].p[k] = tr[p].s[k] = 0; tr[p].f.n = tr[p].f.m = 7; tr[p].g.n = tr[p].g.m = 6;
            for (int i(0); i<6; ++i) if (i ^ k) tr[p].p[i] = tr[p].s[i] = 63; tr[p].f.a[6][6] = 1;
            for (int i(0); i<6; ++i) for (int j(0); j<6; ++j) tr[p].f.a[i][j] = i == j || j == k;
            for (int i(0); i<6; ++i) tr[p].f.a[6][i] = i == k;
            for (int i(0); i<6; ++i) for (int j(0); j<6; ++j) tr[p].g.a[i][j] = i == j && j == k; return;
        }
        int mid((l+r)>>1); if (x <= mid) modify(p<<1, l, mid, x, k); else modify(p<<1|1, mid+1, r, x, k);
        tr[p].f = tr[p<<1].f * tr[p<<1|1].f; tr[p].st = tr[p<<1].st | tr[p<<1|1].st;
        for (int i(0); i<6; ++i) tr[p].p[i] = min(tr[p<<1].p[i], tr[p<<1|1].p[i]|tr[p<<1].st);
        for (int i(0); i<6; ++i) tr[p].s[i] = min(tr[p<<1|1].s[i], tr[p<<1].s[i]|tr[p<<1|1].st);
        Matrix yyx; for (int i(0); i<6; ++i) for (int j(0); j<6; ++j) yyx.a[i][j] = !((1<<i|1<<j)&(tr[p<<1].s[i]|tr[p<<1|1].p[j]));
        yyx.n = yyx.m = 6; tr[p].g = tr[p<<1].g * yyx * tr[p<<1|1].g;
        for (int i(0); i<6; ++i) for (int j(0); j<6; ++j){
            if (!(tr[p<<1].st>>i&1)) tr[p].g.a[i][j] += tr[p<<1|1].g.a[i][j];
            if (!(tr[p<<1|1].st>>j&1)) tr[p].g.a[i][j] += tr[p<<1].g.a[i][j];
        }
    }
}
int sol(){
    Matrix f(Seg::tr[1].f), g(Seg::tr[1].g); Matrix a; a.a[0][6] = a.n = 1; a.m = 7;
    a = a*f; int res(0); for (int i(0); i<6; ++i) (res += a.a[0][i]) %= MOD;
    for (int i(0); i<6; ++i) for (int j(0); j<6; ++j) (res += MOD-g.a[i][j]) %= MOD; return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> q >> t; t = ' ' + t; for (int i(1); i<=n; ++i) Seg::modify(1, 1, n, i, t[i]-'a'); cout << sol() << '\n';
    for (int x; q; --q){
        char c; cin >> x >> c; Seg::modify(1, 1, n, x, c-'a'); cout << sol() << '\n';
    }

    return 0;
}

```

---

## 作者：沉石鱼惊旋 (赞：3)

# 题意

给定长度 $n$ 字符集长度为前 $m$ 小的字符串 $s$，输出有多少本质不同子序列出现了至少两次。

$q$ 次修改，每次给出 $x,t$ 表示 $s_x\gets t$。修改是永久的。在所有修改之前和每次修改后输出共 $q+1$ 个答案。保证 $t$ 也在字符集中。

答案对 $998244353$ 取模。

$3\leq n\leq 5\times 10^4$，$0\leq q\leq 5\times 10^4$，$m=6$。

# 做法

出现至少两次直接计数非常困难，考虑用 Part A 所有本质不同子序列的个数减掉 Part B 恰好出现一次的子序列个数。

Part A 所有本质不同的子序列个数是个大典题。

考虑 DP。设 $f_{i,c}$ 表示前 $i$ 个数 $c$ 结尾的方案数。转移有 $f_{i,j}\gets \begin{cases}f_{i-1,c}&s_i\neq c \\\sum\limits_{d=0}^m f_{i-1,d} &s_i=c\end{cases}$。

我们把前 $m$ 小个字符映射成 $[0,m-1]$，$f_{i,m}$ 是空串，有固定的一个方案数。

而 Part B 恰好出现一次的子序列个数对着这个 DP 改一改就好。

考虑何时会算重，就是 $c$ 的上一个出现位置 $lst_c$ 比 $d$ 的上一个出现位置 $lst_d$ 要靠后。即 $lst_c\gt lst_d$。这种情况不可以转移。

暴力的代码 $\mathcal O(nq)$ 如下：

```cpp
int solve()
{
    vector<array<Z, 6>> f(n + 1);
    vector<array<Z, 6>> g(n + 1);
    vector<int> lst(6);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i] - 'a' == j)
            {
                for (int k = 0; k < m; k++)
                    f[i][j] += f[i - 1][k];
                f[i][j]++;
            }
            else
            {
                f[i][j] = f[i - 1][j];
            }
        }
    }
    Z ans = 0;
    for (int j = 0; j < m; j++)
        ans += f[n][j];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i] - 'a' == j)
            {
                for (int k = 0; k < m; k++)
                    if (lst[j] <= lst[k])
                        g[i][j] += g[i - 1][k];
                if (!lst[j])
                    g[i][j]++;
            }
            else
            {
                g[i][j] = g[i - 1][j];
            }
        }
        lst[s[i] - 'a'] = i;
    }
    for (int j = 0; j < m; j++)
        ans -= g[n][j];
    return ans.val();
}
```

考虑带修怎么做。

Part A 带修是容易的，有朴素的线段树维护矩阵的做法。

<https://loj.ac/p/6074> 这题是若干次区间查询本质不同子序列个数。套到本题的线段树一样。

具体的，我们维护 $A_i$ 为 $i$ 的转移矩阵。那么有 $A_i = \left(\begin{array}{l}1\ \ 0\ \ 0\ \ 0\ \ 0 \\1\ \ 1\ \ 1\ \ 1\ \ 1 \\0\ \ 0\ \ 1\ \ 0\ \ 0 \\0\ \ 0\ \ 0\ \ 1\ \ 0 \\0\ \ 0\ \ 0\ \ 0\ \ 1\end{array}\right)$，即为单位矩阵加上某一行全填 $1$。就是第 $s_i$ 行全填 $1$。

然后线段树单点修改全局查询矩阵乘积是简单的。

Part B 考虑难在处理 $lst$。我们线段树维护这样的矩阵信息：$f_{id,a,b}$ 表示这个节点 $i$ 的范围内以 $a$ 开头 $b$ 结尾的子序列的方案数。

合并的时候就是 $f_{ls,a,b}\times \operatorname{valid}(b,c)\times f_{rs,c,d}$。$\operatorname{valid}$ 即为判断 $ls$ 的最后一个 $b$ 和 $rs$ 的第一个 $c$ 中间是否包含其他的 $b$ 或 $c$。

这个形式很像一般的矩阵乘法。我们把 $\operatorname{valid}$ 也看为一个矩阵，那么 $f_{id}\gets f_{ls}\times \operatorname{valid}\times f_{rs}$ 即可。

这样还有个问题：这只能处理合并左右部分，如果右边某个字符没有出现，左边还有一部分信息要更新上去。这个直接判字符有没有在右边出现就好了。维护的时候维护 $l_{id,c},r_{id,c}$ 表示节点 $id$ 的第一个 $c$ 和最后一个 $c$ 出现位置。用来求 $\operatorname{valid}$ 和这部分信息的更新。

总复杂度 $\mathcal O(m^3q\log n)$。

# 代码

<https://www.luogu.com.cn/record/208779585>

```cpp
#include <bits/stdc++.h>
using namespace std;
template <int P>
class mod_int
{
    using Z = mod_int;

private:
    static int mo(int x) { return x < 0 ? x + P : x; }

public:
    int x;
    int val() const { return x; }
    mod_int() : x(0) {}
    template <class T>
    mod_int(const T &x_) : x(x_ >= 0 && x_ < P ? static_cast<int>(x_) : mo(static_cast<int>(x_ % P))) {}
    bool operator==(const Z &rhs) const { return x == rhs.x; }
    bool operator!=(const Z &rhs) const { return x != rhs.x; }
    Z operator-() const { return Z(x ? P - x : 0); }
    Z pow(long long k) const
    {
        Z res = 1, t = *this;
        while (k)
        {
            if (k & 1)
                res *= t;
            if (k >>= 1)
                t *= t;
        }
        return res;
    }
    Z &operator++()
    {
        x < P - 1 ? ++x : x = 0;
        return *this;
    }
    Z &operator--()
    {
        x ? --x : x = P - 1;
        return *this;
    }
    Z operator++(int)
    {
        Z ret = x;
        x < P - 1 ? ++x : x = 0;
        return ret;
    }
    Z operator--(int)
    {
        Z ret = x;
        x ? --x : x = P - 1;
        return ret;
    }
    Z inv() const { return pow(P - 2); }
    Z &operator+=(const Z &rhs)
    {
        (x += rhs.x) >= P && (x -= P);
        return *this;
    }
    Z &operator-=(const Z &rhs)
    {
        (x -= rhs.x) < 0 && (x += P);
        return *this;
    }
    Z operator-() { return -x; }
    Z &operator*=(const Z &rhs)
    {
        x = 1ULL * x * rhs.x % P;
        return *this;
    }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
#define setO(T, o)                                  \
    friend T operator o(const Z &lhs, const Z &rhs) \
    {                                               \
        Z res = lhs;                                \
        return res o## = rhs;                       \
    }
    setO(Z, +) setO(Z, -) setO(Z, *) setO(Z, /)
#undef setO
        friend istream &
        operator>>(istream &is, mod_int &x)
    {
        long long tmp;
        is >> tmp;
        x = tmp;
        return is;
    }
    friend ostream &operator<<(ostream &os, const mod_int &x)
    {
        os << x.val();
        return os;
    }
};
const int P = 998244353;
using Z = mod_int<P>;
const int inf = 1000000000;
int n, q;
const int m = 6;
string s;
struct Matrix
{
    Z a[7][7];
    Matrix() { memset(a, 0, sizeof(a)); }
    void build()
    {
        for (int i = 0; i <= m; i++)
            a[i][i] = 1;
    }
    void clear() { memset(a, 0, sizeof(a)); }
    Z *operator[](int x) { return a[x]; }
} mtx[6], U, V;
Matrix operator*(const Matrix &x, const Matrix &y)
{
    Matrix z;
    for (int i = 0; i < 7; i++)
        for (int k = 0; k < 7; k++)
            if (x.a[i][k] != 0)
                for (int j = 0; j < 7; j++)
                    z.a[i][j] += x.a[i][k] * y.a[k][j];
    return z;
}
Matrix operator+(const Matrix &x, const Matrix &y)
{
    Matrix z;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            z.a[i][j] += x.a[i][j] + y.a[i][j];
    return z;
}
struct SegTree
{
    struct node
    {
        Matrix mtx_1;
        Matrix mtx_2;
        int l[6];
        int r[6];
    } t[200020 << 2];
#define ls id << 1
#define rs id << 1 | 1
    Matrix valid(int l, int r)
    {
        Matrix ret;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
                ret[i][j] = t[l].r[j] <= t[l].r[i] &&
                            t[r].l[j] <= t[r].l[i];
        }
        return ret;
    }
    void pushup_1(int id)
    {
        t[id].mtx_1 = t[ls].mtx_1 * t[rs].mtx_1;
    }
    void pushup_2(int id)
    {
        for (int i = 0; i < m; i++)
        {
            t[id].l[i] = min(t[ls].l[i], t[rs].l[i]);
            t[id].r[i] = max(t[ls].r[i], t[rs].r[i]);
        }
        t[id].mtx_2 = t[ls].mtx_2 * valid(ls, rs) * t[rs].mtx_2;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (t[rs].l[j] == inf)
                    t[id].mtx_2[i][j] += t[ls].mtx_2[i][j];
                if (t[ls].r[i] == -inf)
                    t[id].mtx_2[i][j] += t[rs].mtx_2[i][j];
            }
        }
    }
    void build(int id = 1, int l = 1, int r = n)
    {
        if (l == r)
        {
            int x = s[l] - 'a';
            t[id].mtx_1 = ::mtx[x];
            t[id].mtx_2[x][x] = 1;
            for (int i = 0; i < m; i++)
                t[id].l[i] = inf, t[id].r[i] = -inf;
            t[id].l[x] = t[id].r[x] = l;
            return;
        }
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup_1(id);
        pushup_2(id);
    }
    void update_1(int pos, int id = 1, int l = 1, int r = n)
    {
        if (r < pos || l > pos)
            return;
        if (pos <= l && r <= pos)
            return t[id].mtx_1 = ::mtx[s[l] - 'a'], void();
        int mid = l + r >> 1;
        update_1(pos, ls, l, mid);
        update_1(pos, rs, mid + 1, r);
        pushup_1(id);
    }
    void update_2(int pos, int x, int y, int id = 1, int l = 1, int r = n)
    {
        if (r < pos || l > pos)
            return;
        if (pos <= l && r <= pos)
        {
            t[id].mtx_2.clear();
            t[id].mtx_2[y][y] = 1;
            t[id].l[x] = inf;
            t[id].r[x] = -inf;
            t[id].l[y] = t[id].r[y] = pos;
            return;
        }
        int mid = l + r >> 1;
        update_2(pos, x, y, ls, l, mid);
        update_2(pos, x, y, rs, mid + 1, r);
        pushup_2(id);
    }
} T;
void init()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j <= m; j++)
            mtx[i][j][j] = 1;
        for (int j = 0; j <= m; j++)
            mtx[i][i][j] = 1;
    }
}
int solve()
{
    Matrix r = T.t[1].mtx_1;
    Z ans = 0;
    for (int i = 0; i < m; i++)
        ans += r[i][m];
    r = T.t[1].mtx_2;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            ans -= r[i][j];
    return ans.val();
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q >> s;
    s = ' ' + s;
    init();
    T.build();
    cout << solve() << '\n';
    while (q--)
    {
        int x;
        char c;
        cin >> x >> c;
        T.update_2(x, s[x] - 'a', c - 'a');
        s[x] = c;
        T.update_1(x);
        cout << solve() << '\n';
    }
    return 0;
}
```

---

## 作者：Claire0918 (赞：1)

我们从来没见过要求子序列出现两次以上的问题，但是我们见过计算子序列数量的问题，于是我们考虑将原问题转化为子序列数量减去仅出现一次的子序列数量。

---

首先考虑如何计算子序列数量。设 $f_{i, j}$ 表示考虑 $[1, i]$ 前缀，最后一位字符为 $j$ 的子序列数量。转移时考虑是否有 $s_i = j$。如果 $s_i = j$，我们强制在 $f_{i - 1}$ 的每个子序列末尾加上一个 $j$，再加上仅有 $j$ 的子序列，就有 $f_{i, j} = \sum_{k} f_{i - 1, k} + 1$。如果 $s_i \neq j$，那么 $i$ 对 $f_{\cdot, j}$ 没有影响，即 $f_{i, j} = f_{i - 1, j}$。

我们发现这转移可以用 $(|\Sigma| + 1)^2$ 的矩阵刻画，具体地，如果我们希望从 $f_{i - 1}$ 转移到 $f_{i}$，我们就有
$$
\begin{bmatrix}
f_{i - 1, 0} & f_{i - 1, 1} &  \ldots & f_{i - 1, 5} & 1
\end{bmatrix}
\times r = 
\begin{bmatrix}
f_{i, 0} & f_{i, 1} &  \ldots & f_{i, 5} & 1
\end{bmatrix}
$$
不难发现 $r_{x, y} = [x = y \vee y = s_i]$ 满足转移条件。

问题中有修改，于是使用线段树维护区间中矩阵的积，使用
$$
\begin{bmatrix}
0 & 0 &  \ldots & 0 & 1
\end{bmatrix}
$$
乘上根节点矩阵即可。

---

我们注意到一个关键事实：长为 $m$ 的 $t$ 在 $s$ 中仅出现一次，当且仅当对于任何的 $i \in [1, m)$，$s$ 中的 $t_i$ 与 $t_{i + 1}$ 之间没有 $t_i$ 和 $t_{i + 1}$。特别地，$s$ 中 $t_1$ 前没有 $t_1$，$s$ 中 $t_m$ 后没有 $t_m$。

如何统计答案？DP 转移非常复杂，肯定不能用矩阵维护。我们考虑到上文有一棵线段树，并且我们常用线段树维护信息合并统计答案，这启示我们对每一个节点设 $g(x, y)$ 表示在该节点的区间中，以 $x$ 开头，以 $y$ 结尾的仅出现一次的子序列数量。

合并时首先考虑直接继承儿子。对于 $(x, y)$，如果右子树中没有 $y$，那么就有 $g(x, y) \gets g_l(x, y)$，另一侧是类似的。如果左子树有 $g_l(x, a)$，右子树有 $g_r(b, y)$，而且在左子树的 $a$ 和右子树的 $b$ 中间没有 $a$ 和 $b$，那么就有 $g_l(x, a)g_r(b, y)$ 的贡献。设 $p(x)$ 为首个 $x$ 前的字符集合，$s(x)$ 为最后一个 $x$ 后的字符集合，那么该条件即为 $[a, b \notin s_l(a) \cup p_r(b)]$，即
$$
g(x, y) \gets \sum_{a, b} g_l(x, a) \times [a, b \notin s_l(a) \cup p_r(b)] \times g_r(b, y)
$$
暴力枚举这四个变元即可做到单次合并 $\mathcal{O}(|\Sigma|^4)$，总时间复杂度 $\mathcal{O}(q\log n|\Sigma|^4) \approx 10^9$，在 15s 下可能能过。

我们注意到和式中三个项的变元分别为 $\{x, a\}, \{a, b\}, \{b, y\}$，这种形式与矩阵乘法极其类似。于是我们设 $a_{i, j} = g_l(i, j), b_{i, j} = [i, j \notin s_l(i) \cup p_r(j)], c_{i, j} = g_r(i, j)$，就有 $g(x, y) = (abc)_{x, y}$。于是复杂度降到了矩阵乘法的 $\mathcal{O}(|\Sigma|^3)$。

综上，复杂度 $\mathcal{O}(q\log n(|\Sigma| + 1)^3) \approx 3 \times 10^8$，实际上没有一个点跑过 3s。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int maxn = 5e4 + 10, mod = 998244353;

int n, q;
char s[maxn];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x &x, Tp_y y){
    return x += y, x >= mod ? x -= mod : x;
}

struct Mat{
    int mat[7][7];
    Mat(){
        mem(mat, 0);
    }
    inline Mat operator * (const Mat & other) const {
        Mat res;
        for (int i = 0; i < 7; i++){
            for (int j = 0; j < 7; j++){
                for (int k = 0; k < 7; k++){
                    mod_add(res.mat[i][j], (long long)mat[i][k] * other.mat[k][j] % mod);
                }
            }
        }
        return res;
    }
};

namespace segtree{
    struct{
        int l, r, st, pre[6], suf[6];
        Mat mov, g;
    } tree[maxn << 2];
    inline void build(int index, int l, int r){
        tree[index].l = l, tree[index].r = r;
        if (l == r){
            return;
        }
        const int mid = l + r >> 1;
        build(index << 1, l, mid), build(index << 1 | 1, mid + 1, r);
    }
    inline void pushup(int index){
        tree[index].mov = tree[index << 1].mov * tree[index << 1 | 1].mov, tree[index].st = tree[index << 1].st | tree[index << 1 | 1].st;
        for (int i = 0; i < 6; i++){
            tree[index].pre[i] = tree[index << 1].st >> i & 1 ? tree[index << 1].pre[i] : tree[index << 1 | 1].pre[i] | tree[index << 1].st;
            tree[index].suf[i] = tree[index << 1 | 1].st >> i & 1 ? tree[index << 1 | 1].suf[i] : tree[index << 1].suf[i] | tree[index << 1 | 1].st;
        }
        Mat b;
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 6; j++){
                b.mat[i][j] = !((1 << i | 1 << j) & (tree[index << 1].suf[i] | tree[index << 1 | 1].pre[j]));
            }
        }
        tree[index].g = tree[index << 1].g * b * tree[index << 1 | 1].g;
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 6; j++){
                tree[index << 1 | 1].st >> j & 1 || (mod_add(tree[index].g.mat[i][j], tree[index << 1].g.mat[i][j]));
                tree[index << 1].st >> i & 1 || (mod_add(tree[index].g.mat[i][j], tree[index << 1 | 1].g.mat[i][j]));
            }
        }
    }
    inline void modify(int index, int x, int k){
        if (tree[index].l == tree[index].r){
            for (int i = 0; i < 7; i++){
                for (int j = 0; j < 7; j++){
                    tree[index].mov.mat[i][j] = i == j || j == k, tree[index].g.mat[i][j] = i == k && j == k;
                }
            }
            tree[index].st = 1 << k;
            for (int i = 0; i < 6; i++){
                tree[index].pre[i] = tree[index].suf[i] = i == k ? 0 : 63;
            }
            return;
        }
        const int mid = tree[index].l + tree[index].r >> 1;
        modify(index << 1 | (x > mid), x, k), pushup(index);
    }
    inline int query(){
        Mat f;
        int res = 0;
        f.mat[0][6] = 1, f = f * tree[1].mov;
        for (int i = 0; i < 6; i++){
            mod_add(res, f.mat[0][i]);
            for (int j = 0; j < 6; j++){
                mod_add(res, mod - tree[1].g.mat[i][j]);
            }
        }
        return res;
    }
}

using namespace segtree;

int main(){
    scanf("%d %d %s", &n, &q, s + 1), build(1, 1, n);
    for (int i = 1; i <= n; i++){
        modify(1, i, s[i] - 'a');
    }
    printf("%d\n", query());
    while (q--){
        int x;
        char k;
        scanf("%d %c", &x, &k), modify(1, x, k - 'a'), printf("%d\n", query());
    }

return 0;
}
```

---

## 作者：ty_mxzhn (赞：1)

把我题目撞了/fn /fn /fn。

## 不带修

注意到至少两次等价于至少一次减去恰好一次，至少一次是板子。

恰好一次可以先考虑怎么判定？注意到如果 $b$ 所匹配到的相邻位置是 $i,j$ 那么 $a_i,a_j$ 不能在 $i$ 和 $j$ 之间出现。

直接暴力计数，记录上一次字符出现位置，单次 $O(nk)$。

## 带修

至少一次这个东西是可以显然构造矩阵，然后直接上线段树的。难点在于恰好一次。

考虑分治方式解决问题，计数 $f_{u,l,r}$ 表示 $u$ 这一区间里面左端点使用的是 $l$ 的值，右端点使用的是 $r$ 的值。

合并的时候，看一下两边第一个 $l,r$ 出现的位置判定。显然这样子每次转移可以看成矩阵乘法，但是你直接转也没什么问题。

时间复杂度 $O((n+q)k^3\log n)$，空间复杂度 $O(nk^2)$。

---

## 作者：伊地知虹夏 (赞：1)

### Description

给你一个长度为 $n$ 的由前 $m$ 个字符构成的串，问有多少不同子序列出现了至少两次（即出现的位置不同），由于答案很大，输出答案对 $998244353$ 取模的结果。

比如对于字符串 `ababa`，一共有 $6$ 个出现了至少两次的子序列：`a, b, ab, ba, aa, aba`。其中 `aba` 出现在 $\{1,2,3\} \{1,2,5\} \{1,4,5\} \{3,4,5\}$。

同时，你还需要支持 $q$ 次修改，每次修改把其中的第 $q$ 位改为字符 $x$。这里下标从 1 开始。注意所有的修改是累积的。

### Analyze

首先容斥，把出现次数 $\geq 2$ 变为 本质不同子序列数量 $-$ 出现次数为 $1$ 的子序列数量。

**1. 本质不同子序列**

考虑 $O(nm)$ dp，设 $f_{i,c}$ 表示 $[1, i]$ 中以 $c$ 结尾的本质不同子序列数量，转移为 $f_{i, s_i} \to \sum {f_{i,c}}$。

写成矩阵乘法形式：
$$ \begin{bmatrix} f_1 & f_2 & \cdots & f_m \end{bmatrix} \times A_{s_i}$$

其中 ${A_c}(i, j) = \begin{cases} 1 & j = i \operatorname{or} j = c \\ 0 & \rm otherwise \end{cases}$。

用线段树维护矩阵乘法转移即可，单次修改时间复杂度 $\mathcal O(m^3\log n)$。

**2. 出现次数为 $1$ 的子序列个数**

考虑线段树维护 $f_{a,b}$ 表示 $a$ 开头 $b$ 结尾的子序列个数。

注意到 $b$ 的位置一定是区间中最后一个 $b$，$c$ 的位置一定是区第一个 $c$。

记录 ${\rm pre}[i]$，${\rm suf}[i]$ 表示在区间中第一个和最后一个 $i$ 的位置。

考虑合并信息，$L_{a,b}$ 能和 $R_{c,d}$ 合并的条件是 $b$ 和 $c$ 之间没有其他的 $b,c$，即 ${\rm pre}_r[b] \geq {\rm pre}_r[c]$ 且 ${\rm suf}_l[c] \leq {\rm suf}_l[b]$。

这样合并的复杂度是 $\mathcal O(m^4)$ 的，考虑优化。

注意到可行性只和 $b,c$ 有关，设 $V_{b,c} = [{\rm pre}_r[b] \geq {\rm pre}_r[c]][{\rm suf}_l[c] \leq {\rm suf}_l[b]]$，那么 $f_{a,d} = \sum\limits_{b,c} L_{a,b} \times V_{b,c} \times R_{c,d}$。

这个可以拆成两个矩阵乘法 $F = L \times V \times R$，合并复杂度变为 $\mathcal O(m^3)$，单次查询时间复杂度 $\mathcal{O}(m^3\log n)$。

总时间复杂度 $\mathcal{O}(m^3(n+q)\log n)$。
本题中 $m = 6$。

---

