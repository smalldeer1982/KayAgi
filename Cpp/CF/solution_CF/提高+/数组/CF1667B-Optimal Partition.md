# Optimal Partition

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。你需要将 $a$ 划分为若干个连续且非空的子数组（总共有 $2^{n-1}$ 种划分方式）。

设 $s = a_l + a_{l+1} + \ldots + a_r$。对于子数组 $a_l, a_{l+1}, \ldots, a_r$，其价值定义如下：

- 如果 $s > 0$，则价值为 $(r-l+1)$；
- 如果 $s = 0$，则价值为 $0$；
- 如果 $s < 0$，则价值为 $-(r-l+1)$。

请问，采用最优划分方式时，所有子数组价值之和的最大值是多少？

## 说明/提示

测试点 $1$：一种最优划分方式为 $[1, 2]$，$[-3]$。$1+2>0$，因此 $[1, 2]$ 的价值为 $2$。$-3<0$，因此 $[-3]$ 的价值为 $-1$。$2+(-1)=1$。

测试点 $2$：最优划分方式为 $[0, -2, 3]$，$[-4]$，总价值为 $3+(-1)=2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3
1 2 -3
4
0 -2 3 -4
5
-1 -2 3 -1 -1
6
-1 2 -3 4 -5 6
7
1 -1 -1 1 -1 -1 1```

### 输出

```
1
2
1
6
-1```

# 题解

## 作者：Anguei (赞：14)

## 题意

给定一个数组 $a$，长度为 $n (1 \leq n \leq 5 \times 10^5)$，你需要将其分割为若干个连续的子数组，使所有子数组的*价值*总和最大。

定义 $\texttt{s(l, r)} = a_l + a_{l+1} + a_{l+2} + \cdots + a_r$，子数组 $a[l, r]$ 的*价值*是：
- $r-l+1$，$\texttt{s(l, r)} > 0$
- 0，$\texttt{s(l, r)} = 0$
- $-(r-l+1)$，$\texttt{s(l, r)} < 0$

## 思路

有意思的一道题目。

### 暴力

若忽略掉数据范围的限制，不难想到一种 $O(n^2)$ 的 dp 方案：
- 先无脑地把前缀和求出来;
- 设 $dp[i]$ 表示前 $i$ 个元素构成的子数组，划分后可产生的最大*价值*；
- 显然 $dp[0] = 0$，即空数组不产生*价值*；
- 考虑转移：枚举 $i, j (j < i)$，则 $dp[i] = \max\left( dp[j] + \texttt{calc(j + 1, i)} \right)$；
- 其中 $\texttt{calc(j + 1, i)}$ 表示子数组 $a[j + 1, r]$ 的*价值*，可以由定义计算；
- $dp[n]$ 就是答案。

```cpp
dp[0] = 0;
for (int i = 1; i <= n; ++i)
  for (int j = 0; j < i; ++j)
    dp[i] = std::max(dp[i], dp[j] + calc(j + 1, i));
print(dp[n]);
```

### 优化

上面的转移方程 $dp[i] = \max\left( dp[j] + \texttt{calc(j + 1, i)} \right)$ 包含了函数调用，有点麻烦，不妨把它拆开，于是产生了三个新的方程：
- $dp[i] = \max\left( dp[j] + (i-j) \right)$，$\texttt{sum(j + 1, i)} > 0$
- $dp[i] = \max\left( dp[j] \right)$，$\texttt{sum(j + 1, i)} = 0$
- $dp[i] = \max\left( dp[j] + (j-i) \right)$，$\texttt{sum(j + 1, i)} < 0$

而刚刚频繁出现的 $\texttt{sum(j + 1, i)}$ 又可以拆成 $s[i] - s[(j+1)-1] = s[i] - s[j]$。于是上面三个式子又可以移项、变形为：
- $dp[i] = \max\left( dp[j] - j \right) + i$，$s[i] > s[j]$
- $dp[i] = \max\left( dp[j] \right)$，$s[i] = s[j]$
- $dp[i] = \max\left( dp[j] + j \right) - i$，$s[i] < s[j]$

于是只需要动态维护 $dp[i] + i$，$dp[i]$，$dp[i] - i$ 的区间最大值即可。

首先对前缀和数组 $s$ 进行离散化，然后把 $s[j]$ 当成下标。每次查询坐标 $s[j]$ 之前（或之后）的区间最大值。当然，对于 $s[i] = s[j]$ 的情况，相当于查询 $s[j]$ 坐标的最大值。

建立三棵线段树，分别维护即可：第零棵维护 $dp[i] + i$，第一棵维护 $dp[i]$，第二棵维护 $dp[i] - i$。dp 数组更新完之后，再进入线段树修改区间最大值（单点修改）。

~~（又是三棵树，仿佛嗅到了 [CF1660F2](https://www.luogu.com.cn/problem/CF1660F2) 的味道）~~

## 代码

```cpp
struct SegTree {
  std::vector<ll> a;
  SegTree(int n) : a((n + 1) * 4, 0) { this->build(1, 1, n); }
#define lson ((o) << 1)
#define rson ((o) << 1 | 1)
  void build(int o, int l, int r) {
    if (l == r) return void(a[o] = -1e18);
    int mid = (l + r) / 2;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    a[o] = std::max(a[lson], a[rson]);
  }
  ll query(int o, int l, int r, int L, int R) {
    if (l >= L && r <= R) return a[o];
    int mid = (l + r) / 2;
    ll res = -1e18;
    if (L <= mid) res = std::max(res, query(lson, l, mid, L, R));
    if (R > mid) res = std::max(res, query(rson, mid + 1, r, L, R));
    return res;
  }
  void change(int o, int l, int r, int x, ll val) {
    if (l == r) return void(a[o] = std::max(a[o], val));
    int mid = (l + r) / 2;
    if (x <= mid)
      change(lson, l, mid, x, val);
    else
      change(rson, mid + 1, r, x, val);
    a[o] = std::max(a[lson], a[rson]);
  }
#undef lson
#undef rson
};

