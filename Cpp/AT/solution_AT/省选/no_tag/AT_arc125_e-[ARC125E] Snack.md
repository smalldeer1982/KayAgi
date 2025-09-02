# [ARC125E] Snack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc125/tasks/arc125_e

$ 1 $ から $ N $ までの番号のついた $ N $ 種類のお菓子があります． お菓子 $ i $ は $ A_i $ 個あります．

$ 1 $ から $ M $ までの番号のついた $ M $ 人の子供がいます． この子供たちに，今からお菓子を配ります． ただし，お菓子を配る際には，次の条件を全て満たす必要があります．

- 子供 $ i $ は，どの種類のお菓子も $ B_i $ 個以下しかもらわない．
- 子供 $ i $ がもらうお菓子の個数の合計は $ C_i $ 以下である．

この条件のもとで，子どもたちに配るお菓子の個数の総和の最大値がいくらになるか求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^{12} $
- $ 1\ \leq\ B_i\ \leq\ 10^7 $
- $ 1\ \leq\ C_i\ \leq\ 10^{12} $
- 入力される値はすべて整数である

### Sample Explanation 1

次のようにお菓子を配ればよいです． - 子供 $ 1 $ は，お菓子 $ 1,2,3 $ をそれぞれ $ 1,1,1 $ 個もらう． - 子供 $ 2 $ は，お菓子 $ 1,2,3 $ をそれぞれ $ 0,2,1 $ 個もらう． - 子供 $ 3 $ は，お菓子 $ 1,2,3 $ をそれぞれ $ 1,2,2 $ 個もらう．

## 样例 #1

### 输入

```
3 3
2 5 5
1 2 2
5 3 5```

### 输出

```
11```

## 样例 #2

### 输入

```
10 6
3 54 62 64 25 89 1 47 77 4
1 17 10 29 95 17
32 40 90 27 50 9```

### 输出

```
211```

# 题解

## 作者：ZillionX (赞：7)

# Description

有 $n$ 种零食，第 $i$ 种零食有 $a_i$ 个。有 $m$ 个小孩，需要把零食分给小孩们，其中第 $i$ 个小孩任一零食只能拿 $\le b_i$ 个，总共只能拿 $\le c_i$ 个。问最多能分出的零食。

$n,m \le 2 \times 10^5,V \le 10^{12}$，时限 2s。

# Solution

这些 $\le x$ 的限制看起来就很线性规划，我们考虑网络流建模。

我们从源点向每个零食连流量为 $a_i$ 的边，每个零食向每个小孩连对应的流量为 $b_i$ 的边，所有小孩向汇点连流量为 $c_i$ 的边。

网络流求解类二分图匹配可以做到 $\mathcal O(m \sqrt n)$，因为 $m$ 太大了，所以显然不可行。

观察到中间有很多冗余边，我们考虑用精妙的方法求出这个特殊问题的最小割。

我们考虑如果零食已经被钦定好了连 $S$ 还是连 $T$，则对于每个小孩，连 $S$ 的代价为 $c_i$，连 $T$ 的代价为 $x b_i$，其中 $x$ 为连 $S$ 的零食数量。

既然小孩的代价只和 $x$ 有关，那么我们直接枚举 $x$ 就好了。肯定是把最小的 $n-x$ 个零食割掉。然后小孩的贡献就是 $\min (c_i,x b_i)$，这个可以按 $\dfrac{c_i}{b_i}$ 排序后双指针维护。

时间复杂度线性对数。

# Code

