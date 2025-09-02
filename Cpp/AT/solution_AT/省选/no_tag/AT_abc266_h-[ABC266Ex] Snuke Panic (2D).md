# [ABC266Ex] Snuke Panic (2D)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc266/tasks/abc266_h

高橋君はすぬけ君たちを捕まえようとしています。

$ 2 $ 次元座標平面上にいくつか穴があいており、すぬけ君たちの巣につながっています。

これから $ N $ 匹のすぬけ君が穴から出てきます。$ i $ 番目のすぬけ君は時刻 $ T_i $ に座標 $ (X_i,Y_i) $ の穴から出てきて、大きさは $ A_i $ であることがわかっています。

高橋君は時刻 $ 0 $ に座標 $ (0,0) $ におり、以下の $ 2 $ 種類の移動ができます。

- $ x $ 軸方向に単位時間あたり $ 1 $ 以下の速さで移動する
- $ y $ 軸**正**方向に単位時間あたり $ 1 $ 以下の速さで移動する

$ y $ 軸負方向に移動することはできません。

すぬけ君が穴から出てきたのと同じ時刻に同じ座標に高橋君がいるとき、かつ、そのときに限り、高橋君はすぬけ君を捕まえることができます。  
すぬけ君を捕まえるのにかかる時間は無視できます。

高橋君が適切に行動したとき、捕まえることができるすぬけ君の大きさの合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ T_i\ \leq\ 10^9 $
- $ 0\ \leq\ X_i,Y_i\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ (T_i,X_i,Y_i) $ は相異なる
- 入力に含まれる値は全て整数である

### Sample Explanation 1

\- 座標 $ (0,0) $ で待機し、時刻 $ 1 $ に $ 1 $ 番目のすぬけ君を捕まえる - 座標 $ (3,1) $ へ移動し、時刻 $ 5 $ に $ 3 $ 番目のすぬけ君を捕まえる $ 1 $ 番目と $ 2 $ 番目のすぬけ君を両方とも捕まえることはできないので、これが最大です。

### Sample Explanation 2

$ y $ 軸負方向には移動できないため、$ 1 $ 番目のすぬけ君を捕まえた後、$ 2 $ 番目のすぬけ君を捕まえることはできません。

## 样例 #1

### 输入

```
3
1 0 0 100
3 2 1 10
5 3 1 1```

### 输出

```
101```

## 样例 #2

### 输入

```
2
100 0 1 1
200 1 0 10```

### 输出

```
10```

## 样例 #3

### 输入

```
10
797829355 595605750 185676190 353195922
913575467 388876063 395940406 533206504
810900084 201398242 159760440 87027328
889089200 220046203 85488350 325976483
277429832 161055688 73308100 940778720
927999455 429014248 477195779 174616807
673419335 415891345 81019893 286986530
989248231 147792453 417536200 219371588
909664305 22150727 414107912 317441890
988670052 140275628 468278658 67181740```

### 输出

```
1553741733```

# 题解

## 作者：acauto (赞：2)

# [ABC266Ex] Snuke Panic (2D) 题解

## 前言

