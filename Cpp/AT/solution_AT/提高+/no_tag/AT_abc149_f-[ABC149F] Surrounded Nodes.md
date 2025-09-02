# [ABC149F] Surrounded Nodes

## 题目描述

给定一棵 $N$ 个节点的树 $T$ ，现在要给树上每个节点随机涂色，每个节点有 $\frac 1 2$ 的概率染成黑色， $\frac 1 2$ 的概率染成白色。对于一颗染过色的树，定义 $S$ 为包含树上所有被染成**黑色**的节点的，节点数**最小**的连通子图。定义 $S$ 的价值为 $S$ 中**白色**节点的个数。问 $S$ 的期望价值是多少。答案对 $10^9+7$ 取模。

## 说明/提示

* $2\le N \le2\times 10^5$
* $1\le A_i,B_i\le N$

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
125000001```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
375000003```

## 样例 #3

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
250000002```

## 样例 #4

### 输入

```
7
4 7
3 1
2 6
5 2
7 1
2 7```

### 输出

```
570312505```

# 题解

## 作者：EuphoricStar (赞：5)

不错的题。

考虑题目等价于，每个点等概率选或不选，求导出子图大小减选出点数的期望。

考虑一个点在导出子图的充要条件，发现不好计算。正难则反，考虑不在导出子图的充要条件，其实就是，所有点都在 $u$ 的**一棵子树内**，或者 $u$ 子树内没有选点。那么我们得到点 $u$ 在导出子图的概率是：

$$1 - \frac{2^{n - sz_u}}{2^n} - \sum\limits_{v \in son_u} \frac{2^{sz_v} - 1}{2^n}$$

导出子图大小的期望就是每个点在导出子图中的概率之和，选出点数的期望显然是 $\frac{n}{2}$，减一下就是最终答案。

[code](https://atcoder.jp/contests/abc149/submissions/42041104)

---

## 作者：mcqueen (赞：4)

为方便讲解，记 $val(S)$ 为 $S$ 的**价值**。

直接求 $val(S)$ 的期望值貌似有点难。根据期望的线性性质，我们可以考虑$T$上每一个节点对 $val(S)$ 的期望值的贡献。

由于树上每个节点被染成黑色、白色是等概率的，因此 $T $的 $2^n $种染色方案也是等概率的，所以 $val(S)$ 的期望值相当于**在 $T$ 的总共 $2^n$ 种不同的染色方案中 $val(S)$ 的总和除以 $2^n$ 。**

形式化地，可以这样写：

记 $T$ 的 $2^n$ 种染色方案对应的 $S$ 分别为： $S_1,S_2,...,S_{2^n}$ 。则我们有：

$$
val(S)\text{的期望值}=\frac {\sum_{i=1}^{2^n}val(S_i)}{2^n}
$$

这样，我们只需可以考虑 $T$ 上的每个节点在 $T$ 的 $2^n$ 种染色方案中，有多少次是对 $val(S)$ 有贡献的。简单来说，我们需要考虑某个节点在什么时候会被黑色节点“包围”：

* 当一个节点周围的所有子树都没有黑色节点时，显然该节点没有被“包围”。

* 当一个节点周围的所有子树中，只有一个子树有黑色节点，那么这个节点也没有被“包围”。

* 当一个节点周围的所有子树中，有两个或两个以上的子树有黑色节点，那么这个节点肯定会被包围。

而一个节点是白色的总方案数是 $2^{n-1}$ ，所以我们用 $2^{n-1}$ 减去**只有一个子树有黑色节点**的方案数以及**所有子树的节点都是白色**的方案数即可。

形式化地表达：

记 $res(x)$ 为某个节点 $x$ 对答案的贡献， $size(x)$ 表示以 $x$ 为根的子树的大小。

那么对于某个节点 $u$ ，我们有：

$$
res(u)=2^{n-1}-\left[\sum_{v\text{是}u\text{相邻的节点}}(2^{size(v)}-1)\right]-1
$$

稍微解释一下：

* 如果与以 $v$ 为根节点的子树是与所有的和 $u$ 相邻的子树中**唯一**的有被染黑的节点的子树，那么这将会有 $2^{size(v)}-1$ 种染色情况。所以，**只有一个子树有黑色节点**的方案数为 $\sum_{v\text{是}u\text{相邻的节点}}(2^{size(v)}-1)$ 。

* 显然，**所有子树的节点都是白色**的方案数为 $1$ 。

然后我们在 dfs 的过程中求出每个节点的贡献并求和，最后再除上 $2^n$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
#define N 200005
#define mod 1000000007
#define pb push_back
using namespace std;
template<typename T>
inline void in(T &x)
{
	x=0;
	bool fu=0;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')fu=1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
int n,sz[N];
vector<int> v[N];
int ksm(int x,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1)ret=1ll*ret*x%mod;
		p>>=1;
		x=1ll*x*x%mod;
	}
	return ret;
}
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
int ans=0;
void dfs(int from,int f)
{
	
	int all=ksm(2,n-1),res=0;
	sz[from]=1;
	for(int i=0;i<v[from].size();++i)
	{
		int to=v[from][i];
		if(to==f)continue;
		dfs(to,from);
		sz[from]+=sz[to];
		add(res,ksm(2,sz[to])-1);
	}
	add(res,ksm(2,n-sz[from])-1+mod);
	add(res,1);
	add(all,mod-res);
	add(ans,all);
}
int main()
{
	in(n);
	for(int i=1;i<n;++i)
	{
		int x,y;
		in(x);in(y);
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs(1,0);
	printf("%d\n",1ll*ans*ksm(ksm(2,n),mod-2)%mod);
	return 0;
}
```