void solution() {
  int n;
  read(n);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) read(a[i]);
  std::vector<ll> s(n + 1);
  for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
  // 离散化前缀和数组 s
  std::vector<ll> vs(s.begin(), s.end());
  std::sort(vs.begin(), vs.end());
  std::map<ll, int> belong;
  int tot = 0;
  for (auto i : vs)
    if (!belong.count(i)) belong[i] = ++tot;
  // s2 是离散化后的 s
  std::vector<int> s2(n + 1);
  for (int i = 1; i <= n; ++i) s2[i] = belong[s[i]];

  auto chmax = [](auto& x, auto y) { x = std::max(x, y); };
  std::vector<SegTree> seg(3, SegTree(tot));
  // 下面这行相当于暴力代码的 dp[0] = 0
  for (int i = 0; i < 3; ++i) seg[i].change(1, 1, tot, belong[0], 0);
  for (int i = 1; i <= n; i++) {
    // 对应上述第一个转移方程
    if (s2[i] > 1) chmax(dp[i], seg[2].query(1, 1, tot, 1, s2[i] - 1) + i);
    // 第二个转移方程
    chmax(dp[i], seg[1].query(1, 1, tot, s2[i], s2[i]));
    // 第三个转移方程
    if (s2[i] < tot) chmax(dp[i], seg[0].query(1, 1, tot, s2[i] + 1, tot) - i);
    // 单点修改
    seg[0].change(1, 1, tot, s2[i], dp[i] + i);
    seg[1].change(1, 1, tot, s2[i], dp[i]);
    seg[2].change(1, 1, tot, s2[i], dp[i] - i);
  }
  print(dp[n]);
}
```

---

## 作者：Jjy123 (赞：9)

## 题目：
[题目传送门](https://www.luogu.com.cn/problem/CF1667B)
## 题意：
给定一个数组 $a$，长度为 $n$($1\le n\le 5\times 10^5$)，你需要将其分割为若干个连续的子数组，使所有子数组的价值总和最大。

定义：令 $ s=a_l+a_{l+1}+\cdots+a_rs=a_l+a_{l+1} +\cdots+a_r$ 一段子序列 $a_l ,a_{l+1} ,\cdots,a_r$ 的价值为：
- $（r−l+1）$ 若 $s>0$
- $0$ 若 $s=0$
- $-（r-l+1）$ 若 $s<0$

你通过某种划分能获得的最大价值和为多少?
## 思路
这是一道~~令人心累~~的题目（结尾有说）。


---

### 暴力
显然能想到一种 $O(n^2)$ 的方法，自然会 TLE，~~尽管限时4s~~。
### 优化
优先采用线段树优化。

可以通过上一道例题 [AT_Flat Subsequence](https://www.luogu.com.cn/problem/AT_abl_d) 的状态转移方程：
$$dp_i = _{j∈[l,r]}^{\max}(1+dp_j)$$

展开思考：
- 对于形如：$dp_i=_{ j∈[l,r]}^{\max}(A(i)+B(j))$，其中 $B(j)$ 往往与 $dp_j$ 有关。
- 可以用线段树优化 $DP$。
- 建一棵线段树优化 $DP$。

本题主要思路：
- 可以分别利用 $3$ 棵线段树，对 $max(dp_j-j)$、 $\max(dp_j)$、$\max(dp_j+j)$ 进行快速查寻。
- 讨论：
  - 求 $\max(dp_j-j)$，需要满足 $sum_j<sum_i$。
  - 如何快速找满足小于 $sum_i$ 的 $sum_j$ 呢？
  - 将所有的 $sum$ 数组离散化，假设离散化后 $pos=b_{sum_i}$，则只需查询 $[1,pos-1]$ 的范围。即 $res1 = tre1.query(1,pos-1)$。

推一推不难发现三个状态转移方程：
- $dp_i=\max(dp_j+(i-j)),sum(j+1,i)>0$
- $dp_i=\max(dp_j),sum(j+1,i)=0$
- $dp_i=\max(dp_j+(j-i)),sum(j+1,i)<0$

整理得：

- $dp_i=\max(dp_j-j)+i,s_i>s_j$
- $dp_i=\max(dp_j),s_i=s_j$
- $dp_i=\max(dp_j+j)-i,s_i<s_j$

只需动态维护 $dp_i+i,dp_i,dp_i-i$ 的区间最大值即可。

建立三棵树：$tre1,tre2,tre3$ 分别进行单点修改与区间、单点查询，最后只需输出 $dp_n$ 即是最终答案。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=500005;
ll n;
ll a[maxn];
ll num[maxn];
ll p[maxn];
ll tot;
map<ll,ll>mp;
ll x,y;
int dp[maxn];
struct node {
	ll sum[4*maxn+5];
	void build(int l,int r,int o) {
		if(l==r) {
			sum[o]=-1e9;
			return;
		}
		int mid=(l+r)/2;
		build(l,mid,o*2);
		build(mid+1,r,o*2+1);
		sum[o]=max(sum[o*2],sum[o*2+1]);
	}
	ll query(int l,int r,int o) {
		
		if(x<=l&&r<=y) {
			return sum[o];
		}
		int mid=(l+r)/2;
		ll ans=-1e9;
		if(x<=mid)ans=max(ans,query(l,mid,o*2));
		if(y>mid)ans=max(ans,query(mid+1,r,o*2+1));
		return ans;
	}
	void update(int l,int r,int o) {
		if(l==r) {
			sum[o]=max(sum[o],y);
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)update(l,mid,o*2);
		else update(mid+1,r,o*2+1);
		sum[o]=max(sum[o*2],sum[o*2+1]);
	}

} tre1,tre2,tre3;

void init() {
	for(int i = 1; i <= n; i++ )dp[i] = -1e9;
	dp[0]=0;
	mp.clear();
	tot=0;
}

int main() {
	int t;
	cin>>t;
	while(t--) {
		cin>>n;
		init();
		for(int i=1; i<=n; i++) {//dp[i]=max(dp[j])+1 a[i]-k<=a[j]<=a[j]+k
			cin>>a[i];
			num[i]=num[i-1]+a[i];
			p[i]=num[i];
		}
		num[n+1]=0;
		stable_sort(num+1,num+n+1+1);
		for(int i=1; i<=n+1; i++) {
			if(num[i]==num[i-1]&&i!=1)continue;
			mp[num[i]]=++tot;
		}
		tre1.build(1,tot,1);
		tre2.build(1,tot,1);
		tre3.build(1,tot,1);
		x=mp[0];y=dp[0];
	//	cout<<x<<' '<<y<<endl;
		tre1.update(1,tot,1);
		tre2.update(1,tot,1);
		tre3.update(1,tot,1);
		for(int i=1;i<=n;i++) {
			long long res1,res2,res3;
			res1=res2=res3=-1e9;
			//
			x=1,y=mp[p[i]]-1;
			if(y>=1){
				res1=tre1.query(1,tot,1);
			}
			x=y=mp[p[i]];
//			cerr<<x<<" "<<y<<"$$$"<<endl;
   			res2=tre2.query(1,tot,1);
   			x=mp[p[i]]+1,y=tot;
            if(x<=tot){
            	res3=tre3.query(1,tot,1);
			}
            //
			dp[i]=max(max(res1+i,res3-i),res2);
			//
			//
			x=mp[p[i]];
			y=dp[i]-i;
			tre1.update(1,tot,1);
			y=dp[i];
			tre2.update(1,tot,1);
			y=dp[i]+i;
			tre3.update(1,tot,1);
		}
		cout<<dp[n]<<endl;
	}
	return 0;
}
//Accumulated (    4    ) hours of debugging !!!!!
```
这串代码我调试历时 $4$ 小时！

注：[AC记录](https://vjudge.net/solution/58237336/sfMcs5hOTelaCMBAeOwv)

致谢 [enyyyyyyy](https://www.luogu.com.cn/user/961881)

---

## 作者：I_am_Accepted (赞：8)

### Analysis

发现很难有贪心策略（至少我没想到），所以就暴力 DP。

$f_i$ 表示 $a[1,i]$ 划分后的最大价值和，$s_i=\sum_{j=1}^ia_j$。

$$p(x)=\begin{cases}
1&x>0\\
0&x=0\\
-1&x<0
\end{cases}$$

$$\begin{cases}
f_0=0
\\
f_i=\max\limits_{j=0}^{i-1}(i-j)\cdot p(s_i-s_j)+f_j
\end{cases}$$

这样是 $O(n^2)$ 的，优化时发现 $p$ 阻碍了时间的优化。

将 $p$ 分类讨论

$$\begin{aligned}
f_i&=\max_{j=0}^{i-1}\begin{cases}
(i-j)+f_j&s_i>s_j
\\
f_j&s_i=s_j
\\
(j-i)+f_j&s_i<s_j
\end{cases}
\\&=\max_{j=0}^{i-1}\begin{cases}
i+(f_j-j)&s_i>s_j
\\
f_j&s_i=s_j
\\
-i+(f_j+j)&s_i<s_j
\end{cases}
\end{aligned}$$

然后就可以用 **两个 BIT（树状数组）** 维护 $s_i\ne s_j$ 部分 和 **一个离散化 $+$ 桶** 维护 $s_i=s_j$ 部分。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 500010
#define low (x&(-x))
const int inf=1e16;
int n,a[N],b[N],lim,c[2][N],qwq[N];
void add(bool T,int x,int y){
	while(x<=lim){
		ckmx(c[T][x],y);
		x+=low;
	}
}
int que(int T,int x){
	int res=-inf;
	while(x){
		ckmx(res,c[T][x]);
		x-=low;
	}
	return res;
}
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n) a[i]+=a[i-1];
	For(i,0,n) b[i]=a[i];
	sort(b,b+1+n);
	lim=unique(b,b+1+n)-b;
	For(i,0,n) a[i]=lower_bound(b,b+lim,a[i])-b+1;
//	For(i,0,n) cerr<<a[i]<<" "; cerr<<endl;
	For(i,1,lim) c[0][i]=c[1][i]=-inf;
	For(i,1,lim) qwq[i]=-inf;
	add(0,a[0],0);
	add(1,1+lim-a[0],0);
	qwq[a[0]]=0;
	int x;
	For(i,1,n){
		x=qwq[a[i]];
		ckmx(x,que(0,a[i]-1)+i);
		ckmx(x,que(1,1+lim-(a[i]+1))-i);
		add(0,a[i],x-i);
		add(1,1+lim-a[i],x+i);
		qwq[a[i]]=x;
	}
	cout<<x<<endl;
}
signed main(){IOS;
	int T;cin>>T;
	while(T--)work();
return 0;}
```

---

## 作者：TLEWA (赞：3)

考虑从朴素的 dp 开始入手优化

## 如何 dp

设 $dp_i$ 表示前 $i$ 个元素划分后所取得的最大价值，$s_i = \sum_{j=1}^{i} a_j $，我们的 dp 转移如下：

$$

\begin{aligned}
dp_i = \max_{j=0}^{i-1} 

\begin{cases}
i-j+dp_j&s_i<s_j
\\
dp_j &s_i=s_j
\\
j-i+dp_j&s_i>s_j
\end{cases}

\end{aligned}

$$

时间复杂度为 $O(n^2)$，无法通过此题。

## 怎么优化

考虑使用数据结构进行优化，在对 $s$ 数组进行离散化后，我们可以在动态规划时将 $dp_i+i$，$dp_i-i$，$dp_i$ 分别塞入三颗权值线段树中，然后分别按照三种情况的转移条件进行区间最大值查询，实现 $O(\log n)$ 的单次转移复杂度。

算是比较典型的线段树优化 dp 题了，具体看代码。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=500005,INF=1e16;

int T;

int n;

struct Node {
	int l,r;
	int max;
}tre[3][4*N];

#define Tre tre[id]
#define mid (Tre[now].l+Tre[now].r>>1)
#define lson (now*2)
#define rson (now*2+1)

void build(int id,int now,int l,int r) {
	Tre[now].l=l,Tre[now].r=r,Tre[now].max=-INF;
	if(l==r) return;
	build(id,lson,l,mid);
	build(id,rson,mid+1,r);
}

int query(int id,int now,int l,int r) {
	if(l>r || Tre[now].r<l || Tre[now].l>r) return -INF;
	if(Tre[now].l>=l && Tre[now].r<=r) return Tre[now].max;
	return max(query(id,lson,l,r),query(id,rson,l,r));
}

void pushup(int id,int now) {if(Tre[now].l!=Tre[now].r) Tre[now].max=max(Tre[lson].max,Tre[rson].max);}

void change(int id,int now,int p,int val) {
	if(Tre[now].r<p || Tre[now].l>p) return;
	if(Tre[now].l==Tre[now].r) {Tre[now].max=max(Tre[now].max,val);return;}
	change(id,lson,p,val);change(id,rson,p,val);
	pushup(id,now);
}

int arr[N],qarr[N],larr[N],dp[N];

pair<int,int> narr[N];
void init() { // 进行离散化 
	for(int i=1;i<=n;++i) narr[i]=make_pair(qarr[i],i);
	narr[n+1]=make_pair(0,0); 
	sort(narr+1,narr+2+n);
	int p=0;
	narr[0].first=-INF;
	for(int i=1;i<=n+1;++i) {
		if(narr[i].first!=narr[i-1].first) ++p;
		larr[narr[i].second]=p;
	}
}

signed main() {
	cin >> T;
	while(T--) {
		cin >> n;
		for(int i=1;i<=n;++i) cin >> arr[i];
		for(int i=1;i<=n;++i) qarr[i]=qarr[i-1]+arr[i],dp[i]=0;
		// 离散化
		init();
		
		for(int i=0;i<3;++i) build(i,1,1,n+1);
		for(int i=0;i<3;++i) change(i,1,larr[0],0);
		
		for(int i=1;i<=n;++i) { // 三种转移 
			dp[i] = max({
				query(0,1,1,larr[i]-1)+i/*qarr[j] < qarr[i]，dp[j]+i-j*/,
				query(1,1,larr[i]+1,n+1)-i/*qarr[j] > qarr[i]，dp[j]+j-i*/,
				query(2,1,larr[i],larr[i])/*qarr[j] == qarr[i]，dp[i]=dp[j]*/
			});
			change(0,1,larr[i],dp[i]-i);
			change(1,1,larr[i],dp[i]+i);
			change(2,1,larr[i],dp[i]);
		}
		cout << dp[n] << endl;
	}
	
	
	return 0;
}

```

