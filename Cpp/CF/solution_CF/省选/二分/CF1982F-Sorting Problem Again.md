# Sorting Problem Again

## 题目描述

已知一个序列，给定 $q$ 次修改。对于初始序列和每次修改后的序列，你需要做到：

找到长度最小的连续的子串，使得如果这个子串按升序排序，整个序列也就满足单调不降。输出这个子串的起始位置 $l, r$；若此时序列已经满足单调不降，认为 $l, r$ 均为 $-1$。

注意，对这个子串的“升序排序”只是一个假想出的操作，并不会改变原序列。

## 说明/提示

对于第一个样例：

- 一开始，序列 $a$ 已经满足单调不降：$[2, 2, 3, 4, 5]$。
- 第一次修改后，序列 $a$ 长这样：$[\color{red}{2}, \color{red}{1}, \color{black}{3}, 4, 5]$。
- 第二次修改后，序列 $a$ 长这样：$[\color{red}{2}, \color{red}{1}, \color{red}{3}, \color{red}{1}, \color{black}{5}]$。
- 第三次修改后，序列 $a$ 长这样：$[1, 1, \color{red}{3}, \color{red}{1}, 5]$。

标红的部分即为题目所求。

## 样例 #1

### 输入

```
2
5
2 2 3 4 5
3
2 1
4 1
1 1
5
1 2 3 4 5
9
1 4
2 3
5 2
3 1
1 1
5 1
4 1
3 1
2 1```

### 输出

```
-1 -1
1 2
1 4
3 4
-1 -1
1 3
1 3
1 5
1 5
2 5
2 5
2 5
2 5
-1 -1```

# 题解

## 作者：Eraine (赞：5)

编号：CF1982F

tag：数据结构

难度：*2600

这里会提供三个做法。第一个做法是笔者在考场现想到的，但是由于实现难度有亿点大没实现出来。第二个做法是结合 jiangly 的 vp 视频想到的，但是时间复杂度较劣且实现不好被卡了。第三个做法是在第二个做法的基础上加以改进优化了时间复杂度最终得到正解。

### Sol 1

原题即维护一个序列 $a$ 支持单点修改，修改后询问序列排序后生成的序列 $b$ 与原序列的最长公共前缀和后缀。

最长公共前/后缀想到 Hash。只需要二分即可出结果。问题变为维护序列 $a$ 的区间 Hash 值以及序列 $b$ 的区间 Hash 值。

序列 $a$ Hash 值做法显然。序列 $b$ 即维护一个有序序列支持动态增删元素。权值线段树和平衡树都可以做。

常数过大，这种算法不能通过此题，仅供思路拓展。

$\Theta(n+q\log^2n)$。

### Sol 2

观察到最长公共前缀必然递增，所以只需在序列 $a$ 第一段上升区间内判断区间 $[1,i]$ 是否是公共前缀即可。二分也可以处理。没有必要 Hash，利用序列 $b$ 上升的性质，对于第一段上升序列，判断区间 $[1,i]$ 的最大值是否小于等于 $[i+1,n]$ 的最小值即可。若不小于，说明在区间 $[i+1,n]$ 内至少存在一个数的排名在 $i$ 之前。这里只需维护最大值和最小值即可。

至于找到第一段上升序列，只需要找到第一个下降位置即可，set 可以简单维护。

同样地这种做法若实现差还是会被卡。

$\Theta(n+q\log^2n)$。

### Sol 3

观察 Sol 2。发现瓶颈在二分。考虑如何将在线段树外的二分优化到线段树内的二分消掉一个 $\log$。

仅列出求 LCP 的方法，LCS 类似。

设第一段上升区间为 $A$。

对于原做法显然无法优化。观察每次二分是进行 $\max_{j\in[1,i]}a_j\le\min_{j\in(i,n]}a_j$ 的判断，由于这里的 $i$ 是在第一段上升区间上，那么序列非 $A$ 段的所有元素都在 $\min$ 里，也就是 $\min$ 的非 $A$ 部分是确定的。而 $\min$ 里的 $A$ 部分则一定能保证大于等于在 $\max$ 的部分。那么 $\min$ 的值也就唯一确定了。问题转换为求最长的区间 $[1,ans]$ 使得 $\max_{j\in[1,ans]}a_j\le\min_{j\notin A}a_j$。后者可以 $\Theta(\log n)$ 求得，而前者可以用线段树上二分求出。

$\Theta(n+q\log n)$。

