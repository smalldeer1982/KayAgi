# Good Pairs

## 题目描述

You are given an array $ a $ consisting of $ n $ integers and an integer $ k $ .

A pair $ (l,r) $ is good if there exists a sequence of indices $ i_1, i_2, \dots, i_m $ such that

- $ i_1=l $ and $ i_m=r $ ;
- $ i_j < i_{j+1} $ for all $ 1 \leq j < m $ ; and
- $ |a_{i_j}-a_{i_{j+1}}| \leq k $ for all $ 1 \leq j < m $ .

Find the number of pairs $ (l,r) $ ( $ 1 \leq l \leq r \leq n $ ) that are good.

## 说明/提示

In the first test case, good pairs are $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,2) $ , $ (2,3) $ , and $ (3,3) $ .

In the second test case, good pairs are $ (1,1) $ , $ (1,3) $ , $ (1,4) $ , $ (2,2) $ , $ (2,3) $ , $ (2,4) $ , $ (3,3) $ , $ (3,4) $ and $ (4,4) $ . Pair $ (1,4) $ is good because there exists a sequence of indices $ 1, 3, 4 $ which satisfy the given conditions.

## 样例 #1

### 输入

```
4
3 0
1 1 1
4 2
4 8 6 8
6 4
7 2 5 8 3 8
20 23
110 57 98 14 20 1 60 82 108 37 82 73 8 46 38 35 106 115 58 112```

### 输出

```
6
9
18
92```

# 题解

## 作者：Alex_Wei (赞：14)

首先，如果路径先下降后上升，即 $a_x > a_y < a_z$，则 $x$ 可达 $z$。因此，路径上所有点的权值 **单调不降** 或 **单调不增**。这两个问题解法几乎完全相同，且仅在 $a_i = a_j$ 时重叠。接下来只讨论单调不降的情况，此时 $a_i \leq a_j$。

- 若 $a_j\leq a_i + k$，则 $i$ 直接可达 $j$。
- 若 $a_j > a_i + k$，则 $i$ 会跳到第一个满足 $a_i\leq a_{p_i}\leq a_i + k$ 的后继 $p_i$，这样显然是不劣的。

对权值从大到小扫描线，用 `set` 维护权值落在 $[v, v + k]$ 的所有位置，即可快速求出 $p_i$。

关于求答案，难道我们要求出 $a_{p_i}$ 所有 $a_j > a_i + k$ 且可达的位置 $j$ 吗？其实不然。考虑以 $l = p_i$ 的合法对数量，一定满足 $a_r \geq a_{p_i}$。而 $a_i\leq a_j < a_{p_i}$ 的 $j$ 是一步可达的，所以 $l = i$ 的合法对数量，即 $l = p_i$ 的合法对数量，加上 $j > i$ 且 $a_i\leq a_j < a_{p_i}$ 的 $j$ 的数量，容易 DP + BIT 维护。

