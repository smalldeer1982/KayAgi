# New Year and Conference

## 题目描述

充满快乐的，Hyunuk将要举办一个关于将来的一年有多伟大的大会！

大会有 $n$ 个讲座。Hyunuk有两个可供选择的会场$a$和$b$。对于n个讲座中的每一个，演讲者选择了两个时间区间$[sa_{i},ea_{i}]$（$sa_{i}  \leq ea_{i}$）和$[sb_{i},eb_{i}]$（$sb_{i}  \leq eb_{i}$）。如果大会在a会场举办，那么讲座就会在$sa_{i}$到$ea_{i}$的时间举行；如果大会在b会场举行，那么该讲座就会在$sb_{i}$到$eb_{i}$的时间举行。Hyunuk只能选定两个会场中的一个，然后所有讲座都要在那个会场举行。

两个讲座被称为冲突，当且仅当它们共用了同一个时间点。正式地，我们称一个在区间$[x,y]$中举办的讲座和一个在$[u,v]$区间举办的讲座冲突，当且仅当$\max(x,u) \leq \min(y,v)$。

我们称一个听众可以参加所有讲座的一个子集$s$，当且仅当这个子集中任何一对讲座都不冲突。注意：是否能参加这个子集$s$的可能取决于Hyunuk选择的是$a$会场或是$b$会场来举办大会

对于一个子集$s$，若在一个会场，观众可以参加，而在另一个会场，观众却不可以参加，那么它被称为“会场敏感的”。

对于观众来说，是否存在一个会场敏感的子集$s$是一个重要的问题，因为观众无法确定讲座时间是否会冲突。Hyunuk会开心当且仅当不存在任意一个会场敏感的子集。请判断Hyunuk是否会开心

## 样例 #1

### 输入

```
2
1 2 3 6
3 4 7 8```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
1 3 2 4
4 5 6 7
3 4 5 5```

### 输出

```
NO```

## 样例 #3

### 输入

```
6
1 5 2 9
2 4 5 8
3 6 7 11
7 10 12 16
8 11 13 17
9 12 14 18```

### 输出

```
YES```

# 题解

## 作者：CYJian (赞：10)

这里是一个非常简单的做法。

---

一开始我们可以想到这样一点：如果不存在任何一对讲座在一个场地中冲突，另一场地不冲突，那么就不会存在一个子集的讲座不合法。反之则一定存在不合法的子集。相信大家都能意会。

然后我们发现这题只需要判断合法性，所以可以使用粗略的判断方法，比如哈希。

然后我们考虑给一个讲座随机一个很大的权值。然后对于每一个讲座，将其两个场地中与它时间无冲突的所有讲座的权值异或起来，如果权值为 $0$ 则说明这个讲座不会和其他讲座冲突。否则就会存在冲突。

乍一看感觉这个东西的正确率并不是很高，但是~~学长告诉我~~这个东西冲突的概率是 $\frac{1}{\text{值域大小}}$ 的。用 `unsigned long long` 理论上不会出问题。除非你是非酋中的非酋。

然后不难发现，我们要求的东西只需要按照端点位置排序之后，求一个 前缀 / 后缀 异或和就好了。加上排序的时间复杂度是 $O(n \log n)$ 的。码量和常数都吊打扫描线做法。在比赛的时候推荐使用这种可以秒过又没有码力要求的做法。

`Code` (头文件啥的请自行补充)

```cpp
typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 200010;

struct Node {
	int p, id, k;

	Node() {}
	Node(int p, int id, int k):p(p), id(id), k(k) {}

	friend bool operator < (Node a, Node b) { return a.p == b.p ? a.k < b.k : a.p < b.p; }
}a1[MAXN], a2[MAXN];

ull val[MAXN], S[MAXN];

