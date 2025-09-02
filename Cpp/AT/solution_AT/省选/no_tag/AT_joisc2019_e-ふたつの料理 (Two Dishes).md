# ふたつの料理 (Two Dishes)

## 题目描述

有两道菜 $A$ 和 $B$，分别有 $n$ 道和 $m$ 个步骤，时间从 $0$ 时刻开始。每个步骤都有三个参数 $t,e,c$ 表示该步骤需要 $t$ 时间完成，若其在 $e$ 时刻前完成，则你获得 $c$ 的分数，$c_i$ 可能为负。

你需要决策进行步骤的次序，每时每刻都只能进行一个步骤；每个步骤都必须连续进行，不能拆开；同时要求每道菜内部都必须按照顺序进行，两道菜菜之间互不影响，求最大分数和。

$1\le n,m\le 10^6$，$1\le t_i\le 10^9$，$1\le e_i\le 2\times 10^{15}$，$|c_i|\le 10^9$。

# 题解

## 作者：DaiRuiChen007 (赞：14)

# JOISC2019E 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2019_e)

**题目大意**

> 给一个长度为 $n$ 的序列 $A$ 和一个长度为 $m$ 的序列 $B$，现在要将在保证相对顺序的前提下合并两个序列。
>
> 每个元素有三个参数 $t_i,e_i,c_i$，表示任务 $i$ 需要 $t_i$ 秒完成，在第 $e_i$ 秒前完成会获得 $c_i$ 的分数。
>
> 求最大可能的分数和。
>
> 数据范围：$n,m\le 10^6$。

**思路分析**

对于 $A$ 中的元素，在他前面的 $A$ 中元素是确定的，因此 $e$ 的限制等价于限制 $A_i$ 前面至多只能有 $p_i$ 个 $B$ 才会有分数。

同理 $B$ 里的元素限制为 $B_i$ 前面至多只能有 $q_i$ 个 $A$ 才会有分数。

考虑统一转化模型：

- 对 $B_i$ 的限制等价于选 $A_{q_i}$ 的时候如果已经选了 $B_i$ 就会有 $+w_i$ 的贡献。
- 对 $A_i$ 的限制考虑反面考虑，先把 $w_i$ 加入答案，选 $A_{i}$ 的时候如果已经选了 $B_{p_i}$ 就会有 $-w_i$ 的贡献。

然后考虑维护 $dp_{i,j}$ 表示插入 $A_1\sim A_i,B_1\sim B_j$，对于所有 $j$ 有数据结构维护，需要支持：若干次后缀加，然后取前缀 $\max$。

用 `std::set` 或 `std::map` 维护差分数组，取前缀 $\max$ 等价于不断删掉原有的差分项并把值相加，直到当前值非负。

显然每个差分项只会被删除一次，因此复杂度是对的。

注意我们实际上是每加一个数就取一次前缀 $\max$，我们要先操作正数再操作负数。