```cpp
const int N=2e5+5;
int n,m,a[N];
struct dat {
	int b,c;
	bool operator<(const dat &r) const {
		return c*r.b>r.c*b;
	}
}v[N];
signed main() {
	scanf("%lld%lld",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (int i=1;i<=m;i++) scanf("%lld",&v[i].b);
	int sa=0,sb=0,sc=0,ans=LLONG_MAX;
	for (int i=1;i<=m;i++) scanf("%lld",&v[i].c),sc+=v[i].c;
	sort(v+1,v+m+1);
	sort(a+1,a+n+1);
	for (int i=n,j=1;i>=0;i--) {
		sa+=a[n-i];
		for (;j<=m && v[j].b*i<=v[j].c;j++) sb+=v[j].b,sc-=v[j].c;
		ans=min(ans,sa+sb*i+sc);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Rosabel (赞：3)

太帅了这题。加深了我对网络流的理解。

先建完图，图为四层，分别为源点，$n$ 种零食，$m$ 个孩子，汇点。第一、二层连边为 $a_i$，第二、三层连边为 $b_j$，第三、四层连边为 $c_j$。

现在要做的是对这张图求最大流。由于最大流=最小割（最大流最小割定理），所以将其转为最小割。

一个很重要的观察是第二层每个点除了 $a_i$ 不同以外没有本质区别，所以一旦确定了第二层归属集合 $T$ 的个数 $S$，便能找到第一、二层的贡献，即 $a_i$ 升序排序前 $x$ 小值之和。

接下来就是第二、三层和第三、四层的贡献了，发现对于每一个第三层的点 $j$，其贡献是 $\min(c_j,b_j(n-x))$。转成关于 $x$ 函数就是一个分段函数，第一段水平，第二段是值域为 $[0,c_i]$ 的下降直线。转折点很容易通过二分求得。

那么问题即变成定义域在 $[0,n]$ 上的 $m$ 个分段函数求和。维护转折点即可。别忘记加上 $\sum a_i$。

瓶颈在于二分和排序。$\Theta(n\log n)$。

[code](https://atcoder.jp/contests/arc125/submissions/58879539)

给珂爱的小妹妹点个赞再走吧 qwq

---

## 作者：bryce (赞：3)

## 思路分析
看到这道题，很容易想到最大流，建边也很好想，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/3fkto7z3.png)

但是，建这么多的边会有问题，就是时间复杂度太高，跑不了网络流，所以我们换一种思路。

有一个重要的结论就是：**最大流 $=$ 最小割**。

证明可以看[这里](https://oi-wiki.org/graph/flow/max-flow/)，这里不证明了。

于是题目就转化为了对于上面这张图求最小割。

我们发现，我们要割掉左边一些零食点集与 $s$ 的连边，同理割掉右边一些人的点集与 $t$ 的边，再割掉中间某些 $b_i$ 的边。

我们可以将这个过程看成删掉左右两边某些点，再删掉中间的某些边，有一个非常妙的性质就是，删掉左右两边的某些点后，必须将没删掉的那些点之间的所有连边全部删除才能保证图不联通，因为对于每一个零食，都对每个人连了边。

设左边零食删去的点集为 $A$，右边人删去的点集为 $c$，那么答案就为下面式子的最小值：
$$\sum_{i\in A} a_i + \sum_{i\in C} c_i+ \sum_{i\notin C} b_i(n-|A|)$$
$|A|$ 表示 $A$ 集合的大小。

进一步地，我们将式子后面的两坨改一下，变为求下面式子的最小值：
$$\sum_{i\in A} a_i + \sum\limits_{i=1}^{m} \min(b_i(n - |A|), c_i)$$
让我们感性理解一下，左边为删掉某些零食点集的贡献，右边为选枚举人的点集中的所有点，要么删掉这个人，要么删掉左边剩余零食点集与这个人的所有 $b_i$ 的边，由于要求最小割，所以取两者中的最小值保证图不联通。

于是题目就变为快速求上面这个式子。

首先我们枚举 $A$ 集合的大小，在当前大小下，肯定选择的点是 $s$ 与之连边 $a_i$ 最小的几个，于是先对 $a_i$ 排序。

如何快速求式子右边那一坨，将 $\frac{c_i}{b_i}$ 求出来，设 $x_i = \frac{c_i}{b_i}$，这样当 $n-|A|=x_i$ 时，$b_i(n-|A|)=c_i$，当 $n-|A|<x_i$ 时，取 $b_i(n-|A|)$，当 $n-|A|>x_i$ 时，取 $c_i$（当然 $x_i$ 可能为小数，可以将 $x_i+1$ 向下取整，看到后面就明白了）。

接下来思路就很明确了，每次枚举到一个 $n-|A|$，后面那个式子有些保持不变，有些超过了临界点，改变了数值，所以以 $x_i$ 为第一关键字从小到大排序，求出 $b_i$ 与  $c_i$ 的前缀和，每次二分大于等于 $n-|A|$ 的 $x_i$ 的位置，前面的还是 $b_i(n-|A|)$，后面的是 $c_i$，利用前缀和统计答案（这时 $x_i+1$ 就有用了，因为浮点数范围太小，$x_i+1$ 后二分到这个临界点随便取 $b_i$ 还是 $c_i$ 都是同样的结果）。
## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<climits>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e5 + 10;
int n, m, sum, ans = LONG_LONG_MAX;
int a[N], qc[N], qb[N];
struct node{
    int x, b, c;
    bool operator < (const node &w) const{
        return x < w.x;
    }
}p[N];

signed main(){
    n = read(), m = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= m; i++) p[i].b = read();
    for (int i = 1; i <= m; i++) p[i].c = read();
    for (int i = 1; i <= m; i++) p[i].x = p[i].c / p[i].b + 1;
    sort(a + 1, a + n + 1);
    sort(p + 1, p + m + 1);
    for (int i = 1; i <= m; i++) qc[i] = qc[i - 1] + p[i].c, qb[i] = qb[i - 1] + p[i].b;
    for (int i = 0; i <= n; i++){
        sum += a[i];
        int y = n - i;
        int l = 1, r = m;
        while (l <= r){
            int mid = (l + r) >> 1;
            if (y >= p[mid].x){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        ans = min(ans, sum + qc[r] + (qb[m] - qb[r]) * y);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Luciylove (赞：3)

考虑网络流。

记 $(x, y, z)$ 为 $x \to y$ 流量为 $z$。下文称 $x$ 为零食， $y$ 为小孩。

- $(S, x_i, a_i)$，$(x_i,y_j,b_j)$，$(y_i, T,c_i)$。

然后我们发现显然会 TLE，所以考虑最小割。

考虑断掉 $y_i \to T$ 和 $S \to y_i$ 哪个小，前者是 $c_i$。

然后就发现了断掉 $S \to y_p$ 的路只需要断掉还没有断掉的那些 $S \to x$ 的 $(x, y, b_p)$ 即可。那么这个只跟这些 $x$ 的个数有关，不难想到枚举 $x$ 的个数。

那么考虑割掉 $k$ 个 $x$，答案即为：

- 选取 $k$ 个 $a_x$ 割掉
- 加上 $\sum \min(c_i,(n - k) \times b_i)$

前面那个显然取 $k$ 个最小的，后面那个可以按照 $\frac{c_i}{b_i}$ 排序 + 双指针解决，想直接做的我是不是傻了 （）

复杂度线性对数。


---

## 作者：Felix72 (赞：1)

我做复杂了，不过也能过。

把零食按照数量排序，一个人 $i$ 来的时候，为了避免有某种零食最后吃不完，肯定会重复以下操作 $c_i$ 次：

- 在自己还能吃的零食中选出数量最大的并吃一份。

这样一来，肯定一个后缀的零食被吃了 $b_i$ 份，剩下前缀的一个后缀的零食被区间推平，最后还可能会选出这个**剩下前缀的后缀的某个前缀**的零食各吃一份。

吃完后单调性还在，因此可以数据结构维护。$O(n\log^2n)$ 很卡常，但是 $O(n\log n)$ 需要精细实现，非常考验手法。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 200010;
int n, m; long long a[N], b[N], c[N], global;

int rt, idx;
struct SGT
{
	int ls, rs;
	long long sum, add, tag, minn, maxn;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define sum(x) tree[x].sum
	#define add(x) tree[x].add
	#define tag(x) tree[x].tag
	#define minn(x) tree[x].minn
	#define maxn(x) tree[x].maxn
} tree[N * 2];
inline void push_add(int now, int l, int r, long long _add)
{
	sum(now) += (r - l + 1) * _add;
	add(now) += _add;
	minn(now) += _add, maxn(now) += _add;
}
inline void push_tag(int now, int l, int r, long long _tag)
{
	sum(now) = (r - l + 1) * _tag;
	add(now) = 0; tag(now) = minn(now) = maxn(now) = _tag;
}
inline void pushdown(int now, int l, int r)
{
	int mid = (l + r) >> 1;
	if(tag(now) != -1)
	{
		push_tag(ls(now), l, mid, tag(now));
		push_tag(rs(now), mid + 1, r, tag(now));
		tag(now) = -1;
	}
	if(add(now))
	{
		push_add(ls(now), l, mid, add(now));
		push_add(rs(now), mid + 1, r, add(now));
		add(now) = 0;
	}
}
inline void pushup(int now)
{
	sum(now) = sum(ls(now)) + sum(rs(now));
	minn(now) = min(minn(ls(now)), minn(rs(now)));
	maxn(now) = max(maxn(ls(now)), maxn(rs(now)));
}
inline void build(int &now, int l, int r)
{
	now = ++idx; tag(now) = -1;
	if(l == r) {sum(now) = minn(now) = maxn(now) = a[l]; return ;}
	int mid = (l + r) >> 1;
	build(ls(now), l, mid), build(rs(now), mid + 1, r);
	pushup(now);
}
inline void range_add(int now, int l, int r, int L, int R, long long num)
{
	if(L > R) return ;
	if(L <= l && r <= R) {push_add(now, l, r, num); return ;}
	pushdown(now, l, r); int mid = (l + r) >> 1;
	if(L <= mid) range_add(ls(now), l, mid, L, R, num);
	if(mid < R) range_add(rs(now), mid + 1, r, L, R, num);
	pushup(now);
}
inline void range_col(int now, int l, int r, int L, int R, long long num)
{
	if(L > R) return ;
	if(L <= l && r <= R) {push_tag(now, l, r, num); return ;}
	pushdown(now, l, r); int mid = (l + r) >> 1;
	if(L <= mid) range_col(ls(now), l, mid, L, R, num);
	if(mid < R) range_col(rs(now), mid + 1, r, L, R, num);
	pushup(now);
}
int l_most;
inline long long query(int now, int l, int r, int L, int R, long long lim)
{
	if(L > R) return 0;
	if(maxn(now) < lim) return 0;
	if(L <= l && r <= R && minn(now) >= lim)
	{
		l_most = min(l_most, l);
		return sum(now) - (r - l + 1) * lim;
	}
	pushdown(now, l, r); int mid = (l + r) >> 1;
	if(R <= mid) return query(ls(now), l, mid, L, R, lim);
	else if(mid < L) return query(rs(now), mid + 1, r, L, R, lim);
	else return query(ls(now), l, mid, L, R, lim) + query(rs(now), mid + 1, r, L, R, lim);
}
inline void debug(int now, int l, int r)
{
	if(l == r) {cerr << sum(now) << " "; return ;}
	pushdown(now, l, r); int mid = (l + r) >> 1;
	debug(ls(now), l, mid), debug(rs(now), mid + 1, r); 
}
long long dt, wn, rec_ps;
inline bool get(int now, int l, int r, int L, int R)
{
//	cerr << now << " " << l << " " << r << " " << L << " " << R << '\n';
	bool flag = true;
	if(L <= l && r <= R)
	{
		long long cur = (R - r) * (dt - minn(now)) + sum(now) - minn(now) * (r - l + 1);
		if(cur <= wn)
		{
			wn -= cur; dt = min(dt, minn(now));
			rec_ps = l; return true;
		}
		flag = false;
	}
	if(l == r) return false;
	pushdown(now, l, r); int mid = (l + r) >> 1;
	if(R <= mid) flag &= get(ls(now), l, mid, L, R);
	else if(mid < L) flag &= get(rs(now), mid + 1, r, L, R);
	else if(get(rs(now), mid + 1, r, L, R)) flag &= get(ls(now), l, mid, L, R);
	else return false;
	return flag;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> a[i], global += a[i];
	for(int i = 1; i <= m; ++i) cin >> b[i];
	for(int i = 1; i <= m; ++i) cin >> c[i];
	sort(a + 1, a + n + 1);
	build(rt, 1, n);
	for(int i = 1; i <= m; ++i)
	{
//		cerr << b[i] << " " << c[i] << " : ----------------------------\n";
		int dv = n + 1, ps = 0;
		long long l = 1, r = n, lim = 0; long long w = c[i];
		while(l <= r)
		{
			int mid = (l + r) >> 1; long long cur_n = query(rt, 1, n, mid, mid, 0);
			if(cur_n < b[i]) l = mid + 1;
			else if(query(rt, 1, n, 1, mid - 1, cur_n - b[i]) + (n - mid + 1) * b[i] <= c[i]) dv = mid, r = mid - 1;
			else l = mid + 1;
		}
		if(dv <= n) w -= (n - dv + 1) * b[i], range_add(rt, 1, n, dv, n, -b[i]);
//		debug(rt, 1, n), cerr << '\n';
		if(dv > 1)
		{
			dt = query(rt, 1, n, dv - 1, dv - 1, 0); wn = w;
			get(rt, 1, n, 1, dv - 1); ps = rec_ps;
			lim = query(rt, 1, n, ps, ps, 0);
			w -= query(rt, 1, n, ps, dv - 1, lim);
			range_col(rt, 1, n, ps, dv - 1, lim);
			if(w)
			{
				l = 1, r = dv - 1; long long ref = query(rt, 1, n, dv - 1, dv - 1, 0);
				if(ref <= 0) continue;
				l_most = 1e9; query(rt, 1, n, 1, dv - 1, ref);
				int len = dv - ps;
				if(w >= len)
				{
					long long dec = min(ref, w / len);
					range_add(rt, 1, n, ps, dv - 1, -dec);
					w %= len; ref -= dec;
				}
				if(w && ref)
				{
					ps = l_most;
					range_add(rt, 1, n, ps, ps + w - 1, -1);
				}
			}
		}
//		debug(rt, 1, n), cerr << '\n';
	}
	cout << global - sum(rt) << '\n';
	return 0;
}
/*

*/
```