int main() {
	srand(time(NULL));
	int n = read, N = 0;
	for(int i = 1; i <= n; i++) {
		val[i] = (ull)rand() << 31 | rand();
		a1[++N] = Node(read, i, 0);
		a1[++N] = Node(read, i, 1);
		N -= 2;
		a2[++N] = Node(read, i, 0);
		a2[++N] = Node(read, i, 1);
	}
	sort(a1 + 1, a1 + 1 + N);
	sort(a2 + 1, a2 + 1 + N);
	ull Xor = 0;
	for(int i = 1; i <= N; i++)
		if(a1[i].k) Xor ^= val[a1[i].id];
		else S[a1[i].id] ^= Xor;
	Xor = 0;
	for(int i = N; i >= 1; i--)
		if(!a1[i].k) Xor ^= val[a1[i].id];
		else S[a1[i].id] ^= Xor;
	Xor = 0;
	for(int i = 1; i <= N; i++)
		if(a2[i].k) Xor ^= val[a2[i].id];
		else S[a2[i].id] ^= Xor;
	Xor = 0;
	for(int i = N; i >= 1; i--)
		if(!a2[i].k) Xor ^= val[a2[i].id];
		else S[a2[i].id] ^= Xor;
	int flag = 0;
	for(int i = 1; i <= n; i++) flag |= S[i] > 0;
	if(flag) puts("NO");
	else puts("YES");
	return 0;
}
```

---

## 作者：苏联小渣 (赞：9)

这个题的题意有点迷惑，大概就是 $n$ 个二元组 $a_i=[l_i,r_i],b_i=[x_i,y_i]$，你需要判断是否有一个子集，使得这个子集中有两个 $a_i,a_j$ 相交且 $\forall b_i,b_j$ 互不相交；或者有两个 $b_i,b_j$ 相交且 $\forall a_i,a_j$ 互不相交。

首先两种情况等价，只需要把 $a,b$ swap 一下就好了。

然后子集很不好处理，考虑转化一下。显然可以发现，大小任意子集等价于大小为 $2$ 的子集，于是我们只需要判断是否有两个数 $i,j$ 满足 $a_i,a_j$ 相交且 $b_i,b_j$ 互不相交。

这个问题就很熟悉了。考虑离散化后将所有二元组按照 $l_i$ 从小到大排序，然后对于一个 $i$，我们要找到是否有 $j<i$ 且满足 $a_i,a_j$ 相交且 $b_i,b_j$ 不相交。由于排了序，那么一定有 $l_j \le l_i$，那么 $r_j \ge r_i$ 就是此时 $a_i,a_j$ 相交的条件了。而 $b_i,b_j$ 不相交，有两种情况：一种是 $x_j > y_i$，另一种是 $y_j<x_i$。所以，问题就转化成了：

- 查询满足 $r_j \ge r_i$ 中，$x_j$ 的最大值。如果最大值比 $y_i$ 大，那么就直接不合法；

- 查询满足 $r_j \ge r_i$ 中，$y_j$ 的最小值。如果最小值比 $x_i$ 小，那么直接不合法。

所以我们需要一个数据结构，支持单点修改，区间查询最大最小值。那么直接用线段树即可。实现的时候我脑抽写了两个线段树，事实上用一个即可。同时，这是个后缀 min/max 的形式，用树状数组也是可以的。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, N, flag;
struct node{
	int l, r, x, y;
	bool operator < (const node &A) const{
		if (l == A.l) return r < A.r;
		return l < A.l;
	}
}a[100010];
map <int, int> mp;
map <int, int> :: iterator it;
struct segment{
	#define lc(x) x<<1
	#define rc(x) x<<1|1
	int mx[1600010], mn[1600010];
	void clear(){
		for (int i=1; i<=(N<<2); i++){
			mx[i] = 0, mn[i] = 1e9;
		}
	}
	void pushup(int k){
		mx[k] = max(mx[lc(k)], mx[rc(k)]);
		mn[k] = min(mn[lc(k)], mn[rc(k)]);
	}
	void modify(int k, int l, int r, int x, int y){
		if (l == r){
			mx[k] = max(mx[k], y);
			mn[k] = min(mn[k], y);
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) modify(lc(k), l, mid, x, y);
		else modify(rc(k), mid+1, r, x, y);
		pushup(k);
	}
	int querymax(int k, int l, int r, int x, int y){
		if (x <= l && r <= y) return mx[k];
		int mid = l + r >> 1, ret = 0;
		if (x <= mid) ret = max(ret, querymax(lc(k), l, mid, x, y));
		if (y > mid) ret = max(ret, querymax(rc(k), mid+1, r, x, y));
		return ret;
	}
	int querymin(int k, int l, int r, int x, int y){
		if (x <= l && r <= y) return mn[k];
		int mid = l + r >> 1, ret = 1e9;
		if (x <= mid) ret = min(ret, querymin(lc(k), l, mid, x, y));
		if (y > mid) ret = min(ret, querymin(rc(k), mid+1, r, x, y));
		return ret;
	}
}S, T;
void work(){
	S.clear(); T.clear();
	for (int i=1; i<=n; i++){
		int rm = S.querymin(1, 1, N, a[i].l, N);
		int lm = T.querymax(1, 1, N, a[i].l, N);
		if (rm < a[i].x || lm > a[i].y) flag = 1;
		S.modify(1, 1, N, a[i].r, a[i].y);
		T.modify(1, 1, N, a[i].r, a[i].x);
	}
}
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		scanf ("%d%d%d%d", &a[i].l, &a[i].r, &a[i].x, &a[i].y);
		mp[a[i].l] = mp[a[i].r] = mp[a[i].x] = mp[a[i].y] = 1;
	}
	for (it=mp.begin(); it!=mp.end(); it++){
		it->second = ++N;
	}
	for (int i=1; i<=n; i++){
		a[i].l = mp[a[i].l], a[i].r = mp[a[i].r];
		a[i].x = mp[a[i].x], a[i].y = mp[a[i].y];
	}
	sort (a+1, a+n+1);
	work();
	for (int i=1; i<=n; i++){
		swap(a[i].l, a[i].x);
		swap(a[i].r, a[i].y);
	}
	sort(a+1, a+n+1);
	work();
	printf (flag ? "NO\n" : "YES\n");
	return 0;
}
```

---

## 作者：Kewth (赞：5)

来自 CF 赛时的智障做法。

只考虑一对演讲 A 区间相交 B 区间不相交的情况。

