# [JOI Open 2021] 决算报告 / Financial Report

## 题目背景

**警告：滥用本题评测将被封号。**

## 题目描述

有一个长度为 $N$ 的序列 $A_i$，定义函数 $f(m,p_1,p_2,\cdots,p_m)$ 的值为满足：

$$\max\limits_{j=1}^{i-1}\{A_{p_j}\} < A_{p_i}$$

的 $p_i$ 的个数，当 $i=1$ 时，我们假设上面这个不等式是恒成立的。

给定一个整数 $D$，求一个序列 $p_i$ 满足：

- $1 \le m \le N$；
- $p_m=N$；
- $p_i<p_{i+1}$；
- 如果 $m \ge 2$，那么有 $p_{j+1}-p_j \le D$；
- $f(m,p_1,p_2,\dots,p_m)$ 的值最大。

求 $f$ 函数的最大值。

## 说明/提示

#### 样例 1 解释

一共有 $7$ 种可能的情况：

- $p_i=\{1,2,3,4,5,6,7\}$，$f(7,1,2,3,4,5,6,7)=2$；
- $p_i=\{2,3,4,5,6,7\}$，$f(6,2,3,4,5,6,7)=1$；
- $p_i=\{3,4,5,6,7\}$，$f(5,3,4,5,6,7)=1$；
- $p_i=\{4,5,6,7\}$，$f(4,4,5,6,7)=3$；
- $p_i=\{5,6,7\}$，$f(3,5,6,7)=2$；
- $p_i=\{6,7\}$，$f(2,6,7)=1$；
- $p_i=\{7\}$，$f(1,7)=1$。

最大值为 $3$。

#### 样例 2 解释

最优的 $p_i=\{1,3,4,5,6\}$，对应的 $A_i=\{100,200,400,600,300\}$，$f$ 函数值为 $4$。

#### 样例 3 解释

最优的方式有多种，其中一种是 $p_i=\{1,3,5,6,8,9,11\}$，对应的 $A_i=\{ 1, 4, 2, 4, 5, 7, 3\}$，$f$ 函数值为 $4$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（14 pts）：$N \le 20$；
- Subtask 2（14 pts）：$N \le 400$；
- Subtask 3（20 pts）：$N \le 7000$；
- Subtask 4（12 pts）：$D=1$；
- Subtask 5（5 pts）：$D=N$；
- Subtask 6（35 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $1 \le N \le 3 \times 10^5$；
- $1 \le D \le N$；
- $0 \le A_i \le 10^9$。

#### 说明

翻译自 [JOI 2020 / 2021 Open Contest B Financial Report](http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2021/financial/2021-open-financial-statement-en.pdf)。

## 样例 #1

### 输入

```
7 1
100 600 600 200 300 500 500```

### 输出

```
3```

## 样例 #2

### 输入

```
6 6
100 500 200 400 600 300```

### 输出

```
4```

## 样例 #3

### 输入

```
11 2
1 4 4 2 2 4 9 5 7 0 3```

### 输出

```
4```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：7)

首先，题目描述过于抽象，本质是求 $A$ 的一个子序列，使得这个子序列包含 $A_n$，并且子序列中相邻的元素位置距离 $\le D$，并且从前往后破纪录元素尽量多，求破纪录元素个数。

只有 $A$ 相对顺序有用，所以先将 $A$ 离散化。

考虑 dp，其中 $dp[i]$ 为 $i$ 为破纪录元素时能包含几个破纪录元素。$i$ 肯定为破纪录元素，所以我们需要枚举在 $i$ 前面的第一个破纪录元素 $j$。则 $A_j<A_i$。而为了保证存在一个子序列包含 $i$ 和 $j$，还满足相邻元素距离 $\le D$，必须存在 $j<p_1<p_2<\dots<p_x<i$ 使得 

 - $p_1-j,p_2-p_1,p_3-p_2,\dots,p_x-p_{x-1},i-p_x\le D$
 - $A_{p_1},A_{p_2},\dots,A_{p_k}<A_i$（来保证 $A_i$ 是破纪录元素，注意不需要保证这些小于 $A_j$，因为这样肯定不优）

则可以取所有满足条件的 $j$ 并且求 $dp[i]=\max(dp[j])+1$。直接 dp 可以做到 $O(n^2)$。而发现由于 $i:1\to n$ 时 $A_i$ 的大量变化，维护相邻元素距离约束相对困难，于是考虑对 $A_i$ 扫描线。

