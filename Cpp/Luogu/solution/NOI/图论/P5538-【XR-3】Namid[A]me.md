# 【XR-3】Namid[A]me

## 题目描述

小 X 给了你一棵 $n$ 个点的树，点有点权。

你需要求出下列式子模 $786433$ 的值：

$\sum_{1\leq u\leq v\leq n}f(u,v)^{f(u,v)}$

其中 $f(u,v)$ 表示 $u$ 到 $v$ 的最短路径上所有点的点权按位与在一起之后的值。

提示：为了方便你的计算，这里我们认为 $0^0=0$。另外，$786433$ 是一个质数，同时也是一个不常用的 NTT 模数，它的原根为 $10$，如果你不知道什么是 NTT 或者不知道什么是原根，你可以忽略这个提示。

## 样例 #1

### 输入

```
10
15 50 89 9 38 73 38 23 6 52
2 1
3 2
4 2
5 3
6 3
7 5
8 7
9 1
10 7
```

### 输出

```
54184
```

## 样例 #2

### 输入

```
20
17 56 72 12 16 43 33 8 28 90 21 12 7 43 55 95 25 65 63 77
2 1
3 2
4 1
5 3
6 5
7 1
8 7
9 7
10 3
11 5
12 7
13 5
14 7
15 11
16 6
17 3
18 15
19 15
20 13
```

### 输出

```
503636
```

# 题解

## 作者：ix35 (赞：8)

全文链接：https://www.luogu.com.cn/blog/ix-35/xr-3-zuo-ti-ji-lu

这里有一种和已有题解不完全一样的做法。

### E. Namid[A]me

**难度：**$\bigstar\bigstar\bigstar$​

**题目大意：**

给定 $n$ 个点的点带权树，设其叶子（度数为 $1$ 的点）个数为 $d$，点 $i$ 的权值为 $a_i$，令 $f(u,v)$ 为 $u\to v$ 路径上点权与，对所有无序对 $(u,v)$ 求和 $f(u,v)^{f(u,v)}$，答案对 $786433$ 取模，模数有一个原根是 $10$​。

$1\leq n\leq 2\times 10^5,\ \ a_i<2^{30},\ \ 1\leq n\times d\leq 3\times 10^6$​

**题目解法：**

显然树中的任意一条路径是以某个叶子为根时的一段祖先链，我们不妨依次枚举叶子 $l_1,\ldots,l_d$ 为根，统计祖先链的贡献。

对于确定的 $u$，枚举其祖先 $v$ 的过程中，显然 $f(u,v)$ 只有不超过 $\log A$ 种取值（$A$ 是 $a_i$ 的上界），并且在 DFS 过程中对每一位记录最深的这一位为 $0$ 的点就可以得到这 $\log A$ 种值和它们的分界点，于是只需要 $O(n\log A)$ 就可以统计所有祖先链的答案。

但是这样会重复计算，所以我们不妨让 $l_i$ 为根时不再计算在 $l_1,\ldots,l_{i-1}$ 为根时已经计算过的那些路径。

设祖先链是 $u\to v$（$v$ 是祖先，$u$ 是后代），再设 $w$ 是 $v$ 到 $u$ 路径上 $v$ 的后继点，那么这条祖先链之前没有被算过，当且仅当 $l_1,\ldots,l_{i-1}$ 都在 $w$ 的子树中，且都不在 $u$ 的子树中，也就是说我们只是对 $u$ 的选取进行限制，然后再限制 $v$ 是 $u$ 的深度不超过一个定值的祖先，还是可以用与上面相同的 DFS 方法求解。

注意利用原根使得幂的计算变为 $O(1)$ 的。