将所有演讲按 A 的左端点排序，维护扫描线，  
维护 A 区间跨过扫描线的所有演讲，然后对于 A 的左端点刚好在扫描线上的演讲 x ，  
其他 A 区间与其相交的演讲 y 有两种情况：

1. y 跨过了当前的扫描线
2. x 跨过了 y 的左端点

前者在现在被维护了，后者在枚举到 y 的时候 x 会被维护。

那么只需要将跨过扫描线的 B 区间维护起来，支持查找有多少区间与当前演讲 x 的 B 区间相交。

区间相交有 l, r 两个维度的限制，对应在二维平面上就是一个矩形，  
用二维线段树维护当前跨过扫描线的演讲的 B 区间在二维平面上的位置即可。

对于一对演讲 A 区间不相交而 B 区间相交的情况，把 A, B 区间交换再做一遍即可。

来自 CF 赛后听别人说的神仙做法。

还是只考虑一对演讲 A 区间相交 B 区间不相交的情况。

对于一个演讲 x ，如果能求出与它 A 区间相交的演讲集合 S 和 B 区间相交的演讲集合 T ，  
只需比较 S, T 是否相等就可以判断是否合法。

但是区间数很多，并不能状压在一个集合，注意到对于集合唯一需要的操作是比较两个集合是否相等。

一个经典套路是给每个演讲一个随机取值，然后一个集合 S 用其包含的演讲的异或和表示。

然后把坐标离散化后对于四个维度分别记前缀后缀异或和之类的就可以直接查询了。

排序 + 扫描线 + 二维线段树的参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
struct shit {
	int l1, r1, l2, r2;
};
shit shi[maxn];
int tmp[maxn << 1], tp;

int iseg[maxn * 600], lt[maxn * 600], rt[maxn * 600], ip;
int iquery(int now, int L, int R, int l) {
	if(R < l or !now) return 0;
	if(L >= l) return iseg[now];
	int M = (L + R) >> 1;
	return iquery(lt[now], L, M, l) + iquery(rt[now], M + 1, R, l);
}

void imodi(int &now, int L, int R, int p, int x) {
	if(!now) now = ++ ip;
	iseg[now] += x;
	if(L == R) return;
	int M = (L + R) >> 1;
	if(p <= M) imodi(lt[now], L, M, p, x);
	else imodi(rt[now], M + 1, R, p, x);
}

int seg[maxn << 3];
int query(int now, int L, int R, int r, int il) {
	if(L > r) return 0;
	if(R <= r) return iquery(seg[now], 1, tp, il);
	int M = (L + R) >> 1;
	return query(now << 1, L, M, r, il) + query(now << 1 | 1, M + 1, R, r, il);
}

void modi(int now, int L, int R, int p, int pp, int x) {
	/* if(now == 1) debug("%d %d %d\n", p, pp, x); */
	imodi(seg[now], 1, tp, pp, x);
	if(L == R) return;
	int M = (L + R) >> 1;
	if(p <= M) modi(now << 1, L, M, p, pp, x);
	else modi(now << 1 | 1, M + 1, R, p, pp, x);
}

