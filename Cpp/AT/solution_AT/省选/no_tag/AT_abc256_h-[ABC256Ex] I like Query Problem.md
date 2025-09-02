# [ABC256Ex] I like Query Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc256/tasks/abc256_h

$ N,\ Q $ および $ A\ =\ (a_1,\ a_2,\ \dots,\ a_N) $ が与えられます。  
 以下で説明されるクエリを $ Q $ 個処理してください。クエリは次の $ 3 $ 種類のいずれかです。

- `1 L R x` : $ i=L,L+1,\dots,R $ について $ a_i $ の値を $ \displaystyle\ \left\lfloor\ \frac{a_i}{x}\ \right\rfloor $ に更新する。
- `2 L R y` : $ i=L,L+1,\dots,R $ について $ a_i $ の値を $ y $ に更新する。
- `3 L R` : $ \displaystyle\sum_{i=L}^R\ a_i $ を出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ L\ \leq\ R\ \leq\ N $
- $ 1\ \leq\ a_i\ \leq\ 10^5 $
- $ 2\ \leq\ x\ \leq\ 10^5 $
- $ 1\ \leq\ y\ \leq\ 10^5 $
- 入力される値はすべて整数

### Sample Explanation 1

はじめ、$ A\ =\ (2,\ 5,\ 6) $ です。よって $ 1 $ 番目のクエリの答えは $ a_1\ +\ a_2\ +\ a_3\ =\ 2\ +\ 5\ +\ 6\ =\ 13 $ になります。 $ 2 $ 番目のクエリを処理した直後は $ A\ =\ (2,\ 2,\ 3) $ です。よって $ 3 $ 番目のクエリの答えは $ a_1\ +\ a_2\ =\ 2\ +\ 2\ =\ 4 $ になります。 $ 4 $ 番目のクエリを処理した直後は $ A\ =\ (3,\ 3,\ 3) $ です。よって $ 5 $ 番目のクエリの答えは $ a_1\ +\ a_2\ +\ a_3\ =\ 3\ +\ 3\ +\ 3\ =\ 9 $ になります。

## 样例 #1

### 输入

```
3 5
2 5 6
3 1 3
1 2 3 2
3 1 2
2 1 2 3
3 1 3```

### 输出

```
13
4
9```

## 样例 #2

### 输入

```
6 11
10 3 5 20 6 7
3 1 6
1 2 4 3
3 1 3
2 1 4 10
3 3 6
1 3 6 2
2 1 4 5
3 1 6
2 1 3 100
1 2 5 6
3 1 4```

### 输出

```
51
12
33
26
132```

# 题解

## 作者：cjZYZtcl (赞：6)

看题解区都是势能线段树，来一发不一样的题解。

### 前置芝士
分块、珂朵莉树

### 思路
第一眼看到这题，想到的很显然是珂朵莉树，但这题珂朵莉树过不去……

所以考虑一些科技。

不妨先对序列分块，每个块建珂朵莉树。

对于操作一，不难发现对于序列中的一个元素，在没有区间推平操作的情况下，至多 $\log{w}$ 次就会变成 $0$。

而对于操作二，可以发现一次推平至多使 $2$ 个区间的元素种类加一，而整个块被推平的情况下，操作一的复杂度是 $O(1)$ 或 $O(\log{n})$ 的（看实现），所以操作一总复杂度为 $O((n + q) \log{w} + \tfrac{(n+q)n \log{w}}{B})$（可能不太严谨，感性理解一下 qwq ）。

再考虑查询，我们可以在操作一和二的时候同时维护块内和，查询时对于整块查询的直接返回块内和即可。

总复杂度大概是 $O(\tfrac{(n+q)n \log{w}}{B})$ （省略了一些复杂度较低的操作）。

### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pr pair<int, int>
#define mp make_pair
#define pb push_back
#define mid (l + r) / 2
#define fi first
#define se second
const int len = 300;

struct node {
	int l, r;
	mutable int v;
	
	node(int l, int r = 0, int v = 0) : l(l), r(r), v(v){}
	
	bool operator < (const node &a) const{
		return l < a.l;
	}
};

struct Block {
	int l, r, ans;
	set<node> s;
	
	set<node> :: iterator split(int pos) {
		auto it = s.lower_bound(node(pos));
		
		if (it != s.end() && it -> l == pos) {
			return it;
		}
		
		it--;
		if (it -> r < pos) return s.end();
		
		int l = it -> l;
		int r = it -> r;
		int v = it -> v;
		
		s.erase(it);
		s.insert(node(l, pos - 1, v));
		
		return s.insert(node(pos, r, v)).first;
	}
	
	void assign(int l, int r, int x) {
		auto itr = split(r + 1), itl = split(l);
		
		for (auto it = itl; it != itr; it++) {
			ans -= (it -> r - it -> l + 1) * it -> v;
		}
		
		s.erase(itl, itr);
		s.insert(node(l, r, x));
		
		ans += (r - l + 1) * x;
	}
	
	void div(int l, int r, int x) {
		if (ans == 0) return;
		
		auto itr = split(r + 1), itl = split(l);
		
		for (auto it = itl; it != itr; it++) {
			ans -= (it -> r - it -> l + 1) * it -> v;
			
			it -> v /= x;
			
			ans += (it -> r - it -> l + 1) * it -> v;
		}
	}
	
	int query(int l, int r) {
		int now = 0;
		
		auto itr = split(r + 1), itl = split(l);
		
		for (auto it = itl; it != itr; it++) {
			now += (it -> r - it -> l + 1) * it -> v;
		}
		
		return now;
	}
} b[500005];

int a[500005], id[500005];

inline int read(){
	int x = 0, mm = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') mm = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * mm;
}

inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}

signed main(){
	int n = read(), q = read(), k = 0;
	
	for (int i = 1; i <= n; i++) {
		a[i] = read();
	}
	
	for (int l = 1, r = min(n, len); l <= n; l = r + 1, r = min(l + len - 1, n)) {
		b[++k].l = l, b[k].r = r;
		
		for (int i = l; i <= r; i++) {
			id[i] = k;
			b[k].s.insert(node(i, i, a[i]));
			b[k].ans += a[i];
		}
	}
	
	auto assign = [&](int l, int r, int x) -> void {
		int L = id[l], R = id[r];
		
		if (L == R) {
			b[L].assign(l, r, x);
		}
		else {
			b[L].assign(l, b[L].r, x);
			b[R].assign(b[R].l, r, x);
			
			for (int i = L + 1; i < R; i++) {
				b[i].assign(b[i].l, b[i].r, x);
			}
		}
	};
	
	auto div = [&](int l, int r, int x) -> void {
		int L = id[l], R = id[r];
		
		if (L == R) {
			b[L].div(l, r, x);
		}
		else {
			b[L].div(l, b[L].r, x);
			b[R].div(b[R].l, r, x);
			
			for (int i = L + 1; i < R; i++) {
				b[i].div(b[i].l, b[i].r, x);
			}
		}
	};
	
	auto query = [&](int l, int r) -> int {
		int L = id[l], R = id[r];
		
		if (L == R) {
			return b[L].query(l, r);
		}
		else {
			int ans = b[L].query(l, b[L].r) + b[R].query(b[R].l, r);
			
			for (int i = L + 1; i < R; i++) {
				ans += b[i].ans;
			}
			
			return ans;
		}
	};
	
	for (int i = 1; i <= q; i++) {
		int opt = read();
		
		if (opt == 1) {
			int l = read(), r = read(), x = read();
			
			div(l, r, x);
		}
		
		if (opt == 2) {
			int l = read(), r = read(), x = read();
			
			assign(l, r, x);
		}
		
		if (opt == 3) {
			int l = read(), r = read();
			
			write(query(l, r));
			putchar('\n');
		}
	}
}
```

---

## 作者：Register_int (赞：4)

锐评题解全是 ODT，到底有没有树枝啊？

首先势能线段树。考虑整除 $k$ 操作在什么时候可以转化为区间加操作。首先求出该段的最大值 $x$ 与最小值 $y$，如果 $x=y$，那么该段的整除操作就可以直接变为区间加 $\left\lfloor\dfrac xk\right\rfloor-x$。**不能化为区间推平，否则标记会炸。**

没了？没了。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 10;

ll a[MAXN];

struct node {
	int l, r, tag;
	ll sum, maxp, minp, add;
} t[MAXN << 2];

inline 
void align(int p, int val) {
	t[p].sum = (ll)(t[p].r - t[p].l + 1) * val;
	t[p].maxp = val, t[p].minp = val, t[p].tag = val, t[p].add = 0;
}

inline 
void update(int p, int val) {
	t[p].sum += (ll)(t[p].r - t[p].l + 1) * val;
	t[p].maxp += val, t[p].minp += val, t[p].add += val;
}

inline 
void pushup(int p) {
	t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
	t[p].maxp = max(t[p << 1].maxp, t[p << 1 | 1].maxp);
	t[p].minp = min(t[p << 1].minp, t[p << 1 | 1].minp);
}

inline 
void pushdown(int p) {
	if (t[p].tag) {
		align(p << 1, t[p].tag), align(p << 1 | 1, t[p].tag);
		t[p].tag = 0;
	}
	if (t[p].add) {
		update(p << 1, t[p].add), update(p << 1 | 1, t[p].add);
		t[p].add = 0;
	}
}

inline 
void build(int l, int r, int p) {
	t[p].l = l, t[p].r = r;
	if (l == r) return t[p].sum = t[p].maxp = t[p].minp = a[l], void();
	int mid = l + r >> 1;
	build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1);
	pushup(p);
}

inline 
void modify(int l, int r, int val, int p) {
	if (l <= t[p].l && t[p].r <= r) return align(p, val);
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	if (l <= mid) modify(l, r, val, p << 1);
	if (r > mid) modify(l, r, val, p << 1 | 1);
	pushup(p);
}

inline 
void div(int l, int r, int val, int p) {
	if (l <= t[p].l && t[p].r <= r) {
		if (t[p].maxp == t[p].minp) return update(p, t[p].maxp / val - t[p].maxp);
	}
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	if (l <= mid) div(l, r, val, p << 1);
	if (r > mid) div(l, r, val, p << 1 | 1);
	pushup(p);
}

inline 
ll qsum(int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r) return t[p].sum;
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1; ll res = 0;
	if (l <= mid) res += qsum(l, r, p << 1);
	if (r > mid) res += qsum(l, r, p << 1 | 1);
	return res;
}

int n, q;

int opt, l, r, k;

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	build(1, n, 1);
	while (q--) {
		scanf("%d%d%d", &opt, &l, &r);
		if (opt == 1) scanf("%d", &k), div(l, r, k, 1);
		if (opt == 2) scanf("%d", &k), modify(l, r, k, 1);
		if (opt == 3) printf("%lld\n", qsum(l, r, 1));
	}
}
```

