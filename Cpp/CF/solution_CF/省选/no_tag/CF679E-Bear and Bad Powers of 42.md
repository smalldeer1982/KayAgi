# Bear and Bad Powers of 42

## 题目描述

Limak, a bear, isn't good at handling queries. So, he asks you to do it.

We say that powers of $ 42 $ (numbers $ 1,42,1764,... $ ) are bad. Other numbers are good.

You are given a sequence of $ n $ good integers $ t_{1},t_{2},...,t_{n} $ . Your task is to handle $ q $ queries of three types:

1. 1 i — print $ t_{i} $ in a separate line.
2. 2 a b x — for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679E/410ca2de5f51b6a4a070685e9aced96067224755.png) set $ t_{i} $ to $ x $ . It's guaranteed that $ x $ is a good number.
3. 3 a b x — for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679E/410ca2de5f51b6a4a070685e9aced96067224755.png) increase $ t_{i} $ by $ x $ . After this repeat the process while at least one $ t_{i} $ is bad.

You can note that after each query all $ t_{i} $ are good.

## 说明/提示

After a query `3 2 4 42` the sequence is $ 40,1742,49,1714,4,1722 $ .

After a query `3 2 6 50` the sequence is $ 40,1842,149,1814,104,1822 $ .

After a query `2 3 4 41` the sequence is $ 40,1842,41,41,104,1822 $ .

After a query `3 1 5 1` the sequence is $ 43,1845,44,44,107,1822 $ .

## 样例 #1

### 输入

```
6 12
40 1700 7 1672 4 1722
3 2 4 42
1 2
1 3
3 2 6 50
1 2
1 4
1 6
2 3 4 41
3 1 5 1
1 1
1 3
1 5
```

### 输出

```
1742
49
1842
1814
1822
43
44
107
```

# 题解

## 作者：小粉兔 (赞：30)

注意到在可能的值域（约为 ${10}^{14}$）内，$42$ 的次幂并不多，尝试从这个角度考虑。

操作 3 比较棘手，解决的办法是用线段树维护当前值到下一个 $42$ 的次幂的差值。

做操作时让这个差值做区间减法，在线段树递归的时候，如果差值会变成负数，就需要再递归进子区间进行修改，但是如果这个区间被打上了区间覆盖标记，就直接修改这个标记就行。

执行完后，如果存在差值为 $0$ 的位置，就再执行一次。

这个做法的复杂度，使用势能函数可以分析得出为 $\mathcal O (q \log n \log_{42} v)$。

具体地说，令当前线段树的势能函数等于每个值相同的连续段，比此连续段的值大的，在值域内的 $42$ 的次幂的个数的总和，乘以 $\log n$。

则操作 2 和操作 3 的摊还代价都为 $\mathcal O (\log n \log_{42} v)$。