前几天看到了[这个](https://www.luogu.com.cn/discuss/1035414)，发现自己还真没仔细思考过。

做了两道题，把这个题当个总结。

## 思路

设 $f_i$ 表示：在 $T_i$ 走到第 $i$ 个节点的最大收益。

有转移：$f_i=\max \{f_j\} + A_i$。

其中 $j$ 需要满足:

- $y_j\le y_i$
- $T_i\le T_i$
- $|x_i-x_j|+y_i-y_j\le T_i-T_j$

第三条限制可以转化为：$x_i-x_j+y_i-y_j\le T_i-T_j \land x_j-x_i+y_i-y_j\le T_i-T_j$。

容易发现满足第三条限制一定满足第二条限制，所以有如下限制：

- $y_i\ge y_j$
- $x_i+y_i-T_i\le x_j+y_j-T_j$
- $-x_i+y_i-T_i\le -x_j+y_j-T_j$

然后其实就是三维偏序了。因为这些点没有顺序限制，所以在外层可以排序掉一维，第二维可以用 CDQ 分治处理，第三为用树状数组即可。值得注意的是，因为有初始的点 $(0,0)$，所以我们有 $n+1$ 个点，离散化后树状数组应该跑到 $n+1$。

### CDQ 实现的时候为什么和平常写的不太一样？

这里的“平常”指先把左右都递归下去再算贡献。

因为如果我们按平常的做法，其实是左右各自贡献，如下图中橙色。但这会出问题，我们更新最右边的时候用的是**没有被左边更新**的**右端的左侧**，所以错了。

粉色的顺序才应该是对的。

![](https://cdn.luogu.com.cn/upload/image_hosting/esdn8a8s.png)

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define IL inline
#define vec vector
#define bg begin
#define eb emplace_back
#define emp emplace
#define fi first
#define se second
#define mkp make_pair
#define lb lower_bound
#define ub upper_bound
using ubt = long long;
using uubt = unsigned long long;
using dub = double;
using pii = pair<int, int>;
using puu = pair<ubt, ubt>;

IL void ckx(int &x, const int &y) { (x < y) && (x = y); }
IL void ckm(int &x, const int &y) { (x > y) && (x = y); }

template <typename T = int>
IL T _R() {
  T s = 0, w = 1;
  char c = getchar();
  while (!isdigit(c)) w = c == '-' ? -1 : 1, c = getchar();
  while (isdigit(c)) s = s * 10 + c - 48, c = getchar();
  return s * w;
}

const int inf = 1e18;

const int N = 1e5;
const int maxN = N + 3;

int n;
int f[maxN], id[maxN], fid[maxN];
int sot[maxN];

struct node {
  int x, y, t;
  int A;

  int k1, k2;
  IL void init() {
    k1 = -x + sot[y] - t;
    k2 = x + sot[y] - t;
  }

  IL friend bool operator < (const node &A, const node &B) {
    if (A.k2 != B.k2) return A.k2 > B.k2;
    if (A.k1 != B.k1) return A.k1 > B.k1;
    if (A.y != B.y) return A.y < B.y;
    if (A.t != B.t) return A.t < B.t;
    assert(false);
  }
  IL friend bool operator <= (const node &A, const node &B) {
    return !(B < A);
  }
} a[maxN];

IL bool cmp(int i, int j) { return a[i] < a[j]; }

struct BIT {
  int t[maxN];
  IL void ins(int x, int b) {
    for (; x <= n + 1; x += x & -x) ckx(t[x], b);
  }
  IL int ask(int x) {
    int res = -inf;
    for (; x > 0; x -= x & -x) ckx(res, t[x]);
    return res;
  }
  IL void clr(int x) {
    for (; x <= n + 1; x += x & -x) t[x] = -inf;
  }
  BIT() { memset(t, ~0x3f, sizeof(t)); }
} T;

void cdq(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  cdq(l, mid);

  for (int i = mid + 1; i <= r; i++) fid[i] = id[i];
  sort(fid + mid + 1, fid + r + 1, cmp);
  int t1 = l, t2 = mid + 1;
  while (t1 <= mid && t2 <= r) {
    if (a[id[t1]] <= a[fid[t2]]) {
      T.ins(a[id[t1]].y, f[id[t1]]);
      t1++;
    } else {
      ckx(f[fid[t2]], T.ask(a[fid[t2]].y) + a[fid[t2]].A);
      t2++;
    }
  }
  while (t2 <= r)
    ckx(f[fid[t2]], T.ask(a[fid[t2]].y) + a[fid[t2]].A),
    t2++;
  for (int i = l; i <= mid; i++) T.clr(a[id[i]].y);

  cdq(mid + 1, r);

  stable_sort(id + l, id + r + 1, cmp);
}

signed main() {
  n = _R();
  for (int i = 1; i <= n; i++) {
    a[i].t = _R(), a[i].x = _R(), a[i].y = _R(), a[i].A = _R();
    sot[i] = a[i].y;
  }

  sot[n + 1] = 0;
  sort(sot + 1, sot + n + 2);
  for (int i = 0; i <= n; i++)
    a[i].y = lb(sot + 1, sot + n + 2, a[i].y) - sot;

  for (int i = 0; i <= n; i++)
    a[i].init();

  sort(a, a + n + 1, [&](const auto &A, const auto &B) {
    if (A.k1 != B.k1) return A.k1 > B.k1;
    if (A.k2 != B.k2) return A.k2 > B.k2;
    if (A.y != B.y) return A.y < B.y;
    if (A.t != B.t) return A.t < B.t;
    assert(false);
  });
  memset(f, ~0x3f, sizeof(f));
  f[0] = 0;
  for (int i = 0; i <= n; i++) id[i] = i;
  cdq(0, n);

  int ans = 0;
  for (int i = 1; i <= n; i++) ckx(ans, f[i]);
  printf("%lld\n", ans);
}
```

---

## 作者：EuphoricStar (赞：2)

考虑 dp，$f_i$ 设在 $t_i$ 时刻到达第 $i$ 个点，能获得的最大收益。

转移：$f_i = f_j + a_i$，其中 $j$ 能转移到 $i$ 的充要条件有：

- $t_j \le t_i$
- $y_j \le y_i$
- $|x_i - x_j| + y_i - y_j \le t_i - t_j$

第三个条件表示从 $j$ 走到 $i$ 时间要足够。

拆第三个条件的绝对值，得：

- $x_i - x_j + y_i - y_j \le t_i - t_j$
- $x_j - x_i + y_i - y_j \le t_i - t_j$

移项，得：

- $t_j - x_j - y_j \le t_i - x_i - y_i$
- $t_j + x_j - y_j \le t_i + x_i - y_i$

这样你就得到了四个条件。乍一看好像是四维偏序！但是你发现若满足 $|x_i - x_j| + y_i - y_j \le t_i - t_j$，则一定满足 $t_i - t_j \ge 0$，因此可以省略一个条件。

接下来跑 cdq 优化 dp 即可。

[code](https://atcoder.jp/contests/abc266/submissions/35979406)

---

## 作者：MortisM (赞：1)

> [ABC266 Ex - Snuke Panic (2D)](https://atcoder.jp/contests/abc266/tasks/abc266_h)

挺好的一道题（不过调了好久QAQ

# 方法一

比较暴力的做法。

首先，你容易想到一个 DP 状态：$f(t,x,y)$ 表示在 $t$ 时刻到达 $(x,y)$ 的最大收益。

转移为：

$$
f(t,x,y)=\max\{f(t',x',y')|t'\leq t,y'\leq y,|x-x'|+y-y'\leq t-t'\}
$$

后面的限制意思就是说你必须要在这么多时间里能够走这么多路程，因为已经有 $t'\leq t,y'\leq y$，所以就不需要加绝对值了。

但是 $x$ 还留着绝对值，不好处理，所以向把这个绝对值拆开。

因为 $-|x-x'|\leq |x-x'|$，所以自然有 $-|x-x'|+y-y'\leq t-t'$。

这样就成功地把绝对值拆成了两个限制：
+ $x-x'+y-y'\leq t-t'$
+ $x'-x+y-y'\leq t-t'$

对它做一个变形（即移项使 $x,y,t$ 在一边，$x',y',t'$ 在一边），得到：
+ $t'-x'-y'\leq t-x-y$
+ $t'+x'-y'\leq t+x-y$

那么你按照 $y$ 对它排一下序，只用考虑满足上面两个性质地最大值，用二维树状数组做就行了。

时间复杂度 $O(n\log^2 n)$。

# 方法二

前面的转化还是跟上面一样的。

你按 $y$ 排完序以后可以考虑用 CDQ 分治来做。

现在考虑问题已经知道 $[l,mid]$ 的值，如何计算出 $[mid+1,r]$ 的值。

首先需要明确，因为已经按找 $y$ 排序过了，所以所有 $[l,mid]$ 的 $y$ 必然不大于 $[mid+1,r]$ 的 $y$。

也就是说，只需要考虑 $t'-x'-y'\leq t-x-y$ 和 $t'+x'-y'\leq t+x-y$ 的限制即可。

对于这两个限制，可以先对 $t-x-y$ 值排序，这样就只剩一个限制了，然后用树状数组就可以做了。

时间复杂度 $O(n\log^2 n)$，但是常数极小，比方法一不知道快多少倍。

**注意：需要添加一个点 $(0,0,0,0)$，并且在树状数组计算的时候需要将初值设为 $-\infty$，防止转移其他的。**

# 反思

第一个思路比较简单，只需要将转移和限制在纸上清晰地列下来就行。

方法二地 CDQ 分治比较巧妙，需要用到一些奇技淫巧。

方法一的 code：

```cpp
#include<bits/stdc++.h>
//#define JERRY_JIANG
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline int read() {
	int x = 0;
	bool f = 0;
	char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}
inline void print(int x) {
	if(x < 0) return putchar('-'), print(-x);
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}
inline int lowbit(int x) {return x & -x;}
bool Memst;
int n;
struct Data {
	int y, a, b, sz;
	bool operator < (const Data &x) const {
		if(y != x.y) return y < x.y;
		if(a != x.a) return a < x.a;
		if(b != x.b) return b < x.b;
		return sz < x.sz;
	}
};
vector<Data> datas;
vector<int> va, vb;
struct FenwickTree1D {
	int Mxn;
	unordered_map<int, ll> tree;
	FenwickTree1D() : Mxn(0){};
	FenwickTree1D(int n) : Mxn(n){};
	void update(int x, ll v) {
		while(x <= Mxn) {
			tree[x] = max(tree[x], v);
			x += lowbit(x);
		}
	}
	ll query(int x) {
		ll res = 0;
		while(x > 0) {
			res = max(res, tree[x]);
			x -= lowbit(x);
		}
		return res;
	}
};
struct FenwickTree2D {
	int Mxn, Mxm;
	vector<FenwickTree1D> tree;
	FenwickTree2D(int n, int m) : Mxn(n), Mxm(m), tree(n, FenwickTree1D(m)){};
	void update(int x, int y, ll v) {
		while(x <= Mxn) {
			tree[x].update(y, v);
			x += lowbit(x);
		}
	}
	ll query(int x, int y) {
		ll res = 0;
		while(x > 0) {
			res = max(res, tree[x].query(y));
			x -= lowbit(x);
		}
		return res;
	}
};
bool Memed;
int main(){
	fprintf(stderr, "%.3lf MB\n", (&Memst - &Memed) / 1048576.0);
	#ifdef JERRY_JIANG
		FILE *IN = freopen("input.in", "r", stdin);
		FILE *OUT = freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false); cin.tie(0);
	/* - input - */
	n = read();
	for(int i = 1; i <= n; i++) {
		int t = read(), x = read(), y = read(), sz = read();
		if(t - x - y >= 0 && t + x - y >= 0) {
			datas.push_back({y, t - x - y, t + x - y, sz});
			va.push_back(t - x - y); vb.push_back(t + x - y);
		}
	}
	double Timst = TIME;
	sort(datas.begin(), datas.end());
	sort(va.begin(), va.end());
	va.resize(unique(va.begin(), va.end()) - va.begin());
	sort(vb.begin(), vb.end());
	vb.resize(unique(vb.begin(), vb.end()) - vb.begin());
	FenwickTree2D T((int)va.size() + 1, (int)vb.size() + 1);
	ll ans = 0;
	for(int i = 0; i < (int)datas.size(); i++) {
		int y = datas[i].y, a = datas[i].a, b = datas[i].b, sz = datas[i].sz;
		a = lower_bound(va.begin(), va.end(), a) - va.begin() + 1;
		b = lower_bound(vb.begin(), vb.end(), b) - vb.begin() + 1;
		ll cur = T.query(a, b) + (ll)sz;
		ans = max(ans, cur);
		T.update(a, b, cur);
	}
	cout << ans << '\n';
	double Timed = TIME;
	fprintf(stderr, "%.3lf ms\n", Timed - Timst);
	return 0;
}
/*
author: Jerry_Jiang
start coding at 30/08/22 08:51
finish debugging at 30/08/22 09:53
*/
```

方法二的 code：

```cpp
#include<bits/stdc++.h>
//#define JERRY_JIANG
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline int read() {
	int x = 0;
	bool f = 0;
	char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}
inline void print(int x) {
	if(x < 0) return putchar('-'), print(-x);
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}
inline int lowbit(int x) {return x & -x;}
bool Memst;
constexpr int N = 1e5 + 10;
int n;
pair<pii, pii> a[N];
pair<pii, int> b[N];
ll tree[N], dp[N];
void update(int x, ll v) {
	while(x < N) {
		tree[x] = max(tree[x], v);
		x += lowbit(x);
	}
}
ll query(int x) {
	ll res = -0x3f3f3f3f3f3f3f3f;
	while(x > 0) {
		res = max(res, tree[x]);
		x -= lowbit(x);
	}
	return res;
}
void solve(int l, int r) {
	if(l == r) {
		dp[l] += (ll)a[l].se.se;
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	vector<int> v;
	int tot = 0;
	for(int i = l; i <= r; i++) {
		int p = a[i].fi.se - a[i].fi.fi - a[i].se.fi, q = a[i].fi.se - a[i].fi.fi + a[i].se.fi;
		b[++tot] = make_pair(make_pair(p, q), i);
		v.push_back(q);
	}
	sort(b + 1, b + tot + 1);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i = 1; i <= (int)v.size(); i++) tree[i] = -0x3f3f3f3f3f3f3f3f;
	for(int i = 1; i <= tot; i++) {
		int pos = lower_bound(v.begin(), v.end(), b[i].fi.se) - v.begin() + 1, id = b[i].se;
		if(id <= mid) update(pos, dp[id]);
		else dp[id] = max(dp[id], query(pos));
	}
	solve(mid + 1, r);
}
bool Memed;
int main(){
	fprintf(stderr, "%.3lf MB\n", (&Memst - &Memed) / 1048576.0);
	#ifdef JERRY_JIANG
		FILE *IN = freopen("input.in", "r", stdin);
		FILE *OUT = freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i].fi.se >> a[i].se.fi >> a[i].fi.fi >> a[i].se.se;
	sort(a + 1, a + n + 1);
	a[0].fi.fi = a[0].fi.se = a[0].se.fi = a[0].se.se = 0;
	memset(dp, -0x3f, sizeof(dp));
	dp[0] = 0;
	solve(0, n);
	ll ans = 0;
	for(int i = 1; i <= n; i++) ans = max(ans, dp[i]);
	cout << ans << endl;
	fprintf(stderr, "%.3lf ms\n", TIME);
	return 0;
}
/*
author: Jerry_Jiang
*/
```

---