时间复杂度 $\mathcal O((n+m)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e6+5;
const ll inf=1e18;
ll a[MAXN],s[MAXN],p[MAXN],b[MAXN],t[MAXN],q[MAXN],ans=0;
vector <array<ll,2>> f[MAXN];
map <int,ll> dp;
inline void add(int id,ll val) {
	for(auto it=dp.lower_bound(id);val<0;it=dp.erase(it)) {
		id=it->first,val+=it->second;
	}
	dp[id]+=val;
}
signed main() {
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i]>>s[i]>>p[i],a[i]+=a[i-1];
	for(int i=1;i<=m;++i) cin>>b[i]>>t[i]>>q[i],b[i]+=b[i-1];
	for(int i=1;i<=n;++i) if(s[i]>=a[i]) {
		int j=upper_bound(b+1,b+m+1,s[i]-a[i])-b;
		ans+=p[i];
		if(j<=m) f[i].push_back({j,-p[i]});
	}
	for(int j=1;j<=m;++j) if(t[j]>=b[j]) {
		int i=upper_bound(a+1,a+n+1,t[j]-b[j])-a;
		if(i<=n) f[i].push_back({j,q[j]});
		else ans+=q[j];
	}
	dp[m+1]=inf;
	for(int i=1;i<=n;++i) {
		sort(f[i].begin(),f[i].end(),[&](auto x,auto y){ return x[1]>y[1]; });
		for(auto k:f[i]) add(k[0],k[1]);
	}
	for(auto x:dp) if(x.first<=m) ans+=x.second;
	cout<<ans<<"\n";
	return 0;
}
```



---

## 作者：紊莫 (赞：11)

这个题并不难，在此写一篇比较易懂的题解。

### 约定

$\text{A, B}$ 表示题中的两道菜，也就是任务序列。

$s_i$ 表示 $\text{A}$ 中第 $i$ 个任务的限定时间，$p_i$ 表示其代价。

$t_i$ 表示 $\text{B}$ 中第 $i$ 个任务的限定时间，$q_i$ 表示其代价。

---

首先 $\mathcal{O}(n^2)$ 的 DP：

设 $f(i, j)$ 表示 $\text{A}$ 序列中选取了 $[1, i]$，$\text{B}$ 序列中选取了 $[1, j]$ 的最优代价。

转移考虑 $f(i, j) \to f(i + 1, j)$ 和 $f(i, j) \to f(i, j + 1)$，因为 $i, j$ 确定了，当前的时间也是确定的，转移是简单的。

首先考虑把题目中所给的关于时间的限制转化一下：

对于 $A_i$ 这个任务，要求完成时间 $\le s_i$，注意到一个事实，我们在完成了 $A_i$ 的时候，一定完成了 $A_{1\dots i - 1}$ 中所有的任务。

那么我们在 $B$ 序列中至多能做的任务是一个前缀。

同理，对 $B$ 序列的也有类似的定义，形如做完了 $B_i$，且完成时间在 $t_i$ 内（也就是可以得到权值），那么此时 $A$ 中最多做 $x$ 个任务。

我们把两者的形式统一，为此，我们先假设所有 $p_i$ 都能被顺利得到，尽管这不一定，然后再把得不到的从答案中减去。

对于 $B_i$ 的形式为，当我们**将要**选择 $A_x$ 时，若此时 $B_i$ 已经被完成了，那么答案加上 $q_i$。

对于 $A_i$ 的形式为，当我们**将要**选择 $A_i$ 时，若此时 $B_x$ 已经被完成了，那么答案减去 $p_i$。

这些操作都可以挂在对应的 $x$ 上。

然后我们还是维护 $f(i, j)$ 这个 DP。

我们对 $i$ 这一维扫描线，动态的维护当前的 $f(j)$。

每一次操作中若此时 $B_x$ 已经被完成了，相当于是对一段后缀加上一个权值，然后做一次前缀 $\max$。

前缀 $\max$ 是怎么来的呢？

考虑另一种刻画问题的方法，我们将其看作是一个格路模型，$f(i, j)$ 就是到 $(i, j)$ 这个点的最大权值。

我们把权值都附在格子中（区别于 $(i, j)$ 这样的格点），那么 $f(i, j) \to f(i + 1, j)$ 就是加上线段 $(i, j) \to (i + 1, j)$ 下方格子的权值。

向上不会增加任何权值，但是 $f(i, j) \to f(i, j + 1)$，在 DP 数组上体现为前缀 $\max$。

最后我们实现这个后缀加，前缀 $\max$ 即可，我们采用差分的方法，记录 DP 数组的差分数组为 $c$，那么对于 $[x, m]$ 的后缀加可以看作是 $c_x$ 的单点加。

如何求解前缀 $\max$ 呢？

分类讨论一下，如果加上的是一个正整数，那么前缀 $\max$ 显然是不变的，只需要在 $c_x$ 修改一下即可。

如果是一个负数，那么可能会出现如下的情况（黑实线表示真实的 DP 值）。

![](https://cdn.luogu.com.cn/upload/image_hosting/tihkr449.png)

那么发现我们只需要找到第一处差分数组之和大于等于下降高度 $val$ 的地方，修改其值即可。

最后一个小问题，我们需要对 $f(j)$ 先加后减，因为我们每次都会取前缀 $\max$，如果先操作负数，可能会出现一个值很小了，但是被前缀 $\max$ 变大，然后再做加法就会偏大。

差分数组只用记录非 $0$ 的位置，每次删除的复杂度均摊是对的，总复杂度线性对数。

---

## 作者：KellyFrog (赞：8)

考虑朴素的 dp：$f_{i,j}$ 表示 $A$ 进行完了 $i$ 步骤，$B$ 进行完了 $j$ 步骤的最大分数和。

记 $pa_i,pb_i$ 表示 A/B 的第 $i$ 个步骤获得分数至少要在另一个序列中的位置。

显然 $f_{i,j}=\max\{f_{i-1,j},f_{i,j-1}+[i\le pb_j]cb_j\}+[j\le pa_i]ca_i$。

考虑这个步骤 $i$ 增大 $1$ 的过程，即先将一个前缀加上一个值，然后进行一个 $f_{i,j}\leftarrow\max(f_{i,j},f_{i,j-1}+[i\le pos_j]cb_j)$ 的过程。

显然这提示我们维护差分，具体地，我们维护 $d_j=f_{i,j}-(f_{i,j-1}+[i\le pb_j]cb_j)$。

对于第一部分前缀 $+c_i$，显然是整体抬升/下降，中间不变，只需要处理最后一个点对后边的贡献即可。

假设最后的这个点改变了 $x$。

如果 $x<0$，那么显然后边都不变，修改下一项的差分 $-x$ 即可。

如果 $x\ge 0$，可以发现每次会“吸收”一部分 $x$，后边会有一个 $\sum d_j\le x$ 的前缀被推成 $0$。

还有就是可能有 $[i\le pb_j]$ 变为 $0$，跟上边是一样的。

直接用 `set` 维护不为 $0$ 的差分位置即可，需要注意更新顺序。

总复杂度 $O((n+m)\log m)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 1e6 + 5;

int n, m;
ll a[N], b[N], c[N], sa[N];
ll d[N], e[N], f[N], sb[N];
ll dt[N];
int p1[N], p2[N];
vector<int> adj[N];
set<int> st;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) cin >> a[i] >> b[i] >> c[i];
	rep(i, 1, m) cin >> d[i] >> e[i] >> f[i];
	rep(i, 1, n) sa[i] = sa[i-1] + a[i];
	rep(i, 1, m) sb[i] = sb[i-1] + d[i];
	rep(i, 1, n) p1[i] = upper_bound(sb, sb + m + 1, b[i]-sa[i]) - sb - 1;
	rep(i, 1, m) p2[i] = upper_bound(sa, sa + n + 1, e[i]-sb[i]) - sa - 1;
	rep(i, 1, m) if(p2[i] >= 0) {
	   	adj[p2[i]].pb(i);
	}
	rep(i, 1, n) {
		for(int j : adj[i-1]) {
			if(f[j] >= 0) dt[j] += f[j], st.emplace(j);
		}
		if(p1[i] >= 0) {
			if(c[i] <= 0) {
				dt[0] += c[i];
				dt[p1[i]+1] -= c[i];
				st.emplace(0), st.emplace(p1[i]+1);
			} else {
				dt[0] += c[i];
				st.emplace(0);
				ll df = c[i];
				auto it = st.lower_bound(p1[i]+1);
				while(df && it != st.end()) {
					int j = *it;
					ll t = min(df, dt[j]);
					dt[j] -= t, df -= t;
					if(df) it = st.erase(it);
				}
			}
		}
		for(int j : adj[i-1]) {
			if(f[j] < 0) {
				ll tt = min(dt[j], -f[j]);
				ll df = -f[j] - tt;
				dt[j] -= tt;
				auto it = st.lower_bound(j);
				while(df && it != st.end()) {
					int k = *it;
					ll t = min(df, dt[k]);
					df -= t, dt[k] -= t;
					if(df) it = st.erase(it);
				}
			}
		}
	}
	ll ans = 0;
	rep(i, 0, m) {
		ans += dt[i] + (p2[i] == n) * f[i];
	}
	cout << ans << "\n";

	return 0;
}

```

