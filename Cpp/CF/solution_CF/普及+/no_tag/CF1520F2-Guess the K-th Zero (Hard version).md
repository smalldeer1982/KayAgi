# Guess the K-th Zero (Hard version)

## 题目描述

# Guess the K-th Zero (Hard version)


**提示: 这是一道交互题**.

数据加强力! 与简化版相比, 现在数据范围比较巨大, $ 1 \le t \le \min(n, 10^4) $ , 而且你的询问次数不得超过 $ 6 \cdot 10^4 $ .

苏苏正在打电动. 她玩的游戏里, 有某个长度固定的 $0,1$ 序列. 苏苏需要在接下来的 $t$ 次操作中猜对从左到右第 $k$ 个 $0$ 的位置.

## 样例 #1

### 输入

```
6 2

2

2

1

1

0

1

0```

### 输出

```
? 4 6

? 1 1

? 1 2

? 5 5

! 5

? 2 2

! 2```

# 题解

## 作者：meyi (赞：5)

记忆化二分+树状数组。

先考虑如何解决单组询问，我们用 $sum_i$ 表示 $1\sim i$ 的和，则可以通过询问 `? 1 i` 来得到 $sum_i$,若查询的数为 $k$，则答案为满足 $i-sum_i=k$ 的**最小的** $i$，可以二分得到答案。

类似地，若我们对多组询问的每组都使用上述方法，查询次数是 $O(t\log n)$ 的，需要优化，发现有多次重复查询一个点的 $sum$，于是我们对于每个点，只在第一次查询时输出询问，之后的查询直接使用已经得到的值即可。

但题目还有一个条件，要在每次回答询问后将答案对应位置的 `0` 改为 `1`，于是若我们回答了 $k$，则需要将 $[k+1,n]$ 的 $sum$ 都自增 `1`。这需要一个支持单点查询和区间修改的数据结构，我使用的是树状数组。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define DEBUG(k...) fprintf(stderr,k)
typedef long long ll;
template<class T>inline bool chmax(T &x,const T &y){return x<y?x=y,true:false;}
template<class T>inline bool chmin(T &x,const T &y){return x>y?x=y,true:false;}
const int maxn=2e5+10;
#define lowbit(k) ((k)&(-k))
template<typename T>
struct BIT{
	T c[maxn];
	int mx_idx;
	inline void clear(){memset(c,0,sizeof(T)*(mx_idx+1));}
	inline void add(int k,T v){
		for(;k<=mx_idx;k+=lowbit(k))c[k]+=v;
	}
	inline T query(int k){
		ri ret=0;
		for(;k;k^=lowbit(k))ret+=c[k];
		return ret;
	}
	inline T query(int l,int r){
		return query(r)-query(l-1);
	}
};
BIT<int>c;
bool vis[maxn];
int k,m,n,t_case;
inline void ask(int l,int r){
	printf("? %d %d\n",l,r);
	fflush(stdout);
}
inline void half(int l,int r,int k){
	if(l==r){
		printf("! %d\n",l);
		vis[l]=true;
		ri d=l-k-c.query(l);
		c.add(l,d+1);
		c.add(l+1,-d);
		fflush(stdout);
		return;
	}
	ri mid=l+r>>1,tmp;
	if(vis[mid])tmp=c.query(mid);
	else{
		ask(1,mid);
		scanf("%d",&tmp);
		vis[mid]=true;
		ri d=tmp-c.query(mid);
		c.add(mid,d);
		c.add(mid+1,-d);
	}
	if(tmp<=mid-k)half(l,mid,k);
	else half(mid+1,r,k);
}
int main(){
	scanf("%d%d",&n,&t_case);
	c.mx_idx=n;
	while(t_case--){
		scanf("%d",&k);
		half(1,n,k);
	}
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：3)

## 题解 CF1520F2 【Guess the K-th Zero (Hard version)】

### 题意

+ 给出一个长度为 $n$ 的 01 串，$t$ 次操作，每次找到从左到右数第 $k$ 个 0 并把它修改为 1。
+ 你可以询问交互库不超过 $6\times10^4$ 个问题，每个问题形如第 $l$ 个字符到第 $r$ 个字符中有多少个 1。
+ $n\le2\times10^5,t\le\min(n,10^4)$。

### 做法

平均每次操作不能超过 $\dfrac{6\times10^4}{t}=6$ 次询问。

可以用类似线段树上二分的做法，每次查询的时候保存一下节点的信息，修改的时候直接 $O(\log n)$ 修改。

然后发现每次操作需要的询问个数是 $\log_2n$，大约是 $18$ 个，远超平均的 $6$。