按照 $A_i$ 从小到大更新 $dp[i]$，则计算某个 $dp[i]$ 的时候肯定只有已经被更新的 $dp[j]$ 能影响 $dp[i]$。

我们维护一个 set 包含所有已经被更新的位置：这些位置上的值均小于 $A_i$。维护一个并查集，其中 $i$ 和 $j$ 连通当且仅当 $i$ 和 $j$ 被更新并且 $j-i\le D$，则可以从并查集的连通块信息得出任何 $i$ 的最左端 $j$ 使得相邻元素距离约束成立。

然后用并查集得到 $j$ 之后用线段树维护 $dp$ 区间最大值，总共时间复杂度 $O(n\log n)$：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll = long long;
using pii = pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int las[300005];

int ufs(int u) {
  if (las[u] == -1)
    return u;
  return las[u] = ufs(las[u]);
}
void conn(int u, int v) {
  u = ufs(u), v = ufs(v);
  if (u != v)
    las[max(u, v)] = min(u, v);
}

int seg[300005 << 2];
void upd(int idx, int l, int r, int u, int v) {
  if (!(l <= u && u < r))
    return;
  if (r - l == 1) {
    seg[idx] = v;
    return;
  }
  upd(idx * 2, l, (l + r) / 2, u, v);
  upd(idx * 2 + 1, (l + r) / 2, r, u, v);
  seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
}
int qry(int idx, int l, int r, int L, int R) {
  if (L <= l && r <= R)
    return seg[idx];
  if (R <= l || r <= L)
    return 0;
  return max(qry(idx * 2, l, (l + r) / 2, L, R),
             qry(idx * 2 + 1, (l + r) / 2, r, L, R));
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  memset(las, -1, sizeof las);
  int n, d;
  cin >> n >> d;
  vector<pii> x(n);
  for (int i = 0; i < n; i++)
    cin >> x[i].fi, x[i].se = -i;
  sort(all(x));
  set<int> on;
  int ans = 0;
  for (auto [_, i] : x) {
    i = -i;
    auto pos = on.insert(i).fi;
    if (pos != on.begin() && *pos - *prev(pos) <= d)
      conn(*pos, *prev(pos));
    if (next(pos) != on.end() && *next(pos) - *pos <= d)
      conn(*pos, *next(pos));
    int dp = qry(1, 0, n, ufs(i), i) + 1;
    ans = max(ans, dp);
    upd(1, 0, n, i, dp);
  }
  cout << ans << endl;
}
```

---

## 作者：_Life_ (赞：6)

思路来自 @[Chinese\_zjc\_](https://www.luogu.com.cn/user/118239) ![](//图.tk/3)

### 题意
有一个长度为 $n$ 的序列 $a_1,a_2,a_3,\cdots,a_n$

选出一个子序列 $a_{p_1},a_{p_2},a_{p_3},\cdots,a_{p_m}$，要求满足如下限制：

- $p_m=n$
- $p_i<p_{i+1}$
- $m=1 \operatorname{or} p_{i+1}-p_i\leq d$

定义一个序列的价值为满足 $\max_{i=1}^{j-1}a_i<a_j$ 的下标 $j$ 个数 

求所有子序列中最大的价值

### 题解

设以 $a_i$ 结尾的序列，最大的 $m$ 为 $dp_i$

因为要求 $a_{p_i}<a_{p_{i+1}}$，所以 $dp_i$ 会按照 $a_i$ 从小到大的顺序转移

因为要求 $p_i<p_{i+1}$ ，所以 $a_i$ 相等时，从前往后转移

于是我们就可以愉快的 `stable_sort()` 一发 **不要打成 `sort()`** ~~挂了好几发 惨案QAQ~~

假设当前正在转移第 $i$ 个，通过不断跳最多 $d$ 个的方式，从 $i$ 向前跳最远可以跳到第 $j$ 个

则 $dp_i=\max_{k=j-d}^{i-1}dp_k+1$

求向前跳最远可以用并查集维护，求 `max` 用线段树维护即可

### 代码
```cpp
#include<bits/stdc++.h>
#define ls (pos<<1)
#define rs (pos<<1|1)
#define mid ((l+r)>>1)
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+(c^'0');
		c=getchar();
	}
	return x*f;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int n,d,a[300005],rk[300005],fa[300005];