---

## 作者：Rainy7 (赞：6)

### 题目大意

> 两道料理分别要 $n,m$ 个操作。做菜需要按顺序。第一道菜第 $i$ 个步骤用时 $a_i$，如果在第 $s_i$ 前完成得分 $p_i$；第二道菜第 $i$ 个步骤用时 $b_i$，如果在第 $t_i$ 前完成得分 $q_i$。
>
> 最大化评分。
>
> 保证 $1 \le n,m, \le 10^6,1\le a_i,b_j \le 10^9,1 \le s_i,t_i \le 10^{15},|p_i|,|q_i| \le 10^9$。

### 题解

不妨设 $f(x,y)$ 表示第一道菜到步骤 $x$，第二道菜到步骤 $y$ 的最大评分。转移都是枚举上一个位置，类似走放方格。相当于就是从 $(0,0)$ 走到 $(n,m)$ 的最大评分。

于是考虑把评分看成点，点 $(i,s_i)$ 有收益当且仅当他在路径上方，$(j,t_j)$ 在路径下方。因为不在一个边很烦，所以将答案先加上 $\sum p_i$，然后将点 $(i,s_i)$ 的权值 $a_{i,s_i}$ 设为 $-p_i$。

预处理个前缀和，设 $s_{i,j} = \sum\limits_{x=0}^y a_{i,x}$。所以有转移：
$$
f(i,j) = \max\{ f(i,j-1) , f(i-1,j) + s_{i-1,j} \}
$$
对一行转移分析。考虑下 $f(x)$ 的性质，显然 $f(x)$ 是单调的，它相当于将 $f(x-1)$ 值加上 $s(x-1)$ 然后取前缀最大值。

所以我们差分一下 $f(x)$，得到的差分数组 $d(i)$ 一定非负。

如果我们对 $d(i)$ 加上一个正数，那么有影响只有位置 $i$。

如果加上一个负数 $x$，若 $d(i)$ 变成 $<0$，则会变成 $0$。接着会影响后面值。可以发现，他会是后面连续一段总和最多为 $-x$ 的数都变成 $0$，所以可以用线段树二分维护。