注意如果不进行离散化，直接使用动态开点有 MLE 的可能，需要做好内存的管理。

---

## 作者：封禁用户 (赞：2)

设 $f(i)$ 表示前 $i$ 的最大答案，转移是朴素的。

$$
f(i) = f(j) + calc(j + 1, i)
$$

$calc$ 函数即为题目所给的贡献函数。

现在考虑的就是优化。

记一个前缀和数列 $s$。

那么贡献其实和 $s_r - s_{l + 1}$ 的符号有关。

进一步的，其实是求 $s_r$ 和 $s_{l + 1}$ 的相对大小。

把转移拆成三部分 $(s_j < s_i, s_j > s_i, s_j = s_i)$ ，对于每个部分拆成只和 $j$ 相关的部分。用一个数据结构对 $s_i$ 维护 $f(i) - i$ 和 $f(i) + i$ 实现对前一个取前缀最大值和对后一部分取后缀最大值。当 $s_i = s_j$ 时，简单记录 $s_i = k$ 时的最大值即可。

时间复杂度 $\mathcal{O}(n \log n)$。

[$\texttt{Code}$](https://codeforces.com/contest/1667/submission/289112048)

---

## 作者：_Ch1F4N_ (赞：2)

VP 了一下场切了。

定义 $dp_i$ 表示 $[1,i]$ 的权值之和，不难发现有 $dp_i = \max(\max_{\sum_{k=i}^{j} > 0} (dp_j + (i-j)),\max_{\sum_{k=i}^{j} < 0} (dp_j - (i-j)))$。当然和为 $0$ 的情况是好特殊处理的，这里略去。

然后记 $pre_i = \sum_{j=1}^{i} a_j$ 式子转化为 $dp_i = \max(\max_{pre_i > pre_j} (dp_j + (i-j)),\max_{pre_i < pre_j} (dp_j - (i-j)))$。

然后考虑怎么处理 $(i-j)$ 这个东西，不难发现假若可以确定前面的符号后，每次从 $i-1$ 考虑到 $i$ 时全局减 $1$ 或者加 $1$ 即可。

再考虑 $pre$ 的偏序限制，将这个离散化后作为下标，那么开两棵线段树分别维护单点修改区间 $\max$ 即可。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5e5+114;
const int inf = 1e18+114;
map<int,int> lsh;
int n,a[maxn],pre[maxn],chifan[maxn],b[maxn],cnt[maxn];
int tr[maxn<<2][2],add[2];//0 维护 -1 & 1 维护 +1
void build(int cur,int lt,int rt){
    if(lt==rt){
        tr[cur][0]=tr[cur][1]=-inf;
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    tr[cur][0]=max(tr[cur<<1][0],tr[cur<<1|1][0]);
    tr[cur][1]=max(tr[cur<<1][1],tr[cur<<1|1][1]);
    return ;
}
void cover(int cur,int lt,int rt,int pos,int v){
    if(lt==rt){
        tr[cur][0]=max(tr[cur][0],v-add[0]);
        tr[cur][1]=max(tr[cur][1],v-add[1]);
        return ;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid) cover(cur<<1,lt,mid,pos,v);
    else cover(cur<<1|1,mid+1,rt,pos,v);
    tr[cur][0]=max(tr[cur<<1][0],tr[cur<<1|1][0]);
    tr[cur][1]=max(tr[cur<<1][1],tr[cur<<1|1][1]);
    return ;
}
int ask(int cur,int lt,int rt,int l,int r,int t){
	if(l>r) return -inf;
    if(r<lt||rt<l) return -inf;
    if(l<=lt&&rt<=r) return tr[cur][t]+add[t];
    int mid=(lt+rt)>>1;
    return max(ask(cur<<1,lt,mid,l,r,t),ask(cur<<1|1,mid+1,rt,l,r,t));
}
void work(){
    lsh.clear();
    cin>>n;
    for(int i=1;i<=n;i++){
    	cnt[i]=-inf;
        cin>>a[i];
        pre[i]=pre[i-1]+a[i];
        b[i]=pre[i];
        chifan[i]=pre[i];
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) if(lsh[b[i]]==0) lsh[b[i]]=lsh.size();
    for(int i=1;i<=n;i++) pre[i]=lsh[pre[i]];
    build(1,1,n);
    add[0]=add[1]=0;
    int ans=-inf;
    int dp;
    for(int i=1;i<=n;i++){
        add[0]--;
        add[1]++;
        dp=-inf;
        dp=max(dp,cnt[pre[i]]);
        if(chifan[i]==0) dp=max(dp,0*1ll);
        if(chifan[i]>0) dp=max(dp,i);
        if(chifan[i]<0) dp=max(dp,-i);
        dp=max(dp,max(ask(1,1,n,1,pre[i]-1,1),ask(1,1,n,pre[i]+1,n,0)));
        cnt[pre[i]]=max(cnt[pre[i]],dp);
        cover(1,1,n,pre[i],dp);
    }
    cout<<dp<<'\n';
    return ;  
}
signed main(){
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：Qcfff (赞：2)

[CF1667B Optimal Partition](https://www.luogu.com.cn/problem/CF1667B)

vp 场内思路想完了没想出咋用数据结构，遂写题解

记 $a$ 前缀数组 $s$，不难想到 dp 并列出转移方程：

$$dp(r)=\max\limits_{1\le l\le r}\Big\{dp(l-1)+\text{calc}(l,r)\Big\}$$

$$S=s(r)-s(l-1),\text{calc}(l,r)=\begin{cases}(r-l+1)&S>0\\0&S=0\\-(r-l+1)&S<0\end{cases}$$

考虑第一种情况的简化版本：

$$dp(r)=\max\limits_{1\le l\le r}\Big\{dp(l-1)+(r-l+1)\Big\}$$

$$dp(r)=\max\limits_{1\le l\le r}\Big\{dp(l-1)-l\Big\}+r+1$$

显然维护 $dp(l-1)-l$ 最大值即可。

同理如果只有 $\text{calc}$ 中的其它两种单独情况时，只要维护 $dp(l-1)$ 和 $dp(l-1)+l$ 最大值即可。

回到原题，尝试把 $\text{calc}$ 的三部分分开统计：

$$dp(r)=\max\limits_{1\le l\le r}\begin{cases}\max(dp(l-1)-l)+r+1&s(l-1)<s(r)\\\max(dp(l-1))&s(l-1)=s(r)\\\max(dp(l-1)+l)-r-1&s(l-1)>s(r)\end{cases}$$

可以按照 $s(r)-s(l-1)$ 把 $s$ 排序，就会存在位置 $1\le kl<kr\le r-1$ 满足排序后的 $s'(i)=s(r)-s(i-1)$ 中 $s'(1\sim kl)<0,s'(kl+1\sim kr-1)=0,s'(kr\sim r-1)>0$，然后在 $[1,kl]$、$[kl+1,kr-1]$、$[kr+1,r-1]$ 中分别取维护的最值计算出 $dp(r)$ 即可，实现的困难在于给 $s$ 排序、求区间最值、找到 $s'$ 中 $0$ 的位置的问题。

可以考虑对 $s$ 排序，预处理出 $s(k)=s(r)$ 的最左和最右的位置即 $kl$ 和 $kr$，建立三棵分别维护 $dp(i-1)-i$、$dp(i-1)$、$dp(i-1)+i$ 最大值的线段树，每次查询区间最值并更新即可，复杂度 $O(n\log n)$。

思路挺好想的，就是不知道为什么 vp 场内傻卵了想不出数据结构。

**code：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const int N=5e5+10;
int T,n,a[N],s[N],cr[N],fl[N],fr[N],dp[N];
struct node{
	int idx,val;
}p[N];
bool cmp(node a,node b){
	if(a.val==b.val){
		return a.idx<b.idx;
	}
	return a.val<b.val;
}
struct segment{//单点修改区间查询 
	struct tree{
		int dat,l,r;
	}t[N*4];
	void build(int p,int l,int r){
		t[p]=(tree){-INF,l,r};
		if(l==r){
			return;
		}
		int mid=(l+r)/2;
		build(p*2,l,mid);
		build(p*2+1,mid+1,r);
		return;
	}
	void pushup(int p){
		t[p].dat=max(t[p*2].dat,t[p*2+1].dat);
		return;
	}
	void change(int p,int x,int v){
		if(t[p].l==t[p].r){
			t[p].dat=v;
			return;
		}
		int mid=(t[p].l+t[p].r)/2;
		if(x<=mid){
			change(p*2,x,v);
		}
		if(x>mid){
			change(p*2+1,x,v);
		}
		pushup(p);
		return;
	}
	int ask(int p,int l,int r){
		if(l<=t[p].l&&t[p].r<=r){
			return t[p].dat;
		}
		int mid=(t[p].l+t[p].r)/2;
		int ans=-INF;
		if(l<=mid){
			ans=max(ans,ask(p*2,l,r));
		}
		if(r>mid){
			ans=max(ans,ask(p*2+1,l,r));
		}
		return ans;
	}
}L,M,R;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s[i]=s[i-1]+a[i];
			p[i]=(node){i,s[i-1]};
		}
		sort(p+1,p+1+n,cmp);
		for(int i=1;i<=n;i++){
			cr[p[i].idx]=i;//cr为每一项s映射的下标 
		}
		
		p[0].val=INF,p[n+1].val=INF;
		fl[n]=0,fr[n]=n+1;
		
		//预处理小于和大于每项前缀和的映射的下标区间 
		for(int i=1;i<=n;i++){
			if(p[i].val!=p[i-1].val){
				fl[p[i].idx-1]=i-1;
			}else{
				fl[p[i].idx-1]=fl[p[i-1].idx-1];
			}
			if(p[i].val<s[n]){//记得单独处理第n项的 
				fl[n]=i;
			}
		}
		for(int i=n;i>=1;i--){
			if(p[i].val!=p[i+1].val){
				fr[p[i].idx-1]=i+1;
			}else{
				fr[p[i].idx-1]=fr[p[i+1].idx-1];
			}
			if(p[i].val>s[n]){//同上 
				fr[n]=i;
			}
		}
		
		L.build(1,1,n);
		M.build(1,1,n);
		R.build(1,1,n);
		for(int r=1;r<=n;r++){
			//更新线段树 
			L.change(1,cr[r],dp[r-1]-r);
			M.change(1,cr[r],dp[r-1]);
			R.change(1,cr[r],dp[r-1]+r);
			
			int kl=fl[r],kr=fr[r];
			
			dp[r]=-INF;
			//分段计算dp 
			if(kl>=1){ 
				dp[r]=max(dp[r],L.ask(1,1,kl)+r+1);
			}
			if(kl+1<=kr-1){
				dp[r]=max(dp[r],M.ask(1,kl+1,kr-1));
			}
			if(kr<=n){
				dp[r]=max(dp[r],R.ask(1,kr,n)-r-1);
			}
		}
		cout<<dp[n]<<"\n";
	}
	return 0;
} 
```

---

## 作者：guojiahong (赞：1)

式子可以看其他题解，这里就不推了。

唯一不同的，其实这个问题只需要 **一个** 线段树（或者树状数组）。

#### 为什么？
这里给出一个结论，一定有一个最优解使得：所有区间长度 $\ge2$ 的区间的 $sum$ 值 $\ge0$ 即所有区间长度 $\ge2$ 的区间对答案的贡献为非负。

证明：如果出现一段区间的 $sum$ 值 $<0$ 且长度 $\ge2$，那么这个区间一定可以拆成若干长度为 $1$ 的正区间（设可以拆成 $k$ 个）、若干个长度为 $1$ 的负区间和若干长度为 $1$ 的 $0$ 区间，容易发现 $k\ge0$，把这个大的负区间拆成长度为 $1$ 的小区间可以给答案带来 $2k$ 的非负的贡献。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=-1000001;
int a[500001];
int dp[500001],s[500001];
pair<long long,int> sum[500001];
long long sum1[500001];
int tree[2000001];
void build(int node,int l,int r)
{
	tree[node]=INF;
	if(l==r)return ;
	int mid=(l+r)/2;
	build(node*2,l,mid);
	build(node*2+1,mid+1,r);
	return ;
}
void change(int node,int l,int r,int w,int z)
{
	if(l==r)
	{
		tree[node]=max(tree[node],z);
		return ; 
	}
	int mid=(l+r)/2;
	if(w<=mid)change(node*2,l,mid,w,z);
	else change(node*2+1,mid+1,r,w,z);
	tree[node]=max(tree[node*2],tree[node*2+1]); 
	return ;
}
int get(int node,int l,int r,int ll,int rr)
{
	if(ll<=l&&r<=rr)return tree[node];
	int mid=(l+r)/2;
	int ans=INF;
	if(ll<=mid)ans=max(ans,get(node*2,l,mid,ll,rr));
	if(rr>mid)ans=max(ans,get(node*2+1,mid+1,r,ll,rr));
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			sum[i].first=sum[i-1].first+a[i];
			sum[i].second=i;
			sum1[i]=sum1[i-1]+a[i]; 
		}
//		for(int i=1;i<=n;i++)cout<<a[i]<<' ';
//		cout<<'\n';
		sort(sum+1,sum+1+n);
		int cnt=1,p=0;
		s[sum[1].second]=1;
		for(int i=2;i<=n;i++)
		{
			if(sum[i].first!=sum[i-1].first)cnt++;
			s[sum[i].second]=cnt;
		}
//		cout<<"s:";
//		for(int i=1;i<=n;i++)cout<<s[i]<<' ';
//		cout<<'\n';
		build(1,1,cnt);
		for(int i=1;i<=n;i++)dp[i]=0;
		for(int i=1;i<=n;i++)
		{
			if(sum1[i]>0)dp[i]=i;
			if(sum1[i]==0)dp[i]=0;
			if(sum1[i]<0)dp[i]=-i;
			dp[i]=max(max(dp[i],(s[i]-s[i-1]==0)?dp[i-1]:INF),max(((s[i]-1>0)?(get(1,1,cnt,1,s[i]-1)+i):INF),dp[i-1]-1));
//			cout<<((s[i]-1>0)?(get(1,1,cnt,1,s[i]-1)+i):INF)<<'\n';
			change(1,1,cnt,s[i],dp[i]-i);
//			cout<<dp[i]-i<<'\n';
		}
//		for(int i=1;i<n;i++)printf("%d ",dp[i]);
		printf("%d\n",dp[n]);
	}
	return 0;
}
```
本文除了代码的所有东西都是完全正确的，虽然代码可以通过原题，但我已经构造出可以 hack 掉它的数据（~虽然我确实还没有改正错误~）。

---

## 作者：VitrelosTia (赞：1)

*2100，简单题。

直接考虑 dp，先记个前缀和 $s$，然后设 $f_i$ 表示强制以 $i$ 为一段结尾的答案。考虑新建段 $[j+1,i]$，按照题意有转移 $f_i = \begin{cases} f_j + i-j \ \ (s_i > s_j)\\f_j \ \ \ \ \ \ \ \ \ \ \ \ \ \ \  (s_i=s_j)\\ f_j + j - i \ \ (s_i < s_j)\end{cases}$，离散化之后分别维护值域上 $f_j-j$ 的前缀 $\max$、$f_j+j$ 的后缀 $\max$，$f_j$ 的 $\max$ 即可。可以树状数组，可以线段树，我比较没脑子直接开三个线段树。

有一个细节是你需要考虑段 $[1,i]$ 的情况，照理来说你应该要使 $f_0=0$，但是离散化之后这个事情非常抽象，其实可以每次转移的时候判掉这种情况。

```cpp
const int N = 5e5 + 5, inf = 1e16;
int n, m, s[N], ss[N], b[N], f[N];
struct SegTree {
	struct Seg { int l, r, v; } s[N << 2];
#define ls (pos << 1)
#define rs (pos << 1 | 1)
#define mid ((s[pos].l + s[pos].r) >> 1)
	void pushup(int pos) { s[pos].v = max(s[ls].v, s[rs].v); }
	void build(int L = 1, int R = m, int pos = 1) {
		s[pos].l = L, s[pos].r = R; if (L == R) return s[pos].v = -inf, void();
		build(L, mid, ls); build(mid + 1, R, rs); pushup(pos);
	}
	void update(int o, int k, int pos = 1) {
		if (s[pos].l == s[pos].r) return s[pos].v = max(s[pos].v, k), void();
		o <= mid ? update(o, k, ls) : update(o, k, rs); pushup(pos);
	}
	int query(int l, int r, int pos = 1) {
		if (l > r) return -inf; if (l <= s[pos].l && s[pos].r <= r) return s[pos].v;
		return max(l <= mid ? query(l, r, ls) : -inf, r > mid ? query(l, r, rs) : -inf);
	}
} t[3];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1], ss[i] = s[i], b[i] = s[i];
	sort(b + 1, b + n + 1); m = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; i++) s[i] = lower_bound(b + 1, b + m + 1, s[i]) - b;
	for (int i = 0; i < 3; i++) t[i].build();
	for (int i = 1; i <= n; i++) {
		int v1 = t[0].query(1, s[i] - 1) + i, 
			v2 = t[1].query(s[i], s[i]), 
			v3 = t[2].query(s[i] + 1, m) - i, 
			v4 = ss[i] == 0 ? 0 : (ss[i] > 0 ? i : -i); // 上面说的特殊情况
		f[i] = max({v1, v2, v3, v4}); 
		t[0].update(s[i], f[i] - i), 
		t[1].update(s[i], f[i]), 
		t[2].update(s[i], f[i] + i);
	} cout << f[n] << '\n';
}
```

---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1667B)