[submission](https://codeforces.com/contest/1982/submission/267821152)

若有疑问和错误请指出，虚心接受您的意见。[为数不多的彩蛋](https://www.luogu.com.cn/article/xf1b94js)

upd:2024.6.28 增加了 Sol 3。

---

## 作者：xyz105 (赞：3)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.014 }\bold{CF1982F}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$


### 题目描述

给定一个长度为 $n$ 的数列 $A$，有 $q$ 次单点修改。

对于 初始序列 和 每次修改后的数列，你需要求出**长度最小**的连续的子串，使得**如果**这个子串按升序排序，整个数列就满足单调不降。（“按升序排序”是假设，而非在序列上的实际操作）

输出这个子串的 起始位置 $l$ 和 终止位置 $r$；若此时整个数列已经满足单调不降，那么认定 $l,r$ 均为 $-1$。

多测，$\sum n,\sum q\le 5\times 10^5$。


### 解题思路

首先考虑一个问题：要求出的这个连续的子串应该满足什么性质？

考虑画个二维图，将每个点 $(i,a_i)$ 标出来。于是有下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3uwzn7h3.png)

这样就满足了“对子串按升序排序，整个序列就单调不降”这个性质。

可以考虑一种贪心的做法，对数列 $A$ 求出 **最长单调不降前缀** 和 **最长单调不降后缀**，令这组 前缀 和 后缀 中间夹着的部分为所求子串，那么这个所求子串不就长度最小了吗？另外有单点修改操作，那用**线段树**去维护这种区间前后缀不正好合适吗？

显然这种贪心是错的。因为它可能并不满足以下两点：
  1. 子串左侧最后一个数 $\le$ 子串内部**最小值**。
  2. 子串内部**最大值** $\le$ 子串右侧第一个数。

对应到图上可能是这个样子（下图 $\text{Part A}$ 部分）：

![](https://cdn.luogu.com.cn/upload/image_hosting/efw3zgx9.png)

不过好消息是，咱们可以通过**调整法**求出正解。看看上图的 $\text{Part B}$ 部分是怎么演示的（其中 **粉色框框** 就是要求的最终子串，不妨**假设**框内已经排好了序，~~画这个图真的很累人~~）。

记粉框的初始左右边界的位置为 $l_0,r_0$。首先将粉框的左边界**向左扩**。向左扩到什么程度呢？满足“子串左侧最后一个数 $\le$ 子串内部最小值”这个性质。  
也就是说，设左扩之后的左边界的位置为 $l$，则 $l$ 是满足 $a_{l-1}\le \min \{ \min \limits_{l_0\le i\le r_0} a_i,\ a_{r_0+1} \} $ 的最大的数。这个步骤使用 `upper_bound` 即可求出。

注意：不等号右边还对 $a_{r_0+1}$ 取了 $\min$。这是因为之后粉框右边界要**向右扩**，会把 $a_{r_0+1}$ 扩进来，所以要求 $a_{l-1}\le a_{r_0+1}$。

发现 向右扩 跟 向左扩 同理。将粉框的右边界向右扩，直到满足“子串内部最大值 $\le$ 子串右侧第一个数”这个性质。  
也就是说，设右扩之后的右边界的位置为 $r$，则 $r$ 是满足 $\max \{ \max \limits_{l_0\le i\le r_0} a_i,\ a_{l_0-1} \} \le a_{r+1}$ 的最小的数。这个步骤也是使用 `upper_bound` 可以求出的。（令 $a2_i=-a_{n-i+1}$，那么在 $A2$ 序列上的左扩操作不就跟 $A$ 上右扩一样了吗？）

把前面的**线段树**搬过来，让它再支持区间 $\min/\max$ 查询，这道题就做完了，$O((n+q)\log n)$。

注意，初始的粉框可能不存在，特判以下两种情况（记 $A$ 的 最长单调不降前缀 长度为 $l2$，最长单调不降后缀 长度为 $r2$）：

1. $l2=r2=n$。此时输出 `-1 -1`。
2. $l2+r2=n$。令 $l_0=l2+1,r_0=l2$。这种情况下左扩时 $l$ 应该满足 $a_{l-1}\le a_{r_0+1}$，右扩同理。


### 参考代码

[Submission on Codeforces](https://codeforces.com/contest/1982/submission/290666630)。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 5e5 + 10;

int t2, n, a[MAXN], a2[MAXN], q;

#define left (u << 1)
#define right ((u << 1) | 1)

struct node{
	int mn, mx, llen, rlen;
}t[MAXN << 2];

inline void push_up(node &u, node &lch, node &rch, int l, int r)
{
	int mid = (l + r) >> 1;
	u.mx = max(lch.mx, rch.mx), u.mn = min(lch.mn, rch.mn);
	u.llen = lch.llen, u.rlen = rch.rlen;
	if (lch.llen == mid - l + 1 && a[mid] <= a[mid + 1])
		u.llen = lch.llen + rch.llen;
	if (rch.rlen == r - mid && a[mid] <= a[mid + 1])
		u.rlen = lch.rlen + rch.rlen;
}

inline void change(int u, int l, int r, int pos)
{
	if (l == r)
	{
		t[u].mn = t[u].mx = a[l], t[u].llen = t[u].rlen = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) change(left, l, mid, pos);
	else change(right, mid + 1, r, pos);
	push_up(t[u], t[left], t[right], l, r);
}

inline node query(int u, int l, int r, int ul, int ur)
{
	if (ul <= l && r <= ur) return t[u];
	int mid = (l + r) >> 1;
	if (ur <= mid) return query(left, l, mid, ul, ur);
	if (ul > mid) return query(right, mid + 1, r, ul, ur);
	node res, res1 = query(left, l, mid, ul, ur), res2 = query(right, mid + 1, r, ul, ur);
	push_up(res, res1, res2, l, r); return res;
}

inline pair<int, int> get_ans()
{
	int l2 = t[1].llen, r2 = t[1].rlen;
	if (l2 == n) return make_pair(-1, -1);
	
	if (l2 + r2 == n)
	{
		int res1 = upper_bound(a + 1, a + l2 + 1, a[n - r2 + 1]) - a;
		int res2 = upper_bound(a2 + 1, a2 + r2 + 1, -a[l2]) - a2;
		return make_pair(res1, n - res2 + 1);
	}
	
	auto u = query(1, 1, n, l2 + 1, n - r2);
	int i1 = u.mn, i2 = u.mx;
	
	i1 = min(i1, a[n - r2 + 1]);
	int res1 = upper_bound(a + 1, a + l2 + 1, i1) - a;
	if (res1 <= l2) i2 = max(i2, a[l2]);
	int res2 = upper_bound(a2 + 1, a2 + r2 + 1, -i2) - a2;
	return make_pair(res1, n - res2 + 1);
}

int main()
{
	scanf("%d", &t2);
	while (t2--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		for (int i = 1; i <= n; i++) a2[i] = -a[n - i + 1];
		for (int i = 1; i <= n; i++) change(1, 1, n, i);
		auto ans1 = get_ans(); printf("%d %d\n", ans1.first, ans1.second);
		
		scanf("%d", &q); int i1, i2;
		while (q--)
		{
			scanf("%d%d", &i1, &i2), a[i1] = i2, a2[n - i1 + 1] = -i2;
			change(1, 1, n, i1);
			auto ans = get_ans(); printf("%d %d\n", ans.first, ans.second);
		}
	}
	
	return 0;
}
```

---

## 作者：Z1qqurat (赞：3)

典中典之想到倒数第二步。

1. Observation: 把所有 $a_i>a_{i+1}$ 的位置拉出来，设这些位置中最小的为 $L$，最大的为 $R$，那么肯定要选出一个包含 $[L,R]$ 的操作区间 $[l,r]$，要不然那些不合法位置对 $(a_i,a_{i+1})$ 消不掉一点。

2. Analysis: 考虑怎样的操作区间 $[l,r]$ 是合法的。

   a. $[L,R]\subseteq[l,r]$。

   b. $a_{l-1}\le \min\limits_{i=l}^r a_i$。

   c. $\max\limits_{i=l}^r a_i\le a_{r+1}$。

3. Trick: $a_1\sim a_{L-1}$ 单调不降，$a_{R+1}\sim a_n$ 单调不降，将所有满足 $a_i>a_{i+1}$ 的 $(i,i+1)$ 都包含在 $[L,R]$ 里面，那么 $a_{L-1}\le a_L,a_R\le a_{R+1}$。初始 $l=L,r=R$，这样可以分析出性质：

   a. $\max\limits_{i=1}^{L-1} a_i = a_{L-1}\le a_L\le \max\limits_{i=L}^R a_i$，向左移动 $l$ 不会影响 $[l,r]$ 内最大值。

   b. 同理的，向右移动 $r$ 不会影响 $[l,r]$ 内最小值。

4. Analysis: 所以 $l,r$ 的选取是独立的，再根据 $a_1\sim a_{L-1},a_{R+1}\sim a_n$ 各自的单调性，可以通过二分找出最大的满足 $2.b$ 条件的 $l$，最小的满足 $2.c$ 条件的 $r$。

5. Code Design: 考虑这些东西怎么维护。

   a. 需要求出 $[L,R]$，用一个 `set` 存储所有满足 $a_i>a_{i+1}$ 的位置 $i$，从 `set` 中取出最小、最大的两个位置作为 $L,R$，注意这里取出来后 $R\gets R+1$，因为要把 $i+1$ 也涵括在 $[L,R]$ 内。（当时没想到这个导致没法做到 $4$ 里面的性质，倒数第二步了属于是）

   b. 维护区间极值并支持单点修改，普通线段树即可。

   c. 求出 $L,R$ 以及 $[L,R]$ 内极值后，二分求解 $l,r$。

时间复杂度 $\mathcal{O}(q\log n)$，实现上参考了 jiangly 的线段树模板，缺省源贺的神 ClHg2 的。

```cpp
#include <bits/stdc++.h>

#define FOR(i, l, r) for (int i = l; i <= (r); ++i)
#define ROF(i, l, r) for (int i = r; i >= (l); ++i)
#define rep(n) FOR(i, 1, n)
#define each(i, x) for (auto &i : x)

using ll = long long;
using db = double;
using str = std::string;

using std::cin;
using std::cout;

using pi = std::pair<int, int>;
#define mr std::make_pair
#define fi first
#define se second

#define ttt template <typename T
ttt > using V = std::vector<T>;
ttt, size_t n > using A = std::array<T, n>;

#define sz(x) int((x).size());
#define rsz resize
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r)] + 1
#define pb push_back
#define eb emplace_back

#define il inline

ttt > il bool ckmin(T &x, const T &y) {
   return y < x ? x = y, true : false;
}
ttt > il bool ckmax(T &x, const T &y) {
   return y > x ? x = y, true : false;
}

constexpr int N = 5e5 + 5;
constexpr int inf = 1.5e9;

struct Info {
   int mn, mx;
   Info(int _mn, int _mx) : mn(_mn), mx(_mx) {}
   friend Info operator+ (const Info &x, const Info &y) {
      return Info{std::min(x.mn, y.mn), std::max(x.mx, y.mx)};
   }
   friend void operator+= (Info &x, const Info &y) {
      x = x + y;
   }
   void apply(int v) { mn += v, mx += v; }
   void cover(int v) { mn = v, mx = v; }
};

A<int, N> a;
struct Sgt {
   int n;
   V<Info> t;
   Sgt(int _n) : n(_n), t(n << 2 | 1, {inf, -inf}) {}

   il int lc(int o) { return o << 1; }
   il int rc(int o) { return o << 1 | 1; }
   void pull(int o) { t[o] = t[lc(o)] + t[rc(o)]; }
   
   void build(int o, int l, int r) {
      if (l == r) return t[o].cover(a[l]), void();
      int mid = l + r >> 1;
      build(lc(o), l, mid), build(rc(o), mid + 1, r);
      pull(o);
   }
   void modify(int L, int v) {
      auto modify { [&] (auto modify, int o, int l, int r) {
         if (l == r) return t[o].cover(v);
         int mid = l + r >> 1;
         if (L <= mid) modify(modify, lc(o), l, mid);
         else modify(modify, rc(o), mid + 1, r);
         pull(o);
      }};
      return modify(modify, 1, 1, n);
   }
   Info query(int L, int R) {
      auto query { [&] (auto query, int o, int l, int r) {
         if (L <= l && r <= R) return t[o];
         int mid = l + r >> 1;
         Info x(inf, -inf);
         if (L <= mid) x += query(query, lc(o), l, mid);
         if (R > mid) x += query(query, rc(o), mid + 1, r);
         return x;
      }};
      return query(query, 1, 1, n);
   }
};

std::set<int> s;
void solve() {
   int n, q;
   cin >> n, a[0] = -inf, a[n + 1] = inf;
   s.clear();
   FOR(i, 1, n) {
      cin >> a[i];
      if (i > 1 && a[i - 1] > a[i]) s.insert(i - 1);
   }
   Sgt t(n); t.build(1, 1, n);

   auto query = [&] () {
      if (s.empty()) return cout << "-1 -1\n", void();
      int L = *begin(s), R = *prev(end(s));
      auto m = t.query(L, ++R);
      int l = 0, r = L + 1;
      while (l + 1 < r) {
         int mid = l + r >> 1;
         if (std::min(a[mid], m.mn) >= a[mid - 1]) l = mid;
         else r = mid;
      }
      ckmin(L, l);
      l = R - 1, r = n + 1;
      while (l + 1 < r) {
         int mid = l + r >> 1;
         if (std::max(a[mid], m.mx) <= a[mid + 1]) r = mid;
         else l = mid;
      }
      ckmax(R, r);
      cout << L << ' ' << R << "\n";
      return ;
   };
	
   query();
   cin >> q;
   FOR(i, 1, q) {
      int x, y; cin >> x >> y;
      if (a[x - 1] > a[x] && a[x - 1] <= y) s.erase(x - 1);
      if (a[x - 1] <= a[x] && a[x - 1] > y) s.insert(x - 1);
      if (a[x] > a[x + 1] && y <= a[x + 1]) s.erase(x);
      if (a[x] <= a[x + 1] && y > a[x + 1]) s.insert(x);
      a[x] = y, t.modify(x, y);
      query();
   }
   return ;
}

int main() {
   std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

   int tc; cin >> tc;
   while (tc--) solve();
   return 0;
}
```

---

## 作者：CCPSDCGK (赞：2)

怎么场上降智到连这题都不会，我真是菜得没边了。

首先选择的区间 $[l,r]$ 必定包含所有的 $(a_i,a_{i+1})$ 使得 $a_i>a_{i+1}$，否则数组不可能有序。

那么选择最紧的 $[l,r]$ 使得其包含所有的 $(a_i,a_{i+1})$ 使得 $a_i>a_{i+1}$ 就一定正确吗，并不是，例如 `4 2 3 4 5`，只存在 $a_1>a_2$，但是要使数组有序必须选择 $[1,3]$，这是因为如果 $\min\limits_{i=l}^r a_i<a_{l-1}$ 或 $\max\limits_{i=1}^r a_i>a_{r+1}$ 那只对 $[l,r]$ 排序还是不行的。

那么接下来就变成了一个纯纯的数据结构问题，给定一个序列 $a_1,a_2,\cdots,a_n$，$q$ 次查询，单点修改，修改完后给定 $[l,r]$ 求最小长度的区间 $[l',r']$，使得 $l'\le l\le r\le r'$ 且满足 $\min\limits_{i=l'}^{r'} a_i\ge a_{l'-1}$ 以及 $\max\limits_{i=1'}^{r'} a_i\le a_{r'+1}$。

哈哈，这可难不倒我，先动态维护关于 $a$ 的单调栈然后在栈上二分 $l'$，如果 $l'$ 能找到对应的 $r'$，那么随着 $l'$ 增大 $r'$ 单调不增，所以只需要线段树二分找到对应的 $r'$ 即可，时间复杂度：$O(n\log n+q\log^2n)$，~~代码长的跟史一样，能不能过先不提，在 2h 的 CF Round 上这根本就不可写。~~

我们是不是还落掉了什么性质，对于 $1\sim l-1$，一定满足 $a_i\le a_{i+1}$，$r\sim n-1$ 同理。

这也就意味着：

对于 $1\le i<l,a_i\le a_l\le \max\limits_{i=l}^r a_i$。

对于 $r\le i\le n-1,a_i\ge a_r\ge \min\limits_{i=l}^r a_i$

这也就意味着区间向左扩展只会对区间 $\min$ 造成影响，向右扩展也只会对区间 $\max$ 造成影响，两边的扩展是**完全独立**的。

但如果区间向左扩展会对区间 $\min$ 造成影响，那么左端点右移仍可以满足条件还可以做到更优，所以我们只需要把区间左边所有 $>\min\limits_{i=l}^r a_i$ 的数加进来即可，因为数组有序，直接二分即可，向右扩展同理。

找到区间 $[l,r]$ 也不是难事，set 随便维护一下即可。

时间复杂度：$O((n+q)\log n)$
```
int a[500005],minn[2000005],maxn[2000005];
void build(int x,int l,int r){
	if(l==r){
		minn[x]=maxn[x]=a[l];return ;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	minn[x]=min(minn[x<<1],minn[x<<1|1]);
	maxn[x]=max(maxn[x<<1],maxn[x<<1|1]);
}
void change(int x,int l,int r,int p){
	if(l==r){
		minn[x]=maxn[x]=a[p];return ;
	}
	int mid=l+r>>1;
	if(mid<p) change(x<<1|1,mid+1,r,p);else change(x<<1,l,mid,p);
	minn[x]=min(minn[x<<1],minn[x<<1|1]);
	maxn[x]=max(maxn[x<<1],maxn[x<<1|1]);
}
int getmin(int x,int l,int r,int l1,int r1){
	if(l<=l1&&r1<=r) return minn[x];
	int mid=l1+r1>>1,res=inf;
	if(l<=mid) res=getmin(x<<1,l,r,l1,mid);if(mid<r) res=min(res,getmin(x<<1|1,l,r,mid+1,r1));
	return res;
}
int getmax(int x,int l,int r,int l1,int r1){
	if(l<=l1&&r1<=r) return maxn[x];
	int mid=l1+r1>>1,res=-inf;
	if(l<=mid) res=getmax(x<<1,l,r,l1,mid);if(mid<r) res=max(res,getmax(x<<1|1,l,r,mid+1,r1));
	return res;
}
void solve(){
	set<int> s;
	int n;cin>>n;
	*a=-inf,a[n+1]=inf;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) if(a[i]>a[i+1]) s.emplace(i);
	build(1,1,n);
	if(s.empty()) cout<<-1<<' '<<-1<<endl;
	else{
		int l=*s.begin(),r=*--s.end();
		int minn=getmin(1,l,r,1,n),maxn=getmax(1,l,r,1,n);
		cout<<ub(a,a+l,minn)-a<<' '<<lb(a+r+1,a+n+2,maxn)-a-1<<endl;
	}
	int q;cin>>q;
	while(q--){
		int p;cin>>p,cin>>a[p],change(1,1,n,p);
		if(a[p-1]>a[p]) s.emplace(p-1);else s.erase(p-1);
		if(a[p]>a[p+1]) s.emplace(p);else s.erase(p);
		if(s.empty()) cout<<-1<<' '<<-1<<endl;
		else{
			int l=*s.begin(),r=*--s.end()+1;
			cout<<ub(a,a+l,getmin(1,l,r,1,n))-a<<' '<<lb(a+r+1,a+n+2,getmax(1,l,r,1,n))-a-1<<endl;
		}
	}
}
int main(){
	int t;cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

考虑一对合法的 $l,r$ 满足什么条件：

- $a_1$ 到 $a_{l-1}$ 递增。

- $a_{r+1}$ 到 $a_n$ 递增。

- $a_{l-1}\le\min\{a_l,a_{l+1},\cdots,a_r\},a_{r+1}\ge\max\{a_l,a_{l+1},\cdots,a_r\}$。

默认空序列递增，$a_0=0,a_n=\infty$。

对于前两个限制，我们显然可以在线段树上维护 $a_i$ 和 $a_{i-1}$ 的大小关系，然后线段树上二分得到初步的 $l,r$，同时也能判掉 `-1 -1` 的情况。注意得到的 $l$ 满足 $a_l<a_{l-1}$，所以此时显然不合法，令 $l\gets l-1$，同理可知 $r$ 保持不变，并且这样得到的 $[l,r]$ 一定不是空区间。

然后我们就满足了前两个限制了，考虑第三个限制。

在钦定 $l$ 的情况下，$r$ 往右移，因为是递增的，最小值不变；同理 $l$ 往左移最小值也不变，那么 $l,r$ 的移动是相互独立的。

那么我们可以先钦定 $r$，考虑二分 $l$，设当前得到的值是 $mid$，那么我们只需要判断 $\min\{a_{mid},\cdots,a_r\}$ 的大小关系，如果直接上线段树的话，时间复杂度会退化成 $O(n\log^2n)$，不是我们想要的。

注意到 $\min\{a_{mid},\cdots,a_r\}=\min\{\min\{a_{mid},\cdots,a_{l-1}\},\min\{a_l,\cdots,a_r\}\}$。同时因为 $a_{[1,l]}$ 是递增的，所以前面那一坨一定是 $\ge a_{mid-1}$ 的，所以我们就只需要判断 $\min\{a_l,\cdots,a_r\}$ 和 $a_{mid-1}$ 的大小关系了。

预处理出 $\min\{a_l,\cdots,a_r\}$ 然后二分就能找到真正的 $l$，$r$ 的求解过程同理。

---

## 作者：Petit_Souris (赞：1)

考虑一个区间 $[l,r]$ 合法的充要条件是什么：

- $[1,l-1]$ 有序；

- $[r+1,n]$ 有序；

- $\min \limits_{i=l}^{r}a_i\ge \max \limits_{i=1}^{l-1}a_i$；

- $\max \limits_{i=l}^{r}a_i\le \min \limits_{i=r+1}^{n}a_i$。

首先特判已经排序的情况。我们可以先找到最小的区间 $[pl,pr]$ 满足前两条限制（这样的最小区间是唯一的，包含所有 $a_i > a_{i+1}$ 的位置的区间），那么 $[pl,pr]\subseteq [l,r]$。

这时候显然有一些比较容易想到的启动复杂数据结构 trick 的 $\mathcal O(n\log^2 n)$ 做法，但是这还不够。

我们发现这样的区间带来了一个非常好的性质：因为两边都是有序的，所以实际上 $\min \limits_{i=l}^{r}a_i$ 在 $r=pr$ 时 $=\min(a_l,\min \limits_{i=pl}^{pr}a_i)$，$r>pr$ 时 $=\min(a_l,\min \limits_{i=pl}^{pr+1}a_i)$。这时候你惊奇地发现 $l,r$ 居然是独立的！因此我们只要分成 $l=pl,r=pr$ 和 $l\neq pl \bigwedge r\neq pr$ 三种情况分类讨论即可，用线段树维护最大最小值，每种情况直接做二分即可。时间复杂度 $\mathcal O(n\log n)$。

最近发现常常出现想了一个看起来能过的比较繁琐的做法就开始想做法细节、忽略其他做法的毛病，很多时候会漏掉很多性质，错过最优最简解。有必要提升一下自己的思考深度。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=5e5+9,INF=1e10;
ll T,n,a[N],Q,mx[N<<2],mn[N<<2];
void Pushup(ll x){
    mx[x]=max(mx[x<<1],mx[x<<1|1]);
    mn[x]=min(mn[x<<1],mn[x<<1|1]);
}
void Build(ll x,ll l,ll r){
    mx[x]=-INF,mn[x]=INF;
    if(l==r){
        mx[x]=mn[x]=a[l];
        return ;
    }
    ll mid=(l+r)>>1;
    Build(x<<1,l,mid);
    Build(x<<1|1,mid+1,r);
    Pushup(x);
}
void Upd(ll x,ll l,ll r,ll u,ll v){
    if(l>u||r<u)return ;
    if(l==r){
        mx[x]=mn[x]=v;
        return ;
    }
    ll mid=(l+r)>>1;
    Upd(x<<1,l,mid,u,v);
    Upd(x<<1|1,mid+1,r,u,v);
    Pushup(x);
}
ll Querymx(ll x,ll l,ll r,ll ql,ll qr){
    if(ql>qr)return -INF;
    if(ql<=l&&r<=qr)return mx[x];
    ll mid=(l+r)>>1;
    if(qr<=mid)return Querymx(x<<1,l,mid,ql,qr);
    if(ql>mid)return Querymx(x<<1|1,mid+1,r,ql,qr);
    return max(Querymx(x<<1,l,mid,ql,qr),Querymx(x<<1|1,mid+1,r,ql,qr));
}
ll Querymn(ll x,ll l,ll r,ll ql,ll qr){
    if(ql>qr)return INF;
    if(ql<=l&&r<=qr)return mn[x];
    ll mid=(l+r)>>1;
    if(qr<=mid)return Querymn(x<<1,l,mid,ql,qr);
    if(ql>mid)return Querymn(x<<1|1,mid+1,r,ql,qr);
    return min(Querymn(x<<1,l,mid,ql,qr),Querymn(x<<1|1,mid+1,r,ql,qr));
}
set<ll>S;
void Min(pii&a,pii b){
    if(a.second-a.first>b.second-b.first)a=b;
}
void calc(){
    if(!S.size())return puts("-1 -1"),void();
    ll pl=*S.begin(),pr=*S.rbegin()+1;
    pii ans={1,n};
    ll Mx=Querymx(1,1,n,pl,pr),Mn=Querymn(1,1,n,pl,pr);
    if(Querymx(1,1,n,1,pr)<=Querymn(1,1,n,pr+1,n)){
        ll l=2,r=pl,pos=1;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(mid==1||a[mid-1]<=Mn)pos=mid,l=mid+1;
            else r=mid-1;
        }
        Min(ans,{pos,pr});
    }
    if(Querymn(1,1,n,pl,n)>=Querymx(1,1,n,1,pl-1)){
        ll l=pr,r=n,pos=n;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(mid==n||a[mid+1]>=Mx)pos=mid,r=mid-1;
            else l=mid+1;
        }
        Min(ans,{pl,pos});
    }
    if(pl==1||pr==n){
        write(ans.first),putchar(' '),write(ans.second),putchar('\n');
        return ;
    }
    Mx=max(Mx,a[pr+1]);
    Mn=min(Mn,a[pl-1]);
    ll l=2,r=pl,posl=1,posr=n;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(mid==1||a[mid-1]<=Mn)posl=mid,l=mid+1;
        else r=mid-1;
    }
    l=pr,r=n;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(mid==n||a[mid+1]>=Mx)posr=mid,r=mid-1;
        else l=mid+1;
    }
    Min(ans,{posl,posr});
    write(ans.first),putchar(' '),write(ans.second),putchar('\n');
}
void solve(){
    n=read();
    S.clear();
    rep(i,1,n)a[i]=read();
    a[0]=a[n+1]=0;
    rep(i,1,n-1){
        if(a[i]>a[i+1])S.insert(i);
    }
    Build(1,1,n);
    Q=read();
    calc();
    while(Q--){
        ll x=read(),y=read();
        a[x]=y;
        Upd(1,1,n,x,y);
        if(x>1){
            if(a[x-1]<=a[x]){
                if(S.find(x-1)!=S.end())S.erase(x-1);
            }
            else S.insert(x-1);
        }
        if(x<n){
            if(a[x]<=a[x+1]){
                if(S.find(x)!=S.end())S.erase(x);
            }
            else S.insert(x);
        }
        calc();
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：yshpdyt (赞：1)

感谢 @Celtic 和 @Frot 的指正！

## 题意
一个序列，可以选择一个区间使该区间递增排序，在保证选择后整个序列单调不降的条件下，找到长度最短的合法区间。

多次不独立单点修改，在修改前和每次修改后返回答案。
## Sol
~~感觉放到 E 的位置比较合适。~~

尝试找到一个修改只用 $O(\log n)$ 的方法。

不妨差分一下。记录 $a_i<a_{i-1}$ 的所有 $i$，设找到的最小的 $i$ 为 $l$，最大的 $i$ 为 $r$。那么一定满足，$[1,l-1]$ 单调不降，$[l-1,r]$ 需要修改，$[r,n]$ 单调不降。

根据题意，排序后最大值在 $r$ 的位置，最小值在 $l-1$ 的位置，不妨设 $[l-1,r]$ 最小值最大值分别为 $x,y$。

我们还需要排完序后不存在以下情况：$a_{l-2}>x$，$a_{r+1}>y$。

所以分别向左找最靠右的小于等于 $x$ 的位置，向右找最靠左的大于等于 $y$ 的位置，扩展一下排序区间。

这是否会导致右边出现比 $x$ 还小的值导致左边扩展不充分？不会，右边最小值为 $a_{r+1}$，如果 $a_{r+1}<x\le a_r$，那 $r$ 明显应该扩大为 $r+1$。

左边同理，$a_{l-2}>y\ge a_{l-1}$ 不可能成立。

考虑修改，用 `set` 即可维护递减位置的最大最小值且支持随时加入删除，由于带有单点修改，使用线段树来维护区间最值。

时间复杂度 $O((n+q)\log n)$。

本题输入数据规模较大，请使用较快的读入方式，空间也较大，请不要使用 `long long`。

## Code
```cpp
#include<bits/stdc++.h>
#define ll int
#define N 500005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=2e9;
const double eps=1e-6;
namespace MYINPUT{
    const int S=(1<<20)+5;char B[S],*H=B,*T=B;
    inline char gc(){if(H==T) T=(H=B)+fread(B,1,S,stdin);return H==T?EOF:*H++;}
    inline ll fr(){ll x=0;bool fh=0;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-') fh=1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=gc();}return fh?-x:x;}
}using MYINPUT::fr;
ll n,a[N],m;
struct node{
    ll val,id;
    friend bool operator<(const node &a,const node &b){
        if(a.val==b.val)return a.id<b.id;
        return a.val<b.val;
    }
};
struct sgt{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    ll mx[N*4],mi[N*4];
    void build(ll p,ll l,ll r){
        if(l==r){
            mx[p]=mi[p]=a[l];
            return ;
        }
        build(ls,l,mid);
        build(rs,mid+1,r);
        mx[p]=max(mx[ls],mx[rs]);
        mi[p]=min(mi[ls],mi[rs]);
    }
    void upd(ll p,ll l,ll r,ll x,ll t){
        if(l==r){
            mx[p]=mi[p]=t;
            return ;
        }
        if(x<=mid)upd(ls,l,mid,x,t);
        if(x>mid)upd(rs,mid+1,r,x,t);
        mx[p]=max(mx[ls],mx[rs]);
        mi[p]=min(mi[ls],mi[rs]);
    }
    pair<ll,ll> qr(ll p,ll l,ll r,ll le,ll ri){
        if(le<=l&&ri>=r)return {mi[p],mx[p]};
        ll ans1=inf,ans2=-inf;
        if(le<=mid){
            auto t=qr(ls,l,mid,le,ri);
            ans1=min(ans1,t.fi);
            ans2=max(ans2,t.se);
        }
        if(ri>mid){
            auto t=qr(rs,mid+1,r,le,ri);
            ans1=min(ans1,t.fi);
            ans2=max(ans2,t.se);
        }
        return {ans1,ans2};
    }
    #undef mid;
}T;
set<node>q;
void solx(){
    if(q.empty()){
        cout<<-1<<" "<<-1<<endl;
        return;
    }
    ll le=(*q.begin()).val;
    ll ri=(*q.rbegin()).val;
    auto [x,y]=T.qr(1,1,n,le-1,ri);
    ll l=1,r=le-1;
    while(l<r){
        ll mid=(l+r)>>1;
        if(a[mid]>x)r=mid;
        else l=mid+1;
    }   
    le=l;
    
    l=ri,r=n;
    while(l<r){
        ll mid=(l+r+1)>>1;
        if(a[mid]<y)l=mid;
        else r=mid-1;
    }
    ri=r;

    cout<<le<<" "<<ri<<endl;
}
void sol(){
    q.clear();
    n=fr();
    a[0]=-inf;
    for(int i=1;i<=n;i++){
        a[i]=fr();
        if(a[i]<a[i-1])q.insert({i,a[i]});
    }
    T.build(1,1,n);
    m=fr();
    solx();
    while(m--){
        ll pos=fr();
        ll x=fr();
        if(a[pos]<a[pos-1])q.erase({pos,a[pos]});
        if(pos<n&&a[pos+1]<a[pos])q.erase({pos+1,a[pos+1]});
        a[pos]=x;
        T.upd(1,1,n,pos,x);
        if(a[pos]<a[pos-1])q.insert({pos,a[pos]});
        if(pos<n&&a[pos+1]<a[pos])q.insert({pos+1,a[pos+1]});
        solx();
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt=fr();
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：DerrickLo (赞：1)

下记 $\displaystyle{\operatorname{MIN}(l,r)=\min_{i=l}^{r}a_i}$，$\displaystyle{\operatorname{MAX}(l,r)=\max_{i=l}^{r}a_i}$。

考虑一对合法的 $(l,r)$ 满足什么条件。

- $a_1$ 到 $a_{l-1}$ 与 $a_{r+1}$ 到 $a_n$ 不降。

- $\operatorname{MIN}(l,r)\ge a_{l-1}$，$\operatorname{MAX}(l,r)\le a_{r+1}$。

那么我们对于每次询问，先通过线段树上二分 $\mathcal O(\log n)$ 地求出最长不降前缀的末尾 $x$ 和最长不降后缀的开头 $y$，那么必然有 $l\in [1,x]$，$r\in[y,n]$。注意这里 $l$ 不能等于 $x+1$，因为如果 $l$ 等于 $x+1$，那么 $\operatorname{MIN}(l,r)\le a_l< a_{l-1}$，与 $\operatorname{MIN}(l,r)\ge a_{l-1}$ 矛盾，同理这里 $r$ 也不能等于 $y-1$。

那么 $\operatorname{MIN}(l,r)\ge a_{l-1}$ 就相当于 $\min(\operatorname{MIN}(l,x),\operatorname{MIN}(x+1,y-1),\operatorname{MIN}(y,r))\ge a_{l-1}$，考虑到 $\operatorname{MIN}(l,x)\ge a_{l-1}$ 且 $\operatorname{MIN}(y,r)=a_y$，所以只需满足 $\min(\operatorname{MIN}(x+1,y-1),a_y)\ge a_{l-1}$ 即可。

然后我们发现左式是固定的！所以只需要二分就能得到 $l$ 的最大值，同理我们也可以二分得到 $r$ 的最小值。

时间复杂度 $\mathcal O((n+q)\log n)$。

[Submission Link](https://codeforces.com/contest/1982/submission/267511147)。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1982F)

**题目大意**

> 给定 $a_1\sim a_n$，$q$ 次操作单点修改，或查询长度最小的 $[l,r]$ 使得对 $a_l\sim a_r$ 排序后原序列有序。
>
> 数据范围：$n,q\le 5\times 10^5$。

**思路分析**

不妨假设 $a_i$ 是 $1\sim n$ 的排列，那么我们要求的就是最长的前缀 $a[1,l-1]$ 和最长的后缀 $a[r+1,n]$ 满足所有 $a_i=i$。

可以用线段树维护信息，维护区间左右端点值，最长的满足 $a_{i+1}-a_i=1$ 的前缀和后缀，信息合并是简单的。

如果 $a_i$ 不是排列，线段树维护比较困难，可以交换值域和下标，即把所有 $i$ 按 $a_i$ 排序得到 $p_1\sim p_n$（相等从小到大排序），然后在 $p_i$ 上统计和刚刚一样的问题。

用平衡树维护。

时间复杂度 $\mathcal O(n+q\log n)$，常数较大。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
namespace IO {
int ow,olim=(1<<23)-100;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23];
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
int read() {
	int x=0,f=1; char c=gc();
	while(!isdigit(c)) f=(c=='-'?-f:f),c=gc();
	while(isdigit(c)) x=x*10+(c^48),c=gc();
	return x*f;
}
void flush() {
	fwrite(obuf,ow,1,stdout),ow=0;
}
void write(int x) {
	if(!x) obuf[ow++]='0';
	else {
		int t=ow;
		for(;x;x/=10) obuf[ow++]=(x%10)^48;
		reverse(obuf+t,obuf+ow);
	}
	if(ow>=olim) flush();
}
void putc(char c) {
	obuf[ow++]=c;
	if(ow>=olim) flush();
}
void putstr(const string &s) {
	for(auto &c:s) obuf[ow++]=c;
	if(ow>=olim) flush();
}
#undef gc
}
mt19937 rnd(time(0));
int n,q,rt,a[MAXN];
struct Treap {
	struct Node {
		array<int,2> val;
		int pri,ls,rs,siz,lv,rv,lx,rx;
	}	tr[MAXN];
	inline void psu(int u) {
		const Node &x=tr[tr[u].ls],&y=tr[tr[u].rs];
		Node &t=tr[u];
		if(!t.ls&&!t.rs) {
			t.siz=1;
			t.lv=t.rv=u;
			t.lx=t.rx=1;
			return ;
		}
		if(!t.ls) {
			t.siz=1+y.siz;
			t.lv=u,t.rv=y.rv;
			if(y.lv==u+1) {
				t.lx=1+y.lx;
				t.rx=y.rx+(y.rx==y.siz);
			} else {
				t.lx=1;
				t.rx=y.rx;
			}
			return ;
		}
		if(!t.rs) {
			t.siz=x.siz+1;
			t.lv=x.lv,t.rv=u;
			if(x.rv==u-1) {
				t.lx=x.lx+(x.lx==x.siz);
				t.rx=1+x.rx;
			} else {
				t.lx=x.lx;
				t.rx=1;
			}
			return ;
		}
		t.siz=x.siz+1+y.siz;
		t.lv=x.lv,t.rv=y.rv;
		if(x.rv==u-1&&x.lx==x.siz) {
			if(y.lv==u+1) t.lx=x.siz+1+y.lx;
			else t.lx=x.siz+1;
		} else t.lx=x.lx;
		if(y.lv==u+1&&y.rx==y.siz) {
			if(x.rv==u-1) t.rx=y.siz+1+x.rx;
			else t.rx=y.siz+1;
		} else t.rx=y.rx;
	}
	inline void init(int u) {
		tr[u].val={a[u],u};
		tr[u].pri=rnd();
		tr[u].ls=tr[u].rs=0;
		tr[u].siz=1;
		tr[u].lv=tr[u].rv=u;
		tr[u].lx=tr[u].rx=1;
	}
	void split(int u,array<int,2>k,int &x,int &y) {
		if(!u) return x=y=0,void();
		if(k<tr[u].val) return y=u,split(tr[u].ls,k,x,tr[u].ls),psu(u);
		return x=u,split(tr[u].rs,k,tr[u].rs,y),psu(u);
	}
	int merge(int x,int y) {
		if(!x||!y) return x|y;
		if(tr[x].pri<tr[y].pri) return tr[x].rs=merge(tr[x].rs,y),psu(x),x;
		else return tr[y].ls=merge(x,tr[y].ls),psu(y),y;
	}
	void dfs(int u) {
		if(!u) return ;
		dfs(tr[u].ls),dfs(tr[u].rs),psu(u);
	}
	void build() {
		static int id[MAXN],stk[MAXN];
		for(int i=1;i<=n;++i) id[i]=i;
		sort(id+1,id+n+1,[&](int x,int y){ return tr[x].val<tr[y].val; });
		int tp=0;
		for(int o=1;o<=n;++o) {
			int i=id[o];
			while(tp&&tr[stk[tp]].pri>tr[i].pri) tr[i].ls=stk[tp--];
			if(tp) tr[stk[tp]].rs=i;
			stk[++tp]=i;
		}
		dfs(rt=stk[1]);
	}
}	T;
void ins(int i) {
	int x,y;
	T.split(rt,{a[i],i},x,y);
	rt=T.merge(x,T.merge(i,y));
}
void ers(int i) {
	int x,y,z,o;
	T.split(rt,{a[i],i},o,z);
	T.split(o,{a[i],i-1},x,y);
	rt=T.merge(x,z);
}
void qry() {
	auto o=T.tr[rt];
	if(o.lx==n) return IO::putstr("-1 -1\n");
	int l=(o.lv==1)?o.lx:0;
	int r=(o.rv==n)?o.rx:0;
	IO::write(l+1);
	IO::putc(' ');
	IO::write(n-r);
	IO::putc('\n');
}
void solve() {
	n=IO::read(),rt=0;
	for(int i=1;i<=n;++i) a[i]=IO::read(),T.init(i);
	T.build();
	q=IO::read(),qry();
	for(int p,v;q--;) {
		p=IO::read(),v=IO::read(),ers(p),a[p]=v,T.init(p),ins(p),qry();
	}
}
signed main() {
	ios::sync_with_stdio(false);
	int _=IO::read();
	while(_--) solve();
	IO::flush();
	return 0;
}
```

---

## 作者：Frodo (赞：0)

## 思路

假设答案为 $[l,r]$，当前最长不下降前缀长度为 $[1,pre]$，当前最长不下降后缀长度为 $[suf,n]$。

若 $pre=n$，则输出 ```-1 -1```。

因为对任意 $i\in[1,l)\cup[r,n)$，有 $a_i\leq a_{i+1}$。

则显然有 $l\in[1,pre]$ 和 $r\in[suf,n]$。

于是有 $[pre,suf]\subseteq[l,r]$。

那么有 $\min_{i=l}^r a_i \leq \min_{i=pre}^{suf} a_i$ 和 $\max_{i=pre}^{suf} a_i \leq \max_{i=l}^r a_i$。

因数列部分有序，则显然取等号时最优。

令 $mn=\min_{i=pre}^{suf} a_i,mx=\max_{i=pre}^{suf} a_i$。

因为要求 $a_{l-1}\leq mn,mx\leq a_{r+1}$。

则二分求出最小的 $i\in[1,pre]$ 满足 $a_i>mn$ 即为 $l$，求出最大的 $i\in[suf,n]$ 满足 $a_i<mx$ 即为 $r$。

用线段树维护区间最长不下降前缀长度，区间最长不下降后缀长度，区间最大值，区间最小值即可。

每组时间复杂度：$\Theta((n+q)\log n)$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=500100,inf=0x7fffffffffff;
int T,n,q,a[N],ID,W,L,R;
#define ls id<<1
#define rs id<<1|1
struct Tree{int minn,maxx,pre,suf;}tr[N<<2];
Tree operator+(Tree x,Tree y){return (Tree){min(x.minn,y.minn),max(x.maxx,y.maxx),0,0};}
void pushup(int id,int l,int r){
	tr[id].minn=min(tr[ls].minn,tr[rs].minn);
	tr[id].maxx=max(tr[ls].maxx,tr[rs].maxx);
	int mid=(l+r)>>1;
	if(tr[ls].pre==mid-l+1&&a[mid]<=a[mid+1]) tr[id].pre=mid-l+1+tr[rs].pre;
	else tr[id].pre=tr[ls].pre;
	if(tr[rs].suf==r-mid&&a[mid]<=a[mid+1]) tr[id].suf=tr[ls].suf+r-mid;
	else tr[id].suf=tr[rs].suf;
}
void build(int id,int l,int r){
	if(l==r){tr[id]=(Tree){a[l],a[l],1,1};return;}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(id,l,r);
}
void update(int id,int l,int r){
	if(l==r){tr[id]=(Tree){W,W,1,1};return;}
	int mid=(l+r)>>1;
	if(ID<=mid) update(ls,l,mid);
	else update(rs,mid+1,r);
	pushup(id,l,r);
}
Tree query(int id,int l,int r){
	if(L<=l&&r<=R) return tr[id];
	int mid=(l+r)>>1;Tree ret=(Tree){inf,-inf,0,0};
	if(L<=mid) ret=ret+query(ls,l,mid);
	if(mid<R) ret=ret+query(rs,mid+1,r);
	return ret;
}
#undef ls
#undef rs
void change(int id,int w){ID=id,W=w;update(1,1,n);}
Tree ask(int l,int r){L=l,R=r;return query(1,1,n);}
void count(){
	Tree x=tr[1];
	int l=x.pre,r=n+1-x.suf;
	if(l>=r){cout<<"-1 -1\n";return;}
	x=ask(l,r);
	int ansl=upper_bound(a+1,a+l+1,x.minn)-a,ansr=lower_bound(a+r,a+n+1,x.maxx)-a-1;
	cout<<ansl<<' '<<ansr<<'\n';
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);count();cin>>q;
	while(q--){
		int id,w;cin>>id>>w;
		a[id]=w;change(id,w);
		count();
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定长度为 $n$ 的序列，$q$ 次修改，对于初始序列和每次修改后求出：

长度最小的子段使得将该子段排序后整个序列单调不降，输出其左右端点。若序列原本已经有序则输出两个 $-1$。每次对子段的排序不会实际进行。
### 分析
显然我们需要求出当前序列的最长不降前缀长度 $x$ 和最长不降后缀长度 $y$，简单 sgt 维护即可，注意若 $x\geq n-y+1$ 则已经有序输出即可。

设答案为 $l$，$r$，则有 $l\leq x$ 且 $r\geq n-y+1 $，否则被排序子段之外的部分就不满足有序了。

然后 $[x+1,n-y]$ 这段区间必定需要排序，但排序后不一定合法，需要向两边扩展，使得排完序后选出的子段两端点与子段外的部分满足不降。求出 $[x,n-y+1]$ 的 $\min$ 和 $\max$，在最长不降前缀和最长不降后缀分别二分即可。

时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=5e5+5;
int T;
int n,q;
int a[maxn];
struct node{
	int mn,mx;
	int L,R;
	int len,pre,suf;
};
struct Segment_Tree{
	node tr[maxn*4];
	node pushup(node x,node y){
		node z;
		z.mn=min(x.mn,y.mn);
		z.mx=max(x.mx,y.mx);
		z.pre=(x.pre==x.len&&x.R<=y.L?x.len+y.pre:x.pre);
		z.suf=(y.suf==y.len&&x.R<=y.L?x.suf+y.len:y.suf);
		z.L=x.L,z.R=y.R,z.len=x.len+y.len;
		return z;
	}
	void build(int o,int l,int r){
		if(l==r){
			tr[o].L=tr[o].R=tr[o].mn=tr[o].mx=a[l];
			tr[o].len=tr[o].pre=tr[o].suf=1;
			return;
		}
		int m=(l+r)/2;
		build(o*2,l,m);
		build(o*2+1,m+1,r);
		tr[o]=pushup(tr[o*2],tr[o*2+1]);
	}
	void update(int o,int l,int r,int x,int k){
		if(l==r){
			tr[o].L=tr[o].R=tr[o].mn=tr[o].mx=k;
			return;
		}
		int m=(l+r)/2;
		if(x<=m) update(o*2,l,m,x,k);
		else update(o*2+1,m+1,r,x,k);
		tr[o]=pushup(tr[o*2],tr[o*2+1]);
	}
	pii query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return mkpr(tr[o].mn,tr[o].mx);
		int m=(l+r)/2;pii res=mkpr(inf,-inf);
		if(x<=m){
			pii t=query(o*2,l,m,x,y);
			res.fir=min(res.fir,t.fir),res.sec=max(res.sec,t.sec);
		}
		if(y>m){
			pii t=query(o*2+1,m+1,r,x,y);
			res.fir=min(res.fir,t.fir),res.sec=max(res.sec,t.sec);
		}
		return res;
	}
}seg;
void solve(){
	node S=seg.tr[1];
	int x=S.pre,y=n-S.suf+1;
	if(x>=y){
		puts("-1 -1");
		return;
	}
	pii mid=seg.query(1,1,n,x,y);
	int l=upper_bound(a+1,a+x+1,mid.fir)-a,r=lower_bound(a+y,a+n+1,mid.sec)-a-1;
	cout<<l<<" "<<r<<"\n";
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		seg.build(1,1,n);solve();
		q=read();
		while(q--){
			int x=read(),k=read();
			a[x]=k;
			seg.update(1,1,n,x,k);
			solve();
		}
	}
	return 0;
}
```

---

## 作者：Engulf (赞：0)

如果存在一个 $a_i > a_{i + 1}$，它将包含于我们的目标区间内，那么我们令 $l$ 为最小的 $i$，$r$ 为最大的 $i$ 再加上 $1$，似乎只要把 $[l, r]$ 排序就可以了？

其实这是不够的，设 $mn$ 是 $[l, r]$ 的最小值，$mx$ 是 $[l, r]$ 的最大值，如果 $[1, l)$ 存在一个数 $k > mn$，对 $[l, r]$ 排序后仍是非递增的，解决方法就是把所有这些 $k$ 都找出来，左移 $l$。而 $r$ 也一样，我们要在 $(r, n]$ 找到所有 $k' < mx$ 并右移 $r$。

发现 $a$ 在 $[1, l)$ 和 $(r, n]$ 都是单调不减的，我们可以通过二分找到最左的 $k$ 以及最右的 $k'$。

我们需要知道 $a_i > a_{i + 1}$ 的所有 $i$ 中的最小值与最大值，还需要修改，使用 set 维护。

我们需要查询区间最值，带上修改，使用线段树维护。

时间复杂度 $O(n + q \log n)$。代码实现起来很舒服。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 5e5 + 5;

int n;

int a[N];

int maxn[N << 2], minx[N << 2];
void build(int p, int l, int r) {
    if (l == r) {maxn[p] = minx[p] = a[l]; return;}
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    maxn[p] = max(maxn[p << 1], maxn[p << 1 | 1]);
    minx[p] = min(minx[p << 1], minx[p << 1 | 1]);
}
void modify(int p, int l, int r, int x, int v) {
    if (l == r) {maxn[p] = minx[p] = v; return;}
    int mid = l + r >> 1;
    x <= mid ? modify(p << 1, l, mid, x, v) : modify(p << 1 | 1, mid + 1, r, x, v);
    maxn[p] = max(maxn[p << 1], maxn[p << 1 | 1]);
    minx[p] = min(minx[p << 1], minx[p << 1 | 1]);
}
int queryMax(int p, int l, int r, int L, int R) {
    if (l > R || r < L) return -2e9;
    if (L <= l && r <= R) return maxn[p];
    int mid = l + r >> 1;
    return max(queryMax(p << 1, l, mid, L, R), queryMax(p << 1 | 1, mid + 1, r, L, R));
}
int queryMin(int p, int l, int r, int L, int R) {
    if (l > R || r < L) return 2e9;
    if (L <= l && r <= R) return minx[p];
    int mid = l + r >> 1;
    return min(queryMin(p << 1, l, mid, L, R), queryMin(p << 1 | 1, mid + 1, r, L, R));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        build(1, 1, n);

        set<int> st; // a[i] > a[i + 1]

        for (int i = 1; i < n; i++)
            if (a[i] > a[i + 1])
                st.insert(i);

        auto query = [&]() {
            int L, R;
            if (st.empty()) L = R = -1;
            else L = *st.begin(), R = *--st.end() + 1;
            // debug("original: [%d, %d]\n", L, R);
            int mn = queryMin(1, 1, n, L, R), mx = queryMax(1, 1, n, L, R);
            int l = 1, r = L - 1, res = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (a[mid] > mn) res = mid, r = mid - 1;
                else l = mid + 1;
            }
            if (res != -1) L = res;
            l = R + 1, r = n, res = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (a[mid] < mx) res = mid, l = mid + 1;
                else r = mid - 1;
            }
            if (res != -1) R = res;
            cout << L << " " << R << "\n";
        };

        query();

        int q;
        cin >> q;
        while (q--) {
            int p, v;
            cin >> p >> v;

            st.erase(p), st.erase(p - 1);

            a[p] = v;
            if (p < n && a[p] > a[p + 1])
                st.insert(p);
            if (p > 1 && a[p - 1] > a[p])
                st.insert(p - 1);

            // for (auto x: st) debug("a[%d] > a[%d]\n", x, x + 1);

            modify(1, 1, n, p, v);

            query();
        }
    }
    return 0;
}
```

---

## 作者：聪明的乖宝宝 (赞：0)

# 题目大意
给一个序列，你可以选择一个区间，将这个区间内的数字从小到大排序，问：如果将这个序列变成一个不降序列，那么需要选择的最小区间长度为多少？

另：序列将进行 $ q $ 次修改，问每次修改之后，答案是多少？
# 思路
## 如果不考虑修改
在不考虑修改的情况下，如果选择将一个区间 $ [l,r] $ 排列后，序列不降，则说明，这个区间前的序列不降，且这个区间前的序列中的元素小于等于其余所有元素，同理，这个区间后的序列也要求不降，且这个区间后的序列中所有元素大于等于区间前所有元素

那么问题就转化成了，找到一个最长前缀，满足这个前缀单调不降，且其中元素小于等于前缀外的元素。再找到一个最长后缀，满足这个后缀单调不降，且其中元素大于等于后缀外的所有元素

首先考虑如何找到一个最长的前缀，满足前缀中的元素单调不降。实际上，在不考虑修改的前提下，只需要暴力计算就可以了。那么现在考虑如何保证前缀中的元素满足小于等于前缀外的所有元素，现不妨假设整个序列的最长不降前缀为 $ [1,r] $ 那么如果我们找到 $ [r+1,n] $ 的最小值，我们会发现只需要求解出 $ [1,r] $ 中最后一个小于这个最小值的元素的位置就可以了，可以通过二分来求解，特别的当 $ r=n $ 时，整个序列不需要操作就满足题意，直接特判输出答案即可

对于后缀，同理
## 考虑修改
在考虑修改的情况下，在上述求解思路里，求 $ [r+1,n] $ 中的最大值，只需要借助一个可动态维护区间最值的数据结构即可，最容易想到的就是线段树

那么现在最后一个要考虑的问题就是，如何动态维护最长不降前（后）缀

我们可以考虑，把整个序列划分成尽可能少的不降区间，如： 

$$ 
1,2,3,1,5,3,7
$$
 
我们可以将其划分成三个不降区间

$$
1,2,3
$$

$$
1,5
$$

$$
3,7
$$

如果我们可以动态维护每一个元素所在区间的左右端点坐标，那么就很容易求解前缀了，因为前缀为 $ [1,k] $ 在这里 $ k $ 为第一个元素所在区间的右端点坐标

下面，分类讨论当我们改变一个点值的时候，对于区间划分的影响

对于区间划分的影响，实际上等价于对于元素所在区间的左右端点坐标的影响，不妨以修改了某一元素，对于其左边的元素所在区间端点坐标的影响为例，假设修改了元素 $ a_i $ 

1. 当 $ a_i{\geq}a_{i-1} $ 且 $ i $ 不是某一区间端点时时，没有任何影响。
2. 当 $ a_i{\geq}a_{i-1} $ 且 $ i $ 是某一区间端点时时，$ i-1 $ 所在区间与 $ i $ 所在区间将连接，即将 $ i $ 所在区间的左端点修改成 $ i-1 $ 所在区间的左端点，同时将 $ i-1 $ 所在区间的右端点修改成 $ i $ 所在区间的右端点 
3. 当 $ a_i<a_{i-1} $ 且 $ i $ 不是是某一区间端点时，那么区间在 $ i-1 $ 到 $ i $ 之间断开，被划分成两个区间，前一个区间中元素的右端点被修改成 $ i-1 $ 后一个区间中元素的左端点被修改成 $ i $ 
4. 当 $ a_i<a_{i-1} $ 且 $ i $ 是某一区间端点时，没有任何影响

按照上述思路，对于所修改元素右边部分的维护类似，同时，在具体实现中，需要考虑一些边界情况，这里不赘述

对于这个维护，只需要区间修改及元素查询，故也可以采用线段树维护

# 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int e;
int n;
const int N=500010;
struct SegTree
{
    int l,r;
    int lar,sma;
    int addl,adds,lk,sk;
    int maxk,mink;
}t[N*4];
int q;
int a[N];
int la[N],sa[N];
void Build(int p,int l,int r)
{
    t[p].l=l;
    t[p].r=r;
    t[p].addl=t[p].lk=0;
    t[p].adds=t[p].sk=0;
    if(l==r)
    {
        t[p].lar=la[l];
        t[p].sma=sa[l];
        t[p].mink=a[l];
        t[p].maxk=a[l];
        return;
    }
    int mid=(t[p].l+t[p].r)/2;
    Build(p*2,l,mid);
    Build(p*2+1,mid+1,r);
    t[p].mink=min(t[p*2].mink,t[p*2+1].mink);
    t[p].maxk=max(t[p*2].maxk,t[p*2+1].maxk);
}
void Spread(int p)
{
    if(t[p].addl)
    {
        t[p*2].lar=t[p].lk;
        t[p*2+1].lar=t[p].lk;
        t[p*2].lk=t[p].lk;
        t[p*2+1].lk=t[p].lk;
        t[p*2].addl=1;
        t[p*2+1].addl=1;
        t[p].addl=0;
    }
    if(t[p].adds)
    {
        t[p*2].sma=t[p].sk;
        t[p*2+1].sma=t[p].sk;
        t[p*2].sk=t[p].sk;
        t[p*2+1].sk=t[p].sk;
        t[p*2].adds=1;
        t[p*2+1].adds=1;
        t[p].adds=0;
    }
}
void Change(int p,int l,int r)
{
    if(t[p].l>=l&&t[p].r<=r)
    {
        t[p].lk=r;
        t[p].sk=l;
        t[p].addl=1;
        t[p].adds=1;
        t[p].lar=r;
        t[p].sma=l;
        return;
    }
    Spread(p);
    int mid=(t[p].l+t[p].r)/2;
    if(mid>=l)Change(p*2,l,r);
    if(mid<r)Change(p*2+1,l,r);
}
void Ask(int p,int k,int &l,int &r)
{
    if(t[p].l==t[p].r)
    {
        l=t[p].sma;
        r=t[p].lar;
        return;
    }
    Spread(p);
    int mid=(t[p].l+t[p].r)/2;
    if(mid>=k)Ask(p*2,k,l,r);
    else Ask(p*2+1,k,l,r);
}
void ycl()
{
    int p=1;
    for(int i=1;i<=n;i++)
    {
        if(a[i]>a[i+1]||i==n)
        {
            while(p<=i)
            {
                la[p]=i;
                p++;
            }
            p=i+1;
        }
    }
    p=n;
    for(int i=n;i>=1;i--)
    {
        if(a[i]<a[i-1]||i==1)
        {
            while(p>=i)
            {
                sa[p]=i;
                p--;
            }
            p=i-1;
        }
    }
}
void Changek(int p,int w,int k)
{
    if(t[p].l==t[p].r)
    {
        t[p].mink=k;
        t[p].maxk=k;
        return;
    }
    int mid=(t[p].l+t[p].r)/2;
    if(mid>=w)Changek(p*2,w,k);
    else Changek(p*2+1,w,k);
    t[p].mink=min(t[p*2].mink,t[p*2+1].mink);
    t[p].maxk=max(t[p*2].maxk,t[p*2+1].maxk);
}
int AskMax(int p,int l,int r)
{
    if(t[p].l>=l&&t[p].r<=r)
    {
        return t[p].maxk;
    }
    int ans=-1e9-1;
    int mid=(t[p].l+t[p].r)/2;
    if(mid>=l)ans=max(ans,AskMax(p*2,l,r));
    if(mid<r)ans=max(ans,AskMax(p*2+1,l,r));
    return ans;
}
int AskMin(int p,int l,int r)
{
    if(t[p].l>=l&&t[p].r<=r)
    {
        return t[p].mink;
    }
    int ans=1e9+1;
    int mid=(t[p].l+t[p].r)/2;
    if(mid>=l)ans=min(ans,AskMin(p*2,l,r));
    if(mid<r)ans=min(ans,AskMin(p*2+1,l,r));
    return ans;
}
int efl(int l,int r,int u)
{
    if(l==r)return l;
    int mid=(l+r)/2;
    if(a[mid]<=u)return efl(mid+1,r,u);
    else return efl(l,mid,u);
}
int efr(int l,int r,int u)
{
    if(l==r)return l;
    int mid=(l+r)/2;
    if(a[mid]>=u)return efr(l,mid,u);
    else return efr(mid+1,r,u);
}
void js()
{
    int l,r;
    Ask(1,1,l,r);
    if(r==n)
    {
        printf("-1 -1\n");
        return;
    }
    int ans1,ans2;
    int u=AskMin(1,r+1,n);
    if(a[r]<=u)ans1=r+1;
    else ans1=efl(1,r,u);
    Ask(1,n,l,r);
    u=AskMax(1,1,l-1);
    if(a[n]<u)ans2=n;
    else ans2=efr(l,n,u)-1;
    printf("%d %d\n",ans1,ans2);
}
int main()
{
    cin>>e;
    while(e--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
        }
        ycl();
        Build(1,1,n);
        scanf("%d",&q);
        js();
        while(q--)
        {
            int w,k;
            scanf("%d%d",&w,&k);
            a[w]=k;
            Changek(1,w,k);
            int l,r;
            Ask(1,w,l,r);
            int pl=0,pr=0;
            if(w==l)
            {
                if(w!=1)
                {
                    if(a[w-1]<=a[w])
                    {
                        pl=1;
                    }
                }
            }
            if(w==r)
            {
                if(w!=n)
                {
                    if(a[w+1]>=a[w])
                    {
                        pr=1;
                    }
                }
            }
            if(pl&&pr)
            {
                int l1,l2,r1,r2;
                Ask(1,w-1,l1,r1);
                Ask(1,w+1,l2,r2);
                Change(1,l1,r2);
            }
            else if(pl)
            {
                int l1,r1;
                Ask(1,w-1,l1,r1);
                Change(1,l1,r);
            }
            else if(pr)
            {
                int l2,r2;
                Ask(1,w+1,l2,r2);
                Change(1,l,r2);
            }
            Ask(1,w,l,r);
            if(l<w&&a[w-1]>a[w])
            {
                Change(1,l,w-1);
                Change(1,w,r);
            }
            else if(r>w&&a[w+1]<a[w])
            {
                Change(1,l,w);
                Change(1,w+1,r);
            }
            js();
        }
    }
    return 0;
}

```

---