---

## 作者：Rainsleep (赞：1)

[cnblog](https://www.cnblogs.com/Rainsheep/p/18026415)

朴素的网络流模型很简单。
+ 从 $S$ 向所有零食连流量是 $a_i$ 的边。
+ 从所有零食向所有小孩连流量是 $b_i$ 的边。
+ 从所有小孩向 $T$ 连流量是 $c_i$ 的边。

注意到第二步涉及到 $nm$ 条边，复杂度 $O(n^{1.5}m)$，过不去。

注意到最大流同时等于最小割，所以尝试换到最小割的视角考虑。

那么问题变为将原图割为不连通的两部分，求最小割掉的权值。那么对于 $a, b, c$ 三种类型的边不妨先枚举其中一种的边的情况。

我们枚举有 $k$ 个零食最终会被割到 $S$ 集合，显然一定会选择最小的 $k$ 个 $a_i$ 割掉。现在考虑每个小孩，如果想割到 $T$，需要把原本未被钦定割到 $S$ 的 $n - k$ 的零食向他连的边全割掉，权值为 $(n - k)b_i$；同时，如果向割到 $S$ 只需要割掉 $c_i$ 即可。

注意到关于 $a_i$ 的部分是确定的，关键在于维护每个小孩的 $\min(kb_i, c_i)$。即为一个一次函数和一个常函数的取值问题，按照 $\dfrac{c_i}{b_i}$ 排序，显然具有单调性，双指针维护即可。

>关于按照 $\dfrac{c_i}{b_i}$ 排序的的理由：\
>考虑 $\min$ 值在交点前为 $c_i$，交点后为 $kb_i$，而交点满足 $kb_i = c_i$，即 $k = \dfrac{c_i}{b_i}$，而 $k$ 越大越早被枚举到，才能满足单调性。

[code](https://www.luogu.com.cn/paste/7mr25pzd)

---

## 作者：Phartial (赞：1)

不难发现一个较简单的网络流模型：

- 源点向所有糖果 $i$ 连 $a_i$ 的容量；
- 所有糖果向所有人 $i$ 连 $b_i$ 的容量；
- 所有人 $i$ 向汇点连 $c_i$ 的容量。

但第二步中建出的边数达到了惊人的 $O(nm)$，显然过不去。

考虑优化。从最大流角度优化较困难，由于最大流等价于最小割，我们可以从最小割的角度进行优化。

考虑先枚举源点到每个糖果的边是否断掉，设保留了 $l$ 个糖果。那么每个人都有两种决策：把到 $l$ 个糖果的边全部断掉，或是断掉到汇点的边，代价是 $\min(lb_i,c_i)$。

发现这个决策与具体选了哪些糖果无关，故我们可以先把不保留代价大的糖果保留，即按 $a_i$ 降序排序，依次选糖果。观察第 $i$ 个人的代价 $\min(lb_i,c_i)$，由于 $l$ 是递增的，所以必定存在某个时刻 $k_i$，使得 $k_ib_i>c_i$ 且 $(k_i-1)b_i\le c_i$，即在 $k_i$ 之前第 $i$ 个人的决策是 $lb_i$，但到 $k_i$ 之后第 $i$ 个人的决策就变成了 $c_i$。把人按 $k_i$ 升序排序，于是所有人决策总变化量是 $O(n)$ 的，双指针即可。

```cpp
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int n, m, b[kN], d[kN];
LL a[kN], c[kN], k[kN], ans;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> c[i];
    k[i] = c[i] / b[i] + 1;
    d[i] = i;
  }
  sort(a + 1, a + n + 1, greater<LL>());
  sort(d + 1, d + m + 1, [](int i, int j) { return k[i] < k[j]; });
  LL s = accumulate(a + 1, a + n + 1, 0LL), vc = 0, bs = accumulate(b + 1, b + m + 1, 0LL);
  ans = s;
  for (int i = 1, j = 1; i <= n; ++i) {
    s -= a[i], vc += bs;
    for (; j <= m && k[d[j]] <= i; ++j) {
      vc -= 1LL * i * b[d[j]] - c[d[j]], bs -= b[d[j]];
    }
    ans = min(ans, s + vc);
  }
  cout << ans;
  return 0;
}
```


---

## 作者：Leowang2009 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc125_e)

# 思路

神仙网络流题。

将每种零食和每个小孩看成一个点，然后构造一个源点，连向每个零食，流量为每种零食的个数，然后再在零食与小孩之间连边，流量为小孩每种能吃的最大个数。最后构造一个汇点，每个小孩向汇点连边，流量为每个小孩最多可以吃的零食数。

建好图后，可以发现这是个最大流，但由于点数达到了 $4 \times\ 10^5$，显然直接跑最大流会 T 的飞起，所以要找到一种快速的计算最大流的方法。

由[最大流最小割定理](https://oi-wiki.org/graph/flow/min-cut/#%E8%AF%81%E6%98%8E)可知，最大流等于最小割。恰好，在此题中，最小割较好处理。具体实现方法可以先将 $A$ 数组排序，然后将小朋友按 $C$ 除以 $B$ 由大到小排序，并分别对 $B$ 和 $C$ 数组做前缀和和后缀和（具体用处下面会说）。然后从小到大枚举切断 $A$ 的数量，并对与每个小朋友，选取切断 $B$ 或 $C$ 的最小代价。

如何选取切断的 $A$ 很好办到，难点在于处理 $B$ 和 $C$，这时候刚才的排序就起作用了。可以再设一个指针 $j$，从 $1$ 到 $j-1$ 切断 $B$，剩下的切断 $C$。显然，由于刚才的排序，$j$ 是单调递增的。所以可以在每次计算之前先移动 $j$ 指针，然后再进行计算。

# 代码实现

## 复杂度分析

时间复杂度瓶颈在排序（显然可以用快排），总体时间复杂度线性对数。

## AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,a[N],b[N],c[N],s,ans=0x3f3f3f3f3f3f3f3f;
struct node{
	int b,c;
}q[N];
bool cmp(node a,node b){
	return a.c*b.b>b.c*a.b;//将除法改为乘法，精度更高，且速度更快
}//比较函数
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++) scanf("%lld",&q[i].b);
	for(int i=1;i<=m;i++) scanf("%lld",&q[i].c);//输入
	sort(a+1,a+n+1);//将 A 从小到大排序
	sort(q+1,q+m+1,cmp);//将小孩按 C/B 排序
	for(int i=2;i<=n;i++) a[i]+=a[i-1];//做 A 的前缀和
	for(int i=1;i<=m;i++) b[i]=b[i-1]+q[i].b;//做 B 的前缀和
	for(int i=m;i;i--) c[i]=c[i+1]+q[i].c;//做 C 的后缀和
	for(int i=0,j=1;i<=n;i++){
		int res=a[i];//割断 A 的代价
		for(;q[j].b*(n-i)<q[j].c;j++);//移动 j 指针
		res+=(n-i)*b[j-1]+c[j];//总代价
		ans=min(res,ans);//记录最小值
	}//计算最小割
	printf("%lld",ans);//输出
	return 0;
}
```

完结撒花！

---

## 作者：shiruoyu114514 (赞：0)

在下文的叙述中，默认 $i$ 为小孩，$j$ 为零食。

有一个显而易见的网络流：左部点为小孩，右部点为零食，$S$ 向 $i$ 连 $c_i$ 大小的边，$i$ 向 $j$ 连 $b_i$ 大小的边，$j$ 向 $T$ 连 $a_j$ 大小的边。求最大流即可。时间复杂度 $O(n^4)$，过不了一点。

考虑最大流转最小割。不难发现对于任何一个 $i$，其要么断掉 $S \rightarrow i$ 的边，要么对于每一个没有断掉 $j \rightarrow T$ 的 $j$，断掉 $i \rightarrow j$。

由于每个 $j$ 除了 $a_j$ 不等外其余地位相等，考虑起来最简单，所以先从少到多枚举 $j \rightarrow T$ 的断边。显然在给定断边条数的情况下，应该首先断最小的。

现在假设有 $n_j$ 种零食。每个 $i$ 要么断掉所有 $j \rightarrow T$ 没有被断掉的 $i \rightarrow j$ 边，消耗 $b_in_j$，要么断掉 $S \rightarrow i$ 边，消耗 $a_i$。不难发现随着 $n_j$ 的减小，$i$ 的贡献会由 $a_i$ 变成 $b_in_j$。在每次转折时维护即可。时间复杂度 $O(n \log n)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc125_e)

**题目大意**

> $n$ 个物品，第 $i$ 种物品有 $a_i$ 个，$m$ 盒子，每个盒子每种物品 $\le b_i$ 个，总数 $\le c_i$，求放入盒子的物品总数最大值。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

直接建立网络流模型，左部点为物品，$S\to i$ 流量 $a_i$，右部点为盒子，$j\to T$ 流量 $c_j$，$i\to j$ 流量 $b_j$。

考虑最小割最大流转化，用组合意义计算最小割。

设 $S\to i$ 切掉了 $k$ 个，那么对于每个盒子，不存在 $S\to j\to T$ 的最小代价为 $\min(c_j,(n-k)\times b_j)$。

注意这个和值具体切掉了哪 $k$ 条边没有关系，直接切掉最大的 $k$ 条，枚举 $k$，动态维护 $\min(c_j,(n-k)\times b_j)$，维护 $j$ 决策切换到 $b_j$ 的时刻即可。

时间复杂度 $\mathcal O(n\log n+m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
int n,m;
ll a[MAXN],b[MAXN],c[MAXN],A,B,C,ans;
vector <int> s[MAXN];
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),A+=a[i];
	for(int i=1;i<=m;++i) scanf("%lld",&b[i]),B+=b[i];
	for(int i=1;i<=m;++i) {
		scanf("%lld",&c[i]);
		if(b[i]*n>c[i]) s[c[i]/b[i]+1].push_back(i);
	}
	sort(a+1,a+n+1),ans=A;
	for(int k=0;k<=n;++k) { //min(kb,c)
		for(int j:s[k]) B-=b[j],C+=c[j];
		ans=min(ans,A+k*B+C),A-=a[n-k];
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：rizynvu (赞：0)

[我的博客](https://www.cnblogs.com/rizynvu/p/18287938)。

观察到这种都是数量上限的限制，且求 $\max$。  

所以可以考虑网络流建模，而流量就对应着给的糖果数。  
令 $S$ 为源点，$T$ 为汇点，编号为 $1\sim n$ 的点对应的糖果的种类，编号为 $n + 1\sim n + m$ 的点对应的小孩。  
连边 $(S, i, a_i)$，表示第 $i$ 种糖果数不超过 $a_i$ 个。  
连边 $(i, n + j, b_j)$，表示第 $j$ 个小孩吃单种糖果不超过 $b_j$ 个。  
连边 $(n + j, T, c_j)$，表示第 $j$ 个小孩总共不能吃超过 $c_i$ 个糖果。

但是在 $n, m\le 2\times 10^5$ 的情况下，跑最大流明显有点废。  
考虑一个套路，根据最大流最小割定理有最大流 $=$ 最小割，所以转而去求这个图的最小割。

考虑这个图的最小割怎么求。  
首先令 $\operatorname{type}_i = S \operatorname{or} T$，代表 $i$ 点是属于 $S$ 集合还是 $T$ 集合。  
能发现对于 $\operatorname{type}_i$ 的分配方式，对应的割的大小就为 $(\sum\limits_{i = 1}^n a_i[\operatorname{type}_i = T]) + (\sum\limits_{j = 1}^m b_j[\operatorname{type}_{n + j} = T]\times \sum\limits_{i = 1}^n [\operatorname{type}_i = S]) + (\sum\limits_{j = 1}^m c_j[\operatorname{type}_{m + j} = S])$。

发现对于 $i, j$ 之间的贡献对于 $i$ 这一方其实只有 $\sum\limits_{i = 1}^n [\operatorname{type}_i = S]$。  

这启发考虑枚举这个 $c = \sum\limits_{i = 1}^n [\operatorname{type}_i = S]$ 来做。  
- 对于 $\sum\limits_{i = 1}^n a_i[\operatorname{type}_i = T]$。  
   易知这就是让最大的 $c$ 个 $a_i$ 对应的 $\operatorname{type}$ 为 $S$。
- 对于 $(\sum\limits_{j = 1}^m b_j[\operatorname{type}_{n + j} = T]\times c) + (\sum\limits_{j = 1}^m c_j[\operatorname{type}_{m + j} = S])$。  
   相当于就是求 $\sum\limits_{j = 1}^m \min\{b_j\times c, c_j\}$。  
   这个可以知道 $b_j\times c\le c_j$ 当且仅当 $c\le \lfloor\frac{c_j}{b_j}\rfloor$，就可以 $\mathcal{O}(1)$ 维护了。

时间复杂度 $\mathcal{O}(n\log n)$，瓶颈在排序。

```cpp
#include<bits/stdc++.h>
using ll = long long;
const int maxn = 2e5 + 10;
ll a[maxn], b[maxn], c[maxn];
std::vector<int> id[maxn];
int main() {
   int n, m; scanf("%d%d", &n, &m);
   for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
   for (int i = 1; i <= m; i++) scanf("%lld", &b[i]);
   for (int i = 1; i <= m; i++) scanf("%lld", &c[i]);
   for (int i = 1; i <= m; i++) {
      ll ti = c[i] / b[i] + 1ll;
      if (ti <= (ll)n) id[ti].push_back(i);
   }
   std::sort(a + 1, a + n + 1, [&](ll x, ll y) {return x > y;});
   ll sum = 0, add = 0, ans;
   for (int i = 1; i <= n; i++) sum += a[i];
   for (int i = 1; i <= m; i++) add += b[i];
   ans = sum;
   for (int i = 1; i <= n; i++) {
      sum -= a[i], sum += add;
      for (int j : id[i]) sum -= b[j] * i, add -= b[j], sum += c[j];
      ans = std::min(ans, sum);
   }
   printf("%lld\n", ans);
   return 0;
}
```

---

