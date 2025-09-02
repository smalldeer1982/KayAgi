# Tree Coloring

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is the vertex $ 1 $ .

You have to color all vertices of the tree into $ n $ colors (also numbered from $ 1 $ to $ n $ ) so that there is exactly one vertex for each color. Let $ c_i $ be the color of vertex $ i $ , and $ p_i $ be the parent of vertex $ i $ in the rooted tree. The coloring is considered beautiful if there is no vertex $ k $ ( $ k > 1 $ ) such that $ c_k = c_{p_k} - 1 $ , i. e. no vertex such that its color is less than the color of its parent by exactly $ 1 $ .

Calculate the number of beautiful colorings, and print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
5
1 2
3 2
4 2
2 5```

### 输出

```
42```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5```

### 输出

```
53```

## 样例 #3

### 输入

```
20
20 19
20 4
12 4
5 8
1 2
20 7
3 10
7 18
11 8
9 10
17 10
1 15
11 16
14 11
18 10
10 1
14 2
13 17
20 6```

### 输出

```
955085064```

# 题解

## 作者：Froggy (赞：10)

设点 $i$ 的儿子个数为 $d_i$，那么显然 $\sum d_i=n-1$。

问题转化为求这个东西：（具体就看别的题解吧）

$$\prod\limits_{i=1}^n (1-d_ix)$$

$\mathcal{O}(n\log^2n)$ 的做法分治 NTT 很 naive 不再赘述。

这里分享一下 zz 的两个 $\mathcal{O}(n\log n)$ 做法。

$first:$

设一个阈值 $B$。

- $d_i\leq B$：对于一个固定的 $k$，可以 $\mathcal{O}(n)$ 求出 $\ln(1-kx)$。那么把 $\ln(1-d_i x)$ 加起来，然后再 $\exp$ 回去。这部分的复杂度是 $\mathcal{O}(Bn+n\log n)$。

- $d_i>B$：由于 $\sum d_i=n-1$，所以最多只有 $\frac{n}{B}$ 个，直接分治 NTT，这部分的复杂度是 $\mathcal{O}(\frac{n}{B}\log^2 \frac{n}{B})$。

设 $B=\log n$，那么总复杂度就是 $\mathcal{O}(n\log n)$。

众所周知，$\exp$ 很 slow，所以效率与 $\mathcal{O}(n\log^2 n)$ 的做法无太大差异。

---

$second:$

对于 $\prod\limits_{i=1}^{n} (1-d_ix)$，若 $\sum d_i$ 与 $n$ 同阶，则我们可以考虑将 $d_i$ 从大到小依次暴力卷积。复杂度由如下式子得到：
$$
\sum_{i}\sum_{j\in S}\ [j\ge i]=\sum_{j\in S}j=O(n)
$$
再带上 NTT 带的 $\log$，复杂度为 $\mathcal{O}(n\log n)$。