***2100**，没想出来，为什么呢。

看到划分序列相关，可能是 dp。

所以，我们很容易得到一个 $O(n^2)$ 的 dp，设 $dp_i$ 表示划分完 $[1,i]$ 的答案，记前缀和为 $s$，以下 $j\in [1,i]$ ：

- 若 $s_i>s_{j-1}$，有 $dp_i=\max(dp_i,dp_j+(i-j+1))$。
- 若 $s_i=s_{j-1}$，有 $dp_i=\max(dp_i,dp_j)$。
- 若 $s_i<s_{j-1}$，有 $dp_i=\max(dp_i,dp_j-(i-j+1)$。

然后我觉得这个 dp 没啥前途，就放去想性质了。然后不会。

实际上很有前途。因为我做的时候没有把柿子写的这么清楚罢了。

把 $j-1$ 换成 $j$ 再写一遍，相当于变成选 $[j+1,i]$ 这个区间，这个更加方便我们整理项。

- 若 $s_i>s_j$，有 $dp_i= dp_j+(i-(j+1)+1)=dp_j+i-j$。
- 若 $s_i=s_j$，有 $dp_i=dp_j$。
- 若 $s_i<s_j$，有 $dp_i= dp_j-(i-j)=dp_j+j-i$。

发现我们在枚举 $i$ 的时候维护和 $j$ 相关的项就做完了，具体的，对 $s$ 离散化以后开权值线段树就行。

~~这么简单的题为啥你能不会呢？~~

实现有细节，注意 $dp_0$ 的处理。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long 
#define DEBUG cout<<"when can get npy"<<endl;
map<int,int> Id;
int lst,n,a[N],s[N],t[N],dp[N],G[N];
template<class T,const int INF> class Tree{
	int d[INF<<2];
	public:
		void build(){
//			memset(d,-0x3f,sizeof(d));
			for(int i=1;i<=4*lst;i++)	d[i]=-1e15;
		} 
		void update(int l,int r,int s,int t,int p,int change){
			if(l<=s&&t<=r){d[p]=max(d[p],change); return ;}
			int mid=(s+t)>>1;
			if(l<=mid)	update(l,r,s,mid,p<<1,change);
			if(r>mid)	update(l,r,mid+1,t,p<<1|1,change);
			d[p]=max(d[p<<1],d[p<<1|1]);
		}
		T Query(int l,int r,int s,int t,int p){
			if(l<=s&&t<=r)	return d[p];
			int mid=(s+t)>>1,ans=-LLONG_MAX;
			if(l<=mid)	ans=max(ans,Query(l,r,s,mid,p<<1));
			if(r>mid)	ans=max(ans,Query(l,r,mid+1,t,p<<1|1));
			return ans;
		}
};
Tree<int,N> Tree1,Tree2;

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i];
		for(int i=1;i<=n;i++)	s[i]=s[i-1]+a[i],G[i]=s[i];
		G[n+1]=0,sort(G+1,G+n+2);
		lst=unique(G+1,G+n+2)-G-1;
		for(int i=1;i<=lst;i++)	Id[G[i]]=i;
		for(int i=0;i<=n+1;i++)	t[i]=dp[i]=-LLONG_MAX;
		
		Tree1.build(),Tree2.build();
		dp[0]=0,t[Id[0]]=0,Tree1.update(Id[0],Id[0],1,lst,1,0),Tree2.update(Id[0],Id[0],1,lst,1,0);
		
		for(int i=1;i<=n;i++){
			dp[i]=max(dp[i],t[Id[s[i]]]);
			
			if(Id[s[i]]+1<=lst)	dp[i]=max(dp[i],Tree1.Query(Id[s[i]]+1,lst,1,lst,1)-i);

			
			if(Id[s[i]]-1>=1)	dp[i]=max(dp[i],Tree2.Query(1,Id[s[i]]-1,1,lst,1)+i);
			
	//		if(i==1)	cout<<dp[i];
			
			Tree1.update(Id[s[i]],Id[s[i]],1,lst,1,dp[i]+i);
			Tree2.update(Id[s[i]],Id[s[i]],1,lst,1,dp[i]-i);
			t[Id[s[i]]]=max(t[Id[s[i]]],dp[i]);
			
			cout<<dp[i]<<endl;
		} 
		cout<<dp[n]<<endl;
		for(int i=1;i<=lst;i++)	Id[G[i]]=0;
	}
	return 0;
}
/*
1
6
-1 2 -3 4 -5 6
    dp_i:(0<=j<i)
	s_i>s_j  dp_i= dp_j+(i-(j+1)+1)=dp_j+i-j
	s_i=s_j  dp_i=dp_j
	s_i<s_j  dp_i= dp_j-(i-j)=dp_j+j-i 

*/
```

---

## 作者：Polaris_Australis_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1667B)
## 题意
给定序列 { $a_i$ } ，分成若干段，对于每一段，设左右端点为 $l,r$ ，$s=\sum_{i=l}^ra_i$ 。对于每一段，若 $s>0$ ，对总答案贡献为 $r-l+1$ ，
若 $s<0$ ，对总答案贡献为 $-(r-l+1)$ ，若 $s=0$ ，对总答案贡献为 $0$ 。求最大总贡献。
## 解法
上面所说的那些对 $s$ 分类讨论的情况，其实相当于前缀和作比较，如 $s>0$ 相当于 $sum_r>sum_{l-1}$ 。那我们可以按照 $sum_{l-1}$ 与 $sum_r$ 的大小关系列出三种转移方程 ($1\le l\le r$) ：
$$
dp[r]=max
\left\{
\begin{array}{l}
dp[l-1]+r-(l-1)\texttt{ }\texttt{ }(sum[r]>sum[l-1])\\
dp[l-1]-r+(l-1)\texttt{ }\texttt{ }(sum[r]<sum[l-1])\\
dp[l-1]\texttt{ }\texttt{ }(sum[r]=sum[l-1])
\end{array}
\right.
(1\le l\le r)
$$

对于第一个式子，相当于从所有满足 $sum[r]>sum[l-1]$ 的 $l$ 里找一个 $dp[l-1]-(l-1)$ 最大的，用正常的树状数组存就好了。

对于第一个式子，相当于从所有满足 $sum[r]<sum[l-1]$ 的 $l$ 里找一个 $dp[l-1]+(l-1)$ 最大的，由于树状数组查询区间最值不是很好用（至少我这个蒟蒻不会），但是查询从 $1$ 到 $x$ 的最值还是很好用的，这题要求的是从某个数到 $sum$ 最大值的，那么树状数组倒着存，就可以了。

对于第三个式子，就对于每个 $sum$ 值求一个 $dp$ 最大值就行了。

最后，由于 $sum$ 很大，需要离散化，并且要初始化 $-inf$ （我就这里挂了。。）
## 代码
```cpp
#include<bits/stdc++.h>
//#define ll long long
#ifdef ll
#define rll register long long
#define ull unsigned long long
#define rint register int
#define uint unsigned int
#else
#define int long long
#define rint register long long
#define uint unsigned long long
#endif
#define db double
#define eps (1e-11)
using namespace std;
namespace Std
{
    template<typename tp>
    void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9')
        {
            if(c=='-')nev=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')
        {
            x=(x<<1)+(x<<3)+(c^48);
            c=getchar();
        }
        x*=nev;
    }
    template<typename tp>
    void write(tp x)
    {
        if(x<0)
        {
            putchar('-');
            write(-x);
            return;
        }
        if(x/10)write(x/10);
        putchar((x%10)^48);
    }
    int rt,n,t,a[500001],sum[500001],dp[500001],inf=0x3f3f3f3f3f3f3f3f,_inf=0xf3f3f3f3f3f3f3f3,tr[3][500001],id[500001],tot;
    bool cmp(int x,int y){return sum[x]<sum[y];}
    inline int lowbit(int x){return x&(-x);}
    void change(int x,int y,int z)
    {
        while(x<=tot)
        {
            tr[z][x]=max(tr[z][x],y);
            x+=lowbit(x);
        }
    }
    int query(int x,int y)
    {
        return x?max(query(x-lowbit(x),y),tr[y][x]):_inf;
    }
    int main()
    {
        read(t);
        memset(dp,0xf3,sizeof(dp));
        memset(tr,0xf3,sizeof(tr));
        while(t--)
        {
            for(int i=1;i<=n;++i)dp[i]=_inf;
            read(n);
            sum[0]=0;
            id[0]=0;
            for(int i=1;i<=n;++i){read(a[i]);sum[i]=sum[i-1]+a[i];id[i]=i;}
            sort(id,id+1+n,cmp);
            sum[n+1]=inf;
            tot=0;
            for(int i=0;i<=n;++i)
            {
                int tp=sum[id[i]];
                sum[id[i]]=++tot;
                if(tp==sum[id[i+1]])--tot;
            }
            dp[0]=0;
            change(sum[0],0,0);
            change(tot-sum[0]+1,0,1);
            tr[2][sum[0]]=0;
            tot=sum[id[n]];
            for(int i=1;i<=n;++i)
            {
                int mn1=query(sum[i]-1,0);
                int mn2=query(tot-sum[i],1);
                int mn3=tr[2][sum[i]];
                if(mn1!=_inf)dp[i]=max(dp[i],mn1+i);
                if(mn2!=_inf)dp[i]=max(dp[i],mn2-i);
                dp[i]=max(dp[i],mn3);
                change(sum[i],dp[i]-i,0);
                change(tot-sum[i]+1,dp[i]+i,1);
                tr[2][sum[i]]=max(tr[2][sum[i]],dp[i]);
            }
            printf("%lld\n",dp[n]);
            for(int i=0;i<=n;++i)
            {
                for(int j=sum[i];j<=tot;j+=lowbit(j))tr[0][j]=_inf;
                for(int j=tot-sum[i]+1;j<=tot;j+=lowbit(j))tr[1][j]=_inf;
                tr[2][sum[i]]=_inf;
            }
        }
        return 0;
    }
}
#ifdef int
#undef int
#endif
int main()
{
    return Std::main();
}
```


---

## 作者：Terry_RE (赞：0)

# CF1667B Optimal Partition 题解

## 题意
  给出一个长度为 $n$ 的数组 $a$，并将其分为 $x$ 段区间，计算每段区间的贡献之和的最大值。

## 思路
- 看完题应该就能想到可以维护前缀和加暴力 dp，转移方程为 $dp_i = \max{\{dp_j + x(j-i+1)\}}$，其中 $j<i$，$x$ 可以理解为区间和的数的正负号。两层循环分别枚举 $i$ 和 $j$，时间复杂度为 $O(n^2)$，明显超时。

### 优化

我们可以对转移方程分类讨论一下,
- $dp_i = dp_j + i - j，(\sum_{k = j}^{i}a_k > 0)$ $①$
- $dp_i = dp_j, (\sum_{k = j}^{i}a_k = 0)$ $②$
- $dp_i = dp_j + j - i, (\sum_{k = j}^{i}a_k < 0)$  $③$

观察后我们会发现，我们暴力求法中的第二层循环中求的最大值可以换为 $①$ 式中的 $dp_j - j$ 和 $③$ 式中的 $dp_j+j$，也就是说，我们就可以把维护 $a$ 数组的前缀最大值换为分别维护 $dp_j-j$ 和 $dp_j+j$ 的前缀最大值。显然，树状数组可以很好的胜任这个任务；对于 $②$ 式，我们只需要用一个数组维护前缀最大值即可。

## 小の技巧
-  一个测试点中有 $t$ 个样例，显然对于每个样例我们都要对树状数组进行初始化，也就是 memset，但这样的时间开销是 $O(n)$ 的，那么有人就会问了：主播主播，我知道你的 memset 很好用，但有没有什么方法可以减小时间开销呢？~~有的兄弟，有的。~~ 那就是**时间戳优化**。这是什么呢？简单来说，就是新建一个 $tag$ 数组，$tag$ 数组在处理**多个测试用例**时，为树状数组 $c$ 中的每个元素记录了当前的测试用例编号。在更新和查询操作中，通过比较 $tag$ 数组的值和当前测试用例编号，保证了不同测试用例的数据不会相互干扰，进而减少了初始化树状数组的时间开销。（可以看下面程序再理解一下）

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define max(a, b) (a > b ? a : b)
#define qwq 0

const int N = 1e6;

int n;

template <typename T>
class BIT
{
public:
	T c[N];
	int tag[N];//时间戳

	#define lowbit(x) (x & -x)

	void update(const int &x, const T &k, const int &id){
		for(int i = x; i <= n; i += lowbit(i)){
			if(id ^ tag[i])c[i] = -1e9;

			tag[i] = id;
			c[i] = max(c[i], k);
		}

		return ;
	}

	T getsum(const int &x, const int &id){
		T sum = -1e9;

		for(int i = x; i > 0; i -= lowbit(i))
			if(tag[i] == id)
				sum = max(sum, c[i]);

		return sum;
	}
};

BIT<ll> c1;
BIT<ll> c2;

ll a[N];
ll b[N];

ll mx[N];
ll dp[N];

int main(){
	cin.tie(0) -> ios::sync_with_stdio(false);

	int T;
	cin >> T;

	for(int t = 1; t <= T; ++t){
		cin >> n;

		for(int i = 1; i <= n; ++i)
			cin >> a[i], b[i] = a[i] = a[i] + a[i-1], mx[i] = -1e17;

		//离散化
		sort(b+1, b+1+n);

		int l = unique(b+1, b+1+n) - (b+1);

		for(int i = 1; i <= n; ++i)
			i[a] = lower_bound(b+1, b+1+l, a[i]) - b;
  

		for(int i = 1; i <= n; ++i){
			dp[i] = -i;
			dp[i] = (b[a[i]] == 0 ? 0 : dp[i]);
			dp[i] = (b[a[i]] > 0 ? i : dp[i]);

			dp[i] = max(dp[i], max(c1.getsum(a[i] - 1, t) + i, max(mx[a[i]], c2.getsum(l - a[i], t) - i)));

			c1.update(a[i], dp[i] - i, t);
			c2.update(l - a[i] + 1, dp[i] + i, t);

			mx[a[i]] = max(mx[a[i]], dp[i]);
		}

		cout << n[dp] << "\n";
	}

	return qwq;
}
```

