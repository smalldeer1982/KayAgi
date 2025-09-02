# The Endspeaker (Hard Version)

## 题目描述

这是这道题目的困难版本。与简单版本的区别在于，你还需要输出达到最优解的操作序列数量。你需要解决这两种版本才能进行 hack。

现在给定一个数组 $ a $，长度为 $ n $，以及一个数组 $ b $，长度为 $ m $（保证 $ b_i > b_{i+1} $ 对所有 $ 1 \le i < m $ 成立）。初始时，$ k $ 的值为 $ 1 $。你的目标是通过执行以下两种操作之一反复将数组 $ a $ 变为空：

- 类型 $ 1 $ 操作 — 在 $ k < m $ 且数组 $ a $ 不为空时，你可以将 $ k $ 的值加 $ 1 $。这种操作不需要花费任何代价。
- 类型 $ 2 $ 操作 — 你可以移除数组 $ a $ 的一个非空前缀，使得这个前缀的和不大于 $ b_k $。这种操作的代价为 $ m - k $。

你需要让将数组 $ a $ 变为空的总操作代价最小化。如果无法通过任何操作序列达到这一目标，请输出 $ -1 $。否则，输出最小总操作代价以及产生命中该代价的操作序列数量，对 $ 10^9 + 7 $ 取模。

若两个操作序列在任一步骤中选择了不同种类的操作，或移除前缀的大小不同，则它们视为不同。

## 说明/提示

以下为一个测试用例的示例，其中最优操作序列的总费用为 $ 1 $，共有 $ 3 $ 种：

- 所有这 $ 3 $ 种序列都以类型 $ 2 $ 的操作开头，移除前缀 $ [9] $，使得 $ a = [3, 4, 3] $，产生代价 $ 1 $。然后执行类型 $ 1 $ 操作，把 $ k $ 提升一位，此后所有操作均无代价。
- 一种序列依次移除前缀 $ [3, 4] $ 和 $ [3] $。
- 另一种序列依次移除前缀 $ [3] $ 和 $ [4, 3] $。
- 还有一种序列依次移除前缀 $ [3] $，再移除 $ [4] $，最后移除 $ [3] $。

在第二个测试用例中，由于 $ a_1 > b_1 $，无法移除任何前缀，因此无论如何都无法使数组 $ a $ 变为空。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1```

### 输出

```
1 3
-1
2 11
10 42
4 1```

# 题解

## 作者：Super_Cube (赞：10)

# Solution

注意到 $nm\le 3\times 10^5$，考虑设计出一份能与 $nm$ 扯上关系的代码。

贪心想不出来就来想 dp。设 $dp_{i,j}$ 表示 $k$ 的值目前为 $i$，$a$ 中剩下的第一个元素下标为 $j$ 的最小代价。枚举状态就是 $O(nm)$ 的，感觉很有前途。从 $j$ 开始往后找到第一个位置 $c$ 满足 $a$ 中 $i\sim c$ 的和大于 $b_j$，有转移：$dp_{i,c}\gets dp_{i,j}+m-i$，因为每次转移一个极大的连续段肯定更优。还有种情况是直接使 $k$ 往后移，即 $dp_{i+1,j}\gets dp_{i,j}$。初始化 $dp_{1,1}=0$，答案为 $\displaystyle\min_{i=1}^m dp_{i,n+1}$。

这样做答案是对了，但是方案会有缺漏。

问题出在每次可以不用转移极大连续段，只选取其中的一小段前缀进行转移，即对于 $p\in(i,c]$ 都有转移 $dp_{i,p}\gets dp_{i,j}+m-i$。之前不这样做是因为答案不会更优却会提升复杂度，现在为了统计方案确实是有必要的。

区间更新，单点查询，直接上线段树维护转移。

时间复杂度：$O(nm\log n)$。

# Code

极其丑陋。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef std::pair<ll,int> pli;
const ll inf=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
inline void operator+=(pli&x,const pli&y){
	if(x.first!=y.first){
		if(x.first>y.first)x=y;
	}else if((x.second+=y.second)>=mod)
		x.second-=mod;
}
struct segment{
	int l,r;
	pli v;
}t[1200005];
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	t[p].v.first=inf;t[p].v.second=0;
	if(l==r)return l==1?t[p].v.first=0,t[p].v.second=1:0,void();
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
inline void tag_down(int p){
	if(t[p].v.first!=inf)
		t[p<<1].v+=t[p].v,t[p<<1|1].v+=t[p].v,t[p].v.first=0x3f3f3f3f3f3f3f3f,t[p].v.second=0;
}
void upd(int p,int l,int r,const pli&x){
	if(t[p].l>=l&&t[p].r<=r)return t[p].v+=x;
	tag_down(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid)upd(p<<1,l,r,x);
	if(r>mid)upd(p<<1|1,l,r,x);
}
pli ask(int p,int x){
	if(t[p].l==t[p].r)return t[p].v;
	tag_down(p);
	return ask(p<<1|(x>(t[p].l+t[p].r>>1)),x);
}
std::vector<ll>a;
std::vector<int>b;
int T,n,m;
std::pair<ll,int>ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		a.resize(n+1);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]),a[i]+=a[i-1];
		b.resize(m+1);
		for(int i=1;i<=m;++i)
			scanf("%d",&b[i]);
		build(1,1,n);
		ans.first=inf;ans.second=0;
		for(int j=1;j<=m;++j){
			static pli res,val;
			res.first=inf;res.second=0;
			for(int i=1,k;i<=n;++i){
				k=std::upper_bound(a.begin()+i,a.begin()+n+1,b[j]+(i?a[i-1]:0))-a.begin();
				if(i<k){
					val=ask(1,i);val.first+=m-j;
					if(k==n+1)res+=val,--k;
					if(i<k)upd(1,i+1,k,val);
				}
			}
			ans+=res;
		}
		if(ans.first==0x3f3f3f3f3f3f3f3f)puts("-1");
		else printf("%lld %d\n",ans.first,ans.second);
	}
	return 0;
}
```