std::vector<shit> stmp[maxn << 1];
bool solve(int n) {
	std::sort(shi + 1, shi + n + 1, [](shit x, shit y) { return x.l1 < y.l1; });

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("%d %d %d %d\n", shi[i].l1, shi[i].r1, shi[i].l2, shi[i].r2); */

	int be = 1, tot = 0;
	for(int i = 1; i <= n; i ++) {
		while(shi[i].l1 > be) {
			for(shit s : stmp[be]) {
				modi(1, 1, tp, s.l2, s.r2, -1);
				-- tot;
			}
			++ be;
		}
		int k = query(1, 1, tp, shi[i].r2, shi[i].l2);
		if(k != tot) return 1;
		stmp[shi[i].r1].push_back(shi[i]);
		modi(1, 1, tp, shi[i].l2, shi[i].r2, 1);
		++ tot;
	}

	for(int i = 1; i <= tp; i ++)
		stmp[i].clear();

	for(int i = 1; i <= tp; i ++)
		iseg[i] = lt[i] = rt[i] = 0;
	memset(seg, 0, sizeof seg);

	return 0;
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		read(shi[i].l1, shi[i].r1, shi[i].l2, shi[i].r2);

	tp = 0;
	for(int i = 1; i <= n; i ++) {
		tmp[++ tp] = shi[i].l1;
		tmp[++ tp] = shi[i].r1;
	}
	std::sort(tmp + 1, tmp + tp + 1);
	for(int i = 1; i <= n; i ++) {
		shi[i].l1 = int(std::lower_bound(tmp + 1, tmp + tp + 1, shi[i].l1) - tmp);
		shi[i].r1 = int(std::lower_bound(tmp + 1, tmp + tp + 1, shi[i].r1) - tmp);
	}

	tp = 0;
	for(int i = 1; i <= n; i ++) {
		tmp[++ tp] = shi[i].l2;
		tmp[++ tp] = shi[i].r2;
	}
	std::sort(tmp + 1, tmp + tp + 1);
	for(int i = 1; i <= n; i ++) {
		shi[i].l2 = int(std::lower_bound(tmp + 1, tmp + tp + 1, shi[i].l2) - tmp);
		shi[i].r2 = int(std::lower_bound(tmp + 1, tmp + tp + 1, shi[i].r2) - tmp);
	}

	if(solve(n)) return puts("NO"), 0;
	for(int i = 1; i <= n; i ++) {
		std::swap(shi[i].l1, shi[i].l2);
		std::swap(shi[i].r1, shi[i].r2);
	}
	if(solve(n)) puts("NO");
	else puts("YES");
	/* debug("%lf\n", (sizeof iseg) / 1024.0 / 1024.0 * 3); */
}
```

---

## 作者：Pengzt (赞：4)

[CF1284D](https://www.luogu.com.cn/problem/CF1284D)

发现直接找会比较麻烦，考虑转化。

发现对于第 $i$ 号区间，令 $S_a$ 表示在 $a$ 中与其无交的区间的集合，$S_b$ 表示在 $b$ 中与其无交的区间的集合。如果 $S_a$ 中的所有区间都与 $S_b$ 中所包含的区间不是一一对应的话，就肯定是输出 NO。

这时候就可以使用异或哈希了，如果对于区间 $i$，异或后为 $0$，则可近似的认为 $S_a$ 与 $S_b$ 相等，反之，就不相等。

时间复杂度：$\mathcal{O}(n \log n)$

说句闲话，这个人一开始 cmp 写挂了。

[评测记录](https://codeforces.com/contest/1284/submission/212910575)

---

## 作者：Yuby (赞：4)

[题面](https://www.luogu.com.cn/problem/CF1284D)

## 简要题意

可能不是很准确，但是可以辅助理解一下题意。

有 $n$ 对区间，每一个表达为 $[sa,ea],[sb,eb]$。定义两对区间“冲突”当且仅当两对区间中的两个区间分别相交或者都不相交，下面两种情况都不满足。

1. $[sa_i,ea_i]$ 与 $[sa_j,ea_j]$ 相交且 $[sb_i,eb_i]$ 与 $[sb_j,eb_j]$ 相交。
2. $[sa_i,ea_i]$ 与 $[sa_j,ea_j]$ 不相交且 $[sb_i,eb_i]$ 与 $[sb_j,eb_j]$ 不相交。

问是否不存在“冲突”的两对区间。

其中 $n\leq10^5$，$sa\leq~ea\leq10^9,sb\leq eb\leq10^9$。

## 分析

如果你读懂了题面的话，你会有一个朴素的暴力，即 $n^2$ 的算法，就是把所有的区间对挨个比配一遍。考虑在这个暴力算法的基础上优化。

考虑另一种方法。我们把不符合题意的拆分为满足区间 $a$ 不和其他重叠且$b$和其他有重叠，和区间 $b$ 不和其他重叠且 $a$ 和其他有重叠。两种情况变为了一种（另一种 swap 一下即可）。

### 免费补习STL

multiset 是一种插入删除查找为 $O(\log n)$ 的数据结构，默认会从小到大排序。可以理解为一个功能更多的 priority_queue 或者一个可以有重复元素的 set。

按照 $sa$ 和 $ea$ 进行升序排列，把每个区间 $[sb_i,eb_i]$ 的拆分为三元组 $(sa_i,[sb_i,eb_i],1)$ 和区间 $(ea_i,[sb_i,eb_i],0)$。我们把这个三元组的第一关键字成为时间。排序保证时间单调递增，枚举时保证当前所有在 multiset 中的区间都包含当前考虑的 $t$ 时间。维护一下当前情况下的 $b$ 就行了，就是用两个 multiset 维护一下 $sb$ 的最大值和 $eb$ 的最小值。

复杂度：$O(n\log n)$

核心代码和注释：

```cp
const ll MAXN=1e5+7;
ll n;
vector<ll>sa,ea,sb,eb;
struct node
{
	ll t,s,e,op;
	node(ll t_,ll s_,ll e_,ll op_):t(t_),s(s_),e(e_),op(op_){}
	bool operator<(const node& xx)const
	{
		return t==xx.t?op<xx.op:t<xx.t;
	}
};
bool check()
{
	multiset<ll>s,e;
	vector<node>a;
	for(ll i=0;i<n;i++)
	{
		a.push_back(node(sa[i],sb[i],eb[i],1));
		a.push_back(node(ea[i]+1,sb[i],eb[i],0));
	}
	sort(a.begin(),a.end());
	for(ll i=0;i<2*n;i++)
		if(a[i].op)//op方便维护是加入还是删除
		{
			if(s.size())
			{
				ll maxn=*(--s.end()),minn=*(e.begin());//multiset是从小到大的。
				if(maxn>a[i].e||minn<a[i].s)return 0;
			}
			s.insert(a[i].s),e.insert(a[i].e);//把当前时间的插入进去
		}
		else
			s.erase(s.find(a[i].s)),e.erase(e.find(a[i].e));//后面的会超过这个时间，不会对答案有贡献了，所以去掉。
	return 1;
}
int main()
{
	n=read();
	sa.resize(n),ea.resize(n),sb.resize(n),eb.resize(n);
	for(ll i=0;i<n;i++)
	{
		sa[i]=read(),ea[i]=read(),sb[i]=read(),eb[i]=read();
	}
	bool flag=check();
	swap(sa,sb);swap(ea,eb);//交换一下
	flag&=check();//两个都满足才对
	if(flag)puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：ademik (赞：3)

#### 分析：

线段树优化。

考虑到我们选择活动时，最少只需要选择两个，倘如我们选择更多的活动，如果此时冲突，那我们一定能分离出两个相冲突的活动。

这样，我们实际上是求是否存在两个活动，使其在一个会场冲突，另一个不冲突，暴力时间复杂度 $O(n^2)$。

我们考虑优化。我们先将活动分别按照 第一会场 和 第二会场经行时间排序，那么此时，一个活动可以被举行当且仅当它与之前的活动在两个会场之一没有冲突。

此时，问题就被转化为：

查询满足 $r_j \ge r_i$ 中，$x_j$ 的最大值。如果最大值比 $y_i$ 大，那么不合法。
查询满足 $r_j \ge r_i$ 中，$y_j$ 的最小值。如果最小值比 $x_i$ 小，那么不合法。

即在满足该活动在 一个会场有冲突 的条件下，查询它是否在另一个会场冲突。

故， 我们可以用线段树优化这个过程，以一个会场的活动举办时间为轴，维护另一个会场的活动举办时间，总时间复杂度为 $O(n \log n)$。

#### Code:

```cpp
using namespace std; 
typedef long long i64;
const int N = 1e5 + 50, Inf = 0x3f3f3f3f;
int n, idx, id[N << 2];
bool ok = true;
struct node {
	int x, y, s, t;
	bool operator <(const node &tmp) const {
		if(x == tmp.x) return y < tmp.y;
		else return x < tmp.x;
	}
} a[N];
struct Tree {  
	# define mid ((l + r) >> 1)
	# define lson (rt << 1)
	# define rson (rt << 1 | 1)
	int mx[N << 4], mn[N << 4];
	void Build(int l, int r, int rt) {
		mx[rt] = 0; mn[rt] = INT_MAX;
		if(l == r) {
			return;
		}
		Build(l, mid, lson); Build(mid + 1, r, rson);
		return;
	}
	void push_up(int rt) {
		mx[rt] = max(mx[lson], mx[rson]);
		mn[rt] = min(mn[lson], mn[rson]);
		return;
	}
	void change(int pos, int l, int r, int rt, int val) {
		if(l == r) {
			mx[rt] = max(val, mx[rt]);
			mn[rt] = min(val, mn[rt]);
			return;
		}
		if(pos <= mid) change(pos, l, mid, lson, val);
		else change(pos, mid + 1, r, rson, val);
		push_up(rt); return;
	} 
	int query_max(int x, int y, int l, int r, int rt) {
		if(x <= l && y >= r) return mx[rt];
		int res = 0;
		if(x <= mid) res = max(res, query_max(x, y, l, mid, lson));
		if(y > mid) res = max(res, query_max(x, y, mid + 1, r, rson));
		return res;
	} 
	int query_min(int x, int y, int l, int r, int rt) {
		if(x <= l && y >= r) return mn[rt];
		int res = INT_MAX;
		if(x <= mid) res = min(res, query_min(x, y, l, mid, lson));
		if(y > mid) res = min(res, query_min(x, y, mid + 1, r, rson));
		return res;
	} 
} T, S;
void work()
{
	S.Build(1, idx, 1); T.Build(1, idx, 1);
	for(int i = 1; i <= n; i ++) {
		int maxn = T.query_max(a[i].x, idx, 1, idx, 1);
		int minn = S.query_min(a[i].x, idx, 1, idx, 1);
		if(minn < a[i].s || maxn > a[i].t) ok = false;
		T.change(a[i].y, 1, idx, 1, a[i].s);
		S.change(a[i].y, 1, idx, 1, a[i].t);
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n;
	for (int i = 1; i <= n; i ++) {
		cin >>a[i].x >>a[i].y >>a[i].s >>a[i].t;
		id[++ idx] = a[i].x; id[++ idx] = a[i].s;
		id[++ idx] = a[i].y; id[++ idx] = a[i].t;
	}
	sort(id + 1, id + 1 + idx);
	idx = unique(id + 1, id + 1 + idx) - (id + 1);
	for (int i = 1; i <= n; i ++) {
		a[i].x = lower_bound(id + 1, id + 1 + idx, a[i].x) - id;
		a[i].y = lower_bound(id + 1, id + 1 + idx, a[i].y) - id;
		a[i].s = lower_bound(id + 1, id + 1 + idx, a[i].s) - id;
		a[i].t = lower_bound(id + 1, id + 1 + idx, a[i].t) - id;
	}
	sort (a + 1, a + 1 + n);
	work();
	for(int i = 1; i <= n; i ++) {
		swap(a[i].x, a[i].s);
		swap(a[i].y, a[i].t);
	}
	sort(a + 1, a + 1 + n);
	work();
	if(ok) cout <<"YES" <<endl;
	else cout <<"NO" <<endl;
	return 0;
} 
```



---

## 作者：Iveloid (赞：1)

限于水平,比赛时没看出这个和扫描线还有哈希有什么关系,用离线+线段树求解,步骤略微复杂但是很直观

将起始和结束看作数轴上的线段,将sa ea 放在x轴, sb eb放在y轴, 分别过sa ea作平行于y轴的直线, 过sb eb作平行于x轴的直线 可以得到一个矩形

对于第i个的sa,ea,eb,ed (四元组,以下简称 Q[i])的x0,y0,x1,y1 ,它们构成了n个矩形

本问题等价于求是否有 i,j(i<j) 使得Q[i],Q[j] 满足以下任一条件:

  为了叙述方便,称Q[x]的x0,y0 为Q[x]的x轴投影,Q[x]的x1,y1为Q[x]的y轴投影

*1.Q[i]的x轴投影与Q[j]的x轴投影有重合部分且 Q[i]与Q[j]的y轴投影无重合部分 ------(1--1)

*2.Q[i]的x轴投影与Q[j]的y轴投影有重合部分且 Q[i]与Q[j]的x轴投影无重合部分------(1--2)

我们先只单独计算(1--2)的情形是否存在
对于(1--1) 只需要将四元组Q[1~n]的(sa,ea,sb,ed)变成(sb,eb,sa,ea)再次按(1--2)的情形计算即可

我们对y轴,考虑使用下列的线段树表示是否有线段覆盖:
  
  1.支持区间[l,r]变成1,区间变成0
  
  2.支持求区间[l,r]区间和 是否大于0

我们暴力枚举n个四元组

对于q[i]的x轴投影,我们需要将所有 q[j](j!=i且q[j]与q[i]的x轴投影没有重叠) 的y轴投影在 初始全为0的线段树上区间更新为1         -----(3--1)

然后用线段树的qry操作看 l=q[i].x1 r=q[i].y1 , 区间[l,r]上 区间和是否大于0  ----(3--2)

暴力过程中只要(3--2) 成立一次,就是满足(1--2)的条件了

然而(3--1)是O(NlogN)的暴力,这是个O(N^2logN) 解法,需要用离线优化,不必每次重新建立线段树

然后就能求解了,离线实际操作不便叙述,请看代码


```cpp
    #include <bits/stdc++.h>
    using namespace std;
    #define int long long
    const int maxn=100000+5;
    int n,sa[maxn],ea[maxn],sb[maxn],eb[maxn];
    struct Qple{
      int x0,y0,x1,y1;
    }a[maxn],q[maxn];
    bool cmp0(const Qple &a,const Qple &b){return a.y0<b.y0;}
    bool cmp1(const Qple &a,const Qple &b){return a.x0<b.x0;}
     
    const int N=2e5+10;
    struct SeT{
      int l,r;
      int sum,add;
    #define ls (p<<1)
    #define rs (p<<1|1)
    #define mid ((t[p].l+t[p].r)>>1)
    }t[4*N];
    void build(int p,int l,int r){
      t[p].l=l,t[p].r=r;
      if(r==l) return t[p].sum=0,t[p].add=0,void();
      build(ls,l,mid);
      build(rs,mid+1,r);
      t[p].sum=t[ls].sum+t[rs].sum;
    }
    void spread(int p){
      if(!t[p].add) return;
      t[ls].add+=t[p].add;
      t[ls].sum+=(t[ls].r-t[ls].l+1)*t[p].add;
      t[rs].add+=t[p].add;
      t[rs].sum+=(t[rs].r-t[rs].l+1)*t[p].add;
      t[p].add=0;
    }
    void change(int p,int l,int r,int d){
      if(l<=t[p].l&&t[p].r<=r){
        t[p].sum+=(t[p].r-t[p].l+1)*d;
        t[p].add+=d;
        return;
      }
      spread(p);
      if(l<=mid) change(ls,l,r,d);
      if(r>=mid+1) change(rs,l,r,d);
      t[p].sum=t[ls].sum+t[rs].sum;
    }
    int qry(int p,int l,int r){
      if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
      spread(p);
      int res=0;
      if(l<=mid) res+=qry(ls,l,r);
      if(r>=mid+1) res+=qry(rs,l,r);
      return res;
    }
     
    bool solve(){
      vector<int>b;
      for(int i=1;i<=n;++i){
        b.push_back(sb[i]);
        b.push_back(eb[i]);
      }
      sort(b.begin(),b.end()), b.resize(distance(b.begin(),unique(b.begin(),b.end())));
      for(int i=1;i<=n;++i){
        a[i].x0=sa[i],a[i].y0=ea[i];
        a[i].x1=lower_bound(b.begin(),b.end(),sb[i])-b.begin()+1;
        a[i].y1=lower_bound(b.begin(),b.end(),eb[i])-b.begin()+1;
      }
      sort(a+1,a+n+1,cmp0);
      memcpy(q,a,sizeof a);
      sort(q+1,q+n+1,cmp1);
      int ptr=0;// pointer
      bool ans=true;
      //memset(t,0,sizeof t);
     
      build(1,1,2*n);
      for(int i=1;i<=n;++i){
        change(1,q[i].x1,q[i].y1,1);
      }
      for(int i=1;i<=n;++i){
        while(ptr+1<=n&&q[ptr+1].x0<=a[i].y0){
          ptr++;
          change(1,q[ptr].x1,q[ptr].y1,-1);
        }
        if(qry(1,a[i].x1,a[i].y1)>0){
          ans=false;
        }
      }
      return ans;
    }
     
    signed main(){
      ios::sync_with_stdio(false),cin.tie(0);
      cin>>n;
      bool ret=true;
      for(int i=1;i<=n;++i)
        cin>>sa[i]>>ea[i]>>sb[i]>>eb[i];
      if(solve()==false) ret=false;
      for(int i=1;i<=n;++i)
        swap(sa[i],sb[i]),swap(ea[i],eb[i]);
      if(solve()==false) ret=false;
      cout<<(ret?"YES":"NO")<<endl;
      return 0;
    }
```






---

## 作者：liuyz11 (赞：1)

# 题解 CF1284D 【New Year and Conference】

 [本场比赛的题解](https://www.cnblogs.com/nblyz2003/p/12151883.html)
题目大意：有n个人，每个人在a会场讲话开始时间为sai，结束时间为eai，在b会场开始时间为sbi，结束时间为ebi。是否存在一个集合中的人在a市场没有时间重叠在b市场有重叠或在b市场没有重叠在a市场有有重叠。设两个人开始结束时间分别为(u，v)和(x，y)，当max(x，u) <= min(y，v)时两人重叠。存在重叠时输出“NO”，否则输出“YES”~~（似乎有什么不对的地方）~~。

提前申明一下，这道题我自己代码一直过不了，但是群里有人按照我的解法过了……代码也差不多……

只WA了第10个点（~~加了个特判过了~~），现在对拍跑了2个半小时还没跑出一组错误数据……

我的解法甚是奇怪……

首先判断a会场不重叠b会场重叠的情况，发现我们对于每个人a会场只要判断左边不重叠的情况，右边的到时候会枚举到的。

对于i这个人，要是eaj < sai，那么这两个人就不会重叠。

所以我们以sai为关键字进行排序，二分查找可以找出所有与i不重叠的人。

但是对每个人找他左边的人的区间肯定要超时，因为左边的人一定是从1开始的一个区间，我们记录下对于每个人i所有的以i为最右边的不重叠的人pi,j。（即不存在一个人k使得eai < eak < sapi,j）

然后只需要判断b会场是否有重叠，也就是说对第i个人，所有他左边的不重叠人j的[sbj，ebj]这个区间是否和[sbi，ebi]有重合，变成了一个区间覆盖问题。

用线段树进行维护，将区间[sbi，ebi]更改为已覆盖，判断pi中是否有点的讲话区间中有已覆盖的点。

对于另一种情况b会场不重叠a会场重叠情况和这个相同。

放上我的WA掉的代码（仅供参考，对着打出锅了别怪我）：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 500005
#define MAXM 2000005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

struct node1{
	int l1, r1, l2, r2;
}a[MAXN];
struct node2{
	int l, r;
	bool flag, tag;
}tree[MAXM];
bool ans;
int num[MAXM];
vi ve1[MAXN], ve2[MAXN];

void pushup(int q){
	tree[q].flag = tree[q << 1].flag || tree[q << 1 | 1].flag;
}

void pushdown(int q){
	if(!tree[q].tag) return;
	tree[q << 1].flag = tree[q << 1].tag = 1;
	tree[q << 1 | 1].flag = tree[q << 1 | 1].tag = 1;
	tree[q].tag = 0;
}

void build(int q, int l, int r){
	tree[q].l = l;
	tree[q].r = r;
	tree[q].tag = 0;
	tree[q].flag = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(q << 1, l, mid);
	build(q << 1 | 1, mid + 1, r);
	pushup(q);
}

void update(int q, int l, int r){
	if(tree[q].l > r || tree[q].r < l) return;
	if(tree[q].l >= l && tree[q].r <= r){
		tree[q].flag = 1;
		tree[q].tag = 1;
		return;
	}
	pushdown(q);
	update(q << 1, l, r);
	update(q << 1 | 1, l, r);
	pushup(q);
}

void query(int q, int l, int r){
	if(tree[q].l > r || tree[q].r < l) return;
	if(tree[q].l >= l && tree[q].r <= r){
		ans = ans || tree[q].flag;
		return;
	}
	pushdown(q);
	query(q << 1, l, r);
	query(q << 1 | 1, l, r);
	pushup(q);
}

bool cmp1(node1 a, node1 b){
	return a.r1 < b.r1;
}

bool cmp2(node1 a, node1 b){
	return a.r2 < b.r2;
}

int main(){
	int n, m = 0;
	scanf("%d", &n);
	rep(i, 1, n){
		scanf("%d%d%d%d", &a[i].l1, &a[i].r1, &a[i].l2, &a[i].r2);
		num[++m] = a[i].l1;
		num[++m] = a[i].r1;
		num[++m] = a[i].l2;
		num[++m] = a[i].r2;
	}
	sort(num + 1, num + m + 1);
	rep(i, 1, n){
		a[i].l1 = lower_bound(num + 1, num + m + 1, a[i].l1) - num;
		a[i].r1 = lower_bound(num + 1, num + m + 1, a[i].r1) - num;
		a[i].l2 = lower_bound(num + 1, num + m + 1, a[i].l2) - num;
		a[i].r2 = lower_bound(num + 1, num + m + 1, a[i].r2) - num;
	}
	sort(a + 1, a + n + 1, cmp1);
	rep(i, 1, n){
		int l = 1, r = n, ans = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(a[mid].r1 < a[i].l1){
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		ve1[ans].pb(i);
	}
	build(1, 1, m);
	rep(i, 1, n){
		update(1, a[i].l2, a[i].r2);
		rep(j, 0, SZ(ve1[i]) - 1){
			int x = ve1[i][j];
			ans = 0;
			query(1, a[x].l2, a[x].r2);
			if(ans){
				puts("NO");
				return 0;
			}
		}
	}
	sort(a + 1, a + n + 1, cmp2);
	rep(i, 1, n){
		int l = 1, r = n, ans = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(a[mid].r2 < a[i].l2){
				ans = mid;
				l = mid + 1;
			}
			r = mid - 1;
		}
		ve2[ans].pb(i);
	}
	build(1, 1, m);
	rep(i, 1, n){
		update(1, a[i].l1, a[i].r1);
		rep(j, 0, SZ(ve2[i]) - 1){
			int x = ve2[i][j];
			ans = 0;
			query(1, a[x].l1, a[x].r1);
			if(ans){
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
    return 0;
}
```

---

## 作者：caidzh (赞：0)

emm...这题用$multiset$或者一个延迟删除的堆就可以解决吧。。。

首先我们转化一下：显然一个会场相交，一个会场不相交是两个讲座之间发生的事情，因此如果答案为$\text{NO}$，则一定存在两个讲座其满足在一个会场相交，一个会场不相交

因此显然就有一个$n^2$做法，暴力枚举讲座然后判断即可

接下来我们考虑如果我们固定了一个会场的线段相交，然后判断在另一个会场的对应线段是否相交就好了

我们仅仅考虑把一个讲座加入集合和从集合中删除的过程，所以固定会场相交可以用一个类似扫描线的方式来完成

怎么判断对应线段存在不相交情况？如果存在不相交的情况，那么肯定有一条线段的起点比一条线段的终点位置要大，因此我们用两个$multiset$分别保存当前固定相交的线段集合中的起点位置和终点位置，每次加入一条新线段的时候判断一下起点集合中的最大值是否比当前线段终点要大，终点集合中的最小值是否比当前线段起点要小就好了

代码乱写的：

```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=100010;
int n,cnt,flag;
struct Node{
	int is,pos,id;
	bool operator <(const Node x)const{return x.pos>pos;}
}A[maxn<<1];
int As[maxn],At[maxn],Bs[maxn],Bt[maxn];
multiset<int>S1,S2;//S1扔进结尾，S2扔进开头 
multiset<int>::iterator it;
void Delete(int x){
	it=S1.find(Bt[x]);S1.erase(it);
	it=S2.find(Bs[x]);S2.erase(it);
}
void Insert(int x){
	S1.insert(Bt[x]);S2.insert(Bs[x]);
}
void check(int x){
	if(S1.size()>0){if(*S1.begin()<Bs[x])flag=1;}
	it=S2.end();if(S2.size()>0){it--;if(*it>Bt[x])flag=1;}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++){
		As[i]=read();At[i]=read();
		A[++cnt].is=1;A[cnt].pos=As[i];A[cnt].id=i;
		A[++cnt].is=0;A[cnt].pos=At[i]+1;A[cnt].id=i;
		Bs[i]=read();Bt[i]=read();
	}sort(A+1,A+cnt+1);int pl=1,pre=1;
	while(pre<=cnt){
		pl=pre;while(pl<=cnt&&A[pl].pos==A[pl+1].pos)pl++;
		for(int i=pre;i<=pl;i++)if(!A[i].is)Delete(A[i].id);
		for(int i=pre;i<=pl;i++)if(A[i].is)Insert(A[i].id);
		for(int i=pre;i<=pl;i++)if(A[i].is)check(A[i].id);pre=pl+1;
	}cnt=0;pl=pre=1;
	for(int i=1;i<=n;i++){
		A[++cnt].is=1;A[cnt].pos=Bs[i];A[cnt].id=i;
		A[++cnt].is=0;A[cnt].pos=Bt[i]+1;A[cnt].id=i;
		swap(As[i],Bs[i]);swap(At[i],Bt[i]);
	}sort(A+1,A+cnt+1);
	while(pre<=cnt){
		pl=pre;while(pl<=cnt&&A[pl].pos==A[pl+1].pos)pl++;
		for(int i=pre;i<=pl;i++)if(!A[i].is)Delete(A[i].id);
		for(int i=pre;i<=pl;i++)if(A[i].is)Insert(A[i].id);
		for(int i=pre;i<=pl;i++)if(A[i].is)check(A[i].id);pre=pl+1;
	}
	if(flag)cout<<"NO";else cout<<"YES";return 0;
}
```


---

