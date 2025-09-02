# [NOISG 2025 Prelim] Lasers 2

## 题目描述

Pavement 从 Gohcart 那里购买了一个激光玩具（Gohcart 原先是从 Rar the Cat 那里买的）。这个玩具有一个由 $h$ 行 $w$ 列组成的网格。网格的行编号从上到下为 $1$ 到 $h$，列编号从左到右为 $1$ 到 $w$。

每一行恰好包含一个上锁的滑动墙。初始时，第 $i$ 行的墙覆盖第 $l[i]$ 列到第 $r[i]$ 列（从 $1$ 开始编号），解锁它需要花费 $c[i]$ 美元。墙一旦解锁，就可以在第 $i$ 行上水平滑动到任意位置，只要它对齐在网格的边缘内即可。墙的任何部分都不能超出玩具的左边缘或右边缘。

每一列的顶部都有一个朝下的激光。如果某个滑动墙位于第 $i$ 列，那么它将阻挡第 $i$ 列上的激光。

一个可能的玩具示例如下，其中 $h = 3$，$w = 10$：

![](https://cdn.luogu.com.cn/upload/image_hosting/4cah8wpf.png)

给定总预算 $k$ 美元，Pavement 的目标是在合理解锁并滑动墙壁的情况下，最大化未被阻挡的激光数量。请你确定他最多可以实现多少束未被阻挡的激光。


## 说明/提示

### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $1 \leq h, w \leq 2000$
- $0 \leq k \leq 10^9$
- 对所有 $1 \leq i \leq h$，满足 $1 \leq l[i] \leq r[i] \leq w$
- 对所有 $1 \leq i \leq h$，满足 $0 \leq c[i] \leq 10^9$

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分数 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $6$ | $k = 0, c[i] = 10^9$ |
| $2$ | $9$ | $l[i] = r[i]$ |
| $3$ | $10$ | $h, w \leq 18$ |
| $4$ | $7$ | $h, w \leq 100, k \leq 2000$ |
| $5$ | $15$ | $h, w \leq 100$ |
| $6$ | $23$ | $h, w \leq 500$ |
| $7$ | $8$ | $r[1] − l[1] = r[2] − l[2] = \ldots = r[h] − l[h]$ |
| $8$ | $22$ | 无 |

### 样例 1 解释

上图的激光玩具正对应该测试用例。Pavement 可以以 $9 + 1 = 10$ 美元的总价解锁第一个和第二个滑动墙。然后他可以将第一个滑动墙滑动到覆盖第 $4$ 到 $7$ 列，将第二个滑动墙滑动到覆盖第 $5$ 到 $7$ 列。

![](https://cdn.luogu.com.cn/upload/image_hosting/glj93dtp.png)

这样一来，$6$ 束激光（第 $1, 2, 3, 8, 9, 10$ 列）未被阻挡，这是能够实现的最大数量。

此样例适用于子任务 $3, 4, 5, 6, 8$。

### 样例 2 解释

此样例适用于子任务 $2$ 到 $8$。

### 样例 3 解释

此样例适用于子任务 $1, 3, 4, 5, 6, 8$。

## 样例 #1

### 输入

```
3 10 10
2 5 9
1 3 1
4 7 10```

### 输出

```
6```

## 样例 #2

### 输入

```
10 10 50
8 8 0
3 3 0
6 6 2
7 7 9
1 1 50
5 5 21
6 6 4
10 10 4
10 10 3
10 10 3```

### 输出

```
9```

## 样例 #3

### 输入

```
4 17 0
2 4 1000000000
6 9 1000000000
8 13 1000000000
15 16 1000000000```

### 输出

```
4```

# 题解

## 作者：EuphoricStar (赞：5)

考虑将最终的局面划分成，若干个极长的，每一列都至少有一个滑动墙的列连续段。设划分出来的连续段是 $[l_1, r_1], [l_2, r_2], \ldots, [l_t, r_t]$，那么不用被解锁的滑动墙的花费是 $\sum\limits_{i = 1}^t g(l_i, r_i)$，其中 $g(l, r)$ 表示所有满足 $l \le l_i \le r_i \le r$ 的滑动墙的 $c_i$ 之和。一种方案合法，当且仅当：

- $\sum\limits_{i = 1}^h c_i - \sum\limits_{i = 1}^t g(l_i, r_i) \le k$，即花费不能超过 $k$；
- 令 $x = \max\limits_{p = 1}^h r_p - l_p + 1$，则 $\exists i \in [1, t], r_i - l_i + 1 \ge x$，因为要给最长的滑动墙留够位置放。

于是我们转而求满足条件的划分方案中，$\sum\limits_{i = 1}^t g(l_i, r_i)$ 的最大值。接下来的 DP 是自然的。设 $f_{i, j, 0/1}$ 表示，考虑到 $[1, i]$ 这个前缀，其中有 $j$ 列没有滑动墙，当前是否出现长度 $\ge x$ 的连续段。有两种转移：

- 第 $i$ 位留空，有 $f_{i, j, k} \gets f_{i - 1, j - 1, k}$；
- 第 $i$ 位是一个连续段的右端点，枚举这个连续段的左端点 $l$，有 $f_{i, j, k \lor [i - l + 1 \ge x]} \gets f_{l - 1, j, k} + g(l, i)$。

朴素转移时间复杂度为 $O(w^3)$，无法通过。考虑优化。发现瓶颈在第二种转移，考虑在最外层枚举 $j$，那么转移形如 $f_i \gets f_{j - 1} + g(j, i)$。考虑线段树优化。线段树每个下标 $j$ 维护 $f_{j - 1} + g(j, i)$，枚举到 $i$ 时加入所有 $r_k = i$ 的滑动墙，即对 $j \in [1, l_k]$ 区间加上 $c_k$。计算 $f_i$ 时求线段树区间最大值即可。

设 $h, w$ 同阶，时间复杂度 $O(w^2 \log w)$。

```cpp
#include <bits/stdc++.h>
#define fst first
#define scd second
#define pb emplace_back
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 2020;

ll n, m, K, f[maxn][maxn][2];
vector<pii> vc[maxn];

struct node {
	ll l, r, x;
} a[maxn];

struct SGT {
	ll a[maxn << 2], tag[maxn << 2];
	
	inline void pushup(int x) {
		a[x] = max(a[x << 1], a[x << 1 | 1]);
	}
	
	inline void pushtag(int x, ll y) {
		a[x] += y;
		tag[x] += y;
	}
	
	inline void pushdown(int x) {
		if (!tag[x]) {
			return;
		}
		pushtag(x << 1, tag[x]);
		pushtag(x << 1 | 1, tag[x]);
		tag[x] = 0;
	}
	
	void build(int rt, int l, int r) {
		tag[rt] = 0;
		a[rt] = -1e18;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(rt << 1, l, mid);
		build(rt << 1 | 1, mid + 1, r);
	}
	
	void update(int rt, int l, int r, int ql, int qr, ll x) {
		if (ql <= l && r <= qr) {
			pushtag(rt, x);
			return;
		}
		pushdown(rt);
		int mid = (l + r) >> 1;
		if (ql <= mid) {
			update(rt << 1, l, mid, ql, qr, x);
		}
		if (qr > mid) {
			update(rt << 1 | 1, mid + 1, r, ql, qr, x);
		}
		pushup(rt);
	}
	
	void modify(int rt, int l, int r, int x, ll y) {
		if (l == r) {
			a[rt] = y;
			return;
		}
		pushdown(rt);
		int mid = (l + r) >> 1;
		(x <= mid) ? modify(rt << 1, l, mid, x, y) : modify(rt << 1 | 1, mid + 1, r, x, y);
		pushup(rt);
	}
	
	ll query(int rt, int l, int r, int ql, int qr) {
		if (ql > qr) {
			return -1e18;
		}
		if (ql <= l && r <= qr) {
			return a[rt];
		}
		pushdown(rt);
		int mid = (l + r) >> 1;
		ll res = -1e18;
		if (ql <= mid) {
			res = max(res, query(rt << 1, l, mid, ql, qr));
		}
		if (qr > mid) {
			res = max(res, query(rt << 1 | 1, mid + 1, r, ql, qr));
		}
		return res;
	}
} T[2];

void solve() {
	scanf("%lld%lld%lld", &n, &m, &K);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld%lld", &a[i].l, &a[i].r, &a[i].x);
		vc[a[i].r].pb(a[i].l, a[i].x);
	}
	ll s = 0, mx = 0;
	for (int i = 1; i <= n; ++i) {
		s += a[i].x;
		mx = max(mx, a[i].r - a[i].l + 1);
	}
	mems(f, -0x3f);
	f[0][0][0] = 0;
	for (int j = 0; j <= m; ++j) {
		T[0].build(1, 1, m);
		T[1].build(1, 1, m);
		for (int i = 1; i <= m; ++i) {
			for (int k = 0; k <= 1; ++k) {
				if (j) {
					f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k]);
				}
			}
			T[0].modify(1, 1, m, i, f[i - 1][j][0]);
			T[1].modify(1, 1, m, i, f[i - 1][j][1]);
			for (pii p : vc[i]) {
				T[0].update(1, 1, m, 1, p.fst, p.scd);
				T[1].update(1, 1, m, 1, p.fst, p.scd);
			}
			f[i][j][0] = max(f[i][j][0], T[0].a[1]);
			f[i][j][1] = max({f[i][j][1], T[1].a[1], T[0].query(1, 1, m, 1, i - mx + 1)});
		}
	}
	for (int i = m; ~i; --i) {
		if (s - f[m][i][1] <= K) {
			printf("%d\n", i);
			return;
		}
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：3)

我们假设，操作结束后，位置 $[x_1,y_1],[x_2,y_2],\cdots,[x_n,y_n]$ 的激光可能会被挡住，其他位置的激光一定不会被挡住，那么所有满足 $\exist j \in [1,n],x_j \le l_i \le r_i \le y_j$ 的滑动墙 $i$ 都不需要解锁，而其余的滑动墙都必须解锁，否则一定会挡住其他激光；同时，设 $m=\max\limits_{i=1}^h r_i-l_i+1$，则需要满足 $\exist z \in [1,n],y_z-x_z+1 \ge m$，否则最长的滑动墙没有地方放置。我们不需要担心解锁后的滑动墙再挡住其他激光，因为我们可以把这些滑动墙都放到最长的滑动墙后面。

于是我们考虑一个 dp：设 $f_{i,j,0/1}$ 表示考虑到第 $i$ 列，目前有 $j$ 列激光没有被挡住，且当前不存在 / 存在 $y_z-x_z+1 \ge m$ 的正整数 $z$ 的，不需要解锁的滑动墙的最大价值和。初始时 $f_{0,0,0}=0$，其余均为 $-\infty$。

有一个朴素的转移方式是：

- 第 $i$ 列激光没有被挡住，$f_{i,j,s}\leftarrow \max(f_{i,j,s},f_{i-1,j-1,s})$；
- 第 $i$ 列激光被挡住了，枚举这段被挡住的激光的左端点 $x$，$f_{i,j,s \lor [i-x+1\ge m]}\leftarrow \max(f_{i,j,s \lor [i-x+1\ge m]},f_{x-1,j,s}+\sum_{x \le l_k \le r_k \le i} c_k)$。

但是直接这样做是 $\mathcal O(w^3)$ 的，考虑优化。

注意到，影响时间复杂度的第二种转移中 $j$ 的值不变，于是我们可以更改一下枚举顺序，先枚举 $j$ 再枚举 $i$，并把所求的信息拍到线段树上维护。

具体而言，对于每个 $j$，我们开两棵线段树 $T_0,T_1$，在 $T_s$ 的第 $x$ 个叶子处维护 $f_{x-1,j,s}+\sum_{x \le l_k \le r_k \le i} c_k$ 的值。每次 $i$ 增加 $1$ 后，我们找到所有 $r_k=i$ 的滑动墙，并给 $T_0$ 和 $T_1$ 的前 $l_k$ 个叶子所维护的值增加 $c_k$，因为这些叶子满足 $x \le l_k \le r_k \le i$；同时，我们把 $f_{i,j,0}$ 的值赋为 $T_0$ 的第 $[i-m+2,i]$ 个叶子的权值的 $\max$，把 $f_{i,j,1}$ 的值赋为 $T_0$ 的前 $i-m+1$ 个叶子与 $T_1$ 的前 $i$ 个叶子的权值的 $\max$，并更新 $T_0$ 和 $T_1$ 的第 $i+1$ 个叶子的权值。这样我们就完成了第二种转移，第一种转移直接暴力做即可。

于是我们就快速求出了 $f$ 数组，那我们找到最大的满足 $\sum c_i-f_{w,a,1}\le k$ 的正整数 $a$ 即为答案。时间复杂度 $\mathcal O(w^2 \log w)$。

---

## 作者：Purslane (赞：2)

# Solution

简单的题目，~~随便想一想就会了。~~

考虑我们解锁了一些方块，如何操作使得答案最小。

显然这些方块应该叠在一起，所以我们只需要考虑最长的方块。

分类讨论：

1. 所有方块中最长的没有被解锁。那么其他所有被解锁的方块都可以移动到这个方块的上方而不产生额外影响，所以设 $dp_{i,j}$ 表示前 $i$ 个数，要求 $j$ 个位置的激光最终存在的最小代价（特别的，第 $i$ 个激光必须存在）。很容易写出转移：$dp_{i,j} = \min_{k<i} dp_{k,j-1} + f(k+1,j)$。其中 $f(a,b)$ 表示所有 $a \le l_i \le b \le r_i$ 的 $c_i$ 之和。容易使用线段树优化。

2. 所有方块中最长的被解锁了。设其长度为 $l$，只需要最终的结果中有连续 $l$ 个激光被挡住即可。在 $dp$ 中再开一维 $0/1$ 记录即可。

复杂度 $O(n^2 \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10;
int ans,n,m,k,L[MAXN],R[MAXN],C[MAXN],bl;
vector<int> occl[MAXN],occr[MAXN];
int f[MAXN],g[MAXN],F[MAXN][2],G[MAXN][2];
struct Seg {
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid ((l+r)>>1)
	//支持区间加，区间求最大值的 segment tree /se
	vector<int> tag,mn;
	void push_down(int k,int l,int r) {return tag[lson]+=tag[k],tag[rson]+=tag[k],mn[lson]+=tag[k],mn[rson]+=tag[k],tag[k]=0,void();}
	void build(int k,int l,int r) {mn[k]=0x3f3f3f3f3f3f3f3f,tag[k]=0;if(l!=r) build(lson,l,mid),build(rson,mid+1,r);return ;}
	void init(void) {return tag.clear(),mn.clear(),tag.resize(4*m+10),mn.resize(4*m+10),build(1,0,m),void();}
	void update(int k,int l,int r,int x,int y,int v) {
		if(x<=l&&r<=y) return tag[k]+=v,mn[k]+=v,void();
		push_down(k,l,r);
		if(x<=mid) update(lson,l,mid,x,y,v);
		if(y>mid) update(rson,mid+1,r,x,y,v);
		return mn[k]=min(mn[lson],mn[rson]),void();
	}
	int query(int k,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return mn[k];
		push_down(k,l,r);
		if(y<=mid) return query(lson,l,mid,x,y);
		if(x>mid) return query(rson,mid+1,r,x,y);
		return min(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));
	}
	void assign(int k,int l,int r,int pos,int v) {
		if(l==r) return mn[k]=v,void();
		push_down(k,l,r);
		if(pos<=mid) assign(lson,l,mid,pos,v);
		else assign(rson,mid+1,r,pos,v);
		return mn[k]=min(mn[lson],mn[rson]),void();
	}
};
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	pair<int,int> mx;
	ffor(i,1,n) cin>>L[i]>>R[i]>>C[i],occl[L[i]].push_back(i),occr[R[i]].push_back(i);
	ffor(i,1,n) mx=max(mx,{R[i]-L[i]+1,i});
	//没有解锁 mx，一定要注意中间不能放东西
	bl=mx.second;
	memset(f,0x3f,sizeof(f)),f[0]=0;
	Seg sg;
	ffor(cnt,1,m) {
		sg.init();
		sg.assign(1,0,m,0,f[0]);
		memset(g,0x3f,sizeof(g));
		ffor(i,1,m) {
			for(auto id:occl[i]) sg.update(1,0,m,0,m,C[id]);
			for(auto id:occr[i-1]) sg.update(1,0,m,0,L[id]-1,-C[id]);
			if(i<L[bl]||i>R[bl]) g[i]=sg.mn[1];
			sg.assign(1,0,m,i,f[i]);
		}
		ffor(i,0,m) {
			f[i]=g[i];
			if(f[i]<=k) ans=max(ans,cnt);
		}
	}
	//解锁了 mx，只需要中间有一个长度为。。的连续断
	//注意我们假装 mx 不存在即可
	Seg sg1,sg2;
	memset(F,0x3f,sizeof(F)),F[0][0]=0;
	ffor(cnt,1,m) {
		memset(G,0x3f,sizeof(G));
		sg1.init(),sg2.init();
		sg1.assign(1,0,m,0,F[0][0]),sg2.assign(1,0,m,0,F[0][1]);
		ffor(i,1,m) {
			for(auto id:occl[i]) if(id!=bl) sg1.update(1,0,m,0,m,C[id]),sg2.update(1,0,m,0,m,C[id]);
			for(auto id:occr[i-1]) if(id!=bl) sg1.update(1,0,m,0,L[id]-1,-C[id]),sg2.update(1,0,m,0,L[id]-1,-C[id]);
			G[i][0]=sg1.mn[1];
			G[i][1]=sg2.mn[1];
			if(i>=R[bl]-L[bl]+2) G[i][1]=min(G[i][1],sg1.query(1,0,m,0,i-R[bl]+L[bl]-2));
			sg1.assign(1,0,m,i,F[i][0]);
			sg2.assign(1,0,m,i,F[i][1]);
		}
		ffor(i,0,m) {
			F[i][0]=G[i][0],F[i][1]=G[i][1];
			if(F[i][1]+C[bl]<=k) ans=max(ans,cnt);
			if(F[i][0]+C[bl]<=k&&m-i>=R[bl]-L[bl]+1) ans=max(ans,cnt);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yukimianyan (赞：1)

# 题解：\[NOISG2025 Prelim\] Lasers 2

## solution

因为我们可以将所有激活墙全部放在最长的激活墙后面，而如果最长的激活墙比最长未激活墙短（也就是全场最长墙未激活），那么答案就是未激活墙的并的大小，否则我们需要找一个地方放置这个激活的全场最长墙，然后答案是未激活墙的并再并上这个最长墙的大小。

一堆区间的并还是太困难了，我们不妨按照并的连续段进行 dp。我们把问题改成最大化选中的区间的价格的和（也就是我们着眼于的是未激活的墙），先处理一个 $sum[l,r]$ 表示所有 $\subseteq[l, r]$ 的区间的价格，然后直接 dp，设 $f_i$ 表示考虑完 $[1, i]$ 的选择情况的最大价格，转移就 $O(n)$ 转移 $f_i=\max_{j\leq i}f_{j-1}+sum_{j, i}$。这只是一个雏形，我们还需要的是：

1. 需要有一个连续段的长度大于全场最长墙，然后再看看能不能计入全场最长墙的价格。使用一个 `0/1` 记录即可。
2. 需要记答案，记录有多少个空位（记作变量 $w$）。使用 $O(n)$ 的时空代价即可。

此时复杂度 $O(n^3)$，需要优化。

发现我们将前面的 $O(n^2)$ 个状态排成矩阵的形式，那么就是形如矩阵的某一列对位加上 $sum$ 的某一列的最大值贡献到 $f_{i, w}$，且随着 $i$ 增加这些列不会变，只有 $sum$ 的那一列会增加。然而这样的话可以不在一开始处理 $sum$，而是 $i$ 增加的时候将右端点为 $i$ 的区间拿出来将每列的某个前缀进行整体加。所以我们对每一列用线段树维护即可，需要支持区间加和区间最大值（因为有一个“连续段的长度大于全场最长墙”的特殊转移需要区间最大值）。由于区间个数是 $O(n)$ 的，复杂度做到 $O(n^2\log n)$ 也就是 $O(hw\log w)$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define debug(...) void(0)
#define endl "\n"
#endif
using LL = long long;
template <class T> T& chkmin(T& x, const T& y) { return x = min(x, y); }
template <class T> T& chkmax(T& x, const T& y) { return x = max(x, y); }
constexpr int N = 2010;
struct wall {
  int l, r, c;
  int length() const { return r - l + 1; }
  friend bool operator<(const wall& lhs, const wall& rhs) { return lhs.length() < rhs.length(); }
};
struct segtree {
  LL ans[N << 2], tag[N << 2];
  segtree() {
    memset(ans, ~0x3f, sizeof ans);
    memset(tag, 0, sizeof tag);
  }
  void spread(int p, LL k) { tag[p] += k, ans[p] += k; }
  void maintain(int p) { ans[p] = max(ans[p << 1], ans[p << 1 | 1]); }
  void pushdown(int p) { spread(p << 1, tag[p]), spread(p << 1 | 1, tag[p]), tag[p] = 0; }
  void setValue(int x, LL v, int p, int l, int r) {
    if (l == r) return ans[p] = v, void();
    int mid = (l + r) >> 1;
    pushdown(p);
    if (x <= mid) setValue(x, v, p << 1, l, mid);
    else setValue(x, v, p << 1 | 1, mid + 1, r);
    maintain(p);
  }
  void modify(int ql, int qr, LL k, int p, int l, int r) {
    if (ql <= l && r <= qr) return spread(p, k);
    int mid = (l + r) >> 1;
    pushdown(p);
    if (ql <= mid) modify(ql, qr, k, p << 1, l, mid);
    if (mid < qr) modify(ql, qr, k, p << 1 | 1, mid + 1, r);
    maintain(p);
  }
  LL query(int ql, int qr, int p, int l, int r) {
    if (ql <= l && r <= qr) return ans[p];
    int mid = (l + r) >> 1;
    pushdown(p);
    LL ret = -1e18;
    if (ql <= mid) chkmax(ret, query(ql, qr, p << 1, l, mid));
    if (mid < qr) chkmax(ret, query(ql, qr, p << 1 | 1, mid + 1, r));
    return ret;
  }
} tr[N][2];
int n, m;
LL lim, f[N][2][N];
vector<wall> rgs[N];
int main() {
#ifndef NF
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  cin >> m >> n >> lim, lim = -lim;
  wall maxw = {0, -1, 0};
  for (int i = 1, l, r, c; i <= m; i++) cin >> l >> r >> c, lim += c, rgs[r].push_back({l, r, c}), maxw = max(maxw, wall{l, r, c});
  rgs[maxw.r].push_back({maxw.l, maxw.r, -maxw.c});
  memset(f, ~0x3f, sizeof f);
  f[0][0][0] = 0;
  for (int i = 1; i <= n; i++) {
    f[i][0][0] = 0;
    for (int t : {0, 1}) {
      for (int w = 1; w <= i; w++) {
        auto& seg = tr[w - i + n][t];
        seg.setValue(i, f[i - 1][t][w - 1], 1, 1, n);
        for (auto wl : rgs[i]) seg.modify(1, wl.l, wl.c, 1, 1, n);
        chkmax(f[i][t][w], max(seg.ans[1], f[i - 1][t][w]));
        if (t == 0 && i >= maxw.length()) {
          if (maxw.r <= i) seg.modify(1, maxw.l, maxw.c, 1, 1, n);
          chkmax(f[i][1][w], seg.query(1, i - maxw.length() + 1, 1, 1, n));
          if (maxw.r <= i) seg.modify(1, maxw.l, -maxw.c, 1, 1, n);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int t : {0, 1}) {
      for (int w = 0; w <= n; w++) if (f[i][t][w] >= 0) debug("f[%d][%d][%d] = %lld\n", i, t, w, f[i][t][w]);
    }
  }
  for (int w = 0; w <= n; w++) if (f[n][1][w] >= lim) return cout << n - w << endl, 0;
  assert(false);
  return 0;
}
```

以下是暴力代码，可以参考一下。

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define debug(...) void(0)
#define endl "\n"
#endif
using LL = long long;
template <class T> T& chkmin(T& x, const T& y) { return x = min(x, y); }
template <class T> T& chkmax(T& x, const T& y) { return x = max(x, y); }
constexpr int N = 2010;
struct wall {
  int l, r, c;
  int length() const { return r - l + 1; }
  friend bool operator<(const wall& lhs, const wall& rhs) { return lhs.length() < rhs.length(); }
};
int n, m;
LL lim, sum[N][N];
vector<pair<int, LL>> f[N][2];
int main() {
#ifndef NF
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  cin >> m >> n >> lim, lim = -lim;
  wall maxw = {0, -1, 0};
  for (int i = 1, l, r, c; i <= m; i++) cin >> l >> r >> c, lim += c, sum[l][r] += c, maxw = max(maxw, wall{l, r, c});
  sum[maxw.l][maxw.r] -= maxw.c;
  for (int l = n; l >= 1; l--) {
    for (int r = 1; r <= n; r++) sum[l][r] += sum[l + 1][r];
  }
  for (int l = 1; l <= n; l++) {
    for (int r = 1; r <= n; r++) sum[l][r] += sum[l][r - 1];
  }
  f[0][0].emplace_back(0, 0);
  for (int i = 1; i <= n; i++) {
    static LL tmp[2][N];
    for (int t : {0, 1}) {
      fill(tmp[t], tmp[t] + i + 1, -1e18); 
      for (auto [w, sv] : f[i - 1][t]) chkmax(tmp[t][w], sv);
      for (int j = i; j >= 1; j--) {
        for (auto [w, sv] : f[j - 1][t]) chkmax(tmp[t][w + i - j + 1], sv + sum[j][i]);
      }
    }
    for (int j = i - maxw.length() + 1; j >= 1; j--) {
      for (auto [w, sv] : f[j - 1][0]) chkmax(tmp[1][w + i - j + 1], sv + sum[j][i] + (j <= maxw.l && maxw.r <= i ? maxw.c : 0));
    }
    for (int t : {0, 1}) {
      for (int w = 0; w <= i; w++) if (tmp[t][w] >= 0) debug("f[%d][%d][%d] = %lld\n", i, t, w, tmp[t][w]);
      LL pre = -1;
      for (int j = 0; j <= i; j++) if (pre < tmp[t][j]) f[i][t].emplace_back(j, pre = tmp[t][j]);
    }
  }
  for (auto [w, sv] : f[n][1]) if (sv >= lim) return cout << n - w << endl, 0;
  assert(false);
  return 0;
}
```

---

## 作者：__FL__ (赞：0)

## Solution
显然当其他墙解锁后可以移动到最长的墙后面，所以我们考虑最长的墙的位置。

不妨设 $f_{i,j}$ 表示对于前 $i$ 列，未被阻挡的激光为 $j$ 束时的最小代价（**钦定第 $i$ 列未被阻挡**），显然有转移：

$$f_{i,j}=\min_{k<i} f_{k,j-1}+w(k,i)$$

其中，$w(k,i)$ 表示解锁阻挡第 $i$ 列**但不阻挡第 $k$ 列**的墙的花费（因为阻挡第 $k$ 列的已经算过了）。显然线段树容易处理这个问题，枚举到第 $i$ 列时，修改左端点为 $i$ 的墙并还原右端点为 $i$ 的墙，同时加入 $f_{i,j-1}$。具体可见代码。

对 $f$ 取前缀最大值，使其一般化；同理求得后缀 $g_{i,j}$ 表示第 $i$ 到第 $w$ 列，未被阻挡的激光为 $j$ 束时的最小代价。

枚举最长墙的位置。枚举左边未被阻挡的激光数量，二分右边最多可以有多少激光不被遮挡，取最大值。

处理 $f$ 和 $g$ 时和处理答案时的时间复杂度都为 $O(w^2\log w)$，可以通过。

## Code
（代码中 $f,g$ 的含义与上文不同）
```cpp
#include <bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
const int N = 2005;
int h,w,k,f[N][N],p[N<<2],g[N<<2],y[N][N];
struct node
{
	int l,r,c;
}a[N],b[N];
bool cmp(node a,node b)
{
	return a.l < b.l;
}
void pushdown(int root)
{
	p[root*2] += g[root];
	p[root*2+1] += g[root];
	g[root*2] += g[root];
	g[root*2+1] += g[root];
	g[root] = 0;
}
void update(int root,int l,int r,int ql,int qr,int x)
{
	if (ql <= l && qr >= r)
	{
		p[root] += x;
		g[root] += x;
		return;
	}
	if (g[root]) pushdown(root);
	int mid = (l+r)/2;
	if (qr <= mid) update(root*2,l,mid,ql,qr,x);
	else if (ql > mid) update(root*2+1,mid+1,r,ql,qr,x);
	else update(root*2,l,mid,ql,mid,x),update(root*2+1,mid+1,r,mid+1,qr,x);
	p[root] = min(p[root*2],p[root*2+1]);
}
int query(int root,int l,int r,int ql,int qr)
{
	if (ql <= l && qr >= r) return p[root];
	if (g[root]) pushdown(root);
	int mid = (l+r)/2;
	if (qr <= mid) return query(root*2,l,mid,ql,qr);
	if (ql > mid) return query(root*2+1,mid+1,r,ql,qr);
	return min(query(root*2,l,mid,ql,mid),query(root*2+1,mid+1,r,mid+1,qr));
}
signed main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >> h >> w >> k;
	int mxl,mxp = 0,mxc,mxk;
	for (int i = 1; i <= h; i++)
	{
		cin >> a[i].l >> a[i].r >> a[i].c;
		if (a[i].r-a[i].l+1 > mxp) mxp = a[i].r-a[i].l+1,mxl = a[i].l,mxc = a[i].c,mxk = i;
	}
	a[mxk].l = 99999999;
	sort(a+1,a+h+1,cmp);
	h--;
	for (int i = 1; i <= h; i++)
		b[i] = {a[i].r,a[i].l,a[i].c};
	sort(b+1,b+h+1,cmp);
	memset(f,0x3f,sizeof f);
	for (int i = 0; i <= w; i++)
		f[i][0] = 0;
	memset(y,0x3f,sizeof y);
	for (int i = 0; i <= w; i++)
		y[i][0] = 0;
	for (int i = 1; i <= w; i++)
	{
		int pot1 = 1,pot2 = 1,tot = 0;
		memset(p,0,sizeof p);
		memset(g,0,sizeof g);
		for (int j = 1; j <= w; j++)
		{
			while (pot1 <= h && a[pot1].l == j) update(1,1,w,a[pot1].l,a[pot1].r,-a[pot1].c),tot += a[pot1].c,pot1++;
			if (j >= i)
			{
				if (i == 1) f[j][i] = tot;
				else f[j][i] = query(1,1,w,1,j-1)+tot;
			}
			update(1,1,w,j,j,f[j][i-1]);
			while (pot2 <= h && b[pot2].l == j) update(1,1,w,b[pot2].r,b[pot2].l,b[pot2].c),tot -= b[pot2].c,pot2++;
		}
	}
	for (int i = 1; i <= w; i++)
	{
		int pot1 = h,pot2 = h,tot = 0;
		memset(p,0,sizeof p);
		memset(g,0,sizeof g);
		for (int j = w; j >= 1; j--)
		{
			while (pot2 >= 1 && b[pot2].l == j) update(1,1,w,b[pot2].r,b[pot2].l,-b[pot2].c),tot += b[pot2].c,pot2--;
			if (j <= w-i+1)
			{
				if (i == 1) y[j][i] = tot;
				else y[j][i] = query(1,1,w,j+1,w)+tot;
			}
			update(1,1,w,j,j,y[j][i-1]);
			while (pot1 >= 1 && a[pot1].l == j) update(1,1,w,a[pot1].l,a[pot1].r,a[pot1].c),tot -= a[pot1].c,pot1--;
		}
	}
	for (int i = 1; i <= w; i++)
		for (int j = i+1; j <= w; j++)
			f[j][i] = min(f[j][i],f[j-1][i]);
	for (int i = 1; i <= w; i++)
		for (int j = w-i; j >= 1; j--)
			y[j][i] = min(y[j][i],y[j+1][i]);
	int ans = 0;
	for (int i = 1; i <= w; i++)
	{
		int bl = i,br = i+mxp-1;
		if (br > w) break;
		int e = k;
		if (bl != mxl) e -= mxc;
		if (e < 0) continue;
		for (int j = 0; j < bl; j++)
		{
			int c = e-f[bl-1][j];
			if (c < 0) continue;
			int l = 0,r = w-br;
			while (l+1 < r)
			{
				int mid = (l+r)/2;
				if (y[br+1][mid] <= c) l = mid;
				else r = mid-1;
			}
			if (y[br+1][r] <= c) ans = max(ans,j+r);
			else ans = max(ans,j+l);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

终于自己会了个题/ll

考虑钦定一个集合 $S$ 是没有被覆盖的，求所有合法的 $S$ 中最大的 $|S|$ 即可，此时所有与 $S_i$ 有交的线段都会有贡献，并且这些线段必须被移动进一个间隔。枚举 $lim$，要求最大间隔 $\ge lim$，分别做，这个是不必要的，原因是你取最长线段长 $mx$，那么显然要求至少有一个间隔 $\ge mx$，因此不需要枚举 $lim$。将这个转述一下，转化为所有被 $[S_i+1,S_{i+1}-1]$ 包含的线段的权值和 $\ge k'=sum-k$，此时 $S_0=0,S_{m+1}=n+1$。

考虑改成最大化被包含的线段的权值和，然后直接 dp。$f_{i,j,0/1}$ 表示 $S_j=i$，是否已有间隔 $\ge mx$。扫描线 $j$，线段树维护一下 $f_{i,j-1,*}+w(j,r)$，每次求 $f_{r,j,*}$，时间复杂度 $\mathcal O(n^2\log n)$。

---

## 作者：shenxindi (赞：0)

下文中 $m=h,n=w$。

设最长的墙编号为 $p$（若有多个最长的则随便选择一个）。发现除了 $p$ 以外的其他墙若被解锁则都可以使其被 $p$ 包含，则解锁除了 $p$ 以外的其他墙等价于删掉这个墙。

考虑枚举 $p$ 最后所在的位置，那么剩下可能被激光照到的位置是一段前缀和一段后缀。那么我们可以考虑预处理前缀和后缀的答案。

下文中的墙均不考虑 $p$。

设 $f_{i,j,0}$ 为只考虑右端点在 $[1,i]$ 的墙，第 $1$ 到 $i$ 列中有 $j$ 列能被激光照到，且被激光照到的编号最大的位置为 $i$ 的最小花费。不难发现 $f_{i,j,0}=\min\limits_{k=0}^{i-1}f_{k,j-1,0}+w_1(k+1,i-1)+w_2(i)$，其中 $w_1(l+1,r)$ 为右端点在 $[l+1,r]$ 且左端点小于等于 $l$ 的墙的花费总和，$w_2(i)$ 为右端点为 $i$ 的墙的花费总和。边界是 $f_{0,0,0}=0,\forall 1\le i\le n,f_{0,i,0}=\infty$。

直接转移是 $\mathcal O(n^3)$ 的，考虑优化。发现 $\min\limits_{k=0}^{i-1}f_{k,j-1,0}+w_1(k+1,i-1)$ 只需要支持单点修改、区间加和区间查询最小值即可，所以可以对每个 $j$ 开一棵线段树维护。然后计算 $w_2(i)$ 是简单的，这样我们就可以就可以 $\mathcal O(n^2\log n)$ 预处理所有 $f_{i ,j,0}$。

再设一个 $f_{i,j,1}$ 为后缀的花费，转移同理，这样我们就预处理出了前后缀的所有花费。

回到原问题，枚举 $p$ 的左端点为 $i$，那么左边答案为 $j$ 的最小花费为 $\min\limits_{k=0}^{i-1}f_{k,j,0}+w_1(k+1,i+len_p-1)$，发现 $w_1(k+1,i+len_p-1)=w_1(k+1,n)$，因为 $p$ 是最长的墙，所以右端点在 $[i+len_p,n]$ 的墙左端点必然大于 $k$。所以 $\min\limits_{k=0}^{i-1}f_{k,j,0}+w_1(k+1,i+len_p-1)$ 实际上就是预处理 $f_{i,j,0}$ 后第 $j$ 棵线段树上区间 $[0,i-1]$ 的最小值，右边的答案同理。剩下的就很简单了，先对于每个 $j$，求出左边答案为 $j$ 的最小花费，然后对于每个 $j$，求出右边答案为 $j$ 的最小花费，然后二分一下左边的答案即可。

总的时间复杂度为 $\mathcal O(n^2\log n)$。

需要略微卡常。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
#define ls (id<<1)
#define rs (id<<1|1)
#define mid (l+r>>1)
using namespace std;
const int N=2010,Inf=1e9+3;
int n,m,w,c[N],L,R,Id,f[N][N][2],fl[N],ans;
vector<pii > vec[N][2];
struct seg{
	int tree[N<<2],tag[N<<2];
	inline void pushdown(int id)
	{
		tree[ls]+=tag[id];
		tag[ls]+=tag[id];
		tree[rs]+=tag[id];
		tag[rs]+=tag[id];
		tag[id]=0;
	}
	inline void update1(int l,int r,int x,int v,int id)
	{
		if(x<l||x>r) return;
		if(l==r)
		{
			tree[id]=v;
			return;
		}
		pushdown(id);
		update1(l,mid,x,v,ls),update1(mid+1,r,x,v,rs);
		tree[id]=min(tree[ls],tree[rs]);
	}
	inline void update2(int l,int r,int x,int y,int v,int id)
	{
		if(x>y||l>y||r<x||tree[id]>w) return;
		if(l>=x&&r<=y)
		{
			tree[id]+=v;
			tag[id]+=v;
			return;
		}
		pushdown(id);
		update2(l,mid,x,y,v,ls),update2(mid+1,r,x,y,v,rs);
		tree[id]=min(tree[ls],tree[rs]);
	}
	inline int query(int l,int r,int x,int y,int id)
	{
		if(x>y||l>y||r<x||tree[id]>w) return Inf;
		if(l>=x&&r<=y) return tree[id];
		pushdown(id);
		return min(query(l,mid,x,y,ls),query(mid+1,r,x,y,rs));
	}
}tr[N][2];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>m>>n>>w;
	for(int i=1;i<=m;i++)
	{
		int l,r;
		cin>>l>>r>>c[i];
		if(r-l>R-L) L=l,R=r,Id=i;
		vec[r][0].push_back(mkp(l,i));
		vec[l][1].push_back(mkp(r,i));
	}
	for(int i=1;i<=n;i++)
	{
		f[0][i][0]=Inf;
		tr[i][0].update1(0,n,0,Inf,1);
	}
	for(int i=1;i<=n;i++)
	{
		int s=0;
		for(pii j:vec[i][0])
		{
			if(j.se!=Id) s+=c[j.se];
		}
		for(int j=1;j<=i;j++)
		{
			f[i][j][0]=tr[j-1][0].query(0,n,0,i-1,1)+s;
		}
		for(int j=1;j<=i;j++)
		{
			tr[j][0].update1(0,n,i,f[i][j][0],1);
			for(pii k:vec[i][0])
			{
				if(k.se==Id) continue;
				tr[j][0].update2(0,n,k.fi,i-1,c[k.se],1);
			}
		}
		for(int j=i+1;j<=n;j++)
		{
			f[i][j][0]=Inf;
			tr[j][0].update1(0,n,i,Inf,1); 
		}
	}
	for(int i=1;i<=n;i++)
	{
		f[n+1][i][1]=Inf;
		tr[i][1].update1(1,n+1,n+1,Inf,1);
	}
	for(int i=n;i;i--)
	{
		int s=0;
		for(pii j:vec[i][1])
		{
			if(j.se!=Id) s+=c[j.se];
		}
		for(int j=1;j<=n-i+1;j++)
		{
			f[i][j][1]=tr[j-1][1].query(1,n+1,i+1,n+1,1)+s;
		}
		for(int j=1;j<=n-i+1;j++)
		{
			tr[j][1].update1(1,n+1,i,f[i][j][1],1);
			for(pii k:vec[i][1])
			{
				if(k.se==Id) continue;
				tr[j][1].update2(1,n+1,i+1,k.fi,c[k.se],1);
			}
		}
		for(int j=n-i+1+1;j<=n;j++)
		{
			f[i][j][1]=Inf;
			tr[j][1].update1(1,n+1,i,Inf,1); 
		}
	}
	for(int i=1;i-L+R<=n;i++)
	{
		int t;
		for(int j=0;j<=n;j++)
		{
			fl[j]=tr[j][0].query(0,n,0,i-1,1);
			if(fl[j]>w) break;
			t=j;
		}
		int nw=w-(i!=L)*c[Id];
		for(int j=max(ans-t+1,0ll);j<=n;j++)
		{
			int fr=tr[j][1].query(1,n+1,i-L+R+1,n+1,1);
			if(fr>nw) break;
			int nans=j+upper_bound(fl,fl+t+1,nw-fr)-fl-1;
			ans=max(ans,nans);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cosf (赞：0)

假设只有一个最长的区间。如果有多个，则可以任选一个。可以发现，如果我们解锁一个区间，则可以将它移到最长区间内部。因此，解锁可以视为删除该区间。

于是先考虑忽略最长区间的 dp。设 $\mathit{df}_{i, j}$ 表示从左往右 dp，上一个未被区间覆盖的点为 $i$，有 $j$ 个未覆盖点的最小花费，则容易列出 $\mathit{df}_{i, j} = \min_{l \lt i} \mathit{df}_{l, j - 1} + w_{l, i}$，其中 $w_{l, i}$ 表示所有左端点在 $(l, i]$，右端点在 $[i, w]$ 的 $c$ 值之和。

显然这可以用线段树维护。具体的，对每个 $j$ 维护 $\mathit{df}_{?, j}$ 的区间 $\min$，并且支持单点修改（把当前值加入）、区间加即可（修改 $w$）。则这一部分复杂度为 $O(n^2\log n)$。

考虑加入最长区间。记 $\mathit{dpf}_{i, j} = \min_{l \le i} \mathit{df}_{l, j}$（即前缀 $\min$），然后倒着做一边 $\mathit{dpb}$。当最长区间覆盖 $[l, r]$ 时，我们只需枚举 $l$ 左侧有几个未覆盖的点，再二分出右边的数量即可。复杂度仍然是 $O(n^2\log n)$。

```cpp

#define MAXN 2005

template <typename T>
constexpr T INF = numeric_limits<T>::max() >> 4;

template <typename T>
inline T &chkmin(T &a, T b);

template <typename T>
inline T &chkmax(T &a, T b);

using ll = long long;

int h, w;

ll k;

struct Seg
{
    int l, r;
    ll c;
} v[MAXN];
vector<int> ss[MAXN], se[MAXN];

ll dpf[MAXN][MAXN], dpb[MAXN][MAXN];

struct SegTree
{
    struct Tree
    {
        ll m, t;
    } t[MAXN << 2];

    void build(int p, int l, int r, ll v);

    void add(int p, int l, int r, int ql, int qr, ll v);

    void assign(int p, int l, int r, int q, ll v);

    ll query(int p, int l, int r, int ql, int qr);
} t[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> h >> w >> k;
    for (int i = 1; i <= h; i++)
    {
        cin >> v[i].l >> v[i].r >> v[i].c;
    }
    sort(v + 1, v + h + 1, [] (Seg &a, Seg &b) {
        if (a.r - a.l == b.r - b.l)
        {
            return a.c > b.c;
        }
        return a.r - a.l > b.r - b.l;
    });
    memset(dpf, 0x3f, sizeof(dpf));
    memset(dpb, 0x3f, sizeof(dpb));
    // forward
    dpf[0][0] = 0;
    for (int i = 2; i <= h; i++)
    {
        ss[v[i].l].push_back(i);
        se[v[i].r + 1].push_back(i);
    }
    for (int i = 0; i < w; i++)
    {
        t[i].build(1, 0, w, INF<ll>);
    }
    t[0].assign(1, 0, w, 0, 0);
    for (int i = 1; i <= w; i++)
    {
        for (int p : ss[i])
        {
            for (int j = 0; j < w; j++)
            {
                t[j].add(1, 0, w, 0, i - 1, v[p].c);
            }
        }
        for (int p : se[i])
        {
            for (int j = 0; j < w; j++)
            {
                t[j].add(1, 0, w, 0, v[p].l - 1, -v[p].c);
            }
        }
        for (int j = 1; j <= w; j++)
        {
            dpf[i][j] = t[j - 1].query(1, 0, w, 0, i - 1);
            if (j < w)
            {
                t[j].assign(1, 0, w, i, dpf[i][j]);
            }
            chkmin(dpf[i][j], dpf[i - 1][j]);
        }
        dpf[i][0] = 0;
    }
    // backward
    dpb[w + 1][0] = 0;
    for (int i = 1; i <= w + 1; i++)
    {
        ss[i].clear();
        se[i].clear();
    }
    for (int i = 2; i <= h; i++)
    {
        ss[v[i].r].push_back(i);
        se[v[i].l - 1].push_back(i);
    }
    for (int i = 0; i < w; i++)
    {
        t[i].build(1, 1, w + 1, INF<ll>);
    }
    t[0].assign(1, 1, w + 1, w + 1, 0);
    for (int i = w; i; i--)
    {
        for (int p : ss[i])
        {
            for (int j = 0; j < w; j++)
            {
                t[j].add(1, 1, w + 1, i + 1, w + 1, v[p].c);
            }
        }
        for (int p : se[i])
        {
            for (int j = 0; j < w; j++)
            {
                t[j].add(1, 1, w + 1, v[p].r + 1, w + 1, -v[p].c);
            }
        }
        for (int j = 1; j <= w; j++)
        {
            dpb[i][j] = t[j - 1].query(1, 1, w + 1, i + 1, w + 1);
            if (j < w)
            {
                t[j].assign(1, 1, w + 1, i, dpb[i][j]);
            }
            chkmin(dpb[i][j], dpb[i + 1][j]);
        }
        dpb[i][0] = 0;
    }

    int res = 0;
    for (int l = 1, r = v[1].r - v[1].l + 1; r <= w; l++, r++)
    {
        ll c = l == v[1].l ? 0 : v[1].c;
        for (int j = 0; j < l; j++)
        {
            if (dpf[l - 1][j] + c <= k)
            {
                chkmax(res, j + int(upper_bound(dpb[r + 1], dpb[r + 1] + (w - r + 1), k - dpf[l - 1][j] - c) - dpb[r + 1] - 1));
            }
        }
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：lalaouye (赞：0)

感觉大部分人，包括我做这道题都会分析一些看起来很有用但是实际没啥用的性质。但是我们发现 $k$ 很大，无论怎么做都很难直接调整。

由于这题是区间问题，我们考虑对于一个选择状态去求最小代价，比如我们钦定了若干个不交区间被覆盖，考虑分析它，发现首先只有完全被包含的积木需要移动，其次这些区间中必须存在一个区间比最长积木长。

于是我们考虑 dp，设 $f(i,j,0/1)$ 表示考虑到第 $i$ 个位置，一共有 $j$ 个位置被覆盖，有无区间不短于最长积木的最小花费。

考虑转移钦定选择区间，发现能互相转移的区间 $i-j$ 的结果，于是可以对于每个 $i-j$ 用一棵线段树维护，时间复杂度 $\mathcal{O}(n^2\log n)$。

---