好笑的是 D2 跑得比 D1 快。

---

## 作者：Louis_lxy (赞：3)

定义 $f(i,j)$ 表示清除前 $i$ 个数，$k=j$ 的答案，$g(i,j)$ 表示得到 $f(i,j)$ 的方案数。

显然有转移方程 $f(i,j)=min(f(i,j-1),f(p,j))$，其中 $p$ 是能删除的最长区间的左端点，然后考虑转移 $g$。

1. $f(i,j-1)<f(p,j)$，$g(i,j)=g(i,j-1)$。
2. $f(i,j-1)>f(p,j)$，$g(i,j)=\sum_{i=p}^{q} g(q,j)$，$q$ 为 $x\in[p,i-1]$，$f(x,j)=f(p,j)$ 的 $x$ 的最大值。
3. $f(i,j-1)=f(p,j)$，$g(i,j)=g(i,j-1)+\sum_{i=p}^{q} g(q,j)$，$q$ 为 $x\in[p,i-1]$，$f(x,j)=f(p,j)$ 的 $x$ 的最大值。

然后容易发现 $f$ 在 $j$ 固定时有单调性，用个二分就可以得到 $q$，于是前缀和优化一下就可以了，复杂度 $O(nm\log n)$，当然也可以把二分改为双指针，复杂度 $O(nm)$。

---

## 作者：灵乌路空 (赞：3)