复杂度是 $\mathcal{O}((n+m) \log m)$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=1e6+5;
const ll inf=1e18;
struct node{
	ll x,y;
	friend bool operator < (node u,node v){
		return (u.x==v.x)?(u.y<v.y):(u.x>v.x);
	}
};
ll n,m,ans,a[N],s[N],p[N],b[N],r[N],q[N];
vector<node> vc[N];
struct tree{
	ll sum[N<<2],tag[N<<2];
	void pushup(ll k){
		sum[k]=sum[k<<1]+sum[k<<1|1];
	}
	void pushdown(ll k)
	{	if(!tag[k])return;
		sum[k<<1]=sum[k<<1|1]=0,tag[k<<1]=tag[k<<1|1]=1;
		tag[k]=0;
	}
	void modify(ll k,ll l,ll r,ll x,ll y)
	{	if(l==r){sum[k]+=y;return;}
		pushdown(k);
		ll mid=(l+r)>>1;
		if(x<=mid)modify(k<<1,l,mid,x,y);
		else modify(k<<1|1,mid+1,r,x,y);
		pushup(k);
	}
	void reset(ll k,ll l,ll r,ll x,ll y)
	{	if(x>y||l>y||r<x)return;
		if(x<=l&&r<=y){sum[k]=0,tag[k]=1;return;}
		pushdown(k);
		ll mid=(l+r)>>1;
		if(x<=mid)reset(k<<1,l,mid,x,y);
		if(y>mid)reset(k<<1|1,mid+1,r,x,y);
		pushup(k);
	}
	ll query(ll k,ll l,ll r,ll x,ll y)
	{	if(x>y||l>y||r<x)return 0;
		if(x<=l&&r<=y)return sum[k];
		pushdown(k);
		ll mid=(l+r)>>1;
		if(y<=mid)return query(k<<1,l,mid,x,y);
		if(x>mid)return query(k<<1|1,mid+1,r,x,y);
		return query(k<<1,l,mid,x,y)+query(k<<1|1,mid+1,r,x,y);
	}
	ll solve(ll k,ll l,ll r,ll x,ll y,ll pr,ll v)
	{	ll mid=(l+r)>>1,res=inf;
		if(x<=l&&r<=y)
		{	if(l==r)
			{	if(pr+sum[k]>=v)return l;
				return inf;
			}
			pushdown(k);
			if(sum[k<<1]+pr>=v)return solve(k<<1,l,mid,x,y,pr,v);
			else return solve(k<<1|1,mid+1,r,x,y,pr+sum[k<<1],v);
		}
		pushdown(k);
		if(x<=mid)res=min(res,solve(k<<1,l,mid,x,y,pr,v));
		if(y>mid)res=min(res,solve(k<<1|1,mid+1,r,x,y,pr+query(k<<1,l,mid,x,y),v));
		return res;
	}
}T;
int main()
{	//freopen("data.in", "r", stdin);
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
	{	scanf("%lld%lld%lld",&a[i],&s[i],&p[i]);
		a[i]+=a[i-1],s[i]=s[i]-a[i];
	}
	for(ll i=1;i<=m;i++)
	{	scanf("%lld%lld%lld",&b[i],&r[i],&q[i]);
		b[i]+=b[i-1],r[i]=r[i]-b[i];
	}
	for(ll i=1;i<=n;i++)
	{	if(s[i]<0)continue;
		ll pos=upper_bound(b+1,b+1+m,s[i])-b;
		if(pos<=m)vc[i-1].push_back((node){-p[i],pos});
		ans+=p[i];
	}
	for(ll i=1;i<=m;i++)
	{	if(r[i]<0)continue;
		ll pos=upper_bound(a+1,a+1+n,r[i])-a;
		vc[pos-1].push_back((node){q[i],i});
	}
	for(ll i=0;i<n;i++)
	{	sort(vc[i].begin(),vc[i].end());
		for(ll j=0;j<(int)vc[i].size();j++)
		{	node v=vc[i][j];
			if(v.x>=0)T.modify(1,0,m,v.y,v.x);
			else{
				ll x=T.solve(1,0,m,v.y,m,0,-v.x);
				if(x==inf)T.reset(1,0,m,v.y,m);
				else T.modify(1,0,m,x,v.x+T.query(1,0,m,v.y,x-1)),T.reset(1,0,m,v.y,x-1);
			}
		}
	}
	ans+=T.sum[1];
	for(ll i=0;i<(int)vc[n].size();i++)ans+=vc[n][i].x;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：MatrixGroup (赞：4)

## 题意

给定 $n$ 道类型 A 的菜，$m$ 道类型 B 的菜，第 $i$ 道类型 A 的菜需要 $A_i$ 分钟制作，第 $j$ 道类型 B 的菜需要 $B_j$ 分钟制作。同一种类型的菜必须按照顺序制作。制作过程不得有休息，同一道菜必须连续制作。

如果在前 $S_i$ 分钟完成了第 $i$ 道类型为 A 的菜，会获得 $P_i$ 的得分。如果在前 $T_j$ 分钟完成了第 $j$ 道类型为 B 的菜，会获得 $Q_j$ 的得分。请求出最大可能的得分和。

$n,m\le 10^6$。

## 题解

假设 $n,m$ 同阶。

我们首先可以将分钟这个限制改掉：我们知道，完成第 $i$ 道类型 A 的菜，一定需要 $\sum\limits_{k=1}^iA_k$ 分钟花在类型 A 的菜上，由此计算出最多可以制作类型 B 的菜多长时间，进而求出最多可以制作类型 B 的菜多少道。特别地，如果不可能实现/一定会实现，直接先对答案处理即可。

我们将限制转化成了「在做第 $i/j$ 道类型 A/B 的菜在做第 $j/i$ 道类型 B/A 的菜之前，可以获得 $x$ 的得分」。我们可以将其中一种化为另外一种：「在做第 $j$ 道类型 B 的菜在做第 $i$ 道类型 A 的菜之前，可以获得 $x$ 的得分」等价于「先获得 $x$ 的得分，如果在做第 $i$ 道类型 A 的菜在做第 $j$ 道类型 B 的菜之前，可以获得 $-x$ 的得分」。

我们使用网格图刻画这个问题。我们将做一道类型 A 的菜刻画为向右走，将做一道类型 B 的菜刻画为向上走。我们考虑如何刻画「做第 $i$ 道类型 A 的菜」和「已经做过了第 $j$ 道类型 B 的菜」。

![](https://cdn.luogu.com.cn/upload/image_hosting/r1u9vst5.png)

可以发现，「做第 $i$ 道类型 A 的菜」相当于图上的绿色箭头，「已经做过了第 $j$ 道类型 B 的菜」相当于图上的红色区域。因此，走过灰色框内的箭头便会有一个权值 $x$。

我们考虑朴素的动态规划：$dp_{i,j}$ 表示走到 $(i,j)$ 的最大权值。我们可以让 $i$ 成为时间维，从左向右计算答案。那么，向上走一步代表值前缀取 $\max$，而向右走一步相当于后缀加。

我们考虑另一个问题：维护一个数组，支持一种操作：后缀加之后**立刻**前缀取 $\max$。这个可以通过维护差分值不为 $0$ 的元素通过 `std::set` 在 $O(n\log n)$ 时间内完成：后缀减掉一个数之后暴力向右填坑即可。可以通过均摊证明复杂度的正确性。

这个问题与原问题的不同点在于 $i$ 相同的权值必须加完之后取前缀 $\max$。可以证明，按照从正到负的顺序排序之后，按照新问题解决一定不会影响答案。因此，我们在 $O(n\log n)$ 的时间复杂度内解决了本题。

## 实现

```cpp
const int N=1000006;
int n,m;
ll a[N],s[N],p[N],b[N],t[N],q[N];
int f[N],g[N];
vector<pair<int,ll> > vc[N];
ll toadd;
bool cmp(const pair<int,ll>&A,const pair<int,ll>&B)
{
	return A.second>B.second;
}
struct DataStructure{
	set<pair<int,ll> > S;
	void init()
	{
		S.insert(mp(0,0ll));
		S.insert(mp(1145141919,123456789012345678ll));
	}
	void add(int bg,ll val)
	{
		while(val<0)
		{
			set<pair<int,ll> >::iterator itr=S.lower_bound(mp(bg,-123456789012345678ll));
			val+=itr->se;
			bg=itr->fi;
			S.erase(itr); 
		}
		if(val>0)
		{
			S.insert(mp(bg,val));
		}
	}
	ll query()
	{
		ll ret=0;
		for(set<pair<int,ll> >::iterator itr=S.begin();itr!=S.end();++itr)
		{
			if(itr->first<1145141919)
			ret+=itr->second;
		}
		return ret;
	}
};
DataStructure DS;
int main()
{
	cin>>n>>m;
	rep1(i,n)cin>>a[i]>>s[i]>>p[i];
	rep1(i,m)cin>>b[i]>>t[i]>>q[i];
	rep1(i,n)a[i]+=a[i-1];rep1(i,m)b[i]+=b[i-1];
	rep1(i,n)
	{
		if(s[i]<a[i])
		{
			f[i]=0;
		}
		else
		{
			f[i]=upper_bound(b,b+m+1,s[i]-a[i])-b;
			if(f[i]==m+1)
			{
				toadd+=p[i];
			}
			else
			{
				vc[f[i]].pb(mp(i,p[i]));
			}
		}
	}
	rep1(i,m)
	{
		if(t[i]<b[i])
		{
			g[i]=0;
		}
		else
		{
			g[i]=upper_bound(a,a+n+1,t[i]-b[i])-a;
			if(g[i]==n+1)
			{
				toadd+=q[i];
			}
			else
			{
				vc[i].pb(mp(g[i],-q[i]));toadd+=q[i];
			}
		}
	}
	DS.init();
	rep1(i,m)
	{
		rep(j,vc[i].size())
		{
			pair<int,ll> Q=vc[i][j];
			if(Q.se>=0)
			DS.add(Q.fi,Q.se);
		}
		rep(j,vc[i].size())
		{
			pair<int,ll> Q=vc[i][j];
			if(Q.se<0)
			DS.add(Q.fi,Q.se);
		}
		
	}
	cout<<toadd+DS.query()<<endl;
	return 0;
}
```

---

## 作者：Z1qqurat (赞：2)

赛前写题解增加 rp。~~今天我的瞪代码补题法被 calvin 瑞平为【】式学习法了，但是菜菜的我除了这个也不会别的了，所以整个理解都是瞪着题解代码 yy 出来的，有很大概率出错。~~ 从考场部分分的角度来理解这个思路。以下默认 $n,m$ 同阶，有的复杂度直接都按照 $n$ 写了。

我是普及组小朋友，我会 $\mathcal{O}(nm)$ dp！考虑设 $f_{i,j}$ 表示当前选了 $a_{1\sim i},b_{1\sim j}$ 可以产生的最大贡献值，转移显然是单次 $\mathcal{O}(1)$，因为只需要枚举目前这一次选 $a_{i+1}$ 还是 $b_{j+1}$ 就可以了。显然不太能优化啥的，毕竟这个状态维度降不下去。

我是 AT 战神，我精通格路模型！发现走 $a_{i+1},b_{j+1}$ 可以看作**相对独立**的两维，所以考虑转化为格路，选择 $a$ 看作向右走一格，选 $b$ 看作向上走一格，那么相当于要求出一条从 $(0,0)$ 到 $(n,m)$ 的符合条件的最大权值路径。

我是数据结构萌新，我不会颜色段均摊也不会写 ODT！所以不考虑 $p,q\ge 1$ 的特殊部分分，直接想怎么把限制转化到网格图上。联系一下某个看起来很水的部分分：$s_1=s_2=\cdots=s_n=t_1=t_2=\cdots=t_m$，做法就是发现在 $s$ 之前选出的 $a,b$ 肯定各是一段前缀，考虑枚举 $a$ 中选出的那一段前缀 $1\sim i$，然后肯定可以直接得到 $b$ 选出的是哪一段前缀，用指针可以做到 $\mathcal{O}(n+m)$。虽然这个部分分看起来很鸡肋，但是它倒是给了正解做法一点小启发：考虑如果我们希望在选 $a_i$ 时可以拿下 $p_i$ 的贡献，能直接求出一个 $j$ 表示如果要拿下 $p_i$，在填 $a_i$ 之前至多选 $b$ 的前缀到 $b_j$（这个 $j$ 很好求，其实就是满足 $\sum\limits_{k=1}^i a_k+\sum\limits_{k=1}^j b_k\le s_i$ 的最大 $j$），也就是说**我们的格路一定要在点 $(i,j)$ 之下**。同理地，对于每个 $b_i$，设 $j$ 为满足 $\sum\limits_{k=1}^j a_k+\sum\limits_{k=1}^i b_k\le t_i$ 的最大数，那么**格路一定要在 $(j,i)$ 之上**。

也就是说我们把权值的计算转化为“满足某个条件就可以获得该权值”，然后把这个条件扔到了网格上。设对于每个 $a_i$ 求出的限制 $c_i=j+1$，对于每个 $b_i$ 求出的限制 $d_i=j+1$，那么相当于格路一定要在每个 $(i,c_i)$ 之上（可以恰好经过）就能得到 $p_i$，每个 $(d_i,i)$ 之下（可以恰好经过）就能得到 $q_i$。把两个限制转化为同一种形式，先给答案加上 $p_i$，然后变成两种点，格路在 $(i,c_i)$ 之下就能得到 $-p_i$，格路在 $(d_i,i)$ 之下就能得到贡献 $q_i$，最大化格路的总权值。

我切穿 AT 的 dp 系列题，我擅长一切 dp 以及其状态优化！先设一个很劣的状态 $f_{i,j}$ 表示当前格路走到点 $(i,j)$ 的最大权值，考虑 $f_{i-1}\to f_i$。分为两步，$f_{i-1,j}\to f_{i,j}$，那么加上在 $(i,j)$ 之下包住的所有点权值即可；然后 $f_{i,j-1}\to f_{i,j}$（这个按照纵坐标从小到大顺次转移），发现不需要加额外权值。前者相当于枚举所有在第 $j$ 列的点，它们的权值对 $f_i$ 做一个后缀加，而后者相当于 $f_i$ 每一项都做前缀 checkmax。试着维护 $f_i$ 的差分，那么一次后缀加可以这样理解（任何情况下，只要 checkmax 没有遗漏，差分数组都是非负的）：

![](https://pic.imgdb.cn/item/65e08c1f9f345e8d039c7608.jpg)

如果后缀加 $(x,w)$，$w\ge 0$，那么只会影响到至多一个点的 $diff$ 值（因为后缀都会直接一样地改，$diff$ 不会变），此时暴力维护这个 $diff$ 的变化就是了。

如果 $w<0$ 呢？

![](https://pic.imgdb.cn/item/65e08c1e9f345e8d039c756e.jpg)

那么发现暂时地，一段区间 $[x,y)$ 内的 $f$ 值仍然会取一个原先的未受 $w$ 影响的最大值，此时会导致 $diff_{x\sim y-1}$ 都被推平成 $0$。（写到这里突然感觉非常地颜色段均摊啊！$p,q\ge 1$ 的颜色段均摊做法是不是一个意思？）然而到了一个点 $y$，$w+\sum\limits_{i=x}^{y} diff_i\ge 0$，这其实就是新的 $f_y-f_{x-1}$，此时 $f_{x-1}$ 是 $f_{x\sim y-1}$ 中的前缀 $\max$，而 $f_y-f_{x-1}\ge 0$ 说明 $f_y$ 成为了一个更大的取值，更新了 $f$ 值，之后的 $diff_{y+1\sim m}$ 仍然不会改变。而这样以来，我们只需要把 $diff_{x\sim y-1}$ 推平成 $0$，$diff_y=w+\sum\limits_{i=x}^{y} diff_i$，后面的不用变。被推平的那一段我们直接把它整个缩到 $y-1$ 这个位置上，如果能保证依次插入的 $w$ 单调不增，那么就可以保证推平的这一段以后不会再分裂了。所以 $w<0$ 时，每次在去掉至少一个现在已经变成 $0$ 了的差分项，至多再加入一个新的差分项，维护 dp 的总复杂度 $\mathcal{O}(n+m)$（因为有效的后缀加的点至多 $n+m$ 个，然后只有在每次后缀加的时候才需要更新 $diff$），然后再加上一开始二分找 $c_i,d_i$，总复杂度 $\mathcal{O}((n+m)\log n)$，当然指针也可以做到线性，不过区别不大了。

整个过程下来我认为比较流畅，只要像我一样不会颜色段均摊就能比较自然地推到这个正解，过程中也解释了 $p,q\ge1$ 中颜色段均摊在正解做法中的体现（？我不知道是不是哈，纯属我感性理解），这个题给了我关于格路模型的很大启发，也有一种做题方式的体现：想不通可以手模画点图的。只是希望能以这个过程为自己在省选赛场上解题做一个示范吧。

[Submission.](https://loj.ac/s/2017174)

---

## 作者：Milmon (赞：1)

把一个方案转化为从 $(0,0)$ 到 $(n,m)$ 的一条折线（每次向右或向上），而题目所给的每个信息可以转化为在例如第一道菜第 $i$ 个步骤结束前第二道菜至多进行了 $j$ 个步骤就可以获得若干贡献。然后可以转化为有若干个点有权值，最终的满意度就是折线下方的点的权值之和（上方的条件可以先加到答案，然后建立相反数作权值的点）。

一个朴素的动态规划是 $f_{i,j}$ 表示第一道菜做了 $i$ 步，第二道菜做了 $j$ 步的最大满意度。

把 $i$ 从 $1$ 到 $n$ 进行转移，维护每个 $j$ 的上的状态的值。这时若从 $(i-1,j)$ 转移到 $(i,j)$，就增加了第 $i$ 列下 $j$ 格中点的权值和；若从 $(i,j-1)$ 转移到 $(i,j)$，状态值则不会发生改变。

于是问题转化为维护一个数列，要支持后缀加一个数或后缀取 $\max$。

考虑对这个数列做差分，所有非 $0$ 的差分项放入一个 `map` 中，每次加一个数 $x$ 之后立即后缀取 $\max$。

原序列后缀取 $\max$ 就等价于在差分数组上找到负值变为 $0$ 后向后调整。在这里需要每次拉出一个数 $y$ 来与 $x$ 相加，并把 $y$ 变为 $0$。

时间复杂度 $\Theta((n+m)\log\min(n,m))$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
long long a[1000001],b[1000001];
long long s[1000001],t[1000001];
int p[1000001],q[1000001];
vector<pair<int,long long> > vec[1000001];
map<int,long long> diff;

inline bool cmp(pair<int,long long> x,pair<int,long long> y){
    return x.second>y.second;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld%d",a+i,s+i,p+i),a[i]+=a[i-1];
    for(int i=1;i<=m;i++)
        scanf("%lld%lld%d",b+i,t+i,q+i),b[i]+=b[i-1];
    long long answer=0;
    for(int i=1;i<=n;i++){
        if(s[i]<a[i])continue;
        int pos=upper_bound(b+1,b+1+m,s[i]-a[i])-b,v=p[i];
        answer+=v; if(1<=pos&&pos<=m)vec[i].push_back({pos,-v});
    }
    for(int i=1;i<=m;i++){
        if(t[i]<b[i])continue;
        int pos=upper_bound(a+1,a+1+n,t[i]-b[i])-a,v=q[i];
        if(1<=pos&&pos<=n)vec[pos].push_back({i,v});
        else answer+=v;
    }
    diff[m+1]=1ll<<62;
    for(int i=1;i<=n;i++){
        sort(vec[i].begin(),vec[i].end(),cmp);
        for(pair<int,long long> j :vec[i]){
            auto it=diff.lower_bound(j.first);
            int x=j.first; long long v=j.second;
            while(v<0&&it!=diff.end()){
                x=(*it).first,v+=(*it).second;
                it=diff.erase(it);
            }
            diff[x]=diff[x]+v;
        }
    }
    for(pair<int,long long> v :diff)
        if(1<=v.first&&v.first<=m)answer+=v.second;
    printf("%lld\n",answer);
    return 0;
}
```

---

## 作者：Cynops (赞：1)

第一次见这种套路的题。

首先注意到步骤 $A_i$ 做完时在菜品 $A$ 上的用时是固定的，所以 $A_i$ 能对答案造成贡献时菜品 $B$ 所进行的步骤 $j$ 是一段前缀 $[1,p_i]$，$B_i$ 同理。

我们考虑将贡献全部放在 $A_i$ 上，首先将答案加上 $\sum ca_i$：

- 对于步骤 $A_i$，若在它 done 时 $B$ 进行到的步骤 $j$ 大于 $p_i$，则贡献 $-ca_i$。
- 对于步骤 $B_i$，若在 $A_{q_i+1}$ done 时 $B$ 进行到的步骤大于等于 $i$，则贡献 $cb_i$。

我们设 $f_{i,j}$ 表示 $A$ 做到了第 $i$ 步，$B$ 做到了第 $j$ 步的最大收益。

考虑 $f_i \to f_{i+1}$ 的过程，其形如后缀加和前缀取 $\max$。我们考虑用一个 `std::map` 维护其差分数组，每次后缀加的时候暴力将差分数组小于 $0$ 的部分丢弃即可，时间复杂度 $\mathcal O(n \log n)$。

---

## 作者：Purslane (赞：0)

# Solution

昨天才了解到这种东西有一个名字叫做整体 DP。。。

显然所有奖励都可以变为：如果完成第一种菜的第 $u_i$ 步之后，另一种菜完成至少 $v_i$ 步，就可以获得一定的奖励 $w_i$。

这样设 $dp_{i,j}$ 为，第一种菜完成了 $i$ 步且第二种菜完成了 $j$ 步能获得的最大奖励。

考虑维护 $dp_{i,*}$，即 $i$ 在变化用数据结构维护 $j$。发现只有：

1. 后缀加；
2. 取前缀 $\rm max$。

那么直接维护差分数组。记录所有修改差分值的位置。取前缀 $\max$ 的时候，按顺序检查这些位置的差分值是否为负数。如果为负数，就不断往后推平，直到负数不存在。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,m,t[MAXN][2],e[MAXN][2],c[MAXN][2],pre[2][MAXN];
vector<pair<int,int>> add[MAXN];
struct INFO {int id;mutable int v;};
bool operator <(INFO A,INFO B) {return A.id<B.id;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) {
		cin>>t[i][0]>>e[i][0]>>c[i][0];
		pre[0][i]=pre[0][i-1]+t[i][0];	
	}
	ffor(i,1,m) {
		cin>>t[i][1]>>e[i][1]>>c[i][1];
		pre[1][i]=pre[1][i-1]+t[i][1];	
	}
	int ans=0;
	ffor(i,1,n) if(e[i][0]>=pre[0][i]) {
		int id=upper_bound(pre[1]+1,pre[1]+m+1,e[i][0]-pre[0][i])-pre[1];
		if(id<=m) add[i].push_back({id,-c[i][0]});
		ans+=c[i][0];
	}
	ffor(i,1,m) if(e[i][1]>=pre[1][i]) {
		int id=upper_bound(pre[0]+1,pre[0]+n+1,e[i][1]-pre[1][i])-pre[0];
		if(id<=n) add[id].push_back({i,c[i][1]});
		else ans+=c[i][1];
	}
	set<INFO> st;
	ffor(i,1,n) {
		set<int> cg;
		for(auto pr:add[i]) {
			int id=pr.first,dt=pr.second;
			auto it=st.lower_bound({id,0});
			if(it!=st.end()&&it->id==id) it->v+=dt;
			else st.insert({id,dt});
			cg.insert(id);
		}
		for(auto id:cg) {
			auto it=st.lower_bound({id,0});
			if(it!=st.end()&&it->id==id&&it->v<0) {
				int tmp=it->v;
				st.erase(it);
				while(1) {
					auto it=st.lower_bound({id,0});
					if(it!=st.end()) {
						tmp+=it->v;
						if(tmp>=0) {it->v=tmp;break ;}
						st.erase(it);	
					}
					else break ;
				}
			}
		}
	}
	for(auto pr:st) ans+=pr.v;
	cout<<ans;
	return 0;
}
```

---

## 作者：一只绝帆 (赞：0)

显然有暴力 $\rm dp$：$f_{i,j}$ 表示第一个序列进度是 $i$，第二个序列进度是 $j$，显然我们知道这个状态的时刻是 $suma_i+sumb_j$。

二维 $\rm dp$ 考虑扫描线一维变成整体 $\rm dp$，每次 $f_{i-1}\to f_i$ 的时候我们会进行前缀加，并把若干个 $j-1\to j$ 的转移系数 $v_j$ 变成 $0$，然后从左往右进行转移。

考虑动态维护 $d_j=f_j-f_{j-1}-v_j$，显然 $d_j\ge 0$，否则就会触发 $v_j$ 的转移。

考虑仅仅变化一个 $v_j$ 造成的影响：

- 若 $v_j\ge 0$，那么将其置为 $0$ 后 $d_j$ 会变大，并且由于转移变得更不优了，不会触发转移。 

- 若 $v_j<0$，那么置为 $0$ 后 $d_j$ 会变小，转移变得更优了会立刻触发转移，造成的效果是操作前从 $j$ 往后找一个最短的前缀使得 $\sum_{k\in[l,r]}d_k\ge |v_j|$，然后将 $[l,r-1]$ 的 $d$ 清空，将 $r$ 的 $d$ 减去 $|v_j|-\sum_{k\in[l,r)}d_k$，手模可以理解这个结论。

同样的，考虑仅仅进行前缀加（对前缀 $j$ 加 $x$）造成的影响：

- 若加了正数，则前缀 $j$ 内部没有任何新的转移，这个过程后若 $d_{j+1}<0$，则我们需要仿照上一部分进行 $v$ 的转移。

- 若加了负数，我们把前缀加变成对差分数组的改变，也就是全局减和后缀加，此时一个关键的问题是：所谓的全局减，要不要仿照上一个后缀减那样，对差分数组处理？
  - 答案当然是不！从事实意义来考虑，我们对差分数组的处理是进行了 $v_j$ 的转移，而事实上我们对全局（或者说前缀）进行减，并不会导致前缀内部或外部产生相邻之间的转移。
    
  - 从抽象的角度来说，我们一定要在这个全局减和上面的后缀减之间找到一个不同点，那就是全局减改变的是 $d_0$，$f_{-1}$ 作为没有意义的值应当是 $-\infty$，所以 $d_0=+\infty$，在此约束下我们进行上文的过程就是正确的。 

现在的问题是，我们即将同时变化多个 $v_j$，有正有负，还要进行一个前缀加，在 $\rm dp$ 中这些“事件”的时刻都是同时发生的，那么我们自然要问：是多次做上面这个过程吗？按照什么顺序做？

事实上每个操作只会影响后缀，且与前缀无关，所以要想它们同时执行，从后往前做即可。

[code](https://atcoder.jp/contests/joisc2019/submissions/62920661)。

---

## 作者：居然有个高手 (赞：0)

提供一种不维护差分数组的做法。

如题，我们可以列出一个朴素的 DP：$dp_{i,j}$ 表示 A 做到第 $i$ 步，B 做到第 $j$ 步时的最大价值。我们定义 $pa_i$ 为最大的 $j$ 满足 $suma_i+sumb_j \le ea_i$，$pb_j$ 为最大的 $i$ 满足 $suma_i+sumb_j \le eb_j$，$pa,pb$ 数组显然可以二分求出。显然转移为 $dp_{i,j} = \max(dp_{i-1,j} + [j\le pa_i]ca_i,dp_{i,j-1} + [i \le pb_j]cb_j)$，时空复杂度均为 $O(nm)$。

将 $dp_{i,j}$ 放在二维平面上考虑，发现每个 $ca_i$ 的贡献为 $[i,i] \times [0,pa_i]$ 的矩阵，每个 $cb_i$ 的贡献为 $[0,pb_i] \times [i,i]$ 的矩阵，每次我们可以向右或向上走一格。

将每个形如 $[a,b] \times [c,d]$，权值为 $x$ 的矩阵差分为点 $(a-1,d+1)$，权值为 $-x$，与点 $(b,c)$，权值为 $x$。维护走过的折线，统计折线下的点对该折线做出的贡献。考虑扫描 $i$ 这一维，用线段树维护 $j$ 这一维。运用整体DP优化，每次往右走时可以直接用线段树做区间加，往上走则一定会走到某个点，可以在处理区间加时取前缀 $\max$ 处理。于是我们可以用 $O(n\log m +m\log n)$ 的时间复杂度解决本题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
inline long long read(){
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
int n,m,ca[N],cb[N];
long long ea[N],eb[N],ta[N],tb[N];
struct tree{
	int l,r;
	long long tag,maxn;
}t[N<<2];
#define mid (t[p].l+t[p].r>>1)
inline void up(int p){
	t[p].maxn=max(t[p<<1].maxn,t[p<<1|1].maxn);
}
inline void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;
	if(l==r)return ;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}
inline void cg(int p,long long v){
	t[p].maxn+=v,t[p].tag+=v;
}
inline void spread(int p){
	if(t[p].tag){
		cg(p<<1,t[p].tag),cg(p<<1|1,t[p].tag);
		t[p].tag=0;
	}
}
inline void change(int p,int l,int r,long long v){
	if(l<=t[p].l&&t[p].r<=r){
		cg(p,v);
		return ;
	}
	spread(p);
	if(l<=mid)change(p<<1,l,r,v);
	if(r>mid)change(p<<1|1,l,r,v);
	up(p);
}
inline void insert(int p,int pos,long long v){
	if(t[p].l==t[p].r){
		t[p].maxn=max(t[p].maxn,v);
		return ;
	}
	spread(p);
	if(pos<=mid)insert(p<<1,pos,v);
	else insert(p<<1|1,pos,v);
	up(p);
}
inline long long query(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r)return t[p].maxn;
	long long ans = -1e18;
	spread(p);
	if(l<=mid)ans=query(p<<1,l,r);
	if(r>mid)ans=max(ans,query(p<<1|1,l,r));
	return ans;
}
#undef mid
vector<pair<int,int>>v[N];
int main(){
	n=read(),m=read();
	for(int i = 1;i<=n;i++)ta[i]=read()+ta[i-1],ea[i]=read(),ca[i]=read();
	for(int i = 1;i<=m;i++)tb[i]=read()+tb[i-1],eb[i]=read(),cb[i]=read();
	build(1,0,m);
	long long g=0;
	for(int i = 1,l,r,mid;i<=n;i++){
		l=0,r=m;
		while(l<=r){
			mid=l+r>>1;
			if(ta[i] + tb[mid] <= ea[i])l=mid+1;
			else r=mid-1;
		}
		l--;
		if(l!=-1){
			
			if(l+1<=m){
				v[i].push_back({0,ca[i]});
				v[i-1].push_back({l+1,-ca[i]});
			}
			else g+=ca[i];
		}
	}
	for(int i = 1,l,r,mid;i<=m;i++){
		l=0,r=n;
		while(l<=r){
			mid=l+r>>1;
			if(ta[mid]+tb[i]<=eb[i])l=mid+1;
			else r=mid-1;
		}
		l--;
		if(l!=-1){
			v[l].push_back({i,cb[i]});
		}
	}
	for(int i = 0;i<=n;i++){
		sort(v[i].begin(),v[i].end(),greater<pair<int,int>>());
		insert(1,m,t[1].maxn);
		for(auto [p,c]:v[i]){
			insert(1,p,query(1,0,p));
			change(1,p,m,c);
		}
	}
	cout<<query(1,m,m)+g;
	return 0;
}

```

---