[**zz の code**](https://codeforces.ml/contest/1613/submission/137738311)

---



---

## 作者：wcyQwQ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1613F)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/03/08/CF1613F%20Tree%20Coloring/)

这篇题解的时间复杂度较高，但是会更详细地讲容斥部分。


首先直接求不太好求，所以我们考虑容斥，记 $g(i)$ 表示钦定 $i$ 个点满足 $c_u = c_{fa_u} - 1$ 的贡献，那么我们就有 $ans = \sum_{i=0}^n(-1)^ig(i)$，然后我们转而求 $g(i)$。

观察到 $g(i)$ 是由两个部分组成的，一个是被钦定的部分，一个则是为被钦定的部分，后者很好计算，因为没有要求所以我们可以直接算，也就是 $(n - i)!$，然后我们考虑前面的部分。观察到被钦定的点一定形成若干条从上到下的链，而只要链中一个点(包括链顶父亲)的 $c$ 值确定了那么整个链也都确定了。根据我们对 $g(i)$ 的定义，每条链顶的父亲是未被钦定的，所以这一部分已经被算在了 $(n - i)!$ 中，所以后面的部分确定了，每条链的 $c$ 值也就确定了，也就是我们只需计算这 $i$ 个点可能的形态有多少。

现在我们梳理一下，问题被我们转化为在树上取 $i$ 个点，形成若干条直链的方案数，因为是直链，所以我们每个点不能有多个儿子被选，所以这个点的生成函数即为 $\text{son}_ux + 1$，其中 $\text{son}_u$ 代表选这个点的方案，后面的 $1$ 代表不选，所以最终的答案即为 $[x^i]\prod_{i = 1}^n(\text{son}_ux + 1)$，可以用分治 $\text{NTT}$ 在 $O(n\log^2n)$ 的时间内解决。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for (int i = (j); i <= (k); i++)
#define R(i, j, k) for (int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define ll long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 5e5 + 10, M = 30, mod = 998244353, G = 3;
int deg[N], res[M][N], tmpL[N], tmpR[N], rev[N], fac[N];

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int mul(int x, int y) {return 1ll * x * y % mod;}

inline int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

inline void ntt(int a[], int n, int flg) {
	L(i, 0, n - 1) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int mid = 1; mid < n; mid <<= 1) {
		int W = qpow(G, (mod - 1) / (mid << 1));
		if (flg == -1) W = qpow(W, mod - 2);
		for (int i = 0; i < n; i += (mid << 1)) {
			int w = 1;
			L(j, i, i + mid - 1) {
				int x = a[j], y = mul(w, a[j + mid]);
				a[j] = (x + y) % mod, a[j + mid] = (x - y + mod) % mod;
				w = mul(w, W);
			}
		}
	}
}