int seg[300005<<2];
void update(int loc,int val,int pos=1,int l=1,int r=n)
{
	if(l==r)return void(seg[pos]=val);
	if(loc<=mid)update(loc,val,ls,l,mid);
	else update(loc,val,rs,mid+1,r);
	seg[pos]=max(seg[ls],seg[rs]);
}
int query(int lx,int rx,int pos=1,int l=1,int r=n)
{
	if(rx<l||lx>r)return 0;
	if(lx<=l&&r<=rx)return seg[pos];
	int ans=INT_MIN;
	if(lx<=mid)ans=max(ans,query(lx,rx,ls,l,mid));
	if(rx>mid)ans=max(ans,query(lx,rx,rs,mid+1,r));
	return ans;
}
int find(int lx,int rx,int pos=1,int l=1,int r=n)
{
	if(rx<l||lx>r||!seg[pos])return 0;
	if(l==r)return l;
	return find(lx,rx,ls,l,mid)?:find(lx,rx,rs,mid+1,r);
}
int find(int x)
{
	if(fa[x]==x)
	{
		int res=find(x-d,x-1);
		if(res)fa[x]=find(res);
		return fa[x];
	}
	return fa[x]=find(fa[x]);
}
int main()
{
	n=read(),d=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)rk[i]=n+1-i;
	stable_sort(rk+1,rk+1+n,[](int x,int y){return a[x]<a[y];});
	for(int i=1;i<=n;i++)update(rk[i],query(find(rk[i])-d,rk[i]-1)+1);
	write(query(1,n));
}
```

---

## 作者：Binah_cyc (赞：5)

别的大佬已经把正解讲得很详细了，我来讲讲部分分的做法吧。本题的部分分很足，建议都写一写。

## Subtask 1

较为简单的子集枚举，只需要枚举一下所有的情况即可。 

时间复杂度：$ \operatorname{O}(2^n)$。 

代码：不想写了。 

## Subtask 2

考虑动态规划。$dp_{i,j}$ 表示考虑到前 $i$ 个数，已经有 $j$ 个数破纪录时最后一个数的值，初始化时所有值都初始化为 $\operatorname{INF}$，$dp_{i,1}$ 初始化为 $a_i$。

考虑转移，一个位置接到第 $k$ 个数的后面，当 $dp_{k,j-1} < dp_{i,j}$ 时会造成 $1$ 的贡献。同时，一个数也可以不造成贡献，即 $dp_{k,j} \ne \operatorname{INF}$ 时直接接到后面而不造成贡献。 

代码如下。
```cpp
	memset(dp,0x7f,sizeof(dp));
	for(int i=1; i<=n; i++) dp[i][1]=a[i];
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=i; j++)
		{
			for(int k=1; k<=d&&i-k; k++)
			{
				if(dp[i-k][j-1]<dp[i][j]&&dp[i][j]!=maxn) dp[i][j]=min(dp[i][j],max(dp[i-k][j-1],a[i]));
				else if(dp[i][j]==maxn&&dp[i-k][j-1]<a[i]) dp[i][j]=max(dp[i-k][j-1],a[i]);
			}
			for(int k=1; k<=d&&i-k; k++) if(dp[i-k][j]!=maxn) dp[i][j]=min(dp[i][j],max(dp[i-k][j],a[i]));
		}
	}
```

## Subtask 3

这个数据点是提示正解的，设 $f_i$ 表示以 $i$ 结尾的破纪录的数字的个数。初始时所有状态为 $1$。

考虑转移，我们从 $i$ 处倒序枚举 $j$，若 $j$ 满足 $a_j < a_i$ 那么就可以把该处接到 $i$ 后面，接法我们待会再说。

在枚举 $j$ 的时候，我们引入一个 $last$ 表示上一个满足 $a_j \le a_i$ 的 $a$ 的位置，在枚举 $j$ 的时候，如果 $j$ 和 $last$ 的距离大于了 $d$，就直接结束枚举。 

接的时候不是指直接将 $j$ 接到 $i$ 后面，而是将 $j$ 接到 $last$ 上，将 $last$ 接到上一个 $last$ 上，以此类推直到 $i$ 后面。这样，因为 $a_j < a_i$，所以至少会造成 $1$ 的贡献。
```cpp
	for(int i=1; i<=n; i++) f[i]=1;
	for(int i=1; i<=n; i++)
	{
		for(int j=i-1,lst=i; j; j--)
		{
			if(lst-j>d) break;
			if(a[i]>a[j]) f[i]=max(f[i],f[j]+1);
			if(a[i]>=a[j]) lst=j;
		}
	}