我们注意到每个节点最多被查询一次，因为被查询后我们时刻保持它的信息是正确的：

> 修改的时候直接 $O(\log n)$ 修改。

且每个节点的两个子树中，只有左子树会被查到（我们只需要左子树的值来判断答案在哪个子树内，右子树的值对我们没有价值），且在每次询问里，最多只会在线段树的每一层多询问一个节点。

综上，线段树的每一层最多只会被询问 $\min(t,\dfrac{size}{2})$ 次，$size$ 为该层线段树的节点个数，可列出下表（图丑勿怪）：

|层数|本层最多询问次数|本层及以上最多询问次数|本层节点数|
|:-|:-|:-|:-|
|$0$(root)|$0$|$0$|$1$|
|$1$|$1$|$1$|$2$|
|$2$|$2$|$3$|$4$|
|$3$|$4$|$7$|$8$|
|$4$|$8$|$2^4-1$|$16$|
|$\dots$|$\dots$|$\dots$|$\dots$|
|$13$|$2^{12}=4096$|$2^{13}-1$|$2^{13}$|
|$14$|$2^{13}=8192$|$2^{14}-1$|$2^{14}$|
|$15$|$10^4$|$10^4+2^{14}-1$|$2^{15}$|
|$16$|$10^4$|$2\times10^4+2^{14}-1$|$2^{16}$|
|$17$|$10^4$|$3\times10^4+2^{14}-1$|$2^{17}=131072$|
|$18$|$10^4$|$4\times10^4+2^{14}-1$|$2^{18}=262144$|

发现到了最后一层，最多也就 $56383$ 次询问，已经可以过，而且很难构造卡满的数据。

### 代码

```cpp
#include <cstdio>

using namespace std;

const int N = 2e5 + 5;

struct Tree {
	Tree *ls, *rs;
	int sum, vis;
	
	Tree() {
		vis = 0;
	}
} seg[N << 1], *leaf = seg;

void build(Tree *t, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	t->ls = ++leaf;
	t->rs = ++leaf;
	build(t->ls, l, mid);
	build(t->rs, mid + 1, r);
}

int q(int l, int r) {
	printf("? %d %d\n", l, r);
	fflush(stdout);
	int ans;
	scanf("%d", &ans);
	return ans;
}

int query(Tree *t, int l, int r, int k) {
	--t->sum;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (!t->ls->vis) {
		t->ls->vis = 1;
		t->ls->sum = mid - l + 1 - q(l, mid);
	}
	if (t->ls->sum >= k) return query(t->ls, l, mid, k);
	else return query(t->rs, mid + 1, r, k - t->ls->sum);
}

int main() {
	int n, t;
	scanf("%d%d", &n, &t);
	build(seg, 1, n);
	for (int i = 1; i <= t; ++i) {
		int k;
		scanf("%d", &k);
		printf("! %d\n", query(seg, 1, n, k));
		fflush(stdout);
	}
}
```

---

## 作者：Anita_Hailey (赞：2)

很有意思的一个题目，据说记忆化搜索的复杂度对的，但是我的做法不是那样。

这个东西很离谱。他要求交互次数不能大于 $6\times 10^4$，我们首先很显然的有一个二分的做法，可是这个的次数为$O(t\log n)$，无法通过这题

于是考虑我们先预处理出来二分的一部份值，然后每次只用在很小的范围内二分即可。

我们考虑对于所有坐标是 $8$ 的倍数的下标预处理出来他们的 $sum_{1,pos}$，然后，把 $n$ 变长到 $2$ 的幂次

每次直接二分即可，前一部分的二分的答案已经被预处理出来了，修改的部分可以用树状数组维护。小的部分直接查询答案就好了。

根据实现的方法不同可以做到 $O(t\log n)$ 或者是 $O(t\log ^2n)$ 的复杂度。