#### 后话
我已经把数学公式全用 LaTeX 括上了，这次总能过了吧()。

---

## 作者：Wu_Qi_Tengteng (赞：0)

第一眼有一个比较显然dp，设 $f_i$ 表示前 $i$ 个数，对他们划分所能得到的最大值。
转移有：
$$
f_i=\max_{j=1}^{i-1} f_j+cost(j+1,i)
$$

首先看这个东西可不可以之接用什么东西优化，好像不太行，那么我们考虑拆给贡献。

$$
  f_{i}=\left\{\begin{matrix} f_j-j+i\ \ s_j<s_i\\ 
   f_j\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ s_j=s_i\\ 
  f_j+j-i\ \ s_j>s_i  
\end{matrix}\right.    
$$

这个东西看能不能用什么数据结构维护，可是你发现每种情况的取值跟区间半毛钱关系都没有。树状数组线段树啥的都用不了。

但是我们可以发现，$j$ 虽然没有构成区间，但是同一种情况下的 $s_j$ 却构成了区间。这启发我们可以把dp值挂在对应的 $s$ 上。

所以离散化一下 $s$ 数组，用两个树状数组分别维护前两种情况，中间直接单点维护就好了。

时间复杂度 $\mathcal{O}(n\log n)$。
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
const int N=5e5+5;
int T,n,s[N],c[N],len,ss[N],f[N]; 
struct Ta{
	int ma[N];
	inline void clear(){for(int i=1;i<=len;i++)ma[i]=-inf;}
	inline void add(int x,int v){for(;x<=len;x+=(x&(-x)))ma[x]=max(ma[x],v);}
	inline int sum(int x){int res=-inf;for(;x;x-=(x&(-x)))res=max(res,ma[x]);return res;}
}t1,t2;
signed main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){
			c[i]=s[i]=read()+s[i-1];
			ss[i]=-inf;
		}
		sort(c+1,c+n+1);
		len=unique(c+1,c+n+1)-c-1;
		for(int i=1;i<=n;i++)s[i]=lower_bound(c+1,c+len+1,s[i])-c;
		t1.clear();t2.clear();
		for(int i=1;i<=n;i++){
			f[i]=c[s[i]]>0?i:c[s[i]]==0?0:-i;
			f[i]=max({f[i],t1.sum(s[i]-1)+i,ss[s[i]],t2.sum(len-s[i])-i});
			t1.add(s[i],f[i]-i);
			t2.add(len-s[i]+1,f[i]+i);
			ss[s[i]]=max(ss[s[i]],f[i]);
		}
		printf("%lld\n",f[n]);
	}
	return 0;
} 
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1667B)