---

## 作者：5k_sync_closer (赞：4)

线段树每个点上维护区间最大值、最小值，

区间除以 $x$ 时，由区间对应的每个节点向下递归到 $\max=\min$ 的节点，在这些节点上区间推平。

每个节点被除 $O(\log V)$ 次后 $\max=\min$，所以总复杂度 $O(n\log n\log V)$。

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int n, m;
struct T
{
    int s, x, y, z;
} R[500050 << 2];
void u(int p)
{
    R[p].s = R[p << 1].s + R[p << 1 | 1].s;
    R[p].x = max(R[p << 1].x, R[p << 1 | 1].x);
    R[p].y = min(R[p << 1].y, R[p << 1 | 1].y);
}
void f(int p, int s, int t, int x)
{
    R[p].s = (t - s + 1) * x;
    R[p].x = R[p].y = R[p].z = x;
}
void d(int p, int s, int t)
{
    if (~R[p].z)
    {
        int m = s + t >> 1;
        f(p << 1, s, m, R[p].z);
        f(p << 1 | 1, m + 1, t, R[p].z);
        R[p].z = -1;
    }
}
void B(int s, int t, int p)
{
    R[p].z = -1;
    if (s == t)
        return (void)(scanf("%lld", &R[p].s), R[p].x = R[p].y = R[p].s);
    int m = s + t >> 1;
    B(s, m, p << 1);
    B(m + 1, t, p << 1 | 1);
    u(p);
}
void M1(int l, int r, int x, int s, int t, int p)
{
    if (l <= s && t <= r && R[p].x == R[p].y)
        return f(p, s, t, R[p].x / x);
    d(p, s, t);
    int m = s + t >> 1;
    if (l <= m)
        M1(l, r, x, s, m, p << 1);
    if (r > m)
        M1(l, r, x, m + 1, t, p << 1 | 1);
    u(p);
}
void M2(int l, int r, int x, int s, int t, int p)
{
    if (l <= s && t <= r)
        return f(p, s, t, x);
    d(p, s, t);
    int m = s + t >> 1;
    if (l <= m)
        M2(l, r, x, s, m, p << 1);
    if (r > m)
        M2(l, r, x, m + 1, t, p << 1 | 1);
    u(p);
}
int Q(int l, int r, int s, int t, int p)
{
    if (l <= s && t <= r)
        return R[p].s;
    d(p, s, t);
    int m = s + t >> 1, q = 0;
    if (l <= m)
        q += Q(l, r, s, m, p << 1);
    if (r > m)
        q += Q(l, r, m + 1, t, p << 1 | 1);
    return q;
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    B(1, n, 1);
    for (int i = 0, o, x, y, k; i < m; ++i)
    {
        scanf("%lld%lld%lld", &o, &x, &y);
        switch (o)
        {
        case 1:
            scanf("%lld", &k);
            M1(x, y, k, 1, n, 1);
            break;
        case 2:
            scanf("%lld", &k);
            M2(x, y, k, 1, n, 1);
            break;
        case 3:
            printf("%lld\n", Q(x, y, 1, n, 1));
            break;
        }
    }
    return 0;
}
```


---

## 作者：hzjnsy (赞：4)

**[AT](https://atcoder.jp/contests/abc256/tasks/abc256_h) [洛谷](https://www.luogu.com.cn/problem/AT_abc256_h)**

两只 $\log$ 跑得快，数据结构真可爱！

> - 你要维护一个序列 $a_1\sim a_N$，支持 $3$ 种操作，共 $Q$ 次：
>
>     - $1\texttt{ }L \texttt{ }R\texttt{ }x$，对 $[L,R]$ 内的所有 $i$ 执行 $a_i\leftarrow \left\lfloor\dfrac{a_i}{x}\right\rfloor$。
>
>     - $2\texttt{ }L\texttt{ }R\texttt{ }y$，对 $[L,R]$ 内的所有 $i$ 执行 $a_i\leftarrow y$。
>
>     - $3\texttt{ }L\texttt{ }R$，求 $\sum\limits_{i=L}^R a_i$。
>
> - $N\le 5\times 10^5$，$Q\le 10^5$。设值域为 $V$，$|V|\le 10^5$。

看到区间推平操作，想到颜色段均摊。考虑用珂朵莉树维护颜色段，线段树维护区间和。

$2$ 操作就是同时在珂朵莉树和线段树上推平，$3$ 操作就是在线段树上查询区间和，都是平凡的。重点讲一下 $1$ 操作。

对于颜色相同的一段，它们在 $1$ 操作中会变成相同的值，那就在珂朵莉树遍历这些段，在线段树上将这些段推平成修改后的值。由于题目保证了 $x\ge 2$，所以每个颜色段只会经过 $\log|V|$ 次 $1$ 操作就会变成 $0$。所以这里的珂朵莉树中维护**非 $\boldsymbol{0}$ 的颜色段，这些颜色段拼起来不一定是整个序列**。每次 $1$ 操作后，若当前段值变成 $0$，则删除。

这样导致珂朵莉树的 `split` 操作会发生一些变化。你想象成从一个位置切一刀，可能会将某个颜色段分成两个颜色相同的颜色段（可能不会发生），然后 `split` 操作就是要返回第一个左端点大于当与该位置的颜色段。这样在 `split(L)` 和 `split(R + 1)` 时会得到一个区间 $[ql,qr)$。记 $r$ 为 $qr$ 左边的第一个颜色段，那么得到的区间就是 $[ql,r]$，而 $qr$ 左边的第一个颜色段 $r$ 不就是最后一个右端点小于等于 $R$ 的颜色段吗？那么这样你就可以遍历 $[L,R]$ 之间的所有颜色段了。

接下来算复杂度。一开始有 $N$ 个颜色段，一次操作会带来 $\mathcal{O}(1)$ 个颜色段，一个颜色段被操作 $\mathcal{O}(\log|V|)$ 次就会被删除，一次操作是 $\mathcal{O}(\log N)$ 的。还有 $2$ 操作的推平一次是 $\mathcal{O}(\log N)$，$3$ 操作的询问一次是 $\mathcal{O}(\log N)$。这么算下来，时间复杂度为 $\mathcal{O}((N+Q)\log |V|\cdot \log N)$，空间复杂度为 $\mathcal{O}(N+Q)$。

**[提交记录](https://atcoder.jp/contests/abc256/submissions/45997365)**

```cpp
#include <bits/stdc++.h>
#define int long long
#define Sit set<node>::iterator
using namespace std; const int N = 5e5 + 5; int n, q, a[N];
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
struct SegmentTree {
    #define ls(x) ((x) << 1)
    #define rs(x) (((x) << 1) | 1)
    int sum[N << 2], tag[N << 2];
    void build(int x, int l, int r) {
        tag[x] = -1; if (l == r) return void(sum[x] = a[l]); 
        int mid = (l + r) >> 1; build(ls(x), l, mid); build(rs(x), mid + 1, r);
        sum[x] = sum[ls(x)] + sum[rs(x)];
    }
    void upd(int x, int l, int r, int v) { sum[x] = (r - l + 1) * (tag[x] = v); }
    void down(int x, int l, int r, int mid) {
        if (tag[x] == -1) return; 
        upd(ls(x), l, mid, tag[x]); upd(rs(x), mid + 1, r, tag[x]); tag[x] = -1;
    }
    void assign(int x, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return void(upd(x, l, r, v));
        int mid = (l + r) >> 1; down(x, l, r, mid);
        if (ql <= mid) assign(ls(x), l, mid, ql, qr, v); 
        if (qr > mid) assign(rs(x), mid + 1, r, ql, qr, v); 
        sum[x] = sum[ls(x)] + sum[rs(x)];
    }
    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[x];
        int mid = (l + r) >> 1, ret = 0; down(x, l, r, mid);
        if (ql <= mid) ret = query(ls(x), l, mid, ql, qr);
        if (qr > mid) ret += query(rs(x), mid + 1, r, ql, qr); return ret;
    }
} SGT;
struct node { mutable int l, r, v; }; 
bool operator<(node a, node b) { return a.l < b.l; }
struct OldDriverTree {
    set<node> s; vector<Sit> tmp;
    void build() { for (int i = 1; i <= n; ++i) s.insert({i, i, a[i]}); }
    Sit split(int pos) {
        if (pos > n) return s.end(); Sit i = s.lower_bound({pos, 0, 0});
        if (i != s.end() && i->l == pos || i == s.begin()) return i;
        --i; if (i->r < pos) return ++i; int l = i->l, r = i->r, v = i->v; 
        s.erase(i); s.insert({l, pos - 1, v}); return s.insert({pos, r, v}).first;
    }
    void assign(int l, int r, int v) {
        SGT.assign(1, 1, n, l, r, v); Sit qr = split(r + 1), ql = split(l);
        s.erase(ql, qr); s.insert({l, r, v});
    }
    void modify(int l, int r, int x) {
        Sit qr = split(r + 1), ql = split(l); tmp.clear();
        for (Sit i = ql; i != qr; ++i) {
            i->v /= x; SGT.assign(1, 1, n, i->l, i->r, i->v);
            if (!i->v) tmp.emplace_back(i);
        }
        for (Sit i : tmp) s.erase(i);
    }
} ODT;
signed main() {
    read(n), read(q); for (int i = 1; i <= n; ++i) read(a[i]); 
    SGT.build(1, 1, n); ODT.build();
    for (int op, l, r, x; q--;) {
        read(op), read(l), read(r);
        if (op == 1) read(x), ODT.modify(l, r, x);
        else if (op == 2) read(x), ODT.assign(l, r, x);
        else print(SGT.query(1, 1, n, l, r));
    }
    return 0;
}
```



---

## 作者：CQ_Bob (赞：3)

## 分析

用势能线段树。

对于一段数字 $a_l$ 到 $a_r$，每次全部除以一个大于 $1$ 的数，不难发现最多除以 $\log x$ 次就会使 $a_l$ 到 $a_r$ 全部变成 $0$，其中 $x$ 是区间最大值。

所以，在没有操作 $2$ 的情况下，我们可以在每次操作 $1$ 的时候都单点修改，只要在某个需要修改的区间 $[l,r]$ 的和为 $0$ 时，就不对改区间进行操作。但有了操作 $2$ 之后，数据是可以在每次操作 $1$ 之后都加 $1$ 个操作 $2$。这样的时间复杂度就退化成 $O(nq)$ 了。考虑优化。

我们设区间 $[l,r]$ 的势能函数为 $\mathit{H}(l,r)$。若 $[l,r]$ 中的权值均相同，则 $\mathit{H}(l,r)=1$，否则 $\mathit{H}(l,r)=\mathit{H}(l,mid)+\mathit{H}(mid+1,r)$。

在 $[l',r'](l \le l' \le r' \le r)$ 的权值相同的情况下，我们可以直接将 $[l',r']$ 的值全部赋值成 $\lfloor\frac{v}{x}\rfloor$，这是能做到 $O(1)$ 的。其中 $v$ 是该区间的某一个权值，$x$ 是操作给的值。否则在 $[l',r'](l \le l' \le r' \le r)$ 的权值不相同的情况下，我们就将操作往下推，分成 $[l',mid],[mid+1,r']$。对单次区间除法操作的复杂度 $O(\mathit{H}(l',r'))$。

总的区间除法的复杂度是 $O(n \log n \log x)$ 的。

注意 $1$：看 $[l,r]$ 的权值是否相同，直接看区间最大和最小值是否相等就行。

注意 $2$：区间推平的懒标记初始值是需要赋成 $-1$ 的，因为存在除法操作之后权值下取整为 $0$ 的情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=2e6+10;
int n,q;
struct node{
	int l,r,mi,ma,lz,s;
}tr[N];
int a[N];

il void up(int now){
	tr[now].s=tr[now<<1].s+tr[now<<1|1].s;
	tr[now].ma=max(tr[now<<1].ma,tr[now<<1|1].ma);
	tr[now].mi=min(tr[now<<1].mi,tr[now<<1|1].mi);
	return ;
}
il void down(int now){
	if(tr[now].lz!=-1){
		tr[now<<1].lz=tr[now].lz,tr[now<<1|1].lz=tr[now].lz;
		tr[now<<1].s=(tr[now<<1].r-tr[now<<1].l+1)*tr[now].lz,tr[now<<1|1].s=(tr[now<<1|1].r-tr[now<<1|1].l+1)*tr[now].lz;
		tr[now<<1].ma=tr[now<<1|1].ma=tr[now].ma;
		tr[now<<1|1].mi=tr[now<<1].mi=tr[now].mi;
		tr[now].lz=-1;
	}
	return ;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r,tr[now].lz=-1;
	if(l==r) tr[now].s=tr[now].ma=tr[now].mi=a[l];
	else{
		int mid=l+r>>1;
		build(now<<1,l,mid),build(now<<1|1,mid+1,r);
		up(now);
	}
	return ;
}
il void insert(int now,int l,int r,int x){
	if(tr[now].l>=l&&tr[now].r<=r)
		if(tr[now].ma==tr[now].mi){
			tr[now].ma=tr[now].mi=tr[now].lz=(int)(tr[now].ma/x);
			tr[now].s=(tr[now].r-tr[now].l+1)*tr[now].lz;
			return ;
		}
	down(now);
	int mid=tr[now].l+tr[now].r>>1;	
	if(l<=mid) insert(now<<1,l,r,x);
	if(mid<r) insert(now<<1|1,l,r,x);
	up(now);
	return ;
}
il void insert2(int now,int l,int r,int x){
	if(tr[now].l>=l&&tr[now].r<=r){
		tr[now].ma=tr[now].mi=tr[now].lz=x;
		tr[now].s=(tr[now].r-tr[now].l+1)*tr[now].lz;
	}
	else{
		down(now);
		int mid=tr[now].l+tr[now].r>>1;	
		if(l<=mid) insert2(now<<1,l,r,x);
		if(mid<r) insert2(now<<1|1,l,r,x);
		up(now);
	}
	return ;
}
il int query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now].s;
	int ans=0,mid=tr[now].l+tr[now].r>>1;
	down(now);
	if(l<=mid) ans+=query(now<<1,l,r);
	if(mid<r) ans+=query(now<<1|1,l,r);
	up(now);
	return ans;
}

il void solve(){
	cin>>n>>q;
	for(re int i=1;i<=n;++i) cin>>a[i];
	build(1,1,n);
	for(re int i=1,op,l,r,x,y;i<=q;++i){
		cin>>op;
		if(op==1)
			cin>>l>>r>>x,
			insert(1,l,r,x);
		else if(op==2)
			cin>>l>>r>>y,
			insert2(1,l,r,y);
		else
			cin>>l>>r,
			cout<<query(1,l,r)<<"\n";
	}
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：AlicX (赞：2)

势能线段树板题。

拿到题第一眼小清新线段树，显然对于数 $x$ 而言，最多只需要用 $\log x$ 次除法便可将 $x$ 变成 $1$。但是此题还需要区间推平操作，所以考虑势能线段树。

发现一个显然的性质：当一个区间里的数相同时，除法的时间是 $O(1)$ 的。而区间推平有一个很妙的性质可以与之结合，就是区间推平后区间里的数就相同了，所以可以 $O(1)$ 改了，那么整个区间就被分为了 $\log$ 块。

总结：维护区间是否相同，然后直接暴力除，时间复杂度 $O(n\operatorname{log}n\operatorname{log}V)$（$V$ 是值域）。

关键代码：

```cpp
il void modify2(int u,int l,int r,int w){ 
	if(l<=tr[u].l&&tr[u].r<=r){ 
		if(tr[u].Min==tr[u].Max){ 
			tr[u].add=tr[u].Min/w; 
			tr[u].Min/=w,tr[u].Max/=w; 
			tr[u].w=(tr[u].r-tr[u].l+1)*tr[u].add;  
			return ;  
		} 
	} pushdown(u); int mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) modify2(u<<1,l,r,w); 
	if(r>mid) modify2(u<<1|1,l,r,w); 
	pushup(u); 
} 
```


---

## 作者：wjr_jok (赞：2)

可以纯分块。

直接分块肯定会炸，所以套用一点势能线段树的思想，在块内所有值相等时把它当成一个点来维护，对应代码中的 $tp$ 数组。

对于操作 $1$，散块直接修改，然后遍历这个块，修改 $tp$ 的状态（是否均为同一值）。整块 $tp$ 若不为 $-1$（所赋初始值）就直接修改 $tp$，否则就暴力遍历整块，然后更新 $tp$（只需看块内最小值是否等于最大值）。

对于操作 $2$，散块仍然只能直接修改，操作不变，而整块可以直接修改 $tp$ 为 $x$（推平的值）。

询问时跟普通分块一样直接统计答案即可。

需要注意的是修改分块由于要保证 $tp$ 的正确性，需要遍历整个块来更新，以及 $tp$ 与原序列 $xl$ 中所存的值的优先级。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+1;
int n,q,opt,l,r,s; 
int xl[N];
int x[N],y[N],fk[N],ans[N],maxx[N],minn[N],tp[N];
signed main(){
	cin>>n>>q;
	int cnt=sqrt(n);
	for(int i=1;i<=cnt;i++){
		x[i]=y[i-1]+1;
		y[i]=x[i]+cnt-1;
	}
	if(y[cnt]<n){
		cnt++;
		x[cnt]=y[cnt-1]+1;
		y[cnt]=n;
	}
	for(int i=1;i<=n;i++){
		cin>>xl[i];
	}
	for(int i=1;i<=n;i++){
		tp[i]=-1,minn[i]=INT_MAX;
		for(int j=x[i];j<=y[i];j++){
			fk[j]=i;
			ans[i]+=xl[j];
			maxx[i]=max(maxx[i],xl[j]);
			minn[i]=min(minn[i],xl[j]);
		}
	}
	for(int i=1;i<=q;i++){
		cin>>opt>>l>>r;
		if(opt==1){
			cin>>s;
			if(tp[fk[l]]){
				if(tp[fk[l]]!=-1){
					for(int j=x[fk[l]];j<=y[fk[l]];j++){
						xl[j]=tp[fk[l]];
					}
				}
				for(int j=l;j<=min(r,y[fk[l]]);j++){
					ans[fk[l]]-=xl[j];
					xl[j]/=s;
					ans[fk[l]]+=xl[j];
				}
				maxx[fk[l]]=0,minn[fk[l]]=INT_MAX;
				for(int j=x[fk[l]];j<=y[fk[l]];j++){
					maxx[fk[l]]=max(maxx[fk[l]],xl[j]);
					minn[fk[l]]=min(minn[fk[l]],xl[j]);
				}
				if(maxx[fk[l]]==minn[fk[l]]){
					tp[fk[l]]=xl[l];
				}
				else{
					tp[fk[l]]=-1;
				}
			}
			if(fk[l]!=fk[r]){
				if(tp[fk[r]]){
					if(tp[fk[r]]!=-1){
						for(int j=x[fk[r]];j<=y[fk[r]];j++){
							xl[j]=tp[fk[r]];
						}
					}
					for(int j=x[fk[r]];j<=r;j++){
						ans[fk[r]]-=xl[j];
						xl[j]/=s;
						ans[fk[r]]+=xl[j];
					}
					maxx[fk[r]]=0,minn[fk[r]]=INT_MAX;
					for(int j=x[fk[r]];j<=y[fk[r]];j++){
						maxx[fk[r]]=max(maxx[fk[r]],xl[j]);
						minn[fk[r]]=min(minn[fk[r]],xl[j]);
					}
					if(maxx[fk[r]]==minn[fk[r]]){
						tp[fk[r]]=xl[r];
					}
					else{
						tp[fk[r]]=-1;
					}
				}
			}
			for(int j=fk[l]+1;j<fk[r];j++){
				maxx[j]/=s;
				minn[j]/=s;
				if(tp[j]!=-1){
					if(tp[j]){
						tp[j]/=s;
						ans[j]=(y[j]-x[j]+1)*tp[j];
					}
				}
				else{
					if(maxx[j]==minn[j]){
						tp[j]=maxx[j];
						ans[j]=(y[j]-x[j]+1)*tp[j];
					}
					else{
						for(int k=x[j];k<=y[j];k++){
							ans[j]-=xl[k];
							xl[k]/=s;
							ans[j]+=xl[k];
						}
					}
				}
			}
		}
		if(opt==2){
			cin>>s;
			if(tp[fk[l]]!=-1){
				for(int j=x[fk[l]];j<=y[fk[l]];j++){
					xl[j]=tp[fk[l]];
				}
			}
			for(int j=l;j<=min(r,y[fk[l]]);j++){
				ans[fk[l]]-=xl[j];
				xl[j]=s;
				ans[fk[l]]+=xl[j];
			}
			maxx[fk[l]]=minn[fk[l]]=s;
			for(int j=x[fk[l]];j<=y[fk[l]];j++){
				maxx[fk[l]]=max(maxx[fk[l]],xl[j]);
				minn[fk[l]]=min(minn[fk[l]],xl[j]);
			}
			if(maxx[fk[l]]==minn[fk[l]]){
				tp[fk[l]]=xl[l];
			}
			else{
				tp[fk[l]]=-1;
			}
			if(fk[l]!=fk[r]){
				if(tp[fk[r]]!=-1){
					for(int j=x[fk[r]];j<=y[fk[r]];j++){
						xl[j]=tp[fk[r]];
					}
				}
				for(int j=x[fk[r]];j<=r;j++){
					ans[fk[r]]-=xl[j];
					xl[j]=s;
					ans[fk[r]]+=xl[j];
				}
				maxx[fk[r]]=minn[fk[r]]=s;
				for(int j=x[fk[r]];j<=y[fk[r]];j++){
					maxx[fk[r]]=max(maxx[fk[r]],xl[j]);
					minn[fk[r]]=min(minn[fk[r]],xl[j]);
				}
				if(maxx[fk[r]]==minn[fk[r]]){
					tp[fk[r]]=xl[r];
				}
				else{
					tp[fk[r]]=-1;
				}
			}
			for(int j=fk[l]+1;j<fk[r];j++){
				tp[j]=s;
				ans[j]=(y[j]-x[j]+1)*s;
			}
		}
		if(opt==3){
			int cnt=0;
			for(int j=l;j<=min(r,y[fk[l]]);j++){
				if(tp[fk[l]]!=-1){
					cnt+=tp[fk[l]];
				}
				else{
					cnt+=xl[j];
				}
			}
			if(fk[l]!=fk[r]){
				for(int j=x[fk[r]];j<=r;j++){
					if(tp[fk[r]]!=-1){
						cnt+=tp[fk[r]];
					}
					else{
						cnt+=xl[j];
					}
				}
			}
			for(int j=fk[l]+1;j<fk[r];j++){
				cnt+=ans[j];
			}
			cout<<cnt<<endl;
		}
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：2)

# 思路

首先可以看一下 [P4145](https://www.luogu.com.cn/problem/P4145)，在 P4145 中使用了一种叫势能线段树的 Trick。

对于势能线段树，我个人的理解是，对于一段区间（或一个点）直接暴力维护，在经过很少的次数后操作将没有意义的题就可以使用势能线段树。

在本题中，如果没有推平操作，显然我们可以直接使用势能线段树，时间复杂度可以轻松做到 $\Theta(n \log n)$。

但是拥有了推平操作，我们可以造出 1，2 操作交替进行的数据，将这类普通的势能线段树卡死。

那么，我们需要考虑优化。发现如果有一段区间的值都是相同的，我们就可以轻松的修改出这段区间在修改后的信息。

因此，考虑再维护两个信息 $\max$ 和 $\min$，当 $\max = \min$ 时才修改。那么在极限数据在也能做到 $\Theta(n \log n \log v)$ 的时间复杂度解决。（其中 $v$ 为值域）

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 5e5 + 10;
int n,q;
int arr[N];

struct seg{
	#define ls(u) (u << 1)
	#define rs(u) (u << 1 | 1)
	
	struct node{
		int l;
		int r;
		int sum;
		int Max;
		int Min;
		int tag;
	}tr[N << 2];
	
	inline void pushup(int u){
		tr[u].sum = tr[ls(u)].sum + tr[rs(u)].sum;
		tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
		tr[u].Min = min(tr[ls(u)].Min,tr[rs(u)].Min);
	}
	
	inline void pushdown(int u){
		if (~tr[u].tag){
			tr[ls(u)].sum = (tr[ls(u)].r - tr[ls(u)].l + 1) * tr[u].tag;
			tr[ls(u)].Max = tr[u].Max;
			tr[ls(u)].Min = tr[u].Min;
			tr[ls(u)].tag = tr[u].tag;
			tr[rs(u)].sum = (tr[rs(u)].r - tr[rs(u)].l + 1) * tr[u].tag;
			tr[rs(u)].Max = tr[u].Max;
			tr[rs(u)].Min = tr[u].Min;
			tr[rs(u)].tag = tr[u].tag;
			tr[u].tag = -1;
		}
	}
	
	inline void build(int u,int l,int r){
		tr[u] = {l,r};
		tr[u].tag = -1;
		if (l == r){
			tr[u].sum = tr[u].Max = tr[u].Min = arr[l];
			return;
		}
		int mid = l + r >> 1;
		build(ls(u),l,mid);
		build(rs(u),mid + 1,r);
		pushup(u);
	}
	
	inline void modify_div(int u,int l,int r,int k){
		if (l <= tr[u].l && tr[u].r <= r){
			if (tr[u].Max == tr[u].Min){
				tr[u].Max /= k;
				tr[u].Min /= k;
				tr[u].tag = tr[u].Max;
				tr[u].sum = (tr[u].r - tr[u].l + 1) * tr[u].Max;
				return;
			}
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify_div(ls(u),l,r,k);
		if (r > mid) modify_div(rs(u),l,r,k);
		pushup(u);
	}
	
	inline void modify_upd(int u,int l,int r,int k){
		if (l <= tr[u].l && tr[u].r <= r){
			tr[u].sum = (tr[u].r - tr[u].l + 1) * k;
			tr[u].Max = tr[u].Min = k;
			tr[u].tag = k;
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify_upd(ls(u),l,r,k);
		if (r > mid) modify_upd(rs(u),l,r,k);
		pushup(u);
	}
	
	inline int query(int u,int l,int r){
		if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
		pushdown(u);
		int res = 0;
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) res += query(ls(u),l,r);
		if (r > mid) res += query(rs(u),l,r);
		return res;
	}
	
	#undef ls
	#undef rs
}tree;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	q = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	tree.build(1,1,n);
	while (q--){
		int op;
		op = read();
		if (op == 1){
			int l,r,x;
			l = read();
			r = read();
			x = read();
			tree.modify_div(1,l,r,x);
		}
		else if (op == 2){
			int l,r,x;
			l = read();
			r = read();
			x = read();
			tree.modify_upd(1,l,r,x);
		}
		else{
			int l,r;
			l = read();
			r = read();
			printf("%lld\n",tree.query(1,l,r));
		}
	}
	return 0;
}
```