```cpp
#include <bits/stdc++.h>
const int N = 2e5 + 10;
int n, t, sc[N], val[N];
inline void add(int x) {
	for ( ; x <= n; x += x & -x) {
		sc[x]++;
	}
}
inline int sum(int x) {
	int res = 0;
	for ( ; x; x -= x & -x) {
		res += sc[x];
	}
	return res;
}
int main() {
	std::cin >> n >> t;
	std::function<void(int, int)> ask = [&] (int l, int r) {
		std::cout << "? " << l << " " << r << std::endl; 
	};
	std::function<bool(int, int)> check = [&] (int pos, int cnt) {
		if (pos >= n) {
			return true;
		}
		if (pos % 8 == 0) {
			return pos - val[pos] - sum(pos) >= cnt;
		}
		ask(1, pos);
		int res;
		std::cin >> res;
		return pos - res >= cnt;
	};
	int sz = 1;
	while (sz < n) {
		sz <<= 1;
	}
	for (int i = 1, k; i <= t; ++i) {
		std::cin >> k;
		if (i == 1) {
			for (int j = 8; j <= n; j += 8) {
				ask(1, j);
				std::cin >> val[j];
			}
		}
		int l = 1, r = sz;
		while (l < r) {
			int mid = (l + r) / 2;
			if (check(mid, k)) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		std::cout << "! " << r << std::endl;
		add(r);
	}
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)

题解区里怎么都用了高级数据结构啊，线段树二分这种算法并不是 div3 级别的吧。这里给出一种没有任何数据结构的简单做法，写起来很舒服。

首先，一个很直观的想法是每次询问直接二分第 $k$ 个 $0$ 的位置，这是非常简单的，但询问次数会达到 $t\log_2 n$，超过了最大询问次数，并不可行。

注意到一件事：由于每次查询之间，只改动了一个位置的数值，所以暴力二分的做法实际上进行了很多无用的查询。比如说，根据二分的思路，第一次查询，我们首先问了 $x=[1,n/2]$；第二次查询，我们又首先问了 $y=[1,n/2]$，而这第二次显然是不必要的，我们可以根据第一次查询时 $1$ 的位置和 $x$ 推出 $y$ 是 $x$ 还是 $x+1$。

于是，考虑将原序列每 $B$ 个分成一块，一共分成大约 $\text{cnt}=n/B$ 块。实时维护每块 $0$ 的个数 $c_i$。具体怎么操作呢？在所有询问的最初，我们暴力询问每块 $0$ 的个数；而每次查询过后，修改其中某一块 $0$ 的个数即可。

接下来，在查询时，我们先找出这个 $0$ 的所在块编号 $id$：从前往后扫描每一块，直到 $\sum_{i=1}^{id}c_i\geq k$，然后在编号为 $id$ 块中二分它的位置就可以了。这样一来，我们的询问次数就变成了 $n/B+t\log_{2}B$，取 $B=32$，这个次数不超过 $56250$。根据 $n$ 和 $t$ 的值确定最优的 $B$ 也可。

时间复杂度：$\mathcal{O}(t(n/B+\log B))$，稳过且好写。

[code](https://codeforces.com/contest/1520/submission/189204104)

---

## 作者：DaiRuiChen007 (赞：1)

# CF1520F2 题解



## 思路分析

简单版本是非常容易解决的，直接在原序列上进行二分，每次检查 $1\sim x$ 中 $0$ 的个数是否超过 $k$ 即可，询问次数 $\log_2 n$ 次。

接下来考虑困难版本，最显然的做法是复制容易版本 $t$ 次，每次直接对每次询问都进行二分，询问次数 $t\log_2n$ 次，超过了题目中的限制。

考虑优化，假设每次猜到 $x$ 后不会修改 $a_x$ 的值，那么我们可以进行记忆化，即对重复的询问直接返回答案。

而每次修改 $a_x$ 的值也可以类似解决，假设我们维护 $b_x$ 表示 $a_1\sim a_x$ 的和，那么每种操作对 $\{b_i\}$ 的贡献如下：

- 修改 $a_x$ 为 $1$，对于所有 $i\in[x,n]$，使 $b_i\gets b_i+1$。
- 询问 `? 1 x`  的答案为 $p$，使 $b_i\gets p$。

因此我们要维护 $\{b_i\}$ 支持单点查值，单点覆盖和区间加，显然用线段树或树状数组随便维护一下即可。

计算一下记忆化后的询问次数，我们可以把二分的过程转成在线段树上逐步向下的过程，那么询问次数就是在一棵动态开点线段树中插入 $t$ 个位置后，动态开点线段树的大小，因此答案为 $\sum_{i=0}^{\left\lceil\log_2n\right\rceil}\min(2^i,t)$，在 $n=2\times  10^5,t=10^4$ 时，询问次数为 $1+2+4+\cdots+8192+10^4+10^4+10^4+10^4=56383$ 次，可以通过本题。

时间复杂度 $\Theta(t\log^2 n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MAXN=2e5+1;
inline int read(int l,int r) {
	cout<<"? "<<l<<" "<<r<<endl;
	int ret; cin>>ret; return ret;
}
int n,T,k;
struct BitTree {
	int tree[MAXN];
	inline int lowbit(int x) { return x&-x; }
	inline void update(int x,int v) {
		for(;x<=n;x+=lowbit(x)) tree[x]+=v;
	}
	inline void Modify(int l,int r,int v) {
		update(l,v);
		if(r<n) update(r+1,-v);
	}
	inline int Query(int x) {
		int ret=0;
		for(;x;x-=lowbit(x)) ret+=tree[x];
		return ret;
	}
}	B;
bool vis[MAXN];
inline int query(int x) {
	if(vis[x]) return B.Query(x);
	vis[x]=true;
	int p=read(1,x);
	B.Modify(x,x,p-B.Query(x));
	return p;
}
inline bool check(int x) {
	return x-query(x)>=k;
}
signed main() {
	cin>>n>>T;
	while(T--) {
		cin>>k;
		int l=1,r=n,res=0;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(check(mid)) res=mid,r=mid-1;
			else l=mid+1;
		}
		B.Modify(res,n,1);
		cout<<"! "<<res<<endl;
	}
	return 0;
}
```