# 思路：

这道题很有趣，首先根据题目，不难判断出这是一个 $dp$ 问题。设 $dp_i$ 代表从 $1 \cdots i$ 能够得到的最大价值总和，那么 $dp_i = \max_j \{dp_j + v_{j+1 \cdots i}\}$，尽管 $v$ 值我们可以靠预处理前缀和 $O(1)$ 得到，但是找 $i$ 的过程仍然是 $O(n^2)$ 的，这样是过不了这道题的。

考虑如何更快地进行解题，首先从这个条件入手，看题解发现，当一段长度大于 $1$ 的区间 $s \gt 0$ 时，它加入答案才能获得更大的收益，否则，我们都可以通过拆的方式将它拆成长度为 $1$ 的几个小段。因为 $s \lt 0$ 时，我们将整个区间再进行拆分，那么得到的结果如果有 $s \gt 0$ 的部分，则结果更优，否则结果也不会更差。如果 $s = 0$ 的话，我们也可以对整个区间进行拆分，若长度是偶数，那么可以分成左右两部分，结果不会更差（$s$ 要么都是 $0$，要么一正一负；若长度为奇数，则暂时将该段分成左、中（长度为 $1$）、右三部分，若左或右的 $s \lt 0$，那么将其分成两段（左，中右）或（左中，右）两部分的话，结果会更好。其余情况可以直接拆成（左、中、右）三部分，结果不会更差。因此最后长度大于 $1$ 的子段，我们只需要计算 $s \gt 0$ 的，其余情况只计算长度为 $1$ 的即可。