时间复杂度 $\mathcal{O}(n\log V)$。[代码](https://codeforces.com/contest/1762/submission/185408338)。

---

## 作者：KSCD_ (赞：6)

### 思路
发现若合法子序列的三个连续元素 $x,y,z$ 满足 $a_x\ge a_y,a_y\le a_z$，那么一定有 $\left| a_z-a_x\right|\le k$，可以删掉中间的 $a_y$，$a_x\le a_y,a_y\ge a_z$ 的也一样。所以所有合法子序列均可通过删除操作变得单调不增或单调不降，因此只考虑单调序列即可。

显然单调不增和单调不降两种序列只会在 $a_l=a_r$ 时重复计算，因此分别计算后减去所有的重复贡献即可。可以先计算单调不增的区间数，然后进行 $a_i\leftarrow P-a_i+1$ 的转化（$P$ 为 $a_i$ 的值域），就把原来的单调不降变成了单调不增，再做一遍即可。

考虑怎么处理这个序列，发现对于 $i$ 后面第一个 $a_i\le a_j\le a_i+k$ 的 $j$，如果直接接上这个数，对于后面继续选不小于 $a_j$ 的数一定不劣。那么设 $f_i$ 表示 $l=i$ 时单调不增序列的结尾 $r$ 的个数，可以直接先把 $f_i$ 累加上 $f_j$。

剩下的就只有 $j$ 后面小于 $a_j$ 的数，这些数不能接在 $a_j$ 后面，需要另外统计。根据 $j$ 是第一个合法数的定义，$j$ 前面已经不可能有 $[a_i,a_j]$ 内的数，所以需要另外统计的个数等价于 $i$ 后面在 $[a_i,a_j)$ 范围内数的个数。

现在需要求的是每个数后面的 $j$（代码中为 $nxt_i$），考虑按照 $a$ 的值从大到小处理，用 set 维护目前在 $[x,x+k]$ 范围内的数，求 $nxt$ 时在 set 中二分即可，需要注意 $a$ 值相等的位置要从后往前加入 set，才能在前面计算时找到后面相等的数。另外还需要维护每个数后面在 $[a_i,a_{nxt_i})$ 内的数，这个在倒序处理时维护权值树状数组即可实现。

另外还需要注意所有的清空都需要清空每个 $a_i$ 的贡献，而不是对整个数组清空，否则时间复杂度是假的。
### 代码
```cpp
#include<iostream>
#include<vector>
#include<set> 
#include<algorithm>
#define int long long
using namespace std;
const int N=5e5+10;
const int P=1e5;
int n,k,res,a[N],t[N],nxt[N],f[N];
set <int> pos;
vector <int> tp[N],tv; 
struct bit
{
	int b[N];
	int lowbit(int x){return x&(-x);}
	void add(int p,int x){for(;p<=P;p+=lowbit(p)) b[p]+=x;}
	int query(int p){int tr=0; for(;p;p-=lowbit(p)) tr+=b[p]; return tr;} 
}T;
void solv()
{
	for(int i=1;i<=n;i++)
	{
		if(tp[a[i]].empty()) tv.push_back(a[i]);
		tp[a[i]].push_back(i);
	}
	sort(tv.rbegin(),tv.rend()),pos.insert(n+1); int l=0;
	for(int x:tv)
	{
		while(tv[l]>x+k)
		{
			for(int p:tp[tv[l]]) pos.erase(p);
			l++; 
		}
		sort(tp[x].rbegin(),tp[x].rend());
		for(int p:tp[x]) nxt[p]=(*pos.lower_bound(p)),pos.insert(p);
	}
	for(int x:tv) tp[x].clear();
	tv.clear(),pos.clear();
	for(int i=n;i>=1;i--)
	{
		f[i]=1;
		if(nxt[i]!=n+1) f[i]=f[nxt[i]]+T.query(a[nxt[i]]-1)-T.query(a[i]-1)+1;
		T.add(a[i],1),res+=f[i];
	}
	for(int i=1;i<=n;i++) T.add(a[i],-1);
}
void sol()
{
	cin>>n>>k,res=0;
	for(int i=1;i<=n;i++) cin>>a[i],t[a[i]]++,res-=t[a[i]];
	solv();
	for(int i=1;i<=n;i++) t[a[i]]--,a[i]=P-a[i]+1;
	solv(),cout<<res<<'\n';
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int TT; cin>>TT;
	while(TT--) sol();
	return 0;
}
```

---

## 作者：Lgx_Q (赞：2)

一道很不错的题目。

首先发现，走过的路径如果不单调，即出现 $a_{i_1}<a_{i_2}>a_{i_3}$ 时，我们完全可以舍弃 $a_{i_2}$，直接从 $a_{i_1}$ 走到 $a_{i_3}$。一直这样舍弃下去，最后的路径一定是单调递增或递减的。

递增还是递减，取决于 $a_l$ 和 $a_r$ 的大小关系。

$a_l$ 和 $a_r$ 的大小关系有 $3$ 种：小于、大于、等于。

这里我的方法是先算小于等于、大于等于，再把等于（重复计算）的去掉。

不妨先算小于等于的对，大于等于的对子可以倒着再处理一遍。

枚举 $i=1...n$，当 $r=i$ 时，算他的左边有多少个符合要求的 $l$。

这里我也困绕了很久。看了眼标签，似乎应该往动态规划的方向想。

猜测状态应为 $f_i$ 表示当 $r=i$ 时左边合法的 $l$ 的个数。

转移很迷茫，应该找一个“基准”，围绕“基准”转移。

于是发现：可以拿左边离 $i$ 最近的 $j$，满足 $a_j\le a_i$ 并且 $a_i\le a_j+k$，作为“基准”。

那么合法的 $l$ 有四种情况：

1. 在 $j$ 和 $i$ 之间。这种情况不可能，因为 $j$ 和 $i$ 之间没有路径能承接 $a_i$（$a_i$ 与他们的差都大于 $k$），舍去。

2. 在 $j$ 左边，并且值域在 $(a_j,a_i]$ 范围。这部分可以直接用线段树维护。（注意不用考虑 $j$ 和 $i$ 之间值域在 $(a_j,a_i]$ 的数）

3. 在 $j$ 左边，并且值域在 $[1,a_j]$ 之间。这部分可以直接拿 $f_j$ 来转移。

4. $l=j$。

只需要把四种情况（严格来说是后三种）的方案数全部加起来即可。

至于如何查找 $j$，可以再次用权值线段树维护数字范围在 $[a_i-k,a_i]$ 种的最大下标。

注意一下，因为是多组数据，所以必须再写一个线段树（因为有维护最值）撤销函数（反正我是这样写）。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=5e5+10;
ll t,n,m,a[maxn],f[maxn],g[maxn],sum[maxn],mn[maxn],cnt[maxn];
void modify(ll p,ll l,ll r,ll x,ll v)
{
	sum[p]++;
	if(l==r)
	{
		mn[p]=min(mn[p],v);
		return;
	}
	ll mid=l+r>>1;
	if(x<=mid) modify(p<<1,l,mid,x,v);
	else modify(p<<1|1,mid+1,r,x,v);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
void chx(ll p,ll l,ll r,ll x)
{
	sum[p]=0;
	mn[p]=1e17;
	if(l==r) return;
	ll mid=l+r>>1;
	if(x<=mid) chx(p<<1,l,mid,x);
	else chx(p<<1|1,mid+1,r,x);
}
ll query(ll p,ll l,ll r,ll ql,ll qr)
{
	if(ql<=l&&r<=qr) return sum[p];
	if(r<ql||qr<l) return 0;
	ll mid=l+r>>1;
	return query(p<<1,l,mid,ql,qr)+query(p<<1|1,mid+1,r,ql,qr);
}
ll find(ll p,ll l,ll r,ll ql,ll qr)
{
	if(ql<=l&&r<=qr) return mn[p];
	if(r<ql||qr<l) return 1e17;
	ll mid=l+r>>1;
	return min(find(p<<1,l,mid,ql,qr),find(p<<1|1,mid+1,r,ql,qr));
}
int main()
{
	scanf("%lld",&t);
	for(ll i=1;i<=4e5;i++) mn[i]=1e17;
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		ll ans=n;
		for(ll i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			ans-=cnt[a[i]];
			++cnt[a[i]];
			ll pos=-find(1,1,1e5,a[i]-m,a[i]);
			if(pos>0) f[i]=query(1,1,1e5,a[pos]+1,a[i])+f[pos]+1;
			else f[i]=0;
			modify(1,1,1e5,a[i],-i);
		}
		for(ll i=1;i<=n;i++) chx(1,1,1e5,a[i]);
		for(ll i=n;i;i--)
		{
			ll pos=find(1,1,1e5,a[i]-m,a[i]);
			if(pos<=n) g[i]=query(1,1,1e5,a[pos]+1,a[i])+g[pos]+1;
			else g[i]=0;
			modify(1,1,1e5,a[i],i);
		}
		for(ll i=1;i<=n;i++)
		{
			ans+=f[i]+g[i];
			chx(1,1,1e5,a[i]);
			cnt[a[i]]=0;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Little09 (赞：2)

这下第一步都没想到，胡了个很麻烦的做法。下面写的是官方题解给出的较简单的方法。

考虑一个事实：走过的路径上的权值一定单调递增，或单调递减，或只有两个数且相等。

对于一对 $(l,r)$，假设 $a_l<a_r$，那么我们从 $l$ 向 $r$ 走的过程中，如果某时刻 $a$ 减少了，显然是不优的。反过来也是同理，只有 $a_l=a_r$ 需要特判。

接下来我们就不用管绝对值了。先考虑满足 $a_l<a_r$ 的点对数，对于 $a_l>a_r$ 我们只要把序列 reverse 一下再跑一遍。

也就是现在 $i$ 能走到 $j$ 的条件是 $a_i<a_j\le a_i+k$。考虑从后往前做，假设位置 $i$ 往后走能走到的点的个数为 $dp_i$（不算自己）。我们考虑对于每个位置 $i$，找到它后面第一个满足这个条件的 $j$。可以发现 $dp_i=dp_j+calc(i,n,a_i+1,a_j)$，其中 $calc(l,r,x,y)$ 表示有多少个 $i$ 满足 $l\le i\le r$ 且 $x\le a_i\le y$。

我们开一个权值线段树维护每个权值有几个、每个权值对应的最小下标是多少。就可以方便地维护。

```cpp
// Author: Little09
// Problem: F. Good Pairs
// Contest: Codeforces - Codeforces Round #838 (Div. 2)
// URL: https://codeforces.com/contest/1762/problem/F
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Start Time: 2022-12-17 21:02:45
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N=500005,M=5e5;
int n,m; 
int a[N],c[N],dp[N];
int mn[N*31],lc[N*31],rc[N*31],tot,s[N*31];
void init()
{
	for (int i=0;i<=tot;i++) mn[i]=N,lc[i]=0,rc[i]=0,s[i]=0;
	tot=0;
}
inline void push_up(int u)
{
	s[u]=s[lc[u]]+s[rc[u]];
	mn[u]=min(mn[lc[u]],mn[rc[u]]);
}
int update(int u,int l,int r,int x,int y)
{
	if (!u) u=++tot;
	if (l==r)
	{
		s[u]++,mn[u]=min(mn[u],y);
		return u;
	}
	int mid=(l+r)>>1;
	if (x<=mid) lc[u]=update(lc[u],l,mid,x,y);
	else rc[u]=update(rc[u],mid+1,r,x,y);
	push_up(u);
	return u;
}
int ask(int u,int L,int R,int l,int r)
{
	if (!u||l>r) return N;
	if (l<=L&&R<=r) return mn[u];
	int mid=(L+R)>>1,res=N;
	if (l<=mid) res=min(res,ask(lc[u],L,mid,l,r));
	if (mid<r) res=min(res,ask(rc[u],mid+1,R,l,r));
	return res;
}
int query(int u,int L,int R,int l,int r)
{
	if (!u||l>r) return 0;
	if (l<=L&&R<=r) return s[u];
	int mid=(L+R)>>1,res=0;
	if (l<=mid) res+=query(lc[u],L,mid,l,r);
	if (mid<r) res+=query(rc[u],mid+1,R,l,r);
	return res;
}

ll work()
{
	init();
	int rt=0;
	ll res=0;
	for (int i=n;i>=1;i--)
	{
		int u=ask(rt,1,M,a[i]+1,a[i]+m);
		if (u==N) dp[i]=0;
		else dp[i]=dp[u]+query(rt,1,M,a[i]+1,a[u]);
		rt=update(rt,1,M,a[i],i);
		res+=dp[i];
	}
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	for (int i=0;i<N*31;i++) mn[i]=N;
	int T;
	cin >> T;
	while (T--) 
	{
		cin >> n >> m;
		for (int i=1;i<=n;i++) cin >> a[i];
		for (int i=1;i<=n;i++) c[a[i]]++;
		ll ans=0;
		for (int i=1;i<=n;i++) ans+=1ll*c[a[i]]*(c[a[i]]+1)/2,c[a[i]]=0;
		ans+=work();
		reverse(a+1,a+n+1);
		ans+=work();
		cout << ans << "\n";
	}
	return 0;
}


```


---

## 作者：冷却心 (赞：0)

为避免 corner case，哥们先把 $a_l=a_r$ 的区间单独计算，开一个桶记录每个数的个数即可。下文中便不讨论等于的情况。

容易发现对于一个合法的 $[l,r]$，若 $a_l<a_r$，那么一定存在一个单调严格递增子序列连接 $a_l,a_r$，$a_l>a_r$ 同理。

下文哥们只讨论上升情况，下降则把序列在值域上翻转即可。

对于 $a_p$，哥们考虑找到一个 $q$ 满足 $q$ 是 $p$ 之后第一个权值 $a_q \in (a_p,a_p+k]$ 之间的数。容易发现如果每个点向他后面所有落在这个区间的数连边，那么 $l \to r$ 的路径会有多条，重复计入答案。于是我们钦定：如果 $a_p$ 跳向的下一个点的权值 $w > a_q$，那么我们钦定它一定先跳到 $a_q$ 再跳到 $w$，否则一步跳到 $w$。这样任意两个点的路径就唯一了。

总结一下上一段的做法，也就是哥们对每个点 $p$ 找到他后面第一个权值之差小于等于 $k$ 的点 $q$，并使得 $p$ 向 $q$ 连边，边权为 $p$ 之后权值落在 $(a_p,a_q]$ 的点的个数。连边表示向后跳到 $q$，边权则表示如果不跳到 $q$，那么一步就能到达的点的个数。我们钦定 $q$ 是 $p$ 的父亲，那么这形成了一个森林，答案就是每个点到它的根的边权和。

寻找 $q$ 是一个单点赋值区间 $\min$，求个数是一个单点加法区间求和，都可以用线段树维护。统计答案的边权和事实上直接倒着扫一遍数组即可，然后做完了。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e5 + 10;
int n, K, A[N], m = 1e5, cnt[N];

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
int tr1[N << 2], tr2[N << 2];
void update1(int p, int l, int r, int x, int k) {
	if (x > r || x < l) return ;
	if (l == r) { tr1[p] = k; return ; }
	int mid = (l + r) >> 1; 
	update1(ls(p), l, mid, x, k); update1(rs(p), mid + 1, r, x, k);
	tr1[p] = min(tr1[ls(p)], tr1[rs(p)]); return ;
}
int query1(int p, int l, int r, int x, int y) {
	if (x > r || y < l) return 1e9;
	if (x <= l && y >= r) return tr1[p];
	int mid = (l + r) >> 1;
	return min(query1(ls(p), l, mid, x, y), query1(rs(p), mid + 1, r, x, y));
}
void update2(int p, int l, int r, int x, int k) {
	if (x > r || x < l) return ;
	if (l == r) { tr2[p] += k; return ; }
	int mid = (l + r) >> 1; 
	update2(ls(p), l, mid, x, k); update2(rs(p), mid + 1, r, x, k);
	tr2[p] = tr2[ls(p)] + tr2[rs(p)]; return ;
}
int query2(int p, int l, int r, int x, int y) {
	if (x > r || y < l) return 0;
	if (x <= l && y >= r) return tr2[p];
	int mid = (l + r) >> 1;
	return query2(ls(p), l, mid, x, y) + query2(rs(p), mid + 1, r, x, y);
}
int nxt[N], W[N];
LL Solve() {
	for (int i = n; i >= 1; i --) {
		nxt[i] = query1(1, 1, m, A[i] + 1, A[i] + K);
		W[i] = (nxt[i] <= n ? query2(1, 1, m, A[i] + 1, A[nxt[i]]) : 0);
		update1(1, 1, m, A[i], i); update2(1, 1, m, A[i], 1);
	}
	for (int i = 1; i <= n; i ++) update1(1, 1, m, A[i], 1e9), update2(1, 1, m, A[i], -1);
	LL res = 0;
	for (int i = n; i >= 1; i --) {
		if (nxt[i] <= n) W[i] += W[nxt[i]];
		res += W[i];
	} return res;
}

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	memset(tr1, 0x3f, sizeof tr1);
	while (_ --) {
		cin >> n >> K; LL Ans = 0;
		for (int i = 1; i <= n; i ++) cin >> A[i], Ans += (++ cnt[A[i]]);
		for (int i = 1; i <= n; i ++) cnt[A[i]] --;
		Ans += Solve();
		for (int i = 1; i <= n; i ++) A[i] = m - A[i] + 1;
		Ans += Solve(); cout << Ans << "\n";
	}
	return 0;
}
```

---

## 作者：ADNAP (赞：0)

### Solution
~~现在交不了 RemoteJudge 很难受qaq~~。

观察到 $j$ 和 $i$ 合法等价于找到从 $j$ 到 $i$ 单调递增或递减的子序列。因为中间有下降的一定不优。

考虑将值域每 $k+1$ 分成一块（助于思考）。那么对于块内部，可以互相到达。另外对于每个数 $x$，$x$ 所在块的前一个块和后一个块也有部分值域满足要求。

考虑 dp，设状态为 $cnt_{i,0/1/2}$，其中，考虑到第 $i$ 个数，

- $cnt_{i,0}$ 表示与 $a_i$ 在同一块的个数（包括 $a_i$ 本身）
- $cnt_{i,1}$ 表示前一个数 $j$，满足与 $a_i$ 在同一块或者 $a_i-a_j \le k$ 的个数，后者即 $a_j \le a_i$ 的合法方案。
- $cnt_{i_2}$ 与 $cnt_{i,1}$ 类似，满足 $a_j$ 与 $a_i$ 在同一块或者 $a_j \ge a_i$ 的合法方案数。

对于 $cnt_{i,0}$，可以记录一下 $ls_{\frac{a_i}{(k+1)}}$ 表示在 $\frac{a_i}{(k+1)}$ 这一块中的上一个数。当然愿意的话也可以在线段树上面查。

对于 $cnt_{i,1}$ 和 $cnt_{i,2}$，我们要根据最后一个合法的 $j$ 转移。
记 $pre01_i$ 是值域在 $a_i$ 所在块的前一块中出现位置最后一个的合法 $j$；$pre1_i$ 是与 $a_i$ 在同一块的出现位置最后的合法 $j$。

若 $pre01_i \le pre1_i$，贡献由 $pre1_i$ 转移到 $i$；否则由 $pre01_i$ 转移到 $i$。

转移方程分别是：

$$cnt_{i,1}=cnt_{pre1_i,1}+cnt_{i,0}-cnt_{pre1_i,0}$$
$$cnt_{i,1}=cnt_{pre01,1}+cnt_{i,0}$$

$cnt_{i,2}$ 的转移同理。

因为合法的 $j$ 根据值域作为限制，我们要求的性质是下标最大值，所以可以将 $i$ 挂到值域线段树 $a_i$ 处，维护和查询区间下标最大值来实现。

按下标扫一遍，算完将 $i$ 塞到值域线段树上。

最后答案记在 $\sum (cnt_{i,1}+cnt_{i,2}-cnt_{i,0})$。因为 $cnt_{i,0}$ 已包含在前两者中。

实现过程中的细节包括但不限于：

- 手动清空数组。
- 建一个值域全局的线段树，只建一次即可。
- 扫一遍数组 $a$ 来清空线段树。
### Code
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=5e5+1e2;
const ll inf=0;
ll T;
ll n,k;
ll a[N];
inline ll read()
{
    ll s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
    return s*w;
}
inline void write(ll n)
{
    if(n<0)
    {
        putchar('-');
        n=-n;
    }
    if(n>9)write(n/10);
    putchar(char(n%10+'0'));
}
struct Tree
{
    ll l,r;
    ll mx;
    ll cnt;
}tr[N];
void pushup(ll u)
{
    tr[u].mx=max(tr[u<<1].mx,tr[u<<1|1].mx);
    tr[u].cnt=tr[u<<1].cnt+tr[u<<1|1].cnt;
}
void build(ll u,ll l,ll r)
{
    tr[u].l=l,tr[u].r=r,tr[u].mx=inf,tr[u].cnt=0;
    if(l==r)return ;
    ll mid=(l+r)>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
}
void modify(ll u,ll pos,ll v)
{
    if(tr[u].l>pos||tr[u].r<pos)return ;
    if(tr[u].l==pos&&tr[u].r==pos)
    {
        tr[u].cnt++;
        tr[u].mx=max(tr[u].mx,v);
        return ;
    }
    modify(u<<1,pos,v);
    modify(u<<1|1,pos,v);
    pushup(u);
}
void clear(ll u,ll pos)
{
    if(tr[u].l>pos||tr[u].r<pos)return ;
    if(tr[u].l==pos&&tr[u].r==pos)
    {
        tr[u].cnt=tr[u].mx=0;
        return ;
    }
    clear(u<<1,pos);
    clear(u<<1|1,pos);
    pushup(u);
}
ll query_Max(ll u,ll l,ll r)
{
    if(tr[u].l>r||tr[u].r<l)return inf;
    if(l<=tr[u].l&&tr[u].r<=r)return tr[u].mx;
    return max(query_Max(u<<1,l,r),query_Max(u<<1|1,l,r));
}
ll query_Cnt(ll u,ll l,ll r)
{
    if(tr[u].l>r||tr[u].r<l)return 0;
    if(l<=tr[u].l&&tr[u].r<=r)return tr[u].cnt;
    return query_Cnt(u<<1,l,r)+query_Cnt(u<<1|1,l,r);
}
ll cnt[N][4];
ll pre1[N],pre01[N],pre2[N],pre02[N];
ll ls[N];
signed main()
{
    build(1,0,1e5);
    T=read();
    while(T--)
    {
        n=read(),k=read();
        for(ll i=1;i<=n;i++)a[i]=read();
        ll ans=0;
        for(ll i=1;i<=n;i++)
        {
            ll hh=max(1ll,a[i]/(k+1)*(k+1)),tt=a[i]/(k+1)*(k+1)+k;
            cnt[i][0]=cnt[ls[a[i]/(k+1)]][0]+1;
            pre1[i]=query_Max(1,hh,a[i]);
            pre01[i]=query_Max(1,max(1ll,a[i]-k),hh-1);
            
            if(pre01[i]<=pre1[i])cnt[i][1]=cnt[pre1[i]][1]+cnt[i][0]-cnt[pre1[i]][0];
            else cnt[i][1]=cnt[pre01[i]][1]+cnt[i][0];
            
            pre2[i]=query_Max(1,a[i],tt);
            pre02[i]=query_Max(1,tt+1,min(100000ll,a[i]+k));
            
            if(pre02[i]<=pre2[i])cnt[i][2]=cnt[pre2[i]][2]+cnt[i][0]-cnt[pre2[i]][0];
            else cnt[i][2]=cnt[pre02[i]][2]+cnt[i][0];
            
            modify(1,a[i],i);
            ls[a[i]/(k+1)]=i;
            ans+=cnt[i][1]+cnt[i][2]-cnt[i][0];
        }
        for(ll i=1;i<=n;i++)ls[a[i]/(k+1)]=0;
        for(ll i=1;i<=n;i++)clear(1,a[i]);
        cout<<ans<<"\n";
    }
}
```

---

## 作者：ThisIsLu (赞：0)

首先可以注意到若 $a_l<a_r$，则你选出的子序列总是可以递增的，若 $a_l=a_r$ 则直接选这两个（或一个），若 $a_l>a_r$ 则你选出的子序列总是可以递减的。

所以你设 $dp_{i,0}$ 表示以 $i$ 为右端点，左端点的值小于等于 $a_i$，且这个区间好的左端点数量，$dp_{i,1}$ 表示左端点的值大于等于 $a_i$，且这个区间好的左端点数量。

不难注意到，设 $last_{i,0}$ 表示最大的 $j$ 满足 $a_i-k \le a_j \le i$ 且 $j<i$ 那么对于若 $[l,i]$ 合法且 $a_l \le a_{last_{i,0}}$ 则选出的子序列必然包含 $last_{i,0}$。

这意味着我们可以处理出 $last_{i,0}$，可以处理出 $[l,i]$ 合法且 $a_l \le a_{last_{i,0}}$ 的左端点数量。

而对于 $a_{last_{i,0}} <a_l \le a_i$ 且 $l<i$，$[l,i]$ 必然合法，直接加上即可。

$dp_{i,1}$ 同理。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
const int N=5e5,V=1e5;
int a[N+5],dp[N+5][2],tot,maxx[(V<<2)+5],sum[(V<<2)+5],ls[(V<<2)+5],rs[(V<<2)+5];
void update(int &x,int l,int r,int pos,int k){
	if(!x) x=++tot;
	maxx[x]=max(maxx[x],k);
	sum[x]++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) update(ls[x],l,mid,pos,k);
	else update(rs[x],mid+1,r,pos,k);
}
int mxquery(int x,int l,int r,int nl,int nr){
	if(nl>nr) return 0;
	if(!x) return 0;
	if(nl<=l&&r<=nr) return maxx[x];
	int mid=(l+r)>>1,res=0;
	if(nl<=mid) res=mxquery(ls[x],l,mid,nl,nr);
	if(mid<nr) res=max(res,mxquery(rs[x],mid+1,r,nl,nr));
	return res;
}
int squery(int x,int l,int r,int nl,int nr){
	if(nl>nr) return 0;
	if(!x) return 0;
	if(nl<=l&&r<=nr) return sum[x];
	int mid=(l+r)>>1,res=0;
	if(nl<=mid) res=squery(ls[x],l,mid,nl,nr);
	if(mid<nr) res+=squery(rs[x],mid+1,r,nl,nr);
	return res;
}
int rt;
void solve(){
	cin>>n>>k;
	for(int i=1;i<=tot;i++) maxx[i]=sum[i]=ls[i]=rs[i]=0;
	tot=rt=0;
	long long ans=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		int ysc=mxquery(rt,1,V,max(1,a[i]-k),a[i]),csy=mxquery(rt,1,V,a[i],min(V,a[i]+k));
		dp[i][0]=dp[ysc][0]+1;
		if(ysc) dp[i][0]+=squery(rt,1,V,a[ysc]+1,a[i]);
		dp[i][1]=dp[csy][1]+1;
		if(csy) dp[i][1]+=squery(rt,1,V,a[i],a[csy]-1);
		update(rt,1,V,a[i],i);
		ans+=dp[i][0]+dp[i][1]-squery(rt,1,V,a[i],a[i]);
	}
	cout<<ans<<"\n";
}
int main(){
	cin>>T;
	while(T--) solve();
	return 0;
} 
```

---

## 作者：Anonymely (赞：0)

找到关键性质：若 $a_x \ge a_y \le a_z, |a_x - a_y| \ge k, |a_y -a_z|\ge k$，则 $|a_x-a_z|\ge k$，这意味着子序列一定不增或不减，两个单独做即可，下面以单调不减为例。

考虑固定左端点如何计算答案，找到第一个 $j$ 满足 $a_l \le a_j \le a_i + k$，发现所有满足 $a_r \ge a_j$ 的方案都在其中，剩下的是 $a_r \in [a_i, a_j)$，对于这一部分一定满足 $|a_r -a_l| \ge k$，于是只需要对这一部分计数即可。

找到 $j$ 和求后缀内一段值域区间个数都可以线段树维护，复杂度 $O(n \log n)$。

[submission](https://codeforces.com/problemset/submission/1762/284120470)

---

## 作者：SFlyer (赞：0)

考虑怎么不重不漏的计算每一个区间。可以发现，每一个可行的区间一定是可以找到 $i_1\sim i_k$ 使 $a_{i_1}\sim a_{i_k}$ 是单调不增或者不降的。

这是因为，考虑有一个地方比两边都要小，那么我们可以直接忽略它，两边的差一定在 $k$ 以内。比两边都大同理。因此我们现在就要算单调不增个数加单调不降减去 $a_l=a_r$ 的 $[l,r]$ 个数。现在只讨论一种单调不降的。

考虑把序列转化成平面上的点，也即 $(i,a_i)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0jm28wau.png)

设 $f_r$ 为右端点为 $r$ 的方案数，先算出 $lst_r$ 为在左边第一个 $a_{i}\in [a_i-k,a_i]$ 的位置 $i$。则 $f_r$ 可以从 $f_{lst_r}$ 转移过来。上图这种情况下，如果我们想要算 $r=5$ 的答案，$lst_5=4$，所以 $f_5$ 有一部分是 $f_4$ 贡献的。但是容易发现 $(3,5)$ 这个点没有被算进去，因此还要加上前面 $a_i\in [a_{lst_r}+1,a_i]$ 的 $i$ 的个数。可以直接加，因为这个区间一定是可以一步到达的。

找 $lst_r$ 可以用线段树，后面的部分可以用树状数组。

时间复杂度 $\mathcal{O}(n\log n)$。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e5+5;
const int A = 1e5+5;

int n,k,a[N],lu[N],ld[N],bit[A],f[N],m=A-5;

void M(int p,int v){
	while (p<A){
		bit[p]+=v,p+=p&-p;
	}
}

int Q(int p){
	int res=0;
	while (p){
		res+=bit[p],p-=p&-p; 
	}
	return res;
}

int S(int l,int r){
	return Q(r)-Q(l-1);
}

int t[N<<2];

void pu(int k){
	t[k]=max(t[k<<1],t[k<<1|1]);
}

void upd(int k,int l,int r,int p,int v){
	if (l==r){
		t[k]=v;
		return;
	}
	int mid=l+r>>1;
	if (p<=mid) upd(k<<1,l,mid,p,v);
	else upd(k<<1|1,mid+1,r,p,v);
	pu(k);
}

int qy(int k,int l,int r,int ql,int qr){
	if (ql<=l && r<=qr){
		return t[k];
	}
	if (r<ql || l>qr){
		return 0;
	}
	int mid=l+r>>1;
	return max(qy(k<<1,l,mid,ql,qr),qy(k<<1|1,mid+1,r,ql,qr));
}

void solve(){
	cin>>n>>k;
	map<int,ll> mp;
	for (int i=1; i<=n; i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	for (int i=1; i<=n; i++){
		int l=max(1,a[i]-k),r=a[i];
		lu[i]=qy(1,1,m,l,r);
		l=a[i],r=min(m,a[i]+k);
		ld[i]=qy(1,1,m,l,r);
		upd(1,1,m,a[i],i);
	}
	for (int i=1; i<=n; i++){
		upd(1,1,m,a[i],0);
	}
	ll ans=0;
	for (int i=1; i<=n; i++){
		if (lu[i]==0){
			f[i]=1,ans++;
			M(a[i],1);
			continue;
		}
		f[i]=f[lu[i]]+S(a[lu[i]]+1,a[i])+1;
		ans+=f[i];
		M(a[i],1);
	}
	for (int i=1; i<=n; i++) M(a[i],-1);
	for (int i=1; i<=n; i++){
		if (ld[i]==0){
			f[i]=1,ans++;
			M(a[i],1);
			continue;
		}
		f[i]=f[ld[i]]+S(a[i],a[ld[i]]-1)+1;
		ans+=f[i];
		M(a[i],1);
	}
	for (int i=1; i<=n; i++) M(a[i],-1);
	for (auto u : mp){
		ll c=u.second;
		ans-=c*(c+1)/2;
	}
	cout<<ans<<"\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		solve();
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

不妨设 $a_l<a_r$。设 $nxt_i$ 表示 $i$ 后面第一个满足 $a_{nxt_i}>a_i$ 且 $a_{nxt_i}-a_i\leq k$ 的位置。对于所有 $i\to nxt_i$ 建边。$[l,r]$ 合法当且仅当第一个向后跳到的位置 $j$ 使得 $a_r-a_j\leq k$ 的 $j\leq r$。

考虑可以跳到 $i$ 位置的 $l$ 的初始数量 $cnt_i$。不难发现所有 $r\geq i$ 且 $a_i\leq a_r<a_{nxt_i}$ 均可以被 $cnt_i$ 个 $l$ 到达。

$O(n\log n)$ 计算 $nxt_i$ 后用线段树计算 $a_i\leq a_r<a_{nxt_i}$ 的数量即可。$a_l>a_r$ 同理。总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int n,k,a[500005],cnt[500005],to[500005],ans,val[500005];
int m=100000;
struct sgt1{
	int f[2000005];
	void pushdown(int i){
		if(f[i]!=-1){
			f[i*2]=f[i*2+1]=f[i];
			f[i]=-1;
		}
	}
	void change(int i,int l,int r,int ql,int qr,int v){
		if(ql>qr) return ;
		if(ql<=l&&r<=qr){
			f[i]=v;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,v);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,v);
	}
	int qry(int i,int l,int r,int pos){
		if(l==r) return f[i];
		pushdown(i);
		if(pos<=mid) return qry(i*2,l,mid,pos);
		else return qry(i*2+1,mid+1,r,pos);
	}
}tree1;
struct sgt2{
	int f[2000005];
	void change(int i,int l,int r,int pos,int cg){
		if(l==r){
			f[i]+=cg;
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos,cg);
		else change(i*2+1,mid+1,r,pos,cg);
		f[i]=f[i*2]+f[i*2+1];
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		return qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr);
	}
}tree2;
int solve(){
	ans=0;
	cin>>n>>k; for(int i=1;i<=n;i++) cin>>a[i],ans+=(++cnt[a[i]]);
	for(int i=1;i<=n;i++) cnt[a[i]]--;
	{
		for(int i=1;i<=n;i++) val[i]=1;
		tree1.f[1]=0;
		for(int i=n;i>=1;i--){
			to[i]=tree1.qry(1,1,m,a[i]);
			tree1.change(1,1,m,a[i]+1,min(a[i]+k,m),i);
//			cout<<i<<" "<<to[i]<<"\n";
		}
		for(int i=1;i<=n;i++) val[to[i]]+=val[i];
		for(int i=n;i>=1;i--){
			tree2.change(1,1,m,a[i],1);
			if(to[i]!=0){
				ans+=val[i]*tree2.qry(1,1,m,a[to[i]],a[i]-1);
			}
		}
		for(int i=1;i<=n;i++) tree2.change(1,1,m,a[i],-1);
	}
//	cout<<ans<<"\n";
	{
		for(int i=1;i<=n;i++) val[i]=1;
		tree1.f[1]=0;
		for(int i=n;i>=1;i--){
			to[i]=tree1.qry(1,1,m,a[i]);
			tree1.change(1,1,m,max(a[i]-k,1ll),a[i]-1,i);
//			cout<<i<<" "<<to[i]<<"\n";
		}
		for(int i=1;i<=n;i++) val[to[i]]+=val[i];
		for(int i=n;i>=1;i--){
			tree2.change(1,1,m,a[i],1);
			if(to[i]!=0){
				ans+=val[i]*tree2.qry(1,1,m,a[i]+1,a[to[i]]);
			}
		}
		for(int i=1;i<=n;i++) tree2.change(1,1,m,a[i],-1);
	}
	return ans;
}
signed main(){
	memset(tree1.f,-1,sizeof(tree1.f));
	int t; cin>>t;
	while(t--) cout<<solve()<<"\n";
	return 0;
}
```

---