```

## Subtask 4

$d$ 为 $1$，所以只能选择相邻的，用单调栈维护一下就行了。

```cpp
	for(int i=n; i; i--)
	{
		while(s.size()&&s.top()<=a[i]) s.pop();
		s.push(a[i]);
		ans=max(ans,(int)s.size());
	}
```
## Subtask 5

$d$ 为 $n$，选择没有限制，答案就是最长上升子序列的长度。

```cpp
	memset(f,0x7f,sizeof(f));
	f[0]=-maxn;
	for(int i=1; i<=n; i++) *lower_bound(f+1,f+n+1,a[i])=a[i];
	cout<<lower_bound(f+1,f+n+1+1,maxn)-f-1;
```

## Subtask 6
最后一档，考虑优化 Subtask 3 的思路，使用线段树和并查集维护一下就行了，别的题解已经讲的十分详细了，这里就不过多赘述了。

最后感谢 @[zengziqvan](https://www.luogu.com.cn/user/935908) 在编写时提供的帮助。

---

## 作者：_lmh_ (赞：1)

首先离散化使得 $a_i$ 构成一个 $[1,n]$ 的排列（如果原始的 $a_i$ 相同，则认为前面的比后面的大）。

一个比较直接的思路是设 $dp_{i,j}$ 代表上一个数选了 $i$，当前最大值为 $j$，但是这个状态数直接爆了。

现在考虑一个子序列的形态，一定是“前缀最大值”——“一些比较小的数”——“下一个前缀最大值”的形态，考虑把状态记在前缀最大值上面，令 $dp_i$ 代表以前缀最大值 $i$ 结尾的子序列 $f$ 最大值。

现在考虑在两个最大值中间选一些数，使得相邻两数之间的距离 $\le D$。不难发现只有在存在连续 $D$ 个更大的数时无解。

从大到小对每个 $a_i$ 找往后第一个足够大的连通块，这个直接用 `set` 维护所有长度 $\ge D$ 的区间即可。这个连通块往前都是 $f_i$ 的转移范围。

之后就相当于去掉了 $\le D$ 的限制，用线段树维护转移即可。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define lson (u<<1)
#define rson (u<<1|1)
const ll N=300007;
ll n,k,ans,a[N],b[N],id[N],f[N],ok[N],L[N],R[N],val[N<<2];
vector<ll> del[N];
set<ll> s;
void add(ll x){
	ok[x]=1;
	int l=x,r=x;
	if (ok[x-1]) l=L[x-1];
	if (ok[x+1]){
		if (s.find(x+1)!=s.end()) s.erase(x+1);
		r=R[x+1];
	}
	if (r-l+1>=k) s.insert(l);
	R[l]=r;L[r]=l;
}
void modify(int u,int l,int r,int x,ll v){
	if (l==r){val[u]=v;return;}
	int mid=l+r>>1;
	if (x<=mid) modify(lson,l,mid,x,v);
	if (x>mid) modify(rson,mid+1,r,x,v);
	val[u]=max(val[lson],val[rson]);
}
ll query(int u,int l,int r,ll R){
	if (r<=R) return val[u];
	int mid=l+r>>1;
	if (R<=mid) return query(lson,l,mid,R);
	return max(query(lson,l,mid,R),query(rson,mid+1,r,R));
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;++i){cin>>a[i];b[i]=a[i];}
	sort(b+1,b+1+n);
	for (int i=n;i;--i){
		a[i]=lower_bound(b+1,b+1+n,a[i])-b;
		--b[a[i]];id[a[i]]=i;
	}
	for (int i=n;i;--i){
		auto it=s.lower_bound(id[i]);
		if (it!=s.end()) del[(*it)+k].emplace_back(id[i]);
		add(id[i]);
	}
	for (int i=1;i<=n;++i){
		for (auto x:del[i]) modify(1,1,n,a[x],0);
		f[i]=query(1,1,n,a[i])+1;
		modify(1,1,n,a[i],f[i]);
		ans=max(ans,f[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：JYX0924 (赞：0)

一道非常好的数据结构优化 dp 的题。

考虑 $dp_{i}$ 表示结尾的值是 $i$，$f$ 的值最大是多少。

考虑从小到大枚举 $i$，那么我们用并查集和 $set$ 维护点 $j$ 向左最远到哪里，$x$ 和 $y$ 联通当且仅当 $x-y\le D(x>y)$。

然后用线段树维护区间最大值即可。

下面是 AC 代码。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define maxn 300005 
#define mid ((l+r)>>1) 
#define ls (now<<1) 
#define rs (now<<1|1) 
using namespace std;
ll n,D,a[maxn],dp[maxn],sum[maxn<<2],pos[maxn],f[maxn];
vector<ll> edge[maxn];
set<ll> s;
void push_up(ll now) {sum[now]=max(sum[ls],sum[rs]);}
void modify(ll now,ll l,ll r,ll pos,ll v)
{
	if(l==r) {sum[now]=v; return;}
	if(mid>=pos) modify(ls,l,mid,pos,v);
	else modify(rs,mid+1,r,pos,v);
	push_up(now);
}
ll query(ll now,ll l,ll r,ll L,ll R)
{
	if(l>=L&&r<=R) return sum[now];
	ll ret=0;
	if(mid>=L) ret=max(ret,query(ls,l,mid,L,R));
	if(R>=mid+1) ret=max(ret,query(rs,mid+1,r,L,R));
	return ret;
}
void init()
{
	vector<ll> q; for(int i=1;i<=n;i++) q.push_back(a[i]);
	sort(q.begin(),q.end()); q.erase(unique(q.begin(),q.end()),q.end());
	for(int i=1;i<=n;i++) a[i]=lower_bound(q.begin(),q.end(),a[i])-q.begin()+1;
	for(int i=n;i>=1;i--) edge[a[i]].push_back(i);
	ll tot=0;
	for(int i=1;i<=q.size();i++) for(auto to:edge[i]) a[to]=++tot,pos[tot]=to;
}
ll find(ll now) {if(f[now]==now) return now; return f[now]=find(f[now]);}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>D; for(int i=1;i<=n;i++) cin>>a[i],f[i]=i;
	init(); ll ans=0;
	for(int i=1;i<=n;i++)
	{
		auto it=s.lower_bound(pos[i]);ll L=max(1LL,pos[i]-D);
		if(it!=s.end()&&*it-D<=pos[i]) f[*it]=pos[i];
		if(it!=s.begin())
		{
			it--; ll now=*it;
			if(pos[i]-now<=D) f[pos[i]]=find(now),L=min(L,find(now));
		}
		dp[i]=query(1,1,n,L,pos[i])+1;
		modify(1,1,n,pos[i],dp[i]);
		ans=max(ans,dp[i]); s.insert(pos[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Skicyer (赞：0)

# [传送门](https://www.luogu.com.cn/problem/P7804)

给出一个很傻的**线段树**做法。

## 简要题意
从一个长为 $n$ 的序列。要求选出一个子序列 $p$，使得其中每个数在原序列中位置相差小于等于 $d$ 且使下面式子的值最大。
$$\sum_{i-1}^n[\max\limits_{j=1}^{i-1}\{P_j\} < P_i]$$

## 暴力
显然，可以使用动态规划。

将每一个最大值的更新点作为关键点 $key$。然后向前遍历，如果遇见一个小于当前值的点，我们往前遍历的限制 $lim$ 就可以重置。

### 关键代码
```cpp
for(int i=1; i<=n; i++) {
	key[i]=1;
	for(int j=i-1; j>=max(i-D,1ll); j--) {
		if(a[i]>a[j])key[i]=max(key[i],key[j]+1);
	}
	int k=i-1,lim=D-1;
	while(k) {
		if(a[k]<a[i]) {
			lim=D-1;
			key[i]=max(key[i],key[k]+1);
		} else lim--;
		if(lim<0) break;
		k--;
	}
	ans=max(ans,key[i]);
}
```

## 优化
想到在前面找到最靠近 $i$ 位置的且连续 $d$ 个数比 $a_i$ 大的点。反复考虑发现不是很会。贡献了很多~~罚时~~。

## 开个新坑
既然找到大于 $a_i$ 很难，但是如果黑白染色后就很好做。

就是小于 $a_i$ 的染红，其余染黑。因为在 $i$ 前面的与 $a_i$ 相等的数会使 $a_i$ 不产生贡献，所以染黑。

接着，为了更方便的染色，我们将 $a_i$ 离散，再从小到大遍历。然后查找就交给我们亲爱的线段树。

给一个关键代码，合并节点。
```cpp
struct node {
	int len,pla;
	node() {}
	node(int _l,int _p) {
		len=_l,pla=_p;
	}
	void init() {
		len=pla=0;
	}
};
//node 为连续的黑段。
node ADD(node a,node b) {
	return node(a.len+b.len,b.pla);
  //把两个片段拼起来。
}
struct TRE {
	node l,r,m;
  //l 为左边连续，r 为右边连续，m 为中间最靠右的len>D的段。(没有就随便了！！)
	int sz;
	void init() {
		l.init(),r.init(),m.init();
		sz=0;
	}
} t[maxn<<2];;
TRE pushup(TRE a,TRE b) {
	TRE res;
	res.init();
	res.sz=a.sz+b.sz;
	if(a.l.len==a.sz&&b.l.len) res.l=ADD(a.l,b.l);
	else res.l=a.l;
	if(b.r.len==b.sz&&a.r.len) res.r=ADD(a.r,b.r);
	else res.r=b.r;
	if(b.m.len>=D) {
		res.m=b.m;
	} else {
		if(a.r.pla&&b.l.pla)res.m=ADD(a.r,b.l);
		if(res.m.len<D&&a.m.len>res.m.len&&a.m.pla) res.m=a.m;
		if(res.m.len<D&&b.m.len>res.m.len&&b.m.pla) res.m=b.m;
	}
	return res;
}
```
然后用线段树对 $key$ 做一个区间最大值，就和暴力一样统计答案就好了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ls rt*2
#define rs rt*2+1
#define mid (l+r)/2
const int maxn=3e5+5;
int a[maxn],b[maxn],n,pla[maxn],D,ans;
struct node{
	int len,pla;
	node(){}
	node(int _l,int _p) {
		len=_l,pla=_p;
	}
	void init(){
		len=pla=0;
	}
};
node ADD(node a,node b){
	return node(a.len+b.len,b.pla);
}
struct TRE{
	node l,r,m;
	int sz;
	void init(){
		l.init(),r.init(),m.init();
		sz=0;
	}
}t[maxn<<2];;
TRE pushup(TRE a,TRE b){
	TRE res;
	res.init();
	res.sz=a.sz+b.sz;
	if(a.l.len==a.sz&&b.l.len) res.l=ADD(a.l,b.l);
	else res.l=a.l;
	if(b.r.len==b.sz&&a.r.len) res.r=ADD(a.r,b.r);
	else res.r=b.r;
	if(b.m.len>=D) {
		res.m=b.m;
	}
	else {
		if(a.r.pla&&b.l.pla)res.m=ADD(a.r,b.l);
		if(res.m.len<D&&a.m.len>res.m.len&&a.m.pla) res.m=a.m;
		if(res.m.len<D&&b.m.len>res.m.len&&b.m.pla) res.m=b.m;
	}
	return res;
}
void build(int rt,int l,int r){
	t[rt].sz=r-l+1;
	if(l==r){
		t[rt].l=t[rt].r=t[rt].m=node(1,l);
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	t[rt]=pushup(t[ls],t[rs]);
}
void modify(int rt,int l,int r,int x){
	if(l==r) {
		t[rt].l=t[rt].r=t[rt].m=node(0,0);
		return ;	
	}
	if(x<=mid) modify(ls,l,mid,x);
	else modify(rs,mid+1,r,x);
	t[rt]=pushup(t[ls],t[rs]);
}
TRE find(int rt,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		return t[rt];
	}
	TRE res;
	if(x>mid) return find(rs,mid+1,r,x,y);
	else if(y<=mid) return find(ls,l,mid,x,y);
	else return pushup(find(ls,l,mid,x,y),find(rs,mid+1,r,x,y));
}
int g[maxn<<2];
void ins(int rt,int l,int r,int x,int y){
	if(l==r) {
		g[rt]=y;
		return ;
	}
	if(x<=mid) ins(ls,l,mid,x,y);
	else ins(rs,mid+1,r,x,y);
	g[rt]=max(g[ls],g[rs]);
}
int query(int rt,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		return g[rt];
	}
	int res=0;
	if(x<=mid) res=max(res,query(ls,l,mid,x,y));
	if(y>mid) res=max(res,query(rs,mid+1,r,x,y));
	return res;
}
signed main() {
	scanf("%lld%lld",&n,&D);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=a[i]*n-i;
	}
	sort(b+1,b+n+1);
	int len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+len+1,a[i]*n-i)-b;
		pla[a[i]]=i;
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int res=1;
		if(pla[i]==1) res=1;
		else {
			TRE tmp=find(1,1,n,1,pla[i]-1);
			if(tmp.m.len>=D)res=query(1,1,n,tmp.m.pla+1,pla[i]-1)+1;
			else res=query(1,1,n,1,pla[i]-1)+1;
		}
		modify(1,1,n,pla[i]);
		ans=max(ans,res);
		ins(1,1,n,pla[i],res);
	}
	printf("%lld",ans);
	return 0;
}
```

---