我们考虑如何选取子段 $s \gt 0$ 的区间，首先设 $p_i$ 为代表 $a_1+a_2+\cdots a_i$ 的前缀和。若我们可以对前缀和进行排序，当我们已知当前位置 $i$ 的前缀和排位 $ord_i$ 时，我们可以通过查找前缀和比其小的段 $1\cdots j$（$ord_j \lt ord_i$），且 $j \lt i$ 进行更新。这样我们可以保证 $j+1 \cdots i$ 区间的 $v$ 值是正的，我们可以直接使用 $i-j$ 表示这一段的价值。

但尽管这样能够保证正值，但仍然需要查找 $j$，根源在于统计 $j+1 \cdots i$ 的价值需要同时用到两次更新的坐标位置。但其实我们可以把 $+i,-j$ 这两件事情分开做，若我们每次找最大的 $dp_j - j$，那么在更新 $i$ 时，我们可以直接将该结果 $+i$ 便变成了 $dp_j + i - j$，这样我们就可以分开统计，直接使用树状数组找最大的 $dp_j - j$ 就可以省去那一次找 $j$ 的遍历，使得总体复杂度变为 $O(n \log n)$。

值得注意的是排序时，对于前缀和相等的情况，我们要把位置大的放前面，这样我们更新的时候就不会使用位置小的去更新位置大的了（此时该段的总价值为 $0$，我们更新的时候是直接 $+i, -j$ 的操作，没有考虑 $0$ 的情况，会导致错误答案，而实际上根据第二段的分析，价值为 $0$ 我们是不该考虑的）。以及要考虑没有分段的情况，即当前位置 $i$ 的前缀和大于 $0$，此时最大价值总和就是 $i$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int RINF=-0x7f7f7f7f;
int T,a[N],f[N],dp[N],ord[N],n,p[N];
int lowbit(int x){ 
    return x&-x;
}
void update(int x,int v){
    while(x<=n){
        f[x]=max(f[x],v);
        x+=lowbit(x);
    }
}
int query(int x){
    int ans=RINF;
    while(x>0){
        ans=max(f[x],ans);
        x-=lowbit(x);
    }
    return ans;
}
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            f[i]=RINF;
        }
        vector<pair<int,int> >pre;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            p[i]=p[i-1]+a[i];
            pre.push_back(make_pair(p[i],-i));
        }
        sort(pre.begin(),pre.end());
        for(int i=1;i<=n;i++){
            ord[-pre[i-1].second]=i;
        }
        for(int i=1;i<=n;i++){
            dp[i]=dp[i-1]+(a[i]>0?1:(a[i]<0?-1:0));
            dp[i]=max(dp[i],query(ord[i])+i);
            if(p[i]>0){
                dp[i]=i;
            }
            update(ord[i],dp[i]-i);
        }
        cout<<dp[n]<<endl;
        p[0]=0;
        dp[0]=0;
    }
    return 0;
}
```

完结撒花~

---

## 作者：Union_Find (赞：0)

# 题意

题意翻译之后简洁明了，就是把原数组分成若干段，若一段数字和大于 $0$，产生 $len$ 的贡献。如果和小于 $0$，产生 $-len$ 的贡献。如果和为 $0$，不产生贡献。求最大贡献和为多少。

# 分析算法

求最大值，并且看数据范围，很明显是 $O(n)$ 或 $O(n \log(n))$ 的。所以我们考虑 dp。

# 暴力

我们定义 $f_i$ 表示前 $i$ 个数的答案。那么就有一个暴力的转移方程 $f_i = \max\{f_j+w(j+1,i)\}$。其中，$w(l,r)$ 表示区间 $[l,r]$ 的贡献。于是根据这个方程，我们可以写出一个 $O(n^2)$ 的暴力。

# 正解

当然，这个时间复杂度太劣了，我们要优化一下。因为 $w(l,r)$ 要分类讨论，我们就也分类讨论。

第一种是 $sum_j < sum_i$，这样的话区间 $[j+1,i]$ 的和就是大于 $0$ 的。那么 $f_i = \max\{f_j + i - j\} = \max\{f_j-j\}+i$。所以对于 $sum_j < sumi$ 的 $j$，我们求 $f_j-j$ 的最大值。

第二种是 $sum_j>sum_i$，我们和前一种情况一样讨论，得到 $f_i = \max\{f_j+j-i\} = \max\{f_j+j\} - i$，所以我们对于 $sum_j>sum_i$ 求 $f_j+j$ 的最大值。

第三种就是 $sum_j = sum_i$。这部分可以直接用一个数组存 $f_j$ 的最大值。

分完类之后，我们发现，我们最后要求的就是对于 $sum_j < sum_i$ 的 $f_j-j$ 的最大值和 $sum_j>sum_i$ 的 $f_j+j$ 的最大值。这样子就可以用线段树来维护了。但是要注意，$a_i$ 很大，$sum_i$ 会更大，所以要先离散化 $sum_i$，然后再用线段树维护。

# CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 500005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, a[N], s[N], tr[N << 2][2], f[N], ans, nls[N], t[N];
map <ll, ll> ls;
il void init(){
	ls.clear();
	for (int i = 1; i <= n * 4; i++) tr[i][0] = tr[i][1] = t[i] = -1e18;
}
void add(ll p, ll l, ll r, ll x, ll fk, ll k){
	if (l == x && r == x){
		tr[p][0] = max(tr[p][0], fk - k);
		tr[p][1] = max(tr[p][1], fk + k);
		return ;
	}
	if (l > x || r < x) return ;
	ll mid = (l + r) >> 1;
	add(p << 1, l, mid, x, fk, k), add(p << 1 | 1, mid + 1, r, x, fk, k);
	tr[p][0] = max(tr[p << 1][0], tr[p << 1 | 1][0]);
	tr[p][1] = max(tr[p << 1][1], tr[p << 1 | 1][1]);
}
ll ask(ll p, ll l, ll r, ll nl, ll nr, ll d){
	if (nl <= l && r <= nr) return tr[p][d];
	if (nl > r || nr < l) return -1e18;
	ll mid = (l + r) >> 1;
	return max(ask(p << 1, l, mid, nl, nr, d), ask(p << 1 | 1, mid + 1, r, nl, nr, d)); 
}
int main(){
	for (int T = rd(); T--;){
		n = rd();
		init();//多测不清空，_____
		for (int i = 1; i <= n; i++) a[i] = rd(), s[i] = s[i - 1] + a[i], nls[i] = s[i];nls[n + 1] = 0;
		sort (nls + 1, nls + n + 2);
		ll cnt = unique(nls + 1, nls + n + 2) - nls - 1;
		for (int i = 1; i <= cnt; i++) ls[nls[i]] = i;
		for (int i = 1; i <= n; i++){
			ll sl = ls[s[i]];
			f[i] = max(ask(1, 1, cnt, 1, sl - 1, 0) + i, ask(1, 1, cnt, sl + 1, cnt, 1) - i);
			f[i] = max(f[i], t[sl]);
			f[i] = max(f[i], s[i] > 0 ? i : (s[i] < 0 ? -i : 0ll));
			add(1, 1, cnt, sl, f[i], i), t[sl] = max(t[sl], f[i]);
			//cout << f[i] << " ";
		}
		printf ("%lld\n", f[n]);
	}
	return 0;
}

```