---

## 作者：StevenLiTheOIer (赞：2)

## 思路：
由于 $n\le2\times10^5$，直接求期望肯定会超时。我们考虑把问题转化为求每一个点对答案的贡献。

先设当前子树的根为 $u$，与 $u$ 直接相连的点为 $v$，以 $v$ 为根的子树的大小为 $siz_v$，可得：

$ans_u = 2^{n-1}-\sum_v(2^{siz_v}-1)+1$

解释一下：当 $u$ 的至少 $2$ 棵子树中有黑点时，包含它们的连通子图必然经过 $u$ 点，对答案产生贡献，这种情况共有 $\sum_v(2^{siz_v}-1)$ 种（减去的 $1$ 是黑点在同一棵子树内的情况）。最后再去除所有点都是白点（空集）的 $1$ 种情况。

则最终的期望为：

$E = (\sum_{i=1}^nans_i)\div2^n$

依次累加每个点的贡献，最后乘以 $2^n$ 的逆元即可。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
long long n, ans, pow2[200006], siz[200006];
vector <int> e[200006];
void dfs(int now, int fa)
{
	siz[now] = 1;
	long long now_ans = pow2[n - 1], cnt = 0;
	for (int i = 0; i < e[now].size(); i++)
	{
		int to = e[now][i];
		if (to != fa) dfs(to, now), siz[now] += siz[to], cnt = (cnt + pow2[siz[to]] - 1) % mod; //累加每棵子树的贡献
	}
	cnt = (cnt + pow2[n - siz[now]]) % mod; //剩下一棵子树大小为 n - siz[now]
	ans = (ans + now_ans - cnt + mod) % mod;
}
long long quick_pow(long long x, long long p)
{
	long long res = 1;
	while (p)
	{
		if (p & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		p >>= 1;
	}
	return res;
}
int main()
{
	pow2[0] = 1;
	for (int i = 1; i <= 200000; i++)
		pow2[i] = (pow2[i - 1] * 2) % mod; //先递推出 2 的次方
	cin >> n;
	for (int i = 1; i <= n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	cout << ans * quick_pow(pow2[n], mod - 2) % mod << endl;
	return 0;
}

```

---

## 作者：Rnfmabj (赞：1)

## ABC149F

*2208

### 题意

给定一个 $n$ 个节点的树，每个点的颜色 $\frac{1}{2}$ 概率黑色，$\frac{1}{2}$ 概率白色，问这棵树上节点数最少的，包括所有黑色节点的连通块的白色节点的数量的期望。答案对 $10^9+7$ 取模。

$n \leq 2×10^5$，AT中文版一开始的翻译莫名其妙让 $n$ 缩水一倍导致我 RE 了一发。

### 题解

一开始以为是妙妙 DP，推了很久转移。后面发现是正难则反，对于每个点算贡献。

考虑一个点在什么情况下 **不会** 被记入答案。一种情况是其本身是黑点，不会直接贡献答案，一种情况则是其不被任何一个连通块包含。

对于不被任何一个连通块包含的情况，只有两种可能：一种是全部的黑点都在它的其中一个子树中（这里暂时把它看做根），一种是没有黑点。

设 $siz$ 表示一个点的子树大小，当前点为 $u$，则（除自己之外）没有黑点的概率是 $2^{-(n-1)}$，全部的黑点都在子树 $v$ 中的概率为 $2^{-(n-siz_v-1)}-2^{-(n-1)}$，全部加起来，然后乘上自身要作为白点的 $\frac{1}{2}$ 即为点 $u$ 的贡献。

最后累加所有点的贡献即为答案。

### 代码

```cpp
const ll maxn=2e5+5,mod=1e9+7;
vector<ll>e[maxn];
ll ksm(ll x,ll k){ll res=1;for(;k;k>>=1,x=x*x%mod)if(k&1)res=res*x%mod;return res;}
ll n;
ll ans;
ll inv[maxn],siz[maxn];
ll neg(ll x){
	return mod-x;
}
void dfs(ll x,ll fa){
	ll res=1;
	siz[x]=1;
	res=(res+neg(inv[n-1]))%mod;
	for(auto v:e[x]){
		if(v==fa)continue;
		dfs(v,x);
		siz[x]+=siz[v];
		res=(res+neg((inv[n-siz[v]-1]+neg(inv[n-1]))%mod))%mod;
	}
	res=(res+neg((inv[siz[x]-1]+neg(inv[n-1]))%mod))%mod;
	res=res*inv[1]%mod;
	ans=(ans+res)%mod;
	return ;
}
void solve(){
	n=R;
	inv[0]=1,inv[1]=ksm(2,mod-2);
	for(ll i=2;i<=n;i++)inv[i]=inv[i-1]*inv[1]%mod;
	for(ll i=1;i<n;i++){
		ll x=R,y=R;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,0);
	we(ans);
	return ;
}
```



---

## 作者：Rushroom (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT4839)

## 思路

设集合 $S$ 期望大小为 $E_S$，在集合 $S$ 中白色节点的期望数量为 $E_{W}$，在集合 $S$ 中黑色节点的期望数量为 $E_{B}$。

容易看出：$E_{W}=E_{S}-E_{B}$。\
因为节点颜色是等概率的，所以 $E_{B}=\frac{n}{2}$。\
那么，我们只需要求出 $E_{S}$ 就可以了。

设 $S$ 内的边数期望为 $E_{edge}$，所以 $E_{S}=E_{edge}+1$。\
**注意：在 $S=\varnothing$ 时，应该把边数看成 $-1$。**

又因为每条边之间互不影响，所以我们按照每条边来考虑。

考虑什么情况下，一条边 $\in S$。\
发现，**如果这条边连着的两个连通分量都包含黑色节点，那么这条边肯定会被选中**。\
设这条边连着的两个连通分量大小分别为 $x,y$，则被选中的概率为 
$$\frac{(2^x-1)(2^y-1)}{2^n}$$

将每一条边的贡献相加即可。

至于实现，可以先 DFS 一遍，算出每个子树的大小（设为 $siz$），然后就可以确定两个连通块分别的大小了，分别为 $siz$ 和 $n-siz$。

最后注意算 $E_{W}$ 时的细节。

## Code

```cpp
/*
 * @Description: How is the foundation so poor ah, I think FGgirl should go back to popularize group to learn again
 * @Author: FGgirl
 * @Date: 2022-03-12 17:43:51
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T_, case_;
int n, a, b;
vector<vector<int>>v;
ll siz[200005], ans = 0;
ll qpow(ll x, ll y) {
    ll p = 1;
    while (y) {
        if (y & 1)p = p * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return p;
}
void dfs(int k, int from) {
    siz[k] = 1;
    rep(i, v[k].size()) {
        int x = v[k][i];
        if (x == from)continue;
        dfs(x, k);
        siz[k] += siz[x];
    }
    if (!k)return;
    ll tmp = 1;
    tmp = tmp * ((qpow(2ll, siz[k]) + mod - 1) % mod) % mod;
    tmp = tmp * ((qpow(2ll, (ll)n - siz[k]) + mod - 1) % mod) % mod;
    ans = (ans + tmp) % mod;
}
void solve() {
    cin >> n;
    v.resize(n);
    rep(i, n - 1) {
        cin >> a >> b;
        a--, b--;
        v[a].pb(b);
        v[b].pb(a);
    }
    dfs(0, -1);
    ans = (ans + mod - 1) % mod;
    ans = ans * qpow(qpow(2ll, (ll)n), mod - 2) % mod;
    ans = ((ans + 1) % mod + mod - qpow(2, mod - 2) * n % mod) % mod;
    cout << ans;
}
int main() {
    T_ = 1;

    for (case_ = 1;case_ <= T_;case_++)solve();
    return 0;
}
```


---