时间复杂度为 $O(dn\log A)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200010,P=786433;
int n,x,y,cnt,nw,ans,lf[MAXN],a[MAXN],b[MAXN],dp[MAXN];
int lg[P+10],ex[P+10],f[MAXN],dep[MAXN],srt[MAXN];
pair <int,int> las[MAXN][32];
vector <int> v[MAXN];
bool cmp (pair <int,int> a,pair<int,int> b) {return a.first>b.first;}
int calc (int x) {
	if (x%P==0) {return 0;}
	return ex[(1ll*x*lg[x%P])%(P-1)];
}
void gt (int a,int b) {
	//cout << "    " << a << "  " << b << "  ";
	int tmp=dep[b];
	if (!srt[b]) {
		sort(las[b],las[b]+30,cmp);
		srt[b]=1;
	}
	for (int i=0;i<30;i++) {
		ans=(ans+(1ll*calc(a)*(tmp-las[b][i].first))%P)%P;
		tmp=las[b][i].first;
		if (a&(1<<las[b][i].second)) {a^=(1<<las[b][i].second);}
	}
	//cout << ans << endl;
	return;
}
void dfs1 (int x,int fa) {
	dp[x]=b[x],f[x]=fa,dep[x]=dep[fa]+1,srt[x]=0;
	for (int i=0;i<30;i++) {
		las[x][i]=las[fa][i];
		if (!(a[x]&(1<<i))) {las[x][i]=make_pair(dep[x],i);}
	}
	int len=v[x].size();
	for (int i=0;i<len;i++) {
		if (v[x][i]==fa) {continue;}
		dfs1(v[x][i],x);
		dp[x]+=dp[v[x][i]];
	}
	return;
}
void dfs2 (int x,int dep,int mdep,int nwv) {
	if (dp[x]==nw) {mdep=f[x];}
	else {nwv&=a[f[x]];}
	if (dp[x]==0) {gt(nwv&a[x],mdep);}
	int len=v[x].size();
	for (int i=0;i<len;i++) {
		if (v[x][i]==f[x]) {continue;}
		dfs2(v[x][i],dep+1,mdep,nwv);
	}
	return;
}
int main () {
	ex[0]=1;
	for (int i=1;i<P;i++) {
		ex[i]=(1ll*ex[i-1]*10)%P;
		lg[ex[i]]=i;
	}
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		ans=(ans+calc(a[i]))%P;
	}
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		v[x].push_back(y),v[y].push_back(x);
	}
	for (int i=1;i<=n;i++) {
		if (v[i].size()==1) {lf[++cnt]=i;}
	}
	for (int i=1;i<=cnt;i++) {
		for (int j=0;j<30;j++) {las[0][j]=make_pair(0,j);}
		dfs1(lf[i],0);
		dfs2(lf[i],1,0,(1<<30)-1);
		b[lf[i]]=1,nw++;
		//cout << i << "  " << lf[i] << "  " << ans << endl;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：a___ (赞：7)

复杂度分析题。  

记 $w=\log_2a_i$。

显然 $f(u,v)^{f(u,v)}$ 这种东西，与和的与和次方，难以拆分，所以我们考虑暴力求出每种值的出现次数。

首先，我们有一个非常经典的结论，就是一条链上，固定起点 $u$，不同的 $f(u,v)$ 仅有 $\mathbf O(w)$ 种。因为显然假设存在链 $u,\cdots,v_1,v_2$，且 $f(u,v_2)\not=f(u,v_1)$，那么，$f(u,v_2)$ 一定是 $f(u,v_1)$ 二进制某几位的 $1$ 变成 $0$。由于一共有 $w$ 位，所以一共有 $\mathbf O(w)$ 种。

其次，可以推出一个有 $d$ 个叶子的子树，对于树中所有点 $u$，$f(rt,u)$ 仅有 $\mathbf O(dw)$ 种。因为每一个从根到叶子的路径上有 $\mathbf O(w)$ 种，那么这 $d$ 个路径的并显然有 $\mathbf O(dw)$ 种。那么我们对每个点的子树都维护一下每种值的出现次数，这一部分的复杂度是 $\mathbf O(ndw)$ 的。

另外，我们还要求出跨越子树的根的贡献，由于每两个叶子只会在它们的 lca 处合并，所以这一部分贡献的复杂度是 $\mathbf O(d^2w^2)$ 的。而显然这个贡献还有另外一个上界 $\mathbf O(n^2)$，因为最多有 $n^2$ 条路径。根据 $\min(a,b)\leq\sqrt{ab}$，复杂度为 $\min(\mathbf O(d^2w^2),\mathbf O(n^2))=\mathbf O(ndw)$。  

综上，暴力求每种值的出现次数的复杂度为 $\mathbf O(ndw)$，可以通过本题。  

trick1：由于本题已经说明了模数 $p$ 是质数并给出了其原根，所以我们可以轻易 $\mathbf O(p)$ 求出每个数关于原根 $g$ 的离散对数 $ind$，以及 $g^i$，则 $x^x=pow[ind[x\bmod p]x\bmod(p-1)]$。这样我们就可以 $\mathbf O(1)$ 求出 $x^x$。

trick2：`vector` 在 `clear()` 之后可以使用 `shrink_to_fit()` 函数清空使用内存，减少空间使用，使空间复杂度正确。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
const int N=2e5+10,mod=786433;
int n,a[N],ind[mod],pwg[mod],ans;
std::vector<int>to[N];
std::vector<std::pair<int,int>>c[N];
inline void add(){int a,b;scanf("%d%d",&a,&b);to[a].push_back(b);to[b].push_back(a);}
inline void add(int x,int y){if(x%mod)ans=(ans+1ll*pwg[1ll*ind[x%mod]*x%(mod-1)]*y)%mod;}
inline void merge(int x,int y)
{
	for(auto &p:c[y])
	{
		p.first&=a[x];
		for(const auto &q:c[x])add(p.first&q.first,1ll*p.second*q.second%mod);
	}
	c[y].insert(c[y].end(),c[x].begin(),c[x].end());c[x].clear();
	std::sort(c[y].begin(),c[y].end());
	for(auto &p:c[y])c[x].empty()||c[x].back().first!=p.first?c[x].push_back(p),0:c[x].back().second+=p.second;
	c[y].clear();c[y].shrink_to_fit();
}
void dfs(int u,int f)
{
	c[u].emplace_back(a[u],1);add(a[u],1);
	for(int v:to[u])if(v!=f)dfs(v,u),merge(u,v);
}
int main()
{
	int i;for(pwg[0]=i=1;i<mod;i++)ind[pwg[i]=10*pwg[i-1]%mod]=i;
	scanf("%d",&n);for(i=1;i<=n;i++)scanf("%d",&a[i]);for(i=1;i<n;i++)add();
	dfs(1,0);printf("%d\n",ans);return 0;
}
```

---

## 作者：zhangshiyan (赞：1)

# P5538 【XR-3】Namid[A]me

[R226464014 记录详情](https://www.luogu.com.cn/record/226464014)

## 前言

这是一道树上路径统计与位运算结合的难题。虽然路径贡献的套路不少见，但这题的难点在于我们需要统计的是路径上所有点权的按位与结果，并且还要计算其幂次，这就涉及了一些不常考察的技巧，比如离散对数和原根。

整体思路其实并不复杂，但实现细节需要注意优化和技巧。

前置知识：原根和阶，离散对数

感谢 [a___](https://www.luogu.com.cn/user/35137) 的[题解](https://www.luogu.com.cn/article/bw9awa48)。

## 题目大意

给你一棵 $n$ 个点的树，每个点有点权 $a_i$。

$\sum_{1\leq u\leq v\leq n}f(u,v)^{f(u,v)} \bmod 786433$ 的值

其中 $f(u,v)$ 表示 $u$ 到 $v$ 的最短路径上所有点的点权按位与在一起之后的值。

注意：本题中 $0^0=0$。另外，$786433$ 是一个质数，它的原根为 $10$。

## 思路

我们观察到数据范围：

- $2 \le n \le 2 \times 10^5$。

如果直接枚举所有 $O(n^2)$ 条路径，然后计算每条路径的按位与、再快速幂，复杂度显然不行。

数据范围中有一条：对于所有满足 $1\le i \le n$ 的 $i$ 都有 $1 \le a_i < 2^{30}$，而且题目中求的是所有点的点权按位与在一起之后的值。

考虑路径上的按位与操作，它具有单调性：路径上点权的按位与不会变大。
并且，点权最多是 $2^{30}$，所以按位与的结果最多只有 $30$ 位，最多只有 $O(30n)$ 种可能值。

这提示我们可以使用换根树形 DP，子树合并时传递路径上的状态，统计出现次数。

我们令 $f_u$ 维护从子树内节点出发，到达当前节点路径上形成的所有路径上按位与值 $val$ 和出现次数 $cnt$ 的集合，在每次 DFS 回溯时合并子树信息，再去计算 $x^x$ 模 $mod$ 的值。

以上就是大体的思路了，但是到目前为止你有没有发现题目中的提示还没有利用过？这就对了，因为我们还没有优化这个代码。

优化 1：由于模数较大，直接计算 $x^x$ 会爆炸。
但模数是质数，并且给了我们原根 $10$，可以对 $x$ 做离散对数映射，将模运算转换为指数域的加法。

我们预处理出：

$powg_{i} = 10^i \bmod 786433$；

$ind_{x} = y$ 表示 $x \equiv 10^y \bmod 786433$。

最终使用：

$$
x^x \equiv g^{\text{ind}[x] \cdot x \bmod (mod-1)} \bmod mod
$$

优化 2：由于我们在代码中使用了大量的 vector，我们直接使用 clear () 函数会导致 MLE，为了防止 MLE，进一步优化内存，我们可以使用 C++11 推出的 shrink_to_fit () 函数释放内存。

到目前为止，代码的时间复杂度为 $O(n\times d \times \log_2{A})$。

具体的时间复杂度分析可参考：[a___](https://www.luogu.com.cn/user/35137) 的[题解](https://www.luogu.com.cn/article/bw9awa48)。

## 代码

```cpp
#include <bits/stdc++.h>
#define INF (ll)1e18
using namespace std;
typedef long long ll;

inline ll read()
{
	ll x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-')
		{
			f = -1;
		}
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	return x * f;
}

const int N = 2e5 + 5;
const ll mod = 786433;

ll ans;
ll a[N], ind[mod], powg[mod];
vector<ll> g[N];
vector<pair<ll, ll>> f[N];

void add(ll x, ll cnt)
{
	if(x % mod != 0)
	{
		ll val = powg[ind[x % mod] * x % (mod - 1)];
		ans = (ans + val * cnt % mod) % mod;
	}
}

void merge(ll u, ll v)
{
	for(auto & pv : f[v])
	{
		pv.first &= a[u];
		for(auto & pu : f[u])
		{
			add(pu.first & pv.first, pu.second * pv.second % mod);
		}
	}
	map<ll, ll> tmp;
	for(pair<ll, ll> p : f[v])
	{
		tmp[p.first] += p.second;
	}
	for(pair<ll, ll> p : f[u])
	{
		tmp[p.first] += p.second;
	}
	f[u].clear();
	f[v].clear();
	f[u].shrink_to_fit();
	f[v].shrink_to_fit();
	for(pair<ll, ll> p : tmp)
	{
		f[u].push_back(make_pair(p.first, p.second));
	}
}

void dfs(ll u, ll fa)
{
	f[u].push_back(make_pair(a[u], 1));
	add(a[u], 1);
	for(ll v : g[u])
	{
		if(v == fa)
		{
			continue;
		}
		dfs(v, u);
		merge(u, v);
	}
}

int main()
{
	powg[0] = 1;
	for(int i = 1; i < mod; i++)
	{
		powg[i] = 10 * powg[i - 1] % mod;
		ind[powg[i]] = i;
	}
	ll n = read();
	for(int i = 1; i <= n; i++)
	{
		a[i] = read();
	}
	for(int i = 1; i < n; i++)
	{
		ll u = read(), v = read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

[前情提要](https://www.luogu.com.cn/blog/DengDuck/noip-mu-ni-lian-ce-11-yue-7-ri-di-si-ti-abstract-ti-xie)。

感谢 $\text{Jijidawang}$ 指路。

统计路径的方法，我们可以用类似于点分治的“在这个节点统计子树中所有经过这个节点的路径”的方法，每个节点用个 `map` 记录所有其子树中节点到祖先的点对（保存与和或的值）及其出现次数，直接做就可以了。

注意用 `map` 不然空间大，求完父亲要清空儿子的 `map`。

为什么时间复杂度是对的呢？我们设树叶子数量为 $k$，显然 $k\leq n$，根据题意，$k\leq 2\times10^3$。

这题找找性质，注意到对于固定的 $i$，其到一个叶子节点的这个链上，所有的 $f(i,x)$，由于一个 $f(i,x)$ 应该是由父亲转移过来的，所以只有可能减少 $1$ 的数字或者不变，所以 $f(i,x)$ 的种类应该是 $\log n$ 级别的。


然后我们发现需要多个儿子合并的位置，可以理解为两个叶子的最近公共祖先，有 $\mathcal O(k)$ 个这样的点，然后我们计算答案，因为两边的数对数量都是 $k\log n$ 级别的，所以合并的时间复杂度为 $\mathcal O(k^2\log^2n)$。

然后其他统计数对的时间复杂度就为 $\mathcal O(nk\log n)$。

处理幂可以做到 $\mathcal O(1)$，利用 $\mathcal O(n)$ 预处理离散对数，我们可以直接套式子：$x^x\equiv g^{x\log_g x}\pmod p$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define fir first
#define sec second
using namespace std;
//const LL inf;
const LL N=2e5+5;
//const LL M;
const LL mod=786433;
const LL G=10;
//const LF eps;
const LL P=20090327;
LL n,a[N],ans,lg[mod+5],pw[mod+5];
namespace OI{
#define BF_SIZE 1000
	bool IOerr=0;
	inline char nc(){
		static char buf[BF_SIZE],*p1=buf+BF_SIZE,*pend=buf+BF_SIZE;
		if(p1==pend){
			p1=buf;
			pend=buf+fread(buf,1,BF_SIZE,stdin);
			if(pend==p1){IOerr=1;return -1;}
		}
		return *p1++;
	}
	inline bool bla(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	inline void Rd(LL &x){
		char ch;
		while(bla(ch=nc()));
		if(IOerr){return;}
		for(x=ch-'0';(ch=nc())>='0'&&ch<='9';x=x*10+ch-'0');
	}
#undef BF_SIZE
};
map<LL,LL>ma[N];
vector<LL>v[N];
inline LL ksm(LL x)
{
	if(x%mod==0)return 0;
	return pw[x*lg[x%mod]%(mod-1)];
}
void dfs(LL x,LL fa)
{
	ma[x][a[x]]=1;
	ans=(ans+ksm(a[x]))%mod;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x);
		for(auto j:ma[x])
		{
			for(auto k:ma[i])ans=(ans+ksm(j.fir&k.fir)*j.sec*k.sec%mod)%mod;
		}
		for(auto j:ma[i])
		{
			ma[x][j.fir&a[x]]+=j.sec;
		}
		ma[i].clear();
	}
}
int main()
{
	pw[0]=1,lg[1]=0;
	for(int i=1;i<=mod;i++)
	{
		pw[i]=pw[i-1]*G%mod;
		lg[pw[i]]=i;
	}
	OI::Rd(n);
	for(int i=1;i<=n;i++)
	{
		OI::Rd(a[i]);
	}
	for(int i=1;i<=n-1;i++)
	{
		LL x,y;
		OI::Rd(x),OI::Rd(y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
//RP++
```

---

## 作者：Kinesis (赞：1)

### P5538 【XR-3】Namid[A]me

用点分治和哈希加速~~水了一个~~AC（逃

用点分治降低树上方案统计复杂度，将决策点加入到hash中，然后分治计算方案、、当时码的时候，极度害怕过多决策点，复杂度趋于$O(n^2)$，不过由于与操作，单个子树最多产生$O(|S|*30)$的决策点，其中$|S|$是现有决策集的秩、、虽然还是数量巨大。。

计算$x^x(\%p)$时可用原根加速取模（参考了标答的做法，原本用快速幂TLE了。。）根据原根性质，x可以被原根表示$x\equiv g^k(\%p),x^x \equiv (g^k)^{g^k} \equiv g^{kg^k}(\%p)$,取以$g$为底的离散对数，

$Indx \equiv k$,故$x^x \equiv g^{x*Indx}(\%\varphi(p))$

故$x^x\equiv x*Indx$,预处理对数和g的幂，介样子就可以就可以$O(1)$求了qwq

代码：

```cpp
//code sourced from kinesis
#include<bits/stdc++.h>
using namespace std;

#define _REP(i,a,b) for(int i = (a) ; i >= (int)(b) ; --i )
#define REP(i,a,b) for(int i = (a) ; i <= (int)(b) ; ++i )
#define UREP(i,u) for(int i = p[(u)] ; i + 1 ; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int,int>
#define mp(x,y) make_pair((x), (y))
#define ll long long
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 786433;
const double eps = 1e-9;
#define mem(x,v) memset((x), (v), sizeof (x))
#define ri1(x) scanf("%d", &(x))
#define ri2(x,y) scanf("%d%d", &(x), &(y))
#define ri3(x,y,z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a,b,c,d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
#define pi1(a) printf("%d\n", (a))
#define pi2(a,b) printf("%d%d\n", (a), (b))
//#define Debug
#ifdef Debug
#endif // debug

ll final_ans = 0;

ll fpow(int x);

namespace HASH
{
    const int NHASH = 40000019;
    int head[NHASH],eid;
    bool exi[NHASH];
    int h_num[NHASH],pid;
    struct node {int key,next;ll val;}N[NHASH];
    void init() {memset(head,-1,sizeof head),memset(exi,0,sizeof exi),eid = 0;}
    void clear() {REP(i,0,pid-1) exi[h_num[i]] = 0,head[h_num[i]] = -1;eid = 0,pid = 0;}
    int HASH_num(int num) {return (num % NHASH + NHASH) % NHASH;}
    void HASH_insert(int key,ll val)
    {
        int num = HASH_num(key);
        for(int i=head[num];i+1;i=N[i].next){
            if(N[i].key==key){
                N[i].val += val;
                return ;
            }
        }
        N[eid].key = key;
        N[eid].val = val;
        N[eid].next = head[num];
        head[num] = eid++;
        if(!exi[num]) h_num[pid++] = num;
    }
    void HASH_go(int key,int id)
    {
        REP(j,0,pid-1){
            for(int i=head[h_num[j]];i+1;i = N[i].next){
                if(id) HASH_insert(N[i].key&key,N[i].val);
                else (final_ans += N[i].val * fpow(N[i].key&key)) %= mod;
            }
        }
    }
}


const static int maxn = 2e5 + 5,maxm = 4e5 + 5;
struct E
{
    int v,next;
}edge[maxm];
int p[maxn],eid;
void init_E(){memset(p,-1,sizeof p),eid = 0;}
void link1(int u,int v){edge[eid].v = v,edge[eid].next = p[u],p[u] = eid++;}
void link2(int u,int v){link1(u,v),link1(v,u);}
int size[maxn],maxs[maxn],totsize,root,a[maxn];
ll g[mod+5],fac[mod+5],G = 10;
bool mark[maxn];

void init() {
	g[0] = 1,fac[1] = 0,fac[0] = 0;
	REP(i,1,mod-1) g[i] = 1ll * g[i - 1] * G % mod,fac[g[i]] = i;
}

ll fpow(int x) {
	if(x % mod != 0) return 1LL * g[(1ll * fac[( x % mod )] * x) % (mod - 1)];
	return 0;
}

void dfs1(int u,int fa)
{
    size[u] = 1,maxs[u] = 0;
    UREP(i,u){
        int v = edge[i].v;
        if(v!=fa&&!mark[v]){
            dfs1(v,u);
            size[u] += size[v];
            maxs[u] = max(maxs[u],size[v]);
        }
    }
    maxs[u] = max(maxs[u],totsize-size[u]);
    if(maxs[u]<maxs[root]) root = u;
}

void modify(int u,int fa,int ad)
{
    ad &= a[u];
    HASH::HASH_go(ad,0);
    UREP(i,u){
        int v = edge[i].v;
        if(v==fa||mark[v]) continue;
        modify(v,u,ad);
    }
}

void add(int u,int fa,int ad)
{
    ad &= a[u];
    HASH::HASH_insert(ad,1);
    UREP(i,u){
        int v = edge[i].v;
        if(v==fa||mark[v]) continue;
        add(v,u,ad);
    }
}

void solve(int rt)
{
    mark[rt]=1;
    HASH::HASH_insert(a[rt],1);
    (final_ans += fpow(a[rt])) %= mod;
    UREP(i,rt){
        int v = edge[i].v;
        if(mark[v]) continue;
        modify(v,rt,a[rt]);
        add(v,rt,a[rt]);
    }
    HASH::clear();
    int tnt = totsize;
    UREP(i,rt){
        int v = edge[i].v;
        if(!mark[v]){
            totsize = (size[v]>size[rt] ? tnt - size[rt] : size[v]);
            root=0;
            dfs1(v,0);
            solve(root);
        }
    }
}

int n;

void intn()
{
    maxs[0] = inf;
    root = 0;
    totsize = n;
    dfs1(1,0);
    solve(root);
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);//cf needn't delete this
    #endif // ONLINE_JUDGE
    HASH::init();
    init();
    init_E();
    ri1(n);
    REP(i,1,n) ri1(a[i]);
    REP(i,1,n-1){
        int u,v;
        ri2(u,v);
        link2(u,v);
    }
    intn();
    printf("%lld\n",final_ans);
    return 0;
}
```




---

## 作者：5k_sync_closer (赞：0)

对原树任意剖一下，然后链数等于叶子数。考虑分别算 $i,j$ 在相同 / 不同链上的贡献。

注意到一个点 $i$ 向链顶 / 链底延伸，形成的树链的 $f$ 值都不超过 $O(\log V)$ 种，

记下这些 $f$ 值的位置，记这些树链为 $i$ 的前缀 / 后缀。

考虑 $i,j$ 在相同链上的贡献，对每个 $i$ 统计其所有后缀即可。

考虑 $i,j$ 在不同链上的贡献，枚举这两条链，分情况讨论：

## 链顶无祖先关系

![](https://cdn.luogu.com.cn/upload/image_hosting/t9e5a491.png)

如图，$i\to j$ 的链一定由 $u$ 的一段后缀，$u\to v$，$v$ 的一段后缀拼成，

分别枚举 $u$ 的这段后缀、$v$ 的这段后缀取到哪个 $f$ 值即可。

## 链顶有祖先关系

![](https://cdn.luogu.com.cn/upload/image_hosting/vqk867rt.png)

如图，$i\to j$ 的链一定由 $u$ 的一段前缀 / 后缀，$u\to v$，$v$ 的一段后缀拼成，

分别枚举 $u$ 的这段前缀 / 后缀，$v$ 的这段后缀取到哪个 $f$ 值即可。

复杂度 $O(d^2\log^2V)$，可以利用原根做到 $O(1)$ 光速幂。

```cpp
%:include <cstdio>
%:include <vector>
%:include <algorithm>
%:define M 786433
using namespace std;
inline int R()
{
    int q = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        q = q * 10 + c - '0', c = getchar();
    return q;
}
struct E
{
    int v, t;
} e[400050];
pair<int, int> S0[400050][32], S1[400050][32];
int n, c, p, q, lg[M], _g[M], l0[50], l1[50], j0[400050], j1[400050], a[400050], z[400050], d[400050], f[400050], s[400050], t[400050], b[400050], h[400050], F[400050][20];
long long P(int x, int y) { return x % M ? _g[1ll * y * lg[x % M] % (M - 1)] : 0; }
void A(int u, int v)
{
    e[++c] = {v, h[u]};
    h[u] = c;
}
void X(int u, int k)
{
    s[u] = 1;
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
        {
            d[v] = d[f[v] = u] + 1;
            X(v, u);
            s[u] += s[v];
            if (s[v] > s[z[u]])
                z[u] = v;
        }
}
void Y(int u, int k)
{
    b[u] = ++p;
    t[u] = k;
    if (z[u])
        Y(z[u], k);
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != f[u] && v != z[u])
            Y(v, v);
}
int _F(int x, int y)
{
    int k = __lg(y - x + 1);
    return F[x][k] & F[y - (1 << k) + 1][k];
}
int QF(int x, int y)
{
    int q = ~0;
    while (t[x] != t[y])
    {
        if (d[t[x]] < d[t[y]])
            swap(x, y);
        q &= _F(b[t[x]], b[x]);
        x = f[t[x]];
    }
    if (d[x] > d[y])
        swap(x, y);
    return q & _F(b[x], b[y]);
}
int T(int x, int y)
{
    while (t[x] != y)
        x = f[t[x]];
    return x;
}
void Q(int F, int Z, int y)
{
    if (!Z)
        return;
    int f = F;
    q = (q + P(f, f) * Z * S1[y][0].first) % M;
    for (int k = 0; k < 30; ++k)
    {
        if (a[y] >> S1[y][k].second & 1)
            f &= ~(1ll << S1[y][k].second);
        q = (q + P(f, f) * Z * (S1[y][k + 1].first - S1[y][k].first)) % M;
    }
    if (a[y] >> S1[y][30].second & 1)
        f &= ~(1ll << S1[y][30].second);
    q = (q + P(f, f) * Z * (j1[y] - S1[y][30].first)) % M;
}
signed main()
{
    _g[0] = 1;
    for (int i = 1; i < M; ++i)
        lg[_g[i] = _g[i - 1] * 10 % M] = i;
    n = R();
    for (int i = 1; i <= n; ++i)
        a[i] = R();
    for (int i = 1, u, v; i < n; ++i)
        u = R(), v = R(), A(u, v), A(v, u);
    X(1, 0);
    Y(1, 1);
    for (int i = 1; i <= n; ++i)
        F[b[i]][0] = a[i];
    for (int j = 1; 1 << j <= n; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            F[i][j] = F[i][j - 1] & F[i + (1 << j - 1)][j - 1];
    for (int i = 1; i <= n; ++i)
        if (!z[i])
        {
            for (int j = 0; j <= 30; ++j)
                l0[j] = l1[j] = 0;
            for (int j = 1, x = i;; x = f[x], ++j)
            {
                j1[x] = j;
                for (int k = 0; k <= 30; ++k)
                    if (a[x] >> k & 1)
                        l1[k] = j, S1[x][k] = {j - l0[k], k};
                    else
                        l0[k] = j, S1[x][k] = {j - l1[k], k};
                sort(S1[x], S1[x] + 31);
                int f = a[x];
                q = (q + P(f, f) * S1[x][0].first) % M;
                for (int k = 0; k < 30; ++k)
                {
                    if (a[x] >> S1[x][k].second & 1)
                        f &= ~(1ll << S1[x][k].second);
                    q = (q + P(f, f) * (S1[x][k + 1].first - S1[x][k].first)) % M;
                }
                if (a[x] >> S1[x][30].second & 1)
                    f &= ~(1ll << S1[x][30].second);
                q = (q + P(f, f) * (j - S1[x][30].first)) % M;
                if (x == t[x])
                    break;
            }
        }
    for (int i = 1; i <= n; ++i)
        if (i == t[i])
        {
            for (int j = 0; j <= 30; ++j)
                l0[j] = l1[j] = 0;
            for (int j = 1, x = i;; x = z[x], ++j)
            {
                j0[x] = j;
                for (int k = 0; k <= 30; ++k)
                    if (a[x] >> k & 1)
                        l1[k] = j, S0[x][k] = {j - l0[k], k};
                    else
                        l0[k] = j, S0[x][k] = {j - l1[k], k};
                sort(S0[x], S0[x] + 31);
                if (!z[x])
                    break;
            }
        }
    for (int i = 1; i <= n; ++i)
        if (!z[i])
            for (int j = i + 1; j <= n; ++j)
                if (!z[j])
                {
                    int x = t[i], y = t[j];
                    if (d[x] > d[y])
                        swap(x, y);
                    if (b[x] <= b[y] && b[y] < b[x] + s[x])
                        x = T(y, x);
                    int F = QF(x, y), T = F;
                    Q(F, S1[x][0].first, y);
                    for (int k = 0; k < 30; ++k)
                    {
                        if (a[x] >> S1[x][k].second & 1)
                            F &= ~(1ll << S1[x][k].second);
                        Q(F, S1[x][k + 1].first - S1[x][k].first, y);
                    }
                    if (a[x] >> S1[x][30].second & 1)
                        F &= ~(1ll << S1[x][30].second);
                    Q(F, j1[x] - S1[x][30].first, y);
                    F = T;
                    Q(F, S0[x][0].first - 1, y);
                    for (int k = 0; k < 30; ++k)
                    {
                        if (a[x] >> S0[x][k].second & 1)
                            F &= ~(1ll << S0[x][k].second);
                        Q(F, S0[x][k + 1].first - S0[x][k].first, y);
                    }
                    if (a[x] >> S0[x][30].second & 1)
                        F &= ~(1ll << S0[x][30].second);
                    Q(F, j0[x] - S0[x][30].first, y);
                }
    printf("%d", q);
    return 0;
}
```


---