---

## 作者：紊莫 (赞：0)

提供一个只需要两颗树状数组的做法。

---

首先对于 DP 方程分讨。

$$
f_i = \begin{cases}
{\color{Red} f_j - j } + i  & \text{ if } s_i>s_j \\
{\color{Red} f_j}  & \text{ if } s_i = s_j \\
{\color{Red} f_j + j } - i  & \text{ if } s_i<s_j
\end{cases}
$$

然后维护标红的部分即可。

此处采用权值树状数组维护前缀和后缀最大值，解决一、三两个转移。

对于第二个转移，单点修改，单点查询，使用高贵的数组来记录。

此外，此题需要离散化（也可使用动态开点线段树，但是树状数组常数较小），其余细节参见代码。

```cpp
const int N = 500005, M = (N << 1), inf = 1e16, mod = 1e9 + 7;
int n, m, a[N], s[N], f[N], y[N];
struct BIT {
	//这是一个能维护前缀后缀的树状数组，TYPE表示种类。
  int t[N], nn;
  void init(int x) {
    nn = x;
    F(i, 0, nn) t[i] = -inf;
  }
  void add(int x, int v, int TYPE) {
    if (TYPE)
      for (; x <= nn; x += x & -x) t[x] = max(t[x], v);
    else
      for (; x > 0; x -= x & -x) t[x] = max(t[x], v);
  }
  int query(int x, int TYPE) {
    int res = -inf;
    if (!TYPE)
      for (; x <= nn; x += x & -x) res = max(res, t[x]);
    else
      for (; x > 0; x -= x & -x) res = max(res, t[x]);
    return res;
  }
} x, z;
map<int, int> mp;
void init(int tot = 0) {
  set<int> S;
  S.insert(0);
  F(i, 1, n) S.insert(s[i]);
  mp.clear();
  for (auto i : S) mp[i] = ++tot;
  x.init(tot + 1), z.init(tot + 1);
  F(i, 0, n + 1) f[i] = y[i] = -inf;
  f[0] = 0, y[mp[0]] = 0;
  x.add(mp[0], 0, 1), z.add(mp[0], 0, 0);
}
void solve() {
  cin >> n;
  F(i, 1, n) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }
  init();//初始化过程：离散化和赋初值。
  F(i, 1, n) {
    int P = mp[s[i]];
    //分别对应上文三种转移。
    f[i] = max({x.query(P - 1, 1) + i, y[P], z.query(P + 1, 0) - i});
    //更新数据结构情况。
    x.add(P, f[i] - i, 1), y[P] = max(y[P], f[i]), z.add(P, f[i] + i, 0);
  }
  cout << f[n] << endl;
}
```

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1667B)

## 前言
树状数组优化 DP 的比较板子的题，浅浅记录一下套路。

## 分析
由题意我们很容易得到 DP 方程：记 $f_i$ 为前 $i$ 个数的最大答案。则有以下转移：

$$f_i = \max_{1\le j < i} \{ \ f_j + val\ \}$$

$val$ 是根据题目计算的贡献。我们现在就得到了 $O(n^2)$ 的 DP。

## 优化
记 $s_i$ 为前 $i$ 个数的前缀和。将上面的 DP 方程分类讨论：

$$f_i = \max_{1 \le j < i} \begin{cases}
f_j+i-j & s_i > s_j \\
f_j & s_i = s_j \\
f_j-(i-j) & s_i < s_j
\end{cases}$$

$$= \max_{1 \le j < i} \begin{cases}
(f_j-j)+i & s_i > s_j \\
f_j & s_i = s_j \\
(f_j+j)-i & s_i < s_j
\end{cases}$$

现在，我们只需要动态维护 $f_j-j$，$f_j$，$f_j+j$ 的最大值就行了。根据 $s_i$ 与 $s_j$ 的大小关系可以知道：$f_j-j$ 应该是前缀最大值，$f_j+j$ 是后缀最大值（前后缀指的是值域上的）。

显然，$f_j-j$ 与 $f_j+j$ 可以用树状数组维护（分别是前缀和后缀），$f_j$ 直接用桶维护即可。

至此我们 $O(n \log n)$ 地解决了这个问题。

## 注意
 1. 值域很大，要离散化。
 2. 记得开 long long。
 3. 多测清空不要 `memset`。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)
using namespace std;

const int N = 5e5 + 10, inf = 1e9;
int n, a[N];
ll s[N], b[N], c[N], ans;
vector<ll> nums;

struct bit1 {
	ll tr[N];
	inline void add(int x, ll v) {
		for (; x < n + 5; x += lowbit(x)) tr[x] = max(tr[x], v);
	}
	inline ll query(int x) {
		ll res = -inf;
		for (; x; x -= lowbit(x)) res = max(res, tr[x]);
		return res;
	}
} T1;

struct bit2 {
	ll tr[N];
	inline void add(int x, ll v) {
		for (; x; x -= lowbit(x)) tr[x] = max(tr[x], v);
	}
	inline ll query(int x) {
		ll res = -inf;
		for (; x < n + 5; x += lowbit(x)) res = max(res, tr[x]);
		return res;
	}
} T2;

void init() {
	for (int i = 0; i <= n + 5; i++) T1.tr[i] = T2.tr[i] = c[i] = -inf;
	nums.clear(); nums.push_back(0);
}

void solve() {
	scanf("%d", &n);
	init();
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
		nums.push_back(s[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 0; i <= n; i++)
		b[i] = lower_bound(nums.begin(), nums.end(), s[i]) - nums.begin() + 1;
	T1.add(b[0], 0); T2.add(b[0], 0);
	c[b[0]] = 0;
	for (int i = 1; i <= n; i++) {
		ll tmp = -inf;
		tmp = max(tmp, T1.query(b[i] - 1) + i);
		tmp = max(tmp, T2.query(b[i] + 1) - i);
		tmp = max(tmp, c[b[i]]);
		ans = tmp;
		T1.add(b[i], tmp - i);
		T2.add(b[i], tmp + i);
		c[b[i]] = max(c[b[i]], tmp);
	}
	printf("%lld\n", ans);
}

int main() {
	int T; cin >> T;
	while (T--) solve();
	return 0;
}
```


---