---

## 作者：CuCl4Loliko (赞：1)

### Problem

给你一个序列，你需要支持以下三个操作：

- 区间所有数字除以 $x$ 下取整

- 区间推平

- 查询区间和

### Solution

对于区间推平操作，正常线段树区间推平即可。

对于区间整除操作，每次整除都在线段树上递归到数字全部相同的节点进行整除。

对于询问区间和，正常线段树查询即可。

### Proof

这里给出一种感性的证明。

考虑区间推平操作对整除操作复杂度的影响。将序列视为一个个相同数字的连续段，每次整除操作的复杂度与区间内连续段的数量同阶，而每个连续段被整除 $\log V$ 次以后就不会产生贡献，或者说会与其他连续段合并成一个。每次区间推平操作会将整个区间变为一个连续段，最多只会使连续段增加两个，因此对整除操作的复杂度影响也是 $\log V$ 级别的。

初始给出的序列可以视为一个初始全相同的序列进行了 $n$ 次区间推平操作而来，因此对整除操作的复杂度影响也不会超过 $O(n\log n)$。

不过由于线段树的结构，一个很长的连续段会被拆成 $\log n$ 个区间，但复杂度绝对不会超过 $O(n \log n \log V)$。

### Code
[Code](https://atcoder.jp/contests/abc256/submissions/45934130)

---

## 作者：小木虫 (赞：1)

### Preface  
一道势能线段树板子。  
### Problem  

给定 $ n, q $，和序列 $ a_n $，给定 $ q $ 次操作，有三种：

`1 L R x`：对于 $ [L, R] $ 内的所有 $ i $ 进行 $ a_i \leftarrow \lfloor \dfrac{a_i}{x} \rfloor $。

`2 L R y`：区间推平 $ [L, R] $ 为 $ y $。

`3 L R`：输出 $ \sum_{i = L}^R a_i $。

### Solution  
我们发现如果没有区间修改操作，每个数只会被除 $\log V$ 次。  
但是区间推平导致这个操作会退化。  
但是区间推平拥有很好的性质。  

我们设一个区间 $(L,R)$ 的势能函数 $H(L,R)$ 为：  
对于一个线段树节点区间，若区间内所有数字相同：  
$$H(L,R)=1$$  
否则：  
$$H(L,R)=H(L,mid)+H(mid+1,R)$$  

对于一个非线段树节点区间，其势能函数为按线段树方法分割这个节点分为 $\log n$ 个线段树区间的势能函数之和。

容易发现如果一个区间内所有数字相等，对这个区间进行区间除法是 $O(1)$ 的。  
那么对一个区间进行区间除法就是 $O(H(L,R))$ 的。  

然后你考虑区间推平操作。  
相似地，我们将区间推平按线段树方法分割成 $\log n$ 个线段树节点推平。  
然后你发现一个神奇的事情。  
区间推平操作会使拆开的线段树节点以及它儿子们的的势能函数变为 $1$。  

考虑对于每一个线段树节点，进行有关的推平操作的时候它直接势能降到最低，然后他的父亲节点的势能函数最多 +1，否则对于每一个线段树节点，因为若其势能函数不等于 1 则需要 $\log V$ 次除法使得其变成 1。  
一次除法操作会关于 $O(\log n)$ 个节点，那么总势能分析的复杂度就是 $O(n \log n \log V)$ 的。

换一种方法解释：这个操作可以让拆出的 $\log n$ 个线段树节点所对应的区间缩为一个元素，这个新元素的权值就是需要推平的值，而这个线段树节点下的其它点可以直接作废了（若之后有推平操作还可以在下面插入新点），之后每一次操作的都是这个缩出来的新元素，同时，这 $\log n$ 个节点的父亲也要被更新（可以理解为更换了一个新元素）。  

那么每个元素的被操作次数还是 $\log V$ 的，而元素个数是 $n \log n$ 的。

然后你发现，如果在区间除法的时候对所有数字相等的线段树节点进行操作，复杂度为 $O(n \log n \log V)$：  
```cpp
#include <bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
const int N=5e5+10;
int n,q,l,r,a[N],op,x,y;
vector < pair<int,int> > ins;
int tree[N<<2],minval[N<<2],maxval[N<<2],lazy[N<<2];
void pushup(int rt){
	tree[rt]=tree[rt*2]+tree[rt*2+1];
	minval[rt]=min(minval[rt*2],minval[rt*2+1]);
	maxval[rt]=max(maxval[rt*2],maxval[rt*2+1]);
}
void pushdown(int rt,int left,int right){
	int mid=(left+right)/2;
	if(lazy[rt]!=-1){
		lazy[rt*2]=lazy[rt*2+1]=lazy[rt];
		tree[rt*2]=(mid-left+1)*lazy[rt];
		tree[rt*2+1]=(right-mid)*lazy[rt];
		minval[rt*2]=maxval[rt*2]=minval[rt*2+1]=maxval[rt*2+1]=lazy[rt];
		lazy[rt]=-1;
	}
}
void build(int rt,int left,int right){
	if(left==right){
		minval[rt]=a[left];
		maxval[rt]=a[left];
		tree[rt]=a[left];
		return;
	}int mid=(left+right)/2;
	build(rt*2,left,mid);
	build(rt*2+1,mid+1,right);
	pushup(rt);
}
void update(int rt,int left,int right,int L,int R,int x){
	if(left<right)pushdown(rt,left,right);
	if(left>=L&&right<=R){
		lazy[rt]=x;tree[rt]=(right-left+1)*x;
		minval[rt]=maxval[rt]=x;return;
	}int mid=(left+right)/2;
	if(L<=mid)update(rt*2,left,mid,L,R,x);
	if(mid+1<=R)update(rt*2+1,mid+1,right,L,R,x);
	pushup(rt);
}
void insert(int rt,int left,int right,int L,int R,int x){
	if(left<right)pushdown(rt,left,right);
	int mid=(left+right)/2;
	//cout<<left<<" "<<right<<"\n";
	if(left>=L&&right<=R){
		if(minval[rt]==maxval[rt]){
			//cout<<"OK\n";
			lazy[rt]=maxval[rt]/x;
			tree[rt]=(right-left+1)*lazy[rt];
			minval[rt]/=x,maxval[rt]/=x;
			return;
		}else{
			insert(rt*2,left,mid,L,R,x);
			insert(rt*2+1,mid+1,right,L,R,x);
		}
	}else{
		if(L<=mid)insert(rt*2,left,mid,L,R,x);
		if(mid+1<=R)insert(rt*2+1,mid+1,right,L,R,x);
	}pushup(rt);
}
int query(int rt,int left,int right,int L,int R){
	if(left<right)pushdown(rt,left,right);
	if(left>=L&&right<=R)return tree[rt];
	int mid=(left+right)/2,res=0;
	if(L<=mid)res+=query(rt*2,left,mid,L,R);
	if(mid+1<=R)res+=query(rt*2+1,mid+1,right,L,R);
	return res;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(lazy,-1,sizeof(lazy));
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	build(1,1,n);
	while(q--){
		cin>>op;
		if(op==1){
			cin>>l>>r>>x;
			insert(1,1,n,l,r,x);
		}else if(op==2){
			cin>>l>>r>>y;
			update(1,1,n,l,r,y);
		}else{
			cin>>l>>r;
			cout<<query(1,1,n,l,r)<<"\n";
		}
	}
	return 0;
}
```


---

## 作者：0x3F (赞：0)

Chtholly 树模板题，我们把每一个颜色段 $(l,r,v)$ 存入一个 `set` 中。

首先这个区间求和很容易破坏我们的均摊性质，因此我们可以另开一个线段树（我写的树状数组），在每一次添加或删除颜色段时进行修改，这样添加或删除一个颜色段的复杂度仍为 $\mathcal{O}(\log n)$。

然后考虑前两种操作，只需要将相关的颜色段取出来，进行对应的修改，**将相同的颜色重新合并**，再放回去就可以了。

为什么这样是对的？

我们记总势能为所有颜色段的 $\log(v+1)$ 之和，初始时不超过 $\mathcal{O}(n\log V)$，而每次修改时，假设涉及到了 $k$ 个颜色段，由于相邻颜色段 $v$ 值不同，其中 $v$ 非零的颜色段至少有 $\frac{k-1}{2}$ 个。势能变化如下：

1. 对于操作一：这些非零的颜色段 $v$ 值至少除以 $2$，每一个颜色段对应的势能至少减少 $\Omega(1)$，总势能至少减少 $\Omega(k)$。

2. 对于操作二：这些非零的颜色段合并成一个，每一个颜色段对应的势能至少减少 $\Omega(1)$，总势能至少减少 $\Omega(k)$。

同时，由于颜色段的分裂，新增了 $\mathcal{O}(1)$ 个颜色段，每一个势能增加 $\mathcal{O}(\log V)$，总势能至多增加 $\mathcal{O}(\log V)$。

而进行上述操作所需的时间为 $\mathcal{O}(k\log n)$。

我们考虑：

+ 势能的增加：初始时有 $\mathcal{O}(n\log V)$，每次操作增加 $\mathcal{O}(\log V)$，总共为 $\mathcal{O}((n+q)\log V)$。

+ 势能的减少：每减少 $\Omega{(k)}$ 的势能，需要花费 $\mathcal{O}(k\log n)$ 的时间，相当于每 $1$ 单位的势能对应 $\mathcal{O}(\log n)$ 的时间。

综上，时间复杂度为 $\mathcal{O}((n+q)\log n\log V)$。

~~常数不小，跑了 3s~~

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 5e5 + 10;
int n, q;
struct fenwick_tree {
    long long arr[_];
    #define y ((x)&(-(x)))
    inline void add(int x, long long k) {
        while (x <= n) {
            arr[x] += k;
            x += y;
        }
    }
    inline long long sum(int x) {
        long long ans = 0LL;
        while (x) {
            ans += arr[x];
            (x ^= y);
        }
        return ans;
    }
    #undef y
} A, B;
struct node {
    int l, r, v;
    inline bool operator < (const node rhs) const {
        return r < rhs.r;
    }
};
set<node> S;
inline void ins(node N) {
    S.insert(N);
    int l = N.l;
    int r = N.r;
    int v = N.v;
    A.add(l, v);
    A.add(r + 1, -v);
    B.add(l, (long long) l * v);
    B.add(r + 1, -(long long) (r + 1) * v);
}
inline void del(node N) {
    S.erase(N);
    int l = N.l;
    int r = N.r;
    int v = N.v;
    A.add(l, -v);
    A.add(r + 1, v);
    B.add(l, -(long long) l * v);
    B.add(r + 1, (long long) (r + 1) * v);
}
int m;
node inv[_];
inline void split(int l, int r) {
    auto it = S.lower_bound((node){0, l, 0});
    auto jt = S.lower_bound((node){0, r, 0});
    m = 0;
    for (auto tmp = it; tmp != jt; tmp++) {
        inv[++m] = (*tmp);
    }
    inv[++m] = (*jt);
    for (int i = 1; i <= m; i++) {
        del(inv[i]);
    }
    if (inv[1].l != l) {
        m++;
        for (int i = m; i >= 3; i--) {
            inv[i] = inv[i-1];
        }
        inv[2].l = l;
        inv[2].r = inv[1].r;
        inv[2].v = inv[1].v;
        inv[1].r = l - 1;
    }
    if (inv[m].r != r) {
        m++;
        inv[m].l = r + 1;
        inv[m].r = inv[m-1].r;
        inv[m].v = inv[m-1].v;
        inv[m-1].r = r;
    }
}
inline void calcdivi(int l, int r, int v) {
    for (int i = 1; i <= m; i++) {
        if (inv[i].l >= l && inv[i].r <= r) {
            inv[i].v /= v;
        }
    }
}
inline void calcover(int l, int r, int v) {
    for (int i = 1; i <= m; i++) {
        if (inv[i].l >= l && inv[i].r <= r) {
            inv[i].v = v;
        }
    }
}
inline void merge(void) {
    int t = 1;
    for (int i = 2; i <= m; i++) {
        if (inv[i].v != inv[t].v) {
            inv[++t] = inv[i];
        } else {
            inv[t].r = inv[i].r;
        }
    }
    for (int i = 1; i <= t; i++) {
        ins(inv[i]);
    }
}
inline void divi(int l, int r, int v) {
    split(l, r);
    calcdivi(l, r, v);
    merge();
}
inline void cover(int l, int r, int v) {
    split(l, r);
    calcover(l, r, v);
    merge();
}
inline long long sum(int l, int r) {
    return (r + 1) * A.sum(r) - B.sum(r) - l * A.sum(l - 1) + B.sum(l - 1);
}
int main() {
    cin >> n >> q;
    m = n;
    for (int i = 1; i <= n; i++) {
        cin >> inv[i].v;
        inv[i].l = inv[i].r = i;
    }
    merge();
    while (q--) {
        int o;
        cin >> o;
        switch (o) {
            case 1: {
                int l, r, v;
                cin >> l >> r >> v;
                divi(l, r, v);
                break;
            }
            case 2: {
                int l, r, v;
                cin >> l >> r >> v;
                cover(l, r, v);
                break;
            }
            case 3: {
                int l, r;
                cin >> l >> r;
                cout << sum(l, r) << endl;
                break;
            }
        }
    }
}
```

---

## 作者：MrcFrst (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc256_h)

### 题意

区间整除，区间推平，查询区间和。



------------
大家好啊，我喜欢暴力乱搞，所以这题我用暴力乱搞 AC 了。

首先观察到操作 $1$ 的性质：首先保证了除数至少为 $2$（不然是 $1$ 或者 $0$ 的话就没有意义了），所以对一个数不断进行操作的话，每次数的大小至少会减少一半，减小到 $0$ 之后就不用操作了，因为再操作也就没有意义了，所以最多进行的次数是 $\log_x$ 级别，其中 $x$ 是原先的数值。所以我们用线段树维护区间和的同时再维护一个区间最大值，每次只要当前区间的最大值不为 $0$ 就进去暴力修改，时间复杂度为 $O(n\log n)$。

但是有个问题是，如果加上区间推平操作之后，我们每次推平之后就不能维持原来的最大值了，这样最坏复杂度就又会退化成纯暴力的复杂度。

但是区间推平这个操作我们还可以用另一个东西去维护啊，没错就是 $ODT$！

但是如果区间推平操作很少的话，$ODT$ 的用时表现就会变得很差。

所以我们直接合在一起~~乱搞~~啊！

将全部操作存下来，同时给区间推平操作计数，如果次数大于 $2000$ 就用 $ODT$，否则就用线段树。

然后你就会发现这东西跑得飞快（。



------------


[评测记录](https://atcoder.jp/contests/abc256/submissions/46004120)

$\text{Code:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
const int N=500500;
int n,m,a[N],cnt;
struct query{
    int op,l,r,x;
}q[N];
il int read(){
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
struct Chtholly{
    int l,r;
    mutable int val;
    Chtholly(int l,int r=0,int val=0):l(l),r(r),val(val){}
    bool operator<(const Chtholly &a)const{
        return l<a.l;
    }
};
set<Chtholly>s;
#define It set<Chtholly>::iterator
il It Split(int pos){
    It fnd=s.lower_bound(Chtholly(pos));
    if(fnd!=s.end()&&fnd->l==pos)return fnd;
    fnd--;
    if(fnd->r<pos)return s.end();
    int l=fnd->l,r=fnd->r,val=fnd->val;
    s.erase(fnd);
    s.insert(Chtholly(l,pos-1,val));
    return s.insert(Chtholly(pos,r,val)).first;
}
il void Assign(int l,int r,int x){
    It R=Split(r+1),L=Split(l);
    s.erase(L,R);
    s.insert(Chtholly(l,r,x));
}
il void update(int l,int r,int x){
    It R=Split(r+1),L=Split(l);
    for(re It i=L;i!=R;i++)i->val/=x;
}
il void solve(int l,int r){
    int res=0;
    It R=Split(r+1),L=Split(l);
    for(re It i=L;i!=R;i++)
        res+=(i->r-i->l+1)*i->val;
    printf("%lld\n",res);
}
struct SegmentTree{
    int sum,mx,tag;
}L[N<<2];
#define ls (id<<1)
#define rs (id<<1|1)
il void pushup(SegmentTree &fa,SegmentTree lson,SegmentTree rson){
    fa.sum=lson.sum+rson.sum;
    fa.mx=max(lson.mx,rson.mx);
}
il void pushdown(SegmentTree &fa,SegmentTree &lson,SegmentTree &rson,int l,int r){
    if(!fa.tag)return;
    int mid=(l+r)>>1,t=fa.tag;
    lson={(mid-l+1)*t,t,t};
    rson={(r-mid)*t,t,t};
    fa.tag=0;
}
il void upd(int id,int l,int r,int x,int y,int z){
    if(!L[id].mx)return;
    if(l==r){
        L[id].sum/=z,L[id].mx/=z;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(L[id],L[ls],L[rs],l,r);
    if(x<=mid)upd(ls,l,mid,x,y,z);
    if(y>mid)upd(rs,mid+1,r,x,y,z);
    pushup(L[id],L[ls],L[rs]);
}
il void Ass(int id,int l,int r,int x,int y,int z){
    if(l>=x&&r<=y){
        L[id]={(r-l+1)*z,z,z};
        return;
    }
    int mid=(l+r)>>1;
    pushdown(L[id],L[ls],L[rs],l,r);
    if(x<=mid)Ass(ls,l,mid,x,y,z);
    if(y>mid)Ass(rs,mid+1,r,x,y,z);
    pushup(L[id],L[ls],L[rs]);
}
il int GetSum(int id,int l,int r,int x,int y){
    if(l>=x&&r<=y)return L[id].sum;
    int mid=(l+r)>>1,res=0;
    pushdown(L[id],L[ls],L[rs],l,r);
    if(x<=mid)res+=GetSum(ls,l,mid,x,y);
    if(y>mid)res+=GetSum(rs,mid+1,r,x,y);
    pushup(L[id],L[ls],L[rs]);
    return res;
}
il void build(int id,int l,int r){
    if(l==r){
        L[id]={a[l],a[l],0};
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    pushup(L[id],L[ls],L[rs]);
}
il void solve_odt(){
    for(re int i=1;i<=n;i++)
        s.insert(Chtholly(i,i,a[i]));
    for(re int i=1;i<=m;i++){
        if(q[i].op==1)update(q[i].l,q[i].r,q[i].x);
        if(q[i].op==2)Assign(q[i].l,q[i].r,q[i].x);
        if(q[i].op==3)solve(q[i].l,q[i].r);
    }
}
il void solveSegmentTree(){
    build(1,1,n);
    for(re int i=1;i<=m;i++){
        int op=q[i].op,l=q[i].l,r=q[i].r,x=q[i].x;
        if(op==1)upd(1,1,n,l,r,x);
        if(op==2)Ass(1,1,n,l,r,x);
        if(op==3)printf("%lld\n",GetSum(1,1,n,l,r));
    }
}
signed main(){
    n=read(),m=read();
    for(re int i=1;i<=n;i++)a[i]=read();
    for(re int i=1;i<=m;i++){
        q[i].op=read(),q[i].l=read(),q[i].r=read();
        if(q[i].op!=3)q[i].x=read();
        if(q[i].op==2)cnt++;
    }
    if(cnt>2000)solve_odt();
    else solveSegmentTree();
    return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [[ABC256Ex] I like Query Problem](https://www.luogu.com.cn/problem/AT_abc256_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC256Ex)

## 题面

给定 $ n, q $，和序列 $ a_n $，给定 $ q $ 次操作，有三种：

`1 L R x`：对于 $ [L, R] $ 内的所有 $ i $ 进行 $ a_i \leftarrow \lfloor \dfrac{a_i}{x} \rfloor $。

`2 L R y`：区间推平 $ [L, R] $ 为 $ y $。

`3 L R`：输出 $ \sum_{i = L}^R a_i $。

## Solution

显然势能线段树，好像不是很难写。大概就是在一般的线段树基础上维护一个区间数是否均相同的标记，然后区间整除的时候直接通过这个实现 lazytag，这个复杂度经过一系列分析总之最后就是 $ O(n \log^2 n) $，实现起来很容易，代码也很短，不过，**这太不优雅了**！

有区间推平操作，不难想到 ODT，显然会被卡，于是想到一种优化：

考虑这个的时候首先要知道一点语法知识，即对于 `set` 它是不同于一般的线性结构如 `basic_string` 的，一般的线性结构当插入删除时若改变 `capacity ` 的话指针就会失效，但当在 `set` 中插入或删除元素的时候，对于**非被删数元素**的迭代器、指针和引用等都是**不会失效**的，用 cppreference 的话来说就是：

> No iterators or references are invalidated.

众所周知，我们一般通过对变量的 `mutable` 修饰以使其可以在 `set` 中被修改，且按照 `l` 排序，所以这里我们可以将 `r` 也修饰为 `mutable`，这样的话我们便可以很方便的 $ O(1) $ 延申区间而不损失重构所需的 $ O(\log) $，此时考虑，因为我们的 $ 1 $ 操作中 $ x \ge 2 $，所以显然对于一个数如果不推平为其它数的时候最多 $ \log $ 次就会变为 $ 0 $，所以我们在维护 $ 1 $ 操作时是可以同时将所有已经为 $ 0 $ 的数合并，这样可以有效减少块数，此时似乎对于 $ 1 $ 和 $ 2 $ 操作复杂度就已经正确了，不过如果我在每 $ \log $ 次之后就重新推平满，这样复杂度似乎大概可能会被卡？？不是很确定。

然后这样交上去会获得 $ 28 / 30 $ 的好成绩，不过依然会 T，也不难想到，我们直接拉满查询这个东西就退化成 $ O(nq) $ 的了。对于这个我最初的思路是，每当修改后再遇到一个 $ 3 $ 操作就**重新建立一棵线段树维护所有数的值**，这样在这次查询接着的所有查询就都是 $ O(\log n) $ 的了，这样应该可以有效的水过一些构造的数据，当然卡的方法也很简单，只要在每次查询之间增加一次微小扰动的修改，但是这样每次都会重新建整棵树，最后复杂度还会退化为 $ \dfrac{1}{2} $ 常数的 $ O(nq) $。**但是**，经过下载数据点发现，T 掉的两个数据并没有如此设计，而是完全询问拉满，也就是说理论上这样实现之后是可以通过这道题的，估计出题人也没想到这种奇怪的做法。。。

但是我们可以尝试扩展这种做法，不难想到刚才说的做法复杂度主要浪费在了修改时只修改了一部分，而不需要整棵树重建，所以我们可以尝试在这里优化一下。不难想到，对于一般的线段树，其是支持除了 $ 1 $ 操作外所有操作的快速实现的，而 ODT 又可以将区间整除转化为区间推平，于是我们便不难想到，同时维护一棵 ODT 和一棵线段树，对于 $ 1 $ 操作在 ODT 上通过刚才说的优化转换为若干个区间推平，然后将推平作用到线段树上，对于 $ 2 $ 操作则 ODT 和线段树同时进行，对于 $ 3 $ 的查询直接在线段树上跑即可。这个的复杂度我没太想出来，不过翻了一下题解区，发现一篇 Blog [[ABC256Ex] I like Query Problem 题解](https://www.luogu.com.cn/blog/EastPorridge/solution-ABC256Ex) 和我的做法几乎相同，唯一的区别就是其在 ODT 维护区间整除的时候是直接重构的 ODT。总体来讲这两种维护方式差别是不大的，无非就是一只小 $ \log $ 的区别，大佬的 Blog 最后分析的复杂度为 $ O(n \log^2 n) $，所以我的这个可能也是这个复杂度？？总之表现还不错，最终 $ 1.6\texttt{s} $ 跑完。

## 写在后面

这个奇怪的做法虽然能过，不过还是不推荐写，毕竟实现起来比较复杂细节较多，如果写的话似乎直接写重构部分 ODT 的方法会更好实现一些。一般的线段树写法实现大概也就 $ 60 $ 行，然后这个东西我实现大概写了将近两百行。。。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, Q;
int A[510000];

struct Node{
    int l;
    mutable int r;
    mutable ll val;
    friend const bool operator < (const Node &a, const Node &b){
        return a.l < b.l;
    }
};

class SegTree{
private:
public:
    ll tr[510000 << 2];
    ll lz[510000 << 2];
    #define LS (p << 1)
    #define RS (LS | 1)
    #define MID ((gl + gr) >> 1)
    #define SIZ(l, r) ((r) - (l) + 1)
public:
    SegTree(void){memset(lz, -1, sizeof lz);}
    void Pushup(int p){tr[p] = tr[LS] + tr[RS];}
    void Pushdown(int p, int gl, int gr){
        if(!~lz[p])return;
        lz[LS] = lz[RS] = lz[p];
        tr[LS] = SIZ(gl, MID) * lz[p];
        tr[RS] = SIZ(MID + 1, gr) * lz[p];
        lz[p] = -1;
    }
    void Build(int p = 1, int gl = 1, int gr = N){
        if(gl == gr)return tr[p] = A[gl = gr], void();
        Build(LS, gl, MID), Build(RS, MID + 1, gr);
        Pushup(p);
    }
    void Assign(int l, int r, ll v, int p = 1, int gl = 1, int gr = N){
        // printf("Assign ST : l = %d, r = %d, v = %lld, gl = %d, gr = %d, p = %d\n", l, r, v, gl, gr, p);
        if(l <= gl && gr <= r)return tr[p] = SIZ(gl, gr) * v, lz[p] = v, void();
        Pushdown(p, gl, gr);
        if(l <= MID)Assign(l, r, v, LS, gl, MID);
        if(MID + 1 <= r)Assign(l, r, v, RS, MID + 1, gr);
        Pushup(p);
    }
    ll Query(int l, int r, int p = 1, int gl = 1, int gr = N){
        if(l <= gl && gr <= r)return tr[p];
        if(r < gl || l > gr)return 0;
        Pushdown(p, gl, gr);
        return Query(l, r, LS, gl, MID) + Query(l, r, RS, MID + 1, gr);
    }
    void Desc(int siz = 3){
        int len(1);
        int cur(0);
        while(siz--){
            for(int i = 1; i <= len; ++i)printf("%lld%c", tr[++cur], i == len ? '\n' : ' ');
            len <<= 1;
        }
    }
}st;

class ODT{
private:
    set < Node > tr;
public:
    auto Insert(Node p){return tr.insert(p);}
    auto Split(int p){
        auto it = tr.lower_bound(Node{p});
        if(it != tr.end() && it->l == p)return it;
        advance(it, -1);
        if(p > it->r)return tr.end();
        int l = it->l, r = it->r;
        ll val = it->val;
        tr.erase(it);
        Insert(Node{l, p - 1, val});
        return Insert(Node{p, r, val}).first;
    }
    void Assign(int l, int r, ll val){
        auto itR = Split(r + 1), itL = Split(l);
        tr.erase(itL, itR);
        Insert(Node{l, r, val});
        st.Assign(l, r, val);
    }
    void Divide(int l, int r, ll x){
        auto itR = Split(r + 1), itL = Split(l);
        for(auto it = itL; it != itR;){
            it->val /= x;
            if(!it->val){
                decltype(it) nxt;
                for(nxt = next(it); nxt != itR; nxt = tr.erase(nxt)){
                    nxt->val /= x;
                    if(!nxt->val)it->r = nxt->r;
                    else{
                        st.Assign(it->l, it->r, it->val);
                        st.Assign(nxt->l, nxt->r, nxt->val);
                        it = next(nxt);
                        break;
                    }
                }
                if(nxt == itR)st.Assign(it->l, it->r, it->val), it = nxt;
            }else
                st.Assign(it->l, it->r, it->val), advance(it, 1);
        }
    }
    ll Query(int l, int r){
        ll ret(0);
        auto itR = Split(r + 1), itL = Split(l);
        for(auto it = itL; it != itR; ++it)
            ret += (it->r - it->l + 1) * it->val;
        return ret;
    }
    void Desc(void){
        printf("Describe ODT:\n");
        for(auto nod : tr)printf("%d ~ %d : %lld\n", nod.l, nod.r, nod.val);
    }
}odt;

int main(){
    // freopen("01_n_small_00.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    N = read(), Q = read();
    for(int i = 1; i <= N; ++i)odt.Insert(Node{i, i, A[i] = read()});
    st.Build();
    while(Q--){
        int opt = read();
        switch(opt){
            case 1:{
                int l = read(), r = read(), x = read();
                odt.Divide(l, r, x);
                break;
            }
            case 2:{
                int l = read(), r = read(), x = read();
                odt.Assign(l, r, x);
                break;
            }
            case 3:{
                int l = read(), r = read();
                printf("%lld\n", st.Query(l, r));
                break;
            }
            default: break;
        }
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_08 初稿

update-2022_12_08 修复一点小锅

---

## 作者：EastPorridge (赞：0)

### 题目概述：

让你写个数据结构，支持区间推平，区间整除，查询区间和。

### 题目分析：

珂朵莉树套线段树，这道题充斥了我对珂朵莉树的所有理解。

看到区间推平，我相信学过珂朵莉树的人已经按捺不住内心想直接写个珂朵莉树胡上去，我也是，但是这是 Ex 题，过不去。

分析原因，很简单，因为块数太散了，每次查询和整除操作的复杂度太傻，一步思考，我们可以通过定期重构的方式，每相隔 $\sqrt q$ 的时间，就用线性的复杂度将 `set` 中权值连续的部分变成极大块，来优化查询和整除操作，但是，还是过不去。

我们每次优化的就是两个要进行块间遍历的操作，所以定期重构可以理解为用近似 $O(n \sqrt q)$ 的复杂度去均摊两个暴力操作的的复杂度。

有啥数据结构也可以降低查询的复杂度呢？线段树。

我们发现线段树很容易支持区间推平和区间和操作，稳定 $O( \log n)$，难在区间整除（其实你如果会，这就是个势能线段树的板子），但珂朵莉树却可以很简单的进行区间整除，结合我们上面的均摊思想，一个新方法诞生了。

每次整除操作和区间推平时，都重构一遍 split 出来的左右端点中间的块，归并成权值相同的极大块，再用线段树进行区间推平，相当于把定期重构换成了遇上修改操作就重构一遍修改操作中间的所有块，再用线段树推平维护一遍，查询就可以直接 $O(\log n)$ 的做。

这玩意是对的，比纯暴力珂朵莉树快 6s 多，下面口胡一下复杂度。

因为每次操作都保证了相同权值极大块，所以每次整除至少是 $\log$ 的，又因为我们外面又套了棵线段树，所以整体近似 $O(n \log^2 n)$ 的，不严格在整除操作，加上 STL 和线段树并用的巨大常数，所以跑的还是比较慢的。

### Code.

```cpp
#include<bits/stdc++.h>
#define int long long
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read()
{
	int x=0; char c=gc(); bool f=0;
	for(;c<'0'||c>'9';c=gc()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=gc()) x=(x<<1)+(x<<3)+(c^48);
	return x=f ? -x : x;
}
using namespace std;
const int N=5e5+10;
int n,q,a[N],tt; struct Seg {int l,r,sum,tag;} tr[N<<2];
inline void pushup(int u) {tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;}
inline void pushdown(int u)
{
	if(tr[u].tag != -1)
	{
		tr[u<<1].sum=tr[u].tag*(tr[u<<1].r - tr[u<<1].l + 1);
		tr[u<<1|1].sum=tr[u].tag*(tr[u<<1|1].r - tr[u<<1|1].l + 1);
		tr[u<<1].tag=tr[u<<1|1].tag=tr[u].tag;
	}
	tr[u].tag=-1;
}
inline void build(int u,int l,int r)
{
	tr[u].l=l,tr[u].r=r,tr[u].tag=-1;
	if(l == r) return tr[u].sum=a[l],void();
	int mid = (l + r) >> 1ll;
	build(u<<1,l,mid); build(u<<1|1,mid+1,r);
	pushup(u);
}
inline int query(int u,int l,int r)
{
	if(l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
	pushdown(u);
	int mid = (tr[u].l + tr[u].r) >> 1ll,res=0;
	if(l <= mid) res=query(u<<1,l,r); if(mid < r) res+=query(u<<1|1,l,r);
	return res;
}
inline void modify(int u,int l,int r,int k)
{
	if(l <= tr[u].l && tr[u].r <= r)
	{
		tr[u].sum=k*(tr[u].r - tr[u].l + 1);
		tr[u].tag=k; return ;
	}
	pushdown(u);
	int mid = (tr[u].l + tr[u].r) >> 1ll;
	if(l <= mid) modify(u<<1,l,r,k); if(mid < r) modify(u<<1|1,l,r,k);
	pushup(u);
}
struct node
{
	int l,r; mutable int v;
	bool operator < (const node &o) const {
		return l < o.l;
	}
} t[N]; set<node> s;
inline set<node> :: iterator split(int pos)
{
	auto it=s.lower_bound(node{pos,-1,0});
	if(it->l == pos && it != s.end()) return it;
	it -- ; int l=it->l,r=it->r,v=it->v;
	s.erase(it); s.insert(node{l,pos-1,v});
	return s.insert(node{pos,r,v}).first;
}
inline void assign(int l,int r,int v)
{
	auto itr=split(r+1),itl=split(l);
	s.erase(itl,itr); s.insert(node{l,r,v});
	modify(1,l,r,v);
}
inline void qr(int l,int r,int x)
{
	auto itr=split(r+1),itl=split(l); int pl=0,yl=1;
	for(auto it=itl;it!=itr;it++) it->v/=x,t[++pl]=*it;
	s.erase(itl,itr);
	for(int i=2;i<=pl;i++)
	{
		if(t[i].v == t[yl].v) t[yl].r=t[i].r;
		else t[++yl]=t[i];
	}
	for(int i=1;i<=yl;i++)
	{
		s.insert(node{t[i].l,t[i].r,t[i].v});
		modify(1,t[i].l,t[i].r,t[i].v);
	}
}
signed main()
{
	n=read(); q=read();
	for(int i=1,l=1;i<=n;i++)
	{
		a[i]=read(); if(i == 1) tt=a[i];
		else if(a[i] != tt || i == n)
		{
			s.insert(node{l,i-1,tt});
			l=i,tt=a[i];
		}
	}
	s.insert(node{n,n,a[n]}); build(1,1,n);
	while(q -- )
	{
		int op=read(),l=read(),r=read();
		if(op == 1) qr(l,r,read()); 
		else if(op == 2) assign(l,r,read());
		else printf("%lld\n",query(1,l,r));
	}
	return 0;
}

```
------------

这个玩意我把它作为有区间推平操作的势能线段树的下位替代品，可以说是用珂朵莉树来简化修改，或者说是用线段树来优化查询了，优点可能是少去了原本在线段树上分析势能的操作，比较无脑且好写，适合暴力。

---