时间复杂度为 $\mathcal O ((n + q) \log n \log_{42} v)$，其中 $v$ 为值域，约为 ${10}^9 q$，[评测链接](https://codeforces.com/contest/679/submission/71983368)。

---

## 作者：CYJian (赞：8)

首先前两个操作属于线段树的基本操作。但是第三个操作看上去就有点辣手了。

如果我们在线段树中维护每个点到其最近的 $42$ 的整次幂的差值的最小值，那么可以每次暴力修改一次加操作后值为负的位置，没有二操作的情况下，每个点只会被修改最多 $\log_{42}val$ 次。每次修改复杂度 $O(\log_{2} n)$，总复杂度就是 $O((n + q) \log_{2} n \log_{42} val)$。

但是二操作和三操作都有，咋办呢？

我们考虑每次覆盖，只修改覆盖的区间的最右边那个点为要修改的值，其他的点赋值为 $\inf$，然后在每次操作区间 $[l, r]$ 的时候，将 $l-1$ 和 $r$ 的值修改为右边第一个不为 $\inf$ 的值即可。查询也是查询右边第一个不为 $\inf$ 的值作为这个位置的值。

不难发现，只有每次操作的时候会带来至多 $2$ 个新的值，每个值最多修改 $\log_{42}val$ 次。总复杂度还是 $O((n + q) \log_{2} n \log_{42} v)$。

在找右边第一个不是 $\inf$ 的值的时候可以用 STL 的 set 方便地实现。

代码还算好写。

${\rm Code}$：

```cpp
const int MAXN = 100010;
const ll inf = 100000000000000000LL;
const ll pw[] = {1LL, 42LL, 1764LL, 74088LL, 3111696LL, 130691232LL, 5489031744LL, 230539333248LL, 9682651996416LL, 406671383849472LL, 17080198121677824LL, 717368321110468608LL, 1000000000000000000LL};

set<int>pos;
ll a[MAXN];
ll ad[MAXN];
int n;

inline ll fdv(ll x) { return *lower_bound(pw, pw + 12, x); }

struct Segment_Tree {
#define ls (x << 1)
#define rs (x << 1 | 1)

	struct Node {
		ll v, tg, tv;

		Node():v(inf), tg(0), tv(0) {}
	} T[MAXN << 2];

	inline void pushup(int x) { T[x].v = min(T[ls].v, T[rs].v); }
	inline void pushdown(int x) {
		if(!T[x].tg && !T[x].tv) return ;
		Node &L = T[ls], &R = T[rs];
		if(T[x].tg) {
			L.v = L.tg = T[x].tg, L.tv = 0;
			R.v = R.tg = T[x].tg, R.tv = 0;
			T[x].tg = 0;
		}
		if(T[x].tv) {
			L.v += T[x].tv, L.tv += T[x].tv;
			R.v += T[x].tv, R.tv += T[x].tv;
			T[x].tv = 0;
		}
	}

	inline void build(int x, int l, int r) {
		if(l == r) return ad[l] = fdv(a[l]), T[x].v = ad[l] - a[l], void();
		int mid = (l + r) >> 1; build(ls, l, mid), build(rs, mid + 1, r), pushup(x);
	}

	inline void Assign(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return T[x].v = T[x].tg = inf, T[x].tv = 0, void();
		int mid = (l + r) >> 1; pushdown(x);
		if(L <= mid) Assign(ls, l, mid, L, R);
		if(mid < R) Assign(rs, mid + 1, r, L, R);
		pushup(x);
	}

	inline void Modify(int x, int l, int r, int p, ll v) {
		if(l == r) return ad[l] = fdv(v), T[x].v = ad[l] - v, void();
		int mid = (l + r) >> 1; pushdown(x);
		p <= mid ? Modify(ls, l, mid, p, v) : Modify(rs, mid + 1, r, p, v);
		pushup(x);
	}

	inline void Dec(int x, int l, int r, int L, int R, ll v) {
		if(L <= l && r <= R) return T[x].v -= v, T[x].tv -= v, void();
		int mid = (l + r) >> 1; pushdown(x);
		if(L <= mid) Dec(ls, l, mid, L, R, v);
		if(mid < R) Dec(rs, mid + 1, r, L, R, v);
		pushup(x);
	}

	inline ll Qm(int x, int l, int r) {
		if(T[x].v >= 0) return T[x].v;
		if(l == r) {
			T[x].v = ad[l] - T[x].v;
			ad[l] = fdv(T[x].v);
			T[x].v = ad[l] - T[x].v;
			return T[x].v;
		} int mid = (l + r) >> 1;
		pushdown(x);
		Qm(ls, l, mid), Qm(rs, mid + 1, r);
		pushup(x);
		return T[x].v;
	}

	inline ll Qval(int x, int l, int r, int p) {
		if(l == r) return ad[p] - T[x].v;
		int mid = (l + r) >> 1; pushdown(x);
		return p <= mid ? Qval(ls, l, mid, p) : Qval(rs, mid + 1, r, p);
	}

	inline void Split(int p) {
		int vp = *pos.lower_bound(p);
		if(vp == p) return ;
		ad[p] = ad[vp], pos.insert(p);
		Modify(1, 1, n, p, Qval(1, 1, n, vp));
	}

#undef ls
#undef rs
}seg;

int main() {
	n = ri; int q = ri;
	for(int i = 1; i <= n; i++) pos.insert(i), a[i] = ri; seg.build(1, 1, n);
	for(int i = 1; i <= q; i++) {
		int opt = ri;
		if(opt == 1) {
			int p = ri;
			printf("%lld\n", seg.Qval(1, 1, n, *pos.lower_bound(p)));
		} else {
			int l = ri, r = ri, v = ri;
			if(l > 1) seg.Split(l - 1);
			seg.Split(r);
			if(opt == 2) {
				pos.erase(pos.lower_bound(l), pos.lower_bound(r));
				if(l < r) seg.Assign(1, 1, n, l, r - 1);
				seg.Modify(1, 1, n, r, v);
			} else for(seg.Dec(1, 1, n, l, r, v); !seg.Qm(1, 1, n); seg.Dec(1, 1, n, l, r, v));
		}
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

> [CF679E Bear and Bad Powers of 42](https://www.luogu.com.cn/problem/CF679E) *3100

注意到在可能的值域范围内（粗略估计为 $qV \approx 10 ^ {14}$）$42$ 的幂的个数极少，因此，为了快速求出哪些位置是坏的，我们尝试记录每个位置上的值与下一个坏数的距离。用线段树维护区间最小值，若当前区间最小值小于增加值，则递归下去暴力修改。

这部分利用了线段树的势能分析，每个位置最多只会被递归修改 $\log_{42}qV$ 次。

对于区间赋值操作，由于其最多只会增加 $\mathcal{O}(1)$ 个相同的数的连续段，因此增加的操作次数为 $\log_{42} qV$。注意，我们是将连续段看成一个数处理，因此若当前区间被打上区间覆盖的懒标记，说明当前区间仅有一种数（这比用 set 处理连续段方便一些）。

注意区间加法和区间赋值的懒标记的先后顺序，笔者采用了优先区间赋值的方法，即若当前区间被赋值且被区间加，则该区间加会体现在区间赋值上。因此，若有区间赋值标记，则无区间加法标记，这样方便考虑。

因为每次操作均为 $\mathcal{O}(\log n)$，故总时间复杂度 $\mathcal{O}(n\log_{42}(nV) \log n)$（视 $n, q$ 同阶）。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
long long pw[N], val[N << 2], add[N << 2], laz[N << 2];
int n, q, a[N];
long long calc(long long a) {for(int i = 1; i <= 9; i++) if(pw[i] >= a) return pw[i] - a; assert(0);}
void pushup(int x) {val[x] = min(val[x << 1], val[x << 1 | 1]);}
void tagmo(int x, long long v) {val[x] = calc(laz[x] = v), add[x] = 0;}
void tagad(int x, long long v) {if(laz[x]) val[x] = calc(laz[x] += v); else assert(val[x] >= v), val[x] -= v, add[x] += v;}
void pushdown(int x) {
	if(laz[x]) tagmo(x << 1, laz[x]), tagmo(x << 1 | 1, laz[x]), laz[x] = 0, assert(!add[x]);
	if(add[x]) tagad(x << 1, add[x]), tagad(x << 1 | 1, add[x]), add[x] = 0;
}
void build(int l, int r, int x) {
	if(l == r) return val[x] = calc(laz[x] = a[l]), void();
	int m = l + r >> 1;
	build(l, m, x << 1), build(m + 1, r, x << 1 | 1);
	pushup(x); // add pushup =.=
}
void modifymo(int l, int r, int ql, int qr, int x, int v) {
	if(ql <= l && r <= qr) return tagmo(x, v);
	int m = l + r >> 1;
	pushdown(x);
	if(ql <= m) modifymo(l, m, ql, qr, x << 1, v);
	if(m < qr) modifymo(m + 1, r, ql, qr, x << 1 | 1, v);
	pushup(x);
}
void modifyad(int l, int r, int ql, int qr, int x, int v) {
	if(ql <= l && r <= qr && (laz[x] || val[x] >= v)) return tagad(x, v);
	int m = l + r >> 1;
	pushdown(x);
	if(ql <= m) modifyad(l, m, ql, qr, x << 1, v);
	if(m < qr) modifyad(m + 1, r, ql, qr, x << 1 | 1, v);
	pushup(x);
}
long long query(int p) {
	int l = 1, r = n, x = 1;
	while(l < r) {
		int m = l + r >> 1;
		pushdown(x);
		if(p <= m) r = m, x <<= 1;
		else l = m + 1, x = x << 1 | 1;
	}
	return laz[x];
}
int main() {
	cin >> n >> q, pw[0] = 1;
	for(int i = 1; i <= 9; i++) pw[i] = pw[i - 1] * 42;
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, n, 1);
	for(int i = 1; i <= q; i++) {
		int op, l, r, x;
		cin >> op;
		if(op == 1) cin >> x, cout << query(x) << endl;
		if(op == 2) cin >> l >> r >> x, modifymo(1, n, l, r, 1, x);
		if(op == 3) {
			cin >> l >> r >> x;
			do modifyad(1, n, l, r, 1, x);
			while(val[1] == 0); 
		}
	}
	return 0;
}
```

---

## 作者：xht (赞：5)

> [CF679E Bear and Bad Powers of 42](https://codeforces.com/contest/679/problem/E)

## 题意

- 定义一个正整数是坏的，当且仅当它是 $42$ 的次幂，否则它是好的。
- 给定一个长度为 $n$ 的序列 $a_i$，保证初始时所有数都是好的。
- 有 $q$ 次操作，每次操作有三种可能：
  - `1 i` 查询 $a_i$。
  - `2 l r x` 将 $a_{l\dots r}$ 赋值为一个好的数 $x$。
  - `3 l r x` 将 $a_{l \dots r}$ 都加上 $x$，重复这一过程直到所有数都变好。
- $n,q \le 10^5$，$a_i,x \le 10^9$。

## 题解

设 $n,q$ 同阶。

这个奇奇怪怪的 $42$ 一点性质都没有，但是这个**次幂**的提示性就很明显，一定范围内**次幂**这破玩意儿的个数再怎么多也只有 $\mathcal O(\log)$ 个。

因此对于一个数，它最多被额外加 $\mathcal O(\log_{42} w)$ 次。在没有操作 2 的情况下，用线段树维护每个数到 $42$ 的次幂的差值即可，时间复杂度为 $\mathcal O(n \log n \log_{42} w)$。

有区间赋值操作时，我们把这一整段的值记录在最右边的位置上，然后在别的位置上打个标记就好了。由于每次这样的操作最多只会产生两个新的值，因此时间复杂度没变。

## 代码

```cpp
const int N = 1e5 + 7;
const ll inf = 1e18;
int n, q;
ll p[12] = {1}, a[N];
set<int> s;
struct T {
	int l, r, o;
	ll z;
	pair<ll, int> x;
} t[N<<2];

inline int f(ll x) {
	return lower_bound(p, p + 12, x) - p; 
}

inline void upd(int p) {
	t[p].x = min(t[ls].x, t[rs].x);
}

inline void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) return t[p].x = mp(::p[t[p].o=f(a[l])] - a[l], l), void();
	build(ls, l, md), build(rs, md + 1, r), upd(p);
}

inline void spd(int p) {
	t[ls].z = max(-inf, t[ls].z + t[p].z);
	t[rs].z = max(-inf, t[rs].z + t[p].z);
	t[ls].x.fi = min(inf, t[ls].x.fi - t[p].z);
	t[rs].x.fi = min(inf, t[rs].x.fi - t[p].z);
	t[p].z = 0;
}

inline ll ask(int p, int x) {
	if (t[p].l == t[p].r) return ::p[t[p].o] - t[p].x.fi;
	spd(p);
	return ask(x <= md ? ls : rs, x);
}

inline void setx(int p, int o, ll x) {
	if (t[p].l == t[p].r)
		return t[p].x = mp(::p[t[p].o=f(x)] - x, t[p].l), void();
	spd(p);
	setx(o <= md ? ls : rs, o, x);
	upd(p);
}

inline void add(int p, int l, int r, ll x) {
	if (t[p].l >= l && t[p].r <= r)
		return t[p].z += x, t[p].x.fi -= x, void();
	spd(p);
	if (l <= md) add(ls, l, r, x);
	if (r > md) add(rs, l, r, x);
	upd(p);
}

inline void work2(int l, int r, ll x) {
	if (l != 1) setx(1, l - 1, ask(1, *s.lower_bound(l - 1))), s.insert(l - 1);
	s.erase(s.lower_bound(l), s.upper_bound(r));
	setx(1, r, x), s.insert(r);
	if (l < r) add(1, l, r - 1, -inf); 
}

inline void upd(int p, int x) {
	if (t[p].l == t[p].r) {
		ll k = ::p[t[p].o] - t[p].x.fi;
		t[p].x = mp(::p[t[p].o=f(k)] - k, t[p].l);
		return;
	}
	spd(p);
	upd(x <= md ? ls : rs, x);
	upd(p);
}

inline void work3(int l, int r, ll x) {
	if (l != 1) setx(1, l - 1, ask(1, *s.lower_bound(l - 1))), s.insert(l - 1);
	setx(1, r, ask(1, *s.lower_bound(r))), s.insert(r);
	do {
		add(1, l, r, x);
		while (t[1].x.fi < 0) upd(1, t[1].x.se);
	} while (!t[1].x.fi);
}

int main() {
	for (int i = 1; i < 12; i++) p[i] = p[i-1] * 42;
	rd(n), rd(q), rda(a, n);
	for (int i = 1; i <= n; i++) s.insert(i);
	build(1, 1, n);
	for (int i = 1, o, x, l, r; i <= q; i++) {
		rd(o);
		switch (o) {
			case 1 : rd(x), print(ask(1, *s.lower_bound(x))); break;
			case 2 : rd(l), rd(r), rd(x), work2(l, r, x); break;
			case 3 : rd(l), rd(r), rd(x), work3(l, r, x); break;
		}
	}
	return 0;
}
```

---

## 作者：duyi (赞：5)

[噜啦噜啦咧噜啦噜啦咧的阅读体验！！！](https://www.cnblogs.com/dysyn1314/p/14139849.html)



# CF679E Bear and Bad Powers of 42

[题目链接](https://codeforces.com/problemset/problem/679/E)

## 本题题解

> 根据笔者的习惯，我们称要维护的序列为 $a_{1\dots n}$，即原题面里的 $t$。

设经过任何操作后，序列里的最大数值为 $\text{maxValue}$。则 $\text{maxValue}\leq 10^9 + q\times 10^9\times \log_{42}(\text{maxValue})$。容易发现 $\text{maxValue}$ 不会超过 $\texttt{long long}$ 范围（这只是一个粗略的估计，实际上更小）。

因此，可能出现的 $42$ 的幂数量非常少，不超过 $\log_{42}(\text{maxValue})\leq 13$ 个。

---

先不考虑操作 $2$（区间赋值）。

用线段树维护序列，支持区间加。考虑在进行操作 $3$（区间加）时，写一个暴力的 $\texttt{while}$ 循环：只要区间里出现了 $42$ 的幂，就再加一次。因为每个数最多只会出现 $\log_{42}(\text{maxValue})$ 次等于 $42$ 的幂的情况，因此总的操作次数是 $\mathcal{O}(n\times \log_{42}(\text{maxValue}))$ 的。

于是问题转化为，如何快速判断，区间里是否存在 $42$ 的幂。

对于序列里的每个数 $a_i$，记第一个大于等于它的、$42$ 的幂为 $b_i$，即 $b_i = 42^{\lceil\log_{42}(a_i)\rceil}$。考虑 $b_i - a_i$ 这个序列，一次“区间加 $x$”，相当于令这个序列上每个位置减 $x$。当出现某个位置上数值 $b_i - a_i < 0$ 时，说明该位置的 $b_i$ 需要更新了，我们暴力更新（根据前面的分析，总更新次数是 $\mathcal{O}(n\times \log_{42}(\text{maxValue}))$ 的）。更新完后，如果出现某个位置上 $b_i - a_i = 0$，就说明原序列（$a$）里存在 $42$ 的幂，我们继续执行区间加。

也就是说，现在我们维护 $b_i - a_i$ 这个序列，支持区间加、单点修改（暴力更新 $b_i$）、求区间最小值。可以用线段树实现，这样单次修改时间复杂度是 $\mathcal{O}(\log_2(n))$ 的。总时间复杂度 $\mathcal{O}((n + q)\times \log_{42}(\text{maxValue})\times \log_2(n))$。

---

再考虑有操作 $2$ 的情况。如果我们直接在线段树上执行区间赋值，就可能会影响前面的复杂度分析：因为此时无法保证 $a$ 序列每个位置上数值都随时间单调变大，也就无法保证总更新次数只有 $\mathcal{O}(n\times \log_{42}(\text{maxValue}))$ 了。

设一次操作 $2$ 的区间为 $[l,r]$，考虑只修改 $r$，然后把区间 $[l,r - 1]$ 设为一个“懒惰状态”。形式化地，懒惰状态满足：

- 在区间加（操作 $3$）检查更新 $b_i$ 时，不会被更新到。
- $a_n$ 不会处于懒惰状态（因为每次只把 $[l,r - 1]$ 设为懒惰状态，显然 $r -1 < n$）。
- 如果 $a_i$ 处于懒惰状态，则 $a_i$ 的实际数值，等于它后面第一个非懒惰状态的值（根据上一条，这样的值一定存在）。

例如，在实现时，我们令 $b_i$ 不变，把 $a_i$ 变成 $-\infty$，这样 $b_i - a_i$ 就永远 $> 0$，区间加检查更新时永远不会被更新到。 

初始时，所有值都处于非懒惰状态。在执行操作 $2$ 时，把区间 $[l,r - 1]$ 里所有值暴力设置为懒惰状态（线段树单点修改）。在执行操作 $2$ 或操作 $3$ 前，检查 $l - 1$, $r$ 这两个位置，如果是懒惰状态，则将它们更新：找出它后面第一个非懒惰状态的值，把被更新的位置赋为这个值。

实现时，可以用一个 $\texttt{std::set}$ 来维护所有非懒惰状态的位置。更新时，用 $\texttt{std::set}$ 的 $\texttt{lower_bound}$ 进行查找。

分析这样做的时间复杂度。在每次操作中，只会增加 $\mathcal{O}(1)$ 个非懒惰状态（$l - 1$ 和 $r$），因此整个过程中，出现的非懒惰状态总数是 $\mathcal{O}(n + q)$ 的，这样插入和暴力删除的总时间复杂度都是 $\mathcal{O}((n + q)\times \log_2(n))$ 的。同时，在线段树中，我们只进行了 $\mathcal{O}(n + q)$ 次“把某个位置的值重置”的操作，而其它情况下值都是随时间单调变大的，于是可以套用之前的复杂度分析。

综上，我们在 $\mathcal{O}((n + q)\times \log_{42}(\text{maxValue})\times \log_2(n))$ 的时间复杂度内解决了本题。

## 参考代码


[勇敢向前进，前进有奖品！！！](https://www.cnblogs.com/dysyn1314/p/14139849.html)


---

## 作者：Hadtsti (赞：3)

### 题意简述

我们称 $42$ 的**正整数**次幂为“坏数”（正整数次幂，不包含 $1$），而其他的正整数都是“好数”。

给出长度为 $n(1\le n\le10^5)$ 的序列 $a_i(1\le a_i\le10^9)$，并进行 $q(1\le q\le 10^5)$ 次操作。操作共三种：

1. 给定 $x$，求 $a_x$ 的值。

2. 给定 $l,r$，将区间 $a_l,a_{l+1},\cdots,a_{r-1},a_r$ 全赋值为给定的 $x(1\le x\le10^9)$。

3. 给定 $l,r$ 和 $x(1\le x\le10^9)$。先将 $a_l,a_{l+1},\cdots,a_{r-1},a_r$ 全部加上 $x$，然后不断如此操作下去一直到 $a_l,a_{l+1},\cdots,a_{r-1},a_r$ 都是“好数”为止。

### 题目分析

显然操作三并不能不停操作下去（操作有限次之后一定能找到两个相邻的 $42$ 的次幂使得 $a_l\sim a_r$ 都夹在其之间，证明此处不多赘述），这就表明可能涉及到的 $42$ 的次幂也是有限的。具体来说，最大的 $42$ 的次幂在 $O(qx)$ 级别，也就是 $10^{14}$ 左右，不会超过 $42^9≈4\times10^{14}$。可以直接把 $42^1,42^2,\cdots,42^9$ 即所谓“坏数”预处理一下。

考虑使用线段树维护 $a_l\sim a_r$ 之间每个 $a_i$ 到下一个“坏数”距离的最小值。操作二的区间赋值很简单，打懒标记简单处理，更新最小值直接 `lower_bound` 查找新的“坏数”计算就行（直接枚举也行）；操作三则先实现区间加，然后不断区间加直到 $a_1\sim a_n$ 距“坏数”距离最小值不为 $0$ 即可。而单点查询，单凭一个数距“坏数”的距离不能确定其原始值，但是区间赋值标记可以解决这一问题。我们直接让 $l=r$ 的结点的区间赋值标记记录原始值即可。

至于时间复杂度，根据刚刚的分析，每个位置只会被修改 $O(\log_{42}qx)$ 次，所以总时间复杂度为 $O((n+q)\log_2n\log_{42}qx)$

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,op,l,r;
long long pow42[12],a[100010],x;
struct node
{
	int l,r;//左右端点。 
	long long mn,tag1,tag2;//mn：离下一个“坏数”距离的最小值；tag1 是区间加标记，tag2 是区间赋值标记。 
}tr[400010];
template<typename T>void rd(T &x)
{
	x=0;
	char c=getchar();
	for(;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
}//快读 
template<typename T>void wt(T x)
{
	if(x>=10)
		wt(x/10);
	putchar(x%10+'0');
}//快写 
long long calc(long long x)
{
	return (*lower_bound(pow42+1,pow42+11,x))-x;//距下一个“坏数”的距离 
}
void pushup(int p)
{
	tr[p].mn=min(tr[p<<1].mn,tr[p<<1|1].mn);
}//子结点更新父结点 
void addtag1(int p,long long tag)
{
	if(tr[p].tag2)//区间赋值过就加到标记上 
	{
		tr[p].tag2+=tag;
		tr[p].mn=calc(tr[p].tag2);
	} 
	else//没区间赋值过就直接打标记 
	{
		tr[p].mn-=tag;
		tr[p].tag1+=tag;
	}
}//区间加打标记 
void addtag2(int p,long long tag)
{
	tr[p].tag2=tag;
	tr[p].mn=calc(tag);
	tr[p].tag1=0;//区间赋值之后，之前的区间加都失效 
}//区间赋值打标记 
void pushdown(int p)
{
	if(tr[p].tag1)
	{
		addtag1(p<<1,tr[p].tag1);
		addtag1(p<<1|1,tr[p].tag1);//向左右子结点下传标记 
		tr[p].tag1=0;//清空标记 
	}
	if(tr[p].tag2)
	{
		addtag2(p<<1,tr[p].tag2);
		addtag2(p<<1|1,tr[p].tag2);//向左右子结点下传标记 
		tr[p].tag2=0;//清空标记 
	}
}
void build(int p,int l,int r)//建树 
{
	tr[p].l=l,tr[p].r=r;
	if(l==r)
	{
		addtag2(p,a[l]);//为了方便询问，初始化就添上一个赋值标记 
		return;
	}
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
void change1(int p,int l,int r,int x)//区间加 
{
	if(tr[p].l>=l&&tr[p].r<=r/*区间全包含*/&&(tr[p].tag2||tr[p].mn>=x)/*若被区间赋值过或者区间加操作完后，没有比原来的“坏数”大，那么就可以直接打标记*/)
	{
		addtag1(p,x);
		return;
	}
	//否则就递归下去算 
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(mid>=l)
		change1(p<<1,l,r,x);
	if(mid<r)
		change1(p<<1|1,l,r,x);
	pushup(p);
}
void change2(int p,int l,int r,int x)//区间赋值 
{
	if(tr[p].l>=l&&tr[p].r<=r)
	{
		addtag2(p,x);
		return;
	}
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(mid>=l)
		change2(p<<1,l,r,x);
	if(mid<r)
		change2(p<<1|1,l,r,x);
	pushup(p);
}
long long query(int p,int x)//单点查询，也可以直接二分实现 
{
	if(tr[p].l==tr[p].r)
		return tr[p].tag2;
	int mid=tr[p].l+tr[p].r>>1;
	pushdown(p);
	if(mid>=x)
		return query(p<<1,x);
	else
		return query(p<<1|1,x);
}
int main()
{
	pow42[0]=1ll;
	for(int i=1;i<=10;i++)
		pow42[i]=42ll*pow42[i-1];//预处理“坏数” 
	rd(n),rd(q);
	for(int i=1;i<=n;i++)
		rd(a[i]);
	build(1,1,n);
	while(q--)
	{
		rd(op),rd(l);
		switch(op)
		{
			case 1:
				wt(query(1,l));
				putchar('\n');
				break;
			case 2:
				rd(r),rd(x);
				change2(1,l,r,x);	
				break;
			case 3:
				rd(r),rd(x);
				do
				{
					change1(1,l,r,x);
				}while(tr[1].mn==0);//由于至少要操作一次，所以用 do-while。 
		}
	}
	return 0;
}
```


---

## 作者：ty_mxzhn (赞：2)

读题，发现 $42^k$ 在 $10^{18}$ 内极其少，考虑利用这个性质。

建立势能系统，于是我们定义一个数的二级势能为其到下一个 $42^k$ 的距离。这个数的一级势能为他前面有几个 $42^k$。

用线段树维护势能，定义线段树一个节点的二级势能为其管辖范围内所有数的二级势能最小值。于是操作 $3$ 时，如果二级势能 $>x$ 则直接减去，否则暴力传下去修改。因为每次传下去修改时都有至少一个数的一级势能增大，则时间复杂度 $O(n \log n \log_{42} V)$。

考虑操作 $2$。操作 $2$ 会将一些数修改成同一个数，可以打一个区间覆盖标记表示这个区间都是同一个数，这样比较好写。

---

## 作者：tzc_wk (赞：2)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/679/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF679E)

这个 $42$ 的条件非常奇怪，不过注意到本题 $a_i$ 范围的最大值为 $10^{14}$，而在值域范围内 $42$ 的幂的个数最多只有 $13$ 个，故考虑用类似于 seg-beats 的方法解决这道题。

首先不考虑操作 $2$（区间赋值操作），我们很容易发现一个性质，那就是我们对一个区间进行区间加的操作，每额外进行一次，都是因为存在某个数 $a_i$ 达到了 $42$ 的整数次幂，而我们的 $a_i$ 是单调递增的，故每个数最多只可能出现 $13$ 次成为 $42$ 的整数次幂的时刻，故总操作次数最多只有 $1.3\times 10^6$，于是暴力加是不会出问题的。故现在问题转化为怎样求一个区间中是否存在 $42$ 的整数次幂。

考虑记 $b_i$ 为 $\geq a_i$ 的最小的 $42$ 的整数次幂。显然我们对区间进行 $+v$ 操作相当于将对应区间 $b_i-a_i$ 的值 $-v$，这个操作可以用线段树维护。当然，我们进行一次 $-v$ 操作后会导致某些 $b_i-a_i$ 变成负数，也就是说，此时的 $b_i$ 不再是 $\geq a_i$ 的最小的 $42$ 的整数次幂了，我们对于这样的 $i$ 暴力修改 $b_i$ 的值，具体来说，线段树维护 $b_i-a_i$ 的最小值，每次修改后在线段树上进行一遍递归，当递归到某个区间时若该区间 $b_i-a_i$ 的最小值 $\geq 0$ 则意味着不存在 $b_i-a_i<0$ 的 $i$，直接 `return` 就行了，否则继续递归左右儿子，递归到叶子节点直接把值改掉。由之前的分析可知最多修改次数也是 $1.3\times 10^6$，如此暴力进行下去直到全局 $b_i-a_i$ 不为 $0$（不存在 $a_i=b_i$）即可，复杂度 $q\log_{42}(qa_i)\log n$。

接下来考虑加上区间赋值操作之后怎么处理。由于我们有区间赋值操作，故刚才总操作次数 $1.3\times 10^6$ 的复杂度上界就不再存在了（不过听说按照之前的套路暴力赋值也能过？大概是因为这题数据比较难卡罢）。不过作为精益求精的 OIer，我们要思考更优秀的做法。不难发现进行一遍区间赋值之后会使很多位置上的值变成同一个值，也就是说我们区间赋值操作会将序列划分成一段段，我们考虑用 `multiset` 维护每一段的右端点，这样查询的时候只用查询对应位置所在段的右端点的值即可。

具体来说，初始状态下所有元素都单独成段，也就是每个元素都是对应段的右端点。当我们进行 $2$ 操作的时候，相当于 $[l,r]$ 成为了完整的一段，故我们将 `multiset` 中 $[l,r-1]$ 内的元素全部删除并插入 $r$，由于我们只关心段的右端点的值即可，于是我们将线段树 $[l,r-1]$ 位置上赋上 INF（为了保证它们永远不会变成负数），暂且忽略它们的存在，并将 $r$ 位置上的值改为待赋的值。当然，这样也会导致 $l-1$ 成为新的段的右端点，故在 `multiset` 中插入 $l-1$，并将 $l-1$ 位置上的值改为真实值（原本 $l-1$ 所在段的右端点的值）即可。其余都和不考虑操作 $2$ 的版本一样。

复杂度还是 $q\log_{42}(qa_i)\log n$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
const int LOG_42=13;
const ll INF=1e18;
int n,qu;set<int> st;
ll pw42[LOG_42+2];
ll get42(ll v){return *lower_bound(pw42,pw42+LOG_42+1,v);}
struct node{int l,r;ll v,tag_lz,add_lz;} s[MAXN*4+5];
ll a[MAXN+5],nxt42[MAXN+5];
void pushup(int k){s[k].v=min(s[k<<1].v,s[k<<1|1].v);}
void pushdown(int k){
	if(s[k].tag_lz!=0){
		s[k<<1].v=s[k].tag_lz;s[k<<1|1].v=s[k].tag_lz;
		s[k<<1].tag_lz=s[k].tag_lz;s[k<<1|1].tag_lz=s[k].tag_lz;
		s[k].tag_lz=0;
	}
	if(s[k].add_lz!=0){
		s[k<<1].v+=s[k].add_lz;s[k<<1|1].v+=s[k].add_lz;
		s[k<<1].add_lz+=s[k].add_lz;s[k<<1|1].add_lz+=s[k].add_lz;
		s[k].add_lz=0;
	}
}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;
	if(l==r){nxt42[l]=get42(a[l]);s[k].v=nxt42[l]-a[l];return;}
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}
void assign(int k,int l,int r,ll x){
	if(l<=s[k].l&&s[k].r<=r){s[k].tag_lz=s[k].v=x;return;}
	pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) assign(k<<1,l,r,x);
	else if(l>mid) assign(k<<1|1,l,r,x);
	else assign(k<<1,l,r,x),assign(k<<1|1,mid+1,r,x);
	pushup(k);
}
void change_v(int k,int p,ll x){
	if(s[k].l==s[k].r){
		nxt42[s[k].l]=get42(x);s[k].v=nxt42[s[k].l]-x;return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(p<=mid) change_v(k<<1,p,x);
	else change_v(k<<1|1,p,x);
	pushup(k);
}
void add(int k,int l,int r,ll x){
	if(l<=s[k].l&&s[k].r<=r){s[k].add_lz+=x;s[k].v+=x;return;}
	pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) add(k<<1,l,r,x);
	else if(l>mid) add(k<<1|1,l,r,x);
	else add(k<<1,l,r,x),add(k<<1|1,mid+1,r,x);
	pushup(k);
}
void killneg(int k){
	if(s[k].v>=0) return;
	if(s[k].l==s[k].r){
		s[k].v=nxt42[s[k].l]-s[k].v;
		nxt42[s[k].l]=get42(s[k].v);
		s[k].v=nxt42[s[k].l]-s[k].v;
		return;
	} pushdown(k);killneg(k<<1);killneg(k<<1|1);
	pushup(k);
}
ll getdif(int k,int p){
	if(s[k].l==s[k].r) return s[k].v;
	int mid=s[k].l+s[k].r>>1;pushdown(k);
	if(p<=mid) return getdif(k<<1,p);
	else return getdif(k<<1|1,p);
}
ll query(int k,int p){
	if(s[k].l==s[k].r) return nxt42[s[k].l]-s[k].v;
	int mid=s[k].l+s[k].r>>1;pushdown(k);
	if(p<=mid) return query(k<<1,p);
	else return query(k<<1|1,p);
}
void split(int x){
	int nxt=*st.lower_bound(x);
	if(nxt==x) return;st.insert(nxt);
	change_v(1,x,query(1,nxt));st.insert(x);
}
int main(){
	pw42[0]=1;for(int i=1;i<=LOG_42;i++) pw42[i]=pw42[i-1]*42ll;
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),st.insert(i);
	build(1,1,n);
	while(qu--){
		int opt;scanf("%d",&opt);
		if(opt==1){int x;scanf("%d",&x);printf("%lld\n",query(1,*st.lower_bound(x)));}
		else if(opt==2){
			int l,r,v;scanf("%d%d%d",&l,&r,&v);
			if(l>1) split(l-1);split(r);
			st.erase(st.lower_bound(l),st.lower_bound(r));
			if(l<r) assign(1,l,r-1,INF);
			change_v(1,r,v);
		} else {
			int l,r,v;scanf("%d%d%d",&l,&r,&v);
			if(l>1) split(l-1);split(r);
			do {
				add(1,l,r,-v);killneg(1);
			} while(s[1].v==0);
		}
	}
	return 0;
}
/*
6 13
40 1700 7 1672 4 1722
3 2 4 42
1 2
1 3
1 4
3 2 6 50
1 2
1 4
1 6
2 3 4 41
3 1 5 1
1 1
1 3
1 5
*/
```



---

## 作者：foreverlasting (赞：2)

[推销博客](https://foreverlasting1202.github.io/2019/07/03/CF679E/)

一道需要分析复杂度的线段树题。
<!--more-->

操作$1$和操作$2$显然是个线段树的基本操作，但操作$3$有点奇怪。我们对于线段树上每一个点维护一个$dis$表示到离该点最近的且比该点大的好数，然后对于操作$3$每次暴力线段树上区间加，直到这棵树的最小$dis$为$0$。那么这里就有几个问题：

一、加到超过怎么办

二、复杂度怎么证

其实这两个问题是一个问题。加到超过的话你可以直接选择暴力重构，这个复杂度其实是对的。我们来分析一下：每一次暴力重构，最多调整$12$次（因为保证了小于等于$1e18$），那么总的调整复杂度也不超过$12nlogn$。同样地，第二个问题也是同样分析得出，因此这题就做好了。

code:
```cpp
//2019.7.3 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 1100005
#define INF 0x3f3f3f3f3f3f3f
#define eps 1e-10
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
inline int read() {
    res s=0,ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline int read() {
//    res s=0,ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N=1e5+10;
const LL pw[]={1LL,42LL,1764LL,74088LL,3111696LL,130691232LL,5489031744LL,230539333248LL,9682651996416LL,406671383849472LL,17080198121677824LL,717368321110468608LL};
namespace MAIN{
    int n,q;
    LL di[N<<2],ad[N<<2],co[N<<2];
    int lo[N<<2];
    inline int Log(const RG LL &x){
        return int(lower_bound(pw,pw+12,x)-pw);
    }
    void build(res rt,res l,res r){
//        L[rt]=l,R[rt]=r;
        if(l==r){
            res x=read();
            lo[rt]=Log(x),di[rt]=pw[lo[rt]]-x;
            return;
        }
        res mid=(l+r)>>1;
        build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
        di[rt]=min(di[rt<<1],di[rt<<1|1]);
    }
//    inline void Change(const res &rt,const RG LL &Co,const RG LL &Ad){
//        if(Co)lo[rt]=Log(Co),di[rt]=pw[lo[rt]]-Co,co[rt]=Co,ad[rt]=0,val[rt]=Co;
//        if(Ad)di[rt]-=Ad,ad[rt]+=Ad,val[rt]+=Ad;
//    }
//    inline void Pushdown(const res &rt){
//        Change(rt<<1,co[rt],ad[rt]),Change(rt<<1|1,co[rt],ad[rt]),co[rt]=ad[rt]=0;
//    }
//    void rebuild(res rt,res l,res r){
//        if(l==r){
//            lo[rt]=Log(val[rt]),di[rt]=pw[lo[rt]]-val[rt];
//            return;
//        }
//        Pushdown(rt);
//        res mid=(l+r)>>1;
//        rebuild(rt<<1,l,mid),rebuild(rt<<1|1,mid+1,r);
//        di[rt]=min(di[rt<<1],di[rt<<1|1]);
//    }
//    inline void change(const res &rt,const RG LL &Co,const RG LL &Ad){
//        if(Co)lo[rt]=Log(Co),di[rt]=pw[lo[rt]]-Co,co[rt]=Co,ad[rt]=0;
//        if(Ad){
//            if(co[rt])co[rt]+=Ad;
//            else di[rt]-=Ad,ad[rt]+=Ad;
//        }
////        if(di[rt]<0)rebuild(rt,L[rt],R[rt]);
//    }
    inline void add(const res &rt,const RG LL &Ad){
        co[rt]?co[rt]+=Ad:ad[rt]+=Ad,di[rt]-=Ad;
    }
    inline void cov(const res &rt,const RG LL &Co){
        lo[rt]=Log(Co),di[rt]=pw[lo[rt]]-Co,co[rt]=Co,ad[rt]=0;
    }
    inline void pushdown(const res &rt){
        if(!co[rt]&&!ad[rt])return;
        if(co[rt])cov(rt<<1,co[rt]),cov(rt<<1|1,co[rt]),co[rt]=0;
        if(ad[rt])add(rt<<1,ad[rt]),add(rt<<1|1,ad[rt]),ad[rt]=0;
    }
    void modify(res rt,res l,res r,const res &L,const res &R,const res &co,const res &ad){
        if(L<=l&&r<=R){co?cov(rt,co):add(rt,ad);return;}
        pushdown(rt);
        res mid=(l+r)>>1;
        if(L<=mid)modify(rt<<1,l,mid,L,R,co,ad);
        if(R>mid)modify(rt<<1|1,mid+1,r,L,R,co,ad);
        di[rt]=min(di[rt<<1],di[rt<<1|1]);
    }
    LL get(res rt,res l,res r,const res &p){
        if(l==r)return pw[lo[rt]]-di[rt];
        pushdown(rt);
        res mid=(l+r)>>1;
        if(p<=mid)return get(rt<<1,l,mid,p);
        return get(rt<<1|1,mid+1,r,p);
    }
    LL query(res rt,res l,res r){
        if(di[rt]>=0)return di[rt];
        if(l==r){
            RG LL x=pw[lo[rt]]-di[rt];
            lo[rt]=Log(x),di[rt]=pw[lo[rt]]-x;
            return di[rt];
        }
        pushdown(rt);
        res mid=(l+r)>>1;
        query(rt<<1,l,mid),query(rt<<1|1,mid+1,r),di[rt]=min(di[rt<<1],di[rt<<1|1]);
        return di[rt];
    }
    inline void MAIN(){
        n=read(),q=read(),build(1,1,n);
        while(q--){
            res opt=read();
            if(opt==2){
                res l=read(),r=read(),x=read();
                modify(1,1,n,l,r,x,0);
            }
            else if(opt==1){
                res p=read();
                printf("%lld\n",get(1,1,n,p));
            }
            else{
                res l=read(),r=read(),x=read();
                modify(1,1,n,l,r,0,x);
                while(!query(1,1,n))modify(1,1,n,l,r,0,x);
            }
        }
    }
}
int main() {
//    srand((unsigned)time(NULL));
    // freopen("zao.in","r",stdin);
    // freopen("std.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