前置知识：[题解：CF2027D1 The Endspeaker (Hard Version)](https://www.luogu.com.cn/article/4quf89a0)


套用 D1 的状态，发现最优决策计数同样仅需考虑当前使用了哪些操作与删除的前缀长度，于是记 $g_{i, j}$ 表示使用操作 $1\sim i$，恰好删除了前缀 $1\sim j$，代价最小时的方案数，初始化 $g_{0, 0} = 1$。则有显然的转移：

$$\begin{cases}
    g_{i, j}\leftarrow g_{i - 1, j}\\
    g_{i, j}\leftarrow \sum_k g_{i, j - k} &\left( f_{i, j} > f_{i, j - k} + m - i\right)\land \left(b_i \ge \sum_{j-k< l\le j} a_l\right)\\
    g_{i, j}\leftarrow g_{i, j} + \sum_k g_{i, j - k} &\left( f_{i, j} = f_{i, j - k} + m - i\right)\land \left(b_i \ge \sum_{j-k< l\le j} a_l\right)
\end{cases}$$

答案即为 $g_{m, n}$。

同样考虑单调性优化，设最优的对 $f$ 的决策为 $f_{i, j - k}$，由上式可知，产生贡献的 $g_{i, j - k}$ 一定是以 $j-k$ 为左端点的一段区间 $[j-k, j - k']$，该区间内所有状态 $f_{i, j-k}\sim f_{i, j - k'}$ 的值均相等，且当 $j$ 增加时该区间的右端点一定是单调不降的。
 
于是考虑双指针优化 DP 时再维护一个指针表示对 $g$ 产生贡献的区间，使用前缀和优化转移即可。

总时间复杂度仍为 $O(nm)$ 级别。

```cpp
//
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 3e5 + 10;
const LL kInf = 1e18;
const LL p = 1e9 + 7;
//=============================================================
int n, m, a[kN], b[kN];
LL sum[kN], f[2][kN], g[2][kN], pre[kN];
//=============================================================
//=============================================================
int main() {
  // freopen("1.txt", "r", stdin);
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int T; std::cin >> T;
  while (T --) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++ i) std::cin >> a[i], sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= m; ++ i) std::cin >> b[i];
    
    int now = 1;
    f[0][0] = f[1][0] = 0, g[0][0] = g[1][0] = 1;
    for (int i = 1; i <= n; ++ i) f[0][i] = kInf, g[0][i] = 0;

    for (int i = 1; i <= m; ++ i, now ^= 1) {
      for (int r = 1, l = 1, r1 = 0; r <= n; ++ r) {
        f[now][r] = f[now ^ 1][r], g[now][r] = g[now ^ 1][r];
        while (l <= r && sum[r] - sum[l - 1] > b[i]) ++ l;

        if (l <= r) {
          r1 = std::max(r1, l - 1);
          while (r1 < r - 1 && f[now][r1 + 1] == f[now][l - 1]) ++ r1;

          if (f[now][r] > f[now][l - 1] + m - i) {
            f[now][r] = f[now][l - 1] + m - i;
            g[now][r] = (pre[r1] - pre[l - 1] + g[now][l - 1] + p) % p;
          } else if (f[now][r] == f[now][l - 1] + m - i) {
            (g[now][r] += (pre[r1] - pre[l - 1] + g[now][l - 1] + p) % p) %= p;
          }
        }
        pre[r] = (pre[r - 1] + g[now][r]) % p;
      }
    }
    if (f[now ^ 1][n] >= kInf) {
      std::cout << -1 << "\n";
    } else {
      std::cout << f[now ^ 1][n] << " " << g[now ^ 1][n] << "\n";
    }
  }
  return 0;
}
```

---

## 作者：CReatiQ (赞：1)

先讲 D1。

因为操作过程中 $k$ 是不降的，我们直接枚举 $k$。

记 $dp_i$ 是当前 $k$ 下将 $a$ 中前 $i-1$ 个位置删去的最小代价。

对每个 $i$，前缀和 + 二分可以得到它在当前 $k$ 下一次操作可以到达的最右位置 $to$。

则 $ dp_{i} + m - k \to dp_{to}$。

```cpp
void R()
{
	int n,m;
	cin>>n>>m;
	vector<i64> a(n+1),b(m+1),pre(n+1),dp(n+2,inf);
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
	for (int i=1;i<=m;i++) cin>>b[i];
	dp[1]=0;
	for (int k=1;k<=m;k++)
		for (int i=1;i<=n;i++)
		{
			int to=upper_bound(pre.begin(),pre.end(),pre[i-1]+b[k])-pre.begin();
			dp[to]=min(dp[to],dp[i]+m-k);
		}
	if (dp[n+1]==inf) cout<<"-1\n";
	else cout<<dp[n+1]<<'\n';
	return;
}
```

D1 可以贪心转移到 $to$，但 D2 不行。

此时 $i$ 需要转移到 $[i+1,to]$ 的每个位置，线段树维护即可。


```cpp
void R()
{
	int n,m;
	cin>>n>>m;
	vector<i64> a(n+1),b(m+1),pre(n+1);
	SGT<Info,Info> dp(n+2);
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
	for (int i=1;i<=m;i++) cin>>b[i];
	dp.modify(1,{0,1});
	for (int k=1;k<=m;k++)
		for (int i=1;i<=n;i++)
		{
			int to=upper_bound(pre.begin(),pre.end(),pre[i-1]+b[k])-pre.begin();
			Info now=dp.rangeQuery(i,i+1);
			dp.rangeApply(i+1,to+1,{now.val+m-k,now.ways});
		}
	Info ans=dp.rangeQuery(n+1,n+2);
	if (ans.val==inf) cout<<"-1\n";
	else cout<<ans.val<<' '<<ans.ways<<'\n';
	return;
}
```

---

## 作者：liugh_ (赞：0)

提供一个不太一样的转移及优化方式。

## [The Endspeaker (Hard Version)](https://codeforces.com/contest/2027/problem/D2)

将 $a$ 分成若干段，每段有限制，考虑以段为阶段性的体现来 dp，显然只有两个变量：$a$ 选到哪和 $b$ 选到哪，而 $nm\le 3\cdot 10^5$ 印证了我们的想法，于是设 $f(i,j)$ 为 $a$ 选到 $i$，$b$ 选到 $j$ 时最小花费。记 $s_x=\sum_{i=1}^{x} a_i$，根据定义显然有转移
$$
f(i,j)=\min_{s_i-s_k\le b_j} \min_{h\le j} f(k,h)+m-j
$$
**贪心地，$k$ 越小越好**。$k$ 越大，对于当前状态没有影响，却会使上一个状态的和更大，于是不优。求 $k$ 是容易的，那么方程只剩下一个 $\min$ 需要处理，注意到 $h\le j$，记录前缀 $\min$ 即可，至此 Easy Version 已经搞定，时间复杂度 $O(nm)$ 或 $O(nm\log n)$。

考虑求方案数，类似地，设 $g(i,j)$ 为 $a$ 选到 $i$，$b$ 选到 $j$ 时取到最小花费的方案数。此时我们不能只考虑最优的 $k$。将方程第一个 $\min$ 的限制进行移项，有 $s_k\ge s_i-b_j$，显然可以直接上三维偏序，然而我们可以改变顺序先枚举 $j$ 再枚举 $i$，让 $h\le j$ 自然满足，那么仅需开**一个**线段树维护区间最小值及出现次数即可，时间复杂度 $O(nm\log n)$。

```cpp
auto mo=[](auto&&x){if(x>=mod)x-=mod;return x;};
auto chk=[](pii&a,pii b){if(b.fi<a.fi)a=b;else if(b.fi==a.fi)mo(a.se+=b.se);};
struct _sgt{
	vector<pii> nd;
	#define mid ((l+r)>>1)
	#define lc (x<<1)
	#define rc (x<<1|1)
	pii up(pii a,pii b){
		pii c{inf,0};
		chk(c,a),chk(c,b);
		return c;
	}
	void upd(int x,int l,int r,int ql,pii k){
		if(l==r)return chk(nd[x],k);
		if(ql<=mid)upd(lc,l,mid,ql,k);
		else upd(rc,mid+1,r,ql,k);
		nd[x]=up(nd[lc],nd[rc]);
	}
	pii qry(int x,int l,int r,int ql,int qr){
		if(ql>qr)return {inf,0};
		if(ql<=l&&r<=qr)return nd[x];
		if(ql>mid)return qry(rc,mid+1,r,ql,qr);
		if(qr<=mid)return qry(lc,l,mid,ql,qr);
		return up(qry(rc,mid+1,r,ql,qr),qry(lc,l,mid,ql,qr));
	}
}sgt{vector<pii>(n*4+5,{inf,0})};
sgt.upd(1,0,n,0,{0,1});
for(int j=1;j<=m;j++){
	for(int i=1;i<=n;i++){
		int k=lower_bound(&s[0],&s[n]+1,s[i]-b[j])-&s[0];
		pii t=sgt.qry(1,0,n,k,i-1);
		t.fi+=m-j;
		sgt.upd(1,0,n,i,t);
	}
}
pii ans=sgt.qry(1,0,n,n,n);
if(ans.fi>1e18)cout<<-1<<'\n';
else cout<<ans.fi<<' '<<ans.se<<'\n';
```

---

## 作者：I_will_AKIOI (赞：0)

前面的东西可以看 [CF2027D1](https://www.luogu.com.cn/article/ggten49b) 题解。

和 D1 一样，设状态 $f_{i,j}$ 表示已经删了 $i-1$ 个元素（也就是从第 $i$ 个元素开始删），$k=j$ 需要花费的最小值，只不过这次要多一个 $g_{i,j}$ 表示方案数。

然后线段树需要多维护一个东西，也就是区间 $f_{i,j}$ 最小值的 $g_{i,j}$ 的和，也就是当前节点的结果等于左儿子和右儿子权值较小的那一个，如果权值相同，那么就返回他们的和。并且操作一的代码也需要进行修改，思路和线段树部分类似。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#pragma GCC optimize("O3")
using namespace std;
struct Data{int l,r,minn,sum;};
int n,m,ans,tot;
void build(vector<Data>&t,int k,int l,int r)
{
	t[k].l=l,t[k].r=r;
	if(l==r)
	{
		t[k].minn=1e18;
		t[k].sum=1;
		return;
	}
	int mid=l+r>>1;
	build(t,k*2,l,mid),build(t,k*2+1,mid+1,r);
	t[k].minn=min(t[k*2].minn,t[k*2+1].minn);
	if(t[k*2].minn==t[k*2+1].minn) t[k].sum=(t[k*2].sum+t[k*2+1].sum)%mod;
	else if(t[k*2].minn<t[k*2+1].minn) t[k].sum=t[k*2].sum;
	else t[k].sum=t[k*2+1].sum;
	return;
}
void update(vector<Data>&t,int k,int l,int x,int y)
{
	if(t[k].l==l&&t[k].r==l)
	{
		t[k].minn=x;
		t[k].sum=y;
		return;
	}
	int mid=t[k].l+t[k].r>>1;
	if(l<=mid) update(t,k*2,l,x,y);
	if(l>mid) update(t,k*2+1,l,x,y);
	t[k].minn=min(t[k*2].minn,t[k*2+1].minn);
	if(t[k*2].minn==t[k*2+1].minn) t[k].sum=(t[k*2].sum+t[k*2+1].sum)%mod;
	else if(t[k*2].minn<t[k*2+1].minn) t[k].sum=t[k*2].sum;
	else t[k].sum=t[k*2+1].sum;
	return;
}
pair<int,int> query(vector<Data>&t,int k,int l,int r)
{
	if(l<=t[k].l&&t[k].r<=r) return {t[k].minn,t[k].sum};
	int mid=t[k].l+t[k].r>>1,res=1e18,sum=0;
	pair<int,int>p;
	if(l<=mid)
	{
		p=query(t,k*2,l,r);
		if(p.first==res) sum=(sum+p.second)%mod;
		else if(p.first<res) res=p.first,sum=p.second;
	}
	if(r>mid)
	{
		p=query(t,k*2+1,l,r);
		if(p.first==res) sum=(sum+p.second)%mod;
		else if(p.first<res) res=p.first,sum=p.second;
	}
	return {res,sum};
}
void solve()
{
	cin>>n>>m;
	vector<int>a(n+5,0),b(m+5,0),sum(n+5,0);
	vector<vector<int> >f(n+5),g(n+5);
	vector<vector<Data> >t(m+5);
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=0;i<=n+4;i++) f[i].resize(m+5,1e18),g[i].resize(m+5,0);
	for(int i=1;i<=m;i++) t[i].resize(n*4+10),build(t[i],1,1,n+1);
	f[1][1]=0,g[1][1]=1;
	for(int i=1;i<=n+1;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int l=1,r=i,mid,k=-1;
			while(l<r)
			{
				mid=l+r>>1;
				if(sum[i-1]-sum[mid-1]<=b[j]) r=k=mid;
				else l=mid+1;
			}
			if(k!=-1)
			{
				pair<int,int>p=query(t[j],1,k,i-1);
				f[i][j]=p.first+m-j,g[i][j]=p.second;
			}
		}
		int minn=1e18,sum=0;
		if(i!=n+1)
		{
			for(int j=1;j<=m;j++)
			{
				if(minn==f[i][j])
				{
					int pos=g[i][j];
					g[i][j]=(g[i][j]+sum)%mod,
					sum=(sum+pos)%mod;
				}
				else if(minn<f[i][j]) g[i][j]=sum;
				else sum=g[i][j];
				minn=min(minn,f[i][j]);
				f[i][j]=min(f[i][j],minn);
				update(t[j],1,i,f[i][j],g[i][j]);
			}
		}
	}
	ans=1e18;
	tot=0;
	for(int i=1;i<=m;i++) ans=min(ans,f[n+1][i]);
	for(int i=1;i<=m;i++) if(f[n+1][i]==ans) tot=(tot+g[n+1][i])%mod;
	if(ans==1e18) cout<<-1<<"\n";
	else cout<<ans<<" "<<tot<<"\n";
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