inline void NTT(int a[], int b[], int n, int m) {
	int k = 1, l = 0;
	while (k <= n + m) k <<= 1, l++;
	L(i, n + 1, k) a[i] = 0;
	L(i, m + 1, k) b[i] = 0;
	L(i, 0, k - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
	ntt(a, k, 1), ntt(b, k, 1);
	L(i, 0, k - 1) a[i] = mul(a[i], b[i]);
	ntt(a, k, -1);
	int invK = qpow(k, mod - 2);
	L(i, 0, k - 1) a[i] = mul(a[i], invK);
}

inline void cdq(int d, int l, int r) {
	if (l == r) {
		res[d][0] = 1, res[d][1] = deg[l];
		return;
	}
	int mid = (l + r) >> 1;
	cdq(d + 1, l, mid);
	L(i, 0, mid - l + 1) res[d][i] = res[d + 1][i];
	cdq(d + 1, mid + 1, r);
	L(i, 0, mid - l + 1) tmpL[i] = res[d][i];
	L(i, 0, r - mid) tmpR[i] = res[d + 1][i];
	NTT(tmpL, tmpR, mid - l + 1, r - mid);
	L(i, 0, r - l + 1) res[d][i] = tmpL[i];
}

inline int getMod(int x) {return (x % mod + mod) % mod;}

int main() {
	int n = read();
	L(_, 1, n - 1) deg[read()]++, deg[read()]++;
	L(i, 2, n) deg[i]--;
	cdq(0, 1, n);
	fac[0] = 1;
	L(i, 1, n) fac[i] = mul(fac[i - 1], i);
	int ans = 0;
	L(i, 0, n - 1) ans = getMod(ans + ((i & 1) ? -1 : 1) * mul(fac[n - i], res[0][i]));
	printf("%d\n", ans);
    return 0;
}
```





---

## 作者：dead_X (赞：4)

## 思路
看到全部不等于直接考虑容斥。

我们考虑钦定一些点不合法，将偶数个不合法的减去奇数个不合法的就是答案。

考虑每个点只能钦定它孩子中至多一个不合法，而点之间是独立的。

那么我们将有 $t$ 个孩子的点用多项式 $(tx+1)$ 表示，将所有多项式相乘的 $k$ 次项就是 $k$ 个点不合法的方案数了。

所以我们要将 $n$ 个形如 $(tx+1)$ 的多项式相乘。

用分治 NTT 已经可以做到 $O(n\log^2 n)$ 了，但是没有封装分治 NTT 板子的 dXqwq 并不想现写分治 NTT。
## 小性质
显然只会有不超过 $\sqrt n$ 个 $t$。

我们将每个 $(tx+1)^k$ 只对 $(tx+1)$ 进行 DFT，并将 DFT 每项都变为其 $k$ 次方后加入答案，最后 IDFT 即可。

时间复杂度 $O(n\sqrt n\log n)$，甚至无法通过 pretest。
## 小优化
对 $(tx+1)$ 的 DFT 并不需要 $O(n\log n)$ 计算。

直接将前 $\frac{N}{2}$ 项赋值为 $1$，后 $\frac{N}{2}$ 项赋值为 $t$，最后乘单位根做一遍即可，时间复杂度可以降低到 $O(n\sqrt n)$，可以通过 pretest，略微卡常后能通过。

另一个小优化是多项式的最高次项等于非叶子节点个数，于是我们 $N$ 预处理时可以适当减小规模，这个优化可以卡掉大约 $\frac{1}{\sqrt 2}$ 的常数。
## 代码
```cpp
// Problem: F. Tree Coloring
// Contest: Educational Codeforces Round 118 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1613/problem/F
// Memory Limit: 512 MB
// Time Limit: 4500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//And in that light,I find deliverance.
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p) if(y&1) res=1ll*res*t%p;
	return res;
}
#define ull unsigned long long
inline ull calc(const ull&x){return x-(__uint128_t(x)*9920937979283557439ull>>93)*998244353;}
int A[262144],B[262144],C[262144];
int rev[262144],N=2;
inline void init()
{
    int d=N>>2;
    rev[0]=0,rev[1]=N>>1;
    for(int i=2; i<N; i<<=1,d>>=1)
        for(int j=0; j<i; ++j) rev[i+j]=rev[j]+d;
    return ;
}
inline void NTT(int *F)
{
    for(int i=0; i<(N>>1); ++i) F[i]=F[0];
    for(int i=(N>>1); i<N; ++i) F[i]=F[N>>1];
    int w0=1,w=qp(3,998244352/N);
	for(int i=0; i<(N>>1); ++i)
    {
        int x=F[i],y=calc(1ull*w0*F[i+(N>>1)]);
        ((F[i]=x+y)>=p)&&(F[i]-=p),
        ((F[i+(N>>1)]=x-y)<0)&&(F[i+(N>>1)]+=p),
        w0=calc(1ull*w0*w);
    }
}
inline void NTT_(int *F)
{
    for(int i=0; i<N; ++i) if(rev[i]>i) F[i]^=F[rev[i]]^=F[i]^=F[rev[i]];
    for(int len=2,M=1; len<=N; len<<=1,M<<=1)
    {
        int w=qp(332748118,998244352/len);
        for(int l=0; l<N; l+=len)
        {
            int w0=1;
            for(int i=l; i<l+M; ++i)
            {
                int x=F[i],y=calc(1ull*w0*F[i+M]);
                ((F[i]=x+y)>=p)&&(F[i]-=p),((F[i+M]=x-y)<0)&&(F[i+M]+=p),w0=calc(1ull*w0*w);
            }
        }
    }
}
int fac[300003],ifac[300003];
bool f[300003];
int a[300003],cnt[300003];
vector<int> e[300003];
void dfs(int x,int fa=0)
{
	for(int y:e[x]) if(y!=fa) ++a[x],dfs(y,x);
	return ;
}
signed main()
{
	int n=read();
	fac[0]=ifac[0]=1;
	for(int i=1; i<n; ++i)
	{
		int x=read(),y=read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1);
	int Q=0;
	for(int i=1; i<=n; ++i) if(a[i]) ++Q,++cnt[a[i]];
	for(int i=1; i<=n; ++i) fac[i]=1ll*fac[i-1]*i%p,ifac[i]=qp(fac[i],p-2);
	for(;N<=Q;N<<=1);
	init(),A[0]=1,NTT(A);
	for(int i=1; i<=n; ++i) if(cnt[i])
	{
		memset(B,0,sizeof(B));
		B[N>>1]=i,B[0]=1,NTT(B);
		for(int j=0; j<N; ++j) A[j]=1ll*A[j]*qp(B[j],cnt[i])%p;
	}
	NTT_(A);
	int ans=0,inv=qp(N,p-2);
	for(int i=0; i<=n; ++i) A[i]=1ll*A[i]*inv%p;
	for(int i=0; i<=n; ++i) ans=(ans+1ll*fac[n-i]*((i&1)?p-A[i]:A[i]))%p;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

提供一个反演的推导，可以推广到对所有 $i$ 求出有恰好 $i$ 个点不满足条件的染色方案数。

---------------

考虑容斥。我们首先在树上钦定一些链的颜色构成一个从上至下连续的东西。这个是简单的，我们设 $dp_i$ 表示把树剖成点不相交的 $i$ 条**直上直下**的链的方案数，那么赋颜色的方案就有 $i!dp_i$ 种。

显然算重了。因为可能会出现两根链颜色上连续，在树上也连续，但我们钦定它断开成两条链的情况。注意到每种赋颜色方案一定一一对应恰好一种极长链剖方案，于是不妨设 $f_i$ 表示这个极长链剖方案剖成 $i$ 根链，$g_i=i!dp_i$ 表示这个链剖方案有 $i$ 条链，但不一定是最少的。

类似二项式反演，我们容易得到 $f,g$ 之间的式子：

$$
g_i=\sum\limits_{j=1}^i {n-j\choose i-j}f_j
$$

一个所有链都极长有 $j$ 条链的方案，树上有 $n-j$ 条边被链覆盖着。在这些边中选择 $i-j$ 条断掉，链数就增加到 $i$ 了。

我们希望求出 $f_n$。

反演这个式子。猜测这个式子的反演形态和二项式反演应该差不多，于是：

$$
f_i=\sum\limits_{j=1}^i(-1)^{i-j}{n-j\choose i-j}g_j
$$

> Proof.   
> 翻转下标，令 $f'_i=f_{n-i+1},g'_i=g_{n-i+1}$，然后考虑反演 $f'$ 和 $g'$ 的新式子：
> $$
> g'_i=\sum\limits_{j=i}^{n} {j-1\choose j-i}f'_j=\sum\limits_{j=i}^n{j-1\choose i-1}f'_j
> $$
> 注意到这就是朴素的二项式反演，只是所有下标后移了一位。于是我们有：
> $$
> f'_i=\sum\limits_{j=i}^n(-1)^{j-i}{j-1\choose i-1}g'_j
> $$
> 将下标转回去即可得到原始的反演。

注意到 $f_n$ 是一个特殊情况，反演等价于直接容斥原理。

于是考虑如何求出 $g_i$，即 $dp_i$。直接树形背包是 $\mathcal O(n^2)$ 的，难以优化……吗？

不要忘记我们这里只有**直上直下**的链。考虑刻画一个剖分的性质，可以发现就是每个点选至多一个儿子，选儿子的方案和链剖分方案一一对应。于是我们规定在链底计数一条链，链数就是没有选儿子的点的数量，当然叶子选不了儿子就自然没有选儿子。于是这变成一个类背包问题，我们可以使用生成函数：第 $i$ 个点的 GF 是 $F(i)=x+son_i$，表示多一条链方案数不变，或者链数不变方案数乘儿子的数量。把这个东西全部乘起来，第 $i$ 项的系数就是 $g_i$。

暴力乘显然不行，最后会变成一个巨长的多项式乘一个一次多项式。所以使用分治 NTT 就好了，时间复杂度 $\mathcal O(n\log^2n)$。想求出所有 $f$ 的答案只需再对着反演的式子做一次 NTT 即可，瓶颈不在这里。

有了多项式板子代码还是很好写的，就是不知道为什么我的板子跑得特别慢。

```cpp
int n;
int sons[N];
Poly gf[N];
Poly divide(int l,int r){
	if(l==r) return gf[l];
	int mid=(l+r>>1);
	Poly lef=divide(l,mid);
	Poly rig=divide(mid+1,r);
	return lef*rig;
}
modint fac[N];
modint G[N];
modint F;
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	init(mod);
	ios::sync_with_stdio(false);
	cin>>n;
	fac[0]=1;
	fr1(i,1,n) fac[i]=fac[i-1]*i;
	fr1(i,2,n){
		int u,v;
		cin>>u>>v;
		sons[u]++,sons[v]++;
	}
	fr1(i,1,n){
		if(i>1) sons[i]--;
		gf[i]={sons[i],1};
	}
	Poly ans=divide(1,n);
	fr1(i,1,n) G[i]=ans.p[i]*fac[i];
	// fr1(i,1,n) cout<<G[i]<<" \n"[i==n];
	fr1(i,1,n){
		if((n-i)&1) F-=G[i];
		else F+=G[i];
	}
	cout<<F<<'\n';
	ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：gdf_yhm (赞：0)

[CF1613F](https://www.luogu.com.cn/problem/CF1613F)

[my blog](https://yhddd123.github.io/post/cf1613f-ti-jie/)

### 思路

容斥。钦定 $i$ 个点不满足 $c_u\neq c_{fa}-1$ 的限制的方案数为 $f_i$，有 $n-1$ 对限制，$ans=\sum_{i=0}^{n-1}(-1)^if_i$。

由于 $c$ 是排列，每个点 $u$ 只有一个儿子能被钦定不合法。而没有被钦定的点之间大小关系独立，即 $(n-i)!$；被钦定的点的值取决于祖先最近的没有被钦定的点，这部分的贡献即每个点独立的选一个儿子或不选，即 $[x^i]\prod(1+d_ux)$。

只需要快速求出 $n$ 个一次的多项式相乘的系数，分治 ntt 复杂度 $O(n\log^2 n)$。

因为有 $\sum d_u$ 是 $O(n)$ 的。将相同的 $(dx+1)$ 合起来做。记有 $t_i$ 个 $d_u=i$。$\prod (ix+1)^{t_i}$ 可以二项式系数直接算。按 $d_u$ 的值从大往小做，直接和之前算出来的多项式 ntt 乘起来，复杂度是对的。即每次 ntt 的长度之和 $\sum_{i=1}^n (\sum_{j=i}^n t_j)=\sum i\times t_i=\sum d_u$，是 $O(n)$ 级别的。复杂度 $O(n\log n)$。

### code

```cpp
int n,ans;
int d[maxn],t[maxn];
vector<int> e[maxn];
void dfs(int u,int fa){
	for(int v:e[u])if(v!=fa)d[u]++,dfs(v,u);
}
vector<int> f;
using poly::mul;
int fac[maxn],inv[maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)t[d[i]]++;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=n-1;i;i--){
		vector<int> g(t[i]+1);
		for(int j=0,mul=1;j<=t[i];j++)g[j]=C(t[i],j)*mul%mod,mul=mul*i%mod;
		f=mul(f,g);
	}
	for(int i=0;i<f.size();i++)(ans+=((i&1)?(mod-1):1)*fac[n-i]%mod*f[i])%=mod;
	printf("%lld\n",ans);
}
```

---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17316432.html)，第十题。

考虑钦定 $k$ 个点不满足条件，即对于每个点 $x,c_x=c_{f_x}-1$，且 $c$ 仍然是 $1\sim n$ 的排列，我们考虑对这个东西计数，设满足这条件的方案数为 $f_k$。
  
由于剩下 $n-k$ 个点能任意挑，于是系数为 $(-1)^k(n-k)!$，
 容斥一下答案为：$\sum\limits_{i=0}^n (-1)^i(n-i)!f_i$。
  
设 $s_i$ 表示点 $i$ 的**儿子**数量。由于 $c$ 仍然是 $1\sim n$ 的排列，于是 $k$ 个点的分布一定满足：每个节点**至多**只有一个儿子被选中。于是 $f_k=[x^k]\prod\limits_{i=1}^n(1+s_ix)\Rightarrow (-1)^kf_k=[x^k]\prod\limits_{i=1}^n(1-s_ix)$。
  
于是我们只需求多项式 $\prod\limits_{i=1}^n(1-s_ix)$ 即可，注意有**特殊条件** $\sum\limits_{i=1}^n s_i=n$。
  
如果没有特殊条件只能朴素分治 **NTT** 做到 $O(n\log^2n)$。接下来介绍科技。
  
---

设有 $c_i$ 个 $s_t=i$，则有：$\sum\limits_{i=0}^n c_i=\sum\limits_{i=1}^n ic_i=n$。
  
考虑对于每个 $i$，先 $O(c_i)$ 二项式展开求出 $g_i=(1-ix)^{c_i}$，然后把 $g_i$ 卷到 $ans$ 上，即 $ans\gets ans\times g_i$。我们算一下这样的复杂度，发现是 $\sum\limits_{i=1}^n\log n\left(\sum\limits_{j=1}^{i}c_j\right)=\log n\sum\limits_{i=1}^nic_i=n\log n$ 的，于是复杂度为 $O(n\log n)$。

---
  
代码：
  
```cpp
#include<bits/stdc++.h>
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
inline int rd()
{
    int x=0,zf=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') (ch=='-')and(zf=-1),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*zf;
}
inline void wr(int x)
{
    if(x==0) return putchar('0'),putchar(' '),void();
    int num[35],len=0;
    while(x) num[++len]=x%10,x/=10;
    for(int i=len;i>=1;i--) putchar(num[i]+'0');
    putchar(' ');
}
const int mod=998244353,N=4e6+5;
int n,m,a[N],b[N],c[N],cc[N],jc[N],inv[N],w[N],mmax;
vector<int>g[N];
inline int bger(int x){return x|=x>>1,x|=x>>2,x|=x>>4,x|=x>>8,x|=x>>16,x+1;}
inline int md(int x){return x>=mod?x-mod:x;}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
inline int C(int n,int m){return 1ll*jc[n]*inv[m]%mod*inv[n-m]%mod;}
inline void init(int mmax)
{
	for(int i=1,j,k;i<mmax;i<<=1)
		for(w[j=i]=1,k=ksm(3,(mod-1)/(i<<1)),j++;j<(i<<1);j++)
			w[j]=1ll*w[j-1]*k%mod;
}
inline void DNT(int *a,int mmax)
{
	for(int i,j,k=mmax>>1,L,*W,*x,*y,z;k;k>>=1)
		for(L=k<<1,i=0;i<mmax;i+=L)
			for(j=0,W=w+k,x=a+i,y=x+k;j<k;j++,W++,x++,y++)
				*y=1ll*(*x+mod-(z=*y))* *W%mod,*x=md(*x+z);
}
inline void IDNT(int *a,int mmax)
{
	for(int i,j,k=1,L,*W,*x,*y,z;k<mmax;k<<=1)
		for(L=k<<1,i=0;i<mmax;i+=L)
			for(j=0,W=w+k,x=a+i,y=x+k;j<k;j++,W++,x++,y++)
				z=1ll* *W* *y%mod,*y=md(*x+mod-z),*x=md(*x+z);
	reverse(a+1,a+mmax);
	for(int inv=ksm(mmax,mod-2),i=0;i<mmax;i++) a[i]=1ll*a[i]*inv%mod;
}
inline void NTT(int *a,int *b,int n,int m)
{
	int mmax=bger(n+m);init(mmax);
	for(int i=m+1;i<mmax;i++) b[i]=0;DNT(a,mmax);DNT(b,mmax);
	for(int i=0;i<mmax;i++) a[i]=1ll*a[i]*b[i]%mod;
	IDNT(a,mmax);for(int i=n+m+1;i<mmax;i++) a[i]=0;
}
void dfs(int x,int fa){for(int i:g[x]) if(i^fa) c[x]++,dfs(i,x);}
int main()
{
	n=rd();for(int i=1,u,v;i<n;i++) u=rd(),v=rd(),g[u].push_back(v),g[v].push_back(u);dfs(1,0);
	jc[0]=1;for(int i=1;i<=n;i++) jc[i]=1ll*jc[i-1]*i%mod;
	inv[n]=ksm(jc[n],mod-2);for(int i=n-1;~i;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	a[0]=1;for(int i=1;i<=n;i++) cc[c[i]]++;int len=0;
	for(int i=1;i<=n;i++)
	{
		int mul=1;if(!cc[i]) continue;
		for(int j=0;j<=cc[i];j++) b[j]=1ll*mul*C(cc[i],j)%mod,mul=1ll*mul*(mod-i)%mod;
		NTT(a,b,len,cc[i]);len+=cc[i];
	}int ans=0;
	for(int i=0;i<=n;i++) ans=md(ans+1ll*jc[n-i]*a[i]%mod);wr(ans);
    return 0;
}
```

---

