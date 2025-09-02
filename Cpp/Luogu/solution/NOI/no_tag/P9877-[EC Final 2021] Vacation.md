# [EC Final 2021] Vacation

## 题目描述

庞教授有 $c$ 天的年假，他想去度假。

现在一年有 $n$ 天。如果庞教授在第 $i$ 天休息，他可以获得 $a_i$ 的幸福感。幸福感的值 $a_i$ 可能是负数。

庞教授希望你执行 $m$ 个操作：

- $1~x~y$，将第 $x$ 天的幸福感改为 $y$。
- $2~l~r$，庞教授希望在 $[l, r]$ 期间找到一个度假期。他希望连续休息几天（可能为 $0$ 天）并获得尽可能多的幸福感。然而，他只有 $c$ 天的假期，因此在 $[l,r]$ 中他最多只能连续休息 $c$ 天。

这意味着他希望找到

$$\max\left(\max_{l \leq l' \leq r' \leq r\atop r'-l'+1\leq c}  ~~ \left(\sum_{i=l'} ^{r'} a_i\right), 0\right)。$$

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 6 3
0 -5 -3 8 -3
2 3 5
1 2 5
2 1 5
1 4 -3
2 3 5
2 1 5```

### 输出

```
8
10
0
5```

# 题解

## 作者：for_cat (赞：5)

# P9877 [EC Final 2021] Vacation 题解
## 1.题意简述
区间长度不超过 $C$ 最大子段和。
## 2.前置芝士 
线段树，分块。
## 3.题目分析
如果去掉长度小于等于 $C$ 的限制，很显然，这个题就是小白逛公园，那么我们现在的任务就要考虑如何把这个限制弱化掉。

我们首先对序列进行分块，每 $C$ 个分成一段，这样我们能得到 $\left \lceil \frac{n}{c}  \right \rceil$ 个块，那么我们每次操作后的答案不是在块内，就是相邻两个块的后缀和前缀拼在一起。块内的答案相对好维护一些，大概就是小白逛公园的思路：线段树维护区间答案，区间前缀最大值，区间后缀最大值，合并的时候取左右儿子答案以及左儿子后缀最大值+右儿子前缀最大值三者中最大值即可。然后再开一个线段树维护区间整块的最值即可。

接下来，我们来考虑相邻两个块的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/led5a1o7.png)

假设我们选了两个点 $i$,$j$,那么 $i$ 和 $j$ 之间所要满足的关系是什么？

这样不太好看，我们把右边的块拿下来。
![](https://cdn.luogu.com.cn/upload/image_hosting/24mmp8gb.png)
  
很显然如果每个块内部重新按顺序编号，那么 $j$ < $i$。

那么此时我们就可以用线段树轻松维护掉这个东西，此时线段树中每个元素的值即为前缀和，设前一个块的第i个元素的前缀和为 $a_{i}$,后一个块的第j个元素的前缀和为 $b_{j}$。

我们维护的答案即为$\operatorname*{max}_{j<i}b_{j}-a_{i}$

这个东西也很好维护：线段树维护信息即为区间答案和最大的 $b$ 和最小的 $a$,合并时区间答案即为左右区间答案和左儿子最大的 $b$ 减右儿子最小的 $a$ 三者取最值。同时再开一个线段树维护若干相邻两个块答案最值的最值。

每次查询区间答案即拆分为两个部分：1.块内的最值以及相邻两块最值的最值。2.左右两端的散块和相邻块的答案。

第一个部分可以用线段树快速查询，第二个部分我们先来看位于左端点的散块，

![](https://cdn.luogu.com.cn/upload/image_hosting/ufkmsg7b.png)

此时答案即为绿色部分最大值-黄色部分最小值与线段树查询黄色与蓝色答案取最大值。

右端点处散块同理，不再赘述。

然后，然后就做完了qwq。

总复杂度即为 $O(n\log n)$。

---

## 作者：ZnPdCo (赞：4)

套路地，将数列每 $c$ 个划分为一个块，那么答案的区间要么在一个块内，要么在两个相邻的两个块内。

如果答案在一个块内，这是好处理的，我们处理一个线段树单独维护（也就是开 $\lceil\frac{n}{c}\rceil$ 棵大小为 $c$ 的线段树）每个块的前缀最大值、后缀最大值、区间和以及子段最大值，合并就是左端点后缀最大值与右端点前缀最小值相加取最大值就好了。

因为查询可能涉及多个块，所以我们需要再有一颗线段树维护连续块的答案。

然后观察到相邻的两个块的情况（感谢 for_cat 的图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/led5a1o7.png)

如果 $j-i+1\le c$，要求满足什么？

我们把右边的块拿下来：

![](https://cdn.luogu.com.cn/upload/image_hosting/24mmp8gb.png)

如果我们把每个块的元素重新编号，那么 $j<i$。

那么我们可以维护区间的前缀最大值（是下一个段的），后缀最大值（是这一个段的），区间和，合并的时候就是**左端点前缀**最大值（下一个段的）与**右端点后缀**最小值（这一个段的）相加取最大值就好了。

然后再有一颗线段树维护维护连续块的答案。

---

考虑查询，我们直接处理 $r-l+1\le c$ 的询问，这可以直接做不限制的子段最大值（当然，这可能需要你再开一颗线段树）。

那么对于左右端点处在不相邻的段的情况，我们直接做中间的区间，然后左端点就查询左端点在 $[l,L]$ 的跨段情况，其中 $L$ 代表左端点所在块的右端点。然后右端点就查询左端点在 $[R,r-c]$ 的跨段情况，其中 $R$ 代表 $r-c$ 所在块的左端点。

然后发现可能还有左右端点不跨块的情况，我们再查询 $[l,l+c-1]$ 与 $[r-c+1,r]$ 的情况就好了。

对于左右端点处在相邻的段的情况，我们直接查左端点在 $[l,r-c]$ 的跨段情况，以及 $[l,l+c-1]$ 与 $[r-c+1,r]$ 的情况就好了。

对着题解看感受不出来的，可以先尝试着写一写，然后你就会了。

代码无法通过加强版，需要你把 `cin` 改成快读。

```cpp
#include <bits/stdc++.h>
#define N 400010
#define pos Index(l, r)
#define ls Index(l, mid)
#define rs Index(mid + 1, r)
#define int long long
using namespace std;
int n, m, c, a[N];
int L[N], R[N], idx[N];      // 块的数据
inline int Index(int l, int r) { return l + r | l != r; }
// 区间最大子段和数据
struct data1 {
    int mx, pre, suf, sum;
    data1(int x = 0):mx(max(x, 0ll)), pre(max(x, 0ll)), suf(max(x, 0ll)), sum(x) {}
    friend data1 operator+(const data1& a, const data1& b) {
        data1 c;
        c.mx = max(a.mx, max(b.mx, a.suf + b.pre));
        c.pre = max(a.pre, a.sum + b.pre);
        c.suf = max(b.suf, a.suf + b.sum);
        c.sum = a.sum + b.sum;
        return c;
    }
};
// 前后段和数据
struct data2 {
    // suf是这一段的后缀和，pre是下一段的前缀和，sum1是这一段的和，sum2是下一段的和
    int mx, pre, suf, sum1, sum2;
    data2(int x = 0, int y = 0):mx(max(x, 0ll)), pre(max(y, 0ll)), suf(max(x, 0ll)), sum1(x), sum2(y) {}
    friend data2 operator+(const data2& a, const data2& b) {
        data2 c;
        c.mx = max(a.mx + b.sum1, max(a.sum2 + b.mx, a.pre + b.suf));
        c.pre = max(a.pre, a.sum2 + b.pre);
        c.suf = max(b.suf, b.sum1 + a.suf);
        c.sum1 = a.sum1 + b.sum1;
        c.sum2 = a.sum2 + b.sum2;
        return c;
    }
};
// 全局线段树，维护区间最大子段和
namespace sg1 {
    data1 t[N * 2];
    void build(int l, int r) {
        if (l == r) return (void)(t[pos] = data1(a[l]));
        int mid = (l + r) >> 1;
        build(l, mid);
        build(mid + 1, r);
        t[pos] = t[ls] + t[rs];
    }
    void update(int x, int l, int r) {
        if (l == r) return (void)(t[pos] = data1(a[l]));
        int mid = (l + r) >> 1;
        if (x <= mid) update(x, l, mid);
        else update(x, mid + 1, r);
        t[pos] = t[ls] + t[rs];
    }
    data1 query(int nl, int nr, int l, int r) {
        if (nl > nr) return 0;
        if (nl <= l && r <= nr) return t[pos];
        int mid = (l + r) >> 1;
        data1 res;
        bool flag = 0;
        if (nl <= mid) res = query(nl, nr, l, mid), flag = 1;
        if (mid < nr) {
            if(flag) res = res + query(nl, nr, mid + 1, r);
            else res = query(nl, nr, mid + 1, r);
        }
        return res;
    }
}
// 局部线段树，维护每个块内的元素data1和data2
namespace sg2 {
    data1 t1[N * 2];
    data2 t2[N * 2];
    void build(int l, int r) {
        if (l == r) return (void)(t1[pos] = data1(a[l]), t2[pos] = data2(a[l], a[l + c]));
        int mid = (l + r) >> 1;
        build(l, mid);
        build(mid + 1, r);
        t1[pos] = t1[ls] + t1[rs], t2[pos] = t2[ls] + t2[rs];
    }
    void update(int x, int l, int r) {
        if (l == r) return (void)(t1[pos] = data1(a[l]), t2[pos] = data2(a[l], a[l + c]));
        int mid = (l + r) >> 1;
        if (x <= mid) update(x, l, mid);
        else update(x, mid + 1, r);
        t1[pos] = t1[ls] + t1[rs], t2[pos] = t2[ls] + t2[rs];
    }
    data1 query1(int nl, int nr, int l, int r) {
        if (nl <= l && r <= nr) return t1[pos];
        int mid = (l + r) >> 1;
        data1 res;
        bool flag = 0;
        if (nl <= mid) res = query1(nl, nr, l, mid), flag = 1;
        if (mid < nr) {
            if(flag) res = res + query1(nl, nr, mid + 1, r);
            else res = query1(nl, nr, mid + 1, r);
        }
        return res;
    }
    data2 query2(int nl, int nr, int l, int r) {
        if (nl <= l && r <= nr) return t2[pos];
        int mid = (l + r) >> 1;
        data2 res;
        bool flag = 0;
        if (nl <= mid) res = query2(nl, nr, l, mid), flag = 1;
        if (mid < nr) {
            if(flag) res = res + query2(nl, nr, mid + 1, r);
            else res = query2(nl, nr, mid + 1, r);
        }
        return res;
    }
}
// 维护局部信息的全局线段树，维护每个块内的答案
namespace sg3 {
    int t[N * 2];
    void build(int l, int r) {
        if (l == r) return (void)(t[pos] = max(sg2::query1(L[l], R[l], L[l], R[l]).mx, sg2::query2(L[l], R[l], L[l], R[l]).mx));
        int mid = (l + r) >> 1;
        build(l, mid);
        build(mid + 1, r);
        t[pos] = max(t[ls], t[rs]);
    }
    void update(int x, int l, int r) {
        if (l == r) return (void)(t[pos] = max(sg2::query1(L[l], R[l], L[l], R[l]).mx, sg2::query2(L[l], R[l], L[l], R[l]).mx));
        int mid = (l + r) >> 1;
        if (x <= mid) update(x, l, mid);
        else update(x, mid + 1, r);
        t[pos] = max(t[ls], t[rs]);
    }
    int query(int nl, int nr, int l, int r) {
        if (nl <= l && r <= nr) return t[pos];
        int mid = (l + r) >> 1;
        int res = 0;
        if (nl <= mid) res = max(res, query(nl, nr, l, mid));
        if (mid < nr) res = max(res, query(nl, nr, mid + 1, r));
        return res;
    }
}
inline int query(int l, int r) {
    if(r - l + 1 <= c) return sg1::query(l, r, 1, n).mx;
    int ans = 0;
    if(idx[l] + 1 < idx[r] - 1) ans = max(ans, sg3::query(idx[l] + 1, idx[r] - 2, 1, n / c));
    if(idx[l] + 1 <= idx[r] - 1) ans = max(ans, sg2::query1(L[idx[r] - 1], R[idx[r] - 1], L[idx[r] - 1], R[idx[r] - 1]).mx);
    if(idx[l] + 1 == idx[r]) {
        ans = max(ans, sg2::query2(l, r - c, L[idx[l]], R[idx[l]]).mx + sg1::query(r - c + 1, l + c - 1, 1, n).sum);
    } else {
        ans = max(ans, sg2::query2(l, R[idx[l]], L[idx[l]], R[idx[l]]).mx + sg1::query(L[idx[l] + 1], l + c - 1, 1, n).sum);
        ans = max(ans, sg2::query2(L[idx[r] - 1], r - c, L[idx[r] - 1], R[idx[r] - 1]).mx + sg1::query(r - c + 1, R[idx[r] - 1], 1, n).sum);
    }
    ans = max(ans, sg1::query(l, l + c - 1, 1, n).mx);
    ans = max(ans, sg1::query(r - c + 1, r, 1, n).mx);
    return ans;
}
signed main() {
    cin >> n >> m >> c;
    for (int i = 1; i <= n; i++) cin >> a[i];
    n = (n + c - 1) / c * c;
    for (int i = 1; i <= n; i++) idx[i] = (i - 1) / c + 1, R[idx[i]] = i;
    for (int i = n; i >= 1; i--) L[idx[i]] = i;
    sg1::build(1, n);
    for (int i = 1; i <= n / c; i++) sg2::build(L[i], R[i]);
    sg3::build(1, n / c);
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            a[x] = y;
            sg1::update(x, 1, n);
            sg2::update(x, L[idx[x]], R[idx[x]]);
            sg3::update(idx[x], 1, n / c);
            if (x > c) sg2::update(x - c, L[idx[x] - 1], R[idx[x] - 1]);
            if (x > c) sg3::update(idx[x] - 1, 1, n / c);
        } else {
            cout << query(x, y) << endl;
        }
    }
}
```

---

## 作者：lzyqwq (赞：3)

这玩意还能有双倍经验的？

----

将序列以 $c$ 为块长分块。则对于一个长度为 $c$ 的子区间，她要么在一个块内，要么仅跨过相邻的两个块。

对于一次查询，考虑分成几种贡献：
- Case 1：整块内。
- Case 2：整块间。
- Case 3：散块内。
- Case 4：左右散块与其相邻块的贡献。

----

**Case 1 & 3**

此时贡献为块内最大子段和。对于每个块开一棵线段树 $\text{T1}$ 维护区间最大子段和。散块内部直接查块内答案。对于整块则要查编号在一段区间内的整块的块内最大子段和的最大值。再开一棵线段树 $\text{T3}$ 维护区间最大值。

在 $\text{T1}$ 上单点修改，再把 $\text{T1}$ 中查询得到的块内答案在 $\text{T3}$ 上单点修改。

----

**Case 2**

对于两个相邻的整块，若分别在两边选择端点构成区间 $[i,j]$，记 $\text{pre}_i$ 表示 $i$ 到所在块左端点的前缀和，$\text{suf}_i$ 表示 $i$ 到所在块右端点的后缀和，则答案为 $\text{suf}_i+\text{pre}_j$，要求 $j-i+1\le c$。令 $k=j-c$，则 $k$ 和 $i$ 在同一个块内。记 $a_i=\text{suf}_i$，$b_k=\text{pre}_{k+c}$，则等价于块内选一对 $(k,i)$ 使得 $k+c-i+1\le c$ 即 $k<i$ 的基础上 $a_i+b_k$ 最大化。

用线段树维护区间内 $a_i,b_k$ 最大值和 $k<i$ 的 $a_i+b_k$ 最大值，合并时考虑是否跨过中点。则要求对一段连续编号的整块求这个东西的最大值，再开一颗线段树 $\text{T4}$ 维护。

修改对应的是修改位置所在块及其上一个块的 $a_i/b_k$ 区间加。然后把这两个块的信息重新单点修改到 $\text{T4}$ 上。

----

**Case 4**

先把区间长度 $\le c$ 判掉，此时要一个全局区间最大子段和的线段树。剩余的问题形如给出两个长度不超过 $c$ 且相邻的区间 $[x,y],[u,v]$，在两边各选一个数 $i,j$ 使得 $j-i+1\le c$ 且最大化 $[i,j]$ 的和。

类似 Case 2 那样，令 $u\leftarrow u-c,v\leftarrow v-c$，选出 $(i,k)$ 使得 $a_i+b_k$ 最大且 $k<i$。则此时 $u\le x$。

若 $x>v$，则两个区间不交，直接取每部分最大值即可。

否则，分成 $k$ 分别属于 $[u,x),[x,v]$ 两类考虑。

对于前者，$k,i$ 所在区间不交，直接取每部分最大值即可。对于后者，若 $i\in[x,v]$，则相当于在 $[x,v]$ 这个区间内查询 $a_i+b_k$ 且 $k<i$ 的最大值，在 $x$ 所在块的 $\text{T2}$ 上查询即可。否则两部分仍然不交，取各部分最大值。

----

做完了。时间复杂度为 $\mathcal{O}(m\log n)$，空间复杂度为 $\mathcal{O}(n)$。

卡常技巧：

- `inline`。
- 用 `vector` 对每个块开线段树，这样 $\log$ 会小一点，并且在 $\text{T3,T4}$ 上修改时直接查对应块线段树上根节点的信息即可，是 $\mathcal{O}(1)$ 的。
- 指令集。


```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define il inline
using namespace std; typedef long long ll;
const int N = 500005, M = 200005; const ll inf = 1e18;
int n, m, c, a[M], be[M], bl[M], br[M]; ll pre[N], suf[N];
il int ls(int x) { return x << 1; } il int rs(int x) { return x << 1 | 1; }
struct node {
	ll sl, sr, sm, st; il void I(int x) { sl = sr = sm = st = x; }
	il node operator+(const node &o) const {
		node rt; rt.st = st + o.st; rt.sl = max(sl, st + o.sl);
		rt.sr = max(o.sr, o.st + sr); rt.sm = max({sm, o.sm, sr + o.sl}); return rt;
	}
};
struct Node {
	ll ma, mb, ms; il void I(ll x, ll y) { ma = x; mb = y; ms = -inf; }
	il void U(ll x, ll y) { ma += x; mb += y; ms += x + y; }
	il Node operator+(const Node &o) const {
		Node rt; rt.ma = max(ma, o.ma); rt.mb = max(mb, o.mb);
		rt.ms = max({ms, o.ms, ma + o.mb}); return rt;
	}
};
struct SGT_IN {
	int L, R; vector<node> s;
	void B(int x, int l, int r) {
		if (l == r) return s[x].I(a[l]); int m = l + r >> 1;
		B(ls(x), l, m); B(rs(x), m + 1, r); s[x] = s[ls(x)] + s[rs(x)];
	}
	il void B(int l, int r) {
		L = l; R = r; s = vector<node>(r - l + 1 << 2); B(1, l, r);
	}
	void U(int x, int l, int r, int k, int v) {
		if (l == r) return s[x].I(v); int m = l + r >> 1;
		if (k <= m) U(ls(x), l, m, k, v); else U(rs(x), m + 1, r, k, v);
		s[x] = s[ls(x)] + s[rs(x)];
	}
	il void U(int k, int v) { U(1, L, R, k, v); }
	node Q(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return s[x]; int m = l + r >> 1;
		if (qr <= m) return Q(ls(x), l, m, ql, qr);
		if (ql > m) return Q(rs(x), m + 1, r, ql, qr);
		return Q(ls(x), l, m, ql, qr) + Q(rs(x), m + 1, r, ql, qr);
	}
	il node Q(int l, int r) { return Q(1, L, R, l, r); }
}; vector<SGT_IN> t1;
struct SGT_BETWEEN {
	int L, R; vector<Node> s; vector<ll> ta, tb;
	void B(int x, int l, int r) {
		if (l == r) return s[x].I(pre[l + c], suf[l]); int m = l + r >> 1;
		B(ls(x), l, m); B(rs(x), m + 1, r); s[x] = s[ls(x)] + s[rs(x)];
	}
	il void B(int l, int r) {
		L = l; R = r; int len = r - l + 1; s = vector<Node>(len << 2);
		ta = tb = vector<ll>(len << 2); B(1, L, R);
	}
	void U(int x, int l, int r, int ql, int qr, ll va, ll vb) {
		if (ql <= l && r <= qr)
			return s[x].U(va, vb), ta[x] += va, tb[x] += vb, void();
		int m = l + r >> 1; if (ql <= m) U(ls(x), l, m, ql, qr, va, vb);
		if (qr > m) U(rs(x), m + 1, r, ql, qr, va, vb);
		s[x] = s[ls(x)] + s[rs(x)]; s[x].U(ta[x], tb[x]);
	}
	il void U(int l, int r, ll va, ll vb) { U(1, L, R, l, r, va, vb); }
	Node Q(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return s[x]; int m = l + r >> 1; Node rt;
		if (qr <= m) rt = Q(ls(x), l, m, ql, qr);
		else if (ql > m) rt = Q(rs(x), m + 1, r, ql, qr);
		else rt = Q(ls(x), l, m, ql, qr) + Q(rs(x), m + 1, r, ql, qr);
		rt.U(ta[x], tb[x]); return rt;
	}
	il Node Q(int l, int r) { return Q(1, L, R, l, r); }
	ll QA(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return s[x].ma; int m = l + r >> 1; ll rt;
		if (qr <= m) rt = QA(ls(x), l, m, ql, qr);
		else if (ql > m) rt = QA(rs(x), m + 1, r, ql, qr);
		else rt = max(QA(ls(x), l, m, ql, qr), QA(rs(x), m + 1, r, ql, qr));
		return rt + ta[x];
	}
	il ll QA(int l, int r) { return QA(1, L, R, l, r); }
	ll QB(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return s[x].mb; int m = l + r >> 1; ll rt;
		if (qr <= m) rt = QB(ls(x), l, m, ql, qr);
		else if (ql > m) rt = QB(rs(x), m + 1, r, ql, qr);
		else rt = max(QB(ls(x), l, m, ql, qr), QB(rs(x), m + 1, r, ql, qr));
		return rt + tb[x];
	}
	il ll QB(int l, int r) { return QB(1, L, R, l, r); }
}; vector<SGT_BETWEEN> t2;
struct SGT_RANGE_MAX {
	ll mx[M << 2];
	il void C(int x, int p, bool o) { mx[x] = (o ? t1[p].s[1].sm : t2[p].s[1].ms); }
	void B(int x, int l, int r, bool o) {
		if (l == r) return C(x, l, o); int m = l + r >> 1;
		B(ls(x), l, m, o); B(rs(x), m + 1, r, o); mx[x] = max(mx[ls(x)], mx[rs(x)]);
	}
	void U(int x, int l, int r, int k, bool o) {
		if (l == r) return C(x, l, o); int m = l + r >> 1;
		if (k <= m) U(ls(x), l, m, k, o); else U(rs(x), m + 1, r, k, o);
		mx[x] = max(mx[ls(x)], mx[rs(x)]);
	}
	ll Q(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return mx[x]; int m = l + r >> 1;
		if (qr <= m) return Q(ls(x), l, m, ql, qr);
		if (ql > m) return Q(rs(x), m + 1, r, ql, qr);
		return max(Q(ls(x), l, m, ql, qr), Q(rs(x), m + 1, r, ql, qr));
	}
} t3, t4;
il ll san(int l, int r, int x, int y) {
	x -= c; y -= c; ll ret = 0;
	if (y >= l) {
		Node t = t2[be[x]].Q(l, y); ret = max(ret, t.ms);
		if (x < l) ret = max(ret, t2[be[x]].QA(x, l - 1) + t2[be[x]].QB(l, r));
		if (r > y) ret = max(ret, t2[be[x]].QB(y + 1, r) + t.ma);
	} else ret = max(ret, t2[be[x]].QA(x, y) + t2[be[x]].QB(l, r)); return ret;
}
int main() {
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), be[i] = (i - 1) / c + 1;
	t1 = vector<SGT_IN>(be[n] + 1); t2 = vector<SGT_BETWEEN>(be[n] + 1);
	for (int i = 1; i <= be[n]; ++i) {
		bl[i] = br[i - 1] + 1, br[i] = min(n, i * c); t1[i].B(bl[i], br[i]);
		pre[bl[i]] = a[bl[i]]; suf[br[i]] = a[br[i]];
		for (int j = bl[i] + 1; j <= br[i]; ++j) pre[j] = pre[j - 1] + a[j];
		for (int j = br[i] - 1; j >= bl[i]; --j) suf[j] = suf[j + 1] + a[j];
		 
	}
	for (int i = 1; i <= be[n]; ++i) t2[i].B(bl[i], br[i]);
	t1[0].B(1, n); t3.B(1, 1, be[n], 1); t4.B(1, 1, be[n], 0);
	for (int op, x, y, d; m--;) {
		scanf("%d%d%d", &op, &x, &y); ll ans = 0;
		if (op & 1) {
			t1[0].U(x, y); t1[be[x]].U(x, y);
			t3.U(1, 1, be[n], be[x], 1); d = y - a[x]; a[x] = y;
			t2[be[x]].U(bl[be[x]], x, 0, d); t4.U(1, 1, be[n], be[x], 0);
			if (be[x] > 1)
				t2[be[x] - 1].U(x - c, br[be[x]] - c, d, 0),
				t4.U(1, 1, be[n], be[x] - 1, 0);
		} else {
			if (y - x < c) {
				printf("%lld\n", max(0ll, t1[0].Q(x, y).sm)); continue;
			}
			if (be[x] < be[y] - 1)
				ans = max(ans, t3.Q(1, 1, be[n], be[x] + 1, be[y] - 1));
			if (be[x] < be[y] - 2)
				ans = max(ans, t4.Q(1, 1, be[n], be[x] + 1, be[y] - 2));
			ans = max({ans, t1[be[x]].Q(x, br[be[x]]).sm,
			                t1[be[y]].Q(bl[be[y]], y).sm});
			if (be[x] < be[y] - 1)
				ans = max({ans, san(x, br[be[x]], bl[be[x] + 1], br[be[x] + 1]),
				                san(bl[be[y] - 1], br[be[y] - 1], bl[be[y]], y)});
			else ans = max(ans, san(x, br[be[x]], bl[be[y]], y));
			printf("%lld\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：llingy (赞：3)

## 题目描述

给定序列 $a_1,\dots,a_n$ 和常数 $c$，$m$ 次询问，每次询问给出 $l,r$，询问所有满足 $l\le l^\prime \le r^\prime\le r$ 且 $r^\prime-l^\prime+1\le c$ 的 $[l^\prime,r^\prime]$ 区间和的最大值。

## 思路

按照 $c$ 分块，则合法的答案必然完全在一个块内或者是一个块的后缀和下一块的前缀拼接得来。

对于块内的问题，我们仅需使用线段树维护不加任何限制的最大子段和即可，由于块数可能很多，因此还要再使用另外一颗线段树维护区间内所有块内部的最大子段和的最大值。

对于块间的问题，预处理出当前块的后缀和 $f$ 和下一块的前缀和 $g$，下标均从 $1$ 开始。记当前块左端点为 $S$。若区间 $[l^\prime,r^\prime]$ 是满足条件的，则要求 $r^\prime-c\lt l^\prime$，此时区间和可表示为 $f_{l^\prime-S+1}+g_{r^\prime-c-S+1}$，即对于 $f_i$ 和 $g_j$，若 $j<i$，则 $f_i+g_j$ 恰好对应一个合法区间的和。因此，对于每一块维护一颗线段树，线段树上维护该和最大值即可。同块内的问题一样，仍需另外一颗线段树维护区间内所有块与下一块拼接的最大值。

在查询时，先判掉 $r-l+1\le c$ 的所有询问，这些询问仅需输出这个区间内的最大子段和。

对于 $l,r$ 所在块不相邻的询问，中间所有块的贡献可以用上述两个维护最大值的线段树得到。两边的散块内部的贡献仅需查询对应区间的最大子段和。记左端点所在块的最左端为 $L$，右端点所在块的最左端 $R$。散块与相邻整块的拼接产生的贡献仅需在 $l$ 所在块的线段树上查询区间 $[l-L+1,c]$，在 $r$ 所在块左侧块的线段树上查询区间 $[1,r-R+1]$ 即可包含所有情况。

对于 $l,r$ 位于相邻两块的询问，仿照上一部分，在 $l$ 所在块内的线段树上查询区间 $[l-L+1,r-R+1]$，但是这并未包含两散块拼接产生所有情况。具体的，漏了所有左端点 $l^\prime$ 位于 $(r-c,L+c-1]$ 中的区间，但是发现此时 $l^\prime$ 到 $r$ 的距离小于 $c$，仅需查询 $[r-c+1,r]$ 内的最大子段和即可包括这部分贡献。同理，仅需查询 $[l,l+c-1]$ 对应的最大子段和即可包括 $r^\prime$ 在 $[R,l+c)$ 内的所有区间的贡献。

总时间复杂度 $O(n\log n)$，但是常数巨大。


## Code

```cpp
constexpr int N=2e5+5;using ll=long long;constexpr ll inf=1e18;
#define lsc ro<<1
#define rsc ro<<1|1
#define now tree[ro]
struct sg1
{
    struct dat{ll lmx,rmx,sum,ans;inline dat()=default;inline dat(ll x):lmx(x),rmx(x),sum(x),ans(x){}};
    inline friend dat operator+(const dat&x,const dat&y)
    {
        dat res;res.sum=x.sum+y.sum;
        res.lmx=max(x.lmx,y.lmx+x.sum);
        res.rmx=max(y.rmx,x.rmx+y.sum);
        res.ans=max({x.ans,y.ans,x.rmx+y.lmx});
        return res;
    }
    struct node{int l,r;dat w;}tree[N<<2];
    inline void push_up(int ro){now.w=tree[lsc].w+tree[rsc].w;}
    inline void build(int ro,int l,int r,ll a[])
    {
        now.l=l,now.r=r;if(l==r) return now.w=dat(a[l]),void();
        int mid=(l+r)>>1;build(lsc,l,mid,a);build(rsc,mid+1,r,a);
        push_up(ro);
    }
    inline void update(int ro,int pos,ll x)
    {
        if(now.l==now.r) return now.w=dat(x),void();
        int mid=(now.l+now.r)>>1;
        if(pos<=mid) update(lsc,pos,x);
        else update(rsc,pos,x);
        push_up(ro);
    }
    inline dat query(int ro,int l,int r)
    {
        if(l==now.l&&now.r==r) return now.w;
        int mid=(now.l+now.r)>>1;
        if(r<=mid) return query(lsc,l,r);
        else if(l>mid) return query(rsc,l,r);
        else return query(lsc,l,mid)+query(rsc,mid+1,r);
    }
}t1;
struct sg2
{
    struct dat{ll lmx,rmx,ans;inline dat()=default;inline dat(ll x,ll y):lmx(x),rmx(y),ans(-inf){}};
    inline friend dat operator+(const dat&x,const dat&y)
    {
        dat res;res.lmx=max(x.lmx,y.lmx);res.rmx=max(x.rmx,y.rmx);
        res.ans=max({x.ans,y.ans,x.rmx+y.lmx});return res;
    }
    struct node{int l,r;dat w;ll t1,t2;};
    static node bt[N<<2],*nt;node*tree;
    inline void init(int n){tree=nt;nt+=n*4;}
    inline void push_up(int ro){now.w=tree[lsc].w+tree[rsc].w;}
    inline void push_tag(int ro,ll t1,ll t2)
    {
        now.w.lmx+=t1;now.w.ans+=t1+t2;
        now.w.rmx+=t2;now.t1+=t1;now.t2+=t2;
    }
    inline void push_down(int ro)
    {
        if(!now.t1&&!now.t2) return;
        push_tag(lsc,now.t1,now.t2);
        push_tag(rsc,now.t1,now.t2);
        now.t1=now.t2=0;
    }
    inline void build(int ro,int l,int r,ll a1[],ll a2[])
    {
        now.l=l,now.r=r;int mid=(now.l+now.r)>>1;
        if(l==r) return now.w=dat(a1[l],a2[l]),void();
        build(lsc,l,mid,a1,a2);build(rsc,mid+1,r,a1,a2);push_up(ro);
    }
    inline dat query(int ro,int l,int r)
    {
        if(now.l==l&&now.r==r) return now.w;
        int mid=(now.l+now.r)>>1;push_down(ro);
        if(r<=mid) return query(lsc,l,r);
        else if(l>mid) return query(rsc,l,r);
        else return query(lsc,l,mid)+query(rsc,mid+1,r);
    }
    inline void update(int ro,int l,int r,ll t1,ll t2)
    {
        if(l<=now.l&&now.r<=r) return push_tag(ro,t1,t2);
        int mid=(now.l+now.r)>>1;push_down(ro);
        if(l<=mid) update(lsc,l,r,t1,t2);
        if(r>mid) update(rsc,l,r,t1,t2);
        push_up(ro);
    }
}t2[N];sg2::node sg2::bt[N<<2],*sg2::nt=bt;
struct sg3
{
    struct node{int l,r;ll w;}tree[N<<2];
    inline void push_up(int ro){now.w=max(tree[lsc].w,tree[rsc].w);}
    inline void build(int ro,int l,int r)
    {
        now.l=l,now.r=r;if(l==r) return;
        int mid=(now.l+now.r)>>1;
        build(lsc,l,mid);build(rsc,mid+1,r);
    }
    inline void update(int ro,int pos,ll x)
    {
        if(now.l==now.r) return now.w=x,void();
        int mid=(now.l+now.r)>>1;
        if(pos<=mid) update(lsc,pos,x);
        else update(rsc,pos,x);
        push_up(ro);
    }
    inline ll query(int ro,int l,int r)
    {
        if(now.l==l&&now.r==r) return now.w;
        int mid=(now.l+now.r)>>1;
        if(r<=mid) return query(lsc,l,r);
        else if(l>mid) return query(rsc,l,r);
        else return max(query(lsc,l,mid),query(rsc,mid+1,r));
    }
}t3,t4;
ll a[N],p1[N],p2[N];int bel[N],L[N],R[N];
inline void work()
{
    using namespace IO;
    int n,m,B,btot;qread(n),qread(m),qread(B);btot=(n-1)/B+1;
    for(int i=1;i<=n;i++) bel[i]=(i-1)/B+1,R[bel[i]]=i,qread(a[i]);
    for(int i=n;i;i--) L[bel[i]]=i; 
    t1.build(1,1,n,a);t3.build(1,1,btot);t4.build(1,1,btot);
    for(int i=1;i<=btot;i++)
    {
        t3.update(1,i,t1.query(1,L[i],R[i]).ans);
        if(i==btot) continue;
        t2[i].init(R[i]-L[i]+1);p2[L[i+1]-1]=0;
        for(int j=R[i];j>=L[i];j--) p1[j]=p1[j+1]+a[j];
        for(int j=L[i+1];j<=R[i+1];j++) p2[j]=p2[j-1]+a[j];
        t2[i].build(1,1,R[i]-L[i]+1,p1+L[i]-1,p2+L[i+1]-1);
        t4.update(1,i,t2[i].tree[1].w.ans);
    }
    while(m--)
    {
        int op,l,r;qread(op),qread(l),qread(r);
        if(op==1)
        {
            int bl=bel[l];ll dt=r-a[l];a[l]=r;t1.update(1,l,r);t3.update(1,bl,t1.query(1,L[bl],R[bl]).ans);
            if(bl!=btot) t2[bl].update(1,1,l-L[bl]+1,dt,0),t4.update(1,bl,t2[bl].tree[1].w.ans);
            if(bl!=1) t2[bl-1].update(1,l-L[bl]+1,R[bl-1]-L[bl-1]+1,0,dt),t4.update(1,bl-1,t2[bl-1].tree[1].w.ans);
        }
        else
        {
            ll ans=0;if(r-l+1<=B) ans=max(0ll,t1.query(1,l,r).ans);
            else
            {
                ans=max({ans,t1.query(1,l,l+B-1).ans,t1.query(1,r-B+1,r).ans});
                if(bel[l]+1==bel[r]) ans=max(ans,t2[bel[l]].query(1,l-L[bel[l]]+1,r-L[bel[r]]+1).ans);
                else
                {
                    ans=max({ans,t3.query(1,bel[l]+1,bel[r]-1),t2[bel[l]].query(1,l-L[bel[l]]+1,B).ans,t2[bel[r]-1].query(1,1,r-L[bel[r]]+1).ans});
                    if(bel[l]+2!=bel[r]) ans=max(ans,t4.query(1,bel[l]+1,bel[r]-2));
                }
            }
            qwrite(ans),pc('\n');
        }
    }
}
```

---

## 作者：Purslane (赞：2)

# Solution

对于这种限定子区间长度的问题，考虑按照 $C$ 分块。

块内所有子区间显然都满足，所以可以用一个线段树维护区间内最大子段和。

考虑跨过两个块的子区间。假设这两个块分别是 $x_1x_2\cdots x_c$ 以及 $y_1y_2 \cdots y_c$。

那么我们选取 $l$ 和 $r$ 满足 $c-l+1+r \le c$，并最大化 $\sum_{i=l}^c x_i + \sum_{j=1}^r y_j$。

限制可以转化为 $l > r$。所以我们开一棵线段树维护 $(x,y)$，很容易单点修改维护最大值。

对于区间询问，我们可能会限制 $l \le l_0$，$r \ge r_0$。我们特判掉区间很短的情况之后，一定有 $[1,l_0] \cap [r_0,c] \neq \varnothing$。分类讨论 $l$ 和 $r$ 的位置即可。别忘了在散块内的共线。复杂度 $O((n+q) \log n)$。

由于所有修改都是单点修改，考虑使用 zkw 线段树以减少常数。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
const ll INF=1e16;
int n,q,c,k,a[MAXN],L[MAXN],R[MAXN],bel[MAXN],rev[MAXN];
ll mx1[MAXN<<2],mx2[MAXN<<2];
struct INFO1 {ll sum,lmx,rmx,ans;}t[MAXN<<2];
struct INFO2 {ll sumx,sumy,lmx,rmx,ans;}tt[MAXN<<2];
inline INFO1 operator +(const INFO1 A,const INFO1 B) {return {A.sum+B.sum,max(A.lmx,A.sum+B.lmx),max(B.rmx,B.sum+A.rmx),max(max(A.ans,B.ans),A.rmx+B.lmx)};}
inline INFO2 operator +(const INFO2 A,const INFO2 B) {return {A.sumx+B.sumx,A.sumy+B.sumy,max(A.lmx,A.sumx+B.lmx),max(B.rmx,B.sumy+A.rmx),max(max(A.ans+B.sumy,B.ans+A.sumx),A.lmx+B.rmx)};}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void build(int k,int l,int r) {
	if(l==r) return rev[l]=k,void();
	build(lson,l,mid),build(rson,mid+1,r);
	return ;	
}
void update1(int pos,int v) {
	int k=rev[pos];
	t[k]={v,max(v,0),max(v,0),max(v,0)};
	while(k!=1) k>>=1,t[k]=t[lson]+t[rson];
	return ;	
}
void update2(int pos,int v,int op) {
	int k=rev[pos];
	if(op==1) tt[k].sumx=v,tt[k].lmx=max(0,v);
	else tt[k].sumy=v,tt[k].rmx=max(0,v);
	while(k!=1) k>>=1,tt[k]=tt[lson]+tt[rson];
	return ;
}
void update3(int pos,ll v) { //修改 mx1，即段内
	int k=rev[pos];
	mx1[k]=v;
	while(k!=1) k>>=1,mx1[k]=max(mx1[lson],mx1[rson]);
	return ;	
}
void update4(int pos,ll v) {
	int k=rev[pos];
	mx2[k]=v;
	while(k!=1) k>>=1,mx2[k]=max(mx2[lson],mx2[rson]);
	return ;	
}
INFO1 query1(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k];
	if(y<=mid) return query1(lson,l,mid,x,y);
	if(x>mid) return query1(rson,mid+1,r,x,y);
	return query1(lson,l,mid,x,y)+query1(rson,mid+1,r,x,y);
}
INFO2 query2(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return tt[k];
	if(y<=mid) return query2(lson,l,mid,x,y);
	if(x>mid) return query2(rson,mid+1,r,x,y);
	return query2(lson,l,mid,x,y)+query2(rson,mid+1,r,x,y);	
}
ll query3(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return mx1[k];
	if(y<=mid) return query3(lson,l,mid,x,y);
	if(x>mid) return query3(rson,mid+1,r,x,y);
	return max(query3(lson,l,mid,x,y),query3(rson,mid+1,r,x,y)); 
}
ll query4(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return mx2[k];
	if(y<=mid) return query4(lson,l,mid,x,y);
	if(x>mid) return query4(rson,mid+1,r,x,y);
	return max(query4(lson,l,mid,x,y),query4(rson,mid+1,r,x,y));	
}
ll solve(int id,int l,int r) {
	INFO2 A,B,C;
	A={0,0,0,0,0},B={0,0,0,0,0},C={0,0,0,0,0};
	if(L[id]<=l-1) A=query2(1,1,n,L[id],l-1);
	A.sumy=-INF,A.rmx=-INF,A.ans=-INF;
	if(l<=r-c) B=query2(1,1,n,l,r-c);
	if(r-c+1<=R[id]) C=query2(1,1,n,r-c+1,R[id]);
	C.sumx=-INF,C.lmx=-INF,C.ans=-INF;
	return (A+B+C).ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q>>c;
	build(1,1,n);
	k=(n+c-1)/c;
	ffor(i,1,k) L[i]=R[i-1]+1,R[i]=min(n,i*c);
	ffor(i,1,k) ffor(j,L[i],R[i]) bel[j]=i; 
	ffor(i,1,n) cin>>a[i],update1(i,a[i]);
	ffor(i,1,k-1) ffor(j,L[i],R[i]) update2(j,a[j],2);
	ffor(i,2,k) ffor(j,L[i],R[i]) update2(j-c,a[j],1);
	ffor(i,1,k) update3(i,query1(1,1,n,L[i],R[i]).ans);
	ffor(i,1,k-1) update4(i,query2(1,1,n,L[i],R[i]).ans);
	
	ffor(i,1,q) {
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1) {
			update1(l,r);
			if(bel[l]!=k) update2(l,r,2);
			if(bel[l]!=1) update2(l-c,r,1);
			int id=bel[l];
			update3(id,query1(1,1,n,L[id],R[id]).ans);
			if(id!=k) update4(id,query2(1,1,n,L[id],R[id]).ans);
			if(id!=1) id--,update4(id,query2(1,1,n,L[id],R[id]).ans);
			a[l]=r;	
		}
		else {
			if(r-l+1<=c) cout<<query1(1,1,n,l,r).ans<<'\n';
			else {
				ll ans=0;
				int kl=bel[l]+1,kr=bel[r]-1;
				ans=max(ans,query1(1,1,n,l,R[bel[l]]).ans);
				ans=max(ans,query1(1,1,n,L[bel[r]],r).ans);
				if(kl<=kr) ans=max(ans,query3(1,1,n,kl,kr));
				if(bel[l]+1<=bel[r]-2) ans=max(ans,query4(1,1,n,bel[l]+1,bel[r]-2));
				if(bel[l]==bel[r]-1) ans=max(ans,solve(bel[l],l,r));
				else ans=max(ans,solve(bel[l],l,R[bel[l]+1])),ans=max(ans,solve(bel[r]-1,L[bel[r]-1],r));
				cout<<ans<<'\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：dengchengyu (赞：2)

# P9877 [EC Final 2021] Vacation 题解

题目大意：给定常数 $C$，若干次询问一个区间内长度为 $[0,C]$ 的子段和的最大值，支持单点修改。

考虑把序列每 $C$ 个分一块，分成 $\lceil\frac nc\rceil$ 块。那么发现符合条件的子段只可能在一个块内或相邻两个块内。

## 在一个块内的情况

那么问题转化为了求区间的最大子段和，这个问题是经典的，即 [GSS3](https://www.luogu.com.cn/problem/SP1716)。这里复述一遍做法：

* 用线段树做，线段树上的每个节点维护区间内总和、最大前缀和、最大后缀和、最大子段和。转移时容易的。

那么对每个块开一棵维护最大子段和的线段树，然后再对全局开一棵线段树维护每个块的最大子段和的最大值用于区间查询。

## 在相邻两个块的情况

考虑一个符合条件的区间满足什么条件，对于 $l\le kC<r$，要满足 $r-l+1\le C$ 即 $r-C<l$。

设 $a_i$ 为 $l=i$ 时 $l$ 所在块中以 $l$ 开始的后缀和，$b_i$ 为 $r=i+C$ 时 $r$ 所在块中以 $r$ 结束的前缀和。那么这两个相邻区间的贡献就是满足 $j<i$ 的 $a_i+b_j$ 的最大值。

那么对每相邻两个块开一棵线段树，每个节点分别维护区间内 $a,b$ 的最大值，同时维护上述 $i,j$ 都在区间内时的答案 $ans$，那么合并区间时，$ans_x=\max(ans_{lson},ans_{rson},b_{lson}+a_{rson})$。

然后由于单点修改时会导致块内一个区间的前缀和或后缀和改变，所以我们还要维护一个区间加标记，用正常方式下传即可，当区间的 $a$ 或 $b$ 加 $x$ 时，$ans$ 也要加 $x$（前提是区间长度大于 $1$）。

同时如上一节，需要对全局开一个线段树维护每相邻两个块的答案的最大值，以便于区间查询。

## 对于散块的情况

对于整块的情况直接在我们开的全局的线段树上查询即可。现在考虑散块的情况。

**询问的  $l,r$ 在同一个块内的情况**：

此时直接查询区间最大子段和。

**询问的 $l,r$ 之间间隔至少一个块的情况：**

此时除了整块的贡献，还有以下贡献：

* 两个散块内的贡献。
* 两个散块与它们相邻整块之间的贡献。

对于两个散块内的贡献，直接查询区间最大子段和。

对于散块与整块之间的贡献，我们以左边的散块为例。我们设造成贡献的区间为左右端点为 $i,j$，询问的左端点为 $l$，这里的 $i,j,l$ 为对应在块中的编号，它们的取值都为 $[1,C]$。

贡献有两种，分别为 $l\le j<i\le C$ 与 $1\le j<l\land l\le i\le C$，前者直接查询区间内的答案，后者分别查询区间内 $b$ 与 $a$ 的最大值即可。

**询问的 $l,r$ 在相邻两个块的情况：**

如果不跨过块，依旧是分别查询区间最大子段和。

考虑跨过块：这里 $l,r$ 依然代表在对应块中的编号。

* 如果 $r<l$，分别查询 $[1,r]$ 中 $b$ 与 $[l,C]$ 中 $a$ 的最大值即可。
* 否则 $l\le r$，考虑到贡献有三种 $1\le j\le r\land r<i\le C$ 和 $1<l\land l\le i\le C$ 和 $l\le j<i\le r$，都是查询对应区间的 $a,b,ans$ 就可以计算。

## 时间复杂度与常数

最多使用了区间加懒标记的线段树，时间复杂度 $O(m\log n)$，对于每一个块的线段树可以考虑使用 `vector` 开空间。

常数方面，对于我的代码，修改最多调用 $6$ 次函数，查询一个块最多 $1$ 次，查询相邻块最多 $7$ 次，查询相隔至少一个块最多 $8$ 次。

可以稳过，对于[加强版](https://www.luogu.com.cn/problem/P6780)也可以通过。

## 其他细节

这里对于不满 $C$ 的块我补满了 $C$，因此数组大小最大是 $2n$ 的。

## 代码实现

[评测记录一](https://www.luogu.com.cn/record/211558333)，[评测记录二](https://www.luogu.com.cn/record/211558581)。

```cpp
struct arr1 {
	ll ans,maxa,maxb;
	arr1 operator+(arr1 x) {
		return {
			max(max(ans,x.ans),maxb+x.maxa),
			max(maxa,x.maxa),
			max(maxb,x.maxb),
		};
	}
};
struct arr2 {
	ll ans,pre,suf,sum;
	arr2 operator+(arr2 x) {
		return {
			max(max(ans,x.ans),suf+x.pre),
			max(pre,sum+x.pre),
			max(suf+x.sum,x.suf),
			sum+x.sum
		};
	}
};
struct tree1 {
	vector<arr1> s;
	vector<ll> ta,tb;
	void resize() {
		s.resize(C*4+5);
		ta.resize(C*4+5);
		tb.resize(C*4+5);
	}
	void make(int x,int l,int r,ll *a,ll *b) {
		if(l==r) {
			s[x].maxa=a[C]-a[l-1];
			s[x].maxb=b[l]-b[0];
			s[x].ans=-9e18;
			return;
		}
		make(ls,l,mid,a,b),make(rs,mid+1,r,a,b);
		s[x]=s[ls]+s[rs];
	}
	void pushdown(int x,int l,int r) {
		if(ta[x]) {
			s[x].maxa+=ta[x];
			if(l<r) s[x].ans+=ta[x],ta[ls]+=ta[x],ta[rs]+=ta[x];
			ta[x]=0;
		}
		if(tb[x]) {
			s[x].maxb+=tb[x];
			if(l<r) s[x].ans+=tb[x],tb[ls]+=tb[x],tb[rs]+=tb[x];
			tb[x]=0;
		}
	}
	void add(int x,int l,int r,int L,int R,int opt,int y) {
		if(L<=l&&r<=R) {
			if(opt==0) ta[x]+=y;
			else tb[x]+=y;
			pushdown(x,l,r);
			return;
		}
		pushdown(x,l,r);
		if(R<l||r<L) return;
		add(ls,l,mid,L,R,opt,y),add(rs,mid+1,r,L,R,opt,y);
		s[x]=s[ls]+s[rs];
	}
	arr1 query(int x,int l,int r,int L,int R) {
		pushdown(x,l,r);
		if(L<=l&&r<=R) return s[x];
		if(L<=mid&&R>mid) return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
		if(L<=mid) return query(ls,l,mid,L,R);
		return query(rs,mid+1,r,L,R);
	}
}tr1[N];
struct tree2 {
	vector<arr2> s;
	void resize() {
		s.resize(C*4+5);
	}
	void make(int x,int l,int r,int *a) {
		if(l==r) {
			s[x].ans=s[x].pre=s[x].suf=s[x].sum=a[l];
			return;
		}
		make(ls,l,mid,a),make(rs,mid+1,r,a);
		s[x]=s[ls]+s[rs];
	}
	void update(int x,int l,int r,int y,int z) {
		if(l==r) {
			s[x].ans=s[x].pre=s[x].suf=s[x].sum=z;
			return;
		}
		if(y<=mid) update(ls,l,mid,y,z);
		else update(rs,mid+1,r,y,z);
		s[x]=s[ls]+s[rs];
	}
	arr2 query(int x,int l,int r,int L,int R) {
		if(L<=l&&r<=R) return s[x];
		if(L<=mid&&R>mid) return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
		if(L<=mid) return query(ls,l,mid,L,R);
		return query(rs,mid+1,r,L,R);
	}
}tr2[N];
struct tree3 {
	ll s[N*4];
	void update(int x,int l,int r,int y,ll z) {
		if(l==r) {
			s[x]=z;
			return;
		}
		if(y<=mid) update(ls,l,mid,y,z);
		else update(rs,mid+1,r,y,z);
		s[x]=max(s[ls],s[rs]);
	}
	ll query(int x,int l,int r,int L,int R) {
		if(L<=l&&r<=R) return s[x];
		if(R<l||r<L) return 0;
		return max(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
	}	
}tr3,tr4;
int n,m,a[N];
ll pre[N];
signed main(){
	read(n,m,C);
	fo(i,1,n) read(a[i]),pre[i]=pre[i-1]+a[i];
	fo(i,0,bn(n)-1) {
		tr1[i].resize();
		tr1[i].make(1,1,C,pre+i*C,pre+i*C+C);
		tr3.update(1,0,bn(n),i,tr1[i].s[1].ans);
	}
	fo(i,0,bn(n)) {
		tr2[i].resize(), tr2[i].make(1,1,C,a+i*C);
		tr4.update(1,0,bn(n),i,tr2[i].s[1].ans);
	}
	while(m--) {
		int opt; read(opt);
		if(opt==1) {
			int x,y; read(x,y);
			tr2[bn(x)].update(1,1,C,x-bn(x)*C,y);
			tr4.update(1,0,bn(n),bn(x),tr2[bn(x)].s[1].ans);
			if(bn(x)>0) 
				tr1[bn(x)-1].add(1,1,C,x-bn(x)*C,C,1,y-a[x]),
				tr3.update(1,0,bn(n),bn(x)-1,tr1[bn(x)-1].s[1].ans);
			if(bn(x)<bn(n))
				tr1[bn(x)].add(1,1,C,1,x-bn(x)*C,0,y-a[x]),
				tr3.update(1,0,bn(n),bn(x),tr1[bn(x)].s[1].ans);
			a[x]=y;
			continue;	
		}
		ll ans=0;
		int l,r; read(l,r);
		int x=l-bn(l)*C,y=C;
		int u=1,v=r-bn(r)*C;
		if(bn(l)+1<bn(r)) {
			if(bn(l)+2<bn(r)) ans=max(ans,tr3.query(1,0,bn(n),bn(l)+1,bn(r)-2));
			ans=max(ans,tr4.query(1,0,bn(n),bn(l)+1,bn(r)-1));
			ans=max(ans,tr2[bn(l)].query(1,1,C,x,y).ans);
			ans=max(ans,tr2[bn(r)].query(1,1,C,u,v).ans);
			arr1 L=tr1[bn(l)].query(1,1,C,x,y);
			arr1 R=tr1[bn(r)-1].query(1,1,C,u,v);
			if(x!=1) ans=max(ans,tr1[bn(l)].query(1,1,C,1,x-1).maxb+L.maxa);
			if(v!=C) ans=max(ans,R.maxb+tr1[bn(r)-1].query(1,1,C,v+1,C).maxa);
			ans=max(ans,max(L.ans,R.ans));
		}
		else if(bn(l)==bn(r)) {
			ans=tr2[bn(l)].query(1,1,C,x,v).ans;
		}
		else {
			ans=max(ans,tr2[bn(l)].query(1,1,C,x,y).ans);
			ans=max(ans,tr2[bn(r)].query(1,1,C,u,v).ans);
			arr1 L=tr1[bn(l)].query(1,1,C,x,y),R=tr1[bn(l)].query(1,1,C,u,v);
			if(v<x) ans=max(ans,R.maxb+L.maxa);
			else {
				if(u<x) ans=max(ans,tr1[bn(l)].query(1,1,C,u,x-1).maxb+L.maxa);
				if(v<y) ans=max(ans,R.maxb+tr1[bn(l)].query(1,1,C,v+1,y).maxa);
				ans=max(ans,tr1[bn(l)].query(1,1,C,x,v).ans);
			}
		}
		write(max(0ll,ans),'\n');
	}
	return 0;
}
```

---