---

## 作者：cirnovsky (赞：1)

来个暴力点的。

首先 F1 的直接二分做 query 会吧？我们直接把同一个区间的询问 hash 一下存下来，然后加上每次 guess 后改变的值，这个可以直接用树状数组做。

然后就做完了，搜索树卡满也跑得过。

[code](https://paste.ubuntu.com/p/mShDDvh7DT/)

---

## 作者：KellyFrog (赞：1)

尽管听说有记忆化二分的做法，但说点常规点的。

一看这个限制次数和 $n$ 就很同阶，考虑分块，把连续 $w$ 个分一块，直接暴力查询所有块，询问就先在块的前缀和上二分，再块内二分，修改就维护块前缀和的树状数组。

这样的交互次数是 $\frac n w + t\cdot \lceil \log_2 w\rceil$，$w$ 取 $8$，交互次数最多 $55000$ 次，时间复杂度是 $O(n\log n + t\log^2 n)$，可以过。

另外需要特别注意二分的写法，一般的 `L<R` 的写法是 $\lceil \log_2 w\rceil$ 次 `check`，而 `L<=R` 的写法最多 $\lceil \log_2 w\rceil+1$ 次 `check`。~~搞了半天二分一直写丑了~~

```cpp

// Problem: F2. Guess the K-th Zero (Hard version)
// Contest: Codeforces - Codeforces Round #719 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1520/F2
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second

#if __cplusplus < 201703L
#define rg register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
};  // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
	cerr << s;
}
template <typename T1, typename... T2>
void debug(const char *s, const T1 x, T2... ls) {
	int p = 0;
	while (*(s + p) != '\0') {
		if (*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

#else
#define debug(...) void(0)
#endif

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

// const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

const int N = 2e5 + 5;
const int SIZ = 8;

int n, q;

int sum[N];
inline int lowbit(int x) {
	return x & (-x);
}
inline void add(int x, int val) {
	for(int x0 = x; x0 <= n; x0 += lowbit(x0)) sum[x0] += val;
}
inline int getsum(int x) {
	int res = 0;
	for(int x0 = x; x0 > 0; x0 -= lowbit(x0)) res += sum[x0];
	return res;
}

inline int ask(int L, int R) {
	L = max(L, 1);
	R = min(R, n);
	printf("? %d %d\n", L, R);
	fflush(stdout);
	int ret = 0;
	scanf("%d", &ret);
	return R - L + 1 - ret;
}

inline void answer(int p) {
	printf("! %d\n", p);
	fflush(stdout);
}

inline void solve(int k) {
	int L = 1, R = n / SIZ + 1;
	int res = -1;
	while(L <= R) {
		int mid = L + R >> 1;
		if(getsum(mid) >= k) {
			res = mid;
			R = mid - 1;
		} else {
			L = mid + 1;
		}
	}
	int p = (res - 1) * SIZ + 1;
	L = 1, R = SIZ;
	res = -1;
	while(L < R) {
		int mid = L + R >> 1;
		if(ask(1, p + mid - 1) >= k) {
			R = mid;
		} else {
			L = mid + 1;
		}
	}
	res = p + R - 1;
	answer(res);
	add((res - 1) / SIZ + 1, -1);
}

int main() {
	scanf("%d%d", &n, &q);
	int x;
	scanf("%d", &x);
	for(int i = 1; i <= n; i += SIZ) add(i / SIZ + 1, ask(i, i + SIZ - 1));
	solve(x);
	rep(i, 2, q) {
		scanf("%d", &x);
		solve(x);
	}
	return 0;
}

```

---

